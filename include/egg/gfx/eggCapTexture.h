#ifndef EGG_GFX_CAP_TEXTURE_H
#define EGG_GFX_CAP_TEXTURE_H
#include "types_egg.h"
#include "eggCpuTexture.h"
#include <revolution/GX.h>

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

        GXTexMapID getLoadMap() const { return mLoadMap; }
        
        void setClearColor(const GXColor& c) { mClearColor = c; }

    private:
        mutable GXTexMapID mLoadMap; // at 0x18
        GXColor mClearColor; // at 0x1C
        u32 mClearZ; // at 0x20
        u8 mCopyFilterArg1[7]; // at 0x24

        static const u8 scCopyFilterArg0[12][2];
        static u8 sCopyFilterArg1_0[7];
        static u8 sCopyFilterArg1_1[7];
    };
}

#endif
