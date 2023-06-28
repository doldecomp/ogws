.include "macros.inc"

.section .text, "ax"
.global RFLSetIconDrawDoneCallback
RFLSetIconDrawDoneCallback:
/* 80171738 0016C638  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8017173C 0016C63C  7C 08 02 A6 */	mflr r0
/* 80171740 0016C640  90 01 00 14 */	stw r0, 0x14(r1)
/* 80171744 0016C644  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80171748 0016C648  7C 7F 1B 78 */	mr r31, r3
/* 8017174C 0016C64C  4B FF 6C B1 */	bl RFLiGetManager
/* 80171750 0016C650  93 E3 1F 14 */	stw r31, 0x1f14(r3)
/* 80171754 0016C654  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80171758 0016C658  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8017175C 0016C65C  7C 08 03 A6 */	mtlr r0
/* 80171760 0016C660  38 21 00 10 */	addi r1, r1, 0x10
/* 80171764 0016C664  4E 80 00 20 */	blr 
