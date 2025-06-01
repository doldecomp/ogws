#ifndef RVL_SDK_DVD_H
#define RVL_SDK_DVD_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

// OS sets MSB to signal that the device code was successfully read
#define DVD_DEVICE_CODE_READ (1 << 15)
#define MAKE_DVD_DEVICE_CODE(x) (DVD_DEVICE_CODE_READ | (x))

// Forward declarations
typedef struct DVDCommandBlock DVDCommandBlock;
typedef struct DVDFileInfo DVDFileInfo;
typedef struct OSAlarm OSAlarm;

typedef enum {
    DVD_RESULT_COVER_CLOSED = -4,
    DVD_RESULT_CANCELED,
    DVD_RESULT_IGNORED,
    DVD_RESULT_FATAL_ERROR,
    DVD_RESULT_GOOD,
} DVDResult;

typedef enum {
    DVD_STATE_FATAL = -1,
    DVD_STATE_IDLE,
    DVD_STATE_BUSY,
    DVD_STATE_WAITING,
    DVD_STATE_COVER_CLOSED,
    DVD_STATE_NO_DISK,
    DVD_STATE_COVER_OPENED,
    DVD_STATE_WRONG_DISK_ID,
    DVD_STATE_7,
    DVD_STATE_PAUSED,
    DVD_STATE_9,
    DVD_STATE_CANCELED,
    DVD_STATE_DISK_ERROR,
    DVD_STATE_MOTOR_STOPPED,
} DVDAsyncState;

typedef enum {
    DVD_COVER_BUSY,
    DVD_COVER_OPENED,
    DVD_COVER_CLOSED,
} DVDCoverState;

typedef void (*DVDAsyncCallback)(s32 result, DVDFileInfo* info);
typedef void (*DVDCommandCallback)(s32 result, DVDCommandBlock* block);

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
    DVDCommandBlock* next;       // at 0x0
    DVDCommandBlock* prev;       // at 0x4
    u32 command;                 // at 0x8
    volatile s32 state;          // at 0xC
    u32 offset;                  // at 0x10
    u32 length;                  // at 0x14
    void* addr;                  // at 0x18
    u32 transferSize;            // at 0x1C
    u32 transferTotal;           // at 0x20
    DVDDiskID* id;               // at 0x24
    DVDCommandCallback callback; // at 0x28
    void* userData;              // at 0x2C
} DVDCommandBlock;

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

extern volatile u32 __DVDLayoutFormat;

void DVDInit(void);
BOOL DVDReadAbsAsyncPrio(DVDCommandBlock* block, void* dst, u32 size,
                         u32 offset, DVDCommandCallback callback, s32 prio);
BOOL DVDInquiryAsync(DVDCommandBlock* block, DVDDriveInfo* info,
                     DVDCommandCallback callback);
s32 DVDGetCommandBlockStatus(const DVDCommandBlock* block);
s32 DVDGetDriveStatus(void);
void DVDPause(void);
void DVDResume(void);
BOOL DVDCancelAsync(DVDCommandBlock* block, DVDCommandCallback callback);
s32 DVDCancel(DVDCommandBlock* block);
BOOL DVDCancelAllAsync(DVDCommandCallback callback);
const DVDDiskID* DVDGetCurrentDiskID(void);
u32 __DVDGetCoverStatus(void);
void __DVDPrepareResetAsync(DVDCommandCallback callback);
void __DVDPrepareReset(void);
BOOL __DVDTestAlarm(const OSAlarm* alarm);
BOOL __DVDLowBreak(void);
BOOL __DVDStopMotorAsync(DVDCommandBlock* block, DVDCommandCallback callback);
void __DVDRestartMotor(void);

#ifdef __cplusplus
}
#endif
#endif
