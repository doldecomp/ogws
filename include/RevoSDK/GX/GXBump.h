#ifndef REVOSDK_GX_BUMP_H
#define REVOSDK_GX_BUMP_H
#include <types.h>
#include <GXTev.h>
#include <GXTexture.h>
#ifdef __cplusplus
extern "C" {
#endif

#define GX_IND_STAGES_MAX 4

UNKTYPE GXSetNumIndStages(UNKWORD);
UNKTYPE GXSetTevDirect(UNKWORD);

UNKTYPE __GXSetIndirectMask(UNKWORD);

UNKTYPE GXSetTevSwapMode(GXTevStageID, UNKWORD, UNKWORD);

UNKTYPE GXSetTevOrder(GXTevStageID, GXTexCoordID, GXTexMapID, UNKWORD colorChanID);

#ifdef __cplusplus
}
#endif
#endif