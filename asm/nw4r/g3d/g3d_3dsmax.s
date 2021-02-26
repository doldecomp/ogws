.include "macros.inc"

.section .rodata, "a"
.global lbl_80378B50
lbl_80378B50:
    .long MakeTexSrtMtx_SRT__Q54nw4r3g3d6detail3dcc24$$2unnamed$$2g3d_3dsmax_cpp$$2FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt
    .long MakeTexSrtMtx_RT__Q54nw4r3g3d6detail3dcc24$$2unnamed$$2g3d_3dsmax_cpp$$2FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt
    .long MakeTexSrtMtx_ST__Q54nw4r3g3d6detail3dcc24$$2unnamed$$2g3d_3dsmax_cpp$$2FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt
    .long MakeTexSrtMtx_T__Q54nw4r3g3d6detail3dcc24$$2unnamed$$2g3d_3dsmax_cpp$$2FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt
    .long MakeTexSrtMtx_SR__Q54nw4r3g3d6detail3dcc24$$2unnamed$$2g3d_3dsmax_cpp$$2FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt
    .long MakeTexSrtMtx_R__Q54nw4r3g3d6detail3dcc24$$2unnamed$$2g3d_3dsmax_cpp$$2FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt
    .long MakeTexSrtMtx_S__Q54nw4r3g3d6detail3dcc24$$2unnamed$$2g3d_3dsmax_cpp$$2FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt
.global lbl_80378B6C
lbl_80378B6C:
    .long ProductTexSrtMtx_SRT__Q54nw4r3g3d6detail3dcc24$$2unnamed$$2g3d_3dsmax_cpp$$2FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt
    .long ProductTexSrtMtx_RT__Q54nw4r3g3d6detail3dcc24$$2unnamed$$2g3d_3dsmax_cpp$$2FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt
    .long ProductTexSrtMtx_ST__Q54nw4r3g3d6detail3dcc24$$2unnamed$$2g3d_3dsmax_cpp$$2FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt
    .long ProductTexSrtMtx_T__Q54nw4r3g3d6detail3dcc24$$2unnamed$$2g3d_3dsmax_cpp$$2FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt
    .long ProductTexSrtMtx_SR__Q54nw4r3g3d6detail3dcc24$$2unnamed$$2g3d_3dsmax_cpp$$2FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt
    .long ProductTexSrtMtx_R__Q54nw4r3g3d6detail3dcc24$$2unnamed$$2g3d_3dsmax_cpp$$2FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt
    .long ProductTexSrtMtx_S__Q54nw4r3g3d6detail3dcc24$$2unnamed$$2g3d_3dsmax_cpp$$2FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt

.section .text, "ax"
# MakeTexSrtMtx_S__Q54nw4r3g3d6detail3dcc24@unnamed@g3d_3dsmax_cpp@FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt
.global MakeTexSrtMtx_S__Q54nw4r3g3d6detail3dcc24$$2unnamed$$2g3d_3dsmax_cpp$$2FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt
MakeTexSrtMtx_S__Q54nw4r3g3d6detail3dcc24$$2unnamed$$2g3d_3dsmax_cpp$$2FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt:
/* 8006EFD8 00069ED8  C0 A4 00 00 */	lfs f5, 0(r4)
/* 8006EFDC 00069EDC  C0 02 89 E0 */	lfs f0, lbl_804C0400-_SDA2_BASE_(r2)
/* 8006EFE0 00069EE0  C0 24 00 04 */	lfs f1, 4(r4)
/* 8006EFE4 00069EE4  EC 40 28 28 */	fsubs f2, f0, f5
/* 8006EFE8 00069EE8  C0 62 89 DC */	lfs f3, lbl_804C03FC-_SDA2_BASE_(r2)
/* 8006EFEC 00069EEC  EC 00 08 28 */	fsubs f0, f0, f1
/* 8006EFF0 00069EF0  C0 82 89 D8 */	lfs f4, lbl_804C03F8-_SDA2_BASE_(r2)
/* 8006EFF4 00069EF4  D0 A3 00 00 */	stfs f5, 0(r3)
/* 8006EFF8 00069EF8  EC 43 00 B2 */	fmuls f2, f3, f2
/* 8006EFFC 00069EFC  EC 03 00 32 */	fmuls f0, f3, f0
/* 8006F000 00069F00  D0 83 00 04 */	stfs f4, 4(r3)
/* 8006F004 00069F04  D0 83 00 08 */	stfs f4, 8(r3)
/* 8006F008 00069F08  D0 43 00 0C */	stfs f2, 0xc(r3)
/* 8006F00C 00069F0C  D0 83 00 10 */	stfs f4, 0x10(r3)
/* 8006F010 00069F10  D0 23 00 14 */	stfs f1, 0x14(r3)
/* 8006F014 00069F14  D0 83 00 18 */	stfs f4, 0x18(r3)
/* 8006F018 00069F18  D0 03 00 1C */	stfs f0, 0x1c(r3)
/* 8006F01C 00069F1C  4E 80 00 20 */	blr 

# MakeTexSrtMtx_R__Q54nw4r3g3d6detail3dcc24@unnamed@g3d_3dsmax_cpp@FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt
.global MakeTexSrtMtx_R__Q54nw4r3g3d6detail3dcc24$$2unnamed$$2g3d_3dsmax_cpp$$2FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt
MakeTexSrtMtx_R__Q54nw4r3g3d6detail3dcc24$$2unnamed$$2g3d_3dsmax_cpp$$2FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt:
/* 8006F020 00069F20  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8006F024 00069F24  7C 08 02 A6 */	mflr r0
/* 8006F028 00069F28  C0 24 00 08 */	lfs f1, 8(r4)
/* 8006F02C 00069F2C  C0 02 89 E4 */	lfs f0, lbl_804C0404-_SDA2_BASE_(r2)
/* 8006F030 00069F30  38 81 00 08 */	addi r4, r1, 8
/* 8006F034 00069F34  90 01 00 24 */	stw r0, 0x24(r1)
/* 8006F038 00069F38  EC 20 00 72 */	fmuls f1, f0, f1
/* 8006F03C 00069F3C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8006F040 00069F40  7C 7F 1B 78 */	mr r31, r3
/* 8006F044 00069F44  38 61 00 0C */	addi r3, r1, 0xc
/* 8006F048 00069F48  4B FC 09 19 */	bl SinCosFIdx__Q24nw4r4mathFPfPff
/* 8006F04C 00069F4C  C0 01 00 08 */	lfs f0, 8(r1)
/* 8006F050 00069F50  C0 82 89 D8 */	lfs f4, lbl_804C03F8-_SDA2_BASE_(r2)
/* 8006F054 00069F54  D0 1F 00 00 */	stfs f0, 0(r31)
/* 8006F058 00069F58  C0 62 89 E0 */	lfs f3, lbl_804C0400-_SDA2_BASE_(r2)
/* 8006F05C 00069F5C  C0 01 00 0C */	lfs f0, 0xc(r1)
/* 8006F060 00069F60  C0 42 89 E8 */	lfs f2, lbl_804C0408-_SDA2_BASE_(r2)
/* 8006F064 00069F64  D0 1F 00 04 */	stfs f0, 4(r31)
/* 8006F068 00069F68  D0 9F 00 08 */	stfs f4, 8(r31)
/* 8006F06C 00069F6C  C0 21 00 08 */	lfs f1, 8(r1)
/* 8006F070 00069F70  C0 01 00 0C */	lfs f0, 0xc(r1)
/* 8006F074 00069F74  EC 01 00 2A */	fadds f0, f1, f0
/* 8006F078 00069F78  EC 00 18 28 */	fsubs f0, f0, f3
/* 8006F07C 00069F7C  EC 02 00 32 */	fmuls f0, f2, f0
/* 8006F080 00069F80  D0 1F 00 0C */	stfs f0, 0xc(r31)
/* 8006F084 00069F84  C0 01 00 0C */	lfs f0, 0xc(r1)
/* 8006F088 00069F88  FC 00 00 50 */	fneg f0, f0
/* 8006F08C 00069F8C  D0 1F 00 10 */	stfs f0, 0x10(r31)
/* 8006F090 00069F90  C0 01 00 08 */	lfs f0, 8(r1)
/* 8006F094 00069F94  D0 1F 00 14 */	stfs f0, 0x14(r31)
/* 8006F098 00069F98  D0 9F 00 18 */	stfs f4, 0x18(r31)
/* 8006F09C 00069F9C  C0 21 00 0C */	lfs f1, 0xc(r1)
/* 8006F0A0 00069FA0  C0 01 00 08 */	lfs f0, 8(r1)
/* 8006F0A4 00069FA4  FC 20 08 50 */	fneg f1, f1
/* 8006F0A8 00069FA8  EC 01 00 2A */	fadds f0, f1, f0
/* 8006F0AC 00069FAC  EC 00 18 28 */	fsubs f0, f0, f3
/* 8006F0B0 00069FB0  EC 02 00 32 */	fmuls f0, f2, f0
/* 8006F0B4 00069FB4  D0 1F 00 1C */	stfs f0, 0x1c(r31)
/* 8006F0B8 00069FB8  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8006F0BC 00069FBC  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8006F0C0 00069FC0  7C 08 03 A6 */	mtlr r0
/* 8006F0C4 00069FC4  38 21 00 20 */	addi r1, r1, 0x20
/* 8006F0C8 00069FC8  4E 80 00 20 */	blr 

