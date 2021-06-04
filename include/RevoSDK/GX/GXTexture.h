#ifndef REVOSDK_GX_TEXTURE_H
#define REVOSDK_GX_TEXTURE_H
#include <types.h>
#include <GX.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef enum _GXTexMapID
{
	GX_TEX_MAP_ID_0,
	GX_TEX_MAP_ID_INVALID = 0xFF
} GXTexMapID;

typedef enum _GXTexFmt
{
	GX_TEX_FMT_0
} GXTexFmt;

typedef enum _GXCITexFmt
{

} GXCITexFmt;

typedef enum _GXTexCoordID
{
	GX_TEX_COORD_ID_0,
	GX_TEX_COORD_ID_COUNT = 8,
	GX_TEX_COORD_ID_INVALID = 0xFF
} GXTexCoordID;

typedef enum _GXTexGenType
{
	GX_TEX_GEN_TYPE_0,
	GX_TEX_GEN_TYPE_1,
} GXTexGenType;

typedef enum _GXTexGenSrc
{
	GX_TEX_GEN_SRC_0,
	GX_TEX_GEN_SRC_1,
	GX_TEX_GEN_SRC_2,
	GX_TEX_GEN_SRC_3,
	GX_TEX_GEN_SRC_4,
} GXTexGenSrc;

typedef struct _GXTexObj
{
	UNKWORD mFlags; // at 0x0
	char UNK_0x4[0x4];
	UNKWORD mDimensions; // at 0x8 (Height/width are split between these bits)
	char UNK_0xC[0x4];
	UNKWORD mUserData; // at 0x10
	GXTexFmt mFormat; // at 0x14
	char UNK_0x18[0x4 + 0x3];
	u8 mMipMap; // at 0x1F
} GXTexObj;

UNKTYPE GXInitTexObj(GXTexObj *, u8 *, UNKWORD width, UNKWORD height, UNKWORD texFormat, UNKWORD, UNKWORD, UNKWORD);
UNKTYPE GXInitTexObjLOD(GXTexObj *, int min_filt, int mag_filt, UNKWORD, UNKWORD, UNKWORD, float, float, float);
UNKTYPE GXLoadTexObj(GXTexObj *, GXTexMapID texMapID);

#ifdef __cplusplus
}
#endif
#endif