#ifndef EGG_GFXE_DRAW_PATH_HDR_H
#define EGG_GFXE_DRAW_PATH_HDR_H
#include <egg/types_egg.h>

#include <egg/gfxe/eggDrawPathBase.h>

namespace EGG {

// Forward declarations
class PostEffectHDR;

class DrawPathHDR : public DrawPathBase {
    friend class ScnRenderer;

public:
    DrawPathHDR();
    virtual ~DrawPathHDR();              // at 0x8
    virtual u16 getNumStep() const;      // at 0x1C
    virtual void internalCalc();         // at 0x24
    virtual void internalDraw(u16 step); // at 0x28

private:
    enum Step {
        cStep_Capture,
        cStep_Draw,

        cStep_Max
    };

private:
    PostEffectHDR* mpPostEffect; // at 0x7C
};

} // namespace EGG

#endif
