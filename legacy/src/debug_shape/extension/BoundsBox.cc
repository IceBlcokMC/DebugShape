#include "debug_shape/extension/BoundsBox.h"
#include "debug_shape/DebugLine.h"
#include "debug_shape/DebugShapeDrawer.h"
#include "debug_shape/IDebugShape.h"

#include "mc/world/level/dimension/Dimension.h"
#include "mc/world/phys/AABB.h"

#include <cassert>
#include <memory>

namespace debug_shape::extension {


BoundsBox::BoundsBox(AABB const& bounds, mce::Color const& color) {
    refreshLines(bounds);
    setColor(color);
}

BoundsBox::~BoundsBox() { DebugShapeDrawer::removeShapes(toArray()); }

void BoundsBox::draw() const { DebugShapeDrawer::drawShapes(toArray()); }

void BoundsBox::draw(Player& player) const { DebugShapeDrawer::drawShapes(toArray(), player); }

void BoundsBox::draw(DimensionType dimension) const { DebugShapeDrawer::drawShapes(toArray(), dimension); }

void BoundsBox::remove() const { DebugShapeDrawer::removeShapes(toArray()); }

void BoundsBox::remove(Player& player) const { DebugShapeDrawer::removeShapes(toArray(), player); }

void BoundsBox::remove(DimensionType dimension) const { DebugShapeDrawer::removeShapes(toArray(), dimension); }

void BoundsBox::setBounds(AABB const& bounds) { refreshLines(bounds); }

// api
std::optional<Vec3> BoundsBox::getRotation() const { return mLines[0]->getRotation(); }

void BoundsBox::setRotation(std::optional<Vec3> rot) {
    for (auto& line : mLines) {
        line->setRotation(rot);
    }
}

std::optional<mce::Color> BoundsBox::getColor() const { return mLines[0]->getColor(); }

void BoundsBox::setColor(std::optional<mce::Color> c) {
    for (auto& line : mLines) {
        line->setColor(c);
    }
}

bool BoundsBox::hasDuration() const { return mLines[0]->hasDuration(); }

std::optional<float> BoundsBox::getTotalTimeLeft() const { return mLines[0]->getTotalTimeLeft(); }

void BoundsBox::setTotalTimeLeft(std::optional<float> t) {
    for (auto& line : mLines) {
        line->setTotalTimeLeft(t);
    }
}


// private：
std::vector<std::pair<Vec3, Vec3>> BoundsBox::getEdges(AABB const& bounds) const {
    return {
        // bottom
        {bounds.min,                                 {bounds.min.x, bounds.min.y, bounds.max.z}},
        {{bounds.max.x, bounds.min.y, bounds.min.z}, {bounds.max.x, bounds.min.y, bounds.max.z}},
        {{bounds.min.x, bounds.max.y, bounds.min.z}, {bounds.min.x, bounds.max.y, bounds.max.z}},
        {{bounds.max.x, bounds.max.y, bounds.min.z}, bounds.max                                },
        // top
        {bounds.min,                                 {bounds.max.x, bounds.min.y, bounds.min.z}},
        {{bounds.min.x, bounds.max.y, bounds.min.z}, {bounds.max.x, bounds.max.y, bounds.min.z}},
        {{bounds.min.x, bounds.min.y, bounds.max.z}, {bounds.max.x, bounds.min.y, bounds.max.z}},
        {{bounds.min.x, bounds.max.y, bounds.max.z}, bounds.max                                },
        // side
        {bounds.min,                                 {bounds.min.x, bounds.max.y, bounds.min.z}},
        {{bounds.max.x, bounds.min.y, bounds.min.z}, {bounds.max.x, bounds.max.y, bounds.min.z}},
        {{bounds.min.x, bounds.min.y, bounds.max.z}, {bounds.min.x, bounds.max.y, bounds.max.z}},
        {{bounds.max.x, bounds.min.y, bounds.max.z}, bounds.max                                },
    };
}
void BoundsBox::refreshLines(AABB const& bounds) {
    auto edges = getEdges(bounds);
    assert(edges.size() == BoxLines);
    for (size_t i = 0; i < BoxLines; ++i) {
        auto const& element = edges[i];
        auto&       line    = mLines[i];
        if (line != nullptr) {
            line->setPosition(element.first);
            line->setEndPosition(element.second);
        } else {
            line = std::make_unique<DebugLine>(element.first, element.second);
        }
    }
}
std::vector<IDebugShape const*> BoundsBox::toArray() const {
    std::vector<IDebugShape const*> lines{};
    lines.reserve(BoxLines);
    for (auto const& line : mLines) {
        lines.push_back(line.get());
    }
    return lines;
}


} // namespace debug_shape::extension