.include "macros.inc"

.section .rodata, "a"
.balign 0x8
EndofProgramInstruction$159:
	.incbin "baserom.dol", 0x378468, 0x4
$$2162:
	.incbin "baserom.dol", 0x37846C, 0x104

.section .data, "wa"
.balign 0x8
.global gDBCommTable
gDBCommTable:
	.incbin "baserom.dol", 0x3954F0, 0x28

.section .bss, "wa"
.balign 0x8
.global TRK_Use_BBA
TRK_Use_BBA:
	.skip 0x8

.section .text, "ax"
.global TRKLoadContext
TRKLoadContext:
/* 800C5D38 000C0C38  80 03 00 00 */	lwz r0, 0(r3)
/* 800C5D3C 000C0C3C  80 23 00 04 */	lwz r1, 4(r3)
/* 800C5D40 000C0C40  80 43 00 08 */	lwz r2, 8(r3)
/* 800C5D44 000C0C44  A0 A3 01 A2 */	lhz r5, 0x1a2(r3)
/* 800C5D48 000C0C48  54 A6 07 BD */	rlwinm. r6, r5, 0, 0x1e, 0x1e
/* 800C5D4C 000C0C4C  41 82 00 14 */	beq lbl_800C5D60
/* 800C5D50 000C0C50  54 A5 07 FA */	rlwinm r5, r5, 0, 0x1f, 0x1d
/* 800C5D54 000C0C54  B0 A3 01 A2 */	sth r5, 0x1a2(r3)
/* 800C5D58 000C0C58  B8 A3 00 14 */	lmw r5, 0x14(r3)
/* 800C5D5C 000C0C5C  48 00 00 08 */	b lbl_800C5D64
lbl_800C5D60:
/* 800C5D60 000C0C60  B9 A3 00 34 */	lmw r13, 0x34(r3)
lbl_800C5D64:
/* 800C5D64 000C0C64  7C 7F 1B 78 */	mr r31, r3
/* 800C5D68 000C0C68  7C 83 23 78 */	mr r3, r4
/* 800C5D6C 000C0C6C  80 9F 00 80 */	lwz r4, 0x80(r31)
/* 800C5D70 000C0C70  7C 8F F1 20 */	mtcrf 0xff, r4
/* 800C5D74 000C0C74  80 9F 00 84 */	lwz r4, 0x84(r31)
/* 800C5D78 000C0C78  7C 88 03 A6 */	mtlr r4
/* 800C5D7C 000C0C7C  80 9F 00 88 */	lwz r4, 0x88(r31)
/* 800C5D80 000C0C80  7C 89 03 A6 */	mtctr r4
/* 800C5D84 000C0C84  80 9F 00 8C */	lwz r4, 0x8c(r31)
/* 800C5D88 000C0C88  7C 81 03 A6 */	mtxer r4
/* 800C5D8C 000C0C8C  7C 80 00 A6 */	mfmsr r4
/* 800C5D90 000C0C90  54 84 04 5E */	rlwinm r4, r4, 0, 0x11, 0xf
/* 800C5D94 000C0C94  54 84 07 FA */	rlwinm r4, r4, 0, 0x1f, 0x1d
/* 800C5D98 000C0C98  7C 80 01 24 */	mtmsr r4
/* 800C5D9C 000C0C9C  7C 51 43 A6 */	mtspr 0x111, r2
/* 800C5DA0 000C0CA0  80 9F 00 0C */	lwz r4, 0xc(r31)
/* 800C5DA4 000C0CA4  7C 92 43 A6 */	mtspr 0x112, r4
/* 800C5DA8 000C0CA8  80 9F 00 10 */	lwz r4, 0x10(r31)
/* 800C5DAC 000C0CAC  7C 93 43 A6 */	mtspr 0x113, r4
/* 800C5DB0 000C0CB0  80 5F 01 98 */	lwz r2, 0x198(r31)
/* 800C5DB4 000C0CB4  80 9F 01 9C */	lwz r4, 0x19c(r31)
/* 800C5DB8 000C0CB8  83 FF 00 7C */	lwz r31, 0x7c(r31)
/* 800C5DBC 000C0CBC  4B FF DD 3C */	b TRKInterruptHandler

