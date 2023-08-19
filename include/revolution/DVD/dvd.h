#ifndef RVL_SDK_DVD_H
#define RVL_SDK_DVD_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations
typedef struct DVDCommandBlock;
typedef struct DVDFileInfo;
typedef struct OSAlarm;

typedef void (*DVDAsyncCallback)(s32 result, struct DVDFileInfo* info);
typedef void (*DVDCommandCallback)(s32 result, struct DVDCommandBlock* block);

typedef struct DVDDiskID {
    char game[4];    // at 0x0
    char company[2]; // at 0x4
    u8 disk;         // at 0x6
    u8 version;      // at 0x7
    u8 strmEnable;   // at 0x8
    u8 strmBufSize;  // at 0x9
    u8 padding[14];  // at 0xA
    u32 rvlMagic;    // at 0x18
    u32 gcMagic;     // at 0x1C
} DVDDiskID;

typedef struct DVDCommandBlock {
    struct DVDCommandBlock* next; // at 0x0
    struct DVDCommandBlock* prev; // at 0x4
    u32 command; // at 0x8
    s32 state; // at 0xC
    u32 offset; // at 0x10
    u32 length; // at 0x14
    void* addr; // at 0x18
    u32 transferSize; // at 0x1C
    u32 transferTotal; // at 0x20
    DVDDiskID* id; // at 0x24
    DVDCommandCallback callback; // at 0x28
    void* userData; // at 0x2C
} DVDCommandBlock;

typedef struct DVDDriveBlock {
    char UNK_0x0[0xC];
    UNKWORD WORD_0xC;
    char UNK_0x10[0x30 - 0x10];
} DVDDriveBlock;

typedef struct DVDDriveInfo {
    u16 revision;    // at 0x0
    u16 deviceCode;  // at 0x2
    u32 releaseDate; // at 0x4
    char padding[32 - 0x8];
} DVDDriveInfo;

typedef struct DVDFileInfo {
    DVDCommandBlock block;     // at 0x0
    u32 offset;                // at 0x30
    u32 size;                  // at 0x34
    DVDAsyncCallback callback; // at 0x38
} DVDFileInfo;

typedef void (*DVDInquiryCallback)(s32, DVDDriveBlock*);

extern u32 __DVDLayoutFormat;

void DVDInit(void);

BOOL DVDReadAbsAsyncPrio(DVDCommandBlock*, void*, u32, UNKWORD,
                         DVDCommandCallback, u32);

BOOL DVDInquiryAsync(DVDDriveBlock*, DVDDriveInfo*, DVDInquiryCallback);

s32 DVDGetCommandBlockStatus(DVDCommandBlock*);

s32 DVDCancelAsync(DVDFileInfo*, DVDCommandCallback);
s32 DVDCancel(DVDFileInfo*);

u32 __DVDGetCoverStatus(void);

void __DVDPrepareReset(void);
BOOL __DVDTestAlarm(struct OSAlarm*);

#ifdef __cplusplus
}
#endif
#endif
