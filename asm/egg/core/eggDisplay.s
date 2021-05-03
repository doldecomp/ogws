.include "macros.inc"

.section .text, "ax"

.global __ct__Q23EGG7DisplayFUc
__ct__Q23EGG7DisplayFUc:
/* 800A9FC0 000A4EC0  38 E0 00 00 */	li r7, 0
/* 800A9FC4 000A4EC4  3D 00 80 3A */	lis r8, lbl_80398350@ha
/* 800A9FC8 000A4EC8  3C C0 80 81 */	lis r6, 0x808080FF@ha
/* 800A9FCC 000A4ECC  3C A0 01 00 */	lis r5, 0x00FFFFFF@ha
/* 800A9FD0 000A4ED0  39 08 83 50 */	addi r8, r8, lbl_80398350@l
/* 800A9FD4 000A4ED4  60 E0 00 01 */	ori r0, r7, 1
/* 800A9FD8 000A4ED8  38 C6 80 FF */	addi r6, r6, 0x808080FF@l
/* 800A9FDC 000A4EDC  38 A5 FF FF */	addi r5, r5, 0x00FFFFFF@l
/* 800A9FE0 000A4EE0  91 03 00 04 */	stw r8, 4(r3)
/* 800A9FE4 000A4EE4  98 83 00 08 */	stb r4, 8(r3)
/* 800A9FE8 000A4EE8  98 E3 00 09 */	stb r7, 9(r3)
/* 800A9FEC 000A4EEC  90 E3 00 0C */	stw r7, 0xc(r3)
/* 800A9FF0 000A4EF0  90 E3 00 10 */	stw r7, 0x10(r3)
/* 800A9FF4 000A4EF4  90 C3 00 14 */	stw r6, 0x14(r3)
/* 800A9FF8 000A4EF8  90 A3 00 18 */	stw r5, 0x18(r3)
/* 800A9FFC 000A4EFC  90 E3 00 1C */	stw r7, 0x1c(r3)
/* 800AA000 000A4F00  98 03 00 00 */	stb r0, 0(r3)
/* 800AA004 000A4F04  4E 80 00 20 */	blr 

.global getTickPerFrame__Q23EGG7DisplayFv
getTickPerFrame__Q23EGG7DisplayFv:
/* 800AA008 000A4F08  48 00 05 44 */	b getTickPerVRetrace__Q23EGG5VideoFv

