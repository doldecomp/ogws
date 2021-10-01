.include "macros.inc"

.section .rodata, "a"
.balign 0x8
.global lbl_80379DF0
lbl_80379DF0:
	.string "eggIScnProc.cpp"
    .string "mpDataSet != NULL"
    .string "mpDataSet == NULL"
    .string "procNum > 0"
    .string "procIndex < getNumScnProc()"
    .string "pScnGroup"
    .string "is_push_back"
    .string "is_remove"
    .string "m"
    .string "pScnProc"
    .string "p_data"
    .string "p_data->mpThis"

.section .data, "wa"
.balign 0x8
.global __vt__Q23EGG8IScnProc
__vt__Q23EGG8IScnProc:
    .long 0
    .long 0
    .long __dt__Q23EGG8IScnProcFv
    .long 0
.global lbl_80397EB0
lbl_80397EB0:
	.string "procIndex < getNumScnProc()"
    .balign 0x4
.global lbl_80397ECC
lbl_80397ECC:
	.string "eggIScnProc.h"
    .balign 0x4

.section .text, "ax"
.global __ct__Q23EGG8IScnProcFv
__ct__Q23EGG8IScnProcFv:
/* 8009C43C 0009733C  3C 80 80 39 */	lis r4, __vt__Q23EGG8IScnProc@ha
/* 8009C440 00097340  38 00 00 00 */	li r0, 0
/* 8009C444 00097344  38 84 7E A0 */	addi r4, r4, __vt__Q23EGG8IScnProc@l
/* 8009C448 00097348  90 03 00 04 */	stw r0, 4(r3)
/* 8009C44C 0009734C  90 83 00 00 */	stw r4, 0(r3)
/* 8009C450 00097350  B0 03 00 08 */	sth r0, 8(r3)
/* 8009C454 00097354  4E 80 00 20 */	blr 

.global __dt__Q23EGG8IScnProcFv
__dt__Q23EGG8IScnProcFv:
/* 8009C458 00097358  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8009C45C 0009735C  7C 08 02 A6 */	mflr r0
/* 8009C460 00097360  2C 03 00 00 */	cmpwi r3, 0
/* 8009C464 00097364  90 01 00 24 */	stw r0, 0x24(r1)
/* 8009C468 00097368  BF 61 00 0C */	stmw r27, 0xc(r1)
/* 8009C46C 0009736C  7C 7B 1B 78 */	mr r27, r3
/* 8009C470 00097370  7C 9C 23 78 */	mr r28, r4
/* 8009C474 00097374  41 82 00 94 */	beq lbl_8009C508
/* 8009C478 00097378  80 03 00 04 */	lwz r0, 4(r3)
/* 8009C47C 0009737C  3C 80 80 39 */	lis r4, __vt__Q23EGG8IScnProc@ha
/* 8009C480 00097380  38 84 7E A0 */	addi r4, r4, __vt__Q23EGG8IScnProc@l
/* 8009C484 00097384  2C 00 00 00 */	cmpwi r0, 0
/* 8009C488 00097388  90 83 00 00 */	stw r4, 0(r3)
/* 8009C48C 0009738C  40 82 00 1C */	bne lbl_8009C4A8
/* 8009C490 00097390  3C 60 80 38 */	lis r3, lbl_80379DF0@ha
/* 8009C494 00097394  38 80 00 1C */	li r4, 0x1c
/* 8009C498 00097398  38 63 9D F0 */	addi r3, r3, lbl_80379DF0@l
/* 8009C49C 0009739C  38 A3 00 10 */	addi r5, r3, 0x10
/* 8009C4A0 000973A0  4C C6 31 82 */	crclr 6
/* 8009C4A4 000973A4  48 00 5A 65 */	bl system_halt
lbl_8009C4A8:
/* 8009C4A8 000973A8  3B A0 00 00 */	li r29, 0
/* 8009C4AC 000973AC  3B C0 00 00 */	li r30, 0
/* 8009C4B0 000973B0  3B E0 00 00 */	li r31, 0
/* 8009C4B4 000973B4  48 00 00 28 */	b lbl_8009C4DC
lbl_8009C4B8:
/* 8009C4B8 000973B8  80 1B 00 04 */	lwz r0, 4(r27)
/* 8009C4BC 000973BC  7C 60 F2 14 */	add r3, r0, r30
/* 8009C4C0 000973C0  80 63 00 04 */	lwz r3, 4(r3)
/* 8009C4C4 000973C4  4B FC 70 71 */	bl Destroy__Q34nw4r3g3d6G3dObjFv
/* 8009C4C8 000973C8  80 1B 00 04 */	lwz r0, 4(r27)
/* 8009C4CC 000973CC  3B BD 00 01 */	addi r29, r29, 1
/* 8009C4D0 000973D0  7C 60 F2 14 */	add r3, r0, r30
/* 8009C4D4 000973D4  3B DE 00 0C */	addi r30, r30, 0xc
/* 8009C4D8 000973D8  93 E3 00 04 */	stw r31, 4(r3)
lbl_8009C4DC:
/* 8009C4DC 000973DC  A0 1B 00 08 */	lhz r0, 8(r27)
/* 8009C4E0 000973E0  7C 1D 00 00 */	cmpw r29, r0
/* 8009C4E4 000973E4  41 80 FF D4 */	blt lbl_8009C4B8
/* 8009C4E8 000973E8  80 7B 00 04 */	lwz r3, 4(r27)
/* 8009C4EC 000973EC  48 00 6D 99 */	bl __dl__FPv
/* 8009C4F0 000973F0  38 00 00 00 */	li r0, 0
/* 8009C4F4 000973F4  2C 1C 00 00 */	cmpwi r28, 0
/* 8009C4F8 000973F8  90 1B 00 04 */	stw r0, 4(r27)
/* 8009C4FC 000973FC  40 81 00 0C */	ble lbl_8009C508
/* 8009C500 00097400  7F 63 DB 78 */	mr r3, r27
/* 8009C504 00097404  48 00 6D 81 */	bl __dl__FPv
lbl_8009C508:
/* 8009C508 00097408  7F 63 DB 78 */	mr r3, r27
/* 8009C50C 0009740C  BB 61 00 0C */	lmw r27, 0xc(r1)
/* 8009C510 00097410  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8009C514 00097414  7C 08 03 A6 */	mtlr r0
/* 8009C518 00097418  38 21 00 20 */	addi r1, r1, 0x20
/* 8009C51C 0009741C  4E 80 00 20 */	blr 

