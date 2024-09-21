#include "eggDrawPathLightMap.h"
#include "eggGXUtility.h"
#include "eggScreen.h"
#include "eggTextureBuffer.h"
#include "eggPostEffectBase.h"
#include "eggDrawGX.h"
#include "eggStateGX.h"
#include "math_types.h"
#include <revolution/GX.h>

namespace EGG
{
    DrawPathLightMap::DrawPathLightMap() :
        BYTE_0x7C(2),
        BYTE_0x7D(0xFF),
        WORD_0x80(0),
        BUF_0x84(NULL),
        BUF_0x88(NULL),
        BUF_0x8C(NULL)
    {
    }

    DrawPathLightMap::~DrawPathLightMap()
    {
    }

    void DrawPathLightMap::calc()
    {
        BUF_0x84 = NULL;
        BUF_0x88 = NULL;
        BUF_0x8C = NULL;
    }

    // https://decomp.me/scratch/53SOd
    void DrawPathLightMap::draw(u16 idx)
    {
        const Screen::DataEfb& efb = GXUtility::getScreen().GetDataEfb();
        
        switch(idx)
        {
            case 0:
                if (BYTE_0x7C & 1)
                {
                    BUF_0x8C = TextureBuffer::alloc(efb.vp.x2, efb.vp.y2, GX_TF_RGBA8);
                    BUF_0x8C->setFlag(0x8);
                    BUF_0x8C->setFlag(0x10);
                    BUF_0x8C->capture(efb.vp.x1, efb.vp.y1, false, -1);
                }
                break;
            case 1:
                if (WORD_0x80 == 2)
                {
                    BUF_0x84 = TextureBuffer::alloc(efb.vp.x2, efb.vp.y2, GX_TF_RGB565);
                }
                else
                {
                    BUF_0x84 = TextureBuffer::alloc(efb.vp.x2, efb.vp.y2, GX_TF_RGBA8);
                }

                BUF_0x84->setFlag(0x8);
                BUF_0x84->setFlag(0x10);
                if (!(BYTE_0x7C & 2)) BUF_0x84->setFlag(0x20);

                int capW = efb.vp.x1;
                int capH = efb.vp.y1;
                BUF_0x84->capture(capW, capH, false, -1);

                if (BUF_0x8C)
                {
                    nw4r::math::MTX34 forDL;
                    PostEffectBase::setProjection(GetScreen());

                    u16 screenH = GetScreen().GetHeight();
                    u16 screenW = GetScreen().GetWidth();
                    PSMTXScale(forDL, screenW, screenH, 1.0f);
                    
                    BUF_0x8C->load(GX_TEXMAP0);
                    DrawGX::BeginDrawScreen(true, true, false);
                    GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);

                    StateGX::ScopedColor color(true);
                    StateGX::ScopedAlpha alpha(true);

                    DrawGX::DrawDL(DrawGX::DL_16, forDL, DrawGX::scColorWhite);
                    BUF_0x8C->free();
                    BUF_0x8C = NULL;
                }

                if (BYTE_0x7C & 2)
                {
                    BUF_0x88 = TextureBuffer::alloc(efb.vp.x2, efb.vp.y2, GX_TF_Z24X8);
                    BUF_0x88->setFlag(0x20);
                    
                    if (isFlag0x2())
                        BUF_0x88->setFlag(0x80);
                    else
                        BUF_0x88->clearFlag(0x80);

                    BUF_0x88->capture(capW, capH, false, -1);
                }
                break;
            case 2:
            case 3:
                if (BUF_0x84 == NULL) break;
                if (idx != 2 || (BYTE_0x7C & 0x4))
                if (idx != 3 || !(BYTE_0x7C & 0x4)) break;

                if (BYTE_0x7D != 0)
                {
                    BUF_0x84->setMinFilt(0);
                    BUF_0x84->setMagFilt(0);
                    BUF_0x84->load(GX_TEXMAP0);
                    
                    nw4r::math::MTX34 forDL;
                    PostEffectBase::setProjection(GetScreen());
                    PSMTXScale(forDL, GetScreen().GetWidth(), GetScreen().GetHeight(), 1.0f);
                    
                    GXColor tevColor = {255, 255, 255, BYTE_0x7D};
                    
                    StateGX::ScopedColor color(true);
                    StateGX::ScopedAlpha alpha(false);
                    StateGX::ScopedDither dither(true);
                    
                    if (BUF_0x88 != NULL)
                    {
                        BUF_0x88->setMinFilt(0);
                        BUF_0x88->setMagFilt(0);
                        BUF_0x88->load(GX_TEXMAP1);

                        DrawGX::SetMat_ColorChannel(DrawGX::COLOR_CHANNEL_1);
                        DrawGX::SetMat_TexGen(DrawGX::TEX_GEN_1);
                        DrawGX::SetMat_Ind();

                        GXSetTevKColor(GX_KCOLOR0, (GXColor){0, 0, 0, 0});

                        GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
                        GXSetNumTevStages(2);
                        GXSetTevDirect(GX_TEVSTAGE0);
                        GXSetTevDirect(GX_TEVSTAGE1);
                        GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
                        GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);

                        if (WORD_0x80 == 0)
                        {
                            GXSetTevKAlphaSel(GX_TEVSTAGE0, GX_TEV_KASEL_K0_A);
                            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
                            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
                            GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
                            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_KONST, GX_CA_RASA, GX_CA_ZERO);
                            GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_COMP_A8_GT, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
                        }
                        else
                        {
                            GXSetTevKAlphaSel(GX_TEVSTAGE0, GX_TEV_KASEL_K0_A);
                            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
                            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
                            GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
                            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
                            GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
                        }

                        GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
                        GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD0, GX_TEXMAP1, GX_COLOR_NULL);
                        GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
                        GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
                        GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
                        GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
                        GXSetZTexture(GZ_ZT_REPLACE, GX_TF_Z24X8, 0);
                        DrawGX::SetZMode(DrawGX::ZMODE_1);
                        GXSetZCompLoc(0);
                        GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
                        DrawGX::SetBlendMode(DrawGX::BLEND_0);
                        DrawGX::SetVtxState(DrawGX::VTX_TYPE_11);
                    }
                    else
                    {
                        DrawGX::BeginDrawScreen(true, true, false);
                        GXSetTevKAlphaSel(GX_TEVSTAGE0, GX_TEV_KASEL_K0_A);
                        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_RASA, GX_CA_ZERO);
                        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_COMP_A8_GT, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
                    }

                    DrawGX::DrawDL(DrawGX::DL_16, forDL, tevColor);
                    GXSetZTexture(GX_ZT_DISABLE, GX_TF_Z24X8, 0);
                }

                if (BUF_0x88 != NULL)
                {
                    BUF_0x88->free();
                    BUF_0x88 = NULL;
                }
                
                BUF_0x84->free();
                BUF_0x84 = NULL;
                break;
        }
    }

    int DrawPathLightMap::getNumScnProc() const
    {
        return NUM_SCNPROC;
    }
}
