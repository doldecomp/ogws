#include <revolution/VF.h>
#include <revolution/OS.h>

static OSMutex l_Mutex;
static s32 l_vf_init;
static s32 l_InitedMutex;

s32 VFIsAvailable(void) {
    return l_vf_init != 0;
}

void VFInitEx(void* param_1, u32 param_2) {
    if (l_InitedMutex == 0) {
        OSInitMutex(&l_Mutex);
        l_InitedMutex = 1;
    }

    if (l_InitedMutex != 0) {
        OSLockMutex(&l_Mutex);
    }

    if (l_vf_init == 0) {
        l_vf_init = 1;
        VFSysInit(param_1, param_2);
        VFipdm_init_diskmanager(0, 0);
        VFipf2_init_prfile2(0, 0);
        dHash_InitHashTable();
    }

    if (l_InitedMutex != 0) {
        OSUnlockMutex(&l_Mutex);
    }
}

VFError VF_activate_drive_common(unsigned int drivePtr, char *path, int param_3) {
    VFError err;
    int driveP;
    int stack_buf[2];

    err = VFSysCheckExistPrfFile((char*)drivePtr);
    if (err != 0) {
        VFSysSetLastError(err);
        return err;
    }

    err = VFSysMountDrv(drivePtr, path, param_3);
    if (err != 0) {
        VFSysSetLastError(err);
        return err;
    }

    driveP = VFSysGetDriveP(drivePtr);
    if (driveP == 0) {
        VFSysSetLastError(VF_ERR_GENERIC);
        return VF_ERR_GENERIC;
    }

    stack_buf[0] = driveP + 8;
    stack_buf[1] = 0;
    err = VFipf2_attach(stack_buf);
    if (err != 0) {
        err = VFipf2_errnum();
        VFSysSetLastError(err);
        VFipdm_close_partition(*(int*)(driveP + 0x14));
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

char *VF_path2handleidx(int *handleIdxPtr, char *path) {
    char driveName[8];
    char *drive_ptr;
    char *path_ptr;
    char c;
    int handle;
    int i;
    char *ret;
    char new_var;
    i = 0;
    *handleIdxPtr = -1;
    path_ptr = path;
    ret = path;
    VFipf_memset(driveName, 0, 8);
    drive_ptr = driveName;
    // TODO(Alex9303) Permuter fake(?)match
    while ((new_var = *path_ptr) != '\0') {
        c = new_var;
        if ((c == '\\') || (c == '/')) {
            break;
        }
        if (c == ':') {
            handle = dHash_GetArg(driveName);
            *handleIdxPtr = handle;
            if ((handle == (-1)) || (i > 7)) {
                ret = 0;
            } else {
                ret = path_ptr + 1;
            }
            break;
        }
        if (i < 7) {
            *drive_ptr = c;
        }
        path_ptr++;
        drive_ptr++;
        i++;
    }

    return ret;
}

VFFile VFOpenFile(const char* i_path_p, const char* i_mode, u32 i_attr) {
    int handleIdx = -1;
    VFFile result;
    char *relativePath;

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
    int handleIdx = -1;
    s32 result;
    char *relativePath;

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
