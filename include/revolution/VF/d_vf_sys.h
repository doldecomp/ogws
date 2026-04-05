#ifndef RVL_SDK_VF_D_VF_SYS_H
#define RVL_SDK_VF_D_VF_SYS_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

void VFSysSetLastError(s32 i_err);
void VFSys_create_cache(struct VF_HANDLE_TYPE* i_handle_p, u32 i_pages, struct MEMiHeapHead* i_heap_handle);
struct VF_HANDLE_TYPE* VFSysGetHandleP(s32 i_idx);
s32 VFSysHandleP2Idx(struct VF_HANDLE_TYPE* i_handle_p);
struct VF_HANDLE_TYPE* VFSysVol2HandleP(struct PF_VOLUME* i_vol_p);
int VFSysPDMDisk2HandleIdx(const struct PDM_DISK* i_disk_p);
struct VF_HANDLE_DRIVE* VFSysGetDriveP(s32 i_idx);
struct VF_HANDLE_DRIVE* VFSysPDMDisk2DriveP(struct PDM_DISK* disk_p);
void VFSysInit(void* i_heap_start_address_p, u32 i_size);
s32 VFSysSetDeviceNANDFlash(s32* o_idx_p, void* i_cache_heap_p, u32 i_cache_size);
s32 VFSysUnsetDevice(s32 i_handle_idx);
s32 VFSysCheckExistPrfFile_nandflash_sub(const s8* i_prf_file_name_p, u32 i_handle_idx);
s32 VFSysCheckExistPrfFile_nandflash(struct VF_HANDLE_DEVICE* i_device_p, const s8* i_prf_file_name_p, void* i_memory_p, u32 i_handle_idx);
s32 VFSysCheckExistPrfFile_ram(struct VF_HANDLE_DEVICE* i_device_p, const s8* i_prf_file_name_p, void* i_memory_p, u32 i_handle_idx);
s32 VFSysCheckExistPrfFile_dvd(struct VF_HANDLE_DEVICE* i_device_p, const s8* i_prf_file_name_p, void* i_memory_p, u32 i_handle_idx);
s32 VFSysCheckExistPrfFile(s32 i_handle_idx, const s8* i_prf_file_name_p, void* i_memory_p);
s32 VFSysMountDrv(s32 i_handle_idx, const s8* i_prf_file_name_p, void* i_memory_p);
s32 VFSysUnmountDrv(s32 i_handle_idx, u32 i_mode);
struct PF_FILE* VFSysOpenFile_current(const s8* i_path_p, const s8* i_mode);
struct PF_FILE* VFSysOpenFile(s32 i_handle_idx, const s8* i_path_p, const s8* i_mode);
s32 VFSysCloseFile(struct PF_FILE* i_file_p);
s32 VFSysSeekFile(struct PF_FILE* i_file_p, s32 i_offset, s32 i_origin);
s32 VFSysReadFile(u32* o_read_size_p, void* o_buf_p, u32 i_size, struct PF_FILE* i_file_p);
s32 VFSysWriteFile(void* i_buf_p, u32 i_size, struct PF_FILE* i_file_p);
s32 VFSysDeleteFile_current(const s8* i_path_p);
s32 VFSysDeleteFile(s32 i_handle_idx, const s8* i_path_p);
s32 VFSysGetFileSizeByFd(s32* o_size_p, struct PF_FILE* i_file_p);
s32 VFSysGetDriveFreeSize(s32 i_handle_idx);
s32 VFSysGetLastError();
s32 VFSysGetLastDeviceError_current();
s32 VFSysGetLastDeviceError(s32 i_handle_idx);
void VFSysSetNandFuncEx(u32 i_handle_idx);
s32 VFSysSetSyncMode(s32 i_handle_idx, u32 i_mode);

#ifdef __cplusplus
}
#endif
#endif
