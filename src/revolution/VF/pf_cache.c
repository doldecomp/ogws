#include <revolution/VF.h>

s32 VFiPFCACHE_InitPageList(struct PF_VOLUME* p_vol, struct PF_CACHE_PAGE** pp_head, struct PF_CACHE_PAGE* pages, u8 (*buffers)[512], u16 num, u32 size, u32 is_fat) {
    u32 i;
    u32 bps_per_buf;

    *pp_head = pages;
    bps_per_buf = (p_vol->bpb.bytes_per_sector >> 9) * size;

    if (is_fat == 1 && num / bps_per_buf < 1 || !is_fat && num / bps_per_buf < 2) {
        return 30;
    }

    if (num / bps_per_buf == 1) {
        pages->p_prev = pages;
        pages->p_next = pages;
        pages->buffer = *buffers;
        pages->p_buf = *buffers;
        pages->p_mod_sbuf = 0;
        pages->p_mod_ebuf = 0;
        pages->size = size;
        pages->sector = -1;
        pages->option = 0;
        pages->signature = 0;
        pages->stat &= 0xFFFCu;
        if (is_fat) {
            pages->stat |= 4u;
        } else {
            pages->stat &= ~4u;
        }
        return 0;
    } else {
        pages->p_prev = &pages[num - num % bps_per_buf - bps_per_buf];
        pages->p_next = &pages[bps_per_buf];
        pages->buffer = *buffers;
        pages->p_buf = *buffers;
        pages->p_mod_sbuf = 0;
        pages->p_mod_ebuf = 0;
        pages->size = size;
        pages->sector = -1;
        pages->option = 0;
        pages->signature = 0;
        pages->stat &= 0xFFFCu;
        if (is_fat) {
            pages->stat |= 4u;
        } else {
            pages->stat &= ~4u;
        }

        for (i = bps_per_buf; i < num - num % bps_per_buf - bps_per_buf; i += bps_per_buf) {
            pages[i].p_prev = &pages[i - bps_per_buf];
            pages[i].p_next = &pages[i + bps_per_buf];
            pages[i].buffer = &(*buffers)[512 * i];
            pages[i].p_buf = &(*buffers)[512 * i];
            pages[i].p_mod_sbuf = 0;
            pages[i].p_mod_ebuf = 0;
            pages[i].size = size;
            pages[i].sector = -1;
            pages[i].option = 0;
            pages[i].signature = 0;
            pages[i].stat &= 0xFFFCu;
            if (is_fat) {
                pages[i].stat |= 4u;
            } else {
                pages[i].stat &= ~4u;
            }
        }

        pages[num - num % bps_per_buf - bps_per_buf].p_prev = &pages[num - num % bps_per_buf - bps_per_buf - bps_per_buf];
        pages[num - num % bps_per_buf - bps_per_buf].p_next = pages;
        pages[num - num % bps_per_buf - bps_per_buf].buffer = &(*buffers)[512 * (num - num % bps_per_buf - bps_per_buf)];
        pages[num - num % bps_per_buf - bps_per_buf].p_buf = &(*buffers)[512 * (num - num % bps_per_buf - bps_per_buf)];
        pages[num - num % bps_per_buf - bps_per_buf].p_mod_sbuf = 0;
        pages[num - num % bps_per_buf - bps_per_buf].p_mod_ebuf = 0;
        pages[num - num % bps_per_buf - bps_per_buf].size = size;
        pages[num - num % bps_per_buf - bps_per_buf].sector = -1;
        pages[num - num % bps_per_buf - bps_per_buf].option = 0;
        pages[num - num % bps_per_buf - bps_per_buf].signature = 0;
        pages[(num - (num % bps_per_buf)) - bps_per_buf].stat &= 0xFFFCu;
        if (is_fat) {
            pages[(num - (num % bps_per_buf)) - bps_per_buf].stat |= 4;
        } else {
            pages[(num - (num % bps_per_buf)) - bps_per_buf].stat &= (~0x4);
        }
        return 0;
    }
}

struct PF_CACHE_PAGE* VFiPFCACHE_SearchForPage(struct PF_VOLUME* p_vol, struct PF_CACHE_PAGE* p_head, u32 sector) {
    struct PF_CACHE_PAGE* p_page;

    if (sector == 0xFFFFFFFF) {
        return NULL;
    }

    if (!(p_head->stat & 1)) {
        return NULL;
    }

    if (p_head->sector <= sector && p_head->sector + p_head->size - 1 >= sector) {
        p_head->p_buf = p_head->buffer + ((sector - p_head->sector) << p_vol->bpb.log2_bytes_per_sector);
        return p_head;
    }

    p_page = p_head->p_next;
    while (p_page != p_head) {
        if (!(p_page->stat & 1)) {
            return NULL;
        }
        if (p_page->sector <= sector && p_page->sector + p_page->size - 1 >= sector) {
            p_page->p_buf = p_page->buffer + ((sector - p_page->sector) << p_vol->bpb.log2_bytes_per_sector);
            return p_page;
        }
        p_page = p_page->p_next;
    }

