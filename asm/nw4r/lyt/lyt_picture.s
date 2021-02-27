.include "macros.inc"

.section .data, "wa"
.global __vt__Q34nw4r3lyt7Picture
__vt__Q34nw4r3lyt7Picture:
    .long 0
    .long 0
    .long __dt__Q34nw4r3lyt7PictureFv
    .long GetRuntimeTypeInfo__Q34nw4r3lyt7PictureCFv
    .long CalculateMtx__Q34nw4r3lyt4PaneFRCQ34nw4r3lyt8DrawInfo
    .long Draw__Q34nw4r3lyt4PaneFRCQ34nw4r3lyt8DrawInfo
    .long DrawSelf__Q34nw4r3lyt7PictureFRCQ34nw4r3lyt8DrawInfo
    .long Animate__Q34nw4r3lyt4PaneFUl
    .long AnimateSelf__Q34nw4r3lyt4PaneFUl
    .long GetVtxColor__Q34nw4r3lyt7PictureCFUl
    .long SetVtxColor__Q34nw4r3lyt7PictureFUlQ34nw4r2ut5Color
    .long GetColorElement__Q34nw4r3lyt4PaneCFUl
    .long SetColorElement__Q34nw4r3lyt4PaneFUlUc
    .long GetVtxColorElement__Q34nw4r3lyt7PictureCFUl
    .long SetVtxColorElement__Q34nw4r3lyt7PictureFUlUc
    .long FindPaneByName__Q34nw4r3lyt4PaneFPCcb
    .long FindMaterialByName__Q34nw4r3lyt4PaneFPCcb
    .long BindAnimation__Q34nw4r3lyt4PaneFPQ34nw4r3lyt13AnimTransformb
    .long UnbindAnimation__Q34nw4r3lyt4PaneFPQ34nw4r3lyt13AnimTransformb
    .long UnbindAllAnimation__Q34nw4r3lyt4PaneFb
    .long UnbindAnimationSelf__Q34nw4r3lyt4PaneFPQ34nw4r3lyt13AnimTransform
    .long FindAnimationLink__Q34nw4r3lyt4PaneFPQ34nw4r3lyt13AnimTransform
    .long SetAnimationEnable__Q34nw4r3lyt4PaneFPQ34nw4r3lyt13AnimTransformbb
    .long GetMaterial__Q34nw4r3lyt4PaneCFv
    .long LoadMtx__Q34nw4r3lyt4PaneFRCQ34nw4r3lyt8DrawInfo
    .long Append__Q34nw4r3lyt7PictureFRCQ34nw4r3lyt6TexMap

