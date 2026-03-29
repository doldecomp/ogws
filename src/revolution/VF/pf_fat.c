#include <revolution/VF.h>

const struct {
    u32 bad;
    u32 eoc1;
    u32 eoc2;
    u32 fat0_mask;
    u32 fat1;
} fat_special_values[3] = {
    {0xFF7, 0xFF8, 0xFFF, 0xF00, 0xFFF},                     // FAT12
    {0xFFF7, 0xFFF8, 0xFFFF, 0xFF00, 0xFFFF},                // FAT16
    {0xFFFFFF7, 0xFFFFFF8, 0xFFFFFFF, 0xFFFFF00, 0xFFFFFFF}  // FAT32
};

static s32 VFiPFFAT_RefreshFSINFO(PF_VOLUME* p_vol);
s32 VFiPFFAT_ReadFATSector(struct PF_VOLUME* p_vol, struct PF_CACHE_PAGE** p_page, u32 cluster);
s32 VFiPFFAT_SearchForNumFreeClusters(struct PF_VOLUME* p_vol, u32 start_cluster, u32 end_cluster, u32 num_cluster, u32* p_start_free_cluster, u32* p_last_free_cluster);
s32 VFiPFFAT_FindClusterLink(struct PF_FFD* p_ffd, u32 chain_index, u32* p_cluster, u32* is_found);
s32 VFiPFFAT_FindClusterLinkPage(struct PF_FFD* p_ffd, u32 chain_index, u32* p_cluster, u32* is_found, struct PF_CACHE_PAGE* p_page);
s32 VFiPFFAT_ReadClusterPage(struct PF_FFD* p_ffd, u32 cluster, u32 chain_index, u32* next_cluster, u32* chk_clstlnk, struct PF_CACHE_PAGE** p_page);
s32 VFiPFFAT_WriteCluster(struct PF_FFD* p_ffd, u32 cluster, u32 chain_index, u32 next_cluster, u32 use_clstlnk);
s32 VFiPFFAT_WriteClusterPage(struct PF_FFD* p_ffd, u32 cluster, u32 chain_index, u32 next_cluster, u32 use_clstlnk, struct PF_CACHE_PAGE** p_page);
s32 VFiPFFAT_GetClusterInChain(struct PF_FFD* p_ffd, u32 chain_index, u32 mode, u32 num_cluster, u32* locate_start, u32* locate_end);
s32 VFiPFFAT_GetClusterContinuousSectorInChain(struct PF_FFD* p_ffd, u32 initial_cluster, u32 chain_index, u32 size, u32* p_num_sector);
s32 VFiPFFAT_GetClusterAllocatedInChain(struct PF_FFD* p_ffd, u32 initial_cluster, u32 chain_index, u32 size, u32* p_num_clusters);
s32 VFiPFFAT_GetClusterSpecified(struct PF_FFD* p_ffd, u32 chain_index, u32 may_allocate, u32* p_cluster);
s32 VFiPFFAT_GetClusterAllocated(struct PF_FFD* p_ffd, u32 chain_index, u32 num_cluster, u32* p_cluster, u32* p_num_cluster);
s32 VFiPFFAT_GetSector(struct PF_FFD* p_ffd, u32 file_sector_index, u32 mode, u32 size, u32* p_sector, u32* p_num_sector);
s32 VFiPFFAT_UpdateFATEntry(struct PF_VOLUME* p_vol, struct PF_CACHE_PAGE* p_page);
s32 VFiPFFAT_UpdateAlternateFATEntry(struct PF_VOLUME* p_vol, u8* p_buf, u32 sector, u32 size);
s32 VFiPFFAT_GetSectorSpecified(struct PF_FFD* p_ffd, u32 file_sector_index, u32 may_allocate, u32* p_sector);
s32 VFiPFFAT_GetSectorAllocated(struct PF_FFD* p_ffd, u32 file_sector_index, u32 size, u32* p_sector, u32* p_num_sector);
s32 VFiPFFAT_GetContinuousSector(struct PF_FFD* p_ffd, u32 file_sector_index, u32 size, u32* p_sector, u32* p_num_sector);
s32 VFiPFFAT_CountAllocatedClusters(struct PF_FFD* p_ffd, u32 size, u32* p_num_alloc_clusters);
s32 VFiPFFAT_CountFreeClusters(struct PF_VOLUME* p_vol, u32* p_num_free_clusters);
s32 VFiPFFAT_FreeChain(struct PF_FFD* p_ffd, u32 start_cluster, u32 chain_index, u32 size);
s32 VFiPFFAT_GetBeforeChain(struct PF_VOLUME* p_vol, u32 start_cluster, u32 lActive, u32* p_cluster);
s32 VFiPFFAT_InitFATRegion(struct PF_VOLUME* p_vol);
s32 VFiPFFAT_MakeRootDir(struct PF_VOLUME* p_vol);
void VFiPFFAT_InitHint(struct PF_FAT_HINT* p_hint);
s32 VFiPFFAT_TraceClustersChain(struct PF_FFD* p_ffd, u32 start_clst, u32 size, u32* p_target_clst, u32* p_next_clst);
s32 VFiPFFAT_ReadValueToSpecifiedCluster(struct PF_VOLUME* p_vol, u32 cluster, u32* value);
s32 VFiPFFAT_ResetFFD(struct PF_FFD* p_ffd, u32* p_start_cluster);
s32 VFiPFFAT_InitFFD(struct PF_FFD* p_ffd, struct PF_FAT_HINT* p_hint, struct PF_VOLUME* p_vol, u32* p_start_cluster);
s32 VFiPFFAT_FinalizeFFD(struct PF_FFD* p_ffd);
u32 VFiPFFAT_GetValueOfEOC2(struct PF_VOLUME* p_vol);

// Other functions called by main functions. These should NOT need to be implemented. They are here for reference only.
s32 VFiPFCACHE_ReadFATPage(struct PF_VOLUME* p_vol, u32 sector, struct PF_CACHE_PAGE** pp_page);
s32 VFiPFFAT12_ReadFATEntryPage(struct PF_VOLUME* p_vol, u16 cluster, u32* p_value, struct PF_CACHE_PAGE** pp_page);
s32 VFiPFFAT16_ReadFATEntryPage(struct PF_VOLUME* p_vol, u32 cluster, u32* p_value, struct PF_CACHE_PAGE** pp_page);
s32 VFiPFFAT32_ReadFATEntryPage(struct PF_VOLUME* p_vol, u32 cluster, u32* p_value, struct PF_CACHE_PAGE** pp_page);
s32 VFiPFFAT12_WriteFATEntry(struct PF_VOLUME* p_vol, u16 cluster, u16 value);
s32 VFiPFFAT16_WriteFATEntry(struct PF_VOLUME* p_vol, u32 cluster, u32 value);
s32 VFiPFFAT32_WriteFATEntry(struct PF_VOLUME* p_vol, u32 cluster, u32 value);
s32 VFiPFFAT12_WriteFATEntryPage(struct PF_VOLUME* p_vol, u16 cluster, u16 value, struct PF_CACHE_PAGE** pp_page);
s32 VFiPFFAT16_WriteFATEntryPage(struct PF_VOLUME* p_vol, u32 cluster, u32 value, struct PF_CACHE_PAGE** pp_page);
s32 VFiPFFAT32_WriteFATEntryPage(struct PF_VOLUME* p_vol, u32 cluster, u32 value, struct PF_CACHE_PAGE** pp_page);
s32 VFiPFCACHE_WriteFATPage(struct PF_VOLUME* p_vol, struct PF_CACHE_PAGE* p_page);
s32 VFiPFDRV_StoreFreeCountToFSINFO(struct PF_VOLUME* p_vol);
s32 VFiPFDRV_lwrite(struct PF_VOLUME* p_vol, const u8* buf, u32 sector, u32 num_sectors, u32* p_num_success);
s32 VFiPFDRV_GetFSINFOInformation(struct PF_VOLUME* p_vol);
s32 VFiPFCACHE_AllocateFATPage(struct PF_VOLUME* p_vol, u32 sector, struct PF_CACHE_PAGE** pp_page);
void* VFipf_memset(void* dst, s32 c, u32 length);
s32 VFiPFCACHE_WriteFATSectorAndFreeIfNeeded(struct PF_VOLUME* p_vol, const u8* p_buf, u32 sector);
void VFiPFCACHE_FreeFATPage(struct PF_VOLUME* p_vol, struct PF_CACHE_PAGE* p_page);
s32 VFiPFCACHE_FlushFATCache(struct PF_VOLUME* p_vol);
s32 VFiPFCACHE_AllocateDataPage(struct PF_VOLUME* p_vol, u32 sector, struct PF_CACHE_PAGE** pp_page);
s32 VFiPFSEC_WriteData(struct PF_VOLUME* p_vol, const u8* p_buf, u32 sector, u16 offset, u32 size, u32* p_success_size, u32 set_sig);
void VFiPFCACHE_FreeDataPage(struct PF_VOLUME* p_vol, struct PF_CACHE_PAGE* p_page);
s32 VFiPFFAT12_ReadFATEntry(struct PF_VOLUME* p_vol, u16 cluster, u32* p_value);
s32 VFiPFFAT16_ReadFATEntry(struct PF_VOLUME* p_vol, u32 cluster, u32* p_value);
s32 VFiPFFAT32_ReadFATEntry(struct PF_VOLUME* p_vol, u32 cluster, u32* p_value);

