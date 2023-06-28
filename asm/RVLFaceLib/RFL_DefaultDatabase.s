.include "macros.inc"

.section .rodata, "a"
.balign 0x8
.global lbl_80381B58
lbl_80381B58:
	.incbin "baserom.dol", 0x37DC58, 0x1C0

.section .text, "ax"
.global RFLiGetDefaultData
RFLiGetDefaultData:
/* 801765CC 001714CC  1C 04 00 4A */	mulli r0, r4, 0x4a
/* 801765D0 001714D0  3C A0 80 38 */	lis r5, lbl_80381B58@ha
/* 801765D4 001714D4  7C 64 1B 78 */	mr r4, r3
/* 801765D8 001714D8  38 A5 1B 58 */	addi r5, r5, lbl_80381B58@l
/* 801765DC 001714DC  7C 65 02 14 */	add r3, r5, r0
/* 801765E0 001714E0  4B FF C9 84 */	b RFLiConvertRaw2Info
