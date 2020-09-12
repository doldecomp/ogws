#ifndef NW4R_UT_COLOR_H
#define NW4R_UT_COLOR_H
#include "types_nw4r.h"

namespace nw4r
{
	namespace ut
	{
		struct Color
		{
			u8 r, g, b, a;
			
			inline u32 & ToU32ref()
			{
				return *reinterpret_cast<u32 *>(this);
			}
			
			inline const u32 & ToU32ref() const
			{
				return *reinterpret_cast<const u32 *>(this);
			}
			
			inline Color & operator=(u32 value)
			{
				ToU32ref() = value;
				return *this;
			}
			
			inline operator unsigned long() const
			{
				return ToU32ref();
			}
			
			inline Color()
			{
				*this = 0xFFFFFFFF;
			}
			
			inline Color(const Color & other)
			{
				r = other.r;
				g = other.g;
				b = other.b;
				a = other.a;
			}
			
			inline Color & operator=(const Color & other)
			{
				r = other.r;
				g = other.g;
				b = other.b;
				a = other.a;
				
				return *this;
			}
		};
	}
}

#endif