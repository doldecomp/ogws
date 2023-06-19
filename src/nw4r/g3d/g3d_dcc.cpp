#include "g3d_dcc.h"
#include "math_types.h"
#include "g3d_maya.h"
#include "g3d_xsi.h"
#include "g3d_3dsmax.h"

namespace nw4r
{
    namespace g3d
    {
        void CalcTexMtx(math::MTX34 *pMtx, bool set, const TexSrt &srt, TexSrt::Flag flag,
            TexSrtTypedef::TexMatrixMode mode)
        {
            bool identity;

            if (mode == TexSrtTypedef::TEX_MTX_MAYA)
            {
                identity = !detail::dcc::CalcTexMtx_Maya(pMtx, set, srt, flag);
            }
            else if (mode == TexSrtTypedef::TEX_MTX_XSI)
            {
                identity = !detail::dcc::CalcTexMtx_Xsi(pMtx, set, srt, flag);
            }
            else
            {
                identity = !detail::dcc::CalcTexMtx_3dsmax(pMtx, set, srt, flag);
            }

            if (identity && set)
            {
                math::MTX34Identity(pMtx);
            }
        }
    }
}