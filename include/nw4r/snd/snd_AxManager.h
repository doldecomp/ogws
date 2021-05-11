#ifndef NW4R_SND_AXMANAGER_H
#define NW4R_SND_AXMANAGER_H
#include <ai.h>
#include <AX.h>
#include "types_nw4r.h"
#include "ut_LinkList.h"
#include "snd_MoveValue.h"

namespace nw4r
{
	namespace snd
	{
		enum AuxBus
		{
			AuxBus_A,
			AuxBus_B,
			AuxBus_C
		};
		
		enum OutputMode
		{
			OUTPUT_MODE_0,
			OUTPUT_MODE_1,
			OUTPUT_MODE_2,
			OUTPUT_MODE_3
		};
		
		namespace detail
		{
			//sizeof(AxManager) = 0x0000f4?
			struct AxManager
			{
				struct CallbackListNode
				{
					ut::LinkListNode mNode; // at 0x0
					AXCallback mCallback; // at 0x8
				};
				
				static AxManager * GetInstance();
				
				static void AxCallbackFunc();
				static void AuxCallbackFunc(void *, void *);
				static void AiDmaCallbackFunc();
				
				static u8 sZeroBuffer[0x100];
				
				AxManager();
				~AxManager();
				
				void Init();
				void Shutdown();
				
				float GetOutputVolume() const;
				
				UNKTYPE Update();
				u8 * GetZeroBufferAddress();
				
				void RegisterCallback(CallbackListNode *, AXCallback);
				void UnregisterCallback(CallbackListNode *);
				
				UNKTYPE SetOutputMode(OutputMode);
				OutputMode GetOutputMode();
				UNKTYPE SetMasterVolume(float, int);
				bool AppendEffect(AuxBus, FxBase *);
				void ClearEffect(AuxBus, int);
				void ShutdownEffect(AuxBus);
				void PrepareReset();
				
				OutputMode mOutputMode; // at 0x0
				u8 * mZeroBufferAddress; // at 0x4
				
				ut::LinkList<CallbackListNode, 0> mCallbackList; // from 0x8 to 0x10
				AXCallback mLastCallback; // at 0x14
				bool mPoweredFlag; // at 0x18
				bool BYTE_0x19;
				bool BYTE_0x1A;
				
				MoveValue<float, int> mOutputVolume; // at 0x1c
				MoveValue<float, int> MV_0x2C;
				MoveValue<float, int> MV_0x3C;
				
				AIDMACallback mAIDMACallback; // at 0x4c
				UNKWORD WORD_0x50;
				
				MoveValue<float, int> ARR_0x54[3];
				MoveValue<float, int> ARR_0x84[3];
				
				ut::LinkList<FxBase, 4> LIST_0xB4[3];
				
				AXAuxCallback ARR_0xD8[3];
				
				UNKWORD ARR_0xE4[3];
				
				char ARR_0xF0[3];
				
				inline ut::LinkList<FxBase, 4> * GetEffectList(AuxBus bus)
				{
					return LIST_0xB4 + bus;
				}
			};
		}
	}
}

#endif