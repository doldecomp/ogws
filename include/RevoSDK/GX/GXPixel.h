#ifndef REVOSDK_GX_PIXEL_H
#define REVOSDK_GX_PIXEL_H
#include <types.h>
#include <GX.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef enum _GXFogType
{
    GX_FOG_TYPE_0,
    GX_FOG_TYPE_1,
    GX_FOG_TYPE_2,
} GXFogType;

// Unofficial name
typedef enum _GXPixelFmt
{
    GX_PIXEL_FMT_0,
    GX_PF_RGBA6_Z24,
    GX_PIXEL_FMT_2,
    GX_PIXEL_FMT_3,
    GX_PIXEL_FMT_4,
    GX_PIXEL_FMT_5,
    GX_PIXEL_FMT_6,
    GX_PIXEL_FMT_7,
} GXPixelFmt;

UNKTYPE GXSetFog(GXFogType, GXColor, float startz, float endz, float nearz, float farz);

UNKTYPE GXInitFogAdjTable(u16 *table, u16 width, const float (*)[4]);
UNKTYPE GXSetFogRangeAdj(u8, u16, u16 *table);

UNKTYPE GXSetBlendMode(UNKWORD, UNKWORD, UNKWORD, UNKWORD);

UNKTYPE GXSetColorUpdate(u8);
UNKTYPE GXSetAlphaUpdate(u8);
UNKTYPE GXSetZMode(UNKWORD, UNKWORD, UNKWORD);
UNKTYPE GXSetZCompLoc(UNKWORD);

UNKTYPE GXSetPixelFmt(GXPixelFmt, UNKWORD);
UNKTYPE GXSetDither(u8);
UNKTYPE GXSetDstAlpha(UNKWORD, UNKWORD);

#ifdef __cplusplus
}
#endif
#endif