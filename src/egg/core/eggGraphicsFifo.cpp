#include "eggGraphicsFifo.h"
#include "eggHeap.h"
#include "eggAssert.h"
#include <RevoSDK/OS/OS.h>
#include <RevoSDK/GX/GXFifo.h>
#include <RevoSDK/GX/GXInit.h>

namespace EGG
{
    GraphicsFifo * GraphicsFifo::create(u32 size, Heap *heap)
    {
        #line 59
        EGG_ASSERT(!sGraphicsFifo);

        if (!heap) heap = Heap::sCurrentHeap;

        #line 69
        EGG_ASSERT(OSIsMEM1Region( heap ));

        GraphicsFifo *pFifo = new (heap, 4) GraphicsFifo(size, heap);
        sGraphicsFifo = pFifo;
        return pFifo;
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
        u32 alignedSize = nw4r::ut::RoundUp<u32>(size, 32);
        mBufSize = alignedSize;

        void *buf = Heap::alloc(mBufSize + 0xA0, 32, heap);
        buf = nw4r::ut::RoundUp<void *>(buf, 32);
        mBufBase = buf;
        #line 145
        EGG_ASSERT(mBufBase);

        PTR_0x4 = GXInit(mBufBase, mBufSize);
    }

    GraphicsFifo *GraphicsFifo::sGraphicsFifo;
    GraphicsFifo::GpStatus GraphicsFifo::sGpStatus;
}