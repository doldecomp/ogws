#ifndef REVOSDK_GX_ATTR_H
#define REVOSDK_GX_ATTR_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

enum _GXAttr
{
	GX_ATTR_POS,
	GX_ATTR_NRM,
	
	GX_ATTR_CLR,
	GX_ATTR_CLR_COUNT = 2,
	
	GX_ATTR_TEX_COORD = GX_ATTR_CLR + GX_ATTR_CLR_COUNT,
	GX_ATTR_TEX_COORD_COUNT = 8,
	
	GX_ATTR_COUNT = GX_ATTR_TEX_COORD + GX_ATTR_TEX_COORD_COUNT
};

typedef struct _GXVtxDescList
{
	UNKWORD WORD_0x0;
	UNKWORD WORD_0x4;
} GXVtxDescList[];

typedef struct _GXVtxAttrFmtList
{
	UNKWORD WORD_0x0;
	UNKWORD WORD_0x4;
	UNKWORD WORD_0x8;
	char BYTE_0xC;
} GXVtxAttrFmtList[];

#ifdef __cplusplus
}
#endif
#endif