#ifndef EGG_CORE_STOP_WATCH_H
#define EGG_CORE_STOP_WATCH_H
#include <egg/types_egg.h>

#include <egg/core/eggWatch.h>

#include <revolution/OS.h>

namespace EGG {

class Stopwatch : public Watch {
public:
    Stopwatch() : mEndTick(0) {}

    void start() {
        Watch::start();
        mEndTick = 0;
    }

    void stop() {
        if (isStarted()) {
            mEndTick = OSGetTick();
        }
    }

    u32 getMeasureTick() {
        if (isStarted() && mEndTick != 0) {
            return mEndTick - getStartTick();
        }

        return 0;
    }

    u32 getStopTick() {
        return mEndTick;
    }
    void setStopTick(u32 tick) {
        mEndTick = tick;
    }

private:
    u32 mEndTick; // at 0x4
};

} // namespace EGG

#endif
