#include <revolution/VF.h>

static void VFiPFFILE_Cursor_MoveToEnd(struct PF_FILE* p_file);

u32 VFiPFFILE_Cursor_AdvanceToRead(struct PF_FILE* p_file, u32 n, u32 sector);
s32 VFiPFFILE_Cursor_ReadHeadSector(struct PF_VOLUME* p_vol, struct PF_FILE* p_file, u8* p_buf, u32 size, u32* p_size_read);
s32 VFiPFFILE_Cursor_ReadBodySectors(struct PF_VOLUME* p_vol, struct PF_FILE* p_file, u8* p_buf, u32 size, u32* p_size_read);
s32 VFiPFFILE_Cursor_ReadTailSector(struct PF_VOLUME* p_vol, struct PF_FILE* p_file, u8* p_buf, u32 size, u32* p_size_read);
s32 VFiPFFILE_Cursor_Read(struct PF_FILE* p_file, u8* p_buf, u32 size, u32* p_size_read);
s32 VFiPFFILE_Cursor_WriteHeadSector(struct PF_VOLUME* p_vol, struct PF_FILE* p_file, u8* p_buf, u32 size, u32* p_size_write);
s32 VFiPFFILE_Cursor_WriteTailSector(struct PF_VOLUME* p_vol, struct PF_FILE* p_file, u8* p_buf, u32 size, u32 append_size, u32* p_size_write);
s32 VFiPFFILE_Cursor_Write_Overwrite(struct PF_VOLUME* p_vol, struct PF_FILE* p_file, u8* p_buf, u32 size, u32* p_size_write);
s32 VFiPFFILE_Cursor_Write(struct PF_FILE* p_file, u8* p_buf, u32 size, u32* p_size_write);
void VFiPFFILE_Cursor_MoveToClusterEnd(struct PF_FILE* p_file, u32 size);
struct PF_SFD* VFiPFFILE_GetSFD(struct PF_VOLUME* p_vol, struct PF_DIR_ENT* p_ent);
s32 VFiPFFILE_createEmptyFile(struct PF_VOLUME* p_vol, struct PF_DIR_ENT* p_file_ent, struct PF_STR* p_filename, u32 namelength);
s32 VFiPFFILE_p_fopen(struct PF_VOLUME* p_vol, struct PF_STR* p_path_str, s32 mode, struct PF_FILE** pp_file);
s32 VFiPFFILE_p_fread(struct PF_VOLUME* p_vol, u8* p_buf, u32 size, u32 count, struct PF_FILE* p_file, u32* p_count_read);
s32 VFiPFFILE_p_fwrite(struct PF_VOLUME* p_vol, u8* p_buf, u32 size, u32 count, struct PF_FILE* p_file, u32* p_count_written);
s32 VFiPFFILE_p_finfo(struct PF_FILE* p_file, struct PF_INFO* p_info);
s32 VFiPFFILE_GetOpenedFile(struct PF_DIR_ENT* p_ent, struct PF_DIR_ENT** pp_open_ent);
void VFiPFFILE_FinalizeAllFiles(struct PF_VOLUME* p_vol);
s32 VFiPFFILE_remove(struct PF_STR* p_path_str);
s32 VFiPFFILE_fopen(struct PF_STR* p_path_str, s32 mode, struct PF_FILE** pp_file);
s32 VFiPFFILE_fclose(struct PF_FILE* p_file);
s32 VFiPFFILE_fread(u8* p_buf, u32 size, u32 count, struct PF_FILE* p_file, u32* p_count_read);
s32 VFiPFFILE_fwrite(u8* p_buf, u32 size, u32 count, struct PF_FILE* p_file, u32* p_count_written);
s32 VFiPFFILE_fseek(struct PF_FILE* p_file, s32 lOffset, s32 nOrigin);
s32 VFiPFFILE_finfo(struct PF_FILE* p_file, struct PF_INFO* p_info);

// Other functions called by main functions. These should NOT need to be implemented. They are here for reference only.
void VFiPFCLUSTER_UpdateLastAccessCluster(struct PF_FILE* p_file, u32 sector);
s32 VFiPFFAT_GetSectorSpecified(struct PF_FFD* p_ffd, u32 file_sector_index, u32 may_allocate, u32* p_sector);
s32 VFiPFSEC_ReadData(struct PF_VOLUME* p_vol, u8* p_buf, u32 sector, u16 offset, u32 size, u32* p_success_size, u32 set_sig);
s32 VFiPFFAT_GetContinuousSector(struct PF_FFD* p_ffd, u32 file_sector_index, u32 size, u32* p_sector, u32* p_num_sector);
s32 VFiPFSEC_WriteData(struct PF_VOLUME* p_vol, const u8* p_buf, u32 sector, u16 offset, u32 size, u32* p_success_size, u32 set_sig);
s32 VFiPFCLUSTER_AppendCluster(struct PF_FILE* p_file, u32 byte, u32* p_success, u32* sector);
s32 VFiPFFAT_CountAllocatedClusters(struct PF_FFD* p_ffd, u32 size, u32* p_num_alloc_clusters);
s32 VFiPFFAT_InitFFD(struct PF_FFD* p_ffd, struct PF_FAT_HINT* p_hint, struct PF_VOLUME* p_vol, u32* p_start_cluster);
void* VFipf_memset(void* dst, s32 c, u32 length);
u32 VFiPFPATH_parseShortName(s8* pDest, struct PF_STR* p_pattern);
s32 VFiPFENT_AdjustSFN(struct PF_DIR_ENT* p_ent, s8* p_s16_name);
u32 VFiPFSTR_GetCodeMode(struct PF_STR* p_str);
s8* VFiPFSTR_GetStrPos(struct PF_STR* p_str, u32 target);
s32 VFiPFPATH_transformInUnicode(u16* sDestStr, const s8* sSrcStr);
u16* VFipf_w_strcpy(u16* dst, const u16* src);
u8 VFiPFENT_getcurrentDateTimeForEnt(u16* p_date, u16* p_time);
s32 VFiPFENT_allocateEntryPos(struct PF_DIR_ENT* p_ent, u8 num_entries, struct PF_FFD* p_ffd, u32* p_next_chain, struct PF_STR* p_filename, u32* p_pos);
s32 VFiPFPATH_AdjustExtShortName(s8* pName, u32 position);
u8 VFiPFENT_CalcCheckSum(struct PF_DIR_ENT* p_ent);
void VFiPFENT_storeLFNEntryFieldsToBuf(u8* buf, struct PF_DIR_ENT* p_ent, u8 ord, u8 sum, u32 is_last);
s32 VFiPFENT_allocateEntry(struct PF_DIR_ENT* p_ent, u8 num_entries, struct PF_FFD* p_ffd, u32* p_next_chain, struct PF_STR* p_filename);
s32 VFiPFENT_updateEntry(struct PF_DIR_ENT* p_ent, u32 flag);
s32 VFiPFENT_ITER_GetEntryOfPath(struct PF_ENT_ITER* p_iter, struct PF_DIR_ENT* p_ent, struct PF_VOLUME* p_vol, struct PF_STR* p_path, u32 no_look_last_token);
s32 VFiPFPATH_SplitPath(struct PF_STR* p_path, struct PF_STR* p_dir_path, struct PF_STR* p_filename);
u16 VFiPFSTR_StrNumChar(struct PF_STR* p_str, u32 target);
s32 VFiPFPATH_transformFromUnicodeToNormal(s8* sDest, const u16* sSrc);
void VFiPFSTR_SetLocalStr(struct PF_STR* p_str, s8* p_local);
s32 VFiPFENT_findEntry(struct PF_FFD* p_ffd, struct PF_DIR_ENT* p_ent, u32 index_search_from, struct PF_STR* p_pattern, u8 attr_required, u8 attr_unwanted);
s32 VFiPFFAT_FreeChain(struct PF_FFD* p_ffd, u32 start_cluster, u32 chain_index, u32 size);
void VFiPFFAT_InitHint(struct PF_FAT_HINT* p_hint);
s32 VFiPFCACHE_AllocateDataPage(struct PF_VOLUME* p_vol, u32 sector, struct PF_CACHE_PAGE** pp_page);
void VFiPFCACHE_FreeDataPage(struct PF_VOLUME* p_vol, struct PF_CACHE_PAGE* p_page);
s32 VFiPFCLUSTER_GetAppendSize(struct PF_FILE* p_file, u32* p_size);
s32 VFiPFFAT_FinalizeFFD(struct PF_FFD* p_ffd);
struct PF_VOLUME* VFiPFPATH_GetVolumeFromPath(struct PF_STR* p_path);
s32 VFiPFVOL_CheckForWrite(struct PF_VOLUME* p_vol);
s32 VFiPFENT_RemoveEntry(struct PF_DIR_ENT* p_ent, struct PF_ENT_ITER* p_iter);
s32 VFiPFCACHE_FlushFATCache(struct PF_VOLUME* p_vol);
s32 VFiPFVOL_CheckForRead(struct PF_VOLUME* p_vol);
u32 VFiPFDRV_IsWProtected(struct PF_VOLUME* p_vol);
s32 VFiPF_UnLockFile(struct PF_FILE* p_file);
s32 VFiPFCACHE_FlushDataCacheSpecific(struct PF_VOLUME* p_vol, void* signature);

