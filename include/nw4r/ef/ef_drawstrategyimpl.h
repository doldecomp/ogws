#ifndef NW4R_EF_DRAWSTRATEGYIMPL_H
#define NW4R_EF_DRAWSTRATEGYIMPL_H
#include "ef_drawstrategy.h"

namespace nw4r
{
	namespace ef
	{
		struct DrawStrategyImpl : DrawStrategy
		{
			DrawStrategyImpl();
			
			virtual UNKTYPE GetGetFirstDrawParticleFunc(int);
			virtual UNKTYPE GetGetNextDrawParticleFunc(int);
			
			char UNK_0x4[0xB8];
		};
	}
}

#endif