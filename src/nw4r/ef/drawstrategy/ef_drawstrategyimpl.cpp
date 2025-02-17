#include <nw4r/ef.h>

#include <revolution/GX.h>

#include <cmath>

namespace nw4r {
namespace ef {

const math::VEC3 DrawStrategyImpl::mXUnitVec(1.0f, 0.0f, 0.0f);
const math::VEC3 DrawStrategyImpl::mYUnitVec(0.0f, 1.0f, 0.0f);
const math::VEC3 DrawStrategyImpl::mZUnitVec(0.0f, 0.0f, 1.0f);
const math::VEC3 DrawStrategyImpl::mZeroVec(0.0f, 0.0f, 0.0f);

// clang-format off
const math::MTX34 DrawStrategyImpl::mIdentityMtx(
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f);
// clang-format on

/******************************************************************************
 *
 * DrawStrategyImpl
 *
 ******************************************************************************/
DrawStrategyImpl::DrawStrategyImpl() {}

void DrawStrategyImpl::InitTexture(const EmitterDrawSetting& rSetting) {
    mNumTexmap = 0;

    mTexmapMap[TEX_LAYER_1] = -1;
    mTexmapMap[TEX_LAYER_2] = -1;
    mTexmapMap[TEX_LAYER_IND] = -1;

    if (rSetting.mFlags & EmitterDrawSetting::FLAG_TEX1_ENABLE) {
        mTexmapMap[TEX_LAYER_1] = 0;
        mNumTexmap++;
    }

    if (rSetting.mFlags & EmitterDrawSetting::FLAG_TEX2_ENABLE) {
        mTexmapMap[TEX_LAYER_2] = mNumTexmap;
        mNumTexmap++;
    }

    if (rSetting.mFlags & EmitterDrawSetting::FLAG_TEXIND_ENABLE) {
        mTexmapMap[TEX_LAYER_IND] = mNumTexmap;
        mNumTexmap++;
    }

    GXSetNumTexGens(mNumTexmap);
}

void DrawStrategyImpl::InitTev(const EmitterDrawSetting& rSetting,
                               const DrawInfo& rInfo) {

    int i;

    GXSetClipMode(rSetting.mFlags & EmitterDrawSetting::FLAG_CLIP_DISABLE
                      ? GX_CLIP_DISABLE
                      : GX_CLIP_ENABLE);

    GXSetNumTevStages(rSetting.mNumTevs);
    GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE,
                          GX_CH_ALPHA);

