#include <revolution/VF.h>

struct DriveInfo {
    // total size: 0x14
    u32 prf_file_size;      // offset 0x0, size 0x4
    s32 last_device_error;  // offset 0x4, size 0x4
    u32 fat_type;           // offset 0x8, size 0x4
    u32 reserved_sec_num;   // offset 0xC, size 0x4
    u32 root_ent_num;       // offset 0x10, size 0x4
};

struct HandleDevice {
    // total size: 0x10
    u32 status;     // offset 0x0, size 0x4
    u32 err;        // offset 0x4, size 0x4
    u32 type;       // offset 0x8, size 0x4
    u32 sync_mode;  // offset 0xC, size 0x4
};

struct HandleCache {
    // total size: 0x10
    struct MEMiHeapHead* heap_handle;       // offset 0x0, size 0x4
    u32 cache_pages;                        // offset 0x4, size 0x4
    struct PF_CACHE_PAGE* pf_cache_page_p;  // offset 0x8, size 0x4
    u8 (*pf_cache_buf_p)[512];              // offset 0xC, size 0x4
};

struct HandleDrive {
    // total size: 0x13C
    void* file_p;                          // offset 0x0, size 0x4
    struct PDM_DISK* pf_disk_p;            // offset 0x4, size 0x4
    struct PF_DRV_TBL pf_drv;              // offset 0x8, size 0xC
    struct PDM_PARTITION* pf_part_p;       // offset 0x14, size 0x4
    struct HandleCache cache;              // offset 0x18, size 0x10
    struct PF_CACHE_SETTING pf_cache_set;  // offset 0x28, size 0x14
    u8 pf_filename[255];                   // offset 0x3C, size 0xFF
};

struct HandleType {
    // total size: 0x140
    struct HandleDevice* device_p;  // offset 0x0, size 0x4
    struct HandleDrive drive;       // offset 0x4, size 0x13C
};

struct DriveInfo l_driveInfo[26];

void dCommon_DevideBuff32(void* i_buf, u32 i_size, u32* i_1st_size_p, void* i_2nd_pp, u32* i_2nd_size_p, void* i_3rd_pp, u32* i_3rd_size_p);
int dCommon_IsPrfFile(void* i_buff_p);
void dCommon_PrintSignature(struct PR_BINHEADER* i_header_p);
s32 dCommon_MakeFsInfoSec(u8* buf, u32 fsInfoSize);
u32 dCommon_GetPhysicalOffset(u32 startBlock, u32 BPS, u32 reservedSecNum);
enum FatType dCommon_GetNiceFatType(u32* spf, u32 SPU, u32 SPC, u32 BPS);
u32 dCommon_GetReservedSecFromFatType(enum FatType fatType);
u32 dCommon_GetRootEntNumFromFatType(enum FatType fatType);
void dCommon_MakeBootSector(u8* buf, enum FatType* type, u32 SPU, u32 SPC, u32 BPS, u8 jump0_1, u8 jump2, u32 secPerTrack, u32 reservedSecNum, u32 rootEntNum, u8 mediaDesc);
int dCommon_ReadDummyBPB(u32 num_blocks, u8* buf, u32 block, u32* p_num_success, struct PDM_DISK* p_disk, s32* p_err, s32 (*makeBS)(struct PDM_DISK*, u8*, enum FatType*), s32 (*makeFS)(u8*));
int dCommon_WriteDummyBPB(u32 num_blocks, u32 block, u32* p_num_success, struct PDM_DISK* p_disk, s32* p_err);
void dCommon_initDriveInfo();
u32 dCommon_getFileSizeFromDisk(struct PDM_DISK* p_disk);
void dCommon_setFileSizeToDisk(struct PDM_DISK* p_disk, u32 i_fileSize);
s32 dCommon_getLastDeviceErrorFromDisk(struct PDM_DISK* p_disk);
void dCommon_setLastDeviceErrorToDisk(struct PDM_DISK* p_disk, s32 i_lastDevErr);
void dCommon_setLastDeviceErrorToDisk2(s32 i_handleIdx, s32 i_lastDevErr);
s32 dCommon_getHandleIdxFromDisk(struct PDM_DISK* p_disk);
void dCommon_setFatTypeToDisk(struct PDM_DISK* p_disk, u32 i_fatType);
u32 dCommon_getResvSecNumFromDisk(struct PDM_DISK* p_disk);
void dCommon_setResvSecNumToDisk(struct PDM_DISK* p_disk, u32 i_reservedSecNum);
u32 dCommon_getRootEntNumFromDisk(struct PDM_DISK* p_disk);
void dCommon_setRootEntNumToDisk(struct PDM_DISK* p_disk, u32 i_rootEntNum);
s32 dCommon_flush_from_handle_p(struct HandleType* i_handle_p, int i_setLastDeviceError);

