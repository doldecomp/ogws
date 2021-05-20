#ifndef NW4R_MATH_EQUATION_H
#define NW4R_MATH_EQUATION_H
#include "types_nw4r.h"

namespace nw4r
{
	namespace math
	{
        inline f32 FSelect(register f32 val, register f32 zero, register f32 notzero)
        {
            asm
            {
                fsel zero, val, zero, notzero
            }

            return zero;
        }
	}
}

#endif