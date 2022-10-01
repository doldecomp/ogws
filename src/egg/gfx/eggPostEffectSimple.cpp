#include "eggPostEffectSimple.h"
#include "eggDrawGX.h"
#include "eggCapTexture.h"

#include <GX/GXAttr.h>
#include <GX/GXTev.h>
#include <GX/GXBump.h>

namespace EGG
{
    PostEffectSimple::PostEffectSimple()
    {
    }

    void PostEffectSimple::reset()
    {
        mColor = DrawGX::scColorWhite;
        FLOAT_0x24 = 1.0f;
        WORD_0x2C = 1;
    }

    void PostEffectSimple::preDraw()
    {
        loadTexObj();

        GXColor color = mColor;
        if (FLOAT_0x24 < 1.0f)
        {
            scaleColor(color, color, FLOAT_0x24, true);
        }

        setMatColorChannel();

        GXSetNumTexGens(1);
        GXSetTexCoordGen2(GX_TEX_COORD_ID_0, GX_TEX_GEN_TYPE_1,
            GX_TEX_GEN_SRC_4, 0x3C, 0, 0x7D);
        setMatInd();

        GXSetNumTevStages(1);
        GXSetTevDirect(0);
        GXSetTevSwapMode(GX_TEV_STAGE_ID_0, 0, 0);
        GXSetTevSwapModeTable(GX_TEV_SWAP_SEL_0, 0, 1, 2, 3);
        GXSetTevKColorSel(GX_TEV_STAGE_ID_0, 0xC);
        GXSetTevKAlphaSel(GX_TEV_STAGE_ID_0, 0x1C);
        GXSetTevKColor(GX_TEV_REG_ID_0, color);
        GXSetTevOrder(GX_TEV_STAGE_ID_0, GX_TEX_COORD_ID_0,
            mpCapTexture->getLoadMap(), 0xFF);
        GXSetTevColorIn(GX_TEV_STAGE_ID_0, 0xF, 0x8, 0xE, 0xF);
        GXSetTevColorOp(GX_TEV_STAGE_ID_0, 0, 0, 0, 1, 0);

        switch(WORD_0x2C)
        {
            case 0:
                GXSetTevAlphaIn(GX_TEV_STAGE_ID_0, 7, 7, 7, 6);
                break;
            case 1:
                GXSetTevAlphaIn(GX_TEV_STAGE_ID_0, 7, 4, 6, 7);
                break;
            case 2:
                GXSetTevColorIn(GX_TEV_STAGE_ID_0, 0xF, 0x9, 0xE, 0xF);
                GXSetTevAlphaIn(GX_TEV_STAGE_ID_0, 7, 6, 6, 7);
                break;
        }

        GXSetTevAlphaOp(GX_TEV_STAGE_ID_0, 0, 0, 0, 1, 0);
        setMatPE();
    }
}