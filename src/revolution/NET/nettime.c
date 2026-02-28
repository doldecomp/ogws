#include <revolution/NWC24.h>
#include <revolution/OS.h>

BOOL NETGetUniversalCalendar(OSCalendarTime* time) {
    static s64 whenCached = 0;
    NWC24Date date;
    s64 universalTime;
    s64 now;

    if (whenCached == 0) {
        goto update;
    }
    now = __OSGetSystemTime();
    if (whenCached + OS_SEC_TO_TICKS(60) >= now) {
        goto use_cache;
    }
update:
    NWC24iSynchronizeRtcCounter(FALSE);
    now = __OSGetSystemTime();
    whenCached = now;
use_cache:
    if (NWC24iGetUniversalTime(&universalTime) < 0) {
        goto error;
    }
    if (NWC24iEpochSecondsToDate(&date, universalTime) < 0) {
        goto error;
    }
    if (NWC24iDateToOSCalendarTime(time, &date) < 0) {
        goto error;
    }
    return TRUE;
error:
    OSTicksToCalendarTime(OSGetTime(), time);
    return FALSE;
}
