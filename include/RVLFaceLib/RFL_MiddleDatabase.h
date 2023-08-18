#ifndef RVL_FACE_LIBRARY_MIDDLE_DATABASE_H
#define RVL_FACE_LIBRARY_MIDDLE_DATABASE_H
#include <RVLFaceLib/RFL_Types.h>
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    RFLMiddleDBType_HiddenRandom,
    RFLMiddleDBType_HiddenNewer,
    RFLMiddleDBType_HiddenOlder,
    RFLMiddleDBType_Random,
    RFLMiddleDBType_UserSet,
    RFLMiddleDBType_Reserved1
} RFLMiddleDBType;

typedef struct RFLMiddleDB {
    u8 dummy[0x18];
} RFLMiddleDB;

u32 RFLGetMiddleDBBufferSize(u16 size);
void RFLInitMiddleDB(RFLMiddleDB* db, RFLMiddleDBType type, void* buffer,
                     u16 size);
RFLErrcode RFLUpdateMiddleDBAsync(RFLMiddleDB* db);
u16 RFLGetMiddleDBStoredSize(const RFLMiddleDB* db);
void RFLSetMiddleDBRandomMask(RFLMiddleDB* db, RFLSex sex, RFLAge age,
                              RFLRace race);
void RFLSetMiddleDBHiddenMask(RFLMiddleDB* db, RFLRace race);
RFLErrcode RFLAddMiddleDBStoreData(RFLMiddleDB* db, RFLRace race);

#ifdef __cplusplus
}
#endif
#endif