extern PF_VOLUME_SET VFipf_vol_set;

static void VFiPFFILE_Cursor_Recalc(struct PF_FILE* p_file) {
    PF_VOLUME* p_vol;

    if (p_file == 0) {
        p_vol = 0;
    } else {
        p_vol = p_file->p_sfd->dir_entry.p_vol;
    }

    p_file->cursor.file_sector_index = p_file->cursor.position >> p_vol->bpb.log2_bytes_per_sector;
    p_file->cursor.offset_in_sector = p_file->cursor.position & (p_vol->bpb.bytes_per_sector - 1);
}

static void VFiPFFILE_Cursor_SetPosition(struct PF_FILE* p_file, u32 pos) {
    struct PF_VOLUME* p_vol;
    u32 pre_sec_off;
    u32 post_sec_off;
    if (p_file == 0) {
        p_vol = 0;
    } else {
        p_vol = p_file->p_sfd->dir_entry.p_vol;
    }

    pre_sec_off = (p_file->cursor.position >> p_vol->bpb.log2_bytes_per_sector) + ((p_file->cursor.position & (p_vol->bpb.bytes_per_sector - 1)) ? 1 : 0);
    post_sec_off = (pos >> p_vol->bpb.log2_bytes_per_sector) + ((pos & (p_vol->bpb.bytes_per_sector - 1)) ? 1 : 0);
    if (pre_sec_off != post_sec_off) {
        p_file->cursor.sector = -1;
    }

    p_file->cursor.position = pos;
    VFiPFFILE_Cursor_Recalc(p_file);
}

u32 VFiPFFILE_Cursor_AdvanceToRead(struct PF_FILE* p_file, u32 n, u32 sector) {
    u32 res;
    struct PF_VOLUME* p_vol;
    u32 wk_sector;

    res = 1;
    p_vol = (p_file == 0) ? (0) : (p_file->p_sfd->dir_entry.p_vol);
    wk_sector = sector + ((p_file->cursor.offset_in_sector + n) >> p_vol->bpb.log2_bytes_per_sector);

    if ((p_file->cursor.position + n) < p_file->p_sfd->dir_entry.file_size) {
        if (((p_file->cursor.offset_in_sector + n) & (p_vol->bpb.bytes_per_sector - 1)) != 0) {
            p_file->cursor.sector = wk_sector;
        } else {
            p_file->cursor.sector = -1;
        }
        p_file->cursor.position = p_file->cursor.position + n;
    } else {
        if (p_file->p_sfd->dir_entry.file_size == 0) {
            p_file->cursor.sector = -1;
            p_file->cursor.position = 0;
            if (n != 0) {
                res = 0;
            }
        } else {
            p_file->cursor.sector = -1;
            p_file->cursor.position = p_file->p_sfd->dir_entry.file_size;
            res = 0;
        }
    }

    VFiPFFILE_Cursor_Recalc(p_file);
    VFiPFCLUSTER_UpdateLastAccessCluster(p_file, wk_sector);
    return res;
}

s32 VFiPFFILE_Cursor_ReadHeadSector(struct PF_VOLUME* p_vol, struct PF_FILE* p_file, u8* p_buf, u32 size, u32* p_size_read) {
    s32 err;
    u32 success_size;

    u32 remaining_in_sector;

    *p_size_read = 0;
    if (p_file->cursor.offset_in_sector == 0) {
        return 0;
    }

    remaining_in_sector = p_vol->bpb.bytes_per_sector - p_file->cursor.offset_in_sector;
    if (size > remaining_in_sector) {
        size = remaining_in_sector;
    }

    if (p_file->cursor.position + size > p_file->p_sfd->dir_entry.file_size) {
        size = p_file->p_sfd->dir_entry.file_size - p_file->cursor.position;
        if (size < remaining_in_sector) {
            return 0;
        }
    }

    if (p_file->cursor.sector == -1) {
        err = VFiPFFAT_GetSectorSpecified(&p_file->p_sfd->ffd, p_file->cursor.file_sector_index, 0, &p_file->cursor.sector);
        if (err) {
            return err;
        }
        if (p_file->cursor.sector == -1) {
            VFiPFFILE_Cursor_SetPosition(p_file, p_file->p_sfd->dir_entry.file_size);
            return 28;
        }
        if (p_file->cursor.position + size > p_file->p_sfd->dir_entry.file_size) {
            VFiPFFILE_Cursor_SetPosition(p_file, p_file->p_sfd->dir_entry.file_size);
            return 27;
        }
    }

    err = VFiPFSEC_ReadData(p_vol, p_buf, p_file->cursor.sector, p_file->cursor.offset_in_sector, size, &success_size, 1);
    if (err && success_size == 0) {
        return err;
    }
    *p_size_read = success_size;
    VFiPFFILE_Cursor_AdvanceToRead(p_file, success_size, p_file->cursor.sector);

    return 0;
}

s32 VFiPFFILE_Cursor_ReadBodySectors(struct PF_VOLUME* p_vol, struct PF_FILE* p_file, u8* p_buf, u32 size, u32* p_size_read) {
    s32 err;
    u32 num_sector;
    u32 success_size;

    *p_size_read = 0;
    num_sector = 0;

    err = VFiPFFAT_GetContinuousSector(&p_file->p_sfd->ffd, p_file->cursor.file_sector_index, size, &p_file->cursor.sector, &num_sector);
    if (err) {
        return err;
    }

    if (p_file->cursor.sector == -1) {
        VFiPFFILE_Cursor_SetPosition(p_file, p_file->p_sfd->dir_entry.file_size);
        return 28;
    }

    if (size > (num_sector << p_vol->bpb.log2_bytes_per_sector)) {
        size = num_sector << p_vol->bpb.log2_bytes_per_sector;
    }

    if (p_file->cursor.position + size > p_file->p_sfd->dir_entry.file_size) {
        size = p_file->p_sfd->dir_entry.file_size - p_file->cursor.position;
        size = size - (size & (p_vol->bpb.bytes_per_sector - 1));
        if (size < p_vol->bpb.bytes_per_sector) {
            return 0;
        }
    }

    err = VFiPFSEC_ReadData(p_vol, p_buf, p_file->cursor.sector, p_file->cursor.offset_in_sector, size, &success_size, 1);
    if (err && success_size == 0) {
        return err;
    }
    *p_size_read = success_size;
    VFiPFFILE_Cursor_AdvanceToRead(p_file, success_size, p_file->cursor.sector);

    return 0;
}

