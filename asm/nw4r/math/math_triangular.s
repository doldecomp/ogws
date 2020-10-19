.include "macros.inc"

.section .data, "wa"  # 0x80393A80 - 0x803CAF00

.balign 0x8

# sSinCosTbl__Q34nw4r4math29@unnamed@math_triangular_cpp@
sSinCosTbl__Q34nw4r4math29$$2unnamed$$2math_triangular_cpp$$2:
	.incbin "baserom.dol", 0x390BE0, 0x1010

# sArcTanTbl__Q34nw4r4math29@unnamed@math_triangular_cpp@
sArcTanTbl__Q34nw4r4math29$$2unnamed$$2math_triangular_cpp$$2:
	.incbin "baserom.dol", 0x391BF0, 0x108

.section .sdata2, "a"  # 0x804BFA20 - 0x804C69E0

.balign 0x8

lbl_804BFEC8: .single 0e65536
lbl_804BFECC: .single 0e0
lbl_804BFED0: .single 0e1
lbl_804BFED4: .single 0e32
lbl_804BFED8: .single 0e64
lbl_804BFEDC: .single 0e-1
lbl_804BFEE0: .single 0e-64
lbl_804BFEE4: .single 0e128
lbl_804BFEE8: .single 0e-128

.section .text, "ax"  # 0x800076E0 - 0x80355080 

.global SinFIdx__Q24nw4r4mathFf
SinFIdx__Q24nw4r4mathFf:
/* 8002F898 0002A798  FC 60 0A 10 */	fabs f3, f1
/* 8002F89C 0002A79C  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8002F8A0 0002A7A0  C0 02 84 A8 */	lfs f0, lbl_804BFEC8-_SDA2_BASE_(r2)
/* 8002F8A4 0002A7A4  48 00 00 08 */	b lbl_8002F8AC
lbl_8002F8A8:
/* 8002F8A8 0002A7A8  EC 63 00 28 */	fsubs f3, f3, f0
lbl_8002F8AC:
/* 8002F8AC 0002A7AC  FC 03 00 40 */	fcmpo cr0, f3, f0
/* 8002F8B0 0002A7B0  4C 41 13 82 */	cror 2, 1, 2
/* 8002F8B4 0002A7B4  41 82 FF F4 */	beq lbl_8002F8A8
/* 8002F8B8 0002A7B8  F0 61 B0 0C */	psq_st f3, 12(r1), 1, qr3
/* 8002F8BC 0002A7BC  A0 01 00 0C */	lhz r0, 0xc(r1)
/* 8002F8C0 0002A7C0  B0 01 00 08 */	sth r0, 8(r1)
/* 8002F8C4 0002A7C4  E0 41 B0 08 */	psq_l f2, 8(r1), 1, qr3
/* 8002F8C8 0002A7C8  3C 80 80 39 */	lis r4, sSinCosTbl__Q34nw4r4math29$$2unnamed$$2math_triangular_cpp$$2@ha
/* 8002F8CC 0002A7CC  54 00 25 36 */	rlwinm r0, r0, 4, 0x14, 0x1b
/* 8002F8D0 0002A7D0  C0 02 84 AC */	lfs f0, lbl_804BFECC-_SDA2_BASE_(r2)
/* 8002F8D4 0002A7D4  38 84 4A E0 */	addi r4, r4, sSinCosTbl__Q34nw4r4math29$$2unnamed$$2math_triangular_cpp$$2@l
/* 8002F8D8 0002A7D8  EC 83 10 28 */	fsubs f4, f3, f2
/* 8002F8DC 0002A7DC  7C 64 02 14 */	add r3, r4, r0
/* 8002F8E0 0002A7E0  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8002F8E4 0002A7E4  C0 63 00 08 */	lfs f3, 8(r3)
/* 8002F8E8 0002A7E8  7C 44 04 2E */	lfsx f2, r4, r0
/* 8002F8EC 0002A7EC  EC 04 00 F2 */	fmuls f0, f4, f3
/* 8002F8F0 0002A7F0  EC 22 00 2A */	fadds f1, f2, f0
/* 8002F8F4 0002A7F4  40 80 00 08 */	bge lbl_8002F8FC
/* 8002F8F8 0002A7F8  FC 20 08 50 */	fneg f1, f1
lbl_8002F8FC:
/* 8002F8FC 0002A7FC  38 21 00 10 */	addi r1, r1, 0x10
/* 8002F900 0002A800  4E 80 00 20 */	blr 

