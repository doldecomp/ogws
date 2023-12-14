#include <revolution/BASE.h>
#include <revolution/DB.h>
#include <revolution/OS.h>

asm void DCEnable(void) {
    // clang-format off
    nofralloc
    
    sync
    mfhid0 r3
    ori r3, r3, 0x4000
    mthid0 r3

    blr
    // clang-format on
}

asm void DCInvalidateRange(register const void* buf, register u32 len) {
    // clang-format off
    nofralloc
    
    cmplwi len, 0
    blelr 

    clrlwi r5, buf, 27
    add len, len, r5
    addi len, len, 31
    srwi len, len, 5
    mtctr len

do_invalidate:
    dcbi 0, buf
    addi buf, buf, 32
    bdnz do_invalidate

    blr
    // clang-format on
}

asm void DCFlushRange(register const void* buf, register u32 len) {
    // clang-format off
    nofralloc
    
    cmplwi len, 0
    blelr 

    clrlwi r5, buf, 27
    add len, len, r5
    addi len, len, 31
    srwi len, len, 5
    mtctr len

do_flush:
    dcbf 0, buf
    addi buf, buf, 32
    bdnz do_flush
    sc

    blr
    // clang-format on
}

asm void DCStoreRange(register const void* buf, register u32 len) {
    // clang-format off
    nofralloc
    
    cmplwi len, 0
    blelr 

    clrlwi r5, buf, 27
    add len, len, r5
    addi len, len, 31
    srwi len, len, 5
    mtctr len

do_store:
    dcbst 0, buf
    addi buf, buf, 32
    bdnz do_store
    sc

    blr
    // clang-format on
}

asm void DCFlushRangeNoSync(register const void* buf, register u32 len) {
    // clang-format off
    nofralloc
    
    cmplwi len, 0
    blelr 

    clrlwi r5, buf, 27
    add len, len, r5
    addi len, len, 31
    srwi len, len, 5
    mtctr len

do_flush:
    dcbf 0, buf
    addi buf, buf, 32
    bdnz do_flush

    blr
    // clang-format on
}

asm void DCStoreRangeNoSync(register const void* buf, register u32 len) {
    // clang-format off
    nofralloc
    
    cmplwi len, 0
    blelr 

    clrlwi r5, buf, 27
    add len, len, r5
    addi len, len, 31
    srwi len, len, 5
    mtctr len

do_store:
    dcbst 0, buf
    addi buf, buf, 32
    bdnz do_store

    blr
    // clang-format on
}

asm void DCZeroRange(register const void* buf, register u32 len) {
    // clang-format off
    nofralloc
    
    cmplwi len, 0
    blelr 

    clrlwi r5, buf, 27
    add len, len, r5
    addi len, len, 31
    srwi len, len, 5
    mtctr len

do_zero:
    dcbz 0, buf
    addi buf, buf, 32
    bdnz do_zero

    blr
    // clang-format on
}

asm void ICInvalidateRange(register const void* buf, register u32 len) {
    // clang-format off
    nofralloc
    
    cmplwi len, 0
    blelr 

    clrlwi r5, buf, 27
    add len, len, r5
    addi len, len, 31
    srwi len, len, 5
    mtctr len

do_invalidate:
    icbi 0, buf
    addi buf, buf, 32
    bdnz do_invalidate
    
    sync
    isync

    blr
    // clang-format on
}

asm void ICFlashInvalidate(void) {
    // clang-format off
    nofralloc
    
    mfhid0 r3
    ori r3, r3, 0x800
    mthid0 r3

    blr
    // clang-format on
}

asm void ICEnable(void) {
    // clang-format off
    nofralloc

    isync
    mfhid0 r3
    ori r3, r3, 0x8000
    mthid0 r3

    blr
    // clang-format on
}

static asm void __LCEnable(void) {
    // clang-format off
    nofralloc

    mfmsr r5
    ori r5, r5, 0x1000
    mtmsr r5

    lis r3, 0x80000000@h
    li r4, 1024
    mtctr r4
do_store:
    dcbt 0, r3
    dcbst 0, r3
    addi r3, r3, 32
    bdnz do_store

    mfspr r4, 0x398
    oris r4, r4, 0x100F
    mtspr 0x398, r4
    
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    
    lis r3, 0xE0000002@h
    ori r3, r3, 0xE0000002@l
    mtdbatl 3, r3
    ori r3, r3, 0x1FE
    mtdbatu 3, r3
    isync

    lis r3, 0xE0000000@h
    li r6, 512
    mtctr r6
    li r6, 0
do_load:
    dcbz_l r6, r3
    addi r3, r3, 32
    bdnz do_load
    
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    
    blr
    // clang-format on
}

void LCEnable(void) {
    BOOL enabled = OSDisableInterrupts();
    __LCEnable();
    OSRestoreInterrupts(enabled);
}

asm void LCDisable(void) {
    // clang-format off
    nofralloc
    
    lis r3, 0xE0000000@ha
    li r4, 512
    mtctr r4
do_invalidate:
    dcbi 0, r3
    addi r3, r3, 32
    bdnz do_invalidate
    
    mfspr r4, 0x398
    rlwinm r4, r4, 0, 4, 2
    mtspr 0x398, r4

    blr
    // clang-format on
}