s32 VFiPFFILE_Cursor_ReadTailSector(struct PF_VOLUME* p_vol, struct PF_FILE* p_file, u8* p_buf, u32 size, u32* p_size_read) {
    s32 err;
    u32 success_size;

    *p_size_read = 0;
    if (size == 0) {
        return 0;
    }

    if (p_file->cursor.position + size > p_file->p_sfd->dir_entry.file_size) {
        size = p_file->p_sfd->dir_entry.file_size - p_file->cursor.position;
        if (size == 0) {
            return 0;
        }
    }

    if (p_file->cursor.sector == -1) {
        err = VFiPFFAT_GetSectorSpecified(&p_file->p_sfd->ffd, p_file->cursor.file_sector_index, 0, &p_file->cursor.sector);
        if (err) {
            return err;
        }
        if (p_file->cursor.sector == -1) {
            VFiPFFILE_Cursor_SetPosition(p_file, p_file->p_sfd->dir_entry.file_size);
            return 28;
        }
        if (p_file->cursor.position + size > p_file->p_sfd->dir_entry.file_size) {
            VFiPFFILE_Cursor_SetPosition(p_file, p_file->p_sfd->dir_entry.file_size);
            return 27;
        }
    }

    err = VFiPFSEC_ReadData(p_vol, p_buf, p_file->cursor.sector, p_file->cursor.offset_in_sector, size, &success_size, 1);
    if (err && success_size == 0) {
        return err;
    }
    *p_size_read = success_size;
    VFiPFFILE_Cursor_AdvanceToRead(p_file, success_size, p_file->cursor.sector);

    return 0;
}

s32 VFiPFFILE_Cursor_Read(struct PF_FILE* p_file, u8* p_buf, u32 size, u32* p_size_read) {
    s32 err;
    struct PF_VOLUME* p_vol;
    u32 size_read;

    p_file->p_sfd->ffd.p_hint = &p_file->hint;
    *p_size_read = 0;

    p_vol = (p_file == NULL) ? NULL : p_file->p_sfd->dir_entry.p_vol;

    err = VFiPFFILE_Cursor_ReadHeadSector(p_vol, p_file, p_buf, size, &size_read);
    *p_size_read += size_read;
    if (err) {
        return err;
    }
    if (size_read >= size) {
        return 0;
    }

    size = size - size_read;
    while (size >= p_vol->bpb.bytes_per_sector) {
        err = VFiPFFILE_Cursor_ReadBodySectors(p_vol, p_file, p_buf + *p_size_read, size, &size_read);
        *p_size_read += size_read;
        if (err) {
            return err;
        }
        if (size_read == 0) {
            break;
        }
        size -= size_read;
    }

    err = VFiPFFILE_Cursor_ReadTailSector(p_vol, p_file, p_buf + *p_size_read, size, &size_read);
    *p_size_read += size_read;
    if (err) {
        return err;
    }
    return 0;
}

static u32 VFiPFFILE_Cursor_AdvanceToWrite(PF_FILE* p_file, u32 n, u32 sector) {
    PF_VOLUME* p_vol;
    u32 wk_sector;

    if (p_file == 0) {
        p_vol = 0;
    } else {
        p_vol = p_file->p_sfd->dir_entry.p_vol;
    }
    wk_sector = sector + ((p_file->cursor.offset_in_sector + n) >> p_vol->bpb.log2_bytes_per_sector);
    if (((p_vol->bpb.bytes_per_sector - 1) & (p_file->cursor.offset_in_sector + n)) != 0) {
        p_file->cursor.sector = sector + ((p_file->cursor.offset_in_sector + n) >> p_vol->bpb.log2_bytes_per_sector);
    } else {
        p_file->cursor.sector = -1;
    }
    p_file->cursor.position += n;
    if (p_file->cursor.position > p_file->p_sfd->dir_entry.file_size) {
        p_file->p_sfd->dir_entry.file_size = p_file->cursor.position;
    }

    VFiPFFILE_Cursor_Recalc(p_file);
    VFiPFCLUSTER_UpdateLastAccessCluster(p_file, wk_sector);
    return 1;
}

static void VFiPFFILE_Cursor_Initialize(struct PF_FILE* p_file) {
    p_file->cursor.sector = -1;
    VFiPFFILE_Cursor_SetPosition(p_file, 0);
}

s32 VFiPFFILE_Cursor_WriteHeadSector(PF_VOLUME* p_vol, PF_FILE* p_file, u8* p_buf, u32 size, u32* p_size_write) {
    s32 err;
    u32 max_writable_size;
    u32 success_size;

    *p_size_write = 0;
    if (p_file->cursor.offset_in_sector == 0) {
        return 0;
    }

    max_writable_size = p_vol->bpb.bytes_per_sector - p_file->cursor.offset_in_sector;
    if (size > max_writable_size) {
        size = max_writable_size;
    }

    if (p_file->cursor.sector == -1) {
        err = VFiPFFAT_GetSectorSpecified(&p_file->p_sfd->ffd, p_file->cursor.file_sector_index, 0, &p_file->cursor.sector);
        if (err) {
            return err;
        }
        if (p_file->cursor.sector == -1) {
            VFiPFFILE_Cursor_MoveToEnd(p_file);
            return 28;
        }
    }
    err = VFiPFSEC_WriteData(p_vol, p_buf, p_file->cursor.sector, p_file->cursor.offset_in_sector, size, &success_size, 1);
    if (err && success_size == 0) {
        return err;
    }
    *p_size_write = success_size;
    VFiPFFILE_Cursor_AdvanceToWrite(p_file, success_size, p_file->cursor.sector);

    return 0;
}

s32 VFiPFFILE_Cursor_WriteTailSector(struct PF_VOLUME* p_vol, struct PF_FILE* p_file, u8* p_buf, u32 size, u32 append_size, u32* p_size_write) {
    s32 err;
    u32 sector;
    u32 success_size;

    *p_size_write = 0;
    if (size == 0) {
        return 0;
    }

    if (size > p_vol->bpb.bytes_per_sector - p_file->cursor.offset_in_sector || size > p_vol->bpb.bytes_per_sector) {
        return 26;
    }

    if (append_size != 0) {
        err = VFiPFCLUSTER_AppendCluster(p_file, append_size, &size, &sector);
        if (err) {
            return err;
        }
        if (size == 0) {
            return 0;
        }
        p_file->cursor.sector = sector;
    } else if (p_file->cursor.sector == -1) {
        err = VFiPFFAT_GetSectorSpecified(&p_file->p_sfd->ffd, p_file->cursor.file_sector_index, 0, &p_file->cursor.sector);
        if (err) {
            return err;
        }
        if (p_file->cursor.sector == -1) {
            VFiPFFILE_Cursor_MoveToEnd(p_file);
            return 28;
        }
    }

    err = VFiPFSEC_WriteData(p_vol, p_buf, p_file->cursor.sector, p_file->cursor.offset_in_sector, size, &success_size, 1);
    if (err && success_size == 0) {
        return err;
    }

    *p_size_write = success_size;
    VFiPFFILE_Cursor_AdvanceToWrite(p_file, success_size, p_file->cursor.sector);

    return 0;
}

static s32 VFiPFFILE_Cursor_WriteBodySectors(struct PF_VOLUME* p_vol, struct PF_FILE* p_file, u8* p_buf, u32 size, u32* p_size_write) {
    s32 err;
    u32 success_size;

    *p_size_write = 0;
    err = VFiPFSEC_WriteData(p_vol, p_buf, p_file->cursor.sector, p_file->cursor.offset_in_sector, size, &success_size, 1);
    if (err && success_size == 0) {
        return err;
    }

    *p_size_write = success_size;
    VFiPFFILE_Cursor_AdvanceToWrite(p_file, success_size, p_file->cursor.sector);
    return 0;
}

s32 VFiPFFILE_Cursor_Write_Overwrite(struct PF_VOLUME* p_vol, struct PF_FILE* p_file, u8* p_buf, u32 size, u32* p_size_write) {
    s32 err;
    u32 success_size;
    u32 num_sector;
    u32 max_writable_size;

    max_writable_size = size;
    *p_size_write = 0;
    err = VFiPFFAT_GetContinuousSector(&p_file->p_sfd->ffd, p_file->cursor.file_sector_index, size, &p_file->cursor.sector, &num_sector);
    if (err) {
        return err;
    }

    if (!num_sector || p_file->cursor.sector == -1) {
        VFiPFFILE_Cursor_MoveToEnd(p_file);
        return 28;
    } else {
        if (max_writable_size > num_sector << p_vol->bpb.log2_bytes_per_sector) {
            max_writable_size = num_sector << p_vol->bpb.log2_bytes_per_sector;
        }
        err = VFiPFFILE_Cursor_WriteBodySectors(p_vol, p_file, &p_buf[*p_size_write], max_writable_size, &success_size);
        *p_size_write = success_size;
        if (err) {
            return err;
        }
    }
    return 0;
}

