#pragma ipa file
#include "eggDisplay.h"
#include "eggVideo.h"
#include "eggSystem.h"
#include "eggAssert.h"
#include "eggXfbManager.h"
#include <RevoSDK/GX/GXMisc.h>
#include <RevoSDK/GX/GXFrameBuf.h>
#include <RevoSDK/OS/OS.h>
#include <RevoSDK/OS/OSTime.h>
#include <RevoSDK/VI/vi.h>

namespace EGG
{
    Display::Display(u8 uc) : BYTE_0x9(0), BYTE_0x8(uc), WORD_0xC(0),
        WORD_0x10(0), mColor(0x808080ff), WORD_0x18(0x00ffffff), mBeginTick(0)
    {
        FLAG_0x0.setBit(0);
    }

    u32 Display::getTickPerFrame()
    {
        return Video::getTickPerVRetrace();
    }

    void Display::beginFrame()
    {
        u8 r31 = BYTE_0x8;
        u32 r30 = VIGetRetraceCount() - WORD_0xC;
        u32 r29 = r31 - 1;

        do
        {
            if (r30 >= r29)
            {
                if (BYTE_0x9 & 1)
                {
                    Video *pVideo = BaseSystem::getVideo();
                    VISetBlack(!pVideo->mFlags.onBit(0));

                    pVideo->mFlags.toggleBit(0);

                    BYTE_0x9 &= (u8)~1;
                }

                BaseSystem::getXfbManager()->setNextFrameBuffer();
            }

            VIWaitForRetrace();
            r30++;
        } while (r30 < r31);

        calcFrequency();
        WORD_0xC = VIGetRetraceCount();
        WORD_0x10++;
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
            GXSetCopyClear(mColor, WORD_0x18);
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
        s32 endTick = OSGetTick();
        mDeltaTick = endTick - mBeginTick;
        mFrequency = 1000000.0f / ((mDeltaTick * 8) / ((BUS_SPEED >> 2) / 125000));
        mBeginTick = endTick;
    }
}