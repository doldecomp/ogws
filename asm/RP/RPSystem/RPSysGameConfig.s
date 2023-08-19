.include "macros.inc"

.section .sbss, "wa"
.balign 0x8
.global sInstance__15RPSysGameConfig
sInstance__15RPSysGameConfig:
	.skip 0x8

.section .rodata, "a"
.balign 0x8
.global strings_80382470
strings_80382470:
    .string "GameConfig"
    .string "RootScene"
    .string "TVMode"
    .string "Language"
    .string "RPPrint"
    .string "RPSysPrint"
    .string "RPUtlPrint"
    .string "RPAudPrint"
    .string "RPSndPrint"
    .string "RPUserPrint"
    .string "RPSmkPrint"
    .string "RPOkaPrint"
    .string "RPOknPrint"
    .string "RPKasPrint"
    .string "RPMatPrint"
    .string "RPSawPrint"
    .string "RPSakPrint"
    .string "RPKodPrint"
    .string "RPGutPrint"
    .string "RPSaiPrint"
    .string "RPSumPrint"
    .string "RPUmePrint"
    .string "GameOpen"

.section .data, "wa"
.balign 0x8
.global __vt__15RPSysGameConfig
__vt__15RPSysGameConfig:
    .long 0
    .long 0
    .long __dt__15RPSysGameConfigFv
.global "__vt__19RPSysPrimTagParm<i>"
"__vt__19RPSysPrimTagParm<i>":
    # inherits from RPSysTagParm
    .long 0
    .long 0
    .long "read__19RPSysPrimTagParm<i>FRQ23EGG6Stream"
    .long "write__19RPSysPrimTagParm<i>FRQ23EGG6Stream"
    .long "dump__19RPSysPrimTagParm<i>Fv"
.global __vt__18RPSysStringTagParm
__vt__18RPSysStringTagParm:
    # inherits from RPSysTagParm
    .long 0
    .long 0
    .long read__18RPSysStringTagParmFRQ23EGG6Stream
    .long write__18RPSysStringTagParmFRQ23EGG6Stream
    .long dump__18RPSysStringTagParmFv
.global __vt__12RPSysTagParm
__vt__12RPSysTagParm:
    .long 0
    .long 0
    .long read__12RPSysTagParmFRQ23EGG6Stream
    .long write__12RPSysTagParmFRQ23EGG6Stream
    .long dump__12RPSysTagParmFv

.section .text, "ax"
.global __dt__15RPSysGameConfigFv
__dt__15RPSysGameConfigFv:
/* 80186430 00181330  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80186434 00181334  7C 08 02 A6 */	mflr r0
/* 80186438 00181338  2C 03 00 00 */	cmpwi r3, 0
/* 8018643C 0018133C  90 01 00 14 */	stw r0, 0x14(r1)
/* 80186440 00181340  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80186444 00181344  7C 7F 1B 78 */	mr r31, r3
/* 80186448 00181348  41 82 00 10 */	beq lbl_80186458
/* 8018644C 0018134C  2C 04 00 00 */	cmpwi r4, 0
/* 80186450 00181350  40 81 00 08 */	ble lbl_80186458
/* 80186454 00181354  4B F1 CE 31 */	bl __dl__FPv
lbl_80186458:
/* 80186458 00181358  7F E3 FB 78 */	mr r3, r31
/* 8018645C 0018135C  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80186460 00181360  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80186464 00181364  7C 08 03 A6 */	mtlr r0
/* 80186468 00181368  38 21 00 10 */	addi r1, r1, 0x10
/* 8018646C 0018136C  4E 80 00 20 */	blr 

