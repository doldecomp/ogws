.include "macros.inc"

.section .sdata, "wa"
.balign 0x8
lbl_804BD6A8:
	.string "/meta"
    .balign 4
lbl_804BD6B0:
	.string "/ticket"
    .balign 4

.section .data, "wa"
.balign 0x8
lbl_8039BA40:
.string "/title/00010000"
.balign 0x4
lbl_8039BA50:
.string "/title/00010001"
.balign 0x4
lbl_8039BA60:
.string "/title/00010003"
.balign 0x4
lbl_8039BA70:
.string "/title/00010004"
.balign 0x4
lbl_8039BA80:
.string "/title/00010005"
.balign 0x4
lbl_8039BA90:
.string "/title/00010006"
.balign 0x4
lbl_8039BAA0:
.string "/title/00010007"
.balign 0x4
lbl_8039BAB0:
.string "/shared2/title"
.balign 0x4
USER_DIR_LIST:
	.long lbl_804BD6A8 # "/meta"
	.long lbl_804BD6B0 # "/ticket"
    .long lbl_8039BA40 # "/title/00010000"
    .long lbl_8039BA50 # "/title/00010001"
    .long lbl_8039BA60 # "/title/00010003"
    .long lbl_8039BA70 # "/title/00010004"
    .long lbl_8039BA80 # "/title/00010005"
    .long lbl_8039BA90 # "/title/00010006"
    .long lbl_8039BAA0 # "/title/00010007"
    .long lbl_8039BAB0 # "/shared2/title"
    # Looks like padding but apparently is not
    # Link map has real size 0x2C (includes these last two)
    .long 0
    .long 0

.section .text, "ax"
nandCalcUsage:
/* 800EBBC4 000E6AC4  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800EBBC8 000E6AC8  7C 08 02 A6 */	mflr r0
/* 800EBBCC 000E6ACC  90 01 00 24 */	stw r0, 0x24(r1)
/* 800EBBD0 000E6AD0  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800EBBD4 000E6AD4  3B E0 00 00 */	li r31, 0
/* 800EBBD8 000E6AD8  93 C1 00 18 */	stw r30, 0x18(r1)
/* 800EBBDC 000E6ADC  7C BE 2B 78 */	mr r30, r5
/* 800EBBE0 000E6AE0  93 A1 00 14 */	stw r29, 0x14(r1)
/* 800EBBE4 000E6AE4  7C 9D 23 78 */	mr r29, r4
/* 800EBBE8 000E6AE8  93 81 00 10 */	stw r28, 0x10(r1)
/* 800EBBEC 000E6AEC  7C 7C 1B 78 */	mr r28, r3
/* 800EBBF0 000E6AF0  93 E3 00 00 */	stw r31, 0(r3)
/* 800EBBF4 000E6AF4  38 60 FF 8B */	li r3, -117
/* 800EBBF8 000E6AF8  93 E4 00 00 */	stw r31, 0(r4)
/* 800EBBFC 000E6AFC  48 00 00 58 */	b lbl_800EBC54
lbl_800EBC00:
/* 800EBC00 000E6B00  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800EBC04 000E6B04  38 81 00 0C */	addi r4, r1, 0xc
/* 800EBC08 000E6B08  38 A1 00 08 */	addi r5, r1, 8
/* 800EBC0C 000E6B0C  93 E1 00 08 */	stw r31, 8(r1)
/* 800EBC10 000E6B10  80 7E 00 00 */	lwz r3, 0(r30)
/* 800EBC14 000E6B14  4B FE E9 AD */	bl ISFS_GetUsage
/* 800EBC18 000E6B18  2C 03 00 00 */	cmpwi r3, 0
/* 800EBC1C 000E6B1C  40 82 00 28 */	bne lbl_800EBC44
/* 800EBC20 000E6B20  80 9C 00 00 */	lwz r4, 0(r28)
/* 800EBC24 000E6B24  80 01 00 0C */	lwz r0, 0xc(r1)
/* 800EBC28 000E6B28  7C 04 02 14 */	add r0, r4, r0
/* 800EBC2C 000E6B2C  90 1C 00 00 */	stw r0, 0(r28)
/* 800EBC30 000E6B30  80 9D 00 00 */	lwz r4, 0(r29)
/* 800EBC34 000E6B34  80 01 00 08 */	lwz r0, 8(r1)
/* 800EBC38 000E6B38  7C 04 02 14 */	add r0, r4, r0
/* 800EBC3C 000E6B3C  90 1D 00 00 */	stw r0, 0(r29)
/* 800EBC40 000E6B40  48 00 00 10 */	b lbl_800EBC50
lbl_800EBC44:
/* 800EBC44 000E6B44  2C 03 FF 96 */	cmpwi r3, -106
/* 800EBC48 000E6B48  40 82 00 18 */	bne lbl_800EBC60
/* 800EBC4C 000E6B4C  38 60 00 00 */	li r3, 0
lbl_800EBC50:
/* 800EBC50 000E6B50  3B DE 00 04 */	addi r30, r30, 4
lbl_800EBC54:
/* 800EBC54 000E6B54  80 1E 00 00 */	lwz r0, 0(r30)
/* 800EBC58 000E6B58  2C 00 00 00 */	cmpwi r0, 0
/* 800EBC5C 000E6B5C  40 82 FF A4 */	bne lbl_800EBC00
lbl_800EBC60:
/* 800EBC60 000E6B60  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800EBC64 000E6B64  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800EBC68 000E6B68  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 800EBC6C 000E6B6C  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 800EBC70 000E6B70  83 81 00 10 */	lwz r28, 0x10(r1)
/* 800EBC74 000E6B74  7C 08 03 A6 */	mtlr r0
/* 800EBC78 000E6B78  38 21 00 20 */	addi r1, r1, 0x20
/* 800EBC7C 000E6B7C  4E 80 00 20 */	blr 

