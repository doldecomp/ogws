#ifndef RVL_SDK_NWC24_MSG_COMMIT_H
#define RVL_SDK_NWC24_MSG_COMMIT_H
#include <types.h>

#include <revolution/NWC24/NWC24Types.h>
#include <revolution/NWC24/NWC24Utils.h>
#ifdef __cplusplus
extern "C" {
#endif

#define NWC24_WORK_BUFFER_SIZE 1024

// Forward declarations
typedef struct NWC24MsgObj NWC24MsgObj;

NWC24Err NWC24CommitMsg(NWC24MsgObj*);

typedef union {
    u64 id;
    NWC24Data data;
} NWC24AddrId;

#ifdef __cplusplus
}
#endif
#endif
