#pragma once
#include <ll/api/base/StdInt.h>

namespace debug_shape {

enum class ShapeType : uchar {
    Line          = 0,
    Box           = 1,
    Sphere        = 2,
    Circle        = 3,
    Text          = 4,
    Arrow         = 5,
    Cylinder      = 6,
    Pyramid       = 7,
    Ellipsoid     = 8,
    Cone          = 9,
    NumShapeTypes = 10,
};

}
