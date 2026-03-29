#include <revolution/VF.h>

s32 VFiPFVOL_DoUnmountVolume(struct PF_VOLUME* p_vol, u32 mode);

s32 VFiPFVOL_DoMountVolume(struct PF_VOLUME* p_vol);
s32 VFiPFVOL_p_unmount(struct PF_VOLUME* p_vol, u32 mode);
s32 VFiPFVOL_InitModule(u32 config, void* param);
s32 VFiPFVOL_CheckForRead(struct PF_VOLUME* p_vol);
s32 VFiPFVOL_CheckForWrite(struct PF_VOLUME* p_vol);
s32 VFiPFVOL_GetCurrentDir(struct PF_VOLUME* p_vol, struct PF_DIR_ENT* p_current_dir);
void VFiPFVOL_SetCurrentVolume(struct PF_VOLUME* p_vol);
struct PF_VOLUME* VFiPFVOL_GetCurrentVolume();
struct PF_VOLUME* VFiPFVOL_GetVolumeFromDrvChar(s8 drv_char);
void VFiPFVOL_LoadVolumeLabelFromBuf(const u8* buf, struct PF_VOLUME* p_vol);
s32 VFiPFVOL_errnum(void);
s32 VFiPFVOL_getdev(s8 drv_char, struct PF_DEV_INF* dev_inf);
s32 VFiPFVOL_attach(struct PF_DRV_TBL* p_drv);
s32 VFiPFVOL_detach(s8 drv_char);
s32 VFiPFVOL_unmount(s8 drv_char, u32 mode);

// Other functions called by main functions. These should NOT need to be implemented. They are here for reference only.
s32 VFiPFDRV_mount(struct PF_VOLUME* p_vol);
s32 VFiPFCACHE_InitCaches(struct PF_VOLUME* p_vol);
s32 VFiPFSYS_GetCurrentContextID(s32* context_id);
s32 VFiPFENT_GetRootDir(struct PF_VOLUME* p_vol, struct PF_DIR_ENT* p_ent);
s32 VFiPFDRV_format(struct PF_VOLUME* p_vol, const u8* param);
s32 VFiPFFAT_InitFATRegion(struct PF_VOLUME* p_vol);
s32 VFiPFENT_MakeRootDir(struct PF_VOLUME* p_vol);
void VFiPFFILE_FinalizeAllFiles(struct PF_VOLUME* p_vol);
void VFiPFDIR_FinalizeAllDirs(struct PF_VOLUME* p_vol);
s32 VFiPFCACHE_FlushAllCaches(struct PF_VOLUME* p_vol);
void VFiPFCACHE_FreeAllCaches(struct PF_VOLUME* p_vol);
s32 VFiPFDRV_unmount(struct PF_VOLUME* p_vol, u32 mode);
void* VFipf_memset(void* dst, s32 c, u32 length);
void VFiPF_InitLockFile();
u32 VFiPFDRV_IsInserted(struct PF_VOLUME* p_vol);
u32 VFiPFDRV_IsDetected(struct PF_VOLUME* p_vol);
u32 VFiPFDRV_IsWProtected(struct PF_VOLUME* p_vol);
s32 VFipf_toupper(s32 c);
void* VFipf_memcpy(void* dst, void* src, u32 length);
s32 VFiPFFAT_CountFreeClusters(struct PF_VOLUME* p_vol, u32* p_num_free_clusters);
s32 VFiPFDRV_init(struct PF_VOLUME* p_vol);
void VFiPFCACHE_SetCache(struct PF_VOLUME* p_vol, struct PF_CACHE_PAGE* p_cache_page, u8 (*p_cache_buf)[512], u16 num_fat_pages, u16 num_data_pages);
void VFiPFCACHE_SetFATBufferSize(struct PF_VOLUME* p_vol, u32 size);
void VFiPFCACHE_SetDataBufferSize(struct PF_VOLUME* p_vol, u32 size);
s32 VFiPFDRV_finalize(struct PF_VOLUME* p_vol);

