#ifndef EGG_GFX_LIGHT_OBJECT_H
#define EGG_GFX_LIGHT_OBJECT_H
#include "eggIBinary.h"
#include "eggVector.h"
#include <revolution/GX.h>

namespace EGG
{
    class LightObj : IBinary<LightObj>
    {
    public:
        struct Bin : IBinary::Bin
        {
            u8 spotFn; // at 0x10
            u8 distAttnFn; // at 0x11
            u8 BYTE_0x12;
            u8 BYTE_0x13;
            u16 ambLightIdx; // at 0x14
            u16 flags; // at 0x16
            Vector3f pos; // at 0x18
            Vector3f target; // at 0x24
            f32 intensity; // at 0x30
            GXColor color; // at 0x34
            GXColor COLOR_0x38;
            f32 spotArg; // at 0x3C
            f32 distAttnArg0; // at 0x40
            f32 distAttnArg1; // at 0x44
            char UNK_0x48[0x8];
        };

    public:
        LightObj();
        virtual void SetBinaryInner(const Bin&); // at 0x8
        virtual void GetBinaryInner(Bin *) const; // at 0xC
        virtual const char * GetBinaryType() const; // 0x10
        virtual u32 GetBinarySize() const; // 0x14
        virtual u8 GetVersion() const; // 0x18

        // TO-DO: Document flags and remove accessor
        u16 getFlags() { return mFlags; }

    private:
        u16 mAmbLightIdx; // at 0x4
        Vector3f mTarget; // at 0x8
        Vector3f mPos; // at 0x14
        Vector3f mDirection; // at 0x20
        GXColor mColor; // at 0x2C
        f32 mIntensity; // at 0x30
        UNKWORD WORD_0x34;
        f32 FLOAT_0x38;
        GXColor COLOR_0x3C;
        UNKWORD WORD_0x40;
        f32 mSpotArg; // at 0x44
        f32 mDistAttn_Arg0; // at 0x48
        f32 mDistAttn_Arg1; // at 0x4C
        f32 mAttnA_Arg0; // at 0x50
        f32 mAttnA_Arg1; // at 0x54
        f32 mAttnA_Arg2; // at 0x58
        f32 mAttnK_Arg0; // at 0x5C
        f32 mAttnK_Arg1; // at 0x60
        f32 mAttnK_Arg2; // at 0x64
        GXSpotFn mSpotFn; // at 0x68
        GXDistAttnFn mDistAttnFn; // at 0x6C
        f32 FLOAT_0x70;
        u16 SHORT_0x74;
        u16 mFlags; // at 0x76
    };
}

#endif