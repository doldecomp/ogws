.include "macros.inc"

.section .data, "wa"
.balign 0x8
lbl_803b7670:
	.incbin "baserom.dol", 0x3B3770, 0x4C
.global lbl_803B76BC
lbl_803B76BC:
	.incbin "baserom.dol", 0x3B37BC, 0x10
.global lbl_803B76CC
lbl_803B76CC:
	.incbin "baserom.dol", 0x3B37CC, 0x9

.section .sdata, "wa"
.balign 0x8
MBoxDir:
	.incbin "baserom.dol", 0x3C7650, 0x4
ConfigFile:
	.incbin "baserom.dol", 0x3C7654, 0x4
CfgBakFile:
	.incbin "baserom.dol", 0x3C7658, 0x4

.section .sbss, "wa"
.balign 0x8
config:
	.skip 0x4
ConfigModified:
	.skip 0x4

.section .text, "ax"
.global NWC24GetMyUserId
NWC24GetMyUserId:
/* 80143DD0 0013ECD0  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80143DD4 0013ECD4  7C 08 02 A6 */	mflr r0
/* 80143DD8 0013ECD8  90 01 00 24 */	stw r0, 0x24(r1)
/* 80143DDC 0013ECDC  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80143DE0 0013ECE0  3B E0 00 00 */	li r31, 0
/* 80143DE4 0013ECE4  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80143DE8 0013ECE8  7C 7E 1B 78 */	mr r30, r3
/* 80143DEC 0013ECEC  48 00 0A 95 */	bl NWC24IsMsgLibOpened
/* 80143DF0 0013ECF0  2C 03 00 00 */	cmpwi r3, 0
/* 80143DF4 0013ECF4  40 82 00 10 */	bne lbl_80143E04
/* 80143DF8 0013ECF8  48 00 0A 9D */	bl NWC24IsMsgLibOpenedByTool
/* 80143DFC 0013ECFC  2C 03 00 00 */	cmpwi r3, 0
/* 80143E00 0013ED00  41 82 00 1C */	beq lbl_80143E1C
lbl_80143E04:
/* 80143E04 0013ED04  80 6D A0 88 */	lwz r3, config-_SDA_BASE_(r13)
/* 80143E08 0013ED08  80 03 00 08 */	lwz r0, 8(r3)
/* 80143E0C 0013ED0C  80 63 00 0C */	lwz r3, 0xc(r3)
/* 80143E10 0013ED10  90 7E 00 04 */	stw r3, 4(r30)
/* 80143E14 0013ED14  90 1E 00 00 */	stw r0, 0(r30)
/* 80143E18 0013ED18  48 00 00 B0 */	b lbl_80143EC8
lbl_80143E1C:
/* 80143E1C 0013ED1C  48 00 52 4D */	bl NWC24SuspendScheduler
/* 80143E20 0013ED20  2C 03 00 00 */	cmpwi r3, 0
/* 80143E24 0013ED24  40 80 00 08 */	bge lbl_80143E2C
/* 80143E28 0013ED28  48 00 00 A4 */	b lbl_80143ECC
lbl_80143E2C:
/* 80143E2C 0013ED2C  38 60 00 01 */	li r3, 1
/* 80143E30 0013ED30  48 00 0A 79 */	bl NWC24BlockOpenMsgLib
/* 80143E34 0013ED34  2C 03 00 00 */	cmpwi r3, 0
/* 80143E38 0013ED38  40 80 00 08 */	bge lbl_80143E40
/* 80143E3C 0013ED3C  48 00 00 5C */	b lbl_80143E98
lbl_80143E40:
/* 80143E40 0013ED40  38 00 00 00 */	li r0, 0
/* 80143E44 0013ED44  2C 1E 00 00 */	cmpwi r30, 0
/* 80143E48 0013ED48  90 01 00 08 */	stw r0, 8(r1)
/* 80143E4C 0013ED4C  40 82 00 0C */	bne lbl_80143E58
/* 80143E50 0013ED50  3B E0 FF FD */	li r31, -3
/* 80143E54 0013ED54  48 00 00 2C */	b lbl_80143E80
lbl_80143E58:
/* 80143E58 0013ED58  3C 60 6F C1 */	lis r3, 0x6FC0FFFF@ha
/* 80143E5C 0013ED5C  3C 80 00 24 */	lis r4, 0x002386F2@ha
/* 80143E60 0013ED60  38 A3 FF FF */	addi r5, r3, 0x6FC0FFFF@l
/* 80143E64 0013ED64  38 04 86 F2 */	addi r0, r4, 0x002386F2@l
/* 80143E68 0013ED68  90 BE 00 04 */	stw r5, 4(r30)
/* 80143E6C 0013ED6C  7F C3 F3 78 */	mr r3, r30
/* 80143E70 0013ED70  38 81 00 08 */	addi r4, r1, 8
/* 80143E74 0013ED74  90 1E 00 00 */	stw r0, 0(r30)
/* 80143E78 0013ED78  48 00 53 B1 */	bl NWC24iRequestGenerateUserId
/* 80143E7C 0013ED7C  7C 7F 1B 78 */	mr r31, r3
lbl_80143E80:
/* 80143E80 0013ED80  38 60 00 00 */	li r3, 0
/* 80143E84 0013ED84  48 00 0A 25 */	bl NWC24BlockOpenMsgLib
/* 80143E88 0013ED88  2C 1F 00 00 */	cmpwi r31, 0
/* 80143E8C 0013ED8C  41 80 00 08 */	blt lbl_80143E94
/* 80143E90 0013ED90  7C 7F 1B 78 */	mr r31, r3
lbl_80143E94:
/* 80143E94 0013ED94  7F E3 FB 78 */	mr r3, r31
lbl_80143E98:
/* 80143E98 0013ED98  38 03 00 24 */	addi r0, r3, 0x24
/* 80143E9C 0013ED9C  7C 7F 1B 78 */	mr r31, r3
/* 80143EA0 0013EDA0  28 00 00 01 */	cmplwi r0, 1
/* 80143EA4 0013EDA4  41 81 00 08 */	bgt lbl_80143EAC
/* 80143EA8 0013EDA8  3B E0 00 00 */	li r31, 0
lbl_80143EAC:
/* 80143EAC 0013EDAC  48 00 52 8D */	bl NWC24ResumeScheduler
/* 80143EB0 0013EDB0  2C 03 00 00 */	cmpwi r3, 0
/* 80143EB4 0013EDB4  40 80 00 14 */	bge lbl_80143EC8
/* 80143EB8 0013EDB8  2C 1F 00 00 */	cmpwi r31, 0
/* 80143EBC 0013EDBC  41 82 00 08 */	beq lbl_80143EC4
/* 80143EC0 0013EDC0  7F E3 FB 78 */	mr r3, r31
lbl_80143EC4:
/* 80143EC4 0013EDC4  7C 7F 1B 78 */	mr r31, r3
lbl_80143EC8:
/* 80143EC8 0013EDC8  7F E3 FB 78 */	mr r3, r31
lbl_80143ECC:
/* 80143ECC 0013EDCC  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80143ED0 0013EDD0  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80143ED4 0013EDD4  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80143ED8 0013EDD8  7C 08 03 A6 */	mtlr r0
/* 80143EDC 0013EDDC  38 21 00 20 */	addi r1, r1, 0x20
/* 80143EE0 0013EDE0  4E 80 00 20 */	blr 

