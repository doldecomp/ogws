#include <string.h>
#include <ai.h>
#include <dvd.h>
#include <OSCache.h>
#include <AXAux.h>
#include <AXOut.h>
#include <AXCL.h>
#include <AXVPB.h>
#include "ut_Lock.h"
#include "ut_algorithm.h"
#include "snd_VoiceManager.h"
#include "snd_AxManager.h"
#include "snd_FxBase.h"

namespace nw4r
{
	using namespace ut;
	namespace snd
	{
		namespace detail
		{
			u8 AxManager::sZeroBuffer[0x100];
			
			template struct LinkList<AxManager::CallbackListNode,0>;
			
			AxManager::AxManager() :
				mOutputMode(OUTPUT_MODE_0),
				mZeroBufferAddress(),
				mCallbackList(),
				mPoweredFlag(false),
				BYTE_0x19(true),
				BYTE_0x1A(false),
				mAIDMACallback(),
				WORD_0x50(-1)
			{
				MV_0x2C.InitValue(1.0f);
				mOutputVolume.InitValue(1.0f);
				MV_0x3C.InitValue(1.0f);
				
				for (int i = 0; i < 3; i++)
				{
					ARR_0x54[i].InitValue(1.0f);
					ARR_0x84[i].InitValue(1.0f);
					ARR_0xD8[i] = 0;
					ARR_0xE4[i] = 0;
				}
			}
			
			template struct LinkList<FxBase,4>;
			
			AxManager * AxManager::GetInstance()
			{
				static AxManager instance;
				
				return &instance;
			}
			
			AxManager::~AxManager() {}
			
			void AxManager::Init()
			{
				if (!mPoweredFlag)
				{
					memset(sZeroBuffer, 0, sizeof(sZeroBuffer));
					DCFlushRange(sZeroBuffer, sizeof(sZeroBuffer));
					mZeroBufferAddress = sZeroBuffer;
					
					AutoInterruptLock lock;
					
					AXGetAuxACallback(ARR_0xD8, ARR_0xE4);
					AXGetAuxBCallback(ARR_0xD8 + 1, ARR_0xE4 + 1);
					AXGetAuxCCallback(ARR_0xD8 + 2, ARR_0xE4 + 2);
					
					AXRegisterAuxACallback(NULL, 0);
					AXRegisterAuxBCallback(NULL, 0);
					AXRegisterAuxCCallback(NULL, 0);
					
					mLastCallback = AXRegisterCallback(AxCallbackFunc);
					
					mPoweredFlag = true;
				}
			}
			
			void AxManager::Shutdown()
			{
				if (mPoweredFlag)
				{
					AXRegisterCallback(mLastCallback);
					
					ShutdownEffect(AuxBus_A);
					ShutdownEffect(AuxBus_B);
					ShutdownEffect(AuxBus_C);
					
					AXRegisterAuxACallback(ARR_0xD8[0], ARR_0xE4[0]);
					AXRegisterAuxBCallback(ARR_0xD8[1], ARR_0xE4[1]);
					AXRegisterAuxCCallback(ARR_0xD8[2], ARR_0xE4[2]);
					
					for (int i = 0; i < 3; i++)
					{
						ARR_0xD8[i] = 0;
						ARR_0xE4[i] = 0;
					}
					
					mZeroBufferAddress = NULL;
					
					mPoweredFlag = false;
				}
			}
			
			float AxManager::GetOutputVolume() const
			{
				return mOutputVolume.GetValue();
			}
			
