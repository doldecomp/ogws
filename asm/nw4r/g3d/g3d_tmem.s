.include "macros.inc"

.section .sbss, "wa"
.balign 8
.global sTMemCachePlan
sTMemCachePlan:
	.skip 0x4
.global sTlutRegionNum
sTlutRegionNum:
	.skip 0x4
.global sfpDefaultTexRegionCallback
sfpDefaultTexRegionCallback:
	.skip 0x4
.global sfpDefaultTlutRegionCallback
sfpDefaultTlutRegionCallback:
	.skip 0x4

.section .bss, "wa"
.balign 8
.global saaTexRegion
saaTexRegion:
	.skip 0x300

# Size = 0x140 according to linker map
.global saaTlutRegion
saaTlutRegion:
	.skip 0x158

.section .rodata, "a"
.balign 8
.global scaaaTexRegionAddr
scaaaTexRegionAddr:
	.incbin "baserom.dol", 0x374410, 0x3C0
.global scaaaTexRegionSize
scaaaTexRegionSize:
	.incbin "baserom.dol", 0x3747D0, 0x3C0

.section .text, "ax"
.global SetTMemLayout__Q34nw4r3g3d4tmemFQ44nw4r3g3d4tmem10TMemLayout
SetTMemLayout__Q34nw4r3g3d4tmemFQ44nw4r3g3d4tmem10TMemLayout:
/* 80063BCC 0005EACC  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80063BD0 0005EAD0  7C 08 02 A6 */	mflr r0
/* 80063BD4 0005EAD4  90 01 00 24 */	stw r0, 0x24(r1)
/* 80063BD8 0005EAD8  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80063BDC 0005EADC  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80063BE0 0005EAE0  93 A1 00 14 */	stw r29, 0x14(r1)
/* 80063BE4 0005EAE4  93 81 00 10 */	stw r28, 0x10(r1)
/* 80063BE8 0005EAE8  7C 7C 1B 78 */	mr r28, r3
/* 80063BEC 0005EAEC  80 0D 97 C8 */	lwz r0, sfpDefaultTexRegionCallback-_SDA_BASE_(r13)
/* 80063BF0 0005EAF0  2C 00 00 00 */	cmpwi r0, 0
/* 80063BF4 0005EAF4  40 82 00 2C */	bne lbl_80063C20
/* 80063BF8 0005EAF8  3C 60 80 06 */	lis r3, TexRegionCallback__FPC9_GXTexObj11_GXTexMapID@ha
/* 80063BFC 0005EAFC  38 63 3C C8 */	addi r3, r3, TexRegionCallback__FPC9_GXTexObj11_GXTexMapID@l
/* 80063C00 0005EB00  48 07 CE E5 */	bl GXSetTexRegionCallback
/* 80063C04 0005EB04  90 6D 97 C8 */	stw r3, sfpDefaultTexRegionCallback-_SDA_BASE_(r13)
/* 80063C08 0005EB08  48 07 CE DD */	bl GXSetTexRegionCallback
/* 80063C0C 0005EB0C  3C 60 80 06 */	lis r3, TlutRegionCallback__FUl@ha
/* 80063C10 0005EB10  38 63 3D 9C */	addi r3, r3, TlutRegionCallback__FUl@l
/* 80063C14 0005EB14  48 07 CE E5 */	bl GXSetTlutRegionCallback
/* 80063C18 0005EB18  90 6D 97 CC */	stw r3, sfpDefaultTlutRegionCallback-_SDA_BASE_(r13)
/* 80063C1C 0005EB1C  48 07 CE DD */	bl GXSetTlutRegionCallback
lbl_80063C20:
/* 80063C20 0005EB20  80 0D 97 C8 */	lwz r0, sfpDefaultTexRegionCallback-_SDA_BASE_(r13)
/* 80063C24 0005EB24  2C 00 00 00 */	cmpwi r0, 0
/* 80063C28 0005EB28  41 82 00 80 */	beq lbl_80063CA8
/* 80063C2C 0005EB2C  93 8D 97 C0 */	stw r28, sTMemCachePlan-_SDA_BASE_(r13)
/* 80063C30 0005EB30  7F 83 E3 78 */	mr r3, r28
/* 80063C34 0005EB34  48 00 01 91 */	bl setTexRegion___F13TMemCachePlan
/* 80063C38 0005EB38  2C 1C 00 02 */	cmpwi r28, 2
/* 80063C3C 0005EB3C  41 82 00 20 */	beq lbl_80063C5C
/* 80063C40 0005EB40  40 80 00 68 */	bge lbl_80063CA8
/* 80063C44 0005EB44  2C 1C 00 00 */	cmpwi r28, 0
/* 80063C48 0005EB48  40 80 00 08 */	bge lbl_80063C50
/* 80063C4C 0005EB4C  48 00 00 5C */	b lbl_80063CA8
lbl_80063C50:
/* 80063C50 0005EB50  80 6D 97 CC */	lwz r3, sfpDefaultTlutRegionCallback-_SDA_BASE_(r13)
/* 80063C54 0005EB54  48 07 CE A5 */	bl GXSetTlutRegionCallback
/* 80063C58 0005EB58  48 00 00 50 */	b lbl_80063CA8
lbl_80063C5C:
/* 80063C5C 0005EB5C  3F 80 80 3F */	lis r28, saaTlutRegion@ha
/* 80063C60 0005EB60  3B C0 00 00 */	li r30, 0
/* 80063C64 0005EB64  3B 9C BF C8 */	addi r28, r28, saaTlutRegion@l
/* 80063C68 0005EB68  3B E0 00 00 */	li r31, 0
/* 80063C6C 0005EB6C  3F A0 00 0F */	lis r29, 0xf
lbl_80063C70:
/* 80063C70 0005EB70  7F 83 E3 78 */	mr r3, r28
/* 80063C74 0005EB74  7F A4 EB 78 */	mr r4, r29
/* 80063C78 0005EB78  38 A0 00 10 */	li r5, 0x10
/* 80063C7C 0005EB7C  48 07 CE 01 */	bl GXInitTlutRegion
/* 80063C80 0005EB80  3B FF 00 01 */	addi r31, r31, 1
/* 80063C84 0005EB84  3B DE 00 01 */	addi r30, r30, 1
/* 80063C88 0005EB88  2C 1F 00 08 */	cmpwi r31, 8
/* 80063C8C 0005EB8C  3B BD 20 00 */	addi r29, r29, 0x2000
/* 80063C90 0005EB90  3B 9C 00 10 */	addi r28, r28, 0x10
/* 80063C94 0005EB94  41 80 FF DC */	blt lbl_80063C70
/* 80063C98 0005EB98  3C 60 80 06 */	lis r3, TlutRegionCallback__FUl@ha
/* 80063C9C 0005EB9C  93 CD 97 C4 */	stw r30, sTlutRegionNum-_SDA_BASE_(r13)
/* 80063CA0 0005EBA0  38 63 3D 9C */	addi r3, r3, TlutRegionCallback__FUl@l
/* 80063CA4 0005EBA4  48 07 CE 55 */	bl GXSetTlutRegionCallback
lbl_80063CA8:
/* 80063CA8 0005EBA8  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80063CAC 0005EBAC  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80063CB0 0005EBB0  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80063CB4 0005EBB4  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 80063CB8 0005EBB8  83 81 00 10 */	lwz r28, 0x10(r1)
/* 80063CBC 0005EBBC  7C 08 03 A6 */	mtlr r0
/* 80063CC0 0005EBC0  38 21 00 20 */	addi r1, r1, 0x20
/* 80063CC4 0005EBC4  4E 80 00 20 */	blr 

