#include "math.h"

double scalbn(double x, int n) {
    double value;
    int exp;

    value = frexp(x, &exp);
    exp += n;

    return ldexp(value, exp);
}
