#include <revolution/VF.h>

long VFiPFSEC_ReadFAT(struct PF_VOLUME* p_vol, unsigned char* p_buf, unsigned long sector, unsigned short offset, unsigned short size);
long VFiPFCACHE_ReadFATPage(struct PF_VOLUME* p_vol, unsigned long sector, struct PF_CACHE_PAGE** pp_page);
long VFiPFFAT_UpdateFATEntry(struct PF_VOLUME* p_vol, struct PF_CACHE_PAGE* p_page);
long VFiPFSEC_WriteFAT(struct PF_VOLUME* p_vol, const unsigned char* p_buf, unsigned long sector, unsigned short offset, unsigned short size);
long VFiPFCACHE_UpdateModifiedSector(struct PF_CACHE_PAGE* p_page);

long VFiPFFAT32_ReadFATEntry(struct PF_VOLUME* p_vol, unsigned long cluster, unsigned long* p_value) {
    unsigned long fat_offset;
    unsigned long fat_sector;
    unsigned short offset_in_sector;
    unsigned char buf[4];
    long err;
    unsigned long current_fat;
    long result;
    unsigned long tmp;

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

        result = ((long (*)(long))p_vol->p_callback)(p_vol->last_driver_error);
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

    tmp = *(unsigned long*)buf;
    err = 0;
    tmp = SWAP32(tmp);
    *p_value = tmp & 0x0FFFFFFF;

    return err;
}

long VFiPFFAT32_ReadFATEntryPage(struct PF_VOLUME* p_vol, unsigned long cluster, unsigned long* p_value, struct PF_CACHE_PAGE** pp_page) {
    long err;
    unsigned long offset;
    unsigned long sector;
    unsigned long current_fat;
    long result;
    unsigned long tmp;

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

            result = ((long (*)(long))p_vol->p_callback)(p_vol->last_driver_error);
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
    tmp = *((unsigned long*)((*pp_page)->p_buf + offset));
    tmp = SWAP32(tmp);
    *p_value = tmp & 0x0FFFFFFF;

    return err;
}

long VFiPFFAT32_WriteFATEntry(struct PF_VOLUME* p_vol, unsigned long cluster, unsigned long value) {
    long err;
    unsigned long fat_offset;
    unsigned long fat_sector;
    unsigned short offset_in_sector;
    unsigned char buf[4];
    unsigned long dword;
    unsigned long tmp;

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
            tmp = *(unsigned long*)buf;
            tmp = SWAP32(tmp);
            tmp = (value & 0xFFFFFFF) | (tmp & 0xF0000000);
            tmp = SWAP32(tmp);
            *(unsigned long*)buf = tmp;
            err = VFiPFSEC_WriteFAT(p_vol, buf, fat_sector, offset_in_sector, 4);
            break;
        }
        default:
            break;
    }

    return err;
}

long VFiPFFAT32_WriteFATEntryPage(struct PF_VOLUME* p_vol, unsigned long cluster, unsigned long value, struct PF_CACHE_PAGE** pp_page) {
    long err;
    unsigned long sector;
    unsigned long offset;
    unsigned long current_fat;
    long result;
    unsigned long tmp;

    err = 0;
    if (!p_vol) {
        return 10;
    }

    if (!((cluster >= 2) && (cluster < p_vol->bpb.num_clusters + 2)) && (cluster != 0) && (cluster != 1)) {
        return 14;
    }

    offset = cluster << 2;
    sector = (u16)(p_vol->bpb.active_FAT_sector + (offset >> p_vol->bpb.log2_bytes_per_sector));
    offset = (unsigned short)(offset & (p_vol->bpb.bytes_per_sector - 1));

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

            result = ((long (*)(long))p_vol->p_callback)(p_vol->last_driver_error);
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

    tmp = *(unsigned long*)((*pp_page)->p_buf + offset);
    tmp = SWAP32(tmp);
    tmp = (value & 0xFFFFFFF) | (tmp & 0xF0000000);
    tmp = SWAP32(tmp);
    *(unsigned long*)((*pp_page)->p_buf + offset) = tmp;

    VFiPFCACHE_UpdateModifiedSector((*pp_page));

    return err;
}
