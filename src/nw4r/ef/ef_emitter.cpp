#include "types_nw4r.h"
#include "ef_emitter.h"
#include "ef_emform.h"
#include "ef_emitterform.h"
#include "ef_effect.h"
#include "ef_effectsystem.h"
#include "ef_memorymanager.h"
#include "ef_draworder.h"
#include "ef_particle.h"
#include "ef_particlemanager.h"
#include "ef_util.h"
#include "ef_resource.h"

namespace nw4r
{
	using namespace math;
	using namespace ut;
	
	namespace ef
	{
		Emitter::Emitter() : mManagers(0x14) {}
		Emitter::~Emitter() {}
		
		u16 Emitter::RetireParticleAll()
		{
			u16 counter = 0;
			ParticleManager * managers[0x400];
			
			u16 len = UtlistToArray(&mManagers.mActive, (void **)managers, mManagers.mActive.size);
			
			for (u16 i = 0; i < len; i++)
			{
				counter += managers[i]->RetireParticleAll();
			}
			
			return counter;
		}
		
		bool Emitter::SendClosing()
		{
			return mEffect->Closing(this);
		}
		
		UNKTYPE Emitter::DestroyFunc()
		{
			if (mForm) mForm = NULL;
			
			if (mFlags & 1) RetireParticleAll();
			
			RetireParticleManagerAll();
			
			if (mFlags & 1)
			{
				Emitter * emitters[0x400];
				
				u16 len = UtlistToArray(&mEffect->mEmitters.mActive, (void **)emitters, mEffect->mEmitters.mActive.size);
				
				for (u16 i = 0; i < len; i++)
				{
					Emitter * emitter = emitters[i];
					
					for (Emitter * curEmitter = emitter->mParent; curEmitter; curEmitter = curEmitter->mParent)
					{
						if (curEmitter == this)
						{
							emitter->RetireParticleAll();
							if (emitter->WORD_0xC == 1) mEffect->RetireEmitter(emitter);
							break;
						}
					}
				}
			}
		}
		
		bool Emitter::Closing(ParticleManager * pManager)
		{
			mEffect->mDrawOrder->Remove(mEffect, pManager);
			pManager->mEmitter->UnRef();
			mManagers.ToClosing(pManager);
			pManager->WORD_0xC = 3;
			
			return true;
		}
		
		bool Emitter::RetireParticleManager(ParticleManager * pManager)
		{
			if (pManager->WORD_0xC != 1) return false;
			
			mManagers.ToWait(pManager);
			pManager->Destroy();
			
			return true;
		}
		
		u16 Emitter::RetireParticleManagerAll()
		{
			u16 counter = 0;
			ParticleManager * managers[0x400];
			
			u16 len = UtlistToArray(&mManagers.mActive, (void **)managers, mManagers.mActive.size);
			
			for (u16 i = 0; i < len; i++)
			{
				ParticleManager * pManager = managers[i];
				if (pManager->WORD_0xC == 1) counter += RetireParticleManager(pManager);
			}
			
			return counter;
		}
		
