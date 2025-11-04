#include "ModEntry.h"

#include "ll/api/mod/RegisterHelper.h"

#ifdef DS_TEST
#include "DebugShapeTest.h"
#endif

namespace debug_shape {

ModEntry& ModEntry::getInstance() {
    static ModEntry instance;
    return instance;
}

bool ModEntry::load() { return true; }

bool ModEntry::enable() {
#ifdef DS_TEST
    tests::DebugShapeTest::setup();
#endif
    return true;
}

bool ModEntry::disable() { return true; }

} // namespace debug_shape

LL_REGISTER_MOD(debug_shape::ModEntry, debug_shape::ModEntry::getInstance());
