.include "macros.inc"

.section .sdata, "wa"
.global u$7185
u$7185:
	.long 0x12345678
.balign 0x8

.section .rodata, "a"
.long 0
.global NoteTable__Q44nw4r3snd6detail4Util
NoteTable__Q44nw4r3snd6detail4Util:
	.incbin "baserom.dol", 0x371CF8, 0x30
.global PitchTable__Q44nw4r3snd6detail4Util
PitchTable__Q44nw4r3snd6detail4Util:
	.incbin "baserom.dol", 0x371D28, 0x400
.global Decibel2RatioTable__Q44nw4r3snd6detail4Util
Decibel2RatioTable__Q44nw4r3snd6detail4Util:
	.incbin "baserom.dol", 0x372128, 0xf14
.global Pan2RatioTableSqrt__Q44nw4r3snd6detail4Util
Pan2RatioTableSqrt__Q44nw4r3snd6detail4Util:
	.incbin "baserom.dol", 0x37303C, 0x404
.global Pan2RatioTableSinCos__Q44nw4r3snd6detail4Util
Pan2RatioTableSinCos__Q44nw4r3snd6detail4Util:
	.incbin "baserom.dol", 0x373440, 0x404
.global Pan2RatioTableLinear__Q44nw4r3snd6detail4Util
Pan2RatioTableLinear__Q44nw4r3snd6detail4Util:
	.incbin "baserom.dol", 0x373844, 0x404
.global RemoteFilterCoefTable__Q44nw4r3snd6detail4Util
RemoteFilterCoefTable__Q44nw4r3snd6detail4Util:
	.incbin "baserom.dol", 0x373C48, 0x500

.section .data, "wa"
# I think this is PanTableTable__Q44nw4r3snd6detail4Util, unsure though
.global lbl_80396468
lbl_80396468:
	.long 0x80376F3C
	.long 0x80377340
	.long 0x80377744
	.long 0
.balign 0x8

.section .sdata2, "a"
.global lbl_804C0160
lbl_804C0160:
	.single 0e1
.global lbl_804C0164
lbl_804C0164:
	.single 0e2
.global lbl_804C0168
lbl_804C0168:
	.single 0e0.5
.global lbl_804C016C
lbl_804C016C:
	.single 0e6
.global lbl_804C0170
lbl_804C0170:
	.single 0e-90.4
.global lbl_804C0174
lbl_804C0174:
	.single 0e10
.global lbl_804C0178
lbl_804C0178:
	.single 0e-1
.global lbl_804C017C
lbl_804C017C:
	.single 0e256
.global lbl_804C0180
lbl_804C0180:
	.double 0e0
.global lbl_804C0188
lbl_804C0188:
	.double 0e32000
.global lbl_804C0190
lbl_804C0190:
	.double 0e2
.global lbl_804C0198
lbl_804C0198:
	.double 0e10
.global lbl_804C01A0
lbl_804C01A0:
	.double 0e1
.global lbl_804C01A8
lbl_804C01A8:
	.single 0e1
	.single 0e0

