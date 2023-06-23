#include "g3d_fog.h"
#include <revolution/GX.h>

namespace nw4r
{
    namespace g3d
    {
        Fog::Fog(FogData* pFogData) : mFogData(pFogData) {}

        void Fog::Init()
        {
            if (mFogData.IsValid())
            {
                FogData& rFogData = mFogData.ref();
                
                rFogData.mFogType = GX_FOG_NONE;

                rFogData.mStartZ = 0.0f;
                rFogData.mEndZ = 0.0f;
                rFogData.mNear = 0.0f;
                rFogData.mFar = 0.0f;

                rFogData.mColor.a = 0;
                rFogData.mColor.b = 0;
                rFogData.mColor.g = 0;
                rFogData.mColor.r = 0;
                
                rFogData.mFogRangeAdjEnable = 0;
                rFogData.BYTE_0x19 = 0;

                rFogData.mAdjTableWidth = 0;
                for (int i = 0; i < 10; i++)
                {
                    rFogData.mAdjTable.r[i] = 0;
                }
            }
        }

        void * Fog::CopyTo(void *pFog) const
        {
            if (pFog)
            {
                register FogData& src = mFogData.ref();
                register void * dest = pFog;

                if (mFogData.IsValid())
                {
                    asm
                    (
                        lfd f0, 0(src)
                        stfd f0, 0(dest)

                        lfd f0, 8(src)
                        stfd f0, 8(dest)

                        lfd f0, 16(src)
                        stfd f0, 16(dest)

                        lfd f0, 24(src)
                        stfd f0, 24(dest)

                        lfd f0, 32(src)
                        stfd f0, 32(dest)

                        lfd f0, 40(src)
                        stfd f0, 40(dest)
                    );

                    return pFog;
                }
            }

            return NULL;
        }

        void Fog::SetFogRangeAdjParam(u16 param1, u16 width, const math::MTX44& rMtx)
        {
            FogData& rFogData = mFogData.ref();

            if (mFogData.IsValid())
            {
                rFogData.mAdjTableWidth = width;
                GXInitFogAdjTable(&rFogData.mAdjTable, param1, rMtx);
            }
        }

        void Fog::SetGP() const
        {
            FogData& rFogData = mFogData.ref();
            
            if (mFogData.IsValid())
            {
                if (rFogData.mFogType != GX_FOG_NONE)
                {
                    GXSetFogRangeAdj(rFogData.mFogRangeAdjEnable, rFogData.mAdjTableWidth, &rFogData.mAdjTable);
                }

                GXSetFog(rFogData.mFogType, rFogData.mColor, rFogData.mStartZ, rFogData.mEndZ,
                    rFogData.mNear, rFogData.mFar);
            }
        }
    }
}