.include "macros.inc"

.section .sbss, "wa"
.balign 0x8
.global __PADSpec
__PADSpec:
	.skip 0x4

.section .text, "ax"
.global __PADDisableRecalibration
__PADDisableRecalibration:
/* 800CA374 000C5274  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800CA378 000C5278  7C 08 02 A6 */	mflr r0
/* 800CA37C 000C527C  90 01 00 14 */	stw r0, 0x14(r1)
/* 800CA380 000C5280  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800CA384 000C5284  7C 7F 1B 78 */	mr r31, r3
/* 800CA388 000C5288  48 02 75 39 */	bl OSDisableInterrupts
/* 800CA38C 000C528C  3C A0 80 00 */	lis r5, 0x800030E3@ha
/* 800CA390 000C5290  2C 1F 00 00 */	cmpwi r31, 0
/* 800CA394 000C5294  88 85 30 E3 */	lbz r4, 0x800030E3@l(r5)
/* 800CA398 000C5298  54 80 06 B0 */	rlwinm r0, r4, 0, 0x1a, 0x18
/* 800CA39C 000C529C  54 9F D7 FE */	rlwinm r31, r4, 0x1a, 0x1f, 0x1f
/* 800CA3A0 000C52A0  98 05 30 E3 */	stb r0, 0x30e3(r5)
/* 800CA3A4 000C52A4  41 82 00 10 */	beq lbl_800CA3B4
/* 800CA3A8 000C52A8  88 05 30 E3 */	lbz r0, 0x30e3(r5)
/* 800CA3AC 000C52AC  60 00 00 40 */	ori r0, r0, 0x40
/* 800CA3B0 000C52B0  98 05 30 E3 */	stb r0, 0x30e3(r5)
lbl_800CA3B4:
/* 800CA3B4 000C52B4  48 02 75 35 */	bl OSRestoreInterrupts
/* 800CA3B8 000C52B8  7F E3 FB 78 */	mr r3, r31
/* 800CA3BC 000C52BC  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 800CA3C0 000C52C0  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800CA3C4 000C52C4  7C 08 03 A6 */	mtlr r0
/* 800CA3C8 000C52C8  38 21 00 10 */	addi r1, r1, 0x10
/* 800CA3CC 000C52CC  4E 80 00 20 */	blr 
