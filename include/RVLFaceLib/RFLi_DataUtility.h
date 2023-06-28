#ifndef RVL_FACE_LIBRARY_INTENRAL_DATA_UTILITY_H
#define RVL_FACE_LIBRARY_INTERNAL_DATA_UTILITY_H
#include <RVLFaceLib/RFLi_Types.h>
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations
typedef struct RFLiCharInfo;
typedef struct RFLMiddleDB;

RFLErrcode RFLiPickupCharInfo(RFLiCharInfo*, RFLDataSource, struct RFLMiddleDB*,
                              u16);

BOOL RFLiCheckValidInfo(const RFLiCharInfo*);
BOOL RFLiIsValidOnNAND(const RFLiCharInfo*);

#ifdef __cplusplus
}
#endif
#endif
