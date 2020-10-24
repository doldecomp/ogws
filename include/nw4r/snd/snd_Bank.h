#ifndef NW4R_SND_BANK_H
#define NW4R_SND_BANK_H
#include "snd_BankFile.h"
#include "snd_Channel.h"

namespace nw4r
{
	namespace snd
	{
		namespace detail
		{
			struct NoteOnInfo
			{
				int INT_0x0;
				int INT_0x4;
				int INT_0x8;
				int INT_0xC;
				int INT_0x10;
				int INT_0x14;
				int INT_0x18;
				Channel::ChannelCallback mChannelCallback; // at 0x1c
				u32 INT_0x20;
			};
			
			struct Bank
			{
				Bank(const void *);
				~Bank();
				Channel * NoteOn(const NoteOnInfo &) const;
				
				BankFileReader mFileReader; // at 0x0
				const UNKTYPE * PTR_0xC;
			};
		}
	}
}

#endif