.global TRKUARTInterruptHandler
TRKUARTInterruptHandler:
/* 800C5DC0 000C0CC0  4E 80 00 20 */	blr 

.global InitializeProgramEndTrap
InitializeProgramEndTrap:
/* 800C5DC4 000C0CC4  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800C5DC8 000C0CC8  7C 08 02 A6 */	mflr r0
/* 800C5DCC 000C0CCC  3C 80 80 11 */	lis r4, PPCHalt@ha
/* 800C5DD0 000C0CD0  3C 60 80 38 */	lis r3, EndofProgramInstruction$159@ha
/* 800C5DD4 000C0CD4  90 01 00 14 */	stw r0, 0x14(r1)
/* 800C5DD8 000C0CD8  38 A0 00 04 */	li r5, 4
/* 800C5DDC 000C0CDC  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800C5DE0 000C0CE0  3B E4 AA 58 */	addi r31, r4, PPCHalt@l
/* 800C5DE4 000C0CE4  38 83 C3 68 */	addi r4, r3, EndofProgramInstruction$159@l
/* 800C5DE8 000C0CE8  38 7F 00 04 */	addi r3, r31, 4
/* 800C5DEC 000C0CEC  4B F3 E3 79 */	bl TRK_memcpy
/* 800C5DF0 000C0CF0  38 7F 00 04 */	addi r3, r31, 4
/* 800C5DF4 000C0CF4  38 80 00 04 */	li r4, 4
/* 800C5DF8 000C0CF8  48 02 84 1D */	bl ICInvalidateRange
/* 800C5DFC 000C0CFC  38 7F 00 04 */	addi r3, r31, 4
/* 800C5E00 000C0D00  38 80 00 04 */	li r4, 4
/* 800C5E04 000C0D04  48 02 83 2D */	bl DCFlushRange
/* 800C5E08 000C0D08  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800C5E0C 000C0D0C  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 800C5E10 000C0D10  7C 08 03 A6 */	mtlr r0
/* 800C5E14 000C0D14  38 21 00 10 */	addi r1, r1, 0x10
/* 800C5E18 000C0D18  4E 80 00 20 */	blr 

.global TRK_board_display
TRK_board_display:
/* 800C5E1C 000C0D1C  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800C5E20 000C0D20  7C 08 02 A6 */	mflr r0
/* 800C5E24 000C0D24  3C A0 80 38 */	lis r5, $$2162@ha
/* 800C5E28 000C0D28  7C 64 1B 78 */	mr r4, r3
/* 800C5E2C 000C0D2C  90 01 00 14 */	stw r0, 0x14(r1)
/* 800C5E30 000C0D30  38 65 C3 6C */	addi r3, r5, $$2162@l
/* 800C5E34 000C0D34  4C C6 31 82 */	crclr 6
/* 800C5E38 000C0D38  48 0B E0 E1 */	bl OSReport
/* 800C5E3C 000C0D3C  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800C5E40 000C0D40  7C 08 03 A6 */	mtlr r0
/* 800C5E44 000C0D44  38 21 00 10 */	addi r1, r1, 0x10
/* 800C5E48 000C0D48  4E 80 00 20 */	blr 

.global UnreserveEXI2Port
UnreserveEXI2Port:
/* 800C5E4C 000C0D4C  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800C5E50 000C0D50  7C 08 02 A6 */	mflr r0
/* 800C5E54 000C0D54  3C 60 80 3A */	lis r3, gDBCommTable@ha
/* 800C5E58 000C0D58  90 01 00 14 */	stw r0, 0x14(r1)
/* 800C5E5C 000C0D5C  38 63 93 F0 */	addi r3, r3, gDBCommTable@l
/* 800C5E60 000C0D60  81 83 00 20 */	lwz r12, 0x20(r3)
/* 800C5E64 000C0D64  7D 89 03 A6 */	mtctr r12
/* 800C5E68 000C0D68  4E 80 04 21 */	bctrl 
/* 800C5E6C 000C0D6C  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800C5E70 000C0D70  7C 08 03 A6 */	mtlr r0
/* 800C5E74 000C0D74  38 21 00 10 */	addi r1, r1, 0x10
/* 800C5E78 000C0D78  4E 80 00 20 */	blr 

