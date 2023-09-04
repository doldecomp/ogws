.include "macros.inc"

.section .sdata2, "a"
.balign 0x8
.global lbl_804C1338
lbl_804C1338:
	.incbin "baserom.dol", 0x3C9F78, 0x4
.global lbl_804C133C
lbl_804C133C:
	.incbin "baserom.dol", 0x3C9F7C, 0x4
.global lbl_804C1340
lbl_804C1340:
	.incbin "baserom.dol", 0x3C9F80, 0x8
.global lbl_804C1348
lbl_804C1348:
	.incbin "baserom.dol", 0x3C9F88, 0x8

.section .text, "ax"
.global AXFXChorusGetMemSize
AXFXChorusGetMemSize:
/* 80109DE0 00104CE0  48 00 01 64 */	b AXFXChorusExpGetMemSize

.global AXFXChorusInit
AXFXChorusInit:
/* 80109DE4 00104CE4  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80109DE8 00104CE8  7C 08 02 A6 */	mflr r0
/* 80109DEC 00104CEC  3C C0 43 30 */	lis r6, 0x4330
/* 80109DF0 00104CF0  C8 C2 99 28 */	lfd f6, lbl_804C1348-_SDA2_BASE_(r2)
/* 80109DF4 00104CF4  90 01 00 24 */	stw r0, 0x24(r1)
/* 80109DF8 00104CF8  38 00 00 00 */	li r0, 0
/* 80109DFC 00104CFC  C0 22 99 1C */	lfs f1, lbl_804C133C-_SDA2_BASE_(r2)
/* 80109E00 00104D00  80 E3 00 A0 */	lwz r7, 0xa0(r3)
/* 80109E04 00104D04  80 A3 00 A4 */	lwz r5, 0xa4(r3)
/* 80109E08 00104D08  80 83 00 A8 */	lwz r4, 0xa8(r3)
/* 80109E0C 00104D0C  90 E1 00 0C */	stw r7, 0xc(r1)
/* 80109E10 00104D10  C0 42 99 18 */	lfs f2, lbl_804C1338-_SDA2_BASE_(r2)
/* 80109E14 00104D14  90 C1 00 08 */	stw r6, 8(r1)
/* 80109E18 00104D18  C8 01 00 08 */	lfd f0, 8(r1)
/* 80109E1C 00104D1C  90 A1 00 14 */	stw r5, 0x14(r1)
/* 80109E20 00104D20  EC A0 30 28 */	fsubs f5, f0, f6
/* 80109E24 00104D24  C0 02 99 20 */	lfs f0, lbl_804C1340-_SDA2_BASE_(r2)
/* 80109E28 00104D28  90 C1 00 10 */	stw r6, 0x10(r1)
/* 80109E2C 00104D2C  C8 61 00 10 */	lfd f3, 0x10(r1)
/* 80109E30 00104D30  90 81 00 1C */	stw r4, 0x1c(r1)
/* 80109E34 00104D34  EC 83 30 28 */	fsubs f4, f3, f6
/* 80109E38 00104D38  90 C1 00 18 */	stw r6, 0x18(r1)
/* 80109E3C 00104D3C  EC 84 28 24 */	fdivs f4, f4, f5
/* 80109E40 00104D40  C8 61 00 18 */	lfd f3, 0x18(r1)
/* 80109E44 00104D44  D0 03 00 98 */	stfs f0, 0x98(r3)
/* 80109E48 00104D48  D0 A3 00 80 */	stfs f5, 0x80(r3)
/* 80109E4C 00104D4C  D0 23 00 8C */	stfs f1, 0x8c(r3)
/* 80109E50 00104D50  90 03 00 90 */	stw r0, 0x90(r3)
/* 80109E54 00104D54  EC 03 30 28 */	fsubs f0, f3, f6
/* 80109E58 00104D58  90 03 00 94 */	stw r0, 0x94(r3)
/* 80109E5C 00104D5C  D0 83 00 84 */	stfs f4, 0x84(r3)
/* 80109E60 00104D60  EC 02 00 24 */	fdivs f0, f2, f0
/* 80109E64 00104D64  D0 23 00 9C */	stfs f1, 0x9c(r3)
/* 80109E68 00104D68  D0 03 00 88 */	stfs f0, 0x88(r3)
/* 80109E6C 00104D6C  48 00 00 E5 */	bl __ParamConvert
/* 80109E70 00104D70  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80109E74 00104D74  7C 08 03 A6 */	mtlr r0
/* 80109E78 00104D78  38 21 00 20 */	addi r1, r1, 0x20
/* 80109E7C 00104D7C  4E 80 00 20 */	blr 

