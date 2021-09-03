.include "macros.inc"

.section .rodata, "a"
.balign 0x8
.global lbl_803793C0
lbl_803793C0:
	.incbin "baserom.dol", 0x3754C0, 0x20

.section .data, "wa"
.balign 0x8
.global lbl_80397888
lbl_80397888:
	.incbin "baserom.dol", 0x393988, 0x30

.section .text, "ax"
# EGG::eggScreen::~eggScreen (weak)
.global lbl_8008D4BC
lbl_8008D4BC:
/* 8008D4BC 000883BC  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8008D4C0 000883C0  7C 08 02 A6 */	mflr r0
/* 8008D4C4 000883C4  2C 03 00 00 */	cmpwi r3, 0
/* 8008D4C8 000883C8  90 01 00 14 */	stw r0, 0x14(r1)
/* 8008D4CC 000883CC  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8008D4D0 000883D0  7C 7F 1B 78 */	mr r31, r3
/* 8008D4D4 000883D4  41 82 00 10 */	beq lbl_8008D4E4
/* 8008D4D8 000883D8  2C 04 00 00 */	cmpwi r4, 0
/* 8008D4DC 000883DC  40 81 00 08 */	ble lbl_8008D4E4
/* 8008D4E0 000883E0  48 01 5D A5 */	bl __dl__FPv
lbl_8008D4E4:
/* 8008D4E4 000883E4  7F E3 FB 78 */	mr r3, r31
/* 8008D4E8 000883E8  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8008D4EC 000883EC  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8008D4F0 000883F0  7C 08 03 A6 */	mtlr r0
/* 8008D4F4 000883F4  38 21 00 10 */	addi r1, r1, 0x10
/* 8008D4F8 000883F8  4E 80 00 20 */	blr 
/* 8008D4FC 000883FC  38 60 00 03 */	li r3, 3
/* 8008D500 00088400  4E 80 00 20 */	blr 
/* 8008D504 00088404  38 63 FF 90 */	addi r3, r3, -112
/* 8008D508 00088408  4B FF E8 50 */	b lbl_8008BD58

