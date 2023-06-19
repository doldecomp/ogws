#ifndef REVOSDK_GX_TRANSFORM_H
#define REVOSDK_GX_TRANSFORM_H
#include <types.h>
#include <GX.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef enum _GXProjectionType 
{
    GX_PROJECTION_PERSP,
    GX_PROJECTION_ORTHO
} GXProjectionType;

UNKTYPE GXSetProjection(float (*)[4], u32);
UNKTYPE GXSetProjectionv(const f32 *);
UNKTYPE GXGetProjectionv(f32 *);

UNKTYPE GXLoadPosMtxImm(float (*)[4], u32);

UNKTYPE GXLoadTexMtxImm(float (*)[4], UNKWORD, UNKWORD type);

UNKTYPE GXSetCurrentMtx(UNKWORD);

UNKTYPE GXSetViewportJitter(f32, f32, f32, f32, f32, f32, u32);
UNKTYPE GXSetViewport(f32, f32, f32, f32, f32, f32);
UNKTYPE GXGetViewportv(f32[6]);

UNKTYPE GXSetScissor(u32 left, u32 top, u32 width, u32 height);
UNKTYPE GXGetScissor(u32 *, u32 *, u32 *, u32 *);
UNKTYPE GXSetScissorBoxOffset(u32 xOffset, u32 yOffset);

UNKTYPE GXSetClipMode(UNKWORD);

#ifdef __cplusplus
}
#endif
#endif