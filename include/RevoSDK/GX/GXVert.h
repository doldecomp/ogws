#ifndef REVOSDK_GX_VERT__H
#define REVOSDK_GX_VERT_H
#include <types.h>
#include <GX.h>
#ifdef __cplusplus
extern "C" {
#endif

static void GXPosition3f32(f32 x, f32 y, f32 z)
{
    WGPIPE.f = x;
    WGPIPE.f = y;
    WGPIPE.f = z;
}

static void GXColor1u32(u32 c)
{
    WGPIPE.i = c;
}

static void GXTexCoord2u16(u16 c1, u16 c2)
{
    WGPIPE.s = c1;
    WGPIPE.s = c2;
}

#ifdef __cplusplus
}
#endif
#endif