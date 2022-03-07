.include "macros.inc"

.section .sdata2, "a"
.balign 0x8
.global lbl_804C07B0
lbl_804C07B0:
	.incbin "baserom.dol", 0x3C93F0, 0x1
.global lbl_804C07B1
lbl_804C07B1:
	.incbin "baserom.dol", 0x3C93F1, 0x1
.global lbl_804C07B2
lbl_804C07B2:
	.incbin "baserom.dol", 0x3C93F2, 0x1
.global lbl_804C07B3
lbl_804C07B3:
	.incbin "baserom.dol", 0x3C93F3, 0x1
.global lbl_804C07B4
lbl_804C07B4:
	.incbin "baserom.dol", 0x3C93F4, 0x4
.global lbl_804C07B8
lbl_804C07B8:
	.incbin "baserom.dol", 0x3C93F8, 0x4
.global lbl_804C07BC
lbl_804C07BC:
	.incbin "baserom.dol", 0x3C93FC, 0x4
.global lbl_804C07C0
lbl_804C07C0:
	.incbin "baserom.dol", 0x3C9400, 0x8
.global lbl_804C07C8
lbl_804C07C8:
	.incbin "baserom.dol", 0x3C9408, 0x8
.global lbl_804C07D0
lbl_804C07D0:
	.incbin "baserom.dol", 0x3C9410, 0x8

.section .data, "wa"
.balign 0x8
.global lbl_80397CC8
lbl_80397CC8:
	.incbin "baserom.dol", 0x393DC8, 0x10
.global lbl_80397CD8
lbl_80397CD8:
	.incbin "baserom.dol", 0x393DD8, 0x10
.global lbl_80397CE8
lbl_80397CE8:
    .long 0
    .long 0
    .long 0x8008a350
    .long 0x80096a6c
    .long 0x8009725c
    .long 0x80097110
    .long 0x80096b20
    .long 0x80096bc0
    .long 0x80096c54
    .long 0

.section .text, "ax"
.global __ct__Q23EGG14PostEffectBlurFv
__ct__Q23EGG14PostEffectBlurFv:
/* 800970D4 00091FD4  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800970D8 00091FD8  7C 08 02 A6 */	mflr r0
/* 800970DC 00091FDC  90 01 00 14 */	stw r0, 0x14(r1)
/* 800970E0 00091FE0  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800970E4 00091FE4  7C 7F 1B 78 */	mr r31, r3
/* 800970E8 00091FE8  4B FF F9 4D */	bl __ct__Q23EGG14PostEffectBaseFv
/* 800970EC 00091FEC  3C 80 80 39 */	lis r4, lbl_80397CE8@ha
/* 800970F0 00091FF0  7F E3 FB 78 */	mr r3, r31
/* 800970F4 00091FF4  38 84 7C E8 */	addi r4, r4, lbl_80397CE8@l
/* 800970F8 00091FF8  90 9F 00 1C */	stw r4, 0x1c(r31)
/* 800970FC 00091FFC  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80097100 00092000  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80097104 00092004  7C 08 03 A6 */	mtlr r0
/* 80097108 00092008  38 21 00 10 */	addi r1, r1, 0x10
/* 8009710C 0009200C  4E 80 00 20 */	blr 

