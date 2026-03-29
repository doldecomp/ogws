#include <revolution/VF.h>

#define PF_STR_CODEMODE_NONE 0
#define PF_STR_CODEMODE_OEM 1
#define PF_STR_CODEMODE_UNICODE 2
#define PF_STR_CODEMODE_LOCAL 3

extern PF_VOLUME_SET VFipf_vol_set;

void VFiPFSTR_SetCodeMode(struct PF_STR* p_str, u32 code_mode) {
    p_str->code_mode = code_mode;
}

u32 VFiPFSTR_GetCodeMode(struct PF_STR* p_str) {
    return p_str->code_mode;
}

void VFiPFSTR_SetLocalStr(struct PF_STR* p_str, s8* p_local) {
    if (p_str->code_mode == PF_STR_CODEMODE_OEM || (p_local == NULL)) {
        p_str->p_local = p_str->p_head;
    } else {
        p_str->p_local = p_local;
    }
}

s8* VFiPFSTR_GetStrPos(struct PF_STR* p_str, u32 target) {
    s8* p_pos;
    if (target == 1) {
        p_pos = (s8*)p_str->p_head;
    } else if (target == 2) {
        p_pos = (s8*)p_str->p_tail;
    } else {
        p_pos = (s8*)p_str->p_local;
    }

    return p_pos;
}

void VFiPFSTR_MoveStrPos(struct PF_STR* p_str, s16 num_char) {
    s16 cnt;
    s16 offset;
    s32 width;
    s8* p;
    u16* wp;

    offset = 0;

    if (VFiPFSTR_GetCodeMode(p_str) == PF_STR_CODEMODE_OEM) {
        p = (s8*)p_str->p_head;

        for (; num_char != 0; offset++, num_char--) {
            if (VFipf_vol_set.codeset.is_oem_mb_char(*p, PF_STR_CODEMODE_OEM)) {
                offset++;
            }
        }
    } else {
        wp = (u16*)p_str->p_head;

        for (cnt = 0; cnt < num_char; cnt++) {
            width = VFipf_vol_set.codeset.unicode_char_width((u16*)wp);
            wp += width;
            offset += (s16)width;
        }
    }

    p_str->p_head += offset;
}

s32 VFiPFSTR_InitStr(struct PF_STR* p_str, const s8* s, u32 code_mode) {
    if (p_str == NULL || s == NULL) {
        return 10;
    }

    if (code_mode == PF_STR_CODEMODE_OEM) {
        p_str->p_head = s;
        p_str->p_tail = s + VFipf_strlen(s);
    } else if (code_mode == PF_STR_CODEMODE_UNICODE) {
        p_str->p_head = s;
        p_str->p_tail = s + (2 * VFipf_w_strlen((const u16*)s));
    } else {
        return 10;
    }

    p_str->code_mode = code_mode;
    return 0;
}

u16 VFiPFSTR_StrLen(struct PF_STR* p_str) {
    return (u16)((u8*)p_str->p_tail - (u8*)p_str->p_head);
}

u16 VFiPFSTR_StrNumChar(struct PF_STR* p_str, u32 target) {
    s8* p;
    u16 cnt;
    s32 width;

    if (target == PF_STR_CODEMODE_OEM) {
        p = (s8*)p_str->p_head;
    } else {
        p = (s8*)p_str->p_tail;
    }

    if (p_str->code_mode == PF_STR_CODEMODE_OEM) {
        cnt = 0;
        for (; *p != '\0'; p++, cnt++) {
            if (VFipf_vol_set.codeset.is_oem_mb_char(*p, PF_STR_CODEMODE_OEM)) {
                p++;
            }
        }
    } else {
        cnt = 0;
        for (; p[0] != '\0' || p[1] != '\0'; p += width, cnt++) {
            width = VFipf_vol_set.codeset.unicode_char_width((u16*)p);
        }
    }

    return cnt;
}

s32 VFiPFSTR_StrCmp(const struct PF_STR* p_str, const s8* s) {
    u16 wc;
    const u16* wp;
    const s8* p1;  // Present in DWARF but unused here.
    const s8* p2;  // Present in DWARF but unused here.
    s32 ret;       // Present in DWARF but unused here.

    if (p_str->code_mode == PF_STR_CODEMODE_OEM) {
        return VFipf_strcmp(p_str->p_head, s);
    }

    wp = (const u16*)p_str->p_head;
    do {
        VFipf_vol_set.codeset.oem2unicode((s8*)s, &wc);
        s++;
    } while (*wp++ == wc && wp[-1] != L'\0' && wc != L'\0');

    return wp[-1] - wc;
}

s32 VFiPFSTR_StrNCmp(struct PF_STR* p_str, const s8* s, u32 target, s16 offset, u16 num) {
    u16 wc;
    const u16* wp;
    const s8* p1;
    const s8* p2;  // Present in DWARF but unused here.
    s32 ret;       // Present in DWARF but unused here.

    if (p_str->code_mode == PF_STR_CODEMODE_OEM || target == PF_STR_CODEMODE_LOCAL) {
        if (target == PF_STR_CODEMODE_OEM) {
            p1 = (const s8*)p_str->p_head + offset;
        } else if (target == PF_STR_CODEMODE_UNICODE) {
            p1 = (const s8*)p_str->p_tail + offset;
        } else {
            p1 = (const s8*)p_str->p_local + offset;
        }

        return VFipf_strncmp(p1, s, num);
    }

    if (target == PF_STR_CODEMODE_OEM) {
        wp = (const u16*)((u8*)p_str->p_head + offset * sizeof(u16));
    } else {
        wp = (const u16*)((u8*)p_str->p_tail + offset * sizeof(u16));
    }

    do {
        VFipf_vol_set.codeset.oem2unicode((s8*)s, &wc);
        s++;
        num--;
    } while (*wp++ == wc && num > 0 && wp[-1] != L'\0' && wc != L'\0');

    return wp[-1] - wc;
}

void VFiPFSTR_ToUpperNStr(struct PF_STR* p_str, u16 num, s8* dest) {
    u16 wc;
    const u16* wp;
    const s8* p;

    if (p_str->code_mode == PF_STR_CODEMODE_OEM) {
        for (p = p_str->p_head; num > 0 && *p != '\0'; p++, num--) {
            *dest++ = VFipf_toupper(*p);
        }
    } else {
        for (wp = (const u16*)p_str->p_head; num > 0 && *wp != L'\0'; num--, wp++) {
            wc = (*wp >= L'a' && *wp <= L'z') ? *wp - (L'a' - L'A') : *wp;
            dest[0] = (wc >> 0) & 0xFF;
            dest[1] = (wc >> 8) & 0xFF;
            dest += sizeof(u16);
        }

        *dest = '\0';
    }

    *dest = '\0';
}
