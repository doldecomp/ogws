#ifndef MSL_MATH_DOUBLE_H
#define MSL_MATH_DOUBLE_H
#include <internal/fdlibm_public.h>
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

static inline float acosf(float x) { return acos(x); }
static inline float ceilf(float x) { return ceil(x); }
static inline float cosf(float x) { return cos(x); }
static inline float sinf(float x) { return sin(x); }
static inline float sqrtf(float x) { return sqrt(x); }
static inline float tanf(float x) { return tan(x); }
static inline float floorf(float x) { return floor(x); }
static inline float fmodf(float x, float y) { return fmod(x, y); }

static inline float modff(float x, float* iptr) {
    float frac;
    double intg;

    x = (double)x;
    frac = modf(x, &intg);
    *iptr = intg;

    return frac;
}

float fabsf(float);

#ifdef __cplusplus
}
#endif
#endif