    for (i = 0; i < rSetting.mNumTevs; i++) {
        GXSetTevDirect(static_cast<GXTevStageID>(i));

        GXSetTevColorIn(static_cast<GXTevStageID>(i),
                        static_cast<GXTevColorArg>(rSetting.mTevColor[i].mA),
                        static_cast<GXTevColorArg>(rSetting.mTevColor[i].mB),
                        static_cast<GXTevColorArg>(rSetting.mTevColor[i].mC),
                        static_cast<GXTevColorArg>(rSetting.mTevColor[i].mD));

        GXSetTevAlphaIn(static_cast<GXTevStageID>(i),
                        static_cast<GXTevAlphaArg>(rSetting.mTevAlpha[i].mA),
                        static_cast<GXTevAlphaArg>(rSetting.mTevAlpha[i].mB),
                        static_cast<GXTevAlphaArg>(rSetting.mTevAlpha[i].mC),
                        static_cast<GXTevAlphaArg>(rSetting.mTevAlpha[i].mD));

        GXSetTevColorOp(
            static_cast<GXTevStageID>(i),
            static_cast<GXTevOp>(rSetting.mTevColorOp[i].mOp),
            static_cast<GXTevBias>(rSetting.mTevColorOp[i].mBias),
            static_cast<GXTevScale>(rSetting.mTevColorOp[i].mScale),
            static_cast<GXBool>(rSetting.mTevColorOp[i].mClamp),
            static_cast<GXTevRegID>(rSetting.mTevColorOp[i].mOutReg));

        // @bug Copy-paste error, should use mTevAlphaOp
        GXSetTevAlphaOp(
            static_cast<GXTevStageID>(i),
            static_cast<GXTevOp>(rSetting.mTevColorOp[i].mOp),
            static_cast<GXTevBias>(rSetting.mTevColorOp[i].mBias),
            static_cast<GXTevScale>(rSetting.mTevColorOp[i].mScale),
            static_cast<GXBool>(rSetting.mTevColorOp[i].mClamp),
            static_cast<GXTevRegID>(rSetting.mTevColorOp[i].mOutReg));

        GXSetTevKColorSel(
            static_cast<GXTevStageID>(i),
            static_cast<GXTevKColorSel>(rSetting.mTevKColorSel[i]));

        GXSetTevKAlphaSel(
            static_cast<GXTevStageID>(i),
            static_cast<GXTevKAlphaSel>(rSetting.mTevKAlphaSel[i]));

        GXSetTevSwapMode(static_cast<GXTevStageID>(i), GX_TEV_SWAP0,
                         GX_TEV_SWAP0);

        if (i == GX_TEVSTAGE0) {
            if (mTexmapMap[TEX_LAYER_1] < 0) {
                GXSetTevOrder(static_cast<GXTevStageID>(i), GX_TEXCOORD_NULL,
                              GX_TEXMAP_NULL, GX_COLOR0A0);
            } else {
                GXSetTevOrder(static_cast<GXTevStageID>(i), GX_TEXCOORD0,
                              GX_TEXMAP0, GX_COLOR0A0);
            }
        } else {
            if (mTexmapMap[TEX_LAYER_2] < 0) {
                GXSetTevOrder(static_cast<GXTevStageID>(i), GX_TEXCOORD_NULL,
                              GX_TEXMAP_NULL, GX_COLOR0A0);
            } else {
                GXSetTevOrder(
                    static_cast<GXTevStageID>(i),
                    static_cast<GXTexCoordID>(mTexmapMap[TEX_LAYER_2]),
                    static_cast<GXTexMapID>(mTexmapMap[TEX_LAYER_2]),
                    GX_COLOR0A0);
            }
        }
    }

    if (rSetting.mFlags & EmitterDrawSetting::FLAG_TEXIND_ENABLE) {
        GXSetNumIndStages(1);

        GXSetIndTexOrder(GX_INDTEXSTAGE0,
                         static_cast<GXTexCoordID>(mTexmapMap[TEX_LAYER_IND]),
                         static_cast<GXTexMapID>(mTexmapMap[TEX_LAYER_IND]));

        GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);
        GXSetIndTexMtx(GX_ITM_0, rSetting.mIndTexOffsetMtx,
                       rSetting.mIndTexScaleExp);

        GXSetTevIndirect(
            static_cast<GXTevStageID>(rSetting.mIndirectTargetStage),
            GX_INDTEXSTAGE0, GX_ITF_8, GX_ITB_STU, GX_ITM_0, GX_ITW_OFF,
            GX_ITW_OFF, FALSE, FALSE, GX_ITBA_OFF);
    } else {
        GXSetNumIndStages(0);
    }

    GXSetZCompLoc(rSetting.mFlags & EmitterDrawSetting::FLAG_ZCOMP_BEFORE_TEX
                      ? TRUE
                      : FALSE);

    GXSetCullMode(GX_CULL_NONE);
    GXSetCoPlanar(FALSE);

    GXSetBlendMode(static_cast<GXBlendMode>(rSetting.mBlendMode.mType),
                   static_cast<GXBlendFactor>(rSetting.mBlendMode.mSrcFactor),
                   static_cast<GXBlendFactor>(rSetting.mBlendMode.mDstFactor),
                   static_cast<GXLogicOp>(rSetting.mBlendMode.mOp));

    GXSetZMode(
        rSetting.mFlags & EmitterDrawSetting::FLAG_ZCOMP_ENABLE_TEST ? TRUE
                                                                     : FALSE,
        static_cast<GXCompare>(rSetting.mZCompareFunc),
        rSetting.mFlags & EmitterDrawSetting::FLAG_ZCOMP_ENABLE_UPDATE ? TRUE
                                                                       : FALSE);

    if (rSetting.mFlags & EmitterDrawSetting::FLAG_FOG_ENABLE) {
        GXFogType type;
        f32 start, end, near, far;
        GXColor color;

        rInfo.GetFog(&type, &start, &end, &near, &far, &color);
        GXSetFog(type, color, start, end, near, far);
    } else {
        GXColor color = {0, 0, 0, 0};
        GXSetFog(GX_FOG_NONE, color, 0.0f, 100.0f, 0.0f, 100.0f);
    }
}

