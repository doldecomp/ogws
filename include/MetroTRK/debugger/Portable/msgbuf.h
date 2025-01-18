#ifndef METROTRK_DEBUGGER_PORTABLE_MSGBUF_H
#define METROTRK_DEBUGGER_PORTABLE_MSGBUF_H
#include <MetroTRK/debugger/portable/mutex_TRK.h>
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

#define kMessageBufferNum 3
#define kMessageBufferSize 2048 /* data block */ + 128 /* additional items */

typedef enum {
    kDSConnect = 1,
    kDSDisconnect,
    kDSReset,
    kDSVersions,
    kDSSupportMask,

    kDSOverride = 7,

    kDSReadMemory = 16,
    kDSWriteMemory,
    kDSReadRegisters,
    kDSWriteRegisters,

    kDSSetOption = 23,
    kDSContinue,
    kDSStep,
    kDSStop
} TRKMessageCommand;

typedef struct TRKMessageBuffer {
    TRKMutex mutex;                         // at 0x0
    BOOL used;                              // at 0x4
    unsigned int size;                      // at 0x8
    unsigned int pos;                       // at 0xC
    unsigned char data[kMessageBufferSize]; // at 0x10
} TRKMessageBuffer;

#define TRKMessageBufferGet(buf, type, offset) (*(type*)(buf->data + offset))

extern TRKMessageBuffer gTRKMsgBufs[kMessageBufferNum];

DSError TRKReadBuffer_ui32(TRKMessageBuffer* buf, unsigned int* dst, int n);
DSError TRKReadBuffer_ui8(TRKMessageBuffer* buf, unsigned char* dst, int n);

DSError TRKReadBuffer1_ui64(TRKMessageBuffer* buf, unsigned long long* dst);
DSError TRKReadBuffer1_ui32(TRKMessageBuffer* buf, unsigned int* dst);
DSError TRKReadBuffer1_ui8(TRKMessageBuffer* buf, unsigned char* dst);

DSError TRKAppendBuffer_ui32(TRKMessageBuffer* buf, const unsigned int* x,
                             int n);
DSError TRKAppendBuffer_ui8(TRKMessageBuffer* buf, const unsigned char* x,
                            int n);

DSError TRKAppendBuffer1_ui32(TRKMessageBuffer* buf, unsigned int x);
DSError TRKAppendBuffer1_ui8(TRKMessageBuffer* buf, unsigned char x);
DSError TRKAppendBuffer1_ui64(TRKMessageBuffer* buf, unsigned long long x);

DSError TRKReadBuffer(TRKMessageBuffer* buf, void* dst, unsigned int n);
DSError TRKAppendBuffer(TRKMessageBuffer* buf, const void* src, unsigned int n);
DSError TRKSetBufferPosition(TRKMessageBuffer* buf, unsigned int pos);
void TRKResetBuffer(TRKMessageBuffer* buf, BOOL save);
void TRKReleaseBuffer(int i);
TRKMessageBuffer* TRKGetBuffer(int i);
DSError TRKGetFreeBuffer(int* id, TRKMessageBuffer** buffer);
DSError TRKInitializeMessageBuffers(void);

#ifdef __cplusplus
}
#endif
#endif