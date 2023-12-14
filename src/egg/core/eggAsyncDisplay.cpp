#include "eggAsyncDisplay.h"
#include "eggSystem.h"
#include "eggXfbManager.h"
#include "eggVideo.h"
#include "eggMatrix.h"

#include "ut_algorithm.h"

#include <OS/OSTime.h>
#include <VI/vi.h>
#include <revolution/GX.h>
#include <revolution/MTX.h>

namespace
{
    static GXTexObj clear_z_tobj;
    static u8 clear_z_TX[] __attribute__ ((aligned (32))) = {
        0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff,
        0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff,
        0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff,
        0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
    };
}

using namespace EGG;

void PostRetraceCallback(u32 retraceCount)
{
    AsyncDisplay *disp = spSelector;
    BaseSystem::getXfbManager()->postVRetrace();
    disp->OSTICK_0x80 = OSGetTick();

    if (disp->WORD_0x60 == 0)
    {
        disp->WORD_0x6C++;
        OSWakeupThread(&disp->mThreadQueue);
    }
}

void DrawDoneCallback()
{
    BaseSystem::getXfbManager()->setNextFrameBuffer();
}

namespace EGG
{
    using namespace nw4r;

    AsyncDisplay::AsyncDisplay(u8 wait) :
        Display(wait),
        WORD_0x60(0),
        FLOAT_0x64(1.0f),
        WORD_0x68(0),
        WORD_0x6C(0),
        BYTE_0x70(1)
    {
        spSelector = this;
        OSInitThreadQueue(&mThreadQueue);
        VISetPostRetraceCallback(PostRetraceCallback);
    }

    void AsyncDisplay::syncTick()
    {
        u32 i = WORD_0x6C - WORD_0x68;
        while (true)
        {
            OSSleepThread(&mThreadQueue);
            if (++i >= mRetraceWait) break;
        }

        WORD_0x68 = WORD_0x6C;
        calcFrequency();

        if (WORD_0x60 == 1)
        {
            s32 r0 = BYTE_0x70;
            s32 r30 = WORD_0x78;
            r0 = WORD_0x74 * r0;
            while (r30 < r0)
            {
                r30 += r0;
            }

            s32 newTick = OSGetTick();
            s32 tickDelta = newTick - OSTICK_0x80;
            OSTICK_0x7C = tickDelta;
            u32 _0x74 = WORD_0x74;
            u32 temp = r30 - _0x74;
            
            s32 diff = temp - tickDelta;
            if (diff < 0) diff += _0x74;

            f32 val = (f32)diff / (f32)_0x74;

            FLOAT_0x64 = val;
            if (val > 1.0f) FLOAT_0x64 = 1.0f;
        }

        if (BaseSystem::getXfbManager()->isReadytoCopy())
        {
            copyEFBtoXFB();
            GXSetDrawDoneCallback(DrawDoneCallback);
        }
        else
        {
            GXRenderModeObj *pObj = BaseSystem::getVideo()->mRenderMode;

            clearEFB(pObj->fbWidth, pObj->efbHeight, 0, 0,
                pObj->fbWidth, pObj->efbHeight, mClearColor);
        }

        if (isBlack())
        {
            BaseSystem::getVideo()->changeBlack();
            setBlack(false);
        }

        mFrameCount++;
    }

    void AsyncDisplay::beginFrame()
    {
        syncTick();
    }

    void AsyncDisplay::beginRender()
    {
        GXDrawDone();
    }

    void AsyncDisplay::endRender()
    {

    }

    u32 AsyncDisplay::getTickPerFrame()
    {
        if (WORD_0x60 == 1)
        {
            return Video::getTickPerVRetrace(VI_TV_FMT_NTSC);
        }

        return Video::getTickPerVRetrace();
    }

    void AsyncDisplay::clearEFB(u16 width, u16 height, u16 r6, u16 r7, u16 r8, u16 r9, ut::Color color)
    {
        GXInitTexObj(&clear_z_tobj, clear_z_TX, 4, 4, GX_TF_Z24X8, GX_REPEAT, GX_REPEAT, 0);
        GXInitTexObjLOD(&clear_z_tobj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, 0, 0, GX_ANISO_1);

        Mtx44 mtx44;
        C_MTXOrtho(mtx44, 0.0f, (f32)height, 0.0f, (f32)width, 0.0f, 1.0f);
        GXSetProjection(mtx44, GX_ORTHOGRAPHIC);
        GXSetViewport(0.0f, 0.0f, (f32)width, (f32)height, 0.0f, 1.0f);
        GXSetScissor(0, 0, width, height);
        Matrix34f::ident.loadPosMtx(0);
        GXSetCurrentMtx(0);

        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_U16, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U8, 0);
        GXSetNumChans(0);
        GXSetChanCtrl(GX_COLOR0A0, 0, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
        GXSetChanCtrl(GX_COLOR1A1, 0, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);

        GXSetNumTexGens(1);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 60, 0, 125);
        GXLoadTexObj(&clear_z_tobj, GX_TEXMAP0);

        GXSetNumTevStages(1);
        GXSetTevColor(GX_TEVREG0, color);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
        GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
        GXSetZTexture(GZ_ZT_REPLACE, GX_TF_Z24X8, 0);
        GXSetZCompLoc(0);
        GXSetBlendMode(GX_BM_NONE, GX_BL_ZERO, GX_BL_ZERO, GX_LO_NOOP);
        GXSetAlphaUpdate(1);
        GXSetDstAlpha(1, color.a);
        GXSetZMode(1, GX_ALWAYS, 1);
        GXSetCullMode(GX_CULL_BACK);
        
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXCmd1u16(r6);
        GXCmd1u16(r7);
        GXCmd1u8(0);
        GXCmd1u8(0);
        u16 temp = r6 + r8;
        GXCmd1u16(temp);
        GXCmd1u16(r7);
        GXCmd1u8(1);
        GXCmd1u8(0);
        GXCmd1u16(temp);
        u16 temp2 = r7 + r9;
        GXCmd1u16(temp2);
        GXCmd1u8(1);
        GXCmd1u8(1);
        GXCmd1u16(r6);
        GXCmd1u16(temp2);
        GXCmd1u8(0);
        GXCmd1u8(1);
        GXEnd();

        GXSetZTexture(GX_ZT_DISABLE, GX_TF_Z24X8, 0);
        GXSetZCompLoc(1);
        GXSetDstAlpha(0, color.a);
    }
}