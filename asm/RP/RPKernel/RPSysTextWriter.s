.include "macros.inc"

.section .sdata2, "a"
.balign 0x8
.global lbl_804C1580
lbl_804C1580:
	.incbin "baserom.dol", 0x3CA1C0, 0x4
.global lbl_804C1584
lbl_804C1584:
	.incbin "baserom.dol", 0x3CA1C4, 0x4
.global lbl_804C1588
lbl_804C1588:
	.incbin "baserom.dol", 0x3CA1C8, 0x8
.global lbl_804C1590
lbl_804C1590:
	.incbin "baserom.dol", 0x3CA1D0, 0x8

.section .sbss, "wa"
.balign 0x8
.global sInstance__15RPSysTextWriter
sInstance__15RPSysTextWriter:
	.skip 0x4

.section .data, "wa"
.balign 0x8
.global __vt__15RPSysTextWriter
__vt__15RPSysTextWriter:
	.long 0
    .long 0
    .long __dt__15RPSysTextWriterFv

.section .text, "ax"
.global End__15RPSysTextWriterFv
End__15RPSysTextWriterFv:
/* 801908CC 0018B7CC  38 00 00 00 */	li r0, 0
/* 801908D0 0018B7D0  90 03 00 68 */	stw r0, 0x68(r3)
/* 801908D4 0018B7D4  4E 80 00 20 */	blr 

.global Begin__15RPSysTextWriterFv
Begin__15RPSysTextWriterFv:
/* 801908D8 0018B7D8  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 801908DC 0018B7DC  7C 08 02 A6 */	mflr r0
/* 801908E0 0018B7E0  90 01 00 44 */	stw r0, 0x44(r1)
/* 801908E4 0018B7E4  38 00 00 01 */	li r0, 1
/* 801908E8 0018B7E8  90 03 00 68 */	stw r0, 0x68(r3)
/* 801908EC 0018B7EC  4B E7 A7 E1 */	bl SetupGX__Q34nw4r2ut10CharWriterFv
/* 801908F0 0018B7F0  38 60 00 00 */	li r3, 0
/* 801908F4 0018B7F4  38 80 00 07 */	li r4, 7
/* 801908F8 0018B7F8  38 A0 00 00 */	li r5, 0
/* 801908FC 0018B7FC  4B F5 18 61 */	bl GXSetZMode
/* 80190900 0018B800  38 61 00 08 */	addi r3, r1, 8
/* 80190904 0018B804  4B F5 6C F5 */	bl PSMTXIdentity
/* 80190908 0018B808  80 6D A2 9C */	lwz r3, lbl_804BF61C-_SDA_BASE_(r13)
/* 8019090C 0018B80C  80 03 00 04 */	lwz r0, 4(r3)
/* 80190910 0018B810  2C 00 00 00 */	cmpwi r0, 0
/* 80190914 0018B814  40 82 00 28 */	bne lbl_8019093C
/* 80190918 0018B818  C0 41 00 0C */	lfs f2, 0xc(r1)
/* 8019091C 0018B81C  C0 21 00 1C */	lfs f1, 0x1c(r1)
/* 80190920 0018B820  C0 01 00 2C */	lfs f0, 0x2c(r1)
/* 80190924 0018B824  FC 40 10 50 */	fneg f2, f2
/* 80190928 0018B828  FC 20 08 50 */	fneg f1, f1
/* 8019092C 0018B82C  FC 00 00 50 */	fneg f0, f0
/* 80190930 0018B830  D0 41 00 0C */	stfs f2, 0xc(r1)
/* 80190934 0018B834  D0 21 00 1C */	stfs f1, 0x1c(r1)
/* 80190938 0018B838  D0 01 00 2C */	stfs f0, 0x2c(r1)
lbl_8019093C:
/* 8019093C 0018B83C  38 61 00 08 */	addi r3, r1, 8
/* 80190940 0018B840  38 80 00 00 */	li r4, 0
/* 80190944 0018B844  4B F5 29 39 */	bl GXLoadPosMtxImm
/* 80190948 0018B848  38 60 00 00 */	li r3, 0
/* 8019094C 0018B84C  4B F5 2A 39 */	bl GXSetCurrentMtx
/* 80190950 0018B850  80 01 00 44 */	lwz r0, 0x44(r1)
/* 80190954 0018B854  7C 08 03 A6 */	mtlr r0
/* 80190958 0018B858  38 21 00 40 */	addi r1, r1, 0x40
/* 8019095C 0018B85C  4E 80 00 20 */	blr 

