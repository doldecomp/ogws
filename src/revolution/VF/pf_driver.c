#include <revolution/VF.h>

extern PF_VOLUME_SET VFipf_vol_set;

s32 VFiPFDRV_GetBPBInformation(u8* p_buf, struct PF_BPB* p_bpb) {
    s32 err;  // Present in DWARF but unused here.
    struct PDM_BPB bpb;

    if (VFipdm_bpb_get_bpb_information(p_buf, &bpb)) {
        return 7;
    }

    p_bpb->bytes_per_sector = bpb.bytes_per_sector;
    p_bpb->num_reserved_sectors = bpb.num_reserved_sectors;
    p_bpb->num_root_dir_entries = bpb.num_root_dir_entries;
    p_bpb->sectors_per_cluster = bpb.sectors_per_cluster;
    p_bpb->num_FATs = bpb.num_FATs;
    p_bpb->total_sectors = bpb.total_sectors;
    p_bpb->sectors_per_FAT = bpb.sectors_per_FAT;
    p_bpb->root_dir_cluster = bpb.root_dir_cluster;
    p_bpb->fs_info_sector = bpb.fs_info_sector;
    p_bpb->backup_boot_sector = bpb.backup_boot_sector;
    p_bpb->ext_flags = bpb.ext_flags;
    p_bpb->media = bpb.media;
    p_bpb->fat_type = bpb.fat_type;
    p_bpb->log2_bytes_per_sector = bpb.log2_bytes_per_sector;
    p_bpb->log2_sectors_per_cluster = bpb.log2_sectors_per_cluster;
    p_bpb->num_active_FATs = bpb.num_active_FATs;
    p_bpb->num_root_dir_sectors = bpb.num_root_dir_sectors;
    p_bpb->active_FAT_sector = bpb.active_FAT_sector;
    p_bpb->first_root_dir_sector = bpb.first_root_dir_sector;
    p_bpb->first_data_sector = bpb.first_data_sector;
    p_bpb->num_clusters = bpb.num_clusters;
    return 0;
}

static s32 VFiPFDRV_LoadFSINFOInformation(u8* p_buf, PF_VOLUME* p_vol) {
    PDM_FSINFO fsinfo;

    if (VFipdm_bpb_get_fsinfo_information(p_buf, &fsinfo)) {
        return 7;
    }
    if (fsinfo.free_count >= 2 && fsinfo.free_count < p_vol->bpb.num_clusters + 2) {
        p_vol->num_free_clusters = fsinfo.free_count;
    }
    if (fsinfo.next_free >= 2 && fsinfo.next_free < p_vol->bpb.num_clusters + 2) {
        p_vol->last_free_cluster = fsinfo.next_free;
    }
    return 0;
}

static void VFiPFDRV_notifyExecuteFormatAfterMount(PF_VOLUME* p_vol, const u8* format_param) {
    p_vol->flags |= 0x10u;
    p_vol->format_param = format_param;
}

static void VFiPFDRV_notifyNoExecuteLogicalFormat(struct PF_VOLUME* p_vol) {
    p_vol->flags |= 0x20u;
}

s32 VFiPFDRV_GetFSINFOInformation(struct PF_VOLUME* p_vol) {
    s32 err;
    struct PF_CACHE_PAGE* p_page;
    u32 nSector;
    u32 is_valid;

    err = VFiPFCACHE_AllocateDataPage(p_vol, 0xFFFFFFFF, &p_page);
    if (err) {
        return err;
    }

    err = VFipdm_part_logical_read(p_vol->p_part, p_page->buffer, p_vol->bpb.fs_info_sector, 1, p_vol->bpb.bytes_per_sector, &nSector);
    if (err) {
        if (err == 21) {
            err = VFipdm_part_get_driver_error_code(p_vol->p_part);
            VFipf_vol_set.last_driver_error = err;
            p_vol->last_driver_error = err;
            err = 4096;
        } else {
            err = -1;
        }
        VFiPFCACHE_FreeDataPage(p_vol, p_page);
        VFipdm_part_release_permission(p_vol->p_part, 1);
        return err;
    } else {
        if (VFipdm_bpb_check_fsinfo_sector(p_page->buffer, &is_valid)) {
            VFiPFCACHE_FreeDataPage(p_vol, p_page);
            VFipdm_part_release_permission(p_vol->p_part, 1);
            return -1;
        }

        if (!is_valid) {
            VFiPFCACHE_FreeDataPage(p_vol, p_page);
            VFipdm_part_release_permission(p_vol->p_part, 1);
            return 7;
        }
        if (VFiPFDRV_LoadFSINFOInformation(p_page->buffer, p_vol)) {
            VFiPFCACHE_FreeDataPage(p_vol, p_page);
            VFipdm_part_release_permission(p_vol->p_part, 1);
            return -1;
        }
        VFiPFCACHE_FreeDataPage(p_vol, p_page);
        return 0;
    }
}

