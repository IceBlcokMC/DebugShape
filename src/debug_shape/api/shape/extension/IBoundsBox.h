#pragma once
#include "debug_shape/api/Macro.h"
#include "debug_shape/api/shape/IDrawer.h"

#include <mc/deps/core/math/Color.h>
#include <mc/world/phys/AABB.h>

namespace debug_shape::extension {

class IBoundsBox : public IDrawer {
public:
    DSNDAPI std::unique_ptr<IBoundsBox> create(AABB const& bounds, mce::Color const& color = mce::Color::WHITE());

    virtual void setBounds(AABB const& bounds) = 0;

    virtual std::optional<Vec3> getRotation() const = 0; // 旋转

    virtual void setRotation(std::optional<Vec3> rot) = 0;

    virtual std::optional<mce::Color> getColor() const = 0; // 颜色

    virtual void setColor(std::optional<mce::Color> c) = 0;

    virtual bool hasDuration() const = 0; // 是否有持续时间

    virtual std::optional<float> getTotalTimeLeft() const = 0; // 剩余时间(s)

    virtual void setTotalTimeLeft(std::optional<float> t) = 0;

    // v1.21.120
    virtual DimensionType getDimensionId() const = 0;

    virtual void setDimensionId(DimensionType d) = 0;
};

} // namespace debug_shape::extension