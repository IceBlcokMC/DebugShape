#pragma once
#include "DebugShapeImpl.h"
#include "debug_shape/api/shape/IDebugText.h"

namespace debug_shape ::detail {

class DebugTextImpl : public IDebugText, public DebugShapeImpl {
public:
    explicit DebugTextImpl(Vec3 const& loc, std::string const& text);

    std::string getText() const override;

    void setText(const std::string& txt) override;
};
static_assert(!std::is_abstract_v<DebugTextImpl>);

} // namespace debug_shape::detail