# MakeTexSrtMtx_T__Q54nw4r3g3d6detail3dcc24@unnamed@g3d_3dsmax_cpp@FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt
.global MakeTexSrtMtx_T__Q54nw4r3g3d6detail3dcc24$$2unnamed$$2g3d_3dsmax_cpp$$2FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt
MakeTexSrtMtx_T__Q54nw4r3g3d6detail3dcc24$$2unnamed$$2g3d_3dsmax_cpp$$2FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt:
/* 8006F0CC 00069FCC  C0 04 00 0C */	lfs f0, 0xc(r4)
/* 8006F0D0 00069FD0  C0 42 89 D8 */	lfs f2, lbl_804C03F8-_SDA2_BASE_(r2)
/* 8006F0D4 00069FD4  FC 20 00 50 */	fneg f1, f0
/* 8006F0D8 00069FD8  C0 62 89 E0 */	lfs f3, lbl_804C0400-_SDA2_BASE_(r2)
/* 8006F0DC 00069FDC  C0 04 00 10 */	lfs f0, 0x10(r4)
/* 8006F0E0 00069FE0  D0 63 00 00 */	stfs f3, 0(r3)
/* 8006F0E4 00069FE4  D0 43 00 04 */	stfs f2, 4(r3)
/* 8006F0E8 00069FE8  D0 43 00 08 */	stfs f2, 8(r3)
/* 8006F0EC 00069FEC  D0 23 00 0C */	stfs f1, 0xc(r3)
/* 8006F0F0 00069FF0  D0 43 00 10 */	stfs f2, 0x10(r3)
/* 8006F0F4 00069FF4  D0 63 00 14 */	stfs f3, 0x14(r3)
/* 8006F0F8 00069FF8  D0 43 00 18 */	stfs f2, 0x18(r3)
/* 8006F0FC 00069FFC  D0 03 00 1C */	stfs f0, 0x1c(r3)
/* 8006F100 0006A000  4E 80 00 20 */	blr 

# MakeTexSrtMtx_SR__Q54nw4r3g3d6detail3dcc24@unnamed@g3d_3dsmax_cpp@FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt
.global MakeTexSrtMtx_SR__Q54nw4r3g3d6detail3dcc24$$2unnamed$$2g3d_3dsmax_cpp$$2FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt
MakeTexSrtMtx_SR__Q54nw4r3g3d6detail3dcc24$$2unnamed$$2g3d_3dsmax_cpp$$2FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt:
/* 8006F104 0006A004  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8006F108 0006A008  7C 08 02 A6 */	mflr r0
/* 8006F10C 0006A00C  C0 24 00 08 */	lfs f1, 8(r4)
/* 8006F110 0006A010  90 01 00 24 */	stw r0, 0x24(r1)
/* 8006F114 0006A014  C0 02 89 E4 */	lfs f0, lbl_804C0404-_SDA2_BASE_(r2)
/* 8006F118 0006A018  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8006F11C 0006A01C  7C 9F 23 78 */	mr r31, r4
/* 8006F120 0006A020  EC 20 00 72 */	fmuls f1, f0, f1
/* 8006F124 0006A024  38 81 00 08 */	addi r4, r1, 8
/* 8006F128 0006A028  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8006F12C 0006A02C  7C 7E 1B 78 */	mr r30, r3
/* 8006F130 0006A030  38 61 00 0C */	addi r3, r1, 0xc
/* 8006F134 0006A034  4B FC 08 2D */	bl SinCosFIdx__Q24nw4r4mathFPfPff
/* 8006F138 0006A038  C0 21 00 0C */	lfs f1, 0xc(r1)
/* 8006F13C 0006A03C  C0 1F 00 04 */	lfs f0, 4(r31)
/* 8006F140 0006A040  C0 7F 00 00 */	lfs f3, 0(r31)
/* 8006F144 0006A044  C0 41 00 08 */	lfs f2, 8(r1)
/* 8006F148 0006A048  ED 20 00 72 */	fmuls f9, f0, f1
/* 8006F14C 0006A04C  EC E3 00 72 */	fmuls f7, f3, f1
/* 8006F150 0006A050  C0 A2 89 D8 */	lfs f5, lbl_804C03F8-_SDA2_BASE_(r2)
/* 8006F154 0006A054  EC C3 00 B2 */	fmuls f6, f3, f2
/* 8006F158 0006A058  C0 82 89 E0 */	lfs f4, lbl_804C0400-_SDA2_BASE_(r2)
/* 8006F15C 0006A05C  ED 00 00 B2 */	fmuls f8, f0, f2
/* 8006F160 0006A060  FC 20 48 50 */	fneg f1, f9
/* 8006F164 0006A064  EC 46 38 2A */	fadds f2, f6, f7
/* 8006F168 0006A068  C0 62 89 E8 */	lfs f3, lbl_804C0408-_SDA2_BASE_(r2)
/* 8006F16C 0006A06C  D0 DE 00 00 */	stfs f6, 0(r30)
/* 8006F170 0006A070  EC 01 40 2A */	fadds f0, f1, f8
/* 8006F174 0006A074  EC 42 20 28 */	fsubs f2, f2, f4
/* 8006F178 0006A078  D0 FE 00 04 */	stfs f7, 4(r30)
/* 8006F17C 0006A07C  EC 00 20 28 */	fsubs f0, f0, f4
/* 8006F180 0006A080  D0 BE 00 08 */	stfs f5, 8(r30)
/* 8006F184 0006A084  EC 43 00 B2 */	fmuls f2, f3, f2
/* 8006F188 0006A088  D0 3E 00 10 */	stfs f1, 0x10(r30)
/* 8006F18C 0006A08C  EC 03 00 32 */	fmuls f0, f3, f0
/* 8006F190 0006A090  D0 5E 00 0C */	stfs f2, 0xc(r30)
/* 8006F194 0006A094  D1 1E 00 14 */	stfs f8, 0x14(r30)
/* 8006F198 0006A098  D0 BE 00 18 */	stfs f5, 0x18(r30)
/* 8006F19C 0006A09C  D0 1E 00 1C */	stfs f0, 0x1c(r30)
/* 8006F1A0 0006A0A0  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8006F1A4 0006A0A4  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8006F1A8 0006A0A8  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8006F1AC 0006A0AC  7C 08 03 A6 */	mtlr r0
/* 8006F1B0 0006A0B0  38 21 00 20 */	addi r1, r1, 0x20
/* 8006F1B4 0006A0B4  4E 80 00 20 */	blr 

# MakeTexSrtMtx_RT__Q54nw4r3g3d6detail3dcc24@unnamed@g3d_3dsmax_cpp@FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt
.global MakeTexSrtMtx_RT__Q54nw4r3g3d6detail3dcc24$$2unnamed$$2g3d_3dsmax_cpp$$2FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt
MakeTexSrtMtx_RT__Q54nw4r3g3d6detail3dcc24$$2unnamed$$2g3d_3dsmax_cpp$$2FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt:
/* 8006F1B8 0006A0B8  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8006F1BC 0006A0BC  7C 08 02 A6 */	mflr r0
/* 8006F1C0 0006A0C0  C0 24 00 08 */	lfs f1, 8(r4)
/* 8006F1C4 0006A0C4  90 01 00 24 */	stw r0, 0x24(r1)
/* 8006F1C8 0006A0C8  C0 02 89 E4 */	lfs f0, lbl_804C0404-_SDA2_BASE_(r2)
/* 8006F1CC 0006A0CC  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8006F1D0 0006A0D0  7C 9F 23 78 */	mr r31, r4
/* 8006F1D4 0006A0D4  EC 20 00 72 */	fmuls f1, f0, f1
/* 8006F1D8 0006A0D8  38 81 00 08 */	addi r4, r1, 8
/* 8006F1DC 0006A0DC  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8006F1E0 0006A0E0  7C 7E 1B 78 */	mr r30, r3
/* 8006F1E4 0006A0E4  38 61 00 0C */	addi r3, r1, 0xc
/* 8006F1E8 0006A0E8  4B FC 07 79 */	bl SinCosFIdx__Q24nw4r4mathFPfPff
/* 8006F1EC 0006A0EC  C0 01 00 08 */	lfs f0, 8(r1)
/* 8006F1F0 0006A0F0  C0 A2 89 D8 */	lfs f5, lbl_804C03F8-_SDA2_BASE_(r2)
/* 8006F1F4 0006A0F4  D0 1E 00 00 */	stfs f0, 0(r30)
/* 8006F1F8 0006A0F8  C0 82 89 DC */	lfs f4, lbl_804C03FC-_SDA2_BASE_(r2)
/* 8006F1FC 0006A0FC  C0 01 00 0C */	lfs f0, 0xc(r1)
/* 8006F200 0006A100  C0 3F 00 0C */	lfs f1, 0xc(r31)
/* 8006F204 0006A104  D0 1E 00 04 */	stfs f0, 4(r30)
/* 8006F208 0006A108  C0 1F 00 10 */	lfs f0, 0x10(r31)
/* 8006F20C 0006A10C  EC 64 08 2A */	fadds f3, f4, f1
/* 8006F210 0006A110  D0 BE 00 08 */	stfs f5, 8(r30)
/* 8006F214 0006A114  EC 40 20 28 */	fsubs f2, f0, f4
/* 8006F218 0006A118  C0 21 00 08 */	lfs f1, 8(r1)
/* 8006F21C 0006A11C  C0 01 00 0C */	lfs f0, 0xc(r1)
/* 8006F220 0006A120  FC 20 08 50 */	fneg f1, f1
/* 8006F224 0006A124  EC 00 00 B2 */	fmuls f0, f0, f2
/* 8006F228 0006A128  EC 21 00 F2 */	fmuls f1, f1, f3
/* 8006F22C 0006A12C  EC 01 00 2A */	fadds f0, f1, f0
/* 8006F230 0006A130  EC 04 00 2A */	fadds f0, f4, f0
/* 8006F234 0006A134  D0 1E 00 0C */	stfs f0, 0xc(r30)
/* 8006F238 0006A138  C0 01 00 0C */	lfs f0, 0xc(r1)
/* 8006F23C 0006A13C  FC 00 00 50 */	fneg f0, f0
/* 8006F240 0006A140  D0 1E 00 10 */	stfs f0, 0x10(r30)
/* 8006F244 0006A144  C0 01 00 08 */	lfs f0, 8(r1)
/* 8006F248 0006A148  D0 1E 00 14 */	stfs f0, 0x14(r30)
/* 8006F24C 0006A14C  D0 BE 00 18 */	stfs f5, 0x18(r30)
/* 8006F250 0006A150  C0 21 00 0C */	lfs f1, 0xc(r1)
/* 8006F254 0006A154  C0 01 00 08 */	lfs f0, 8(r1)
/* 8006F258 0006A158  EC 21 00 F2 */	fmuls f1, f1, f3
/* 8006F25C 0006A15C  EC 00 00 B2 */	fmuls f0, f0, f2
/* 8006F260 0006A160  EC 01 00 2A */	fadds f0, f1, f0
/* 8006F264 0006A164  EC 04 00 2A */	fadds f0, f4, f0
/* 8006F268 0006A168  D0 1E 00 1C */	stfs f0, 0x1c(r30)
/* 8006F26C 0006A16C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8006F270 0006A170  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8006F274 0006A174  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8006F278 0006A178  7C 08 03 A6 */	mtlr r0
/* 8006F27C 0006A17C  38 21 00 20 */	addi r1, r1, 0x20
/* 8006F280 0006A180  4E 80 00 20 */	blr 

