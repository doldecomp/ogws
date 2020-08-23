#include "memset.h"
#include "__fill_mem.h"

void * memset(void * dest, int val, size_t count)
{
	__fill_mem(dest, val, num);
	return dest;
}