    return NULL;
}

static struct PF_CACHE_PAGE* VFiPFCACHE_SearchForUsedPage(struct PF_VOLUME* p_vol, struct PF_CACHE_PAGE** pp_head, struct PF_CACHE_PAGE* p_page) {
    struct PF_CACHE_PAGE* lp_page;

    if (!p_page) {
        lp_page = *pp_head;

    } else {
        lp_page = p_page->p_next;
        if (lp_page == *pp_head) {
            return 0;
        }
    }

    while ((lp_page->stat & 1) != 0) {
        if (lp_page->sector != -1) {
            lp_page->p_buf = lp_page->buffer;
            return lp_page;
        }
        lp_page = lp_page->p_next;
    }
    return 0;
}

static u32 VFiPFCACHE_SearchForFreePage(struct PF_CACHE_PAGE* p_head, struct PF_CACHE_PAGE** pp_page) {
    struct PF_CACHE_PAGE* p_page;

    p_page = p_head->p_prev;
    while (p_page != p_head) {
        if (!(p_page->stat & 1)) {
            *pp_page = p_page;
            return 1;
        }
        if (p_page->sector != 0xFFFFFFFF) {
            *pp_page = p_page;
            return 0;
        }
        p_page = p_page->p_prev;
    }

    if (!(p_page->stat & 1)) {
        *pp_page = p_page;
        return 1;
    }
    if (p_page->sector != 0xFFFFFFFF) {
        *pp_page = p_page;
        return 0;
    }

    *pp_page = NULL;
    return 0;
}

static void VFiPFCACHE_MovePageToHead(struct PF_CACHE_PAGE** pp_head, struct PF_CACHE_PAGE* p_page) {
    if (p_page != *pp_head) {
        if (p_page == (*pp_head)->p_prev) {
            *pp_head = p_page;
        } else {
            p_page->p_prev->p_next = p_page->p_next;
            p_page->p_next->p_prev = p_page->p_prev;
            p_page->p_next = *pp_head;
            p_page->p_prev = (*pp_head)->p_prev;
            p_page->p_next->p_prev = p_page;
            p_page->p_prev->p_next = p_page;
            *pp_head = p_page;
        }
    }
}

static void VFiPFCACHE_MovePageToTail(struct PF_CACHE_PAGE** pp_head, struct PF_CACHE_PAGE* p_page) {
    if (p_page == *pp_head) {
        *pp_head = p_page->p_next;
    } else if (p_page != (*pp_head)->p_prev) {
        p_page->p_prev->p_next = p_page->p_next;
        p_page->p_next->p_prev = p_page->p_prev;
        p_page->p_next = *pp_head;
        p_page->p_prev = (*pp_head)->p_prev;
        p_page->p_next->p_prev = p_page;
        p_page->p_prev->p_next = p_page;
    }
}

s32 VFiPFCACHE_FlushPageIfNeeded(struct PF_VOLUME* p_vol, struct PF_CACHE_PAGE* p_page) {
    u8* p_buf;
    s32 err;
    u32 num_success;
    u32 size;
    u32 sector;

    if (p_page != NULL && (p_page->stat & 2) && p_page->sector != 0xFFFFFFFF) {
        p_buf = p_page->p_mod_sbuf;
        sector = p_page->sector + ((u32)(p_buf - p_page->buffer) >> p_vol->bpb.log2_bytes_per_sector);
        size = ((u32)p_page->p_mod_ebuf >> p_vol->bpb.log2_bytes_per_sector) - ((u32)p_buf >> p_vol->bpb.log2_bytes_per_sector) + 1;
        err = VFiPFDRV_lwrite(p_vol, p_buf, sector, size, &num_success);
        if (err != 0) {
            return err;
        }

        if (num_success != size) {
            return 0x11;
        }

        if (p_page->stat & 4) {
            err = VFiPFFAT_UpdateAlternateFATEntry(p_vol, p_buf, sector, size);
            if (err != 0) {
                return err;
            }
        }

        p_page->p_mod_sbuf = NULL;
        p_page->p_mod_ebuf = NULL;
        p_page->stat &= ~2;
    }
    return 0;
}

static s32 VFiPFCACHE_ClearModified(struct PF_VOLUME* p_vol, struct PF_CACHE_PAGE* p_head) {
    struct PF_CACHE_PAGE* p_page;

    p_page = p_head;
    do {
        if ((p_page->stat & 1) == 0) {
            break;
        }
        p_page->stat &= ~2u;
        p_page = p_page->p_next;
    } while (p_page != p_head);

    return 0;
}

