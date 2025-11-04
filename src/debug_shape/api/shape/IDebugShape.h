#pragma once
#include "IDrawer.h"
#include "ShapeID.h"
#include "ShapeType.h"
#include "debug_shape/api/Macro.h"

#include <mc/deps/core/math/Color.h>
#include <mc/deps/core/math/Vec3.h>
#include <memory>


namespace debug_shape {


/**
 * 调试形状
 * @see
 * https://learn.microsoft.com/en-us/minecraft/creator/scriptapi/minecraft/debug-utilities/debugshape?view=minecraft-bedrock-experimental
 */
class IDebugShape : public virtual IDrawer {
public:
    virtual ShapeID getShapeID() const = 0;

    virtual ShapeType getShapeType() const = 0;

    virtual std::optional<Vec3> getLocation() const = 0; // 位置

    virtual void setLocation(Vec3 const& loc) = 0;

    virtual std::optional<Vec3> getRotation() const = 0; // 旋转

    virtual void setRotation(std::optional<Vec3> rot) = 0;

    virtual std::optional<float> getScale() const = 0; // 缩放

    virtual void setScale(std::optional<float> s) = 0;

    virtual std::optional<mce::Color> getColor() const = 0; // 颜色

    virtual void setColor(std::optional<mce::Color> c) = 0;

    virtual bool hasDuration() const = 0; // 是否有持续时间

    virtual std::optional<float> getTotalTimeLeft() const = 0; // 剩余时间(s)

    virtual void setTotalTimeLeft(std::optional<float> t) = 0;

    // v1.21.120
    virtual DimensionType getDimensionId() const = 0;

    virtual void setDimensionId(DimensionType d) = 0;
};


} // namespace debug_shape