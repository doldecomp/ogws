#ifndef EGG_GFXE_SCREEN_EFFECT_BASE_H
#define EGG_GFXE_SCREEN_EFFECT_BASE_H
#include <egg/types_egg.h>

#include <egg/gfxe/eggScreen.h>
#include <egg/prim.h>

#include <revolution/GX.h>

namespace EGG {

class ScreenEffectBase {
public:
    enum BufferType {
        cBufferType_None = -1,

        cBufferType_Hide_1_16,
        cBufferType_1,
        cBufferType_2,
        cBufferType_3,
        cBufferType_Max
    };

    enum WorkBuffer {
        cWorkBuffer_None = -1,

        cWorkBuffer_0,
        cWorkBuffer_1,
    };

    struct EffectBuffer {
        TextureBuffer* mpTexBuffer;          // at 0x0
        const ScreenEffectBase* mpAllocBase; // at 0x4
        u32 unk8;                            // at 0x8
    };

private:
    u8 mFlags;      // at 0x0
    Screen mScreen; // at 0x4

public:
    static void Clean();

    ScreenEffectBase();
    virtual ~ScreenEffectBase() {} // at 0x8

    Screen& GetScreen() {
        return mScreen;
    }
    const Screen& GetScreen() const {
        return mScreen;
    }

    bool isEnable() const {
        return mFlags & cFlag_Enable;
    }
    void setEnable(bool enable) {
        if (enable) {
            mFlags |= cFlag_Enable;
        } else {
            mFlags &= ~cFlag_Enable;
        }
    }

    void setScreen(const Screen& rScreen);

    TextureBuffer* captureEfb(BufferType type, bool alpha) const;
    bool releaseEfb(BufferType type) const;

    void pushWorkBuffer(WorkBuffer buffer) const;
    void popWorkBuffer(bool hide) const;

    const f32* shiftWorkSpaceViewportGX() const;

protected:
    static void setBuffer(BufferType type, TextureBuffer* pBuffer) {
#line 163
        EGG_ASSERT(type < cBufferType_Max);
        spBufferSet[type].mpTexBuffer = pBuffer;
    }

    static void clearBuffer(BufferType type) {
        setBuffer(type, NULL);
        spBufferSet[type].mpAllocBase = NULL;
        spBufferSet[type].unk8 = 0;
    }

    static TextureBuffer* getBuffer(BufferType type) {
        return spBufferSet[type].mpTexBuffer;
    }

    static void setGlbFlag0(bool enable) {
        if (enable) {
            sFlag |= cGlobalFlag_0;

        } else {
            sFlag &= ~cGlobalFlag_0;
        }
    }
    static bool isGlbFlag0() {
        return sFlag & cGlobalFlag_0;
    }

    static void setGlbFlag1(bool enable) {
        if (enable) {
            sFlag |= cGlobalFlag_1;

        } else {
            sFlag &= ~cGlobalFlag_1;
        }
    }
    static bool isGlbFlag1() {
        return sFlag & cGlobalFlag_1;
    }

private:
    enum {
        cFlag_Enable = 1 << 0,
    };

    enum {
        cGlobalFlag_0 = 1 << 0,
        cGlobalFlag_1 = 1 << 1,
    };

    static const int EFFECT_WIDTH = 640;
    static const int EFFECT_HEIGHT = 528;

private:
    static EffectBuffer spBufferSet[cBufferType_Max];

    static f32 sWorkSpaceV[GX_VIEWPORT_SZ];
    static f32 sWorkSpaceHideV[GX_VIEWPORT_SZ];

    static u16 sCaptureFlag;
    static u32 sFlag;

    static u32 D_804BEC58;
    static u32 sPushCount;

    static WorkBuffer sWorkBuffer;
};

} // namespace EGG

#endif