asm void LCLoadBlocks(register void* dst, register const void* src,
                      register u32 len) {
    // clang-format off
    nofralloc

    rlwinm r6, len, 30, 27, 31
    clrlwi src, src, 3
    or r6, r6, src
    mtspr DMA_U, r6
    rlwinm r6, len, 2, 28, 29
    or r6, r6, dst
    ori r6, r6, 0x12
    mtspr DMA_L, r6

    blr
    // clang-format on
}

asm void LCStoreBlocks(register void* dst, register const void* src,
                       register u32 len){
    // clang-format off
    nofralloc

    rlwinm r6, len, 30, 27, 31
    clrlwi dst, dst, 3
    or r6, r6, dst
    mtspr DMA_U, r6
    rlwinm r6, len, 2, 28, 29
    or r6, r6, src
    ori r6, r6, 0x2
    mtspr DMA_L, r6

    blr
    // clang-format on
}

u32 LCStoreData(void* dst, const void* src, u32 len) {
    u32 blocks = (len + 31) / 32;
    u32 ret = (blocks + 127) / 128;

    while (blocks > 0) {
        if (blocks < 128) {
            LCStoreBlocks(dst, src, blocks);
            blocks = 0;
        } else {
            LCStoreBlocks(dst, src, 0);
            blocks -= 128;

            dst = (u8*)dst + 0x1000;
            src = (u8*)src + 0x1000;
        }
    }

    return ret;
}

asm u32 LCQueueLength(void) {
    // clang-format off
    nofralloc

    mfspr r4, 0x398
    rlwinm r3, r4, 8, 28, 31

    blr
    // clang-format on
}

asm void LCQueueWait(register u32 n) {
    // clang-format off
    nofralloc

    mfspr r4, 0x398
    rlwinm r4, r4, 8, 28, 31
    cmpw r4, n
    bgt LCQueueWait

    blr
    // clang-format on
}

static void L2Init(void) {
    u32 msr;

    msr = PPCMfmsr();
    __sync();
    PPCMtmsr(MSR_IR | MSR_DR);
    __sync();

    L2Disable();
    L2GlobalInvalidate();
    PPCMtmsr(msr);
}

void L2Enable(void) {
    u32 l2cr = PPCMfl2cr();
    PPCMtl2cr((l2cr | L2CR_L2E) & ~L2CR_L2I);
}

void L2Disable(void) {
    u32 l2cr;

    __sync();
    l2cr = PPCMfl2cr();
    PPCMtl2cr(l2cr & ~L2CR_L2E);
    __sync();
}

void L2GlobalInvalidate(void) {
    u32 l2cr;

    L2Disable();

    l2cr = PPCMfl2cr();
    PPCMtl2cr(l2cr | L2CR_L2I);

    while (PPCMfl2cr() & L2CR_L2IP) {
    }

    l2cr = PPCMfl2cr();
    PPCMtl2cr(l2cr & ~L2CR_L2I);

    while (PPCMfl2cr() & L2CR_L2IP) {
        DBPrintf(">>> L2 INVALIDATE : SHOULD NEVER HAPPEN\n");
    }
}

void DMAErrorHandler(u8 error, OSContext* ctx, u32 dsisr, u32 dar, ...) {
    u32 hid2 = PPCMfhid2();

    OSReport("Machine check received\n");
    OSReport("HID2 = 0x%x   SRR1 = 0x%x\n", hid2, ctx->srr1);

    if (!(hid2 & (HID2_DCHERR | HID2_DNCERR | HID2_DCMERR | HID2_DQOERR)) ||
        !(ctx->srr1 & 0x200000)) {
        OSReport("Machine check was not DMA/locked cache related\n");
        OSDumpContext(ctx);
        PPCHalt();
    }

    OSReport("DMAErrorHandler(): An error occurred while processing DMA.\n");
    OSReport("The following errors have been detected and cleared :\n");

    if (hid2 & HID2_DCHERR) {
        OSReport(
            "\t- Requested a locked cache tag that was already in the cache\n");
    }
    if (hid2 & HID2_DNCERR) {
        OSReport("\t- DMA attempted to access normal cache\n");
    }
    if (hid2 & HID2_DCMERR) {
        OSReport("\t- DMA missed in data cache\n");
    }
    if (hid2 & HID2_DQOERR) {
        OSReport("\t- DMA queue overflowed\n");
    }

    PPCMthid2(hid2);
}

void __OSCacheInit(void) {
    if (!(PPCMfhid0() & HID0_ICE)) {
        ICEnable();
        DBPrintf("L1 i-caches initialized\n");
    }

    if (!(PPCMfhid0() & HID0_DCE)) {
        DCEnable();
        DBPrintf("L1 d-caches initialized\n");
    }

    if (!(PPCMfl2cr() & L2CR_L2E)) {
        L2Init();
        L2Enable();
        DBPrintf("L2 cache initialized\n");
    }

    OSSetErrorHandler(OS_ERR_MACHINE_CHECK, DMAErrorHandler);
    DBPrintf("Locked cache machine check handler installed\n");
}