void DrawStrategyImpl::InitColor(ParticleManager* pManager,
                                 const EmitterDrawSetting& rSetting,
                                 const DrawInfo& rInfo) {

#pragma unused(pManager)

    int i;

    mPrevARef0 = -1;
    mPrevARef1 = -1;

    GXSetNumChans(1);

    if (rInfo.IsLightEnable() &&
        rSetting.mColorInput.mRasColor == ColorInput::RASCOLOR_LIGHTING) {

        GXSetChanCtrl(GX_COLOR0, TRUE, GX_SRC_REG, GX_SRC_REG,
                      rInfo.GetLightMask(), GX_DF_NONE,
                      rInfo.IsSpotLight() ? GX_AF_SPOT : GX_AF_NONE);
    } else {
        GXSetChanCtrl(GX_COLOR0, FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL,
                      GX_DF_NONE, GX_AF_NONE);
    }

    GXSetChanCtrl(GX_ALPHA0, FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL,
                  GX_DF_NONE, GX_AF_NONE);
    GXSetChanCtrl(GX_COLOR1A1, FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL,
                  GX_DF_NONE, GX_AF_NONE);

    GXColor mat;
    mat.a = mat.r = mat.g = mat.b = 255;

    GXColor amb;
    amb.a = amb.r = amb.g = amb.b = 0;

    GXSetChanMatColor(GX_COLOR0A0, mat);
    GXSetChanAmbColor(GX_COLOR0A0, amb);

    mUseColor1 = false;
    mUseColor2 = false;

    for (i = 0; i < GX_MAX_TEVREG - 1; i++) {
        if (rSetting.mColorInput.mTevColor[i] == ColorInput::TEVCOLOR1_1 ||
            rSetting.mColorInput.mTevColor[i] == ColorInput::TEVCOLOR1_2) {
            mUseColor1 = true;
        }

        // @bug Copy-paste error, should use TEVCOLOR2_*
        if (rSetting.mColorInput.mTevColor[i] == ColorInput::TEVCOLOR1_1 ||
            rSetting.mColorInput.mTevColor[i] == ColorInput::TEVCOLOR1_2) {
            mUseColor2 = true;
        }
    }

    for (i = 0; i < GX_MAX_KCOLOR; i++) {
        if (rSetting.mColorInput.mTevKColor[i] == ColorInput::TEVCOLOR1_1 ||
            rSetting.mColorInput.mTevKColor[i] == ColorInput::TEVCOLOR1_2) {
            mUseColor1 = true;
        }

        if (rSetting.mColorInput.mTevKColor[i] == ColorInput::TEVCOLOR2_3 ||
            rSetting.mColorInput.mTevKColor[i] == ColorInput::TEVCOLOR2_2) {
            mUseColor2 = true;
        }
    }
}

