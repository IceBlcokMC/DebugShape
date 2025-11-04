#pragma once
#include "debug_shape/IDebugShape.h"
#include "debug_shape/Macro.h"

#include "mc/_HeaderOutputPredefine.h"
#include "mc/network/packet/DebugDrawerPacket.h"

#include <vector>

class Player;

namespace debug_shape {

using ShapeDrawerPacket = ::DebugDrawerPacket;

class DebugShapeDrawer {
    static void implDrawer(
        std::vector<ShapeDataPacket> const& shapes,
        std::optional<Player*>              player,
        std::optional<DimensionType>        dimension
    );
    static ShapeDataPacket cloneNewEmptyShapeDataPacket(ShapeDataPacket const& shape);

    using CloneHandler = ShapeDataPacket (*)(IDebugShape const* shape);
    static void cloneShapeDataPacket(
        std::vector<IDebugShape const*> const& shapes,
        std::vector<ShapeDataPacket>&          result,
        CloneHandler                           handler = DefaultCloneHandler
    );
    static CloneHandler const DefaultCloneHandler;


public:
    DebugShapeDrawer() = delete;

    DSAPI static void drawShape(IDebugShape const* shape);                          // All clients
    DSAPI static void drawShape(IDebugShape const* shape, Player& player);          // Specific player
    DSAPI static void drawShape(IDebugShape const* shape, DimensionType dimension); // Specific dimension

    DSAPI static void removeShape(IDebugShape const* shape);
    DSAPI static void removeShape(IDebugShape const* shape, Player& player);
    DSAPI static void removeShape(IDebugShape const* shape, DimensionType dimension);

    DSAPI static void drawShapes(std::vector<IDebugShape const*> const& shapes);
    DSAPI static void drawShapes(std::vector<IDebugShape const*> const& shapes, Player& player);
    DSAPI static void drawShapes(std::vector<IDebugShape const*> const& shapes, DimensionType dimension);

    DSAPI static void removeShapes(std::vector<IDebugShape const*> const& shapes);
    DSAPI static void removeShapes(std::vector<IDebugShape const*> const& shapes, Player& player);
    DSAPI static void removeShapes(std::vector<IDebugShape const*> const& shapes, DimensionType dimension);
};


} // namespace debug_shape