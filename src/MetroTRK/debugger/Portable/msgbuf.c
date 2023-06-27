#include <MetroTRK.h>

TRKMessageBuffer gTRKMsgBufs[kMessageBufferNum];

#define SWAP_ENDIAN(dst, src, n)                                               \
    {                                                                          \
        int __i;                                                               \
        for (__i = 0; __i < n; __i++) {                                        \
            ((unsigned char*)dst)[__i] = ((unsigned char*)src)[n - __i - 1];   \
        }                                                                      \
    }

DSError TRKInitializeMessageBuffers(void) {
    int i;

    for (i = 0; i < kMessageBufferNum; i++) {
        TRKInitializeMutex(&gTRKMsgBufs[i].mutex);
        TRKAcquireMutex(&gTRKMsgBufs[i].mutex);
        gTRKMsgBufs[i].used = FALSE;
        TRKReleaseMutex(&gTRKMsgBufs[i].mutex);
    }

    return kNoError;
}

DSError TRKGetFreeBuffer(int* id, TRKMessageBuffer** buffer) {
    DSError err = kMsgBufUnavailable;
    int i;

    *buffer = NULL;

    for (i = 0; i < kMessageBufferNum; i++) {
        TRKMessageBuffer* buf = TRKGetBuffer(i);
        TRKAcquireMutex(&buf->mutex);

        if (!buf->used) {
            buf->size = 0;
            buf->pos = 0;
            buf->used = TRUE;

            *buffer = buf;
            *id = i;

            i = kMessageBufferNum;
            err = kNoError;
        }

        TRKReleaseMutex(&buf->mutex);
    }

    if (err == kMsgBufUnavailable) {
        usr_puts_serial("ERROR : No buffer available\n");
    }

    return err;
}

TRKMessageBuffer* TRKGetBuffer(int i) {
    TRKMessageBuffer* buf = NULL;

    if (i >= 0 && i < kMessageBufferNum) {
        buf = &gTRKMsgBufs[i];
    }

    return buf;
}

void TRKReleaseBuffer(int i) {
    if (i != -1 && i >= 0 && i < kMessageBufferNum) {
        TRKMessageBuffer* buf = &gTRKMsgBufs[i];
        TRKAcquireMutex(&buf->mutex);
        buf->used = FALSE;
        TRKReleaseMutex(&buf->mutex);
    }
}

void TRKResetBuffer(TRKMessageBuffer* buf, BOOL save) {
    buf->size = 0;
    buf->pos = 0;

    if (!save) {
        TRK_memset(buf->data, 0, sizeof(buf->data));
    }
}

DSError TRKSetBufferPosition(TRKMessageBuffer* buf, unsigned int pos) {
    DSError err = kNoError;

    if (pos > sizeof(buf->data)) {
        err = kMsgWriteOverflow;
    } else {
        buf->pos = pos;
        if (pos > buf->size) {
            buf->size = pos;
        }
    }

    return err;
}

DSError TRKAppendBuffer(TRKMessageBuffer* buf, const void* src,
                        unsigned int n) {
    DSError err = kNoError;
    unsigned long avail;

    // Nothing to write
    if (n == 0) {
        return kNoError;
    }

    // Clamp write size
    avail = sizeof(buf->data) - buf->pos;
    if (avail < n) {
        err = kMsgWriteOverflow;
        n = avail;
    }

    // Don't use memcpy for single byte
    if (n == 1) {
        buf->data[buf->pos] = *(unsigned char*)src;
    } else {
        TRK_memcpy(buf->data + buf->pos, src, n);
    }

    buf->pos += n;
    buf->size = buf->pos;

    return err;
}

DSError TRKReadBuffer(TRKMessageBuffer* buf, void* dst, unsigned int n) {
    DSError err = kNoError;
    unsigned long avail;

    // Nothing to read
    if (n == 0) {
        return kNoError;
    }

    // Clamp read size
    avail = buf->size - buf->pos;
    if (n > avail) {
        err = kMsgReadOverflow;
        n = avail;
    }

    TRK_memcpy(dst, buf->data + buf->pos, n);
    buf->pos += n;

    return err;
}

