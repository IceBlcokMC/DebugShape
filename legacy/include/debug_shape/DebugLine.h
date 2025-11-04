#pragma once
#include "debug_shape/DebugShape.h"


namespace debug_shape {

/**
 * 调试线段
 * @see
 * https://learn.microsoft.com/en-us/minecraft/creator/scriptapi/minecraft/debug-utilities/debugline?view=minecraft-bedrock-experimental
 */
class DebugLine : public DebugShape {
public:
    DSNDAPI explicit DebugLine(Vec3 const& start, Vec3 const& end);

    DSNDAPI virtual std::optional<Vec3> getEndPosition() const;

    DSAPI virtual void setEndPosition(std::optional<Vec3> loc);
};

} // namespace debug_shape