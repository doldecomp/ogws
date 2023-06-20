.include "macros.inc"

.section .sdata2, "a"
.balign 0x8
.global lbl_804C11C0
lbl_804C11C0:
	.incbin "baserom.dol", 0x3C9E00, 0x4
.global lbl_804C11C4
lbl_804C11C4:
	.incbin "baserom.dol", 0x3C9E04, 0x4
.global lbl_804C11C8
lbl_804C11C8:
	.incbin "baserom.dol", 0x3C9E08, 0x4
.global lbl_804C11CC
lbl_804C11CC:
	.incbin "baserom.dol", 0x3C9E0C, 0x4
.global lbl_804C11D0
lbl_804C11D0:
	.incbin "baserom.dol", 0x3C9E10, 0x4
.global lbl_804C11D4
lbl_804C11D4:
	.incbin "baserom.dol", 0x3C9E14, 0x4
.global lbl_804C11D8
lbl_804C11D8:
	.incbin "baserom.dol", 0x3C9E18, 0x8

.section .sdata, "wa"
.balign 0x8
Unit01:
	.single 0e0
	.single 0e1

.section .text, "ax"
.global PSMTXIdentity
PSMTXIdentity:
/* 800E75F8 000E24F8  C0 02 97 A4 */	lfs f0, lbl_804C11C4-_SDA2_BASE_(r2)
/* 800E75FC 000E24FC  C0 22 97 A0 */	lfs f1, lbl_804C11C0-_SDA2_BASE_(r2)
/* 800E7600 000E2500  F0 03 00 08 */	psq_st f0, 8(r3), 0, qr0
/* 800E7604 000E2504  10 41 04 A0 */	ps_merge10 f2, f1, f0
/* 800E7608 000E2508  10 20 0C 60 */	ps_merge01 f1, f0, f1
/* 800E760C 000E250C  F0 03 00 18 */	psq_st f0, 24(r3), 0, qr0
/* 800E7610 000E2510  F0 03 00 20 */	psq_st f0, 32(r3), 0, qr0
/* 800E7614 000E2514  F0 23 00 10 */	psq_st f1, 16(r3), 0, qr0
/* 800E7618 000E2518  F0 43 00 00 */	psq_st f2, 0(r3), 0, qr0
/* 800E761C 000E251C  F0 43 00 28 */	psq_st f2, 40(r3), 0, qr0
/* 800E7620 000E2520  4E 80 00 20 */	blr 

.global PSMTXCopy
PSMTXCopy:
/* 800E7624 000E2524  E0 03 00 00 */	psq_l f0, 0(r3), 0, qr0
/* 800E7628 000E2528  F0 04 00 00 */	psq_st f0, 0(r4), 0, qr0
/* 800E762C 000E252C  E0 23 00 08 */	psq_l f1, 8(r3), 0, qr0
/* 800E7630 000E2530  F0 24 00 08 */	psq_st f1, 8(r4), 0, qr0
/* 800E7634 000E2534  E0 43 00 10 */	psq_l f2, 16(r3), 0, qr0
/* 800E7638 000E2538  F0 44 00 10 */	psq_st f2, 16(r4), 0, qr0
/* 800E763C 000E253C  E0 63 00 18 */	psq_l f3, 24(r3), 0, qr0
/* 800E7640 000E2540  F0 64 00 18 */	psq_st f3, 24(r4), 0, qr0
/* 800E7644 000E2544  E0 83 00 20 */	psq_l f4, 32(r3), 0, qr0
/* 800E7648 000E2548  F0 84 00 20 */	psq_st f4, 32(r4), 0, qr0
/* 800E764C 000E254C  E0 A3 00 28 */	psq_l f5, 40(r3), 0, qr0
/* 800E7650 000E2550  F0 A4 00 28 */	psq_st f5, 40(r4), 0, qr0
/* 800E7654 000E2554  4E 80 00 20 */	blr 

.global PSMTXConcat
PSMTXConcat:
/* 800E7658 000E2558  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 800E765C 000E255C  E0 03 00 00 */	psq_l f0, 0(r3), 0, qr0
/* 800E7660 000E2560  D9 C1 00 08 */	stfd f14, 8(r1)
/* 800E7664 000E2564  E0 C4 00 00 */	psq_l f6, 0(r4), 0, qr0
/* 800E7668 000E2568  3C C0 80 4C */	lis r6, Unit01@ha
/* 800E766C 000E256C  E0 E4 00 08 */	psq_l f7, 8(r4), 0, qr0
/* 800E7670 000E2570  D9 E1 00 10 */	stfd f15, 0x10(r1)
/* 800E7674 000E2574  38 C6 D6 60 */	addi r6, r6, Unit01@l
/* 800E7678 000E2578  DB E1 00 28 */	stfd f31, 0x28(r1)
/* 800E767C 000E257C  E1 04 00 10 */	psq_l f8, 16(r4), 0, qr0
/* 800E7680 000E2580  11 86 00 18 */	ps_muls0 f12, f6, f0
/* 800E7684 000E2584  E0 43 00 10 */	psq_l f2, 16(r3), 0, qr0
/* 800E7688 000E2588  11 A7 00 18 */	ps_muls0 f13, f7, f0
/* 800E768C 000E258C  E3 E6 00 00 */	psq_l f31, 0(r6), 0, qr0
/* 800E7690 000E2590  11 C6 00 98 */	ps_muls0 f14, f6, f2
/* 800E7694 000E2594  E1 24 00 18 */	psq_l f9, 24(r4), 0, qr0
/* 800E7698 000E2598  11 E7 00 98 */	ps_muls0 f15, f7, f2
/* 800E769C 000E259C  E0 23 00 08 */	psq_l f1, 8(r3), 0, qr0
/* 800E76A0 000E25A0  11 88 60 1E */	ps_madds1 f12, f8, f0, f12
/* 800E76A4 000E25A4  E0 63 00 18 */	psq_l f3, 24(r3), 0, qr0
/* 800E76A8 000E25A8  11 C8 70 9E */	ps_madds1 f14, f8, f2, f14
/* 800E76AC 000E25AC  E1 44 00 20 */	psq_l f10, 32(r4), 0, qr0
/* 800E76B0 000E25B0  11 A9 68 1E */	ps_madds1 f13, f9, f0, f13
/* 800E76B4 000E25B4  E1 64 00 28 */	psq_l f11, 40(r4), 0, qr0
/* 800E76B8 000E25B8  11 E9 78 9E */	ps_madds1 f15, f9, f2, f15
/* 800E76BC 000E25BC  E0 83 00 20 */	psq_l f4, 32(r3), 0, qr0
/* 800E76C0 000E25C0  E0 A3 00 28 */	psq_l f5, 40(r3), 0, qr0
/* 800E76C4 000E25C4  11 8A 60 5C */	ps_madds0 f12, f10, f1, f12
/* 800E76C8 000E25C8  11 AB 68 5C */	ps_madds0 f13, f11, f1, f13
/* 800E76CC 000E25CC  11 CA 70 DC */	ps_madds0 f14, f10, f3, f14
/* 800E76D0 000E25D0  11 EB 78 DC */	ps_madds0 f15, f11, f3, f15
/* 800E76D4 000E25D4  F1 85 00 00 */	psq_st f12, 0(r5), 0, qr0
/* 800E76D8 000E25D8  10 46 01 18 */	ps_muls0 f2, f6, f4
/* 800E76DC 000E25DC  11 BF 68 5E */	ps_madds1 f13, f31, f1, f13
/* 800E76E0 000E25E0  10 07 01 18 */	ps_muls0 f0, f7, f4
/* 800E76E4 000E25E4  F1 C5 00 10 */	psq_st f14, 16(r5), 0, qr0
/* 800E76E8 000E25E8  11 FF 78 DE */	ps_madds1 f15, f31, f3, f15
/* 800E76EC 000E25EC  F1 A5 00 08 */	psq_st f13, 8(r5), 0, qr0
/* 800E76F0 000E25F0  10 48 11 1E */	ps_madds1 f2, f8, f4, f2
/* 800E76F4 000E25F4  10 09 01 1E */	ps_madds1 f0, f9, f4, f0
/* 800E76F8 000E25F8  10 4A 11 5C */	ps_madds0 f2, f10, f5, f2
/* 800E76FC 000E25FC  C9 C1 00 08 */	lfd f14, 8(r1)
/* 800E7700 000E2600  F1 E5 00 18 */	psq_st f15, 24(r5), 0, qr0
/* 800E7704 000E2604  10 0B 01 5C */	ps_madds0 f0, f11, f5, f0
/* 800E7708 000E2608  F0 45 00 20 */	psq_st f2, 32(r5), 0, qr0
/* 800E770C 000E260C  10 1F 01 5E */	ps_madds1 f0, f31, f5, f0
/* 800E7710 000E2610  C9 E1 00 10 */	lfd f15, 0x10(r1)
/* 800E7714 000E2614  F0 05 00 28 */	psq_st f0, 40(r5), 0, qr0
/* 800E7718 000E2618  CB E1 00 28 */	lfd f31, 0x28(r1)
/* 800E771C 000E261C  38 21 00 40 */	addi r1, r1, 0x40
/* 800E7720 000E2620  4E 80 00 20 */	blr 

