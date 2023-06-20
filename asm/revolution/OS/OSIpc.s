.include "macros.inc"

.section .sdata, "wa"
.balign 0x8
IpcBufferLo:
	.long 0xFFFFFFFF

.section .sbss, "wa"
.balign 0x8
IpcBufferHi:
	.skip 0x8

.section .text, "ax"
.global __OSGetIPCBufferHi
__OSGetIPCBufferHi:
/* 800F5EF0 000F0DF0  80 6D 9C 38 */	lwz r3, IpcBufferHi-_SDA_BASE_(r13)
/* 800F5EF4 000F0DF4  4E 80 00 20 */	blr 

.global __OSGetIPCBufferLo
__OSGetIPCBufferLo:
/* 800F5EF8 000F0DF8  80 6D 83 98 */	lwz r3, IpcBufferLo-_SDA_BASE_(r13)
/* 800F5EFC 000F0DFC  4E 80 00 20 */	blr 

.global __OSInitIPCBuffer
__OSInitIPCBuffer:
/* 800F5F00 000F0E00  3C 60 80 00 */	lis r3, 0x8000
/* 800F5F04 000F0E04  80 03 31 30 */	lwz r0, 0x3130(r3)
/* 800F5F08 000F0E08  90 0D 83 98 */	stw r0, IpcBufferLo-_SDA_BASE_(r13)
/* 800F5F0C 000F0E0C  80 03 31 34 */	lwz r0, 0x3134(r3)
/* 800F5F10 000F0E10  90 0D 9C 38 */	stw r0, IpcBufferHi-_SDA_BASE_(r13)
/* 800F5F14 000F0E14  4E 80 00 20 */	blr 
