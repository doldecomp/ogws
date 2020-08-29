.include "macros.inc"

# I'm not sure what these are for
# They both don't seem related to the DrawSmoothStripeStrategy functions
# They don't seem to be related to the math_arithmetic functions either

.section .text, "ax"  # 0x800076E0 - 0x80355080 

.global func_8002F700
func_8002F700:
/* 8002F700 0002A600  80 C4 00 00 */	lwz r6, 0(r4)
/* 8002F704 0002A604  54 A0 13 BA */	rlwinm r0, r5, 2, 0xe, 0x1d
/* 8002F708 0002A608  80 86 00 04 */	lwz r4, 4(r6)
/* 8002F70C 0002A60C  7C 84 32 14 */	add r4, r4, r6
/* 8002F710 0002A610  38 A4 00 08 */	addi r5, r4, 8
/* 8002F714 0002A614  80 84 00 08 */	lwz r4, 8(r4)
/* 8002F718 0002A618  7C 84 2A 14 */	add r4, r4, r5
/* 8002F71C 0002A61C  38 84 00 04 */	addi r4, r4, 4
/* 8002F720 0002A620  7C 84 02 14 */	add r4, r4, r0
/* 8002F724 0002A624  80 04 00 04 */	lwz r0, 4(r4)
/* 8002F728 0002A628  90 03 00 00 */	stw r0, 0(r3)
/* 8002F72C 0002A62C  4E 80 00 20 */	blr 

.global func_8002F730
func_8002F730:
/* 8002F730 0002A630  2C 04 00 00 */	cmpwi r4, 0
/* 8002F734 0002A634  80 63 00 00 */	lwz r3, 0(r3)
/* 8002F738 0002A638  41 82 00 14 */	beq lbl_8002F74C
/* 8002F73C 0002A63C  88 03 00 04 */	lbz r0, 4(r3)
/* 8002F740 0002A640  60 00 00 08 */	ori r0, r0, 8
/* 8002F744 0002A644  98 03 00 04 */	stb r0, 4(r3)
/* 8002F748 0002A648  4E 80 00 20 */	blr 
lbl_8002F74C:
/* 8002F74C 0002A64C  88 03 00 04 */	lbz r0, 4(r3)
/* 8002F750 0002A650  54 00 07 76 */	rlwinm r0, r0, 0, 0x1d, 0x1b
/* 8002F754 0002A654  98 03 00 04 */	stb r0, 4(r3)
/* 8002F758 0002A658  4E 80 00 20 */	blr 