#ifndef RVL_SDK_VF_PF_VOLUME_H
#define RVL_SDK_VF_PF_VOLUME_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

s32 VFiPFVOL_DoMountVolume(struct PF_VOLUME* p_vol);
s32 VFiPFVOL_p_unmount(struct PF_VOLUME* p_vol, u32 mode);
s32 VFiPFVOL_InitModule(u32 config, void* param);
s32 VFiPFVOL_CheckForRead(struct PF_VOLUME* p_vol);
s32 VFiPFVOL_CheckForWrite(struct PF_VOLUME* p_vol);
s32 VFiPFVOL_GetCurrentDir(struct PF_VOLUME* p_vol, struct PF_DIR_ENT* p_current_dir);
void VFiPFVOL_SetCurrentVolume(struct PF_VOLUME* p_vol);
struct PF_VOLUME* VFiPFVOL_GetCurrentVolume();
struct PF_VOLUME* VFiPFVOL_GetVolumeFromDrvChar(s8 drv_char);
void VFiPFVOL_LoadVolumeLabelFromBuf(const u8* buf, struct PF_VOLUME* p_vol);
s32 VFiPFVOL_errnum();
s32 VFiPFVOL_getdev(s8 drv_char, struct PF_DEV_INF* dev_inf);
s32 VFiPFVOL_attach(struct PF_DRV_TBL* p_drv);
s32 VFiPFVOL_detach(s8 drv_char);
s32 VFiPFVOL_unmount(s8 drv_char, u32 mode);

#ifdef __cplusplus
}
#endif
#endif
