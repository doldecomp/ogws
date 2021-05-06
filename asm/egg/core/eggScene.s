.include "macros.inc"



.section .data, "wa"
.balign 0x8
.global __vt__Q23EGG5Scene
__vt__Q23EGG5Scene:
    .long 0
    .long 0
    .long __dt__Q23EGG5SceneFv
    .long calc__Q23EGG5SceneFv
    .long draw__Q23EGG5SceneFv
    .long enter__Q23EGG5SceneFv
    .long exit__Q23EGG5SceneFv
    .long reinit__Q23EGG5SceneFv
    .long incoming_childDestroy__Q23EGG5SceneFv
    .long outgoing_childCreate__Q23EGG5SceneFv

.section .rodata, "a"
.balign 0x8
.global lbl_8037ABB0
lbl_8037ABB0:
	.string "eggScene.cpp"
    .string "mHeap != NULL"

.section .text, "ax"
.global __ct__Q23EGG5SceneFv
__ct__Q23EGG5SceneFv:
/* 800AAFE4 000A5EE4  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800AAFE8 000A5EE8  7C 08 02 A6 */	mflr r0
/* 800AAFEC 000A5EEC  3C 80 80 3A */	lis r4, __vt__Q23EGG5Scene@ha
/* 800AAFF0 000A5EF0  90 01 00 14 */	stw r0, 0x14(r1)
/* 800AAFF4 000A5EF4  38 84 83 98 */	addi r4, r4, __vt__Q23EGG5Scene@l
/* 800AAFF8 000A5EF8  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800AAFFC 000A5EFC  7C 7F 1B 78 */	mr r31, r3
/* 800AB000 000A5F00  90 83 00 00 */	stw r4, 0(r3)
/* 800AB004 000A5F04  80 0D 99 28 */	lwz r0, sCurrentHeap__Q23EGG4Heap-_SDA_BASE_(r13)
/* 800AB008 000A5F08  2C 00 00 00 */	cmpwi r0, 0
/* 800AB00C 000A5F0C  90 03 00 04 */	stw r0, 4(r3)
/* 800AB010 000A5F10  40 82 00 1C */	bne lbl_800AB02C
/* 800AB014 000A5F14  3C 60 80 38 */	lis r3, lbl_8037ABB0@ha
/* 800AB018 000A5F18  38 80 00 20 */	li r4, 0x20
/* 800AB01C 000A5F1C  38 63 AB B0 */	addi r3, r3, lbl_8037ABB0@l
/* 800AB020 000A5F20  38 A3 00 0D */	addi r5, r3, 0xd
/* 800AB024 000A5F24  4C C6 31 82 */	crclr 6
/* 800AB028 000A5F28  4B FF 6E E1 */	bl system_halt
lbl_800AB02C:
/* 800AB02C 000A5F2C  80 AD 99 5C */	lwz r5, lbl_804BECDC-_SDA_BASE_(r13)
/* 800AB030 000A5F30  38 80 00 00 */	li r4, 0
/* 800AB034 000A5F34  38 00 FF FF */	li r0, -1
/* 800AB038 000A5F38  7F E3 FB 78 */	mr r3, r31
/* 800AB03C 000A5F3C  90 BF 00 08 */	stw r5, 8(r31)
/* 800AB040 000A5F40  80 AD 99 60 */	lwz r5, lbl_804BECE0-_SDA_BASE_(r13)
/* 800AB044 000A5F44  90 BF 00 0C */	stw r5, 0xc(r31)
/* 800AB048 000A5F48  80 AD 99 64 */	lwz r5, lbl_804BECE4-_SDA_BASE_(r13)
/* 800AB04C 000A5F4C  90 BF 00 10 */	stw r5, 0x10(r31)
/* 800AB050 000A5F50  90 9F 00 14 */	stw r4, 0x14(r31)
/* 800AB054 000A5F54  90 9F 00 18 */	stw r4, 0x18(r31)
/* 800AB058 000A5F58  90 1F 00 1C */	stw r0, 0x1c(r31)
/* 800AB05C 000A5F5C  90 9F 00 20 */	stw r4, 0x20(r31)
/* 800AB060 000A5F60  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 800AB064 000A5F64  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800AB068 000A5F68  7C 08 03 A6 */	mtlr r0
/* 800AB06C 000A5F6C  38 21 00 10 */	addi r1, r1, 0x10
/* 800AB070 000A5F70  4E 80 00 20 */	blr 

.global __dt__Q23EGG5SceneFv
__dt__Q23EGG5SceneFv:
/* 800AB074 000A5F74  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800AB078 000A5F78  7C 08 02 A6 */	mflr r0
/* 800AB07C 000A5F7C  2C 03 00 00 */	cmpwi r3, 0
/* 800AB080 000A5F80  90 01 00 14 */	stw r0, 0x14(r1)
/* 800AB084 000A5F84  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800AB088 000A5F88  7C 7F 1B 78 */	mr r31, r3
/* 800AB08C 000A5F8C  41 82 00 10 */	beq lbl_800AB09C
/* 800AB090 000A5F90  2C 04 00 00 */	cmpwi r4, 0
/* 800AB094 000A5F94  40 81 00 08 */	ble lbl_800AB09C
/* 800AB098 000A5F98  4B FF 81 ED */	bl __dl__FPv
lbl_800AB09C:
/* 800AB09C 000A5F9C  7F E3 FB 78 */	mr r3, r31
/* 800AB0A0 000A5FA0  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 800AB0A4 000A5FA4  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800AB0A8 000A5FA8  7C 08 03 A6 */	mtlr r0
/* 800AB0AC 000A5FAC  38 21 00 10 */	addi r1, r1, 0x10
/* 800AB0B0 000A5FB0  4E 80 00 20 */	blr 
