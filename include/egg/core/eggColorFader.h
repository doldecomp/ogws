#ifndef EGG_CORE_COLOR_FADER_H
#define EGG_CORE_COLOR_FADER_H
#include <egg/types_egg.h>

#include <egg/core/eggBitFlag.h>
#include <egg/core/eggFader.h>

#include <nw4r/ut.h>

namespace EGG {

class ColorFader : public Fader {
public:
    ColorFader(f32 x, f32 y, f32 width, f32 height,
               nw4r::ut::Color color = 0x00000000,
               EStatus status = STATUS_PREPARE_IN);

    virtual ~ColorFader() {} // at 0x20

    virtual void setStatus(EStatus status); // at 0x8
    virtual EStatus getStatus() const {
        return mStatus;
    } // at 0xC

    virtual bool fadeIn();  // at 0x10
    virtual bool fadeOut(); // at 0x14

    virtual bool calc(); // at 0x18
    virtual void draw(); // at 0x1C

    void setFrame(u16 frame);
    void setColor(nw4r::ut::Color color);

private:
    enum FlagBit { BIT_FINISH_AFTER_IN, BIT_FINISH_AFTER_OUT, BIT_2 };

    static const u16 DEFAULT_FRAME = 20;

private:
    EStatus mStatus;     // at 0x4
    TBitFlag<u8> mFlags; // at 0x8
    u16 mFadeFrame;      // at 0xA
    u16 mFrame;          // at 0xC
    u8 UNK_0xE[0x10 - 0xE];
    nw4r::ut::Color mColor; // at 0x10
    nw4r::ut::Rect mSpace;  // at 0x14
};

} // namespace EGG

#endif
