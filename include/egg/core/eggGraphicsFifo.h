#ifndef EGG_CORE_GRAPHICS_FIFO_H
#define EGG_CORE_GRAPHICS_FIFO_H
#include <egg/types_egg.h>

#include <revolution/GX.h>

namespace EGG {

// Forward declarations
class Heap;

class GraphicsFifo {
public:
    struct GpStatus {
        GXBool overhi;   // at 0x0
        GXBool underlow; // at 0x1
        GXBool readIdle; // at 0x2
        GXBool cmdIdle;  // at 0x3
        GXBool brkpt;    // at 0x4
    };

public:
    static GraphicsFifo* create(u32 size, Heap* pHeap);

    GraphicsFifo(u32 size, Heap* pHeap);
    virtual ~GraphicsFifo(); // at 0x8

    static bool isGPActive() {
        return !getGpStatus().readIdle;
    }

    static const GpStatus& getGpStatus() {
        GXGetGPStatus(&sGpStatus.overhi, &sGpStatus.underlow,
                      &sGpStatus.readIdle, &sGpStatus.cmdIdle,
                      &sGpStatus.brkpt);

        return sGpStatus;
    }

private:
    GXFifoObj* mFifoObj; // at 0x4
    void* mBufBase;      // at 0x8
    u32 mBufSize;        // at 0xC

    static GraphicsFifo* sGraphicsFifo;
    static GpStatus sGpStatus;
};

} // namespace EGG

#endif
