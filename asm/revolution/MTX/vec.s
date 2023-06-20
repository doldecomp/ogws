.include "macros.inc"

.section .sdata2, "a"
.balign 0x8
.global lbl_804C11F8
lbl_804C11F8:
	.incbin "baserom.dol", 0x3C9E38, 0x4
.global lbl_804C11FC
lbl_804C11FC:
	.incbin "baserom.dol", 0x3C9E3C, 0x4
.global lbl_804C1200
lbl_804C1200:
	.incbin "baserom.dol", 0x3C9E40, 0x8

.section .text, "ax"
.global PSVECAdd
PSVECAdd:
/* 800E84D4 000E33D4  E0 43 00 00 */	psq_l f2, 0(r3), 0, qr0
/* 800E84D8 000E33D8  E0 84 00 00 */	psq_l f4, 0(r4), 0, qr0
/* 800E84DC 000E33DC  10 C2 20 2A */	ps_add f6, f2, f4
/* 800E84E0 000E33E0  F0 C5 00 00 */	psq_st f6, 0(r5), 0, qr0
/* 800E84E4 000E33E4  E0 63 80 08 */	psq_l f3, 8(r3), 1, qr0
/* 800E84E8 000E33E8  E0 A4 80 08 */	psq_l f5, 8(r4), 1, qr0
/* 800E84EC 000E33EC  10 E3 28 2A */	ps_add f7, f3, f5
/* 800E84F0 000E33F0  F0 E5 80 08 */	psq_st f7, 8(r5), 1, qr0
/* 800E84F4 000E33F4  4E 80 00 20 */	blr 

.global PSVECScale
PSVECScale:
/* 800E84F8 000E33F8  E0 03 00 00 */	psq_l f0, 0(r3), 0, qr0
/* 800E84FC 000E33FC  E0 43 80 08 */	psq_l f2, 8(r3), 1, qr0
/* 800E8500 000E3400  10 00 00 58 */	ps_muls0 f0, f0, f1
/* 800E8504 000E3404  10 22 00 58 */	ps_muls0 f1, f2, f1
/* 800E8508 000E3408  F0 04 00 00 */	psq_st f0, 0(r4), 0, qr0
/* 800E850C 000E340C  F0 24 80 08 */	psq_st f1, 8(r4), 1, qr0
/* 800E8510 000E3410  4E 80 00 20 */	blr 

.global PSVECNormalize
PSVECNormalize:
/* 800E8514 000E3414  E0 43 00 00 */	psq_l f2, 0(r3), 0, qr0
/* 800E8518 000E3418  E0 63 80 08 */	psq_l f3, 8(r3), 1, qr0
/* 800E851C 000E341C  10 A2 00 B2 */	ps_mul f5, f2, f2
/* 800E8520 000E3420  C0 02 97 D8 */	lfs f0, lbl_804C11F8-_SDA2_BASE_(r2)
/* 800E8524 000E3424  C0 22 97 DC */	lfs f1, lbl_804C11FC-_SDA2_BASE_(r2)
/* 800E8528 000E3428  10 83 28 FA */	ps_madd f4, f3, f3, f5
/* 800E852C 000E342C  10 84 28 D4 */	ps_sum0 f4, f4, f3, f5
/* 800E8530 000E3430  FC A0 20 34 */	frsqrte f5, f4
/* 800E8534 000E3434  EC C5 01 72 */	fmuls f6, f5, f5
/* 800E8538 000E3438  EC 05 00 32 */	fmuls f0, f5, f0
/* 800E853C 000E343C  EC C6 09 3C */	fnmsubs f6, f6, f4, f1
/* 800E8540 000E3440  EC A6 00 32 */	fmuls f5, f6, f0
/* 800E8544 000E3444  10 42 01 58 */	ps_muls0 f2, f2, f5
/* 800E8548 000E3448  10 63 01 58 */	ps_muls0 f3, f3, f5
/* 800E854C 000E344C  F0 44 00 00 */	psq_st f2, 0(r4), 0, qr0
/* 800E8550 000E3450  F0 64 80 08 */	psq_st f3, 8(r4), 1, qr0
/* 800E8554 000E3454  4E 80 00 20 */	blr 

