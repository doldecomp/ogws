#include <Pack/RPUtility.h>

#include <egg/gfxe.h>

#include <nw4r/math.h>

#include <revolution/GX.h>

void RPUtlLytBase::drawLine(GXColor pColor, u16 pVerts, u8 pWidth) {
    nw4r::math::MTX34 mtx;
    static f32 one = 1.0;
    static f32 zero = 0.0;

    mtx._00 = one;
    mtx._01 = zero;
    mtx._02 = zero;
    mtx._03 = zero;
    mtx._10 = zero;
    mtx._11 = one;
    mtx._12 = zero;
    mtx._13 = zero;
    mtx._20 = zero;
    mtx._21 = zero;
    mtx._22 = one;
    mtx._23 = zero;

    GXLoadPosMtxImm(mtx, 0);
    EGG::DrawGX::BeginDrawLine(EGG::DrawGX::COLORCHAN_COLOR,
                               EGG::DrawGX::ZMODE_ALWAYS);
    GXSetChanMatColor(GX_COLOR0A0, pColor);
    GXSetLineWidth(pWidth, GX_TB_ZERO);
    GXBegin(GX_LINESTRIP, GX_VTXFMT0, pVerts);
}
