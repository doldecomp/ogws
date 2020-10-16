#ifndef NW4R_EF_DRAWPOINTSTRATEGY_H
#define NW4R_EF_DRAWPOINTSTRATEGY_H
#include "types_nw4r.h"
#include "ef_drawstrategyimpl.h"

namespace nw4r
{
	namespace ef
	{
		//TODO: Implement the object accurately
		struct DrawPointStrategy : DrawStrategyImpl
		{
			DrawPointStrategy();
			~DrawPointStrategy();
			
			UNKTYPE Draw(const DrawInfo &, ParticleManager *);
		};
	}
}

#endif