#pragma once
#include "shape/IDebugShape.h"


namespace debug_shape {


class IDebugShapeDrawer {
public:
    DSNDAPI static IDebugShapeDrawer& getInstance();

    virtual ~IDebugShapeDrawer() = default;

    // 单个绘制
    virtual void drawShape(IDebugShape const& shape)                    = 0;
    virtual void drawShape(IDebugShape const& shape, Player& player)    = 0;
    virtual void drawShape(IDebugShape const& shape, DimensionType dim) = 0;

    // 批量绘制
    virtual void drawShapes(std::vector<IDebugShape const*> const& shapes)                    = 0;
    virtual void drawShapes(std::vector<IDebugShape const*> const& shapes, Player& player)    = 0;
    virtual void drawShapes(std::vector<IDebugShape const*> const& shapes, DimensionType dim) = 0;

    // 单个删除
    virtual void removeShape(IDebugShape const& shape)                    = 0;
    virtual void removeShape(IDebugShape const& shape, Player& player)    = 0;
    virtual void removeShape(IDebugShape const& shape, DimensionType dim) = 0;

    // 批量删除
    virtual void removeShapes(std::vector<IDebugShape const*> const& shapes)                    = 0;
    virtual void removeShapes(std::vector<IDebugShape const*> const& shapes, Player& player)    = 0;
    virtual void removeShapes(std::vector<IDebugShape const*> const& shapes, DimensionType dim) = 0;
};


} // namespace debug_shape