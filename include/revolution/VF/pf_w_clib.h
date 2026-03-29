#ifndef RVL_SDK_VF_PF_W_CLIB_H
#define RVL_SDK_VF_PF_W_CLIB_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

u32 VFipf_w_strlen(const u16* s);
u16* VFipf_w_strcpy(u16* dst, const u16* src);
s32 VFipf_w_strncmp(const u16* s1, const u16* s2, u32 length);

#ifdef __cplusplus
}
#endif
#endif
