#include <revolution/OS.h>
#include <revolution/SI.h>

typedef enum {
    SI_ERROR_NOREP = (1 << 3),
    SI_ERROR_BUSY = (1 << 7),
    SI_WIRELESS_LITE = (1 << 18),
    SI_WIRELESS_CONT = (1 << 19),
} SIStatus;

typedef struct SIMain {
    s32 chan;            // at 0x0
    u32 poll;            // at 0x4
    u32 inSize;          // at 0x8
    void* inAddr;        // at 0xC
    SICallback callback; // at 0x10
} SIMain;

typedef struct SIPacket {
    s32 chan;            // at 0x0
    void* outAddr;       // at 0x4
    u32 outSize;         // at 0x8
    void* inAddr;        // at 0xC
    u32 inSize;          // at 0x10
    SICallback callback; // at 0x14
    s64 fire;            // at 0x18
} SIPacket;

const char* __SIVersion =
    "<< RVL_SDK - SI \trelease build: Nov 30 2006 03:31:44 (0x4199_60831) >>";

static SIMain Si = {SI_CHAN_NONE};
static u32 Type[SI_MAX_CHAN] = {SI_ERROR_NOREP, SI_ERROR_NOREP, SI_ERROR_NOREP,
                                SI_ERROR_NOREP};

static SIPacket Packet[SI_MAX_CHAN];
static s64 XferTime[SI_MAX_CHAN];
static s64 TypeTime[SI_MAX_CHAN];
static SICallback TypeCallback[SI_MAX_TYPE][SI_MAX_CHAN];
static BOOL InputBufferValid[SI_MAX_CHAN];
static u32 InputBuffer[SI_MAX_CHAN][2];
static OSInterruptHandler RDSTHandler[SI_MAX_CHAN];
static u32 InputBufferVcount[SI_MAX_CHAN];
static OSAlarm Alarm[SI_MAX_CHAN];

static void SIClearTCInterrupt(void) {
    u32 csr = SI_HW_REGS[SI_SICOMSCR];

    csr |= SI_SICOMCSR_TCINT;
    csr &= ~SI_SICOMCSR_TSTART;

    SI_HW_REGS[SI_SICOMSCR] = csr;
}

static u32 CompleteTransfer(void) {
    u32 i;
    u32 sr;
    u8* dst;
    u32 size;
    u32 imm;

    sr = SI_HW_REGS[SI_SISR];
    SIClearTCInterrupt();

    if (Si.chan != SI_CHAN_NONE) {
        XferTime[Si.chan] = __OSGetSystemTime();

        dst = (u8*)Si.inAddr;

        size = Si.inSize / sizeof(u32);
        for (i = 0; i < size; dst += sizeof(u32), i++) {
            *(u32*)dst = SI_HW_REGS[SI_RAM_BASE + i];
        }

        size = Si.inSize % sizeof(u32);
        if (size > 0) {
            imm = SI_HW_REGS[SI_RAM_BASE + i];

            for (i = 0; i < size; dst++, i++) {
                *dst = imm >> (3 - i) * 8;
            }
        }

        if (SI_HW_REGS[SI_SICOMSCR] & SI_SICOMCSR_COMERR) {
            // Flags relative to channel ID
            sr >>= ((SI_MAX_CHAN - 1) - Si.chan) * 8;
            sr &= (SI_UNRUN | SI_OVRUN | SI_COLL | SI_NOREP);

            if ((sr & SI_NOREP) && (Type[Si.chan] & SI_ERROR_BUSY) == 0) {
                Type[Si.chan] = SI_ERROR_NOREP;
            }

            if (sr == 0) {
                sr = SI_COLL;
            }
        } else {
            TypeTime[Si.chan] = __OSGetSystemTime();
            sr = 0;
        }

        Si.chan = SI_CHAN_NONE;
    }

    return sr;
}

// TODO
static void SIInterruptHandler(s16 intr, OSContext* ctx) {
    ;
}

void SIInit(void) {
    static BOOL Initialized = FALSE;

    if (Initialized) {
        return;
    }

    OSRegisterVersion(__SIVersion);

    Packet[SI_CHAN_0].chan = Packet[SI_CHAN_1].chan = Packet[SI_CHAN_2].chan =
        Packet[SI_CHAN_3].chan = SI_CHAN_NONE;

    Si.poll = 0;
    SISetSamplingRate(0);

    while (SI_HW_REGS[SI_SICOMSCR] & SI_SICOMCSR_TSTART) {
        ;
    }

    SI_HW_REGS[SI_SICOMSCR] = SI_SICOMCSR_TCINT;

    __OSSetInterruptHandler(OS_INTR_PI_SI, SIInterruptHandler);
    __OSUnmaskInterrupts(OS_INTR_MASK(OS_INTR_PI_SI));

    SIGetType(SI_CHAN_0);
    SIGetType(SI_CHAN_1);
    SIGetType(SI_CHAN_2);
    SIGetType(SI_CHAN_3);

    Initialized = TRUE;
}