static s32 VFiPFFILE_Cursor_Write_Append(struct PF_VOLUME* p_vol, struct PF_FILE* p_file, u8* p_buf, u32 size, u32* p_size_write, u32* p_append_size) {
    s32 err;
    u32 sector;
    u32 append_size;
    u32 success_size;

    *p_size_write = 0;
    *p_append_size = 0;
    err = VFiPFCLUSTER_AppendCluster(p_file, size, &append_size, &sector);
    if (err) {
        return err;
    }
    p_file->cursor.sector = sector;
    if (!append_size) {
        return 0;
    }

    *p_append_size = append_size;
    err = VFiPFFILE_Cursor_WriteBodySectors(p_vol, p_file, &p_buf[*p_size_write], append_size, &success_size);
    *p_size_write += success_size;
    if (err) {
        return err;
    }

    return 0;
}

s32 VFiPFFILE_Cursor_Write(PF_FILE* p_file, u8* p_buf, u32 size, u32* p_size_write) {
    s32 err;
    struct PF_VOLUME* p_vol;
    u32 size_write;
    u32 size_request;
    u32 num_cluster;
    u32 append_size;

    p_file->p_sfd->ffd.p_hint = &p_file->hint;

    *p_size_write = 0;
    if (-1 - p_file->cursor.position < size) {
        size = -1 - p_file->cursor.position;
        VFipf_vol_set.last_error = 37;
        p_file->p_sfd->ffd.p_vol->last_error = 37;
        p_file->last_error = 37;
    }
    p_vol = (p_file == 0) ? 0 : p_file->p_sfd->dir_entry.p_vol;
    err = VFiPFFILE_Cursor_WriteHeadSector(p_vol, p_file, p_buf, size, &size_write);
    *p_size_write += size_write;
    if (err) {
        return err;
    }
    if (size_write >= size) {
        return 0;
    }
    size = size - size_write;
    err = VFiPFFAT_CountAllocatedClusters(&p_file->p_sfd->ffd, p_file->cursor.position + size, &num_cluster);
    if (err) {
        return err;
    }

    if (p_file->cursor.position + size > (num_cluster << (p_vol->bpb.log2_bytes_per_sector + p_vol->bpb.log2_sectors_per_cluster))) {
        size_request = (p_file->cursor.position + size) - (num_cluster << (p_vol->bpb.log2_bytes_per_sector + p_vol->bpb.log2_sectors_per_cluster));
        append_size = size - size_request;
    } else {
        size_request = 0;
        append_size = size;
    }

    while (append_size && append_size >= p_vol->bpb.bytes_per_sector) {
        err = VFiPFFILE_Cursor_Write_Overwrite(p_vol, p_file, &p_buf[*p_size_write], append_size, &size_write);
        *p_size_write += size_write;
        if (err) {
            return err;
        }
        append_size -= size_write;
        size -= size_write;
    }
    while (size_request && size >= p_vol->bpb.bytes_per_sector) {
        err = VFiPFFILE_Cursor_Write_Append(p_vol, p_file, &p_buf[*p_size_write], size_request, &size_write, &append_size);
        *p_size_write += size_write;
        if (err) {
            return err;
        }
        if (!append_size) {
            return 0;
        }
        size_request -= append_size;
        size -= size_write;
    }
    err = VFiPFFILE_Cursor_WriteTailSector(p_vol, p_file, &p_buf[*p_size_write], size, size_request, &size_write);
    *p_size_write += size_write;
    if (err) {
        return err;
    } else {
        return 0;
    }

    return err;
}

static void VFiPFFILE_Cursor_MoveToEnd(struct PF_FILE* p_file) {
    VFiPFFILE_Cursor_SetPosition(p_file, p_file->p_sfd->dir_entry.file_size);
}

void VFiPFFILE_Cursor_MoveToClusterEnd(PF_FILE* p_file, u32 size) {
    PF_VOLUME* p_vol;
    u32 cluster;

    if (p_file == 0) {
        p_vol = 0;
    } else {
        p_vol = p_file->p_sfd->dir_entry.p_vol;
    }

    VFiPFFAT_CountAllocatedClusters(&p_file->p_sfd->ffd, size, &cluster);

    if (cluster > 0xFFFFFFFF >> (p_vol->bpb.log2_bytes_per_sector + p_vol->bpb.log2_sectors_per_cluster)) {
        VFiPFFILE_Cursor_SetPosition(p_file, 0xFFFFFFFF);
    } else {
        VFiPFFILE_Cursor_SetPosition(p_file, cluster << (p_vol->bpb.log2_bytes_per_sector + p_vol->bpb.log2_sectors_per_cluster));
    }
}

static void VFiPFFILE_InitSFD(struct PF_SFD* p_sfd, struct PF_DIR_ENT* p_dir_entry) {
    p_sfd->stat = 3;
    p_sfd->num_handlers = 1;
    p_sfd->dir_entry = *p_dir_entry;
    p_sfd->lock.mode = 0;
    p_sfd->lock.count = 0;
    p_sfd->lock.wcount = 0;
    p_sfd->lock.owner = NULL;
    p_sfd->lock.resource = 0;
    VFiPFFAT_InitFFD(&p_sfd->ffd, NULL, p_dir_entry->p_vol, &p_sfd->dir_entry.start_cluster);
}

struct PF_SFD* VFiPFFILE_GetSFD(struct PF_VOLUME* p_vol, struct PF_DIR_ENT* p_ent) {
    u32 i;
    u32 sfd_num;
    struct PF_SFD* p_first_free_SFD;

    sfd_num = 0;
    p_first_free_SFD = NULL;
    for (i = 0; i < 5; ++i) {
        if ((p_vol->sfds[i].stat & 1) == 0 || (p_vol->sfds[i].stat & 1) != 0 && ((p_vol->sfds[i].stat == 0) & 2) != 0) {
            if (!p_first_free_SFD) {
                p_first_free_SFD = &p_vol->sfds[i];
                sfd_num = i;
            }
        } else {
            if (p_ent->p_vol == p_vol->sfds[i].dir_entry.p_vol && p_ent->entry_sector == p_vol->sfds[i].dir_entry.entry_sector && p_ent->entry_offset == p_vol->sfds[i].dir_entry.entry_offset) {
                ++p_vol->sfds[i].num_handlers;
                return &p_vol->sfds[i];
            }
        }
    }
    if (!p_first_free_SFD) {
        return NULL;
    }

    VFiPFFILE_InitSFD(p_first_free_SFD, p_ent);

    if ((p_vol->cluster_link.flag & 1) != 0) {
        p_first_free_SFD->ffd.cluster_link.buffer = &p_vol->cluster_link.buffer[sfd_num * p_vol->cluster_link.link_max];
        VFipf_memset(p_first_free_SFD->ffd.cluster_link.buffer, 0, 4 * p_vol->cluster_link.link_max);
        p_first_free_SFD->ffd.cluster_link.max_count = p_vol->cluster_link.link_max;
        p_first_free_SFD->ffd.cluster_link.interval = p_vol->cluster_link.interval;
        p_first_free_SFD->ffd.cluster_link.interval_offset = 0;
        p_first_free_SFD->ffd.cluster_link.position = 0;
        p_first_free_SFD->ffd.cluster_link.save_index = 0;
        if (p_ent->file_size) {
            if (p_first_free_SFD->ffd.cluster_link.max_count) {
                *p_first_free_SFD->ffd.cluster_link.buffer = p_ent->start_cluster;
                ++p_first_free_SFD->ffd.cluster_link.position;
            }
        }
    }

    return p_first_free_SFD;
}

