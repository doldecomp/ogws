.include "macros.inc"

.section .sbss, "wa"
.balign 0x8
.global IpcNumPendingReqs
IpcNumPendingReqs:
	.skip 0x4
.global IpcNumUnIssuedReqs
IpcNumUnIssuedReqs:
	.skip 0x4

.section .bss, "wa"
.balign 0x8
.global IpcFdArray
IpcFdArray:
	.skip 0x80
.global IpcReqPtrArray
IpcReqPtrArray:
	.skip 0x80

.section .text, "ax"
.global IPCiProfInit
IPCiProfInit:
/* 800E5C20 000E0B20  38 80 00 00 */	li r4, 0
/* 800E5C24 000E0B24  3C A0 80 41 */	lis r5, IpcReqPtrArray@ha
/* 800E5C28 000E0B28  3C C0 80 41 */	lis r6, IpcFdArray@ha
/* 800E5C2C 000E0B2C  38 00 00 02 */	li r0, 2
/* 800E5C30 000E0B30  90 8D 9B 68 */	stw r4, IpcNumPendingReqs-_SDA_BASE_(r13)
/* 800E5C34 000E0B34  38 A5 3F F0 */	addi r5, r5, IpcReqPtrArray@l
/* 800E5C38 000E0B38  38 C6 3F 70 */	addi r6, r6, IpcFdArray@l
/* 800E5C3C 000E0B3C  38 60 FF FF */	li r3, -1
/* 800E5C40 000E0B40  90 8D 9B 6C */	stw r4, IpcNumUnIssuedReqs-_SDA_BASE_(r13)
/* 800E5C44 000E0B44  7C 09 03 A6 */	mtctr r0
lbl_800E5C48:
/* 800E5C48 000E0B48  90 85 00 00 */	stw r4, 0(r5)
/* 800E5C4C 000E0B4C  90 66 00 00 */	stw r3, 0(r6)
/* 800E5C50 000E0B50  90 85 00 04 */	stw r4, 4(r5)
/* 800E5C54 000E0B54  90 66 00 04 */	stw r3, 4(r6)
/* 800E5C58 000E0B58  90 85 00 08 */	stw r4, 8(r5)
/* 800E5C5C 000E0B5C  90 66 00 08 */	stw r3, 8(r6)
/* 800E5C60 000E0B60  90 85 00 0C */	stw r4, 0xc(r5)
/* 800E5C64 000E0B64  90 66 00 0C */	stw r3, 0xc(r6)
/* 800E5C68 000E0B68  90 85 00 10 */	stw r4, 0x10(r5)
/* 800E5C6C 000E0B6C  90 66 00 10 */	stw r3, 0x10(r6)
/* 800E5C70 000E0B70  90 85 00 14 */	stw r4, 0x14(r5)
/* 800E5C74 000E0B74  90 66 00 14 */	stw r3, 0x14(r6)
/* 800E5C78 000E0B78  90 85 00 18 */	stw r4, 0x18(r5)
/* 800E5C7C 000E0B7C  90 66 00 18 */	stw r3, 0x18(r6)
/* 800E5C80 000E0B80  90 85 00 1C */	stw r4, 0x1c(r5)
/* 800E5C84 000E0B84  90 66 00 1C */	stw r3, 0x1c(r6)
/* 800E5C88 000E0B88  90 85 00 20 */	stw r4, 0x20(r5)
/* 800E5C8C 000E0B8C  90 66 00 20 */	stw r3, 0x20(r6)
/* 800E5C90 000E0B90  90 85 00 24 */	stw r4, 0x24(r5)
/* 800E5C94 000E0B94  90 66 00 24 */	stw r3, 0x24(r6)
/* 800E5C98 000E0B98  90 85 00 28 */	stw r4, 0x28(r5)
/* 800E5C9C 000E0B9C  90 66 00 28 */	stw r3, 0x28(r6)
/* 800E5CA0 000E0BA0  90 85 00 2C */	stw r4, 0x2c(r5)
/* 800E5CA4 000E0BA4  90 66 00 2C */	stw r3, 0x2c(r6)
/* 800E5CA8 000E0BA8  90 85 00 30 */	stw r4, 0x30(r5)
/* 800E5CAC 000E0BAC  90 66 00 30 */	stw r3, 0x30(r6)
/* 800E5CB0 000E0BB0  90 85 00 34 */	stw r4, 0x34(r5)
/* 800E5CB4 000E0BB4  90 66 00 34 */	stw r3, 0x34(r6)
/* 800E5CB8 000E0BB8  90 85 00 38 */	stw r4, 0x38(r5)
/* 800E5CBC 000E0BBC  90 66 00 38 */	stw r3, 0x38(r6)
/* 800E5CC0 000E0BC0  90 85 00 3C */	stw r4, 0x3c(r5)
/* 800E5CC4 000E0BC4  38 A5 00 40 */	addi r5, r5, 0x40
/* 800E5CC8 000E0BC8  90 66 00 3C */	stw r3, 0x3c(r6)
/* 800E5CCC 000E0BCC  38 C6 00 40 */	addi r6, r6, 0x40
/* 800E5CD0 000E0BD0  42 00 FF 78 */	bdnz lbl_800E5C48
/* 800E5CD4 000E0BD4  4E 80 00 20 */	blr 

