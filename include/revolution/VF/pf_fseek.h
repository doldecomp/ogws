#ifndef RVL_SDK_VF_PF_FSEEK_H
#define RVL_SDK_VF_PF_FSEEK_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

int VFipf2_fseek(struct PF_FILE* pFile, s32 lOffset, int nOrigin);

#ifdef __cplusplus
}
#endif
#endif
