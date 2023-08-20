# 
# This is not part of RPSysLoadScene, nor RPSysResourceManager
# (proven by other RP titles). It is also not present in Rev 0,
# but it *is* in Rev 2 (still unused).
# 

.include "macros.inc"

.section .ctors, "a"
.4byte "__sinit_\RP_80186e40_cpp"

.section .bss, "wa"
.balign 0x8
.global lbl_804A3DA0
lbl_804A3DA0:
	.skip 0x10
.global lbl_804A3DB0
lbl_804A3DB0:
	.skip 0x30

.section .text, "ax"
.global "__sinit_\RP_80186e40_cpp"
"__sinit_\RP_80186e40_cpp":
/* 80186E40 00181D40  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80186E44 00181D44  7C 08 02 A6 */	mflr r0
/* 80186E48 00181D48  3C 60 80 4A */	lis r3, lbl_804A3DB0@ha
/* 80186E4C 00181D4C  3C 80 80 0A */	lis r4, func_800A1D30@ha
/* 80186E50 00181D50  3C A0 80 0A */	lis r5, __dt__Q23EGG8Vector3fFv@ha
/* 80186E54 00181D54  90 01 00 14 */	stw r0, 0x14(r1)
/* 80186E58 00181D58  38 C0 00 0C */	li r6, 0xc
/* 80186E5C 00181D5C  38 63 3D B0 */	addi r3, r3, lbl_804A3DB0@l
/* 80186E60 00181D60  38 84 1D 30 */	addi r4, r4, func_800A1D30@l
/* 80186E64 00181D64  38 A5 1C 30 */	addi r5, r5, __dt__Q23EGG8Vector3fFv@l
/* 80186E68 00181D68  38 E0 00 04 */	li r7, 4
/* 80186E6C 00181D6C  4B F2 AB E9 */	bl __construct_array
/* 80186E70 00181D70  3C 80 80 18 */	lis r4, __arraydtor@ha
/* 80186E74 00181D74  3C A0 80 4A */	lis r5, lbl_804A3DA0@ha
/* 80186E78 00181D78  38 84 6E 98 */	addi r4, r4, __arraydtor@l
/* 80186E7C 00181D7C  38 60 00 00 */	li r3, 0
/* 80186E80 00181D80  38 A5 3D A0 */	addi r5, r5, lbl_804A3DA0@l
/* 80186E84 00181D84  4B F2 A9 B1 */	bl func_800B1834
/* 80186E88 00181D88  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80186E8C 00181D8C  7C 08 03 A6 */	mtlr r0
/* 80186E90 00181D90  38 21 00 10 */	addi r1, r1, 0x10
/* 80186E94 00181D94  4E 80 00 20 */	blr 

__arraydtor:
/* 80186E98 00181D98  3C 60 80 4A */	lis r3, lbl_804A3DB0@ha
/* 80186E9C 00181D9C  3C 80 80 0A */	lis r4, __dt__Q23EGG8Vector3fFv@ha
/* 80186EA0 00181DA0  38 63 3D B0 */	addi r3, r3, lbl_804A3DB0@l
/* 80186EA4 00181DA4  38 A0 00 0C */	li r5, 0xc
/* 80186EA8 00181DA8  38 84 1C 30 */	addi r4, r4, __dt__Q23EGG8Vector3fFv@l
/* 80186EAC 00181DAC  38 C0 00 04 */	li r6, 4
/* 80186EB0 00181DB0  4B F2 AC 9C */	b __destroy_arr
