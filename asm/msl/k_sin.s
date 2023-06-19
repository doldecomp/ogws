.include "macros.inc"

.section .sdata2, "a"
.balign 0x8
.global lbl_804C0EC0
lbl_804C0EC0:
	.incbin "baserom.dol", 0x3C9B00, 0x8
.global lbl_804C0EC8
lbl_804C0EC8:
	.incbin "baserom.dol", 0x3C9B08, 0x8
.global lbl_804C0ED0
lbl_804C0ED0:
	.incbin "baserom.dol", 0x3C9B10, 0x8
.global lbl_804C0ED8
lbl_804C0ED8:
	.incbin "baserom.dol", 0x3C9B18, 0x8
.global lbl_804C0EE0
lbl_804C0EE0:
	.incbin "baserom.dol", 0x3C9B20, 0x8
.global lbl_804C0EE8
lbl_804C0EE8:
	.incbin "baserom.dol", 0x3C9B28, 0x8
.global lbl_804C0EF0
lbl_804C0EF0:
	.incbin "baserom.dol", 0x3C9B30, 0x8

.section .text, "ax"
.global __kernel_sin
__kernel_sin:
/* 800C0154 000BB054  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800C0158 000BB058  3C 00 3E 40 */	lis r0, 0x3e40
/* 800C015C 000BB05C  D8 21 00 08 */	stfd f1, 8(r1)
/* 800C0160 000BB060  80 81 00 08 */	lwz r4, 8(r1)
/* 800C0164 000BB064  54 84 00 7E */	clrlwi r4, r4, 1
/* 800C0168 000BB068  7C 04 00 00 */	cmpw r4, r0
/* 800C016C 000BB06C  40 80 00 1C */	bge lbl_800C0188
/* 800C0170 000BB070  FC 00 08 1E */	fctiwz f0, f1
/* 800C0174 000BB074  D8 01 00 10 */	stfd f0, 0x10(r1)
/* 800C0178 000BB078  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800C017C 000BB07C  2C 00 00 00 */	cmpwi r0, 0
/* 800C0180 000BB080  40 82 00 08 */	bne lbl_800C0188
/* 800C0184 000BB084  48 00 00 88 */	b lbl_800C020C
lbl_800C0188:
/* 800C0188 000BB088  FC E1 00 72 */	fmul f7, f1, f1
/* 800C018C 000BB08C  C8 02 94 C0 */	lfd f0, lbl_804C0EE0-_SDA2_BASE_(r2)
/* 800C0190 000BB090  C8 A2 94 B8 */	lfd f5, lbl_804C0ED8-_SDA2_BASE_(r2)
/* 800C0194 000BB094  2C 03 00 00 */	cmpwi r3, 0
/* 800C0198 000BB098  C8 82 94 B0 */	lfd f4, lbl_804C0ED0-_SDA2_BASE_(r2)
/* 800C019C 000BB09C  C8 62 94 A8 */	lfd f3, lbl_804C0EC8-_SDA2_BASE_(r2)
/* 800C01A0 000BB0A0  FC C0 01 F2 */	fmul f6, f0, f7
/* 800C01A4 000BB0A4  C8 02 94 A0 */	lfd f0, lbl_804C0EC0-_SDA2_BASE_(r2)
/* 800C01A8 000BB0A8  FD 07 00 72 */	fmul f8, f7, f1
/* 800C01AC 000BB0AC  FC A5 30 2A */	fadd f5, f5, f6
/* 800C01B0 000BB0B0  FC A7 01 72 */	fmul f5, f7, f5
/* 800C01B4 000BB0B4  FC 84 28 2A */	fadd f4, f4, f5
/* 800C01B8 000BB0B8  FC 87 01 32 */	fmul f4, f7, f4
/* 800C01BC 000BB0BC  FC 63 20 2A */	fadd f3, f3, f4
/* 800C01C0 000BB0C0  FC 67 00 F2 */	fmul f3, f7, f3
/* 800C01C4 000BB0C4  FC 00 18 2A */	fadd f0, f0, f3
/* 800C01C8 000BB0C8  40 82 00 1C */	bne lbl_800C01E4
/* 800C01CC 000BB0CC  FC 47 00 32 */	fmul f2, f7, f0
/* 800C01D0 000BB0D0  C8 02 94 C8 */	lfd f0, lbl_804C0EE8-_SDA2_BASE_(r2)
/* 800C01D4 000BB0D4  FC 00 10 2A */	fadd f0, f0, f2
/* 800C01D8 000BB0D8  FC 08 00 32 */	fmul f0, f8, f0
/* 800C01DC 000BB0DC  FC 21 00 2A */	fadd f1, f1, f0
/* 800C01E0 000BB0E0  48 00 00 2C */	b lbl_800C020C
lbl_800C01E4:
/* 800C01E4 000BB0E4  C8 82 94 D0 */	lfd f4, lbl_804C0EF0-_SDA2_BASE_(r2)
/* 800C01E8 000BB0E8  FC 68 00 32 */	fmul f3, f8, f0
/* 800C01EC 000BB0EC  C8 02 94 C8 */	lfd f0, lbl_804C0EE8-_SDA2_BASE_(r2)
/* 800C01F0 000BB0F0  FC 84 00 B2 */	fmul f4, f4, f2
/* 800C01F4 000BB0F4  FC 00 02 32 */	fmul f0, f0, f8
/* 800C01F8 000BB0F8  FC 64 18 28 */	fsub f3, f4, f3
/* 800C01FC 000BB0FC  FC 67 00 F2 */	fmul f3, f7, f3
/* 800C0200 000BB100  FC 43 10 28 */	fsub f2, f3, f2
/* 800C0204 000BB104  FC 02 00 28 */	fsub f0, f2, f0
/* 800C0208 000BB108  FC 21 00 28 */	fsub f1, f1, f0
lbl_800C020C:
/* 800C020C 000BB10C  38 21 00 20 */	addi r1, r1, 0x20
/* 800C0210 000BB110  4E 80 00 20 */	blr 