/* 80097110 00092010  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 80097114 00092014  7C 08 02 A6 */	mflr r0
/* 80097118 00092018  90 01 00 34 */	stw r0, 0x34(r1)
/* 8009711C 0009201C  39 61 00 30 */	addi r11, r1, 0x30
/* 80097120 00092020  48 01 AC 21 */	bl _savegpr_26
/* 80097124 00092024  38 C0 00 10 */	li r6, 0x10
/* 80097128 00092028  C0 22 8D 94 */	lfs f1, lbl_804C07B4-_SDA2_BASE_(r2)
/* 8009712C 0009202C  98 C3 00 30 */	stb r6, 0x30(r3)
/* 80097130 00092030  3B 80 00 00 */	li r28, 0
/* 80097134 00092034  C0 02 8D 98 */	lfs f0, lbl_804C07B8-_SDA2_BASE_(r2)
/* 80097138 00092038  38 00 00 01 */	li r0, 1
/* 8009713C 0009203C  88 A2 8D 90 */	lbz r5, lbl_804C07B0-_SDA2_BASE_(r2)
/* 80097140 00092040  88 82 8D 91 */	lbz r4, lbl_804C07B1-_SDA2_BASE_(r2)
/* 80097144 00092044  8B 42 8D 92 */	lbz r26, lbl_804C07B2-_SDA2_BASE_(r2)
/* 80097148 00092048  8B 62 8D 93 */	lbz r27, lbl_804C07B3-_SDA2_BASE_(r2)
/* 8009714C 0009204C  98 A1 00 14 */	stb r5, 0x14(r1)
/* 80097150 00092050  98 A3 00 31 */	stb r5, 0x31(r3)
/* 80097154 00092054  98 83 00 32 */	stb r4, 0x32(r3)
/* 80097158 00092058  9B 43 00 33 */	stb r26, 0x33(r3)
/* 8009715C 0009205C  9B 63 00 34 */	stb r27, 0x34(r3)
/* 80097160 00092060  D0 23 00 38 */	stfs f1, 0x38(r3)
/* 80097164 00092064  D0 03 00 3C */	stfs f0, 0x3c(r3)
/* 80097168 00092068  93 83 00 40 */	stw r28, 0x40(r3)
/* 8009716C 0009206C  98 C3 00 44 */	stb r6, 0x44(r3)
/* 80097170 00092070  8B A2 8D 90 */	lbz r29, lbl_804C07B0-_SDA2_BASE_(r2)
/* 80097174 00092074  8B C2 8D 91 */	lbz r30, lbl_804C07B1-_SDA2_BASE_(r2)
/* 80097178 00092078  8B E2 8D 92 */	lbz r31, lbl_804C07B2-_SDA2_BASE_(r2)
/* 8009717C 0009207C  89 82 8D 93 */	lbz r12, lbl_804C07B3-_SDA2_BASE_(r2)
/* 80097180 00092080  98 81 00 15 */	stb r4, 0x15(r1)
/* 80097184 00092084  9B A3 00 45 */	stb r29, 0x45(r3)
/* 80097188 00092088  9B C3 00 46 */	stb r30, 0x46(r3)
/* 8009718C 0009208C  9B E3 00 47 */	stb r31, 0x47(r3)
/* 80097190 00092090  99 83 00 48 */	stb r12, 0x48(r3)
/* 80097194 00092094  D0 23 00 4C */	stfs f1, 0x4c(r3)
/* 80097198 00092098  D0 03 00 50 */	stfs f0, 0x50(r3)
/* 8009719C 0009209C  93 83 00 54 */	stw r28, 0x54(r3)
/* 800971A0 000920A0  98 C3 00 58 */	stb r6, 0x58(r3)
/* 800971A4 000920A4  89 62 8D 90 */	lbz r11, lbl_804C07B0-_SDA2_BASE_(r2)
/* 800971A8 000920A8  89 42 8D 91 */	lbz r10, lbl_804C07B1-_SDA2_BASE_(r2)
/* 800971AC 000920AC  89 22 8D 92 */	lbz r9, lbl_804C07B2-_SDA2_BASE_(r2)
/* 800971B0 000920B0  89 02 8D 93 */	lbz r8, lbl_804C07B3-_SDA2_BASE_(r2)
/* 800971B4 000920B4  99 61 00 0C */	stb r11, 0xc(r1)
/* 800971B8 000920B8  99 63 00 59 */	stb r11, 0x59(r3)
/* 800971BC 000920BC  39 61 00 30 */	addi r11, r1, 0x30
/* 800971C0 000920C0  99 43 00 5A */	stb r10, 0x5a(r3)
/* 800971C4 000920C4  99 23 00 5B */	stb r9, 0x5b(r3)
/* 800971C8 000920C8  99 03 00 5C */	stb r8, 0x5c(r3)
/* 800971CC 000920CC  D0 23 00 60 */	stfs f1, 0x60(r3)
/* 800971D0 000920D0  D0 03 00 64 */	stfs f0, 0x64(r3)
/* 800971D4 000920D4  93 83 00 68 */	stw r28, 0x68(r3)
/* 800971D8 000920D8  98 C3 00 6C */	stb r6, 0x6c(r3)
/* 800971DC 000920DC  88 E2 8D 90 */	lbz r7, lbl_804C07B0-_SDA2_BASE_(r2)
/* 800971E0 000920E0  88 C2 8D 91 */	lbz r6, lbl_804C07B1-_SDA2_BASE_(r2)
/* 800971E4 000920E4  88 A2 8D 92 */	lbz r5, lbl_804C07B2-_SDA2_BASE_(r2)
/* 800971E8 000920E8  88 82 8D 93 */	lbz r4, lbl_804C07B3-_SDA2_BASE_(r2)
/* 800971EC 000920EC  9B 41 00 16 */	stb r26, 0x16(r1)
/* 800971F0 000920F0  98 E3 00 6D */	stb r7, 0x6d(r3)
/* 800971F4 000920F4  98 C3 00 6E */	stb r6, 0x6e(r3)
/* 800971F8 000920F8  98 A3 00 6F */	stb r5, 0x6f(r3)
/* 800971FC 000920FC  98 83 00 70 */	stb r4, 0x70(r3)
/* 80097200 00092100  D0 23 00 74 */	stfs f1, 0x74(r3)
/* 80097204 00092104  D0 03 00 78 */	stfs f0, 0x78(r3)
/* 80097208 00092108  93 83 00 7C */	stw r28, 0x7c(r3)
/* 8009720C 0009210C  98 03 00 20 */	stb r0, 0x20(r3)
/* 80097210 00092110  D0 03 00 2C */	stfs f0, 0x2c(r3)
/* 80097214 00092114  93 83 00 24 */	stw r28, 0x24(r3)
/* 80097218 00092118  9B 61 00 17 */	stb r27, 0x17(r1)
/* 8009721C 0009211C  9B A1 00 08 */	stb r29, 8(r1)
/* 80097220 00092120  9B C1 00 09 */	stb r30, 9(r1)
/* 80097224 00092124  9B E1 00 0A */	stb r31, 0xa(r1)
/* 80097228 00092128  99 81 00 0B */	stb r12, 0xb(r1)
/* 8009722C 0009212C  99 41 00 0D */	stb r10, 0xd(r1)
/* 80097230 00092130  99 21 00 0E */	stb r9, 0xe(r1)
/* 80097234 00092134  99 01 00 0F */	stb r8, 0xf(r1)
/* 80097238 00092138  98 E1 00 10 */	stb r7, 0x10(r1)
/* 8009723C 0009213C  98 C1 00 11 */	stb r6, 0x11(r1)
/* 80097240 00092140  98 A1 00 12 */	stb r5, 0x12(r1)
/* 80097244 00092144  98 81 00 13 */	stb r4, 0x13(r1)
/* 80097248 00092148  48 01 AB 45 */	bl _restgpr_26
/* 8009724C 0009214C  80 01 00 34 */	lwz r0, 0x34(r1)
/* 80097250 00092150  7C 08 03 A6 */	mtlr r0
/* 80097254 00092154  38 21 00 30 */	addi r1, r1, 0x30
/* 80097258 00092158  4E 80 00 20 */	blr 

