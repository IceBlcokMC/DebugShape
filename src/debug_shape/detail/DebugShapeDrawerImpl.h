#pragma once
#include "debug_shape/api/IDebugShapeDrawer.h"
#include "debug_shape/api/shape/IDebugShape.h"

namespace debug_shape::detail {


class DebugShapeDrawerImpl final : public IDebugShapeDrawer {
public:
    DS_DISABLE_COPY_MOVE(DebugShapeDrawerImpl);

    static DebugShapeDrawerImpl& getInstance();

    DebugShapeDrawerImpl();
    ~DebugShapeDrawerImpl() override;

    void drawShape(IDebugShape const* shape) override;

    void removeShape(IDebugShape const* shape) override;
};


} // namespace debug_shape::detail