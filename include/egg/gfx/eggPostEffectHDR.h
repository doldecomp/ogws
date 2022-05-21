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

    private:
        char UNK_0x4[0x28];
    };
}

#endif