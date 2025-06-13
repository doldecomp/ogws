#ifndef EGG_CORE_ASYNC_DISPLAY_H
#define EGG_CORE_ASYNC_DISPLAY_H
#include <egg/types_egg.h>

#include <egg/core/eggDisplay.h>

#include <nw4r/ut.h>

#include <revolution/OS.h>

namespace EGG {

class AsyncDisplay : public Display {
public:
    explicit AsyncDisplay(u8 frameRate);

    virtual void beginFrame();  // at 0x8
    virtual void beginRender(); // at 0xC
    virtual void endRender();   // at 0x10

    virtual u32 getTickPerFrame(); // at 0x18

    void postVRetrace();
    void clearEFB();

private:
    enum SyncMode {
        SYNC_MODE_NONE,
        SYNC_MODE_NTSC,
    };

private:
    void calcS();
    void syncTick();

    void clearEFB(u16 fbWidth, u16 fbHeight, u16 x, u16 y, u16 width,
                  u16 height, nw4r::ut::Color color);

private:
    OSAlarm mSyncAlarm;       // at 0x28
    OSThreadQueue mSyncQueue; // at 0x58
    SyncMode mSyncMode;       // at 0x60

    f32 mTimeScale;          // at 0x64
    u32 mPrevTickCount;      // at 0x68
    u32 mTickCount;          // at 0x6C
    u8 mFrameRateNTSC;       // at 0x70
    u32 mTickPerRetraceNTSC; // at 0x74
    u32 mTickPerRetrace;     // at 0x78
    s32 mTickCostTick;       // at 0x7C
    s32 mPrevTickTick;       // at 0x80
};

} // namespace EGG

#endif
