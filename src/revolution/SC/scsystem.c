#include <revolution/SC.h>
#include <string.h>

#define SYSCONF_SIZE 0x4000
#define SYSCONF_BEGIN_MAGIC "SCv0"
#define SYSCONF_END_MAGIC "SCed"

const char* __SCVersion =
    "<< RVL_SDK - SC \trelease build: Nov 30 2006 03:33:00 (0x4199_60831) >>";

static SCControl Control;
static u8 ConfBuf[SYSCONF_SIZE] ALIGN(32);
static u8 ConfBufForFlush[SYSCONF_SIZE] ALIGN(32);

static const char ConfDirName[] = "/shared2/sys";
static const char ConfFileName[] = "/shared2/sys/SYSCONF";
static const char ProductInfoFileName[] =
    "/title/00000001/00000002/data/setting.txt";

static u8 BgJobStatus;
static u32 ItemRestSize;
static u32 ItemNumTotal;
static u32 ItemIDMaxPlus1;
static u32 ItemIDOffsetTblOffset;
static u8 IsDevKit;
static u8 DirtyFlag;
static u8 Initialized;

typedef struct SCConfHeader {
    u32 magic;         // at 0x0
    u16 numItems;      // at 0x4
    u16 itemOffsets[]; // at 0x6
    // . . .
} SCConfHeader;

static void SetBgJobStatus(SCStatus status);
static s32 SCReloadConfFileAsync(u8* buf, u32 size, SCAsyncCallback callback);
static void OpenCallbackFromReload(s32 result, NANDCommandBlock* block);
static void ReadCallbackFromReload(s32 result, NANDCommandBlock* block);
static void CloseCallbackFromReload(s32 result, NANDCommandBlock* block);
static void FinishFromReload(void);
static void ErrorFromReload(s32 result);
static void CloseCallbackFromReloadError(s32 result, NANDCommandBlock* block);
static void ClearConfBuf(u8* conf);
static s32 ParseConfBuf(u8* conf, u32 size);
static BOOL UnpackItem(const u8* data, SCItem* item);
static void MyNandCallback(s32 result, NANDCommandBlock* block);
static void FinishFromFlush(void);
static void ErrorFromFlush(void);

void SCInit(void) {
    BOOL enabled = OSDisableInterrupts();

    if (Initialized) {
        OSRestoreInterrupts(enabled);
        return;
    }

    Initialized = TRUE;
    SetBgJobStatus(SC_STATUS_1);
    OSRestoreInterrupts(enabled);

    OSRegisterVersion(__SCVersion);
    OSInitThreadQueue(&Control.threadQueue);

    if (OSGetConsoleType() & OS_CONSOLE_MASK_EMU) {
        IsDevKit = TRUE;
    }

    if (NANDInit() == NAND_RESULT_OK &&
        SCReloadConfFileAsync(__SCGetConfBuf(), __SCGetConfBufSize(),
                              SC_CONF_FILE_SYSTEM) == NAND_RESULT_OK) {
        return;
    }

    SetBgJobStatus(SC_STATUS_2);
}

static void SetBgJobStatus(SCStatus status) { BgJobStatus = status; }

u32 SCCheckStatus(void) {
    BOOL enabled;
    u32 status;

    enabled = OSDisableInterrupts();
    status = BgJobStatus;

    if (status == SC_STATUS_3) {
        SetBgJobStatus(SC_STATUS_1);
        OSRestoreInterrupts(enabled);

        if (ParseConfBuf(Control.fileBuffers[SC_CONF_FILE_SYSTEM],
                         Control.fileSizes[SC_CONF_FILE_SYSTEM]) == 0) {
            enabled = OSDisableInterrupts();
            if (__SCGetConfBuf() != Control.fileBuffers[SC_CONF_FILE_SYSTEM]) {
                memcpy(__SCGetConfBuf(),
                       Control.fileBuffers[SC_CONF_FILE_SYSTEM],
                       __SCGetConfBufSize());
            }
            __SCClearDirtyFlag();
            OSRestoreInterrupts(enabled);
        } else {
            enabled = OSDisableInterrupts();
            ClearConfBuf(Control.fileBuffers[SC_CONF_FILE_SYSTEM]);
            __SCClearDirtyFlag();
            OSRestoreInterrupts(enabled);
        }

        status = SC_STATUS_0;
        SetBgJobStatus(SC_STATUS_0);
    } else {
        OSRestoreInterrupts(enabled);
    }

    return status;
}

