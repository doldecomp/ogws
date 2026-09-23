#include <egg/gfxe.h>
#include <egg/prim.h>

#include <nw4r/g3d.h>

#include <revolution/GX.h>
#include <revolution/MTX.h>

namespace {

const GXColor WHITE = {255, 255, 255, 255};

} // namespace

namespace EGG {

StateGX::GXCache StateGX::s_cacheGX;

u16 StateGX::s_widthFb = 0;
u16 StateGX::s_heightEfb = 0;

GXPixelFmt StateGX::s_pixFormat = GX_PF_RGB8_Z24;
GXZFmt16 StateGX::s_zFmt16 = GX_ZC_LINEAR;

GXPixelFmt StateGX::s_pixFormatCurrent = GX_PF_RGB8_Z24;
GXZFmt16 StateGX::s_zFmt16Current = GX_ZC_LINEAR;

GXColor StateGX::s_clearEfb = {0, 0, 0, 0};

u16 StateGX::s_flag = cFlag_EnableCache;

f32 StateGX::s_modifyRatio = 1.0f;

nw4r::g3d::tmem::TMemLayout StateGX::s_tmem_layout =
    nw4r::g3d::tmem::TMEM_LAYOUT_1;

void StateGX::initialize() {
    s_flag &= ~cFlag_EnableCache;

    GXInvalidateTexAll();
    frameInit();
    initGXCache();

    s_tmem_layout = nw4r::g3d::tmem::TMEM_LAYOUT_1;
    nw4r::g3d::tmem::SetTMemLayout(s_tmem_layout);
}

void StateGX::frameInit() {
    setPixelFormatGX(s_pixFormat, s_zFmt16);
    GXInvalidateVtxCache();
    GXSetCurrentMtx(GX_PNMTX0);
    GXSetCoPlanar(GX_FALSE);
    GXSetClipMode(GX_CLIP_ENABLE);

    resetGX();
    nw4r::g3d::G3dReset();

    if (s_flag & cFlag_EnableTMem) {
        nw4r::g3d::tmem::SetTMemLayout(s_tmem_layout);
    }
}

void StateGX::initGXCache() {
    resetGXCache();
}

void StateGX::resetGX() {
    resetVtx();
    resetIndirect();
    resetColorChannel();
    resetTexture();
    resetTexGen();
    resetTev();
    resetPE();
}

void StateGX::resetVtx() {
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR1, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_S16, 7);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX1, GX_TEX_ST, GX_S16, 7);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX2, GX_TEX_ST, GX_S16, 7);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX3, GX_TEX_ST, GX_S16, 7);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX4, GX_TEX_ST, GX_S16, 7);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX5, GX_TEX_ST, GX_S16, 7);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX6, GX_TEX_ST, GX_S16, 7);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX7, GX_TEX_ST, GX_S16, 7);
}

void StateGX::resetColorChannel() {
    GXSetNumChans(1);

    GXSetChanAmbColor(GX_COLOR0A0, WHITE);
    GXSetChanAmbColor(GX_COLOR1A1, WHITE);
    GXSetChanMatColor(GX_COLOR0A0, WHITE);
    GXSetChanMatColor(GX_COLOR1A1, WHITE);

    GXSetCullMode(GX_CULL_BACK);

    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL,
                  GX_DF_CLAMP, GX_AF_NONE);
    GXSetChanCtrl(GX_COLOR1A1, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL,
                  GX_DF_CLAMP, GX_AF_NONE);
}

void StateGX::resetIndirect() {
    GXSetNumIndStages(0);

    for (u32 i = 0; i < GX_ITM_NUM; i++) {
        static const f32 offsetMtx[2][3] = {
            {0.5f, 0.0f, 0.0f},
            {0.0f, 0.5f, 0.0f},
        };

        GXSetIndTexMtx(static_cast<GXIndTexMtxID>(i + GX_ITM_0), offsetMtx, 1);
    }

    for (u32 i = 0; i < GX_MAX_INDTEXSTAGE; i++) {
        GXSetIndTexCoordScale(static_cast<GXIndTexStageID>(i), //
                              GX_ITS_1, GX_ITS_1);
    }
}

