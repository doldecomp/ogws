.include "macros.inc"

.section .data, "wa"
.balign 0x8
.global lbl_803B7F00
lbl_803B7F00:
	.incbin "baserom.dol", 0x3B4000, 0x18
.global lbl_803B7F18
lbl_803B7F18:
	.incbin "baserom.dol", 0x3B4018, 0x14
.global lbl_803B7F2C
lbl_803B7F2C:
	.incbin "baserom.dol", 0x3B402C, 0x1C

.section .sdata, "wa"
.balign 0x8
nwc24ShtFd:
	.long -1

.section .sbss, "wa"
.balign 0x8
nwc24ShtRetryRest:
	.skip 0x4
shuttingdown$2076:
	.skip 0x4
result$2077:
	.skip 0x4

.section .bss, "wa"
.balign 0x8
ShutdownFuncInfo:
	.skip 0x10
.balign 32
shtBuffer$2046: # ALIGN(32)
	.skip 0x20
.balign 32
shtResult$2047: # ALIGN(32)
	.skip 0x20

.section .text, "ax"
.global NWC24iPrepareShutdown
NWC24iPrepareShutdown:
/* 8014ACCC 00145BCC  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8014ACD0 00145BD0  7C 08 02 A6 */	mflr r0
/* 8014ACD4 00145BD4  90 01 00 24 */	stw r0, 0x24(r1)
/* 8014ACD8 00145BD8  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8014ACDC 00145BDC  3B E0 00 00 */	li r31, 0
/* 8014ACE0 00145BE0  4B FF 99 11 */	bl NWC24iRegister
/* 8014ACE4 00145BE4  3C A0 80 15 */	lis r5, NWC24Shutdown@ha
/* 8014ACE8 00145BE8  3C 80 80 48 */	lis r4, ShutdownFuncInfo@ha
/* 8014ACEC 00145BEC  38 A5 AD 74 */	addi r5, r5, NWC24Shutdown@l
/* 8014ACF0 00145BF0  38 00 00 6E */	li r0, 0x6e
/* 8014ACF4 00145BF4  38 64 A8 C0 */	addi r3, r4, ShutdownFuncInfo@l
/* 8014ACF8 00145BF8  90 A4 A8 C0 */	stw r5, -0x5740(r4)
/* 8014ACFC 00145BFC  90 03 00 04 */	stw r0, 4(r3)
/* 8014AD00 00145C00  4B FA 81 49 */	bl OSRegisterShutdownFunction
/* 8014AD04 00145C04  80 0D 87 70 */	lwz r0, nwc24ShtFd-_SDA_BASE_(r13)
/* 8014AD08 00145C08  2C 00 00 00 */	cmpwi r0, 0
/* 8014AD0C 00145C0C  40 80 00 24 */	bge lbl_8014AD30
/* 8014AD10 00145C10  3C 60 80 3B */	lis r3, lbl_803B7F00@ha
/* 8014AD14 00145C14  3C 80 80 3B */	lis r4, lbl_803B7F18@ha
/* 8014AD18 00145C18  38 63 7F 00 */	addi r3, r3, lbl_803B7F00@l
/* 8014AD1C 00145C1C  38 AD 87 70 */	addi r5, r13, nwc24ShtFd-_SDA_BASE_
/* 8014AD20 00145C20  38 84 7F 18 */	addi r4, r4, lbl_803B7F18@l
/* 8014AD24 00145C24  38 C0 00 01 */	li r6, 1
/* 8014AD28 00145C28  4B FF F9 05 */	bl NWC24iOpenResourceManager
/* 8014AD2C 00145C2C  7C 7F 1B 78 */	mr r31, r3
lbl_8014AD30:
/* 8014AD30 00145C30  38 00 00 05 */	li r0, 5
/* 8014AD34 00145C34  90 0D A0 E8 */	stw r0, nwc24ShtRetryRest-_SDA_BASE_(r13)
lbl_8014AD38:
/* 8014AD38 00145C38  4B FA C3 6D */	bl SCCheckStatus
/* 8014AD3C 00145C3C  28 03 00 02 */	cmplwi r3, 2
/* 8014AD40 00145C40  41 82 00 1C */	beq lbl_8014AD5C
/* 8014AD44 00145C44  28 03 00 01 */	cmplwi r3, 1
/* 8014AD48 00145C48  41 82 FF F0 */	beq lbl_8014AD38
/* 8014AD4C 00145C4C  38 61 00 08 */	addi r3, r1, 8
/* 8014AD50 00145C50  4B FA DD 35 */	bl SCGetIdleMode
/* 8014AD54 00145C54  88 61 00 09 */	lbz r3, 9(r1)
/* 8014AD58 00145C58  4B FA B6 31 */	bl __OSSetIdleLEDMode
lbl_8014AD5C:
/* 8014AD5C 00145C5C  7F E3 FB 78 */	mr r3, r31
/* 8014AD60 00145C60  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8014AD64 00145C64  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8014AD68 00145C68  7C 08 03 A6 */	mtlr r0
/* 8014AD6C 00145C6C  38 21 00 20 */	addi r1, r1, 0x20
/* 8014AD70 00145C70  4E 80 00 20 */	blr 

