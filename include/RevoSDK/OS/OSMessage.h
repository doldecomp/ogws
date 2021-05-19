#ifndef REVOSDK_OS_MESSAGE
#define REVOSDK_OS_MESSAGE
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef void * OSMessage;

struct OSMessageQueue
{
    UNKWORD WORD_0x0;
    UNKWORD WORD_0x4;
    UNKWORD WORD_0x8;
    UNKWORD WORD_0xC;
    UNKWORD WORD_0x10;
    UNKWORD WORD_0x14;
    UNKWORD WORD_0x18;
    UNKWORD WORD_0x1C;
};

UNKWORD OSInitMessageQueue(struct OSMessageQueue *, OSMessage buffer, UNKWORD mesgCount);

#ifdef __cplusplus
}
#endif
#endif