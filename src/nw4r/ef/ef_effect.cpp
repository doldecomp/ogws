#include "types_nw4r.h"
#include "ef_effect.h"
#include "ef_effectsystem.h"
#include "ef_memorymanager.h"
#include "ef_emitter.h"
#include "ef_util.h"
#include "ef_particle.h"
#include "ef_draworder.h"

namespace nw4r
{
	using namespace ut;
	using namespace math;
	
	namespace ef
	{
		Effect::Effect() : mEmitters(0x14)
		{
			List_Init(&UTLIST_0x90, 0x30);
		}
		
		Effect::~Effect()
		{
			RetireEmitterAll();
		}
		
		bool Effect::Initialize(EffectSystem * pSystem, EmitterResource * pRes, u16 num)
		{
			ReferencedObject::Initialize();
			mEmitters.Initialize();
			mDrawOrder = pSystem->mDrawOrder;
			
			MTX34Identity(&mRootMtx);
			
			mSystem = pSystem;
			mEmissionPrologue = NULL;
			WORD_0x48 = 0;
			WORD_0x4C = 0;
			mFlags = 0;
			
			VEC_0x84.x = 0.0f;
			VEC_0x84.y = 0.0f;
			VEC_0x84.z = 0.0f;
			
			Emitter * pEmitter = pSystem->GetMemoryManager()->AllocEmitter();
			
			if (!pEmitter) return false;
			
			if (!pEmitter->Initialize(this, pRes, 0x80))
			{
				pSystem->GetMemoryManager()->FreeEmitter(pEmitter);
				return false;
			}
			
			mEmitters.ToActive(pEmitter);
			pEmitter->WORD_0xC = 1;
			
			pEmitter->SHORT_0xE8 += num;
			
			return true;
		}
		
		bool Effect::SendClosing()
		{
			return mSystem->Closing(this);
		}
		
		UNKTYPE Effect::DestroyFunc()
		{
			RetireEmitterAll();
		}
		
		bool Effect::Closing(Emitter * pEmitter)
		{
			if (pEmitter->mParent) pEmitter->mParent->UnRef();
			
			if (pEmitter->REF_0xF8)
			{
				pEmitter->REF_0xF8->UnRef();
				pEmitter->REF_0xF8 = NULL;
			}
			
			pEmitter->mEffect->UnRef();
			
			mEmitters.ToClosing(pEmitter);
			pEmitter->WORD_0xC = 3;
			
			return true;
		}
		
		Emitter * Effect::CreateEmitter(EmitterResource * pRes, u8 byte, u16 num)
		{
			Emitter * pEmitter = mSystem->GetMemoryManager()->AllocEmitter();
			
			if (!pEmitter) return NULL;
			
			if (!pEmitter->Initialize(this, pRes, byte))
			{
				mSystem->GetMemoryManager()->FreeEmitter(pEmitter);
				return NULL;
			}
			
			mEmitters.ToActive(pEmitter);
			pEmitter->WORD_0xC = 1;
			
			pEmitter->SHORT_0xE8 += num;
			
			return pEmitter;
		}
		
		bool Effect::RetireEmitter(Emitter * pEmitter)
		{
			if (pEmitter->WORD_0xC != 1) return false;
			
			mEmitters.ToWait(pEmitter);
			pEmitter->Destroy();
			return true;
		}
		
		u16 Effect::RetireEmitterAll()
		{
			u16 counter = 0;
			Emitter * emitters[0x400];
			
			u16 len = UtlistToArray(&mEmitters.mActive, (void **)emitters, mEmitters.mActive.size);
			
			for (u16 i = 0; i < len; i++)
			{
				Emitter * curEmitter = emitters[i];
				if (curEmitter->WORD_0xC == 1) counter += RetireEmitter(curEmitter);
			}
			
			return counter;
		}
		
