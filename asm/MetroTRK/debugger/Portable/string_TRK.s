.include "macros.inc"

.section .text, "ax"
.global TRK_strlen
TRK_strlen:
/* 800C3A90 000BE990  38 83 FF FF */	addi r4, r3, -1
/* 800C3A94 000BE994  38 60 FF FF */	li r3, -1
lbl_800C3A98:
/* 800C3A98 000BE998  8C 04 00 01 */	lbzu r0, 1(r4)
/* 800C3A9C 000BE99C  38 63 00 01 */	addi r3, r3, 1
/* 800C3AA0 000BE9A0  28 00 00 00 */	cmplwi r0, 0
/* 800C3AA4 000BE9A4  40 82 FF F4 */	bne lbl_800C3A98
/* 800C3AA8 000BE9A8  4E 80 00 20 */	blr 
