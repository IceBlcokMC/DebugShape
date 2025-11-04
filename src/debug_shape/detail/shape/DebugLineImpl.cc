#include "DebugLineImpl.h"

namespace debug_shape {

std::unique_ptr<IDebugLine> IDebugLine::create(Vec3 const& start, Vec3 const& end) {
    return std::make_unique<detail::DebugLineImpl>(start, end);
}

namespace detail {

DebugLineImpl::DebugLineImpl(Vec3 const& start, Vec3 const& end) : DebugShapeImpl(ShapeType::Line, start) {
    LineDataPayload extra{};
    extra.mEndLocation         = end;
    payload_.mExtraDataPayload = extra;
}
Vec3 DebugLineImpl::getEndPosition() const {
    return std::get<LineDataPayload>(payload_.mExtraDataPayload.get()).mEndLocation;
}
void DebugLineImpl::setEndPosition(Vec3 const& loc) {
    std::get<LineDataPayload>(payload_.mExtraDataPayload.get()).mEndLocation = loc;
}

} // namespace detail
} // namespace debug_shape