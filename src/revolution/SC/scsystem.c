#include <revolution/FS.h>
#include <revolution/NAND.h>
#include <revolution/OS.h>
#include <revolution/SC.h>

#include <string.h>

#define SC_CONF_MIN_SIZE (sizeof(SCConfHeader) + sizeof(u32))
#define SC_CONF_MAX_SIZE 0x4000

#define SC_CONF_BEGIN_MAGIC "SCv0"
#define SC_CONF_END_MAGIC "SCed"

#define SC_SMALLARRAY_MAX 0xFF
#define SC_BIGARRAY_MAX 0xFFFF

typedef enum {
    NAND_CB_STATE_0,
    NAND_CB_STATE_1,
    NAND_CB_STATE_2,
    NAND_CB_STATE_3,
    NAND_CB_STATE_4,
    NAND_CB_STATE_5,
    NAND_CB_STATE_6,
    NAND_CB_STATE_7,
    NAND_CB_STATE_8,
    NAND_CB_STATE_9
} NandCallbackState;

typedef enum {
    SC_CONF_FILE_SYSTEM,  // SYSCONF
    SC_CONF_FILE_PRODUCT, // setting.txt
    SC_CONF_FILE_MAX
} SCConfFile;

typedef enum {
    SC_ITEM_BIGARRAY = (1 << 5),
    SC_ITEM_SMALLARRAY = (2 << 5),
    SC_ITEM_BYTE = (3 << 5),
    SC_ITEM_SHORT = (4 << 5),
    SC_ITEM_LONG = (5 << 5),
    SC_ITEM_LONGLONG = (6 << 5),
    SC_ITEM_BOOL = (7 << 5)
} SCItemType;

typedef void (*SCAsyncCallback)(s32 result);

typedef struct SCConfHeader {
    u32 magic;         // at 0x0
    u16 numItems;      // at 0x4
    u16 itemOffsets[]; // at 0x6
} SCConfHeader;

typedef struct SCConfItem {
    // & 00011111 -> name length (-1)
    // & 11100000 -> item type
    u8 desc;     // at 0x0
    char name[]; // at 0x4
} SCConfItem;

typedef struct SCControl {
    OSThreadQueue threadQueue;     // at 0x0
    NANDFileInfo fileInfo;         // at 0x8
    NANDCommandBlock commandBlock; // at 0x94
    union {
        NANDStatus fileAttr;
        u8 fileType;
    }; // at 0x14C
    u8 nandCbState;                          // at 0x154
    u8 isFileOpen;                           // at 0x155
    u8 openFileType;                         // at 0x156
    SCAsyncCallback asyncCallback;           // at 0x158
    s32 asyncResult;                         // at 0x15C
    const char* filePaths[SC_CONF_FILE_MAX]; // at 0x160
    u8* fileBuffers[SC_CONF_FILE_MAX];       // at 0x168
    u32 bufferSizes[SC_CONF_FILE_MAX];       // at 0x170
    u32 fileSizes[SC_CONF_FILE_MAX];         // at 0x178
    SCFlushCallback flushCallback;           // at 0x180
    SCStatus flushStatus;                    // at 0x184
    u32 flushSize;                           // at 0x188
} SCControl;

typedef struct SCNameAndID {
    const char* name; // at 0x0
    SCItemID id;      // at 0x4
} SCNameAndID;

typedef struct SCItem {
    char UNK_0x0[0x8];
    u8 primType;      // at 0x8
    u8 arrayType;     // at 0x9
    u32 nameLen;      // at 0xC
    u32 dataLen;      // at 0x10
    const char* name; // at 0x14
    u8* data;         // at 0x18
    u32 itemLen;      // at 0x1C
} SCItem;

const char* __SCVersion =
    "<< RVL_SDK - SC \trelease build: Nov 30 2006 03:33:00 (0x4199_60831) >>";

static SCControl Control;
static u8 ConfBuf[SC_CONF_MAX_SIZE] ALIGN(32);
static u8 ConfBufForFlush[SC_CONF_MAX_SIZE] ALIGN(32);

static const char ConfDirName[] = "/shared2/sys";
static const char ConfFileName[] = "/shared2/sys/SYSCONF";
static const char ProductInfoFileName[] =
    "/title/00000001/00000002/data/setting.txt";

