#include <revolution/OS.h>
#include <revolution/VF.h>

static OSMutex l_Mutex;
static s32 l_InitedMutex;
static s32 l_vf_init;

#define VF_ERROR_B001 0xB001
#define VF_ERR_GENERIC 0xB002
#define VF_ERR_DRIVE_NOT_FOUND 0xB003
#define VF_ERR_0xB004 0xB004
#define VF_ERR_0xB005 0xB005

struct DriveP {
    void* file_p;
    struct PDM_DISK* pf_disk_p;
    struct PF_DRV_TBL pf_drv;
    struct PDM_PARTITION* pf_part_p;
    struct {
        struct MEMiHeapHead* heap_handle;
        unsigned long cache_pages;
        struct PF_CACHE_PAGE* pf_cache_page_p;
        unsigned char (*pf_cache_buf_p)[512];
    } cache;
    struct PF_CACHE_SETTING pf_cache_set;
    unsigned char pf_filename[255];
};

s32 VFIsAvailable(void) {
    return l_vf_init != 0;
}

void VFInitEx(void* i_heap_start_address_p, u32 i_size) {
    if (l_InitedMutex == 0) {
        OSInitMutex(&l_Mutex);
        l_InitedMutex = 1;
    }

    if (l_InitedMutex != 0) {
        OSLockMutex(&l_Mutex);
    }

    if (l_vf_init == 0) {
        l_vf_init = 1;
        VFSysInit(i_heap_start_address_p, i_size);
        VFipdm_init_diskmanager(0, 0);
        VFipf2_init_prfile2(0, 0);
        dHash_InitHashTable();
    }

    if (l_InitedMutex != 0) {
        OSUnlockMutex(&l_Mutex);
    }
}

s32 VF_activate_drive_common(long i_handle_idx, const char* i_sys_file_name_p, void* i_memory_p) {
    long err;
    struct DriveP* drive_p;
    struct PF_DRV_TBL* drv_tbl[2];

    err = VFSysCheckExistPrfFile((char*)i_handle_idx);
    if (err != 0) {
        VFSysSetLastError(err);
        return err;
    }

    err = VFSysMountDrv(i_handle_idx, i_sys_file_name_p, i_memory_p);
    if (err != 0) {
        VFSysSetLastError(err);
        return err;
    }

    drive_p = (void*)VFSysGetDriveP(i_handle_idx);

    if (drive_p == 0) {
        VFSysSetLastError(0xb002);
        return 0xb002;
    }

    drv_tbl[0] = &drive_p->pf_drv;
    drv_tbl[1] = 0;

    err = VFipf2_attach(drv_tbl);

    if (err != 0) {
        err = VFipf2_errnum();
        VFSysSetLastError(err);
        VFipdm_close_partition(drive_p->pf_part_p);
        return err;
    }

    return 0;
}

s32 VFMountDriveNANDFlashEx(const char* i_drive, const char* i_sys_file_name_p) {
    s32 result = VF_ERR_0xB004;
    int arg;
    int buf = -1;

    if (l_InitedMutex != 0) {
        OSLockMutex(&l_Mutex);
    }

    arg = dHash_GetArg(i_drive);
    if (arg == -1) {
        result = VFSysSetDeviceNANDFlash((char*)&buf, 0, 0);
        if (result == 0) {
            dHash_SetArgW((int)i_drive, (*(int*)&buf) & 0xFF);
        }
    }

    VFSysSetLastError(result);

    if (l_InitedMutex != 0) {
        OSUnlockMutex(&l_Mutex);
    }

    if (result == 0 || result == VF_ERR_0xB004) {
        if (l_InitedMutex != 0) {
            OSLockMutex(&l_Mutex);
        }

        arg = dHash_GetArg(i_drive);
        VFSysSetNandFuncNormal(arg);
        result = VF_activate_drive_common(arg, (char*)i_sys_file_name_p, 0);

        if (l_InitedMutex != 0) {
            OSUnlockMutex(&l_Mutex);
        }

        if (result != VF_OK && result != VF_ERR_0xB005) {
            if (l_InitedMutex != 0) {
                OSLockMutex(&l_Mutex);
            }

            arg = dHash_GetArg(i_drive);
            if (VFSysUnsetDevice(arg) == 0) {
                dHash_SetArg((int)i_drive);
            }

            if (l_InitedMutex != 0) {
                OSUnlockMutex(&l_Mutex);
            }
        }
    }

    return result;
}