static s32 VFiPFFAT_ReadFATEntry(struct PF_VOLUME* p_vol, u32 cluster, u32* p_value) {
    switch (p_vol->bpb.fat_type) {
        case FAT_12:
            return VFiPFFAT12_ReadFATEntry(p_vol, cluster, p_value);
        case FAT_16:
            return VFiPFFAT16_ReadFATEntry(p_vol, cluster, p_value);
        case FAT_32:
            return VFiPFFAT32_ReadFATEntry(p_vol, cluster, p_value);
        default:
            break;
    }

    *p_value = -1;
    return 15;
}

static s32 VFiPFFAT_ReadFATEntryPage(struct PF_VOLUME* p_vol, u32 cluster, u32* p_value, struct PF_CACHE_PAGE** p_page) {
    s32 err;
    err = 0xf;
    switch (p_vol->bpb.fat_type) {
        case FAT_12:
            return VFiPFFAT12_ReadFATEntryPage(p_vol, (u16)cluster, p_value, p_page);
        case FAT_16:
            return VFiPFFAT16_ReadFATEntryPage(p_vol, cluster, p_value, p_page);
        case FAT_32:
            return VFiPFFAT32_ReadFATEntryPage(p_vol, cluster, p_value, p_page);
        default:
            break;
    }
    return err;
}

static s32 VFiPFFAT_WriteFATEntry(struct PF_VOLUME* p_vol, u32 cluster, u32 value) {
    switch (p_vol->bpb.fat_type) {
        case FAT_12:
            if (value > 0xFFF) {
                return 16;
            }
            return VFiPFFAT12_WriteFATEntry(p_vol, (u16)cluster, (u16)value);
        case FAT_16:
            if (value > 0xFFFF) {
                return 16;
            }
            return VFiPFFAT16_WriteFATEntry(p_vol, cluster, value);
        case FAT_32:
            if (value > 0x0FFFFFFF) {
                return 16;
            }
            return VFiPFFAT32_WriteFATEntry(p_vol, cluster, value);
        default:
            break;
    }
    return 15;
}

s32 VFiPFFAT_ReadFATSector(struct PF_VOLUME* p_vol, struct PF_CACHE_PAGE** p_page, u32 cluster) {
    s32 err;
    u32 offset;
    u32 current_fat;
    s32 result;
    u32 sector;

    switch (p_vol->bpb.fat_type) {
        case FAT_12:
            offset = (u16)(cluster + (cluster >> 1));
            break;
        case FAT_16:
            offset = cluster * 2;
            break;
        case FAT_32:
            offset = cluster * 4;
            break;
        default:
            return 15;
    }

    sector = (u16)(p_vol->bpb.active_FAT_sector + (offset >> p_vol->bpb.log2_bytes_per_sector));

    if (p_vol->bpb.ext_flags & 0x80) {
        current_fat = (p_vol->bpb.ext_flags & 7);
    } else {
        current_fat = 1;
    }

    while (1) {
        err = VFiPFCACHE_ReadFATPage(p_vol, sector, p_page);
        if (err == 0x1000 && p_vol->p_callback != NULL) {
            result = ((s32 (*)(s32))p_vol->p_callback)(p_vol->last_driver_error);
            if (result != 0) {
                if (result == 1 && p_vol->bpb.num_active_FATs >= 2 && current_fat < p_vol->bpb.num_active_FATs) {
                    current_fat++;
                    sector += p_vol->bpb.sectors_per_FAT;
                    goto skip;
                }
            } else {
                goto skip;
            }
        }

        if (err) {
            return err;
        }

    skip:
        if (!err) {
            return err;
        }
    }
}

static s32 VFiPFFAT_WriteFATEntryPage(struct PF_VOLUME* p_vol, u32 cluster, u32 value, struct PF_CACHE_PAGE** p_page) {
    switch (p_vol->bpb.fat_type) {
        case FAT_12:
            if (value > 0xFFF) {
                return 16;
            }
            return VFiPFFAT12_WriteFATEntryPage(p_vol, (u16)cluster, (u16)value, p_page);
        case FAT_16:
            if (value > 0xFFFF) {
                return 16;
            }
            return VFiPFFAT16_WriteFATEntryPage(p_vol, cluster, value, p_page);
        case FAT_32:
            if (value > 0x0FFFFFFF) {
                return 16;
            }
            return VFiPFFAT32_WriteFATEntryPage(p_vol, cluster, value, p_page);
        default:
            break;
    }
    return 15;
}

s32 VFiPFFAT_SearchForNumFreeClusters(struct PF_VOLUME* p_vol, u32 start_cluster, u32 end_cluster, u32 num_cluster, u32* p_start_free_cluster, u32* p_last_free_cluster) {
    u32 upper_bound_cluster;
    u32 fat_entry;
    u32 success_num;
    u32 save_start_cluster;
    u32 save_success_num;
    s32 err;
    u32 search_flg;
    u32 temp_start_cluster;
    struct PF_CACHE_PAGE* p_page;

    search_flg = 0;
    *p_start_free_cluster = -1;
    *p_last_free_cluster = -1;
    success_num = 0;
    save_start_cluster = -1;
    save_success_num = 0;
    upper_bound_cluster = p_vol->bpb.num_clusters + 2;

    if (start_cluster < 2 || start_cluster >= upper_bound_cluster) {
        start_cluster = 2;
    }

    if (end_cluster < 2 || end_cluster >= upper_bound_cluster) {
        end_cluster = upper_bound_cluster - 1;
    }

    temp_start_cluster = start_cluster;
    err = VFiPFFAT_ReadFATSector(p_vol, &p_page, start_cluster);
    if (err) {
        return err;
    }
    p_page->option = 0;

    while (start_cluster <= end_cluster) {
        if (upper_bound_cluster <= start_cluster) {
            start_cluster = 2;
        }
        err = VFiPFFAT_ReadFATEntryPage(p_vol, start_cluster, &fat_entry, &p_page);
        if (err) {
            return err;
        }

        if (fat_entry == 0) {
            if (*p_start_free_cluster == -1) {
                *p_start_free_cluster = start_cluster;
            }
            success_num++;
            if (success_num >= num_cluster) {
                *p_last_free_cluster = start_cluster;
                return 0;
            }
        } else {
            if (save_success_num < success_num) {
                save_start_cluster = *p_start_free_cluster;
                save_success_num = success_num;
            }
            *p_start_free_cluster = -1;
            success_num = 0;
        }

        start_cluster++;
        if (search_flg == 0 && success_num == 0 && start_cluster > 2 && start_cluster == end_cluster) {
            end_cluster = temp_start_cluster;
            start_cluster = 2;
            search_flg = 1;
        }
    }

    if (save_success_num < success_num) {
        save_start_cluster = *p_start_free_cluster;
        save_success_num = success_num;
    }

    if (save_success_num != 0) {
        *p_start_free_cluster = save_start_cluster;
        *p_last_free_cluster = save_start_cluster;
        *p_last_free_cluster = ((*p_last_free_cluster) + save_success_num) - 1;
    }
    return 0;
}