.global PSMTXConcatArray
PSMTXConcatArray:
/* 800E7724 000E2624  94 21 FF A0 */	stwu r1, -0x60(r1)
/* 800E7728 000E2628  DB E1 00 50 */	stfd f31, 0x50(r1)
/* 800E772C 000E262C  F3 E1 00 58 */	psq_st f31, 88(r1), 0, qr0
/* 800E7730 000E2630  DB C1 00 40 */	stfd f30, 0x40(r1)
/* 800E7734 000E2634  F3 C1 00 48 */	psq_st f30, 72(r1), 0, qr0
/* 800E7738 000E2638  DB A1 00 30 */	stfd f29, 0x30(r1)
/* 800E773C 000E263C  F3 A1 00 38 */	psq_st f29, 56(r1), 0, qr0
/* 800E7740 000E2640  DB 81 00 20 */	stfd f28, 0x20(r1)
/* 800E7744 000E2644  F3 81 00 28 */	psq_st f28, 40(r1), 0, qr0
/* 800E7748 000E2648  DB 61 00 10 */	stfd f27, 0x10(r1)
/* 800E774C 000E264C  F3 61 00 18 */	psq_st f27, 24(r1), 0, qr0
/* 800E7750 000E2650  38 06 FF FF */	addi r0, r6, -1
/* 800E7754 000E2654  E0 03 00 00 */	psq_l f0, 0(r3), 0, qr0
/* 800E7758 000E2658  E0 23 00 08 */	psq_l f1, 8(r3), 0, qr0
/* 800E775C 000E265C  38 CD 82 E0 */	addi r6, r13, Unit01-_SDA_BASE_
/* 800E7760 000E2660  E0 43 00 10 */	psq_l f2, 16(r3), 0, qr0
/* 800E7764 000E2664  E0 63 00 18 */	psq_l f3, 24(r3), 0, qr0
/* 800E7768 000E2668  E0 83 00 20 */	psq_l f4, 32(r3), 0, qr0
/* 800E776C 000E266C  E0 A3 00 28 */	psq_l f5, 40(r3), 0, qr0
/* 800E7770 000E2670  7C 09 03 A6 */	mtctr r0
/* 800E7774 000E2674  E0 C4 00 00 */	psq_l f6, 0(r4), 0, qr0
/* 800E7778 000E2678  E0 E4 00 08 */	psq_l f7, 8(r4), 0, qr0
/* 800E777C 000E267C  11 86 00 18 */	ps_muls0 f12, f6, f0
/* 800E7780 000E2680  E1 04 00 10 */	psq_l f8, 16(r4), 0, qr0
/* 800E7784 000E2684  13 E6 00 98 */	ps_muls0 f31, f6, f2
/* 800E7788 000E2688  E1 44 00 20 */	psq_l f10, 32(r4), 0, qr0
/* 800E778C 000E268C  13 A6 01 18 */	ps_muls0 f29, f6, f4
/* 800E7790 000E2690  E1 24 00 18 */	psq_l f9, 24(r4), 0, qr0
/* 800E7794 000E2694  11 88 60 1E */	ps_madds1 f12, f8, f0, f12
/* 800E7798 000E2698  E3 66 00 00 */	psq_l f27, 0(r6), 0, qr0
/* 800E779C 000E269C  13 E8 F8 9E */	ps_madds1 f31, f8, f2, f31
/* 800E77A0 000E26A0  E1 64 00 28 */	psq_l f11, 40(r4), 0, qr0
/* 800E77A4 000E26A4  13 A8 E9 1E */	ps_madds1 f29, f8, f4, f29
/* 800E77A8 000E26A8  11 A7 00 18 */	ps_muls0 f13, f7, f0
/* 800E77AC 000E26AC  13 C7 00 98 */	ps_muls0 f30, f7, f2
/* 800E77B0 000E26B0  13 87 01 18 */	ps_muls0 f28, f7, f4
/* 800E77B4 000E26B4  11 8A 60 5C */	ps_madds0 f12, f10, f1, f12
/* 800E77B8 000E26B8  13 EA F8 DC */	ps_madds0 f31, f10, f3, f31
/* 800E77BC 000E26BC  13 AA E9 5C */	ps_madds0 f29, f10, f5, f29
/* 800E77C0 000E26C0  11 A9 68 1E */	ps_madds1 f13, f9, f0, f13
/* 800E77C4 000E26C4  F1 85 00 00 */	psq_st f12, 0(r5), 0, qr0
/* 800E77C8 000E26C8  13 C9 F0 9E */	ps_madds1 f30, f9, f2, f30
/* 800E77CC 000E26CC  13 89 E1 1E */	ps_madds1 f28, f9, f4, f28
/* 800E77D0 000E26D0  F3 E5 00 10 */	psq_st f31, 16(r5), 0, qr0
lbl_800E77D4:
/* 800E77D4 000E26D4  11 AB 68 5C */	ps_madds0 f13, f11, f1, f13
/* 800E77D8 000E26D8  E0 C4 00 30 */	psq_l f6, 48(r4), 0, qr0
/* 800E77DC 000E26DC  13 CB F0 DC */	ps_madds0 f30, f11, f3, f30
/* 800E77E0 000E26E0  F3 A5 00 20 */	psq_st f29, 32(r5), 0, qr0
/* 800E77E4 000E26E4  13 8B E1 5C */	ps_madds0 f28, f11, f5, f28
/* 800E77E8 000E26E8  E1 04 00 40 */	psq_l f8, 64(r4), 0, qr0
/* 800E77EC 000E26EC  11 BB 68 7A */	ps_madd f13, f27, f1, f13
/* 800E77F0 000E26F0  E1 44 00 50 */	psq_l f10, 80(r4), 0, qr0
/* 800E77F4 000E26F4  11 86 00 18 */	ps_muls0 f12, f6, f0
/* 800E77F8 000E26F8  E0 E4 00 38 */	psq_l f7, 56(r4), 0, qr0
/* 800E77FC 000E26FC  13 E6 00 98 */	ps_muls0 f31, f6, f2
/* 800E7800 000E2700  E1 24 00 48 */	psq_l f9, 72(r4), 0, qr0
/* 800E7804 000E2704  F1 A5 00 08 */	psq_st f13, 8(r5), 0, qr0
/* 800E7808 000E2708  13 DB F0 FA */	ps_madd f30, f27, f3, f30
/* 800E780C 000E270C  11 88 60 1E */	ps_madds1 f12, f8, f0, f12
/* 800E7810 000E2710  E1 64 00 58 */	psq_l f11, 88(r4), 0, qr0
/* 800E7814 000E2714  13 A6 01 18 */	ps_muls0 f29, f6, f4
/* 800E7818 000E2718  38 84 00 30 */	addi r4, r4, 0x30
/* 800E781C 000E271C  F3 C5 00 18 */	psq_st f30, 24(r5), 0, qr0
/* 800E7820 000E2720  13 9B E1 7A */	ps_madd f28, f27, f5, f28
/* 800E7824 000E2724  13 E8 F8 9E */	ps_madds1 f31, f8, f2, f31
/* 800E7828 000E2728  13 A8 E9 1E */	ps_madds1 f29, f8, f4, f29
/* 800E782C 000E272C  F3 85 00 28 */	psq_st f28, 40(r5), 0, qr0
/* 800E7830 000E2730  11 8A 60 5C */	ps_madds0 f12, f10, f1, f12
/* 800E7834 000E2734  11 A7 00 18 */	ps_muls0 f13, f7, f0
/* 800E7838 000E2738  13 C7 00 98 */	ps_muls0 f30, f7, f2
/* 800E783C 000E273C  13 87 01 18 */	ps_muls0 f28, f7, f4
/* 800E7840 000E2740  F1 85 00 30 */	psq_st f12, 48(r5), 0, qr0
/* 800E7844 000E2744  13 EA F8 DC */	ps_madds0 f31, f10, f3, f31
/* 800E7848 000E2748  13 AA E9 5C */	ps_madds0 f29, f10, f5, f29
/* 800E784C 000E274C  11 A9 68 1E */	ps_madds1 f13, f9, f0, f13
/* 800E7850 000E2750  F3 E5 00 40 */	psq_st f31, 64(r5), 0, qr0
/* 800E7854 000E2754  13 C9 F0 9E */	ps_madds1 f30, f9, f2, f30
/* 800E7858 000E2758  13 89 E1 1E */	ps_madds1 f28, f9, f4, f28
/* 800E785C 000E275C  38 A5 00 30 */	addi r5, r5, 0x30
/* 800E7860 000E2760  42 00 FF 74 */	bdnz lbl_800E77D4
/* 800E7864 000E2764  11 AB 68 5C */	ps_madds0 f13, f11, f1, f13
/* 800E7868 000E2768  F3 A5 00 20 */	psq_st f29, 32(r5), 0, qr0
/* 800E786C 000E276C  13 CB F0 DC */	ps_madds0 f30, f11, f3, f30
/* 800E7870 000E2770  13 8B E1 5C */	ps_madds0 f28, f11, f5, f28
/* 800E7874 000E2774  11 BB 68 7A */	ps_madd f13, f27, f1, f13
/* 800E7878 000E2778  13 DB F0 FA */	ps_madd f30, f27, f3, f30
/* 800E787C 000E277C  13 9B E1 7A */	ps_madd f28, f27, f5, f28
/* 800E7880 000E2780  F1 A5 00 08 */	psq_st f13, 8(r5), 0, qr0
/* 800E7884 000E2784  F3 C5 00 18 */	psq_st f30, 24(r5), 0, qr0
/* 800E7888 000E2788  F3 85 00 28 */	psq_st f28, 40(r5), 0, qr0
/* 800E788C 000E278C  E3 E1 00 58 */	psq_l f31, 88(r1), 0, qr0
/* 800E7890 000E2790  CB E1 00 50 */	lfd f31, 0x50(r1)
/* 800E7894 000E2794  E3 C1 00 48 */	psq_l f30, 72(r1), 0, qr0
/* 800E7898 000E2798  CB C1 00 40 */	lfd f30, 0x40(r1)
/* 800E789C 000E279C  E3 A1 00 38 */	psq_l f29, 56(r1), 0, qr0
/* 800E78A0 000E27A0  CB A1 00 30 */	lfd f29, 0x30(r1)
/* 800E78A4 000E27A4  E3 81 00 28 */	psq_l f28, 40(r1), 0, qr0
/* 800E78A8 000E27A8  CB 81 00 20 */	lfd f28, 0x20(r1)
/* 800E78AC 000E27AC  E3 61 00 18 */	psq_l f27, 24(r1), 0, qr0
/* 800E78B0 000E27B0  CB 61 00 10 */	lfd f27, 0x10(r1)
/* 800E78B4 000E27B4  38 21 00 60 */	addi r1, r1, 0x60
/* 800E78B8 000E27B8  4E 80 00 20 */	blr 

