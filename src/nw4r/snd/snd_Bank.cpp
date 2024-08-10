#include "ut_algorithm.h"
#include "snd_Bank.h"

namespace nw4r
{
	using namespace ut;
	
	namespace snd
	{
		namespace detail
		{
			Bank::Bank(const void * ptr) : mFileReader(ptr), PTR_0xC(NULL) {}
			Bank::~Bank() {}
			
			Channel * Bank::NoteOn(const NoteOnInfo & noteOnInfo) const
			{
				InstInfo instInfo; // at 0x8
				
				if (!mFileReader.ReadInstInfo(&instInfo, noteOnInfo.INT_0x0, noteOnInfo.INT_0x4, noteOnInfo.INT_0x8)) return NULL;
				WaveData waveData; // at 0x18
				
				if (!mFileReader.ReadWaveParam(&waveData, instInfo.WORD_0x0, PTR_0xC)) return NULL;
				
				Channel * pChannel = Channel::AllocChannel(Min<int>(waveData.numChannels, 2), noteOnInfo.INT_0x18, noteOnInfo.INT_0x14, noteOnInfo.mChannelCallback, noteOnInfo.INT_0x20);
				
				if (!pChannel) return NULL;
				
				pChannel->SetKey(noteOnInfo.INT_0x4);
				pChannel->SetOriginalKey(instInfo.BYTE_0x8);
				
				//f3 = noteOnInfo.INT_0x8
				//f3 = f3 / 127.0f
				//f0 = instInfo.BYTE_0xA
				//f3 = f3 * f3
				//f0 = f0 / 127.0f
				float f3 = noteOnInfo.INT_0x8 / 127.0f;
				float f0 = instInfo.BYTE_0xA / 127.0f;
				f3 *= f3;
				pChannel->SetInitVolume(f3 *= f0);
				pChannel->SetTune(instInfo.FLOAT_0xC);
				
				pChannel->SetAttack(instInfo.mAttack);
				pChannel->SetDecay(instInfo.mDecay);
				pChannel->SetSustain(instInfo.mSustain);
				pChannel->SetRelease(instInfo.mRelease);
				
				//r5 = instInfo.BYTE_0x9 -64
				//r0 = noteOnInfo.WORD_0x10
				//f3 = r5
				//f1 = r0
				//f3 = f3 / 63.0f 
				//f1 = f1 / 63.0f
				
				float a = (instInfo.BYTE_0x9 - 64) / 63.0f;
				float b = noteOnInfo.INT_0x10 / 63.0f;
				
				pChannel->SetInitPan(a += b);
				pChannel->SetInitSurroundPan(0.0f);
				pChannel->Start(waveData, noteOnInfo.INT_0xC, 0) ;
				
				return pChannel;
			}
		}
	}
}