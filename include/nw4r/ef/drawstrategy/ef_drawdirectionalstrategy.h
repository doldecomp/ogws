#ifndef NW4R_EF_DRAW_DIRECTIONAL_STRATEGY_H
#define NW4R_EF_DRAW_DIRECTIONAL_STRATEGY_H
#include <nw4r/types_nw4r.h>

#include <nw4r/ef/drawstrategy/ef_drawstrategyimpl.h>

namespace nw4r {
namespace ef {

class DrawDirectionalStrategy : public DrawStrategyImpl {
public:
    DrawDirectionalStrategy();

    virtual void Draw(const DrawInfo& rInfo,
                      ParticleManager* pManager); // at 0xC

    virtual CalcAheadFunc
    GetCalcAheadFunc(ParticleManager* pManager); // at 0x18
private:
    void DrawDirectional(const DrawInfo& rInfo, ParticleManager* pManager);
    void DrawDirectionalBillboard(const DrawInfo& rInfo, ParticleManager* pManager);
    void InitGraphics(const DrawInfo& rInfo, ParticleManager* pManager);

    enum DirectionalPivot {
        DIRECTIONAL_PIVOT_NOP,
        DIRECTIONAL_PIVOT_BILLBOARD,
        DIRECTIONAL_PIVOT__MASK = 0x3
    };

    DirectionalPivot GetDirectionalPivot(const EmitterDrawSetting& rSetting) {
        return static_cast<DirectionalPivot>(rSetting.typeOption2 & DIRECTIONAL_PIVOT__MASK);
    }
};

} // namespace ef
} // namespace nw4r

#endif
