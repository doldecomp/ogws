.include "macros.inc"

.section .text, "ax"
.global TRKTargetContinue
TRKTargetContinue:
/* 800C61F8 000C10F8  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800C61FC 000C10FC  7C 08 02 A6 */	mflr r0
/* 800C6200 000C1100  38 60 00 00 */	li r3, 0
/* 800C6204 000C1104  90 01 00 14 */	stw r0, 0x14(r1)
/* 800C6208 000C1108  4B FF DC A9 */	bl TRKTargetSetStopped
/* 800C620C 000C110C  4B FF FC 41 */	bl UnreserveEXI2Port
/* 800C6210 000C1110  4B FF DB 19 */	bl TRKSwapAndGo
/* 800C6214 000C1114  4B FF FC 69 */	bl ReserveEXI2Port
/* 800C6218 000C1118  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800C621C 000C111C  38 60 00 00 */	li r3, 0
/* 800C6220 000C1120  7C 08 03 A6 */	mtlr r0
/* 800C6224 000C1124  38 21 00 10 */	addi r1, r1, 0x10
/* 800C6228 000C1128  4E 80 00 20 */	blr 
