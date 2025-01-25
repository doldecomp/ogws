#ifndef NW4R_EF_DRAW_STRATEGY_DRAW_STRATEGY_BUILDER_H
#define NW4R_EF_DRAW_STRATEGY_DRAW_STRATEGY_BUILDER_H
#include <nw4r/types_nw4r.h>

namespace nw4r {
namespace ef {

enum DrawStrategyType {
    DRAWSTRATEGY_POINT,
    DRAWSTRATEGY_LINE,
    DRAWSTRATEGY_FREE,
    DRAWSTRATEGY_BILLBOARD,
    DRAWSTRATEGY_DIRECTIONAL,
    DRAWSTRATEGY_STRIPE,
    DRAWSTRATEGY_SMOOTHSTRIPE
};

class DrawStrategyBuilder {
public:
    virtual DrawStrategy* Create(u32 type); // at 0x8
};

} // namespace ef
} // namespace nw4r

#endif
