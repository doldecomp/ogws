.include "macros.inc"

.section .text, "ax"  # 0x800076E0 - 0x80355080

.global Create__Q34nw4r2ef19DrawStrategyBuilderFUl
Create__Q34nw4r2ef19DrawStrategyBuilderFUl:
/* 80021384 0001C284  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80021388 0001C288  7C 08 02 A6 */	mflr r0
/* 8002138C 0001C28C  90 01 00 14 */	stw r0, 0x14(r1)
/* 80021390 0001C290  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80021394 0001C294  3F E0 80 3D */	lis r31, lbl_803D0038@ha
/* 80021398 0001C298  3B FF 00 38 */	addi r31, r31, lbl_803D0038@l
/* 8002139C 0001C29C  93 C1 00 08 */	stw r30, 8(r1)
/* 800213A0 0001C2A0  7C 9E 23 78 */	mr r30, r4
/* 800213A4 0001C2A4  88 0D 96 D0 */	lbz r0, lbl_804BEA50-_SDA_BASE_(r13)
/* 800213A8 0001C2A8  7C 00 07 75 */	extsb. r0, r0
/* 800213AC 0001C2AC  40 82 00 28 */	bne lbl_800213D4
/* 800213B0 0001C2B0  38 7F 00 0C */	addi r3, r31, 0xc
/* 800213B4 0001C2B4  48 00 1F E1 */	bl __ct__Q34nw4r2ef21DrawBillboardStrategyFv
/* 800213B8 0001C2B8  3C 80 80 02 */	lis r4, __dt__Q34nw4r2ef21DrawBillboardStrategyFv@ha
/* 800213BC 0001C2BC  38 7F 00 0C */	addi r3, r31, 0xc
/* 800213C0 0001C2C0  38 84 15 68 */	addi r4, r4, __dt__Q34nw4r2ef21DrawBillboardStrategyFv@l
/* 800213C4 0001C2C4  38 BF 00 00 */	addi r5, r31, 0
/* 800213C8 0001C2C8  48 09 04 6D */	bl func_800B1834
/* 800213CC 0001C2CC  38 00 00 01 */	li r0, 1
/* 800213D0 0001C2D0  98 0D 96 D0 */	stb r0, lbl_804BEA50-_SDA_BASE_(r13)
lbl_800213D4:
/* 800213D4 0001C2D4  88 0D 96 D1 */	lbz r0, lbl_804BEA51-_SDA_BASE_(r13)
/* 800213D8 0001C2D8  7C 00 07 75 */	extsb. r0, r0
/* 800213DC 0001C2DC  40 82 00 28 */	bne lbl_80021404
/* 800213E0 0001C2E0  38 7F 00 D4 */	addi r3, r31, 0xd4
/* 800213E4 0001C2E4  48 00 3F 5D */	bl __ct__Q34nw4r2ef23DrawDirectionalStrategyFv
/* 800213E8 0001C2E8  3C 80 80 02 */	lis r4, __dt__Q34nw4r2ef23DrawDirectionalStrategyFv@ha
/* 800213EC 0001C2EC  38 7F 00 D4 */	addi r3, r31, 0xd4
/* 800213F0 0001C2F0  38 84 15 A8 */	addi r4, r4, __dt__Q34nw4r2ef23DrawDirectionalStrategyFv@l
/* 800213F4 0001C2F4  38 BF 00 C8 */	addi r5, r31, 0xc8
/* 800213F8 0001C2F8  48 09 04 3D */	bl func_800B1834
/* 800213FC 0001C2FC  38 00 00 01 */	li r0, 1
/* 80021400 0001C300  98 0D 96 D1 */	stb r0, lbl_804BEA51-_SDA_BASE_(r13)
lbl_80021404:
/* 80021404 0001C304  88 0D 96 D2 */	lbz r0, lbl_804BEA52-_SDA_BASE_(r13)
/* 80021408 0001C308  7C 00 07 75 */	extsb. r0, r0
/* 8002140C 0001C30C  40 82 00 28 */	bne lbl_80021434
/* 80021410 0001C310  38 7F 01 9C */	addi r3, r31, 0x19c
/* 80021414 0001C314  48 00 60 31 */	bl __ct__Q34nw4r2ef16DrawFreeStrategyFv
/* 80021418 0001C318  3C 80 80 02 */	lis r4, __dt__Q34nw4r2ef16DrawFreeStrategyFv@ha
/* 8002141C 0001C31C  38 7F 01 9C */	addi r3, r31, 0x19c
/* 80021420 0001C320  38 84 15 E8 */	addi r4, r4, __dt__Q34nw4r2ef16DrawFreeStrategyFv@l
/* 80021424 0001C324  38 BF 01 90 */	addi r5, r31, 0x190
/* 80021428 0001C328  48 09 04 0D */	bl func_800B1834
/* 8002142C 0001C32C  38 00 00 01 */	li r0, 1
/* 80021430 0001C330  98 0D 96 D2 */	stb r0, lbl_804BEA52-_SDA_BASE_(r13)
lbl_80021434:
/* 80021434 0001C334  88 0D 96 D3 */	lbz r0, lbl_804BEA53-_SDA_BASE_(r13)
/* 80021438 0001C338  7C 00 07 75 */	extsb. r0, r0
/* 8002143C 0001C33C  40 82 00 28 */	bne lbl_80021464
/* 80021440 0001C340  38 7F 02 64 */	addi r3, r31, 0x264
/* 80021444 0001C344  48 00 67 8D */	bl __ct__Q34nw4r2ef16DrawLineStrategyFv
/* 80021448 0001C348  3C 80 80 02 */	lis r4, __dt__Q34nw4r2ef16DrawLineStrategyFv@ha
/* 8002144C 0001C34C  38 7F 02 64 */	addi r3, r31, 0x264
/* 80021450 0001C350  38 84 16 28 */	addi r4, r4, __dt__Q34nw4r2ef16DrawLineStrategyFv@l
/* 80021454 0001C354  38 BF 02 58 */	addi r5, r31, 0x258
/* 80021458 0001C358  48 09 03 DD */	bl func_800B1834
/* 8002145C 0001C35C  38 00 00 01 */	li r0, 1
/* 80021460 0001C360  98 0D 96 D3 */	stb r0, lbl_804BEA53-_SDA_BASE_(r13)
lbl_80021464:
/* 80021464 0001C364  88 0D 96 D4 */	lbz r0, lbl_804BEA54-_SDA_BASE_(r13)
/* 80021468 0001C368  7C 00 07 75 */	extsb. r0, r0
/* 8002146C 0001C36C  40 82 00 28 */	bne lbl_80021494
/* 80021470 0001C370  38 7F 03 2C */	addi r3, r31, 0x32c
/* 80021474 0001C374  48 00 6C 39 */	bl __ct__Q34nw4r2ef17DrawPointStrategyFv
/* 80021478 0001C378  3C 80 80 02 */	lis r4, __dt__Q34nw4r2ef17DrawPointStrategyFv@ha
/* 8002147C 0001C37C  38 7F 03 2C */	addi r3, r31, 0x32c
/* 80021480 0001C380  38 84 16 68 */	addi r4, r4, __dt__Q34nw4r2ef17DrawPointStrategyFv@l
/* 80021484 0001C384  38 BF 03 20 */	addi r5, r31, 0x320
/* 80021488 0001C388  48 09 03 AD */	bl func_800B1834
/* 8002148C 0001C38C  38 00 00 01 */	li r0, 1
/* 80021490 0001C390  98 0D 96 D4 */	stb r0, lbl_804BEA54-_SDA_BASE_(r13)
lbl_80021494:
/* 80021494 0001C394  88 0D 96 D5 */	lbz r0, lbl_804BEA55-_SDA_BASE_(r13)
/* 80021498 0001C398  7C 00 07 75 */	extsb. r0, r0
/* 8002149C 0001C39C  40 82 00 28 */	bne lbl_800214C4
/* 800214A0 0001C3A0  38 7F 03 F4 */	addi r3, r31, 0x3f4
/* 800214A4 0001C3A4  48 00 6E FD */	bl __ct__Q34nw4r2ef18DrawStripeStrategyFv
/* 800214A8 0001C3A8  3C 80 80 02 */	lis r4, __dt__Q34nw4r2ef18DrawStripeStrategyFv@ha
/* 800214AC 0001C3AC  38 7F 03 F4 */	addi r3, r31, 0x3f4
/* 800214B0 0001C3B0  38 84 16 A8 */	addi r4, r4, __dt__Q34nw4r2ef18DrawStripeStrategyFv@l
/* 800214B4 0001C3B4  38 BF 03 E8 */	addi r5, r31, 0x3e8
/* 800214B8 0001C3B8  48 09 03 7D */	bl func_800B1834
/* 800214BC 0001C3BC  38 00 00 01 */	li r0, 1
/* 800214C0 0001C3C0  98 0D 96 D5 */	stb r0, lbl_804BEA55-_SDA_BASE_(r13)
lbl_800214C4:
/* 800214C4 0001C3C4  88 0D 96 D6 */	lbz r0, lbl_804BEA56-_SDA_BASE_(r13)
/* 800214C8 0001C3C8  7C 00 07 75 */	extsb. r0, r0
/* 800214CC 0001C3CC  40 82 00 28 */	bne lbl_800214F4
/* 800214D0 0001C3D0  38 7F 04 BC */	addi r3, r31, 0x4bc
/* 800214D4 0001C3D4  48 00 9D 19 */	bl __ct__Q34nw4r2ef24DrawSmoothStripeStrategyFv
/* 800214D8 0001C3D8  3C 80 80 02 */	lis r4, __dt__Q34nw4r2ef24DrawSmoothStripeStrategyFv@ha
/* 800214DC 0001C3DC  38 7F 04 BC */	addi r3, r31, 0x4bc
/* 800214E0 0001C3E0  38 84 16 E8 */	addi r4, r4, __dt__Q34nw4r2ef24DrawSmoothStripeStrategyFv@l
/* 800214E4 0001C3E4  38 BF 04 B0 */	addi r5, r31, 0x4b0
/* 800214E8 0001C3E8  48 09 03 4D */	bl func_800B1834
/* 800214EC 0001C3EC  38 00 00 01 */	li r0, 1
/* 800214F0 0001C3F0  98 0D 96 D6 */	stb r0, lbl_804BEA56-_SDA_BASE_(r13)
lbl_800214F4:
/* 800214F4 0001C3F4  28 1E 00 06 */	cmplwi r30, 6
/* 800214F8 0001C3F8  41 81 00 54 */	bgt lbl_8002154C
/* 800214FC 0001C3FC  3C 60 80 39 */	lis r3, lbl_80393FB0@ha
/* 80021500 0001C400  57 C0 10 3A */	slwi r0, r30, 2
/* 80021504 0001C404  38 63 3F B0 */	addi r3, r3, lbl_80393FB0@l
/* 80021508 0001C408  7C 63 00 2E */	lwzx r3, r3, r0
/* 8002150C 0001C40C  7C 69 03 A6 */	mtctr r3
/* 80021510 0001C410  4E 80 04 20 */	bctr 
/* 80021514 0001C414  38 7F 00 0C */	addi r3, r31, 0xc
/* 80021518 0001C418  48 00 00 38 */	b lbl_80021550
/* 8002151C 0001C41C  38 7F 00 D4 */	addi r3, r31, 0xd4
/* 80021520 0001C420  48 00 00 30 */	b lbl_80021550
/* 80021524 0001C424  38 7F 01 9C */	addi r3, r31, 0x19c
/* 80021528 0001C428  48 00 00 28 */	b lbl_80021550
/* 8002152C 0001C42C  38 7F 02 64 */	addi r3, r31, 0x264
/* 80021530 0001C430  48 00 00 20 */	b lbl_80021550
/* 80021534 0001C434  38 7F 03 2C */	addi r3, r31, 0x32c
/* 80021538 0001C438  48 00 00 18 */	b lbl_80021550
/* 8002153C 0001C43C  38 7F 03 F4 */	addi r3, r31, 0x3f4
/* 80021540 0001C440  48 00 00 10 */	b lbl_80021550
/* 80021544 0001C444  38 7F 04 BC */	addi r3, r31, 0x4bc
/* 80021548 0001C448  48 00 00 08 */	b lbl_80021550
lbl_8002154C:
/* 8002154C 0001C44C  38 7F 00 0C */	addi r3, r31, 0xc
lbl_80021550:
/* 80021550 0001C450  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80021554 0001C454  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80021558 0001C458  83 C1 00 08 */	lwz r30, 8(r1)
/* 8002155C 0001C45C  7C 08 03 A6 */	mtlr r0
/* 80021560 0001C460  38 21 00 10 */	addi r1, r1, 0x10
/* 80021564 0001C464  4E 80 00 20 */	blr 

