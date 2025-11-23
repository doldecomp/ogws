#ifndef MSL_INTERNAL_SFORMATTER_H
#define MSL_INTERNAL_SFORMATTER_H

#include "stddef.h"

enum argument_options {
    normal_argument,
    char_argument,
    short_argument,
    long_argument,
    intmax_argument,
    size_t_argument,
    ptrdiff_argument,
    long_long_argument,
    double_argument,
    long_double_argument,
    wchar_argument
};

typedef unsigned char char_map[32];

#define set_char_map(map, ch) ((map)[(unsigned char)(ch) >> 3] |= (1 << ((ch) & 7)))
#define tst_char_map(map, ch) ((map)[(unsigned char)(ch) >> 3] & (1 << ((ch) & 7)))

typedef struct {
    unsigned char suppress_assignment;
    unsigned char field_width_specified;
    unsigned char argument_options;
    unsigned char conversion_char;
    int field_width;
    char_map char_set;
} scan_format;

#endif // MSL_INTERNAL_SFORMATTER_H