/* 8009725C 0009215C  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 80097260 00092160  7C 08 02 A6 */	mflr r0
/* 80097264 00092164  90 01 00 44 */	stw r0, 0x44(r1)
/* 80097268 00092168  DB E1 00 30 */	stfd f31, 0x30(r1)
/* 8009726C 0009216C  F3 E1 00 38 */	psq_st f31, 56(r1), 0, qr0
/* 80097270 00092170  DB C1 00 20 */	stfd f30, 0x20(r1)
/* 80097274 00092174  F3 C1 00 28 */	psq_st f30, 40(r1), 0, qr0
/* 80097278 00092178  FF C0 08 90 */	fmr f30, f1
/* 8009727C 0009217C  FF E0 10 90 */	fmr f31, f2
/* 80097280 00092180  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80097284 00092184  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80097288 00092188  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8009728C 0009218C  93 81 00 10 */	stw r28, 0x10(r1)
/* 80097290 00092190  7C 7C 1B 78 */	mr r28, r3
/* 80097294 00092194  A0 03 00 00 */	lhz r0, 0(r3)
/* 80097298 00092198  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 8009729C 0009219C  40 82 00 C8 */	bne lbl_80097364
/* 800972A0 000921A0  81 83 00 1C */	lwz r12, 0x1c(r3)
/* 800972A4 000921A4  81 8C 00 20 */	lwz r12, 0x20(r12)
/* 800972A8 000921A8  7D 89 03 A6 */	mtctr r12
/* 800972AC 000921AC  4E 80 04 21 */	bctrl 
/* 800972B0 000921B0  7F 83 E3 78 */	mr r3, r28
/* 800972B4 000921B4  4B FF FA 05 */	bl setGXChanState__Q23EGG14PostEffectBaseFv
/* 800972B8 000921B8  7F 83 E3 78 */	mr r3, r28
/* 800972BC 000921BC  4B FF FA 69 */	bl setGXIndStages__Q23EGG14PostEffectBaseFv
/* 800972C0 000921C0  7F 83 E3 78 */	mr r3, r28
/* 800972C4 000921C4  4B FF FA 69 */	bl setGXFog__Q23EGG14PostEffectBaseFv
/* 800972C8 000921C8  7F 83 E3 78 */	mr r3, r28
/* 800972CC 000921CC  4B FF F8 ED */	bl setGXVtxState__Q23EGG14PostEffectBaseFv
/* 800972D0 000921D0  3B E0 00 00 */	li r31, 0
/* 800972D4 000921D4  48 00 00 80 */	b lbl_80097354
lbl_800972D8:
/* 800972D8 000921D8  57 E0 06 3E */	clrlwi r0, r31, 0x18
/* 800972DC 000921DC  3B A0 00 00 */	li r29, 0
/* 800972E0 000921E0  1C 00 00 14 */	mulli r0, r0, 0x14
/* 800972E4 000921E4  7C 7C 02 14 */	add r3, r28, r0
/* 800972E8 000921E8  88 63 00 30 */	lbz r3, 0x30(r3)
/* 800972EC 000921EC  38 03 FF FF */	addi r0, r3, -1
/* 800972F0 000921F0  7C 00 1E 70 */	srawi r0, r0, 3
/* 800972F4 000921F4  7F C0 01 94 */	addze r30, r0
/* 800972F8 000921F8  48 00 00 4C */	b lbl_80097344
lbl_800972FC:
/* 800972FC 000921FC  7F 83 E3 78 */	mr r3, r28
/* 80097300 00092200  57 E4 06 3E */	clrlwi r4, r31, 0x18
/* 80097304 00092204  57 A5 06 3E */	clrlwi r5, r29, 0x18
/* 80097308 00092208  48 00 00 8D */	bl func_80097394
/* 8009730C 0009220C  81 9C 00 1C */	lwz r12, 0x1c(r28)
/* 80097310 00092210  7F 83 E3 78 */	mr r3, r28
/* 80097314 00092214  C0 3C 00 14 */	lfs f1, 0x14(r28)
/* 80097318 00092218  C0 1C 00 18 */	lfs f0, 0x18(r28)
/* 8009731C 0009221C  EC 7E 00 72 */	fmuls f3, f30, f1
/* 80097320 00092220  81 8C 00 1C */	lwz r12, 0x1c(r12)
/* 80097324 00092224  EC 9F 00 32 */	fmuls f4, f31, f0
/* 80097328 00092228  C0 3C 00 0C */	lfs f1, 0xc(r28)
/* 8009732C 0009222C  C0 5C 00 10 */	lfs f2, 0x10(r28)
/* 80097330 00092230  7D 89 03 A6 */	mtctr r12
/* 80097334 00092234  4E 80 04 21 */	bctrl 
/* 80097338 00092238  38 60 00 02 */	li r3, 2
/* 8009733C 0009223C  4B FF 2A 21 */	bl SetBlendMode__Q23EGG6DrawGXFQ33EGG6DrawGX5Blend
/* 80097340 00092240  3B BD 00 01 */	addi r29, r29, 1
lbl_80097344:
/* 80097344 00092244  57 A0 06 3E */	clrlwi r0, r29, 0x18
/* 80097348 00092248  7C 00 F0 00 */	cmpw r0, r30
/* 8009734C 0009224C  40 81 FF B0 */	ble lbl_800972FC
/* 80097350 00092250  3B FF 00 01 */	addi r31, r31, 1
lbl_80097354:
/* 80097354 00092254  88 1C 00 20 */	lbz r0, 0x20(r28)
/* 80097358 00092258  57 E3 06 3E */	clrlwi r3, r31, 0x18
/* 8009735C 0009225C  7C 03 00 40 */	cmplw r3, r0
/* 80097360 00092260  41 80 FF 78 */	blt lbl_800972D8
lbl_80097364:
/* 80097364 00092264  E3 E1 00 38 */	psq_l f31, 56(r1), 0, qr0
/* 80097368 00092268  CB E1 00 30 */	lfd f31, 0x30(r1)
/* 8009736C 0009226C  E3 C1 00 28 */	psq_l f30, 40(r1), 0, qr0
/* 80097370 00092270  CB C1 00 20 */	lfd f30, 0x20(r1)
/* 80097374 00092274  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80097378 00092278  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8009737C 0009227C  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 80097380 00092280  80 01 00 44 */	lwz r0, 0x44(r1)
/* 80097384 00092284  83 81 00 10 */	lwz r28, 0x10(r1)
/* 80097388 00092288  7C 08 03 A6 */	mtlr r0
/* 8009738C 0009228C  38 21 00 40 */	addi r1, r1, 0x40
/* 80097390 00092290  4E 80 00 20 */	blr 