# MakeTexSrtMtx_ST__Q54nw4r3g3d6detail3dcc24@unnamed@g3d_3dsmax_cpp@FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt
.global MakeTexSrtMtx_ST__Q54nw4r3g3d6detail3dcc24$$2unnamed$$2g3d_3dsmax_cpp$$2FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt
MakeTexSrtMtx_ST__Q54nw4r3g3d6detail3dcc24$$2unnamed$$2g3d_3dsmax_cpp$$2FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt:
/* 8006F284 0006A184  C0 C4 00 00 */	lfs f6, 0(r4)
/* 8006F288 0006A188  C0 62 89 DC */	lfs f3, lbl_804C03FC-_SDA2_BASE_(r2)
/* 8006F28C 0006A18C  C0 24 00 0C */	lfs f1, 0xc(r4)
/* 8006F290 0006A190  FC 80 30 50 */	fneg f4, f6
/* 8006F294 0006A194  C0 04 00 10 */	lfs f0, 0x10(r4)
/* 8006F298 0006A198  EC 43 08 2A */	fadds f2, f3, f1
/* 8006F29C 0006A19C  C0 24 00 04 */	lfs f1, 4(r4)
/* 8006F2A0 0006A1A0  EC 00 18 28 */	fsubs f0, f0, f3
/* 8006F2A4 0006A1A4  C0 A2 89 D8 */	lfs f5, lbl_804C03F8-_SDA2_BASE_(r2)
/* 8006F2A8 0006A1A8  D0 C3 00 00 */	stfs f6, 0(r3)
/* 8006F2AC 0006A1AC  EC 44 00 B2 */	fmuls f2, f4, f2
/* 8006F2B0 0006A1B0  EC 01 00 32 */	fmuls f0, f1, f0
/* 8006F2B4 0006A1B4  D0 A3 00 04 */	stfs f5, 4(r3)
/* 8006F2B8 0006A1B8  EC 43 10 2A */	fadds f2, f3, f2
/* 8006F2BC 0006A1BC  D0 A3 00 08 */	stfs f5, 8(r3)
/* 8006F2C0 0006A1C0  EC 03 00 2A */	fadds f0, f3, f0
/* 8006F2C4 0006A1C4  D0 A3 00 10 */	stfs f5, 0x10(r3)
/* 8006F2C8 0006A1C8  D0 43 00 0C */	stfs f2, 0xc(r3)
/* 8006F2CC 0006A1CC  D0 23 00 14 */	stfs f1, 0x14(r3)
/* 8006F2D0 0006A1D0  D0 A3 00 18 */	stfs f5, 0x18(r3)
/* 8006F2D4 0006A1D4  D0 03 00 1C */	stfs f0, 0x1c(r3)
/* 8006F2D8 0006A1D8  4E 80 00 20 */	blr 

# MakeTexSrtMtx_SRT__Q54nw4r3g3d6detail3dcc24@unnamed@g3d_3dsmax_cpp@FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt
.global MakeTexSrtMtx_SRT__Q54nw4r3g3d6detail3dcc24$$2unnamed$$2g3d_3dsmax_cpp$$2FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt
MakeTexSrtMtx_SRT__Q54nw4r3g3d6detail3dcc24$$2unnamed$$2g3d_3dsmax_cpp$$2FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt:
/* 8006F2DC 0006A1DC  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8006F2E0 0006A1E0  7C 08 02 A6 */	mflr r0
/* 8006F2E4 0006A1E4  C0 24 00 08 */	lfs f1, 8(r4)
/* 8006F2E8 0006A1E8  90 01 00 24 */	stw r0, 0x24(r1)
/* 8006F2EC 0006A1EC  C0 02 89 E4 */	lfs f0, lbl_804C0404-_SDA2_BASE_(r2)
/* 8006F2F0 0006A1F0  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8006F2F4 0006A1F4  7C 9F 23 78 */	mr r31, r4
/* 8006F2F8 0006A1F8  EC 20 00 72 */	fmuls f1, f0, f1
/* 8006F2FC 0006A1FC  38 81 00 08 */	addi r4, r1, 8
/* 8006F300 0006A200  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8006F304 0006A204  7C 7E 1B 78 */	mr r30, r3
/* 8006F308 0006A208  38 61 00 0C */	addi r3, r1, 0xc
/* 8006F30C 0006A20C  4B FC 06 55 */	bl SinCosFIdx__Q24nw4r4mathFPfPff
/* 8006F310 0006A210  C0 3F 00 00 */	lfs f1, 0(r31)
/* 8006F314 0006A214  C0 01 00 08 */	lfs f0, 8(r1)
/* 8006F318 0006A218  C0 61 00 0C */	lfs f3, 0xc(r1)
/* 8006F31C 0006A21C  C0 5F 00 04 */	lfs f2, 4(r31)
/* 8006F320 0006A220  EC A1 00 32 */	fmuls f5, f1, f0
/* 8006F324 0006A224  EC E1 00 F2 */	fmuls f7, f1, f3
/* 8006F328 0006A228  C0 82 89 DC */	lfs f4, lbl_804C03FC-_SDA2_BASE_(r2)
/* 8006F32C 0006A22C  ED 02 00 32 */	fmuls f8, f2, f0
/* 8006F330 0006A230  C0 3F 00 0C */	lfs f1, 0xc(r31)
/* 8006F334 0006A234  ED 22 00 F2 */	fmuls f9, f2, f3
/* 8006F338 0006A238  C0 1F 00 10 */	lfs f0, 0x10(r31)
/* 8006F33C 0006A23C  EC 64 08 2A */	fadds f3, f4, f1
/* 8006F340 0006A240  D0 BE 00 00 */	stfs f5, 0(r30)
/* 8006F344 0006A244  EC 40 20 28 */	fsubs f2, f0, f4
/* 8006F348 0006A248  C0 C2 89 D8 */	lfs f6, lbl_804C03F8-_SDA2_BASE_(r2)
/* 8006F34C 0006A24C  FC A0 28 50 */	fneg f5, f5
/* 8006F350 0006A250  D0 FE 00 04 */	stfs f7, 4(r30)
/* 8006F354 0006A254  EC 29 00 F2 */	fmuls f1, f9, f3
/* 8006F358 0006A258  D0 DE 00 08 */	stfs f6, 8(r30)
/* 8006F35C 0006A25C  EC 08 00 B2 */	fmuls f0, f8, f2
/* 8006F360 0006A260  EC 65 00 F2 */	fmuls f3, f5, f3
/* 8006F364 0006A264  D1 1E 00 14 */	stfs f8, 0x14(r30)
/* 8006F368 0006A268  EC 47 00 B2 */	fmuls f2, f7, f2
/* 8006F36C 0006A26C  EC 01 00 2A */	fadds f0, f1, f0
/* 8006F370 0006A270  D0 DE 00 18 */	stfs f6, 0x18(r30)
/* 8006F374 0006A274  FC 20 48 50 */	fneg f1, f9
/* 8006F378 0006A278  EC 43 10 2A */	fadds f2, f3, f2
/* 8006F37C 0006A27C  EC 04 00 2A */	fadds f0, f4, f0
/* 8006F380 0006A280  D0 3E 00 10 */	stfs f1, 0x10(r30)
/* 8006F384 0006A284  EC 44 10 2A */	fadds f2, f4, f2
/* 8006F388 0006A288  D0 1E 00 1C */	stfs f0, 0x1c(r30)
/* 8006F38C 0006A28C  D0 5E 00 0C */	stfs f2, 0xc(r30)
/* 8006F390 0006A290  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8006F394 0006A294  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8006F398 0006A298  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8006F39C 0006A29C  7C 08 03 A6 */	mtlr r0
/* 8006F3A0 0006A2A0  38 21 00 20 */	addi r1, r1, 0x20
/* 8006F3A4 0006A2A4  4E 80 00 20 */	blr 

