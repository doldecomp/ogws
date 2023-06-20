.include "macros.inc"

.section .bss, "wa"
bUseSerialIO:
	.skip 0x1

.section .text, "ax"
.global GetUseSerialIO
GetUseSerialIO:
/* 800C622C 000C112C  3C 60 80 41 */	lis r3, bUseSerialIO@ha
/* 800C6230 000C1130  38 63 DC 30 */	addi r3, r3, bUseSerialIO@l
/* 800C6234 000C1134  88 63 00 00 */	lbz r3, 0(r3)
/* 800C6238 000C1138  4E 80 00 20 */	blr 

.global SetUseSerialIO
SetUseSerialIO:
/* 800C623C 000C113C  3C 80 80 41 */	lis r4, bUseSerialIO@ha
/* 800C6240 000C1140  98 64 DC 30 */	stb r3, bUseSerialIO@l(r4)
/* 800C6244 000C1144  4E 80 00 20 */	blr 
