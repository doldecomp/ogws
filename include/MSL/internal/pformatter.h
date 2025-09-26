#ifndef MSL_INTERNAL_PFORMATTER_H
#define MSL_INTERNAL_PFORMATTER_H

#include "stddef.h"

enum justification_options {
    left_justification,
    right_justification,
    zero_fill
};

enum sign_options { only_minus, sign_always, space_holder };

enum argument_options {
    normal_argument,
    char_argument,
    short_argument,
    long_argument,
    long_long_argument,
    wchar_argument,
    intmax_argument,
    size_t_argument,
    ptrdiff_argument,
    long_double_argument
};

typedef struct {
    char* CharStr;
    size_t MaxCharCount;
    size_t CharsWritten;
} __OutStrCtrl;

#define LDBL_MANT_DIG 24
#define LDBL_MAX_EXP 128
#define TARGET_FLOAT_BITS 32
#define TARGET_FLOAT_BYTES (TARGET_FLOAT_BITS / 8)
#define TARGET_FLOAT_MAX_EXP LDBL_MAX_EXP
#define TARGET_FLOAT_MANT_DIG LDBL_MANT_DIG
#define TARGET_FLOAT_IMPLICIT_J_BIT 1
#define TARGET_FLOAT_MANT_BITS (TARGET_FLOAT_MANT_DIG - TARGET_FLOAT_IMPLICIT_J_BIT)
#define TARGET_FLOAT_EXP_BITS (TARGET_FLOAT_BITS - TARGET_FLOAT_MANT_BITS - 1)

typedef long long intmax_t;

#define PTRDIFF __typeof__((char*)0-(char*)0)
typedef PTRDIFF ptrdiff_t;

#endif // MSL_INTERNAL_PFORMATTER_H