.global __dt__Q34nw4r2ef21DrawBillboardStrategyFv
__dt__Q34nw4r2ef21DrawBillboardStrategyFv:
/* 80021568 0001C468  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8002156C 0001C46C  7C 08 02 A6 */	mflr r0
/* 80021570 0001C470  2C 03 00 00 */	cmpwi r3, 0
/* 80021574 0001C474  90 01 00 14 */	stw r0, 0x14(r1)
/* 80021578 0001C478  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8002157C 0001C47C  7C 7F 1B 78 */	mr r31, r3
/* 80021580 0001C480  41 82 00 10 */	beq lbl_80021590
/* 80021584 0001C484  2C 04 00 00 */	cmpwi r4, 0
/* 80021588 0001C488  40 81 00 08 */	ble lbl_80021590
/* 8002158C 0001C48C  48 08 1C F9 */	bl __dl__FPv
lbl_80021590:
/* 80021590 0001C490  7F E3 FB 78 */	mr r3, r31
/* 80021594 0001C494  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80021598 0001C498  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8002159C 0001C49C  7C 08 03 A6 */	mtlr r0
/* 800215A0 0001C4A0  38 21 00 10 */	addi r1, r1, 0x10
/* 800215A4 0001C4A4  4E 80 00 20 */	blr 