static s32 VFiPFFAT_UpdateClusterLink(struct PF_FFD* p_ffd, u32 cluster, u32 chain_index) {
    if (p_ffd->cluster_link.max_count > p_ffd->cluster_link.position && p_ffd->cluster_link.max_count) {
        if (chain_index == p_ffd->cluster_link.position * (p_ffd->cluster_link.interval + 1)) {
            p_ffd->cluster_link.interval_offset = 0;
            p_ffd->cluster_link.buffer[p_ffd->cluster_link.position] = cluster;
            ++p_ffd->cluster_link.position;
        } else {
            ++p_ffd->cluster_link.interval_offset;
        }
        p_ffd->cluster_link.save_index = chain_index;
    }
    return 0;
}

static s32 VFiPFFAT_ClearClusterLink(struct PF_FFD* p_ffd, u32 chain_index) {
    u32 position; // Present in DWARF but unused here.
    u32 offset;

    offset = chain_index / (p_ffd->cluster_link.interval + 1);
    if (p_ffd->cluster_link.max_count >= offset) {
        if (!(chain_index % (p_ffd->cluster_link.interval + 1))) {
            p_ffd->cluster_link.buffer[offset] = 0;
        }
        if (p_ffd->cluster_link.save_index >= chain_index) {
            p_ffd->cluster_link.position = (chain_index - 1) / (p_ffd->cluster_link.interval + 1);
            p_ffd->cluster_link.interval_offset = (chain_index - 1) % (p_ffd->cluster_link.interval + 1);
            p_ffd->cluster_link.save_index = chain_index - 1;
        }
    }
    return 0;
}

s32 VFiPFFAT_FindClusterLink(struct PF_FFD* p_ffd, u32 chain_index, u32* p_cluster, u32* is_found) {
    u32 current_cluster;
    u32 next_cluster;
    u32 position;
    u32 offset;
    u32 i;
    s32 err;
    struct PF_CACHE_PAGE* p_page;

    err = 0;
    next_cluster = -1;
    *is_found = 0;
    if (p_ffd->cluster_link.position == 0) {
        return 0;
    }
    if (p_ffd->cluster_link.save_index >= chain_index) {
        position = chain_index / (p_ffd->cluster_link.interval + 1);
        offset = chain_index % (p_ffd->cluster_link.interval + 1);

        if (offset == 0) {
            *p_cluster = p_ffd->cluster_link.buffer[position];
            *is_found = 1;
        } else {
            current_cluster = p_ffd->cluster_link.buffer[position];
            err = VFiPFFAT_ReadFATSector(p_ffd->p_vol, &p_page, current_cluster);
            if (err) {
                return err;
            }
            for (i = offset; i != 0; i--) {
                err = VFiPFFAT_ReadFATEntryPage(p_ffd->p_vol, current_cluster, &next_cluster, &p_page);
                if (err) {
                    return err;
                }
                if (next_cluster == 0) {
                    return 13;
                }
                current_cluster = next_cluster;
            }
            if (next_cluster == 0) {
                return 13;
            }
            if (next_cluster == fat_special_values[p_ffd->p_vol->bpb.fat_type].eoc2) {
                return 0;
            }
            *p_cluster = next_cluster;
            *is_found = 1;
        }
        err = 0;
    } else {
        return 0;
    }
    return err;
}

s32 VFiPFFAT_FindClusterLinkPage(struct PF_FFD* p_ffd, u32 chain_index, u32* p_cluster, u32* is_found, struct PF_CACHE_PAGE* p_page) {
    u32 current_cluster;
    u32 next_cluster;
    u32 position;
    u32 offset;
    u32 i;
    s32 err;

    err = 0;
    next_cluster = -1;
    *is_found = 0;

    if (p_ffd->cluster_link.position == 0) {
        return 0;
    }

    if (p_ffd->cluster_link.save_index >= chain_index) {
        position = chain_index / (p_ffd->cluster_link.interval + 1);
        offset = chain_index % (p_ffd->cluster_link.interval + 1);

        if (offset == 0) {
            *p_cluster = p_ffd->cluster_link.buffer[position];
            *is_found = 1;
        } else {
            current_cluster = p_ffd->cluster_link.buffer[position];
            for (i = offset; i != 0; i--) {
                err = VFiPFFAT_ReadFATEntryPage(p_ffd->p_vol, current_cluster, &next_cluster, &p_page);
                if (err) {
                    return err;
                }
                if (next_cluster == 0) {
                    return 13;
                }
                current_cluster = next_cluster;
            }
            if (next_cluster == 0) {
                return 13;
            }
            if (next_cluster == fat_special_values[p_ffd->p_vol->bpb.fat_type].eoc2) {
                return 0;
            }
            *p_cluster = next_cluster;
            *is_found = 1;
        }
        err = 0;
    } else {
        return 0;
    }
    return err;
}

s32 VFiPFFAT_ReadClusterPage(struct PF_FFD* p_ffd, u32 cluster, u32 chain_index, u32* next_cluster, u32* chk_clstlnk, struct PF_CACHE_PAGE** p_page) {
    s32 err;

    *next_cluster = -1;
    if (p_ffd->cluster_link.buffer != NULL) {
        if (*chk_clstlnk == 1) {
            err = VFiPFFAT_FindClusterLinkPage(p_ffd, chain_index, next_cluster, chk_clstlnk, *p_page);
            if (err != 0) {
                return err;
            }
        }
    }

    if (p_ffd->cluster_link.buffer == NULL || (*chk_clstlnk == 0)) {
        err = VFiPFFAT_ReadFATEntryPage(p_ffd->p_vol, cluster, next_cluster, p_page);
        if (err) {
            return err;
        }
        if (*next_cluster == 0) {
            return 13;
        }
        if (*next_cluster == -1) {
            return 6;
        }

        if (p_ffd->cluster_link.buffer != NULL) {
            if (*next_cluster != fat_special_values[p_ffd->p_vol->bpb.fat_type].eoc2) {
                VFiPFFAT_UpdateClusterLink(p_ffd, *next_cluster, chain_index);
            }
        }
    }
    return 0;
}

s32 VFiPFFAT_WriteCluster(struct PF_FFD* p_ffd, u32 cluster, u32 chain_index, u32 next_cluster, u32 use_clstlnk) {
    s32 err;
    u32 access_cluster;

    // TODO(Alex9303): dumb hack to prevent inlining
    s32 i;
    for (i = 0; i < 0; i++) {
    }

    err = VFiPFFAT_WriteFATEntry(p_ffd->p_vol, cluster, next_cluster);
    if (err) {
        return err;
    }
    if (p_ffd->cluster_link.buffer && use_clstlnk == 1) {
        if (next_cluster == 0) {
            VFiPFFAT_ClearClusterLink(p_ffd, chain_index);
        } else {
            if (cluster != fat_special_values[p_ffd->p_vol->bpb.fat_type].eoc2) {
                err = VFiPFFAT_FindClusterLink(p_ffd, chain_index, &access_cluster, &use_clstlnk);
                if (err) {
                    return err;
                }
                if (!use_clstlnk) {
                    VFiPFFAT_UpdateClusterLink(p_ffd, cluster, chain_index);
                }
            }
        }
    }
    return 0;
}

s32 VFiPFFAT_WriteClusterPage(struct PF_FFD* p_ffd, u32 cluster, u32 chain_index, u32 next_cluster, u32 use_clstlnk, struct PF_CACHE_PAGE** p_page) {
    s32 err;
    u32 access_cluster;

    // TODO(Alex9303): dumb hack to prevent inlining
    s32 i;
    for (i = 0; i < 0; i++) {
    }

    err = VFiPFFAT_WriteFATEntryPage(p_ffd->p_vol, cluster, next_cluster, p_page);
    if (err) {
        return err;
    }
    if (p_ffd->cluster_link.buffer && use_clstlnk == 1) {
        if (next_cluster == 0) {
            VFiPFFAT_ClearClusterLink(p_ffd, chain_index);
        } else {
            if (cluster != fat_special_values[p_ffd->p_vol->bpb.fat_type].eoc2) {
                err = VFiPFFAT_FindClusterLinkPage(p_ffd, chain_index, &access_cluster, &use_clstlnk, *p_page);
                if (err) {
                    return err;
                }
                if (!use_clstlnk) {
                    err = VFiPFFAT_UpdateClusterLink(p_ffd, cluster, chain_index);
                }
            }
        }
    }
    return 0;
}

