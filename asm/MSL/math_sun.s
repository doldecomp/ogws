.include "macros.inc"

.section .text, "ax"
.global scalbn
scalbn:
/* 800BD164 000B8064  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800BD168 000B8068  7C 08 02 A6 */	mflr r0
/* 800BD16C 000B806C  90 01 00 24 */	stw r0, 0x24(r1)
/* 800BD170 000B8070  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800BD174 000B8074  7C 7F 1B 78 */	mr r31, r3
/* 800BD178 000B8078  38 61 00 08 */	addi r3, r1, 8
/* 800BD17C 000B807C  48 00 38 B5 */	bl frexp
/* 800BD180 000B8080  80 01 00 08 */	lwz r0, 8(r1)
/* 800BD184 000B8084  7C 60 FA 14 */	add r3, r0, r31
/* 800BD188 000B8088  90 61 00 08 */	stw r3, 8(r1)
/* 800BD18C 000B808C  48 00 39 2D */	bl ldexp
/* 800BD190 000B8090  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800BD194 000B8094  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800BD198 000B8098  7C 08 03 A6 */	mtlr r0
/* 800BD19C 000B809C  38 21 00 20 */	addi r1, r1, 0x20
/* 800BD1A0 000B80A0  4E 80 00 20 */	blr 