.global IPCiProfQueueReq
IPCiProfQueueReq:
/* 800E5CD8 000E0BD8  80 CD 9B 68 */	lwz r6, IpcNumPendingReqs-_SDA_BASE_(r13)
/* 800E5CDC 000E0BDC  3D 00 80 41 */	lis r8, IpcReqPtrArray@ha
/* 800E5CE0 000E0BE0  80 AD 9B 6C */	lwz r5, IpcNumUnIssuedReqs-_SDA_BASE_(r13)
/* 800E5CE4 000E0BE4  3D 20 80 41 */	lis r9, IpcFdArray@ha
/* 800E5CE8 000E0BE8  38 C6 00 01 */	addi r6, r6, 1
/* 800E5CEC 000E0BEC  38 00 00 20 */	li r0, 0x20
/* 800E5CF0 000E0BF0  38 A5 00 01 */	addi r5, r5, 1
/* 800E5CF4 000E0BF4  90 CD 9B 68 */	stw r6, IpcNumPendingReqs-_SDA_BASE_(r13)
/* 800E5CF8 000E0BF8  39 08 3F F0 */	addi r8, r8, IpcReqPtrArray@l
/* 800E5CFC 000E0BFC  39 29 3F 70 */	addi r9, r9, IpcFdArray@l
/* 800E5D00 000E0C00  90 AD 9B 6C */	stw r5, IpcNumUnIssuedReqs-_SDA_BASE_(r13)
/* 800E5D04 000E0C04  38 E0 00 00 */	li r7, 0
/* 800E5D08 000E0C08  7C 09 03 A6 */	mtctr r0
lbl_800E5D0C:
/* 800E5D0C 000E0C0C  80 08 00 00 */	lwz r0, 0(r8)
/* 800E5D10 000E0C10  2C 00 00 00 */	cmpwi r0, 0
/* 800E5D14 000E0C14  40 82 00 30 */	bne lbl_800E5D44
/* 800E5D18 000E0C18  80 09 00 00 */	lwz r0, 0(r9)
/* 800E5D1C 000E0C1C  2C 00 FF FF */	cmpwi r0, -1
/* 800E5D20 000E0C20  40 82 00 24 */	bne lbl_800E5D44
/* 800E5D24 000E0C24  3C C0 80 41 */	lis r6, IpcReqPtrArray@ha
/* 800E5D28 000E0C28  3C A0 80 41 */	lis r5, IpcFdArray@ha
/* 800E5D2C 000E0C2C  54 E0 10 3A */	slwi r0, r7, 2
/* 800E5D30 000E0C30  38 C6 3F F0 */	addi r6, r6, IpcReqPtrArray@l
/* 800E5D34 000E0C34  38 A5 3F 70 */	addi r5, r5, IpcFdArray@l
/* 800E5D38 000E0C38  7C 66 01 2E */	stwx r3, r6, r0
/* 800E5D3C 000E0C3C  7C 85 01 2E */	stwx r4, r5, r0
/* 800E5D40 000E0C40  4E 80 00 20 */	blr 
lbl_800E5D44:
/* 800E5D44 000E0C44  39 08 00 04 */	addi r8, r8, 4
/* 800E5D48 000E0C48  39 29 00 04 */	addi r9, r9, 4
/* 800E5D4C 000E0C4C  38 E7 00 01 */	addi r7, r7, 1
/* 800E5D50 000E0C50  42 00 FF BC */	bdnz lbl_800E5D0C
/* 800E5D54 000E0C54  4E 80 00 20 */	blr 