.global NWC24Shutdown
NWC24Shutdown:
/* 8014AD74 00145C74  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8014AD78 00145C78  7C 08 02 A6 */	mflr r0
/* 8014AD7C 00145C7C  2C 03 00 00 */	cmpwi r3, 0
/* 8014AD80 00145C80  90 01 00 14 */	stw r0, 0x14(r1)
/* 8014AD84 00145C84  41 82 00 0C */	beq lbl_8014AD90
/* 8014AD88 00145C88  38 60 00 01 */	li r3, 1
/* 8014AD8C 00145C8C  48 00 00 A8 */	b lbl_8014AE34
lbl_8014AD90:
/* 8014AD90 00145C90  80 0D A0 EC */	lwz r0, shuttingdown$2076-_SDA_BASE_(r13)
/* 8014AD94 00145C94  2C 00 00 00 */	cmpwi r0, 0
/* 8014AD98 00145C98  41 82 00 54 */	beq lbl_8014ADEC
/* 8014AD9C 00145C9C  4B FF F9 E1 */	bl NWC24iIsAsyncRequestPending
/* 8014ADA0 00145CA0  2C 03 00 00 */	cmpwi r3, 0
/* 8014ADA4 00145CA4  41 82 00 0C */	beq lbl_8014ADB0
/* 8014ADA8 00145CA8  38 60 00 00 */	li r3, 0
/* 8014ADAC 00145CAC  48 00 00 88 */	b lbl_8014AE34
lbl_8014ADB0:
/* 8014ADB0 00145CB0  80 0D A0 F0 */	lwz r0, result$2077-_SDA_BASE_(r13)
/* 8014ADB4 00145CB4  2C 00 00 00 */	cmpwi r0, 0
/* 8014ADB8 00145CB8  41 80 00 0C */	blt lbl_8014ADC4
/* 8014ADBC 00145CBC  38 60 00 01 */	li r3, 1
/* 8014ADC0 00145CC0  48 00 00 74 */	b lbl_8014AE34
lbl_8014ADC4:
/* 8014ADC4 00145CC4  80 6D A0 E8 */	lwz r3, nwc24ShtRetryRest-_SDA_BASE_(r13)
/* 8014ADC8 00145CC8  2C 03 00 00 */	cmpwi r3, 0
/* 8014ADCC 00145CCC  40 81 00 18 */	ble lbl_8014ADE4
/* 8014ADD0 00145CD0  38 03 FF FF */	addi r0, r3, -1
/* 8014ADD4 00145CD4  38 60 00 00 */	li r3, 0
/* 8014ADD8 00145CD8  90 6D A0 EC */	stw r3, shuttingdown$2076-_SDA_BASE_(r13)
/* 8014ADDC 00145CDC  90 0D A0 E8 */	stw r0, nwc24ShtRetryRest-_SDA_BASE_(r13)
/* 8014ADE0 00145CE0  48 00 00 50 */	b lbl_8014AE30
lbl_8014ADE4:
/* 8014ADE4 00145CE4  38 60 00 01 */	li r3, 1
/* 8014ADE8 00145CE8  48 00 00 4C */	b lbl_8014AE34
lbl_8014ADEC:
/* 8014ADEC 00145CEC  3C A0 80 48 */	lis r5, shtBuffer$2046@ha
/* 8014ADF0 00145CF0  3C 60 80 3B */	lis r3, lbl_803B7F2C@ha
/* 8014ADF4 00145CF4  90 85 A8 E0 */	stw r4, shtBuffer$2046@l(r5)
/* 8014ADF8 00145CF8  3D 00 80 48 */	lis r8, shtResult$2047@ha
/* 8014ADFC 00145CFC  38 C5 A8 E0 */	addi r6, r5, -22304
/* 8014AE00 00145D00  80 8D 87 70 */	lwz r4, nwc24ShtFd-_SDA_BASE_(r13)
/* 8014AE04 00145D04  38 63 7F 2C */	addi r3, r3, lbl_803B7F2C@l
/* 8014AE08 00145D08  39 08 A9 00 */	addi r8, r8, shtResult$2047@l
/* 8014AE0C 00145D0C  38 A0 00 28 */	li r5, 0x28
/* 8014AE10 00145D10  38 E0 00 20 */	li r7, 0x20
/* 8014AE14 00145D14  39 20 00 20 */	li r9, 0x20
/* 8014AE18 00145D18  39 4D A0 F0 */	addi r10, r13, result$2077-_SDA_BASE_
/* 8014AE1C 00145D1C  4B FF F9 05 */	bl NWC24iIoctlResourceManagerAsync
/* 8014AE20 00145D20  2C 03 00 00 */	cmpwi r3, 0
/* 8014AE24 00145D24  41 80 00 0C */	blt lbl_8014AE30
/* 8014AE28 00145D28  38 00 00 01 */	li r0, 1
/* 8014AE2C 00145D2C  90 0D A0 EC */	stw r0, shuttingdown$2076-_SDA_BASE_(r13)
lbl_8014AE30:
/* 8014AE30 00145D30  38 60 00 00 */	li r3, 0
lbl_8014AE34:
/* 8014AE34 00145D34  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8014AE38 00145D38  7C 08 03 A6 */	mtlr r0
/* 8014AE3C 00145D3C  38 21 00 10 */	addi r1, r1, 0x10
/* 8014AE40 00145D40  4E 80 00 20 */	blr 