		u16 Effect::RetireParticleAll()
		{
			u16 counter = 0;
			Emitter * emitters[0x400];
			
			u16 len = UtlistToArray(&mEmitters.mActive, (void **)emitters, mEmitters.mActive.size);
			
			for (u16 i = 0; i < len; i++)
			{
				counter += emitters[i]->RetireParticleAll();
			}
			
			return counter;
		}
		
		void Effect::Calc(bool b)
		{
			if (b)
			{
				Emitter * curEmitter = NULL;
				
				while (curEmitter = (Emitter *)List_GetNext(&mEmitters.mActive, curEmitter))
				{
					if ((u32)curEmitter->WORD_0xC - 1 > 1) continue;
					
					if (curEmitter->WORD_0x24 & 0x10000 || curEmitter->WORD_0x24 & 0x8000)
					{
						curEmitter->CalcBillboard();
					}
				}
			}
			else
			{
				//80010E50
				if (mFlags & 1) return;
				Emitter * curEmitter = NULL;
				
				while (curEmitter = (Emitter *)List_GetNext(&mEmitters.mActive, curEmitter)) //80010EB4
				{
					//80010E68
					if ((u32)curEmitter->WORD_0xC - 1 <= 1 && curEmitter->WORD_0xB4 == 1)
					{
						curEmitter->WORD_0xB4 = 0;
					}
					
					ParticleManager * curManager = NULL;
					
					while (curManager = (ParticleManager *)List_GetNext(&curEmitter->mManagers.mActive, curManager)) //80010E9C
					{
						//80010E90
						curManager->BeginCalc(false);
					}
				}
				//80010ECC
				mFlags |= 0x10000;
				Emitter * emitters[0x400];
				
				while (mFlags & 0x10000) //80011130
				{
					//80010EE4
					mFlags &= ~0x10000;
					
					do
					{
						//80010EF0
						u16 len1 = UtlistToArray(&mEmitters.mActive, (void **)emitters, mEmitters.mActive.size);
						
						for (u16 i = 0; i < len1; i++)
						{
							emitters[i]->CalcEmitter();
						}
						
						//80010F34
						Emitter * pEmitter = NULL;
						
						while (pEmitter = (Emitter *)List_GetNext(&mEmitters.mActive, pEmitter))  //80010F74
						{
							//80010F3C
							if ((u32)pEmitter->WORD_0xC - 1 > 1) continue;
							
							if (pEmitter->WORD_0x24 & 0x10000 || pEmitter->WORD_0x24 & 0x8000)
							{
								pEmitter->CalcBillboard();
							}
						}
						
						//80010F8C
						u16 len2 = UtlistToArray(&mEmitters.mActive, (void **)emitters, mEmitters.mActive.size);
						
						for (u16 i = 0; i < len2; i++) //80010FF8
						{
							//80010FA8
							Emitter * curEmitter = emitters[i];
							
							if (curEmitter->WORD_0xB4 == 0) curEmitter->WORD_0xE4++;
							
							curEmitter->CalcParticle();
							
							if (curEmitter->WORD_0xB4 == 0) curEmitter->WORD_0xE4--;
						}
						
						//80011004
						u16 len3 = UtlistToArray(&mEmitters.mActive, (void **)emitters, mEmitters.mActive.size);
						
						for (u16 i = 0; i < len3; i++) //8001103C
						{
							//80011020
							emitters[i]->CalcEmission();
						}
						
						//80011048
						u16 len = UtlistToArray(&mEmitters.mActive, (void **)emitters, mEmitters.mActive.size);
						
						for (u16 i = 0; i < len; i++) //80011080
						{
							//80011064
							emitters[i]->CalcParticle();
						}
						
						if (mSystem->mCreationQueue.IsEmpty()) break;
						
						mSystem->mCreationQueue.Execute();
					} while(true);
					
					if (mFlags & 0x10000)
					{
						Emitter * pEmitter = NULL;
						
						while (pEmitter = (Emitter *)List_GetNext(&mEmitters.mActive, pEmitter)) //80011118
						{
							//800110B8
							if (pEmitter->WORD_0xC == 1 && pEmitter->SHORT_0xE8)
							{
								if (pEmitter->SHORT_0xE8 != 0) pEmitter->SHORT_0xE8--;
								
								if (pEmitter->WORD_0xB4 == 1) pEmitter->WORD_0xB4 = 0;
							}
							//800110EC
							
							ParticleManager * curManager = NULL;
							
							while (curManager = (ParticleManager *)List_GetNext(&pEmitter->mManagers.mActive, curManager))
							{
								curManager->BeginCalc(true);
							}
						}
					}
					
					//80011130
				}
				
				Emitter * pEmitter = NULL;
				
				while (pEmitter = (Emitter *)List_GetNext(&mEmitters.mActive, pEmitter)) //80011190
				{
					//80011148
					if ((u32)pEmitter->WORD_0xC - 1 <= 1 && pEmitter->WORD_0xB4 == 3)
					{
						pEmitter->WORD_0xB4 = 1;
					}
					
					ParticleManager * curManager = NULL;
					
					while (curManager = (ParticleManager *)List_GetNext(&pEmitter->mManagers.mActive, curManager)) //80011178
					{
						//80011170
						curManager->EndCalc();
					}
				}
			}
		}
		
