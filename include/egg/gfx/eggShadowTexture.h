#ifndef EGG_GFX_SHADOW_TEXTURE_H
#define EGG_GFX_SHADOW_TEXTURE_H
#include "types_egg.h"
#include "eggModelSnapshot.h"
#include "eggPostEffectBase.h"

namespace EGG
{
    class ShadowTexture : public ModelSnapshot
    { 
    public:
        ShadowTexture(u16, u16, u16);

        void Calc();
        void Draw(Screen *, bool, bool, bool);

        // Temporary names, needed for regalloc
        void SetCapTexture0(CapTexture *pCapTexture)
        {
            POST_EFF_0xE4->setCapTexture(pCapTexture);
        }
        void SetCapTexture1(CapTexture *pCapTexture)
        {
            POST_EFF_0xE8->setCapTexture(pCapTexture);
        }

    //private:
        u16 SHORT_0x70;
        char UNK_0x72[0xE4 - 0x72];
        // TO-DO: May not be base
        PostEffectBase *POST_EFF_0xE4;
        PostEffectBase *POST_EFF_0xE8;
    };
}

#endif