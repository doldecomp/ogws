.include "macros.inc"

.section .text, "ax"  # 0x800076E0 - 0x80355080

.global func_80007C6C
func_80007C6C:
/* 80007C6C 00002B6C  3C 80 80 39 */	lis r4, lbl_80393A94@ha
/* 80007C70 00002B70  38 84 3A 94 */	addi r4, r4, lbl_80393A94@l
/* 80007C74 00002B74  90 83 00 00 */	stw r4, 0(r3)
/* 80007C78 00002B78  4E 80 00 20 */	blr 

.global func_80007C7C
func_80007C7C:
/* 80007C7C 00002B7C  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80007C80 00002B80  7C 08 02 A6 */	mflr r0
/* 80007C84 00002B84  2C 03 00 00 */	cmpwi r3, 0
/* 80007C88 00002B88  90 01 00 14 */	stw r0, 0x14(r1)
/* 80007C8C 00002B8C  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80007C90 00002B90  7C 7F 1B 78 */	mr r31, r3
/* 80007C94 00002B94  41 82 00 10 */	beq lbl_80007CA4
/* 80007C98 00002B98  2C 04 00 00 */	cmpwi r4, 0
/* 80007C9C 00002B9C  40 81 00 08 */	ble lbl_80007CA4
/* 80007CA0 00002BA0  48 09 B5 E5 */	bl func_800A3284
lbl_80007CA4:
/* 80007CA4 00002BA4  7F E3 FB 78 */	mr r3, r31
/* 80007CA8 00002BA8  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80007CAC 00002BAC  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80007CB0 00002BB0  7C 08 03 A6 */	mtlr r0
/* 80007CB4 00002BB4  38 21 00 10 */	addi r1, r1, 0x10
/* 80007CB8 00002BB8  4E 80 00 20 */	blr 
/* 80007CBC 00002BBC  94 21 FF B0 */	stwu r1, -0x50(r1)
/* 80007CC0 00002BC0  7C 08 02 A6 */	mflr r0
/* 80007CC4 00002BC4  90 01 00 54 */	stw r0, 0x54(r1)
/* 80007CC8 00002BC8  DB E1 00 40 */	stfd f31, 0x40(r1)
/* 80007CCC 00002BCC  F3 E1 00 48 */	psq_st f31, 72(r1), 0, qr0
/* 80007CD0 00002BD0  DB C1 00 30 */	stfd f30, 0x30(r1)
/* 80007CD4 00002BD4  F3 C1 00 38 */	psq_st f30, 56(r1), 0, qr0
/* 80007CD8 00002BD8  2C 04 00 0A */	cmpwi r4, 0xa
/* 80007CDC 00002BDC  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 80007CE0 00002BE0  93 C1 00 28 */	stw r30, 0x28(r1)
/* 80007CE4 00002BE4  93 A1 00 24 */	stw r29, 0x24(r1)
/* 80007CE8 00002BE8  7C BD 2B 78 */	mr r29, r5
/* 80007CEC 00002BEC  41 82 00 14 */	beq lbl_80007D00
/* 80007CF0 00002BF0  40 80 00 CC */	bge lbl_80007DBC
/* 80007CF4 00002BF4  2C 04 00 09 */	cmpwi r4, 9
/* 80007CF8 00002BF8  40 80 00 30 */	bge lbl_80007D28
/* 80007CFC 00002BFC  48 00 00 C0 */	b lbl_80007DBC
lbl_80007D00:
/* 80007D00 00002C00  83 E5 00 00 */	lwz r31, 0(r5)
/* 80007D04 00002C04  C3 E5 00 08 */	lfs f31, 8(r5)
/* 80007D08 00002C08  C3 DF 00 30 */	lfs f30, 0x30(r31)
/* 80007D0C 00002C0C  7F E3 FB 78 */	mr r3, r31
/* 80007D10 00002C10  48 00 49 79 */	bl func_8000C688
/* 80007D14 00002C14  EC 1E 08 2A */	fadds f0, f30, f1
/* 80007D18 00002C18  D3 FF 00 2C */	stfs f31, 0x2c(r31)
/* 80007D1C 00002C1C  38 60 00 03 */	li r3, 3
/* 80007D20 00002C20  D0 1F 00 30 */	stfs f0, 0x30(r31)
/* 80007D24 00002C24  48 00 00 9C */	b lbl_80007DC0
lbl_80007D28:
/* 80007D28 00002C28  83 E5 00 00 */	lwz r31, 0(r5)
/* 80007D2C 00002C2C  83 DF 00 58 */	lwz r30, 0x58(r31)
/* 80007D30 00002C30  2C 1E 00 00 */	cmpwi r30, 0
/* 80007D34 00002C34  40 81 00 80 */	ble lbl_80007DB4
/* 80007D38 00002C38  88 1F 00 43 */	lbz r0, 0x43(r31)
/* 80007D3C 00002C3C  2C 00 00 00 */	cmpwi r0, 0
/* 80007D40 00002C40  41 82 00 0C */	beq lbl_80007D4C
/* 80007D44 00002C44  C0 3F 00 44 */	lfs f1, 0x44(r31)
/* 80007D48 00002C48  48 00 00 0C */	b lbl_80007D54
lbl_80007D4C:
/* 80007D4C 00002C4C  7F E3 FB 78 */	mr r3, r31
/* 80007D50 00002C50  48 00 3E 99 */	bl func_8000BBE8
lbl_80007D54:
/* 80007D54 00002C54  3C 00 43 30 */	lis r0, 0x4330
/* 80007D58 00002C58  6F C3 80 00 */	xoris r3, r30, 0x8000
/* 80007D5C 00002C5C  90 61 00 0C */	stw r3, 0xc(r1)
/* 80007D60 00002C60  C8 42 80 00 */	lfd f2, lbl_804BFA20-_SDA2_BASE_(r2)
/* 80007D64 00002C64  90 01 00 08 */	stw r0, 8(r1)
/* 80007D68 00002C68  C0 9F 00 2C */	lfs f4, 0x2c(r31)
/* 80007D6C 00002C6C  C8 01 00 08 */	lfd f0, 8(r1)
/* 80007D70 00002C70  C0 7D 00 08 */	lfs f3, 8(r29)
/* 80007D74 00002C74  EC 00 10 28 */	fsubs f0, f0, f2
/* 80007D78 00002C78  90 01 00 18 */	stw r0, 0x18(r1)
/* 80007D7C 00002C7C  EC 84 18 28 */	fsubs f4, f4, f3
/* 80007D80 00002C80  EC 20 00 72 */	fmuls f1, f0, f1
/* 80007D84 00002C84  EC 04 08 24 */	fdivs f0, f4, f1
/* 80007D88 00002C88  FC 00 00 1E */	fctiwz f0, f0
/* 80007D8C 00002C8C  D8 01 00 10 */	stfd f0, 0x10(r1)
/* 80007D90 00002C90  80 61 00 14 */	lwz r3, 0x14(r1)
/* 80007D94 00002C94  38 03 00 01 */	addi r0, r3, 1
/* 80007D98 00002C98  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 80007D9C 00002C9C  90 01 00 1C */	stw r0, 0x1c(r1)
/* 80007DA0 00002CA0  C8 01 00 18 */	lfd f0, 0x18(r1)
/* 80007DA4 00002CA4  EC 00 10 28 */	fsubs f0, f0, f2
/* 80007DA8 00002CA8  EC 01 00 32 */	fmuls f0, f1, f0
/* 80007DAC 00002CAC  EC 03 00 2A */	fadds f0, f3, f0
/* 80007DB0 00002CB0  D0 1F 00 2C */	stfs f0, 0x2c(r31)
lbl_80007DB4:
/* 80007DB4 00002CB4  38 60 00 01 */	li r3, 1
/* 80007DB8 00002CB8  48 00 00 08 */	b lbl_80007DC0
lbl_80007DBC:
/* 80007DBC 00002CBC  38 60 00 00 */	li r3, 0
lbl_80007DC0:
/* 80007DC0 00002CC0  E3 E1 00 48 */	psq_l f31, 72(r1), 0, qr0
/* 80007DC4 00002CC4  CB E1 00 40 */	lfd f31, 0x40(r1)
/* 80007DC8 00002CC8  E3 C1 00 38 */	psq_l f30, 56(r1), 0, qr0
/* 80007DCC 00002CCC  CB C1 00 30 */	lfd f30, 0x30(r1)
/* 80007DD0 00002CD0  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 80007DD4 00002CD4  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 80007DD8 00002CD8  80 01 00 54 */	lwz r0, 0x54(r1)
/* 80007DDC 00002CDC  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 80007DE0 00002CE0  7C 08 03 A6 */	mtlr r0
/* 80007DE4 00002CE4  38 21 00 50 */	addi r1, r1, 0x50
/* 80007DE8 00002CE8  4E 80 00 20 */	blr 
/* 80007DEC 00002CEC  94 21 FF A0 */	stwu r1, -0x60(r1)
/* 80007DF0 00002CF0  7C 08 02 A6 */	mflr r0
/* 80007DF4 00002CF4  90 01 00 64 */	stw r0, 0x64(r1)
/* 80007DF8 00002CF8  DB E1 00 50 */	stfd f31, 0x50(r1)
/* 80007DFC 00002CFC  F3 E1 00 58 */	psq_st f31, 88(r1), 0, qr0
/* 80007E00 00002D00  DB C1 00 40 */	stfd f30, 0x40(r1)
/* 80007E04 00002D04  F3 C1 00 48 */	psq_st f30, 72(r1), 0, qr0
/* 80007E08 00002D08  39 61 00 40 */	addi r11, r1, 0x40
/* 80007E0C 00002D0C  48 0A 9F 39 */	bl func_800B1D44
/* 80007E10 00002D10  2C 05 00 0A */	cmpwi r5, 0xa
/* 80007E14 00002D14  7C 9B 23 78 */	mr r27, r4
/* 80007E18 00002D18  7C DC 33 78 */	mr r28, r6
/* 80007E1C 00002D1C  41 82 00 14 */	beq lbl_80007E30
/* 80007E20 00002D20  40 80 01 88 */	bge lbl_80007FA8
/* 80007E24 00002D24  2C 05 00 09 */	cmpwi r5, 9
/* 80007E28 00002D28  40 80 00 90 */	bge lbl_80007EB8
/* 80007E2C 00002D2C  48 00 01 7C */	b lbl_80007FA8
lbl_80007E30:
/* 80007E30 00002D30  83 C6 00 00 */	lwz r30, 0(r6)
/* 80007E34 00002D34  C0 1E 00 2C */	lfs f0, 0x2c(r30)
/* 80007E38 00002D38  D0 04 00 08 */	stfs f0, 8(r4)
/* 80007E3C 00002D3C  C0 1E 00 30 */	lfs f0, 0x30(r30)
/* 80007E40 00002D40  D0 04 00 04 */	stfs f0, 4(r4)
/* 80007E44 00002D44  83 E6 00 00 */	lwz r31, 0(r6)
/* 80007E48 00002D48  C3 E6 00 08 */	lfs f31, 8(r6)
/* 80007E4C 00002D4C  C3 DF 00 30 */	lfs f30, 0x30(r31)
/* 80007E50 00002D50  7F E3 FB 78 */	mr r3, r31
/* 80007E54 00002D54  48 00 48 35 */	bl func_8000C688
/* 80007E58 00002D58  EC 1E 08 2A */	fadds f0, f30, f1
/* 80007E5C 00002D5C  D3 FF 00 2C */	stfs f31, 0x2c(r31)
/* 80007E60 00002D60  D0 1F 00 30 */	stfs f0, 0x30(r31)
/* 80007E64 00002D64  C0 1E 00 2C */	lfs f0, 0x2c(r30)
/* 80007E68 00002D68  D0 1B 00 00 */	stfs f0, 0(r27)
/* 80007E6C 00002D6C  C3 DE 00 30 */	lfs f30, 0x30(r30)
/* 80007E70 00002D70  80 7C 00 00 */	lwz r3, 0(r28)
/* 80007E74 00002D74  48 00 3D D5 */	bl func_8000BC48
/* 80007E78 00002D78  EC 1E 08 2A */	fadds f0, f30, f1
/* 80007E7C 00002D7C  C0 DB 00 04 */	lfs f6, 4(r27)
/* 80007E80 00002D80  C0 FB 00 00 */	lfs f7, 0(r27)
/* 80007E84 00002D84  38 60 00 03 */	li r3, 3
/* 80007E88 00002D88  C0 BB 00 08 */	lfs f5, 8(r27)
/* 80007E8C 00002D8C  EC 40 30 28 */	fsubs f2, f0, f6
/* 80007E90 00002D90  EC 65 38 28 */	fsubs f3, f5, f7
/* 80007E94 00002D94  FC 22 01 AE */	fsel f1, f2, f6, f0
/* 80007E98 00002D98  FC 83 29 EE */	fsel f4, f3, f7, f5
/* 80007E9C 00002D9C  FC 63 39 6E */	fsel f3, f3, f5, f7
/* 80007EA0 00002DA0  FC 02 30 2E */	fsel f0, f2, f0, f6
/* 80007EA4 00002DA4  D0 3B 00 04 */	stfs f1, 4(r27)
/* 80007EA8 00002DA8  D0 9B 00 00 */	stfs f4, 0(r27)
/* 80007EAC 00002DAC  D0 7B 00 08 */	stfs f3, 8(r27)
/* 80007EB0 00002DB0  D0 1B 00 0C */	stfs f0, 0xc(r27)
/* 80007EB4 00002DB4  48 00 00 F8 */	b lbl_80007FAC
lbl_80007EB8:
/* 80007EB8 00002DB8  83 A6 00 00 */	lwz r29, 0(r6)
/* 80007EBC 00002DBC  C0 1D 00 2C */	lfs f0, 0x2c(r29)
/* 80007EC0 00002DC0  D0 04 00 00 */	stfs f0, 0(r4)
/* 80007EC4 00002DC4  83 E6 00 00 */	lwz r31, 0(r6)
/* 80007EC8 00002DC8  83 DF 00 58 */	lwz r30, 0x58(r31)
/* 80007ECC 00002DCC  2C 1E 00 00 */	cmpwi r30, 0
/* 80007ED0 00002DD0  40 81 00 80 */	ble lbl_80007F50
/* 80007ED4 00002DD4  88 1F 00 43 */	lbz r0, 0x43(r31)
/* 80007ED8 00002DD8  2C 00 00 00 */	cmpwi r0, 0
/* 80007EDC 00002DDC  41 82 00 0C */	beq lbl_80007EE8
/* 80007EE0 00002DE0  C0 3F 00 44 */	lfs f1, 0x44(r31)
/* 80007EE4 00002DE4  48 00 00 0C */	b lbl_80007EF0
lbl_80007EE8:
/* 80007EE8 00002DE8  7F E3 FB 78 */	mr r3, r31
/* 80007EEC 00002DEC  48 00 3C FD */	bl func_8000BBE8
lbl_80007EF0:
/* 80007EF0 00002DF0  3C 00 43 30 */	lis r0, 0x4330
/* 80007EF4 00002DF4  6F C3 80 00 */	xoris r3, r30, 0x8000
/* 80007EF8 00002DF8  90 61 00 0C */	stw r3, 0xc(r1)
/* 80007EFC 00002DFC  C8 42 80 00 */	lfd f2, lbl_804BFA20-_SDA2_BASE_(r2)
/* 80007F00 00002E00  90 01 00 08 */	stw r0, 8(r1)
/* 80007F04 00002E04  C0 9F 00 2C */	lfs f4, 0x2c(r31)
/* 80007F08 00002E08  C8 01 00 08 */	lfd f0, 8(r1)
/* 80007F0C 00002E0C  C0 7C 00 08 */	lfs f3, 8(r28)
/* 80007F10 00002E10  EC 00 10 28 */	fsubs f0, f0, f2
/* 80007F14 00002E14  90 01 00 18 */	stw r0, 0x18(r1)
/* 80007F18 00002E18  EC 84 18 28 */	fsubs f4, f4, f3
/* 80007F1C 00002E1C  EC 20 00 72 */	fmuls f1, f0, f1
/* 80007F20 00002E20  EC 04 08 24 */	fdivs f0, f4, f1
/* 80007F24 00002E24  FC 00 00 1E */	fctiwz f0, f0
/* 80007F28 00002E28  D8 01 00 10 */	stfd f0, 0x10(r1)
/* 80007F2C 00002E2C  80 61 00 14 */	lwz r3, 0x14(r1)
/* 80007F30 00002E30  38 03 00 01 */	addi r0, r3, 1
/* 80007F34 00002E34  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 80007F38 00002E38  90 01 00 1C */	stw r0, 0x1c(r1)
/* 80007F3C 00002E3C  C8 01 00 18 */	lfd f0, 0x18(r1)
/* 80007F40 00002E40  EC 00 10 28 */	fsubs f0, f0, f2
/* 80007F44 00002E44  EC 01 00 32 */	fmuls f0, f1, f0
/* 80007F48 00002E48  EC 03 00 2A */	fadds f0, f3, f0
/* 80007F4C 00002E4C  D0 1F 00 2C */	stfs f0, 0x2c(r31)
lbl_80007F50:
/* 80007F50 00002E50  C0 1D 00 2C */	lfs f0, 0x2c(r29)
/* 80007F54 00002E54  7F A3 EB 78 */	mr r3, r29
/* 80007F58 00002E58  D0 1B 00 08 */	stfs f0, 8(r27)
/* 80007F5C 00002E5C  C0 1D 00 30 */	lfs f0, 0x30(r29)
/* 80007F60 00002E60  D0 1B 00 04 */	stfs f0, 4(r27)
/* 80007F64 00002E64  48 00 3C E5 */	bl func_8000BC48
/* 80007F68 00002E68  C0 5B 00 04 */	lfs f2, 4(r27)
/* 80007F6C 00002E6C  38 60 00 01 */	li r3, 1
/* 80007F70 00002E70  C0 DB 00 00 */	lfs f6, 0(r27)
/* 80007F74 00002E74  EC 02 08 2A */	fadds f0, f2, f1
/* 80007F78 00002E78  C0 9B 00 08 */	lfs f4, 8(r27)
/* 80007F7C 00002E7C  EC 24 30 28 */	fsubs f1, f4, f6
/* 80007F80 00002E80  EC 60 10 28 */	fsubs f3, f0, f2
/* 80007F84 00002E84  FC A1 21 AE */	fsel f5, f1, f6, f4
/* 80007F88 00002E88  FC 81 31 2E */	fsel f4, f1, f4, f6
/* 80007F8C 00002E8C  FC 23 00 AE */	fsel f1, f3, f2, f0
/* 80007F90 00002E90  FC 03 10 2E */	fsel f0, f3, f0, f2
/* 80007F94 00002E94  D0 BB 00 00 */	stfs f5, 0(r27)
/* 80007F98 00002E98  D0 9B 00 08 */	stfs f4, 8(r27)
/* 80007F9C 00002E9C  D0 3B 00 04 */	stfs f1, 4(r27)
/* 80007FA0 00002EA0  D0 1B 00 0C */	stfs f0, 0xc(r27)
/* 80007FA4 00002EA4  48 00 00 08 */	b lbl_80007FAC
lbl_80007FA8:
/* 80007FA8 00002EA8  38 60 00 00 */	li r3, 0
lbl_80007FAC:
/* 80007FAC 00002EAC  E3 E1 00 58 */	psq_l f31, 88(r1), 0, qr0
/* 80007FB0 00002EB0  CB E1 00 50 */	lfd f31, 0x50(r1)
/* 80007FB4 00002EB4  E3 C1 00 48 */	psq_l f30, 72(r1), 0, qr0
/* 80007FB8 00002EB8  39 61 00 40 */	addi r11, r1, 0x40
/* 80007FBC 00002EBC  CB C1 00 40 */	lfd f30, 0x40(r1)
/* 80007FC0 00002EC0  48 0A 9D D1 */	bl func_800B1D90
/* 80007FC4 00002EC4  80 01 00 64 */	lwz r0, 0x64(r1)
/* 80007FC8 00002EC8  7C 08 03 A6 */	mtlr r0
/* 80007FCC 00002ECC  38 21 00 60 */	addi r1, r1, 0x60
/* 80007FD0 00002ED0  4E 80 00 20 */	blr 