void DrawStrategyImpl::SetupGP(Particle* pParticle,
                               const EmitterDrawSetting& rSetting,
                               const DrawInfo& rInfo, bool first,
                               bool xfDirty) {

#pragma unused(xfDirty)

    struct VtxDescData {
        GXAttrType type;     // at 0x0
        GXCompCnt compCnt;   // at 0x4
        GXCompType compType; // at 0x8
    };

    bool changed;
    bool xfBug;

    changed = _SetupACmp(pParticle, rSetting, first);
    xfBug = changed;

    changed = _SetupTevReg(pParticle, rSetting, first);
    xfBug = xfBug || changed;

    changed = _SetupTexture(pParticle, rSetting, rInfo, first);
    xfBug = xfBug && !changed;

    if ((rSetting.mFlags & EmitterDrawSetting::FLAG_CLIP_DISABLE) ||
        !pParticle->mParticleManager->mManagerEM->mManagerEF->mManagerES
             ->mXFFlushSafe) {
        return;
    }

    VtxDescData vtxDescPos;
    VtxDescData vtxDescNrm;
    VtxDescData vtxDescTex0;
    u8 shift;

    GXGetVtxDesc(GX_VA_POS, &vtxDescPos.type);
    GXGetVtxDesc(GX_VA_NRM, &vtxDescNrm.type);
    GXGetVtxDesc(GX_VA_TEX0, &vtxDescTex0.type);

    GXGetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, &vtxDescPos.compCnt,
                    &vtxDescPos.compType, &shift);
    GXGetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, &vtxDescNrm.compCnt,
                    &vtxDescNrm.compType, &shift);
    GXGetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, &vtxDescTex0.compCnt,
                    &vtxDescTex0.compType, &shift);

    if (!xfBug) {
        return;
    }

    GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 8);
    {
        for (int i = 0; i < 8; i++) {
            if (vtxDescPos.type != GX_NONE) {
                switch (vtxDescPos.type) {
                case GX_DIRECT: {

                    switch (vtxDescPos.compCnt) {
                    case GX_POS_XYZ: {

                        switch (vtxDescPos.compType) {
                        case GX_U8: {
                            GXPosition3u8(0, 0, 0);
                            break;
                        }

                        case GX_S8: {
                            GXPosition3s8(0, 0, 0);
                            break;
                        }

                        case GX_U16: {
                            GXPosition3u16(0, 0, 0);
                            break;
                        }

                        case GX_S16: {
                            GXPosition3s16(0, 0, 0);
                            break;
                        }

                        case GX_F32: {
                            GXPosition3f32(0.0f, 0.0f, 0.0f);
                            break;
                        }
                        }

                        break;
                    }

                    case GX_POS_XY: {

                        switch (vtxDescPos.compType) {
                        case GX_U8: {
                            GXPosition2u8(0, 0);
                            break;
                        }

                        case GX_S8: {
                            GXPosition2s8(0, 0);
                            break;
                        }

                        case GX_U16: {
                            GXPosition2u16(0, 0);
                            break;
                        }

                        case GX_S16: {
                            GXPosition2s16(0, 0);
                            break;
                        }

                        case GX_F32: {
                            GXPosition2f32(0.0f, 0.0f);
                            break;
                        }
                        }

                        break;
                    }
                    }

                    break;
                }

                case GX_INDEX8: {
                    GXPosition1x8(0);
                    break;
                }

                case GX_INDEX16: {
                    GXPosition1x16(0);
                    break;
                }
                }
            }

            if (vtxDescNrm.type != GX_NONE) {
                switch (vtxDescNrm.type) {
                case GX_DIRECT: {

                    switch (vtxDescNrm.compCnt) {
                    case GX_NRM_XYZ: {

                        // @bug Missing GX_U8/GX_U16
                        switch (vtxDescNrm.compType) {
                        case GX_S8: {
                            GXNormal3u8(0, 0, 0);
                            break;
                        }

                        case GX_S16: {
                            GXNormal3u16(0, 0, 0);
                            break;
                        }

                        case GX_F32: {
                            GXNormal3f32(0.0f, 0.0f, 0.0f);
                            break;
                        }
                        }

                        break;
                    }
                    }

                    break;
                }

                case GX_INDEX8: {
                    GXNormal1x8(0);
                    break;
                }

                case GX_INDEX16: {
                    GXNormal1x16(0);
                    break;
                }
                }
            }

            if (vtxDescTex0.type != GX_NONE) {
                switch (vtxDescTex0.type) {
                case GX_DIRECT: {

                    switch (vtxDescTex0.compCnt) {
                    case GX_TEX_ST: {

                        switch (vtxDescTex0.compType) {
                        case GX_U8: {
                            GXTexCoord2u8(0, 0);
                            break;
                        }

                        case GX_S8: {
                            GXTexCoord2s8(0, 0);
                            break;
                        }

                        case GX_U16: {
                            GXTexCoord2u16(0, 0);
                            break;
                        }

                        case GX_S16: {
                            GXTexCoord2s16(0, 0);
                            break;
                        }

                        case GX_F32: {
                            GXTexCoord2f32(0.0f, 0.0f);
                            break;
                        }
                        }

                        break;
                    }

                    case GX_TEX_S: {

                        switch (vtxDescTex0.compType) {
                        case GX_U8: {
                            GXTexCoord1u8(0);
                            break;
                        }

                        case GX_S8: {
                            GXTexCoord1s8(0);
                            break;
                        }

                        case GX_U16: {
                            GXTexCoord1u16(0);
                            break;
                        }

                        case GX_S16: {
                            GXTexCoord1s16(0);
                            break;
                        }

                        case GX_F32: {
                            GXTexCoord1f32(0.0f);
                            break;
                        }
                        }

                        break;
                    }
                    }

                    break;
                }

                case GX_INDEX8: {
                    GXTexCoord1x8(0);
                    break;
                }

                case GX_INDEX16: {
                    GXTexCoord1x16(0);
                    break;
                }
                }
            }
        }
    }
    GXEnd();
}

