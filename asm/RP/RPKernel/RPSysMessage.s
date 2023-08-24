.include "macros.inc"

.section .data, "wa"
.balign 0x8
.global __vt__12RPSysMessage
__vt__12RPSysMessage:
	.long 0
    .long 0
    .long __dt__12RPSysMessageFv

.section .text, "ax"
.global GetCharSpace__12RPSysMessageFUlUl
GetCharSpace__12RPSysMessageFUlUl:
/* 80190D24 0018BC24  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80190D28 0018BC28  7C 08 02 A6 */	mflr r0
/* 80190D2C 0018BC2C  90 01 00 14 */	stw r0, 0x14(r1)
/* 80190D30 0018BC30  4B F2 08 51 */	bl getMsgEntry__Q23EGG6MsgResFUiUi
/* 80190D34 0018BC34  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80190D38 0018BC38  88 63 00 0A */	lbz r3, 0xa(r3)
/* 80190D3C 0018BC3C  7C 08 03 A6 */	mtlr r0
/* 80190D40 0018BC40  38 21 00 10 */	addi r1, r1, 0x10
/* 80190D44 0018BC44  4E 80 00 20 */	blr 

.global GetScale__12RPSysMessageFUlUl
GetScale__12RPSysMessageFUlUl:
/* 80190D48 0018BC48  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80190D4C 0018BC4C  7C 08 02 A6 */	mflr r0
/* 80190D50 0018BC50  90 01 00 14 */	stw r0, 0x14(r1)
/* 80190D54 0018BC54  4B F2 08 2D */	bl getMsgEntry__Q23EGG6MsgResFUiUi
/* 80190D58 0018BC58  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80190D5C 0018BC5C  A0 63 00 08 */	lhz r3, 8(r3)
/* 80190D60 0018BC60  7C 08 03 A6 */	mtlr r0
/* 80190D64 0018BC64  38 21 00 10 */	addi r1, r1, 0x10
/* 80190D68 0018BC68  4E 80 00 20 */	blr 

.global GetAttribute__12RPSysMessageFUlUl
GetAttribute__12RPSysMessageFUlUl:
/* 80190D6C 0018BC6C  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80190D70 0018BC70  7C 08 02 A6 */	mflr r0
/* 80190D74 0018BC74  90 01 00 14 */	stw r0, 0x14(r1)
/* 80190D78 0018BC78  4B F2 08 09 */	bl getMsgEntry__Q23EGG6MsgResFUiUi
/* 80190D7C 0018BC7C  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80190D80 0018BC80  80 63 00 04 */	lwz r3, 4(r3)
/* 80190D84 0018BC84  7C 08 03 A6 */	mtlr r0
/* 80190D88 0018BC88  38 21 00 10 */	addi r1, r1, 0x10
/* 80190D8C 0018BC8C  4E 80 00 20 */	blr 

.global GetMsgEntryEx__12RPSysMessageFUlUl
GetMsgEntryEx__12RPSysMessageFUlUl:
/* 80190D90 0018BC90  4B F2 07 38 */	b getMsg__Q23EGG6MsgResFUiUi

.global __dt__12RPSysMessageFv
__dt__12RPSysMessageFv:
/* 80190D94 0018BC94  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80190D98 0018BC98  7C 08 02 A6 */	mflr r0
/* 80190D9C 0018BC9C  2C 03 00 00 */	cmpwi r3, 0
/* 80190DA0 0018BCA0  90 01 00 14 */	stw r0, 0x14(r1)
/* 80190DA4 0018BCA4  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80190DA8 0018BCA8  7C 9F 23 78 */	mr r31, r4
/* 80190DAC 0018BCAC  93 C1 00 08 */	stw r30, 8(r1)
/* 80190DB0 0018BCB0  7C 7E 1B 78 */	mr r30, r3
/* 80190DB4 0018BCB4  41 82 00 1C */	beq lbl_80190DD0
/* 80190DB8 0018BCB8  38 80 00 00 */	li r4, 0
/* 80190DBC 0018BCBC  4B F2 05 BD */	bl __dt__Q23EGG6MsgResFv
/* 80190DC0 0018BCC0  2C 1F 00 00 */	cmpwi r31, 0
/* 80190DC4 0018BCC4  40 81 00 0C */	ble lbl_80190DD0
/* 80190DC8 0018BCC8  7F C3 F3 78 */	mr r3, r30
/* 80190DCC 0018BCCC  4B F1 24 B9 */	bl __dl__FPv
lbl_80190DD0:
/* 80190DD0 0018BCD0  7F C3 F3 78 */	mr r3, r30
/* 80190DD4 0018BCD4  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80190DD8 0018BCD8  83 C1 00 08 */	lwz r30, 8(r1)
/* 80190DDC 0018BCDC  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80190DE0 0018BCE0  7C 08 03 A6 */	mtlr r0
/* 80190DE4 0018BCE4  38 21 00 10 */	addi r1, r1, 0x10
/* 80190DE8 0018BCE8  4E 80 00 20 */	blr 

.global __ct__12RPSysMessageFPCvPQ23EGG4Heap
__ct__12RPSysMessageFPCvPQ23EGG4Heap:
/* 80190DEC 0018BCEC  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80190DF0 0018BCF0  7C 08 02 A6 */	mflr r0
/* 80190DF4 0018BCF4  90 01 00 14 */	stw r0, 0x14(r1)
/* 80190DF8 0018BCF8  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80190DFC 0018BCFC  7C 7F 1B 78 */	mr r31, r3
/* 80190E00 0018BD00  4B F2 02 6D */	bl __ct__Q23EGG6MsgResFPCv
/* 80190E04 0018BD04  3C 80 80 3C */	lis r4, __vt__12RPSysMessage@ha
/* 80190E08 0018BD08  7F E3 FB 78 */	mr r3, r31
/* 80190E0C 0018BD0C  38 84 99 D0 */	addi r4, r4, __vt__12RPSysMessage@l
/* 80190E10 0018BD10  90 9F 00 1C */	stw r4, 0x1c(r31)
/* 80190E14 0018BD14  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80190E18 0018BD18  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80190E1C 0018BD1C  7C 08 03 A6 */	mtlr r0
/* 80190E20 0018BD20  38 21 00 10 */	addi r1, r1, 0x10
/* 80190E24 0018BD24  4E 80 00 20 */	blr 