.global __dt__Q34nw4r2ef23DrawDirectionalStrategyFv
__dt__Q34nw4r2ef23DrawDirectionalStrategyFv:
/* 800215A8 0001C4A8  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800215AC 0001C4AC  7C 08 02 A6 */	mflr r0
/* 800215B0 0001C4B0  2C 03 00 00 */	cmpwi r3, 0
/* 800215B4 0001C4B4  90 01 00 14 */	stw r0, 0x14(r1)
/* 800215B8 0001C4B8  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800215BC 0001C4BC  7C 7F 1B 78 */	mr r31, r3
/* 800215C0 0001C4C0  41 82 00 10 */	beq lbl_800215D0
/* 800215C4 0001C4C4  2C 04 00 00 */	cmpwi r4, 0
/* 800215C8 0001C4C8  40 81 00 08 */	ble lbl_800215D0
/* 800215CC 0001C4CC  48 08 1C B9 */	bl __dl__FPv
lbl_800215D0:
/* 800215D0 0001C4D0  7F E3 FB 78 */	mr r3, r31
/* 800215D4 0001C4D4  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 800215D8 0001C4D8  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800215DC 0001C4DC  7C 08 03 A6 */	mtlr r0
/* 800215E0 0001C4E0  38 21 00 10 */	addi r1, r1, 0x10
/* 800215E4 0001C4E4  4E 80 00 20 */	blr 