.global PSMTXTranspose
PSMTXTranspose:
/* 800E78BC 000E27BC  E0 23 00 00 */	psq_l f1, 0(r3), 0, qr0
/* 800E78C0 000E27C0  E0 43 00 10 */	psq_l f2, 16(r3), 0, qr0
/* 800E78C4 000E27C4  C0 02 97 A4 */	lfs f0, lbl_804C11C4-_SDA2_BASE_(r2)
/* 800E78C8 000E27C8  10 81 14 20 */	ps_merge00 f4, f1, f2
/* 800E78CC 000E27CC  E0 63 80 08 */	psq_l f3, 8(r3), 1, qr0
/* 800E78D0 000E27D0  10 A1 14 E0 */	ps_merge11 f5, f1, f2
/* 800E78D4 000E27D4  E0 43 80 18 */	psq_l f2, 24(r3), 1, qr0
/* 800E78D8 000E27D8  E0 23 00 20 */	psq_l f1, 32(r3), 0, qr0
/* 800E78DC 000E27DC  10 43 14 20 */	ps_merge00 f2, f3, f2
/* 800E78E0 000E27E0  F0 84 00 00 */	psq_st f4, 0(r4), 0, qr0
/* 800E78E4 000E27E4  10 81 04 20 */	ps_merge00 f4, f1, f0
/* 800E78E8 000E27E8  C0 63 00 28 */	lfs f3, 0x28(r3)
/* 800E78EC 000E27EC  F0 A4 00 10 */	psq_st f5, 16(r4), 0, qr0
/* 800E78F0 000E27F0  10 A1 04 A0 */	ps_merge10 f5, f1, f0
/* 800E78F4 000E27F4  D0 04 00 2C */	stfs f0, 0x2c(r4)
/* 800E78F8 000E27F8  F0 44 00 20 */	psq_st f2, 32(r4), 0, qr0
/* 800E78FC 000E27FC  F0 84 00 08 */	psq_st f4, 8(r4), 0, qr0
/* 800E7900 000E2800  F0 A4 00 18 */	psq_st f5, 24(r4), 0, qr0
/* 800E7904 000E2804  D0 64 00 28 */	stfs f3, 0x28(r4)
/* 800E7908 000E2808  4E 80 00 20 */	blr 

.global PSMTXInverse
PSMTXInverse:
/* 800E790C 000E280C  E0 03 80 00 */	psq_l f0, 0(r3), 1, qr0
/* 800E7910 000E2810  E0 23 00 04 */	psq_l f1, 4(r3), 0, qr0
/* 800E7914 000E2814  E0 43 80 10 */	psq_l f2, 16(r3), 1, qr0
/* 800E7918 000E2818  10 C1 04 A0 */	ps_merge10 f6, f1, f0
/* 800E791C 000E281C  E0 63 00 14 */	psq_l f3, 20(r3), 0, qr0
/* 800E7920 000E2820  E0 83 80 20 */	psq_l f4, 32(r3), 1, qr0
/* 800E7924 000E2824  10 E3 14 A0 */	ps_merge10 f7, f3, f2
/* 800E7928 000E2828  E0 A3 00 24 */	psq_l f5, 36(r3), 0, qr0
/* 800E792C 000E282C  11 63 01 B2 */	ps_mul f11, f3, f6
/* 800E7930 000E2830  11 A5 01 F2 */	ps_mul f13, f5, f7
/* 800E7934 000E2834  11 05 24 A0 */	ps_merge10 f8, f5, f4
/* 800E7938 000E2838  11 61 59 F8 */	ps_msub f11, f1, f7, f11
/* 800E793C 000E283C  11 81 02 32 */	ps_mul f12, f1, f8
/* 800E7940 000E2840  11 A3 6A 38 */	ps_msub f13, f3, f8, f13
/* 800E7944 000E2844  11 43 01 32 */	ps_mul f10, f3, f4
/* 800E7948 000E2848  11 85 61 B8 */	ps_msub f12, f5, f6, f12
/* 800E794C 000E284C  11 20 01 72 */	ps_mul f9, f0, f5
/* 800E7950 000E2850  11 01 00 B2 */	ps_mul f8, f1, f2
/* 800E7954 000E2854  10 C6 30 28 */	ps_sub f6, f6, f6
/* 800E7958 000E2858  11 42 51 78 */	ps_msub f10, f2, f5, f10
/* 800E795C 000E285C  10 E0 03 72 */	ps_mul f7, f0, f13
/* 800E7960 000E2860  11 21 49 38 */	ps_msub f9, f1, f4, f9
/* 800E7964 000E2864  10 E2 3B 3A */	ps_madd f7, f2, f12, f7
/* 800E7968 000E2868  11 00 40 F8 */	ps_msub f8, f0, f3, f8
/* 800E796C 000E286C  10 E4 3A FA */	ps_madd f7, f4, f11, f7
/* 800E7970 000E2870  10 07 30 40 */	ps_cmpo0 cr0, f7, f6
/* 800E7974 000E2874  40 82 00 0C */	bne lbl_800E7980
/* 800E7978 000E2878  38 60 00 00 */	li r3, 0
/* 800E797C 000E287C  4E 80 00 20 */	blr 
lbl_800E7980:
/* 800E7980 000E2880  EC 00 38 30 */	fres f0, f7
/* 800E7984 000E2884  10 C0 00 2A */	ps_add f6, f0, f0
/* 800E7988 000E2888  10 A0 00 32 */	ps_mul f5, f0, f0
/* 800E798C 000E288C  10 07 31 7C */	ps_nmsub f0, f7, f5, f6
/* 800E7990 000E2890  C0 23 00 0C */	lfs f1, 0xc(r3)
/* 800E7994 000E2894  11 AD 00 18 */	ps_muls0 f13, f13, f0
/* 800E7998 000E2898  C0 43 00 1C */	lfs f2, 0x1c(r3)
/* 800E799C 000E289C  11 8C 00 18 */	ps_muls0 f12, f12, f0
/* 800E79A0 000E28A0  C0 63 00 2C */	lfs f3, 0x2c(r3)
/* 800E79A4 000E28A4  11 6B 00 18 */	ps_muls0 f11, f11, f0
/* 800E79A8 000E28A8  10 AD 64 20 */	ps_merge00 f5, f13, f12
/* 800E79AC 000E28AC  11 4A 00 18 */	ps_muls0 f10, f10, f0
/* 800E79B0 000E28B0  10 8D 64 E0 */	ps_merge11 f4, f13, f12
/* 800E79B4 000E28B4  11 29 00 18 */	ps_muls0 f9, f9, f0
/* 800E79B8 000E28B8  F0 A4 00 00 */	psq_st f5, 0(r4), 0, qr0
/* 800E79BC 000E28BC  10 CD 00 72 */	ps_mul f6, f13, f1
/* 800E79C0 000E28C0  F0 84 00 10 */	psq_st f4, 16(r4), 0, qr0
/* 800E79C4 000E28C4  11 08 00 18 */	ps_muls0 f8, f8, f0
/* 800E79C8 000E28C8  10 CC 30 BA */	ps_madd f6, f12, f2, f6
/* 800E79CC 000E28CC  F1 44 80 20 */	psq_st f10, 32(r4), 1, qr0
/* 800E79D0 000E28D0  10 CB 30 FE */	ps_nmadd f6, f11, f3, f6
/* 800E79D4 000E28D4  F1 24 80 24 */	psq_st f9, 36(r4), 1, qr0
/* 800E79D8 000E28D8  10 EA 00 72 */	ps_mul f7, f10, f1
/* 800E79DC 000E28DC  10 AB 34 20 */	ps_merge00 f5, f11, f6
/* 800E79E0 000E28E0  F1 04 80 28 */	psq_st f8, 40(r4), 1, qr0
/* 800E79E4 000E28E4  10 8B 34 E0 */	ps_merge11 f4, f11, f6
/* 800E79E8 000E28E8  F0 A4 00 08 */	psq_st f5, 8(r4), 0, qr0
/* 800E79EC 000E28EC  10 E9 38 BA */	ps_madd f7, f9, f2, f7
/* 800E79F0 000E28F0  F0 84 00 18 */	psq_st f4, 24(r4), 0, qr0
/* 800E79F4 000E28F4  10 E8 38 FE */	ps_nmadd f7, f8, f3, f7
/* 800E79F8 000E28F8  38 60 00 01 */	li r3, 1
/* 800E79FC 000E28FC  F0 E4 80 2C */	psq_st f7, 44(r4), 1, qr0
/* 800E7A00 000E2900  4E 80 00 20 */	blr 

.global PSMTXInvXpose
PSMTXInvXpose:
/* 800E7A04 000E2904  E0 03 80 00 */	psq_l f0, 0(r3), 1, qr0
/* 800E7A08 000E2908  E0 23 00 04 */	psq_l f1, 4(r3), 0, qr0
/* 800E7A0C 000E290C  E0 43 80 10 */	psq_l f2, 16(r3), 1, qr0
/* 800E7A10 000E2910  10 C1 04 A0 */	ps_merge10 f6, f1, f0
/* 800E7A14 000E2914  E0 63 00 14 */	psq_l f3, 20(r3), 0, qr0
/* 800E7A18 000E2918  E0 83 80 20 */	psq_l f4, 32(r3), 1, qr0
/* 800E7A1C 000E291C  10 E3 14 A0 */	ps_merge10 f7, f3, f2
/* 800E7A20 000E2920  E0 A3 00 24 */	psq_l f5, 36(r3), 0, qr0
/* 800E7A24 000E2924  11 63 01 B2 */	ps_mul f11, f3, f6
/* 800E7A28 000E2928  11 05 24 A0 */	ps_merge10 f8, f5, f4
/* 800E7A2C 000E292C  11 A5 01 F2 */	ps_mul f13, f5, f7
/* 800E7A30 000E2930  11 61 59 F8 */	ps_msub f11, f1, f7, f11
/* 800E7A34 000E2934  11 81 02 32 */	ps_mul f12, f1, f8
/* 800E7A38 000E2938  11 A3 6A 38 */	ps_msub f13, f3, f8, f13
/* 800E7A3C 000E293C  11 85 61 B8 */	ps_msub f12, f5, f6, f12
/* 800E7A40 000E2940  11 43 01 32 */	ps_mul f10, f3, f4
/* 800E7A44 000E2944  11 20 01 72 */	ps_mul f9, f0, f5
/* 800E7A48 000E2948  11 01 00 B2 */	ps_mul f8, f1, f2
/* 800E7A4C 000E294C  11 42 51 78 */	ps_msub f10, f2, f5, f10
/* 800E7A50 000E2950  11 21 49 38 */	ps_msub f9, f1, f4, f9
/* 800E7A54 000E2954  11 00 40 F8 */	ps_msub f8, f0, f3, f8
/* 800E7A58 000E2958  10 E0 03 72 */	ps_mul f7, f0, f13
/* 800E7A5C 000E295C  10 21 08 28 */	ps_sub f1, f1, f1
/* 800E7A60 000E2960  10 E2 3B 3A */	ps_madd f7, f2, f12, f7
/* 800E7A64 000E2964  10 E4 3A FA */	ps_madd f7, f4, f11, f7
/* 800E7A68 000E2968  10 07 08 40 */	ps_cmpo0 cr0, f7, f1
/* 800E7A6C 000E296C  40 82 00 0C */	bne lbl_800E7A78
/* 800E7A70 000E2970  38 60 00 00 */	li r3, 0
/* 800E7A74 000E2974  4E 80 00 20 */	blr 
lbl_800E7A78:
/* 800E7A78 000E2978  EC 00 38 30 */	fres f0, f7
/* 800E7A7C 000E297C  F0 24 80 0C */	psq_st f1, 12(r4), 1, qr0
/* 800E7A80 000E2980  10 C0 00 2A */	ps_add f6, f0, f0
/* 800E7A84 000E2984  10 A0 00 32 */	ps_mul f5, f0, f0
/* 800E7A88 000E2988  F0 24 80 1C */	psq_st f1, 28(r4), 1, qr0
/* 800E7A8C 000E298C  10 07 31 7C */	ps_nmsub f0, f7, f5, f6
/* 800E7A90 000E2990  F0 24 80 2C */	psq_st f1, 44(r4), 1, qr0
/* 800E7A94 000E2994  11 AD 00 18 */	ps_muls0 f13, f13, f0
/* 800E7A98 000E2998  11 8C 00 18 */	ps_muls0 f12, f12, f0
/* 800E7A9C 000E299C  11 6B 00 18 */	ps_muls0 f11, f11, f0
/* 800E7AA0 000E29A0  F1 A4 00 00 */	psq_st f13, 0(r4), 0, qr0
/* 800E7AA4 000E29A4  F1 84 00 10 */	psq_st f12, 16(r4), 0, qr0
/* 800E7AA8 000E29A8  11 4A 00 18 */	ps_muls0 f10, f10, f0
/* 800E7AAC 000E29AC  11 29 00 18 */	ps_muls0 f9, f9, f0
/* 800E7AB0 000E29B0  F1 64 00 20 */	psq_st f11, 32(r4), 0, qr0
/* 800E7AB4 000E29B4  F1 44 80 08 */	psq_st f10, 8(r4), 1, qr0
/* 800E7AB8 000E29B8  11 08 00 18 */	ps_muls0 f8, f8, f0
/* 800E7ABC 000E29BC  38 60 00 01 */	li r3, 1
/* 800E7AC0 000E29C0  F1 24 80 18 */	psq_st f9, 24(r4), 1, qr0
/* 800E7AC4 000E29C4  F1 04 80 28 */	psq_st f8, 40(r4), 1, qr0
/* 800E7AC8 000E29C8  4E 80 00 20 */	blr 

