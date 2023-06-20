.include "macros.inc"

.section .sdata2, "a"
.balign 0x8
.global lbl_804C0FC8
lbl_804C0FC8:
	.incbin "baserom.dol", 0x3C9C08, 0x4
.global lbl_804C0FCC
lbl_804C0FCC:
	.incbin "baserom.dol", 0x3C9C0C, 0x4
.global lbl_804C0FD0
lbl_804C0FD0:
	.incbin "baserom.dol", 0x3C9C10, 0x4
.global lbl_804C0FD4
lbl_804C0FD4:
	.incbin "baserom.dol", 0x3C9C14, 0x4
.global lbl_804C0FD8
lbl_804C0FD8:
	.incbin "baserom.dol", 0x3C9C18, 0x4
.global lbl_804C0FDC
lbl_804C0FDC:
	.incbin "baserom.dol", 0x3C9C1C, 0x4
.global lbl_804C0FE0
lbl_804C0FE0:
	.incbin "baserom.dol", 0x3C9C20, 0x4
.global lbl_804C0FE4
lbl_804C0FE4:
	.incbin "baserom.dol", 0x3C9C24, 0x4
.global lbl_804C0FE8
lbl_804C0FE8:
	.incbin "baserom.dol", 0x3C9C28, 0x4
.global lbl_804C0FEC
lbl_804C0FEC:
	.incbin "baserom.dol", 0x3C9C2C, 0x4
.global lbl_804C0FF0
lbl_804C0FF0:
	.incbin "baserom.dol", 0x3C9C30, 0x8
.global lbl_804C0FF8
lbl_804C0FF8:
	.incbin "baserom.dol", 0x3C9C38, 0x8
.global lbl_804C1000
lbl_804C1000:
	.incbin "baserom.dol", 0x3C9C40, 0x4
.global lbl_804C1004
lbl_804C1004:
	.incbin "baserom.dol", 0x3C9C44, 0x4
.global lbl_804C1008
lbl_804C1008:
	.incbin "baserom.dol", 0x3C9C48, 0x4
.global lbl_804C100C
lbl_804C100C:
	.incbin "baserom.dol", 0x3C9C4C, 0x2
.global lbl_804C100E
lbl_804C100E:
	.incbin "baserom.dol", 0x3C9C4E, 0x2
.global lbl_804C1010
lbl_804C1010:
	.incbin "baserom.dol", 0x3C9C50, 0x4
.global lbl_804C1014
lbl_804C1014:
	.incbin "baserom.dol", 0x3C9C54, 0x2
.global lbl_804C1016
lbl_804C1016:
	.incbin "baserom.dol", 0x3C9C56, 0x2
.global lbl_804C1018
lbl_804C1018:
	.incbin "baserom.dol", 0x3C9C58, 0x4
.global lbl_804C101C
lbl_804C101C:
	.incbin "baserom.dol", 0x3C9C5C, 0x4
.global lbl_804C1020
lbl_804C1020:
	.incbin "baserom.dol", 0x3C9C60, 0x8
.global lbl_804C1028
lbl_804C1028:
	.incbin "baserom.dol", 0x3C9C68, 0x8

.section .sdata, "wa"
.balign 0x8
.global __KPADVersion
__KPADVersion:
	.incbin "baserom.dol", 0x3C71E0, 0x4
idist_org:
	.incbin "baserom.dol", 0x3C71E4, 0x4
iaccXY_nrm_hori:
	.incbin "baserom.dol", 0x3C71E8, 0x8
isec_nrm_hori:
	.incbin "baserom.dol", 0x3C71F0, 0x8
.global kp_obj_interval
kp_obj_interval:
	.incbin "baserom.dol", 0x3C71F8, 0x4
.global kp_acc_horizon_pw
kp_acc_horizon_pw:
	.incbin "baserom.dol", 0x3C71FC, 0x4
.global kp_ah_circle_radius
kp_ah_circle_radius:
	.incbin "baserom.dol", 0x3C7200, 0x4
.global kp_ah_circle_pw
kp_ah_circle_pw:
	.incbin "baserom.dol", 0x3C7204, 0x4
.global kp_ah_circle_ct
kp_ah_circle_ct:
	.incbin "baserom.dol", 0x3C7208, 0x4
.global kp_err_outside_frame
kp_err_outside_frame:
	.incbin "baserom.dol", 0x3C720C, 0x4
.global kp_err_dist_max
kp_err_dist_max:
	.incbin "baserom.dol", 0x3C7210, 0x4
.global kp_err_dist_speed
kp_err_dist_speed:
	.incbin "baserom.dol", 0x3C7214, 0x4
.global kp_err_first_inpr
kp_err_first_inpr:
	.incbin "baserom.dol", 0x3C7218, 0x4
.global kp_err_next_inpr
kp_err_next_inpr:
	.incbin "baserom.dol", 0x3C721C, 0x4
.global kp_err_acc_inpr
kp_err_acc_inpr:
	.incbin "baserom.dol", 0x3C7220, 0x4
.global kp_err_up_inpr
kp_err_up_inpr:
	.incbin "baserom.dol", 0x3C7224, 0x4
.global kp_err_near_pos
kp_err_near_pos:
	.incbin "baserom.dol", 0x3C7228, 0x4
kp_fs_fstick_min:
	.incbin "baserom.dol", 0x3C722C, 0x4
kp_fs_fstick_max:
	.incbin "baserom.dol", 0x3C7230, 0x4
kp_cl_stick_min:
	.incbin "baserom.dol", 0x3C7234, 0x4
kp_cl_stick_max:
	.incbin "baserom.dol", 0x3C7238, 0x4
kp_cl_trigger_min:
	.incbin "baserom.dol", 0x3C723C, 0x4
kp_cl_trigger_max:
	.incbin "baserom.dol", 0x3C7240, 0x4
kp_rm_acc_max:
	.incbin "baserom.dol", 0x3C7244, 0x4
kp_fs_acc_max:
	.incbin "baserom.dol", 0x3C7248, 0x8

.section .sbss, "wa"
.balign 0x8
icenter_org:
	.skip 0x8
.global kp_stick_clamp_cross
kp_stick_clamp_cross:
    # real size = 0x4
	.skip 0x8
Vec2_0:
	.skip 0x8
kp_dist_vv1:
	.skip 0x4
.global kp_err_dist_min
kp_err_dist_min:
	.skip 0x4

.section .data, "wa"
.balign 0x8
lbl_80399418:
    .string "<< RVL_SDK - KPAD \trelease build: Jun  5 2007 11:27:45 (0x4199_60831) >>"
    .balign 4
table$3298:
	.incbin "baserom.dol", 0x395564, 0xC

.section .bss, "wa"
.balign 0x8
.global inside_kpads
inside_kpads:
	.skip 0x14A8

.section .text, "ax"
.global KPADSetBtnRepeat
KPADSetBtnRepeat:
/* 800C72D0 000C21D0  C0 02 95 A8 */	lfs f0, lbl_804C0FC8-_SDA2_BASE_(r2)
/* 800C72D4 000C21D4  3C 80 80 41 */	lis r4, inside_kpads@ha
/* 800C72D8 000C21D8  1C 03 05 24 */	mulli r0, r3, 0x524
/* 800C72DC 000C21DC  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800C72E0 000C21E0  FC 02 00 00 */	fcmpu cr0, f2, f0
/* 800C72E4 000C21E4  38 84 E1 58 */	addi r4, r4, inside_kpads@l
/* 800C72E8 000C21E8  7C 84 02 14 */	add r4, r4, r0
/* 800C72EC 000C21EC  41 82 00 40 */	beq lbl_800C732C
/* 800C72F0 000C21F0  C0 02 95 B0 */	lfs f0, lbl_804C0FD0-_SDA2_BASE_(r2)
/* 800C72F4 000C21F4  C0 62 95 AC */	lfs f3, lbl_804C0FCC-_SDA2_BASE_(r2)
/* 800C72F8 000C21F8  EC 20 00 72 */	fmuls f1, f0, f1
/* 800C72FC 000C21FC  EC 00 00 B2 */	fmuls f0, f0, f2
/* 800C7300 000C2200  EC 23 08 2A */	fadds f1, f3, f1
/* 800C7304 000C2204  EC 03 00 2A */	fadds f0, f3, f0
/* 800C7308 000C2208  FC 20 08 1E */	fctiwz f1, f1
/* 800C730C 000C220C  FC 00 00 1E */	fctiwz f0, f0
/* 800C7310 000C2210  D8 21 00 08 */	stfd f1, 8(r1)
/* 800C7314 000C2214  D8 01 00 10 */	stfd f0, 0x10(r1)
/* 800C7318 000C2218  80 61 00 0C */	lwz r3, 0xc(r1)
/* 800C731C 000C221C  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800C7320 000C2220  B0 64 04 D0 */	sth r3, 0x4d0(r4)
/* 800C7324 000C2224  B0 04 04 D2 */	sth r0, 0x4d2(r4)
/* 800C7328 000C2228  48 00 00 18 */	b lbl_800C7340
lbl_800C732C:
/* 800C732C 000C222C  3C 60 00 01 */	lis r3, 0x00009C40@ha
/* 800C7330 000C2230  38 00 00 00 */	li r0, 0
/* 800C7334 000C2234  38 63 9C 40 */	addi r3, r3, 0x00009C40@l
/* 800C7338 000C2238  B0 64 04 D0 */	sth r3, 0x4d0(r4)
/* 800C733C 000C223C  B0 04 04 D2 */	sth r0, 0x4d2(r4)
lbl_800C7340:
/* 800C7340 000C2240  38 60 00 00 */	li r3, 0
/* 800C7344 000C2244  B0 64 04 CC */	sth r3, 0x4cc(r4)
/* 800C7348 000C2248  A0 04 04 D0 */	lhz r0, 0x4d0(r4)
/* 800C734C 000C224C  B0 04 04 CE */	sth r0, 0x4ce(r4)
/* 800C7350 000C2250  B0 64 04 D4 */	sth r3, 0x4d4(r4)
/* 800C7354 000C2254  B0 04 04 D6 */	sth r0, 0x4d6(r4)
/* 800C7358 000C2258  38 21 00 20 */	addi r1, r1, 0x20
/* 800C735C 000C225C  4E 80 00 20 */	blr 

.global KPADSetPosParam
KPADSetPosParam:
/* 800C7360 000C2260  1C 03 05 24 */	mulli r0, r3, 0x524
/* 800C7364 000C2264  3C 60 80 41 */	lis r3, inside_kpads@ha
/* 800C7368 000C2268  38 63 E1 58 */	addi r3, r3, inside_kpads@l
/* 800C736C 000C226C  7C 63 02 14 */	add r3, r3, r0
/* 800C7370 000C2270  D0 23 00 84 */	stfs f1, 0x84(r3)
/* 800C7374 000C2274  D0 43 00 88 */	stfs f2, 0x88(r3)
/* 800C7378 000C2278  4E 80 00 20 */	blr 

.global KPADSetHoriParam
KPADSetHoriParam:
/* 800C737C 000C227C  1C 03 05 24 */	mulli r0, r3, 0x524
/* 800C7380 000C2280  3C 60 80 41 */	lis r3, inside_kpads@ha
/* 800C7384 000C2284  38 63 E1 58 */	addi r3, r3, inside_kpads@l
/* 800C7388 000C2288  7C 63 02 14 */	add r3, r3, r0
/* 800C738C 000C228C  D0 23 00 8C */	stfs f1, 0x8c(r3)
/* 800C7390 000C2290  D0 43 00 90 */	stfs f2, 0x90(r3)
/* 800C7394 000C2294  4E 80 00 20 */	blr 

.global KPADSetDistParam
KPADSetDistParam:
/* 800C7398 000C2298  1C 03 05 24 */	mulli r0, r3, 0x524
/* 800C739C 000C229C  3C 60 80 41 */	lis r3, inside_kpads@ha
/* 800C73A0 000C22A0  38 63 E1 58 */	addi r3, r3, inside_kpads@l
/* 800C73A4 000C22A4  7C 63 02 14 */	add r3, r3, r0
/* 800C73A8 000C22A8  D0 23 00 94 */	stfs f1, 0x94(r3)
/* 800C73AC 000C22AC  D0 43 00 98 */	stfs f2, 0x98(r3)
/* 800C73B0 000C22B0  4E 80 00 20 */	blr 

.global KPADSetAccParam
KPADSetAccParam:
/* 800C73B4 000C22B4  1C 03 05 24 */	mulli r0, r3, 0x524
/* 800C73B8 000C22B8  3C 60 80 41 */	lis r3, inside_kpads@ha
/* 800C73BC 000C22BC  38 63 E1 58 */	addi r3, r3, inside_kpads@l
/* 800C73C0 000C22C0  7C 63 02 14 */	add r3, r3, r0
/* 800C73C4 000C22C4  D0 23 00 9C */	stfs f1, 0x9c(r3)
/* 800C73C8 000C22C8  D0 43 00 A0 */	stfs f2, 0xa0(r3)
/* 800C73CC 000C22CC  4E 80 00 20 */	blr 

.global reset_kpad
reset_kpad:
/* 800C73D0 000C22D0  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800C73D4 000C22D4  38 03 00 C4 */	addi r0, r3, 0xc4
/* 800C73D8 000C22D8  C0 C2 95 B8 */	lfs f6, lbl_804C0FD8-_SDA2_BASE_(r2)
/* 800C73DC 000C22DC  38 80 FF FF */	li r4, -1
/* 800C73E0 000C22E0  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800C73E4 000C22E4  C0 A2 95 BC */	lfs f5, lbl_804C0FDC-_SDA2_BASE_(r2)
/* 800C73E8 000C22E8  93 C1 00 18 */	stw r30, 0x18(r1)
/* 800C73EC 000C22EC  3B C0 00 00 */	li r30, 0
/* 800C73F0 000C22F0  C0 82 95 C0 */	lfs f4, lbl_804C0FE0-_SDA2_BASE_(r2)
/* 800C73F4 000C22F4  93 A1 00 14 */	stw r29, 0x14(r1)
/* 800C73F8 000C22F8  3B A3 00 E8 */	addi r29, r3, 0xe8
/* 800C73FC 000C22FC  C0 62 95 C4 */	lfs f3, lbl_804C0FE4-_SDA2_BASE_(r2)
/* 800C7400 000C2300  9B C3 05 1D */	stb r30, 0x51d(r3)
/* 800C7404 000C2304  C0 23 00 A4 */	lfs f1, 0xa4(r3)
/* 800C7408 000C2308  C0 0D 82 0C */	lfs f0, kp_err_outside_frame-_SDA_BASE_(r13)
/* 800C740C 000C230C  A0 A3 04 D0 */	lhz r5, 0x4d0(r3)
/* 800C7410 000C2310  EC 06 00 2A */	fadds f0, f6, f0
/* 800C7414 000C2314  C0 42 95 A8 */	lfs f2, lbl_804C0FC8-_SDA2_BASE_(r2)
/* 800C7418 000C2318  81 63 00 B0 */	lwz r11, 0xb0(r3)
/* 800C741C 000C231C  81 43 00 B4 */	lwz r10, 0xb4(r3)
/* 800C7420 000C2320  D0 03 04 F4 */	stfs f0, 0x4f4(r3)
/* 800C7424 000C2324  C0 0D 82 0C */	lfs f0, kp_err_outside_frame-_SDA_BASE_(r13)
/* 800C7428 000C2328  EC 05 00 28 */	fsubs f0, f5, f0
/* 800C742C 000C232C  D0 03 04 FC */	stfs f0, 0x4fc(r3)
/* 800C7430 000C2330  C0 0D 82 0C */	lfs f0, kp_err_outside_frame-_SDA_BASE_(r13)
/* 800C7434 000C2334  EC 04 00 2A */	fadds f0, f4, f0
/* 800C7438 000C2338  D0 03 04 F8 */	stfs f0, 0x4f8(r3)
/* 800C743C 000C233C  C0 0D 82 0C */	lfs f0, kp_err_outside_frame-_SDA_BASE_(r13)
/* 800C7440 000C2340  EC 03 00 28 */	fsubs f0, f3, f0
/* 800C7444 000C2344  D0 03 05 00 */	stfs f0, 0x500(r3)
/* 800C7448 000C2348  C0 0D 82 14 */	lfs f0, kp_err_dist_speed-_SDA_BASE_(r13)
/* 800C744C 000C234C  EC 05 00 24 */	fdivs f0, f5, f0
/* 800C7450 000C2350  D0 03 05 04 */	stfs f0, 0x504(r3)
/* 800C7454 000C2354  C0 0D 82 14 */	lfs f0, kp_err_dist_speed-_SDA_BASE_(r13)
/* 800C7458 000C2358  EC 06 00 24 */	fdivs f0, f6, f0
/* 800C745C 000C235C  D0 03 05 08 */	stfs f0, 0x508(r3)
/* 800C7460 000C2360  C0 0D 82 00 */	lfs f0, kp_ah_circle_radius-_SDA_BASE_(r13)
/* 800C7464 000C2364  EC 00 00 32 */	fmuls f0, f0, f0
/* 800C7468 000C2368  D0 03 05 0C */	stfs f0, 0x50c(r3)
/* 800C746C 000C236C  C0 0D 9A 44 */	lfs f0, kp_err_dist_min-_SDA_BASE_(r13)
/* 800C7470 000C2370  D0 03 05 14 */	stfs f0, 0x514(r3)
/* 800C7474 000C2374  C0 6D 9A 40 */	lfs f3, kp_dist_vv1-_SDA_BASE_(r13)
/* 800C7478 000C2378  EC 03 08 24 */	fdivs f0, f3, f1
/* 800C747C 000C237C  D0 63 05 10 */	stfs f3, 0x510(r3)
/* 800C7480 000C2380  93 C3 00 08 */	stw r30, 8(r3)
/* 800C7484 000C2384  93 C3 00 04 */	stw r30, 4(r3)
/* 800C7488 000C2388  93 C3 00 00 */	stw r30, 0(r3)
/* 800C748C 000C238C  B3 C3 04 CC */	sth r30, 0x4cc(r3)
/* 800C7490 000C2390  B0 A3 04 CE */	sth r5, 0x4ce(r3)
/* 800C7494 000C2394  9B C3 00 5E */	stb r30, 0x5e(r3)
/* 800C7498 000C2398  9B C3 04 CA */	stb r30, 0x4ca(r3)
/* 800C749C 000C239C  81 0D 9A 38 */	lwz r8, Vec2_0-_SDA_BASE_(r13)
/* 800C74A0 000C23A0  80 ED 9A 3C */	lwz r7, (Vec2_0 + 4)-_SDA_BASE_(r13)
/* 800C74A4 000C23A4  D0 A3 04 B8 */	stfs f5, 0x4b8(r3)
/* 800C74A8 000C23A8  D0 43 04 BC */	stfs f2, 0x4bc(r3)
/* 800C74AC 000C23AC  80 C3 04 B8 */	lwz r6, 0x4b8(r3)
/* 800C74B0 000C23B0  91 03 00 28 */	stw r8, 0x28(r3)
/* 800C74B4 000C23B4  80 A3 04 BC */	lwz r5, 0x4bc(r3)
/* 800C74B8 000C23B8  90 E3 00 2C */	stw r7, 0x2c(r3)
/* 800C74BC 000C23BC  91 03 00 20 */	stw r8, 0x20(r3)
/* 800C74C0 000C23C0  90 E3 00 24 */	stw r7, 0x24(r3)
/* 800C74C4 000C23C4  D0 43 00 30 */	stfs f2, 0x30(r3)
/* 800C74C8 000C23C8  D0 A3 04 B0 */	stfs f5, 0x4b0(r3)
/* 800C74CC 000C23CC  D0 A3 00 34 */	stfs f5, 0x34(r3)
/* 800C74D0 000C23D0  D0 43 04 B4 */	stfs f2, 0x4b4(r3)
/* 800C74D4 000C23D4  D0 43 00 38 */	stfs f2, 0x38(r3)
/* 800C74D8 000C23D8  83 ED 9A 38 */	lwz r31, Vec2_0-_SDA_BASE_(r13)
/* 800C74DC 000C23DC  81 8D 9A 3C */	lwz r12, (Vec2_0 + 4)-_SDA_BASE_(r13)
/* 800C74E0 000C23E0  D0 43 00 14 */	stfs f2, 0x14(r3)
/* 800C74E4 000C23E4  D0 43 00 0C */	stfs f2, 0xc(r3)
/* 800C74E8 000C23E8  80 E3 00 14 */	lwz r7, 0x14(r3)
/* 800C74EC 000C23EC  D0 C3 00 10 */	stfs f6, 0x10(r3)
/* 800C74F0 000C23F0  81 23 00 0C */	lwz r9, 0xc(r3)
/* 800C74F4 000C23F4  81 03 00 10 */	lwz r8, 0x10(r3)
/* 800C74F8 000C23F8  93 E3 00 3C */	stw r31, 0x3c(r3)
/* 800C74FC 000C23FC  91 83 00 40 */	stw r12, 0x40(r3)
/* 800C7500 000C2400  D0 43 00 44 */	stfs f2, 0x44(r3)
/* 800C7504 000C2404  D0 A3 00 54 */	stfs f5, 0x54(r3)
/* 800C7508 000C2408  D0 43 00 58 */	stfs f2, 0x58(r3)
/* 800C750C 000C240C  D0 23 00 48 */	stfs f1, 0x48(r3)
/* 800C7510 000C2410  D0 43 00 50 */	stfs f2, 0x50(r3)
/* 800C7514 000C2414  D0 43 00 4C */	stfs f2, 0x4c(r3)
/* 800C7518 000C2418  D0 23 04 9C */	stfs f1, 0x49c(r3)
/* 800C751C 000C241C  D0 03 04 A0 */	stfs f0, 0x4a0(r3)
/* 800C7520 000C2420  D0 03 04 90 */	stfs f0, 0x490(r3)
/* 800C7524 000C2424  91 63 04 94 */	stw r11, 0x494(r3)
/* 800C7528 000C2428  91 43 04 98 */	stw r10, 0x498(r3)
/* 800C752C 000C242C  D0 A3 00 18 */	stfs f5, 0x18(r3)
/* 800C7530 000C2430  D0 43 00 1C */	stfs f2, 0x1c(r3)
/* 800C7534 000C2434  91 23 04 A4 */	stw r9, 0x4a4(r3)
/* 800C7538 000C2438  91 03 04 A8 */	stw r8, 0x4a8(r3)
/* 800C753C 000C243C  90 E3 04 AC */	stw r7, 0x4ac(r3)
/* 800C7540 000C2440  90 C3 04 C0 */	stw r6, 0x4c0(r3)
/* 800C7544 000C2444  90 A3 04 C4 */	stw r5, 0x4c4(r3)
/* 800C7548 000C2448  A0 AD 82 08 */	lhz r5, kp_ah_circle_ct-_SDA_BASE_(r13)
/* 800C754C 000C244C  B0 A3 04 C8 */	sth r5, 0x4c8(r3)
/* 800C7550 000C2450  B3 C3 01 0C */	sth r30, 0x10c(r3)
lbl_800C7554:
/* 800C7554 000C2454  98 9D 00 08 */	stb r4, 8(r29)
/* 800C7558 000C2458  3B BD FF F4 */	addi r29, r29, -12
/* 800C755C 000C245C  7C 1D 00 40 */	cmplw r29, r0
/* 800C7560 000C2460  40 80 FF F4 */	bge lbl_800C7554
/* 800C7564 000C2464  38 A3 01 00 */	addi r5, r3, 0x100
/* 800C7568 000C2468  38 03 00 F4 */	addi r0, r3, 0xf4
/* 800C756C 000C246C  38 80 FF FF */	li r4, -1
lbl_800C7570:
/* 800C7570 000C2470  98 85 00 08 */	stb r4, 8(r5)
/* 800C7574 000C2474  38 A5 FF F4 */	addi r5, r5, -12
/* 800C7578 000C2478  7C 05 00 40 */	cmplw r5, r0
/* 800C757C 000C247C  40 80 FF F4 */	bge lbl_800C7570
/* 800C7580 000C2480  38 80 00 00 */	li r4, 0
/* 800C7584 000C2484  38 00 00 01 */	li r0, 1
/* 800C7588 000C2488  98 83 01 0F */	stb r4, 0x10f(r3)
/* 800C758C 000C248C  98 03 05 1E */	stb r0, 0x51e(r3)
/* 800C7590 000C2490  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800C7594 000C2494  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 800C7598 000C2498  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 800C759C 000C249C  38 21 00 20 */	addi r1, r1, 0x20
/* 800C75A0 000C24A0  4E 80 00 20 */	blr 

.global KPADSetSensorHeight
KPADSetSensorHeight:
/* 800C75A4 000C24A4  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 800C75A8 000C24A8  7C 08 02 A6 */	mflr r0
/* 800C75AC 000C24AC  90 01 00 34 */	stw r0, 0x34(r1)
/* 800C75B0 000C24B0  DB E1 00 20 */	stfd f31, 0x20(r1)
/* 800C75B4 000C24B4  F3 E1 00 28 */	psq_st f31, 40(r1), 0, qr0
/* 800C75B8 000C24B8  DB C1 00 10 */	stfd f30, 0x10(r1)
/* 800C75BC 000C24BC  F3 C1 00 18 */	psq_st f30, 24(r1), 0, qr0
/* 800C75C0 000C24C0  1C 03 05 24 */	mulli r0, r3, 0x524
/* 800C75C4 000C24C4  C3 C2 95 BC */	lfs f30, lbl_804C0FDC-_SDA2_BASE_(r2)
/* 800C75C8 000C24C8  3C 60 80 41 */	lis r3, inside_kpads@ha
/* 800C75CC 000C24CC  C3 E2 95 C4 */	lfs f31, lbl_804C0FE4-_SDA2_BASE_(r2)
/* 800C75D0 000C24D0  FC 60 08 50 */	fneg f3, f1
/* 800C75D4 000C24D4  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800C75D8 000C24D8  38 63 E1 58 */	addi r3, r3, inside_kpads@l
/* 800C75DC 000C24DC  EC 5E 07 B2 */	fmuls f2, f30, f30
/* 800C75E0 000C24E0  EC 1F 07 F2 */	fmuls f0, f31, f31
/* 800C75E4 000C24E4  C0 82 95 A8 */	lfs f4, lbl_804C0FC8-_SDA2_BASE_(r2)
/* 800C75E8 000C24E8  7F E3 02 14 */	add r31, r3, r0
/* 800C75EC 000C24EC  D0 9F 00 B8 */	stfs f4, 0xb8(r31)
/* 800C75F0 000C24F0  EC 22 00 2A */	fadds f1, f2, f0
/* 800C75F4 000C24F4  D0 7F 00 BC */	stfs f3, 0xbc(r31)
/* 800C75F8 000C24F8  4B FF 9A D9 */	bl sqrt
/* 800C75FC 000C24FC  C0 5F 00 B8 */	lfs f2, 0xb8(r31)
/* 800C7600 000C2500  FC 60 08 18 */	frsp f3, f1
/* 800C7604 000C2504  C0 02 95 A8 */	lfs f0, lbl_804C0FC8-_SDA2_BASE_(r2)
/* 800C7608 000C2508  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 800C760C 000C250C  40 80 00 0C */	bge lbl_800C7618
/* 800C7610 000C2510  EF DE 10 2A */	fadds f30, f30, f2
/* 800C7614 000C2514  48 00 00 08 */	b lbl_800C761C
lbl_800C7618:
/* 800C7618 000C2518  EF DE 10 28 */	fsubs f30, f30, f2
lbl_800C761C:
/* 800C761C 000C251C  C0 3F 00 BC */	lfs f1, 0xbc(r31)
/* 800C7620 000C2520  C0 02 95 A8 */	lfs f0, lbl_804C0FC8-_SDA2_BASE_(r2)
/* 800C7624 000C2524  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800C7628 000C2528  40 80 00 0C */	bge lbl_800C7634
/* 800C762C 000C252C  EF FF 08 2A */	fadds f31, f31, f1
/* 800C7630 000C2530  48 00 00 08 */	b lbl_800C7638
lbl_800C7634:
/* 800C7634 000C2534  EF FF 08 28 */	fsubs f31, f31, f1
lbl_800C7638:
/* 800C7638 000C2538  FC 1E F8 40 */	fcmpo cr0, f30, f31
/* 800C763C 000C253C  40 80 00 08 */	bge lbl_800C7644
/* 800C7640 000C2540  48 00 00 08 */	b lbl_800C7648
lbl_800C7644:
/* 800C7644 000C2544  FF C0 F8 90 */	fmr f30, f31
lbl_800C7648:
/* 800C7648 000C2548  EC 03 F0 24 */	fdivs f0, f3, f30
/* 800C764C 000C254C  D0 1F 00 C0 */	stfs f0, 0xc0(r31)
/* 800C7650 000C2550  E3 E1 00 28 */	psq_l f31, 40(r1), 0, qr0
/* 800C7654 000C2554  CB E1 00 20 */	lfd f31, 0x20(r1)
/* 800C7658 000C2558  E3 C1 00 18 */	psq_l f30, 24(r1), 0, qr0
/* 800C765C 000C255C  CB C1 00 10 */	lfd f30, 0x10(r1)
/* 800C7660 000C2560  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 800C7664 000C2564  80 01 00 34 */	lwz r0, 0x34(r1)
/* 800C7668 000C2568  7C 08 03 A6 */	mtlr r0
/* 800C766C 000C256C  38 21 00 30 */	addi r1, r1, 0x30
/* 800C7670 000C2570  4E 80 00 20 */	blr 

.global calc_button_repeat
calc_button_repeat:
/* 800C7674 000C2574  80 03 00 04 */	lwz r0, 4(r3)
/* 800C7678 000C2578  2C 00 00 00 */	cmpwi r0, 0
/* 800C767C 000C257C  40 82 00 10 */	bne lbl_800C768C
/* 800C7680 000C2580  80 03 00 08 */	lwz r0, 8(r3)
/* 800C7684 000C2584  2C 00 00 00 */	cmpwi r0, 0
/* 800C7688 000C2588  41 82 00 3C */	beq lbl_800C76C4
lbl_800C768C:
/* 800C768C 000C258C  80 03 00 04 */	lwz r0, 4(r3)
/* 800C7690 000C2590  38 E0 00 00 */	li r7, 0
/* 800C7694 000C2594  A0 C3 04 D0 */	lhz r6, 0x4d0(r3)
/* 800C7698 000C2598  2C 00 00 00 */	cmpwi r0, 0
/* 800C769C 000C259C  B0 E3 04 CC */	sth r7, 0x4cc(r3)
/* 800C76A0 000C25A0  B0 C3 04 CE */	sth r6, 0x4ce(r3)
/* 800C76A4 000C25A4  41 82 00 94 */	beq lbl_800C7738
/* 800C76A8 000C25A8  A0 03 04 D2 */	lhz r0, 0x4d2(r3)
/* 800C76AC 000C25AC  2C 00 00 00 */	cmpwi r0, 0
/* 800C76B0 000C25B0  41 82 00 88 */	beq lbl_800C7738
/* 800C76B4 000C25B4  80 03 00 00 */	lwz r0, 0(r3)
/* 800C76B8 000C25B8  64 00 80 00 */	oris r0, r0, 0x8000
/* 800C76BC 000C25BC  90 03 00 00 */	stw r0, 0(r3)
/* 800C76C0 000C25C0  48 00 00 78 */	b lbl_800C7738
lbl_800C76C4:
/* 800C76C4 000C25C4  80 03 00 00 */	lwz r0, 0(r3)
/* 800C76C8 000C25C8  2C 00 00 00 */	cmpwi r0, 0
/* 800C76CC 000C25CC  41 82 00 6C */	beq lbl_800C7738
/* 800C76D0 000C25D0  A0 03 04 CC */	lhz r0, 0x4cc(r3)
/* 800C76D4 000C25D4  7C 00 2A 14 */	add r0, r0, r5
/* 800C76D8 000C25D8  54 06 04 3E */	clrlwi r6, r0, 0x10
/* 800C76DC 000C25DC  B0 03 04 CC */	sth r0, 0x4cc(r3)
/* 800C76E0 000C25E0  28 06 9C 40 */	cmplwi r6, 0x9c40
/* 800C76E4 000C25E4  41 80 00 10 */	blt lbl_800C76F4
/* 800C76E8 000C25E8  3C C6 FF FF */	addis r6, r6, 0xffff
/* 800C76EC 000C25EC  38 06 63 C0 */	addi r0, r6, 0x63c0
/* 800C76F0 000C25F0  B0 03 04 CC */	sth r0, 0x4cc(r3)
lbl_800C76F4:
/* 800C76F4 000C25F4  A1 03 04 CC */	lhz r8, 0x4cc(r3)
/* 800C76F8 000C25F8  A0 E3 04 CE */	lhz r7, 0x4ce(r3)
/* 800C76FC 000C25FC  7C 08 38 40 */	cmplw r8, r7
/* 800C7700 000C2600  41 80 00 38 */	blt lbl_800C7738
/* 800C7704 000C2604  80 C3 00 00 */	lwz r6, 0(r3)
/* 800C7708 000C2608  28 08 4E 20 */	cmplwi r8, 0x4e20
/* 800C770C 000C260C  A0 03 04 D2 */	lhz r0, 0x4d2(r3)
/* 800C7710 000C2610  64 C6 80 00 */	oris r6, r6, 0x8000
/* 800C7714 000C2614  7C 07 02 14 */	add r0, r7, r0
/* 800C7718 000C2618  90 C3 00 00 */	stw r6, 0(r3)
/* 800C771C 000C261C  B0 03 04 CE */	sth r0, 0x4ce(r3)
/* 800C7720 000C2620  41 80 00 18 */	blt lbl_800C7738
/* 800C7724 000C2624  54 06 04 3E */	clrlwi r6, r0, 0x10
/* 800C7728 000C2628  38 E8 B1 E0 */	addi r7, r8, -20000
/* 800C772C 000C262C  38 06 B1 E0 */	addi r0, r6, -20000
/* 800C7730 000C2630  B0 E3 04 CC */	sth r7, 0x4cc(r3)
/* 800C7734 000C2634  B0 03 04 CE */	sth r0, 0x4ce(r3)
lbl_800C7738:
/* 800C7738 000C2638  28 04 00 02 */	cmplwi r4, 2
/* 800C773C 000C263C  4C 82 00 20 */	bnelr 
/* 800C7740 000C2640  80 03 00 64 */	lwz r0, 0x64(r3)
/* 800C7744 000C2644  2C 00 00 00 */	cmpwi r0, 0
/* 800C7748 000C2648  40 82 00 10 */	bne lbl_800C7758
/* 800C774C 000C264C  80 03 00 68 */	lwz r0, 0x68(r3)
/* 800C7750 000C2650  2C 00 00 00 */	cmpwi r0, 0
/* 800C7754 000C2654  41 82 00 3C */	beq lbl_800C7790
lbl_800C7758:
/* 800C7758 000C2658  80 03 00 64 */	lwz r0, 0x64(r3)
/* 800C775C 000C265C  38 A0 00 00 */	li r5, 0
/* 800C7760 000C2660  A0 83 04 D0 */	lhz r4, 0x4d0(r3)
/* 800C7764 000C2664  2C 00 00 00 */	cmpwi r0, 0
/* 800C7768 000C2668  B0 A3 04 D4 */	sth r5, 0x4d4(r3)
/* 800C776C 000C266C  B0 83 04 D6 */	sth r4, 0x4d6(r3)
/* 800C7770 000C2670  4D 82 00 20 */	beqlr 
/* 800C7774 000C2674  A0 03 04 D2 */	lhz r0, 0x4d2(r3)
/* 800C7778 000C2678  2C 00 00 00 */	cmpwi r0, 0
/* 800C777C 000C267C  4D 82 00 20 */	beqlr 
/* 800C7780 000C2680  80 03 00 60 */	lwz r0, 0x60(r3)
/* 800C7784 000C2684  64 00 80 00 */	oris r0, r0, 0x8000
/* 800C7788 000C2688  90 03 00 60 */	stw r0, 0x60(r3)
/* 800C778C 000C268C  4E 80 00 20 */	blr 
lbl_800C7790:
/* 800C7790 000C2690  80 03 00 60 */	lwz r0, 0x60(r3)
/* 800C7794 000C2694  2C 00 00 00 */	cmpwi r0, 0
/* 800C7798 000C2698  4D 82 00 20 */	beqlr 
/* 800C779C 000C269C  A0 03 04 D4 */	lhz r0, 0x4d4(r3)
/* 800C77A0 000C26A0  7C 00 2A 14 */	add r0, r0, r5
/* 800C77A4 000C26A4  54 04 04 3E */	clrlwi r4, r0, 0x10
/* 800C77A8 000C26A8  B0 03 04 D4 */	sth r0, 0x4d4(r3)
/* 800C77AC 000C26AC  28 04 9C 40 */	cmplwi r4, 0x9c40
/* 800C77B0 000C26B0  41 80 00 10 */	blt lbl_800C77C0
/* 800C77B4 000C26B4  3C 84 FF FF */	addis r4, r4, 0xffff
/* 800C77B8 000C26B8  38 04 63 C0 */	addi r0, r4, 0x63c0
/* 800C77BC 000C26BC  B0 03 04 D4 */	sth r0, 0x4d4(r3)
lbl_800C77C0:
/* 800C77C0 000C26C0  A0 C3 04 D4 */	lhz r6, 0x4d4(r3)
/* 800C77C4 000C26C4  A0 A3 04 D6 */	lhz r5, 0x4d6(r3)
/* 800C77C8 000C26C8  7C 06 28 40 */	cmplw r6, r5
/* 800C77CC 000C26CC  4D 80 00 20 */	bltlr 
/* 800C77D0 000C26D0  80 83 00 60 */	lwz r4, 0x60(r3)
/* 800C77D4 000C26D4  28 06 4E 20 */	cmplwi r6, 0x4e20
/* 800C77D8 000C26D8  A0 03 04 D2 */	lhz r0, 0x4d2(r3)
/* 800C77DC 000C26DC  64 84 80 00 */	oris r4, r4, 0x8000
/* 800C77E0 000C26E0  7C 05 02 14 */	add r0, r5, r0
/* 800C77E4 000C26E4  90 83 00 60 */	stw r4, 0x60(r3)
/* 800C77E8 000C26E8  B0 03 04 D6 */	sth r0, 0x4d6(r3)
/* 800C77EC 000C26EC  4D 80 00 20 */	bltlr 
/* 800C77F0 000C26F0  54 04 04 3E */	clrlwi r4, r0, 0x10
/* 800C77F4 000C26F4  38 A6 B1 E0 */	addi r5, r6, -20000
/* 800C77F8 000C26F8  38 04 B1 E0 */	addi r0, r4, -20000
/* 800C77FC 000C26FC  B0 A3 04 D4 */	sth r5, 0x4d4(r3)
/* 800C7800 000C2700  B0 03 04 D6 */	sth r0, 0x4d6(r3)
/* 800C7804 000C2704  4E 80 00 20 */	blr 