.global createScnProc__Q23EGG8IScnProcFUsP12MEMAllocator
createScnProc__Q23EGG8IScnProcFUsP12MEMAllocator:
/* 8009C520 00097420  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8009C524 00097424  7C 08 02 A6 */	mflr r0
/* 8009C528 00097428  90 01 00 34 */	stw r0, 0x34(r1)
/* 8009C52C 0009742C  BF 41 00 18 */	stmw r26, 0x18(r1)
/* 8009C530 00097430  7C 7D 1B 78 */	mr r29, r3
/* 8009C534 00097434  7C 9A 23 78 */	mr r26, r4
/* 8009C538 00097438  7C BE 2B 78 */	mr r30, r5
/* 8009C53C 0009743C  80 03 00 04 */	lwz r0, 4(r3)
/* 8009C540 00097440  2C 00 00 00 */	cmpwi r0, 0
/* 8009C544 00097444  41 82 00 1C */	beq lbl_8009C560
/* 8009C548 00097448  3C 60 80 38 */	lis r3, lbl_80379DF0@ha
/* 8009C54C 0009744C  38 80 00 2F */	li r4, 0x2f
/* 8009C550 00097450  38 63 9D F0 */	addi r3, r3, lbl_80379DF0@l
/* 8009C554 00097454  38 A3 00 22 */	addi r5, r3, 0x22
/* 8009C558 00097458  4C C6 31 82 */	crclr 6
/* 8009C55C 0009745C  48 00 59 AD */	bl system_halt
lbl_8009C560:
/* 8009C560 00097460  2C 1A 00 00 */	cmpwi r26, 0
/* 8009C564 00097464  40 82 00 1C */	bne lbl_8009C580
/* 8009C568 00097468  3C 60 80 38 */	lis r3, lbl_80379DF0@ha
/* 8009C56C 0009746C  38 80 00 30 */	li r4, 0x30
/* 8009C570 00097470  38 63 9D F0 */	addi r3, r3, lbl_80379DF0@l
/* 8009C574 00097474  38 A3 00 34 */	addi r5, r3, 0x34
/* 8009C578 00097478  4C C6 31 82 */	crclr 6
/* 8009C57C 0009747C  48 00 59 8D */	bl system_halt
lbl_8009C580:
/* 8009C580 00097480  1C 7A 00 0C */	mulli r3, r26, 0xc
/* 8009C584 00097484  B3 5D 00 08 */	sth r26, 8(r29)
/* 8009C588 00097488  48 00 6C D9 */	bl __nwa__FUl
/* 8009C58C 0009748C  90 7D 00 04 */	stw r3, 4(r29)
/* 8009C590 00097490  3B E0 00 00 */	li r31, 0
/* 8009C594 00097494  3F 60 80 0A */	lis r27, 0x800a
/* 8009C598 00097498  3B 80 00 01 */	li r28, 1
/* 8009C59C 0009749C  48 00 00 8C */	b lbl_8009C628
lbl_8009C5A0:
/* 8009C5A0 000974A0  2C 1E 00 00 */	cmpwi r30, 0
/* 8009C5A4 000974A4  40 82 00 0C */	bne lbl_8009C5B0
/* 8009C5A8 000974A8  80 6D 98 6C */	lwz r3, sAllocator__Q23EGG10G3DUtility-_SDA_BASE_(r13)
/* 8009C5AC 000974AC  48 00 00 08 */	b lbl_8009C5B4
lbl_8009C5B0:
/* 8009C5B0 000974B0  7F C3 F3 78 */	mr r3, r30
lbl_8009C5B4:
/* 8009C5B4 000974B4  57 E0 04 3E */	clrlwi r0, r31, 0x10
/* 8009C5B8 000974B8  38 81 00 08 */	addi r4, r1, 8
/* 8009C5BC 000974BC  1F 40 00 0C */	mulli r26, r0, 0xc
/* 8009C5C0 000974C0  38 BB C9 08 */	addi r5, r27, -14072
/* 8009C5C4 000974C4  38 C0 00 01 */	li r6, 1
/* 8009C5C8 000974C8  38 E0 00 00 */	li r7, 0
/* 8009C5CC 000974CC  39 00 00 00 */	li r8, 0
/* 8009C5D0 000974D0  4B FD B6 69 */	bl func_80077C38
/* 8009C5D4 000974D4  80 1D 00 04 */	lwz r0, 4(r29)
/* 8009C5D8 000974D8  57 E4 04 3E */	clrlwi r4, r31, 0x10
/* 8009C5DC 000974DC  57 E5 06 3E */	clrlwi r5, r31, 0x18
/* 8009C5E0 000974E0  38 C0 00 01 */	li r6, 1
/* 8009C5E4 000974E4  7C E0 D2 14 */	add r7, r0, r26
/* 8009C5E8 000974E8  90 67 00 04 */	stw r3, 4(r7)
/* 8009C5EC 000974EC  7F A3 EB 78 */	mr r3, r29
/* 8009C5F0 000974F0  80 1D 00 04 */	lwz r0, 4(r29)
/* 8009C5F4 000974F4  7D 00 D2 14 */	add r8, r0, r26
/* 8009C5F8 000974F8  80 E8 00 04 */	lwz r7, 4(r8)
/* 8009C5FC 000974FC  91 07 00 F0 */	stw r8, 0xf0(r7)
/* 8009C600 00097500  80 1D 00 04 */	lwz r0, 4(r29)
/* 8009C604 00097504  7C E0 D2 14 */	add r7, r0, r26
/* 8009C608 00097508  B3 E7 00 08 */	sth r31, 8(r7)
/* 8009C60C 0009750C  80 FD 00 04 */	lwz r7, 4(r29)
/* 8009C610 00097510  7F A7 D1 2E */	stwx r29, r7, r26
/* 8009C614 00097514  80 1D 00 04 */	lwz r0, 4(r29)
/* 8009C618 00097518  7C E0 D2 14 */	add r7, r0, r26
/* 8009C61C 0009751C  9B 87 00 0A */	stb r28, 0xa(r7)
/* 8009C620 00097520  48 00 00 2D */	bl setPriorityScnProc__Q23EGG8IScnProcFUsUcb
/* 8009C624 00097524  3B FF 00 01 */	addi r31, r31, 1
lbl_8009C628:
/* 8009C628 00097528  A0 1D 00 08 */	lhz r0, 8(r29)
/* 8009C62C 0009752C  57 E3 04 3E */	clrlwi r3, r31, 0x10
/* 8009C630 00097530  7C 03 00 40 */	cmplw r3, r0
/* 8009C634 00097534  41 80 FF 6C */	blt lbl_8009C5A0
/* 8009C638 00097538  BB 41 00 18 */	lmw r26, 0x18(r1)
/* 8009C63C 0009753C  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8009C640 00097540  7C 08 03 A6 */	mtlr r0
/* 8009C644 00097544  38 21 00 30 */	addi r1, r1, 0x30
/* 8009C648 00097548  4E 80 00 20 */	blr 