.global CosFIdx__Q24nw4r4mathFf
CosFIdx__Q24nw4r4mathFf:
/* 8002F904 0002A804  FC 20 0A 10 */	fabs f1, f1
/* 8002F908 0002A808  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8002F90C 0002A80C  C0 02 84 A8 */	lfs f0, lbl_804BFEC8-_SDA2_BASE_(r2)
/* 8002F910 0002A810  48 00 00 08 */	b lbl_8002F918
lbl_8002F914:
/* 8002F914 0002A814  EC 21 00 28 */	fsubs f1, f1, f0
lbl_8002F918:
/* 8002F918 0002A818  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8002F91C 0002A81C  4C 41 13 82 */	cror 2, 1, 2
/* 8002F920 0002A820  41 82 FF F4 */	beq lbl_8002F914
/* 8002F924 0002A824  F0 21 B0 0C */	psq_st f1, 12(r1), 1, qr3
/* 8002F928 0002A828  A0 01 00 0C */	lhz r0, 0xc(r1)
/* 8002F92C 0002A82C  B0 01 00 08 */	sth r0, 8(r1)
/* 8002F930 0002A830  E0 01 B0 08 */	psq_l f0, 8(r1), 1, qr3
/* 8002F934 0002A834  3C 60 80 39 */	lis r3, sSinCosTbl__Q34nw4r4math29$$2unnamed$$2math_triangular_cpp$$2@ha
/* 8002F938 0002A838  54 00 25 36 */	rlwinm r0, r0, 4, 0x14, 0x1b
/* 8002F93C 0002A83C  38 63 4A E0 */	addi r3, r3, sSinCosTbl__Q34nw4r4math29$$2unnamed$$2math_triangular_cpp$$2@l
/* 8002F940 0002A840  EC 41 00 28 */	fsubs f2, f1, f0
/* 8002F944 0002A844  7C 63 02 14 */	add r3, r3, r0
/* 8002F948 0002A848  C0 23 00 0C */	lfs f1, 0xc(r3)
/* 8002F94C 0002A84C  C0 03 00 04 */	lfs f0, 4(r3)
/* 8002F950 0002A850  EC 22 00 72 */	fmuls f1, f2, f1
/* 8002F954 0002A854  EC 20 08 2A */	fadds f1, f0, f1
/* 8002F958 0002A858  38 21 00 10 */	addi r1, r1, 0x10
/* 8002F95C 0002A85C  4E 80 00 20 */	blr 