static s32 VFiPFFILE_ReleaseSFD(PF_SFD* p_sfd) {
    if (!--p_sfd->num_handlers) {
        p_sfd->stat &= ~1u;
        p_sfd->ffd.cluster_link.buffer = 0;
    }
    return 0;
}

static struct PF_FILE* VFiPFFILE_GetFreeUFD(struct PF_VOLUME* p_vol) {
    s32 i;

    for (i = 0; i < 5; i++) {
        if ((p_vol->ufds[i].stat & 1) == 0) {
            return &p_vol->ufds[i];
        }
    }
    return 0;
}

static s32 VFiPFFILE_ReleaseUFD(PF_FILE* p_file) {
    p_file->stat &= ~1u;
    return 0;
}

s32 VFiPFFILE_createEmptyFile(struct PF_VOLUME* p_vol, struct PF_DIR_ENT* p_file_ent, struct PF_STR* p_filename, u32 namelength) {
    struct PF_DIR_ENT ent;
    u8 buf[32];
    u32 position;
    u8 num_entry_LFNs;
    u32 i;
    u8 sum;
    u32 OldSector;
    u32 NextChain[2];
    struct PF_FFD ffd;
    struct PF_FAT_HINT hint;
    u32 success_size;
    s32 pozIdx;
    s32 err;

    ent = *p_file_ent;
    VFiPFFAT_InitFFD(&ffd, &hint, ent.p_vol, &ent.start_cluster);

    if (p_vol->num_opened_files >= 5) {
        return 21;
    }

    err = VFiPFPATH_parseShortName((s8*)p_file_ent->short_name, p_filename);
    if (err != 0) {
        if (p_file_ent->short_name[0] == 0) {
            return 1;
        }
    }

    if (err != 0) {
        err = VFiPFENT_AdjustSFN(&ent, (s8*)p_file_ent->short_name); /* &ent not p_file_ent */
        if (err) {
            return err;
        }
        if (VFiPFSTR_GetCodeMode(p_filename) == 1) {
            VFiPFPATH_transformInUnicode((u16*)p_file_ent->long_name, (const s8*)VFiPFSTR_GetStrPos(p_filename, 1));
        } else {
            VFipf_w_strcpy((u16*)p_file_ent->long_name, (const u16*)VFiPFSTR_GetStrPos(p_filename, 1));
        }
    } else {
        p_file_ent->long_name[0] = 0;
    }

    if (p_vol->bpb.fat_type == FAT_32) {
        p_file_ent->start_cluster = 1;
    } else {
        p_file_ent->start_cluster = 0;
    }

    p_file_ent->file_size = 0;
    p_file_ent->p_vol = p_vol;
    p_file_ent->small_letter_flag = 0;
    p_file_ent->attr = 0x20;

    p_file_ent->create_time_ms = VFiPFENT_getcurrentDateTimeForEnt(&p_file_ent->create_date, &p_file_ent->create_time);
    p_file_ent->access_date = p_file_ent->create_date;
    p_file_ent->modify_time = p_file_ent->create_time;
    p_file_ent->modify_date = p_file_ent->create_date;

    if (p_file_ent->long_name[0] != 0 && (p_file_ent->small_letter_flag & 0x18) == 0) {
        num_entry_LFNs = namelength / 13 + (namelength % 13 != 0);
        err = VFiPFENT_allocateEntryPos(p_file_ent, num_entry_LFNs + 1, &ffd, NextChain, p_filename, (u32*)&pozIdx);
        if (err) {
            return err;
        }

        if ((VFipf_vol_set.setting & 2) == 2) {
            VFiPFPATH_AdjustExtShortName((s8*)p_file_ent->short_name, pozIdx);
        }

        p_file_ent->num_entry_LFNs = num_entry_LFNs;
        OldSector = p_file_ent->entry_sector;
        sum = VFiPFENT_CalcCheckSum(p_file_ent);

        position = (u32)NextChain;
        for (i = num_entry_LFNs; i >= 1; i--) {
            VFiPFENT_storeLFNEntryFieldsToBuf(buf, p_file_ent, i, sum, i == num_entry_LFNs);
            err = VFiPFSEC_WriteData(p_vol, buf, OldSector, p_file_ent->entry_offset, 32, &success_size, 0);
            if (err) {
                return err;
            }
            if (success_size != 32) {
                return 17;
            }
            p_file_ent->entry_offset += 32;
            if (p_file_ent->entry_offset >= p_vol->bpb.bytes_per_sector) {
                p_file_ent->entry_offset = 0;
                OldSector = *(u32*)position;
                position += 4;
            }
        }
        p_file_ent->entry_sector = OldSector;
    } else {
        err = VFiPFENT_allocateEntry(p_file_ent, 1, &ffd, NextChain, p_filename);
        if (err) {
            return err;
        }
    }

    if (p_file_ent->start_cluster == 1) {
        p_file_ent->start_cluster = 0;
    }

    return VFiPFENT_updateEntry(p_file_ent, 1);
}

s32 VFiPFFILE_p_fopen(struct PF_VOLUME* p_vol, struct PF_STR* p_path_str, s32 mode, struct PF_FILE** pp_file) {
    struct PF_DIR_ENT ent;
    struct PF_ENT_ITER iter;
    struct PF_SFD* p_sfd;
    struct PF_FILE* p_file;
    s32 err;
    u16 access_time;
    struct PF_STR file_str;
    struct PF_STR dir_str;
    struct PF_FFD ffd;
    struct PF_FAT_HINT hint;
    s8 tmp_local[512];
    s32 namelength;

    *pp_file = NULL;

    err = VFiPFENT_ITER_GetEntryOfPath(&iter, &ent, p_vol, p_path_str, 1);
    if (err != 0) {
        return err;
    }

    if ((ent.attr & 0x10) == 0) {
        return 1;
    }

    err = VFiPFPATH_SplitPath(p_path_str, &dir_str, &file_str);
    if (err != 0) {
        return 1;
    }

    namelength = VFiPFSTR_StrNumChar(&file_str, 1);
    if (namelength > 255) {
        return 1;
    }

    if (VFiPFSTR_GetCodeMode(&file_str) == 2) {
        VFiPFPATH_transformFromUnicodeToNormal(tmp_local, (const u16*)VFiPFSTR_GetStrPos(&file_str, 1));
    }
    VFiPFSTR_SetLocalStr(&file_str, tmp_local);

    if ((mode & 2) != 0) {
        VFiPFFAT_InitFFD(&ffd, &hint, ent.p_vol, &ent.start_cluster);
        err = VFiPFENT_findEntry(&ffd, &ent, 0, &file_str, 0x7F, 0);
        if (err != 0) {
            return 3;
        }

        if ((mode & 8) != 0 && (ent.attr & 1) != 0) {
            return 10;
        }

        if ((ent.attr & 0x10) != 0) {
            return 23;
        }

        VFiPFENT_getcurrentDateTimeForEnt(&ent.access_date, &access_time);
    } else {
        if (namelength + ent.path_len > 259) {
            return 1;
        }

        err = VFiPFFILE_createEmptyFile(p_vol, &ent, &file_str, namelength);
        if (err == 8) {
            if ((mode & 0x10) != 0) {
                return 8;
            }

            if ((mode & 1) != 0) {
                s32 is_open;
                struct PF_DIR_ENT* p_open_ent;
                p_open_ent = NULL;
                if (&ent == NULL) {
                    is_open = 0;
                } else {
                    VFiPFFILE_GetOpenedFile(&ent, &p_open_ent);
                    is_open = (p_open_ent != NULL);
                }
                if (is_open) {
                    return 8;
                }
            }

            if ((ent.attr & 1) != 0 && ((mode & 1) != 0 || (mode & 4) != 0 || (mode & 8) != 0)) {
                return 10;
            }

            if ((ent.attr & 0x10) != 0) {
                return 23;
            }

            if ((mode & 1) != 0) {
                if (ent.start_cluster >= 2 && ent.start_cluster != (u32)-1 && ent.file_size != 0) {
                    VFiPFFAT_FreeChain(&iter.ffd, ent.start_cluster, -1, ent.file_size);
                }
                ent.start_cluster = 0;
                ent.file_size = 0;
                VFiPFENT_getcurrentDateTimeForEnt(&ent.modify_date, &ent.modify_time);
                ent.access_date = ent.modify_date;
            } else {
                VFiPFENT_getcurrentDateTimeForEnt(&ent.access_date, &access_time);
            }
        } else if (err != 0) {
            return err;
        }
    }

    p_vol = ent.p_vol;
    p_sfd = VFiPFFILE_GetSFD(p_vol, &ent);
    if (p_sfd == NULL) {
        return 21;
    }

    p_file = VFiPFFILE_GetFreeUFD(p_vol);
    if (p_file == NULL) {
        p_sfd->num_handlers--;
        if (p_sfd->num_handlers == 0) {
            p_sfd->stat &= ~1;
            p_sfd->ffd.cluster_link.buffer = 0;
        }
        return 22;
    }

    p_file->p_sfd = p_sfd;
    p_file->stat = 1;
    p_file->open_mode = mode;
    p_file->last_error = 0;
    p_file->lock_count = 0;
    VFiPFFAT_InitHint(&p_file->hint);

    VFiPFFILE_Cursor_Initialize(p_file);

    if ((mode & 0x1) != 0) {
        p_file->p_sfd->stat |= 4u;
    }
    if ((p_file->open_mode & 4) != 0) {
        VFiPFFILE_Cursor_MoveToEnd(p_file);
    }

    *pp_file = p_file;
    return 0;
}

