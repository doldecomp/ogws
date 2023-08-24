.include "macros.inc"

.section .data, "wa"
.balign 0x8
.global __vt__18IRPSysHostIOSocket
__vt__18IRPSysHostIOSocket:
    .long 0
    .long 0
    .long __dt__18IRPSysHostIOSocketFv
    .long GenMessage__18IRPSysHostIOSocketFv
    .long ListenPropertyEvent__18IRPSysHostIOSocketFv

.section .text, "ax"
.global __dt__18IRPSysHostIOSocketFv
__dt__18IRPSysHostIOSocketFv:
/* 80190794 0018B694  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80190798 0018B698  7C 08 02 A6 */	mflr r0
/* 8019079C 0018B69C  2C 03 00 00 */	cmpwi r3, 0
/* 801907A0 0018B6A0  90 01 00 14 */	stw r0, 0x14(r1)
/* 801907A4 0018B6A4  93 E1 00 0C */	stw r31, 0xc(r1)
/* 801907A8 0018B6A8  7C 7F 1B 78 */	mr r31, r3
/* 801907AC 0018B6AC  41 82 00 10 */	beq lbl_801907BC
/* 801907B0 0018B6B0  2C 04 00 00 */	cmpwi r4, 0
/* 801907B4 0018B6B4  40 81 00 08 */	ble lbl_801907BC
/* 801907B8 0018B6B8  4B F1 2A CD */	bl __dl__FPv
lbl_801907BC:
/* 801907BC 0018B6BC  7F E3 FB 78 */	mr r3, r31
/* 801907C0 0018B6C0  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 801907C4 0018B6C4  80 01 00 14 */	lwz r0, 0x14(r1)
/* 801907C8 0018B6C8  7C 08 03 A6 */	mtlr r0
/* 801907CC 0018B6CC  38 21 00 10 */	addi r1, r1, 0x10
/* 801907D0 0018B6D0  4E 80 00 20 */	blr 

.global __ct__18IRPSysHostIOSocketFv
__ct__18IRPSysHostIOSocketFv:
/* 801907D4 0018B6D4  3C 80 80 3C */	lis r4, __vt__18IRPSysHostIOSocket@ha
/* 801907D8 0018B6D8  38 84 99 98 */	addi r4, r4, __vt__18IRPSysHostIOSocket@l
/* 801907DC 0018B6DC  90 83 00 00 */	stw r4, 0(r3)
/* 801907E0 0018B6E0  4E 80 00 20 */	blr 

.global __ct__18IRPSysHostIOSocketFPCce
__ct__18IRPSysHostIOSocketFPCce:
/* 801907E4 0018B6E4  94 21 FF 90 */	stwu r1, -0x70(r1)
/* 801907E8 0018B6E8  40 86 00 24 */	bne cr1, lbl_8019080C
/* 801907EC 0018B6EC  D8 21 00 28 */	stfd f1, 0x28(r1)
/* 801907F0 0018B6F0  D8 41 00 30 */	stfd f2, 0x30(r1)
/* 801907F4 0018B6F4  D8 61 00 38 */	stfd f3, 0x38(r1)
/* 801907F8 0018B6F8  D8 81 00 40 */	stfd f4, 0x40(r1)
/* 801907FC 0018B6FC  D8 A1 00 48 */	stfd f5, 0x48(r1)
/* 80190800 0018B700  D8 C1 00 50 */	stfd f6, 0x50(r1)
/* 80190804 0018B704  D8 E1 00 58 */	stfd f7, 0x58(r1)
/* 80190808 0018B708  D9 01 00 60 */	stfd f8, 0x60(r1)
lbl_8019080C:
/* 8019080C 0018B70C  3D 60 80 3C */	lis r11, __vt__18IRPSysHostIOSocket@ha
/* 80190810 0018B710  90 61 00 08 */	stw r3, 8(r1)
/* 80190814 0018B714  39 6B 99 98 */	addi r11, r11, __vt__18IRPSysHostIOSocket@l
/* 80190818 0018B718  91 63 00 00 */	stw r11, 0(r3)
/* 8019081C 0018B71C  90 81 00 0C */	stw r4, 0xc(r1)
/* 80190820 0018B720  90 A1 00 10 */	stw r5, 0x10(r1)
/* 80190824 0018B724  90 C1 00 14 */	stw r6, 0x14(r1)
/* 80190828 0018B728  90 E1 00 18 */	stw r7, 0x18(r1)
/* 8019082C 0018B72C  91 01 00 1C */	stw r8, 0x1c(r1)
/* 80190830 0018B730  91 21 00 20 */	stw r9, 0x20(r1)
/* 80190834 0018B734  91 41 00 24 */	stw r10, 0x24(r1)
/* 80190838 0018B738  38 21 00 70 */	addi r1, r1, 0x70
/* 8019083C 0018B73C  4E 80 00 20 */	blr 
