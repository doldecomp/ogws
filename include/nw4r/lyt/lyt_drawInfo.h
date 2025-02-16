#ifndef NW4R_LYT_DRAW_INFO_H
#define NW4R_LYT_DRAW_INFO_H
#include <nw4r/types_nw4r.h>

#include <nw4r/math.h>
#include <nw4r/ut.h>

namespace nw4r {
namespace lyt {

class DrawInfo {
public:
    DrawInfo();
    virtual ~DrawInfo(); // at 0x8

    bool IsYAxisUp() const {
        return mViewRect.bottom - mViewRect.top < 0.0f;
    }

    const math::MTX34& GetViewMtx() const {
        return mViewMtx;
    }
    void SetViewMtx(const math::MTX34& rViewMtx) {
        mViewMtx = rViewMtx;
    }

    const ut::Rect& GetViewRect() const {
        return mViewRect;
    }
    void SetViewRect(const ut::Rect& rViewRect) {
        mViewRect = rViewRect;
    }

    const math::VEC2& GetLocationAdjustScale() const {
        return mLocationAdjustScale;
    }
    void SetLocationAdjustScale(const math::VEC2& rScale) {
        mLocationAdjustScale = rScale;
    }

    f32 GetGlobalAlpha() const {
        return mGlobalAlpha;
    }
    void SetGlobalAlpha(f32 alpha) {
        mGlobalAlpha = alpha;
    }

    bool IsMultipleViewMtxOnDraw() const {
        return mFlag.mulViewDraw;
    }

    bool IsInfluencedAlpha() const {
        return mFlag.influencedAlpha;
    }
    void SetInfluencedAlpha(bool influenced) {
        mFlag.influencedAlpha = influenced;
    }

    bool IsLocationAdjust() const {
        return mFlag.locationAdjust;
    }
    void SetLocationAdjust(bool adjust) {
        mFlag.locationAdjust = adjust;
    }

    bool IsInvisiblePaneCalculateMtx() const {
        return mFlag.invisiblePaneCalculateMtx;
    }
    void SetInvisiblePaneCalculateMtx(bool calc) {
        mFlag.invisiblePaneCalculateMtx = calc;
    }

    bool IsDebugDrawMode() const {
        return mFlag.debugDrawMode;
    }

protected:
    math::MTX34 mViewMtx;            // at 0x4
    ut::Rect mViewRect;              // at 0x34
    math::VEC2 mLocationAdjustScale; // at 0x44
    f32 mGlobalAlpha;                // at 0x4C

    struct {
        u8 mulViewDraw : 1;
        u8 influencedAlpha : 1;
        u8 locationAdjust : 1;
        u8 invisiblePaneCalculateMtx : 1;
        u8 debugDrawMode : 1;
    } mFlag; // at 0x50
};

} // namespace lyt
} // namespace nw4r

#endif
