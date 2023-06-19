#ifndef EGG_CORE_XFB_H
#define EGG_CORE_XFB_H
#include "types_egg.h"

namespace EGG
{
    class Xfb
    {
    public:
        static u32 calcBufferSize(u16, u16);

        Xfb(Heap *);
        void init(u16, u16, Heap *);

        u16 getWidth() const { return mWidth; }
        u16 getHeight() const { return mHeight; }

        u8* getBuffer() const { return mBuffer; }

        Xfb* getPrev() const { return mPrev; }
        void setPrev(Xfb* xfb) { mPrev = xfb; }

        Xfb* getNext() const { return mNext; }
        void setNext(Xfb* xfb) { mNext = xfb; }

    private:
        u16 mWidth; // at 0x0
        u16 mHeight; // at 0x2
        u8 *mBuffer; // at 0x4

        Xfb *mPrev; // at 0x8
        Xfb *mNext; // at 0xC
    };
}

#endif