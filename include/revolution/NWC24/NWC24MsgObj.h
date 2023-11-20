#ifndef RVL_SDK_NWC24_MSG_OBJ_H
#define RVL_SDK_NWC24_MSG_OBJ_H
#include <revolution/NWC24/NWC24Types.h>
#include <revolution/NWC24/NWC24Utils.h>
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations
typedef struct RFLCharData;

typedef struct NWC24MsgObj {
    u32 id; // at 0x0
    char _04[0x8];
    u32 app; // at 0xC
    char _10[0x4];
    u32 tag; // at 0x14
    char _18[0x40 - 0x18];
    NWC24Data subject; // at 0x40
    NWC24Data text;    // at 0x48
    char _50[0xD8 - 0x50];
    NWC24Data face; // at 0xD8
    char _E0[0x100 - 0xE0];
} NWC24MsgObj;

NWC24Err NWC24SetMsgFaceData(NWC24MsgObj*, const struct RFLCharData*);

#ifdef __cplusplus
}
#endif
#endif
