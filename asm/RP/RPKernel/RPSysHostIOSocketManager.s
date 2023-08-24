.include "macros.inc"

.section .sbss, "wa"
.balign 0x8
.global sInstance__24RPSysHostIOSocketManager
sInstance__24RPSysHostIOSocketManager:
	.skip 0x4

.section .data, "wa"
.balign 0x8
.global __vt__24RPSysHostIOSocketManager
__vt__24RPSysHostIOSocketManager:
	.long 0
    .long 0
    .long __dt__24RPSysHostIOSocketManagerFv

.section .text, "ax"
.global Update__24RPSysHostIOSocketManagerFv
Update__24RPSysHostIOSocketManagerFv:
/* 80190840 0018B740  4E 80 00 20 */	blr 

.global AddHostIOSocket__24RPSysHostIOSocketManagerFP18IRPSysHostIOSocketP18IRPSysHostIOSocket
AddHostIOSocket__24RPSysHostIOSocketManagerFP18IRPSysHostIOSocketP18IRPSysHostIOSocket:
/* 80190844 0018B744  4E 80 00 20 */	blr 

.global __dt__24RPSysHostIOSocketManagerFv
__dt__24RPSysHostIOSocketManagerFv:
/* 80190848 0018B748  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8019084C 0018B74C  7C 08 02 A6 */	mflr r0
/* 80190850 0018B750  2C 03 00 00 */	cmpwi r3, 0
/* 80190854 0018B754  90 01 00 14 */	stw r0, 0x14(r1)
/* 80190858 0018B758  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8019085C 0018B75C  7C 7F 1B 78 */	mr r31, r3
/* 80190860 0018B760  41 82 00 10 */	beq lbl_80190870
/* 80190864 0018B764  2C 04 00 00 */	cmpwi r4, 0
/* 80190868 0018B768  40 81 00 08 */	ble lbl_80190870
/* 8019086C 0018B76C  4B F1 2A 19 */	bl __dl__FPv
lbl_80190870:
/* 80190870 0018B770  7F E3 FB 78 */	mr r3, r31
/* 80190874 0018B774  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80190878 0018B778  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8019087C 0018B77C  7C 08 03 A6 */	mtlr r0
/* 80190880 0018B780  38 21 00 10 */	addi r1, r1, 0x10
/* 80190884 0018B784  4E 80 00 20 */	blr 

.global CreateInstance__24RPSysHostIOSocketManagerFv
CreateInstance__24RPSysHostIOSocketManagerFv:
/* 80190888 0018B788  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8019088C 0018B78C  7C 08 02 A6 */	mflr r0
/* 80190890 0018B790  38 60 00 04 */	li r3, 4
/* 80190894 0018B794  90 01 00 14 */	stw r0, 0x14(r1)
/* 80190898 0018B798  4B F1 29 AD */	bl __nw__FUl
/* 8019089C 0018B79C  2C 03 00 00 */	cmpwi r3, 0
/* 801908A0 0018B7A0  41 82 00 10 */	beq lbl_801908B0
/* 801908A4 0018B7A4  3C 80 80 3C */	lis r4, __vt__24RPSysHostIOSocketManager@ha
/* 801908A8 0018B7A8  38 84 99 B0 */	addi r4, r4, __vt__24RPSysHostIOSocketManager@l
/* 801908AC 0018B7AC  90 83 00 00 */	stw r4, 0(r3)
lbl_801908B0:
/* 801908B0 0018B7B0  90 6D A1 A8 */	stw r3, sInstance__24RPSysHostIOSocketManager-_SDA_BASE_(r13)
/* 801908B4 0018B7B4  80 01 00 14 */	lwz r0, 0x14(r1)
/* 801908B8 0018B7B8  7C 08 03 A6 */	mtlr r0
/* 801908BC 0018B7BC  38 21 00 10 */	addi r1, r1, 0x10
/* 801908C0 0018B7C0  4E 80 00 20 */	blr 
