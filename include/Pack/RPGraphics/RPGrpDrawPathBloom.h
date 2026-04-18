#ifndef RP_GRAPHICS_DRAW_PATH_BLOOM_H
#define RP_GRAPHICS_DRAW_PATH_BLOOM_H
#include <Pack/types_pack.h>

#include <Pack/RPGraphics/RPGrpDrawPath.h>

#include <egg/gfxe.h>

//! @addtogroup rp_graphics
//! @{

class RPGrpDrawPathBloom : public RPGrpDrawPath {
public:
    RPGrpDrawPathBloom(EGG::ScnRenderer* pRenderer)
        : RPGrpDrawPath(pRenderer, pRenderer->getDrawPathBase(
                                       EGG::ScnRenderer::DRAW_PATH_BLOOM)) {

        mpBloom = static_cast<EGG::DrawPathBloom*>(
            pRenderer->getDrawPathBase(EGG::ScnRenderer::DRAW_PATH_BLOOM));
    }

private:
    char unkC[0x10 - 0xC];
    EGG::DrawPathBloom* mpBloom; // at 0x10
};

//! @}

#endif
