#pragma once
#include "IDebugShape.h"

namespace debug_shape {


/**
 * 调试文本
 * @see
 * https://learn.microsoft.com/en-us/minecraft/creator/scriptapi/minecraft/debug-utilities/debugtext?view=minecraft-bedrock-experimental
 */
class IDebugText : public virtual IDebugShape {
public:
    DSNDAPI static std::unique_ptr<IDebugText> create(Vec3 const& loc, std::string const& text);

    virtual std::string getText() const = 0;

    virtual void setText(std::string const& txt) = 0;
};


} // namespace debug_shape