// Prototypes for VFiPFVOL_InitModule's static functions.
s32 VFiPFCODE_CP932_OEM2Unicode(const s8* cp932_src, u16* uc_dst);
s32 VFiPFCODE_CP932_Unicode2OEM(const u16* uc_src, s8* cp932_dst);
s32 VFiPFCODE_CP932_OEMCharWidth(const s8* buf);
u32 VFiPFCODE_CP932_isOEMMBchar(s8 cp932, u32 num);
s32 VFiPFCODE_CP932_UnicodeCharWidth(const u16* buf);
u32 VFiPFCODE_CP932_isUnicodeMBchar(u16 uc_src, u32 num);

struct PF_VOLUME_SET VFipf_vol_set;

static u32 VFiPFVOL_CheckContextRegistered(s32 context_id) {
    u32 i;
    for (i = 1; i < 1; i++) {
        VFipf_vol_set.context[i].stat &= 1;
        if (VFipf_vol_set.context[i].stat != 0 && VFipf_vol_set.context[i].context_id == context_id) {
            return 1;
        }
    }
    return 0;
}

static s32 VFiPFVOL_SetUpVolumeForMount(struct PF_VOLUME* p_vol) {
    return 0;
}

static s32 VFiPFVOL_InitCurrentDir(struct PF_VOLUME* p_vol) {
    s32 err;
    s32 context_id;
    u32 i;

    if ((p_vol->flags & 2) == 0) {
        return 9;
    }

    VFiPFSYS_GetCurrentContextID(&context_id);
    p_vol->current_dir[0].stat |= 1;

    if (VFiPFVOL_CheckContextRegistered(context_id)) {
        p_vol->current_dir[1].stat |= 1;
        p_vol->current_dir[1].context_id = context_id;
    }

    for (i = 0; i < 1; i++) {
        err = VFiPFENT_GetRootDir(p_vol, &p_vol->current_dir[i].directory);
        if (err) {
            return err;
        }
    }

    return 0;
}

static s32 VFiPFVOL_FinalizeCurrentDir(struct PF_VOLUME* p_vol) {
    u32 i;

    if ((p_vol->flags & 2) == 0) {
        return 9;
    }
    for (i = 0; i < 1; i++) {
        p_vol->current_dir[i].stat = 0;
    }

    return 0;
}

s32 VFiPFVOL_DoMountVolume(struct PF_VOLUME* p_vol) {
    s32 err;

    VFiPFVOL_SetUpVolumeForMount(p_vol);
    err = VFiPFDRV_mount(p_vol);
    if (err) {
        return err;
    }

    if (!p_vol->bpb.bytes_per_sector || (p_vol->bpb.bytes_per_sector & 0x1FF) != 0) {
        return 15;
    }

    err = VFiPFCACHE_InitCaches(p_vol);
    if (err) {
        return err;
    }

    p_vol->flags |= 2u;
    err = VFiPFVOL_InitCurrentDir(p_vol);
    if (!err && (p_vol->flags & 0x10) != 0) {
        err = VFiPFDRV_format(p_vol, p_vol->format_param);
        if (!err && (p_vol->flags & 0x20) == 0) {
            err = VFiPFFAT_InitFATRegion(p_vol);
            if (!err) {
                err = VFiPFENT_MakeRootDir(p_vol);
            }
        }
    }
    if (err) {
        p_vol->flags &= ~2u;
    }
    return err;
}

static s32 VFiPFVOL_DoUnmountVolume(struct PF_VOLUME* p_vol, u32 mode) {
    s32 err;

    err = VFiPFDRV_unmount(p_vol, mode);
    if (err) {
        return err;
    }

    VFiPFVOL_FinalizeCurrentDir(p_vol);
    p_vol->flags &= ~2u;
    return 0;
}

static void VFiPFVOL_UnmountVolumeByEject(struct PF_VOLUME* p_vol) {
    VFiPFFILE_FinalizeAllFiles(p_vol);
    VFiPFDIR_FinalizeAllDirs(p_vol);
    VFiPFCACHE_FreeAllCaches(p_vol);
    VFiPFVOL_DoUnmountVolume(p_vol, 1);
    VFipf_vol_set.num_mounted_volumes--;
}