# ProductTexSrtMtx_S__Q54nw4r3g3d6detail3dcc24@unnamed@g3d_3dsmax_cpp@FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt
.global ProductTexSrtMtx_S__Q54nw4r3g3d6detail3dcc24$$2unnamed$$2g3d_3dsmax_cpp$$2FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt
ProductTexSrtMtx_S__Q54nw4r3g3d6detail3dcc24$$2unnamed$$2g3d_3dsmax_cpp$$2FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt:
/* 8006F3A8 0006A2A8  C0 23 00 0C */	lfs f1, 0xc(r3)
/* 8006F3AC 0006A2AC  C0 C2 89 DC */	lfs f6, lbl_804C03FC-_SDA2_BASE_(r2)
/* 8006F3B0 0006A2B0  C0 03 00 1C */	lfs f0, 0x1c(r3)
/* 8006F3B4 0006A2B4  EC 21 30 28 */	fsubs f1, f1, f6
/* 8006F3B8 0006A2B8  C1 44 00 00 */	lfs f10, 0(r4)
/* 8006F3BC 0006A2BC  C0 43 00 00 */	lfs f2, 0(r3)
/* 8006F3C0 0006A2C0  EC 00 30 28 */	fsubs f0, f0, f6
/* 8006F3C4 0006A2C4  C0 84 00 04 */	lfs f4, 4(r4)
/* 8006F3C8 0006A2C8  EC AA 00 72 */	fmuls f5, f10, f1
/* 8006F3CC 0006A2CC  ED 22 02 B2 */	fmuls f9, f2, f10
/* 8006F3D0 0006A2D0  C1 03 00 04 */	lfs f8, 4(r3)
/* 8006F3D4 0006A2D4  EC 04 00 32 */	fmuls f0, f4, f0
/* 8006F3D8 0006A2D8  C0 E3 00 08 */	lfs f7, 8(r3)
/* 8006F3DC 0006A2DC  C0 63 00 10 */	lfs f3, 0x10(r3)
/* 8006F3E0 0006A2E0  C0 43 00 14 */	lfs f2, 0x14(r3)
/* 8006F3E4 0006A2E4  C0 23 00 18 */	lfs f1, 0x18(r3)
/* 8006F3E8 0006A2E8  ED 08 02 B2 */	fmuls f8, f8, f10
/* 8006F3EC 0006A2EC  EC E7 02 B2 */	fmuls f7, f7, f10
/* 8006F3F0 0006A2F0  D1 23 00 00 */	stfs f9, 0(r3)
/* 8006F3F4 0006A2F4  EC A6 28 2A */	fadds f5, f6, f5
/* 8006F3F8 0006A2F8  EC 63 01 32 */	fmuls f3, f3, f4
/* 8006F3FC 0006A2FC  D1 03 00 04 */	stfs f8, 4(r3)
/* 8006F400 0006A300  EC 42 01 32 */	fmuls f2, f2, f4
/* 8006F404 0006A304  EC 21 01 32 */	fmuls f1, f1, f4
/* 8006F408 0006A308  D0 E3 00 08 */	stfs f7, 8(r3)
/* 8006F40C 0006A30C  EC 06 00 2A */	fadds f0, f6, f0
/* 8006F410 0006A310  D0 A3 00 0C */	stfs f5, 0xc(r3)
/* 8006F414 0006A314  D0 63 00 10 */	stfs f3, 0x10(r3)
/* 8006F418 0006A318  D0 43 00 14 */	stfs f2, 0x14(r3)
/* 8006F41C 0006A31C  D0 23 00 18 */	stfs f1, 0x18(r3)
/* 8006F420 0006A320  D0 03 00 1C */	stfs f0, 0x1c(r3)
/* 8006F424 0006A324  4E 80 00 20 */	blr 

# ProductTexSrtMtx_R__Q54nw4r3g3d6detail3dcc24@unnamed@g3d_3dsmax_cpp@FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt
.global ProductTexSrtMtx_R__Q54nw4r3g3d6detail3dcc24$$2unnamed$$2g3d_3dsmax_cpp$$2FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt
ProductTexSrtMtx_R__Q54nw4r3g3d6detail3dcc24$$2unnamed$$2g3d_3dsmax_cpp$$2FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt:
/* 8006F428 0006A328  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8006F42C 0006A32C  7C 08 02 A6 */	mflr r0
/* 8006F430 0006A330  C0 24 00 08 */	lfs f1, 8(r4)
/* 8006F434 0006A334  C0 02 89 E4 */	lfs f0, lbl_804C0404-_SDA2_BASE_(r2)
/* 8006F438 0006A338  38 81 00 08 */	addi r4, r1, 8
/* 8006F43C 0006A33C  90 01 00 24 */	stw r0, 0x24(r1)
/* 8006F440 0006A340  EC 20 00 72 */	fmuls f1, f0, f1
/* 8006F444 0006A344  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8006F448 0006A348  7C 7F 1B 78 */	mr r31, r3
/* 8006F44C 0006A34C  38 61 00 0C */	addi r3, r1, 0xc
/* 8006F450 0006A350  4B FC 05 11 */	bl SinCosFIdx__Q24nw4r4mathFPfPff
/* 8006F454 0006A354  C0 41 00 0C */	lfs f2, 0xc(r1)
/* 8006F458 0006A358  C0 1F 00 10 */	lfs f0, 0x10(r31)
/* 8006F45C 0006A35C  FC 20 10 50 */	fneg f1, f2
/* 8006F460 0006A360  C0 9F 00 00 */	lfs f4, 0(r31)
/* 8006F464 0006A364  C0 61 00 08 */	lfs f3, 8(r1)
/* 8006F468 0006A368  EC 42 00 32 */	fmuls f2, f2, f0
/* 8006F46C 0006A36C  C0 E2 89 DC */	lfs f7, lbl_804C03FC-_SDA2_BASE_(r2)
/* 8006F470 0006A370  EC 03 00 32 */	fmuls f0, f3, f0
/* 8006F474 0006A374  EC 63 01 32 */	fmuls f3, f3, f4
/* 8006F478 0006A378  C1 5F 00 04 */	lfs f10, 4(r31)
/* 8006F47C 0006A37C  EC 21 01 32 */	fmuls f1, f1, f4
/* 8006F480 0006A380  C0 BF 00 14 */	lfs f5, 0x14(r31)
/* 8006F484 0006A384  C1 1F 00 08 */	lfs f8, 8(r31)
/* 8006F488 0006A388  EC 43 10 2A */	fadds f2, f3, f2
/* 8006F48C 0006A38C  EC 61 00 2A */	fadds f3, f1, f0
/* 8006F490 0006A390  C0 3F 00 0C */	lfs f1, 0xc(r31)
/* 8006F494 0006A394  C0 1F 00 1C */	lfs f0, 0x1c(r31)
/* 8006F498 0006A398  D0 5F 00 00 */	stfs f2, 0(r31)
/* 8006F49C 0006A39C  EC C1 38 28 */	fsubs f6, f1, f7
/* 8006F4A0 0006A3A0  C0 9F 00 18 */	lfs f4, 0x18(r31)
/* 8006F4A4 0006A3A4  D0 7F 00 10 */	stfs f3, 0x10(r31)
/* 8006F4A8 0006A3A8  EC 60 38 28 */	fsubs f3, f0, f7
/* 8006F4AC 0006A3AC  C0 21 00 0C */	lfs f1, 0xc(r1)
/* 8006F4B0 0006A3B0  C1 61 00 08 */	lfs f11, 8(r1)
/* 8006F4B4 0006A3B4  FC 00 08 50 */	fneg f0, f1
/* 8006F4B8 0006A3B8  EC 41 01 72 */	fmuls f2, f1, f5
/* 8006F4BC 0006A3BC  ED 2B 02 B2 */	fmuls f9, f11, f10
/* 8006F4C0 0006A3C0  EC 20 02 B2 */	fmuls f1, f0, f10
/* 8006F4C4 0006A3C4  EC 0B 01 72 */	fmuls f0, f11, f5
/* 8006F4C8 0006A3C8  EC 49 10 2A */	fadds f2, f9, f2
/* 8006F4CC 0006A3CC  EC 01 00 2A */	fadds f0, f1, f0
/* 8006F4D0 0006A3D0  D0 5F 00 04 */	stfs f2, 4(r31)
/* 8006F4D4 0006A3D4  D0 1F 00 14 */	stfs f0, 0x14(r31)
/* 8006F4D8 0006A3D8  C0 21 00 0C */	lfs f1, 0xc(r1)
/* 8006F4DC 0006A3DC  C1 21 00 08 */	lfs f9, 8(r1)
/* 8006F4E0 0006A3E0  FC 00 08 50 */	fneg f0, f1
/* 8006F4E4 0006A3E4  EC 41 01 32 */	fmuls f2, f1, f4
/* 8006F4E8 0006A3E8  EC A9 02 32 */	fmuls f5, f9, f8
/* 8006F4EC 0006A3EC  EC 20 02 32 */	fmuls f1, f0, f8
/* 8006F4F0 0006A3F0  EC 09 01 32 */	fmuls f0, f9, f4
/* 8006F4F4 0006A3F4  EC 45 10 2A */	fadds f2, f5, f2
/* 8006F4F8 0006A3F8  EC 01 00 2A */	fadds f0, f1, f0
/* 8006F4FC 0006A3FC  D0 5F 00 08 */	stfs f2, 8(r31)
/* 8006F500 0006A400  D0 1F 00 18 */	stfs f0, 0x18(r31)
/* 8006F504 0006A404  C0 21 00 0C */	lfs f1, 0xc(r1)
/* 8006F508 0006A408  C0 A1 00 08 */	lfs f5, 8(r1)
/* 8006F50C 0006A40C  FC 00 08 50 */	fneg f0, f1
/* 8006F510 0006A410  EC 41 00 F2 */	fmuls f2, f1, f3
/* 8006F514 0006A414  EC 85 01 B2 */	fmuls f4, f5, f6
/* 8006F518 0006A418  EC 20 01 B2 */	fmuls f1, f0, f6
/* 8006F51C 0006A41C  EC 05 00 F2 */	fmuls f0, f5, f3
/* 8006F520 0006A420  EC 44 10 2A */	fadds f2, f4, f2
/* 8006F524 0006A424  EC 01 00 2A */	fadds f0, f1, f0
/* 8006F528 0006A428  EC 27 10 2A */	fadds f1, f7, f2
/* 8006F52C 0006A42C  EC 07 00 2A */	fadds f0, f7, f0
/* 8006F530 0006A430  D0 3F 00 0C */	stfs f1, 0xc(r31)
/* 8006F534 0006A434  D0 1F 00 1C */	stfs f0, 0x1c(r31)
/* 8006F538 0006A438  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8006F53C 0006A43C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8006F540 0006A440  7C 08 03 A6 */	mtlr r0
/* 8006F544 0006A444  38 21 00 20 */	addi r1, r1, 0x20
/* 8006F548 0006A448  4E 80 00 20 */	blr 

