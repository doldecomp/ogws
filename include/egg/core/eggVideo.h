#ifndef EGG_CORE_VIDEO_H
#define EGG_CORE_VIDEO_H
#include <egg/types_egg.h>

#include <egg/core/eggBitFlag.h>

#include <revolution/GX.h>
#include <revolution/VI.h>

namespace EGG {

class Video {
public:
    explicit Video(GXRenderModeObj* pRenderMode)
        : mRenderMode(NULL), mConfiguredTime(0) {

        initialize(pRenderMode);
    }

    void initialize(GXRenderModeObj* pRenderMode);
    GXRenderModeObj* configure(GXRenderModeObj* pRenderMode);

    static u32 getTickPerVRetrace(u32 tvFormat);
    static u32 getTickPerVRetrace();

    static const GXRenderModeObj* getStandardRenderModeObj();

    bool isBlack() {
        return mFlags.offBit(BIT_VIDEO_SHOW);
    }
    void changeBlack() {
        VISetBlack(mFlags.offBit(BIT_VIDEO_SHOW));
        mFlags.toggleBit(BIT_VIDEO_SHOW);
    }

    GXRenderModeObj* getRenderModeObj() {
        return mRenderMode;
    }

    u16 getFbWidth() {
        return mRenderMode->fbWidth;
    }
    u16 getEfbHeight() {
        return mRenderMode->efbHeight;
    }

private:
    enum {
        BIT_VIDEO_SHOW,
    };

private:
    GXRenderModeObj* mRenderMode; // at 0x0
    TBitFlag<u8> mFlags;          // at 0x4
    s32 mConfiguredTime;          // at 0x8
};

} // namespace EGG

#endif