			UNKTYPE AxManager::Update()
			{
				if (DVDGetDriveStatus() <= 1)
				{
					//80031600
					if (BYTE_0x1A)
					{
						BYTE_0x1A = false;
						VoiceManager::GetInstance()->UpdateAllVoicesSync(0x2);
					}
				}
				else
				{
					//80031624
					if (!BYTE_0x1A)
					{
						BYTE_0x1A = true;
						VoiceManager::GetInstance()->UpdateAllVoicesSync(0x2);
					}
				}
				//80031644
				for (int i = 0; i < 3; i++)
				{
					//r29 = this
					//r30 = i
					//r31 = this->???[i]
					//f28 = 1.0f
					//f29 = 0.0f
					//f30 = 32768.0f
					//f31 = signed int2float conv const
					//8003165c
					bool r4 = false;
					if (!ARR_0x84[i].IsFinished())
					{
						ARR_0x84[i].Update();
						r4 = true;
					}
					if (!ARR_0x54[i].IsFinished())
					{
						ARR_0x54[i].Update();
						if (ARR_0x54[i].IsFinished()) ShutdownEffect((AuxBus)i);
						r4 = true;
					}
					if (r4)
					{
						//800316DC
						float f4 = 1.0f;
						f4 *= Clamp<float>(0.0f, 1.0f, ARR_0x84[i].GetValue());
						f4 *= Clamp<float>(0.0f, 1.0f, ARR_0x54[i].GetValue());
						u16 auxRetVolume = f4 * 0x8000;
						//800317D0
						switch (i) // loop-switch anti-pattern
						{
							case AuxBus_A:
								//800317F4
								AXSetAuxAReturnVolume(auxRetVolume);
								break;
							case AuxBus_B:
								//80031800
								AXSetAuxBReturnVolume(auxRetVolume);
								break;
							case AuxBus_C:
								//8003180C
								AXSetAuxCReturnVolume(auxRetVolume);
								break;
						}
						//80031814
					}
					//CONTINUE
				}
				//80031824
				if (!mOutputVolume.IsFinished())
				{
					mOutputVolume.Update();
					VoiceManager::GetInstance()->UpdateAllVoicesSync(0x8);
				}
				//80031858
				if (!MV_0x3C.IsFinished())
				{
					MV_0x3C.Update();
				}
				//80031880
				if (!MV_0x2C.IsFinished())
				{
					MV_0x2C.Update();
				}
				//80031978
				AXSetMasterVolume(0x8000 * Clamp<float>(0.0f, 1.0f, MV_0x2C.GetValue() * MV_0x3C.GetValue()));
				//END
			}
			
			u8 * AxManager::GetZeroBufferAddress()
			{
				return mZeroBufferAddress;
			}
			
			void AxManager::RegisterCallback(CallbackListNode * pNode, AXCallback callback)
			{
				AutoInterruptLock lock;
				
				pNode->mCallback = callback;
				
				mCallbackList.PushBack(pNode);
			}
			
			void AxManager::UnregisterCallback(CallbackListNode * pNode)
			{
				AutoInterruptLock lock;
				
				mCallbackList.Erase(pNode);
			}
			
			UNKTYPE AxManager::SetOutputMode(OutputMode mode)
			{
				mOutputMode = mode;
				
				switch (mode)
				{
					case OUTPUT_MODE_0:
						AXSetMode(0);
						break;
					case OUTPUT_MODE_1:
						AXSetMode(1);
						break;
					case OUTPUT_MODE_2:
						AXSetMode(2);
						break;
					case OUTPUT_MODE_3:
						AXSetMode(0);
						break;
				}
				
				VoiceManager::GetInstance()->UpdateAllVoicesSync(0x10);
			}
			
			OutputMode AxManager::GetOutputMode()
			{
				return mOutputMode;
			}
			
			UNKTYPE AxManager::SetMasterVolume(float f, int i)
			{
				/*
				float f5 = Clamp<float>(0.0f, 1.0f, f);
				
				mOutputVolume.T1_0x0 = mOutputVolume.GetValue();
				mOutputVolume.T1_0x4 = f5;
				mOutputVolume.T2_0xC = 0;
				mOutputVolume.T2_0x8 = i / 3;
				*/
				
				mOutputVolume.SetTarget(Clamp<float>(0.0f, 1.0f, f), (i + 2) / 3);
				
				if (!i) VoiceManager::GetInstance()->UpdateAllVoicesSync(0x8);
			}
			
			void AxManager::AxCallbackFunc()
			{
				LinkList<CallbackListNode, 0>::Iterator it = GetInstance()->mCallbackList.GetBeginIter();
				
				while (it != GetInstance()->mCallbackList.GetEndIter())
				{
					it++->mCallback();
				}
				
				if (GetInstance()->mLastCallback) GetInstance()->mLastCallback();
			}
			
			bool AxManager::AppendEffect(AuxBus bus, FxBase * pEffect)
			{
				if (!ARR_0x54[bus].IsFinished()) ShutdownEffect(bus);
				
				ARR_0x54[bus].SetTarget(1.0f, 0);
				
				switch (bus)
				{
					case AuxBus_A:
						AXSetAuxAReturnVolume(0x8000);
						break;
					case AuxBus_B:
						AXSetAuxBReturnVolume(0x8000);
						break;
					case AuxBus_C:
						AXSetAuxCReturnVolume(0x8000);
						break;
				}
				//80031E78
				if (!pEffect->StartUp()) return false;
				
				AutoInterruptLock lock;
				
				if (!LIST_0xB4[bus].mCount)
				{
					switch (bus)
					{
						case AuxBus_A:
							AXRegisterAuxACallback(AuxCallbackFunc, bus);
							break;
						case AuxBus_B:
							AXRegisterAuxBCallback(AuxCallbackFunc, bus);
							break;
						case AuxBus_C:
							AXRegisterAuxCCallback(AuxCallbackFunc, bus);
							break;
					}
					ARR_0xF0[bus] = 2;
				}
				
				LIST_0xB4[bus].PushBack(pEffect);
				
				return true;
			}
			
