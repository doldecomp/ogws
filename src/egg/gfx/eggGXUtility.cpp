#include "eggGXUtility.h"
#include "eggAssert.h"
#include "eggResTIMG.h"
#include "ut_algorithm.h"
#include "g3d_restex.h"

namespace EGG
{
    using namespace nw4r;

    eggScreen *IDrawGX::spScreen;

    u8 GXUtility::getTexCoordGenVal(int no)
    {
        #line 22
        EGG_ASSERT(0 <= no && no < 8);

        return sTexCoordGenVals[no];
    }

    void GXUtility::setScaleOffsetPerspective(f32 *p, f32 sx, f32 sy, f32 ox, f32 oy)
    {
        #line 38
        EGG_ASSERT(p != NULL);
        EGG_ASSERT(sx != 0.0f);
        EGG_ASSERT(sy != 0.0f);

        p[1] *= (1.0f / sx);
        p[3] *= (1.0f / sy);
        p[2] += ox;
        p[4] += oy;
    }

    void GXUtility::getTexObj(GXTexObj *pObj, const ResTIMG& tex)
    {
        #line 70
        EGG_ASSERT(pObj);

        u32 imageOfs = (tex.mImageOfs != 0) ? tex.mImageOfs : 32;
        BOOL bMipmap = (tex.mMipmap) ? TRUE : FALSE;

        GXInitTexObj(pObj, (char *)&tex + imageOfs, tex.mWidth, tex.mHeight,
            tex.mTexFormat, tex.mWrapS, tex.mWrapT, bMipmap);

        GXInitTexObjLOD(pObj, tex.mMinFilt, tex.mMagFilt, tex.mBiasClampEnable, tex.mEdgeLodEnable,
            tex.mAnisotropy, tex.mMinLod / 8.0f, tex.mMaxLod / 8.0f, tex.mLodBias / 100.0f);
    }

    void GXUtility::getTexObj(GXTexObj *pObj, const nw4r::g3d::ResTex& tex,
        UNKWORD wrapS, UNKWORD wrapT, UNKWORD minFilt, UNKWORD magFilt)
    {
        #line 113
        EGG_ASSERT(pObj);
        EGG_ASSERT(tex.IsValid());

        void *image;
        u16 width, height;
        GXTexFmt fmt;
        f32 minLod, maxLod;
        u8 mipmap;

        if (tex.GetTexObjParam(&image, &width, &height, &fmt, &minLod, &maxLod, &mipmap))
        {
            GXInitTexObj(pObj, image, width, height, fmt, wrapS, wrapT, mipmap);
            GXInitTexObjLOD(pObj, minFilt, magFilt, 0, 0, 0, minLod, maxLod, 0.0f);
        }
    }

    #ifdef __DECOMP_NON_MATCHING
    void GXUtility::func_800a1b6c(u16 s, Mtx m, UNKTYPE *p)
    {

    }
    #endif

    #ifdef __DECOMP_NON_MATCHING
    void GXUtility::func_800a1b88(UNKTYPE *p)
    {

    }
    #endif
}