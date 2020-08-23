#include "__fill_mem.h"
void (*a)();
void __fill_mem(void * dest, int val, size_t count)
{
	char * cdest = (char *)dest;
	int cval = (unsigned char)val;
	int * idest = (int *)dest;
	int r0;
	cdest--;
	if (count >= 0x20)
	{
		r0 = ~(int)(cdest) & 3;
		
		if (r0)
		{
			count -= r0;
			
			do
			{
				*++cdest = cval;
			} while(--r0);
		}
		
		if (cval)
		{
			cval = (cval << 0x18) | (cval << 0x10) | (cval << 0x8) | cval;
		}
		
		r0 = count >> 5;
		idest = (int *)(cdest - 3);
		
		if (r0)
		{
			do
			{
				idest[1] = cval;//4
				--r0;
				idest[2] = cval;//8
				idest[3] = cval;//c
				idest[4] = cval;//10
				idest[5] = cval;//14
				idest[6] = cval;//18
				idest[7] = cval;//1c
				*(idest += 8) = cval;//20
			} while (r0);
		}
		
		r0 = (count >> 2) & 7;
		
		if (r0)
		{
			do
			{
				*++idest = cval;
			} while(--r0);
		}
		
		cdest = (char *)idest + 3;
		count &= 3;
	}
	
	if (count)
	{
	do
	{
		*++cdest = cval;
	} while(--count);
	}
}