.section .text, "ax"  # 0x800076E0 - 0x80355080 
.global CalcPitchRatio__Q44nw4r3snd6detail4UtilFi
CalcPitchRatio__Q44nw4r3snd6detail4UtilFi:
/* 8004E83C 0004973C  20 A3 0B FF */	subfic r5, r3, 0xbff
/* 8004E840 00049740  38 00 0C 00 */	li r0, 0xc00
/* 8004E844 00049744  7C A5 03 96 */	divwu r5, r5, r0
/* 8004E848 00049748  2C 03 00 00 */	cmpwi r3, 0
/* 8004E84C 0004974C  C0 22 87 40 */	lfs f1, lbl_804C0160-_SDA2_BASE_(r2)
/* 8004E850 00049750  38 C0 00 00 */	li r6, 0
/* 8004E854 00049754  40 80 00 34 */	bge lbl_8004E888
/* 8004E858 00049758  54 A4 E8 FF */	rlwinm. r4, r5, 0x1d, 3, 0x1f
/* 8004E85C 0004975C  1C 05 0C 00 */	mulli r0, r5, 0xc00
/* 8004E860 00049760  7C 89 03 A6 */	mtctr r4
/* 8004E864 00049764  41 82 00 14 */	beq lbl_8004E878
lbl_8004E868:
/* 8004E868 00049768  38 C6 FF F8 */	addi r6, r6, -8
/* 8004E86C 0004976C  42 00 FF FC */	bdnz lbl_8004E868
/* 8004E870 00049770  70 A5 00 07 */	andi. r5, r5, 7
/* 8004E874 00049774  41 82 00 10 */	beq lbl_8004E884
lbl_8004E878:
/* 8004E878 00049778  7C A9 03 A6 */	mtctr r5
lbl_8004E87C:
/* 8004E87C 0004977C  38 C6 FF FF */	addi r6, r6, -1
/* 8004E880 00049780  42 00 FF FC */	bdnz lbl_8004E87C
lbl_8004E884:
/* 8004E884 00049784  7C 63 02 14 */	add r3, r3, r0
lbl_8004E888:
/* 8004E888 00049788  38 00 0C 00 */	li r0, 0xc00
/* 8004E88C 0004978C  2C 03 0C 00 */	cmpwi r3, 0xc00
/* 8004E890 00049790  7C A3 03 96 */	divwu r5, r3, r0
/* 8004E894 00049794  41 80 00 34 */	blt lbl_8004E8C8
/* 8004E898 00049798  54 A4 E8 FF */	rlwinm. r4, r5, 0x1d, 3, 0x1f
/* 8004E89C 0004979C  1C 05 F4 00 */	mulli r0, r5, -3072
/* 8004E8A0 000497A0  7C 89 03 A6 */	mtctr r4
/* 8004E8A4 000497A4  41 82 00 14 */	beq lbl_8004E8B8
lbl_8004E8A8:
/* 8004E8A8 000497A8  38 C6 00 08 */	addi r6, r6, 8
/* 8004E8AC 000497AC  42 00 FF FC */	bdnz lbl_8004E8A8
/* 8004E8B0 000497B0  70 A5 00 07 */	andi. r5, r5, 7
/* 8004E8B4 000497B4  41 82 00 10 */	beq lbl_8004E8C4
lbl_8004E8B8:
/* 8004E8B8 000497B8  7C A9 03 A6 */	mtctr r5
lbl_8004E8BC:
/* 8004E8BC 000497BC  38 C6 00 01 */	addi r6, r6, 1
/* 8004E8C0 000497C0  42 00 FF FC */	bdnz lbl_8004E8BC
lbl_8004E8C4:
/* 8004E8C4 000497C4  7C 63 02 14 */	add r3, r3, r0
lbl_8004E8C8:
/* 8004E8C8 000497C8  2C 06 00 00 */	cmpwi r6, 0
/* 8004E8CC 000497CC  C0 02 87 44 */	lfs f0, lbl_804C0164-_SDA2_BASE_(r2)
/* 8004E8D0 000497D0  7C C5 33 78 */	mr r5, r6
/* 8004E8D4 000497D4  40 81 00 50 */	ble lbl_8004E924
/* 8004E8D8 000497D8  54 C4 E8 FF */	rlwinm. r4, r6, 0x1d, 3, 0x1f
/* 8004E8DC 000497DC  7C 06 00 D0 */	neg r0, r6
/* 8004E8E0 000497E0  7C 89 03 A6 */	mtctr r4
/* 8004E8E4 000497E4  41 82 00 30 */	beq lbl_8004E914
lbl_8004E8E8:
/* 8004E8E8 000497E8  EC 21 00 32 */	fmuls f1, f1, f0
/* 8004E8EC 000497EC  EC 21 00 32 */	fmuls f1, f1, f0
/* 8004E8F0 000497F0  EC 21 00 32 */	fmuls f1, f1, f0
/* 8004E8F4 000497F4  EC 21 00 32 */	fmuls f1, f1, f0
/* 8004E8F8 000497F8  EC 21 00 32 */	fmuls f1, f1, f0
/* 8004E8FC 000497FC  EC 21 00 32 */	fmuls f1, f1, f0
/* 8004E900 00049800  EC 21 00 32 */	fmuls f1, f1, f0
/* 8004E904 00049804  EC 21 00 32 */	fmuls f1, f1, f0
/* 8004E908 00049808  42 00 FF E0 */	bdnz lbl_8004E8E8
/* 8004E90C 0004980C  70 C5 00 07 */	andi. r5, r6, 7
/* 8004E910 00049810  41 82 00 10 */	beq lbl_8004E920
lbl_8004E914:
/* 8004E914 00049814  7C A9 03 A6 */	mtctr r5
lbl_8004E918:
/* 8004E918 00049818  EC 21 00 32 */	fmuls f1, f1, f0
/* 8004E91C 0004981C  42 00 FF FC */	bdnz lbl_8004E918
lbl_8004E920:
/* 8004E920 00049820  7C C6 02 14 */	add r6, r6, r0
lbl_8004E924:
/* 8004E924 00049824  2C 06 00 00 */	cmpwi r6, 0
/* 8004E928 00049828  C0 02 87 48 */	lfs f0, lbl_804C0168-_SDA2_BASE_(r2)
/* 8004E92C 0004982C  7C 86 00 D0 */	neg r4, r6
/* 8004E930 00049830  40 80 00 48 */	bge lbl_8004E978
/* 8004E934 00049834  54 80 E8 FF */	rlwinm. r0, r4, 0x1d, 3, 0x1f
/* 8004E938 00049838  7C 09 03 A6 */	mtctr r0
/* 8004E93C 0004983C  41 82 00 30 */	beq lbl_8004E96C
lbl_8004E940:
/* 8004E940 00049840  EC 21 00 32 */	fmuls f1, f1, f0
/* 8004E944 00049844  EC 21 00 32 */	fmuls f1, f1, f0
/* 8004E948 00049848  EC 21 00 32 */	fmuls f1, f1, f0
/* 8004E94C 0004984C  EC 21 00 32 */	fmuls f1, f1, f0
/* 8004E950 00049850  EC 21 00 32 */	fmuls f1, f1, f0
/* 8004E954 00049854  EC 21 00 32 */	fmuls f1, f1, f0
/* 8004E958 00049858  EC 21 00 32 */	fmuls f1, f1, f0
/* 8004E95C 0004985C  EC 21 00 32 */	fmuls f1, f1, f0
/* 8004E960 00049860  42 00 FF E0 */	bdnz lbl_8004E940
/* 8004E964 00049864  70 84 00 07 */	andi. r4, r4, 7
/* 8004E968 00049868  41 82 00 10 */	beq lbl_8004E978
lbl_8004E96C:
/* 8004E96C 0004986C  7C 89 03 A6 */	mtctr r4
lbl_8004E970:
/* 8004E970 00049870  EC 21 00 32 */	fmuls f1, f1, f0
/* 8004E974 00049874  42 00 FF FC */	bdnz lbl_8004E970
lbl_8004E978:
/* 8004E978 00049878  7C 64 46 70 */	srawi r4, r3, 8
/* 8004E97C 0004987C  54 60 C0 0E */	slwi r0, r3, 0x18
/* 8004E980 00049880  54 63 0F FE */	srwi r3, r3, 0x1f
/* 8004E984 00049884  7C 03 00 50 */	subf r0, r3, r0
/* 8004E988 00049888  7C A4 01 95 */	addze. r5, r4
/* 8004E98C 0004988C  54 00 40 3E */	rotlwi r0, r0, 8
/* 8004E990 00049890  7C 60 1A 14 */	add r3, r0, r3
/* 8004E994 00049894  41 82 00 18 */	beq lbl_8004E9AC
/* 8004E998 00049898  3C 80 80 37 */	lis r4, NoteTable__Q44nw4r3snd6detail4Util@ha
/* 8004E99C 0004989C  54 A0 10 3A */	slwi r0, r5, 2
/* 8004E9A0 000498A0  38 84 5B F8 */	addi r4, r4, NoteTable__Q44nw4r3snd6detail4Util@l
/* 8004E9A4 000498A4  7C 04 04 2E */	lfsx f0, r4, r0
/* 8004E9A8 000498A8  EC 21 00 32 */	fmuls f1, f1, f0
lbl_8004E9AC:
/* 8004E9AC 000498AC  2C 03 00 00 */	cmpwi r3, 0
/* 8004E9B0 000498B0  4D 82 00 20 */	beqlr 
/* 8004E9B4 000498B4  3C 80 80 37 */	lis r4, PitchTable__Q44nw4r3snd6detail4Util@ha
/* 8004E9B8 000498B8  54 60 10 3A */	slwi r0, r3, 2
/* 8004E9BC 000498BC  38 84 5C 28 */	addi r4, r4, PitchTable__Q44nw4r3snd6detail4Util@l
/* 8004E9C0 000498C0  7C 04 04 2E */	lfsx f0, r4, r0
/* 8004E9C4 000498C4  EC 21 00 32 */	fmuls f1, f1, f0
/* 8004E9C8 000498C8  4E 80 00 20 */	blr 

