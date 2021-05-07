#ifndef REVOSDK_VI_H
#define REVOSDK_VI_H
#ifdef __cplusplus
#include <types.h>
#include <GX/GXFrameBuf.h>
extern "C" {
#endif

void VIInit(void);
void VISetBlack(UNKWORD);
void VIConfigure(_GXRenderModeObj *);
void VIWaitForRetrace(void);
void VIFlush(void);

UNKTYPE * VIGetCurrentFrameBuffer(void);

UNKTYPE VISetNextFrameBuffer(UNKTYPE *);

enum VITvFormat
{
    VI_NTSC = 0,
    VI_PAL50 = 1
};

VITvFormat VIGetTvFormat(void);

#ifdef __cplusplus
}
#endif
#endif