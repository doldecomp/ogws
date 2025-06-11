#ifndef EGG_CORE_WATCH_H
#define EGG_CORE_WATCH_H
#include <egg/types_egg.h>

#include <revolution/OS.h>

namespace EGG {

class Watch {
public:
    Watch() {
        reset();
    }

    void reset() {
        mStartTick = 0;
    }
    void start() {
        mStartTick = OSGetTick();
    }

    bool isStarted() {
        return mStartTick != 0;
    }

    u32 getStartTick() {
        return mStartTick;
    }
    void setStartTick(u32 tick) {
        mStartTick = tick;
    }

private:
    u32 mStartTick; // at 0x0
};

} // namespace EGG

#endif