static s32 SCReloadConfFileAsync(u8* buf, u32 size, SCAsyncCallback callback) {
    int i;

    if (size < __SCGetConfBufSize()) {
        return NAND_RESULT_FATAL_ERROR;
    }

    SetBgJobStatus(SC_STATUS_1);
    Control.asyncCallback = callback;
    Control.asyncResult = NAND_RESULT_OK;
    Control.openFile = 0;

    for (i = 0; i < SC_CONF_FILE_MAX; i++) {
        Control.fileSizes[i] = 0;
    }

    Control.filePaths[SC_CONF_FILE_SYSTEM] = ConfFileName;
    Control.filePaths[SC_CONF_FILE_PRODUCT] = ProductInfoFileName;

    Control.fileBuffers[SC_CONF_FILE_SYSTEM] = buf;
    Control.fileBuffers[SC_CONF_FILE_PRODUCT] =
        (u8*)OSPhysicalToCached(OS_PHYS_SC_PRDINFO);

    Control.bufferSizes[SC_CONF_FILE_SYSTEM] = __SCGetConfBufSize();
    Control.bufferSizes[SC_CONF_FILE_PRODUCT] = SC_PRDINFO_SIZE;

    ClearConfBuf(buf);

    ItemIDOffsetTblOffset = 0;
    ItemNumTotal = 0;
    ItemRestSize = 0;
    Control.BYTE_0x155 = 0;

    return NANDPrivateOpenAsync(Control.filePaths[Control.openFile],
                                &Control.fileInfo, NAND_ACCESS_READ,
                                OpenCallbackFromReload, &Control.commandBlock);
}

static void OpenCallbackFromReload(s32 result, NANDCommandBlock* block) {
#pragma unused(block)

    if (result == NAND_RESULT_OK) {
        Control.BYTE_0x155 = 1;

        if (NANDReadAsync(
                &Control.fileInfo, Control.fileBuffers[Control.openFile],
                Control.bufferSizes[Control.openFile], ReadCallbackFromReload,
                &Control.commandBlock) == NAND_RESULT_OK) {
            return;
        }
    }

    ErrorFromReload(result);
}

static void ReadCallbackFromReload(s32 result, NANDCommandBlock* block) {
#pragma unused(block)

    if (result == Control.bufferSizes[Control.openFile]) {
        Control.fileSizes[Control.openFile] = result;
        Control.BYTE_0x155 = 0;
        if (NANDCloseAsync(&Control.fileInfo, CloseCallbackFromReload,
                           &Control.commandBlock) == NAND_RESULT_OK) {
            return;
        }
    }

    ErrorFromReload((result != NAND_RESULT_OK) ? result
                                               : NAND_RESULT_FATAL_ERROR);
}

static void CloseCallbackFromReload(s32 result, NANDCommandBlock* block) {
#pragma unused(block)

    if (result == NAND_RESULT_OK) {
        FinishFromReload();
    } else {
        ErrorFromReload(result);
    }
}

static void FinishFromReload(void) {
    SCStatus status;

openFile:
    Control.openFile++;
    if (Control.openFile < SC_CONF_FILE_MAX) {
        Control.BYTE_0x155 = 0;
        if (NANDPrivateOpenAsync(Control.filePaths[Control.openFile],
                                 &Control.fileInfo, NAND_ACCESS_READ,
                                 OpenCallbackFromReload,
                                 &Control.commandBlock) == NAND_RESULT_OK) {
            return;
        }

        goto openFile;
    }

    switch (Control.asyncResult) {
    case NAND_RESULT_OK:
        status = SC_STATUS_3;
        break;
    case NAND_RESULT_NOEXISTS:
    default:
        ClearConfBuf(Control.fileBuffers[SC_CONF_FILE_SYSTEM]);
        status = SC_STATUS_3;
        Control.fileSizes[SC_CONF_FILE_SYSTEM] =
            Control.bufferSizes[SC_CONF_FILE_SYSTEM];
        break;
    }

    *((u8*)OSPhysicalToCached(OS_PHYS_SC_PRDINFO) + SC_PRDINFO_SIZE - 1) = '\0';

    if (Control.asyncCallback != NULL) {
        Control.asyncCallback(Control.asyncResult);
        Control.asyncCallback = NULL;
    }

    SetBgJobStatus(status);
}

