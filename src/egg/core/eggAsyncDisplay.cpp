#include "eggAsyncDisplay.h"
#include "eggSystem.h"
#include "eggXfbManager.h"
#include "eggVideo.h"
#include "eggMatrix.h"
#include "ut_algorithm.h"
#include <RevoSDK/OS/OSTime.h>
#include <RevoSDK/VI/vi.h>
#include <RevoSDK/GX/GXMisc.h>
#include <RevoSDK/GX/GXTransform.h>
#include <RevoSDK/GX/GXAttr.h>
#include <RevoSDK/GX/GXTev.h>
#include <RevoSDK/GX/GXLight.h>
#include <RevoSDK/GX/GXGeometry.h>
#include <RevoSDK/GX/GXBump.h>
#include <RevoSDK/GX/GXPixel.h>
#include <RevoSDK/GX/GXVert.h>
#include <RevoSDK/math/mtx44.h>

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

void PostRetraceCallback()
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

    AsyncDisplay::AsyncDisplay(u8 uc) : Display(uc), WORD_0x60(0), FLOAT_0x64(1.0f),
        WORD_0x68(0), WORD_0x6C(0), BYTE_0x70(1)
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
            if (++i >= BYTE_0x8) break;
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

        XfbManager *xfbmgr = BaseSystem::getXfbManager();
        Xfb *xfb_04 = xfbmgr->XFB_0x4;
        bool b = false;
        
        if ((xfb_04 != xfbmgr->XFB_0xC)
            && (xfb_04 != xfbmgr->XFB_0x0))
        {
            b = true;
        }

        if (b)
        {
            copyEFBtoXFB();
            GXSetDrawDoneCallback(DrawDoneCallback);
        }
        else
        {
            GXRenderModeObj *pObj = BaseSystem::getVideo()->mRenderMode;

            clearEFB(pObj->mFbWidth, pObj->mEfbHeight, 0, 0,
                pObj->mFbWidth, pObj->mEfbHeight, mColor);
        }

        if (BYTE_0x9 & 1)
        {
            Video *pVideo = BaseSystem::getVideo();
            bool setBlack = (!pVideo->mFlags.onBit(0));
            VISetBlack(setBlack);

            pVideo->mFlags.toggleBit(0);
            BYTE_0x9 &= (u8)~1;
        }

        WORD_0x10++;
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
            return Video::getTickPerVRetrace(VI_NTSC);
        }

        return Video::getTickPerVRetrace();
    }

    void AsyncDisplay::clearEFB(u16 width, u16 height, u16 r6, u16 r7, u16 r8, u16 r9, ut::Color color)
    {
        GXInitTexObj(&clear_z_tobj, clear_z_TX, 4, 4, 22, 1, 1, 0);
        GXInitTexObjLOD(&clear_z_tobj, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f);

        Mtx44 mtx44;
        C_MTXOrtho(mtx44, 0.0f, (f32)height, 0.0f, (f32)width, 0.0f, 1.0f);
        GXSetProjection(mtx44, 1);
        GXSetViewport(0.0f, 0.0f, (f32)width, (f32)height, 0.0f, 1.0f);
        GXSetScissor(0, 0, width, height);
        Matrix34f::ident.loadPosMtx(0);
        GXSetCurrentMtx(0);

        GXClearVtxDesc();
        GXSetVtxDesc(GX_ATTR_VTX, 1);
        GXSetVtxDesc(GX_ATTR_VTX_TEX_COORD, 1);
        GXSetVtxAttrFmt(0, GX_ATTR_VTX, 0, 2, 0);
        GXSetVtxAttrFmt(0, GX_ATTR_VTX_TEX_COORD, 1, 0, 0);
        GXSetNumChans(0);
        GXSetChanCtrl(GX_CHANNEL_ID_4, 0, 0, 0, 0, 0, 2);
        GXSetChanCtrl(GX_CHANNEL_ID_5, 0, 0, 0, 0, 0, 2);

        GXSetNumTexGens(1);
        GXSetTexCoordGen2(GX_TEX_COORD_ID_0, GX_TEX_GEN_TYPE_1, GX_TEX_GEN_SRC_4, 60, 0, 125);
        GXLoadTexObj(&clear_z_tobj, GX_TEX_MAP_ID_0);

        GXSetNumTevStages(1);
        GXSetTevColor(GX_TEV_REG_ID_1, color.mChannels);
        GXSetTevOrder(GX_TEV_STAGE_ID_0, GX_TEX_COORD_ID_0, GX_TEX_MAP_ID_0, 0xff);
        GXSetTevColorIn(GX_TEV_STAGE_ID_0, 15, 15, 15, 2);
        GXSetTevColorOp(GX_TEV_STAGE_ID_0, 0, 0, 0, 1, 0);
        GXSetTevAlphaIn(GX_TEV_STAGE_ID_0, 7, 7, 7, 1);
        GXSetTevAlphaOp(GX_TEV_STAGE_ID_0, 0, 0, 0, 1, 0);
        GXSetAlphaCompare(7, 0, 1, 7, 0);
        GXSetZTexture(2, 22, 0);
        GXSetZCompLoc(0);
        GXSetBlendMode(0, 0, 0, 5);
        GXSetAlphaUpdate(1);
        GXSetDstAlpha(1, color.mChannels.a);
        GXSetZMode(1, 7, 1);
        GXSetCullMode(2);
        
        GXBegin(0x80, 0, 4);
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

        GXSetZTexture(0, 22, 0);
        GXSetZCompLoc(1);
        GXSetDstAlpha(0, color.mChannels.a);
    }
}