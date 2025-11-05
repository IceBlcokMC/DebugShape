# Drawer Packet Behavior

## 数据包发送行为

| DimensionId                  | sendToClients()                                             | sendTo(player)                                              | sendTo(pos, dim) pos&dim == input                                       | sendTo(pos, dim) dim != input, pos==input                                               | sendTo(pos, dim) dim&pos != input                                                           |
| ---------------------------- | ----------------------------------------------------------- | ----------------------------------------------------------- | ----------------------------------------------------------------------- | --------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------- |
| **set (0/1/2)**              | 所有玩家可见，但客户端仅渲染匹配 payload.DimensionId 的维度 | 指定玩家可见，但客户端仅渲染匹配 payload.DimensionId 的维度 | shape 显示在 pos 所在维度（dim 覆盖 payload.DimensionId 时以 dim 为准） | dim 覆盖 payload.DimensionId，shape 显示在指定 dim，原 payload.DimensionId 的维度不可见 | dim 覆盖 payload.DimensionId，shape 显示在指定 dim&pos，原 payload.DimensionId 的维度不可见 |
| **unset (默认 0/Overworld)** | 所有玩家可见，但客户端仅渲染 Overworld（默认 0）            | 指定玩家可见，但客户端仅渲染 Overworld（默认 0）            | pos 对应维度显示（默认使用 Overworld 0）                                | dim 覆盖默认值，shape 显示在指定 dim                                                    | dim 覆盖默认值，shape 显示在指定 dim&pos                                                    |

> `sendTo(pos, dim)` 的 `pos` 和 `dim` 的优先级均大于 `payload` 中的 `Location` 和 `DimensionId` (覆盖)。

## 图形 ID 行为

1. **new**：对于新的 ShapeID，客户端会新建图形。
2. **update**：对于已存在的 ShapeID，客户端会更新图形。
3. **delete**：对于发送已存在的 ShapeID 但 payload 为空，客户端会删除图形。
