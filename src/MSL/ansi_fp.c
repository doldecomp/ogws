#include "ansi_fp.h"
#include "math_api.h"
#include "float.h"

#pragma exceptions on

const signed char lbl_8037B2F8[] =
    "542101086242752217003726400434970855712890625\000"
    "11102230246251565404236316680908203125\000"
    "23283064365386962890625\000"
    "152587890625\000"
    "390625\000"
    "78125\000"
    "15625\000"
    "3125\000"
    "625\000"
    "125\000"
    "25\000"
    "5\000"
    "1\000"
    "2\000"
    "4\000"
    "8\000"
    "16\000"
    "32\000"
    "64\000"
    "128\000"
    "256\000"
    "179769313486231580793728714053034151\000\000\000";

const unsigned short __ctype_mapC[0x100] = {
    4,     4,     4,     4,     4,     4,     4,     4,     
    4,     0x106, 0x104, 0x104, 0x104, 0x104, 4,     4,
    4,     4,     4,     4,     4,     4,     4,     4,
    4,     4,     4,     4,     4,     4,     4,     4, 
    0x142, 0xD0,  0xD0,  0xD0,  0xD0,  0xD0,  0xD0,  0xD0,
    0xD0,  0xD0,  0xD0,  0xD0,  0xD0,  0xD0,  0xD0,  0xD0,
    0x458, 0x458, 0x458, 0x458, 0x458, 0x458, 0x458, 0x458,
    0x458, 0x458, 0xD0,  0xD0,  0xD0,  0xD0,  0xD0,  0xD0,
    0xD0,  0x651, 0x651, 0x651, 0x651, 0x651, 0x651, 0x251,
    0x251, 0x251, 0x251, 0x251, 0x251, 0x251, 0x251, 0x251,
    0x251, 0x251, 0x251, 0x251, 0x251, 0x251, 0x251, 0x251,
    0x251, 0x251, 0x251, 0xD0,  0xD0,  0xD0,  0xD0,  0xD0,
    0xD0,  0x471, 0x471, 0x471, 0x471, 0x471, 0x471, 0x71,
    0x71,  0x71,  0x71,  0x71,  0x71,  0x71,  0x71,  0x71,
    0x71,  0x71,  0x71,  0x71,  0x71,  0x71,  0x71,  0x71,
    0x71,  0x71,  0x71,  0xd0,  0xd0,  0xd0,  0xd0,  4

};

const unsigned char __lower_mapC[0x100] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
    ' ',  '!',  '"',  '#',  '$',  '%',  '&',  '\'', '(',  ')',  '*',  '+',  ',',  '-',  '.',  '/',
    '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  ':',  ';',  '<',  '=',  '>',  '?',
    '@',  'a',  'b',  'c',  'd',  'e',  'f',  'g',  'h',  'i',  'j',  'k',  'l',  'm',  'n',  'o',
    'p',  'q',  'r',  's',  't',  'u',  'v',  'w',  'x',  'y',  'z',  '[',  '\\', ']',  '^',  '_',
    '`',  'a',  'b',  'c',  'd',  'e',  'f',  'g',  'h',  'i',  'j',  'k',  'l',  'm',  'n',  'o',
    'p',  'q',  'r',  's',  't',  'u',  'v',  'w',  'x',  'y',  'z',  '{',  '|',  '}',  '~',  0x7F,
    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F,
    0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F,
    0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF,
    0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF,
    0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF,
    0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF,
    0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF,
    0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE, 0xFF};

const unsigned char __upper_mapC[0x100] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
    ' ',  '!',  '"',  '#',  '$',  '%',  '&',  '\'', '(',  ')',  '*',  '+',  ',',  '-',  '.',  '/',
    '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  ':',  ';',  '<',  '=',  '>',  '?',
    '@',  'A',  'B',  'C',  'D',  'E',  'F',  'G',  'H',  'I',  'J',  'K',  'L',  'M',  'N',  'O',
    'P',  'Q',  'R',  'S',  'T',  'U',  'V',  'W',  'X',  'Y',  'Z',  '[',  '\\', ']',  '^',  '_',
    '`',  'A',  'B',  'C',  'D',  'E',  'F',  'G',  'H',  'I',  'J',  'K',  'L',  'M',  'N',  'O', 
    'P',  'Q',  'R',  'S',  'T',  'U',  'V',  'W',  'X',  'Y',  'Z',  '{',  '|',  '}',  '~',  0x7F,
    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F,
    0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F,
    0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF,
    0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF,
    0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF,
    0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF,
    0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF,
    0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE, 0xFF};

