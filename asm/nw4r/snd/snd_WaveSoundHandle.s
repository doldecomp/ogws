.include "macros.inc"

.section .text, "ax"  # 0x800076E0 - 0x80355080 

.global DetachSound__Q34nw4r3snd15WaveSoundHandleFv
DetachSound__Q34nw4r3snd15WaveSoundHandleFv:
/* 8004F238 0004A138  80 83 00 00 */	lwz r4, 0(r3)
/* 8004F23C 0004A13C  2C 04 00 00 */	cmpwi r4, 0
/* 8004F240 0004A140  41 82 00 18 */	beq lbl_8004F258
/* 8004F244 0004A144  80 04 01 B0 */	lwz r0, 0x1b0(r4)
/* 8004F248 0004A148  7C 00 18 40 */	cmplw r0, r3
/* 8004F24C 0004A14C  40 82 00 0C */	bne lbl_8004F258
/* 8004F250 0004A150  38 00 00 00 */	li r0, 0
/* 8004F254 0004A154  90 04 01 B0 */	stw r0, 0x1b0(r4)
lbl_8004F258:
/* 8004F258 0004A158  80 03 00 00 */	lwz r0, 0(r3)
/* 8004F25C 0004A15C  2C 00 00 00 */	cmpwi r0, 0
/* 8004F260 0004A160  4D 82 00 20 */	beqlr 
/* 8004F264 0004A164  38 00 00 00 */	li r0, 0
/* 8004F268 0004A168  90 03 00 00 */	stw r0, 0(r3)
/* 8004F26C 0004A16C  4E 80 00 20 */	blr 
