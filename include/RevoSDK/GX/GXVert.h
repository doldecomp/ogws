#ifndef REVOSDK_GX_VERT_H
#define REVOSDK_GX_VERT_H
#include <types.h>
#include <GX.h>
#ifdef __cplusplus
extern "C" {
#endif

void GXPosition3f32(f32 x, f32 y, f32 z)
{
    WGPIPE.f = x;
    WGPIPE.f = y;
    WGPIPE.f = z;
}

void GXColor1u32(u32 c)
{
    WGPIPE.i = c;
}

void GXTexCoord2u16(u16 c1, u16 c2)
{
    WGPIPE.s = c1;
    WGPIPE.s = c2;
}

void GXCmd1u8(u8 uc)
{
    WGPIPE.c = uc;
}

void GXCmd1u16(u16 us)
{
    WGPIPE.s = us;
}

void GXCmd1u32(u32 ul)
{
    WGPIPE.i = ul;
}

#ifdef __cplusplus
}
#endif
#endif