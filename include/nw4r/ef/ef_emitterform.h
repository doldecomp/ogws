#ifndef NW4R_EF_EMITTERFORM_H
#define NW4R_EF_EMITTERFORM_H
#include "types_nw4r.h"

namespace nw4r
{
	namespace ef
	{
		struct EmitterForm
		{
			virtual UNKTYPE Emission(Emitter *, ParticleManager *, int, u32, float *, u16, float, const math::MTX34 *);
		};
	}
}

#endif