.global SinCosFIdx__Q24nw4r4mathFPfPff
SinCosFIdx__Q24nw4r4mathFPfPff:
/* 8002F960 0002A860  FC 60 0A 10 */	fabs f3, f1
/* 8002F964 0002A864  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8002F968 0002A868  C0 02 84 A8 */	lfs f0, lbl_804BFEC8-_SDA2_BASE_(r2)
/* 8002F96C 0002A86C  48 00 00 08 */	b lbl_8002F974
lbl_8002F970:
/* 8002F970 0002A870  EC 63 00 28 */	fsubs f3, f3, f0
lbl_8002F974:
/* 8002F974 0002A874  FC 03 00 40 */	fcmpo cr0, f3, f0
/* 8002F978 0002A878  4C 41 13 82 */	cror 2, 1, 2
/* 8002F97C 0002A87C  41 82 FF F4 */	beq lbl_8002F970
/* 8002F980 0002A880  F0 61 B0 0C */	psq_st f3, 12(r1), 1, qr3
/* 8002F984 0002A884  A0 01 00 0C */	lhz r0, 0xc(r1)
/* 8002F988 0002A888  B0 01 00 08 */	sth r0, 8(r1)
/* 8002F98C 0002A88C  E0 41 B0 08 */	psq_l f2, 8(r1), 1, qr3
/* 8002F990 0002A890  3C C0 80 39 */	lis r6, sSinCosTbl__Q34nw4r4math29$$2unnamed$$2math_triangular_cpp$$2@ha
/* 8002F994 0002A894  C0 02 84 AC */	lfs f0, lbl_804BFECC-_SDA2_BASE_(r2)
/* 8002F998 0002A898  54 00 25 36 */	rlwinm r0, r0, 4, 0x14, 0x1b
/* 8002F99C 0002A89C  38 C6 4A E0 */	addi r6, r6, sSinCosTbl__Q34nw4r4math29$$2unnamed$$2math_triangular_cpp$$2@l
/* 8002F9A0 0002A8A0  EC 83 10 28 */	fsubs f4, f3, f2
/* 8002F9A4 0002A8A4  7C A6 02 14 */	add r5, r6, r0
/* 8002F9A8 0002A8A8  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8002F9AC 0002A8AC  C0 65 00 08 */	lfs f3, 8(r5)
/* 8002F9B0 0002A8B0  C0 25 00 0C */	lfs f1, 0xc(r5)
/* 8002F9B4 0002A8B4  EC 64 00 F2 */	fmuls f3, f4, f3
/* 8002F9B8 0002A8B8  7C 46 04 2E */	lfsx f2, r6, r0
/* 8002F9BC 0002A8BC  EC 24 00 72 */	fmuls f1, f4, f1
/* 8002F9C0 0002A8C0  C0 05 00 04 */	lfs f0, 4(r5)
/* 8002F9C4 0002A8C4  EC 42 18 2A */	fadds f2, f2, f3
/* 8002F9C8 0002A8C8  EC 00 08 2A */	fadds f0, f0, f1
/* 8002F9CC 0002A8CC  40 80 00 08 */	bge lbl_8002F9D4
/* 8002F9D0 0002A8D0  FC 40 10 50 */	fneg f2, f2
lbl_8002F9D4:
/* 8002F9D4 0002A8D4  D0 43 00 00 */	stfs f2, 0(r3)
/* 8002F9D8 0002A8D8  D0 04 00 00 */	stfs f0, 0(r4)
/* 8002F9DC 0002A8DC  38 21 00 10 */	addi r1, r1, 0x10
/* 8002F9E0 0002A8E0  4E 80 00 20 */	blr 

