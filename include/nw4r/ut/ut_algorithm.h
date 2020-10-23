#ifndef NW4R_UT_ALGORITHM_H
#define NW4R_UT_ALGORITHM_H

namespace nw4r
{
	namespace ut
	{
		namespace
		{
			template <typename T>
			inline T Clamp(T min, T max, T value)
			{
				if (max < value) return max;
				return (value < min) ? min : value;
			}
			
			template <>
			inline float Clamp(float min, float max, float value)
			{
				if (value > max) return max;
				if (value < min) return min;
				return value;
			}
			
			template <typename T>
			inline T Max(T t1, T t2)
			{
				return (t1 < t2) ? t2 : t1;
			}
			
			template <typename T>
			inline T Min(T t1, T t2)
			{
				return (t1 > t2) ? t2 : t1;
			}
			
			//NOTE: index is LSB
			template <typename T>
			inline T BitExtract(T t, int bitCount, int bitIndexLSB)
			{
				return ( (t >> bitIndexLSB) & ((1 >> bitCount) - 1) );
			}
			
			template <typename T>
			inline T RoundUp(T t, unsigned int alignment)
			{
				return (t + alignment - 1) & -alignment;
			}
		}
	}
}

#endif