.global calc_acc_horizon
calc_acc_horizon:
/* 800C7808 000C2708  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 800C780C 000C270C  7C 08 02 A6 */	mflr r0
/* 800C7810 000C2710  90 01 00 34 */	stw r0, 0x34(r1)
/* 800C7814 000C2714  DB E1 00 20 */	stfd f31, 0x20(r1)
/* 800C7818 000C2718  F3 E1 00 28 */	psq_st f31, 40(r1), 0, qr0
/* 800C781C 000C271C  DB C1 00 10 */	stfd f30, 0x10(r1)
/* 800C7820 000C2720  F3 C1 00 18 */	psq_st f30, 24(r1), 0, qr0
/* 800C7824 000C2724  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800C7828 000C2728  7C 7F 1B 78 */	mr r31, r3
/* 800C782C 000C272C  C0 23 04 A4 */	lfs f1, 0x4a4(r3)
/* 800C7830 000C2730  C0 03 04 A8 */	lfs f0, 0x4a8(r3)
/* 800C7834 000C2734  EC 21 00 72 */	fmuls f1, f1, f1
/* 800C7838 000C2738  EC 00 00 32 */	fmuls f0, f0, f0
/* 800C783C 000C273C  EC 21 00 2A */	fadds f1, f1, f0
/* 800C7840 000C2740  4B FF 98 91 */	bl sqrt
/* 800C7844 000C2744  FD 00 08 18 */	frsp f8, f1
/* 800C7848 000C2748  C0 02 95 A8 */	lfs f0, lbl_804C0FC8-_SDA2_BASE_(r2)
/* 800C784C 000C274C  FC 00 40 00 */	fcmpu cr0, f0, f8
/* 800C7850 000C2750  41 82 01 28 */	beq lbl_800C7978
/* 800C7854 000C2754  C0 42 95 D0 */	lfs f2, lbl_804C0FF0-_SDA2_BASE_(r2)
/* 800C7858 000C2758  FC 08 10 40 */	fcmpo cr0, f8, f2
/* 800C785C 000C275C  4C 41 13 82 */	cror 2, 1, 2
/* 800C7860 000C2760  40 82 00 08 */	bne lbl_800C7868
/* 800C7864 000C2764  48 00 01 14 */	b lbl_800C7978
lbl_800C7868:
/* 800C7868 000C2768  C0 1F 04 A4 */	lfs f0, 0x4a4(r31)
/* 800C786C 000C276C  C0 3F 04 A8 */	lfs f1, 0x4a8(r31)
/* 800C7870 000C2770  ED 20 40 24 */	fdivs f9, f0, f8
/* 800C7874 000C2774  C0 02 95 BC */	lfs f0, lbl_804C0FDC-_SDA2_BASE_(r2)
/* 800C7878 000C2778  ED 41 40 24 */	fdivs f10, f1, f8
/* 800C787C 000C277C  FC 08 00 40 */	fcmpo cr0, f8, f0
/* 800C7880 000C2780  40 81 00 08 */	ble lbl_800C7888
/* 800C7884 000C2784  ED 02 40 28 */	fsubs f8, f2, f8
lbl_800C7888:
/* 800C7888 000C2788  C0 1F 00 AC */	lfs f0, 0xac(r31)
/* 800C788C 000C278C  C0 DF 00 A8 */	lfs f6, 0xa8(r31)
/* 800C7890 000C2790  EC 80 02 B2 */	fmuls f4, f0, f10
/* 800C7894 000C2794  C0 ED 81 FC */	lfs f7, kp_acc_horizon_pw-_SDA_BASE_(r13)
/* 800C7898 000C2798  EC A6 02 72 */	fmuls f5, f6, f9
/* 800C789C 000C279C  C0 7F 04 B8 */	lfs f3, 0x4b8(r31)
/* 800C78A0 000C27A0  EC 40 02 72 */	fmuls f2, f0, f9
/* 800C78A4 000C27A4  C0 3F 04 BC */	lfs f1, 0x4bc(r31)
/* 800C78A8 000C27A8  EC 06 02 B2 */	fmuls f0, f6, f10
/* 800C78AC 000C27AC  EC C8 01 F2 */	fmuls f6, f8, f7
/* 800C78B0 000C27B0  EC 85 20 2A */	fadds f4, f5, f4
/* 800C78B4 000C27B4  EC 02 00 28 */	fsubs f0, f2, f0
/* 800C78B8 000C27B8  ED 08 01 B2 */	fmuls f8, f8, f6
/* 800C78BC 000C27BC  EC 44 18 28 */	fsubs f2, f4, f3
/* 800C78C0 000C27C0  EC 00 08 28 */	fsubs f0, f0, f1
/* 800C78C4 000C27C4  EC 48 00 B2 */	fmuls f2, f8, f2
/* 800C78C8 000C27C8  EC 08 00 32 */	fmuls f0, f8, f0
/* 800C78CC 000C27CC  EF E3 10 2A */	fadds f31, f3, f2
/* 800C78D0 000C27D0  EF C1 00 2A */	fadds f30, f1, f0
/* 800C78D4 000C27D4  EC 3F 07 F2 */	fmuls f1, f31, f31
/* 800C78D8 000C27D8  EC 1E 07 B2 */	fmuls f0, f30, f30
/* 800C78DC 000C27DC  EC 21 00 2A */	fadds f1, f1, f0
/* 800C78E0 000C27E0  4B FF 97 F1 */	bl sqrt
/* 800C78E4 000C27E4  FC 20 08 18 */	frsp f1, f1
/* 800C78E8 000C27E8  C0 02 95 A8 */	lfs f0, lbl_804C0FC8-_SDA2_BASE_(r2)
/* 800C78EC 000C27EC  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 800C78F0 000C27F0  41 82 00 88 */	beq lbl_800C7978
/* 800C78F4 000C27F4  EC FF 08 24 */	fdivs f7, f31, f1
/* 800C78F8 000C27F8  C0 BF 04 C0 */	lfs f5, 0x4c0(r31)
/* 800C78FC 000C27FC  C0 9F 04 C4 */	lfs f4, 0x4c4(r31)
/* 800C7900 000C2800  C0 1F 05 0C */	lfs f0, 0x50c(r31)
/* 800C7904 000C2804  EC DE 08 24 */	fdivs f6, f30, f1
/* 800C7908 000C2808  D0 FF 04 B8 */	stfs f7, 0x4b8(r31)
/* 800C790C 000C280C  D0 DF 04 BC */	stfs f6, 0x4bc(r31)
/* 800C7910 000C2810  EC 47 28 28 */	fsubs f2, f7, f5
/* 800C7914 000C2814  EC 66 20 28 */	fsubs f3, f6, f4
/* 800C7918 000C2818  C0 2D 82 04 */	lfs f1, kp_ah_circle_pw-_SDA_BASE_(r13)
/* 800C791C 000C281C  EC 21 00 B2 */	fmuls f1, f1, f2
/* 800C7920 000C2820  EC 25 08 2A */	fadds f1, f5, f1
/* 800C7924 000C2824  EC 47 08 28 */	fsubs f2, f7, f1
/* 800C7928 000C2828  D0 3F 04 C0 */	stfs f1, 0x4c0(r31)
/* 800C792C 000C282C  C0 2D 82 04 */	lfs f1, kp_ah_circle_pw-_SDA_BASE_(r13)
/* 800C7930 000C2830  EC 42 00 B2 */	fmuls f2, f2, f2
/* 800C7934 000C2834  EC 21 00 F2 */	fmuls f1, f1, f3
/* 800C7938 000C2838  EC 24 08 2A */	fadds f1, f4, f1
/* 800C793C 000C283C  EC 66 08 28 */	fsubs f3, f6, f1
/* 800C7940 000C2840  D0 3F 04 C4 */	stfs f1, 0x4c4(r31)
/* 800C7944 000C2844  EC 23 00 F2 */	fmuls f1, f3, f3
/* 800C7948 000C2848  EC 22 08 2A */	fadds f1, f2, f1
/* 800C794C 000C284C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800C7950 000C2850  4C 40 13 82 */	cror 2, 0, 2
/* 800C7954 000C2854  40 82 00 1C */	bne lbl_800C7970
/* 800C7958 000C2858  A0 7F 04 C8 */	lhz r3, 0x4c8(r31)
/* 800C795C 000C285C  2C 03 00 00 */	cmpwi r3, 0
/* 800C7960 000C2860  41 82 00 18 */	beq lbl_800C7978
/* 800C7964 000C2864  38 03 FF FF */	addi r0, r3, -1
/* 800C7968 000C2868  B0 1F 04 C8 */	sth r0, 0x4c8(r31)
/* 800C796C 000C286C  48 00 00 0C */	b lbl_800C7978
lbl_800C7970:
/* 800C7970 000C2870  A0 0D 82 08 */	lhz r0, kp_ah_circle_ct-_SDA_BASE_(r13)
/* 800C7974 000C2874  B0 1F 04 C8 */	sth r0, 0x4c8(r31)
lbl_800C7978:
/* 800C7978 000C2878  E3 E1 00 28 */	psq_l f31, 40(r1), 0, qr0
/* 800C797C 000C287C  CB E1 00 20 */	lfd f31, 0x20(r1)
/* 800C7980 000C2880  E3 C1 00 18 */	psq_l f30, 24(r1), 0, qr0
/* 800C7984 000C2884  CB C1 00 10 */	lfd f30, 0x10(r1)
/* 800C7988 000C2888  80 01 00 34 */	lwz r0, 0x34(r1)
/* 800C798C 000C288C  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 800C7990 000C2890  7C 08 03 A6 */	mtlr r0
/* 800C7994 000C2894  38 21 00 30 */	addi r1, r1, 0x30
/* 800C7998 000C2898  4E 80 00 20 */	blr 

.global calc_acc_vertical
calc_acc_vertical:
/* 800C799C 000C289C  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 800C79A0 000C28A0  7C 08 02 A6 */	mflr r0
/* 800C79A4 000C28A4  90 01 00 44 */	stw r0, 0x44(r1)
/* 800C79A8 000C28A8  DB E1 00 30 */	stfd f31, 0x30(r1)
/* 800C79AC 000C28AC  F3 E1 00 38 */	psq_st f31, 56(r1), 0, qr0
/* 800C79B0 000C28B0  DB C1 00 20 */	stfd f30, 0x20(r1)
/* 800C79B4 000C28B4  F3 C1 00 28 */	psq_st f30, 40(r1), 0, qr0
/* 800C79B8 000C28B8  DB A1 00 10 */	stfd f29, 0x10(r1)
/* 800C79BC 000C28BC  F3 A1 00 18 */	psq_st f29, 24(r1), 0, qr0
/* 800C79C0 000C28C0  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800C79C4 000C28C4  7C 7F 1B 78 */	mr r31, r3
/* 800C79C8 000C28C8  C0 23 04 A4 */	lfs f1, 0x4a4(r3)
/* 800C79CC 000C28CC  C0 03 04 A8 */	lfs f0, 0x4a8(r3)
/* 800C79D0 000C28D0  EC 21 00 72 */	fmuls f1, f1, f1
/* 800C79D4 000C28D4  EC 00 00 32 */	fmuls f0, f0, f0
/* 800C79D8 000C28D8  EF C1 00 2A */	fadds f30, f1, f0
/* 800C79DC 000C28DC  FC 20 F0 90 */	fmr f1, f30
/* 800C79E0 000C28E0  4B FF 96 F1 */	bl sqrt
/* 800C79E4 000C28E4  C0 1F 04 AC */	lfs f0, 0x4ac(r31)
/* 800C79E8 000C28E8  FF E0 08 18 */	frsp f31, f1
/* 800C79EC 000C28EC  FF A0 00 50 */	fneg f29, f0
/* 800C79F0 000C28F0  EC 1D 07 72 */	fmuls f0, f29, f29
/* 800C79F4 000C28F4  EC 3E 00 2A */	fadds f1, f30, f0
/* 800C79F8 000C28F8  4B FF 96 D9 */	bl sqrt
/* 800C79FC 000C28FC  FC A0 08 18 */	frsp f5, f1
/* 800C7A00 000C2900  C0 02 95 A8 */	lfs f0, lbl_804C0FC8-_SDA2_BASE_(r2)
/* 800C7A04 000C2904  FC 00 28 00 */	fcmpu cr0, f0, f5
/* 800C7A08 000C2908  41 82 00 8C */	beq lbl_800C7A94
/* 800C7A0C 000C290C  C0 22 95 D0 */	lfs f1, lbl_804C0FF0-_SDA2_BASE_(r2)
/* 800C7A10 000C2910  FC 05 08 40 */	fcmpo cr0, f5, f1
/* 800C7A14 000C2914  4C 41 13 82 */	cror 2, 1, 2
/* 800C7A18 000C2918  40 82 00 08 */	bne lbl_800C7A20
/* 800C7A1C 000C291C  48 00 00 78 */	b lbl_800C7A94
lbl_800C7A20:
/* 800C7A20 000C2920  EC 5F 28 24 */	fdivs f2, f31, f5
/* 800C7A24 000C2924  C0 02 95 BC */	lfs f0, lbl_804C0FDC-_SDA2_BASE_(r2)
/* 800C7A28 000C2928  EF BD 28 24 */	fdivs f29, f29, f5
/* 800C7A2C 000C292C  FC 05 00 40 */	fcmpo cr0, f5, f0
/* 800C7A30 000C2930  40 81 00 08 */	ble lbl_800C7A38
/* 800C7A34 000C2934  EC A1 28 28 */	fsubs f5, f1, f5
lbl_800C7A38:
/* 800C7A38 000C2938  C0 0D 81 FC */	lfs f0, kp_acc_horizon_pw-_SDA_BASE_(r13)
/* 800C7A3C 000C293C  C0 7F 00 54 */	lfs f3, 0x54(r31)
/* 800C7A40 000C2940  EC 85 00 32 */	fmuls f4, f5, f0
/* 800C7A44 000C2944  C0 3F 00 58 */	lfs f1, 0x58(r31)
/* 800C7A48 000C2948  EC 42 18 28 */	fsubs f2, f2, f3
/* 800C7A4C 000C294C  EC 1D 08 28 */	fsubs f0, f29, f1
/* 800C7A50 000C2950  EC A5 01 32 */	fmuls f5, f5, f4
/* 800C7A54 000C2954  EC 45 00 B2 */	fmuls f2, f5, f2
/* 800C7A58 000C2958  EC 05 00 32 */	fmuls f0, f5, f0
/* 800C7A5C 000C295C  EF E3 10 2A */	fadds f31, f3, f2
/* 800C7A60 000C2960  EF C1 00 2A */	fadds f30, f1, f0
/* 800C7A64 000C2964  EC 3F 07 F2 */	fmuls f1, f31, f31
/* 800C7A68 000C2968  EC 1E 07 B2 */	fmuls f0, f30, f30
/* 800C7A6C 000C296C  EC 21 00 2A */	fadds f1, f1, f0
/* 800C7A70 000C2970  4B FF 96 61 */	bl sqrt
/* 800C7A74 000C2974  FC 40 08 18 */	frsp f2, f1
/* 800C7A78 000C2978  C0 02 95 A8 */	lfs f0, lbl_804C0FC8-_SDA2_BASE_(r2)
/* 800C7A7C 000C297C  FC 00 10 00 */	fcmpu cr0, f0, f2
/* 800C7A80 000C2980  41 82 00 14 */	beq lbl_800C7A94
/* 800C7A84 000C2984  EC 3F 10 24 */	fdivs f1, f31, f2
/* 800C7A88 000C2988  EC 1E 10 24 */	fdivs f0, f30, f2
/* 800C7A8C 000C298C  D0 3F 00 54 */	stfs f1, 0x54(r31)
/* 800C7A90 000C2990  D0 1F 00 58 */	stfs f0, 0x58(r31)
lbl_800C7A94:
/* 800C7A94 000C2994  E3 E1 00 38 */	psq_l f31, 56(r1), 0, qr0
/* 800C7A98 000C2998  CB E1 00 30 */	lfd f31, 0x30(r1)
/* 800C7A9C 000C299C  E3 C1 00 28 */	psq_l f30, 40(r1), 0, qr0
/* 800C7AA0 000C29A0  CB C1 00 20 */	lfd f30, 0x20(r1)
/* 800C7AA4 000C29A4  E3 A1 00 18 */	psq_l f29, 24(r1), 0, qr0
/* 800C7AA8 000C29A8  CB A1 00 10 */	lfd f29, 0x10(r1)
/* 800C7AAC 000C29AC  80 01 00 44 */	lwz r0, 0x44(r1)
/* 800C7AB0 000C29B0  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 800C7AB4 000C29B4  7C 08 03 A6 */	mtlr r0
/* 800C7AB8 000C29B8  38 21 00 40 */	addi r1, r1, 0x40
/* 800C7ABC 000C29BC  4E 80 00 20 */	blr 

.global read_kpad_acc
read_kpad_acc:
/* 800C7AC0 000C29C0  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 800C7AC4 000C29C4  7C 08 02 A6 */	mflr r0
/* 800C7AC8 000C29C8  3C A0 43 30 */	lis r5, 0x4330
/* 800C7ACC 000C29CC  90 01 00 44 */	stw r0, 0x44(r1)
/* 800C7AD0 000C29D0  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 800C7AD4 000C29D4  7C 9F 23 78 */	mr r31, r4
/* 800C7AD8 000C29D8  93 C1 00 38 */	stw r30, 0x38(r1)
/* 800C7ADC 000C29DC  7C 7E 1B 78 */	mr r30, r3
/* 800C7AE0 000C29E0  88 04 00 36 */	lbz r0, 0x36(r4)
/* 800C7AE4 000C29E4  90 A1 00 20 */	stw r5, 0x20(r1)
/* 800C7AE8 000C29E8  2C 00 00 06 */	cmpwi r0, 6
/* 800C7AEC 000C29EC  90 A1 00 28 */	stw r5, 0x28(r1)
/* 800C7AF0 000C29F0  41 82 05 C0 */	beq lbl_800C80B0
/* 800C7AF4 000C29F4  40 80 00 1C */	bge lbl_800C7B10
/* 800C7AF8 000C29F8  2C 00 00 03 */	cmpwi r0, 3
/* 800C7AFC 000C29FC  41 82 05 B4 */	beq lbl_800C80B0
/* 800C7B00 000C2A00  40 80 00 20 */	bge lbl_800C7B20
/* 800C7B04 000C2A04  2C 00 00 01 */	cmpwi r0, 1
/* 800C7B08 000C2A08  40 80 00 18 */	bge lbl_800C7B20
/* 800C7B0C 000C2A0C  48 00 05 A4 */	b lbl_800C80B0
lbl_800C7B10:
/* 800C7B10 000C2A10  2C 00 00 09 */	cmpwi r0, 9
/* 800C7B14 000C2A14  40 80 05 9C */	bge lbl_800C80B0
/* 800C7B18 000C2A18  48 00 00 08 */	b lbl_800C7B20
/* 800C7B1C 000C2A1C  48 00 05 94 */	b lbl_800C80B0
lbl_800C7B20:
/* 800C7B20 000C2A20  A8 04 00 02 */	lha r0, 2(r4)
/* 800C7B24 000C2A24  C8 62 95 D8 */	lfd f3, lbl_804C0FF8-_SDA2_BASE_(r2)
/* 800C7B28 000C2A28  7C 00 00 D0 */	neg r0, r0
/* 800C7B2C 000C2A2C  C0 23 04 DC */	lfs f1, 0x4dc(r3)
/* 800C7B30 000C2A30  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 800C7B34 000C2A34  C0 02 95 A8 */	lfs f0, lbl_804C0FC8-_SDA2_BASE_(r2)
/* 800C7B38 000C2A38  90 01 00 24 */	stw r0, 0x24(r1)
/* 800C7B3C 000C2A3C  C0 8D 82 44 */	lfs f4, kp_rm_acc_max-_SDA_BASE_(r13)
/* 800C7B40 000C2A40  C8 41 00 20 */	lfd f2, 0x20(r1)
/* 800C7B44 000C2A44  EC 42 18 28 */	fsubs f2, f2, f3
/* 800C7B48 000C2A48  EC 22 00 72 */	fmuls f1, f2, f1
/* 800C7B4C 000C2A4C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800C7B50 000C2A50  40 80 00 14 */	bge lbl_800C7B64
/* 800C7B54 000C2A54  FC 80 20 50 */	fneg f4, f4
/* 800C7B58 000C2A58  FC 01 20 40 */	fcmpo cr0, f1, f4
/* 800C7B5C 000C2A5C  40 80 00 14 */	bge lbl_800C7B70
/* 800C7B60 000C2A60  48 00 00 14 */	b lbl_800C7B74
lbl_800C7B64:
/* 800C7B64 000C2A64  FC 01 20 40 */	fcmpo cr0, f1, f4
/* 800C7B68 000C2A68  40 81 00 08 */	ble lbl_800C7B70
/* 800C7B6C 000C2A6C  48 00 00 08 */	b lbl_800C7B74
lbl_800C7B70:
/* 800C7B70 000C2A70  FC 80 08 90 */	fmr f4, f1
lbl_800C7B74:
/* 800C7B74 000C2A74  D0 83 04 A4 */	stfs f4, 0x4a4(r3)
/* 800C7B78 000C2A78  C8 62 95 D8 */	lfd f3, lbl_804C0FF8-_SDA2_BASE_(r2)
/* 800C7B7C 000C2A7C  A8 04 00 06 */	lha r0, 6(r4)
/* 800C7B80 000C2A80  C0 23 04 E4 */	lfs f1, 0x4e4(r3)
/* 800C7B84 000C2A84  7C 00 00 D0 */	neg r0, r0
/* 800C7B88 000C2A88  C0 02 95 A8 */	lfs f0, lbl_804C0FC8-_SDA2_BASE_(r2)
/* 800C7B8C 000C2A8C  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 800C7B90 000C2A90  C0 8D 82 44 */	lfs f4, kp_rm_acc_max-_SDA_BASE_(r13)
/* 800C7B94 000C2A94  90 01 00 2C */	stw r0, 0x2c(r1)
/* 800C7B98 000C2A98  C8 41 00 28 */	lfd f2, 0x28(r1)
/* 800C7B9C 000C2A9C  EC 42 18 28 */	fsubs f2, f2, f3
/* 800C7BA0 000C2AA0  EC 22 00 72 */	fmuls f1, f2, f1
/* 800C7BA4 000C2AA4  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800C7BA8 000C2AA8  40 80 00 14 */	bge lbl_800C7BBC
/* 800C7BAC 000C2AAC  FC 80 20 50 */	fneg f4, f4
/* 800C7BB0 000C2AB0  FC 01 20 40 */	fcmpo cr0, f1, f4
/* 800C7BB4 000C2AB4  40 80 00 14 */	bge lbl_800C7BC8
/* 800C7BB8 000C2AB8  48 00 00 14 */	b lbl_800C7BCC
lbl_800C7BBC:
/* 800C7BBC 000C2ABC  FC 01 20 40 */	fcmpo cr0, f1, f4
/* 800C7BC0 000C2AC0  40 81 00 08 */	ble lbl_800C7BC8
/* 800C7BC4 000C2AC4  48 00 00 08 */	b lbl_800C7BCC
lbl_800C7BC8:
/* 800C7BC8 000C2AC8  FC 80 08 90 */	fmr f4, f1
lbl_800C7BCC:
/* 800C7BCC 000C2ACC  D0 83 04 A8 */	stfs f4, 0x4a8(r3)
/* 800C7BD0 000C2AD0  C8 62 95 D8 */	lfd f3, lbl_804C0FF8-_SDA2_BASE_(r2)
/* 800C7BD4 000C2AD4  A8 04 00 04 */	lha r0, 4(r4)
/* 800C7BD8 000C2AD8  C0 23 04 E0 */	lfs f1, 0x4e0(r3)
/* 800C7BDC 000C2ADC  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 800C7BE0 000C2AE0  C0 02 95 A8 */	lfs f0, lbl_804C0FC8-_SDA2_BASE_(r2)
/* 800C7BE4 000C2AE4  90 01 00 24 */	stw r0, 0x24(r1)
/* 800C7BE8 000C2AE8  C0 8D 82 44 */	lfs f4, kp_rm_acc_max-_SDA_BASE_(r13)
/* 800C7BEC 000C2AEC  C8 41 00 20 */	lfd f2, 0x20(r1)
/* 800C7BF0 000C2AF0  EC 42 18 28 */	fsubs f2, f2, f3
/* 800C7BF4 000C2AF4  EC 22 00 72 */	fmuls f1, f2, f1
/* 800C7BF8 000C2AF8  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800C7BFC 000C2AFC  40 80 00 14 */	bge lbl_800C7C10
/* 800C7C00 000C2B00  FC 80 20 50 */	fneg f4, f4
/* 800C7C04 000C2B04  FC 01 20 40 */	fcmpo cr0, f1, f4
/* 800C7C08 000C2B08  40 80 00 14 */	bge lbl_800C7C1C
/* 800C7C0C 000C2B0C  48 00 00 14 */	b lbl_800C7C20
lbl_800C7C10:
/* 800C7C10 000C2B10  FC 01 20 40 */	fcmpo cr0, f1, f4
/* 800C7C14 000C2B14  40 81 00 08 */	ble lbl_800C7C1C
/* 800C7C18 000C2B18  48 00 00 08 */	b lbl_800C7C20
lbl_800C7C1C:
/* 800C7C1C 000C2B1C  FC 80 08 90 */	fmr f4, f1
lbl_800C7C20:
/* 800C7C20 000C2B20  C0 23 04 A4 */	lfs f1, 0x4a4(r3)
/* 800C7C24 000C2B24  C0 03 00 0C */	lfs f0, 0xc(r3)
/* 800C7C28 000C2B28  80 A3 00 0C */	lwz r5, 0xc(r3)
/* 800C7C2C 000C2B2C  EC 41 00 28 */	fsubs f2, f1, f0
/* 800C7C30 000C2B30  C0 02 95 A8 */	lfs f0, lbl_804C0FC8-_SDA2_BASE_(r2)
/* 800C7C34 000C2B34  80 83 00 10 */	lwz r4, 0x10(r3)
/* 800C7C38 000C2B38  80 03 00 14 */	lwz r0, 0x14(r3)
/* 800C7C3C 000C2B3C  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 800C7C40 000C2B40  D0 83 04 AC */	stfs f4, 0x4ac(r3)
/* 800C7C44 000C2B44  90 A1 00 14 */	stw r5, 0x14(r1)
/* 800C7C48 000C2B48  90 81 00 18 */	stw r4, 0x18(r1)
/* 800C7C4C 000C2B4C  90 01 00 1C */	stw r0, 0x1c(r1)
/* 800C7C50 000C2B50  40 80 00 0C */	bge lbl_800C7C5C
/* 800C7C54 000C2B54  FC 60 10 50 */	fneg f3, f2
/* 800C7C58 000C2B58  48 00 00 08 */	b lbl_800C7C60
lbl_800C7C5C:
/* 800C7C5C 000C2B5C  FC 60 10 90 */	fmr f3, f2
lbl_800C7C60:
/* 800C7C60 000C2B60  C0 03 00 9C */	lfs f0, 0x9c(r3)
/* 800C7C64 000C2B64  FC 03 00 40 */	fcmpo cr0, f3, f0
/* 800C7C68 000C2B68  4C 41 13 82 */	cror 2, 1, 2
/* 800C7C6C 000C2B6C  40 82 00 0C */	bne lbl_800C7C78
/* 800C7C70 000C2B70  C0 62 95 BC */	lfs f3, lbl_804C0FDC-_SDA2_BASE_(r2)
/* 800C7C74 000C2B74  48 00 00 10 */	b lbl_800C7C84
lbl_800C7C78:
/* 800C7C78 000C2B78  EC 63 00 24 */	fdivs f3, f3, f0
/* 800C7C7C 000C2B7C  EC 63 00 F2 */	fmuls f3, f3, f3
/* 800C7C80 000C2B80  EC 63 00 F2 */	fmuls f3, f3, f3
lbl_800C7C84:
/* 800C7C84 000C2B84  C0 03 00 A0 */	lfs f0, 0xa0(r3)
/* 800C7C88 000C2B88  C0 83 04 A8 */	lfs f4, 0x4a8(r3)
/* 800C7C8C 000C2B8C  EC 63 00 32 */	fmuls f3, f3, f0
/* 800C7C90 000C2B90  C0 03 00 10 */	lfs f0, 0x10(r3)
/* 800C7C94 000C2B94  C0 23 00 0C */	lfs f1, 0xc(r3)
/* 800C7C98 000C2B98  EC 84 00 28 */	fsubs f4, f4, f0
/* 800C7C9C 000C2B9C  C0 02 95 A8 */	lfs f0, lbl_804C0FC8-_SDA2_BASE_(r2)
/* 800C7CA0 000C2BA0  EC 43 00 B2 */	fmuls f2, f3, f2
/* 800C7CA4 000C2BA4  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 800C7CA8 000C2BA8  EC 01 10 2A */	fadds f0, f1, f2
/* 800C7CAC 000C2BAC  D0 03 00 0C */	stfs f0, 0xc(r3)
/* 800C7CB0 000C2BB0  40 80 00 0C */	bge lbl_800C7CBC
/* 800C7CB4 000C2BB4  FC 40 20 50 */	fneg f2, f4
/* 800C7CB8 000C2BB8  48 00 00 08 */	b lbl_800C7CC0
lbl_800C7CBC:
/* 800C7CBC 000C2BBC  FC 40 20 90 */	fmr f2, f4
lbl_800C7CC0:
/* 800C7CC0 000C2BC0  C0 03 00 9C */	lfs f0, 0x9c(r3)
/* 800C7CC4 000C2BC4  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 800C7CC8 000C2BC8  4C 41 13 82 */	cror 2, 1, 2
/* 800C7CCC 000C2BCC  40 82 00 0C */	bne lbl_800C7CD8
/* 800C7CD0 000C2BD0  C0 42 95 BC */	lfs f2, lbl_804C0FDC-_SDA2_BASE_(r2)
/* 800C7CD4 000C2BD4  48 00 00 10 */	b lbl_800C7CE4
lbl_800C7CD8:
/* 800C7CD8 000C2BD8  EC 42 00 24 */	fdivs f2, f2, f0
/* 800C7CDC 000C2BDC  EC 42 00 B2 */	fmuls f2, f2, f2
/* 800C7CE0 000C2BE0  EC 42 00 B2 */	fmuls f2, f2, f2
lbl_800C7CE4:
/* 800C7CE4 000C2BE4  C0 03 00 A0 */	lfs f0, 0xa0(r3)
/* 800C7CE8 000C2BE8  C0 63 04 AC */	lfs f3, 0x4ac(r3)
/* 800C7CEC 000C2BEC  EC 42 00 32 */	fmuls f2, f2, f0
/* 800C7CF0 000C2BF0  C0 03 00 14 */	lfs f0, 0x14(r3)
/* 800C7CF4 000C2BF4  C0 23 00 10 */	lfs f1, 0x10(r3)
/* 800C7CF8 000C2BF8  EC 63 00 28 */	fsubs f3, f3, f0
/* 800C7CFC 000C2BFC  C0 02 95 A8 */	lfs f0, lbl_804C0FC8-_SDA2_BASE_(r2)
/* 800C7D00 000C2C00  EC 42 01 32 */	fmuls f2, f2, f4
/* 800C7D04 000C2C04  FC 03 00 40 */	fcmpo cr0, f3, f0
/* 800C7D08 000C2C08  EC 01 10 2A */	fadds f0, f1, f2
/* 800C7D0C 000C2C0C  D0 03 00 10 */	stfs f0, 0x10(r3)
/* 800C7D10 000C2C10  40 80 00 0C */	bge lbl_800C7D1C
/* 800C7D14 000C2C14  FC 80 18 50 */	fneg f4, f3
/* 800C7D18 000C2C18  48 00 00 08 */	b lbl_800C7D20
lbl_800C7D1C:
/* 800C7D1C 000C2C1C  FC 80 18 90 */	fmr f4, f3
lbl_800C7D20:
/* 800C7D20 000C2C20  C0 03 00 9C */	lfs f0, 0x9c(r3)
/* 800C7D24 000C2C24  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 800C7D28 000C2C28  4C 41 13 82 */	cror 2, 1, 2
/* 800C7D2C 000C2C2C  40 82 00 0C */	bne lbl_800C7D38
/* 800C7D30 000C2C30  C0 82 95 BC */	lfs f4, lbl_804C0FDC-_SDA2_BASE_(r2)
/* 800C7D34 000C2C34  48 00 00 10 */	b lbl_800C7D44
lbl_800C7D38:
/* 800C7D38 000C2C38  EC 84 00 24 */	fdivs f4, f4, f0
/* 800C7D3C 000C2C3C  EC 84 01 32 */	fmuls f4, f4, f4
/* 800C7D40 000C2C40  EC 84 01 32 */	fmuls f4, f4, f4
lbl_800C7D44:
/* 800C7D44 000C2C44  C0 03 00 A0 */	lfs f0, 0xa0(r3)
/* 800C7D48 000C2C48  C0 23 00 0C */	lfs f1, 0xc(r3)
/* 800C7D4C 000C2C4C  EC 84 00 32 */	fmuls f4, f4, f0
/* 800C7D50 000C2C50  C0 03 00 10 */	lfs f0, 0x10(r3)
/* 800C7D54 000C2C54  C0 43 00 14 */	lfs f2, 0x14(r3)
/* 800C7D58 000C2C58  EC 21 00 72 */	fmuls f1, f1, f1
/* 800C7D5C 000C2C5C  EC 00 00 32 */	fmuls f0, f0, f0
/* 800C7D60 000C2C60  EC 64 00 F2 */	fmuls f3, f4, f3
/* 800C7D64 000C2C64  EC 01 00 2A */	fadds f0, f1, f0
/* 800C7D68 000C2C68  EC 42 18 2A */	fadds f2, f2, f3
/* 800C7D6C 000C2C6C  EC 22 00 B2 */	fmuls f1, f2, f2
/* 800C7D70 000C2C70  D0 43 00 14 */	stfs f2, 0x14(r3)
/* 800C7D74 000C2C74  EC 21 00 2A */	fadds f1, f1, f0
/* 800C7D78 000C2C78  4B FF 93 59 */	bl sqrt
/* 800C7D7C 000C2C7C  C0 41 00 14 */	lfs f2, 0x14(r1)
/* 800C7D80 000C2C80  FC C0 08 18 */	frsp f6, f1
/* 800C7D84 000C2C84  C0 1E 00 0C */	lfs f0, 0xc(r30)
/* 800C7D88 000C2C88  C0 21 00 18 */	lfs f1, 0x18(r1)
/* 800C7D8C 000C2C8C  EC A2 00 28 */	fsubs f5, f2, f0
/* 800C7D90 000C2C90  C0 1E 00 10 */	lfs f0, 0x10(r30)
/* 800C7D94 000C2C94  C0 41 00 1C */	lfs f2, 0x1c(r1)
/* 800C7D98 000C2C98  EC 81 00 28 */	fsubs f4, f1, f0
/* 800C7D9C 000C2C9C  C0 1E 00 14 */	lfs f0, 0x14(r30)
/* 800C7DA0 000C2CA0  EC 25 01 72 */	fmuls f1, f5, f5
/* 800C7DA4 000C2CA4  EC 62 00 28 */	fsubs f3, f2, f0
/* 800C7DA8 000C2CA8  D0 DE 00 18 */	stfs f6, 0x18(r30)
/* 800C7DAC 000C2CAC  EC 04 01 32 */	fmuls f0, f4, f4
/* 800C7DB0 000C2CB0  D0 A1 00 14 */	stfs f5, 0x14(r1)
/* 800C7DB4 000C2CB4  EC 43 00 F2 */	fmuls f2, f3, f3
/* 800C7DB8 000C2CB8  EC 01 00 2A */	fadds f0, f1, f0
/* 800C7DBC 000C2CBC  D0 81 00 18 */	stfs f4, 0x18(r1)
/* 800C7DC0 000C2CC0  D0 61 00 1C */	stfs f3, 0x1c(r1)
/* 800C7DC4 000C2CC4  EC 22 00 2A */	fadds f1, f2, f0
/* 800C7DC8 000C2CC8  4B FF 93 09 */	bl sqrt
/* 800C7DCC 000C2CCC  FC 00 08 18 */	frsp f0, f1
/* 800C7DD0 000C2CD0  7F C3 F3 78 */	mr r3, r30
/* 800C7DD4 000C2CD4  D0 1E 00 1C */	stfs f0, 0x1c(r30)
/* 800C7DD8 000C2CD8  4B FF FA 31 */	bl calc_acc_horizon
/* 800C7DDC 000C2CDC  7F C3 F3 78 */	mr r3, r30
/* 800C7DE0 000C2CE0  4B FF FB BD */	bl calc_acc_vertical
/* 800C7DE4 000C2CE4  88 1F 00 29 */	lbz r0, 0x29(r31)
/* 800C7DE8 000C2CE8  7C 00 07 75 */	extsb. r0, r0
/* 800C7DEC 000C2CEC  40 82 02 C4 */	bne lbl_800C80B0
/* 800C7DF0 000C2CF0  88 1F 00 28 */	lbz r0, 0x28(r31)
/* 800C7DF4 000C2CF4  28 00 00 01 */	cmplwi r0, 1
/* 800C7DF8 000C2CF8  40 82 02 B8 */	bne lbl_800C80B0
/* 800C7DFC 000C2CFC  88 1F 00 36 */	lbz r0, 0x36(r31)
/* 800C7E00 000C2D00  28 00 00 04 */	cmplwi r0, 4
/* 800C7E04 000C2D04  41 82 00 10 */	beq lbl_800C7E14
/* 800C7E08 000C2D08  28 00 00 05 */	cmplwi r0, 5
/* 800C7E0C 000C2D0C  41 82 00 08 */	beq lbl_800C7E14
/* 800C7E10 000C2D10  48 00 02 A0 */	b lbl_800C80B0
lbl_800C7E14:
/* 800C7E14 000C2D14  A8 1F 00 2A */	lha r0, 0x2a(r31)
/* 800C7E18 000C2D18  80 BE 00 68 */	lwz r5, 0x68(r30)
/* 800C7E1C 000C2D1C  7C 00 00 D0 */	neg r0, r0
/* 800C7E20 000C2D20  80 9E 00 6C */	lwz r4, 0x6c(r30)
/* 800C7E24 000C2D24  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 800C7E28 000C2D28  80 7E 00 70 */	lwz r3, 0x70(r30)
/* 800C7E2C 000C2D2C  90 01 00 2C */	stw r0, 0x2c(r1)
/* 800C7E30 000C2D30  C8 42 95 D8 */	lfd f2, lbl_804C0FF8-_SDA2_BASE_(r2)
/* 800C7E34 000C2D34  C8 01 00 28 */	lfd f0, 0x28(r1)
/* 800C7E38 000C2D38  C0 3E 04 E8 */	lfs f1, 0x4e8(r30)
/* 800C7E3C 000C2D3C  EC 40 10 28 */	fsubs f2, f0, f2
/* 800C7E40 000C2D40  C0 02 95 A8 */	lfs f0, lbl_804C0FC8-_SDA2_BASE_(r2)
/* 800C7E44 000C2D44  90 A1 00 08 */	stw r5, 8(r1)
/* 800C7E48 000C2D48  C0 6D 82 48 */	lfs f3, kp_fs_acc_max-_SDA_BASE_(r13)
/* 800C7E4C 000C2D4C  EC 22 00 72 */	fmuls f1, f2, f1
/* 800C7E50 000C2D50  90 81 00 0C */	stw r4, 0xc(r1)
/* 800C7E54 000C2D54  90 61 00 10 */	stw r3, 0x10(r1)
/* 800C7E58 000C2D58  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800C7E5C 000C2D5C  40 80 00 14 */	bge lbl_800C7E70
/* 800C7E60 000C2D60  FC 60 18 50 */	fneg f3, f3
/* 800C7E64 000C2D64  FC 01 18 40 */	fcmpo cr0, f1, f3
/* 800C7E68 000C2D68  40 80 00 14 */	bge lbl_800C7E7C
/* 800C7E6C 000C2D6C  48 00 00 14 */	b lbl_800C7E80
lbl_800C7E70:
/* 800C7E70 000C2D70  FC 01 18 40 */	fcmpo cr0, f1, f3
/* 800C7E74 000C2D74  40 81 00 08 */	ble lbl_800C7E7C
/* 800C7E78 000C2D78  48 00 00 08 */	b lbl_800C7E80
lbl_800C7E7C:
/* 800C7E7C 000C2D7C  FC 60 08 90 */	fmr f3, f1
lbl_800C7E80:
/* 800C7E80 000C2D80  C0 3E 00 68 */	lfs f1, 0x68(r30)
/* 800C7E84 000C2D84  C0 02 95 A8 */	lfs f0, lbl_804C0FC8-_SDA2_BASE_(r2)
/* 800C7E88 000C2D88  EC 83 08 28 */	fsubs f4, f3, f1
/* 800C7E8C 000C2D8C  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 800C7E90 000C2D90  40 80 00 0C */	bge lbl_800C7E9C
/* 800C7E94 000C2D94  FC A0 20 50 */	fneg f5, f4
/* 800C7E98 000C2D98  48 00 00 08 */	b lbl_800C7EA0
lbl_800C7E9C:
/* 800C7E9C 000C2D9C  FC A0 20 90 */	fmr f5, f4
lbl_800C7EA0:
/* 800C7EA0 000C2DA0  C0 1E 00 9C */	lfs f0, 0x9c(r30)
/* 800C7EA4 000C2DA4  FC 05 00 40 */	fcmpo cr0, f5, f0
/* 800C7EA8 000C2DA8  4C 41 13 82 */	cror 2, 1, 2
/* 800C7EAC 000C2DAC  40 82 00 0C */	bne lbl_800C7EB8
/* 800C7EB0 000C2DB0  C0 A2 95 BC */	lfs f5, lbl_804C0FDC-_SDA2_BASE_(r2)
/* 800C7EB4 000C2DB4  48 00 00 10 */	b lbl_800C7EC4
lbl_800C7EB8:
/* 800C7EB8 000C2DB8  EC A5 00 24 */	fdivs f5, f5, f0
/* 800C7EBC 000C2DBC  EC A5 01 72 */	fmuls f5, f5, f5
/* 800C7EC0 000C2DC0  EC A5 01 72 */	fmuls f5, f5, f5
lbl_800C7EC4:
/* 800C7EC4 000C2DC4  C0 1E 00 A0 */	lfs f0, 0xa0(r30)
/* 800C7EC8 000C2DC8  C0 5E 00 68 */	lfs f2, 0x68(r30)
/* 800C7ECC 000C2DCC  EC A5 00 32 */	fmuls f5, f5, f0
/* 800C7ED0 000C2DD0  C8 62 95 D8 */	lfd f3, lbl_804C0FF8-_SDA2_BASE_(r2)
/* 800C7ED4 000C2DD4  C0 3E 04 F0 */	lfs f1, 0x4f0(r30)
/* 800C7ED8 000C2DD8  C0 02 95 A8 */	lfs f0, lbl_804C0FC8-_SDA2_BASE_(r2)
/* 800C7EDC 000C2DDC  EC 85 01 32 */	fmuls f4, f5, f4
/* 800C7EE0 000C2DE0  EC 42 20 2A */	fadds f2, f2, f4
/* 800C7EE4 000C2DE4  D0 5E 00 68 */	stfs f2, 0x68(r30)
/* 800C7EE8 000C2DE8  A8 1F 00 2E */	lha r0, 0x2e(r31)
/* 800C7EEC 000C2DEC  C0 8D 82 48 */	lfs f4, kp_fs_acc_max-_SDA_BASE_(r13)
/* 800C7EF0 000C2DF0  7C 00 00 D0 */	neg r0, r0
/* 800C7EF4 000C2DF4  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 800C7EF8 000C2DF8  90 01 00 24 */	stw r0, 0x24(r1)
/* 800C7EFC 000C2DFC  C8 41 00 20 */	lfd f2, 0x20(r1)
/* 800C7F00 000C2E00  EC 42 18 28 */	fsubs f2, f2, f3
/* 800C7F04 000C2E04  EC 22 00 72 */	fmuls f1, f2, f1
/* 800C7F08 000C2E08  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800C7F0C 000C2E0C  40 80 00 14 */	bge lbl_800C7F20
/* 800C7F10 000C2E10  FC 80 20 50 */	fneg f4, f4
/* 800C7F14 000C2E14  FC 01 20 40 */	fcmpo cr0, f1, f4
/* 800C7F18 000C2E18  40 80 00 14 */	bge lbl_800C7F2C
/* 800C7F1C 000C2E1C  48 00 00 14 */	b lbl_800C7F30
lbl_800C7F20:
/* 800C7F20 000C2E20  FC 01 20 40 */	fcmpo cr0, f1, f4
/* 800C7F24 000C2E24  40 81 00 08 */	ble lbl_800C7F2C
/* 800C7F28 000C2E28  48 00 00 08 */	b lbl_800C7F30
lbl_800C7F2C:
/* 800C7F2C 000C2E2C  FC 80 08 90 */	fmr f4, f1
lbl_800C7F30:
/* 800C7F30 000C2E30  C0 3E 00 6C */	lfs f1, 0x6c(r30)
/* 800C7F34 000C2E34  C0 02 95 A8 */	lfs f0, lbl_804C0FC8-_SDA2_BASE_(r2)
/* 800C7F38 000C2E38  EC 84 08 28 */	fsubs f4, f4, f1
/* 800C7F3C 000C2E3C  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 800C7F40 000C2E40  40 80 00 0C */	bge lbl_800C7F4C
/* 800C7F44 000C2E44  FC A0 20 50 */	fneg f5, f4
/* 800C7F48 000C2E48  48 00 00 08 */	b lbl_800C7F50
lbl_800C7F4C:
/* 800C7F4C 000C2E4C  FC A0 20 90 */	fmr f5, f4
lbl_800C7F50:
/* 800C7F50 000C2E50  C0 1E 00 9C */	lfs f0, 0x9c(r30)
/* 800C7F54 000C2E54  FC 05 00 40 */	fcmpo cr0, f5, f0
/* 800C7F58 000C2E58  4C 41 13 82 */	cror 2, 1, 2
/* 800C7F5C 000C2E5C  40 82 00 0C */	bne lbl_800C7F68
/* 800C7F60 000C2E60  C0 A2 95 BC */	lfs f5, lbl_804C0FDC-_SDA2_BASE_(r2)
/* 800C7F64 000C2E64  48 00 00 10 */	b lbl_800C7F74
lbl_800C7F68:
/* 800C7F68 000C2E68  EC A5 00 24 */	fdivs f5, f5, f0
/* 800C7F6C 000C2E6C  EC A5 01 72 */	fmuls f5, f5, f5
/* 800C7F70 000C2E70  EC A5 01 72 */	fmuls f5, f5, f5
lbl_800C7F74:
/* 800C7F74 000C2E74  C0 1E 00 A0 */	lfs f0, 0xa0(r30)
/* 800C7F78 000C2E78  C0 5E 00 6C */	lfs f2, 0x6c(r30)
/* 800C7F7C 000C2E7C  EC A5 00 32 */	fmuls f5, f5, f0
/* 800C7F80 000C2E80  C8 62 95 D8 */	lfd f3, lbl_804C0FF8-_SDA2_BASE_(r2)
/* 800C7F84 000C2E84  C0 3E 04 EC */	lfs f1, 0x4ec(r30)
/* 800C7F88 000C2E88  C0 02 95 A8 */	lfs f0, lbl_804C0FC8-_SDA2_BASE_(r2)
/* 800C7F8C 000C2E8C  EC 85 01 32 */	fmuls f4, f5, f4
/* 800C7F90 000C2E90  EC 42 20 2A */	fadds f2, f2, f4
/* 800C7F94 000C2E94  D0 5E 00 6C */	stfs f2, 0x6c(r30)
/* 800C7F98 000C2E98  A8 1F 00 2C */	lha r0, 0x2c(r31)
/* 800C7F9C 000C2E9C  C0 8D 82 48 */	lfs f4, kp_fs_acc_max-_SDA_BASE_(r13)
/* 800C7FA0 000C2EA0  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 800C7FA4 000C2EA4  90 01 00 2C */	stw r0, 0x2c(r1)
/* 800C7FA8 000C2EA8  C8 41 00 28 */	lfd f2, 0x28(r1)
/* 800C7FAC 000C2EAC  EC 42 18 28 */	fsubs f2, f2, f3
/* 800C7FB0 000C2EB0  EC 22 00 72 */	fmuls f1, f2, f1
/* 800C7FB4 000C2EB4  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800C7FB8 000C2EB8  40 80 00 14 */	bge lbl_800C7FCC
/* 800C7FBC 000C2EBC  FC 80 20 50 */	fneg f4, f4
/* 800C7FC0 000C2EC0  FC 01 20 40 */	fcmpo cr0, f1, f4
/* 800C7FC4 000C2EC4  40 80 00 14 */	bge lbl_800C7FD8
/* 800C7FC8 000C2EC8  48 00 00 14 */	b lbl_800C7FDC
lbl_800C7FCC:
/* 800C7FCC 000C2ECC  FC 01 20 40 */	fcmpo cr0, f1, f4
/* 800C7FD0 000C2ED0  40 81 00 08 */	ble lbl_800C7FD8
/* 800C7FD4 000C2ED4  48 00 00 08 */	b lbl_800C7FDC
lbl_800C7FD8:
/* 800C7FD8 000C2ED8  FC 80 08 90 */	fmr f4, f1
lbl_800C7FDC:
/* 800C7FDC 000C2EDC  C0 3E 00 70 */	lfs f1, 0x70(r30)
/* 800C7FE0 000C2EE0  C0 02 95 A8 */	lfs f0, lbl_804C0FC8-_SDA2_BASE_(r2)
/* 800C7FE4 000C2EE4  EC 64 08 28 */	fsubs f3, f4, f1
/* 800C7FE8 000C2EE8  FC 03 00 40 */	fcmpo cr0, f3, f0
/* 800C7FEC 000C2EEC  40 80 00 0C */	bge lbl_800C7FF8
/* 800C7FF0 000C2EF0  FC 80 18 50 */	fneg f4, f3
/* 800C7FF4 000C2EF4  48 00 00 08 */	b lbl_800C7FFC
lbl_800C7FF8:
/* 800C7FF8 000C2EF8  FC 80 18 90 */	fmr f4, f3
lbl_800C7FFC:
/* 800C7FFC 000C2EFC  C0 1E 00 9C */	lfs f0, 0x9c(r30)
/* 800C8000 000C2F00  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 800C8004 000C2F04  4C 41 13 82 */	cror 2, 1, 2
/* 800C8008 000C2F08  40 82 00 0C */	bne lbl_800C8014
/* 800C800C 000C2F0C  C0 82 95 BC */	lfs f4, lbl_804C0FDC-_SDA2_BASE_(r2)
/* 800C8010 000C2F10  48 00 00 10 */	b lbl_800C8020
lbl_800C8014:
/* 800C8014 000C2F14  EC 84 00 24 */	fdivs f4, f4, f0
/* 800C8018 000C2F18  EC 84 01 32 */	fmuls f4, f4, f4
/* 800C801C 000C2F1C  EC 84 01 32 */	fmuls f4, f4, f4
lbl_800C8020:
/* 800C8020 000C2F20  C0 1E 00 A0 */	lfs f0, 0xa0(r30)
/* 800C8024 000C2F24  C0 3E 00 68 */	lfs f1, 0x68(r30)
/* 800C8028 000C2F28  EC 84 00 32 */	fmuls f4, f4, f0
/* 800C802C 000C2F2C  C0 1E 00 6C */	lfs f0, 0x6c(r30)
/* 800C8030 000C2F30  C0 5E 00 70 */	lfs f2, 0x70(r30)
/* 800C8034 000C2F34  EC 21 00 72 */	fmuls f1, f1, f1
/* 800C8038 000C2F38  EC 00 00 32 */	fmuls f0, f0, f0
/* 800C803C 000C2F3C  EC 64 00 F2 */	fmuls f3, f4, f3
/* 800C8040 000C2F40  EC 01 00 2A */	fadds f0, f1, f0
/* 800C8044 000C2F44  EC 42 18 2A */	fadds f2, f2, f3
/* 800C8048 000C2F48  EC 22 00 B2 */	fmuls f1, f2, f2
/* 800C804C 000C2F4C  D0 5E 00 70 */	stfs f2, 0x70(r30)
/* 800C8050 000C2F50  EC 21 00 2A */	fadds f1, f1, f0
/* 800C8054 000C2F54  4B FF 90 7D */	bl sqrt
/* 800C8058 000C2F58  C0 41 00 08 */	lfs f2, 8(r1)
/* 800C805C 000C2F5C  FC C0 08 18 */	frsp f6, f1
/* 800C8060 000C2F60  C0 1E 00 68 */	lfs f0, 0x68(r30)
/* 800C8064 000C2F64  C0 21 00 0C */	lfs f1, 0xc(r1)
/* 800C8068 000C2F68  EC A2 00 28 */	fsubs f5, f2, f0
/* 800C806C 000C2F6C  C0 1E 00 6C */	lfs f0, 0x6c(r30)
/* 800C8070 000C2F70  C0 41 00 10 */	lfs f2, 0x10(r1)
/* 800C8074 000C2F74  EC 81 00 28 */	fsubs f4, f1, f0
/* 800C8078 000C2F78  C0 1E 00 70 */	lfs f0, 0x70(r30)
/* 800C807C 000C2F7C  EC 25 01 72 */	fmuls f1, f5, f5
/* 800C8080 000C2F80  EC 62 00 28 */	fsubs f3, f2, f0
/* 800C8084 000C2F84  D0 DE 00 74 */	stfs f6, 0x74(r30)
/* 800C8088 000C2F88  EC 04 01 32 */	fmuls f0, f4, f4
/* 800C808C 000C2F8C  D0 A1 00 08 */	stfs f5, 8(r1)
/* 800C8090 000C2F90  EC 43 00 F2 */	fmuls f2, f3, f3
/* 800C8094 000C2F94  EC 01 00 2A */	fadds f0, f1, f0
/* 800C8098 000C2F98  D0 81 00 0C */	stfs f4, 0xc(r1)
/* 800C809C 000C2F9C  D0 61 00 10 */	stfs f3, 0x10(r1)
/* 800C80A0 000C2FA0  EC 22 00 2A */	fadds f1, f2, f0
/* 800C80A4 000C2FA4  4B FF 90 2D */	bl sqrt
/* 800C80A8 000C2FA8  FC 00 08 18 */	frsp f0, f1
/* 800C80AC 000C2FAC  D0 1E 00 78 */	stfs f0, 0x78(r30)
lbl_800C80B0:
/* 800C80B0 000C2FB0  80 01 00 44 */	lwz r0, 0x44(r1)
/* 800C80B4 000C2FB4  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 800C80B8 000C2FB8  83 C1 00 38 */	lwz r30, 0x38(r1)
/* 800C80BC 000C2FBC  7C 08 03 A6 */	mtlr r0
/* 800C80C0 000C2FC0  38 21 00 40 */	addi r1, r1, 0x40
/* 800C80C4 000C2FC4  4E 80 00 20 */	blr 