		bool Emitter::InitializeDatas(EmitterResource * pResource, Effect * pEffect)
		{
			WORD_0xE4 = 0;
			WORD_0xC = 1;
			mResource = pResource;
			WORD_0xB4 = 0;
			SHORT_0xE8 = pResource->STRUCT_0x8.SHORT_0x16;
			mFlags = pResource->STRUCT_0x8.FLAGS_0x0;
			WORD_0x24 = pResource->STRUCT_0x8.EMFORMTYPE_0x4;
			SHORT_0x3C = pResource->STRUCT_0x8.SHORT_0x8;
			SHORT_0xDE = pResource->STRUCT_0x8.SHORT_0x14;
			SHORT_0xE0 = 0;
			FLOAT_0x44 = pResource->STRUCT_0x8.BYTE_0x85 / 100.0f;
			FLOAT_0x40 = pResource->STRUCT_0x8.BYTE_0x84 / 100.0f;
			FLOAT_0x48 = pResource->STRUCT_0x8.BYTE_0x86 / 100.0f;
			FLOAT_0x28 = pResource->STRUCT_0x8.FLOAT_0x10;
			FLOAT_0x2C = pResource->STRUCT_0x8.SBYTE_0xF / 100.0f;
			SHORT_0x30 = pResource->STRUCT_0x8.SHORT_0x18;
			SHORT_0x32 = pResource->STRUCT_0x8.SHORT_0x34;
			FLOAT_0x38 = 0.0f;
			BYTE_0xDC = 1;
			FLOAT_0x34 = pResource->STRUCT_0x8.SBYTE_0xE / 100.0f;
			
			VEC_0x90.x = pResource->STRUCT_0x8.FLOAT_0x78;
			VEC_0x90.y = pResource->STRUCT_0x8.FLOAT_0x7C;
			VEC_0x90.z = pResource->STRUCT_0x8.FLOAT_0x80;
			
			VEC_0x9C.x = pResource->STRUCT_0x8.FLOAT_0x60;
			VEC_0x9C.y = pResource->STRUCT_0x8.FLOAT_0x64;
			VEC_0x9C.z = pResource->STRUCT_0x8.FLOAT_0x68;
			
			VEC_0xA8.x = pResource->STRUCT_0x8.FLOAT_0x6C;
			VEC_0xA8.y = pResource->STRUCT_0x8.FLOAT_0x70;
			VEC_0xA8.z = pResource->STRUCT_0x8.FLOAT_0x74;
			
			BYTE_0x64 = 3;
			BYTE_0x65 = 100;
			BYTE_0x66 = pResource->STRUCT_0x8.BYTE_0x36;
			BYTE_0x67 = pResource->STRUCT_0x8.BYTE_0x37;
			
			FLOAT_0x68 = pResource->STRUCT_0x8.FLOAT_0x38;
			FLOAT_0x6C = pResource->STRUCT_0x8.FLOAT_0x3C;
			FLOAT_0x70 = pResource->STRUCT_0x8.FLOAT_0x40;
			FLOAT_0x74 = pResource->STRUCT_0x8.FLOAT_0x44;
			FLOAT_0x78 = pResource->STRUCT_0x8.FLOAT_0x48;
			FLOAT_0x7C = pResource->STRUCT_0x8.FLOAT_0x4C;
			FLOAT_0x80 = pResource->STRUCT_0x8.FLOAT_0x50;
			FLOAT_0x84 = pResource->STRUCT_0x8.FLOAT_0x54;
			FLOAT_0x88 = pResource->STRUCT_0x8.FLOAT_0x58;
			FLOAT_0x8C = pResource->STRUCT_0x8.FLOAT_0x5C;
			
			Resource::GetInstance();
			
			SHORT_0xEA = pResource->STRUCT_0x8.WORD_0x88;
			
			if (!SHORT_0xEA)
			{
				SHORT_0xEA = pEffect->mSystem->mRandom.Rand();
			}
			
			mRandom.Srand(SHORT_0xEA);
			
			FLOAT_0x4C = pResource->STRUCT_0x8.FLOAT_0x1C;
			FLOAT_0x50 = pResource->STRUCT_0x8.FLOAT_0x20;
			FLOAT_0x54 = pResource->STRUCT_0x8.FLOAT_0x24;
			FLOAT_0x58 = pResource->STRUCT_0x8.FLOAT_0x28;
			FLOAT_0x5C = pResource->STRUCT_0x8.FLOAT_0x2C;
			FLOAT_0x60 = pResource->STRUCT_0x8.FLOAT_0x30;
			
			mMtxDirtyFlag = true;
			REF_0xF8 = NULL;
			
			mForm = pEffect->mSystem->mEmitFormBuilder->Create((EmitFormType)(pResource->STRUCT_0x8.EMFORMTYPE_0x4 & 0xFF));
			mParent = NULL;
			mEffect = NULL;
			
			return true;
		}
		
		bool Emitter::Initialize(Effect * pEffect, EmitterResource * pResource, u8 byte)
		{
			WORD_0xC = 1;
			mManagers.Initialize();
			InitializeDatas(pResource, pEffect);
			
			ParticleManager * pManager = mEffect->mSystem->GetMemoryManager()->AllocParticleManager();
			
			if (!pManager) return false;
			
			if (!pManager->Initialize(this, pResource)) return false; //memory leak?
			
			mEffect->Ref();
			mManagers.ToActive(pManager);
			
			pManager->WORD_0xC = 1;
			pManager->FLAGS_0x28 = 0;
			
			if (pResource->STRUCT_0x8.FLAGS_0x0 & 0x20) pManager->FLAGS_0x28 |= 1;
			if (pResource->STRUCT_0x8.FLAGS_0x0 & 0x40) pManager->FLAGS_0x28 |= 2;
			
			mEffect->mDrawOrder->Add(mEffect, pManager);
			
			return true;
		}
		
