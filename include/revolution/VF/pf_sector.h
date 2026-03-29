#ifndef RVL_SDK_VF_PF_SECTOR_H
#define RVL_SDK_VF_PF_SECTOR_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

s32 VFiPFSEC_ReadFAT(struct PF_VOLUME* p_vol, u8* p_buf, u32 sector, u16 offset, u16 size);
s32 VFiPFSEC_ReadData(struct PF_VOLUME* p_vol, u8* p_buf, u32 sector, u16 offset, u32 size, u32* p_success_size, u32 set_sig);
s32 VFiPFSEC_WriteFAT(struct PF_VOLUME* p_vol, const u8* p_buf, u32 sector, u16 offset, u16 size);
s32 VFiPFSEC_WriteData(struct PF_VOLUME* p_vol, const u8* p_buf, u32 sector, u16 offset, u32 size, u32* p_success_size, u32 set_sig);

#ifdef __cplusplus
}
#endif
#endif
