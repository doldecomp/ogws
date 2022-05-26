#ifndef NW4R_G3D_RESMAT_H
#define NW4R_G3D_RESMAT_H
#include "types_nw4r.h"
#include "g3d_rescommon.h"
#include "math_types.h"

namespace nw4r
{
    namespace g3d
    {
        struct ResTexSrtData
        {
        };
        
        struct ResTexSrt
        {
            ResCommon<ResTexSrtData> mTexSrt; // at 0x0
            
            inline ResTexSrt(void * vptr) : mTexSrt(vptr) {}
            bool IsValid() const { return mTexSrt.IsValid(); }
        };     

        struct ResTexPlttInfoData
        {
            u32 mNumOffsets; // at 0x0

            struct InfoOffset
            {
                u32 mResOffset; // at 0x0
                u32 mTexOffset; // at 0x4
            } mOffsets[]; // at 0x4
        };

        struct ResTexPlttInfo
        {
            ResCommon<ResTexPlttInfoData> mInfo;

            inline ResTexPlttInfo(void * vptr) : mInfo(vptr) {}
        };

        struct ResMatData
        {
            char UNK_0x0[0x1A4];
            ResTexSrt mResTexSrt;
        };

        struct ResMat
        {
            ResCommon<ResMatData> mMat;

            inline ResMat(void * vptr) : mMat(vptr) {}
            bool IsValid() const { return mMat.IsValid(); }

            ResTexSrt GetResTexSrt() { return mMat.ref().mResTexSrt; }

            bool Bind(ResFile);
            UNKTYPE Release();
            UNKTYPE Init();
        };
    }
}

#endif