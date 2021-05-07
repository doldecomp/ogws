#ifndef REVOSDK_GX_FRAME_BUF_H
#define REVOSDK_GX_FRAME_BUF_H
#include <types.h>
#include <GX.h>
#ifdef __cplusplus
extern "C" {
#endif

struct _GXRenderModeObj
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
    u8 BYTE_0x1A;
    u8 BYTE_0x1B;
    u8 BYTE_0x1C;
    u8 BYTE_0x1D;
    u8 BYTE_0x1E;
    u8 BYTE_0x1F;
    u8 BYTE_0x20;
    u8 BYTE_0x21;
    u8 BYTE_0x22;
    u8 BYTE_0x23;
    u8 BYTE_0x24;
    u8 BYTE_0x25;
    u8 BYTE_0x26;
    u8 BYTE_0x27;
    u8 UNUSED_0x28;
    u8 BYTE_0x29;
    u8 BYTE_0x2A;
    u8 BYTE_0x2B;
    u8 BYTE_0x2C;
    u8 BYTE_0x2D;
    u8 BYTE_0x2E;
    u8 BYTE_0x2F;
    u8 BYTE_0x30;
    u8 BYTE_0x31;
    u8 BYTE_0x32;
    u8 BYTE_0x33;
    u8 BYTE_0x34;
    u8 BYTE_0x35;
    u8 BYTE_0x36;
    u8 BYTE_0x37;
    u8 BYTE_0x38;
};

UNKTYPE GXCopyDisp(UNKTYPE *, u8);

#ifdef __cplusplus
}
#endif
#endif