		Emitter * Emitter::CreateEmitter(EmitterResource * pRes, EmitterInheritSetting * pInherit, Particle * pParticle, u16 snum)
		{
			Emitter * pChild = mEffect->CreateEmitter(pRes, pInherit->BYTE_0x5, 0);
			
			if (!pChild) return NULL;
			
			pChild->SHORT_0xE8 += snum;
			pChild->mParent = this;
			ReferencedObject::Ref();
			pChild->BYTE_0x64 = 0;
			if (mResource->STRUCT_0x8.FLAGS_0x0 & 0x80) pChild->BYTE_0x64 |= 0x1;
			if (mResource->STRUCT_0x8.FLAGS_0x0 & 0x100) pChild->BYTE_0x64 |= 0x2;
			pChild->BYTE_0x65 = mResource->STRUCT_0x8.BYTE_0x1B;
			if (pParticle)
			{
				//80012484
				VEC3 vec_0x8(VEC_0x90);
				pChild->VEC_0x90.x = 0.0f;
				pChild->VEC_0x90.y = 0.0f;
				pChild->VEC_0x90.z = 0.0f;
				
				pChild->SetMtxDirty();
				
				MTX34 mtx_0x48; // at 0x48
				
				MTX34Identity(&mtx_0x48);
				
				MTX34RotXYZFIdx(&mtx_0x48, 40.743664f * pChild->VEC_0xA8.x, 40.743664f * pChild->VEC_0xA8.y, 40.743664f * pChild->VEC_0xA8.z);
				MTX34Scale(&mtx_0x48, &mtx_0x48, &pChild->VEC_0x9C);
				
				MTX34 mtx_0x18;
				
				pChild->CalcGlobalMtx(&mtx_0x18);
				MTX34Inv(&mtx_0x18, &mtx_0x18);
				MTX34Mult(&mtx_0x48, &mtx_0x18, &mtx_0x48);
				pParticle->mManager->CalcGlobalMtx(&mtx_0x18);
				MTX34Mult(&mtx_0x48, &mtx_0x18, &mtx_0x48);
				
				MTX34Trans(&mtx_0x48, &mtx_0x48, &pParticle->VEC_0xAC);
				
				MTX34RotXYZFIdx(&mtx_0x18, 40.743664f * pChild->VEC_0xA8.x, 40.743664f * pChild->VEC_0xA8.y, 40.743664f * pChild->VEC_0xA8.z);
				MTX34Scale(&mtx_0x18, &mtx_0x18, &pChild->VEC_0x9C);
				MTX34Inv(&mtx_0x18, &mtx_0x18);
				MTX34Mult(&mtx_0x48, &mtx_0x18, &mtx_0x48);
				
				pChild->VEC_0x90.x = vec_0x8.x + mtx_0x48.m[0][3];
				pChild->VEC_0x90.y = vec_0x8.y + mtx_0x48.m[1][3];
				pChild->VEC_0x90.z = vec_0x8.z + mtx_0x48.m[2][3];
				
				pChild->SetMtxDirty();
				
				if (pInherit->SHORT_0x0 || pInherit->BYTE_0x2 || pInherit->BYTE_0x3 || pInherit->BYTE_0x4 || pInherit->BYTE_0x7)
				{
					pChild->REF_0xF8 = pParticle;
					pParticle->Ref();
					pChild->mInheritSettings = *pInherit;
				}
			}
			//80012650
			return pChild;
		}
		ParticleManager * Emitter::FindParticleManager(EmitterResource * pRes, bool b1, bool b2, s8 sbyte, u8 ubyte)
		{
			ParticleManager * curMgr;
			
			for (curMgr = (ParticleManager *)List_GetFirst(&mManagers.mActive); curMgr; curMgr = (ParticleManager *)List_GetNext(&mManagers.mActive, curMgr))
			{
				if (curMgr->mResource == pRes &&
				(bool)(curMgr->FLAGS_0xB4 & 1) == b1 &&
				(bool)(curMgr->FLAGS_0xB4 & 2) == b2 &&
				curMgr->BYTE_0x88 == sbyte &&
				curMgr->BYTE_0x89 == ubyte) return curMgr;
			}
			
			return NULL;
		}
		
