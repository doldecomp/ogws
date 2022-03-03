#ifndef REVOSDK_GX_BUMP_H
#define REVOSDK_GX_BUMP_H
#include <types.h>
#include <GXTev.h>
#include <GXTexture.h>
#include <math/mtx.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef enum _GXIndTexStageID
{
    GX_IND_TEX_STAGE_0
} GXIndTexStageID;

typedef enum _GXIndTexScale
{
    GX_IND_TEX_SCALE_0
} GXIndTexScale;

typedef enum _GXIndTexMtxID
{
    GX_IND_TEX_MTX_0
} GXIndTexMtxID;

UNKTYPE GXSetIndTexCoordScale(GXIndTexStageID, GXIndTexScale, GXIndTexScale);
UNKTYPE GXSetIndTexMtx(GXIndTexMtxID, const f32 *, UNKWORD);

UNKTYPE GXSetNumIndStages(UNKWORD);
UNKTYPE GXSetTevDirect(UNKWORD);

UNKTYPE __GXSetIndirectMask(UNKWORD);

UNKTYPE GXSetTevSwapMode(GXTevStageID, UNKWORD, UNKWORD);

UNKTYPE GXSetTevOrder(GXTevStageID, GXTexCoordID, GXTexMapID, UNKWORD colorChanID);

#ifdef __cplusplus
}
#endif
#endif