s32 VFUnmountDrive(const char* i_drive) {
    s32 result;
    s32 arg;

    if (l_InitedMutex != 0) {
        OSLockMutex(&l_Mutex);
    }

    arg = dHash_GetArg(i_drive);
    result = VFSysUnmountDrv(arg, 0);
    VFSysSetLastError(result);

    if (l_InitedMutex != 0) {
        OSUnlockMutex(&l_Mutex);
    }

    if (result == VF_OK) {
        if (l_InitedMutex != 0) {
            OSLockMutex(&l_Mutex);
        }

        dHash_GetArg(i_drive);
        result = VFSysUnsetDevice();
        if (result == VF_OK) {
            dHash_SetArg(i_drive);
        }

        VFSysSetLastError(result);

        if (l_InitedMutex != 0) {
            OSUnlockMutex(&l_Mutex);
        }
    }

    return result;
}

char* VF_path2handleidx(s32* o_handle_idx_p, const char* i_path_p) {
    char drive[8];
    const char* str_p;
    s32 idx;
    const char* ret_p;

    *o_handle_idx_p = -1;
    str_p = i_path_p;
    idx = 0;
    ret_p = i_path_p;

    VFipf_memset(drive, 0, 8);

    while (*str_p != '\0') {
        if (*str_p == '\\' || *str_p == '/') {
            break;
        }

        if (*str_p == ':') {
            *o_handle_idx_p = dHash_GetArg(drive);
            if (*o_handle_idx_p == -1 || idx > 7) {
                ret_p = 0;
            } else {
                ret_p = str_p + 1;
            }
            break;
        }

        if (idx < 7) {
            drive[idx] = *str_p;
        }

        str_p++;
        idx++;
    }

    return (char*)ret_p;
}

VFFile VFOpenFile(const char* i_path_p, const char* i_mode, u32 i_attr) {
    s32 handleIdx = -1;
    VFFile result;
    char* relativePath;

    if (l_InitedMutex != 0) {
        OSLockMutex(&l_Mutex);
    }

    relativePath = VF_path2handleidx(&handleIdx, (char*)i_path_p);

    if (relativePath == 0) {
        VFSysSetLastError(VF_ERR_DRIVE_NOT_FOUND);
        if (l_InitedMutex != 0) {
            OSUnlockMutex(&l_Mutex);
        }
        return 0;
    }

    if (handleIdx != -1) {
        result = (VFFile)VFSysOpenFile(handleIdx, (int)relativePath, (int)i_mode);
    } else {
        result = (VFFile)VFSysOpenFile_current((int)relativePath, (int)i_mode);
    }

    if (l_InitedMutex != 0) {
        OSUnlockMutex(&l_Mutex);
    }

    return result;
}

s32 VFCloseFile(VFFile i_file_p) {
    s32 result;

    if (l_InitedMutex != 0) {
        OSLockMutex(&l_Mutex);
    }

    result = VFSysCloseFile((int)i_file_p);
    VFSysSetLastError(result);

    if (l_InitedMutex != 0) {
        OSUnlockMutex(&l_Mutex);
    }

    return result;
}

s32 VFSeekFile(VFFile i_file_p, s32 i_offset, s32 i_origin) {
    s32 result;

    if (l_InitedMutex != 0) {
        OSLockMutex(&l_Mutex);
    }

    result = VFSysSeekFile((int)i_file_p, i_offset, i_origin);
    VFSysSetLastError(result);

    if (l_InitedMutex != 0) {
        OSUnlockMutex(&l_Mutex);
    }

    return result;
}

