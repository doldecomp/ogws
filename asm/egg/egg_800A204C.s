.include "macros.inc"

.section .text, "ax"
# I'm pretty sure this is multScalar__Q23EGG8Vector3fFf,
# but until I can get a good idea of 800A2074, I don't
# want to label this one.
.global func_800A204C
func_800A204C:
/* 800A204C 0009CF4C  C0 64 00 08 */	lfs f3, 8(r4)
/* 800A2050 0009CF50  C0 44 00 04 */	lfs f2, 4(r4)
/* 800A2054 0009CF54  C0 04 00 00 */	lfs f0, 0(r4)
/* 800A2058 0009CF58  EC 63 00 72 */	fmuls f3, f3, f1
/* 800A205C 0009CF5C  EC 42 00 72 */	fmuls f2, f2, f1
/* 800A2060 0009CF60  EC 00 00 72 */	fmuls f0, f0, f1
/* 800A2064 0009CF64  D0 63 00 08 */	stfs f3, 8(r3)
/* 800A2068 0009CF68  D0 03 00 00 */	stfs f0, 0(r3)
/* 800A206C 0009CF6C  D0 43 00 04 */	stfs f2, 4(r3)
/* 800A2070 0009CF70  4E 80 00 20 */	blr 

.global func_800A2074
func_800A2074:
/* 800A2074 0009CF74  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800A2078 0009CF78  7C 08 02 A6 */	mflr r0
/* 800A207C 0009CF7C  C0 05 00 04 */	lfs f0, 4(r5)
/* 800A2080 0009CF80  90 01 00 24 */	stw r0, 0x24(r1)
/* 800A2084 0009CF84  80 E5 00 00 */	lwz r7, 0(r5)
/* 800A2088 0009CF88  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800A208C 0009CF8C  7C 7F 1B 78 */	mr r31, r3
/* 800A2090 0009CF90  80 C5 00 04 */	lwz r6, 4(r5)
/* 800A2094 0009CF94  C0 24 00 04 */	lfs f1, 4(r4)
/* 800A2098 0009CF98  C0 64 00 00 */	lfs f3, 0(r4)
/* 800A209C 0009CF9C  EC 81 00 32 */	fmuls f4, f1, f0
/* 800A20A0 0009CFA0  C0 05 00 00 */	lfs f0, 0(r5)
/* 800A20A4 0009CFA4  C0 44 00 08 */	lfs f2, 8(r4)
/* 800A20A8 0009CFA8  C0 25 00 08 */	lfs f1, 8(r5)
/* 800A20AC 0009CFAC  EC 63 20 3A */	fmadds f3, f3, f0, f4
/* 800A20B0 0009CFB0  C0 04 00 0C */	lfs f0, 0xc(r4)
/* 800A20B4 0009CFB4  80 05 00 08 */	lwz r0, 8(r5)
/* 800A20B8 0009CFB8  90 E3 00 00 */	stw r7, 0(r3)
/* 800A20BC 0009CFBC  EC 22 18 7A */	fmadds f1, f2, f1, f3
/* 800A20C0 0009CFC0  90 C3 00 04 */	stw r6, 4(r3)
/* 800A20C4 0009CFC4  EC 21 00 28 */	fsubs f1, f1, f0
/* 800A20C8 0009CFC8  90 03 00 08 */	stw r0, 8(r3)
/* 800A20CC 0009CFCC  38 61 00 08 */	addi r3, r1, 8
/* 800A20D0 0009CFD0  4B FF FF 7D */	bl func_800A204C
/* 800A20D4 0009CFD4  C0 3F 00 00 */	lfs f1, 0(r31)
/* 800A20D8 0009CFD8  C0 01 00 08 */	lfs f0, 8(r1)
/* 800A20DC 0009CFDC  C0 5F 00 04 */	lfs f2, 4(r31)
/* 800A20E0 0009CFE0  EC 01 00 28 */	fsubs f0, f1, f0
/* 800A20E4 0009CFE4  C0 3F 00 08 */	lfs f1, 8(r31)
/* 800A20E8 0009CFE8  D0 1F 00 00 */	stfs f0, 0(r31)
/* 800A20EC 0009CFEC  C0 01 00 0C */	lfs f0, 0xc(r1)
/* 800A20F0 0009CFF0  EC 02 00 28 */	fsubs f0, f2, f0
/* 800A20F4 0009CFF4  D0 1F 00 04 */	stfs f0, 4(r31)
/* 800A20F8 0009CFF8  C0 01 00 10 */	lfs f0, 0x10(r1)
/* 800A20FC 0009CFFC  EC 01 00 28 */	fsubs f0, f1, f0
/* 800A2100 0009D000  D0 1F 00 08 */	stfs f0, 8(r31)
/* 800A2104 0009D004  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800A2108 0009D008  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800A210C 0009D00C  7C 08 03 A6 */	mtlr r0
/* 800A2110 0009D010  38 21 00 20 */	addi r1, r1, 0x20
/* 800A2114 0009D014  4E 80 00 20 */	blr 
