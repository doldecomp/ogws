.include "macros.inc"

.section .text, "ax"
.global __OSModuleInit
__OSModuleInit:
/* 800F2044 000ECF44  38 00 00 00 */	li r0, 0
/* 800F2048 000ECF48  3C 60 80 00 */	lis r3, 0x800030CC@ha
/* 800F204C 000ECF4C  90 03 30 CC */	stw r0, 0x800030CC@l(r3)
/* 800F2050 000ECF50  90 03 30 C8 */	stw r0, 0x30c8(r3)
/* 800F2054 000ECF54  90 03 30 D0 */	stw r0, 0x30d0(r3)
/* 800F2058 000ECF58  4E 80 00 20 */	blr 