#define INFINITY (*(float*)__float_huge)
#define SIGDIGLEN 36
extern double pow(double, double);


inline int count_trailing(double x) {
    return __builtin___count_trailing_zero64(*(unsigned long long*)&x |
                                             0x0010000000000000);
}

static inline void __dorounddecup(decimal* d, int digits) {
    u8* b = d->sig.text;
    u8* i = b + digits - 1;

    while (1) {
        if (*i < 9) {
            *i += 1;
            break;
        }
        if (i == b) {
            *i = 1;
            d->exponent++;
            break;
        }
        *i-- = 0;
    }
}

static inline int __must_round(const decimal* d, int digits) {
    // regswap fun here
    u8 const* i = d->sig.text + digits;

    if (*i > 5) {
        return 1;
    }

    if (*i < 5) {
        return -1;
    }

    for (i++; i < d->sig.text + d->sig.length; i++) {
        if (*i != 0) {
            return 1;
        }
    }

    if (d->sig.text[digits - 1] & 1) {
        return 1;
    }

    return -1;
}

static inline void __rounddec(decimal* d, int digits) {
    if (digits > 0 && digits < d->sig.length) {
        int unkBool = __must_round(d, digits);
        d->sig.length = digits;

        if (unkBool >= 0) {
            __dorounddecup(d, digits);
        }
    }
}

void __ull2dec(decimal* pDecimal, unsigned long long input) {
    pDecimal->sign = 0;
    pDecimal->sig.length = 0;

    for (; input != 0; input /= 10) {
        pDecimal->sig.text[pDecimal->sig.length++] =
            (unsigned char)(input % 10);
    }

    /* regswap if these were declared at the top...only logic I can think of is making them valid in this block */
    {
        unsigned char* start = pDecimal->sig.text;
        unsigned char* end = pDecimal->sig.text + pDecimal->sig.length;

        for (; start < --end; ++start) {
            unsigned char t = *start;
            *start = *end;
            *end = t;
        }
    }

    pDecimal->exponent = (short)(pDecimal->sig.length - 1);
}

void __timesdec(decimal* pResult, const decimal* x, const decimal* y) {
    unsigned long accumulator = 0;
    unsigned char mant[72];
    int i = x->sig.length + y->sig.length - 1;
    unsigned char* ip = mant + i + 1;
    unsigned char* ep = ip;
    pResult->sign = 0;

    for (; i > 0; --i) {
        int k = y->sig.length - 1;
        int j = i - k - 1;
        int l;
        int t;
        unsigned char const *jp, *kp;

        if (j < 0) {
            j = 0;
            k = i - 1;
        }

        jp = x->sig.text + j;
        kp = y->sig.text + k;
        l = k + 1;
        t = x->sig.length - j;

        if (l > t) {
            l = t;
        }

        for (; l > 0; --l, ++jp, --kp) {
            accumulator += (unsigned long)(*jp) * *kp;
        }

        *--ip = (unsigned char)(accumulator % 10);
        accumulator /= 10;
    }

    pResult->exponent = (short)(x->exponent + y->exponent);

    if (accumulator > 0) {
        *--ip = (unsigned char)accumulator;
        pResult->exponent++;
    }

    for (i = 0; i < 36 && ip < ep; ++i, ++ip) {
        pResult->sig.text[i] = *ip;
    }

    pResult->sig.length = i;

    if (ip < ep && *ip >= 5) {
        if (*ip == 5) {
            unsigned char* jp = ip + 1;
            for (; jp < ep; ++jp) {
                if (*jp != 0) {
                    goto round;
                }
            }

            if ((*(ip - 1) & 1) == 0) {
                return;
            }
        }
    round:
        __dorounddecup(pResult, pResult->sig.length);
    }
}

void __str2dec(decimal* pDecimal, const char* pStr, short exp) {
    int i;
    pDecimal->exponent = exp;
    pDecimal->sign = 0;

    for (i = 0; i < 36 && *pStr != 0;) {
        pDecimal->sig.text[i++] = (unsigned char)(*pStr++ - '0');
    }

    pDecimal->sig.length = i;

    if (*pStr != 0) {
        if (*pStr < 5) {
            return;
        }

        if (*pStr > 5) {
            goto round;
        }

        {
            const char* p = pStr + 1;
            for (; *p != 0; ++p) {
                if (*p != '0') {
                    goto round;
                }
            }

            if ((pDecimal->sig.text[i - 1] & 1) == 0) {
                return;
            }
        }

    round:
        __dorounddecup(pDecimal, pDecimal->sig.length);
    }
}



