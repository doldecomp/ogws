#ifndef RVL_SDK_VF_PF_DRIVER_H
#define RVL_SDK_VF_PF_DRIVER_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

s32 VFiPFDRV_GetBPBInformation(u8* p_buf, struct PF_BPB* p_bpb);
s32 VFiPFDRV_GetFSINFOInformation(struct PF_VOLUME* p_vol);
s32 VFiPFDRV_StoreFreeCountToFSINFO(struct PF_VOLUME* p_vol);
u32 VFiPFDRV_IsInserted(struct PF_VOLUME* p_vol);
u32 VFiPFDRV_IsDetected(struct PF_VOLUME* p_vol);
u32 VFiPFDRV_IsWProtected(struct PF_VOLUME* p_vol);
s32 VFiPFDRV_init(struct PF_VOLUME* p_vol);
s32 VFiPFDRV_finalize(struct PF_VOLUME* p_vol);
s32 VFiPFDRV_mount(struct PF_VOLUME* p_vol);
s32 VFiPFDRV_unmount(struct PF_VOLUME* p_vol, u32 mode);
s32 VFiPFDRV_format(struct PF_VOLUME* p_vol, const u8* param);
s32 VFiPFDRV_lread(struct PF_VOLUME* p_vol, u8* buf, u32 sector, u32 num_sectors, u32* p_num_success);
s32 VFiPFDRV_lwrite(struct PF_VOLUME* p_vol, const u8* buf, u32 sector, u32 num_sectors, u32* p_num_success);

#ifdef __cplusplus
}
#endif
#endif
