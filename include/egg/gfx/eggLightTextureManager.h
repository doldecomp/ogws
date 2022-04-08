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
            char UNK_0x4[0x20 - 0x4];
        };

    public:
        LightTextureManager(LightManager *);
        virtual void SetBinaryInner(const Bin&); // at 0x8
        virtual void GetBinaryInner(Bin *) const; // at 0xC
        virtual const char * GetBinaryType() const; // at 0x10
        virtual u8 GetVersion() const = 0; // at 0x18

        void Draw(LightManager *,
            eggScreen::EfbData *, f32, f32, f32, f32);

    private:
    };
}

#endif