s32 VFiPFFAT_DoAllocateChain(struct PF_FFD* p_ffd, u32 chain_len, u32 chain_index, u32* p_chain_start, u32* p_last_allocated) {
    struct PF_VOLUME* p_vol;
    u32 eoc2;
    enum FatType fat_type;
    u32 first_allocated_cluster;
    u32 last_allocated_cluster;
    u32 start_cluster;
    s32 err;
    struct PF_CACHE_PAGE* p_page;

    s32 i;

    p_vol = p_ffd->p_vol;
    fat_type = p_vol->bpb.fat_type;
    eoc2 = fat_special_values[fat_type].eoc2;
    *p_chain_start = -1;
    *p_last_allocated = -1;
    last_allocated_cluster = -1;

    err = VFiPFFAT_SearchForNumFreeClusters(p_vol, p_vol->last_free_cluster, -1, chain_len, &first_allocated_cluster, &last_allocated_cluster);
    if (err) {
        return err;
    }
    if (first_allocated_cluster == -1) {
        return 0;
    }

    err = VFiPFFAT_ReadFATSector(p_vol, &p_page, first_allocated_cluster);
    if (err) {
        return err;
    }

    p_page->option = 0;
    for (i = first_allocated_cluster; i < last_allocated_cluster; i++) {
        err = VFiPFFAT_WriteClusterPage(p_ffd, i, chain_index, i + 1, 1, &p_page);
        if (err) {
            return err;
        }
        if ((p_vol->fsi_flag & 4) && p_vol->num_free_clusters != -1 && p_vol->num_free_clusters != 0) {
            if (p_vol->bpb.fat_type != FAT_32 || last_allocated_cluster != p_vol->bpb.root_dir_cluster) {
                p_vol->num_free_clusters--;
            }
        }
        if (*p_chain_start == -1) {
            *p_chain_start = i;
        }
        *p_last_allocated = i;
        chain_index++;
    }

    if (last_allocated_cluster != -1) {
        err = VFiPFFAT_WriteClusterPage(p_ffd, last_allocated_cluster, chain_index, eoc2, 1, &p_page);
        if (err) {
            return err;
        }
        if (*p_chain_start == -1) {
            *p_chain_start = i;
        }
        *p_last_allocated = i;
        if (p_vol->num_free_clusters != -1 && p_vol->num_free_clusters != 0) {
            if (p_vol->bpb.fat_type != FAT_32 || last_allocated_cluster != p_vol->bpb.root_dir_cluster) {
                p_vol->num_free_clusters--;
            }
        }
    }

    p_vol->last_free_cluster = last_allocated_cluster + 1;
    p_ffd->last_cluster.num_last_cluster = last_allocated_cluster;
    p_ffd->last_cluster.max_chain_index = chain_index;
    *p_last_allocated = last_allocated_cluster;

    err = VFiPFFAT_UpdateFATEntry(p_vol, p_page);
    if (err != 0) {
        return err;
    }

    if (p_vol->bpb.fat_type == FAT_32 && (p_vol->fsi_flag & 2)) {
        if (VFiPFFAT_RefreshFSINFO(p_vol)) {
            p_vol->num_free_clusters = -1;
            p_vol->fsi_flag &= ~4;
        }
    }
    return 0;
}

static s32 VFiPFFAT_AllocateChain(PF_FFD* p_ffd, u32 chain_len, u32 chain_index, u32* p_chain_start, u32* p_last_allocated) {
    int err = 0;

    err = VFiPFFAT_DoAllocateChain(p_ffd, chain_len, chain_index, p_chain_start, p_last_allocated);
    if (err) {
        if (*p_chain_start != -1) {
            VFiPFFAT_FreeChain(p_ffd, *p_chain_start, chain_index, -1);
        }
        *p_chain_start = -1;
        *p_last_allocated = -1;
        return err;
    }
    return 0;
}

s32 VFiPFFAT_GetClusterInChain(struct PF_FFD* p_ffd, u32 chain_index, u32 mode, u32 num_cluster, u32* locate_start, u32* locate_end) {
    s32 err;
    u32 bad;
    u32 eoc1;
    u32 current_cluster;
    u32 next_cluster;
    u32 trace_cnt;
    u32 append_cnt;
    u32 search_index;
    u32* p_chain_start;
    u32 chain_start;
    u32 check_use;
    struct PF_CACHE_PAGE* p_page;

    p_page = 0;
    bad = fat_special_values[p_ffd->p_vol->bpb.fat_type].bad;
    eoc1 = fat_special_values[p_ffd->p_vol->bpb.fat_type].eoc1;
    *locate_end = -1;
    *locate_start = -1;

    if (p_ffd->last_access_cluster.chain_index != 0 && p_ffd->last_access_cluster.chain_index <= chain_index) {
        chain_start = p_ffd->last_access_cluster.cluster;
        p_chain_start = &chain_start;
        trace_cnt = chain_index - p_ffd->last_access_cluster.chain_index;
        search_index = p_ffd->last_access_cluster.chain_index + 1;
    } else {
        p_chain_start = p_ffd->p_start_cluster;
        trace_cnt = chain_index;
        search_index = 1;
    }

    current_cluster = *p_chain_start;
    next_cluster = *p_chain_start;

    if (mode == 2) {
        if (trace_cnt != 0 && num_cluster != 0) {
            trace_cnt += num_cluster - 1;
        } else {
            trace_cnt = num_cluster;
        }
        append_cnt = trace_cnt;
        if (p_ffd->last_cluster.num_last_cluster != 0) {
            trace_cnt = 0;
            append_cnt = p_ffd->last_cluster.max_chain_index + num_cluster - chain_index;
            current_cluster = p_ffd->last_cluster.num_last_cluster;
            next_cluster = fat_special_values[p_ffd->p_vol->bpb.fat_type].eoc2;
            search_index = p_ffd->last_cluster.max_chain_index + 1;
        }
    } else {
        if (mode == 1 && current_cluster == 0) {
            trace_cnt++;
        }
        append_cnt = trace_cnt;
    }

    if (trace_cnt != 0) {
        err = VFiPFFAT_ReadFATSector(p_ffd->p_vol, &p_page, current_cluster);
        if (err) {
            return err;
        }
        p_page->option = 0;
        check_use = 1;

        while (trace_cnt-- != 0 && current_cluster < bad) {
            if (current_cluster != 0) {
                err = VFiPFFAT_ReadClusterPage(p_ffd, current_cluster, search_index, &next_cluster, &check_use, &p_page);
                if (err != 0 && next_cluster != (u32)-1) {
                    return err;
                }
            } else {
                search_index--;
                next_cluster = fat_special_values[p_ffd->p_vol->bpb.fat_type].eoc2;
            }

            if ((next_cluster < 2 || next_cluster >= (p_ffd->p_vol->bpb.num_clusters + 2)) && next_cluster < eoc1) {
                return 14;
            }

            if (mode != 0 && next_cluster >= eoc1) {
                break;
            }

            current_cluster = next_cluster;
            search_index++;
        }
        append_cnt = trace_cnt;
    }

    if (mode != 0 && next_cluster >= eoc1) {
        *locate_start = 0;
        err = VFiPFFAT_AllocateChain(p_ffd, append_cnt + 1, search_index, locate_start, &next_cluster);
        if (err) {
            return err;
        }
        if (next_cluster == -1) {
            return 6;
        }
        if (*p_chain_start == 0) {
            *p_chain_start = *locate_start;
        } else {
            err = VFiPFFAT_WriteCluster(p_ffd, current_cluster, search_index - 1, *locate_start, 1);
            if (err) {
                return err;
            }
        }
        current_cluster = next_cluster;
    }

    *locate_end = current_cluster;
    return 0;
}

