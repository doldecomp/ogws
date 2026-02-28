#ifndef RVL_SDK_VF_PDM_BPB_H
#define RVL_SDK_VF_PDM_BPB_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    VF_FAT_TYPE_FAT12 = 0,
    VF_FAT_TYPE_FAT16 = 1,
    VF_FAT_TYPE_FAT32 = 2
} VF_FAT_TYPE;

typedef struct {
    /* 0x00 */ u8  oem_name[8];
    /* 0x08 */ u16 bytes_per_sec;
    /* 0x0A */ u8  sec_per_clus;
    /* 0x0B */ u8  num_fats;
    /* 0x0C */ u16 rsvd_sec_cnt;
    /* 0x0E */ u16 root_ent_cnt;
    /* 0x10 */ u16 tot_sec16;
    /* 0x12 */ u16 fat_sz16;
    /* 0x14 */ u16 sec_per_trk;
    /* 0x16 */ u8  reserved_16[2];
    /* 0x18 */ u32 hidden_sec;
    /* 0x1C */ u32 tot_sec32;
    /* 0x20 */ u16 num_heads;
    /* 0x22 */ u8  media;
    /* 0x23 */ u8  drv_num;
    /* 0x24 */ u32 vol_id;
    /* 0x28 */ u8  boot_sig;
    /* 0x29 */ u8  vol_lab[11];
    /* 0x34 */ u8  fil_sys_type[8];
    /* 0x3C */ u32 root_cluster_copy;
    /* 0x40 */ u16 ext_flags;
    /* 0x42 */ u16 fs_ver;
    /* 0x44 */ u32 root_cluster;
    /* 0x48 */ u16 fs_info;
    /* 0x4A */ u16 bk_boot_sec;
    /* 0x4C */ u8  jump_boot[3];
    /* 0x4F */ u8  active_fats;
    /* 0x50 */ u32 fat_type;
    /* 0x54 */ u8  bps_shift;
    /* 0x55 */ u8  spc_shift;
    /* 0x56 */ u16 root_dir_secs;
    /* 0x58 */ u32 fat1_start_sec;
    /* 0x5C */ u32 root_start_sec;
    /* 0x60 */ u32 data_start_sec;
    /* 0x64 */ u32 count_of_clusters;
    /* 0x68 */ u32 total_sectors;
    /* 0x6C */ u32 fat_sz;
} VF_BPB;

#ifdef __cplusplus
}
#endif
#endif
