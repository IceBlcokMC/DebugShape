#pragma once
#include "IDebugShape.h"

namespace debug_shape {


/**
 * 调试圈
 * @see
 * https://learn.microsoft.com/en-us/minecraft/creator/scriptapi/minecraft/debug-utilities/debugcircle?view=minecraft-bedrock-experimental
 */
class IDebugCircle : public virtual IDebugShape {
public:
    DSNDAPI static std::unique_ptr<IDebugCircle> create(Vec3 const& center);
};


} // namespace debug_shape