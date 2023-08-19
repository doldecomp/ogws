.include "macros.inc"

.section .bss, "wa"
.balign 0x8
TRK_mainError:
	.skip 0x8

.section .text, "ax"
.global TRK_main
TRK_main:
/* 800C5CF4 000C0BF4  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800C5CF8 000C0BF8  7C 08 02 A6 */	mflr r0
/* 800C5CFC 000C0BFC  90 01 00 14 */	stw r0, 0x14(r1)
/* 800C5D00 000C0C00  4B FF B7 41 */	bl TRKInitializeNub
/* 800C5D04 000C0C04  3C 80 80 41 */	lis r4, TRK_mainError@ha
/* 800C5D08 000C0C08  2C 03 00 00 */	cmpwi r3, 0
/* 800C5D0C 000C0C0C  90 64 DC 20 */	stw r3, TRK_mainError@l(r4)
/* 800C5D10 000C0C10  40 82 00 0C */	bne lbl_800C5D1C
/* 800C5D14 000C0C14  4B FF B6 E1 */	bl TRKNubWelcome
/* 800C5D18 000C0C18  4B FF B3 BD */	bl TRKNubMainLoop
lbl_800C5D1C:
/* 800C5D1C 000C0C1C  4B FF B7 01 */	bl TRKTerminateNub
/* 800C5D20 000C0C20  3C 80 80 41 */	lis r4, TRK_mainError@ha
/* 800C5D24 000C0C24  90 64 DC 20 */	stw r3, TRK_mainError@l(r4)
/* 800C5D28 000C0C28  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800C5D2C 000C0C2C  7C 08 03 A6 */	mtlr r0
/* 800C5D30 000C0C30  38 21 00 10 */	addi r1, r1, 0x10
/* 800C5D34 000C0C34  4E 80 00 20 */	blr 
