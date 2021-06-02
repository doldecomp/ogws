#ifndef REVOSDK_GX_PIXEL_H
#define REVOSDK_GX_PIXEL_H
#include <types.h>
#include <GX.h>
#ifdef __cplusplus
extern "C" {
#endif

UNKTYPE GXSetFog(int, GXColor, float, float, float nearz, float farz);

UNKTYPE GXInitFogAdjTable(u16 *table, u16 width, const float (*)[4]);
UNKTYPE GXSetFogRangeAdj(u8, u16, u16 *table);

UNKTYPE GXSetBlendMode(UNKWORD, UNKWORD, UNKWORD, UNKWORD);

UNKTYPE GXSetColorUpdate(UNKWORD);
UNKTYPE GXSetAlphaUpdate(UNKWORD);
UNKTYPE GXSetZMode(UNKWORD, UNKWORD, UNKWORD);
UNKTYPE GXSetZCompLoc(UNKWORD);

UNKTYPE GXSetDstAlpha(UNKWORD, UNKWORD);

#ifdef __cplusplus
}
#endif
#endif