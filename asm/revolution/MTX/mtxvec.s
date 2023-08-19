.include "macros.inc"

.section .text, "ax"
.global PSMTXMultVec
PSMTXMultVec:
/* 800E8260 000E3160  E0 04 00 00 */	psq_l f0, 0(r4), 0, qr0
/* 800E8264 000E3164  E0 43 00 00 */	psq_l f2, 0(r3), 0, qr0
/* 800E8268 000E3168  E0 24 80 08 */	psq_l f1, 8(r4), 1, qr0
/* 800E826C 000E316C  10 82 00 32 */	ps_mul f4, f2, f0
/* 800E8270 000E3170  E0 63 00 08 */	psq_l f3, 8(r3), 0, qr0
/* 800E8274 000E3174  10 A3 20 7A */	ps_madd f5, f3, f1, f4
/* 800E8278 000E3178  E1 03 00 10 */	psq_l f8, 16(r3), 0, qr0
/* 800E827C 000E317C  10 C5 29 94 */	ps_sum0 f6, f5, f6, f5
/* 800E8280 000E3180  E1 23 00 18 */	psq_l f9, 24(r3), 0, qr0
/* 800E8284 000E3184  11 48 00 32 */	ps_mul f10, f8, f0
/* 800E8288 000E3188  F0 C5 80 00 */	psq_st f6, 0(r5), 1, qr0
/* 800E828C 000E318C  11 69 50 7A */	ps_madd f11, f9, f1, f10
/* 800E8290 000E3190  E0 43 00 20 */	psq_l f2, 32(r3), 0, qr0
/* 800E8294 000E3194  11 8B 5B 14 */	ps_sum0 f12, f11, f12, f11
/* 800E8298 000E3198  E0 63 00 28 */	psq_l f3, 40(r3), 0, qr0
/* 800E829C 000E319C  10 82 00 32 */	ps_mul f4, f2, f0
/* 800E82A0 000E31A0  F1 85 80 04 */	psq_st f12, 4(r5), 1, qr0
/* 800E82A4 000E31A4  10 A3 20 7A */	ps_madd f5, f3, f1, f4
/* 800E82A8 000E31A8  10 C5 29 94 */	ps_sum0 f6, f5, f6, f5
/* 800E82AC 000E31AC  F0 C5 80 08 */	psq_st f6, 8(r5), 1, qr0
/* 800E82B0 000E31B0  4E 80 00 20 */	blr 
