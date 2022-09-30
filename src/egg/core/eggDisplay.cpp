#pragma ipa file
#include "eggDisplay.h"
#include "eggVideo.h"
#include "eggSystem.h"
#include "eggAssert.h"
#include "eggXfbManager.h"

#include <GX/GXMisc.h>
#include <GX/GXFrameBuf.h>
#include <OS/OS.h>
#include <OS/OSTime.h>
#include <VI/vi.h>

namespace EGG
{
    Display::Display(u8 wait) :
        BYTE_0x9(0),
        mRetraceWait(wait),
        mRetraceCount(0),
        mFrameCount(0),
        mClearColor(0x808080ff),
        mClearZ(0x00ffffff),
        mBeginTick(0)
    {
        FLAG_0x0.setBit(0);
    }

    u32 Display::getTickPerFrame()
    {
        return Video::getTickPerVRetrace();
    }

    void Display::beginFrame()
    {
        const u8 wait = mRetraceWait;
        u32 retraceDiff = VIGetRetraceCount() - mRetraceCount;
        const u32 maxDiff = wait - 1;
    
        while (true)
        {
            if (retraceDiff >= maxDiff)
            {
                if (isBlack())
                {
                    BaseSystem::getVideo()->changeBlack();
                    setBlack(false);
                }
    
                BaseSystem::getXfbManager()->setNextFrameBuffer();
            }
    
            VIWaitForRetrace();
            if (++retraceDiff >= wait) break;
        }
    
        calcFrequency();
        mRetraceCount = VIGetRetraceCount();
        mFrameCount++;
    }

    void Display::beginRender()
    {

    }

    void Display::endRender()
    {
        copyEFBtoXFB();
    }

    void Display::endFrame()
    {
        GXDrawDone();
    }

    void Display::copyEFBtoXFB()
    {
        if (FLAG_0x0.onBit(0))
        {
            GXSetCopyClear(mClearColor, mClearZ);
        }

        GXRenderModeObj *pObj = BaseSystem::getVideo()->mRenderMode;
        #line 150
        EGG_ASSERT(pObj != NULL);

        bool b = (pObj->BYTE_0x19 == 0);
        GXSetCopyFilter(pObj->BYTE_0x19, &pObj->BYTES_0x1A, b, &pObj->BYTES_0x32);
        
        bool efbFlag = FLAG_0x0.onBit(0);
        BaseSystem::getXfbManager()->copyEFB(efbFlag);
    }

	void Display::calcFrequency()
    {
        const s32 endTick = OSGetTick();
        mDeltaTick = endTick - mBeginTick;
        mFrequency = 1000000.0f / ((mDeltaTick * 8) / ((BUS_SPEED >> 2) / 125000));
        mBeginTick = endTick;
    }
}