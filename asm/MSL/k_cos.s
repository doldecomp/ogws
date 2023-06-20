.include "macros.inc"

.section .sdata2, "a"
.balign 0x8
.global lbl_804C0E38
lbl_804C0E38:
	.incbin "baserom.dol", 0x3C9A78, 0x8
.global lbl_804C0E40
lbl_804C0E40:
	.incbin "baserom.dol", 0x3C9A80, 0x8
.global lbl_804C0E48
lbl_804C0E48:
	.incbin "baserom.dol", 0x3C9A88, 0x8
.global lbl_804C0E50
lbl_804C0E50:
	.incbin "baserom.dol", 0x3C9A90, 0x8
.global lbl_804C0E58
lbl_804C0E58:
	.incbin "baserom.dol", 0x3C9A98, 0x8
.global lbl_804C0E60
lbl_804C0E60:
	.incbin "baserom.dol", 0x3C9AA0, 0x8
.global lbl_804C0E68
lbl_804C0E68:
	.incbin "baserom.dol", 0x3C9AA8, 0x8
.global lbl_804C0E70
lbl_804C0E70:
	.incbin "baserom.dol", 0x3C9AB0, 0x8
.global lbl_804C0E78
lbl_804C0E78:
	.incbin "baserom.dol", 0x3C9AB8, 0x8

