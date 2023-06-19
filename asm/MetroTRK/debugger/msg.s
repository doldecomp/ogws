.include "macros.inc"

.section .text, "ax"
.global TRKMessageSend
TRKMessageSend:
/* 800C1578 000BC478  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800C157C 000BC47C  7C 08 02 A6 */	mflr r0
/* 800C1580 000BC480  90 01 00 14 */	stw r0, 0x14(r1)
/* 800C1584 000BC484  80 83 00 08 */	lwz r4, 8(r3)
/* 800C1588 000BC488  38 63 00 10 */	addi r3, r3, 0x10
/* 800C158C 000BC48C  48 00 49 21 */	bl TRKWriteUARTN
/* 800C1590 000BC490  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800C1594 000BC494  38 60 00 00 */	li r3, 0
/* 800C1598 000BC498  7C 08 03 A6 */	mtlr r0
/* 800C159C 000BC49C  38 21 00 10 */	addi r1, r1, 0x10
/* 800C15A0 000BC4A0  4E 80 00 20 */	blr 