.global CalcVolumeRatio__Q44nw4r3snd6detail4UtilFf
CalcVolumeRatio__Q44nw4r3snd6detail4UtilFf:
/* 8004E9CC 000498CC  C0 42 87 4C */	lfs f2, lbl_804C016C-_SDA2_BASE_(r2)
/* 8004E9D0 000498D0  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8004E9D4 000498D4  FC 01 10 40 */	fcmpo cr0, f1, f2
/* 8004E9D8 000498D8  40 81 00 08 */	ble lbl_8004E9E0
/* 8004E9DC 000498DC  48 00 00 18 */	b lbl_8004E9F4
lbl_8004E9E0:
/* 8004E9E0 000498E0  C0 42 87 50 */	lfs f2, lbl_804C0170-_SDA2_BASE_(r2)
/* 8004E9E4 000498E4  FC 01 10 40 */	fcmpo cr0, f1, f2
/* 8004E9E8 000498E8  40 80 00 08 */	bge lbl_8004E9F0
/* 8004E9EC 000498EC  48 00 00 08 */	b lbl_8004E9F4
lbl_8004E9F0:
/* 8004E9F0 000498F0  FC 40 08 90 */	fmr f2, f1
lbl_8004E9F4:
/* 8004E9F4 000498F4  C0 02 87 54 */	lfs f0, lbl_804C0174-_SDA2_BASE_(r2)
/* 8004E9F8 000498F8  3C 60 80 37 */	lis r3, Decibel2RatioTable__Q44nw4r3snd6detail4Util@ha
/* 8004E9FC 000498FC  38 63 60 28 */	addi r3, r3, Decibel2RatioTable__Q44nw4r3snd6detail4Util@l
/* 8004EA00 00049900  EC 00 00 B2 */	fmuls f0, f0, f2
/* 8004EA04 00049904  FC 00 00 1E */	fctiwz f0, f0
/* 8004EA08 00049908  D8 01 00 08 */	stfd f0, 8(r1)
/* 8004EA0C 0004990C  80 81 00 0C */	lwz r4, 0xc(r1)
/* 8004EA10 00049910  38 04 03 88 */	addi r0, r4, 0x388
/* 8004EA14 00049914  54 00 10 3A */	slwi r0, r0, 2
/* 8004EA18 00049918  7C 23 04 2E */	lfsx f1, r3, r0
/* 8004EA1C 0004991C  38 21 00 10 */	addi r1, r1, 0x10
/* 8004EA20 00049920  4E 80 00 20 */	blr 

