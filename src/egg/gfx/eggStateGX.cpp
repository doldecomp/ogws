#include "eggStateGX.h"
#include "eggAssert.h"
#include "g3d_init.h"
#include "g3d_tmem.h"
#include <revolution/GX/GXAttr.h>
#include <revolution/GX/GXBump.h>
#include <revolution/GX/GXGeometry.h>
#include <revolution/GX/GXLight.h>
#include <revolution/GX/GXPixel.h>
#include <revolution/GX/GXTexture.h>
#include <revolution/GX/GXTransform.h>
#include <revolution/MTX.h>

namespace EGG
{
    using namespace nw4r::g3d;

    const GXColor StateGX::cDefaultGXColor = {255, 255, 255, 255};

    StateGX::CachedState StateGX::sCache;

    const f32 StateGX::lbl_80378C68[] = {
        0.5f, 0.0f, 0.0f, 0.0f, 0.5f, 0.0f,
    };
    const f32 StateGX::lbl_80378C80[] = {
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f
    };

    u16 StateGX::s_widthFb;
    u16 StateGX::s_heightEfb;
    GXPixelFmt StateGX::s_pixFormat;
    UNKWORD StateGX::sDefaultPixelFormatArg2;
    GXPixelFmt StateGX::s_pixFormatCurrent;
    UNKWORD StateGX::sCurrentPixelFormatArg2;
    GXColor StateGX::sDefaultTexColor;
    u8 StateGX::sDefaultTexObjImage[4 * 4];

    u16 StateGX::sStateFlags = VALID_CACHE;
    f32 StateGX::sModifyRatio = 1.0f;
    tmem::TMemLayout StateGX::sTMemLayout = tmem::TMEM_LAYOUT_1;
}

namespace EGG
{
    using namespace nw4r::g3d;

    void StateGX::initialize()
    {
        sStateFlags &= ~VALID_CACHE;

        GXInvalidateTexAll();
        frameInit();
        doResetStateCache();

        sTMemLayout = tmem::TMEM_LAYOUT_1;
        tmem::SetTMemLayout(tmem::TMEM_LAYOUT_1);
    }

    void StateGX::frameInit()
    {
        GXSetPixelFmt_(s_pixFormat, sDefaultPixelFormatArg2);
        GXInvalidateVtxCache();
        GXSetCurrentMtx(0);
        GXSetCoPlanar(0);
        GXSetClipMode(0);

        resetGX();
        G3dReset();

        if (sStateFlags & USE_TMEM) tmem::SetTMemLayout(sTMemLayout);
    }

    void StateGX::doResetStateCache()
    {
        resetStateCache();
    }

    void StateGX::resetGX()
    {
        resetVtx();
        resetIndirect();
        resetColorChannel();
        resetTexture();
        resetTexGen();
        resetTev();
        resetPE();
    }

    void StateGX::resetVtx()
    {
        GXSetVtxAttrFmt(0, GX_ATTR_VTX, 1, 4, 0);
        GXSetVtxAttrFmt(0, GX_ATTR_VTX_NRM, 0, 4, 0);
        GXSetVtxAttrFmt(0, GX_ATTR_VTX_CLR, 1, 5, 0);
        GXSetVtxAttrFmt(0, GX_ATTR_VTX_COUNT, 1, 5, 0);
        GXSetVtxAttrFmt(0, GX_ATTR_VTX_TEX_COORD, 1, 3, 7);
        GXSetVtxAttrFmt(0, GX_ATTR_14, 1, 3, 7);
        GXSetVtxAttrFmt(0, GX_ATTR_15, 1, 3, 7);
        GXSetVtxAttrFmt(0, GX_ATTR_16, 1, 3, 7);
        GXSetVtxAttrFmt(0, GX_ATTR_17, 1, 3, 7);
        GXSetVtxAttrFmt(0, GX_ATTR_18, 1, 3, 7);
        GXSetVtxAttrFmt(0, GX_ATTR_19, 1, 3, 7);
        GXSetVtxAttrFmt(0, GX_ATTR_20, 1, 3, 7);
    }

    void StateGX::resetColorChannel()
    {
        GXSetNumChans(1);

        GXSetChanAmbColor(GX_CHANNEL_ID_4, cDefaultGXColor);
        GXSetChanAmbColor(GX_CHANNEL_ID_5, cDefaultGXColor);
        GXSetChanMatColor(GX_CHANNEL_ID_4, cDefaultGXColor);
        GXSetChanMatColor(GX_CHANNEL_ID_5, cDefaultGXColor);

        GXSetCullMode(2);
        GXSetChanCtrl(GX_CHANNEL_ID_4, 0, 0, 0, 0, 2, 2);
        GXSetChanCtrl(GX_CHANNEL_ID_5, 0, 0, 0, 0, 2, 2);
    }