.global func_80007FD4
func_80007FD4:
/* 80007FD4 00002ED4  3C 80 80 39 */	lis r4, lbl_80393A80@ha
/* 80007FD8 00002ED8  38 84 3A 80 */	addi r4, r4, lbl_80393A80@l
/* 80007FDC 00002EDC  90 83 00 00 */	stw r4, 0(r3)
/* 80007FE0 00002EE0  4E 80 00 20 */	blr 

.global func_80007FE4
func_80007FE4:
/* 80007FE4 00002EE4  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80007FE8 00002EE8  7C 08 02 A6 */	mflr r0
/* 80007FEC 00002EEC  2C 03 00 00 */	cmpwi r3, 0
/* 80007FF0 00002EF0  90 01 00 14 */	stw r0, 0x14(r1)
/* 80007FF4 00002EF4  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80007FF8 00002EF8  7C 7F 1B 78 */	mr r31, r3
/* 80007FFC 00002EFC  41 82 00 10 */	beq lbl_8000800C
/* 80008000 00002F00  2C 04 00 00 */	cmpwi r4, 0
/* 80008004 00002F04  40 81 00 08 */	ble lbl_8000800C
/* 80008008 00002F08  48 09 B2 7D */	bl func_800A3284
lbl_8000800C:
/* 8000800C 00002F0C  7F E3 FB 78 */	mr r3, r31
/* 80008010 00002F10  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80008014 00002F14  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80008018 00002F18  7C 08 03 A6 */	mtlr r0
/* 8000801C 00002F1C  38 21 00 10 */	addi r1, r1, 0x10
/* 80008020 00002F20  4E 80 00 20 */	blr 

