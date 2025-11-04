#include "mc/deps/core/math/Vec3.h"
#include "mc/world/level/BlockPos.h"
#include "mc/world/level/dimension/Dimension.h"

#include "debug_shape/DebugArrow.h"
#include "debug_shape/DebugBox.h"
#include "debug_shape/DebugCircle.h"
#include "debug_shape/DebugLine.h"
#include "debug_shape/DebugShape.h"
#include "debug_shape/DebugSphere.h"
#include "debug_shape/DebugText.h"


namespace debug_shape {


DebugShape::DebugShape(DebugShapeType type, Vec3 const& loc) {
    mShapeData.mShapeType = type;
    mShapeData.mLocation  = loc;
}

uint64_t                  DebugShape::getId() const { return mShapeData.mNetworkId; }
DebugShapeType            DebugShape::getType() const { return mShapeData.mShapeType->value(); }
std::optional<Vec3>       DebugShape::getPosition() const { return mShapeData.mLocation; }
void                      DebugShape::setPosition(Vec3 const& loc) { mShapeData.mLocation = loc; }
std::optional<Vec3>       DebugShape::getRotation() const { return mShapeData.mRotation; }
void                      DebugShape::setRotation(std::optional<Vec3> rot) { mShapeData.mRotation = rot; }
std::optional<float>      DebugShape::getScale() const { return mShapeData.mScale; }
void                      DebugShape::setScale(std::optional<float> s) { mShapeData.mScale = s; }
std::optional<mce::Color> DebugShape::getColor() const { return mShapeData.mColor; }
void                      DebugShape::setColor(std::optional<mce::Color> c) { mShapeData.mColor = c; }
std::optional<float>      DebugShape::getTotalTimeLeft() const { return mShapeData.mTimeLeftTotalSec; }
void                      DebugShape::setTotalTimeLeft(std::optional<float> t) { mShapeData.mTimeLeftTotalSec = t; }
bool                      DebugShape::hasDuration() const { return mShapeData.mTimeLeftTotalSec->value_or(0) > 0; }


DebugSphere::DebugSphere(Vec3 const& loc) : DebugShape(DebugShapeType::Sphere, loc) {}

DebugText::DebugText(Vec3 const& loc, const std::string& text) : DebugShape(DebugShapeType::Text, loc) {
    mShapeData.mText = text;
}
std::optional<std::string> DebugText::getText() const { return mShapeData.mText; }
void                       DebugText::setText(const std::string& txt) { mShapeData.mText = txt; }

DebugCircle::DebugCircle(Vec3 const& center) : DebugShape(DebugShapeType::Circle, center) {}

DebugBox::DebugBox(Vec3 const& loc) : DebugShape(DebugShapeType::Box, loc) {}
std::optional<Vec3> DebugBox::getBound() const { return mShapeData.mBoxBound; }
void                DebugBox::setBound(Vec3 const& bound) { mShapeData.mBoxBound = bound; }

DebugLine::DebugLine(Vec3 const& start, Vec3 const& end) : DebugShape(DebugShapeType::Line, start) {
    mShapeData.mEndLocation = end;
}
std::optional<Vec3> DebugLine::getEndPosition() const { return mShapeData.mEndLocation; }
void                DebugLine::setEndPosition(std::optional<Vec3> loc) { mShapeData.mEndLocation = loc; }

DebugArrow::DebugArrow(Vec3 const& start, Vec3 const& end) : DebugLine(start, end) {
    mShapeData.mShapeType = DebugShapeType::Arrow;
}
std::optional<float>   DebugArrow::getHeadLength() const { return mShapeData.mArrowHeadLength; }
void                   DebugArrow::setHeadLength(std::optional<float> l) { mShapeData.mArrowHeadLength = l; }
std::optional<float>   DebugArrow::getHeadRadius() const { return mShapeData.mArrowHeadRadius; }
void                   DebugArrow::setHeadRadius(std::optional<float> r) { mShapeData.mArrowHeadRadius = r; }
std::optional<uint8_t> DebugArrow::getHeadSegments() const { return mShapeData.mNumSegments; }
void                   DebugArrow::setHeadSegments(std::optional<uint8_t> s) { mShapeData.mNumSegments = s; }


} // namespace debug_shape