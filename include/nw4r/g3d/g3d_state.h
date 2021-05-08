#ifndef NW4R_G3D_STATE_H
#define NW4R_G3D_STATE_H
#include <RevoSDK/GX/GXFrameBuf.h>

namespace nw4r
{
    namespace g3d
    {
        namespace G3DState
        {
            GXRenderModeObj& GetRenderModeObj();
            UNKTYPE SetRenderModeObj(const GXRenderModeObj&);
        }
    }
}

#endif