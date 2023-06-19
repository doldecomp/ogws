.include "macros.inc"

.section .rodata, "a"
.balign 0x8
.global __constants
__constants:
	.incbin "baserom.dol", 0x377358, 0x18

.section .text, "ax"
.global __cvt_fp2unsigned
__cvt_fp2unsigned:
/* 800B1C1C 000ACB1C  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800B1C20 000ACB20  3C 80 80 38 */	lis r4, __constants@ha
/* 800B1C24 000ACB24  38 84 B2 58 */	addi r4, r4, __constants@l
/* 800B1C28 000ACB28  38 60 00 00 */	li r3, 0
/* 800B1C2C 000ACB2C  C8 04 00 00 */	lfd f0, 0(r4)
/* 800B1C30 000ACB30  C8 64 00 08 */	lfd f3, 8(r4)
/* 800B1C34 000ACB34  C8 84 00 10 */	lfd f4, 0x10(r4)
/* 800B1C38 000ACB38  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 800B1C3C 000ACB3C  FF 01 18 00 */	fcmpu cr6, f1, f3
/* 800B1C40 000ACB40  41 80 00 30 */	blt lbl_800B1C70
/* 800B1C44 000ACB44  38 63 FF FF */	addi r3, r3, -1
/* 800B1C48 000ACB48  40 98 00 28 */	bge cr6, lbl_800B1C70
/* 800B1C4C 000ACB4C  FF 81 20 00 */	fcmpu cr7, f1, f4
/* 800B1C50 000ACB50  FC 40 08 90 */	fmr f2, f1
/* 800B1C54 000ACB54  41 9C 00 08 */	blt cr7, lbl_800B1C5C
/* 800B1C58 000ACB58  FC 41 20 28 */	fsub f2, f1, f4
lbl_800B1C5C:
/* 800B1C5C 000ACB5C  FC 40 10 1E */	fctiwz f2, f2
/* 800B1C60 000ACB60  D8 41 00 08 */	stfd f2, 8(r1)
/* 800B1C64 000ACB64  80 61 00 0C */	lwz r3, 0xc(r1)
/* 800B1C68 000ACB68  41 9C 00 08 */	blt cr7, lbl_800B1C70
/* 800B1C6C 000ACB6C  3C 63 80 00 */	addis r3, r3, 0x8000
lbl_800B1C70:
/* 800B1C70 000ACB70  38 21 00 10 */	addi r1, r1, 0x10
/* 800B1C74 000ACB74  4E 80 00 20 */	blr 

.global __save_fpr
__save_fpr:
.global _savefpr_14
_savefpr_14:
/* 800B1C78 000ACB78  D9 CB FF 70 */	stfd f14, -0x90(r11)

.global _savefpr_15
_savefpr_15:
/* 800B1C7C 000ACB7C  D9 EB FF 78 */	stfd f15, -0x88(r11)

.global _savefpr_16
_savefpr_16:
/* 800B1C80 000ACB80  DA 0B FF 80 */	stfd f16, -0x80(r11)

.global _savefpr_17
_savefpr_17:
/* 800B1C84 000ACB84  DA 2B FF 88 */	stfd f17, -0x78(r11)

.global _savefpr_18
_savefpr_18:
/* 800B1C88 000ACB88  DA 4B FF 90 */	stfd f18, -0x70(r11)

.global _savefpr_19
_savefpr_19:
/* 800B1C8C 000ACB8C  DA 6B FF 98 */	stfd f19, -0x68(r11)

.global _savefpr_20
_savefpr_20:
/* 800B1C90 000ACB90  DA 8B FF A0 */	stfd f20, -0x60(r11)

.global _savefpr_21
_savefpr_21:
/* 800B1C94 000ACB94  DA AB FF A8 */	stfd f21, -0x58(r11)

.global _savefpr_22
_savefpr_22:
/* 800B1C98 000ACB98  DA CB FF B0 */	stfd f22, -0x50(r11)

.global _savefpr_23
_savefpr_23:
/* 800B1C9C 000ACB9C  DA EB FF B8 */	stfd f23, -0x48(r11)

.global _savefpr_24
_savefpr_24:
/* 800B1CA0 000ACBA0  DB 0B FF C0 */	stfd f24, -0x40(r11)

.global _savefpr_25
_savefpr_25:
/* 800B1CA4 000ACBA4  DB 2B FF C8 */	stfd f25, -0x38(r11)

.global _savefpr_26
_savefpr_26:
/* 800B1CA8 000ACBA8  DB 4B FF D0 */	stfd f26, -0x30(r11)

.global _savefpr_27
_savefpr_27:
/* 800B1CAC 000ACBAC  DB 6B FF D8 */	stfd f27, -0x28(r11)

.global _savefpr_28
_savefpr_28:
/* 800B1CB0 000ACBB0  DB 8B FF E0 */	stfd f28, -0x20(r11)

.global _savefpr_29
_savefpr_29:
/* 800B1CB4 000ACBB4  DB AB FF E8 */	stfd f29, -0x18(r11)

.global _savefpr_30
_savefpr_30:
/* 800B1CB8 000ACBB8  DB CB FF F0 */	stfd f30, -0x10(r11)

.global _savefpr_31
_savefpr_31:
/* 800B1CBC 000ACBBC  DB EB FF F8 */	stfd f31, -8(r11)
/* 800B1CC0 000ACBC0  4E 80 00 20 */	blr 

.global __restore_fpr
__restore_fpr:
.global _restfpr_14
_restfpr_14:
/* 800B1CC4 000ACBC4  C9 CB FF 70 */	lfd f14, -0x90(r11)

