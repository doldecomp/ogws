#ifndef RVL_FACE_LIBRARY_INTERNAL_HIDDEN_DATABASE_H
#define RVL_FACE_LIBRARY_INTERNAL_HIDDEN_DATABASE_H
#include <RVLFaceLib/RFLi_Database.h>
#include <RVLFaceLib/RFLi_Types.h>
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct RFLiHDBList {
    RFLiDBCharInfo data[RFL_DB_CHAR_MAX]; // at 0x0
    u16 num;                              // at 0x1900
    u8 current;                           // at 0x1901
} RFLiHDBList;

typedef struct RFLiHDBManager {
    BOOL loaded;                   // at 0x0
    BOOL readError;                // at 0x4
    void* writeTmp;                // at 0x8
    s16 writeIndex;                // at 0xC
    RFLiDatabaseCallback writeCb;  // at 0x10
    void* formatTmp;               // at 0x14
    RFLiDatabaseCallback formatCb; // at 0x18
    s16 formatIndex;               // at 0x1C
    RFLiDBCharInfo* loadDst;       // at 0x20
    void* loadTmp;                 // at 0x24
    u32 loadArg;                   // at 0x28
    RFLiAlarmCallback loadCb;      // at 0x2C
    u16 loadIndex;                 // at 0x30
    RFLiDBCharInfo* cachedDB;      // at 0x34
    BOOL cached;                   // at 0x38
    RFLiHDBList list;              // at 0x3C
} RFLiHDBManager;

void RFLiInitHiddenDatabase(void);

#ifdef __cplusplus
}
#endif
#endif
