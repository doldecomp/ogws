#include "eggPostEffectHDR.h"
#include "eggCapTexture.h"
#include "eggDrawGX.h"
#include <revolution/GX.h>

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
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 0x3C, 0, 0x7D);
        setMatInd();
        GXSetTevKColor(GX_KCOLOR0, COLOR_0x34);
        GXSetTevKColor(GX_KCOLOR1, COLOR_0x30);
        GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
        GXSetNumTevStages(stages1);

        for (int i = 0; i < stages1; i++)
        {
            GXSetTevDirect((GXTevStageID)i);
            GXSetTevSwapMode((GXTevStageID)i, GX_TEV_SWAP0, GX_TEV_SWAP0);

            switch(i)
            {
                case 0:
                    GXSetTevKColorSel((GXTevStageID)i, GX_TEV_KCSEL_K0);
                    GXSetTevOrder((GXTevStageID)i, GX_TEXCOORD0, getCapTexture()->getLoadMap(), GX_COLOR_NULL);
                    GXSetTevColorIn((GXTevStageID)i, GX_CC_KONST, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
                    GXSetTevColorOp((GXTevStageID)i, GX_TEV_SUB, GX_TB_ZERO, (GXTevScale)WORD_0x3C, 1, GX_TEVREG0);
                    break;
                case 1:
                    GXSetTevKColorSel((GXTevStageID)i, GX_TEV_KCSEL_K1);
                    GXSetTevOrder((GXTevStageID)i, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
                    if (stages0 == 0)
                    {
                        GXSetTevColorIn((GXTevStageID)i, GX_CC_ZERO, GX_CC_C0, GX_CC_KONST, GX_CC_C0);
                        GXSetTevColorOp((GXTevStageID)i, BYTE_0x44 != 0 ? GX_TEV_SUB : GX_TEV_ADD, GX_TB_ZERO, (GXTevScale)WORD_0x40, 1, GX_TEVPREV);
                    }
                    else
                    {
                        GXSetTevColorIn((GXTevStageID)i, GX_CC_ZERO, GX_CC_C0, GX_CC_KONST, GX_CC_ZERO);
                        GXSetTevColorOp((GXTevStageID)i, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
                    }
                    break;
                case 2:
                    GXSetTevOrder((GXTevStageID)i, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
                    GXSetTevColorIn((GXTevStageID)i, GX_CC_CPREV, GX_CC_ZERO, GX_CC_C0, GX_CC_C0);
                    GXSetTevColorOp((GXTevStageID)i, BYTE_0x44 != 0 ? GX_TEV_SUB : GX_TEV_ADD, GX_TB_ZERO, (GXTevScale)WORD_0x40, 1, GX_TEVPREV);
                    break;
                default:
                    break;
            }

            GXSetTevAlphaIn((GXTevStageID)i, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
            GXSetTevAlphaOp((GXTevStageID)i, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
        }

        setMatPE();
    }
}