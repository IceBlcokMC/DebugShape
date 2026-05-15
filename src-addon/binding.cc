#include "debug_shape/api/IDebugShapeDrawer.h"
#include "debug_shape/api/shape/IDebugArrow.h"
#include "debug_shape/api/shape/IDebugBox.h"
#include "debug_shape/api/shape/IDebugCircle.h"
#include "debug_shape/api/shape/IDebugLine.h"
#include "debug_shape/api/shape/IDebugShape.h"
#include "debug_shape/api/shape/IDebugSphere.h"
#include "debug_shape/api/shape/IDebugText.h"
#include "debug_shape/api/shape/IDrawer.h"
#include "debug_shape/api/shape/ShapeID.h"
#include "debug_shape/api/shape/ShapeType.h"
#include "debug_shape/api/shape/extension/IBoundsBox.h"

#include "ll/api/service/Bedrock.h"

#include "mc/deps/core/math/Color.h"
#include "mc/platform/UUID.h"
#include "mc/world/actor/player/Player.h"
#include "mc/world/level/Level.h"

#include "jspp/Jspp.h"
#include "jspp/binding/BindingUtils.h"
#include "jspp/binding/MetaBuilder.h"
#include "jspp/binding/ReturnValuePolicy.h"
#include "jspp/binding/TypeConverter.h"
#include "jspp/core/Engine.h"
#include "jspp/core/Exception.h"
#include "jspp/core/MetaInfo.h"
#include "jspp/core/Reference.h"
#include "jspp/core/Value.h"

#include "magic_enum/magic_enum.hpp"
#include "mc/world/phys/AABB.h"

#include <string>
#include <string_view>
#include <type_traits>

namespace jspp::binding {

// 手动特化兼容处理
// 这些类型无法走泛型特化，需要兼容 LSE 引擎内的 LLSE 类型

template <>
struct TypeConverter<Vec3> {
    static Local<Value> toJs(Vec3 const& v, ReturnValuePolicy /* policy */, Local<Value> const& /* parent */) {
        auto obj = Object::newObject();
        obj.set(String::newString("x"), Number::newNumber(v.x));
        obj.set(String::newString("y"), Number::newNumber(v.y));
        obj.set(String::newString("z"), Number::newNumber(v.z));
        return obj;
    }
    static Vec3 toCpp(Local<Value> const& v) {
        if (!v.isObject()) {
            throw Exception{"expected object"};
        }
        auto obj = v.asObject();
        return {
            obj.get(String::newString("x")).asNumber().getFloat(),
            obj.get(String::newString("y")).asNumber().getFloat(),
            obj.get(String::newString("z")).asNumber().getFloat(),
        };
    }
};

template <>
struct TypeConverter<Player> {
    // LLSE_Player 不支持脚本端构造，为了兼容 LSE 引擎的 LLSE_Player 对象，这里传递 UUID
    static Local<Value> toJs(Player& v, ReturnValuePolicy /* policy */, Local<Value> const& /* parent */) {
        return String::newString(v.getUuid().asString());
    }
    static Player* toCpp(Local<Value> const& v) {
        if (!v.isString()) {
            throw Exception{"expected string"};
        }
        auto strUuid = v.asString().getValue();
        if (!mce::UUID::canParse(strUuid)) {
            throw Exception{"invalid uuid"};
        }

        auto uuid = mce::UUID::fromString(strUuid);
        if (auto level = ll::service::getLevel()) {
            return level->getPlayer(uuid);
        }
        return nullptr;
    }
};

template <>
struct TypeConverter<DimensionType> {
    static Local<Value> toJs(DimensionType const& v, ReturnValuePolicy /* policy */, Local<Value> const& /* parent */) {
        return Number::newNumber(static_cast<int>(v));
    }
    static DimensionType toCpp(Local<Value> const& v) { return static_cast<DimensionType>(v.asNumber().getInt32()); }
};

template <>
struct TypeConverter<AABB> {
    using Vec3Converter = TypeConverter<Vec3>;