.global PSMTXRotRad
PSMTXRotRad:
/* 800E7ACC 000E29CC  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 800E7AD0 000E29D0  7C 08 02 A6 */	mflr r0
/* 800E7AD4 000E29D4  90 01 00 34 */	stw r0, 0x34(r1)
/* 800E7AD8 000E29D8  DB E1 00 20 */	stfd f31, 0x20(r1)
/* 800E7ADC 000E29DC  F3 E1 00 28 */	psq_st f31, 40(r1), 0, qr0
/* 800E7AE0 000E29E0  DB C1 00 10 */	stfd f30, 0x10(r1)
/* 800E7AE4 000E29E4  F3 C1 00 18 */	psq_st f30, 24(r1), 0, qr0
/* 800E7AE8 000E29E8  FF C0 08 90 */	fmr f30, f1
/* 800E7AEC 000E29EC  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800E7AF0 000E29F0  7C 9F 23 78 */	mr r31, r4
/* 800E7AF4 000E29F4  93 C1 00 08 */	stw r30, 8(r1)
/* 800E7AF8 000E29F8  7C 7E 1B 78 */	mr r30, r3
/* 800E7AFC 000E29FC  4B FD 92 25 */	bl sin
/* 800E7B00 000E2A00  FF E0 08 18 */	frsp f31, f1
/* 800E7B04 000E2A04  FC 20 F0 90 */	fmr f1, f30
/* 800E7B08 000E2A08  4B FD 8D 11 */	bl cos
/* 800E7B0C 000E2A0C  FC 40 08 18 */	frsp f2, f1
/* 800E7B10 000E2A10  7F C3 F3 78 */	mr r3, r30
/* 800E7B14 000E2A14  FC 20 F8 90 */	fmr f1, f31
/* 800E7B18 000E2A18  7F E4 07 74 */	extsb r4, r31
/* 800E7B1C 000E2A1C  48 00 00 2D */	bl PSMTXRotTrig
/* 800E7B20 000E2A20  E3 E1 00 28 */	psq_l f31, 40(r1), 0, qr0
/* 800E7B24 000E2A24  CB E1 00 20 */	lfd f31, 0x20(r1)
/* 800E7B28 000E2A28  E3 C1 00 18 */	psq_l f30, 24(r1), 0, qr0
/* 800E7B2C 000E2A2C  CB C1 00 10 */	lfd f30, 0x10(r1)
/* 800E7B30 000E2A30  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 800E7B34 000E2A34  80 01 00 34 */	lwz r0, 0x34(r1)
/* 800E7B38 000E2A38  83 C1 00 08 */	lwz r30, 8(r1)
/* 800E7B3C 000E2A3C  7C 08 03 A6 */	mtlr r0
/* 800E7B40 000E2A40  38 21 00 30 */	addi r1, r1, 0x30
/* 800E7B44 000E2A44  4E 80 00 20 */	blr 

.global PSMTXRotTrig
PSMTXRotTrig:
/* 800E7B48 000E2A48  FC A0 08 18 */	frsp f5, f1
/* 800E7B4C 000E2A4C  60 80 00 20 */	ori r0, r4, 0x20
/* 800E7B50 000E2A50  FC 80 10 18 */	frsp f4, f2
/* 800E7B54 000E2A54  28 00 00 78 */	cmplwi r0, 0x78
/* 800E7B58 000E2A58  C0 02 97 A4 */	lfs f0, lbl_804C11C4-_SDA2_BASE_(r2)
/* 800E7B5C 000E2A5C  10 40 28 50 */	ps_neg f2, f5
/* 800E7B60 000E2A60  C0 22 97 A0 */	lfs f1, lbl_804C11C0-_SDA2_BASE_(r2)
/* 800E7B64 000E2A64  41 82 00 18 */	beq lbl_800E7B7C
/* 800E7B68 000E2A68  28 00 00 79 */	cmplwi r0, 0x79
/* 800E7B6C 000E2A6C  41 82 00 38 */	beq lbl_800E7BA4
/* 800E7B70 000E2A70  28 00 00 7A */	cmplwi r0, 0x7a
/* 800E7B74 000E2A74  41 82 00 5C */	beq lbl_800E7BD0
/* 800E7B78 000E2A78  4E 80 00 20 */	blr 
lbl_800E7B7C:
/* 800E7B7C 000E2A7C  10 65 24 20 */	ps_merge00 f3, f5, f4
/* 800E7B80 000E2A80  F0 23 80 00 */	psq_st f1, 0(r3), 1, qr0
/* 800E7B84 000E2A84  10 24 14 20 */	ps_merge00 f1, f4, f2
/* 800E7B88 000E2A88  F0 03 00 04 */	psq_st f0, 4(r3), 0, qr0
/* 800E7B8C 000E2A8C  F0 03 00 0C */	psq_st f0, 12(r3), 0, qr0
/* 800E7B90 000E2A90  F0 03 00 1C */	psq_st f0, 28(r3), 0, qr0
/* 800E7B94 000E2A94  F0 03 80 2C */	psq_st f0, 44(r3), 1, qr0
/* 800E7B98 000E2A98  F0 63 00 24 */	psq_st f3, 36(r3), 0, qr0
/* 800E7B9C 000E2A9C  F0 23 00 14 */	psq_st f1, 20(r3), 0, qr0
/* 800E7BA0 000E2AA0  4E 80 00 20 */	blr 
lbl_800E7BA4:
/* 800E7BA4 000E2AA4  10 64 04 20 */	ps_merge00 f3, f4, f0
/* 800E7BA8 000E2AA8  F0 03 00 18 */	psq_st f0, 24(r3), 0, qr0
/* 800E7BAC 000E2AAC  10 20 0C 20 */	ps_merge00 f1, f0, f1
/* 800E7BB0 000E2AB0  10 42 04 20 */	ps_merge00 f2, f2, f0
/* 800E7BB4 000E2AB4  10 05 04 20 */	ps_merge00 f0, f5, f0
/* 800E7BB8 000E2AB8  F0 63 00 00 */	psq_st f3, 0(r3), 0, qr0
/* 800E7BBC 000E2ABC  F0 63 00 28 */	psq_st f3, 40(r3), 0, qr0
/* 800E7BC0 000E2AC0  F0 23 00 10 */	psq_st f1, 16(r3), 0, qr0
/* 800E7BC4 000E2AC4  F0 03 00 08 */	psq_st f0, 8(r3), 0, qr0
/* 800E7BC8 000E2AC8  F0 43 00 20 */	psq_st f2, 32(r3), 0, qr0
/* 800E7BCC 000E2ACC  4E 80 00 20 */	blr 
lbl_800E7BD0:
/* 800E7BD0 000E2AD0  10 65 24 20 */	ps_merge00 f3, f5, f4
/* 800E7BD4 000E2AD4  F0 03 00 08 */	psq_st f0, 8(r3), 0, qr0
/* 800E7BD8 000E2AD8  10 44 14 20 */	ps_merge00 f2, f4, f2
/* 800E7BDC 000E2ADC  10 21 04 20 */	ps_merge00 f1, f1, f0
/* 800E7BE0 000E2AE0  F0 03 00 18 */	psq_st f0, 24(r3), 0, qr0
/* 800E7BE4 000E2AE4  F0 03 00 20 */	psq_st f0, 32(r3), 0, qr0
/* 800E7BE8 000E2AE8  F0 63 00 10 */	psq_st f3, 16(r3), 0, qr0
/* 800E7BEC 000E2AEC  F0 43 00 00 */	psq_st f2, 0(r3), 0, qr0
/* 800E7BF0 000E2AF0  F0 23 00 28 */	psq_st f1, 40(r3), 0, qr0
/* 800E7BF4 000E2AF4  4E 80 00 20 */	blr 

