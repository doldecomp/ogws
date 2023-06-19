#ifndef EGG_CORE_COLOR_FADER_H
#define EGG_CORE_COLOR_FADER_H
#include "types_egg.h"
#include "ut_Color.h"
#include "eggBitFlag.h"
#include "eggFader.h"

namespace EGG
{
    struct ColorFader : Fader
    {
        ColorFader(f32, f32, f32, f32, nw4r::ut::Color, EStatus);
        void setFrame(u16);
        void setColor(nw4r::ut::Color);
        virtual void setStatus(EStatus); // at 0x8
        virtual EStatus getStatus() const; // at 0xC
        virtual bool fadeIn(); // at 0x10
        virtual bool fadeOut(); // at 0x14
        virtual bool calc(); // at 0x18
        virtual void draw();  // at 0x1C
        virtual ~ColorFader(); // at 0x20

        // Unofficial symbols
        f32 getWidth() const { return mEndX - mStartX; }
        f32 getHeight() const { return mEndY - mStartY; }

        EStatus mStatus; // at 0x4
        TBitFlag<u8> mFlags; // at 0x8
        u16 mFrame; // Fade length (in frames); at 0xA
        u16 mFadeTimer; // at 0xC; Length of current fade
        u16 SHORT_0xE; // at 0xE
        nw4r::ut::Color mColor; // at 0x10
        f32 mStartX; // at 0x14
        f32 mStartY; // at 0x18
        f32 mEndX; // at 0x1C
        f32 mEndY; // at 0x20
    };
}

#endif