# ProductTexSrtMtx_T__Q54nw4r3g3d6detail3dcc24@unnamed@g3d_3dsmax_cpp@FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt
.global ProductTexSrtMtx_T__Q54nw4r3g3d6detail3dcc24$$2unnamed$$2g3d_3dsmax_cpp$$2FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt
ProductTexSrtMtx_T__Q54nw4r3g3d6detail3dcc24$$2unnamed$$2g3d_3dsmax_cpp$$2FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt:
/* 8006F54C 0006A44C  C0 63 00 0C */	lfs f3, 0xc(r3)
/* 8006F550 0006A450  C0 44 00 0C */	lfs f2, 0xc(r4)
/* 8006F554 0006A454  C0 23 00 1C */	lfs f1, 0x1c(r3)
/* 8006F558 0006A458  C0 04 00 10 */	lfs f0, 0x10(r4)
/* 8006F55C 0006A45C  EC 43 10 28 */	fsubs f2, f3, f2
/* 8006F560 0006A460  EC 01 00 2A */	fadds f0, f1, f0
/* 8006F564 0006A464  D0 43 00 0C */	stfs f2, 0xc(r3)
/* 8006F568 0006A468  D0 03 00 1C */	stfs f0, 0x1c(r3)
/* 8006F56C 0006A46C  4E 80 00 20 */	blr 

# ProductTexSrtMtx_SR__Q54nw4r3g3d6detail3dcc24@unnamed@g3d_3dsmax_cpp@FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt
.global ProductTexSrtMtx_SR__Q54nw4r3g3d6detail3dcc24$$2unnamed$$2g3d_3dsmax_cpp$$2FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt
ProductTexSrtMtx_SR__Q54nw4r3g3d6detail3dcc24$$2unnamed$$2g3d_3dsmax_cpp$$2FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt:
/* 8006F570 0006A470  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 8006F574 0006A474  7C 08 02 A6 */	mflr r0
/* 8006F578 0006A478  90 01 00 44 */	stw r0, 0x44(r1)
/* 8006F57C 0006A47C  DB E1 00 30 */	stfd f31, 0x30(r1)
/* 8006F580 0006A480  F3 E1 00 38 */	psq_st f31, 56(r1), 0, qr0
/* 8006F584 0006A484  DB C1 00 20 */	stfd f30, 0x20(r1)
/* 8006F588 0006A488  F3 C1 00 28 */	psq_st f30, 40(r1), 0, qr0
/* 8006F58C 0006A48C  C0 24 00 08 */	lfs f1, 8(r4)
/* 8006F590 0006A490  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8006F594 0006A494  7C 9F 23 78 */	mr r31, r4
/* 8006F598 0006A498  C0 02 89 E4 */	lfs f0, lbl_804C0404-_SDA2_BASE_(r2)
/* 8006F59C 0006A49C  38 81 00 08 */	addi r4, r1, 8
/* 8006F5A0 0006A4A0  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8006F5A4 0006A4A4  7C 7E 1B 78 */	mr r30, r3
/* 8006F5A8 0006A4A8  EC 20 00 72 */	fmuls f1, f0, f1
/* 8006F5AC 0006A4AC  38 61 00 0C */	addi r3, r1, 0xc
/* 8006F5B0 0006A4B0  4B FC 03 B1 */	bl SinCosFIdx__Q24nw4r4mathFPfPff
/* 8006F5B4 0006A4B4  C0 01 00 0C */	lfs f0, 0xc(r1)
/* 8006F5B8 0006A4B8  C0 BF 00 04 */	lfs f5, 4(r31)
/* 8006F5BC 0006A4BC  C0 5F 00 00 */	lfs f2, 0(r31)
/* 8006F5C0 0006A4C0  ED 05 00 32 */	fmuls f8, f5, f0
/* 8006F5C4 0006A4C4  C0 C1 00 08 */	lfs f6, 8(r1)
/* 8006F5C8 0006A4C8  EC 22 00 32 */	fmuls f1, f2, f0
/* 8006F5CC 0006A4CC  C0 7E 00 0C */	lfs f3, 0xc(r30)
/* 8006F5D0 0006A4D0  C0 E2 89 DC */	lfs f7, lbl_804C03FC-_SDA2_BASE_(r2)
/* 8006F5D4 0006A4D4  EC 02 01 B2 */	fmuls f0, f2, f6
/* 8006F5D8 0006A4D8  FD 80 40 50 */	fneg f12, f8
/* 8006F5DC 0006A4DC  C0 5E 00 1C */	lfs f2, 0x1c(r30)
/* 8006F5E0 0006A4E0  EC 83 38 28 */	fsubs f4, f3, f7
/* 8006F5E4 0006A4E4  C3 DE 00 00 */	lfs f30, 0(r30)
/* 8006F5E8 0006A4E8  EC 62 38 28 */	fsubs f3, f2, f7
/* 8006F5EC 0006A4EC  C1 BE 00 10 */	lfs f13, 0x10(r30)
/* 8006F5F0 0006A4F0  EC 45 01 B2 */	fmuls f2, f5, f6
/* 8006F5F4 0006A4F4  C1 7E 00 04 */	lfs f11, 4(r30)
/* 8006F5F8 0006A4F8  EC C0 01 32 */	fmuls f6, f0, f4
/* 8006F5FC 0006A4FC  C1 5E 00 14 */	lfs f10, 0x14(r30)
/* 8006F600 0006A500  EC A1 00 F2 */	fmuls f5, f1, f3
/* 8006F604 0006A504  C1 3E 00 08 */	lfs f9, 8(r30)
/* 8006F608 0006A508  EC 8C 01 32 */	fmuls f4, f12, f4
/* 8006F60C 0006A50C  C1 1E 00 18 */	lfs f8, 0x18(r30)
/* 8006F610 0006A510  EC 62 00 F2 */	fmuls f3, f2, f3
/* 8006F614 0006A514  EC A6 28 2A */	fadds f5, f6, f5
/* 8006F618 0006A518  EF E0 07 B2 */	fmuls f31, f0, f30
/* 8006F61C 0006A51C  EC C1 03 72 */	fmuls f6, f1, f13
/* 8006F620 0006A520  EC 64 18 2A */	fadds f3, f4, f3
/* 8006F624 0006A524  EC 87 28 2A */	fadds f4, f7, f5
/* 8006F628 0006A528  EF FF 30 2A */	fadds f31, f31, f6
/* 8006F62C 0006A52C  EC E7 18 2A */	fadds f7, f7, f3
/* 8006F630 0006A530  D0 9E 00 0C */	stfs f4, 0xc(r30)
/* 8006F634 0006A534  EC CC 07 B2 */	fmuls f6, f12, f30
/* 8006F638 0006A538  EC A2 03 72 */	fmuls f5, f2, f13
/* 8006F63C 0006A53C  EC 80 02 F2 */	fmuls f4, f0, f11
/* 8006F640 0006A540  D0 FE 00 1C */	stfs f7, 0x1c(r30)
/* 8006F644 0006A544  EC 61 02 B2 */	fmuls f3, f1, f10
/* 8006F648 0006A548  ED A6 28 2A */	fadds f13, f6, f5
/* 8006F64C 0006A54C  D3 FE 00 00 */	stfs f31, 0(r30)
/* 8006F650 0006A550  EC CC 02 F2 */	fmuls f6, f12, f11
/* 8006F654 0006A554  EC E4 18 2A */	fadds f7, f4, f3
/* 8006F658 0006A558  EC A2 02 B2 */	fmuls f5, f2, f10
/* 8006F65C 0006A55C  D1 BE 00 10 */	stfs f13, 0x10(r30)
/* 8006F660 0006A560  EC 80 02 72 */	fmuls f4, f0, f9
/* 8006F664 0006A564  EC 61 02 32 */	fmuls f3, f1, f8
/* 8006F668 0006A568  D0 FE 00 04 */	stfs f7, 4(r30)
/* 8006F66C 0006A56C  EC 02 02 32 */	fmuls f0, f2, f8
/* 8006F670 0006A570  EC 2C 02 72 */	fmuls f1, f12, f9
/* 8006F674 0006A574  EC A6 28 2A */	fadds f5, f6, f5
/* 8006F678 0006A578  EC 44 18 2A */	fadds f2, f4, f3
/* 8006F67C 0006A57C  EC 01 00 2A */	fadds f0, f1, f0
/* 8006F680 0006A580  D0 BE 00 14 */	stfs f5, 0x14(r30)
/* 8006F684 0006A584  D0 5E 00 08 */	stfs f2, 8(r30)
/* 8006F688 0006A588  D0 1E 00 18 */	stfs f0, 0x18(r30)
/* 8006F68C 0006A58C  E3 E1 00 38 */	psq_l f31, 56(r1), 0, qr0
/* 8006F690 0006A590  CB E1 00 30 */	lfd f31, 0x30(r1)
/* 8006F694 0006A594  E3 C1 00 28 */	psq_l f30, 40(r1), 0, qr0
/* 8006F698 0006A598  CB C1 00 20 */	lfd f30, 0x20(r1)
/* 8006F69C 0006A59C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8006F6A0 0006A5A0  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8006F6A4 0006A5A4  80 01 00 44 */	lwz r0, 0x44(r1)
/* 8006F6A8 0006A5A8  7C 08 03 A6 */	mtlr r0
/* 8006F6AC 0006A5AC  38 21 00 40 */	addi r1, r1, 0x40
/* 8006F6B0 0006A5B0  4E 80 00 20 */	blr 

