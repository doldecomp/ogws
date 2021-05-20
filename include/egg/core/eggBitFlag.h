#ifndef EGG_CORE_BIT_FLAG_H
#define EGG_CORE_BIT_FLAG_H
#include "types_egg.h"

namespace EGG
{
	//NOTE: index is LSB
	template <typename T>
	struct TBitFlag
	{
		T value;
		
		inline void makeAllZero()
		{
			value = T();
		}
		
		inline TBitFlag()
		{
			makeAllZero();
		}
		
		inline T makeMask(u8 bit) const
		{
			return 1 << bit;
		}
		
		inline T on(T mask) const
		{
			return value & mask;
		}
		
		inline void set(T mask)
		{
			value |= mask;
		}
		
		inline void reset(T mask)
		{
			value &= ~mask;
		}
		
		inline bool onBit(u8 bit) const
		{
			return on(makeMask(bit));
		}
		
		inline void setBit(u8 bit)
		{
			set(makeMask(bit));
		}
		
		inline void resetBit(u8 bit)
		{
			reset(makeMask(bit));
		}
	};
}

#endif