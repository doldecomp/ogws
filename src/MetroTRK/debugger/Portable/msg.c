#include <MetroTRK.h>

DSError TRKMessageSend(TRKMessageBuffer* buf) {
    TRKWriteUARTN(buf->data, buf->size);
    return kNoError;
}