.global _restfpr_15
_restfpr_15:
/* 800B1CC8 000ACBC8  C9 EB FF 78 */	lfd f15, -0x88(r11)

.global _restfpr_16
_restfpr_16:
/* 800B1CCC 000ACBCC  CA 0B FF 80 */	lfd f16, -0x80(r11)

.global _restfpr_17
_restfpr_17:
/* 800B1CD0 000ACBD0  CA 2B FF 88 */	lfd f17, -0x78(r11)

.global _restfpr_18
_restfpr_18:
/* 800B1CD4 000ACBD4  CA 4B FF 90 */	lfd f18, -0x70(r11)

.global _restfpr_19
_restfpr_19:
/* 800B1CD8 000ACBD8  CA 6B FF 98 */	lfd f19, -0x68(r11)

.global _restfpr_20
_restfpr_20:
/* 800B1CDC 000ACBDC  CA 8B FF A0 */	lfd f20, -0x60(r11)

.global _restfpr_21
_restfpr_21:
/* 800B1CE0 000ACBE0  CA AB FF A8 */	lfd f21, -0x58(r11)

.global _restfpr_22
_restfpr_22:
/* 800B1CE4 000ACBE4  CA CB FF B0 */	lfd f22, -0x50(r11)

.global _restfpr_23
_restfpr_23:
/* 800B1CE8 000ACBE8  CA EB FF B8 */	lfd f23, -0x48(r11)

.global _restfpr_24
_restfpr_24:
/* 800B1CEC 000ACBEC  CB 0B FF C0 */	lfd f24, -0x40(r11)

.global _restfpr_25
_restfpr_25:
/* 800B1CF0 000ACBF0  CB 2B FF C8 */	lfd f25, -0x38(r11)

.global _restfpr_26
_restfpr_26:
/* 800B1CF4 000ACBF4  CB 4B FF D0 */	lfd f26, -0x30(r11)

.global _restfpr_27
_restfpr_27:
/* 800B1CF8 000ACBF8  CB 6B FF D8 */	lfd f27, -0x28(r11)

.global _restfpr_28
_restfpr_28:
/* 800B1CFC 000ACBFC  CB 8B FF E0 */	lfd f28, -0x20(r11)

.global _restfpr_29
_restfpr_29:
/* 800B1D00 000ACC00  CB AB FF E8 */	lfd f29, -0x18(r11)

.global _restfpr_30
_restfpr_30:
/* 800B1D04 000ACC04  CB CB FF F0 */	lfd f30, -0x10(r11)

.global _restfpr_31
_restfpr_31:
/* 800B1D08 000ACC08  CB EB FF F8 */	lfd f31, -8(r11)
/* 800B1D0C 000ACC0C  4E 80 00 20 */	blr 

.global __save_gpr
__save_gpr:
.global _savegpr_14
_savegpr_14:
/* 800B1D10 000ACC10  91 CB FF B8 */	stw r14, -0x48(r11)

.global _savegpr_15
_savegpr_15:
/* 800B1D14 000ACC14  91 EB FF BC */	stw r15, -0x44(r11)

.global _savegpr_16
_savegpr_16:
/* 800B1D18 000ACC18  92 0B FF C0 */	stw r16, -0x40(r11)

.global _savegpr_17
_savegpr_17:
/* 800B1D1C 000ACC1C  92 2B FF C4 */	stw r17, -0x3c(r11)

.global _savegpr_18
_savegpr_18:
/* 800B1D20 000ACC20  92 4B FF C8 */	stw r18, -0x38(r11)

.global _savegpr_19
_savegpr_19:
/* 800B1D24 000ACC24  92 6B FF CC */	stw r19, -0x34(r11)

.global _savegpr_20
_savegpr_20:
/* 800B1D28 000ACC28  92 8B FF D0 */	stw r20, -0x30(r11)

.global _savegpr_21
_savegpr_21:
/* 800B1D2C 000ACC2C  92 AB FF D4 */	stw r21, -0x2c(r11)

.global _savegpr_22
_savegpr_22:
/* 800B1D30 000ACC30  92 CB FF D8 */	stw r22, -0x28(r11)

.global _savegpr_23
_savegpr_23:
/* 800B1D34 000ACC34  92 EB FF DC */	stw r23, -0x24(r11)

.global _savegpr_24
_savegpr_24:
/* 800B1D38 000ACC38  93 0B FF E0 */	stw r24, -0x20(r11)

.global _savegpr_25
_savegpr_25:
/* 800B1D3C 000ACC3C  93 2B FF E4 */	stw r25, -0x1c(r11)

.global _savegpr_26
_savegpr_26:
/* 800B1D40 000ACC40  93 4B FF E8 */	stw r26, -0x18(r11)

.global _savegpr_27
_savegpr_27:
/* 800B1D44 000ACC44  93 6B FF EC */	stw r27, -0x14(r11)

.global _savegpr_28
_savegpr_28:
/* 800B1D48 000ACC48  93 8B FF F0 */	stw r28, -0x10(r11)

.global _savegpr_29
_savegpr_29:
/* 800B1D4C 000ACC4C  93 AB FF F4 */	stw r29, -0xc(r11)

.global _savegpr_30
_savegpr_30:
/* 800B1D50 000ACC50  93 CB FF F8 */	stw r30, -8(r11)

.global _savegpr_31
_savegpr_31:
/* 800B1D54 000ACC54  93 EB FF FC */	stw r31, -4(r11)
/* 800B1D58 000ACC58  4E 80 00 20 */	blr 

