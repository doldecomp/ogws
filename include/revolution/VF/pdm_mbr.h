#ifndef RVL_SDK_VF_PDM_MBR_H
#define RVL_SDK_VF_PDM_MBR_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

s32 VFipdm_mbr_get_table(u8* buf, u32 sector, struct PDM_MBR* p_mbr_tbl);
s32 VFipdm_mbr_get_mbr_part_table(struct PDM_DISK* p_disk, struct PDM_MBR* p_mbr_tbl);
s32 VFipdm_mbr_get_epbr_part_table(struct PDM_DISK* p_disk, struct PDM_MBR* p_mbr_tbl);
s32 VFipdm_mbr_check_master_boot_record(struct PDM_DISK* p_disk, u8* buf, u32* is_master_boot);

#ifdef __cplusplus
}
#endif
#endif
