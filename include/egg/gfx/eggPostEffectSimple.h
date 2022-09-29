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
        char UNK_0x20[0xC];
    };
}

#endif