.include "macros.inc"

.section .data, "wa"
.balign 0x8
__SrcTab12khz:
	.incbin "baserom.dol", 0x3AAEA0, 0x800

.section .text, "ax"
.global __AXFXGetSrcCoef
__AXFXGetSrcCoef:
/* 8010A9CC 001058CC  3C 80 80 3B */	lis r4, __SrcTab12khz@ha
/* 8010A9D0 001058D0  54 60 20 36 */	slwi r0, r3, 4
/* 8010A9D4 001058D4  38 84 ED A0 */	addi r4, r4, __SrcTab12khz@l
/* 8010A9D8 001058D8  7C 64 02 14 */	add r3, r4, r0
/* 8010A9DC 001058DC  4E 80 00 20 */	blr 
