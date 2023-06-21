.include "macros.inc"

.section .sbss, "wa"
.balign 0x8
__init:
	.skip 0x4

.section .sdata, "wa"
.balign 0x8
lbl_804BD898:
	.long lbl_803AB798

.section .data, "wa"
.balign 0x8
lbl_803AB798:
	.string "<< RVL_SDK - AX \trelease build: Dec 18 2006 15:43:48 (0x4199_60831) >>"

.section .text, "ax"
.global AXInit
AXInit:
/* 80104450 000FF350  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80104454 000FF354  7C 08 02 A6 */	mflr r0
/* 80104458 000FF358  90 01 00 14 */	stw r0, 0x14(r1)
/* 8010445C 000FF35C  80 0D 9D E0 */	lwz r0, __init-_SDA_BASE_(r13)
/* 80104460 000FF360  2C 00 00 00 */	cmpwi r0, 0
/* 80104464 000FF364  40 82 00 30 */	bne lbl_80104494
/* 80104468 000FF368  80 6D 85 18 */	lwz r3, lbl_804BD898-_SDA_BASE_(r13)
/* 8010446C 000FF36C  4B FE 8B D5 */	bl OSRegisterVersion
/* 80104470 000FF370  48 00 00 F5 */	bl __AXAllocInit
/* 80104474 000FF374  48 00 2C 49 */	bl __AXVPBInit
/* 80104478 000FF378  48 00 21 D1 */	bl __AXSPBInit
/* 8010447C 000FF37C  48 00 04 E1 */	bl __AXAuxInit
/* 80104480 000FF380  48 00 16 ED */	bl __AXClInit
/* 80104484 000FF384  38 60 00 00 */	li r3, 0
/* 80104488 000FF388  48 00 1B E1 */	bl __AXOutInit
/* 8010448C 000FF38C  38 00 00 01 */	li r0, 1
/* 80104490 000FF390  90 0D 9D E0 */	stw r0, __init-_SDA_BASE_(r13)
lbl_80104494:
/* 80104494 000FF394  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80104498 000FF398  7C 08 03 A6 */	mtlr r0
/* 8010449C 000FF39C  38 21 00 10 */	addi r1, r1, 0x10
/* 801044A0 000FF3A0  4E 80 00 20 */	blr 
