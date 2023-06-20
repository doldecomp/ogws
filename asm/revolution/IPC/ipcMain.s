.include "macros.inc"

.section .sbss, "wa"
.balign 0x8
Initialized:
	.skip 0x4
IPCCurrentBufferLo:
	.skip 0x4
IPCCurrentBufferHi:
	.skip 0x4
IPCBufferLo:
	.skip 0x4
IPCBufferHi:
	.skip 0x8

.section .text, "ax"
.global IPCInit
IPCInit:
/* 800E3F78 000DEE78  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800E3F7C 000DEE7C  7C 08 02 A6 */	mflr r0
/* 800E3F80 000DEE80  90 01 00 14 */	stw r0, 0x14(r1)
/* 800E3F84 000DEE84  88 0D 9B 40 */	lbz r0, Initialized-_SDA_BASE_(r13)
/* 800E3F88 000DEE88  2C 00 00 00 */	cmpwi r0, 0
/* 800E3F8C 000DEE8C  40 82 00 28 */	bne lbl_800E3FB4
/* 800E3F90 000DEE90  48 01 1F 61 */	bl __OSGetIPCBufferHi
/* 800E3F94 000DEE94  90 6D 9B 50 */	stw r3, IPCBufferHi-_SDA_BASE_(r13)
/* 800E3F98 000DEE98  48 01 1F 61 */	bl __OSGetIPCBufferLo
/* 800E3F9C 000DEE9C  80 8D 9B 50 */	lwz r4, IPCBufferHi-_SDA_BASE_(r13)
/* 800E3FA0 000DEEA0  38 00 00 01 */	li r0, 1
/* 800E3FA4 000DEEA4  90 6D 9B 4C */	stw r3, IPCBufferLo-_SDA_BASE_(r13)
/* 800E3FA8 000DEEA8  90 8D 9B 48 */	stw r4, IPCCurrentBufferHi-_SDA_BASE_(r13)
/* 800E3FAC 000DEEAC  90 6D 9B 44 */	stw r3, IPCCurrentBufferLo-_SDA_BASE_(r13)
/* 800E3FB0 000DEEB0  98 0D 9B 40 */	stb r0, Initialized-_SDA_BASE_(r13)
lbl_800E3FB4:
/* 800E3FB4 000DEEB4  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800E3FB8 000DEEB8  7C 08 03 A6 */	mtlr r0
/* 800E3FBC 000DEEBC  38 21 00 10 */	addi r1, r1, 0x10
/* 800E3FC0 000DEEC0  4E 80 00 20 */	blr 

.global IPCReadReg
IPCReadReg:
/* 800E3FC4 000DEEC4  54 60 10 3A */	slwi r0, r3, 2
/* 800E3FC8 000DEEC8  3C 60 CD 00 */	lis r3, 0xcd00
/* 800E3FCC 000DEECC  7C 63 00 2E */	lwzx r3, r3, r0
/* 800E3FD0 000DEED0  4E 80 00 20 */	blr 

.global IPCWriteReg
IPCWriteReg:
/* 800E3FD4 000DEED4  54 60 10 3A */	slwi r0, r3, 2
/* 800E3FD8 000DEED8  3C 60 CD 00 */	lis r3, 0xcd00
/* 800E3FDC 000DEEDC  7C 83 01 2E */	stwx r4, r3, r0
/* 800E3FE0 000DEEE0  4E 80 00 20 */	blr 

.global IPCGetBufferHi
IPCGetBufferHi:
/* 800E3FE4 000DEEE4  80 6D 9B 48 */	lwz r3, IPCCurrentBufferHi-_SDA_BASE_(r13)
/* 800E3FE8 000DEEE8  4E 80 00 20 */	blr 

.global IPCGetBufferLo
IPCGetBufferLo:
/* 800E3FEC 000DEEEC  80 6D 9B 44 */	lwz r3, IPCCurrentBufferLo-_SDA_BASE_(r13)
/* 800E3FF0 000DEEF0  4E 80 00 20 */	blr 

.global IPCSetBufferLo
IPCSetBufferLo:
/* 800E3FF4 000DEEF4  90 6D 9B 44 */	stw r3, IPCCurrentBufferLo-_SDA_BASE_(r13)
/* 800E3FF8 000DEEF8  4E 80 00 20 */	blr 
