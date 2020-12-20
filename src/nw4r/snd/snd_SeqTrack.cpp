#ifdef __DECOMP_NON_MATCHING
#pragma ipa file
#include "ut_algorithm.h"
#include "snd_SoundThread.h"
#include "snd_SeqTrack.h"
#include "snd_SeqPlayer.h"

namespace nw4r
{
	namespace snd
	{
		using namespace ut;
		
		namespace detail
		{
			void SeqTrack::SetPlayerTrackNo(int playerTrackNo)
			{
				mPlayerTrackNo = playerTrackNo;
			}
			
			SeqTrack::SeqTrack() : mOpenFlag(false), mPlayer(NULL), mChannel(NULL)
			{
				InitParam();
			}
			
			SeqTrack::~SeqTrack()
			{
				Close();
			}
			
			UNKTYPE SeqTrack::InitParam()
			{
				//f1=1f
				//f0=0f
				mVolume = 1.0f;
				mPitch = 1.0f;
				FLOAT_0x10 = 0.0f;
				FLOAT_0x14 = 0.0f;
				FLOAT_0x18 = 1.0f;
				FLOAT_0x1C = 0.0f;
				FLOAT_0x20 = 0.0f;
				for (int i = 0; i < 3; i++)
				{
					FLOATS_0x24[i] = 0.0f;
				}
				for (int i = 0; i < 4; i++)
				{
					FLOATS_0x30[i] = 0.0f;
					FLOATS_0x40[i] = 0.0f;
				}
				PTR_0x50 = NULL;
				PTR_0x54 = NULL;
				INT_0x64 = 0;
				WORD_0x68 = 0;
				BYTE_0x8C = 0x40;
				TIMER_0x58 = 0;
				BOOL_0x5C = false;
				BYTE_0x5D = 0;
				BOOL_0x5E = false;
				BOOL_0x5F = false;
				BOOL_0x60 = false;
				BYTE_0x84 = 0x7F;
				BYTE_0x85 = 0x7F;
				BYTE_0x88 = 0;
				BYTE_0x89 = 0;
				BYTE_0x8A = 0;
				BYTE_0x86 = 0;
				mAttack = 0xFF;
				mDecay = 0xFF;
				mSustain = 0xFF;
				mRelease = 0xFF;
				BYTE_0x93 = 0x7F;
				for (int i = 0; i < 3; i++)
				{
					BYTES_0x94[i] = 0;
				}
				BYTE_0x97 = 0x40;
				BYTE_0x87 = 2;
				BYTE_0x8D = 0x3C;
				BYTE_0x8E = 0;
				FLOAT_0x80 = 0.0f;
				BYTE_0x8B = 0;
				mLfoParam.Init();
				BYTE_0x7C = 0;
				for (int i = 0; i < 0x10; i++)
				{
					mVariables[i] = -1;
				}
			}
			
			void SeqTrack::SetSeqData(const void * r_4, s32 offset)
			{
				PTR_0x50 = r_4;
				PTR_0x54 = static_cast<const u8 *>(r_4) + offset;
			}
			
			void SeqTrack::Open()
			{
				mOpenFlag = true;
			}
			
			void SeqTrack::Close()
			{
				OSLockMutex(&SoundThread::GetInstance()->mMutex);
				
				ReleaseAllChannel(-1);
				FreeAllChannel();
				
				mOpenFlag = false;
				
				OSUnlockMutex(&SoundThread::GetInstance()->mMutex);
			}
			
			void SeqTrack::UpdateChannelRelease(Channel * pChannel)
			{
				OSLockMutex(&SoundThread::GetInstance()->mMutex);
				
				if (!pChannel->mLength &&
					pChannel->mEnvGenerator.mStatus != EnvGenerator::Status_Release &&
					BOOL_0x60) pChannel->Release();
				
				OSUnlockMutex(&SoundThread::GetInstance()->mMutex);
			}
			
			void SeqTrack::UpdateChannelLength()
			{
				OSLockMutex(&SoundThread::GetInstance()->mMutex);
				
				if (!mOpenFlag)
				{
					OSUnlockMutex(&SoundThread::GetInstance()->mMutex);
					return;
				}
				
				for (Channel * pChannel = mChannel; pChannel; pChannel = pChannel->mNext)
				{
					if (pChannel->mLength > 0) pChannel->mLength--;
					
					UpdateChannelRelease(pChannel);
					
					if (!pChannel->IsAutoUpdateSweep()) pChannel->UpdateSweep(1);
				}
				
				OSUnlockMutex(&SoundThread::GetInstance()->mMutex);
			}
			