.global select_2obj_first
select_2obj_first:
/* 800C80C8 000C2FC8  94 21 FF 80 */	stwu r1, -0x80(r1)
/* 800C80CC 000C2FCC  7C 08 02 A6 */	mflr r0
/* 800C80D0 000C2FD0  90 01 00 84 */	stw r0, 0x84(r1)
/* 800C80D4 000C2FD4  DB E1 00 70 */	stfd f31, 0x70(r1)
/* 800C80D8 000C2FD8  F3 E1 00 78 */	psq_st f31, 120(r1), 0, qr0
/* 800C80DC 000C2FDC  DB C1 00 60 */	stfd f30, 0x60(r1)
/* 800C80E0 000C2FE0  F3 C1 00 68 */	psq_st f30, 104(r1), 0, qr0
/* 800C80E4 000C2FE4  DB A1 00 50 */	stfd f29, 0x50(r1)
/* 800C80E8 000C2FE8  F3 A1 00 58 */	psq_st f29, 88(r1), 0, qr0
/* 800C80EC 000C2FEC  DB 81 00 40 */	stfd f28, 0x40(r1)
/* 800C80F0 000C2FF0  F3 81 00 48 */	psq_st f28, 72(r1), 0, qr0
/* 800C80F4 000C2FF4  DB 61 00 30 */	stfd f27, 0x30(r1)
/* 800C80F8 000C2FF8  F3 61 00 38 */	psq_st f27, 56(r1), 0, qr0
/* 800C80FC 000C2FFC  39 61 00 30 */	addi r11, r1, 0x30
/* 800C8100 000C3000  4B FE 9C 3D */	bl _savegpr_25
/* 800C8104 000C3004  C3 CD 82 18 */	lfs f30, kp_err_first_inpr-_SDA_BASE_(r13)
/* 800C8108 000C3008  7C 79 1B 78 */	mr r25, r3
/* 800C810C 000C300C  C3 A2 95 A8 */	lfs f29, lbl_804C0FC8-_SDA2_BASE_(r2)
/* 800C8110 000C3010  3B A3 00 C4 */	addi r29, r3, 0xc4
/* 800C8114 000C3014  C3 E2 95 BC */	lfs f31, lbl_804C0FDC-_SDA2_BASE_(r2)
/* 800C8118 000C3018  3B E3 00 E8 */	addi r31, r3, 0xe8
lbl_800C811C:
/* 800C811C 000C301C  88 1D 00 08 */	lbz r0, 8(r29)
/* 800C8120 000C3020  7C 00 07 75 */	extsb. r0, r0
/* 800C8124 000C3024  40 82 00 F8 */	bne lbl_800C821C
/* 800C8128 000C3028  3B 9D 00 0C */	addi r28, r29, 0xc
/* 800C812C 000C302C  3B D9 00 E8 */	addi r30, r25, 0xe8
lbl_800C8130:
/* 800C8130 000C3030  88 1C 00 08 */	lbz r0, 8(r28)
/* 800C8134 000C3034  7C 00 07 75 */	extsb. r0, r0
/* 800C8138 000C3038  40 82 00 D8 */	bne lbl_800C8210
/* 800C813C 000C303C  C0 7C 00 00 */	lfs f3, 0(r28)
/* 800C8140 000C3040  C0 5D 00 00 */	lfs f2, 0(r29)
/* 800C8144 000C3044  C0 3C 00 04 */	lfs f1, 4(r28)
/* 800C8148 000C3048  C0 1D 00 04 */	lfs f0, 4(r29)
/* 800C814C 000C304C  EF 63 10 28 */	fsubs f27, f3, f2
/* 800C8150 000C3050  EF 81 00 28 */	fsubs f28, f1, f0
/* 800C8154 000C3054  EC 3B 06 F2 */	fmuls f1, f27, f27
/* 800C8158 000C3058  EC 1C 07 32 */	fmuls f0, f28, f28
/* 800C815C 000C305C  EC 21 00 2A */	fadds f1, f1, f0
/* 800C8160 000C3060  4B FF 8F 71 */	bl sqrt
/* 800C8164 000C3064  FC 00 08 18 */	frsp f0, f1
/* 800C8168 000C3068  C0 B9 00 B0 */	lfs f5, 0xb0(r25)
/* 800C816C 000C306C  C0 59 00 B4 */	lfs f2, 0xb4(r25)
/* 800C8170 000C3070  C0 39 05 10 */	lfs f1, 0x510(r25)
/* 800C8174 000C3074  EC 7F 00 24 */	fdivs f3, f31, f0
/* 800C8178 000C3078  C0 19 05 14 */	lfs f0, 0x514(r25)
/* 800C817C 000C307C  EF 7B 00 F2 */	fmuls f27, f27, f3
/* 800C8180 000C3080  EF 9C 00 F2 */	fmuls f28, f28, f3
/* 800C8184 000C3084  EC C1 00 F2 */	fmuls f6, f1, f3
/* 800C8188 000C3088  EC 85 06 F2 */	fmuls f4, f5, f27
/* 800C818C 000C308C  EC 62 07 32 */	fmuls f3, f2, f28
/* 800C8190 000C3090  EC 42 06 F2 */	fmuls f2, f2, f27
/* 800C8194 000C3094  EC 25 07 32 */	fmuls f1, f5, f28
/* 800C8198 000C3098  EC 64 18 2A */	fadds f3, f4, f3
/* 800C819C 000C309C  FC 06 00 40 */	fcmpo cr0, f6, f0
/* 800C81A0 000C30A0  EC 42 08 28 */	fsubs f2, f2, f1
/* 800C81A4 000C30A4  D0 61 00 08 */	stfs f3, 8(r1)
/* 800C81A8 000C30A8  D0 41 00 0C */	stfs f2, 0xc(r1)
/* 800C81AC 000C30AC  4C 40 13 82 */	cror 2, 0, 2
/* 800C81B0 000C30B0  41 82 00 60 */	beq lbl_800C8210
/* 800C81B4 000C30B4  C0 0D 82 10 */	lfs f0, kp_err_dist_max-_SDA_BASE_(r13)
/* 800C81B8 000C30B8  FC 06 00 40 */	fcmpo cr0, f6, f0
/* 800C81BC 000C30BC  4C 41 13 82 */	cror 2, 1, 2
/* 800C81C0 000C30C0  41 82 00 50 */	beq lbl_800C8210
/* 800C81C4 000C30C4  C0 39 04 B8 */	lfs f1, 0x4b8(r25)
/* 800C81C8 000C30C8  C0 19 04 BC */	lfs f0, 0x4bc(r25)
/* 800C81CC 000C30CC  EC 21 00 F2 */	fmuls f1, f1, f3
/* 800C81D0 000C30D0  EC 00 00 B2 */	fmuls f0, f0, f2
/* 800C81D4 000C30D4  EC 01 00 2A */	fadds f0, f1, f0
/* 800C81D8 000C30D8  FC 00 E8 40 */	fcmpo cr0, f0, f29
/* 800C81DC 000C30DC  40 80 00 20 */	bge lbl_800C81FC
/* 800C81E0 000C30E0  FC 00 00 50 */	fneg f0, f0
/* 800C81E4 000C30E4  FC 00 F0 40 */	fcmpo cr0, f0, f30
/* 800C81E8 000C30E8  40 81 00 28 */	ble lbl_800C8210
/* 800C81EC 000C30EC  FF C0 00 90 */	fmr f30, f0
/* 800C81F0 000C30F0  7F 9B E3 78 */	mr r27, r28
/* 800C81F4 000C30F4  7F BA EB 78 */	mr r26, r29
/* 800C81F8 000C30F8  48 00 00 18 */	b lbl_800C8210
lbl_800C81FC:
/* 800C81FC 000C30FC  FC 00 F0 40 */	fcmpo cr0, f0, f30
/* 800C8200 000C3100  40 81 00 10 */	ble lbl_800C8210
/* 800C8204 000C3104  FF C0 00 90 */	fmr f30, f0
/* 800C8208 000C3108  7F BB EB 78 */	mr r27, r29
/* 800C820C 000C310C  7F 9A E3 78 */	mr r26, r28
lbl_800C8210:
/* 800C8210 000C3110  3B 9C 00 0C */	addi r28, r28, 0xc
/* 800C8214 000C3114  7C 1C F0 40 */	cmplw r28, r30
/* 800C8218 000C3118  40 81 FF 18 */	ble lbl_800C8130
lbl_800C821C:
/* 800C821C 000C311C  3B BD 00 0C */	addi r29, r29, 0xc
/* 800C8220 000C3120  7C 1D F8 40 */	cmplw r29, r31
/* 800C8224 000C3124  41 80 FE F8 */	blt lbl_800C811C
/* 800C8228 000C3128  C0 0D 82 18 */	lfs f0, kp_err_first_inpr-_SDA_BASE_(r13)
/* 800C822C 000C312C  FC 1E 00 00 */	fcmpu cr0, f30, f0
/* 800C8230 000C3130  40 82 00 0C */	bne lbl_800C823C
/* 800C8234 000C3134  38 60 00 00 */	li r3, 0
/* 800C8238 000C3138  48 00 00 38 */	b lbl_800C8270
lbl_800C823C:
/* 800C823C 000C313C  80 9B 00 00 */	lwz r4, 0(r27)
/* 800C8240 000C3140  38 60 00 02 */	li r3, 2
/* 800C8244 000C3144  80 1B 00 04 */	lwz r0, 4(r27)
/* 800C8248 000C3148  90 99 00 F4 */	stw r4, 0xf4(r25)
/* 800C824C 000C314C  90 19 00 F8 */	stw r0, 0xf8(r25)
/* 800C8250 000C3150  80 1B 00 08 */	lwz r0, 8(r27)
/* 800C8254 000C3154  90 19 00 FC */	stw r0, 0xfc(r25)
/* 800C8258 000C3158  80 9A 00 00 */	lwz r4, 0(r26)
/* 800C825C 000C315C  80 1A 00 04 */	lwz r0, 4(r26)
/* 800C8260 000C3160  90 99 01 00 */	stw r4, 0x100(r25)
/* 800C8264 000C3164  90 19 01 04 */	stw r0, 0x104(r25)
/* 800C8268 000C3168  80 1A 00 08 */	lwz r0, 8(r26)
/* 800C826C 000C316C  90 19 01 08 */	stw r0, 0x108(r25)
lbl_800C8270:
/* 800C8270 000C3170  E3 E1 00 78 */	psq_l f31, 120(r1), 0, qr0
/* 800C8274 000C3174  CB E1 00 70 */	lfd f31, 0x70(r1)
/* 800C8278 000C3178  E3 C1 00 68 */	psq_l f30, 104(r1), 0, qr0
/* 800C827C 000C317C  CB C1 00 60 */	lfd f30, 0x60(r1)
/* 800C8280 000C3180  E3 A1 00 58 */	psq_l f29, 88(r1), 0, qr0
/* 800C8284 000C3184  CB A1 00 50 */	lfd f29, 0x50(r1)
/* 800C8288 000C3188  E3 81 00 48 */	psq_l f28, 72(r1), 0, qr0
/* 800C828C 000C318C  CB 81 00 40 */	lfd f28, 0x40(r1)
/* 800C8290 000C3190  E3 61 00 38 */	psq_l f27, 56(r1), 0, qr0
/* 800C8294 000C3194  39 61 00 30 */	addi r11, r1, 0x30
/* 800C8298 000C3198  CB 61 00 30 */	lfd f27, 0x30(r1)
/* 800C829C 000C319C  4B FE 9A ED */	bl _restgpr_25
/* 800C82A0 000C31A0  80 01 00 84 */	lwz r0, 0x84(r1)
/* 800C82A4 000C31A4  7C 08 03 A6 */	mtlr r0
/* 800C82A8 000C31A8  38 21 00 80 */	addi r1, r1, 0x80
/* 800C82AC 000C31AC  4E 80 00 20 */	blr 

.global select_2obj_continue
select_2obj_continue:
/* 800C82B0 000C31B0  94 21 FF 80 */	stwu r1, -0x80(r1)
/* 800C82B4 000C31B4  7C 08 02 A6 */	mflr r0
/* 800C82B8 000C31B8  90 01 00 84 */	stw r0, 0x84(r1)
/* 800C82BC 000C31BC  DB E1 00 70 */	stfd f31, 0x70(r1)
/* 800C82C0 000C31C0  F3 E1 00 78 */	psq_st f31, 120(r1), 0, qr0
/* 800C82C4 000C31C4  DB C1 00 60 */	stfd f30, 0x60(r1)
/* 800C82C8 000C31C8  F3 C1 00 68 */	psq_st f30, 104(r1), 0, qr0
/* 800C82CC 000C31CC  DB A1 00 50 */	stfd f29, 0x50(r1)
/* 800C82D0 000C31D0  F3 A1 00 58 */	psq_st f29, 88(r1), 0, qr0
/* 800C82D4 000C31D4  DB 81 00 40 */	stfd f28, 0x40(r1)
/* 800C82D8 000C31D8  F3 81 00 48 */	psq_st f28, 72(r1), 0, qr0
/* 800C82DC 000C31DC  DB 61 00 30 */	stfd f27, 0x30(r1)
/* 800C82E0 000C31E0  F3 61 00 38 */	psq_st f27, 56(r1), 0, qr0
/* 800C82E4 000C31E4  39 61 00 30 */	addi r11, r1, 0x30
/* 800C82E8 000C31E8  4B FE 9A 55 */	bl _savegpr_25
/* 800C82EC 000C31EC  C3 E2 95 D0 */	lfs f31, lbl_804C0FF0-_SDA2_BASE_(r2)
/* 800C82F0 000C31F0  7C 7F 1B 78 */	mr r31, r3
/* 800C82F4 000C31F4  C3 A2 95 A8 */	lfs f29, lbl_804C0FC8-_SDA2_BASE_(r2)
/* 800C82F8 000C31F8  3B 83 00 C4 */	addi r28, r3, 0xc4
/* 800C82FC 000C31FC  C3 C2 95 BC */	lfs f30, lbl_804C0FDC-_SDA2_BASE_(r2)
/* 800C8300 000C3200  3B C3 00 E8 */	addi r30, r3, 0xe8
lbl_800C8304:
/* 800C8304 000C3204  88 1C 00 08 */	lbz r0, 8(r28)
/* 800C8308 000C3208  7C 00 07 75 */	extsb. r0, r0
/* 800C830C 000C320C  40 82 01 38 */	bne lbl_800C8444
/* 800C8310 000C3210  3B 7C 00 0C */	addi r27, r28, 0xc
/* 800C8314 000C3214  3B BF 00 E8 */	addi r29, r31, 0xe8
lbl_800C8318:
/* 800C8318 000C3218  88 1B 00 08 */	lbz r0, 8(r27)
/* 800C831C 000C321C  7C 00 07 75 */	extsb. r0, r0
/* 800C8320 000C3220  40 82 01 18 */	bne lbl_800C8438
/* 800C8324 000C3224  C0 7B 00 00 */	lfs f3, 0(r27)
/* 800C8328 000C3228  C0 5C 00 00 */	lfs f2, 0(r28)
/* 800C832C 000C322C  C0 3B 00 04 */	lfs f1, 4(r27)
/* 800C8330 000C3230  C0 1C 00 04 */	lfs f0, 4(r28)
/* 800C8334 000C3234  EF 83 10 28 */	fsubs f28, f3, f2
/* 800C8338 000C3238  EF 61 00 28 */	fsubs f27, f1, f0
/* 800C833C 000C323C  EC 3C 07 32 */	fmuls f1, f28, f28
/* 800C8340 000C3240  EC 1B 06 F2 */	fmuls f0, f27, f27
/* 800C8344 000C3244  EC 21 00 2A */	fadds f1, f1, f0
/* 800C8348 000C3248  4B FF 8D 89 */	bl sqrt
/* 800C834C 000C324C  FC 40 08 18 */	frsp f2, f1
/* 800C8350 000C3250  C0 3F 05 10 */	lfs f1, 0x510(r31)
/* 800C8354 000C3254  C0 1F 05 14 */	lfs f0, 0x514(r31)
/* 800C8358 000C3258  EC 9E 10 24 */	fdivs f4, f30, f2
/* 800C835C 000C325C  EC 7C 01 32 */	fmuls f3, f28, f4
/* 800C8360 000C3260  EC 5B 01 32 */	fmuls f2, f27, f4
/* 800C8364 000C3264  EC 84 00 72 */	fmuls f4, f4, f1
/* 800C8368 000C3268  D0 61 00 08 */	stfs f3, 8(r1)
/* 800C836C 000C326C  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 800C8370 000C3270  D0 41 00 0C */	stfs f2, 0xc(r1)
/* 800C8374 000C3274  4C 40 13 82 */	cror 2, 0, 2
/* 800C8378 000C3278  41 82 00 C0 */	beq lbl_800C8438
/* 800C837C 000C327C  C0 0D 82 10 */	lfs f0, kp_err_dist_max-_SDA_BASE_(r13)
/* 800C8380 000C3280  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 800C8384 000C3284  4C 41 13 82 */	cror 2, 1, 2
/* 800C8388 000C3288  41 82 00 B0 */	beq lbl_800C8438
/* 800C838C 000C328C  C0 1F 04 9C */	lfs f0, 0x49c(r31)
/* 800C8390 000C3290  EC 84 00 28 */	fsubs f4, f4, f0
/* 800C8394 000C3294  FC 04 E8 40 */	fcmpo cr0, f4, f29
/* 800C8398 000C3298  40 80 00 10 */	bge lbl_800C83A8
/* 800C839C 000C329C  C0 1F 05 08 */	lfs f0, 0x508(r31)
/* 800C83A0 000C32A0  EC 84 00 32 */	fmuls f4, f4, f0
/* 800C83A4 000C32A4  48 00 00 0C */	b lbl_800C83B0
lbl_800C83A8:
/* 800C83A8 000C32A8  C0 1F 05 04 */	lfs f0, 0x504(r31)
/* 800C83AC 000C32AC  EC 84 00 32 */	fmuls f4, f4, f0
lbl_800C83B0:
/* 800C83B0 000C32B0  FC 04 F0 40 */	fcmpo cr0, f4, f30
/* 800C83B4 000C32B4  4C 41 13 82 */	cror 2, 1, 2
/* 800C83B8 000C32B8  41 82 00 80 */	beq lbl_800C8438
/* 800C83BC 000C32BC  C0 7F 04 94 */	lfs f3, 0x494(r31)
/* 800C83C0 000C32C0  C0 41 00 08 */	lfs f2, 8(r1)
/* 800C83C4 000C32C4  C0 3F 04 98 */	lfs f1, 0x498(r31)
/* 800C83C8 000C32C8  C0 01 00 0C */	lfs f0, 0xc(r1)
/* 800C83CC 000C32CC  EC 43 00 B2 */	fmuls f2, f3, f2
/* 800C83D0 000C32D0  EC 01 00 32 */	fmuls f0, f1, f0
/* 800C83D4 000C32D4  EC 22 00 2A */	fadds f1, f2, f0
/* 800C83D8 000C32D8  FC 01 E8 40 */	fcmpo cr0, f1, f29
/* 800C83DC 000C32DC  40 80 00 10 */	bge lbl_800C83EC
/* 800C83E0 000C32E0  FC 20 08 50 */	fneg f1, f1
/* 800C83E4 000C32E4  38 00 00 01 */	li r0, 1
/* 800C83E8 000C32E8  48 00 00 08 */	b lbl_800C83F0
lbl_800C83EC:
/* 800C83EC 000C32EC  38 00 00 00 */	li r0, 0
lbl_800C83F0:
/* 800C83F0 000C32F0  C0 0D 82 1C */	lfs f0, kp_err_next_inpr-_SDA_BASE_(r13)
/* 800C83F4 000C32F4  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800C83F8 000C32F8  4C 40 13 82 */	cror 2, 0, 2
/* 800C83FC 000C32FC  41 82 00 3C */	beq lbl_800C8438
/* 800C8400 000C3300  EC 3E 08 28 */	fsubs f1, f30, f1
/* 800C8404 000C3304  EC 1E 00 28 */	fsubs f0, f30, f0
/* 800C8408 000C3308  EC 01 00 24 */	fdivs f0, f1, f0
/* 800C840C 000C330C  EC 84 00 2A */	fadds f4, f4, f0
/* 800C8410 000C3310  FC 04 F8 40 */	fcmpo cr0, f4, f31
/* 800C8414 000C3314  40 80 00 24 */	bge lbl_800C8438
/* 800C8418 000C3318  FF E0 20 90 */	fmr f31, f4
/* 800C841C 000C331C  2C 00 00 00 */	cmpwi r0, 0
/* 800C8420 000C3320  41 82 00 10 */	beq lbl_800C8430
/* 800C8424 000C3324  7F 7A DB 78 */	mr r26, r27
/* 800C8428 000C3328  7F 99 E3 78 */	mr r25, r28
/* 800C842C 000C332C  48 00 00 0C */	b lbl_800C8438
lbl_800C8430:
/* 800C8430 000C3330  7F 9A E3 78 */	mr r26, r28
/* 800C8434 000C3334  7F 79 DB 78 */	mr r25, r27
lbl_800C8438:
/* 800C8438 000C3338  3B 7B 00 0C */	addi r27, r27, 0xc
/* 800C843C 000C333C  7C 1B E8 40 */	cmplw r27, r29
/* 800C8440 000C3340  40 81 FE D8 */	ble lbl_800C8318
lbl_800C8444:
/* 800C8444 000C3344  3B 9C 00 0C */	addi r28, r28, 0xc
/* 800C8448 000C3348  7C 1C F0 40 */	cmplw r28, r30
/* 800C844C 000C334C  41 80 FE B8 */	blt lbl_800C8304
/* 800C8450 000C3350  C0 02 95 D0 */	lfs f0, lbl_804C0FF0-_SDA2_BASE_(r2)
/* 800C8454 000C3354  FC 00 F8 00 */	fcmpu cr0, f0, f31
/* 800C8458 000C3358  40 82 00 0C */	bne lbl_800C8464
/* 800C845C 000C335C  38 60 00 00 */	li r3, 0
/* 800C8460 000C3360  48 00 00 38 */	b lbl_800C8498
lbl_800C8464:
/* 800C8464 000C3364  80 9A 00 00 */	lwz r4, 0(r26)
/* 800C8468 000C3368  38 60 00 02 */	li r3, 2
/* 800C846C 000C336C  80 1A 00 04 */	lwz r0, 4(r26)
/* 800C8470 000C3370  90 9F 00 F4 */	stw r4, 0xf4(r31)
/* 800C8474 000C3374  90 1F 00 F8 */	stw r0, 0xf8(r31)
/* 800C8478 000C3378  80 1A 00 08 */	lwz r0, 8(r26)
/* 800C847C 000C337C  90 1F 00 FC */	stw r0, 0xfc(r31)
/* 800C8480 000C3380  80 99 00 00 */	lwz r4, 0(r25)
/* 800C8484 000C3384  80 19 00 04 */	lwz r0, 4(r25)
/* 800C8488 000C3388  90 9F 01 00 */	stw r4, 0x100(r31)
/* 800C848C 000C338C  90 1F 01 04 */	stw r0, 0x104(r31)
/* 800C8490 000C3390  80 19 00 08 */	lwz r0, 8(r25)
/* 800C8494 000C3394  90 1F 01 08 */	stw r0, 0x108(r31)
lbl_800C8498:
/* 800C8498 000C3398  E3 E1 00 78 */	psq_l f31, 120(r1), 0, qr0
/* 800C849C 000C339C  CB E1 00 70 */	lfd f31, 0x70(r1)
/* 800C84A0 000C33A0  E3 C1 00 68 */	psq_l f30, 104(r1), 0, qr0
/* 800C84A4 000C33A4  CB C1 00 60 */	lfd f30, 0x60(r1)
/* 800C84A8 000C33A8  E3 A1 00 58 */	psq_l f29, 88(r1), 0, qr0
/* 800C84AC 000C33AC  CB A1 00 50 */	lfd f29, 0x50(r1)
/* 800C84B0 000C33B0  E3 81 00 48 */	psq_l f28, 72(r1), 0, qr0
/* 800C84B4 000C33B4  CB 81 00 40 */	lfd f28, 0x40(r1)
/* 800C84B8 000C33B8  E3 61 00 38 */	psq_l f27, 56(r1), 0, qr0
/* 800C84BC 000C33BC  39 61 00 30 */	addi r11, r1, 0x30
/* 800C84C0 000C33C0  CB 61 00 30 */	lfd f27, 0x30(r1)
/* 800C84C4 000C33C4  4B FE 98 C5 */	bl _restgpr_25
/* 800C84C8 000C33C8  80 01 00 84 */	lwz r0, 0x84(r1)
/* 800C84CC 000C33CC  7C 08 03 A6 */	mtlr r0
/* 800C84D0 000C33D0  38 21 00 80 */	addi r1, r1, 0x80
/* 800C84D4 000C33D4  4E 80 00 20 */	blr 

