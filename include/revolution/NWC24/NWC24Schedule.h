#ifndef RVL_SDK_NWC24_SCHEDULE_H
#define RVL_SDK_NWC24_SCHEDULE_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

s32 NWC24SuspendScheduler(void);

s32 NWC24iTrySuspendForOpenLib(void);

s32 NWC24iResumeForCloseLib(void);

#ifdef __cplusplus
}
#endif
#endif
