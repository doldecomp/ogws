.include "macros.inc"

.section .bss, "wa"
.global lbl_803F1700
lbl_803F1700:
	.skip 0x18000

.section .text, "ax"
.global GetScaleTemporary__Q44nw4r3g3d6detail7workmemFv
GetScaleTemporary__Q44nw4r3g3d6detail7workmemFv:
/* 8006A028 00064F28  3C 60 80 3F */	lis r3, lbl_803F1700@ha
/* 8006A02C 00064F2C  38 63 17 00 */	addi r3, r3, lbl_803F1700@l
/* 8006A030 00064F30  4E 80 00 20 */	blr 

.global GetMtxIDTemporary__Q44nw4r3g3d6detail7workmemFv
GetMtxIDTemporary__Q44nw4r3g3d6detail7workmemFv:
/* 8006A034 00064F34  3C 60 80 3F */	lis r3, lbl_803F1700@ha
/* 8006A038 00064F38  38 63 17 00 */	addi r3, r3, lbl_803F1700@l
/* 8006A03C 00064F3C  38 63 60 00 */	addi r3, r3, 0x6000
/* 8006A040 00064F40  4E 80 00 20 */	blr 

.global GetMdlZTemporary__Q44nw4r3g3d6detail7workmemFv
GetMdlZTemporary__Q44nw4r3g3d6detail7workmemFv:
/* 8006A044 00064F44  3C 60 80 3F */	lis r3, lbl_803F1700@ha
/* 8006A048 00064F48  38 63 17 00 */	addi r3, r3, lbl_803F1700@l
/* 8006A04C 00064F4C  4E 80 00 20 */	blr 

.global GetSkinningMtxTemporary__Q44nw4r3g3d6detail7workmemFv
GetSkinningMtxTemporary__Q44nw4r3g3d6detail7workmemFv:
/* 8006A050 00064F50  3C 60 80 3F */	lis r3, lbl_803F1700@ha
/* 8006A054 00064F54  38 63 17 00 */	addi r3, r3, lbl_803F1700@l
/* 8006A058 00064F58  4E 80 00 20 */	blr 

.global GetBillboardMtxTemporary__Q44nw4r3g3d6detail7workmemFv
GetBillboardMtxTemporary__Q44nw4r3g3d6detail7workmemFv:
/* 8006A05C 00064F5C  3C 60 80 3F */	lis r3, lbl_803F1700@ha
/* 8006A060 00064F60  38 63 17 00 */	addi r3, r3, lbl_803F1700@l
/* 8006A064 00064F64  4E 80 00 20 */	blr 

.global GetShpAnmResultBufTemporary__Q44nw4r3g3d6detail7workmemFv
GetShpAnmResultBufTemporary__Q44nw4r3g3d6detail7workmemFv:
/* 8006A068 00064F68  3C 60 80 3F */	lis r3, lbl_803F1700@ha
/* 8006A06C 00064F6C  38 63 17 00 */	addi r3, r3, lbl_803F1700@l
/* 8006A070 00064F70  4E 80 00 20 */	blr 
