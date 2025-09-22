#include "wstring.h"

size_t wcslen(const wchar_t* s) {
    const wchar_t* ptr = s - 1;
    size_t length = (size_t)-1;
    wchar_t current_char;

    do {
        current_char = *++ptr;
        length++;
    } while (current_char != 0);

    return length;
}

wchar_t* wcscpy(wchar_t* dst, const wchar_t* src) {
    wchar_t* original_dst = dst;
    const wchar_t* p_src = src - 1;
    wchar_t* p_dst = dst - 1;
    wchar_t current_char;

    do {
        current_char = *++p_src;
        *++p_dst = current_char;
    } while (current_char != 0);

    return original_dst;
}

wchar_t* wcsncpy(wchar_t* dst, const wchar_t* src, unsigned long n) {
    wchar_t* original_dst = dst;
    const wchar_t* p_src = src - 1;
    wchar_t* p_dst = dst - 1;
    unsigned long count = n + 1;
    wchar_t current_char;

    while (--count != 0) {
        current_char = *++p_src;
        *++p_dst = current_char;

        if (current_char == 0) {
            while (--count != 0) {
                *++p_dst = 0;
            }
            goto exit_func;
        }
    }

exit_func:
    return original_dst;
}

wchar_t* wcscat(wchar_t* dst, const wchar_t* src) {
    const wchar_t* p_src = src - 1;
    wchar_t* p_dst = dst - 1;
    wchar_t* original_dst = dst;
    wchar_t current_char;
    do {
        current_char = *++p_dst;
    } while (current_char != 0);

    p_dst--;

    do {
        current_char = *++p_src;
        *++p_dst = current_char;
    } while (current_char != 0);
    return original_dst;
}

int wcscmp(const wchar_t* s1, const wchar_t* s2) {
    unsigned int c1;
    wchar_t c2;
    const wchar_t* p1 = s1 - 1;
    const wchar_t* p2 = s2 - 1;

    goto load_s1_entry;

null_check:
    if (c1 == 0) {
        return 0;
    }

load_s1_entry:
    c1 = (unsigned int)(*++p1);
    c2 = *++p2;

    if (c1 == (unsigned int)c2) {
        goto null_check;
    } else {
        return (int)(c1 - (unsigned int)c2);
    }
}

wchar_t* wcschr(const wchar_t* s, wchar_t c) {
    const wchar_t* ptr = s - 1;
    wchar_t current_char;
    goto load_entry;

compare_check:
    if (current_char == c) {
        return (wchar_t*)ptr;
    }

load_entry:
    current_char = *++ptr;

    if (current_char != 0) {
        goto compare_check;
    }

    if (c == 0) {
        return (wchar_t*)ptr;
    }

    return NULL;
}
