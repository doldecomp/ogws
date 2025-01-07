#ifndef MSL_MATH_DOUBLE_H
#define MSL_MATH_DOUBLE_H
#include <types.h>

#include <internal/fdlibm_public.h>
#ifdef __cplusplus
extern "C" {
#endif

inline float acosf(float x) {
    return acos(x);
}
inline float asinf(float x) {
    return asin(x);
}
inline float atan2f(float x, float y) {
    return atan2(x, y);
}
inline float ceilf(float x) {
    return ceil(x);
}
inline float cosf(float x) {
    return cos(x);
}
inline float sinf(float x) {
    return sin(x);
}
inline float sqrtf(float x) {
    return sqrt(x);
}
inline float tanf(float x) {
    return tan(x);
}
inline float floorf(float x) {
    return floor(x);
}
inline float fmodf(float x, float y) {
    return fmod(x, y);
}

inline float ldexpf(float value, int exp) {
    return ldexp(value, exp);
}

inline float modff(float x, float* iptr) {
    float frac;
    double intg;

    frac = modf(x, &intg);
    *iptr = intg;

    return frac;
}

float fabsf(float);

#ifdef __cplusplus
}
#endif
#endif
