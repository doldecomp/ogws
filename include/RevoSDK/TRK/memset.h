#ifndef MEMSET_H
#define MEMSET_H
#include "typesTRK.h"

__declspec(section ".init") void * memset(void *, int, size_t);

#endif