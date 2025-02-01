#ifndef NW4R_EF_DRAW_STRATEGY_DRAW_LINE_STRATEGY_H
#define NW4R_EF_DRAW_STRATEGY_DRAW_LINE_STRATEGY_H
#include <nw4r/types_nw4r.h>

#include <nw4r/ef/drawstrategy/ef_drawstrategyimpl.h>

namespace nw4r {
namespace ef {

class DrawLineStrategy : public DrawStrategyImpl {
public:
    DrawLineStrategy();

    virtual void Draw(const DrawInfo& rInfo,
                      ParticleManager* pManager); // at 0xC

    void InitGraphics(const DrawInfo& rInfo, ParticleManager* pManager);
};

} // namespace ef
} // namespace nw4r

#endif
