#include <revolution/VF.h>

struct PF_CACHE_PAGE* VFiPFCACHE_SearchDataCache(struct PF_VOLUME* p_vol, u32 sector);

s32 VFiPFSEC_ReadFAT(struct PF_VOLUME* p_vol, u8* p_buf, u32 sector, u16 offset, u16 size) {
    struct PF_CACHE_PAGE* p_page;
    s32 err;

    if (!p_vol) {
        return 10;
    }
    if (!p_buf) {
        return 10;
    }
    if (((p_vol->flags & 1) == 0) || !VFiPFDRV_IsInserted(p_vol)) {
        return 9;
    }
    err = VFiPFCACHE_ReadFATPage(p_vol, sector, &p_page);
    if (err) {
        return err;
    }

    VFipf_memcpy(p_buf, &p_page->p_buf[offset], size);
    return 0;
}

s32 VFiPFSEC_ReadData(struct PF_VOLUME* p_vol, u8* p_buf, u32 sector, u16 offset, u32 size, u32* p_success_size, u32 set_sig) {
    struct PF_CACHE_PAGE* p_page;
    u32 num_success;
    u32 num_sector;
    u32 adjust_sector;
    u32 rest_sector;
    s32 err;

    u32 cache_remaining_sectors;  // Extra variable. Not in DWARF.

    *p_success_size = 0;
    if (!p_vol) {
        return 10;
    }
    if (!p_buf) {
        return 10;
    }
    if (((p_vol->flags & 1) == 0) || !VFiPFDRV_IsInserted(p_vol)) {
        return 9;
    }
    if (offset != 0 || size < p_vol->bpb.bytes_per_sector) {
        err = VFiPFCACHE_ReadDataPage(p_vol, sector, &p_page, set_sig);
        if (err) {
            return err;
        }
        VFipf_memcpy(p_buf, &p_page->p_buf[offset], size);
        *p_success_size = size;
    } else if (offset == 0 && (size & (p_vol->bpb.bytes_per_sector - 1)) == 0) {
        err = VFiPFCACHE_ReadDataNumSector(p_vol, p_buf, sector, size >> p_vol->bpb.log2_bytes_per_sector, &num_success);
        if (err) {
            return err;
        }
        *p_success_size += num_success << p_vol->bpb.log2_bytes_per_sector;
        if (num_success != (size >> p_vol->bpb.log2_bytes_per_sector)) {
            return 17;
        }
    } else {
        if (offset == 0) {
            p_page = VFiPFCACHE_SearchDataCache(p_vol, sector);
            if (p_page) {
                cache_remaining_sectors = p_page->sector + p_page->size - sector;
                num_sector = size >> p_vol->bpb.log2_bytes_per_sector;
                if (cache_remaining_sectors <= num_sector) {
                    VFipf_memcpy(p_buf, p_page->p_buf, cache_remaining_sectors << p_vol->bpb.log2_bytes_per_sector);
                    *p_success_size += cache_remaining_sectors << p_vol->bpb.log2_bytes_per_sector;
                    sector += cache_remaining_sectors;
                    size -= cache_remaining_sectors << p_vol->bpb.log2_bytes_per_sector;
                } else {
                    if (cache_remaining_sectors > num_sector) {
                        VFipf_memcpy(p_buf, p_page->p_buf, size);
                        *p_success_size += size;
                        size = 0;
                    }
                }
            }
            if (size != 0) {
                num_sector = size >> p_vol->bpb.log2_bytes_per_sector;
                rest_sector = (sector + num_sector) % p_vol->cache.data_buff_size;
                if (num_sector > rest_sector) {
                    adjust_sector = num_sector - rest_sector;
                    err = VFiPFCACHE_ReadDataNumSector(p_vol, p_buf + *p_success_size, sector, adjust_sector, &num_success);
                    if (err) {
                        return err;
                    }
                    *p_success_size += num_success << p_vol->bpb.log2_bytes_per_sector;
                    if (num_success != adjust_sector) {
                        return 17;
                    }
                    sector += adjust_sector;
                    num_sector -= adjust_sector;
                }
                if (num_sector != 0) {
                    err = VFiPFCACHE_ReadDataPage(p_vol, sector, &p_page, set_sig);
                    if (err) {
                        return err;
                    }
                    VFipf_memcpy(p_buf + *p_success_size, p_page->p_buf, num_sector << p_vol->bpb.log2_bytes_per_sector);
                    *p_success_size += num_sector << p_vol->bpb.log2_bytes_per_sector;
                }
            }
            goto end;
        }
        return 10;
    }
end:
    return 0;
}

