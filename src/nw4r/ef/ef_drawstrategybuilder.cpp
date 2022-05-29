#pragma ipa file

#include "ef_drawstrategybuilder.h"
#include "ef_drawstrategy.h"
#include "ef_drawsmoothstripestrategy.h"
#include "ef_drawstripestrategy.h"
#include "ef_drawpointstrategy.h"
#include "ef_drawlinestrategy.h"
#include "ef_drawfreestrategy.h"
#include "ef_drawdirectionalstrategy.h"
#include "ef_drawbillboardstrategy.h"

namespace nw4r
{
	namespace ef
	{
		DrawStrategy * DrawStrategyBuilder::Create(u32 strategyType)
		{
			static DrawBillboardStrategy billboardStrategy;
			static DrawDirectionalStrategy directionalStrategy;
			static DrawFreeStrategy freeStrategy;
			static DrawLineStrategy lineStrategy;
			static DrawPointStrategy pointStrategy;
			static DrawStripeStrategy stripeStrategy;
			static DrawSmoothStripeStrategy smoothStripeStrategy;
			
			switch (strategyType)
			{
				case DrawStratType_Billboard:
					return &billboardStrategy;
				case DrawStratType_Directional:
					return &directionalStrategy;
				case DrawStratType_Free:
					return &freeStrategy;
				case DrawStratType_Line:
					return &lineStrategy;
				case DrawStratType_Point:
					return &pointStrategy;
				case DrawStratType_Stripe:
					return &stripeStrategy;
				case DrawStratType_SmoothStripe:
					return &smoothStripeStrategy;
			}
			
			return &billboardStrategy;
		}		
	}
}