    void StateGX::resetIndirect()
    {
        GXSetNumIndStages(0);

        for (u32 i = 0; i < 3; i++)
        {
            GXSetIndTexMtx((GXIndTexMtxID)(i + 1), lbl_80378C68, 1);
        }

        for (u32 i = 0; i < 4; i++)
        {
            GXSetIndTexCoordScale((GXIndTexStageID)i,
                GX_IND_TEX_SCALE_0, GX_IND_TEX_SCALE_0);
        }
    }

    void StateGX::resetTexture()
    {
        GXTexObj gxTex;
        GXInitTexObj(&gxTex, sDefaultTexObjImage, 4, 4, 3, 0, 0, 0);

        GXLoadTexObj(&gxTex, GX_TEX_MAP_ID_0);
        GXLoadTexObj(&gxTex, GX_TEX_MAP_ID_1);
        GXLoadTexObj(&gxTex, GX_TEX_MAP_ID_2);
        GXLoadTexObj(&gxTex, GX_TEX_MAP_ID_3);
        GXLoadTexObj(&gxTex, GX_TEX_MAP_ID_4);
        GXLoadTexObj(&gxTex, GX_TEX_MAP_ID_5);
        GXLoadTexObj(&gxTex, GX_TEX_MAP_ID_6);
        GXLoadTexObj(&gxTex, GX_TEX_MAP_ID_7);
    }

    void StateGX::resetTexGen()
    {
        Mtx ident;
        PSMTXIdentity(ident);

        GXSetNumTexGens(1);

        for (u32 i = 0; i < 10; i++)
        {
            GXLoadTexMtxImm(ident, 30 + 3 * i, 0);
        }

        for (u32 i = 0; i < 8; i++)
        {
            GXSetTexCoordGen2((GXTexCoordID)i, GX_TEX_GEN_TYPE_1,
                GX_TEX_GEN_SRC_4, 0x3C, 0, 0x7D);

            GXSetTexCoordScaleManually(i, 0, 0, 0);
            GXSetTexCoordCylWrap(i, 0, 0);
        }
    }

    void StateGX::resetTev()
    {
        GXSetNumTevStages(1);

        for (u32 i = 0; i < 16; i++)
        {
            GXSetTevDirect(i);
            GXSetTevColorIn((GXTevStageID)i, 10, 15, 15, 15);
            GXSetTevColorOp((GXTevStageID)i, 0, 0, 0, 1, 0);
            GXSetTevAlphaIn((GXTevStageID)i, 5, 7, 7, 7);
            GXSetTevAlphaOp((GXTevStageID)i, 0, 0, 0, 1, 0);
            GXSetTevOrder((GXTevStageID)i, GX_TEX_COORD_ID_INVALID,
                GX_TEX_MAP_ID_INVALID, 0xFF);
            GXSetTevSwapMode((GXTevStageID)i, 0, 0);
        }

        for (u32 i = 0; i < 4; i++)
        {
            GXSetTevKColor((GXTevRegID)i, cDefaultGXColor);
        }

        for (u32 i = 0; i < 4; i++)
        {
            GXSetTevColor((GXTevRegID)i, cDefaultGXColor);
        }

        GXSetTevSwapModeTable(GX_TEV_SWAP_SEL_0, 0, 1, 2, 3);
        GXSetTevSwapModeTable(GX_TEV_SWAP_SEL_1, 0, 0, 0, 3);
        GXSetTevSwapModeTable(GX_TEV_SWAP_SEL_2, 1, 1, 1, 3);
        GXSetTevSwapModeTable(GX_TEV_SWAP_SEL_3, 2, 2, 2, 3);
    }

    void StateGX::resetPE()
    {
        GXSetBlendMode(1, 4, 5, 5);
        GXSetAlphaCompare(7, 0, 0, 7, 0);
        GXSetZMode(1, 3, 1);

        GXSetFog(GX_FOG_TYPE_0, cDefaultGXColor, 0.0f, 1.0f, 0.1f, 1.0f);
        GXSetFogRangeAdj(0, 0, NULL);
        GXSetZCompLoc(1);
        GXSetDstAlpha(0, 0);
    }

    void StateGX::resetStateCache()
    {
        sCache.flags = 0;
        StateGX::GXSetColorUpdate_(true);
        StateGX::GXSetAlphaUpdate_(true);
        StateGX::GXSetDither_(true);
    }

    // Fake match: Figure out what is actually happening here
    void StateGX::GXSetProjection_(Mtx44 mtx, int type)
    {
        f32 pj[12];

        switch(type)
        {
            case 0:
                __memclr(&pj[7], 7 * 0x4);
                pj[8] = mtx[0][0];
                pj[9] = mtx[0][2];
                pj[10] = mtx[1][1];
                pj[11] = mtx[1][2];
                pj[12] = mtx[2][2];
                pj[13] = mtx[2][3];
                GXSetProjectionv_(&pj[7]);
                break;
            case 1:
                __memcpy(&pj[0], lbl_80378C80, 7 * 0x4);
                pj[1] = mtx[0][0];
                pj[2] = mtx[0][3];
                pj[3] = mtx[1][1];
                pj[4] = mtx[1][3];
                pj[5] = mtx[2][2];
                pj[6] = mtx[2][3];
                GXSetProjectionv_(&pj[0]);
                break;
            default:
                #line 288
                EGG_ASSERT(0);
        }
    }

