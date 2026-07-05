#include "debug_shape/api/shape/ShapeType.h"

#include "mc/scripting/modules/minecraft/primitiveshapes/ScriptPrimitiveShapeType.h"

static_assert(
    std::is_same_v<std::underlying_type_t<debug_shape::ShapeType>, uchar>
        && std::is_same_v<std::underlying_type_t<ScriptModuleMinecraft::ScriptPrimitiveShapeType>, uchar>,
    "ShapeType and ScriptPrimitiveShapeType must have uchar as underlying type"
);

constexpr bool operator==(debug_shape::ShapeType lhs, ScriptModuleMinecraft::ScriptPrimitiveShapeType rhs) {
    return static_cast<uchar>(lhs) == static_cast<uchar>(rhs);
}

namespace debug_shape {

static_assert(ShapeType::Line == ScriptModuleMinecraft::ScriptPrimitiveShapeType::Line);
static_assert(ShapeType::Box == ScriptModuleMinecraft::ScriptPrimitiveShapeType::Box);
static_assert(ShapeType::Sphere == ScriptModuleMinecraft::ScriptPrimitiveShapeType::Sphere);
static_assert(ShapeType::Circle == ScriptModuleMinecraft::ScriptPrimitiveShapeType::Circle);
static_assert(ShapeType::Text == ScriptModuleMinecraft::ScriptPrimitiveShapeType::Text);
static_assert(ShapeType::Arrow == ScriptModuleMinecraft::ScriptPrimitiveShapeType::Arrow);
static_assert(ShapeType::NumShapeTypes == ScriptModuleMinecraft::ScriptPrimitiveShapeType::NumShapeTypes);

} // namespace debug_shape