.global setPriorityScnProc__Q23EGG8IScnProcFUsUcb
setPriorityScnProc__Q23EGG8IScnProcFUsUcb:
/* 8009C64C 0009754C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8009C650 00097550  7C 08 02 A6 */	mflr r0
/* 8009C654 00097554  90 01 00 24 */	stw r0, 0x24(r1)
/* 8009C658 00097558  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8009C65C 0009755C  7C 9F 23 78 */	mr r31, r4
/* 8009C660 00097560  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8009C664 00097564  7C DE 33 78 */	mr r30, r6
/* 8009C668 00097568  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8009C66C 0009756C  7C BD 2B 78 */	mr r29, r5
/* 8009C670 00097570  93 81 00 10 */	stw r28, 0x10(r1)
/* 8009C674 00097574  7C 7C 1B 78 */	mr r28, r3
/* 8009C678 00097578  A0 03 00 08 */	lhz r0, 8(r3)
/* 8009C67C 0009757C  7C 04 00 40 */	cmplw r4, r0
/* 8009C680 00097580  41 80 00 1C */	blt lbl_8009C69C
/* 8009C684 00097584  3C 60 80 38 */	lis r3, lbl_80379DF0@ha
/* 8009C688 00097588  38 80 00 50 */	li r4, 0x50
/* 8009C68C 0009758C  38 63 9D F0 */	addi r3, r3, lbl_80379DF0@l
/* 8009C690 00097590  38 A3 00 40 */	addi r5, r3, 0x40
/* 8009C694 00097594  4C C6 31 82 */	crclr 6
/* 8009C698 00097598  48 00 58 71 */	bl system_halt
lbl_8009C69C:
/* 8009C69C 0009759C  A0 1C 00 08 */	lhz r0, 8(r28)
/* 8009C6A0 000975A0  7C 1F 00 40 */	cmplw r31, r0
/* 8009C6A4 000975A4  41 80 00 20 */	blt lbl_8009C6C4
/* 8009C6A8 000975A8  3C 60 80 39 */	lis r3, lbl_80397ECC@ha
/* 8009C6AC 000975AC  3C A0 80 39 */	lis r5, lbl_80397EB0@ha
/* 8009C6B0 000975B0  38 63 7E CC */	addi r3, r3, lbl_80397ECC@l
/* 8009C6B4 000975B4  38 80 00 56 */	li r4, 0x56
/* 8009C6B8 000975B8  38 A5 7E B0 */	addi r5, r5, lbl_80397EB0@l
/* 8009C6BC 000975BC  4C C6 31 82 */	crclr 6
/* 8009C6C0 000975C0  48 00 58 49 */	bl system_halt
lbl_8009C6C4:
/* 8009C6C4 000975C4  1F FF 00 0C */	mulli r31, r31, 0xc
/* 8009C6C8 000975C8  80 1C 00 04 */	lwz r0, 4(r28)
/* 8009C6CC 000975CC  2C 1E 00 00 */	cmpwi r30, 0
/* 8009C6D0 000975D0  7C 60 FA 14 */	add r3, r0, r31
/* 8009C6D4 000975D4  80 63 00 04 */	lwz r3, 4(r3)
/* 8009C6D8 000975D8  41 82 00 2C */	beq lbl_8009C704
/* 8009C6DC 000975DC  3C A0 80 0A */	lis r5, func_8009C908@ha
/* 8009C6E0 000975E0  7F A4 EB 78 */	mr r4, r29
/* 8009C6E4 000975E4  38 A5 C9 08 */	addi r5, r5, func_8009C908@l
/* 8009C6E8 000975E8  90 A3 00 EC */	stw r5, 0xec(r3)
/* 8009C6EC 000975EC  80 03 00 E8 */	lwz r0, 0xe8(r3)
/* 8009C6F0 000975F0  60 00 00 01 */	ori r0, r0, 1
/* 8009C6F4 000975F4  54 00 07 FA */	rlwinm r0, r0, 0, 0x1f, 0x1d
/* 8009C6F8 000975F8  90 03 00 E8 */	stw r0, 0xe8(r3)
/* 8009C6FC 000975FC  4B FD 39 0D */	bl func_80070008
/* 8009C700 00097600  48 00 00 28 */	b lbl_8009C728
lbl_8009C704:
/* 8009C704 00097604  3C A0 80 0A */	lis r5, func_8009C908@ha
/* 8009C708 00097608  7F A4 EB 78 */	mr r4, r29
/* 8009C70C 0009760C  38 A5 C9 08 */	addi r5, r5, func_8009C908@l
/* 8009C710 00097610  90 A3 00 EC */	stw r5, 0xec(r3)
/* 8009C714 00097614  80 03 00 E8 */	lwz r0, 0xe8(r3)
/* 8009C718 00097618  54 00 00 3C */	rlwinm r0, r0, 0, 0, 0x1e
/* 8009C71C 0009761C  60 00 00 02 */	ori r0, r0, 2
/* 8009C720 00097620  90 03 00 E8 */	stw r0, 0xe8(r3)
/* 8009C724 00097624  4B FD 39 09 */	bl func_8007002C
lbl_8009C728:
/* 8009C728 00097628  80 1C 00 04 */	lwz r0, 4(r28)
/* 8009C72C 0009762C  7C 60 FA 14 */	add r3, r0, r31
/* 8009C730 00097630  9B C3 00 0A */	stb r30, 0xa(r3)
/* 8009C734 00097634  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8009C738 00097638  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8009C73C 0009763C  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8009C740 00097640  83 81 00 10 */	lwz r28, 0x10(r1)
/* 8009C744 00097644  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8009C748 00097648  7C 08 03 A6 */	mtlr r0
/* 8009C74C 0009764C  38 21 00 20 */	addi r1, r1, 0x20
/* 8009C750 00097650  4E 80 00 20 */	blr 