s32 VFiPFCACHE_DoAllocatePage(struct PF_VOLUME* p_vol, struct PF_CACHE_PAGE** pp_head, u32 sector, struct PF_CACHE_PAGE** pp_page, u32* p_is_hit) {
    s32 err;
    u32 offset;             // Present in DWARF but unused here.
    u32 data_start_sector;  // Present in DWARF but unused here.
    s32 do_flush;
    struct PF_CACHE_PAGE* p_page;  // Present in DWARF but unused here.

    do_flush = 0;
    *pp_page = VFiPFCACHE_SearchForPage(p_vol, *pp_head, sector);
    if (*pp_page) {
        *p_is_hit = 1;
    } else {
        *p_is_hit = 0;
        if (!VFiPFCACHE_SearchForFreePage(*pp_head, pp_page)) {
            if (!*pp_page) {
                *pp_page = 0;
                return 30;
            }

            if (*pp_page && ((*pp_page)->stat & 2) && (*pp_page)->sector != 0xFFFFFFFF) {
                do_flush = 1;
            }

            err = VFiPFCACHE_FlushPageIfNeeded(p_vol, *pp_page);
            if (err != 0) {
                *pp_page = NULL;
                return err;
            }

            (*pp_page)->p_mod_sbuf = 0;
            (*pp_page)->p_mod_ebuf = 0;

            if (do_flush) {
                if (dCommon_flush_from_handle_p((struct VF_HANDLE_TYPE*)p_vol, 1)) {
                    return 17;
                }
            }
        }

        if (sector != -1) {
            if (((*pp_page)->stat & 4) != 0) {
                (*pp_page)->sector = sector - (sector % (*pp_page)->size);
                (*pp_page)->p_buf = &(*pp_page)->buffer[(sector % (*pp_page)->size) << p_vol->bpb.log2_bytes_per_sector];
            } else {
                if (p_vol->bpb.fat_type == FAT_32 && (sector < p_vol->bpb.first_data_sector || sector >= p_vol->bpb.total_sectors)) {
                    if (sector == p_vol->bpb.fs_info_sector) {
                        (*pp_page)->size = 1;
                    }
                }
                (*pp_page)->sector = sector - (sector % (*pp_page)->size);
                (*pp_page)->p_buf = &(*pp_page)->buffer[(sector % (*pp_page)->size) << p_vol->bpb.log2_bytes_per_sector];
            }
        } else {
            (*pp_page)->sector = sector;
            (*pp_page)->p_buf = (*pp_page)->buffer;
        }

        (*pp_page)->stat |= 1u;
    }
    VFiPFCACHE_MovePageToHead(pp_head, *pp_page);
    return 0;
}

static void VFiPFCACHE_DoFreeCachePage(struct PF_CACHE_PAGE** pp_head, struct PF_CACHE_PAGE* p_page) {
    p_page->stat &= ~0x1;
    p_page->stat &= ~0x2;
    p_page->p_mod_sbuf = 0;
    p_page->p_mod_ebuf = 0;
    p_page->sector = -1;
    p_page->signature = 0;
    VFiPFCACHE_MovePageToTail(pp_head, p_page);
}

s32 VFiPFCACHE_DoReadPage(struct PF_VOLUME* p_vol, struct PF_CACHE_PAGE** pp_head, u32 sector, struct PF_CACHE_PAGE** pp_page, u32 set_sig) {
    u32 num_success;
    u32 is_hit;
    s32 err;

    err = VFiPFCACHE_DoAllocatePage(p_vol, pp_head, sector, pp_page, &is_hit);
    if (err) {
        return err;
    }

    if (!is_hit) {
        err = VFiPFDRV_lread(p_vol, (*pp_page)->buffer, (*pp_page)->sector, (*pp_page)->size, &num_success);
        if (err) {
            VFiPFCACHE_DoFreeCachePage(pp_head, *pp_page);
            return err;
        }
        if (num_success != (*pp_page)->size && p_vol->bpb.total_sectors != (*pp_page)->sector + num_success) {
            VFiPFCACHE_DoFreeCachePage(pp_head, *pp_page);
            return 17;
        }

        (*pp_page)->stat &= ~2;
        (*pp_page)->p_mod_sbuf = 0;
        (*pp_page)->p_mod_ebuf = 0;

        if (set_sig) {
            (*pp_page)->signature = p_vol->cache.signature;
        } else {
            (*pp_page)->signature = 0;
        }
    }
    return 0;
}

s32 VFiPFCACHE_DoReadPageAndFlushIfNeeded(struct PF_VOLUME* p_vol, struct PF_CACHE_PAGE** pp_head, u32 sector, struct PF_CACHE_PAGE** pp_page, u32 set_sig) {
    u32 num_success;
    u32 is_hit;
    s32 err;
    s32 do_flush;
    struct PF_CACHE_PAGE* p_page;  // Present in DWARF but unused here.

    do_flush = 1;

    err = VFiPFCACHE_DoAllocatePage(p_vol, pp_head, sector, pp_page, &is_hit);
    if (err) {
        return err;
    }

    if (!is_hit) {
        err = VFiPFDRV_lread(p_vol, (*pp_page)->buffer, (*pp_page)->sector, (*pp_page)->size, &num_success);
        if (err) {
            VFiPFCACHE_DoFreeCachePage(pp_head, *pp_page);
            return err;
        }
        if (num_success != (*pp_page)->size && p_vol->bpb.total_sectors != (*pp_page)->sector + num_success) {
            VFiPFCACHE_DoFreeCachePage(pp_head, *pp_page);
            return 17;
        }

        (*pp_page)->stat &= ~2u;
        (*pp_page)->p_mod_sbuf = 0;
        (*pp_page)->p_mod_ebuf = 0;

        if (set_sig) {
            (*pp_page)->signature = p_vol->cache.signature;
        } else {
            (*pp_page)->signature = 0;
        }

    } else {
        if (set_sig && (*pp_page)->stat & 2 && p_vol->cache.mode & 2 && (*pp_page)->signature != p_vol->cache.signature) {
            if (*pp_page && ((*pp_page)->stat & 2) && (*pp_page)->sector != 0xFFFFFFFF) {
                do_flush = 1;
            }

            err = VFiPFCACHE_FlushPageIfNeeded(p_vol, *pp_page);
            if (err) {
                *pp_page = NULL;
                return err;
            }

            if (do_flush) {
                err = dCommon_flush_from_handle_p((struct VF_HANDLE_TYPE*)p_vol, 1);
                if (err) {
                    return 17;
                }
            }
        }
    }

    return 0;
}