inline s32 VFiPFFAT_GetNumberOfCluster(struct PF_FFD* p_ffd, u32 chain_index, u32 may_allocate, u32* p_cluster) {
    s32 err;
    u32 locate_start;
    u32 locate_end;
    u32 mode;

    *p_cluster = -1;
    if (may_allocate) {
        mode = 1;
    } else {
        mode = 0;
    }
    err = VFiPFFAT_GetClusterInChain(p_ffd, chain_index, mode, 0, &locate_start, &locate_end);
    if (err) {
        return err;
    }
    if (locate_end >= 2 && locate_end < p_ffd->p_vol->bpb.num_clusters + 2) {
        *p_cluster = locate_end;
    }
    return 0;
}

static s32 VFiPFFAT_GetNumberOfAllocatedCluster(struct PF_FFD* p_ffd, u32 chain_index, u32 num_cluster, u32* p_cluster, u32* p_num_cluster) {
    s32 err;
    u32 locate_start;
    u32 locate_end;

    *p_cluster = -1;
    err = VFiPFFAT_GetClusterInChain(p_ffd, chain_index, 2, num_cluster, &locate_start, &locate_end);
    if (err) {
        return err;
    }
    *p_num_cluster = locate_end - locate_start + 1;
    if (locate_start >= 2 && locate_start < p_ffd->p_vol->bpb.num_clusters + 2) {
        *p_cluster = locate_start;
    }
    return 0;
}

s32 VFiPFFAT_GetClusterContinuousSectorInChain(struct PF_FFD* p_ffd, u32 initial_cluster, u32 chain_index, u32 size, u32* p_num_sector) {
    struct PF_VOLUME* p_vol;
    u32 cluster;
    u32 next_cluster;
    u32 check_use;
    s32 err;
    struct PF_CACHE_PAGE* p_page;

    p_vol = p_ffd->p_vol;
    next_cluster = -1;
    cluster = initial_cluster;
    check_use = 1;
    err = VFiPFFAT_ReadFATSector(p_vol, &p_page, initial_cluster);
    if (err) {
        return err;
    }

    while (next_cluster) {
        err = VFiPFFAT_ReadClusterPage(p_ffd, cluster, chain_index, &next_cluster, &check_use, &p_page);
        if (err) {
            return err;
        }
        if (cluster + 1 != next_cluster) {
            if (next_cluster == fat_special_values[p_vol->bpb.fat_type].eoc2) {
                p_ffd->last_cluster.num_last_cluster = cluster;
                p_ffd->last_cluster.max_chain_index = chain_index - 1;
            }
            break;
        }
        ++p_ffd->p_hint->chain_index;
        p_ffd->p_hint->cluster = next_cluster;
        *p_num_sector += p_vol->bpb.sectors_per_cluster;
        if (*p_num_sector << p_vol->bpb.log2_bytes_per_sector >= size) {
            break;
        }
        cluster = next_cluster;
        ++chain_index;
    }
    return 0;
}

s32 VFiPFFAT_GetClusterAllocatedInChain(struct PF_FFD* p_ffd, u32 initial_cluster, u32 chain_index, u32 size, u32* p_num_clusters) {
    struct PF_VOLUME* p_vol;
    u32 cluster;
    u32 next_cluster;
    u32 total_size;
    u32 check_use;
    s32 err;
    struct PF_CACHE_PAGE* p_page;

    p_vol = p_ffd->p_vol;
    next_cluster = -1;
    cluster = initial_cluster;
    check_use = 1;
    total_size = 0;
    err = VFiPFFAT_ReadFATSector(p_vol, &p_page, initial_cluster);
    if (err) {
        return err;
    }

    while (next_cluster != 0) {
        total_size += (p_vol->bpb.bytes_per_sector << p_vol->bpb.log2_sectors_per_cluster);
        (*p_num_clusters)++;
        if (total_size >= size) {
            break;
        }
        err = VFiPFFAT_ReadClusterPage(p_ffd, cluster, chain_index, &next_cluster, &check_use, &p_page);
        if (err) {
            return err;
        }
        if (next_cluster == fat_special_values[p_vol->bpb.fat_type].eoc2) {
            p_ffd->last_cluster.num_last_cluster = cluster;
            p_ffd->last_cluster.max_chain_index = chain_index - 1;
            break;
        }
        cluster = next_cluster;
        chain_index++;
    }
    return 0;
}

s32 VFiPFFAT_GetClusterSpecified(struct PF_FFD* p_ffd, u32 chain_index, u32 may_allocate, u32* p_cluster) {
    struct PF_VOLUME* p_vol;
    struct PF_FAT_HINT* p_hint;
    u32 fat_type;
    u32 is_found;
    s32 err;

    p_vol = p_ffd->p_vol;
    fat_type = p_vol->bpb.fat_type;
    p_hint = p_ffd->p_hint;

    if (*p_ffd->p_start_cluster == 0 && may_allocate == 0) {
        *p_cluster = -1;
        return 0;
    }

    if (*p_ffd->p_start_cluster == 1) {
        if (fat_type <= FAT_16) {
            *p_cluster = -1;
            return 0;
        }
        *p_ffd->p_start_cluster = p_vol->bpb.root_dir_cluster;
    }

    if (p_ffd->cluster_link.buffer != NULL && may_allocate == 0) {
        err = VFiPFFAT_FindClusterLink(p_ffd, chain_index, p_cluster, &is_found);
        if (err) {
            return err;
        }
        if (is_found == 1) {
            p_hint->file_version = p_ffd->file_version;
            p_hint->chain_index = chain_index;
            p_hint->cluster = *p_cluster;
            return 0;
        }
    }

    *p_cluster = -1;

    err = VFiPFFAT_GetNumberOfCluster(p_ffd, chain_index, may_allocate, p_cluster);
    if (err != 0) {
        return err;
    }

    if (*p_cluster == -1) {
        return 0;
    }

    p_hint->file_version = p_ffd->file_version;
    p_hint->chain_index = chain_index;
    p_hint->cluster = *p_cluster;
    return 0;
}

s32 VFiPFFAT_GetClusterAllocated(PF_FFD* p_ffd, u32 chain_index, u32 num_cluster, u32* p_cluster, u32* p_num_cluster) {
    PF_VOLUME* p_vol;
    PF_FAT_HINT* p_hint;
    int err;

    u32 fat_type;

    p_vol = p_ffd->p_vol;
    fat_type = p_vol->bpb.fat_type;
    p_hint = p_ffd->p_hint;

    if (*p_ffd->p_start_cluster == 1) {
        if (fat_type <= FAT_16) {
            *p_cluster = -1;
            return 0;
        }
        *p_ffd->p_start_cluster = p_vol->bpb.root_dir_cluster;
    }
    err = VFiPFFAT_GetNumberOfAllocatedCluster(p_ffd, chain_index, num_cluster, p_cluster, p_num_cluster);
    if (err) {
        return err;
    }

    if (*p_cluster == -1) {
        return 0;
    }
    p_hint->file_version = p_ffd->file_version;
    p_hint->chain_index = chain_index;
    p_hint->cluster = *p_cluster;
    return 0;
}

static s32 VFiPFFAT_GetSectorInRootDirRegion(PF_VOLUME* p_vol, u32 sector_offset, u32* p_sector) {
    if (p_vol->bpb.fat_type != FAT_12 && (s32)p_vol->bpb.fat_type != FAT_16) {
        return 12;
    }
    if (sector_offset >= p_vol->bpb.num_root_dir_sectors) {
        *p_sector = -1;
        return 0;
    } else {
        *p_sector = p_vol->bpb.first_root_dir_sector + sector_offset;
        return 0;
    }
}

