#include "locale.h"

inline int tolower_inline(int c) {
    return ((c < 0) || (c >= 0x100))
               ? c
               : (int)(_current_locale.ctype_cmpt_ptr->lower_map_ptr[c]);
}

int stricmp(const char* s1, const char* s2) {
    char c1, c2;

    while (1) {
        c1 = tolower_inline(*s1++);
        c2 = tolower_inline(*s2++);

        if (c1 < c2) {
            return -1;
        }

        if (c1 > c2) {
            return 1;
        }

        if (c1 == 0) {
            return 0;
        }
    }
}
