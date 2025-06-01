#ifndef EGG_CORE_DISPLAY_H
#define EGG_CORE_DISPLAY_H
#include <egg/types_egg.h>

#include <egg/core/eggBitFlag.h>
#include <egg/core/eggSystem.h>
#include <egg/core/eggVideo.h>

#include <nw4r/ut.h>

namespace EGG {

class Display {
protected:
    TBitFlag<u8> mEfbFlags; // at 0x0

public:
    Display(u8 frameRate);

    virtual void beginFrame();  // at 0x8
    virtual void beginRender(); // at 0xC
    virtual void endRender();   // at 0x10
    virtual void endFrame();    // at 0x14

    virtual u32 getTickPerFrame(); // at 0x18

    void copyEFBtoXFB();

    void setBlack(bool enable) {
        if (!BaseSystem::getVideo()->isBlack() &&
            !mXfbFlags.onBit(BIT_XFB_CHANGE_BLACK)) {

            mXfbFlags.changeBit(BIT_XFB_CHANGE_BLACK, !enable);
        }
    }

    nw4r::ut::Color getClearColor() const {
        return mClearColor;
    }
    void setClearColor(nw4r::ut::Color color) {
        mClearColor = color;
    }

protected:
    enum EfbFlagBit {
        BIT_EFB_COPY_CLEAR,
    };
    enum XfbFlagBit {
        BIT_XFB_CHANGE_BLACK,
    };

protected:
    void calcFrequency();

protected:
    u8 mFrameRate;               // at 0x8
    TBitFlag<u8> mXfbFlags;      // at 0x9
    u32 mRetraceCount;           // at 0xC
    u32 mFrameCount;             // at 0x10
    nw4r::ut::Color mClearColor; // at 0x14
    u32 mClearZ;                 // at 0x20
    s32 mPrevFrameTick;          // at 0x1C
    s32 mFrameCostTick;          // at 0x20
    f32 mFrequency;              // at 0x24

private:
    void syncVRetrace(u8 frameRate);
};

} // namespace EGG

#endif
