#include "DebugShapeImpl.h"

#include "debug_shape/detail/DebugShapeDrawerImpl.h"
#include "mc/world/level/dimension/Dimension.h"


namespace debug_shape ::detail {

static std::atomic<uint64_t> nextId_{UINT64_MAX};

DebugShapeImpl::DebugShapeImpl(ShapeType type, Vec3 const& location) {
    // The implementation of this library comes from the PLand mod.
    // In order to avoid conflicts, PLand starts counting IDs from INT_MAX.
    // This library can only count downwards from UINT64_MAX to avoid conflicts.
    // TODO: Look for the internal counter of Minecraft.
    payload_.mNetworkId = nextId_.fetch_sub(1);
    if (payload_.mNetworkId == 0) {
        throw std::overflow_error("DebugShape ID overflow");
    }

    payload_.mLocation  = location;
    payload_.mShapeType = static_cast<ScriptModuleDebugUtilities::ScriptDebugShapeType>(type);
}
DebugShapeImpl::~DebugShapeImpl() { DebugShapeImpl::remove(); }

ShapeID DebugShapeImpl::getShapeID() const { return {payload_.mNetworkId}; }

ShapeType DebugShapeImpl::getShapeType() const { return static_cast<ShapeType>(*payload_.mShapeType.get()); }

std::optional<Vec3> DebugShapeImpl::getLocation() const { return payload_.mLocation; }

void DebugShapeImpl::setLocation(const Vec3& loc) { payload_.mLocation = loc; }

std::optional<Vec3> DebugShapeImpl::getRotation() const { return payload_.mRotation; }

void DebugShapeImpl::setRotation(std::optional<Vec3> rot) { payload_.mRotation = rot; }

std::optional<float> DebugShapeImpl::getScale() const { return payload_.mScale; }

void DebugShapeImpl::setScale(std::optional<float> s) { payload_.mScale = s; }

std::optional<mce::Color> DebugShapeImpl::getColor() const { return payload_.mColor; }

void DebugShapeImpl::setColor(std::optional<mce::Color> c) { payload_.mColor = c; }

bool DebugShapeImpl::hasDuration() const { return payload_.mTimeLeftTotalSec->value_or(0) > 0; }

std::optional<float> DebugShapeImpl::getTotalTimeLeft() const { return payload_.mTimeLeftTotalSec; }

void DebugShapeImpl::setTotalTimeLeft(std::optional<float> t) { payload_.mTimeLeftTotalSec = t; }

DimensionType DebugShapeImpl::getDimensionId() const { return payload_.mDimensionId; }

void DebugShapeImpl::setDimensionId(DimensionType d) { payload_.mDimensionId = d; }

void DebugShapeImpl::draw() const { DebugShapeDrawerImpl::getInstance().drawShape(this); }

void DebugShapeImpl::draw(Player& player) const {}

void DebugShapeImpl::draw(DimensionType dimension) const {}

void DebugShapeImpl::remove() const {}

void DebugShapeImpl::remove(Player& player) const {}

void DebugShapeImpl::remove(DimensionType dimension) const {}

void DebugShapeImpl::update() const {}

void DebugShapeImpl::update(Player& player) const {}

void DebugShapeImpl::update(DimensionType dimension) const {}


} // namespace debug_shape::detail