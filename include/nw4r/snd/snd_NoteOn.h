#ifndef NW4R_SND_NOTE_ON_H
#define NW4R_SND_NOTE_ON_H
#include "types_nw4r.h"
#include "snd_Channel.h"

namespace nw4r
{
	namespace snd
	{
		namespace detail
		{
			struct NoteOnInfo
			{
				int prgNo; // at 0x0
				int key; // at 0x4
				int velocity; // at 0x8
				int length; // at 0xC
				int initPan; // at 0x10
				int priority; // at 0x14
				int voiceOutCount; // at 0x18
				Channel::ChannelCallback channelCallback; // at 0x1C
				u32 channelCallbackData; // at 0x20
			};
			
			struct NoteOnCallback
			{
				virtual ~NoteOnCallback(); // at 0x8
				virtual bool NoteOn(SeqPlayer *, int, const NoteOnInfo &) = 0; // at 0xc
			};
		}
	}
}

#endif