s32 VFiPFCACHE_DoReadNumSector(struct PF_VOLUME* p_vol, struct PF_CACHE_PAGE** pp_head, u8* p_buf, u32 sector, u32 num_sector, u32* p_num_success) {
    struct PF_CACHE_PAGE* p_page;
    s32 err;
    u32 num_rest_sector;
    u32 num_success_sector;

    *p_num_success = 0;

    err = VFiPFDRV_lread(p_vol, p_buf, sector, num_sector, p_num_success);
    if (err) {
        return err;
    }

    p_page = NULL;
    num_success_sector = *p_num_success;
    num_rest_sector = *p_num_success;

    do {
        p_page = VFiPFCACHE_SearchForUsedPage(p_vol, pp_head, p_page);

        if (p_page != NULL && p_page->sector != 0xFFFFFFFF) {
            if (p_page->sector <= sector && p_page->sector + p_page->size >= sector + num_success_sector) {
                VFipf_memcpy(p_buf, &p_page->buffer[(sector - p_page->sector) << p_vol->bpb.log2_bytes_per_sector], num_success_sector << p_vol->bpb.log2_bytes_per_sector);
                num_rest_sector -= num_success_sector;
            } else if (p_page->sector >= sector && p_page->sector + p_page->size <= sector + num_success_sector) {
                VFipf_memcpy(&p_buf[(p_page->sector - sector) << p_vol->bpb.log2_bytes_per_sector], p_page->buffer, p_page->size << p_vol->bpb.log2_bytes_per_sector);
                num_rest_sector -= p_page->size;
            } else if (p_page->sector > sector && p_page->sector < sector + num_success_sector && p_page->sector + p_page->size >= sector + num_success_sector) {
                VFipf_memcpy(&p_buf[(p_page->sector - sector) << p_vol->bpb.log2_bytes_per_sector], p_page->buffer, (p_page->size - ((p_page->sector + p_page->size) - (sector + num_success_sector))) << p_vol->bpb.log2_bytes_per_sector);
                num_rest_sector -= p_page->size - ((p_page->sector + p_page->size) - (sector + num_success_sector));
            } else if (p_page->sector < sector && p_page->sector + p_page->size > sector && p_page->sector + p_page->size <= sector + num_success_sector) {
                VFipf_memcpy(p_buf, &p_page->buffer[(sector - p_page->sector) << p_vol->bpb.log2_bytes_per_sector], (p_page->size - (sector - p_page->sector)) << p_vol->bpb.log2_bytes_per_sector);
                num_rest_sector -= p_page->size - (sector - p_page->sector);
            }
        }
    } while (p_page && num_rest_sector);

    if (*p_num_success != num_sector && sector + *p_num_success != p_vol->bpb.total_sectors) {
        return 17;
    } else {
        return 0;
    }
}

s32 VFiPFCACHE_DoWritePage(struct PF_VOLUME* p_vol, struct PF_CACHE_PAGE** pp_head, struct PF_CACHE_PAGE* p_page, u32 set_sig) {
    s32 err;
    s32 do_flush;

    do_flush = 0;
    VFiPFCACHE_MovePageToHead(pp_head, p_page);

    if (p_page->p_mod_sbuf == 0) {
        p_page->stat |= 2;
        p_page->p_mod_sbuf = p_page->p_buf;
        p_page->p_mod_ebuf = p_page->p_buf;
    } else {
        if (p_page->p_buf < p_page->p_mod_sbuf) {
            p_page->p_mod_sbuf = p_page->p_buf;
        } else if (p_page->p_buf > p_page->p_mod_ebuf) {
            p_page->p_mod_ebuf = p_page->p_buf;
        }
    }

    if (set_sig) {
        p_page->signature = p_vol->cache.signature;
    } else {
        p_page->signature = 0;
    }

    if ((p_vol->cache.mode & 1) != 0 || ((p_vol->cache.mode & 4) != 0 && (p_page->stat & 4) != 0)) {
        if (p_page && (p_page->stat & 2) != 0 && p_page->sector != -1) {
            do_flush = 1;
        }

        err = VFiPFCACHE_FlushPageIfNeeded(p_vol, p_page);

        if (err) {
            return err;
        }

        if (do_flush && dCommon_flush_from_handle_p((struct VF_HANDLE_TYPE*)p_vol, 1)) {
            return 17;
        }
    }

    return 0;
}

