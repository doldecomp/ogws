#ifndef REVOSDK_GX_TEV_H
#define REVOSDK_GX_TEV_H
#include <types.h>
#include <GX.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef enum _GXTevSwapSel
{
	GX_TEV_SWAP_SEL_0,
	GX_TEV_SWAP_SEL_1,
	GX_TEV_SWAP_SEL_2,
	GX_TEV_SWAP_SEL_3,
	GX_TEV_SWAP_SEL_COUNT
} GXTevSwapSel;

typedef enum _GXTevColorChan
{
	
} GXTevColorChan;

typedef enum _GXTevStageID
{
	GX_TEV_STAGE_0,
	GX_TEV_STAGE_1,
	GX_TEV_STAGE_2,
	GX_TEV_STAGE_COUNT = 16
} GXTevStageID;

typedef enum _GXTevColorArg
{
	
} GXTevColorArg;

typedef enum _GXTevRegID
{
	GX_TEV_REG_ID_0,
	GX_TEV_REG_ID_1,
	GX_TEV_REG_ID_2,
	GX_TEV_REG_ID_3,
} GXTevRegID;

UNKTYPE GXSetTevOp(GXTevStageID, UNKWORD tevMode);
UNKTYPE GXSetTevColorIn(GXTevStageID, UNKWORD a, UNKWORD b, UNKWORD c, UNKWORD d);
UNKTYPE GXSetTevAlphaIn(GXTevStageID, UNKWORD a, UNKWORD b, UNKWORD c, UNKWORD d);
UNKTYPE GXSetTevColorOp(GXTevStageID, UNKWORD, UNKWORD, UNKWORD, UNKWORD, UNKWORD);
UNKTYPE GXSetTevAlphaOp(GXTevStageID, UNKWORD, UNKWORD, UNKWORD, UNKWORD, UNKWORD);
UNKTYPE GXSetTevColor(GXTevRegID, GXColor);

UNKTYPE GXSetTevSwapModeTable(GXTevSwapSel, UNKWORD, UNKWORD, UNKWORD, UNKWORD);

UNKTYPE GXSetZTexture(UNKWORD, UNKWORD zTexFormat, UNKWORD);

UNKTYPE GXSetNumTevStages(UNKWORD);

#ifdef __cplusplus
}
#endif
#endif