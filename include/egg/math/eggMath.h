#ifndef EGG_MATH_MATH_H
#define EGG_MATH_MATH_H
#include <egg/types_egg.h>

#include <cmath>

namespace EGG {

template <typename T> class Math {
public:
    static T sqrt(T t);
    static T sin(T t);
    static T cos(T t);
    static T atan2(T ty, T tx);

    static T zero() {
        return static_cast<T>(0);
    }

    static T pi() {
        return static_cast<T>(M_PI);
    }
    static T pi_half() {
        return static_cast<T>(M_PI / 2);
    }
    static T pi2() {
        return static_cast<T>(M_PI * 2);
    }

    static T neg(T t) {
        return -t;
    }
    static T inv(T t) {
        return static_cast<T>(1) / t;
    }
    static T square(T t) {
        return t * t;
    }

    static T abs(T t) {
        return t > zero() ? t : neg(t);
    }

    static T min(T t1, T t2) {
        return t1 < t2 ? t1 : t2;
    }
    static T max(T t1, T t2) {
        return t1 > t2 ? t1 : t2;
    }
};

} // namespace EGG

#endif