s32 VFiPFCACHE_DoWriteSector(struct PF_VOLUME* p_vol, struct PF_CACHE_PAGE** pp_head, const u8* p_buf, u32 sector) {
    struct PF_CACHE_PAGE* p_page;
    u32 num_success;
    s32 err;
    s32 do_flush;

    do_flush = 0;

    p_page = VFiPFCACHE_SearchForPage(p_vol, *pp_head, sector);

    if (p_page) {
        VFipf_memcpy(p_page->p_buf, (void*)p_buf, p_vol->bpb.bytes_per_sector);

        if (p_page->p_mod_sbuf == 0) {
            p_page->stat |= 2;
            p_page->p_mod_sbuf = p_page->p_buf;
            p_page->p_mod_ebuf = p_page->p_buf;
        } else {
            if (p_page->p_buf < p_page->p_mod_sbuf) {
                p_page->p_mod_sbuf = p_page->p_buf;
            } else if (p_page->p_buf > p_page->p_mod_ebuf) {
                p_page->p_mod_ebuf = p_page->p_buf;
            }
        }

        if (p_page && (p_page->stat & 2) != 0 && p_page->sector != 0xFFFFFFFF) {
            do_flush = 1;
        }

        err = VFiPFCACHE_FlushPageIfNeeded(p_vol, p_page);
        if (err) {
            return err;
        }

        if (do_flush && dCommon_flush_from_handle_p((struct VF_HANDLE_TYPE*)p_vol, 1)) {
            return 17;
        }
    } else {
        err = VFiPFDRV_lwrite(p_vol, p_buf, sector, 1, &num_success);
        if (err) {
            return err;
        }

        if (num_success != 1) {
            return 17;
        }

        err = dCommon_flush_from_handle_p((struct VF_HANDLE_TYPE*)p_vol, 1);
        if (err) {
            return 17;
        }
    }

    return 0;
}

s32 VFiPFCACHE_DoWriteNumSectorAndFreeIfNeeded(struct PF_VOLUME* p_vol, struct PF_CACHE_PAGE** pp_head, const u8* p_buf, u32 sector, u32 num_sector, u32* p_num_success) {
    struct PF_CACHE_PAGE* p_page;
    s32 err;
    u32 num_rest_sector;
    u8* p_sbuf;
    u8* p_ebuf;

    p_page = NULL;
    num_rest_sector = num_sector;
    *p_num_success = 0;

    do {
        p_page = VFiPFCACHE_SearchForUsedPage(p_vol, pp_head, p_page);

        if (p_page != NULL && p_page->sector != 0xFFFFFFFF) {
            if (p_page->sector <= sector && p_page->sector + p_page->size >= sector + num_sector) {
                VFipf_memcpy(&p_page->buffer[(sector - p_page->sector) << p_vol->bpb.log2_bytes_per_sector], (void*)p_buf, num_sector << p_vol->bpb.log2_bytes_per_sector);
                *p_num_success += num_rest_sector;
                num_rest_sector = 0;
                p_page->stat |= 2;
                p_sbuf = &p_page->buffer[(sector - p_page->sector) << p_vol->bpb.log2_bytes_per_sector];
                p_ebuf = p_sbuf + ((num_sector - 1) << p_vol->bpb.log2_bytes_per_sector);
                if (!p_page->p_mod_sbuf) {
                    p_page->p_mod_sbuf = p_sbuf;
                    p_page->p_mod_ebuf = p_ebuf;
                } else if (p_sbuf < p_page->p_mod_sbuf) {
                    p_page->p_mod_sbuf = p_sbuf;
                } else if (p_page->p_mod_ebuf < p_ebuf) {
                    p_page->p_mod_ebuf = p_ebuf;
                }
            } else if (p_page->sector >= sector && p_page->sector + p_page->size <= sector + num_sector) {
                VFipf_memcpy(p_page->buffer, (void*)&p_buf[(p_page->sector - sector) << p_vol->bpb.log2_bytes_per_sector], p_page->size << p_vol->bpb.log2_bytes_per_sector);
                num_rest_sector -= p_page->size;
                *p_num_success += p_page->size;
                p_page->stat |= 2;
                p_page->p_mod_sbuf = p_page->buffer;
                p_page->p_mod_ebuf = &p_page->buffer[(p_page->size - 1) << p_vol->bpb.log2_bytes_per_sector];
            } else if (p_page->sector > sector && p_page->sector < sector + num_sector && p_page->sector + p_page->size >= sector + num_sector) {
                VFipf_memcpy(p_page->buffer, (void*)&p_buf[(p_page->sector - sector) << p_vol->bpb.log2_bytes_per_sector], (p_page->size - ((p_page->sector + p_page->size) - (sector + num_sector))) << p_vol->bpb.log2_bytes_per_sector);
                num_rest_sector -= p_page->size - ((p_page->sector + p_page->size) - (sector + num_sector));
                *p_num_success += p_page->size - ((p_page->sector + p_page->size) - (sector + num_sector));
                p_page->stat |= 2;
                p_ebuf = &p_page->buffer[(p_page->size - ((p_page->sector + p_page->size) - (sector + num_sector)) - 1) << p_vol->bpb.log2_bytes_per_sector];
                p_page->p_mod_sbuf = p_page->buffer;
                if (!p_page->p_mod_ebuf || p_page->p_mod_ebuf < p_ebuf) {
                    p_page->p_mod_ebuf = p_ebuf;
                }
            } else if (p_page->sector < sector && p_page->sector + p_page->size > sector && p_page->sector + p_page->size <= sector + num_sector) {
                VFipf_memcpy(&p_page->buffer[(sector - p_page->sector) << p_vol->bpb.log2_bytes_per_sector], (void*)p_buf, (p_page->size - (sector - p_page->sector)) << p_vol->bpb.log2_bytes_per_sector);
                num_rest_sector -= p_page->size - (sector - p_page->sector);
                *p_num_success += p_page->size - (sector - p_page->sector);
                p_page->stat |= 2;
                p_sbuf = &p_page->buffer[(p_page->size - (sector - p_page->sector) - 1) << p_vol->bpb.log2_bytes_per_sector];
                if (!p_page->p_mod_sbuf || p_sbuf < p_page->p_mod_sbuf) {
                    p_page->p_mod_sbuf = p_sbuf;
                }
                p_page->p_mod_ebuf = &p_page->buffer[(p_page->size - 1) << p_vol->bpb.log2_bytes_per_sector];
            }
        }
    } while (p_page && num_rest_sector);

    if (num_rest_sector != 0 || (p_vol->cache.mode & 1) != 0) {
        err = VFiPFDRV_lwrite(p_vol, p_buf, sector, num_sector, p_num_success);
        if (err) {
            return err;
        }
        if (dCommon_flush_from_handle_p((struct VF_HANDLE_TYPE*)p_vol, 1)) {
            return 17;
        }
    }

    if ((p_vol->cache.mode & 1) != 0 && num_sector != num_rest_sector) {
        VFiPFCACHE_ClearModified(p_vol, p_vol->cache.p_current_data);
    }

    return 0;
}

