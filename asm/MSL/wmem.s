.include "macros.inc"

.section .text, "ax"
.global wmemcpy
wmemcpy:
/* 800BAD14 000B5C14  54 A5 08 3C */	slwi r5, r5, 1
/* 800BAD18 000B5C18  4B F4 92 E8 */	b memcpy

.global wmemchr
wmemchr:
/* 800BAD1C 000B5C1C  7C A9 03 A6 */	mtctr r5
/* 800BAD20 000B5C20  2C 05 00 00 */	cmpwi r5, 0
/* 800BAD24 000B5C24  41 82 00 18 */	beq lbl_800BAD3C
lbl_800BAD28:
/* 800BAD28 000B5C28  A0 03 00 00 */	lhz r0, 0(r3)
/* 800BAD2C 000B5C2C  7C 00 20 40 */	cmplw r0, r4
/* 800BAD30 000B5C30  4D 82 00 20 */	beqlr 
/* 800BAD34 000B5C34  38 63 00 02 */	addi r3, r3, 2
/* 800BAD38 000B5C38  42 00 FF F0 */	bdnz lbl_800BAD28
lbl_800BAD3C:
/* 800BAD3C 000B5C3C  38 60 00 00 */	li r3, 0
/* 800BAD40 000B5C40  4E 80 00 20 */	blr 
