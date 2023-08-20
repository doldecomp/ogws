.include "macros.inc"

.section .ctors, "a"
.4byte "__sinit_\RPSysScene_cpp"

.section .sbss, "wa"
.balign 0x8
.global sDebugHeap__10RPSysScene
sDebugHeap__10RPSysScene:
	.skip 0x4

.section .data, "wa"
.balign 0x8
.global __vt__10RPSysScene
__vt__10RPSysScene:
    # inherited from EGG::Scene
    .long 0
    .long 0
    .long __dt__10RPSysSceneFv
    .long calc__10RPSysSceneFv
    .long draw__10RPSysSceneFv
    .long enter__10RPSysSceneFv
    .long exit__10RPSysSceneFv
    .long reinit__10RPSysSceneFv
    .long incoming_childDestroy__10RPSysSceneFv
    .long outgoing_childCreate__10RPSysSceneFv
    # inherited from IRPGrpDrawObject
    .long 0
    .long 0
    .long "@36@__dt__10RPSysSceneFv"
    .long UserDraw__16IRPGrpDrawObjectFv
    .long DebugDraw__16IRPGrpDrawObjectFv
    # unique to this class
    .long getDebugSceneHeap__10RPSysSceneFv
    .long pauseCallBack__10RPSysSceneFb
    .long Configure__10RPSysSceneFv
    .long LoadResource__10RPSysSceneFv
    .long Reset__10RPSysSceneFv
    .long Calculate__10RPSysSceneFv
    .long Exit__10RPSysSceneFv
    .long taskAsync__10RPSysSceneFv

.section .text, "ax"
.global disableMgrFadeIn__10RPSysSceneFv
disableMgrFadeIn__10RPSysSceneFv:
/* 80184E80 0017FD80  80 03 00 3C */	lwz r0, 0x3c(r3)
/* 80184E84 0017FD84  60 00 00 08 */	ori r0, r0, 8
/* 80184E88 0017FD88  90 03 00 3C */	stw r0, 0x3c(r3)
/* 80184E8C 0017FD8C  4E 80 00 20 */	blr 

.global getCreatorSceneID__10RPSysSceneCFv
getCreatorSceneID__10RPSysSceneCFv:
/* 80184E90 0017FD90  80 63 00 40 */	lwz r3, 0x40(r3)
/* 80184E94 0017FD94  4E 80 00 20 */	blr 

.global setCreatorSceneID__10RPSysSceneFl
setCreatorSceneID__10RPSysSceneFl:
/* 80184E98 0017FD98  90 83 00 40 */	stw r4, 0x40(r3)
/* 80184E9C 0017FD9C  4E 80 00 20 */	blr 

.global construct__10RPSysSceneFv
construct__10RPSysSceneFv:
/* 80184EA0 0017FDA0  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80184EA4 0017FDA4  7C 08 02 A6 */	mflr r0
/* 80184EA8 0017FDA8  90 01 00 14 */	stw r0, 0x14(r1)
/* 80184EAC 0017FDAC  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80184EB0 0017FDB0  7C 7F 1B 78 */	mr r31, r3
/* 80184EB4 0017FDB4  38 60 00 14 */	li r3, 0x14
/* 80184EB8 0017FDB8  4B F1 E3 8D */	bl __nw__FUl
/* 80184EBC 0017FDBC  2C 03 00 00 */	cmpwi r3, 0
/* 80184EC0 0017FDC0  41 82 00 10 */	beq lbl_80184ED0
/* 80184EC4 0017FDC4  80 9F 00 04 */	lwz r4, 4(r31)
/* 80184EC8 0017FDC8  38 A0 00 20 */	li r5, 0x20
/* 80184ECC 0017FDCC  4B F1 E5 51 */	bl __ct__Q23EGG9AllocatorFPQ23EGG4Heapl
lbl_80184ED0:
/* 80184ED0 0017FDD0  80 1F 00 1C */	lwz r0, 0x1c(r31)
/* 80184ED4 0017FDD4  54 04 04 3E */	clrlwi r4, r0, 0x10
/* 80184ED8 0017FDD8  48 02 AE A9 */	bl func_801AFD80
/* 80184EDC 0017FDDC  90 7F 00 2C */	stw r3, 0x2c(r31)
/* 80184EE0 0017FDE0  48 02 AE 69 */	bl func_801AFD48
/* 80184EE4 0017FDE4  80 6D A2 90 */	lwz r3, lbl_804BF610-_SDA_BASE_(r13)
/* 80184EE8 0017FDE8  38 9F 00 24 */	addi r4, r31, 0x24
/* 80184EEC 0017FDEC  48 02 A5 45 */	bl func_801AF430
/* 80184EF0 0017FDF0  38 60 00 08 */	li r3, 8
/* 80184EF4 0017FDF4  4B F1 E3 51 */	bl __nw__FUl
/* 80184EF8 0017FDF8  2C 03 00 00 */	cmpwi r3, 0
/* 80184EFC 0017FDFC  41 82 00 08 */	beq lbl_80184F04
/* 80184F00 0017FE00  48 00 2E BD */	bl __ct__17RPSysCommonObjectFv
lbl_80184F04:
/* 80184F04 0017FE04  90 7F 00 30 */	stw r3, 0x30(r31)
/* 80184F08 0017FE08  38 60 00 44 */	li r3, 0x44
/* 80184F0C 0017FE0C  4B F1 E3 39 */	bl __nw__FUl
/* 80184F10 0017FE10  2C 03 00 00 */	cmpwi r3, 0
/* 80184F14 0017FE14  41 82 00 0C */	beq lbl_80184F20
/* 80184F18 0017FE18  38 80 00 00 */	li r4, 0
/* 80184F1C 0017FE1C  48 01 39 BD */	bl func_801988D8
lbl_80184F20:
/* 80184F20 0017FE20  90 7F 00 34 */	stw r3, 0x34(r31)
/* 80184F24 0017FE24  80 6D A1 C0 */	lwz r3, lbl_804BF540-_SDA_BASE_(r13)
/* 80184F28 0017FE28  48 00 D4 21 */	bl func_80192348
/* 80184F2C 0017FE2C  80 6D A1 48 */	lwz r3, sInstance__17RPSysSceneCreator-_SDA_BASE_(r13)
/* 80184F30 0017FE30  80 9F 00 1C */	lwz r4, 0x1c(r31)
/* 80184F34 0017FE34  4B FF F5 89 */	bl isCommonSnd__17RPSysSceneCreatorFl
/* 80184F38 0017FE38  2C 03 00 01 */	cmpwi r3, 1
/* 80184F3C 0017FE3C  40 82 00 0C */	bne lbl_80184F48
/* 80184F40 0017FE40  80 6D A2 C4 */	lwz r3, lbl_804BF644-_SDA_BASE_(r13)
/* 80184F44 0017FE44  48 03 25 F1 */	bl func_801B7534
lbl_80184F48:
/* 80184F48 0017FE48  80 6D A1 48 */	lwz r3, sInstance__17RPSysSceneCreator-_SDA_BASE_(r13)
/* 80184F4C 0017FE4C  80 9F 00 1C */	lwz r4, 0x1c(r31)
/* 80184F50 0017FE50  4B FF F6 09 */	bl getExitType__17RPSysSceneCreatorFl
/* 80184F54 0017FE54  2C 03 00 00 */	cmpwi r3, 0
/* 80184F58 0017FE58  40 82 00 10 */	bne lbl_80184F68
/* 80184F5C 0017FE5C  80 6D A1 A0 */	lwz r3, lbl_804BF520-_SDA_BASE_(r13)
/* 80184F60 0017FE60  48 00 8B 75 */	bl func_8018DAD4
/* 80184F64 0017FE64  48 00 00 18 */	b lbl_80184F7C
lbl_80184F68:
/* 80184F68 0017FE68  38 03 FF FF */	addi r0, r3, -1
/* 80184F6C 0017FE6C  28 00 00 01 */	cmplwi r0, 1
/* 80184F70 0017FE70  41 81 00 0C */	bgt lbl_80184F7C
/* 80184F74 0017FE74  80 6D A1 A0 */	lwz r3, lbl_804BF520-_SDA_BASE_(r13)
/* 80184F78 0017FE78  48 00 94 91 */	bl func_8018E408
lbl_80184F7C:
/* 80184F7C 0017FE7C  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80184F80 0017FE80  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80184F84 0017FE84  7C 08 03 A6 */	mtlr r0
/* 80184F88 0017FE88  38 21 00 10 */	addi r1, r1, 0x10
/* 80184F8C 0017FE8C  4E 80 00 20 */	blr 