    static Local<Value> toJs(AABB const& v, ReturnValuePolicy policy, Local<Value> const& parent) {
        auto obj = Object::newObject();
        obj.set(String::newString("min"), Vec3Converter::toJs(v.min, policy, parent));
        obj.set(String::newString("max"), Vec3Converter::toJs(v.max, policy, parent));
        return obj;
    }
    static AABB toCpp(Local<Value> const& v) {
        if (!v.isObject()) {
            throw Exception{"expected object"};
        }
        auto obj = v.asObject();
        return {
            Vec3Converter::toCpp(obj.get(String::newString("min"))),
            Vec3Converter::toCpp(obj.get(String::newString("max")))
        };
    }
};

} // namespace jspp::binding

namespace {

using namespace jspp;
using namespace jspp::binding;

template <typename T>
    requires std::is_enum_v<T>
EnumMeta generateEnumMeta(std::string_view name) {
    EnumMetaBuilder<T> meta = defEnum<T>(name);
    for (auto [value, enumName] : magic_enum::enum_entries<T>()) {
        meta.value(std::string{enumName}, value);
    }
    return meta.build();
}


EnumMeta const kShapeTypeMeta = generateEnumMeta<debug_shape::ShapeType>("ShapeType");

ClassMeta const kDrawerMeta =
    defClass<debug_shape::IDrawer>("Drawer")
        .ctor(nullptr)
        .method(
            "draw",
            static_cast<void (debug_shape::IDrawer::*)() const>(&debug_shape::IDrawer::draw),             //
            static_cast<void (debug_shape::IDrawer::*)(Player&) const>(&debug_shape::IDrawer::draw),      //
            static_cast<void (debug_shape::IDrawer::*)(DimensionType) const>(&debug_shape::IDrawer::draw) //
        )
        .method(
            "remove",
            static_cast<void (debug_shape::IDrawer::*)() const>(&debug_shape::IDrawer::remove),             //
            static_cast<void (debug_shape::IDrawer::*)(Player&) const>(&debug_shape::IDrawer::remove),      //
            static_cast<void (debug_shape::IDrawer::*)(DimensionType) const>(&debug_shape::IDrawer::remove) //
        )
        .method(
            "update",
            static_cast<void (debug_shape::IDrawer::*)() const>(&debug_shape::IDrawer::update),             //
            static_cast<void (debug_shape::IDrawer::*)(Player&) const>(&debug_shape::IDrawer::update),      //
            static_cast<void (debug_shape::IDrawer::*)(DimensionType) const>(&debug_shape::IDrawer::update) //
        )
        // IDebugShapeDrawer Batch Interface
        .func(
            "drawAll",
            [](std::vector<debug_shape::IDebugShape const*> const& shapes) {
                debug_shape::IDebugShapeDrawer::getInstance().drawShapes(shapes);
            },
            [](std::vector<debug_shape::IDebugShape const*> const& shapes, Player& player) {
                debug_shape::IDebugShapeDrawer::getInstance().drawShapes(shapes, player);
            },
            [](std::vector<debug_shape::IDebugShape const*> const& shapes, DimensionType dim) {
                debug_shape::IDebugShapeDrawer::getInstance().drawShapes(shapes, dim);
            }
        )
        .func(
            "updateAll",
            [](std::vector<debug_shape::IDebugShape const*> const& shapes) {
                debug_shape::IDebugShapeDrawer::getInstance().drawShapes(shapes);
            },
            [](std::vector<debug_shape::IDebugShape const*> const& shapes, Player& player) {
                debug_shape::IDebugShapeDrawer::getInstance().drawShapes(shapes, player);
            },
            [](std::vector<debug_shape::IDebugShape const*> const& shapes, DimensionType dim) {
                debug_shape::IDebugShapeDrawer::getInstance().drawShapes(shapes, dim);
            }
        )
        .func(
            "removeAll",
            [](std::vector<debug_shape::IDebugShape const*> const& shapes) {
                debug_shape::IDebugShapeDrawer::getInstance().removeShapes(shapes);
            },
            [](std::vector<debug_shape::IDebugShape const*> const& shapes, Player& player) {
                debug_shape::IDebugShapeDrawer::getInstance().removeShapes(shapes, player);
            },
            [](std::vector<debug_shape::IDebugShape const*> const& shapes, DimensionType dim) {
                debug_shape::IDebugShapeDrawer::getInstance().removeShapes(shapes, dim);
            }
        )
        .build();

ClassMeta const kColorMeta =
    defClass<mce::Color>("Color")
        .ctor<>()
        .ctor<int, int, int, int>() // rgba
        .ctor<std::string_view>()   // hex
        .prop(
            "r",
            [](mce::Color const& color) { return color.r; },
            [](InstancePayload& payload, Arguments const& args) {
                auto inst = payload.unwrap<mce::Color>();
                inst->r   = args[0].asNumber().getFloat();
            }
        )
        .prop(
            "g",
            [](mce::Color const& color) { return color.g; },
            [](InstancePayload& payload, Arguments const& args) {
                auto inst = payload.unwrap<mce::Color>();
                inst->g   = args[0].asNumber().getFloat();
            }
        )
        .prop(
            "b",
            [](mce::Color const& color) { return color.b; },
            [](InstancePayload& payload, Arguments const& args) {
                auto inst = payload.unwrap<mce::Color>();
                inst->b   = args[0].asNumber().getFloat();
            }
        )
        .prop(
            "a",
            [](mce::Color const& color) { return color.a; },
            [](InstancePayload& payload, Arguments const& args) {
                auto inst = payload.unwrap<mce::Color>();
                inst->a   = args[0].asNumber().getFloat();
            }
        )
        .method("toHexString", &mce::Color::toHexString)
        // builtin colors
        .var_readonly("BLACK", &mce::Color::BLACK, ReturnValuePolicy::kReferencePersistent)
        .var_readonly("WHITE", &mce::Color::WHITE, ReturnValuePolicy::kReferencePersistent)
        .var_readonly("RED", &mce::Color::RED, ReturnValuePolicy::kReferencePersistent)
        .var_readonly("GREEN", &mce::Color::GREEN, ReturnValuePolicy::kReferencePersistent)
        .var_readonly("BLUE", &mce::Color::BLUE, ReturnValuePolicy::kReferencePersistent)
        .var_readonly("YELLOW", &mce::Color::YELLOW, ReturnValuePolicy::kReferencePersistent)
        .var_readonly("PURPLE", &mce::Color::PURPLE, ReturnValuePolicy::kReferencePersistent)
        // @LeviLamina v26.10.11, These colors have no symbols, the link failed.
        // .var_readonly("CYAN", &mce::Color::CYAN, ReturnValuePolicy::kReferencePersistent)
        // .var_readonly("ORANGE", &mce::Color::ORANGE, ReturnValuePolicy::kReferencePersistent)
        // .var_readonly("PINK", &mce::Color::PINK, ReturnValuePolicy::kReferencePersistent)
        // .var_readonly("GREY", &mce::Color::GREY, ReturnValuePolicy::kReferencePersistent)
        // .var_readonly("REBECCA_PURPLE", &mce::Color::REBECCA_PURPLE, ReturnValuePolicy::kReferencePersistent)
        .var_readonly(
            "CYAN",
            []() -> const mce::Color& {
                static mce::Color c(0, 255, 255);
                return c;
            },
            ReturnValuePolicy::kReferencePersistent
        )
        .var_readonly(
            "GREY",
            []() -> const mce::Color& {
                static mce::Color c(128, 128, 128);
                return c;
            },
            ReturnValuePolicy::kReferencePersistent
        )
        .var_readonly(
            "ORANGE",
            []() -> const mce::Color& {
                static mce::Color c(255, 165, 0);
                return c;
            },
            ReturnValuePolicy::kReferencePersistent
        )
        .var_readonly(
            "PINK",
            []() -> const mce::Color& {
                static mce::Color c(255, 192, 203);
                return c;
            },
            ReturnValuePolicy::kReferencePersistent
        )
        .var_readonly(
            "REBECCA_PURPLE",
            []() -> const mce::Color& {
                static mce::Color c(102, 51, 153);
                return c;
            },
            ReturnValuePolicy::kReferencePersistent
        )
        .build();

ClassMeta const kDebugShapeMeta =
    defClass<debug_shape::IDebugShape>("DebugShape")
        .ctor(nullptr)
        .inherit<debug_shape::IDrawer>(kDrawerMeta)
        .prop_readonly("id", [](debug_shape::IDebugShape const* shape) { return shape->getShapeID().val_; })
        .prop_readonly("type", &debug_shape::IDebugShape::getShapeType)
        .prop("location", &debug_shape::IDebugShape::getLocation, &debug_shape::IDebugShape::setLocation)
        .prop("rotation", &debug_shape::IDebugShape::getRotation, &debug_shape::IDebugShape::setRotation)
        .prop("scale", &debug_shape::IDebugShape::getScale, &debug_shape::IDebugShape::setScale)
        .prop("color", &debug_shape::IDebugShape::getColor, &debug_shape::IDebugShape::setColor)
        .method("hasDuration", &debug_shape::IDebugShape::hasDuration)
        .prop("totalTimeLeft", &debug_shape::IDebugShape::getTotalTimeLeft, &debug_shape::IDebugShape::setTotalTimeLeft)
        .prop("dimid", &debug_shape::IDebugShape::getDimensionId, &debug_shape::IDebugShape::setDimensionId)
        .build();

ClassMeta const kDebugTextMeta = defClass<debug_shape::IDebugText>("DebugText")
                                     .func("create", &debug_shape::IDebugText::create)
                                     .ctor(nullptr)
                                     .inherit<debug_shape::IDebugShape>(kDebugShapeMeta)
                                     .prop("text", &debug_shape::IDebugText::getText, &debug_shape::IDebugText::setText)
                                     .build();

ClassMeta const kDebugLineMeta =
    defClass<debug_shape::IDebugLine>("DebugLine")
        .func("create", &debug_shape::IDebugLine::create)
        .ctor(nullptr)
        .inherit<debug_shape::IDebugShape>(kDebugShapeMeta)
        .prop("endPosition", &debug_shape::IDebugLine::getEndPosition, &debug_shape::IDebugLine::setEndPosition)
        .build();

ClassMeta const kDebugCircleMeta = defClass<debug_shape::IDebugCircle>("DebugCircle")
                                       .func("create", &debug_shape::IDebugCircle::create)
                                       .ctor(nullptr)
                                       .inherit<debug_shape::IDebugShape>(kDebugShapeMeta)
                                       .build();

ClassMeta const kDebugBoxMeta = defClass<debug_shape::IDebugBox>("DebugBox")
                                    .func("create", &debug_shape::IDebugBox::create)
                                    .ctor(nullptr)
                                    .inherit<debug_shape::IDebugShape>(kDebugShapeMeta)
                                    .prop("bound", &debug_shape::IDebugBox::getBound, &debug_shape::IDebugBox::setBound)
                                    .build();

ClassMeta const kDebugSphereMeta =
    defClass<debug_shape::IDebugSphere>("DebugSphere")
        .func("create", &debug_shape::IDebugSphere::create)
        .ctor(nullptr)
        .inherit<debug_shape::IDebugShape>(kDebugShapeMeta)
        .prop("numSegments", &debug_shape::IDebugSphere::getNumSegments, &debug_shape::IDebugSphere::setNumSegments)
        .build();

ClassMeta const kDebugArrowMeta =
    defClass<debug_shape::IDebugArrow>("DebugArrow")
        .func("create", &debug_shape::IDebugArrow::create)
        .ctor(nullptr)
        .inherit<debug_shape::IDebugShape>(kDebugShapeMeta)
        .prop("endPosition", &debug_shape::IDebugArrow::getEndPosition, &debug_shape::IDebugArrow::setEndPosition)
        .prop("headLength", &debug_shape::IDebugArrow::getHeadLength, &debug_shape::IDebugArrow::setHeadLength)
        .prop("headRadius", &debug_shape::IDebugArrow::getHeadRadius, &debug_shape::IDebugArrow::setHeadRadius)
        .prop("headSegments", &debug_shape::IDebugArrow::getHeadSegments, &debug_shape::IDebugArrow::setHeadSegments)
        .build();

ClassMeta const kBoundsBoxMeta =
    defClass<debug_shape::extension::IBoundsBox>("extension.BoundsBox")
        .func("create", &debug_shape::extension::IBoundsBox::create)
        .ctor(nullptr)
        .inherit<debug_shape::IDrawer>(kDrawerMeta)
        .method("setBounds", &debug_shape::extension::IBoundsBox::setBounds)
        .prop(
            "rotation",
            &debug_shape::extension::IBoundsBox::getRotation,
            &debug_shape::extension::IBoundsBox::setRotation
        )
        .prop("color", &debug_shape::extension::IBoundsBox::getColor, &debug_shape::extension::IBoundsBox::setColor)
        .method("hasDuration", &debug_shape::extension::IBoundsBox::hasDuration)
        .prop(
            "totalTimeLeft",
            &debug_shape::extension::IBoundsBox::getTotalTimeLeft,
            &debug_shape::extension::IBoundsBox::setTotalTimeLeft
        )
        .prop(
            "dimid",
            &debug_shape::extension::IBoundsBox::getDimensionId,
            &debug_shape::extension::IBoundsBox::setDimensionId
        )
        .build();

} // namespace