.global func_80008024
func_80008024:
/* 80008024 00002F24  94 21 FF B0 */	stwu r1, -0x50(r1)
/* 80008028 00002F28  7C 08 02 A6 */	mflr r0
/* 8000802C 00002F2C  90 01 00 54 */	stw r0, 0x54(r1)
/* 80008030 00002F30  DB E1 00 40 */	stfd f31, 0x40(r1)
/* 80008034 00002F34  F3 E1 00 48 */	psq_st f31, 72(r1), 0, qr0
/* 80008038 00002F38  DB C1 00 30 */	stfd f30, 0x30(r1)
/* 8000803C 00002F3C  F3 C1 00 38 */	psq_st f30, 56(r1), 0, qr0
/* 80008040 00002F40  2C 04 00 0A */	cmpwi r4, 0xa
/* 80008044 00002F44  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 80008048 00002F48  93 C1 00 28 */	stw r30, 0x28(r1)
/* 8000804C 00002F4C  93 A1 00 24 */	stw r29, 0x24(r1)
/* 80008050 00002F50  7C BD 2B 78 */	mr r29, r5
/* 80008054 00002F54  41 82 00 14 */	beq lbl_80008068
/* 80008058 00002F58  40 80 00 CC */	bge lbl_80008124
/* 8000805C 00002F5C  2C 04 00 09 */	cmpwi r4, 9
/* 80008060 00002F60  40 80 00 30 */	bge lbl_80008090
/* 80008064 00002F64  48 00 00 C0 */	b lbl_80008124
lbl_80008068:
/* 80008068 00002F68  83 E5 00 00 */	lwz r31, 0(r5)
/* 8000806C 00002F6C  C3 E5 00 08 */	lfs f31, 8(r5)
/* 80008070 00002F70  C3 DF 00 30 */	lfs f30, 0x30(r31)
/* 80008074 00002F74  7F E3 FB 78 */	mr r3, r31
/* 80008078 00002F78  48 00 65 01 */	bl func_8000E578
/* 8000807C 00002F7C  EC 1E 08 2A */	fadds f0, f30, f1
/* 80008080 00002F80  D3 FF 00 2C */	stfs f31, 0x2c(r31)
/* 80008084 00002F84  38 60 00 03 */	li r3, 3
/* 80008088 00002F88  D0 1F 00 30 */	stfs f0, 0x30(r31)
/* 8000808C 00002F8C  48 00 00 9C */	b lbl_80008128
lbl_80008090:
/* 80008090 00002F90  83 E5 00 00 */	lwz r31, 0(r5)
/* 80008094 00002F94  83 DF 00 58 */	lwz r30, 0x58(r31)
/* 80008098 00002F98  2C 1E 00 00 */	cmpwi r30, 0
/* 8000809C 00002F9C  40 81 00 80 */	ble lbl_8000811C
/* 800080A0 00002FA0  88 1F 00 43 */	lbz r0, 0x43(r31)
/* 800080A4 00002FA4  2C 00 00 00 */	cmpwi r0, 0
/* 800080A8 00002FA8  41 82 00 0C */	beq lbl_800080B4
/* 800080AC 00002FAC  C0 3F 00 44 */	lfs f1, 0x44(r31)
/* 800080B0 00002FB0  48 00 00 0C */	b lbl_800080BC
lbl_800080B4:
/* 800080B4 00002FB4  7F E3 FB 78 */	mr r3, r31
/* 800080B8 00002FB8  48 00 3B 31 */	bl func_8000BBE8
lbl_800080BC:
/* 800080BC 00002FBC  3C 00 43 30 */	lis r0, 0x4330
/* 800080C0 00002FC0  6F C3 80 00 */	xoris r3, r30, 0x8000
/* 800080C4 00002FC4  90 61 00 0C */	stw r3, 0xc(r1)
/* 800080C8 00002FC8  C8 42 80 00 */	lfd f2, lbl_804BFA20-_SDA2_BASE_(r2)
/* 800080CC 00002FCC  90 01 00 08 */	stw r0, 8(r1)
/* 800080D0 00002FD0  C0 9F 00 2C */	lfs f4, 0x2c(r31)
/* 800080D4 00002FD4  C8 01 00 08 */	lfd f0, 8(r1)
/* 800080D8 00002FD8  C0 7D 00 08 */	lfs f3, 8(r29)
/* 800080DC 00002FDC  EC 00 10 28 */	fsubs f0, f0, f2
/* 800080E0 00002FE0  90 01 00 18 */	stw r0, 0x18(r1)
/* 800080E4 00002FE4  EC 84 18 28 */	fsubs f4, f4, f3
/* 800080E8 00002FE8  EC 20 00 72 */	fmuls f1, f0, f1
/* 800080EC 00002FEC  EC 04 08 24 */	fdivs f0, f4, f1
/* 800080F0 00002FF0  FC 00 00 1E */	fctiwz f0, f0
/* 800080F4 00002FF4  D8 01 00 10 */	stfd f0, 0x10(r1)
/* 800080F8 00002FF8  80 61 00 14 */	lwz r3, 0x14(r1)
/* 800080FC 00002FFC  38 03 00 01 */	addi r0, r3, 1
/* 80008100 00003000  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 80008104 00003004  90 01 00 1C */	stw r0, 0x1c(r1)
/* 80008108 00003008  C8 01 00 18 */	lfd f0, 0x18(r1)
/* 8000810C 0000300C  EC 00 10 28 */	fsubs f0, f0, f2
/* 80008110 00003010  EC 01 00 32 */	fmuls f0, f1, f0
/* 80008114 00003014  EC 03 00 2A */	fadds f0, f3, f0
/* 80008118 00003018  D0 1F 00 2C */	stfs f0, 0x2c(r31)
lbl_8000811C:
/* 8000811C 0000301C  38 60 00 01 */	li r3, 1
/* 80008120 00003020  48 00 00 08 */	b lbl_80008128
lbl_80008124:
/* 80008124 00003024  38 60 00 00 */	li r3, 0
lbl_80008128:
/* 80008128 00003028  E3 E1 00 48 */	psq_l f31, 72(r1), 0, qr0
/* 8000812C 0000302C  CB E1 00 40 */	lfd f31, 0x40(r1)
/* 80008130 00003030  E3 C1 00 38 */	psq_l f30, 56(r1), 0, qr0
/* 80008134 00003034  CB C1 00 30 */	lfd f30, 0x30(r1)
/* 80008138 00003038  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 8000813C 0000303C  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 80008140 00003040  80 01 00 54 */	lwz r0, 0x54(r1)
/* 80008144 00003044  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 80008148 00003048  7C 08 03 A6 */	mtlr r0
/* 8000814C 0000304C  38 21 00 50 */	addi r1, r1, 0x50
/* 80008150 00003050  4E 80 00 20 */	blr 

