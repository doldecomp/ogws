#ifndef RVL_SDK_VF_PDM_DISK_H
#define RVL_SDK_VF_PDM_DISK_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

s32 VFipdm_disk_convert_sector_into_block(struct PDM_DISK* p_disk, u32 sector, u32 num_sector, u16 bps, u32* p_block, u32* p_num_block);
s32 VFipdm_disk_convert_block_into_sector(struct PDM_DISK* p_disk, u32 block, u32 num_block, u16 bps, u32* p_sector, u32* p_num_sector);
s32 VFipdm_disk_get_handle(struct PDM_INIT_DISK* p_init_disk_tbl, struct PDM_DISK** pp_disk, u16* p_disk_no, u16* p_handle_no);
s32 VFipdm_disk_do_get_permission(struct PDM_DISK* p_disk, struct PDM_DISK* lp_disk);
s32 VFipdm_disk_check_disk_handle(struct PDM_DISK* p_disk);
s32 VFipdm_disk_open_disk(struct PDM_INIT_DISK* p_init_disk_tbl, struct PDM_DISK** pp_disk);
s32 VFipdm_disk_close_disk(struct PDM_DISK* p_disk);
s32 VFipdm_disk_get_part_permission(struct PDM_DISK* p_disk);
s32 VFipdm_disk_release_part_permission(struct PDM_DISK* p_disk, u32 mode);
s32 VFipdm_disk_physical_read(struct PDM_DISK* p_disk, u8* buf, u32 psector, u32 num_sector, u16 bps, u32* p_num_success);
s32 VFipdm_disk_physical_write(struct PDM_DISK* p_disk, const u8* buf, u32 psector, u32 num_sector, u16 bps, u32* p_num_success);
s32 VFipdm_disk_format(struct PDM_DISK* p_disk, const u8* param);
s32 VFipdm_disk_get_lba_size(struct PDM_DISK* p_disk, u16* p_lba_size);
s32 VFipdm_disk_get_media_information(struct PDM_DISK* p_disk, struct PDM_DISK_INFO* p_disk_info);
s32 VFipdm_disk_check_media_insert(struct PDM_DISK* p_disk, u32* is_insert);
s32 VFipdm_disk_set_disk(struct PDM_DISK* p_disk, struct PDM_PARTITION* p_part);
void VFipdm_disk_notify_media_insert(struct PDM_DISK* p_disk);

#ifdef __cplusplus
}
#endif
#endif
