.include "macros.inc"

# .text1 = .text

.section .text, "ax"  # 0x800076E0 - 0x80355080

.global Create__Q34nw4r2ef15EmitFormBuilderFQ34nw4r2ef12EmitFormType
Create__Q34nw4r2ef15EmitFormBuilderFQ34nw4r2ef12EmitFormType:
/* 8001D42C 0001832C  28 04 00 0A */	cmplwi r4, 0xa
/* 8001D430 00018330  41 81 00 54 */	bgt lbl_8001D484
/* 8001D434 00018334  3C 60 80 39 */	lis r3, lbl_80393F08@ha
/* 8001D438 00018338  54 80 10 3A */	slwi r0, r4, 2
/* 8001D43C 0001833C  38 63 3F 08 */	addi r3, r3, lbl_80393F08@l
/* 8001D440 00018340  7C 63 00 2E */	lwzx r3, r3, r0
/* 8001D444 00018344  7C 69 03 A6 */	mtctr r3
/* 8001D448 00018348  4E 80 04 20 */	bctr 
/* 8001D44C 0001834C  38 6D 96 B0 */	addi r3, r13, lbl_804BEA30-_SDA_BASE_
/* 8001D450 00018350  4E 80 00 20 */	blr 
/* 8001D454 00018354  38 6D 96 B4 */	addi r3, r13, lbl_804BEA34-_SDA_BASE_
/* 8001D458 00018358  4E 80 00 20 */	blr 
/* 8001D45C 0001835C  38 6D 96 B8 */	addi r3, r13, lbl_804BEA38-_SDA_BASE_
/* 8001D460 00018360  4E 80 00 20 */	blr 
/* 8001D464 00018364  38 6D 96 BC */	addi r3, r13, lbl_804BEA3C-_SDA_BASE_
/* 8001D468 00018368  4E 80 00 20 */	blr 
/* 8001D46C 0001836C  38 6D 96 C0 */	addi r3, r13, lbl_804BEA40-_SDA_BASE_
/* 8001D470 00018370  4E 80 00 20 */	blr 
/* 8001D474 00018374  38 6D 96 C4 */	addi r3, r13, lbl_804BEA44-_SDA_BASE_
/* 8001D478 00018378  4E 80 00 20 */	blr 
/* 8001D47C 0001837C  38 6D 96 C8 */	addi r3, r13, lbl_804BEA48-_SDA_BASE_
/* 8001D480 00018380  4E 80 00 20 */	blr 
lbl_8001D484:
/* 8001D484 00018384  38 60 00 00 */	li r3, 0
/* 8001D488 00018388  4E 80 00 20 */	blr 

# __sinit_\ef_emform_cpp
.global __sinit_$$3ef_emform_cpp
__sinit_$$3ef_emform_cpp:
/* 8001D48C 0001838C  3D 20 80 39 */	lis r9, lbl_80393F60@ha
/* 8001D490 00018390  3D 00 80 39 */	lis r8, lbl_80393F50@ha
/* 8001D494 00018394  3C E0 80 39 */	lis r7, lbl_80393F80@ha
/* 8001D498 00018398  3C C0 80 39 */	lis r6, lbl_80393F70@ha
/* 8001D49C 0001839C  3C A0 80 39 */	lis r5, lbl_80393F90@ha
/* 8001D4A0 000183A0  3C 80 80 39 */	lis r4, lbl_80393FA0@ha
/* 8001D4A4 000183A4  3C 60 80 39 */	lis r3, lbl_80393F40@ha
/* 8001D4A8 000183A8  39 29 3F 60 */	addi r9, r9, lbl_80393F60@l
/* 8001D4AC 000183AC  39 08 3F 50 */	addi r8, r8, lbl_80393F50@l
/* 8001D4B0 000183B0  38 E7 3F 80 */	addi r7, r7, lbl_80393F80@l
/* 8001D4B4 000183B4  38 C6 3F 70 */	addi r6, r6, lbl_80393F70@l
/* 8001D4B8 000183B8  38 A5 3F 90 */	addi r5, r5, lbl_80393F90@l
/* 8001D4BC 000183BC  38 84 3F A0 */	addi r4, r4, lbl_80393FA0@l
/* 8001D4C0 000183C0  38 63 3F 40 */	addi r3, r3, lbl_80393F40@l
/* 8001D4C4 000183C4  91 2D 96 B0 */	stw r9, lbl_804BEA30-_SDA_BASE_(r13)
/* 8001D4C8 000183C8  91 0D 96 B4 */	stw r8, lbl_804BEA34-_SDA_BASE_(r13)
/* 8001D4CC 000183CC  90 ED 96 B8 */	stw r7, lbl_804BEA38-_SDA_BASE_(r13)
/* 8001D4D0 000183D0  90 CD 96 BC */	stw r6, lbl_804BEA3C-_SDA_BASE_(r13)
/* 8001D4D4 000183D4  90 AD 96 C0 */	stw r5, lbl_804BEA40-_SDA_BASE_(r13)
/* 8001D4D8 000183D8  90 8D 96 C4 */	stw r4, lbl_804BEA44-_SDA_BASE_(r13)
/* 8001D4DC 000183DC  90 6D 96 C8 */	stw r3, lbl_804BEA48-_SDA_BASE_(r13)
/* 8001D4E0 000183E0  4E 80 00 20 */	blr 