.global beginFrame__Q23EGG7DisplayFv
beginFrame__Q23EGG7DisplayFv:
/* 800AA00C 000A4F0C  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 800AA010 000A4F10  7C 08 02 A6 */	mflr r0
/* 800AA014 000A4F14  90 01 00 34 */	stw r0, 0x34(r1)
/* 800AA018 000A4F18  39 61 00 30 */	addi r11, r1, 0x30
/* 800AA01C 000A4F1C  48 00 7D 29 */	bl _savegpr_27
/* 800AA020 000A4F20  8B E3 00 08 */	lbz r31, 8(r3)
/* 800AA024 000A4F24  7C 7C 1B 78 */	mr r28, r3
/* 800AA028 000A4F28  48 05 24 4D */	bl func_800FC474
/* 800AA02C 000A4F2C  80 1C 00 0C */	lwz r0, 0xc(r28)
/* 800AA030 000A4F30  3B BF FF FF */	addi r29, r31, -1
/* 800AA034 000A4F34  7F C0 18 50 */	subf r30, r0, r3
lbl_800AA038:
/* 800AA038 000A4F38  7C 1E E8 40 */	cmplw r30, r29
/* 800AA03C 000A4F3C  41 80 00 88 */	blt lbl_800AA0C4
/* 800AA040 000A4F40  88 1C 00 09 */	lbz r0, 9(r28)
/* 800AA044 000A4F44  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 800AA048 000A4F48  41 82 00 64 */	beq lbl_800AA0AC
/* 800AA04C 000A4F4C  80 6D 99 38 */	lwz r3, lbl_804BECB8-_SDA_BASE_(r13)
/* 800AA050 000A4F50  81 83 00 00 */	lwz r12, 0(r3)
/* 800AA054 000A4F54  81 8C 00 08 */	lwz r12, 8(r12)
/* 800AA058 000A4F58  7D 89 03 A6 */	mtctr r12
/* 800AA05C 000A4F5C  4E 80 04 21 */	bctrl 
/* 800AA060 000A4F60  88 03 00 04 */	lbz r0, 4(r3)
/* 800AA064 000A4F64  7C 7B 1B 78 */	mr r27, r3
/* 800AA068 000A4F68  54 00 07 FE */	clrlwi r0, r0, 0x1f
/* 800AA06C 000A4F6C  7C 00 00 34 */	cntlzw r0, r0
/* 800AA070 000A4F70  54 03 D9 7E */	srwi r3, r0, 5
/* 800AA074 000A4F74  48 05 23 89 */	bl func_800FC3FC
/* 800AA078 000A4F78  88 1B 00 04 */	lbz r0, 4(r27)
/* 800AA07C 000A4F7C  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 800AA080 000A4F80  40 82 00 14 */	bne lbl_800AA094
/* 800AA084 000A4F84  88 1B 00 04 */	lbz r0, 4(r27)
/* 800AA088 000A4F88  60 00 00 01 */	ori r0, r0, 1
/* 800AA08C 000A4F8C  98 1B 00 04 */	stb r0, 4(r27)
/* 800AA090 000A4F90  48 00 00 10 */	b lbl_800AA0A0
lbl_800AA094:
/* 800AA094 000A4F94  88 1B 00 04 */	lbz r0, 4(r27)
/* 800AA098 000A4F98  54 00 06 3C */	rlwinm r0, r0, 0, 0x18, 0x1e
/* 800AA09C 000A4F9C  98 1B 00 04 */	stb r0, 4(r27)
lbl_800AA0A0:
/* 800AA0A0 000A4FA0  88 1C 00 09 */	lbz r0, 9(r28)
/* 800AA0A4 000A4FA4  54 00 06 3C */	rlwinm r0, r0, 0, 0x18, 0x1e
/* 800AA0A8 000A4FA8  98 1C 00 09 */	stb r0, 9(r28)
lbl_800AA0AC:
/* 800AA0AC 000A4FAC  80 6D 99 38 */	lwz r3, lbl_804BECB8-_SDA_BASE_(r13)
/* 800AA0B0 000A4FB0  81 83 00 00 */	lwz r12, 0(r3)
/* 800AA0B4 000A4FB4  81 8C 00 14 */	lwz r12, 0x14(r12)
/* 800AA0B8 000A4FB8  7D 89 03 A6 */	mtctr r12
/* 800AA0BC 000A4FBC  4E 80 04 21 */	bctrl 
/* 800AA0C0 000A4FC0  48 00 08 35 */	bl setNextFrameBuffer__Q23EGG10XfbManagerFv
lbl_800AA0C4:
/* 800AA0C4 000A4FC4  48 05 12 2D */	bl func_800FB2F0
/* 800AA0C8 000A4FC8  3B DE 00 01 */	addi r30, r30, 1
/* 800AA0CC 000A4FCC  7C 1E F8 40 */	cmplw r30, r31
/* 800AA0D0 000A4FD0  41 80 FF 68 */	blt lbl_800AA038
/* 800AA0D4 000A4FD4  48 04 B5 49 */	bl func_800F561C
/* 800AA0D8 000A4FD8  80 DC 00 1C */	lwz r6, 0x1c(r28)
/* 800AA0DC 000A4FDC  3C 00 43 30 */	lis r0, 0x4330
/* 800AA0E0 000A4FE0  3C 80 43 1C */	lis r4, 0x431BDE83@ha
/* 800AA0E4 000A4FE4  3C A0 80 00 */	lis r5, 0x800000F8@ha
/* 800AA0E8 000A4FE8  7C E6 18 50 */	subf r7, r6, r3
/* 800AA0EC 000A4FEC  90 01 00 08 */	stw r0, 8(r1)
/* 800AA0F0 000A4FF0  38 C4 DE 83 */	addi r6, r4, 0x431BDE83@l
/* 800AA0F4 000A4FF4  C8 42 90 28 */	lfd f2, lbl_804C0A48-_SDA2_BASE_(r2)
/* 800AA0F8 000A4FF8  90 FC 00 20 */	stw r7, 0x20(r28)
/* 800AA0FC 000A4FFC  54 E7 18 38 */	slwi r7, r7, 3
/* 800AA100 000A5000  C0 02 90 20 */	lfs f0, lbl_804C0A40-_SDA2_BASE_(r2)
/* 800AA104 000A5004  80 85 00 F8 */	lwz r4, 0x800000F8@l(r5)
/* 800AA108 000A5008  54 80 F0 BE */	srwi r0, r4, 2
/* 800AA10C 000A500C  90 7C 00 1C */	stw r3, 0x1c(r28)
/* 800AA110 000A5010  7C 06 00 16 */	mulhwu r0, r6, r0
/* 800AA114 000A5014  54 00 8B FE */	srwi r0, r0, 0xf
/* 800AA118 000A5018  7C 07 03 96 */	divwu r0, r7, r0
/* 800AA11C 000A501C  90 01 00 0C */	stw r0, 0xc(r1)
/* 800AA120 000A5020  C8 21 00 08 */	lfd f1, 8(r1)
/* 800AA124 000A5024  EC 21 10 28 */	fsubs f1, f1, f2
/* 800AA128 000A5028  EC 00 08 24 */	fdivs f0, f0, f1
/* 800AA12C 000A502C  D0 1C 00 24 */	stfs f0, 0x24(r28)
/* 800AA130 000A5030  48 05 23 45 */	bl func_800FC474
/* 800AA134 000A5034  80 9C 00 10 */	lwz r4, 0x10(r28)
/* 800AA138 000A5038  39 61 00 30 */	addi r11, r1, 0x30
/* 800AA13C 000A503C  90 7C 00 0C */	stw r3, 0xc(r28)
/* 800AA140 000A5040  38 04 00 01 */	addi r0, r4, 1
/* 800AA144 000A5044  90 1C 00 10 */	stw r0, 0x10(r28)
/* 800AA148 000A5048  48 00 7C 49 */	bl _restgpr_27
/* 800AA14C 000A504C  80 01 00 34 */	lwz r0, 0x34(r1)
/* 800AA150 000A5050  7C 08 03 A6 */	mtlr r0
/* 800AA154 000A5054  38 21 00 30 */	addi r1, r1, 0x30
/* 800AA158 000A5058  4E 80 00 20 */	blr 

