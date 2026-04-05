#ifndef RVL_SDK_VF_PF_CODE_H
#define RVL_SDK_VF_PF_CODE_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

s32 VFiPFCODE_Combine_Width(s16 oem_width, s16 uni_width);
void VFiPFCODE_Divide_Width(s32 width, s16* oem_width, s16* uni_width);

#ifdef __cplusplus
}
#endif
#endif