.global func_8008D50C
func_8008D50C:
/* 8008D50C 0008840C  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8008D510 00088410  7C 08 02 A6 */	mflr r0
/* 8008D514 00088414  90 01 00 14 */	stw r0, 0x14(r1)
/* 8008D518 00088418  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8008D51C 0008841C  7C 7F 1B 78 */	mr r31, r3
/* 8008D520 00088420  4B FF C8 AD */	bl func_80089DCC
/* 8008D524 00088424  3C 80 80 39 */	lis r4, lbl_80397888@ha
/* 8008D528 00088428  38 00 00 00 */	li r0, 0
/* 8008D52C 0008842C  38 84 78 88 */	addi r4, r4, lbl_80397888@l
/* 8008D530 00088430  90 1F 00 7C */	stw r0, 0x7c(r31)
/* 8008D534 00088434  38 04 00 0C */	addi r0, r4, 0xc
/* 8008D538 00088438  38 60 00 48 */	li r3, 0x48
/* 8008D53C 0008843C  90 9F 00 6C */	stw r4, 0x6c(r31)
/* 8008D540 00088440  90 1F 00 70 */	stw r0, 0x70(r31)
/* 8008D544 00088444  48 01 5D 01 */	bl __nw__FUl
/* 8008D548 00088448  2C 03 00 00 */	cmpwi r3, 0
/* 8008D54C 0008844C  41 82 00 08 */	beq lbl_8008D554
/* 8008D550 00088450  48 00 AB 99 */	bl func_800980E8
lbl_8008D554:
/* 8008D554 00088454  90 7F 00 7C */	stw r3, 0x7c(r31)
/* 8008D558 00088458  81 83 00 1C */	lwz r12, 0x1c(r3)
/* 8008D55C 0008845C  81 8C 00 0C */	lwz r12, 0xc(r12)
/* 8008D560 00088460  7D 89 03 A6 */	mtctr r12
/* 8008D564 00088464  4E 80 04 21 */	bctrl 
/* 8008D568 00088468  7F E3 FB 78 */	mr r3, r31
/* 8008D56C 0008846C  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8008D570 00088470  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8008D574 00088474  7C 08 03 A6 */	mtlr r0
/* 8008D578 00088478  38 21 00 10 */	addi r1, r1, 0x10
/* 8008D57C 0008847C  4E 80 00 20 */	blr 
lbl_8008D580:
/* 8008D580 00088480  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8008D584 00088484  7C 08 02 A6 */	mflr r0
/* 8008D588 00088488  2C 03 00 00 */	cmpwi r3, 0
/* 8008D58C 0008848C  90 01 00 14 */	stw r0, 0x14(r1)
/* 8008D590 00088490  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8008D594 00088494  7C 9F 23 78 */	mr r31, r4
/* 8008D598 00088498  93 C1 00 08 */	stw r30, 8(r1)
/* 8008D59C 0008849C  7C 7E 1B 78 */	mr r30, r3
/* 8008D5A0 000884A0  41 82 00 68 */	beq lbl_8008D608
/* 8008D5A4 000884A4  80 A3 00 7C */	lwz r5, 0x7c(r3)
/* 8008D5A8 000884A8  3C 80 80 39 */	lis r4, lbl_80397888@ha
/* 8008D5AC 000884AC  38 84 78 88 */	addi r4, r4, lbl_80397888@l
/* 8008D5B0 000884B0  38 04 00 0C */	addi r0, r4, 0xc
/* 8008D5B4 000884B4  2C 05 00 00 */	cmpwi r5, 0
/* 8008D5B8 000884B8  90 83 00 6C */	stw r4, 0x6c(r3)
/* 8008D5BC 000884BC  90 03 00 70 */	stw r0, 0x70(r3)
/* 8008D5C0 000884C0  41 82 00 1C */	beq lbl_8008D5DC
/* 8008D5C4 000884C4  81 85 00 1C */	lwz r12, 0x1c(r5)
/* 8008D5C8 000884C8  7C A3 2B 78 */	mr r3, r5
/* 8008D5CC 000884CC  38 80 00 01 */	li r4, 1
/* 8008D5D0 000884D0  81 8C 00 08 */	lwz r12, 8(r12)
/* 8008D5D4 000884D4  7D 89 03 A6 */	mtctr r12
/* 8008D5D8 000884D8  4E 80 04 21 */	bctrl 
lbl_8008D5DC:
/* 8008D5DC 000884DC  38 00 00 00 */	li r0, 0
/* 8008D5E0 000884E0  2C 1E 00 00 */	cmpwi r30, 0
/* 8008D5E4 000884E4  90 1E 00 7C */	stw r0, 0x7c(r30)
/* 8008D5E8 000884E8  41 82 00 10 */	beq lbl_8008D5F8
/* 8008D5EC 000884EC  38 7E 00 70 */	addi r3, r30, 0x70
/* 8008D5F0 000884F0  38 80 00 00 */	li r4, 0
/* 8008D5F4 000884F4  48 00 EE 65 */	bl func_8009C458
lbl_8008D5F8:
/* 8008D5F8 000884F8  2C 1F 00 00 */	cmpwi r31, 0
/* 8008D5FC 000884FC  40 81 00 0C */	ble lbl_8008D608
/* 8008D600 00088500  7F C3 F3 78 */	mr r3, r30
/* 8008D604 00088504  48 01 5C 81 */	bl __dl__FPv
lbl_8008D608:
/* 8008D608 00088508  7F C3 F3 78 */	mr r3, r30
/* 8008D60C 0008850C  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8008D610 00088510  83 C1 00 08 */	lwz r30, 8(r1)
/* 8008D614 00088514  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8008D618 00088518  7C 08 03 A6 */	mtlr r0
/* 8008D61C 0008851C  38 21 00 10 */	addi r1, r1, 0x10
/* 8008D620 00088520  4E 80 00 20 */	blr 
/* 8008D624 00088524  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8008D628 00088528  7C 08 02 A6 */	mflr r0
/* 8008D62C 0008852C  2C 03 00 00 */	cmpwi r3, 0
/* 8008D630 00088530  90 01 00 14 */	stw r0, 0x14(r1)
/* 8008D634 00088534  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8008D638 00088538  7C 7F 1B 78 */	mr r31, r3
/* 8008D63C 0008853C  41 82 00 10 */	beq lbl_8008D64C
/* 8008D640 00088540  2C 04 00 00 */	cmpwi r4, 0
/* 8008D644 00088544  40 81 00 08 */	ble lbl_8008D64C
/* 8008D648 00088548  48 01 5C 3D */	bl __dl__FPv
lbl_8008D64C:
/* 8008D64C 0008854C  7F E3 FB 78 */	mr r3, r31
/* 8008D650 00088550  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8008D654 00088554  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8008D658 00088558  7C 08 03 A6 */	mtlr r0
/* 8008D65C 0008855C  38 21 00 10 */	addi r1, r1, 0x10
/* 8008D660 00088560  4E 80 00 20 */	blr 
/* 8008D664 00088564  4E 80 00 20 */	blr 
/* 8008D668 00088568  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 8008D66C 0008856C  7C 08 02 A6 */	mflr r0
/* 8008D670 00088570  90 01 00 44 */	stw r0, 0x44(r1)
/* 8008D674 00088574  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 8008D678 00088578  93 C1 00 38 */	stw r30, 0x38(r1)
/* 8008D67C 0008857C  93 A1 00 34 */	stw r29, 0x34(r1)
/* 8008D680 00088580  7C 9D 23 78 */	mr r29, r4
/* 8008D684 00088584  93 81 00 30 */	stw r28, 0x30(r1)
/* 8008D688 00088588  7C 7C 1B 78 */	mr r28, r3
/* 8008D68C 0008858C  38 63 00 04 */	addi r3, r3, 4
/* 8008D690 00088590  48 00 CA C5 */	bl func_8009A154
/* 8008D694 00088594  2C 1D 00 01 */	cmpwi r29, 1
/* 8008D698 00088598  41 82 00 34 */	beq lbl_8008D6CC
/* 8008D69C 0008859C  40 80 01 28 */	bge lbl_8008D7C4
/* 8008D6A0 000885A0  2C 1D 00 00 */	cmpwi r29, 0
/* 8008D6A4 000885A4  40 80 00 08 */	bge lbl_8008D6AC
/* 8008D6A8 000885A8  48 00 01 1C */	b lbl_8008D7C4
lbl_8008D6AC:
/* 8008D6AC 000885AC  7F 83 E3 78 */	mr r3, r28
/* 8008D6B0 000885B0  38 80 00 02 */	li r4, 2
/* 8008D6B4 000885B4  38 A0 00 00 */	li r5, 0
/* 8008D6B8 000885B8  48 01 27 15 */	bl func_8009FDCC
/* 8008D6BC 000885BC  80 0D 98 D4 */	lwz r0, lbl_804BEC54-_SDA_BASE_(r13)
/* 8008D6C0 000885C0  60 00 00 02 */	ori r0, r0, 2
/* 8008D6C4 000885C4  90 0D 98 D4 */	stw r0, lbl_804BEC54-_SDA_BASE_(r13)
/* 8008D6C8 000885C8  48 00 00 FC */	b lbl_8008D7C4
lbl_8008D6CC:
/* 8008D6CC 000885CC  3C 80 80 41 */	lis r4, lbl_80409720@ha
/* 8008D6D0 000885D0  38 60 00 00 */	li r3, 0
/* 8008D6D4 000885D4  38 84 97 20 */	addi r4, r4, lbl_80409720@l
/* 8008D6D8 000885D8  8B E4 00 0D */	lbz r31, 0xd(r4)
/* 8008D6DC 000885DC  4B FF 74 7D */	bl func_80084B58
/* 8008D6E0 000885E0  3C 60 80 41 */	lis r3, lbl_8040A9C0@ha
/* 8008D6E4 000885E4  38 63 A9 C0 */	addi r3, r3, lbl_8040A9C0@l
/* 8008D6E8 000885E8  83 A3 00 18 */	lwz r29, 0x18(r3)
/* 8008D6EC 000885EC  2C 1D 00 00 */	cmpwi r29, 0
/* 8008D6F0 000885F0  40 82 00 1C */	bne lbl_8008D70C
/* 8008D6F4 000885F4  3C 60 80 38 */	lis r3, lbl_803793C0@ha
/* 8008D6F8 000885F8  38 80 00 4A */	li r4, 0x4a
/* 8008D6FC 000885FC  38 63 93 C0 */	addi r3, r3, lbl_803793C0@l
/* 8008D700 00088600  38 A3 00 13 */	addi r5, r3, 0x13
/* 8008D704 00088604  4C C6 31 82 */	crclr 6
/* 8008D708 00088608  48 01 48 01 */	bl system_halt
lbl_8008D70C:
/* 8008D70C 0008860C  2C 1D 00 00 */	cmpwi r29, 0
/* 8008D710 00088610  83 DC 00 7C */	lwz r30, 0x7c(r28)
/* 8008D714 00088614  40 82 00 20 */	bne lbl_8008D734
/* 8008D718 00088618  3C 60 80 39 */	lis r3, lbl_80397518@ha
/* 8008D71C 0008861C  3C A0 80 39 */	lis r5, lbl_8039750C@ha
/* 8008D720 00088620  38 63 75 18 */	addi r3, r3, lbl_80397518@l
/* 8008D724 00088624  38 80 00 5F */	li r4, 0x5f
/* 8008D728 00088628  38 A5 75 0C */	addi r5, r5, lbl_8039750C@l
/* 8008D72C 0008862C  4C C6 31 82 */	crclr 6
/* 8008D730 00088630  48 01 47 D9 */	bl system_halt
lbl_8008D734:
/* 8008D734 00088634  93 BE 00 08 */	stw r29, 8(r30)
/* 8008D738 00088638  38 7C 00 04 */	addi r3, r28, 4
/* 8008D73C 0008863C  48 00 99 01 */	bl func_8009703C
/* 8008D740 00088640  C0 3C 00 10 */	lfs f1, 0x10(r28)
/* 8008D744 00088644  3C 80 43 30 */	lis r4, 0x4330
/* 8008D748 00088648  C0 1C 00 0C */	lfs f0, 0xc(r28)
/* 8008D74C 0008864C  FC 20 08 1E */	fctiwz f1, f1
/* 8008D750 00088650  80 7C 00 7C */	lwz r3, 0x7c(r28)
/* 8008D754 00088654  FC 00 00 1E */	fctiwz f0, f0
/* 8008D758 00088658  90 81 00 18 */	stw r4, 0x18(r1)
/* 8008D75C 0008865C  81 83 00 1C */	lwz r12, 0x1c(r3)
/* 8008D760 00088660  D8 21 00 08 */	stfd f1, 8(r1)
/* 8008D764 00088664  C8 42 8C D0 */	lfd f2, lbl_804C06F0-_SDA2_BASE_(r2)
/* 8008D768 00088668  D8 01 00 10 */	stfd f0, 0x10(r1)
/* 8008D76C 0008866C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8008D770 00088670  80 A1 00 14 */	lwz r5, 0x14(r1)
/* 8008D774 00088674  54 00 04 3E */	clrlwi r0, r0, 0x10
/* 8008D778 00088678  90 81 00 20 */	stw r4, 0x20(r1)
/* 8008D77C 0008867C  54 A4 04 3E */	clrlwi r4, r5, 0x10
/* 8008D780 00088680  81 8C 00 10 */	lwz r12, 0x10(r12)
/* 8008D784 00088684  90 81 00 1C */	stw r4, 0x1c(r1)
/* 8008D788 00088688  90 01 00 24 */	stw r0, 0x24(r1)
/* 8008D78C 0008868C  C8 21 00 18 */	lfd f1, 0x18(r1)
/* 8008D790 00088690  C8 01 00 20 */	lfd f0, 0x20(r1)
/* 8008D794 00088694  EC 21 10 28 */	fsubs f1, f1, f2
/* 8008D798 00088698  EC 40 10 28 */	fsubs f2, f0, f2
/* 8008D79C 0008869C  7D 89 03 A6 */	mtctr r12
/* 8008D7A0 000886A0  4E 80 04 21 */	bctrl 
/* 8008D7A4 000886A4  7F 83 E3 78 */	mr r3, r28
/* 8008D7A8 000886A8  38 80 00 02 */	li r4, 2
/* 8008D7AC 000886AC  48 01 2B 65 */	bl func_800A0310
/* 8008D7B0 000886B0  80 0D 98 D4 */	lwz r0, lbl_804BEC54-_SDA_BASE_(r13)
/* 8008D7B4 000886B4  7F E3 FB 78 */	mr r3, r31
/* 8008D7B8 000886B8  54 00 00 3A */	rlwinm r0, r0, 0, 0, 0x1d
/* 8008D7BC 000886BC  90 0D 98 D4 */	stw r0, lbl_804BEC54-_SDA_BASE_(r13)
/* 8008D7C0 000886C0  4B FF 73 99 */	bl func_80084B58
lbl_8008D7C4:
/* 8008D7C4 000886C4  80 01 00 44 */	lwz r0, 0x44(r1)
/* 8008D7C8 000886C8  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 8008D7CC 000886CC  83 C1 00 38 */	lwz r30, 0x38(r1)
/* 8008D7D0 000886D0  83 A1 00 34 */	lwz r29, 0x34(r1)
/* 8008D7D4 000886D4  83 81 00 30 */	lwz r28, 0x30(r1)
/* 8008D7D8 000886D8  7C 08 03 A6 */	mtlr r0
/* 8008D7DC 000886DC  38 21 00 40 */	addi r1, r1, 0x40
/* 8008D7E0 000886E0  4E 80 00 20 */	blr 
/* 8008D7E4 000886E4  38 60 00 02 */	li r3, 2
/* 8008D7E8 000886E8  4E 80 00 20 */	blr 
/* 8008D7EC 000886EC  38 63 FF 90 */	addi r3, r3, -112
/* 8008D7F0 000886F0  4B FF FD 90 */	b lbl_8008D580