.global ReserveEXI2Port
ReserveEXI2Port:
/* 800C5E7C 000C0D7C  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800C5E80 000C0D80  7C 08 02 A6 */	mflr r0
/* 800C5E84 000C0D84  3C 60 80 3A */	lis r3, gDBCommTable@ha
/* 800C5E88 000C0D88  90 01 00 14 */	stw r0, 0x14(r1)
/* 800C5E8C 000C0D8C  38 63 93 F0 */	addi r3, r3, gDBCommTable@l
/* 800C5E90 000C0D90  81 83 00 24 */	lwz r12, 0x24(r3)
/* 800C5E94 000C0D94  7D 89 03 A6 */	mtctr r12
/* 800C5E98 000C0D98  4E 80 04 21 */	bctrl 
/* 800C5E9C 000C0D9C  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800C5EA0 000C0DA0  7C 08 03 A6 */	mtlr r0
/* 800C5EA4 000C0DA4  38 21 00 10 */	addi r1, r1, 0x10
/* 800C5EA8 000C0DA8  4E 80 00 20 */	blr 

.global TRKWriteUARTN
TRKWriteUARTN:
/* 800C5EAC 000C0DAC  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800C5EB0 000C0DB0  7C 08 02 A6 */	mflr r0
/* 800C5EB4 000C0DB4  3C A0 80 3A */	lis r5, gDBCommTable@ha
/* 800C5EB8 000C0DB8  90 01 00 14 */	stw r0, 0x14(r1)
/* 800C5EBC 000C0DBC  38 A5 93 F0 */	addi r5, r5, gDBCommTable@l
/* 800C5EC0 000C0DC0  81 85 00 14 */	lwz r12, 0x14(r5)
/* 800C5EC4 000C0DC4  7D 89 03 A6 */	mtctr r12
/* 800C5EC8 000C0DC8  4E 80 04 21 */	bctrl 
/* 800C5ECC 000C0DCC  7C 03 00 D0 */	neg r0, r3
/* 800C5ED0 000C0DD0  7C 00 1B 78 */	or r0, r0, r3
/* 800C5ED4 000C0DD4  7C 03 FE 70 */	srawi r3, r0, 0x1f
/* 800C5ED8 000C0DD8  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800C5EDC 000C0DDC  7C 08 03 A6 */	mtlr r0
/* 800C5EE0 000C0DE0  38 21 00 10 */	addi r1, r1, 0x10
/* 800C5EE4 000C0DE4  4E 80 00 20 */	blr 

.global TRKReadUARTN
TRKReadUARTN:
/* 800C5EE8 000C0DE8  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800C5EEC 000C0DEC  7C 08 02 A6 */	mflr r0
/* 800C5EF0 000C0DF0  3C A0 80 3A */	lis r5, gDBCommTable@ha
/* 800C5EF4 000C0DF4  90 01 00 14 */	stw r0, 0x14(r1)
/* 800C5EF8 000C0DF8  38 A5 93 F0 */	addi r5, r5, gDBCommTable@l
/* 800C5EFC 000C0DFC  81 85 00 10 */	lwz r12, 0x10(r5)
/* 800C5F00 000C0E00  7D 89 03 A6 */	mtctr r12
/* 800C5F04 000C0E04  4E 80 04 21 */	bctrl 
/* 800C5F08 000C0E08  7C 03 00 D0 */	neg r0, r3
/* 800C5F0C 000C0E0C  7C 00 1B 78 */	or r0, r0, r3
/* 800C5F10 000C0E10  7C 03 FE 70 */	srawi r3, r0, 0x1f
/* 800C5F14 000C0E14  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800C5F18 000C0E18  7C 08 03 A6 */	mtlr r0
/* 800C5F1C 000C0E1C  38 21 00 10 */	addi r1, r1, 0x10
/* 800C5F20 000C0E20  4E 80 00 20 */	blr 

