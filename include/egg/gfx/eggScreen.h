#ifndef EGG_GFX_SCREEN_H
#define EGG_GFX_SCREEN_H
#include <egg/types_egg.h>

#include <egg/gfx/eggFrustum.h>

#include <nw4r/g3d.h>

#include <revolution/GX.h>

namespace EGG {

class Screen : public Frustum {
public:
    typedef void (*ChangeTVModeFunc)(void* pArg);

    enum TVMode { TV_MODE_STD, TV_MODE_WIDE, TV_MODE_MAX };

    enum FillBufferFlag {
        FILLBUFFER_COLOR = 1 << 0,
        FILLBUFFER_ALPHA = 1 << 1,
        FILLBUFFER_TEXTURE = 1 << 2,
    };

    struct DataEfb {
        struct Viewport {
            f32 x;      // at 0x0
            f32 y;      // at 0x4
            f32 width;  // at 0x8
            f32 height; // at 0xC
            f32 near;   // at 0x10
            f32 far;    // at 0x14
        } vp;

        s32 ox; // at 0x18
        s32 oy; // at 0x1C
    };

public:
    static void Initialize(const u16* maxX, const u16* maxY,
                           Screen* pUserRoot = NULL);

    Screen();
    Screen(f32 x, f32 y, f32 width, f32 height, const Screen* pParent,
           CanvasMode canvasMode);
    Screen(const Screen& rOther);

    virtual ~Screen() {}                                    // at 0x8
    virtual void SetProjectionGX() const;                   // at 0xC
    virtual void CopyToG3D(nw4r::g3d::Camera camera) const; // at 0x10

    void CopyFromAnother(const Screen& rOther);

    void GetPosSizeInEfb() const;
    const DataEfb& GetDataEfb() const;
    bool IsChangeEfb() const;

    void CalcMatrixForDrawQuad(nw4r::math::MTX34* pMtx, f32 x, f32 y, f32 width,
                               f32 height) const;
    void FillBufferGX(u32 flags, GXColor color, u32 arg2) const;
    void GetGlobalPos(f32* pX, f32* pY) const;

    const Screen* GetParent() const {
        return mParent;
    }
    void SetParent(const Screen* pParent) {
        mFlags |= FLAG_DIRTY;

        if (spRoot == this) {
            mParent = NULL;
        } else {
            mParent = pParent != NULL ? pParent : spRoot;
        }
    }

    void SetProjectionAbsolute() const {
        mFlags |= FLAG_PROJ_ABSOLUTE;
    }

    const nw4r::math::VEC2& GetPosition() const {
        return mPosition;
    }
    void SetPosition(const nw4r::math::VEC2& rPos) {
        mPosition = rPos;
    }

    static void SetTVMode(TVMode tvMode);
    static void SetTVModeDefault();

    static u16 GetSizeXMax() {
        return sTVModeWidths[sTVMode];
    }
    static u16 GetSizeYMax() {
        return sTVModeHeights[sTVMode];
    }

private:
    enum {
        FLAG_ALIGN_EFB_POS = 1 << 1,
        FLAG_ALIGN_EFB_SIZE = 1 << 2,
        FLAG_VPSIZE_ABSOLUTE = 1 << 3,
        FLAG_FORCE_STD_ASPECT = 1 << 5,
        FLAG_PROJ_ABSOLUTE = 1 << 7,
    };

    struct TVModeRatio {
        TVModeRatio() {}

        f32 widthRatio;  // at 0x0
        f32 heightRatio; // at 0x4
    };

private:
    void Configure();

    void SetViewGX() const;
    void SetViewG3D(nw4r::g3d::Camera camera) const;

    static void CalcRatio();

private:
    const Screen* mParent;      // at 0x3C
    nw4r::math::VEC2 mPosition; // at 0x40
    mutable DataEfb mDataEfb;   // at 0x48

    static TVMode sTVMode;
    static TVModeRatio sTVModeRatios[Screen::TV_MODE_MAX];
    static u16 sTVModeWidths[TV_MODE_MAX];
    static u16 sTVModeHeights[TV_MODE_MAX];

    static Screen* spRoot;

    static ChangeTVModeFunc sChangeTVModeFunc;
    static void* spChangeTVModeFuncInfo;

    static nw4r::math::VEC2 sCanvasScale;
    static nw4r::math::VEC2 sCanvasOffset;
};

} // namespace EGG

#endif