.global pushBackToScnGroup__Q23EGG8IScnProcFPQ34nw4r3g3d8ScnGroup
pushBackToScnGroup__Q23EGG8IScnProcFPQ34nw4r3g3d8ScnGroup:
/* 8009C754 00097654  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8009C758 00097658  7C 08 02 A6 */	mflr r0
/* 8009C75C 0009765C  2C 04 00 00 */	cmpwi r4, 0
/* 8009C760 00097660  90 01 00 24 */	stw r0, 0x24(r1)
/* 8009C764 00097664  BF 41 00 08 */	stmw r26, 8(r1)
/* 8009C768 00097668  7C 7A 1B 78 */	mr r26, r3
/* 8009C76C 0009766C  7C 9B 23 78 */	mr r27, r4
/* 8009C770 00097670  40 82 00 1C */	bne lbl_8009C78C
/* 8009C774 00097674  3C 60 80 38 */	lis r3, lbl_80379DF0@ha
/* 8009C778 00097678  38 80 00 7D */	li r4, 0x7d
/* 8009C77C 0009767C  38 63 9D F0 */	addi r3, r3, lbl_80379DF0@l
/* 8009C780 00097680  38 A3 00 5C */	addi r5, r3, 0x5c
/* 8009C784 00097684  4C C6 31 82 */	crclr 6
/* 8009C788 00097688  48 00 57 81 */	bl system_halt
lbl_8009C78C:
/* 8009C78C 0009768C  3B 80 00 00 */	li r28, 0
/* 8009C790 00097690  3F A0 80 39 */	lis r29, 0x8039
/* 8009C794 00097694  3F C0 80 39 */	lis r30, 0x8039
/* 8009C798 00097698  3F E0 80 38 */	lis r31, 0x8038
/* 8009C79C 0009769C  48 00 00 70 */	b lbl_8009C80C
lbl_8009C7A0:
/* 8009C7A0 000976A0  57 80 04 3E */	clrlwi r0, r28, 0x10
/* 8009C7A4 000976A4  7C 00 18 40 */	cmplw r0, r3
/* 8009C7A8 000976A8  41 80 00 18 */	blt lbl_8009C7C0
/* 8009C7AC 000976AC  38 7D 7E CC */	addi r3, r29, 0x7ecc
/* 8009C7B0 000976B0  38 BE 7E B0 */	addi r5, r30, 0x7eb0
/* 8009C7B4 000976B4  38 80 00 56 */	li r4, 0x56
/* 8009C7B8 000976B8  4C C6 31 82 */	crclr 6
/* 8009C7BC 000976BC  48 00 57 4D */	bl system_halt
lbl_8009C7C0:
/* 8009C7C0 000976C0  57 80 04 3E */	clrlwi r0, r28, 0x10
/* 8009C7C4 000976C4  81 9B 00 00 */	lwz r12, 0(r27)
/* 8009C7C8 000976C8  1C 00 00 0C */	mulli r0, r0, 0xc
/* 8009C7CC 000976CC  80 9A 00 04 */	lwz r4, 4(r26)
/* 8009C7D0 000976D0  81 8C 00 34 */	lwz r12, 0x34(r12)
/* 8009C7D4 000976D4  7F 63 DB 78 */	mr r3, r27
/* 8009C7D8 000976D8  7C A4 02 14 */	add r5, r4, r0
/* 8009C7DC 000976DC  80 9B 00 E4 */	lwz r4, 0xe4(r27)
/* 8009C7E0 000976E0  80 A5 00 04 */	lwz r5, 4(r5)
/* 8009C7E4 000976E4  7D 89 03 A6 */	mtctr r12
/* 8009C7E8 000976E8  4E 80 04 21 */	bctrl 
/* 8009C7EC 000976EC  2C 03 00 00 */	cmpwi r3, 0
/* 8009C7F0 000976F0  40 82 00 18 */	bne lbl_8009C808
/* 8009C7F4 000976F4  38 7F 9D F0 */	addi r3, r31, -25104
/* 8009C7F8 000976F8  38 80 00 81 */	li r4, 0x81
/* 8009C7FC 000976FC  38 A3 00 66 */	addi r5, r3, 0x66
/* 8009C800 00097700  4C C6 31 82 */	crclr 6
/* 8009C804 00097704  48 00 57 05 */	bl system_halt
lbl_8009C808:
/* 8009C808 00097708  3B 9C 00 01 */	addi r28, r28, 1
lbl_8009C80C:
/* 8009C80C 0009770C  A0 7A 00 08 */	lhz r3, 8(r26)
/* 8009C810 00097710  57 80 04 3E */	clrlwi r0, r28, 0x10
/* 8009C814 00097714  7C 00 18 40 */	cmplw r0, r3
/* 8009C818 00097718  41 80 FF 88 */	blt lbl_8009C7A0
/* 8009C81C 0009771C  BB 41 00 08 */	lmw r26, 8(r1)
/* 8009C820 00097720  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8009C824 00097724  7C 08 03 A6 */	mtlr r0
/* 8009C828 00097728  38 21 00 20 */	addi r1, r1, 0x20
/* 8009C82C 0009772C  4E 80 00 20 */	blr 