.section .text, "ax"
.global __ct__Q34nw4r3lyt7PictureFPCQ44nw4r3lyt3res7PictureRCQ34nw4r3lyt11ResBlockSet
__ct__Q34nw4r3lyt7PictureFPCQ44nw4r3lyt3res7PictureRCQ34nw4r3lyt11ResBlockSet:
/* 8007B1CC 000760CC  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8007B1D0 000760D0  7C 08 02 A6 */	mflr r0
/* 8007B1D4 000760D4  90 01 00 24 */	stw r0, 0x24(r1)
/* 8007B1D8 000760D8  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8007B1DC 000760DC  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8007B1E0 000760E0  7C BE 2B 78 */	mr r30, r5
/* 8007B1E4 000760E4  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8007B1E8 000760E8  7C 9D 23 78 */	mr r29, r4
/* 8007B1EC 000760EC  93 81 00 10 */	stw r28, 0x10(r1)
/* 8007B1F0 000760F0  7C 7C 1B 78 */	mr r28, r3
/* 8007B1F4 000760F4  4B FF E1 29 */	bl __ct__Q34nw4r3lyt4PaneFPCQ44nw4r3lyt3res4Pane
/* 8007B1F8 000760F8  3C 60 80 39 */	lis r3, __vt__Q34nw4r3lyt7Picture@ha
/* 8007B1FC 000760FC  3C 80 80 08 */	lis r4, __ct__Q34nw4r2ut5ColorFv@ha
/* 8007B200 00076100  38 63 72 38 */	addi r3, r3, __vt__Q34nw4r3lyt7Picture@l
/* 8007B204 00076104  3C A0 80 01 */	lis r5, __dt__Q34nw4r2ut5ColorFv@ha
/* 8007B208 00076108  90 7C 00 00 */	stw r3, 0(r28)
/* 8007B20C 0007610C  38 7C 00 D4 */	addi r3, r28, 0xd4
/* 8007B210 00076110  38 84 B1 C0 */	addi r4, r4, __ct__Q34nw4r2ut5ColorFv@l
/* 8007B214 00076114  38 A5 AC 88 */	addi r5, r5, __dt__Q34nw4r2ut5ColorFv@l
/* 8007B218 00076118  38 C0 00 04 */	li r6, 4
/* 8007B21C 0007611C  38 E0 00 04 */	li r7, 4
/* 8007B220 00076120  48 03 68 35 */	bl __construct_array
/* 8007B224 00076124  38 7C 00 E4 */	addi r3, r28, 0xe4
/* 8007B228 00076128  48 00 7C 29 */	bl __ct__Q44nw4r3lyt6detail11TexCoordAryFv
/* 8007B22C 0007612C  88 1D 00 5E */	lbz r0, 0x5e(r29)
/* 8007B230 00076130  3B E0 00 08 */	li r31, 8
/* 8007B234 00076134  28 00 00 08 */	cmplwi r0, 8
/* 8007B238 00076138  41 81 00 08 */	bgt lbl_8007B240
/* 8007B23C 0007613C  7C 1F 03 78 */	mr r31, r0
lbl_8007B240:
/* 8007B240 00076140  57 E4 06 3F */	clrlwi. r4, r31, 0x18
/* 8007B244 00076144  41 82 00 0C */	beq lbl_8007B250
/* 8007B248 00076148  38 7C 00 E4 */	addi r3, r28, 0xe4
/* 8007B24C 0007614C  48 00 7C 65 */	bl Reserve__Q44nw4r3lyt6detail11TexCoordAryFUc
lbl_8007B250:
/* 8007B250 00076150  80 DD 00 4C */	lwz r6, 0x4c(r29)
/* 8007B254 00076154  57 E5 06 3F */	clrlwi. r5, r31, 0x18
/* 8007B258 00076158  80 9D 00 50 */	lwz r4, 0x50(r29)
/* 8007B25C 0007615C  80 7D 00 54 */	lwz r3, 0x54(r29)
/* 8007B260 00076160  80 1D 00 58 */	lwz r0, 0x58(r29)
/* 8007B264 00076164  90 DC 00 D4 */	stw r6, 0xd4(r28)
/* 8007B268 00076168  90 9C 00 D8 */	stw r4, 0xd8(r28)
/* 8007B26C 0007616C  90 7C 00 DC */	stw r3, 0xdc(r28)
/* 8007B270 00076170  90 1C 00 E0 */	stw r0, 0xe0(r28)
/* 8007B274 00076174  41 82 00 1C */	beq lbl_8007B290
/* 8007B278 00076178  88 1C 00 E4 */	lbz r0, 0xe4(r28)
/* 8007B27C 0007617C  2C 00 00 00 */	cmpwi r0, 0
/* 8007B280 00076180  41 82 00 10 */	beq lbl_8007B290
/* 8007B284 00076184  38 7C 00 E4 */	addi r3, r28, 0xe4
/* 8007B288 00076188  38 9D 00 60 */	addi r4, r29, 0x60
/* 8007B28C 0007618C  48 00 7D 91 */	bl Copy__Q44nw4r3lyt6detail11TexCoordAryFPCvUc
lbl_8007B290:
/* 8007B290 00076190  80 6D 98 00 */	lwz r3, lbl_804BEB80-_SDA_BASE_(r13)
/* 8007B294 00076194  38 80 00 5C */	li r4, 0x5c
/* 8007B298 00076198  48 06 C1 F5 */	bl func_800E748C
/* 8007B29C 0007619C  2C 03 00 00 */	cmpwi r3, 0
/* 8007B2A0 000761A0  41 82 00 2C */	beq lbl_8007B2CC
/* 8007B2A4 000761A4  A0 1D 00 5C */	lhz r0, 0x5c(r29)
/* 8007B2A8 000761A8  80 BE 00 08 */	lwz r5, 8(r30)
/* 8007B2AC 000761AC  54 00 10 3A */	slwi r0, r0, 2
/* 8007B2B0 000761B0  7C 85 02 14 */	add r4, r5, r0
/* 8007B2B4 000761B4  80 04 00 0C */	lwz r0, 0xc(r4)
/* 8007B2B8 000761B8  7C 85 02 14 */	add r4, r5, r0
/* 8007B2BC 000761BC  41 82 00 0C */	beq lbl_8007B2C8
/* 8007B2C0 000761C0  7F C5 F3 78 */	mr r5, r30
/* 8007B2C4 000761C4  48 00 3A 89 */	bl __ct__Q34nw4r3lyt8MaterialFPCQ44nw4r3lyt3res8MaterialRCQ34nw4r3lyt11ResBlockSet
lbl_8007B2C8:
/* 8007B2C8 000761C8  90 7C 00 28 */	stw r3, 0x28(r28)
lbl_8007B2CC:
/* 8007B2CC 000761CC  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8007B2D0 000761D0  7F 83 E3 78 */	mr r3, r28
/* 8007B2D4 000761D4  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8007B2D8 000761D8  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8007B2DC 000761DC  83 81 00 10 */	lwz r28, 0x10(r1)
/* 8007B2E0 000761E0  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8007B2E4 000761E4  7C 08 03 A6 */	mtlr r0
/* 8007B2E8 000761E8  38 21 00 20 */	addi r1, r1, 0x20
/* 8007B2EC 000761EC  4E 80 00 20 */	blr 

