#include "eggMath.h"
#include "eggAssert.h"
#include "STL/math.h"

namespace EGG
{
    template <typename T>
    T Math<T>::sqrt(T t)
    {
        EGG_ASSERT(t >= 0.0f, "eggMath.cpp", 14, "t >= 0")
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

const char * UNUSED_ArcCosSinWarning()
{
    return "-1 <= t && t <= 1";
}

const char * UNUSED_GcdResult()
{
    return "gcd(%d,%d)\n";
}