static u8 BgJobStatus = SC_STATUS_OK;

static u32 ItemRestSize = 0;
static u32 ItemNumTotal = 0;
static u32 ItemIDMaxPlus1 = 0;
static u32 ItemIDOffsetTblOffset = 0;

static u8 IsDevKit = FALSE;
static u8 DirtyFlag = FALSE;
static u8 Initialized = FALSE;

static SCNameAndID NameAndIDTbl[SC_ITEM_MAX] = {
    {"IPL.CB", SC_ITEM_IPL_CB},     {"IPL.AR", SC_ITEM_IPL_AR},
    {"IPL.ARN", SC_ITEM_IPL_ARN},   {"IPL.CD", SC_ITEM_IPL_CD},
    {"IPL.CD2", SC_ITEM_IPL_CD2},   {"IPL.DH", SC_ITEM_IPL_DH},
    {"IPL.E60", SC_ITEM_IPL_E60},   {"IPL.EULA", SC_ITEM_IPL_EULA},
    {"IPL.FRC", SC_ITEM_IPL_FRC},   {"IPL.IDL", SC_ITEM_IPL_IDL},
    {"IPL.INC", SC_ITEM_IPL_INC},   {"IPL.LNG", SC_ITEM_IPL_LNG},
    {"IPL.NIK", SC_ITEM_IPL_NIK},   {"IPL.PC", SC_ITEM_IPL_PC},
    {"IPL.PGS", SC_ITEM_IPL_PGS},   {"IPL.SSV", SC_ITEM_IPL_SSV},
    {"IPL.SADR", SC_ITEM_IPL_SADR}, {"IPL.SND", SC_ITEM_IPL_SND},
    {"IPL.UPT", SC_ITEM_IPL_UPT},   {"NET.CNF", SC_ITEM_NET_CNF},
    {"NET.CTPC", SC_ITEM_NET_CTPC}, {"NET.PROF", SC_ITEM_NET_PROF},
    {"NET.WCPC", SC_ITEM_NET_WCPC}, {"NET.WCFG", SC_ITEM_NET_WCFG},
    {"DEV.BTM", SC_ITEM_DEV_BTM},   {"DEV.VIM", SC_ITEM_DEV_VIM},
    {"DEV.CTC", SC_ITEM_DEV_CTC},   {"DEV.DSM", SC_ITEM_DEV_DSM},
    {"BT.DINF", SC_ITEM_BT_DINF},   {"BT.SENS", SC_ITEM_BT_SENS},
    {"BT.SPKV", SC_ITEM_BT_SPKV},   {"BT.MOT", SC_ITEM_BT_MOT},
    {"BT.BAR", SC_ITEM_BT_BAR},     {"DVD.CNF", SC_ITEM_DVD_CNF},
    {"WWW.RST", SC_ITEM_WWW_RST}};

static void SetBgJobStatus(SCStatus status);
static s32 SCReloadConfFileAsync(u8* buf, u32 size, SCAsyncCallback callback);
static void OpenCallbackFromReload(s32 result, NANDCommandBlock* block);
static void ReadCallbackFromReload(s32 result, NANDCommandBlock* block);
static void CloseCallbackFromReload(s32 result, NANDCommandBlock* block);
static void FinishFromReload(void);
static void ErrorFromReload(s32 result);
static void CloseCallbackFromReloadError(s32 result, NANDCommandBlock* block);
static void ClearConfBuf(u8* conf);
static SCStatus ParseConfBuf(u8* conf, u32 size);
static BOOL ParseGetBEValue(const u8* start, const u8* end, u32* out, u32 size);
static BOOL UnpackItem(const SCConfItem* raw, SCItem* item);
static void MyNandCallback(s32 result, NANDCommandBlock* block);
static void FinishFromFlush(void);
static void ErrorFromFlush(void);

BOOL __SCIsDirty(void);
void __SCSetDirtyFlag(void);
void __SCClearDirtyFlag(void);
u8* __SCGetConfBuf(void);
u32 __SCGetConfBufSize(void);