.global CalcPanRatio__Q44nw4r3snd6detail4UtilFfRCQ54nw4r3snd6detail4Util7PanInfo
CalcPanRatio__Q44nw4r3snd6detail4UtilFfRCQ54nw4r3snd6detail4Util7PanInfo:
/* 8004EA24 00049924  C0 42 87 40 */	lfs f2, lbl_804C0160-_SDA2_BASE_(r2)
/* 8004EA28 00049928  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8004EA2C 0004992C  FC 01 10 40 */	fcmpo cr0, f1, f2
/* 8004EA30 00049930  40 81 00 08 */	ble lbl_8004EA38
/* 8004EA34 00049934  48 00 00 18 */	b lbl_8004EA4C
lbl_8004EA38:
/* 8004EA38 00049938  C0 42 87 58 */	lfs f2, lbl_804C0178-_SDA2_BASE_(r2)
/* 8004EA3C 0004993C  FC 01 10 40 */	fcmpo cr0, f1, f2
/* 8004EA40 00049940  40 80 00 08 */	bge lbl_8004EA48
/* 8004EA44 00049944  48 00 00 08 */	b lbl_8004EA4C
lbl_8004EA48:
/* 8004EA48 00049948  FC 40 08 90 */	fmr f2, f1
lbl_8004EA4C:
/* 8004EA4C 0004994C  C0 02 87 40 */	lfs f0, lbl_804C0160-_SDA2_BASE_(r2)
/* 8004EA50 00049950  3C 80 80 39 */	lis r4, lbl_80396468@ha
/* 8004EA54 00049954  80 03 00 00 */	lwz r0, 0(r3)
/* 8004EA58 00049958  38 84 64 68 */	addi r4, r4, lbl_80396468@l
/* 8004EA5C 0004995C  EC 20 10 2A */	fadds f1, f0, f2
/* 8004EA60 00049960  C0 42 87 48 */	lfs f2, lbl_804C0168-_SDA2_BASE_(r2)
/* 8004EA64 00049964  54 05 10 3A */	slwi r5, r0, 2
/* 8004EA68 00049968  88 03 00 04 */	lbz r0, 4(r3)
/* 8004EA6C 0004996C  C0 02 87 5C */	lfs f0, lbl_804C017C-_SDA2_BASE_(r2)
/* 8004EA70 00049970  EC 21 00 B2 */	fmuls f1, f1, f2
/* 8004EA74 00049974  2C 00 00 00 */	cmpwi r0, 0
/* 8004EA78 00049978  7C 84 28 2E */	lwzx r4, r4, r5
/* 8004EA7C 0004997C  EC 00 00 72 */	fmuls f0, f0, f1
/* 8004EA80 00049980  EC 02 00 2A */	fadds f0, f2, f0
/* 8004EA84 00049984  FC 00 00 1E */	fctiwz f0, f0
/* 8004EA88 00049988  D8 01 00 08 */	stfd f0, 8(r1)
/* 8004EA8C 0004998C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8004EA90 00049990  54 00 10 3A */	slwi r0, r0, 2
/* 8004EA94 00049994  7C 44 04 2E */	lfsx f2, r4, r0
/* 8004EA98 00049998  41 82 00 0C */	beq lbl_8004EAA4
/* 8004EA9C 0004999C  C0 04 02 00 */	lfs f0, 0x200(r4)
/* 8004EAA0 000499A0  EC 42 00 24 */	fdivs f2, f2, f0
lbl_8004EAA4:
/* 8004EAA4 000499A4  88 03 00 05 */	lbz r0, 5(r3)
/* 8004EAA8 000499A8  2C 00 00 00 */	cmpwi r0, 0
/* 8004EAAC 000499AC  41 82 00 2C */	beq lbl_8004EAD8
/* 8004EAB0 000499B0  C0 22 87 40 */	lfs f1, lbl_804C0160-_SDA2_BASE_(r2)
/* 8004EAB4 000499B4  FC 02 08 40 */	fcmpo cr0, f2, f1
/* 8004EAB8 000499B8  40 81 00 08 */	ble lbl_8004EAC0
/* 8004EABC 000499BC  48 00 00 40 */	b lbl_8004EAFC
lbl_8004EAC0:
/* 8004EAC0 000499C0  C0 22 87 60 */	lfs f1, lbl_804C0180-_SDA2_BASE_(r2)
/* 8004EAC4 000499C4  FC 02 08 40 */	fcmpo cr0, f2, f1
/* 8004EAC8 000499C8  40 80 00 08 */	bge lbl_8004EAD0
/* 8004EACC 000499CC  48 00 00 30 */	b lbl_8004EAFC
lbl_8004EAD0:
/* 8004EAD0 000499D0  FC 20 10 90 */	fmr f1, f2
/* 8004EAD4 000499D4  48 00 00 28 */	b lbl_8004EAFC
lbl_8004EAD8:
/* 8004EAD8 000499D8  C0 22 87 44 */	lfs f1, lbl_804C0164-_SDA2_BASE_(r2)
/* 8004EADC 000499DC  FC 02 08 40 */	fcmpo cr0, f2, f1
/* 8004EAE0 000499E0  40 81 00 08 */	ble lbl_8004EAE8
/* 8004EAE4 000499E4  48 00 00 18 */	b lbl_8004EAFC
lbl_8004EAE8:
/* 8004EAE8 000499E8  C0 22 87 60 */	lfs f1, lbl_804C0180-_SDA2_BASE_(r2)
/* 8004EAEC 000499EC  FC 02 08 40 */	fcmpo cr0, f2, f1
/* 8004EAF0 000499F0  40 80 00 08 */	bge lbl_8004EAF8
/* 8004EAF4 000499F4  48 00 00 08 */	b lbl_8004EAFC
lbl_8004EAF8:
/* 8004EAF8 000499F8  FC 20 10 90 */	fmr f1, f2
lbl_8004EAFC:
/* 8004EAFC 000499FC  38 21 00 10 */	addi r1, r1, 0x10
/* 8004EB00 00049A00  4E 80 00 20 */	blr 

