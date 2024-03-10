#include <revolution/NWC24.h>
#include <string.h>

static const char* DLFilePath = "/shared2/wc24/nwc24dl.bin";

static NWC24DlEntry* GetDlTaskEntryHeader(u16 i);
static NWC24Err WriteDlHeader(NWC24File* file);
static NWC24Err SeekDlTaskEntry(u16 i, NWC24File* file);
static NWC24Err CheckDlEntryAvailable(u16 i);
static NWC24Err WriteDlTaskEntry(NWC24DlTask* task, NWC24File* file);
static NWC24Err ReadDlTaskEntry(NWC24DlTask* task, u16 i, NWC24File* file);
static NWC24Err ClearDlTaskEntry(u16 i, NWC24File* file);
static NWC24Err ReadDlHeader(NWC24File* file);
static void InitTaskEntryHeader(u16 i);
static NWC24Err LoadDlTask(NWC24DlTask* task, u16 i);
static NWC24Err DeleteDlTask(NWC24DlTask* task) DECOMP_DONT_INLINE;
static NWC24Err CheckHeader(NWC24DlHeader* header);

static BOOL IsPrivateId(u16 i) {
    return i < NWC24iGetCachedDlHeader()->privateTasks;
}

NWC24Err NWC24CheckDlTask(NWC24DlTask* task) {
    NWC24DlHeader* header;

    header = NWC24iGetCachedDlHeader();

    if (task == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }

    if (header == NULL) {
        return NWC24_ERR_LIB_NOT_OPENED;
    }

    // @bug Should be maxTasks
    if (task->id != 0xFFFF &&
        task->id >= NWC24iGetCachedDlHeader()->maxSubTasks) {
        return NWC24_ERR_INVALID_VALUE;
    }

    return NWC24_OK;
}

NWC24Err NWC24DeleteDlTaskForced(NWC24DlTask* task) {
    NWC24Err result;

    result = NWC24CheckDlTask(task);
    if (result != NWC24_OK) {
        return result;
    }

    result = DeleteDlTask(task);
    if (result < 0) {
        return result;
    }

    task->id = 0xFFFF;
    return result;
}

NWC24Err NWC24GetDlTask(NWC24DlTask* task, u16 i) {
    NWC24Err result;

    result = CheckDlEntryAvailable(i);
    if (result < 0) {
        return result;
    }

    result = LoadDlTask(task, i);
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

NWC24Err NWC24iCheckHeaderConsistency(NWC24DlHeader* header, BOOL clear) {
    NWC24DlTask* ptask;
    NWC24DlTask* pptask;
    NWC24DlTask task;
    u16 i;

    // Man...
    ptask = &task;
    pptask = ptask;

    // @bug Should be maxTasks
    for (i = 0; i < header->maxSubTasks; i++) {
        if (CheckDlEntryAvailable(i) == NWC24_OK && clear) {
            if (NWC24GetDlTask(pptask, i) < 0) {
                NWC24DeleteDlTaskForced(ptask);
            } else if (!IsPrivateId(i) && task.count == 0) {
                NWC24DeleteDlTaskForced(ptask);
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

static NWC24DlEntry* GetDlTaskEntryHeader(u16 i) {
    return &NWC24iGetCachedDlHeader()->entries[i];
}

static NWC24Err WriteDlHeader(NWC24File* file) {
    NWC24Err result;

    result = NWC24FSeek(file, 0, NWC24_SEEK_BEG);
    if (result < 0) {
        return result;
    }

    result =
        NWC24FWrite(NWC24iGetCachedDlHeader(), sizeof(NWC24DlHeader), file);
    if (result < 0) {
        return result;
    }

    return NWC24_OK;
}

static NWC24Err SeekDlTaskEntry(u16 i, NWC24File* file) {
    return NWC24FSeek(file, sizeof(NWC24DlHeader) + i * sizeof(NWC24DlTask),
                      NWC24_SEEK_BEG);
}

static NWC24Err CheckDlEntryAvailable(u16 i) {
    // @bug Should be maxTasks
    if (i >= NWC24iGetCachedDlHeader()->maxSubTasks || i == 0xFFFF) {
        return NWC24_ERR_INVALID_VALUE;
    }

    if (GetDlTaskEntryHeader(i)->app == 0) {
        return NWC24_ERR_NOT_FOUND;
    }

    return NWC24_OK;
}

static NWC24Err WriteDlTaskEntry(NWC24DlTask* task, NWC24File* file) {
    NWC24Err result;

    result = SeekDlTaskEntry(task->id, file);
    if (result < 0) {
        return result;
    }

    memcpy(NWC24WorkP->dlTask, task, sizeof(NWC24DlTask));
    result = NWC24FWrite(NWC24WorkP->dlTask, sizeof(NWC24DlTask), file);
    if (result < 0) {
        return result;
    }

    return NWC24_OK;
}

static NWC24Err ReadDlTaskEntry(NWC24DlTask* task, u16 i, NWC24File* file) {
    NWC24Err result;

    result = SeekDlTaskEntry(i, file);
    if (result < 0) {
        return result;
    }

    result = NWC24FRead(task, sizeof(NWC24DlTask), file);
    if (result < 0) {
        return result;
    }

    return NWC24_OK;
}

static NWC24Err ClearDlTaskEntry(u16 i, NWC24File* file) {
    NWC24DlTask* task = (NWC24DlTask*)NWC24WorkP->dlTask;

    memset(task, 0, sizeof(NWC24DlTask));
    task->type = 0xFF;
    task->id = i;

    InitTaskEntryHeader(i);
    return WriteDlTaskEntry(task, file);
}

static NWC24Err ReadDlHeader(NWC24File* file) {
    NWC24Err result;

    result = NWC24FSeek(file, 0, NWC24_SEEK_BEG);
    if (result < 0) {
        return result;
    }

    result = NWC24FRead(&NWC24WorkP->dlHeader, sizeof(NWC24DlHeader), file);
    if (result < 0) {
        return result;
    }

    return NWC24_OK;
}

static void InitTaskEntryHeader(u16 i) {
    memset(GetDlTaskEntryHeader(i), 0, sizeof(NWC24DlEntry));
}

static NWC24Err LoadDlTask(NWC24DlTask* task, u16 i) {
    NWC24File file;
    NWC24Err result;
    NWC24Err close;
    NWC24Err ret;

    result = NWC24FOpen(&file, DLFilePath, NWC24_OPEN_NAND_RBUFF);
    if (result < 0) {
        return result;
    }

    result = ReadDlTaskEntry(task, i, &file);
    close = NWC24FClose(&file);

    if (result != NWC24_OK) {
        ret = result;
    } else {
        ret = close;
    }

    return ret;
}

static NWC24Err DeleteDlTask(NWC24DlTask* task) {
    NWC24File file;
    NWC24Err result;
    NWC24Err close;
    NWC24Err ret;

    result = NWC24FOpen(&file, DLFilePath, NWC24_OPEN_NAND_RW);
    if (result < 0) {
        return result;
    }

    result = ClearDlTaskEntry(task->id, &file);
    if (result >= 0) {
        InitTaskEntryHeader(task->id);
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

static NWC24Err CheckHeader(NWC24DlHeader* header) {
    // @bug Should be maxTasks
    if (header->maxSubTasks < 1 || header->privateTasks < 1 ||
        header->maxSubTasks < header->privateTasks) {
        return NWC24_ERR_BROKEN;
    }

    return NWC24_OK;
}
