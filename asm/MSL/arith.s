.include "macros.inc"

.section .text, "ax"
.global abs
abs:
/* 800B43A8 000AF2A8  7C 64 FE 70 */	srawi r4, r3, 0x1f
/* 800B43AC 000AF2AC  7C 80 1A 78 */	xor r0, r4, r3
/* 800B43B0 000AF2B0  7C 64 00 50 */	subf r3, r4, r0
/* 800B43B4 000AF2B4  4E 80 00 20 */	blr 