s32 VFiPFCACHE_DoFlushCache(struct PF_VOLUME* p_vol, struct PF_CACHE_PAGE* p_head) {
    struct PF_CACHE_PAGE* p_page;
    s32 err;
    s32 first_err;
    s32 check_do_flush;
    s32 do_flush;
    s32 set_device_err;

    do_flush = 0;
    first_err = 0;
    p_page = p_head;

    if ((p_head->stat & 1) == 0) {
        return 0;
    }

    do {
        if ((p_page->stat & 1) == 0) {
            break;
        }

        check_do_flush = 0;
        if (p_page && (p_page->stat & 2) != 0) {
            if (p_page->sector != -1) {
                check_do_flush = 1;
            }
        }

        err = VFiPFCACHE_FlushPageIfNeeded(p_vol, p_page);

        if (check_do_flush && err == 0) {
            do_flush = 1;
        }

        if (err != 0 && first_err == 0) {
            first_err = err;
        }

        p_page = p_page->p_next;

    } while (p_page != p_head);

    if (do_flush) {
        set_device_err = !first_err;
        do_flush = set_device_err;
        set_device_err = dCommon_flush_from_handle_p((struct VF_HANDLE_TYPE*)p_vol, do_flush);
        if (set_device_err != 0 && do_flush == 1) {
            return 17;
        }
    }

    return first_err;
}

void VFiPFCACHE_SetCache(struct PF_VOLUME* p_vol, struct PF_CACHE_PAGE* p_cache_page, u8 (*p_cache_buf)[512], u16 num_fat_pages, u16 num_data_pages) {
    p_vol->cache.pages = p_cache_page;
    p_vol->cache.buffers = p_cache_buf;
    p_vol->cache.num_fat_pages = num_fat_pages;
    p_vol->cache.num_data_pages = num_data_pages;
}

void VFiPFCACHE_SetFATBufferSize(struct PF_VOLUME* p_vol, u32 size) {
    if (size) {
        p_vol->cache.fat_buff_size = size;
    }
}

void VFiPFCACHE_SetDataBufferSize(struct PF_VOLUME* p_vol, u32 size) {
    if (size) {
        p_vol->cache.data_buff_size = size;
    }
}

