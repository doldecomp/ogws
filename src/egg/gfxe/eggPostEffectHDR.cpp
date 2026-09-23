#include <egg/gfxe.h>

#include <revolution/GX.h>

namespace EGG {

PostEffectHDR::PostEffectHDR() {}

void PostEffectHDR::reset() {
    mBrightnessColor = DrawGX::WHITE;

    mFracExposureColor = mBrightnessColor;
    mThresholdColor = mBrightnessColor;
    mCutoffColor = mBrightnessColor;
    mExposureColor = mBrightnessColor;

    mExposureInv = 1.0f;
    mThresholdScale = 0.0f;

    mFlags = 0;
    mCutoffTevScale = GX_CS_SCALE_1;
    mExposureTevScale = GX_CS_SCALE_1;
}

void PostEffectHDR::calcScale() {
    f32 divisor = 6.0f;

    f32 scale = 1.0f / divisor;
    scale = mExposureInv > scale ? mExposureInv : scale;

    mIsSubtractive = false;
    scale = 1.0f / scale - 1.0f;

    if (scale <= 1.0f) {
        mCutoffTevScale = GX_CS_SCALE_1;
        mExposureTevScale = GX_CS_SCALE_1;

    } else if (scale <= 2.0f) {
        mCutoffTevScale = GX_CS_SCALE_1;
        mExposureTevScale = GX_CS_SCALE_2;
        scale = 0.5f * (scale - 1.0f);

    } else if (scale <= 3.0f) {
        mCutoffTevScale = GX_CS_SCALE_1;
        mExposureTevScale = GX_CS_SCALE_2;
        scale = 0.5f * (1.0f + (scale - 2.0f));

    } else if (scale <= 4.0f) {
        mCutoffTevScale = GX_CS_SCALE_1;
        mExposureTevScale = GX_CS_SCALE_4;
        scale = 0.25f * (scale - 3.0f);

    } else if (scale <= 5.0f) {
        mCutoffTevScale = GX_CS_SCALE_1;
        mExposureTevScale = GX_CS_SCALE_4;
        scale = 0.25f * (1.0f + (scale - 4.0f));
    }

    GXColor cutoff;
    scaleRGBA(&cutoff, mThresholdColor, mThresholdScale, true);

    GXColor frac;
    scaleRGBA(&frac, mExposureColor, scale, true);

    mFracExposureColor = frac;
    mCutoffColor = cutoff;
}

void PostEffectHDR::setMaterialInternal() {
    calcScale();
    loadTextureInternal();

    bool useStage2 = mFlags & cFlag_0;
    int tevStageNum = useStage2 + 2;

    setMatColorChannel();

    GXSetNumTexGens(1);
    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);

    setMatInd();

    GXSetTevKColor(GX_KCOLOR0, mCutoffColor);
    GXSetTevKColor(GX_KCOLOR1, mFracExposureColor);

    GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE,
                          GX_CH_ALPHA);

    GXSetNumTevStages(tevStageNum);

    for (int i = 0; i < tevStageNum; i++) {
        GXSetTevDirect(static_cast<GXTevStageID>(i));

        GXSetTevSwapMode(static_cast<GXTevStageID>(i), GX_TEV_SWAP0,
                         GX_TEV_SWAP0);

        switch (i) {
        case cTevStage_Threshold: {
            GXSetTevKColorSel(static_cast<GXTevStageID>(i), GX_TEV_KCSEL_K0);

            GXSetTevOrder(static_cast<GXTevStageID>(i), GX_TEXCOORD0,
                          getCapTexture()->getLoadMap(), GX_COLOR_NULL);

            // Tev0.RGB = (Tex.RGB - mCutoffColor.RGB)
            GXSetTevColorIn(static_cast<GXTevStageID>(i), GX_CC_KONST,
                            GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);

            // Tev0.RGB *= mCutoffTevScale
            GXSetTevColorOp(static_cast<GXTevStageID>(i), GX_TEV_SUB,
                            GX_TB_ZERO, mCutoffTevScale, GX_TRUE, GX_TEVREG0);
            break;
        }

        case cTevStage_Amplify: {
            GXSetTevKColorSel(static_cast<GXTevStageID>(i), GX_TEV_KCSEL_K1);

            GXSetTevOrder(static_cast<GXTevStageID>(i), GX_TEXCOORD_NULL,
                          GX_TEXMAP_NULL, GX_COLOR_NULL);

            if (!useStage2) {
                // Color = Tev0.RGB (+/-) (mFracExposureColor.RGB * Tev0.RGB)
                GXSetTevColorIn(static_cast<GXTevStageID>(i), GX_CC_ZERO,
                                GX_CC_C0, GX_CC_KONST, GX_CC_C0);

                // Color *= mExposureTevScale
                GXSetTevColorOp(static_cast<GXTevStageID>(i),
                                mIsSubtractive ? GX_TEV_SUB : GX_TEV_ADD,
                                GX_TB_ZERO, mExposureTevScale, GX_TRUE,
                                GX_TEVPREV);
            } else {
                // Color = mFracExposureColor.RGB * Tev0.RGB
                GXSetTevColorIn(static_cast<GXTevStageID>(i), GX_CC_ZERO,
                                GX_CC_C0, GX_CC_KONST, GX_CC_ZERO);
                GXSetTevColorOp(static_cast<GXTevStageID>(i), GX_TEV_ADD,
                                GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            }
            break;
        }

        case cTevStage_Stabilize: {
            GXSetTevOrder(static_cast<GXTevStageID>(i), GX_TEXCOORD_NULL,
                          GX_TEXMAP_NULL, GX_COLOR_NULL);

            // Color = Tev0.RGB (+/-) ((1 - Tev0.RGB) * Color)
            GXSetTevColorIn(static_cast<GXTevStageID>(i), GX_CC_CPREV,
                            GX_CC_ZERO, GX_CC_C0, GX_CC_C0);

            // Color *= mExposureTevScale
            GXSetTevColorOp(static_cast<GXTevStageID>(i),
                            mIsSubtractive ? GX_TEV_SUB : GX_TEV_ADD,
                            GX_TB_ZERO, mExposureTevScale, GX_TRUE, GX_TEVPREV);
            break;
        }

        default: {
            break;
        }
        }

        GXSetTevAlphaIn(static_cast<GXTevStageID>(i), GX_CA_ZERO, GX_CA_ZERO,
                        GX_CA_ZERO, GX_CA_KONST);
        GXSetTevAlphaOp(static_cast<GXTevStageID>(i), GX_TEV_ADD, GX_TB_ZERO,
                        GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    }

    setMatPE();
}

} // namespace EGG
