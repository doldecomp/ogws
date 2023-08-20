.include "macros.inc"

.section .sbss, "wa"
.balign 0x8
.global sInstance__16RPSysQueuedScene
sInstance__16RPSysQueuedScene:
	.skip 0x4

.section .data, "wa"
.balign 0x8
.global __vt__16RPSysQueuedScene
__vt__16RPSysQueuedScene:
	.long 0
    .long 0
    .long __dt__16RPSysQueuedSceneFv

.section .text, "ax"
.global __dt__16RPSysQueuedSceneFv
__dt__16RPSysQueuedSceneFv:
/* 80187B54 00182A54  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80187B58 00182A58  7C 08 02 A6 */	mflr r0
/* 80187B5C 00182A5C  2C 03 00 00 */	cmpwi r3, 0
/* 80187B60 00182A60  90 01 00 14 */	stw r0, 0x14(r1)
/* 80187B64 00182A64  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80187B68 00182A68  7C 7F 1B 78 */	mr r31, r3
/* 80187B6C 00182A6C  41 82 00 10 */	beq lbl_80187B7C
/* 80187B70 00182A70  2C 04 00 00 */	cmpwi r4, 0
/* 80187B74 00182A74  40 81 00 08 */	ble lbl_80187B7C
/* 80187B78 00182A78  4B F1 B7 0D */	bl __dl__FPv
lbl_80187B7C:
/* 80187B7C 00182A7C  7F E3 FB 78 */	mr r3, r31
/* 80187B80 00182A80  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80187B84 00182A84  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80187B88 00182A88  7C 08 03 A6 */	mtlr r0
/* 80187B8C 00182A8C  38 21 00 10 */	addi r1, r1, 0x10
/* 80187B90 00182A90  4E 80 00 20 */	blr 

.global reset__16RPSysQueuedSceneFv
reset__16RPSysQueuedSceneFv:
/* 80187B94 00182A94  38 00 FF FF */	li r0, -1
/* 80187B98 00182A98  90 03 00 08 */	stw r0, 8(r3)
/* 80187B9C 00182A9C  4E 80 00 20 */	blr 

.global CreateInstance__16RPSysQueuedSceneFPQ23EGG4Heap
CreateInstance__16RPSysQueuedSceneFPQ23EGG4Heap:
/* 80187BA0 00182AA0  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80187BA4 00182AA4  7C 08 02 A6 */	mflr r0
/* 80187BA8 00182AA8  90 01 00 14 */	stw r0, 0x14(r1)
/* 80187BAC 00182AAC  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80187BB0 00182AB0  7C 7F 1B 78 */	mr r31, r3
/* 80187BB4 00182AB4  80 0D A1 78 */	lwz r0, sInstance__16RPSysQueuedScene-_SDA_BASE_(r13)
/* 80187BB8 00182AB8  2C 00 00 00 */	cmpwi r0, 0
/* 80187BBC 00182ABC  40 82 00 3C */	bne lbl_80187BF8
/* 80187BC0 00182AC0  7F E4 FB 78 */	mr r4, r31
/* 80187BC4 00182AC4  38 60 00 0C */	li r3, 0xc
/* 80187BC8 00182AC8  38 A0 00 04 */	li r5, 4
/* 80187BCC 00182ACC  4B F1 B6 85 */	bl __nw__FUlPQ23EGG4Heapi
/* 80187BD0 00182AD0  2C 03 00 00 */	cmpwi r3, 0
/* 80187BD4 00182AD4  41 82 00 1C */	beq lbl_80187BF0
/* 80187BD8 00182AD8  3C 80 80 3C */	lis r4, __vt__16RPSysQueuedScene@ha
/* 80187BDC 00182ADC  38 00 FF FF */	li r0, -1
/* 80187BE0 00182AE0  38 84 98 70 */	addi r4, r4, __vt__16RPSysQueuedScene@l
/* 80187BE4 00182AE4  90 83 00 00 */	stw r4, 0(r3)
/* 80187BE8 00182AE8  93 E3 00 04 */	stw r31, 4(r3)
/* 80187BEC 00182AEC  90 03 00 08 */	stw r0, 8(r3)
lbl_80187BF0:
/* 80187BF0 00182AF0  90 6D A1 78 */	stw r3, sInstance__16RPSysQueuedScene-_SDA_BASE_(r13)
/* 80187BF4 00182AF4  48 00 00 08 */	b lbl_80187BFC
lbl_80187BF8:
/* 80187BF8 00182AF8  38 60 00 00 */	li r3, 0
lbl_80187BFC:
/* 80187BFC 00182AFC  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80187C00 00182B00  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80187C04 00182B04  7C 08 03 A6 */	mtlr r0
/* 80187C08 00182B08  38 21 00 10 */	addi r1, r1, 0x10
/* 80187C0C 00182B0C  4E 80 00 20 */	blr 
