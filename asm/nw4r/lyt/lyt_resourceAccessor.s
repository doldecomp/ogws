.include "macros.inc"

.section .text, "ax"

.global __dt__Q34nw4r3lyt16ResourceAccessorFv
__dt__Q34nw4r3lyt16ResourceAccessorFv:
/* 80082964 0007D864  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80082968 0007D868  7C 08 02 A6 */	mflr r0
/* 8008296C 0007D86C  2C 03 00 00 */	cmpwi r3, 0
/* 80082970 0007D870  90 01 00 14 */	stw r0, 0x14(r1)
/* 80082974 0007D874  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80082978 0007D878  7C 7F 1B 78 */	mr r31, r3
/* 8008297C 0007D87C  41 82 00 10 */	beq lbl_8008298C
/* 80082980 0007D880  2C 04 00 00 */	cmpwi r4, 0
/* 80082984 0007D884  40 81 00 08 */	ble lbl_8008298C
/* 80082988 0007D888  48 02 08 FD */	bl __dl__FPv
lbl_8008298C:
/* 8008298C 0007D88C  7F E3 FB 78 */	mr r3, r31
/* 80082990 0007D890  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80082994 0007D894  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80082998 0007D898  7C 08 03 A6 */	mtlr r0
/* 8008299C 0007D89C  38 21 00 10 */	addi r1, r1, 0x10
/* 800829A0 0007D8A0  4E 80 00 20 */	blr 

.global __ct__Q34nw4r3lyt16ResourceAccessorFv
__ct__Q34nw4r3lyt16ResourceAccessorFv:
/* 800829A4 0007D8A4  3C 80 80 39 */	lis r4, lbl_803974D0@ha
/* 800829A8 0007D8A8  38 84 74 D0 */	addi r4, r4, lbl_803974D0@l
/* 800829AC 0007D8AC  90 83 00 00 */	stw r4, 0(r3)
/* 800829B0 0007D8B0  4E 80 00 20 */	blr 

.global GetFont__Q34nw4r3lyt16ResourceAccessorFPCc
GetFont__Q34nw4r3lyt16ResourceAccessorFPCc:
/* 800829B4 0007D8B4  38 60 00 00 */	li r3, 0
/* 800829B8 0007D8B8  4E 80 00 20 */	blr 
