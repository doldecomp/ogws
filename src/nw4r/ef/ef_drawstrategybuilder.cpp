#include <nw4r/ef.h>

namespace nw4r {
namespace ef {

DrawStrategy* DrawStrategyBuilder::Create(u32 type) {
    static DrawBillboardStrategy billboardStrategy;
    static DrawDirectionalStrategy directionalStrategy;
    static DrawFreeStrategy freeStrategy;
    static DrawLineStrategy lineStrategy;
    static DrawPointStrategy pointStrategy;
    static DrawStripeStrategy stripeStrategy;
    static DrawSmoothStripeStrategy smoothStripeStrategy;

    switch (type) {
    case DRAWSTRATEGY_BILLBOARD: {
        return &billboardStrategy;
    }

    case DRAWSTRATEGY_DIRECTIONAL: {
        return &directionalStrategy;
    }

    case DRAWSTRATEGY_FREE: {
        return &freeStrategy;
    }

    case DRAWSTRATEGY_LINE: {
        return &lineStrategy;
    }

    case DRAWSTRATEGY_POINT: {
        return &pointStrategy;
    }

    case DRAWSTRATEGY_STRIPE: {
        return &stripeStrategy;
    }

    case DRAWSTRATEGY_SMOOTHSTRIPE: {
        return &smoothStripeStrategy;
    }

    default: {
        return &billboardStrategy;
    }
    }
}

} // namespace ef
} // namespace nw4r
