#ifndef RVL_SDK_VF_PF_API_UTIL_H
#define RVL_SDK_VF_PF_API_UTIL_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

s32 VFiPFAPI_ParseOpenModeString(const s8* mode_str);
s32 VFiPFAPI_convertError(s32 err);
s32 VFiPFAPI_convertReturnValue(s32 err);
void* VFiPFAPI_convertReturnValue2NULL(s32 err, void* p_stream);
s32 VFiPFAPI_convertReturnValue4unmount(s32 err);

#ifdef __cplusplus
}
#endif
#endif
