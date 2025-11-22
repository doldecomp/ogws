#include <Pack/RPSystem.h>

#include <revolution/OS.h>

// Stubbed for release
void OSReport(const char* /* msg */, ...) {
    ;
}

#if defined(__CWCC__)
void main(int /* argc */, char** /* argv */) {
#else
int main(int /* argc */, char** /* argv */) {
#endif
    RPSysSystem::initialize();
    RPSysSystem::create();
    RP_GET_INSTANCE(RPSysSystem)->setup();
    RP_GET_INSTANCE(RPSysSystem)->mainLoop();
}
