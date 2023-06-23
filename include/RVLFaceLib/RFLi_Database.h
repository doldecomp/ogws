#ifndef RVL_FACE_LIBRARY_INTERNAL_DATABASE_H
#define RVL_FACE_LIBRARY_INTERNAL_DATABASE_H
#include <RVLFaceLib/RFLi_Types.h>
#include <revolution/OS.h>
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations
typedef struct MEMiHeapHead;

// TODO: 0x34a009
typedef struct RFLiDatabase {
    u8 dummy[0x1F1E0];
} RFLiDatabase;

// TODO: IDK what this name is
// 0x3491af
typedef struct RFLiTrg {
    u8 dummy[0x4A];
} RFLiTrg;

// TODO: 0x34a921
typedef struct RFLiDBCharInfo {
    u8 dummy[0x40];
} RFLiDBCharInfo;

typedef struct RFLiCRCInfo {
    void* head;                 // at 0x0
    u32 size;                   // at 0x4
    u8* current;                // at 0x8
    u32 count;                  // at 0xC
    u16 crc;                    // at 0x10
    OSAlarm alarm;              // at 0x18
    RFLiAlarmCallback callback; // at 0x48
} RFLiCRCInfo;

typedef struct RFLiDBManager {
    RFLiDatabase* database;          // at 0x0
    RFLiDatabaseCallback saveCb;     // at 0x4
    RFLiDatabaseCallback formatCb;   // at 0x8
    RFLiDatabaseCallback bootloadCb; // at 0xC
    RFLiOpenType saveType;           // at 0x10
    RFLiTrg trg;                     // at 0x14
    RFLiCRCInfo crcInfo;             // at 0x60
} RFLiDBManager;

void RFLiInitDatabase(struct MEMiHeapHead*);

RFLErrcode RFLiBootLoadDatabaseAsync(RFLiDatabaseCallback);

#ifdef __cplusplus
}
#endif
#endif
