#include "eggPostEffectBlur.h"
#include "eggDrawGX.h"
#include "eggGXUtility.h"
#include "eggCapTexture.h"
#include "math_triangular.h"
#include <revolution/GX.h>

namespace EGG
{
    using namespace nw4r;
    
    PostEffectBlur::PostEffectBlur()
    {
    }

    void PostEffectBlur::reset()
    {
        // Maybe old code? Draw seems to suggest it is an array
        BlurData* it = mBlurData;
        for (int i = 0; i < CIRCLE_MAX; i++, it++){
            it->reset();
        }

        mNumBlurData = 1;
        mColorScale = 1.0f;
        WORD_0x24 = 0;
    }

    void PostEffectBlur::draw(f32 width, f32 height)
    {
        if (isVisible())
        {
            loadTexObj();
            setMatColorChannel();
            setMatInd();
            setMatPE();
            setVtxState();

            for (u8 i = 0; i < mNumBlurData; i++)
            {
                int end = (mBlurData[i].BYTE_0x0 - 1) / 8;
                for (u8 j = 0; j <= end; j++)
                {
                    drawBlurPass(i, j);
                    drawDL(mOffsetX, mOffsetY, width * mScaleX, height * mScaleY);
                    DrawGX::SetBlendMode(DrawGX::BLEND_2);
                }
            }
        }
    }

    // https://decomp.me/scratch/pbk8u
    void PostEffectBlur::drawBlurPass(u8 idx, u8 pass)
    {
    }
}