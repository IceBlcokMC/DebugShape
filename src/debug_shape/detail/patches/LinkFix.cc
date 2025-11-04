#include "mc/network/packet/ShapeDataPayload.h"
ShapeDataPayload::ShapeDataPayload() = default;

#include "mc/network/packet/TextDataPayload.h"
TextDataPayload::TextDataPayload() = default;
TextDataPayload::TextDataPayload(TextDataPayload const& cp) { mText = cp.mText; };

#include "mc/network/packet/DebugDrawerPacketPayload.h"
DebugDrawerPacketPayload::DebugDrawerPacketPayload() = default;