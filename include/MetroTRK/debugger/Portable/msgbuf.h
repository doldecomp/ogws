#ifndef METROTRK_DEBUGGER_PORTABLE_MSGBUF_H
#define METROTRK_DEBUGGER_PORTABLE_MSGBUF_H
#include <MetroTRK/debugger/portable/mutex_TRK.h>
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

#define kMessageBufferSize 2048 /* data block */ + 128 /* additional items */

typedef struct TRKMessageBuffer {
    TRKMutex mutex;                        // at 0x0
    BOOL used;                             // at 0x4
    unsigned int size;                     // at 0x8
    unsigned int pos;                      // at 0xC
    unsigned char buf[kMessageBufferSize]; // at 0x10
} TRKMessageBuffer;

void TRKReleaseBuffer(int i);

#ifdef __cplusplus
}
#endif
#endif