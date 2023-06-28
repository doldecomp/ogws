#ifndef RVL_FACE_LIBRARY_INTERNAL_DATABASE_H
#define RVL_FACE_LIBRARY_INTERNAL_DATABASE_H
#include <RVLFaceLib/RFLi_HiddenDatabase.h>
#include <RVLFaceLib/RFLi_Types.h>
#include <revolution/OS.h>
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations
typedef struct MEMiHeapHead;

typedef struct RFLiDatabase {
    u32 identifier;                           // at 0x0
    RFLiCharRawData rawData[RFL_DB_CHAR_MAX]; // at 0x4

    u32 isolation : 1; // at 0x1CEC
    u32 padding1 : 31;

    u8 specialInvite[13]; // at 1CF0
    u8 nwc24Month;        // at 0x1CFD
    u8 mwc24Day;          // at 0x1CFE
    u8 padding2;          // at 0x1CFF

    RFLiHiddenDB hidden; // at 0x1D00
} RFLiDatabase;

typedef struct RFLiCRCInfo {
    void* head;                 // at 0x0
    u32 size;                   // at 0x4
    u8* current;                // at 0x8
    u32 count;                  // at 0xC
    u16 crc;                    // at 0x10
    OSAlarm alarm;              // at 0x18
    RFLiAsyncCallback callback; // at 0x48
} RFLiCRCInfo;

typedef struct RFLiDBManager {
    RFLiDatabase* database;  // at 0x0
    RFLiCallback saveCb;     // at 0x4
    RFLiCallback formatCb;   // at 0x8
    RFLiCallback bootloadCb; // at 0xC
    RFLiOpenType saveType;   // at 0x10
    RFLiCharRawData trg;     // at 0x14
    RFLiCRCInfo crcInfo;     // at 0x60
} RFLiDBManager;

void RFLiInitDatabase(struct MEMiHeapHead*);

RFLErrcode RFLiBootLoadDatabaseAsync(RFLiCallback);

BOOL RFLiIsSameID(const u8[RFL_CREATEID_LEN], const u8[RFL_CREATEID_LEN]);

void RFLiConvertRaw2Info(const RFLiCharRawData*, RFLiCharInfo*);
void RFLiConvertHRaw2Info(const RFLiCharHRawData*, RFLiCharInfo*);

RFLiHiddenDB* RFLiGetHiddenHeader(void);

BOOL RFLiIsValidID(const u8[RFL_CREATEID_LEN]);

BOOL RFLiDBIsLoaded(void);

#ifdef __cplusplus
}
#endif
#endif