bool DrawStrategyImpl::_SetupACmp(Particle* pParticle,
                                  const EmitterDrawSetting& rSetting,
                                  bool first) {

    // @bug Copy-paste error, double comparison
    if (first || mPrevARef0 != pParticle->mParameter.mACmpRef0 ||
        mPrevARef0 != pParticle->mParameter.mACmpRef0) {

        // @bug Copy-paste error, assigns ref0 to prev ref1
        mPrevARef0 = pParticle->mParameter.mACmpRef0;
        mPrevARef1 = pParticle->mParameter.mACmpRef0;

        GXSetAlphaCompare(static_cast<GXCompare>(rSetting.mACmpComp0),
                          pParticle->mParameter.mACmpRef0,
                          static_cast<GXAlphaOp>(rSetting.mACmpOp),
                          static_cast<GXCompare>(rSetting.mACmpComp1),
                          pParticle->mParameter.mACmpRef1);

        return true;
    }

    return false;
}

bool DrawStrategyImpl::_SetupTevReg(Particle* pParticle,
                                    const EmitterDrawSetting& rSetting,
                                    bool first) {

    bool changed = false;
    GXColor colorPri, colorSec;

    if (mUseColor1) {
        pParticle->Draw_GetColor(COLOR_LAYER_0, &colorPri, &colorSec);

        if (first ||
            (mPrevColor[COLOR_LAYER_0][COLOR_IDX_PRI].r != colorPri.r ||
             mPrevColor[COLOR_LAYER_0][COLOR_IDX_PRI].g != colorPri.g ||
             mPrevColor[COLOR_LAYER_0][COLOR_IDX_PRI].b != colorPri.b ||
             mPrevColor[COLOR_LAYER_0][COLOR_IDX_PRI].a != colorPri.a) ||
            (mPrevColor[COLOR_LAYER_0][COLOR_IDX_SEC].r != colorSec.r ||
             mPrevColor[COLOR_LAYER_0][COLOR_IDX_SEC].g != colorSec.g ||
             mPrevColor[COLOR_LAYER_0][COLOR_IDX_SEC].b != colorSec.b ||
             mPrevColor[COLOR_LAYER_0][COLOR_IDX_SEC].a != colorSec.a)) {

            changed = true;

            mPrevColor[COLOR_LAYER_0][COLOR_IDX_PRI] = colorPri;
            mPrevColor[COLOR_LAYER_0][COLOR_IDX_SEC] = colorSec;

            for (int i = 0; i < GX_MAX_TEVREG - 1; i++) {
                if (rSetting.mColorInput.mTevColor[i] ==
                    ColorInput::TEVCOLOR1_1) {

                    GXSetTevColor(static_cast<GXTevRegID>(GX_TEVREG0 + i),
                                  colorPri);
                }

                // @bug Typo of 'i'
                if (rSetting.mColorInput.mTevColor[1] ==
                    ColorInput::TEVCOLOR1_2) {

                    GXSetTevColor(static_cast<GXTevRegID>(GX_TEVREG0 + i),
                                  colorSec);
                }
            }

            for (int i = 0; i < GX_MAX_KCOLOR; i++) {
                if (rSetting.mColorInput.mTevKColor[i] ==
                    ColorInput::TEVCOLOR1_1) {

                    GXSetTevKColor(static_cast<GXTevKColorID>(GX_KCOLOR0 + i),
                                   colorPri);
                }

                if (rSetting.mColorInput.mTevKColor[i] ==
                    ColorInput::TEVCOLOR1_2) {

                    GXSetTevKColor(static_cast<GXTevKColorID>(GX_KCOLOR0 + i),
                                   colorSec);
                }
            }
        }
    }

    if (mUseColor2) {
        pParticle->Draw_GetColor(COLOR_LAYER_1, &colorPri, &colorSec);

        if (first ||
            (mPrevColor[COLOR_LAYER_1][COLOR_IDX_PRI].r != colorPri.r ||
             mPrevColor[COLOR_LAYER_1][COLOR_IDX_PRI].g != colorPri.g ||
             mPrevColor[COLOR_LAYER_1][COLOR_IDX_PRI].b != colorPri.b ||
             mPrevColor[COLOR_LAYER_1][COLOR_IDX_PRI].a != colorPri.a) ||
            (mPrevColor[COLOR_LAYER_1][COLOR_IDX_SEC].r != colorSec.r ||
             mPrevColor[COLOR_LAYER_1][COLOR_IDX_SEC].g != colorSec.g ||
             mPrevColor[COLOR_LAYER_1][COLOR_IDX_SEC].b != colorSec.b ||
             mPrevColor[COLOR_LAYER_1][COLOR_IDX_SEC].a != colorSec.a)) {

            changed = true;

            mPrevColor[COLOR_LAYER_1][COLOR_IDX_PRI] = colorPri;
            mPrevColor[COLOR_LAYER_1][COLOR_IDX_SEC] = colorSec;

            for (int i = 0; i < GX_MAX_TEVREG - 1; i++) {
                if (rSetting.mColorInput.mTevColor[i] ==
                    ColorInput::TEVCOLOR2_3) {

                    GXSetTevColor(static_cast<GXTevRegID>(GX_TEVREG0 + i),
                                  colorPri);
                }

                // @bug Typo of 'i'
                if (rSetting.mColorInput.mTevColor[1] ==
                    ColorInput::TEVCOLOR2_2) {

                    GXSetTevColor(static_cast<GXTevRegID>(GX_TEVREG0 + i),
                                  colorSec);
                }
            }

            for (int i = 0; i < GX_MAX_KCOLOR; i++) {
                if (rSetting.mColorInput.mTevKColor[i] ==
                    ColorInput::TEVCOLOR2_3) {

                    GXSetTevKColor(static_cast<GXTevKColorID>(GX_KCOLOR0 + i),
                                   colorPri);
                }

                if (rSetting.mColorInput.mTevKColor[i] ==
                    ColorInput::TEVCOLOR2_2) {

                    GXSetTevKColor(static_cast<GXTevKColorID>(GX_KCOLOR0 + i),
                                   colorSec);
                }
            }
        }
    }

    return changed;
}

