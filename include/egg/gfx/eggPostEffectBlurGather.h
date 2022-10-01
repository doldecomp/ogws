#ifndef EGG_GFX_POST_EFFECT_BLUR_GATHER_H
#define EGG_GFX_POST_EFFECT_BLUR_GATHER_H
#include "types_egg.h"
#include "eggPostEffectBase.h"
#include "eggAssert.h"
#include "eggDrawGX.h"

namespace EGG
{
    class PostEffectBlurGather : public PostEffectBase
    {
    public:
        enum Constants
        {
            eCnstBlurGather_Max = 3
        };

        struct BlurGatherData
        {
            void reset()
            {
                mpCapTexture = NULL;
                mColor = DrawGX::scColorWhite;
                mColorScale = 1.0f;
                BYTE_0xC = 0;
            }

            CapTexture *mpCapTexture; // at 0x0
            GXColor mColor; // at 0x4
            f32 mColorScale; // at 0x8
            u8 BYTE_0xC;
        };

    public:
        PostEffectBlurGather();
        virtual ~PostEffectBlurGather() {} // at 0x8
        virtual void reset(); // at 0x14
        virtual void preDraw(); // at 0x18

        void setNumBlurGather(u8 num)
        {
            #line 58
            EGG_ASSERT(num <= eCnstBlurGather_Max);
            mNumBlurGatherData = num;
        }

        bool textureReady() const { return mpCapTexture != NULL && (mFlags & 0x1) == 0; }

    private:
        u8 mNumBlurGatherData; // at 0x20
        u8 mFlags; // at 0x21
        f32 FLOAT_0x24;
        BlurGatherData mBlurGatherData[eCnstBlurGather_Max]; // at 0x28
    };
}

#endif