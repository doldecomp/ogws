#ifndef RVL_FACE_LIBRARY_INTERNAL_DATA_UTILITY_H
#define RVL_FACE_LIBRARY_INTERNAL_DATA_UTILITY_H
#include <types.h>

#include <RVLFaceLib/RFLi_Types.h>
#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations
typedef struct RFLMiddleDB;

BOOL RFLiCheckValidInfo(const RFLiCharInfo* info);
#if defined(VERSION_RSPE01_01)
BOOL RFLiIsValidOnNAND(const RFLiCharInfo* info);
#endif
BOOL RFLiIsSameFaceCore(const RFLiCharInfo* lhs, const RFLiCharInfo* rhs);
RFLErrcode RFLiPickupCharInfo(RFLiCharInfo* info, RFLDataSource source,
                              struct RFLMiddleDB* db, u16 index);
#if defined(VERSION_RSPE01_01)
BOOL RFLiCheckBirthday(u8 month, u8 day);
#endif

#ifdef __cplusplus
}
#endif
#endif