.global AXFXChorusShutdown
AXFXChorusShutdown:
/* 80109E80 00104D80  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80109E84 00104D84  7C 08 02 A6 */	mflr r0
/* 80109E88 00104D88  90 01 00 14 */	stw r0, 0x14(r1)
/* 80109E8C 00104D8C  48 00 04 49 */	bl AXFXChorusExpShutdown
/* 80109E90 00104D90  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80109E94 00104D94  38 60 00 01 */	li r3, 1
/* 80109E98 00104D98  7C 08 03 A6 */	mtlr r0
/* 80109E9C 00104D9C  38 21 00 10 */	addi r1, r1, 0x10
/* 80109EA0 00104DA0  4E 80 00 20 */	blr 

.global AXFXChorusSettings
AXFXChorusSettings:
/* 80109EA4 00104DA4  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80109EA8 00104DA8  7C 08 02 A6 */	mflr r0
/* 80109EAC 00104DAC  3C C0 43 30 */	lis r6, 0x4330
/* 80109EB0 00104DB0  C8 C2 99 28 */	lfd f6, lbl_804C1348-_SDA2_BASE_(r2)
/* 80109EB4 00104DB4  90 01 00 24 */	stw r0, 0x24(r1)
/* 80109EB8 00104DB8  38 00 00 00 */	li r0, 0
/* 80109EBC 00104DBC  C0 22 99 1C */	lfs f1, lbl_804C133C-_SDA2_BASE_(r2)
/* 80109EC0 00104DC0  80 E3 00 A0 */	lwz r7, 0xa0(r3)
/* 80109EC4 00104DC4  80 A3 00 A4 */	lwz r5, 0xa4(r3)
/* 80109EC8 00104DC8  80 83 00 A8 */	lwz r4, 0xa8(r3)
/* 80109ECC 00104DCC  90 E1 00 0C */	stw r7, 0xc(r1)
/* 80109ED0 00104DD0  C0 42 99 18 */	lfs f2, lbl_804C1338-_SDA2_BASE_(r2)
/* 80109ED4 00104DD4  90 C1 00 08 */	stw r6, 8(r1)
/* 80109ED8 00104DD8  C8 01 00 08 */	lfd f0, 8(r1)
/* 80109EDC 00104DDC  90 A1 00 14 */	stw r5, 0x14(r1)
/* 80109EE0 00104DE0  EC A0 30 28 */	fsubs f5, f0, f6
/* 80109EE4 00104DE4  C0 02 99 20 */	lfs f0, lbl_804C1340-_SDA2_BASE_(r2)
/* 80109EE8 00104DE8  90 C1 00 10 */	stw r6, 0x10(r1)
/* 80109EEC 00104DEC  C8 61 00 10 */	lfd f3, 0x10(r1)
/* 80109EF0 00104DF0  90 81 00 1C */	stw r4, 0x1c(r1)
/* 80109EF4 00104DF4  EC 83 30 28 */	fsubs f4, f3, f6
/* 80109EF8 00104DF8  90 C1 00 18 */	stw r6, 0x18(r1)
/* 80109EFC 00104DFC  EC 84 28 24 */	fdivs f4, f4, f5
/* 80109F00 00104E00  C8 61 00 18 */	lfd f3, 0x18(r1)
/* 80109F04 00104E04  D0 03 00 98 */	stfs f0, 0x98(r3)
/* 80109F08 00104E08  D0 A3 00 80 */	stfs f5, 0x80(r3)
/* 80109F0C 00104E0C  D0 23 00 8C */	stfs f1, 0x8c(r3)
/* 80109F10 00104E10  90 03 00 90 */	stw r0, 0x90(r3)
/* 80109F14 00104E14  EC 03 30 28 */	fsubs f0, f3, f6
/* 80109F18 00104E18  90 03 00 94 */	stw r0, 0x94(r3)
/* 80109F1C 00104E1C  D0 83 00 84 */	stfs f4, 0x84(r3)
/* 80109F20 00104E20  EC 02 00 24 */	fdivs f0, f2, f0
/* 80109F24 00104E24  D0 23 00 9C */	stfs f1, 0x9c(r3)
/* 80109F28 00104E28  D0 03 00 88 */	stfs f0, 0x88(r3)
/* 80109F2C 00104E2C  48 00 02 81 */	bl AXFXChorusExpSettings
/* 80109F30 00104E30  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80109F34 00104E34  7C 08 03 A6 */	mtlr r0
/* 80109F38 00104E38  38 21 00 20 */	addi r1, r1, 0x20
/* 80109F3C 00104E3C  4E 80 00 20 */	blr 

.global AXFXChorusCallback
AXFXChorusCallback:
/* 80109F40 00104E40  48 00 04 24 */	b AXFXChorusExpCallback