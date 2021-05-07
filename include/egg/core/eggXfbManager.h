#ifndef EGG_CORE_XFBMANAGER_H
#define EGG_CORE_XFBMANAGER_H
#include "types_egg.h"
#include "eggXfb.h"

namespace EGG
{
    struct XfbManager
    {
        inline XfbManager() {}
        inline ~XfbManager() {}

        bool attach(Xfb *);
        void copyEFB(bool);
        void setNextFrameBuffer();
        void postVRetrace();

        Xfb mXfb;
    };
}

#endif