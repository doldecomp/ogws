#include "eggXfbManager.h"
#include "eggXfb.h"

#include <VI/vi.h>
#include <OS/OSInterrupt.h>
#include <revolution/GX.h>

namespace EGG
{
    bool XfbManager::attach(Xfb *xfb)
    {
        bool success = false;

        if (xfb != NULL)
        {
            if (mListHead == NULL)
            {
                // Circular linked list
                mListHead = xfb;
                mListTail = xfb;
                xfb->setPrev(xfb);
                xfb->setNext(xfb);
            }
            else
            {
                // Attach as next XFB after list head
                mListHead->getNext()->setPrev(xfb);
                xfb->setNext(mListHead->getNext());
                // Link to list head
                mListHead->setNext(xfb);
                xfb->setPrev(mListHead);
                // Fix tail (redundant?)
                mListTail = mListHead->getPrev();
            }

            success = true;
        }

        return success;
    }

    void XfbManager::copyEFB(bool bUpdate)
    {
        if (bUpdate)
        {
            GXSetZMode(1, GX_ALWAYS, 1);
            GXSetAlphaUpdate(1);
            GXSetColorUpdate(1);
        }

        GXCopyDisp(mListTail->getBuffer(), bUpdate);
        GXFlush();

        mCopiedXfb = mListTail;
        mListTail = mListTail->getPrev();
    }

    void XfbManager::setNextFrameBuffer()
    {
        UNKWORD intr = OSDisableInterrupts();

        if (mCopiedXfb != NULL)
        {
            VISetNextFrameBuffer(mCopiedXfb->getBuffer());
            VIFlush();

            mShowXfb = mCopiedXfb;
            mCopiedXfb = NULL;
        }

        OSRestoreInterrupts(intr);
    }

    void XfbManager::postVRetrace()
    {
        if (mShowXfb != NULL)
        {
            if (mShowXfb->getBuffer() == VIGetCurrentFrameBuffer())
            {
                mListHead = mShowXfb;
                mShowXfb = NULL;
            }
        }
    }
}