#include <revolution/EXI.h>

static BOOL Enabled = FALSE;
static BOOL BarnacleEnabled = FALSE;

static u32 Dev = EXI_DEV_EXT;
static EXIChannel Chan = EXI_CHAN_0;

static BOOL ProbeBarnacle(EXIChannel chan, u32 dev, u32* id) {
    BOOL error;
    u32 cmd;

    if (chan != EXI_CHAN_2 && dev == EXI_DEV_EXT) {
        if (!EXIAttach(chan, NULL)) {
            return FALSE;
        }
    }

    error = !EXILock(chan, dev, NULL);
    if (error) {
        goto _detach;
    }

    error = !EXISelect(chan, dev, EXI_FREQ_1MHZ);
    if (error) {
        goto _unlock;
    }

    cmd = 0x20011300;
    error = !EXIImm(chan, &cmd, sizeof(u32), EXI_WRITE, NULL);
    error |= !EXISync(chan);

    error |= !EXIImm(chan, id, sizeof(u32), EXI_READ, NULL);
    error |= !EXISync(chan);
    error |= !EXIDeselect(chan);

_unlock:
    EXIUnlock(chan);

_detach:
    if (chan != EXI_CHAN_2 && dev == EXI_DEV_EXT) {
        EXIDetach(chan);
    }

    if (error) {
        return FALSE;
    }

    return *id != EXI_ID_INVALID;
}

void __OSEnableBarnacle(EXIChannel chan, u32 dev) {
    u32 id;

    if (!EXIGetID(chan, dev, &id)) {
        return;
    }

    switch (id) {
    case EXI_ID_MEMCARD_59:
    case EXI_ID_MEMCARD_123:
    case EXI_ID_MEMCARD_251:
    case EXI_ID_MEMCARD_507:
    case EXI_ID_USB_ADAPTER:
    case 0x01020000:
    case 0x02020000:
    case 0x03010000:
    case 0x04020100:
    case EXI_ID_BROADBAND_ADAPTER:
    case 0x04020300:
    case 0x04040404:
    case 0x04060000:
    case 0x04120000:
    case 0x04130000:
    case 0x04220000:
    case 0x80000004:
    case 0x80000008:
    case 0x80000010:
    case 0x80000020:
    case EXI_ID_INVALID:
        break;
    default:
        if (ProbeBarnacle(chan, dev, &id)) {
            Chan = chan;
            Dev = dev;
            BarnacleEnabled = 0xA5FF005A;
            Enabled = 0xA5FF005A;
        }
        break;
    }
}
