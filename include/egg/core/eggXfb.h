#ifndef EGG_CORE_XFB_H
#define EGG_CORE_XFB_H
#include "types_egg.h"

namespace EGG
{
    struct Xfb
    {
        Xfb(Heap *);
        void init(u16, u16, Heap *);
        static UNKWORD calcBufferSize(u16, u16);

        u16 mWidth; // at 0x0
        u16 mHeight; // at 0x2
        char *mBuffer; // at 0x4
        // Linked list framebuffer?
        Xfb *XFB_0x8;
        Xfb *XFB_0xC;
    };
}

#endif