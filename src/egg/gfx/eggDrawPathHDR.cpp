#include "eggDrawPathHDR.h"
#include "eggPostEffectHDR.h"
#include "eggStateGX.h"

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
        const Screen::EfbData* efb = GetScreen().GetDataEfb();

        switch(idx)
        {
            case 0:
                g_capture_for_efb(cBufferType_2, false);
                lbl_804BEC54 |= 0x2;
                break;
            case 1:
                // u8 required to fix regalloc with any cache usage,
                // but StateGX functions require bool to match
                union
                {
                    u8 alpha;
                    bool bAlpha;
                };
                alpha = StateGX::getCache().alphaUpdate;
                
                StateGX::GXSetAlphaUpdate_(false);
                
                TextureBuffer *p_buff = getBuffer(cBufferType_2);
                #line 74
                EGG_ASSERT(p_buff);
                mPostEffect->setCapTexture(p_buff);
                mPostEffect->setProjection(GetScreen());
                mPostEffect->draw(GetScreen().GetWidth(), GetScreen().GetHeight());

                freeEffectBuffer(cBufferType_2);
                lbl_804BEC54 &= ~0x3;

                StateGX::GXSetAlphaUpdate_(bAlpha);
                break;
        }
    }

    int DrawPathHDR::getNumScnProc() const
    {
        return NUM_SCNPROC;
    }
}