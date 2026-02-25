#include <revolution/VF.h>

int VFiPFCODE_CP932_OEM2Unicode(const char *src, wchar_t *dst) {
    u8 hi;
    u8 lo;
    int row;
    int col;

    lo = (u8)src[0];
    hi = (u8)src[1];

    if (lo < 0x80) {
        *dst = lo;
        return VFiPFCODE_Combine_Width(1, 2);
    }

    if (lo >= 0xA1 && lo <= 0xDF) {
        *dst = lo + 0xFEC0;
        return VFiPFCODE_Combine_Width(1, 2);
    }

    if (lo == 0x80 || lo == 0x85 || lo == 0x86 || lo == 0xA0 || lo == 0xEB || lo == 0xEC || (lo >= 0xEF && lo <= 0xF9) || (lo >= 0xFD && lo == 0xFF)) {
        *dst = 0x5F;
        return VFiPFCODE_Combine_Width(1, 2);
    }

    if (hi >= 0xFD) {
        *dst = 0x5F;
        return VFiPFCODE_Combine_Width(1, 2);
    }

    if ((lo >= 0x81) && (lo <= 0x84)) {
        row = lo - 0x81;
    } else if ((lo >= 0x87) && (lo <= 0x9F)) {
        row = lo - 0x83;
    } else if ((lo >= 0xE0) && (lo <= 0xEA)) {
        row = lo - 0xC3;
    } else if ((lo >= 0xED) && (lo <= 0xEE)) {
        row = lo - 0xC5;
    } else if ((lo >= 0xFA) && (lo <= 0xFC)) {
        row = lo - 0xD0;
    } else {
        *dst = 0x5F;
        return VFiPFCODE_Combine_Width(1, 2);
    }

    col = hi - 0x40;
    if (col < 0 || col >= 189) {
        *dst = 0x5F;
        return VFiPFCODE_Combine_Width(1, 2);
    }

    *dst = cp932_to_unicode[row][col];
    if (*dst == 0) {
        *dst = 0x5F;
        return VFiPFCODE_Combine_Width(1, 2);
    }

    return VFiPFCODE_Combine_Width(2, 2);
}

int VFiPFCODE_CP932_Unicode2OEM(const wchar_t *src, u8 *dst) {
    u8 lo;
    u8 hi;
    int row;
    int col;
    u16 oem;
    const u16 *row_ptr;
    u16 uni;
    u16 temp;

    lo = *src & 0xFF;
    hi = *src >> 8;

    if ((lo < 0x80) && (hi == 0)) {
        dst[0] = (u8)lo;
        dst[1] = 0;
        return VFiPFCODE_Combine_Width(1, 2);
    }

    uni = (u16)((hi << 8) + lo);
    if ((0xFF61 <= uni) && (uni <= 0xFF9F)) {
        temp = (u16)(uni - 0xFEC0);
        dst[0] = (u8)(temp);
        dst[1] = 0;
        return VFiPFCODE_Combine_Width(1, 2);
    }

    if (uni == 0x5F) {
        dst[0] = 0x5F;
        return VFiPFCODE_Combine_Width(1, 2);
    }

    row = 0;
    while (row < 45) {
        row_ptr = cp932_to_unicode[row];
        col = 0;
        while (col < 189) {
            if (*row_ptr == uni) {
                break;
            }
            col++;
            row_ptr++;
        }
        if (col < 189) {
            break;
        }
        row++;
    }

    if (col == 189) {
        dst[0] = 0x5F;
        return VFiPFCODE_Combine_Width(1, 2);
    }

    if ((row >= 0) && (row <= 3)) {
        oem = ((row + 0x81) << 8) | (col + 0x40);
    } else if ((row >= 4) && (row <= 0x1C)) {
        oem = ((row + 0x83) << 8) | (col + 0x40);
    } else if ((row >= 0x1D) && (row <= 0x27)) {
        oem = ((row + 0xC3) << 8) | (col + 0x40);
    } else if ((row >= 0x28) && (row <= 0x29)) {
        oem = ((row + 0xC5) << 8) | (col + 0x40);
    } else if ((row >= 0x2A) && (row <= 0x2C)) {
        oem = ((row + 0xD0) << 8) | (col + 0x40);
    } else {
        dst[0] = 0x5F;
        return VFiPFCODE_Combine_Width(1, 2);
    }

    dst[1] = (u8)(oem & 0xFF);
    dst[0] = (oem >> 8) & 0xFF;
    return VFiPFCODE_Combine_Width(2, 2);
}

int VFiPFCODE_CP932_OEMCharWidth(const char* buf) {
    wchar_t temp_uni;
    int packed_width;
    s16 oem_width;
    s16 uni_width;

    packed_width = VFiPFCODE_CP932_OEM2Unicode(buf, &temp_uni);
    VFiPFCODE_Divide_Width(packed_width, &oem_width, &uni_width);
    return oem_width;
}

BOOL VFiPFCODE_CP932_isOEMMBchar(char code, u32 type) {
    u8 c = (u8)code;
    BOOL is_mb = FALSE;

    switch (type) {
        case 1:
            is_mb = FALSE;
            if ((c >= 0x81 && c <= 0x9F) || (c >= 0xE0 && c <= 0xFC)) {
                is_mb = TRUE;
            }
            return is_mb;

        case 2:
            is_mb = FALSE;
            if ((c >= 0x40 && c <= 0x7E) || (c >= 0x80 && c <= 0xFC)) {
                is_mb = TRUE;
            }
            return is_mb;
    }
    return is_mb;
}

s32 VFiPFCODE_CP932_UnicodeCharWidth(const wchar_t* src) {
    // Structure preserves stack layout used in the original assembly
    struct {
        s16 uni_width;    // Offset 0
        s16 oem_width;    // Offset 2
        u8 temp_buf[2];   // Offset 4 (Buffer for Unicode2OEM output)
    } vars;

    VFiPFCODE_Divide_Width(
        VFiPFCODE_CP932_Unicode2OEM(src, vars.temp_buf),
        &vars.oem_width,
        &vars.uni_width
    );

    return vars.uni_width;
}

u32 VFiPFCODE_CP932_isUnicodeMBchar(void) {
    return 0;
}
