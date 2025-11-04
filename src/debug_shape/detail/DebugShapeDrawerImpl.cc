#include "DebugShapeDrawerImpl.h"

#include "debug_shape/ModEntry.h"
#include "shape/DebugShapeImpl.h"

#include <mc/network/packet/DebugDrawerPacket.h>
#include <mc/network/packet/ShapeDataPayload.h>
#include <mc/world/level/BlockPos.h>

namespace debug_shape {

IDebugShapeDrawer& IDebugShapeDrawer::getInstance() { return detail::DebugShapeDrawerImpl::getInstance(); }

namespace detail {

DebugShapeDrawerImpl::DebugShapeDrawerImpl()  = default;
DebugShapeDrawerImpl::~DebugShapeDrawerImpl() = default;

DebugShapeDrawerImpl& DebugShapeDrawerImpl::getInstance() {
    static DebugShapeDrawerImpl instance;
    return instance;
}

void DebugShapeDrawerImpl::drawer(std::vector<IDebugShape const*> const& shapes, Player* player) {
    DebugDrawerPacket packet{};
    packet.mPayload->mShapes->reserve(shapes.size());
    for (auto shape : shapes) {
        auto parent = dynamic_cast<DebugShapeImpl const*>(shape);
        if (!parent) {
            ModEntry::getInstance().getSelf().getLogger().error("Failed to cast shape to DebugShapeImpl");
        }
        packet.mPayload->mShapes->push_back(parent->payload_);
    }
    if (player) {
        packet.sendTo(*player);
    } else if (shapes.size() >= 1) {
        packet.sendTo(shapes[0]->getLocation().value_or(Vec3::ZERO()), shapes[0]->getDimensionId());
    }
}

void DebugShapeDrawerImpl::deleter(std::vector<IDebugShape const*> const& shapes, Player* player) {
    static auto copyEmpty = [](ShapeDataPayload const& payload) {
        ShapeDataPayload data_payload{};
        data_payload.mNetworkId = payload.mNetworkId;
        return data_payload;
    };
    DebugDrawerPacket packet{};
    packet.mPayload->mShapes->reserve(shapes.size());
    for (auto shape : shapes) {
        auto parent = dynamic_cast<DebugShapeImpl const*>(shape);
        if (!parent) {
            ModEntry::getInstance().getSelf().getLogger().error("Failed to cast shape to DebugShapeImpl");
        }
        packet.mPayload->mShapes->push_back(copyEmpty(parent->payload_));
    }
    if (player) {
        packet.sendTo(*player);
    } else if (shapes.size() >= 1) {
        packet.sendTo(shapes[0]->getLocation().value_or(Vec3::ZERO()), shapes[0]->getDimensionId());
    }
}

void DebugShapeDrawerImpl::drawShape(IDebugShape const* shape) { drawer({shape}, nullptr); }

void DebugShapeDrawerImpl::removeShape(IDebugShape const* shape) { deleter({shape}, nullptr); }

void DebugShapeDrawerImpl::drawShape(const IDebugShape* shape, Player& player) { drawer({shape}, &player); }

void DebugShapeDrawerImpl::removeShape(const IDebugShape* shape, Player& player) { deleter({shape}, &player); }

void DebugShapeDrawerImpl::drawShapes(const std::vector<IDebugShape const*>& shapes) { drawer(shapes, nullptr); }

void DebugShapeDrawerImpl::drawShapes(const std::vector<IDebugShape const*>& shapes, Player& player) {
    drawer(shapes, &player);
}

void DebugShapeDrawerImpl::removeShapes(const std::vector<IDebugShape const*>& shapes) { deleter(shapes, nullptr); }

void DebugShapeDrawerImpl::removeShapes(const std::vector<IDebugShape const*>& shapes, Player& player) {
    deleter(shapes, &player);
}

} // namespace detail

} // namespace debug_shape
