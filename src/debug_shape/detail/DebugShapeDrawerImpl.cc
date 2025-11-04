#include "DebugShapeDrawerImpl.h"


namespace debug_shape {

IDebugShapeDrawer& IDebugShapeDrawer::getInstance() { return detail::DebugShapeDrawerImpl::getInstance(); }

namespace detail {

DebugShapeDrawerImpl::DebugShapeDrawerImpl()  = default;
DebugShapeDrawerImpl::~DebugShapeDrawerImpl() = default;

DebugShapeDrawerImpl& DebugShapeDrawerImpl::getInstance() {
    static DebugShapeDrawerImpl instance;
    return instance;
}

void DebugShapeDrawerImpl::drawShape(IDebugShape const* shape) {}

void DebugShapeDrawerImpl::removeShape(IDebugShape const* shape) {}

} // namespace detail

} // namespace debug_shape