void dCommon_DevideBuff32(void* i_buf, u32 i_size, u32* i_1st_size_p, void* i_2nd_pp, u32* i_2nd_size_p, void* i_3rd_pp, u32* i_3rd_size_p) {
    u32 align = ((u32)i_buf) & 0x1f;
    u32 diff;
    *(void**)i_3rd_pp = NULL;
    *(void**)i_2nd_pp = NULL;
    *i_3rd_size_p = 0;
    *i_2nd_size_p = 0;
    *i_1st_size_p = 0;

    if (align == 0) {
        *i_1st_size_p = 0;
        *(void**)i_2nd_pp = i_buf;
        *i_2nd_size_p = i_size;
        *(void**)i_3rd_pp = NULL;
        *i_3rd_size_p = 0;
        return;
    }

    diff = 0x20 - align;
    *i_1st_size_p = diff;

    if ((i_size - 0x20) != 0) {
        *(void**)i_2nd_pp = (u8*)i_buf + diff;
        *i_2nd_size_p = i_size - 0x20;
    }

    *i_3rd_size_p = align;
    *(void**)i_3rd_pp = (u8*)i_buf + i_size - align;
}

int dCommon_IsPrfFile(void* i_buff_p) {
    struct PR_BINHEADER header;
    VFipf_memcpy(&header, i_buff_p, 0x20);

    if (header.signature[0] != 0x56 || header.signature[1] != 0x46 || header.signature[2] != 0x46 || header.signature[3] != 0x20) {
        return 0;
    }
    return 1;
}

void dCommon_PrintSignature(struct PR_BINHEADER* i_header_p) {
    ;
}

s32 dCommon_MakeFsInfoSec(u8* buf, u32 fsInfoSize) {
    struct PDM_FSINFO fsinfo;
    VFipf_memset(buf, 0, fsInfoSize);
    fsinfo.free_count = -1;
    fsinfo.next_free = -1;
    return VFipdm_bpb_set_fsinfo_information(&fsinfo, buf);
}

u32 dCommon_GetPhysicalOffset(u32 startBlock, u32 BPS, u32 reservedSecNum) {
    return ((startBlock - reservedSecNum) * BPS) + 0x20;
}

enum FatType dCommon_GetNiceFatType(u32* spf, u32 SPU, u32 SPC, u32 BPS) {
    u32 SPU_div_SPC = SPU / SPC;

    // This prevents dCommon_GetNiceFatType from being inlined in dCommon_MakeBootSector.
    int i;
    for (i = 0; i < 1; i++) {
    }  // Fake loop

    if (SPU_div_SPC < 0xff5) {
        if (spf != NULL) {
            *spf = (((SPU_div_SPC * 3) / 2) + BPS - 1) / BPS;
        }
        return FAT_12;
    }

    if (SPU_div_SPC < 0xfff5) {
        if (spf != NULL) {
            *spf = ((SPU_div_SPC * 2) + BPS - 1) / BPS;
        }
        return FAT_16;
    }

    if (spf != NULL) {
        *spf = ((SPU_div_SPC * 4) + BPS - 1) / BPS;
    }

    return FAT_32;
}

u32 dCommon_GetReservedSecFromFatType(enum FatType fatType) {
    if (fatType == FAT_32) {
        return 0x20;
    }
    return 1;
}

u32 dCommon_GetRootEntNumFromFatType(enum FatType fatType) {
    return (fatType == FAT_32) ? 0 : 0x80;
}

