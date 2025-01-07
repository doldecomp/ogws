#ifndef MSL_MATH_H
#define MSL_MATH_H
#include <types.h>

#include <internal/float.h>
#include <internal/math_api.h>
#include <internal/math_double.h>
#include <internal/math_ppc.h>
#include <internal/math_sun.h>
#ifdef __cplusplus
extern "C" {
#endif

#ifdef __MWERKS__
#define fabs(x) __fabs(x)
#endif

#define NAN (*(float*)&__float_nan);
#define HUGE_VALF (*(float*)&__float_huge);
#define HUGE_VAL (*(float*)&__double_huge);

#define FP_NAN 1
#define FP_INFINITE 2
#define FP_ZERO 3
#define FP_NORMAL 4
#define FP_SUBNORMAL 5

#define M_PI 3.141592653589793f
#define M_SQRT3 1.73205f

#define FLT_EPSILON 1.19209289550781e-7f

#define fpclassify(x)                                                          \
    (sizeof(x) == sizeof(float)                                                \
         ? __fpclassifyf(x)                                                    \
         : (sizeof(x) == sizeof(double) ? __fpclassifyd(x) : __fpclassify(x)))

#define isfinite(x) (fpclassify(x) > FP_INFINITE)
#define isinfinite(x) (fpclassify(x) == FP_INFINITE)
#define isnan(x) (fpclassify(x) == FP_NAN)
#define isnormal(x) (fpclassify(x) == FP_NORMAL)

#ifdef __cplusplus
}
#endif
#endif
