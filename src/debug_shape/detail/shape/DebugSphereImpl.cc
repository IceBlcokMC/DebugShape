#include "DebugSphereImpl.h"

namespace debug_shape {

std::unique_ptr<IDebugSphere> IDebugSphere::create(Vec3 const& loc) {
    return std::make_unique<detail::DebugSphereImpl>(ShapeType::Sphere, loc);
}

std::optional<uchar> detail::DebugSphereImpl::getNumSegments() const {
    if (std::holds_alternative<cereal::NullType>(payload_.mExtraDataPayload.get())) {
        return std::nullopt;
    }
    return std::get<SphereDataPayload>(payload_.mExtraDataPayload.get()).mNumSegments;
}

void detail::DebugSphereImpl::setNumSegments(uchar numSegments) {
    if (std::holds_alternative<cereal::NullType>(payload_.mExtraDataPayload.get())) {
        payload_.mExtraDataPayload = SphereDataPayload{numSegments};
    } else {
        std::get<SphereDataPayload>(payload_.mExtraDataPayload.get()).mNumSegments = numSegments;
    }
}

} // namespace debug_shape
