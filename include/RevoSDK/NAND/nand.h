#ifndef REVOSDK_NAND_H
#define REVOSDK_NAND_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

struct NANDCommandBlock;
struct NANDFileInfo;

typedef UNKTYPE (* NANDAsyncCallback)(s32, struct NANDCommandBlock *);
typedef UNKTYPE (* NANDCBAsyncCallback)(s32, struct NANDCB_UNK *, UNKWORD);

struct NANDCB_UNK
{
	char UNK_0x0[0x8];
	UNKWORD WORD_0x8;
	NANDCBAsyncCallback CALLBACK_0xC;
	UNKWORD WORD_0x10;
	char UNK_0x14[0x152];
	char BYTE_0x166;
};

struct NANDCommandBlock
{
	char UNK_0x0[0x144];
	struct NANDCB_UNK * PTR_0x144;
};

struct NANDFileInfo
{
	UNKWORD WORD_0x0;
	UNKWORD WORD_0x4;
	
	volatile char BUF_0x8[0x40];
	
	volatile char BUF_0x48[0x40];
	
	char BYTE_0x88;
	char BYTE_0x89;
	char BYTE_0x8a;
};

BOOL NANDOpen(const char *, struct NANDFileInfo *, u8);
UNKWORD NANDGetLength(struct NANDFileInfo *, u32 *);
UNKTYPE NANDClose(struct NANDFileInfo *);
UNKWORD NANDRead(struct NANDFileInfo *, void *, u32);
UNKWORD NANDWrite(struct NANDFileInfo *, const void *, u32);
UNKWORD NANDReadAsync(struct NANDFileInfo *, void *, u32, NANDAsyncCallback, void *);
UNKWORD NANDWriteAsync(struct NANDFileInfo *, const void *, u32, NANDAsyncCallback, void *);

UNKTYPE NANDSeek(struct NANDFileInfo *, u32, UNKWORD);

#ifdef __cplusplus
}
#endif
#endif