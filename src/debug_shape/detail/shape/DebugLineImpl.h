#pragma once
#include "DebugShapeImpl.h"
#include "debug_shape/api/shape/IDebugLine.h"


namespace debug_shape::detail {

class DebugLineImpl : public IDebugLine, public DebugShapeImpl {
public:
    explicit DebugLineImpl(Vec3 const& start, Vec3 const& end);

    Vec3 getEndPosition() const override;
    void setEndPosition(Vec3 const& loc) override;
};
static_assert(!std::is_abstract_v<DebugLineImpl>);

} // namespace debug_shape::detail