.global NWC24iConfigOpen
NWC24iConfigOpen:
/* 80143EE4 0013EDE4  80 6D A0 90 */	lwz r3, NWC24WorkP-_SDA_BASE_(r13)
/* 80143EE8 0013EDE8  38 00 00 00 */	li r0, 0
/* 80143EEC 0013EDEC  90 0D A0 8C */	stw r0, ConfigModified-_SDA_BASE_(r13)
/* 80143EF0 0013EDF0  38 03 0D 00 */	addi r0, r3, 0xd00
/* 80143EF4 0013EDF4  90 0D A0 88 */	stw r0, config-_SDA_BASE_(r13)
/* 80143EF8 0013EDF8  48 00 00 04 */	b lbl_80143EFC
lbl_80143EFC:
/* 80143EFC 0013EDFC  94 21 FF 50 */	stwu r1, -0xb0(r1)
/* 80143F00 0013EE00  7C 08 02 A6 */	mflr r0
/* 80143F04 0013EE04  90 01 00 B4 */	stw r0, 0xb4(r1)
/* 80143F08 0013EE08  93 E1 00 AC */	stw r31, 0xac(r1)
/* 80143F0C 0013EE0C  80 0D A0 90 */	lwz r0, NWC24WorkP-_SDA_BASE_(r13)
/* 80143F10 0013EE10  2C 00 00 00 */	cmpwi r0, 0
/* 80143F14 0013EE14  40 82 00 0C */	bne lbl_80143F20
/* 80143F18 0013EE18  38 60 FF F7 */	li r3, -9
/* 80143F1C 0013EE1C  48 00 00 C0 */	b lbl_80143FDC
lbl_80143F20:
/* 80143F20 0013EE20  80 8D 86 54 */	lwz r4, ConfigFile-_SDA_BASE_(r13)
/* 80143F24 0013EE24  38 61 00 08 */	addi r3, r1, 8
/* 80143F28 0013EE28  38 A0 00 02 */	li r5, 2
/* 80143F2C 0013EE2C  4B FF EB F9 */	bl NWC24FOpen
/* 80143F30 0013EE30  2C 03 00 00 */	cmpwi r3, 0
/* 80143F34 0013EE34  40 82 00 2C */	bne lbl_80143F60
/* 80143F38 0013EE38  80 6D A0 88 */	lwz r3, config-_SDA_BASE_(r13)
/* 80143F3C 0013EE3C  38 A1 00 08 */	addi r5, r1, 8
/* 80143F40 0013EE40  38 80 04 00 */	li r4, 0x400
/* 80143F44 0013EE44  4B FF F2 B1 */	bl NWC24FRead
/* 80143F48 0013EE48  7C 7F 1B 78 */	mr r31, r3
/* 80143F4C 0013EE4C  38 61 00 08 */	addi r3, r1, 8
/* 80143F50 0013EE50  4B FF EF 25 */	bl NWC24FClose
/* 80143F54 0013EE54  2C 1F 00 00 */	cmpwi r31, 0
/* 80143F58 0013EE58  41 82 00 08 */	beq lbl_80143F60
/* 80143F5C 0013EE5C  7F E3 FB 78 */	mr r3, r31
lbl_80143F60:
/* 80143F60 0013EE60  2C 03 00 00 */	cmpwi r3, 0
/* 80143F64 0013EE64  40 82 00 1C */	bne lbl_80143F80
/* 80143F68 0013EE68  48 00 03 75 */	bl CheckConfig
/* 80143F6C 0013EE6C  2C 03 00 00 */	cmpwi r3, 0
/* 80143F70 0013EE70  40 82 00 10 */	bne lbl_80143F80
/* 80143F74 0013EE74  38 00 00 00 */	li r0, 0
/* 80143F78 0013EE78  90 0D A0 8C */	stw r0, ConfigModified-_SDA_BASE_(r13)
/* 80143F7C 0013EE7C  48 00 00 60 */	b lbl_80143FDC
lbl_80143F80:
/* 80143F80 0013EE80  80 8D 86 58 */	lwz r4, CfgBakFile-_SDA_BASE_(r13)
/* 80143F84 0013EE84  38 61 00 08 */	addi r3, r1, 8
/* 80143F88 0013EE88  38 A0 00 02 */	li r5, 2
/* 80143F8C 0013EE8C  4B FF EB 99 */	bl NWC24FOpen
/* 80143F90 0013EE90  2C 03 00 00 */	cmpwi r3, 0
/* 80143F94 0013EE94  40 82 00 2C */	bne lbl_80143FC0
/* 80143F98 0013EE98  80 6D A0 88 */	lwz r3, config-_SDA_BASE_(r13)
/* 80143F9C 0013EE9C  38 A1 00 08 */	addi r5, r1, 8
/* 80143FA0 0013EEA0  38 80 04 00 */	li r4, 0x400
/* 80143FA4 0013EEA4  4B FF F2 51 */	bl NWC24FRead
/* 80143FA8 0013EEA8  7C 7F 1B 78 */	mr r31, r3
/* 80143FAC 0013EEAC  38 61 00 08 */	addi r3, r1, 8
/* 80143FB0 0013EEB0  4B FF EE C5 */	bl NWC24FClose
/* 80143FB4 0013EEB4  2C 1F 00 00 */	cmpwi r31, 0
/* 80143FB8 0013EEB8  41 82 00 08 */	beq lbl_80143FC0
/* 80143FBC 0013EEBC  7F E3 FB 78 */	mr r3, r31
lbl_80143FC0:
/* 80143FC0 0013EEC0  2C 03 00 00 */	cmpwi r3, 0
/* 80143FC4 0013EEC4  40 82 00 18 */	bne lbl_80143FDC
/* 80143FC8 0013EEC8  48 00 03 15 */	bl CheckConfig
/* 80143FCC 0013EECC  2C 03 00 00 */	cmpwi r3, 0
/* 80143FD0 0013EED0  40 82 00 0C */	bne lbl_80143FDC
/* 80143FD4 0013EED4  38 00 00 01 */	li r0, 1
/* 80143FD8 0013EED8  90 0D A0 8C */	stw r0, ConfigModified-_SDA_BASE_(r13)
lbl_80143FDC:
/* 80143FDC 0013EEDC  80 01 00 B4 */	lwz r0, 0xb4(r1)
/* 80143FE0 0013EEE0  83 E1 00 AC */	lwz r31, 0xac(r1)
/* 80143FE4 0013EEE4  7C 08 03 A6 */	mtlr r0
/* 80143FE8 0013EEE8  38 21 00 B0 */	addi r1, r1, 0xb0
/* 80143FEC 0013EEEC  4E 80 00 20 */	blr 

