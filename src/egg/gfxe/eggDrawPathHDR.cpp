#include <egg/gfxe.h>

namespace EGG {

DrawPathHDR::DrawPathHDR() : mpPostEffect(NULL) {
    mpPostEffect = new PostEffectHDR();
    mpPostEffect->configure();
}

DrawPathHDR::~DrawPathHDR() {
    delete mpPostEffect;
    mpPostEffect = NULL;
}

void DrawPathHDR::internalCalc() {}

void DrawPathHDR::internalDraw(u16 step) {
    const Screen::DataEfb& rEfb = GetScreen().GetDataEfb();

    switch (step) {
    case cStep_Capture: {
        captureEfb(cBufferType_2, false);
        setGlbFlag1(true);
        break;
    }

    case cStep_Draw: {
        StateGX::AutoAlphaUpdate alphaLock(false);

        TextureBuffer* p_buff = getBuffer(cBufferType_2);
#line 74
        EGG_ASSERT(p_buff);
        mpPostEffect->setCapTexture(p_buff);
        mpPostEffect->setProjection(GetScreen());
        mpPostEffect->draw(GetScreen().GetWidth(), GetScreen().GetHeight());

        releaseEfb(cBufferType_2);
        setGlbFlag1(false);
        setGlbFlag0(false);
        break;
    }
    }
}

u16 DrawPathHDR::getNumStep() const {
    return cStep_Max;
}

} // namespace EGG