s32 VFiPFSEC_WriteFAT(struct PF_VOLUME* p_vol, const u8* p_buf, u32 sector, u16 offset, u16 size) {
    struct PF_CACHE_PAGE* p_page;
    s32 err;

    if (!p_vol) {
        return 10;
    }
    if (!p_buf) {
        return 10;
    }
    if ((p_vol->flags & 1) == 0 || !VFiPFDRV_IsInserted(p_vol) || VFiPFDRV_IsWProtected(p_vol)) {
        return 9;
    }
    err = VFiPFCACHE_ReadFATPage(p_vol, sector, &p_page);
    if (err) {
        return err;
    }

    VFipf_memcpy(&p_page->p_buf[offset], (void*)p_buf, size);
    err = VFiPFCACHE_WriteFATPage(p_vol, p_page);
    if (err) {
        return err;
    }

    return 0;
}

s32 VFiPFSEC_WriteData(struct PF_VOLUME* p_vol, const u8* p_buf, u32 sector, u16 offset, u32 size, u32* p_success_size, u32 set_sig) {
    s32 err;
    struct PF_CACHE_PAGE* p_page;
    u32 num_success;
    u32 num_sector;     // Present in DWARF but unused here.
    u32 adjust_sector;  // Present in DWARF but unused here.
    u32 rest_sector;    // Present in DWARF but unused here.

    *p_success_size = 0;

    if (!p_vol) {
        return 10;
    }
    if (!p_buf) {
        return 10;
    }
    if (((p_vol->flags & 1) == 0) || !VFiPFDRV_IsInserted(p_vol) || VFiPFDRV_IsWProtected(p_vol)) {
        return 9;
    }
    if (offset != 0 || size < p_vol->bpb.bytes_per_sector) {
        err = VFiPFCACHE_ReadDataPageAndFlushIfNeeded(p_vol, sector, &p_page, set_sig);
        if (err) {
            return err;
        }

        VFipf_memcpy(&p_page->p_buf[offset], (void*)p_buf, size);

        err = VFiPFCACHE_WriteDataPage(p_vol, p_page, set_sig);
        if (err) {
            return err;
        }
        *p_success_size = size;
    } else {
        if ((offset == 0) && ((size & (p_vol->bpb.bytes_per_sector - 1)) == 0)) {
            err = VFiPFCACHE_WriteDataNumSectorAndFreeIfNeeded(p_vol, p_buf, sector, size >> p_vol->bpb.log2_bytes_per_sector, &num_success);
            if (err) {
                return err;
            }

            *p_success_size = num_success << p_vol->bpb.log2_bytes_per_sector;
            if (num_success != (size >> p_vol->bpb.log2_bytes_per_sector)) {
                return 17;
            }
        } else {
            if (offset == 0) {
                u32 num_sector = size >> p_vol->bpb.log2_bytes_per_sector;
                u32 rest_sector = (sector + num_sector) % p_vol->cache.data_buff_size;

                if (num_sector > rest_sector) {
                    u32 adjust_sector = num_sector - rest_sector;
                    err = VFiPFCACHE_WriteDataNumSectorAndFreeIfNeeded(p_vol, p_buf, sector, adjust_sector, &num_success);
                    if (err) {
                        return err;
                    }

                    *p_success_size = num_success << p_vol->bpb.log2_bytes_per_sector;

                    if (num_success != adjust_sector) {
                        return 17;
                    }

                    sector += adjust_sector;
                    num_sector -= adjust_sector;
                }

                if (num_sector != 0) {
                    err = VFiPFCACHE_ReadDataPageAndFlushIfNeeded(p_vol, sector, &p_page, set_sig);
                    if (err) {
                        return err;
                    }

                    VFipf_memcpy(p_page->p_buf, (void*)(p_buf + *p_success_size), num_sector << p_vol->bpb.log2_bytes_per_sector);

                    err = VFiPFCACHE_WriteDataPage(p_vol, p_page, set_sig);
                    if (err) {
                        return err;
                    }

                    *p_success_size += num_sector << p_vol->bpb.log2_bytes_per_sector;
                }
                goto end;
            }
            return 10;
        }
    }
end:
    return 0;
}
