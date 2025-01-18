#include <revolution/FS.h>
#include <revolution/OS.h>
#include <revolution/USB.h>
#include <stdio.h>

#define USB_HEAP_SIZE 0x1000

typedef enum {
    USB_NCLEAN_CLOSEDEVICE = 0,
    USB_NCLEAN_BULKMSG = 3,
    USB_NCLEAN_CTRLMSG = 7,
    USB_NCLEAN_MAX = 8
} USBNClean;

typedef enum {
    USB_IOCTLV_CTRLMSG,
    USB_IOCTLV_BLKMSG,
    USB_IOCTLV_INTRMSG
} USBIoctl;

typedef struct USBMsg {
    void* buffer; // at 0x0
    u16 length;   // at 0x4
} USBMsg;

typedef struct USBCommandBlock {
    USBCallback callback; // at 0x0
    void* callbackArg;    // at 0x4
    char UNK_0x8[0x4];
    void* clean[USB_NCLEAN_MAX]; // at 0xC
    u32 nclean;                  // at 0x2C
    char UNK_0x30[0x40 - 0x30];
    union {
        char path[FS_MAX_PATH];
        USBMsg msg;
    }; // at 0x40
} USBCommandBlock;

static s32 hId = -1;

static void* lo = NULL;
static void* hi = NULL;

static u8 s_usb_log = FALSE;

static void USB_LOG(const char* fmt, ...) {
    va_list list;

    if (s_usb_log) {
        OSReport("USB: ");
        va_start(list, fmt);
        vprintf(fmt, list);
        va_end(list);
    }
}

static void USB_ERR(const char* fmt, ...) {
    va_list list;

    if (s_usb_log) {
        OSReport("USB ERR: ");
        va_start(list, fmt);
        vprintf(fmt, list);
        va_end(list);
    }
}

static void* IOSAlloc(size_t size) {
    void* mem;

    mem = iosAllocAligned(hId, size, 32);

    if (mem == NULL) {
        USB_ERR("iosAllocAligned(%d, %u) failed: %d\n", hId, size, mem);
    }

    return mem;
}

static void IOSFree(void* mem) {
    s32 result;

    if (mem != NULL) {
        result = iosFree(hId, mem);

        if (result < 0) {
            USB_ERR("iosFree(%d, 0x%x) failed: %d\n", hId, mem, result);
        }
    }
}

IPCResult IUSB_OpenLib(void) {
    IPCResult result;
    BOOL enabled;

    result = IPC_RESULT_OK;
    enabled = OSDisableInterrupts();

    if (hId != -1) {
        USB_LOG("Library is already initialized. Heap Id = %d\n", hId);
        goto end;
    }

    if (lo == NULL) {
        lo = IPCGetBufferLo();
        hi = IPCGetBufferHi();

        USB_LOG("iusb size: %d lo: %x hi: %x\n", sizeof(USBCommandBlock), lo,
                hi);

        if ((u8*)lo + USB_HEAP_SIZE > hi) {
            USB_ERR("Not enough IPC arena\n");
            result = IPC_RESULT_ALLOC_FAILED;
            goto end;
        }

        IPCSetBufferLo((u8*)lo + USB_HEAP_SIZE);
    }

    hId = iosCreateHeap(lo, USB_HEAP_SIZE);
    if (hId < 0) {
        USB_ERR("Not enough heaps\n");
        result = IPC_RESULT_ALLOC_FAILED;
    }

end:
    OSRestoreInterrupts(enabled);
    return result;
}

IPCResult IUSB_CloseLib(void) {
    return IPC_RESULT_OK;
}

static s32 _intBlkCtrlCb(s32 result, void* arg) {
    int i;
    USBCommandBlock* block = (USBCommandBlock*)arg;

    USB_LOG("_intrBlkCtrlCb returned: %d\n", result);
    USB_LOG("_intrBlkCtrlCb: nclean = %d\n", block->nclean);

    if (block->nclean != USB_NCLEAN_CTRLMSG &&
        block->nclean != USB_NCLEAN_BULKMSG &&
        block->nclean != USB_NCLEAN_CLOSEDEVICE) {
        USB_ERR("__intBlkCtrlCb: got invalid nclean\n");
    } else {
        for (i = 0; i < block->nclean; i++) {
            USB_LOG("Freeing clean[%d] = %x\n", i, block->clean[i]);
            IOSFree(block->clean[i]);
        }
    }

    USB_LOG("cb = %x cbArg = %x\n", block->callback, block->callbackArg);

    if (block->callback != NULL) {
        block->callback(result, block->callbackArg);
    }

    IOSFree(block);
    return result;
}