void SCInit(void) {
    BOOL enabled = OSDisableInterrupts();

    if (Initialized) {
        OSRestoreInterrupts(enabled);
        return;
    }

    Initialized = TRUE;

    SetBgJobStatus(SC_STATUS_BUSY);
    OSRestoreInterrupts(enabled);

    OSRegisterVersion(__SCVersion);
    OSInitThreadQueue(&Control.threadQueue);

    if (OSGetConsoleType() & OS_CONSOLE_MASK_EMU) {
        IsDevKit = TRUE;
    }

    if (NANDInit() != NAND_RESULT_OK ||
        SCReloadConfFileAsync(__SCGetConfBuf(), __SCGetConfBufSize(), NULL) !=
            NAND_RESULT_OK) {

        SetBgJobStatus(SC_STATUS_FATAL);
    }
}

static void SetBgJobStatus(SCStatus status) {
    BgJobStatus = status;
}

u32 SCCheckStatus(void) {
    BOOL enabled;
    u32 status;

    enabled = OSDisableInterrupts();
    status = BgJobStatus;

    if (status == SC_STATUS_PARSE) {
        SetBgJobStatus(SC_STATUS_BUSY);
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

        status = SC_STATUS_OK;
        SetBgJobStatus(SC_STATUS_OK);
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

    SetBgJobStatus(SC_STATUS_BUSY);
    Control.asyncCallback = callback;
    Control.asyncResult = NAND_RESULT_OK;
    Control.openFileType = 0;

    for (i = 0; i < SC_CONF_FILE_MAX; i++) {
        Control.fileSizes[i] = 0;
    }

    Control.filePaths[SC_CONF_FILE_SYSTEM] = ConfFileName;
    Control.filePaths[SC_CONF_FILE_PRODUCT] = ProductInfoFileName;

    Control.fileBuffers[SC_CONF_FILE_SYSTEM] = buf;
    Control.fileBuffers[SC_CONF_FILE_PRODUCT] = OS_SC_PRDINFO;

    Control.bufferSizes[SC_CONF_FILE_SYSTEM] = __SCGetConfBufSize();
    Control.bufferSizes[SC_CONF_FILE_PRODUCT] = ARRAY_SIZE(OS_SC_PRDINFO);

    ClearConfBuf(buf);

    ItemIDOffsetTblOffset = 0;
    ItemNumTotal = 0;
    ItemRestSize = 0;

    Control.isFileOpen = FALSE;

    return NANDPrivateOpenAsync(Control.filePaths[Control.openFileType],
                                &Control.fileInfo, NAND_ACCESS_READ,
                                OpenCallbackFromReload, &Control.commandBlock);
}

static void OpenCallbackFromReload(s32 result, NANDCommandBlock* block) {
#pragma unused(block)

    if (result == NAND_RESULT_OK) {
        Control.isFileOpen = TRUE;

        if (NANDReadAsync(&Control.fileInfo,
                          Control.fileBuffers[Control.openFileType],
                          Control.bufferSizes[Control.openFileType],
                          ReadCallbackFromReload,
                          &Control.commandBlock) == NAND_RESULT_OK) {
            return;
        }
    }

    ErrorFromReload(result);
}

static void ReadCallbackFromReload(s32 result, NANDCommandBlock* block) {
#pragma unused(block)

    if (result == Control.bufferSizes[Control.openFileType]) {
        Control.fileSizes[Control.openFileType] = result;
        Control.isFileOpen = FALSE;

        if (NANDCloseAsync(&Control.fileInfo, CloseCallbackFromReload,
                           &Control.commandBlock) == NAND_RESULT_OK) {
            return;
        }
    }

    ErrorFromReload(result != NAND_RESULT_OK ? result
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

_openFile:
    Control.openFileType++;

    if (Control.openFileType < SC_CONF_FILE_MAX) {
        Control.isFileOpen = FALSE;

        if (NANDPrivateOpenAsync(Control.filePaths[Control.openFileType],
                                 &Control.fileInfo, NAND_ACCESS_READ,
                                 OpenCallbackFromReload,
                                 &Control.commandBlock) == NAND_RESULT_OK) {
            return;
        }

        goto _openFile;
    }

    switch (Control.asyncResult) {
    case NAND_RESULT_OK:
        status = SC_STATUS_PARSE;
        break;
    case NAND_RESULT_NOEXISTS:
    default:
        ClearConfBuf(Control.fileBuffers[SC_CONF_FILE_SYSTEM]);
        status = SC_STATUS_PARSE;

        Control.fileSizes[SC_CONF_FILE_SYSTEM] =
            Control.bufferSizes[SC_CONF_FILE_SYSTEM];
        break;
    }

    OS_SC_PRDINFO[ARRAY_SIZE(OS_SC_PRDINFO) - 1] = '\0';

    if (Control.asyncCallback != NULL) {
        Control.asyncCallback(Control.asyncResult);
        Control.asyncCallback = NULL;
    }

    SetBgJobStatus(status);
}

static void ErrorFromReload(s32 result) {
    if (Control.openFileType == SC_CONF_FILE_SYSTEM) {
        Control.asyncResult = result;
    }

    Control.fileSizes[Control.openFileType] = 0;

    if (!Control.isFileOpen ||
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

    if (size > SC_CONF_MIN_SIZE) {
        memcpy(conf, SC_CONF_BEGIN_MAGIC, 4);

        end = conf + size - sizeof(u32);
        memcpy(end, SC_CONF_END_MAGIC, 4);

        header->itemOffsets[0] = sizeof(SCConfHeader);
    }
}

static SCStatus ParseConfBuf(u8* conf, u32 size) {
    int i;

    u8* confBegin;
    u8* confEnd;
    u32 itemOffset;

    u32 numItems;
    u16* confItems;
    u32 itemRest;

    u8* confLutEnd;
    u8* confLutBegin;

    SCNameAndID* tblIter;
    SCNameAndID* tblEnd;
    const char* itName;

    tblIter = NameAndIDTbl;

    /**
     * Config parameters
     */

    if (size < SC_CONF_MIN_SIZE) {
        goto _error;
    }

    if (size > __SCGetConfBufSize()) {
        goto _error;
    }

    confBegin = conf;
    confEnd = conf + size - sizeof(u32);
    ItemIDMaxPlus1 = SC_ITEM_MAX;

    /**
     * File magic
     */

    if (memcmp(conf, SC_CONF_BEGIN_MAGIC, sizeof(u32)) != 0) {
        goto _error;
    }

    if (memcmp(confEnd, SC_CONF_END_MAGIC, sizeof(u32)) != 0) {
        goto _error;
    }

    conf += sizeof(u32);

    if (size < __SCGetConfBufSize()) {
        u32 confRest = __SCGetConfBufSize() - size;
        memset(confEnd, 0, confRest);
        confEnd += confRest;
        memcpy(confEnd, SC_CONF_END_MAGIC, sizeof(u32));
    }

    /**
     * Item count
     */

    if (!ParseGetBEValue(conf, confEnd, &numItems, sizeof(u16))) {
        goto _error;
    }

    conf += sizeof(u16);

    /**
     * Item data
     */

    confItems = (u16*)conf;
    itemOffset = (u8*)(confItems + numItems + 1) - confBegin;

    for (i = 0; i < numItems; i++) {
        SCItem item;

        if (itemOffset > size) {
            goto _error;
        }

        if ((u8*)&confItems[i] - confBegin > size) {
            goto _error;
        }

        if (itemOffset != confItems[i]) {
            goto _error;
        }

        if (!UnpackItem((SCConfItem*)(confBegin + itemOffset), &item)) {
            goto _error;
        }

        itemOffset += item.itemLen;
    }

    if (itemOffset > size || itemOffset != confItems[i]) {
        goto _error;
    }

    /**
     * Item lookup table
     */

    confLutEnd = confEnd - (SC_ITEM_MAX - 1) * sizeof(u16);

    if (confBegin + itemOffset > confLutEnd) {
        goto _error;
    }

    itemRest = confLutEnd - (confBegin + itemOffset);
    memset(confLutEnd, 0, confEnd - confLutEnd);

    // First LUT entry (grows upward)
    confLutBegin = confEnd - sizeof(u16);

    /**
     * Build lookup table
     */

    for (tblEnd = &tblIter[ItemIDMaxPlus1];
         tblIter < tblEnd && (itName = tblIter->name) != (void*)NULL;
         tblIter++) {

        u32 itNameLen = strlen(itName);

        for (i = 0; i < numItems; i++) {
            SCConfItem* itData = (SCConfItem*)(confBegin + confItems[i]);

            // Item length doesn't include terminator
            if (itNameLen != (itData->desc & 0b00011111) + 1) {
                continue;
            }

            if (memcmp(itName, itData->name, itNameLen) != 0) {
                continue;
            }

            // LUT items are in reverse order
            ((u16*)confLutBegin)[-tblIter->id] =
                (u8*)(confItems + i) - confBegin;

            break;
        }
    }

    ItemIDOffsetTblOffset = confLutBegin - confBegin;
    ItemNumTotal = numItems;
    ItemRestSize = itemRest;
    return SC_STATUS_OK;

_error:
    return SC_STATUS_FATAL;
}

static BOOL ParseGetBEValue(const u8* start, const u8* end, u32* out,
                            u32 size) {
    u32 imm = 0;

    if (start + size > end) {
        return FALSE;
    }

    for (; size > 0; start++, size--) {
        imm = imm << 8 | *start;
    }

    *out = imm;
    return TRUE;
}

static BOOL UnpackItem(const SCConfItem* raw, SCItem* item) {
    u8 type;

    memset(item, 0, sizeof(SCItem));
    type = raw->desc & 0b11100000;
    item->name = raw->name;
    item->nameLen = (raw->desc & 0b00011111) + 1;
    item->data = (u8*)raw + item->nameLen + 1;

    switch (type) {
    case SC_ITEM_BYTE:
    case SC_ITEM_BOOL:
        item->dataLen = sizeof(u8);
        break;
    case SC_ITEM_SHORT:
        item->dataLen = sizeof(u16);
        break;
    case SC_ITEM_LONG:
        item->dataLen = sizeof(u32);
        break;
    case SC_ITEM_LONGLONG:
        item->dataLen = sizeof(u64);
        break;
    case SC_ITEM_SMALLARRAY:
        item->dataLen = *item->data + sizeof(u8);
        item->data = item->data + sizeof(u8);
        item->itemLen += sizeof(u8);
        break;
    case SC_ITEM_BIGARRAY:
        item->dataLen = (item->data[0] << 8 | item->data[1]) + sizeof(u8);
        item->data = item->data + sizeof(u16);
        item->itemLen += sizeof(u16);
        break;
    default:
        goto _exit;
    }

    if (type == SC_ITEM_SMALLARRAY || type == SC_ITEM_BIGARRAY) {
        item->arrayType = SC_ITEM_SMALLARRAY;
    } else {
        item->primType = type;
        memcpy(item, item->data, item->dataLen);
    }

    item->itemLen += item->nameLen + item->dataLen + sizeof(u8);

_exit:
    return item->dataLen != 0;
}

static BOOL FindItemByID(SCItemID id, SCItem* item) {
    u8* conf;
    u16* ofsTbl;
    u16 itemOfsOfs;

    conf = __SCGetConfBuf();
    if (id < ItemIDMaxPlus1 && ItemIDOffsetTblOffset > 0) {
        ofsTbl = (u16*)(conf + ItemIDOffsetTblOffset);

        // LUT items are in reverse order
        itemOfsOfs = ofsTbl[-id];

        if (itemOfsOfs > 0) {
            return UnpackItem((SCConfItem*)(conf + *(u16*)(conf + itemOfsOfs)),
                              item);
        }
    }

    return FALSE;
}

static void DeleteItemByID(SCItemID id) {
    u8* conf;
    u16* itemOfs;
    u32 itemOfsOfs;
    u32 itemsEndOfs;
    u32 itemSize;
    u16* confLut;
    u16* confItemsBegin;
    u16* confItemsEnd;
    u32 sp14;
    u16* it;
    int i;

    conf = __SCGetConfBuf();

    if (id >= ItemIDMaxPlus1) {
        return;
    }

    if (ItemIDOffsetTblOffset == 0) {
        return;
    }

    confLut = (u16*)(conf + ItemIDOffsetTblOffset);
    // LUT items are in reverse order
    itemOfsOfs = confLut[-id];

    if (itemOfsOfs == 0) {
        return;
    }

    if (ItemNumTotal == 0) {
        return;
    }

    confItemsBegin = ((SCConfHeader*)conf)->itemOffsets;

    // LUT -> Item offset -> Item data
    itemOfs = (u16*)(conf + itemOfsOfs);

    // Last offset -> past end of items
    confItemsEnd = &confItemsBegin[ItemNumTotal];
    itemsEndOfs = *confItemsEnd;

    // Offset from next item
    itemSize = itemOfs[1] - itemOfs[0] + sizeof(u16);

    sp14 = *itemOfs - (itemOfsOfs + sizeof(u16));
    memmove(conf + itemOfsOfs, conf + itemOfsOfs + sizeof(u16), sp14);

    // Adjust item offsets
    for (it = confItemsEnd - 1; it >= confItemsBegin; it--) {
        if (it < itemOfs) {
            // After deleted item
            *it -= sizeof(u16);
        } else {
            // Before deleted item
            *it -= itemSize;
        }
    }

    memmove(conf + *itemOfs, conf + itemSize + *itemOfs,
            itemsEndOfs - (*itemOfs + itemSize));

    memset(conf + (itemsEndOfs - itemSize), 0, itemSize);

    // Adjust item lookup table
    for (i = 0; i < ItemIDMaxPlus1; i++) {
        // Before deleted slot
        if (confLut[-i] < itemOfsOfs) {
            continue;
        }

        // After deleted slot
        if (confLut[-i] > itemOfsOfs) {
            confLut[-i] -= sizeof(u16);
        } else {
            confLut[-i] = 0;
        }
    }

    ItemRestSize += itemSize;
    ItemNumTotal--;
    ((SCConfHeader*)conf)->numItems = ItemNumTotal;
    __SCSetDirtyFlag();
}

static BOOL CreateItemByID(SCItemID id, u8 primType, const void* src, u32 len) {
    u8* conf;
    u32 itemNameLen;
    u32 itemSize;
    u32 itemsEndOfs;
    const char* itemName;
    u8* newItem;
    u16* confItemsBegin;
    u16* confItemsEnd;
    u16* confLut;
    SCNameAndID* it;
    u16* ofsIter;

    conf = __SCGetConfBuf();
    itemSize = 1;
    it = NameAndIDTbl;

    if (id >= ItemIDMaxPlus1) {
        goto _error;
    }

    if (src == (void*)NULL) {
        goto _error;
    }

    if (ItemNumTotal >= 0xFFFF) {
        goto _error;
    }

    if (ItemIDOffsetTblOffset == 0) {
        goto _error;
    }

    switch (primType) {
    case SC_ITEM_BYTE:
    case SC_ITEM_BOOL:
        len = sizeof(u8);
        break;
    case SC_ITEM_SHORT:
        len = sizeof(u16);
        break;
    case SC_ITEM_LONG:
        len = sizeof(u32);
        break;
    case SC_ITEM_LONGLONG:
        len = sizeof(u64);
        break;
    case SC_ITEM_SMALLARRAY:
        if (len == 0) {
            goto _error;
        }

        // Length is stored minus one
        if (len > SC_BIGARRAY_MAX + 1) {
            goto _error;
        }

        // Length is stored minus one
        if (len > SC_SMALLARRAY_MAX + 1) {
            itemSize += 2;
            primType = SC_ITEM_BIGARRAY;
        } else {
            itemSize += 1;
        }
        break;
    default:
        goto _error;
    }

    itemSize += len;

    for (; (itemName = it->name) != (void*)NULL; it++) {
        if (it->id == id) {
            break;
        }
    }

    if (itemName == (void*)NULL) {
        goto _error;
    }

    // Only five bits reserved for name length (minus one)
    itemNameLen = strlen(itemName);
    if (itemNameLen > 0b00011111 + 1) {
        goto _error;
    }

    itemSize += itemNameLen;
    if (ItemRestSize < itemSize + sizeof(u16)) {
        goto _error;
    }

    confItemsBegin = ((SCConfHeader*)conf)->itemOffsets;
    confItemsEnd = &confItemsBegin[ItemNumTotal];
    itemsEndOfs = *confItemsEnd;

    // Make room for new item
    memmove(confItemsBegin[0] + sizeof(u16) + conf, confItemsBegin[0] + conf,
            itemsEndOfs - confItemsBegin[0]);

    // Adjust offsets
    ofsIter = confItemsBegin;
    do {
        *ofsIter++ += sizeof(u16);
    } while (ofsIter <= confItemsEnd);

    itemsEndOfs = *confItemsEnd;
    newItem = conf + itemsEndOfs;

    *newItem = primType | (itemNameLen - 1);
    memcpy(newItem + 1, itemName, itemNameLen);
    newItem += itemNameLen + 1;

    if (primType == SC_ITEM_SMALLARRAY) {
        *newItem++ = len - 1;
    } else if (primType == SC_ITEM_BIGARRAY) {
        *newItem++ = (len - 1) >> 8 & 0xFF;
        *newItem++ = (len - 1) >> 0 & 0xFF;
    }

    memcpy(newItem, src, len);
    newItem += len;

    confLut = (u16*)(conf + ItemIDOffsetTblOffset);
    confLut[-id] = (u8*)confItemsEnd - conf;
    confItemsEnd[1] = confItemsEnd[0] + itemSize;

    ItemRestSize -= itemSize + sizeof(u16);
    ItemNumTotal++;
    ((SCConfHeader*)conf)->numItems = ItemNumTotal;
    __SCSetDirtyFlag();
    return TRUE;

_error:
    return FALSE;
}

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
    BOOL success;
    BOOL enabled;
    SCItem item;

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
                goto _exit;

            } else {
                DeleteItemByID(id);
            }
        }

        success = CreateItemByID(id, SC_ITEM_SMALLARRAY, src, len);
    }

