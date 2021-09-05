#include "eggFog.h"
#include "eggDrawGX.h"
#include "g3d_resanmfog.h"
#include "g3d_anmfog.h"

namespace EGG
{
    Fog::Fog()
    {

    }

    void Fog::reset()
    {
        mFlags = 0;
        resetFlags();

        mColor.a = 0xFF;
        mColor.b = 0xFF;
        mColor.g = 0xFF;
        mColor.r = 0xFF;

        mFarZ = 0.0f;
        mNearZ = 0.0f;
        mEndZ = 0.0f;
        mStartZ = 0.0f;

        mFogType = GX_FOG_TYPE_2;
    }

    void Fog::VF_0x10()
    {

    }

    void Fog::setGX() const
    {
        if (mFlags & IS_INITIALIZED)
        {
            GXSetFog(mFogType, mColor, mStartZ, mEndZ, mNearZ, mFarZ);
        }
        else
        {
            GXSetFog(GX_FOG_TYPE_0, DrawGX::sColorWhite, 0.0f, 1.0f, 0.0f, 1.0f);
        }

        GXSetFogRangeAdj(0, 0, NULL);
    }

    void Fog::setG3D(nw4r::g3d::Fog& fog) const
    {
        fog.SetFogType((mFlags & IS_INITIALIZED) ? mFogType : GX_FOG_TYPE_0);
        fog.SetZ(mStartZ, mEndZ);
        fog.SetFogColor(mColor);
    }

    void Fog::initialize(const nw4r::g3d::ResAnmFog& res, f32 f1)
    {
        if (res.IsValid())
        {
            nw4r::g3d::FogAnmResult result;
            res.GetAnmResult(&result, f1);

            mFogType = result.mFogType;
            mStartZ = result.mStartZ;
            mEndZ = result.mEndZ;
            mColor = result.mColor.mChannels;

            mFlags |= IS_INITIALIZED;
        }
        else
        {
            mFogType = GX_FOG_TYPE_0;
            resetFlags();
        }
    }

    Fog::~Fog()
    {

    }
}