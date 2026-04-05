#ifndef RVL_SDK_NWC24_INTERNAL_MSG_OBJ_H
#define RVL_SDK_NWC24_INTERNAL_MSG_OBJ_H
#include <types.h>

#include <revolution/NWC24/NWC24Types.h>
#include <revolution/NWC24/NWC24Utils.h>
#ifdef __cplusplus
extern "C" {
#endif

#define NWC24i_MSG_RECIPIENT_MAX 8
#define NWC24i_MSG_ATTACHMENT_MAX 2

// wXXXXXXXXXXXXXXXX@wii.com
#define NWC24i_WII_ID_LEN 16

// X-AAAAAAAA-GGGG
#define NWC24i_APP_ID_LEN 15

// %05X%08X%08X%08X
#define NWC24i_MSG_ID_LEN 30

#define NWC24i_MSGOBJ_GET_MB_NOREPLY(pObj) ((pObj)->msgBoard & 0x80000000)
#define NWC24i_MSGOBJ_SET_MB_NOREPLY(pObj, x)                                  \
    ((x) ? ((pObj)->msgBoard |= 0x80000000) : ((pObj)->msgBoard &= ~0x80000000))

#define NWC24i_MSGOBJ_GET_MB_DELAY(pObj) ((pObj)->msgBoard & 0x00FF0000)
#define NWC24i_MSGOBJ_SET_MB_DELAY(pObj, x)                                    \
    ((pObj)->msgBoard = ((pObj)->msgBoard & ~0x00FF0000) | ((x) & 0x00FF0000))

#define NWC24i_MSGOBJ_GET_MB_REGDATE(pObj) ((pObj)->msgBoard & 0x0000FFFF)
#define NWC24i_MSGOBJ_SET_MB_REGDATE(pObj, x)                                  \
    ((pObj)->msgBoard = ((pObj)->msgBoard & ~0x0000FFFF) | ((x) & 0x0000FFFF))

typedef enum NWC24iMsgObjFlags {
    NWC24_MSGOBJ_FOR_RECIPIENT = 1 << 0,
    NWC24_MSGOBJ_FOR_PUBLIC = 1 << 1,
    NWC24_MSGOBJ_FOR_APP = 1 << 2,
    NWC24_MSGOBJ_FOR_MENU = 1 << 3,
    NWC24_MSGOBJ_TO_SEND = 1 << 4,
    NWC24_MSGOBJ_TO_RECV = 1 << 5,
    NWC24_MSGOBJ_INITIALIZED = 1 << 8,
    NWC24_MSGOBJ_DELIVERING = 1 << 9,
    NWC24_MSGOBJ_DWC = 1 << 13,
    NWC24_MSGOBJ_MULTIPART = 1 << 16,
    NWC24_MSGOBJ_FLAG_20 = 1 << 20,
} NWC24iMsgObjFlags;

typedef union NWC24iAddr {
    u64 id;
    NWC24Data data;
} NWC24iAddr;

typedef struct NWC24iMsgObj {
    u32 id;     // at 0x0
    u32 flags;  // at 0x4
    u32 length; // at 0x8
    u32 appId;  // at 0xC
    s32 unk10;
    u32 tag;     // at 0x14
    u32 command; // at 0x18
    u32 unk1C;
    NWC24iAddr from; // at 0x20
    s32 createTime;  // at 0x28
    u32 unk2C;
    NWC24Data fromField;                                   // at 0x30
    NWC24Data toField;                                     // at 0x38
    NWC24Data subject;                                     // at 0x40
    NWC24Data text;                                        // at 0x48
    NWC24Data contentType;                                 // at 0x50
    NWC24Data txEncoding;                                  // at 0x58
    NWC24Charset charset;                                  // at 0x60
    NWC24Encoding encoding;                                // at 0x64
    NWC24Data attached[NWC24i_MSG_ATTACHMENT_MAX];         // at 0x68
    u32 attachedSize[NWC24i_MSG_ATTACHMENT_MAX];           // at 0x78
    NWC24MIMEType attachedType[NWC24i_MSG_ATTACHMENT_MAX]; // at 0x80
    union {
        NWC24iAddr to[NWC24i_MSG_RECIPIENT_MAX];
    }; // at 0x88
    u8 numTo;        // at 0xC8
    u8 numAttached;  // at 0xC9
    u16 groupId;     // at 0xCA
    u32 msgBoard;    // at 0xCC
    NWC24Data user;  // at 0xD0
    NWC24Data face;  // at 0xD8
    NWC24Data alt;   // at 0xE0
    NWC24Data dwcId; // at 0xE8
    u32 iconNew;     // at 0xF0
    char unkF0[0x100 - 0xF4];
} NWC24iMsgObj;

#ifdef __cplusplus
}
#endif
#endif
