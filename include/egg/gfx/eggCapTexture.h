#ifndef EGG_GFX_CAP_TEXTURE_H
#define EGG_GFX_CAP_TEXTURE_H
#include "types_egg.h"
#include "eggCpuTexture.h"
#include <GX/GXTexture.h>

namespace EGG
{
    class CapTexture : public CpuTexture
    {
    public:
        CapTexture() {}
        CapTexture(u16 w, u16 h, GXTexFmt fmt) : CpuTexture(w, h, fmt) {}

        virtual ~CapTexture() {} // at 0x8
        virtual void configure(); // at 0xC
        virtual void load(GXTexMapID) const; // at 0x14

        void capture(u16, u16, bool, int);

        void setColor(const GXColor& c) { COLOR_0x1C = c; }
        GXTexMapID getLoadMap() const { return mLoadMap; }

    private:
        GXTexMapID mLoadMap; // at 0x18
        GXColor COLOR_0x1C;
        UNKWORD WORD_0x20;
        u8 BYTES_0x24[0x2C - 0x24];
    };
}

#endif