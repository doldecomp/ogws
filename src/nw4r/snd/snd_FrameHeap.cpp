#ifdef __DECOMP_NON_MATCHING
#pragma ipa file
#include <new>
#include <mem_frameHeap.h>
#include "snd_FrameHeap.h"

namespace nw4r
{
	namespace snd
	{
		using namespace ut;
		
		namespace detail
		{
			FrameHeap::FrameHeap() : PTR_0x0() {}
			
			FrameHeap::~FrameHeap()
			{
				Destroy();
			}
			
			bool FrameHeap::NewSection()
			{
				void * ptr = MEMAllocFromFrmHeapEx(PTR_0x0, sizeof(Section), 4);
				
				if (!ptr) return false;
				
				mList.PushBack(new (ptr) Section());
				
				return true;
			}
			
			UNKTYPE FrameHeap::ClearSection()
			{
				Section * pSection = mList.GetBack();
				
				pSection->~Section();
				
				mList.Erase(pSection);
			}
			
			bool FrameHeap::Create(void * r4_27, u32 r5_28)
			{
				// r26 <- this
				Destroy();
				
				u8 * r3 = (u8 *)RoundUp<void *>(r4_27, 4);
				u8 * r4 = static_cast<u8 *>(r4_27) + r5_28;
				
				if (r3 > r4) return false;
				
				PTR_0x0 = MEMCreateFrmHeapEx(r3, r4 - r3, 0);
				
				if (!PTR_0x0) return false;
				
				if (!NewSection()) return false;
				
				return true;
			}
			
			UNKTYPE FrameHeap::Destroy()
			{
				if (IsValid())
				{
					while (mList.mCount)
					{
						ClearSection();
					}
				}
				
				MEMFreeToFrmHeap(PTR_0x0, 3);
				MEMDestroyFrmHeap(PTR_0x0);
				
				PTR_0x0 = NULL;
			}
			
			void FrameHeap::Clear()
			{
				if (IsValid())
				{
					while (mList.mCount)
					{
						ClearSection();
					}
				}
				
				MEMFreeToFrmHeap(PTR_0x0, 3);
				
				NewSection();
			}
			
			void * FrameHeap::Alloc(u32 r28_4, AllocCallback r29_5, void * r30_6)
			{
				//r27 <- this
				
				void * ptr = MEMAllocFromFrmHeapEx(PTR_0x0, RoundUp<u32>(r28_4, 0x20) + RoundUp<u32>(sizeof(Block), 0x20), 0x20);
				
				if (!ptr) return NULL;
				
				Block * pBlock = new (ptr) Block(r28_4, r29_5, r30_6);
				
				mList.GetBack()->AppendBlock(pBlock);
				
				return pBlock->GetBufferAddr();
			}
			
			int FrameHeap::SaveState()
			{
				if (!MEMRecordStateForFrmHeap(PTR_0x0, mList.mCount)) return -1;
				
				if (!NewSection())
				{
					MEMFreeByStateToFrmHeap(PTR_0x0, 0);
					return -1;
				}
				
				return GetCurrentLevel();
			}
			
			void FrameHeap::LoadState(int state)
			{
				// r31 <- this
				// r27 <- state
				if (!state)
				{
					Clear();
				}
				else
				{
					if (state < mList.mCount)
					{
						while (state < mList.mCount)
						{
							ClearSection();
						}
					}
					
					MEMFreeByStateToFrmHeap(PTR_0x0, state);
					MEMRecordStateForFrmHeap(PTR_0x0, mList.mCount);
					
					NewSection();
				}
			}
			
			int FrameHeap::GetCurrentLevel() const
			{
				return mList.mCount - 1;
			}
			
			u32 FrameHeap::GetFreeSize() const
			{
				u32 r3 = MEMGetAllocatableSizeForFrmHeapEx(PTR_0x0, 0x20);
				
				return (r3 < 0x20) ? 0 : RoundUp<u32>(r3 - 0x3F, 0x20);
			}
		}
	}
}
#else
#error This file has yet to be decompiled accurately. Use "snd_FrameHeap.s" instead.
#endif