static void ErrorFromReload(s32 result) {
    if (Control.openFile == SC_CONF_FILE_SYSTEM) {
        Control.asyncResult = result;
    }

    Control.fileSizes[Control.openFile] = 0;

    if (Control.BYTE_0x155 == 0 ||
        NANDCloseAsync(&Control.fileInfo, CloseCallbackFromReloadError,
                       &Control.commandBlock) != NAND_RESULT_OK) {
        FinishFromReload();
    }
}

static void CloseCallbackFromReloadError(s32 result, NANDCommandBlock* block) {
#pragma unused(result)
#pragma unused(block)

    FinishFromReload();
}

static void ClearConfBuf(u8* conf) {
    u8* end;
    u32 size;
    SCConfHeader* header;

    header = (SCConfHeader*)conf;
    size = __SCGetConfBufSize();
    memset(conf, 0, size);

    if (size > 0xC) {
        memcpy(conf, SYSCONF_BEGIN_MAGIC, 4);

        end = conf + size - 4;
        memcpy(end, SYSCONF_END_MAGIC, 4);

        header->itemOffsets[0] = 8;
    }
}

#ifdef __DECOMP_NON_MATCHING
static s32 ParseConfBuf(u8* conf, u32 size) {
    ;
    ;
}
#else
#error This file has not yet been decompiled accurately. Use "scsystem.s" instead.
#endif

static BOOL UnpackItem(const u8* data, SCItem* item) {
    u8 type;

    memset(item, 0, sizeof(SCItem));
    type = *data & 0b11100000;
    item->name = (const char*)data + 1;
    item->nameLen = (*data & 0b00011111) + 1;
    item->data = (u8*)(data + item->nameLen + 1);

    switch (type) {
    case SC_ITEM_BYTE:
    case SC_ITEM_BOOL:
        item->dataLen = 1;
        break;
    case SC_ITEM_SHORT:
        item->dataLen = 2;
        break;
    case SC_ITEM_LONG:
        item->dataLen = 4;
        break;
    case SC_ITEM_LONGLONG:
        item->dataLen = 8;
        break;
    case SC_ITEM_SMALLARRAY:
        item->dataLen = *item->data + sizeof(u8);
        item->data = item->data + sizeof(u8);
        item->itemLen += sizeof(u8);
        break;
    case SC_ITEM_BIGARRAY:
        item->dataLen = (*item->data << 8 | *(item->data + 1)) + sizeof(u8);
        item->data = item->data + sizeof(u16);
        item->itemLen += sizeof(u16);
        break;
    default:
        goto exit;
    }

    if (type == SC_ITEM_SMALLARRAY || type == SC_ITEM_BIGARRAY) {
        // ???
        item->arrayType = SC_ITEM_SMALLARRAY;
    } else {
        item->primType = type;
        memcpy(item, item->data, item->dataLen);
    }

    item->itemLen += item->nameLen + item->dataLen + sizeof(u8);

exit:
    return item->dataLen != 0;
}

static BOOL FindItemByID(SCItemID id, SCItem* item) {
    u8* conf;
    u16* ofsTbl;
    u16 itemOfs;

    conf = __SCGetConfBuf();
    if (id < ItemIDMaxPlus1 && ItemIDOffsetTblOffset > 0) {
        ofsTbl = (u16*)(conf + ItemIDOffsetTblOffset);
        itemOfs = ofsTbl[-id];

        if (itemOfs > 0) {
            return UnpackItem(conf + *(u16*)(conf + itemOfs), item);
        }
    }

    return FALSE;
}

#ifdef __DECOMP_NON_MATCHING
static void DeleteItemByID(SCItemID id) {
    ;
    ;
}
#else
#error This file has not yet been decompiled accurately. Use "scsystem.s" instead.
#endif

#ifdef __DECOMP_NON_MATCHING
static BOOL CreateItemByID(SCItemID id, u8 primType, const void* src, u32 len) {
    ;
    ;
}
#else
#error This file has not yet been decompiled accurately. Use "scsystem.s" instead.
#endif

BOOL SCFindByteArrayItem(void* dst, u32 len, SCItemID id) {
    BOOL success;
    BOOL enabled;
    SCItem item;

    success = FALSE;
    enabled = OSDisableInterrupts();

    if (dst != ((void*)NULL) && FindItemByID(id, &item) &&
        item.arrayType != 0 && item.dataLen == len) {
        memcpy(dst, item.data, len);
        success = TRUE;
    }

    OSRestoreInterrupts(enabled);
    return success;
}

