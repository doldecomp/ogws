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
	GX_TEX_MAP_ID_1,
	GX_TEX_MAP_ID_2,
	GX_TEX_MAP_ID_3,
	GX_TEX_MAP_ID_4,
	GX_TEX_MAP_ID_5,
	GX_TEX_MAP_ID_6,
	GX_TEX_MAP_ID_7,
	
	GX_TEX_MAP_ID_INVALID = 0xFF
} GXTexMapID;

typedef enum _GXTexFmt
{
	GX_TEX_FMT_0,
	GX_TEX_FMT_1,
	GX_TEX_FMT_2,
	GX_TEX_FMT_3,
	GX_TEX_FMT_4,
	GX_TEX_FMT_5,
	GX_TEX_FMT_6,
	GX_TEX_FMT_7,

	// CI formats
	GX_TEX_FMT_8,
	GX_TEX_FMT_9,
	GX_TEX_FMT_10,

	GX_TEX_FMT_11,
	GX_TEX_FMT_12,
	GX_TEX_FMT_13,
	GX_TEX_FMT_14,
	GX_TEX_FMT_15,
	GX_TEX_FMT_16,
	GX_TEX_FMT_17,
	GX_TEX_FMT_18,
	GX_TEX_FMT_19,
	GX_TEX_FMT_20,
	GX_TEX_FMT_21,
	GX_TEX_FMT_22
} GXTexFmt;

typedef enum _GXTlutFmt
{
	GX_TLUT_FORMAT_0
} GXTlutFmt;

typedef enum _GXTexFilter
{
	GX_LINEAR = 1,
	GX_LIN_MIP_LIN = 5
} GXTexFilter;

typedef enum _GXAnisotropy
{

} GXAnisotropy;

typedef enum _GXTexWrapMode
{
	GX_TEXWRAPMODE_0,
	GX_TEXWRAPMODE_1,
	GX_TEXWRAPMODE_2,
	GX_MAX_TEXWRAPMODE
} GXTexWrapMode;

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

typedef struct _GXTlutObj
{

} GXTlutObj;

typedef struct _GXTexObj
{
	UNKWORD mFlags; // at 0x0
	char UNK_0x4[0x4];
	UNKWORD mDimensions; // at 0x8 (Height/width are split between these bits)
	char UNK_0xC[0x4];
	UNKWORD mUserData; // at 0x10
	GXTexFmt mFormat; // at 0x14
	UNKWORD mTLUT; // at 0x18
} GXTexObj;

UNKWORD GXGetTexBufferSize(UNKWORD width, UNKWORD height, GXTexFmt format, UNKWORD, UNKWORD);

UNKTYPE GXInitTexObj(GXTexObj *, UNKTYPE *image, u16 width, UNKWORD height, UNKWORD texFormat, UNKWORD wrapModeS, UNKWORD wrapModeT, BOOL mipmap);
UNKTYPE GXInitTexObjCI(GXTexObj *, UNKTYPE *, UNKWORD width, UNKWORD height, UNKWORD texFormat, UNKWORD wrapModeS, UNKWORD wrapModeT, BOOL mipmap, UNKWORD tlut);
UNKTYPE GXInitTexObjLOD(GXTexObj *, int min_filt, int mag_filt, UNKWORD biasClampEnable, UNKWORD edgeLodEnable, UNKWORD anisotropy, f32 minLod, f32 maxLod, f32 lodBias);
UNKTYPE GXLoadTexObj(GXTexObj *, GXTexMapID texMapID);
UNKWORD GXGetTexObjTlut(GXTexObj *);
UNKTYPE GXInitTlutObj(GXTlutObj *, UNKTYPE *palette, UNKWORD paletteFmt, UNKWORD paletteEntryNum);

UNKTYPE GXInvalidateTexAll();

UNKTYPE GXSetTexCoordScaleManually(UNKWORD, UNKWORD, UNKWORD, UNKWORD);
UNKTYPE GXSetTexCoordCylWrap(UNKWORD, UNKWORD, UNKWORD);

#ifdef __cplusplus
}
#endif
#endif