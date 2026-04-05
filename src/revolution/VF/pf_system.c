#include <revolution/VF.h>

void VFiPFSYS_initializeSYS() {
    return;
}

s32 VFiPFSYS_GetCurrentContextID(s32* context_id) {
    s32 err;

    err = 0;
    *context_id = 0;
    return err;
}

void VFiPFSYS_TimeStamp(struct PF_SYS_DATE* sdate, struct PF_SYS_TIME* stime) {
    sdate->sys_year = 2000;
    sdate->sys_month = 4;
    sdate->sys_day = 1;
    stime->sys_hour = 0;
    stime->sys_min = 0;
    stime->sys_sec = 0;
    stime->sys_ms = 1;
    dTM_GetNowTime(sdate, stime);
    stime->sys_ms = 1;
}
