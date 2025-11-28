#ifndef EGG_GFXE_DRAW_PATH_BASE_H
#define EGG_GFXE_DRAW_PATH_BASE_H
#include <egg/types_egg.h>

#include <egg/gfxe/eggIDrawGX.h>
#include <egg/gfxe/eggIScnProc.h>
#include <egg/gfxe/eggScreenEffectBase.h>

#include <egg/prim.h>

namespace EGG {

class DrawPathBase : public ScreenEffectBase, public IScnProc {
public:
    DrawPathBase();
    virtual ~DrawPathBase() {}               // at 0x8
    virtual int getNumStep() const = 0;      // at 0x1C
    virtual void internalResetForDraw() {}   // at 0x20
    virtual void internalCalc() {}           // at 0x24
    virtual void internalDraw(u16 step) = 0; // at 0x28
    virtual void scnProcDraw(u16 step);      // at 0x2C

    void calc();
};

} // namespace EGG

#endif
