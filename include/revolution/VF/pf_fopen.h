#ifndef RVL_SDK_VF_PF_FOPEN_H
#define RVL_SDK_VF_PF_FOPEN_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

struct PF_FILE* VFipf2_fopen(const s8* path, const s8* mode);

#ifdef __cplusplus
}
#endif
#endif
