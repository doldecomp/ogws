#include <revolution/VF.h>

void VFiPFSYS_initializeSYS() {
    return;
}

s32 VFiPFSYS_GetCurrentContextID(s32* context_id) {
    *context_id = 0;
    return 0;
}

void VFiPFSYS_TimeStamp(PFDATE* date, PFTIME* time) {
    date->year = 2000;
    date->month = 4;
    date->day = 1;
    time->hour = 0;
    time->minute = 0;
    time->second = 0;
    time->millisecond = 1;
    dTM_GetNowTime(date, time);
    time->millisecond = 1;
}
