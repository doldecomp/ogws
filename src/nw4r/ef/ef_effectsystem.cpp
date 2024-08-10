#include <revolution/OS/OS.h>
#include "ef_effectsystem.h"
#include "ef_effect.h"
#include "ef_draworder.h"
#include "ef_drawstrategybuilder.h"
#include "ef_emform.h"
#include "ef_resource.h"
#include "ef_util.h"
#include "ef_memorymanager.h"

namespace
{
	const char * NW4R_EF_Version_ = "<< NW4R    - EF \tfinal   build: Jun  8 2007 11:16:29 (0x4199_60831) >>";
}

inline void * operator new[](size_t size, void *p)
{
	return p;
}

namespace nw4r
{
	namespace ef
	{
		static DrawOrder gBasicDrawOrder;
		static DrawStrategyBuilder gBasicDrawStrategyBuilder;
		static EmitFormBuilder gBasicEmitFormBuilder;
		
		EffectSystem::EffectSystem()
		{
			if (mDisplayVersion)
			{
				mDisplayVersion = false;
				OSRegisterVersion(NW4R_EF_Version_);
			}
			
			mMemoryManager = NULL;
			mNumGroup = 0;
			BYTE_0x5064 = 0;
		}
		
		EffectSystem::~EffectSystem()
		{
			for (u32 i = 0; i < mNumGroup; i++)
			{
				RetireEffectAll(i);
			}
		}
		
		EffectSystem * EffectSystem::GetInstance()
		{
			return &instance;
		}
		
		bool EffectSystem::Initialize(u32 maxGroupID)
		{
			u32 len = mNumGroup = maxGroupID;

			void *p = mMemoryManager->AllocHeap(mNumGroup * sizeof(ActivityList) + 32);
			ARR_0x5018 = new (p) ActivityList[len];
			
			for (u32 i = 0; i < mNumGroup; i++)
			{
				ARR_0x5018[i].SetOffset(0x14);
				ARR_0x5018[i].Initialize();
			}
			
			mRandom.Srand(0);
			
			mDrawOrder = &gBasicDrawOrder;
			mDrawStrategyBuilder = &gBasicDrawStrategyBuilder;
			mEmitFormBuilder = &gBasicEmitFormBuilder;
			
			return true;
		}
		
		bool EffectSystem::Closing(Effect * pEffect)
		{
			ARR_0x5018[pEffect->INDEX_0x40].ToClosing(pEffect);
			pEffect->WORD_0xC = 3;
			
			return true;
		}
		
		Effect * EffectSystem::CreateEffect(const char * str, u32 index, u16 snum)
		{
			EmitterResource * pEmitRes = Resource::GetInstance()->_FindEmitter(str, NULL);
			
			if (!pEmitRes) return NULL;
			
			Effect * pEffect = mMemoryManager->AllocEffect();
			
			if (!pEffect) return NULL;
			
			if (!pEffect->Initialize(this, pEmitRes, snum))
			{
				mMemoryManager->FreeEffect(pEffect);
				return NULL;
			}
			
			pEffect->INDEX_0x40 = index;
			
			ARR_0x5018[index].ToActive(pEffect);
			pEffect->WORD_0xC = 1;
			
			ARR_0x5018[index].ToWait(pEffect);
			pEffect->WORD_0xC = 2;
			
			return pEffect;
		}
		
		bool EffectSystem::RetireEffect(Effect * pEffect)
		{
			if (pEffect->WORD_0xC != 1) return false;
			
			ARR_0x5018[pEffect->INDEX_0x40].ToWait(pEffect);
			pEffect->Destroy();
			
			return true;
		}
		
		u16 EffectSystem::RetireEffectAll(u32 index)
		{
			Effect * effects[0x400];
			
			u16 counter = 0;
			u16 len = UtlistToArray(&ARR_0x5018[index].mActive, (void **)effects, ARR_0x5018[index].mActive.size);
			
			for (u16 i = 0; i < len; i++)
			{
				Effect * effect = effects[i];
				
				if (effect->WORD_0xC == 1) counter += RetireEffect(effect);
			}
			
			return counter;
		}
		
		u16 EffectSystem::RetireEmitterAll(u32 index)
		{
			Effect * effects[0x400];
			
			u16 counter = 0;
			u16 len = UtlistToArray(&ARR_0x5018[index].mActive, (void **)effects, ARR_0x5018[index].mActive.size);
			
			for (u16 i = 0; i < len; i++)
			{
				counter += effects[i]->RetireEmitterAll();
			}
			
			return counter;
		}
		
		u16 EffectSystem::RetireParticleAll(u32 index)
		{
			Effect * effects[0x400];
			
			u16 counter = 0;
			u16 len = UtlistToArray(&ARR_0x5018[index].mActive, (void **)effects, ARR_0x5018[index].mActive.size);
			
			for (u16 i = 0; i < len; i++)
			{
				counter += effects[i]->RetireParticleAll();
			}
			
			return counter;
		}
		
		void EffectSystem::Calc(u32 index, bool b)
		{
			Effect * effects[0x400];
			
			u16 len = UtlistToArray(&ARR_0x5018[index].mActive, (void **)effects, ARR_0x5018[index].mActive.size);
			
			for (u16 i = 0; i < len; i++)
			{
				effects[i]->Calc(b);
			}
			
			mMemoryManager->GarbageCollection();
		}
		
		void EffectSystem::Draw(const DrawInfo & drawInfo, u32 index)
		{
			Effect * curEffect = NULL;
			
			while (curEffect = (Effect *)List_GetNext(&ARR_0x5018[index].mActive, curEffect))
			{
				curEffect->Draw(drawInfo);
			}
		}
		
		bool EffectSystem::mDisplayVersion = true;
		EffectSystem EffectSystem::instance;
	}
}