.include "macros.inc"

.section .text, "ax"  # 0x800076E0 - 0x80355080

.global Emission__Q34nw4r2ef16EmitterFormTorusFPQ34nw4r2ef7EmitterPQ34nw4r2ef15ParticleManageriUlPfUsfPCQ34nw4r4math5MTX34
Emission__Q34nw4r2ef16EmitterFormTorusFPQ34nw4r2ef7EmitterPQ34nw4r2ef15ParticleManageriUlPfUsfPCQ34nw4r4math5MTX34:
/* 8001F1A4 0001A0A4  94 21 FE 00 */	stwu r1, -0x200(r1)
/* 8001F1A8 0001A0A8  7C 08 02 A6 */	mflr r0
/* 8001F1AC 0001A0AC  90 01 02 04 */	stw r0, 0x204(r1)
/* 8001F1B0 0001A0B0  DB E1 01 F0 */	stfd f31, 0x1f0(r1)
/* 8001F1B4 0001A0B4  F3 E1 01 F8 */	psq_st f31, 504(r1), 0, qr0
/* 8001F1B8 0001A0B8  DB C1 01 E0 */	stfd f30, 0x1e0(r1)
/* 8001F1BC 0001A0BC  F3 C1 01 E8 */	psq_st f30, 488(r1), 0, qr0
/* 8001F1C0 0001A0C0  DB A1 01 D0 */	stfd f29, 0x1d0(r1)
/* 8001F1C4 0001A0C4  F3 A1 01 D8 */	psq_st f29, 472(r1), 0, qr0
/* 8001F1C8 0001A0C8  DB 81 01 C0 */	stfd f28, 0x1c0(r1)
/* 8001F1CC 0001A0CC  F3 81 01 C8 */	psq_st f28, 456(r1), 0, qr0
/* 8001F1D0 0001A0D0  DB 61 01 B0 */	stfd f27, 0x1b0(r1)
/* 8001F1D4 0001A0D4  F3 61 01 B8 */	psq_st f27, 440(r1), 0, qr0
/* 8001F1D8 0001A0D8  DB 41 01 A0 */	stfd f26, 0x1a0(r1)
/* 8001F1DC 0001A0DC  F3 41 01 A8 */	psq_st f26, 424(r1), 0, qr0
/* 8001F1E0 0001A0E0  DB 21 01 90 */	stfd f25, 0x190(r1)
/* 8001F1E4 0001A0E4  F3 21 01 98 */	psq_st f25, 408(r1), 0, qr0
/* 8001F1E8 0001A0E8  DB 01 01 80 */	stfd f24, 0x180(r1)
/* 8001F1EC 0001A0EC  F3 01 01 88 */	.4byte 0xF3010188
/* 8001F1F0 0001A0F0  DA E1 01 70 */	stfd f23, 0x170(r1)
/* 8001F1F4 0001A0F4  F2 E1 01 78 */	psq_st f23, 376(r1), 0, qr0
/* 8001F1F8 0001A0F8  DA C1 01 60 */	stfd f22, 0x160(r1)
/* 8001F1FC 0001A0FC  F2 C1 01 68 */	psq_st f22, 360(r1), 0, qr0
/* 8001F200 0001A100  DA A1 01 50 */	stfd f21, 0x150(r1)
/* 8001F204 0001A104  F2 A1 01 58 */	psq_st f21, 344(r1), 0, qr0
/* 8001F208 0001A108  DA 81 01 40 */	stfd f20, 0x140(r1)
/* 8001F20C 0001A10C  F2 81 01 48 */	.4byte 0xF2810148
/* 8001F210 0001A110  DA 61 01 30 */	stfd f19, 0x130(r1)
/* 8001F214 0001A114  F2 61 01 38 */	psq_st f19, 312(r1), 0, qr0
/* 8001F218 0001A118  DA 41 01 20 */	stfd f18, 0x120(r1)
/* 8001F21C 0001A11C  F2 41 01 28 */	psq_st f18, 296(r1), 0, qr0
/* 8001F220 0001A120  DA 21 01 10 */	stfd f17, 0x110(r1)
/* 8001F224 0001A124  F2 21 01 18 */	psq_st f17, 280(r1), 0, qr0
/* 8001F228 0001A128  DA 01 01 00 */	stfd f16, 0x100(r1)
/* 8001F22C 0001A12C  F2 01 01 08 */	.4byte 0xF2010108
/* 8001F230 0001A130  D9 E1 00 F0 */	stfd f15, 0xf0(r1)
/* 8001F234 0001A134  F1 E1 00 F8 */	psq_st f15, 248(r1), 0, qr0
/* 8001F238 0001A138  D9 C1 00 E0 */	stfd f14, 0xe0(r1)
/* 8001F23C 0001A13C  F1 C1 00 E8 */	psq_st f14, 232(r1), 0, qr0
/* 8001F240 0001A140  39 61 00 E0 */	addi r11, r1, 0xe0
/* 8001F244 0001A144  48 09 2A E5 */	bl func_800B1D28
/* 8001F248 0001A148  3C 00 43 30 */	lis r0, 0x4330
/* 8001F24C 0001A14C  2C 06 00 01 */	cmpwi r6, 1
/* 8001F250 0001A150  D0 21 00 08 */	stfs f1, 8(r1)
/* 8001F254 0001A154  7C 74 1B 78 */	mr r20, r3
/* 8001F258 0001A158  7C 95 23 78 */	mr r21, r4
/* 8001F25C 0001A15C  7C B6 2B 78 */	mr r22, r5
/* 8001F260 0001A160  90 01 00 60 */	stw r0, 0x60(r1)
/* 8001F264 0001A164  7C D7 33 78 */	mr r23, r6
/* 8001F268 0001A168  7D 18 43 78 */	mr r24, r8
/* 8001F26C 0001A16C  7D 39 4B 78 */	mr r25, r9
/* 8001F270 0001A170  90 01 00 68 */	stw r0, 0x68(r1)
/* 8001F274 0001A174  7D 5A 53 78 */	mr r26, r10
/* 8001F278 0001A178  41 80 05 24 */	blt lbl_8001F79C
/* 8001F27C 0001A17C  C2 68 00 00 */	lfs f19, 0(r8)
/* 8001F280 0001A180  C0 02 82 B8 */	lfs f0, lbl_804BFCD8-_SDA2_BASE_(r2)
/* 8001F284 0001A184  FC 20 9A 10 */	fabs f1, f19
/* 8001F288 0001A188  FC 20 08 18 */	frsp f1, f1
/* 8001F28C 0001A18C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8001F290 0001A190  40 81 00 08 */	ble lbl_8001F298
/* 8001F294 0001A194  48 00 00 08 */	b lbl_8001F29C
lbl_8001F298:
/* 8001F298 0001A198  FE 60 00 90 */	fmr f19, f0
lbl_8001F29C:
/* 8001F29C 0001A19C  C3 08 00 10 */	lfs f24, 0x10(r8)
/* 8001F2A0 0001A1A0  C0 02 82 B8 */	lfs f0, lbl_804BFCD8-_SDA2_BASE_(r2)
/* 8001F2A4 0001A1A4  FC 20 C2 10 */	fabs f1, f24
/* 8001F2A8 0001A1A8  FC 20 08 18 */	frsp f1, f1
/* 8001F2AC 0001A1AC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8001F2B0 0001A1B0  40 81 00 08 */	ble lbl_8001F2B8
/* 8001F2B4 0001A1B4  48 00 00 08 */	b lbl_8001F2BC
lbl_8001F2B8:
/* 8001F2B8 0001A1B8  FF 00 00 90 */	fmr f24, f0
lbl_8001F2BC:
/* 8001F2BC 0001A1BC  54 E0 01 8D */	rlwinm. r0, r7, 0, 6, 6
/* 8001F2C0 0001A1C0  41 82 00 0C */	beq lbl_8001F2CC
/* 8001F2C4 0001A1C4  FE 40 98 90 */	fmr f18, f19
/* 8001F2C8 0001A1C8  48 00 00 24 */	b lbl_8001F2EC
lbl_8001F2CC:
/* 8001F2CC 0001A1CC  C2 48 00 14 */	lfs f18, 0x14(r8)
/* 8001F2D0 0001A1D0  C0 02 82 B8 */	lfs f0, lbl_804BFCD8-_SDA2_BASE_(r2)
/* 8001F2D4 0001A1D4  FC 20 92 10 */	fabs f1, f18
/* 8001F2D8 0001A1D8  FC 20 08 18 */	frsp f1, f1
/* 8001F2DC 0001A1DC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8001F2E0 0001A1E0  40 81 00 08 */	ble lbl_8001F2E8
/* 8001F2E4 0001A1E4  48 00 00 08 */	b lbl_8001F2EC
lbl_8001F2E8:
/* 8001F2E8 0001A1E8  FE 40 00 90 */	fmr f18, f0
lbl_8001F2EC:
/* 8001F2EC 0001A1EC  C2 22 82 BC */	lfs f17, lbl_804BFCDC-_SDA2_BASE_(r2)
/* 8001F2F0 0001A1F0  54 E0 03 5B */	rlwinm. r0, r7, 0, 0xd, 0xd
/* 8001F2F4 0001A1F4  D2 21 00 70 */	stfs f17, 0x70(r1)
/* 8001F2F8 0001A1F8  41 82 00 0C */	beq lbl_8001F304
/* 8001F2FC 0001A1FC  C2 08 00 08 */	lfs f16, 8(r8)
/* 8001F300 0001A200  48 00 00 4C */	b lbl_8001F34C
lbl_8001F304:
/* 8001F304 0001A204  3C 60 00 03 */	lis r3, 0x000343FD@ha
/* 8001F308 0001A208  80 A4 00 EC */	lwz r5, 0xec(r4)
/* 8001F30C 0001A20C  38 03 43 FD */	addi r0, r3, 0x000343FD@l
/* 8001F310 0001A210  C8 82 82 F0 */	lfd f4, lbl_804BFD10-_SDA2_BASE_(r2)
/* 8001F314 0001A214  7C 65 01 D6 */	mullw r3, r5, r0
/* 8001F318 0001A218  C0 42 82 C0 */	lfs f2, lbl_804BFCE0-_SDA2_BASE_(r2)
/* 8001F31C 0001A21C  C0 22 82 C8 */	lfs f1, lbl_804BFCE8-_SDA2_BASE_(r2)
/* 8001F320 0001A220  C0 02 82 C4 */	lfs f0, lbl_804BFCE4-_SDA2_BASE_(r2)
/* 8001F324 0001A224  3C 63 00 27 */	addis r3, r3, 0x27
/* 8001F328 0001A228  38 63 9E C3 */	addi r3, r3, -24893
/* 8001F32C 0001A22C  54 60 84 3E */	srwi r0, r3, 0x10
/* 8001F330 0001A230  90 64 00 EC */	stw r3, 0xec(r4)
/* 8001F334 0001A234  90 01 00 64 */	stw r0, 0x64(r1)
/* 8001F338 0001A238  C8 61 00 60 */	lfd f3, 0x60(r1)
/* 8001F33C 0001A23C  EC 63 20 28 */	fsubs f3, f3, f4
/* 8001F340 0001A240  EC 43 10 24 */	fdivs f2, f3, f2
/* 8001F344 0001A244  EC 21 00 B2 */	fmuls f1, f1, f2
/* 8001F348 0001A248  EE 00 00 72 */	fmuls f16, f0, f1
lbl_8001F34C:
/* 8001F34C 0001A24C  54 FC 03 9D */	rlwinm. r28, r7, 0, 0xe, 0xe
/* 8001F350 0001A250  41 82 00 90 */	beq lbl_8001F3E0
/* 8001F354 0001A254  C0 28 00 0C */	lfs f1, 0xc(r8)
/* 8001F358 0001A258  C0 08 00 08 */	lfs f0, 8(r8)
/* 8001F35C 0001A25C  C8 42 82 D0 */	lfd f2, lbl_804BFCF0-_SDA2_BASE_(r2)
/* 8001F360 0001A260  EC 21 00 28 */	fsubs f1, f1, f0
/* 8001F364 0001A264  48 0A 1B 19 */	bl func_800C0E7C
/* 8001F368 0001A268  FC 20 08 18 */	frsp f1, f1
/* 8001F36C 0001A26C  C0 02 82 D8 */	lfs f0, lbl_804BFCF8-_SDA2_BASE_(r2)
/* 8001F370 0001A270  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8001F374 0001A274  41 80 00 10 */	blt lbl_8001F384
/* 8001F378 0001A278  C0 02 82 DC */	lfs f0, lbl_804BFCFC-_SDA2_BASE_(r2)
/* 8001F37C 0001A27C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8001F380 0001A280  40 81 00 30 */	ble lbl_8001F3B0
lbl_8001F384:
/* 8001F384 0001A284  A0 15 00 32 */	lhz r0, 0x32(r21)
/* 8001F388 0001A288  C0 78 00 0C */	lfs f3, 0xc(r24)
/* 8001F38C 0001A28C  90 01 00 6C */	stw r0, 0x6c(r1)
/* 8001F390 0001A290  C0 58 00 08 */	lfs f2, 8(r24)
/* 8001F394 0001A294  C8 22 82 F0 */	lfd f1, lbl_804BFD10-_SDA2_BASE_(r2)
/* 8001F398 0001A298  C8 01 00 68 */	lfd f0, 0x68(r1)
/* 8001F39C 0001A29C  EC 43 10 28 */	fsubs f2, f3, f2
/* 8001F3A0 0001A2A0  EC 00 08 28 */	fsubs f0, f0, f1
/* 8001F3A4 0001A2A4  EC 02 00 24 */	fdivs f0, f2, f0
/* 8001F3A8 0001A2A8  D0 01 00 70 */	stfs f0, 0x70(r1)
/* 8001F3AC 0001A2AC  48 00 00 34 */	b lbl_8001F3E0
lbl_8001F3B0:
/* 8001F3B0 0001A2B0  A0 75 00 32 */	lhz r3, 0x32(r21)
/* 8001F3B4 0001A2B4  C0 58 00 0C */	lfs f2, 0xc(r24)
/* 8001F3B8 0001A2B8  38 03 FF FF */	addi r0, r3, -1
/* 8001F3BC 0001A2BC  C0 18 00 08 */	lfs f0, 8(r24)
/* 8001F3C0 0001A2C0  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 8001F3C4 0001A2C4  C8 22 82 F8 */	lfd f1, lbl_804BFD18-_SDA2_BASE_(r2)
/* 8001F3C8 0001A2C8  90 01 00 64 */	stw r0, 0x64(r1)
/* 8001F3CC 0001A2CC  EC 42 00 28 */	fsubs f2, f2, f0
/* 8001F3D0 0001A2D0  C8 01 00 60 */	lfd f0, 0x60(r1)
/* 8001F3D4 0001A2D4  EC 00 08 28 */	fsubs f0, f0, f1
/* 8001F3D8 0001A2D8  EC 02 00 24 */	fdivs f0, f2, f0
/* 8001F3DC 0001A2DC  D0 01 00 70 */	stfs f0, 0x70(r1)
lbl_8001F3E0:
/* 8001F3E0 0001A2E0  2C 1C 00 00 */	cmpwi r28, 0
/* 8001F3E4 0001A2E4  7E FD BB 78 */	mr r29, r23
/* 8001F3E8 0001A2E8  41 82 00 08 */	beq lbl_8001F3F0
/* 8001F3EC 0001A2EC  7F B7 B9 D6 */	mullw r29, r23, r23
lbl_8001F3F0:
/* 8001F3F0 0001A2F0  C0 02 82 C8 */	lfs f0, lbl_804BFCE8-_SDA2_BASE_(r2)
/* 8001F3F4 0001A2F4  3F C0 00 03 */	lis r30, 0x000343FD@ha
/* 8001F3F8 0001A2F8  C1 E2 82 BC */	lfs f15, lbl_804BFCDC-_SDA2_BASE_(r2)
/* 8001F3FC 0001A2FC  3B FE 43 FD */	addi r31, r30, 0x000343FD@l
/* 8001F400 0001A300  D8 01 00 78 */	stfd f0, 0x78(r1)
/* 8001F404 0001A304  3B 60 00 00 */	li r27, 0
/* 8001F408 0001A308  C0 02 82 C4 */	lfs f0, lbl_804BFCE4-_SDA2_BASE_(r2)
/* 8001F40C 0001A30C  FF A0 78 90 */	fmr f29, f15
/* 8001F410 0001A310  FF C0 78 90 */	fmr f30, f15
/* 8001F414 0001A314  CB 42 82 F0 */	lfd f26, lbl_804BFD10-_SDA2_BASE_(r2)
/* 8001F418 0001A318  D8 01 00 80 */	stfd f0, 0x80(r1)
/* 8001F41C 0001A31C  FF E0 78 90 */	fmr f31, f15
/* 8001F420 0001A320  C8 02 82 F8 */	lfd f0, lbl_804BFD18-_SDA2_BASE_(r2)
/* 8001F424 0001A324  C3 62 82 C0 */	lfs f27, lbl_804BFCE0-_SDA2_BASE_(r2)
/* 8001F428 0001A328  D8 01 00 90 */	stfd f0, 0x90(r1)
/* 8001F42C 0001A32C  C0 02 82 E8 */	lfs f0, lbl_804BFD08-_SDA2_BASE_(r2)
/* 8001F430 0001A330  D9 E1 00 88 */	stfd f15, 0x88(r1)
/* 8001F434 0001A334  C3 22 82 E0 */	lfs f25, lbl_804BFD00-_SDA2_BASE_(r2)
/* 8001F438 0001A338  D8 01 00 98 */	stfd f0, 0x98(r1)
/* 8001F43C 0001A33C  C0 02 82 EC */	lfs f0, lbl_804BFD0C-_SDA2_BASE_(r2)
/* 8001F440 0001A340  C3 82 82 E4 */	lfs f28, lbl_804BFD04-_SDA2_BASE_(r2)
/* 8001F444 0001A344  D8 01 00 A0 */	stfd f0, 0xa0(r1)
/* 8001F448 0001A348  48 00 03 4C */	b lbl_8001F794
lbl_8001F44C:
/* 8001F44C 0001A34C  C0 18 00 04 */	lfs f0, 4(r24)
/* 8001F450 0001A350  2C 1C 00 00 */	cmpwi r28, 0
/* 8001F454 0001A354  EC 39 00 28 */	fsubs f1, f25, f0
/* 8001F458 0001A358  EC 19 00 2A */	fadds f0, f25, f0
/* 8001F45C 0001A35C  ED C1 00 24 */	fdivs f14, f1, f0
/* 8001F460 0001A360  40 82 00 74 */	bne lbl_8001F4D4
/* 8001F464 0001A364  80 15 00 EC */	lwz r0, 0xec(r21)
/* 8001F468 0001A368  38 9E 43 FD */	addi r4, r30, 0x43fd
/* 8001F46C 0001A36C  7C 60 21 D6 */	mullw r3, r0, r4
/* 8001F470 0001A370  3C 63 00 27 */	addis r3, r3, 0x27
/* 8001F474 0001A374  38 03 9E C3 */	addi r0, r3, -24893
/* 8001F478 0001A378  7C 60 21 D6 */	mullw r3, r0, r4
/* 8001F47C 0001A37C  90 15 00 EC */	stw r0, 0xec(r21)
/* 8001F480 0001A380  54 00 84 3E */	srwi r0, r0, 0x10
/* 8001F484 0001A384  90 01 00 6C */	stw r0, 0x6c(r1)
/* 8001F488 0001A388  C0 58 00 0C */	lfs f2, 0xc(r24)
/* 8001F48C 0001A38C  C8 01 00 68 */	lfd f0, 0x68(r1)
/* 8001F490 0001A390  3C 63 00 27 */	addis r3, r3, 0x27
/* 8001F494 0001A394  EC 00 D0 28 */	fsubs f0, f0, f26
/* 8001F498 0001A398  38 63 9E C3 */	addi r3, r3, -24893
/* 8001F49C 0001A39C  C0 38 00 08 */	lfs f1, 8(r24)
/* 8001F4A0 0001A3A0  54 60 84 3E */	srwi r0, r3, 0x10
/* 8001F4A4 0001A3A4  90 01 00 64 */	stw r0, 0x64(r1)
/* 8001F4A8 0001A3A8  EC 60 D8 24 */	fdivs f3, f0, f27
/* 8001F4AC 0001A3AC  C8 01 00 60 */	lfd f0, 0x60(r1)
/* 8001F4B0 0001A3B0  90 75 00 EC */	stw r3, 0xec(r21)
/* 8001F4B4 0001A3B4  EC 42 08 28 */	fsubs f2, f2, f1
/* 8001F4B8 0001A3B8  EC 00 D0 28 */	fsubs f0, f0, f26
/* 8001F4BC 0001A3BC  EE 22 00 F2 */	fmuls f17, f2, f3
/* 8001F4C0 0001A3C0  EC 20 D8 24 */	fdivs f1, f0, f27
/* 8001F4C4 0001A3C4  C8 01 00 78 */	lfd f0, 0x78(r1)
/* 8001F4C8 0001A3C8  EC 20 00 72 */	fmuls f1, f0, f1
/* 8001F4CC 0001A3CC  C8 01 00 80 */	lfd f0, 0x80(r1)
/* 8001F4D0 0001A3D0  ED E0 00 72 */	fmuls f15, f0, f1
lbl_8001F4D4:
/* 8001F4D4 0001A3D4  EC 30 88 2A */	fadds f1, f16, f17
/* 8001F4D8 0001A3D8  48 0A 18 49 */	bl func_800C0D20
/* 8001F4DC 0001A3DC  FE E0 08 18 */	frsp f23, f1
/* 8001F4E0 0001A3E0  EC 30 88 2A */	fadds f1, f16, f17
/* 8001F4E4 0001A3E4  48 0A 13 35 */	bl func_800C0818
/* 8001F4E8 0001A3E8  FE C0 08 18 */	frsp f22, f1
/* 8001F4EC 0001A3EC  FC 20 78 90 */	fmr f1, f15
/* 8001F4F0 0001A3F0  48 0A 18 31 */	bl func_800C0D20
/* 8001F4F4 0001A3F4  FE A0 08 18 */	frsp f21, f1
/* 8001F4F8 0001A3F8  FC 20 78 90 */	fmr f1, f15
/* 8001F4FC 0001A3FC  48 0A 13 1D */	bl func_800C0818
/* 8001F500 0001A400  FE 80 08 18 */	frsp f20, f1
/* 8001F504 0001A404  FC 00 70 50 */	fneg f0, f14
/* 8001F508 0001A408  EC 38 05 72 */	fmuls f1, f24, f21
/* 8001F50C 0001A40C  EC 4E 05 32 */	fmuls f2, f14, f20
/* 8001F510 0001A410  EC 00 05 32 */	fmuls f0, f0, f20
/* 8001F514 0001A414  D0 21 00 58 */	stfs f1, 0x58(r1)
/* 8001F518 0001A418  EC 3C 70 2A */	fadds f1, f28, f14
/* 8001F51C 0001A41C  EC 57 00 B2 */	fmuls f2, f23, f2
/* 8001F520 0001A420  EC 16 00 32 */	fmuls f0, f22, f0
/* 8001F524 0001A424  80 01 00 58 */	lwz r0, 0x58(r1)
/* 8001F528 0001A428  EC 57 10 2A */	fadds f2, f23, f2
/* 8001F52C 0001A42C  90 01 00 40 */	stw r0, 0x40(r1)
/* 8001F530 0001A430  EC 00 B0 28 */	fsubs f0, f0, f22
/* 8001F534 0001A434  EC 53 00 B2 */	fmuls f2, f19, f2
/* 8001F538 0001A438  EC 12 00 32 */	fmuls f0, f18, f0
/* 8001F53C 0001A43C  EC 42 08 24 */	fdivs f2, f2, f1
/* 8001F540 0001A440  EC 20 08 24 */	fdivs f1, f0, f1
/* 8001F544 0001A444  D0 41 00 54 */	stfs f2, 0x54(r1)
/* 8001F548 0001A448  80 01 00 54 */	lwz r0, 0x54(r1)
/* 8001F54C 0001A44C  90 01 00 3C */	stw r0, 0x3c(r1)
/* 8001F550 0001A450  C0 01 00 3C */	lfs f0, 0x3c(r1)
/* 8001F554 0001A454  D0 21 00 5C */	stfs f1, 0x5c(r1)
/* 8001F558 0001A458  FC 1D 00 00 */	fcmpu cr0, f29, f0
/* 8001F55C 0001A45C  80 01 00 5C */	lwz r0, 0x5c(r1)
/* 8001F560 0001A460  90 01 00 44 */	stw r0, 0x44(r1)
/* 8001F564 0001A464  40 82 00 1C */	bne lbl_8001F580
/* 8001F568 0001A468  C0 01 00 40 */	lfs f0, 0x40(r1)
/* 8001F56C 0001A46C  FC 1D 00 00 */	fcmpu cr0, f29, f0
/* 8001F570 0001A470  40 82 00 10 */	bne lbl_8001F580
/* 8001F574 0001A474  C0 01 00 44 */	lfs f0, 0x44(r1)
/* 8001F578 0001A478  FC 1D 00 00 */	fcmpu cr0, f29, f0
/* 8001F57C 0001A47C  41 82 00 10 */	beq lbl_8001F58C
lbl_8001F580:
/* 8001F580 0001A480  38 61 00 3C */	addi r3, r1, 0x3c
/* 8001F584 0001A484  7C 64 1B 78 */	mr r4, r3
/* 8001F588 0001A488  48 0C 8F 8D */	bl func_800E8514
lbl_8001F58C:
/* 8001F58C 0001A48C  C0 01 00 54 */	lfs f0, 0x54(r1)
/* 8001F590 0001A490  C0 21 00 5C */	lfs f1, 0x5c(r1)
/* 8001F594 0001A494  FC 1E 00 00 */	fcmpu cr0, f30, f0
/* 8001F598 0001A498  D0 01 00 30 */	stfs f0, 0x30(r1)
/* 8001F59C 0001A49C  D3 C1 00 34 */	stfs f30, 0x34(r1)
/* 8001F5A0 0001A4A0  D0 21 00 38 */	stfs f1, 0x38(r1)
/* 8001F5A4 0001A4A4  40 82 00 0C */	bne lbl_8001F5B0
/* 8001F5A8 0001A4A8  FC 1E 08 00 */	fcmpu cr0, f30, f1
/* 8001F5AC 0001A4AC  41 82 00 10 */	beq lbl_8001F5BC
lbl_8001F5B0:
/* 8001F5B0 0001A4B0  38 61 00 30 */	addi r3, r1, 0x30
/* 8001F5B4 0001A4B4  7C 64 1B 78 */	mr r4, r3
/* 8001F5B8 0001A4B8  48 0C 8F 5D */	bl func_800E8514
lbl_8001F5BC:
/* 8001F5BC 0001A4BC  C8 01 00 88 */	lfd f0, 0x88(r1)
/* 8001F5C0 0001A4C0  FC 00 70 00 */	fcmpu cr0, f0, f14
/* 8001F5C4 0001A4C4  40 82 00 2C */	bne lbl_8001F5F0
/* 8001F5C8 0001A4C8  FC 00 90 50 */	fneg f0, f18
/* 8001F5CC 0001A4CC  EC 53 05 32 */	fmuls f2, f19, f20
/* 8001F5D0 0001A4D0  EC 38 05 72 */	fmuls f1, f24, f21
/* 8001F5D4 0001A4D4  EC 00 05 32 */	fmuls f0, f0, f20
/* 8001F5D8 0001A4D8  EC 57 00 B2 */	fmuls f2, f23, f2
/* 8001F5DC 0001A4DC  D0 21 00 28 */	stfs f1, 0x28(r1)
/* 8001F5E0 0001A4E0  EC 16 00 32 */	fmuls f0, f22, f0
/* 8001F5E4 0001A4E4  D0 41 00 24 */	stfs f2, 0x24(r1)
/* 8001F5E8 0001A4E8  D0 01 00 2C */	stfs f0, 0x2c(r1)
/* 8001F5EC 0001A4EC  48 00 00 3C */	b lbl_8001F628
lbl_8001F5F0:
/* 8001F5F0 0001A4F0  FC 00 70 50 */	fneg f0, f14
/* 8001F5F4 0001A4F4  EC 4E 05 32 */	fmuls f2, f14, f20
/* 8001F5F8 0001A4F8  EC 38 05 72 */	fmuls f1, f24, f21
/* 8001F5FC 0001A4FC  EC 00 05 32 */	fmuls f0, f0, f20
/* 8001F600 0001A500  EC 77 00 B2 */	fmuls f3, f23, f2
/* 8001F604 0001A504  D0 21 00 28 */	stfs f1, 0x28(r1)
/* 8001F608 0001A508  EC 5C 70 2A */	fadds f2, f28, f14
/* 8001F60C 0001A50C  EC 16 00 32 */	fmuls f0, f22, f0
/* 8001F610 0001A510  EC 33 00 F2 */	fmuls f1, f19, f3
/* 8001F614 0001A514  EC 12 00 32 */	fmuls f0, f18, f0
/* 8001F618 0001A518  EC 21 10 24 */	fdivs f1, f1, f2
/* 8001F61C 0001A51C  EC 00 10 24 */	fdivs f0, f0, f2
/* 8001F620 0001A520  D0 21 00 24 */	stfs f1, 0x24(r1)
/* 8001F624 0001A524  D0 01 00 2C */	stfs f0, 0x2c(r1)
lbl_8001F628:
/* 8001F628 0001A528  C0 01 00 24 */	lfs f0, 0x24(r1)
/* 8001F62C 0001A52C  FC 1F 00 00 */	fcmpu cr0, f31, f0
/* 8001F630 0001A530  40 82 00 1C */	bne lbl_8001F64C
/* 8001F634 0001A534  C0 01 00 28 */	lfs f0, 0x28(r1)
/* 8001F638 0001A538  FC 1F 00 00 */	fcmpu cr0, f31, f0
/* 8001F63C 0001A53C  40 82 00 10 */	bne lbl_8001F64C
/* 8001F640 0001A540  C0 01 00 2C */	lfs f0, 0x2c(r1)
/* 8001F644 0001A544  FC 1F 00 00 */	fcmpu cr0, f31, f0
/* 8001F648 0001A548  41 82 00 10 */	beq lbl_8001F658
lbl_8001F64C:
/* 8001F64C 0001A54C  38 61 00 24 */	addi r3, r1, 0x24
/* 8001F650 0001A550  7C 64 1B 78 */	mr r4, r3
/* 8001F654 0001A554  48 0C 8E C1 */	bl func_800E8514
lbl_8001F658:
/* 8001F658 0001A558  7E 83 A3 78 */	mr r3, r20
/* 8001F65C 0001A55C  7E A5 AB 78 */	mr r5, r21
/* 8001F660 0001A560  38 81 00 48 */	addi r4, r1, 0x48
/* 8001F664 0001A564  38 C1 00 54 */	addi r6, r1, 0x54
/* 8001F668 0001A568  38 E1 00 24 */	addi r7, r1, 0x24
/* 8001F66C 0001A56C  39 01 00 3C */	addi r8, r1, 0x3c
/* 8001F670 0001A570  39 21 00 30 */	addi r9, r1, 0x30
/* 8001F674 0001A574  4B FF D5 11 */	bl CalcVelocity__Q34nw4r2ef11EmitterFormCFPQ34nw4r4math4VEC3PQ34nw4r2ef7EmitterRCQ34nw4r4math4VEC3RCQ34nw4r4math4VEC3RCQ34nw4r4math4VEC3RCQ34nw4r4math4VEC3
/* 8001F678 0001A578  80 15 00 EC */	lwz r0, 0xec(r21)
/* 8001F67C 0001A57C  7E 83 A3 78 */	mr r3, r20
/* 8001F680 0001A580  C0 21 00 08 */	lfs f1, 8(r1)
/* 8001F684 0001A584  7F 24 CB 78 */	mr r4, r25
/* 8001F688 0001A588  7C C0 F9 D6 */	mullw r6, r0, r31
/* 8001F68C 0001A58C  7E A5 AB 78 */	mr r5, r21
/* 8001F690 0001A590  3C C6 00 27 */	addis r6, r6, 0x27
/* 8001F694 0001A594  38 C6 9E C3 */	addi r6, r6, -24893
/* 8001F698 0001A598  54 C0 84 3E */	srwi r0, r6, 0x10
/* 8001F69C 0001A59C  90 D5 00 EC */	stw r6, 0xec(r21)
/* 8001F6A0 0001A5A0  90 01 00 6C */	stw r0, 0x6c(r1)
/* 8001F6A4 0001A5A4  81 41 00 48 */	lwz r10, 0x48(r1)
/* 8001F6A8 0001A5A8  C8 01 00 68 */	lfd f0, 0x68(r1)
/* 8001F6AC 0001A5AC  81 21 00 4C */	lwz r9, 0x4c(r1)
/* 8001F6B0 0001A5B0  EC 00 D0 28 */	fsubs f0, f0, f26
/* 8001F6B4 0001A5B4  81 01 00 50 */	lwz r8, 0x50(r1)
/* 8001F6B8 0001A5B8  80 E1 00 54 */	lwz r7, 0x54(r1)
/* 8001F6BC 0001A5BC  80 C1 00 58 */	lwz r6, 0x58(r1)
/* 8001F6C0 0001A5C0  EE 80 D8 24 */	fdivs f20, f0, f27
/* 8001F6C4 0001A5C4  80 01 00 5C */	lwz r0, 0x5c(r1)
/* 8001F6C8 0001A5C8  91 41 00 0C */	stw r10, 0xc(r1)
/* 8001F6CC 0001A5CC  91 21 00 10 */	stw r9, 0x10(r1)
/* 8001F6D0 0001A5D0  91 01 00 14 */	stw r8, 0x14(r1)
/* 8001F6D4 0001A5D4  90 E1 00 18 */	stw r7, 0x18(r1)
/* 8001F6D8 0001A5D8  90 C1 00 1C */	stw r6, 0x1c(r1)
/* 8001F6DC 0001A5DC  90 01 00 20 */	stw r0, 0x20(r1)
/* 8001F6E0 0001A5E0  4B FF D9 C1 */	bl CalcLife__Q34nw4r2ef11EmitterFormFUsfPQ34nw4r2ef7Emitter
/* 8001F6E4 0001A5E4  88 15 00 67 */	lbz r0, 0x67(r21)
/* 8001F6E8 0001A5E8  7C 64 1B 78 */	mr r4, r3
/* 8001F6EC 0001A5EC  81 96 00 1C */	lwz r12, 0x1c(r22)
/* 8001F6F0 0001A5F0  7E C3 B3 78 */	mr r3, r22
/* 8001F6F4 0001A5F4  7C 00 07 74 */	extsb r0, r0
/* 8001F6F8 0001A5F8  C8 01 00 90 */	lfd f0, 0x90(r1)
/* 8001F6FC 0001A5FC  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 8001F700 0001A600  81 8C 00 14 */	lwz r12, 0x14(r12)
/* 8001F704 0001A604  90 01 00 64 */	stw r0, 0x64(r1)
/* 8001F708 0001A608  7F 47 D3 78 */	mr r7, r26
/* 8001F70C 0001A60C  54 84 04 3E */	clrlwi r4, r4, 0x10
/* 8001F710 0001A610  38 A1 00 18 */	addi r5, r1, 0x18
/* 8001F714 0001A614  C8 21 00 60 */	lfd f1, 0x60(r1)
/* 8001F718 0001A618  38 C1 00 0C */	addi r6, r1, 0xc
/* 8001F71C 0001A61C  39 15 00 FC */	addi r8, r21, 0xfc
/* 8001F720 0001A620  81 35 00 F8 */	lwz r9, 0xf8(r21)
/* 8001F724 0001A624  EC 21 00 28 */	fsubs f1, f1, f0
/* 8001F728 0001A628  C8 01 00 98 */	lfd f0, 0x98(r1)
/* 8001F72C 0001A62C  A1 55 00 E8 */	lhz r10, 0xe8(r21)
/* 8001F730 0001A630  EC 00 00 72 */	fmuls f0, f0, f1
/* 8001F734 0001A634  EC 00 05 32 */	fmuls f0, f0, f20
/* 8001F738 0001A638  EC 3C 00 2A */	fadds f1, f28, f0
/* 8001F73C 0001A63C  7D 89 03 A6 */	mtctr r12
/* 8001F740 0001A640  4E 80 04 21 */	bctrl 
/* 8001F744 0001A644  2C 1C 00 00 */	cmpwi r28, 0
/* 8001F748 0001A648  41 82 00 48 */	beq lbl_8001F790
/* 8001F74C 0001A64C  38 7B 00 01 */	addi r3, r27, 1
/* 8001F750 0001A650  7C 03 BB D6 */	divw r0, r3, r23
/* 8001F754 0001A654  7C 00 B9 D6 */	mullw r0, r0, r23
/* 8001F758 0001A658  7C 00 18 51 */	subf. r0, r0, r3
/* 8001F75C 0001A65C  40 82 00 14 */	bne lbl_8001F770
/* 8001F760 0001A660  C0 01 00 70 */	lfs f0, 0x70(r1)
/* 8001F764 0001A664  C1 E2 82 BC */	lfs f15, lbl_804BFCDC-_SDA2_BASE_(r2)
/* 8001F768 0001A668  EE 31 00 2A */	fadds f17, f17, f0
/* 8001F76C 0001A66C  48 00 00 24 */	b lbl_8001F790
lbl_8001F770:
/* 8001F770 0001A670  6E E0 80 00 */	xoris r0, r23, 0x8000
/* 8001F774 0001A674  C8 01 00 90 */	lfd f0, 0x90(r1)
/* 8001F778 0001A678  90 01 00 6C */	stw r0, 0x6c(r1)
/* 8001F77C 0001A67C  C8 21 00 68 */	lfd f1, 0x68(r1)
/* 8001F780 0001A680  EC 21 00 28 */	fsubs f1, f1, f0
/* 8001F784 0001A684  C8 01 00 A0 */	lfd f0, 0xa0(r1)
/* 8001F788 0001A688  EC 00 08 24 */	fdivs f0, f0, f1
/* 8001F78C 0001A68C  ED EF 00 2A */	fadds f15, f15, f0
lbl_8001F790:
/* 8001F790 0001A690  3B 7B 00 01 */	addi r27, r27, 1
lbl_8001F794:
/* 8001F794 0001A694  7C 1B E8 00 */	cmpw r27, r29
/* 8001F798 0001A698  41 80 FC B4 */	blt lbl_8001F44C
lbl_8001F79C:
/* 8001F79C 0001A69C  E3 E1 01 F8 */	psq_l f31, 504(r1), 0, qr0
/* 8001F7A0 0001A6A0  CB E1 01 F0 */	lfd f31, 0x1f0(r1)
/* 8001F7A4 0001A6A4  E3 C1 01 E8 */	psq_l f30, 488(r1), 0, qr0
/* 8001F7A8 0001A6A8  CB C1 01 E0 */	lfd f30, 0x1e0(r1)
/* 8001F7AC 0001A6AC  E3 A1 01 D8 */	psq_l f29, 472(r1), 0, qr0
/* 8001F7B0 0001A6B0  CB A1 01 D0 */	lfd f29, 0x1d0(r1)
/* 8001F7B4 0001A6B4  E3 81 01 C8 */	psq_l f28, 456(r1), 0, qr0
/* 8001F7B8 0001A6B8  CB 81 01 C0 */	lfd f28, 0x1c0(r1)
/* 8001F7BC 0001A6BC  E3 61 01 B8 */	psq_l f27, 440(r1), 0, qr0
/* 8001F7C0 0001A6C0  CB 61 01 B0 */	lfd f27, 0x1b0(r1)
/* 8001F7C4 0001A6C4  E3 41 01 A8 */	psq_l f26, 424(r1), 0, qr0
/* 8001F7C8 0001A6C8  CB 41 01 A0 */	lfd f26, 0x1a0(r1)
/* 8001F7CC 0001A6CC  E3 21 01 98 */	psq_l f25, 408(r1), 0, qr0
/* 8001F7D0 0001A6D0  CB 21 01 90 */	lfd f25, 0x190(r1)
/* 8001F7D4 0001A6D4  E3 01 01 88 */	psq_l f24, 392(r1), 0, qr0
/* 8001F7D8 0001A6D8  CB 01 01 80 */	lfd f24, 0x180(r1)
/* 8001F7DC 0001A6DC  E2 E1 01 78 */	psq_l f23, 376(r1), 0, qr0
/* 8001F7E0 0001A6E0  CA E1 01 70 */	lfd f23, 0x170(r1)
/* 8001F7E4 0001A6E4  E2 C1 01 68 */	psq_l f22, 360(r1), 0, qr0
/* 8001F7E8 0001A6E8  CA C1 01 60 */	lfd f22, 0x160(r1)
/* 8001F7EC 0001A6EC  E2 A1 01 58 */	psq_l f21, 344(r1), 0, qr0
/* 8001F7F0 0001A6F0  CA A1 01 50 */	lfd f21, 0x150(r1)
/* 8001F7F4 0001A6F4  E2 81 01 48 */	psq_l f20, 328(r1), 0, qr0
/* 8001F7F8 0001A6F8  CA 81 01 40 */	lfd f20, 0x140(r1)
/* 8001F7FC 0001A6FC  E2 61 01 38 */	psq_l f19, 312(r1), 0, qr0
/* 8001F800 0001A700  CA 61 01 30 */	lfd f19, 0x130(r1)
/* 8001F804 0001A704  E2 41 01 28 */	psq_l f18, 296(r1), 0, qr0
/* 8001F808 0001A708  CA 41 01 20 */	lfd f18, 0x120(r1)
/* 8001F80C 0001A70C  E2 21 01 18 */	psq_l f17, 280(r1), 0, qr0
/* 8001F810 0001A710  CA 21 01 10 */	lfd f17, 0x110(r1)
/* 8001F814 0001A714  E2 01 01 08 */	psq_l f16, 264(r1), 0, qr0
/* 8001F818 0001A718  CA 01 01 00 */	lfd f16, 0x100(r1)
/* 8001F81C 0001A71C  E1 E1 00 F8 */	psq_l f15, 248(r1), 0, qr0
/* 8001F820 0001A720  C9 E1 00 F0 */	lfd f15, 0xf0(r1)
/* 8001F824 0001A724  E1 C1 00 E8 */	psq_l f14, 232(r1), 0, qr0
/* 8001F828 0001A728  39 61 00 E0 */	addi r11, r1, 0xe0
/* 8001F82C 0001A72C  C9 C1 00 E0 */	lfd f14, 0xe0(r1)
/* 8001F830 0001A730  48 09 25 45 */	bl func_800B1D74
/* 8001F834 0001A734  80 01 02 04 */	lwz r0, 0x204(r1)
/* 8001F838 0001A738  7C 08 03 A6 */	mtlr r0
/* 8001F83C 0001A73C  38 21 02 00 */	addi r1, r1, 0x200
/* 8001F840 0001A740  4E 80 00 20 */	blr 
