#pragma once
#include "debug_shape/DebugShape.h"


namespace debug_shape {

/**
 * 调试文本
 * @see
 * https://learn.microsoft.com/en-us/minecraft/creator/scriptapi/minecraft/debug-utilities/debugtext?view=minecraft-bedrock-experimental
 */
class DebugText : public DebugShape {
public:
    DSNDAPI explicit DebugText(Vec3 const& loc, const std::string& text);

    DSNDAPI virtual std::optional<std::string> getText() const;

    DSAPI virtual void setText(std::string const& txt);
};

} // namespace debug_shape