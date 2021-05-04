.include "macros.inc"

.section .data, "wa"
.global __vt__Q23EGG9Allocator
__vt__Q23EGG9Allocator:
    .long 0
    .long 0
    .long __dt__Q23EGG9AllocatorFv
    .long alloc__Q23EGG9AllocatorFUl
    .long free__Q23EGG9AllocatorFPv
    .long 0

.section .text, "ax"
.global __ct__Q23EGG9AllocatorFPQ23EGG4Heapl
__ct__Q23EGG9AllocatorFPQ23EGG4Heapl:
/* 800A341C 0009E31C  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800A3420 0009E320  7C 08 02 A6 */	mflr r0
/* 800A3424 0009E324  3C C0 80 3A */	lis r6, __vt__Q23EGG9Allocator@ha
/* 800A3428 0009E328  90 01 00 14 */	stw r0, 0x14(r1)
/* 800A342C 0009E32C  38 C6 81 48 */	addi r6, r6, __vt__Q23EGG9Allocator@l
/* 800A3430 0009E330  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800A3434 0009E334  7C 7F 1B 78 */	mr r31, r3
/* 800A3438 0009E338  7C 83 23 78 */	mr r3, r4
/* 800A343C 0009E33C  90 DF 00 10 */	stw r6, 0x10(r31)
/* 800A3440 0009E340  7F E4 FB 78 */	mr r4, r31
/* 800A3444 0009E344  81 83 00 00 */	lwz r12, 0(r3)
/* 800A3448 0009E348  81 8C 00 10 */	lwz r12, 0x10(r12)
/* 800A344C 0009E34C  7D 89 03 A6 */	mtctr r12
/* 800A3450 0009E350  4E 80 04 21 */	bctrl 
/* 800A3454 0009E354  7F E3 FB 78 */	mr r3, r31
/* 800A3458 0009E358  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 800A345C 0009E35C  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800A3460 0009E360  7C 08 03 A6 */	mtlr r0
/* 800A3464 0009E364  38 21 00 10 */	addi r1, r1, 0x10
/* 800A3468 0009E368  4E 80 00 20 */	blr 

.global __dt__Q23EGG9AllocatorFv
__dt__Q23EGG9AllocatorFv:
/* 800A346C 0009E36C  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800A3470 0009E370  7C 08 02 A6 */	mflr r0
/* 800A3474 0009E374  2C 03 00 00 */	cmpwi r3, 0
/* 800A3478 0009E378  90 01 00 14 */	stw r0, 0x14(r1)
/* 800A347C 0009E37C  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800A3480 0009E380  7C 7F 1B 78 */	mr r31, r3
/* 800A3484 0009E384  41 82 00 10 */	beq lbl_800A3494
/* 800A3488 0009E388  2C 04 00 00 */	cmpwi r4, 0
/* 800A348C 0009E38C  40 81 00 08 */	ble lbl_800A3494
/* 800A3490 0009E390  4B FF FD F5 */	bl __dl__FPv
lbl_800A3494:
/* 800A3494 0009E394  7F E3 FB 78 */	mr r3, r31
/* 800A3498 0009E398  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 800A349C 0009E39C  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800A34A0 0009E3A0  7C 08 03 A6 */	mtlr r0
/* 800A34A4 0009E3A4  38 21 00 10 */	addi r1, r1, 0x10
/* 800A34A8 0009E3A8  4E 80 00 20 */	blr 

.global alloc__Q23EGG9AllocatorFUl
alloc__Q23EGG9AllocatorFUl:
/* 800A34AC 0009E3AC  48 04 3F E0 */	b func_800E748C

.global free__Q23EGG9AllocatorFPv
free__Q23EGG9AllocatorFPv:
/* 800A34B0 0009E3B0  48 04 3F EC */	b func_800E749C