void StateGX::resetTexture() {
    GXTexObj tobj;

    static u8 NullTexData[4 * 4] ALIGN(32) = {};
    GXInitTexObj(&tobj, NullTexData, 4, 4, GX_TF_IA8, GX_CLAMP, GX_CLAMP,
                 GX_FALSE);

    GXLoadTexObj(&tobj, GX_TEXMAP0);
    GXLoadTexObj(&tobj, GX_TEXMAP1);
    GXLoadTexObj(&tobj, GX_TEXMAP2);
    GXLoadTexObj(&tobj, GX_TEXMAP3);
    GXLoadTexObj(&tobj, GX_TEXMAP4);
    GXLoadTexObj(&tobj, GX_TEXMAP5);
    GXLoadTexObj(&tobj, GX_TEXMAP6);
    GXLoadTexObj(&tobj, GX_TEXMAP7);
}

void StateGX::resetTexGen() {
    nw4r::math::MTX34 m;
    nw4r::math::MTX34Identity(&m);

    GXSetNumTexGens(1);

    for (u32 i = 0; i < GX_TEXMTX_NUM; i++) {
        GXLoadTexMtxImm(m, GX_TEXMTX0 + i * 3, GX_MTX_3x4);
    }

    for (u32 i = 0; i < GX_MAX_TEXCOORD; i++) {
        GXSetTexCoordGen(static_cast<GXTexCoordID>(i), GX_TG_MTX2x4, GX_TG_TEX0,
                         GX_IDENTITY);

        GXSetTexCoordScaleManually(static_cast<GXTexCoordID>(i), //
                                   GX_FALSE, 0, 0);

        GXSetTexCoordCylWrap(static_cast<GXTexCoordID>(i), GX_FALSE, GX_FALSE);
    }
}

void StateGX::resetTev() {
    GXSetNumTevStages(1);

    for (u32 i = 0; i < GX_MAX_TEVSTAGE; i++) {
        GXSetTevDirect(static_cast<GXTevStageID>(i));

        GXSetTevColorIn(static_cast<GXTevStageID>(i), GX_CC_RASC, GX_CC_ZERO,
                        GX_CC_ZERO, GX_CC_ZERO);

        GXSetTevColorOp(static_cast<GXTevStageID>(i), GX_TEV_ADD, GX_TB_ZERO,
                        GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

        GXSetTevAlphaIn(static_cast<GXTevStageID>(i), GX_CA_RASA, GX_CA_ZERO,
                        GX_CA_ZERO, GX_CA_ZERO);

        GXSetTevAlphaOp(static_cast<GXTevStageID>(i), GX_TEV_ADD, GX_TB_ZERO,
                        GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

        GXSetTevOrder(static_cast<GXTevStageID>(i), GX_TEXCOORD_NULL,
                      GX_TEXMAP_NULL, GX_COLOR_NULL);

        GXSetTevSwapMode(static_cast<GXTevStageID>(i), GX_TEV_SWAP0,
                         GX_TEV_SWAP0);
    }

    for (u32 i = 0; i < GX_MAX_KCOLOR; i++) {
        GXSetTevKColor(static_cast<GXTevKColorID>(i), WHITE);
    }

    for (u32 i = 0; i < GX_MAX_TEVREG; i++) {
        GXSetTevColor(static_cast<GXTevRegID>(i), WHITE);
    }

    GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE,
                          GX_CH_ALPHA);

    GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_RED, GX_CH_RED,
                          GX_CH_ALPHA);

    GXSetTevSwapModeTable(GX_TEV_SWAP2, GX_CH_GREEN, GX_CH_GREEN, GX_CH_GREEN,
                          GX_CH_ALPHA);

    GXSetTevSwapModeTable(GX_TEV_SWAP3, GX_CH_BLUE, GX_CH_BLUE, GX_CH_BLUE,
                          GX_CH_ALPHA);
}

