#ifndef RVL_SDK_VF_PF_PATH_H
#define RVL_SDK_VF_PF_PATH_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

s32 VFiPFPATH_DoSplitPath(struct PF_STR* p_path, struct PF_STR* p_dir_path, struct PF_STR* p_filename, u32 wildcard);
u16 VFiPFPATH_GetNextCharOfPattern(struct PF_STR* p_pattern, u32 is_long_name);
u32 VFiPFPATH_DoMatchFileNameWithPattern(u16 c_name, struct PF_FILE_NAME_ITER* p_name, u16 c_pat, struct PF_STR* p_pattern, u32 is_long_name);
s32 VFiPFPATH_cmpNameImpl(const s8* sName, const s8* sPattern, u32* p_is_end);
s32 VFiPFPATH_cmpNameUni(const u16* p_name, struct PF_STR* sPattern);
s32 VFiPFPATH_cmpName(const s8* sShort, struct PF_STR* p_pattern, u32 is_short_search);
s32 VFiPFPATH_cmpTailSFN(const s8* sfn_name, const s8* pattern);
void VFiPFPATH_InitTokenOfPath(struct PF_STR* p_str, s8* path, u32 code_mode);
s32 VFiPFPATH_GetNextTokenOfPath(struct PF_STR* p_str, u32 wildcard);
s32 VFiPFPATH_SplitPath(struct PF_STR* p_path, struct PF_STR* p_dir_path, struct PF_STR* p_filename);
struct PF_VOLUME* VFiPFPATH_GetVolumeFromPath(struct PF_STR* p_path);
u32 VFiPFPATH_MatchFileNameWithPattern(const s8* file_name, struct PF_STR* p_pattern, u32 is_long_name);
s32 VFiPFPATH_putShortName(u8* pDirEntry, const s8* short_name, u8 attr);
s32 VFiPFPATH_getShortName(s8* short_name, const u8* pDirEntry, u8 attr);
void VFiPFPATH_getLongNameformShortName(s8* short_name, s8* long_name, u8 flag);
u32 VFiPFPATH_GetLengthFromShortname(const s8* sSrc);
u32 VFiPFPATH_GetLengthFromUnicode(const u16* sSrc);
s32 VFiPFPATH_transformFromUnicodeToNormal(s8* sDest, const u16* sSrc);
s32 VFiPFPATH_transformInUnicode(u16* sDestStr, const s8* sSrcStr);
u32 VFiPFPATH_parseShortName(s8* pDest, struct PF_STR* p_pattern);
s32 VFiPFPATH_parseShortNameNumeric(s8* p_char, u32 count);
u32 VFiPFPATH_CheckExtShortNameSignature(struct PF_STR* p_str);
u32 VFiPFPATH_CheckExtShortName(struct PF_STR* p_str, u32 target, u32 wildcard);
u32 VFiPFPATH_GetExtShortNameIndex(struct PF_STR* p_str, u32* p_index);
s32 VFiPFPATH_AdjustExtShortName(s8* pName, u32 position);

#ifdef __cplusplus
}
#endif
#endif
