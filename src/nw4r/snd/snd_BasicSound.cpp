#ifdef __DECOMP_NON_MATCHING
#include "types_nw4r.h"
#include "ut_algorithm.h"
#include "snd_BasicSound.h"
#include "snd_ExternalSoundPlayer.h"
#include "snd_SoundPlayer.h"
#include "snd_SoundHandle.h"

namespace nw4r
{
	namespace snd
	{
		using namespace ut;
		
		namespace detail
		{
			BasicSound::BasicSound() :
				WORD_0x4(),
				mGeneralHandle(NULL),
				mTempGeneralHandle(NULL),
				mSoundPlayer(NULL),
				mExternalSoundPlayer(NULL),
				mAmbientParamUpdateCallback(NULL),
				mAmbientArgUpdateCallback(NULL),
				mAmbientArgAllocaterCallback(NULL),
				PTR_0x24(NULL),
				MV_0x44(),
				MV_0x54(),
				mId(-1),
				mVolume(),
				WORD_0xB8(),
				WORD_0xBC(),
				WORD_0xC0(),
				WORD_0xC4(),
				WORD_0xC8(),
				WORD_0xCC(),
				WORD_0xD0(),
				WORD_0xD4()
			{}
			
			UNKTYPE BasicSound::InitParam()
			{
				mPauseFlag = false;
				BOOL_0x68 = false;
				BOOL_0x64 = false;
				BOOL_0x65 = false;
				BOOL_0x66 = false;
				BOOL_0x69 = false;
				mAutoStopCounter = 0;
				WORD_0x70 = 0;
				MV_0x44.InitValue(0.0f);
				MV_0x54.InitValue(1.0f);
				MV_0x44.SetTarget(1.0f, 1);
				//800363CC
				mInitialVolume = 1.0f;
				mPitch = 1.0f;
				mPan = 0.0f;
				mSurroundPan = 0.0f;
				mVolume.InitValue(1.0f);
				mOutputLine = 1;
				BOOL_0x9C = 0;
				mMainOutVolume = 1.0f;
				mRemoteOutVolumes[0] = 1.0f;
				mRemoteOutVolumes[1] = 1.0f;
				mRemoteOutVolumes[2] = 1.0f;
				mRemoteOutVolumes[3] = 1.0f;
				mParam.FLOAT_0x0 = 1.0f;
				mParam.FLOAT_0x4 = 1.0f;
				mParam.FLOAT_0x8 = 0.0f;
				mParam.FLOAT_0xC = 0.0f;
				mParam.FLOAT_0x10 = 0.0f;
				mParam.FLOAT_0x14 = 0.0f;
				mParam.WORD_0x18 = 0;
			}
			
			UNKTYPE BasicSound::StartPrepared()
			{
				if (BOOL_0x65) BOOL_0x64 = 1;
			}
			
			UNKTYPE BasicSound::Stop(int num)
			{
				//r29 <- this
				//r30 <- num
				
				BasicPlayer * pPlayer = GetBasicPlayer(); // at r31
				
				if (!num || !pPlayer->IsActive() || !pPlayer->IsStarted() || pPlayer->IsPause())
				{
					//800364DC
					Shutdown();
					//END
				}
				else
				{
					////800364F4
					//float MVAL_0 = MV_0x44.GetValue();
					////80036548
					int r6 = num * MV_0x44.GetValue();
					//80036570
					MV_0x44.SetTarget(0.0f, r6);
					//800365D4
					SetPlayerPriority(0);
					BOOL_0x66 = false;
					mPauseFlag = false;
					BOOL_0x68 = false;
					BOOL_0x69 = true;
					//END
				}
				//800365F8
				//END
			}
			
			UNKTYPE BasicSound::Pause(bool r31_4, int r29_5)
			{
				// r30 <- this
				BasicPlayer * pPlayer = GetBasicPlayer();
				
				if (r31_4)
				{
					//8003665C
					int r5 = r29_5 * MV_0x54.GetValue();
					BOOL_0x68 = true;
					if (r5 <= 0) r5 = 1;
					MV_0x54.SetTarget(0.0f, r5);
					//END
				}
				else
				{
					//80036758
					if (mPauseFlag != r31_4) pPlayer->Pause(false);
					//80036778
					int r5 = r29_5 * (1.0f - MV_0x54.GetValue());
					//800367CC
					BOOL_0x68 = true;
					if (r5 <= 0) r5 = 1;
					MV_0x54.SetTarget(0.0f, r5);
				}
				mPauseFlag = r31_4;
				//END
			}
			
			UNKTYPE BasicSound::SetAutoStopCounter(int asc)
			{
				mAutoStopCounter = asc;
				BOOL_0x66 = asc;
			}
			