.global __restore_gpr
__restore_gpr:
.global _restgpr_14
_restgpr_14:
/* 800B1D5C 000ACC5C  81 CB FF B8 */	lwz r14, -0x48(r11)

.global _restgpr_15
_restgpr_15:
/* 800B1D60 000ACC60  81 EB FF BC */	lwz r15, -0x44(r11)

.global _restgpr_16
_restgpr_16:
/* 800B1D64 000ACC64  82 0B FF C0 */	lwz r16, -0x40(r11)

.global _restgpr_17
_restgpr_17:
/* 800B1D68 000ACC68  82 2B FF C4 */	lwz r17, -0x3c(r11)

.global _restgpr_18
_restgpr_18:
/* 800B1D6C 000ACC6C  82 4B FF C8 */	lwz r18, -0x38(r11)

.global _restgpr_19
_restgpr_19:
/* 800B1D70 000ACC70  82 6B FF CC */	lwz r19, -0x34(r11)

.global _restgpr_20
_restgpr_20:
/* 800B1D74 000ACC74  82 8B FF D0 */	lwz r20, -0x30(r11)

.global _restgpr_21
_restgpr_21:
/* 800B1D78 000ACC78  82 AB FF D4 */	lwz r21, -0x2c(r11)

.global _restgpr_22
_restgpr_22:
/* 800B1D7C 000ACC7C  82 CB FF D8 */	lwz r22, -0x28(r11)

.global _restgpr_23
_restgpr_23:
/* 800B1D80 000ACC80  82 EB FF DC */	lwz r23, -0x24(r11)

.global _restgpr_24
_restgpr_24:
/* 800B1D84 000ACC84  83 0B FF E0 */	lwz r24, -0x20(r11)

.global _restgpr_25
_restgpr_25:
/* 800B1D88 000ACC88  83 2B FF E4 */	lwz r25, -0x1c(r11)

.global _restgpr_26
_restgpr_26:
/* 800B1D8C 000ACC8C  83 4B FF E8 */	lwz r26, -0x18(r11)

.global _restgpr_27
_restgpr_27:
/* 800B1D90 000ACC90  83 6B FF EC */	lwz r27, -0x14(r11)

.global _restgpr_28
_restgpr_28:
/* 800B1D94 000ACC94  83 8B FF F0 */	lwz r28, -0x10(r11)

.global _restgpr_29
_restgpr_29:
/* 800B1D98 000ACC98  83 AB FF F4 */	lwz r29, -0xc(r11)

.global _restgpr_30
_restgpr_30:
/* 800B1D9C 000ACC9C  83 CB FF F8 */	lwz r30, -8(r11)

.global _restgpr_31
_restgpr_31:
/* 800B1DA0 000ACCA0  83 EB FF FC */	lwz r31, -4(r11)
/* 800B1DA4 000ACCA4  4E 80 00 20 */	blr 

