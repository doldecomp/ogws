.include "macros.inc"

.section .data, "wa"  # 0x80393A80 - 0x803CAF00

.balign 0x8

# sExpTbl__Q34nw4r4math29@unnamed@math_arithmetic_cpp@
sExpTbl__Q34nw4r4math29$$2unnamed$$2math_arithmetic_cpp$$2:
	.incbin "baserom.dol", 0x3902D0, 0x108

# sLogTbl__Q34nw4r4math29@unnamed@math_arithmetic_cpp@
sLogTbl__Q34nw4r4math29$$2unnamed$$2math_arithmetic_cpp$$2:
	.incbin "baserom.dol", 0x3903D8, 0x808

.section .sdata2, "a"  # 0x804BFA20 - 0x804C69E0

.balign 0x8

lbl_804BFEA8: .single 0e1.442695
lbl_804BFEAC: .single 0e0.6931472
lbl_804BFEB0: .single 0e23.08312
lbl_804BFEB4: .single 0e256
lbl_804BFEB8: .single 0e1
lbl_804BFEBC: .single 0e0.5
lbl_804BFEC0: .single 0e3

.section .text, "ax"  # 0x800076E0 - 0x80355080

.global FExp__Q34nw4r4math6detailFf
FExp__Q34nw4r4math6detailFf:
/* 8002F75C 0002A65C  C0 02 84 88 */	lfs f0, lbl_804BFEA8-_SDA2_BASE_(r2)
/* 8002F760 0002A660  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8002F764 0002A664  EC 00 00 72 */	fmuls f0, f0, f1
/* 8002F768 0002A668  F0 01 D0 18 */	psq_st f0, 24(r1), 1, qr5
/* 8002F76C 0002A66C  A8 01 00 18 */	lha r0, 0x18(r1)
/* 8002F770 0002A670  B0 01 00 0A */	sth r0, 0xa(r1)
/* 8002F774 0002A674  E0 41 D0 0A */	psq_l f2, 10(r1), 1, qr5
/* 8002F778 0002A678  C0 62 84 8C */	lfs f3, lbl_804BFEAC-_SDA2_BASE_(r2)
/* 8002F77C 0002A67C  C0 02 84 90 */	lfs f0, lbl_804BFEB0-_SDA2_BASE_(r2)
/* 8002F780 0002A680  EC 43 00 B2 */	fmuls f2, f3, f2
/* 8002F784 0002A684  EC 21 10 28 */	fsubs f1, f1, f2
/* 8002F788 0002A688  EC 23 08 2A */	fadds f1, f3, f1
/* 8002F78C 0002A68C  EC 20 00 72 */	fmuls f1, f0, f1
/* 8002F790 0002A690  F0 21 B0 14 */	psq_st f1, 20(r1), 1, qr3
/* 8002F794 0002A694  A0 61 00 14 */	lhz r3, 0x14(r1)
/* 8002F798 0002A698  B0 61 00 08 */	sth r3, 8(r1)
/* 8002F79C 0002A69C  E0 01 B0 08 */	psq_l f0, 8(r1), 1, qr3
/* 8002F7A0 0002A6A0  3C A0 80 39 */	lis r5, sExpTbl__Q34nw4r4math29$$2unnamed$$2math_arithmetic_cpp$$2@ha
/* 8002F7A4 0002A6A4  54 66 18 38 */	slwi r6, r3, 3
/* 8002F7A8 0002A6A8  54 03 B8 10 */	slwi r3, r0, 0x17
/* 8002F7AC 0002A6AC  38 A5 41 D0 */	addi r5, r5, sExpTbl__Q34nw4r4math29$$2unnamed$$2math_arithmetic_cpp$$2@l
/* 8002F7B0 0002A6B0  EC 41 00 28 */	fsubs f2, f1, f0
/* 8002F7B4 0002A6B4  7C 85 32 14 */	add r4, r5, r6
/* 8002F7B8 0002A6B8  7C 05 34 2E */	lfsx f0, r5, r6
/* 8002F7BC 0002A6BC  C0 24 00 04 */	lfs f1, 4(r4)
/* 8002F7C0 0002A6C0  EC 22 00 72 */	fmuls f1, f2, f1
/* 8002F7C4 0002A6C4  EC 00 08 2A */	fadds f0, f0, f1
/* 8002F7C8 0002A6C8  D0 01 00 10 */	stfs f0, 0x10(r1)
/* 8002F7CC 0002A6CC  80 01 00 10 */	lwz r0, 0x10(r1)
/* 8002F7D0 0002A6D0  7C 03 02 14 */	add r0, r3, r0
/* 8002F7D4 0002A6D4  54 00 00 7E */	clrlwi r0, r0, 1
/* 8002F7D8 0002A6D8  90 01 00 0C */	stw r0, 0xc(r1)
/* 8002F7DC 0002A6DC  C0 21 00 0C */	lfs f1, 0xc(r1)
/* 8002F7E0 0002A6E0  38 21 00 20 */	addi r1, r1, 0x20
/* 8002F7E4 0002A6E4  4E 80 00 20 */	blr 

