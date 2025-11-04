#include "debug_shape/IDebugShape.h"
#include "debug_shape/DebugShapeDrawer.h"
#include "debug_shape/internal/GlobalIDAllocator.h"

#include "mc/_HeaderOutputPredefine.h"
#include "mc/world/level/dimension/Dimension.h"

namespace debug_shape {


// IDrawerInterface

void IDrawerInterface::update() const {
    remove();
    draw();
}
void IDrawerInterface::update(Player& player) const {
    remove(player);
    draw(player);
}
void IDrawerInterface::update(DimensionType dimension) const {
    remove(dimension);
    draw(dimension);
}


// IDebugShape

IDebugShape::IDebugShape() { mShapeData.mNetworkId = internal::GlobalIDAllocator::allocateID(); }

IDebugShape::~IDebugShape() { remove(); }

ShapeDataPacket const& IDebugShape::serialize() const { return mShapeData; }

void IDebugShape::draw() const { DebugShapeDrawer::drawShape(this); }
void IDebugShape::draw(Player& player) const { DebugShapeDrawer::drawShape(this, player); }
void IDebugShape::draw(DimensionType dimension) const { DebugShapeDrawer::drawShape(this, dimension); }

void IDebugShape::remove() const { DebugShapeDrawer::removeShape(this); }
void IDebugShape::remove(Player& player) const { DebugShapeDrawer::removeShape(this, player); }
void IDebugShape::remove(DimensionType dimension) const { DebugShapeDrawer::removeShape(this, dimension); }

} // namespace debug_shape