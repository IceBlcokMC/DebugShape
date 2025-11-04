#pragma once
#include "debug_shape/Macro.h"

#include "mc/_HeaderOutputPredefine.h"
#include "mc/network/packet/PacketShapeData.h"
#include "mc/scripting/modules/minecraft/debugdrawer/ScriptDebugShapeType.h"

class Player;

namespace debug_shape {

using DebugShapeType  = ScriptModuleDebugUtilities::ScriptDebugShapeType;
using ShapeDataPacket = ScriptModuleDebugUtilities::PacketShapeData;

using ShapeID = uint64_t;

inline constexpr ShapeID InvalidShapeID = 0;


class IDrawerInterface {
public:
    DSAPI virtual ~IDrawerInterface() = default;

    virtual void       draw() const                          = 0; // sendToClients
    virtual void       draw(Player& player) const            = 0; // sendToPlayer
    virtual void       draw(DimensionType dimension) const   = 0; // sendToDimension
    virtual void       remove() const                        = 0;
    virtual void       remove(Player& player) const          = 0;
    virtual void       remove(DimensionType dimension) const = 0;
    DSAPI virtual void update() const;
    DSAPI virtual void update(Player& player) const;
    DSAPI virtual void update(DimensionType dimension) const;
};


class IDebugShape : public IDrawerInterface {
protected:
    ShapeDataPacket mShapeData;

public:
    DSAPI IDebugShape();
    DSAPI ~IDebugShape() override;

    IDebugShape(const IDebugShape&)            = delete;
    IDebugShape& operator=(const IDebugShape&) = delete;

    DSNDAPI virtual ShapeDataPacket const& serialize() const final;

    DSAPI void draw() const override;
    DSAPI void draw(Player& player) const override;
    DSAPI void draw(DimensionType dimension) const override;
    DSAPI void remove() const override;
    DSAPI void remove(Player& player) const override;
    DSAPI void remove(DimensionType dimension) const override;
};


} // namespace debug_shape