void StateGX::resetPE() {
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);

    GXSetFog(GX_FOG_NONE, WHITE, 0.0f, 1.0f, 0.1f, 1.0f);
    GXSetFogRangeAdj(GX_FALSE, 0, NULL);
    GXSetZCompLoc(GX_TRUE);
    GXSetDstAlpha(GX_FALSE, 0);
}

void StateGX::resetGXCache() {
    s_cacheGX.flags = 0;

    GXSetColorUpdate_(GX_TRUE);
    GXSetAlphaUpdate_(GX_TRUE);
    GXSetDither_(GX_TRUE);
}

void StateGX::GXSetProjection_(Mtx44 mtx, GXProjectionType type) {
    switch (type) {
    case GX_PERSPECTIVE: {
        // clang-format off
        f32 proj[GX_PROJECTION_SZ] = {
            static_cast<f32>(GX_PERSPECTIVE),
            0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        };
        // clang-format on

        proj[GX_PROJECTION_A] = mtx[0][0];
        proj[GX_PROJECTION_B] = mtx[0][2];
        proj[GX_PROJECTION_C] = mtx[1][1];
        proj[GX_PROJECTION_D] = mtx[1][2];
        proj[GX_PROJECTION_E] = mtx[2][2];
        proj[GX_PROJECTION_F] = mtx[2][3];

        GXSetProjectionv_(proj);
        break;
    }

    case GX_ORTHOGRAPHIC: {
        // clang-format off
        f32 proj[GX_PROJECTION_SZ] = {
            static_cast<f32>(GX_ORTHOGRAPHIC),
            0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        };
        // clang-format on

        proj[GX_PROJECTION_A] = mtx[0][0];
        proj[GX_PROJECTION_B] = mtx[0][3];
        proj[GX_PROJECTION_C] = mtx[1][1];
        proj[GX_PROJECTION_D] = mtx[1][3];
        proj[GX_PROJECTION_E] = mtx[2][2];
        proj[GX_PROJECTION_F] = mtx[2][3];

        GXSetProjectionv_(proj);
        break;
    }

    default: {
#line 288
        EGG_ASSERT(0);
    }
    }
}

void StateGX::GXSetProjectionv_(const f32 pProj[GX_VIEWPORT_SZ]) {
    f32 old[GX_PROJECTION_SZ];
    GXGetProjectionv(old);

    if (s_cacheGX.flags & cCacheFlag_ProjectionV) {
        if (pProj[GX_PROJECTION_TP] == old[GX_PROJECTION_TP] && //
            pProj[GX_PROJECTION_A] == old[GX_PROJECTION_A] &&   //
            pProj[GX_PROJECTION_B] == old[GX_PROJECTION_B] &&   //
            pProj[GX_PROJECTION_C] == old[GX_PROJECTION_C] &&   //
            pProj[GX_PROJECTION_D] == old[GX_PROJECTION_D] &&   //
            pProj[GX_PROJECTION_E] == old[GX_PROJECTION_E] &&   //
            pProj[GX_PROJECTION_F] == old[GX_PROJECTION_F]) {

            return;
        }
    }

    GXSetProjectionv(pProj);

    if (s_flag & cFlag_EnableCache) {
        s_cacheGX.flags |= cCacheFlag_ProjectionV;
    }
}

void StateGX::GXSetViewport_(f32 left, f32 top, f32 width, f32 height, f32 near,
                             f32 far) {
    f32 old[GX_VIEWPORT_SZ];
    GXGetViewportv(old);

    if (s_cacheGX.flags & cCacheFlag_Viewport) {
        if (left == old[GX_VIEWPORT_L] &&   //
            top == old[GX_VIEWPORT_T] &&    //
            width == old[GX_VIEWPORT_W] &&  //
            height == old[GX_VIEWPORT_H] && //
            near == old[GX_VIEWPORT_N] &&   //
            far == old[GX_VIEWPORT_F]) {

            return;
        }
    }

    GXSetViewport(left, top, width, height, near, far);

    if (s_flag & cFlag_EnableCache) {
        s_cacheGX.flags |= cCacheFlag_Viewport;
    }
}

