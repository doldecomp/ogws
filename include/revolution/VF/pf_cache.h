#ifndef RVL_SDK_VF_PF_CACHE_H
#define RVL_SDK_VF_PF_CACHE_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

s32 VFiPFCACHE_InitPageList(struct PF_VOLUME* p_vol, struct PF_CACHE_PAGE** pp_head, struct PF_CACHE_PAGE* pages, u8 (*buffers)[512], u16 num, u32 size, u32 is_fat);
struct PF_CACHE_PAGE* VFiPFCACHE_SearchForPage(struct PF_VOLUME* p_vol, struct PF_CACHE_PAGE* p_head, u32 sector);
u32 VFiPFCACHE_SearchForFreePage(struct PF_CACHE_PAGE* p_head, struct PF_CACHE_PAGE** pp_page);
s32 VFiPFCACHE_FlushPageIfNeeded(struct PF_VOLUME* p_vol, struct PF_CACHE_PAGE* p_page);
s32 VFiPFCACHE_DoAllocatePage(struct PF_VOLUME* p_vol, struct PF_CACHE_PAGE** pp_head, u32 sector, struct PF_CACHE_PAGE** pp_page, u32* p_is_hit);
s32 VFiPFCACHE_DoReadPage(struct PF_VOLUME* p_vol, struct PF_CACHE_PAGE** pp_head, u32 sector, struct PF_CACHE_PAGE** pp_page, u32 set_sig);
s32 VFiPFCACHE_DoReadPageAndFlushIfNeeded(struct PF_VOLUME* p_vol, struct PF_CACHE_PAGE** pp_head, u32 sector, struct PF_CACHE_PAGE** pp_page, u32 set_sig);
s32 VFiPFCACHE_DoReadNumSector(struct PF_VOLUME* p_vol, struct PF_CACHE_PAGE** pp_head, u8* p_buf, u32 sector, u32 num_sector, u32* p_num_success);
s32 VFiPFCACHE_DoWritePage(struct PF_VOLUME* p_vol, struct PF_CACHE_PAGE** pp_head, struct PF_CACHE_PAGE* p_page, u32 set_sig);
s32 VFiPFCACHE_DoWriteSector(struct PF_VOLUME* p_vol, struct PF_CACHE_PAGE** pp_head, const u8* p_buf, u32 sector);
s32 VFiPFCACHE_DoWriteNumSectorAndFreeIfNeeded(struct PF_VOLUME* p_vol, struct PF_CACHE_PAGE** pp_head, const u8* p_buf, u32 sector, u32 num_sector, u32* p_num_success);
s32 VFiPFCACHE_DoFlushCache(struct PF_VOLUME* p_vol, struct PF_CACHE_PAGE* p_head);
void VFiPFCACHE_SetCache(struct PF_VOLUME* p_vol, struct PF_CACHE_PAGE* p_cache_page, u8 (*p_cache_buf)[512], u16 num_fat_pages, u16 num_data_pages);
void VFiPFCACHE_SetFATBufferSize(struct PF_VOLUME* p_vol, u32 size);
void VFiPFCACHE_SetDataBufferSize(struct PF_VOLUME* p_vol, u32 size);
s32 VFiPFCACHE_InitCaches(struct PF_VOLUME* p_vol);
s32 VFiPFCACHE_UpdateModifiedSector(struct PF_CACHE_PAGE* p_page);
s32 VFiPFCACHE_AllocateFATPage(struct PF_VOLUME* p_vol, u32 sector, struct PF_CACHE_PAGE** pp_page);
s32 VFiPFCACHE_AllocateDataPage(struct PF_VOLUME* p_vol, u32 sector, struct PF_CACHE_PAGE** pp_page);
void VFiPFCACHE_FreeFATPage(struct PF_VOLUME* p_vol, struct PF_CACHE_PAGE* p_page);
void VFiPFCACHE_FreeDataPage(struct PF_VOLUME* p_vol, struct PF_CACHE_PAGE* p_page);
s32 VFiPFCACHE_ReadFATPage(struct PF_VOLUME* p_vol, u32 sector, struct PF_CACHE_PAGE** pp_page);
s32 VFiPFCACHE_ReadDataPage(struct PF_VOLUME* p_vol, u32 sector, struct PF_CACHE_PAGE** pp_page, u32 set_sig);
s32 VFiPFCACHE_ReadDataPageAndFlushIfNeeded(struct PF_VOLUME* p_vol, u32 sector, struct PF_CACHE_PAGE** pp_page, u32 set_sig);
s32 VFiPFCACHE_ReadDataNumSector(struct PF_VOLUME* p_vol, u8* p_buf, u32 sector, u32 num_sector, u32* p_num_success);
s32 VFiPFCACHE_WriteFATPage(struct PF_VOLUME* p_vol, struct PF_CACHE_PAGE* p_page);
s32 VFiPFCACHE_WriteDataPage(struct PF_VOLUME* p_vol, struct PF_CACHE_PAGE* p_page, u32 set_sig);
s32 VFiPFCACHE_WriteFATSectorAndFreeIfNeeded(struct PF_VOLUME* p_vol, const u8* p_buf, u32 sector);
s32 VFiPFCACHE_WriteDataNumSectorAndFreeIfNeeded(struct PF_VOLUME* p_vol, const u8* p_buf, u32 sector, u32 num_sector, u32* p_num_success);
struct PF_CACHE_PAGE* VFiPFCACHE_SearchDataCache(struct PF_VOLUME* p_vol, u32 sector);
s32 VFiPFCACHE_FlushFATCache(struct PF_VOLUME* p_vol);
s32 VFiPFCACHE_FlushDataCacheSpecific(struct PF_VOLUME* p_vol, void* signature);
s32 VFiPFCACHE_FlushAllCaches(struct PF_VOLUME* p_vol);
void VFiPFCACHE_FreeAllCaches(struct PF_VOLUME* p_vol);

#ifdef __cplusplus
}
#endif
#endif