static void __two_exp(decimal* pDecimal, long exp) {
    switch (exp) {
        case -64:
            __str2dec(pDecimal, (const char*)&lbl_8037B2F8[0], -20);
            return;
        case -53:
            __str2dec(pDecimal, (const char*)&lbl_8037B2F8[0x2E], -16);
            return;
        case -32:
            __str2dec(pDecimal, (const char*)&lbl_8037B2F8[0x55], -10);
            return;
        case -16:
            __str2dec(pDecimal, (const char*)&lbl_8037B2F8[0x6D], -5);
            return;
        case -8:
            __str2dec(pDecimal, (const char*)&lbl_8037B2F8[0x7A], -3);
            return;
        case -7:
            __str2dec(pDecimal, (const char*)&lbl_8037B2F8[0x81], -3);
            return;
        case -6:
            __str2dec(pDecimal, (const char*)&lbl_8037B2F8[0x87], -2);
            return;
        case -5:
            __str2dec(pDecimal, (const char*)&lbl_8037B2F8[0x8D], -2);
            return;
        case -4:
            __str2dec(pDecimal, (const char*)&lbl_8037B2F8[0x92], -2);
            return;
        case -3:
            __str2dec(pDecimal, (const char*)&lbl_8037B2F8[0x96], -1);
            return;
        case -2:
            __str2dec(pDecimal, (const char*)&lbl_8037B2F8[0x9A], -1);
            return;
        case -1:
            __str2dec(pDecimal, (const char*)&lbl_8037B2F8[0x9D], -1);
            return;
        case 0:
            __str2dec(pDecimal, (const char*)&lbl_8037B2F8[0x9F], 0);
            return;
        case 1:
            __str2dec(pDecimal, (const char*)&lbl_8037B2F8[0xA1], 0);
            return;
        case 2:
            __str2dec(pDecimal, (const char*)&lbl_8037B2F8[0xA3], 0);
            return;
        case 3:
            __str2dec(pDecimal, (const char*)&lbl_8037B2F8[0xA5], 0);
            return;
        case 4:
            __str2dec(pDecimal, (const char*)&lbl_8037B2F8[0xA7], 1);
            return;
        case 5:
            __str2dec(pDecimal, (const char*)&lbl_8037B2F8[0xAA], 1);
            return;
        case 6:
            __str2dec(pDecimal, (const char*)&lbl_8037B2F8[0xAD], 1);
            return;
        case 7:
            __str2dec(pDecimal, (const char*)&lbl_8037B2F8[0xB0], 2);
            return;
        case 8:
            __str2dec(pDecimal, (const char*)&lbl_8037B2F8[0xB4], 2);
            return;
    }

    {
        decimal x2, temp;
        __two_exp(&x2, ((long)((0x80000000UL & exp) >> 31) + exp) >> 1);
        __timesdec(pDecimal, &x2, &x2);
        if (exp & 1) {
            temp = *pDecimal;
            if (exp > 0)
                __str2dec(&x2, (const char*)&lbl_8037B2F8[0xA1], 0);
            else
                __str2dec(&x2, (const char*)&lbl_8037B2F8[0x9D], -1);
            __timesdec(pDecimal, &temp, &x2);
        }
    }
}

int __equals_dec(const decimal* x, const decimal* y) {
    if (x->sig.text[0] == 0) {
        if (y->sig.text[0] == 0) {
            return 1;
        }

        return 0;
    }

    if (y->sig.text[0] == 0) {
        if (x->sig.text[0] == 0) {
            return 1;
        }

        return 0;
    }

    if (x->exponent == y->exponent) {
        int i;
        int l = x->sig.length;

        if (l > y->sig.length) {
            l = y->sig.length;
        }

        for (i = 0; i < l; ++i) {
            if (x->sig.text[i] != y->sig.text[i]) {
                return 0;
            }
        }

        if (l == x->sig.length) {
            x = y;
        }

        for (; i < x->sig.length; ++i) {
            if (x->sig.text[i] != 0) {
                return 0;
            }
        }

        return 1;
    }

    return 0;
}