.global __dt__Q34nw4r3lyt7PictureFv
__dt__Q34nw4r3lyt7PictureFv:
/* 8007B2F0 000761F0  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8007B2F4 000761F4  7C 08 02 A6 */	mflr r0
/* 8007B2F8 000761F8  2C 03 00 00 */	cmpwi r3, 0
/* 8007B2FC 000761FC  90 01 00 14 */	stw r0, 0x14(r1)
/* 8007B300 00076200  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8007B304 00076204  7C 9F 23 78 */	mr r31, r4
/* 8007B308 00076208  93 C1 00 08 */	stw r30, 8(r1)
/* 8007B30C 0007620C  7C 7E 1B 78 */	mr r30, r3
/* 8007B310 00076210  41 82 00 90 */	beq lbl_8007B3A0
/* 8007B314 00076214  80 A3 00 28 */	lwz r5, 0x28(r3)
/* 8007B318 00076218  3C 80 80 39 */	lis r4, __vt__Q34nw4r3lyt7Picture@ha
/* 8007B31C 0007621C  38 84 72 38 */	addi r4, r4, __vt__Q34nw4r3lyt7Picture@l
/* 8007B320 00076220  2C 05 00 00 */	cmpwi r5, 0
/* 8007B324 00076224  90 83 00 00 */	stw r4, 0(r3)
/* 8007B328 00076228  41 82 00 3C */	beq lbl_8007B364
/* 8007B32C 0007622C  88 05 00 59 */	lbz r0, 0x59(r5)
/* 8007B330 00076230  2C 00 00 00 */	cmpwi r0, 0
/* 8007B334 00076234  40 82 00 30 */	bne lbl_8007B364
/* 8007B338 00076238  81 85 00 00 */	lwz r12, 0(r5)
/* 8007B33C 0007623C  7C A3 2B 78 */	mr r3, r5
/* 8007B340 00076240  38 80 FF FF */	li r4, -1
/* 8007B344 00076244  81 8C 00 08 */	lwz r12, 8(r12)
/* 8007B348 00076248  7D 89 03 A6 */	mtctr r12
/* 8007B34C 0007624C  4E 80 04 21 */	bctrl 
/* 8007B350 00076250  80 6D 98 00 */	lwz r3, lbl_804BEB80-_SDA_BASE_(r13)
/* 8007B354 00076254  80 9E 00 28 */	lwz r4, 0x28(r30)
/* 8007B358 00076258  48 06 C1 45 */	bl func_800E749C
/* 8007B35C 0007625C  38 00 00 00 */	li r0, 0
/* 8007B360 00076260  90 1E 00 28 */	stw r0, 0x28(r30)
lbl_8007B364:
/* 8007B364 00076264  38 7E 00 E4 */	addi r3, r30, 0xe4
/* 8007B368 00076268  48 00 7A FD */	bl Free__Q44nw4r3lyt6detail11TexCoordAryFv
/* 8007B36C 0007626C  3C 80 80 01 */	lis r4, __dt__Q34nw4r2ut5ColorFv@ha
/* 8007B370 00076270  38 7E 00 D4 */	addi r3, r30, 0xd4
/* 8007B374 00076274  38 84 AC 88 */	addi r4, r4, __dt__Q34nw4r2ut5ColorFv@l
/* 8007B378 00076278  38 A0 00 04 */	li r5, 4
/* 8007B37C 0007627C  38 C0 00 04 */	li r6, 4
/* 8007B380 00076280  48 03 67 CD */	bl __destroy_arr
/* 8007B384 00076284  7F C3 F3 78 */	mr r3, r30
/* 8007B388 00076288  38 80 00 00 */	li r4, 0
/* 8007B38C 0007628C  4B FF E0 C5 */	bl __dt__Q34nw4r3lyt4PaneFv
/* 8007B390 00076290  2C 1F 00 00 */	cmpwi r31, 0
/* 8007B394 00076294  40 81 00 0C */	ble lbl_8007B3A0
/* 8007B398 00076298  7F C3 F3 78 */	mr r3, r30
/* 8007B39C 0007629C  48 02 7E E9 */	bl __dl__FPv
lbl_8007B3A0:
/* 8007B3A0 000762A0  7F C3 F3 78 */	mr r3, r30
/* 8007B3A4 000762A4  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8007B3A8 000762A8  83 C1 00 08 */	lwz r30, 8(r1)
/* 8007B3AC 000762AC  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8007B3B0 000762B0  7C 08 03 A6 */	mtlr r0
/* 8007B3B4 000762B4  38 21 00 10 */	addi r1, r1, 0x10
/* 8007B3B8 000762B8  4E 80 00 20 */	blr 

