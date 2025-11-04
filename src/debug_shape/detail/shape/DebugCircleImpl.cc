#include "DebugCircleImpl.h"

namespace debug_shape {

std::unique_ptr<IDebugCircle> IDebugCircle::create(Vec3 const& center) {
    return std::make_unique<detail::DebugCircleImpl>(ShapeType::Circle, center);
}

} // namespace debug_shape