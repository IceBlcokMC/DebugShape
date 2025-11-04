#pragma once
#include "DebugShapeImpl.h"
#include "debug_shape/api/shape/IDebugBox.h"


namespace debug_shape ::detail {

class DebugBoxImpl : public IDebugBox, public DebugShapeImpl {
public:
    explicit DebugBoxImpl(Vec3 const& loc);

    std::optional<Vec3> getBound() const override;
    void                setBound(const Vec3& bound) override;
};
static_assert(!std::is_abstract_v<DebugBoxImpl>);

} // namespace debug_shape::detail