# ProductTexSrtMtx_RT__Q54nw4r3g3d6detail3dcc24@unnamed@g3d_3dsmax_cpp@FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt
.global ProductTexSrtMtx_RT__Q54nw4r3g3d6detail3dcc24$$2unnamed$$2g3d_3dsmax_cpp$$2FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt
ProductTexSrtMtx_RT__Q54nw4r3g3d6detail3dcc24$$2unnamed$$2g3d_3dsmax_cpp$$2FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt:
/* 8006F6B4 0006A5B4  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8006F6B8 0006A5B8  7C 08 02 A6 */	mflr r0
/* 8006F6BC 0006A5BC  C0 24 00 08 */	lfs f1, 8(r4)
/* 8006F6C0 0006A5C0  90 01 00 24 */	stw r0, 0x24(r1)
/* 8006F6C4 0006A5C4  C0 02 89 E4 */	lfs f0, lbl_804C0404-_SDA2_BASE_(r2)
/* 8006F6C8 0006A5C8  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8006F6CC 0006A5CC  7C 9F 23 78 */	mr r31, r4
/* 8006F6D0 0006A5D0  EC 20 00 72 */	fmuls f1, f0, f1
/* 8006F6D4 0006A5D4  38 81 00 08 */	addi r4, r1, 8
/* 8006F6D8 0006A5D8  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8006F6DC 0006A5DC  7C 7E 1B 78 */	mr r30, r3
/* 8006F6E0 0006A5E0  38 61 00 0C */	addi r3, r1, 0xc
/* 8006F6E4 0006A5E4  4B FC 02 7D */	bl SinCosFIdx__Q24nw4r4mathFPfPff
/* 8006F6E8 0006A5E8  C0 41 00 0C */	lfs f2, 0xc(r1)
/* 8006F6EC 0006A5EC  C0 1E 00 10 */	lfs f0, 0x10(r30)
/* 8006F6F0 0006A5F0  FC 20 10 50 */	fneg f1, f2
/* 8006F6F4 0006A5F4  C0 9E 00 00 */	lfs f4, 0(r30)
/* 8006F6F8 0006A5F8  C0 61 00 08 */	lfs f3, 8(r1)
/* 8006F6FC 0006A5FC  EC 42 00 32 */	fmuls f2, f2, f0
/* 8006F700 0006A600  C1 5E 00 04 */	lfs f10, 4(r30)
/* 8006F704 0006A604  EC 03 00 32 */	fmuls f0, f3, f0
/* 8006F708 0006A608  EC 63 01 32 */	fmuls f3, f3, f4
/* 8006F70C 0006A60C  C0 DE 00 14 */	lfs f6, 0x14(r30)
/* 8006F710 0006A610  EC 21 01 32 */	fmuls f1, f1, f4
/* 8006F714 0006A614  C0 E2 89 DC */	lfs f7, lbl_804C03FC-_SDA2_BASE_(r2)
/* 8006F718 0006A618  C1 1E 00 08 */	lfs f8, 8(r30)
/* 8006F71C 0006A61C  EC 63 10 2A */	fadds f3, f3, f2
/* 8006F720 0006A620  EC A1 00 2A */	fadds f5, f1, f0
/* 8006F724 0006A624  C0 5E 00 0C */	lfs f2, 0xc(r30)
/* 8006F728 0006A628  C0 1F 00 0C */	lfs f0, 0xc(r31)
/* 8006F72C 0006A62C  D0 7E 00 00 */	stfs f3, 0(r30)
/* 8006F730 0006A630  EC 42 00 28 */	fsubs f2, f2, f0
/* 8006F734 0006A634  C0 3E 00 1C */	lfs f1, 0x1c(r30)
/* 8006F738 0006A638  D0 BE 00 10 */	stfs f5, 0x10(r30)
/* 8006F73C 0006A63C  C0 1F 00 10 */	lfs f0, 0x10(r31)
/* 8006F740 0006A640  C0 61 00 0C */	lfs f3, 0xc(r1)
/* 8006F744 0006A644  EC 01 00 2A */	fadds f0, f1, f0
/* 8006F748 0006A648  C1 61 00 08 */	lfs f11, 8(r1)
/* 8006F74C 0006A64C  FC 20 18 50 */	fneg f1, f3
/* 8006F750 0006A650  C0 9E 00 18 */	lfs f4, 0x18(r30)
/* 8006F754 0006A654  EC A3 01 B2 */	fmuls f5, f3, f6
/* 8006F758 0006A658  ED 2B 02 B2 */	fmuls f9, f11, f10
/* 8006F75C 0006A65C  EC 61 02 B2 */	fmuls f3, f1, f10
/* 8006F760 0006A660  EC 2B 01 B2 */	fmuls f1, f11, f6
/* 8006F764 0006A664  EC A9 28 2A */	fadds f5, f9, f5
/* 8006F768 0006A668  EC C2 38 28 */	fsubs f6, f2, f7
/* 8006F76C 0006A66C  EC 23 08 2A */	fadds f1, f3, f1
/* 8006F770 0006A670  D0 BE 00 04 */	stfs f5, 4(r30)
/* 8006F774 0006A674  EC 60 38 28 */	fsubs f3, f0, f7
/* 8006F778 0006A678  D0 3E 00 14 */	stfs f1, 0x14(r30)
/* 8006F77C 0006A67C  C0 21 00 0C */	lfs f1, 0xc(r1)
/* 8006F780 0006A680  C1 21 00 08 */	lfs f9, 8(r1)
/* 8006F784 0006A684  FC 00 08 50 */	fneg f0, f1
/* 8006F788 0006A688  EC 41 01 32 */	fmuls f2, f1, f4
/* 8006F78C 0006A68C  EC A9 02 32 */	fmuls f5, f9, f8
/* 8006F790 0006A690  EC 20 02 32 */	fmuls f1, f0, f8
/* 8006F794 0006A694  EC 09 01 32 */	fmuls f0, f9, f4
/* 8006F798 0006A698  EC 45 10 2A */	fadds f2, f5, f2
/* 8006F79C 0006A69C  EC 01 00 2A */	fadds f0, f1, f0
/* 8006F7A0 0006A6A0  D0 5E 00 08 */	stfs f2, 8(r30)
/* 8006F7A4 0006A6A4  D0 1E 00 18 */	stfs f0, 0x18(r30)
/* 8006F7A8 0006A6A8  C0 21 00 0C */	lfs f1, 0xc(r1)
/* 8006F7AC 0006A6AC  C0 A1 00 08 */	lfs f5, 8(r1)
/* 8006F7B0 0006A6B0  FC 00 08 50 */	fneg f0, f1
/* 8006F7B4 0006A6B4  EC 41 00 F2 */	fmuls f2, f1, f3
/* 8006F7B8 0006A6B8  EC 85 01 B2 */	fmuls f4, f5, f6
/* 8006F7BC 0006A6BC  EC 20 01 B2 */	fmuls f1, f0, f6
/* 8006F7C0 0006A6C0  EC 05 00 F2 */	fmuls f0, f5, f3
/* 8006F7C4 0006A6C4  EC 44 10 2A */	fadds f2, f4, f2
/* 8006F7C8 0006A6C8  EC 01 00 2A */	fadds f0, f1, f0
/* 8006F7CC 0006A6CC  EC 27 10 2A */	fadds f1, f7, f2
/* 8006F7D0 0006A6D0  EC 07 00 2A */	fadds f0, f7, f0
/* 8006F7D4 0006A6D4  D0 3E 00 0C */	stfs f1, 0xc(r30)
/* 8006F7D8 0006A6D8  D0 1E 00 1C */	stfs f0, 0x1c(r30)
/* 8006F7DC 0006A6DC  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8006F7E0 0006A6E0  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8006F7E4 0006A6E4  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8006F7E8 0006A6E8  7C 08 03 A6 */	mtlr r0
/* 8006F7EC 0006A6EC  38 21 00 20 */	addi r1, r1, 0x20
/* 8006F7F0 0006A6F0  4E 80 00 20 */	blr 

