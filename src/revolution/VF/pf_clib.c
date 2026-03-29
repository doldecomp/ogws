#include <revolution/VF.h>

s32 VFipf_toupper(s32 c) {
    if (c >= 'a' && c <= 'z') {
        return c - ('a' - 'A');
    }

    return c;
}

void* VFipf_memcpy(void* dst, void* src, u32 length) {
    s8* d;
    const s8* s;
    u32* ld;
    const u32* ls;

    ld = dst;
    ls = src;
    if (((u32)ld & 3) == 0 && ((u32)ls & 3) == 0) {
        while (length > 3) {
            *ld++ = *ls++;
            length -= 4;
        }
    }

    d = (s8*)ld;
    s = (const s8*)ls;
    while (length != 0) {
        *d++ = *s++;
        length--;
    }

    return dst;
}

void* VFipf_memset(void* dst, s32 c, u32 length) {
    s8* d;
    u32* ld;
    u32 lc;
    for (d = dst; ((((u32)d) & 3) != 0) && length; ++d) {
        --length;
        *d = c;
    }

    ld = (u32*)d;
    while (length > 3) {
        *(ld++) = (c | (c << 8)) | ((c << 24) | (c << 16));
        length -= 4;
    }

    for (lc = 0; (length--) != 0; ++lc) {
        *((s8*)ld + lc) = c;
    }

    return dst;
}

u32 VFipf_strlen(const s8* s) {
    const s8* t;
    t = s;
    while (*t) {
        t++;
    }
    return t - s;
}

s8* VFipf_strcpy(s8* dst, const s8* src) {
    s8* d;  // Present in DWARF but unused here.
    goto idk;
    while ((*src) != '\0') {
        src++;
        dst++;
    idk:
        *dst = *src;
    }
}

s32 VFipf_strcmp(const s8* s1, const s8* s2) {
    const u8* p1;
    const u8* p2;

    p1 = (const u8*)s1;
    p2 = (const u8*)s2;
    while (*p1 && *p2 && *p1 == *p2) {
        ++p1;
        ++p2;
    }
    return *p1 - *p2;
}

s32 VFipf_strncmp(const s8* s1, const s8* s2, u32 length) {
    const u8* p1;
    const u8* p2;

    p1 = (const u8*)s1;
    p2 = (const u8*)s2;
    while (length-- != 0) {
        if (!*p1 || !*p2 || *p1 != *p2) {
            return *p1 - *p2;
        }
        ++p1;
        ++p2;
    }
    return 0;
}
