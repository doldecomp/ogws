#ifndef EGG_GFX_LIGHT_TEXTURE_MANAGER_H
#define EGG_GFX_LIGHT_TEXTURE_MANAGER_H
#include "types_egg.h"
#include "eggIBinary.h"
#include "eggScreen.h"

namespace EGG
{
    class LightTextureManager : IBinary<LightTextureManager>
    {
    public:
        struct Bin : IBinary::Bin
        {
            char UNK_0x10[0x20 - 0x10];
        };

        enum LightTexMgrFlag
        {
            CLEAR_WORKSPACE = (1 << 3)
        };

    public:
        LightTextureManager(LightManager *);
        virtual void SetBinaryInner(const IBinary::Bin&); // at 0x8
        virtual void GetBinaryInner(IBinary::Bin *) const; // at 0xC
        virtual const char * GetBinaryType() const; // at 0x10
        virtual u8 GetVersion() const = 0; // at 0x18

        u16 createTexture(const char *);
        int replaceModelTexture(int, ModelEx *) const;
        int getTextureIndex(const char *) const;
        void correctLightObject();
        void frameReset();
        void draw(LightManager *, const Screen::DataEfb&, f32, f32, f32, f32);

        bool isEnableClearWorkSpace() const { return mFlags & CLEAR_WORKSPACE; }

        u32 getMax() const { return LIGHT_TEX_MAX; }

    private:
        u8 mFlags; // at 0x4
        u16 mTexNum; // at 0x6
        LightTexture **mppLightTextures; // at 0x8
        LightManager *mpLightManager; // at 0xC
        u32 mDrawFlags; // at 0x10
        u16 mLightObjNum; // at 0x14
        LightObj **mppLightObjs; // at 0x18

        static const int LIGHT_TEX_MAX = 32;
        static const int LIGHT_OBJ_MAX = 32;
    };
}

#endif