#include "string.h"

#define K1 0x80808080
#define K2 0xFEFEFEFF

#define set_unk(x, y)                                                          \
    x[(unsigned char)(y) >> 3] |= (unsigned char)(1 << ((y)&7))
#define cond_unk(x, y)                                                         \
    (x[(unsigned char)(y) >> 3] & (unsigned char)(1 << ((y)&7)))
typedef unsigned char unk[32];

// thanks metrowerks very cool
char* strcpy(char* dst, const char* src) {
    register u8 *destb, *fromb;
    register u32 w, t, align;

    fromb = (u8*)src;
    destb = (u8*)dst;

    if ((align = ((int)fromb & 3)) != ((int)destb & 3)) {
        goto bytecopy;
    }

    if (align) {
        if ((*destb = *fromb) == 0) {
            return (dst);
        }
        for (align = 3 - align; align; align--) {
            if ((*(++destb) = *(++fromb)) == 0) {
                return (dst);
            }
        }
        ++destb;
        ++fromb;
    }

    w = *((int*)(fromb));

    t = w + K2;
    t &= ~w;
    t &= K1;
    if (t) {
        goto bytecopy;
    }
    --((int*)(destb));

    do {
        *(++((int*)(destb))) = w;
        w = *(++((int*)(fromb)));

        t = w + K2;
        t &= ~w;
        t &= K1;
        if (t) {
            goto adjust;
        }
    } while (1);

adjust:
    ++((int*)(destb));
bytecopy:
    if ((*destb = *fromb) == 0) {
        return dst;
    }
    do {
        if ((*(++destb) = *(++fromb)) == 0) {
            return dst;
        }
    } while (1);

    return dst;
}

char* strncpy(char* dst, const char* src, size_t n) {
    const unsigned char* p = (const unsigned char*)src - 1;
    unsigned char* q = (unsigned char*)dst - 1;
    unsigned char zero = 0;

    n++;

    while (--n) {
        if (!(*++q = *++p)) {
            while (--n) {
                *++q = 0;
            }
            break;
        }
    }
    return (dst);
}

char* strcat(char* dst, const char* src) {
    const u8* p = (u8*)src - 1;
    u8* q = (u8*)dst - 1;

    while (*++q)
        ;

    q--;

    while (*++q = *++p)
        ;

    return (dst);
}

char* strncat(char* dst, const char* src, size_t n) {
    const u8* p = (u8*)src - 1;
    u8* q = (u8*)dst - 1;

    while (*++q)
        ;

    q--;
    n++;

    while (--n) {
        if (!(*++q = *++p)) {
            q--;
            break;
        }
    }

    *++q = 0;

    return dst;
}

int strcmp(const char* str1, const char* str2) {
    // bless metrowerks for this implementation
    register u8* left = (u8*)str1;
    register u8* right = (u8*)str2;
    u32 align, l1, r1, x;

    l1 = *left;
    r1 = *right;
    if (l1 - r1) {
        return (l1 - r1);
    }

    if ((align = ((int)left & 3)) != ((int)right & 3)) {
        goto bytecopy;
    }
    if (align) {
        if (l1 == 0) {
            return 0;
        }
        for (align = 3 - align; align; align--) {
            l1 = *(++left);
            r1 = *(++right);
            if (l1 - r1) {
                return (l1 - r1);
            }
            if (l1 == 0) {
                return 0;
            }
        }
        left++;
        right++;
    }

    l1 = *(int*)left;
    r1 = *(int*)right;
    x = l1 + K2;
    x &= ~l1;
    if (x & K1) {
        goto adjust;
    }
    while (l1 == r1) {
        l1 = *(++((int*)(left)));
        r1 = *(++((int*)(right)));
        x = l1 + K2;
        if (x & K1) {
            goto adjust;
        }
    }

adjust:
    l1 = *left;
    r1 = *right;
    if (l1 - r1) {
        return (l1 - r1);
    }
bytecopy:
    if (l1 == 0) {
        return 0;
    }
    do {
        l1 = *(++left);
        r1 = *(++right);
        if (l1 - r1) {
            return (l1 - r1);
        }
        if (l1 == 0) {
            return 0;
        }
    } while (1);
}

int strncmp(const char* str1, const char* str2, size_t n) {
    const u8* p1 = (u8*)str1 - 1;
    const u8* p2 = (u8*)str2 - 1;
    u32 c1, c2;

    n++;

    while (--n) {
        if ((c1 = *++p1) != (c2 = *++p2)) {
            return (c1 - c2);
        } else if (!c1) {
            break;
        }
    }
    return 0;
}

char* strchr(const char* str, int chr) {
    const u8* p = (u8*)str - 1;
    u32 c = (chr & 0xFF);
    u32 ch;

    while (ch = *++p) {
        if (ch == c) {
            return ((char*)p);
        }
    }

    return (c ? 0 : (char*)p);
}

char* strstr(const char* str, const char* pat) {
    u8* s1 = (u8*)str - 1;
    u8* p1 = (u8*)pat - 1;
    u32 firstc, c1, c2;

    if (pat == NULL || !(firstc = *++p1)) {
        return (char*)str;
    }

    while ((c1 = *++s1)) {
        if (c1 == firstc) {
            const u8* s2 = s1 - 1;
            const u8* p2 = p1 - 1;

            while ((c1 = *(++s2)) == (c2 = *(++p2)) && c1)
                ;

            if (!c2) {
                return (char*)s1;
            }
        }
    }

    return NULL;
}
