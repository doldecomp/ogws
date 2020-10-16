#ifndef NW4R_EF_DRAWLINESTRATEGY_H
#define NW4R_EF_DRAWLINESTRATEGY_H
#include "types_nw4r.h"
#include "ef_drawstrategyimpl.h"

namespace nw4r
{
	namespace ef
	{
		//TODO: Implement the object accurately
		struct DrawLineStrategy : DrawStrategyImpl
		{
			DrawLineStrategy();
			~DrawLineStrategy();
			
			UNKTYPE Draw(const DrawInfo &, ParticleManager *);
		};
	}
}

#endif