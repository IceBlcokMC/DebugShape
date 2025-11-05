#include "BoundsBoxImpl.h"

#include "debug_shape/api/shape/IDebugLine.h"
#include "debug_shape/detail/DebugShapeDrawerImpl.h"

#include <mc/deps/core/utility/AutomaticID.h>

namespace debug_shape {

std::unique_ptr<extension::IBoundsBox> extension::IBoundsBox::create(AABB const& bounds, mce::Color const& color) {
    return std::make_unique<detail::extension::BoundsBoxImpl>(bounds, color);
}

namespace detail ::extension {

struct BoundsBoxImpl::Impl {
    static constexpr int                           Lines = 12;
    std::array<std::unique_ptr<IDebugLine>, Lines> lines_;

    std::vector<IDebugShape const*> asVector() const {
        std::vector<IDebugShape const*> result;
        result.reserve(Lines);
        for (auto const& line : lines_) {
            result.push_back(line.get());
        }
        return result;
    }

    std::vector<std::pair<Vec3, Vec3>> getEdges(AABB const& bounds) const {
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

    void refreshLines(AABB const& bounds) {
        auto edges = getEdges(bounds);
        assert(edges.size() == Lines);
        for (size_t i = 0; i < Lines; ++i) {
            auto const& element = edges[i];
            auto&       line    = lines_[i];
            if (line == nullptr) {
                line = IDebugLine::create(element.first, element.second);
            } else {
                line->setLocation(element.first);
                line->setEndPosition(element.second);
            }
        }
    }
};

BoundsBoxImpl::BoundsBoxImpl(AABB const& bounds, mce::Color const& color) : impl_(std::make_unique<Impl>()) {
    impl_->refreshLines(bounds);
    BoundsBoxImpl::setColor(color);
}

BoundsBoxImpl::~BoundsBoxImpl() { DebugShapeDrawerImpl::getInstance().removeShapes(impl_->asVector()); }

void BoundsBoxImpl::draw() const { DebugShapeDrawerImpl::getInstance().drawShapes(impl_->asVector()); }

void BoundsBoxImpl::draw(Player& player) const {
    DebugShapeDrawerImpl::getInstance().drawShapes(impl_->asVector(), player);
}

void BoundsBoxImpl::draw(DimensionType dimension) const {
    DebugShapeDrawerImpl::getInstance().drawShapes(impl_->asVector(), dimension);
}

void BoundsBoxImpl::remove() const { DebugShapeDrawerImpl::getInstance().removeShapes(impl_->asVector()); }

void BoundsBoxImpl::remove(Player& player) const {
    DebugShapeDrawerImpl::getInstance().removeShapes(impl_->asVector(), player);
}

void BoundsBoxImpl::remove(DimensionType dimension) const {
    DebugShapeDrawerImpl::getInstance().removeShapes(impl_->asVector(), dimension);
}

void BoundsBoxImpl::update() const { draw(); }

void BoundsBoxImpl::update(Player& player) const { draw(player); }

void BoundsBoxImpl::update(DimensionType dimension) const { draw(dimension); }

void BoundsBoxImpl::setBounds(const AABB& bounds) { impl_->refreshLines(bounds); }

std::optional<Vec3> BoundsBoxImpl::getRotation() const { return impl_->lines_[0]->getRotation(); }
void                BoundsBoxImpl::setRotation(std::optional<Vec3> rot) {
    for (auto& line : impl_->lines_) {
        line->setRotation(rot);
    }
}

std::optional<mce::Color> BoundsBoxImpl::getColor() const { return impl_->lines_[0]->getColor(); }
void                      BoundsBoxImpl::setColor(std::optional<mce::Color> c) {
    for (auto& line : impl_->lines_) {
        line->setColor(c);
    }
}

bool                 BoundsBoxImpl::hasDuration() const { return impl_->lines_[0]->hasDuration(); }
std::optional<float> BoundsBoxImpl::getTotalTimeLeft() const { return impl_->lines_[0]->getTotalTimeLeft(); }
void                 BoundsBoxImpl::setTotalTimeLeft(std::optional<float> t) {
    for (auto& line : impl_->lines_) {
        line->setTotalTimeLeft(t);
    }
}

DimensionType BoundsBoxImpl::getDimensionId() const { return impl_->lines_[0]->getDimensionId(); }
void          BoundsBoxImpl::setDimensionId(DimensionType d) {
    for (auto& line : impl_->lines_) {
        line->setDimensionId(d);
    }
}


} // namespace detail::extension
} // namespace debug_shape