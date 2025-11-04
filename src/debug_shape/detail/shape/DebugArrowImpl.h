#pragma once
#include "DebugShapeImpl.h"
#include "debug_shape/api/shape/IDebugArrow.h"

namespace debug_shape ::detail {

class DebugArrowImpl : public IDebugArrow, public DebugShapeImpl {
public:
    explicit DebugArrowImpl(Vec3 const& start, Vec3 const& end);

    Vec3                   getEndPosition() const override;
    void                   setEndPosition(const Vec3& loc) override;
    std::optional<float>   getHeadLength() const override;
    void                   setHeadLength(std::optional<float> l) override;
    std::optional<float>   getHeadRadius() const override;
    void                   setHeadRadius(std::optional<float> r) override;
    std::optional<uint8_t> getHeadSegments() const override;
    void                   setHeadSegments(std::optional<uint8_t> s) override;
};
static_assert(!std::is_abstract_v<DebugArrowImpl>);

} // namespace debug_shape::detail