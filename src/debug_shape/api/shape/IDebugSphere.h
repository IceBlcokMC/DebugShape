#pragma once
#include "IDebugShape.h"


namespace debug_shape {


/**
 * 调试球
 * @see
 * https://learn.microsoft.com/en-us/minecraft/creator/scriptapi/minecraft/debug-utilities/debugsphere?view=minecraft-bedrock-experimental
 */
class IDebugSphere : public virtual IDebugShape {
public:
    DSNDAPI static std::unique_ptr<IDebugSphere> create(Vec3 const& loc);

    virtual std::optional<uchar> getNumSegments() const = 0;

    virtual void setNumSegments(uchar numSegments) = 0;
};


} // namespace debug_shape