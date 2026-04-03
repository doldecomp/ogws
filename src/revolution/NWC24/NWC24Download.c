#include <revolution/NWC24.h>

#include <string.h>

static const char* DLFilePath = "/shared2/wc24/nwc24dl.bin";

// Forward declarations
static BOOL IsPrivateId(u16 id);
static NWC24DlEntry* GetDlTaskEntryHeader(u16 id);
static NWC24Err WriteDlHeader(NWC24File* pFile);
static NWC24Err SeekDlTaskEntry(u16 id, NWC24File* pFile);
static NWC24Err CheckDlEntryAvailable(u16 id);
static NWC24Err WriteDlTaskEntry(NWC24DlTask* pTask, NWC24File* pFile);
static NWC24Err ReadDlTaskEntry(NWC24DlTask* pTask, u16 id, NWC24File* pFile);
static NWC24Err ClearDlTaskEntry(u16 id, NWC24File* pFile);
static NWC24Err ReadDlHeader(NWC24File* pFile);
static void InitTaskEntryHeader(u16 id);
static NWC24Err LoadDlTask(NWC24DlTask* pTask, u16 id);
static NWC24Err DeleteDlTask(NWC24DlTask* pTask) DECOMP_DONT_INLINE;
static NWC24Err CheckHeader(NWC24DlHeader* pHeader);

NWC24Err NWC24CheckDlTask(NWC24DlTask* pTask) {
    NWC24DlHeader* pHeader;

    pHeader = NWC24iGetCachedDlHeader();

    if (pTask == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }

    if (pHeader == NULL) {
        return NWC24_ERR_LIB_NOT_OPENED;
    }

    // @bug Should be maxTasks
    if (pTask->id != 0xFFFF &&
        pTask->id >= NWC24iGetCachedDlHeader()->maxSubTasks) {
        return NWC24_ERR_INVALID_VALUE;
    }

    return NWC24_OK;
}

static BOOL IsPrivateId(u16 id) {
    return id < NWC24iGetCachedDlHeader()->privateTasks;
}

NWC24Err NWC24DeleteDlTaskForced(NWC24DlTask* pTask) {
    NWC24Err result;

    result = NWC24CheckDlTask(pTask);
    if (result != NWC24_OK) {
        return result;
    }

    result = DeleteDlTask(pTask);
    if (result < 0) {
        return result;
    }

    pTask->id = 0xFFFF;
    return result;
}

NWC24Err NWC24GetDlTask(NWC24DlTask* pTask, u16 id) {
    NWC24Err result;

    result = CheckDlEntryAvailable(id);
    if (result < 0) {
        return result;
    }

    result = LoadDlTask(pTask, id);
    if (result < 0) {
        return result;
    }

    return result;
}

NWC24Err NWC24iOpenDlTaskList(void) {
    NWC24Err result;

    result = NWC24iLoadDlHeader();

    if (result >= 0) {
        NWC24iSynchronizeRtcCounter(FALSE);
        result = NWC24iCheckHeaderConsistency(NWC24iGetCachedDlHeader(), FALSE);

        if (result >= 0) {
            return NWC24_OK;
        }
    }

    return result;
}

NWC24Err NWC24iCloseDlTaskList(void) {
    return NWC24_OK;
}

NWC24DlHeader* NWC24iGetCachedDlHeader(void) {
    return (NWC24DlHeader*)NWC24WorkP->dlHeader;
}

NWC24Err NWC24iCheckHeaderConsistency(NWC24DlHeader* pHeader, BOOL clear) {
    NWC24DlTask* pTask;
    NWC24DlTask* ppTask;
    NWC24DlTask task;
    u16 i;

    // TODO(kiwi) Fakematch
    pTask = &task;
    ppTask = pTask;

    // @bug Should be maxTasks
    for (i = 0; i < pHeader->maxSubTasks; i++) {
        if (CheckDlEntryAvailable(i) == NWC24_OK && clear) {
            if (NWC24GetDlTask(ppTask, i) < 0) {
                NWC24DeleteDlTaskForced(pTask);
            } else if (!IsPrivateId(i) && pTask->count == 0) {
                NWC24DeleteDlTaskForced(pTask);
            }
        }
    }

    return NWC24_OK;
}

NWC24Err NWC24iLoadDlHeader(void) {
    NWC24File file;
    NWC24Err result;
    NWC24Err close;
    NWC24Err ret;
    u32 length;

    length = 0;

    result = NWC24FOpen(&file, DLFilePath, NWC24_OPEN_NAND_R);
    if (result < 0) {
        return result;
    }

    result = ReadDlHeader(&file);
    if (result < 0) {
        return result;
    }

    result = NWC24FGetLength(&file, &length);
    if (result >= 0) {
        result = CheckHeader(NWC24iGetCachedDlHeader());
    }

    close = NWC24FClose(&file);

    if (result != NWC24_OK) {
        ret = result;
    } else {
        ret = close;
    }

    return ret;
}

