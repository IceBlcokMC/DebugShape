/// <reference path="./jspp_builtin_type.d.ts" />

declare module "DebugShape.dll" {
  export type UUID = string;
  export type DimensionType = number; // dimid

  export class Drawer {
    draw(): void; // sendToClients (all players)
    draw(player_uuid: UUID): void; // sendToPlayer (only specific player)
    draw(dimid: DimensionType): void; // sendToDimension (only specific dimension)

    remove(): void;
    remove(player_uuid: UUID): void;
    remove(dimid: DimensionType): void;

    update(): void;
    update(player_uuid: UUID): void;
    update(dimid: DimensionType): void;

    // 批量静态方法 / Batch static methods
    static drawAll(shapes: Drawer[]): void;
    static drawAll(shapes: Drawer[], player_uuid: UUID): void;
    static drawAll(shapes: Drawer[], dimid: DimensionType): void;
    static updateAll(shapes: Drawer[]): void;
    static updateAll(shapes: Drawer[], player_uuid: UUID): void;
    static updateAll(shapes: Drawer[], dimid: DimensionType): void;
    static removeAll(shapes: Drawer[]): void;
    static removeAll(shapes: Drawer[], player_uuid: UUID): void;
    static removeAll(shapes: Drawer[], dimid: DimensionType): void;
  }

  export enum ShapeType {
    Line = 0,
    Box = 1,
    Sphere = 2,
    Circle = 3,
    Text = 4,
    Arrow = 5,
    NumShapeTypes = 6,
  }

  /**
   * Vec3 向量，表示三维空间中的点或方向。
   * Vec3 vector, representing a point or direction in 3D space.
   *
   * **注意：这是纯值类型（plain object），无引用语义。**
   * **Note: This is a plain value type with no reference semantics.**
   *
   * 从图形上读取的 Vec3 是一个副本，修改其属性不会影响原图形。
   * 必须整体赋值才能更新：
   * Reading a Vec3 from a shape creates a copy. Modifying its properties
   * will not affect the original shape. You must reassign the entire object:
   *
   * @example
   * ```ts
   * // ❌ 错误 / Wrong — 这样改不会生效 / this won't take effect
   * shape.location.x = 10;
   *
   * // ✅ 正确 / Correct — 整体赋值 / reassign the entire object
   * const loc = shape.location;
   * loc.x = 10;
   * shape.location = loc;
   * ```
   */
  export interface Vec3 {
    x: number;
    y: number;
    z: number;
  }
  export class Color {
    constructor();

    /**
     * @param r red 0~255
     * @param g green 0~255
     * @param b blue 0~255
     * @param a alpha 0~255 (255 = 1.0f, 0 = 0.0f)
     */
    constructor(r: number, g: number, b: number, a: number);

    constructor(hex: string);

    r: number; // float
    g: number; // float
    b: number; // float
    a: number; // float

    toHexString(): string;

    // 下列只读颜色对象禁止修改，否则抛出异常
    // The following read-only color objects cannot be modified, otherwise an exception will be thrown.
    readonly BLACK: Color;
    readonly WHITE: Color;
    readonly RED: Color;
    readonly GREEN: Color;
    readonly BLUE: Color;
    readonly YELLOW: Color;
    readonly CYAN: Color;
    readonly ORANGE: Color;
    readonly PINK: Color;
    readonly PURPLE: Color;
    readonly GREY: Color;
    readonly REBECCA_PURPLE: Color;
  }

  /**
   * @see https://learn.microsoft.com/en-us/minecraft/creator/scriptapi/minecraft/debug-utilities/debugshape?view=minecraft-bedrock-experimental
   */
  export class DebugShape extends Drawer {
    readonly id: number;
    readonly type: ShapeType;
    location: optional<Vec3>;
    rotation: optional<Vec3>;
    scale: optional<number>;
    color: optional<Color>;
    hasDuration(): boolean;
    totalTimeLeft: optional<number>;
    dimid: optional<DimensionType>;
  }

  /**
   * @see https://learn.microsoft.com/en-us/minecraft/creator/scriptapi/minecraft/debug-utilities/debugtext?view=minecraft-bedrock-experimental
   */
  export class DebugText extends DebugShape {
    text: string;

    static create(pos: Vec3, text: string): DebugText;
  }

  /**
   * @see https://learn.microsoft.com/en-us/minecraft/creator/scriptapi/minecraft/debug-utilities/debugline?view=minecraft-bedrock-experimental
   */
  export class DebugLine extends DebugShape {
    endPosition: Vec3;

    static create(start: Vec3, end: Vec3): DebugLine;
  }

  /**
   * @see https://learn.microsoft.com/en-us/minecraft/creator/scriptapi/minecraft/debug-utilities/debugcircle?view=minecraft-bedrock-experimental
   */
  export class DebugCircle extends DebugShape {
    static create(center: Vec3): DebugCircle;
  }

  /**
   * @see https://learn.microsoft.com/en-us/minecraft/creator/scriptapi/minecraft/debug-utilities/debugbox?view=minecraft-bedrock-experimental
   */
  export class DebugBox extends DebugShape {
    static create(location: Vec3): DebugBox;

    bound: optional<Vec3>;
  }

  /**
   * @see https://learn.microsoft.com/en-us/minecraft/creator/scriptapi/minecraft/debug-utilities/debugsphere?view=minecraft-bedrock-experimental
   */
  export class DebugSphere extends DebugShape {
    static create(location: Vec3): DebugSphere;

    numSegments: optional<number>; // uchar (0-255)
  }

  /**
   * @see https://learn.microsoft.com/en-us/minecraft/creator/scriptapi/minecraft/debug-utilities/debugarrow?view=minecraft-bedrock-experimental
   */
  export class DebugArrow extends DebugShape {
    static create(start: Vec3, end: Vec3): DebugArrow;

    endPosition: Vec3;

    headLength: optional<number>;

    headRadius: optional<number>;

    headSegments: optional<number>; // uint8 (0-255)
  }

  /**
   * AABB 轴对齐包围盒。
   * Axis-Aligned Bounding Box.
   *
   * 由两个对角点定义，所有边与坐标轴平行。
   * Defined by two opposite corners, all edges parallel to the coordinate axes.
   *
   * **注意：这是纯值类型（plain object），无引用语义。**
   * **Note: This is a plain value type with no reference semantics.**
   */
  export interface AABB {
    min: Vec3;
    max: Vec3;
  }

  export namespace extension {
    export class BoundsBox extends Drawer {
      static create(bounds: AABB, color: Color): BoundsBox;

      setBounds(bounds: AABB): void;

      rotation: optional<Vec3>;
      color: optional<Color>;
      totalTimeLeft: optional<number>;
      dimid: optional<DimensionType>;

      hasDuration(): boolean;
    }
  }
}