static s32 VFiPFVOL_p_attach(struct PF_VOLUME* p_vol, struct PF_DRV_TBL* p_drv, s16 vol_idx) {
    s32 err;

    VFipf_memset(p_vol, 0, sizeof(struct PF_VOLUME));
    p_vol->p_part = p_drv->p_part;
    p_vol->drv_char = vol_idx + 'A';
    p_vol->tail_entry.tracker_size = 1;
    p_vol->tail_entry.tracker_bits = p_vol->tail_entry.tracker_buff;

    err = VFiPFDRV_init(p_vol);
    if (err != 0) {
        return err;
    }

    VFiPFCACHE_SetCache(p_vol, p_drv->cache->pages, p_drv->cache->buffers, p_drv->cache->num_fat_pages, p_drv->cache->num_data_pages);
    VFiPFCACHE_SetFATBufferSize(p_vol, p_drv->cache->num_fat_buf_size);
    VFiPFCACHE_SetDataBufferSize(p_vol, p_drv->cache->num_data_buf_size);
    return 0;
}

static s32 VFiPFVOL_p_detach(struct PF_VOLUME* p_vol) {
    s32 err;
    err = VFiPFDRV_finalize(p_vol);
    if (err) {
        return err;
    }
    return 0;
}

static s32 VFiPFVOL_p_mount(struct PF_VOLUME* p_vol) {
    s32 err;

    if ((p_vol->flags & 2) == 0) {
        err = VFiPFVOL_DoMountVolume(p_vol);
        if (err != 0) {
            return err;
        }

        p_vol->fsi_flag &= ~7;
        VFipf_vol_set.num_mounted_volumes++;
    }
    return 0;
}

s32 VFiPFVOL_p_unmount(struct PF_VOLUME* p_vol, u32 mode) {
    s32 err;
    s32 err2;

    err = 0;

    if ((p_vol->flags & 2) == 0) {
        return 9;
    }

    VFiPFFILE_FinalizeAllFiles(p_vol);
    VFiPFDIR_FinalizeAllDirs(p_vol);
    err2 = VFiPFCACHE_FlushAllCaches(p_vol);
    if (err2 != 0) {
        err = err2;
    }

    if (err2 == 0 || (mode & 1) != 0) {
        VFiPFCACHE_FreeAllCaches(p_vol);
        err2 = VFiPFVOL_DoUnmountVolume(p_vol, mode);
        if (err2 != 0 && err == 0) {
            err = err2;
        }
    }

    if (err == 0 || (mode & 1) != 0) {
        VFipf_vol_set.num_mounted_volumes--;
    }

    return err;
}

static s32 VFiPFVOL_CheckMediaInsert(struct PF_VOLUME* p_vol) {
    s32 err;

    if (VFiPFDRV_IsInserted(p_vol) != 0) {
        if (VFiPFDRV_IsDetected(p_vol) != 0) {
            if ((p_vol->flags & 2) != 0) {
                VFiPFVOL_UnmountVolumeByEject(p_vol);
            }
            err = VFiPFVOL_p_mount(p_vol);
            if (err != 0) {
                return err;
            }
        }
    } else {
        if ((p_vol->flags & 2) != 0) {
            if (VFiPFDRV_IsDetected(p_vol) != 0) {
                VFiPFVOL_UnmountVolumeByEject(p_vol);
            }
            p_vol->flags &= ~2;
        }
    }
    return 0;
}

