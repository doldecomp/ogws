.include "macros.inc"

.section .text, "ax"

.global func_800A1DB0
func_800A1DB0:
/* 800A1DB0 0009CCB0  C0 24 00 08 */	lfs f1, 8(r4)
/* 800A1DB4 0009CCB4  C0 05 00 08 */	lfs f0, 8(r5)
/* 800A1DB8 0009CCB8  C0 64 00 04 */	lfs f3, 4(r4)
/* 800A1DBC 0009CCBC  EC 81 00 28 */	fsubs f4, f1, f0
/* 800A1DC0 0009CCC0  C0 45 00 04 */	lfs f2, 4(r5)
/* 800A1DC4 0009CCC4  C0 24 00 00 */	lfs f1, 0(r4)
/* 800A1DC8 0009CCC8  C0 05 00 00 */	lfs f0, 0(r5)
/* 800A1DCC 0009CCCC  EC 43 10 28 */	fsubs f2, f3, f2
/* 800A1DD0 0009CCD0  D0 83 00 08 */	stfs f4, 8(r3)
/* 800A1DD4 0009CCD4  EC 01 00 28 */	fsubs f0, f1, f0
/* 800A1DD8 0009CCD8  D0 43 00 04 */	stfs f2, 4(r3)
/* 800A1DDC 0009CCDC  D0 03 00 00 */	stfs f0, 0(r3)
/* 800A1DE0 0009CCE0  4E 80 00 20 */	blr 
