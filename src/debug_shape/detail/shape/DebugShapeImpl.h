#pragma once
#include "debug_shape/api/shape/IDebugShape.h"

#include "mc/network/packet/ShapeDataPayload.h"

namespace debug_shape::detail {

class DebugShapeImpl : public virtual IDebugShape {
protected:
    ShapeDataPayload payload_{};
    friend class DebugShapeDrawerImpl;

public:
    DS_DISABLE_COPY(DebugShapeImpl);
    explicit DebugShapeImpl(ShapeType type, Vec3 const& location);
    ~DebugShapeImpl() override;

    ShapeID                   getShapeID() const override;
    ShapeType                 getShapeType() const override;
    std::optional<Vec3>       getLocation() const override;
    void                      setLocation(const Vec3& loc) override;
    std::optional<Vec3>       getRotation() const override;
    void                      setRotation(std::optional<Vec3> rot) override;
    std::optional<float>      getScale() const override;
    void                      setScale(std::optional<float> s) override;
    std::optional<mce::Color> getColor() const override;
    void                      setColor(std::optional<mce::Color> c) override;
    bool                      hasDuration() const override;
    std::optional<float>      getTotalTimeLeft() const override;
    void                      setTotalTimeLeft(std::optional<float> t) override;
    DimensionType             getDimensionId() const override;
    void                      setDimensionId(DimensionType d) override;

    // impl IDrawer
    void draw() const override;
    void draw(Player& player) const override;
    void draw(DimensionType dimension) const override;
    void remove() const override;
    void remove(Player& player) const override;
    void remove(DimensionType dimension) const override;
    void update() const override;
    void update(Player& player) const override;
    void update(DimensionType dimension) const override;
};
static_assert(!std::is_abstract_v<DebugShapeImpl>);

} // namespace debug_shape::detail