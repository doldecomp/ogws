#ifndef REVOSDK_DVD_H
#define REVOSDK_DVD_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef UNKTYPE (* DVDAsyncCallback)(s32, struct DVDFileInfo *);
typedef UNKTYPE (* DVDCBAsyncCallback)(s32, struct DVDCommandBlock *);

struct DVDFileInfo
{
	UNKWORD WORD_0x0;
	UNKWORD WORD_0x4;
	UNKWORD WORD_0x8;
	UNKWORD WORD_0xC;
	UNKWORD WORD_0x10;
	UNKWORD WORD_0x14;
	UNKWORD WORD_0x18;
	UNKWORD WORD_0x1C;
	UNKWORD WORD_0x20;
	UNKWORD WORD_0x24;
	UNKWORD WORD_0x28;
	UNKWORD WORD_0x2C;
	UNKWORD WORD_0x30;
	UNKWORD mFileSize;
	UNKWORD WORD_0x38;
};

struct DVDCommandBlock
{
	UNKWORD WORD_0x0;
	UNKWORD WORD_0x4;
	UNKWORD WORD_0x8;
	UNKWORD WORD_0xC;
	UNKWORD WORD_0x10;
	UNKWORD WORD_0x14;
	UNKWORD WORD_0x18;
	UNKWORD WORD_0x1C;
	UNKWORD WORD_0x20;
	UNKWORD WORD_0x24;
	UNKWORD WORD_0x28;
	UNKWORD WORD_0x2C;
	UNKWORD WORD_0x30;
	UNKWORD WORD_0x34;
	UNKWORD WORD_0x38;
};

u32 DVDGetDriveStatus(void);

s32 DVDConvertPathToEntrynum(const char *);

BOOL DVDFastOpen(s32, struct DVDFileInfo *);

BOOL DVDClose(struct DVDFileInfo *);

s32 DVDReadPrio(struct DVDFileInfo *, void *, u32, s32, UNKWORD);
u32 DVDReadAsyncPrio(struct DVDFileInfo *, void *, u32, s32, DVDAsyncCallback, UNKWORD);

u32 DVDCancel(struct DVDFileInfo *);
u32 DVDCancelAsync(struct DVDFileInfo *, DVDCBAsyncCallback);

UNKWORD DVDGetCommandBlockStatus(struct DVDCommandBlock *);

#ifdef __cplusplus
}
#endif
#endif