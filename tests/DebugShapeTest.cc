#include "DebugShapeTest.h"

#include "debug_shape/api/shape/IDebugArrow.h"
#include "debug_shape/api/shape/IDebugBox.h"
#include "debug_shape/api/shape/IDebugCircle.h"
#include "debug_shape/api/shape/IDebugLine.h"
#include "debug_shape/api/shape/IDebugShape.h"
#include "debug_shape/api/shape/IDebugSphere.h"
#include "debug_shape/api/shape/IDebugText.h"

#include "debug_shape/api/shape/extension/IBoundsBox.h"


#include "ll/api/Expected.h"
#include "ll/api/command/CommandHandle.h"
#include "ll/api/command/CommandRegistrar.h"
#include "ll/api/command/Overload.h"

#include "mc/platform/UUID.h"
#include "mc/server/commands/CommandOrigin.h"
#include "mc/server/commands/CommandOriginType.h"
#include "mc/server/commands/CommandOutput.h"
#include "mc/server/commands/CommandPosition.h"
#include "mc/server/commands/CommandVersion.h"
#include "mc/world/actor/player/Player.h"
#include "mc/world/phys/AABB.h"

#include <memory>
#include <vector>


namespace tests {


std::vector<std::unique_ptr<debug_shape::IDebugShape>> gShapes;
void addShape(std::unique_ptr<debug_shape::IDebugShape> shape) { gShapes.push_back(std::move(shape)); }

#define CHECK_ORIGIN(ORI)                                                                                              \
    if (ORI.getOriginType() != CommandOriginType::Player) {                                                            \
        output.error("This command can only be run by a player");                                                      \
        return;                                                                                                        \
    }

#define GET_PLAYER(ORI) *static_cast<Player*>(ORI.getEntity())

#define RESOLVE_POS(ORI, POS) POS.getPosition(CommandVersion::CurrentVersion(), ORI, Vec3{0, 0, 0})

// commands
struct TextParam {
    CommandPosition position;
    std::string     text;
};

struct SphereParam {
    CommandPosition position;
    float           scale{1.0f};
};

struct LineParam {
    CommandPosition start;
    CommandPosition end;
};

void DebugShapeTest::setup() {
    auto& cmd = ll::command::CommandRegistrar::getInstance().getOrCreateCommand("shape", "Minecraft DebugShape");

    // clear
    cmd.overload().text("clear").execute([](CommandOrigin const& /* origin */, CommandOutput& output) {
        gShapes.clear();
        output.success("Cleared all shapes");
    });

    // text
    cmd.overload<TextParam>()
        .text("text")
        .required("position")
        .required("text")
        .execute([](CommandOrigin const& origin, CommandOutput& output, TextParam const& param) {
            auto pos   = RESOLVE_POS(origin, param.position);
            auto shape = debug_shape::IDebugText::create(pos, param.text);
            shape->draw();
            addShape(std::move(shape));
            output.success("Added text shape");
        });

    // sphere
    cmd.overload<SphereParam>()
        .text("sphere")
        .required("position")
        .optional("scale")
        .execute([](CommandOrigin const& origin, CommandOutput& output, SphereParam const& param) {
            auto pos   = RESOLVE_POS(origin, param.position);
            auto shape = debug_shape::IDebugSphere::create(pos);
            shape->setScale(param.scale);
            shape->draw();
            addShape(std::move(shape));
            output.success("Added sphere shape");
        });

    // line
    cmd.overload<LineParam>().text("line").required("start").required("end").execute(
        [](CommandOrigin const& origin, CommandOutput& output, LineParam const& param) {
            auto start = RESOLVE_POS(origin, param.start);
            auto end   = RESOLVE_POS(origin, param.end);
            auto shape = debug_shape::IDebugLine::create(start, end);
            shape->draw();
            addShape(std::move(shape));
            output.success("Added line shape");
        }
    );

    // circle
    cmd.overload<SphereParam>()
        .text("circle")
        .required("position")
        .optional("scale")
        .execute([](CommandOrigin const& origin, CommandOutput& output, SphereParam const& param) {
            auto pos   = RESOLVE_POS(origin, param.position);
            auto shape = debug_shape::IDebugCircle::create(pos);
            shape->setScale(param.scale);
            shape->draw();
            addShape(std::move(shape));
            output.success("Added circle shape");
        });

    // box
    cmd.overload<LineParam>().text("box").required("start").required("end").execute(
        [](CommandOrigin const& origin, CommandOutput& output, LineParam const& param) {
            auto start = RESOLVE_POS(origin, param.start);
            auto end   = RESOLVE_POS(origin, param.end);
            auto shape = debug_shape::IDebugBox::create(start);
            shape->setBound(end);
            shape->draw();
            addShape(std::move(shape));
            output.success("Added box shape");
        }
    );

    // arrow
    cmd.overload<LineParam>().text("arrow").required("start").required("end").execute(
        [](CommandOrigin const& origin, CommandOutput& output, LineParam const& param) {
            auto start = RESOLVE_POS(origin, param.start);
            auto end   = RESOLVE_POS(origin, param.end);
            auto shape = debug_shape::IDebugArrow::create(start, end);
            shape->draw();
            addShape(std::move(shape));
            output.success("Added arrow shape");
        }
    );

    // extension: boundsbox
    cmd.overload<LineParam>()
        .text("extension")
        .text("bounds_box")
        .required("start")
        .required("end")
        .execute([](CommandOrigin const& origin, CommandOutput& output, LineParam const& param) {
            auto start = RESOLVE_POS(origin, param.start);
            auto end   = RESOLVE_POS(origin, param.end);
            auto shape = debug_shape::extension::IBoundsBox::create(AABB{start, end});
            shape->draw();
            static std::vector<std::unique_ptr<debug_shape::extension::IBoundsBox>> gBoundsBox;
            gBoundsBox.emplace_back(std::move(shape));
            output.success("Added bounds box shape");
        });
}


} // namespace tests