.global func_80097394
func_80097394:
/* 80097394 00092294  94 21 FE E0 */	stwu r1, -0x120(r1)
/* 80097398 00092298  7C 08 02 A6 */	mflr r0
/* 8009739C 0009229C  90 01 01 24 */	stw r0, 0x124(r1)
/* 800973A0 000922A0  DB E1 01 10 */	stfd f31, 0x110(r1)
/* 800973A4 000922A4  F3 E1 01 18 */	psq_st f31, 280(r1), 0, qr0
/* 800973A8 000922A8  DB C1 01 00 */	stfd f30, 0x100(r1)
/* 800973AC 000922AC  F3 C1 01 08 */	.4byte 0xF3C10108
/* 800973B0 000922B0  DB A1 00 F0 */	stfd f29, 0xf0(r1)
/* 800973B4 000922B4  F3 A1 00 F8 */	psq_st f29, 248(r1), 0, qr0
/* 800973B8 000922B8  DB 81 00 E0 */	stfd f28, 0xe0(r1)
/* 800973BC 000922BC  F3 81 00 E8 */	psq_st f28, 232(r1), 0, qr0
/* 800973C0 000922C0  DB 61 00 D0 */	stfd f27, 0xd0(r1)
/* 800973C4 000922C4  F3 61 00 D8 */	psq_st f27, 216(r1), 0, qr0
/* 800973C8 000922C8  DB 41 00 C0 */	stfd f26, 0xc0(r1)
/* 800973CC 000922CC  F3 41 00 C8 */	psq_st f26, 200(r1), 0, qr0
/* 800973D0 000922D0  DB 21 00 B0 */	stfd f25, 0xb0(r1)
/* 800973D4 000922D4  F3 21 00 B8 */	psq_st f25, 184(r1), 0, qr0
/* 800973D8 000922D8  DB 01 00 A0 */	stfd f24, 0xa0(r1)
/* 800973DC 000922DC  F3 01 00 A8 */	psq_st f24, 168(r1), 0, qr0
/* 800973E0 000922E0  DA E1 00 90 */	stfd f23, 0x90(r1)
/* 800973E4 000922E4  F2 E1 00 98 */	psq_st f23, 152(r1), 0, qr0
/* 800973E8 000922E8  DA C1 00 80 */	stfd f22, 0x80(r1)
/* 800973EC 000922EC  F2 C1 00 88 */	psq_st f22, 136(r1), 0, qr0
/* 800973F0 000922F0  39 61 00 80 */	addi r11, r1, 0x80
/* 800973F4 000922F4  48 01 A9 45 */	bl _savegpr_24
/* 800973F8 000922F8  1C 04 00 14 */	mulli r0, r4, 0x14
/* 800973FC 000922FC  3C C0 43 30 */	lis r6, 0x4330
/* 80097400 00092300  54 A4 1E 38 */	rlwinm r4, r5, 3, 0x18, 0x1c
/* 80097404 00092304  90 C1 00 50 */	stw r6, 0x50(r1)
/* 80097408 00092308  7C 7F 1B 78 */	mr r31, r3
/* 8009740C 0009230C  7F A3 02 14 */	add r29, r3, r0
/* 80097410 00092310  88 1D 00 30 */	lbz r0, 0x30(r29)
/* 80097414 00092314  54 BC 1D 78 */	rlwinm r28, r5, 3, 0x15, 0x1c
/* 80097418 00092318  90 C1 00 58 */	stw r6, 0x58(r1)
/* 8009741C 0009231C  7C 04 00 50 */	subf r0, r4, r0
/* 80097420 00092320  54 1B 06 3E */	clrlwi r27, r0, 0x18
/* 80097424 00092324  28 1B 00 08 */	cmplwi r27, 8
/* 80097428 00092328  40 81 00 08 */	ble lbl_80097430
/* 8009742C 0009232C  3B 60 00 08 */	li r27, 8
lbl_80097430:
/* 80097430 00092330  80 A3 00 08 */	lwz r5, 8(r3)
/* 80097434 00092334  7F 63 DB 78 */	mr r3, r27
/* 80097438 00092338  C8 62 8D A8 */	lfd f3, lbl_804C07C8-_SDA2_BASE_(r2)
/* 8009743C 0009233C  A0 85 00 02 */	lhz r4, 2(r5)
/* 80097440 00092340  A0 05 00 04 */	lhz r0, 4(r5)
/* 80097444 00092344  90 81 00 54 */	stw r4, 0x54(r1)
/* 80097448 00092348  C0 22 8D 98 */	lfs f1, lbl_804C07B8-_SDA2_BASE_(r2)
/* 8009744C 0009234C  90 01 00 5C */	stw r0, 0x5c(r1)
/* 80097450 00092350  C8 41 00 50 */	lfd f2, 0x50(r1)
/* 80097454 00092354  C8 01 00 58 */	lfd f0, 0x58(r1)
/* 80097458 00092358  EC 42 18 28 */	fsubs f2, f2, f3
/* 8009745C 0009235C  EC 00 18 28 */	fsubs f0, f0, f3
/* 80097460 00092360  EF 61 10 24 */	fdivs f27, f1, f2
/* 80097464 00092364  EF 41 00 24 */	fdivs f26, f1, f0
/* 80097468 00092368  48 04 6B 21 */	bl GXSetNumTexGens
/* 8009746C 0009236C  CB 82 8D B0 */	lfd f28, lbl_804C07D0-_SDA2_BASE_(r2)
/* 80097470 00092370  3B 40 00 00 */	li r26, 0
/* 80097474 00092374  CB A2 8D A8 */	lfd f29, lbl_804C07C8-_SDA2_BASE_(r2)
/* 80097478 00092378  3B C0 00 00 */	li r30, 0
/* 8009747C 0009237C  C3 C2 8D A0 */	lfs f30, lbl_804C07C0-_SDA2_BASE_(r2)
/* 80097480 00092380  C3 E2 8D 9C */	lfs f31, lbl_804C07BC-_SDA2_BASE_(r2)
/* 80097484 00092384  C2 E2 8D 98 */	lfs f23, lbl_804C07B8-_SDA2_BASE_(r2)
/* 80097488 00092388  C2 C2 8D 94 */	lfs f22, lbl_804C07B4-_SDA2_BASE_(r2)
/* 8009748C 0009238C  48 00 01 34 */	b lbl_800975C0
lbl_80097490:
/* 80097490 00092390  7F 43 D3 78 */	mr r3, r26
/* 80097494 00092394  48 00 A3 45 */	bl getTexCoordGenVal__Q23EGG9GXUtilityFi
/* 80097498 00092398  7C 79 1B 78 */	mr r25, r3
/* 8009749C 0009239C  7F 43 D3 78 */	mr r3, r26
/* 800974A0 000923A0  7F 26 CB 78 */	mr r6, r25
/* 800974A4 000923A4  38 80 00 01 */	li r4, 1
/* 800974A8 000923A8  38 A0 00 04 */	li r5, 4
/* 800974AC 000923AC  38 E0 00 00 */	li r7, 0
/* 800974B0 000923B0  39 00 00 7D */	li r8, 0x7d
/* 800974B4 000923B4  48 04 68 AD */	bl GXSetTexCoordGen2
/* 800974B8 000923B8  88 1D 00 30 */	lbz r0, 0x30(r29)
/* 800974BC 000923BC  6F 83 80 00 */	xoris r3, r28, 0x8000
/* 800974C0 000923C0  90 61 00 54 */	stw r3, 0x54(r1)
/* 800974C4 000923C4  38 61 00 1C */	addi r3, r1, 0x1c
/* 800974C8 000923C8  C0 1D 00 38 */	lfs f0, 0x38(r29)
/* 800974CC 000923CC  38 81 00 18 */	addi r4, r1, 0x18
/* 800974D0 000923D0  90 01 00 5C */	stw r0, 0x5c(r1)
/* 800974D4 000923D4  C8 41 00 50 */	lfd f2, 0x50(r1)
/* 800974D8 000923D8  C8 21 00 58 */	lfd f1, 0x58(r1)
/* 800974DC 000923DC  EC 42 E0 28 */	fsubs f2, f2, f28
/* 800974E0 000923E0  EC 21 E8 28 */	fsubs f1, f1, f29
/* 800974E4 000923E4  EC 22 08 24 */	fdivs f1, f2, f1
/* 800974E8 000923E8  EC 00 08 2A */	fadds f0, f0, f1
/* 800974EC 000923EC  EC 1E 00 32 */	fmuls f0, f30, f0
/* 800974F0 000923F0  EC 3F 00 32 */	fmuls f1, f31, f0
/* 800974F4 000923F4  4B F9 84 6D */	bl SinCosFIdx__Q24nw4r4mathFPfPff
/* 800974F8 000923F8  C0 41 00 18 */	lfs f2, 0x18(r1)
/* 800974FC 000923FC  EC 3F 05 B2 */	fmuls f1, f31, f22
/* 80097500 00092400  C0 7D 00 3C */	lfs f3, 0x3c(r29)
/* 80097504 00092404  38 61 00 14 */	addi r3, r1, 0x14
/* 80097508 00092408  C0 01 00 1C */	lfs f0, 0x1c(r1)
/* 8009750C 0009240C  38 81 00 10 */	addi r4, r1, 0x10
/* 80097510 00092410  EC 42 00 F2 */	fmuls f2, f2, f3
/* 80097514 00092414  EC 00 00 F2 */	fmuls f0, f0, f3
/* 80097518 00092418  D2 C1 00 20 */	stfs f22, 0x20(r1)
/* 8009751C 0009241C  EF 3B 00 B2 */	fmuls f25, f27, f2
/* 80097520 00092420  D2 C1 00 24 */	stfs f22, 0x24(r1)
/* 80097524 00092424  EF 1A 00 32 */	fmuls f24, f26, f0
/* 80097528 00092428  D2 C1 00 28 */	stfs f22, 0x28(r1)
/* 8009752C 0009242C  4B F9 84 35 */	bl SinCosFIdx__Q24nw4r4mathFPfPff
/* 80097530 00092430  C0 21 00 10 */	lfs f1, 0x10(r1)
/* 80097534 00092434  FC 60 B0 18 */	frsp f3, f22
/* 80097538 00092438  C0 01 00 14 */	lfs f0, 0x14(r1)
/* 8009753C 0009243C  FC 40 B0 18 */	frsp f2, f22
/* 80097540 00092440  EC D7 00 72 */	fmuls f6, f23, f1
/* 80097544 00092444  93 C1 00 30 */	stw r30, 0x30(r1)
/* 80097548 00092448  EC F7 00 32 */	fmuls f7, f23, f0
/* 8009754C 0009244C  93 C1 00 40 */	stw r30, 0x40(r1)
/* 80097550 00092450  7F 24 CB 78 */	mr r4, r25
/* 80097554 00092454  EC 06 00 F2 */	fmuls f0, f6, f3
/* 80097558 00092458  FC A0 38 50 */	fneg f5, f7
/* 8009755C 0009245C  93 C1 00 34 */	stw r30, 0x34(r1)
/* 80097560 00092460  FC 80 30 50 */	fneg f4, f6
/* 80097564 00092464  38 61 00 30 */	addi r3, r1, 0x30
/* 80097568 00092468  EC 27 00 F2 */	fmuls f1, f7, f3
/* 8009756C 0009246C  EC 05 00 B8 */	fmsubs f0, f5, f2, f0
/* 80097570 00092470  93 C1 00 44 */	stw r30, 0x44(r1)
/* 80097574 00092474  38 A0 00 01 */	li r5, 1
/* 80097578 00092478  EC 24 08 BA */	fmadds f1, f4, f2, f1
/* 8009757C 0009247C  EC 03 00 2A */	fadds f0, f3, f0
/* 80097580 00092480  93 C1 00 38 */	stw r30, 0x38(r1)
/* 80097584 00092484  EC 22 08 2A */	fadds f1, f2, f1
/* 80097588 00092488  93 C1 00 48 */	stw r30, 0x48(r1)
/* 8009758C 0009248C  EC 18 00 2A */	fadds f0, f24, f0
/* 80097590 00092490  93 C1 00 3C */	stw r30, 0x3c(r1)
/* 80097594 00092494  EC 39 08 2A */	fadds f1, f25, f1
/* 80097598 00092498  93 C1 00 4C */	stw r30, 0x4c(r1)
/* 8009759C 0009249C  D0 C1 00 30 */	stfs f6, 0x30(r1)
/* 800975A0 000924A0  D0 A1 00 34 */	stfs f5, 0x34(r1)
/* 800975A4 000924A4  D0 21 00 38 */	stfs f1, 0x38(r1)
/* 800975A8 000924A8  D0 E1 00 40 */	stfs f7, 0x40(r1)
/* 800975AC 000924AC  D0 C1 00 44 */	stfs f6, 0x44(r1)
/* 800975B0 000924B0  D0 01 00 48 */	stfs f0, 0x48(r1)
/* 800975B4 000924B4  48 04 BD F1 */	bl GXLoadTexMtxImm
/* 800975B8 000924B8  3B 9C 00 01 */	addi r28, r28, 1
/* 800975BC 000924BC  3B 5A 00 01 */	addi r26, r26, 1
lbl_800975C0:
/* 800975C0 000924C0  7C 1A D8 00 */	cmpw r26, r27
/* 800975C4 000924C4  41 80 FE CC */	blt lbl_80097490
/* 800975C8 000924C8  C0 3F 00 2C */	lfs f1, 0x2c(r31)
/* 800975CC 000924CC  38 61 00 0C */	addi r3, r1, 0xc
/* 800975D0 000924D0  38 9D 00 31 */	addi r4, r29, 0x31
/* 800975D4 000924D4  38 A0 00 01 */	li r5, 1
/* 800975D8 000924D8  4B FF F8 91 */	bl scaleColor__Q23EGG14PostEffectBaseFR8_GXColorRC8_GXColorfb
/* 800975DC 000924DC  80 01 00 0C */	lwz r0, 0xc(r1)
/* 800975E0 000924E0  38 81 00 08 */	addi r4, r1, 8
/* 800975E4 000924E4  38 60 00 00 */	li r3, 0
/* 800975E8 000924E8  90 01 00 08 */	stw r0, 8(r1)
/* 800975EC 000924EC  48 04 A2 21 */	bl GXSetTevKColor
/* 800975F0 000924F0  80 1F 00 24 */	lwz r0, 0x24(r31)
/* 800975F4 000924F4  3B 20 00 0C */	li r25, 0xc
/* 800975F8 000924F8  2C 00 00 00 */	cmpwi r0, 0
/* 800975FC 000924FC  40 82 00 08 */	bne lbl_80097604
/* 80097600 00092500  3B 20 00 0F */	li r25, 0xf
lbl_80097604:
/* 80097604 00092504  2C 00 00 00 */	cmpwi r0, 0
/* 80097608 00092508  3B 40 00 06 */	li r26, 6
/* 8009760C 0009250C  40 82 00 08 */	bne lbl_80097614
/* 80097610 00092510  3B 40 00 07 */	li r26, 7
lbl_80097614:
/* 80097614 00092514  7F 63 DB 78 */	mr r3, r27
/* 80097618 00092518  48 04 A5 C9 */	bl GXSetNumTevStages
/* 8009761C 0009251C  3B 00 00 00 */	li r24, 0
/* 80097620 00092520  48 00 01 18 */	b lbl_80097738
lbl_80097624:
/* 80097624 00092524  7F 03 C3 78 */	mr r3, r24
/* 80097628 00092528  48 04 9E BD */	bl GXSetTevDirect
/* 8009762C 0009252C  7F 03 C3 78 */	mr r3, r24
/* 80097630 00092530  38 80 00 00 */	li r4, 0
/* 80097634 00092534  38 A0 00 00 */	li r5, 0
/* 80097638 00092538  48 04 A2 D1 */	bl GXSetTevSwapMode
/* 8009763C 0009253C  2C 18 00 00 */	cmpwi r24, 0
/* 80097640 00092540  7F 3C CB 78 */	mr r28, r25
/* 80097644 00092544  40 81 00 08 */	ble lbl_8009764C
/* 80097648 00092548  3B 80 00 00 */	li r28, 0
lbl_8009764C:
/* 8009764C 0009254C  2C 18 00 00 */	cmpwi r24, 0
/* 80097650 00092550  7F 5E D3 78 */	mr r30, r26
/* 80097654 00092554  40 81 00 08 */	ble lbl_8009765C
/* 80097658 00092558  3B C0 00 00 */	li r30, 0
lbl_8009765C:
/* 8009765C 0009255C  7F 03 C3 78 */	mr r3, r24
/* 80097660 00092560  38 80 00 0C */	li r4, 0xc
/* 80097664 00092564  48 04 A2 05 */	bl func_800E1868
/* 80097668 00092568  7F 03 C3 78 */	mr r3, r24
/* 8009766C 0009256C  38 80 00 1C */	li r4, 0x1c
/* 80097670 00092570  48 04 A2 49 */	bl func_800E18B8
/* 80097674 00092574  80 BF 00 08 */	lwz r5, 8(r31)
/* 80097678 00092578  7F 03 C3 78 */	mr r3, r24
/* 8009767C 0009257C  7F 04 C3 78 */	mr r4, r24
/* 80097680 00092580  38 C0 00 FF */	li r6, 0xff
/* 80097684 00092584  80 A5 00 18 */	lwz r5, 0x18(r5)
/* 80097688 00092588  48 04 A3 FD */	bl GXSetTevOrder
/* 8009768C 0009258C  80 1F 00 24 */	lwz r0, 0x24(r31)
/* 80097690 00092590  2C 00 00 00 */	cmpwi r0, 0
/* 80097694 00092594  40 82 00 38 */	bne lbl_800976CC
/* 80097698 00092598  7F 03 C3 78 */	mr r3, r24
/* 8009769C 0009259C  7F 87 E3 78 */	mr r7, r28
/* 800976A0 000925A0  38 80 00 0F */	li r4, 0xf
/* 800976A4 000925A4  38 A0 00 08 */	li r5, 8
/* 800976A8 000925A8  38 C0 00 0E */	li r6, 0xe
/* 800976AC 000925AC  48 04 9F 6D */	bl GXSetTevColorIn
/* 800976B0 000925B0  7F 03 C3 78 */	mr r3, r24
/* 800976B4 000925B4  7F C7 F3 78 */	mr r7, r30
/* 800976B8 000925B8  38 80 00 07 */	li r4, 7
/* 800976BC 000925BC  38 A0 00 04 */	li r5, 4
/* 800976C0 000925C0  38 C0 00 06 */	li r6, 6
/* 800976C4 000925C4  48 04 9F 95 */	bl GXSetTevAlphaIn
/* 800976C8 000925C8  48 00 00 34 */	b lbl_800976FC
lbl_800976CC:
/* 800976CC 000925CC  7F 03 C3 78 */	mr r3, r24
/* 800976D0 000925D0  7F 87 E3 78 */	mr r7, r28
/* 800976D4 000925D4  38 80 00 0E */	li r4, 0xe
/* 800976D8 000925D8  38 A0 00 0F */	li r5, 0xf
/* 800976DC 000925DC  38 C0 00 08 */	li r6, 8
/* 800976E0 000925E0  48 04 9F 39 */	bl GXSetTevColorIn
/* 800976E4 000925E4  7F 03 C3 78 */	mr r3, r24
/* 800976E8 000925E8  7F C7 F3 78 */	mr r7, r30
/* 800976EC 000925EC  38 80 00 06 */	li r4, 6
/* 800976F0 000925F0  38 A0 00 07 */	li r5, 7
/* 800976F4 000925F4  38 C0 00 04 */	li r6, 4
/* 800976F8 000925F8  48 04 9F 61 */	bl GXSetTevAlphaIn
lbl_800976FC:
/* 800976FC 000925FC  80 9F 00 24 */	lwz r4, 0x24(r31)
/* 80097700 00092600  7F 03 C3 78 */	mr r3, r24
/* 80097704 00092604  80 DD 00 40 */	lwz r6, 0x40(r29)
/* 80097708 00092608  38 A0 00 00 */	li r5, 0
/* 8009770C 0009260C  38 E0 00 01 */	li r7, 1
/* 80097710 00092610  39 00 00 00 */	li r8, 0
/* 80097714 00092614  48 04 9F 85 */	bl GXSetTevColorOp
/* 80097718 00092618  80 9F 00 24 */	lwz r4, 0x24(r31)
/* 8009771C 0009261C  7F 03 C3 78 */	mr r3, r24
/* 80097720 00092620  80 DD 00 40 */	lwz r6, 0x40(r29)
/* 80097724 00092624  38 A0 00 00 */	li r5, 0
/* 80097728 00092628  38 E0 00 01 */	li r7, 1
/* 8009772C 0009262C  39 00 00 00 */	li r8, 0
/* 80097730 00092630  48 04 9F C1 */	bl GXSetTevAlphaOp
/* 80097734 00092634  3B 18 00 01 */	addi r24, r24, 1
lbl_80097738:
/* 80097738 00092638  7C 18 D8 00 */	cmpw r24, r27
/* 8009773C 0009263C  41 80 FE E8 */	blt lbl_80097624
/* 80097740 00092640  E3 E1 01 18 */	psq_l f31, 280(r1), 0, qr0
/* 80097744 00092644  CB E1 01 10 */	lfd f31, 0x110(r1)
/* 80097748 00092648  E3 C1 01 08 */	psq_l f30, 264(r1), 0, qr0
/* 8009774C 0009264C  CB C1 01 00 */	lfd f30, 0x100(r1)
/* 80097750 00092650  E3 A1 00 F8 */	psq_l f29, 248(r1), 0, qr0
/* 80097754 00092654  CB A1 00 F0 */	lfd f29, 0xf0(r1)
/* 80097758 00092658  E3 81 00 E8 */	psq_l f28, 232(r1), 0, qr0
/* 8009775C 0009265C  CB 81 00 E0 */	lfd f28, 0xe0(r1)
/* 80097760 00092660  E3 61 00 D8 */	psq_l f27, 216(r1), 0, qr0
/* 80097764 00092664  CB 61 00 D0 */	lfd f27, 0xd0(r1)
/* 80097768 00092668  E3 41 00 C8 */	psq_l f26, 200(r1), 0, qr0
/* 8009776C 0009266C  CB 41 00 C0 */	lfd f26, 0xc0(r1)
/* 80097770 00092670  E3 21 00 B8 */	psq_l f25, 184(r1), 0, qr0
/* 80097774 00092674  CB 21 00 B0 */	lfd f25, 0xb0(r1)
/* 80097778 00092678  E3 01 00 A8 */	psq_l f24, 168(r1), 0, qr0
/* 8009777C 0009267C  CB 01 00 A0 */	lfd f24, 0xa0(r1)
/* 80097780 00092680  E2 E1 00 98 */	psq_l f23, 152(r1), 0, qr0
/* 80097784 00092684  CA E1 00 90 */	lfd f23, 0x90(r1)
/* 80097788 00092688  E2 C1 00 88 */	psq_l f22, 136(r1), 0, qr0
/* 8009778C 0009268C  39 61 00 80 */	addi r11, r1, 0x80
/* 80097790 00092690  CA C1 00 80 */	lfd f22, 0x80(r1)
/* 80097794 00092694  48 01 A5 F1 */	bl _restgpr_24
/* 80097798 00092698  80 01 01 24 */	lwz r0, 0x124(r1)
/* 8009779C 0009269C  7C 08 03 A6 */	mtlr r0
/* 800977A0 000926A0  38 21 01 20 */	addi r1, r1, 0x120
/* 800977A4 000926A4  4E 80 00 20 */	blr 