.global exit__10RPSysSceneFv
exit__10RPSysSceneFv:
/* 80184F90 0017FE90  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80184F94 0017FE94  7C 08 02 A6 */	mflr r0
/* 80184F98 0017FE98  90 01 00 14 */	stw r0, 0x14(r1)
/* 80184F9C 0017FE9C  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80184FA0 0017FEA0  7C 7F 1B 78 */	mr r31, r3
/* 80184FA4 0017FEA4  48 01 68 39 */	bl func_8019B7DC
/* 80184FA8 0017FEA8  80 6D A1 C8 */	lwz r3, lbl_804BF548-_SDA_BASE_(r13)
/* 80184FAC 0017FEAC  48 00 E6 55 */	bl func_80193600
/* 80184FB0 0017FEB0  80 6D A1 C8 */	lwz r3, lbl_804BF548-_SDA_BASE_(r13)
/* 80184FB4 0017FEB4  80 9F 00 34 */	lwz r4, 0x34(r31)
/* 80184FB8 0017FEB8  48 00 E6 E5 */	bl func_8019369C
/* 80184FBC 0017FEBC  81 9F 00 00 */	lwz r12, 0(r31)
/* 80184FC0 0017FEC0  7F E3 FB 78 */	mr r3, r31
/* 80184FC4 0017FEC4  81 8C 00 54 */	lwz r12, 0x54(r12)
/* 80184FC8 0017FEC8  7D 89 03 A6 */	mtctr r12
/* 80184FCC 0017FECC  4E 80 04 21 */	bctrl 
/* 80184FD0 0017FED0  4B F5 94 C5 */	bl GXDrawDone
/* 80184FD4 0017FED4  80 7F 00 2C */	lwz r3, 0x2c(r31)
/* 80184FD8 0017FED8  48 02 AD A1 */	bl func_801AFD78
/* 80184FDC 0017FEDC  80 9F 00 38 */	lwz r4, 0x38(r31)
/* 80184FE0 0017FEE0  2C 04 00 00 */	cmpwi r4, 0
/* 80184FE4 0017FEE4  41 82 00 0C */	beq lbl_80184FF0
/* 80184FE8 0017FEE8  80 6D A1 38 */	lwz r3, sInstance__11RPSysSystem-_SDA_BASE_(r13)
/* 80184FEC 0017FEEC  4B FF E5 2D */	bl destroyHeap__11RPSysSystemFPQ23EGG4Heap
lbl_80184FF0:
/* 80184FF0 0017FEF0  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80184FF4 0017FEF4  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80184FF8 0017FEF8  7C 08 03 A6 */	mtlr r0
/* 80184FFC 0017FEFC  38 21 00 10 */	addi r1, r1, 0x10
/* 80185000 0017FF00  4E 80 00 20 */	blr 

# Weak function in WFU
.global Exit__10RPSysSceneFv
Exit__10RPSysSceneFv:
/* 80185004 0017FF04  4E 80 00 20 */	blr 

