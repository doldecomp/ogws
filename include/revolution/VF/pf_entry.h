#ifndef RVL_SDK_VF_PF_ENTRY_H
#define RVL_SDK_VF_PF_ENTRY_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

static u32 VFiPFENT_compareAttr(u8 attr, u8 attr_required, u8 attr_unwanted);
static s32 VFiPFENT_compareEntryName(struct PF_DIR_ENT* p_ent, struct PF_STR* p_pattern, u8 attr);
static s32 VFiPFENT_getEntry(struct PF_DIR_ENT* p_ent, struct PF_ENT_ITER* p_iter, struct PF_STR* p_pattern, u8 attr_required, u8 attr_unwanted, u32* logical_index);
static s32 VFiPFENT_searchEmptyTailSFN(struct PF_FFD* p_ffd, u32 tail_index, const s8* pattern, u32* p_tail_bit);
static s32 VFiPFENT_findEmptyTailSFN(struct PF_DIR_ENT* p_ent_containig_dir, const s8* name, u32* p_tails);
u8 VFiPFENT_CalcCheckSum(struct PF_DIR_ENT* p_ent);
void VFiPFENT_LoadShortNameFromBuf(struct PF_DIR_ENT* p_ent, const u8* buf);
void VFiPFENT_loadEntryNumericFieldsFromBuf(struct PF_DIR_ENT* p_ent, const u8* buf);
s32 VFiPFENT_LoadLFNEntryFieldsFromBuf(struct PF_DIR_ENT* p_ent, const u8* buf);
void VFiPFENT_storeLFNEntryFieldsToBuf(u8* buf, struct PF_DIR_ENT* p_ent, u8 ord, u8 sum, u32 is_last);
s32 VFiPFENT_findEntryPos(struct PF_FFD* p_ffd, struct PF_DIR_ENT* p_ent, u32 index_search_from, struct PF_STR* p_pattern, u8 attr_required, u8 attr_unwanted, u32* p_lpos, u32* p_ppos);
s32 VFiPFENT_findEntry(struct PF_FFD* p_ffd, struct PF_DIR_ENT* p_ent, u32 index_search_from, struct PF_STR* p_pattern, u8 attr_required, u8 attr_unwanted);
s32 VFiPFENT_allocateEntryPos(struct PF_DIR_ENT* p_ent, u8 num_entries, struct PF_FFD* p_ffd, u32* p_next_chain, struct PF_STR* p_filename, u32* p_pos);
s32 VFiPFENT_allocateEntry(struct PF_DIR_ENT* p_ent, u8 num_entries, struct PF_FFD* p_ffd, u32* p_next_chain, struct PF_STR* p_filename);
s32 VFiPFENT_GetRootDir(struct PF_VOLUME* p_vol, struct PF_DIR_ENT* p_ent);
s32 VFiPFENT_MakeRootDir(struct PF_VOLUME* p_vol);
s32 VFiPFENT_updateEntry(struct PF_DIR_ENT* p_ent, u32 flag);
s32 VFiPFENT_AdjustSFN(struct PF_DIR_ENT* p_ent, s8* p_short_name);
s32 VFiPFENT_RemoveEntry(struct PF_DIR_ENT* p_ent, struct PF_ENT_ITER* p_iter);
u8 VFiPFENT_getcurrentDateTimeForEnt(u16* p_date, u16* p_time);

#ifdef __cplusplus
}
#endif
#endif
