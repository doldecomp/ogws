// TODO: REMOVE AFTER REFACTOR
#pragma ipa file

#include <egg/core.h>
#include <egg/math.h>
#include <egg/prim.h>

#include <nw4r/ut.h>

#include <revolution/GX.h>
#include <revolution/MTX.h>
#include <revolution/OS.h>
#include <revolution/VI.h>

namespace {

static GXTexObj clear_z_tobj;

static u32 clear_z_TX[4 * 4] ALIGN(32) = {
    // clang-format off
    0x00FF00FF, 0x00FF00FF, 0x00FF00FF, 0x00FF00FF,
    0x00FF00FF, 0x00FF00FF, 0x00FF00FF, 0x00FF00FF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
    // clang-format on
};

} // namespace

#ifdef __cplusplus
extern "C" {
#endif

static EGG::AsyncDisplay* spSelector = NULL;

void PostRetraceCallback(u32 retraceCount) {
#pragma unused(retraceCount)

    spSelector->postVRetrace();
}

void DrawDoneCallback() {
    EGG::BaseSystem::getXfbManager()->setNextFrameBuffer();
}

#ifdef __cplusplus
}
#endif

namespace EGG {

AsyncDisplay::AsyncDisplay(u8 frameRate)
    : Display(frameRate),
      mSyncMode(SYNC_MODE_NONE),
      mTimeScale(1.0f),
      mPrevTickCount(0),
      mTickCount(0),
      mFrameRateNTSC(1) {

    spSelector = this;

    OSInitThreadQueue(&mSyncQueue);
    VISetPostRetraceCallback(PostRetraceCallback);
}

void AsyncDisplay::calcS() {
    s32 ticksPer = mTickPerRetrace;
    s32 ticksPerNTSC = mTickPerRetraceNTSC * mFrameRateNTSC;

    while (ticksPer < ticksPerNTSC) {
        ticksPer += ticksPerNTSC;
    }

    mTickCostTick = OSGetTick() - mPrevTickTick;

    s32 ticksRemain = ticksPer - mTickPerRetraceNTSC - mTickCostTick;
    if (ticksRemain < 0) {
        ticksRemain += mTickPerRetraceNTSC;
    }

    mTimeScale =
        static_cast<f32>(ticksRemain) / static_cast<f32>(mTickPerRetraceNTSC);

    if (mTimeScale > 1.0f) {
        mTimeScale = 1.0f;
    }
}

void AsyncDisplay::syncTick() {
    u32 waitForTick = mTickCount - mPrevTickCount;

    do {
        OSSleepThread(&mSyncQueue);
    } while (++waitForTick < mFrameRate);

    mPrevTickCount = mTickCount;
    calcFrequency();

    if (mSyncMode == SYNC_MODE_NTSC) {
        calcS();
    }

    if (BaseSystem::getXfbManager()->isReadytoCopy()) {
        copyEFBtoXFB();
        GXSetDrawDoneCallback(DrawDoneCallback);
    } else {
        clearEFB();
    }

    if (mXfbFlags.onBit(BIT_XFB_CHANGE_BLACK)) {
        BaseSystem::getVideo()->changeBlack();
        mXfbFlags.resetBit(BIT_XFB_CHANGE_BLACK);
    }

    mFrameCount++;
}

void AsyncDisplay::beginFrame() {
    syncTick();
}

void AsyncDisplay::beginRender() {
    GXDrawDone();
}

void AsyncDisplay::endRender() {}

void AsyncDisplay::postVRetrace() {
    EGG::BaseSystem::getXfbManager()->postVRetrace();
    mPrevTickTick = OSGetTick();

    if (mSyncMode == SYNC_MODE_NONE) {
        mTickCount++;
        OSWakeupThread(&mSyncQueue);
    }
}

void AsyncDisplay::clearEFB() {
    const GXRenderModeObj* pObj = BaseSystem::getVideo()->getRenderModeObj();

    clearEFB(pObj->fbWidth, pObj->efbHeight, 0, 0, pObj->fbWidth,
             pObj->efbHeight, mClearColor);
}

u32 AsyncDisplay::getTickPerFrame() {
    if (mSyncMode == SYNC_MODE_NTSC) {
        return Video::getTickPerVRetrace(VI_TVFORMAT_NTSC);
    }

    return Video::getTickPerVRetrace();
}

void AsyncDisplay::clearEFB(u16 fbWidth, u16 fbHeight, u16 x, u16 y, u16 width,
                            u16 height, nw4r::ut::Color color) {

    GXInitTexObj(&clear_z_tobj, clear_z_TX, 4, 4, GX_TF_Z24X8, GX_REPEAT,
                 GX_REPEAT, GX_FALSE);
    GXInitTexObjLOD(&clear_z_tobj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE,
                    GX_FALSE, GX_ANISO_1);

    Mtx44 projMtx;
    C_MTXOrtho(projMtx, 0.0f, fbHeight, 0.0f, fbWidth, 0.0f, 1.0f);
    GXSetProjection(projMtx, GX_ORTHOGRAPHIC);

    GXSetViewport(0.0f, 0.0f, fbWidth, fbHeight, 0.0f, 1.0f);
    GXSetScissor(0, 0, fbWidth, fbHeight);

    Matrix34f::ident.loadPosMtx(GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_U16, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U8, 0);

    GXSetNumChans(0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL,
                  GX_DF_NONE, GX_AF_NONE);
    GXSetChanCtrl(GX_COLOR1A1, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL,
                  GX_DF_NONE, GX_AF_NONE);

    GXSetNumTexGens(1);
    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
    GXLoadTexObj(&clear_z_tobj, GX_TEXMAP0);

    GXSetNumTevStages(1);
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                    GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                    GX_TRUE, GX_TEVPREV);

    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
    GXSetZTexture(GX_ZT_REPLACE, GX_TF_Z24X8, 0);
    GXSetZCompLoc(GX_FALSE);
    GXSetBlendMode(GX_BM_NONE, GX_BL_ZERO, GX_BL_ZERO, GX_LO_NOOP);
    GXSetAlphaUpdate(GX_TRUE);
    GXSetDstAlpha(GX_TRUE, color.a);
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
    GXSetCullMode(GX_CULL_BACK);

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    {
        GXPosition2u16(x, y);
        GXTexCoord2u8(0, 0);

        GXPosition2u16(x + width, y);
        GXTexCoord2u8(1, 0);

        GXPosition2u16(x + width, y + height);
        GXTexCoord2u8(1, 1);

        GXPosition2u16(x, y + height);
        GXTexCoord2u8(0, 1);
    }
    GXEnd();

    GXSetZTexture(GX_ZT_DISABLE, GX_TF_Z24X8, 0);
    GXSetZCompLoc(GX_TRUE);
    GXSetDstAlpha(GX_FALSE, color.a);
}

} // namespace EGG
