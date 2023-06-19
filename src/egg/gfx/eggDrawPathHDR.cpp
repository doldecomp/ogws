#include "eggDrawPathHDR.h"
#include "eggPostEffectHDR.h"
#include "eggStateGX.h"
#include "eggTextureBuffer.h"

namespace EGG
{
    DrawPathHDR::DrawPathHDR() :
        mPostEffect(NULL)
    {
        mPostEffect = new PostEffectHDR();
        mPostEffect->onReset();
    }

    DrawPathHDR::~DrawPathHDR()
    {
        delete mPostEffect;
        mPostEffect = NULL;
    }

    void DrawPathHDR::calc()
    {
    }

    void DrawPathHDR::draw(u16 idx)
    {
        const Screen::DataEfb& efb = GetScreen().GetDataEfb();

        switch(idx)
        {
            case 0:
                capture(cBufferType_2, false);
                ScreenEffectBase::sFlag |= 0x2;
                break;
            case 1:
                StateGX::ScopedAlpha alpha(false);
                
                TextureBuffer *p_buff = getBuffer(cBufferType_2);
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

    int DrawPathHDR::getNumScnProc() const
    {
        return NUM_SCNPROC;
    }
}