.global __ct__15RPSysGameConfigFPQ23EGG4Heap
__ct__15RPSysGameConfigFPQ23EGG4Heap:
/* 80186470 00181370  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80186474 00181374  7C 08 02 A6 */	mflr r0
/* 80186478 00181378  90 01 00 24 */	stw r0, 0x24(r1)
/* 8018647C 0018137C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80186480 00181380  7C 9F 23 78 */	mr r31, r4
/* 80186484 00181384  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80186488 00181388  3F C0 80 38 */	lis r30, strings_80382470@ha
/* 8018648C 0018138C  38 9E 24 70 */	addi r4, r30, strings_80382470@l
/* 80186490 00181390  93 A1 00 14 */	stw r29, 0x14(r1)
/* 80186494 00181394  7C 7D 1B 78 */	mr r29, r3
/* 80186498 00181398  48 00 02 B5 */	bl __ct__18RPSysTagParametersFPc
/* 8018649C 0018139C  3C A0 80 3C */	lis r5, __vt__15RPSysGameConfig@ha
/* 801864A0 001813A0  3B DE 24 70 */	addi r30, r30, 0x2470
/* 801864A4 001813A4  38 A5 98 08 */	addi r5, r5, __vt__15RPSysGameConfig@l
/* 801864A8 001813A8  93 FD 00 0C */	stw r31, 0xc(r29)
/* 801864AC 001813AC  7F A4 EB 78 */	mr r4, r29
/* 801864B0 001813B0  38 7D 00 10 */	addi r3, r29, 0x10
/* 801864B4 001813B4  90 BD 00 08 */	stw r5, 8(r29)
/* 801864B8 001813B8  38 BE 00 0B */	addi r5, r30, 0xb
/* 801864BC 001813BC  48 00 02 F1 */	bl __ct__18RPSysStringTagParmFP18RPSysTagParametersPc
/* 801864C0 001813C0  7F A4 EB 78 */	mr r4, r29
/* 801864C4 001813C4  38 7D 00 20 */	addi r3, r29, 0x20
/* 801864C8 001813C8  38 BE 00 15 */	addi r5, r30, 0x15
/* 801864CC 001813CC  48 00 02 E1 */	bl __ct__18RPSysStringTagParmFP18RPSysTagParametersPc
/* 801864D0 001813D0  7F A4 EB 78 */	mr r4, r29
/* 801864D4 001813D4  38 7D 00 30 */	addi r3, r29, 0x30
/* 801864D8 001813D8  38 BE 00 1C */	addi r5, r30, 0x1c
/* 801864DC 001813DC  48 00 02 D1 */	bl __ct__18RPSysStringTagParmFP18RPSysTagParametersPc
/* 801864E0 001813E0  7F A4 EB 78 */	mr r4, r29
/* 801864E4 001813E4  38 BE 00 25 */	addi r5, r30, 0x25
/* 801864E8 001813E8  38 7D 00 40 */	addi r3, r29, 0x40
/* 801864EC 001813EC  48 00 03 55 */	bl __ct__12RPSysTagParmFP18RPSysTagParametersPc
/* 801864F0 001813F0  3F E0 80 3C */	lis r31, "__vt__19RPSysPrimTagParm<i>"@ha
/* 801864F4 001813F4  7F A4 EB 78 */	mr r4, r29
/* 801864F8 001813F8  3B FF 98 14 */	addi r31, r31, "__vt__19RPSysPrimTagParm<i>"@l
/* 801864FC 001813FC  38 BE 00 2D */	addi r5, r30, 0x2d
/* 80186500 00181400  93 FD 00 40 */	stw r31, 0x40(r29)
/* 80186504 00181404  38 7D 00 50 */	addi r3, r29, 0x50
/* 80186508 00181408  48 00 03 39 */	bl __ct__12RPSysTagParmFP18RPSysTagParametersPc
/* 8018650C 0018140C  93 FD 00 50 */	stw r31, 0x50(r29)
/* 80186510 00181410  7F A4 EB 78 */	mr r4, r29
/* 80186514 00181414  38 BE 00 38 */	addi r5, r30, 0x38
/* 80186518 00181418  38 7D 00 60 */	addi r3, r29, 0x60
/* 8018651C 0018141C  48 00 03 25 */	bl __ct__12RPSysTagParmFP18RPSysTagParametersPc
/* 80186520 00181420  93 FD 00 60 */	stw r31, 0x60(r29)
/* 80186524 00181424  7F A4 EB 78 */	mr r4, r29
/* 80186528 00181428  38 BE 00 43 */	addi r5, r30, 0x43
/* 8018652C 0018142C  38 7D 00 70 */	addi r3, r29, 0x70
/* 80186530 00181430  48 00 03 11 */	bl __ct__12RPSysTagParmFP18RPSysTagParametersPc
/* 80186534 00181434  93 FD 00 70 */	stw r31, 0x70(r29)
/* 80186538 00181438  7F A4 EB 78 */	mr r4, r29
/* 8018653C 0018143C  38 BE 00 4E */	addi r5, r30, 0x4e
/* 80186540 00181440  38 7D 00 80 */	addi r3, r29, 0x80
/* 80186544 00181444  48 00 02 FD */	bl __ct__12RPSysTagParmFP18RPSysTagParametersPc
/* 80186548 00181448  93 FD 00 80 */	stw r31, 0x80(r29)
/* 8018654C 0018144C  7F A4 EB 78 */	mr r4, r29
/* 80186550 00181450  38 BE 00 59 */	addi r5, r30, 0x59
/* 80186554 00181454  38 7D 00 90 */	addi r3, r29, 0x90
/* 80186558 00181458  48 00 02 E9 */	bl __ct__12RPSysTagParmFP18RPSysTagParametersPc
/* 8018655C 0018145C  93 FD 00 90 */	stw r31, 0x90(r29)
/* 80186560 00181460  7F A4 EB 78 */	mr r4, r29
/* 80186564 00181464  38 BE 00 65 */	addi r5, r30, 0x65
/* 80186568 00181468  38 7D 00 A0 */	addi r3, r29, 0xa0
/* 8018656C 0018146C  48 00 02 D5 */	bl __ct__12RPSysTagParmFP18RPSysTagParametersPc
/* 80186570 00181470  93 FD 00 A0 */	stw r31, 0xa0(r29)
/* 80186574 00181474  7F A4 EB 78 */	mr r4, r29
/* 80186578 00181478  38 BE 00 70 */	addi r5, r30, 0x70
/* 8018657C 0018147C  38 7D 00 B0 */	addi r3, r29, 0xb0
/* 80186580 00181480  48 00 02 C1 */	bl __ct__12RPSysTagParmFP18RPSysTagParametersPc
/* 80186584 00181484  93 FD 00 B0 */	stw r31, 0xb0(r29)
/* 80186588 00181488  7F A4 EB 78 */	mr r4, r29
/* 8018658C 0018148C  38 BE 00 7B */	addi r5, r30, 0x7b
/* 80186590 00181490  38 7D 00 C0 */	addi r3, r29, 0xc0
/* 80186594 00181494  48 00 02 AD */	bl __ct__12RPSysTagParmFP18RPSysTagParametersPc
/* 80186598 00181498  93 FD 00 C0 */	stw r31, 0xc0(r29)
/* 8018659C 0018149C  7F A4 EB 78 */	mr r4, r29
/* 801865A0 001814A0  38 BE 00 86 */	addi r5, r30, 0x86
/* 801865A4 001814A4  38 7D 00 D0 */	addi r3, r29, 0xd0
/* 801865A8 001814A8  48 00 02 99 */	bl __ct__12RPSysTagParmFP18RPSysTagParametersPc
/* 801865AC 001814AC  93 FD 00 D0 */	stw r31, 0xd0(r29)
/* 801865B0 001814B0  7F A4 EB 78 */	mr r4, r29
/* 801865B4 001814B4  38 BE 00 91 */	addi r5, r30, 0x91
/* 801865B8 001814B8  38 7D 00 E0 */	addi r3, r29, 0xe0
/* 801865BC 001814BC  48 00 02 85 */	bl __ct__12RPSysTagParmFP18RPSysTagParametersPc
/* 801865C0 001814C0  93 FD 00 E0 */	stw r31, 0xe0(r29)
/* 801865C4 001814C4  7F A4 EB 78 */	mr r4, r29
/* 801865C8 001814C8  38 BE 00 9C */	addi r5, r30, 0x9c
/* 801865CC 001814CC  38 7D 00 F0 */	addi r3, r29, 0xf0
/* 801865D0 001814D0  48 00 02 71 */	bl __ct__12RPSysTagParmFP18RPSysTagParametersPc
/* 801865D4 001814D4  93 FD 00 F0 */	stw r31, 0xf0(r29)
/* 801865D8 001814D8  7F A4 EB 78 */	mr r4, r29
/* 801865DC 001814DC  38 BE 00 A7 */	addi r5, r30, 0xa7
/* 801865E0 001814E0  38 7D 01 00 */	addi r3, r29, 0x100
/* 801865E4 001814E4  48 00 02 5D */	bl __ct__12RPSysTagParmFP18RPSysTagParametersPc
/* 801865E8 001814E8  93 FD 01 00 */	stw r31, 0x100(r29)
/* 801865EC 001814EC  7F A4 EB 78 */	mr r4, r29
/* 801865F0 001814F0  38 BE 00 B2 */	addi r5, r30, 0xb2
/* 801865F4 001814F4  38 7D 01 10 */	addi r3, r29, 0x110
/* 801865F8 001814F8  48 00 02 49 */	bl __ct__12RPSysTagParmFP18RPSysTagParametersPc
/* 801865FC 001814FC  93 FD 01 10 */	stw r31, 0x110(r29)
/* 80186600 00181500  7F A4 EB 78 */	mr r4, r29
/* 80186604 00181504  38 BE 00 BD */	addi r5, r30, 0xbd
/* 80186608 00181508  38 7D 01 20 */	addi r3, r29, 0x120
/* 8018660C 0018150C  48 00 02 35 */	bl __ct__12RPSysTagParmFP18RPSysTagParametersPc
/* 80186610 00181510  93 FD 01 20 */	stw r31, 0x120(r29)
/* 80186614 00181514  7F A4 EB 78 */	mr r4, r29
/* 80186618 00181518  38 BE 00 C8 */	addi r5, r30, 0xc8
/* 8018661C 0018151C  38 7D 01 30 */	addi r3, r29, 0x130
/* 80186620 00181520  48 00 02 21 */	bl __ct__12RPSysTagParmFP18RPSysTagParametersPc
/* 80186624 00181524  93 FD 01 30 */	stw r31, 0x130(r29)
/* 80186628 00181528  7F A4 EB 78 */	mr r4, r29
/* 8018662C 0018152C  38 BE 00 D3 */	addi r5, r30, 0xd3
/* 80186630 00181530  38 7D 01 40 */	addi r3, r29, 0x140
/* 80186634 00181534  48 00 02 0D */	bl __ct__12RPSysTagParmFP18RPSysTagParametersPc
/* 80186638 00181538  93 FD 01 40 */	stw r31, 0x140(r29)
/* 8018663C 0018153C  7F A4 EB 78 */	mr r4, r29
/* 80186640 00181540  38 BE 00 DE */	addi r5, r30, 0xde
/* 80186644 00181544  38 7D 01 50 */	addi r3, r29, 0x150
/* 80186648 00181548  48 00 01 F9 */	bl __ct__12RPSysTagParmFP18RPSysTagParametersPc
/* 8018664C 0018154C  93 FD 01 50 */	stw r31, 0x150(r29)
/* 80186650 00181550  7F A4 EB 78 */	mr r4, r29
/* 80186654 00181554  38 BE 00 E9 */	addi r5, r30, 0xe9
/* 80186658 00181558  38 7D 01 60 */	addi r3, r29, 0x160
/* 8018665C 0018155C  48 00 01 E5 */	bl __ct__12RPSysTagParmFP18RPSysTagParametersPc
/* 80186660 00181560  38 00 00 00 */	li r0, 0
/* 80186664 00181564  93 FD 01 60 */	stw r31, 0x160(r29)
/* 80186668 00181568  7F A3 EB 78 */	mr r3, r29
/* 8018666C 0018156C  90 1D 00 1C */	stw r0, 0x1c(r29)
/* 80186670 00181570  90 1D 00 2C */	stw r0, 0x2c(r29)
/* 80186674 00181574  90 1D 00 3C */	stw r0, 0x3c(r29)
/* 80186678 00181578  90 1D 00 4C */	stw r0, 0x4c(r29)
/* 8018667C 0018157C  90 1D 00 5C */	stw r0, 0x5c(r29)
/* 80186680 00181580  90 1D 00 6C */	stw r0, 0x6c(r29)
/* 80186684 00181584  90 1D 00 7C */	stw r0, 0x7c(r29)
/* 80186688 00181588  90 1D 00 8C */	stw r0, 0x8c(r29)
/* 8018668C 0018158C  90 1D 00 9C */	stw r0, 0x9c(r29)
/* 80186690 00181590  90 1D 00 AC */	stw r0, 0xac(r29)
/* 80186694 00181594  90 1D 00 BC */	stw r0, 0xbc(r29)
/* 80186698 00181598  90 1D 00 CC */	stw r0, 0xcc(r29)
/* 8018669C 0018159C  90 1D 00 DC */	stw r0, 0xdc(r29)
/* 801866A0 001815A0  90 1D 00 EC */	stw r0, 0xec(r29)
/* 801866A4 001815A4  90 1D 00 FC */	stw r0, 0xfc(r29)
/* 801866A8 001815A8  90 1D 01 0C */	stw r0, 0x10c(r29)
/* 801866AC 001815AC  90 1D 01 1C */	stw r0, 0x11c(r29)
/* 801866B0 001815B0  90 1D 01 2C */	stw r0, 0x12c(r29)
/* 801866B4 001815B4  90 1D 01 3C */	stw r0, 0x13c(r29)
/* 801866B8 001815B8  90 1D 01 4C */	stw r0, 0x14c(r29)
/* 801866BC 001815BC  90 1D 01 5C */	stw r0, 0x15c(r29)
/* 801866C0 001815C0  90 1D 01 6C */	stw r0, 0x16c(r29)
/* 801866C4 001815C4  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 801866C8 001815C8  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 801866CC 001815CC  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 801866D0 001815D0  80 01 00 24 */	lwz r0, 0x24(r1)
/* 801866D4 001815D4  7C 08 03 A6 */	mtlr r0
/* 801866D8 001815D8  38 21 00 20 */	addi r1, r1, 0x20
/* 801866DC 001815DC  4E 80 00 20 */	blr 

