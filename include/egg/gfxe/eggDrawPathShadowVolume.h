#ifndef EGG_GFXE_DRAW_PATH_SHADOW_VOLUME_H
#define EGG_GFXE_DRAW_PATH_SHADOW_VOLUME_H
#include "eggDrawPathBase.h"
#include "types_egg.h"

namespace EGG {
class DrawPathShadowVolume : public DrawPathBase {
public:
    DrawPathShadowVolume();
    virtual int getNumScnProc() const; // at 0x1C
    virtual void calc();               // at 0x24
    virtual void draw(u16);            // at 0x28
    virtual ~DrawPathShadowVolume();   // at 0x8

private:
    char UNK_0x7C[0x98 - 0x7C];
};
} // namespace EGG

#endif
