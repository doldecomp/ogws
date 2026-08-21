#include <egg/gfxe.h>

#include <revolution/GX.h>

namespace EGG {

PostEffectSimple::PostEffectSimple() {}

void PostEffectSimple::reset() {
    mColor = DrawGX::WHITE;
    mIntensity = 1.0f;
    mBlendMode = cBlendMode_Xlu;
}

void PostEffectSimple::setMaterialInternal() {
    loadTextureInternal();

    GXColor color = mColor;
    if (mIntensity < 1.0f) {
        scaleRGBA(&color, color, mIntensity, true);
    }

    setMatColorChannel();

    GXSetNumTexGens(1);
    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);

    setMatInd();

    GXSetNumTevStages(1);
    GXSetTevDirect(GX_TEVSTAGE0);

    GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
    GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE,
                          GX_CH_ALPHA);

    GXSetTevKColorSel(GX_TEVSTAGE0, GX_TEV_KCSEL_K0);
    GXSetTevKAlphaSel(GX_TEVSTAGE0, GX_TEV_KASEL_K0_A);
    GXSetTevKColor(GX_KCOLOR0, color);

    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, mpCapTexture->getLoadMap(),
                  GX_COLOR_NULL);

    // Color = color.RGB * Tex0.RGB
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_KONST,
                    GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                    GX_TRUE, GX_TEVPREV);

    switch (mBlendMode) {
    case cBlendMode_Opa:
        // Alpha = color.A
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO,
                        GX_CA_KONST);
        break;

    case cBlendMode_Xlu:
        // Alpha = color.A * Tex0.A
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_KONST,
                        GX_CA_ZERO);
        break;

    case cBlendMode_Intensity:
        // Color = color.RGB * Tex0.A
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXA, GX_CC_KONST,
                        GX_CC_ZERO);
        // Alpha = color.A * color.A
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_KONST, GX_CA_KONST,
                        GX_CA_ZERO);
        break;
    }

    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                    GX_TRUE, GX_TEVPREV);

    setMatPE();
}

} // namespace EGG