bool DrawStrategyImpl::_SetupTexture(Particle* pParticle,
                                     const EmitterDrawSetting& rSetting,
                                     const DrawInfo& rInfo, bool first) {

    bool changed = false;

    for (int i = 0; i < TEX_LAYER_MAX; i++) {
        if (mTexmapMap[i] < 0) {
            continue;
        }

        if (pParticle->mParameter.mTexture[i] == NULL) {
            continue;
        }

        const TextureData* pTexData = pParticle->mParameter.mTexture[i];

        f32 scaleS = pParticle->Draw_GetTextureScaleS(i);
        f32 scaleT = pParticle->Draw_GetTextureScaleT(i);

        f32 transS = pParticle->Draw_GetTextureTransS(i);
        f32 transT = pParticle->Draw_GetTextureTransT(i);

        GXTexWrapMode wrapS = pParticle->GetTextureWrapS(i);
        GXTexWrapMode wrapT = pParticle->GetTextureWrapT(i);

        if (first || !mPrevTexture[i].IsEqual(
                         pTexData, scaleS, scaleT, transS, transT, wrapS, wrapT,
                         pParticle->mParameter.mTextureScale[i],
                         pParticle->mParameter.mTextureRotate[i],
                         pParticle->mParameter.mTextureTranslate[i])) {

            changed = true;

            mPrevTexture[i].Set(pTexData, scaleS, scaleT, transS, transT, wrapS,
                                wrapT, pParticle->mParameter.mTextureScale[i],
                                pParticle->mParameter.mTextureRotate[i],
                                pParticle->mParameter.mTextureTranslate[i]);

            int format = pTexData->format;

            GXTexObj texObj;
            GXTlutObj tlutObj;

            switch (format) {
            case GX_TF_C4:
            case GX_TF_C8:
            case GX_TF_C14X2: {
                GXInitTlutObj(&tlutObj, pTexData->tlut,
                              static_cast<GXTlutFmt>(pTexData->tlutFormat),
                              pTexData->tlutEntries);

                GXLoadTlut(&tlutObj, static_cast<GXTlut>(mTexmapMap[i]));

                GXInitTexObjCI(&texObj, pTexData->texture, pTexData->width,
                               pTexData->height, static_cast<GXTexFmt>(format),
                               wrapS, wrapT, pTexData->mipmap > 1,
                               mTexmapMap[i]);
                break;
            }

            case GX_TF_I4:
            case GX_TF_I8:
            case GX_TF_IA4:
            case GX_TF_IA8:
            case GX_TF_RGB565:
            case GX_TF_RGB5A3:
            case GX_TF_RGBA8:
            case GX_TF_CMPR: {
                GXInitTexObj(&texObj, pTexData->texture, pTexData->width,
                             pTexData->height, static_cast<GXTexFmt>(format),
                             wrapS, wrapT, pTexData->mipmap > 1);
                break;
            }

            default: {
                break;
            }
            }

            f32 maxLod = pTexData->mipmap + -1.0f;
            f32 lodBias = 0.0f;

            GXInitTexObjLOD(
                &texObj, pTexData->mipmap > 1 ? GX_LIN_MIP_LIN : GX_LINEAR,
                GX_LINEAR, 0.0f, maxLod, lodBias, FALSE, FALSE, GX_ANISO_1);

            GXLoadTexObj(&texObj, static_cast<GXTexMapID>(mTexmapMap[i]));

            math::MTX34 mtx;
            math::MTX34Identity(&mtx);

            math::MTX34 work;
            math::MTX34Identity(&work);
            {
                work._03 = pParticle->mParameter.mTextureTranslate[i].x;
                work._13 = pParticle->mParameter.mTextureTranslate[i].y;
            }
            math::MTX34Mult(&mtx, &work, &mtx);

            if (pParticle->mParameter.mTextureRotate[i] != 0.0f) {
                math::MTX34Identity(&work);
                {
                    work._03 = -0.5f;
                    work._13 = -0.5f;
                }
                math::MTX34Mult(&mtx, &work, &mtx);

                math::MTX34Identity(&work);
                {
                    f32 cr = std::cosf(pParticle->mParameter.mTextureRotate[i]);
                    work._00 = work._11 = cr;

                    f32 sr = std::sinf(pParticle->mParameter.mTextureRotate[i]);
                    work._01 = -sr;
                    work._10 = sr;
                }
                math::MTX34Mult(&mtx, &work, &mtx);

                math::MTX34Identity(&work);
                {
                    work._03 = 0.5f;
                    work._13 = 0.5f;
                }
                math::MTX34Mult(&mtx, &work, &mtx);
            }

            math::MTX34Identity(&work);
            {
                work._03 = -0.5f;
                work._13 = -0.5f;
            }
            math::MTX34Mult(&mtx, &work, &mtx);

            math::MTX34Identity(&work);
            {
                work._00 = pParticle->mParameter.mTextureScale[i].x;
                work._11 = pParticle->mParameter.mTextureScale[i].y;
            }
            math::MTX34Mult(&mtx, &work, &mtx);

            math::MTX34Identity(&work);
            {
                work._03 = 0.5f;
                work._13 = 0.5f;
            }
            math::MTX34Mult(&mtx, &work, &mtx);

            work._00 = scaleS;
            work._01 = 0.0f;
            work._02 = 0.0f;
            work._03 = transS;

            work._10 = 0.0f;
            work._11 = scaleT;
            work._12 = 0.0f;
            work._13 = transT;

            work._20 = 0.0f;
            work._21 = 0.0f;
            work._22 = 1.0f;
            work._23 = 0.0f;

            math::MTX34Mult(&mtx, &work, &mtx);

            if (!((rSetting.mFlags >> i + 7 /* FLAG_TEX1_PROJ */) & 1)) {
                GXLoadTexMtxImm(mtx, GX_TEXMTX0 + mTexmapMap[i] * 3,
                                GX_MTX_2x4);

                GXSetTexCoordGen(static_cast<GXTexCoordID>(mTexmapMap[i]),
                                 GX_TG_MTX2x4, GX_TG_TEX0,
                                 GX_TEXMTX0 + mTexmapMap[i] * 3);
            } else {
                math::MTX34Mult(&mtx, rInfo.GetProjMtx(), &mtx);

                GXLoadTexMtxImm(mtx, GX_PTTEXMTX0 + mTexmapMap[i] * 3,
                                GX_MTX_3x4);

                GXSetTexCoordGen2(static_cast<GXTexCoordID>(mTexmapMap[i]),
                                  GX_TG_MTX3x4, GX_TG_POS, GX_PNMTX0, FALSE,
                                  GX_PTTEXMTX0 + mTexmapMap[i] * 3);
            }
        }
    }

    return changed;
}