s32 VFiPFFAT_GetSector(struct PF_FFD* p_ffd, u32 file_sector_index, u32 mode, u32 size, u32* p_sector, u32* p_num_sector) {
    s32 err;
    struct PF_VOLUME* p_vol;
    u32 fat_type;
    u32 chain_index;
    u32 cluster;
    u32 num_divide;
    u32 num_remaind;
    u32 num_cluster;
    u32 num_success;

    num_success = 0;
    p_vol = p_ffd->p_vol;
    fat_type = p_vol->bpb.fat_type;

    if (*p_ffd->p_start_cluster == 1 && fat_type <= FAT_16) {
        err = VFiPFFAT_GetSectorInRootDirRegion(p_vol, file_sector_index, p_sector);
        return err ? err : 0;
    } else {
        chain_index = file_sector_index >> p_vol->bpb.log2_sectors_per_cluster;
        if (mode == 2) {
            num_divide = size >> p_vol->bpb.log2_bytes_per_sector;
            num_remaind = (size & (p_vol->bpb.bytes_per_sector - 1)) != 0;
            num_cluster = (num_divide + num_remaind) >> p_vol->bpb.log2_sectors_per_cluster;
            num_cluster += (((num_divide + num_remaind) & (p_vol->bpb.sectors_per_cluster - 1)) != 0);
            err = VFiPFFAT_GetClusterAllocated(p_ffd, chain_index, num_cluster, &cluster, &num_success);
            if (err) {
                return err;
            }
            *p_num_sector = num_success << p_vol->bpb.log2_sectors_per_cluster;
        } else {
            err = VFiPFFAT_GetClusterSpecified(p_ffd, chain_index, mode, &cluster);
            if (err) {
                return err;
            }
            *p_num_sector = 1 << p_vol->bpb.log2_sectors_per_cluster;
        }
        if (cluster == -1) {
            *p_sector = -1;
            err = 0;
        } else {
            *p_sector = p_vol->bpb.first_data_sector + ((cluster - 2) << p_vol->bpb.log2_sectors_per_cluster) + (file_sector_index & (p_vol->bpb.sectors_per_cluster - 1));
            err = 0;
        }
    }
    return err;
}

s32 VFiPFFAT_UpdateFATEntry(struct PF_VOLUME* p_vol, struct PF_CACHE_PAGE* p_page) {
    s32 err = 0;
    if ((p_page->stat & 2) == 2) {
        err = VFiPFCACHE_WriteFATPage(p_vol, p_page);
    }
    return err;
}

s32 VFiPFFAT_UpdateAlternateFATEntry(struct PF_VOLUME* p_vol, u8* p_buf, u32 sector, u32 size) {
    s32 err;
    s32 err2;
    u32 fat_no;
    u32 offset;
    s32 size_copy;
    u32 num_success;
    u32 fat_num;

    err = 0;
    offset = sector - p_vol->bpb.num_reserved_sectors;
    fat_num = offset / p_vol->bpb.sectors_per_FAT;

    // Copy needed in order to match the assembly. Possible missing inline function?
    size_copy = size;
    if ((offset / p_vol->bpb.sectors_per_FAT) != 0) {
        fat_num = offset - (fat_num * p_vol->bpb.sectors_per_FAT);
        fat_no = 0;
    } else {
        fat_num = sector + p_vol->bpb.sectors_per_FAT;
        fat_no = 1;
    }

    while (fat_no < p_vol->bpb.num_active_FATs) {
        err2 = VFiPFDRV_lwrite(p_vol, p_buf, fat_num, size_copy, &num_success);
        if ((err2 != 0) && (err == 0)) {
            err = err2;
        }
        if (num_success != size_copy) {
            err = 17;
        }
        fat_num += p_vol->bpb.sectors_per_FAT;
        fat_no++;
    }

    return err;
}

s32 VFiPFFAT_GetSectorSpecified(struct PF_FFD* p_ffd, u32 file_sector_index, u32 may_allocate, u32* p_sector) {
    s32 err;
    u32 mode;
    u32 num_sector;
    if (!p_ffd) {
        return 10;
    }
    if (!p_ffd->p_hint) {
        return 10;
    }
    if (!p_ffd->file_version) {
        return 10;
    }
    if (p_ffd->p_hint->file_version > p_ffd->file_version) {
        return 10;
    }
    if (p_ffd->p_vol->drv_char < 'A' || p_ffd->p_vol->drv_char > 'Z') {
        return 35;
    }
    if (file_sector_index >= (u32)(0xFFFFFFFF >> p_ffd->p_vol->bpb.log2_bytes_per_sector) + 1) {
        return 37;
    }
    if (may_allocate) {
        mode = 1;
    } else {
        mode = 0;
    }
    err = VFiPFFAT_GetSector(p_ffd, file_sector_index, mode, 0, p_sector, &num_sector);
    if (err) {
        return err;
    }
    return 0;
}

s32 VFiPFFAT_GetSectorAllocated(struct PF_FFD* p_ffd, u32 file_sector_index, u32 size, u32* p_sector, u32* p_num_sector) {
    s32 err;

    if (!p_ffd) {
        return 10;
    }
    if (!p_ffd->p_hint) {
        return 10;
    }
    if (!p_ffd->file_version) {
        return 10;
    }
    if (p_ffd->p_hint->file_version > p_ffd->file_version) {
        return 10;
    }
    if (p_ffd->p_vol->drv_char < 'A' || p_ffd->p_vol->drv_char > 'Z') {
        return 35;
    }
    if (file_sector_index >= (0xFFFFFFFF >> p_ffd->p_vol->bpb.log2_bytes_per_sector) + 1) {
        return 37;
    }
    err = VFiPFFAT_GetSector(p_ffd, file_sector_index, 2u, size, p_sector, p_num_sector);
    if (!err) {
        return 0;
    }
    return err;
}

s32 VFiPFFAT_GetContinuousSector(struct PF_FFD* p_ffd, u32 file_sector_index, u32 size, u32* p_sector, u32* p_num_sector) {
    struct PF_VOLUME* p_vol;
    u32 chain_index;
    u32 cluster;
    s32 err;

    cluster = -1;
    if (!p_ffd) {
        return 10;
    }
    if (!p_ffd->p_hint) {
        return 10;
    }
    if (!p_ffd->file_version) {
        return 10;
    }
    if (p_ffd->p_hint->file_version > p_ffd->file_version) {
        return 10;
    }
    p_vol = p_ffd->p_vol;
    if (p_ffd->p_vol->drv_char < 'A' || p_ffd->p_vol->drv_char > 'Z') {
        return 35;
    }
    if (file_sector_index >= (u32)(0xFFFFFFFF >> p_vol->bpb.log2_bytes_per_sector) + 1) {
        return 37;
    }

    if (*p_sector != -1) {
        cluster = ((*p_sector - p_vol->bpb.first_data_sector) >> p_vol->bpb.log2_sectors_per_cluster) + 2;
    } else {
        err = VFiPFFAT_GetSectorSpecified(p_ffd, file_sector_index, 0, p_sector);
        if (err) {
            return err;
        }
        if (*p_sector != -1) {
            cluster = ((*p_sector - p_vol->bpb.first_data_sector) >> p_vol->bpb.log2_sectors_per_cluster) + 2;
        }
    }

    if (*p_sector != -1) {
        *p_num_sector = p_vol->bpb.first_data_sector + ((cluster - 1) << p_vol->bpb.log2_sectors_per_cluster) - *p_sector;
    } else {
        *p_num_sector = 0;
    }

    if (*p_sector != -1) {
        if ((*p_num_sector << p_vol->bpb.log2_bytes_per_sector) < size) {
            chain_index = (file_sector_index >> p_vol->bpb.log2_sectors_per_cluster) + 1;
            err = VFiPFFAT_GetClusterContinuousSectorInChain(p_ffd, cluster, chain_index, size, p_num_sector);
            if (err) {
                return err;
            }
        }
    }

    return 0;
}

s32 VFiPFFAT_CountAllocatedClusters(struct PF_FFD* p_ffd, u32 size, u32* p_num_alloc_clusters) {
    u32 cluster;
    u32 total_size;
    u32 chain_index;
    s32 err;

    total_size = size;
    *p_num_alloc_clusters = 0;
    if (!p_ffd) {
        return 10;
    }
    if (!p_ffd->p_hint) {
        return 10;
    }
    if (!p_ffd->file_version) {
        return 10;
    }
    if (p_ffd->p_hint->file_version > p_ffd->file_version) {
        return 10;
    }
    if (p_ffd->p_vol->drv_char < 'A' || p_ffd->p_vol->drv_char > 'Z') {
        return 35;
    }
    if (*p_ffd->p_start_cluster < 2) {
        return 0;
    }
    if (p_ffd->last_cluster.num_last_cluster) {
        *p_num_alloc_clusters = p_ffd->last_cluster.max_chain_index + 1;
        return 0;
    }
    if (p_ffd->p_hint->cluster) {
        if (size <= (p_ffd->p_hint->chain_index + 1) << (p_ffd->p_vol->bpb.log2_bytes_per_sector + p_ffd->p_vol->bpb.log2_sectors_per_cluster)) {
            *p_num_alloc_clusters = p_ffd->p_hint->chain_index + 1;
            return 0;
        }
        *p_num_alloc_clusters = p_ffd->p_hint->chain_index;
        cluster = p_ffd->p_hint->cluster;
        chain_index = p_ffd->p_hint->chain_index + 1;
        total_size = size - (p_ffd->p_hint->chain_index << (p_ffd->p_vol->bpb.log2_bytes_per_sector + p_ffd->p_vol->bpb.log2_sectors_per_cluster));
    } else {
        cluster = *p_ffd->p_start_cluster;
        chain_index = 1;
    }
    err = VFiPFFAT_GetClusterAllocatedInChain(p_ffd, cluster, chain_index, total_size, p_num_alloc_clusters);
    if (err) {
        return err;
    }
    return 0;
}

