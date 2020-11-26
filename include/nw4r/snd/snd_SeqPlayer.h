#ifndef NW4R_SND_SEQ_PLAYER_H
#define NW4R_SND_SEQ_PLAYER_H
#include "types_nw4r.h"
#include "snd_BasicPlayer.h"
#include "snd_InstancePool.h"

namespace nw4r
{
	namespace snd
	{
		namespace detail
		{
			struct SeqPlayer : BasicPlayer
			{
				enum OffsetType
				{
					PLACEHOLDER_OffsetType // empty enums are ill-formed
				};
				
				~SeqPlayer();
				
				UNKWORD Start(); // at 0xc
				UNKTYPE Stop(); // at 0x10
				UNKTYPE Pause(bool); // at 0x14
				bool IsActive() const; // at 0x18
				bool IsStarted() const; // at 0x1c
				bool IsPause() const; // at 0x20
				
				char UNK_0x70[0xA8];
				
				SeqPlayer();
				UNKTYPE Setup(SeqTrackAllocator *, u32, int, NoteOnCallback *);
				UNKTYPE SetSeqData(const void *, s32);
				UNKTYPE Skip(OffsetType, int);
				
				UNKTYPE SetTempoRatio(float);
				UNKTYPE SetChannelPriority(int);
				UNKTYPE SetReleasePriorityFix(bool);
				
				UNKTYPE SetTrackVolume(u32, float);
				UNKTYPE SetTrackPitch(u32, float);
				
				UNKTYPE SetLocalVariable(int, short);
				static UNKTYPE SetGlobalVariable(int, short);
			};
		}
	}
}

#endif