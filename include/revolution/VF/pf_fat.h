#ifndef RVL_SDK_VF_PF_FAT_H
#define RVL_SDK_VF_PF_FAT_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

s32 VFiPFFAT_ReadFATSector(struct PF_VOLUME* p_vol, struct PF_CACHE_PAGE** p_page, u32 cluster);
s32 VFiPFFAT_SearchForNumFreeClusters(struct PF_VOLUME* p_vol, u32 start_cluster, u32 end_cluster, u32 num_cluster, u32* p_start_free_cluster, u32* p_last_free_cluster);
s32 VFiPFFAT_FindClusterLink(struct PF_FFD* p_ffd, u32 chain_index, u32* p_cluster, u32* is_found);
s32 VFiPFFAT_FindClusterLinkPage(struct PF_FFD* p_ffd, u32 chain_index, u32* p_cluster, u32* is_found, struct PF_CACHE_PAGE* p_page);
s32 VFiPFFAT_ReadClusterPage(struct PF_FFD* p_ffd, u32 cluster, u32 chain_index, u32* next_cluster, u32* chk_clstlnk, struct PF_CACHE_PAGE** p_page);
s32 VFiPFFAT_WriteCluster(struct PF_FFD* p_ffd, u32 cluster, u32 chain_index, u32 next_cluster, u32 use_clstlnk);
s32 VFiPFFAT_WriteClusterPage(struct PF_FFD* p_ffd, u32 cluster, u32 chain_index, u32 next_cluster, u32 use_clstlnk, struct PF_CACHE_PAGE** p_page);
s32 VFiPFFAT_DoAllocateChain(struct PF_FFD* p_ffd, u32 chain_len, u32 chain_index, u32* p_chain_start, u32* p_last_allocated);
s32 VFiPFFAT_GetClusterInChain(struct PF_FFD* p_ffd, u32 chain_index, u32 mode, u32 num_cluster, u32* locate_start, u32* locate_end);
s32 VFiPFFAT_GetClusterContinuousSectorInChain(struct PF_FFD* p_ffd, u32 initial_cluster, u32 chain_index, u32 size, u32* p_num_sector);
s32 VFiPFFAT_GetClusterAllocatedInChain(struct PF_FFD* p_ffd, u32 initial_cluster, u32 chain_index, u32 size, u32* p_num_clusters);
s32 VFiPFFAT_GetClusterSpecified(struct PF_FFD* p_ffd, u32 chain_index, u32 may_allocate, u32* p_cluster);
s32 VFiPFFAT_GetClusterAllocated(struct PF_FFD* p_ffd, u32 chain_index, u32 num_cluster, u32* p_cluster, u32* p_num_cluster);
s32 VFiPFFAT_GetSector(struct PF_FFD* p_ffd, u32 file_sector_index, u32 mode, u32 size, u32* p_sector, u32* p_num_sector);
s32 VFiPFFAT_UpdateFATEntry(struct PF_VOLUME* p_vol, struct PF_CACHE_PAGE* p_page);
s32 VFiPFFAT_UpdateAlternateFATEntry(struct PF_VOLUME* p_vol, u8* p_buf, u32 sector, u32 size);
s32 VFiPFFAT_GetSectorSpecified(struct PF_FFD* p_ffd, u32 file_sector_index, u32 may_allocate, u32* p_sector);
s32 VFiPFFAT_GetSectorAllocated(struct PF_FFD* p_ffd, u32 file_sector_index, u32 size, u32* p_sector, u32* p_num_sector);
s32 VFiPFFAT_GetContinuousSector(struct PF_FFD* p_ffd, u32 file_sector_index, u32 size, u32* p_sector, u32* p_num_sector);
s32 VFiPFFAT_CountAllocatedClusters(struct PF_FFD* p_ffd, u32 size, u32* p_num_alloc_clusters);
s32 VFiPFFAT_CountFreeClusters(struct PF_VOLUME* p_vol, u32* p_num_free_clusters);
s32 VFiPFFAT_FreeChain(struct PF_FFD* p_ffd, u32 start_cluster, u32 chain_index, u32 size);
s32 VFiPFFAT_GetBeforeChain(struct PF_VOLUME* p_vol, u32 start_cluster, u32 lActive, u32* p_cluster);
s32 VFiPFFAT_InitFATRegion(struct PF_VOLUME* p_vol);
s32 VFiPFFAT_MakeRootDir(struct PF_VOLUME* p_vol);
void VFiPFFAT_InitHint(struct PF_FAT_HINT* p_hint);
s32 VFiPFFAT_TraceClustersChain(struct PF_FFD* p_ffd, u32 start_clst, u32 size, u32* p_target_clst, u32* p_next_clst);
s32 VFiPFFAT_ReadValueToSpecifiedCluster(struct PF_VOLUME* p_vol, u32 cluster, u32* value);
s32 VFiPFFAT_ResetFFD(struct PF_FFD* p_ffd, u32* p_start_cluster);
s32 VFiPFFAT_InitFFD(struct PF_FFD* p_ffd, struct PF_FAT_HINT* p_hint, struct PF_VOLUME* p_vol, u32* p_start_cluster);
s32 VFiPFFAT_FinalizeFFD(struct PF_FFD* p_ffd);
u32 VFiPFFAT_GetValueOfEOC2(struct PF_VOLUME* p_vol);

#ifdef __cplusplus
}
#endif
#endif
