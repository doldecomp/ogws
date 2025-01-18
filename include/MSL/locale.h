#ifndef MSL_LOCALE_H
#define MSL_LOCALE_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct lconv {
    char* decimal_point;     // at 0x0
    char* thousands_sep;     // at 0x4
    char* grouping;          // at 0x8
    char* currency_symbol;   // at 0xC
    char* mon_decimal_point; // at 0x10
    char* mon_thousands_sep; // at 0x14
    char* mon_grouping;      // at 0x18
    char* positive_sign;     // at 0x1C
    char* negative_sign;     // at 0x20
    char int_frac_digits;    // at 0x24
    char frac_digits;        // at 0x25
    char p_cs_precedes;      // at 0x26
    char p_sep_by_space;     // at 0x27
    char n_cs_precedes;      // at 0x28
    char n_sep_by_space;     // at 0x29
    char p_sign_posn;        // at 0x2A
    char n_sign_posn;        // at 0x2B
    char* int_curr_symbol;   // at 0x2C
    char int_p_cs_precedes;  // at 0x30
    char int_n_cs_precedes;  // at 0x31
    char int_p_sep_by_space; // at 0x32
    char int_n_sep_by_space; // at 0x33
    char int_p_sign_posn;    // at 0x34
    char int_n_sign_posn;    // at 0x35
} lconv;

#ifdef __cplusplus
}
#endif
#endif
