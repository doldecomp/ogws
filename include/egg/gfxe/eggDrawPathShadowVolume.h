#ifndef EGG_GFXE_DRAW_PATH_SHADOW_VOLUME_H
#define EGG_GFXE_DRAW_PATH_SHADOW_VOLUME_H
#include <egg/types_egg.h>

#include <egg/gfxe/eggDrawPathBase.h>

namespace EGG {

class DrawPathShadowVolume : public DrawPathBase {
    friend class ScnRenderer;

public:
    DrawPathShadowVolume();
    virtual ~DrawPathShadowVolume(); // at 0x8
    virtual u16 getNumStep() const;  // at 0x1C
    virtual void internalCalc();     // at 0x24
    virtual void internalDraw(u16);  // at 0x28

private:
    enum Step {
        cStep_0,
        cStep_1,
        cStep_2,

        cStep_Max
    };

private:
    char UNK_0x7C[0x98 - 0x7C];
};

} // namespace EGG

#endif
