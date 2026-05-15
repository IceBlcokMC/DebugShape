/// <reference types="@levimc-lse/types" />
/// <reference types="../bin/DebugShape/DebugShape.d.ts" />

import { DebugText, ShapeType, Color } from "DebugShape.dll";

/** @type {DebugText} */ let textShape = null;

function hslToColor(h, s, l) {
  const c = (1 - Math.abs(2 * l - 1)) * s;
  const x = c * (1 - Math.abs(((h / 60) % 2) - 1));
  const m = l - c / 2;
  let r = 0,
    g = 0,
    b = 0;
  if (h < 60) {
    r = c;
    g = x;
  } else if (h < 120) {
    r = x;
    g = c;
  } else if (h < 180) {
    g = c;
    b = x;
  } else if (h < 240) {
    g = x;
    b = c;
  } else if (h < 300) {
    r = x;
    b = c;
  } else {
    r = c;
    b = x;
  }
  return new Color(
    Math.floor((r + m) * 255),
    Math.floor((g + m) * 255),
    Math.floor((b + m) * 255),
    255,
  );
}
function randomVibrantColor() {
  const h = Math.random() * 360;
  const s = 0.7 + Math.random() * 0.3;
  const l = 0.45 + Math.random() * 0.15;
  return hslToColor(h, s, l);
}

function registerCommand() {
  const cmd = mc.newCommand(
    "test_addon",
    "test DebugShape addon",
    PermType.Any,
  );
  cmd.setEnum("shape_text", ["text"]);
  cmd.mandatory("type", ParamType.Enum, "shape_text");
  cmd.mandatory("text", ParamType.String);
  cmd.mandatory("pos", ParamType.Vec3);
  cmd.overload(["type", "text", "pos"]);
  cmd.setCallback((cmd, origin, out, result) => {
    /** @type {string} */ const text = result.text;
    /** @type {FloatPos} */ const pos = result.pos;
    if (textShape == null) {
      textShape = DebugText.create(pos, text); // first use
      textShape.draw();
      return;
    }
    textShape.text = text;
    textShape.location = pos;
    textShape.update(); // sendToClients (all players)
  });
}

function main() {
  registerCommand();

  setInterval(() => {
    if (textShape != null) {
      textShape.color = randomVibrantColor();
      textShape.update();
    }
  }, 500);
}

mc.listen("onServerStarted", main);
