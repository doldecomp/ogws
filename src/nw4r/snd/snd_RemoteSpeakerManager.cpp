#include <OS.h>
#include <OSTime.h>
#include <AXOut.h>
#include "snd_RemoteSpeakerManager.h"

namespace nw4r
{
	namespace snd
	{
		namespace detail
		{
			RemoteSpeakerManager::RemoteSpeakerManager() : mPoweredFlag(false), mRemoteSpeakers()
			{
				for (int i = 0; i < 4; i++)
				{
					mRemoteSpeakers[i].SetChannelIndex(i);
				}
			}
			
			RemoteSpeakerManager * RemoteSpeakerManager::GetInstance()
			{
				static RemoteSpeakerManager instance;
				
				return &instance;
			}
			
			RemoteSpeaker * RemoteSpeakerManager::GetRemoteSpeaker(int remoteIndex)
			{
				return mRemoteSpeakers + remoteIndex;
			}
			
			void RemoteSpeakerManager::Setup()
			{
				if (mPoweredFlag) return;
				
				OSCreateAlarm(&mAlarm);
				
				s64 time = OSGetTime();
				u32 num = BUS_SPEED / 4 / 125000 * 6666667 / 8000;
				
				OSSetPeriodicAlarm(&mAlarm, time, num, RemoteSpeakerAlarmProc);
				
				mPoweredFlag = true;
			}
			
			void RemoteSpeakerManager::Shutdown()
			{
				if (!mPoweredFlag) return;
				
				OSCancelAlarm(&mAlarm);
				
				mPoweredFlag = false;
			}
			
			void RemoteSpeakerManager::RemoteSpeakerAlarmProc(OSAlarm *, OSContext *)
			{
				RemoteSpeakerManager * pManager = GetInstance();
				s16 samples[40];
				
				if (AXRmtGetSamplesLeft() < 40) return;
				
				for (int i = 0; i < 4; i++)
				{
					if (pManager->GetRemoteSpeaker(i)->WORD_0xC == 4)
					{
						AXRmtGetSamples(i, samples, 40);
						pManager->GetRemoteSpeaker(i)->UpdateStreamData(samples);
					}
					
					pManager->GetRemoteSpeaker(i)->Update();
				}
				
				AXRmtAdvancePtr(40);
			}
		}
	}
}