DrawStrategyImpl::GetFirstDrawParticleFunc
DrawStrategyImpl::GetGetFirstDrawParticleFunc(int drawOrder) {

    switch (drawOrder) {
    case DRAWORDER_YOUNGERS_FIRST: {
        return GetFirstDrawParticle_YoungersFirst;
    }

    default: /* DRAWORDER_ELDERS_FIRST */ {
        return GetFirstDrawParticle_EldersFirst;
    }
    }
}

DrawStrategyImpl::GetNextDrawParticleFunc
DrawStrategyImpl::GetGetNextDrawParticleFunc(int drawOrder) {

    switch (drawOrder) {
    case DRAWORDER_YOUNGERS_FIRST: {
        return GetNextDrawParticle_YoungersFirst;
    }

    default: /* DRAWORDER_ELDERS_FIRST */ {
        return GetNextDrawParticle_EldersFirst;
    }
    }
}

Particle*
DrawStrategyImpl::GetFirstDrawParticle_EldersFirst(ParticleManager* pManager) {

    return GetOldestDrawParticle(pManager);
}

Particle* DrawStrategyImpl::GetFirstDrawParticle_YoungersFirst(
    ParticleManager* pManager) {

    return GetYoungestDrawParticle(pManager);
}

Particle*
DrawStrategyImpl::GetNextDrawParticle_EldersFirst(ParticleManager* pManager,
                                                  Particle* pParticle) {

    return GetYoungerDrawParticle(pManager, pParticle);
}