.global outgoing_childCreate__10RPSysSceneFv
outgoing_childCreate__10RPSysSceneFv:
/* 80185008 0017FF08  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8018500C 0017FF0C  7C 08 02 A6 */	mflr r0
/* 80185010 0017FF10  90 01 00 14 */	stw r0, 0x14(r1)
/* 80185014 0017FF14  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80185018 0017FF18  7C 7F 1B 78 */	mr r31, r3
/* 8018501C 0017FF1C  48 01 67 C1 */	bl func_8019B7DC
/* 80185020 0017FF20  80 6D A1 C8 */	lwz r3, lbl_804BF548-_SDA_BASE_(r13)
/* 80185024 0017FF24  48 00 E5 DD */	bl func_80193600
/* 80185028 0017FF28  80 6D A1 C8 */	lwz r3, lbl_804BF548-_SDA_BASE_(r13)
/* 8018502C 0017FF2C  80 9F 00 34 */	lwz r4, 0x34(r31)
/* 80185030 0017FF30  48 00 E6 6D */	bl func_8019369C
/* 80185034 0017FF34  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80185038 0017FF38  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8018503C 0017FF3C  7C 08 03 A6 */	mtlr r0
/* 80185040 0017FF40  38 21 00 10 */	addi r1, r1, 0x10
/* 80185044 0017FF44  4E 80 00 20 */	blr 

.global draw__10RPSysSceneFv
draw__10RPSysSceneFv:
/* 80185048 0017FF48  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8018504C 0017FF4C  7C 08 02 A6 */	mflr r0
/* 80185050 0017FF50  90 01 00 14 */	stw r0, 0x14(r1)
/* 80185054 0017FF54  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80185058 0017FF58  7C 7F 1B 78 */	mr r31, r3
/* 8018505C 0017FF5C  80 6D A1 C0 */	lwz r3, lbl_804BF540-_SDA_BASE_(r13)
/* 80185060 0017FF60  48 00 C4 61 */	bl func_801914C0
/* 80185064 0017FF64  48 02 AF 09 */	bl func_801AFF6C
/* 80185068 0017FF68  80 7F 00 2C */	lwz r3, 0x2c(r31)
/* 8018506C 0017FF6C  48 02 A7 8D */	bl func_801AF7F8
/* 80185070 0017FF70  48 02 AE 7D */	bl func_801AFEEC
/* 80185074 0017FF74  80 6D A1 B0 */	lwz r3, lbl_804BF530-_SDA_BASE_(r13)
/* 80185078 0017FF78  48 00 B8 4D */	bl func_801908C4
/* 8018507C 0017FF7C  48 02 AE 65 */	bl func_801AFEE0
/* 80185080 0017FF80  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80185084 0017FF84  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80185088 0017FF88  7C 08 03 A6 */	mtlr r0
/* 8018508C 0017FF8C  38 21 00 10 */	addi r1, r1, 0x10
/* 80185090 0017FF90  4E 80 00 20 */	blr 

.global calc__10RPSysSceneFv
calc__10RPSysSceneFv:
/* 80185094 0017FF94  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80185098 0017FF98  7C 08 02 A6 */	mflr r0
/* 8018509C 0017FF9C  90 01 00 14 */	stw r0, 0x14(r1)
/* 801850A0 0017FFA0  93 E1 00 0C */	stw r31, 0xc(r1)
/* 801850A4 0017FFA4  7C 7F 1B 78 */	mr r31, r3
/* 801850A8 0017FFA8  80 6D A1 80 */	lwz r3, sInstance__14RPSysDvdStatus-_SDA_BASE_(r13)
/* 801850AC 0017FFAC  48 00 31 B5 */	bl isErrorOccurred__14RPSysDvdStatusFv
/* 801850B0 0017FFB0  2C 03 00 00 */	cmpwi r3, 0
/* 801850B4 0017FFB4  40 82 00 8C */	bne lbl_80185140
/* 801850B8 0017FFB8  80 7F 00 30 */	lwz r3, 0x30(r31)
/* 801850BC 0017FFBC  48 00 2C 59 */	bl preUpdate__17RPSysCommonObjectFv
/* 801850C0 0017FFC0  7F E3 FB 78 */	mr r3, r31
/* 801850C4 0017FFC4  48 00 1C 69 */	bl STUB_80186D2C__10RPSysSceneFv
/* 801850C8 0017FFC8  80 6D A1 58 */	lwz r3, sInstance__13RPSysSceneMgr-_SDA_BASE_(r13)
/* 801850CC 0017FFCC  48 00 0E 99 */	bl isNormalState__13RPSysSceneMgrCFv
/* 801850D0 0017FFD0  2C 03 00 00 */	cmpwi r3, 0
/* 801850D4 0017FFD4  41 82 00 4C */	beq lbl_80185120
/* 801850D8 0017FFD8  80 6D A2 28 */	lwz r3, lbl_804BF5A8-_SDA_BASE_(r13)
/* 801850DC 0017FFDC  88 03 00 0B */	lbz r0, 0xb(r3)
/* 801850E0 0017FFE0  2C 00 00 00 */	cmpwi r0, 0
/* 801850E4 0017FFE4  40 82 00 3C */	bne lbl_80185120
/* 801850E8 0017FFE8  80 6D A1 98 */	lwz r3, lbl_804BF518-_SDA_BASE_(r13)
/* 801850EC 0017FFEC  80 03 00 08 */	lwz r0, 8(r3)
/* 801850F0 0017FFF0  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 801850F4 0017FFF4  40 82 00 2C */	bne lbl_80185120
/* 801850F8 0017FFF8  80 7F 00 2C */	lwz r3, 0x2c(r31)
/* 801850FC 0017FFFC  48 02 A6 F5 */	bl func_801AF7F0
/* 80185100 00180000  81 9F 00 00 */	lwz r12, 0(r31)
/* 80185104 00180004  7F E3 FB 78 */	mr r3, r31
/* 80185108 00180008  81 8C 00 50 */	lwz r12, 0x50(r12)
/* 8018510C 0018000C  7D 89 03 A6 */	mtctr r12
/* 80185110 00180010  4E 80 04 21 */	bctrl 
/* 80185114 00180014  80 7F 00 2C */	lwz r3, 0x2c(r31)
/* 80185118 00180018  48 02 A6 55 */	bl func_801AF76C
/* 8018511C 0018001C  48 00 00 0C */	b lbl_80185128
lbl_80185120:
/* 80185120 00180020  80 7F 00 2C */	lwz r3, 0x2c(r31)
/* 80185124 00180024  48 02 A5 F1 */	bl func_801AF714
lbl_80185128:
/* 80185128 00180028  80 6D A1 B0 */	lwz r3, lbl_804BF530-_SDA_BASE_(r13)
/* 8018512C 0018002C  48 00 B7 9D */	bl func_801908C8
/* 80185130 00180030  80 6D A1 A8 */	lwz r3, lbl_804BF528-_SDA_BASE_(r13)
/* 80185134 00180034  48 00 B7 0D */	bl func_80190840
/* 80185138 00180038  80 7F 00 30 */	lwz r3, 0x30(r31)
/* 8018513C 0018003C  48 00 2B 51 */	bl postUpdate__17RPSysCommonObjectFv
lbl_80185140:
/* 80185140 00180040  7F E3 FB 78 */	mr r3, r31
/* 80185144 00180044  48 00 18 D9 */	bl updateDvdEndMessage__10RPSysSceneFv
/* 80185148 00180048  7F E3 FB 78 */	mr r3, r31
/* 8018514C 0018004C  48 00 18 15 */	bl updateNandEndMessage__10RPSysSceneFv
/* 80185150 00180050  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80185154 00180054  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80185158 00180058  7C 08 03 A6 */	mtlr r0
/* 8018515C 0018005C  38 21 00 10 */	addi r1, r1, 0x10
/* 80185160 00180060  4E 80 00 20 */	blr 

