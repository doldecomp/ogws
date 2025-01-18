#include <revolution/BASE.h>
#include <revolution/OS.h>

#pragma section ".ctors$00"
DECL_SECTION(".ctors$00") extern funcptr_t _ctors[];
#pragma section ".dtors$00"
DECL_SECTION(".dtors$00") extern funcptr_t _dtors[];

asm void __init_hardware(void) {
    // clang-format off
    nofralloc

    // Enable floating-point
    mfmsr r0
    ori r0, r0, MSR_FP
    mtmsr r0

    // Backup LR
    mflr r31

    bl __OSPSInit
    bl __OSFPRInit
    bl __OSCacheInit

    // Restore LR
    mtlr r31
    blr
    // clang-format on
}

asm void __flush_cache(register void* dst, register size_t n) {
    // clang-format off
    nofralloc

    lis r5, 0xFFFFFFF1@h
    ori r5, r5, 0xFFFFFFF1@l
    and r5, r5, dst

    subf r3, r5, r3
    add n, n, r3

_loop:
    dcbst 0, r5
    sync
    icbi 0, r5
    addic r5, r5, 8
    subic. n, n, 8
    bge _loop

    isync
    blr
    // clang-format on
}

asm void __init_user(void) {
    // clang-format off
    fralloc

    bl __init_cpp

    frfree
    blr
    // clang-format on
}

void __init_cpp(void) {
    funcptr_t* ctor;

    for (ctor = _ctors; *ctor != NULL; ctor++) {
        (*ctor)();
    }
}

void __fini_cpp(void) {
    funcptr_t* dtor;

    for (dtor = _dtors; *dtor != NULL; dtor++) {
        (*dtor)();
    }
}

void exit(void) {
    __fini_cpp();
    _ExitProcess();
}

void _ExitProcess(void) {
    PPCHalt();
}
