#ifndef NW4R_EF_DRAWFREESTRATEGY_H
#define NW4R_EF_DRAWFREESTRATEGY_H
#include "types_nw4r.h"
#include "ef_drawstrategyimpl.h"

namespace nw4r
{
	namespace ef
	{
		//TODO: Implement the object accurately
		struct DrawFreeStrategy : DrawStrategyImpl
		{
			DrawFreeStrategy();
			~DrawFreeStrategy();
			
			UNKTYPE Draw(const DrawInfo &, ParticleManager *);
		};
	}
}

#endif