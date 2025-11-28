#include <egg/gfxe.h>

namespace EGG {

DrawPathHDR::DrawPathHDR() : mPostEffect(NULL) {
    mPostEffect = new PostEffectHDR();
    mPostEffect->configure();
}

DrawPathHDR::~DrawPathHDR() {
    delete mPostEffect;
    mPostEffect = NULL;
}

void DrawPathHDR::internalCalc() {}

void DrawPathHDR::internalDraw(u16 step) {
    const Screen::DataEfb& rEfb = GetScreen().GetDataEfb();

    switch (step) {
    case EStep_0: {
        capture(cBufferType_2, false);
        ScreenEffectBase::sFlag |= 0x2;
        break;
    }

    case EStep_1: {
        StateGX::ScopedAlphaUpdate alpha(false);

        TextureBuffer* p_buff = getBuffer(cBufferType_2);
#line 74
        EGG_ASSERT(p_buff);
        mPostEffect->setCapTexture(p_buff);
        mPostEffect->setProjection(GetScreen());
        mPostEffect->draw(GetScreen().GetWidth(), GetScreen().GetHeight());

        release(cBufferType_2);
        ScreenEffectBase::sFlag &= ~0x3;
        break;
    }
    }
}

int DrawPathHDR::getNumStep() const {
    return EStep_Max;
}

} // namespace EGG