.global __div2u
__div2u:
/* 800B1DA8 000ACCA8  2C 03 00 00 */	cmpwi r3, 0
/* 800B1DAC 000ACCAC  7C 60 00 34 */	cntlzw r0, r3
/* 800B1DB0 000ACCB0  7C 89 00 34 */	cntlzw r9, r4
/* 800B1DB4 000ACCB4  40 82 00 08 */	bne lbl_800B1DBC
/* 800B1DB8 000ACCB8  38 09 00 20 */	addi r0, r9, 0x20
lbl_800B1DBC:
/* 800B1DBC 000ACCBC  2C 05 00 00 */	cmpwi r5, 0
/* 800B1DC0 000ACCC0  7C A9 00 34 */	cntlzw r9, r5
/* 800B1DC4 000ACCC4  7C CA 00 34 */	cntlzw r10, r6
/* 800B1DC8 000ACCC8  40 82 00 08 */	bne lbl_800B1DD0
/* 800B1DCC 000ACCCC  39 2A 00 20 */	addi r9, r10, 0x20
lbl_800B1DD0:
/* 800B1DD0 000ACCD0  7C 00 48 00 */	cmpw r0, r9
/* 800B1DD4 000ACCD4  21 40 00 40 */	subfic r10, r0, 0x40
/* 800B1DD8 000ACCD8  41 81 00 B0 */	bgt lbl_800B1E88
/* 800B1DDC 000ACCDC  39 29 00 01 */	addi r9, r9, 1
/* 800B1DE0 000ACCE0  21 29 00 40 */	subfic r9, r9, 0x40
/* 800B1DE4 000ACCE4  7C 00 4A 14 */	add r0, r0, r9
/* 800B1DE8 000ACCE8  7D 29 50 50 */	subf r9, r9, r10
/* 800B1DEC 000ACCEC  7D 29 03 A6 */	mtctr r9
/* 800B1DF0 000ACCF0  2C 09 00 20 */	cmpwi r9, 0x20
/* 800B1DF4 000ACCF4  38 E9 FF E0 */	addi r7, r9, -32
/* 800B1DF8 000ACCF8  41 80 00 10 */	blt lbl_800B1E08
/* 800B1DFC 000ACCFC  7C 68 3C 30 */	srw r8, r3, r7
/* 800B1E00 000ACD00  38 E0 00 00 */	li r7, 0
/* 800B1E04 000ACD04  48 00 00 18 */	b lbl_800B1E1C
lbl_800B1E08:
/* 800B1E08 000ACD08  7C 88 4C 30 */	srw r8, r4, r9
/* 800B1E0C 000ACD0C  20 E9 00 20 */	subfic r7, r9, 0x20
/* 800B1E10 000ACD10  7C 67 38 30 */	slw r7, r3, r7
/* 800B1E14 000ACD14  7D 08 3B 78 */	or r8, r8, r7
/* 800B1E18 000ACD18  7C 67 4C 30 */	srw r7, r3, r9
lbl_800B1E1C:
/* 800B1E1C 000ACD1C  2C 00 00 20 */	cmpwi r0, 0x20
/* 800B1E20 000ACD20  31 20 FF E0 */	addic r9, r0, -32
/* 800B1E24 000ACD24  41 80 00 10 */	blt lbl_800B1E34
/* 800B1E28 000ACD28  7C 83 48 30 */	slw r3, r4, r9
/* 800B1E2C 000ACD2C  38 80 00 00 */	li r4, 0
/* 800B1E30 000ACD30  48 00 00 18 */	b lbl_800B1E48
lbl_800B1E34:
/* 800B1E34 000ACD34  7C 63 00 30 */	slw r3, r3, r0
/* 800B1E38 000ACD38  21 20 00 20 */	subfic r9, r0, 0x20
/* 800B1E3C 000ACD3C  7C 89 4C 30 */	srw r9, r4, r9
/* 800B1E40 000ACD40  7C 63 4B 78 */	or r3, r3, r9
/* 800B1E44 000ACD44  7C 84 00 30 */	slw r4, r4, r0
lbl_800B1E48:
/* 800B1E48 000ACD48  39 40 FF FF */	li r10, -1
/* 800B1E4C 000ACD4C  30 E7 00 00 */	addic r7, r7, 0
lbl_800B1E50:
/* 800B1E50 000ACD50  7C 84 21 14 */	adde r4, r4, r4
/* 800B1E54 000ACD54  7C 63 19 14 */	adde r3, r3, r3
/* 800B1E58 000ACD58  7D 08 41 14 */	adde r8, r8, r8
/* 800B1E5C 000ACD5C  7C E7 39 14 */	adde r7, r7, r7
/* 800B1E60 000ACD60  7C 06 40 10 */	subfc r0, r6, r8
/* 800B1E64 000ACD64  7D 25 39 11 */	subfe. r9, r5, r7
/* 800B1E68 000ACD68  41 80 00 10 */	blt lbl_800B1E78
/* 800B1E6C 000ACD6C  7C 08 03 78 */	mr r8, r0
/* 800B1E70 000ACD70  7D 27 4B 78 */	mr r7, r9
/* 800B1E74 000ACD74  30 0A 00 01 */	addic r0, r10, 1
lbl_800B1E78:
/* 800B1E78 000ACD78  42 00 FF D8 */	bdnz lbl_800B1E50
/* 800B1E7C 000ACD7C  7C 84 21 14 */	adde r4, r4, r4
/* 800B1E80 000ACD80  7C 63 19 14 */	adde r3, r3, r3
/* 800B1E84 000ACD84  4E 80 00 20 */	blr 
lbl_800B1E88:
/* 800B1E88 000ACD88  38 80 00 00 */	li r4, 0
/* 800B1E8C 000ACD8C  38 60 00 00 */	li r3, 0
/* 800B1E90 000ACD90  4E 80 00 20 */	blr 