.global AtanFIdx__Q24nw4r4mathFf
AtanFIdx__Q24nw4r4mathFf:
/* 8002F9E4 0002A8E4  C0 02 84 AC */	lfs f0, lbl_804BFECC-_SDA2_BASE_(r2)
/* 8002F9E8 0002A8E8  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8002F9EC 0002A8EC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8002F9F0 0002A8F0  4C 41 13 82 */	cror 2, 1, 2
/* 8002F9F4 0002A8F4  40 82 00 9C */	bne lbl_8002FA90
/* 8002F9F8 0002A8F8  C0 02 84 B0 */	lfs f0, lbl_804BFED0-_SDA2_BASE_(r2)
/* 8002F9FC 0002A8FC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8002FA00 0002A900  40 81 00 50 */	ble lbl_8002FA50
/* 8002FA04 0002A904  EC 20 08 24 */	fdivs f1, f0, f1
/* 8002FA08 0002A908  C0 02 84 B4 */	lfs f0, lbl_804BFED4-_SDA2_BASE_(r2)
/* 8002FA0C 0002A90C  EC 21 00 32 */	fmuls f1, f1, f0
/* 8002FA10 0002A910  F0 21 B0 1C */	psq_st f1, 28(r1), 1, qr3
/* 8002FA14 0002A914  A0 01 00 1C */	lhz r0, 0x1c(r1)
/* 8002FA18 0002A918  B0 01 00 0E */	sth r0, 0xe(r1)
/* 8002FA1C 0002A91C  E0 41 B0 0E */	psq_l f2, 14(r1), 1, qr3
/* 8002FA20 0002A920  3C 80 80 39 */	lis r4, sArcTanTbl__Q34nw4r4math29$$2unnamed$$2math_triangular_cpp$$2@ha
/* 8002FA24 0002A924  54 00 18 38 */	slwi r0, r0, 3
/* 8002FA28 0002A928  C0 02 84 B8 */	lfs f0, lbl_804BFED8-_SDA2_BASE_(r2)
/* 8002FA2C 0002A92C  38 84 5A F0 */	addi r4, r4, sArcTanTbl__Q34nw4r4math29$$2unnamed$$2math_triangular_cpp$$2@l
/* 8002FA30 0002A930  EC 61 10 28 */	fsubs f3, f1, f2
/* 8002FA34 0002A934  7C 64 02 14 */	add r3, r4, r0
/* 8002FA38 0002A938  7C 24 04 2E */	lfsx f1, r4, r0
/* 8002FA3C 0002A93C  C0 43 00 04 */	lfs f2, 4(r3)
/* 8002FA40 0002A940  EC 43 00 B2 */	fmuls f2, f3, f2
/* 8002FA44 0002A944  EC 21 10 2A */	fadds f1, f1, f2
/* 8002FA48 0002A948  EC 20 08 28 */	fsubs f1, f0, f1
/* 8002FA4C 0002A94C  48 00 00 E0 */	b lbl_8002FB2C
lbl_8002FA50:
/* 8002FA50 0002A950  C0 02 84 B4 */	lfs f0, lbl_804BFED4-_SDA2_BASE_(r2)
/* 8002FA54 0002A954  EC 01 00 32 */	fmuls f0, f1, f0
/* 8002FA58 0002A958  F0 01 B0 18 */	psq_st f0, 24(r1), 1, qr3
/* 8002FA5C 0002A95C  A0 01 00 18 */	lhz r0, 0x18(r1)
/* 8002FA60 0002A960  B0 01 00 0C */	sth r0, 0xc(r1)
/* 8002FA64 0002A964  E0 21 B0 0C */	psq_l f1, 12(r1), 1, qr3
/* 8002FA68 0002A968  3C 80 80 39 */	lis r4, sArcTanTbl__Q34nw4r4math29$$2unnamed$$2math_triangular_cpp$$2@ha
/* 8002FA6C 0002A96C  54 00 18 38 */	slwi r0, r0, 3
/* 8002FA70 0002A970  38 84 5A F0 */	addi r4, r4, sArcTanTbl__Q34nw4r4math29$$2unnamed$$2math_triangular_cpp$$2@l
/* 8002FA74 0002A974  EC 40 08 28 */	fsubs f2, f0, f1
/* 8002FA78 0002A978  7C 64 02 14 */	add r3, r4, r0
/* 8002FA7C 0002A97C  7C 04 04 2E */	lfsx f0, r4, r0
/* 8002FA80 0002A980  C0 23 00 04 */	lfs f1, 4(r3)
/* 8002FA84 0002A984  EC 22 00 72 */	fmuls f1, f2, f1
/* 8002FA88 0002A988  EC 20 08 2A */	fadds f1, f0, f1
/* 8002FA8C 0002A98C  48 00 00 A0 */	b lbl_8002FB2C
lbl_8002FA90:
/* 8002FA90 0002A990  C0 02 84 BC */	lfs f0, lbl_804BFEDC-_SDA2_BASE_(r2)
/* 8002FA94 0002A994  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8002FA98 0002A998  40 80 00 50 */	bge lbl_8002FAE8
/* 8002FA9C 0002A99C  EC 20 08 24 */	fdivs f1, f0, f1
/* 8002FAA0 0002A9A0  C0 02 84 B4 */	lfs f0, lbl_804BFED4-_SDA2_BASE_(r2)
/* 8002FAA4 0002A9A4  EC 21 00 32 */	fmuls f1, f1, f0
/* 8002FAA8 0002A9A8  F0 21 B0 14 */	psq_st f1, 20(r1), 1, qr3
/* 8002FAAC 0002A9AC  A0 01 00 14 */	lhz r0, 0x14(r1)
/* 8002FAB0 0002A9B0  B0 01 00 0A */	sth r0, 0xa(r1)
/* 8002FAB4 0002A9B4  E0 41 B0 0A */	psq_l f2, 10(r1), 1, qr3
/* 8002FAB8 0002A9B8  3C 80 80 39 */	lis r4, sArcTanTbl__Q34nw4r4math29$$2unnamed$$2math_triangular_cpp$$2@ha
/* 8002FABC 0002A9BC  54 00 18 38 */	slwi r0, r0, 3
/* 8002FAC0 0002A9C0  C0 02 84 C0 */	lfs f0, lbl_804BFEE0-_SDA2_BASE_(r2)
/* 8002FAC4 0002A9C4  38 84 5A F0 */	addi r4, r4, sArcTanTbl__Q34nw4r4math29$$2unnamed$$2math_triangular_cpp$$2@l
/* 8002FAC8 0002A9C8  EC 61 10 28 */	fsubs f3, f1, f2
/* 8002FACC 0002A9CC  7C 64 02 14 */	add r3, r4, r0
/* 8002FAD0 0002A9D0  7C 24 04 2E */	lfsx f1, r4, r0
/* 8002FAD4 0002A9D4  C0 43 00 04 */	lfs f2, 4(r3)
/* 8002FAD8 0002A9D8  EC 43 00 B2 */	fmuls f2, f3, f2
/* 8002FADC 0002A9DC  EC 21 10 2A */	fadds f1, f1, f2
/* 8002FAE0 0002A9E0  EC 20 08 2A */	fadds f1, f0, f1
/* 8002FAE4 0002A9E4  48 00 00 48 */	b lbl_8002FB2C
lbl_8002FAE8:
/* 8002FAE8 0002A9E8  FC 20 08 50 */	fneg f1, f1
/* 8002FAEC 0002A9EC  C0 02 84 B4 */	lfs f0, lbl_804BFED4-_SDA2_BASE_(r2)
/* 8002FAF0 0002A9F0  EC 21 00 32 */	fmuls f1, f1, f0
/* 8002FAF4 0002A9F4  F0 21 B0 10 */	psq_st f1, 16(r1), 1, qr3
/* 8002FAF8 0002A9F8  A0 01 00 10 */	lhz r0, 0x10(r1)
/* 8002FAFC 0002A9FC  B0 01 00 08 */	sth r0, 8(r1)
/* 8002FB00 0002AA00  E0 01 B0 08 */	psq_l f0, 8(r1), 1, qr3
/* 8002FB04 0002AA04  3C 80 80 39 */	lis r4, sArcTanTbl__Q34nw4r4math29$$2unnamed$$2math_triangular_cpp$$2@ha
/* 8002FB08 0002AA08  54 00 18 38 */	slwi r0, r0, 3
/* 8002FB0C 0002AA0C  38 84 5A F0 */	addi r4, r4, sArcTanTbl__Q34nw4r4math29$$2unnamed$$2math_triangular_cpp$$2@l
/* 8002FB10 0002AA10  EC 41 00 28 */	fsubs f2, f1, f0
/* 8002FB14 0002AA14  7C 64 02 14 */	add r3, r4, r0
/* 8002FB18 0002AA18  7C 04 04 2E */	lfsx f0, r4, r0
/* 8002FB1C 0002AA1C  C0 23 00 04 */	lfs f1, 4(r3)
/* 8002FB20 0002AA20  EC 22 00 72 */	fmuls f1, f2, f1
/* 8002FB24 0002AA24  EC 00 08 2A */	fadds f0, f0, f1
/* 8002FB28 0002AA28  FC 20 00 50 */	fneg f1, f0
lbl_8002FB2C:
/* 8002FB2C 0002AA2C  38 21 00 20 */	addi r1, r1, 0x20
/* 8002FB30 0002AA30  4E 80 00 20 */	blr 