BOOL SCReplaceByteArrayItem(const void* src, u32 len, SCItemID id) {
    SCItem item;
    BOOL success;
    BOOL enabled;

    success = FALSE;
    enabled = OSDisableInterrupts();

    if (src != ((void*)NULL)) {
        if (FindItemByID(id, &item)) {
            if (item.arrayType != 0 && item.dataLen == len) {
                if (memcmp(item.data, src, len) != 0) {
                    memcpy(item.data, src, len);
                    __SCSetDirtyFlag();
                }
                success = TRUE;
                goto exit;

            } else {
                DeleteItemByID(id);
            }
        }

        success = CreateItemByID(id, SC_ITEM_SMALLARRAY, src, len);
    }
exit:
    OSRestoreInterrupts(enabled);
    return success;
}

static BOOL SCFindIntegerItem(void* dst, SCItemID id, u8 primType) {
    BOOL success;
    BOOL enabled;
    SCItem item;

    success = FALSE;
    enabled = OSDisableInterrupts();

    if (FindItemByID(id, &item) && item.primType == primType) {
        memcpy(dst, item.data, item.dataLen);
        success = TRUE;
    }

    OSRestoreInterrupts(enabled);
    return success;
}

static BOOL SCReplaceIntegerItem(const void* src, SCItemID id,
                                 u8 primType) DONT_INLINE {
    BOOL success;
    BOOL enabled;
    SCItem item;

    success = FALSE;
    enabled = OSDisableInterrupts();

    if (FindItemByID(id, &item)) {
        if (item.primType == primType) {
            if (memcmp(item.data, src, item.dataLen) != 0) {
                memcpy(item.data, src, item.dataLen);
                __SCSetDirtyFlag();
            }
            success = TRUE;
            goto exit;

        } else {
            DeleteItemByID(id);
        }
    }

    success = CreateItemByID(id, primType, src, 0);

exit:
    OSRestoreInterrupts(enabled);
    return success;
}

BOOL SCFindU8Item(u8* dst, SCItemID id) {
    return SCFindIntegerItem(dst, id, SC_ITEM_BYTE);
}

BOOL SCFindS8Item(s8* dst, SCItemID id) {
    return SCFindIntegerItem(dst, id, SC_ITEM_BYTE);
}

BOOL SCFindU32Item(u32* dst, SCItemID id) {
    return SCFindIntegerItem(dst, id, SC_ITEM_LONG);
}

BOOL SCReplaceU8Item(u8 data, SCItemID id) {
    SCReplaceIntegerItem(&data, id, SC_ITEM_BYTE);
}

static void __SCFlushSyncCallback(SCStatus status) {
#pragma unused(status)

    OSWakeupThread(&Control.threadQueue);
}

void SCFlushAsync(SCFlushCallback callback) {
    SCControl* ctrl;
    BOOL enabled;
    u8 status;
    u8* conf;

    ctrl = &Control;
    enabled = OSDisableInterrupts();
    status = BgJobStatus;

    if (status == SC_STATUS_0) {
        SetBgJobStatus(SC_STATUS_1);

        if (callback == ((void*)NULL)) {
            callback = __SCFlushSyncCallback;
        }

        ctrl->flushCallback = callback;
        ctrl->flushStatus = SC_STATUS_0;
        ctrl->BYTE_0x155 = 0;
        ctrl->flushSize = __SCGetConfBufSize();

        if (!__SCIsDirty()) {
            OSRestoreInterrupts(enabled);
            FinishFromFlush();
        } else {
            __SCClearDirtyFlag();
            memcpy(ConfBufForFlush, __SCGetConfBuf(), __SCGetConfBufSize());
            OSRestoreInterrupts(enabled);
            ctrl->nandCbState = 0;

            if (NANDPrivateGetTypeAsync(ConfFileName, &ctrl->fileAttr.BYTE_0x0,
                                        MyNandCallback, &ctrl->commandBlock) !=
                NAND_RESULT_OK) {
                ErrorFromFlush();
            }
        }
    } else {
        if (callback != NULL) {
            callback(status == SC_STATUS_1 ? status : SC_STATUS_2);
        }
        OSRestoreInterrupts(enabled);
    }
}

