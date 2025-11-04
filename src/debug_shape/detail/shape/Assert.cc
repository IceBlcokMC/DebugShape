#include "debug_shape/api/shape/ShapeType.h"

#include "mc/scripting/modules/minecraft/debugdrawer/ScriptDebugShapeType.h"

static_assert(
    std::is_same_v<std::underlying_type_t<debug_shape::ShapeType>, uchar>
        && std::is_same_v<std::underlying_type_t<ScriptModuleDebugUtilities::ScriptDebugShapeType>, uchar>,
    "ShapeType and ScriptDebugShapeType must have uchar as underlying type"
);

constexpr bool operator==(debug_shape::ShapeType lhs, ScriptModuleDebugUtilities::ScriptDebugShapeType rhs) {
    return static_cast<uchar>(lhs) == static_cast<uchar>(rhs);
}

namespace debug_shape {

static_assert(ShapeType::Line == ScriptModuleDebugUtilities::ScriptDebugShapeType::Line);
static_assert(ShapeType::Box == ScriptModuleDebugUtilities::ScriptDebugShapeType::Box);
static_assert(ShapeType::Sphere == ScriptModuleDebugUtilities::ScriptDebugShapeType::Sphere);
static_assert(ShapeType::Circle == ScriptModuleDebugUtilities::ScriptDebugShapeType::Circle);
static_assert(ShapeType::Text == ScriptModuleDebugUtilities::ScriptDebugShapeType::Text);
static_assert(ShapeType::Arrow == ScriptModuleDebugUtilities::ScriptDebugShapeType::Arrow);
static_assert(ShapeType::NumShapeTypes == ScriptModuleDebugUtilities::ScriptDebugShapeType::NumShapeTypes);

} // namespace debug_shape