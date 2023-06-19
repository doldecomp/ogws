#include "eggMath.h"
#include "eggAssert.h"
#include <math.h>

namespace EGG
{
    template <typename T>
    T Math<T>::sqrt(T t)
    {
        #line 14
        EGG_ASSERT(t >= 0);
        return ::sqrt(t);
    }

    template <typename T>
    T Math<T>::sin(T t)
    {
        return ::sin(t);
    }

    template <typename T>
    T Math<T>::cos(T t)
    {
        return ::cos(t);
    }

    template <typename T>
    T Math<T>::atan2(T t1, T t2)
    {
        return ::atan2(t1, t2);
    }

    template struct Math<f32>;
}

const char * eggMath_asserts[] = {"-1 <= t && t <= 1", "gcd(%d,%d)\n"};