#ifndef REVOSDK_GX_H
#define REVOSDK_GX_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

extern volatile union {
	char c;
	short s;
	int i;
	void * p;
	float f;
} WGPIPE : 0xcc008000;

typedef struct _GXColor
{
	u8 r;
	u8 g;
	u8 b;
	u8 a;
} GXColor;

typedef struct _GXColorS10
{
	u16 r;
	u16 g;
	u16 b;
	u16 a;
} GXColorS10;

typedef enum _GXChannelID
{
	GX_CHANNEL_ID_0,
	GX_CHANNEL_ID_1,
	GX_CHANNEL_ID_2,
	GX_CHANNEL_ID_3,
	GX_CHANNEL_ID_4,
	GX_CHANNEL_ID_5,
	GX_CHANNEL_ID_6,
	GX_CHANNEL_ID_7,
	GX_CHANNEL_ID_8,
	GX_CHANNEL_ID_INVALID = 0xFF
} GXChannelID;

static void GXEnd(void) {}

extern UNKTYPE GXBegin(UNKWORD, UNKWORD formatIndex, UNKWORD);

extern UNKTYPE GXSetFog(int, GXColor, float, float, float, float);
extern UNKTYPE GXInitFogAdjTable(u16 *, u16, const float (*)[4]);
extern UNKTYPE GXSetFogRangeAdj(u8, u16, u16 *);
extern UNKTYPE GXSetTevSwapModeTable(UNKWORD, UNKWORD, UNKWORD, UNKWORD, UNKWORD);
extern UNKTYPE GXSetZTexture(UNKWORD, UNKWORD, UNKWORD);
extern UNKTYPE GXSetChanCtrl(UNKWORD, UNKWORD, UNKWORD, UNKWORD, UNKWORD, UNKWORD, UNKWORD);

extern UNKTYPE GXSetNumChans(UNKWORD);
extern UNKTYPE GXSetNumTexGens(UNKWORD);
extern UNKTYPE GXSetNumIndStages(UNKWORD);
extern UNKTYPE GXSetNumTevStages(UNKWORD);

extern UNKTYPE GXSetTevDirect(UNKWORD);
extern UNKTYPE GXSetTevSwapMode(UNKWORD, UNKWORD, UNKWORD);
extern UNKTYPE GXSetTevOrder(UNKWORD, UNKWORD, UNKWORD, UNKWORD);
extern UNKTYPE GXSetBlendMode(UNKWORD, UNKWORD, UNKWORD, UNKWORD);
extern UNKTYPE GXSetTexCoordGen2(UNKWORD, UNKWORD, UNKWORD, UNKWORD, UNKWORD, UNKWORD);
extern UNKTYPE GXSetTevColor(UNKWORD, GXColor);
extern UNKTYPE GXSetTevColorIn(UNKWORD, UNKWORD, UNKWORD, UNKWORD, UNKWORD);
extern UNKTYPE GXSetTevAlphaIn(UNKWORD, UNKWORD, UNKWORD, UNKWORD, UNKWORD);
extern UNKTYPE GXSetTevColorOp(UNKWORD, UNKWORD, UNKWORD, UNKWORD, UNKWORD, UNKWORD);
extern UNKTYPE GXSetTevAlphaOp(UNKWORD, UNKWORD, UNKWORD, UNKWORD, UNKWORD, UNKWORD);
extern UNKTYPE GXSetVtxAttrFmt(UNKWORD, UNKWORD, UNKWORD, UNKWORD, UNKWORD);
extern UNKTYPE GXClearVtxDesc(UNKTYPE);
extern UNKTYPE GXSetVtxDesc(UNKWORD, UNKWORD);
extern UNKTYPE GXSetTevOp(UNKWORD, UNKWORD);

#ifdef __cplusplus
}
#endif
#endif