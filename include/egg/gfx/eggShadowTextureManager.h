#ifndef EGG_GFX_SHADOW_TEXTURE_MANAGER_H
#define EGG_GFX_SHADOW_TEXTURE_MANAGER_H
#include "types_egg.h"

namespace EGG
{
    class ShadowTextureManager
    {
    private:
        static const int GROUP_MAX = 16;

        bool mIsActive; // at 0x0
        u16 mNumFreeGroups; // at 0x2
        u16 SHORT_0x4;
        ShadowTexture *mTextures[GROUP_MAX]; // at 0x8

    public:
        ShadowTextureManager();
        virtual ~ShadowTextureManager() {}

        void Initialize();
        void Set(u16, ShadowTexture *);
        void Append(ShadowTexture *);
        void Calc();
        void Draw(Screen *);
    };
}

#endif