.global removeFromScnGroup__Q23EGG8IScnProcFPQ34nw4r3g3d8ScnGroup
removeFromScnGroup__Q23EGG8IScnProcFPQ34nw4r3g3d8ScnGroup:
/* 8009C830 00097730  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8009C834 00097734  7C 08 02 A6 */	mflr r0
/* 8009C838 00097738  2C 04 00 00 */	cmpwi r4, 0
/* 8009C83C 0009773C  90 01 00 24 */	stw r0, 0x24(r1)
/* 8009C840 00097740  BF 41 00 08 */	stmw r26, 8(r1)
/* 8009C844 00097744  7C 7A 1B 78 */	mr r26, r3
/* 8009C848 00097748  7C 9B 23 78 */	mr r27, r4
/* 8009C84C 0009774C  40 82 00 1C */	bne lbl_8009C868
/* 8009C850 00097750  3C 60 80 38 */	lis r3, lbl_80379DF0@ha
/* 8009C854 00097754  38 80 00 8C */	li r4, 0x8c
/* 8009C858 00097758  38 63 9D F0 */	addi r3, r3, lbl_80379DF0@l
/* 8009C85C 0009775C  38 A3 00 5C */	addi r5, r3, 0x5c
/* 8009C860 00097760  4C C6 31 82 */	crclr 6
/* 8009C864 00097764  48 00 56 A5 */	bl system_halt
lbl_8009C868:
/* 8009C868 00097768  3B 80 00 00 */	li r28, 0
/* 8009C86C 0009776C  3F A0 80 39 */	lis r29, 0x8039
/* 8009C870 00097770  3F C0 80 39 */	lis r30, 0x8039
/* 8009C874 00097774  3F E0 80 38 */	lis r31, 0x8038
/* 8009C878 00097778  48 00 00 6C */	b lbl_8009C8E4
lbl_8009C87C:
/* 8009C87C 0009777C  57 80 04 3E */	clrlwi r0, r28, 0x10
/* 8009C880 00097780  7C 00 18 40 */	cmplw r0, r3
/* 8009C884 00097784  41 80 00 18 */	blt lbl_8009C89C
/* 8009C888 00097788  38 7D 7E CC */	addi r3, r29, 0x7ecc
/* 8009C88C 0009778C  38 BE 7E B0 */	addi r5, r30, 0x7eb0
/* 8009C890 00097790  38 80 00 56 */	li r4, 0x56
/* 8009C894 00097794  4C C6 31 82 */	crclr 6
/* 8009C898 00097798  48 00 56 71 */	bl system_halt
lbl_8009C89C:
/* 8009C89C 0009779C  57 80 04 3E */	clrlwi r0, r28, 0x10
/* 8009C8A0 000977A0  81 9B 00 00 */	lwz r12, 0(r27)
/* 8009C8A4 000977A4  1C 00 00 0C */	mulli r0, r0, 0xc
/* 8009C8A8 000977A8  80 9A 00 04 */	lwz r4, 4(r26)
/* 8009C8AC 000977AC  81 8C 00 3C */	lwz r12, 0x3c(r12)
/* 8009C8B0 000977B0  7F 63 DB 78 */	mr r3, r27
/* 8009C8B4 000977B4  7C 84 02 14 */	add r4, r4, r0
/* 8009C8B8 000977B8  80 84 00 04 */	lwz r4, 4(r4)
/* 8009C8BC 000977BC  7D 89 03 A6 */	mtctr r12
/* 8009C8C0 000977C0  4E 80 04 21 */	bctrl 
/* 8009C8C4 000977C4  2C 03 00 00 */	cmpwi r3, 0
/* 8009C8C8 000977C8  40 82 00 18 */	bne lbl_8009C8E0
/* 8009C8CC 000977CC  38 7F 9D F0 */	addi r3, r31, -25104
/* 8009C8D0 000977D0  38 80 00 90 */	li r4, 0x90
/* 8009C8D4 000977D4  38 A3 00 73 */	addi r5, r3, 0x73
/* 8009C8D8 000977D8  4C C6 31 82 */	crclr 6
/* 8009C8DC 000977DC  48 00 56 2D */	bl system_halt
lbl_8009C8E0:
/* 8009C8E0 000977E0  3B 9C 00 01 */	addi r28, r28, 1
lbl_8009C8E4:
/* 8009C8E4 000977E4  A0 7A 00 08 */	lhz r3, 8(r26)
/* 8009C8E8 000977E8  57 80 04 3E */	clrlwi r0, r28, 0x10
/* 8009C8EC 000977EC  7C 00 18 40 */	cmplw r0, r3
/* 8009C8F0 000977F0  41 80 FF 8C */	blt lbl_8009C87C
/* 8009C8F4 000977F4  BB 41 00 08 */	lmw r26, 8(r1)
/* 8009C8F8 000977F8  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8009C8FC 000977FC  7C 08 03 A6 */	mtlr r0
/* 8009C900 00097800  38 21 00 20 */	addi r1, r1, 0x20
/* 8009C904 00097804  4E 80 00 20 */	blr 

