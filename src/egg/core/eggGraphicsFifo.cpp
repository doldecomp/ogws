#pragma ipa file
#include "eggGraphicsFifo.h"
#include "eggHeap.h"
#include "eggAssert.h"
#include <revolution/OS.h>
#include <revolution/GX.h>

namespace EGG
{
    GraphicsFifo * GraphicsFifo::create(u32 size, Heap *heap)
    {
        #line 59
        EGG_ASSERT(!sGraphicsFifo);

        if (!heap) heap = Heap::getCurrentHeap();

        #line 69
        EGG_ASSERT(OSIsMEM1Region( heap ));

        sGraphicsFifo = new (heap, 4) GraphicsFifo(size, heap);
        return sGraphicsFifo;
    }
    
    GraphicsFifo::~GraphicsFifo()
    {
        do
        {
            GXGetGPStatus(&sGpStatus.b0, &sGpStatus.b1, &sGpStatus.b2, &sGpStatus.b3, &sGpStatus.b4);
        } while (sGpStatus.b2 == 0);

        Heap::free(mBufBase, NULL);
    }

    GraphicsFifo::GraphicsFifo(u32 size, Heap *heap)
    {
        mBufSize = nw4r::ut::RoundUp(size, 32);
        void *buf = Heap::alloc(mBufSize + 0xA0, 32, heap);
        mBufBase = nw4r::ut::RoundUp(buf, 32);
        #line 145
        EGG_ASSERT(mBufBase);

        PTR_0x4 = GXInit(mBufBase, mBufSize);
    }

    GraphicsFifo *GraphicsFifo::sGraphicsFifo;
    GraphicsFifo::GpStatus GraphicsFifo::sGpStatus;
}