_exit:
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

static BOOL SCReplaceIntegerItem(const void* src, SCItemID id, u8 primType)
    DECOMP_DONT_INLINE {
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
            goto _exit;

        } else {
            DeleteItemByID(id);
        }
    }

    success = CreateItemByID(id, primType, src, 0);

_exit:
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
    return SCReplaceIntegerItem(&data, id, SC_ITEM_BYTE);
}

static void __SCFlushSyncCallback(SCStatus status) {
#pragma unused(status)

    OSWakeupThread(&Control.threadQueue);
}

void SCFlushAsync(SCFlushCallback callback) {
    SCControl* ctrl;
    BOOL enabled;
    u8 status;

    ctrl = &Control;
    enabled = OSDisableInterrupts();
    status = BgJobStatus;

    if (status == SC_STATUS_OK) {
        SetBgJobStatus(SC_STATUS_BUSY);

        if (callback == ((void*)NULL)) {
            callback = __SCFlushSyncCallback;
        }

        ctrl->flushCallback = callback;
        ctrl->flushStatus = SC_STATUS_OK;
        ctrl->isFileOpen = FALSE;
        ctrl->flushSize = __SCGetConfBufSize();

        if (!__SCIsDirty()) {
            OSRestoreInterrupts(enabled);
            FinishFromFlush();
        } else {
            __SCClearDirtyFlag();
            memcpy(ConfBufForFlush, __SCGetConfBuf(), __SCGetConfBufSize());

            OSRestoreInterrupts(enabled);
            ctrl->nandCbState = NAND_CB_STATE_0;

            if (NANDPrivateGetTypeAsync(ConfFileName, &ctrl->fileType,
                                        MyNandCallback, &ctrl->commandBlock) !=
                NAND_RESULT_OK) {
                ErrorFromFlush();
            }
        }
    } else {
        if (callback != NULL) {
            callback(status == SC_STATUS_BUSY ? status : SC_STATUS_FATAL);
        }

        OSRestoreInterrupts(enabled);
    }
}