    void StateGX::GXSetProjectionv_(const f32 *proj)
    {
        f32 old_pj[6];
        GXGetProjectionv(old_pj);

        if (sCache.flags & PROJECTIONV_CACHED)
        {
            if (proj[0] == old_pj[0] && proj[1] == old_pj[1]
                && proj[2] == old_pj[2] && proj[3] == old_pj[3]
                && proj[4] == old_pj[4] && proj[5] == old_pj[5]
                && proj[6] == old_pj[6]) return;
        }

        GXSetProjectionv(proj);

        if (sStateFlags & VALID_CACHE) sCache.flags |= PROJECTIONV_CACHED;
    }

    void StateGX::GXSetViewport_(f32 x1, f32 y1, f32 w, f32 h, f32 f5, f32 f6)
    {
        f32 old_vp[5];
        GXGetViewportv(old_vp);

        if (sCache.flags & VIEWPORT_CACHED)
        {
            if (x1 == old_vp[0] && y1 == old_vp[1]
                && w == old_vp[2] && h == old_vp[3]
                && f5 == old_vp[4] && f6 == old_vp[5]) return;
        }

        GXSetViewport(x1, y1, w, h, f5, f6);

        if (sStateFlags & VALID_CACHE) sCache.flags |= VIEWPORT_CACHED;
    }

    void StateGX::GXSetScissor_(u32 s0, u32 s1, u32 s2, u32 s3)
    {
        #line 385
        EGG_ASSERT(s0 < 2048);
        EGG_ASSERT(s1 < 2048);
        EGG_ASSERT(s2 < 2048);
        EGG_ASSERT(s3 < 2048);

        u32 old_s3, old_s2, old_s1, old_s0;
        GXGetScissor(&old_s0, &old_s1, &old_s2, &old_s3);

        if (sCache.flags & SCISSOR_CACHED)
        {
            if (s0 == old_s0 && s1 == old_s1
                && s2 == old_s2 && s3 == old_s3) return;
        }

        GXSetScissor(s0, s1, s2, s3);

        if (sStateFlags & VALID_CACHE) sCache.flags |= SCISSOR_CACHED;
    }

    void StateGX::GXSetScissorBoxOffset_(int b0, int b1)
    {
        #line 422
        EGG_ASSERT(b0 % 2 == 0);
        EGG_ASSERT(b1 % 2 == 0);

        if (sCache.flags & SCISSOR_BOX_CACHED)
        {
            if (b0 == sCache.scissorOfsX
                && b1 == sCache.scissorOfsY) return;
        }

        GXSetScissorBoxOffset(b0, b1);
        sCache.scissorOfsX = b0;
        sCache.scissorOfsY = b1;

        if (sStateFlags & VALID_CACHE) sCache.flags |= SCISSOR_BOX_CACHED;
    }

    void StateGX::GXSetColorUpdate_(bool enable)
    {
        if (sCache.flags & COLOR_UPDATE_CACHED)
        {
            if (enable == sCache.colorUpdate) return;
        }

        GXSetColorUpdate(enable);
        sCache.colorUpdate = enable;

        if (sStateFlags & VALID_CACHE) sCache.flags |= COLOR_UPDATE_CACHED;
    }

    void StateGX::GXSetAlphaUpdate_(bool enable)
    {
        if (sCache.flags & ALPHA_UPDATE_CACHED)
        {
            if (enable == sCache.alphaUpdate) return;
        }

        GXSetAlphaUpdate(enable);
        sCache.alphaUpdate = enable;

        if (sStateFlags & VALID_CACHE) sCache.flags |= ALPHA_UPDATE_CACHED;
    }

    void StateGX::GXSetDither_(bool enable)
    {
        if (sCache.flags & DITHER_CACHED)
        {
            if (enable == sCache.dither) return;
        }

        GXSetDither(enable);
        sCache.dither = enable;

        if (sStateFlags & VALID_CACHE) sCache.flags |= DITHER_CACHED;
    }

    void StateGX::GXSetPixelFmt_(GXPixelFmt fmt, UNKWORD arg2)
    {
        // New setting only required if cache exists
        if (sStateFlags & VALID_CACHE
            && (s_pixFormatCurrent != fmt || sCurrentPixelFormatArg2 != arg2)
            || ((sStateFlags & VALID_CACHE) == 0))
        {
            GXSetPixelFmt(fmt, arg2);
            GXSetColorUpdate(sCache.colorUpdate);
            GXSetAlphaUpdate(sCache.alphaUpdate);
        }

        s_pixFormatCurrent = fmt;
        sCurrentPixelFormatArg2 = arg2;
    }
}