			UNKWORD SeqTrack::ParseNextTick(bool flag)
			{
				OSLockMutex(&SoundThread::GetInstance()->mMutex);
				
				if (!mOpenFlag)
				{
					OSUnlockMutex(&SoundThread::GetInstance()->mMutex);
					return 0;
				}
				
				if (BOOL_0x5E)
				{
					if (mChannel)
					{
						OSUnlockMutex(&SoundThread::GetInstance()->mMutex);
						return 1;
					}
					BOOL_0x5E = false;
				}
				
				if (TIMER_0x58 > 0 && --TIMER_0x58 > 0)
				{
					OSUnlockMutex(&SoundThread::GetInstance()->mMutex);
					return 1;
				}
				
				if (PTR_0x54)
				{
					while (!TIMER_0x58 && !BOOL_0x5E)
					{
						if (Parse(flag) == 1)
						{
							OSUnlockMutex(&SoundThread::GetInstance()->mMutex);
							return -1;
						}
					}
				}
				
				OSUnlockMutex(&SoundThread::GetInstance()->mMutex);
				
				return 1;
			}
			
			void SeqTrack::ReleaseAllChannel(int release)
			{
				OSLockMutex(&SoundThread::GetInstance()->mMutex);
				
				UpdateChannelParam();
				
				for (Channel * pChannel = mChannel; pChannel; pChannel = pChannel->mNext)
				{
					if (pChannel->IsActive()) pChannel->SetRelease(release);
				}
				
				OSUnlockMutex(&SoundThread::GetInstance()->mMutex);
			}
			
			void SeqTrack::PauseAllChannel(bool flag)
			{
				OSLockMutex(&SoundThread::GetInstance()->mMutex);
				
				UpdateChannelParam();
				
				for (Channel * pChannel = mChannel; pChannel; pChannel = pChannel->mNext)
				{
					if (pChannel->IsActive() && flag != (pChannel->IsPause() != false)) pChannel->Pause(flag);
				}
				
				OSUnlockMutex(&SoundThread::GetInstance()->mMutex);
			}
			
