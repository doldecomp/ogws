#ifndef MSL_FDLIBM_PUBLIC_H
#define MSL_FDLIBM_PUBLIC_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

/**
 * For including FDLIBM declarations without also including its many macros.
 */

double atan(double x);
double ceil(double x);
double copysign(double x, double y);
double cos(double x);
double floor(double x);
double frexp(double x, int* eptr);
double ldexp(double value, int exp);
double modf(double x, double* iptr);
double sin(double x);
double tan(double x);
double acos(double x);
double asin(double x);
double atan2(double y, double x);
double fmod(double x, double y);
double pow(double x, double y);
double sqrt(double x);

#ifdef __cplusplus
}
#endif
#endif