# Weak function in WFU
.global Calculate__10RPSysSceneFv
Calculate__10RPSysSceneFv:
/* 80185164 00180064  4E 80 00 20 */	blr 

.global incoming_childDestroy__10RPSysSceneFv
incoming_childDestroy__10RPSysSceneFv:
/* 80185168 00180068  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8018516C 0018006C  7C 08 02 A6 */	mflr r0
/* 80185170 00180070  90 01 00 14 */	stw r0, 0x14(r1)
/* 80185174 00180074  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80185178 00180078  7C 7F 1B 78 */	mr r31, r3
/* 8018517C 0018007C  48 01 6D 05 */	bl func_8019BE80
/* 80185180 00180080  80 6D A1 B8 */	lwz r3, lbl_804BF538-_SDA_BASE_(r13)
/* 80185184 00180084  48 00 BA 19 */	bl func_80190B9C
/* 80185188 00180088  80 1F 00 3C */	lwz r0, 0x3c(r31)
/* 8018518C 0018008C  54 00 07 39 */	rlwinm. r0, r0, 0, 0x1c, 0x1c
/* 80185190 00180090  40 82 00 0C */	bne lbl_8018519C
/* 80185194 00180094  7F E3 FB 78 */	mr r3, r31
/* 80185198 00180098  48 00 19 11 */	bl initTaskAsync__10RPSysSceneFv
lbl_8018519C:
/* 8018519C 0018009C  80 7F 00 2C */	lwz r3, 0x2c(r31)
/* 801851A0 001800A0  48 02 AB A9 */	bl func_801AFD48
/* 801851A4 001800A4  80 7F 00 30 */	lwz r3, 0x30(r31)
/* 801851A8 001800A8  48 00 2B D1 */	bl init__17RPSysCommonObjectFv
/* 801851AC 001800AC  80 6D A1 58 */	lwz r3, sInstance__13RPSysSceneMgr-_SDA_BASE_(r13)
/* 801851B0 001800B0  48 00 0A DD */	bl resetFadeColor__13RPSysSceneMgrFv
/* 801851B4 001800B4  80 6D A1 58 */	lwz r3, sInstance__13RPSysSceneMgr-_SDA_BASE_(r13)
/* 801851B8 001800B8  48 00 0B 7D */	bl resetFadeFrame__13RPSysSceneMgrFv
/* 801851BC 001800BC  80 6D A1 58 */	lwz r3, sInstance__13RPSysSceneMgr-_SDA_BASE_(r13)
/* 801851C0 001800C0  38 80 00 01 */	li r4, 1
/* 801851C4 001800C4  48 00 09 A1 */	bl setSceneStatus__13RPSysSceneMgrFQ33EGG5Fader7EStatus
/* 801851C8 001800C8  80 6D A1 58 */	lwz r3, sInstance__13RPSysSceneMgr-_SDA_BASE_(r13)
/* 801851CC 001800CC  48 00 0D 6D */	bl resetGuard__13RPSysSceneMgrFv
/* 801851D0 001800D0  80 6D A1 38 */	lwz r3, sInstance__11RPSysSystem-_SDA_BASE_(r13)
/* 801851D4 001800D4  38 80 00 01 */	li r4, 1
/* 801851D8 001800D8  4B FF E0 11 */	bl setDimming__11RPSysSystemFi
/* 801851DC 001800DC  80 6D A1 C8 */	lwz r3, lbl_804BF548-_SDA_BASE_(r13)
/* 801851E0 001800E0  38 A0 00 00 */	li r5, 0
/* 801851E4 001800E4  80 9F 00 34 */	lwz r4, 0x34(r31)
/* 801851E8 001800E8  48 00 E4 FD */	bl func_801936E4
/* 801851EC 001800EC  81 9F 00 00 */	lwz r12, 0(r31)
/* 801851F0 001800F0  7F E3 FB 78 */	mr r3, r31
/* 801851F4 001800F4  81 8C 00 4C */	lwz r12, 0x4c(r12)
/* 801851F8 001800F8  7D 89 03 A6 */	mtctr r12
/* 801851FC 001800FC  4E 80 04 21 */	bctrl 
/* 80185200 00180100  80 1F 00 3C */	lwz r0, 0x3c(r31)
/* 80185204 00180104  54 00 07 39 */	rlwinm. r0, r0, 0, 0x1c, 0x1c
/* 80185208 00180108  40 82 00 0C */	bne lbl_80185214
/* 8018520C 0018010C  80 6D A1 58 */	lwz r3, sInstance__13RPSysSceneMgr-_SDA_BASE_(r13)
/* 80185210 00180110  48 00 09 51 */	bl startMgrFadeIn__13RPSysSceneMgrFv
lbl_80185214:
/* 80185214 00180114  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80185218 00180118  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8018521C 0018011C  7C 08 03 A6 */	mtlr r0
/* 80185220 00180120  38 21 00 10 */	addi r1, r1, 0x10
/* 80185224 00180124  4E 80 00 20 */	blr 

