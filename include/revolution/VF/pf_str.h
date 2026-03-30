#ifndef RVL_SDK_VF_PF_STR_H
#define RVL_SDK_VF_PF_STR_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

void VFiPFSTR_SetCodeMode(struct PF_STR* p_str, u32 code_mode);
u32 VFiPFSTR_GetCodeMode(struct PF_STR* p_str);
void VFiPFSTR_SetLocalStr(struct PF_STR* p_str, s8* p_local);
s8* VFiPFSTR_GetStrPos(struct PF_STR* p_str, u32 target);
void VFiPFSTR_MoveStrPos(struct PF_STR* p_str, s16 num_s8);
s32 VFiPFSTR_InitStr(struct PF_STR* p_str, const s8* s, u32 code_mode);
u16 VFiPFSTR_StrLen(struct PF_STR* p_str);
u16 VFiPFSTR_StrNumChar(struct PF_STR* p_str, u32 target);
s32 VFiPFSTR_StrCmp(const struct PF_STR* p_str, const s8* s);
s32 VFiPFSTR_StrNCmp(struct PF_STR* p_str, const s8* s, u32 target, s16 offset, u16 num);
void VFiPFSTR_ToUpperNStr(struct PF_STR* p_str, u16 num, s8* dest);

#ifdef __cplusplus
}
#endif
#endif
