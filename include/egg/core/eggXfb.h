#ifndef EGG_CORE_XFB_H
#define EGG_CORE_XFB_H
#include <egg/types_egg.h>

namespace EGG {

// Forward declarations
class XfbManager;

class Xfb {
    friend class XfbManager;

public:
    Xfb(Heap* pHeap = NULL);

    u16 getWidth() {
        return mWidth;
    }
    u16 getHeight() {
        return mHeight;
    }

    u8* getBuffer() {
        return mBuffer;
    }

private:
    void init(u16 width, u16 height, Heap* pHeap);

    static u32 calcBufferSize(u16 width, u16 height);

private:
    u16 mWidth;  // at 0x0
    u16 mHeight; // at 0x2
    u8* mBuffer; // at 0x4

    Xfb* mPrev; // at 0x8
    Xfb* mNext; // at 0xC
};

} // namespace EGG

#endif