			UNKTYPE BasicSound::FadeIn(int r_4)
			{
				if (BOOL_0x69) return;
				
				int time = r_4 * (1.0f - MV_0x44.GetValue());
				
				MV_0x44.SetTarget(1.0f, time);
			}
			
			bool BasicSound::IsPause() const
			{
				return mPauseFlag;
			}
			
			UNKTYPE BasicSound::Update()
			{
				// r29 <- this
				
				BasicPlayer * pPlayer = GetBasicPlayer(); // at r31
				//80036A20
				if (BOOL_0x66 && pPlayer->IsActive())
				{
					//80036A48
					if (!mAutoStopCounter)
					{
						Stop(0);
						return;
					}
					//80036A70
					mAutoStopCounter--;
				}
				//80036A78
				bool r30 = false;
				
				if (!BOOL_0x65)
				{
					//if (!BOOL_0x64 || !IsPrepared()) return;
					if (!BOOL_0x64) return;
					if (!IsPrepared()) return;
					
					r30 = true;
				}
				//80036AB4
				if (pPlayer->IsStarted() && WORD_0x70 < -1) WORD_0x70++;
				//80036AE8
				if (!pPlayer->IsActive())
				{
					Shutdown();
					return;
				}
				//80036B1C
				if (pPlayer->IsPause()) return;
				//80036B38
				if (BOOL_0x68)
				{
					MV_0x54.Update();
					//END
				}
				else
				{
					MV_0x44.Update();
					mVolume.Update();
					//END
				}
				//80036B90
				if (mAmbientArgUpdateCallback) mAmbientArgUpdateCallback->detail_Update(PTR_0x24, this);
				//80036BB4
				if (mAmbientParamUpdateCallback) mAmbientParamUpdateCallback->detail_Update(&mParam, mId, this, PTR_0x24, -1);
				//80036BE4
				float f31 = 1.0f;
				f31 *= mInitialVolume;
				f31 *= mSoundPlayer->FLOAT_0x28;
				if (mExternalSoundPlayer) f31 *= mExternalSoundPlayer->FLOAT_0x10;
				//80036C10
				f31 *= mVolume.GetValue();
				f31 *= MV_0x44.GetValue();
				f31 *= MV_0x54.GetValue();
				//80036D14
				int r26 = 1;
				
				float f29 = 0.0f;
				//f2=FLOAT_0x28
				float f28 = 0.0f;
				f29+=mPan;
				float f26 = 1.0f;
				f31*=mParam.FLOAT_0x0;
				f28+=mSurroundPan;
				f29+=mParam.FLOAT_0x8;
				float f27 = 1.0f;
				f26*=mSoundPlayer->FLOAT_0x34;
				f28+=mParam.FLOAT_0xC;
				f26*=mMainOutVolume;
				f27*=mPitch;
				
				if (mSoundPlayer->detail_IsEnabledOutputLine()) r26 = mSoundPlayer->detail_GetOutputLine();
				if (BOOL_0x9C) r26 = mOutputLine;
				//80036D94
				float remoteOutputVolumes[4]; // at 0x8
				
				for (int r25 = 0; r25 < 4; r25++)
				{
					remoteOutputVolumes[r25] = 1.0f;
					remoteOutputVolumes[r25] *= mSoundPlayer->detail_GetRemoteOutVolume(r25);
					remoteOutputVolumes[r25] *= mRemoteOutVolumes[r25];
				}
				//80036DDC
				pPlayer->FLOAT_0x8 = f31;
				pPlayer->FLOAT_0x10 = f29;
				pPlayer->FLOAT_0x14 = f28;
				pPlayer->FLOAT_0xC = f27;
				pPlayer->WORD_0x20 = r26;
				pPlayer->FLOAT_0x24 = f26;
				//80036DFC
				for (int r25 = 0; r25 < 4; r25++)
				{
					pPlayer->SetRemoteOutVolume(r25, remoteOutputVolumes[r25]);
				}
				//80036E1C
				if (BOOL_0x69 && MV_0x44.IsFinished())
				{
					BOOL_0x69 = false;
					Shutdown();
					return;
				}
				//80036E58
				if (BOOL_0x68 && MV_0x54.IsFinished())
				{
					BOOL_0x68 = false;
					if (mPauseFlag) pPlayer->Pause(mPauseFlag);
				}
				//80036E9C
				if (r30 && pPlayer->Start())
				{
					BOOL_0x65 = true;
					BOOL_0x64 = false;
				}
				//END
			}
			
