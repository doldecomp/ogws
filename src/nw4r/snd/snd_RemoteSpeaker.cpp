#include <OSTime.h>
#include <WPAD.h>
#include <wenc.h>
#include <string.h>
#include "snd_RemoteSpeaker.h"
#include "snd_RemoteSpeakerManager.h"
#include "ut_lock.h"

namespace nw4r
{
	using namespace ut;
	
	namespace snd
	{
		using namespace detail;
		
		RemoteSpeaker::RemoteSpeaker()
		{
			mPoweredFlag = false;
			BOOL_0x1 = false;
			mEnabledOutputFlag = false;
			BOOL_0x3 = false;
			BOOL_0x4 = false;
			BOOL_0x5 = false;
			BOOL_0x6 = false;
			WORD_0xC = 0;
			CMD_0x10 = SpeakerCommand_None;
			CMD_0x14 = SpeakerCommand_None;
			mCallback = NULL;
			
			OSCreateAlarm(&ALARM_0x40);
			OSSetAlarmUserData(&ALARM_0x40, this);
			
			OSCreateAlarm(&ALARM_0x70);
			OSSetAlarmUserData(&ALARM_0x70, this);
		}
		
		void RemoteSpeaker::ClearParam()
		{
			BOOL_0x1 = false;
			mEnabledOutputFlag = false;
			OSCancelAlarm(&ALARM_0x40);
			
			BOOL_0x7 = false;
			OSCancelAlarm(&ALARM_0x70);
			
			BOOL_0x8 = false;
		}
		
		void RemoteSpeaker::InitParam()
		{
			ClearParam();
			
			BOOL_0x6 = false;
			BOOL_0x7 = false;
			BOOL_0x1 = false;
			mEnabledOutputFlag = true;
			BOOL_0x8 = false;
		}
		
		bool RemoteSpeaker::Setup(RemoteSpeakerCallback callback)
		{
			AutoInterruptLock lock;
			
			InitParam();
			
			if (mCallback)
			{
				mCallback(mChannelIndex, 0);
				BOOL_0x4 = false;
			}
			
			mCallback = callback;
			CMD_0x10 = SpeakerCommand_On;
			mPoweredFlag = true;
			
			return true;
		}
		
		void RemoteSpeaker::Shutdown(RemoteSpeakerCallback callback)
		{
			AutoInterruptLock lock;
			
			ClearParam();
			
			if (mCallback)
			{
				mCallback(mChannelIndex, 0);
				BOOL_0x4 = false;
			}
			
			CMD_0x10 = SpeakerCommand_Off;
			mCallback = callback;
			mPoweredFlag = false;
		}
		
		bool RemoteSpeaker::EnableOutput(bool outputFlag)
		{
			if (!mPoweredFlag) return false;
			mEnabledOutputFlag = outputFlag;
			return true;
		}
		
		bool RemoteSpeaker::IsEnabledOutput() const
		{
			return mPoweredFlag ? mEnabledOutputFlag : false;
		}
		
		void RemoteSpeaker::Update()
		{
			if (BOOL_0x5) return;
			
			SpeakerCommand command = (CMD_0x10 != SpeakerCommand_None) ? CMD_0x10 : CMD_0x14;
			
			CMD_0x10 = SpeakerCommand_None;
			CMD_0x14 = SpeakerCommand_None;
			
			ExecCommand(command);
		}
		
		void RemoteSpeaker::ExecCommand(SpeakerCommand command)
		{
			switch (command)
			{
				case SpeakerCommand_None:
					break;
				case SpeakerCommand_On:
					BOOL_0x4 = true;
					BOOL_0x5 = true;
					WORD_0xC = 1;
					WPADControlSpeaker(mChannelIndex, 1, SpeakerOnCallback);
					break;
				case SpeakerCommand_Play:
					BOOL_0x4 = true;
					BOOL_0x5 = true;
					WORD_0xC = 3;
					WPADControlSpeaker(mChannelIndex, 4, SpeakerPlayCallback);
					break;
				case SpeakerCommand_Off:
					BOOL_0x4 = true;
					BOOL_0x5 = true;
					WORD_0xC = 5;
					WPADControlSpeaker(mChannelIndex, 0, SpeakerOffCallback);
					break;
			}
		}
		
		bool RemoteSpeaker::IsAllSampleZero(const s16 * pSample)
		{
			const s32 * pSampleWords = reinterpret_cast<const s32 *>(pSample);
			bool flag = true;
			for (int i = 0; i < 20; i++)
			{
				if (pSampleWords[i])
				{
					flag = false;
					break;
				}
			}
			return flag;
		}
		
