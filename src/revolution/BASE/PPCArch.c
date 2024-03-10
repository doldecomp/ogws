#include <revolution/BASE.h>
#include <revolution/OS.h>

asm u32 PPCMfmsr(void) {
    // clang-format off
    nofralloc
    mfmsr r3
    blr
    // clang-format on
}

asm void PPCMtmsr(register u32 val) {
    // clang-format off
    nofralloc
    mtmsr val
    blr
    // clang-format on
}

asm u32 PPCMfhid0(void) {
    // clang-format off
    nofralloc
    mfhid0 r3
    blr
    // clang-format on
}

asm void PPCMthid0(register u32 val) {
    // clang-format off
    nofralloc
    mthid0 val
    blr
    // clang-format on
}

asm u32 PPCMfl2cr(void) {
    // clang-format off
    nofralloc
    mfl2cr r3
    blr
    // clang-format on
}

asm void PPCMtl2cr(register u32 val) {
    // clang-format off
    nofralloc
    mtl2cr val
    blr
    // clang-format on
}

asm void PPCMtdec(register u32 val) {
    // clang-format off
    nofralloc
    mtdec val
    blr
    // clang-format on
}

asm void PPCSync(void) {
    // clang-format off
    nofralloc
    sc
    blr
    // clang-format on
}

asm void PPCHalt(void) {
    // clang-format off
    nofralloc
    sync

loop:
    nop
    li r3, 0
    nop
    b loop
    // clang-format on
}

asm void PPCMtmmcr0(register u32 val) {
    // clang-format off
    nofralloc
    mtmmcr0 val
    blr
    // clang-format on
}

asm void PPCMtmmcr1(register u32 val) {
    // clang-format off
    nofralloc
    mtmmcr1 val
    blr
    // clang-format on
}

asm void PPCMtpmc1(register u32 val) {
    // clang-format off
    nofralloc
    mtpmc1 val
    blr
    // clang-format on
}

asm void PPCMtpmc2(register u32 val) {
    // clang-format off
    nofralloc
    mtpmc2 val
    blr
    // clang-format on
}

asm void PPCMtpmc3(register u32 val) {
    // clang-format off
    nofralloc
    mtpmc3 val
    blr
    // clang-format on
}

asm void PPCMtpmc4(register u32 val){
    // clang-format off
    nofralloc
    mtpmc4 val
    blr
    // clang-format on
}

u32 PPCMffpscr(void) {
    // clang-format off
    register u64 fpscr;
    asm {
        mffs f31
        stfd f31, fpscr
    }

    return fpscr;
    // clang-format on
}

void PPCMtfpscr(register u32 val) {
    // clang-format off
    register struct {
        f32 tmp;
        f32 data;
    } fpscr;

    asm {
        li r4, 0
        stw val, fpscr.data
        stw r4, fpscr.tmp
        lfd f31, fpscr.tmp
        mtfs f31
    }
    // clang-format on
}

asm u32 PPCMfhid2(void) {
    // clang-format off
    nofralloc
    mfspr r3, 0x398
    blr
    // clang-format on
}

asm void PPCMthid2(register u32 val) {
    // clang-format off
    nofralloc
    mtspr 0x398, val
    blr
    // clang-format on
}

asm u32 PPCMfwpar(void) {
    // clang-format off
    nofralloc
    sync
    mfwpar r3
    blr
    // clang-format on
}

asm void PPCMtwpar(register u32 val) {
    // clang-format off
    nofralloc
    mtwpar r3
    blr
    // clang-format on
}

void PPCDisableSpeculation(void) {
    PPCMthid0(PPCMfhid0() | HID0_SPD);
}

asm void PPCSetFpNonIEEEMode(void) {
    // clang-format off
    nofralloc
    mtfsb1 29
    blr
    // clang-format on
}

void PPCMthid4(register u32 val) {
    if (val & HID4_H4A) {
        // clang-format off
        asm {
            mtspr 0x3F3, val
        }
        // clang-format on
    } else {
        OSReport("H4A should not be cleared because of Broadway errata.\n");
        val |= HID4_H4A;
        // clang-format off
        asm {
            mtspr 0x3F3, val
        }
        // clang-format on
    }
}
