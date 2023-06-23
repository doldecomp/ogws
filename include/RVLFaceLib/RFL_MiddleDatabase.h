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

#ifdef __cplusplus
}
#endif
#endif
