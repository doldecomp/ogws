#include <Pack/RPUtility.h>

#include <revolution/OS.h>

RPUtlRandom RPUtlRandom::sRandom;
const u32 RPUtlRandom::RANDF_MAX = 0xFFFF;
const u32 RPUtlRandom::RANDF_SHIFT = 16;
const u32 RPUtlRandom::MULT = 0x10DCD;

/**
 * @brief Creates a seed based off of the system time.
 */
void RPUtlRandom::initialize() {
    sRandom.initRand();
}
void RPUtlRandom::initRand() {
    s64 ticks = OSGetTime();
    OSCalendarTime calTime;

    OSTicksToCalendarTime(ticks, &calTime);
    //! Maybe there's a macro for this? Might look a bit fake-matchy at the
    //! moment.
    mSeed = (calTime.min << 26) | (calTime.sec << 20) | (calTime.msec << 10) |
            calTime.usec;
}