.global CalcSurroundPanRatio__Q44nw4r3snd6detail4UtilFfRCQ54nw4r3snd6detail4Util7PanInfo
CalcSurroundPanRatio__Q44nw4r3snd6detail4UtilFfRCQ54nw4r3snd6detail4Util7PanInfo:
/* 8004EB04 00049A04  C0 02 87 44 */	lfs f0, lbl_804C0164-_SDA2_BASE_(r2)
/* 8004EB08 00049A08  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8004EB0C 00049A0C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8004EB10 00049A10  40 81 00 08 */	ble lbl_8004EB18
/* 8004EB14 00049A14  48 00 00 18 */	b lbl_8004EB2C
lbl_8004EB18:
/* 8004EB18 00049A18  C0 02 87 60 */	lfs f0, lbl_804C0180-_SDA2_BASE_(r2)
/* 8004EB1C 00049A1C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8004EB20 00049A20  40 80 00 08 */	bge lbl_8004EB28
/* 8004EB24 00049A24  48 00 00 08 */	b lbl_8004EB2C
lbl_8004EB28:
/* 8004EB28 00049A28  FC 00 08 90 */	fmr f0, f1
lbl_8004EB2C:
/* 8004EB2C 00049A2C  C0 42 87 48 */	lfs f2, lbl_804C0168-_SDA2_BASE_(r2)
/* 8004EB30 00049A30  3C 80 80 39 */	lis r4, lbl_80396468@ha
/* 8004EB34 00049A34  80 03 00 00 */	lwz r0, 0(r3)
/* 8004EB38 00049A38  38 84 64 68 */	addi r4, r4, lbl_80396468@l
/* 8004EB3C 00049A3C  EC 20 00 B2 */	fmuls f1, f0, f2
/* 8004EB40 00049A40  C0 02 87 5C */	lfs f0, lbl_804C017C-_SDA2_BASE_(r2)
/* 8004EB44 00049A44  54 00 10 3A */	slwi r0, r0, 2
/* 8004EB48 00049A48  C0 62 87 44 */	lfs f3, lbl_804C0164-_SDA2_BASE_(r2)
/* 8004EB4C 00049A4C  7C 64 00 2E */	lwzx r3, r4, r0
/* 8004EB50 00049A50  EC 00 00 72 */	fmuls f0, f0, f1
/* 8004EB54 00049A54  EC 02 00 2A */	fadds f0, f2, f0
/* 8004EB58 00049A58  FC 00 00 1E */	fctiwz f0, f0
/* 8004EB5C 00049A5C  D8 01 00 08 */	stfd f0, 8(r1)
/* 8004EB60 00049A60  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8004EB64 00049A64  54 00 10 3A */	slwi r0, r0, 2
/* 8004EB68 00049A68  7C 03 04 2E */	lfsx f0, r3, r0
/* 8004EB6C 00049A6C  FC 00 18 40 */	fcmpo cr0, f0, f3
/* 8004EB70 00049A70  40 81 00 08 */	ble lbl_8004EB78
/* 8004EB74 00049A74  48 00 00 18 */	b lbl_8004EB8C
lbl_8004EB78:
/* 8004EB78 00049A78  C0 62 87 60 */	lfs f3, lbl_804C0180-_SDA2_BASE_(r2)
/* 8004EB7C 00049A7C  FC 00 18 40 */	fcmpo cr0, f0, f3
/* 8004EB80 00049A80  40 80 00 08 */	bge lbl_8004EB88
/* 8004EB84 00049A84  48 00 00 08 */	b lbl_8004EB8C
lbl_8004EB88:
/* 8004EB88 00049A88  FC 60 00 90 */	fmr f3, f0
lbl_8004EB8C:
/* 8004EB8C 00049A8C  FC 20 18 90 */	fmr f1, f3
/* 8004EB90 00049A90  38 21 00 10 */	addi r1, r1, 0x10
/* 8004EB94 00049A94  4E 80 00 20 */	blr 