s32 VFiPFVOL_InitModule(u32 config, void* param) {
    s32 vol_idx;
    struct PF_CHARCODE codeset; // Present in DWARF but unused here.
    u32 i;

    if ((config & 0xFFFCFFFF) != 0) {
        VFipf_vol_set.last_error = 10;
        return 10;
    }
    if ((config & 0x30000) == 0x30000) {
        VFipf_vol_set.last_error = 10;
        return 10;
    }

    if ((config & 0x10000) != 0) {
        VFipf_vol_set.config |= 0x10000;
    } else {
        VFipf_vol_set.config &= ~0x10000;
    }

    VFipf_vol_set.current_vol[0].p_vol = &VFipf_vol_set.volumes[0];
    VFipf_vol_set.current_vol[0].stat |= 1;
    VFipf_vol_set.num_attached_drives = 0;
    VFipf_vol_set.num_mounted_volumes = 0;

    if ((config & 0x10000) != 0) {
        VFipf_vol_set.config |= 0x10000;
    } else {
        VFipf_vol_set.config &= ~0x10000;
    }

    VFipf_vol_set.param = param;
    VFipf_vol_set.last_error = 0;
    VFipf_vol_set.last_driver_error = 0;
    VFipf_vol_set.setting = 1;

    VFipf_vol_set.codeset.oem2unicode = &VFiPFCODE_CP932_OEM2Unicode;
    VFipf_vol_set.codeset.unicode2oem = &VFiPFCODE_CP932_Unicode2OEM;
    VFipf_vol_set.codeset.oem_char_width = &VFiPFCODE_CP932_OEMCharWidth;
    VFipf_vol_set.codeset.is_oem_mb_char = &VFiPFCODE_CP932_isOEMMBchar;
    VFipf_vol_set.codeset.unicode_char_width = &VFiPFCODE_CP932_UnicodeCharWidth;
    VFipf_vol_set.codeset.is_unicode_mb_char = &VFiPFCODE_CP932_isUnicodeMBchar;

    for (vol_idx = 0; vol_idx < 26; vol_idx++) {
        VFipf_memset(&VFipf_vol_set.volumes[vol_idx], 0, sizeof(struct PF_VOLUME));
    }

    VFiPF_InitLockFile();

    return 0;
}

s32 VFiPFVOL_CheckForRead(struct PF_VOLUME* p_vol) {
    s32 err;

    if (p_vol == NULL) {
        return 10;
    }

    err = VFiPFVOL_CheckMediaInsert(p_vol);
    if (err != 0) {
        return err;
    }

    if (!(p_vol->flags & 2)) {
        return 9;
    }

    return 0;
}

s32 VFiPFVOL_CheckForWrite(struct PF_VOLUME* p_vol) {
    s32 err;

    if (p_vol == NULL) {
        return 10;
    }

    err = VFiPFVOL_CheckMediaInsert(p_vol);
    if (err != 0) {
        return err;
    }

    if ((p_vol->flags & 2) == 0) {
        return 9;
    }

    if (VFiPFDRV_IsWProtected(p_vol)) {
        return 11;
    }

    return 0;
}

s32 VFiPFVOL_GetCurrentDir(struct PF_VOLUME* p_vol, struct PF_DIR_ENT* p_current_dir) {
    s32 context_id;
    u32 i;

    if (p_vol == NULL) {
        return 10;
    }
    if ((p_vol->flags & 2) == 0) {
        return 9;
    }

    VFiPFSYS_GetCurrentContextID(&context_id);

    for (i = 1; i < 1; i++) {
        if ((p_vol->current_dir[i].stat & 1) != 0 && p_vol->current_dir[i].context_id == context_id) {
            *p_current_dir = p_vol->current_dir[i].directory;
            break;
        }
    }

    if (i == 1) {
        if (VFiPFVOL_CheckContextRegistered(context_id)) {
            for (i = 1; i < 1; i++) {
                if ((p_vol->current_dir[i].stat & 1) == 0) {
                    p_vol->current_dir[i].stat |= 1;
                    p_vol->current_dir[i].context_id = context_id;
                    *p_current_dir = p_vol->current_dir[i].directory;
                    break;
                }
            }
        } else {
            *p_current_dir = p_vol->current_dir[0].directory;
        }
    }

    return 0;
}

void VFiPFVOL_SetCurrentVolume(struct PF_VOLUME* p_vol) {
    s32 context_id;
    u32 i;

    VFiPFSYS_GetCurrentContextID(&context_id);
    for (i = 1; i < 1; i++) {
        if ((VFipf_vol_set.current_vol[i].stat & 1) != 0 && VFipf_vol_set.current_vol[i].context_id == context_id) {
            VFipf_vol_set.current_vol[i].p_vol = p_vol;
            break;
        }
    }

    if (i == 1) {
        if (VFiPFVOL_CheckContextRegistered(context_id)) {
            for (i = 1; i < 1; i++) {
                if ((VFipf_vol_set.current_vol[i].stat & 1) == 0) {
                    VFipf_vol_set.current_vol[i].stat |= 1;
                    VFipf_vol_set.current_vol[i].context_id = context_id;
                    VFipf_vol_set.current_vol[i].p_vol = p_vol;
                    break;
                }
            }
        }
    }
    VFipf_vol_set.current_vol[0].p_vol = p_vol;
}

