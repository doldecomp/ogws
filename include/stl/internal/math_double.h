#ifndef MSL_MATH_DOUBLE_H
#define MSL_MATH_DOUBLE_H
#include "s_cos.h"
#include "s_sin.h"
#include "s_tan.h"
#include "w_sqrt.h"
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

static inline float sqrtf(float x) { return sqrt(x); }
static inline float sinf(float x) { return sin(x); }
static inline float cosf(float x) { return cos(x); }
static inline float tanf(float x) { return tan(x); }

float fabsf(float);

#ifdef __cplusplus
}
#endif
#endif
