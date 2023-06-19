.include "macros.inc"

.section .text, "ax"
.global __stdio_atexit
__stdio_atexit:
/* 800B52D0 000B01D0  3C 60 80 0B */	lis r3, __close_all@ha
/* 800B52D4 000B01D4  38 63 29 28 */	addi r3, r3, __close_all@l
/* 800B52D8 000B01D8  90 6D 99 F8 */	stw r3, __stdio_exit-_SDA_BASE_(r13)
/* 800B52DC 000B01DC  4E 80 00 20 */	blr 