.global beginRender__Q23EGG7DisplayFv
beginRender__Q23EGG7DisplayFv:
/* 800AA15C 000A505C  4E 80 00 20 */	blr 

.global endRender__Q23EGG7DisplayFv
endRender__Q23EGG7DisplayFv:
/* 800AA160 000A5060  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800AA164 000A5064  7C 08 02 A6 */	mflr r0
/* 800AA168 000A5068  90 01 00 24 */	stw r0, 0x24(r1)
/* 800AA16C 000A506C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800AA170 000A5070  93 C1 00 18 */	stw r30, 0x18(r1)
/* 800AA174 000A5074  7C 7E 1B 78 */	mr r30, r3
/* 800AA178 000A5078  88 03 00 00 */	lbz r0, 0(r3)
/* 800AA17C 000A507C  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 800AA180 000A5080  41 82 00 34 */	beq lbl_800AA1B4
/* 800AA184 000A5084  88 03 00 14 */	lbz r0, 0x14(r3)
/* 800AA188 000A5088  38 81 00 08 */	addi r4, r1, 8
/* 800AA18C 000A508C  98 01 00 08 */	stb r0, 8(r1)
/* 800AA190 000A5090  88 03 00 15 */	lbz r0, 0x15(r3)
/* 800AA194 000A5094  98 01 00 09 */	stb r0, 9(r1)
/* 800AA198 000A5098  88 03 00 16 */	lbz r0, 0x16(r3)
/* 800AA19C 000A509C  98 01 00 0A */	stb r0, 0xa(r1)
/* 800AA1A0 000A50A0  88 03 00 17 */	lbz r0, 0x17(r3)
/* 800AA1A4 000A50A4  7C 83 23 78 */	mr r3, r4
/* 800AA1A8 000A50A8  98 01 00 0B */	stb r0, 0xb(r1)
/* 800AA1AC 000A50AC  80 9E 00 18 */	lwz r4, 0x18(r30)
/* 800AA1B0 000A50B0  48 03 51 F5 */	bl func_800DF3A4
lbl_800AA1B4:
/* 800AA1B4 000A50B4  80 6D 99 38 */	lwz r3, lbl_804BECB8-_SDA_BASE_(r13)
/* 800AA1B8 000A50B8  81 83 00 00 */	lwz r12, 0(r3)
/* 800AA1BC 000A50BC  81 8C 00 08 */	lwz r12, 8(r12)
/* 800AA1C0 000A50C0  7D 89 03 A6 */	mtctr r12
/* 800AA1C4 000A50C4  4E 80 04 21 */	bctrl 
/* 800AA1C8 000A50C8  83 E3 00 00 */	lwz r31, 0(r3)
/* 800AA1CC 000A50CC  2C 1F 00 00 */	cmpwi r31, 0
/* 800AA1D0 000A50D0  40 82 00 1C */	bne lbl_800AA1EC
/* 800AA1D4 000A50D4  3C 60 80 38 */	lis r3, lbl_8037A888@ha
/* 800AA1D8 000A50D8  38 80 00 96 */	li r4, 0x96
/* 800AA1DC 000A50DC  38 63 A8 88 */	addi r3, r3, lbl_8037A888@l
/* 800AA1E0 000A50E0  38 A3 00 0F */	addi r5, r3, 0xf
/* 800AA1E4 000A50E4  4C C6 31 82 */	crclr 6
/* 800AA1E8 000A50E8  4B FF 7D 21 */	bl func_800A1F08
lbl_800AA1EC:
/* 800AA1EC 000A50EC  88 7F 00 19 */	lbz r3, 0x19(r31)
/* 800AA1F0 000A50F0  38 9F 00 1A */	addi r4, r31, 0x1a
/* 800AA1F4 000A50F4  38 DF 00 32 */	addi r6, r31, 0x32
/* 800AA1F8 000A50F8  7C 60 00 34 */	cntlzw r0, r3
/* 800AA1FC 000A50FC  54 05 DE 3E */	rlwinm r5, r0, 0x1b, 0x18, 0x1f
/* 800AA200 000A5100  48 03 52 1D */	bl func_800DF41C
/* 800AA204 000A5104  80 6D 99 38 */	lwz r3, lbl_804BECB8-_SDA_BASE_(r13)
/* 800AA208 000A5108  88 1E 00 00 */	lbz r0, 0(r30)
/* 800AA20C 000A510C  81 83 00 00 */	lwz r12, 0(r3)
/* 800AA210 000A5110  54 1F 07 FE */	clrlwi r31, r0, 0x1f
/* 800AA214 000A5114  81 8C 00 14 */	lwz r12, 0x14(r12)
/* 800AA218 000A5118  7D 89 03 A6 */	mtctr r12
/* 800AA21C 000A511C  4E 80 04 21 */	bctrl 
/* 800AA220 000A5120  7F E4 FB 78 */	mr r4, r31
/* 800AA224 000A5124  48 00 06 51 */	bl copyEFB__Q23EGG10XfbManagerFb
/* 800AA228 000A5128  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800AA22C 000A512C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800AA230 000A5130  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 800AA234 000A5134  7C 08 03 A6 */	mtlr r0
/* 800AA238 000A5138  38 21 00 20 */	addi r1, r1, 0x20
/* 800AA23C 000A513C  4E 80 00 20 */	blr 

