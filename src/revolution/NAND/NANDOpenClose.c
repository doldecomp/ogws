#include <revolution/NAND.h>
#include <revolution/OS.h>
#include <stdio.h>

static void nandOpenCallback(s32 result, void* arg);
static s32 nandSafeOpenAsync(const char* path, NANDFileInfo* info, u8 access,
                             void* buffer, u32 bufferSize,
                             NANDAsyncCallback callback,
                             NANDCommandBlock* block, BOOL priv);
static void nandSafeOpenCallback(s32 result, void* arg);
static void nandReadOpenCallback(s32 result, void* arg);
static s32 nandSafeCloseAsync(NANDFileInfo* info, NANDAsyncCallback callback,
                              NANDCommandBlock* block);
static void nandSafeCloseCallback(s32 result, void* arg);
static void nandReadCloseCallback(s32 result, void* arg);
static void nandCloseCallback(s32 result, void* arg);
static u32 nandGetUniqueNumber(void);

static s32 nandOpen(const char* path, u8 mode, NANDCommandBlock* block,
                    BOOL async, BOOL priv) {
    IPCOpenMode ipcMode;
    char absPath[64];

    MEMCLR(&absPath);
    ipcMode = IPC_OPEN_NONE;
    nandGenerateAbsPath(absPath, path);

    if (!priv && nandIsPrivatePath(absPath)) {
        return IPC_RESULT_ACCESS;
    }

    switch (mode) {
    case NAND_ACCESS_RW:
        ipcMode = IPC_OPEN_RW;
        break;
    case NAND_ACCESS_READ:
        ipcMode = IPC_OPEN_READ;
        break;
    case NAND_ACCESS_WRITE:
        ipcMode = IPC_OPEN_WRITE;
        break;
    }

    if (async) {
        return ISFS_OpenAsync(absPath, ipcMode, nandOpenCallback, block);
    } else {
        return ISFS_Open(absPath, ipcMode);
    }
}

s32 NANDOpen(const char* path, NANDFileInfo* info, u8 mode) {
    s32 result;

    if (!nandIsInitialized()) {
        return NAND_RESULT_FATAL_ERROR;
    }

    result = nandOpen(path, mode, NULL, FALSE, FALSE);
    if (result >= 0) {
        info->fd = result;
        info->mark = 1;
        return NAND_RESULT_OK;
    }

    return nandConvertErrorCode(result);
}

s32 NANDPrivateOpen(const char* path, NANDFileInfo* info, u8 mode) {
    s32 result;

    if (!nandIsInitialized()) {
        return NAND_RESULT_FATAL_ERROR;
    }

    result = nandOpen(path, mode, NULL, FALSE, TRUE);
    if (result >= 0) {
        info->fd = result;
        info->mark = 1;
        return NAND_RESULT_OK;
    }

    return nandConvertErrorCode(result);
}

s32 NANDOpenAsync(const char* path, NANDFileInfo* info, u8 mode,
                  NANDAsyncCallback callback, NANDCommandBlock* block) {
    if (!nandIsInitialized()) {
        return NAND_RESULT_FATAL_ERROR;
    }

    block->callback = callback;
    block->info = info;
    return nandConvertErrorCode(nandOpen(path, mode, block, TRUE, FALSE));
}

s32 NANDPrivateOpenAsync(const char* path, NANDFileInfo* info, u8 mode,
                         NANDAsyncCallback callback, NANDCommandBlock* block) {
    if (!nandIsInitialized()) {
        return NAND_RESULT_FATAL_ERROR;
    }

    block->callback = callback;
    block->info = info;
    return nandConvertErrorCode(nandOpen(path, mode, block, TRUE, TRUE));
}

static void nandOpenCallback(s32 result, void* arg) {
    NANDCommandBlock* block = (NANDCommandBlock*)arg;

    if (result >= 0) {
        block->info->fd = result;
        block->info->stage = 2;
        block->info->mark = 1;
        block->callback(NAND_RESULT_OK, block);
    } else {
        block->callback(nandConvertErrorCode(result), block);
    }
}

s32 NANDClose(NANDFileInfo* info) {
    s32 result;

    if (!nandIsInitialized()) {
        return NAND_RESULT_FATAL_ERROR;
    }

    if (info->mark != 1) {
        return NAND_RESULT_INVALID;
    }

    result = ISFS_Close(info->fd);
    if (result == IPC_RESULT_OK) {
        info->mark = 2;
    }

    return nandConvertErrorCode(result);
}