s32 VFiPFDRV_StoreFreeCountToFSINFO(struct PF_VOLUME* p_vol) {
    s32 err;
    struct PF_CACHE_PAGE* p_page;
    u32 num_success;

    err = VFiPFCACHE_AllocateDataPage(p_vol, 0xFFFFFFFF, &p_page);
    if (err) {
        return err;
    }

    err = VFiPFDRV_lread(p_vol, p_page->p_buf, p_vol->bpb.fs_info_sector, 1, &num_success);
    if (err || num_success != 1) {
        err = 17;
    }
    if (!err) {
        p_page->p_buf[488] = (u8)(p_vol->num_free_clusters & 0xFF);
        p_page->p_buf[489] = (u8)((p_vol->num_free_clusters >> 8) & 0xFF);
        p_page->p_buf[490] = (u8)((p_vol->num_free_clusters >> 16) & 0xFF);
        p_page->p_buf[491] = (u8)((p_vol->num_free_clusters >> 24) & 0xFF);
        err = VFiPFDRV_lwrite(p_vol, p_page->p_buf, p_vol->bpb.fs_info_sector, 1u, &num_success);
        if (err || num_success != 1) {
            err = 17;
        }
    }
    VFiPFCACHE_FreeDataPage(p_vol, p_page);
    return err;
}

u32 VFiPFDRV_IsInserted(struct PF_VOLUME* p_vol) {
    u32 is_insert;
    VFipdm_part_check_media_insert(p_vol->p_part, &is_insert);
    return is_insert;
}

u32 VFiPFDRV_IsDetected(struct PF_VOLUME* p_vol) {
    u32 is_detect;
    VFipdm_part_check_media_detect(p_vol->p_part, &is_detect);
    return is_detect;
}

u32 VFiPFDRV_IsWProtected(struct PF_VOLUME* p_vol) {
    u32 is_wprotect;
    VFipdm_part_check_media_write_protect(p_vol->p_part, &is_wprotect);
    return is_wprotect;
}

s32 VFiPFDRV_init(struct PF_VOLUME* p_vol) {
    u32 r0 = __cntlzw((u32)p_vol);
    r0 = (r0 << 26) >> 31;
    return -r0 & 0xa;
}

s32 VFiPFDRV_finalize(struct PF_VOLUME* p_vol) {
    if (p_vol) {
        return 0;
    } else {
        return 10;
    }
}

s32 VFiPFDRV_mount(struct PF_VOLUME* p_vol) {
    s32 err;
    struct PF_CACHE_PAGE* p_page;
    u32 nSector;
    struct PDM_DISK_INFO disk_inf;
    u32 is_valid;

    if (!p_vol) {
        return 10;
    }
    err = VFipdm_part_get_permission(p_vol->p_part);
    if (err) {
        if (err == 21) {
            err = VFipdm_part_get_driver_error_code(p_vol->p_part);
            VFipf_vol_set.last_driver_error = err;
            p_vol->last_driver_error = err;
            return 4096;
        } else {
            return -1;
        }
    } else if (VFipdm_part_get_media_information(p_vol->p_part, &disk_inf)) {
        VFipdm_part_release_permission(p_vol->p_part, 1);
        return -1;
    } else {
        if ((disk_inf.media_attr & 2) != 0) {
            VFiPFDRV_notifyExecuteFormatAfterMount(p_vol, disk_inf.format_param);
        }
        if ((disk_inf.media_attr & 8) != 0) {
            VFiPFDRV_notifyNoExecuteLogicalFormat(p_vol);
        }
        VFiPFCACHE_AllocateDataPage(p_vol, 0xFFFFFFFF, &p_page);
        err = VFipdm_part_logical_read(p_vol->p_part, p_page->buffer, 0, 1, 512, &nSector);
        if (err) {
            if (err == 21) {
                err = VFipdm_part_get_driver_error_code(p_vol->p_part);
                VFipf_vol_set.last_driver_error = err;
                p_vol->last_driver_error = err;
                err = 4096;
            } else {
                err = -1;
            }
            VFiPFCACHE_FreeDataPage(p_vol, p_page);
            VFipdm_part_release_permission(p_vol->p_part, 1);
            return err;
        } else if (VFipdm_bpb_check_boot_sector(p_page->buffer, &is_valid)) {
            VFiPFCACHE_FreeDataPage(p_vol, p_page);
            VFipdm_part_release_permission(p_vol->p_part, 1);
            return -1;
        } else if (!is_valid) {
            VFiPFCACHE_FreeDataPage(p_vol, p_page);
            VFipdm_part_release_permission(p_vol->p_part, 1);
            return 7;
        } else {
            err = VFiPFDRV_GetBPBInformation(p_page->buffer, &p_vol->bpb);
            if (err) {
                VFiPFCACHE_FreeDataPage(p_vol, p_page);
                VFipdm_part_release_permission(p_vol->p_part, 1);
                return err;
            } else {
                VFiPFCACHE_FreeDataPage(p_vol, p_page);
                p_vol->num_free_clusters = -1;
                p_vol->last_free_cluster = -1;
                if (p_vol->bpb.fat_type == FAT_32) {
                    err = VFiPFDRV_GetFSINFOInformation(p_vol);
                }
            }
        }

        return err;
    }
}

