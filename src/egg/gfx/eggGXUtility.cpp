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

    const u8 GXUtility::sTexMtxIDs[] = {0x1E, 0x21, 0x24, 0x27, 0x2A, 0x2D, 0x30, 0x33};
    Screen *IDrawGX::spScreen;
    GXUtility::ProjectionCallback GXUtility::sProjectionCallback;
    UNKWORD GXUtility::sProjectionCallbackArg;
    u16 GXUtility::lbl_804BEC7C;
    u32 GXUtility::sDrawSettings;
    math::MTX34 GXUtility::sCameraMtx;

    u8 GXUtility::getTexMtxID(int no)
    {
        #line 22
        EGG_ASSERT(0 <= no && no < 8);

        return sTexMtxIDs[no];
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

        u32 imageOfs = (tex.mImageOfs != 0) ? tex.mImageOfs : sizeof(tex);
        BOOL bMipmap = (tex.mMipmap) ? TRUE : FALSE;

        GXInitTexObj(pObj, (char *)&tex + imageOfs, tex.mWidth, tex.mHeight,
            (GXTexFmt)tex.mTexFormat, (GXTexWrapMode)tex.mWrapS, (GXTexWrapMode)tex.mWrapT, bMipmap);

        GXInitTexObjLOD(pObj, (GXTexFilter)tex.mMinFilt, (GXTexFilter)tex.mMagFilt,
            tex.mMinLod / 8.0f, tex.mMaxLod / 8.0f, tex.mLodBias / 100.0f,
            tex.mBiasClampEnable, tex.mEdgeLodEnable, (GXAnisotropy)tex.mAnisotropy);
    }

    void GXUtility::getTexObj(GXTexObj *pObj, nw4r::g3d::ResTex tex,
        GXTexWrapMode wrapS, GXTexWrapMode wrapT, GXTexFilter minFilt, GXTexFilter magFilt)
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
            GXInitTexObjLOD(pObj, minFilt, magFilt, minLod, maxLod, 0.0f, 0, 0, GX_ANISO_1);
        }
    }

    void GXUtility::set(u16 s, const nw4r::math::MTX34& mtx, Screen& screen)
    {
        lbl_804BEC7C = s;
        setScreen(screen);
        PSMTXCopy(mtx, sCameraMtx);
    }

    void GXUtility::setScreenProjection(bool b)
    {
        StateGX::GXSetColorUpdate_(sDrawSettings & ENABLE_COLOR_UPDATE);
        StateGX::GXSetAlphaUpdate_(sDrawSettings & ENABLE_ALPHA_UPDATE);
        StateGX::GXSetDither_(sDrawSettings & ENABLE_DITHER);

        if (sProjectionCallback != NULL)
            sProjectionCallback(sProjectionCallbackArg, b);

        GXUtility::getScreen().SetProjectionGX();
    }
}