# Weak function in WFU
.global Reset__10RPSysSceneFv
Reset__10RPSysSceneFv:
/* 80185228 00180128  4E 80 00 20 */	blr 

.global reinit__10RPSysSceneFv
reinit__10RPSysSceneFv:
/* 8018522C 0018012C  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80185230 00180130  7C 08 02 A6 */	mflr r0
/* 80185234 00180134  90 01 00 14 */	stw r0, 0x14(r1)
/* 80185238 00180138  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8018523C 0018013C  7C 7F 1B 78 */	mr r31, r3
/* 80185240 00180140  48 01 65 9D */	bl func_8019B7DC
/* 80185244 00180144  80 6D A1 C8 */	lwz r3, lbl_804BF548-_SDA_BASE_(r13)
/* 80185248 00180148  48 00 E3 B9 */	bl func_80193600
/* 8018524C 0018014C  80 6D A1 C8 */	lwz r3, lbl_804BF548-_SDA_BASE_(r13)
/* 80185250 00180150  80 9F 00 34 */	lwz r4, 0x34(r31)
/* 80185254 00180154  48 00 E4 49 */	bl func_8019369C
/* 80185258 00180158  48 01 6C 29 */	bl func_8019BE80
/* 8018525C 0018015C  80 6D A1 B8 */	lwz r3, lbl_804BF538-_SDA_BASE_(r13)
/* 80185260 00180160  48 00 B9 3D */	bl func_80190B9C
/* 80185264 00180164  80 1F 00 3C */	lwz r0, 0x3c(r31)
/* 80185268 00180168  54 00 07 39 */	rlwinm. r0, r0, 0, 0x1c, 0x1c
/* 8018526C 0018016C  40 82 00 0C */	bne lbl_80185278
/* 80185270 00180170  7F E3 FB 78 */	mr r3, r31
/* 80185274 00180174  48 00 18 35 */	bl initTaskAsync__10RPSysSceneFv
lbl_80185278:
/* 80185278 00180178  80 7F 00 2C */	lwz r3, 0x2c(r31)
/* 8018527C 0018017C  48 02 AA CD */	bl func_801AFD48
/* 80185280 00180180  80 7F 00 30 */	lwz r3, 0x30(r31)
/* 80185284 00180184  48 00 2A F5 */	bl init__17RPSysCommonObjectFv
/* 80185288 00180188  80 6D A1 58 */	lwz r3, sInstance__13RPSysSceneMgr-_SDA_BASE_(r13)
/* 8018528C 0018018C  48 00 0A 01 */	bl resetFadeColor__13RPSysSceneMgrFv
/* 80185290 00180190  80 6D A1 58 */	lwz r3, sInstance__13RPSysSceneMgr-_SDA_BASE_(r13)
/* 80185294 00180194  48 00 0A A1 */	bl resetFadeFrame__13RPSysSceneMgrFv
/* 80185298 00180198  80 6D A1 58 */	lwz r3, sInstance__13RPSysSceneMgr-_SDA_BASE_(r13)
/* 8018529C 0018019C  38 80 00 01 */	li r4, 1
/* 801852A0 001801A0  48 00 08 C5 */	bl setSceneStatus__13RPSysSceneMgrFQ33EGG5Fader7EStatus
/* 801852A4 001801A4  80 6D A1 58 */	lwz r3, sInstance__13RPSysSceneMgr-_SDA_BASE_(r13)
/* 801852A8 001801A8  48 00 0C 91 */	bl resetGuard__13RPSysSceneMgrFv
/* 801852AC 001801AC  80 6D A1 38 */	lwz r3, sInstance__11RPSysSystem-_SDA_BASE_(r13)
/* 801852B0 001801B0  38 80 00 01 */	li r4, 1
/* 801852B4 001801B4  4B FF DF 35 */	bl setDimming__11RPSysSystemFi
/* 801852B8 001801B8  80 6D A1 C8 */	lwz r3, lbl_804BF548-_SDA_BASE_(r13)
/* 801852BC 001801BC  38 A0 00 00 */	li r5, 0
/* 801852C0 001801C0  80 9F 00 34 */	lwz r4, 0x34(r31)
/* 801852C4 001801C4  48 00 E4 21 */	bl func_801936E4
/* 801852C8 001801C8  81 9F 00 00 */	lwz r12, 0(r31)
/* 801852CC 001801CC  7F E3 FB 78 */	mr r3, r31
/* 801852D0 001801D0  81 8C 00 4C */	lwz r12, 0x4c(r12)
/* 801852D4 001801D4  7D 89 03 A6 */	mtctr r12
/* 801852D8 001801D8  4E 80 04 21 */	bctrl 
/* 801852DC 001801DC  80 1F 00 3C */	lwz r0, 0x3c(r31)
/* 801852E0 001801E0  54 00 07 39 */	rlwinm. r0, r0, 0, 0x1c, 0x1c
/* 801852E4 001801E4  40 82 00 0C */	bne lbl_801852F0
/* 801852E8 001801E8  80 6D A1 58 */	lwz r3, sInstance__13RPSysSceneMgr-_SDA_BASE_(r13)
/* 801852EC 001801EC  48 00 08 75 */	bl startMgrFadeIn__13RPSysSceneMgrFv
lbl_801852F0:
/* 801852F0 001801F0  80 01 00 14 */	lwz r0, 0x14(r1)
/* 801852F4 001801F4  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 801852F8 001801F8  7C 08 03 A6 */	mtlr r0
/* 801852FC 001801FC  38 21 00 10 */	addi r1, r1, 0x10
/* 80185300 00180200  4E 80 00 20 */	blr 

