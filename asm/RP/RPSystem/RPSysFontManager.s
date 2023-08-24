.include "macros.inc"

.section .sbss, "wa"
.balign 0x8
.global sInstance__16RPSysFontManager
sInstance__16RPSysFontManager:
	.skip 0x4

.section .rodata, "a"
.balign 0x8
.global scResFontsRequired__16RPSysFontManager
scResFontsRequired__16RPSysFontManager:
	.long 1, 1, 1, 0, 1, 1, 0
strings_80382a6c:
	.incbin "baserom.dol", 0x37EB6C, 0xA4

.section .data, "wa"
.balign 0x8
.global scResFontNames__16RPSysFontManager
scResFontNames__16RPSysFontManager:
	.incbin "baserom.dol", 0x3B5A50, 0x1C
.global __vt__16RPSysFontManager
__vt__16RPSysFontManager:
    .long 0
    .long 0
    .long __dt__16RPSysFontManagerFv

.section .text, "ax"
.global GetResFontData__16RPSysFontManagerCFPCc
GetResFontData__16RPSysFontManagerCFPCc:
/* 8018BCDC 00186BDC  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8018BCE0 00186BE0  7C 08 02 A6 */	mflr r0
/* 8018BCE4 00186BE4  90 01 00 24 */	stw r0, 0x24(r1)
/* 8018BCE8 00186BE8  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8018BCEC 00186BEC  3F E0 80 3C */	lis r31, scResFontNames__16RPSysFontManager@ha
/* 8018BCF0 00186BF0  3B FF 99 50 */	addi r31, r31, scResFontNames__16RPSysFontManager@l
/* 8018BCF4 00186BF4  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8018BCF8 00186BF8  3B C0 00 00 */	li r30, 0
/* 8018BCFC 00186BFC  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8018BD00 00186C00  7C 9D 23 78 */	mr r29, r4
/* 8018BD04 00186C04  93 81 00 10 */	stw r28, 0x10(r1)
/* 8018BD08 00186C08  7C 7C 1B 78 */	mr r28, r3
lbl_8018BD0C:
/* 8018BD0C 00186C0C  57 C0 15 BA */	rlwinm r0, r30, 2, 0x16, 0x1d
/* 8018BD10 00186C10  7F A3 EB 78 */	mr r3, r29
/* 8018BD14 00186C14  7C 9F 00 2E */	lwzx r4, r31, r0
/* 8018BD18 00186C18  4B F2 D0 99 */	bl strcmp
/* 8018BD1C 00186C1C  2C 03 00 00 */	cmpwi r3, 0
/* 8018BD20 00186C20  40 82 00 08 */	bne lbl_8018BD28
/* 8018BD24 00186C24  48 00 00 14 */	b lbl_8018BD38
lbl_8018BD28:
/* 8018BD28 00186C28  3B DE 00 01 */	addi r30, r30, 1
/* 8018BD2C 00186C2C  28 1E 00 07 */	cmplwi r30, 7
/* 8018BD30 00186C30  41 80 FF DC */	blt lbl_8018BD0C
/* 8018BD34 00186C34  3B C0 00 00 */	li r30, 0
lbl_8018BD38:
/* 8018BD38 00186C38  57 C0 15 BA */	rlwinm r0, r30, 2, 0x16, 0x1d
/* 8018BD3C 00186C3C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8018BD40 00186C40  7C 7C 02 14 */	add r3, r28, r0
/* 8018BD44 00186C44  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8018BD48 00186C48  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8018BD4C 00186C4C  83 81 00 10 */	lwz r28, 0x10(r1)
/* 8018BD50 00186C50  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8018BD54 00186C54  80 63 00 24 */	lwz r3, 0x24(r3)
/* 8018BD58 00186C58  7C 08 03 A6 */	mtlr r0
/* 8018BD5C 00186C5C  38 21 00 20 */	addi r1, r1, 0x20
/* 8018BD60 00186C60  4E 80 00 20 */	blr 

