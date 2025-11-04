#pragma once
#include "debug_shape/DebugLine.h"

namespace debug_shape {

/**
 * 调试箭头
 * @see
 * https://learn.microsoft.com/en-us/minecraft/creator/scriptapi/minecraft/debug-utilities/debugarrow?view=minecraft-bedrock-experimental
 */
class DebugArrow : public DebugLine {
public:
    DSNDAPI explicit DebugArrow(Vec3 const& start, Vec3 const& end);

    DSNDAPI virtual std::optional<float> getHeadLength() const; // 箭头长度

    DSAPI virtual void setHeadLength(std::optional<float> l);

    DSNDAPI virtual std::optional<float> getHeadRadius() const; // 箭头半径

    DSAPI virtual void setHeadRadius(std::optional<float> r);

    DSNDAPI virtual std::optional<uint8_t> getHeadSegments() const; // 箭头分段数

    DSAPI virtual void setHeadSegments(std::optional<uint8_t> s);
};

} // namespace debug_shape