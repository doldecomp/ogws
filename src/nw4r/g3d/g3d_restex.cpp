#include "g3d_restex.h"
#include <revolution/OS/OSCache.h>

namespace nw4r
{
    namespace g3d
    {
        void ResPltt::DCStore(bool bSync)
        {
            ResPlttData& rPltt = mPltt.ref();
            int len = rPltt.mLength;

            if (bSync)
            {
                DCStoreRange(&rPltt, len);
            }
            else
            {
                DCStoreRangeNoSync(&rPltt, len);
            }
        }

        bool ResTex::GetTexObjParam(void **r4, u16 *r5, u16 *r6, GXTexFmt *pFmt,
        f32 *r8, f32 *r9, u8 *r10) const
        {
            if (mTex.ref().mFlags & 1) return false;

            ResTexData& rTex = mTex.ref();

            if (r4) *r4 = mTex.ofs_to_obj<void *>(mTex.ref().INT_0x10);
            
            if (r5) *r5 = mTex.ref().SHORT_0x1C;

            if (r6) *r6 = mTex.ref().SHORT_0x1E;
            
            if (pFmt) *pFmt = rTex.mFormat;
            
            if (r8) *r8 = rTex.FLOAT_0x28;
            
            if (r9) *r9 = rTex.FLOAT_0x2C;

            if (r10)
            {
                *r10 = (rTex.WORD_0x24 > 1);
            }

            return true;
        }

        bool ResTex::GetTexObjCIParam(void **r4, u16 *r5, u16 *r6, GXCITexFmt *pFmt,
        f32 *r8, f32 *r9, u8 *r10) const
        {
            if ((mTex.ref().mFlags & 1) == 0) return false;

            ResTexData& rTex = mTex.ref();

            if (r4) *r4 = mTex.ofs_to_obj<void *>(mTex.ref().INT_0x10);
            
            if (r5) *r5 = mTex.ref().SHORT_0x1C;

            if (r6) *r6 = mTex.ref().SHORT_0x1E;
            
            if (pFmt) *pFmt = rTex.mCiFormat;
            
            if (r8) *r8 = rTex.FLOAT_0x28;
            
            if (r9) *r9 = rTex.FLOAT_0x2C;

            if (r10)
            {
                *r10 = (rTex.WORD_0x24 > 1);
            }

            return true;
        }

        void ResTex::Init()
        {
            ResTexData& rTex = mTex.ref();
            int len = rTex.mLength;
            
            DCFlushRangeNoSync(&rTex, len);
        }
    }
}