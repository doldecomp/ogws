#ifndef REVOSDK_GX_FRAME_BUF_H
#define REVOSDK_GX_FRAME_BUF_H
#include <types.h>
#include <GX.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct _GXRenderModeObj
{
    u32 INT_0x0;
    u16 mFbWidth; // at 0x4
    u16 mEfbHeight; // at 0x6
    u16 mFbHeight; // at 0x8
    u16 SHORT_0xA;
    u16 SHORT_0xC;
    u16 SHORT_0xE;
    u16 SHORT_0x10;
    u16 UNUSED_0x12;
    u32 INT_0x14;
    u8 BYTE_0x18;
    u8 BYTE_0x19;
    u8 BYTES_0x1A[24];
    u8 BYTES_0x32[7];
} GXRenderModeObj;

extern GXRenderModeObj GXNtsc480IntDf;
extern GXRenderModeObj GXPal528IntDf;
extern GXRenderModeObj GXEurgb60Hz480IntDf;
extern GXRenderModeObj GXMpal480IntDf;

UNKTYPE GXCopyDisp(UNKTYPE *, u8);
UNKTYPE GXSetCopyClear(GXColor, UNKWORD zClear);
UNKTYPE GXSetCopyFilter(u8, u8(*)[24], u8, u8(*)[7]);

#ifdef __cplusplus
}
#endif
#endif