#ifndef EGG_GFX_POST_EFFECT_SIMPLE_H
#define EGG_GFX_POST_EFFECT_SIMPLE_H
#include "types_egg.h"
#include "eggPostEffectBase.h"

namespace EGG
{
    class PostEffectSimple : public PostEffectBase
    {
    public:
        PostEffectSimple();
        virtual ~PostEffectSimple() {} // at 0x8
        virtual void reset(); // at 0x14
        virtual void preDraw(); // at 0x18

    private:
        GXColor mColor; // at 0x20
        f32 FLOAT_0x24;
        char UNK_0x28[0x4];
        UNKWORD WORD_0x2C;
    };
}

#endif