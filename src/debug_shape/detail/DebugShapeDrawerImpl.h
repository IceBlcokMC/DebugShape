#pragma once
#include "debug_shape/api/IDebugShapeDrawer.h"
#include "debug_shape/api/shape/IDebugShape.h"

namespace debug_shape::detail {


class DebugShapeDrawerImpl final : public IDebugShapeDrawer {
    void processShapes(
        std::vector<IDebugShape const*> const& shapes,
        Player*                                player,
        std::optional<DimensionType>           dim,
        bool                                   remove
    );

public:
    DS_DISABLE_COPY_MOVE(DebugShapeDrawerImpl);

    static DebugShapeDrawerImpl& getInstance();

    DebugShapeDrawerImpl();
    ~DebugShapeDrawerImpl() override;

    // 单个绘制
    void drawShape(IDebugShape const& shape) override;
    void drawShape(IDebugShape const& shape, Player& player) override;
    void drawShape(IDebugShape const& shape, DimensionType dim) override;

    // 批量绘制
    void drawShapes(std::vector<IDebugShape const*> const& shapes) override;
    void drawShapes(std::vector<IDebugShape const*> const& shapes, Player& player) override;
    void drawShapes(std::vector<IDebugShape const*> const& shapes, DimensionType dim) override;

    // 单个删除
    void removeShape(IDebugShape const& shape) override;
    void removeShape(IDebugShape const& shape, Player& player) override;
    void removeShape(IDebugShape const& shape, DimensionType dim) override;

    // 批量删除
    void removeShapes(std::vector<IDebugShape const*> const& shapes) override;
    void removeShapes(std::vector<IDebugShape const*> const& shapes, Player& player) override;
    void removeShapes(std::vector<IDebugShape const*> const& shapes, DimensionType dim) override;
};


} // namespace debug_shape::detail