s32 VFReadFile(VFFile i_file_p, void* o_buf_p, u32 i_size, u32* o_read_size_p) {
    s32 result;

    if (l_InitedMutex != 0) {
        OSLockMutex(&l_Mutex);
    }

    result = VFSysReadFile((int)o_read_size_p, (int)o_buf_p, i_size, (int)i_file_p);
    VFSysSetLastError(result);

    if (l_InitedMutex != 0) {
        OSUnlockMutex(&l_Mutex);
    }

    return result;
}

s32 VFWriteFile(VFFile i_file_p, const void* i_buf_p, u32 i_size) {
    s32 result;

    if (l_InitedMutex != 0) {
        OSLockMutex(&l_Mutex);
    }

    result = VFSysWriteFile((int)i_buf_p, (int)i_size, (int)i_file_p);
    VFSysSetLastError(result);

    if (l_InitedMutex != 0) {
        OSUnlockMutex(&l_Mutex);
    }

    return result;
}

s32 VFDeleteFile(const char* i_path_p) {
    s32 handleIdx = -1;
    s32 result;
    char* relativePath;

    if (l_InitedMutex != 0) {
        OSLockMutex(&l_Mutex);
    }

    relativePath = VF_path2handleidx(&handleIdx, (char*)i_path_p);

    if (relativePath == 0) {
        result = VF_ERR_DRIVE_NOT_FOUND;
        VFSysSetLastError(result);
        if (l_InitedMutex != 0) {
            OSUnlockMutex(&l_Mutex);
        }
        return VF_ERR_DRIVE_NOT_FOUND;
    }

    if (handleIdx != -1) {
        result = VFSysDeleteFile(handleIdx, (int)relativePath);
    } else {
        result = VFSysDeleteFile_current((int)relativePath);
    }

    VFSysSetLastError(result);

    if (l_InitedMutex != 0) {
        OSUnlockMutex(&l_Mutex);
    }

    return result;
}

s32 VFGetFileSizeByFd(VFFile i_file_p) {
    int size = -1;
    int result = VFSysGetFileSizeByFd(&size, (int)i_file_p);

    if (result != 0) {
        VFSysSetLastError(result);
    }

    return size;
}

s32 VFGetLastError(void) {
    return VFSysGetLastError();
}

s32 VFGetLastDeviceError(const char* i_drive) {
    s32 result;

    if (l_InitedMutex != 0) {
        OSLockMutex(&l_Mutex);
    }

    if (i_drive != 0) {
        int arg = dHash_GetArg(i_drive);
        result = VFSysGetLastDeviceError(arg);
    } else {
        result = VFSysGetLastDeviceError_current();
    }

    VFSysSetLastError(result);

    if (l_InitedMutex != 0) {
        OSUnlockMutex(&l_Mutex);
    }

    return result;
}

s32 VFGetDriveFreeSize(const char* i_drive) {
    s32 size;

    if (l_InitedMutex != 0) {
        OSLockMutex(&l_Mutex);
    }

    if (i_drive != 0) {
        int arg = dHash_GetArg(i_drive);
        size = VFSysGetDriveFreeSize(arg);
    } else {
        VFSysSetLastError(-1);
        size = -1;
    }

    if (l_InitedMutex != 0) {
        OSUnlockMutex(&l_Mutex);
    }

    return size;
}

s32 VFSetSyncMode(const char* i_drive, u32 i_mode) {
    s32 result;

    if (l_InitedMutex != 0) {
        OSLockMutex(&l_Mutex);
    }

    if (i_drive != 0) {
        int arg = dHash_GetArg(i_drive);
        result = VFSysSetSyncMode(arg, i_mode);
    } else {
        result = -1;
    }

    VFSysSetLastError(result);

    if (l_InitedMutex != 0) {
        OSUnlockMutex(&l_Mutex);
    }

    return result;
}
