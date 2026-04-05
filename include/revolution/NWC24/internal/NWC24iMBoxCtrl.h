#ifndef RVL_SDK_NWC24_INTERNAL_MBOX_CTRL_H
#define RVL_SDK_NWC24_INTERNAL_MBOX_CTRL_H
#include <types.h>

#include <revolution/NWC24/NWC24Types.h>
#include <revolution/NWC24/internal/NWC24iMsgObj.h>
#ifdef __cplusplus
extern "C" {
#endif

#define NWC24i_MBOX_DIR_LENGTH 64
#define NWC24i_MBOX_MAX_SIZE 0x31C00

typedef struct NWC24iMBCHeader {
    u32 magic;               // at 0x0
    u32 version;             // at 0x4
    u32 numMsgs;             // at 0x8
    u32 capacity;            // at 0xC
    u32 totalMsgSize;        // at 0x10
    u32 fileSize;            // at 0x14
    u32 nextMsgId;           // at 0x18
    u32 freeChain;           // at 0x1C
    u32 oldestMsgId;         // at 0x20
    u32 freeSpace;           // at 0x24
    u8 padding[0x80 - 0x28]; // at 0x28
} NWC24iMBCHeader;

typedef struct NWC24iMBCEntry {
    u32 id;                                                // at 0x0
    u32 flags;                                             // at 0x4
    u32 length;                                            // at 0x8
    u32 appId;                                             // at 0xC
    u32 unk10;                                             // at 0x10
    u32 tag;                                               // at 0x14
    u32 command;                                           // at 0x18
    u32 unk1C;                                             // at 0x1C
    NWC24iAddr from;                                       // at 0x20
    s32 createTime;                                        // at 0x28
    u32 unk2C;                                             // at 0x2C
    u8 numTo;                                              // at 0x30
    u8 numAttached;                                        // at 0x31
    u16 groupId;                                           // at 0x32
    u32 fromField;                                         // at 0x34
    u32 toField;                                           // at 0x38
    u32 subject;                                           // at 0x3C
    u32 contentType;                                       // at 0x40
    u32 txEncoding;                                        // at 0x44
    NWC24Data text;                                        // at 0x48
    NWC24Data attached[NWC24i_MSG_ATTACHMENT_MAX];         // at 0x50
    u32 attachedSize[NWC24i_MSG_ATTACHMENT_MAX];           // at 0x60
    NWC24MIMEType attachedType[NWC24i_MSG_ATTACHMENT_MAX]; // at 0x68
    NWC24Data dwcId;                                       // at 0x70
    u32 unk78;                                             // at 0x78
    u32 unk7C;                                             // at 0x7C
} NWC24iMBCEntry;

NWC24Err NWC24iOpenMBox(void);
NWC24Err NWC24iMBoxGetCtrlFilePath(NWC24MsgBoxId id, char* pDst, s32 maxlen);
NWC24Err NWC24iMBoxOpenNewMsg(NWC24MsgBoxId id, NWC24File* pFile, u32* pMsgID);
NWC24Err NWC24iMBoxCloseMsg(NWC24File* pFile);
NWC24Err NWC24iMBoxCancelMsg(NWC24File* pFile, NWC24MsgBoxId id, u32 msgId);
NWC24Err NWC24iMBoxAddMsgObj(NWC24MsgBoxId id, NWC24iMsgObj* pMsg);
NWC24Err NWC24iMBoxFlushHeader(NWC24MsgBoxId id);
NWC24Err NWC24iMBoxCheck(NWC24MsgBoxId id, u32 size);

#ifdef __cplusplus
}
#endif
#endif
