#include <revolution/VF.h>

s32 VFiPFFAT12_ReadFATEntry(struct PF_VOLUME* p_vol, u16 cluster, u32* p_value) {
    s32 err;
    u16 fat_offset;
    u16 fat_sector;
    u16 offset_in_sector;
    u16 word;
    u8 buf[2];
    u32 current_fat;
    s32 result;

    if (!p_vol) {
        *p_value = -1;
        return 10;
    }
    if (!((cluster >= 2) && (cluster < p_vol->bpb.num_clusters + 2)) && (cluster != 0) && (cluster != 1)) {
        *p_value = -1;
        return 14;
    }

    fat_offset = (u16)(cluster + (cluster >> 1));
    fat_sector = (u16)(p_vol->bpb.active_FAT_sector + (fat_offset >> p_vol->bpb.log2_bytes_per_sector));
    offset_in_sector = (u16)(fat_offset & (p_vol->bpb.bytes_per_sector - 1));

    if ((p_vol->bpb.ext_flags & 0x80) == 0) {
        current_fat = 1;
    } else {
        current_fat = (u32)(p_vol->bpb.ext_flags & 7);
    }

    do {
        if (offset_in_sector < p_vol->bpb.bytes_per_sector - 1) {
            err = VFiPFSEC_ReadFAT(p_vol, buf, fat_sector, offset_in_sector, 2);
        } else {
            err = VFiPFSEC_ReadFAT(p_vol, buf, fat_sector, offset_in_sector, 1);
            if (err == 0) {
                err = VFiPFSEC_ReadFAT(p_vol, &buf[1], fat_sector + 1, 0, 1);
            }
        }

        if (err == 0x1000 && p_vol->p_callback != 0) {
            result = ((s32 (*)(s32))p_vol->p_callback)(p_vol->last_driver_error);

            if (result == 0) {
                continue;
            }

            if (result == 1 && p_vol->bpb.num_active_FATs >= 2 && current_fat < (u32)p_vol->bpb.num_active_FATs) {
                current_fat++;
                fat_sector += (u16)p_vol->bpb.sectors_per_FAT;
                continue;
            }
        }

        if (err != 0) {
            *p_value = -1;
            return err;
        }
    } while (err != 0);

    word = *(u16*)buf;
    word = SWAP16(word);
    if ((cluster & 1) != 0) {
        *p_value = word >> 4;
    } else {
        *p_value = word & 0xFFF;
    }

    return 0;
}

s32 VFiPFFAT12_ReadFATEntryPage(struct PF_VOLUME* p_vol, u16 cluster, u32* p_value, struct PF_CACHE_PAGE** pp_page) {
    s32 err;
    u32 offset;
    u32 sector;
    u32 current_fat;
    s32 result;

    if (!p_vol) {
        return 10;
    }
    if (!((cluster >= 2) && (cluster < p_vol->bpb.num_clusters + 2)) && (cluster != 0) && (cluster != 1)) {
        return 14;
    }

    offset = (u16)(cluster + (cluster >> 1));
    sector = p_vol->bpb.active_FAT_sector + (offset >> p_vol->bpb.log2_bytes_per_sector) & 0xFFFF;

    if ((p_vol->bpb.ext_flags & 0x80) == 0) {
        current_fat = 1;
    } else {
        current_fat = (u32)(p_vol->bpb.ext_flags & 7);
    }

    err = 0;
    do {
        if (err == 0x1000 && p_vol->p_callback != 0) {
            result = ((s32 (*)(s32))p_vol->p_callback)(p_vol->last_driver_error);
            if (result == 0) {
                err = 0;
                continue;
            }
            if (result == 1 && p_vol->bpb.num_active_FATs >= 2 && current_fat < (u32)p_vol->bpb.num_active_FATs) {
                current_fat++;
                sector += p_vol->bpb.sectors_per_FAT;
                err = 0;
                continue;
            }

        } else {
            if ((*pp_page)->sector > sector || (*pp_page)->sector + p_vol->cache.fat_buff_size <= sector) {
                if ((*pp_page)->option == 1) {
                    err = VFiPFFAT_UpdateFATEntry(p_vol, *pp_page);
                    if (err != 0) {
                        return err;
                    }
                }

                err = VFiPFCACHE_ReadFATPage(p_vol, sector, pp_page);
                if (err != 0) {
                    continue;
                }
            } else {
                if (sector != (*pp_page)->sector + (((*pp_page)->p_buf - (*pp_page)->buffer) >> p_vol->bpb.log2_bytes_per_sector)) {
                    (*pp_page)->p_buf += p_vol->bpb.bytes_per_sector;
                }
            }

            offset &= (p_vol->bpb.bytes_per_sector - 1);

            if (offset == p_vol->bpb.bytes_per_sector - 1) {
                *p_value = (*pp_page)->p_buf[offset];
                sector++;

                if ((*pp_page)->sector > sector || (*pp_page)->sector + p_vol->cache.fat_buff_size <= sector) {
                    if ((*pp_page)->option == 1) {
                        err = VFiPFFAT_UpdateFATEntry(p_vol, *pp_page);
                        if (err != 0) {
                            return err;
                        }
                    }

                    err = VFiPFCACHE_ReadFATPage(p_vol, sector, pp_page);
                    if (err != 0) {
                        return err;
                    }
                } else {
                    if (sector != (*pp_page)->sector + (((*pp_page)->p_buf - (*pp_page)->buffer) >> p_vol->bpb.log2_bytes_per_sector)) {
                        (*pp_page)->p_buf += p_vol->bpb.bytes_per_sector;
                    }
                }

                *p_value += ((*pp_page)->p_buf[0] << 8);
            } else {
                *p_value = ((*pp_page)->p_buf[offset + 1] << 8) + (*pp_page)->p_buf[offset];
            }
        }
        break;
    } while (1);
    if (err != 0) {
        *p_value = -1;
        return err;
    }

    if ((cluster & 1) != 0) {
        *p_value >>= 4;
    } else {
        *p_value &= 0xFFF;
    }

    return 0;
}