s32 VFiPFDRV_unmount(struct PF_VOLUME* p_vol, u32 mode) {
    s32 err;

    if (!p_vol) {
        return 10;
    }
    err = VFipdm_part_release_permission(p_vol->p_part, mode == 1);

    if (err) {
        if (err == 21) {
            err = VFipdm_part_get_driver_error_code(p_vol->p_part);
            VFipf_vol_set.last_driver_error = err;
            p_vol->last_driver_error = err;
            return 4096;
        }

        return -1;
    }

    return 0;
}

s32 VFiPFDRV_format(struct PF_VOLUME* p_vol, const u8* param) {
    s32 err;

    if (!p_vol) {
        return 10;
    }

    if ((p_vol->flags & 2) == 0) {
        err = VFipdm_part_get_permission(p_vol->p_part);
        if (err) {
            if (err == 21) {
                err = VFipdm_part_get_driver_error_code(p_vol->p_part);
                VFipf_vol_set.last_driver_error = err;
                p_vol->last_driver_error = err;
                return 4096;
            }
            return -1;
        }
    }

    err = VFipdm_part_format(p_vol->p_part, param);
    if (err) {
        if (err == 21) {
            err = VFipdm_part_get_driver_error_code(p_vol->p_part);
            VFipf_vol_set.last_driver_error = err;
            p_vol->last_driver_error = err;
            return 4096;
        }
        return -1;
    }

    if ((p_vol->flags & 2) == 0) {
        err = VFipdm_part_release_permission(p_vol->p_part, 1);
        if (err) {
            if (err == 21) {
                err = VFipdm_part_get_driver_error_code(p_vol->p_part);
                VFipf_vol_set.last_driver_error = err;
                p_vol->last_driver_error = err;
                return 4096;
            }

            return -1;
        }
    }

    return 0;
}

s32 VFiPFDRV_lread(struct PF_VOLUME* p_vol, u8* buf, u32 sector, u32 num_sectors, u32* p_num_success) {
    s32 err;

    if (!p_vol) {
        return 10;
    }
    err = VFipdm_part_logical_read(p_vol->p_part, buf, sector, num_sectors, p_vol->bpb.bytes_per_sector, p_num_success);

    if (err) {
        if (err == 21) {
            err = VFipdm_part_get_driver_error_code(p_vol->p_part);
            VFipf_vol_set.last_driver_error = err;
            p_vol->last_driver_error = err;
            return 4096;
        }

        return -1;
    }

    return 0;
}

s32 VFiPFDRV_lwrite(struct PF_VOLUME* p_vol, const u8* buf, u32 sector, u32 num_sectors, u32* p_num_success) {
    s32 err;

    if (!p_vol) {
        return 10;
    }
    err = VFipdm_part_logical_write(p_vol->p_part, buf, sector, num_sectors, p_vol->bpb.bytes_per_sector, p_num_success);

    if (err) {
        if (err == 21) {
            err = VFipdm_part_get_driver_error_code(p_vol->p_part);
            VFipf_vol_set.last_driver_error = err;
            p_vol->last_driver_error = err;
            return 4096;
        }

        return -1;
    }

    return 0;
}