.global LoadResFonts__16RPSysFontManagerFv
LoadResFonts__16RPSysFontManagerFv:
/* 8018BD64 00186C64  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8018BD68 00186C68  7C 08 02 A6 */	mflr r0
/* 8018BD6C 00186C6C  90 01 00 34 */	stw r0, 0x34(r1)
/* 8018BD70 00186C70  BF 21 00 14 */	stmw r25, 0x14(r1)
/* 8018BD74 00186C74  3F E0 80 3C */	lis r31, scResFontNames__16RPSysFontManager@ha
/* 8018BD78 00186C78  3F C0 80 38 */	lis r30, scResFontsRequired__16RPSysFontManager@ha
/* 8018BD7C 00186C7C  7C 79 1B 78 */	mr r25, r3
/* 8018BD80 00186C80  3B FF 99 50 */	addi r31, r31, scResFontNames__16RPSysFontManager@l
/* 8018BD84 00186C84  3B 40 00 00 */	li r26, 0
/* 8018BD88 00186C88  3B DE 2A 50 */	addi r30, r30, scResFontsRequired__16RPSysFontManager@l
/* 8018BD8C 00186C8C  80 8D A1 70 */	lwz r4, sInstance__20RPSysResourceManager-_SDA_BASE_(r13)
/* 8018BD90 00186C90  83 64 00 28 */	lwz r27, 0x28(r4)
lbl_8018BD94:
/* 8018BD94 00186C94  57 5C 15 BA */	rlwinm r28, r26, 2, 0x16, 0x1d
/* 8018BD98 00186C98  7C 1E E0 2E */	lwzx r0, r30, r28
/* 8018BD9C 00186C9C  2C 00 00 00 */	cmpwi r0, 0
/* 8018BDA0 00186CA0  41 82 00 50 */	beq lbl_8018BDF0
/* 8018BDA4 00186CA4  7C 9F E0 2E */	lwzx r4, r31, r28
/* 8018BDA8 00186CA8  7F 63 DB 78 */	mr r3, r27
/* 8018BDAC 00186CAC  7F B9 E2 14 */	add r29, r25, r28
/* 8018BDB0 00186CB0  38 A0 00 00 */	li r5, 0
/* 8018BDB4 00186CB4  4B FF BA C5 */	bl GetFileFromArchive__20RPSysResourceManagerFPQ23EGG7ArchivePCcPUl
/* 8018BDB8 00186CB8  90 7D 00 24 */	stw r3, 0x24(r29)
/* 8018BDBC 00186CBC  7C 64 1B 78 */	mr r4, r3
/* 8018BDC0 00186CC0  80 BD 00 08 */	lwz r5, 8(r29)
/* 8018BDC4 00186CC4  80 05 00 10 */	lwz r0, 0x10(r5)
/* 8018BDC8 00186CC8  7C 00 18 40 */	cmplw r0, r3
/* 8018BDCC 00186CCC  41 82 00 24 */	beq lbl_8018BDF0
/* 8018BDD0 00186CD0  7C A3 2B 78 */	mr r3, r5
/* 8018BDD4 00186CD4  4B E7 EC 45 */	bl SetResource__Q34nw4r2ut7ResFontFPv
/* 8018BDD8 00186CD8  80 7D 00 08 */	lwz r3, 8(r29)
/* 8018BDDC 00186CDC  38 80 00 3F */	li r4, 0x3f
/* 8018BDE0 00186CE0  81 83 00 00 */	lwz r12, 0(r3)
/* 8018BDE4 00186CE4  81 8C 00 40 */	lwz r12, 0x40(r12)
/* 8018BDE8 00186CE8  7D 89 03 A6 */	mtctr r12
/* 8018BDEC 00186CEC  4E 80 04 21 */	bctrl 
lbl_8018BDF0:
/* 8018BDF0 00186CF0  3B 5A 00 01 */	addi r26, r26, 1
/* 8018BDF4 00186CF4  28 1A 00 07 */	cmplwi r26, 7
/* 8018BDF8 00186CF8  41 80 FF 9C */	blt lbl_8018BD94
/* 8018BDFC 00186CFC  BB 21 00 14 */	lmw r25, 0x14(r1)
/* 8018BE00 00186D00  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8018BE04 00186D04  7C 08 03 A6 */	mtlr r0
/* 8018BE08 00186D08  38 21 00 30 */	addi r1, r1, 0x30
/* 8018BE0C 00186D0C  4E 80 00 20 */	blr 