.global __PSMTXRotAxisRadInternal
__PSMTXRotAxisRadInternal:
/* 800E7BF8 000E2AF8  E0 64 00 00 */	psq_l f3, 0(r4), 0, qr0
/* 800E7BFC 000E2AFC  FD 60 10 18 */	frsp f11, f2
/* 800E7C00 000E2B00  C1 42 97 A8 */	lfs f10, lbl_804C11C8-_SDA2_BASE_(r2)
/* 800E7C04 000E2B04  FD 80 08 18 */	frsp f12, f1
/* 800E7C08 000E2B08  10 83 00 F2 */	ps_mul f4, f3, f3
/* 800E7C0C 000E2B0C  C0 44 00 08 */	lfs f2, 8(r4)
/* 800E7C10 000E2B10  ED 0A 50 2A */	fadds f8, f10, f10
/* 800E7C14 000E2B14  C1 22 97 AC */	lfs f9, lbl_804C11CC-_SDA2_BASE_(r2)
/* 800E7C18 000E2B18  EC 2A 50 28 */	fsubs f1, f10, f10
/* 800E7C1C 000E2B1C  10 A2 20 BA */	ps_madd f5, f2, f2, f4
/* 800E7C20 000E2B20  EC 08 58 28 */	fsubs f0, f8, f11
/* 800E7C24 000E2B24  11 6B 5C 20 */	ps_merge00 f11, f11, f11
/* 800E7C28 000E2B28  10 C5 20 94 */	ps_sum0 f6, f5, f2, f4
/* 800E7C2C 000E2B2C  FC E0 30 34 */	frsqrte f7, f6
/* 800E7C30 000E2B30  EC 87 01 F2 */	fmuls f4, f7, f7
/* 800E7C34 000E2B34  EC A7 02 B2 */	fmuls f5, f7, f10
/* 800E7C38 000E2B38  EC 84 49 BC */	fnmsubs f4, f4, f6, f9
/* 800E7C3C 000E2B3C  EC E4 01 72 */	fmuls f7, f4, f5
/* 800E7C40 000E2B40  10 63 01 D8 */	ps_muls0 f3, f3, f7
/* 800E7C44 000E2B44  10 42 01 D8 */	ps_muls0 f2, f2, f7
/* 800E7C48 000E2B48  10 C3 00 18 */	ps_muls0 f6, f3, f0
/* 800E7C4C 000E2B4C  10 E2 00 18 */	ps_muls0 f7, f2, f0
/* 800E7C50 000E2B50  11 43 03 18 */	ps_muls0 f10, f3, f12
/* 800E7C54 000E2B54  10 A6 00 DA */	ps_muls1 f5, f6, f3
/* 800E7C58 000E2B58  10 86 00 D8 */	ps_muls0 f4, f6, f3
/* 800E7C5C 000E2B5C  10 C6 00 98 */	ps_muls0 f6, f6, f2
/* 800E7C60 000E2B60  EC 02 2B 3C */	fnmsubs f0, f2, f12, f5
/* 800E7C64 000E2B64  10 60 50 50 */	ps_neg f3, f10
/* 800E7C68 000E2B68  ED 02 2B 3A */	fmadds f8, f2, f12, f5
/* 800E7C6C 000E2B6C  10 84 58 14 */	ps_sum0 f4, f4, f0, f11
/* 800E7C70 000E2B70  10 03 30 54 */	ps_sum0 f0, f3, f1, f6
/* 800E7C74 000E2B74  10 E7 00 98 */	ps_muls0 f7, f7, f2
/* 800E7C78 000E2B78  11 26 50 54 */	ps_sum0 f9, f6, f1, f10
/* 800E7C7C 000E2B7C  F0 83 00 00 */	psq_st f4, 0(r3), 0, qr0
/* 800E7C80 000E2B80  10 66 19 94 */	ps_sum0 f3, f6, f6, f3
/* 800E7C84 000E2B84  10 AB 2A 16 */	ps_sum1 f5, f11, f8, f5
/* 800E7C88 000E2B88  F0 03 00 18 */	psq_st f0, 24(r3), 0, qr0
/* 800E7C8C 000E2B8C  10 E7 58 54 */	ps_sum0 f7, f7, f1, f11
/* 800E7C90 000E2B90  10 CA 30 D6 */	ps_sum1 f6, f10, f3, f6
/* 800E7C94 000E2B94  F1 23 00 08 */	psq_st f9, 8(r3), 0, qr0
/* 800E7C98 000E2B98  F0 A3 00 10 */	psq_st f5, 16(r3), 0, qr0
/* 800E7C9C 000E2B9C  F0 C3 00 20 */	psq_st f6, 32(r3), 0, qr0
/* 800E7CA0 000E2BA0  F0 E3 00 28 */	psq_st f7, 40(r3), 0, qr0
/* 800E7CA4 000E2BA4  4E 80 00 20 */	blr 

.global PSMTXRotAxisRad
PSMTXRotAxisRad:
/* 800E7CA8 000E2BA8  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 800E7CAC 000E2BAC  7C 08 02 A6 */	mflr r0
/* 800E7CB0 000E2BB0  90 01 00 34 */	stw r0, 0x34(r1)
/* 800E7CB4 000E2BB4  DB E1 00 20 */	stfd f31, 0x20(r1)
/* 800E7CB8 000E2BB8  F3 E1 00 28 */	psq_st f31, 40(r1), 0, qr0
/* 800E7CBC 000E2BBC  DB C1 00 10 */	stfd f30, 0x10(r1)
/* 800E7CC0 000E2BC0  F3 C1 00 18 */	psq_st f30, 24(r1), 0, qr0
/* 800E7CC4 000E2BC4  FF C0 08 90 */	fmr f30, f1
/* 800E7CC8 000E2BC8  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800E7CCC 000E2BCC  7C 9F 23 78 */	mr r31, r4
/* 800E7CD0 000E2BD0  93 C1 00 08 */	stw r30, 8(r1)
/* 800E7CD4 000E2BD4  7C 7E 1B 78 */	mr r30, r3
/* 800E7CD8 000E2BD8  4B FD 90 49 */	bl sin
/* 800E7CDC 000E2BDC  FF E0 08 18 */	frsp f31, f1
/* 800E7CE0 000E2BE0  FC 20 F0 90 */	fmr f1, f30
/* 800E7CE4 000E2BE4  4B FD 8B 35 */	bl cos
/* 800E7CE8 000E2BE8  FC 40 08 18 */	frsp f2, f1
/* 800E7CEC 000E2BEC  7F C3 F3 78 */	mr r3, r30
/* 800E7CF0 000E2BF0  FC 20 F8 90 */	fmr f1, f31
/* 800E7CF4 000E2BF4  7F E4 FB 78 */	mr r4, r31
/* 800E7CF8 000E2BF8  4B FF FF 01 */	bl __PSMTXRotAxisRadInternal
/* 800E7CFC 000E2BFC  E3 E1 00 28 */	psq_l f31, 40(r1), 0, qr0
/* 800E7D00 000E2C00  CB E1 00 20 */	lfd f31, 0x20(r1)
/* 800E7D04 000E2C04  E3 C1 00 18 */	psq_l f30, 24(r1), 0, qr0
/* 800E7D08 000E2C08  CB C1 00 10 */	lfd f30, 0x10(r1)
/* 800E7D0C 000E2C0C  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 800E7D10 000E2C10  80 01 00 34 */	lwz r0, 0x34(r1)
/* 800E7D14 000E2C14  83 C1 00 08 */	lwz r30, 8(r1)
/* 800E7D18 000E2C18  7C 08 03 A6 */	mtlr r0
/* 800E7D1C 000E2C1C  38 21 00 30 */	addi r1, r1, 0x30
/* 800E7D20 000E2C20  4E 80 00 20 */	blr 

.global PSMTXTrans
PSMTXTrans:
/* 800E7D24 000E2C24  C0 02 97 A4 */	lfs f0, lbl_804C11C4-_SDA2_BASE_(r2)
/* 800E7D28 000E2C28  C0 82 97 A0 */	lfs f4, lbl_804C11C0-_SDA2_BASE_(r2)
/* 800E7D2C 000E2C2C  D0 23 00 0C */	stfs f1, 0xc(r3)
/* 800E7D30 000E2C30  D0 43 00 1C */	stfs f2, 0x1c(r3)
/* 800E7D34 000E2C34  F0 03 00 04 */	psq_st f0, 4(r3), 0, qr0
/* 800E7D38 000E2C38  F0 03 00 20 */	psq_st f0, 32(r3), 0, qr0
/* 800E7D3C 000E2C3C  D0 03 00 10 */	stfs f0, 0x10(r3)
/* 800E7D40 000E2C40  D0 83 00 14 */	stfs f4, 0x14(r3)
/* 800E7D44 000E2C44  D0 03 00 18 */	stfs f0, 0x18(r3)
/* 800E7D48 000E2C48  D0 83 00 28 */	stfs f4, 0x28(r3)
/* 800E7D4C 000E2C4C  D0 63 00 2C */	stfs f3, 0x2c(r3)
/* 800E7D50 000E2C50  D0 83 00 00 */	stfs f4, 0(r3)
/* 800E7D54 000E2C54  4E 80 00 20 */	blr 

.global PSMTXTransApply
PSMTXTransApply:
/* 800E7D58 000E2C58  E0 83 00 00 */	psq_l f4, 0(r3), 0, qr0
/* 800E7D5C 000E2C5C  FC 20 08 18 */	frsp f1, f1
/* 800E7D60 000E2C60  E0 A3 00 08 */	psq_l f5, 8(r3), 0, qr0
/* 800E7D64 000E2C64  FC 40 10 18 */	frsp f2, f2
/* 800E7D68 000E2C68  E0 E3 00 18 */	psq_l f7, 24(r3), 0, qr0
/* 800E7D6C 000E2C6C  FC 60 18 18 */	frsp f3, f3
/* 800E7D70 000E2C70  E1 03 00 28 */	psq_l f8, 40(r3), 0, qr0
/* 800E7D74 000E2C74  F0 84 00 00 */	psq_st f4, 0(r4), 0, qr0
/* 800E7D78 000E2C78  10 A1 29 56 */	ps_sum1 f5, f1, f5, f5
/* 800E7D7C 000E2C7C  E0 C3 00 10 */	psq_l f6, 16(r3), 0, qr0
/* 800E7D80 000E2C80  F0 A4 00 08 */	psq_st f5, 8(r4), 0, qr0
/* 800E7D84 000E2C84  10 E2 39 D6 */	ps_sum1 f7, f2, f7, f7
/* 800E7D88 000E2C88  E1 23 00 20 */	psq_l f9, 32(r3), 0, qr0
/* 800E7D8C 000E2C8C  F0 C4 00 10 */	psq_st f6, 16(r4), 0, qr0
/* 800E7D90 000E2C90  11 03 42 16 */	ps_sum1 f8, f3, f8, f8
/* 800E7D94 000E2C94  F0 E4 00 18 */	psq_st f7, 24(r4), 0, qr0
/* 800E7D98 000E2C98  F1 24 00 20 */	psq_st f9, 32(r4), 0, qr0
/* 800E7D9C 000E2C9C  F1 04 00 28 */	psq_st f8, 40(r4), 0, qr0
/* 800E7DA0 000E2CA0  4E 80 00 20 */	blr 