.global NWC24iConfigFlush
NWC24iConfigFlush:
/* 80143FF0 0013EEF0  94 21 FF 50 */	stwu r1, -0xb0(r1)
/* 80143FF4 0013EEF4  7C 08 02 A6 */	mflr r0
/* 80143FF8 0013EEF8  90 01 00 B4 */	stw r0, 0xb4(r1)
/* 80143FFC 0013EEFC  93 E1 00 AC */	stw r31, 0xac(r1)
/* 80144000 0013EF00  80 0D A0 90 */	lwz r0, NWC24WorkP-_SDA_BASE_(r13)
/* 80144004 0013EF04  2C 00 00 00 */	cmpwi r0, 0
/* 80144008 0013EF08  40 82 00 0C */	bne lbl_80144014
/* 8014400C 0013EF0C  38 60 FF F7 */	li r3, -9
/* 80144010 0013EF10  48 00 01 4C */	b lbl_8014415C
lbl_80144014:
/* 80144014 0013EF14  80 0D A0 8C */	lwz r0, ConfigModified-_SDA_BASE_(r13)
/* 80144018 0013EF18  2C 00 00 00 */	cmpwi r0, 0
/* 8014401C 0013EF1C  40 82 00 0C */	bne lbl_80144028
/* 80144020 0013EF20  38 60 00 00 */	li r3, 0
/* 80144024 0013EF24  48 00 01 38 */	b lbl_8014415C
lbl_80144028:
/* 80144028 0013EF28  81 0D A0 88 */	lwz r8, config-_SDA_BASE_(r13)
/* 8014402C 0013EF2C  38 00 00 1F */	li r0, 0x1f
/* 80144030 0013EF30  38 E0 00 00 */	li r7, 0
/* 80144034 0013EF34  7D 06 43 78 */	mr r6, r8
/* 80144038 0013EF38  7C 09 03 A6 */	mtctr r0
lbl_8014403C:
/* 8014403C 0013EF3C  80 66 00 00 */	lwz r3, 0(r6)
/* 80144040 0013EF40  80 06 00 04 */	lwz r0, 4(r6)
/* 80144044 0013EF44  7C E7 1A 14 */	add r7, r7, r3
/* 80144048 0013EF48  80 66 00 08 */	lwz r3, 8(r6)
/* 8014404C 0013EF4C  7C E7 02 14 */	add r7, r7, r0
/* 80144050 0013EF50  80 06 00 0C */	lwz r0, 0xc(r6)
/* 80144054 0013EF54  7C E7 1A 14 */	add r7, r7, r3
/* 80144058 0013EF58  80 66 00 10 */	lwz r3, 0x10(r6)
/* 8014405C 0013EF5C  7C E7 02 14 */	add r7, r7, r0
/* 80144060 0013EF60  80 06 00 14 */	lwz r0, 0x14(r6)
/* 80144064 0013EF64  7C E7 1A 14 */	add r7, r7, r3
/* 80144068 0013EF68  80 66 00 18 */	lwz r3, 0x18(r6)
/* 8014406C 0013EF6C  7C E7 02 14 */	add r7, r7, r0
/* 80144070 0013EF70  80 06 00 1C */	lwz r0, 0x1c(r6)
/* 80144074 0013EF74  7C E7 1A 14 */	add r7, r7, r3
/* 80144078 0013EF78  38 C6 00 20 */	addi r6, r6, 0x20
/* 8014407C 0013EF7C  7C E7 02 14 */	add r7, r7, r0
/* 80144080 0013EF80  42 00 FF BC */	bdnz lbl_8014403C
/* 80144084 0013EF84  80 06 00 00 */	lwz r0, 0(r6)
/* 80144088 0013EF88  38 61 00 08 */	addi r3, r1, 8
/* 8014408C 0013EF8C  80 86 00 04 */	lwz r4, 4(r6)
/* 80144090 0013EF90  38 A0 00 01 */	li r5, 1
/* 80144094 0013EF94  7C E7 02 14 */	add r7, r7, r0
/* 80144098 0013EF98  80 06 00 08 */	lwz r0, 8(r6)
/* 8014409C 0013EF9C  7C E7 22 14 */	add r7, r7, r4
/* 801440A0 0013EFA0  80 86 00 0C */	lwz r4, 0xc(r6)
/* 801440A4 0013EFA4  7C E7 02 14 */	add r7, r7, r0
/* 801440A8 0013EFA8  80 06 00 10 */	lwz r0, 0x10(r6)
/* 801440AC 0013EFAC  7C E7 22 14 */	add r7, r7, r4
/* 801440B0 0013EFB0  80 86 00 14 */	lwz r4, 0x14(r6)
/* 801440B4 0013EFB4  7C E7 02 14 */	add r7, r7, r0
/* 801440B8 0013EFB8  80 06 00 18 */	lwz r0, 0x18(r6)
/* 801440BC 0013EFBC  7C E7 22 14 */	add r7, r7, r4
/* 801440C0 0013EFC0  7C E7 02 14 */	add r7, r7, r0
/* 801440C4 0013EFC4  90 E8 03 FC */	stw r7, 0x3fc(r8)
/* 801440C8 0013EFC8  80 8D 86 54 */	lwz r4, ConfigFile-_SDA_BASE_(r13)
/* 801440CC 0013EFCC  4B FF EA 59 */	bl NWC24FOpen
/* 801440D0 0013EFD0  2C 03 00 00 */	cmpwi r3, 0
/* 801440D4 0013EFD4  40 82 00 34 */	bne lbl_80144108
/* 801440D8 0013EFD8  80 6D A0 88 */	lwz r3, config-_SDA_BASE_(r13)
/* 801440DC 0013EFDC  38 A1 00 08 */	addi r5, r1, 8
/* 801440E0 0013EFE0  38 80 04 00 */	li r4, 0x400
/* 801440E4 0013EFE4  4B FF F2 DD */	bl NWC24FWrite
/* 801440E8 0013EFE8  7C 7F 1B 78 */	mr r31, r3
/* 801440EC 0013EFEC  38 61 00 08 */	addi r3, r1, 8
/* 801440F0 0013EFF0  4B FF ED 85 */	bl NWC24FClose
/* 801440F4 0013EFF4  2C 1F 00 00 */	cmpwi r31, 0
/* 801440F8 0013EFF8  41 82 00 08 */	beq lbl_80144100
/* 801440FC 0013EFFC  7F E3 FB 78 */	mr r3, r31
lbl_80144100:
/* 80144100 0013F000  38 00 00 00 */	li r0, 0
/* 80144104 0013F004  90 0D A0 8C */	stw r0, ConfigModified-_SDA_BASE_(r13)
lbl_80144108:
/* 80144108 0013F008  2C 03 00 00 */	cmpwi r3, 0
/* 8014410C 0013F00C  41 82 00 08 */	beq lbl_80144114
/* 80144110 0013F010  48 00 00 4C */	b lbl_8014415C
lbl_80144114:
/* 80144114 0013F014  80 8D 86 58 */	lwz r4, CfgBakFile-_SDA_BASE_(r13)
/* 80144118 0013F018  38 61 00 08 */	addi r3, r1, 8
/* 8014411C 0013F01C  38 A0 00 01 */	li r5, 1
/* 80144120 0013F020  4B FF EA 05 */	bl NWC24FOpen
/* 80144124 0013F024  2C 03 00 00 */	cmpwi r3, 0
/* 80144128 0013F028  40 82 00 34 */	bne lbl_8014415C
/* 8014412C 0013F02C  80 6D A0 88 */	lwz r3, config-_SDA_BASE_(r13)
/* 80144130 0013F030  38 A1 00 08 */	addi r5, r1, 8
/* 80144134 0013F034  38 80 04 00 */	li r4, 0x400
/* 80144138 0013F038  4B FF F2 89 */	bl NWC24FWrite
/* 8014413C 0013F03C  7C 7F 1B 78 */	mr r31, r3
/* 80144140 0013F040  38 61 00 08 */	addi r3, r1, 8
/* 80144144 0013F044  4B FF ED 31 */	bl NWC24FClose
/* 80144148 0013F048  2C 1F 00 00 */	cmpwi r31, 0
/* 8014414C 0013F04C  41 82 00 08 */	beq lbl_80144154
/* 80144150 0013F050  7F E3 FB 78 */	mr r3, r31
lbl_80144154:
/* 80144154 0013F054  38 00 00 00 */	li r0, 0
/* 80144158 0013F058  90 0D A0 8C */	stw r0, ConfigModified-_SDA_BASE_(r13)
lbl_8014415C:
/* 8014415C 0013F05C  80 01 00 B4 */	lwz r0, 0xb4(r1)
/* 80144160 0013F060  83 E1 00 AC */	lwz r31, 0xac(r1)
/* 80144164 0013F064  7C 08 03 A6 */	mtlr r0
/* 80144168 0013F068  38 21 00 B0 */	addi r1, r1, 0xb0
/* 8014416C 0013F06C  4E 80 00 20 */	blr 

