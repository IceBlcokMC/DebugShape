#pragma once
#include "IDebugShape.h"

namespace debug_shape {

/**
 * 调试箭头
 * @see
 * https://learn.microsoft.com/en-us/minecraft/creator/scriptapi/minecraft/debug-utilities/debugarrow?view=minecraft-bedrock-experimental
 */
class IDebugArrow : public virtual IDebugShape {
public:
    DSNDAPI static std::unique_ptr<IDebugArrow> create(Vec3 const& start, Vec3 const& end);

    virtual Vec3 getEndPosition() const = 0; // 箭头末端位置

    virtual void setEndPosition(Vec3 const& loc) = 0;

    virtual std::optional<float> getHeadLength() const = 0; // 箭头长度

    virtual void setHeadLength(std::optional<float> l) = 0;

    virtual std::optional<float> getHeadRadius() const = 0; // 箭头半径

    virtual void setHeadRadius(std::optional<float> r) = 0;

    virtual std::optional<uint8_t> getHeadSegments() const = 0; // 箭头分段数

    virtual void setHeadSegments(std::optional<uint8_t> s) = 0;
};

} // namespace debug_shape