.global PSMTXScale
PSMTXScale:
/* 800E7DA4 000E2CA4  C0 02 97 A4 */	lfs f0, lbl_804C11C4-_SDA2_BASE_(r2)
/* 800E7DA8 000E2CA8  D0 23 00 00 */	stfs f1, 0(r3)
/* 800E7DAC 000E2CAC  F0 03 00 04 */	psq_st f0, 4(r3), 0, qr0
/* 800E7DB0 000E2CB0  F0 03 00 0C */	psq_st f0, 12(r3), 0, qr0
/* 800E7DB4 000E2CB4  D0 43 00 14 */	stfs f2, 0x14(r3)
/* 800E7DB8 000E2CB8  F0 03 00 18 */	psq_st f0, 24(r3), 0, qr0
/* 800E7DBC 000E2CBC  F0 03 00 20 */	psq_st f0, 32(r3), 0, qr0
/* 800E7DC0 000E2CC0  D0 63 00 28 */	stfs f3, 0x28(r3)
/* 800E7DC4 000E2CC4  D0 03 00 2C */	stfs f0, 0x2c(r3)
/* 800E7DC8 000E2CC8  4E 80 00 20 */	blr 

.global PSMTXScaleApply
PSMTXScaleApply:
/* 800E7DCC 000E2CCC  FC 20 08 18 */	frsp f1, f1
/* 800E7DD0 000E2CD0  E0 83 00 00 */	psq_l f4, 0(r3), 0, qr0
/* 800E7DD4 000E2CD4  FC 40 10 18 */	frsp f2, f2
/* 800E7DD8 000E2CD8  E0 A3 00 08 */	psq_l f5, 8(r3), 0, qr0
/* 800E7DDC 000E2CDC  FC 60 18 18 */	frsp f3, f3
/* 800E7DE0 000E2CE0  10 84 00 58 */	ps_muls0 f4, f4, f1
/* 800E7DE4 000E2CE4  E0 C3 00 10 */	psq_l f6, 16(r3), 0, qr0
/* 800E7DE8 000E2CE8  10 A5 00 58 */	ps_muls0 f5, f5, f1
/* 800E7DEC 000E2CEC  E0 E3 00 18 */	psq_l f7, 24(r3), 0, qr0
/* 800E7DF0 000E2CF0  10 C6 00 98 */	ps_muls0 f6, f6, f2
/* 800E7DF4 000E2CF4  E1 03 00 20 */	psq_l f8, 32(r3), 0, qr0
/* 800E7DF8 000E2CF8  F0 84 00 00 */	psq_st f4, 0(r4), 0, qr0
/* 800E7DFC 000E2CFC  10 E7 00 98 */	ps_muls0 f7, f7, f2
/* 800E7E00 000E2D00  E0 43 00 28 */	psq_l f2, 40(r3), 0, qr0
/* 800E7E04 000E2D04  F0 A4 00 08 */	psq_st f5, 8(r4), 0, qr0
/* 800E7E08 000E2D08  11 08 00 D8 */	ps_muls0 f8, f8, f3
/* 800E7E0C 000E2D0C  F0 C4 00 10 */	psq_st f6, 16(r4), 0, qr0
/* 800E7E10 000E2D10  10 42 00 D8 */	ps_muls0 f2, f2, f3
/* 800E7E14 000E2D14  F0 E4 00 18 */	psq_st f7, 24(r4), 0, qr0
/* 800E7E18 000E2D18  F1 04 00 20 */	psq_st f8, 32(r4), 0, qr0
/* 800E7E1C 000E2D1C  F0 44 00 28 */	psq_st f2, 40(r4), 0, qr0
/* 800E7E20 000E2D20  4E 80 00 20 */	blr 

.global PSMTXQuat
PSMTXQuat:
/* 800E7E24 000E2D24  E0 84 00 00 */	psq_l f4, 0(r4), 0, qr0
/* 800E7E28 000E2D28  E0 A4 00 08 */	psq_l f5, 8(r4), 0, qr0
/* 800E7E2C 000E2D2C  10 C4 01 32 */	ps_mul f6, f4, f4
/* 800E7E30 000E2D30  C0 22 97 A0 */	lfs f1, lbl_804C11C0-_SDA2_BASE_(r2)
/* 800E7E34 000E2D34  11 24 24 A0 */	ps_merge10 f9, f4, f4
/* 800E7E38 000E2D38  EC 01 08 28 */	fsubs f0, f1, f1
/* 800E7E3C 000E2D3C  11 05 31 7A */	ps_madd f8, f5, f5, f6
/* 800E7E40 000E2D40  11 45 01 5A */	ps_muls1 f10, f5, f5
/* 800E7E44 000E2D44  EC 41 08 2A */	fadds f2, f1, f1
/* 800E7E48 000E2D48  F0 03 80 0C */	psq_st f0, 12(r3), 1, qr0
/* 800E7E4C 000E2D4C  10 68 42 14 */	ps_sum0 f3, f8, f8, f8
/* 800E7E50 000E2D50  10 E5 01 72 */	ps_mul f7, f5, f5
/* 800E7E54 000E2D54  F0 03 80 2C */	psq_st f0, 44(r3), 1, qr0
/* 800E7E58 000E2D58  11 84 52 7A */	ps_madd f12, f4, f9, f10
/* 800E7E5C 000E2D5C  ED A0 18 30 */	fres f13, f3
/* 800E7E60 000E2D60  10 63 13 7C */	ps_nmsub f3, f3, f13, f2
/* 800E7E64 000E2D64  11 69 01 5A */	ps_muls1 f11, f9, f5
/* 800E7E68 000E2D68  11 44 52 78 */	ps_msub f10, f4, f9, f10
/* 800E7E6C 000E2D6C  10 6D 00 F2 */	ps_mul f3, f13, f3
/* 800E7E70 000E2D70  11 24 59 5C */	ps_madds0 f9, f4, f5, f11
/* 800E7E74 000E2D74  11 07 32 16 */	ps_sum1 f8, f7, f8, f6
/* 800E7E78 000E2D78  EC 63 00 B2 */	fmuls f3, f3, f2
/* 800E7E7C 000E2D7C  11 6B 48 BC */	ps_nmsub f11, f11, f2, f9
/* 800E7E80 000E2D80  10 C6 31 94 */	ps_sum0 f6, f6, f6, f6
/* 800E7E84 000E2D84  11 29 00 F2 */	ps_mul f9, f9, f3
/* 800E7E88 000E2D88  11 6B 00 F2 */	ps_mul f11, f11, f3
/* 800E7E8C 000E2D8C  11 08 08 FC */	ps_nmsub f8, f8, f3, f1
/* 800E7E90 000E2D90  11 8C 00 F2 */	ps_mul f12, f12, f3
/* 800E7E94 000E2D94  F1 23 80 08 */	psq_st f9, 8(r3), 1, qr0
/* 800E7E98 000E2D98  11 4A 00 F2 */	ps_mul f10, f10, f3
/* 800E7E9C 000E2D9C  10 EB 04 A0 */	ps_merge10 f7, f11, f0
/* 800E7EA0 000E2DA0  10 AC 44 20 */	ps_merge00 f5, f12, f8
/* 800E7EA4 000E2DA4  10 88 54 A0 */	ps_merge10 f4, f8, f10
/* 800E7EA8 000E2DA8  11 AB 4C 60 */	ps_merge01 f13, f11, f9
/* 800E7EAC 000E2DAC  F0 E3 00 18 */	psq_st f7, 24(r3), 0, qr0
/* 800E7EB0 000E2DB0  10 C6 08 FC */	ps_nmsub f6, f6, f3, f1
/* 800E7EB4 000E2DB4  F0 A3 00 10 */	psq_st f5, 16(r3), 0, qr0
/* 800E7EB8 000E2DB8  F0 C3 80 28 */	psq_st f6, 40(r3), 1, qr0
/* 800E7EBC 000E2DBC  F0 83 00 00 */	psq_st f4, 0(r3), 0, qr0
/* 800E7EC0 000E2DC0  F1 A3 00 20 */	psq_st f13, 32(r3), 0, qr0
/* 800E7EC4 000E2DC4  4E 80 00 20 */	blr 

