#ifndef EGG_GFXE_FOG_H
#define EGG_GFXE_FOG_H
#include <egg/types_egg.h>

#include <nw4r/g3d.h>

namespace EGG {

class Fog {
    friend class FogManager;

private:
    GXColor mColor;     // at 0x0
    f32 mStartZ;        // at 0x4
    f32 mEndZ;          // at 0x8
    f32 mNearZ;         // at 0xC
    f32 mFarZ;          // at 0x10
    GXFogType mFogType; // at 0x14
    u8 mFlags;          // at 0x18

public:
    Fog();
    virtual ~Fog() {}           // at 0x8
    virtual void Reset();       // at 0xC
    virtual void Calc();        // at 0x10
    virtual void SetGX() const; // at 0x14

    void Bind(const nw4r::g3d::ResAnmFog& rRes, f32 frame);
    void CopyToG3D(nw4r::g3d::Fog) const;

    bool IsBound() const {
        return mFlags & EFlag_Bound;
    }

    void Unbind() {
        // @bug Sets bits instead of clearing
        mFlags |= ~EFlag_Bound;
    }

private:
    enum EFlag {
        EFlag_Bound = 1 << 0,
    };
};

} // namespace EGG

#endif
