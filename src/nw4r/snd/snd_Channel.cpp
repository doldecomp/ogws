#ifdef __DECOMP_NON_MATCHING
#pragma ipa file
#include <AXVPB.h>
#include "snd_Channel.h"
#include "snd_VoiceManager.h"
#include "ut_interrupt.h"
#include "ut_algorithm.h"

namespace nw4r
{
	namespace snd
	{
		using namespace ut;
		
		namespace detail
		{
			using namespace Util;
			//TODO
			template struct LinkList<Channel, 0xE4>;
			
			ChannelManager * ChannelManager::GetInstance()
			{
				static ChannelManager instance;
				
				return &instance;
			}
			
			ChannelManager::ChannelManager() : BOOL_0x10(), INT_0x14() {}
			
			u32 ChannelManager::GetRequiredMemSize()
			{
				return (AXGetMaxVoices() + 1) * sizeof(Channel);
			}
			
			void ChannelManager::Setup(void * r29_4, u32 r30_5)
			{
				AutoInterruptLock lock;
				
				if (BOOL_0x10) return;
				
				//POOL_0x0.Create
				INT_0x14 = mPool.Create(r29_4, r30_5);
				PTR_0x18 = r29_4;
				INT_0x1C = r30_5;
				BOOL_0x10 = true;
			}
			
			void ChannelManager::Free(Channel * pChannel)
			{
				ChannelManager * pManager;
				pManager = GetInstance();
				
				pManager->mList.Erase(pChannel);
				if (pChannel) pManager->mPool.Free(pChannel);
			}
			
			//8004C724: nw4r::snd::detail::Voice::Stop
			//8004C388: nw4r::snd::detail::Voice::Free
			//Channel::~Channel()
			
			void ChannelManager::Shutdown()
			{
				AutoInterruptLock lock;
				
				if (!BOOL_0x10) return;
				
				LinkList<Channel, 0xE4>::Iterator curIter = mList.GetBeginIter();
				
				while (mList.GetEndIter() != curIter)
				{
					curIter++->Stop();
				}
				
				mPool.Destroy(PTR_0x18, INT_0x1C);
				
				BOOL_0x10 = false;
			}
			
			UNKTYPE ChannelManager::UpdateAllChannel()
			{
				LinkList<Channel, 0xE4>::Iterator curIter = mList.GetBeginIter();
				
				while (mList.GetEndIter() != curIter)
				{
					curIter++->Update(true);
				}
			}
			
			UNKTYPE Channel::InitParam(ChannelCallback callback, u32 num)
			{
				// f0 = 0.0f
				// f2 = 1.0f
				// f1 = -90.4f
				WORD_0xE0 = 0;
				mCallback = callback;
				INT_0xD8 = num;
				BOOL_0x31 = false;
				mAutoUpdateSweepFlag = true;
				BOOL_0x35 = false;
				INT_0xC8 = 0;
				INT_0xC0 = 60;
				INT_0xC4 = 60;
				FLOAT_0xA8 = 1.0f;
				FLOAT_0xAC = 0.0f;
				FLOAT_0xB0 = 0.0f;
				FLOAT_0xB4 = 1.0f;
				FLOAT_0x38 = 1.0f;
				FLOAT_0x98 = 0.0f;
				FLOAT_0x3C = 1.0f;
				FLOAT_0x40 = 0.0f;
				FLOAT_0x44 = 0.0f;
				FLOAT_0x48 = 0.0f;
				mRemoteFilter = 0;
				mOutputLine = 1;
				FLOAT_0x54 = 1.0f;
				FLOAT_0x58 = 0.0f;
				/*
				FLOAT_0x5C = 0.0f;
				FLOAT_0x60 = 0.0f;
				FLOAT_0x64 = 0.0f;
				
				FLOAT_0x68 = 1.0f;
				FLOAT_0x78 = 0.0f;
				FLOAT_0x88 = 0.0f;
				
				FLOAT_0x6C = 1.0f;
				FLOAT_0x7C = 0.0f;
				FLOAT_0x8C = 0.0f;
				
				FLOAT_0x70 = 1.0f;
				FLOAT_0x80 = 0.0f;
				FLOAT_0x90 = 0.0f;
				
				FLOAT_0x74 = 1.0f;
				FLOAT_0x84 = 0.0f;
				FLOAT_0x94 = 0.0f;
				*/
				for (int i=0;i<3;i++)
				{
					ARR_0x5C[i] = 0.0f;
				}
				for (int i=0;i<4;i++)
				{
					ARR_0x68[i] = 1.0f;
					ARR_0x78[i] = 0.0f;
					ARR_0x88[i] = 0.0f;
				}
				
				MV_0xB8.InitValue(0xFF);
				
				FLOAT_0x9C = 0.0f;
				INT_0xA4 = 0;
				INT_0xA0 = 0;
				
				mEnvGenerator.Init(EnvGenerator::VOLUME_INIT);
				mLfo.mParam.Init();
				BYTE_0x30 = 0;
				mPanMode = PAN_MODE_0;
				mPanCurve = PAN_CURVE_0;
				//END
			}
			
