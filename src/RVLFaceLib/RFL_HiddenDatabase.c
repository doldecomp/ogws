#include <RVLFaceLib/RVLFaceLibInternal.h>
#include <string.h>

void RFLiInitHiddenDatabase(void) {
    RFLiHDBManager* mgr = RFLiGetHDBManager();
    if (mgr != NULL) {
        mgr->cachedDB = NULL;
        mgr->cached = FALSE;
    }
}

static void loadclosecallback_(void) {
    RFLiHDBManager* mgr = RFLiGetHDBManager();
    if (mgr->loadCb != NULL) {
        mgr->loadCb(mgr->loadArg);
    }
}

static void loadcallback_(void) {
    RFLiHDBManager* mgr;
    RFLiCharHRawData* hraw;
    RFLiCharInfo info;

    mgr = RFLiGetHDBManager();

    if (RFLGetAsyncStatus() == RFLErrcode_Success) {
        hraw = (RFLiCharHRawData*)mgr->loadTmp;

        if (RFLiIsSameID(
                hraw->createID,
                RFLiGetHiddenHeader()->data[mgr->loadIndex].createID)) {
            RFLiConvertHRaw2Info(hraw, &info);

            if (RFLiCheckValidInfo(&info) && RFLiIsValidOnNAND(&info)) {
                memcpy(mgr->loadDst, hraw, sizeof(RFLiCharHRawData));
            } else {
                RFLiGetManager()->lastErrCode = RFLErrcode_Broken;
            }
        }
    }

    RFLiFree(mgr->loadTmp);
    mgr->loadTmp = NULL;

    RFLiCloseAsync(RFLiFileType_Database, loadclosecallback_);
}

static void loadopencallback_(void) {
    RFLiHDBManager* mgr;
    s32 offset;

    mgr = RFLiGetHDBManager();

    if (RFLGetAsyncStatus() == RFLErrcode_Success) {
        offset = mgr->loadIndex * sizeof(RFLiCharHRawData);
        mgr->loadTmp = RFLiAlloc32(sizeof(RFLiCharHRawData));

        switch (RFLiReadAsync(RFLiFileType_Database, mgr->loadTmp,
                              sizeof(RFLiCharHRawData), loadcallback_,
                              offset + sizeof(RFLiDatabase))) {
        case RFLErrcode_Success:
        case RFLErrcode_Busy:
            break;
        default:
            RFLiFree(mgr->loadTmp);
            mgr->loadTmp = NULL;
            RFLiCloseAsync(RFLiFileType_Database, NULL);
        }
    } else {
        mgr->loadDst = NULL;
        mgr->loadTmp = NULL;
        mgr->loadIndex = 0;
        mgr->loadCb = NULL;
    }
}

RFLErrcode RFLiLoadHiddenDataAsync(RFLiCharHRawData* hraw, u16 index,
                                   RFLiAsyncCallback cb, u32 arg) {
    RFLiHDBManager* mgr;

    if (index >= RFL_HDB_DATA_MAX) {
        return RFLErrcode_WrongParam;
    }

    if (hraw == NULL) {
        return RFLErrcode_WrongParam;
    }

    if (!RFLAvailable()) {
        return RFLErrcode_NotAvailable;
    }

    mgr = RFLiGetHDBManager();
    if (mgr == NULL) {
        return RFLErrcode_NotAvailable;
    }

    mgr->loadDst = hraw;
    mgr->loadIndex = index;
    mgr->loadCb = cb;
    mgr->loadArg = arg;

    return RFLiOpenAsync(RFLiFileType_Database, NAND_ACCESS_READ,
                         loadopencallback_);
}

