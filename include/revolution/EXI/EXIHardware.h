#ifndef RVL_SDK_EXI_HARDWARE_H
#define RVL_SDK_EXI_HARDWARE_H
#include <revolution/EXI/EXICommon.h>
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct EXIChannelParam {
    u32 cpr;    // at 0x0
    void* mar;  // at 0x4
    u32 length; // at 0x8
    u32 cr;     // at 0xC
    u32 data;   // at 0x10
} EXIChannelParam;

volatile EXIChannelParam EXI_CHAN_PARAMS[EXI_MAX_CHAN] : 0xCD006800;

// CPR - Channel Parameter Register
#define EXI_CPR_EXIINTMASK (1 << 0)
#define EXI_CPR_EXIINT (1 << 1)
#define EXI_CPR_TCINTMASK (1 << 2)
#define EXI_CPR_TCINT (1 << 3)
#define EXI_CPR_CLK (1 << 4 | 1 << 5 | 1 << 6)
#define EXI_CPR_CS0B (1 << 7)
#define EXI_CPR_CS1B (1 << 8)
#define EXI_CPR_CS2B (1 << 9)
#define EXI_CPR_EXTINTMASK (1 << 10)
#define EXI_CPR_EXTINT (1 << 11)
#define EXI_CPR_EXT (1 << 12)
#define EXI_CPR_ROMDIS (1 << 13)

// CR - Control Register
#define EXI_CR_TSTART (1 << 0)
#define EXI_CR_DMA (1 << 1)
#define EXI_CR_RW (1 << 2 | 1 << 3)
#define EXI_CR_TLEN (1 << 4 | 1 << 5)

#ifdef __cplusplus
}
#endif
#endif
