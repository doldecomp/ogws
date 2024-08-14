#pragma ipa file
#include <OSMutex.h>
#include "ut_lock.h"
#include "snd_SoundThread.h"
#include "snd_SeqPlayer.h"
#include "snd_SeqTrack.h"
#include "snd_DisposeCallbackManager.h"

namespace nw4r
{
	namespace snd
	{
		namespace detail
		{
			SeqPlayer::SeqPlayer()
			{
				mActiveFlag = false;
				mStartedFlag = false;
				mPauseFlag = false;
				mReleasePriorityFixFlag = false;
				mTempoRatio = 1.0f;
				FLOAT_0x98 = 0.0f;
				OFFSET_0x9C = 0;
				OFFSET_0xA0 = 0.0f;
				FLOAT_0x90 = 1.0f;
				INT_0x118 = 0;
				INT_0xA4 = 0;
				SHORT_0xAC = 120;
				BYTE_0xAA = 0x30;
				BYTE_0xA8 = 0x7F;
				mChannelPriority = 0x40;
				mNoteOnCallback = NULL;
				for (int i = 0; i < SEQ_VARIABLE_COUNT; i++)
				{
					mLocalVariables[i] = -1;
				}
				for (int i = 0; i < SEQ_TRACKS_PER_PLAYER; i++)
				{
					mPlayerTracks[i] = NULL;
				}
			}
			
			SeqPlayer::~SeqPlayer()
			{
				SeqPlayer::Stop();
			}
			
			UNKTYPE SeqPlayer::InitParam(int r4_30, NoteOnCallback * pNoteOnCallback)
			{
				//r31 <- pCallback
				
				BasicPlayer::InitParam();
				//f1=1.0f
				//f0=0.0f
				mStartedFlag = false;
				mPauseFlag = false;
				mTempoRatio = 1.0f;
				OFFSET_0x9C = 0;
				OFFSET_0xA0 = 0.0f;
				FLOAT_0x90 = 1.0f;
				INT_0x118 = 0;
				INT_0xA4 = r4_30;
				SHORT_0xAC = 120;
				BYTE_0xAA = 0x30;
				BYTE_0xA8 = 0x7F;
				mChannelPriority = 0x40;
				mNoteOnCallback = pNoteOnCallback;
				FLOAT_0x98 = 0.0f;
				for (int i = 0; i < SEQ_VARIABLE_COUNT; i++)
				{
					mLocalVariables[i] = -1;
				}
				for (int i = 0; i < SEQ_TRACKS_PER_PLAYER; i++)
				{
					mPlayerTracks[i] = NULL;
				}
			}
			
			bool SeqPlayer::Setup(SeqTrackAllocator * pTrackAllocator, u32 trackFlags, int r6_24, NoteOnCallback * pNoteOnCallback)
			{
				SoundThread::AutoLock lock;
				
				SeqPlayer::Stop();
				
				//8003E338
				InitParam(r6_24, pNoteOnCallback);
				{
					ut::AutoInterruptLock lock;
					
					u32 flags = trackFlags;
					int trackCount = 0;
					
					while (flags)
					{
						if (flags & 1) trackCount++;
						
						flags >>= 1;
					}
					
					if (trackCount > pTrackAllocator->GetAllocatableTrackCount()) return true;
					
					//8003E3AC
					for (int i = 0; trackFlags; trackFlags >>= 1, i++)
					{
						if (trackFlags & 1)
						{
							SeqTrack *pTrack = pTrackAllocator->AllocTrack(this);
							SetPlayerTrack(i, pTrack);
						}
					}
				}
				DisposeCallbackManager::GetInstance().RegisterDisposeCallback(this);
				
				mTrackAllocator = pTrackAllocator;
				mActiveFlag = true;
				
				return false;
			}
			
			void SeqPlayer::SetSeqData(const void * r4_29, s32 r5_30)
			{
				SoundThread::AutoLock lock;
				
				SeqTrack * pPlayerTrack = mPlayerTracks[0];
				
				if (r4_29)
				{
					pPlayerTrack->SetSeqData(r4_29, r5_30);
					pPlayerTrack->Open();
				}
			}
			
			bool SeqPlayer::Start()
			{
				SoundThread::AutoLock lock;
				
				SoundThread::GetInstance().RegisterPlayerCallback(this);
				mStartedFlag = true;
				
				return true;
			}
			