.global select_1obj_first
select_1obj_first:
/* 800C84D8 000C33D8  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800C84DC 000C33DC  39 03 00 C4 */	addi r8, r3, 0xc4
/* 800C84E0 000C33E0  38 03 00 F4 */	addi r0, r3, 0xf4
/* 800C84E4 000C33E4  C0 A3 00 B0 */	lfs f5, 0xb0(r3)
/* 800C84E8 000C33E8  C0 03 04 B8 */	lfs f0, 0x4b8(r3)
/* 800C84EC 000C33EC  C0 63 00 B4 */	lfs f3, 0xb4(r3)
/* 800C84F0 000C33F0  C0 23 04 BC */	lfs f1, 0x4bc(r3)
/* 800C84F4 000C33F4  EC 85 00 32 */	fmuls f4, f5, f0
/* 800C84F8 000C33F8  EC 43 00 32 */	fmuls f2, f3, f0
/* 800C84FC 000C33FC  C0 03 04 A0 */	lfs f0, 0x4a0(r3)
/* 800C8500 000C3400  EC 63 00 72 */	fmuls f3, f3, f1
/* 800C8504 000C3404  EC 25 00 72 */	fmuls f1, f5, f1
/* 800C8508 000C3408  EC E4 18 2A */	fadds f7, f4, f3
/* 800C850C 000C340C  ED 02 08 28 */	fsubs f8, f2, f1
/* 800C8510 000C3410  EC E7 00 32 */	fmuls f7, f7, f0
/* 800C8514 000C3414  ED 08 00 32 */	fmuls f8, f8, f0
lbl_800C8518:
/* 800C8518 000C3418  88 88 00 08 */	lbz r4, 8(r8)
/* 800C851C 000C341C  7C 84 07 75 */	extsb. r4, r4
/* 800C8520 000C3420  40 82 01 54 */	bne lbl_800C8674
/* 800C8524 000C3424  C0 48 00 00 */	lfs f2, 0(r8)
/* 800C8528 000C3428  C0 08 00 04 */	lfs f0, 4(r8)
/* 800C852C 000C342C  EC 22 38 28 */	fsubs f1, f2, f7
/* 800C8530 000C3430  C0 63 04 F4 */	lfs f3, 0x4f4(r3)
/* 800C8534 000C3434  EC C0 40 28 */	fsubs f6, f0, f8
/* 800C8538 000C3438  EC A2 38 2A */	fadds f5, f2, f7
/* 800C853C 000C343C  EC 80 40 2A */	fadds f4, f0, f8
/* 800C8540 000C3440  D0 21 00 10 */	stfs f1, 0x10(r1)
/* 800C8544 000C3444  FC 01 18 40 */	fcmpo cr0, f1, f3
/* 800C8548 000C3448  D0 C1 00 14 */	stfs f6, 0x14(r1)
/* 800C854C 000C344C  D0 A1 00 08 */	stfs f5, 8(r1)
/* 800C8550 000C3450  D0 81 00 0C */	stfs f4, 0xc(r1)
/* 800C8554 000C3454  4C 40 13 82 */	cror 2, 0, 2
/* 800C8558 000C3458  41 82 00 34 */	beq lbl_800C858C
/* 800C855C 000C345C  C0 43 04 FC */	lfs f2, 0x4fc(r3)
/* 800C8560 000C3460  FC 01 10 40 */	fcmpo cr0, f1, f2
/* 800C8564 000C3464  4C 41 13 82 */	cror 2, 1, 2
/* 800C8568 000C3468  41 82 00 24 */	beq lbl_800C858C
/* 800C856C 000C346C  C0 23 04 F8 */	lfs f1, 0x4f8(r3)
/* 800C8570 000C3470  FC 06 08 40 */	fcmpo cr0, f6, f1
/* 800C8574 000C3474  4C 40 13 82 */	cror 2, 0, 2
/* 800C8578 000C3478  41 82 00 14 */	beq lbl_800C858C
/* 800C857C 000C347C  C0 03 05 00 */	lfs f0, 0x500(r3)
/* 800C8580 000C3480  FC 06 00 40 */	fcmpo cr0, f6, f0
/* 800C8584 000C3484  4C 41 13 82 */	cror 2, 1, 2
/* 800C8588 000C3488  40 82 00 7C */	bne lbl_800C8604
lbl_800C858C:
/* 800C858C 000C348C  C0 21 00 08 */	lfs f1, 8(r1)
/* 800C8590 000C3490  C0 03 04 F4 */	lfs f0, 0x4f4(r3)
/* 800C8594 000C3494  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800C8598 000C3498  40 81 00 DC */	ble lbl_800C8674
/* 800C859C 000C349C  C0 03 04 FC */	lfs f0, 0x4fc(r3)
/* 800C85A0 000C34A0  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800C85A4 000C34A4  40 80 00 D0 */	bge lbl_800C8674
/* 800C85A8 000C34A8  C0 21 00 0C */	lfs f1, 0xc(r1)
/* 800C85AC 000C34AC  C0 03 04 F8 */	lfs f0, 0x4f8(r3)
/* 800C85B0 000C34B0  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800C85B4 000C34B4  40 81 00 C0 */	ble lbl_800C8674
/* 800C85B8 000C34B8  C0 03 05 00 */	lfs f0, 0x500(r3)
/* 800C85BC 000C34BC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800C85C0 000C34C0  40 80 00 B4 */	bge lbl_800C8674
/* 800C85C4 000C34C4  80 A8 00 00 */	lwz r5, 0(r8)
/* 800C85C8 000C34C8  38 80 00 00 */	li r4, 0
/* 800C85CC 000C34CC  80 E8 00 04 */	lwz r7, 4(r8)
/* 800C85D0 000C34D0  38 00 FF FF */	li r0, -1
/* 800C85D4 000C34D4  80 C1 00 10 */	lwz r6, 0x10(r1)
/* 800C85D8 000C34D8  90 A3 01 00 */	stw r5, 0x100(r3)
/* 800C85DC 000C34DC  80 A1 00 14 */	lwz r5, 0x14(r1)
/* 800C85E0 000C34E0  90 E3 01 04 */	stw r7, 0x104(r3)
/* 800C85E4 000C34E4  80 E8 00 08 */	lwz r7, 8(r8)
/* 800C85E8 000C34E8  90 E3 01 08 */	stw r7, 0x108(r3)
/* 800C85EC 000C34EC  90 C3 00 F4 */	stw r6, 0xf4(r3)
/* 800C85F0 000C34F0  90 A3 00 F8 */	stw r5, 0xf8(r3)
/* 800C85F4 000C34F4  98 83 00 FC */	stb r4, 0xfc(r3)
/* 800C85F8 000C34F8  98 03 00 FD */	stb r0, 0xfd(r3)
/* 800C85FC 000C34FC  38 60 FF FF */	li r3, -1
/* 800C8600 000C3500  48 00 00 84 */	b lbl_800C8684
lbl_800C8604:
/* 800C8604 000C3504  FC 05 18 40 */	fcmpo cr0, f5, f3
/* 800C8608 000C3508  4C 40 13 82 */	cror 2, 0, 2
/* 800C860C 000C350C  41 82 00 28 */	beq lbl_800C8634
/* 800C8610 000C3510  FC 05 10 40 */	fcmpo cr0, f5, f2
/* 800C8614 000C3514  4C 41 13 82 */	cror 2, 1, 2
/* 800C8618 000C3518  41 82 00 1C */	beq lbl_800C8634
/* 800C861C 000C351C  FC 04 08 40 */	fcmpo cr0, f4, f1
/* 800C8620 000C3520  4C 40 13 82 */	cror 2, 0, 2
/* 800C8624 000C3524  41 82 00 10 */	beq lbl_800C8634
/* 800C8628 000C3528  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 800C862C 000C352C  4C 41 13 82 */	cror 2, 1, 2
/* 800C8630 000C3530  40 82 00 44 */	bne lbl_800C8674
lbl_800C8634:
/* 800C8634 000C3534  80 A8 00 00 */	lwz r5, 0(r8)
/* 800C8638 000C3538  38 80 00 00 */	li r4, 0
/* 800C863C 000C353C  80 E8 00 04 */	lwz r7, 4(r8)
/* 800C8640 000C3540  38 00 FF FF */	li r0, -1
/* 800C8644 000C3544  80 C1 00 08 */	lwz r6, 8(r1)
/* 800C8648 000C3548  90 A3 00 F4 */	stw r5, 0xf4(r3)
/* 800C864C 000C354C  80 A1 00 0C */	lwz r5, 0xc(r1)
/* 800C8650 000C3550  90 E3 00 F8 */	stw r7, 0xf8(r3)
/* 800C8654 000C3554  80 E8 00 08 */	lwz r7, 8(r8)
/* 800C8658 000C3558  90 E3 00 FC */	stw r7, 0xfc(r3)
/* 800C865C 000C355C  90 C3 01 00 */	stw r6, 0x100(r3)
/* 800C8660 000C3560  90 A3 01 04 */	stw r5, 0x104(r3)
/* 800C8664 000C3564  98 83 01 08 */	stb r4, 0x108(r3)
/* 800C8668 000C3568  98 03 01 09 */	stb r0, 0x109(r3)
/* 800C866C 000C356C  38 60 FF FF */	li r3, -1
/* 800C8670 000C3570  48 00 00 14 */	b lbl_800C8684
lbl_800C8674:
/* 800C8674 000C3574  39 08 00 0C */	addi r8, r8, 0xc
/* 800C8678 000C3578  7C 08 00 40 */	cmplw r8, r0
/* 800C867C 000C357C  41 80 FE 9C */	blt lbl_800C8518
/* 800C8680 000C3580  38 60 00 00 */	li r3, 0
lbl_800C8684:
/* 800C8684 000C3584  38 21 00 20 */	addi r1, r1, 0x20
/* 800C8688 000C3588  4E 80 00 20 */	blr 

.global select_1obj_continue
select_1obj_continue:
/* 800C868C 000C358C  C0 0D 82 28 */	lfs f0, kp_err_near_pos-_SDA_BASE_(r13)
/* 800C8690 000C3590  38 C3 00 F4 */	addi r6, r3, 0xf4
/* 800C8694 000C3594  38 03 01 0C */	addi r0, r3, 0x10c
/* 800C8698 000C3598  EC 80 00 32 */	fmuls f4, f0, f0
lbl_800C869C:
/* 800C869C 000C359C  88 86 00 08 */	lbz r4, 8(r6)
/* 800C86A0 000C35A0  7C 84 07 75 */	extsb. r4, r4
/* 800C86A4 000C35A4  40 82 00 68 */	bne lbl_800C870C
/* 800C86A8 000C35A8  88 86 00 09 */	lbz r4, 9(r6)
/* 800C86AC 000C35AC  7C 84 07 75 */	extsb. r4, r4
/* 800C86B0 000C35B0  40 82 00 5C */	bne lbl_800C870C
/* 800C86B4 000C35B4  38 E3 00 C4 */	addi r7, r3, 0xc4
/* 800C86B8 000C35B8  38 83 00 F4 */	addi r4, r3, 0xf4
lbl_800C86BC:
/* 800C86BC 000C35BC  88 A7 00 08 */	lbz r5, 8(r7)
/* 800C86C0 000C35C0  7C A5 07 75 */	extsb. r5, r5
/* 800C86C4 000C35C4  40 82 00 3C */	bne lbl_800C8700
/* 800C86C8 000C35C8  C0 66 00 00 */	lfs f3, 0(r6)
/* 800C86CC 000C35CC  C0 47 00 00 */	lfs f2, 0(r7)
/* 800C86D0 000C35D0  C0 26 00 04 */	lfs f1, 4(r6)
/* 800C86D4 000C35D4  C0 07 00 04 */	lfs f0, 4(r7)
/* 800C86D8 000C35D8  EC 43 10 28 */	fsubs f2, f3, f2
/* 800C86DC 000C35DC  EC 01 00 28 */	fsubs f0, f1, f0
/* 800C86E0 000C35E0  EC 22 00 B2 */	fmuls f1, f2, f2
/* 800C86E4 000C35E4  EC 00 00 32 */	fmuls f0, f0, f0
/* 800C86E8 000C35E8  EC 01 00 2A */	fadds f0, f1, f0
/* 800C86EC 000C35EC  FC 00 20 40 */	fcmpo cr0, f0, f4
/* 800C86F0 000C35F0  40 80 00 10 */	bge lbl_800C8700
/* 800C86F4 000C35F4  FC 80 00 90 */	fmr f4, f0
/* 800C86F8 000C35F8  7C C8 33 78 */	mr r8, r6
/* 800C86FC 000C35FC  7C E9 3B 78 */	mr r9, r7
lbl_800C8700:
/* 800C8700 000C3600  38 E7 00 0C */	addi r7, r7, 0xc
/* 800C8704 000C3604  7C 07 20 40 */	cmplw r7, r4
/* 800C8708 000C3608  41 80 FF B4 */	blt lbl_800C86BC
lbl_800C870C:
/* 800C870C 000C360C  38 C6 00 0C */	addi r6, r6, 0xc
/* 800C8710 000C3610  7C 06 00 40 */	cmplw r6, r0
/* 800C8714 000C3614  41 80 FF 88 */	blt lbl_800C869C
/* 800C8718 000C3618  C0 0D 82 28 */	lfs f0, kp_err_near_pos-_SDA_BASE_(r13)
/* 800C871C 000C361C  EC 00 00 32 */	fmuls f0, f0, f0
/* 800C8720 000C3620  FC 04 00 00 */	fcmpu cr0, f4, f0
/* 800C8724 000C3624  40 82 00 0C */	bne lbl_800C8730
/* 800C8728 000C3628  38 60 00 00 */	li r3, 0
/* 800C872C 000C362C  4E 80 00 20 */	blr 
lbl_800C8730:
/* 800C8730 000C3630  80 A9 00 00 */	lwz r5, 0(r9)
/* 800C8734 000C3634  38 03 00 F4 */	addi r0, r3, 0xf4
/* 800C8738 000C3638  80 89 00 04 */	lwz r4, 4(r9)
/* 800C873C 000C363C  7C 08 00 40 */	cmplw r8, r0
/* 800C8740 000C3640  90 A8 00 00 */	stw r5, 0(r8)
/* 800C8744 000C3644  90 88 00 04 */	stw r4, 4(r8)
/* 800C8748 000C3648  80 09 00 08 */	lwz r0, 8(r9)
/* 800C874C 000C364C  90 08 00 08 */	stw r0, 8(r8)
/* 800C8750 000C3650  C0 A3 00 B0 */	lfs f5, 0xb0(r3)
/* 800C8754 000C3654  C0 03 04 B8 */	lfs f0, 0x4b8(r3)
/* 800C8758 000C3658  C0 63 00 B4 */	lfs f3, 0xb4(r3)
/* 800C875C 000C365C  C0 23 04 BC */	lfs f1, 0x4bc(r3)
/* 800C8760 000C3660  EC 85 00 32 */	fmuls f4, f5, f0
/* 800C8764 000C3664  EC 43 00 32 */	fmuls f2, f3, f0
/* 800C8768 000C3668  C0 03 04 90 */	lfs f0, 0x490(r3)
/* 800C876C 000C366C  EC 63 00 72 */	fmuls f3, f3, f1
/* 800C8770 000C3670  EC 25 00 72 */	fmuls f1, f5, f1
/* 800C8774 000C3674  EC 64 18 2A */	fadds f3, f4, f3
/* 800C8778 000C3678  EC 22 08 28 */	fsubs f1, f2, f1
/* 800C877C 000C367C  EC 40 00 F2 */	fmuls f2, f0, f3
/* 800C8780 000C3680  D0 63 04 94 */	stfs f3, 0x494(r3)
/* 800C8784 000C3684  EC 60 00 72 */	fmuls f3, f0, f1
/* 800C8788 000C3688  D0 23 04 98 */	stfs f1, 0x498(r3)
/* 800C878C 000C368C  40 82 00 30 */	bne lbl_800C87BC
/* 800C8790 000C3690  C0 08 00 00 */	lfs f0, 0(r8)
/* 800C8794 000C3694  38 80 00 00 */	li r4, 0
/* 800C8798 000C3698  38 00 FF FF */	li r0, -1
/* 800C879C 000C369C  EC 00 10 2A */	fadds f0, f0, f2
/* 800C87A0 000C36A0  D0 03 01 00 */	stfs f0, 0x100(r3)
/* 800C87A4 000C36A4  C0 08 00 04 */	lfs f0, 4(r8)
/* 800C87A8 000C36A8  EC 00 18 2A */	fadds f0, f0, f3
/* 800C87AC 000C36AC  98 83 01 08 */	stb r4, 0x108(r3)
/* 800C87B0 000C36B0  98 03 01 09 */	stb r0, 0x109(r3)
/* 800C87B4 000C36B4  D0 03 01 04 */	stfs f0, 0x104(r3)
/* 800C87B8 000C36B8  48 00 00 2C */	b lbl_800C87E4
lbl_800C87BC:
/* 800C87BC 000C36BC  C0 08 00 00 */	lfs f0, 0(r8)
/* 800C87C0 000C36C0  38 80 00 00 */	li r4, 0
/* 800C87C4 000C36C4  38 00 FF FF */	li r0, -1
/* 800C87C8 000C36C8  EC 00 10 28 */	fsubs f0, f0, f2
/* 800C87CC 000C36CC  D0 03 00 F4 */	stfs f0, 0xf4(r3)
/* 800C87D0 000C36D0  C0 08 00 04 */	lfs f0, 4(r8)
/* 800C87D4 000C36D4  EC 00 18 28 */	fsubs f0, f0, f3
/* 800C87D8 000C36D8  98 83 00 FC */	stb r4, 0xfc(r3)
/* 800C87DC 000C36DC  98 03 00 FD */	stb r0, 0xfd(r3)
/* 800C87E0 000C36E0  D0 03 00 F8 */	stfs f0, 0xf8(r3)
lbl_800C87E4:
/* 800C87E4 000C36E4  88 03 00 5E */	lbz r0, 0x5e(r3)
/* 800C87E8 000C36E8  7C 00 07 75 */	extsb. r0, r0
/* 800C87EC 000C36EC  40 80 00 0C */	bge lbl_800C87F8
/* 800C87F0 000C36F0  38 60 FF FF */	li r3, -1
/* 800C87F4 000C36F4  4E 80 00 20 */	blr 
lbl_800C87F8:
/* 800C87F8 000C36F8  38 60 00 01 */	li r3, 1
/* 800C87FC 000C36FC  4E 80 00 20 */	blr 

.global calc_dpd_variable
calc_dpd_variable:
/* 800C8800 000C3700  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800C8804 000C3704  7C 08 02 A6 */	mflr r0
/* 800C8808 000C3708  90 01 00 24 */	stw r0, 0x24(r1)
/* 800C880C 000C370C  7C 80 07 75 */	extsb. r0, r4
/* 800C8810 000C3710  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800C8814 000C3714  7C 9F 23 78 */	mr r31, r4
/* 800C8818 000C3718  93 C1 00 18 */	stw r30, 0x18(r1)
/* 800C881C 000C371C  7C 7E 1B 78 */	mr r30, r3
/* 800C8820 000C3720  40 82 00 10 */	bne lbl_800C8830
/* 800C8824 000C3724  38 00 00 00 */	li r0, 0
/* 800C8828 000C3728  98 03 00 5E */	stb r0, 0x5e(r3)
/* 800C882C 000C372C  48 00 03 A4 */	b lbl_800C8BD0
lbl_800C8830:
/* 800C8830 000C3730  C0 83 00 B0 */	lfs f4, 0xb0(r3)
/* 800C8834 000C3734  C0 23 04 94 */	lfs f1, 0x494(r3)
/* 800C8838 000C3738  C0 43 00 B4 */	lfs f2, 0xb4(r3)
/* 800C883C 000C373C  EC 64 00 72 */	fmuls f3, f4, f1
/* 800C8840 000C3740  C0 03 04 98 */	lfs f0, 0x498(r3)
/* 800C8844 000C3744  EC 22 00 72 */	fmuls f1, f2, f1
/* 800C8848 000C3748  88 03 00 5E */	lbz r0, 0x5e(r3)
/* 800C884C 000C374C  EC 42 00 32 */	fmuls f2, f2, f0
/* 800C8850 000C3750  EC 04 00 32 */	fmuls f0, f4, f0
/* 800C8854 000C3754  7C 00 07 75 */	extsb. r0, r0
/* 800C8858 000C3758  EC 63 10 2A */	fadds f3, f3, f2
/* 800C885C 000C375C  EC 41 00 28 */	fsubs f2, f1, f0
/* 800C8860 000C3760  D0 61 00 10 */	stfs f3, 0x10(r1)
/* 800C8864 000C3764  D0 41 00 14 */	stfs f2, 0x14(r1)
/* 800C8868 000C3768  40 82 00 30 */	bne lbl_800C8898
/* 800C886C 000C376C  80 81 00 10 */	lwz r4, 0x10(r1)
/* 800C8870 000C3770  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800C8874 000C3774  90 83 00 34 */	stw r4, 0x34(r3)
/* 800C8878 000C3778  C0 02 95 A8 */	lfs f0, lbl_804C0FC8-_SDA2_BASE_(r2)
/* 800C887C 000C377C  90 03 00 38 */	stw r0, 0x38(r3)
/* 800C8880 000C3780  80 8D 9A 38 */	lwz r4, Vec2_0-_SDA_BASE_(r13)
/* 800C8884 000C3784  80 0D 9A 3C */	lwz r0, (Vec2_0 + 4)-_SDA_BASE_(r13)
/* 800C8888 000C3788  90 83 00 3C */	stw r4, 0x3c(r3)
/* 800C888C 000C378C  90 03 00 40 */	stw r0, 0x40(r3)
/* 800C8890 000C3790  D0 03 00 44 */	stfs f0, 0x44(r3)
/* 800C8894 000C3794  48 00 00 F0 */	b lbl_800C8984
lbl_800C8898:
/* 800C8898 000C3798  C0 23 00 34 */	lfs f1, 0x34(r3)
/* 800C889C 000C379C  C0 03 00 38 */	lfs f0, 0x38(r3)
/* 800C88A0 000C37A0  EC 63 08 28 */	fsubs f3, f3, f1
/* 800C88A4 000C37A4  EC 42 00 28 */	fsubs f2, f2, f0
/* 800C88A8 000C37A8  EC 23 00 F2 */	fmuls f1, f3, f3
/* 800C88AC 000C37AC  D0 61 00 08 */	stfs f3, 8(r1)
/* 800C88B0 000C37B0  EC 02 00 B2 */	fmuls f0, f2, f2
/* 800C88B4 000C37B4  D0 41 00 0C */	stfs f2, 0xc(r1)
/* 800C88B8 000C37B8  EC 21 00 2A */	fadds f1, f1, f0
/* 800C88BC 000C37BC  4B FF 88 15 */	bl sqrt
/* 800C88C0 000C37C0  FC 20 08 18 */	frsp f1, f1
/* 800C88C4 000C37C4  C0 1E 00 8C */	lfs f0, 0x8c(r30)
/* 800C88C8 000C37C8  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800C88CC 000C37CC  4C 41 13 82 */	cror 2, 1, 2
/* 800C88D0 000C37D0  40 82 00 0C */	bne lbl_800C88DC
/* 800C88D4 000C37D4  C0 82 95 BC */	lfs f4, lbl_804C0FDC-_SDA2_BASE_(r2)
/* 800C88D8 000C37D8  48 00 00 10 */	b lbl_800C88E8
lbl_800C88DC:
/* 800C88DC 000C37DC  EC 81 00 24 */	fdivs f4, f1, f0
/* 800C88E0 000C37E0  EC 84 01 32 */	fmuls f4, f4, f4
/* 800C88E4 000C37E4  EC 84 01 32 */	fmuls f4, f4, f4
lbl_800C88E8:
/* 800C88E8 000C37E8  C0 1E 00 90 */	lfs f0, 0x90(r30)
/* 800C88EC 000C37EC  C0 61 00 08 */	lfs f3, 8(r1)
/* 800C88F0 000C37F0  EC 84 00 32 */	fmuls f4, f4, f0
/* 800C88F4 000C37F4  C0 21 00 0C */	lfs f1, 0xc(r1)
/* 800C88F8 000C37F8  C0 5E 00 34 */	lfs f2, 0x34(r30)
/* 800C88FC 000C37FC  C0 1E 00 38 */	lfs f0, 0x38(r30)
/* 800C8900 000C3800  EC 64 00 F2 */	fmuls f3, f4, f3
/* 800C8904 000C3804  EC 24 00 72 */	fmuls f1, f4, f1
/* 800C8908 000C3808  EC 62 18 2A */	fadds f3, f2, f3
/* 800C890C 000C380C  EC 40 08 2A */	fadds f2, f0, f1
/* 800C8910 000C3810  EC 23 00 F2 */	fmuls f1, f3, f3
/* 800C8914 000C3814  D0 61 00 08 */	stfs f3, 8(r1)
/* 800C8918 000C3818  EC 02 00 B2 */	fmuls f0, f2, f2
/* 800C891C 000C381C  D0 41 00 0C */	stfs f2, 0xc(r1)
/* 800C8920 000C3820  EC 21 00 2A */	fadds f1, f1, f0
/* 800C8924 000C3824  4B FF 87 AD */	bl sqrt
/* 800C8928 000C3828  FC 80 08 18 */	frsp f4, f1
/* 800C892C 000C382C  C0 01 00 08 */	lfs f0, 8(r1)
/* 800C8930 000C3830  C0 41 00 0C */	lfs f2, 0xc(r1)
/* 800C8934 000C3834  C0 3E 00 34 */	lfs f1, 0x34(r30)
/* 800C8938 000C3838  EC 60 20 24 */	fdivs f3, f0, f4
/* 800C893C 000C383C  C0 1E 00 38 */	lfs f0, 0x38(r30)
/* 800C8940 000C3840  EC 42 20 24 */	fdivs f2, f2, f4
/* 800C8944 000C3844  D0 61 00 08 */	stfs f3, 8(r1)
/* 800C8948 000C3848  EC 63 08 28 */	fsubs f3, f3, f1
/* 800C894C 000C384C  D0 41 00 0C */	stfs f2, 0xc(r1)
/* 800C8950 000C3850  EC 42 00 28 */	fsubs f2, f2, f0
/* 800C8954 000C3854  EC 23 00 F2 */	fmuls f1, f3, f3
/* 800C8958 000C3858  D0 7E 00 3C */	stfs f3, 0x3c(r30)
/* 800C895C 000C385C  EC 02 00 B2 */	fmuls f0, f2, f2
/* 800C8960 000C3860  D0 5E 00 40 */	stfs f2, 0x40(r30)
/* 800C8964 000C3864  EC 21 00 2A */	fadds f1, f1, f0
/* 800C8968 000C3868  4B FF 87 69 */	bl sqrt
/* 800C896C 000C386C  FC 00 08 18 */	frsp f0, f1
/* 800C8970 000C3870  80 61 00 08 */	lwz r3, 8(r1)
/* 800C8974 000C3874  80 01 00 0C */	lwz r0, 0xc(r1)
/* 800C8978 000C3878  90 7E 00 34 */	stw r3, 0x34(r30)
/* 800C897C 000C387C  D0 1E 00 44 */	stfs f0, 0x44(r30)
/* 800C8980 000C3880  90 1E 00 38 */	stw r0, 0x38(r30)
lbl_800C8984:
/* 800C8984 000C3884  C0 3E 05 10 */	lfs f1, 0x510(r30)
/* 800C8988 000C3888  C0 1E 04 90 */	lfs f0, 0x490(r30)
/* 800C898C 000C388C  88 1E 00 5E */	lbz r0, 0x5e(r30)
/* 800C8990 000C3890  EC 41 00 24 */	fdivs f2, f1, f0
/* 800C8994 000C3894  7C 00 07 75 */	extsb. r0, r0
/* 800C8998 000C3898  40 82 00 18 */	bne lbl_800C89B0
/* 800C899C 000C389C  C0 02 95 A8 */	lfs f0, lbl_804C0FC8-_SDA2_BASE_(r2)
/* 800C89A0 000C38A0  D0 5E 00 48 */	stfs f2, 0x48(r30)
/* 800C89A4 000C38A4  D0 1E 00 4C */	stfs f0, 0x4c(r30)
/* 800C89A8 000C38A8  D0 1E 00 50 */	stfs f0, 0x50(r30)
/* 800C89AC 000C38AC  48 00 00 84 */	b lbl_800C8A30
lbl_800C89B0:
/* 800C89B0 000C38B0  C0 3E 00 48 */	lfs f1, 0x48(r30)
/* 800C89B4 000C38B4  C0 02 95 A8 */	lfs f0, lbl_804C0FC8-_SDA2_BASE_(r2)
/* 800C89B8 000C38B8  EC 62 08 28 */	fsubs f3, f2, f1
/* 800C89BC 000C38BC  FC 03 00 40 */	fcmpo cr0, f3, f0
/* 800C89C0 000C38C0  40 80 00 0C */	bge lbl_800C89CC
/* 800C89C4 000C38C4  FC 40 18 50 */	fneg f2, f3
/* 800C89C8 000C38C8  48 00 00 08 */	b lbl_800C89D0
lbl_800C89CC:
/* 800C89CC 000C38CC  FC 40 18 90 */	fmr f2, f3
lbl_800C89D0:
/* 800C89D0 000C38D0  C0 1E 00 94 */	lfs f0, 0x94(r30)
/* 800C89D4 000C38D4  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 800C89D8 000C38D8  4C 41 13 82 */	cror 2, 1, 2
/* 800C89DC 000C38DC  40 82 00 0C */	bne lbl_800C89E8
/* 800C89E0 000C38E0  C0 42 95 BC */	lfs f2, lbl_804C0FDC-_SDA2_BASE_(r2)
/* 800C89E4 000C38E4  48 00 00 10 */	b lbl_800C89F4
lbl_800C89E8:
/* 800C89E8 000C38E8  EC 42 00 24 */	fdivs f2, f2, f0
/* 800C89EC 000C38EC  EC 42 00 B2 */	fmuls f2, f2, f2
/* 800C89F0 000C38F0  EC 42 00 B2 */	fmuls f2, f2, f2
lbl_800C89F4:
/* 800C89F4 000C38F4  C0 3E 00 98 */	lfs f1, 0x98(r30)
/* 800C89F8 000C38F8  C0 02 95 A8 */	lfs f0, lbl_804C0FC8-_SDA2_BASE_(r2)
/* 800C89FC 000C38FC  EC 42 00 72 */	fmuls f2, f2, f1
/* 800C8A00 000C3900  EC 22 00 F2 */	fmuls f1, f2, f3
/* 800C8A04 000C3904  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800C8A08 000C3908  D0 3E 00 4C */	stfs f1, 0x4c(r30)
/* 800C8A0C 000C390C  40 80 00 10 */	bge lbl_800C8A1C
/* 800C8A10 000C3910  FC 00 08 50 */	fneg f0, f1
/* 800C8A14 000C3914  D0 1E 00 50 */	stfs f0, 0x50(r30)
/* 800C8A18 000C3918  48 00 00 08 */	b lbl_800C8A20
lbl_800C8A1C:
/* 800C8A1C 000C391C  D0 3E 00 50 */	stfs f1, 0x50(r30)
lbl_800C8A20:
/* 800C8A20 000C3920  C0 3E 00 48 */	lfs f1, 0x48(r30)
/* 800C8A24 000C3924  C0 1E 00 4C */	lfs f0, 0x4c(r30)
/* 800C8A28 000C3928  EC 01 00 2A */	fadds f0, f1, f0
/* 800C8A2C 000C392C  D0 1E 00 48 */	stfs f0, 0x48(r30)
lbl_800C8A30:
/* 800C8A30 000C3930  C0 5E 04 98 */	lfs f2, 0x498(r30)
/* 800C8A34 000C3934  C0 1E 00 B4 */	lfs f0, 0xb4(r30)
/* 800C8A38 000C3938  FC 20 10 50 */	fneg f1, f2
/* 800C8A3C 000C393C  88 1E 00 5E */	lbz r0, 0x5e(r30)
/* 800C8A40 000C3940  C0 BE 04 94 */	lfs f5, 0x494(r30)
/* 800C8A44 000C3944  EC 62 00 32 */	fmuls f3, f2, f0
/* 800C8A48 000C3948  C0 9E 00 B0 */	lfs f4, 0xb0(r30)
/* 800C8A4C 000C394C  7C 00 07 75 */	extsb. r0, r0
/* 800C8A50 000C3950  EC 05 00 32 */	fmuls f0, f5, f0
/* 800C8A54 000C3954  C0 FE 00 F4 */	lfs f7, 0xf4(r30)
/* 800C8A58 000C3958  EC 41 01 32 */	fmuls f2, f1, f4
/* 800C8A5C 000C395C  C0 DE 01 00 */	lfs f6, 0x100(r30)
/* 800C8A60 000C3960  EC A5 01 32 */	fmuls f5, f5, f4
/* 800C8A64 000C3964  C0 9E 00 F8 */	lfs f4, 0xf8(r30)
/* 800C8A68 000C3968  C0 3E 01 04 */	lfs f1, 0x104(r30)
/* 800C8A6C 000C396C  EC E7 30 2A */	fadds f7, f7, f6
/* 800C8A70 000C3970  C1 02 95 AC */	lfs f8, lbl_804C0FCC-_SDA2_BASE_(r2)
/* 800C8A74 000C3974  EC 65 18 2A */	fadds f3, f5, f3
/* 800C8A78 000C3978  EC C4 08 2A */	fadds f6, f4, f1
/* 800C8A7C 000C397C  C0 9E 00 AC */	lfs f4, 0xac(r30)
/* 800C8A80 000C3980  EC E8 01 F2 */	fmuls f7, f8, f7
/* 800C8A84 000C3984  EC 42 00 2A */	fadds f2, f2, f0
/* 800C8A88 000C3988  C0 3E 00 A8 */	lfs f1, 0xa8(r30)
/* 800C8A8C 000C398C  EC A8 01 B2 */	fmuls f5, f8, f6
/* 800C8A90 000C3990  ED 23 01 F2 */	fmuls f9, f3, f7
/* 800C8A94 000C3994  C0 DE 00 B8 */	lfs f6, 0xb8(r30)
/* 800C8A98 000C3998  EC E2 01 F2 */	fmuls f7, f2, f7
/* 800C8A9C 000C399C  EC 03 01 72 */	fmuls f0, f3, f5
/* 800C8AA0 000C39A0  C0 7E 00 BC */	lfs f3, 0xbc(r30)
/* 800C8AA4 000C39A4  ED 02 01 72 */	fmuls f8, f2, f5
/* 800C8AA8 000C39A8  C0 BE 00 C0 */	lfs f5, 0xc0(r30)
/* 800C8AAC 000C39AC  FC 40 20 50 */	fneg f2, f4
/* 800C8AB0 000C39B0  EC E7 00 2A */	fadds f7, f7, f0
/* 800C8AB4 000C39B4  ED 09 40 28 */	fsubs f8, f9, f8
/* 800C8AB8 000C39B8  FC 00 08 50 */	fneg f0, f1
/* 800C8ABC 000C39BC  EC 63 38 28 */	fsubs f3, f3, f7
/* 800C8AC0 000C39C0  EC C6 40 28 */	fsubs f6, f6, f8
/* 800C8AC4 000C39C4  EC C5 01 B2 */	fmuls f6, f5, f6
/* 800C8AC8 000C39C8  EC A5 00 F2 */	fmuls f5, f5, f3
/* 800C8ACC 000C39CC  EC 62 01 B2 */	fmuls f3, f2, f6
/* 800C8AD0 000C39D0  D0 C1 00 08 */	stfs f6, 8(r1)
/* 800C8AD4 000C39D4  EC 41 01 72 */	fmuls f2, f1, f5
/* 800C8AD8 000C39D8  EC 20 01 B2 */	fmuls f1, f0, f6
/* 800C8ADC 000C39DC  D0 A1 00 0C */	stfs f5, 0xc(r1)
/* 800C8AE0 000C39E0  EC 04 01 72 */	fmuls f0, f4, f5
/* 800C8AE4 000C39E4  EC 63 10 2A */	fadds f3, f3, f2
/* 800C8AE8 000C39E8  EC 41 00 28 */	fsubs f2, f1, f0
/* 800C8AEC 000C39EC  D0 61 00 10 */	stfs f3, 0x10(r1)
/* 800C8AF0 000C39F0  D0 41 00 14 */	stfs f2, 0x14(r1)
/* 800C8AF4 000C39F4  40 82 00 30 */	bne lbl_800C8B24
/* 800C8AF8 000C39F8  80 61 00 10 */	lwz r3, 0x10(r1)
/* 800C8AFC 000C39FC  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800C8B00 000C3A00  90 7E 00 20 */	stw r3, 0x20(r30)
/* 800C8B04 000C3A04  C0 02 95 A8 */	lfs f0, lbl_804C0FC8-_SDA2_BASE_(r2)
/* 800C8B08 000C3A08  90 1E 00 24 */	stw r0, 0x24(r30)
/* 800C8B0C 000C3A0C  80 6D 9A 38 */	lwz r3, Vec2_0-_SDA_BASE_(r13)
/* 800C8B10 000C3A10  80 0D 9A 3C */	lwz r0, (Vec2_0 + 4)-_SDA_BASE_(r13)
/* 800C8B14 000C3A14  90 7E 00 28 */	stw r3, 0x28(r30)
/* 800C8B18 000C3A18  90 1E 00 2C */	stw r0, 0x2c(r30)
/* 800C8B1C 000C3A1C  D0 1E 00 30 */	stfs f0, 0x30(r30)
/* 800C8B20 000C3A20  48 00 00 AC */	b lbl_800C8BCC
lbl_800C8B24:
/* 800C8B24 000C3A24  C0 3E 00 20 */	lfs f1, 0x20(r30)
/* 800C8B28 000C3A28  C0 1E 00 24 */	lfs f0, 0x24(r30)
/* 800C8B2C 000C3A2C  EC 63 08 28 */	fsubs f3, f3, f1
/* 800C8B30 000C3A30  EC 42 00 28 */	fsubs f2, f2, f0
/* 800C8B34 000C3A34  EC 23 00 F2 */	fmuls f1, f3, f3
/* 800C8B38 000C3A38  D0 61 00 08 */	stfs f3, 8(r1)
/* 800C8B3C 000C3A3C  EC 02 00 B2 */	fmuls f0, f2, f2
/* 800C8B40 000C3A40  D0 41 00 0C */	stfs f2, 0xc(r1)
/* 800C8B44 000C3A44  EC 21 00 2A */	fadds f1, f1, f0
/* 800C8B48 000C3A48  4B FF 85 89 */	bl sqrt
/* 800C8B4C 000C3A4C  FC 20 08 18 */	frsp f1, f1
/* 800C8B50 000C3A50  C0 1E 00 84 */	lfs f0, 0x84(r30)
/* 800C8B54 000C3A54  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800C8B58 000C3A58  4C 41 13 82 */	cror 2, 1, 2
/* 800C8B5C 000C3A5C  40 82 00 0C */	bne lbl_800C8B68
/* 800C8B60 000C3A60  C0 42 95 BC */	lfs f2, lbl_804C0FDC-_SDA2_BASE_(r2)
/* 800C8B64 000C3A64  48 00 00 10 */	b lbl_800C8B74
lbl_800C8B68:
/* 800C8B68 000C3A68  EC 41 00 24 */	fdivs f2, f1, f0
/* 800C8B6C 000C3A6C  EC 42 00 B2 */	fmuls f2, f2, f2
/* 800C8B70 000C3A70  EC 42 00 B2 */	fmuls f2, f2, f2
lbl_800C8B74:
/* 800C8B74 000C3A74  C0 1E 00 88 */	lfs f0, 0x88(r30)
/* 800C8B78 000C3A78  C0 21 00 08 */	lfs f1, 8(r1)
/* 800C8B7C 000C3A7C  EC 42 00 32 */	fmuls f2, f2, f0
/* 800C8B80 000C3A80  C0 01 00 0C */	lfs f0, 0xc(r1)
/* 800C8B84 000C3A84  EC 62 00 72 */	fmuls f3, f2, f1
/* 800C8B88 000C3A88  EC 42 00 32 */	fmuls f2, f2, f0
/* 800C8B8C 000C3A8C  EC 23 00 F2 */	fmuls f1, f3, f3
/* 800C8B90 000C3A90  D0 7E 00 28 */	stfs f3, 0x28(r30)
/* 800C8B94 000C3A94  EC 02 00 B2 */	fmuls f0, f2, f2
/* 800C8B98 000C3A98  D0 5E 00 2C */	stfs f2, 0x2c(r30)
/* 800C8B9C 000C3A9C  EC 21 00 2A */	fadds f1, f1, f0
/* 800C8BA0 000C3AA0  4B FF 85 31 */	bl sqrt
/* 800C8BA4 000C3AA4  FC 80 08 18 */	frsp f4, f1
/* 800C8BA8 000C3AA8  C0 7E 00 20 */	lfs f3, 0x20(r30)
/* 800C8BAC 000C3AAC  C0 5E 00 28 */	lfs f2, 0x28(r30)
/* 800C8BB0 000C3AB0  C0 3E 00 24 */	lfs f1, 0x24(r30)
/* 800C8BB4 000C3AB4  C0 1E 00 2C */	lfs f0, 0x2c(r30)
/* 800C8BB8 000C3AB8  EC 43 10 2A */	fadds f2, f3, f2
/* 800C8BBC 000C3ABC  D0 9E 00 30 */	stfs f4, 0x30(r30)
/* 800C8BC0 000C3AC0  EC 01 00 2A */	fadds f0, f1, f0
/* 800C8BC4 000C3AC4  D0 5E 00 20 */	stfs f2, 0x20(r30)
/* 800C8BC8 000C3AC8  D0 1E 00 24 */	stfs f0, 0x24(r30)
lbl_800C8BCC:
/* 800C8BCC 000C3ACC  9B FE 00 5E */	stb r31, 0x5e(r30)
lbl_800C8BD0:
/* 800C8BD0 000C3AD0  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800C8BD4 000C3AD4  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800C8BD8 000C3AD8  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 800C8BDC 000C3ADC  7C 08 03 A6 */	mtlr r0
/* 800C8BE0 000C3AE0  38 21 00 20 */	addi r1, r1, 0x20
/* 800C8BE4 000C3AE4  4E 80 00 20 */	blr 