		void Effect::Draw(const DrawInfo & drawInfo)
		{
			if (GetFlagDisableDraw()) return;
			
			mDrawOrder->Draw(this, drawInfo);
		}
		
		u16 Effect::GetNumEmitter() const
		{
			return mEmitters.mActive.size;
		}
		
		Emitter * Effect::GetEmitter(u16 i)
		{
			return (Emitter *)List_GetNth(&mEmitters.mActive, i);
		}
		
		u16 Effect::ForeachParticleManager(Action action, u32 arg, bool b)
		{
			u16 counter = 0;
			Emitter * curEmitter;
			Emitter * nextEmitter;
			
			for (curEmitter = (Emitter *)List_GetFirst(&mEmitters.mActive); curEmitter; curEmitter = nextEmitter)
			{
				nextEmitter = (Emitter *)List_GetNext(&mEmitters.mActive, curEmitter);
				
				counter += curEmitter->ForeachParticleManager(action, arg, b, false);
			}
			
			return counter;
		}
		
		u16 Effect::ForeachEmitterFrom(Action action, u32 arg, bool b, Emitter * pEmitter)
		{
			u16 counter = 0;
			
			Emitter * curEmitter;
			Emitter * nextEmitter;
			
			for (curEmitter = (Emitter *)List_GetFirst(&mEmitters.mActive); curEmitter; curEmitter = nextEmitter)
			{
				nextEmitter = (Emitter *)List_GetNext(&mEmitters.mActive, curEmitter);
				
				if (b || curEmitter->WORD_0xC == 1)
				{
					bool flag = false;
					Emitter * otherEmitter = curEmitter;
					
					while (!flag && (otherEmitter = otherEmitter->mParent)) //8001130C
					{
						if (otherEmitter == pEmitter) flag = true;
					}
					
					if (flag)
					{
						action(curEmitter, arg);
						counter++;
					}
				}
			}
			
			return counter;
		}
		
		UNKTYPE Effect::SetRootMtx(const MTX34 & rootMtx)
		{
			MTX34Copy(&mRootMtx, &rootMtx);
			
			Emitter * curEmitter = NULL;
			
			while (curEmitter = (Emitter *)List_GetNext(&mEmitters.mActive, curEmitter))
			{
				if (!curEmitter->mParent) curEmitter->SetMtxDirty();
			}
		}
		
		Emitter * Effect::CreateEmitter(ResEmitter res, u8 byte, u16 num)
		{
			return CreateEmitter(res.ptr(), byte, num);
		}
	}
}