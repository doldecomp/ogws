.include "macros.inc"

.section .rodata, "a"
.global lbl_80378300
lbl_80378300:
	.long 0x07
	.string "AnmObj"
	.balign 8

.section .text, "ax"
.global PlayPolicy_Onetime__Q24nw4r3g3dFfff
PlayPolicy_Onetime__Q24nw4r3g3dFfff:
/* 80063604 0005E504  FC 20 18 90 */	fmr f1, f3
/* 80063608 0005E508  4E 80 00 20 */	blr 

.global PlayPolicy_Loop__Q24nw4r3g3dFfff
PlayPolicy_Loop__Q24nw4r3g3dFfff:
/* 8006360C 0005E50C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80063610 0005E510  7C 08 02 A6 */	mflr r0
/* 80063614 0005E514  90 01 00 24 */	stw r0, 0x24(r1)
/* 80063618 0005E518  DB E1 00 10 */	stfd f31, 0x10(r1)
/* 8006361C 0005E51C  F3 E1 00 18 */	psq_st f31, 24(r1), 0, qr0
/* 80063620 0005E520  C0 02 89 08 */	lfs f0, lbl_804C0328-_SDA2_BASE_(r2)
/* 80063624 0005E524  EF E2 08 28 */	fsubs f31, f2, f1
/* 80063628 0005E528  FC 03 00 40 */	fcmpo cr0, f3, f0
/* 8006362C 0005E52C  4C 41 13 82 */	cror 2, 1, 2
/* 80063630 0005E530  40 82 00 18 */	bne lbl_80063648
/* 80063634 0005E534  FC 20 18 90 */	fmr f1, f3
/* 80063638 0005E538  FC 40 F8 90 */	fmr f2, f31
/* 8006363C 0005E53C  48 05 D8 41 */	bl fmod
/* 80063640 0005E540  FC 20 08 18 */	frsp f1, f1
/* 80063644 0005E544  48 00 00 20 */	b lbl_80063664
lbl_80063648:
/* 80063648 0005E548  FC 40 F8 90 */	fmr f2, f31
/* 8006364C 0005E54C  EC 23 F8 2A */	fadds f1, f3, f31
/* 80063650 0005E550  48 05 D8 2D */	bl fmod
/* 80063654 0005E554  FC 20 08 18 */	frsp f1, f1
/* 80063658 0005E558  C0 02 89 08 */	lfs f0, lbl_804C0328-_SDA2_BASE_(r2)
/* 8006365C 0005E55C  FC 01 F8 2E */	fsel f0, f1, f0, f31
/* 80063660 0005E560  EC 21 00 2A */	fadds f1, f1, f0
lbl_80063664:
/* 80063664 0005E564  E3 E1 00 18 */	psq_l f31, 24(r1), 0, qr0
/* 80063668 0005E568  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8006366C 0005E56C  CB E1 00 10 */	lfd f31, 0x10(r1)
/* 80063670 0005E570  7C 08 03 A6 */	mtlr r0
/* 80063674 0005E574  38 21 00 20 */	addi r1, r1, 0x20
/* 80063678 0005E578  4E 80 00 20 */	blr 

.global SetAnmFlag__Q34nw4r3g3d6AnmObjFQ44nw4r3g3d6AnmObj7AnmFlagb
SetAnmFlag__Q34nw4r3g3d6AnmObjFQ44nw4r3g3d6AnmObj7AnmFlagb:
/* 8006367C 0005E57C  2C 05 00 00 */	cmpwi r5, 0
/* 80063680 0005E580  41 82 00 14 */	beq lbl_80063694
/* 80063684 0005E584  80 03 00 0C */	lwz r0, 0xc(r3)
/* 80063688 0005E588  7C 00 23 78 */	or r0, r0, r4
/* 8006368C 0005E58C  90 03 00 0C */	stw r0, 0xc(r3)
/* 80063690 0005E590  4E 80 00 20 */	blr 
lbl_80063694:
/* 80063694 0005E594  80 03 00 0C */	lwz r0, 0xc(r3)
/* 80063698 0005E598  7C 00 20 78 */	andc r0, r0, r4
/* 8006369C 0005E59C  90 03 00 0C */	stw r0, 0xc(r3)
/* 800636A0 0005E5A0  4E 80 00 20 */	blr 

.global TestAnmFlag__Q34nw4r3g3d6AnmObjCFQ44nw4r3g3d6AnmObj7AnmFlag
TestAnmFlag__Q34nw4r3g3d6AnmObjCFQ44nw4r3g3d6AnmObj7AnmFlag:
/* 800636A4 0005E5A4  80 03 00 0C */	lwz r0, 0xc(r3)
/* 800636A8 0005E5A8  7C 03 20 38 */	and r3, r0, r4
/* 800636AC 0005E5AC  7C 03 00 D0 */	neg r0, r3
/* 800636B0 0005E5B0  7C 00 1B 78 */	or r0, r0, r3
/* 800636B4 0005E5B4  54 03 0F FE */	srwi r3, r0, 0x1f
/* 800636B8 0005E5B8  4E 80 00 20 */	blr 