.global CalcLpfFreq__Q44nw4r3snd6detail4UtilFf
CalcLpfFreq__Q44nw4r3snd6detail4UtilFf:
/* 8004EB98 00049A98  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8004EB9C 00049A9C  7C 08 02 A6 */	mflr r0
/* 8004EBA0 00049AA0  C0 42 87 40 */	lfs f2, lbl_804C0160-_SDA2_BASE_(r2)
/* 8004EBA4 00049AA4  90 01 00 14 */	stw r0, 0x14(r1)
/* 8004EBA8 00049AA8  FC 01 10 40 */	fcmpo cr0, f1, f2
/* 8004EBAC 00049AAC  40 81 00 08 */	ble lbl_8004EBB4
/* 8004EBB0 00049AB0  48 00 00 18 */	b lbl_8004EBC8
lbl_8004EBB4:
/* 8004EBB4 00049AB4  C0 42 87 60 */	lfs f2, lbl_804C0180-_SDA2_BASE_(r2)
/* 8004EBB8 00049AB8  FC 01 10 40 */	fcmpo cr0, f1, f2
/* 8004EBBC 00049ABC  40 80 00 08 */	bge lbl_8004EBC4
/* 8004EBC0 00049AC0  48 00 00 08 */	b lbl_8004EBC8
lbl_8004EBC4:
/* 8004EBC4 00049AC4  FC 40 08 90 */	fmr f2, f1
lbl_8004EBC8:
/* 8004EBC8 00049AC8  C8 22 87 80 */	lfd f1, lbl_804C01A0-_SDA2_BASE_(r2)
/* 8004EBCC 00049ACC  C8 02 87 78 */	lfd f0, lbl_804C0198-_SDA2_BASE_(r2)
/* 8004EBD0 00049AD0  FC 42 08 28 */	fsub f2, f2, f1
/* 8004EBD4 00049AD4  C8 22 87 70 */	lfd f1, lbl_804C0190-_SDA2_BASE_(r2)
/* 8004EBD8 00049AD8  FC 40 00 B2 */	fmul f2, f0, f2
/* 8004EBDC 00049ADC  48 07 22 A5 */	bl pow
/* 8004EBE0 00049AE0  C8 02 87 68 */	lfd f0, lbl_804C0188-_SDA2_BASE_(r2)
/* 8004EBE4 00049AE4  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8004EBE8 00049AE8  FC 00 00 72 */	fmul f0, f0, f1
/* 8004EBEC 00049AEC  FC 00 00 1E */	fctiwz f0, f0
/* 8004EBF0 00049AF0  D8 01 00 08 */	stfd f0, 8(r1)
/* 8004EBF4 00049AF4  80 61 00 0C */	lwz r3, 0xc(r1)
/* 8004EBF8 00049AF8  7C 08 03 A6 */	mtlr r0
/* 8004EBFC 00049AFC  38 21 00 10 */	addi r1, r1, 0x10
/* 8004EC00 00049B00  4E 80 00 20 */	blr 

