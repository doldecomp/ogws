#include <MetroTRK.h>

DSError TRKMessageSend(TRKMessageBuffer* buf) {
    TRKWriteUARTN(buf->buf, buf->size);
    return kNoError;
}
