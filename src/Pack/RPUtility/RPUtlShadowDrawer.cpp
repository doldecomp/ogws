#include <Pack/RPUtility.h>

#include <nw4r/math.h>

#include <revolution/GX.h>

nw4r::math::MTX34 RPUtlShadowDrawer::sCameraMtx;

//! NOTE: mLocalMtx may be an argument, though this requires
//! further analysis of RPGrpRenderer.
void RPUtlShadowDrawer::initMtx() const {
    sCameraMtx = mLocalMtx;
}

/**
 * @brief Draws basic shadows.
 */
void RPUtlShadowDrawer::drawShadow() {
    nw4r::math::MTX34 ab;

    nw4r::math::MTX34Mult(&ab, &sCameraMtx, &mLocalMtx);
    GXLoadPosMtxImm(ab, GX_PNMTX0);
    GXLoadNrmMtxImm(ab, GX_PNMTX0);
    GXSetChanMatColor(GX_COLOR0A0, mColor);
    GXDrawCylinder(16);
}
