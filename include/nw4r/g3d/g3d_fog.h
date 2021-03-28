#ifndef NW4R_G3D_FOG_H
#define NW4R_G3D_FOG_H
#include "types_nw4r.h"
#include "g3d_rescommon.h"
#include "math_types.h"
#include "ut_Color.h"

namespace nw4r
{
    namespace g3d
    {
        struct FogData
        {
            u32 INT_0x0;
            f32 FLOATS_0x4[4];
            ut::Color mColor;
            u8 BYTE_0x18;
            u8 BYTE_0x19;
            u16 mAdjTable[11]; // at 0x1A
        };

        struct Fog
        {			
            ResCommon<FogData> mFogData;
            
            inline Fog(void * vptr) : mFogData(vptr) {}

            Fog(FogData *);
            void Init();
            void * CopyTo(void *) const;
            void SetFogRangeAdjParam(u16, u16, const math::MTX44&);
            void SetGP() const;
        };
    }
}

#endif