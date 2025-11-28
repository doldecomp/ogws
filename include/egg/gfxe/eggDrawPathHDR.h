#ifndef EGG_GFXE_DRAW_PATH_HDR_H
#define EGG_GFXE_DRAW_PATH_HDR_H
#include <egg/types_egg.h>

#include <egg/gfxe/eggDrawPathBase.h>

namespace EGG {

class DrawPathHDR : public DrawPathBase {
public:
    DrawPathHDR();
    virtual ~DrawPathHDR();              // at 0x8
    virtual int getNumStep() const;      // at 0x1C
    virtual void internalCalc();         // at 0x24
    virtual void internalDraw(u16 step); // at 0x28

private:
    enum EStep {
        EStep_0,
        EStep_1,

        EStep_Max
    };

private:
    PostEffectHDR* mPostEffect; // at 0x7C
};

} // namespace EGG

#endif
