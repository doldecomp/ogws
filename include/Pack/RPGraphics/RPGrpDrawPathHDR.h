#ifndef RP_GRAPHICS_DRAW_PATH_HDR_H
#define RP_GRAPHICS_DRAW_PATH_HDR_H
#include <Pack/types_pack.h>

#include <Pack/RPGraphics/RPGrpDrawPath.h>

#include <egg/gfxe.h>

//! @addtogroup rp_graphics
//! @{

class RPGrpDrawPathHDR : public RPGrpDrawPath {
public:
    RPGrpDrawPathHDR(EGG::ScnRenderer* pRenderer)
        : RPGrpDrawPath(pRenderer, pRenderer->getDrawPathBase(
                                       EGG::ScnRenderer::DRAW_PATH_HDR)) {}
};

//! @}

#endif