			UNKTYPE BasicSound::Shutdown()
			{
				BasicPlayer * pPlayer = GetBasicPlayer();
				if (pPlayer->IsActive())
				{
					//80036F5C
					if (BOOL_0x69) pPlayer->FLOAT_0x8 = 0.0f;
					pPlayer->Stop();
				}
				//80036F84
				mId = -1;
				GetBasicPlayer()->mId = -1;
				if (mGeneralHandle) mGeneralHandle->DetachSound();
				if (mTempGeneralHandle) mTempGeneralHandle->DetachSound();
				//80036FC4
				if (IsAttachedTempSpecialHandle()) DetachTempSpecialHandle();
				//80036FF4
				if (WORD_0x4) mSoundPlayer->detail_FreePlayerHeap(this);
				mSoundPlayer->detail_RemovePriorityList(this);
				mSoundPlayer->detail_RemoveSoundList(this);
				if (mExternalSoundPlayer) mExternalSoundPlayer->RemoveSoundList(this);
				if (mAmbientArgAllocaterCallback)
				{
					mAmbientArgAllocaterCallback->detail_FreeAmbientArg(PTR_0x24, this);
					PTR_0x24 = NULL;
				}
				BOOL_0x65 = false;
				BOOL_0x69 = false;
			}
			
			UNKTYPE BasicSound::SetPlayerPriority(int priority)
			{
				mPlayerPriority = priority;
				
				if (!mSoundPlayer) return;
				
				mSoundPlayer->detail_RemovePriorityList(this);
				mSoundPlayer->detail_InsertPriorityList(this);
			}
			
			UNKTYPE BasicSound::SetInitialVolume(float initVol)
			{
				mInitialVolume = Clamp<float>(initVol, 0.0f, 1.0f);
			}
			
			UNKTYPE BasicSound::SetVolume(float targetVol, int time)
			{
				mVolume.SetTarget(Clamp<float>(targetVol, 0.0f, 1.0f), time);
			}
			
			UNKTYPE BasicSound::SetPitch(float pitch)
			{
				mPitch = pitch;
			}
			
			UNKTYPE BasicSound::SetPan(float pan)
			{
				mPan = pan;
			}
			
			UNKTYPE BasicSound::SetSurroundPan(float surroundPan)
			{
				mSurroundPan = surroundPan;
			}
			
			UNKTYPE BasicSound::SetLpfFreq(float lpfFreq)
			{
				GetBasicPlayer()->mLpfFreq = lpfFreq;
			}
			
			UNKTYPE BasicSound::SetOutputLine(int outputLine)
			{
				mOutputLine = outputLine;
				BOOL_0x9C = true;
			}
			UNKTYPE BasicSound::SetMainOutVolume(float mainOutVolume)
			{
				mMainOutVolume = Clamp<float>(mainOutVolume, 0.0f, 1.0f);
			}
			
			UNKTYPE BasicSound::SetRemoteOutVolume(int i, float remoteOutVolume)
			{
				mRemoteOutVolumes[i] = Clamp<float>(remoteOutVolume, 0.0f, 1.0f);
			}
			
			UNKTYPE BasicSound::SetFxSend(AuxBus bus, float f)
			{
				GetBasicPlayer()->SetFxSend(bus, f);
			}
			
			UNKTYPE BasicSound::SetRemoteFilter(int remoteFilter)
			{
				GetBasicPlayer()->mRemoteFilter = remoteFilter > 0x7F ? 0x7F : remoteFilter & ~(remoteFilter < 0);
			}
			
			UNKTYPE BasicSound::SetPanMode(PanMode panMode)
			{
				GetBasicPlayer()->mPanMode = panMode;
			}
			
			UNKTYPE BasicSound::SetPanCurve(PanCurve panCurve)
			{
				GetBasicPlayer()->mPanCurve = panCurve;
			}
			
			UNKTYPE BasicSound::SetAmbientParamCallback(AmbientParamUpdateCallback * paramUpdate, AmbientArgUpdateCallback * argUpdate, AmbientArgAllocaterCallback * alloc, void * ptr)
			{
				mAmbientParamUpdateCallback = paramUpdate;
				mAmbientArgUpdateCallback = argUpdate;
				mAmbientArgAllocaterCallback = alloc;
				PTR_0x24 = ptr;
			}
			
			bool BasicSound::IsAttachedGeneralHandle()
			{
				return mGeneralHandle;
			}
			
			bool BasicSound::IsAttachedTempGeneralHandle()
			{
				return mTempGeneralHandle;
			}
			
			UNKTYPE BasicSound::DetachGeneralHandle()
			{
				mGeneralHandle->DetachSound();
			}
			
			UNKTYPE BasicSound::DetachTempGeneralHandle()
			{
				mTempGeneralHandle->DetachSound();
			}
			
			UNKTYPE BasicSound::SetId(u32 id)
			{
				mId = id;
				GetBasicPlayer()->mId = id;
			}
			
			ut::detail::RuntimeTypeInfo BasicSound::typeInfo(NULL);
		}
	}
}
#else
#error This file has yet to be decompiled accurately. Use "snd_BasicSound.s" instead.
#endif