.global read_kpad_dpd
read_kpad_dpd:
/* 800C8BE8 000C3AE8  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 800C8BEC 000C3AEC  7C 08 02 A6 */	mflr r0
/* 800C8BF0 000C3AF0  90 01 00 44 */	stw r0, 0x44(r1)
/* 800C8BF4 000C3AF4  DB E1 00 30 */	stfd f31, 0x30(r1)
/* 800C8BF8 000C3AF8  F3 E1 00 38 */	psq_st f31, 56(r1), 0, qr0
/* 800C8BFC 000C3AFC  DB C1 00 20 */	stfd f30, 0x20(r1)
/* 800C8C00 000C3B00  F3 C1 00 28 */	psq_st f30, 40(r1), 0, qr0
/* 800C8C04 000C3B04  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800C8C08 000C3B08  7C 7F 1B 78 */	mr r31, r3
/* 800C8C0C 000C3B0C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 800C8C10 000C3B10  88 04 00 36 */	lbz r0, 0x36(r4)
/* 800C8C14 000C3B14  28 00 00 02 */	cmplwi r0, 2
/* 800C8C18 000C3B18  41 82 00 14 */	beq lbl_800C8C2C
/* 800C8C1C 000C3B1C  28 00 00 05 */	cmplwi r0, 5
/* 800C8C20 000C3B20  41 82 00 0C */	beq lbl_800C8C2C
/* 800C8C24 000C3B24  28 00 00 08 */	cmplwi r0, 8
/* 800C8C28 000C3B28  40 82 00 A4 */	bne lbl_800C8CCC
lbl_800C8C2C:
/* 800C8C2C 000C3B2C  C8 82 95 D8 */	lfd f4, lbl_804C0FF8-_SDA2_BASE_(r2)
/* 800C8C30 000C3B30  39 04 00 20 */	addi r8, r4, 0x20
/* 800C8C34 000C3B34  C0 62 95 E0 */	lfs f3, lbl_804C1000-_SDA2_BASE_(r2)
/* 800C8C38 000C3B38  39 23 00 E8 */	addi r9, r3, 0xe8
/* 800C8C3C 000C3B3C  C0 42 95 E4 */	lfs f2, lbl_804C1004-_SDA2_BASE_(r2)
/* 800C8C40 000C3B40  38 03 00 C4 */	addi r0, r3, 0xc4
/* 800C8C44 000C3B44  C0 22 95 E8 */	lfs f1, lbl_804C1008-_SDA2_BASE_(r2)
/* 800C8C48 000C3B48  38 80 FF FF */	li r4, -1
/* 800C8C4C 000C3B4C  3C E0 43 30 */	lis r7, 0x4330
/* 800C8C50 000C3B50  38 A0 00 00 */	li r5, 0
lbl_800C8C54:
/* 800C8C54 000C3B54  A0 C8 00 04 */	lhz r6, 4(r8)
/* 800C8C58 000C3B58  2C 06 00 00 */	cmpwi r6, 0
/* 800C8C5C 000C3B5C  41 82 00 58 */	beq lbl_800C8CB4
/* 800C8C60 000C3B60  A8 C8 00 00 */	lha r6, 0(r8)
/* 800C8C64 000C3B64  90 E1 00 08 */	stw r7, 8(r1)
/* 800C8C68 000C3B68  6C C6 80 00 */	xoris r6, r6, 0x8000
/* 800C8C6C 000C3B6C  90 C1 00 0C */	stw r6, 0xc(r1)
/* 800C8C70 000C3B70  C8 01 00 08 */	lfd f0, 8(r1)
/* 800C8C74 000C3B74  90 E1 00 10 */	stw r7, 0x10(r1)
/* 800C8C78 000C3B78  EC 00 20 28 */	fsubs f0, f0, f4
/* 800C8C7C 000C3B7C  EC 03 00 32 */	fmuls f0, f3, f0
/* 800C8C80 000C3B80  EC 00 10 28 */	fsubs f0, f0, f2
/* 800C8C84 000C3B84  D0 09 00 00 */	stfs f0, 0(r9)
/* 800C8C88 000C3B88  A8 C8 00 02 */	lha r6, 2(r8)
/* 800C8C8C 000C3B8C  6C C6 80 00 */	xoris r6, r6, 0x8000
/* 800C8C90 000C3B90  90 C1 00 14 */	stw r6, 0x14(r1)
/* 800C8C94 000C3B94  C8 01 00 10 */	lfd f0, 0x10(r1)
/* 800C8C98 000C3B98  EC 00 20 28 */	fsubs f0, f0, f4
/* 800C8C9C 000C3B9C  EC 03 00 32 */	fmuls f0, f3, f0
/* 800C8CA0 000C3BA0  EC 00 08 28 */	fsubs f0, f0, f1
/* 800C8CA4 000C3BA4  D0 09 00 04 */	stfs f0, 4(r9)
/* 800C8CA8 000C3BA8  98 A9 00 08 */	stb r5, 8(r9)
/* 800C8CAC 000C3BAC  98 A9 00 09 */	stb r5, 9(r9)
/* 800C8CB0 000C3BB0  48 00 00 08 */	b lbl_800C8CB8
lbl_800C8CB4:
/* 800C8CB4 000C3BB4  98 89 00 08 */	stb r4, 8(r9)
lbl_800C8CB8:
/* 800C8CB8 000C3BB8  39 29 FF F4 */	addi r9, r9, -12
/* 800C8CBC 000C3BBC  39 08 FF F8 */	addi r8, r8, -8
/* 800C8CC0 000C3BC0  7C 09 00 40 */	cmplw r9, r0
/* 800C8CC4 000C3BC4  40 80 FF 90 */	bge lbl_800C8C54
/* 800C8CC8 000C3BC8  48 00 00 20 */	b lbl_800C8CE8
lbl_800C8CCC:
/* 800C8CCC 000C3BCC  38 A3 00 E8 */	addi r5, r3, 0xe8
/* 800C8CD0 000C3BD0  38 03 00 C4 */	addi r0, r3, 0xc4
/* 800C8CD4 000C3BD4  38 80 FF FF */	li r4, -1
lbl_800C8CD8:
/* 800C8CD8 000C3BD8  98 85 00 08 */	stb r4, 8(r5)
/* 800C8CDC 000C3BDC  38 A5 FF F4 */	addi r5, r5, -12
/* 800C8CE0 000C3BE0  7C 05 00 40 */	cmplw r5, r0
/* 800C8CE4 000C3BE4  40 80 FF F4 */	bge lbl_800C8CD8
lbl_800C8CE8:
/* 800C8CE8 000C3BE8  38 E3 00 E8 */	addi r7, r3, 0xe8
/* 800C8CEC 000C3BEC  38 C3 00 C4 */	addi r6, r3, 0xc4
/* 800C8CF0 000C3BF0  7C E4 3B 78 */	mr r4, r7
lbl_800C8CF4:
/* 800C8CF4 000C3BF4  88 04 00 08 */	lbz r0, 8(r4)
/* 800C8CF8 000C3BF8  7C 00 07 75 */	extsb. r0, r0
/* 800C8CFC 000C3BFC  41 80 00 58 */	blt lbl_800C8D54
/* 800C8D00 000C3C00  C0 24 00 00 */	lfs f1, 0(r4)
/* 800C8D04 000C3C04  C0 03 04 F4 */	lfs f0, 0x4f4(r3)
/* 800C8D08 000C3C08  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800C8D0C 000C3C0C  4C 40 13 82 */	cror 2, 0, 2
/* 800C8D10 000C3C10  41 82 00 38 */	beq lbl_800C8D48
/* 800C8D14 000C3C14  C0 03 04 FC */	lfs f0, 0x4fc(r3)
/* 800C8D18 000C3C18  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800C8D1C 000C3C1C  4C 41 13 82 */	cror 2, 1, 2
/* 800C8D20 000C3C20  41 82 00 28 */	beq lbl_800C8D48
/* 800C8D24 000C3C24  C0 24 00 04 */	lfs f1, 4(r4)
/* 800C8D28 000C3C28  C0 03 04 F8 */	lfs f0, 0x4f8(r3)
/* 800C8D2C 000C3C2C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800C8D30 000C3C30  4C 40 13 82 */	cror 2, 0, 2
/* 800C8D34 000C3C34  41 82 00 14 */	beq lbl_800C8D48
/* 800C8D38 000C3C38  C0 03 05 00 */	lfs f0, 0x500(r3)
/* 800C8D3C 000C3C3C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800C8D40 000C3C40  4C 41 13 82 */	cror 2, 1, 2
/* 800C8D44 000C3C44  40 82 00 10 */	bne lbl_800C8D54
lbl_800C8D48:
/* 800C8D48 000C3C48  88 04 00 08 */	lbz r0, 8(r4)
/* 800C8D4C 000C3C4C  60 00 00 01 */	ori r0, r0, 1
/* 800C8D50 000C3C50  98 04 00 08 */	stb r0, 8(r4)
lbl_800C8D54:
/* 800C8D54 000C3C54  38 84 FF F4 */	addi r4, r4, -12
/* 800C8D58 000C3C58  7C 04 30 40 */	cmplw r4, r6
/* 800C8D5C 000C3C5C  40 80 FF 98 */	bge lbl_800C8CF4
lbl_800C8D60:
/* 800C8D60 000C3C60  88 06 00 08 */	lbz r0, 8(r6)
/* 800C8D64 000C3C64  7C 00 07 75 */	extsb. r0, r0
/* 800C8D68 000C3C68  40 82 00 48 */	bne lbl_800C8DB0
/* 800C8D6C 000C3C6C  38 A6 00 0C */	addi r5, r6, 0xc
lbl_800C8D70:
/* 800C8D70 000C3C70  88 85 00 08 */	lbz r4, 8(r5)
/* 800C8D74 000C3C74  7C 80 07 75 */	extsb. r0, r4
/* 800C8D78 000C3C78  40 82 00 2C */	bne lbl_800C8DA4
/* 800C8D7C 000C3C7C  C0 26 00 00 */	lfs f1, 0(r6)
/* 800C8D80 000C3C80  C0 05 00 00 */	lfs f0, 0(r5)
/* 800C8D84 000C3C84  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 800C8D88 000C3C88  40 82 00 1C */	bne lbl_800C8DA4
/* 800C8D8C 000C3C8C  C0 26 00 04 */	lfs f1, 4(r6)
/* 800C8D90 000C3C90  C0 05 00 04 */	lfs f0, 4(r5)
/* 800C8D94 000C3C94  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 800C8D98 000C3C98  40 82 00 0C */	bne lbl_800C8DA4
/* 800C8D9C 000C3C9C  60 80 00 02 */	ori r0, r4, 2
/* 800C8DA0 000C3CA0  98 05 00 08 */	stb r0, 8(r5)
lbl_800C8DA4:
/* 800C8DA4 000C3CA4  38 A5 00 0C */	addi r5, r5, 0xc
/* 800C8DA8 000C3CA8  7C 05 38 40 */	cmplw r5, r7
/* 800C8DAC 000C3CAC  40 81 FF C4 */	ble lbl_800C8D70
lbl_800C8DB0:
/* 800C8DB0 000C3CB0  38 C6 00 0C */	addi r6, r6, 0xc
/* 800C8DB4 000C3CB4  7C 06 38 40 */	cmplw r6, r7
/* 800C8DB8 000C3CB8  41 80 FF A8 */	blt lbl_800C8D60
/* 800C8DBC 000C3CBC  38 00 00 00 */	li r0, 0
/* 800C8DC0 000C3CC0  38 A3 00 E8 */	addi r5, r3, 0xe8
/* 800C8DC4 000C3CC4  B0 03 01 0C */	sth r0, 0x10c(r3)
/* 800C8DC8 000C3CC8  38 03 00 C4 */	addi r0, r3, 0xc4
lbl_800C8DCC:
/* 800C8DCC 000C3CCC  88 85 00 08 */	lbz r4, 8(r5)
/* 800C8DD0 000C3CD0  7C 84 07 75 */	extsb. r4, r4
/* 800C8DD4 000C3CD4  40 82 00 10 */	bne lbl_800C8DE4
/* 800C8DD8 000C3CD8  A8 83 01 0C */	lha r4, 0x10c(r3)
/* 800C8DDC 000C3CDC  38 84 00 01 */	addi r4, r4, 1
/* 800C8DE0 000C3CE0  B0 83 01 0C */	sth r4, 0x10c(r3)
lbl_800C8DE4:
/* 800C8DE4 000C3CE4  38 A5 FF F4 */	addi r5, r5, -12
/* 800C8DE8 000C3CE8  7C 05 00 40 */	cmplw r5, r0
/* 800C8DEC 000C3CEC  40 80 FF E0 */	bge lbl_800C8DCC
/* 800C8DF0 000C3CF0  C0 23 00 54 */	lfs f1, 0x54(r3)
/* 800C8DF4 000C3CF4  C0 0D 82 24 */	lfs f0, kp_err_up_inpr-_SDA_BASE_(r13)
/* 800C8DF8 000C3CF8  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800C8DFC 000C3CFC  4C 40 13 82 */	cror 2, 0, 2
/* 800C8E00 000C3D00  41 82 00 F4 */	beq lbl_800C8EF4
/* 800C8E04 000C3D04  88 03 00 5E */	lbz r0, 0x5e(r3)
/* 800C8E08 000C3D08  7C 00 07 74 */	extsb r0, r0
/* 800C8E0C 000C3D0C  2C 00 00 02 */	cmpwi r0, 2
/* 800C8E10 000C3D10  41 82 00 0C */	beq lbl_800C8E1C
/* 800C8E14 000C3D14  2C 00 FF FE */	cmpwi r0, -2
/* 800C8E18 000C3D18  40 82 00 48 */	bne lbl_800C8E60
lbl_800C8E1C:
/* 800C8E1C 000C3D1C  A8 03 01 0C */	lha r0, 0x10c(r3)
/* 800C8E20 000C3D20  2C 00 00 02 */	cmpwi r0, 2
/* 800C8E24 000C3D24  41 80 00 18 */	blt lbl_800C8E3C
/* 800C8E28 000C3D28  7F E3 FB 78 */	mr r3, r31
/* 800C8E2C 000C3D2C  4B FF F4 85 */	bl select_2obj_continue
/* 800C8E30 000C3D30  7C 60 07 75 */	extsb. r0, r3
/* 800C8E34 000C3D34  7C 7E 1B 78 */	mr r30, r3
/* 800C8E38 000C3D38  40 82 00 C0 */	bne lbl_800C8EF8
lbl_800C8E3C:
/* 800C8E3C 000C3D3C  A8 1F 01 0C */	lha r0, 0x10c(r31)
/* 800C8E40 000C3D40  2C 00 00 01 */	cmpwi r0, 1
/* 800C8E44 000C3D44  41 80 00 B0 */	blt lbl_800C8EF4
/* 800C8E48 000C3D48  7F E3 FB 78 */	mr r3, r31
/* 800C8E4C 000C3D4C  4B FF F8 41 */	bl select_1obj_continue
/* 800C8E50 000C3D50  7C 60 07 75 */	extsb. r0, r3
/* 800C8E54 000C3D54  7C 7E 1B 78 */	mr r30, r3
/* 800C8E58 000C3D58  40 82 00 A0 */	bne lbl_800C8EF8
/* 800C8E5C 000C3D5C  48 00 00 98 */	b lbl_800C8EF4
lbl_800C8E60:
/* 800C8E60 000C3D60  2C 00 00 01 */	cmpwi r0, 1
/* 800C8E64 000C3D64  41 82 00 0C */	beq lbl_800C8E70
/* 800C8E68 000C3D68  2C 00 FF FF */	cmpwi r0, -1
/* 800C8E6C 000C3D6C  40 82 00 48 */	bne lbl_800C8EB4
lbl_800C8E70:
/* 800C8E70 000C3D70  A8 03 01 0C */	lha r0, 0x10c(r3)
/* 800C8E74 000C3D74  2C 00 00 02 */	cmpwi r0, 2
/* 800C8E78 000C3D78  41 80 00 18 */	blt lbl_800C8E90
/* 800C8E7C 000C3D7C  7F E3 FB 78 */	mr r3, r31
/* 800C8E80 000C3D80  4B FF F2 49 */	bl select_2obj_first
/* 800C8E84 000C3D84  7C 60 07 75 */	extsb. r0, r3
/* 800C8E88 000C3D88  7C 7E 1B 78 */	mr r30, r3
/* 800C8E8C 000C3D8C  40 82 00 6C */	bne lbl_800C8EF8
lbl_800C8E90:
/* 800C8E90 000C3D90  A8 1F 01 0C */	lha r0, 0x10c(r31)
/* 800C8E94 000C3D94  2C 00 00 01 */	cmpwi r0, 1
/* 800C8E98 000C3D98  41 80 00 5C */	blt lbl_800C8EF4
/* 800C8E9C 000C3D9C  7F E3 FB 78 */	mr r3, r31
/* 800C8EA0 000C3DA0  4B FF F7 ED */	bl select_1obj_continue
/* 800C8EA4 000C3DA4  7C 60 07 75 */	extsb. r0, r3
/* 800C8EA8 000C3DA8  7C 7E 1B 78 */	mr r30, r3
/* 800C8EAC 000C3DAC  40 82 00 4C */	bne lbl_800C8EF8
/* 800C8EB0 000C3DB0  48 00 00 44 */	b lbl_800C8EF4
lbl_800C8EB4:
/* 800C8EB4 000C3DB4  A8 03 01 0C */	lha r0, 0x10c(r3)
/* 800C8EB8 000C3DB8  2C 00 00 02 */	cmpwi r0, 2
/* 800C8EBC 000C3DBC  41 80 00 18 */	blt lbl_800C8ED4
/* 800C8EC0 000C3DC0  7F E3 FB 78 */	mr r3, r31
/* 800C8EC4 000C3DC4  4B FF F2 05 */	bl select_2obj_first
/* 800C8EC8 000C3DC8  7C 60 07 75 */	extsb. r0, r3
/* 800C8ECC 000C3DCC  7C 7E 1B 78 */	mr r30, r3
/* 800C8ED0 000C3DD0  40 82 00 28 */	bne lbl_800C8EF8
lbl_800C8ED4:
/* 800C8ED4 000C3DD4  A8 1F 01 0C */	lha r0, 0x10c(r31)
/* 800C8ED8 000C3DD8  2C 00 00 01 */	cmpwi r0, 1
/* 800C8EDC 000C3DDC  40 82 00 18 */	bne lbl_800C8EF4
/* 800C8EE0 000C3DE0  7F E3 FB 78 */	mr r3, r31
/* 800C8EE4 000C3DE4  4B FF F5 F5 */	bl select_1obj_first
/* 800C8EE8 000C3DE8  7C 60 07 75 */	extsb. r0, r3
/* 800C8EEC 000C3DEC  7C 7E 1B 78 */	mr r30, r3
/* 800C8EF0 000C3DF0  40 82 00 08 */	bne lbl_800C8EF8
lbl_800C8EF4:
/* 800C8EF4 000C3DF4  3B C0 00 00 */	li r30, 0
lbl_800C8EF8:
/* 800C8EF8 000C3DF8  7F C0 07 75 */	extsb. r0, r30
/* 800C8EFC 000C3DFC  41 82 01 08 */	beq lbl_800C9004
/* 800C8F00 000C3E00  C0 7F 01 00 */	lfs f3, 0x100(r31)
/* 800C8F04 000C3E04  C0 5F 00 F4 */	lfs f2, 0xf4(r31)
/* 800C8F08 000C3E08  C0 3F 01 04 */	lfs f1, 0x104(r31)
/* 800C8F0C 000C3E0C  C0 1F 00 F8 */	lfs f0, 0xf8(r31)
/* 800C8F10 000C3E10  EF C3 10 28 */	fsubs f30, f3, f2
/* 800C8F14 000C3E14  EF E1 00 28 */	fsubs f31, f1, f0
/* 800C8F18 000C3E18  EC 3E 07 B2 */	fmuls f1, f30, f30
/* 800C8F1C 000C3E1C  EC 1F 07 F2 */	fmuls f0, f31, f31
/* 800C8F20 000C3E20  EC 21 00 2A */	fadds f1, f1, f0
/* 800C8F24 000C3E24  4B FF 81 AD */	bl sqrt
/* 800C8F28 000C3E28  FC 60 08 18 */	frsp f3, f1
/* 800C8F2C 000C3E2C  C0 02 95 BC */	lfs f0, lbl_804C0FDC-_SDA2_BASE_(r2)
/* 800C8F30 000C3E30  A0 1F 04 C8 */	lhz r0, 0x4c8(r31)
/* 800C8F34 000C3E34  C0 9F 00 B0 */	lfs f4, 0xb0(r31)
/* 800C8F38 000C3E38  EC 40 18 24 */	fdivs f2, f0, f3
/* 800C8F3C 000C3E3C  C0 3F 05 10 */	lfs f1, 0x510(r31)
/* 800C8F40 000C3E40  C0 1F 00 B4 */	lfs f0, 0xb4(r31)
/* 800C8F44 000C3E44  2C 00 00 00 */	cmpwi r0, 0
/* 800C8F48 000C3E48  D0 7F 04 90 */	stfs f3, 0x490(r31)
/* 800C8F4C 000C3E4C  EF DE 00 B2 */	fmuls f30, f30, f2
/* 800C8F50 000C3E50  EF FF 00 B2 */	fmuls f31, f31, f2
/* 800C8F54 000C3E54  EC A1 00 B2 */	fmuls f5, f1, f2
/* 800C8F58 000C3E58  EC 64 07 B2 */	fmuls f3, f4, f30
/* 800C8F5C 000C3E5C  D3 DF 04 94 */	stfs f30, 0x494(r31)
/* 800C8F60 000C3E60  EC 40 07 F2 */	fmuls f2, f0, f31
/* 800C8F64 000C3E64  EC 20 07 B2 */	fmuls f1, f0, f30
/* 800C8F68 000C3E68  D0 BF 04 9C */	stfs f5, 0x49c(r31)
/* 800C8F6C 000C3E6C  EC 04 07 F2 */	fmuls f0, f4, f31
/* 800C8F70 000C3E70  EC 43 10 2A */	fadds f2, f3, f2
/* 800C8F74 000C3E74  D3 FF 04 98 */	stfs f31, 0x498(r31)
/* 800C8F78 000C3E78  EC 61 00 28 */	fsubs f3, f1, f0
/* 800C8F7C 000C3E7C  D0 5F 04 B0 */	stfs f2, 0x4b0(r31)
/* 800C8F80 000C3E80  D0 7F 04 B4 */	stfs f3, 0x4b4(r31)
/* 800C8F84 000C3E84  40 82 00 38 */	bne lbl_800C8FBC
/* 800C8F88 000C3E88  C0 1F 04 B8 */	lfs f0, 0x4b8(r31)
/* 800C8F8C 000C3E8C  C0 3F 04 BC */	lfs f1, 0x4bc(r31)
/* 800C8F90 000C3E90  EC 42 00 32 */	fmuls f2, f2, f0
/* 800C8F94 000C3E94  C0 0D 82 20 */	lfs f0, kp_err_acc_inpr-_SDA_BASE_(r13)
/* 800C8F98 000C3E98  EC 23 00 72 */	fmuls f1, f3, f1
/* 800C8F9C 000C3E9C  EC 22 08 2A */	fadds f1, f2, f1
/* 800C8FA0 000C3EA0  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800C8FA4 000C3EA4  4C 40 13 82 */	cror 2, 0, 2
/* 800C8FA8 000C3EA8  40 82 00 14 */	bne lbl_800C8FBC
/* 800C8FAC 000C3EAC  38 00 00 01 */	li r0, 1
/* 800C8FB0 000C3EB0  3B C0 00 00 */	li r30, 0
/* 800C8FB4 000C3EB4  98 1F 01 08 */	stb r0, 0x108(r31)
/* 800C8FB8 000C3EB8  98 1F 00 FC */	stb r0, 0xfc(r31)
lbl_800C8FBC:
/* 800C8FBC 000C3EBC  88 1F 00 5E */	lbz r0, 0x5e(r31)
/* 800C8FC0 000C3EC0  2C 00 00 02 */	cmpwi r0, 2
/* 800C8FC4 000C3EC4  40 82 00 34 */	bne lbl_800C8FF8
/* 800C8FC8 000C3EC8  7F C0 07 74 */	extsb r0, r30
/* 800C8FCC 000C3ECC  2C 00 00 02 */	cmpwi r0, 2
/* 800C8FD0 000C3ED0  40 82 00 28 */	bne lbl_800C8FF8
/* 800C8FD4 000C3ED4  88 7F 04 CA */	lbz r3, 0x4ca(r31)
/* 800C8FD8 000C3ED8  28 03 00 C8 */	cmplwi r3, 0xc8
/* 800C8FDC 000C3EDC  40 82 00 10 */	bne lbl_800C8FEC
/* 800C8FE0 000C3EE0  C0 1F 04 90 */	lfs f0, 0x490(r31)
/* 800C8FE4 000C3EE4  D0 1F 04 A0 */	stfs f0, 0x4a0(r31)
/* 800C8FE8 000C3EE8  48 00 00 24 */	b lbl_800C900C
lbl_800C8FEC:
/* 800C8FEC 000C3EEC  38 03 00 01 */	addi r0, r3, 1
/* 800C8FF0 000C3EF0  98 1F 04 CA */	stb r0, 0x4ca(r31)
/* 800C8FF4 000C3EF4  48 00 00 18 */	b lbl_800C900C
lbl_800C8FF8:
/* 800C8FF8 000C3EF8  38 00 00 00 */	li r0, 0
/* 800C8FFC 000C3EFC  98 1F 04 CA */	stb r0, 0x4ca(r31)
/* 800C9000 000C3F00  48 00 00 0C */	b lbl_800C900C
lbl_800C9004:
/* 800C9004 000C3F04  38 00 00 00 */	li r0, 0
/* 800C9008 000C3F08  98 1F 04 CA */	stb r0, 0x4ca(r31)
lbl_800C900C:
/* 800C900C 000C3F0C  7F E3 FB 78 */	mr r3, r31
/* 800C9010 000C3F10  7F C4 07 74 */	extsb r4, r30
/* 800C9014 000C3F14  4B FF F7 ED */	bl calc_dpd_variable
/* 800C9018 000C3F18  E3 E1 00 38 */	psq_l f31, 56(r1), 0, qr0
/* 800C901C 000C3F1C  CB E1 00 30 */	lfd f31, 0x30(r1)
/* 800C9020 000C3F20  E3 C1 00 28 */	psq_l f30, 40(r1), 0, qr0
/* 800C9024 000C3F24  CB C1 00 20 */	lfd f30, 0x20(r1)
/* 800C9028 000C3F28  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800C902C 000C3F2C  80 01 00 44 */	lwz r0, 0x44(r1)
/* 800C9030 000C3F30  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 800C9034 000C3F34  7C 08 03 A6 */	mtlr r0
/* 800C9038 000C3F38  38 21 00 40 */	addi r1, r1, 0x40
/* 800C903C 000C3F3C  4E 80 00 20 */	blr 

.global clamp_stick_circle
clamp_stick_circle:
/* 800C9040 000C3F40  94 21 FF A0 */	stwu r1, -0x60(r1)
/* 800C9044 000C3F44  7C 08 02 A6 */	mflr r0
/* 800C9048 000C3F48  90 01 00 64 */	stw r0, 0x64(r1)
/* 800C904C 000C3F4C  DB E1 00 50 */	stfd f31, 0x50(r1)
/* 800C9050 000C3F50  F3 E1 00 58 */	psq_st f31, 88(r1), 0, qr0
/* 800C9054 000C3F54  DB C1 00 40 */	stfd f30, 0x40(r1)
/* 800C9058 000C3F58  F3 C1 00 48 */	psq_st f30, 72(r1), 0, qr0
/* 800C905C 000C3F5C  DB A1 00 30 */	stfd f29, 0x30(r1)
/* 800C9060 000C3F60  F3 A1 00 38 */	psq_st f29, 56(r1), 0, qr0
/* 800C9064 000C3F64  DB 81 00 20 */	stfd f28, 0x20(r1)
/* 800C9068 000C3F68  F3 81 00 28 */	psq_st f28, 40(r1), 0, qr0
/* 800C906C 000C3F6C  3D 00 43 30 */	lis r8, 0x4330
/* 800C9070 000C3F70  6C 80 80 00 */	xoris r0, r4, 0x8000
/* 800C9074 000C3F74  6C A5 80 00 */	xoris r5, r5, 0x8000
/* 800C9078 000C3F78  90 01 00 0C */	stw r0, 0xc(r1)
/* 800C907C 000C3F7C  6C C4 80 00 */	xoris r4, r6, 0x8000
/* 800C9080 000C3F80  C8 82 95 D8 */	lfd f4, lbl_804C0FF8-_SDA2_BASE_(r2)
/* 800C9084 000C3F84  6C E0 80 00 */	xoris r0, r7, 0x8000
/* 800C9088 000C3F88  91 01 00 08 */	stw r8, 8(r1)
/* 800C908C 000C3F8C  C8 01 00 08 */	lfd f0, 8(r1)
/* 800C9090 000C3F90  91 01 00 10 */	stw r8, 0x10(r1)
/* 800C9094 000C3F94  EF E0 20 28 */	fsubs f31, f0, f4
/* 800C9098 000C3F98  90 A1 00 14 */	stw r5, 0x14(r1)
/* 800C909C 000C3F9C  C8 01 00 10 */	lfd f0, 0x10(r1)
/* 800C90A0 000C3FA0  EC 3F 07 F2 */	fmuls f1, f31, f31
/* 800C90A4 000C3FA4  90 81 00 0C */	stw r4, 0xc(r1)
/* 800C90A8 000C3FA8  EF C0 20 28 */	fsubs f30, f0, f4
/* 800C90AC 000C3FAC  90 01 00 14 */	stw r0, 0x14(r1)
/* 800C90B0 000C3FB0  C8 61 00 08 */	lfd f3, 8(r1)
/* 800C90B4 000C3FB4  EC 1E 07 B2 */	fmuls f0, f30, f30
/* 800C90B8 000C3FB8  C8 41 00 10 */	lfd f2, 0x10(r1)
/* 800C90BC 000C3FBC  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800C90C0 000C3FC0  EF A3 20 28 */	fsubs f29, f3, f4
/* 800C90C4 000C3FC4  EF 82 20 28 */	fsubs f28, f2, f4
/* 800C90C8 000C3FC8  7C 7F 1B 78 */	mr r31, r3
/* 800C90CC 000C3FCC  EC 21 00 2A */	fadds f1, f1, f0
/* 800C90D0 000C3FD0  4B FF 80 01 */	bl sqrt
/* 800C90D4 000C3FD4  FC 40 08 18 */	frsp f2, f1
/* 800C90D8 000C3FD8  FC 02 E8 40 */	fcmpo cr0, f2, f29
/* 800C90DC 000C3FDC  4C 40 13 82 */	cror 2, 0, 2
/* 800C90E0 000C3FE0  40 82 00 14 */	bne lbl_800C90F4
/* 800C90E4 000C3FE4  C0 02 95 A8 */	lfs f0, lbl_804C0FC8-_SDA2_BASE_(r2)
/* 800C90E8 000C3FE8  D0 1F 00 04 */	stfs f0, 4(r31)
/* 800C90EC 000C3FEC  D0 1F 00 00 */	stfs f0, 0(r31)
/* 800C90F0 000C3FF0  48 00 00 44 */	b lbl_800C9134
lbl_800C90F4:
/* 800C90F4 000C3FF4  FC 02 E0 40 */	fcmpo cr0, f2, f28
/* 800C90F8 000C3FF8  4C 41 13 82 */	cror 2, 1, 2
/* 800C90FC 000C3FFC  40 82 00 18 */	bne lbl_800C9114
/* 800C9100 000C4000  EC 3F 10 24 */	fdivs f1, f31, f2
/* 800C9104 000C4004  EC 1E 10 24 */	fdivs f0, f30, f2
/* 800C9108 000C4008  D0 3F 00 00 */	stfs f1, 0(r31)
/* 800C910C 000C400C  D0 1F 00 04 */	stfs f0, 4(r31)
/* 800C9110 000C4010  48 00 00 24 */	b lbl_800C9134
lbl_800C9114:
/* 800C9114 000C4014  EC 22 E8 28 */	fsubs f1, f2, f29
/* 800C9118 000C4018  EC 1C E8 28 */	fsubs f0, f28, f29
/* 800C911C 000C401C  EC 01 00 24 */	fdivs f0, f1, f0
/* 800C9120 000C4020  EC 00 10 24 */	fdivs f0, f0, f2
/* 800C9124 000C4024  EC 3F 00 32 */	fmuls f1, f31, f0
/* 800C9128 000C4028  EC 1E 00 32 */	fmuls f0, f30, f0
/* 800C912C 000C402C  D0 3F 00 00 */	stfs f1, 0(r31)
/* 800C9130 000C4030  D0 1F 00 04 */	stfs f0, 4(r31)
lbl_800C9134:
/* 800C9134 000C4034  E3 E1 00 58 */	psq_l f31, 88(r1), 0, qr0
/* 800C9138 000C4038  CB E1 00 50 */	lfd f31, 0x50(r1)
/* 800C913C 000C403C  E3 C1 00 48 */	psq_l f30, 72(r1), 0, qr0
/* 800C9140 000C4040  CB C1 00 40 */	lfd f30, 0x40(r1)
/* 800C9144 000C4044  E3 A1 00 38 */	psq_l f29, 56(r1), 0, qr0
/* 800C9148 000C4048  CB A1 00 30 */	lfd f29, 0x30(r1)
/* 800C914C 000C404C  E3 81 00 28 */	psq_l f28, 40(r1), 0, qr0
/* 800C9150 000C4050  CB 81 00 20 */	lfd f28, 0x20(r1)
/* 800C9154 000C4054  80 01 00 64 */	lwz r0, 0x64(r1)
/* 800C9158 000C4058  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800C915C 000C405C  7C 08 03 A6 */	mtlr r0
/* 800C9160 000C4060  38 21 00 60 */	addi r1, r1, 0x60
/* 800C9164 000C4064  4E 80 00 20 */	blr 

