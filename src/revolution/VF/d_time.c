#include <revolution/VF.h>
#include <revolution/OS.h>

void dTM_GetNowTime(PF_SYS_DATE* sdate, PF_SYS_TIME* stime) {
    VFSysTime time;
    OSCalendarTime CalenderTime;

    sdate->sys_year = 0;
    sdate->sys_month = 0;
    sdate->sys_day = 0;
    stime->sys_hour = 0;
    stime->sys_min = 0;
    stime->sys_sec = 0;
     
    OSTicksToCalendarTime(OSGetTime(), &CalenderTime);
    sdate->sys_year = CalenderTime.year;
    sdate->sys_month = CalenderTime.month + 1;
    sdate->sys_day = CalenderTime.mday;
    stime->sys_hour = CalenderTime.hour;
    stime->sys_min = CalenderTime.min;
    stime->sys_sec = CalenderTime.sec;
    
}
