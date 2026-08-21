#include <egg/gfxe.h>

#include <revolution/GX.h>

namespace EGG {

PostEffectMask::PostEffectMask() {}

void PostEffectMask::reset() {
    mColor = DrawGX::WHITE;
    mIntensity = 0.0f;
    mpDstScreen = NULL;
    unk30 = 1.0f;
    unk20 = 0;
}

void PostEffectMask::setMaterialInternal() {
    bool hasScreen = mpDstScreen != NULL;
    loadTextureInternal();

    if (hasScreen) {
#line 112
        EGG_ASSERT(getCapTexture()->getLoadMap() != mpDstScreen->getLoadMap());
        mpDstScreen->load(mpDstScreen->getLoadMap());
    }

    GXColor maskColor;
    scaleRGBA(&maskColor, mColor, mIntensity, false);

    setMatColorChannel();

    GXSetNumTexGens(1);
    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);

    setMatInd();

    GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE,
                          GX_CH_ALPHA);

    ;

    setMatPE();
}

} // namespace EGG