s32 VFiPFFILE_p_fread(struct PF_VOLUME* p_vol, u8* p_buf, u32 size, u32 count, struct PF_FILE* p_file, u32* p_count_read) {
    u32 size_read;
    u32 total_size;
    s32 err;

    size_read = 0;
    *p_count_read = 0;

    if ((p_file->open_mode & 8) == 0 && ((p_file->open_mode & 1) != 0 || (p_file->open_mode & 4) != 0)) {
        return 10;
    }

    if ((p_file->p_sfd->lock.mode & 3) != 0 && p_file->lock_count == 0) {
        return 25;
    }

    if (p_file->cursor.position >= p_file->p_sfd->dir_entry.file_size) {
        return 28;
    }

    total_size = size * count;
    err = VFiPFFILE_Cursor_Read(p_file, p_buf, total_size, &size_read);
    *p_count_read = size_read / size;

    if (err) {
        return err;
    } else {
        return 0;
    }
}

s32 VFiPFFILE_p_fwrite(struct PF_VOLUME* p_vol, u8* p_buf, u32 size, u32 count, struct PF_FILE* p_file, u32* p_count_written) {
    u32 append_size;
    struct PF_CACHE_PAGE* p_page;
    u32 size_written;
    s32 err;

    size_written = 0;
    *p_count_written = 0;
    if ((p_file->open_mode & 8) == 0 && (p_file->open_mode & 2) != 0) {
        return 10;
    }
    if ((p_file->p_sfd->lock.mode & 3) != 0 && ((p_file->p_sfd->lock.mode & 1) != 0 || (p_file->p_sfd->lock.mode & 2) != 0 && !p_file->lock_count)) {
        return 25;
    }

    if ((p_file->open_mode & 4) != 0) {
        VFiPFFILE_Cursor_MoveToEnd(p_file);
    }

    if (p_file->cursor.position > p_file->p_sfd->dir_entry.file_size) {
        append_size = p_file->cursor.position - p_file->p_sfd->dir_entry.file_size;
        p_file->cursor.position = p_file->p_sfd->dir_entry.file_size;
        p_file->cursor.file_sector_index = p_file->cursor.position >> p_vol->bpb.log2_bytes_per_sector;
        p_file->cursor.offset_in_sector = p_file->cursor.position & (p_vol->bpb.bytes_per_sector - 1);
        err = VFiPFCACHE_AllocateDataPage(p_vol, -1, &p_page);
        if (err) {
            return err;
        }
        VFipf_memset(p_page->p_buf, 0, p_vol->bpb.bytes_per_sector);
        while (append_size) {
            if (append_size > p_vol->bpb.bytes_per_sector) {
                err = VFiPFFILE_Cursor_Write(p_file, p_page->p_buf, p_vol->bpb.bytes_per_sector, &size_written);
                if (err) {
                    return err;
                }
            } else {
                err = VFiPFFILE_Cursor_Write(p_file, p_page->p_buf, append_size, &size_written);
                if (err) {
                    return err;
                }
                break;
            }
            append_size -= p_vol->bpb.bytes_per_sector;
        }
        VFiPFCACHE_FreeDataPage(p_vol, p_page);
    }
    err = VFiPFFILE_Cursor_Write(p_file, p_buf, size * count, &size_written);
    *p_count_written = size_written / size;
    if (err) {
        return err;
    } else {
        return 0;
    }
}

s32 VFiPFFILE_p_finfo(struct PF_FILE* p_file, struct PF_INFO* p_info) {
    struct PF_VOLUME* p_vol;
    u32 cluster_size;
    s32 err;

    p_file->p_sfd->ffd.p_hint = &p_file->hint;

    if (p_file == 0) {
        p_vol = 0;
    } else {
        p_vol = p_file->p_sfd->dir_entry.p_vol;
    }

    p_info->file_size = p_file->p_sfd->dir_entry.file_size;
    p_info->io_pointer = p_file->cursor.position;

    cluster_size = (u32)p_vol->bpb.bytes_per_sector << p_vol->bpb.log2_sectors_per_cluster;

    if (p_file->p_sfd->dir_entry.start_cluster != 0) {
        err = VFiPFCLUSTER_GetAppendSize(p_file, &p_info->allocated_size);
        if (err) {
            return err;
        }

        // possible inlined function?
        {
            u32 allocated_size;
            u32 remainder;

            allocated_size = p_info->allocated_size;
            remainder = p_file->p_sfd->dir_entry.file_size % cluster_size;
            p_info->empty_size = ((s32)(-remainder | remainder)) >> 31;
            p_info->empty_size = (cluster_size - remainder) & (err = p_info->empty_size);
            p_info->empty_size = (s32)(allocated_size + p_info->empty_size);
        }
    } else {
        p_info->allocated_size = 0;
        p_info->empty_size = 0;
    }

    p_info->lock_mode = p_file->p_sfd->lock.mode & 3;
    p_info->lock_owner = p_file->p_sfd->lock.owner;
    p_info->lock_count = p_file->lock_count;
    p_info->lock_tcount = p_file->p_sfd->lock.count;

    return 0;
}

s32 VFiPFFILE_GetOpenedFile(struct PF_DIR_ENT* p_ent, struct PF_DIR_ENT** pp_open_ent) {
    s32 i;

    if (!p_ent || !pp_open_ent || !p_ent->p_vol) {
        return 10;
    }
    *pp_open_ent = 0;
    for (i = 0; i < 5; ++i) {
        if ((p_ent->p_vol->sfds[i].stat & 1) != 0 && (p_ent->p_vol->sfds[i].stat & 2) != 0 && p_ent->p_vol == p_ent->p_vol->sfds[i].dir_entry.p_vol && p_ent->entry_sector == p_ent->p_vol->sfds[i].dir_entry.entry_sector && p_ent->entry_offset == p_ent->p_vol->sfds[i].dir_entry.entry_offset) {
            *pp_open_ent = &p_ent->p_vol->sfds[i].dir_entry;
        }
    }
    return 0;
}

static void VFiPFFILE_FinalizeSFD(struct PF_SFD* p_sfd) {
    p_sfd->stat = 0;
    VFiPFFAT_FinalizeFFD(&p_sfd->ffd);
}

static void VFiPFFILE_FinalizeUFD(struct PF_FILE* p_file) {
    p_file->stat &= ~1;
}

void VFiPFFILE_FinalizeAllFiles(struct PF_VOLUME* p_vol) {
    u16 i;

    for (i = 0; i < 5; i++) {
        VFiPFFILE_FinalizeSFD(&p_vol->sfds[i]);
    }
    for (i = 0; i < 5; i++) {
        VFiPFFILE_FinalizeUFD(&p_vol->ufds[i]);
    }
    p_vol->num_opened_files = 0;
}

