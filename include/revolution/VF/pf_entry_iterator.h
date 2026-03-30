#ifndef RVL_SDK_VF_PF_ENTRY_ITERATOR_H
#define RVL_SDK_VF_PF_ENTRY_ITERATOR_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

static s32 VFiPFENT_RecalcEntryIterator(struct PF_ENT_ITER* p_iter, u32 may_allocate);
static s32 VFiPFENT_ITER_FindCluster(struct PF_ENT_ITER* p_iter, struct PF_DIR_ENT* p_ent, u32 cluster, u32* p_is_found);
static s32 VFiPFENT_ITER_DoFindEntry(struct PF_ENT_ITER* p_iter, struct PF_DIR_ENT* p_ent, struct PF_STR* p_pattern, u8 attr_required, u8 attr_unwanted, u32* p_is_found, u32 is_skip);
static s32 VFiPFENT_ITER_DoGetEntry(struct PF_ENT_ITER* p_iter, struct PF_DIR_ENT* p_ent, struct PF_VOLUME* p_vol, struct PF_STR* p_path, u32 wildcard, u32 no_look_last_token);
s32 VFiPFENT_ITER_IteratorInitialize(struct PF_ENT_ITER* p_iter, u32 index_start_from);
u32 VFiPFENT_ITER_IsAtLogicalEnd(struct PF_ENT_ITER* p_iter);
s32 VFiPFENT_ITER_Advance(struct PF_ENT_ITER* p_iter, u32 may_allocate);
s32 VFiPFENT_ITER_Retreat(struct PF_ENT_ITER* p_iter, u32 may_allocate);
s32 VFiPFENT_ITER_GetEntryOfPath(struct PF_ENT_ITER* p_iter, struct PF_DIR_ENT* p_ent, struct PF_VOLUME* p_vol, struct PF_STR* p_path, u32 no_look_last_token);

#ifdef __cplusplus
}
#endif
#endif
