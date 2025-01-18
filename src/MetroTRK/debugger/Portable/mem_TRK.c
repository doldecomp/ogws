#include <MetroTRK.h>

DECL_SECTION(".init")
void* TRK_memcpy(void* dest, const void* src, size_t count) {
    const char* csrc = (const char*)src;
    char* cdest = (char*)dest;

    csrc--;
    cdest--;
    count++;

    while (--count) {
        *++cdest = *++csrc;
    }

    return dest;
}

DECL_SECTION(".init") void* TRK_memset(void* dest, int val, size_t count) {
    TRK_fill_mem(dest, val, count);
    return dest;
}

// https://decomp.me/scratch/xJC0Q
void TRK_fill_mem(void* dst, int c, size_t count) {
    int work;
    char* bdst = (char*)dst;
    int* wdst = (int*)dst;
    unsigned int cc = (unsigned char)c;

    bdst--;

    // Optimize when filling more than 32B
    if (count >= 32) {
        // How many bytes dest is word-unaligned
        work = ~(unsigned int)(bdst)&3;

        // Byte-store to hit word alignment
        if (work) {
            count -= work;
            do {
                *++bdst = cc;
            } while (--work);
        }

        // Build word-sized value
        if (cc) {
            cc = (cc << 24) | (cc << 16) | (cc << 8) | cc;
        }

        // 32-byte store
        work = count / 32;
        wdst = (int*)(bdst - 3);
        if (work) {
            do {
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
        work = (count / 4) & 7;
        if (work) {
            do {
                *++wdst = cc;
            } while (--work);
        }

        bdst = (char*)wdst + 3;
        count &= 3;
    }

    // Remaining byte-copy, or caller specified < 32B store
    if (count > 0) {
        do {
            *++bdst = cc;
        } while (--count);
    }
}