.global Atan2FIdx__Q24nw4r4mathFff
Atan2FIdx__Q24nw4r4mathFff:
/* 8002FB34 0002AA34  C0 02 84 AC */	lfs f0, lbl_804BFECC-_SDA2_BASE_(r2)
/* 8002FB38 0002AA38  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8002FB3C 0002AA3C  FC 00 10 00 */	fcmpu cr0, f0, f2
/* 8002FB40 0002AA40  40 82 00 14 */	bne lbl_8002FB54
/* 8002FB44 0002AA44  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 8002FB48 0002AA48  40 82 00 0C */	bne lbl_8002FB54
/* 8002FB4C 0002AA4C  FC 20 00 90 */	fmr f1, f0
/* 8002FB50 0002AA50  48 00 01 84 */	b lbl_8002FCD4
lbl_8002FB54:
/* 8002FB54 0002AA54  C0 82 84 AC */	lfs f4, lbl_804BFECC-_SDA2_BASE_(r2)
/* 8002FB58 0002AA58  FC 02 20 40 */	fcmpo cr0, f2, f4
/* 8002FB5C 0002AA5C  4C 41 13 82 */	cror 2, 1, 2
/* 8002FB60 0002AA60  40 82 00 6C */	bne lbl_8002FBCC
/* 8002FB64 0002AA64  FC 01 20 40 */	fcmpo cr0, f1, f4
/* 8002FB68 0002AA68  4C 41 13 82 */	cror 2, 1, 2
/* 8002FB6C 0002AA6C  40 82 00 30 */	bne lbl_8002FB9C
/* 8002FB70 0002AA70  FC 02 08 40 */	fcmpo cr0, f2, f1
/* 8002FB74 0002AA74  4C 41 13 82 */	cror 2, 1, 2
/* 8002FB78 0002AA78  40 82 00 10 */	bne lbl_8002FB88
/* 8002FB7C 0002AA7C  FC 60 10 90 */	fmr f3, f2
/* 8002FB80 0002AA80  38 00 00 00 */	li r0, 0
/* 8002FB84 0002AA84  48 00 00 BC */	b lbl_8002FC40
lbl_8002FB88:
/* 8002FB88 0002AA88  FC 60 08 90 */	fmr f3, f1
/* 8002FB8C 0002AA8C  C0 82 84 B8 */	lfs f4, lbl_804BFED8-_SDA2_BASE_(r2)
/* 8002FB90 0002AA90  FC 20 10 90 */	fmr f1, f2
/* 8002FB94 0002AA94  38 00 00 01 */	li r0, 1
/* 8002FB98 0002AA98  48 00 00 A8 */	b lbl_8002FC40
lbl_8002FB9C:
/* 8002FB9C 0002AA9C  FC 20 08 50 */	fneg f1, f1
/* 8002FBA0 0002AAA0  FC 02 08 40 */	fcmpo cr0, f2, f1
/* 8002FBA4 0002AAA4  4C 41 13 82 */	cror 2, 1, 2
/* 8002FBA8 0002AAA8  40 82 00 10 */	bne lbl_8002FBB8
/* 8002FBAC 0002AAAC  FC 60 10 90 */	fmr f3, f2
/* 8002FBB0 0002AAB0  38 00 00 01 */	li r0, 1
/* 8002FBB4 0002AAB4  48 00 00 8C */	b lbl_8002FC40
lbl_8002FBB8:
/* 8002FBB8 0002AAB8  FC 60 08 90 */	fmr f3, f1
/* 8002FBBC 0002AABC  C0 82 84 C0 */	lfs f4, lbl_804BFEE0-_SDA2_BASE_(r2)
/* 8002FBC0 0002AAC0  FC 20 10 90 */	fmr f1, f2
/* 8002FBC4 0002AAC4  38 00 00 00 */	li r0, 0
/* 8002FBC8 0002AAC8  48 00 00 78 */	b lbl_8002FC40
lbl_8002FBCC:
/* 8002FBCC 0002AACC  FC 01 20 40 */	fcmpo cr0, f1, f4
/* 8002FBD0 0002AAD0  4C 41 13 82 */	cror 2, 1, 2
/* 8002FBD4 0002AAD4  40 82 00 38 */	bne lbl_8002FC0C
/* 8002FBD8 0002AAD8  FC 00 10 50 */	fneg f0, f2
/* 8002FBDC 0002AADC  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 8002FBE0 0002AAE0  4C 41 13 82 */	cror 2, 1, 2
/* 8002FBE4 0002AAE4  40 82 00 14 */	bne lbl_8002FBF8
/* 8002FBE8 0002AAE8  FC 60 00 90 */	fmr f3, f0
/* 8002FBEC 0002AAEC  C0 82 84 C4 */	lfs f4, lbl_804BFEE4-_SDA2_BASE_(r2)
/* 8002FBF0 0002AAF0  38 00 00 01 */	li r0, 1
/* 8002FBF4 0002AAF4  48 00 00 4C */	b lbl_8002FC40
lbl_8002FBF8:
/* 8002FBF8 0002AAF8  FC 60 08 90 */	fmr f3, f1
/* 8002FBFC 0002AAFC  C0 82 84 B8 */	lfs f4, lbl_804BFED8-_SDA2_BASE_(r2)
/* 8002FC00 0002AB00  FC 20 00 90 */	fmr f1, f0
/* 8002FC04 0002AB04  38 00 00 00 */	li r0, 0
/* 8002FC08 0002AB08  48 00 00 38 */	b lbl_8002FC40
lbl_8002FC0C:
/* 8002FC0C 0002AB0C  FC 00 10 50 */	fneg f0, f2
/* 8002FC10 0002AB10  FC 20 08 50 */	fneg f1, f1
/* 8002FC14 0002AB14  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 8002FC18 0002AB18  4C 41 13 82 */	cror 2, 1, 2
/* 8002FC1C 0002AB1C  40 82 00 14 */	bne lbl_8002FC30
/* 8002FC20 0002AB20  FC 60 00 90 */	fmr f3, f0
/* 8002FC24 0002AB24  C0 82 84 C8 */	lfs f4, lbl_804BFEE8-_SDA2_BASE_(r2)
/* 8002FC28 0002AB28  38 00 00 00 */	li r0, 0
/* 8002FC2C 0002AB2C  48 00 00 14 */	b lbl_8002FC40
lbl_8002FC30:
/* 8002FC30 0002AB30  FC 60 08 90 */	fmr f3, f1
/* 8002FC34 0002AB34  C0 82 84 C0 */	lfs f4, lbl_804BFEE0-_SDA2_BASE_(r2)
/* 8002FC38 0002AB38  FC 20 00 90 */	fmr f1, f0
/* 8002FC3C 0002AB3C  38 00 00 01 */	li r0, 1
lbl_8002FC40:
/* 8002FC40 0002AB40  2C 00 00 00 */	cmpwi r0, 0
/* 8002FC44 0002AB44  41 82 00 4C */	beq lbl_8002FC90
/* 8002FC48 0002AB48  EC 21 18 24 */	fdivs f1, f1, f3
/* 8002FC4C 0002AB4C  C0 02 84 B4 */	lfs f0, lbl_804BFED4-_SDA2_BASE_(r2)
/* 8002FC50 0002AB50  EC 21 00 32 */	fmuls f1, f1, f0
/* 8002FC54 0002AB54  F0 21 B0 10 */	psq_st f1, 16(r1), 1, qr3
/* 8002FC58 0002AB58  A0 01 00 10 */	lhz r0, 0x10(r1)
/* 8002FC5C 0002AB5C  B0 01 00 0A */	sth r0, 0xa(r1)
/* 8002FC60 0002AB60  E0 01 B0 0A */	psq_l f0, 10(r1), 1, qr3
/* 8002FC64 0002AB64  3C 80 80 39 */	lis r4, sArcTanTbl__Q34nw4r4math29$$2unnamed$$2math_triangular_cpp$$2@ha
/* 8002FC68 0002AB68  54 00 18 38 */	slwi r0, r0, 3
/* 8002FC6C 0002AB6C  38 84 5A F0 */	addi r4, r4, sArcTanTbl__Q34nw4r4math29$$2unnamed$$2math_triangular_cpp$$2@l
/* 8002FC70 0002AB70  EC 41 00 28 */	fsubs f2, f1, f0
/* 8002FC74 0002AB74  7C 64 02 14 */	add r3, r4, r0
/* 8002FC78 0002AB78  7C 04 04 2E */	lfsx f0, r4, r0
/* 8002FC7C 0002AB7C  C0 23 00 04 */	lfs f1, 4(r3)
/* 8002FC80 0002AB80  EC 22 00 72 */	fmuls f1, f2, f1
/* 8002FC84 0002AB84  EC 00 08 2A */	fadds f0, f0, f1
/* 8002FC88 0002AB88  EC 24 00 28 */	fsubs f1, f4, f0
/* 8002FC8C 0002AB8C  48 00 00 48 */	b lbl_8002FCD4
lbl_8002FC90:
/* 8002FC90 0002AB90  EC 21 18 24 */	fdivs f1, f1, f3
/* 8002FC94 0002AB94  C0 02 84 B4 */	lfs f0, lbl_804BFED4-_SDA2_BASE_(r2)
/* 8002FC98 0002AB98  EC 21 00 32 */	fmuls f1, f1, f0
/* 8002FC9C 0002AB9C  F0 21 B0 0C */	psq_st f1, 12(r1), 1, qr3
/* 8002FCA0 0002ABA0  A0 01 00 0C */	lhz r0, 0xc(r1)
/* 8002FCA4 0002ABA4  B0 01 00 08 */	sth r0, 8(r1)
/* 8002FCA8 0002ABA8  E0 01 B0 08 */	psq_l f0, 8(r1), 1, qr3
/* 8002FCAC 0002ABAC  3C 80 80 39 */	lis r4, sArcTanTbl__Q34nw4r4math29$$2unnamed$$2math_triangular_cpp$$2@ha
/* 8002FCB0 0002ABB0  54 00 18 38 */	slwi r0, r0, 3
/* 8002FCB4 0002ABB4  38 84 5A F0 */	addi r4, r4, sArcTanTbl__Q34nw4r4math29$$2unnamed$$2math_triangular_cpp$$2@l
/* 8002FCB8 0002ABB8  EC 41 00 28 */	fsubs f2, f1, f0
/* 8002FCBC 0002ABBC  7C 64 02 14 */	add r3, r4, r0
/* 8002FCC0 0002ABC0  7C 04 04 2E */	lfsx f0, r4, r0
/* 8002FCC4 0002ABC4  C0 23 00 04 */	lfs f1, 4(r3)
/* 8002FCC8 0002ABC8  EC 22 00 72 */	fmuls f1, f2, f1
/* 8002FCCC 0002ABCC  EC 00 08 2A */	fadds f0, f0, f1
/* 8002FCD0 0002ABD0  EC 24 00 2A */	fadds f1, f4, f0
lbl_8002FCD4:
/* 8002FCD4 0002ABD4  38 21 00 20 */	addi r1, r1, 0x20
/* 8002FCD8 0002ABD8  4E 80 00 20 */	blr 
