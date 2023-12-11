#ifndef RVL_SDK_NAND_CORE_H
#define RVL_SDK_NAND_CORE_H
#include <revolution/NAND/nand.h>
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

void nandRemoveTailToken(char* newp, const char* oldp);
void nandGetHeadToken(char* head, char* rest, const char* path);
void nandGetRelativeName(char* name, const char* path);
void nandConvertPath(char* abs, const char* dir, const char* rel);
BOOL nandIsPrivatePath(const char* path);
BOOL nandIsUnderPrivatePath(const char* path);
BOOL nandIsInitialized(void);
void nandReportErrorCode(s32 result) DECOMP_DONT_INLINE;
s32 nandConvertErrorCode(s32 result);
void nandGenerateAbsPath(char* abs, const char* rel);
void nandGetParentDirectory(char* dir, const char* path);
s32 NANDInit(void);
s32 NANDGetCurrentDir(char* out);
s32 NANDGetHomeDir(char* out);
void nandCallback(s32 result, void* arg);
s32 NANDGetType(const char* path, u8* type);
s32 NANDPrivateGetTypeAsync(const char* path, u8* type,
                            NANDAsyncCallback callback,
                            NANDCommandBlock* block);
const char* nandGetHomeDir(void);
void NANDInitBanner(NANDBanner* banner, u32 flags, const wchar_t* title,
                    const wchar_t* subtitle);

#ifdef __cplusplus
}
#endif
#endif
