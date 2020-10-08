#ifndef NW4R_EF_PARTICLEMANAGER
#define NW4R_EF_PARTICLEMANAGER
#include "types_nw4r.h"
#include "math_types.h"
#include "ef_list.h"
#include "ef_ref.h"

namespace nw4r
{
	namespace ef
	{
		struct ParticleManager : ReferencedObject
		{
			UNKTYPE BeginDraw();
			UNKTYPE EndDraw();
			UNKTYPE BeginCalc(bool);
			UNKTYPE EndCalc();
			
			UNKTYPE SendClosing();
			UNKTYPE DestroyFunc();
			virtual UNKTYPE Initialize(Emitter *, EmitterResource *);
			virtual UNKTYPE CreateParticle(u16, math::VEC3, math::VEC3, const math::MTX34 *, float, const EmitterInheritSetting *, Particle *, u16);
			virtual UNKTYPE Calc();
			virtual UNKTYPE Draw(const DrawInfo &);
			
			char UNK_0x20[0x18];
			ActivityList EFLIST_0x38;
			char UNK_0x52[0x35];
			
			u8 BYTE_0x89;
		};
	}
}

#endif