			void SeqPlayer::CloseTrack(int i)
			{
				SoundThread::AutoLock lock;
				
				SeqTrack * pTrack = GetPlayerTrack(i);
				
				if (!pTrack) return;
				
				
				pTrack->Close();
				
				mTrackAllocator->FreeTrack(mPlayerTracks[i]);
				mPlayerTracks[i] = NULL;
			}
			
			void SeqPlayer::FinishPlayer()
			{
				SoundThread::AutoLock lock;
				
				if (mStartedFlag)
				{
					SoundThread::GetInstance().UnregisterPlayerCallback(this);
					mStartedFlag = false;
				}
				
				if (mActiveFlag)
				{
					DisposeCallbackManager::GetInstance().UnregisterDisposeCallback(this);
					mActiveFlag = false;
				}
				
				for (int i = 0; i < SEQ_TRACKS_PER_PLAYER; i++)
				{
					CloseTrack(i);
				}
			}
			
			void SeqPlayer::Stop()
			{
				SoundThread::AutoLock lock;
				
				FinishPlayer();
			}
			
			void SeqPlayer::Pause(bool pauseFlag)
			{
				SoundThread::AutoLock lock;
				
				mPauseFlag = pauseFlag;
				
				for (int i = 0; i < SEQ_TRACKS_PER_PLAYER; i++)
				{
					SeqTrack * pPlayerTrack = GetPlayerTrack(i);
					
					if (pPlayerTrack) pPlayerTrack->PauseAllChannel(pauseFlag);
				}
			}
			
			void SeqPlayer::Skip(OffsetType offsetType, int offset)
			{
				SoundThread::AutoLock lock;
				
				if (!mActiveFlag) return;
				
				switch (offsetType)
				{
					case OFFSET_TYPE_0:
						OFFSET_0x9C += offset;
						break;
					case OFFSET_TYPE_1:
						OFFSET_0xA0 += offset;
						break;
				}
			}
			
			void SeqPlayer::SetTempoRatio(float tempoRatio)
			{
				mTempoRatio = tempoRatio;
			}
			
			void SeqPlayer::SetChannelPriority(int channelPriority)
			{
				mChannelPriority = channelPriority;
			}
			
			void SeqPlayer::SetReleasePriorityFix(bool releasePriorityFixFlag)
			{
				mReleasePriorityFixFlag = releasePriorityFixFlag;
			}
			
			void SeqPlayer::SetLocalVariable(int i, short value)
			{
				mLocalVariables[i] = value;
			}
			
			void SeqPlayer::InitGlobalVariable()
			{
				for (int i = 0; i < SEQ_VARIABLE_COUNT; i++)
				{
					mGlobalVariable[i] = -1;
				}
				
				mGobalVariableInitialized = true;
			}
			
			void SeqPlayer::SetGlobalVariable(int i, short value)
			{
				if (!mGobalVariableInitialized) InitGlobalVariable();
				
				mGlobalVariable[i] = value;
			}
			
			void SeqPlayer::SetTrackVolume(u32 flags, float volume)
			{
				SetTrackParam<float>(flags, &SeqTrack::SetVolume, volume);
			}
			
			void SeqPlayer::SetTrackPitch(u32 flags, float pitch)
			{
				SetTrackParam<float>(flags, &SeqTrack::SetPitch, pitch);
			}
			
			void SeqPlayer::InvalidateData(const void * pStart, const void * pEnd)
			{
				SoundThread::AutoLock lock;
				
				if (mActiveFlag)
				{
					for (int i = 0; i < SEQ_TRACKS_PER_PLAYER; i++)
					{
						SeqTrack * pTrack = GetPlayerTrack(i);
						
						if (pTrack && pStart <= pTrack->PTR_0x50 && pTrack->PTR_0x50 <= pEnd)
						{
							SeqPlayer::Stop();
							break;
						}
					}
				}
			}
			
			void SeqPlayer::SetPlayerTrack(int i, SeqTrack * pTrack)
			{
				SoundThread::AutoLock lock;
				
				if (i > (SEQ_TRACKS_PER_PLAYER - 1)) return;
				
				mPlayerTracks[i] = pTrack;
				
				pTrack->SetPlayerTrackNo(i);
			}
			
