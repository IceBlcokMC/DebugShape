#include "DebugArrowImpl.h"

namespace debug_shape {

std::unique_ptr<IDebugArrow> IDebugArrow::create(Vec3 const& start, Vec3 const& end) {
    return std::make_unique<detail::DebugArrowImpl>(start, end);
}

namespace detail {

DebugArrowImpl::DebugArrowImpl(Vec3 const& start, Vec3 const& end) : DebugShapeImpl(ShapeType::Arrow, start) {
    ArrowDataPayload extra{};
    extra.mEndLocation         = end;
    payload_.mExtraDataPayload = std::move(extra);
}
Vec3 DebugArrowImpl::getEndPosition() const {
    return std::get<ArrowDataPayload>(payload_.mExtraDataPayload.get()).mEndLocation->value();
}
void DebugArrowImpl::setEndPosition(const Vec3& loc) {
    std::get<ArrowDataPayload>(payload_.mExtraDataPayload.get()).mEndLocation = loc;
}
std::optional<float> DebugArrowImpl::getHeadLength() const {
    return std::get<ArrowDataPayload>(payload_.mExtraDataPayload.get()).mArrowHeadLength;
}
void DebugArrowImpl::setHeadLength(std::optional<float> l) {
    std::get<ArrowDataPayload>(payload_.mExtraDataPayload.get()).mArrowHeadLength = l;
}
std::optional<float> DebugArrowImpl::getHeadRadius() const {
    return std::get<ArrowDataPayload>(payload_.mExtraDataPayload.get()).mArrowHeadRadius;
}
void DebugArrowImpl::setHeadRadius(std::optional<float> r) {
    std::get<ArrowDataPayload>(payload_.mExtraDataPayload.get()).mArrowHeadRadius = r;
}
std::optional<uint8_t> DebugArrowImpl::getHeadSegments() const {
    return std::get<ArrowDataPayload>(payload_.mExtraDataPayload.get()).mNumSegments;
}
void DebugArrowImpl::setHeadSegments(std::optional<uint8_t> s) {
    std::get<ArrowDataPayload>(payload_.mExtraDataPayload.get()).mNumSegments = s;
}

} // namespace detail
} // namespace debug_shape