.global clamp_stick_cross
clamp_stick_cross:
/* 800C9168 000C4068  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800C916C 000C406C  7C 08 02 A6 */	mflr r0
/* 800C9170 000C4070  2C 04 00 00 */	cmpwi r4, 0
/* 800C9174 000C4074  90 01 00 24 */	stw r0, 0x24(r1)
/* 800C9178 000C4078  3C 00 43 30 */	lis r0, 0x4330
/* 800C917C 000C407C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800C9180 000C4080  7C 7F 1B 78 */	mr r31, r3
/* 800C9184 000C4084  90 01 00 08 */	stw r0, 8(r1)
/* 800C9188 000C4088  90 01 00 10 */	stw r0, 0x10(r1)
/* 800C918C 000C408C  40 80 00 78 */	bge lbl_800C9204
/* 800C9190 000C4090  7C 04 00 D0 */	neg r0, r4
/* 800C9194 000C4094  7C 00 30 00 */	cmpw r0, r6
/* 800C9198 000C4098  41 81 00 10 */	bgt lbl_800C91A8
/* 800C919C 000C409C  C0 02 95 A8 */	lfs f0, lbl_804C0FC8-_SDA2_BASE_(r2)
/* 800C91A0 000C40A0  D0 03 00 00 */	stfs f0, 0(r3)
/* 800C91A4 000C40A4  48 00 00 50 */	b lbl_800C91F4
lbl_800C91A8:
/* 800C91A8 000C40A8  7C 00 38 00 */	cmpw r0, r7
/* 800C91AC 000C40AC  41 80 00 10 */	blt lbl_800C91BC
/* 800C91B0 000C40B0  C0 02 95 BC */	lfs f0, lbl_804C0FDC-_SDA2_BASE_(r2)
/* 800C91B4 000C40B4  D0 03 00 00 */	stfs f0, 0(r3)
/* 800C91B8 000C40B8  48 00 00 3C */	b lbl_800C91F4
lbl_800C91BC:
/* 800C91BC 000C40BC  7C 84 32 14 */	add r4, r4, r6
/* 800C91C0 000C40C0  7C 06 38 50 */	subf r0, r6, r7
/* 800C91C4 000C40C4  7C 84 00 D0 */	neg r4, r4
/* 800C91C8 000C40C8  C8 42 95 D8 */	lfd f2, lbl_804C0FF8-_SDA2_BASE_(r2)
/* 800C91CC 000C40CC  6C 84 80 00 */	xoris r4, r4, 0x8000
/* 800C91D0 000C40D0  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 800C91D4 000C40D4  90 81 00 0C */	stw r4, 0xc(r1)
/* 800C91D8 000C40D8  90 01 00 14 */	stw r0, 0x14(r1)
/* 800C91DC 000C40DC  C8 21 00 08 */	lfd f1, 8(r1)
/* 800C91E0 000C40E0  C8 01 00 10 */	lfd f0, 0x10(r1)
/* 800C91E4 000C40E4  EC 21 10 28 */	fsubs f1, f1, f2
/* 800C91E8 000C40E8  EC 00 10 28 */	fsubs f0, f0, f2
/* 800C91EC 000C40EC  EC 01 00 24 */	fdivs f0, f1, f0
/* 800C91F0 000C40F0  D0 03 00 00 */	stfs f0, 0(r3)
lbl_800C91F4:
/* 800C91F4 000C40F4  C0 03 00 00 */	lfs f0, 0(r3)
/* 800C91F8 000C40F8  FC 00 00 50 */	fneg f0, f0
/* 800C91FC 000C40FC  D0 03 00 00 */	stfs f0, 0(r3)
/* 800C9200 000C4100  48 00 00 60 */	b lbl_800C9260
lbl_800C9204:
/* 800C9204 000C4104  7C 04 30 00 */	cmpw r4, r6
/* 800C9208 000C4108  41 81 00 10 */	bgt lbl_800C9218
/* 800C920C 000C410C  C0 02 95 A8 */	lfs f0, lbl_804C0FC8-_SDA2_BASE_(r2)
/* 800C9210 000C4110  D0 03 00 00 */	stfs f0, 0(r3)
/* 800C9214 000C4114  48 00 00 4C */	b lbl_800C9260
lbl_800C9218:
/* 800C9218 000C4118  7C 04 38 00 */	cmpw r4, r7
/* 800C921C 000C411C  41 80 00 10 */	blt lbl_800C922C
/* 800C9220 000C4120  C0 02 95 BC */	lfs f0, lbl_804C0FDC-_SDA2_BASE_(r2)
/* 800C9224 000C4124  D0 03 00 00 */	stfs f0, 0(r3)
/* 800C9228 000C4128  48 00 00 38 */	b lbl_800C9260
lbl_800C922C:
/* 800C922C 000C412C  7C 86 20 50 */	subf r4, r6, r4
/* 800C9230 000C4130  7C 06 38 50 */	subf r0, r6, r7
/* 800C9234 000C4134  6C 84 80 00 */	xoris r4, r4, 0x8000
/* 800C9238 000C4138  C8 42 95 D8 */	lfd f2, lbl_804C0FF8-_SDA2_BASE_(r2)
/* 800C923C 000C413C  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 800C9240 000C4140  90 81 00 0C */	stw r4, 0xc(r1)
/* 800C9244 000C4144  90 01 00 14 */	stw r0, 0x14(r1)
/* 800C9248 000C4148  C8 21 00 08 */	lfd f1, 8(r1)
/* 800C924C 000C414C  C8 01 00 10 */	lfd f0, 0x10(r1)
/* 800C9250 000C4150  EC 21 10 28 */	fsubs f1, f1, f2
/* 800C9254 000C4154  EC 00 10 28 */	fsubs f0, f0, f2
/* 800C9258 000C4158  EC 01 00 24 */	fdivs f0, f1, f0
/* 800C925C 000C415C  D0 03 00 00 */	stfs f0, 0(r3)
lbl_800C9260:
/* 800C9260 000C4160  2C 05 00 00 */	cmpwi r5, 0
/* 800C9264 000C4164  40 80 00 78 */	bge lbl_800C92DC
/* 800C9268 000C4168  7C 05 00 D0 */	neg r0, r5
/* 800C926C 000C416C  7C 00 30 00 */	cmpw r0, r6
/* 800C9270 000C4170  41 81 00 10 */	bgt lbl_800C9280
/* 800C9274 000C4174  C0 02 95 A8 */	lfs f0, lbl_804C0FC8-_SDA2_BASE_(r2)
/* 800C9278 000C4178  D0 03 00 04 */	stfs f0, 4(r3)
/* 800C927C 000C417C  48 00 00 50 */	b lbl_800C92CC
lbl_800C9280:
/* 800C9280 000C4180  7C 00 38 00 */	cmpw r0, r7
/* 800C9284 000C4184  41 80 00 10 */	blt lbl_800C9294
/* 800C9288 000C4188  C0 02 95 BC */	lfs f0, lbl_804C0FDC-_SDA2_BASE_(r2)
/* 800C928C 000C418C  D0 03 00 04 */	stfs f0, 4(r3)
/* 800C9290 000C4190  48 00 00 3C */	b lbl_800C92CC
lbl_800C9294:
/* 800C9294 000C4194  7C 85 32 14 */	add r4, r5, r6
/* 800C9298 000C4198  7C 06 38 50 */	subf r0, r6, r7
/* 800C929C 000C419C  7C 84 00 D0 */	neg r4, r4
/* 800C92A0 000C41A0  C8 42 95 D8 */	lfd f2, lbl_804C0FF8-_SDA2_BASE_(r2)
/* 800C92A4 000C41A4  6C 84 80 00 */	xoris r4, r4, 0x8000
/* 800C92A8 000C41A8  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 800C92AC 000C41AC  90 81 00 0C */	stw r4, 0xc(r1)
/* 800C92B0 000C41B0  90 01 00 14 */	stw r0, 0x14(r1)
/* 800C92B4 000C41B4  C8 21 00 08 */	lfd f1, 8(r1)
/* 800C92B8 000C41B8  C8 01 00 10 */	lfd f0, 0x10(r1)
/* 800C92BC 000C41BC  EC 21 10 28 */	fsubs f1, f1, f2
/* 800C92C0 000C41C0  EC 00 10 28 */	fsubs f0, f0, f2
/* 800C92C4 000C41C4  EC 01 00 24 */	fdivs f0, f1, f0
/* 800C92C8 000C41C8  D0 03 00 04 */	stfs f0, 4(r3)
lbl_800C92CC:
/* 800C92CC 000C41CC  C0 03 00 04 */	lfs f0, 4(r3)
/* 800C92D0 000C41D0  FC 00 00 50 */	fneg f0, f0
/* 800C92D4 000C41D4  D0 03 00 04 */	stfs f0, 4(r3)
/* 800C92D8 000C41D8  48 00 00 60 */	b lbl_800C9338
lbl_800C92DC:
/* 800C92DC 000C41DC  7C 05 30 00 */	cmpw r5, r6
/* 800C92E0 000C41E0  41 81 00 10 */	bgt lbl_800C92F0
/* 800C92E4 000C41E4  C0 02 95 A8 */	lfs f0, lbl_804C0FC8-_SDA2_BASE_(r2)
/* 800C92E8 000C41E8  D0 03 00 04 */	stfs f0, 4(r3)
/* 800C92EC 000C41EC  48 00 00 4C */	b lbl_800C9338
lbl_800C92F0:
/* 800C92F0 000C41F0  7C 05 38 00 */	cmpw r5, r7
/* 800C92F4 000C41F4  41 80 00 10 */	blt lbl_800C9304
/* 800C92F8 000C41F8  C0 02 95 BC */	lfs f0, lbl_804C0FDC-_SDA2_BASE_(r2)
/* 800C92FC 000C41FC  D0 03 00 04 */	stfs f0, 4(r3)
/* 800C9300 000C4200  48 00 00 38 */	b lbl_800C9338
lbl_800C9304:
/* 800C9304 000C4204  7C 86 28 50 */	subf r4, r6, r5
/* 800C9308 000C4208  7C 06 38 50 */	subf r0, r6, r7
/* 800C930C 000C420C  6C 84 80 00 */	xoris r4, r4, 0x8000
/* 800C9310 000C4210  C8 42 95 D8 */	lfd f2, lbl_804C0FF8-_SDA2_BASE_(r2)
/* 800C9314 000C4214  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 800C9318 000C4218  90 81 00 0C */	stw r4, 0xc(r1)
/* 800C931C 000C421C  90 01 00 14 */	stw r0, 0x14(r1)
/* 800C9320 000C4220  C8 21 00 08 */	lfd f1, 8(r1)
/* 800C9324 000C4224  C8 01 00 10 */	lfd f0, 0x10(r1)
/* 800C9328 000C4228  EC 21 10 28 */	fsubs f1, f1, f2
/* 800C932C 000C422C  EC 00 10 28 */	fsubs f0, f0, f2
/* 800C9330 000C4230  EC 01 00 24 */	fdivs f0, f1, f0
/* 800C9334 000C4234  D0 03 00 04 */	stfs f0, 4(r3)
lbl_800C9338:
/* 800C9338 000C4238  C0 03 00 00 */	lfs f0, 0(r3)
/* 800C933C 000C423C  C0 23 00 04 */	lfs f1, 4(r3)
/* 800C9340 000C4240  EC 40 00 32 */	fmuls f2, f0, f0
/* 800C9344 000C4244  C0 02 95 BC */	lfs f0, lbl_804C0FDC-_SDA2_BASE_(r2)
/* 800C9348 000C4248  EC 21 00 72 */	fmuls f1, f1, f1
/* 800C934C 000C424C  EC 22 08 2A */	fadds f1, f2, f1
/* 800C9350 000C4250  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800C9354 000C4254  40 81 00 24 */	ble lbl_800C9378
/* 800C9358 000C4258  4B FF 7D 79 */	bl sqrt
/* 800C935C 000C425C  FC 40 08 18 */	frsp f2, f1
/* 800C9360 000C4260  C0 3F 00 00 */	lfs f1, 0(r31)
/* 800C9364 000C4264  C0 1F 00 04 */	lfs f0, 4(r31)
/* 800C9368 000C4268  EC 21 10 24 */	fdivs f1, f1, f2
/* 800C936C 000C426C  EC 00 10 24 */	fdivs f0, f0, f2
/* 800C9370 000C4270  D0 3F 00 00 */	stfs f1, 0(r31)
/* 800C9374 000C4274  D0 1F 00 04 */	stfs f0, 4(r31)
lbl_800C9378:
/* 800C9378 000C4278  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800C937C 000C427C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800C9380 000C4280  7C 08 03 A6 */	mtlr r0
/* 800C9384 000C4284  38 21 00 20 */	addi r1, r1, 0x20
/* 800C9388 000C4288  4E 80 00 20 */	blr 

.global read_kpad_stick
read_kpad_stick:
/* 800C938C 000C428C  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 800C9390 000C4290  7C 08 02 A6 */	mflr r0
/* 800C9394 000C4294  3C A0 43 30 */	lis r5, 0x4330
/* 800C9398 000C4298  90 01 00 34 */	stw r0, 0x34(r1)
/* 800C939C 000C429C  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 800C93A0 000C42A0  3F E0 80 0D */	lis r31, clamp_stick_cross@ha
/* 800C93A4 000C42A4  3B FF 91 68 */	addi r31, r31, clamp_stick_cross@l
/* 800C93A8 000C42A8  93 C1 00 28 */	stw r30, 0x28(r1)
/* 800C93AC 000C42AC  3B C3 00 60 */	addi r30, r3, 0x60
/* 800C93B0 000C42B0  93 A1 00 24 */	stw r29, 0x24(r1)
/* 800C93B4 000C42B4  7C 9D 23 78 */	mr r29, r4
/* 800C93B8 000C42B8  80 0D 9A 30 */	lwz r0, kp_stick_clamp_cross-_SDA_BASE_(r13)
/* 800C93BC 000C42BC  90 A1 00 08 */	stw r5, 8(r1)
/* 800C93C0 000C42C0  2C 00 00 00 */	cmpwi r0, 0
/* 800C93C4 000C42C4  90 A1 00 10 */	stw r5, 0x10(r1)
/* 800C93C8 000C42C8  41 82 00 0C */	beq lbl_800C93D4
/* 800C93CC 000C42CC  3F E0 80 0D */	lis r31, clamp_stick_circle@ha
/* 800C93D0 000C42D0  3B FF 90 40 */	addi r31, r31, clamp_stick_circle@l
lbl_800C93D4:
/* 800C93D4 000C42D4  88 C4 00 28 */	lbz r6, 0x28(r4)
/* 800C93D8 000C42D8  28 06 00 01 */	cmplwi r6, 1
/* 800C93DC 000C42DC  40 82 00 88 */	bne lbl_800C9464
/* 800C93E0 000C42E0  88 A4 00 36 */	lbz r5, 0x36(r4)
/* 800C93E4 000C42E4  38 05 00 FD */	addi r0, r5, 0xfd
/* 800C93E8 000C42E8  54 00 06 3E */	clrlwi r0, r0, 0x18
/* 800C93EC 000C42EC  28 00 00 02 */	cmplwi r0, 2
/* 800C93F0 000C42F0  41 81 00 74 */	bgt lbl_800C9464
/* 800C93F4 000C42F4  88 03 05 1E */	lbz r0, 0x51e(r3)
/* 800C93F8 000C42F8  2C 00 00 00 */	cmpwi r0, 0
/* 800C93FC 000C42FC  41 82 00 3C */	beq lbl_800C9438
/* 800C9400 000C4300  38 00 00 00 */	li r0, 0
/* 800C9404 000C4304  C0 42 95 A8 */	lfs f2, lbl_804C0FC8-_SDA2_BASE_(r2)
/* 800C9408 000C4308  98 03 05 1E */	stb r0, 0x51e(r3)
/* 800C940C 000C430C  C0 22 95 B8 */	lfs f1, lbl_804C0FD8-_SDA2_BASE_(r2)
/* 800C9410 000C4310  80 6D 9A 38 */	lwz r3, Vec2_0-_SDA_BASE_(r13)
/* 800C9414 000C4314  80 0D 9A 3C */	lwz r0, (Vec2_0 + 4)-_SDA_BASE_(r13)
/* 800C9418 000C4318  C0 02 95 BC */	lfs f0, lbl_804C0FDC-_SDA2_BASE_(r2)
/* 800C941C 000C431C  90 7E 00 00 */	stw r3, 0(r30)
/* 800C9420 000C4320  90 1E 00 04 */	stw r0, 4(r30)
/* 800C9424 000C4324  D0 5E 00 10 */	stfs f2, 0x10(r30)
/* 800C9428 000C4328  D0 5E 00 08 */	stfs f2, 8(r30)
/* 800C942C 000C432C  D0 3E 00 0C */	stfs f1, 0xc(r30)
/* 800C9430 000C4330  D0 1E 00 14 */	stfs f0, 0x14(r30)
/* 800C9434 000C4334  D0 5E 00 18 */	stfs f2, 0x18(r30)
lbl_800C9438:
/* 800C9438 000C4338  88 84 00 30 */	lbz r4, 0x30(r4)
/* 800C943C 000C433C  7F EC FB 78 */	mr r12, r31
/* 800C9440 000C4340  88 BD 00 31 */	lbz r5, 0x31(r29)
/* 800C9444 000C4344  7F C3 F3 78 */	mr r3, r30
/* 800C9448 000C4348  7C 84 07 74 */	extsb r4, r4
/* 800C944C 000C434C  80 CD 82 2C */	lwz r6, kp_fs_fstick_min-_SDA_BASE_(r13)
/* 800C9450 000C4350  7C A5 07 74 */	extsb r5, r5
/* 800C9454 000C4354  80 ED 82 30 */	lwz r7, kp_fs_fstick_max-_SDA_BASE_(r13)
/* 800C9458 000C4358  7D 89 03 A6 */	mtctr r12
/* 800C945C 000C435C  4E 80 04 21 */	bctrl 
/* 800C9460 000C4360  48 00 01 88 */	b lbl_800C95E8
lbl_800C9464:
/* 800C9464 000C4364  28 06 00 02 */	cmplwi r6, 2
/* 800C9468 000C4368  40 82 01 80 */	bne lbl_800C95E8
/* 800C946C 000C436C  88 A4 00 36 */	lbz r5, 0x36(r4)
/* 800C9470 000C4370  38 05 00 FA */	addi r0, r5, 0xfa
/* 800C9474 000C4374  54 00 06 3E */	clrlwi r0, r0, 0x18
/* 800C9478 000C4378  28 00 00 02 */	cmplwi r0, 2
/* 800C947C 000C437C  41 81 01 6C */	bgt lbl_800C95E8
/* 800C9480 000C4380  88 03 05 1E */	lbz r0, 0x51e(r3)
/* 800C9484 000C4384  2C 00 00 00 */	cmpwi r0, 0
/* 800C9488 000C4388  41 82 00 50 */	beq lbl_800C94D8
/* 800C948C 000C438C  38 E0 00 00 */	li r7, 0
/* 800C9490 000C4390  C0 02 95 A8 */	lfs f0, lbl_804C0FC8-_SDA2_BASE_(r2)
/* 800C9494 000C4394  98 E3 05 1E */	stb r7, 0x51e(r3)
/* 800C9498 000C4398  A0 03 04 D0 */	lhz r0, 0x4d0(r3)
/* 800C949C 000C439C  80 CD 9A 38 */	lwz r6, Vec2_0-_SDA_BASE_(r13)
/* 800C94A0 000C43A0  80 AD 9A 3C */	lwz r5, (Vec2_0 + 4)-_SDA_BASE_(r13)
/* 800C94A4 000C43A4  90 DE 00 0C */	stw r6, 0xc(r30)
/* 800C94A8 000C43A8  90 BE 00 10 */	stw r5, 0x10(r30)
/* 800C94AC 000C43AC  80 CD 9A 38 */	lwz r6, Vec2_0-_SDA_BASE_(r13)
/* 800C94B0 000C43B0  80 AD 9A 3C */	lwz r5, (Vec2_0 + 4)-_SDA_BASE_(r13)
/* 800C94B4 000C43B4  90 DE 00 14 */	stw r6, 0x14(r30)
/* 800C94B8 000C43B8  90 BE 00 18 */	stw r5, 0x18(r30)
/* 800C94BC 000C43BC  D0 1E 00 20 */	stfs f0, 0x20(r30)
/* 800C94C0 000C43C0  D0 1E 00 1C */	stfs f0, 0x1c(r30)
/* 800C94C4 000C43C4  90 FE 00 08 */	stw r7, 8(r30)
/* 800C94C8 000C43C8  90 FE 00 04 */	stw r7, 4(r30)
/* 800C94CC 000C43CC  90 FE 00 00 */	stw r7, 0(r30)
/* 800C94D0 000C43D0  B0 E3 04 D4 */	sth r7, 0x4d4(r3)
/* 800C94D4 000C43D4  B0 03 04 D6 */	sth r0, 0x4d6(r3)
lbl_800C94D8:
/* 800C94D8 000C43D8  7F EC FB 78 */	mr r12, r31
/* 800C94DC 000C43DC  38 7E 00 0C */	addi r3, r30, 0xc
/* 800C94E0 000C43E0  A8 84 00 2C */	lha r4, 0x2c(r4)
/* 800C94E4 000C43E4  A8 BD 00 2E */	lha r5, 0x2e(r29)
/* 800C94E8 000C43E8  80 CD 82 34 */	lwz r6, kp_cl_stick_min-_SDA_BASE_(r13)
/* 800C94EC 000C43EC  80 ED 82 38 */	lwz r7, kp_cl_stick_max-_SDA_BASE_(r13)
/* 800C94F0 000C43F0  7D 89 03 A6 */	mtctr r12
/* 800C94F4 000C43F4  4E 80 04 21 */	bctrl 
/* 800C94F8 000C43F8  7F EC FB 78 */	mr r12, r31
/* 800C94FC 000C43FC  38 7E 00 14 */	addi r3, r30, 0x14
/* 800C9500 000C4400  A8 9D 00 30 */	lha r4, 0x30(r29)
/* 800C9504 000C4404  A8 BD 00 32 */	lha r5, 0x32(r29)
/* 800C9508 000C4408  80 CD 82 34 */	lwz r6, kp_cl_stick_min-_SDA_BASE_(r13)
/* 800C950C 000C440C  80 ED 82 38 */	lwz r7, kp_cl_stick_max-_SDA_BASE_(r13)
/* 800C9510 000C4410  7D 89 03 A6 */	mtctr r12
/* 800C9514 000C4414  4E 80 04 21 */	bctrl 
/* 800C9518 000C4418  80 AD 82 3C */	lwz r5, kp_cl_trigger_min-_SDA_BASE_(r13)
/* 800C951C 000C441C  88 1D 00 34 */	lbz r0, 0x34(r29)
/* 800C9520 000C4420  80 8D 82 40 */	lwz r4, kp_cl_trigger_max-_SDA_BASE_(r13)
/* 800C9524 000C4424  7C 00 28 00 */	cmpw r0, r5
/* 800C9528 000C4428  41 81 00 10 */	bgt lbl_800C9538
/* 800C952C 000C442C  C0 02 95 A8 */	lfs f0, lbl_804C0FC8-_SDA2_BASE_(r2)
/* 800C9530 000C4430  D0 1E 00 1C */	stfs f0, 0x1c(r30)
/* 800C9534 000C4434  48 00 00 4C */	b lbl_800C9580
lbl_800C9538:
/* 800C9538 000C4438  7C 00 20 00 */	cmpw r0, r4
/* 800C953C 000C443C  41 80 00 10 */	blt lbl_800C954C
/* 800C9540 000C4440  C0 02 95 BC */	lfs f0, lbl_804C0FDC-_SDA2_BASE_(r2)
/* 800C9544 000C4444  D0 1E 00 1C */	stfs f0, 0x1c(r30)
/* 800C9548 000C4448  48 00 00 38 */	b lbl_800C9580
lbl_800C954C:
/* 800C954C 000C444C  7C 65 00 50 */	subf r3, r5, r0
/* 800C9550 000C4450  7C 05 20 50 */	subf r0, r5, r4
/* 800C9554 000C4454  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 800C9558 000C4458  C8 42 95 D8 */	lfd f2, lbl_804C0FF8-_SDA2_BASE_(r2)
/* 800C955C 000C445C  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 800C9560 000C4460  90 61 00 0C */	stw r3, 0xc(r1)
/* 800C9564 000C4464  90 01 00 14 */	stw r0, 0x14(r1)
/* 800C9568 000C4468  C8 21 00 08 */	lfd f1, 8(r1)
/* 800C956C 000C446C  C8 01 00 10 */	lfd f0, 0x10(r1)
/* 800C9570 000C4470  EC 21 10 28 */	fsubs f1, f1, f2
/* 800C9574 000C4474  EC 00 10 28 */	fsubs f0, f0, f2
/* 800C9578 000C4478  EC 01 00 24 */	fdivs f0, f1, f0
/* 800C957C 000C447C  D0 1E 00 1C */	stfs f0, 0x1c(r30)
lbl_800C9580:
/* 800C9580 000C4480  80 AD 82 3C */	lwz r5, kp_cl_trigger_min-_SDA_BASE_(r13)
/* 800C9584 000C4484  88 1D 00 35 */	lbz r0, 0x35(r29)
/* 800C9588 000C4488  80 8D 82 40 */	lwz r4, kp_cl_trigger_max-_SDA_BASE_(r13)
/* 800C958C 000C448C  7C 00 28 00 */	cmpw r0, r5
/* 800C9590 000C4490  41 81 00 10 */	bgt lbl_800C95A0
/* 800C9594 000C4494  C0 02 95 A8 */	lfs f0, lbl_804C0FC8-_SDA2_BASE_(r2)
/* 800C9598 000C4498  D0 1E 00 20 */	stfs f0, 0x20(r30)
/* 800C959C 000C449C  48 00 00 4C */	b lbl_800C95E8
lbl_800C95A0:
/* 800C95A0 000C44A0  7C 00 20 00 */	cmpw r0, r4
/* 800C95A4 000C44A4  41 80 00 10 */	blt lbl_800C95B4
/* 800C95A8 000C44A8  C0 02 95 BC */	lfs f0, lbl_804C0FDC-_SDA2_BASE_(r2)
/* 800C95AC 000C44AC  D0 1E 00 20 */	stfs f0, 0x20(r30)
/* 800C95B0 000C44B0  48 00 00 38 */	b lbl_800C95E8
lbl_800C95B4:
/* 800C95B4 000C44B4  7C 65 00 50 */	subf r3, r5, r0
/* 800C95B8 000C44B8  7C 05 20 50 */	subf r0, r5, r4
/* 800C95BC 000C44BC  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 800C95C0 000C44C0  C8 42 95 D8 */	lfd f2, lbl_804C0FF8-_SDA2_BASE_(r2)
/* 800C95C4 000C44C4  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 800C95C8 000C44C8  90 61 00 0C */	stw r3, 0xc(r1)
/* 800C95CC 000C44CC  90 01 00 14 */	stw r0, 0x14(r1)
/* 800C95D0 000C44D0  C8 21 00 08 */	lfd f1, 8(r1)
/* 800C95D4 000C44D4  C8 01 00 10 */	lfd f0, 0x10(r1)
/* 800C95D8 000C44D8  EC 21 10 28 */	fsubs f1, f1, f2
/* 800C95DC 000C44DC  EC 00 10 28 */	fsubs f0, f0, f2
/* 800C95E0 000C44E0  EC 01 00 24 */	fdivs f0, f1, f0
/* 800C95E4 000C44E4  D0 1E 00 20 */	stfs f0, 0x20(r30)
lbl_800C95E8:
/* 800C95E8 000C44E8  80 01 00 34 */	lwz r0, 0x34(r1)
/* 800C95EC 000C44EC  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 800C95F0 000C44F0  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 800C95F4 000C44F4  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 800C95F8 000C44F8  7C 08 03 A6 */	mtlr r0
/* 800C95FC 000C44FC  38 21 00 30 */	addi r1, r1, 0x30
/* 800C9600 000C4500  4E 80 00 20 */	blr 

