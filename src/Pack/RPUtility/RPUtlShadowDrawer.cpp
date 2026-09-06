#include <Pack/RPUtility.h>

#include <revolution/GX.h>

nw4r::math::MTX34 RPUtlShadowDrawer::mMtx;

void RPUtlShadowDrawer::drawShadow(RPUtlSimpleShadow* simpShad) {
    nw4r::math::MTX34 ab;

    PSMTXConcat(mMtx, simpShad->mMtx, ab);
    GXLoadPosMtxImm(ab, 0);
    GXLoadNrmMtxImm(ab, 0);
    GXSetChanMatColor(GX_COLOR0A0, simpShad->mColor);
    GXDrawCylinder(0x10u);
}
