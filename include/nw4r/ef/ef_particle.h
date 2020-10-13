#ifndef NW4R_EF_PARTICLE_H
#define NW4R_EF_PARTICLE_H
#include "types_nw4r.h"
#include "ef_ref.h"

namespace nw4r
{
	namespace ef
	{
		struct Particle : ReferencedObject
		{
			math::VEC3 VEC_0xAC;
			math::VEC3 VEC_0xB8;
			ParticleManager * mManager; // at 0xc8
		};
	}
}

#endif