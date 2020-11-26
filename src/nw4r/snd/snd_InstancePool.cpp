#include "snd_InstancePool.h"
#include "ut_lock.h"
#include "ut_algorithm.h"

namespace nw4r
{
	namespace snd
	{
		using namespace ut;
		
		namespace detail
		{
			u32 PoolImpl::CreateImpl(void * r28_4, u32 r29_5, u32 r30_6)
			{
				AutoInterruptLock lock;
				
				u8 * r6 = (u8 *)RoundUp<void *>(r28_4, 4);
				u32 r4 = RoundUp<u32>(r30_6, 4);
				u32 count = (r29_5-(r6-(u8*)r28_4))/r4;
				
				for (u32 i=0; i < count; i++, r6+=r4)
				{
					Member * cur = (Member *)r6;
					cur->mNext = mHead.mNext;
					mHead.mNext = cur;
				}
				
				return count;
			}
			
			void PoolImpl::DestroyImpl(void * r30_4, u32 r31_4)
			{
				AutoInterruptLock lock;
				
				Member * r29 = &mHead;
				void * r4 = (u8 *)r30_4 + r31_4;
				
				for (Member * curMember = r29->mNext; curMember; curMember = curMember->mNext)
				{
					if (r30_4 <= curMember && curMember < r4) r29->mNext = curMember->mNext;
					else r29 = curMember;
				}
			}
			
			u32 PoolImpl::CountImpl() const
			{
				AutoInterruptLock lock;
				
				Member * curMember = mHead.mNext;
				u32 counter = 0;
				
				while (curMember)
				{
					curMember = curMember->mNext;
					counter++;
				}
				
				return counter;
			}
			
			void * PoolImpl::AllocImpl()
			{
				AutoInterruptLock lock;
				
				Member * ptr = mHead.mNext; // at r31
				
				if (!ptr) return NULL;
				
				mHead.mNext = ptr->mNext;
				
				return ptr;
			}
			
			void PoolImpl::FreeImpl(void * ptr)
			{
				AutoInterruptLock lock;
				
				Member * pMember = static_cast<Member *>(ptr);
				pMember->mNext = mHead.mNext;
				mHead.mNext = pMember;
			}
		}
	}
}