.global NWC24GetAccountDomain
NWC24GetAccountDomain:
/* 80144170 0013F070  80 6D A0 88 */	lwz r3, config-_SDA_BASE_(r13)
/* 80144174 0013F074  38 63 00 18 */	addi r3, r3, 0x18
/* 80144178 0013F078  4E 80 00 20 */	blr 

.global NWC24GetMBoxDir
NWC24GetMBoxDir:
/* 8014417C 0013F07C  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80144180 0013F080  7C 08 02 A6 */	mflr r0
/* 80144184 0013F084  90 01 00 14 */	stw r0, 0x14(r1)
/* 80144188 0013F088  38 61 00 08 */	addi r3, r1, 8
/* 8014418C 0013F08C  4B FA 7D 25 */	bl __OSGetIOSRev
/* 80144190 0013F090  88 01 00 09 */	lbz r0, 9(r1)
/* 80144194 0013F094  2C 00 00 00 */	cmpwi r0, 0
/* 80144198 0013F098  40 82 00 40 */	bne lbl_801441D8
/* 8014419C 0013F09C  88 61 00 0A */	lbz r3, 0xa(r1)
/* 801441A0 0013F0A0  28 03 00 07 */	cmplwi r3, 7
/* 801441A4 0013F0A4  40 82 00 10 */	bne lbl_801441B4
/* 801441A8 0013F0A8  88 01 00 0B */	lbz r0, 0xb(r1)
/* 801441AC 0013F0AC  2C 00 00 00 */	cmpwi r0, 0
/* 801441B0 0013F0B0  41 82 00 0C */	beq lbl_801441BC
lbl_801441B4:
/* 801441B4 0013F0B4  28 03 00 07 */	cmplwi r3, 7
/* 801441B8 0013F0B8  40 80 00 20 */	bge lbl_801441D8
lbl_801441BC:
/* 801441BC 0013F0BC  3C 60 80 3B */	lis r3, lbl_803B76BC@ha
/* 801441C0 0013F0C0  3C A0 80 3B */	lis r5, lbl_803B76CC@ha
/* 801441C4 0013F0C4  38 63 76 BC */	addi r3, r3, lbl_803B76BC@l
/* 801441C8 0013F0C8  38 80 02 9A */	li r4, 0x29a
/* 801441CC 0013F0CC  38 A5 76 CC */	addi r5, r5, lbl_803B76CC@l
/* 801441D0 0013F0D0  4C C6 31 82 */	crclr 6
/* 801441D4 0013F0D4  4B FA AD D5 */	bl OSPanic
lbl_801441D8:
/* 801441D8 0013F0D8  80 01 00 14 */	lwz r0, 0x14(r1)
/* 801441DC 0013F0DC  80 6D 86 50 */	lwz r3, MBoxDir-_SDA_BASE_(r13)
/* 801441E0 0013F0E0  7C 08 03 A6 */	mtlr r0
/* 801441E4 0013F0E4  38 21 00 10 */	addi r1, r1, 0x10
/* 801441E8 0013F0E8  4E 80 00 20 */	blr 

