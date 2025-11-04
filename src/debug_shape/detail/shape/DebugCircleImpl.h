#pragma once
#include "DebugShapeImpl.h"
#include "debug_shape/api/shape/IDebugCircle.h"

namespace debug_shape ::detail {

class DebugCircleImpl : public IDebugCircle, public DebugShapeImpl {
public:
    using DebugShapeImpl::DebugShapeImpl;
};
static_assert(!std::is_abstract_v<DebugCircleImpl>);

} // namespace debug_shape::detail