s32 VFiPFCACHE_InitCaches(struct PF_VOLUME* p_vol) {
    s32 err;

    p_vol->cache.mode &= ~1u;
    p_vol->cache.mode |= 2u;
    p_vol->cache.mode &= ~4u;
    VFipf_memset(p_vol->cache.buffers, 0, (p_vol->cache.num_fat_pages + p_vol->cache.num_data_pages) << 9);

    err = VFiPFCACHE_InitPageList(p_vol, &p_vol->cache.p_current_fat, p_vol->cache.pages, p_vol->cache.buffers, p_vol->cache.num_fat_pages, p_vol->cache.fat_buff_size, 1);
    if (err) {
        return err;
    } else {
        err = VFiPFCACHE_InitPageList(p_vol, &p_vol->cache.p_current_data, &p_vol->cache.pages[p_vol->cache.num_fat_pages], &p_vol->cache.buffers[p_vol->cache.num_fat_pages], p_vol->cache.num_data_pages, p_vol->cache.data_buff_size, 0);
    }

    if (!err) {
        return 0;
    }
    return err;
}

s32 VFiPFCACHE_UpdateModifiedSector(struct PF_CACHE_PAGE* p_page) {
    if (p_page->p_mod_sbuf == 0) {
        p_page->stat |= 2;
        p_page->p_mod_sbuf = p_page->p_buf;
        p_page->p_mod_ebuf = p_page->p_buf;
    } else {
        if (p_page->p_buf < p_page->p_mod_sbuf) {
            p_page->p_mod_sbuf = p_page->p_buf;
        } else if (p_page->p_buf > p_page->p_mod_ebuf) {
            p_page->p_mod_ebuf = p_page->p_buf;
        }
    }
    return 0;
}

s32 VFiPFCACHE_AllocateFATPage(struct PF_VOLUME* p_vol, u32 sector, struct PF_CACHE_PAGE** pp_page) {
    s32 err;
    u32 is_hit;

    if (!p_vol->cache.p_current_fat) {
        p_vol->cache.pages->buffer = *p_vol->cache.buffers;
        p_vol->cache.pages->p_buf = *p_vol->cache.buffers;
        *pp_page = p_vol->cache.pages;
        return 0;
    }

    err = VFiPFCACHE_DoAllocatePage(p_vol, &p_vol->cache.p_current_fat, sector, pp_page, &is_hit);
    if (!err) {
        return 0;
    }
    return err;
}

s32 VFiPFCACHE_AllocateDataPage(struct PF_VOLUME* p_vol, u32 sector, struct PF_CACHE_PAGE** pp_page) {
    s32 err;
    u32 is_hit;

    if (!p_vol->cache.p_current_data) {
        p_vol->cache.pages->buffer = *p_vol->cache.buffers;
        p_vol->cache.pages->p_buf = *p_vol->cache.buffers;
        *pp_page = p_vol->cache.pages;
        return 0;
    } else {
        err = VFiPFCACHE_DoAllocatePage(p_vol, &p_vol->cache.p_current_data, sector, pp_page, &is_hit);
        if (!err) {
            return 0;
        }
    }
    return err;
}

void VFiPFCACHE_FreeFATPage(struct PF_VOLUME* p_vol, struct PF_CACHE_PAGE* p_page) {
    if (p_vol->cache.p_current_fat) {
        p_page->p_mod_sbuf = 0;
        p_page->p_mod_ebuf = 0;
        VFiPFCACHE_DoFreeCachePage(&p_vol->cache.p_current_fat, p_page);
    }
}

void VFiPFCACHE_FreeDataPage(struct PF_VOLUME* p_vol, struct PF_CACHE_PAGE* p_page) {
    if (p_vol->cache.p_current_data) {
        p_page->p_mod_sbuf = 0;
        p_page->p_mod_ebuf = 0;
        VFiPFCACHE_DoFreeCachePage(&p_vol->cache.p_current_data, p_page);
    }
}

s32 VFiPFCACHE_ReadFATPage(struct PF_VOLUME* p_vol, u32 sector, struct PF_CACHE_PAGE** pp_page) {
    s32 err;

    err = VFiPFCACHE_DoReadPage(p_vol, &p_vol->cache.p_current_fat, sector, pp_page, 0);
    if (!err) {
        return 0;
    }

    return err;
}

s32 VFiPFCACHE_ReadDataPage(struct PF_VOLUME* p_vol, u32 sector, struct PF_CACHE_PAGE** pp_page, u32 set_sig) {
    s32 err;

    err = VFiPFCACHE_DoReadPage(p_vol, &p_vol->cache.p_current_data, sector, pp_page, set_sig);
    if (!err) {
        return 0;
    }
    return err;
}

s32 VFiPFCACHE_ReadDataPageAndFlushIfNeeded(struct PF_VOLUME* p_vol, u32 sector, struct PF_CACHE_PAGE** pp_page, u32 set_sig) {
    s32 err;

    err = VFiPFCACHE_DoReadPageAndFlushIfNeeded(p_vol, &p_vol->cache.p_current_data, sector, pp_page, set_sig);
    if (!err) {
        return 0;
    }
    return err;
}

s32 VFiPFCACHE_ReadDataNumSector(struct PF_VOLUME* p_vol, u8* p_buf, u32 sector, u32 num_sector, u32* p_num_success) {
    s32 err;

    if (sector >= p_vol->bpb.total_sectors) {
        return 16;
    }

    err = VFiPFCACHE_DoReadNumSector(p_vol, &p_vol->cache.p_current_data, p_buf, sector, num_sector, p_num_success);
    if (!err) {
        return 0;
    }
    return err;
}

