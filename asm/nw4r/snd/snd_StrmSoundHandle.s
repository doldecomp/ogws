.include "macros.inc"

.section .text, "ax"  # 0x800076E0 - 0x80355080 

.global DetachSound__Q34nw4r3snd15StrmSoundHandleFv
DetachSound__Q34nw4r3snd15StrmSoundHandleFv:
/* 8004AF80 00045E80  80 83 00 00 */	lwz r4, 0(r3)
/* 8004AF84 00045E84  2C 04 00 00 */	cmpwi r4, 0
/* 8004AF88 00045E88  41 82 00 18 */	beq lbl_8004AFA0
/* 8004AF8C 00045E8C  80 04 09 20 */	lwz r0, 0x920(r4)
/* 8004AF90 00045E90  7C 00 18 40 */	cmplw r0, r3
/* 8004AF94 00045E94  40 82 00 0C */	bne lbl_8004AFA0
/* 8004AF98 00045E98  38 00 00 00 */	li r0, 0
/* 8004AF9C 00045E9C  90 04 09 20 */	stw r0, 0x920(r4)
lbl_8004AFA0:
/* 8004AFA0 00045EA0  80 03 00 00 */	lwz r0, 0(r3)
/* 8004AFA4 00045EA4  2C 00 00 00 */	cmpwi r0, 0
/* 8004AFA8 00045EA8  4D 82 00 20 */	beqlr 
/* 8004AFAC 00045EAC  38 00 00 00 */	li r0, 0
/* 8004AFB0 00045EB0  90 03 00 00 */	stw r0, 0(r3)
/* 8004AFB4 00045EB4  4E 80 00 20 */	blr 
