#ifndef MEM_H
#define MEM_H
#include "typesTRK.h"

__declspec(section ".init") void * memcpy(void *, const void *, size_t);
__declspec(section ".init") void __fill_mem(void *, int, size_t);
__declspec(section ".init") void * memset(void *, int, size_t);

#endif