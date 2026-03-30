#ifndef RVL_SDK_VF_PF_FAT16_H
#define RVL_SDK_VF_PF_FAT16_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

s32 VFiPFFAT16_ReadFATEntry(struct PF_VOLUME* p_vol, u32 cluster, u32* p_value);
s32 VFiPFFAT16_ReadFATEntryPage(struct PF_VOLUME* p_vol, u32 cluster, u32* p_value, struct PF_CACHE_PAGE** pp_page);
s32 VFiPFFAT16_WriteFATEntry(struct PF_VOLUME* p_vol, u32 cluster, u32 value);
s32 VFiPFFAT16_WriteFATEntryPage(struct PF_VOLUME* p_vol, u32 cluster, u32 value, struct PF_CACHE_PAGE** pp_page);

#ifdef __cplusplus
}
#endif
#endif