			SeqTrack * SeqPlayer::GetPlayerTrack(int i)
			{
				if (i > (SEQ_TRACKS_PER_PLAYER - 1)) return NULL;
				
				return mPlayerTracks[i];
			}
			
			bool SeqPlayer::ParseNextTick(bool flag)
			{
				SoundThread::AutoLock lock;
				
				bool loopFlag = false;
				
				for (int i = 0; i < SEQ_TRACKS_PER_PLAYER; i++)
				{
					SeqTrack * pTrack = GetPlayerTrack(i);
					
					if (pTrack)
					{
						pTrack->UpdateChannelLength();
						
						if (pTrack->ParseNextTick(flag) < 0) CloseTrack(i);
						
						if (pTrack->IsOpened()) loopFlag = true;
					}
				}
				
				if (!loopFlag) return true;
				
				return false;
			}
			
			volatile s16 * SeqPlayer::GetVariablePtr(int i)
			{
				if (i < SEQ_VARIABLE_COUNT) return mLocalVariables + i;
				
				if (i < SEQ_VARIABLE_COUNT * 2) return mGlobalVariable + (i - SEQ_VARIABLE_COUNT);
				
				return NULL;
			}
			
			void SeqPlayer::UpdateChannelParam()
			{
				SoundThread::AutoLock lock;
				
				for (int i = 0; i < SEQ_TRACKS_PER_PLAYER; i++)
				{
					SeqTrack * pTrack = GetPlayerTrack(i);
					
					if (pTrack) pTrack->UpdateChannelParam();
				}
			}
			
			void SeqPlayer::Update()
			{
				SoundThread::AutoLock lock;
				
				if (!mActiveFlag) return;
				if (!mStartedFlag) return;
				
				if (OFFSET_0x9C || OFFSET_0xA0 > 0.0f) UpdateTick();
				else if (!mPauseFlag) UpdateTick(3);
				
				UpdateChannelParam();
			}
			
			//8003EEC4
			void SeqPlayer::UpdateTick(int ticks)
			{
				//8003EF1C
				float f1 = GetBaseTempo();
				
				if (0.0f == f1) return;
				
				//8003EF50
				float f2 = FLOAT_0x98 / f1;
				float f27 = ticks;
				
				while (f2 < f27) //8003F0CC
				{
					//8003EF74
					f27 -= f2;
					
					if (ParseNextTick(true))
					{
						FinishPlayer();
						return;
					}
					//8003F088
					INT_0x118++;
					
					f1 = GetBaseTempo();
					
					if (0.0f == f1) return;
					
					f2 = 1.0f / f1;
				}
				
				f2 -= f27;
				FLOAT_0x98 = f2 * f1;
				
				//8003F0E0 (END)
			}

			//8003F128
			void SeqPlayer::UpdateTick()
			{
				for (int i = 0; i < SEQ_TRACKS_PER_PLAYER; i++)
				{
					SeqTrack * pTrack = GetPlayerTrack(i);
					
					if (pTrack)
					{
						pTrack->ReleaseAllChannel(0x7F);
						pTrack->FreeAllChannel();
					}
				}
				//8003F1A8
				
				int r28 = 0;
				while (OFFSET_0x9C || OFFSET_0xA0 * GetBaseTempo() >= 1.0f) //8003F33C
				{
					//8003F1C0
					if (r28 >= 0x300) return;
					
					if (OFFSET_0x9C) OFFSET_0x9C--;
					else OFFSET_0xA0 -= 1.0f / GetBaseTempo();
					
					//8003F21C
					if (ParseNextTick(false))
					{
						FinishPlayer();
						return;
					}
					
					//8003F32C
					INT_0x118++;
					r28++;
				}
				//8003F388
				OFFSET_0xA0 = 0.0f;
				//END (8003F390)
			}
			
			bool SeqPlayer::NoteOn(int r_4, const NoteOnInfo & noteOnInfo)
			{
				return mNoteOnCallback->NoteOn(this, r_4, noteOnInfo);
			}
			
			bool SeqPlayer::mGobalVariableInitialized; // typo
			volatile s16 SeqPlayer::mGlobalVariable[SEQ_VARIABLE_COUNT];
		}
	}
}