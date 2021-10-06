.include "macros.inc"

.section .data, "wa"
.global lbl_803976A0
lbl_803976A0:
	.incbin "baserom.dol", 0x3937A0, 0x30
.global lbl_803976D0
lbl_803976D0:
	.incbin "baserom.dol", 0x3937D0, 0xC
.global lbl_803976DC
lbl_803976DC:
	.incbin "baserom.dol", 0x3937DC, 0x14

.section .rodata, "a"
.balign 0x8
.global lbl_80379308
lbl_80379308:
	.incbin "baserom.dol", 0x375408, 0x10

.section .text, "ax"
# DrawPathBase::DrawPathBase
# Inherits from ScreenEffectBase, IScnProc
.global func_80089DCC
func_80089DCC:
/* 80089DCC 00084CCC  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80089DD0 00084CD0  7C 08 02 A6 */	mflr r0
/* 80089DD4 00084CD4  90 01 00 14 */	stw r0, 0x14(r1)
/* 80089DD8 00084CD8  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80089DDC 00084CDC  7C 7F 1B 78 */	mr r31, r3
/* 80089DE0 00084CE0  48 01 5E CD */	bl __ct__Q23EGG16ScreenEffectBaseFv
/* 80089DE4 00084CE4  38 7F 00 70 */	addi r3, r31, 0x70
/* 80089DE8 00084CE8  48 01 26 55 */	bl __ct__Q23EGG8IScnProcFv
/* 80089DEC 00084CEC  3C 80 80 39 */	lis r4, lbl_803976A0@ha
/* 80089DF0 00084CF0  7F E3 FB 78 */	mr r3, r31
/* 80089DF4 00084CF4  38 84 76 A0 */	addi r4, r4, lbl_803976A0@l
/* 80089DF8 00084CF8  38 04 00 0C */	addi r0, r4, 0xc
/* 80089DFC 00084CFC  90 9F 00 6C */	stw r4, 0x6c(r31)
/* 80089E00 00084D00  90 1F 00 70 */	stw r0, 0x70(r31)
/* 80089E04 00084D04  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80089E08 00084D08  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80089E0C 00084D0C  7C 08 03 A6 */	mtlr r0
/* 80089E10 00084D10  38 21 00 10 */	addi r1, r1, 0x10
/* 80089E14 00084D14  4E 80 00 20 */	blr 

# ScreenEffectBase::~ScreenEffectBase (weak)
.global __dt__Q23EGG16ScreenEffectBaseFv
__dt__Q23EGG16ScreenEffectBaseFv:
/* 80089E18 00084D18  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80089E1C 00084D1C  7C 08 02 A6 */	mflr r0
/* 80089E20 00084D20  2C 03 00 00 */	cmpwi r3, 0
/* 80089E24 00084D24  90 01 00 14 */	stw r0, 0x14(r1)
/* 80089E28 00084D28  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80089E2C 00084D2C  7C 7F 1B 78 */	mr r31, r3
/* 80089E30 00084D30  41 82 00 10 */	beq lbl_80089E40
/* 80089E34 00084D34  2C 04 00 00 */	cmpwi r4, 0
/* 80089E38 00084D38  40 81 00 08 */	ble lbl_80089E40
/* 80089E3C 00084D3C  48 01 94 49 */	bl __dl__FPv
lbl_80089E40:
/* 80089E40 00084D40  7F E3 FB 78 */	mr r3, r31
/* 80089E44 00084D44  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80089E48 00084D48  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80089E4C 00084D4C  7C 08 03 A6 */	mtlr r0
/* 80089E50 00084D50  38 21 00 10 */	addi r1, r1, 0x10
/* 80089E54 00084D54  4E 80 00 20 */	blr 