# ProductTexSrtMtx_ST__Q54nw4r3g3d6detail3dcc24@unnamed@g3d_3dsmax_cpp@FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt
.global ProductTexSrtMtx_ST__Q54nw4r3g3d6detail3dcc24$$2unnamed$$2g3d_3dsmax_cpp$$2FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt
ProductTexSrtMtx_ST__Q54nw4r3g3d6detail3dcc24$$2unnamed$$2g3d_3dsmax_cpp$$2FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt:
/* 8006F7F4 0006A6F4  C0 23 00 1C */	lfs f1, 0x1c(r3)
/* 8006F7F8 0006A6F8  C0 04 00 10 */	lfs f0, 0x10(r4)
/* 8006F7FC 0006A6FC  C0 63 00 0C */	lfs f3, 0xc(r3)
/* 8006F800 0006A700  C0 44 00 0C */	lfs f2, 0xc(r4)
/* 8006F804 0006A704  EC 01 00 2A */	fadds f0, f1, f0
/* 8006F808 0006A708  C0 E2 89 DC */	lfs f7, lbl_804C03FC-_SDA2_BASE_(r2)
/* 8006F80C 0006A70C  EC 83 10 28 */	fsubs f4, f3, f2
/* 8006F810 0006A710  C0 A4 00 04 */	lfs f5, 4(r4)
/* 8006F814 0006A714  EC 00 38 28 */	fsubs f0, f0, f7
/* 8006F818 0006A718  C0 63 00 14 */	lfs f3, 0x14(r3)
/* 8006F81C 0006A71C  C0 43 00 10 */	lfs f2, 0x10(r3)
/* 8006F820 0006A720  EC C4 38 28 */	fsubs f6, f4, f7
/* 8006F824 0006A724  EC 05 00 32 */	fmuls f0, f5, f0
/* 8006F828 0006A728  C1 64 00 00 */	lfs f11, 0(r4)
/* 8006F82C 0006A72C  EC 82 01 72 */	fmuls f4, f2, f5
/* 8006F830 0006A730  C1 03 00 00 */	lfs f8, 0(r3)
/* 8006F834 0006A734  EC 4B 01 B2 */	fmuls f2, f11, f6
/* 8006F838 0006A738  ED 48 02 F2 */	fmuls f10, f8, f11
/* 8006F83C 0006A73C  EC 07 00 2A */	fadds f0, f7, f0
/* 8006F840 0006A740  C1 23 00 04 */	lfs f9, 4(r3)
/* 8006F844 0006A744  EC C7 10 2A */	fadds f6, f7, f2
/* 8006F848 0006A748  C1 03 00 08 */	lfs f8, 8(r3)
/* 8006F84C 0006A74C  C0 43 00 18 */	lfs f2, 0x18(r3)
/* 8006F850 0006A750  ED 29 02 F2 */	fmuls f9, f9, f11
/* 8006F854 0006A754  EC E8 02 F2 */	fmuls f7, f8, f11
/* 8006F858 0006A758  D1 43 00 00 */	stfs f10, 0(r3)
/* 8006F85C 0006A75C  EC 63 01 72 */	fmuls f3, f3, f5
/* 8006F860 0006A760  EC 42 01 72 */	fmuls f2, f2, f5
/* 8006F864 0006A764  D0 C3 00 0C */	stfs f6, 0xc(r3)
/* 8006F868 0006A768  EC 01 00 32 */	fmuls f0, f1, f0
/* 8006F86C 0006A76C  D1 23 00 04 */	stfs f9, 4(r3)
/* 8006F870 0006A770  D0 E3 00 08 */	stfs f7, 8(r3)
/* 8006F874 0006A774  D0 83 00 10 */	stfs f4, 0x10(r3)
/* 8006F878 0006A778  D0 63 00 14 */	stfs f3, 0x14(r3)
/* 8006F87C 0006A77C  D0 43 00 18 */	stfs f2, 0x18(r3)
/* 8006F880 0006A780  D0 03 00 1C */	stfs f0, 0x1c(r3)
/* 8006F884 0006A784  4E 80 00 20 */	blr 