.global C_MTXLookAt
C_MTXLookAt:
/* 800E7EC8 000E2DC8  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 800E7ECC 000E2DCC  7C 08 02 A6 */	mflr r0
/* 800E7ED0 000E2DD0  C0 24 00 00 */	lfs f1, 0(r4)
/* 800E7ED4 000E2DD4  90 01 00 44 */	stw r0, 0x44(r1)
/* 800E7ED8 000E2DD8  C0 06 00 00 */	lfs f0, 0(r6)
/* 800E7EDC 000E2DDC  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 800E7EE0 000E2DE0  7C BF 2B 78 */	mr r31, r5
/* 800E7EE4 000E2DE4  EC 81 00 28 */	fsubs f4, f1, f0
/* 800E7EE8 000E2DE8  C0 64 00 04 */	lfs f3, 4(r4)
/* 800E7EEC 000E2DEC  93 C1 00 38 */	stw r30, 0x38(r1)
/* 800E7EF0 000E2DF0  7C 9E 23 78 */	mr r30, r4
/* 800E7EF4 000E2DF4  C0 46 00 04 */	lfs f2, 4(r6)
/* 800E7EF8 000E2DF8  93 A1 00 34 */	stw r29, 0x34(r1)
/* 800E7EFC 000E2DFC  EC 43 10 28 */	fsubs f2, f3, f2
/* 800E7F00 000E2E00  C0 24 00 08 */	lfs f1, 8(r4)
/* 800E7F04 000E2E04  C0 06 00 08 */	lfs f0, 8(r6)
/* 800E7F08 000E2E08  7C 7D 1B 78 */	mr r29, r3
/* 800E7F0C 000E2E0C  38 61 00 20 */	addi r3, r1, 0x20
/* 800E7F10 000E2E10  D0 81 00 20 */	stfs f4, 0x20(r1)
/* 800E7F14 000E2E14  EC 01 00 28 */	fsubs f0, f1, f0
/* 800E7F18 000E2E18  D0 41 00 24 */	stfs f2, 0x24(r1)
/* 800E7F1C 000E2E1C  7C 64 1B 78 */	mr r4, r3
/* 800E7F20 000E2E20  D0 01 00 28 */	stfs f0, 0x28(r1)
/* 800E7F24 000E2E24  48 00 05 F1 */	bl PSVECNormalize
/* 800E7F28 000E2E28  7F E3 FB 78 */	mr r3, r31
/* 800E7F2C 000E2E2C  38 81 00 20 */	addi r4, r1, 0x20
/* 800E7F30 000E2E30  38 A1 00 14 */	addi r5, r1, 0x14
/* 800E7F34 000E2E34  48 00 06 89 */	bl PSVECCrossProduct
/* 800E7F38 000E2E38  38 61 00 14 */	addi r3, r1, 0x14
/* 800E7F3C 000E2E3C  7C 64 1B 78 */	mr r4, r3
/* 800E7F40 000E2E40  48 00 05 D5 */	bl PSVECNormalize
/* 800E7F44 000E2E44  38 61 00 20 */	addi r3, r1, 0x20
/* 800E7F48 000E2E48  38 81 00 14 */	addi r4, r1, 0x14
/* 800E7F4C 000E2E4C  38 A1 00 08 */	addi r5, r1, 8
/* 800E7F50 000E2E50  48 00 06 6D */	bl PSVECCrossProduct
/* 800E7F54 000E2E54  C0 01 00 14 */	lfs f0, 0x14(r1)
/* 800E7F58 000E2E58  C0 9E 00 00 */	lfs f4, 0(r30)
/* 800E7F5C 000E2E5C  D0 1D 00 00 */	stfs f0, 0(r29)
/* 800E7F60 000E2E60  C0 7E 00 04 */	lfs f3, 4(r30)
/* 800E7F64 000E2E64  C0 01 00 18 */	lfs f0, 0x18(r1)
/* 800E7F68 000E2E68  C0 BE 00 08 */	lfs f5, 8(r30)
/* 800E7F6C 000E2E6C  D0 1D 00 04 */	stfs f0, 4(r29)
/* 800E7F70 000E2E70  C0 01 00 1C */	lfs f0, 0x1c(r1)
/* 800E7F74 000E2E74  D0 1D 00 08 */	stfs f0, 8(r29)
/* 800E7F78 000E2E78  C0 21 00 14 */	lfs f1, 0x14(r1)
/* 800E7F7C 000E2E7C  C0 01 00 18 */	lfs f0, 0x18(r1)
/* 800E7F80 000E2E80  EC 24 00 72 */	fmuls f1, f4, f1
/* 800E7F84 000E2E84  C0 41 00 1C */	lfs f2, 0x1c(r1)
/* 800E7F88 000E2E88  EC 03 00 32 */	fmuls f0, f3, f0
/* 800E7F8C 000E2E8C  EC 45 00 B2 */	fmuls f2, f5, f2
/* 800E7F90 000E2E90  EC 01 00 2A */	fadds f0, f1, f0
/* 800E7F94 000E2E94  EC 02 00 2A */	fadds f0, f2, f0
/* 800E7F98 000E2E98  FC 00 00 50 */	fneg f0, f0
/* 800E7F9C 000E2E9C  D0 1D 00 0C */	stfs f0, 0xc(r29)
/* 800E7FA0 000E2EA0  C0 01 00 08 */	lfs f0, 8(r1)
/* 800E7FA4 000E2EA4  D0 1D 00 10 */	stfs f0, 0x10(r29)
/* 800E7FA8 000E2EA8  C0 01 00 0C */	lfs f0, 0xc(r1)
/* 800E7FAC 000E2EAC  D0 1D 00 14 */	stfs f0, 0x14(r29)
/* 800E7FB0 000E2EB0  C0 01 00 10 */	lfs f0, 0x10(r1)
/* 800E7FB4 000E2EB4  D0 1D 00 18 */	stfs f0, 0x18(r29)
/* 800E7FB8 000E2EB8  C0 21 00 08 */	lfs f1, 8(r1)
/* 800E7FBC 000E2EBC  C0 01 00 0C */	lfs f0, 0xc(r1)
/* 800E7FC0 000E2EC0  C0 41 00 10 */	lfs f2, 0x10(r1)
/* 800E7FC4 000E2EC4  EC 24 00 72 */	fmuls f1, f4, f1
/* 800E7FC8 000E2EC8  EC 03 00 32 */	fmuls f0, f3, f0
/* 800E7FCC 000E2ECC  EC 45 00 B2 */	fmuls f2, f5, f2
/* 800E7FD0 000E2ED0  EC 01 00 2A */	fadds f0, f1, f0
/* 800E7FD4 000E2ED4  EC 02 00 2A */	fadds f0, f2, f0
/* 800E7FD8 000E2ED8  FC 00 00 50 */	fneg f0, f0
/* 800E7FDC 000E2EDC  D0 1D 00 1C */	stfs f0, 0x1c(r29)
/* 800E7FE0 000E2EE0  C0 01 00 20 */	lfs f0, 0x20(r1)
/* 800E7FE4 000E2EE4  D0 1D 00 20 */	stfs f0, 0x20(r29)
/* 800E7FE8 000E2EE8  C0 01 00 24 */	lfs f0, 0x24(r1)
/* 800E7FEC 000E2EEC  D0 1D 00 24 */	stfs f0, 0x24(r29)
/* 800E7FF0 000E2EF0  C0 01 00 28 */	lfs f0, 0x28(r1)
/* 800E7FF4 000E2EF4  D0 1D 00 28 */	stfs f0, 0x28(r29)
/* 800E7FF8 000E2EF8  C0 21 00 20 */	lfs f1, 0x20(r1)
/* 800E7FFC 000E2EFC  C0 01 00 24 */	lfs f0, 0x24(r1)
/* 800E8000 000E2F00  C0 41 00 28 */	lfs f2, 0x28(r1)
/* 800E8004 000E2F04  EC 24 00 72 */	fmuls f1, f4, f1
/* 800E8008 000E2F08  EC 03 00 32 */	fmuls f0, f3, f0
/* 800E800C 000E2F0C  EC 45 00 B2 */	fmuls f2, f5, f2
/* 800E8010 000E2F10  EC 01 00 2A */	fadds f0, f1, f0
/* 800E8014 000E2F14  EC 02 00 2A */	fadds f0, f2, f0
/* 800E8018 000E2F18  FC 00 00 50 */	fneg f0, f0
/* 800E801C 000E2F1C  D0 1D 00 2C */	stfs f0, 0x2c(r29)
/* 800E8020 000E2F20  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 800E8024 000E2F24  83 C1 00 38 */	lwz r30, 0x38(r1)
/* 800E8028 000E2F28  83 A1 00 34 */	lwz r29, 0x34(r1)
/* 800E802C 000E2F2C  80 01 00 44 */	lwz r0, 0x44(r1)
/* 800E8030 000E2F30  7C 08 03 A6 */	mtlr r0
/* 800E8034 000E2F34  38 21 00 40 */	addi r1, r1, 0x40
/* 800E8038 000E2F38  4E 80 00 20 */	blr 

.global C_MTXLightFrustum
C_MTXLightFrustum:
/* 800E803C 000E2F3C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800E8040 000E2F40  DB E1 00 10 */	stfd f31, 0x10(r1)
/* 800E8044 000E2F44  F3 E1 00 18 */	psq_st f31, 24(r1), 0, qr0
/* 800E8048 000E2F48  EC 04 18 28 */	fsubs f0, f4, f3
/* 800E804C 000E2F4C  C1 42 97 A4 */	lfs f10, lbl_804C11C4-_SDA2_BASE_(r2)
/* 800E8050 000E2F50  C1 82 97 A0 */	lfs f12, lbl_804C11C0-_SDA2_BASE_(r2)
/* 800E8054 000E2F54  ED 21 10 28 */	fsubs f9, f1, f2
/* 800E8058 000E2F58  C1 62 97 B0 */	lfs f11, lbl_804C11D0-_SDA2_BASE_(r2)
/* 800E805C 000E2F5C  EC 64 18 2A */	fadds f3, f4, f3
/* 800E8060 000E2F60  ED AC 00 24 */	fdivs f13, f12, f0
/* 800E8064 000E2F64  C0 02 97 B4 */	lfs f0, lbl_804C11D4-_SDA2_BASE_(r2)
/* 800E8068 000E2F68  C3 E1 00 28 */	lfs f31, 0x28(r1)
/* 800E806C 000E2F6C  D0 03 00 28 */	stfs f0, 0x28(r3)
/* 800E8070 000E2F70  D1 43 00 04 */	stfs f10, 4(r3)
/* 800E8074 000E2F74  D1 43 00 0C */	stfs f10, 0xc(r3)
/* 800E8078 000E2F78  EC 8B 01 72 */	fmuls f4, f11, f5
/* 800E807C 000E2F7C  D1 43 00 10 */	stfs f10, 0x10(r3)
/* 800E8080 000E2F80  EC 01 10 2A */	fadds f0, f1, f2
/* 800E8084 000E2F84  EC 2D 00 F2 */	fmuls f1, f13, f3
/* 800E8088 000E2F88  D1 43 00 1C */	stfs f10, 0x1c(r3)
/* 800E808C 000E2F8C  EC AC 48 24 */	fdivs f5, f12, f9
/* 800E8090 000E2F90  D1 43 00 20 */	stfs f10, 0x20(r3)
/* 800E8094 000E2F94  D1 43 00 24 */	stfs f10, 0x24(r3)
/* 800E8098 000E2F98  D1 43 00 2C */	stfs f10, 0x2c(r3)
/* 800E809C 000E2F9C  EC 46 00 72 */	fmuls f2, f6, f1
/* 800E80A0 000E2FA0  EC 05 00 32 */	fmuls f0, f5, f0
/* 800E80A4 000E2FA4  EC 64 03 72 */	fmuls f3, f4, f13
/* 800E80A8 000E2FA8  EC 24 01 72 */	fmuls f1, f4, f5
/* 800E80AC 000E2FAC  EC 07 00 32 */	fmuls f0, f7, f0
/* 800E80B0 000E2FB0  EC 66 00 F2 */	fmuls f3, f6, f3
/* 800E80B4 000E2FB4  EC 42 40 28 */	fsubs f2, f2, f8
/* 800E80B8 000E2FB8  EC 27 00 72 */	fmuls f1, f7, f1
/* 800E80BC 000E2FBC  EC 00 F8 28 */	fsubs f0, f0, f31
/* 800E80C0 000E2FC0  D0 63 00 00 */	stfs f3, 0(r3)
/* 800E80C4 000E2FC4  D0 43 00 08 */	stfs f2, 8(r3)
/* 800E80C8 000E2FC8  D0 23 00 14 */	stfs f1, 0x14(r3)
/* 800E80CC 000E2FCC  D0 03 00 18 */	stfs f0, 0x18(r3)
/* 800E80D0 000E2FD0  E3 E1 00 18 */	psq_l f31, 24(r1), 0, qr0
/* 800E80D4 000E2FD4  CB E1 00 10 */	lfd f31, 0x10(r1)
/* 800E80D8 000E2FD8  38 21 00 20 */	addi r1, r1, 0x20
/* 800E80DC 000E2FDC  4E 80 00 20 */	blr 

