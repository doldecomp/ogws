#include <Pack/RPUtility.h>

#include <revolution/OS.h>

u32 RPUtlRandom::sSeed = 0;
const u32 RPUtlRandom::RANDF_MAX = 0xFFFF;
const u32 RPUtlRandom::RANDF_SHIFT = 16;
const u32 RPUtlRandom::MULT = 0x10DCD;

/**
 * @brief Creates a seed based off of the system time.
 */
void RPUtlRandom::initialize() {
    s64 ticks = OSGetTime();
    OSCalendarTime calTime;

    OSTicksToCalendarTime(ticks, &calTime);
    //! Maybe there's a macro for this? Might look a bit fake-matchy at the
    //! moment.
    sSeed = (calTime.min << 26) | (calTime.sec << 20) | (calTime.msec << 10) |
            calTime.usec;
}
