#ifndef MEM_TRK_H
#define MEM_TRK_H
#include "typesTRK.h"

__declspec(section ".init") void * TRK_memset(void *, int, size_t);
__declspec(section ".init") void * TRK_memcpy(void *, const void *, size_t);

void TRK_fill_mem(void *, int, size_t);

#endif