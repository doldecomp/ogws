#ifndef MSL_MATH_H
#define MSL_MATH_H
#include <stddef.h>
#ifdef __cplusplus
extern "C" {
#endif

double sin(double);
double cos(double);

double atan2(double y, double x);

double sqrt(double);

double floor(double);
double ceil(double);

double modf(double, double *);

double pow(double base, double exp);

#ifdef __cplusplus
}
#endif
#endif