DSError TRKAppendBuffer1_ui8(TRKMessageBuffer* buf, unsigned char x) {
    if (buf->pos >= sizeof(buf->data)) {
        return kMsgWriteOverflow;
    }

    buf->data[buf->pos++] = x;
    buf->size++;
    return kNoError;
}

DSError TRKAppendBuffer1_ui32(TRKMessageBuffer* buf, unsigned int x) {
    DSError err;
    unsigned char work[sizeof(unsigned int)];
    unsigned char* p;

    if (gTRKBigEndian) {
        p = (unsigned char*)&x;
    } else {
        p = work;
        SWAP_ENDIAN(p, &x, sizeof(unsigned int));
    }

    return TRKAppendBuffer(buf, p, sizeof(unsigned int));
}

DSError TRKAppendBuffer1_ui64(TRKMessageBuffer* buf, unsigned long long x) {
    DSError err;
    unsigned char work[sizeof(unsigned long long)];
    unsigned char* p;

    if (gTRKBigEndian) {
        p = (unsigned char*)&x;
    } else {
        p = work;
        SWAP_ENDIAN(p, &x, sizeof(unsigned long long));
    }

    return TRKAppendBuffer(buf, p, sizeof(unsigned long long));
}

DSError TRKAppendBuffer_ui8(TRKMessageBuffer* buf, const unsigned char* x,
                            int n) {
    DSError err = kNoError;
    int i;

    for (i = 0, err = kNoError; err == kNoError && i < n; i++) {
        err = TRKAppendBuffer1_ui8(buf, x[i]);
    }

    return err;
}

DSError TRKAppendBuffer_ui32(TRKMessageBuffer* buf, const unsigned int* x,
                             int n) {
    DSError err = kNoError;
    int i;

    for (i = 0, err = kNoError; err == kNoError && i < n; i++) {
        err = TRKAppendBuffer1_ui32(buf, x[i]);
    }

    return err;
}

DSError TRKReadBuffer1_ui8(TRKMessageBuffer* buf, unsigned char* dst) {
    return TRKReadBuffer(buf, dst, sizeof(unsigned char));
}

DSError TRKReadBuffer1_ui32(TRKMessageBuffer* buf, unsigned int* dst) {
    DSError err;
    unsigned char work[sizeof(unsigned int)];
    unsigned char* p;

    if (gTRKBigEndian) {
        p = (unsigned char*)dst;
    } else {
        p = work;
    }

    err = TRKReadBuffer(buf, p, sizeof(unsigned int));

    if (!gTRKBigEndian && err == kNoError) {
        SWAP_ENDIAN(dst, p, sizeof(unsigned int));
    }

    return err;
}

DSError TRKReadBuffer1_ui64(TRKMessageBuffer* buf, unsigned long long* dst) {
    DSError err;
    unsigned char work[sizeof(unsigned long long)];
    unsigned char* p;

    if (gTRKBigEndian) {
        p = (unsigned char*)dst;
    } else {
        p = work;
    }

    err = TRKReadBuffer(buf, p, sizeof(unsigned long long));

    if (!gTRKBigEndian && err == kNoError) {
        SWAP_ENDIAN(dst, p, sizeof(unsigned long long));
    }

    return err;
}

DSError TRKReadBuffer_ui8(TRKMessageBuffer* buf, unsigned char* dst, int n) {
    DSError err;
    int i;

    for (i = 0, err = kNoError; err == kNoError && i < n; i++) {
        err = TRKReadBuffer1_ui8(buf, dst + i);
    }

    return err;
}

DSError TRKReadBuffer_ui32(TRKMessageBuffer* buf, unsigned int* dst, int n) {
    DSError err;
    int i;

    for (i = 0, err = kNoError; err == kNoError && i < n; i++) {
        err = TRKReadBuffer1_ui32(buf, dst + i);
    }

    return err;
}