			float Channel::GetSweepValue() const
			{
				return (0.0f == FLOAT_0x9C) ? 0.0f : (
					(INT_0xA0 >= INT_0xA4) ? 0.0f : FLOAT_0x9C * (INT_0xA0 - INT_0xA4) / INT_0xA4
				);
			}
			
			//8004E9CC: nw4r::snd::detail::Util::CalcVolumeRatio
			//8004E83C: nw4r::snd::detail::Util::CalcPitchRatio
			UNKTYPE Channel::Update(bool r31_4)
			{
				//return; <=> goto lbl_80037F9C;
				// r30 <- this
				if (!BOOL_0x32) return;
				//80037964
				if (BOOL_0x31) r31_4 = false;
				//80037974
				float f31 = mLfo.GetValue();
				MV_0xB8.Update();
				//80037998
				float f30 = 1.0f;
				f30 *= FLOAT_0xA8;
				f30 *= FLOAT_0x38;
				f30 *= MV_0xB8.GetValue() / 255.0f;
				float f29 = 1.0f;
				f29 *= CalcVolumeRatio(mEnvGenerator.GetValue());
				if (BYTE_0x30 == 1) f29 *= CalcVolumeRatio(6.0f * f31);
				//80037A2C
				if (mEnvGenerator.GetStatus() == EnvGenerator::Status_Release)
				{
					//80037A38
					if (mCallback)
					{
						//80037A44
						if (0.0f != f29)
						{
							//80037A50
							Stop();
							return;
						}
					}
					//80037B28
					else if (0.0f != f30 * f29)
					{
						Stop();
						return;
					}
				}
				//80037C10
				float f4 = 0.0f;
				f4 += INT_0xC0 - INT_0xC4;
				f4 += GetSweepValue();
				f4 += FLOAT_0x98;
				if (BYTE_0x30 == 0) f4 += f31;
				//80037CA8
				float f20 = 1.0f;
				f20 *= FLOAT_0xB4;
				f20 *= FLOAT_0x3C;
				//f0=0x100 * f4
				float f28 = CalcPitchRatio(256.0f * f4) * f20;
				float f27 = 0.0f;
				f27 += FLOAT_0xAC;
				f27 += FLOAT_0x40;
				if (BYTE_0x30 == 2) f27 += f31;
				//80037CFC
				{
				/**
				float flarr_0x38[3];
				
				float flarr_0x8[4];
				float flarr_0x18[4];
				float flarr_0x28[4];
				
				float f31 = 0.0f;
				float f8 = 0.0f;
				//f4=1.0f
				f31 += FLOAT_0xB0;
				float f26 = 0.0f;
				float f7 = f8 + FLOAT_0x5C;
				float f6 = f8 + FLOAT_0x60;
				float f5 = f8 + FLOAT_0x64;
				float f21 = f8 + FLOAT_0x7C;
				float f22 = f8 + FLOAT_0x8C;
				float f3 = FLOAT_0x68;
				float f2 = FLOAT_0x78;
				float f4 = 1.0f;
				float f25 = 1.0f;
				float f1 = FLOAT_0x88;
				float f0 = FLOAT_0x6C;
				float f23 = FLOAT_0x70;
				f2 += f8;
				float f13 = FLOAT_0x80;
				f1 += f8;
				float f12 = FLOAT_0x90;
				float f11 = FLOAT_0x74;
				float f10 = FLOAT_0x84;
				f23 *= f4;
				float f24 = FLOAT_0x48;
				f13 += f8;
				float f20 = FLOAT_0x44;
				f12 += f8;
				flarr_0x38[0] = f8;
				f11 *= f4;
				float f9
				flarr_0x38[1] = f8;
				flarr_0x38[2] = f8;
				f8 += f9;
				f9 = FLOAT_0x54;
				f3 *= f4;
				flarr_0x28[0] = f4;
				f31 += f20;
				f4 = FLOAT_0x58;
				f25 *= f9
				r29 = mRemoteFilter
				
				f24 += f4;
				
				flarr_0x38[0] = f7;
				flarr_0x38[1] = f6;
				flarr_0x38[2] = f5;
				
				flarr_0x28[0] = f3;
				flarr_0x18[0] = f2;
				flarr_0x8[0] = f1;
				
				flarr_0x28[1] = f0;
				flarr_0x18[1] = f21;
				flarr_0x8[1] = f22;
				
				flarr_0x28[2] = f23;
				flarr_0x18[2] = f13;
				flarr_0x8[2] = f12;
				
				flarr_0x28[3] = f11;
				flarr_0x18[3] = f10;
				flarr_0x8[3] = f8;
				**/
				float flarr_0x38[3] = { 0.0f, 0.0f, 0.0f };
				
				float flarr_0x28[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
				float flarr_0x18[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
				float flarr_0x8[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
				
				float f26 = 1.0f;
				float f25 = 1.0f;
				f26 += FLOAT_0x48;
				f25 *= FLOAT_0x54;
				float f24 = 0.0f;
				int r29 = mRemoteFilter;
				f24 += FLOAT_0x58;
				for (int i=0;i<3;i++)
				{
					flarr_0x38[i]+=ARR_0x5C[i];
				}
				
				for (int i=0;i<4;i++)
				{
					flarr_0x28[i]*=ARR_0x68[i];
					flarr_0x18[i]+=ARR_0x78[i];
					flarr_0x8[i]+=ARR_0x88[i];
				}
				if (r31_4)
				{
					//80037E0C
					if (mAutoUpdateSweepFlag) UpdateSweep(3);
					mLfo.Update(3);
					mEnvGenerator.Update(3);
					//80037E4C
				}
				//80037E4C
				float f23 = mLfo.GetValue();
				f20 = 1.0f;
				f20 *= CalcVolumeRatio(mEnvGenerator.GetValue());
				//80037E70
				if (BYTE_0x30 == 1) f20 *= CalcVolumeRatio(6.0f * f23);
				//80037E88
				if (!mVoice) return;
				//80037E94
				mVoice->SetPanMode(mPanMode);
				mVoice->SetPanCurve(mPanCurve);
				mVoice->SetVolume(f30);
				mVoice->SetVeVolume(f20, f29);
				mVoice->SetPitch(f28);
				mVoice->SetPan(f27);
				mVoice->SetSurroundPan(f31);
				mVoice->SetLpfFreq(f26);
				mVoice->SetRemoteFilter(r29);
				mVoice->SetOutputLine(mOutputLine);
				mVoice->SetMainOutVolume(f25);
				mVoice->SetMainSend(f24);
				for (int i = 0; i < 3; i++)
				{
					mVoice->SetFxSend((AuxBus)i, flarr_0x38[i]);
				}
				for (int i = 0; i < 4; i++)
				{
					mVoice->SetRemoteOutVolume(i, flarr_0x28[i]);
					mVoice->SetRemoteSend(i, flarr_0x18[i]);
					mVoice->SetRemoteFxSend(i, flarr_0x18[i]);
				}
				//80037F9C END
				}
			}
			
			UNKTYPE Channel::Start(const WaveData & r30_4, int r_5, u32 r31_6)
			{
				// r29 <- this
				
				INT_0xC8 = r_5;
				
				mLfo.Reset();
				mEnvGenerator.Reset(EnvGenerator::VOLUME_INIT);
				
				INT_0xA0 = 0;
				
				mVoice->Setup(r30_4, r31_6);
				mVoice->Start();
				
				BOOL_0x32 = true;
			}
			
			UNKTYPE Channel::Release()
			{
				if (mEnvGenerator.GetStatus() != EnvGenerator::Status_Release)
				{
					if (mVoice && !BOOL_0x35) mVoice->SetPriority(1);
					mEnvGenerator.SetStatus(EnvGenerator::Status_Release);
				}
				BOOL_0x31 = false;
			}
			
			UNKTYPE Channel::Stop()
			{
				if (!mVoice) return;
				
				mVoice->Stop();
				mVoice->Free();
				mVoice = NULL;
				
				BOOL_0x31 = false;
				BOOL_0x32 = false;
				
				if (BOOL_0x33)
				{
					//80038154
					BOOL_0x33 = false;
					ChannelManager::Free(this);
				}
				//800381D4
				if (mCallback) mCallback(this, CALLBACK_STATUS_0, INT_0xD8);
			}
			
			void Channel::UpdateSweep(int r4)
			{
				if ((INT_0xA0 += r4) > INT_0xA4) INT_0xA0 = INT_0xA4;
			}
			
			void Channel::SetSweepParam(float f1, int r4, bool r5)
			{
				FLOAT_0x9C = f1;
				INT_0xA4 = r4;
				mAutoUpdateSweepFlag = r5;
				INT_0xA0 = 0;
			}
			
			void Channel::VoiceCallbackFunc(Voice * pVoice, Voice::VoiceCallbackStatus voiceStatus, void * ptr)
			{
				//not saved <- pVoice
				Channel * pChannel = static_cast<Channel *>(ptr); // at r30
				
				ChannelCallbackStatus channelStatus;
				
				switch (voiceStatus)
				{
					case Voice::STATUS_0:
						channelStatus = CALLBACK_STATUS_2;
						pVoice->Free();
						break;
					case Voice::STATUS_1:
						channelStatus = CALLBACK_STATUS_3;
						pVoice->Free();
						break;
					case Voice::STATUS_2:
						channelStatus = CALLBACK_STATUS_1;
						break;
					case Voice::STATUS_3:
						channelStatus = CALLBACK_STATUS_1;
						break;
				}
				//800382A8
				if (pChannel->mCallback) pChannel->mCallback(pChannel, channelStatus, pChannel->INT_0xD8);
				pChannel->mVoice = NULL;
				pChannel->BOOL_0x31 = false;
				pChannel->BOOL_0x32 = false;
				pChannel->BOOL_0x33 = false;
				
				ChannelManager::Free(pChannel);
			}
			
			//...
			/*
			 *
			 * 8004E358
			 * AllocVoice__Q44nw4r3snd6detail12VoiceManagerFiiiPFPQ44nw4r3snd6detail5VoiceQ54nw4r3snd6detail5Voice19VoiceCallbackStatusPv_vPv
			 * nw4r::snd::detail::VoiceManager::AllocVoice(int, int, int, Voice::VoiceCallback, void *)
			 *
			 */
			Channel * ChannelManager::Alloc()
			{
				Channel * pChannel = mPool.Alloc();
				mList.PushBack(pChannel);
				return pChannel;
			}
			
			Channel::Channel() :
				BYTE_0x30(),
				BOOL_0x31(false),
				BOOL_0x32(false),
				BOOL_0x33(false),
				MV_0xB8(),
				mVoice(NULL),
				mNode()
			{}
			
			Channel * Channel::AllocChannel(int r24_3, int r25_4, int r26_5, ChannelCallback callback, u32 r28_7)
			{
				// r27 <- callback
				Channel * pChannel = ChannelManager::GetInstance()->Alloc();
				
				if (!pChannel) return NULL;
				
				//80038488
				pChannel->BOOL_0x33 = true;
				
				Voice * pVoice = VoiceManager::GetInstance()->AllocVoice(r24_3, r25_4, r26_5, VoiceCallbackFunc, pChannel);
				
				if (!pVoice)
				{
					ChannelManager::Free(pChannel);
					return NULL;
				}
				
				pChannel->mVoice = pVoice;
				pChannel->InitParam(callback, r28_7);
				
				return pChannel;
			}
			
			void Channel::FreeChannel(Channel * pChannel)
			{
				if (!pChannel) return;
				
				pChannel->mCallback = NULL;
				pChannel->INT_0xD8 = 0;
			}
		}
	}
}
#else
#error This file has yet to be decompiled accurately. Use "snd_Channel.s" instead.
#endif