#pragma once
#include <cstdint>
#include <functional>

namespace debug_shape {


struct ShapeID {
    uint64_t val_;

    constexpr explicit operator uint64_t() const { return val_; }
    constexpr explicit operator bool() const { return val_ != 0; }

    static constexpr ShapeID invalid() noexcept { return ShapeID{0}; }
};


} // namespace debug_shape


namespace std {

template <>
struct hash<debug_shape::ShapeID> {
    size_t operator()(const debug_shape::ShapeID& id) const noexcept { return id.val_; }
};

} // namespace std