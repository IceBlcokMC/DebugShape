#pragma once
#include "debug_shape/api/shape/extension/IBoundsBox.h"

namespace debug_shape ::detail ::extension {

class BoundsBoxImpl : public debug_shape::extension::IBoundsBox {
    struct Impl;
    std::unique_ptr<Impl> impl_;

public:
    explicit BoundsBoxImpl(AABB const& bounds, mce::Color const& color = mce::Color::WHITE());
    ~BoundsBoxImpl() override;

    void                      draw() const override;
    void                      draw(Player& player) const override;
    void                      draw(DimensionType dimension) const override;
    void                      remove() const override;
    void                      remove(Player& player) const override;
    void                      remove(DimensionType dimension) const override;
    void                      update() const override;
    void                      update(Player& player) const override;
    void                      update(DimensionType dimension) const override;
    void                      setBounds(const AABB& bounds) override;
    std::optional<Vec3>       getRotation() const override;
    void                      setRotation(std::optional<Vec3> rot) override;
    std::optional<mce::Color> getColor() const override;
    void                      setColor(std::optional<mce::Color> c) override;
    bool                      hasDuration() const override;
    std::optional<float>      getTotalTimeLeft() const override;
    void                      setTotalTimeLeft(std::optional<float> t) override;
    DimensionType             getDimensionId() const override;
    void                      setDimensionId(DimensionType d) override;
};

} // namespace debug_shape::detail::extension
