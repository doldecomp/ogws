.include "macros.inc"

.section .sdata2, "a"
.balign 0x8
.global lbl_804C0728
lbl_804C0728:
	.incbin "baserom.dol", 0x3C9368, 0x2
.global lbl_804C072A
lbl_804C072A:
	.incbin "baserom.dol", 0x3C936A, 0x6

.section .sbss, "wa"
.balign 0x8
.global spInstance__Q23EGG9GfxEngine
spInstance__Q23EGG9GfxEngine:
	.skip 0x8

.section .rodata, "a"
.balign 0x8
.global lbl_80379490
lbl_80379490:
	.string "eggGfxEngine.cpp"
    .string "spInstance == NULL"
    .string "spInstance"
    .string "interlace < cVFilter_Max"
    .string "progressive < cVFilter_Max"
    
.section .data, "wa"
.balign 0x8
.global __vt__Q23EGG9GfxEngine
__vt__Q23EGG9GfxEngine:
    .long 0
    .long 0
    .long __dt__Q23EGG9GfxEngine
    .long 0

.section .text, "ax"
# GfxEngine::initialize() ???
# (Unofficial symbol)
.global func_8008FCEC
func_8008FCEC:
/* 8008FCEC 0008ABEC  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8008FCF0 0008ABF0  7C 08 02 A6 */	mflr r0
/* 8008FCF4 0008ABF4  90 01 00 24 */	stw r0, 0x24(r1)
/* 8008FCF8 0008ABF8  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8008FCFC 0008ABFC  7C BF 2B 78 */	mr r31, r5
/* 8008FD00 0008AC00  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8008FD04 0008AC04  7C 9E 23 78 */	mr r30, r4
/* 8008FD08 0008AC08  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8008FD0C 0008AC0C  7C 7D 1B 78 */	mr r29, r3
/* 8008FD10 0008AC10  80 0D 98 80 */	lwz r0, spInstance__Q23EGG9GfxEngine-_SDA_BASE_(r13)
/* 8008FD14 0008AC14  2C 00 00 00 */	cmpwi r0, 0
/* 8008FD18 0008AC18  41 82 00 1C */	beq lbl_8008FD34
/* 8008FD1C 0008AC1C  3C 60 80 38 */	lis r3, lbl_80379490@ha
/* 8008FD20 0008AC20  38 80 00 2B */	li r4, 0x2b
/* 8008FD24 0008AC24  38 63 94 90 */	addi r3, r3, lbl_80379490@l
/* 8008FD28 0008AC28  38 A3 00 11 */	addi r5, r3, 0x11
/* 8008FD2C 0008AC2C  4C C6 31 82 */	crclr 6
/* 8008FD30 0008AC30  48 01 21 D9 */	bl system_halt
lbl_8008FD34:
/* 8008FD34 0008AC34  2C 1F 00 00 */	cmpwi r31, 0
/* 8008FD38 0008AC38  40 82 00 08 */	bne lbl_8008FD40
/* 8008FD3C 0008AC3C  83 ED 99 28 */	lwz r31, sCurrentHeap__Q23EGG4Heap-_SDA_BASE_(r13)
lbl_8008FD40:
/* 8008FD40 0008AC40  7F E4 FB 78 */	mr r4, r31
/* 8008FD44 0008AC44  38 60 00 0C */	li r3, 0xc
/* 8008FD48 0008AC48  38 A0 00 04 */	li r5, 4
/* 8008FD4C 0008AC4C  48 01 35 05 */	bl __nw__FUlPQ23EGG4Heapi
/* 8008FD50 0008AC50  2C 03 00 00 */	cmpwi r3, 0
/* 8008FD54 0008AC54  41 82 00 08 */	beq lbl_8008FD5C
/* 8008FD58 0008AC58  48 00 01 41 */	bl __ct__Q23EGG9GfxEngineFv
lbl_8008FD5C:
/* 8008FD5C 0008AC5C  2C 03 00 00 */	cmpwi r3, 0
/* 8008FD60 0008AC60  90 6D 98 80 */	stw r3, spInstance__Q23EGG9GfxEngine-_SDA_BASE_(r13)
/* 8008FD64 0008AC64  40 82 00 1C */	bne lbl_8008FD80
/* 8008FD68 0008AC68  3C 60 80 38 */	lis r3, lbl_80379490@ha
/* 8008FD6C 0008AC6C  38 80 00 38 */	li r4, 0x38
/* 8008FD70 0008AC70  38 63 94 90 */	addi r3, r3, lbl_80379490@l
/* 8008FD74 0008AC74  38 A3 00 24 */	addi r5, r3, 0x24
/* 8008FD78 0008AC78  4C C6 31 82 */	crclr 6
/* 8008FD7C 0008AC7C  48 01 21 8D */	bl system_halt
lbl_8008FD80:
/* 8008FD80 0008AC80  4B FF 40 99 */	bl func_80083E18
/* 8008FD84 0008AC84  A0 C2 8D 08 */	lhz r6, lbl_804C0728-_SDA2_BASE_(r2)
/* 8008FD88 0008AC88  38 61 00 0C */	addi r3, r1, 0xc
/* 8008FD8C 0008AC8C  A0 02 8D 0A */	lhz r0, lbl_804C072A-_SDA2_BASE_(r2)
/* 8008FD90 0008AC90  38 81 00 08 */	addi r4, r1, 8
/* 8008FD94 0008AC94  B3 AD 98 30 */	sth r29, lbl_804BEBB0-_SDA_BASE_(r13)
/* 8008FD98 0008AC98  38 A0 00 00 */	li r5, 0
/* 8008FD9C 0008AC9C  B3 CD 98 32 */	sth r30, lbl_804BEBB2-_SDA_BASE_(r13)
/* 8008FDA0 0008ACA0  B0 C1 00 0C */	sth r6, 0xc(r1)
/* 8008FDA4 0008ACA4  B0 01 00 0E */	sth r0, 0xe(r1)
/* 8008FDA8 0008ACA8  B3 C1 00 08 */	sth r30, 8(r1)
/* 8008FDAC 0008ACAC  B3 C1 00 0A */	sth r30, 0xa(r1)
/* 8008FDB0 0008ACB0  48 00 98 1D */	bl func_800995CC
/* 8008FDB4 0008ACB4  48 00 AE B1 */	bl func_8009AC64
/* 8008FDB8 0008ACB8  7F E4 FB 78 */	mr r4, r31
/* 8008FDBC 0008ACBC  38 60 60 00 */	li r3, 0x6000
/* 8008FDC0 0008ACC0  4B FF F5 75 */	bl func_8008F334
/* 8008FDC4 0008ACC4  7F E3 FB 78 */	mr r3, r31
/* 8008FDC8 0008ACC8  4B FF 7A 65 */	bl func_8008782C
/* 8008FDCC 0008ACCC  7F E4 FB 78 */	mr r4, r31
/* 8008FDD0 0008ACD0  38 60 00 20 */	li r3, 0x20
/* 8008FDD4 0008ACD4  48 00 1B 4D */	bl func_80091920
/* 8008FDD8 0008ACD8  7C 1D F1 D6 */	mullw r0, r29, r30
/* 8008FDDC 0008ACDC  7F E4 FB 78 */	mr r4, r31
/* 8008FDE0 0008ACE0  1C 60 00 0C */	mulli r3, r0, 0xc
/* 8008FDE4 0008ACE4  4B FF 51 95 */	bl initialize__Q23EGG13TextureBufferFUlPQ23EGG4Heap
/* 8008FDE8 0008ACE8  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8008FDEC 0008ACEC  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8008FDF0 0008ACF0  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8008FDF4 0008ACF4  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8008FDF8 0008ACF8  7C 08 03 A6 */	mtlr r0
/* 8008FDFC 0008ACFC  38 21 00 20 */	addi r1, r1, 0x20
/* 8008FE00 0008AD00  4E 80 00 20 */	blr 

