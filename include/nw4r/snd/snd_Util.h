#ifndef NW4R_SND_UTIL_H
#define NW4R_SND_UTIL_H
#include "types_nw4r.h"

namespace nw4r
{
	namespace snd
	{
		namespace detail
		{
			namespace Util
			{
				enum RefType
				{
					PLACEHOLDER // Empty enums are ill-formed
				};
				
				const void * GetDataRefAddressImpl(RefType, u32, const void *);
				
				template <typename T0, typename T1, typename T2, typename T3>
				struct DataRef
				{
					u8 mType; // at 0x0
					u8 BYTE_0x1;
					u32 INT_0x4;
				};
				
				template <typename T>
				struct Table
				{
					u32 mCount; // at 0x0
					T mEntries[]; // at 0x4
				};
				
				template <typename T0, typename T1, typename T2, typename T3>
				inline const T0 * GetDataRefAddress0(const DataRef<T0, T1, T2, T3> & dataRef, const void * ptr)
				{
					return (const T0 *)GetDataRefAddressImpl((RefType)dataRef.mType, dataRef.INT_0x4, ptr);
				}
				
				template <typename T0, typename T1, typename T2, typename T3>
				inline const T1 * GetDataRefAddress1(const DataRef<T0, T1, T2, T3> & dataRef, const void * ptr)
				{
					return (const T1 *)GetDataRefAddressImpl((RefType)dataRef.mType, dataRef.INT_0x4, ptr);
				}
				
				template <typename T0, typename T1, typename T2, typename T3>
				inline const T2 * GetDataRefAddress2(const DataRef<T0, T1, T2, T3> & dataRef, const void * ptr)
				{
					return (const T2 *)GetDataRefAddressImpl((RefType)dataRef.mType, dataRef.INT_0x4, ptr);
				}
				
				template <typename T0, typename T1, typename T2, typename T3>
				inline const T3 * GetDataRefAddress3(const DataRef<T0, T1, T2, T3> & dataRef, const void * ptr)
				{
					return (const T3 *)GetDataRefAddressImpl((RefType)dataRef.mType, dataRef.INT_0x4, ptr);
				}
				
				float CalcVolumeRatio(float);
				float CalcPitchRatio(int);
				
				u16 CalcRandom();
			}
		}
	}
}

#endif