.global endFrame__Q23EGG7DisplayFv
endFrame__Q23EGG7DisplayFv:
/* 800AA240 000A5140  48 03 42 54 */	b func_800DE494

.global copyEFBtoXFB__Q23EGG7DisplayFv
copyEFBtoXFB__Q23EGG7DisplayFv:
/* 800AA244 000A5144  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800AA248 000A5148  7C 08 02 A6 */	mflr r0
/* 800AA24C 000A514C  90 01 00 24 */	stw r0, 0x24(r1)
/* 800AA250 000A5150  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800AA254 000A5154  93 C1 00 18 */	stw r30, 0x18(r1)
/* 800AA258 000A5158  7C 7E 1B 78 */	mr r30, r3
/* 800AA25C 000A515C  88 03 00 00 */	lbz r0, 0(r3)
/* 800AA260 000A5160  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 800AA264 000A5164  41 82 00 34 */	beq lbl_800AA298
/* 800AA268 000A5168  88 03 00 14 */	lbz r0, 0x14(r3)
/* 800AA26C 000A516C  38 81 00 08 */	addi r4, r1, 8
/* 800AA270 000A5170  98 01 00 08 */	stb r0, 8(r1)
/* 800AA274 000A5174  88 03 00 15 */	lbz r0, 0x15(r3)
/* 800AA278 000A5178  98 01 00 09 */	stb r0, 9(r1)
/* 800AA27C 000A517C  88 03 00 16 */	lbz r0, 0x16(r3)
/* 800AA280 000A5180  98 01 00 0A */	stb r0, 0xa(r1)
/* 800AA284 000A5184  88 03 00 17 */	lbz r0, 0x17(r3)
/* 800AA288 000A5188  7C 83 23 78 */	mr r3, r4
/* 800AA28C 000A518C  98 01 00 0B */	stb r0, 0xb(r1)
/* 800AA290 000A5190  80 9E 00 18 */	lwz r4, 0x18(r30)
/* 800AA294 000A5194  48 03 51 11 */	bl func_800DF3A4
lbl_800AA298:
/* 800AA298 000A5198  80 6D 99 38 */	lwz r3, lbl_804BECB8-_SDA_BASE_(r13)
/* 800AA29C 000A519C  81 83 00 00 */	lwz r12, 0(r3)
/* 800AA2A0 000A51A0  81 8C 00 08 */	lwz r12, 8(r12)
/* 800AA2A4 000A51A4  7D 89 03 A6 */	mtctr r12
/* 800AA2A8 000A51A8  4E 80 04 21 */	bctrl 
/* 800AA2AC 000A51AC  83 E3 00 00 */	lwz r31, 0(r3)
/* 800AA2B0 000A51B0  2C 1F 00 00 */	cmpwi r31, 0
/* 800AA2B4 000A51B4  40 82 00 1C */	bne lbl_800AA2D0
/* 800AA2B8 000A51B8  3C 60 80 38 */	lis r3, lbl_8037A888@ha
/* 800AA2BC 000A51BC  38 80 00 96 */	li r4, 0x96
/* 800AA2C0 000A51C0  38 63 A8 88 */	addi r3, r3, lbl_8037A888@l
/* 800AA2C4 000A51C4  38 A3 00 0F */	addi r5, r3, 0xf
/* 800AA2C8 000A51C8  4C C6 31 82 */	crclr 6
/* 800AA2CC 000A51CC  4B FF 7C 3D */	bl func_800A1F08
lbl_800AA2D0:
/* 800AA2D0 000A51D0  88 7F 00 19 */	lbz r3, 0x19(r31)
/* 800AA2D4 000A51D4  38 9F 00 1A */	addi r4, r31, 0x1a
/* 800AA2D8 000A51D8  38 DF 00 32 */	addi r6, r31, 0x32
/* 800AA2DC 000A51DC  7C 60 00 34 */	cntlzw r0, r3
/* 800AA2E0 000A51E0  54 05 DE 3E */	rlwinm r5, r0, 0x1b, 0x18, 0x1f
/* 800AA2E4 000A51E4  48 03 51 39 */	bl func_800DF41C
/* 800AA2E8 000A51E8  80 6D 99 38 */	lwz r3, lbl_804BECB8-_SDA_BASE_(r13)
/* 800AA2EC 000A51EC  88 1E 00 00 */	lbz r0, 0(r30)
/* 800AA2F0 000A51F0  81 83 00 00 */	lwz r12, 0(r3)
/* 800AA2F4 000A51F4  54 1F 07 FE */	clrlwi r31, r0, 0x1f
/* 800AA2F8 000A51F8  81 8C 00 14 */	lwz r12, 0x14(r12)
/* 800AA2FC 000A51FC  7D 89 03 A6 */	mtctr r12
/* 800AA300 000A5200  4E 80 04 21 */	bctrl 
/* 800AA304 000A5204  7F E4 FB 78 */	mr r4, r31
/* 800AA308 000A5208  48 00 05 6D */	bl copyEFB__Q23EGG10XfbManagerFb
/* 800AA30C 000A520C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800AA310 000A5210  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800AA314 000A5214  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 800AA318 000A5218  7C 08 03 A6 */	mtlr r0
/* 800AA31C 000A521C  38 21 00 20 */	addi r1, r1, 0x20
/* 800AA320 000A5220  4E 80 00 20 */	blr 