Particle*
DrawStrategyImpl::GetNextDrawParticle_YoungersFirst(ParticleManager* pManager,
                                                    Particle* pParticle) {

    return GetElderDrawParticle(pManager, pParticle);
}

/******************************************************************************
 *
 * AheadContext
 *
 ******************************************************************************/
DrawStrategyImpl::AheadContext::AheadContext(const math::MTX34& rViewMtx,
                                             ParticleManager* pManager) {

    mCommon.mViewMtx = &rViewMtx;
    mCommon.mParticleManager = pManager;

    pManager->mManagerEM->CalcGlobalMtx(&mCommon.mEmitterMtx);
    pManager->CalcGlobalMtx(&mCommon.mParticleManagerMtx);

    math::MTX34Inv(&mCommon.mParticleManagerMtxInv,
                   &mCommon.mParticleManagerMtx);

    math::VEC3 axisY(mCommon.mEmitterMtx._01, mCommon.mEmitterMtx._11,
                     mCommon.mEmitterMtx._21);
    math::VEC3TransformNormal(&axisY, &mCommon.mParticleManagerMtxInv, &axisY);

    if (!Normalize(&axisY)) {
        axisY = math::VEC3(0.0f, 1.0f, 0.0f);
    }

    mCommon.mEmitterAxisY = axisY;

    math::VEC3 center(mCommon.mEmitterMtx._03, mCommon.mEmitterMtx._13,
                      mCommon.mEmitterMtx._23);
    math::VEC3TransformCoord(&center, &mCommon.mParticleManagerMtxInv, &center);

    mCommon.mEmitterCenter = center;

    EmitterDrawSetting& rDesc = *pManager->mResource->GetEmitterDrawSetting();

    switch (rDesc.typeDir) {
    case EmitterDrawSetting::DIR_NO_DESIGN: {
        math::MTX34& rMtx = mCommon.mParticleManagerMtxInv;
        math::VEC3 worldAxisY(rMtx._01, rMtx._11, rMtx._21);

        if (!Normalize(&worldAxisY)) {
            worldAxisY = math::VEC3(0.0f, 1.0f, 0.0f);
        }

        mNoDesign.mWorldYAxis = worldAxisY;
        break;
    }

    default: {
        break;
    }
    }
}

} // namespace ef
} // namespace nw4r