s32 VFiPFFAT_CountFreeClusters(struct PF_VOLUME* p_vol, u32* p_num_free_clusters) {
    u32 free_cluster;
    s32 err;
    u32 next_cluster;
    struct PF_CACHE_PAGE* p_page;

    if (p_vol == NULL) {
        return 10;
    }
    if (p_vol->bpb.fat_type != FAT_12 && p_vol->bpb.fat_type != FAT_16 && p_vol->bpb.fat_type != FAT_32) {
        return 15;
    }
    if ((p_vol->fsi_flag & 4) && p_vol->num_free_clusters != -1) {
        *p_num_free_clusters = p_vol->num_free_clusters;
        return 0;
    }
    *p_num_free_clusters = -1;
    free_cluster = 2;
    if ((p_vol->fsi_flag & 1) && p_vol->bpb.fat_type == FAT_32) {
        err = VFiPFDRV_GetFSINFOInformation(p_vol);
        if (err) {
            return err;
        }
        *p_num_free_clusters = p_vol->num_free_clusters;
    }
    if (*p_num_free_clusters == -1) {
        err = VFiPFFAT_ReadFATSector(p_vol, &p_page, 2);
        if (err) {
            return err;
        }
        p_page->option = 0;
        while (free_cluster >= 2 && free_cluster < p_vol->bpb.num_clusters + 2) {
            err = VFiPFFAT_ReadFATEntryPage(p_vol, free_cluster, &next_cluster, &p_page);
            if (err) {
                return err;
            }
            if (next_cluster == 0) {
                (*p_num_free_clusters)++;
            }
            free_cluster++;
        }
        p_vol->num_free_clusters = *p_num_free_clusters;
        if (p_vol->bpb.fat_type == FAT_32 && (p_vol->fsi_flag & 2)) {
            if (VFiPFFAT_RefreshFSINFO(p_vol)) {
                p_vol->num_free_clusters = -1;
                p_vol->fsi_flag &= ~4;
            }
        }
    }
    p_vol->fsi_flag |= 4;
    return 0;
}

s32 VFiPFFAT_FreeChain(struct PF_FFD* p_ffd, u32 start_cluster, u32 chain_index, u32 size) {
    s32 err;
    struct PF_VOLUME* p_vol;
    u32 eoc1;
    u32 next_cluster;
    u32 file_size;
    u32 clst_size;
    struct PF_CACHE_PAGE* p_page;
    u32 sector;

    u32 current_cluster;
    u32 save_start_cluster;
    u32 save_num_clusters;

    p_vol = p_ffd->p_vol;
    if (p_vol == NULL) {
        return 10;
    }
    if ((start_cluster < 2 || start_cluster >= p_vol->bpb.num_clusters + 2) && start_cluster != 0) {
        return 14;
    }
    if (start_cluster == 0) {
        return 0;
    }

    eoc1 = fat_special_values[p_vol->bpb.fat_type].eoc1;
    if (size != 0) {
        file_size = size;
        clst_size = p_vol->bpb.bytes_per_sector << p_vol->bpb.log2_sectors_per_cluster;
    } else {
        return 0;
    }

    err = VFiPFFAT_ReadFATSector(p_vol, &p_page, start_cluster);
    if (err) {
        return err;
    }
    p_page->option = 1;

    current_cluster = start_cluster;
    next_cluster = start_cluster;
    save_start_cluster = start_cluster;
    save_num_clusters = 1;

    while (current_cluster < eoc1) {
        if (size != 0 && file_size == 0) {
            break;
        }
        sector = p_page->sector;
        err = VFiPFFAT_ReadFATEntryPage(p_vol, current_cluster, &next_cluster, &p_page);
        if (err) {
            return err;
        }
        if (next_cluster == 0) {
            err = VFiPFFAT_UpdateFATEntry(p_vol, p_page);
            if (err) {
                return err;
            }
            return 0;
        }

        if (sector != p_page->sector) {
            err = VFiPFFAT_ReadFATSector(p_vol, &p_page, current_cluster);
            if (err) {
                return err;
            }
        }

        if (chain_index != 0xFFFFFFFF) {
            err = VFiPFFAT_WriteClusterPage(p_ffd, current_cluster, chain_index, 0, 1, &p_page);
            chain_index++;
        } else {
            // err = VFiPFFAT_WriteFATEntryPage(p_vol, current_cluster, 0, &p_page);
            switch (p_vol->bpb.fat_type) {
                case FAT_12:
                    err = VFiPFFAT12_WriteFATEntryPage(p_vol, (u16)current_cluster, 0, &p_page);
                    break;
                case FAT_16:
                    err = VFiPFFAT16_WriteFATEntryPage(p_vol, current_cluster, 0, &p_page);
                    break;
                case FAT_32:
                    err = VFiPFFAT32_WriteFATEntryPage(p_vol, current_cluster, 0, &p_page);
                    break;
                default:
                    err = 15;
                    break;
            }
        }
        if (err) {
            return err;
        }
        save_start_cluster = next_cluster;
        save_num_clusters = 1;

        if (size != 0 && file_size != 0) {
            if (clst_size >= file_size) {
                file_size = 0;
            } else {
                file_size -= clst_size;
            }
        }
        if (p_vol->num_free_clusters != -1) {
            p_vol->num_free_clusters++;
        }
        current_cluster = next_cluster;
    }

    err = VFiPFFAT_UpdateFATEntry(p_vol, p_page);
    if (err) {
        return err;
    }

    if (p_vol->bpb.fat_type == FAT_32 && (p_vol->fsi_flag & 2)) {
        if (VFiPFFAT_RefreshFSINFO(p_vol)) {
            p_vol->num_free_clusters = -1;
            p_vol->fsi_flag &= ~4;
        }
    }
    return 0;
}

s32 VFiPFFAT_GetBeforeChain(struct PF_VOLUME* p_vol, u32 start_cluster, u32 lActive, u32* p_cluster) {
    s32 err;
    u32 eoc1;
    u32 next_cluster;
    struct PF_CACHE_PAGE* p_page;

    if (p_vol == NULL) {
        *p_cluster = -1;
        return 10;
    }
    if (start_cluster < 2 || start_cluster >= p_vol->bpb.num_clusters + 2) {
        *p_cluster = -1;
        return 10;
    }

    eoc1 = fat_special_values[p_vol->bpb.fat_type].eoc1;
    *p_cluster = -1;

    err = VFiPFFAT_ReadFATSector(p_vol, &p_page, start_cluster);
    if (err) {
        return err;
    }

    p_page->option = 0;
    while (start_cluster < eoc1) {
        err = VFiPFFAT_ReadFATEntryPage(p_vol, start_cluster, &next_cluster, &p_page);
        if (err) {
            return err;
        }
        if (lActive == next_cluster) {
            *p_cluster = start_cluster;
            return 0;
        }
        start_cluster--;
        if ((start_cluster < 2 || start_cluster >= p_vol->bpb.num_clusters + 2) && start_cluster < eoc1) {
            *p_cluster = lActive;
            return 0;
        }
    }
    return 13;
}

