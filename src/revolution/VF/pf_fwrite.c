#include <revolution/VF.h>

u32 VFipf2_fwrite(void* p_buf, u32 size, u32 count, struct PF_FILE* p_file) {
    u32 count_written;
    VFiPFFILE_fwrite(p_buf, size, count, p_file, &count_written);
    return count_written;
}