.global TexRegionCallback__FPC9_GXTexObj11_GXTexMapID
TexRegionCallback__FPC9_GXTexObj11_GXTexMapID:
/* 80063CC8 0005EBC8  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80063CCC 0005EBCC  7C 08 02 A6 */	mflr r0
/* 80063CD0 0005EBD0  90 01 00 24 */	stw r0, 0x24(r1)
/* 80063CD4 0005EBD4  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80063CD8 0005EBD8  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80063CDC 0005EBDC  7C 9E 23 78 */	mr r30, r4
/* 80063CE0 0005EBE0  93 A1 00 14 */	stw r29, 0x14(r1)
/* 80063CE4 0005EBE4  7C 7D 1B 78 */	mr r29, r3
/* 80063CE8 0005EBE8  48 07 C9 55 */	bl GXGetTexObjFmt
/* 80063CEC 0005EBEC  7C 7F 1B 78 */	mr r31, r3
/* 80063CF0 0005EBF0  7F A3 EB 78 */	mr r3, r29
/* 80063CF4 0005EBF4  48 07 C9 69 */	bl GXGetTexObjMipMap
/* 80063CF8 0005EBF8  2C 1F 00 07 */	cmpwi r31, 7
/* 80063CFC 0005EBFC  41 82 00 68 */	beq lbl_80063D64
/* 80063D00 0005EC00  40 80 00 10 */	bge lbl_80063D10
/* 80063D04 0005EC04  2C 1F 00 06 */	cmpwi r31, 6
/* 80063D08 0005EC08  40 80 00 14 */	bge lbl_80063D1C
/* 80063D0C 0005EC0C  48 00 00 58 */	b lbl_80063D64
lbl_80063D10:
/* 80063D10 0005EC10  2C 1F 00 0B */	cmpwi r31, 0xb
/* 80063D14 0005EC14  40 80 00 50 */	bge lbl_80063D64
/* 80063D18 0005EC18  48 00 00 28 */	b lbl_80063D40
lbl_80063D1C:
/* 80063D1C 0005EC1C  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 80063D20 0005EC20  3C 60 80 3F */	lis r3, saaTexRegion@ha
/* 80063D24 0005EC24  57 C0 20 36 */	slwi r0, r30, 4
/* 80063D28 0005EC28  38 63 BC C8 */	addi r3, r3, saaTexRegion@l
/* 80063D2C 0005EC2C  7C 83 02 14 */	add r4, r3, r0
/* 80063D30 0005EC30  38 64 02 00 */	addi r3, r4, 0x200
/* 80063D34 0005EC34  41 82 00 4C */	beq lbl_80063D80
/* 80063D38 0005EC38  38 64 02 80 */	addi r3, r4, 0x280
/* 80063D3C 0005EC3C  48 00 00 44 */	b lbl_80063D80
lbl_80063D40:
/* 80063D40 0005EC40  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 80063D44 0005EC44  3C 60 80 3F */	lis r3, saaTexRegion@ha
/* 80063D48 0005EC48  57 C0 20 36 */	slwi r0, r30, 4
/* 80063D4C 0005EC4C  38 63 BC C8 */	addi r3, r3, saaTexRegion@l
/* 80063D50 0005EC50  7C 83 02 14 */	add r4, r3, r0
/* 80063D54 0005EC54  38 64 01 00 */	addi r3, r4, 0x100
/* 80063D58 0005EC58  41 82 00 28 */	beq lbl_80063D80
/* 80063D5C 0005EC5C  38 64 01 80 */	addi r3, r4, 0x180
/* 80063D60 0005EC60  48 00 00 20 */	b lbl_80063D80
lbl_80063D64:
/* 80063D64 0005EC64  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 80063D68 0005EC68  3C 60 80 3F */	lis r3, saaTexRegion@ha
/* 80063D6C 0005EC6C  57 C0 20 36 */	slwi r0, r30, 4
/* 80063D70 0005EC70  38 63 BC C8 */	addi r3, r3, saaTexRegion@l
/* 80063D74 0005EC74  7C 63 02 14 */	add r3, r3, r0
/* 80063D78 0005EC78  41 82 00 08 */	beq lbl_80063D80
/* 80063D7C 0005EC7C  38 63 00 80 */	addi r3, r3, 0x80
lbl_80063D80:
/* 80063D80 0005EC80  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80063D84 0005EC84  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80063D88 0005EC88  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80063D8C 0005EC8C  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 80063D90 0005EC90  7C 08 03 A6 */	mtlr r0
/* 80063D94 0005EC94  38 21 00 20 */	addi r1, r1, 0x20
/* 80063D98 0005EC98  4E 80 00 20 */	blr 