		void RemoteSpeaker::UpdateStreamData(const s16 * pSample)
		{
			u8 streamData[20];
			
			if (WORD_0xC != 4) return;
			
			bool r30 = true;
			if ((mEnabledOutputFlag ? IsAllSampleZero(pSample) : true) || BOOL_0x6) r30 = false;
			
			bool r26 = !BOOL_0x1 && r30;
			bool r31 = BOOL_0x1 && !r30;
			
			if (r30)
			{
				AutoInterruptLock lock;
				
				if (!WPADCanSendStreamData(mChannelIndex)) return;
				UNKWORD r4 = !BOOL_0x3;
				BOOL_0x3 = false;
				WENCGetEncodeData(UNK_0x18, r4, pSample, 40, streamData);
				if (WPADSendStreamData(mChannelIndex, streamData, 20))
				{
					WORD_0xC = 0;
					CMD_0x14 = SpeakerCommand_On;
					InitParam();
					return;
				}
			}
			//8003D694
			if (r26)
			{
				AutoInterruptLock lock;
				if (!BOOL_0x7)
				{
					u32 bs = BUS_SPEED;
					s64 busSpeed = bs / 4;
					OSSetAlarm(&ALARM_0x40, busSpeed * 480, ContinueAlarmHandler);
					mTime = OSGetTime();
					BOOL_0x7 = true;
				}
				OSCancelAlarm(&ALARM_0x70);
				BOOL_0x8 = false;
			}
			//8003D710
			if (r31)
			{
				AutoInterruptLock lock;
				
				BOOL_0x8 = true;
				OSCancelAlarm(&ALARM_0x70);
				u32 busSpeed = BUS_SPEED / 4;
				OSSetAlarm(&ALARM_0x70, busSpeed, IntervalAlarmHandler);
			}
			//8003D758
			BOOL_0x1 = r30;
		}
		
		void RemoteSpeaker::NotifyCallback(s32 index, s32 arg2)
		{
			if (arg2 != -2 && BOOL_0x4 && mCallback)
			{
				mCallback(index, arg2);
				mCallback = NULL;
			}
		}
		
		void RemoteSpeaker::SpeakerOnCallback(s32 index, s32 r30)
		{
			RemoteSpeaker * pSpeaker = RemoteSpeakerManager::GetInstance()->GetRemoteSpeaker(index);
			
			switch (r30)
			{
				case 0:
					pSpeaker->BOOL_0x3 = true;
					memset(pSpeaker->UNK_0x18, 0, sizeof pSpeaker->UNK_0x18);
					pSpeaker->WORD_0xC = 2;
					pSpeaker->CMD_0x14 = SpeakerCommand_Play;
					break;
				case -2:
					pSpeaker->CMD_0x14 = SpeakerCommand_On;
					break;
				case -3:
					pSpeaker->WORD_0xC = 0;
					break;
				case -1:
					pSpeaker->WORD_0xC = 0;
					break;
				default:
					pSpeaker->WORD_0xC = 0;
					break;
			}
			
			if (r30) pSpeaker->NotifyCallback(index, r30);
			
			pSpeaker->BOOL_0x5 = false;
		}
		
		void RemoteSpeaker::SpeakerPlayCallback(s32 index, s32 r30)
		{
			RemoteSpeaker * pSpeaker = RemoteSpeakerManager::GetInstance()->GetRemoteSpeaker(index);
			
			switch (r30)
			{
				case 0:
					pSpeaker->WORD_0xC = 4;
					break;
				case -2:
					pSpeaker->CMD_0x14 = SpeakerCommand_Play;
					break;
				case -3:
					pSpeaker->WORD_0xC = 0;
					break;
				case -1:
					pSpeaker->WORD_0xC = 0;
					break;
				default:
					pSpeaker->WORD_0xC = 0;
					break;
			}
			
			pSpeaker->NotifyCallback(index, r30);
			
			pSpeaker->BOOL_0x5 = false;
		}
		
		void RemoteSpeaker::SpeakerOffCallback(s32 index, s32 r30)
		{
			RemoteSpeaker * pSpeaker = RemoteSpeakerManager::GetInstance()->GetRemoteSpeaker(index);
			
			switch (r30)
			{
				case 0:
					pSpeaker->WORD_0xC = 6;
					break;
				case -2:
					pSpeaker->CMD_0x14 = SpeakerCommand_Off;
					break;
				case -3:
					pSpeaker->WORD_0xC = 0;
					break;
				case -1:
					pSpeaker->WORD_0xC = 0;
					break;
				default:
					pSpeaker->WORD_0xC = 0;
					break;
			}
			
			pSpeaker->NotifyCallback(index, r30);
			
			pSpeaker->BOOL_0x5 = false;
		}
		
		void RemoteSpeaker::ContinueAlarmHandler(OSAlarm * pAlarm, OSContext *)
		{
			AutoInterruptLock lock;
			
			RemoteSpeaker * pSpeaker = static_cast<RemoteSpeaker *>(OSGetAlarmUserData(pAlarm));
			
			pSpeaker->BOOL_0x6 = true;
			pSpeaker->BOOL_0x7 = false;
		}
		
		void RemoteSpeaker::IntervalAlarmHandler(OSAlarm * pAlarm, OSContext *)
		{
			AutoInterruptLock lock;
			
			RemoteSpeaker * pSpeaker = static_cast<RemoteSpeaker *>(OSGetAlarmUserData(pAlarm));
			
			if (pSpeaker->BOOL_0x8)
			{
				OSCancelAlarm(&pSpeaker->ALARM_0x40);
				pSpeaker->BOOL_0x6 = false;
				pSpeaker->BOOL_0x7 = false;
			}
			
			pSpeaker->BOOL_0x8 = false;
		}
	}
}