.global __dt__Q34nw4r2ef16DrawFreeStrategyFv
__dt__Q34nw4r2ef16DrawFreeStrategyFv:
/* 800215E8 0001C4E8  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800215EC 0001C4EC  7C 08 02 A6 */	mflr r0
/* 800215F0 0001C4F0  2C 03 00 00 */	cmpwi r3, 0
/* 800215F4 0001C4F4  90 01 00 14 */	stw r0, 0x14(r1)
/* 800215F8 0001C4F8  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800215FC 0001C4FC  7C 7F 1B 78 */	mr r31, r3
/* 80021600 0001C500  41 82 00 10 */	beq lbl_80021610
/* 80021604 0001C504  2C 04 00 00 */	cmpwi r4, 0
/* 80021608 0001C508  40 81 00 08 */	ble lbl_80021610
/* 8002160C 0001C50C  48 08 1C 79 */	bl __dl__FPv
lbl_80021610:
/* 80021610 0001C510  7F E3 FB 78 */	mr r3, r31
/* 80021614 0001C514  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80021618 0001C518  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8002161C 0001C51C  7C 08 03 A6 */	mtlr r0
/* 80021620 0001C520  38 21 00 10 */	addi r1, r1, 0x10
/* 80021624 0001C524  4E 80 00 20 */	blr 

.global __dt__Q34nw4r2ef16DrawLineStrategyFv
__dt__Q34nw4r2ef16DrawLineStrategyFv:
/* 80021628 0001C528  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8002162C 0001C52C  7C 08 02 A6 */	mflr r0
/* 80021630 0001C530  2C 03 00 00 */	cmpwi r3, 0
/* 80021634 0001C534  90 01 00 14 */	stw r0, 0x14(r1)
/* 80021638 0001C538  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8002163C 0001C53C  7C 7F 1B 78 */	mr r31, r3
/* 80021640 0001C540  41 82 00 10 */	beq lbl_80021650
/* 80021644 0001C544  2C 04 00 00 */	cmpwi r4, 0
/* 80021648 0001C548  40 81 00 08 */	ble lbl_80021650
/* 8002164C 0001C54C  48 08 1C 39 */	bl __dl__FPv
lbl_80021650:
/* 80021650 0001C550  7F E3 FB 78 */	mr r3, r31
/* 80021654 0001C554  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80021658 0001C558  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8002165C 0001C55C  7C 08 03 A6 */	mtlr r0
/* 80021660 0001C560  38 21 00 10 */	addi r1, r1, 0x10
/* 80021664 0001C564  4E 80 00 20 */	blr 

