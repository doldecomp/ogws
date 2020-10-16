#ifndef NW4R_EF_DRAWSTRIPESTRATEGY_H
#define NW4R_EF_DRAWSTRIPESTRATEGY_H
#include "types_nw4r.h"
#include "ef_drawstrategyimpl.h"

namespace nw4r
{
	namespace ef
	{
		//TODO: Implement the object accurately
		struct DrawStripeStrategy : DrawStrategyImpl
		{
			DrawStripeStrategy();
			~DrawStripeStrategy();
			
			UNKTYPE Draw(const DrawInfo &, ParticleManager *);
			virtual UNKTYPE GetCalcAheadFunc(ParticleManager *);
		};
	}
}

#endif