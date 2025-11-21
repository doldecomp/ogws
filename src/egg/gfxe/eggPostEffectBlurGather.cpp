#include "eggPostEffectBlurGather.h"
#include "eggDrawGX.h"
#include "eggCapTexture.h"
#include <revolution/GX.h>

namespace EGG
{
    PostEffectBlurGather::PostEffectBlurGather()
    {
    }

    void PostEffectBlurGather::reset()
    {
        BlurGatherData* it = mBlurGatherData;
        for (int i = 0; i < eCnstBlurGather_Max; i++, it++){
            it->reset();
        }

        mNumBlurGatherData = 1;
        mFlags = 0x1;
        FLOAT_0x24 = 0.0f;
    }

    // https://decomp.me/scratch/7ue6S
    void PostEffectBlurGather::preDraw()
    {
    }
}