.global KPADRead
KPADRead:
/* 800C9604 000C4504  94 21 FF 40 */	stwu r1, -0xc0(r1)
/* 800C9608 000C4508  7C 08 02 A6 */	mflr r0
/* 800C960C 000C450C  90 01 00 C4 */	stw r0, 0xc4(r1)
/* 800C9610 000C4510  39 61 00 C0 */	addi r11, r1, 0xc0
/* 800C9614 000C4514  4B FE 86 FD */	bl _savegpr_14
/* 800C9618 000C4518  1C 03 05 24 */	mulli r0, r3, 0x524
/* 800C961C 000C451C  3C E0 43 30 */	lis r7, 0x4330
/* 800C9620 000C4520  3C C0 80 41 */	lis r6, inside_kpads@ha
/* 800C9624 000C4524  90 E1 00 50 */	stw r7, 0x50(r1)
/* 800C9628 000C4528  7C 7B 1B 78 */	mr r27, r3
/* 800C962C 000C452C  38 C6 E1 58 */	addi r6, r6, inside_kpads@l
/* 800C9630 000C4530  90 E1 00 58 */	stw r7, 0x58(r1)
/* 800C9634 000C4534  7C 9C 23 78 */	mr r28, r4
/* 800C9638 000C4538  7C AE 2B 78 */	mr r14, r5
/* 800C963C 000C453C  7F E6 02 14 */	add r31, r6, r0
/* 800C9640 000C4540  3B C0 00 00 */	li r30, 0
/* 800C9644 000C4544  48 02 82 7D */	bl OSDisableInterrupts
/* 800C9648 000C4548  88 1F 05 1C */	lbz r0, 0x51c(r31)
/* 800C964C 000C454C  7C 71 1B 78 */	mr r17, r3
/* 800C9650 000C4550  2C 00 00 00 */	cmpwi r0, 0
/* 800C9654 000C4554  41 82 00 10 */	beq lbl_800C9664
/* 800C9658 000C4558  48 02 82 91 */	bl OSRestoreInterrupts
/* 800C965C 000C455C  38 60 00 00 */	li r3, 0
/* 800C9660 000C4560  48 00 06 A4 */	b lbl_800C9D04
lbl_800C9664:
/* 800C9664 000C4564  3A 00 00 01 */	li r16, 1
/* 800C9668 000C4568  7F 63 DB 78 */	mr r3, r27
/* 800C966C 000C456C  9A 1F 05 1C */	stb r16, 0x51c(r31)
/* 800C9670 000C4570  38 80 00 00 */	li r4, 0
/* 800C9674 000C4574  48 00 3F 95 */	bl WPADProbe
/* 800C9678 000C4578  2C 03 FF FF */	cmpwi r3, -1
/* 800C967C 000C457C  7C 6F 1B 78 */	mr r15, r3
/* 800C9680 000C4580  40 82 00 58 */	bne lbl_800C96D8
/* 800C9684 000C4584  80 1F 04 D8 */	lwz r0, 0x4d8(r31)
/* 800C9688 000C4588  2C 80 00 00 */	cmpwi cr1, r0, 0
/* 800C968C 000C458C  41 86 00 4C */	beq cr1, lbl_800C96D8
/* 800C9690 000C4590  88 1F 05 22 */	lbz r0, 0x522(r31)
/* 800C9694 000C4594  2C 00 00 00 */	cmpwi r0, 0
/* 800C9698 000C4598  41 82 00 40 */	beq lbl_800C96D8
/* 800C969C 000C459C  88 1F 05 23 */	lbz r0, 0x523(r31)
/* 800C96A0 000C45A0  2C 00 00 00 */	cmpwi r0, 0
/* 800C96A4 000C45A4  40 82 00 34 */	bne lbl_800C96D8
/* 800C96A8 000C45A8  41 86 00 28 */	beq cr1, lbl_800C96D0
/* 800C96AC 000C45AC  40 82 00 24 */	bne lbl_800C96D0
/* 800C96B0 000C45B0  9A 1F 05 23 */	stb r16, 0x523(r31)
/* 800C96B4 000C45B4  7F 63 DB 78 */	mr r3, r27
/* 800C96B8 000C45B8  38 80 00 01 */	li r4, 1
/* 800C96BC 000C45BC  81 9F 04 D8 */	lwz r12, 0x4d8(r31)
/* 800C96C0 000C45C0  7D 89 03 A6 */	mtctr r12
/* 800C96C4 000C45C4  4E 80 04 21 */	bctrl 
/* 800C96C8 000C45C8  38 00 00 00 */	li r0, 0
/* 800C96CC 000C45CC  98 1F 05 22 */	stb r0, 0x522(r31)
lbl_800C96D0:
/* 800C96D0 000C45D0  38 00 00 00 */	li r0, 0
/* 800C96D4 000C45D4  98 1F 05 1F */	stb r0, 0x51f(r31)
lbl_800C96D8:
/* 800C96D8 000C45D8  7E 23 8B 78 */	mr r3, r17
/* 800C96DC 000C45DC  48 02 82 0D */	bl OSRestoreInterrupts
/* 800C96E0 000C45E0  88 1F 05 1D */	lbz r0, 0x51d(r31)
/* 800C96E4 000C45E4  2C 00 00 00 */	cmpwi r0, 0
/* 800C96E8 000C45E8  41 82 00 10 */	beq lbl_800C96F8
/* 800C96EC 000C45EC  99 FF 00 5D */	stb r15, 0x5d(r31)
/* 800C96F0 000C45F0  7F E3 FB 78 */	mr r3, r31
/* 800C96F4 000C45F4  4B FF DC DD */	bl reset_kpad
lbl_800C96F8:
/* 800C96F8 000C45F8  3C 80 80 0D */	lis r4, KPADiSamplingCallback@ha
/* 800C96FC 000C45FC  7F 63 DB 78 */	mr r3, r27
/* 800C9700 000C4600  38 84 A1 00 */	addi r4, r4, KPADiSamplingCallback@l
/* 800C9704 000C4604  48 00 3F 91 */	bl WPADSetSamplingCallback
/* 800C9708 000C4608  88 1F 01 0F */	lbz r0, 0x10f(r31)
/* 800C970C 000C460C  2C 00 00 00 */	cmpwi r0, 0
/* 800C9710 000C4610  41 82 05 E8 */	beq lbl_800C9CF8
/* 800C9714 000C4614  2C 1C 00 00 */	cmpwi r28, 0
/* 800C9718 000C4618  41 82 05 E0 */	beq lbl_800C9CF8
/* 800C971C 000C461C  2C 0E 00 00 */	cmpwi r14, 0
/* 800C9720 000C4620  41 82 05 D8 */	beq lbl_800C9CF8
/* 800C9724 000C4624  48 02 81 9D */	bl OSDisableInterrupts
/* 800C9728 000C4628  8B BF 01 0F */	lbz r29, 0x10f(r31)
/* 800C972C 000C462C  7C 1D 70 40 */	cmplw r29, r14
/* 800C9730 000C4630  7F BE EB 78 */	mr r30, r29
/* 800C9734 000C4634  40 81 00 08 */	ble lbl_800C973C
/* 800C9738 000C4638  7D DE 73 78 */	mr r30, r14
lbl_800C973C:
/* 800C973C 000C463C  38 80 00 00 */	li r4, 0
/* 800C9740 000C4640  7F C0 F3 78 */	mr r0, r30
/* 800C9744 000C4644  98 9F 01 0F */	stb r4, 0x10f(r31)
/* 800C9748 000C4648  1C BE 00 84 */	mulli r5, r30, 0x84
/* 800C974C 000C464C  88 9F 01 0E */	lbz r4, 0x10e(r31)
/* 800C9750 000C4650  7C BC 2A 14 */	add r5, r28, r5
/* 800C9754 000C4654  7C DE 20 51 */	subf. r6, r30, r4
/* 800C9758 000C4658  40 80 00 08 */	bge lbl_800C9760
/* 800C975C 000C465C  38 C6 00 10 */	addi r6, r6, 0x10
lbl_800C9760:
/* 800C9760 000C4660  38 A5 FF 7C */	addi r5, r5, -132
/* 800C9764 000C4664  48 00 01 00 */	b lbl_800C9864
lbl_800C9768:
/* 800C9768 000C4668  1C 86 00 38 */	mulli r4, r6, 0x38
/* 800C976C 000C466C  38 C6 00 01 */	addi r6, r6, 1
/* 800C9770 000C4670  2C 06 00 10 */	cmpwi r6, 0x10
/* 800C9774 000C4674  7C 9F 22 14 */	add r4, r31, r4
/* 800C9778 000C4678  A1 04 01 10 */	lhz r8, 0x110(r4)
/* 800C977C 000C467C  A0 E4 01 12 */	lhz r7, 0x112(r4)
/* 800C9780 000C4680  B1 05 FF 7C */	sth r8, -0x84(r5)
/* 800C9784 000C4684  B0 E5 FF 7E */	sth r7, -0x82(r5)
/* 800C9788 000C4688  A1 04 01 14 */	lhz r8, 0x114(r4)
/* 800C978C 000C468C  A0 E4 01 16 */	lhz r7, 0x116(r4)
/* 800C9790 000C4690  B1 05 FF 80 */	sth r8, -0x80(r5)
/* 800C9794 000C4694  B0 E5 FF 82 */	sth r7, -0x7e(r5)
/* 800C9798 000C4698  A1 04 01 18 */	lhz r8, 0x118(r4)
/* 800C979C 000C469C  A0 E4 01 1A */	lhz r7, 0x11a(r4)
/* 800C97A0 000C46A0  B1 05 FF 84 */	sth r8, -0x7c(r5)
/* 800C97A4 000C46A4  B0 E5 FF 86 */	sth r7, -0x7a(r5)
/* 800C97A8 000C46A8  A1 04 01 1C */	lhz r8, 0x11c(r4)
/* 800C97AC 000C46AC  A0 E4 01 1E */	lhz r7, 0x11e(r4)
/* 800C97B0 000C46B0  B1 05 FF 88 */	sth r8, -0x78(r5)
/* 800C97B4 000C46B4  B0 E5 FF 8A */	sth r7, -0x76(r5)
/* 800C97B8 000C46B8  A1 04 01 20 */	lhz r8, 0x120(r4)
/* 800C97BC 000C46BC  A0 E4 01 22 */	lhz r7, 0x122(r4)
/* 800C97C0 000C46C0  B1 05 FF 8C */	sth r8, -0x74(r5)
/* 800C97C4 000C46C4  B0 E5 FF 8E */	sth r7, -0x72(r5)
/* 800C97C8 000C46C8  A1 04 01 24 */	lhz r8, 0x124(r4)
/* 800C97CC 000C46CC  A0 E4 01 26 */	lhz r7, 0x126(r4)
/* 800C97D0 000C46D0  B1 05 FF 90 */	sth r8, -0x70(r5)
/* 800C97D4 000C46D4  B0 E5 FF 92 */	sth r7, -0x6e(r5)
/* 800C97D8 000C46D8  A1 04 01 28 */	lhz r8, 0x128(r4)
/* 800C97DC 000C46DC  A0 E4 01 2A */	lhz r7, 0x12a(r4)
/* 800C97E0 000C46E0  B1 05 FF 94 */	sth r8, -0x6c(r5)
/* 800C97E4 000C46E4  B0 E5 FF 96 */	sth r7, -0x6a(r5)
/* 800C97E8 000C46E8  A1 04 01 2C */	lhz r8, 0x12c(r4)
/* 800C97EC 000C46EC  A0 E4 01 2E */	lhz r7, 0x12e(r4)
/* 800C97F0 000C46F0  B1 05 FF 98 */	sth r8, -0x68(r5)
/* 800C97F4 000C46F4  B0 E5 FF 9A */	sth r7, -0x66(r5)
/* 800C97F8 000C46F8  A1 04 01 30 */	lhz r8, 0x130(r4)
/* 800C97FC 000C46FC  A0 E4 01 32 */	lhz r7, 0x132(r4)
/* 800C9800 000C4700  B1 05 FF 9C */	sth r8, -0x64(r5)
/* 800C9804 000C4704  B0 E5 FF 9E */	sth r7, -0x62(r5)
/* 800C9808 000C4708  A1 04 01 34 */	lhz r8, 0x134(r4)
/* 800C980C 000C470C  A0 E4 01 36 */	lhz r7, 0x136(r4)
/* 800C9810 000C4710  B1 05 FF A0 */	sth r8, -0x60(r5)
/* 800C9814 000C4714  B0 E5 FF A2 */	sth r7, -0x5e(r5)
/* 800C9818 000C4718  A1 04 01 38 */	lhz r8, 0x138(r4)
/* 800C981C 000C471C  A0 E4 01 3A */	lhz r7, 0x13a(r4)
/* 800C9820 000C4720  B1 05 FF A4 */	sth r8, -0x5c(r5)
/* 800C9824 000C4724  B0 E5 FF A6 */	sth r7, -0x5a(r5)
/* 800C9828 000C4728  A1 04 01 3C */	lhz r8, 0x13c(r4)
/* 800C982C 000C472C  A0 E4 01 3E */	lhz r7, 0x13e(r4)
/* 800C9830 000C4730  B1 05 FF A8 */	sth r8, -0x58(r5)
/* 800C9834 000C4734  B0 E5 FF AA */	sth r7, -0x56(r5)
/* 800C9838 000C4738  A1 04 01 40 */	lhz r8, 0x140(r4)
/* 800C983C 000C473C  A0 E4 01 42 */	lhz r7, 0x142(r4)
/* 800C9840 000C4740  B1 05 FF AC */	sth r8, -0x54(r5)
/* 800C9844 000C4744  B0 E5 FF AE */	sth r7, -0x52(r5)
/* 800C9848 000C4748  A0 E4 01 44 */	lhz r7, 0x144(r4)
/* 800C984C 000C474C  A0 84 01 46 */	lhz r4, 0x146(r4)
/* 800C9850 000C4750  B0 E5 FF B0 */	sth r7, -0x50(r5)
/* 800C9854 000C4754  B0 85 FF B2 */	sth r4, -0x4e(r5)
/* 800C9858 000C4758  38 A5 FF 7C */	addi r5, r5, -132
/* 800C985C 000C475C  41 80 00 08 */	blt lbl_800C9864
/* 800C9860 000C4760  38 C0 00 00 */	li r6, 0
lbl_800C9864:
/* 800C9864 000C4764  34 00 FF FF */	addic. r0, r0, -1
/* 800C9868 000C4768  40 82 FF 00 */	bne lbl_800C9768
/* 800C986C 000C476C  1C 06 00 38 */	mulli r0, r6, 0x38
/* 800C9870 000C4770  7E 1F 02 14 */	add r16, r31, r0
/* 800C9874 000C4774  A1 F0 01 3A */	lhz r15, 0x13a(r16)
/* 800C9878 000C4778  A0 10 01 36 */	lhz r0, 0x136(r16)
/* 800C987C 000C477C  91 E1 00 74 */	stw r15, 0x74(r1)
/* 800C9880 000C4780  A1 F0 01 3C */	lhz r15, 0x13c(r16)
/* 800C9884 000C4784  B0 01 00 3E */	sth r0, 0x3e(r1)
/* 800C9888 000C4788  80 01 00 74 */	lwz r0, 0x74(r1)
/* 800C988C 000C478C  91 E1 00 60 */	stw r15, 0x60(r1)
/* 800C9890 000C4790  A1 F0 01 3E */	lhz r15, 0x13e(r16)
/* 800C9894 000C4794  B0 01 00 42 */	sth r0, 0x42(r1)
/* 800C9898 000C4798  80 01 00 60 */	lwz r0, 0x60(r1)
/* 800C989C 000C479C  91 E1 00 64 */	stw r15, 0x64(r1)
/* 800C98A0 000C47A0  A1 F0 01 40 */	lhz r15, 0x140(r16)
/* 800C98A4 000C47A4  B0 01 00 44 */	sth r0, 0x44(r1)
/* 800C98A8 000C47A8  80 01 00 64 */	lwz r0, 0x64(r1)
/* 800C98AC 000C47AC  91 E1 00 68 */	stw r15, 0x68(r1)
/* 800C98B0 000C47B0  A1 F0 01 42 */	lhz r15, 0x142(r16)
/* 800C98B4 000C47B4  B0 01 00 46 */	sth r0, 0x46(r1)
/* 800C98B8 000C47B8  80 01 00 68 */	lwz r0, 0x68(r1)
/* 800C98BC 000C47BC  91 E1 00 6C */	stw r15, 0x6c(r1)
/* 800C98C0 000C47C0  A1 F0 01 44 */	lhz r15, 0x144(r16)
/* 800C98C4 000C47C4  B0 01 00 48 */	sth r0, 0x48(r1)
/* 800C98C8 000C47C8  80 01 00 6C */	lwz r0, 0x6c(r1)
/* 800C98CC 000C47CC  91 E1 00 70 */	stw r15, 0x70(r1)
/* 800C98D0 000C47D0  A2 30 01 10 */	lhz r17, 0x110(r16)
/* 800C98D4 000C47D4  A2 50 01 12 */	lhz r18, 0x112(r16)
/* 800C98D8 000C47D8  A2 70 01 14 */	lhz r19, 0x114(r16)
/* 800C98DC 000C47DC  A2 90 01 16 */	lhz r20, 0x116(r16)
/* 800C98E0 000C47E0  A2 B0 01 18 */	lhz r21, 0x118(r16)
/* 800C98E4 000C47E4  A2 D0 01 1A */	lhz r22, 0x11a(r16)
/* 800C98E8 000C47E8  A2 F0 01 1C */	lhz r23, 0x11c(r16)
/* 800C98EC 000C47EC  A3 10 01 1E */	lhz r24, 0x11e(r16)
/* 800C98F0 000C47F0  A3 30 01 20 */	lhz r25, 0x120(r16)
/* 800C98F4 000C47F4  A3 50 01 22 */	lhz r26, 0x122(r16)
/* 800C98F8 000C47F8  A1 90 01 24 */	lhz r12, 0x124(r16)
/* 800C98FC 000C47FC  A1 70 01 26 */	lhz r11, 0x126(r16)
/* 800C9900 000C4800  A1 50 01 28 */	lhz r10, 0x128(r16)
/* 800C9904 000C4804  A1 30 01 2A */	lhz r9, 0x12a(r16)
/* 800C9908 000C4808  A1 10 01 2C */	lhz r8, 0x12c(r16)
/* 800C990C 000C480C  A0 F0 01 2E */	lhz r7, 0x12e(r16)
/* 800C9910 000C4810  A0 D0 01 30 */	lhz r6, 0x130(r16)
/* 800C9914 000C4814  A0 B0 01 32 */	lhz r5, 0x132(r16)
/* 800C9918 000C4818  A0 90 01 34 */	lhz r4, 0x134(r16)
/* 800C991C 000C481C  A1 D0 01 38 */	lhz r14, 0x138(r16)
/* 800C9920 000C4820  A1 F0 01 46 */	lhz r15, 0x146(r16)
/* 800C9924 000C4824  B0 01 00 4A */	sth r0, 0x4a(r1)
/* 800C9928 000C4828  80 01 00 70 */	lwz r0, 0x70(r1)
/* 800C992C 000C482C  B2 21 00 18 */	sth r17, 0x18(r1)
/* 800C9930 000C4830  B2 41 00 1A */	sth r18, 0x1a(r1)
/* 800C9934 000C4834  B2 61 00 1C */	sth r19, 0x1c(r1)
/* 800C9938 000C4838  B2 81 00 1E */	sth r20, 0x1e(r1)
/* 800C993C 000C483C  B2 A1 00 20 */	sth r21, 0x20(r1)
/* 800C9940 000C4840  B2 C1 00 22 */	sth r22, 0x22(r1)
/* 800C9944 000C4844  B2 E1 00 24 */	sth r23, 0x24(r1)
/* 800C9948 000C4848  B3 01 00 26 */	sth r24, 0x26(r1)
/* 800C994C 000C484C  B3 21 00 28 */	sth r25, 0x28(r1)
/* 800C9950 000C4850  B3 41 00 2A */	sth r26, 0x2a(r1)
/* 800C9954 000C4854  B1 81 00 2C */	sth r12, 0x2c(r1)
/* 800C9958 000C4858  B1 61 00 2E */	sth r11, 0x2e(r1)
/* 800C995C 000C485C  B1 41 00 30 */	sth r10, 0x30(r1)
/* 800C9960 000C4860  B1 21 00 32 */	sth r9, 0x32(r1)
/* 800C9964 000C4864  B1 01 00 34 */	sth r8, 0x34(r1)
/* 800C9968 000C4868  B0 E1 00 36 */	sth r7, 0x36(r1)
/* 800C996C 000C486C  B0 C1 00 38 */	sth r6, 0x38(r1)
/* 800C9970 000C4870  B0 A1 00 3A */	sth r5, 0x3a(r1)
/* 800C9974 000C4874  B0 81 00 3C */	sth r4, 0x3c(r1)
/* 800C9978 000C4878  B1 C1 00 40 */	sth r14, 0x40(r1)
/* 800C997C 000C487C  B0 01 00 4C */	sth r0, 0x4c(r1)
/* 800C9980 000C4880  B1 E1 00 4E */	sth r15, 0x4e(r1)
/* 800C9984 000C4884  48 02 7F 65 */	bl OSRestoreInterrupts
/* 800C9988 000C4888  A1 42 95 EC */	lhz r10, lbl_804C100C-_SDA2_BASE_(r2)
/* 800C998C 000C488C  7F 63 DB 78 */	mr r3, r27
/* 800C9990 000C4890  A1 22 95 EE */	lhz r9, lbl_804C100E-_SDA2_BASE_(r2)
/* 800C9994 000C4894  38 A1 00 10 */	addi r5, r1, 0x10
/* 800C9998 000C4898  A1 02 95 F0 */	lhz r8, lbl_804C1010-_SDA2_BASE_(r2)
/* 800C999C 000C489C  38 80 00 00 */	li r4, 0
/* 800C99A0 000C48A0  A0 E2 95 F4 */	lhz r7, lbl_804C1014-_SDA2_BASE_(r2)
/* 800C99A4 000C48A4  A0 C2 95 F6 */	lhz r6, lbl_804C1016-_SDA2_BASE_(r2)
/* 800C99A8 000C48A8  A0 02 95 F8 */	lhz r0, lbl_804C1018-_SDA2_BASE_(r2)
/* 800C99AC 000C48AC  B1 41 00 10 */	sth r10, 0x10(r1)
/* 800C99B0 000C48B0  B1 21 00 12 */	sth r9, 0x12(r1)
/* 800C99B4 000C48B4  B1 01 00 14 */	sth r8, 0x14(r1)
/* 800C99B8 000C48B8  B0 E1 00 08 */	sth r7, 8(r1)
/* 800C99BC 000C48BC  B0 C1 00 0A */	sth r6, 0xa(r1)
/* 800C99C0 000C48C0  B0 01 00 0C */	sth r0, 0xc(r1)
/* 800C99C4 000C48C4  48 00 3A 85 */	bl WPADGetAccGravityUnit
/* 800C99C8 000C48C8  A8 A1 00 10 */	lha r5, 0x10(r1)
/* 800C99CC 000C48CC  A8 81 00 14 */	lha r4, 0x14(r1)
/* 800C99D0 000C48D0  A8 61 00 12 */	lha r3, 0x12(r1)
/* 800C99D4 000C48D4  7C 04 29 D6 */	mullw r0, r4, r5
/* 800C99D8 000C48D8  7C 00 19 D7 */	mullw. r0, r0, r3
/* 800C99DC 000C48DC  41 82 00 58 */	beq lbl_800C9A34
/* 800C99E0 000C48E0  6C A0 80 00 */	xoris r0, r5, 0x8000
/* 800C99E4 000C48E4  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 800C99E8 000C48E8  90 01 00 54 */	stw r0, 0x54(r1)
/* 800C99EC 000C48EC  6C 80 80 00 */	xoris r0, r4, 0x8000
/* 800C99F0 000C48F0  C8 82 95 D8 */	lfd f4, lbl_804C0FF8-_SDA2_BASE_(r2)
/* 800C99F4 000C48F4  C8 01 00 50 */	lfd f0, 0x50(r1)
/* 800C99F8 000C48F8  90 61 00 5C */	stw r3, 0x5c(r1)
/* 800C99FC 000C48FC  EC 40 20 28 */	fsubs f2, f0, f4
/* 800C9A00 000C4900  C0 62 95 BC */	lfs f3, lbl_804C0FDC-_SDA2_BASE_(r2)
/* 800C9A04 000C4904  90 01 00 54 */	stw r0, 0x54(r1)
/* 800C9A08 000C4908  C8 21 00 58 */	lfd f1, 0x58(r1)
/* 800C9A0C 000C490C  C8 01 00 50 */	lfd f0, 0x50(r1)
/* 800C9A10 000C4910  EC 43 10 24 */	fdivs f2, f3, f2
/* 800C9A14 000C4914  EC 21 20 28 */	fsubs f1, f1, f4
/* 800C9A18 000C4918  D0 5F 04 DC */	stfs f2, 0x4dc(r31)
/* 800C9A1C 000C491C  EC 00 20 28 */	fsubs f0, f0, f4
/* 800C9A20 000C4920  EC 23 08 24 */	fdivs f1, f3, f1
/* 800C9A24 000C4924  EC 03 00 24 */	fdivs f0, f3, f0
/* 800C9A28 000C4928  D0 3F 04 E0 */	stfs f1, 0x4e0(r31)
/* 800C9A2C 000C492C  D0 1F 04 E4 */	stfs f0, 0x4e4(r31)
/* 800C9A30 000C4930  48 00 00 14 */	b lbl_800C9A44
lbl_800C9A34:
/* 800C9A34 000C4934  C0 02 95 FC */	lfs f0, lbl_804C101C-_SDA2_BASE_(r2)
/* 800C9A38 000C4938  D0 1F 04 DC */	stfs f0, 0x4dc(r31)
/* 800C9A3C 000C493C  D0 1F 04 E0 */	stfs f0, 0x4e0(r31)
/* 800C9A40 000C4940  D0 1F 04 E4 */	stfs f0, 0x4e4(r31)
lbl_800C9A44:
/* 800C9A44 000C4944  7F 63 DB 78 */	mr r3, r27
/* 800C9A48 000C4948  38 A1 00 08 */	addi r5, r1, 8
/* 800C9A4C 000C494C  38 80 00 01 */	li r4, 1
/* 800C9A50 000C4950  48 00 39 F9 */	bl WPADGetAccGravityUnit
/* 800C9A54 000C4954  A8 A1 00 08 */	lha r5, 8(r1)
/* 800C9A58 000C4958  A8 81 00 0C */	lha r4, 0xc(r1)
/* 800C9A5C 000C495C  A8 61 00 0A */	lha r3, 0xa(r1)
/* 800C9A60 000C4960  7C 04 29 D6 */	mullw r0, r4, r5
/* 800C9A64 000C4964  7C 00 19 D7 */	mullw. r0, r0, r3
/* 800C9A68 000C4968  41 82 00 58 */	beq lbl_800C9AC0
/* 800C9A6C 000C496C  6C A0 80 00 */	xoris r0, r5, 0x8000
/* 800C9A70 000C4970  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 800C9A74 000C4974  90 01 00 5C */	stw r0, 0x5c(r1)
/* 800C9A78 000C4978  6C 80 80 00 */	xoris r0, r4, 0x8000
/* 800C9A7C 000C497C  C8 82 95 D8 */	lfd f4, lbl_804C0FF8-_SDA2_BASE_(r2)
/* 800C9A80 000C4980  C8 01 00 58 */	lfd f0, 0x58(r1)
/* 800C9A84 000C4984  90 61 00 54 */	stw r3, 0x54(r1)
/* 800C9A88 000C4988  EC 40 20 28 */	fsubs f2, f0, f4
/* 800C9A8C 000C498C  C0 62 95 BC */	lfs f3, lbl_804C0FDC-_SDA2_BASE_(r2)
/* 800C9A90 000C4990  90 01 00 5C */	stw r0, 0x5c(r1)
/* 800C9A94 000C4994  C8 21 00 50 */	lfd f1, 0x50(r1)
/* 800C9A98 000C4998  C8 01 00 58 */	lfd f0, 0x58(r1)
/* 800C9A9C 000C499C  EC 43 10 24 */	fdivs f2, f3, f2
/* 800C9AA0 000C49A0  EC 21 20 28 */	fsubs f1, f1, f4
/* 800C9AA4 000C49A4  D0 5F 04 E8 */	stfs f2, 0x4e8(r31)
/* 800C9AA8 000C49A8  EC 00 20 28 */	fsubs f0, f0, f4
/* 800C9AAC 000C49AC  EC 23 08 24 */	fdivs f1, f3, f1
/* 800C9AB0 000C49B0  EC 03 00 24 */	fdivs f0, f3, f0
/* 800C9AB4 000C49B4  D0 3F 04 EC */	stfs f1, 0x4ec(r31)
/* 800C9AB8 000C49B8  D0 1F 04 F0 */	stfs f0, 0x4f0(r31)
/* 800C9ABC 000C49BC  48 00 00 14 */	b lbl_800C9AD0
lbl_800C9AC0:
/* 800C9AC0 000C49C0  C0 02 96 00 */	lfs f0, lbl_804C1020-_SDA2_BASE_(r2)
/* 800C9AC4 000C49C4  D0 1F 04 E8 */	stfs f0, 0x4e8(r31)
/* 800C9AC8 000C49C8  D0 1F 04 EC */	stfs f0, 0x4ec(r31)
/* 800C9ACC 000C49CC  D0 1F 04 F0 */	stfs f0, 0x4f0(r31)
lbl_800C9AD0:
/* 800C9AD0 000C49D0  1C 1E 00 84 */	mulli r0, r30, 0x84
/* 800C9AD4 000C49D4  3C 60 00 01 */	lis r3, 0x0000FFFF@ha
/* 800C9AD8 000C49D8  7F C6 F3 78 */	mr r6, r30
/* 800C9ADC 000C49DC  39 23 FF FF */	addi r9, r3, 0x0000FFFF@l
/* 800C9AE0 000C49E0  7D DC 02 14 */	add r14, r28, r0
/* 800C9AE4 000C49E4  38 80 00 FD */	li r4, 0xfd
/* 800C9AE8 000C49E8  7D 28 4B 78 */	mr r8, r9
/* 800C9AEC 000C49EC  7D 27 4B 78 */	mr r7, r9
/* 800C9AF0 000C49F0  38 AE FF 7C */	addi r5, r14, -132
lbl_800C9AF4:
/* 800C9AF4 000C49F4  28 06 00 01 */	cmplwi r6, 1
/* 800C9AF8 000C49F8  38 A5 FF 7C */	addi r5, r5, -132
/* 800C9AFC 000C49FC  40 81 00 0C */	ble lbl_800C9B08
/* 800C9B00 000C4A00  7C A3 2B 78 */	mr r3, r5
/* 800C9B04 000C4A04  48 00 00 08 */	b lbl_800C9B0C
lbl_800C9B08:
/* 800C9B08 000C4A08  38 61 00 18 */	addi r3, r1, 0x18
lbl_800C9B0C:
/* 800C9B0C 000C4A0C  88 03 00 29 */	lbz r0, 0x29(r3)
/* 800C9B10 000C4A10  7C 00 07 74 */	extsb r0, r0
/* 800C9B14 000C4A14  2C 00 FF FE */	cmpwi r0, -2
/* 800C9B18 000C4A18  41 82 00 54 */	beq lbl_800C9B6C
/* 800C9B1C 000C4A1C  40 80 00 10 */	bge lbl_800C9B2C
/* 800C9B20 000C4A20  2C 00 FF F9 */	cmpwi r0, -7
/* 800C9B24 000C4A24  41 82 00 48 */	beq lbl_800C9B6C
/* 800C9B28 000C4A28  48 00 00 48 */	b lbl_800C9B70
lbl_800C9B2C:
/* 800C9B2C 000C4A2C  2C 00 00 00 */	cmpwi r0, 0
/* 800C9B30 000C4A30  41 82 00 08 */	beq lbl_800C9B38
/* 800C9B34 000C4A34  48 00 00 3C */	b lbl_800C9B70
lbl_800C9B38:
/* 800C9B38 000C4A38  88 83 00 28 */	lbz r4, 0x28(r3)
/* 800C9B3C 000C4A3C  28 04 00 01 */	cmplwi r4, 1
/* 800C9B40 000C4A40  40 82 00 10 */	bne lbl_800C9B50
/* 800C9B44 000C4A44  A1 03 00 00 */	lhz r8, 0(r3)
/* 800C9B48 000C4A48  39 20 00 00 */	li r9, 0
/* 800C9B4C 000C4A4C  48 00 00 20 */	b lbl_800C9B6C
lbl_800C9B50:
/* 800C9B50 000C4A50  28 04 00 02 */	cmplwi r4, 2
/* 800C9B54 000C4A54  40 82 00 10 */	bne lbl_800C9B64
/* 800C9B58 000C4A58  A1 23 00 2A */	lhz r9, 0x2a(r3)
/* 800C9B5C 000C4A5C  39 00 00 00 */	li r8, 0
/* 800C9B60 000C4A60  48 00 00 0C */	b lbl_800C9B6C
lbl_800C9B64:
/* 800C9B64 000C4A64  39 20 00 00 */	li r9, 0
/* 800C9B68 000C4A68  39 00 00 00 */	li r8, 0
lbl_800C9B6C:
/* 800C9B6C 000C4A6C  A0 E3 00 00 */	lhz r7, 0(r3)
lbl_800C9B70:
/* 800C9B70 000C4A70  34 C6 FF FF */	addic. r6, r6, -1
/* 800C9B74 000C4A74  40 82 FF 80 */	bne lbl_800C9AF4
/* 800C9B78 000C4A78  28 07 FF FF */	cmplwi r7, 0xffff
/* 800C9B7C 000C4A7C  40 82 00 24 */	bne lbl_800C9BA0
lbl_800C9B80:
/* 800C9B80 000C4A80  7F 83 E3 78 */	mr r3, r28
/* 800C9B84 000C4A84  7F E4 FB 78 */	mr r4, r31
/* 800C9B88 000C4A88  38 A0 00 84 */	li r5, 0x84
/* 800C9B8C 000C4A8C  4B F3 A4 75 */	bl memcpy
/* 800C9B90 000C4A90  37 DE FF FF */	addic. r30, r30, -1
/* 800C9B94 000C4A94  3B 9C 00 84 */	addi r28, r28, 0x84
/* 800C9B98 000C4A98  40 82 FF E8 */	bne lbl_800C9B80
/* 800C9B9C 000C4A9C  48 00 01 5C */	b lbl_800C9CF8
lbl_800C9BA0:
/* 800C9BA0 000C4AA0  28 08 FF FF */	cmplwi r8, 0xffff
/* 800C9BA4 000C4AA4  40 82 00 08 */	bne lbl_800C9BAC
/* 800C9BA8 000C4AA8  81 1F 00 00 */	lwz r8, 0(r31)
lbl_800C9BAC:
/* 800C9BAC 000C4AAC  28 09 FF FF */	cmplwi r9, 0xffff
/* 800C9BB0 000C4AB0  40 82 00 08 */	bne lbl_800C9BB8
/* 800C9BB4 000C4AB4  81 3F 00 60 */	lwz r9, 0x60(r31)
lbl_800C9BB8:
/* 800C9BB8 000C4AB8  70 E0 9F FF */	andi. r0, r7, 0x9fff
/* 800C9BBC 000C4ABC  80 7F 00 00 */	lwz r3, 0(r31)
/* 800C9BC0 000C4AC0  51 00 04 64 */	rlwimi r0, r8, 0, 0x11, 0x12
/* 800C9BC4 000C4AC4  28 04 00 02 */	cmplwi r4, 2
/* 800C9BC8 000C4AC8  54 65 04 3E */	clrlwi r5, r3, 0x10
/* 800C9BCC 000C4ACC  7C 03 2A 78 */	xor r3, r0, r5
/* 800C9BD0 000C4AD0  90 1F 00 00 */	stw r0, 0(r31)
/* 800C9BD4 000C4AD4  7C 60 00 38 */	and r0, r3, r0
/* 800C9BD8 000C4AD8  90 1F 00 04 */	stw r0, 4(r31)
/* 800C9BDC 000C4ADC  7C 60 28 38 */	and r0, r3, r5
/* 800C9BE0 000C4AE0  90 1F 00 08 */	stw r0, 8(r31)
/* 800C9BE4 000C4AE4  40 82 00 28 */	bne lbl_800C9C0C
/* 800C9BE8 000C4AE8  80 7F 00 60 */	lwz r3, 0x60(r31)
/* 800C9BEC 000C4AEC  55 20 04 3E */	clrlwi r0, r9, 0x10
/* 800C9BF0 000C4AF0  54 65 04 3E */	clrlwi r5, r3, 0x10
/* 800C9BF4 000C4AF4  90 1F 00 60 */	stw r0, 0x60(r31)
/* 800C9BF8 000C4AF8  7C 03 2A 78 */	xor r3, r0, r5
/* 800C9BFC 000C4AFC  7C 60 00 38 */	and r0, r3, r0
/* 800C9C00 000C4B00  90 1F 00 64 */	stw r0, 0x64(r31)
/* 800C9C04 000C4B04  7C 60 28 38 */	and r0, r3, r5
/* 800C9C08 000C4B08  90 1F 00 68 */	stw r0, 0x68(r31)
lbl_800C9C0C:
/* 800C9C0C 000C4B0C  7F E3 FB 78 */	mr r3, r31
/* 800C9C10 000C4B10  7F A5 EB 78 */	mr r5, r29
/* 800C9C14 000C4B14  4B FF DA 61 */	bl calc_button_repeat
/* 800C9C18 000C4B18  7F CF F3 78 */	mr r15, r30
/* 800C9C1C 000C4B1C  39 CE FF 7C */	addi r14, r14, -132
/* 800C9C20 000C4B20  3A 40 00 01 */	li r18, 1
/* 800C9C24 000C4B24  3A 20 00 00 */	li r17, 0
/* 800C9C28 000C4B28  3A 00 00 10 */	li r16, 0x10
lbl_800C9C2C:
/* 800C9C2C 000C4B2C  28 0F 00 01 */	cmplwi r15, 1
/* 800C9C30 000C4B30  39 CE FF 7C */	addi r14, r14, -132
/* 800C9C34 000C4B34  40 81 00 0C */	ble lbl_800C9C40
/* 800C9C38 000C4B38  7D D3 73 78 */	mr r19, r14
/* 800C9C3C 000C4B3C  48 00 00 08 */	b lbl_800C9C44
lbl_800C9C40:
/* 800C9C40 000C4B40  3A 61 00 18 */	addi r19, r1, 0x18
lbl_800C9C44:
/* 800C9C44 000C4B44  88 13 00 29 */	lbz r0, 0x29(r19)
/* 800C9C48 000C4B48  98 1F 00 5D */	stb r0, 0x5d(r31)
/* 800C9C4C 000C4B4C  88 93 00 28 */	lbz r4, 0x28(r19)
/* 800C9C50 000C4B50  88 1F 00 5C */	lbz r0, 0x5c(r31)
/* 800C9C54 000C4B54  7C 00 20 40 */	cmplw r0, r4
/* 800C9C58 000C4B58  41 82 00 20 */	beq lbl_800C9C78
/* 800C9C5C 000C4B5C  88 73 00 29 */	lbz r3, 0x29(r19)
/* 800C9C60 000C4B60  38 03 00 02 */	addi r0, r3, 2
/* 800C9C64 000C4B64  54 00 06 3E */	clrlwi r0, r0, 0x18
/* 800C9C68 000C4B68  28 00 00 02 */	cmplwi r0, 2
/* 800C9C6C 000C4B6C  41 81 00 0C */	bgt lbl_800C9C78
/* 800C9C70 000C4B70  98 9F 00 5C */	stb r4, 0x5c(r31)
/* 800C9C74 000C4B74  9A 5F 05 1E */	stb r18, 0x51e(r31)
lbl_800C9C78:
/* 800C9C78 000C4B78  88 13 00 36 */	lbz r0, 0x36(r19)
/* 800C9C7C 000C4B7C  98 1F 00 5F */	stb r0, 0x5f(r31)
/* 800C9C80 000C4B80  88 13 00 29 */	lbz r0, 0x29(r19)
/* 800C9C84 000C4B84  7C 00 07 75 */	extsb. r0, r0
/* 800C9C88 000C4B88  41 82 00 14 */	beq lbl_800C9C9C
/* 800C9C8C 000C4B8C  40 80 00 38 */	bge lbl_800C9CC4
/* 800C9C90 000C4B90  2C 00 FF F9 */	cmpwi r0, -7
/* 800C9C94 000C4B94  41 82 00 14 */	beq lbl_800C9CA8
/* 800C9C98 000C4B98  48 00 00 2C */	b lbl_800C9CC4
lbl_800C9C9C:
/* 800C9C9C 000C4B9C  7F E3 FB 78 */	mr r3, r31
/* 800C9CA0 000C4BA0  7E 64 9B 78 */	mr r4, r19
/* 800C9CA4 000C4BA4  4B FF F6 E9 */	bl read_kpad_stick
lbl_800C9CA8:
/* 800C9CA8 000C4BA8  7F E3 FB 78 */	mr r3, r31
/* 800C9CAC 000C4BAC  7E 64 9B 78 */	mr r4, r19
/* 800C9CB0 000C4BB0  4B FF DE 11 */	bl read_kpad_acc
/* 800C9CB4 000C4BB4  7F E3 FB 78 */	mr r3, r31
/* 800C9CB8 000C4BB8  7E 64 9B 78 */	mr r4, r19
/* 800C9CBC 000C4BBC  4B FF EF 2D */	bl read_kpad_dpd
/* 800C9CC0 000C4BC0  48 00 00 08 */	b lbl_800C9CC8
lbl_800C9CC4:
/* 800C9CC4 000C4BC4  9A 3F 00 5E */	stb r17, 0x5e(r31)
lbl_800C9CC8:
/* 800C9CC8 000C4BC8  38 AE 00 80 */	addi r5, r14, 0x80
/* 800C9CCC 000C4BCC  38 9F FF FC */	addi r4, r31, -4
/* 800C9CD0 000C4BD0  7E 09 03 A6 */	mtctr r16
lbl_800C9CD4:
/* 800C9CD4 000C4BD4  80 64 00 04 */	lwz r3, 4(r4)
/* 800C9CD8 000C4BD8  84 04 00 08 */	lwzu r0, 8(r4)
/* 800C9CDC 000C4BDC  90 65 00 04 */	stw r3, 4(r5)
/* 800C9CE0 000C4BE0  94 05 00 08 */	stwu r0, 8(r5)
/* 800C9CE4 000C4BE4  42 00 FF F0 */	bdnz lbl_800C9CD4
/* 800C9CE8 000C4BE8  80 04 00 04 */	lwz r0, 4(r4)
/* 800C9CEC 000C4BEC  35 EF FF FF */	addic. r15, r15, -1
/* 800C9CF0 000C4BF0  90 05 00 04 */	stw r0, 4(r5)
/* 800C9CF4 000C4BF4  40 82 FF 38 */	bne lbl_800C9C2C
lbl_800C9CF8:
/* 800C9CF8 000C4BF8  38 00 00 00 */	li r0, 0
/* 800C9CFC 000C4BFC  7F C3 F3 78 */	mr r3, r30
/* 800C9D00 000C4C00  98 1F 05 1C */	stb r0, 0x51c(r31)
lbl_800C9D04:
/* 800C9D04 000C4C04  39 61 00 C0 */	addi r11, r1, 0xc0
/* 800C9D08 000C4C08  4B FE 80 55 */	bl _restgpr_14
/* 800C9D0C 000C4C0C  80 01 00 C4 */	lwz r0, 0xc4(r1)
/* 800C9D10 000C4C10  7C 08 03 A6 */	mtlr r0
/* 800C9D14 000C4C14  38 21 00 C0 */	addi r1, r1, 0xc0
/* 800C9D18 000C4C18  4E 80 00 20 */	blr 

