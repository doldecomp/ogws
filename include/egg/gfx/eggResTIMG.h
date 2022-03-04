#ifndef EGG_GFX_RES_TIMG_H
#define EGG_GFX_RES_TIMG_H
#include "types_egg.h"

namespace EGG
{
    struct ResTIMG
    {
        u8 mTexFormat; // at 0x0
        u16 mWidth; // at 0x2
        u16 mHeight; // at 0x4
        u8 mWrapS; // at 0x6
        u8 mWrapT; // at 0x7
        char UNK_0x8[0x10 - 0x8];
        bool mMipmap; // at 0x10
        u8 mEdgeLodEnable; // at 0x11
        u8 mBiasClampEnable; // at 0x12
        u8 mAnisotropy; // at 0x13
        u8 mMinFilt; // at 0x14
        u8 mMagFilt; // at 0x15
        s8 mMinLod; // at 0x16
        s8 mMaxLod; // at 0x17
        char UNK_0x18[0x1A - 0x18];
        s16 mLodBias; // at 0x1A
        UNKWORD mImageOfs; // at 0x1C
    };
}

#endif