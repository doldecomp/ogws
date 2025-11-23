#include "arith.h"

int abs(int x) {
    return ((x >> 31) ^ x) - (x >> 31);
}
