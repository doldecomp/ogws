#ifndef NW4R_EF_DRAW_ORDER_H
#define NW4R_EF_DRAW_ORDER_H
#include <nw4r/types_nw4r.h>

namespace nw4r {
namespace ef {

// Forward declarations
class Effect;
class ParticleManager;
class DrawInfo;

class DrawOrderBase {
public:
    DrawOrderBase() {}

    virtual void Add(Effect* pEffect, ParticleManager* pManager) = 0; // at 0x8
    virtual void Remove(Effect* pEffect,
                        ParticleManager* pManager) = 0;            // at 0xC
    virtual void Draw(Effect* pEffect, const DrawInfo& rInfo) = 0; // at 0x10

    static ut::List* GetPMList(Effect* pEffect);
};

class DrawOrder : public DrawOrderBase {
public:
    virtual void Add(Effect* pEffect, ParticleManager* pManager); // at 0x8
    virtual void Remove(Effect* pEffect,
                        ParticleManager* pManager);            // at 0xC
    virtual void Draw(Effect* pEffect, const DrawInfo& rInfo); // at 0x10
};

} // namespace ef
} // namespace nw4r

#endif
