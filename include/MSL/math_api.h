#ifndef MSL_MATH_API_H
#define MSL_MATH_API_H
#ifdef __cplusplus
extern "C" {
#endif

int __fpclassify(long double);
int __fpclassifyd(double);
int __fpclassifyf(float);
int __signbitd(double);

double copysign(double, double);
double frexp(double, int *);
double ldexp(double, int);
double nan(const char *);

#ifdef __cplusplus
}
#endif
#endif
