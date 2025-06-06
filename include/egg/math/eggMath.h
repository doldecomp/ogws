#ifndef EGG_MATH_MATH_H
#define EGG_MATH_MATH_H
#include <egg/types_egg.h>

namespace EGG {

template <typename T> class Math {
public:
    static T sqrt(T t);
    static T sin(T t);
    static T cos(T t);
    static T atan2(T ty, T tx);
};

} // namespace EGG

#endif