s32 VFiPFFILE_remove(struct PF_STR* p_path_str) {
    struct PF_VOLUME* p_vol;
    s32 err;
    struct PF_ENT_ITER iter;
    struct PF_DIR_ENT ent;
    u32 start_cluster;

    if (p_path_str == NULL) {
        err = 10;
        VFipf_vol_set.last_error = 10;
        return err;
    }
    p_vol = VFiPFPATH_GetVolumeFromPath(p_path_str);
    if (p_vol == NULL) {
        err = 10;
        VFipf_vol_set.last_error = 10;
        return err;
    }

    err = VFiPFVOL_CheckForWrite(p_vol);
    if (err) {
        VFipf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }

    p_vol->cache.signature = NULL;
    err = VFiPFENT_ITER_GetEntryOfPath(&iter, &ent, p_vol, p_path_str, 0);

    // idk
    switch (err) {
        default:
            break;
        case 0:
            if ((ent.attr & 0x19) != 0) {
                err = 11;
            } else {
                struct PF_DIR_ENT* p_open_ent = NULL;
                s32 is_open;
                if (&ent == NULL) {
                    is_open = 0;
                } else {
                    VFiPFFILE_GetOpenedFile(&ent, &p_open_ent);
                    is_open = (p_open_ent != NULL);
                }
                if (is_open) {
                    err = 19;
                } else {
                    start_cluster = ent.start_cluster;
                    err = VFiPFENT_RemoveEntry(&ent, &iter);
                    // idk
                    switch (err) {
                        default:
                            break;
                        case 0:
                            err = VFiPFFAT_FreeChain(&iter.ffd, start_cluster, -1, ent.file_size);
                    }
                }
            }
    }

    if (err) {
        VFipf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }

    err = VFiPFCACHE_FlushFATCache(p_vol);
    if (err) {
        VFipf_vol_set.last_error = err;
        p_vol->last_error = err;
    }

    return err;
}

s32 VFiPFFILE_fopen(struct PF_STR* p_path_str, s32 mode, struct PF_FILE** pp_file) {
    struct PF_VOLUME* p_vol;
    s32 err;

    if (pp_file == NULL) {
        err = 10;
        VFipf_vol_set.last_error = 10;
        return err;
    }
    *pp_file = NULL;
    if (p_path_str == NULL) {
        err = 10;
        VFipf_vol_set.last_error = 10;
        return err;
    }

    p_vol = VFiPFPATH_GetVolumeFromPath(p_path_str);
    if (p_vol == NULL) {
        err = 10;
        VFipf_vol_set.last_error = 10;
        return err;
    }

    err = VFiPFVOL_CheckForRead(p_vol);
    if (err) {
        VFipf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }

    if (VFiPFDRV_IsWProtected(p_vol) && mode != 2) {
        return 11;
    }

    err = VFiPFFILE_p_fopen(p_vol, p_path_str, mode, pp_file);
    if (err) {
        VFipf_vol_set.last_error = err;
        p_vol->last_error = err;
    } else {
        p_vol->num_opened_files++;
    }
    return err;
}

s32 VFiPFFILE_fclose(struct PF_FILE* p_file) {
    struct PF_VOLUME* p_vol;
    s32 err;

    if ((u32)&VFipf_vol_set > (u32)p_file || (u32)&VFipf_vol_set + 0x27FB8 < (u32)p_file) {
        VFipf_vol_set.last_error = 10;
        return 10;
    }

    p_vol = (p_file == NULL) ? NULL : p_file->p_sfd->dir_entry.p_vol;
    if (p_vol == NULL) {
        VFipf_vol_set.last_error = 10;
        return 10;
    }

    err = VFiPFVOL_CheckForRead(p_vol);
    if (err) {
        VFipf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }

    if (VFiPFDRV_IsWProtected(p_vol) && p_file->open_mode != 2) {
        return 11;
    }

    if (!p_file || !p_file->p_sfd || (p_file->stat & 1) == 0 || (p_file->p_sfd->stat & 1) == 0 || (p_file->p_sfd->stat & 2) == 0) {
        VFipf_vol_set.last_error = 10;
        p_vol->last_error = 10;
        return 10;
    }

    if ((p_file->p_sfd->stat & 1) == 0 || (p_file->p_sfd->stat & 2) == 0) {
        VFipf_vol_set.last_error = 10;
        p_vol->last_error = 10;
        return 10;
    }
    p_vol->cache.signature = p_file;

    if (p_file->p_sfd->num_handlers - 1 <= 0 && (p_file->p_sfd->dir_entry.attr & 0x19) == 0 && !VFiPFDRV_IsWProtected(p_vol) && ((p_file->p_sfd->stat & 4) || (p_vol->file_config & 1) != 1)) {
        err = VFiPFENT_updateEntry(&p_file->p_sfd->dir_entry, 1);
    }

    if (p_file->lock_count > 0) {
        if (p_file->p_sfd->lock.mode & 1) {  // Share lock
            p_file->p_sfd->lock.count -= p_file->lock_count;
            p_file->lock_count = 0;
            if (p_file->p_sfd->lock.count == 0) {
                VFiPF_UnLockFile(p_file);
            }
            p_file->p_sfd->lock.mode &= ~3;
        } else if (p_file->p_sfd->lock.owner != p_file) {  // Exclusive lock

            err = 25;
        } else {
            p_file->p_sfd->lock.count = 0;
            p_file->lock_count = 0;
            p_file->p_sfd->lock.owner = NULL;
            VFiPF_UnLockFile(p_file);
            p_file->p_sfd->lock.mode &= ~3;
        }
    }

    if (err) {
        VFipf_vol_set.last_error = err;
        p_file->p_sfd->ffd.p_vol->last_error = err;
        p_file->last_error = err;
    } else {
        if (p_vol->cache.mode & 2) {
            err = VFiPFCACHE_FlushFATCache(p_vol);
            if (err) {
                VFipf_vol_set.last_error = err;
                p_file->p_sfd->ffd.p_vol->last_error = err;
                p_file->last_error = err;
            } else {
                err = VFiPFCACHE_FlushDataCacheSpecific(p_vol, p_file);
                if (err) {
                    VFipf_vol_set.last_error = err;
                    p_file->p_sfd->ffd.p_vol->last_error = err;
                    p_file->last_error = err;
                }
            }
        }
        if (err == 0) {
            VFiPFFILE_ReleaseSFD(p_file->p_sfd);
            VFiPFFILE_ReleaseUFD(p_file);
            p_vol->num_opened_files--;
        }
    }

    p_vol->cache.signature = NULL;
    return err;
}

s32 VFiPFFILE_fread(u8* p_buf, u32 size, u32 count, struct PF_FILE* p_file, u32* p_count_read) {
    struct PF_VOLUME* p_vol;
    u32 count_read;
    s32 err;

    if (p_count_read == NULL) {
        VFipf_vol_set.last_error = 10;
        return 10;
    }
    *p_count_read = 0;

    if ((u32)&VFipf_vol_set > (u32)p_file || (u32)&VFipf_vol_set + 0x27FB8 < (u32)p_file) {
        VFipf_vol_set.last_error = 10;
        return 10;
    }

    p_vol = (p_file == NULL) ? NULL : p_file->p_sfd->dir_entry.p_vol;
    if (p_vol == NULL) {
        VFipf_vol_set.last_error = 38;
        p_file->p_sfd->ffd.p_vol->last_error = 38;
        p_file->last_error = 38;
        return 38;
    }

    err = VFiPFVOL_CheckForRead(p_vol);
    if (err) {
        VFipf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }

    if (!p_file || !p_file->p_sfd || (p_file->stat & 1) == 0 || (p_file->p_sfd->stat & 1) == 0 || (p_file->p_sfd->stat & 2) == 0) {
        VFipf_vol_set.last_error = 38;
        p_vol->last_error = 38;
        return 38;
    }

    if ((p_file->p_sfd->stat & 1) == 0 || (p_file->p_sfd->stat & 2) == 0) {
        VFipf_vol_set.last_error = 38;
        p_vol->last_error = 38;
        return 38;
    }

    if (p_buf == NULL || count == 0 || size == 0) {
        VFipf_vol_set.last_error = 10;
        p_file->p_sfd->ffd.p_vol->last_error = 10;
        p_file->last_error = 10;
        return 10;
    }

    p_vol->cache.signature = p_file;
    err = VFiPFFILE_p_fread(p_vol, p_buf, size, count, p_file, &count_read);
    *p_count_read = count_read;
    p_vol->cache.signature = NULL;

    if (err) {
        VFipf_vol_set.last_error = err;
        p_file->p_sfd->ffd.p_vol->last_error = err;
        p_file->last_error = err;
    }

    return err;
}

