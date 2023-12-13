#include "eggFog.h"
#include "eggDrawGX.h"
#include "g3d_resanmfog.h"
#include "g3d_anmfog.h"

namespace EGG
{
    Fog::Fog()
    {
    }

    void Fog::Reset()
    {
        mFlags = 0;
        Unbind();

        mColor.a = 0xFF;
        mColor.b = 0xFF;
        mColor.g = 0xFF;
        mColor.r = 0xFF;

        mFarZ = 0.0f;
        mNearZ = 0.0f;
        mEndZ = 0.0f;
        mStartZ = 0.0f;

        mFogType = GX_FOG_PERSP_LIN;
    }

    void Fog::Calc()
    {
    }

    void Fog::SetGX() const
    {
        if (mFlags & BOUND)
        {
            GXSetFog(mFogType, mColor, mStartZ, mEndZ, mNearZ, mFarZ);
        }
        else
        {
            GXSetFog(GX_FOG_NONE, DrawGX::scColorWhite, 0.0f, 1.0f, 0.0f, 1.0f);
        }

        GXSetFogRangeAdj(0, 0, NULL);
    }

    void Fog::CopyToG3D(nw4r::g3d::Fog fog) const
    {
        fog.SetFogType((mFlags & BOUND) ? mFogType : GX_FOG_NONE);
        fog.SetZ(mStartZ, mEndZ);
        fog.SetFogColor(mColor);
    }

    void Fog::Bind(const nw4r::g3d::ResAnmFog& res, f32 f1)
    {
        if (res.IsValid())
        {
            nw4r::g3d::FogAnmResult result;
            res.GetAnmResult(&result, f1);

            mFogType = result.mFogType;
            mStartZ = result.mStartZ;
            mEndZ = result.mEndZ;
            mColor = result.mColor;

            mFlags |= BOUND;
        }
        else
        {
            mFogType = GX_FOG_NONE;
            Unbind();
        }
    }

    Fog::~Fog()
    {
    }
}