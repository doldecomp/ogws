// TODO(kiwi) REMOVE AFTER REFACTOR
#pragma ipa file

#include <egg/core.h>
#include <egg/prim.h>

#include <nw4r/ut.h>

#include <revolution/GX.h>
#include <revolution/OS.h>

/******************************************************************************
 *
 * Utility functions
 *
 ******************************************************************************/
namespace {

void drawBox(f32 x, f32 y, f32 w, f32 h) {
    if (w > 0.0f && h > 0.0f) {
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        {
            GXPosition2f32(x, y);
            GXPosition2f32(x + w, y);
            GXPosition2f32(x + w, y + h);
            GXPosition2f32(x, y + h);
        }
        GXEnd();
    }
}

void drawLine(f32 x1, f32 y1, f32 x2, f32 y2) {
    GXBegin(GX_LINES, GX_VTXFMT0, 2);
    {
        GXPosition2f32(x1, y1);
        GXPosition2f32(x2, y2);
    }
    GXEnd();
}

void drawColor(nw4r::ut::Color color) {
    GXSetChanMatColor(GX_COLOR0A0, color);
}

} // namespace

namespace EGG {

/******************************************************************************
 *
 * ProcessBar
 *
 ******************************************************************************/
ProcessMeter::ProcessBar::ProcessBar(nw4r::ut::Color color, f32 posY,
                                     f32 height)
    : mColor(color), mPosX(0.0f), mWidth(0.0f), mPosY(posY), mHeight(height) {}

bool ProcessMeter::ProcessBar::update(s32 measureTick) {
    return update(static_cast<f32>(measureTick) /
                  static_cast<u32>(OS_MSEC_TO_TICKS(1)));
}

bool ProcessMeter::ProcessBar::update(f32 measureTime) {
    mPosX = measureTime;
    if (mPosX < 0.0f) {
        mPosX = 0.0f;
    }

    mWidth = static_cast<f32>(mStopWatch.getMeasureTick()) /
             static_cast<u32>(OS_MSEC_TO_TICKS(1));

    return mWidth > 0.0f;
}

void ProcessMeter::ProcessBar::draw() {
    draw(mPosY, mHeight);
}

void ProcessMeter::ProcessBar::draw(f32 posY, f32 height) {
    drawColor(mColor);
    drawBox(mPosX, posY, mWidth, height);
}

/******************************************************************************
 *
 * CpuMonitor
 *
 ******************************************************************************/
ProcessMeter::CpuMonitor::CpuMonitor(nw4r::ut::Color color, f32 posY)
    : mCpuProcessBar(color, posY, 1.0f) {}

void ProcessMeter::CpuMonitor::measureBegin() {
    mCpuProcessBar.mStopWatch.start();
}

void ProcessMeter::CpuMonitor::measureEnd() {
    mCpuProcessBar.mStopWatch.stop();
}

void ProcessMeter::CpuMonitor::show() {
    mCpuProcessBar.show();
}

void ProcessMeter::CpuMonitor::hide() {
    mCpuProcessBar.hide();
}

/******************************************************************************
 *
 * CpuGpMonitor
 *
 ******************************************************************************/
ProcessMeter::CpuGpMonitor::CpuGpMonitor(nw4r::ut::Color cpuColor,
                                         nw4r::ut::Color gpColor, f32 cpuPosY,
                                         f32 gpPosY)
    : CpuMonitor(cpuColor, cpuPosY), mGpProcessBar(gpColor, gpPosY, 1.0f) {

    mBeginDrawSync.pGpMonitor = this;
    mDrawSyncState = DRAWSYNC_NONE;
    mEndDrawSync.pGpMonitor = this;
}

void ProcessMeter::CpuGpMonitor::doToken(u32 tick) {
    switch (mDrawSyncState) {
    case DRAWSYNC_BEGIN: {
        mGpProcessBar.mStopWatch.setStartTick(tick);
        mDrawSyncState = DRAWSYNC_END;
        break;
    }

    case DRAWSYNC_END: {
        mGpProcessBar.mStopWatch.setStopTick(tick);
        mDrawSyncState = DRAWSYNC_NONE;
        break;
    }

    case DRAWSYNC_NONE:
    default: {
        break;
    }
    }
}

void ProcessMeter::CpuGpMonitor::measureBegin() {
    CpuMonitor::measureBegin();
    mDrawSyncState = DRAWSYNC_BEGIN;
    mProcessMeter->setDrawSync(&mBeginDrawSync);
}

void ProcessMeter::CpuGpMonitor::measureEnd() {
    CpuMonitor::measureEnd();
    mProcessMeter->setDrawSync(&mEndDrawSync);
}

void ProcessMeter::CpuGpMonitor::show() {
    mCpuProcessBar.show();
    mGpProcessBar.show();
}

void ProcessMeter::CpuGpMonitor::hide() {
    mCpuProcessBar.hide();
    mGpProcessBar.hide();
}

/******************************************************************************
 *
 * ProcessMeter
 *
 ******************************************************************************/
ProcessMeter::ProcessMeter(bool showGp)
    : Thread(THREAD_STACK_SIZE, THREAD_MSG_CAPACITY, OS_PRIORITY_MIN),
      mGraduationColor(GRADUATION_COLOR),
      mPosX(5.0f),
      mPosY(5.0f),
      mWidth(90.0f),
      mHeight(1.0f),
      mBgProcessBar(BG_COLOR, 0.0f, 1.0f),
      mCpuMonitor(CPU_BAR_COLOR, 0.0f),
      mCpuGpMonitor(CPU_GP_BAR_COLOR, GP_BAR_COLOR, 1.0f, 2.0f) {

    mHeadDrawSync = NULL;
    mTailDrawSync = NULL;

    append(&mCpuMonitor);
    append(&mCpuGpMonitor);

    mFlags.setBit(BIT_VISIBLE);

    if (showGp) {
        GXSetDrawSyncCallback(callbackDrawSyncStatic);
    }

    OSThread* pGXThread = GXGetCurrentGXThread();
#line 319
    EGG_ASSERT(pGXThread->priority > 0);

    OSSetThreadPriority(getOSThread(), pGXThread->priority - 1);
    OSResumeThread(getOSThread());
}

void ProcessMeter::measureBeginFrame() {
    mBgProcessBar.mStopWatch.stop();
    u32 startTick = mBgProcessBar.mStopWatch.getStartTick();

    bool barVisible = mBgProcessBar.update(0.0f);

    // TODO(kiwi) Fakematch
    f32 dummy = barVisible ? 0.0f : 0.0f;
    dummy = barVisible ? 0.0f : 0.0f;

    f32 meterHeight = 0.0f;

    EGG_NW4R_LIST_FOREACH (ProcessBar, it, mProcessBarList) {
        it->update(OS_TICKS_DELTA(it->mStopWatch.getStartTick(), startTick));

        f32 barHeight = it->mWidth > 0.0f ? it->mPosY + it->mHeight : 0.0f;

        if (it->isVisible() && barHeight > meterHeight) {
            meterHeight = barHeight;
        }
    }

    mBgBarHeight = 1.0f + meterHeight;
    mBgProcessBar.mStopWatch.start();

    mCpuMonitor.measureBegin();
}

void ProcessMeter::measureEndFrame() {
    mCpuMonitor.measureEnd();
}

void ProcessMeter::measureBeginRender() {
    mCpuGpMonitor.measureBegin();
}

void ProcessMeter::measureEndRender() {
    mCpuGpMonitor.measureEnd();
}

void ProcessMeter::callbackDrawSync(u16 token) {
    if (mHeadDrawSync->token == token) {
        sendMessage(reinterpret_cast<OSMessage>(OSGetTick()));
    }
}

void* ProcessMeter::run() {
    while (true) {
        OSMessage msg = waitMessageBlock();
        u32 tick = reinterpret_cast<u32>(msg);

        BOOL enabled = OSDisableInterrupts();

        DrawSync* pDrawSync = mHeadDrawSync->pNext;

        if (pDrawSync != NULL) {
            if (pDrawSync->pNext != NULL) {
                GXEnableBreakPt(pDrawSync->pNext->pWritePtr);
            } else {
                GXDisableBreakPt();
            }
        }

        CpuGpMonitor* pGpMonitor = mHeadDrawSync->pGpMonitor;
        mHeadDrawSync = mHeadDrawSync->pNext;

        OSRestoreInterrupts(enabled);

        pGpMonitor->doToken(tick);
    }

    return NULL;
}

void ProcessMeter::setDrawSync(DrawSync* pDrawSync) {
    BOOL enabled = OSDisableInterrupts();

    if (++mNextToken > DRAW_TOKEN_MAX) {
        mNextToken = DRAW_TOKEN_MIN;
    }

    pDrawSync->token = mNextToken;
    pDrawSync->pNext = NULL;

    if (mHeadDrawSync != NULL) {
        GXFifoObj fifoObj;
        GXGetGPFifo(&fifoObj);

        void* pReadPtr;
        GXGetFifoPtrs(&fifoObj, &pReadPtr, &pDrawSync->pWritePtr);

        if (mHeadDrawSync->pNext == NULL) {
            GXEnableBreakPt(pDrawSync->pWritePtr);
        }

        mTailDrawSync->pNext = pDrawSync;
        mTailDrawSync = pDrawSync;
    } else {
        mHeadDrawSync = pDrawSync;
        mTailDrawSync = pDrawSync;
    }

    GXSetDrawSync(mNextToken);

    OSRestoreInterrupts(enabled);
}

void ProcessMeter::setVisible(bool visible) {
    mFlags.changeBit(BIT_VISIBLE, visible);
}

bool ProcessMeter::isVisible() {
    return mFlags.onBit(BIT_VISIBLE);
}

void ProcessMeter::append(CpuMonitor* pMonitor) {
    mProcessBarList.append(&pMonitor->mCpuProcessBar);
}

void ProcessMeter::append(CpuGpMonitor* pGpMonitor) {
    mProcessBarList.append(&pGpMonitor->mCpuProcessBar);
    mProcessBarList.append(&pGpMonitor->mGpProcessBar);
    pGpMonitor->mProcessMeter = this;
}

void ProcessMeter::draw(f32 fbWidth, f32 efbHeight, u32 tickPerFrame) {
    if (mFlags.offBit(BIT_VISIBLE)) {
        return;
    }

    drawSetting(fbWidth, efbHeight);
    mBgProcessBar.draw(-0.5f, mBgBarHeight);

    f32 step, pos, width;
    pos = 0.0f;
    width = mBgProcessBar.mWidth;
    step = static_cast<u32>(OS_TICKS_TO_USEC(tickPerFrame)) / 1000.0f;

    GXSetLineWidth(12, 0);

    for (; pos < width; pos += step) {
        drawColor(mGraduationColor);
        drawLine(pos, -0.5f, pos, mBgBarHeight);
    }

    EGG_NW4R_LIST_FOREACH (ProcessBar, it, mProcessBarList) {
        if (it->isVisible()) {
            it->draw();
        }
    }
}

void ProcessMeter::draw() {
    const GXRenderModeObj* pRenderMode =
        BaseSystem::getVideo()->getRenderModeObj();

    draw(pRenderMode->fbWidth, pRenderMode->efbHeight,
         BaseSystem::getDisplay()->getTickPerFrame());
}

void ProcessMeter::drawSetting(f32 fbWidth, f32 efbHeight) {
    GXSetViewport(0.0f, 0.0f, fbWidth, efbHeight, 0.0f, 1.0f);
    GXSetScissor(0, 0, fbWidth, efbHeight);

    Mtx44 projMtx;
    C_MTXOrtho(projMtx, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f);
    GXSetProjection(projMtx, GX_ORTHOGRAPHIC);

    Mtx posMtx;
    Mtx scale, trans;

    PSMTXTrans(trans, mPosX / 100.0f, mPosY / 100.0f, 0.0f);

    PSMTXScale(scale, mWidth / 100.0f, mHeight / 100.0f, 0.0f);
    PSMTXConcat(trans, scale, posMtx);

    PSMTXScale(scale, 1.0f / mBgProcessBar.mWidth, 1.0f, 1.0f);
    PSMTXConcat(posMtx, scale, posMtx);

    GXLoadPosMtxImm(posMtx, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);

    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL,
                  GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);

    GXSetNumIndStages(0);
    GXSetNumTexGens(0);

    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetNumTevStages(1);

    GXSetCullMode(GX_CULL_NONE);
    GXSetBlendMode(GX_BM_LOGIC, GX_BL_ONE, GX_BL_ZERO, GX_LO_COPY);

    GXSetColorUpdate(GX_TRUE);

    GXClearVtxDesc();
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_F32, 0);
}

} // namespace EGG