.global func_80008154
func_80008154:
/* 80008154 00003054  94 21 FF A0 */	stwu r1, -0x60(r1)
/* 80008158 00003058  7C 08 02 A6 */	mflr r0
/* 8000815C 0000305C  90 01 00 64 */	stw r0, 0x64(r1)
/* 80008160 00003060  DB E1 00 50 */	stfd f31, 0x50(r1)
/* 80008164 00003064  F3 E1 00 58 */	psq_st f31, 88(r1), 0, qr0
/* 80008168 00003068  DB C1 00 40 */	stfd f30, 0x40(r1)
/* 8000816C 0000306C  F3 C1 00 48 */	psq_st f30, 72(r1), 0, qr0
/* 80008170 00003070  39 61 00 40 */	addi r11, r1, 0x40
/* 80008174 00003074  48 0A 9B D1 */	bl func_800B1D44
/* 80008178 00003078  2C 05 00 0A */	cmpwi r5, 0xa
/* 8000817C 0000307C  7C 9B 23 78 */	mr r27, r4
/* 80008180 00003080  7C DC 33 78 */	mr r28, r6
/* 80008184 00003084  41 82 00 14 */	beq lbl_80008198
/* 80008188 00003088  40 80 01 88 */	bge lbl_80008310
/* 8000818C 0000308C  2C 05 00 09 */	cmpwi r5, 9
/* 80008190 00003090  40 80 00 90 */	bge lbl_80008220
/* 80008194 00003094  48 00 01 7C */	b lbl_80008310
lbl_80008198:
/* 80008198 00003098  83 C6 00 00 */	lwz r30, 0(r6)
/* 8000819C 0000309C  C0 1E 00 2C */	lfs f0, 0x2c(r30)
/* 800081A0 000030A0  D0 04 00 08 */	stfs f0, 8(r4)
/* 800081A4 000030A4  C0 1E 00 30 */	lfs f0, 0x30(r30)
/* 800081A8 000030A8  D0 04 00 04 */	stfs f0, 4(r4)
/* 800081AC 000030AC  83 E6 00 00 */	lwz r31, 0(r6)
/* 800081B0 000030B0  C3 E6 00 08 */	lfs f31, 8(r6)
/* 800081B4 000030B4  C3 DF 00 30 */	lfs f30, 0x30(r31)
/* 800081B8 000030B8  7F E3 FB 78 */	mr r3, r31
/* 800081BC 000030BC  48 00 63 BD */	bl func_8000E578
/* 800081C0 000030C0  EC 1E 08 2A */	fadds f0, f30, f1
/* 800081C4 000030C4  D3 FF 00 2C */	stfs f31, 0x2c(r31)
/* 800081C8 000030C8  D0 1F 00 30 */	stfs f0, 0x30(r31)
/* 800081CC 000030CC  C0 1E 00 2C */	lfs f0, 0x2c(r30)
/* 800081D0 000030D0  D0 1B 00 00 */	stfs f0, 0(r27)
/* 800081D4 000030D4  C3 DE 00 30 */	lfs f30, 0x30(r30)
/* 800081D8 000030D8  80 7C 00 00 */	lwz r3, 0(r28)
/* 800081DC 000030DC  48 00 3A 6D */	bl func_8000BC48
/* 800081E0 000030E0  EC 1E 08 2A */	fadds f0, f30, f1
/* 800081E4 000030E4  C0 DB 00 04 */	lfs f6, 4(r27)
/* 800081E8 000030E8  C0 FB 00 00 */	lfs f7, 0(r27)
/* 800081EC 000030EC  38 60 00 03 */	li r3, 3
/* 800081F0 000030F0  C0 BB 00 08 */	lfs f5, 8(r27)
/* 800081F4 000030F4  EC 40 30 28 */	fsubs f2, f0, f6
/* 800081F8 000030F8  EC 65 38 28 */	fsubs f3, f5, f7
/* 800081FC 000030FC  FC 22 01 AE */	fsel f1, f2, f6, f0
/* 80008200 00003100  FC 83 29 EE */	fsel f4, f3, f7, f5
/* 80008204 00003104  FC 63 39 6E */	fsel f3, f3, f5, f7
/* 80008208 00003108  FC 02 30 2E */	fsel f0, f2, f0, f6
/* 8000820C 0000310C  D0 3B 00 04 */	stfs f1, 4(r27)
/* 80008210 00003110  D0 9B 00 00 */	stfs f4, 0(r27)
/* 80008214 00003114  D0 7B 00 08 */	stfs f3, 8(r27)
/* 80008218 00003118  D0 1B 00 0C */	stfs f0, 0xc(r27)
/* 8000821C 0000311C  48 00 00 F8 */	b lbl_80008314
lbl_80008220:
/* 80008220 00003120  83 A6 00 00 */	lwz r29, 0(r6)
/* 80008224 00003124  C0 1D 00 2C */	lfs f0, 0x2c(r29)
/* 80008228 00003128  D0 04 00 00 */	stfs f0, 0(r4)
/* 8000822C 0000312C  83 E6 00 00 */	lwz r31, 0(r6)
/* 80008230 00003130  83 DF 00 58 */	lwz r30, 0x58(r31)
/* 80008234 00003134  2C 1E 00 00 */	cmpwi r30, 0
/* 80008238 00003138  40 81 00 80 */	ble lbl_800082B8
/* 8000823C 0000313C  88 1F 00 43 */	lbz r0, 0x43(r31)
/* 80008240 00003140  2C 00 00 00 */	cmpwi r0, 0
/* 80008244 00003144  41 82 00 0C */	beq lbl_80008250
/* 80008248 00003148  C0 3F 00 44 */	lfs f1, 0x44(r31)
/* 8000824C 0000314C  48 00 00 0C */	b lbl_80008258
lbl_80008250:
/* 80008250 00003150  7F E3 FB 78 */	mr r3, r31
/* 80008254 00003154  48 00 39 95 */	bl func_8000BBE8
lbl_80008258:
/* 80008258 00003158  3C 00 43 30 */	lis r0, 0x4330
/* 8000825C 0000315C  6F C3 80 00 */	xoris r3, r30, 0x8000
/* 80008260 00003160  90 61 00 0C */	stw r3, 0xc(r1)
/* 80008264 00003164  C8 42 80 00 */	lfd f2, lbl_804BFA20-_SDA2_BASE_(r2)
/* 80008268 00003168  90 01 00 08 */	stw r0, 8(r1)
/* 8000826C 0000316C  C0 9F 00 2C */	lfs f4, 0x2c(r31)
/* 80008270 00003170  C8 01 00 08 */	lfd f0, 8(r1)
/* 80008274 00003174  C0 7C 00 08 */	lfs f3, 8(r28)
/* 80008278 00003178  EC 00 10 28 */	fsubs f0, f0, f2
/* 8000827C 0000317C  90 01 00 18 */	stw r0, 0x18(r1)
/* 80008280 00003180  EC 84 18 28 */	fsubs f4, f4, f3
/* 80008284 00003184  EC 20 00 72 */	fmuls f1, f0, f1
/* 80008288 00003188  EC 04 08 24 */	fdivs f0, f4, f1
/* 8000828C 0000318C  FC 00 00 1E */	fctiwz f0, f0
/* 80008290 00003190  D8 01 00 10 */	stfd f0, 0x10(r1)
/* 80008294 00003194  80 61 00 14 */	lwz r3, 0x14(r1)
/* 80008298 00003198  38 03 00 01 */	addi r0, r3, 1
/* 8000829C 0000319C  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 800082A0 000031A0  90 01 00 1C */	stw r0, 0x1c(r1)
/* 800082A4 000031A4  C8 01 00 18 */	lfd f0, 0x18(r1)
/* 800082A8 000031A8  EC 00 10 28 */	fsubs f0, f0, f2
/* 800082AC 000031AC  EC 01 00 32 */	fmuls f0, f1, f0
/* 800082B0 000031B0  EC 03 00 2A */	fadds f0, f3, f0
/* 800082B4 000031B4  D0 1F 00 2C */	stfs f0, 0x2c(r31)
lbl_800082B8:
/* 800082B8 000031B8  C0 1D 00 2C */	lfs f0, 0x2c(r29)
/* 800082BC 000031BC  7F A3 EB 78 */	mr r3, r29
/* 800082C0 000031C0  D0 1B 00 08 */	stfs f0, 8(r27)
/* 800082C4 000031C4  C0 1D 00 30 */	lfs f0, 0x30(r29)
/* 800082C8 000031C8  D0 1B 00 04 */	stfs f0, 4(r27)
/* 800082CC 000031CC  48 00 39 7D */	bl func_8000BC48
/* 800082D0 000031D0  C0 5B 00 04 */	lfs f2, 4(r27)
/* 800082D4 000031D4  38 60 00 01 */	li r3, 1
/* 800082D8 000031D8  C0 DB 00 00 */	lfs f6, 0(r27)
/* 800082DC 000031DC  EC 02 08 2A */	fadds f0, f2, f1
/* 800082E0 000031E0  C0 9B 00 08 */	lfs f4, 8(r27)
/* 800082E4 000031E4  EC 24 30 28 */	fsubs f1, f4, f6
/* 800082E8 000031E8  EC 60 10 28 */	fsubs f3, f0, f2
/* 800082EC 000031EC  FC A1 21 AE */	fsel f5, f1, f6, f4
/* 800082F0 000031F0  FC 81 31 2E */	fsel f4, f1, f4, f6
/* 800082F4 000031F4  FC 23 00 AE */	fsel f1, f3, f2, f0
/* 800082F8 000031F8  FC 03 10 2E */	fsel f0, f3, f0, f2
/* 800082FC 000031FC  D0 BB 00 00 */	stfs f5, 0(r27)
/* 80008300 00003200  D0 9B 00 08 */	stfs f4, 8(r27)
/* 80008304 00003204  D0 3B 00 04 */	stfs f1, 4(r27)
/* 80008308 00003208  D0 1B 00 0C */	stfs f0, 0xc(r27)
/* 8000830C 0000320C  48 00 00 08 */	b lbl_80008314
lbl_80008310:
/* 80008310 00003210  38 60 00 00 */	li r3, 0
lbl_80008314:
/* 80008314 00003214  E3 E1 00 58 */	psq_l f31, 88(r1), 0, qr0
/* 80008318 00003218  CB E1 00 50 */	lfd f31, 0x50(r1)
/* 8000831C 0000321C  E3 C1 00 48 */	psq_l f30, 72(r1), 0, qr0
/* 80008320 00003220  39 61 00 40 */	addi r11, r1, 0x40
/* 80008324 00003224  CB C1 00 40 */	lfd f30, 0x40(r1)
/* 80008328 00003228  48 0A 9A 69 */	bl func_800B1D90
/* 8000832C 0000322C  80 01 00 64 */	lwz r0, 0x64(r1)
/* 80008330 00003230  7C 08 03 A6 */	mtlr r0
/* 80008334 00003234  38 21 00 60 */	addi r1, r1, 0x60
/* 80008338 00003238  4E 80 00 20 */	blr 