void dCommon_MakeBootSector(u8* buf, enum FatType* type, u32 SPU, u32 SPC, u32 BPS, u8 jump0_1, u8 jump2, u32 secPerTrack, u32 reservedSecNum, u32 rootEntNum, u8 mediaDesc) {
    u32 spf;
    *type = dCommon_GetNiceFatType(&spf, SPU, SPC, BPS);

    VFipf_memset(buf, 0, 0x200);

    buf[0] = jump0_1;
    buf[2] = jump2;
    buf[0x1fe] = 0x55;
    buf[0x1ff] = 0xaa;

    buf[0x18] = secPerTrack & 0xff;
    buf[0x19] = (secPerTrack >> 8) & 0xff;
    buf[0x1a] = 0xff;
    buf[0x1b] = 0;

    buf[0xb] = BPS & 0xff;
    buf[0xc] = (BPS >> 8) & 0xff;
    buf[0xd] = SPC;
    buf[0xe] = reservedSecNum & 0xff;
    buf[0xf] = (reservedSecNum >> 8) & 0xff;
    buf[0x10] = 2;
    buf[0x11] = rootEntNum & 0xff;
    buf[0x12] = (rootEntNum >> 8) & 0xff;
    buf[0x15] = mediaDesc;

    if (SPU < 0x10000) {
        buf[0x13] = SPU & 0xff;
        buf[0x14] = (SPU >> 8) & 0xff;
        buf[0x20] = 0;
        buf[0x21] = 0;
        buf[0x22] = 0;
        buf[0x23] = 0;
    } else {
        buf[0x13] = 0;
        buf[0x14] = 0;
        buf[0x20] = SPU & 0xff;
        buf[0x21] = (SPU >> 8) & 0xff;
        buf[0x22] = (SPU >> 16) & 0xff;
        buf[0x23] = (SPU >> 24) & 0xff;
    }

    if (*type == FAT_32) {
        buf[0xe] = 0x20;
        buf[0xf] = 0;
        buf[0x11] = 0;
        buf[0x12] = 0;

        buf[0x24] = spf & 0xff;
        buf[0x25] = (spf >> 8) & 0xff;
        buf[0x26] = (spf >> 16) & 0xff;
        buf[0x27] = (spf >> 24) & 0xff;
        buf[0x28] = 0;
        buf[0x29] = 0;
        buf[0x2a] = 0;
        buf[0x2b] = 0;
        buf[0x2c] = 2;
        buf[0x2d] = 0;
        buf[0x2e] = 0;
        buf[0x2f] = 0;
        buf[0x30] = 1;
        buf[0x31] = 0;

        buf[0x41] = 0;
        buf[0x42] = 0x29;
        buf[0x43] = 0x34;
        buf[0x44] = 0x12;
        buf[0x45] = 0;
        buf[0x46] = 0;

        buf[0x40] = 0x80;
        buf[0x32] = 6;
        buf[0x33] = 0;
    } else {
        buf[0x11] = rootEntNum;
        buf[0x12] = rootEntNum >> 8;

        buf[0x16] = spf & 0xff;
        buf[0x17] = (spf >> 8) & 0xff;
        buf[0x25] = 0;
        buf[0x26] = 0x29;
        buf[0x27] = 0x34;
        buf[0x28] = 0x12;
        buf[0x29] = 0;
        buf[0x2a] = 0;
        buf[0x24] = 0x80;
    }
}

int dCommon_ReadDummyBPB(u32 num_blocks, u8* buf, u32 block, u32* p_num_success, struct PDM_DISK* p_disk, s32* p_err, s32 (*makeBS)(struct PDM_DISK*, u8*, enum FatType*), s32 (*makeFS)(u8*)) {
    u32 handleIdx;
    struct DriveInfo* info;
    u32 reservedSecNum;

    *p_err = 0;
    handleIdx = (u32)VFSysPDMDisk2HandleIdx(p_disk);

    if (handleIdx < 0x1a) {
        info = &l_driveInfo[handleIdx];
    } else {
        info = NULL;
    }

    reservedSecNum = info ? info->reserved_sec_num : 0;

    if (block < reservedSecNum) {
        if (block == 0) {
            enum FatType type;
            s32 err;
            err = makeBS(p_disk, buf, &type);
            *p_err = err;
            if (err != 0) {
                return 0;
            } else {
                *p_num_success = num_blocks;
                *p_err = 0;
                return 0;
            }
        } else if (block == 1) {
            u32 handleIdx2;
            struct DriveInfo* info2;
            u32 FatType;

            handleIdx2 = (u32)VFSysPDMDisk2HandleIdx(p_disk);
            if (handleIdx2 < 0x1a) {
                info2 = &l_driveInfo[handleIdx2];
            } else {
                info2 = NULL;
            }

            FatType = info2 ? info2->fat_type : 1;

            if (FatType == FAT_32) {
                s32 err;
                err = makeFS(buf);
                *p_err = err;
                if (err != 0) {
                    return 0;
                } else {
                    *p_num_success = num_blocks;
                    *p_err = 0;
                    return 0;
                }
            } else {
                goto error;
            }
        } else {
        error:
            *p_err = -22;
            return 0;
        }
    } else {
        return 1;
    }
}

