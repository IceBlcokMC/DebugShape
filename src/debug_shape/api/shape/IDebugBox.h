#pragma once
#include "IDebugShape.h"

namespace debug_shape {

/**
 * 调试立方体
 * @see
 * https://learn.microsoft.com/en-us/minecraft/creator/scriptapi/minecraft/debug-utilities/debugbox?view=minecraft-bedrock-experimental
 */
class IDebugBox : public virtual IDebugShape {
public:
    DSNDAPI static std::unique_ptr<IDebugBox> create(Vec3 const& loc);

    virtual std::optional<Vec3> getBound() const = 0; // 获取边界

    virtual void setBound(Vec3 const& bound) = 0;
};

} // namespace debug_shape