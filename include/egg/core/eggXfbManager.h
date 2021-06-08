#ifndef EGG_CORE_XFBMANAGER_H
#define EGG_CORE_XFBMANAGER_H
#include "types_egg.h"
#include "eggXfb.h"

namespace EGG
{
    struct XfbManager
    {
        inline XfbManager(Heap *heap) {}
        inline ~XfbManager() {}

        bool attach(Xfb *);
        void copyEFB(bool);
        void setNextFrameBuffer();
        void postVRetrace();

        Xfb *XFB_0x0;
        Xfb *XFB_0x4;
        Xfb *XFB_0x8;
        Xfb *XFB_0xC;
    };
}

#endif