#ifndef NW4R_SND_MOVEVALUE_H
#define NW4R_SND_MOVEVALUE_H
#include "types_nw4r.h"

namespace nw4r
{
	namespace snd
	{
		namespace detail
		{
			template <typename T1, typename T2>
			struct MoveValue
			{
				T1 T1_0x0;
				T1 T1_0x4;
				T2 T2_0x8;
				T2 T2_0xC;
				
				inline MoveValue() : T1_0x0(), T1_0x4(), T2_0x8(), T2_0xC() {}
				
				inline void InitValue(T1 t1)
				{
					T1_0x0 = t1;
					T1_0x4 = t1;
					T2_0x8 = 0;
					T2_0xC = 0;
				}
				
				inline bool IsFinished() const
				{
					return T2_0xC >= T2_0x8;
				}
				
				inline T1 GetValue() const
				{
					if (IsFinished()) return T1_0x4;
					
					return T1_0x0 + T2_0xC * (T1_0x4 - T1_0x0) / T2_0x8;
				}
				
				inline void Update()
				{
					if (T2_0xC < T2_0x8) T2_0xC++;
				}
				
				inline void SetTarget(T1 t1, T2 t2)
				{
					T1_0x0 = GetValue();
					T1_0x4 = t1;
					T2_0x8 = t2;
					T2_0xC = 0;
				}
			};
		}
	}
}
#endif