jspp::ModuleMeta const& buildModule(std::string_view name) {
    static jspp::ModuleMeta const m = jspp::binding::defModule(name)
                                          .exportEnum(kShapeTypeMeta)
                                          .exportClass(kDrawerMeta)
                                          .exportClass(kDebugShapeMeta)
                                          .exportClass(kDebugTextMeta)
                                          .exportClass(kDebugLineMeta)
                                          .exportClass(kDebugCircleMeta)
                                          .exportClass(kDebugBoxMeta)
                                          .exportClass(kDebugSphereMeta)
                                          .exportClass(kDebugArrowMeta)
                                          .exportClass(kColorMeta)
                                          .exportClass(kBoundsBoxMeta)
                                          .build();
    return m;
}

static std::unordered_map<JSContext*, jspp::Engine*> g_activeEngines;
static std::mutex                                    g_mutex; // for g_activeEngines

jspp::Engine* getOrCreateEngine(JSContext* ctx) {
    std::scoped_lock lock(g_mutex);

    auto iter = g_activeEngines.find(ctx);
    if (iter == g_activeEngines.end()) {
        auto rt     = JS_GetRuntime(ctx);
        auto engine = new jspp::Engine{rt, ctx, jspp::qjs_backend::QjsInitializeFlags::AddonMode};
        iter        = g_activeEngines.emplace(ctx, engine).first;
    }
    return iter->second;
}
JSClassID newCleanupClass(JSContext* ctx) {
    auto rt = JS_GetRuntime(ctx);

    JSClassID  id{JS_INVALID_CLASS_ID};
    JSClassDef def{};
    def.class_name = "__engine_cleanup_hook__";
    def.finalizer  = [](JSRuntime* /*rt*/, JSValueConst val) {
        auto id = JS_GetClassID(val);
        if (auto engine = static_cast<jspp::Engine*>(JS_GetOpaque(val, id))) {
            {
                std::scoped_lock lock(g_mutex);
                g_activeEngines.erase(engine->context());
            }
            delete engine;
        }
    };
    JS_NewClassID(rt, &id);
    JS_NewClass(rt, id, &def);
    assert(id != JS_INVALID_CLASS_ID);
    return id;
}
void addCleanupHook(JSContext* ctx, JSClassID id, JSModuleDef* def, jspp::Engine* engine) {
    auto v = JS_NewObjectClass(ctx, id);
    JS_SetOpaque(v, engine);

    // Note: jspp has used ModulePrivateData to transmit the engine pointer, you cannot change it.
    auto priv = JS_GetModulePrivateValue(ctx, def);
    JS_DefinePropertyValueStr(ctx, priv, "__cleanup_for_engine__", v, 0);
    JS_FreeValue(ctx, priv);
}

#ifdef _WIN32
#define JS_MODULE_EXPORT __declspec(dllexport)
#else
#define JS_MODULE_EXPORT __attribute__((visibility("default")))
#endif

extern "C" {
JS_MODULE_EXPORT JSModuleDef* js_init_module(JSContext* ctx, const char* module_name) {
    if (auto engine = getOrCreateEngine(ctx)) {
        auto id     = newCleanupClass(ctx);
        auto module = jspp::qjs_backend::QjsModuleLoader::performNewNativeModule(engine, &buildModule(module_name));
        addCleanupHook(ctx, id, module, engine);
        return module;
    }
    return nullptr;
}
}
