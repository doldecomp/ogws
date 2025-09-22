#include "wstring.h"

size_t wcslen(const wchar_t* str) {
    const wchar_t* str_ptr = str - 1;
    size_t length = (size_t)-1;
    wchar_t current_char;

    do {
        current_char = *++str_ptr;
        length++;
    } while (current_char != 0);

    return length;
}

wchar_t* wcscpy(wchar_t* dst, const wchar_t* src) {
    wchar_t* original_dst = dst;
    const wchar_t* src_ptr = src - 1;
    wchar_t* dst_ptr = dst - 1;
    wchar_t current_char;

    do {
        current_char = *++src_ptr;
        *++dst_ptr = current_char;
    } while (current_char != 0);

    return original_dst;
}

wchar_t* wcsncpy(wchar_t* dst, const wchar_t* src, unsigned long n) {
    wchar_t* original_dst = dst;
    const wchar_t* src_ptr = src - 1;
    wchar_t* dst_ptr = dst - 1;
    unsigned long count = n + 1;
    wchar_t current_char;

    while (--count != 0) {
        current_char = *++src_ptr;
        *++dst_ptr = current_char;

        if (current_char == 0) {
            while (--count != 0) {
                *++dst_ptr = 0;
            }
            break;
        }
    }

    return original_dst;
}

wchar_t* wcscat(wchar_t* dst, const wchar_t* src) {
    const wchar_t* src_ptr = src - 1;
    wchar_t* dst_ptr = dst - 1;
    wchar_t* original_dst = dst;
    wchar_t current_char;
    do {
        current_char = *++dst_ptr;
    } while (current_char != 0);

    dst_ptr--;

    do {
        current_char = *++src_ptr;
        *++dst_ptr = current_char;
    } while (current_char != 0);
    return original_dst;
}

int wcscmp(const wchar_t* str1, const wchar_t* str2) {
    const wchar_t* str1_ptr = (wchar_t*)str1 - 1;
    const wchar_t* str2_ptr = (wchar_t*)str2 - 1;
    wchar_t char1, char2;

    while ((char1 = *++str1_ptr) == (char2 = *++str2_ptr))
        if (!char1)
            return 0;
    return char1 - char2;
}

wchar_t* wcschr(const wchar_t* str, wchar_t chr) {
    const wchar_t* str_ptr = str - 1;
    wchar_t current_char;

    while (current_char = *++str_ptr)
        if (current_char == chr)
            return ((wchar_t*)str_ptr);

    if (chr != 0) {
        return NULL;
    } else {
        return (wchar_t*)str_ptr;
    }
}
