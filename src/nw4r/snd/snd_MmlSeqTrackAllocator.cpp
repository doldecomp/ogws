#include "snd_MmlSeqTrackAllocator.h"

namespace nw4r
{
	namespace snd
	{
		namespace detail
		{
			SeqTrack * MmlSeqTrackAllocator::AllocTrack(SeqPlayer * pPlayer)
			{
				MmlSeqTrack * pTrack = mPool.Alloc();
				
				if (pTrack)
				{
					pTrack->mPlayer = pPlayer;
					pTrack->mParser = mParser;
				}
				
				return pTrack;
			}
			
			void MmlSeqTrackAllocator::FreeTrack(SeqTrack * pTrack)
			{
				pTrack->mPlayer = NULL;
				
				mPool.Free(static_cast<MmlSeqTrack *>(pTrack));
			}
			
			u32 MmlSeqTrackAllocator::Create(void * r_4, u32 r_5)
			{
				return mPool.Create(r_4, r_5);
			}
			
			void MmlSeqTrackAllocator::Destroy(void * r_4, u32 r_5)
			{
				mPool.Destroy(r_4, r_5);
			}
			
			int MmlSeqTrackAllocator::GetAllocatableTrackCount() const
			{
				return mPool.Count();
			}
		}
	}
}