.global enter__10RPSysSceneFv
enter__10RPSysSceneFv:
/* 80185304 00180204  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80185308 00180208  7C 08 02 A6 */	mflr r0
/* 8018530C 0018020C  90 01 00 14 */	stw r0, 0x14(r1)
/* 80185310 00180210  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80185314 00180214  7C 7F 1B 78 */	mr r31, r3
/* 80185318 00180218  4B FF FB 89 */	bl construct__10RPSysSceneFv
/* 8018531C 0018021C  81 9F 00 00 */	lwz r12, 0(r31)
/* 80185320 00180220  7F E3 FB 78 */	mr r3, r31
/* 80185324 00180224  81 8C 00 44 */	lwz r12, 0x44(r12)
/* 80185328 00180228  7D 89 03 A6 */	mtctr r12
/* 8018532C 0018022C  4E 80 04 21 */	bctrl 
/* 80185330 00180230  80 1F 00 3C */	lwz r0, 0x3c(r31)
/* 80185334 00180234  54 00 07 39 */	rlwinm. r0, r0, 0, 0x1c, 0x1c
/* 80185338 00180238  40 82 00 1C */	bne lbl_80185354
/* 8018533C 0018023C  80 6D A1 58 */	lwz r3, sInstance__13RPSysSceneMgr-_SDA_BASE_(r13)
/* 80185340 00180240  48 00 05 5D */	bl drawMgrFader__13RPSysSceneMgrFv
/* 80185344 00180244  7F E3 FB 78 */	mr r3, r31
/* 80185348 00180248  48 00 18 ED */	bl loadSceneResource__10RPSysSceneFv
/* 8018534C 0018024C  7F E3 FB 78 */	mr r3, r31
/* 80185350 00180250  48 00 17 D1 */	bl load__10RPSysSceneFv
lbl_80185354:
/* 80185354 00180254  48 01 6B 2D */	bl func_8019BE80
/* 80185358 00180258  80 6D A1 B8 */	lwz r3, lbl_804BF538-_SDA_BASE_(r13)
/* 8018535C 0018025C  48 00 B8 41 */	bl func_80190B9C
/* 80185360 00180260  80 1F 00 3C */	lwz r0, 0x3c(r31)
/* 80185364 00180264  54 00 07 39 */	rlwinm. r0, r0, 0, 0x1c, 0x1c
/* 80185368 00180268  40 82 00 0C */	bne lbl_80185374
/* 8018536C 0018026C  7F E3 FB 78 */	mr r3, r31
/* 80185370 00180270  48 00 17 39 */	bl initTaskAsync__10RPSysSceneFv
lbl_80185374:
/* 80185374 00180274  80 7F 00 2C */	lwz r3, 0x2c(r31)
/* 80185378 00180278  48 02 A9 D1 */	bl func_801AFD48
/* 8018537C 0018027C  80 7F 00 30 */	lwz r3, 0x30(r31)
/* 80185380 00180280  48 00 29 F9 */	bl init__17RPSysCommonObjectFv
/* 80185384 00180284  80 6D A1 58 */	lwz r3, sInstance__13RPSysSceneMgr-_SDA_BASE_(r13)
/* 80185388 00180288  48 00 09 05 */	bl resetFadeColor__13RPSysSceneMgrFv
/* 8018538C 0018028C  80 6D A1 58 */	lwz r3, sInstance__13RPSysSceneMgr-_SDA_BASE_(r13)
/* 80185390 00180290  48 00 09 A5 */	bl resetFadeFrame__13RPSysSceneMgrFv
/* 80185394 00180294  80 6D A1 58 */	lwz r3, sInstance__13RPSysSceneMgr-_SDA_BASE_(r13)
/* 80185398 00180298  38 80 00 01 */	li r4, 1
/* 8018539C 0018029C  48 00 07 C9 */	bl setSceneStatus__13RPSysSceneMgrFQ33EGG5Fader7EStatus
/* 801853A0 001802A0  80 6D A1 58 */	lwz r3, sInstance__13RPSysSceneMgr-_SDA_BASE_(r13)
/* 801853A4 001802A4  48 00 0B 95 */	bl resetGuard__13RPSysSceneMgrFv
/* 801853A8 001802A8  80 6D A1 38 */	lwz r3, sInstance__11RPSysSystem-_SDA_BASE_(r13)
/* 801853AC 001802AC  38 80 00 01 */	li r4, 1
/* 801853B0 001802B0  4B FF DE 39 */	bl setDimming__11RPSysSystemFi
/* 801853B4 001802B4  80 6D A1 C8 */	lwz r3, lbl_804BF548-_SDA_BASE_(r13)
/* 801853B8 001802B8  38 A0 00 00 */	li r5, 0
/* 801853BC 001802BC  80 9F 00 34 */	lwz r4, 0x34(r31)
/* 801853C0 001802C0  48 00 E3 25 */	bl func_801936E4
/* 801853C4 001802C4  81 9F 00 00 */	lwz r12, 0(r31)
/* 801853C8 001802C8  7F E3 FB 78 */	mr r3, r31
/* 801853CC 001802CC  81 8C 00 4C */	lwz r12, 0x4c(r12)
/* 801853D0 001802D0  7D 89 03 A6 */	mtctr r12
/* 801853D4 001802D4  4E 80 04 21 */	bctrl 
/* 801853D8 001802D8  80 1F 00 3C */	lwz r0, 0x3c(r31)
/* 801853DC 001802DC  54 00 07 39 */	rlwinm. r0, r0, 0, 0x1c, 0x1c
/* 801853E0 001802E0  40 82 00 0C */	bne lbl_801853EC
/* 801853E4 001802E4  80 6D A1 58 */	lwz r3, sInstance__13RPSysSceneMgr-_SDA_BASE_(r13)
/* 801853E8 001802E8  48 00 07 79 */	bl startMgrFadeIn__13RPSysSceneMgrFv
lbl_801853EC:
/* 801853EC 001802EC  80 01 00 14 */	lwz r0, 0x14(r1)
/* 801853F0 001802F0  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 801853F4 001802F4  7C 08 03 A6 */	mtlr r0
/* 801853F8 001802F8  38 21 00 10 */	addi r1, r1, 0x10
/* 801853FC 001802FC  4E 80 00 20 */	blr 

# Weak function in WFU
.global Configure__10RPSysSceneFv
Configure__10RPSysSceneFv:
/* 80185400 00180300  4E 80 00 20 */	blr 

