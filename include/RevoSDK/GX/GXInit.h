#ifndef REVOSDK_GX_INIT_H
#define REVOSDK_GX_INIT_H
#include <types.h>
#include <GX.h>
#include <GXFifo.h>
#ifdef __cplusplus
extern "C" {
#endif

GXFifoObj * GXInit(void *, u32);

#ifdef __cplusplus
}
#endif
#endif