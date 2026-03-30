#ifndef RVL_SDK_VF_PF_CLUSTER_H
#define RVL_SDK_VF_PF_CLUSTER_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

void VFiPFCLUSTER_UpdateLastAccessCluster(struct PF_FILE* p_file, u32 sector);
s32 VFiPFCLUSTER_AppendCluster(struct PF_FILE* p_file, u32 byte, u32* p_success, u32* sector);
s32 VFiPFCLUSTER_GetAppendSize(struct PF_FILE* p_file, u32* p_size);

#ifdef __cplusplus
}
#endif
#endif
