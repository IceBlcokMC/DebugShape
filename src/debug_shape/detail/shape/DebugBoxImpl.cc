#include "DebugBoxImpl.h"

namespace debug_shape {

std::unique_ptr<IDebugBox> IDebugBox::create(Vec3 const& loc) {
    return std::make_unique<detail::DebugBoxImpl>(loc);
}

namespace detail {

DebugBoxImpl::DebugBoxImpl(Vec3 const& loc) : DebugShapeImpl(ShapeType::Box, loc) {}

std::optional<Vec3> DebugBoxImpl::getBound() const {
    if (std::holds_alternative<cereal::NullType>(payload_.mExtraDataPayload.get())) {
        return std::nullopt;
    }
    return std::get<BoxDataPayload>(payload_.mExtraDataPayload.get()).mBoxBound;
}

void DebugBoxImpl::setBound(const Vec3& bound) {
    if (std::holds_alternative<cereal::NullType>(payload_.mExtraDataPayload.get())) {
        payload_.mExtraDataPayload = BoxDataPayload{bound};
    } else {
        std::get<BoxDataPayload>(payload_.mExtraDataPayload.get()).mBoxBound = bound;
    }
}


} // namespace detail

} // namespace debug_shape