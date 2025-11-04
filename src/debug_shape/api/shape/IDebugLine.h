#pragma once
#include "IDebugShape.h"


namespace debug_shape {


/**
 * 调试线段
 * @see
 * https://learn.microsoft.com/en-us/minecraft/creator/scriptapi/minecraft/debug-utilities/debugline?view=minecraft-bedrock-experimental
 */
class IDebugLine : public virtual IDebugShape {
public:
    DSNDAPI static std::unique_ptr<IDebugLine> create(Vec3 const& start, Vec3 const& end);

    virtual Vec3 getEndPosition() const = 0;

    virtual void setEndPosition(Vec3 const& loc) = 0;
};


} // namespace debug_shape