static void MyNandCallback(s32 result, NANDCommandBlock* block) {
#pragma unused(block)

    SCControl* ctrl = &Control;

    switch (ctrl->nandCbState) {
    case 0:
        if (result == NAND_RESULT_OK && ctrl->fileAttr.BYTE_0x0 == 1) {
            ctrl->nandCbState = 1;
            if (NANDPrivateGetStatusAsync(
                    ConfFileName, &ctrl->fileAttr, MyNandCallback,
                    &ctrl->commandBlock) != NAND_RESULT_OK) {
                goto error;
            }
        } else {
            goto case_1_lbl;
        }
        return;
    case 1:
        if (result == NAND_RESULT_OK && ctrl->fileAttr.perm == '?') {
            goto case_5_lbl;
        }

    case_1_lbl:
        ctrl->nandCbState = 2;
        if (NANDPrivateDeleteAsync(ConfFileName, MyNandCallback,
                                   &ctrl->commandBlock) != NAND_RESULT_OK) {
            goto error;
        }
        return;
    case 2:
        ctrl->nandCbState = 3;
        if (NANDPrivateGetTypeAsync(ConfDirName, &ctrl->fileAttr.BYTE_0x0,
                                    MyNandCallback,
                                    &ctrl->commandBlock) != NAND_RESULT_OK) {
            goto error;
        }
        return;
    case 3:
        if (result == NAND_RESULT_OK && ctrl->fileAttr.BYTE_0x0 == 2) {
            goto case_4_lbl;
        }
        ctrl->nandCbState = 4;
        if (NANDPrivateCreateDirAsync(ConfDirName, NAND_PERM_RWALL, 0,
                                      MyNandCallback,
                                      &ctrl->commandBlock) != NAND_RESULT_OK) {
            goto error;
        }
        return;
    case 4:
    case_4_lbl:
        ctrl->nandCbState = 5;
        if (NANDPrivateCreateAsync(ConfFileName, NAND_PERM_RWALL, 0,
                                   MyNandCallback,
                                   &ctrl->commandBlock) != NAND_RESULT_OK) {
            goto error;
        }
        return;
    case 5:
    case_5_lbl:
        ctrl->nandCbState = 6;
        if (NANDPrivateOpenAsync(ConfFileName, &ctrl->fileInfo,
                                 NAND_ACCESS_WRITE, MyNandCallback,
                                 &ctrl->commandBlock) != NAND_RESULT_OK) {
            goto error;
        }
        return;
    case 6:
        if (result != NAND_RESULT_OK) {
            goto error;
        }
        ctrl->BYTE_0x155 = 1;
        ctrl->nandCbState = 7;
        if (NANDWriteAsync(&ctrl->fileInfo, ConfBufForFlush, ctrl->flushSize,
                           MyNandCallback,
                           &ctrl->commandBlock) != NAND_RESULT_OK) {
            goto error;
        }
        return;
    case 7:
        if (result != ctrl->flushSize) {
            goto error;
        }
        ctrl->BYTE_0x155 = 0;
        ctrl->nandCbState = 8;
        if (NANDCloseAsync(&ctrl->fileInfo, MyNandCallback,
                           &ctrl->commandBlock) != NAND_RESULT_OK) {
            goto error;
        }
        return;
    case 8:
        if (result != NAND_RESULT_OK) {
            goto error;
        }
        // FALLTHROUGH
    case 9:
        FinishFromFlush();
        // FALLTHROUGH
    default:
        return;
    }

error:
    ErrorFromFlush();
}

static void FinishFromFlush(void) {
    SCControl* ctrl;
    SCFlushCallback callback;

    ctrl = &Control;
    if (ctrl->flushStatus != SC_STATUS_0) {
        __SCSetDirtyFlag();
    }

    callback = ctrl->flushCallback;
    if (callback != NULL) {
        ctrl->flushCallback = NULL;
        callback(ctrl->flushStatus);

        if (ctrl->threadQueue.head != ((void*)NULL)) {
            OSWakeupThread(&ctrl->threadQueue);
        }
    }

    SetBgJobStatus(ctrl->flushStatus);
}

static void ErrorFromFlush(void) {
    SCControl* ctrl;

    ctrl = &Control;
    ctrl->flushStatus = SC_STATUS_2;

    if (ctrl->BYTE_0x155 != 0) {
        ctrl->nandCbState = 9;
        if (NANDCloseAsync(&ctrl->fileInfo, MyNandCallback,
                           &ctrl->commandBlock) == NAND_RESULT_OK) {
            return;
        }
    }

    FinishFromFlush();
}

BOOL __SCIsDirty(void) { return DirtyFlag != FALSE ? TRUE : FALSE; }

void __SCSetDirtyFlag(void) { DirtyFlag = TRUE; }

void __SCClearDirtyFlag(void) { DirtyFlag = FALSE; }

u8* __SCGetConfBuf(void) { return ConfBuf; }

u32 __SCGetConfBufSize(void) { return SYSCONF_SIZE; }