RFLErrcode RFLiLoadCachedHiddenData(RFLiCharHRawData* hraw, u16 index) {
    RFLiHDBManager* mgr;
    RFLiCharInfo info;

    if (index >= RFL_HDB_DATA_MAX) {
        return RFLErrcode_WrongParam;
    }

    if (hraw == NULL) {
        return RFLErrcode_WrongParam;
    }

    if (!RFLAvailable()) {
        return RFLErrcode_NotAvailable;
    }

    mgr = RFLiGetHDBManager();
    if (mgr == NULL) {
        return RFLErrcode_NotAvailable;
    }

    if (RFLiIsCachedHDB()) {
        if (RFLiIsSameID(mgr->cachedDB[index].createID,
                         RFLiGetHiddenHeader()->data[index].createID)) {
            RFLiConvertHRaw2Info(&mgr->cachedDB[index], &info);

            if (RFLiCheckValidInfo(&info)) {
                memcpy(hraw, &mgr->cachedDB[index], sizeof(RFLiCharHRawData));
                return RFLErrcode_Success;
            } else {
                return RFLErrcode_Broken;
            }
        } else {
            return RFLErrcode_Broken;
        }
    } else {
        return RFLErrcode_NotAvailable;
    }
}

/**
 * TODO: Label 80171b5c - 80172044
 */

u16 RFLiCountupHiddenDataNum(RFLSex sex) {
    RFLiHDBManager* mgr;
    RFLiHiddenDB* header;
    u16 count;
    u16 i;

    count = 0;

    if (!RFLAvailable()) {
        return 0;
    }

    mgr = RFLiGetHDBManager();
    if (mgr == NULL) {
        return 0;
    }

    if (!RFLiDBIsLoaded()) {
        return 0;
    }

    header = RFLiGetHiddenHeader();

    for (i = 0; i < RFL_HDB_DATA_MAX; i++) {
        if (RFLiIsValidHiddenData(i, sex)) {
            count++;
        }
    }

    return count;
}

s16 RFLiGetHiddenNext(u16 index) {
    RFLiHDBManager* mgr;
    RFLiHDBData* data;

    mgr = RFLiGetHDBManager();

    if (index >= RFL_HDB_DATA_MAX) {
        return -1;
    }

    if (mgr == NULL) {
        return -1;
    }

    data = &RFLiGetHiddenHeader()->data[index];

    if (RFLiIsValidID(data->createID)) {
        return data->next;
    }

    return -1;
}

s16 RFLiGetHiddenPrev(u16 index) {
    RFLiHDBManager* mgr;
    RFLiHDBData* data;

    mgr = RFLiGetHDBManager();

    if (index >= RFL_HDB_DATA_MAX) {
        return -1;
    }

    if (mgr == NULL) {
        return -1;
    }

    data = &RFLiGetHiddenHeader()->data[index];

    if (RFLiIsValidID(data->createID)) {
        return data->prev;
    }

    return -1;
}

BOOL RFLiIsValidHiddenData(u16 index, RFLSex sex) {
    RFLiHDBManager* mgr;
    RFLiHiddenDB* header;
    u16 count;

    if (!RFLAvailable()) {
        return FALSE;
    }

    mgr = RFLiGetHDBManager();
    if (mgr == NULL) {
        return FALSE;
    }

    header = RFLiGetHiddenHeader();

    if (!RFLiIsValidID(header->data[index].createID)) {
        return FALSE;
    }

    if (sex == RFLSex_All) {
        return TRUE;
    }

    switch (header->data[index].sex) {
    case RFLSex_Male:
        return sex == RFLSex_Male;
    case RFLSex_Female:
        return sex == RFLSex_Female;
    }

    return FALSE;
}

void RFLiClearCacheHDB(RFLiCharHRawData* cache) {
    memset(cache, 0, sizeof(RFLiCharHRawData) * RFL_HDB_DATA_MAX);
}

BOOL RFLiIsCachedHDB(void) {
    RFLiHDBManager* mgr;

    if (!RFLAvailable()) {
        return FALSE;
    }

    mgr = RFLiGetHDBManager();
    if (mgr == NULL) {
        return FALSE;
    }

    return mgr->cached;
}