			void SeqTrack::UpdateChannelParam()
			{
				OSLockMutex(&SoundThread::GetInstance()->mMutex);
				
				if (!mOpenFlag)
				{
					OSUnlockMutex(&SoundThread::GetInstance()->mMutex);
					return;
				}
				//8004047C
				if (!mChannel)
				{
					OSUnlockMutex(&SoundThread::GetInstance()->mMutex);
					return;
				}
				//80040498
				//r0=BYTE_0x84
				//r4=mPlayer
				//stack_0x3c=BYTE_0x84
				//r0=BYTE_0x85
				//f8=unsigned conv val
				//stack_0x44=BYTE_0x85
				
				float f7=BYTE_0x84/127.0f;
				float f22_=mPlayer->BYTE_0xA8/127.0f;
				float f13=BYTE_0x85/127.0f;
				float f3=BYTE_0x86/128.0f;
				float sq7=f7*f7;
				float sq13=f13*f13;
				float sq22=f22_*f22_;
				
				float f28;
				float f27;
				float f26;
				float f25;
				float f24;
				float f23;
				float f22;
				
				
				f28=1.0f;
				f27=f3*BYTE_0x87;
				f28*=sq7;
				f28*=sq13;
				f28*=sq22;
				f28*=mVolume;
				f28*=mPlayer->FLOAT_0x8;
				f26=1.0f;
				f26*=mPlayer->FLOAT_0xC;
				f26*=mPitch;
				float f9=BYTE_0x88/63.0f;
				f25=0.0f;
				float f12=Clamp<float>(-1.0f, 1.0f, f9);
				//800405A0
				f25+=f12;
				///f25+=Clamp<float>(-1.0f, 1.0f, f9);
				f25*=FLOAT_0x18;
				f25*=mPlayer->FLOAT_0x90;
				f25+=FLOAT_0x10;
				f25+=mPlayer->FLOAT_0x10;
				f24=0.0f;
				f24+=Clamp<float>(0.0f,2.0f,BYTE_0x8A/63.0f);
				//80040614
				f23=0.0f;
				f22=0.0f;
				//f30=127.0f;
				f24+=FLOAT_0x14;
				//f1=BYTE_0x93/127.0f;
				f24+=mPlayer->FLOAT_0x14;
				f22+=BYTE_0x93/127.0f-1.0f;
				f22+=FLOAT_0x20;
				f22+=mPlayer->FLOAT_0x28;
				f23+=(BYTE_0x97-64)/64.0f;
				f23+=FLOAT_0x1C;
				f23+=mPlayer->mLpfFreq;
				UNKWORD remoteFilter=mPlayer->mRemoteFilter; //at r30
				//800406AC
				float floats_0x28[3];
				for (int i = 0; i < 3; i++)
				{
					floats_0x28[i] = 0.0f;
					floats_0x28[i] += BYTES_0x94[i] / 127.0f + FLOATS_0x24[i];
					floats_0x28[i] += mPlayer->GetFxSend((AuxBus)i);
				}
				float floats_0x18[4];
				float floats_0x8[4];
				for (int i = 0; i < 4; i++)
				{
					floats_0x18[i] = 0.0f;
					floats_0x18[i] += mPlayer->GetRemoteSend(i);
					
					floats_0x8[i] = 0.0f;
					floats_0x8[i] += mPlayer->GetRemoteFxSend(i);
				}
				
				for (Channel * pChannel = mChannel; pChannel; pChannel = pChannel->mNext)
				{
					//80040778
					pChannel->FLOAT_0x38=f28;
					pChannel->FLOAT_0x98=f27;
					pChannel->FLOAT_0x3C=f26;
					pChannel->FLOAT_0x40=f25;
					pChannel->FLOAT_0x44=f24;
					pChannel->FLOAT_0x48=f23;
					pChannel->mRemoteFilter=remoteFilter;
					pChannel->mOutputLine=mPlayer->mOutputLine;
					pChannel->FLOAT_0x54=mPlayer->FLOAT_0x24;
					pChannel->FLOAT_0x58=f22;
					for (int i = 0; i < 3; i++)
					{
						pChannel->ARR_0x5C[i] = floats_0x28[i];
					}
					//800407CC
					for (int i = 0; i < 4; i++)
					{
						pChannel->mRemoteOutVolumes[i] = mPlayer->GetRemoteOutVolume(i);
						pChannel->ARR_0x78[i] = floats_0x18[i];
						pChannel->ARR_0x88[i] = floats_0x8[i];
					}
					//80040804
					pChannel->SetLfoParam(mLfoParam);
					pChannel->BYTE_0x30 = BYTE_0x7C;
					//80040848
				}
				
				OSUnlockMutex(&SoundThread::GetInstance()->mMutex);
			}
			
			void SeqTrack::FreeAllChannel()
			{
				OSLockMutex(&SoundThread::GetInstance()->mMutex);
				
				for (Channel * pChannel = mChannel; pChannel; pChannel = pChannel->mNext)
				{
					Channel::FreeChannel(pChannel);
				}
				
				mChannel = NULL;
				
				OSUnlockMutex(&SoundThread::GetInstance()->mMutex);
			}
			
			void SeqTrack::ChannelCallbackFunc(Channel * pChannel, Channel::ChannelCallbackStatus status, u32 arg)
			{
				OSLockMutex(&SoundThread::GetInstance()->mMutex);
				
				SeqTrack * pTrack = (SeqTrack *)arg;
				
				switch (status)
				{
					case Channel::CALLBACK_STATUS_0:
					case Channel::CALLBACK_STATUS_2:
						Channel::FreeChannel(pChannel);
						break;
				}
				
				if (pTrack->mPlayer) pTrack->mPlayer->ChannelCallback(pChannel);
				
				if (pTrack->mChannel == pChannel)
				{
					pTrack->mChannel = pChannel->mNext;
					OSUnlockMutex(&SoundThread::GetInstance()->mMutex);
					return;
				}
				
				for (Channel * pCur = pTrack->mChannel; pCur->mNext; pCur = pCur->mNext)
				{
					if (pCur->mNext == pChannel)
					{
						pCur->mNext = pChannel->mNext;
						OSUnlockMutex(&SoundThread::GetInstance()->mMutex);
						return;
					}
				}
				
				OSUnlockMutex(&SoundThread::GetInstance()->mMutex);
			}
			
			void SeqTrack::StopAllChannel()
			{
				OSLockMutex(&SoundThread::GetInstance()->mMutex);
				
				for (Channel * pChannel = mChannel; pChannel; pChannel = pChannel->mNext)
				{
					Channel::FreeChannel(pChannel);
					pChannel->Stop();
				}
				
				mChannel = NULL;
				
				OSUnlockMutex(&SoundThread::GetInstance()->mMutex);
			}
			
