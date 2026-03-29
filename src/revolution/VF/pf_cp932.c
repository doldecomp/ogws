#include <revolution/VF.h>

s32 VFiPFCODE_CP932_OEM2Unicode(const s8* cp932_src, u16* uc_dst) {
    u8 cp932_lead;
    u8 cp932_trail;
    s32 lead_index;
    s32 trail_index;

    cp932_lead = (u8)cp932_src[0];
    cp932_trail = (u8)cp932_src[1];

    if (cp932_lead < 0x80) {
        *uc_dst = cp932_lead;
        return VFiPFCODE_Combine_Width(1, 2);
    }

    if (cp932_lead >= 0xA1 && cp932_lead <= 0xDF) {
        *uc_dst = cp932_lead + 0xFEC0;
        return VFiPFCODE_Combine_Width(1, 2);
    }

    if (cp932_lead == 0x80 || cp932_lead == 0x85 || cp932_lead == 0x86 || cp932_lead == 0xA0 || cp932_lead == 0xEB || cp932_lead == 0xEC || (cp932_lead >= 0xEF && cp932_lead <= 0xF9) || (cp932_lead >= 0xFD && cp932_lead == 0xFF)) {
        *uc_dst = 0x5F;
        return VFiPFCODE_Combine_Width(1, 2);
    }

    if (cp932_trail >= 0xFD) {
        *uc_dst = 0x5F;
        return VFiPFCODE_Combine_Width(1, 2);
    }

    if ((cp932_lead >= 0x81) && (cp932_lead <= 0x84)) {
        lead_index = cp932_lead - 0x81;
    } else if ((cp932_lead >= 0x87) && (cp932_lead <= 0x9F)) {
        lead_index = cp932_lead - 0x83;
    } else if ((cp932_lead >= 0xE0) && (cp932_lead <= 0xEA)) {
        lead_index = cp932_lead - 0xC3;
    } else if ((cp932_lead >= 0xED) && (cp932_lead <= 0xEE)) {
        lead_index = cp932_lead - 0xC5;
    } else if ((cp932_lead >= 0xFA) && (cp932_lead <= 0xFC)) {
        lead_index = cp932_lead - 0xD0;
    } else {
        *uc_dst = 0x5F;
        return VFiPFCODE_Combine_Width(1, 2);
    }

    trail_index = cp932_trail - 0x40;
    if (trail_index < 0 || trail_index >= 189) {
        *uc_dst = 0x5F;
        return VFiPFCODE_Combine_Width(1, 2);
    }

    *uc_dst = cp932_to_unicode[lead_index][trail_index];
    if (*uc_dst == 0) {
        *uc_dst = 0x5F;
        return VFiPFCODE_Combine_Width(1, 2);
    }

    return VFiPFCODE_Combine_Width(2, 2);
}

s32 VFiPFCODE_CP932_Unicode2OEM(const u16* uc_src, s8* cp932_dst) {
    s32 i;
    s32 j;
    u16* p_table;
    u8 uc_lead;
    u8 uc_trail;
    u16 uc;
    u16 cp932;

    u16 temp;  // Extra variable. Not in DWARF.

    uc_lead = *uc_src & 0xFF;
    uc_trail = *uc_src >> 8;

    if ((uc_lead < 0x80) && (uc_trail == 0)) {
        cp932_dst[0] = (u8)uc_lead;
        cp932_dst[1] = 0;
        return VFiPFCODE_Combine_Width(1, 2);
    }

    uc = (u16)((uc_trail << 8) + uc_lead);
    if ((0xFF61 <= uc) && (uc <= 0xFF9F)) {
        temp = (u16)(uc - 0xFEC0);
        cp932_dst[0] = (u8)(temp);
        cp932_dst[1] = 0;
        return VFiPFCODE_Combine_Width(1, 2);
    }

    if (uc == 0x5F) {
        cp932_dst[0] = 0x5F;
        return VFiPFCODE_Combine_Width(1, 2);
    }

    i = 0;
    while (i < 45) {
        p_table = (u16*)cp932_to_unicode[i];
        j = 0;
        while (j < 189) {
            if (*p_table == uc) {
                break;
            }
            j++;
            p_table++;
        }
        if (j < 189) {
            break;
        }
        i++;
    }

    if (j == 189) {
        cp932_dst[0] = 0x5F;
        return VFiPFCODE_Combine_Width(1, 2);
    }

    if ((i >= 0) && (i <= 3)) {
        cp932 = ((i + 0x81) << 8) | (j + 0x40);
    } else if ((i >= 4) && (i <= 0x1C)) {
        cp932 = ((i + 0x83) << 8) | (j + 0x40);
    } else if ((i >= 0x1D) && (i <= 0x27)) {
        cp932 = ((i + 0xC3) << 8) | (j + 0x40);
    } else if ((i >= 0x28) && (i <= 0x29)) {
        cp932 = ((i + 0xC5) << 8) | (j + 0x40);
    } else if ((i >= 0x2A) && (i <= 0x2C)) {
        cp932 = ((i + 0xD0) << 8) | (j + 0x40);
    } else {
        cp932_dst[0] = 0x5F;
        return VFiPFCODE_Combine_Width(1, 2);
    }

    cp932_dst[1] = (u8)(cp932 & 0xFF);
    cp932_dst[0] = (cp932 >> 8) & 0xFF;
    return VFiPFCODE_Combine_Width(2, 2);
}

s32 VFiPFCODE_CP932_OEMCharWidth(const s8* buf) {
    u16 tmp;
    s32 width;
    s16 oem_width;
    s16 uni_width;

    width = VFiPFCODE_CP932_OEM2Unicode(buf, &tmp);
    VFiPFCODE_Divide_Width(width, &oem_width, &uni_width);
    return oem_width;
}

u32 VFiPFCODE_CP932_isOEMMBchar(s8 cp932, u32 num) {
    u8 code;
    u32 is_mb;

    code = (u8)cp932;
    is_mb = 0;

    switch (num) {
        case 1:
            is_mb = 0;
            if ((code >= 0x81 && code <= 0x9F) || (code >= 0xE0 && code <= 0xFC)) {
                is_mb = 1;
            }
            return is_mb;

        case 2:
            is_mb = 0;
            if ((code >= 0x40 && code <= 0x7E) || (code >= 0x80 && code <= 0xFC)) {
                is_mb = 1;
            }
            return is_mb;
    }
    return is_mb;
}

s32 VFiPFCODE_CP932_UnicodeCharWidth(const u16* buf) {
    s8 tmp[2];
    s32 width;
    s16 oem_width;
    s16 uni_width;

    width = VFiPFCODE_CP932_Unicode2OEM(buf, tmp);
    VFiPFCODE_Divide_Width(width, &oem_width, &uni_width);

    return uni_width;
}

u32 VFiPFCODE_CP932_isUnicodeMBchar(u16 uc_src, u32 num) {
    return 0;
}
