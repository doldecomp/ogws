#ifndef NW4R_MATH_CONSTANT_H
#define NW4R_MATH_CONSTANT_H
#include <nw4r/types_nw4r.h>

#include <cmath>

/******************************************************************************
 *
 * Mathematical constants
 *
 ******************************************************************************/
// Pi mathematical constant
#define NW4R_MATH_PI M_PI

// ln(2)
#define NW4R_MATH_LN_2 0.69314718056f

// 1 / sqrt(3)
#define NW4R_MATH_INVSQRT3 0.577350258f

/******************************************************************************
 *
 * Not-a-number (NaN) types
 *
 ******************************************************************************/
// Quiet NaN (0x7FC00000)
#define NW4R_MATH_QNAN (-(0.0f / 0.0f))

/******************************************************************************
 *
 * Float limits
 *
 ******************************************************************************/
// Smallest finite floating-point value
#define NW4R_MATH_FLT_MIN 1.175494350e-38f

// Largest finite floating-point value
#define NW4R_MATH_FLT_MAX 3.402823466e+38f

// Difference between 1.0 and the next representable value
#define NW4R_MATH_FLT_EPSILON 1.192092895e-7f

#endif