# Either       drawProcFunc__Q23EGG8IScnProcFPQ34nw4r3g3d8ScnGroupb or
# drawProcFuncNoGlobalState__Q23EGG8IScnProcFPQ34nw4r3g3d8ScnGroupb
# Need to look into GXUtility to see what this function does exactly
.global func_8009C908
func_8009C908:
/* 8009C908 00097808  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8009C90C 0009780C  7C 08 02 A6 */	mflr r0
/* 8009C910 00097810  2C 03 00 00 */	cmpwi r3, 0
/* 8009C914 00097814  90 01 00 14 */	stw r0, 0x14(r1)
/* 8009C918 00097818  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8009C91C 0009781C  7C 7F 1B 78 */	mr r31, r3
/* 8009C920 00097820  93 C1 00 08 */	stw r30, 8(r1)
/* 8009C924 00097824  7C 9E 23 78 */	mr r30, r4
/* 8009C928 00097828  40 82 00 1C */	bne lbl_8009C944
/* 8009C92C 0009782C  3C 60 80 38 */	lis r3, lbl_80379DF0@ha
/* 8009C930 00097830  38 80 00 B8 */	li r4, 0xb8
/* 8009C934 00097834  38 63 9D F0 */	addi r3, r3, lbl_80379DF0@l
/* 8009C938 00097838  38 A3 00 7F */	addi r5, r3, 0x7f
/* 8009C93C 0009783C  4C C6 31 82 */	crclr 6
/* 8009C940 00097840  48 00 55 C9 */	bl system_halt
lbl_8009C944:
/* 8009C944 00097844  83 FF 00 F0 */	lwz r31, 0xf0(r31)
/* 8009C948 00097848  2C 1F 00 00 */	cmpwi r31, 0
/* 8009C94C 0009784C  40 82 00 1C */	bne lbl_8009C968
/* 8009C950 00097850  3C 60 80 38 */	lis r3, lbl_80379DF0@ha
/* 8009C954 00097854  38 80 00 BA */	li r4, 0xba
/* 8009C958 00097858  38 63 9D F0 */	addi r3, r3, lbl_80379DF0@l
/* 8009C95C 0009785C  38 A3 00 88 */	addi r5, r3, 0x88
/* 8009C960 00097860  4C C6 31 82 */	crclr 6
/* 8009C964 00097864  48 00 55 A5 */	bl system_halt
lbl_8009C968:
/* 8009C968 00097868  80 1F 00 00 */	lwz r0, 0(r31)
/* 8009C96C 0009786C  2C 00 00 00 */	cmpwi r0, 0
/* 8009C970 00097870  40 82 00 1C */	bne lbl_8009C98C
/* 8009C974 00097874  3C 60 80 38 */	lis r3, lbl_80379DF0@ha
/* 8009C978 00097878  38 80 00 BB */	li r4, 0xbb
/* 8009C97C 0009787C  38 63 9D F0 */	addi r3, r3, lbl_80379DF0@l
/* 8009C980 00097880  38 A3 00 8F */	addi r5, r3, 0x8f
/* 8009C984 00097884  4C C6 31 82 */	crclr 6
/* 8009C988 00097888  48 00 55 81 */	bl system_halt
lbl_8009C98C:
/* 8009C98C 0009788C  7F C3 F3 78 */	mr r3, r30
/* 8009C990 00097890  48 00 51 F9 */	bl func_800A1B88
/* 8009C994 00097894  80 7F 00 00 */	lwz r3, 0(r31)
/* 8009C998 00097898  A0 9F 00 08 */	lhz r4, 8(r31)
/* 8009C99C 0009789C  81 83 00 00 */	lwz r12, 0(r3)
/* 8009C9A0 000978A0  81 8C 00 0C */	lwz r12, 0xc(r12)
/* 8009C9A4 000978A4  7D 89 03 A6 */	mtctr r12
/* 8009C9A8 000978A8  4E 80 04 21 */	bctrl 
/* 8009C9AC 000978AC  4B FE 7B 9D */	bl func_80084548
/* 8009C9B0 000978B0  7F C3 F3 78 */	mr r3, r30
/* 8009C9B4 000978B4  48 00 51 D5 */	bl func_800A1B88
/* 8009C9B8 000978B8  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8009C9BC 000978BC  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8009C9C0 000978C0  83 C1 00 08 */	lwz r30, 8(r1)
/* 8009C9C4 000978C4  7C 08 03 A6 */	mtlr r0
/* 8009C9C8 000978C8  38 21 00 10 */	addi r1, r1, 0x10
/* 8009C9CC 000978CC  4E 80 00 20 */	blr 
