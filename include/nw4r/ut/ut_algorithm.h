#ifndef NW4R_UT_ALGORITHM_H
#define NW4R_UT_ALGORITHM_H
#include "types_nw4r.h"

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
				return (value < min) ? min : value;
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
			
			template <>
			inline void * RoundUp(void * ptr, unsigned int alignment)
			{
				return (void *)RoundUp<u32>((u32)ptr, alignment);
			}
			
			template <>
			inline u8 * RoundUp(u8 * ptr, unsigned int alignment)
			{
				return (u8 *)RoundUp<u32>((u32)ptr, alignment);
			}
			
			template <typename T>
			inline const void * AddOffsetToPtr(const void * ptr, T offset)
			{
				return (const void *)(offset + (T)ptr);
			}

			inline u32 GetOffsetFromPtr(void *begin, void *end)
			{
				return (u32)end - (u32)begin;
			}
		}
	}
}

#endif