s32 NANDCloseAsync(NANDFileInfo* info, NANDAsyncCallback callback,
                   NANDCommandBlock* block) {
    if (!nandIsInitialized()) {
        return NAND_RESULT_FATAL_ERROR;
    }

    if (info->mark != 1) {
        return NAND_RESULT_INVALID;
    }

    block->callback = callback;
    block->info = info;
    return nandConvertErrorCode(
        ISFS_CloseAsync(info->fd, nandCloseCallback, block));
}

s32 NANDPrivateSafeOpenAsync(const char* path, NANDFileInfo* info, u8 access,
                             void* buffer, u32 bufferSize,
                             NANDAsyncCallback callback,
                             NANDCommandBlock* block) {
    return nandSafeOpenAsync(path, info, access, buffer, bufferSize, callback,
                             block, TRUE);
}

static s32 nandSafeOpenAsync(const char* path, NANDFileInfo* info, u8 access,
                             void* buffer, u32 bufferSize,
                             NANDAsyncCallback callback,
                             NANDCommandBlock* block, BOOL priv) {
    s32 result;

    if (!nandIsInitialized()) {
        return NAND_RESULT_FATAL_ERROR;
    }

    info->access = access;
    info->stage = 0;

    nandGenerateAbsPath(info->openPath, path);

    if (!priv && nandIsPrivatePath(info->openPath)) {
        return NAND_RESULT_ACCESS;
    }

    if (access == NAND_ACCESS_READ) {
        block->info = info;
        block->callback = callback;
        result = ISFS_OpenAsync(info->openPath, IPC_OPEN_READ,
                                nandReadOpenCallback, block);
        return (result == IPC_RESULT_OK) ? NAND_RESULT_OK
                                         : nandConvertErrorCode(result);
    }

    if (access == NAND_ACCESS_WRITE || access == NAND_ACCESS_RW) {
        block->info = info;
        block->callback = callback;
        block->state = 0;
        block->buffer = buffer;
        block->bufferSize = bufferSize;
        result = ISFS_CreateDirAsync("/tmp/sys", 0, IPC_OPEN_RW, IPC_OPEN_RW,
                                     IPC_OPEN_RW, nandSafeOpenCallback, block);
        return (result == IPC_RESULT_OK) ? NAND_RESULT_OK
                                         : nandConvertErrorCode(result);
    }

    return NAND_RESULT_INVALID;
}

static void nandSafeOpenCallback(s32 result, void* arg) {
// Why???
#define block ((NANDCommandBlock*)arg)

    s32 myResult;
    char tempPath[64];
    char relativeName[12];

    if (result >= 0 || (result == IPC_RESULT_EXISTS && block->state == 0)) {
        NANDFileInfo* info = block->info;
        myResult = -117;

        if (block->state == 0) {
            info->stage = 1;
        }

        block->state++;

        if (block->state == 1) {
            myResult = ISFS_GetAttrAsync(
                info->openPath, &block->ownerId, &block->groupId, &block->attr,
                &block->ownerPerm, &block->groupPerm, &block->otherPerm,
                nandSafeOpenCallback, block);
        } else if (block->state == 2) {
            myResult = ISFS_OpenAsync(info->openPath, IPC_OPEN_READ,
                                      nandSafeOpenCallback, block);
        } else if (block->state == 3) {
            info->stage = 2;
            block->uniqueNo = nandGetUniqueNumber();
            info->tempFd = result;
            sprintf(tempPath, "%s/%08x", "/tmp/sys", block->uniqueNo);
            myResult =
                ISFS_CreateDirAsync(tempPath, 0, IPC_OPEN_RW, IPC_OPEN_NONE,
                                    IPC_OPEN_NONE, nandSafeOpenCallback, block);
        } else if (block->state == 4) {
            info->stage = 3;
            nandGetRelativeName(relativeName, info->openPath);
            sprintf(info->tempPath, "%s/%08x/%s", "/tmp/sys", block->uniqueNo,
                    relativeName);
            myResult = ISFS_CreateFileAsync(
                info->tempPath, block->attr, block->ownerPerm, block->groupPerm,
                block->otherPerm, nandSafeOpenCallback, block);
        } else if (block->state == 5) {
            info->stage = 4;
            if (info->access == NAND_ACCESS_WRITE) {
                myResult = ISFS_OpenAsync(info->tempPath, IPC_OPEN_WRITE,
                                          nandSafeOpenCallback, block);
            } else if (info->access == NAND_ACCESS_RW) {
                myResult = ISFS_OpenAsync(info->tempPath, IPC_OPEN_RW,
                                          nandSafeOpenCallback, block);
            } else {
                myResult = -117;
            }
        } else if (block->state == 6) {
            info->fd = result;
            info->stage = 5;
            block->state = 7;
            myResult =
                ISFS_ReadAsync(info->tempFd, block->buffer, block->bufferSize,
                               nandSafeOpenCallback, block);
        } else if (block->state == 7) {
            myResult =
                ISFS_ReadAsync(info->tempFd, block->buffer, block->bufferSize,
                               nandSafeOpenCallback, block);
        } else if (block->state == 8) {
            if (result > 0) {
                block->state = 6;
                myResult = ISFS_WriteAsync(info->fd, block->buffer, result,
                                           nandSafeOpenCallback, block);
            } else if (result == IPC_RESULT_OK) {
                myResult = ISFS_SeekAsync(info->fd, 0, IPC_SEEK_BEG,
                                          nandSafeOpenCallback, block);
            }
        } else if (block->state == 9) {
            if (result == IPC_RESULT_OK) {
                info->mark = 3;
                block->callback(nandConvertErrorCode(IPC_RESULT_OK), block);
            } else {
                block->callback(nandConvertErrorCode(result), block);
            }
            return;
        }

        if (myResult != IPC_RESULT_OK) {
            block->callback(nandConvertErrorCode(myResult), block);
        }
        return;
    }

    block->callback(nandConvertErrorCode(result), block);

#undef block
}

