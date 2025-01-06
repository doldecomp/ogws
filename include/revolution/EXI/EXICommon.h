#ifndef RVL_SDK_EXI_COMMON_H
#define RVL_SDK_EXI_COMMON_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations
typedef struct OSContext OSContext;

typedef enum {
    EXI_STATE_DMA_ACCESS = (1 << 0),
    EXI_STATE_IMM_ACCESS = (1 << 1),
    EXI_STATE_SELECTED = (1 << 2),
    EXI_STATE_ATTACHED = (1 << 3),
    EXI_STATE_LOCKED = (1 << 4),

    EXI_STATE_BUSY = EXI_STATE_DMA_ACCESS | EXI_STATE_IMM_ACCESS
} EXIState;

typedef enum {
    EXI_FREQ_1MHZ,
    EXI_FREQ_2MHZ,
    EXI_FREQ_4MHZ,
    EXI_FREQ_8MHZ,
    EXI_FREQ_16MHZ,
    EXI_FREQ_32HZ,
    EXI_MAX_FREQ
} EXIFreq;

typedef enum { EXI_CHAN_0, EXI_CHAN_1, EXI_CHAN_2, EXI_MAX_CHAN } EXIChannel;

typedef enum { EXI_DEV_EXT, EXI_DEV_INT, EXI_DEV_NET, EXI_MAX_DEV } EXIDev;

typedef enum { EXI_READ, EXI_WRITE, EXI_TYPE_2, EXI_MAX_TYPE } EXIType;

typedef enum {
    EXI_ID_MEMCARD_59 = 0x00000004,
    EXI_ID_MEMCARD_123 = 0x00000008,
    EXI_ID_MEMCARD_251 = 0x00000010,
    EXI_ID_MEMCARD_507 = 0x00000020,
    EXI_ID_MEMCARD_1019 = 0x00000040,
    EXI_ID_MEMCARD_2043 = 0x00000080,
    EXI_ID_USB_ADAPTER = 0x01010000,
    EXI_ID_IS_DOL_VIEWER = 0x05070000,
    EXI_ID_BROADBAND_ADAPTER = 0x04020200,
    EXI_ID_INVALID = 0xFFFFFFFF
} EXIDeviceID;

typedef void (*EXICallback)(EXIChannel chan, OSContext* ctx);

extern const u32 __EXIFreq;

static u32 __EXISwap32(u32 val) {
    return val >> 24 & 0x000000FF | val >> 8 & 0x0000FF00 |
           val << 8 & 0x00FF0000 | val << 24 & 0xFF000000;
}

BOOL EXIWriteReg(EXIChannel chan, u32 dev, u32 cmd, const void* buf, s32 len);

#ifdef __cplusplus
}
#endif
#endif
