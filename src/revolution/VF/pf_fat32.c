#include <revolution/VF.h>

s32 VFiPFSEC_ReadFAT(struct PF_VOLUME* p_vol, u8* p_buf, u32 sector, u16 offset, u16 size);
s32 VFiPFCACHE_ReadFATPage(struct PF_VOLUME* p_vol, u32 sector, struct PF_CACHE_PAGE** pp_page);
s32 VFiPFFAT_UpdateFATEntry(struct PF_VOLUME* p_vol, struct PF_CACHE_PAGE* p_page);
s32 VFiPFSEC_WriteFAT(struct PF_VOLUME* p_vol, const u8* p_buf, u32 sector, u16 offset, u16 size);
s32 VFiPFCACHE_UpdateModifiedSector(struct PF_CACHE_PAGE* p_page);

s32 VFiPFFAT32_ReadFATEntry(struct PF_VOLUME* p_vol, u32 cluster, u32* p_value) {
    u32 fat_offset;
    u32 fat_sector;
    u16 offset_in_sector;
    u8 buf[4];
    s32 err;
    u32 current_fat;
    s32 result;
    u32 tmp;

    if (!p_vol) {
        *p_value = -1;
        return 10;
    }

    if (!((cluster >= 2) && (cluster < p_vol->bpb.num_clusters + 2)) && (cluster != 0) && (cluster != 1)) {
        *p_value = -1;
        return 14;
    }

    fat_offset = cluster << 2;
    current_fat = 1;

    fat_sector = (u16)(p_vol->bpb.active_FAT_sector + (fat_offset >> p_vol->bpb.log2_bytes_per_sector));
    offset_in_sector = fat_offset & (p_vol->bpb.bytes_per_sector - 1);

    if ((p_vol->bpb.ext_flags & 0x80) == 0) {
        current_fat = 1;
    } else {
        current_fat = p_vol->bpb.ext_flags & 7;
    }

    do {
        err = VFiPFSEC_ReadFAT(p_vol, buf, fat_sector, offset_in_sector, 4);

        if (err != 0x1000 || p_vol->p_callback == 0) {
            goto check;
        }

        result = ((s32 (*)(s32))p_vol->p_callback)(p_vol->last_driver_error);
        if (result != 0) {
            if (result == 1 && p_vol->bpb.num_active_FATs >= 2 && current_fat < p_vol->bpb.num_active_FATs) {
                current_fat++;
                fat_sector += p_vol->bpb.sectors_per_FAT;
            } else {
            check:;
                if (err != 0) {
                    *p_value = -1;
                    return err;
                }
            }
        }
    } while (err != 0);

    tmp = *(u32*)buf;
    err = 0;
    tmp = SWAP32(tmp);
    *p_value = tmp & 0x0FFFFFFF;

    return err;
}

s32 VFiPFFAT32_ReadFATEntryPage(struct PF_VOLUME* p_vol, u32 cluster, u32* p_value, struct PF_CACHE_PAGE** pp_page) {
    s32 err;
    u32 offset;
    u32 sector;
    u32 current_fat;
    s32 result;
    u32 tmp;

    err = 0;
    if (!p_vol) {
        return 10;
    }

    if (!((cluster >= 2) && (cluster < p_vol->bpb.num_clusters + 2)) && (cluster != 0) && (cluster != 1)) {
        return 14;
    }

    offset = cluster << 2;
    sector = (u16)(p_vol->bpb.active_FAT_sector + (offset >> p_vol->bpb.log2_bytes_per_sector));

    if ((p_vol->bpb.ext_flags & 0x80) == 0) {
        current_fat = 1;
    } else {
        current_fat = (p_vol->bpb.ext_flags) & 7;
    }

    if ((*pp_page)->sector > sector || (*pp_page)->sector + p_vol->cache.fat_buff_size <= sector) {
        if ((*pp_page)->option == 1) {
            err = VFiPFFAT_UpdateFATEntry(p_vol, *pp_page);
            if (err != 0) {
                return err;
            }
        }

        do {
            err = VFiPFCACHE_ReadFATPage(p_vol, sector, pp_page);
            if (err != 0x1000 || p_vol->p_callback == 0) {
                goto check;
            }

            result = ((s32 (*)(s32))p_vol->p_callback)(p_vol->last_driver_error);
            if (result != 0) {
                if (result == 1 && p_vol->bpb.num_active_FATs >= 2 && current_fat < p_vol->bpb.num_active_FATs) {
                    current_fat++;
                    sector += p_vol->bpb.sectors_per_FAT;
                } else {
                check:;
                    if (err != 0) {
                        return err;
                    }
                }
            }
        } while (err != 0);

    } else {
        if (sector != (*pp_page)->sector + (((*pp_page)->p_buf - (*pp_page)->buffer) >> p_vol->bpb.log2_bytes_per_sector)) {
            (*pp_page)->p_buf += p_vol->bpb.bytes_per_sector;
        }
    }

    offset &= (p_vol->bpb.bytes_per_sector - 1);
    tmp = *((u32*)((*pp_page)->p_buf + offset));
    tmp = SWAP32(tmp);
    *p_value = tmp & 0x0FFFFFFF;

    return err;
}