.global CreateInstance__15RPSysGameConfigFPQ23EGG4Heap
CreateInstance__15RPSysGameConfigFPQ23EGG4Heap:
/* 801866E0 001815E0  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 801866E4 001815E4  7C 08 02 A6 */	mflr r0
/* 801866E8 001815E8  90 01 00 14 */	stw r0, 0x14(r1)
/* 801866EC 001815EC  93 E1 00 0C */	stw r31, 0xc(r1)
/* 801866F0 001815F0  7C 7F 1B 78 */	mr r31, r3
/* 801866F4 001815F4  80 0D A1 68 */	lwz r0, sInstance__15RPSysGameConfig-_SDA_BASE_(r13)
/* 801866F8 001815F8  2C 00 00 00 */	cmpwi r0, 0
/* 801866FC 001815FC  40 82 00 2C */	bne lbl_80186728
/* 80186700 00181600  7F E4 FB 78 */	mr r4, r31
/* 80186704 00181604  38 60 01 70 */	li r3, 0x170
/* 80186708 00181608  38 A0 00 04 */	li r5, 4
/* 8018670C 0018160C  4B F1 CB 45 */	bl __nw__FUlPQ23EGG4Heapi
/* 80186710 00181610  2C 03 00 00 */	cmpwi r3, 0
/* 80186714 00181614  41 82 00 0C */	beq lbl_80186720
/* 80186718 00181618  7F E4 FB 78 */	mr r4, r31
/* 8018671C 0018161C  4B FF FD 55 */	bl __ct__15RPSysGameConfigFPQ23EGG4Heap
lbl_80186720:
/* 80186720 00181620  90 6D A1 68 */	stw r3, sInstance__15RPSysGameConfig-_SDA_BASE_(r13)
/* 80186724 00181624  48 00 00 08 */	b lbl_8018672C
lbl_80186728:
/* 80186728 00181628  38 60 00 00 */	li r3, 0
lbl_8018672C:
/* 8018672C 0018162C  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80186730 00181630  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80186734 00181634  7C 08 03 A6 */	mtlr r0
/* 80186738 00181638  38 21 00 10 */	addi r1, r1, 0x10
/* 8018673C 0018163C  4E 80 00 20 */	blr 