.global LoadRomFont__16RPSysFontManagerFv
LoadRomFont__16RPSysFontManagerFv:
/* 8018BE10 00186D10  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8018BE14 00186D14  7C 08 02 A6 */	mflr r0
/* 8018BE18 00186D18  90 01 00 14 */	stw r0, 0x14(r1)
/* 8018BE1C 00186D1C  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8018BE20 00186D20  93 C1 00 08 */	stw r30, 8(r1)
/* 8018BE24 00186D24  7C 7E 1B 78 */	mr r30, r3
/* 8018BE28 00186D28  80 8D A1 38 */	lwz r4, sInstance__11RPSysSystem-_SDA_BASE_(r13)
/* 8018BE2C 00186D2C  83 E4 00 08 */	lwz r31, 8(r4)
/* 8018BE30 00186D30  4B E7 DF F9 */	bl GetRequireBufferSize__Q34nw4r2ut7RomFontFv
/* 8018BE34 00186D34  7F E4 FB 78 */	mr r4, r31
/* 8018BE38 00186D38  38 A0 00 20 */	li r5, 0x20
/* 8018BE3C 00186D3C  4B F1 74 39 */	bl __nwa__FUlPQ23EGG4Heapi
/* 8018BE40 00186D40  7C 64 1B 78 */	mr r4, r3
/* 8018BE44 00186D44  80 7E 00 04 */	lwz r3, 4(r30)
/* 8018BE48 00186D48  4B E7 DF 0D */	bl Load__Q34nw4r2ut7RomFontFPv
/* 8018BE4C 00186D4C  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8018BE50 00186D50  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8018BE54 00186D54  83 C1 00 08 */	lwz r30, 8(r1)
/* 8018BE58 00186D58  7C 08 03 A6 */	mtlr r0
/* 8018BE5C 00186D5C  38 21 00 10 */	addi r1, r1, 0x10
/* 8018BE60 00186D60  4E 80 00 20 */	blr 

.global __dt__16RPSysFontManagerFv
__dt__16RPSysFontManagerFv:
/* 8018BE64 00186D64  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8018BE68 00186D68  7C 08 02 A6 */	mflr r0
/* 8018BE6C 00186D6C  2C 03 00 00 */	cmpwi r3, 0
/* 8018BE70 00186D70  90 01 00 14 */	stw r0, 0x14(r1)
/* 8018BE74 00186D74  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8018BE78 00186D78  7C 7F 1B 78 */	mr r31, r3
/* 8018BE7C 00186D7C  41 82 00 10 */	beq lbl_8018BE8C
/* 8018BE80 00186D80  2C 04 00 00 */	cmpwi r4, 0
/* 8018BE84 00186D84  40 81 00 08 */	ble lbl_8018BE8C
/* 8018BE88 00186D88  4B F1 73 FD */	bl __dl__FPv
lbl_8018BE8C:
/* 8018BE8C 00186D8C  7F E3 FB 78 */	mr r3, r31
/* 8018BE90 00186D90  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8018BE94 00186D94  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8018BE98 00186D98  7C 08 03 A6 */	mtlr r0
/* 8018BE9C 00186D9C  38 21 00 10 */	addi r1, r1, 0x10
/* 8018BEA0 00186DA0  4E 80 00 20 */	blr 

