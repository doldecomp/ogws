#ifndef NW4R_EF_EMITTER
#define NW4R_EF_EMITTER
#include "types_nw4r.h"
#include "ef_ref.h"
#include "ef_list.h"
#include "ef_util.h"

namespace nw4r
{
	namespace ef
	{
		struct Emitter : ReferencedObject
		{
			virtual bool Initialize(Effect *, EmitterResource *, u8); // at 0x10
			virtual UNKTYPE CreateEmitter(EmitterResource *, EmitterInheritSetting *, Particle *, u16); // at 0x14
			virtual UNKTYPE CalcEmitter(); // at 0x18
			virtual UNKTYPE CalcParticle(); // at 0x1c
			virtual UNKTYPE CalcEmission(); // at 0x20
			virtual UNKTYPE CalcBillboard(); // at 0x24
			
			char UNK_0x20[0x4];
			UNKWORD WORD_0x24;
			char UNK_0x28[0x8C];
			UNKWORD WORD_0xB4;
			char UNK_0xB8[0x4];
			UNKREF * REF_0xBC;
			ActivityList EFLIST_0xC0;
			char UNK_0xDA[0x6];
			UNKWORD WORD_0xE4;
			u16 SHORT_0xE8;
			char UNK_0xEC[0x8];
			Emitter * EMITTER_0xF4;
			UNKREF * REF_0xF8;
			
			u16 RetireParticleAll();
			
			u16 ForeachParticleManager(Action, u32, bool, bool);
			UNKTYPE SetMtxDirty();
		};
	}
}

#endif