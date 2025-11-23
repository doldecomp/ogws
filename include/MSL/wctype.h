#ifndef WCTYPE_H
#define WCTYPE_H

#include "types.h"
#include "wchar.h"
#include "locale.h"

extern const unsigned short __wctype_mapC[0x100];
extern const wchar_t __wlower_mapC[0x100];
extern const wchar_t __wupper_mapC[0x100];

inline int iswdigit(wint_t c) {
    return ((c < 0) || (c >= 0x100))
               ? 0
               : (int)(_current_locale.ctype_cmpt_ptr->wctype_map_ptr[c] & 0x8);
}

inline int iswupper(wint_t c) {
    return ((c < 0) || (c >= 0x100))
               ? 0
               : (int)(_current_locale.ctype_cmpt_ptr->wctype_map_ptr[c] &
                       0x200);
}

#endif // WCTYPE_H
