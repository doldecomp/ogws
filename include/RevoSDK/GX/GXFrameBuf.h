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
    u16 SHORT_0x4;
    u16 SHORT_0x6;
    u16 SHORT_0x8;
    u16 SHORT_0xA;
    u16 SHORT_0xC;
    u16 SHORT_0xE;
    u16 SHORT_0x10;
    u16 UNUSED_0x12;
    u32 INT_0x14;
    u8 BYTE_0x18;
    u8 BYTE_0x19;
    u8 BYTES_0x1A[24];
    u8 BYTE_0x32;
    u8 BYTE_0x33;
    u8 BYTE_0x34;
    u8 BYTE_0x35;
    u8 BYTE_0x36;
    u8 BYTE_0x37;
    u8 BYTE_0x38;
} GXRenderModeObj;

UNKTYPE GXCopyDisp(UNKTYPE *, u8);

#ifdef __cplusplus
}
#endif
#endif