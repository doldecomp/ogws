// TODO: REMOVE AFTER REFACTOR
#pragma ipa file

#include <egg/math.h>
#include <egg/prim.h>

#include <cmath>

namespace EGG {

template <typename T> T Math<T>::sqrt(T t) {
#line 14
    EGG_ASSERT(t >= 0);
    return std::sqrt(t);
}

template <typename T> T Math<T>::sin(T t) {
    return std::sin(t);
}

template <typename T> T Math<T>::cos(T t) {
    return std::cos(t);
}

template <typename T> T Math<T>::atan2(T t1, T t2) {
    return std::atan2(t1, t2);
}

template class Math<f32>;

DECOMP_FORCEACTIVE(eggMath_cpp, "-1 <= t && t <= 1", "gcd(%d,%d)\n");

} // namespace EGG