.global dump__12RPSysTagParmFv
dump__12RPSysTagParmFv:
/* 80186740 00181640  4E 80 00 20 */	blr 

.global write__12RPSysTagParmFRQ23EGG6Stream
write__12RPSysTagParmFRQ23EGG6Stream:
/* 80186744 00181644  4E 80 00 20 */	blr 

.global read__12RPSysTagParmFRQ23EGG6Stream
read__12RPSysTagParmFRQ23EGG6Stream:
/* 80186748 00181648  4E 80 00 20 */	blr 

.global __ct__18RPSysTagParametersFPc
__ct__18RPSysTagParametersFPc:
/* 8018674C 0018164C  38 00 00 00 */	li r0, 0
/* 80186750 00181650  90 83 00 00 */	stw r4, 0(r3)
/* 80186754 00181654  90 03 00 04 */	stw r0, 4(r3)
/* 80186758 00181658  4E 80 00 20 */	blr 

.global dump__18RPSysStringTagParmFv
dump__18RPSysStringTagParmFv:
/* 8018675C 0018165C  4E 80 00 20 */	blr 

.global write__18RPSysStringTagParmFRQ23EGG6Stream
write__18RPSysStringTagParmFRQ23EGG6Stream:
/* 80186760 00181660  7C 65 1B 78 */	mr r5, r3
/* 80186764 00181664  7C 83 23 78 */	mr r3, r4
/* 80186768 00181668  80 85 00 0C */	lwz r4, 0xc(r5)
/* 8018676C 0018166C  4B F2 1C A4 */	b writeString__Q23EGG6StreamFPc

