#ifndef NW4R_UT_RECT
#define NW4R_UT_RECT

namespace nw4r
{
	namespace ut
	{
		// TODO: Implement the object properly
		struct Rect
		{
			float FLOAT_0x0;
			float FLOAT_0x4;
			float FLOAT_0x8;
			float FLOAT_0xC;
			
			inline Rect(float F_0x0, float F_0x4, float F_0x8, float F_0xC)
				: FLOAT_0x0(F_0x0), FLOAT_0x4(F_0x4),
				FLOAT_0x8(F_0x8), FLOAT_0xC(F_0xC)
			{}
			
			inline Rect() : FLOAT_0x0(), FLOAT_0x4(), FLOAT_0x8(), FLOAT_0xC() {}
			
			inline Rect & operator=(const Rect & other)
			{
				FLOAT_0x0 = other.FLOAT_0x0;
				FLOAT_0x4 = other.FLOAT_0x4;
				FLOAT_0x8 = other.FLOAT_0x8;
				FLOAT_0xC = other.FLOAT_0xC;
				
				return *this;
			}
			
			inline float GetWidth() const
			{
				return FLOAT_0x8 - FLOAT_0x0;
			}
		};
	}
}

#endif