		UNKTYPE Emitter::CreateEmitterTmp(EmitterResource * pRes, EmitterInheritSetting * pInherit, register Particle * pParticle, u16 snum)
		{
			//r27 <- r6 (pParticle)
			
			Emitter tmp; // at 0x150
			
			tmp.InitializeDatas(pRes, mEffect);
			
			SHORT_0xE8 += snum;
			
			tmp.mEffect = mEffect;
			tmp.mParent = this;
			
			if ((pInherit->BYTE_0x7 & 1) && pInherit->SHORT_0x0)
			{
				//80012704
				MTX34 mtx_0xf0;
				
				pParticle->mManager->CalcGlobalMtx(&mtx_0xf0);
				
				mtx_0xf0.m[2][3] = 0.0f;
				mtx_0xf0.m[1][3] = 0.0f;
				mtx_0xf0.m[0][3] = 0.0f;
				
				VEC3 vec_0x20;
				vec_0x20 = pParticle->VEC_0xAC - pParticle->VEC_0xB8;
				
				VEC3Transform(&vec_0x20, &mtx_0xf0, &vec_0x20);
				
				if (vec_0x20.x || vec_0x20.y || vec_0x20.z)
				{
					//80012790
					VEC3Normalize(&vec_0x20, &vec_0x20);
					if (pInherit->SHORT_0x0 < 0)
					{
						VEC3Scale(&vec_0x20, &vec_0x20, -1);
					}
					//800127C4
					MTX34 mtx_0x120;
					GetDirMtxY(&mtx_0x120, vec_0x20);
					MTX34RotXYZFIdx(&mtx_0x120, 40.743664f * tmp.VEC_0xA8.x, 40.743664f * tmp.VEC_0xA8.y, 40.743664f * tmp.VEC_0xA8.z);
					MTX34Mult(&mtx_0x120, &mtx_0xf0, &mtx_0x120);
					MtxGetRotation(mtx_0x120, &tmp.VEC_0xA8);
					//80012810 (END)
				}
				//80012810 (END)
			}
			//80012810
			VEC3 vec_0x14(tmp.VEC_0x90);
			
			tmp.VEC_0x90.x = 0.0f;
			tmp.VEC_0x90.y = 0.0f;
			tmp.VEC_0x90.z = 0.0f;
			
			tmp.SetMtxDirty();
			
			MTX34 mtx_0xc0;
			
			MTX34Identity(&mtx_0xc0);
			MTX34RotXYZFIdx(&mtx_0xc0, 40.743664f * tmp.VEC_0xA8.x, 40.743664f * tmp.VEC_0xA8.y, 40.743664f * tmp.VEC_0xA8.z);
			MTX34Scale(&mtx_0xc0, &mtx_0xc0, &tmp.VEC_0x9C);
			
			MTX34 mtx_0x90;
			
			tmp.CalcGlobalMtx(&mtx_0x90);
			
			MTX34Inv(&mtx_0x90, &mtx_0x90);
			
			MTX34Mult(&mtx_0xc0, &mtx_0x90, &mtx_0xc0);
			
			pParticle->mManager->CalcGlobalMtx(&mtx_0x90);
			
			MTX34Mult(&mtx_0xc0, &mtx_0x90, &mtx_0xc0);
			MTX34Trans(&mtx_0xc0, &mtx_0xc0, &pParticle->VEC_0xAC);
			
			MTX34RotXYZFIdx(&mtx_0x90, 40.743664f * tmp.VEC_0xA8.x, 40.743664f * tmp.VEC_0xA8.y, 40.743664f * tmp.VEC_0xA8.z);
			
			MTX34Scale(&mtx_0x90, &mtx_0x90, &tmp.VEC_0x9C);
			MTX34Inv(&mtx_0x90, &mtx_0x90);
			MTX34Mult(&mtx_0xc0, &mtx_0x90, &mtx_0xc0);
			
			tmp.VEC_0x90.x = vec_0x14.x + mtx_0xc0.m[0][3];
			tmp.VEC_0x90.y = vec_0x14.y + mtx_0xc0.m[1][3];
			tmp.VEC_0x90.z = vec_0x14.z + mtx_0xc0.m[2][3];
			
			tmp.SetMtxDirty();
			tmp.CalcEmitter();
			tmp.CalcBillboard();
			
			bool r31 = ((this->mFlags & 0x80) && (this->mFlags & 0x20));
			bool r30 = ((this->mFlags & 0x100) && (this->mFlags & 0x40));
			
			s8 r29 = this->mResource->STRUCT_0x8.BYTE_0x1A;
			s8 r0 = this->mResource->STRUCT_0x8.BYTE_0x1B;
			
			if (r0 == 0 || r29 == 0)
			{
				r29 = 0;
			}
			else if (r0 == 100) //lbl_800129CC
			{
				r29 = r29;
			}
			else if (r29 == 100)
			{
				r29 = r0;
			}
			else
			{
				r29 = r0 * r29 / 100;
			}
			//80012A08
			ParticleManager * pParticleMgr = FindParticleManager(pRes, r31, r30, r29, pInherit->BYTE_0x5); // saved to r28
			//80012A80
			if (!pParticleMgr)
			{
				pParticleMgr = mEffect->mSystem->GetMemoryManager()->AllocParticleManager();
				
				if (!pParticleMgr) return;
				//80012AB4
				if (!pParticleMgr->Initialize(this, pRes)) return;
				//80012AD4
				mManagers.ToActive(pParticleMgr);
				//80012AF8
				pParticleMgr->WORD_0xC = 1;
				pParticleMgr->FLAGS_0x28 = 0;
				//80012B00
				if (r31) pParticleMgr->FLAGS_0x28 |= 1;
				//80012B10
				if (r30) pParticleMgr->FLAGS_0x28 |= 2;
				pParticleMgr->BYTE_0x88 = r29;
				pParticleMgr->BYTE_0x89 = pInherit->BYTE_0x5;
				mEffect->mDrawOrder->Add(mEffect, pParticleMgr);
				//80012B4C
			}
			//80012B4C
			if (pInherit->SHORT_0x0 || pInherit->BYTE_0x2 || pInherit->BYTE_0x3 || pInherit->BYTE_0x4 || (pInherit->BYTE_0x7 & 2))
			{
				tmp.REF_0xF8 = pParticle;
				pParticle->Ref();
				tmp.mInheritSettings = *pInherit;
			}
			else
			{
				tmp.REF_0xF8 = NULL;
			}
			//80012BDC
			MTX34 mtx_0x60;
			MTX34 mtx_0x30;
			pParticleMgr->CalcGlobalMtx(&mtx_0x30);
			MTX34Inv(&mtx_0x30, &mtx_0x30);
			tmp.CalcGlobalMtx(&mtx_0x60);
			MTX34Mult(&mtx_0x30, &mtx_0x60, &mtx_0x60);
			tmp.Emission(pParticleMgr, &mtx_0x60);
			
			tmp.mParent = NULL;
			tmp.mEffect = NULL;
			//80012C30
			if (REF_0xF8)
			{
				pParticle->UnRef();
				REF_0xF8 = NULL;
			}
			//80012C70
			if (this->WORD_0xC == 1 || pParticleMgr->WORD_0xC == 1) return;
			
			RetireParticleManager(pParticleMgr);
		}
		