.global Append__Q34nw4r3lyt7PictureFRCQ34nw4r3lyt6TexMap
Append__Q34nw4r3lyt7PictureFRCQ34nw4r3lyt6TexMap:
/* 8007B3BC 000762BC  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8007B3C0 000762C0  7C 08 02 A6 */	mflr r0
/* 8007B3C4 000762C4  90 01 00 34 */	stw r0, 0x34(r1)
/* 8007B3C8 000762C8  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 8007B3CC 000762CC  93 C1 00 28 */	stw r30, 0x28(r1)
/* 8007B3D0 000762D0  7C 7E 1B 78 */	mr r30, r3
/* 8007B3D4 000762D4  93 A1 00 24 */	stw r29, 0x24(r1)
/* 8007B3D8 000762D8  93 81 00 20 */	stw r28, 0x20(r1)
/* 8007B3DC 000762DC  7C 9C 23 78 */	mr r28, r4
/* 8007B3E0 000762E0  80 A3 00 28 */	lwz r5, 0x28(r3)
/* 8007B3E4 000762E4  80 05 00 3C */	lwz r0, 0x3c(r5)
/* 8007B3E8 000762E8  80 65 00 38 */	lwz r3, 0x38(r5)
/* 8007B3EC 000762EC  54 1F 27 3E */	srwi r31, r0, 0x1c
/* 8007B3F0 000762F0  54 60 27 3E */	srwi r0, r3, 0x1c
/* 8007B3F4 000762F4  7C 1F 00 40 */	cmplw r31, r0
/* 8007B3F8 000762F8  40 80 01 58 */	bge lbl_8007B550
/* 8007B3FC 000762FC  54 60 67 3E */	rlwinm r0, r3, 0xc, 0x1c, 0x1f
/* 8007B400 00076300  7C 1F 00 40 */	cmplw r31, r0
/* 8007B404 00076304  41 80 00 08 */	blt lbl_8007B40C
/* 8007B408 00076308  48 00 01 48 */	b lbl_8007B550
lbl_8007B40C:
/* 8007B40C 0007630C  38 1F 00 01 */	addi r0, r31, 1
/* 8007B410 00076310  7C A3 2B 78 */	mr r3, r5
/* 8007B414 00076314  54 04 06 3E */	clrlwi r4, r0, 0x18
/* 8007B418 00076318  48 00 52 29 */	bl SetTextureNum__Q34nw4r3lyt8MaterialFUc
/* 8007B41C 0007631C  80 7E 00 28 */	lwz r3, 0x28(r30)
/* 8007B420 00076320  48 00 51 81 */	bl GetTexMapAry__Q34nw4r3lyt8MaterialFv
/* 8007B424 00076324  1C 1F 00 1C */	mulli r0, r31, 0x1c
/* 8007B428 00076328  80 DC 00 00 */	lwz r6, 0(r28)
/* 8007B42C 0007632C  80 BC 00 04 */	lwz r5, 4(r28)
/* 8007B430 00076330  A0 9C 00 08 */	lhz r4, 8(r28)
/* 8007B434 00076334  7C E3 02 14 */	add r7, r3, r0
/* 8007B438 00076338  A0 1C 00 0A */	lhz r0, 0xa(r28)
/* 8007B43C 0007633C  90 C7 00 00 */	stw r6, 0(r7)
/* 8007B440 00076340  C0 3C 00 0C */	lfs f1, 0xc(r28)
/* 8007B444 00076344  90 A7 00 04 */	stw r5, 4(r7)
/* 8007B448 00076348  C0 1C 00 10 */	lfs f0, 0x10(r28)
/* 8007B44C 0007634C  B0 87 00 08 */	sth r4, 8(r7)
/* 8007B450 00076350  A0 9C 00 14 */	lhz r4, 0x14(r28)
/* 8007B454 00076354  B0 07 00 0A */	sth r0, 0xa(r7)
/* 8007B458 00076358  A0 7C 00 16 */	lhz r3, 0x16(r28)
/* 8007B45C 0007635C  D0 27 00 0C */	stfs f1, 0xc(r7)
/* 8007B460 00076360  80 1C 00 18 */	lwz r0, 0x18(r28)
/* 8007B464 00076364  D0 07 00 10 */	stfs f0, 0x10(r7)
/* 8007B468 00076368  B0 87 00 14 */	sth r4, 0x14(r7)
/* 8007B46C 0007636C  B0 67 00 16 */	sth r3, 0x16(r7)
/* 8007B470 00076370  90 07 00 18 */	stw r0, 0x18(r7)
/* 8007B474 00076374  80 7E 00 28 */	lwz r3, 0x28(r30)
/* 8007B478 00076378  80 03 00 3C */	lwz r0, 0x3c(r3)
/* 8007B47C 0007637C  54 04 27 3E */	srwi r4, r0, 0x1c
/* 8007B480 00076380  48 00 52 51 */	bl SetTexCoordGenNum__Q34nw4r3lyt8MaterialFUc
/* 8007B484 00076384  3B 80 00 00 */	li r28, 0
/* 8007B488 00076388  3B A0 00 01 */	li r29, 1
/* 8007B48C 0007638C  38 80 00 04 */	li r4, 4
/* 8007B490 00076390  38 00 00 3C */	li r0, 0x3c
/* 8007B494 00076394  9B 81 00 0B */	stb r28, 0xb(r1)
/* 8007B498 00076398  80 7E 00 28 */	lwz r3, 0x28(r30)
/* 8007B49C 0007639C  9B A1 00 08 */	stb r29, 8(r1)
/* 8007B4A0 000763A0  98 81 00 09 */	stb r4, 9(r1)
/* 8007B4A4 000763A4  98 01 00 0A */	stb r0, 0xa(r1)
/* 8007B4A8 000763A8  80 01 00 08 */	lwz r0, 8(r1)
/* 8007B4AC 000763AC  90 01 00 0C */	stw r0, 0xc(r1)
/* 8007B4B0 000763B0  48 00 51 11 */	bl GetTexCoordGenAry__Q34nw4r3lyt8MaterialFv
/* 8007B4B4 000763B4  57 E0 15 BA */	rlwinm r0, r31, 2, 0x16, 0x1d
/* 8007B4B8 000763B8  88 81 00 0C */	lbz r4, 0xc(r1)
/* 8007B4BC 000763BC  7C A3 02 14 */	add r5, r3, r0
/* 8007B4C0 000763C0  88 01 00 0D */	lbz r0, 0xd(r1)
/* 8007B4C4 000763C4  98 85 00 00 */	stb r4, 0(r5)
/* 8007B4C8 000763C8  38 7E 00 E4 */	addi r3, r30, 0xe4
/* 8007B4CC 000763CC  88 81 00 0E */	lbz r4, 0xe(r1)
/* 8007B4D0 000763D0  98 05 00 01 */	stb r0, 1(r5)
/* 8007B4D4 000763D4  88 01 00 0F */	lbz r0, 0xf(r1)
/* 8007B4D8 000763D8  98 85 00 02 */	stb r4, 2(r5)
/* 8007B4DC 000763DC  98 05 00 03 */	stb r0, 3(r5)
/* 8007B4E0 000763E0  80 9E 00 28 */	lwz r4, 0x28(r30)
/* 8007B4E4 000763E4  80 04 00 3C */	lwz r0, 0x3c(r4)
/* 8007B4E8 000763E8  54 04 27 3E */	srwi r4, r0, 0x1c
/* 8007B4EC 000763EC  48 00 7A 45 */	bl SetSize__Q44nw4r3lyt6detail11TexCoordAryFUc
/* 8007B4F0 000763F0  C0 22 8A 78 */	lfs f1, lbl_804C0498-_SDA2_BASE_(r2)
/* 8007B4F4 000763F4  C0 1E 00 4C */	lfs f0, 0x4c(r30)
/* 8007B4F8 000763F8  D0 21 00 18 */	stfs f1, 0x18(r1)
/* 8007B4FC 000763FC  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 8007B500 00076400  D0 21 00 1C */	stfs f1, 0x1c(r1)
/* 8007B504 00076404  40 82 00 14 */	bne lbl_8007B518
/* 8007B508 00076408  C0 1E 00 50 */	lfs f0, 0x50(r30)
/* 8007B50C 0007640C  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 8007B510 00076410  40 82 00 08 */	bne lbl_8007B518
/* 8007B514 00076414  7F BC EB 78 */	mr r28, r29
lbl_8007B518:
/* 8007B518 00076418  2C 1C 00 00 */	cmpwi r28, 0
/* 8007B51C 0007641C  41 82 00 34 */	beq lbl_8007B550
/* 8007B520 00076420  80 9E 00 28 */	lwz r4, 0x28(r30)
/* 8007B524 00076424  80 04 00 3C */	lwz r0, 0x3c(r4)
/* 8007B528 00076428  54 00 27 3E */	srwi r0, r0, 0x1c
/* 8007B52C 0007642C  28 00 00 01 */	cmplwi r0, 1
/* 8007B530 00076430  40 82 00 20 */	bne lbl_8007B550
/* 8007B534 00076434  38 61 00 10 */	addi r3, r1, 0x10
/* 8007B538 00076438  38 A0 00 00 */	li r5, 0
/* 8007B53C 0007643C  48 00 64 4D */	bl GetTextureSize__Q34nw4r3lyt6detailFPQ34nw4r3lyt8MaterialUc
/* 8007B540 00076440  C0 01 00 10 */	lfs f0, 0x10(r1)
/* 8007B544 00076444  D0 1E 00 4C */	stfs f0, 0x4c(r30)
/* 8007B548 00076448  C0 01 00 14 */	lfs f0, 0x14(r1)
/* 8007B54C 0007644C  D0 1E 00 50 */	stfs f0, 0x50(r30)
lbl_8007B550:
/* 8007B550 00076450  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8007B554 00076454  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 8007B558 00076458  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 8007B55C 0007645C  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 8007B560 00076460  83 81 00 20 */	lwz r28, 0x20(r1)
/* 8007B564 00076464  7C 08 03 A6 */	mtlr r0
/* 8007B568 00076468  38 21 00 30 */	addi r1, r1, 0x30
/* 8007B56C 0007646C  4E 80 00 20 */	blr 