.global __ct__10RPSysSceneFv
__ct__10RPSysSceneFv:
/* 80185404 00180304  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80185408 00180308  7C 08 02 A6 */	mflr r0
/* 8018540C 0018030C  90 01 00 14 */	stw r0, 0x14(r1)
/* 80185410 00180310  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80185414 00180314  7C 7F 1B 78 */	mr r31, r3
/* 80185418 00180318  4B F2 5B CD */	bl __ct__Q23EGG5SceneFv
/* 8018541C 0018031C  3C A0 80 3C */	lis r5, __vt__10RPSysScene@ha
/* 80185420 00180320  38 C0 00 00 */	li r6, 0
/* 80185424 00180324  38 A5 96 00 */	addi r5, r5, __vt__10RPSysScene@l
/* 80185428 00180328  38 00 FF FF */	li r0, -1
/* 8018542C 0018032C  38 85 00 28 */	addi r4, r5, 0x28
/* 80185430 00180330  90 DF 00 24 */	stw r6, 0x24(r31)
/* 80185434 00180334  7F E3 FB 78 */	mr r3, r31
/* 80185438 00180338  90 BF 00 00 */	stw r5, 0(r31)
/* 8018543C 0018033C  90 9F 00 28 */	stw r4, 0x28(r31)
/* 80185440 00180340  90 DF 00 2C */	stw r6, 0x2c(r31)
/* 80185444 00180344  90 DF 00 30 */	stw r6, 0x30(r31)
/* 80185448 00180348  90 DF 00 34 */	stw r6, 0x34(r31)
/* 8018544C 0018034C  90 DF 00 38 */	stw r6, 0x38(r31)
/* 80185450 00180350  90 DF 00 3C */	stw r6, 0x3c(r31)
/* 80185454 00180354  90 1F 00 40 */	stw r0, 0x40(r31)
/* 80185458 00180358  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8018545C 0018035C  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80185460 00180360  7C 08 03 A6 */	mtlr r0
/* 80185464 00180364  38 21 00 10 */	addi r1, r1, 0x10
/* 80185468 00180368  4E 80 00 20 */	blr 

.global setDimming__10RPSysSceneFb
setDimming__10RPSysSceneFb:
/* 8018546C 0018036C  80 6D A1 38 */	lwz r3, sInstance__11RPSysSystem-_SDA_BASE_(r13)
/* 80185470 00180370  4B FF DD 78 */	b setDimming__11RPSysSystemFi

.global startFadeOut__10RPSysSceneFv
startFadeOut__10RPSysSceneFv:
/* 80185474 00180374  80 6D A1 58 */	lwz r3, sInstance__13RPSysSceneMgr-_SDA_BASE_(r13)
/* 80185478 00180378  48 00 06 C0 */	b startSceneFadeOut__13RPSysSceneMgrFv

.global startFadeIn__10RPSysSceneFv
startFadeIn__10RPSysSceneFv:
/* 8018547C 0018037C  80 6D A1 58 */	lwz r3, sInstance__13RPSysSceneMgr-_SDA_BASE_(r13)
/* 80185480 00180380  48 00 06 CC */	b startSceneFadeIn__13RPSysSceneMgrFv

.global setSceneFadeColor__10RPSysSceneFQ23EGG5Color
setSceneFadeColor__10RPSysSceneFQ23EGG5Color:
/* 80185484 00180384  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80185488 00180388  7C 08 02 A6 */	mflr r0
/* 8018548C 0018038C  88 64 00 00 */	lbz r3, 0(r4)
/* 80185490 00180390  90 01 00 14 */	stw r0, 0x14(r1)
/* 80185494 00180394  88 C4 00 01 */	lbz r6, 1(r4)
/* 80185498 00180398  88 A4 00 02 */	lbz r5, 2(r4)
/* 8018549C 0018039C  88 04 00 03 */	lbz r0, 3(r4)
/* 801854A0 001803A0  38 81 00 08 */	addi r4, r1, 8
/* 801854A4 001803A4  98 61 00 08 */	stb r3, 8(r1)
/* 801854A8 001803A8  80 6D A1 58 */	lwz r3, sInstance__13RPSysSceneMgr-_SDA_BASE_(r13)
/* 801854AC 001803AC  98 C1 00 09 */	stb r6, 9(r1)
/* 801854B0 001803B0  98 A1 00 0A */	stb r5, 0xa(r1)
/* 801854B4 001803B4  98 01 00 0B */	stb r0, 0xb(r1)
/* 801854B8 001803B8  48 00 06 D5 */	bl setSceneFadeColor__13RPSysSceneMgrFQ23EGG5Color
/* 801854BC 001803BC  80 01 00 14 */	lwz r0, 0x14(r1)
/* 801854C0 001803C0  7C 08 03 A6 */	mtlr r0
/* 801854C4 001803C4  38 21 00 10 */	addi r1, r1, 0x10
/* 801854C8 001803C8  4E 80 00 20 */	blr 

.global setFadeColor__10RPSysSceneFQ23EGG5Color
setFadeColor__10RPSysSceneFQ23EGG5Color:
/* 801854CC 001803CC  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 801854D0 001803D0  7C 08 02 A6 */	mflr r0
/* 801854D4 001803D4  88 64 00 00 */	lbz r3, 0(r4)
/* 801854D8 001803D8  90 01 00 14 */	stw r0, 0x14(r1)
/* 801854DC 001803DC  88 C4 00 01 */	lbz r6, 1(r4)
/* 801854E0 001803E0  88 A4 00 02 */	lbz r5, 2(r4)
/* 801854E4 001803E4  88 04 00 03 */	lbz r0, 3(r4)
/* 801854E8 001803E8  38 81 00 08 */	addi r4, r1, 8
/* 801854EC 001803EC  98 61 00 08 */	stb r3, 8(r1)
/* 801854F0 001803F0  80 6D A1 58 */	lwz r3, sInstance__13RPSysSceneMgr-_SDA_BASE_(r13)
/* 801854F4 001803F4  98 C1 00 09 */	stb r6, 9(r1)
/* 801854F8 001803F8  98 A1 00 0A */	stb r5, 0xa(r1)
/* 801854FC 001803FC  98 01 00 0B */	stb r0, 0xb(r1)
/* 80185500 00180400  48 00 06 D5 */	bl setFadeColor__13RPSysSceneMgrFQ23EGG5Color
/* 80185504 00180404  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80185508 00180408  7C 08 03 A6 */	mtlr r0
/* 8018550C 0018040C  38 21 00 10 */	addi r1, r1, 0x10
/* 80185510 00180410  4E 80 00 20 */	blr 

