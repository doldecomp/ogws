#include <Pack/RPUtility.h>

#include <egg/gfxe.h>

#include <nw4r/math.h>

#include <revolution/GX.h>

void RPUtlLytBase::beginDrawLine(GXColor color, u16 verts, u8 width) {
    nw4r::math::MTX34 ident;

    ident._00 = 1.0f;
    ident._01 = 0.0f;
    ident._02 = 0.0f;
    ident._03 = 0.0f;
    ident._10 = 0.0f;
    ident._11 = 1.0f;
    ident._12 = 0.0f;
    ident._13 = 0.0f;
    ident._20 = 0.0f;
    ident._21 = 0.0f;
    ident._22 = 1.0f;
    ident._23 = 0.0f;

    GXLoadPosMtxImm(ident, GX_PNMTX0);
    EGG::DrawGX::BeginDrawLine(EGG::DrawGX::COLORCHAN_COLOR,
                               EGG::DrawGX::ZMODE_ALWAYS);
    GXSetChanMatColor(GX_COLOR0A0, color);
    GXSetLineWidth(width, 0);
    GXBegin(GX_LINESTRIP, GX_VTXFMT0, verts);
}