static void MyNandCallback(s32 result, NANDCommandBlock* block) {
#pragma unused(block)

    SCControl* ctrl = &Control;

    switch (ctrl->nandCbState) {
    case NAND_CB_STATE_0:
        if (result == NAND_RESULT_OK && ctrl->fileType == NAND_FILE_TYPE_FILE) {
            ctrl->nandCbState = NAND_CB_STATE_1;

            if (NANDPrivateGetStatusAsync(
                    ConfFileName, &ctrl->fileAttr, MyNandCallback,
                    &ctrl->commandBlock) != NAND_RESULT_OK) {
                goto _error;
            }
        } else {
            goto _case_1_lbl;
        }
        return;

    case NAND_CB_STATE_1:
        if (result == NAND_RESULT_OK &&
            ctrl->fileAttr.perm == NAND_PERM_RWALL) {
            goto _case_5_lbl;
        }
    _case_1_lbl:
        ctrl->nandCbState = NAND_CB_STATE_2;

        if (NANDPrivateDeleteAsync(ConfFileName, MyNandCallback,
                                   &ctrl->commandBlock) != NAND_RESULT_OK) {
            goto _error;
        }
        return;

    case NAND_CB_STATE_2:
        ctrl->nandCbState = NAND_CB_STATE_3;

        if (NANDPrivateGetTypeAsync(ConfDirName, &ctrl->fileType,
                                    MyNandCallback,
                                    &ctrl->commandBlock) != NAND_RESULT_OK) {
            goto _error;
        }
        return;

    case NAND_CB_STATE_3:
        if (result == NAND_RESULT_OK && ctrl->fileType == NAND_FILE_TYPE_DIR) {
            goto _case_4_lbl;
        }

        ctrl->nandCbState = NAND_CB_STATE_4;

        if (NANDPrivateCreateDirAsync(ConfDirName, NAND_PERM_RWALL, 0,
                                      MyNandCallback,
                                      &ctrl->commandBlock) != NAND_RESULT_OK) {
            goto _error;
        }
        return;

    case NAND_CB_STATE_4:
    _case_4_lbl:
        ctrl->nandCbState = NAND_CB_STATE_5;
        if (NANDPrivateCreateAsync(ConfFileName, NAND_PERM_RWALL, 0,
                                   MyNandCallback,
                                   &ctrl->commandBlock) != NAND_RESULT_OK) {
            goto _error;
        }
        return;

    case NAND_CB_STATE_5:
    _case_5_lbl:
        ctrl->nandCbState = NAND_CB_STATE_6;
        if (NANDPrivateOpenAsync(ConfFileName, &ctrl->fileInfo,
                                 NAND_ACCESS_WRITE, MyNandCallback,
                                 &ctrl->commandBlock) != NAND_RESULT_OK) {
            goto _error;
        }
        return;

    case NAND_CB_STATE_6:
        if (result != NAND_RESULT_OK) {
            goto _error;
        }

        ctrl->isFileOpen = TRUE;
        ctrl->nandCbState = NAND_CB_STATE_7;

        if (NANDWriteAsync(&ctrl->fileInfo, ConfBufForFlush, ctrl->flushSize,
                           MyNandCallback,
                           &ctrl->commandBlock) != NAND_RESULT_OK) {
            goto _error;
        }
        return;

    case NAND_CB_STATE_7:
        if (result != ctrl->flushSize) {
            goto _error;
        }

        ctrl->isFileOpen = FALSE;
        ctrl->nandCbState = NAND_CB_STATE_8;

        if (NANDCloseAsync(&ctrl->fileInfo, MyNandCallback,
                           &ctrl->commandBlock) != NAND_RESULT_OK) {
            goto _error;
        }
        return;

    case NAND_CB_STATE_8:
        if (result != NAND_RESULT_OK) {
            goto _error;
        }
        // FALLTHROUGH

    case NAND_CB_STATE_9:
        FinishFromFlush();
        // FALLTHROUGH

    default:
        return;
    }

_error:
    ErrorFromFlush();
}

static void FinishFromFlush(void) {
    SCControl* ctrl;
    SCFlushCallback callback;

    ctrl = &Control;
    if (ctrl->flushStatus != SC_STATUS_OK) {
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
    ctrl->flushStatus = SC_STATUS_FATAL;

    if (ctrl->isFileOpen) {
        ctrl->nandCbState = NAND_CB_STATE_9;

        if (NANDCloseAsync(&ctrl->fileInfo, MyNandCallback,
                           &ctrl->commandBlock) == NAND_RESULT_OK) {
            return;
        }
    }

    FinishFromFlush();
}

BOOL __SCIsDirty(void) {
    return DirtyFlag ? TRUE : FALSE;
}

void __SCSetDirtyFlag(void) {
    DirtyFlag = TRUE;
}

void __SCClearDirtyFlag(void) {
    DirtyFlag = FALSE;
}

u8* __SCGetConfBuf(void) {
    return ConfBuf;
}

u32 __SCGetConfBufSize(void) {
    return SC_CONF_MAX_SIZE;
}
