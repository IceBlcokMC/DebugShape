#pragma once
#include "DebugShapeImpl.h"
#include "debug_shape/api/shape/IDebugSphere.h"


namespace debug_shape ::detail {

class DebugSphereImpl : public IDebugSphere, public DebugShapeImpl {
public:
    using DebugShapeImpl::DebugShapeImpl;

    std::optional<uchar> getNumSegments() const override;
    void                 setNumSegments(uchar numSegments) override;
};
static_assert(!std::is_abstract_v<DebugSphereImpl>);

} // namespace debug_shape::detail