void StateGX::GXSetScissor_(u32 s0, u32 s1, u32 s2, u32 s3) {
#line 385
    EGG_ASSERT(s0 < 2048);
    EGG_ASSERT(s1 < 2048);
    EGG_ASSERT(s2 < 2048);
    EGG_ASSERT(s3 < 2048);

    u32 height, width, top, left;
    GXGetScissor(&left, &top, &width, &height);

    if (s_cacheGX.flags & cCacheFlag_Scissor) {
        if (s0 == left && s1 == top && s2 == width && s3 == height) {
            return;
        }
    }

    GXSetScissor(s0, s1, s2, s3);

    if (s_flag & cFlag_EnableCache) {
        s_cacheGX.flags |= cCacheFlag_Scissor;
    }
}

void StateGX::GXSetScissorBoxOffset_(int b0, int b1) {
#line 422
    EGG_ASSERT(b0 % 2 == 0);
    EGG_ASSERT(b1 % 2 == 0);

    if (s_cacheGX.flags & cCacheFlag_ScissorBox) {
        if (b0 == s_cacheGX.scissorX && b1 == s_cacheGX.scissorY) {
            return;
        }
    }

    GXSetScissorBoxOffset(b0, b1);

    s_cacheGX.scissorX = b0;
    s_cacheGX.scissorY = b1;

    if (s_flag & cFlag_EnableCache) {
        s_cacheGX.flags |= cCacheFlag_ScissorBox;
    }
}

void StateGX::GXSetColorUpdate_(bool enable) {
    if (s_cacheGX.flags & cCacheFlag_ColorUpdate) {
        if (enable == s_cacheGX.colorUpdate) {
            return;
        }
    }

    GXSetColorUpdate(enable);

    s_cacheGX.colorUpdate = enable;

    if (s_flag & cFlag_EnableCache) {
        s_cacheGX.flags |= cCacheFlag_ColorUpdate;
    }
}

void StateGX::GXSetAlphaUpdate_(bool enable) {
    if (s_cacheGX.flags & cCacheFlag_AlphaUpdate) {
        if (enable == s_cacheGX.alphaUpdate) {
            return;
        }
    }

    GXSetAlphaUpdate(enable);

    s_cacheGX.alphaUpdate = enable;

    if (s_flag & cFlag_EnableCache) {
        s_cacheGX.flags |= cCacheFlag_AlphaUpdate;
    }
}

void StateGX::GXSetDither_(bool enable) {
    if (s_cacheGX.flags & cCacheFlag_Dither) {
        if (enable == s_cacheGX.dither) {
            return;
        }
    }

    GXSetDither(enable);

    s_cacheGX.dither = enable;

    if (s_flag & cFlag_EnableCache) {
        s_cacheGX.flags |= cCacheFlag_Dither;
    }
}

void StateGX::setPixelFormatGX(GXPixelFmt pixFormat, GXZFmt16 zFmt16) {
    if ((s_flag & cFlag_EnableCache) &&
            (s_pixFormatCurrent != pixFormat || s_zFmt16Current != zFmt16) ||
        // Always set if cache is disabled!
        !(s_flag & cFlag_EnableCache)) {

        GXSetPixelFmt(pixFormat, zFmt16);
        GXSetColorUpdate(s_cacheGX.colorUpdate);
        GXSetAlphaUpdate(s_cacheGX.alphaUpdate);
    }

    s_pixFormatCurrent = pixFormat;
    s_zFmt16Current = zFmt16;
}

} // namespace EGG
