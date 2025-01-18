#include <revolution/EXI.h>
#include <revolution/OS.h>

#define OS_SRAM_SIZE (sizeof(OSSram) + sizeof(OSSramEx))

typedef struct OSScb {
    union {
        struct {
            OSSram sram;
            OSSramEx sramEx;
        };
        u8 block[OS_SRAM_SIZE];
    };            // at 0x0
    u32 pos;      // at 0x40
    BOOL enabled; // at 0x44
    BOOL locked;  // at 0x48
    BOOL sync;    // at 0x4C
    UNKWORD WORD_0x50;
} OSScb;

static OSScb Scb ALIGN(32);

static BOOL WriteSram(const void* src, u32 pos, s32 size);

static BOOL ReadSram(OSScb* scb) {
    BOOL error = FALSE;
    u32 imm;

    DCInvalidateRange(scb, OS_SRAM_SIZE);

    if (!EXILock(EXI_CHAN_0, EXI_DEV_INT, NULL)) {
        return FALSE;
    }

    if (!EXISelect(EXI_CHAN_0, EXI_DEV_INT, EXI_FREQ_8MHZ)) {
        EXIUnlock(EXI_CHAN_0);
        return FALSE;
    }

    imm = 0x20000100;
    error |= !EXIImm(EXI_CHAN_0, &imm, sizeof(imm), EXI_WRITE, NULL);
    error |= !EXISync(EXI_CHAN_0);
    error |= !EXIDma(EXI_CHAN_0, scb->block, OS_SRAM_SIZE, EXI_READ, NULL);
    error |= !EXISync(EXI_CHAN_0);
    error |= !EXIDeselect(EXI_CHAN_0);
    EXIUnlock(EXI_CHAN_0);

    return error == FALSE;
}

static void WriteSramCallback(EXIChannel chan, OSContext* ctx) {
#pragma unused(chan)
#pragma unused(ctx)

    Scb.sync = WriteSram(Scb.block + Scb.pos, Scb.pos, OS_SRAM_SIZE - Scb.pos);
    if (Scb.sync) {
        Scb.pos = OS_SRAM_SIZE;
    }
}

static BOOL WriteSram(const void* src, u32 pos, s32 size) {
    u32 imm;
    BOOL error = FALSE;

    if (!EXILock(EXI_CHAN_0, EXI_DEV_INT, WriteSramCallback)) {
        return FALSE;
    }

    if (!EXISelect(EXI_CHAN_0, EXI_DEV_INT, EXI_FREQ_8MHZ)) {
        EXIUnlock(EXI_CHAN_0);
        return FALSE;
    }

    imm = pos * 0x40 + 0x100 | 0xA0000000;
    error |= !EXIImm(EXI_CHAN_0, &imm, sizeof(imm), EXI_WRITE, NULL);
    error |= !EXISync(EXI_CHAN_0);
    error |= !EXIImmEx(EXI_CHAN_0, (void*)src, size, EXI_WRITE);
    error |= !EXIDeselect(EXI_CHAN_0);
    EXIUnlock(EXI_CHAN_0);

    return error == FALSE;
}

void __OSInitSram(void) {
    Scb.enabled = FALSE;
    Scb.locked = FALSE;
    Scb.sync = ReadSram(&Scb);
    Scb.pos = OS_SRAM_SIZE;
    OSSetGbsMode(OSGetGbsMode());
}

static void* LockSram(u32 pos) {
    BOOL enabled;

    enabled = OSDisableInterrupts();

    if (Scb.locked) {
        OSRestoreInterrupts(enabled);
        return NULL;
    }

    Scb.enabled = enabled;
    Scb.locked = TRUE;

    return Scb.block + pos;
}

OSSramEx* __OSLockSramEx(void) {
    return (OSSramEx*)LockSram(sizeof(OSSram));
}

static BOOL UnlockSram(BOOL save, u32 pos) {
    u16* data;
    OSSram* sram;
    OSSramEx* sramEx;

    if (save) {
        if (pos == 0) {
            sram = &Scb.sram;
            if ((u8)(sram->flags & 0x3) > 2) {
                sram->flags &= ~0x3;
            }

            // Checksum base SRAM
            sram->invchecksum = 0;
            sram->checksum = 0;
            for (data = (u16*)&sram->counterBias; data < (u16*)&Scb.sramEx;
                 data++) {
                sram->checksum += *data;
                sram->invchecksum += ~*data;
            }
        }

        if (pos < Scb.pos) {
            Scb.pos = pos;
        }

        sramEx = &Scb.sramEx;
        if (Scb.pos <= sizeof(OSSram) &&
            (((u32)sramEx->gbs & 0x7C00) == 0x5000 ||
             ((u32)sramEx->gbs & 0xC0) == 0xC0)) {
            sramEx->gbs = 0;
        }

        Scb.sync =
            WriteSram(Scb.block + Scb.pos, Scb.pos, OS_SRAM_SIZE - Scb.pos);
        if (Scb.sync) {
            Scb.pos = OS_SRAM_SIZE;
        }
    }

    Scb.locked = FALSE;
    OSRestoreInterrupts(Scb.enabled);
    return Scb.sync;
}

