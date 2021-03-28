#ifndef REVOSDK_GX_ATTR_H
#define REVOSDK_GX_ATTR_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

enum _GXAttr
{
	GX_ATTR_0,
	GX_ATTR_1,
	GX_ATTR_2,
	GX_ATTR_3,
	GX_ATTR_4,
	GX_ATTR_5,
	GX_ATTR_6,
	GX_ATTR_7,
	GX_ATTR_8,
	
	GX_ATTR_VTX,
	
	GX_ATTR_VTX_POS = GX_ATTR_VTX,
	GX_ATTR_VTX_NRM,
	
	GX_ATTR_VTX_CLR,
	GX_ATTR_VTX_CLR_COUNT = 2,
	
	GX_ATTR_VTX_TEX_COORD = GX_ATTR_VTX_CLR + GX_ATTR_VTX_CLR_COUNT,
	GX_ATTR_VTX_TEX_COORD_COUNT = 8,
	
	GX_ATTR_COUNT = GX_ATTR_VTX_TEX_COORD + GX_ATTR_VTX_TEX_COORD_COUNT,
	GX_ATTR_VTX_COUNT = GX_ATTR_COUNT - GX_ATTR_VTX,
	
	GX_ATTR_INVALID = 0xFF
};

typedef struct _GXVtxDescList
{
	enum _GXAttr mAttr; // at 0x0
	UNKWORD WORD_0x4;
} GXVtxDescList[];

typedef struct _GXVtxAttrFmtList
{
	enum _GXAttr mAttr; // at 0x0
	UNKWORD WORD_0x4;
	UNKWORD WORD_0x8;
	char BYTE_0xC;
} GXVtxAttrFmtList[];

UNKTYPE GXSetArray(enum _GXAttr, const void *, u8);

#ifdef __cplusplus
}
#endif
#endif