.global NANDCheck
NANDCheck:
/* 800EBC80 000E6B80  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 800EBC84 000E6B84  7C 08 02 A6 */	mflr r0
/* 800EBC88 000E6B88  90 01 00 34 */	stw r0, 0x34(r1)
/* 800EBC8C 000E6B8C  38 00 FF FF */	li r0, -1
/* 800EBC90 000E6B90  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 800EBC94 000E6B94  7C BF 2B 78 */	mr r31, r5
/* 800EBC98 000E6B98  93 C1 00 28 */	stw r30, 0x28(r1)
/* 800EBC9C 000E6B9C  7C 9E 23 78 */	mr r30, r4
/* 800EBCA0 000E6BA0  93 A1 00 24 */	stw r29, 0x24(r1)
/* 800EBCA4 000E6BA4  7C 7D 1B 78 */	mr r29, r3
/* 800EBCA8 000E6BA8  90 01 00 14 */	stw r0, 0x14(r1)
/* 800EBCAC 000E6BAC  90 01 00 10 */	stw r0, 0x10(r1)
/* 800EBCB0 000E6BB0  90 01 00 0C */	stw r0, 0xc(r1)
/* 800EBCB4 000E6BB4  90 01 00 08 */	stw r0, 8(r1)
/* 800EBCB8 000E6BB8  4B FF F0 45 */	bl nandIsInitialized
/* 800EBCBC 000E6BBC  2C 03 00 00 */	cmpwi r3, 0
/* 800EBCC0 000E6BC0  40 82 00 0C */	bne lbl_800EBCCC
/* 800EBCC4 000E6BC4  38 60 FF 80 */	li r3, -128
/* 800EBCC8 000E6BC8  48 00 00 A4 */	b lbl_800EBD6C
lbl_800EBCCC:
/* 800EBCCC 000E6BCC  4B FF FD 75 */	bl nandGetHomeDir
/* 800EBCD0 000E6BD0  38 81 00 14 */	addi r4, r1, 0x14
/* 800EBCD4 000E6BD4  38 A1 00 10 */	addi r5, r1, 0x10
/* 800EBCD8 000E6BD8  4B FE E8 E9 */	bl ISFS_GetUsage
/* 800EBCDC 000E6BDC  2C 03 00 00 */	cmpwi r3, 0
/* 800EBCE0 000E6BE0  41 82 00 0C */	beq lbl_800EBCEC
/* 800EBCE4 000E6BE4  4B FF F0 31 */	bl nandConvertErrorCode
/* 800EBCE8 000E6BE8  48 00 00 84 */	b lbl_800EBD6C
lbl_800EBCEC:
/* 800EBCEC 000E6BEC  3C A0 80 3A */	lis r5, USER_DIR_LIST@ha
/* 800EBCF0 000E6BF0  38 61 00 0C */	addi r3, r1, 0xc
/* 800EBCF4 000E6BF4  38 81 00 08 */	addi r4, r1, 8
/* 800EBCF8 000E6BF8  38 A5 BA C0 */	addi r5, r5, USER_DIR_LIST@l
/* 800EBCFC 000E6BFC  4B FF FE C9 */	bl nandCalcUsage
/* 800EBD00 000E6C00  2C 03 00 00 */	cmpwi r3, 0
/* 800EBD04 000E6C04  41 82 00 0C */	beq lbl_800EBD10
/* 800EBD08 000E6C08  4B FF F0 0D */	bl nandConvertErrorCode
/* 800EBD0C 000E6C0C  48 00 00 60 */	b lbl_800EBD6C
lbl_800EBD10:
/* 800EBD10 000E6C10  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800EBD14 000E6C14  38 A0 00 00 */	li r5, 0
/* 800EBD18 000E6C18  80 81 00 08 */	lwz r4, 8(r1)
/* 800EBD1C 000E6C1C  7C 00 EA 14 */	add r0, r0, r29
/* 800EBD20 000E6C20  80 61 00 0C */	lwz r3, 0xc(r1)
/* 800EBD24 000E6C24  28 00 04 00 */	cmplwi r0, 0x400
/* 800EBD28 000E6C28  80 01 00 10 */	lwz r0, 0x10(r1)
/* 800EBD2C 000E6C2C  40 81 00 08 */	ble lbl_800EBD34
/* 800EBD30 000E6C30  60 A5 00 01 */	ori r5, r5, 1
lbl_800EBD34:
/* 800EBD34 000E6C34  7C 00 F2 14 */	add r0, r0, r30
/* 800EBD38 000E6C38  28 00 00 21 */	cmplwi r0, 0x21
/* 800EBD3C 000E6C3C  40 81 00 08 */	ble lbl_800EBD44
/* 800EBD40 000E6C40  60 A5 00 02 */	ori r5, r5, 2
lbl_800EBD44:
/* 800EBD44 000E6C44  7C 03 EA 14 */	add r0, r3, r29
/* 800EBD48 000E6C48  28 00 44 00 */	cmplwi r0, 0x4400
/* 800EBD4C 000E6C4C  40 81 00 08 */	ble lbl_800EBD54
/* 800EBD50 000E6C50  60 A5 00 04 */	ori r5, r5, 4
lbl_800EBD54:
/* 800EBD54 000E6C54  7C 04 F2 14 */	add r0, r4, r30
/* 800EBD58 000E6C58  28 00 0F A0 */	cmplwi r0, 0xfa0
/* 800EBD5C 000E6C5C  40 81 00 08 */	ble lbl_800EBD64
/* 800EBD60 000E6C60  60 A5 00 08 */	ori r5, r5, 8
lbl_800EBD64:
/* 800EBD64 000E6C64  90 BF 00 00 */	stw r5, 0(r31)
/* 800EBD68 000E6C68  38 60 00 00 */	li r3, 0
lbl_800EBD6C:
/* 800EBD6C 000E6C6C  80 01 00 34 */	lwz r0, 0x34(r1)
/* 800EBD70 000E6C70  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 800EBD74 000E6C74  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 800EBD78 000E6C78  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 800EBD7C 000E6C7C  7C 08 03 A6 */	mtlr r0
/* 800EBD80 000E6C80  38 21 00 30 */	addi r1, r1, 0x30
/* 800EBD84 000E6C84  4E 80 00 20 */	blr 
