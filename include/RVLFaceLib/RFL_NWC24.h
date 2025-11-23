#ifndef RVL_FACE_LIBRARY_NWC24_H
#define RVL_FACE_LIBRARY_NWC24_H
#include <types.h>

#include <RVLFaceLib/RFL_Types.h>
#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations
typedef struct NWC24MsgObj;

RFLErrcode RFLCommitNWC24Msg(struct NWC24MsgObj* msg, u16 index);

#ifdef __cplusplus
}
#endif
#endif
