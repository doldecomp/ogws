#include <mem_frameHeap.h>
#include "ut_algorithm.h"
#include "snd_AxfxImpl.h"

namespace nw4r
{
	using namespace ut;
	
	namespace snd
	{
		namespace detail
		{
			bool AxfxImpl::CreateHeap(void * ptr, u32 num)
			{
				return mHeap = (MEMiHeapHead *)MEMCreateFrmHeapEx(ptr, num, 0);
			}
			
			UNKTYPE AxfxImpl::DestroyHeap()
			{
				if (mHeap) MEMDestroyFrmHeap(mHeap);
			}
			
			UNKTYPE AxfxImpl::HookAlloc(AXFXAllocHook * allocHook, AXFXFreeHook * freeHook)
			{
				AXFXGetHooks(allocHook, freeHook);
				AXFXSetHooks(Alloc, Free);
				
				mCurrentFx = this;
			}
			
			UNKTYPE AxfxImpl::RestoreAlloc(AXFXAllocHook allocHook, AXFXFreeHook freeHook)
			{
				AXFXSetHooks(allocHook, freeHook);
				
				mCurrentFx = NULL;
			}
			
			void * AxfxImpl::Alloc(u32 size)
			{
				void * ret = MEMAllocFromFrmHeapEx(mCurrentFx->mHeap, size, 4);
				
				mCurrentFx->mAllocCount++;
				mAllocatedSize += RoundUp<u32>(size, 4);
				
				return ret;
			}
			
			void AxfxImpl::Free(void * ptr)
			{
				if (mCurrentFx->mAllocCount) mCurrentFx->mAllocCount--;
				
				if (!mCurrentFx->mAllocCount) MEMFreeToFrmHeap(mCurrentFx->mHeap, 3);
			}
			
			AxfxImpl * AxfxImpl::mCurrentFx;
			u32 AxfxImpl::mAllocatedSize;
		}
	}
}