.global PrintfZeroCenter__15RPSysTextWriterFffPCce
PrintfZeroCenter__15RPSysTextWriterFffPCce:
/* 80190960 0018B860  94 21 FF 60 */	stwu r1, -0xa0(r1)
/* 80190964 0018B864  7C 08 02 A6 */	mflr r0
/* 80190968 0018B868  90 01 00 A4 */	stw r0, 0xa4(r1)
/* 8019096C 0018B86C  93 E1 00 9C */	stw r31, 0x9c(r1)
/* 80190970 0018B870  93 C1 00 98 */	stw r30, 0x98(r1)
/* 80190974 0018B874  40 86 00 24 */	bne cr1, lbl_80190998
/* 80190978 0018B878  D8 21 00 28 */	stfd f1, 0x28(r1)
/* 8019097C 0018B87C  D8 41 00 30 */	stfd f2, 0x30(r1)
/* 80190980 0018B880  D8 61 00 38 */	stfd f3, 0x38(r1)
/* 80190984 0018B884  D8 81 00 40 */	stfd f4, 0x40(r1)
/* 80190988 0018B888  D8 A1 00 48 */	stfd f5, 0x48(r1)
/* 8019098C 0018B88C  D8 C1 00 50 */	stfd f6, 0x50(r1)
/* 80190990 0018B890  D8 E1 00 58 */	stfd f7, 0x58(r1)
/* 80190994 0018B894  D9 01 00 60 */	stfd f8, 0x60(r1)
lbl_80190998:
/* 80190998 0018B898  39 61 00 A8 */	addi r11, r1, 0xa8
/* 8019099C 0018B89C  38 01 00 08 */	addi r0, r1, 8
/* 801909A0 0018B8A0  3D 80 02 02 */	lis r12, 0x202
/* 801909A4 0018B8A4  90 61 00 08 */	stw r3, 8(r1)
/* 801909A8 0018B8A8  83 CD A2 9C */	lwz r30, lbl_804BF61C-_SDA_BASE_(r13)
/* 801909AC 0018B8AC  3F E0 43 30 */	lis r31, 0x4330
/* 801909B0 0018B8B0  90 81 00 0C */	stw r4, 0xc(r1)
/* 801909B4 0018B8B4  90 A1 00 10 */	stw r5, 0x10(r1)
/* 801909B8 0018B8B8  90 C1 00 14 */	stw r6, 0x14(r1)
/* 801909BC 0018B8BC  90 E1 00 18 */	stw r7, 0x18(r1)
/* 801909C0 0018B8C0  91 01 00 1C */	stw r8, 0x1c(r1)
/* 801909C4 0018B8C4  91 21 00 20 */	stw r9, 0x20(r1)
/* 801909C8 0018B8C8  91 41 00 24 */	stw r10, 0x24(r1)
/* 801909CC 0018B8CC  91 81 00 68 */	stw r12, 0x68(r1)
/* 801909D0 0018B8D0  91 61 00 6C */	stw r11, 0x6c(r1)
/* 801909D4 0018B8D4  90 01 00 70 */	stw r0, 0x70(r1)
/* 801909D8 0018B8D8  80 1E 00 04 */	lwz r0, 4(r30)
/* 801909DC 0018B8DC  93 E1 00 78 */	stw r31, 0x78(r1)
/* 801909E0 0018B8E0  2C 00 00 00 */	cmpwi r0, 0
/* 801909E4 0018B8E4  93 E1 00 80 */	stw r31, 0x80(r1)
/* 801909E8 0018B8E8  40 82 00 08 */	bne lbl_801909F0
/* 801909EC 0018B8EC  FC 40 10 50 */	fneg f2, f2
lbl_801909F0:
/* 801909F0 0018B8F0  80 1E 00 04 */	lwz r0, 4(r30)
/* 801909F4 0018B8F4  2C 00 00 01 */	cmpwi r0, 1
/* 801909F8 0018B8F8  41 82 00 70 */	beq lbl_80190A68
/* 801909FC 0018B8FC  40 80 00 D4 */	bge lbl_80190AD0
/* 80190A00 0018B900  2C 00 00 00 */	cmpwi r0, 0
/* 80190A04 0018B904  40 80 00 08 */	bge lbl_80190A0C
/* 80190A08 0018B908  48 00 00 C8 */	b lbl_80190AD0
lbl_80190A0C:
/* 80190A0C 0018B90C  C0 7E 00 08 */	lfs f3, 8(r30)
/* 80190A10 0018B910  C0 1E 00 0C */	lfs f0, 0xc(r30)
/* 80190A14 0018B914  FC 80 18 1E */	fctiwz f4, f3
/* 80190A18 0018B918  C8 A2 9B 68 */	lfd f5, lbl_804C1588-_SDA2_BASE_(r2)
/* 80190A1C 0018B91C  FC 00 00 1E */	fctiwz f0, f0
/* 80190A20 0018B920  C0 62 9B 60 */	lfs f3, lbl_804C1580-_SDA2_BASE_(r2)
/* 80190A24 0018B924  D8 81 00 88 */	stfd f4, 0x88(r1)
/* 80190A28 0018B928  D8 01 00 90 */	stfd f0, 0x90(r1)
/* 80190A2C 0018B92C  80 01 00 8C */	lwz r0, 0x8c(r1)
/* 80190A30 0018B930  80 C1 00 94 */	lwz r6, 0x94(r1)
/* 80190A34 0018B934  54 05 04 3E */	clrlwi r5, r0, 0x10
/* 80190A38 0018B938  54 C0 04 3E */	clrlwi r0, r6, 0x10
/* 80190A3C 0018B93C  90 A1 00 7C */	stw r5, 0x7c(r1)
/* 80190A40 0018B940  90 01 00 84 */	stw r0, 0x84(r1)
/* 80190A44 0018B944  C8 81 00 78 */	lfd f4, 0x78(r1)
/* 80190A48 0018B948  C8 01 00 80 */	lfd f0, 0x80(r1)
/* 80190A4C 0018B94C  EC 84 28 28 */	fsubs f4, f4, f5
/* 80190A50 0018B950  EC 00 28 28 */	fsubs f0, f0, f5
/* 80190A54 0018B954  EC 21 01 32 */	fmuls f1, f1, f4
/* 80190A58 0018B958  EC 02 00 32 */	fmuls f0, f2, f0
/* 80190A5C 0018B95C  EC 21 00 F2 */	fmuls f1, f1, f3
/* 80190A60 0018B960  EC 40 00 F2 */	fmuls f2, f0, f3
/* 80190A64 0018B964  48 00 00 6C */	b lbl_80190AD0
lbl_80190A68:
/* 80190A68 0018B968  C0 7E 00 08 */	lfs f3, 8(r30)
/* 80190A6C 0018B96C  FC 00 10 50 */	fneg f0, f2
/* 80190A70 0018B970  C0 5E 00 0C */	lfs f2, 0xc(r30)
/* 80190A74 0018B974  FC E0 18 1E */	fctiwz f7, f3
/* 80190A78 0018B978  C0 C2 9B 64 */	lfs f6, lbl_804C1584-_SDA2_BASE_(r2)
/* 80190A7C 0018B97C  FC 40 10 1E */	fctiwz f2, f2
/* 80190A80 0018B980  C8 82 9B 68 */	lfd f4, lbl_804C1588-_SDA2_BASE_(r2)
/* 80190A84 0018B984  EC A6 08 2A */	fadds f5, f6, f1
/* 80190A88 0018B988  C0 62 9B 60 */	lfs f3, lbl_804C1580-_SDA2_BASE_(r2)
/* 80190A8C 0018B98C  D8 E1 00 90 */	stfd f7, 0x90(r1)
/* 80190A90 0018B990  EC 26 00 2A */	fadds f1, f6, f0
/* 80190A94 0018B994  D8 41 00 88 */	stfd f2, 0x88(r1)
/* 80190A98 0018B998  80 01 00 94 */	lwz r0, 0x94(r1)
/* 80190A9C 0018B99C  80 C1 00 8C */	lwz r6, 0x8c(r1)
/* 80190AA0 0018B9A0  54 05 04 3E */	clrlwi r5, r0, 0x10
/* 80190AA4 0018B9A4  54 C0 04 3E */	clrlwi r0, r6, 0x10
/* 80190AA8 0018B9A8  90 A1 00 7C */	stw r5, 0x7c(r1)
/* 80190AAC 0018B9AC  90 01 00 84 */	stw r0, 0x84(r1)
/* 80190AB0 0018B9B0  C8 41 00 78 */	lfd f2, 0x78(r1)
/* 80190AB4 0018B9B4  C8 01 00 80 */	lfd f0, 0x80(r1)
/* 80190AB8 0018B9B8  EC 42 20 28 */	fsubs f2, f2, f4
/* 80190ABC 0018B9BC  EC 00 20 28 */	fsubs f0, f0, f4
/* 80190AC0 0018B9C0  EC 45 00 B2 */	fmuls f2, f5, f2
/* 80190AC4 0018B9C4  EC 01 00 32 */	fmuls f0, f1, f0
/* 80190AC8 0018B9C8  EC 22 00 F2 */	fmuls f1, f2, f3
/* 80190ACC 0018B9CC  EC 40 00 F2 */	fmuls f2, f0, f3
lbl_80190AD0:
/* 80190AD0 0018B9D0  D0 23 00 2C */	stfs f1, 0x2c(r3)
/* 80190AD4 0018B9D4  38 A1 00 68 */	addi r5, r1, 0x68
/* 80190AD8 0018B9D8  D0 43 00 30 */	stfs f2, 0x30(r3)
/* 80190ADC 0018B9DC  4B E7 BC 29 */	bl VPrintf__Q34nw4r2ut17TextWriterBase$$0c$$1FPCcP16__va_list_struct
/* 80190AE0 0018B9E0  80 01 00 A4 */	lwz r0, 0xa4(r1)
/* 80190AE4 0018B9E4  83 E1 00 9C */	lwz r31, 0x9c(r1)
/* 80190AE8 0018B9E8  83 C1 00 98 */	lwz r30, 0x98(r1)
/* 80190AEC 0018B9EC  7C 08 03 A6 */	mtlr r0
/* 80190AF0 0018B9F0  38 21 00 A0 */	addi r1, r1, 0xa0
/* 80190AF4 0018B9F4  4E 80 00 20 */	blr 

