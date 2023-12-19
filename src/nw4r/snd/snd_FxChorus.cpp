#include "snd_FxChorus.h"
#include "ut_algorithm.h"

namespace nw4r
{
	using namespace ut;
	
	namespace snd
	{
		using namespace detail;
		
		FxChorus::FxChorus()
		{
			ChorusParam chorusParam = { 10.0f, 0.5f, 1.0f }; // at 0x8
			SetParam(chorusParam);
		}
		
		u32 FxChorus::GetRequiredMemSize()
		{
			return RoundUp<u32>(AXFXChorusGetMemSize(&mAXFXChorus) + 0x68, 0x20);
		}
		
		UNKTYPE FxChorus::AssignWorkBuffer(void * r4, u32 r5)
		{
			mAxfxImpl.CreateHeap(r4, r5);
		}
		
		UNKTYPE FxChorus::ReleaseWorkBuffer()
		{
			mAxfxImpl.DestroyHeap();
		}
		
		bool FxChorus::StartUp()
		{
			u32 req = GetRequiredMemSize();
			if (req > mAxfxImpl.GetHeapTotalSize()) return false;
			
			AXFXAllocHook allocHook; // at 0xc
			AXFXFreeHook freeHook; // at 0x8
			
			mAxfxImpl.HookAlloc(&allocHook, &freeHook);
			
			mAxfxImpl.mAllocatedSize = 0;
			
			UNKWORD ret = AXFXChorusInit(&mAXFXChorus);
			
			mAxfxImpl.RestoreAlloc(allocHook, freeHook);
			
			AXFXChorusGetMemSize(&mAXFXChorus);
			
			mAxfxImpl.mActive = true;
			
			return ret;
		}
		
		UNKTYPE FxChorus::Shutdown()
		{
			if (!mAxfxImpl.mActive) return;
			
			mAxfxImpl.mActive = false;
			
			AXFXAllocHook allocHook; // at 0xc
			AXFXFreeHook freeHook; // at 0x8
			
			mAxfxImpl.HookAlloc(&allocHook, &freeHook);
			
			AXFXChorusShutdown(&mAXFXChorus);
			
			mAxfxImpl.RestoreAlloc(allocHook, freeHook);
		}
		
		bool FxChorus::SetParam(const ChorusParam & param)
		{
			mParam = param;
			
			u32 r31 = param.FLOAT_0x0;
			u32 r30 = param.FLOAT_0x0 * param.FLOAT_0x4;
			u32 r3 = 1000.0f / param.FLOAT_0x8;
			
			mAXFXChorus.baseDelay = Clamp<u32>(r31, 1, 50);
			mAXFXChorus.variation = Clamp<u32>(r30, 0, 50);
			mAXFXChorus.period = Clamp<u32>(r3, 500, 10000);
			
			if (!mAxfxImpl.mActive) return true;
			
			u32 req = GetRequiredMemSize();
			if (req > mAxfxImpl.GetHeapTotalSize()) return false;
			
			AXFXAllocHook allocHook; // at 0xc
			AXFXFreeHook freeHook; // at 0x8
			
			mAxfxImpl.HookAlloc(&allocHook, &freeHook);
			
			UNKWORD ret = AXFXChorusSettings(&mAXFXChorus);
			
			mAxfxImpl.RestoreAlloc(allocHook, freeHook);
			
			return ret;
		}
		
		UNKTYPE FxChorus::UpdateBuffer(int, void ** r_5, u32, SampleFormat, float, OutputMode)
		{
			void * r_3[3];
			r_3[0] = r_5[0];
			r_3[1] = r_5[1];
			r_3[2] = r_5[2];
			AXFXChorusCallback(r_3, &mAXFXChorus);
		}
	}
}