static BOOL __SITransfer(s32 chan, void* outAddr, u32 outSize, void* inAddr,
                         u32 inSize, SICallback callback) {
    BOOL enabled;
    u32 sr;
    u32 alignSize;
    u32 i;

    union {
        struct {
            u32 TCINT : 1;
            u32 TCINTMSK : 1;
            u32 COMERR : 1;
            u32 RDSTINT : 1;
            u32 RDSTINTMSK : 1;
            u32 reserved2 : 4;
            u32 OUTLNGTH : 7;
            u32 reserved1 : 1;
            u32 INLNGTH : 7;
            u32 reserved0 : 5;
            u32 CHANNEL : 2;
            u32 TSTART : 1;
        };

        u32 reg;
    } comscr;

    enabled = OSDisableInterrupts();

    if (Si.chan != SI_CHAN_NONE) {
        OSRestoreInterrupts(enabled);
        return FALSE;
    }

    sr = SI_HW_REGS[SI_SISR];
    sr &= (SI_SISR_UNRUN0 | SI_SISR_OVRUN0 | SI_SISR_COLL0 | SI_SISR_NOREP0) >>
          (chan * 8);
    SI_HW_REGS[SI_SISR] = sr;

    Si.chan = chan;
    Si.callback = callback;
    Si.inSize = inSize;
    Si.inAddr = inAddr;

    alignSize = (outSize + 3) / 4;
    for (i = 0; i < alignSize; i++) {
        SI_HW_REGS[SI_RAM_BASE + i] = ((u32*)outAddr)[i];
    }

    comscr.reg = SI_HW_REGS[SI_SICOMSCR];

    comscr.TCINT = TRUE;
    comscr.TCINTMSK = callback != NULL;
    // Minimum transfer is 1 byte. 0x00 will transfer 128 bytes
    comscr.OUTLNGTH = outSize == 128 ? 0 : outSize;
    comscr.INLNGTH = inSize == 128 ? 0 : inSize;
    comscr.CHANNEL = chan;
    comscr.TSTART = TRUE;

    SI_HW_REGS[SI_SICOMSCR] = comscr.reg;

    OSRestoreInterrupts(enabled);
    return TRUE;
}

u32 SISetXY(u32 lines, u32 times) {
    BOOL enabled;
    u32 poll;

    poll = lines << 16;
    poll |= times << 8;

    enabled = OSDisableInterrupts();

    Si.poll &= ~(SI_SIPOLL_X | SI_SIPOLL_Y);
    Si.poll |= poll;

    poll = Si.poll;
    SI_HW_REGS[SI_SIPOLL] = poll;

    OSRestoreInterrupts(enabled);
    return poll;
}

static void AlarmHandler(OSAlarm* alarm, OSContext* ctx) {
    s32 chan;
    SIPacket* packet;

    chan = alarm - Alarm;
    packet = &Packet[chan];

    if (packet->chan != SI_CHAN_NONE) {
        if (__SITransfer(packet->chan, packet->outAddr, packet->outSize,
                         packet->inAddr, packet->inSize, packet->callback)) {
            packet->chan = SI_CHAN_NONE;
        }
    }
}

BOOL SITransfer(s32 chan, void* outAddr, u32 outSize, void* inAddr, u32 inSize,
                SICallback callback, s64 wait) {
    SIPacket* packet;
    BOOL enabled;
    s64 start;
    s64 fire;

    packet = &Packet[chan];
    enabled = OSDisableInterrupts();

    if (packet->chan != SI_CHAN_NONE || Si.chan == packet->chan) {
        OSRestoreInterrupts(enabled);
        return FALSE;
    }

    start = __OSGetSystemTime();
    fire = wait == 0 ? start : wait + XferTime[chan];

    if (start < fire) {
        OSSetAlarm(&Alarm[chan], fire - start, AlarmHandler);
    } else if (__SITransfer(chan, outAddr, outSize, inAddr, inSize, callback)) {
        OSRestoreInterrupts(enabled);
        return TRUE;
    }

    packet->chan = chan;
    packet->outAddr = outAddr;
    packet->outSize = outSize;
    packet->inAddr = inAddr;
    packet->inSize = inSize;
    packet->callback = callback;
    packet->fire = fire;

    OSRestoreInterrupts(enabled);
    return TRUE;
}

// TODO
static void GetTypeCallback(s32 chan, u32 status) {
    // static u32 cmdFixDevice[SI_MAX_CHAN];

    // Type[chan] &= ~SI_ERROR_BUSY;
    // Type[chan] |= status;
    // TypeTime[chan] = __OSGetSystemTime();
}

// TODO
u32 SIGetType(s32 chan) {
    ;
}