s32 VFiPFFILE_fwrite(u8* p_buf, u32 size, u32 count, struct PF_FILE* p_file, u32* p_count_written) {
    struct PF_VOLUME* p_vol;
    u32 count_written;
    s32 err;

    if (p_count_written == NULL) {
        VFipf_vol_set.last_error = 10;
        return 10;
    }
    *p_count_written = 0;

    if ((u32)&VFipf_vol_set > (u32)p_file || (u32)&VFipf_vol_set + 0x27FB8 < (u32)p_file) {
        VFipf_vol_set.last_error = 10;
        return 10;
    }

    p_vol = (p_file == NULL) ? NULL : p_file->p_sfd->dir_entry.p_vol;
    if (p_vol == NULL) {
        VFipf_vol_set.last_error = 38;
        p_file->p_sfd->ffd.p_vol->last_error = 38;
        p_file->last_error = 38;
        return 38;
    }

    err = VFiPFVOL_CheckForWrite(p_vol);
    if (err) {
        VFipf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }

    if (!p_file || !p_file->p_sfd || (p_file->stat & 1) == 0 || (p_file->p_sfd->stat & 1) == 0 || (p_file->p_sfd->stat & 2) == 0) {
        VFipf_vol_set.last_error = 38;
        p_vol->last_error = 38;
        return 38;
    }

    if ((p_file->p_sfd->stat & 1) == 0 || (p_file->p_sfd->stat & 2) == 0) {
        VFipf_vol_set.last_error = 38;
        p_vol->last_error = 38;
        return 38;
    }

    if (p_buf == NULL || count == 0 || size == 0) {
        VFipf_vol_set.last_error = 10;
        p_file->p_sfd->ffd.p_vol->last_error = 10;
        p_file->last_error = 10;
        return 10;
    }

    p_vol->cache.signature = p_file;
    err = VFiPFFILE_p_fwrite(p_vol, p_buf, size, count, p_file, &count_written);
    *p_count_written = count_written;
    p_vol->cache.signature = NULL;

    if (err) {
        VFipf_vol_set.last_error = err;
        p_file->p_sfd->ffd.p_vol->last_error = err;
        p_file->last_error = err;
    }

    if (count_written > 0) {
        VFiPFENT_getcurrentDateTimeForEnt(&p_file->p_sfd->dir_entry.modify_date, &p_file->p_sfd->dir_entry.modify_time);
        p_file->p_sfd->dir_entry.access_date = p_file->p_sfd->dir_entry.modify_date;
        p_file->p_sfd->stat |= 4;
    }

    return err;
}

s32 VFiPFFILE_fseek(struct PF_FILE* p_file, s32 lOffset, s32 nOrigin) {
    struct PF_VOLUME* p_vol;
    s32 err;
    u32 file_io;
    u32 wk_offset;
    u32 base_pos;
    u32* base_pos_pointer;
    if ((u32)&VFipf_vol_set > (u32)p_file || (u32)&VFipf_vol_set + 0x27FB8 < (u32)p_file) {
        VFipf_vol_set.last_error = 10;
        return 10;
    }
    p_vol = (p_file == 0) ? (0) : (p_file->p_sfd->dir_entry.p_vol);
    if (p_vol == 0) {
        VFipf_vol_set.last_error = 38;
        return 38;
    }
    err = VFiPFVOL_CheckForRead(p_vol);
    if (err) {
        VFipf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }
    if (((((!p_file) || (!p_file->p_sfd)) || ((p_file->stat & 1) == 0)) || ((p_file->p_sfd->stat & 1) == 0)) || ((p_file->p_sfd->stat & 2) == 0)) {
        VFipf_vol_set.last_error = 38;
        p_vol->last_error = 38;
        return 38;
    }
    if (((p_file->p_sfd->stat & 1) == 0) || ((p_file->p_sfd->stat & 2) == 0)) {
        VFipf_vol_set.last_error = 38;
        p_vol->last_error = 38;
        return 38;
    }
    switch (nOrigin) {
        case 1:
            base_pos = p_file->cursor.position;
            break;
        case 0:
            base_pos = 0;
            break;
        case 2:
            base_pos = p_file->p_sfd->dir_entry.file_size;
            break;
        default:
            VFipf_vol_set.last_error = 10;
            p_file->p_sfd->ffd.p_vol->last_error = 10;
            p_file->last_error = 10;
            return 10;
    }
    base_pos_pointer = &base_pos;
    if (lOffset & 0x80000000) {
        wk_offset = ((~lOffset) & 0x7FFFFFFF) + 1;
        if ((*base_pos_pointer) < wk_offset) {
            VFipf_vol_set.last_error = 10;
            p_file->p_sfd->ffd.p_vol->last_error = 10;
            p_file->last_error = 10;
            return 10;
        }
        file_io = base_pos - wk_offset;
    } else {
        if (((u32)lOffset) > (0xFFFFFFFF - base_pos)) {
            VFipf_vol_set.last_error = 37;
            p_file->p_sfd->ffd.p_vol->last_error = 37;
            p_file->last_error = 37;
            return 37;
        }
        file_io = base_pos + lOffset;
    }
    VFiPFFILE_Cursor_Initialize(p_file);
    VFiPFFILE_Cursor_SetPosition(p_file, file_io);
    return err;
}

s32 VFiPFFILE_finfo(struct PF_FILE* p_file, struct PF_INFO* p_info) {
    struct PF_VOLUME* p_vol;
    struct PF_CURSOR save_cursor;
    struct PF_FAT_HINT save_hint;
    s32 err;

    if ((u32)&VFipf_vol_set > (u32)p_file || (u32)&VFipf_vol_set + 0x27FB8 < (u32)p_file) {
        VFipf_vol_set.last_error = 10;
        return 10;
    }

    p_vol = (p_file == NULL) ? NULL : p_file->p_sfd->dir_entry.p_vol;
    if (p_vol == NULL) {
        VFipf_vol_set.last_error = 38;
        return 38;
    }

    err = VFiPFVOL_CheckForRead(p_vol);
    if (err) {
        VFipf_vol_set.last_error = err;
        p_file->p_sfd->ffd.p_vol->last_error = err;
        p_file->last_error = err;
        return err;
    }

    if (!p_file || !p_file->p_sfd || (p_file->stat & 1) == 0 || (p_file->p_sfd->stat & 1) == 0 || (p_file->p_sfd->stat & 2) == 0) {
        VFipf_vol_set.last_error = 38;
        p_vol->last_error = 38;
        return 38;
    }

    if ((p_file->p_sfd->stat & 1) == 0 || (p_file->p_sfd->stat & 2) == 0) {
        VFipf_vol_set.last_error = 38;
        p_vol->last_error = 38;
        return 38;
    }

    if (p_info == NULL) {
        VFipf_vol_set.last_error = 10;
        p_file->p_sfd->ffd.p_vol->last_error = 10;
        p_file->last_error = 10;
        return 10;
    }

    p_vol->cache.signature = p_file;
    save_cursor = p_file->cursor;
    save_hint = p_file->hint;

    err = VFiPFFILE_p_finfo(p_file, p_info);

    p_file->cursor = save_cursor;
    p_file->hint = save_hint;
    p_vol->cache.signature = NULL;

    if (err) {
        VFipf_vol_set.last_error = err;
        p_file->p_sfd->ffd.p_vol->last_error = err;
        p_file->last_error = err;
        return err;
    }

    return 0;
}
