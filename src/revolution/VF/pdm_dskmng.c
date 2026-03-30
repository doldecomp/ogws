#include <revolution/VF.h>

PDM_DISK_SET VFipdm_disk_set;

s32 VFipdm_init_diskmanager(u32 config, void* param) {
    u32 i;

    VFipf_memset(&VFipdm_disk_set, 0, 2916);
    for (i = 0; i < 0x1A; i++) {
        VFipdm_disk_set.disk[i].disk_lock_handle = 0;
    }

    for (i = 0; i < 0x1A; i++) {
        VFipdm_disk_set.partition[i].part_lock_handle = 0;
    }

    return 0;
}

s32 VFipdm_open_disk(struct PDM_INIT_DISK* p_init_disk_tbl, struct PDM_DISK** pp_disk) {
    s32 err;

    if (!pp_disk) {
        return 1;
    }

    *pp_disk = 0;
    err = VFipdm_disk_open_disk(p_init_disk_tbl, pp_disk);

    if (!err) {
        return 0;
    }

    return err;
}

s32 VFipdm_close_disk(struct PDM_DISK* p_disk) {
    s32 err;

    if (!p_disk) {
        return 1;
    }

    err = VFipdm_disk_close_disk(p_disk);
    return err;
}

s32 VFipdm_open_partition(struct PDM_DISK* p_disk, s32 part_id, struct PDM_PARTITION** pp_part) {
    s32 err;

    if (!p_disk) {
        return 1;
    }

    if (!pp_part) {
        return 1;
    }

    *pp_part = 0;
    part_id &= 0xFFFF;
    err = VFipdm_part_open_partition(p_disk, part_id, pp_part);
    if (!err) {
        return 0;
    }

    return err;
}

s32 VFipdm_close_partition(struct PDM_PARTITION* p_part) {
    s32 err;

    if (!p_part) {
        return 1;
    }

    err = VFipdm_part_close_partition(p_part);
    if (!err) {
        return 0;
    }

    return err;
}
