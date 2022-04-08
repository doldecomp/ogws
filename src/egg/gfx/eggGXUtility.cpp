#include "eggGXUtility.h"
#include "eggAssert.h"
#include "eggResTIMG.h"
#include "eggMatrix.h"
#include "eggStateGX.h"
#include "eggScreen.h"
#include "ut_algorithm.h"
#include "g3d_restex.h"

namespace EGG
{
    using namespace nw4r;

    const u8 GXUtility::sTexCoordGenVals[] = {0x1E, 0x21, 0x24, 0x27, 0x2A, 0x2D, 0x30, 0x33};
    eggScreen *IDrawGX::spScreen;
    GXUtility::ProjectionCallback GXUtility::sProjectionCallback;
    UNKWORD GXUtility::sProjectionCallbackArg;
    u16 GXUtility::lbl_804BEC7C;
    u32 GXUtility::sDrawSettings;
    Matrix34f GXUtility::sCameraMtx;

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
        EGG_ASSERT(sx != 0.f);
        EGG_ASSERT(sy != 0.f);

        p[1] *= (1.0f / sx);
        p[3] *= (1.0f / sy);
        p[2] += ox;
        p[4] += oy;
    }

    namespace
    {
        void UNUSED_ASSERTS_GXUTILITY()
        {
            EGG_ASSERT_MSG(false, "Not implemented.");
        }
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

    void GXUtility::set(u16 s, Matrix34f& out, eggScreen& screen)
    {
        lbl_804BEC7C = s;
        setScreen(screen);
        PSMTXCopy(out, sCameraMtx);
    }

    void GXUtility::setScreenProjection(bool b)
    {
        StateGX::GXSetColorUpdate(sDrawSettings & ENABLE_COLOR_UPDATE);
        StateGX::GXSetAlphaUpdate(sDrawSettings & ENABLE_ALPHA_UPDATE);
        StateGX::GXSetDither(sDrawSettings & ENABLE_DITHER);

        if (sProjectionCallback != NULL)
            sProjectionCallback(sProjectionCallbackArg, b);

        GXUtility::getScreen().SetProjectionGX();
    }
}