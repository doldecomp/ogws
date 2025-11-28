#include <egg/gfxe.h>

#include <nw4r/g3d.h>

#include <revolution/GX.h>

namespace EGG {

Fog::Fog() {}

void Fog::Reset() {
    mFlags = 0;
    Unbind();

    mColor.r = mColor.g = mColor.b = mColor.a = 255;

    mNearZ = mFarZ = 0.0f;
    mStartZ = mEndZ = 0.0f;

    mFogType = GX_FOG_PERSP_LIN;
}

void Fog::Calc() {}

void Fog::SetGX() const {
    if (IsBound()) {
        GXSetFog(mFogType, mColor, mStartZ, mEndZ, mNearZ, mFarZ);
    } else {
        GXSetFog(GX_FOG_NONE, DrawGX::WHITE, 0.0f, 1.0f, 0.0f, 1.0f);
    }

    GXSetFogRangeAdj(GX_FALSE, 0, NULL);
}

void Fog::CopyToG3D(nw4r::g3d::Fog fog) const {
    fog.SetFogType(IsBound() ? mFogType : GX_FOG_NONE);
    fog.SetZ(mStartZ, mEndZ);
    fog.SetFogColor(mColor);
}

void Fog::Bind(const nw4r::g3d::ResAnmFog& rRes, f32 frame) {
    if (rRes.IsValid()) {
        nw4r::g3d::FogAnmResult result;
        rRes.GetAnmResult(&result, frame);

        mFogType = result.type;
        mStartZ = result.startz;
        mEndZ = result.endz;
        mColor = result.color;

        mFlags |= EFlag_Bound;
    } else {
        mFogType = GX_FOG_NONE;
        Unbind();
    }
}

} // namespace EGG