.global IPCiProfAck
IPCiProfAck:
/* 800E5D58 000E0C58  80 6D 9B 6C */	lwz r3, IpcNumUnIssuedReqs-_SDA_BASE_(r13)
/* 800E5D5C 000E0C5C  38 03 FF FF */	addi r0, r3, -1
/* 800E5D60 000E0C60  90 0D 9B 6C */	stw r0, IpcNumUnIssuedReqs-_SDA_BASE_(r13)
/* 800E5D64 000E0C64  4E 80 00 20 */	blr 

.global IPCiProfReply
IPCiProfReply:
/* 800E5D68 000E0C68  80 AD 9B 68 */	lwz r5, IpcNumPendingReqs-_SDA_BASE_(r13)
/* 800E5D6C 000E0C6C  3C C0 80 41 */	lis r6, IpcReqPtrArray@ha
/* 800E5D70 000E0C70  3C E0 80 41 */	lis r7, IpcFdArray@ha
/* 800E5D74 000E0C74  38 00 00 20 */	li r0, 0x20
/* 800E5D78 000E0C78  38 A5 FF FF */	addi r5, r5, -1
/* 800E5D7C 000E0C7C  38 C6 3F F0 */	addi r6, r6, IpcReqPtrArray@l
/* 800E5D80 000E0C80  90 AD 9B 68 */	stw r5, IpcNumPendingReqs-_SDA_BASE_(r13)
/* 800E5D84 000E0C84  38 E7 3F 70 */	addi r7, r7, IpcFdArray@l
/* 800E5D88 000E0C88  38 A0 00 00 */	li r5, 0
/* 800E5D8C 000E0C8C  7C 09 03 A6 */	mtctr r0
lbl_800E5D90:
/* 800E5D90 000E0C90  80 06 00 00 */	lwz r0, 0(r6)
/* 800E5D94 000E0C94  7C 03 00 40 */	cmplw r3, r0
/* 800E5D98 000E0C98  40 82 00 38 */	bne lbl_800E5DD0
/* 800E5D9C 000E0C9C  80 07 00 00 */	lwz r0, 0(r7)
/* 800E5DA0 000E0CA0  7C 04 00 00 */	cmpw r4, r0
/* 800E5DA4 000E0CA4  40 82 00 2C */	bne lbl_800E5DD0
/* 800E5DA8 000E0CA8  3C 80 80 41 */	lis r4, IpcReqPtrArray@ha
/* 800E5DAC 000E0CAC  3C 60 80 41 */	lis r3, IpcFdArray@ha
/* 800E5DB0 000E0CB0  54 A6 10 3A */	slwi r6, r5, 2
/* 800E5DB4 000E0CB4  38 A0 00 00 */	li r5, 0
/* 800E5DB8 000E0CB8  38 84 3F F0 */	addi r4, r4, IpcReqPtrArray@l
/* 800E5DBC 000E0CBC  38 63 3F 70 */	addi r3, r3, IpcFdArray@l
/* 800E5DC0 000E0CC0  38 00 FF FF */	li r0, -1
/* 800E5DC4 000E0CC4  7C A4 31 2E */	stwx r5, r4, r6
/* 800E5DC8 000E0CC8  7C 03 31 2E */	stwx r0, r3, r6
/* 800E5DCC 000E0CCC  4E 80 00 20 */	blr 
lbl_800E5DD0:
/* 800E5DD0 000E0CD0  38 C6 00 04 */	addi r6, r6, 4
/* 800E5DD4 000E0CD4  38 E7 00 04 */	addi r7, r7, 4
/* 800E5DD8 000E0CD8  38 A5 00 01 */	addi r5, r5, 1
/* 800E5DDC 000E0CDC  42 00 FF B4 */	bdnz lbl_800E5D90
/* 800E5DE0 000E0CE0  4E 80 00 20 */	blr 
