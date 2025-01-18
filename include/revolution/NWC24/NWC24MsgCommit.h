#ifndef RVL_SDK_NWC24_MSG_COMMIT_H
#define RVL_SDK_NWC24_MSG_COMMIT_H
#include <types.h>

#include <revolution/NWC24/NWC24Types.h>
#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations
typedef struct NWC24MsgObj NWC24MsgObj;

NWC24Err NWC24CommitMsg(NWC24MsgObj*);

#ifdef __cplusplus
}
#endif
#endif
