#ifndef ANSI_FP_H
#define ANSI_FP_H
#include <types.h>

typedef struct decimal {
    char sign;
    char _1;
    short exponent;

    struct {
        unsigned char length;
        unsigned char text[36];
        unsigned char pad;
    } sig;
} decimal;

typedef struct decform {
    char style;
    char _1;
    short digits;
} decform;

#ifdef __cplusplus
extern "C" {
#endif

extern const unsigned short __ctype_mapC[0x100];
extern const unsigned char __lower_mapC[0x100];
extern const unsigned char __upper_mapC[0x100];

#ifdef __cplusplus
}
#endif
#endif