s32 VFiPFCACHE_WriteFATPage(struct PF_VOLUME* p_vol, struct PF_CACHE_PAGE* p_page) {
    s32 err;

    err = VFiPFCACHE_DoWritePage(p_vol, &p_vol->cache.p_current_fat, p_page, 0);
    if (!err) {
        return 0;
    }
    return err;
}

s32 VFiPFCACHE_WriteDataPage(struct PF_VOLUME* p_vol, struct PF_CACHE_PAGE* p_page, u32 set_sig) {
    s32 err;

    err = VFiPFCACHE_DoWritePage(p_vol, &p_vol->cache.p_current_data, p_page, set_sig);
    if (!err) {
        return 0;
    }
    return err;
}

s32 VFiPFCACHE_WriteFATSectorAndFreeIfNeeded(struct PF_VOLUME* p_vol, const u8* p_buf, u32 sector) {
    s32 err;

    if (sector >= p_vol->bpb.total_sectors) {
        return 16;
    }

    err = VFiPFCACHE_DoWriteSector(p_vol, &p_vol->cache.p_current_fat, p_buf, sector);
    if (!err) {
        return 0;
    }
    return err;
}

s32 VFiPFCACHE_WriteDataNumSectorAndFreeIfNeeded(struct PF_VOLUME* p_vol, const u8* p_buf, u32 sector, u32 num_sector, u32* p_num_success) {
    s32 err;

    if (sector >= p_vol->bpb.total_sectors) {
        return 16;
    }
    err = VFiPFCACHE_DoWriteNumSectorAndFreeIfNeeded(p_vol, &p_vol->cache.p_current_data, p_buf, sector, num_sector, p_num_success);
    if (!err) {
        return 0;
    }
    return err;
}

struct PF_CACHE_PAGE* VFiPFCACHE_SearchDataCache(struct PF_VOLUME* p_vol, u32 sector) {
    return VFiPFCACHE_SearchForPage(p_vol, p_vol->cache.p_current_data, sector);
}

s32 VFiPFCACHE_FlushFATCache(struct PF_VOLUME* p_vol) {
    s32 err;

    err = VFiPFCACHE_DoFlushCache(p_vol, p_vol->cache.p_current_fat);
    if (!err) {
        return 0;
    }
    return err;
}

s32 VFiPFCACHE_FlushDataCacheSpecific(struct PF_VOLUME* p_vol, void* signature) {
    s32 err;
    struct PF_CACHE_PAGE* p_head;
    struct PF_CACHE_PAGE* p_page;
    u32 check_do_flush;
    u32 do_flush;

    err = 0;
    do_flush = 0;

    if ((p_vol->cache.mode & 0x7)) {
        p_head = p_vol->cache.p_current_data;
        p_page = p_head;

        if (p_page->signature == 0 || p_page->signature == signature) {
            if (p_page != 0) {
                if ((p_page->stat & 2) && p_page->sector != (u32)-1) {
                    do_flush = 1;
                }
            }
            err = VFiPFCACHE_FlushPageIfNeeded(p_vol, p_page);
            if (err) {
                return err;
            }
        }

        p_page = p_head->p_next;
        while (p_page != p_head) {
            if (p_page->signature == 0 || p_page->signature == signature) {
                check_do_flush = 0;
                if (p_page != 0) {
                    if ((p_page->stat & 2) && p_page->sector != (u32)-1) {
                        check_do_flush = 1;
                    }
                }
                err = VFiPFCACHE_FlushPageIfNeeded(p_vol, p_page);
                if (err) {
                    if (do_flush) {
                        dCommon_flush_from_handle_p((struct VF_HANDLE_TYPE*)p_vol, 0);
                    }
                    return err;
                }
                if (check_do_flush) {
                    do_flush = 1;
                }
            }
            p_page = p_page->p_next;
        }

        if (do_flush) {
            if (dCommon_flush_from_handle_p((struct VF_HANDLE_TYPE*)p_vol, 1)) {
                return 17;
            }
        }
    }

    return err;
}

s32 VFiPFCACHE_FlushAllCaches(struct PF_VOLUME* p_vol) {
    s32 err;

    err = VFiPFCACHE_DoFlushCache(p_vol, p_vol->cache.p_current_fat);
    if (err) {
        return err;
    }

    err = VFiPFCACHE_DoFlushCache(p_vol, p_vol->cache.p_current_data);
    if (!err) {
        return 0;
    }
    return err;
}

void VFiPFCACHE_FreeAllCaches(struct PF_VOLUME* p_vol) {
    while ((p_vol->cache.p_current_fat->stat & 1) != 0) {
        VFiPFCACHE_FreeFATPage(p_vol, p_vol->cache.p_current_fat);
    }
    while ((p_vol->cache.p_current_data->stat & 1) != 0) {
        VFiPFCACHE_FreeDataPage(p_vol, p_vol->cache.p_current_data);
    }
}