s32 VFiPFFAT12_WriteFATEntry(struct PF_VOLUME* p_vol, u16 cluster, u16 value) {
    s32 err;
    u16 fat_offset;
    u16 fat_sector;
    u16 offset_in_sector;
    u16 fat_sector2;
    u16 offset_in_sector2;
    u16 word;
    u8 buf[2];

    if (!p_vol) {
        return 10;
    }
    if (!((cluster >= 2) && (cluster < p_vol->bpb.num_clusters + 2)) && (cluster != 0) && (cluster != 1)) {
        return 14;
    }

    fat_offset = (u16)(cluster + (cluster >> 1));
    fat_sector = (u16)(p_vol->bpb.active_FAT_sector + (fat_offset >> p_vol->bpb.log2_bytes_per_sector));
    offset_in_sector = (u16)(fat_offset & (p_vol->bpb.bytes_per_sector - 1));

    if ((cluster & 1) != 0) {
        err = VFiPFSEC_ReadFAT(p_vol, buf, fat_sector, offset_in_sector, 1);
        if (err != 0) {
            return err;
        }
        word = (u16)((value << 4) + (buf[0] & 0xF));
    } else {
        fat_sector2 = (u16)(p_vol->bpb.active_FAT_sector + ((fat_offset + 1) >> p_vol->bpb.log2_bytes_per_sector));
        offset_in_sector2 = (u16)((fat_offset + 1) & (p_vol->bpb.bytes_per_sector - 1));

        err = VFiPFSEC_ReadFAT(p_vol, buf, fat_sector2, offset_in_sector2, 1);
        if (err != 0) {
            return err;
        }
        word = (u16)(((buf[0] << 8) & 0xF000) + (value & 0xFFF));
    }

    *(u16*)buf = SWAP16(word);

    if (offset_in_sector < p_vol->bpb.bytes_per_sector - 1) {
        err = VFiPFSEC_WriteFAT(p_vol, buf, fat_sector, offset_in_sector, 2);
    } else {
        err = VFiPFSEC_WriteFAT(p_vol, buf, fat_sector, offset_in_sector, 1);
        if (err == 0) {
            err = VFiPFSEC_WriteFAT(p_vol, &buf[1], fat_sector + 1, 0, 1);
        }
    }

    return err;
}

