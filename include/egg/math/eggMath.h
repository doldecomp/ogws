#ifndef EGG_MATH_MATH_H
#define EGG_MATH_MATH_H
#include "types_egg.h"

namespace EGG
{
    template <typename T> struct Math
    {
        static T sqrt(T);
        static T sin(T);
        static T cos(T);
        static T atan2(T, T);
    };
}

#endif