		float Emitter::GetLODratio(VEC3 & vec1, VEC3 & vec2, float flt1, float flt2, float flt3, float flt4)
		{
			float f31 = flt1 - flt2;
			
			float f1;
			float f2;
			float f0;
			
			f0 = (float)sqrt(VEC3DistSq(&vec1, &vec2)) - flt2;
			f2 = f31 * flt4;
			f1 = f31 * flt3;
			
			if (f2 > f0) return 1.0f;
			
			if (f1 < f0) return 0.0f;
			
			float f3 = f1 - f2;
			
			if (0.0f == f3) return 0.0f;
			
			return 1.0f - (f0 - f2) / f3;
		}
		
		void Emitter::Emission(ParticleManager * pManager, const math::MTX34 * pMtx)
		{
			//r29 <- this
			//r30 <- pManager
			//r31 <- pMtx
			if (SHORT_0xE0)
			{
				SHORT_0xE0--; //SHORT_0xE0 is probably a timer
				return;
			}
			//80012E0C
			SHORT_0xE0 = SHORT_0x30;
			//80012E20
			if (0.0f != FLOAT_0x34)
			{
				//80012E24
				SHORT_0xE0 += ceil((SHORT_0x30 * FLOAT_0x34 - 1.0f) * mRandom.RandFloat());
				//80012E98 (END)
			}
			//80012E98
			if (WORD_0x24 & 0x00020000)
			{
				//80012EA4
				FLOAT_0x38 = SHORT_0x32;
			}
			//80012EC0
			else
			{
				float f31;
				
				//80012ECC
				if (0.0f == FLOAT_0x2C)
				{
					//80012ED0
					f31 = FLOAT_0x28;
				}
				//80012ED8
				else
				{
					f31 = FLOAT_0x28 + (FLOAT_0x2C * FLOAT_0x28 * (2.0f * mRandom.RandFloat() - 1.0f));
				}
				//80012F30
				if (WORD_0x24 & 0x100) //80012F38
				{
					//80012F3C
					float ratio = GetLODratio(VEC_0x90, mEffect->mSystem->VEC_0x5020, mEffect->mSystem->FLOAT_0x505C, mEffect->mSystem->FLOAT_0x5060, FLOAT_0x44, FLOAT_0x40);
					
					f31 *= FLOAT_0x48 + (1.0f - FLOAT_0x48) * ratio;
				}
				//80012F78
				FLOAT_0x38 += f31;
				//80012F88
				if (BYTE_0xDC && 0.0f != FLOAT_0x28 && FLOAT_0x38 < 1.0f)
				{
					FLOAT_0x38 = 1.0f;
				}
				//80012FB0 (END)
			}
			//80012FB0
			if (FLOAT_0x38 >= 1.0f)
			{
				//80012FC4
				Resource::GetInstance();
				//80012FC8
				EmitterResource * r11 = mResource;
				if (mForm)
				{
					//80012FD8
					if (mEffect->mEmissionPrologue)
					{
						//80012FE8
						//r3 <- this (r29)
						//r4 <- pManager (r30)
						//r5 <- stack_0x14
						//r6 <- stack_0x10
						//r7 <- stack_0x18
						//r8 <- stack_0x8
						//r9 <- stack_0xc
						//r10 <- stack_0x30
						
						int int_0x14 = (int)FLOAT_0x38;
						u32 word_0x10 = WORD_0x24;
						
						float arr_0x18[6];
						
						arr_0x18[0] = FLOAT_0x4C;
						arr_0x18[1] = FLOAT_0x50;
						arr_0x18[2] = FLOAT_0x54;
						arr_0x18[3] = FLOAT_0x58;
						arr_0x18[4] = FLOAT_0x5C;
						arr_0x18[5] = FLOAT_0x60;
						//8001308C
						u16 short_0x8 = r11->STRUCT_0x8.SHORT_0xA;
						
						float float_0xc = r11->STRUCT_0x8.SBYTE_0xC / 100.0f;
						
						MTX34 mtx(*pMtx); // at 0x30
						
						mEffect->mEmissionPrologue(this, pManager, &int_0x14,
						&word_0x10, arr_0x18, &short_0x8,
						&float_0xc, &mtx);
						//800130F4
						mForm->Emission(this, pManager, int_0x14,
						word_0x10, arr_0x18, short_0x8,
						float_0xc, &mtx);
						//goto 80013188 (END)
					}
					else //8001312C
					{
						//r0=r11->STRUCT_0x8.SBYTE_0xC
						//f0=FLOAT_0x38
						//r5 <- pManager
						mForm->Emission(this, pManager, (int)FLOAT_0x38,
						WORD_0x24, &FLOAT_0x4C, r11->STRUCT_0x8.SHORT_0xA,
						r11->STRUCT_0x8.SBYTE_0xC / 100.0f, pMtx);
						//80013188
					}
					//80013188 (END)
				}
				//80013188
				FLOAT_0x38 -= (s32)FLOAT_0x38;
				//800131B4 (END)
			}
			//800131B4
			if (BYTE_0xDC) BYTE_0xDC = 0;
			//800131C8 (END)
		}
		
