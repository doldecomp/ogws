#ifndef REVOSDK_TPL_H
#define REVOSDK_TPL_H
#ifdef __cplusplus
#include <types.h>
#include <GX/GXTexture.h>
extern "C" {
#endif

typedef struct
{
    u32 mVersion; // 00 20 AF 30
    UNKWORD WORD_0x4;
    UNKWORD WORD_0x8;
} TPLPalette;

typedef struct
{
    u16 mHeight; // at 0x0
    u16 mWidth; // at 0x2
    GXTexFmt mTexFmt; // at 0x4
    UNKTYPE *mImage; // at 0x8
    GXTexWrapMode mWrapModeS; // at 0xC
    GXTexWrapMode mWrapModeT; // at 0x10
    GXTexFilter mMinFilter; // at 0x14
    GXTexFilter mMagFilter; // at 0x18
    f32 mLODBias; // at 0x1C
    u8 mEdgeLODEnable; // at 0x20
    u8 mMinLOD; // at 0x21
    u8 mMaxLOD; // at 0x22
} TPLDescriptorUnk0;

typedef struct
{
    u16 mPalEntryNum; // at 0x0
    char UNK_0x2[0x2];
    GXTlutFmt mPaletteFmt; // at 0x4
    UNKTYPE *mPalette; // at 0x8
} TPLDescriptorUnk1;

typedef struct
{
    TPLDescriptorUnk0 *PTR_0x0;
    TPLDescriptorUnk1 *PTR_0x4;
} TPLDescriptor;

UNKTYPE TPLBind(TPLPalette *);
TPLDescriptor * TPLGet(TPLPalette *, u32 id);

#ifdef __cplusplus
}
#endif
#endif