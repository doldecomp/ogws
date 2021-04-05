#ifndef NW4R_MATH_TRIANGULAR_H
#define NW4R_MATH_TRIANGULAR_H
#include "types_nw4r.h"

#define DEG_TO_FIDX (256.0f / 360.0f)

namespace nw4r
{
    namespace math
    {
        void SinCosFIdx(f32 *, f32 *, f32);

        inline void SinCosDeg(f32 *pf1, f32 *pf2, f32 f3)
        {
            SinCosFIdx(pf1, pf2, DEG_TO_FIDX * f3);
        }
    }
}

#endif