s32 VFiPFFAT32_WriteFATEntry(struct PF_VOLUME* p_vol, u32 cluster, u32 value) {
    s32 err;
    u32 fat_offset;
    u32 fat_sector;
    u16 offset_in_sector;
    u8 buf[4];
    u32 dword;
    u32 tmp;

    if (!p_vol) {
        return 10;
    }

    if (!((cluster >= 2) && (cluster < p_vol->bpb.num_clusters + 2)) && (cluster != 0) && (cluster != 1)) {
        return 14;
    }

    fat_offset = cluster << 2;
    fat_sector = (u16)(p_vol->bpb.active_FAT_sector + (fat_offset >> p_vol->bpb.log2_bytes_per_sector));
    offset_in_sector = fat_offset & (p_vol->bpb.bytes_per_sector - 1);

    err = VFiPFSEC_ReadFAT(p_vol, buf, fat_sector, offset_in_sector, 4);
    switch (err) {
        case 0: {
            tmp = *(u32*)buf;
            tmp = SWAP32(tmp);
            tmp = (value & 0xFFFFFFF) | (tmp & 0xF0000000);
            tmp = SWAP32(tmp);
            *(u32*)buf = tmp;
            err = VFiPFSEC_WriteFAT(p_vol, buf, fat_sector, offset_in_sector, 4);
            break;
        }
        default:
            break;
    }

    return err;
}

s32 VFiPFFAT32_WriteFATEntryPage(struct PF_VOLUME* p_vol, u32 cluster, u32 value, struct PF_CACHE_PAGE** pp_page) {
    s32 err;
    u32 sector;
    u32 offset;
    u32 current_fat;
    s32 result;
    u32 tmp;

    err = 0;
    if (!p_vol) {
        return 10;
    }

    if (!((cluster >= 2) && (cluster < p_vol->bpb.num_clusters + 2)) && (cluster != 0) && (cluster != 1)) {
        return 14;
    }

    offset = cluster << 2;
    sector = (u16)(p_vol->bpb.active_FAT_sector + (offset >> p_vol->bpb.log2_bytes_per_sector));
    offset = (u16)(offset & (p_vol->bpb.bytes_per_sector - 1));

    if ((*pp_page)->sector > sector || (*pp_page)->sector + p_vol->cache.fat_buff_size <= sector) {
        err = VFiPFFAT_UpdateFATEntry(p_vol, *pp_page);
        if (err != 0) {
            return err;
        }

        if ((p_vol->bpb.ext_flags & 0x80) == 0) {
            current_fat = 1;
        } else {
            current_fat = (p_vol->bpb.ext_flags) & 7;
        }

        do {
            err = VFiPFCACHE_ReadFATPage(p_vol, sector, pp_page);
            if (err != 0x1000 || p_vol->p_callback == 0) {
                goto check;
            }

            result = ((s32 (*)(s32))p_vol->p_callback)(p_vol->last_driver_error);
            if (result != 0) {
                if (result == 1 && p_vol->bpb.num_active_FATs >= 2 && current_fat < p_vol->bpb.num_active_FATs) {
                    current_fat++;
                    sector += p_vol->bpb.sectors_per_FAT;
                } else {
                check:;
                    if (err != 0) {
                        return err;
                    }
                }
            }
        } while (err != 0);

    } else {
        if (sector != (*pp_page)->sector + (((*pp_page)->p_buf - (*pp_page)->buffer) >> p_vol->bpb.log2_bytes_per_sector)) {
            (*pp_page)->p_buf += p_vol->bpb.bytes_per_sector;
        }
    }

    tmp = *(u32*)((*pp_page)->p_buf + offset);
    tmp = SWAP32(tmp);
    tmp = (value & 0xFFFFFFF) | (tmp & 0xF0000000);
    tmp = SWAP32(tmp);
    *(u32*)((*pp_page)->p_buf + offset) = tmp;

    VFiPFCACHE_UpdateModifiedSector((*pp_page));

    return err;
}
