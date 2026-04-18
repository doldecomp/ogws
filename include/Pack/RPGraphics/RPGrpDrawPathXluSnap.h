#ifndef RP_GRAPHICS_DRAW_PATH_XLU_SNAP_H
#define RP_GRAPHICS_DRAW_PATH_XLU_SNAP_H
#include <Pack/types_pack.h>

#include <Pack/RPGraphics/RPGrpDrawPath.h>

#include <egg/gfxe.h>

//! @addtogroup rp_graphics
//! @{

class RPGrpDrawPathXluSnap : public RPGrpDrawPath {
public:
    RPGrpDrawPathXluSnap(EGG::ScnRenderer* pRenderer)
        : RPGrpDrawPath(pRenderer, pRenderer->getDrawPathBase(
                                       EGG::ScnRenderer::DRAW_PATH_XLU_SNAP)) {

        mpXluSnap = static_cast<EGG::DrawPathXluSnap*>(
            pRenderer->getDrawPathBase(EGG::ScnRenderer::DRAW_PATH_XLU_SNAP));
    }

private:
    EGG::DrawPathXluSnap* mpXluSnap; // at 0xC
};

//! @}

#endif
