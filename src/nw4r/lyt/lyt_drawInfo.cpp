#include "lyt_drawInfo.h"
#include <revolution/TRK/__mem.h>

namespace nw4r
{
    namespace lyt
    {
        DrawInfo::DrawInfo() : mViewMtx(), mViewRect(), mScale(1.0f, 1.0f), mGlobalAlpha(1.0f)
        {
            memset(&mFlags, 0, sizeof(mFlags));
            math::MTX34Identity(&mViewMtx);
        }

        DrawInfo::~DrawInfo()
        {
            
        }
    }
}