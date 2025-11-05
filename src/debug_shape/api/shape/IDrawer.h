#pragma once
#include <mc/_HeaderOutputPredefine.h>

class Player;

namespace debug_shape {


class IDrawer {
public:
    virtual ~IDrawer() = default;

    virtual void draw() const                        = 0; // sendToClients (all players)
    virtual void draw(Player& player) const          = 0; // sendToPlayer (only specific player)
    virtual void draw(DimensionType dimension) const = 0; // sendToDimension (only specific dimension)

    virtual void remove() const                        = 0;
    virtual void remove(Player& player) const          = 0;
    virtual void remove(DimensionType dimension) const = 0;

    virtual void update() const                        = 0;
    virtual void update(Player& player) const          = 0;
    virtual void update(DimensionType dimension) const = 0;
};


} // namespace debug_shape