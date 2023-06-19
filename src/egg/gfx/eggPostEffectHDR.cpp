#include "eggPostEffectHDR.h"
#include "eggCapTexture.h"
#include "eggDrawGX.h"
#include <revolution/GX/GXAttr.h>
#include <revolution/GX/GXTev.h>
#include <revolution/GX/GXBump.h>

namespace EGG
{
    PostEffectHDR::PostEffectHDR()
    {
    }

    void PostEffectHDR::reset()
    {
        COLOR_0x38 = DrawGX::scColorWhite;
        COLOR_0x30 = COLOR_0x38;
        COLOR_0x20 = COLOR_0x38;
        COLOR_0x34 = COLOR_0x38;
        COLOR_0x24 = COLOR_0x38;

        FLOAT_0x2C = 1.0f;
        FLOAT_0x28 = 0.0f;

        BYTE_0x45 = 0;
        WORD_0x3C = 0;
        WORD_0x40 = 0;
    }

    void PostEffectHDR::setupRange()
    {
        f32 six = 6.0f;
        f32 scale = 1.0f / six;
        scale = (FLOAT_0x2C > scale) ? FLOAT_0x2C : scale;

        BYTE_0x44 = 0;
        scale = 1.0f / scale - 1.0f;
        if (scale <= 1.0f)
        {
            WORD_0x3C = 0;
            WORD_0x40 = 0;
        }
        else if (scale <= 2.0f)
        {
            WORD_0x3C = 0;
            WORD_0x40 = 1;
            scale = 0.5f * (scale - 1.0f);
        }
        else if (scale <= 3.0f)
        {
            WORD_0x3C = 0;
            WORD_0x40 = 1;
            scale = 0.5f * (1.0f + (scale - 2.0f));
        }
        else if (scale <= 4.0f)
        {
            WORD_0x3C = 0;
            WORD_0x40 = 2;
            scale = 0.25f * (scale - 3.0f);
        }
        else if (scale <= 5.0f)
        {
            WORD_0x3C = 0;
            WORD_0x40 = 2;
            scale = 0.25f * (1.0f + (scale - 4.0f));
        }
        
        GXColor sp0C;
        scaleColor(sp0C, COLOR_0x20, FLOAT_0x28, true);
        GXColor sp08;
        scaleColor(sp08, COLOR_0x24, scale, true);

        COLOR_0x30 = sp08;
        COLOR_0x34 = sp0C;
    }

    void PostEffectHDR::preDraw()
    {
        setupRange();
        loadTexObj();

        const int stages0 = (BYTE_0x45 & 1);
        const int stages1 = stages0 + 2;
        
        setMatColorChannel();
        GXSetNumTexGens(1);
        GXSetTexCoordGen2(GX_TEX_COORD_ID_0, GX_TEX_GEN_TYPE_1, GX_TEX_GEN_SRC_4, 0x3C, 0, 0x7D);
        setMatInd();
        GXSetTevKColor(GX_TEV_REG_ID_0, COLOR_0x34);
        GXSetTevKColor(GX_TEV_REG_ID_1, COLOR_0x30);
        GXSetTevSwapModeTable(GX_TEV_SWAP_SEL_0, 0, 1, 2, 3);
        GXSetNumTevStages(stages1);

        for (int i = 0; i < stages1; i++)
        {
            GXSetTevDirect(i);
            GXSetTevSwapMode((GXTevStageID)i, 0, 0);

            switch(i)
            {
                case 0:
                    GXSetTevKColorSel((GXTevStageID)i, 0xC);
                    GXSetTevOrder((GXTevStageID)i, GX_TEX_COORD_ID_0, getCapTexture()->getLoadMap(), 0xFF);
                    GXSetTevColorIn((GXTevStageID)i, 0xE, 0xF, 0xF, 0x8);
                    GXSetTevColorOp((GXTevStageID)i, 1, 0, WORD_0x3C, 1, 1);
                    break;
                case 1:
                    GXSetTevKColorSel((GXTevStageID)i, 0xD);
                    GXSetTevOrder((GXTevStageID)i, GX_TEX_COORD_ID_INVALID, GX_TEX_MAP_ID_INVALID, 0xFF);
                    if (stages0 == 0)
                    {
                        GXSetTevColorIn((GXTevStageID)i, 0xF, 0x2, 0xE, 0x2);
                        GXSetTevColorOp((GXTevStageID)i, BYTE_0x44 != 0, 0, WORD_0x40, 1, 0);
                    }
                    else
                    {
                        GXSetTevColorIn((GXTevStageID)i, 0xF, 0x2, 0xE, 0xF);
                        GXSetTevColorOp((GXTevStageID)i, 0, 0, 0, 1, 0);
                    }
                    break;
                case 2:
                    GXSetTevOrder((GXTevStageID)i, GX_TEX_COORD_ID_INVALID, GX_TEX_MAP_ID_INVALID, 0xFF);
                    GXSetTevColorIn((GXTevStageID)i, 0x0, 0xF, 0x2, 0x2);
                    GXSetTevColorOp((GXTevStageID)i, BYTE_0x44 != 0, 0, WORD_0x40, 1, 0);
                    break;
                default:
                    break;
            }

            GXSetTevAlphaIn((GXTevStageID)i, 0x7, 0x7, 0x7, 0x6);
            GXSetTevAlphaOp((GXTevStageID)i, 0, 0, 0, 1, 0);
        }

        setMatPE();
    }
}