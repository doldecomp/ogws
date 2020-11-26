#ifndef NW4R_UT_LOCK_H
#define NW4R_UT_LOCK_H
#include <OSMutex.h>
#include <OSInterrupt.h>

namespace nw4r
{
	namespace ut
	{
		namespace detail
		{
			inline void Lock(OSMutex & mutex)
			{
				OSLockMutex(&mutex);
			}
			
			inline void Unlock(OSMutex & mutex)
			{
				OSUnlockMutex(&mutex);
			}
			
			template <typename T>
			struct AutoLock
			{
				T & mMutex;
				
				inline AutoLock(T & rMutex) : mMutex(rMutex)
				{
					Lock(mMutex);
				}
				
				inline ~AutoLock()
				{
					Unlock(mMutex);
				}
			};
		}
		
		struct AutoInterruptLock
		{
			UNKWORD WORD_0x0;
			
			inline AutoInterruptLock() : WORD_0x0(OSDisableInterrupts()) {}
			inline ~AutoInterruptLock() { OSRestoreInterrupts(WORD_0x0); }
		};
	}
}

#endif