.global func_8008FE04
func_8008FE04:
/* 8008FE04 0008AD04  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8008FE08 0008AD08  7C 08 02 A6 */	mflr r0
/* 8008FE0C 0008AD0C  90 01 00 14 */	stw r0, 0x14(r1)
/* 8008FE10 0008AD10  4B FF 40 4D */	bl func_80083E5C
/* 8008FE14 0008AD14  4B FF 40 A9 */	bl func_80083EBC
/* 8008FE18 0008AD18  80 6D 99 38 */	lwz r3, mConfigData__Q23EGG10BaseSystem-_SDA_BASE_(r13)
/* 8008FE1C 0008AD1C  81 83 00 00 */	lwz r12, 0(r3)
/* 8008FE20 0008AD20  81 8C 00 10 */	lwz r12, 0x10(r12)
/* 8008FE24 0008AD24  7D 89 03 A6 */	mtctr r12
/* 8008FE28 0008AD28  4E 80 04 21 */	bctrl 
/* 8008FE2C 0008AD2C  7C 64 1B 78 */	mr r4, r3
/* 8008FE30 0008AD30  38 61 00 08 */	addi r3, r1, 8
/* 8008FE34 0008AD34  48 00 00 41 */	bl func_8008FE74
/* 8008FE38 0008AD38  88 E1 00 08 */	lbz r7, 8(r1)
/* 8008FE3C 0008AD3C  38 00 00 00 */	li r0, 0
/* 8008FE40 0008AD40  88 C1 00 09 */	lbz r6, 9(r1)
/* 8008FE44 0008AD44  38 AD 98 44 */	addi r5, r13, sDefaultTexColor__Q23EGG7StateGX-_SDA_BASE_
/* 8008FE48 0008AD48  88 81 00 0A */	lbz r4, 0xa(r1)
/* 8008FE4C 0008AD4C  88 61 00 0B */	lbz r3, 0xb(r1)
/* 8008FE50 0008AD50  98 ED 98 44 */	stb r7, sDefaultTexColor__Q23EGG7StateGX-_SDA_BASE_(r13)
/* 8008FE54 0008AD54  98 C5 00 01 */	stb r6, 1(r5)
/* 8008FE58 0008AD58  98 85 00 02 */	stb r4, 2(r5)
/* 8008FE5C 0008AD5C  98 65 00 03 */	stb r3, 3(r5)
/* 8008FE60 0008AD60  90 0D 98 74 */	stw r0, sTempMemIndex__Q23EGG10G3DUtility-_SDA_BASE_(r13)
/* 8008FE64 0008AD64  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8008FE68 0008AD68  7C 08 03 A6 */	mtlr r0
/* 8008FE6C 0008AD6C  38 21 00 10 */	addi r1, r1, 0x10
/* 8008FE70 0008AD70  4E 80 00 20 */	blr 

