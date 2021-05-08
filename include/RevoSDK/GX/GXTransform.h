#ifndef REVOSDK_GX_TRANSFORM_H
#define REVOSDK_GX_TRANSFORM_H
#include <types.h>
#include <GX.h>
#ifdef __cplusplus
extern "C" {
#endif

UNKTYPE GXSetScissor(u32, u32, u32, u32);
UNKTYPE GXSetScissorBoxOffset(u32, u32);

UNKTYPE GXSetViewport(f32, f32, f32, f32, f32, f32);
UNKTYPE GXSetViewportJitter(f32, f32, f32, f32, f32, f32, u32);

UNKTYPE GXSetProjection(float (*)[4], u32);

UNKTYPE GXLoadPosMtxImm(float (*)[4], u32);

#ifdef __cplusplus
}
#endif
#endif