.global GetRemoteFilterCoefs__Q44nw4r3snd6detail4UtilFiPUsPUsPUsPUsPUs
GetRemoteFilterCoefs__Q44nw4r3snd6detail4UtilFiPUsPUsPUsPUsPUs:
/* 8004EC04 00049B04  2C 03 00 7F */	cmpwi r3, 0x7f
/* 8004EC08 00049B08  40 81 00 0C */	ble lbl_8004EC14
/* 8004EC0C 00049B0C  38 00 00 7F */	li r0, 0x7f
/* 8004EC10 00049B10  48 00 00 0C */	b lbl_8004EC1C
lbl_8004EC14:
/* 8004EC14 00049B14  7C 60 FE 70 */	srawi r0, r3, 0x1f
/* 8004EC18 00049B18  7C 60 00 78 */	andc r0, r3, r0
lbl_8004EC1C:
/* 8004EC1C 00049B1C  1D 20 00 0A */	mulli r9, r0, 0xa
/* 8004EC20 00049B20  3C 60 80 37 */	lis r3, RemoteFilterCoefTable__Q44nw4r3snd6detail4Util@ha
/* 8004EC24 00049B24  38 63 7B 48 */	addi r3, r3, RemoteFilterCoefTable__Q44nw4r3snd6detail4Util@l
/* 8004EC28 00049B28  7C 03 4A 2E */	lhzx r0, r3, r9
/* 8004EC2C 00049B2C  7D 23 4A 14 */	add r9, r3, r9
/* 8004EC30 00049B30  A0 69 00 02 */	lhz r3, 2(r9)
/* 8004EC34 00049B34  B0 04 00 00 */	sth r0, 0(r4)
/* 8004EC38 00049B38  A0 09 00 04 */	lhz r0, 4(r9)
/* 8004EC3C 00049B3C  B0 65 00 00 */	sth r3, 0(r5)
/* 8004EC40 00049B40  A0 69 00 06 */	lhz r3, 6(r9)
/* 8004EC44 00049B44  B0 06 00 00 */	sth r0, 0(r6)
/* 8004EC48 00049B48  A0 09 00 08 */	lhz r0, 8(r9)
/* 8004EC4C 00049B4C  B0 67 00 00 */	sth r3, 0(r7)
/* 8004EC50 00049B50  B0 08 00 00 */	sth r0, 0(r8)
/* 8004EC54 00049B54  4E 80 00 20 */	blr 

