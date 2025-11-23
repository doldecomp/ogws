#ifndef _RAND_H
#define _RAND_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

int rand();
void srand(u32 seed);

#ifdef __cplusplus
};
#endif

#endif
