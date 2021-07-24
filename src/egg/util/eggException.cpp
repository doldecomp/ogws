#include "eggException.h"

namespace EGG
{
    Exception * Exception::create(u16, u16, u16, Heap *)
    {
        return NULL;
    }

    UNKTYPE Exception::setUserCallBack(UserCallback)
    {

    }
}