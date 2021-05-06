.include "macros.inc"

.section .data, "wa"
.balign 0x8
.global __vt__Q23EGG8Disposer
__vt__Q23EGG8Disposer:
    .long 0
    .long 0
    .long __dt__Q23EGG8DisposerFv
    .long 0

.section .text, "ax"
.global __ct__Q23EGG8DisposerFv
__ct__Q23EGG8DisposerFv:
/* 800AC048 000A6F48  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800AC04C 000A6F4C  7C 08 02 A6 */	mflr r0
/* 800AC050 000A6F50  3C 80 80 3A */	lis r4, __vt__Q23EGG8Disposer@ha
/* 800AC054 000A6F54  90 01 00 14 */	stw r0, 0x14(r1)
/* 800AC058 000A6F58  38 84 84 58 */	addi r4, r4, __vt__Q23EGG8Disposer@l
/* 800AC05C 000A6F5C  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800AC060 000A6F60  7C 7F 1B 78 */	mr r31, r3
/* 800AC064 000A6F64  90 83 00 00 */	stw r4, 0(r3)
/* 800AC068 000A6F68  4B FF 6F 91 */	bl findContainHeap__Q23EGG4HeapFPCv
/* 800AC06C 000A6F6C  2C 03 00 00 */	cmpwi r3, 0
/* 800AC070 000A6F70  90 7F 00 04 */	stw r3, 4(r31)
/* 800AC074 000A6F74  41 82 00 10 */	beq lbl_800AC084
/* 800AC078 000A6F78  7F E4 FB 78 */	mr r4, r31
/* 800AC07C 000A6F7C  38 63 00 28 */	addi r3, r3, 0x28
/* 800AC080 000A6F80  4B F5 B6 79 */	bl List_Append__Q24nw4r2utFPQ34nw4r2ut4ListPv
lbl_800AC084:
/* 800AC084 000A6F84  7F E3 FB 78 */	mr r3, r31
/* 800AC088 000A6F88  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 800AC08C 000A6F8C  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800AC090 000A6F90  7C 08 03 A6 */	mtlr r0
/* 800AC094 000A6F94  38 21 00 10 */	addi r1, r1, 0x10
/* 800AC098 000A6F98  4E 80 00 20 */	blr 

.global __dt__Q23EGG8DisposerFv
__dt__Q23EGG8DisposerFv:
/* 800AC09C 000A6F9C  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800AC0A0 000A6FA0  7C 08 02 A6 */	mflr r0
/* 800AC0A4 000A6FA4  2C 03 00 00 */	cmpwi r3, 0
/* 800AC0A8 000A6FA8  90 01 00 14 */	stw r0, 0x14(r1)
/* 800AC0AC 000A6FAC  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800AC0B0 000A6FB0  7C 9F 23 78 */	mr r31, r4
/* 800AC0B4 000A6FB4  93 C1 00 08 */	stw r30, 8(r1)
/* 800AC0B8 000A6FB8  7C 7E 1B 78 */	mr r30, r3
/* 800AC0BC 000A6FBC  41 82 00 38 */	beq lbl_800AC0F4
/* 800AC0C0 000A6FC0  80 A3 00 04 */	lwz r5, 4(r3)
/* 800AC0C4 000A6FC4  3C 80 80 3A */	lis r4, __vt__Q23EGG8Disposer@ha
/* 800AC0C8 000A6FC8  38 84 84 58 */	addi r4, r4, __vt__Q23EGG8Disposer@l
/* 800AC0CC 000A6FCC  2C 05 00 00 */	cmpwi r5, 0
/* 800AC0D0 000A6FD0  90 83 00 00 */	stw r4, 0(r3)
/* 800AC0D4 000A6FD4  41 82 00 10 */	beq lbl_800AC0E4
/* 800AC0D8 000A6FD8  7F C4 F3 78 */	mr r4, r30
/* 800AC0DC 000A6FDC  38 65 00 28 */	addi r3, r5, 0x28
/* 800AC0E0 000A6FE0  4B F5 B7 A9 */	bl List_Remove__Q24nw4r2utFPQ34nw4r2ut4ListPv
lbl_800AC0E4:
/* 800AC0E4 000A6FE4  2C 1F 00 00 */	cmpwi r31, 0
/* 800AC0E8 000A6FE8  40 81 00 0C */	ble lbl_800AC0F4
/* 800AC0EC 000A6FEC  7F C3 F3 78 */	mr r3, r30
/* 800AC0F0 000A6FF0  4B FF 71 95 */	bl __dl__FPv
lbl_800AC0F4:
/* 800AC0F4 000A6FF4  7F C3 F3 78 */	mr r3, r30
/* 800AC0F8 000A6FF8  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 800AC0FC 000A6FFC  83 C1 00 08 */	lwz r30, 8(r1)
/* 800AC100 000A7000  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800AC104 000A7004  7C 08 03 A6 */	mtlr r0
/* 800AC108 000A7008  38 21 00 10 */	addi r1, r1, 0x10
/* 800AC10C 000A700C  4E 80 00 20 */	blr 
