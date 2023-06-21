.include "macros.inc"

.section .sbss, "wa"
.balign 0x8
.global __DBInterface
__DBInterface:
	.skip 0x4
.global DBVerbose
DBVerbose:
	.skip 0x4

.section .data, "wa"
.balign 0x8
lbl_803B5AE8:
	.string "DBExceptionDestination\n"

.section .text, "ax"
.global DBInit
DBInit:
/* 80138A18 00133918  3C 80 80 00 */	lis r4, 0x80000040@ha
/* 80138A1C 0013391C  3C 60 80 14 */	lis r3, __DBExceptionDestination@ha
/* 80138A20 00133920  38 A4 00 40 */	addi r5, r4, 0x80000040@l
/* 80138A24 00133924  38 00 00 01 */	li r0, 1
/* 80138A28 00133928  38 63 8A 88 */	addi r3, r3, __DBExceptionDestination@l
/* 80138A2C 0013392C  90 AD 9F 50 */	stw r5, __DBInterface-_SDA_BASE_(r13)
/* 80138A30 00133930  3C 63 80 00 */	addis r3, r3, 0x8000
/* 80138A34 00133934  90 64 00 48 */	stw r3, 0x48(r4)
/* 80138A38 00133938  90 0D 9F 54 */	stw r0, DBVerbose-_SDA_BASE_(r13)
/* 80138A3C 0013393C  4E 80 00 20 */	blr 

.global __DBExceptionDestinationAux
__DBExceptionDestinationAux:
/* 80138A40 00133940  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80138A44 00133944  7C 08 02 A6 */	mflr r0
/* 80138A48 00133948  3C 60 80 3B */	lis r3, lbl_803B5AE8@ha
/* 80138A4C 0013394C  90 01 00 14 */	stw r0, 0x14(r1)
/* 80138A50 00133950  38 63 5A E8 */	addi r3, r3, lbl_803B5AE8@l
/* 80138A54 00133954  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80138A58 00133958  80 80 00 C0 */	lwz r4, 0xc0(0)
/* 80138A5C 0013395C  3F E4 80 00 */	addis r31, r4, 0x8000
/* 80138A60 00133960  4C C6 31 82 */	crclr 6
/* 80138A64 00133964  48 04 B4 B5 */	bl OSReport
/* 80138A68 00133968  7F E3 FB 78 */	mr r3, r31
/* 80138A6C 0013396C  4B FB 62 11 */	bl OSDumpContext
/* 80138A70 00133970  4B FD 1F E9 */	bl PPCHalt
/* 80138A74 00133974  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80138A78 00133978  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80138A7C 0013397C  7C 08 03 A6 */	mtlr r0
/* 80138A80 00133980  38 21 00 10 */	addi r1, r1, 0x10
/* 80138A84 00133984  4E 80 00 20 */	blr 

.global __DBExceptionDestination
__DBExceptionDestination:
/* 80138A88 00133988  7C 60 00 A6 */	mfmsr r3
/* 80138A8C 0013398C  60 63 00 30 */	ori r3, r3, 0x30
/* 80138A90 00133990  7C 60 01 24 */	mtmsr r3
/* 80138A94 00133994  4B FF FF AC */	b __DBExceptionDestinationAux

.global __DBIsExceptionMarked
__DBIsExceptionMarked:
/* 80138A98 00133998  80 8D 9F 50 */	lwz r4, __DBInterface-_SDA_BASE_(r13)
/* 80138A9C 0013399C  38 00 00 01 */	li r0, 1
/* 80138AA0 001339A0  7C 00 18 30 */	slw r0, r0, r3
/* 80138AA4 001339A4  80 64 00 04 */	lwz r3, 4(r4)
/* 80138AA8 001339A8  7C 63 00 38 */	and r3, r3, r0
/* 80138AAC 001339AC  4E 80 00 20 */	blr 

.global DBPrintf
DBPrintf:
/* 80138AB0 001339B0  94 21 FF 90 */	stwu r1, -0x70(r1)
/* 80138AB4 001339B4  40 86 00 24 */	bne cr1, lbl_80138AD8
/* 80138AB8 001339B8  D8 21 00 28 */	stfd f1, 0x28(r1)
/* 80138ABC 001339BC  D8 41 00 30 */	stfd f2, 0x30(r1)
/* 80138AC0 001339C0  D8 61 00 38 */	stfd f3, 0x38(r1)
/* 80138AC4 001339C4  D8 81 00 40 */	stfd f4, 0x40(r1)
/* 80138AC8 001339C8  D8 A1 00 48 */	stfd f5, 0x48(r1)
/* 80138ACC 001339CC  D8 C1 00 50 */	stfd f6, 0x50(r1)
/* 80138AD0 001339D0  D8 E1 00 58 */	stfd f7, 0x58(r1)
/* 80138AD4 001339D4  D9 01 00 60 */	stfd f8, 0x60(r1)
lbl_80138AD8:
/* 80138AD8 001339D8  90 61 00 08 */	stw r3, 8(r1)
/* 80138ADC 001339DC  90 81 00 0C */	stw r4, 0xc(r1)
/* 80138AE0 001339E0  90 A1 00 10 */	stw r5, 0x10(r1)
/* 80138AE4 001339E4  90 C1 00 14 */	stw r6, 0x14(r1)
/* 80138AE8 001339E8  90 E1 00 18 */	stw r7, 0x18(r1)
/* 80138AEC 001339EC  91 01 00 1C */	stw r8, 0x1c(r1)
/* 80138AF0 001339F0  91 21 00 20 */	stw r9, 0x20(r1)
/* 80138AF4 001339F4  91 41 00 24 */	stw r10, 0x24(r1)
/* 80138AF8 001339F8  38 21 00 70 */	addi r1, r1, 0x70
/* 80138AFC 001339FC  4E 80 00 20 */	blr 
