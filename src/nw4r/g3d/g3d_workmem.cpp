#include "g3d_workmem.h"

namespace nw4r
{
    namespace g3d
    {
        namespace detail
        {
            namespace workmem
            {
                namespace
                {
                    static u8 sTemp[G3D_WORKMEM_SIZE];
                }

                void * GetScaleTemporary()
                {
                    return &sTemp;
                }

                void * GetMtxIDTemporary()
                {
                    return &sTemp[0x6000];
                }

                void * GetMdlZTemporary()
                {
                    return &sTemp;
                }

                void * GetSkinningMtxTemporary()
                {
                    return &sTemp;
                }

                void * GetBillboardMtxTemporary()
                {
                    return &sTemp;
                }

                void * GetShpAnmResultBufTemporary()
                {
                    return &sTemp;
                }
            }
        }
    }
}
