.include "macros.inc"

.section .text, "ax"
.global func_8018D6AC
func_8018D6AC:
/* 8018D6AC 001885AC  54 80 06 3E */	clrlwi r0, r4, 0x18
/* 8018D6B0 001885B0  38 80 00 01 */	li r4, 1
/* 8018D6B4 001885B4  80 63 00 18 */	lwz r3, 0x18(r3)
/* 8018D6B8 001885B8  7C 80 00 30 */	slw r0, r4, r0
/* 8018D6BC 001885BC  7C 63 00 38 */	and r3, r3, r0
/* 8018D6C0 001885C0  7C 03 00 D0 */	neg r0, r3
/* 8018D6C4 001885C4  7C 00 1B 78 */	or r0, r0, r3
/* 8018D6C8 001885C8  54 03 0F FE */	srwi r3, r0, 0x1f
/* 8018D6CC 001885CC  4E 80 00 20 */	blr 
