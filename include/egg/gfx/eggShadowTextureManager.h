#ifndef EGG_GFX_SHADOW_TEXTURE_MANAGER_H
#define EGG_GFX_SHADOW_TEXTURE_MANAGER_H
#include "types_egg.h"

namespace EGG
{
    class ShadowTextureManager
    {
    public:
        enum EShadowMgrFlag
        {
            SHADOW_MGR_ACTIVE = (1 << 0)
        };

    private:
        static const int GROUP_MAX = 16;

        u8 mFlags; // at 0x0
        u16 mFreeGroup; // at 0x2
        u16 mShadowIdx; // at 0x4
        ShadowTexture *mGroups[GROUP_MAX]; // at 0x8

    public:
        ShadowTextureManager();
        virtual ~ShadowTextureManager() {} // at 0x8

        void Reset();
        void Set(u16, ShadowTexture *);
        u16 Append(ShadowTexture *);
        void Calc();
        void Draw(Screen *);

        bool IsActive() const { return mFlags & SHADOW_MGR_ACTIVE; }
    };
}

#endif