s32 VFiPFFAT12_WriteFATEntryPage(struct PF_VOLUME* p_vol, u16 cluster, u16 value, struct PF_CACHE_PAGE** pp_page) {
    s32 err;
    u32 fat_offset;
    u32 fat_sector;
    u16 offset_in_sector;
    u32 current_fat;
    s32 result;

    err = 0;
    if (!p_vol) {
        return 10;
    }

    if (!((cluster >= 2) && (cluster < p_vol->bpb.num_clusters + 2)) && (cluster != 0) && (cluster != 1)) {
        return 14;
    }

    fat_offset = (u16)(cluster + (cluster >> 1));
    fat_sector = (u16)(p_vol->bpb.active_FAT_sector + (fat_offset >> p_vol->bpb.log2_bytes_per_sector));
    offset_in_sector = (u16)(fat_offset & (p_vol->bpb.bytes_per_sector - 1));

    if ((*pp_page)->sector > fat_sector || (*pp_page)->sector + p_vol->cache.fat_buff_size <= fat_sector) {
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
            err = VFiPFCACHE_ReadFATPage(p_vol, fat_sector, pp_page);
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
                        return err;
                    }
                }
            }
        } while (err != 0);

    } else {
        if (fat_sector != (*pp_page)->sector + (((*pp_page)->p_buf - (*pp_page)->buffer) >> p_vol->bpb.log2_bytes_per_sector)) {
            (*pp_page)->p_buf += p_vol->bpb.bytes_per_sector;
        }
    }

    if ((cluster & 1) != 0) {
        (*pp_page)->p_buf[offset_in_sector] = (u8)(((*pp_page)->p_buf[offset_in_sector] & 0x0F) | ((value << 4) & 0xF0));
        VFiPFCACHE_UpdateModifiedSector(*pp_page);

        if (offset_in_sector == (u32)(p_vol->bpb.bytes_per_sector - 1)) {
            if ((*pp_page)->sector > fat_sector + 1 || (*pp_page)->sector + p_vol->cache.fat_buff_size <= fat_sector + 1) {
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
                    err = VFiPFCACHE_ReadFATPage(p_vol, fat_sector + 1, pp_page);
                    if (err != 0x1000 || p_vol->p_callback == 0) {
                        goto check2;
                    }

                    result = ((long (*)(long))p_vol->p_callback)(p_vol->last_driver_error);
                    if (result != 0) {
                        if (result == 1 && p_vol->bpb.num_active_FATs >= 2 && current_fat < p_vol->bpb.num_active_FATs) {
                            current_fat++;
                            fat_sector += p_vol->bpb.sectors_per_FAT;
                        } else {
                        check2:;
                            if (err != 0) {
                                return err;
                            }
                        }
                    }
                } while (err != 0);

                VFiPFCACHE_UpdateModifiedSector(*pp_page);
            } else {
                if (fat_sector + 1 != (*pp_page)->sector + (((*pp_page)->p_buf - (*pp_page)->buffer) >> p_vol->bpb.log2_bytes_per_sector)) {
                    (*pp_page)->p_buf += p_vol->bpb.bytes_per_sector;
                    VFiPFCACHE_UpdateModifiedSector(*pp_page);
                }
            }

            (*pp_page)->p_buf[0] = (u8)(value >> 4);
        } else {
            (*pp_page)->p_buf[offset_in_sector + 1] = (u8)(value >> 4);
        }
    } else {
        (*pp_page)->p_buf[offset_in_sector] = (u8)value;
        VFiPFCACHE_UpdateModifiedSector(*pp_page);

        if (offset_in_sector == (u32)(p_vol->bpb.bytes_per_sector - 1)) {
            if ((*pp_page)->sector > fat_sector + 1 || (*pp_page)->sector + p_vol->cache.fat_buff_size <= fat_sector + 1) {
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
                    err = VFiPFCACHE_ReadFATPage(p_vol, fat_sector + 1, pp_page);
                    if (err != 0x1000 || p_vol->p_callback == 0) {
                        goto check3;
                    }

                    result = ((long (*)(long))p_vol->p_callback)(p_vol->last_driver_error);
                    if (result != 0) {
                        if (result == 1 && p_vol->bpb.num_active_FATs >= 2 && current_fat < p_vol->bpb.num_active_FATs) {
                            current_fat++;
                            fat_sector += p_vol->bpb.sectors_per_FAT;
                        } else {
                        check3:;
                            if (err != 0) {
                                return err;
                            }
                        }
                    }
                } while (err != 0);

                VFiPFCACHE_UpdateModifiedSector(*pp_page);
            } else {
                if (fat_sector + 1 != (*pp_page)->sector + (((*pp_page)->p_buf - (*pp_page)->buffer) >> p_vol->bpb.log2_bytes_per_sector)) {
                    (*pp_page)->p_buf += p_vol->bpb.bytes_per_sector;
                    VFiPFCACHE_UpdateModifiedSector(*pp_page);
                }
            }

            (*pp_page)->p_buf[0] = ((*pp_page)->p_buf[0] & 0xF0) | (u8)(value >> 8);
        } else {
            (*pp_page)->p_buf[offset_in_sector + 1] = (u8)((value >> 8) | ((*pp_page)->p_buf[offset_in_sector + 1] & 0xF0));
        }
    }

    return err;
}
