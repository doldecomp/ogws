#ifndef MEMCPY_H
#define MEMCPY_H

#include "typesTRK.h"

__declspec(section ".init") void * memcpy(void *, const void *, size_t);

#endif