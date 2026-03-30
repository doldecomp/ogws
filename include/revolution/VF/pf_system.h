#ifndef RVL_SDK_VF_PF_SYSTEM_H
#define RVL_SDK_VF_PF_SYSTEM_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

void VFiPFSYS_initializeSYS();
s32 VFiPFSYS_GetCurrentContextID(s32* context_id);
void VFiPFSYS_TimeStamp(struct PF_SYS_DATE* sdate, struct PF_SYS_TIME* stime);

#ifdef __cplusplus
}
#endif
#endif