IPCResult IUSB_OpenDeviceIds(const char* interface, u16 vid, u16 pid,
                             IPCResult* resultOut) {
    IPCResult result;
    USBCommandBlock* block;

    block = NULL;

    if (resultOut == NULL) {
        result = IPC_RESULT_INVALID_INTERNAL;
        goto end;
    }

    block = IOSAlloc(sizeof(USBCommandBlock));
    if (block == NULL) {
        USB_ERR("OpenDeviceIds: Not enough memory\n");
        result = IPC_RESULT_ALLOC_FAILED;
        goto end;
    }

    snprintf(block->path, sizeof(block->path), "/dev/usb/%s/%x/%x", interface,
             vid, pid);
    USB_LOG("OpenDevice - %s\n", block->path);

    result = IOS_Open(block->path, IPC_OPEN_NONE);
    USB_LOG("OpenDevice returned: %d\n", result);

    *resultOut = result;

end:
    IOSFree(block);
    return result;
}

// clang-format off
DECOMP_FORCEACTIVE(usb_c,
                   "OpenDevice\n",
                   "OpenDeviceIdsAsync: Not enough memory\n",
                   "CloseDevice\n",
                   "CloseDevice returned: %d\n");
// clang-format on

IPCResult IUSB_CloseDeviceAsync(s32 fd, USBCallback callback,
                                void* callbackArg) {
    IPCResult result;
    USBCommandBlock* block;

    USB_LOG("CloseDevice\n");

    block = IOSAlloc(sizeof(USBCommandBlock));
    if (block == NULL) {
        USB_ERR("CloseDeviceAsync: Not enough memory\n");
        result = IPC_RESULT_ALLOC_FAILED;
        goto end;
    }

    block->callback = callback;
    block->callbackArg = callbackArg;
    block->nclean = USB_NCLEAN_CLOSEDEVICE;

    result = IOS_CloseAsync(fd, _intBlkCtrlCb, block);
    USB_LOG("CloseDevice returned: %d\n", result);

    if (result < 0) {
        IOSFree(block);
    }

end:
    return result;
}

// clang-format off
DECOMP_FORCEACTIVE(usb_c,
                   "openDevice: Not enough memory\n",
                   "getDeviceList: Not enough memory\n");
// clang-format on

static IPCResult __IntrBlkMsgInt(s32 fd, u32 endpoint, u32 length, void* buffer,
                                 u8 ioctl, USBCallback callback,
                                 void* callbackArg, u8 async) {
    IPCResult result;
    IPCIOVector* vectors;
    u8* endpointWork;
    u16* lengthWork;
    USBCommandBlock* block;

    vectors = (IPCIOVector*)IOSAlloc(0x60);
    endpointWork = (u8*)IOSAlloc(32);
    lengthWork = (u16*)IOSAlloc(32);

    if (vectors == NULL || endpointWork == NULL || lengthWork == NULL) {
        USB_ERR("__IntrBlkMsgInt: Not enough memory\n");
        result = IPC_RESULT_ALLOC_FAILED;
        goto end;
    }

    *endpointWork = (u8)endpoint;
    *lengthWork = (u16)length;

    // Input vector 1: Transfer endpoint
    vectors[0].base = endpointWork;
    vectors[0].length = sizeof(u8);

    // Input vector 2: Transfer length
    vectors[1].base = lengthWork;
    vectors[1].length = sizeof(u16);

    // Output vector 1: Transfer buffer
    vectors[2].base = buffer;
    vectors[2].length = length;

    DCFlushRange(endpointWork, 32);
    DCFlushRange(lengthWork, 32);
    DCFlushRange(vectors, 0x60);

    if (!async) {
        result = IOS_Ioctlv(fd, ioctl, 2, 1, vectors);
        USB_LOG("intr/blk ioctl returned: %d\n", result);
        goto end;
    }

    block = IOSAlloc(sizeof(USBCommandBlock));
    if (block == NULL) {
        USB_ERR("IntBlkMsgInt (async): Not enough memory\n");
        result = IPC_RESULT_ALLOC_FAILED;
        goto end;
    }

    block->callback = callback;
    block->callbackArg = callbackArg;
    USB_LOG("intrblkmsg: cb = 0x%x cbArg = 0x%x\n", block->callback,
            block->callbackArg);

    // Mark memory for deletion
    block->nclean = USB_NCLEAN_BULKMSG;
    block->clean[0] = endpointWork;
    block->clean[1] = lengthWork;
    block->clean[2] = vectors;

    block->msg.buffer = buffer;
    block->msg.length = length;

    result = IOS_IoctlvAsync(fd, ioctl, 2, 1, vectors, _intBlkCtrlCb, block);
    if (result >= IPC_RESULT_OK) {
        goto end_async;
    }

    IOSFree(block);

// Non-async (or unsuccessful async) means we must manually free memory
end:
    IOSFree(endpointWork);
    IOSFree(lengthWork);
    IOSFree(vectors);

// Async callback automatically freed the memory marked in block->clean
end_async:
    return result;
}

