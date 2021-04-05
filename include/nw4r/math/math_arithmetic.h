#ifndef NW4R_MATH_ARITHMETIC_H
#define NW4R_MATH_ARITHMETIC_H
#include "types_nw4r.h"
#include <OS.h>
#include <math.h>

namespace nw4r
{
    namespace math
    {
		inline float FFloor(float arg)
		{
			return floor(arg);
		}
		
		inline float FModf(float arg, float * pIntegralPart)
		{
			double integralPart;
			float fractionalPart = modf(arg, &integralPart);
			
			*pIntegralPart = integralPart;
			
			return fractionalPart;
		}
		
		inline float FInv(register float arg)
		{
			register float tmp;
			register float ret;
			
			asm
			{
				fres ret, arg
				ps_add tmp, ret, ret
				ps_mul ret, ret, ret
				ps_nmsub ret, arg, ret, tmp
			}
			
			return ret;
		}
		
		inline f32 U16ToF32(u16 arg)
		{
			f32 ret;
			
			OSu16tof32(&arg, &ret);
			
			return ret;
		}
		
		inline u16 F32ToU16(f32 arg)
		{
			u16 ret;
			
			OSf32tou16(&arg, &ret);
			
			return ret;
		}
		
		inline s16 F32ToS16(f32 arg)
		{
			s16 ret;
			
			OSf32tos16(&arg, &ret);
			
			return ret;
		}
    }
}

#endif