.global Printf__15RPSysTextWriterFffPCce
Printf__15RPSysTextWriterFffPCce:
/* 80190AF8 0018B9F8  94 21 FF 80 */	stwu r1, -0x80(r1)
/* 80190AFC 0018B9FC  7C 08 02 A6 */	mflr r0
/* 80190B00 0018BA00  90 01 00 84 */	stw r0, 0x84(r1)
/* 80190B04 0018BA04  93 E1 00 7C */	stw r31, 0x7c(r1)
/* 80190B08 0018BA08  40 86 00 24 */	bne cr1, lbl_80190B2C
/* 80190B0C 0018BA0C  D8 21 00 28 */	stfd f1, 0x28(r1)
/* 80190B10 0018BA10  D8 41 00 30 */	stfd f2, 0x30(r1)
/* 80190B14 0018BA14  D8 61 00 38 */	stfd f3, 0x38(r1)
/* 80190B18 0018BA18  D8 81 00 40 */	stfd f4, 0x40(r1)
/* 80190B1C 0018BA1C  D8 A1 00 48 */	stfd f5, 0x48(r1)
/* 80190B20 0018BA20  D8 C1 00 50 */	stfd f6, 0x50(r1)
/* 80190B24 0018BA24  D8 E1 00 58 */	stfd f7, 0x58(r1)
/* 80190B28 0018BA28  D9 01 00 60 */	stfd f8, 0x60(r1)
lbl_80190B2C:
/* 80190B2C 0018BA2C  39 81 00 88 */	addi r12, r1, 0x88
/* 80190B30 0018BA30  38 01 00 08 */	addi r0, r1, 8
/* 80190B34 0018BA34  3F E0 02 02 */	lis r31, 0x202
/* 80190B38 0018BA38  90 61 00 08 */	stw r3, 8(r1)
/* 80190B3C 0018BA3C  81 6D A2 9C */	lwz r11, lbl_804BF61C-_SDA_BASE_(r13)
/* 80190B40 0018BA40  90 81 00 0C */	stw r4, 0xc(r1)
/* 80190B44 0018BA44  90 A1 00 10 */	stw r5, 0x10(r1)
/* 80190B48 0018BA48  90 C1 00 14 */	stw r6, 0x14(r1)
/* 80190B4C 0018BA4C  90 E1 00 18 */	stw r7, 0x18(r1)
/* 80190B50 0018BA50  91 01 00 1C */	stw r8, 0x1c(r1)
/* 80190B54 0018BA54  91 21 00 20 */	stw r9, 0x20(r1)
/* 80190B58 0018BA58  91 41 00 24 */	stw r10, 0x24(r1)
/* 80190B5C 0018BA5C  93 E1 00 68 */	stw r31, 0x68(r1)
/* 80190B60 0018BA60  91 81 00 6C */	stw r12, 0x6c(r1)
/* 80190B64 0018BA64  90 01 00 70 */	stw r0, 0x70(r1)
/* 80190B68 0018BA68  80 0B 00 04 */	lwz r0, 4(r11)
/* 80190B6C 0018BA6C  2C 00 00 00 */	cmpwi r0, 0
/* 80190B70 0018BA70  40 82 00 08 */	bne lbl_80190B78
/* 80190B74 0018BA74  FC 40 10 50 */	fneg f2, f2
lbl_80190B78:
/* 80190B78 0018BA78  D0 23 00 2C */	stfs f1, 0x2c(r3)
/* 80190B7C 0018BA7C  38 A1 00 68 */	addi r5, r1, 0x68
/* 80190B80 0018BA80  D0 43 00 30 */	stfs f2, 0x30(r3)
/* 80190B84 0018BA84  4B E7 BB 81 */	bl VPrintf__Q34nw4r2ut17TextWriterBase$$0c$$1FPCcP16__va_list_struct
/* 80190B88 0018BA88  80 01 00 84 */	lwz r0, 0x84(r1)
/* 80190B8C 0018BA8C  83 E1 00 7C */	lwz r31, 0x7c(r1)
/* 80190B90 0018BA90  7C 08 03 A6 */	mtlr r0
/* 80190B94 0018BA94  38 21 00 80 */	addi r1, r1, 0x80
/* 80190B98 0018BA98  4E 80 00 20 */	blr 

