#ifndef NW4R_EF_DRAW_FREE_STRATEGY_H
#define NW4R_EF_DRAW_FREE_STRATEGY_H
#include "types_nw4r.h"
#include "ef_drawstrategyimpl.h"

namespace nw4r
{
    namespace ef
    {
        class DrawFreeStrategy : public DrawStrategyImpl
        {
        public:
            DrawFreeStrategy();
            
            virtual UNKTYPE Draw(const DrawInfo &, ParticleManager *);
        };
    }
}

#endif