.global read__18RPSysStringTagParmFRQ23EGG6Stream
read__18RPSysStringTagParmFRQ23EGG6Stream:
/* 80186770 00181670  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80186774 00181674  7C 08 02 A6 */	mflr r0
/* 80186778 00181678  38 A0 00 00 */	li r5, 0
/* 8018677C 0018167C  90 01 00 14 */	stw r0, 0x14(r1)
/* 80186780 00181680  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80186784 00181684  7C 7F 1B 78 */	mr r31, r3
/* 80186788 00181688  7C 83 23 78 */	mr r3, r4
/* 8018678C 0018168C  38 80 00 00 */	li r4, 0
/* 80186790 00181690  4B F2 23 ED */	bl readString__Q23EGG6StreamFPci
/* 80186794 00181694  90 7F 00 0C */	stw r3, 0xc(r31)
/* 80186798 00181698  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8018679C 0018169C  80 01 00 14 */	lwz r0, 0x14(r1)
/* 801867A0 001816A0  7C 08 03 A6 */	mtlr r0
/* 801867A4 001816A4  38 21 00 10 */	addi r1, r1, 0x10
/* 801867A8 001816A8  4E 80 00 20 */	blr 

.global __ct__18RPSysStringTagParmFP18RPSysTagParametersPc
__ct__18RPSysStringTagParmFP18RPSysTagParametersPc:
/* 801867AC 001816AC  3C C0 80 3C */	lis r6, __vt__12RPSysTagParm@ha
/* 801867B0 001816B0  38 00 00 00 */	li r0, 0
/* 801867B4 001816B4  38 C6 98 3C */	addi r6, r6, __vt__12RPSysTagParm@l
/* 801867B8 001816B8  90 A3 00 04 */	stw r5, 4(r3)
/* 801867BC 001816BC  90 C3 00 00 */	stw r6, 0(r3)
/* 801867C0 001816C0  90 03 00 08 */	stw r0, 8(r3)
/* 801867C4 001816C4  80 04 00 04 */	lwz r0, 4(r4)
/* 801867C8 001816C8  2C 00 00 00 */	cmpwi r0, 0
/* 801867CC 001816CC  41 82 00 10 */	beq lbl_801867DC
/* 801867D0 001816D0  90 03 00 08 */	stw r0, 8(r3)
/* 801867D4 001816D4  90 64 00 04 */	stw r3, 4(r4)
/* 801867D8 001816D8  48 00 00 08 */	b lbl_801867E0
lbl_801867DC:
/* 801867DC 001816DC  90 64 00 04 */	stw r3, 4(r4)
lbl_801867E0:
/* 801867E0 001816E0  3C 80 80 3C */	lis r4, __vt__18RPSysStringTagParm@ha
/* 801867E4 001816E4  38 00 00 00 */	li r0, 0
/* 801867E8 001816E8  38 84 98 28 */	addi r4, r4, __vt__18RPSysStringTagParm@l
/* 801867EC 001816EC  90 03 00 0C */	stw r0, 0xc(r3)
/* 801867F0 001816F0  90 83 00 00 */	stw r4, 0(r3)
/* 801867F4 001816F4  4E 80 00 20 */	blr 

