.include "macros.inc"

.section .data, "wa"
.balign 0x8
__SinTableFixedPoint:
	.incbin "baserom.dol", 0x3AACA0, 0x200

.section .text, "ax"
.global __AXFXGetLfoSinTable
__AXFXGetLfoSinTable:
/* 8010A9C0 001058C0  3C 60 80 3B */	lis r3, __SinTableFixedPoint@ha
/* 8010A9C4 001058C4  38 63 EB A0 */	addi r3, r3, __SinTableFixedPoint@l
/* 8010A9C8 001058C8  4E 80 00 20 */	blr 
