#ifndef NW4R_EF_DRAWORDER
#define NW4R_EF_DRAWORDER
#include "types_nw4r.h"
#include "ef_particlemanager.h"
#include "ef_draworderbase.h"

namespace nw4r
{
	namespace ef
	{
		struct DrawOrder : DrawOrderBase
		{
			virtual void Draw(Effect *, const DrawInfo &);
			virtual void Add(Effect *, ParticleManager *);
			virtual void Remove(Effect *, ParticleManager *);
		};
	}
}

#endif