# ProductTexSrtMtx_SRT__Q54nw4r3g3d6detail3dcc24@unnamed@g3d_3dsmax_cpp@FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt
.global ProductTexSrtMtx_SRT__Q54nw4r3g3d6detail3dcc24$$2unnamed$$2g3d_3dsmax_cpp$$2FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt
ProductTexSrtMtx_SRT__Q54nw4r3g3d6detail3dcc24$$2unnamed$$2g3d_3dsmax_cpp$$2FPQ34nw4r4math5MTX34RCQ34nw4r3g3d6TexSrt:
/* 8006F888 0006A788  94 21 FF B0 */	stwu r1, -0x50(r1)
/* 8006F88C 0006A78C  7C 08 02 A6 */	mflr r0
/* 8006F890 0006A790  90 01 00 54 */	stw r0, 0x54(r1)
/* 8006F894 0006A794  DB E1 00 40 */	stfd f31, 0x40(r1)
/* 8006F898 0006A798  F3 E1 00 48 */	psq_st f31, 72(r1), 0, qr0
/* 8006F89C 0006A79C  DB C1 00 30 */	stfd f30, 0x30(r1)
/* 8006F8A0 0006A7A0  F3 C1 00 38 */	psq_st f30, 56(r1), 0, qr0
/* 8006F8A4 0006A7A4  DB A1 00 20 */	stfd f29, 0x20(r1)
/* 8006F8A8 0006A7A8  F3 A1 00 28 */	psq_st f29, 40(r1), 0, qr0
/* 8006F8AC 0006A7AC  C0 24 00 08 */	lfs f1, 8(r4)
/* 8006F8B0 0006A7B0  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8006F8B4 0006A7B4  7C 9F 23 78 */	mr r31, r4
/* 8006F8B8 0006A7B8  C0 02 89 E4 */	lfs f0, lbl_804C0404-_SDA2_BASE_(r2)
/* 8006F8BC 0006A7BC  38 81 00 08 */	addi r4, r1, 8
/* 8006F8C0 0006A7C0  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8006F8C4 0006A7C4  7C 7E 1B 78 */	mr r30, r3
/* 8006F8C8 0006A7C8  EC 20 00 72 */	fmuls f1, f0, f1
/* 8006F8CC 0006A7CC  38 61 00 0C */	addi r3, r1, 0xc
/* 8006F8D0 0006A7D0  4B FC 00 91 */	bl SinCosFIdx__Q24nw4r4mathFPfPff
/* 8006F8D4 0006A7D4  C0 41 00 0C */	lfs f2, 0xc(r1)
/* 8006F8D8 0006A7D8  C0 BF 00 04 */	lfs f5, 4(r31)
/* 8006F8DC 0006A7DC  C0 3E 00 0C */	lfs f1, 0xc(r30)
/* 8006F8E0 0006A7E0  C0 1F 00 0C */	lfs f0, 0xc(r31)
/* 8006F8E4 0006A7E4  ED 25 00 B2 */	fmuls f9, f5, f2
/* 8006F8E8 0006A7E8  C1 1F 00 00 */	lfs f8, 0(r31)
/* 8006F8EC 0006A7EC  EC 81 00 28 */	fsubs f4, f1, f0
/* 8006F8F0 0006A7F0  C0 C1 00 08 */	lfs f6, 8(r1)
/* 8006F8F4 0006A7F4  EC 28 00 B2 */	fmuls f1, f8, f2
/* 8006F8F8 0006A7F8  C0 E2 89 DC */	lfs f7, lbl_804C03FC-_SDA2_BASE_(r2)
/* 8006F8FC 0006A7FC  EC 08 01 B2 */	fmuls f0, f8, f6
/* 8006F900 0006A800  C0 7E 00 1C */	lfs f3, 0x1c(r30)
/* 8006F904 0006A804  C0 5F 00 10 */	lfs f2, 0x10(r31)
/* 8006F908 0006A808  FD 80 48 50 */	fneg f12, f9
/* 8006F90C 0006A80C  C3 BE 00 00 */	lfs f29, 0(r30)
/* 8006F910 0006A810  EC 84 38 28 */	fsubs f4, f4, f7
/* 8006F914 0006A814  EC 63 10 2A */	fadds f3, f3, f2
/* 8006F918 0006A818  C3 FE 00 10 */	lfs f31, 0x10(r30)
/* 8006F91C 0006A81C  EC 45 01 B2 */	fmuls f2, f5, f6
/* 8006F920 0006A820  EC C0 01 32 */	fmuls f6, f0, f4
/* 8006F924 0006A824  C1 7E 00 04 */	lfs f11, 4(r30)
/* 8006F928 0006A828  EC 63 38 28 */	fsubs f3, f3, f7
/* 8006F92C 0006A82C  EC 8C 01 32 */	fmuls f4, f12, f4
/* 8006F930 0006A830  C1 5E 00 14 */	lfs f10, 0x14(r30)
/* 8006F934 0006A834  EF C0 07 72 */	fmuls f30, f0, f29
/* 8006F938 0006A838  EC A1 00 F2 */	fmuls f5, f1, f3
/* 8006F93C 0006A83C  C1 3E 00 08 */	lfs f9, 8(r30)
/* 8006F940 0006A840  EC 62 00 F2 */	fmuls f3, f2, f3
/* 8006F944 0006A844  ED A1 07 F2 */	fmuls f13, f1, f31
/* 8006F948 0006A848  C1 1E 00 18 */	lfs f8, 0x18(r30)
/* 8006F94C 0006A84C  EC A6 28 2A */	fadds f5, f6, f5
/* 8006F950 0006A850  EC 64 18 2A */	fadds f3, f4, f3
/* 8006F954 0006A854  EC 9E 68 2A */	fadds f4, f30, f13
/* 8006F958 0006A858  ED A7 28 2A */	fadds f13, f7, f5
/* 8006F95C 0006A85C  EC E7 18 2A */	fadds f7, f7, f3
/* 8006F960 0006A860  D0 9E 00 00 */	stfs f4, 0(r30)
/* 8006F964 0006A864  EC CC 07 72 */	fmuls f6, f12, f29
/* 8006F968 0006A868  EC A2 07 F2 */	fmuls f5, f2, f31
/* 8006F96C 0006A86C  D1 BE 00 0C */	stfs f13, 0xc(r30)
/* 8006F970 0006A870  EC 80 02 F2 */	fmuls f4, f0, f11
/* 8006F974 0006A874  EC 61 02 B2 */	fmuls f3, f1, f10
/* 8006F978 0006A878  ED A6 28 2A */	fadds f13, f6, f5
/* 8006F97C 0006A87C  D0 FE 00 1C */	stfs f7, 0x1c(r30)
/* 8006F980 0006A880  EC CC 02 F2 */	fmuls f6, f12, f11
/* 8006F984 0006A884  EC E4 18 2A */	fadds f7, f4, f3
/* 8006F988 0006A888  EC A2 02 B2 */	fmuls f5, f2, f10
/* 8006F98C 0006A88C  D1 BE 00 10 */	stfs f13, 0x10(r30)
/* 8006F990 0006A890  EC 80 02 72 */	fmuls f4, f0, f9
/* 8006F994 0006A894  EC 61 02 32 */	fmuls f3, f1, f8
/* 8006F998 0006A898  D0 FE 00 04 */	stfs f7, 4(r30)
/* 8006F99C 0006A89C  EC 02 02 32 */	fmuls f0, f2, f8
/* 8006F9A0 0006A8A0  EC 2C 02 72 */	fmuls f1, f12, f9
/* 8006F9A4 0006A8A4  EC A6 28 2A */	fadds f5, f6, f5
/* 8006F9A8 0006A8A8  EC 44 18 2A */	fadds f2, f4, f3
/* 8006F9AC 0006A8AC  EC 01 00 2A */	fadds f0, f1, f0
/* 8006F9B0 0006A8B0  D0 BE 00 14 */	stfs f5, 0x14(r30)
/* 8006F9B4 0006A8B4  D0 5E 00 08 */	stfs f2, 8(r30)
/* 8006F9B8 0006A8B8  D0 1E 00 18 */	stfs f0, 0x18(r30)
/* 8006F9BC 0006A8BC  E3 E1 00 48 */	psq_l f31, 72(r1), 0, qr0
/* 8006F9C0 0006A8C0  CB E1 00 40 */	lfd f31, 0x40(r1)
/* 8006F9C4 0006A8C4  E3 C1 00 38 */	psq_l f30, 56(r1), 0, qr0
/* 8006F9C8 0006A8C8  CB C1 00 30 */	lfd f30, 0x30(r1)
/* 8006F9CC 0006A8CC  E3 A1 00 28 */	psq_l f29, 40(r1), 0, qr0
/* 8006F9D0 0006A8D0  CB A1 00 20 */	lfd f29, 0x20(r1)
/* 8006F9D4 0006A8D4  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8006F9D8 0006A8D8  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8006F9DC 0006A8DC  80 01 00 54 */	lwz r0, 0x54(r1)
/* 8006F9E0 0006A8E0  7C 08 03 A6 */	mtlr r0
/* 8006F9E4 0006A8E4  38 21 00 50 */	addi r1, r1, 0x50
/* 8006F9E8 0006A8E8  4E 80 00 20 */	blr 

.global CalcTexMtx_3dsmax__Q44nw4r3g3d6detail3dccFPQ34nw4r4math5MTX34bRCQ34nw4r3g3d6TexSrtQ44nw4r3g3d6TexSrt4Flag
CalcTexMtx_3dsmax__Q44nw4r3g3d6detail3dccFPQ34nw4r4math5MTX34bRCQ34nw4r3g3d6TexSrtQ44nw4r3g3d6TexSrt4Flag:
/* 8006F9EC 0006A8EC  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8006F9F0 0006A8F0  7C 08 02 A6 */	mflr r0
/* 8006F9F4 0006A8F4  90 01 00 14 */	stw r0, 0x14(r1)
/* 8006F9F8 0006A8F8  54 C0 FF 7E */	rlwinm r0, r6, 0x1f, 0x1d, 0x1f
/* 8006F9FC 0006A8FC  28 00 00 07 */	cmplwi r0, 7
/* 8006FA00 0006A900  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8006FA04 0006A904  7C 7F 1B 78 */	mr r31, r3
/* 8006FA08 0006A908  40 82 00 0C */	bne lbl_8006FA14
/* 8006FA0C 0006A90C  38 60 00 00 */	li r3, 0
/* 8006FA10 0006A910  48 00 00 64 */	b lbl_8006FA74
lbl_8006FA14:
/* 8006FA14 0006A914  2C 04 00 00 */	cmpwi r4, 0
/* 8006FA18 0006A918  41 82 00 24 */	beq lbl_8006FA3C
/* 8006FA1C 0006A91C  3C C0 80 38 */	lis r6, lbl_80378B50@ha
/* 8006FA20 0006A920  54 00 10 3A */	slwi r0, r0, 2
/* 8006FA24 0006A924  38 C6 8B 50 */	addi r6, r6, lbl_80378B50@l
/* 8006FA28 0006A928  7C A4 2B 78 */	mr r4, r5
/* 8006FA2C 0006A92C  7D 86 00 2E */	lwzx r12, r6, r0
/* 8006FA30 0006A930  7D 89 03 A6 */	mtctr r12
/* 8006FA34 0006A934  4E 80 04 21 */	bctrl 
/* 8006FA38 0006A938  48 00 00 20 */	b lbl_8006FA58
lbl_8006FA3C:
/* 8006FA3C 0006A93C  3C C0 80 38 */	lis r6, lbl_80378B6C@ha
/* 8006FA40 0006A940  54 00 10 3A */	slwi r0, r0, 2
/* 8006FA44 0006A944  38 C6 8B 6C */	addi r6, r6, lbl_80378B6C@l
/* 8006FA48 0006A948  7C A4 2B 78 */	mr r4, r5
/* 8006FA4C 0006A94C  7D 86 00 2E */	lwzx r12, r6, r0
/* 8006FA50 0006A950  7D 89 03 A6 */	mtctr r12
/* 8006FA54 0006A954  4E 80 04 21 */	bctrl 
lbl_8006FA58:
/* 8006FA58 0006A958  C0 22 89 D8 */	lfs f1, lbl_804C03F8-_SDA2_BASE_(r2)
/* 8006FA5C 0006A95C  38 60 00 01 */	li r3, 1
/* 8006FA60 0006A960  C0 02 89 E0 */	lfs f0, lbl_804C0400-_SDA2_BASE_(r2)
/* 8006FA64 0006A964  D0 3F 00 20 */	stfs f1, 0x20(r31)
/* 8006FA68 0006A968  D0 3F 00 24 */	stfs f1, 0x24(r31)
/* 8006FA6C 0006A96C  D0 1F 00 28 */	stfs f0, 0x28(r31)
/* 8006FA70 0006A970  D0 3F 00 2C */	stfs f1, 0x2c(r31)
lbl_8006FA74:
/* 8006FA74 0006A974  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8006FA78 0006A978  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8006FA7C 0006A97C  7C 08 03 A6 */	mtlr r0
/* 8006FA80 0006A980  38 21 00 10 */	addi r1, r1, 0x10
/* 8006FA84 0006A984  4E 80 00 20 */	blr 