.global PSVECMag
PSVECMag:
/* 800E8558 000E3458  E0 03 00 00 */	psq_l f0, 0(r3), 0, qr0
/* 800E855C 000E345C  C0 82 97 D8 */	lfs f4, lbl_804C11F8-_SDA2_BASE_(r2)
/* 800E8560 000E3460  10 00 00 32 */	ps_mul f0, f0, f0
/* 800E8564 000E3464  C0 23 00 08 */	lfs f1, 8(r3)
/* 800E8568 000E3468  EC 44 20 28 */	fsubs f2, f4, f4
/* 800E856C 000E346C  10 21 00 7A */	ps_madd f1, f1, f1, f0
/* 800E8570 000E3470  10 21 00 14 */	ps_sum0 f1, f1, f0, f0
/* 800E8574 000E3474  FC 01 10 00 */	fcmpu cr0, f1, f2
/* 800E8578 000E3478  4D 82 00 20 */	beqlr 
/* 800E857C 000E347C  FC 00 08 34 */	frsqrte f0, f1
/* 800E8580 000E3480  C0 62 97 DC */	lfs f3, lbl_804C11FC-_SDA2_BASE_(r2)
/* 800E8584 000E3484  EC 40 00 32 */	fmuls f2, f0, f0
/* 800E8588 000E3488  EC 00 01 32 */	fmuls f0, f0, f4
/* 800E858C 000E348C  EC 42 18 7C */	fnmsubs f2, f2, f1, f3
/* 800E8590 000E3490  EC 02 00 32 */	fmuls f0, f2, f0
/* 800E8594 000E3494  EC 21 00 32 */	fmuls f1, f1, f0
/* 800E8598 000E3498  4E 80 00 20 */	blr 

.global PSVECDotProduct
PSVECDotProduct:
/* 800E859C 000E349C  E0 43 00 04 */	psq_l f2, 4(r3), 0, qr0
/* 800E85A0 000E34A0  E0 64 00 04 */	psq_l f3, 4(r4), 0, qr0
/* 800E85A4 000E34A4  10 42 00 F2 */	ps_mul f2, f2, f3
/* 800E85A8 000E34A8  E0 A3 00 00 */	psq_l f5, 0(r3), 0, qr0
/* 800E85AC 000E34AC  E0 84 00 00 */	psq_l f4, 0(r4), 0, qr0
/* 800E85B0 000E34B0  10 65 11 3A */	ps_madd f3, f5, f4, f2
/* 800E85B4 000E34B4  10 23 10 94 */	ps_sum0 f1, f3, f2, f2
/* 800E85B8 000E34B8  4E 80 00 20 */	blr 

.global PSVECCrossProduct
PSVECCrossProduct:
/* 800E85BC 000E34BC  E0 24 00 00 */	psq_l f1, 0(r4), 0, qr0
/* 800E85C0 000E34C0  C0 43 00 08 */	lfs f2, 8(r3)
/* 800E85C4 000E34C4  E0 03 00 00 */	psq_l f0, 0(r3), 0, qr0
/* 800E85C8 000E34C8  10 C1 0C A0 */	ps_merge10 f6, f1, f1
/* 800E85CC 000E34CC  C0 64 00 08 */	lfs f3, 8(r4)
/* 800E85D0 000E34D0  10 81 00 B2 */	ps_mul f4, f1, f2
/* 800E85D4 000E34D4  10 E1 00 18 */	ps_muls0 f7, f1, f0
/* 800E85D8 000E34D8  10 A0 20 F8 */	ps_msub f5, f0, f3, f4
/* 800E85DC 000E34DC  11 00 39 B8 */	ps_msub f8, f0, f6, f7
/* 800E85E0 000E34E0  11 25 2C E0 */	ps_merge11 f9, f5, f5
/* 800E85E4 000E34E4  11 45 44 60 */	ps_merge01 f10, f5, f8
/* 800E85E8 000E34E8  F1 25 80 00 */	psq_st f9, 0(r5), 1, qr0
/* 800E85EC 000E34EC  11 40 50 50 */	ps_neg f10, f10
/* 800E85F0 000E34F0  F1 45 00 04 */	psq_st f10, 4(r5), 0, qr0
/* 800E85F4 000E34F4  4E 80 00 20 */	blr 