.global TRKPollUART
TRKPollUART:
/* 800C5F24 000C0E24  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800C5F28 000C0E28  7C 08 02 A6 */	mflr r0
/* 800C5F2C 000C0E2C  3C 60 80 3A */	lis r3, gDBCommTable@ha
/* 800C5F30 000C0E30  90 01 00 14 */	stw r0, 0x14(r1)
/* 800C5F34 000C0E34  38 63 93 F0 */	addi r3, r3, gDBCommTable@l
/* 800C5F38 000C0E38  81 83 00 0C */	lwz r12, 0xc(r3)
/* 800C5F3C 000C0E3C  7D 89 03 A6 */	mtctr r12
/* 800C5F40 000C0E40  4E 80 04 21 */	bctrl 
/* 800C5F44 000C0E44  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800C5F48 000C0E48  7C 08 03 A6 */	mtlr r0
/* 800C5F4C 000C0E4C  38 21 00 10 */	addi r1, r1, 0x10
/* 800C5F50 000C0E50  4E 80 00 20 */	blr 

.global EnableEXI2Interrupts
EnableEXI2Interrupts:
/* 800C5F54 000C0E54  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800C5F58 000C0E58  7C 08 02 A6 */	mflr r0
/* 800C5F5C 000C0E5C  3C 60 80 41 */	lis r3, TRK_Use_BBA@ha
/* 800C5F60 000C0E60  90 01 00 14 */	stw r0, 0x14(r1)
/* 800C5F64 000C0E64  88 03 DC 28 */	lbz r0, TRK_Use_BBA@l(r3)
/* 800C5F68 000C0E68  28 00 00 00 */	cmplwi r0, 0
/* 800C5F6C 000C0E6C  40 82 00 20 */	bne lbl_800C5F8C
/* 800C5F70 000C0E70  3C 60 80 3A */	lis r3, gDBCommTable@ha
/* 800C5F74 000C0E74  38 63 93 F0 */	addi r3, r3, gDBCommTable@l
/* 800C5F78 000C0E78  81 83 00 04 */	lwz r12, 4(r3)
/* 800C5F7C 000C0E7C  28 0C 00 00 */	cmplwi r12, 0
/* 800C5F80 000C0E80  41 82 00 0C */	beq lbl_800C5F8C
/* 800C5F84 000C0E84  7D 89 03 A6 */	mtctr r12
/* 800C5F88 000C0E88  4E 80 04 21 */	bctrl 
lbl_800C5F8C:
/* 800C5F8C 000C0E8C  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800C5F90 000C0E90  7C 08 03 A6 */	mtlr r0
/* 800C5F94 000C0E94  38 21 00 10 */	addi r1, r1, 0x10
/* 800C5F98 000C0E98  4E 80 00 20 */	blr 

.global TRKInitializeIntDrivenUART
TRKInitializeIntDrivenUART:
/* 800C5F9C 000C0E9C  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800C5FA0 000C0EA0  7C 08 02 A6 */	mflr r0
/* 800C5FA4 000C0EA4  3C 80 80 0C */	lis r4, TRKEXICallBack@ha
/* 800C5FA8 000C0EA8  3C 60 80 3A */	lis r3, gDBCommTable@ha
/* 800C5FAC 000C0EAC  90 01 00 14 */	stw r0, 0x14(r1)
/* 800C5FB0 000C0EB0  38 84 61 C0 */	addi r4, r4, TRKEXICallBack@l
/* 800C5FB4 000C0EB4  81 83 93 F0 */	lwz r12, gDBCommTable@l(r3)
/* 800C5FB8 000C0EB8  7C C3 33 78 */	mr r3, r6
/* 800C5FBC 000C0EBC  7D 89 03 A6 */	mtctr r12
/* 800C5FC0 000C0EC0  4E 80 04 21 */	bctrl 
/* 800C5FC4 000C0EC4  3C 60 80 3A */	lis r3, gDBCommTable@ha
/* 800C5FC8 000C0EC8  38 63 93 F0 */	addi r3, r3, gDBCommTable@l
/* 800C5FCC 000C0ECC  81 83 00 18 */	lwz r12, 0x18(r3)
/* 800C5FD0 000C0ED0  7D 89 03 A6 */	mtctr r12
/* 800C5FD4 000C0ED4  4E 80 04 21 */	bctrl 
/* 800C5FD8 000C0ED8  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800C5FDC 000C0EDC  38 60 00 00 */	li r3, 0
/* 800C5FE0 000C0EE0  7C 08 03 A6 */	mtlr r0
/* 800C5FE4 000C0EE4  38 21 00 10 */	addi r1, r1, 0x10
/* 800C5FE8 000C0EE8  4E 80 00 20 */	blr 