static int __less_dec(const decimal* x, const decimal* y) {
    if (x->sig.text[0] == 0) {
        if (y->sig.text[0] != 0) {
            return 1;
        }

        return 0;
    }

    if (y->sig.text[0] == 0) {
        return 0;
    }

    if (x->exponent == y->exponent) {
        int i;
        int l = x->sig.length;

        if (l > y->sig.length) {
            l = y->sig.length;
        }

        for (i = 0; i < l; ++i) {
            if (x->sig.text[i] < y->sig.text[i]) {
                return 1;
            }

            if (y->sig.text[i] < x->sig.text[i]) {
                return 0;
            }
        }

        if (l == x->sig.length) {
            for (; i < y->sig.length; ++i) {
                if (y->sig.text[i] != 0) {
                    return 1;
                }
            }
        }

        return 0;
    }

    return x->exponent < y->exponent;
}

void __minus_dec(decimal* z, const decimal* x, const decimal* y) {
    int zlen, dexp;
    unsigned char *ib, *i, *ie;
    unsigned char const *jb, *j, *jn;
    *z = *x;

    if (y->sig.text[0] == 0) {
        return;
    }

    zlen = z->sig.length;

    if (zlen < y->sig.length) {
        zlen = y->sig.length;
    }

    dexp = z->exponent - y->exponent;
    zlen += dexp;

    if (zlen > 36) {
        zlen = 36;
    }

    while (z->sig.length < zlen) {
        z->sig.text[z->sig.length++] = 0;
    }

    ib = z->sig.text;
    i = ib + zlen;

    if (y->sig.length + dexp < zlen) {
        i = ib + (y->sig.length + dexp);
    }

    jb = y->sig.text;
    j = jb + (i - ib - dexp);
    jn = j;

    while (i > ib && j > jb) {
        --i;
        --j;
        if (*i < *j) {
            unsigned char* k = i - 1;
            while (*k == 0) {
                --k;
            }
            while (k != i) {
                --*k;
                *++k += 10;
            }
        }

        *i -= *j;
    }

    if (jn - jb < y->sig.length) {
        BOOL round_down = FALSE;
        if (*jn < 5) {
            round_down = TRUE;
        } else if (*jn == 5) {
            unsigned char const* je = y->sig.text + y->sig.length;

            for (j = jn + 1; j < je; ++j) {
                if (*j != 0) {
                    goto done;
                }
            }

            i = ib + (jn - jb) + dexp - 1;

            if (*i & 1) {
                round_down = 1;
            }
        }
        if (round_down) {
            if (*i < 1) {
                unsigned char* k = i - 1;

                while (*k == 0) {
                    --k;
                }
                while (k != i) {
                    --*k;
                    *++k += 10;
                }
            }

            *i -= 1;
        }
    }

done:
    for (i = ib; *i == 0; ++i)
        ;

    if (i > ib) {
        unsigned char dl = (unsigned char)(i - ib);
        z->exponent -= dl;
        ie = ib + z->sig.length;
        for (; i < ie; ++i, ++ib)
            *ib = *i;
        z->sig.length -= dl;
    }

    ib = z->sig.text;

    for (i = ib + z->sig.length; i > ib;) {
        --i;
        if (*i != 0) {
            break;
        }
    }

    z->sig.length = (unsigned char)(i - ib + 1);
}

void __num2dec_internal(decimal* pDecimal, double x) {
    char sign = (char)(__signbitd(x) != 0);
    if (x == 0.0) {
        pDecimal->sign = sign;
        pDecimal->exponent = 0;
        pDecimal->sig.length = 1;
        pDecimal->sig.text[0] = 0;
        return;
    }

    if (!(__fpclassifyd(x) > 2)) {
        pDecimal->sign = sign;
        pDecimal->exponent = 0;
        pDecimal->sig.length = 1;
        pDecimal->sig.text[0] =
            (unsigned char)(__fpclassifyd(x) == 1 ? 'N' : 'I');
        return;
    }

    if (sign) {
        x = -x;
    }

    {
        int exp;
        double frac = frexp(x, &exp);
        long num_bits_extract = 53 - count_trailing(frac);
        decimal int_d, pow2_d;
        __two_exp(&pow2_d, exp - num_bits_extract);
        __ull2dec(&int_d,
                  (unsigned long long)ldexp(frac, (int)num_bits_extract));
        __timesdec(pDecimal, &int_d, &pow2_d);
        pDecimal->sign = sign;
    }
}