.global __div2i
__div2i:
/* 800B1E94 000ACD94  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800B1E98 000ACD98  54 69 00 01 */	rlwinm. r9, r3, 0, 0, 0
/* 800B1E9C 000ACD9C  41 82 00 0C */	beq lbl_800B1EA8
/* 800B1EA0 000ACDA0  20 84 00 00 */	subfic r4, r4, 0
/* 800B1EA4 000ACDA4  7C 63 01 90 */	subfze r3, r3
lbl_800B1EA8:
/* 800B1EA8 000ACDA8  91 21 00 08 */	stw r9, 8(r1)
/* 800B1EAC 000ACDAC  54 AA 00 01 */	rlwinm. r10, r5, 0, 0, 0
/* 800B1EB0 000ACDB0  41 82 00 0C */	beq lbl_800B1EBC
/* 800B1EB4 000ACDB4  20 C6 00 00 */	subfic r6, r6, 0
/* 800B1EB8 000ACDB8  7C A5 01 90 */	subfze r5, r5
lbl_800B1EBC:
/* 800B1EBC 000ACDBC  91 41 00 0C */	stw r10, 0xc(r1)
/* 800B1EC0 000ACDC0  2C 03 00 00 */	cmpwi r3, 0
/* 800B1EC4 000ACDC4  7C 60 00 34 */	cntlzw r0, r3
/* 800B1EC8 000ACDC8  7C 89 00 34 */	cntlzw r9, r4
/* 800B1ECC 000ACDCC  40 82 00 08 */	bne lbl_800B1ED4
/* 800B1ED0 000ACDD0  38 09 00 20 */	addi r0, r9, 0x20
lbl_800B1ED4:
/* 800B1ED4 000ACDD4  2C 05 00 00 */	cmpwi r5, 0
/* 800B1ED8 000ACDD8  7C A9 00 34 */	cntlzw r9, r5
/* 800B1EDC 000ACDDC  7C CA 00 34 */	cntlzw r10, r6
/* 800B1EE0 000ACDE0  40 82 00 08 */	bne lbl_800B1EE8
/* 800B1EE4 000ACDE4  39 2A 00 20 */	addi r9, r10, 0x20
lbl_800B1EE8:
/* 800B1EE8 000ACDE8  7C 00 48 00 */	cmpw r0, r9
/* 800B1EEC 000ACDEC  21 40 00 40 */	subfic r10, r0, 0x40
/* 800B1EF0 000ACDF0  41 81 00 CC */	bgt lbl_800B1FBC
/* 800B1EF4 000ACDF4  39 29 00 01 */	addi r9, r9, 1
/* 800B1EF8 000ACDF8  21 29 00 40 */	subfic r9, r9, 0x40
/* 800B1EFC 000ACDFC  7C 00 4A 14 */	add r0, r0, r9
/* 800B1F00 000ACE00  7D 29 50 50 */	subf r9, r9, r10
/* 800B1F04 000ACE04  7D 29 03 A6 */	mtctr r9
/* 800B1F08 000ACE08  2C 09 00 20 */	cmpwi r9, 0x20
/* 800B1F0C 000ACE0C  38 E9 FF E0 */	addi r7, r9, -32
/* 800B1F10 000ACE10  41 80 00 10 */	blt lbl_800B1F20
/* 800B1F14 000ACE14  7C 68 3C 30 */	srw r8, r3, r7
/* 800B1F18 000ACE18  38 E0 00 00 */	li r7, 0
/* 800B1F1C 000ACE1C  48 00 00 18 */	b lbl_800B1F34
lbl_800B1F20:
/* 800B1F20 000ACE20  7C 88 4C 30 */	srw r8, r4, r9
/* 800B1F24 000ACE24  20 E9 00 20 */	subfic r7, r9, 0x20
/* 800B1F28 000ACE28  7C 67 38 30 */	slw r7, r3, r7
/* 800B1F2C 000ACE2C  7D 08 3B 78 */	or r8, r8, r7
/* 800B1F30 000ACE30  7C 67 4C 30 */	srw r7, r3, r9
lbl_800B1F34:
/* 800B1F34 000ACE34  2C 00 00 20 */	cmpwi r0, 0x20
/* 800B1F38 000ACE38  31 20 FF E0 */	addic r9, r0, -32
/* 800B1F3C 000ACE3C  41 80 00 10 */	blt lbl_800B1F4C
/* 800B1F40 000ACE40  7C 83 48 30 */	slw r3, r4, r9
/* 800B1F44 000ACE44  38 80 00 00 */	li r4, 0
/* 800B1F48 000ACE48  48 00 00 18 */	b lbl_800B1F60
lbl_800B1F4C:
/* 800B1F4C 000ACE4C  7C 63 00 30 */	slw r3, r3, r0
/* 800B1F50 000ACE50  21 20 00 20 */	subfic r9, r0, 0x20
/* 800B1F54 000ACE54  7C 89 4C 30 */	srw r9, r4, r9
/* 800B1F58 000ACE58  7C 63 4B 78 */	or r3, r3, r9
/* 800B1F5C 000ACE5C  7C 84 00 30 */	slw r4, r4, r0
lbl_800B1F60:
/* 800B1F60 000ACE60  39 40 FF FF */	li r10, -1
/* 800B1F64 000ACE64  30 E7 00 00 */	addic r7, r7, 0
lbl_800B1F68:
/* 800B1F68 000ACE68  7C 84 21 14 */	adde r4, r4, r4
/* 800B1F6C 000ACE6C  7C 63 19 14 */	adde r3, r3, r3
/* 800B1F70 000ACE70  7D 08 41 14 */	adde r8, r8, r8
/* 800B1F74 000ACE74  7C E7 39 14 */	adde r7, r7, r7
/* 800B1F78 000ACE78  7C 06 40 10 */	subfc r0, r6, r8
/* 800B1F7C 000ACE7C  7D 25 39 11 */	subfe. r9, r5, r7
/* 800B1F80 000ACE80  41 80 00 10 */	blt lbl_800B1F90
/* 800B1F84 000ACE84  7C 08 03 78 */	mr r8, r0
/* 800B1F88 000ACE88  7D 27 4B 78 */	mr r7, r9
/* 800B1F8C 000ACE8C  30 0A 00 01 */	addic r0, r10, 1
lbl_800B1F90:
/* 800B1F90 000ACE90  42 00 FF D8 */	bdnz lbl_800B1F68
/* 800B1F94 000ACE94  7C 84 21 14 */	adde r4, r4, r4
/* 800B1F98 000ACE98  7C 63 19 14 */	adde r3, r3, r3
/* 800B1F9C 000ACE9C  81 21 00 08 */	lwz r9, 8(r1)
/* 800B1FA0 000ACEA0  81 41 00 0C */	lwz r10, 0xc(r1)
/* 800B1FA4 000ACEA4  7D 27 52 79 */	xor. r7, r9, r10
/* 800B1FA8 000ACEA8  41 82 00 10 */	beq lbl_800B1FB8
/* 800B1FAC 000ACEAC  2C 09 00 00 */	cmpwi r9, 0
/* 800B1FB0 000ACEB0  20 84 00 00 */	subfic r4, r4, 0
/* 800B1FB4 000ACEB4  7C 63 01 90 */	subfze r3, r3
lbl_800B1FB8:
/* 800B1FB8 000ACEB8  48 00 00 0C */	b lbl_800B1FC4
lbl_800B1FBC:
/* 800B1FBC 000ACEBC  38 80 00 00 */	li r4, 0
/* 800B1FC0 000ACEC0  38 60 00 00 */	li r3, 0
lbl_800B1FC4:
/* 800B1FC4 000ACEC4  38 21 00 10 */	addi r1, r1, 0x10
/* 800B1FC8 000ACEC8  4E 80 00 20 */	blr 