.global CreateInstance__16RPSysFontManagerFv
CreateInstance__16RPSysFontManagerFv:
/* 8018BEA4 00186DA4  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8018BEA8 00186DA8  7C 08 02 A6 */	mflr r0
/* 8018BEAC 00186DAC  38 60 00 40 */	li r3, 0x40
/* 8018BEB0 00186DB0  90 01 00 24 */	stw r0, 0x24(r1)
/* 8018BEB4 00186DB4  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8018BEB8 00186DB8  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8018BEBC 00186DBC  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8018BEC0 00186DC0  93 81 00 10 */	stw r28, 0x10(r1)
/* 8018BEC4 00186DC4  4B F1 73 81 */	bl __nw__FUl
/* 8018BEC8 00186DC8  2C 03 00 00 */	cmpwi r3, 0
/* 8018BECC 00186DCC  7C 7E 1B 78 */	mr r30, r3
/* 8018BED0 00186DD0  41 82 00 60 */	beq lbl_8018BF30
/* 8018BED4 00186DD4  3C 80 80 3C */	lis r4, __vt__16RPSysFontManager@ha
/* 8018BED8 00186DD8  38 84 99 6C */	addi r4, r4, __vt__16RPSysFontManager@l
/* 8018BEDC 00186DDC  90 83 00 00 */	stw r4, 0(r3)
/* 8018BEE0 00186DE0  38 60 00 1C */	li r3, 0x1c
/* 8018BEE4 00186DE4  4B F1 73 61 */	bl __nw__FUl
/* 8018BEE8 00186DE8  2C 03 00 00 */	cmpwi r3, 0
/* 8018BEEC 00186DEC  41 82 00 08 */	beq lbl_8018BEF4
/* 8018BEF0 00186DF0  4B E7 DD 91 */	bl __ct__Q34nw4r2ut7RomFontFv
lbl_8018BEF4:
/* 8018BEF4 00186DF4  90 7E 00 04 */	stw r3, 4(r30)
/* 8018BEF8 00186DF8  7F DC F3 78 */	mr r28, r30
/* 8018BEFC 00186DFC  3B A0 00 00 */	li r29, 0
/* 8018BF00 00186E00  3B E0 00 00 */	li r31, 0
lbl_8018BF04:
/* 8018BF04 00186E04  38 60 00 18 */	li r3, 0x18
/* 8018BF08 00186E08  4B F1 73 3D */	bl __nw__FUl
/* 8018BF0C 00186E0C  2C 03 00 00 */	cmpwi r3, 0
/* 8018BF10 00186E10  41 82 00 08 */	beq lbl_8018BF18
/* 8018BF14 00186E14  4B E7 EA 71 */	bl __ct__Q34nw4r2ut7ResFontFv
lbl_8018BF18:
/* 8018BF18 00186E18  90 7C 00 08 */	stw r3, 8(r28)
/* 8018BF1C 00186E1C  3B BD 00 01 */	addi r29, r29, 1
/* 8018BF20 00186E20  2C 1D 00 07 */	cmpwi r29, 7
/* 8018BF24 00186E24  93 FC 00 24 */	stw r31, 0x24(r28)
/* 8018BF28 00186E28  3B 9C 00 04 */	addi r28, r28, 4
/* 8018BF2C 00186E2C  41 80 FF D8 */	blt lbl_8018BF04
lbl_8018BF30:
/* 8018BF30 00186E30  93 CD A1 90 */	stw r30, sInstance__16RPSysFontManager-_SDA_BASE_(r13)
/* 8018BF34 00186E34  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8018BF38 00186E38  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8018BF3C 00186E3C  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8018BF40 00186E40  83 81 00 10 */	lwz r28, 0x10(r1)
/* 8018BF44 00186E44  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8018BF48 00186E48  7C 08 03 A6 */	mtlr r0
/* 8018BF4C 00186E4C  38 21 00 20 */	addi r1, r1, 0x20
/* 8018BF50 00186E50  4E 80 00 20 */	blr 
