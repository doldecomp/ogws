#ifndef RVL_SDK_VF_NAND_DRV_H
#define RVL_SDK_VF_NAND_DRV_H
#include <revolution/NAND.h>
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

s32 VFi_NandCreate(const char* path, u8 perm, u8 attr);
s32 VFi_NandDelete(const char* path);
s32 VFi_NandClose(struct NANDFileInfo* info);
s32 VFi_NandPrivateOpen(const char* path, struct NANDFileInfo* info, u8 accType);
s32 VFi_NandRead(struct NANDFileInfo* info, void* buf, u32 length);
s32 VFi_NandCreateDir(const char* path, u8 perm, u8 attr);
s32 VFi_NandGetLength(struct NANDFileInfo* info, u32* length);
s32 VFi_NandOpenSp(const char* path, void* info, u8 accType, u32 i_handleIdx);
void VFi_NandSetNANDFuncNormal(u32 i_handleIdx);
s32 A32_NANDRead(struct NANDFileInfo* i_fileInfo_p, void* i_buf, u32 i_size);
s32 A32_NANDWrite(struct NANDFileInfo* i_fileInfo_p, void* i_buf, u32 i_size, struct PDM_DISK* p_disk);
s32 VFi_NandFlushNANDFromHandleIdx(s32 i_handleIdx, int i_setLastDeviceError);
s32 _MountPrfFile(struct PDM_DISK* p_disk, s8* i_fullpath_p);
s32 nanddrv_BuildUpFSInfoSector(u8* buf);
s32 nanddrv_BuildUpBootSector(struct PDM_DISK* p_disk, u8* buf, enum FatType* type);
s32 nanddrv_init(struct PDM_DISK* p_disk);
s32 nanddrv_mount(struct PDM_DISK* p_disk);
s32 nanddrv_format(struct PDM_DISK* p_disk, const u8* param);
s32 nanddrv_pread(struct PDM_DISK* p_disk, u8* p_buf, u32 block, u32 num_blocks, u32* p_num_success);
s32 nanddrv_pwrite(struct PDM_DISK* p_disk, const u8* p_buf, u32 block, u32 num_blocks, u32* p_num_success);
s32 nanddrv_unmount(struct PDM_DISK* p_disk);
s32 nanddrv_finalize(struct PDM_DISK* p_disk);
s32 nanddrv_get_disk_info(struct PDM_DISK* p_disk, struct PDM_DISK_INFO* p_disk_info);
s32 VFi_nanddrv_init_drv_tbl(struct PDM_DISK_TBL* p_disk_tbl, u32 ui_ext);
s32 nanddrv_physical_read(u32 num_blocks, u8* buf, u32 block, u32 bps, u32* p_num_success, struct PDM_DISK* p_disk);
s32 nanddrv_physical_write(u32 num_blocks, const u8* buf, u32 block, u32 bps, u32* p_num_success, struct PDM_DISK* p_disk);

#ifdef __cplusplus
}
#endif
#endif