.global InitMetroTRKCommTable
InitMetroTRKCommTable:
/* 800C5FEC 000C0EEC  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800C5FF0 000C0EF0  7C 08 02 A6 */	mflr r0
/* 800C5FF4 000C0EF4  3C 80 80 38 */	lis r4, EndofProgramInstruction$159@ha
/* 800C5FF8 000C0EF8  90 01 00 24 */	stw r0, 0x24(r1)
/* 800C5FFC 000C0EFC  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800C6000 000C0F00  93 C1 00 18 */	stw r30, 0x18(r1)
/* 800C6004 000C0F04  7C 7E 1B 78 */	mr r30, r3
/* 800C6008 000C0F08  93 A1 00 14 */	stw r29, 0x14(r1)
/* 800C600C 000C0F0C  3B A4 C3 68 */	addi r29, r4, EndofProgramInstruction$159@l
/* 800C6010 000C0F10  7F C4 F3 78 */	mr r4, r30
/* 800C6014 000C0F14  38 7D 00 08 */	addi r3, r29, 8
/* 800C6018 000C0F18  4C C6 31 82 */	crclr 6
/* 800C601C 000C0F1C  48 0B DE FD */	bl OSReport
/* 800C6020 000C0F20  38 7D 00 20 */	addi r3, r29, 0x20
/* 800C6024 000C0F24  38 80 00 40 */	li r4, 0x40
/* 800C6028 000C0F28  4C C6 31 82 */	crclr 6
/* 800C602C 000C0F2C  48 0B DE ED */	bl OSReport
/* 800C6030 000C0F30  3C 60 80 41 */	lis r3, TRK_Use_BBA@ha
/* 800C6034 000C0F34  38 00 00 00 */	li r0, 0
/* 800C6038 000C0F38  2C 1E 00 02 */	cmpwi r30, 2
/* 800C603C 000C0F3C  98 03 DC 28 */	stb r0, TRK_Use_BBA@l(r3)
/* 800C6040 000C0F40  40 82 00 A0 */	bne lbl_800C60E0
/* 800C6044 000C0F44  38 7D 00 48 */	addi r3, r29, 0x48
/* 800C6048 000C0F48  4C C6 31 82 */	crclr 6
/* 800C604C 000C0F4C  48 0B DE CD */	bl OSReport
/* 800C6050 000C0F50  3D 80 80 0C */	lis r12, udp_cc_initialize@ha
/* 800C6054 000C0F54  3D 60 80 3A */	lis r11, gDBCommTable@ha
/* 800C6058 000C0F58  3B EC 62 88 */	addi r31, r12, udp_cc_initialize@l
/* 800C605C 000C0F5C  3D 40 80 0C */	lis r10, udp_cc_open@ha
/* 800C6060 000C0F60  39 8B 93 F0 */	addi r12, r11, gDBCommTable@l
/* 800C6064 000C0F64  38 00 00 00 */	li r0, 0
/* 800C6068 000C0F68  39 6A 62 78 */	addi r11, r10, udp_cc_open@l
/* 800C606C 000C0F6C  3D 20 80 0C */	lis r9, udp_cc_close@ha
/* 800C6070 000C0F70  39 49 62 70 */	addi r10, r9, udp_cc_close@l
/* 800C6074 000C0F74  3D 00 80 0C */	lis r8, udp_cc_read@ha
/* 800C6078 000C0F78  39 28 62 68 */	addi r9, r8, udp_cc_read@l
/* 800C607C 000C0F7C  3C E0 80 0C */	lis r7, udp_cc_write@ha
/* 800C6080 000C0F80  39 07 62 60 */	addi r8, r7, udp_cc_write@l
/* 800C6084 000C0F84  3C C0 80 0C */	lis r6, udp_cc_shutdown@ha
/* 800C6088 000C0F88  38 E6 62 80 */	addi r7, r6, udp_cc_shutdown@l
/* 800C608C 000C0F8C  3C A0 80 0C */	lis r5, udp_cc_peek@ha
/* 800C6090 000C0F90  38 C5 62 58 */	addi r6, r5, udp_cc_peek@l
/* 800C6094 000C0F94  3C 80 80 0C */	lis r4, udp_cc_pre_continue@ha
/* 800C6098 000C0F98  38 A4 62 50 */	addi r5, r4, udp_cc_pre_continue@l
/* 800C609C 000C0F9C  3C 60 80 0C */	lis r3, udp_cc_post_stop@ha
/* 800C60A0 000C0FA0  38 83 62 48 */	addi r4, r3, udp_cc_post_stop@l
/* 800C60A4 000C0FA4  3F C0 80 41 */	lis r30, TRK_Use_BBA@ha
/* 800C60A8 000C0FA8  3B A0 00 01 */	li r29, 1
/* 800C60AC 000C0FAC  93 EC 00 00 */	stw r31, 0(r12)
/* 800C60B0 000C0FB0  38 60 00 00 */	li r3, 0
/* 800C60B4 000C0FB4  9B BE DC 28 */	stb r29, TRK_Use_BBA@l(r30)
/* 800C60B8 000C0FB8  91 6C 00 18 */	stw r11, 0x18(r12)
/* 800C60BC 000C0FBC  91 4C 00 1C */	stw r10, 0x1c(r12)
/* 800C60C0 000C0FC0  91 2C 00 10 */	stw r9, 0x10(r12)
/* 800C60C4 000C0FC4  91 0C 00 14 */	stw r8, 0x14(r12)
/* 800C60C8 000C0FC8  90 EC 00 08 */	stw r7, 8(r12)
/* 800C60CC 000C0FCC  90 CC 00 0C */	stw r6, 0xc(r12)
/* 800C60D0 000C0FD0  90 AC 00 20 */	stw r5, 0x20(r12)
/* 800C60D4 000C0FD4  90 8C 00 24 */	stw r4, 0x24(r12)
/* 800C60D8 000C0FD8  90 0C 00 04 */	stw r0, 4(r12)
/* 800C60DC 000C0FDC  48 00 00 C8 */	b lbl_800C61A4
lbl_800C60E0:
/* 800C60E0 000C0FE0  2C 1E 00 01 */	cmpwi r30, 1
/* 800C60E4 000C0FE4  40 82 00 94 */	bne lbl_800C6178
/* 800C60E8 000C0FE8  38 7D 00 60 */	addi r3, r29, 0x60
/* 800C60EC 000C0FEC  4C C6 31 82 */	crclr 6
/* 800C60F0 000C0FF0  48 0B DE 29 */	bl OSReport
/* 800C60F4 000C0FF4  3F E0 80 0C */	lis r31, gdev_cc_initialize@ha
/* 800C60F8 000C0FF8  3D 60 80 0C */	lis r11, gdev_cc_open@ha
/* 800C60FC 000C0FFC  3B FF 64 C8 */	addi r31, r31, gdev_cc_initialize@l
/* 800C6100 000C1000  3D 80 80 3A */	lis r12, gDBCommTable@ha
/* 800C6104 000C1004  3D 40 80 0C */	lis r10, gdev_cc_close@ha
/* 800C6108 000C1008  3D 20 80 0C */	lis r9, gdev_cc_read@ha
/* 800C610C 000C100C  3D 00 80 0C */	lis r8, gdev_cc_write@ha
/* 800C6110 000C1010  3C E0 80 0C */	lis r7, gdev_cc_shutdown@ha
/* 800C6114 000C1014  3C C0 80 0C */	lis r6, gdev_cc_peek@ha
/* 800C6118 000C1018  3C A0 80 0C */	lis r5, gdev_cc_pre_continue@ha
/* 800C611C 000C101C  3C 80 80 0C */	lis r4, gdev_cc_post_stop@ha
/* 800C6120 000C1020  3C 60 80 0C */	lis r3, gdev_cc_initinterrupts@ha
/* 800C6124 000C1024  38 03 62 90 */	addi r0, r3, gdev_cc_initinterrupts@l
/* 800C6128 000C1028  97 EC 93 F0 */	stwu r31, gDBCommTable@l(r12)
/* 800C612C 000C102C  39 6B 64 9C */	addi r11, r11, gdev_cc_open@l
/* 800C6130 000C1030  39 4A 64 94 */	addi r10, r10, gdev_cc_close@l
/* 800C6134 000C1034  39 29 63 E0 */	addi r9, r9, gdev_cc_read@l
/* 800C6138 000C1038  39 08 63 6C */	addi r8, r8, gdev_cc_write@l
/* 800C613C 000C103C  38 E7 64 C0 */	addi r7, r7, gdev_cc_shutdown@l
/* 800C6140 000C1040  38 C6 62 B4 */	addi r6, r6, gdev_cc_peek@l
/* 800C6144 000C1044  38 A5 63 48 */	addi r5, r5, gdev_cc_pre_continue@l
/* 800C6148 000C1048  38 84 63 24 */	addi r4, r4, gdev_cc_post_stop@l
/* 800C614C 000C104C  91 6C 00 18 */	stw r11, 0x18(r12)
/* 800C6150 000C1050  38 60 00 00 */	li r3, 0
/* 800C6154 000C1054  91 4C 00 1C */	stw r10, 0x1c(r12)
/* 800C6158 000C1058  91 2C 00 10 */	stw r9, 0x10(r12)
/* 800C615C 000C105C  91 0C 00 14 */	stw r8, 0x14(r12)
/* 800C6160 000C1060  90 EC 00 08 */	stw r7, 8(r12)
/* 800C6164 000C1064  90 CC 00 0C */	stw r6, 0xc(r12)
/* 800C6168 000C1068  90 AC 00 20 */	stw r5, 0x20(r12)
/* 800C616C 000C106C  90 8C 00 24 */	stw r4, 0x24(r12)
/* 800C6170 000C1070  90 0C 00 04 */	stw r0, 4(r12)
/* 800C6174 000C1074  48 00 00 30 */	b lbl_800C61A4
lbl_800C6178:
/* 800C6178 000C1078  7F C4 F3 78 */	mr r4, r30
/* 800C617C 000C107C  38 7D 00 84 */	addi r3, r29, 0x84
/* 800C6180 000C1080  4C C6 31 82 */	crclr 6
/* 800C6184 000C1084  48 0B DD 95 */	bl OSReport
/* 800C6188 000C1088  38 7D 00 B0 */	addi r3, r29, 0xb0
/* 800C618C 000C108C  4C C6 31 82 */	crclr 6
/* 800C6190 000C1090  48 0B DD 89 */	bl OSReport
/* 800C6194 000C1094  38 7D 00 E0 */	addi r3, r29, 0xe0
/* 800C6198 000C1098  4C C6 31 82 */	crclr 6
/* 800C619C 000C109C  48 0B DD 7D */	bl OSReport
/* 800C61A0 000C10A0  38 60 00 01 */	li r3, 1
lbl_800C61A4:
/* 800C61A4 000C10A4  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800C61A8 000C10A8  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800C61AC 000C10AC  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 800C61B0 000C10B0  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 800C61B4 000C10B4  7C 08 03 A6 */	mtlr r0
/* 800C61B8 000C10B8  38 21 00 20 */	addi r1, r1, 0x20
/* 800C61BC 000C10BC  4E 80 00 20 */	blr 

.global TRKEXICallBack
TRKEXICallBack:
/* 800C61C0 000C10C0  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800C61C4 000C10C4  7C 08 02 A6 */	mflr r0
/* 800C61C8 000C10C8  90 01 00 14 */	stw r0, 0x14(r1)
/* 800C61CC 000C10CC  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800C61D0 000C10D0  7C 9F 23 78 */	mr r31, r4
/* 800C61D4 000C10D4  48 02 DF F9 */	bl OSEnableScheduler
/* 800C61D8 000C10D8  7F E3 FB 78 */	mr r3, r31
/* 800C61DC 000C10DC  38 80 05 00 */	li r4, 0x500
/* 800C61E0 000C10E0  4B FF FB 59 */	bl TRKLoadContext
/* 800C61E4 000C10E4  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800C61E8 000C10E8  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 800C61EC 000C10EC  7C 08 03 A6 */	mtlr r0
/* 800C61F0 000C10F0  38 21 00 10 */	addi r1, r1, 0x10
/* 800C61F4 000C10F4  4E 80 00 20 */	blr 
