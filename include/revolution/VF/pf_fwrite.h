#ifndef RVL_SDK_VF_PF_FWRITE_H
#define RVL_SDK_VF_PF_FWRITE_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

u32 VFipf2_fwrite(void* p_buf, u32 size, u32 count, struct PF_FILE* p_file);

#ifdef __cplusplus
}
#endif
#endif
