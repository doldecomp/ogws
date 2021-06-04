#ifndef REVOSDK_GX_FIFO_H
#define REVOSDK_GX_FIFO_H
#include <types.h>
#include <GX.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct _GXFifoObj
{
    // TO-DO
    char UNK_0x0[0x80];
} GXFifoObj;

void GXGetGPStatus(u8 *, u8 *, u8 *, u8 *, u8 *);

#ifdef __cplusplus
}
#endif
#endif