.global NWC24GetAppId
NWC24GetAppId:
/* 801441EC 0013F0EC  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 801441F0 0013F0F0  7C 08 02 A6 */	mflr r0
/* 801441F4 0013F0F4  90 01 00 14 */	stw r0, 0x14(r1)
/* 801441F8 0013F0F8  93 E1 00 0C */	stw r31, 0xc(r1)
/* 801441FC 0013F0FC  4B FA 8E 55 */	bl OSGetAppGamename
/* 80144200 0013F100  83 E3 00 00 */	lwz r31, 0(r3)
/* 80144204 0013F104  2C 1F 00 00 */	cmpwi r31, 0
/* 80144208 0013F108  40 82 00 18 */	bne lbl_80144220
/* 8014420C 0013F10C  4B FA 8E 91 */	bl OSGetAppType
/* 80144210 0013F110  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 80144214 0013F114  40 82 00 0C */	bne lbl_80144220
/* 80144218 0013F118  4B FF 9F 81 */	bl DVDGetCurrentDiskID
/* 8014421C 0013F11C  83 E3 00 00 */	lwz r31, 0(r3)
lbl_80144220:
/* 80144220 0013F120  7F E3 FB 78 */	mr r3, r31
/* 80144224 0013F124  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80144228 0013F128  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8014422C 0013F12C  7C 08 03 A6 */	mtlr r0
/* 80144230 0013F130  38 21 00 10 */	addi r1, r1, 0x10
/* 80144234 0013F134  4E 80 00 20 */	blr 