struct PF_VOLUME* VFiPFVOL_GetCurrentVolume(void) {
    struct PF_VOLUME* p_vol;
    s32 context_id;
    u32 i;

    p_vol = NULL;
    VFiPFSYS_GetCurrentContextID(&context_id);

    for (i = 1; i < 1; i++) {
        if ((VFipf_vol_set.current_vol[i].stat & 1) != 0 && VFipf_vol_set.current_vol[i].context_id == context_id) {
            p_vol = VFipf_vol_set.current_vol[i].p_vol;
            break;
        }
    }

    if (i == 1) {
        if (VFiPFVOL_CheckContextRegistered(context_id)) {
            for (i = 1; i < 1; i++) {
                if ((VFipf_vol_set.current_vol[i].stat & 1) == 0) {
                    VFipf_vol_set.current_vol[i].stat |= 1;
                    VFipf_vol_set.current_vol[i].context_id = context_id;
                    p_vol = VFipf_vol_set.current_vol[i].p_vol;
                    break;
                }
            }
        } else {
            p_vol = VFipf_vol_set.current_vol[0].p_vol;
        }
    }
    return p_vol;
}

struct PF_VOLUME* VFiPFVOL_GetVolumeFromDrvChar(s8 drv_char) {
    struct PF_VOLUME* p_vol; // Present in DWARF but unused here.
    s16 vol_idx;

    vol_idx = VFipf_toupper(drv_char) - 'A';
    if (vol_idx < 0 || vol_idx >= 26) {
        return NULL;
    }

    return &VFipf_vol_set.volumes[vol_idx];
}

void VFiPFVOL_LoadVolumeLabelFromBuf(const u8* buf, struct PF_VOLUME* p_vol) {
    VFipf_memcpy(p_vol->label, (void*)buf, 11);
    p_vol->label[11] = '\0';
}

s32 VFiPFVOL_errnum(void) {
    return VFipf_vol_set.last_error;
}

s32 VFiPFVOL_getdev(s8 drv_char, struct PF_DEV_INF* dev_inf) {
    struct PF_VOLUME* p_vol;
    s32 err;

    p_vol = VFiPFVOL_GetVolumeFromDrvChar(drv_char);
    if (p_vol == NULL) {
        VFipf_vol_set.last_error = 10;
        return 10;
    }

    if (dev_inf == NULL) {
        VFipf_vol_set.last_error = 10;
        p_vol->last_error = 10;
        return 10;
    }

    err = VFiPFVOL_CheckForRead(p_vol);
    if (err != 0) {
        VFipf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }

    dev_inf->bps = p_vol->bpb.bytes_per_sector;
    dev_inf->spc = p_vol->bpb.sectors_per_cluster;
    dev_inf->cls = p_vol->bpb.num_clusters;

    err = VFiPFFAT_CountFreeClusters(p_vol, &dev_inf->ecl);
    if (err != 0) {
        VFipf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }

    return 0;
}