.global "dump__19RPSysPrimTagParm<i>Fv"
"dump__19RPSysPrimTagParm<i>Fv":
/* 801867F8 001816F8  4E 80 00 20 */	blr 

.global "write__19RPSysPrimTagParm<i>FRQ23EGG6Stream"
"write__19RPSysPrimTagParm<i>FRQ23EGG6Stream":
/* 801867FC 001816FC  7C 65 1B 78 */	mr r5, r3
/* 80186800 00181700  7C 83 23 78 */	mr r3, r4
/* 80186804 00181704  80 85 00 0C */	lwz r4, 0xc(r5)
/* 80186808 00181708  4B F2 19 88 */	b write_s32__Q23EGG6StreamFl

.global "read__19RPSysPrimTagParm<i>FRQ23EGG6Stream"
"read__19RPSysPrimTagParm<i>FRQ23EGG6Stream":
/* 8018680C 0018170C  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80186810 00181710  7C 08 02 A6 */	mflr r0
/* 80186814 00181714  90 01 00 14 */	stw r0, 0x14(r1)
/* 80186818 00181718  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8018681C 0018171C  7C 7F 1B 78 */	mr r31, r3
/* 80186820 00181720  7C 83 23 78 */	mr r3, r4
/* 80186824 00181724  4B F2 18 5D */	bl read_s32__Q23EGG6StreamFv
/* 80186828 00181728  90 7F 00 0C */	stw r3, 0xc(r31)
/* 8018682C 0018172C  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80186830 00181730  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80186834 00181734  7C 08 03 A6 */	mtlr r0
/* 80186838 00181738  38 21 00 10 */	addi r1, r1, 0x10
/* 8018683C 0018173C  4E 80 00 20 */	blr 