.global NWC24GetGroupId
NWC24GetGroupId:
/* 80144238 0013F138  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8014423C 0013F13C  7C 08 02 A6 */	mflr r0
/* 80144240 0013F140  90 01 00 24 */	stw r0, 0x24(r1)
/* 80144244 0013F144  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80144248 0013F148  3B E0 00 01 */	li r31, 1
/* 8014424C 0013F14C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80144250 0013F150  4B FA 8E 4D */	bl OSGetAppType
/* 80144254 0013F154  54 60 06 3E */	clrlwi r0, r3, 0x18
/* 80144258 0013F158  2C 00 00 80 */	cmpwi r0, 0x80
/* 8014425C 0013F15C  41 82 00 28 */	beq lbl_80144284
/* 80144260 0013F160  40 80 00 10 */	bge lbl_80144270
/* 80144264 0013F164  2C 00 00 40 */	cmpwi r0, 0x40
/* 80144268 0013F168  41 82 00 14 */	beq lbl_8014427C
/* 8014426C 0013F16C  48 00 00 54 */	b lbl_801442C0
lbl_80144270:
/* 80144270 0013F170  2C 00 00 82 */	cmpwi r0, 0x82
/* 80144274 0013F174  40 80 00 4C */	bge lbl_801442C0
/* 80144278 0013F178  48 00 00 18 */	b lbl_80144290
lbl_8014427C:
/* 8014427C 0013F17C  3B E0 00 01 */	li r31, 1
/* 80144280 0013F180  48 00 00 40 */	b lbl_801442C0
lbl_80144284:
/* 80144284 0013F184  4B FF 9F 15 */	bl DVDGetCurrentDiskID
/* 80144288 0013F188  A3 E3 00 04 */	lhz r31, 4(r3)
/* 8014428C 0013F18C  48 00 00 34 */	b lbl_801442C0
lbl_80144290:
/* 80144290 0013F190  80 6D A0 90 */	lwz r3, NWC24WorkP-_SDA_BASE_(r13)
/* 80144294 0013F194  3B C3 08 00 */	addi r30, r3, 0x800
/* 80144298 0013F198  7F C3 F3 78 */	mr r3, r30
/* 8014429C 0013F19C  4B FA 70 7D */	bl NANDGetHomeDir
/* 801442A0 0013F1A0  2C 03 00 00 */	cmpwi r3, 0
/* 801442A4 0013F1A4  40 82 00 1C */	bne lbl_801442C0
/* 801442A8 0013F1A8  7F C3 F3 78 */	mr r3, r30
/* 801442AC 0013F1AC  38 81 00 08 */	addi r4, r1, 8
/* 801442B0 0013F1B0  4B FA 58 59 */	bl NANDGetStatus
/* 801442B4 0013F1B4  2C 03 00 00 */	cmpwi r3, 0
/* 801442B8 0013F1B8  40 82 00 08 */	bne lbl_801442C0
/* 801442BC 0013F1BC  A3 E1 00 0C */	lhz r31, 0xc(r1)
lbl_801442C0:
/* 801442C0 0013F1C0  7F E3 FB 78 */	mr r3, r31
/* 801442C4 0013F1C4  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 801442C8 0013F1C8  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 801442CC 0013F1CC  80 01 00 24 */	lwz r0, 0x24(r1)
/* 801442D0 0013F1D0  7C 08 03 A6 */	mtlr r0
/* 801442D4 0013F1D4  38 21 00 20 */	addi r1, r1, 0x20
/* 801442D8 0013F1D8  4E 80 00 20 */	blr 