.global Reset__15RPSysTextWriterFv
Reset__15RPSysTextWriterFv:
/* 80190B9C 0018BA9C  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 80190BA0 0018BAA0  7C 08 02 A6 */	mflr r0
/* 80190BA4 0018BAA4  90 01 00 34 */	stw r0, 0x34(r1)
/* 80190BA8 0018BAA8  38 00 00 FF */	li r0, 0xff
/* 80190BAC 0018BAAC  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 80190BB0 0018BAB0  93 C1 00 28 */	stw r30, 0x28(r1)
/* 80190BB4 0018BAB4  93 A1 00 24 */	stw r29, 0x24(r1)
/* 80190BB8 0018BAB8  7C 7D 1B 78 */	mr r29, r3
/* 80190BBC 0018BABC  98 03 00 42 */	stb r0, 0x42(r3)
/* 80190BC0 0018BAC0  4B E7 B5 79 */	bl UpdateVertexColor__Q34nw4r2ut10CharWriterFv
/* 80190BC4 0018BAC4  C0 02 9B 70 */	lfs f0, lbl_804C1590-_SDA2_BASE_(r2)
/* 80190BC8 0018BAC8  3B C0 00 00 */	li r30, 0
/* 80190BCC 0018BACC  9B DD 00 43 */	stb r30, 0x43(r29)
/* 80190BD0 0018BAD0  3B E0 FF FF */	li r31, -1
/* 80190BD4 0018BAD4  7F A3 EB 78 */	mr r3, r29
/* 80190BD8 0018BAD8  38 81 00 08 */	addi r4, r1, 8
/* 80190BDC 0018BADC  D0 1D 00 44 */	stfs f0, 0x44(r29)
/* 80190BE0 0018BAE0  38 A1 00 0C */	addi r5, r1, 0xc
/* 80190BE4 0018BAE4  93 C1 00 08 */	stw r30, 8(r1)
/* 80190BE8 0018BAE8  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80190BEC 0018BAEC  4B E7 A2 FD */	bl SetColorMapping__Q34nw4r2ut10CharWriterFQ34nw4r2ut5ColorQ34nw4r2ut5Color
/* 80190BF0 0018BAF0  93 DD 00 20 */	stw r30, 0x20(r29)
/* 80190BF4 0018BAF4  7F A3 EB 78 */	mr r3, r29
/* 80190BF8 0018BAF8  4B E7 B5 41 */	bl UpdateVertexColor__Q34nw4r2ut10CharWriterFv
/* 80190BFC 0018BAFC  93 E1 00 10 */	stw r31, 0x10(r1)
/* 80190C00 0018BB00  7F A3 EB 78 */	mr r3, r29
/* 80190C04 0018BB04  38 81 00 10 */	addi r4, r1, 0x10
/* 80190C08 0018BB08  4B E7 A3 25 */	bl SetTextColor__Q34nw4r2ut10CharWriterFQ34nw4r2ut5Color
/* 80190C0C 0018BB0C  C0 02 9B 70 */	lfs f0, lbl_804C1590-_SDA2_BASE_(r2)
/* 80190C10 0018BB10  7F A3 EB 78 */	mr r3, r29
/* 80190C14 0018BB14  C0 22 9B 64 */	lfs f1, lbl_804C1584-_SDA2_BASE_(r2)
/* 80190C18 0018BB18  38 80 00 01 */	li r4, 1
/* 80190C1C 0018BB1C  D0 1D 00 2C */	stfs f0, 0x2c(r29)
/* 80190C20 0018BB20  38 A0 00 01 */	li r5, 1
/* 80190C24 0018BB24  D0 3D 00 24 */	stfs f1, 0x24(r29)
/* 80190C28 0018BB28  D0 3D 00 28 */	stfs f1, 0x28(r29)
/* 80190C2C 0018BB2C  D0 1D 00 30 */	stfs f0, 0x30(r29)
/* 80190C30 0018BB30  D0 1D 00 34 */	stfs f0, 0x34(r29)
/* 80190C34 0018BB34  4B E7 B1 35 */	bl EnableLinearFilter__Q34nw4r2ut10CharWriterFbb
/* 80190C38 0018BB38  C0 02 9B 70 */	lfs f0, lbl_804C1590-_SDA2_BASE_(r2)
/* 80190C3C 0018BB3C  38 00 00 04 */	li r0, 4
/* 80190C40 0018BB40  90 1D 00 58 */	stw r0, 0x58(r29)
/* 80190C44 0018BB44  D0 1D 00 50 */	stfs f0, 0x50(r29)
/* 80190C48 0018BB48  D0 1D 00 54 */	stfs f0, 0x54(r29)
/* 80190C4C 0018BB4C  93 DD 00 5C */	stw r30, 0x5c(r29)
/* 80190C50 0018BB50  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 80190C54 0018BB54  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 80190C58 0018BB58  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 80190C5C 0018BB5C  80 01 00 34 */	lwz r0, 0x34(r1)
/* 80190C60 0018BB60  7C 08 03 A6 */	mtlr r0
/* 80190C64 0018BB64  38 21 00 30 */	addi r1, r1, 0x30
/* 80190C68 0018BB68  4E 80 00 20 */	blr 

