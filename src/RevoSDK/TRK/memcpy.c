#include "memcpy.h"

// O4,s
void * memcpy(void * dest, const void * src, size_t count)
{
	const char * csrc = (const char *)src;
	char * cdest = (char *)dest;
	
	if (src >= dest)
	{
		csrc--;
		cdest--;
		count++;
		
		while (--count)
		{
			*++cdest = *++csrc;
		}
	}
	else
	{
		csrc += count;
		cdest += count;
		count++;
		
		while (--count)
		{
			*--cdest = *--csrc;
		}
	}
}