.global __dt__Q34nw4r2ef17DrawPointStrategyFv
__dt__Q34nw4r2ef17DrawPointStrategyFv:
/* 80021668 0001C568  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8002166C 0001C56C  7C 08 02 A6 */	mflr r0
/* 80021670 0001C570  2C 03 00 00 */	cmpwi r3, 0
/* 80021674 0001C574  90 01 00 14 */	stw r0, 0x14(r1)
/* 80021678 0001C578  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8002167C 0001C57C  7C 7F 1B 78 */	mr r31, r3
/* 80021680 0001C580  41 82 00 10 */	beq lbl_80021690
/* 80021684 0001C584  2C 04 00 00 */	cmpwi r4, 0
/* 80021688 0001C588  40 81 00 08 */	ble lbl_80021690
/* 8002168C 0001C58C  48 08 1B F9 */	bl __dl__FPv
lbl_80021690:
/* 80021690 0001C590  7F E3 FB 78 */	mr r3, r31
/* 80021694 0001C594  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80021698 0001C598  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8002169C 0001C59C  7C 08 03 A6 */	mtlr r0
/* 800216A0 0001C5A0  38 21 00 10 */	addi r1, r1, 0x10
/* 800216A4 0001C5A4  4E 80 00 20 */	blr 

.global __dt__Q34nw4r2ef18DrawStripeStrategyFv
__dt__Q34nw4r2ef18DrawStripeStrategyFv:
/* 800216A8 0001C5A8  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800216AC 0001C5AC  7C 08 02 A6 */	mflr r0
/* 800216B0 0001C5B0  2C 03 00 00 */	cmpwi r3, 0
/* 800216B4 0001C5B4  90 01 00 14 */	stw r0, 0x14(r1)
/* 800216B8 0001C5B8  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800216BC 0001C5BC  7C 7F 1B 78 */	mr r31, r3
/* 800216C0 0001C5C0  41 82 00 10 */	beq lbl_800216D0
/* 800216C4 0001C5C4  2C 04 00 00 */	cmpwi r4, 0
/* 800216C8 0001C5C8  40 81 00 08 */	ble lbl_800216D0
/* 800216CC 0001C5CC  48 08 1B B9 */	bl __dl__FPv
lbl_800216D0:
/* 800216D0 0001C5D0  7F E3 FB 78 */	mr r3, r31
/* 800216D4 0001C5D4  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 800216D8 0001C5D8  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800216DC 0001C5DC  7C 08 03 A6 */	mtlr r0
/* 800216E0 0001C5E0  38 21 00 10 */	addi r1, r1, 0x10
/* 800216E4 0001C5E4  4E 80 00 20 */	blr 

.global __dt__Q34nw4r2ef24DrawSmoothStripeStrategyFv
__dt__Q34nw4r2ef24DrawSmoothStripeStrategyFv:
/* 800216E8 0001C5E8  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800216EC 0001C5EC  7C 08 02 A6 */	mflr r0
/* 800216F0 0001C5F0  2C 03 00 00 */	cmpwi r3, 0
/* 800216F4 0001C5F4  90 01 00 14 */	stw r0, 0x14(r1)
/* 800216F8 0001C5F8  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800216FC 0001C5FC  7C 7F 1B 78 */	mr r31, r3
/* 80021700 0001C600  41 82 00 10 */	beq lbl_80021710
/* 80021704 0001C604  2C 04 00 00 */	cmpwi r4, 0
/* 80021708 0001C608  40 81 00 08 */	ble lbl_80021710
/* 8002170C 0001C60C  48 08 1B 79 */	bl __dl__FPv
lbl_80021710:
/* 80021710 0001C610  7F E3 FB 78 */	mr r3, r31
/* 80021714 0001C614  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80021718 0001C618  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8002171C 0001C61C  7C 08 03 A6 */	mtlr r0
/* 80021720 0001C620  38 21 00 10 */	addi r1, r1, 0x10
/* 80021724 0001C624  4E 80 00 20 */	blr 
