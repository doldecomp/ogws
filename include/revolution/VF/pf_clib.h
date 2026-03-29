#ifndef RVL_SDK_VF_PF_CLIB_H
#define RVL_SDK_VF_PF_CLIB_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

s32 VFipf_toupper(s32 c);
void* VFipf_memcpy(void* dst, void* src, u32 length);
void* VFipf_memset(void* dst, s32 c, u32 length);
u32 VFipf_strlen(const s8* s);
s8* VFipf_strcpy(s8* dst, const s8* src);
s32 VFipf_strcmp(const s8* s1, const s8* s2);
s32 VFipf_strncmp(const s8* s1, const s8* s2, u32 length);

#ifdef __cplusplus
}
#endif
#endif
