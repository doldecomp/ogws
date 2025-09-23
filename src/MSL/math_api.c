#include "math_api.h"

#pragma exceptions on

int __signbitd(double dbl) {
    return (*(int*)&dbl) & 0x80000000;
}

int __fpclassifyd(double dbl) {
    switch ((*(int*)&dbl) & 0x7FF00000) {
        case 0x7FF00000:
            if (((*(int*)&dbl) & 0xFFFFF) || (*(1 + (int*)&dbl)) & 0xFFFFFFFF) {
                return 1;
            }
            else {
                return 2;
            }

            break;
        case 0:
            if (((*(int*)&dbl) & 0xFFFFF) || (*(1 + (int*)&dbl)) & 0xFFFFFFFF) {
                return 5;
            }
            else {
                return 3;
            }

            break;
    }

    return 4;
}
