#ifndef NW4R_EF_DRAW_INFO_H
#define NW4R_EF_DRAW_INFO_H
#include <nw4r/types_nw4r.h>

#include <nw4r/math.h>

#include <revolution/GX.h>

namespace nw4r {
namespace ef {

class DrawInfo {
private:
    math::MTX34 mViewMtx;    // at 0x0
    math::MTX34 mProjMtx;    // at 0x30
    bool mLightEnable;       // at 0x60
    GXLightID mLightMask;    // at 0x64
    bool mIsSpotLight;       // at 0x6C
    GXFogType mFogType;      // at 0x70
    f32 mFogStartz;          // at 0x74
    f32 mFogEndz;            // at 0x78
    f32 mFogNearz;           // at 0x7C
    f32 mFogFarz;            // at 0x80
    GXColor mFogColor;       // at 0x84
    f32 mZOffset;            // at 0x88
    math::VEC3 mZOffsetOrig; // at 0x8C
    GXColor mChanMatColor;   // at 0x98
    GXColor mChanAmbColor;   // at 0x9C

public:
    DrawInfo()
        : mLightEnable(false),
          mLightMask(GX_LIGHT_NULL),
          mIsSpotLight(true),
          mFogType(GX_FOG_NONE),
          mFogStartz(0.0f),
          mFogEndz(1.0f),
          mFogNearz(0.0f),
          mFogFarz(1.0f),
          mZOffset(0.0f) {

        mZOffsetOrig.x = 0.0f;
        mZOffsetOrig.y = 0.0f;
        mZOffsetOrig.z = 0.0f;

        mChanMatColor.r = mChanMatColor.g = mChanMatColor.b = mChanMatColor.a =
            255;

        mChanAmbColor.r = mChanAmbColor.g = mChanAmbColor.b = 0;
        mChanAmbColor.a = 255;
    }

    const math::MTX34* GetViewMtx() const {
        return &mViewMtx;
    }
    void SetViewMtx(const math::MTX34& rMtx) {
        mViewMtx = rMtx;
    }

    const math::MTX34* GetProjMtx() const {
        return &mProjMtx;
    }
    void SetProjMtx(const math::MTX34& rMtx) {
        mProjMtx = rMtx;
    }

    bool IsLightEnable() const {
        return mLightEnable;
    }

    GXLightID GetLightMask() const {
        return mLightMask;
    }

    bool IsSpotLight() const {
        return mIsSpotLight;
    }

    void GetFog(GXFogType* pType, f32* pStartZ, f32* pEndZ, f32* pNearZ,
                f32* pFarZ, GXColor* pColor) const {

        *pType = mFogType;
        *pStartZ = mFogStartz;
        *pEndZ = mFogEndz;
        *pNearZ = mFogNearz;
        *pFarZ = mFogFarz;
        *pColor = mFogColor;
    }

    void GetZOffset(f32& rOffset, math::VEC3& rPos) const {
        rOffset = mZOffset;
        rPos = mZOffsetOrig;
    }
    void SetZOffset(f32 offset, const math::VEC3& rPos) {
        mZOffset = offset;
        mZOffsetOrig = rPos;
    }

    const GXColor& GetChanMatColor() const {
        return mChanMatColor;
    }
    const GXColor& GetChanAmbColor() const {
        return mChanAmbColor;
    }
};

} // namespace ef
} // namespace nw4r

#endif
