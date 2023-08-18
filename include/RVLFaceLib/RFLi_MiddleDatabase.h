#ifndef RVL_FACE_LIBRARY_INTERNAL_MIDDLE_DATABASE_H
#define RVL_FACE_LIBRARY_INTERNAL_MIDDLE_DATABASE_H
#include <RVLFaceLib/RFL_MiddleDatabase.h>
#include <RVLFaceLib/RFLi_Types.h>
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct RFLiMiddleDB {
    RFLMiddleDBType type;   // at 0x0
    RFLiCallback callback;  // at 0x4
    RFLiCharHRawData* data; // at 0x8
    u16 size;               // at 0xC
    u16 storedSize;         // at 0xE
    u32 userData1;          // at 0x10
    u32 userData2;          // at 0x14
} RFLiMiddleDB;

typedef struct RFLiMiddleDBRandomMask {
    u8 sex;     // at 0x0
    u8 age;     // at 0x1
    u8 race;    // at 0x2
    u8 padding; // at 0x3
} RFLiMiddleDBRandomMask;

typedef struct RFLiMiddleDBHiddenMask {
    u16 dstIdx; // at 0x0
    u8 sex;     // at 0x2
    u8 padding; // at 0x3
} RFLiMiddleDBHiddenMask;

typedef struct RFLiMiddleDBHiddenParam {
    s32 sex : 2;
    s32 srcIdx : 15;
    s32 dstIdx : 15;
} RFLiMiddleDBHiddenParam;

typedef struct RFLiMiddleDBHiddenParam2 {
    s16 lastSrcIdx; // at 0x0
    u16 padding;    // at 0x2
} RFLiMiddleDBHiddenParam2;

RFLErrcode RFLiUpdateMiddleDBAsync(RFLMiddleDB* db, RFLiCallback cb,
                                   BOOL cache);
BOOL RFLiGetCharInfoMiddleDB(RFLiCharInfo* info, const RFLMiddleDB* db,
                             u16 index);
RFLErrcode RFLiAddMiddleDBUserData(RFLMiddleDB* db, RFLiCharRawData* raw);

#ifdef __cplusplus
}
#endif
#endif
