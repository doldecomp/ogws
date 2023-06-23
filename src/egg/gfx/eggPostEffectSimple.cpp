#include "eggPostEffectSimple.h"
#include "eggDrawGX.h"
#include "eggCapTexture.h"

#include <revolution/GX.h>

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
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4,
            GX_TG_TEX0, 0x3C, 0, 0x7D);
        setMatInd();

        GXSetNumTevStages(1);
        GXSetTevDirect(GX_TEVSTAGE0);
        GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
        GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
        GXSetTevKColorSel(GX_TEVSTAGE0, GX_TEV_KCSEL_K0);
        GXSetTevKAlphaSel(GX_TEVSTAGE0, GX_TEV_KASEL_K0_A);
        GXSetTevKColor(GX_KCOLOR0, color);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0,
            mpCapTexture->getLoadMap(), GX_COLOR_NULL);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_KONST, GX_CC_ZERO);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);

        switch(WORD_0x2C)
        {
            case 0:
                GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
                break;
            case 1:
                GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_KONST, GX_CA_ZERO);
                break;
            case 2:
                GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXA, GX_CC_KONST, GX_CC_ZERO);
                GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_KONST, GX_CA_KONST, GX_CA_ZERO);
                break;
        }

        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
        setMatPE();
    }
}