.section .text, "ax"
.global __kernel_cos
__kernel_cos:
/* 800BE938 000B9838  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800BE93C 000B983C  3C 00 3E 40 */	lis r0, 0x3e40
/* 800BE940 000B9840  D8 21 00 08 */	stfd f1, 8(r1)
/* 800BE944 000B9844  80 61 00 08 */	lwz r3, 8(r1)
/* 800BE948 000B9848  54 64 00 7E */	clrlwi r4, r3, 1
/* 800BE94C 000B984C  7C 04 00 00 */	cmpw r4, r0
/* 800BE950 000B9850  40 80 00 20 */	bge lbl_800BE970
/* 800BE954 000B9854  FC 00 08 1E */	fctiwz f0, f1
/* 800BE958 000B9858  D8 01 00 18 */	stfd f0, 0x18(r1)
/* 800BE95C 000B985C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 800BE960 000B9860  2C 00 00 00 */	cmpwi r0, 0
/* 800BE964 000B9864  40 82 00 0C */	bne lbl_800BE970
/* 800BE968 000B9868  C8 22 94 18 */	lfd f1, lbl_804C0E38-_SDA2_BASE_(r2)
/* 800BE96C 000B986C  48 00 00 D4 */	b lbl_800BEA40
lbl_800BE970:
/* 800BE970 000B9870  FD 01 00 72 */	fmul f8, f1, f1
/* 800BE974 000B9874  C8 02 94 48 */	lfd f0, lbl_804C0E68-_SDA2_BASE_(r2)
/* 800BE978 000B9878  3C 60 3F D3 */	lis r3, 0x3FD33333@ha
/* 800BE97C 000B987C  C8 C2 94 40 */	lfd f6, lbl_804C0E60-_SDA2_BASE_(r2)
/* 800BE980 000B9880  38 03 33 33 */	addi r0, r3, 0x3FD33333@l
/* 800BE984 000B9884  C8 A2 94 38 */	lfd f5, lbl_804C0E58-_SDA2_BASE_(r2)
/* 800BE988 000B9888  FC E0 02 32 */	fmul f7, f0, f8
/* 800BE98C 000B988C  C8 82 94 30 */	lfd f4, lbl_804C0E50-_SDA2_BASE_(r2)
/* 800BE990 000B9890  C8 62 94 28 */	lfd f3, lbl_804C0E48-_SDA2_BASE_(r2)
/* 800BE994 000B9894  7C 04 00 00 */	cmpw r4, r0
/* 800BE998 000B9898  C8 02 94 20 */	lfd f0, lbl_804C0E40-_SDA2_BASE_(r2)
/* 800BE99C 000B989C  FC C6 38 2A */	fadd f6, f6, f7
/* 800BE9A0 000B98A0  FC C8 01 B2 */	fmul f6, f8, f6
/* 800BE9A4 000B98A4  FC A5 30 2A */	fadd f5, f5, f6
/* 800BE9A8 000B98A8  FC A8 01 72 */	fmul f5, f8, f5
/* 800BE9AC 000B98AC  FC 84 28 2A */	fadd f4, f4, f5
/* 800BE9B0 000B98B0  FC 88 01 32 */	fmul f4, f8, f4
/* 800BE9B4 000B98B4  FC 63 20 2A */	fadd f3, f3, f4
/* 800BE9B8 000B98B8  FC 68 00 F2 */	fmul f3, f8, f3
/* 800BE9BC 000B98BC  FC 00 18 2A */	fadd f0, f0, f3
/* 800BE9C0 000B98C0  FC 68 00 32 */	fmul f3, f8, f0
/* 800BE9C4 000B98C4  40 80 00 28 */	bge lbl_800BE9EC
/* 800BE9C8 000B98C8  FC 68 00 F2 */	fmul f3, f8, f3
/* 800BE9CC 000B98CC  C8 82 94 50 */	lfd f4, lbl_804C0E70-_SDA2_BASE_(r2)
/* 800BE9D0 000B98D0  C8 02 94 18 */	lfd f0, lbl_804C0E38-_SDA2_BASE_(r2)
/* 800BE9D4 000B98D4  FC 21 00 B2 */	fmul f1, f1, f2
/* 800BE9D8 000B98D8  FC 44 02 32 */	fmul f2, f4, f8
/* 800BE9DC 000B98DC  FC 23 08 28 */	fsub f1, f3, f1
/* 800BE9E0 000B98E0  FC 22 08 28 */	fsub f1, f2, f1
/* 800BE9E4 000B98E4  FC 20 08 28 */	fsub f1, f0, f1
/* 800BE9E8 000B98E8  48 00 00 58 */	b lbl_800BEA40
lbl_800BE9EC:
/* 800BE9EC 000B98EC  3C 00 3F E9 */	lis r0, 0x3fe9
/* 800BE9F0 000B98F0  7C 04 00 00 */	cmpw r4, r0
/* 800BE9F4 000B98F4  40 81 00 10 */	ble lbl_800BEA04
/* 800BE9F8 000B98F8  C8 02 94 58 */	lfd f0, lbl_804C0E78-_SDA2_BASE_(r2)
/* 800BE9FC 000B98FC  D8 01 00 10 */	stfd f0, 0x10(r1)
/* 800BEA00 000B9900  48 00 00 14 */	b lbl_800BEA14
lbl_800BEA04:
/* 800BEA04 000B9904  3C 64 FF E0 */	addis r3, r4, 0xffe0
/* 800BEA08 000B9908  38 00 00 00 */	li r0, 0
/* 800BEA0C 000B990C  90 61 00 10 */	stw r3, 0x10(r1)
/* 800BEA10 000B9910  90 01 00 14 */	stw r0, 0x14(r1)
lbl_800BEA14:
/* 800BEA14 000B9914  C8 02 94 50 */	lfd f0, lbl_804C0E70-_SDA2_BASE_(r2)
/* 800BEA18 000B9918  FC 68 00 F2 */	fmul f3, f8, f3
/* 800BEA1C 000B991C  C8 A1 00 10 */	lfd f5, 0x10(r1)
/* 800BEA20 000B9920  FC C0 02 32 */	fmul f6, f0, f8
/* 800BEA24 000B9924  C8 82 94 18 */	lfd f4, lbl_804C0E38-_SDA2_BASE_(r2)
/* 800BEA28 000B9928  FC 01 00 B2 */	fmul f0, f1, f2
/* 800BEA2C 000B992C  FC 46 28 28 */	fsub f2, f6, f5
/* 800BEA30 000B9930  FC 24 28 28 */	fsub f1, f4, f5
/* 800BEA34 000B9934  FC 03 00 28 */	fsub f0, f3, f0
/* 800BEA38 000B9938  FC 02 00 28 */	fsub f0, f2, f0
/* 800BEA3C 000B993C  FC 21 00 28 */	fsub f1, f1, f0
lbl_800BEA40:
/* 800BEA40 000B9940  38 21 00 20 */	addi r1, r1, 0x20
/* 800BEA44 000B9944  4E 80 00 20 */	blr 