		void Emitter::CalcEmitter()
		{
			if (GetFlagDisableCalc()) return;
			//8001320C
			if (WORD_0xC != 1) return;
			//80013218
			if (WORD_0xB4) return;
			//80013224
			if (SHORT_0xDE) return;
			//80013230
			u32 r31;
			
			if (!(mFlags & 0x4))
			{
				//8001323C
				r31 = WORD_0xE4;
				
				if (r31 >= SHORT_0x3C)
				{
					mEffect->RetireEmitter(this);
					return;
				}
			}
			else
			{
				//8001325C
				r31 = WORD_0xE4;
				
				if (r31 == 0xFFFF)
				{
					mEffect->RetireEmitter(this);
					return;
				}
			}
			//8001327C
			u32 r30 = (mFlags & 0x4) ? -1 : SHORT_0x3C;
			//80013290
			bool r29 = 0;
			//80013298
			
			for (u16 i = (!r31) ? 0 : mResource->NumEmitInitTrack(); i < mResource->NumEmitTrack(); i++) //80013468
			{
				//r5 <- mResource
				//r6 <- mResource->SkipEmitterDesc - mResource
				
				/*r3 <- len of particle desc*/				/**lwzx r3, r5, r6**/
				/*r4 <- GetParticleParameterDesc*/			/**add r4, r5, r6**/
				//r0 (for indexing) <- r28
				//r3 <- SkipParticleParameterDesc; add r3, r3, r4
				//GetEmitTrackTbl(); addi r3, r3, 4
				//GetEmitTrack(i); lwz r3, 4(r3)
				EmitTrack * pTrack = mResource->GetEmitTrack(i);
				
				if ((pTrack->BYTE_0x4 & 0x8) || (pTrack->BYTE_0x0 != 0xAC)) continue;
				//80013310
				u8 r4 = pTrack->BYTE_0x4;
				float * r4_2;
				switch (pTrack->SHORT_0x2)
				{
					case 0x0001:
						break;
					case 0x0007:
						break;
					case 0x0301:
						switch (r4)
						{
							case 0x44:
								r4_2 = &FLOAT_0x68;
								break;
							case 0x45:
								r4_2 = &FLOAT_0x6C;
								break;
							case 0x46:
								r4_2 = &FLOAT_0x70;
								break;
							case 0x49:
								r4_2 = &FLOAT_0x28;
								break;
							default:
								continue;
						}
						AnimCurveExecuteF32((u8 *)&pTrack, r4_2, r31, SHORT_0xEA, r30);
						break;
					case 0x0303:
						switch (r4)
						{
							case 0x47:
								AnimCurveExecuteF32((u8 *)&pTrack, &FLOAT_0x74, r31, SHORT_0xEA, r30);
								break;
						}
						break;
					case 0x0307:
						switch (r4)
						{
							case 0x41:
								r4_2 = &VEC_0x9C.x;
								break;
							case 0x42:
								r4_2 = &VEC_0xA8.x;
								break;
							case 0x43:
								r4_2 = &VEC_0x90.x;
								break;
							default:
								continue;
						}
						AnimCurveExecuteF32((u8 *)&pTrack, r4_2, r31, SHORT_0xEA, r30);
						r29 = true;
						break;
					default:
						if ((pTrack->SHORT_0x2 & 0xFF00) != 0x300)
						{
							// empty
						}
						else
						{
							switch (r4)
							{
								case 0x48:
									r4_2 = &FLOAT_0x7C;
									break;
								case 0x40:
									r4_2 = &FLOAT_0x4C;
									break;
								default:
									continue;
							}
							AnimCurveExecuteF32((u8 *)&pTrack, r4_2, r31, SHORT_0xEA, r30);
						}
						break;
				}
			}
			//8001349C
			if (r29) this->SetMtxDirty();
			//800134AC (END)
		}
		
		void Emitter::CalcParticle()
		{
			if (GetFlagDisableCalc()) return;
			
			ParticleManager * managers[0x400];
			
			u16 len = UtlistToArray(&mManagers.mActive, (void **)managers, mManagers.mActive.size);
			
			for (u16 i = 0; i < len; i++)
			{
				managers[i]->Calc();
			}
		}
		