.global GetVtxColor__Q34nw4r3lyt7PictureCFUl
GetVtxColor__Q34nw4r3lyt7PictureCFUl:
/* 8007B570 00076470  54 A0 10 3A */	slwi r0, r5, 2
/* 8007B574 00076474  7C E4 02 14 */	add r7, r4, r0
/* 8007B578 00076478  88 C7 00 D4 */	lbz r6, 0xd4(r7)
/* 8007B57C 0007647C  88 A7 00 D5 */	lbz r5, 0xd5(r7)
/* 8007B580 00076480  88 87 00 D6 */	lbz r4, 0xd6(r7)
/* 8007B584 00076484  88 07 00 D7 */	lbz r0, 0xd7(r7)
/* 8007B588 00076488  98 C3 00 00 */	stb r6, 0(r3)
/* 8007B58C 0007648C  98 A3 00 01 */	stb r5, 1(r3)
/* 8007B590 00076490  98 83 00 02 */	stb r4, 2(r3)
/* 8007B594 00076494  98 03 00 03 */	stb r0, 3(r3)
/* 8007B598 00076498  4E 80 00 20 */	blr 

.global SetVtxColor__Q34nw4r3lyt7PictureFUlQ34nw4r2ut5Color
SetVtxColor__Q34nw4r3lyt7PictureFUlQ34nw4r2ut5Color:
/* 8007B59C 0007649C  54 80 10 3A */	slwi r0, r4, 2
/* 8007B5A0 000764A0  88 C5 00 00 */	lbz r6, 0(r5)
/* 8007B5A4 000764A4  7C 83 02 14 */	add r4, r3, r0
/* 8007B5A8 000764A8  88 05 00 01 */	lbz r0, 1(r5)
/* 8007B5AC 000764AC  98 C4 00 D4 */	stb r6, 0xd4(r4)
/* 8007B5B0 000764B0  88 65 00 02 */	lbz r3, 2(r5)
/* 8007B5B4 000764B4  98 04 00 D5 */	stb r0, 0xd5(r4)
/* 8007B5B8 000764B8  88 05 00 03 */	lbz r0, 3(r5)
/* 8007B5BC 000764BC  98 64 00 D6 */	stb r3, 0xd6(r4)
/* 8007B5C0 000764C0  98 04 00 D7 */	stb r0, 0xd7(r4)
/* 8007B5C4 000764C4  4E 80 00 20 */	blr 

