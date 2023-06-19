#ifndef REVOSDK_CNT_H
#define REVOSDK_CNT_H
#ifdef __cplusplus
#include <types.h>
#include <RevoSDK/ARC/arc.h>
extern "C" {
#endif

typedef struct
{
    struct ARCHandle *mParent; // at 0x0
    UNKWORD mFileOffset; // at 0x4
    UNKWORD mFileSize; // at 0x8
    UNKWORD WORD_0xC;
} CNTFileInfo;

UNKWORD contentFastOpenNAND(struct ARCHandle *, s32, CNTFileInfo *);
s32 contentConvertPathToEntrynumNAND(struct ARCHandle *, const char *);
UNKWORD contentGetLengthNAND(const CNTFileInfo *);
s32 contentReadNAND(CNTFileInfo *, void *, s32, s32);
UNKWORD contentCloseNAND(CNTFileInfo *);

#ifdef __cplusplus
}
#endif
#endif