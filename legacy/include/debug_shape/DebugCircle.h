#pragma once
#include "debug_shape/DebugShape.h"


namespace debug_shape {

/**
 * 调试圈
 * @see
 * https://learn.microsoft.com/en-us/minecraft/creator/scriptapi/minecraft/debug-utilities/debugcircle?view=minecraft-bedrock-experimental
 */
class DebugCircle : public DebugShape {
public:
    DSNDAPI explicit DebugCircle(Vec3 const& center);
};

} // namespace debug_shape