#pragma once
#include "debug_shape/IDebugShape.h"
#include "debug_shape/Macro.h"
#include <optional>

#include "mc/deps/core/math/Color.h"
#include "mc/deps/core/math/Vec3.h"


namespace debug_shape {


/**
 * 调试形状
 * @see
 * https://learn.microsoft.com/en-us/minecraft/creator/scriptapi/minecraft/debug-utilities/debugshape?view=minecraft-bedrock-experimental
 */
class DebugShape : public IDebugShape {
public:
    DSNDAPI explicit DebugShape(DebugShapeType type, Vec3 const& loc);

    DSNDAPI virtual ShapeID getId() const final; // 唯一id

    DSNDAPI virtual DebugShapeType getType() const final; // 形状类型

    DSNDAPI virtual std::optional<Vec3> getPosition() const; // 位置

    DSAPI virtual void setPosition(Vec3 const& loc);

    DSNDAPI virtual std::optional<Vec3> getRotation() const; // 旋转

    DSAPI virtual void setRotation(std::optional<Vec3> rot);

    DSNDAPI virtual std::optional<float> getScale() const; // 缩放

    DSAPI virtual void setScale(std::optional<float> s);

    DSNDAPI virtual std::optional<mce::Color> getColor() const; // 颜色

    DSAPI virtual void setColor(std::optional<mce::Color> c);


    DSNDAPI virtual bool hasDuration() const; // 是否有持续时间

    DSNDAPI virtual std::optional<float> getTotalTimeLeft() const; // 剩余时间

    DSAPI virtual void setTotalTimeLeft(std::optional<float> t);
};


} // namespace debug_shape