BOOL __OSUnlockSramEx(BOOL save) {
    return UnlockSram(save, sizeof(OSSram));
}

BOOL __OSSyncSram(void) {
    return Scb.sync;
}

BOOL __OSReadROM(void* dst, s32 size, const void* src) {
    u32 imm;
    BOOL error = FALSE;

    DCInvalidateRange(dst, size);

    if (!EXILock(EXI_CHAN_0, EXI_DEV_INT, NULL)) {
        return FALSE;
    }

    if (!EXISelect(EXI_CHAN_0, EXI_DEV_INT, EXI_FREQ_8MHZ)) {
        EXIUnlock(EXI_CHAN_0);
        return FALSE;
    }

    imm = (u32)src << 6;
    error |= !EXIImm(EXI_CHAN_0, &imm, sizeof(imm), EXI_WRITE, NULL);
    error |= !EXISync(EXI_CHAN_0);
    error |= !EXIDma(EXI_CHAN_0, dst, size, EXI_READ, NULL);
    error |= !EXISync(EXI_CHAN_0);
    error |= !EXIDeselect(EXI_CHAN_0);
    EXIUnlock(EXI_CHAN_0);

    return error == FALSE;
}

u16 OSGetWirelessID(s32 pad) {
    OSSramEx* sram;
    u16 id;

    sram = __OSLockSramEx();
    id = sram->wirelessPadId[pad];
    __OSUnlockSramEx(FALSE);

    return id;
}

void OSSetWirelessID(s32 pad, u16 id) {
    OSSramEx* sram;

    sram = __OSLockSramEx();
    if (id != sram->wirelessPadId[pad]) {
        sram->wirelessPadId[pad] = id;
        __OSUnlockSramEx(TRUE);
    } else {
        __OSUnlockSramEx(FALSE);
    }
}

u16 OSGetGbsMode(void) {
    OSSramEx* sram;
    u16 gbs;

    sram = __OSLockSramEx();
    gbs = sram->gbs;
    __OSUnlockSramEx(FALSE);

    return gbs;
}

void OSSetGbsMode(u16 gbs) {
    OSSramEx* sram;

    if (((u32)gbs & 0x7C00) == 0x5000 || ((u32)gbs & 0xC0) == 0xC0) {
        gbs = 0;
    }

    sram = __OSLockSramEx();
    if (gbs == sram->gbs) {
        __OSUnlockSramEx(FALSE);
    } else {
        sram->gbs = gbs;
        __OSUnlockSramEx(TRUE);
    }
}

BOOL __OSGetRTCFlags(u32* out) {
    u32 imm;
    BOOL error = FALSE;

    if (!EXILock(EXI_CHAN_0, EXI_DEV_INT, NULL)) {
        return FALSE;
    }

    if (!EXISelect(EXI_CHAN_0, EXI_DEV_INT, EXI_FREQ_8MHZ)) {
        EXIUnlock(EXI_CHAN_0);
        return FALSE;
    }

    imm = 0x21000800;
    error |= !EXIImm(EXI_CHAN_0, &imm, sizeof(imm), EXI_WRITE, NULL);
    error |= !EXISync(EXI_CHAN_0);
    error |= !EXIImm(EXI_CHAN_0, &imm, sizeof(imm), EXI_READ, NULL);
    error |= !EXISync(EXI_CHAN_0);
    error |= !EXIDeselect(EXI_CHAN_0);
    EXIUnlock(EXI_CHAN_0);

    *out = imm;
    return error == FALSE;
}

BOOL __OSClearRTCFlags(void) {
    u32 imm;
    u32 flags = 0;
    BOOL error = FALSE;

    if (!EXILock(EXI_CHAN_0, EXI_DEV_INT, NULL)) {
        return FALSE;
    }

    if (!EXISelect(EXI_CHAN_0, EXI_DEV_INT, EXI_FREQ_8MHZ)) {
        EXIUnlock(EXI_CHAN_0);
        return FALSE;
    }

    imm = 0xA1000800;
    error |= !EXIImm(EXI_CHAN_0, &imm, sizeof(imm), EXI_WRITE, NULL);
    error |= !EXISync(EXI_CHAN_0);
    error |= !EXIImm(EXI_CHAN_0, &flags, sizeof(flags), EXI_WRITE, NULL);
    error |= !EXISync(EXI_CHAN_0);
    error |= !EXIDeselect(EXI_CHAN_0);
    EXIUnlock(EXI_CHAN_0);

    return error == FALSE;
}