			void SeqTrack::SetMute(SeqMute mute)
			{
				OSLockMutex(&SoundThread::GetInstance()->mMutex);
				
				switch (mute)
				{
					case SEQ_MUTE_0:
						BOOL_0x5C = false;
						break;
					case SEQ_MUTE_3:
						StopAllChannel();
						BOOL_0x5C = true;
						break;
					case SEQ_MUTE_2:
						ReleaseAllChannel(-1);
						FreeAllChannel();
						BOOL_0x5C = true;
						break;
					case SEQ_MUTE_1:
						BOOL_0x5C = true;
						break;
				}
				
				OSUnlockMutex(&SoundThread::GetInstance()->mMutex);
			}
			
			void SeqTrack::SetVolume(float volume)
			{
				mVolume = volume;
			}
			
			void SeqTrack::SetPitch(float pitch)
			{
				mPitch = pitch;
			}
			
			s16 * SeqTrack::GetVariablePtr(int i)
			{
				if (i < 0x10) return mVariables + i;
				
				return NULL;
			}
			
			void SeqTrack::AddChannel(Channel * pChannel)
			{
				OSLockMutex(&SoundThread::GetInstance()->mMutex);
				
				pChannel->mNext = mChannel;
				mChannel = pChannel;
				
				OSUnlockMutex(&SoundThread::GetInstance()->mMutex);
			}
			
			Channel * SeqTrack::NoteOn(int r4_28, int r5_29, s32 r6_30, bool r7_26)
			{
				OSLockMutex(&SoundThread::GetInstance()->mMutex);
				
				SeqPlayer * pPlayer = mPlayer;
				Channel * pChannel = NULL;
				
				if (r7_26 && (pChannel = mChannel))
				{
					//80040C10
					pChannel->INT_0xC0 = (u8)r4_28;
					float f0 = r5_29 / 127.0f;
					pChannel->FLOAT_0xA8 = f0 * f0;
					//END
				}
				//80040C44
				if (!pChannel)
				{
					//80040C4C
					NoteOnInfo noteOnInfo = {
						WORD_0x68, r4_28, r5_29,
						(r7_26 ? -1 : r6_30), BYTE_0x89,
						pPlayer->mChannelPriority + BYTE_0x8C,
						mPlayer->INT_0xA4, ChannelCallbackFunc, (u32)this
					};
					
					if (!mPlayer->NoteOn(INT_0x64, noteOnInfo))
					{
						OSUnlockMutex(&SoundThread::GetInstance()->mMutex);
						return NULL;
					}
					
					AddChannel(pChannel);
				}
				//80040D3C
				if (mAttack != 0xFF) pChannel->mEnvGenerator.SetAttack(mAttack);
				if (mDecay != 0xFF) pChannel->mEnvGenerator.SetDecay(mDecay);
				if (mSustain != 0xFF) pChannel->mEnvGenerator.SetSustain(mSustain);
				if (mRelease != 0xFF) pChannel->mEnvGenerator.SetRelease(mRelease);
				//80040D8C
				
				float f1 = FLOAT_0x80;
				
				if (BOOL_0x5F) f1 += BYTE_0x8D - r4_28;
				
				//80040DC4
				if (!BYTE_0x8E)
				{
					pChannel->SetSweepParam(f1, r6_30, false);
				}
				else
				{
					float f3 = (f1 >= 0.0f) ? f1 : -f1;
					int r4 = BYTE_0x8E * BYTE_0x8E * f3;
					pChannel->SetSweepParam(f1, (r4 >> 5) << 2, true);
				}
				
				//80040E48
				BYTE_0x8D = r4_28;
				//bool r3 = BYTE_0x5D;
				
				pChannel->SetSilence(BYTE_0x5D, 0);
				
				//80040EB8
				pChannel->mReleasePriorityFixFlag = mPlayer->mReleasePriorityFixFlag;
				pChannel->mPanMode = mPlayer->mPanMode;
				pChannel->mPanCurve = mPlayer->mPanCurve;
				
				OSUnlockMutex(&SoundThread::GetInstance()->mMutex);
				return pChannel;
			}
		}
	}
}
#else
#error This file has yet to be decompiled accurately. Use "snd_SeqTrack.s" instead.
#endif