#include <revolution/VF.h>

void VFipdm_bpb_calculate_common_bpb_fields(VF_BPB *bpb) {
    u32 temp;
    u32 root_secs;
    u32 data_secs;

    bpb->bps_shift = 0;
    temp = bpb->bytes_per_sec;
    while ((temp = (temp >> 1) & 0x7FFF) != 0) {
        bpb->bps_shift++;
    }

    bpb->spc_shift = 0;
    temp = bpb->sec_per_clus;
    while ((temp = (temp >> 1) & 0x7FFF) != 0) {
        bpb->spc_shift++;
    }

    root_secs = ((bpb->bytes_per_sec + (bpb->root_ent_cnt * 32)) - 1) >> bpb->bps_shift;
    bpb->root_dir_secs = root_secs;

    root_secs = ((u16)root_secs + bpb->rsvd_sec_cnt) + (bpb->num_fats * bpb->fat_sz);
    bpb->data_start_sec = root_secs;

    data_secs = bpb->total_sectors - root_secs; 
    bpb->count_of_clusters = data_secs >> bpb->spc_shift;

    if ((data_secs >> bpb->spc_shift) < 0xFF5) {
        bpb->fat_type = VF_FAT_TYPE_FAT12;
    } else if ((data_secs >> bpb->spc_shift) < 0xFFF5) {
        bpb->fat_type = VF_FAT_TYPE_FAT16;
    } else {
        bpb->fat_type = VF_FAT_TYPE_FAT32;
    }
}

static void VFipdm_bpb_calculate_specific_bpb_fields(VF_BPB *dst) {
    switch ((s32)dst->fat_type) {
        case VF_FAT_TYPE_FAT12:
        case VF_FAT_TYPE_FAT16: {
            dst->fat1_start_sec = dst->rsvd_sec_cnt;
            dst->active_fats = dst->num_fats;
            dst->root_start_sec = dst->rsvd_sec_cnt + (dst->num_fats * dst->fat_sz);
        } break;
        case VF_FAT_TYPE_FAT32: {
            dst->root_start_sec = dst->data_start_sec + ((dst->root_cluster - 2) << dst->spc_shift);
            if (dst->ext_flags & 0x80) {
                dst->active_fats = 1;
                dst->fat1_start_sec = dst->rsvd_sec_cnt + ((dst->ext_flags & 0x7) * dst->fat_sz);
            } else {
                dst->active_fats = dst->num_fats;
                dst->fat1_start_sec = dst->rsvd_sec_cnt;
            }
        }
    }
}

static s32 VFipdm_bpb_load_string(const u8 *src, u32 length, u8 *dst) {
    u32 i;
    if (src == NULL || dst == NULL || length == 0) {
        return 1;
    }
    for (i = 0; i < length; ++i) {
        dst[i] = src[i];
    }
    return 0;
}

s32 VFipdm_bpb_get_bpb_information(const u8 *src, VF_BPB *dst) {
    s32 result;
    int i;

    if (src == 0 || dst == 0) {
        return 1;
    }

    result = 0;

    VFipdm_bpb_load_string(src, 3, dst->jump_boot);
    VFipdm_bpb_load_string(src + 3, 8, dst->oem_name);

    dst->bytes_per_sec = src[0xB] | (src[0xC] << 8);
    dst->sec_per_clus = src[0xD];
    dst->rsvd_sec_cnt = src[0xE] | (src[0xF] << 8);
    dst->num_fats = src[0x10];
    dst->root_ent_cnt = src[0x11] | (src[0x12] << 8);

    dst->tot_sec16 = src[0x13] | (src[0x14] << 8);
    dst->media = src[0x15];
    dst->fat_sz16 = src[0x16] | (src[0x17] << 8);
    dst->sec_per_trk = src[0x18] | (src[0x19] << 8);
    dst->num_heads = src[0x1A] | (src[0x1B] << 8);
    dst->hidden_sec = src[0x1C] | (src[0x1D] << 8) | (src[0x1E] << 16) | (src[0x1F] << 24);
    dst->tot_sec32 = src[0x20] | (src[0x21] << 8) | (src[0x22] << 16) | (src[0x23] << 24);

    dst->total_sectors = (dst->tot_sec16 == 0) ? dst->tot_sec32 : (u32)dst->tot_sec16;

    if (dst->fat_sz16 == 0) {
        int fat_sz32 = src[0x24] | (src[0x25] << 8) | (src[0x26] << 16) | (src[0x27] << 24);
        dst->fat_sz = (dst->root_cluster_copy = fat_sz32);
    } else {
        dst->fat_sz = dst->fat_sz16;
        dst->root_cluster_copy = 0;
    }

    VFipdm_bpb_calculate_common_bpb_fields(dst);

    switch ((s32)dst->fat_type) {
        case VF_FAT_TYPE_FAT12:
        case VF_FAT_TYPE_FAT16: {
            if (dst->fat_sz16 == 0) {
                result = 4;
            }

            dst->ext_flags = 0;
            dst->fs_ver = 0;
            dst->root_cluster = 0;
            dst->fs_info = 0;
            dst->bk_boot_sec = 0;

            dst->drv_num = src[0x24];
            dst->boot_sig = src[0x26];
            dst->vol_id = src[0x27] | (src[0x28] << 8) | (src[0x29] << 16) | (src[0x2A] << 24);

            VFipdm_bpb_load_string(src + 0x2b, 11, dst->vol_lab);
            VFipdm_bpb_load_string(src + 0x36, 8, dst->fil_sys_type);
        } break;
        case VF_FAT_TYPE_FAT32: {
            if (dst->tot_sec16 != 0 || dst->fat_sz16 != 0) {
                result = 4;
            }

            dst->ext_flags = src[0x28] | (src[0x29] << 8);
            dst->fs_ver = src[0x2A] | (src[0x2B] << 8);
            dst->root_cluster = src[0x2C] | (src[0x2D] << 8) | (src[0x2E] << 16) | (src[0x2F] << 24);
            dst->fs_info = (src[0x31] << 8) | src[0x30];
            dst->bk_boot_sec = (src[0x33] << 8) | src[0x32];

            dst->drv_num = src[0x40];
            dst->boot_sig = src[0x42];
            dst->vol_id = src[0x43] | (src[0x44] << 8) | (src[0x45] << 16) | (src[0x46] << 24);

            VFipdm_bpb_load_string(src + 0x47, 11, dst->vol_lab);
            VFipdm_bpb_load_string(src + 0x52, 8, dst->fil_sys_type);

            if (dst->fs_ver != 0) {
                result = 4;
            }
        } break;
        default:
            result = 4;
    }

    VFipdm_bpb_calculate_specific_bpb_fields(dst);

    return result;
}