		void Emitter::CalcEmission()
		{
			if (GetFlagDisableCalc() || WORD_0xB4) return;
			//8001357C
			
			WORD_0xB4 = 1;
			
			if (SHORT_0xE8) mEffect->mFlags |= 0x10000;
			//800135A0
			if (WORD_0xC == 1)
			{
				//800135AC
				MTX34 mtx_0x38;
				MTX34 mtx_0x8;
				
				ParticleManager * pManager = (ParticleManager *)List_GetFirst(&mManagers.mActive);
				
				pManager->CalcGlobalMtx(&mtx_0x8);
				
				MTX34Inv(&mtx_0x8, &mtx_0x8);
				
				CalcGlobalMtx(&mtx_0x38);
				MTX34Mult(&mtx_0x8, &mtx_0x38, &mtx_0x38);
				
				if (SHORT_0xDE)
				{
					SHORT_0xDE--; // also probably a timer
				}
				else
				{
					Emission(pManager, &mtx_0x38);
					WORD_0xE4++;
				}
			}
			else //80013624
			{
				if (SHORT_0xDE)
				{
					SHORT_0xDE--;
				}
				else
				{
					WORD_0xE4++;
				}
			}
		}
		
		void Emitter::CalcBillboard()
		{
			if (WORD_0xC != 1 && WORD_0xC != 2) return;
			
			if ((WORD_0x24 & 0x10000) && (WORD_0x24 & 0x8000)) return;
			
			//800136A4
			VEC_0xA8.z = 0.0f;
			VEC_0xA8.y = 0.0f;
			VEC_0xA8.x = 0.0f;
			
			mMtxDirtyFlag = true;
			
			MTX34 mtx_0xa8;
			MTX34 mtx_0x78;
			MTX34 mtx_0x48;
			MTX34 mtx_0x18;
			
			CalcGlobalMtx(&mtx_0xa8);
			MTX34Mult(&mEffect->mSystem->MTX_0x502C, &mtx_0x78, &mtx_0xa8);
			
			mtx_0x48 = mtx_0x78;
			
			float xxSquared = mtx_0x48.m[0][0] * mtx_0x48.m[0][0];
			float yxSquared = mtx_0x48.m[1][0] * mtx_0x48.m[1][0];
			float zxSquared = mtx_0x48.m[2][0] * mtx_0x48.m[2][0];
			
			float xSum = xxSquared + yxSquared + zxSquared;
			
			mtx_0x48.m[0][0] = (xSum <= 0.0f) ? 0.0f : FSqrt(xSum);
			mtx_0x48.m[0][1] = 0.0f;
			mtx_0x48.m[0][2] = 0.0f;
			
			float xySquared = mtx_0x48.m[0][1] * mtx_0x48.m[0][1];
			float yySquared = mtx_0x48.m[1][1] * mtx_0x48.m[1][1];
			float zySquared = mtx_0x48.m[2][1] * mtx_0x48.m[2][1];
			
			float ySum = xySquared + yySquared + zySquared;
			
			mtx_0x48.m[1][1] = (ySum <= 0.0f) ? 0.0f : FSqrt(ySum);
			mtx_0x48.m[1][2] = 0.0f;
			mtx_0x48.m[1][0] = 0.0f;
			
			float xzSquared = mtx_0x48.m[0][2] * mtx_0x48.m[0][2];
			float yzSquared = mtx_0x48.m[1][2] * mtx_0x48.m[1][2];
			float zzSquared = mtx_0x48.m[2][2] * mtx_0x48.m[2][2];
			
			float zSum = xzSquared + yzSquared + zzSquared;
			
			mtx_0x48.m[2][2] = (zSum <= 0.0f) ? 0.0f : FSqrt(zSum);
			mtx_0x48.m[2][1] = 0.0f;
			mtx_0x48.m[2][0] = 0.0f;
			
			//80013828
			if (WORD_0x24 & 0x8000)
			{
				MTX34RotXYZFIdx(&mtx_0x18, 64.0f, 0.0f, 0.0f);
				MTX34Mult(&mtx_0x48, &mtx_0x18, &mtx_0x48);
			}
			//80013854
			MTX34Inv(&mtx_0x78, &mtx_0x78);
			MTX34Mult(&mtx_0x78, &mtx_0x48, &mtx_0x78);
			
			VEC3 vec_0x8;
			
			vec_0x8.x = 1.0f / VEC_0x9C.x;
			vec_0x8.y = 1.0f / VEC_0x9C.y;
			vec_0x8.z = 1.0f / VEC_0x9C.z;
			
			MTX34Scale(&mtx_0x78, &mtx_0x78, &vec_0x8);
			MTX34Scale(&mtx_0x78, &VEC_0x9C, &mtx_0x78);
			MtxGetRotation(mtx_0x78, &VEC_0xA8);
			SetMtxDirty();
		}
		