.global KPADInit
KPADInit:
/* 800C9D1C 000C4C1C  94 21 FF 70 */	stwu r1, -0x90(r1)
/* 800C9D20 000C4C20  7C 08 02 A6 */	mflr r0
/* 800C9D24 000C4C24  90 01 00 94 */	stw r0, 0x94(r1)
/* 800C9D28 000C4C28  DB E1 00 80 */	stfd f31, 0x80(r1)
/* 800C9D2C 000C4C2C  F3 E1 00 88 */	psq_st f31, 136(r1), 0, qr0
/* 800C9D30 000C4C30  DB C1 00 70 */	stfd f30, 0x70(r1)
/* 800C9D34 000C4C34  F3 C1 00 78 */	psq_st f30, 120(r1), 0, qr0
/* 800C9D38 000C4C38  DB A1 00 60 */	stfd f29, 0x60(r1)
/* 800C9D3C 000C4C3C  F3 A1 00 68 */	psq_st f29, 104(r1), 0, qr0
/* 800C9D40 000C4C40  DB 81 00 50 */	stfd f28, 0x50(r1)
/* 800C9D44 000C4C44  F3 81 00 58 */	psq_st f28, 88(r1), 0, qr0
/* 800C9D48 000C4C48  DB 61 00 40 */	stfd f27, 0x40(r1)
/* 800C9D4C 000C4C4C  F3 61 00 48 */	psq_st f27, 72(r1), 0, qr0
/* 800C9D50 000C4C50  DB 41 00 30 */	stfd f26, 0x30(r1)
/* 800C9D54 000C4C54  F3 41 00 38 */	psq_st f26, 56(r1), 0, qr0
/* 800C9D58 000C4C58  39 61 00 30 */	addi r11, r1, 0x30
/* 800C9D5C 000C4C5C  4B FE 7F E1 */	bl _savegpr_25
/* 800C9D60 000C4C60  48 00 25 79 */	bl WPADInit
lbl_800C9D64:
/* 800C9D64 000C4C64  48 00 25 E9 */	bl WPADGetStatus
/* 800C9D68 000C4C68  2C 03 00 03 */	cmpwi r3, 3
/* 800C9D6C 000C4C6C  40 82 FF F8 */	bne lbl_800C9D64
/* 800C9D70 000C4C70  3F 60 80 41 */	lis r27, inside_kpads@ha
/* 800C9D74 000C4C74  38 80 00 00 */	li r4, 0
/* 800C9D78 000C4C78  38 7B E1 58 */	addi r3, r27, inside_kpads@l
/* 800C9D7C 000C4C7C  38 A0 14 90 */	li r5, 0x1490
/* 800C9D80 000C4C80  4B F3 A3 85 */	bl memset
/* 800C9D84 000C4C84  48 00 61 8D */	bl WPADGetDpdSensitivity
/* 800C9D88 000C4C88  54 63 06 3E */	clrlwi r3, r3, 0x18
/* 800C9D8C 000C4C8C  3C 00 43 30 */	lis r0, 0x4330
/* 800C9D90 000C4C90  90 61 00 0C */	stw r3, 0xc(r1)
/* 800C9D94 000C4C94  3C 60 00 01 */	lis r3, 0x00009C40@ha
/* 800C9D98 000C4C98  3B 5B E1 58 */	addi r26, r27, -7848
/* 800C9D9C 000C4C9C  C8 22 96 08 */	lfd f1, lbl_804C1028-_SDA2_BASE_(r2)
/* 800C9DA0 000C4CA0  90 01 00 08 */	stw r0, 8(r1)
/* 800C9DA4 000C4CA4  3B A3 9C 40 */	addi r29, r3, 0x00009C40@l
/* 800C9DA8 000C4CA8  C3 E2 95 BC */	lfs f31, lbl_804C0FDC-_SDA2_BASE_(r2)
/* 800C9DAC 000C4CAC  3B 20 00 00 */	li r25, 0
/* 800C9DB0 000C4CB0  C8 01 00 08 */	lfd f0, 8(r1)
/* 800C9DB4 000C4CB4  3B E0 FF FF */	li r31, -1
/* 800C9DB8 000C4CB8  C3 82 95 A8 */	lfs f28, lbl_804C0FC8-_SDA2_BASE_(r2)
/* 800C9DBC 000C4CBC  3B C0 00 00 */	li r30, 0
/* 800C9DC0 000C4CC0  EC 00 08 28 */	fsubs f0, f0, f1
/* 800C9DC4 000C4CC4  C3 A2 95 C8 */	lfs f29, lbl_804C0FE8-_SDA2_BASE_(r2)
/* 800C9DC8 000C4CC8  C3 C2 95 CC */	lfs f30, lbl_804C0FEC-_SDA2_BASE_(r2)
/* 800C9DCC 000C4CCC  3B 60 00 01 */	li r27, 1
/* 800C9DD0 000C4CD0  3B 80 00 FD */	li r28, 0xfd
/* 800C9DD4 000C4CD4  EC 1F 00 2A */	fadds f0, f31, f0
/* 800C9DD8 000C4CD8  D0 0D 82 10 */	stfs f0, kp_err_dist_max-_SDA_BASE_(r13)
lbl_800C9DDC:
/* 800C9DDC 000C4CDC  9B 7A 05 20 */	stb r27, 0x520(r26)
/* 800C9DE0 000C4CE0  C3 42 95 BC */	lfs f26, lbl_804C0FDC-_SDA2_BASE_(r2)
/* 800C9DE4 000C4CE4  9B DA 05 21 */	stb r30, 0x521(r26)
/* 800C9DE8 000C4CE8  C3 62 95 C4 */	lfs f27, lbl_804C0FE4-_SDA2_BASE_(r2)
/* 800C9DEC 000C4CEC  EC 3A 06 B2 */	fmuls f1, f26, f26
/* 800C9DF0 000C4CF0  9B 9A 00 5C */	stb r28, 0x5c(r26)
/* 800C9DF4 000C4CF4  EC 1B 06 F2 */	fmuls f0, f27, f27
/* 800C9DF8 000C4CF8  C0 4D 81 E4 */	lfs f2, idist_org-_SDA_BASE_(r13)
/* 800C9DFC 000C4CFC  9B DA 00 5F */	stb r30, 0x5f(r26)
/* 800C9E00 000C4D00  80 6D 81 E8 */	lwz r3, iaccXY_nrm_hori-_SDA_BASE_(r13)
/* 800C9E04 000C4D04  D0 5A 00 A4 */	stfs f2, 0xa4(r26)
/* 800C9E08 000C4D08  EC 21 00 2A */	fadds f1, f1, f0
/* 800C9E0C 000C4D0C  80 0D 81 EC */	lwz r0, (iaccXY_nrm_hori + 4)-_SDA_BASE_(r13)
/* 800C9E10 000C4D10  90 7A 00 A8 */	stw r3, 0xa8(r26)
/* 800C9E14 000C4D14  80 6D 81 F0 */	lwz r3, isec_nrm_hori-_SDA_BASE_(r13)
/* 800C9E18 000C4D18  90 1A 00 AC */	stw r0, 0xac(r26)
/* 800C9E1C 000C4D1C  80 0D 81 F4 */	lwz r0, (isec_nrm_hori + 4)-_SDA_BASE_(r13)
/* 800C9E20 000C4D20  90 7A 00 B0 */	stw r3, 0xb0(r26)
/* 800C9E24 000C4D24  80 6D 9A 28 */	lwz r3, icenter_org-_SDA_BASE_(r13)
/* 800C9E28 000C4D28  90 1A 00 B4 */	stw r0, 0xb4(r26)
/* 800C9E2C 000C4D2C  80 0D 9A 2C */	lwz r0, (icenter_org + 4)-_SDA_BASE_(r13)
/* 800C9E30 000C4D30  90 7A 00 B8 */	stw r3, 0xb8(r26)
/* 800C9E34 000C4D34  90 1A 00 BC */	stw r0, 0xbc(r26)
/* 800C9E38 000C4D38  4B FF 72 99 */	bl sqrt
/* 800C9E3C 000C4D3C  C0 1A 00 B8 */	lfs f0, 0xb8(r26)
/* 800C9E40 000C4D40  FC 20 08 18 */	frsp f1, f1
/* 800C9E44 000C4D44  FC 00 E0 40 */	fcmpo cr0, f0, f28
/* 800C9E48 000C4D48  40 80 00 0C */	bge lbl_800C9E54
/* 800C9E4C 000C4D4C  EF 5A 00 2A */	fadds f26, f26, f0
/* 800C9E50 000C4D50  48 00 00 08 */	b lbl_800C9E58
lbl_800C9E54:
/* 800C9E54 000C4D54  EF 5A 00 28 */	fsubs f26, f26, f0
lbl_800C9E58:
/* 800C9E58 000C4D58  C0 1A 00 BC */	lfs f0, 0xbc(r26)
/* 800C9E5C 000C4D5C  FC 00 E0 40 */	fcmpo cr0, f0, f28
/* 800C9E60 000C4D60  40 80 00 0C */	bge lbl_800C9E6C
/* 800C9E64 000C4D64  EF 7B 00 2A */	fadds f27, f27, f0
/* 800C9E68 000C4D68  48 00 00 08 */	b lbl_800C9E70
lbl_800C9E6C:
/* 800C9E6C 000C4D6C  EF 7B 00 28 */	fsubs f27, f27, f0
lbl_800C9E70:
/* 800C9E70 000C4D70  FC 1A D8 40 */	fcmpo cr0, f26, f27
/* 800C9E74 000C4D74  40 80 00 08 */	bge lbl_800C9E7C
/* 800C9E78 000C4D78  48 00 00 08 */	b lbl_800C9E80
lbl_800C9E7C:
/* 800C9E7C 000C4D7C  FF 40 D8 90 */	fmr f26, f27
lbl_800C9E80:
/* 800C9E80 000C4D80  EC 01 D0 24 */	fdivs f0, f1, f26
/* 800C9E84 000C4D84  D0 1A 00 C0 */	stfs f0, 0xc0(r26)
/* 800C9E88 000C4D88  D3 9A 00 9C */	stfs f28, 0x9c(r26)
/* 800C9E8C 000C4D8C  D3 9A 00 94 */	stfs f28, 0x94(r26)
/* 800C9E90 000C4D90  D3 9A 00 8C */	stfs f28, 0x8c(r26)
/* 800C9E94 000C4D94  D3 9A 00 84 */	stfs f28, 0x84(r26)
/* 800C9E98 000C4D98  D3 FA 00 A0 */	stfs f31, 0xa0(r26)
/* 800C9E9C 000C4D9C  D3 FA 00 98 */	stfs f31, 0x98(r26)
/* 800C9EA0 000C4DA0  D3 FA 00 90 */	stfs f31, 0x90(r26)
/* 800C9EA4 000C4DA4  D3 FA 00 88 */	stfs f31, 0x88(r26)
/* 800C9EA8 000C4DA8  B3 BA 04 D0 */	sth r29, 0x4d0(r26)
/* 800C9EAC 000C4DAC  B3 DA 04 D2 */	sth r30, 0x4d2(r26)
/* 800C9EB0 000C4DB0  B3 DA 04 CC */	sth r30, 0x4cc(r26)
/* 800C9EB4 000C4DB4  B3 BA 04 CE */	sth r29, 0x4ce(r26)
/* 800C9EB8 000C4DB8  B3 DA 04 D4 */	sth r30, 0x4d4(r26)
/* 800C9EBC 000C4DBC  B3 BA 04 D6 */	sth r29, 0x4d6(r26)
/* 800C9EC0 000C4DC0  48 00 25 11 */	bl WPADGetSensorBarPosition
/* 800C9EC4 000C4DC4  54 60 06 3E */	clrlwi r0, r3, 0x18
/* 800C9EC8 000C4DC8  28 00 00 01 */	cmplwi r0, 1
/* 800C9ECC 000C4DCC  40 82 00 74 */	bne lbl_800C9F40
/* 800C9ED0 000C4DD0  C3 42 95 BC */	lfs f26, lbl_804C0FDC-_SDA2_BASE_(r2)
/* 800C9ED4 000C4DD4  C3 62 95 C4 */	lfs f27, lbl_804C0FE4-_SDA2_BASE_(r2)
/* 800C9ED8 000C4DD8  EC 3A 06 B2 */	fmuls f1, f26, f26
/* 800C9EDC 000C4DDC  D3 9A 00 B8 */	stfs f28, 0xb8(r26)
/* 800C9EE0 000C4DE0  EC 1B 06 F2 */	fmuls f0, f27, f27
/* 800C9EE4 000C4DE4  D3 BA 00 BC */	stfs f29, 0xbc(r26)
/* 800C9EE8 000C4DE8  EC 21 00 2A */	fadds f1, f1, f0
/* 800C9EEC 000C4DEC  4B FF 71 E5 */	bl sqrt
/* 800C9EF0 000C4DF0  C0 1A 00 B8 */	lfs f0, 0xb8(r26)
/* 800C9EF4 000C4DF4  FC 20 08 18 */	frsp f1, f1
/* 800C9EF8 000C4DF8  FC 00 E0 40 */	fcmpo cr0, f0, f28
/* 800C9EFC 000C4DFC  40 80 00 0C */	bge lbl_800C9F08
/* 800C9F00 000C4E00  EF 5A 00 2A */	fadds f26, f26, f0
/* 800C9F04 000C4E04  48 00 00 08 */	b lbl_800C9F0C
lbl_800C9F08:
/* 800C9F08 000C4E08  EF 5A 00 28 */	fsubs f26, f26, f0
lbl_800C9F0C:
/* 800C9F0C 000C4E0C  C0 1A 00 BC */	lfs f0, 0xbc(r26)
/* 800C9F10 000C4E10  FC 00 E0 40 */	fcmpo cr0, f0, f28
/* 800C9F14 000C4E14  40 80 00 0C */	bge lbl_800C9F20
/* 800C9F18 000C4E18  EF 7B 00 2A */	fadds f27, f27, f0
/* 800C9F1C 000C4E1C  48 00 00 08 */	b lbl_800C9F24
lbl_800C9F20:
/* 800C9F20 000C4E20  EF 7B 00 28 */	fsubs f27, f27, f0
lbl_800C9F24:
/* 800C9F24 000C4E24  FC 1A D8 40 */	fcmpo cr0, f26, f27
/* 800C9F28 000C4E28  40 80 00 08 */	bge lbl_800C9F30
/* 800C9F2C 000C4E2C  48 00 00 08 */	b lbl_800C9F34
lbl_800C9F30:
/* 800C9F30 000C4E30  FF 40 D8 90 */	fmr f26, f27
lbl_800C9F34:
/* 800C9F34 000C4E34  EC 01 D0 24 */	fdivs f0, f1, f26
/* 800C9F38 000C4E38  D0 1A 00 C0 */	stfs f0, 0xc0(r26)
/* 800C9F3C 000C4E3C  48 00 00 70 */	b lbl_800C9FAC
lbl_800C9F40:
/* 800C9F40 000C4E40  C3 42 95 BC */	lfs f26, lbl_804C0FDC-_SDA2_BASE_(r2)
/* 800C9F44 000C4E44  C3 62 95 C4 */	lfs f27, lbl_804C0FE4-_SDA2_BASE_(r2)
/* 800C9F48 000C4E48  EC 3A 06 B2 */	fmuls f1, f26, f26
/* 800C9F4C 000C4E4C  D3 9A 00 B8 */	stfs f28, 0xb8(r26)
/* 800C9F50 000C4E50  EC 1B 06 F2 */	fmuls f0, f27, f27
/* 800C9F54 000C4E54  D3 DA 00 BC */	stfs f30, 0xbc(r26)
/* 800C9F58 000C4E58  EC 21 00 2A */	fadds f1, f1, f0
/* 800C9F5C 000C4E5C  4B FF 71 75 */	bl sqrt
/* 800C9F60 000C4E60  C0 1A 00 B8 */	lfs f0, 0xb8(r26)
/* 800C9F64 000C4E64  FC 20 08 18 */	frsp f1, f1
/* 800C9F68 000C4E68  FC 00 E0 40 */	fcmpo cr0, f0, f28
/* 800C9F6C 000C4E6C  40 80 00 0C */	bge lbl_800C9F78
/* 800C9F70 000C4E70  EF 5A 00 2A */	fadds f26, f26, f0
/* 800C9F74 000C4E74  48 00 00 08 */	b lbl_800C9F7C
lbl_800C9F78:
/* 800C9F78 000C4E78  EF 5A 00 28 */	fsubs f26, f26, f0
lbl_800C9F7C:
/* 800C9F7C 000C4E7C  C0 1A 00 BC */	lfs f0, 0xbc(r26)
/* 800C9F80 000C4E80  FC 00 E0 40 */	fcmpo cr0, f0, f28
/* 800C9F84 000C4E84  40 80 00 0C */	bge lbl_800C9F90
/* 800C9F88 000C4E88  EF 7B 00 2A */	fadds f27, f27, f0
/* 800C9F8C 000C4E8C  48 00 00 08 */	b lbl_800C9F94
lbl_800C9F90:
/* 800C9F90 000C4E90  EF 7B 00 28 */	fsubs f27, f27, f0
lbl_800C9F94:
/* 800C9F94 000C4E94  FC 1A D8 40 */	fcmpo cr0, f26, f27
/* 800C9F98 000C4E98  40 80 00 08 */	bge lbl_800C9FA0
/* 800C9F9C 000C4E9C  48 00 00 08 */	b lbl_800C9FA4
lbl_800C9FA0:
/* 800C9FA0 000C4EA0  FF 40 D8 90 */	fmr f26, f27
lbl_800C9FA4:
/* 800C9FA4 000C4EA4  EC 01 D0 24 */	fdivs f0, f1, f26
/* 800C9FA8 000C4EA8  D0 1A 00 C0 */	stfs f0, 0xc0(r26)
lbl_800C9FAC:
/* 800C9FAC 000C4EAC  7F 43 D3 78 */	mr r3, r26
/* 800C9FB0 000C4EB0  38 80 00 00 */	li r4, 0
lbl_800C9FB4:
/* 800C9FB4 000C4EB4  38 84 00 01 */	addi r4, r4, 1
/* 800C9FB8 000C4EB8  9B E3 01 39 */	stb r31, 0x139(r3)
/* 800C9FBC 000C4EBC  28 04 00 10 */	cmplwi r4, 0x10
/* 800C9FC0 000C4EC0  38 63 00 38 */	addi r3, r3, 0x38
/* 800C9FC4 000C4EC4  41 80 FF F0 */	blt lbl_800C9FB4
/* 800C9FC8 000C4EC8  3B 39 00 01 */	addi r25, r25, 1
/* 800C9FCC 000C4ECC  3B 5A 05 24 */	addi r26, r26, 0x524
/* 800C9FD0 000C4ED0  2C 19 00 04 */	cmpwi r25, 4
/* 800C9FD4 000C4ED4  41 80 FE 08 */	blt lbl_800C9DDC
/* 800C9FD8 000C4ED8  C3 6D 81 F8 */	lfs f27, kp_obj_interval-_SDA_BASE_(r13)
/* 800C9FDC 000C4EDC  48 02 78 E5 */	bl OSDisableInterrupts
/* 800C9FE0 000C4EE0  C0 02 95 B4 */	lfs f0, lbl_804C0FD4-_SDA2_BASE_(r2)
/* 800C9FE4 000C4EE4  D3 6D 81 F8 */	stfs f27, kp_obj_interval-_SDA_BASE_(r13)
/* 800C9FE8 000C4EE8  EC 1B 00 24 */	fdivs f0, f27, f0
/* 800C9FEC 000C4EEC  D0 0D 9A 44 */	stfs f0, kp_err_dist_min-_SDA_BASE_(r13)
/* 800C9FF0 000C4EF0  D0 0D 9A 40 */	stfs f0, kp_dist_vv1-_SDA_BASE_(r13)
/* 800C9FF4 000C4EF4  48 02 78 F5 */	bl OSRestoreInterrupts
/* 800C9FF8 000C4EF8  3C 60 80 41 */	lis r3, inside_kpads@ha
/* 800C9FFC 000C4EFC  3B 60 00 03 */	li r27, 3
/* 800CA000 000C4F00  38 63 E1 58 */	addi r3, r3, inside_kpads@l
/* 800CA004 000C4F04  3B E0 00 01 */	li r31, 1
/* 800CA008 000C4F08  3B 83 0F 6C */	addi r28, r3, 0xf6c
lbl_800CA00C:
/* 800CA00C 000C4F0C  7F 63 DB 78 */	mr r3, r27
/* 800CA010 000C4F10  38 80 00 00 */	li r4, 0
/* 800CA014 000C4F14  48 00 3B 25 */	bl WPADControlMotor
/* 800CA018 000C4F18  37 7B FF FF */	addic. r27, r27, -1
/* 800CA01C 000C4F1C  9B FC 05 1D */	stb r31, 0x51d(r28)
/* 800CA020 000C4F20  3B 9C FA DC */	addi r28, r28, -1316
/* 800CA024 000C4F24  40 80 FF E8 */	bge lbl_800CA00C
/* 800CA028 000C4F28  80 6D 81 E0 */	lwz r3, __KPADVersion-_SDA_BASE_(r13)
/* 800CA02C 000C4F2C  48 02 30 15 */	bl OSRegisterVersion
/* 800CA030 000C4F30  E3 E1 00 88 */	psq_l f31, 136(r1), 0, qr0
/* 800CA034 000C4F34  CB E1 00 80 */	lfd f31, 0x80(r1)
/* 800CA038 000C4F38  E3 C1 00 78 */	psq_l f30, 120(r1), 0, qr0
/* 800CA03C 000C4F3C  CB C1 00 70 */	lfd f30, 0x70(r1)
/* 800CA040 000C4F40  E3 A1 00 68 */	psq_l f29, 104(r1), 0, qr0
/* 800CA044 000C4F44  CB A1 00 60 */	lfd f29, 0x60(r1)
/* 800CA048 000C4F48  E3 81 00 58 */	psq_l f28, 88(r1), 0, qr0
/* 800CA04C 000C4F4C  CB 81 00 50 */	lfd f28, 0x50(r1)
/* 800CA050 000C4F50  E3 61 00 48 */	psq_l f27, 72(r1), 0, qr0
/* 800CA054 000C4F54  CB 61 00 40 */	lfd f27, 0x40(r1)
/* 800CA058 000C4F58  E3 41 00 38 */	psq_l f26, 56(r1), 0, qr0
/* 800CA05C 000C4F5C  39 61 00 30 */	addi r11, r1, 0x30
/* 800CA060 000C4F60  CB 41 00 30 */	lfd f26, 0x30(r1)
/* 800CA064 000C4F64  4B FE 7D 25 */	bl _restgpr_25
/* 800CA068 000C4F68  80 01 00 94 */	lwz r0, 0x94(r1)
/* 800CA06C 000C4F6C  7C 08 03 A6 */	mtlr r0
/* 800CA070 000C4F70  38 21 00 90 */	addi r1, r1, 0x90
/* 800CA074 000C4F74  4E 80 00 20 */	blr 

.global KPADDisableDPD
KPADDisableDPD:
/* 800CA078 000C4F78  1C 03 05 24 */	mulli r0, r3, 0x524
/* 800CA07C 000C4F7C  3C 60 80 41 */	lis r3, inside_kpads@ha
/* 800CA080 000C4F80  38 80 00 00 */	li r4, 0
/* 800CA084 000C4F84  38 63 E1 58 */	addi r3, r3, inside_kpads@l
/* 800CA088 000C4F88  7C 63 02 14 */	add r3, r3, r0
/* 800CA08C 000C4F8C  98 83 05 20 */	stb r4, 0x520(r3)
/* 800CA090 000C4F90  4E 80 00 20 */	blr 

.global KPADEnableDPD
KPADEnableDPD:
/* 800CA094 000C4F94  1C 03 05 24 */	mulli r0, r3, 0x524
/* 800CA098 000C4F98  3C 60 80 41 */	lis r3, inside_kpads@ha
/* 800CA09C 000C4F9C  38 80 00 01 */	li r4, 1
/* 800CA0A0 000C4FA0  38 63 E1 58 */	addi r3, r3, inside_kpads@l
/* 800CA0A4 000C4FA4  7C 63 02 14 */	add r3, r3, r0
/* 800CA0A8 000C4FA8  98 83 05 20 */	stb r4, 0x520(r3)
/* 800CA0AC 000C4FAC  4E 80 00 20 */	blr 

.global KPADSetControlDpdCallback
KPADSetControlDpdCallback:
/* 800CA0B0 000C4FB0  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800CA0B4 000C4FB4  7C 08 02 A6 */	mflr r0
/* 800CA0B8 000C4FB8  90 01 00 14 */	stw r0, 0x14(r1)
/* 800CA0BC 000C4FBC  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800CA0C0 000C4FC0  7C 9F 23 78 */	mr r31, r4
/* 800CA0C4 000C4FC4  93 C1 00 08 */	stw r30, 8(r1)
/* 800CA0C8 000C4FC8  7C 7E 1B 78 */	mr r30, r3
/* 800CA0CC 000C4FCC  48 02 77 F5 */	bl OSDisableInterrupts
/* 800CA0D0 000C4FD0  1C 1E 05 24 */	mulli r0, r30, 0x524
/* 800CA0D4 000C4FD4  3C 80 80 41 */	lis r4, inside_kpads@ha
/* 800CA0D8 000C4FD8  38 84 E1 58 */	addi r4, r4, inside_kpads@l
/* 800CA0DC 000C4FDC  7C 84 02 14 */	add r4, r4, r0
/* 800CA0E0 000C4FE0  93 E4 04 D8 */	stw r31, 0x4d8(r4)
/* 800CA0E4 000C4FE4  48 02 78 05 */	bl OSRestoreInterrupts
/* 800CA0E8 000C4FE8  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800CA0EC 000C4FEC  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 800CA0F0 000C4FF0  83 C1 00 08 */	lwz r30, 8(r1)
/* 800CA0F4 000C4FF4  7C 08 03 A6 */	mtlr r0
/* 800CA0F8 000C4FF8  38 21 00 10 */	addi r1, r1, 0x10
/* 800CA0FC 000C4FFC  4E 80 00 20 */	blr 

.global KPADiSamplingCallback
KPADiSamplingCallback:
/* 800CA100 000C5000  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800CA104 000C5004  7C 08 02 A6 */	mflr r0
/* 800CA108 000C5008  3C 80 80 41 */	lis r4, inside_kpads@ha
/* 800CA10C 000C500C  90 01 00 24 */	stw r0, 0x24(r1)
/* 800CA110 000C5010  1C 03 05 24 */	mulli r0, r3, 0x524
/* 800CA114 000C5014  38 84 E1 58 */	addi r4, r4, inside_kpads@l
/* 800CA118 000C5018  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800CA11C 000C501C  7F E4 02 14 */	add r31, r4, r0
/* 800CA120 000C5020  38 81 00 08 */	addi r4, r1, 8
/* 800CA124 000C5024  93 C1 00 18 */	stw r30, 0x18(r1)
/* 800CA128 000C5028  7C 7E 1B 78 */	mr r30, r3
/* 800CA12C 000C502C  93 A1 00 14 */	stw r29, 0x14(r1)
/* 800CA130 000C5030  93 81 00 10 */	stw r28, 0x10(r1)
/* 800CA134 000C5034  48 00 34 D5 */	bl WPADProbe
/* 800CA138 000C5038  2C 03 FF FF */	cmpwi r3, -1
/* 800CA13C 000C503C  41 82 01 84 */	beq lbl_800CA2C0
/* 800CA140 000C5040  8B BF 01 0E */	lbz r29, 0x10e(r31)
/* 800CA144 000C5044  28 1D 00 10 */	cmplwi r29, 0x10
/* 800CA148 000C5048  41 80 00 08 */	blt lbl_800CA150
/* 800CA14C 000C504C  3B A0 00 00 */	li r29, 0
lbl_800CA150:
/* 800CA150 000C5050  1C 1D 00 38 */	mulli r0, r29, 0x38
/* 800CA154 000C5054  7F C3 F3 78 */	mr r3, r30
/* 800CA158 000C5058  7C 9F 02 14 */	add r4, r31, r0
/* 800CA15C 000C505C  3B 84 01 10 */	addi r28, r4, 0x110
/* 800CA160 000C5060  7F 84 E3 78 */	mr r4, r28
/* 800CA164 000C5064  48 00 3D 9D */	bl WPADRead
/* 800CA168 000C5068  7F C3 F3 78 */	mr r3, r30
/* 800CA16C 000C506C  48 00 36 61 */	bl WPADGetDataFormat
/* 800CA170 000C5070  98 7C 00 36 */	stb r3, 0x36(r28)
/* 800CA174 000C5074  38 1D 00 01 */	addi r0, r29, 1
/* 800CA178 000C5078  98 1F 01 0E */	stb r0, 0x10e(r31)
/* 800CA17C 000C507C  88 7F 01 0F */	lbz r3, 0x10f(r31)
/* 800CA180 000C5080  28 03 00 10 */	cmplwi r3, 0x10
/* 800CA184 000C5084  40 80 00 0C */	bge lbl_800CA190
/* 800CA188 000C5088  38 03 00 01 */	addi r0, r3, 1
/* 800CA18C 000C508C  98 1F 01 0F */	stb r0, 0x10f(r31)
lbl_800CA190:
/* 800CA190 000C5090  80 01 00 08 */	lwz r0, 8(r1)
/* 800CA194 000C5094  2C 00 00 FB */	cmpwi r0, 0xfb
/* 800CA198 000C5098  40 80 00 28 */	bge lbl_800CA1C0
/* 800CA19C 000C509C  2C 00 00 01 */	cmpwi r0, 1
/* 800CA1A0 000C50A0  41 82 00 3C */	beq lbl_800CA1DC
/* 800CA1A4 000C50A4  40 80 00 10 */	bge lbl_800CA1B4
/* 800CA1A8 000C50A8  2C 00 00 00 */	cmpwi r0, 0
/* 800CA1AC 000C50AC  40 80 00 28 */	bge lbl_800CA1D4
/* 800CA1B0 000C50B0  48 00 01 10 */	b lbl_800CA2C0
lbl_800CA1B4:
/* 800CA1B4 000C50B4  2C 00 00 03 */	cmpwi r0, 3
/* 800CA1B8 000C50B8  40 80 01 08 */	bge lbl_800CA2C0
/* 800CA1BC 000C50BC  48 00 00 28 */	b lbl_800CA1E4
lbl_800CA1C0:
/* 800CA1C0 000C50C0  2C 00 00 FF */	cmpwi r0, 0xff
/* 800CA1C4 000C50C4  41 82 00 10 */	beq lbl_800CA1D4
/* 800CA1C8 000C50C8  40 80 00 F8 */	bge lbl_800CA2C0
/* 800CA1CC 000C50CC  2C 00 00 FD */	cmpwi r0, 0xfd
/* 800CA1D0 000C50D0  40 80 00 F0 */	bge lbl_800CA2C0
lbl_800CA1D4:
/* 800CA1D4 000C50D4  3B A0 00 00 */	li r29, 0
/* 800CA1D8 000C50D8  48 00 00 10 */	b lbl_800CA1E8
lbl_800CA1DC:
/* 800CA1DC 000C50DC  3B A0 00 02 */	li r29, 2
/* 800CA1E0 000C50E0  48 00 00 08 */	b lbl_800CA1E8
lbl_800CA1E4:
/* 800CA1E4 000C50E4  3B A0 00 04 */	li r29, 4
lbl_800CA1E8:
/* 800CA1E8 000C50E8  88 1F 05 20 */	lbz r0, 0x520(r31)
/* 800CA1EC 000C50EC  2C 00 00 00 */	cmpwi r0, 0
/* 800CA1F0 000C50F0  41 82 00 08 */	beq lbl_800CA1F8
/* 800CA1F4 000C50F4  3B BD 00 01 */	addi r29, r29, 1
lbl_800CA1F8:
/* 800CA1F8 000C50F8  7F C3 F3 78 */	mr r3, r30
/* 800CA1FC 000C50FC  48 00 5D 75 */	bl WPADIsDpdEnabled
/* 800CA200 000C5100  2C 03 00 00 */	cmpwi r3, 0
/* 800CA204 000C5104  41 82 00 0C */	beq lbl_800CA210
/* 800CA208 000C5108  88 9F 05 21 */	lbz r4, 0x521(r31)
/* 800CA20C 000C510C  48 00 00 08 */	b lbl_800CA214
lbl_800CA210:
/* 800CA210 000C5110  38 80 00 00 */	li r4, 0
lbl_800CA214:
/* 800CA214 000C5114  3C 60 80 3A */	lis r3, table$3298@ha
/* 800CA218 000C5118  57 A0 08 3C */	slwi r0, r29, 1
/* 800CA21C 000C511C  38 63 94 64 */	addi r3, r3, table$3298@l
/* 800CA220 000C5120  7F A3 02 14 */	add r29, r3, r0
/* 800CA224 000C5124  7C 03 00 AE */	lbzx r0, r3, r0
/* 800CA228 000C5128  7C 04 00 40 */	cmplw r4, r0
/* 800CA22C 000C512C  41 82 00 7C */	beq lbl_800CA2A8
/* 800CA230 000C5130  80 1F 04 D8 */	lwz r0, 0x4d8(r31)
/* 800CA234 000C5134  2C 00 00 00 */	cmpwi r0, 0
/* 800CA238 000C5138  41 82 00 34 */	beq lbl_800CA26C
/* 800CA23C 000C513C  88 1F 05 22 */	lbz r0, 0x522(r31)
/* 800CA240 000C5140  2C 00 00 00 */	cmpwi r0, 0
/* 800CA244 000C5144  40 82 00 28 */	bne lbl_800CA26C
/* 800CA248 000C5148  38 00 00 01 */	li r0, 1
/* 800CA24C 000C514C  7F C3 F3 78 */	mr r3, r30
/* 800CA250 000C5150  98 1F 05 22 */	stb r0, 0x522(r31)
/* 800CA254 000C5154  38 80 00 00 */	li r4, 0
/* 800CA258 000C5158  81 9F 04 D8 */	lwz r12, 0x4d8(r31)
/* 800CA25C 000C515C  7D 89 03 A6 */	mtctr r12
/* 800CA260 000C5160  4E 80 04 21 */	bctrl 
/* 800CA264 000C5164  38 00 00 00 */	li r0, 0
/* 800CA268 000C5168  98 1F 05 23 */	stb r0, 0x523(r31)
lbl_800CA26C:
/* 800CA26C 000C516C  88 1F 05 1F */	lbz r0, 0x51f(r31)
/* 800CA270 000C5170  2C 00 00 00 */	cmpwi r0, 0
/* 800CA274 000C5174  40 82 00 4C */	bne lbl_800CA2C0
/* 800CA278 000C5178  38 00 00 01 */	li r0, 1
/* 800CA27C 000C517C  3C A0 80 0D */	lis r5, KPADiControlDpdCallback@ha
/* 800CA280 000C5180  98 1F 05 1F */	stb r0, 0x51f(r31)
/* 800CA284 000C5184  7F C3 F3 78 */	mr r3, r30
/* 800CA288 000C5188  88 9D 00 00 */	lbz r4, 0(r29)
/* 800CA28C 000C518C  38 A5 A2 F8 */	addi r5, r5, KPADiControlDpdCallback@l
/* 800CA290 000C5190  48 00 5D 55 */	bl WPADControlDpd
/* 800CA294 000C5194  2C 03 00 00 */	cmpwi r3, 0
/* 800CA298 000C5198  40 82 00 28 */	bne lbl_800CA2C0
/* 800CA29C 000C519C  88 1D 00 00 */	lbz r0, 0(r29)
/* 800CA2A0 000C51A0  98 1F 05 21 */	stb r0, 0x521(r31)
/* 800CA2A4 000C51A4  48 00 00 1C */	b lbl_800CA2C0
lbl_800CA2A8:
/* 800CA2A8 000C51A8  88 9D 00 01 */	lbz r4, 1(r29)
/* 800CA2AC 000C51AC  88 1C 00 36 */	lbz r0, 0x36(r28)
/* 800CA2B0 000C51B0  7C 00 20 40 */	cmplw r0, r4
/* 800CA2B4 000C51B4  41 82 00 0C */	beq lbl_800CA2C0
/* 800CA2B8 000C51B8  7F C3 F3 78 */	mr r3, r30
/* 800CA2BC 000C51BC  48 00 35 59 */	bl WPADSetDataFormat
lbl_800CA2C0:
/* 800CA2C0 000C51C0  81 9F 05 18 */	lwz r12, 0x518(r31)
/* 800CA2C4 000C51C4  2C 0C 00 00 */	cmpwi r12, 0
/* 800CA2C8 000C51C8  41 82 00 10 */	beq lbl_800CA2D8
/* 800CA2CC 000C51CC  7F C3 F3 78 */	mr r3, r30
/* 800CA2D0 000C51D0  7D 89 03 A6 */	mtctr r12
/* 800CA2D4 000C51D4  4E 80 04 21 */	bctrl 
lbl_800CA2D8:
/* 800CA2D8 000C51D8  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800CA2DC 000C51DC  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800CA2E0 000C51E0  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 800CA2E4 000C51E4  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 800CA2E8 000C51E8  83 81 00 10 */	lwz r28, 0x10(r1)
/* 800CA2EC 000C51EC  7C 08 03 A6 */	mtlr r0
/* 800CA2F0 000C51F0  38 21 00 20 */	addi r1, r1, 0x20
/* 800CA2F4 000C51F4  4E 80 00 20 */	blr 

.global KPADiControlDpdCallback
KPADiControlDpdCallback:
/* 800CA2F8 000C51F8  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800CA2FC 000C51FC  7C 08 02 A6 */	mflr r0
/* 800CA300 000C5200  3C A0 80 41 */	lis r5, inside_kpads@ha
/* 800CA304 000C5204  2C 04 00 00 */	cmpwi r4, 0
/* 800CA308 000C5208  90 01 00 14 */	stw r0, 0x14(r1)
/* 800CA30C 000C520C  1C 03 05 24 */	mulli r0, r3, 0x524
/* 800CA310 000C5210  38 A5 E1 58 */	addi r5, r5, inside_kpads@l
/* 800CA314 000C5214  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800CA318 000C5218  7F E5 02 14 */	add r31, r5, r0
/* 800CA31C 000C521C  40 82 00 3C */	bne lbl_800CA358
/* 800CA320 000C5220  80 1F 04 D8 */	lwz r0, 0x4d8(r31)
/* 800CA324 000C5224  2C 00 00 00 */	cmpwi r0, 0
/* 800CA328 000C5228  41 82 00 30 */	beq lbl_800CA358
/* 800CA32C 000C522C  88 1F 05 23 */	lbz r0, 0x523(r31)
/* 800CA330 000C5230  2C 00 00 00 */	cmpwi r0, 0
/* 800CA334 000C5234  40 82 00 24 */	bne lbl_800CA358
/* 800CA338 000C5238  38 00 00 01 */	li r0, 1
/* 800CA33C 000C523C  38 80 00 01 */	li r4, 1
/* 800CA340 000C5240  98 1F 05 23 */	stb r0, 0x523(r31)
/* 800CA344 000C5244  81 9F 04 D8 */	lwz r12, 0x4d8(r31)
/* 800CA348 000C5248  7D 89 03 A6 */	mtctr r12
/* 800CA34C 000C524C  4E 80 04 21 */	bctrl 
/* 800CA350 000C5250  38 00 00 00 */	li r0, 0
/* 800CA354 000C5254  98 1F 05 22 */	stb r0, 0x522(r31)
lbl_800CA358:
/* 800CA358 000C5258  38 00 00 00 */	li r0, 0
/* 800CA35C 000C525C  98 1F 05 1F */	stb r0, 0x51f(r31)
/* 800CA360 000C5260  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 800CA364 000C5264  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800CA368 000C5268  7C 08 03 A6 */	mtlr r0
/* 800CA36C 000C526C  38 21 00 10 */	addi r1, r1, 0x10
/* 800CA370 000C5270  4E 80 00 20 */	blr 
