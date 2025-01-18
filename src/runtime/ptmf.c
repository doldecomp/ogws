#include <types.h>

typedef struct PTMF {
    s32 clsoffset; // at 0x0
    s32 vfoffset;  // at 0x4
    union {
        s32 vtoffset;
        void* func;
    }; // at 0x8
} PTMF;

asm BOOL __ptmf_test(register const PTMF* ptmf) {
    // clang-format off
    nofralloc

    lwz r5, ptmf->clsoffset
    lwz r6, ptmf->vfoffset
    lwz r7, ptmf->func
        
    li r3, 1
        
    cmpwi r5, 0
    cmpwi cr6, r6, 0
    cmpwi cr7, r7, 0

    bnelr
    bnelr cr6
    bnelr cr7
    
    li r3, 0
    blr
    // clang-format on
}

asm void __ptmf_scall(void) {
    // clang-format off
    nofralloc

    lwz r0, PTMF.clsoffset(r12)
    lwz r11, PTMF.vfoffset(r12)
    lwz r12, PTMF.vtoffset(r12)

    // Apply offset to this pointer
    add r3, r3, r0

    // -1 vfoffset means not a virtual call
    // (vtoffset will be the function address)
    cmpwi r11, 0
    blt call_function

    // Load virtual function table
    lwzx r12, r3, r12
    // Load virtual function pointer
    lwzx r12, r12, r11
    
call_function:
    // Call function
    mtctr r12
    bctr
    // clang-format on
}