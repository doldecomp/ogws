#ifndef REVOSDK_DVD_H
#define REVOSDK_DVD_H
#ifdef __cplusplus
extern "C" {
#endif

typedef void UNKTYPE;
typedef int UNKWORD;

struct DVD_UNK;
struct DVDCB_UNK;

typedef UNKTYPE (* DVDAsyncCallback)(s32, struct DVD_UNK *, UNKWORD);
typedef UNKTYPE (* DVDCBAsyncCallback)(s32, struct DVDCB_UNK *, UNKWORD);

struct DVD_UNK
{
	char UNK_0x0[0x8];
	signed long LONG_0x8;
	DVDAsyncCallback CALLBACK_0xC;
	UNKWORD WORD_0x10;
	char UNK_0x14[0x58];
	char BYTE_0x6C;
};

struct DVDCB_UNK
{
	char UNK_0x0[0x1C];
	DVDCBAsyncCallback CALLBACK_0x1C;
	UNKWORD WORD_0x20;
	char BYTE_0x24;
};

struct DVDFileInfo
{
	char UNK_0x0[0x3C];
	struct DVD_UNK * PTR_0x3C;
};

struct DVDCommandBlock
{
	char UNK_0x0[0x3C];
	struct DVDCB_UNK * PTR_0x3C;
};

#ifdef __cplusplus
}
#endif
#endif