#include <revolution/NdevExi2AD.h>
#include <revolution/OS.h>

static u32 __DBRecvDataSize;
static u32 __DBRecvMail;
static u8 __DBEXIInputFlag;
static OSInterruptHandler __DBDbgCallback;
static OSInterruptHandler __DBMtrCallback;

static u8 __DBReadUSB_CSR(void);
static void __DBWaitForSendMail(void);

void __DBMtrHandler(u32 type, OSContext* ctx) {
    __DBEXIInputFlag = TRUE;

    if (__DBMtrCallback != NULL)
        __DBMtrCallback(0, ctx);
}

void __DBIntrHandler(u32 type, OSContext* ctx) {
    PI_HW_REGS[PI_INTSR] = PI_INTSR_DEBUG;
    if (__DBDbgCallback != NULL)
        __DBDbgCallback(type, ctx);
}

static void __DBCheckMailBox(void) {
    const u8 csr = __DBReadUSB_CSR();
    if (!(csr & 0x8)) {
        u32 mail;
        __DBReadMailbox(&mail);
        if (ODEMUIsValidMail(mail)) {
            __DBRecvMail = mail;
            __DBRecvDataSize = ODEMUGetSize(mail);
            __DBEXIInputFlag = TRUE;
        }
    }
}

static u8 __DBReadUSB_CSR(void) {
    u8 val;
    __DBEXIReadReg(0x34000000, &val, sizeof(val));
    return val;
}

void DBInitComm(u8** flagOut, OSInterruptHandler handler) {
    const BOOL enabled = OSDisableInterrupts();

    *flagOut = &__DBEXIInputFlag;
    __DBMtrCallback = handler;
    __DBEXIInit();

    OSRestoreInterrupts(enabled);
}

#ifdef __DECOMP_NON_MATCHING
void DBInitInterrupts(void) {
    __OSMaskInterrupts(OS_INTR_MASK(OS_INTR_EXI_2_EXI) |
                       OS_INTR_MASK(OS_INTR_EXI_2_TC));
    __OSMaskInterrupts(OS_INTR_MASK(OS_INTR_PI_DEBUG));
    __DBDbgCallback = __DBMtrHandler;
    __OSSetInterruptHandler(OS_INTR_PI_DEBUG, __DBIntrHandler);
    __OSUnmaskInterrupts(OS_INTR_MASK(OS_INTR_PI_DEBUG));
}
#else
#error This file has not yet been decompiled accurately. Use "cnt.s" instead.
#endif

u32 DBQueryData(void) {
    __DBEXIInputFlag = FALSE;

    if (__DBRecvDataSize == 0) {
        const BOOL enabled = OSDisableInterrupts();
        __DBCheckMailBox();
        OSRestoreInterrupts(enabled);
    }

    return __DBRecvDataSize;
}

BOOL DBRead(void* dst, u32 size) {
    const BOOL enabled = OSDisableInterrupts();

    __DBRead(ODEMUGetPc2NngcOffset(__DBRecvMail) + 0x1000, dst,
             ROUND_UP(size, 4));
    __DBRecvDataSize = 0;
    __DBEXIInputFlag = FALSE;

    OSRestoreInterrupts(enabled);

    return FALSE;
}

BOOL DBWrite(const void* src, u32 size) {
    static u8 l_byOffsetCounter = 128;
    const BOOL enabled = OSDisableInterrupts();

    u32 ofs, mail;

    __DBWaitForSendMail();

    ofs = 0;
    if (!(++l_byOffsetCounter & 0x1)) {
        ofs = 0;
    } else {
        ofs = 0x800;
    }

    while (__DBWrite(ofs, src, ROUND_UP(size, 4)) == 0) {
    }

    __DBWaitForSendMail();

    mail = ODEMUGenMailData(l_byOffsetCounter, size);
    while (__DBWriteMailbox(mail) == 0) {
    }

    __DBWaitForSendMail();

    OSRestoreInterrupts(enabled);

    return FALSE;
}

static void __DBWaitForSendMail(void) {
    while (__DBReadUSB_CSR() & 0x4) {
    }
}

void DBOpen(void) {}

void DBClose(void) {}
