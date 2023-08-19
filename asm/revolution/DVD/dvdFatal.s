.include "macros.inc"

.section .sbss, "wa"
.balign 0x8
FatalFunc:
	.skip 0x4

.section .sdata2, "a"
.balign 0x8
# OSFatal text color
lbl_804C13D8:
	.byte 255, 255, 255, 0

.section .rodata, "a"
.balign 0x8
.global __DVDErrorMessage
__DVDErrorMessage:
	.incbin "baserom.dol", 0x378BD0, 0x20

.section .data, "wa"
.balign 0x8
strings_803b60e8: # see __DVDErrorMessage (SJIS btw)
	.incbin "baserom.dol", 0x3B21E8, 0x4B0

.section .text, "ax"
.global __DVDShowFatalMessage
__DVDShowFatalMessage:
/* 8013EA2C 0013992C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8013EA30 00139930  7C 08 02 A6 */	mflr r0
/* 8013EA34 00139934  90 01 00 24 */	stw r0, 0x24(r1)
/* 8013EA38 00139938  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8013EA3C 0013993C  3B E0 00 00 */	li r31, 0
/* 8013EA40 00139940  88 A2 99 B8 */	lbz r5, lbl_804C13D8-_SDA2_BASE_(r2)
/* 8013EA44 00139944  88 82 99 B9 */	lbz r4, (lbl_804C13D8+0x1)-_SDA2_BASE_(r2)
/* 8013EA48 00139948  88 62 99 BA */	lbz r3, (lbl_804C13D8+0x2)-_SDA2_BASE_(r2)
/* 8013EA4C 0013994C  88 02 99 BB */	lbz r0, (lbl_804C13D8+0x3)-_SDA2_BASE_(r2)
/* 8013EA50 00139950  98 A1 00 10 */	stb r5, 0x10(r1)
/* 8013EA54 00139954  98 81 00 11 */	stb r4, 0x11(r1)
/* 8013EA58 00139958  98 61 00 12 */	stb r3, 0x12(r1)
/* 8013EA5C 0013995C  98 01 00 13 */	stb r0, 0x13(r1)
/* 8013EA60 00139960  4B FB A0 31 */	bl SCGetLanguage
/* 8013EA64 00139964  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 8013EA68 00139968  40 82 00 10 */	bne lbl_8013EA78
/* 8013EA6C 0013996C  38 60 00 01 */	li r3, 1
/* 8013EA70 00139970  4B FB 1D FD */	bl OSSetFontEncode
/* 8013EA74 00139974  48 00 00 0C */	b lbl_8013EA80
lbl_8013EA78:
/* 8013EA78 00139978  38 60 00 00 */	li r3, 0
/* 8013EA7C 0013997C  4B FB 1D F1 */	bl OSSetFontEncode
lbl_8013EA80:
/* 8013EA80 00139980  4B FB A0 11 */	bl SCGetLanguage
/* 8013EA84 00139984  54 60 06 3E */	clrlwi r0, r3, 0x18
/* 8013EA88 00139988  28 00 00 06 */	cmplwi r0, 6
/* 8013EA8C 0013998C  40 81 00 14 */	ble lbl_8013EAA0
/* 8013EA90 00139990  3C 60 80 38 */	lis r3, __DVDErrorMessage@ha
/* 8013EA94 00139994  38 63 CA D0 */	addi r3, r3, __DVDErrorMessage@l
/* 8013EA98 00139998  80 A3 00 04 */	lwz r5, 4(r3)
/* 8013EA9C 0013999C  48 00 00 18 */	b lbl_8013EAB4
lbl_8013EAA0:
/* 8013EAA0 001399A0  4B FB 9F F1 */	bl SCGetLanguage
/* 8013EAA4 001399A4  3C 80 80 38 */	lis r4, __DVDErrorMessage@ha
/* 8013EAA8 001399A8  54 60 15 BA */	rlwinm r0, r3, 2, 0x16, 0x1d
/* 8013EAAC 001399AC  38 84 CA D0 */	addi r4, r4, __DVDErrorMessage@l
/* 8013EAB0 001399B0  7C A4 00 2E */	lwzx r5, r4, r0
lbl_8013EAB4:
/* 8013EAB4 001399B4  80 01 00 10 */	lwz r0, 0x10(r1)
/* 8013EAB8 001399B8  38 61 00 0C */	addi r3, r1, 0xc
/* 8013EABC 001399BC  93 E1 00 08 */	stw r31, 8(r1)
/* 8013EAC0 001399C0  38 81 00 08 */	addi r4, r1, 8
/* 8013EAC4 001399C4  90 01 00 0C */	stw r0, 0xc(r1)
/* 8013EAC8 001399C8  4B FB 12 75 */	bl OSFatal
/* 8013EACC 001399CC  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8013EAD0 001399D0  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8013EAD4 001399D4  7C 08 03 A6 */	mtlr r0
/* 8013EAD8 001399D8  38 21 00 20 */	addi r1, r1, 0x20
/* 8013EADC 001399DC  4E 80 00 20 */	blr 