# EGG::Display::getColor (weak)
.global func_8008FE74
func_8008FE74:
/* 8008FE74 0008AD74  88 E4 00 14 */	lbz r7, 0x14(r4)
/* 8008FE78 0008AD78  88 C4 00 15 */	lbz r6, 0x15(r4)
/* 8008FE7C 0008AD7C  88 A4 00 16 */	lbz r5, 0x16(r4)
/* 8008FE80 0008AD80  88 04 00 17 */	lbz r0, 0x17(r4)
/* 8008FE84 0008AD84  98 E3 00 00 */	stb r7, 0(r3)
/* 8008FE88 0008AD88  98 C3 00 01 */	stb r6, 1(r3)
/* 8008FE8C 0008AD8C  98 A3 00 02 */	stb r5, 2(r3)
/* 8008FE90 0008AD90  98 03 00 03 */	stb r0, 3(r3)
/* 8008FE94 0008AD94  4E 80 00 20 */	blr 

.global __ct__Q23EGG9GfxEngineFv
__ct__Q23EGG9GfxEngineFv:
/* 8008FE98 0008AD98  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8008FE9C 0008AD9C  7C 08 02 A6 */	mflr r0
/* 8008FEA0 0008ADA0  3C 80 80 39 */	lis r4, __vt__Q23EGG9GfxEngine@ha
/* 8008FEA4 0008ADA4  90 01 00 14 */	stw r0, 0x14(r1)
/* 8008FEA8 0008ADA8  38 00 00 00 */	li r0, 0
/* 8008FEAC 0008ADAC  38 84 79 40 */	addi r4, r4, __vt__Q23EGG9GfxEngine@l
/* 8008FEB0 0008ADB0  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8008FEB4 0008ADB4  7C 7F 1B 78 */	mr r31, r3
/* 8008FEB8 0008ADB8  90 03 00 00 */	stw r0, 0(r3)
/* 8008FEBC 0008ADBC  90 83 00 08 */	stw r4, 8(r3)
/* 8008FEC0 0008ADC0  38 60 00 01 */	li r3, 1
/* 8008FEC4 0008ADC4  48 01 33 81 */	bl __nw__FUl
/* 8008FEC8 0008ADC8  90 7F 00 00 */	stw r3, 0(r31)
/* 8008FECC 0008ADCC  7F E3 FB 78 */	mr r3, r31
/* 8008FED0 0008ADD0  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8008FED4 0008ADD4  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8008FED8 0008ADD8  7C 08 03 A6 */	mtlr r0
/* 8008FEDC 0008ADDC  38 21 00 10 */	addi r1, r1, 0x10
/* 8008FEE0 0008ADE0  4E 80 00 20 */	blr 

.global __dt__Q23EGG9GfxEngine
__dt__Q23EGG9GfxEngine:
/* 8008FEE4 0008ADE4  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8008FEE8 0008ADE8  7C 08 02 A6 */	mflr r0
/* 8008FEEC 0008ADEC  2C 03 00 00 */	cmpwi r3, 0
/* 8008FEF0 0008ADF0  90 01 00 14 */	stw r0, 0x14(r1)
/* 8008FEF4 0008ADF4  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8008FEF8 0008ADF8  7C 7F 1B 78 */	mr r31, r3
/* 8008FEFC 0008ADFC  41 82 00 10 */	beq lbl_8008FF0C
/* 8008FF00 0008AE00  2C 04 00 00 */	cmpwi r4, 0
/* 8008FF04 0008AE04  40 81 00 08 */	ble lbl_8008FF0C
/* 8008FF08 0008AE08  48 01 33 7D */	bl __dl__FPv
lbl_8008FF0C:
/* 8008FF0C 0008AE0C  7F E3 FB 78 */	mr r3, r31
/* 8008FF10 0008AE10  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8008FF14 0008AE14  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8008FF18 0008AE18  7C 08 03 A6 */	mtlr r0
/* 8008FF1C 0008AE1C  38 21 00 10 */	addi r1, r1, 0x10
/* 8008FF20 0008AE20  4E 80 00 20 */	blr 
