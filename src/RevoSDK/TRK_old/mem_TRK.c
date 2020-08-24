#include "mem_TRK.h"

void * TRK_memset(void * dest, int val, size_t count)
{
	TRK_fill_mem(dest, val, count);
	return dest;
}

void * TRK_memcpy(void * dest, const void * src, size_t count)
{
	const char * csrc = (const char *)src;
	char * cdest = (char *)dest;
	
	csrc--;
	cdest--;
	count++;
	
	while (--count)
	{
		*++cdest = *++csrc;
	}
	
	return dest;
}