#ifndef RVL_SDK_DVD_ERROR_H
#define RVL_SDK_DVD_ERROR_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef void (*DVDErrorCallback)(s32 result, s32 arg1);

typedef struct DVDErrorInfo {
    char game[4]; // at 0x0
    u8 disk;      // at 0x1
    u8 revision;  // at 0x2
    u32 error;    // at 0x8
    s32 time;     // at 0xC
    u32 disr;     // at 0x10
    u32 dicr;     // at 0x14
    u32 next;     // at 0x18
    char UNK_1C[0x80 - 0x1C];
} DVDErrorInfo;

extern DVDErrorInfo __ErrorInfo;

void __DVDStoreErrorCode(u32 error, DVDErrorCallback callback);

#ifdef __cplusplus
}
#endif
#endif
