#ifndef EGG_GFX_LIGHT_TEXTURE_H
#define EGG_GFX_LIGHT_TEXTURE_H
#include "types_egg.h"
#include "eggIBinary.h"
#include "eggScreen.h"
#include "eggCapTexture.h"

namespace EGG
{
    class LightTexture : public CapTexture, public IBinary<LightTexture>
    {
    public:
        struct Bin : IBinary::Bin
        {
        };

    public:
        static void initialize(u16, Heap *);
        static void initDrawSetting(u16, u16, u16, u16);
        static void getDrawSetting(u16 *, u16 *, u16 *, u16 *, u16);

        LightTexture(u16, const char *, LightTextureManager *);
        virtual void SetBinaryInner(const IBinary::Bin&); // at 0x8
        virtual void GetBinaryInner(IBinary::Bin *) const; // at 0xC
        virtual const char * GetBinaryType() const; // at 0x10
        virtual u8 GetVersion() const; // at 0x18
        
        void draw();
        void capture(const GXColor&, bool);

        const char * getName() const { return mName; }

    private:
        static const int MAX_NAME_LEN = 32;

        char UNK_0x2C[0x54 - 0x2C];
        char mName[MAX_NAME_LEN]; // at 0x54
        char UNK_0x74[0x84 - 0x74];
    };
}

#endif