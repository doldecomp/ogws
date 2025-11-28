#ifndef EGG_GFXE_DRAW_PATH_DOF_H
#define EGG_GFXE_DRAW_PATH_DOF_H
#include <egg/types_egg.h>

#include <egg/gfxe/eggDrawPathBase.h>

namespace EGG {

class DrawPathDOF : public DrawPathBase {
public:
    DrawPathDOF();
    virtual ~DrawPathDOF();         // at 0x8
    virtual int getNumStep() const; // at 0x1C
    virtual void internalCalc();    // at 0x24
    virtual void internalDraw(u16); // at 0x28

private:
    char UNK_0x7C[0xB4 - 0x7C];
};

} // namespace EGG

#endif
