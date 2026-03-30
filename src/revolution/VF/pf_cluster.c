#include <revolution/VF.h>

extern PF_VOLUME_SET VFipf_vol_set;

void VFiPFCLUSTER_UpdateLastAccessCluster(struct PF_FILE* p_file, u32 sector) {
    struct PF_VOLUME* p_vol;
    if (!p_file->cursor.position) {
        p_file->p_sfd->ffd.last_access_cluster.cluster = 0;
        p_file->p_sfd->ffd.last_access_cluster.chain_index = 0;
    } else {
        if (p_file == 0) {
            p_vol = 0;
        } else {
            p_vol = p_file->p_sfd->dir_entry.p_vol;
        }
        if ((p_file->cursor.position & (p_vol->bpb.bytes_per_sector - 1)) == 0 && ((p_file->cursor.file_sector_index & (p_vol->bpb.sectors_per_cluster - 1))) == 0) {
            if (p_file->cursor.file_sector_index != 0) {
                p_file->p_sfd->ffd.last_access_cluster.chain_index = (p_file->cursor.file_sector_index - 1) >> p_vol->bpb.log2_sectors_per_cluster;
                p_file->p_sfd->ffd.last_access_cluster.cluster = ((sector - 1 - p_vol->bpb.first_data_sector) >> p_vol->bpb.log2_sectors_per_cluster) + 2;
            }

        } else {
            p_file->p_sfd->ffd.last_access_cluster.chain_index = p_file->cursor.file_sector_index >> p_vol->bpb.log2_sectors_per_cluster;
            p_file->p_sfd->ffd.last_access_cluster.cluster = ((sector - p_vol->bpb.first_data_sector) >> p_vol->bpb.log2_sectors_per_cluster) + 2;
        }
    }
}

s32 VFiPFCLUSTER_AppendCluster(struct PF_FILE* p_file, u32 byte, u32* p_success, u32* sector) {
    s32 err;
    struct PF_VOLUME* p_vol;
    u32 num_sector;
    u32 max_appendable_size;
    struct PF_CURSOR save_cursor;
    struct PF_FAT_HINT save_hint;

    *p_success = 0;

    if ((u32)&VFipf_vol_set > (u32)p_file || (u32)&VFipf_vol_set + 0x27FB8 < (u32)p_file) {
        return 10;
    }
    if (!p_file || !p_file->p_sfd || (p_file->stat & 1) == 0 || (p_file->p_sfd->stat & 1) == 0 || (p_file->p_sfd->stat & 2) == 0) {
        return 38;
    }
    if ((p_file->p_sfd->stat & 1) == 0 || (p_file->p_sfd->stat & 2) == 0) {
        return 38;
    }
    if (p_file == 0) {
        p_vol = 0;
    } else {
        p_vol = p_file->p_sfd->dir_entry.p_vol;
    }

    if (!p_vol) {
        return 38;
    }

    save_cursor = p_file->cursor;
    save_hint = p_file->hint;
    p_file->p_sfd->ffd.p_hint = &p_file->hint;

    *sector = (u32)-1;
    if ((p_vol->fsi_flag & 4) != 0 && (p_vol->num_free_clusters != (u32)-1) && (p_vol->num_free_clusters == 0)) {
        return 6;
    }

    VFiPFFILE_Cursor_MoveToClusterEnd(p_file, p_file->p_sfd->dir_entry.file_size + byte);
    if (p_file->cursor.position == (u32)-1) {
        *p_success = 0;
        return 37;
    }

    err = VFiPFFAT_GetSectorAllocated(&p_file->p_sfd->ffd, p_file->cursor.file_sector_index, byte, sector, &num_sector);
    if (err) {
        p_file->cursor = save_cursor;
        p_file->hint = save_hint;
        return err;
    } else {
        p_file->cursor = save_cursor;
        p_file->hint = save_hint;

        max_appendable_size = num_sector << p_vol->bpb.log2_bytes_per_sector;
        if (byte < max_appendable_size) {
            max_appendable_size = byte;
        }

        *p_success = max_appendable_size;
        return 0;
    }
}

s32 VFiPFCLUSTER_GetAppendSize(struct PF_FILE* p_file, u32* p_size) {
    struct PF_VOLUME* p_vol;
    u32 cluster_size;
    u32 file_cluster_size;
    u32 total_allocated_size;
    u32 file_end_cluster;
    u32 unused_cluster;
    u32 next_cluster;
    u32 num_append_cluster;
    u32 sig_eoc;
    s32 err;

    *p_size = 0;

    if ((u32)&VFipf_vol_set > (u32)p_file || (u32)&VFipf_vol_set + 0x27FB8 < (u32)p_file) {
        return 10;
    }

    if (!p_file || !p_file->p_sfd || (p_file->stat & 1) == 0 || (p_file->p_sfd->stat & 1) == 0 || (p_file->p_sfd->stat & 2) == 0) {
        return 38;
    }

    if ((p_file->p_sfd->stat & 1) == 0 || (p_file->p_sfd->stat & 2) == 0) {
        return 38;
    }

    if (p_file == 0) {
        p_vol = 0;
    } else {
        p_vol = p_file->p_sfd->dir_entry.p_vol;
    }

    if (!p_vol) {
        return 38;
    }

    cluster_size = p_vol->bpb.bytes_per_sector << p_vol->bpb.log2_sectors_per_cluster;

    if (p_file->p_sfd->dir_entry.start_cluster != 0) {
        if (p_file->p_sfd->dir_entry.file_size % cluster_size) {
            err = cluster_size - p_file->p_sfd->dir_entry.file_size % cluster_size;
        } else {
            err = 0;
        }

        file_cluster_size = p_file->p_sfd->dir_entry.file_size + err;
        if (p_file->p_sfd->ffd.last_cluster.max_chain_index) {
            total_allocated_size = ((p_file->p_sfd->ffd.last_cluster.max_chain_index + 1) * cluster_size);
        } else {
            if (p_file->p_sfd->dir_entry.file_size != 0) {
                err = VFiPFFAT_TraceClustersChain(&p_file->p_sfd->ffd, p_file->p_sfd->dir_entry.start_cluster, p_file->p_sfd->dir_entry.file_size, &file_end_cluster, &unused_cluster);
                if (err) {
                    return err;
                }
            } else {
                unused_cluster = p_file->p_sfd->dir_entry.start_cluster;
            }

            sig_eoc = VFiPFFAT_GetValueOfEOC2(p_vol);
            num_append_cluster = 0;

            while (unused_cluster != sig_eoc) {
                num_append_cluster++;
                err = VFiPFFAT_ReadValueToSpecifiedCluster(p_vol, unused_cluster, &next_cluster);
                if (err != 0) {
                    return err;
                }
                unused_cluster = next_cluster;
            }

            total_allocated_size = (file_cluster_size + num_append_cluster * cluster_size);
        }
        *p_size = total_allocated_size - file_cluster_size;
    }
    return 0;
}