s32 VFiPFFAT_InitFATRegion(struct PF_VOLUME* p_vol) {
    u32 sector;
    struct PF_CACHE_PAGE* p_page;
    s32 err;

    if (p_vol == NULL) {
        return 10;
    }
    if (p_vol->bpb.fat_type != FAT_12 && p_vol->bpb.fat_type != FAT_16 && p_vol->bpb.fat_type != FAT_32) {
        return 15;
    }
    err = VFiPFCACHE_AllocateFATPage(p_vol, -1, &p_page);
    if (err) {
        return err;
    }

    VFipf_memset(p_page->p_buf, 0, p_vol->bpb.bytes_per_sector);
    for (sector = p_vol->bpb.num_reserved_sectors; sector < p_vol->bpb.first_root_dir_sector; sector++) {
        err = VFiPFCACHE_WriteFATSectorAndFreeIfNeeded(p_vol, p_page->p_buf, sector);
        if (err) {
            VFiPFCACHE_FreeFATPage(p_vol, p_page);
            return err;
        }
    }

    VFiPFCACHE_FreeFATPage(p_vol, p_page);

    err = VFiPFFAT_WriteFATEntry(p_vol, 0, p_vol->bpb.media | fat_special_values[p_vol->bpb.fat_type].fat0_mask);
    if (err) {
        return err;
    }
    err = VFiPFFAT_WriteFATEntry(p_vol, 1, fat_special_values[p_vol->bpb.fat_type].fat1);
    if (err) {
        return err;
    }
    err = VFiPFCACHE_FlushFATCache(p_vol);
    if (err) {
        return err;
    }
    return 0;
}

s32 VFiPFFAT_MakeRootDir(struct PF_VOLUME* p_vol) {
    s32 err;
    u32 sector;
    u32 success_size;
    u32 num_sectors;
    struct PF_CACHE_PAGE* p_page;

    err = VFiPFFAT_WriteFATEntry(p_vol, p_vol->bpb.root_dir_cluster, fat_special_values[p_vol->bpb.fat_type].eoc2);
    if (err) {
        return err;
    }
    err = VFiPFCACHE_FlushFATCache(p_vol);
    if (err) {
        return err;
    }

    err = VFiPFCACHE_AllocateDataPage(p_vol, -1, &p_page);
    if (err) {
        return err;
    }

    VFipf_memset(p_page->p_buf, 0, p_vol->bpb.bytes_per_sector);

    sector = p_vol->bpb.first_data_sector + ((p_vol->bpb.root_dir_cluster - 2) << p_vol->bpb.log2_sectors_per_cluster);

    for (num_sectors = 0; num_sectors < p_vol->bpb.sectors_per_cluster; num_sectors++) {
        err = VFiPFSEC_WriteData(p_vol, p_page->p_buf, sector + num_sectors, 0, p_vol->bpb.bytes_per_sector, &success_size, 0);
        if (err) {
            VFiPFCACHE_FreeDataPage(p_vol, p_page);
            return err;
        }
        if (success_size != p_vol->bpb.bytes_per_sector) {
            VFiPFCACHE_FreeDataPage(p_vol, p_page);
            return 17;
        }
    }

    VFiPFCACHE_FreeDataPage(p_vol, p_page);
    return 0;
}

static s32 VFiPFFAT_RefreshFSINFO(PF_VOLUME* p_vol) {
    s32 err;

    err = 0;
    if (p_vol->bpb.fat_type != FAT_32) {
        return 12;
    }
    if ((p_vol->fsi_flag & 2) == 0) {
        return 36;
    } else if ((p_vol->fsi_flag & 4) != 0) {
        err = VFiPFDRV_StoreFreeCountToFSINFO(p_vol);
    }
    return err;
}

void VFiPFFAT_InitHint(struct PF_FAT_HINT* p_hint) {
    p_hint->chain_index = 0;
    p_hint->cluster = 0;
    p_hint->file_version = 0;
}

s32 VFiPFFAT_TraceClustersChain(struct PF_FFD* p_ffd, u32 start_clst, u32 size, u32* p_target_clst, u32* p_next_clst) {
    s32 err;
    struct PF_VOLUME* p_vol;
    u32 next_cluster;
    u32 save_cluster;
    u32 chain_index;
    u32 clst_size;
    u32 clst_cnt;
    u32 cnt;
    u32 check_use;
    struct PF_CACHE_PAGE* p_page;

    save_cluster = start_clst;

    *p_target_clst = 0;
    *p_next_clst = 0;

    if (!p_ffd) {
        return 10;
    }
    if (!p_ffd->p_hint) {
        return 10;
    }
    if (!p_ffd->file_version) {
        return 10;
    }
    if (p_ffd->p_hint->file_version > p_ffd->file_version) {
        return 10;
    }
    p_vol = p_ffd->p_vol;
    if (p_vol->drv_char < 'A' || p_vol->drv_char > 'Z') {
        return 35;
    }
    if (p_vol == NULL) {
        return 10;
    }
    if (*p_ffd->p_start_cluster < 2) {
        return 0;
    }
    if (start_clst < 2) {
        return 0;
    }
    if (size == 0) {
        return 0;
    }

    if (size == -1 && p_ffd->last_cluster.num_last_cluster != 0) {
        *p_target_clst = p_ffd->last_cluster.num_last_cluster;
        *p_next_clst = fat_special_values[p_vol->bpb.fat_type].eoc2;
        return 0;
    }

    clst_size = p_vol->bpb.bytes_per_sector << p_vol->bpb.log2_sectors_per_cluster;
    clst_cnt = size / clst_size;
    if (size % clst_size) {
        clst_cnt++;
    }

    if (*p_ffd->p_start_cluster == start_clst) {
        chain_index = 1;
    } else {
        chain_index = p_ffd->p_hint->chain_index + 1;
    }

    next_cluster = -1;
    check_use = 1;
    err = VFiPFFAT_ReadFATSector(p_vol, &p_page, start_clst);
    if (err) {
        return err;
    }

    for (cnt = 0; cnt < clst_cnt; cnt++) {
        err = VFiPFFAT_ReadClusterPage(p_ffd, start_clst, chain_index, &next_cluster, &check_use, &p_page);
        if (err) {
            return err;
        }
        save_cluster = start_clst;
        if (next_cluster == fat_special_values[p_vol->bpb.fat_type].eoc2) {
            p_ffd->last_cluster.num_last_cluster = start_clst;
            p_ffd->last_cluster.max_chain_index = chain_index - 1;
            break;
        }
        start_clst = next_cluster;
        chain_index++;
    }

    p_ffd->p_hint->chain_index = chain_index - 1;
    *p_target_clst = save_cluster;
    *p_next_clst = next_cluster;
    return 0;
}

s32 VFiPFFAT_ReadValueToSpecifiedCluster(struct PF_VOLUME* p_vol, u32 cluster, u32* value) {
    s32 err;

    err = VFiPFFAT_ReadFATEntry(p_vol, cluster, value);
    if (err) {
        return err;
    }

    return 0;
}

s32 VFiPFFAT_ResetFFD(struct PF_FFD* p_ffd, u32* p_start_cluster) {
    if (p_ffd == NULL) {
        return 10;
    }
    if (p_start_cluster == NULL) {
        return 10;
    }
    p_ffd->p_start_cluster = p_start_cluster;
    p_ffd->file_version = 1;
    if (p_ffd->p_hint) {
        p_ffd->p_hint->file_version = 0;
    }
    p_ffd->last_access_cluster.cluster = 0;
    p_ffd->last_access_cluster.chain_index = 0;
    p_ffd->last_cluster.num_last_cluster = 0;
    p_ffd->last_cluster.max_chain_index = 0;
    p_ffd->cluster_link.buffer = 0;
    return 0;
}

s32 VFiPFFAT_InitFFD(struct PF_FFD* p_ffd, struct PF_FAT_HINT* p_hint, struct PF_VOLUME* p_vol, u32* p_start_cluster) {
    if (!p_ffd) {
        return 10;
    }
    if (!p_start_cluster) {
        return 10;
    }
    p_ffd->p_hint = p_hint;
    p_ffd->p_vol = p_vol;
    VFiPFFAT_ResetFFD(p_ffd, p_start_cluster);
    return 0;
}

s32 VFiPFFAT_FinalizeFFD(struct PF_FFD* p_ffd) {
    if (!p_ffd) {
        return 10;
    }
    p_ffd->cluster_link.buffer = 0;
    return 0;
}

u32 VFiPFFAT_GetValueOfEOC2(struct PF_VOLUME* p_vol) {
    return fat_special_values[p_vol->bpb.fat_type].eoc2;
}
