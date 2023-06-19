#ifndef EGG_GFX_POST_EFFECT_BLUR_H
#define EGG_GFX_POST_EFFECT_BLUR_H
#include "types_egg.h"
#include "eggPostEffectBase.h"
#include "eggAssert.h"

namespace EGG
{
    class PostEffectBlur : public PostEffectBase
    {
    public:
        struct BlurData
        {
            void reset()
            {
                BYTE_0x0 = 0x10;
                mColor = (GXColor){215, 215, 215, 215};
                FLOAT_0x8 = 0.0f;
                mRadius = 1.0f;
                WORD_0x10 = 0;
            }

            u8 BYTE_0x0;
            GXColor mColor; // at 0x1
            f32 FLOAT_0x8;
            f32 mRadius; // at 0xC
            u32 WORD_0x10;
        };

    public:
        PostEffectBlur();
        virtual ~PostEffectBlur() {} // at 0x8
        virtual void draw(f32, f32); // at 0x10
        virtual void reset(); // at 0x14

        void drawBlurPass(u8, u8);

        BlurData * getBlurData(int dataNum)
        {
            #line 102
            EGG_ASSERT(dataNum < CIRCLE_MAX);
            return &mBlurData[dataNum];
        }

    private:
        static const u32 CIRCLE_MAX = 4;

        u8 mNumBlurData; // at 0x20
        u32 WORD_0x24;
        char UNK_0x28[0x2C - 0x28];
        f32 mColorScale; // at 0x2C
        BlurData mBlurData[CIRCLE_MAX]; // at 0x30
    };
}

#endif