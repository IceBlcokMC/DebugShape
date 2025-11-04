#include "debug_shape/DebugShapeDrawer.h"
#include "debug_shape/IDebugShape.h"

#include "mc/_HeaderOutputPredefine.h"
#include "mc/world/level/BlockPos.h"
#include "mc/world/level/BlockSourceListener.h"
#include "mc/world/level/dimension/Dimension.h"

#include <vector>

namespace debug_shape {

// 单个接口
void DebugShapeDrawer::drawShape(IDebugShape const* shape) {
    implDrawer({shape->serialize()}, std::nullopt, std::nullopt);
}
void DebugShapeDrawer::drawShape(IDebugShape const* shape, Player& player) {
    implDrawer({shape->serialize()}, &player, std::nullopt);
}
void DebugShapeDrawer::drawShape(IDebugShape const* shape, DimensionType dimension) {
    implDrawer({shape->serialize()}, std::nullopt, dimension);
}

void DebugShapeDrawer::removeShape(IDebugShape const* shape) {
    implDrawer({cloneNewEmptyShapeDataPacket(shape->serialize())}, std::nullopt, std::nullopt);
}
void DebugShapeDrawer::removeShape(IDebugShape const* shape, Player& player) {
    implDrawer({cloneNewEmptyShapeDataPacket(shape->serialize())}, &player, std::nullopt);
}
void DebugShapeDrawer::removeShape(IDebugShape const* shape, DimensionType dimension) {
    implDrawer({cloneNewEmptyShapeDataPacket(shape->serialize())}, std::nullopt, dimension);
}


// 批量接口
void DebugShapeDrawer::drawShapes(std::vector<IDebugShape const*> const& shapes) {
    std::vector<ShapeDataPacket> datas{};
    cloneShapeDataPacket(shapes, datas);
    implDrawer(datas, std::nullopt, std::nullopt);
}
void DebugShapeDrawer::drawShapes(std::vector<IDebugShape const*> const& shapes, Player& player) {
    std::vector<ShapeDataPacket> datas{};
    cloneShapeDataPacket(shapes, datas);
    implDrawer(datas, &player, std::nullopt);
}
void DebugShapeDrawer::drawShapes(std::vector<IDebugShape const*> const& shapes, DimensionType dimension) {
    std::vector<ShapeDataPacket> datas{};
    cloneShapeDataPacket(shapes, datas);
    implDrawer(datas, std::nullopt, dimension);
}

void DebugShapeDrawer::removeShapes(std::vector<IDebugShape const*> const& shapes) {
    std::vector<ShapeDataPacket> datas{};
    cloneShapeDataPacket(shapes, datas);
    implDrawer(datas, std::nullopt, std::nullopt);
}
void DebugShapeDrawer::removeShapes(std::vector<IDebugShape const*> const& shapes, Player& player) {
    std::vector<ShapeDataPacket> datas{};
    cloneShapeDataPacket(shapes, datas, [](IDebugShape const* shape) {
        return cloneNewEmptyShapeDataPacket(shape->serialize());
    });
    implDrawer(datas, &player, std::nullopt);
}
void DebugShapeDrawer::removeShapes(std::vector<IDebugShape const*> const& shapes, DimensionType dimension) {
    std::vector<ShapeDataPacket> datas{};
    cloneShapeDataPacket(shapes, datas, [](IDebugShape const* shape) {
        return cloneNewEmptyShapeDataPacket(shape->serialize());
    });
    implDrawer(datas, std::nullopt, dimension);
}


// private

void DebugShapeDrawer::implDrawer(
    std::vector<ShapeDataPacket> const& shapes,
    std::optional<Player*>              player,
    std::optional<DimensionType>        dimension
) {
    ShapeDrawerPacket packet;
    packet.mShapes->reserve(shapes.size());
    for (const auto& shape : shapes) {
        packet.mShapes->push_back(shape);
    }

    if (player) {
        packet.sendTo(**player);
    } else if (dimension) {
        auto loc = shapes[0].mLocation->value_or(BlockPos{});
        packet.sendTo(loc, *dimension);
    } else {
        packet.sendToClients();
    }
}

ShapeDataPacket DebugShapeDrawer::cloneNewEmptyShapeDataPacket(ShapeDataPacket const& shape) {
    ShapeDataPacket data{};
    data.mNetworkId = shape.mNetworkId;
    return data;
}

void DebugShapeDrawer::cloneShapeDataPacket(
    std::vector<IDebugShape const*> const& shapes,
    std::vector<ShapeDataPacket>&          result,
    CloneHandler                           handler
) {
    result.clear();
    result.reserve(shapes.size());
    for (const auto& shape : shapes) {
        result.push_back(handler(shape));
    }
}

DebugShapeDrawer::CloneHandler const DebugShapeDrawer::DefaultCloneHandler = [](IDebugShape const* shape) {
    return shape->serialize();
};


} // namespace debug_shape