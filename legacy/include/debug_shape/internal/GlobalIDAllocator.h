#pragma once
#include "debug_shape/IDebugShape.h"
#include <atomic>


namespace debug_shape::internal {


class GlobalIDAllocator {
    static std::atomic<ShapeID> mNextID;

public:
    GlobalIDAllocator() = delete;

    static ShapeID allocateID();
};


} // namespace debug_shape::internal