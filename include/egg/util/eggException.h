#ifndef EGG_UTIL_EXCEPTION_H
#define EGG_UTIL_EXCEPTION_H
#include "types_egg.h"
#include <revolution/KPAD/KPAD.h>

namespace EGG
{
    struct Exception
    {
        typedef void (*UserCallback)(KPADStatus *);

        static Exception * create(u16, u16, u16, Heap *);
        static UNKTYPE setUserCallBack(UserCallback);
    };
}

#endif