.global __mod2u
__mod2u:
/* 800B1FCC 000ACECC  2C 03 00 00 */	cmpwi r3, 0
/* 800B1FD0 000ACED0  7C 60 00 34 */	cntlzw r0, r3
/* 800B1FD4 000ACED4  7C 89 00 34 */	cntlzw r9, r4
/* 800B1FD8 000ACED8  40 82 00 08 */	bne lbl_800B1FE0
/* 800B1FDC 000ACEDC  38 09 00 20 */	addi r0, r9, 0x20
lbl_800B1FE0:
/* 800B1FE0 000ACEE0  2C 05 00 00 */	cmpwi r5, 0
/* 800B1FE4 000ACEE4  7C A9 00 34 */	cntlzw r9, r5
/* 800B1FE8 000ACEE8  7C CA 00 34 */	cntlzw r10, r6
/* 800B1FEC 000ACEEC  40 82 00 08 */	bne lbl_800B1FF4
/* 800B1FF0 000ACEF0  39 2A 00 20 */	addi r9, r10, 0x20
lbl_800B1FF4:
/* 800B1FF4 000ACEF4  7C 00 48 00 */	cmpw r0, r9
/* 800B1FF8 000ACEF8  21 40 00 40 */	subfic r10, r0, 0x40
/* 800B1FFC 000ACEFC  41 81 00 B0 */	bgt lbl_800B20AC
/* 800B2000 000ACF00  39 29 00 01 */	addi r9, r9, 1
/* 800B2004 000ACF04  21 29 00 40 */	subfic r9, r9, 0x40
/* 800B2008 000ACF08  7C 00 4A 14 */	add r0, r0, r9
/* 800B200C 000ACF0C  7D 29 50 50 */	subf r9, r9, r10
/* 800B2010 000ACF10  7D 29 03 A6 */	mtctr r9
/* 800B2014 000ACF14  2C 09 00 20 */	cmpwi r9, 0x20
/* 800B2018 000ACF18  38 E9 FF E0 */	addi r7, r9, -32
/* 800B201C 000ACF1C  41 80 00 10 */	blt lbl_800B202C
/* 800B2020 000ACF20  7C 68 3C 30 */	srw r8, r3, r7
/* 800B2024 000ACF24  38 E0 00 00 */	li r7, 0
/* 800B2028 000ACF28  48 00 00 18 */	b lbl_800B2040
lbl_800B202C:
/* 800B202C 000ACF2C  7C 88 4C 30 */	srw r8, r4, r9
/* 800B2030 000ACF30  20 E9 00 20 */	subfic r7, r9, 0x20
/* 800B2034 000ACF34  7C 67 38 30 */	slw r7, r3, r7
/* 800B2038 000ACF38  7D 08 3B 78 */	or r8, r8, r7
/* 800B203C 000ACF3C  7C 67 4C 30 */	srw r7, r3, r9
lbl_800B2040:
/* 800B2040 000ACF40  2C 00 00 20 */	cmpwi r0, 0x20
/* 800B2044 000ACF44  31 20 FF E0 */	addic r9, r0, -32
/* 800B2048 000ACF48  41 80 00 10 */	blt lbl_800B2058
/* 800B204C 000ACF4C  7C 83 48 30 */	slw r3, r4, r9
/* 800B2050 000ACF50  38 80 00 00 */	li r4, 0
/* 800B2054 000ACF54  48 00 00 18 */	b lbl_800B206C
lbl_800B2058:
/* 800B2058 000ACF58  7C 63 00 30 */	slw r3, r3, r0
/* 800B205C 000ACF5C  21 20 00 20 */	subfic r9, r0, 0x20
/* 800B2060 000ACF60  7C 89 4C 30 */	srw r9, r4, r9
/* 800B2064 000ACF64  7C 63 4B 78 */	or r3, r3, r9
/* 800B2068 000ACF68  7C 84 00 30 */	slw r4, r4, r0
lbl_800B206C:
/* 800B206C 000ACF6C  39 40 FF FF */	li r10, -1
/* 800B2070 000ACF70  30 E7 00 00 */	addic r7, r7, 0
lbl_800B2074:
/* 800B2074 000ACF74  7C 84 21 14 */	adde r4, r4, r4
/* 800B2078 000ACF78  7C 63 19 14 */	adde r3, r3, r3
/* 800B207C 000ACF7C  7D 08 41 14 */	adde r8, r8, r8
/* 800B2080 000ACF80  7C E7 39 14 */	adde r7, r7, r7
/* 800B2084 000ACF84  7C 06 40 10 */	subfc r0, r6, r8
/* 800B2088 000ACF88  7D 25 39 11 */	subfe. r9, r5, r7
/* 800B208C 000ACF8C  41 80 00 10 */	blt lbl_800B209C
/* 800B2090 000ACF90  7C 08 03 78 */	mr r8, r0
/* 800B2094 000ACF94  7D 27 4B 78 */	mr r7, r9
/* 800B2098 000ACF98  30 0A 00 01 */	addic r0, r10, 1
lbl_800B209C:
/* 800B209C 000ACF9C  42 00 FF D8 */	bdnz lbl_800B2074
/* 800B20A0 000ACFA0  7D 04 43 78 */	mr r4, r8
/* 800B20A4 000ACFA4  7C E3 3B 78 */	mr r3, r7
/* 800B20A8 000ACFA8  4E 80 00 20 */	blr 
lbl_800B20AC:
/* 800B20AC 000ACFAC  4E 80 00 20 */	blr 

