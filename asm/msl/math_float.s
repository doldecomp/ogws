.include "macros.inc"

.section .text, "ax"
.global fabsf
fabsf:
/* 800BD1A4 000B80A4  FC 00 08 18 */	frsp f0, f1
/* 800BD1A8 000B80A8  FC 00 02 10 */	fabs f0, f0
/* 800BD1AC 000B80AC  FC 20 00 18 */	frsp f1, f0
/* 800BD1B0 000B80B0  4E 80 00 20 */	blr 