.global GetVtxColorElement__Q34nw4r3lyt7PictureCFUl
GetVtxColorElement__Q34nw4r3lyt7PictureCFUl:
/* 8007B5C8 000764C8  54 85 00 3A */	rlwinm r5, r4, 0, 0, 0x1d
/* 8007B5CC 000764CC  54 80 07 BE */	clrlwi r0, r4, 0x1e
/* 8007B5D0 000764D0  7C 63 2A 14 */	add r3, r3, r5
/* 8007B5D4 000764D4  7C 63 02 14 */	add r3, r3, r0
/* 8007B5D8 000764D8  88 63 00 D4 */	lbz r3, 0xd4(r3)
/* 8007B5DC 000764DC  4E 80 00 20 */	blr 

.global SetVtxColorElement__Q34nw4r3lyt7PictureFUlUc
SetVtxColorElement__Q34nw4r3lyt7PictureFUlUc:
/* 8007B5E0 000764E0  54 86 00 3A */	rlwinm r6, r4, 0, 0, 0x1d
/* 8007B5E4 000764E4  54 80 07 BE */	clrlwi r0, r4, 0x1e
/* 8007B5E8 000764E8  7C 63 32 14 */	add r3, r3, r6
/* 8007B5EC 000764EC  7C 63 02 14 */	add r3, r3, r0
/* 8007B5F0 000764F0  98 A3 00 D4 */	stb r5, 0xd4(r3)
/* 8007B5F4 000764F4  4E 80 00 20 */	blr 