.global DVDSetAutoFatalMessaging
DVDSetAutoFatalMessaging:
/* 8013EAE0 001399E0  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8013EAE4 001399E4  7C 08 02 A6 */	mflr r0
/* 8013EAE8 001399E8  90 01 00 14 */	stw r0, 0x14(r1)
/* 8013EAEC 001399EC  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8013EAF0 001399F0  7C 7F 1B 78 */	mr r31, r3
/* 8013EAF4 001399F4  4B FB 2D CD */	bl OSDisableInterrupts
/* 8013EAF8 001399F8  80 AD A0 28 */	lwz r5, FatalFunc-_SDA_BASE_(r13)
/* 8013EAFC 001399FC  2C 1F 00 00 */	cmpwi r31, 0
/* 8013EB00 00139A00  38 80 00 00 */	li r4, 0
/* 8013EB04 00139A04  7C 05 00 D0 */	neg r0, r5
/* 8013EB08 00139A08  7C 00 2B 78 */	or r0, r0, r5
/* 8013EB0C 00139A0C  54 1F 0F FE */	srwi r31, r0, 0x1f
/* 8013EB10 00139A10  41 82 00 0C */	beq lbl_8013EB1C
/* 8013EB14 00139A14  3C 80 80 14 */	lis r4, __DVDShowFatalMessage@ha
/* 8013EB18 00139A18  38 84 EA 2C */	addi r4, r4, __DVDShowFatalMessage@l
lbl_8013EB1C:
/* 8013EB1C 00139A1C  90 8D A0 28 */	stw r4, FatalFunc-_SDA_BASE_(r13)
/* 8013EB20 00139A20  4B FB 2D C9 */	bl OSRestoreInterrupts
/* 8013EB24 00139A24  7F E3 FB 78 */	mr r3, r31
/* 8013EB28 00139A28  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8013EB2C 00139A2C  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8013EB30 00139A30  7C 08 03 A6 */	mtlr r0
/* 8013EB34 00139A34  38 21 00 10 */	addi r1, r1, 0x10
/* 8013EB38 00139A38  4E 80 00 20 */	blr 

.global __DVDGetAutoFatalMessaging
__DVDGetAutoFatalMessaging:
/* 8013EB3C 00139A3C  80 6D A0 28 */	lwz r3, FatalFunc-_SDA_BASE_(r13)
/* 8013EB40 00139A40  7C 03 00 D0 */	neg r0, r3
/* 8013EB44 00139A44  7C 00 1B 78 */	or r0, r0, r3
/* 8013EB48 00139A48  54 03 0F FE */	srwi r3, r0, 0x1f
/* 8013EB4C 00139A4C  4E 80 00 20 */	blr 

.global __DVDPrintFatalMessage
__DVDPrintFatalMessage:
/* 8013EB50 00139A50  81 8D A0 28 */	lwz r12, FatalFunc-_SDA_BASE_(r13)
/* 8013EB54 00139A54  2C 0C 00 00 */	cmpwi r12, 0
/* 8013EB58 00139A58  4D 82 00 20 */	beqlr 
/* 8013EB5C 00139A5C  7D 89 03 A6 */	mtctr r12
/* 8013EB60 00139A60  4E 80 04 20 */	bctr 
/* 8013EB64 00139A64  4E 80 00 20 */	blr 
