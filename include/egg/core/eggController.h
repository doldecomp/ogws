#ifndef EGG_CORE_CONTROLLER_H
#define EGG_CORE_CONTROLLER_H
#include <egg/types_egg.h>

namespace EGG {

class CoreControllerMgr {
public:
    static CoreControllerMgr* instance() {
        return sInstance;
    }

    char dummy[0x10];

    virtual void beginFrame(); // at 0x8
    virtual void endFrame();   // at 0xC

private:
    static CoreControllerMgr* sInstance;
};

} // namespace EGG

#endif