.global getFadeColor__10RPSysSceneCFv
getFadeColor__10RPSysSceneCFv:
/* 80185514 00180414  80 8D A1 58 */	lwz r4, sInstance__13RPSysSceneMgr-_SDA_BASE_(r13)
/* 80185518 00180418  48 00 07 48 */	b getFadeColor__13RPSysSceneMgrFv

.global setFadeFrame__10RPSysSceneFUs
setFadeFrame__10RPSysSceneFUs:
/* 8018551C 0018041C  80 6D A1 58 */	lwz r3, sInstance__13RPSysSceneMgr-_SDA_BASE_(r13)
/* 80185520 00180420  48 00 07 C0 */	b setFadeFrame__13RPSysSceneMgrFUs

.global isNandAccessEnable__10RPSysSceneCFv
isNandAccessEnable__10RPSysSceneCFv:
/* 80185524 00180424  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80185528 00180428  7C 08 02 A6 */	mflr r0
/* 8018552C 0018042C  90 01 00 14 */	stw r0, 0x14(r1)
/* 80185530 00180430  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80185534 00180434  3B E0 00 00 */	li r31, 0
/* 80185538 00180438  80 6D A1 58 */	lwz r3, sInstance__13RPSysSceneMgr-_SDA_BASE_(r13)
/* 8018553C 0018043C  48 00 04 A1 */	bl isFadeOut__13RPSysSceneMgrFv
/* 80185540 00180440  2C 03 00 00 */	cmpwi r3, 0
/* 80185544 00180444  40 82 00 18 */	bne lbl_8018555C
/* 80185548 00180448  80 6D A1 58 */	lwz r3, sInstance__13RPSysSceneMgr-_SDA_BASE_(r13)
/* 8018554C 0018044C  48 00 04 1D */	bl isTaskFinished__13RPSysSceneMgrFv
/* 80185550 00180450  2C 03 00 00 */	cmpwi r3, 0
/* 80185554 00180454  41 82 00 08 */	beq lbl_8018555C
/* 80185558 00180458  3B E0 00 01 */	li r31, 1
lbl_8018555C:
/* 8018555C 0018045C  7F E3 FB 78 */	mr r3, r31
/* 80185560 00180460  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80185564 00180464  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80185568 00180468  7C 08 03 A6 */	mtlr r0
/* 8018556C 0018046C  38 21 00 10 */	addi r1, r1, 0x10
/* 80185570 00180470  4E 80 00 20 */	blr 

.global isSceneChangeEnable__10RPSysSceneCFv
isSceneChangeEnable__10RPSysSceneCFv:
/* 80185574 00180474  80 6D A1 58 */	lwz r3, sInstance__13RPSysSceneMgr-_SDA_BASE_(r13)
/* 80185578 00180478  48 00 03 60 */	b isSceneChangeEnable__13RPSysSceneMgrFv

.global isSceneBlank__10RPSysSceneCFv
isSceneBlank__10RPSysSceneCFv:
/* 8018557C 0018047C  80 6D A1 58 */	lwz r3, sInstance__13RPSysSceneMgr-_SDA_BASE_(r13)
/* 80185580 00180480  48 00 04 D0 */	b isBlank__13RPSysSceneMgrFv

.global isSceneDisplay__10RPSysSceneCFv
isSceneDisplay__10RPSysSceneCFv:
/* 80185584 00180484  80 6D A1 58 */	lwz r3, sInstance__13RPSysSceneMgr-_SDA_BASE_(r13)
/* 80185588 00180488  48 00 05 3C */	b isDisplay__13RPSysSceneMgrFv

.global getDebugSceneHeap__10RPSysSceneFv
getDebugSceneHeap__10RPSysSceneFv:
/* 8018558C 0018048C  38 6D A1 50 */	addi r3, r13, sDebugHeap__10RPSysScene-_SDA_BASE_
/* 80185590 00180490  4E 80 00 20 */	blr 

# Weak function in WFU
.global pauseCallBack__10RPSysSceneFb
pauseCallBack__10RPSysSceneFb:
/* 80185594 00180494  4E 80 00 20 */	blr 

# Weak function in WFU
.global LoadResource__10RPSysSceneFv
LoadResource__10RPSysSceneFv:
/* 80185598 00180498  4E 80 00 20 */	blr 

# Weak function in WFU
.global taskAsync__10RPSysSceneFv
taskAsync__10RPSysSceneFv:
/* 8018559C 0018049C  4E 80 00 20 */	blr 

# Weak function!
.global UserDraw__16IRPGrpDrawObjectFv
UserDraw__16IRPGrpDrawObjectFv:
/* 801855A0 001804A0  4E 80 00 20 */	blr 

# Weak function!
.global DebugDraw__16IRPGrpDrawObjectFv
DebugDraw__16IRPGrpDrawObjectFv:
/* 801855A4 001804A4  4E 80 00 20 */	blr 

.global "__sinit_\RPSysScene_cpp"
"__sinit_\RPSysScene_cpp":
/* 801855A8 001804A8  38 00 00 00 */	li r0, 0
/* 801855AC 001804AC  90 0D A1 50 */	stw r0, sDebugHeap__10RPSysScene-_SDA_BASE_(r13)
/* 801855B0 001804B0  4E 80 00 20 */	blr 

.global "@36@__dt__10RPSysSceneFv"
"@36@__dt__10RPSysSceneFv":
/* 801855B4 001804B4  38 63 FF DC */	addi r3, r3, -36
/* 801855B8 001804B8  4B FF E9 F0 */	b __dt__10RPSysSceneFv
