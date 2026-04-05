#ifndef RVL_SDK_NWC24_INTERNAL_MSG_COMMIT_H
#define RVL_SDK_NWC24_INTERNAL_MSG_COMMIT_H
#include <types.h>

#include <revolution/NWC24/NWC24Types.h>
#include <revolution/NWC24/internal/NWC24iMBoxCtrl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations
typedef struct NWC24iMsgObj NWC24iMsgObj;

NWC24Err NWC24CommitMsgInternal(NWC24iMsgObj* msg, NWC24MsgBoxId id);

#ifdef __cplusplus
}
#endif
#endif
