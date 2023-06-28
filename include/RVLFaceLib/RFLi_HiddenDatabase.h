#ifndef RVL_FACE_LIBRARY_INTERNAL_HIDDEN_DATABASE_H
#define RVL_FACE_LIBRARY_INTERNAL_HIDDEN_DATABASE_H
#include <RVLFaceLib/RFLi_Types.h>
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

#define RFL_HDB_DATA_MAX 10000

typedef struct RFLiHDBData {
    u8 createID[RFL_CREATEID_LEN]; // at 0x0

    // at 0x8
    u16 sex : 1;
    s16 next : 15;

    // at 0xA
    s16 padding2 : 1;
    s16 prev : 15;
} RFLiHDBData;

typedef struct RFLiHiddenDB {
    u32 identifier;                     // at 0x0
    s16 head;                           // at 0x4
    s16 tail;                           // at 0x6
    RFLiHDBData data[RFL_HDB_DATA_MAX]; // at 0x8
    u8 padding[22];                     // at 0x1D4C8
    u16 crc;                            // at 0x1D4DE
} RFLiHiddenDB;

typedef struct RFLiHDBList {
    RFLiCharHRawData data[RFL_DB_CHAR_MAX]; // at 0x0
    u16 num;                                // at 0x1900
    u8 current;                             // at 0x1901
} RFLiHDBList;

typedef struct RFLiHDBManager {
    BOOL loaded;                // at 0x0
    BOOL readError;             // at 0x4
    void* writeTmp;             // at 0x8
    s16 writeIndex;             // at 0xC
    RFLiCallback writeCb;       // at 0x10
    void* formatTmp;            // at 0x14
    RFLiCallback formatCb;      // at 0x18
    s16 formatIndex;            // at 0x1C
    RFLiCharHRawData* loadDst;  // at 0x20
    void* loadTmp;              // at 0x24
    u32 loadArg;                // at 0x28
    RFLiAsyncCallback loadCb;   // at 0x2C
    u16 loadIndex;              // at 0x30
    RFLiCharHRawData* cachedDB; // at 0x34
    BOOL cached;                // at 0x38
    RFLiHDBList list;           // at 0x3C
} RFLiHDBManager;

void RFLiInitHiddenDatabase(void);
RFLErrcode RFLiLoadHiddenDataAsync(RFLiCharHRawData* hraw, u16 index,
                                   RFLiAsyncCallback cb, u32 arg);
RFLErrcode RFLiLoadCachedHiddenData(RFLiCharHRawData* hraw, u16 index);

u16 RFLiCountupHiddenDataNum(RFLSex sex);
s16 RFLiGetHiddenNext(u16 index);
s16 RFLiGetHiddenPrev(u16 index);
BOOL RFLiIsValidHiddenData(u16 index, RFLSex sex);
void RFLiClearCacheHDB(RFLiCharHRawData* hdb);
BOOL RFLiIsCachedHDB(void);

#ifdef __cplusplus
}
#endif
#endif