.global C_MTXLightPerspective
C_MTXLightPerspective:
/* 800E80E0 000E2FE0  94 21 FF A0 */	stwu r1, -0x60(r1)
/* 800E80E4 000E2FE4  7C 08 02 A6 */	mflr r0
/* 800E80E8 000E2FE8  90 01 00 64 */	stw r0, 0x64(r1)
/* 800E80EC 000E2FEC  DB E1 00 50 */	stfd f31, 0x50(r1)
/* 800E80F0 000E2FF0  F3 E1 00 58 */	psq_st f31, 88(r1), 0, qr0
/* 800E80F4 000E2FF4  DB C1 00 40 */	stfd f30, 0x40(r1)
/* 800E80F8 000E2FF8  F3 C1 00 48 */	psq_st f30, 72(r1), 0, qr0
/* 800E80FC 000E2FFC  DB A1 00 30 */	stfd f29, 0x30(r1)
/* 800E8100 000E3000  F3 A1 00 38 */	psq_st f29, 56(r1), 0, qr0
/* 800E8104 000E3004  DB 81 00 20 */	stfd f28, 0x20(r1)
/* 800E8108 000E3008  F3 81 00 28 */	psq_st f28, 40(r1), 0, qr0
/* 800E810C 000E300C  DB 61 00 10 */	stfd f27, 0x10(r1)
/* 800E8110 000E3010  F3 61 00 18 */	psq_st f27, 24(r1), 0, qr0
/* 800E8114 000E3014  FF 60 10 90 */	fmr f27, f2
/* 800E8118 000E3018  C0 E2 97 A8 */	lfs f7, lbl_804C11C8-_SDA2_BASE_(r2)
/* 800E811C 000E301C  FF 80 18 90 */	fmr f28, f3
/* 800E8120 000E3020  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800E8124 000E3024  FF A0 20 90 */	fmr f29, f4
/* 800E8128 000E3028  EC 27 00 72 */	fmuls f1, f7, f1
/* 800E812C 000E302C  C0 02 97 B8 */	lfs f0, lbl_804C11D8-_SDA2_BASE_(r2)
/* 800E8130 000E3030  FF C0 28 90 */	fmr f30, f5
/* 800E8134 000E3034  FF E0 30 90 */	fmr f31, f6
/* 800E8138 000E3038  7C 7F 1B 78 */	mr r31, r3
/* 800E813C 000E303C  EC 20 00 72 */	fmuls f1, f0, f1
/* 800E8140 000E3040  4B FD 8C B9 */	bl tan
/* 800E8144 000E3044  FC A0 08 18 */	frsp f5, f1
/* 800E8148 000E3048  C0 62 97 A4 */	lfs f3, lbl_804C11C4-_SDA2_BASE_(r2)
/* 800E814C 000E304C  C0 82 97 A0 */	lfs f4, lbl_804C11C0-_SDA2_BASE_(r2)
/* 800E8150 000E3050  FC 20 F8 50 */	fneg f1, f31
/* 800E8154 000E3054  C0 02 97 B4 */	lfs f0, lbl_804C11D4-_SDA2_BASE_(r2)
/* 800E8158 000E3058  FC 40 F0 50 */	fneg f2, f30
/* 800E815C 000E305C  EC 84 28 24 */	fdivs f4, f4, f5
/* 800E8160 000E3060  D0 3F 00 18 */	stfs f1, 0x18(r31)
/* 800E8164 000E3064  D0 1F 00 28 */	stfs f0, 0x28(r31)
/* 800E8168 000E3068  D0 7F 00 04 */	stfs f3, 4(r31)
/* 800E816C 000E306C  D0 5F 00 08 */	stfs f2, 8(r31)
/* 800E8170 000E3070  D0 7F 00 0C */	stfs f3, 0xc(r31)
/* 800E8174 000E3074  EC 24 D8 24 */	fdivs f1, f4, f27
/* 800E8178 000E3078  D0 7F 00 10 */	stfs f3, 0x10(r31)
/* 800E817C 000E307C  D0 7F 00 1C */	stfs f3, 0x1c(r31)
/* 800E8180 000E3080  D0 7F 00 20 */	stfs f3, 0x20(r31)
/* 800E8184 000E3084  D0 7F 00 24 */	stfs f3, 0x24(r31)
/* 800E8188 000E3088  D0 7F 00 2C */	stfs f3, 0x2c(r31)
/* 800E818C 000E308C  EC 3C 00 72 */	fmuls f1, f28, f1
/* 800E8190 000E3090  EC 04 07 72 */	fmuls f0, f4, f29
/* 800E8194 000E3094  D0 3F 00 00 */	stfs f1, 0(r31)
/* 800E8198 000E3098  D0 1F 00 14 */	stfs f0, 0x14(r31)
/* 800E819C 000E309C  E3 E1 00 58 */	psq_l f31, 88(r1), 0, qr0
/* 800E81A0 000E30A0  CB E1 00 50 */	lfd f31, 0x50(r1)
/* 800E81A4 000E30A4  E3 C1 00 48 */	psq_l f30, 72(r1), 0, qr0
/* 800E81A8 000E30A8  CB C1 00 40 */	lfd f30, 0x40(r1)
/* 800E81AC 000E30AC  E3 A1 00 38 */	psq_l f29, 56(r1), 0, qr0
/* 800E81B0 000E30B0  CB A1 00 30 */	lfd f29, 0x30(r1)
/* 800E81B4 000E30B4  E3 81 00 28 */	psq_l f28, 40(r1), 0, qr0
/* 800E81B8 000E30B8  CB 81 00 20 */	lfd f28, 0x20(r1)
/* 800E81BC 000E30BC  E3 61 00 18 */	psq_l f27, 24(r1), 0, qr0
/* 800E81C0 000E30C0  CB 61 00 10 */	lfd f27, 0x10(r1)
/* 800E81C4 000E30C4  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 800E81C8 000E30C8  80 01 00 64 */	lwz r0, 0x64(r1)
/* 800E81CC 000E30CC  7C 08 03 A6 */	mtlr r0
/* 800E81D0 000E30D0  38 21 00 60 */	addi r1, r1, 0x60
/* 800E81D4 000E30D4  4E 80 00 20 */	blr 

.global C_MTXLightOrtho
C_MTXLightOrtho:
/* 800E81D8 000E30D8  ED 64 18 28 */	fsubs f11, f4, f3
/* 800E81DC 000E30DC  C1 22 97 A4 */	lfs f9, lbl_804C11C4-_SDA2_BASE_(r2)
/* 800E81E0 000E30E0  C1 42 97 A0 */	lfs f10, lbl_804C11C0-_SDA2_BASE_(r2)
/* 800E81E4 000E30E4  EC 01 10 28 */	fsubs f0, f1, f2
/* 800E81E8 000E30E8  EC 64 18 2A */	fadds f3, f4, f3
/* 800E81EC 000E30EC  C0 82 97 B0 */	lfs f4, lbl_804C11D0-_SDA2_BASE_(r2)
/* 800E81F0 000E30F0  ED 8A 58 24 */	fdivs f12, f10, f11
/* 800E81F4 000E30F4  D1 23 00 04 */	stfs f9, 4(r3)
/* 800E81F8 000E30F8  D1 23 00 08 */	stfs f9, 8(r3)
/* 800E81FC 000E30FC  D1 23 00 10 */	stfs f9, 0x10(r3)
/* 800E8200 000E3100  D1 23 00 18 */	stfs f9, 0x18(r3)
/* 800E8204 000E3104  D1 23 00 20 */	stfs f9, 0x20(r3)
/* 800E8208 000E3108  ED 6A 00 24 */	fdivs f11, f10, f0
/* 800E820C 000E310C  D1 23 00 24 */	stfs f9, 0x24(r3)
/* 800E8210 000E3110  D1 23 00 28 */	stfs f9, 0x28(r3)
/* 800E8214 000E3114  D1 43 00 2C */	stfs f10, 0x2c(r3)
/* 800E8218 000E3118  EC 01 10 2A */	fadds f0, f1, f2
/* 800E821C 000E311C  FC 20 18 50 */	fneg f1, f3
/* 800E8220 000E3120  EC 64 03 32 */	fmuls f3, f4, f12
/* 800E8224 000E3124  FC 00 00 50 */	fneg f0, f0
/* 800E8228 000E3128  EC 4C 00 72 */	fmuls f2, f12, f1
/* 800E822C 000E312C  EC 24 02 F2 */	fmuls f1, f4, f11
/* 800E8230 000E3130  EC 0B 00 32 */	fmuls f0, f11, f0
/* 800E8234 000E3134  EC 45 00 B2 */	fmuls f2, f5, f2
/* 800E8238 000E3138  EC 63 01 72 */	fmuls f3, f3, f5
/* 800E823C 000E313C  EC 06 00 32 */	fmuls f0, f6, f0
/* 800E8240 000E3140  EC 47 10 2A */	fadds f2, f7, f2
/* 800E8244 000E3144  EC 21 01 B2 */	fmuls f1, f1, f6
/* 800E8248 000E3148  D0 63 00 00 */	stfs f3, 0(r3)
/* 800E824C 000E314C  EC 08 00 2A */	fadds f0, f8, f0
/* 800E8250 000E3150  D0 43 00 0C */	stfs f2, 0xc(r3)
/* 800E8254 000E3154  D0 23 00 14 */	stfs f1, 0x14(r3)
/* 800E8258 000E3158  D0 03 00 1C */	stfs f0, 0x1c(r3)
/* 800E825C 000E315C  4E 80 00 20 */	blr 