.global __mod2i
__mod2i:
/* 800B20B0 000ACFB0  2F 83 00 00 */	cmpwi cr7, r3, 0
/* 800B20B4 000ACFB4  40 9C 00 0C */	bge cr7, lbl_800B20C0
/* 800B20B8 000ACFB8  20 84 00 00 */	subfic r4, r4, 0
/* 800B20BC 000ACFBC  7C 63 01 90 */	subfze r3, r3
lbl_800B20C0:
/* 800B20C0 000ACFC0  2C 05 00 00 */	cmpwi r5, 0
/* 800B20C4 000ACFC4  40 80 00 0C */	bge lbl_800B20D0
/* 800B20C8 000ACFC8  20 C6 00 00 */	subfic r6, r6, 0
/* 800B20CC 000ACFCC  7C A5 01 90 */	subfze r5, r5
lbl_800B20D0:
/* 800B20D0 000ACFD0  2C 03 00 00 */	cmpwi r3, 0
/* 800B20D4 000ACFD4  7C 60 00 34 */	cntlzw r0, r3
/* 800B20D8 000ACFD8  7C 89 00 34 */	cntlzw r9, r4
/* 800B20DC 000ACFDC  40 82 00 08 */	bne lbl_800B20E4
/* 800B20E0 000ACFE0  38 09 00 20 */	addi r0, r9, 0x20
lbl_800B20E4:
/* 800B20E4 000ACFE4  2C 05 00 00 */	cmpwi r5, 0
/* 800B20E8 000ACFE8  7C A9 00 34 */	cntlzw r9, r5
/* 800B20EC 000ACFEC  7C CA 00 34 */	cntlzw r10, r6
/* 800B20F0 000ACFF0  40 82 00 08 */	bne lbl_800B20F8
/* 800B20F4 000ACFF4  39 2A 00 20 */	addi r9, r10, 0x20
lbl_800B20F8:
/* 800B20F8 000ACFF8  7C 00 48 00 */	cmpw r0, r9
/* 800B20FC 000ACFFC  21 40 00 40 */	subfic r10, r0, 0x40
/* 800B2100 000AD000  41 81 00 AC */	bgt lbl_800B21AC
/* 800B2104 000AD004  39 29 00 01 */	addi r9, r9, 1
/* 800B2108 000AD008  21 29 00 40 */	subfic r9, r9, 0x40
/* 800B210C 000AD00C  7C 00 4A 14 */	add r0, r0, r9
/* 800B2110 000AD010  7D 29 50 50 */	subf r9, r9, r10
/* 800B2114 000AD014  7D 29 03 A6 */	mtctr r9
/* 800B2118 000AD018  2C 09 00 20 */	cmpwi r9, 0x20
/* 800B211C 000AD01C  38 E9 FF E0 */	addi r7, r9, -32
/* 800B2120 000AD020  41 80 00 10 */	blt lbl_800B2130
/* 800B2124 000AD024  7C 68 3C 30 */	srw r8, r3, r7
/* 800B2128 000AD028  38 E0 00 00 */	li r7, 0
/* 800B212C 000AD02C  48 00 00 18 */	b lbl_800B2144
lbl_800B2130:
/* 800B2130 000AD030  7C 88 4C 30 */	srw r8, r4, r9
/* 800B2134 000AD034  20 E9 00 20 */	subfic r7, r9, 0x20
/* 800B2138 000AD038  7C 67 38 30 */	slw r7, r3, r7
/* 800B213C 000AD03C  7D 08 3B 78 */	or r8, r8, r7
/* 800B2140 000AD040  7C 67 4C 30 */	srw r7, r3, r9
lbl_800B2144:
/* 800B2144 000AD044  2C 00 00 20 */	cmpwi r0, 0x20
/* 800B2148 000AD048  31 20 FF E0 */	addic r9, r0, -32
/* 800B214C 000AD04C  41 80 00 10 */	blt lbl_800B215C
/* 800B2150 000AD050  7C 83 48 30 */	slw r3, r4, r9
/* 800B2154 000AD054  38 80 00 00 */	li r4, 0
/* 800B2158 000AD058  48 00 00 18 */	b lbl_800B2170
lbl_800B215C:
/* 800B215C 000AD05C  7C 63 00 30 */	slw r3, r3, r0
/* 800B2160 000AD060  21 20 00 20 */	subfic r9, r0, 0x20
/* 800B2164 000AD064  7C 89 4C 30 */	srw r9, r4, r9
/* 800B2168 000AD068  7C 63 4B 78 */	or r3, r3, r9
/* 800B216C 000AD06C  7C 84 00 30 */	slw r4, r4, r0
lbl_800B2170:
/* 800B2170 000AD070  39 40 FF FF */	li r10, -1
/* 800B2174 000AD074  30 E7 00 00 */	addic r7, r7, 0
lbl_800B2178:
/* 800B2178 000AD078  7C 84 21 14 */	adde r4, r4, r4
/* 800B217C 000AD07C  7C 63 19 14 */	adde r3, r3, r3
/* 800B2180 000AD080  7D 08 41 14 */	adde r8, r8, r8
/* 800B2184 000AD084  7C E7 39 14 */	adde r7, r7, r7
/* 800B2188 000AD088  7C 06 40 10 */	subfc r0, r6, r8
/* 800B218C 000AD08C  7D 25 39 11 */	subfe. r9, r5, r7
/* 800B2190 000AD090  41 80 00 10 */	blt lbl_800B21A0
/* 800B2194 000AD094  7C 08 03 78 */	mr r8, r0
/* 800B2198 000AD098  7D 27 4B 78 */	mr r7, r9
/* 800B219C 000AD09C  30 0A 00 01 */	addic r0, r10, 1
lbl_800B21A0:
/* 800B21A0 000AD0A0  42 00 FF D8 */	bdnz lbl_800B2178
/* 800B21A4 000AD0A4  7D 04 43 78 */	mr r4, r8
/* 800B21A8 000AD0A8  7C E3 3B 78 */	mr r3, r7
lbl_800B21AC:
/* 800B21AC 000AD0AC  40 9C 00 0C */	bge cr7, lbl_800B21B8
/* 800B21B0 000AD0B0  20 84 00 00 */	subfic r4, r4, 0
/* 800B21B4 000AD0B4  7C 63 01 90 */	subfze r3, r3
lbl_800B21B8:
/* 800B21B8 000AD0B8  4E 80 00 20 */	blr 