.global __ct__12RPSysTagParmFP18RPSysTagParametersPc
__ct__12RPSysTagParmFP18RPSysTagParametersPc:
/* 80186840 00181740  3C C0 80 3C */	lis r6, __vt__12RPSysTagParm@ha
/* 80186844 00181744  38 00 00 00 */	li r0, 0
/* 80186848 00181748  38 C6 98 3C */	addi r6, r6, __vt__12RPSysTagParm@l
/* 8018684C 0018174C  90 A3 00 04 */	stw r5, 4(r3)
/* 80186850 00181750  90 C3 00 00 */	stw r6, 0(r3)
/* 80186854 00181754  90 03 00 08 */	stw r0, 8(r3)
/* 80186858 00181758  80 04 00 04 */	lwz r0, 4(r4)
/* 8018685C 0018175C  2C 00 00 00 */	cmpwi r0, 0
/* 80186860 00181760  41 82 00 10 */	beq lbl_80186870
/* 80186864 00181764  90 03 00 08 */	stw r0, 8(r3)
/* 80186868 00181768  90 64 00 04 */	stw r3, 4(r4)
/* 8018686C 0018176C  4E 80 00 20 */	blr 
lbl_80186870:
/* 80186870 00181770  90 64 00 04 */	stw r3, 4(r4)
/* 80186874 00181774  4E 80 00 20 */	blr 