static NWC24DlEntry* GetDlTaskEntryHeader(u16 id) {
    return &NWC24iGetCachedDlHeader()->entries[id];
}

static NWC24Err WriteDlHeader(NWC24File* pFile) {
    NWC24Err result;

    result = NWC24FSeek(pFile, 0, NWC24_SEEK_BEG);
    if (result < 0) {
        return result;
    }

    result =
        NWC24FWrite(NWC24iGetCachedDlHeader(), sizeof(NWC24DlHeader), pFile);
    if (result < 0) {
        return result;
    }

    return NWC24_OK;
}

static NWC24Err SeekDlTaskEntry(u16 id, NWC24File* pFile) {
    return NWC24FSeek(pFile, sizeof(NWC24DlHeader) + id * sizeof(NWC24DlTask),
                      NWC24_SEEK_BEG);
}

static NWC24Err CheckDlEntryAvailable(u16 id) {
    // @bug Should be maxTasks
    if (id >= NWC24iGetCachedDlHeader()->maxSubTasks || id == 0xFFFF) {
        return NWC24_ERR_INVALID_VALUE;
    }

    if (GetDlTaskEntryHeader(id)->app == 0) {
        return NWC24_ERR_NOT_FOUND;
    }

    return NWC24_OK;
}

static NWC24Err WriteDlTaskEntry(NWC24DlTask* pTask, NWC24File* pFile) {
    NWC24Err result;

    result = SeekDlTaskEntry(pTask->id, pFile);
    if (result < 0) {
        return result;
    }

    memcpy(NWC24WorkP->dlTask, pTask, sizeof(NWC24DlTask));
    result = NWC24FWrite(NWC24WorkP->dlTask, sizeof(NWC24DlTask), pFile);
    if (result < 0) {
        return result;
    }

    return NWC24_OK;
}

static NWC24Err ReadDlTaskEntry(NWC24DlTask* pTask, u16 id, NWC24File* pFile) {
    NWC24Err result;

    result = SeekDlTaskEntry(id, pFile);
    if (result < 0) {
        return result;
    }

    result = NWC24FRead(pTask, sizeof(NWC24DlTask), pFile);
    if (result < 0) {
        return result;
    }

    return NWC24_OK;
}

static NWC24Err ClearDlTaskEntry(u16 id, NWC24File* pFile) {
    NWC24DlTask* pTask = (NWC24DlTask*)NWC24WorkP->dlTask;

    memset(pTask, 0, sizeof(NWC24DlTask));
    pTask->type = 0xFF;
    pTask->id = id;

    InitTaskEntryHeader(id);
    return WriteDlTaskEntry(pTask, pFile);
}

static NWC24Err ReadDlHeader(NWC24File* pFile) {
    NWC24Err result;

    result = NWC24FSeek(pFile, 0, NWC24_SEEK_BEG);
    if (result < 0) {
        return result;
    }

    result = NWC24FRead(&NWC24WorkP->dlHeader, sizeof(NWC24DlHeader), pFile);
    if (result < 0) {
        return result;
    }

    return NWC24_OK;
}

static void InitTaskEntryHeader(u16 id) {
    memset(GetDlTaskEntryHeader(id), 0, sizeof(NWC24DlEntry));
}

static NWC24Err LoadDlTask(NWC24DlTask* pTask, u16 id) {
    NWC24File file;
    NWC24Err result;
    NWC24Err close;
    NWC24Err ret;

    result = NWC24FOpen(&file, DLFilePath, NWC24_OPEN_NAND_RBUFF);
    if (result < 0) {
        return result;
    }

    result = ReadDlTaskEntry(pTask, id, &file);
    close = NWC24FClose(&file);

    if (result != NWC24_OK) {
        ret = result;
    } else {
        ret = close;
    }

    return ret;
}

static NWC24Err DeleteDlTask(NWC24DlTask* pTask) {
    NWC24File file;
    NWC24Err result;
    NWC24Err close;
    NWC24Err ret;

    result = NWC24FOpen(&file, DLFilePath, NWC24_OPEN_NAND_RW);
    if (result < 0) {
        return result;
    }

    result = ClearDlTaskEntry(pTask->id, &file);
    if (result >= 0) {
        InitTaskEntryHeader(pTask->id);
        result = WriteDlHeader(&file);
    }

    close = NWC24FClose(&file);

    if (result != NWC24_OK) {
        ret = result;
    } else {
        ret = close;
    }

    return ret;
}

static NWC24Err CheckHeader(NWC24DlHeader* pHeader) {
    // @bug Should be maxTasks
    if (pHeader->maxSubTasks < 1 || pHeader->privateTasks < 1 ||
        pHeader->maxSubTasks < pHeader->privateTasks) {
        return NWC24_ERR_BROKEN;
    }

    return NWC24_OK;
}
