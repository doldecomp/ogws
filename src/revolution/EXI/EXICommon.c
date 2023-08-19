#include <revolution/EXI/EXIBios.h>
#include <revolution/EXI/EXICommon.h>

const u32 __EXIFreq = 4;

BOOL EXIWriteReg(EXIChannel chan, u32 dev, UNKWORD r5, const void* buf,
                 s32 len) {
    BOOL error = FALSE;
    u32 write_val;

    switch (len) {
    case 1:
        write_val = *(u8*)buf << 24;
        break;
    case 2:
        write_val = *(u16*)buf << 24 | (*(u16*)buf & 0xFF00) << 8;
        break;
    default:
        write_val = __EXISwap32(*(u32*)buf);
        break;
    }

    error |= !EXILock(chan, dev, NULL);
    if (error) {
        return FALSE;
    }

    error |= !EXISelect(chan, dev, EXI_FREQ_16MHZ);
    if (error) {
        EXIUnlock(chan);
        return FALSE;
    }

    error |= !EXIImm(chan, &r5, sizeof(r5), EXI_WRITE, NULL);
    error |= !EXISync(chan);
    error |= !EXIImm(chan, &write_val, sizeof(write_val), EXI_WRITE, NULL);
    error |= !EXISync(chan);
    error |= !EXIDeselect(chan);
    error |= !EXIUnlock(chan);

    return error == FALSE;
}
