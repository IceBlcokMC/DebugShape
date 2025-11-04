#pragma once
#include "debug_shape/DebugLine.h"
#include "debug_shape/IDebugShape.h"
#include "debug_shape/Macro.h"

#include "mc/deps/core/math/Color.h"
#include "mc/deps/core/math/Vec3.h"
#include "mc/world/phys/AABB.h"

#include <array>
#include <memory>
#include <utility>

namespace debug_shape::extension {


class BoundsBox : public IDrawerInterface {
    static inline constexpr int                      BoxLines = 12;
    std::array<std::unique_ptr<DebugLine>, BoxLines> mLines{}; // 12 lines for a box

    void refreshLines(AABB const& bounds);

    std::vector<std::pair<Vec3, Vec3>> getEdges(AABB const& bounds) const;

    std::vector<IDebugShape const*> toArray() const;

public:
    DSNDAPI explicit BoundsBox(AABB const& bounds, mce::Color const& color = mce::Color::WHITE());
    DSAPI ~BoundsBox() override;

    DSAPI void draw() const override;
    DSAPI void draw(Player& player) const override;
    DSAPI void draw(DimensionType dimension) const override;
    DSAPI void remove() const override;
    DSAPI void remove(Player& player) const override;
    DSAPI void remove(DimensionType dimension) const override;

    DSAPI void setBounds(AABB const& bounds);

    // api
    DSNDAPI virtual std::optional<Vec3> getRotation() const; // 旋转

    DSAPI virtual void setRotation(std::optional<Vec3> rot);

    DSNDAPI virtual std::optional<mce::Color> getColor() const; // 颜色

    DSAPI virtual void setColor(std::optional<mce::Color> c);

    DSNDAPI virtual bool hasDuration() const; // 是否有持续时间

    DSNDAPI virtual std::optional<float> getTotalTimeLeft() const; // 剩余时间

    DSAPI virtual void setTotalTimeLeft(std::optional<float> t);
};


} // namespace debug_shape::extension