			void AxManager::ClearEffect(AuxBus bus, int time)
			{
				if (!time) ShutdownEffect(bus);
				else ARR_0x54[bus].SetTarget(0.0f, (time + 2) / 3);
			}
			
			void AxManager::ShutdownEffect(AuxBus bus)
			{
				AutoInterruptLock lock;
				
				LinkList<FxBase, 4> * fxList = GetEffectList(bus);
				
				if (!fxList->mCount) return;
				
				LinkList<FxBase, 4>::Iterator it = fxList->GetBeginIter();
				
				while (it != fxList->GetEndIter())
				{
					it->Shutdown();
					it++;
				}
				
				fxList->Clear();
				
				switch (bus)
				{
					case AuxBus_A:
						AXRegisterAuxACallback(NULL, 0);
						break;
					case AuxBus_B:
						AXRegisterAuxBCallback(NULL, 0);
						break;
					case AuxBus_C:
						AXRegisterAuxCCallback(NULL, 0);
						break;
				}
			}
			
			#ifdef __DECOMP_NON_MATCHING
			void AxManager::AuxCallbackFunc(void * arg1, void * arg2)
			{
				int len;
				void * arrPtr[4];
				
				void ** ptrs = (void **)arg1;
				AuxBus bus = (AuxBus)arg2;

				if (GetInstance()->mOutputMode == 2)
				{
					//80032174
					len = 4;
					arrPtr[0] = ptrs[0];
					arrPtr[1] = ptrs[1];
					arrPtr[2] = ptrs[2];
					arrPtr[3] = ptrs[3];
				}
				else
				{
					//8003219C
					len = 3;
					arrPtr[0] = ptrs[0];
					arrPtr[1] = ptrs[1];
					arrPtr[2] = ptrs[2];
				}
				//800321B8
				if (GetInstance()->ARR_0xF0[bus])
				{
					//80032208
					GetInstance()->ARR_0xF0[bus]--;
					
					for (int i = 0; i < len; i++)
					{
						memset(arrPtr[i], 0, 0x180);
					}
				}
				//80032278
				else if (!GetInstance()->LIST_0xB4[bus].mCount)
				{
					for (int i = 0; i < len; i++)
					{
						memset(arrPtr[i], 0, 0x180);
					}
				}
				//800322F8
				else
				{
					//8003232C
					LinkList<FxBase, 4>::Iterator it = GetInstance()->LIST_0xB4[bus].GetBeginIter();
					
					while (it != GetInstance()->LIST_0xB4[bus].GetEndIter())
					{
						it++->UpdateBuffer(len, arrPtr, 0x180, SAMPLE_FORMAT_0, 32000.0f, GetInstance()->mOutputMode);
					}
					
					//END
				}
				
				//800323D0 (END)
			}
			#else
			#error This file has yet to be decompiled accurately. Use "snd_AxManager.s" instead.
			#endif

			void AxManager::PrepareReset()
			{
				if (mAIDMACallback)
				{
					MV_0x3C.SetTarget(0.0f, 3);
					WORD_0x50 = -1;
					mAIDMACallback = AIRegisterDMACallback(AiDmaCallbackFunc);
				}
			}
			
			void AxManager::AiDmaCallbackFunc()
			{
				static bool finishedFlag;
				AxManager * pInstance = GetInstance();
				
				pInstance->mAIDMACallback();
				
				if (finishedFlag)
				{
					if (pInstance->WORD_0x50 < 0)
					{
						AXSetMaxDspCycles(0);
						pInstance->WORD_0x50 = 6;
					}
				}
				else
				{
					if (0.0f != pInstance->MV_0x3C.GetValue()) finishedFlag = true;
				}
				
				// if (pInstance->WORD_0x50 > 0) pInstance->WORD_0x50--; 
				if (pInstance->WORD_0x50 > 0) const_cast<volatile AxManager *>(pInstance)->WORD_0x50--;
			}
		}
	}
}