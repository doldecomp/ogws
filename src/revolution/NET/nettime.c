#include <revolution/NET.h>
#include <revolution/NWC24.h>
#include <revolution/OS.h>

BOOL NETGetUniversalCalendar(OSCalendarTime* pTime) {
    static s64 whenCached = 0;
    NWC24Date date;
    s64 universalTime;
    s64 now;

    if (whenCached == 0 ||
        whenCached + OS_SEC_TO_TICKS(60) < __OSGetSystemTime()) {

        NWC24iSynchronizeRtcCounter(FALSE);
        whenCached = __OSGetSystemTime();
    }

    if (NWC24iGetUniversalTime(&universalTime) >= 0 &&
        NWC24iEpochSecondsToDate(&date, universalTime) >= 0 &&
        NWC24iDateToOSCalendarTime(pTime, &date) >= 0) {

        return TRUE;
    }

    OSTicksToCalendarTime(OSGetTime(), pTime);
    return FALSE;
}
