#include <Pack/RPUtility.h>

#include <nw4r/math.h>

#include <revolution/GX.h>

nw4r::math::MTX34 RPUtlShadowDrawer::sGlobalMtx;

void RPUtlShadowDrawer::initMtx() const {
    sGlobalMtx = mLocalMtx;
}

/**
 * @brief Draws basic shadows.
 */
void RPUtlShadowDrawer::drawShadow() {
    nw4r::math::MTX34 ab;

    nw4r::math::MTX34Mult(&ab, &sGlobalMtx, &mLocalMtx);
    GXLoadPosMtxImm(ab, GX_PNMTX0);
    GXLoadNrmMtxImm(ab, GX_PNMTX0);
    GXSetChanMatColor(GX_COLOR0A0, mColor);
    GXDrawCylinder(16);
}
