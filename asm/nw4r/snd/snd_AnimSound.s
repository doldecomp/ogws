.include "macros.inc"

.section .text, "ax"

.global __dt__Q34nw4r3snd11SoundHandle
__dt__Q34nw4r3snd11SoundHandle:
/* 80030D7C 0002BC7C  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80030D80 0002BC80  7C 08 02 A6 */	mflr r0
/* 80030D84 0002BC84  2C 03 00 00 */	cmpwi r3, 0
/* 80030D88 0002BC88  90 01 00 14 */	stw r0, 0x14(r1)
/* 80030D8C 0002BC8C  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80030D90 0002BC90  7C 9F 23 78 */	mr r31, r4
/* 80030D94 0002BC94  93 C1 00 08 */	stw r30, 8(r1)
/* 80030D98 0002BC98  7C 7E 1B 78 */	mr r30, r3
/* 80030D9C 0002BC9C  41 82 00 18 */	beq lbl_80030DB4
/* 80030DA0 0002BCA0  48 01 4D BD */	bl DetachSound__Q34nw4r3snd11SoundHandleFv
/* 80030DA4 0002BCA4  2C 1F 00 00 */	cmpwi r31, 0
/* 80030DA8 0002BCA8  40 81 00 0C */	ble lbl_80030DB4
/* 80030DAC 0002BCAC  7F C3 F3 78 */	mr r3, r30
/* 80030DB0 0002BCB0  48 07 24 D5 */	bl __dl__FPv
lbl_80030DB4:
/* 80030DB4 0002BCB4  7F C3 F3 78 */	mr r3, r30
/* 80030DB8 0002BCB8  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80030DBC 0002BCBC  83 C1 00 08 */	lwz r30, 8(r1)
/* 80030DC0 0002BCC0  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80030DC4 0002BCC4  7C 08 03 A6 */	mtlr r0
/* 80030DC8 0002BCC8  38 21 00 10 */	addi r1, r1, 0x10
/* 80030DCC 0002BCCC  4E 80 00 20 */	blr 