		MTX34 * Emitter::RestructMatrix(MTX34 * pMtx1, MTX34 * pMtx2, bool b1, bool b2, s8 sbyte)
		{
			if (b1 && b2 && sbyte == 100)
			{
				*pMtx1 = *pMtx2;
				return pMtx1;
			}
			
			if (!b1 && !b2 && sbyte == 0)
			{
				MTX34Identity(pMtx1);
				return pMtx1;
			}
			
			MTX34Identity(pMtx1);
			
			if (sbyte)
			{
				//800139D0
				VEC3 vec_0x14;
				
				MtxGetTranslate(*pMtx2, &vec_0x14);
				VEC3Scale(&vec_0x14, &vec_0x14, sbyte / 100.0f);
				MTX34Trans(pMtx1, pMtx2, &vec_0x14);
				//80013A2C
			}
			//80013A2C
			if (b2)
			{
				//80013A34
				MTX34 mtx_0x20;
				
				MtxGetRotationMtx(*pMtx2, &mtx_0x20);
				MTX34Mult(pMtx1, pMtx1, &mtx_0x20); //PSMTXConcat(*pMtx1, mtx_0x20, *pMtx1)
				//80013A50
			}
			//80013A50
			if (b1)
			{
				//80013A58
				VEC3 vec_0x8;
				
				MtxGetScale(*pMtx2, &vec_0x8);
				MTX34Scale(pMtx1, pMtx1, &vec_0x8);
				//80013A74
			}
			//80013A74
			return pMtx1;
		}
		
		MTX34 * Emitter::CalcGlobalMtx(MTX34 * pMtx)
		{
			//r31 <- pMtx
			//r30 <- this
			
			if (mMtxDirtyFlag)
			{
				if (!mParent)
				{
					MTX34Copy(&mGlobalMtx, &mEffect->mRootMtx);
				}
				else
				{
					MTX34 mtx_0x8;
					
					mParent->CalcGlobalMtx(&mtx_0x8);
					RestructMatrix(&mGlobalMtx, &mtx_0x8, BYTE_0x64 & 1, BYTE_0x64 & 2, BYTE_0x65);
				}
				
				MTX34Trans(&mGlobalMtx, &mGlobalMtx, &VEC_0x90);
				
				MTX34 mtx_0x38;
				
				MTX34RotXYZFIdx(&mtx_0x38, 40.743664f * VEC_0xA8.x, 40.743664f * VEC_0xA8.y, 40.743664f * VEC_0xA8.z);
				MTX34Mult(&mGlobalMtx, &mGlobalMtx, &mtx_0x38); //PSMTXConcat(&mGlobalMtx, &mtx_0x38, &mGlobalMtx);
				MTX34Scale(&mGlobalMtx, &mGlobalMtx, &VEC_0x9C);
				
				mMtxDirtyFlag = false;
			}
			
			if (pMtx)
			{
				*pMtx = mGlobalMtx;
				
				return pMtx;
			}
			
			return &mGlobalMtx;
		}
		
		void Emitter::SetMtxDirty()
		{
			mMtxDirtyFlag = true;
			ParticleManager * curMgr = NULL;
			
			while (curMgr = (ParticleManager *)List_GetNext(&mManagers.mActive, curMgr))
			{
				curMgr->BOOL_0x8A = true;
			}
			//80013C34
			if (!mEffect) return;
			
			Emitter * curEmitter = NULL;
			
			while (curEmitter = (Emitter *)List_GetNext(&mEffect->mEmitters.mActive, curEmitter))
			{
				if (curEmitter->mMtxDirtyFlag) continue;
				
				for (Emitter * curParent = curEmitter->mParent; curParent; curParent = curParent->mParent)
				{
					if (curParent == this)
					{
						curEmitter->mMtxDirtyFlag = true;
						ParticleManager * curMgr = NULL;
						
						while (curMgr = (ParticleManager *)List_GetNext(&curEmitter->mManagers.mActive, curMgr))
						{
							curMgr->BOOL_0x8A = true;
						}
					}
				}
			}
		}
		
		u16 Emitter::GetNumParticleManager() const
		{
			return mManagers.mActive.size;
		}
		
		ParticleManager * Emitter::GetParticleManager(u16 i)
		{
			return (ParticleManager *)List_GetNth(&mManagers.mActive, i);
		}
		
		struct ParticleManagerIterationContext
		{
			u32 mCounter;
			Action mAction;
			u32 mArgument;
			bool BOOL_0xC;
		};
		
		static void foreachParticleManagerSub(void * thisEm, u32 arg)
		{
			ParticleManagerIterationContext * context = reinterpret_cast<ParticleManagerIterationContext *>(arg);
			
			context->mCounter += static_cast<Emitter *>(thisEm)->ForeachParticleManager(context->mAction, context->mArgument, context->BOOL_0xC, false);
		}
		
		u16 Emitter::ForeachParticleManager(Action action, u32 arg, bool b1, bool b2)
		{
			ParticleManager * nextMgr;
			ParticleManager * curMgr;
			
			u32 counter = 0;
			
			for (curMgr = (ParticleManager *)List_GetFirst(&mManagers.mActive); curMgr; curMgr = nextMgr)
			{
				nextMgr = (ParticleManager *)List_GetNext(&mManagers.mActive, curMgr);
				
				if (b1 || curMgr->WORD_0xC != 1)
				{
					action(curMgr, arg);
					counter++;
				}
			}
			
			if (b2)
			{
				ParticleManagerIterationContext context = { 0, action, arg, b1 };
				
				mEffect->ForeachEmitterFrom(foreachParticleManagerSub, (u32)&context, true, this);
				
				counter += context.mCounter;
			}
			
			return counter;
		}
	}
}
