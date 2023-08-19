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
    #ifdef __DECOMP_NON_MATCHING
    void DrawPathLightMap::draw(u16 idx)
    {
        const Screen::DataEfb* efb = GXUtility::getScreen().GetDataEfb();
        
        switch(idx)
        {
            case 0:
                if (BYTE_0x7C & 1)
                {
                    BUF_0x8C = TextureBuffer::alloc(efb->FLOAT_0x8, efb->FLOAT_0xC, GX_TEX_FMT_6);
                    BUF_0x8C->setFlag(0x8);
                    BUF_0x8C->setFlag(0x10);
                    BUF_0x8C->capture(efb->FLOAT_0x0, efb->FLOAT_0x4, false, -1);
                }
                break;
            case 1:
                if (WORD_0x80 == 2)
                {
                    BUF_0x84 = TextureBuffer::alloc(efb->FLOAT_0x8, efb->FLOAT_0xC, GX_TEX_FMT_4);
                }
                else
                {
                    BUF_0x84 = TextureBuffer::alloc(efb->FLOAT_0x8, efb->FLOAT_0xC, GX_TEX_FMT_6);
                }

                BUF_0x84->setFlag(0x8);
                BUF_0x84->setFlag(0x10);
                if (!(BYTE_0x7C & 2)) BUF_0x84->setFlag(0x20);

                int capW = efb->FLOAT_0x0;
                int capH = efb->FLOAT_0x4;
                BUF_0x84->capture(capW, capH, false, -1);

                if (BUF_0x8C)
                {
                    math::MTX34 forDL;
                    PostEffectBase::setProjection(GetScreen());

                    u16 screenH = GetScreen().GetHeight();
                    u16 screenW = GetScreen().GetWidth();
                    PSMTXScale(forDL, screenW, screenH, 1.0f);
                    
                    BUF_0x8C->load(GX_TEXMAP0);
                    DrawGX::BeginDrawScreen(true, true, false);
                    GXSetBlendMode(0, 4, 5, 0);

                    StateGX::ScopedColor color(true);
                    StateGX::ScopedAlpha alpha(true);

                    DrawGX::DrawDL(DrawGX::DL_16, forDL, DrawGX::scColorWhite);
                    BUF_0x8C->free();
                    BUF_0x8C = NULL;
                }

                if (BYTE_0x7C & 2)
                {
                    BUF_0x88 = TextureBuffer::alloc(efb->FLOAT_0x8, efb->FLOAT_0xC, GX_TEX_FMT_22);
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
                    
                    math::MTX34 forDL;
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

                        GXSetTevSwapModeTable(GX_TEV_SWAP0, 0, 1, 2, 3);
                        GXSetNumTevStages(2);
                        GXSetTevDirect(0);
                        GXSetTevDirect(1);
                        GXSetTevSwapMode(GX_TEVSTAGE0, 0, 0);
                        GXSetTevSwapMode(GX_TEV_STAGE_ID_1, 0, 0);

                        if (WORD_0x80 == 0)
                        {
                            GXSetTevKAlphaSel(GX_TEVSTAGE0, 28);
                            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, 4);
                            GXSetTevColorIn(GX_TEVSTAGE0, 15, 8, 10, 15);
                            GXSetTevColorOp(GX_TEVSTAGE0, 0, 0, 0, 1, 0);
                            GXSetTevAlphaIn(GX_TEVSTAGE0, 4, 6, 5, 7);
                            GXSetTevAlphaOp(GX_TEVSTAGE0, 14, 0, 0, 1, 0);
                        }
                        else
                        {
                            GXSetTevKAlphaSel(GX_TEVSTAGE0, 28);
                            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, 4);
                            GXSetTevColorIn(GX_TEVSTAGE0, 15, 15, 15, 8);
                            GXSetTevColorOp(GX_TEVSTAGE0, 0, 0, 0, 1, 0);
                            GXSetTevAlphaIn(GX_TEVSTAGE0, 7, 7, 7, 5);
                            GXSetTevAlphaOp(GX_TEVSTAGE0, 0, 0, 0, 1, 0);
                        }

                        GXSetTevSwapMode(GX_TEV_STAGE_ID_1, 0, 0);
                        GXSetTevOrder(GX_TEV_STAGE_ID_1, GX_TEXCOORD0, GX_TEXMAP1, 0xFF);
                        GXSetTevColorIn(GX_TEV_STAGE_ID_1, 15, 15,15, 0);
                        GXSetTevColorOp(GX_TEV_STAGE_ID_1, 0, 0, 0, 1, 0);
                        GXSetTevAlphaIn(GX_TEV_STAGE_ID_1, 7, 7, 7, 0);
                        GXSetTevAlphaOp(GX_TEV_STAGE_ID_1, 0, 0, 0, 1, 0);
                        GXSetZTexture(2, 22, 0);
                        DrawGX::SetZMode(DrawGX::ZMODE_1);
                        GXSetZCompLoc(0);
                        GXSetAlphaCompare(7, 0, 1, 7, 0);
                        DrawGX::SetBlendMode(DrawGX::BLEND_0);
                        DrawGX::SetVtxState(DrawGX::VTX_TYPE_11);
                    }
                    else
                    {
                        DrawGX::BeginDrawScreen(true, true, false);
                        GXSetTevKAlphaSel(GX_TEVSTAGE0, 0x1C);
                        GXSetTevAlphaIn(GX_TEVSTAGE0, 4, 7, 5, 7);
                        GXSetTevAlphaOp(GX_TEVSTAGE0, 14, 0, 0, 1, 0);
                    }

                    DrawGX::DrawDL(DrawGX::DL_16, forDL, tevColor);
                    GXSetZTexture(0, 22, 0);
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
    #else
    #error "This file has yet to be decompiled accurately. Use "eggDrawPathLightMap.s" instead."
    #endif

    int DrawPathLightMap::getNumScnProc() const
    {
        return NUM_SCNPROC;
    }
}