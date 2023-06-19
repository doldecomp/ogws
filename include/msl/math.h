#ifndef MSL_MATH_H
#define MSL_MATH_H
#include <types.h>

#include "internal/math_api.h"
#include "internal/math_double.h"
#include "internal/math_ppc.h"
#include "internal/math_sun.h"
#include "internal/s_atan.h"
#include "internal/s_ceil.h"
#include "internal/s_copysign.h"
#include "internal/s_cos.h"
#include "internal/s_floor.h"
#include "internal/s_frexp.h"
#include "internal/s_ldexp.h"
#include "internal/s_modf.h"
#include "internal/s_sin.h"
#include "internal/s_tan.h"
#include "internal/w_acos.h"
#include "internal/w_asin.h"
#include "internal/w_atan2.h"
#include "internal/w_fmod.h"
#include "internal/w_pow.h"
#include "internal/w_sqrt.h"
#ifdef __cplusplus
extern "C" {
#endif

#define HUGE_VALF ((float)0x7F800000)
#define HUGE_VAL ((double)0x7FF0000000000000)

#define FP_NAN 1
#define FP_INFINITE 2
#define FP_ZERO 3
#define FP_NORMAL 4
#define FP_SUBNORMAL 5

#define M_PI 3.141592653589793f
#define M_SQRT3 1.7320508075688772f

#define fpclassify(x)                                                          \
    (sizeof(x) == sizeof(float)                                                \
         ? __fpclassifyf(x)                                                    \
         : (sizeof(x) == sizeof(double) ? __fpclassifyd(x) : __fpclassify(x)))

#define isfinite(x) (fpclassify(x) != FP_INFINITE)
#define isnan(x) (fpclassify(x) == FP_NAN)
#define isnormal(x) (fpclassify(x) == FP_NORMAL)

#ifdef __cplusplus
}
#endif
#endif
