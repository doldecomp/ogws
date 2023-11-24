#ifndef RVL_SDK_VF_D_VF_H
#define RVL_SDK_VF_D_VF_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef void* VFFile;

typedef enum {
    VF_OK = 0x0000,
    VF_ERROR_0002 = 0x0002,
    VF_ERROR_0005 = 0x0005,
    VF_ERROR_B001 = 0xB001,
} VFError;

// Sync and async?
typedef enum { VF_SYNC_MODE_0, VF_SYNC_MODE_1 } VFSyncMode;

s32 VFIsAvailable(void);
s32 VFMountDriveNANDFlashEx(const char* i_drive, const char* i_sys_file_name_p);
s32 VFUnmountDrive(const char* i_drive);
VFFile VFOpenFile(const char* i_path_p, const char* i_mode, u32 i_attr);
s32 VFCloseFile(VFFile i_file_p);
s32 VFSeekFile(VFFile i_file_p, s32 i_offset, s32 i_origin);
s32 VFReadFile(VFFile i_file_p, void* o_buf_p, u32 i_size, u32* o_read_size_p);
s32 VFWriteFile(VFFile i_file_p, const void* i_buf_p, u32 i_size);
s32 VFDeleteFile(const char* i_path_p);
s32 VFGetFileSizeByFd(VFFile i_file_p);
s32 VFGetLastError(void);
s32 VFGetDriveFreeSize(const char* i_drive);
s32 VFGetLastDeviceError(const char* i_drive);
s32 VFSetSyncMode(const char* i_drive, u32 i_mode);

#ifdef __cplusplus
}
#endif
#endif
