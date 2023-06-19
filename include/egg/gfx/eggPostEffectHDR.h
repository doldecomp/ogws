#ifndef EGG_GFX_POST_EFFECT_HDR_H
#define EGG_GFX_POST_EFFECT_HDR_H
#include "types_egg.h"
#include "eggPostEffectBase.h"

namespace EGG
{
    class PostEffectHDR : public PostEffectBase
    {
    public:
        PostEffectHDR();
        virtual ~PostEffectHDR() {} // at 0x8
        virtual void reset(); // at 0x14
        virtual void preDraw(); // at 0x18

        void setupRange();

    private:
        GXColor COLOR_0x20;
        GXColor COLOR_0x24;
        f32 FLOAT_0x28;
        f32 FLOAT_0x2C;
        GXColor COLOR_0x30;
        GXColor COLOR_0x34;
        GXColor COLOR_0x38;
        u32 WORD_0x3C;
        u32 WORD_0x40;
        u8 BYTE_0x44;
        u8 BYTE_0x45;
    };
}

#endif