.global CalcRandom__Q44nw4r3snd6detail4UtilFv
CalcRandom__Q44nw4r3snd6detail4UtilFv:
/* 8004EC58 00049B58  3C 60 00 19 */	lis r3, 0x0019660D@ha
/* 8004EC5C 00049B5C  80 8D 80 90 */	lwz r4, u$7185-_SDA_BASE_(r13)
/* 8004EC60 00049B60  38 03 66 0D */	addi r0, r3, 0x0019660D@l
/* 8004EC64 00049B64  7C 64 01 D6 */	mullw r3, r4, r0
/* 8004EC68 00049B68  3C 63 3C 6F */	addis r3, r3, 0x3c6f
/* 8004EC6C 00049B6C  38 03 F3 5F */	addi r0, r3, -3233
/* 8004EC70 00049B70  90 0D 80 90 */	stw r0, u$7185-_SDA_BASE_(r13)
/* 8004EC74 00049B74  54 03 84 3E */	srwi r3, r0, 0x10
/* 8004EC78 00049B78  4E 80 00 20 */	blr 

.global GetDataRefAddressImpl__Q44nw4r3snd6detail4UtilFQ54nw4r3snd6detail4Util7RefTypeUlPCv
GetDataRefAddressImpl__Q44nw4r3snd6detail4UtilFQ54nw4r3snd6detail4Util7RefTypeUlPCv:
/* 8004EC7C 00049B7C  2C 03 00 01 */	cmpwi r3, 1
/* 8004EC80 00049B80  40 82 00 0C */	bne lbl_8004EC8C
/* 8004EC84 00049B84  7C 64 2A 14 */	add r3, r4, r5
/* 8004EC88 00049B88  4E 80 00 20 */	blr 
lbl_8004EC8C:
/* 8004EC8C 00049B8C  2C 03 00 00 */	cmpwi r3, 0
/* 8004EC90 00049B90  38 60 00 00 */	li r3, 0
/* 8004EC94 00049B94  4C 82 00 20 */	bnelr 
/* 8004EC98 00049B98  7C 83 23 78 */	mr r3, r4
/* 8004EC9C 00049B9C  4E 80 00 20 */	blr 
