#include <string.h>

DECL_SECTION(".init") void * memcpy(void * dest, const void * src, size_t count)
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

DECL_SECTION(".init") void __fill_mem(void* dst, int c, size_t n)
{
    int work;
    char* bdst = (char*)dst;
    int* wdst = (int*)dst;
    unsigned int cc = (unsigned char)c;
    
    bdst--;

    // Optimize when filling more than 32B
    if (n >= 32)
    {
        // How many bytes dest is word-unaligned
        work = ~(u32)(bdst) & 3;

        // Byte-store to hit word alignment
        if (work)
        {
            n -= work;
            do
            {
                *++bdst = cc;
            } while(--work);
        }

        // Build word-sized value
        if (cc)
        {
            cc = (cc << 24) | (cc << 16) | (cc << 8) | cc;
        }

        // 32-byte store
        work = n / 32;
        wdst = (int *)(bdst - 3);
        if (work)
        {
            do
            {
                wdst[1] = cc;
                wdst[2] = cc;
                wdst[3] = cc;
                wdst[4] = cc;
                wdst[5] = cc;
                wdst[6] = cc;
                wdst[7] = cc;
                wdst[8] = cc;
                wdst += 8;
            } while (--work);
        }

        // 4-byte (word) store
        work = (n / 4) & 7;
        if (work)
        {
            do
            {
                *++wdst = cc;
            } while(--work);
        }

        bdst = (char *)wdst + 3;
        n &= 3;
    }

    // Remaining byte-copy, or caller specified < 32B store
    if (n > 0)
    {
        do
        {
            *++bdst = cc;
        } while(--n);
    }
}

DECL_SECTION(".init") void * memset(void * dest, int val, size_t count)
{
    __fill_mem(dest, val, count);
    return dest;
}

DECL_WEAK size_t strlen(const char* s) {
    const u8* p = (u8*)s - 1;
    size_t len = -1;
    
    do {
        len++;
    } while (*++p);

    return len;
}