IPCResult IUSB_ReadIntrMsgAsync(s32 fd, u32 endpoint, u32 length, void* buffer,
                                USBCallback callback, void* callbackArg) {
    DCInvalidateRange(buffer, length);
    return __IntrBlkMsgInt(fd, endpoint, length, buffer, USB_IOCTLV_INTRMSG,
                           callback, callbackArg, TRUE);
}

IPCResult IUSB_ReadBlkMsgAsync(s32 fd, u32 endpoint, u32 length, void* buffer,
                               USBCallback callback, void* callbackArg) {
    DCInvalidateRange(buffer, length);
    return __IntrBlkMsgInt(fd, endpoint, length, buffer, USB_IOCTLV_BLKMSG,
                           callback, callbackArg, TRUE);
}

IPCResult IUSB_WriteBlkMsgAsync(s32 fd, u32 endpoint, u32 length,
                                const void* buffer, USBCallback callback,
                                void* callbackArg) {
    DCFlushRange(buffer, length);
    return __IntrBlkMsgInt(fd, endpoint, length, (void*)buffer,
                           USB_IOCTLV_BLKMSG, callback, callbackArg, TRUE);
}

static IPCResult __CtrlMsgInt(s32 fd, u8 requestType, u8 request, u16 value,
                              u16 index, u16 length, void* buffer,
                              USBCallback callback, void* callbackArg,
                              u8 async) {
    IPCResult result;
    IPCIOVector* vectors;
    u8* requestTypeWork;
    u8* requestWork;
    u8* unkWork;
    u16* valueWork;
    u16* indexWork;
    u16* lengthWork;
    USBCommandBlock* block;

    if ((buffer == NULL && length != 0) || (u32)buffer % 32 != 0) {
        result = IPC_RESULT_INVALID_INTERNAL;
        USB_ERR("ctrlmsg: bad data buffer\n");
        goto end_async;
    }

    vectors = (IPCIOVector*)IOSAlloc(0xE0);
    requestTypeWork = (u8*)IOSAlloc(32);
    requestWork = (u8*)IOSAlloc(32);
    unkWork = (u8*)IOSAlloc(32);
    valueWork = (u16*)IOSAlloc(32);
    indexWork = (u16*)IOSAlloc(32);
    lengthWork = (u16*)IOSAlloc(32);

    if (requestTypeWork == NULL || requestWork == NULL || unkWork == NULL ||
        valueWork == NULL || indexWork == NULL || lengthWork == NULL ||
        vectors == NULL) {
        USB_ERR("Ctrl Msg: Not enough memory\n");
        result = IPC_RESULT_ALLOC_FAILED;
        goto end;
    }

    *requestTypeWork = requestType;
    *requestWork = request;
    *valueWork = (value & 0xFF) << 8 | value >> 8 & 0xFF;
    *indexWork = (index & 0xFF) << 8 | index >> 8 & 0xFF;
    *lengthWork = (length & 0xFF) << 8 | length >> 8 & 0xFF;
    *unkWork = 0;

    // Input vector 1: bmRequestType
    vectors[0].base = requestTypeWork;
    vectors[0].length = sizeof(u8);

    // Input vector 2: bmRequest
    vectors[1].base = requestWork;
    vectors[1].length = sizeof(u8);

    // Input vector 3: wValue
    vectors[2].base = valueWork;
    vectors[2].length = sizeof(u16);

    // Input vector 4: wIndex
    vectors[3].base = indexWork;
    vectors[3].length = sizeof(u16);

    // Input vector 5: wLength
    vectors[4].base = lengthWork;
    vectors[4].length = sizeof(u16);

    // Input vector 6: Unknown data
    vectors[5].base = unkWork;
    vectors[5].length = sizeof(u8);

    // Output vector 1: Transfer buffer
    vectors[6].base = buffer;
    vectors[6].length = length;

    DCFlushRange(requestTypeWork, 32);
    DCFlushRange(requestWork, 32);
    DCFlushRange(unkWork, 32);
    DCFlushRange(valueWork, 32);
    DCFlushRange(indexWork, 32);
    DCFlushRange(lengthWork, 32);
    DCFlushRange(vectors, 0xE0);

    if (!async) {
        result = IOS_Ioctlv(fd, USB_IOCTLV_CTRLMSG, 6, 1, vectors);
        goto end;
    }

    block = IOSAlloc(sizeof(USBCommandBlock));
    if (block == NULL) {
        USB_ERR("CtrlMsgInt (async): Not enough memory\n");
        result = IPC_RESULT_ALLOC_FAILED;
        goto end;
    }

    block->callback = callback;
    block->callbackArg = callbackArg;
    USB_LOG("ctrlmsgint: cb = 0x%x cbArg = 0x%x\n", block->callback,
            block->callbackArg);

    // Mark memory for deletion
    block->nclean = USB_NCLEAN_CTRLMSG;
    block->clean[0] = requestTypeWork;
    block->clean[1] = requestWork;
    block->clean[2] = valueWork;
    block->clean[3] = indexWork;
    block->clean[4] = lengthWork;
    block->clean[5] = unkWork;
    block->clean[6] = vectors;

    block->msg.buffer = buffer;
    block->msg.length = length;

    result = IOS_IoctlvAsync(fd, USB_IOCTLV_CTRLMSG, 6, 1, vectors,
                             _intBlkCtrlCb, block);
    USB_LOG("Ctrl Msg async returned: %d\n", result);

    if (result >= IPC_RESULT_OK) {
        goto end_async;
    }

    IOSFree(block);

// Non-async (or unsuccessful async) means we must manually free memory
end:
    IOSFree(requestTypeWork);
    IOSFree(requestWork);
    IOSFree(valueWork);
    IOSFree(indexWork);
    IOSFree(lengthWork);
    IOSFree(unkWork);
    IOSFree(vectors);

// Async callback automatically freed the memory marked in block->clean
end_async:
    return result;
}