.global func_80089E58
func_80089E58:
/* 80089E58 00084D58  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80089E5C 00084D5C  7C 08 02 A6 */	mflr r0
/* 80089E60 00084D60  90 01 00 14 */	stw r0, 0x14(r1)
/* 80089E64 00084D64  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80089E68 00084D68  7C 7F 1B 78 */	mr r31, r3
/* 80089E6C 00084D6C  88 03 00 00 */	lbz r0, 0(r3)
/* 80089E70 00084D70  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 80089E74 00084D74  41 82 00 4C */	beq lbl_80089EC0
/* 80089E78 00084D78  80 0D 98 F0 */	lwz r0, lbl_804BEC70-_SDA_BASE_(r13)
/* 80089E7C 00084D7C  2C 00 00 00 */	cmpwi r0, 0
/* 80089E80 00084D80  40 82 00 20 */	bne lbl_80089EA0
/* 80089E84 00084D84  3C 60 80 39 */	lis r3, lbl_803976DC@ha
/* 80089E88 00084D88  3C A0 80 39 */	lis r5, lbl_803976D0@ha
/* 80089E8C 00084D8C  38 63 76 DC */	addi r3, r3, lbl_803976DC@l
/* 80089E90 00084D90  38 80 00 3B */	li r4, 0x3b
/* 80089E94 00084D94  38 A5 76 D0 */	addi r5, r5, lbl_803976D0@l
/* 80089E98 00084D98  4C C6 31 82 */	crclr 6
/* 80089E9C 00084D9C  48 01 80 6D */	bl system_halt
lbl_80089EA0:
/* 80089EA0 00084DA0  80 8D 98 F0 */	lwz r4, lbl_804BEC70-_SDA_BASE_(r13)
/* 80089EA4 00084DA4  7F E3 FB 78 */	mr r3, r31
/* 80089EA8 00084DA8  48 01 5E 4D */	bl func_8009FCF4
/* 80089EAC 00084DAC  81 9F 00 6C */	lwz r12, 0x6c(r31)
/* 80089EB0 00084DB0  7F E3 FB 78 */	mr r3, r31
/* 80089EB4 00084DB4  81 8C 00 24 */	lwz r12, 0x24(r12)
/* 80089EB8 00084DB8  7D 89 03 A6 */	mtctr r12
/* 80089EBC 00084DBC  4E 80 04 21 */	bctrl 
lbl_80089EC0:
/* 80089EC0 00084DC0  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80089EC4 00084DC4  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80089EC8 00084DC8  7C 08 03 A6 */	mtlr r0
/* 80089ECC 00084DCC  38 21 00 10 */	addi r1, r1, 0x10
/* 80089ED0 00084DD0  4E 80 00 20 */	blr 

/* 80089ED4 00084DD4  4E 80 00 20 */	blr 

/* 80089ED8 00084DD8  4E 80 00 20 */	blr 

# DrawPathBase::~DrawPathBase
lbl_80089EDC:
/* 80089EDC 00084DDC  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80089EE0 00084DE0  7C 08 02 A6 */	mflr r0
/* 80089EE4 00084DE4  2C 03 00 00 */	cmpwi r3, 0
/* 80089EE8 00084DE8  90 01 00 14 */	stw r0, 0x14(r1)
/* 80089EEC 00084DEC  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80089EF0 00084DF0  7C 9F 23 78 */	mr r31, r4
/* 80089EF4 00084DF4  93 C1 00 08 */	stw r30, 8(r1)
/* 80089EF8 00084DF8  7C 7E 1B 78 */	mr r30, r3
/* 80089EFC 00084DFC  41 82 00 20 */	beq lbl_80089F1C
/* 80089F00 00084E00  38 80 00 00 */	li r4, 0
/* 80089F04 00084E04  38 63 00 70 */	addi r3, r3, 0x70
/* 80089F08 00084E08  48 01 25 51 */	bl __dt__Q23EGG8IScnProcFv
/* 80089F0C 00084E0C  2C 1F 00 00 */	cmpwi r31, 0
/* 80089F10 00084E10  40 81 00 0C */	ble lbl_80089F1C
/* 80089F14 00084E14  7F C3 F3 78 */	mr r3, r30
/* 80089F18 00084E18  48 01 93 6D */	bl __dl__FPv
lbl_80089F1C:
/* 80089F1C 00084E1C  7F C3 F3 78 */	mr r3, r30
/* 80089F20 00084E20  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80089F24 00084E24  83 C1 00 08 */	lwz r30, 8(r1)
/* 80089F28 00084E28  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80089F2C 00084E2C  7C 08 03 A6 */	mtlr r0
/* 80089F30 00084E30  38 21 00 10 */	addi r1, r1, 0x10
/* 80089F34 00084E34  4E 80 00 20 */	blr 

.global lbl_80089F38
lbl_80089F38:
/* 80089F38 00084E38  88 03 00 00 */	lbz r0, 0(r3)
/* 80089F3C 00084E3C  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 80089F40 00084E40  4D 82 00 20 */	beqlr 
/* 80089F44 00084E44  81 83 00 6C */	lwz r12, 0x6c(r3)
/* 80089F48 00084E48  81 8C 00 28 */	lwz r12, 0x28(r12)
/* 80089F4C 00084E4C  7D 89 03 A6 */	mtctr r12
/* 80089F50 00084E50  4E 80 04 20 */	bctr 
/* 80089F54 00084E54  4E 80 00 20 */	blr 

/* 80089F58 00084E58  38 63 FF 90 */	addi r3, r3, -112
/* 80089F5C 00084E5C  4B FF FF 80 */	b lbl_80089EDC

/* 80089F60 00084E60  38 63 FF 90 */	addi r3, r3, -112
/* 80089F64 00084E64  4B FF FF D4 */	b lbl_80089F38
