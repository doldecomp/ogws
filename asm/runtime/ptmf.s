.include "macros.inc"

.section .text, "ax"

.global __ptmf_test
__ptmf_test:
/* 800B1BC4 000ACAC4  80 A3 00 00 */	lwz r5, 0(r3)
/* 800B1BC8 000ACAC8  80 C3 00 04 */	lwz r6, 4(r3)
/* 800B1BCC 000ACACC  80 E3 00 08 */	lwz r7, 8(r3)
/* 800B1BD0 000ACAD0  38 60 00 01 */	li r3, 1
/* 800B1BD4 000ACAD4  2C 05 00 00 */	cmpwi r5, 0
/* 800B1BD8 000ACAD8  2F 06 00 00 */	cmpwi cr6, r6, 0
/* 800B1BDC 000ACADC  2F 87 00 00 */	cmpwi cr7, r7, 0
/* 800B1BE0 000ACAE0  4C 82 00 20 */	bnelr 
/* 800B1BE4 000ACAE4  4C 9A 00 20 */	bnelr cr6
/* 800B1BE8 000ACAE8  4C 9E 00 20 */	bnelr cr7
/* 800B1BEC 000ACAEC  38 60 00 00 */	li r3, 0
/* 800B1BF0 000ACAF0  4E 80 00 20 */	blr 

.global __ptmf_scall
__ptmf_scall:
/* 800B1BF4 000ACAF4  80 0C 00 00 */	lwz r0, 0(r12)
/* 800B1BF8 000ACAF8  81 6C 00 04 */	lwz r11, 4(r12)
/* 800B1BFC 000ACAFC  81 8C 00 08 */	lwz r12, 8(r12)
/* 800B1C00 000ACB00  7C 63 02 14 */	add r3, r3, r0
/* 800B1C04 000ACB04  2C 0B 00 00 */	cmpwi r11, 0
/* 800B1C08 000ACB08  41 80 00 0C */	blt lbl_800B1C14
/* 800B1C0C 000ACB0C  7D 83 60 2E */	lwzx r12, r3, r12
/* 800B1C10 000ACB10  7D 8C 58 2E */	lwzx r12, r12, r11
lbl_800B1C14:
/* 800B1C14 000ACB14  7D 89 03 A6 */	mtctr r12
/* 800B1C18 000ACB18  4E 80 04 20 */	bctr 
