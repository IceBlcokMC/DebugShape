#pragma once
#include "debug_shape/DebugShape.h"


namespace debug_shape {

/**
 * 调试立方体
 * @see
 * https://learn.microsoft.com/en-us/minecraft/creator/scriptapi/minecraft/debug-utilities/debugbox?view=minecraft-bedrock-experimental
 */
class DebugBox : public DebugShape {
public:
    DSNDAPI explicit DebugBox(Vec3 const& loc);

    DSNDAPI virtual std::optional<Vec3> getBound() const; // 获取边界

    DSAPI virtual void setBound(Vec3 const& bound);
};

} // namespace debug_shape