s32 VFiPFVOL_attach(struct PF_DRV_TBL* p_drv) {
    s32 vol_idx;
    struct PF_VOLUME* p_vol;
    s32 err;

    if (p_drv == NULL || p_drv->cache->num_fat_pages < 1 || p_drv->cache->num_data_pages < 2 || p_drv->cache->pages == NULL || p_drv->cache->buffers == NULL || ((u32)p_drv->cache->pages & 3) != 0 || ((u32)p_drv->cache->buffers & 3) != 0) {
        VFipf_vol_set.last_error = 10;
        return 10;
    }

    if (p_drv->cache->num_fat_buf_size == 0) {
        p_drv->cache->num_fat_buf_size = 1;
    }
    if (p_drv->cache->num_data_buf_size == 0) {
        p_drv->cache->num_data_buf_size = 1;
    }

    if (p_drv->cache->num_fat_pages / p_drv->cache->num_fat_buf_size < 1) {
        VFipf_vol_set.last_error = 10;
        return 10;
    }

    if (p_drv->cache->num_data_pages / p_drv->cache->num_data_buf_size < 2) {
        VFipf_vol_set.last_error = 10;
        return 10;
    }

    p_drv->stat = 0;
    p_drv->drive = 0;

    for (vol_idx = 0; vol_idx < 26; vol_idx++) {
        p_vol = &VFipf_vol_set.volumes[vol_idx];
        if ((p_vol->flags & 1) == 0) {
            break;
        }
    }

    if (vol_idx < 0 || vol_idx >= 26 || VFipf_vol_set.num_attached_drives < 0 || VFipf_vol_set.num_attached_drives >= 26) {
        VFipf_vol_set.last_error = 4;
        return 4;
    }

    p_vol->num_free_clusters = -1;
    p_vol->last_free_cluster = -1;

    err = VFiPFVOL_p_attach(p_vol, p_drv, vol_idx);
    if (err != 0) {
        VFipf_vol_set.last_error = err;
        return err;
    }

    p_vol->flags |= 1;
    p_drv->stat |= 1;
    p_vol->drv_char = vol_idx + 'A';
    p_drv->drive = vol_idx + 'A';

    VFipf_vol_set.num_attached_drives++;

    err = VFiPFVOL_CheckMediaInsert(p_vol);
    if (err != 0) {
        VFipf_vol_set.last_error = err;
        p_vol->last_error = err;
        return 0;
    }

    err = VFiPFDRV_IsInserted(p_vol);
    if (err != 0) {
        err = VFiPFVOL_p_mount(p_vol);
        if (err != 0) {
            VFipf_vol_set.last_error = err;
            p_vol->last_error = err;
            return 0;
        }
        p_drv->stat |= 2;
    }

    return 0;
}

s32 VFiPFVOL_detach(s8 drv_char) {
    struct PF_VOLUME* p_vol;
    s32 err;

    p_vol = VFiPFVOL_GetVolumeFromDrvChar(drv_char);
    if (p_vol == NULL) {
        VFipf_vol_set.last_error = 10;
        return 10;
    }

    if ((p_vol->flags & 2) != 0) {
        VFipf_vol_set.last_error = 10;
        p_vol->last_error = 10;
        return 10;
    }

    if ((p_vol->flags & 1) == 0) {
        VFipf_vol_set.last_error = 10;
        p_vol->last_error = 10;
        return 10;
    }

    err = VFiPFVOL_p_detach(p_vol);
    if (err) {
        VFipf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }

    p_vol->flags &= ~1;
    VFipf_vol_set.num_attached_drives--;

    return 0;
}

s32 VFiPFVOL_unmount(s8 drv_char, u32 mode) {
    struct PF_VOLUME* p_vol;
    s32 err;
    s32 err2;

    err2 = 0;
    p_vol = VFiPFVOL_GetVolumeFromDrvChar(drv_char);
    if (p_vol == NULL) {
        VFipf_vol_set.last_error = 10;
        return 10;
    } else if ((p_vol->flags & 1) == 0) {
        VFipf_vol_set.last_error = 10;
        return 10;
    } else if (mode != 0 && (mode & 1) == 0) {
        VFipf_vol_set.last_error = 10;
        p_vol->last_error = 10;
        return 10;
    } else {
        if (((p_vol->flags >> 1) & 1) & VFiPFDRV_IsDetected(p_vol)) {
            VFiPFVOL_UnmountVolumeByEject(p_vol);
        }

        if ((p_vol->flags & 2) == 0) {
            return 0;
        } else {
            if (p_vol->num_opened_files != 0 || p_vol->num_opened_directories != 0) {
                err2 = 1;
                VFipf_vol_set.last_error = 19;
                p_vol->last_error = 19;
                if ((mode & 1) == 0) {
                    return 19;
                }
            }

            err = VFiPFVOL_p_unmount(p_vol, mode);
            if (err != 0 && err2 == 0) {
                VFipf_vol_set.last_error = err;
                p_vol->last_error = err;
                err2 = 1;
                if ((mode & 1) == 0) {
                    err2 = err;
                }
            }
        }
    }

    return err2;
}
