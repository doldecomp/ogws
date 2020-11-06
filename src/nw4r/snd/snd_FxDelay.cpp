#pragma ipa file
#include "snd_FxDelay.h"
#include "ut_algorithm.h"

namespace nw4r
{
	using namespace ut;
	
	namespace snd
	{
		using namespace detail;
		
		FxDelay::FxDelay()
		{
			DelayParam delayParam = { 160.0f, 0.4f, 1.0f }; // at 0x10
			SetParam(delayParam);
		}
		
		u32 FxDelay::GetRequiredMemSize()
		{
			return RoundUp<u32>(AXFXDelayGetMemSize(&mAXFXDelay) + 0x68, 0x20);
		}
		
		UNKTYPE FxDelay::AssignWorkBuffer(void * r4, u32 r5)
		{
			mAxfxImpl.CreateHeap(r4, r5);
		}
		
		UNKTYPE FxDelay::ReleaseWorkBuffer()
		{
			mAxfxImpl.DestroyHeap();
		}
		
		bool FxDelay::StartUp()
		{
			u32 req = GetRequiredMemSize();
			if (req > mAxfxImpl.GetHeapTotalSize()) return false;
			
			AXFXAllocHook allocHook; // at 0xc
			AXFXFreeHook freeHook; // at 0x8
			
			mAxfxImpl.HookAlloc(&allocHook, &freeHook);
			
			mAxfxImpl.mAllocatedSize = 0;
			
			UNKWORD ret = AXFXDelayInit(&mAXFXDelay);
			
			mAxfxImpl.RestoreAlloc(allocHook, freeHook);
			
			AXFXDelayGetMemSize(&mAXFXDelay);
			
			mAxfxImpl.mPoweredFlag = true;
			
			return ret;
		}
		
		UNKTYPE FxDelay::Shutdown()
		{
			if (!mAxfxImpl.mPoweredFlag) return;
			
			mAxfxImpl.mPoweredFlag = false;
			
			AXFXAllocHook allocHook; // at 0xc
			AXFXFreeHook freeHook; // at 0x8
			
			mAxfxImpl.HookAlloc(&allocHook, &freeHook);
			
			AXFXDelayShutdown(&mAXFXDelay);
			
			mAxfxImpl.RestoreAlloc(allocHook, freeHook);
		}
		
		bool FxDelay::SetParam(const DelayParam & param)
		{
			mParam = param;
			
			INT_0x64 = INT_0x68 = INT_0x6C = Clamp<u32>(1, 5000, param.FLOAT_0x0);
			INT_0x70 = INT_0x74 = INT_0x78 = Clamp<u32>(0, 99, 100.0f * param.FLOAT_0x4);
			INT_0x7C = INT_0x80 = INT_0x84 = Clamp<u32>(0, 100, 100.0f * param.FLOAT_0x8);
			
			if (!mAxfxImpl.mPoweredFlag) return true;
			
			u32 req = GetRequiredMemSize();
			if (req > mAxfxImpl.GetHeapTotalSize()) return false;
			
			AXFXAllocHook allocHook; // at 0xc
			AXFXFreeHook freeHook; // at 0x8
			
			mAxfxImpl.HookAlloc(&allocHook, &freeHook);
			
			UNKWORD ret = AXFXDelaySettings(&mAXFXDelay);
			
			mAxfxImpl.RestoreAlloc(allocHook, freeHook);
			
			return ret;
		}
		
		UNKTYPE FxDelay::UpdateBuffer(int, void ** r_5, u32, SampleFormat, float, OutputMode)
		{
			void * r_3[3];
			r_3[0] = r_5[0];
			r_3[1] = r_5[1];
			r_3[2] = r_5[2];
			AXFXDelayCallback(r_3, &mAXFXDelay);
		}
	}
}