.global C_VECHalfAngle
C_VECHalfAngle:
/* 800E85F8 000E34F8  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 800E85FC 000E34FC  7C 08 02 A6 */	mflr r0
/* 800E8600 000E3500  C0 43 00 00 */	lfs f2, 0(r3)
/* 800E8604 000E3504  C0 23 00 04 */	lfs f1, 4(r3)
/* 800E8608 000E3508  C0 03 00 08 */	lfs f0, 8(r3)
/* 800E860C 000E350C  FC A0 10 50 */	fneg f5, f2
/* 800E8610 000E3510  C0 44 00 00 */	lfs f2, 0(r4)
/* 800E8614 000E3514  FC 80 08 50 */	fneg f4, f1
/* 800E8618 000E3518  C0 24 00 04 */	lfs f1, 4(r4)
/* 800E861C 000E351C  FC 60 00 50 */	fneg f3, f0
/* 800E8620 000E3520  C0 04 00 08 */	lfs f0, 8(r4)
/* 800E8624 000E3524  90 01 00 44 */	stw r0, 0x44(r1)
/* 800E8628 000E3528  38 61 00 20 */	addi r3, r1, 0x20
/* 800E862C 000E352C  FC 40 10 50 */	fneg f2, f2
/* 800E8630 000E3530  7C 64 1B 78 */	mr r4, r3
/* 800E8634 000E3534  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 800E8638 000E3538  FC 20 08 50 */	fneg f1, f1
/* 800E863C 000E353C  FC 00 00 50 */	fneg f0, f0
/* 800E8640 000E3540  7C BF 2B 78 */	mr r31, r5
/* 800E8644 000E3544  D0 A1 00 20 */	stfs f5, 0x20(r1)
/* 800E8648 000E3548  D0 81 00 24 */	stfs f4, 0x24(r1)
/* 800E864C 000E354C  D0 61 00 28 */	stfs f3, 0x28(r1)
/* 800E8650 000E3550  D0 41 00 14 */	stfs f2, 0x14(r1)
/* 800E8654 000E3554  D0 21 00 18 */	stfs f1, 0x18(r1)
/* 800E8658 000E3558  D0 01 00 1C */	stfs f0, 0x1c(r1)
/* 800E865C 000E355C  4B FF FE B9 */	bl PSVECNormalize
/* 800E8660 000E3560  38 61 00 14 */	addi r3, r1, 0x14
/* 800E8664 000E3564  7C 64 1B 78 */	mr r4, r3
/* 800E8668 000E3568  4B FF FE AD */	bl PSVECNormalize
/* 800E866C 000E356C  38 61 00 20 */	addi r3, r1, 0x20
/* 800E8670 000E3570  38 81 00 14 */	addi r4, r1, 0x14
/* 800E8674 000E3574  38 A1 00 08 */	addi r5, r1, 8
/* 800E8678 000E3578  4B FF FE 5D */	bl PSVECAdd
/* 800E867C 000E357C  38 61 00 08 */	addi r3, r1, 8
/* 800E8680 000E3580  7C 64 1B 78 */	mr r4, r3
/* 800E8684 000E3584  4B FF FF 19 */	bl PSVECDotProduct
/* 800E8688 000E3588  C0 02 97 E0 */	lfs f0, lbl_804C1200-_SDA2_BASE_(r2)
/* 800E868C 000E358C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800E8690 000E3590  40 81 00 14 */	ble lbl_800E86A4
/* 800E8694 000E3594  7F E4 FB 78 */	mr r4, r31
/* 800E8698 000E3598  38 61 00 08 */	addi r3, r1, 8
/* 800E869C 000E359C  4B FF FE 79 */	bl PSVECNormalize
/* 800E86A0 000E35A0  48 00 00 1C */	b lbl_800E86BC
lbl_800E86A4:
/* 800E86A4 000E35A4  80 61 00 08 */	lwz r3, 8(r1)
/* 800E86A8 000E35A8  80 01 00 0C */	lwz r0, 0xc(r1)
/* 800E86AC 000E35AC  90 7F 00 00 */	stw r3, 0(r31)
/* 800E86B0 000E35B0  90 1F 00 04 */	stw r0, 4(r31)
/* 800E86B4 000E35B4  80 01 00 10 */	lwz r0, 0x10(r1)
/* 800E86B8 000E35B8  90 1F 00 08 */	stw r0, 8(r31)
lbl_800E86BC:
/* 800E86BC 000E35BC  80 01 00 44 */	lwz r0, 0x44(r1)
/* 800E86C0 000E35C0  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 800E86C4 000E35C4  7C 08 03 A6 */	mtlr r0
/* 800E86C8 000E35C8  38 21 00 40 */	addi r1, r1, 0x40
/* 800E86CC 000E35CC  4E 80 00 20 */	blr 

.global PSVECSquareDistance
PSVECSquareDistance:
/* 800E86D0 000E35D0  E0 03 00 04 */	psq_l f0, 4(r3), 0, qr0
/* 800E86D4 000E35D4  E0 24 00 04 */	psq_l f1, 4(r4), 0, qr0
/* 800E86D8 000E35D8  E0 43 00 00 */	psq_l f2, 0(r3), 0, qr0
/* 800E86DC 000E35DC  10 60 08 28 */	ps_sub f3, f0, f1
/* 800E86E0 000E35E0  E0 04 00 00 */	psq_l f0, 0(r4), 0, qr0
/* 800E86E4 000E35E4  10 02 00 28 */	ps_sub f0, f2, f0
/* 800E86E8 000E35E8  10 63 00 F2 */	ps_mul f3, f3, f3
/* 800E86EC 000E35EC  10 20 18 3A */	ps_madd f1, f0, f0, f3
/* 800E86F0 000E35F0  10 21 18 D4 */	ps_sum0 f1, f1, f3, f3
/* 800E86F4 000E35F4  4E 80 00 20 */	blr 
