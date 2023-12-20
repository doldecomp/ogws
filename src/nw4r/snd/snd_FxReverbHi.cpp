#pragma ipa file
#include "snd_FxReverbHi.h"
#include "ut_algorithm.h"

namespace nw4r
{
	using namespace ut;
	
	namespace snd
	{
		using namespace detail;
		
		FxReverbHi::FxReverbHi()
		{
			ReverbHiParam reverbHiParam = { 0.02f, 3.0f, 0.6f, 0.4f, 0.1f, 1.0f }; // at 0x10
			SetParam(reverbHiParam);
		}
		
		u32 FxReverbHi::GetRequiredMemSize()
		{
			return RoundUp<u32>(AXFXReverbHiGetMemSize(&mAXFXReverbHi) + 0x68, 0x20);
		}
		
		UNKTYPE FxReverbHi::AssignWorkBuffer(void * r4, u32 r5)
		{
			mAxfxImpl.CreateHeap(r4, r5);
		}
		
		UNKTYPE FxReverbHi::ReleaseWorkBuffer()
		{
			mAxfxImpl.DestroyHeap();
		}
		
		bool FxReverbHi::StartUp()
		{
			u32 req = GetRequiredMemSize();
			if (req > mAxfxImpl.GetHeapTotalSize()) return false;
			
			AXFXAllocHook allocHook; // at 0xc
			AXFXFreeHook freeHook; // at 0x8
			
			mAxfxImpl.HookAlloc(&allocHook, &freeHook);
			
			mAxfxImpl.mAllocatedSize = 0;
			
			UNKWORD ret = AXFXReverbHiInit(&mAXFXReverbHi);
			
			mAxfxImpl.RestoreAlloc(allocHook, freeHook);
			
			AXFXReverbHiGetMemSize(&mAXFXReverbHi);
			
			mAxfxImpl.mIsActive = true;
			
			return ret;
		}
		
		UNKTYPE FxReverbHi::Shutdown()
		{
			if (!mAxfxImpl.mIsActive) return;
			
			mAxfxImpl.mIsActive = false;
			
			AXFXAllocHook allocHook; // at 0xc
			AXFXFreeHook freeHook; // at 0x8
			
			mAxfxImpl.HookAlloc(&allocHook, &freeHook);
			
			AXFXReverbHiShutdown(&mAXFXReverbHi);
			
			mAxfxImpl.RestoreAlloc(allocHook, freeHook);
		}
		
		bool FxReverbHi::SetParam(const ReverbHiParam & param)
		{
			mParam = param;
			
			mAXFXReverbHi.preDelay = Clamp<float>(param.FLOAT_0x0, 0.0f, 0.1f);
			mAXFXReverbHi.time = Clamp<float>(param.FLOAT_0x4, 0.0f, 10.0f);
			mAXFXReverbHi.coloration = Clamp<float>(param.FLOAT_0x8, 0.0f, 1.0f);
			mAXFXReverbHi.damping = Clamp<float>(param.FLOAT_0xC, 0.0f, 1.0f);
			mAXFXReverbHi.crosstalk = Clamp<float>(param.FLOAT_0x10, 0.0f, 1.0f);
			mAXFXReverbHi.mix = Clamp<float>(param.FLOAT_0x14, 0.0f, 1.0f);
			
			if (!mAxfxImpl.mIsActive) return true;
			
			u32 req = GetRequiredMemSize();
			if (req > mAxfxImpl.GetHeapTotalSize()) return false;
			
			AXFXAllocHook allocHook; // at 0xc
			AXFXFreeHook freeHook; // at 0x8
			
			mAxfxImpl.HookAlloc(&allocHook, &freeHook);
			
			UNKWORD ret = AXFXReverbHiSettings(&mAXFXReverbHi);
			
			mAxfxImpl.RestoreAlloc(allocHook, freeHook);
			
			return ret;
		}
		
		UNKTYPE FxReverbHi::UpdateBuffer(int, void ** r_5, u32, SampleFormat, float, OutputMode)
		{
			void * r_3[3];
			r_3[0] = r_5[0];
			r_3[1] = r_5[1];
			r_3[2] = r_5[2];
			AXFXReverbHiCallback(r_3, &mAXFXReverbHi);
		}
	}
}