.global FLog__Q34nw4r4math6detailFf
FLog__Q34nw4r4math6detailFf:
/* 8002F7E8 0002A6E8  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8002F7EC 0002A6EC  D0 21 00 18 */	stfs f1, 0x18(r1)
/* 8002F7F0 0002A6F0  D0 21 00 10 */	stfs f1, 0x10(r1)
/* 8002F7F4 0002A6F4  80 61 00 18 */	lwz r3, 0x18(r1)
/* 8002F7F8 0002A6F8  80 01 00 10 */	lwz r0, 0x10(r1)
/* 8002F7FC 0002A6FC  54 63 4E 3E */	rlwinm r3, r3, 9, 0x18, 0x1f
/* 8002F800 0002A700  54 00 02 40 */	rlwinm r0, r0, 0, 9, 0
/* 8002F804 0002A704  38 63 FF 81 */	addi r3, r3, -127
/* 8002F808 0002A708  64 00 3F 80 */	oris r0, r0, 0x3f80
/* 8002F80C 0002A70C  B0 61 00 0A */	sth r3, 0xa(r1)
/* 8002F810 0002A710  90 01 00 14 */	stw r0, 0x14(r1)
/* 8002F814 0002A714  C0 41 00 14 */	lfs f2, 0x14(r1)
/* 8002F818 0002A718  E0 61 D0 0A */	psq_l f3, 10(r1), 1, qr5
/* 8002F81C 0002A71C  C0 22 84 98 */	lfs f1, lbl_804BFEB8-_SDA2_BASE_(r2)
/* 8002F820 0002A720  C0 02 84 94 */	lfs f0, lbl_804BFEB4-_SDA2_BASE_(r2)
/* 8002F824 0002A724  EC 22 08 28 */	fsubs f1, f2, f1
/* 8002F828 0002A728  EC 40 00 72 */	fmuls f2, f0, f1
/* 8002F82C 0002A72C  F0 41 B0 0C */	psq_st f2, 12(r1), 1, qr3
/* 8002F830 0002A730  A0 01 00 0C */	lhz r0, 0xc(r1)
/* 8002F834 0002A734  B0 01 00 08 */	sth r0, 8(r1)
/* 8002F838 0002A738  E0 21 B0 08 */	psq_l f1, 8(r1), 1, qr3
/* 8002F83C 0002A73C  3C 80 80 39 */	lis r4, sLogTbl__Q34nw4r4math29$$2unnamed$$2math_arithmetic_cpp$$2@ha
/* 8002F840 0002A740  C0 02 84 8C */	lfs f0, lbl_804BFEAC-_SDA2_BASE_(r2)
/* 8002F844 0002A744  54 00 18 38 */	slwi r0, r0, 3
/* 8002F848 0002A748  38 84 42 D8 */	addi r4, r4, sLogTbl__Q34nw4r4math29$$2unnamed$$2math_arithmetic_cpp$$2@l
/* 8002F84C 0002A74C  EC 82 08 28 */	fsubs f4, f2, f1
/* 8002F850 0002A750  7C 64 02 14 */	add r3, r4, r0
/* 8002F854 0002A754  7C 24 04 2E */	lfsx f1, r4, r0
/* 8002F858 0002A758  C0 43 00 04 */	lfs f2, 4(r3)
/* 8002F85C 0002A75C  EC 00 00 F2 */	fmuls f0, f0, f3
/* 8002F860 0002A760  EC 44 00 B2 */	fmuls f2, f4, f2
/* 8002F864 0002A764  EC 21 10 2A */	fadds f1, f1, f2
/* 8002F868 0002A768  EC 21 00 2A */	fadds f1, f1, f0
/* 8002F86C 0002A76C  38 21 00 20 */	addi r1, r1, 0x20
/* 8002F870 0002A770  4E 80 00 20 */	blr 

.global FrSqrt__Q24nw4r4mathFf
FrSqrt__Q24nw4r4mathFf:
/* 8002F874 0002A774  FC 00 08 34 */	frsqrte f0, f1
/* 8002F878 0002A778  C0 42 84 9C */	lfs f2, lbl_804BFEBC-_SDA2_BASE_(r2)
/* 8002F87C 0002A77C  C0 62 84 A0 */	lfs f3, lbl_804BFEC0-_SDA2_BASE_(r2)
/* 8002F880 0002A780  EC 80 00 32 */	fmuls f4, f0, f0
/* 8002F884 0002A784  EC 00 00 B2 */	fmuls f0, f0, f2
/* 8002F888 0002A788  EC 84 18 7C */	fnmsubs f4, f4, f1, f3
/* 8002F88C 0002A78C  EC 04 00 32 */	fmuls f0, f4, f0
/* 8002F890 0002A790  FC 20 00 90 */	fmr f1, f0
/* 8002F894 0002A794  4E 80 00 20 */	blr 