.global __shl2i
__shl2i:
/* 800B21BC 000AD0BC  21 05 00 20 */	subfic r8, r5, 0x20
/* 800B21C0 000AD0C0  31 25 FF E0 */	addic r9, r5, -32
/* 800B21C4 000AD0C4  7C 63 28 30 */	slw r3, r3, r5
/* 800B21C8 000AD0C8  7C 8A 44 30 */	srw r10, r4, r8
/* 800B21CC 000AD0CC  7C 63 53 78 */	or r3, r3, r10
/* 800B21D0 000AD0D0  7C 8A 48 30 */	slw r10, r4, r9
/* 800B21D4 000AD0D4  7C 63 53 78 */	or r3, r3, r10
/* 800B21D8 000AD0D8  7C 84 28 30 */	slw r4, r4, r5
/* 800B21DC 000AD0DC  4E 80 00 20 */	blr 

.global __cvt_dbl_ull
__cvt_dbl_ull:
/* 800B21E0 000AD0E0  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800B21E4 000AD0E4  D8 21 00 08 */	stfd f1, 8(r1)
/* 800B21E8 000AD0E8  80 61 00 08 */	lwz r3, 8(r1)
/* 800B21EC 000AD0EC  80 81 00 0C */	lwz r4, 0xc(r1)
/* 800B21F0 000AD0F0  54 65 65 7E */	rlwinm r5, r3, 0xc, 0x15, 0x1f
/* 800B21F4 000AD0F4  28 05 03 FF */	cmplwi r5, 0x3ff
/* 800B21F8 000AD0F8  40 80 00 10 */	bge lbl_800B2208
lbl_800B21FC:
/* 800B21FC 000AD0FC  38 60 00 00 */	li r3, 0
/* 800B2200 000AD100  38 80 00 00 */	li r4, 0
/* 800B2204 000AD104  48 00 00 7C */	b lbl_800B2280
lbl_800B2208:
/* 800B2208 000AD108  54 66 00 01 */	rlwinm. r6, r3, 0, 0, 0
/* 800B220C 000AD10C  40 82 FF F0 */	bne lbl_800B21FC
/* 800B2210 000AD110  54 63 03 3E */	clrlwi r3, r3, 0xc
/* 800B2214 000AD114  64 63 00 10 */	oris r3, r3, 0x10
/* 800B2218 000AD118  38 A5 FB CD */	addi r5, r5, -1075
/* 800B221C 000AD11C  2C 05 00 00 */	cmpwi r5, 0
/* 800B2220 000AD120  40 80 00 2C */	bge lbl_800B224C
/* 800B2224 000AD124  7C A5 00 D0 */	neg r5, r5
/* 800B2228 000AD128  21 05 00 20 */	subfic r8, r5, 0x20
/* 800B222C 000AD12C  31 25 FF E0 */	addic r9, r5, -32
/* 800B2230 000AD130  7C 84 2C 30 */	srw r4, r4, r5
/* 800B2234 000AD134  7C 6A 40 30 */	slw r10, r3, r8
/* 800B2238 000AD138  7C 84 53 78 */	or r4, r4, r10
/* 800B223C 000AD13C  7C 6A 4C 30 */	srw r10, r3, r9
/* 800B2240 000AD140  7C 84 53 78 */	or r4, r4, r10
/* 800B2244 000AD144  7C 63 2C 30 */	srw r3, r3, r5
/* 800B2248 000AD148  48 00 00 38 */	b lbl_800B2280
lbl_800B224C:
/* 800B224C 000AD14C  2C 05 00 0B */	cmpwi r5, 0xb
/* 800B2250 000AD150  40 A1 00 10 */	ble+ lbl_800B2260
/* 800B2254 000AD154  38 60 FF FF */	li r3, -1
/* 800B2258 000AD158  38 80 FF FF */	li r4, -1
/* 800B225C 000AD15C  48 00 00 24 */	b lbl_800B2280
lbl_800B2260:
/* 800B2260 000AD160  21 05 00 20 */	subfic r8, r5, 0x20
/* 800B2264 000AD164  31 25 FF E0 */	addic r9, r5, -32
/* 800B2268 000AD168  7C 63 28 30 */	slw r3, r3, r5
/* 800B226C 000AD16C  7C 8A 44 30 */	srw r10, r4, r8
/* 800B2270 000AD170  7C 63 53 78 */	or r3, r3, r10
/* 800B2274 000AD174  7C 8A 48 30 */	slw r10, r4, r9
/* 800B2278 000AD178  7C 63 53 78 */	or r3, r3, r10
/* 800B227C 000AD17C  7C 84 28 30 */	slw r4, r4, r5
lbl_800B2280:
/* 800B2280 000AD180  38 21 00 10 */	addi r1, r1, 0x10
/* 800B2284 000AD184  4E 80 00 20 */	blr 
