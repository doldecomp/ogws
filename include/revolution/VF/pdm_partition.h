#ifndef RVL_SDK_VF_PDM_PARTITION_H
#define RVL_SDK_VF_PDM_PARTITION_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

s32 VFipdm_part_get_start_sector(struct PDM_PARTITION* p_part);
u32 VFipdm_part_chg_ltop(struct PDM_PARTITION* p_part, u32 lsector, u16 lbps);
s32 VFipdm_part_get_handle(struct PDM_DISK* p_disk, u16 part_id, struct PDM_PARTITION** pp_part, u16* p_part_no, u16* p_handle_no);
s32 VFipdm_part_open_partition(struct PDM_DISK* p_disk, u16 part_id, struct PDM_PARTITION** pp_part);
s32 VFipdm_part_close_partition(struct PDM_PARTITION* p_part);
s32 VFipdm_part_get_permission(struct PDM_PARTITION* p_part);
s32 VFipdm_part_release_permission(struct PDM_PARTITION* p_part, u32 mode);
s32 VFipdm_part_format(struct PDM_PARTITION* p_part, const u8* param);
s32 VFipdm_part_logical_read(struct PDM_PARTITION* p_part, u8* buf, u32 lsector, u32 num_sector, u16 bps, u32* p_num_success);
s32 VFipdm_part_logical_write(struct PDM_PARTITION* p_part, const u8* buf, u32 lsector, u32 num_sector, u16 bps, u32* p_num_success);
s32 VFipdm_part_get_media_information(struct PDM_PARTITION* p_part, struct PDM_DISK_INFO* p_disk_info);
s32 VFipdm_part_check_media_write_protect(struct PDM_PARTITION* p_part, u32* is_wprotect);
s32 VFipdm_part_check_media_insert(struct PDM_PARTITION* p_part, u32* is_insert);
s32 VFipdm_part_check_media_detect(struct PDM_PARTITION* p_part, u32* is_detect);
void VFipdm_part_set_change_media_state(struct PDM_DISK* p_disk, u32 event);
void VFipdm_part_set_driver_error_code(struct PDM_PARTITION* p_part, s32 error_code);
s32 VFipdm_part_get_driver_error_code(struct PDM_PARTITION* p_part);

#ifdef __cplusplus
}
#endif
#endif
