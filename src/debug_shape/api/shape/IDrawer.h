#pragma once
#include <mc/_HeaderOutputPredefine.h>

class Player;

namespace debug_shape {

#define MC_V1_21_120_DEPRECATED [[deprecated("v1.21.120 added a dimension field")]]

class IDrawer {
public:
    virtual ~IDrawer() = default;

    virtual void                         draw() const                        = 0; // sendToClients
    virtual void                         draw(Player& player) const          = 0; // sendToPlayer
    MC_V1_21_120_DEPRECATED virtual void draw(DimensionType dimension) const = 0; // sendToDimension

    virtual void                         remove() const                        = 0;
    virtual void                         remove(Player& player) const          = 0;
    MC_V1_21_120_DEPRECATED virtual void remove(DimensionType dimension) const = 0;

    virtual void                         update() const                        = 0;
    virtual void                         update(Player& player) const          = 0;
    MC_V1_21_120_DEPRECATED virtual void update(DimensionType dimension) const = 0;
};

} // namespace debug_shape