#include "eggXfbManager.h"
#include "eggXfb.h"
#include <RevoSDK/VI/vi.h>
#include <RevoSDK/OS/OSInterrupt.h>
#include <RevoSDK/GX/GXPixel.h>
#include <RevoSDK/GX/GXFrameBuf.h>
#include <RevoSDK/GX/GXMisc.h>

namespace EGG
{
    bool XfbManager::attach(Xfb *pXfb)
    {
        bool success = false;

        if (pXfb)
        {
            if (mXfb.XFB_0x0 == NULL)
            {
                mXfb.XFB_0x0 = pXfb;
                mXfb.XFB_0x4 = pXfb;
                pXfb->XFB_0x8 = pXfb;
                pXfb->XFB_0xC = pXfb;
            }
            else
            {
                mXfb.XFB_0x0->XFB_0xC->XFB_0x8 = pXfb;

                pXfb->XFB_0xC = mXfb.XFB_0x0->XFB_0xC;
                mXfb.XFB_0x0->XFB_0xC = pXfb;

                pXfb->XFB_0x8 = mXfb.XFB_0x0;
                mXfb.XFB_0x4 = mXfb.XFB_0x0->XFB_0x8;
            }
            success = true;
        }

        return success;
    }

    void XfbManager::copyEFB(bool bUpdate)
    {
        if (bUpdate)
        {
            GXSetZMode(1, 7, 1);
            GXSetAlphaUpdate(1);
            GXSetColorUpdate(1);
        }

        GXCopyDisp(mXfb.XFB_0x4->XFB_0x4, bUpdate);
        GXFlush();
        mXfb.XFB_0x8 = mXfb.XFB_0x4;
        mXfb.XFB_0x4 = mXfb.XFB_0x4->XFB_0x8;
    }

    void XfbManager::setNextFrameBuffer()
    {
        UNKWORD r31 = OSDisableInterrupts();

        if (mXfb.XFB_0x8)
        {
            VISetNextFrameBuffer(mXfb.XFB_0x8->XFB_0x4);
            VIFlush();
            mXfb.XFB_0xC = mXfb.XFB_0x8;
            mXfb.XFB_0x8 = NULL;
        }

        OSRestoreInterrupts(r31);
    }

    void XfbManager::postVRetrace()
    {
        if (mXfb.XFB_0xC != NULL)
        {
            Xfb* pXfb = mXfb.XFB_0xC->XFB_0x4;
            if (pXfb == VIGetCurrentFrameBuffer())
            {
                mXfb.XFB_0x0 = mXfb.XFB_0xC;
                mXfb.XFB_0xC = NULL;
            }
        }
    }
}