int dCommon_WriteDummyBPB(u32 num_blocks, u32 block, u32* p_num_success, struct PDM_DISK* p_disk, s32* p_err) {
    u32 handleIdx;
    struct DriveInfo* info;
    u32 reservedSecNum;

    *p_err = 0;

    handleIdx = (u32)VFSysPDMDisk2HandleIdx(p_disk);

    if (handleIdx < 0x1a) {
        info = &l_driveInfo[handleIdx];
    } else {
        info = NULL;
    }

    reservedSecNum = info ? info->reserved_sec_num : 0;

    if (block < reservedSecNum) {
        if (block != 0) {
            if (block == 1) {
                u32 handleIdx2;
                struct DriveInfo* info2;
                u32 FatType;

                handleIdx2 = (u32)VFSysPDMDisk2HandleIdx(p_disk);

                if (handleIdx2 < 0x1a) {
                    info2 = &l_driveInfo[handleIdx2];
                } else {
                    info2 = NULL;
                }

                FatType = info2 ? info2->fat_type : 1;

                if (FatType != FAT_32) {
                    goto error;
                }
            } else {
                goto error;
            }
        }

        *p_num_success = num_blocks;
        *p_err = 0;
        return 0;

    error:
        *p_err = -22;
        return 0;
    }

    return 1;
}

void dCommon_initDriveInfo() {
    struct DriveInfo* driveInfo_p;
    int i;

    for (i = 0, driveInfo_p = l_driveInfo; i < 26; i++, driveInfo_p++) {
        driveInfo_p->prf_file_size = 0;
        driveInfo_p->last_device_error = 0;
        driveInfo_p->fat_type = 0;
        driveInfo_p->reserved_sec_num = 0;
        driveInfo_p->root_ent_num = 0;
    }
}

u32 dCommon_getFileSizeFromDisk(struct PDM_DISK* p_disk) {
    u32 handleIdx = (u32)VFSysPDMDisk2HandleIdx(p_disk);
    struct DriveInfo* driveInfo_p;

    if (handleIdx < 0x1a) {
        driveInfo_p = &l_driveInfo[handleIdx];
    } else {
        driveInfo_p = NULL;
    }

    return driveInfo_p ? driveInfo_p->prf_file_size : 0;
}

void dCommon_setFileSizeToDisk(struct PDM_DISK* p_disk, u32 i_fileSize) {
    u32 handleIdx = (u32)VFSysPDMDisk2HandleIdx(p_disk);
    struct DriveInfo* driveInfo_p;

    if (handleIdx < 0x1a) {
        driveInfo_p = &l_driveInfo[handleIdx];
    } else {
        driveInfo_p = NULL;
    }

    if (driveInfo_p) {
        driveInfo_p->prf_file_size = i_fileSize;
    }
}

s32 dCommon_getLastDeviceErrorFromDisk(struct PDM_DISK* p_disk) {
    u32 handleIdx = (u32)VFSysPDMDisk2HandleIdx(p_disk);
    struct DriveInfo* driveInfo_p;

    if (handleIdx < 0x1a) {
        driveInfo_p = &l_driveInfo[handleIdx];
    } else {
        driveInfo_p = NULL;
    }

    return driveInfo_p ? driveInfo_p->last_device_error : 0;
}

