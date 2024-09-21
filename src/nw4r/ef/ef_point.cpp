#include "math_types.h"
#include "ef_rand.h"
#include "ef_emitter.h"
#include "ef_point.h"
#include "ef_particle.h"
#include "ef_particlemanager.h"

namespace nw4r
{
	using namespace math;
	
	namespace ef
	{
		void EmitterFormPoint::Emission(Emitter * pEmitter, ParticleManager * pManager,
			int particleCount, u32 r_7, float * r_8, u16 r28_9, float f23_1, const MTX34 * pMtx)
		{
			//r24 <- this
			//r25 <- pEmitter
			//r26 <- pManager
			//r29 <- pMtx
			
			//f21 = int2float convconst signed
			//f22 = 0.01f
			//f24 = 0.0f
			//f26 = 65536.0f
			//f25 = int2float convconst unsigned
			if (particleCount < 1) return;
			
			for (int i = 0; i < particleCount; i++)
			{
				VEC3 vec_0x44(0.0f, 0.0f, 0.0f);
				float f1 = 2.0f * pEmitter->mRandom.RandFloat() - 1.0f;
				/*double d1;
				if (f1 >= 0.0f)
				{
					//8001D610
					d1 = f1 * (0.66f + 0.34f * f1);
				}
				else
				{
					//8001D620
					d1 = f1 * (0.66f - 0.34f * f1);
				}*/
				//8001D62C
				VEC3 vec_0x38;
				//f1 = d1;
				
				vec_0x38.x = (f1 >= 0.0f) ?
					((0.66f + 0.34f * f1) * f1) :
					((0.66f - 0.34f * f1) * f1);
				
				float diagLen = (float)sqrt(1.0f - vec_0x38.x * vec_0x38.x); // at f20
				float angle = 2.0f * (pEmitter->mRandom.RandFloat() * NW4R_MATH_PI); // at f19
				
				vec_0x38.y = diagLen * (float)cos(angle);
				vec_0x38.z = diagLen * (float)sin(angle);
				
				VEC3 vec_0x2c(vec_0x38.x, 0.0f, vec_0x38.z);
				
				/*
				vec_0x2c.x = vec_0x38.x;
				vec_0x2c.y = 0.0f;
				vec_0x2c.z = vec_0x38.z;
				*/
				
				if (0.0f != vec_0x2c.x || 0.0f != vec_0x2c.z)
				{
					VEC3Normalize(&vec_0x2c, &vec_0x2c);
				}
				//lbl_8001D6C8
				VEC3 vec_0x20;
				this->CalcVelocity(&vec_0x20, pEmitter, vec_0x44, vec_0x38, vec_0x38, vec_0x2c);
				
				float f20 = pEmitter->mRandom.RandFloat();
				/*
				VEC3 vec_0x8(vec_0x20);
				
				VEC3 vec_0x14(vec_0x2c);
				*/
				
				pManager->CreateParticle(this->CalcLife(r28_9, f23_1, pEmitter), vec_0x44, vec_0x20, pMtx,
					1.0f + 0.01f * pEmitter->BYTE_0x67 * f20, &pEmitter->mInheritSettings, pEmitter->REF_0xF8, pEmitter->SHORT_0xE8);
			}
			
		}
	}
}