void __num2dec(const decform* form, double val, decimal* d) {
    short digits = form->digits;
    int i;
    __num2dec_internal(d, val);

    if (d->sig.text[0] > 9) {
        return;
    }

    if (digits > SIGDIGLEN) {
        digits = SIGDIGLEN;
    }

    __rounddec(d, digits);

    while (d->sig.length < digits) {
        d->sig.text[d->sig.length++] = 0;
    }

    d->exponent -= d->sig.length - 1;

    for (i = 0; i < d->sig.length; i++) {
        d->sig.text[i] += '0';
    }
}

double __dec2num(const decimal* d) {
    if (d->sig.length <= 0) {
        return copysign(0.0, d->sign == 0 ? 1.0 : -1.0);
    }

    switch (d->sig.text[0]) {
    case '0':
        return copysign(0.0, d->sign == 0 ? 1.0 : -1.0);
    case 'I':
        return copysign((double)INFINITY, d->sign == 0 ? 1.0 : -1.0);
    case 'N': {
        double result;
        long long* ll = (long long*)&result;
        *ll = 0x7FF0000000000000ULL;
        if (d->sign)
            *ll |= 0x8000000000000000ULL;
        *ll |= 0x0008000000000000ULL;

        return result;
    }
    }
    {
        static double pow_10[8] = {1e1, 1e2, 1e3, 1e4, 1e5, 1e6, 1e7, 1e8};
        decimal dec = *d;
        unsigned char* i = dec.sig.text;
        unsigned char* e = i + dec.sig.length;
        double first_guess;
        int exponent;

        for (; i < e; ++i) {
            *i -= '0';
        }

        dec.exponent += dec.sig.length - 1;
        exponent = dec.exponent;
        {
            decimal max;
            __str2dec(&max, (const char*)&lbl_8037B2F8[0xB8], 308);
            if (__less_dec(&max, &dec)) {
                return copysign((double)INFINITY, d->sign == 0 ? 1.0 : -1.0);
            }
        }

        i = dec.sig.text;
        first_guess = *i++;

        while (i < e) {
            unsigned long ival = 0;
            int j;
            double temp1, temp2;
            int ndig = (int)(e - i) % 8;

            if (ndig == 0) {
                ndig = 8;
            }

            for (j = 0; j < ndig; ++j, ++i) {
                ival = ival * 10 + *i;
            }

            temp1 = first_guess * pow_10[ndig - 1];
            temp2 = temp1 + ival;

            if (ival != 0 && temp1 == temp2) {
                break;
            }

            first_guess = temp2;
            exponent -= ndig;
        }
        if (exponent < 0) {
            first_guess /= pow(5.0, -exponent);
        } else {
            first_guess *= pow(5.0, exponent);
        }

        first_guess = ldexp(first_guess, exponent);

        if (__fpclassifyd(first_guess) == 2) {
            first_guess = (double)0x7FEFFFFFFFFFFFFF;
        }

        {
            decimal feedback1, feedback2, difflow, diffhigh;
            double next_guess;
            long long* ull = (long long*)&next_guess;
            int guessed_low = 0;
            __num2dec_internal(&feedback1, first_guess);

            if (__equals_dec(&feedback1, &dec)) {
                goto done;
            }

            if (__less_dec(&feedback1, &dec)) {
                guessed_low = 1;
            }

            next_guess = first_guess;
            while (1) {
                if (guessed_low) {
                    ++*ull;
                    if (__fpclassifyd(next_guess) != 2) {
                        ; // this makes it match somehow
                    } else {
                        goto done;
                    }
                } else {
                    --*ull;
                }

                __num2dec_internal(&feedback2, next_guess);
                if (guessed_low && !__less_dec(&feedback2, &dec)) {
                    break;
                } else if (!guessed_low && !__less_dec(&dec, &feedback2)) {
                    difflow = feedback1;
                    feedback1 = feedback2;
                    feedback2 = difflow;
                    {
                        double temp = first_guess;
                        first_guess = next_guess;
                        next_guess = temp;
                    }
                    break;
                }
                feedback1 = feedback2;
                first_guess = next_guess;
            }

            __minus_dec(&difflow, &dec, &feedback1);
            __minus_dec(&diffhigh, &feedback2, &dec);
            if (__equals_dec(&difflow, &diffhigh)) {
                if (*(long long*)&first_guess & 1) {
                    first_guess = next_guess;
                }
            } else if (!__less_dec(&difflow, &diffhigh)) {
                first_guess = next_guess;
            }
        }
    done:
        if (dec.sign) {
            first_guess = -first_guess;
        }
        return first_guess;
    }
}