.global __dt__15RPSysTextWriterFv
__dt__15RPSysTextWriterFv:
/* 80190C6C 0018BB6C  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80190C70 0018BB70  7C 08 02 A6 */	mflr r0
/* 80190C74 0018BB74  2C 03 00 00 */	cmpwi r3, 0
/* 80190C78 0018BB78  90 01 00 14 */	stw r0, 0x14(r1)
/* 80190C7C 0018BB7C  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80190C80 0018BB80  7C 9F 23 78 */	mr r31, r4
/* 80190C84 0018BB84  93 C1 00 08 */	stw r30, 8(r1)
/* 80190C88 0018BB88  7C 7E 1B 78 */	mr r30, r3
/* 80190C8C 0018BB8C  41 82 00 1C */	beq lbl_80190CA8
/* 80190C90 0018BB90  38 80 00 00 */	li r4, 0
/* 80190C94 0018BB94  4B E7 B9 9D */	bl __dt__Q34nw4r2ut17TextWriterBase$$0c$$1Fv
/* 80190C98 0018BB98  2C 1F 00 00 */	cmpwi r31, 0
/* 80190C9C 0018BB9C  40 81 00 0C */	ble lbl_80190CA8
/* 80190CA0 0018BBA0  7F C3 F3 78 */	mr r3, r30
/* 80190CA4 0018BBA4  4B F1 25 E1 */	bl __dl__FPv
lbl_80190CA8:
/* 80190CA8 0018BBA8  7F C3 F3 78 */	mr r3, r30
/* 80190CAC 0018BBAC  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80190CB0 0018BBB0  83 C1 00 08 */	lwz r30, 8(r1)
/* 80190CB4 0018BBB4  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80190CB8 0018BBB8  7C 08 03 A6 */	mtlr r0
/* 80190CBC 0018BBBC  38 21 00 10 */	addi r1, r1, 0x10
/* 80190CC0 0018BBC0  4E 80 00 20 */	blr 

