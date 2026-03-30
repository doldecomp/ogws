#ifndef RVL_SDK_VF_D_HASH_H
#define RVL_SDK_VF_D_HASH_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

int _MakeWStr(const s8* i_Name);
void dHash_InitHashTable();
s32 dHash_SearchHashW(const u16* i_Name);
int dHash_GetArg(const s8* i_Name);
int dHash_SetArg(const s8* i_Name, u8 i_Arg);
int dHash_DeleteData(const s8* i_Name);

#ifdef __cplusplus
}
#endif
#endif