.global TlutRegionCallback__FUl
TlutRegionCallback__FUl:
/* 80063D9C 0005EC9C  80 0D 97 C4 */	lwz r0, sTlutRegionNum-_SDA_BASE_(r13)
/* 80063DA0 0005ECA0  38 80 00 00 */	li r4, 0
/* 80063DA4 0005ECA4  7C 03 00 40 */	cmplw r3, r0
/* 80063DA8 0005ECA8  40 80 00 14 */	bge lbl_80063DBC
/* 80063DAC 0005ECAC  3C 80 80 3F */	lis r4, saaTlutRegion@ha
/* 80063DB0 0005ECB0  54 60 20 36 */	slwi r0, r3, 4
/* 80063DB4 0005ECB4  38 84 BF C8 */	addi r4, r4, saaTlutRegion@l
/* 80063DB8 0005ECB8  7C 84 02 14 */	add r4, r4, r0
lbl_80063DBC:
/* 80063DBC 0005ECBC  7C 83 23 78 */	mr r3, r4
/* 80063DC0 0005ECC0  4E 80 00 20 */	blr 

.global setTexRegion___F13TMemCachePlan
setTexRegion___F13TMemCachePlan:
/* 80063DC4 0005ECC4  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 80063DC8 0005ECC8  7C 08 02 A6 */	mflr r0
/* 80063DCC 0005ECCC  90 01 00 34 */	stw r0, 0x34(r1)
/* 80063DD0 0005ECD0  39 61 00 30 */	addi r11, r1, 0x30
/* 80063DD4 0005ECD4  48 04 DF 61 */	bl _savegpr_23
/* 80063DD8 0005ECD8  2C 03 00 00 */	cmpwi r3, 0
/* 80063DDC 0005ECDC  40 82 00 10 */	bne lbl_80063DEC
/* 80063DE0 0005ECE0  80 6D 97 C8 */	lwz r3, sfpDefaultTexRegionCallback-_SDA_BASE_(r13)
/* 80063DE4 0005ECE4  48 07 CD 01 */	bl GXSetTexRegionCallback
/* 80063DE8 0005ECE8  48 00 01 24 */	b lbl_80063F0C
lbl_80063DEC:
/* 80063DEC 0005ECEC  38 03 FF FF */	addi r0, r3, -1
/* 80063DF0 0005ECF0  3C 80 80 38 */	lis r4, scaaaTexRegionSize@ha
/* 80063DF4 0005ECF4  1C 00 01 40 */	mulli r0, r0, 0x140
/* 80063DF8 0005ECF8  3C 60 80 38 */	lis r3, scaaaTexRegionAddr@ha
/* 80063DFC 0005ECFC  3F A0 80 3F */	lis r29, saaTexRegion@ha
/* 80063E00 0005ED00  38 84 86 D0 */	addi r4, r4, scaaaTexRegionSize@l
/* 80063E04 0005ED04  3B BD BC C8 */	addi r29, r29, saaTexRegion@l
/* 80063E08 0005ED08  38 63 83 10 */	addi r3, r3, scaaaTexRegionAddr@l
/* 80063E0C 0005ED0C  7F E4 02 14 */	add r31, r4, r0
/* 80063E10 0005ED10  3A E0 00 00 */	li r23, 0
/* 80063E14 0005ED14  7F C3 02 14 */	add r30, r3, r0
/* 80063E18 0005ED18  3B 9D 00 80 */	addi r28, r29, 0x80
/* 80063E1C 0005ED1C  3B 7D 01 00 */	addi r27, r29, 0x100
/* 80063E20 0005ED20  3B 5D 01 80 */	addi r26, r29, 0x180
/* 80063E24 0005ED24  3B 3D 02 00 */	addi r25, r29, 0x200
/* 80063E28 0005ED28  3B 1D 02 80 */	addi r24, r29, 0x280
lbl_80063E2C:
/* 80063E2C 0005ED2C  80 BE 00 00 */	lwz r5, 0(r30)
/* 80063E30 0005ED30  7F A3 EB 78 */	mr r3, r29
/* 80063E34 0005ED34  80 DF 00 00 */	lwz r6, 0(r31)
/* 80063E38 0005ED38  38 80 00 00 */	li r4, 0
/* 80063E3C 0005ED3C  38 E0 00 00 */	li r7, 0
/* 80063E40 0005ED40  39 00 00 03 */	li r8, 3
/* 80063E44 0005ED44  48 07 CB 85 */	bl GXInitTexCacheRegion
/* 80063E48 0005ED48  80 BE 00 20 */	lwz r5, 0x20(r30)
/* 80063E4C 0005ED4C  7F 83 E3 78 */	mr r3, r28
/* 80063E50 0005ED50  80 DF 00 20 */	lwz r6, 0x20(r31)
/* 80063E54 0005ED54  38 80 00 00 */	li r4, 0
/* 80063E58 0005ED58  80 FE 00 40 */	lwz r7, 0x40(r30)
/* 80063E5C 0005ED5C  81 1F 00 40 */	lwz r8, 0x40(r31)
/* 80063E60 0005ED60  48 07 CB 69 */	bl GXInitTexCacheRegion
/* 80063E64 0005ED64  80 BE 00 60 */	lwz r5, 0x60(r30)
/* 80063E68 0005ED68  7F 63 DB 78 */	mr r3, r27
/* 80063E6C 0005ED6C  80 DF 00 60 */	lwz r6, 0x60(r31)
/* 80063E70 0005ED70  38 80 00 00 */	li r4, 0
/* 80063E74 0005ED74  38 E0 00 00 */	li r7, 0
/* 80063E78 0005ED78  39 00 00 03 */	li r8, 3
/* 80063E7C 0005ED7C  48 07 CB 4D */	bl GXInitTexCacheRegion
/* 80063E80 0005ED80  80 BE 00 80 */	lwz r5, 0x80(r30)
/* 80063E84 0005ED84  7F 43 D3 78 */	mr r3, r26
/* 80063E88 0005ED88  80 DF 00 80 */	lwz r6, 0x80(r31)
/* 80063E8C 0005ED8C  38 80 00 00 */	li r4, 0
/* 80063E90 0005ED90  80 FE 00 A0 */	lwz r7, 0xa0(r30)
/* 80063E94 0005ED94  81 1F 00 A0 */	lwz r8, 0xa0(r31)
/* 80063E98 0005ED98  48 07 CB 31 */	bl GXInitTexCacheRegion
/* 80063E9C 0005ED9C  80 BE 00 C0 */	lwz r5, 0xc0(r30)
/* 80063EA0 0005EDA0  7F 23 CB 78 */	mr r3, r25
/* 80063EA4 0005EDA4  80 DF 00 C0 */	lwz r6, 0xc0(r31)
/* 80063EA8 0005EDA8  38 80 00 00 */	li r4, 0
/* 80063EAC 0005EDAC  80 FE 00 E0 */	lwz r7, 0xe0(r30)
/* 80063EB0 0005EDB0  81 1F 00 E0 */	lwz r8, 0xe0(r31)
/* 80063EB4 0005EDB4  48 07 CB 15 */	bl GXInitTexCacheRegion
/* 80063EB8 0005EDB8  80 BE 01 00 */	lwz r5, 0x100(r30)
/* 80063EBC 0005EDBC  7F 03 C3 78 */	mr r3, r24
/* 80063EC0 0005EDC0  80 DF 01 00 */	lwz r6, 0x100(r31)
/* 80063EC4 0005EDC4  38 80 00 00 */	li r4, 0
/* 80063EC8 0005EDC8  80 FE 01 20 */	lwz r7, 0x120(r30)
/* 80063ECC 0005EDCC  81 1F 01 20 */	lwz r8, 0x120(r31)
/* 80063ED0 0005EDD0  48 07 CA F9 */	bl GXInitTexCacheRegion
/* 80063ED4 0005EDD4  3A F7 00 01 */	addi r23, r23, 1
/* 80063ED8 0005EDD8  3B DE 00 04 */	addi r30, r30, 4
/* 80063EDC 0005EDDC  2C 17 00 08 */	cmpwi r23, 8
/* 80063EE0 0005EDE0  3B BD 00 10 */	addi r29, r29, 0x10
/* 80063EE4 0005EDE4  3B 9C 00 10 */	addi r28, r28, 0x10
/* 80063EE8 0005EDE8  3B 7B 00 10 */	addi r27, r27, 0x10
/* 80063EEC 0005EDEC  3B 5A 00 10 */	addi r26, r26, 0x10
/* 80063EF0 0005EDF0  3B 39 00 10 */	addi r25, r25, 0x10
/* 80063EF4 0005EDF4  3B 18 00 10 */	addi r24, r24, 0x10
/* 80063EF8 0005EDF8  3B FF 00 04 */	addi r31, r31, 4
/* 80063EFC 0005EDFC  41 80 FF 30 */	blt lbl_80063E2C
/* 80063F00 0005EE00  3C 60 80 06 */	lis r3, TexRegionCallback__FPC9_GXTexObj11_GXTexMapID@ha
/* 80063F04 0005EE04  38 63 3C C8 */	addi r3, r3, TexRegionCallback__FPC9_GXTexObj11_GXTexMapID@l
/* 80063F08 0005EE08  48 07 CB DD */	bl GXSetTexRegionCallback
lbl_80063F0C:
/* 80063F0C 0005EE0C  39 61 00 30 */	addi r11, r1, 0x30
/* 80063F10 0005EE10  48 04 DE 71 */	bl _restgpr_23
/* 80063F14 0005EE14  80 01 00 34 */	lwz r0, 0x34(r1)
/* 80063F18 0005EE18  7C 08 03 A6 */	mtlr r0
/* 80063F1C 0005EE1C  38 21 00 30 */	addi r1, r1, 0x30
/* 80063F20 0005EE20  4E 80 00 20 */	blr 
