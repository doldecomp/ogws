#ifndef FILL_MEM_H
#define FILL_MEM_H
#include "typesTRK.h"

__declspec(section ".init") void * __fill_mem(void *, int, size_t);

#endif