.global CreateInstance__15RPSysTextWriterFv
CreateInstance__15RPSysTextWriterFv:
/* 80190CC4 0018BBC4  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80190CC8 0018BBC8  7C 08 02 A6 */	mflr r0
/* 80190CCC 0018BBCC  38 60 00 6C */	li r3, 0x6c
/* 80190CD0 0018BBD0  90 01 00 14 */	stw r0, 0x14(r1)
/* 80190CD4 0018BBD4  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80190CD8 0018BBD8  4B F1 25 6D */	bl __nw__FUl
/* 80190CDC 0018BBDC  2C 03 00 00 */	cmpwi r3, 0
/* 80190CE0 0018BBE0  7C 7F 1B 78 */	mr r31, r3
/* 80190CE4 0018BBE4  41 82 00 28 */	beq lbl_80190D0C
/* 80190CE8 0018BBE8  4B E7 B8 ED */	bl __ct__Q34nw4r2ut17TextWriterBase$$0c$$1Fv
/* 80190CEC 0018BBEC  3C 60 80 3C */	lis r3, __vt__15RPSysTextWriter@ha
/* 80190CF0 0018BBF0  38 00 00 00 */	li r0, 0
/* 80190CF4 0018BBF4  38 63 99 C0 */	addi r3, r3, __vt__15RPSysTextWriter@l
/* 80190CF8 0018BBF8  90 7F 00 64 */	stw r3, 0x64(r31)
/* 80190CFC 0018BBFC  80 6D A1 90 */	lwz r3, sInstance__16RPSysFontManager-_SDA_BASE_(r13)
/* 80190D00 0018BC00  80 63 00 04 */	lwz r3, 4(r3)
/* 80190D04 0018BC04  90 7F 00 48 */	stw r3, 0x48(r31)
/* 80190D08 0018BC08  90 1F 00 68 */	stw r0, 0x68(r31)
lbl_80190D0C:
/* 80190D0C 0018BC0C  93 ED A1 B8 */	stw r31, sInstance__15RPSysTextWriter-_SDA_BASE_(r13)
/* 80190D10 0018BC10  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80190D14 0018BC14  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80190D18 0018BC18  7C 08 03 A6 */	mtlr r0
/* 80190D1C 0018BC1C  38 21 00 10 */	addi r1, r1, 0x10
/* 80190D20 0018BC20  4E 80 00 20 */	blr 