#ifndef MSL_MATH_DOUBLE_H
#define MSL_MATH_DOUBLE_H
#include <internal/fdlibm_public.h>
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

static inline float sqrtf(float x) { return sqrt(x); }
static inline float sinf(float x) { return sin(x); }
static inline float cosf(float x) { return cos(x); }
static inline float tanf(float x) { return tan(x); }

static inline float acosf(float x) { return acos(x); }

float fabsf(float);

#ifdef __cplusplus
}
#endif
#endif
