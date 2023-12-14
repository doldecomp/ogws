#include <revolution/DSP.h>
#include <revolution/OS.h>
#include <string.h>

#define DSP_CODE_WORK_MEM ((void*)0x81000000)
#define DSP_CODE_WORK_MEM_BACKUP ((u8*)OSGetArenaHi() - sizeof(DSPInitCode))

static u8 DSPInitCode[128] = {
    0x02, 0x9F, 0x00, 0x10, 0x02, 0x9F, 0x00, 0x33, 0x02, 0x9F, 0x00, 0x34,
    0x02, 0x9F, 0x00, 0x35, 0x02, 0x9F, 0x00, 0x36, 0x02, 0x9F, 0x00, 0x37,
    0x02, 0x9F, 0x00, 0x38, 0x02, 0x9F, 0x00, 0x39, 0x12, 0x06, 0x12, 0x03,
    0x12, 0x04, 0x12, 0x05, 0x00, 0x80, 0x80, 0x00, 0x00, 0x88, 0xFF, 0xFF,
    0x00, 0x84, 0x10, 0x00, 0x00, 0x64, 0x00, 0x1D, 0x02, 0x18, 0x00, 0x00,
    0x81, 0x00, 0x1C, 0x1E, 0x00, 0x44, 0x1B, 0x1E, 0x00, 0x84, 0x08, 0x00,
    0x00, 0x64, 0x00, 0x27, 0x19, 0x1E, 0x00, 0x00, 0x00, 0xDE, 0xFF, 0xFC,
    0x02, 0xA0, 0x80, 0x00, 0x02, 0x9C, 0x00, 0x28, 0x16, 0xFC, 0x00, 0x54,
    0x16, 0xFD, 0x43, 0x48, 0x00, 0x21, 0x02, 0xFF, 0x02, 0xFF, 0x02, 0xFF,
    0x02, 0xFF, 0x02, 0xFF, 0x02, 0xFF, 0x02, 0xFF, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static void waitMicroSec(u32 usec) {
    u32 start = OSGetTick();
    do {
        ;
    } while (OS_TICKS_TO_USEC(OS_TICKS_DELTA(OSGetTick(), start)) < usec);
}

static void __AIClockInit(BOOL arg0) {
    u32 tmp;

    tmp = OS_UNK_CD800180;
    tmp &= ~0x100;
    tmp |= (arg0 << 8);
    tmp &= ~0x80;
    OS_UNK_CD800180 = tmp;

    OS_UNK_CD8001D0 &= ~0xC0000000;
    waitMicroSec(100);

    if (!arg0) {
        tmp = OS_UNK_CD8001CC;
        tmp &= ~0x3FFC0;
        tmp |= 0xFC0;
        tmp &= ~0x3F;
        tmp &= ~0x7FC0000;
        tmp |= 0x4640000;
        OS_UNK_CD8001CC = tmp;
    } else {
        tmp = OS_UNK_CD8001CC;
        tmp &= ~0x3FFC0;
        tmp |= 0xFFC0;
        tmp &= ~0x3F;
        tmp |= 0xE;
        tmp &= ~0x7FC0000;
        tmp |= 0x4B00000;
        OS_UNK_CD8001CC = tmp;
    }
    waitMicroSec(100);

    OS_UNK_CD8001D0 &= ~0x10000000;
    waitMicroSec(1000);

    OS_UNK_CD8001D0 = (OS_UNK_CD8001D0 & ~0x40000000) | 0x40000000;
    waitMicroSec(1000);

    OS_UNK_CD8001D0 = (OS_UNK_CD8001D0 & ~0x80000000) | 0x80000000;
    waitMicroSec(1000);
}

void __OSInitAudioSystem(void) {
    u16 cpuMboxHi;
    u32 start;
    u16 ctrl;

    if (!__OSInIPL) {
        __AIClockInit(TRUE);
    }

    // Backup existing work memory contents
    memcpy(DSP_CODE_WORK_MEM_BACKUP, DSP_CODE_WORK_MEM, sizeof(DSPInitCode));
    // Copy in DSP code
    memcpy(DSP_CODE_WORK_MEM, DSPInitCode, sizeof(DSPInitCode));
    DCFlushRange(DSP_CODE_WORK_MEM, sizeof(DSPInitCode));

    DSP_HW_REGS[DSP_AR_SIZE] = 0x43;
    DSP_HW_REGS[DSP_CSR] = DSP_CSR_HALT | DSP_CSR_AIDINT | DSP_CSR_ARINT |
                           DSP_CSR_DSPINT | DSP_CSR_RES;

    // Reset DSP
    DSP_HW_REGS[DSP_CSR] |= 0x1;
    while (DSP_HW_REGS[DSP_CSR] & 0x1) {
        ;
    }

    DSP_HW_REGS[DSP_DSPMBOX_H] = 0;
    // Wait for mail delivery
    while (((DSP_HW_REGS[DSP_CPUMBOX_H] << 16) | DSP_HW_REGS[DSP_CPUMBOX_L]) &
           (DSP_CPUMBOX_H_STATUS << 16)) {
        ;
    }

    *(u32*)&DSP_HW_REGS[DSP_AR_DMA_MMADDR_H] = 0x01000000;
    *(u32*)&DSP_HW_REGS[DSP_AR_DMA_ARADDR_H] = 0x00000000;
    *(u32*)&DSP_HW_REGS[DSP_AR_DMA_CNT_H] = 32;

    // Wait for ARAM interrupt
    for (ctrl = DSP_HW_REGS[DSP_CSR]; !(ctrl & DSP_CSR_ARINT);
         ctrl = DSP_HW_REGS[DSP_CSR]) {
        ;
    }
    DSP_HW_REGS[DSP_CSR] = ctrl;

    start = OSGetTick();
    do {
        ;
    } while (OS_TICKS_DELTA(OSGetTick(), start) < 2194);

    *(u32*)&DSP_HW_REGS[DSP_AR_DMA_MMADDR_H] = 0x01000000;
    *(u32*)&DSP_HW_REGS[DSP_AR_DMA_ARADDR_H] = 0x00000000;
    *(u32*)&DSP_HW_REGS[DSP_AR_DMA_CNT_H] = 32;

    // Wait for ARAM interrupt
    for (ctrl = DSP_HW_REGS[DSP_CSR]; !(ctrl & DSP_CSR_ARINT);
         ctrl = DSP_HW_REGS[DSP_CSR]) {
        ;
    }
    DSP_HW_REGS[DSP_CSR] = ctrl;

    DSP_HW_REGS[DSP_CSR] &= ~DSP_CSR_RES;
    while (DSP_HW_REGS[DSP_CSR] & 0x400) {
        ;
    }

    DSP_HW_REGS[DSP_CSR] &= ~DSP_CSR_HALT;
    for (cpuMboxHi = DSP_HW_REGS[DSP_CPUMBOX_H];
         !(cpuMboxHi & DSP_CPUMBOX_H_STATUS);
         cpuMboxHi = DSP_HW_REGS[DSP_CPUMBOX_H]) {
        ;
    }

    // ?????
    DSP_HW_REGS[DSP_CPUMBOX_L];

    DSP_HW_REGS[DSP_CSR] |= DSP_CSR_HALT;
    DSP_HW_REGS[DSP_CSR] = DSP_CSR_HALT | DSP_CSR_AIDINT | DSP_CSR_ARINT |
                           DSP_CSR_DSPINT | DSP_CSR_RES;

    // Reset DSP
    DSP_HW_REGS[DSP_CSR] |= 0x1;
    while (DSP_HW_REGS[DSP_CSR] & 0x1) {
        ;
    }

    // Restore backup
    memcpy(DSP_CODE_WORK_MEM, DSP_CODE_WORK_MEM_BACKUP, sizeof(DSPInitCode));
}

void __OSStopAudioSystem(void) {
    u32 start;
    u16 ctrl;

    DSP_HW_REGS[DSP_CSR] = DSP_CSR_HALT | DSP_CSR_RES;
    // Clear sample control
    DSP_HW_REGS[DSP_AI_DMA_CSR] &= ~DSP_AI_DMA_CSR_PLAY;

    for (ctrl = DSP_HW_REGS[DSP_CSR]; ctrl & 0x400;
         ctrl = DSP_HW_REGS[DSP_CSR]) {
        ;
    }

    // Wait for DMA interrupt to end
    for (ctrl = DSP_HW_REGS[DSP_CSR]; ctrl & DSP_CSR_DMAINT;
         ctrl = DSP_HW_REGS[DSP_CSR]) {
        ;
    }

    DSP_HW_REGS[DSP_CSR] = DSP_CSR_HALT | DSP_CSR_AIDINT | DSP_CSR_ARINT |
                           DSP_CSR_DSPINT | DSP_CSR_RES;

    DSP_HW_REGS[DSP_DSPMBOX_H] = 0;
    // Wait for mail delivery
    while (((DSP_HW_REGS[DSP_CPUMBOX_H] << 16) | DSP_HW_REGS[DSP_CPUMBOX_L]) &
           (DSP_CPUMBOX_H_STATUS << 16)) {
        ;
    }

    start = OSGetTick();
    do {
        ;
    } while (OS_TICKS_DELTA(OSGetTick(), start) < 44);

    // Reset DSP
    DSP_HW_REGS[DSP_CSR] |= 0x1;
    for (ctrl = DSP_HW_REGS[DSP_CSR]; ctrl & 0x1; ctrl = DSP_HW_REGS[DSP_CSR]) {
        ;
    }
}
