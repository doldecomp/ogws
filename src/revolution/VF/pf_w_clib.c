#include <revolution/VF.h>

size_t VFipf_w_strlen(const wchar_t* str) {
    const wchar_t* it = str;
    ptrdiff_t diff;

    // Find end of string
    while (*it != L'\0') {
        it++;
    }

    // Calculate size
    diff = (uintptr_t)it - (uintptr_t)str;
    return diff >> 1;
}

int VFipf_w_strcpy(wchar_t* dest, const wchar_t* src) {
    // Unconditional jump to the middle of the loop
    goto jump;
    while (*src != L'\0') {
        src++;
        dest++;
    jump:
        *dest = *src;
    }
}

int VFipf_w_strncmp(const wchar_t* s1, const wchar_t* s2, size_t n) {
    while (n != 0) {
        if (*s1 == L'\0' || *s2 == L'\0' || *s1 != *s2) {
            return (int)(*s1 - *s2);
        }

        s1++;
        s2++;
        n--;
    }
    return 0;
}