.global calcFrequency__Q23EGG7DisplayFv
calcFrequency__Q23EGG7DisplayFv:
/* 800AA324 000A5224  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800AA328 000A5228  7C 08 02 A6 */	mflr r0
/* 800AA32C 000A522C  90 01 00 24 */	stw r0, 0x24(r1)
/* 800AA330 000A5230  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800AA334 000A5234  7C 7F 1B 78 */	mr r31, r3
/* 800AA338 000A5238  48 04 B2 E5 */	bl func_800F561C
/* 800AA33C 000A523C  80 DF 00 1C */	lwz r6, 0x1c(r31)
/* 800AA340 000A5240  3C 00 43 30 */	lis r0, 0x4330
/* 800AA344 000A5244  3C 80 43 1C */	lis r4, 0x431BDE83@ha
/* 800AA348 000A5248  3C A0 80 00 */	lis r5, 0x800000F8@ha
/* 800AA34C 000A524C  7C E6 18 50 */	subf r7, r6, r3
/* 800AA350 000A5250  90 01 00 08 */	stw r0, 8(r1)
/* 800AA354 000A5254  38 C4 DE 83 */	addi r6, r4, 0x431BDE83@l
/* 800AA358 000A5258  C8 42 90 28 */	lfd f2, lbl_804C0A48-_SDA2_BASE_(r2)
/* 800AA35C 000A525C  90 FF 00 20 */	stw r7, 0x20(r31)
/* 800AA360 000A5260  54 E7 18 38 */	slwi r7, r7, 3
/* 800AA364 000A5264  C0 02 90 20 */	lfs f0, lbl_804C0A40-_SDA2_BASE_(r2)
/* 800AA368 000A5268  80 85 00 F8 */	lwz r4, 0x800000F8@l(r5)
/* 800AA36C 000A526C  54 80 F0 BE */	srwi r0, r4, 2
/* 800AA370 000A5270  90 7F 00 1C */	stw r3, 0x1c(r31)
/* 800AA374 000A5274  7C 06 00 16 */	mulhwu r0, r6, r0
/* 800AA378 000A5278  54 00 8B FE */	srwi r0, r0, 0xf
/* 800AA37C 000A527C  7C 07 03 96 */	divwu r0, r7, r0
/* 800AA380 000A5280  90 01 00 0C */	stw r0, 0xc(r1)
/* 800AA384 000A5284  C8 21 00 08 */	lfd f1, 8(r1)
/* 800AA388 000A5288  EC 21 10 28 */	fsubs f1, f1, f2
/* 800AA38C 000A528C  EC 00 08 24 */	fdivs f0, f0, f1
/* 800AA390 000A5290  D0 1F 00 24 */	stfs f0, 0x24(r31)
/* 800AA394 000A5294  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800AA398 000A5298  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800AA39C 000A529C  7C 08 03 A6 */	mtlr r0
/* 800AA3A0 000A52A0  38 21 00 20 */	addi r1, r1, 0x20
/* 800AA3A4 000A52A4  4E 80 00 20 */	blr 