.global DrawSelf__Q34nw4r3lyt7PictureFRCQ34nw4r3lyt8DrawInfo
DrawSelf__Q34nw4r3lyt7PictureFRCQ34nw4r3lyt8DrawInfo:
/* 8007B5F8 000764F8  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8007B5FC 000764FC  7C 08 02 A6 */	mflr r0
/* 8007B600 00076500  90 01 00 24 */	stw r0, 0x24(r1)
/* 8007B604 00076504  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8007B608 00076508  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8007B60C 0007650C  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8007B610 00076510  93 81 00 10 */	stw r28, 0x10(r1)
/* 8007B614 00076514  7C 7C 1B 78 */	mr r28, r3
/* 8007B618 00076518  80 03 00 28 */	lwz r0, 0x28(r3)
/* 8007B61C 0007651C  2C 00 00 00 */	cmpwi r0, 0
/* 8007B620 00076520  41 82 00 94 */	beq lbl_8007B6B4
/* 8007B624 00076524  81 83 00 00 */	lwz r12, 0(r3)
/* 8007B628 00076528  81 8C 00 60 */	lwz r12, 0x60(r12)
/* 8007B62C 0007652C  7D 89 03 A6 */	mtctr r12
/* 8007B630 00076530  4E 80 04 21 */	bctrl 
/* 8007B634 00076534  8B BC 00 B5 */	lbz r29, 0xb5(r28)
/* 8007B638 00076538  38 7C 00 D4 */	addi r3, r28, 0xd4
/* 8007B63C 0007653C  7F A4 EB 78 */	mr r4, r29
/* 8007B640 00076540  48 00 7A 71 */	bl IsModulateVertexColor__Q34nw4r3lyt6detailFPQ34nw4r2ut5ColorUc
/* 8007B644 00076544  7C 64 1B 78 */	mr r4, r3
/* 8007B648 00076548  80 7C 00 28 */	lwz r3, 0x28(r28)
/* 8007B64C 0007654C  7F A5 EB 78 */	mr r5, r29
/* 8007B650 00076550  81 83 00 00 */	lwz r12, 0(r3)
/* 8007B654 00076554  81 8C 00 0C */	lwz r12, 0xc(r12)
/* 8007B658 00076558  7D 89 03 A6 */	mtctr r12
/* 8007B65C 0007655C  4E 80 04 21 */	bctrl 
/* 8007B660 00076560  88 9C 00 E5 */	lbz r4, 0xe5(r28)
/* 8007B664 00076564  7C 7D 1B 78 */	mr r29, r3
/* 8007B668 00076568  48 00 7B 05 */	bl SetVertexFormat__Q34nw4r3lyt6detailFbUc
/* 8007B66C 0007656C  2C 1D 00 00 */	cmpwi r29, 0
/* 8007B670 00076570  41 82 00 0C */	beq lbl_8007B67C
/* 8007B674 00076574  3B DC 00 D4 */	addi r30, r28, 0xd4
/* 8007B678 00076578  48 00 00 08 */	b lbl_8007B680
lbl_8007B67C:
/* 8007B67C 0007657C  3B C0 00 00 */	li r30, 0
lbl_8007B680:
/* 8007B680 00076580  83 BC 00 E8 */	lwz r29, 0xe8(r28)
/* 8007B684 00076584  7F 83 E3 78 */	mr r3, r28
/* 8007B688 00076588  8B FC 00 E5 */	lbz r31, 0xe5(r28)
/* 8007B68C 0007658C  4B FF EA 99 */	bl GetVtxPos__Q34nw4r3lyt4PaneCFv
/* 8007B690 00076590  90 81 00 0C */	stw r4, 0xc(r1)
/* 8007B694 00076594  7F E5 FB 78 */	mr r5, r31
/* 8007B698 00076598  7F A6 EB 78 */	mr r6, r29
/* 8007B69C 0007659C  7F C7 F3 78 */	mr r7, r30
/* 8007B6A0 000765A0  90 61 00 08 */	stw r3, 8(r1)
/* 8007B6A4 000765A4  38 61 00 08 */	addi r3, r1, 8
/* 8007B6A8 000765A8  38 9C 00 4C */	addi r4, r28, 0x4c
/* 8007B6AC 000765AC  89 1C 00 B5 */	lbz r8, 0xb5(r28)
/* 8007B6B0 000765B0  48 00 81 01 */	bl DrawQuad__Q34nw4r3lyt6detailFRCQ34nw4r4math4VEC2RCQ34nw4r3lyt4SizeUcPA4_CQ34nw4r4math4VEC2PCQ34nw4r2ut5ColorUc
lbl_8007B6B4:
/* 8007B6B4 000765B4  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8007B6B8 000765B8  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8007B6BC 000765BC  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8007B6C0 000765C0  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8007B6C4 000765C4  83 81 00 10 */	lwz r28, 0x10(r1)
/* 8007B6C8 000765C8  7C 08 03 A6 */	mtlr r0
/* 8007B6CC 000765CC  38 21 00 20 */	addi r1, r1, 0x20
/* 8007B6D0 000765D0  4E 80 00 20 */	blr 

.global GetRuntimeTypeInfo__Q34nw4r3lyt7PictureCFv
GetRuntimeTypeInfo__Q34nw4r3lyt7PictureCFv:
/* 8007B6D4 000765D4  38 6D 98 08 */	addi r3, r13, lbl_804BEB88-_SDA_BASE_
/* 8007B6D8 000765D8  4E 80 00 20 */	blr 

# __sinit_\lyt_picture_cpp
.global __sinit_$$3lyt_picture_cpp
__sinit_$$3lyt_picture_cpp:
/* 8007B6DC 000765DC  38 0D 97 F8 */	addi r0, r13, lbl_804BEB78-_SDA_BASE_
/* 8007B6E0 000765E0  90 0D 98 08 */	stw r0, lbl_804BEB88-_SDA_BASE_(r13)
/* 8007B6E4 000765E4  4E 80 00 20 */	blr 
