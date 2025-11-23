#include <wmem.h>

wchar_t* wmemcpy(wchar_t* dest, const wchar_t* src, size_t n) {
    return (wchar_t*)memcpy(dest, src, n * sizeof(wchar_t));
}

wchar_t* wmemchr(wchar_t* s, wchar_t c, size_t n) {
    while (n) {
        if (*s == c) {
            return s;
        }

        s++;
        n--;
    }

    return NULL;
}
