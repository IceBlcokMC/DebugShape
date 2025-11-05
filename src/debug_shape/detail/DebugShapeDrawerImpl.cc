#include "DebugShapeDrawerImpl.h"

#include "mc/_HeaderOutputPredefine.h"
#include "mc/deps/core/math/Vec3.h"
#include "shape/DebugShapeImpl.h"

#include <functional>
#include <mc/network/packet/DebugDrawerPacket.h>
#include <mc/network/packet/ShapeDataPayload.h>
#include <mc/world/level/BlockPos.h>
#include <optional>
#include <vector>

namespace debug_shape {

IDebugShapeDrawer& IDebugShapeDrawer::getInstance() { return detail::DebugShapeDrawerImpl::getInstance(); }

namespace detail {

void drawer(
    std::function<std::vector<ShapeDataPayload>()> const& provider,
    Player*                                               player,
    std::optional<DimensionType>                          dimension
) {
    auto payloads = provider();
    if (payloads.empty()) {
        return;
    }

    DebugDrawerPacket packet{};
    packet.setSerializationMode(SerializationMode::CerealOnly);

    auto& shapes = packet.mPayload->mShapes.get();
    shapes.reserve(payloads.size());
    shapes = std::move(payloads);

    if (player) {
        packet.sendTo(*player);
    } else if (dimension) {
        packet.sendTo(shapes[0].mLocation->value_or(Vec3::ZERO()), *dimension);
    } else {
        packet.sendToClients();
    }
}

ShapeDataPayload emptyCloneWithId(ShapeDataPayload const& src) {
    ShapeDataPayload payload{};
    payload.mNetworkId = src.mNetworkId;
    return payload;
}

DebugShapeDrawerImpl::DebugShapeDrawerImpl()  = default;
DebugShapeDrawerImpl::~DebugShapeDrawerImpl() = default;

DebugShapeDrawerImpl& DebugShapeDrawerImpl::getInstance() {
    static DebugShapeDrawerImpl instance;
    return instance;
}

void DebugShapeDrawerImpl::processShapes(
    std::vector<IDebugShape const*> const& shapes,
    Player*                                player,
    std::optional<DimensionType>           dim,
    bool                                   remove
) {
    drawer(
        [&]() {
            std::vector<ShapeDataPayload> payloads;
            payloads.reserve(shapes.size());
            for (auto const* shape : shapes) {
                if (auto* parent = dynamic_cast<DebugShapeImpl const*>(shape)) {
                    payloads.push_back(remove ? emptyCloneWithId(parent->getPayload()) : parent->getPayload());
                }
            }
            return payloads;
        },
        player,
        dim
    );
}


void DebugShapeDrawerImpl::drawShape(IDebugShape const& shape) { drawShapes({&shape}); }
void DebugShapeDrawerImpl::drawShape(IDebugShape const& shape, Player& player) { drawShapes({&shape}, player); }
void DebugShapeDrawerImpl::drawShape(IDebugShape const& shape, DimensionType dim) { drawShapes({&shape}, dim); }

void DebugShapeDrawerImpl::drawShapes(std::vector<IDebugShape const*> const& shapes) {
    processShapes(shapes, nullptr, std::nullopt, false);
}
void DebugShapeDrawerImpl::drawShapes(std::vector<IDebugShape const*> const& shapes, Player& player) {
    processShapes(shapes, &player, std::nullopt, false);
}
void DebugShapeDrawerImpl::drawShapes(std::vector<IDebugShape const*> const& shapes, DimensionType dim) {
    processShapes(shapes, nullptr, dim, false);
}

void DebugShapeDrawerImpl::removeShape(IDebugShape const& shape) { removeShapes({&shape}); }
void DebugShapeDrawerImpl::removeShape(IDebugShape const& shape, Player& player) { removeShapes({&shape}, player); }
void DebugShapeDrawerImpl::removeShape(IDebugShape const& shape, DimensionType dim) { removeShapes({&shape}, dim); }

void DebugShapeDrawerImpl::removeShapes(std::vector<IDebugShape const*> const& shapes) {
    processShapes(shapes, nullptr, std::nullopt, true);
}
void DebugShapeDrawerImpl::removeShapes(std::vector<IDebugShape const*> const& shapes, Player& player) {
    processShapes(shapes, &player, std::nullopt, true);
}
void DebugShapeDrawerImpl::removeShapes(std::vector<IDebugShape const*> const& shapes, DimensionType dim) {
    processShapes(shapes, nullptr, dim, true);
}


} // namespace detail

} // namespace debug_shape
