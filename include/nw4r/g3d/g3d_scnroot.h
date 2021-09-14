#ifndef NW4R_G3D_SCNROOT_H
#define NW4R_G3D_SCNROOT_H
#include "types_nw4r.h"

namespace nw4r
{
    namespace g3d
    {
        struct ScnRoot // : public ScnGroup
        {
            Fog GetFog(int);
        };
    }
}

#endif