IPCResult IUSB_WriteCtrlMsgAsync(s32 fd, u8 requestType, u8 request, u16 value,
                                 u16 index, u16 length, void* buffer,
                                 USBCallback callback, void* callbackArg) {
    DCFlushRange(buffer, length);
    return __CtrlMsgInt(fd, requestType, request, value, index, length, buffer,
                        callback, callbackArg, TRUE);
}

// clang-format off
DECOMP_FORCEACTIVE(usb_c,
                   "GetStrCb returned: %d\n",
                   "GetStrCb: buf = 0x%x buflen = %u\n",
                   "Failed to convert buffer from unicode 2 ascii\n",
                   "calling cb 0x%x with arg 0x%x\n",
                   "Failed __CtrlMsg: %d",
                   "Failed to convert unicode 2 ascii\n",
                   "GetStr - _GetStrCb\n",
                   " GetAsciiStrAsync: Not enough memory\n",
                   "__CtrlMsgInt failed %d\n",
                   "GetDescrCb returned: %d\n",
                   "GetDevDescr\n",
                   "GetDevDescr: Not enough memory\n",
                   "GetDevDescr: %d\n",
                   "GetDevDescr - _GetDescrCb\n",
                   "GetDevDescrAsync: Not enough memory\n",
                   "DeviceRemovalNotifyAsync\n",
                   "Invalid parameters for ISO transfer request\n",
                   "IUSB_IsoMsgAsync: Not enough memory\n",
                   "Open(%s) failed\n");
// clang-format on
