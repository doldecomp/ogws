// TODO: REMOVE AFTER REFACTOR
#pragma ipa file

#include <egg/core.h>
#include <egg/prim.h>

#include <nw4r/ut.h>

#include <revolution/GX.h>
#include <revolution/OS.h>

namespace EGG {

GraphicsFifo* GraphicsFifo::sGraphicsFifo = NULL;
GraphicsFifo::GpStatus GraphicsFifo::sGpStatus;

GraphicsFifo* GraphicsFifo::create(u32 size, Heap* heap) {
#line 59
    EGG_ASSERT(!sGraphicsFifo);

    if (heap == NULL) {
        heap = Heap::getCurrentHeap();
    }

#line 69
    EGG_ASSERT(OSIsMEM1Region( heap ));

    sGraphicsFifo = new (heap) GraphicsFifo(size, heap);
    return sGraphicsFifo;
}

GraphicsFifo::~GraphicsFifo() {
    while (isGPActive()) {
        ;
    }

    Heap::free(mBufBase, NULL);
}

GraphicsFifo::GraphicsFifo(u32 size, Heap* pHeap) {
    mBufSize = ROUND_UP(size, 32);

    mBufBase = Heap::alloc(mBufSize + sizeof(GXFifoObj) + 32, 32, pHeap);
    mBufBase = ROUND_UP_PTR(mBufBase, 32);
#line 145
    EGG_ASSERT(mBufBase);

    mFifoObj = GXInit(mBufBase, mBufSize);
}

} // namespace EGG
