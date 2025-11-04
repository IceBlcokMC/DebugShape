#include "debug_shape/internal/GlobalIDAllocator.h"
#include "debug_shape/IDebugShape.h"
#include <atomic>
#include <cstdint>


namespace debug_shape::internal {


std::atomic<ShapeID> GlobalIDAllocator::mNextID = UINT64_MAX;

ShapeID GlobalIDAllocator::allocateID() {
    // The implementation of this library comes from the PLand mod.
    // In order to avoid conflicts, PLand starts counting IDs from INT_MAX.
    // This library can only count downwards from UINT64_MAX to avoid conflicts.
    // TODO: Look for the internal counter of Minecraft.
    uint64_t id = mNextID.fetch_sub(1, std::memory_order_relaxed);
    if (id == 0) {
        throw std::overflow_error("DebugShape ID overflow");
    }
    return id;
}

} // namespace debug_shape::internal