#include "g3d_dcc.h"
#include "math_types.h"
#include "g3d_maya.h"
#include "g3d_xsi.h"
#include "g3d_3dsmax.h"

namespace nw4r
{
    namespace g3d
    {
        void CalcTexMtx(math::MTX34 *pMtx, bool b, const TexSrt &srt, TexSrt::Flag flag,
            TexSrtTypedef::TexMatrixMode mode)
        {
            bool result;

            if (mode == TexSrtTypedef::TEX_MTX_MAYA)
            {
                result = detail::dcc::CalcTexMtx_Maya(pMtx, b, srt, flag) == false;
            }
            else if (mode == TexSrtTypedef::TEX_MTX_XSI)
            {
                result = detail::dcc::CalcTexMtx_Xsi(pMtx, b, srt, flag) == false;
            }
            else /* TexSrtTypedef::TEX_MTX_3DSMAX */
            {
                result = detail::dcc::CalcTexMtx_3dsmax(pMtx, b, srt, flag) == false;
            }

            if (result && b)
            {
                math::MTX34Identity(pMtx);
            }
        }
    }
}