s32 VFipdm_bpb_get_fsinfo_information(const u8 *src, u32 *dst) {
    if ((src == NULL) || (dst == NULL)) {
        return 1;
    }

    dst[0] = src[0x1E8] | (src[0x1E9] << 8) | (src[0x1EA] << 16) | (src[0x1EB] << 24);
    dst[1] = src[0x1EC] | (src[0x1ED] << 8) | (src[0x1EE] << 16) | (src[0x1EF] << 24);

    return 0;
}

s32 VFipdm_bpb_set_fsinfo_information(const u32 *src, u8 *dst) {
    if (dst == NULL || src == NULL) {
        return 1;
    }

    dst[0] = 0x52;
    dst[1] = 0x52;
    dst[2] = 0x61;
    dst[3] = 0x41;
    dst[0x1E4] = 0x72;
    dst[0x1E5] = 0x72;
    dst[0x1E6] = 0x41;
    dst[0x1E7] = 0x61;

    dst[0x1E8] = src[0];
    dst[0x1E9] = src[0] >> 8;
    dst[0x1EA] = src[0] >> 16;
    dst[0x1EB] = src[0] >> 24;

    dst[0x1EC] = src[1];
    dst[0x1ED] = src[1] >> 8;
    dst[0x1EE] = src[1] >> 16;
    dst[0x1EF] = src[1] >> 24;

    dst[0x1FC] = 0x00;
    dst[0x1FD] = 0x00;
    dst[0x1FE] = 0x55;
    dst[0x1FF] = 0xAA;

    return 0;
}

s32 VFipdm_bpb_check_boot_sector(const u8 *buf, u32 *is_boot) {
    u16 bps;
    u8 spc;
    u8 media;

    if (buf == NULL || is_boot == NULL) {
        return 1;
    }

    *is_boot = 1;

    if (buf[0] != 0xEB || buf[2] != 0x90) {
        if (buf[0] != 0xE9) {
            *is_boot = 0;
        }
    }

    if (buf[0x1FE] != 0x55 || buf[0x1FF] != 0xAA) {
        *is_boot = 0;
    }

    bps = (buf[0xC] << 8) | buf[0xB];
    if (bps != 512 && bps != 1024 && bps != 2048 && bps != 4096) {
        *is_boot = 0;
    }

    spc = buf[0xD];
    if (spc != 1 && spc != 2 && spc != 4 && spc != 8 && spc != 16 && spc != 32 && spc != 64 && spc != 128) {
        *is_boot = 0;
    }

    media = buf[0x15];
    if (media != 0xF0 && media != 0xF8 && media != 0xF9 && media != 0xFA && media != 0xFB && media != 0xFC && media != 0xFD && media != 0xFE && media != 0xFF) {
        *is_boot = 0;
    }

    return 0;
}

s32 VFipdm_bpb_check_fsinfo_sector(const u8 *buf, u32 *is_fsinfo) {
    u32 sig1;
    u32 sig2;
    u32 sig3;

    if (buf == NULL || is_fsinfo == NULL) {
        return 1;
    }

    sig1 = buf[0] | (buf[1] << 8) | (buf[2] << 16) | (buf[3] << 24);
    sig2 = buf[0x1E4] | (buf[0x1E5] << 8) | (buf[0x1E6] << 16) | (buf[0x1E7] << 24);
    sig3 = buf[0x1FC] | (buf[0x1FD] << 8) | (buf[0x1FE] << 16) | (buf[0x1FF] << 24);

    if (sig1 == 0x41615252 && sig2 == 0x61417272 && sig3 == 0xAA550000) {
        *is_fsinfo = 1;
    } else {
        *is_fsinfo = 0;
    }

    return 0;
}