static void nandReadOpenCallback(s32 result, void* arg) {
    NANDCommandBlock* block = (NANDCommandBlock*)arg;

    if (result >= 0) {
        block->info->fd = result;
        block->info->stage = 2;
        block->info->mark = 3;
        block->callback(NAND_RESULT_OK, block);
    } else {
        block->callback(nandConvertErrorCode(result), block);
    }
}

s32 NANDSafeCloseAsync(NANDFileInfo* info, NANDAsyncCallback callback,
                       NANDCommandBlock* block) {
    s32 result;

    if (!nandIsInitialized()) {
        return NAND_RESULT_FATAL_ERROR;
    }

    if (info->mark != 3) {
        return NAND_RESULT_INVALID;
    }

    if (info->access == NAND_ACCESS_READ) {
        block->info = info;
        block->callback = callback;
        result = ISFS_CloseAsync(info->fd, nandReadCloseCallback, block);
    } else if (info->access == NAND_ACCESS_WRITE ||
               info->access == NAND_ACCESS_RW) {
        block->info = info;
        block->callback = callback;
        block->state = 10;
        result = ISFS_CloseAsync(info->fd, nandSafeCloseCallback, block);
    } else {
        result = IPC_RESULT_INVALID;
    }

    return nandConvertErrorCode(result);
}

static void nandSafeCloseCallback(s32 result, void* arg) {
    s32 myResult;
    NANDCommandBlock* block = (NANDCommandBlock*)arg;

    if (result == IPC_RESULT_OK) {
        NANDFileInfo* info = block->info;
        myResult = -117;

        block->state++;

        if (block->state == 11) {
            info->stage = 6;
            myResult =
                ISFS_CloseAsync(info->tempFd, nandSafeCloseCallback, block);
        } else if (block->state == 12) {
            info->stage = 7;
            myResult = ISFS_RenameAsync(info->tempPath, info->openPath,
                                        nandSafeCloseCallback, block);
        } else if (block->state == 13) {
            char parentDir[64];
            MEMCLR(&parentDir);

            info->stage = 8;
            nandGetParentDirectory(parentDir, info->tempPath);
            myResult =
                ISFS_DeleteAsync(parentDir, nandSafeCloseCallback, block);
        } else if (block->state == 14) {
            info->stage = 9;
            info->mark = 4;
            block->callback(nandConvertErrorCode(result), block);
            return;
        }

        if (myResult != IPC_RESULT_OK) {
            block->callback(nandConvertErrorCode(myResult), block);
        }
        return;
    }

    block->callback(nandConvertErrorCode(result), block);
}

static void nandReadCloseCallback(s32 result, void* arg) {
    NANDCommandBlock* block = (NANDCommandBlock*)arg;

    if (result == IPC_RESULT_OK) {
        block->info->stage = 7;
        block->info->mark = 4;
    }

    block->callback(nandConvertErrorCode(result), block);
}

static void nandCloseCallback(s32 result, void* arg) {
    NANDCommandBlock* block = (NANDCommandBlock*)arg;

    if (result == IPC_RESULT_OK) {
        block->info->stage = 7;
        block->info->mark = 2;
    }

    block->callback(nandConvertErrorCode(result), block);
}

static u32 nandGetUniqueNumber(void) {
    static u32 s_counter = 0;

    BOOL enabled = OSDisableInterrupts();
    u32 num = s_counter++;
    OSRestoreInterrupts(enabled);

    return num;
}