void dCommon_setLastDeviceErrorToDisk(struct PDM_DISK* p_disk, s32 i_lastDevErr) {
    u32 handleIdx = (u32)VFSysPDMDisk2HandleIdx(p_disk);
    struct DriveInfo* driveInfo_p;

    if (handleIdx < 0x1a) {
        driveInfo_p = &l_driveInfo[handleIdx];
    } else {
        driveInfo_p = NULL;
    }

    if (driveInfo_p) {
        driveInfo_p->last_device_error = i_lastDevErr;
    }
}

void dCommon_setLastDeviceErrorToDisk2(s32 i_handleIdx, s32 i_lastDevErr) {
    if (i_handleIdx >= 0 && i_handleIdx < 0x1a) {
        l_driveInfo[i_handleIdx].last_device_error = i_lastDevErr;
    }
}

s32 dCommon_getHandleIdxFromDisk(struct PDM_DISK* p_disk) {
    return VFSysPDMDisk2HandleIdx(p_disk);
}

void dCommon_setFatTypeToDisk(struct PDM_DISK* p_disk, u32 i_fatType) {
    u32 handleIdx = (u32)VFSysPDMDisk2HandleIdx(p_disk);
    struct DriveInfo* driveInfo_p;

    if (handleIdx < 0x1a) {
        driveInfo_p = &l_driveInfo[handleIdx];
    } else {
        driveInfo_p = NULL;
    }

    if (driveInfo_p) {
        driveInfo_p->fat_type = i_fatType;
    }
}

u32 dCommon_getResvSecNumFromDisk(struct PDM_DISK* p_disk) {
    u32 handleIdx = (u32)VFSysPDMDisk2HandleIdx(p_disk);
    struct DriveInfo* driveInfo_p;

    if (handleIdx < 0x1a) {
        driveInfo_p = &l_driveInfo[handleIdx];
    } else {
        driveInfo_p = NULL;
    }

    return driveInfo_p ? driveInfo_p->reserved_sec_num : 0;
}

void dCommon_setResvSecNumToDisk(struct PDM_DISK* p_disk, u32 i_reservedSecNum) {
    u32 handleIdx = (u32)VFSysPDMDisk2HandleIdx(p_disk);
    struct DriveInfo* driveInfo_p;

    if (handleIdx < 0x1a) {
        driveInfo_p = &l_driveInfo[handleIdx];
    } else {
        driveInfo_p = NULL;
    }

    if (driveInfo_p) {
        driveInfo_p->reserved_sec_num = i_reservedSecNum;
    }
}

u32 dCommon_getRootEntNumFromDisk(struct PDM_DISK* p_disk) {
    u32 handleIdx = (u32)VFSysPDMDisk2HandleIdx(p_disk);
    struct DriveInfo* driveInfo_p;

    if (handleIdx < 0x1a) {
        driveInfo_p = &l_driveInfo[handleIdx];
    } else {
        driveInfo_p = NULL;
    }

    return driveInfo_p ? driveInfo_p->root_ent_num : 0;
}

void dCommon_setRootEntNumToDisk(struct PDM_DISK* p_disk, u32 i_rootEntNum) {
    u32 handleIdx = (u32)VFSysPDMDisk2HandleIdx(p_disk);
    struct DriveInfo* driveInfo_p;

    if (handleIdx < 0x1a) {
        driveInfo_p = &l_driveInfo[handleIdx];
    } else {
        driveInfo_p = NULL;
    }

    if (driveInfo_p) {
        driveInfo_p->root_ent_num = i_rootEntNum;
    }
}

s32 dCommon_flush_from_handle_p(struct HandleType* i_handle_p, int i_setLastDeviceError) {
    struct HandleDrive* vol;
    s32 err;
    s32 handle_idx;

    vol = (struct HandleDrive*)VFSysVol2HandleP(i_handle_p);
    err = -1;
    if (vol != NULL && vol->file_p != NULL) {
        if (((u32*)vol->file_p)[2] == 0) {
            handle_idx = VFSysHandleP2Idx((struct HandleType*)vol);
            if (handle_idx != -1) {
                err = VFi_NandFlushNANDFromHandleIdx(handle_idx, i_setLastDeviceError);
            }
        } else {
            err = 0;
        }
    }
    return err;
}
