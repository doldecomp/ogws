#include "ef_creationqueue.h"
#include "ef_emitter.h"
#include "ef_particle.h"
#include "ef_particlemanager.h"

namespace nw4r
{
	namespace ef
	{
		CreationQueue::CreationQueue() : mSize() {}
		
		void CreationQueue::AddParticleCreation(const EmitterInheritSetting * pInherit, Particle * pParticle, EmitterResource * pRes, u16 num)
		{
			if (mSize < 0x400)
			{
				mCreations[mSize].mType = CreationType_Particle;
				mCreations[mSize].SHORT_0x2 = num;
				mCreations[mSize].mInheritSetting = *pInherit; // at 0x4
				mCreations[mSize].mParticle = pParticle; // at 0xc
				
				pParticle->Ref();
				
				mCreations[mSize].mResource = pRes; // at 0x10
				
				mSize++;
			}
		}
		
		void CreationQueue::AddEmitterCreation(const EmitterInheritSetting * pInherit, Particle * pParticle, EmitterResource * pRes, u16 num)
		{
			if (mSize < 0x400)
			{
				mCreations[mSize].mType = CreationType_Emitter;
				mCreations[mSize].SHORT_0x2 = num;
				mCreations[mSize].mInheritSetting = *pInherit; // at 0x4
				mCreations[mSize].mParticle = pParticle; // at 0xc
				
				pParticle->Ref();
				
				mCreations[mSize].mResource = pRes; // at 0x10
				
				mSize++;
			}
		}
		
		void CreationQueue::Execute()
		{
			for (int i = 0; i < mSize; i++)
			{
				Creation & cur = mCreations[i];
				switch (cur.mType)
				{
					case CreationType_Particle:
						cur.mParticle->mManager->mEmitter->CreateEmitterTmp(cur.mResource, &cur.mInheritSetting, cur.mParticle, cur.SHORT_0x2);
						cur.mParticle->UnRef();
						break;
					case CreationType_Emitter:
						cur.mParticle->mManager->mEmitter->CreateEmitter(cur.mResource, &cur.mInheritSetting, cur.mParticle, cur.SHORT_0x2);
						cur.mParticle->UnRef();
						break;
				}
			}
			
			mSize = 0;
		}
	}
}