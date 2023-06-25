#ifndef MSL_MATH_API_H
#define MSL_MATH_API_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

int __fpclassify(long double);
int __fpclassifyd(double);
int __fpclassifyf(float);

#ifdef __cplusplus
}
#endif
#endif