.global CheckConfig
CheckConfig:
/* 801442DC 0013F1DC  80 CD A0 88 */	lwz r6, config-_SDA_BASE_(r13)
/* 801442E0 0013F1E0  80 66 00 00 */	lwz r3, 0(r6)
/* 801442E4 0013F1E4  3C 03 A8 9D */	addis r0, r3, 0xa89d
/* 801442E8 0013F1E8  28 00 43 66 */	cmplwi r0, 0x4366
/* 801442EC 0013F1EC  41 82 00 0C */	beq lbl_801442F8
/* 801442F0 0013F1F0  38 60 FF F2 */	li r3, -14
/* 801442F4 0013F1F4  4E 80 00 20 */	blr 
lbl_801442F8:
/* 801442F8 0013F1F8  38 00 00 1F */	li r0, 0x1f
/* 801442FC 0013F1FC  7C C4 33 78 */	mr r4, r6
/* 80144300 0013F200  38 A0 00 00 */	li r5, 0
/* 80144304 0013F204  7C 09 03 A6 */	mtctr r0
lbl_80144308:
/* 80144308 0013F208  80 64 00 00 */	lwz r3, 0(r4)
/* 8014430C 0013F20C  80 04 00 04 */	lwz r0, 4(r4)
/* 80144310 0013F210  7C A5 1A 14 */	add r5, r5, r3
/* 80144314 0013F214  80 64 00 08 */	lwz r3, 8(r4)
/* 80144318 0013F218  7C A5 02 14 */	add r5, r5, r0
/* 8014431C 0013F21C  80 04 00 0C */	lwz r0, 0xc(r4)
/* 80144320 0013F220  7C A5 1A 14 */	add r5, r5, r3
/* 80144324 0013F224  80 64 00 10 */	lwz r3, 0x10(r4)
/* 80144328 0013F228  7C A5 02 14 */	add r5, r5, r0
/* 8014432C 0013F22C  80 04 00 14 */	lwz r0, 0x14(r4)
/* 80144330 0013F230  7C A5 1A 14 */	add r5, r5, r3
/* 80144334 0013F234  80 64 00 18 */	lwz r3, 0x18(r4)
/* 80144338 0013F238  7C A5 02 14 */	add r5, r5, r0
/* 8014433C 0013F23C  80 04 00 1C */	lwz r0, 0x1c(r4)
/* 80144340 0013F240  7C A5 1A 14 */	add r5, r5, r3
/* 80144344 0013F244  38 84 00 20 */	addi r4, r4, 0x20
/* 80144348 0013F248  7C A5 02 14 */	add r5, r5, r0
/* 8014434C 0013F24C  42 00 FF BC */	bdnz lbl_80144308
/* 80144350 0013F250  80 64 00 00 */	lwz r3, 0(r4)
/* 80144354 0013F254  80 04 00 04 */	lwz r0, 4(r4)
/* 80144358 0013F258  7C A5 1A 14 */	add r5, r5, r3
/* 8014435C 0013F25C  80 64 00 08 */	lwz r3, 8(r4)
/* 80144360 0013F260  7C A5 02 14 */	add r5, r5, r0
/* 80144364 0013F264  80 04 00 0C */	lwz r0, 0xc(r4)
/* 80144368 0013F268  7C A5 1A 14 */	add r5, r5, r3
/* 8014436C 0013F26C  80 64 00 10 */	lwz r3, 0x10(r4)
/* 80144370 0013F270  7C A5 02 14 */	add r5, r5, r0
/* 80144374 0013F274  80 04 00 14 */	lwz r0, 0x14(r4)
/* 80144378 0013F278  7C A5 1A 14 */	add r5, r5, r3
/* 8014437C 0013F27C  80 64 00 18 */	lwz r3, 0x18(r4)
/* 80144380 0013F280  7C A5 02 14 */	add r5, r5, r0
/* 80144384 0013F284  80 06 03 FC */	lwz r0, 0x3fc(r6)
/* 80144388 0013F288  7C A5 1A 14 */	add r5, r5, r3
/* 8014438C 0013F28C  7C 00 28 40 */	cmplw r0, r5
/* 80144390 0013F290  41 82 00 0C */	beq lbl_8014439C
/* 80144394 0013F294  38 60 FF F2 */	li r3, -14
/* 80144398 0013F298  4E 80 00 20 */	blr 
lbl_8014439C:
/* 8014439C 0013F29C  80 06 00 10 */	lwz r0, 0x10(r6)
/* 801443A0 0013F2A0  28 00 00 20 */	cmplwi r0, 0x20
/* 801443A4 0013F2A4  41 80 00 0C */	blt lbl_801443B0
/* 801443A8 0013F2A8  38 60 FF F2 */	li r3, -14
/* 801443AC 0013F2AC  4E 80 00 20 */	blr 
lbl_801443B0:
/* 801443B0 0013F2B0  80 06 00 04 */	lwz r0, 4(r6)
/* 801443B4 0013F2B4  38 60 00 00 */	li r3, 0
/* 801443B8 0013F2B8  28 00 00 08 */	cmplwi r0, 8
/* 801443BC 0013F2BC  4D 82 00 20 */	beqlr 
/* 801443C0 0013F2C0  38 60 FF E5 */	li r3, -27
/* 801443C4 0013F2C4  4E 80 00 20 */	blr 