#pragma ipa file

#include "lyt_texMap.h"

namespace nw4r
{
    namespace lyt
    {
        using namespace detail;

        void TexMap::Get(GXTexObj *pTexObj) const
        {
            if (IsCITexelFormat(GetTexelFormat()))
            {
                u32 tlut = GXGetTexObjTlut(pTexObj);
                GXInitTexObjCI(pTexObj, GetImage(), GetWidth(), GetHeight(),
                    GetTexelFormat(), GetWrapModeS(), GetWrapModeT(), IsMipMap(), tlut);
            }
            else
            {
                GXInitTexObj(pTexObj, GetImage(), GetWidth(), GetHeight(),
                    GetTexelFormat(), GetWrapModeS(), GetWrapModeT(), IsMipMap());
            }

            GXInitTexObjLOD(pTexObj, GetMinFilter(), GetMagFilter(), GetMinLOD(),
                GetMaxLOD(), GetLODBias(), IsBiasClampEnable(), IsEdgeLODEnable(), GetAnisotropy());
        }

        void TexMap::Get(GXTlutObj *pTLUTObj) const
        {
            GXInitTlutObj(pTLUTObj, GetPalette(), GetPaletteFormat(), GetPaletteEntryNum());
        }

        void TexMap::Set(TPLPalette *pPalette, u32 tplID)
        {
            // Is this pointer validation?
            if (pPalette->WORD_0x8 < 0x80000000)
            {
                TPLBind(pPalette);
            }

            Set(TPLGet(pPalette, tplID));
        }

        // Inlined
        void TexMap::Set(const TPLDescriptor *pDescriptor)
        {
            SetNoWrap(pDescriptor);
            SetWrapMode(pDescriptor->PTR_0x0->mWrapModeS, pDescriptor->PTR_0x0->mWrapModeT);
        }

        void TexMap::SetNoWrap(const TexMap& map)
        {
            GXTexWrapMode wrapS = GetWrapModeS();
            GXTexWrapMode wrapT = GetWrapModeT();

            Set(map);
            SetWrapMode(wrapS, wrapT);
        }

        void TexMap::SetNoWrap(const TPLDescriptor *pDescriptor)
        {
            TPLDescriptorUnk0 *unk0 = pDescriptor->PTR_0x0;
            SetImage(unk0->mImage);
            SetSize(unk0->mWidth, unk0->mHeight);
            SetTexelFormat(unk0->mTexFmt);

            bool bMipMap = (unk0->mMinLOD != unk0->mMaxLOD);
            SetMipMap(bMipMap);

            SetFilter(unk0->mMinFilter, unk0->mMagFilter);
            SetLOD(unk0->mMinLOD, unk0->mMaxLOD);
            SetLODBias(unk0->mLODBias);
            SetEdgeLODEnable(unk0->mEdgeLODEnable);

            TPLDescriptorUnk1 *unk1 = pDescriptor->PTR_0x4;
            if (unk1 != NULL)
            {
                SetPalette(unk1->mPalette);
                SetPaletteFormat(unk1->mPaletteFmt);
                SetPaletteEntryNum(unk1->mPalEntryNum);
            }
            else
            {
                SetPalette(NULL);
                SetPaletteFormat(GX_TL_IA8);
                SetPaletteEntryNum(0);
            }
        }
    }
}