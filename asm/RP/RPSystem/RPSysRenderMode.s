# 
# Render mode is managed by this TU and RPSysSystem.
# BBA and later EAD games refactored everything into once class: RenderModeMgr.
# The name "RPSysRenderMode" is only an educated guess.
# 

.include "macros.inc"

.section .data, "wa"
.balign 0x8
# Render mode objects
	.incbin "baserom.dol", 0x3B5760, 0x130

.section .rodata, "a"
.balign 0x8
.global sRenderModeTable__15RPSysRenderMode
sRenderModeTable__15RPSysRenderMode:
	.incbin "baserom.dol", 0x37E538, 0x18

.section .text, "ax"
# "RPSysRenderMode::adjust" may be a good name?
# Function adjusts viXOrigin/viWidth based on some widescreen related parameters.
# (See Sys::RenderModeMgr::start in BBA)
.global func_801855BC
func_801855BC:
/* 801855BC 001804BC  2C 06 00 00 */	cmpwi r6, 0
/* 801855C0 001804C0  41 82 00 24 */	beq lbl_801855E4
/* 801855C4 001804C4  2C 05 00 02 */	cmpwi r5, 2
/* 801855C8 001804C8  40 82 00 10 */	bne lbl_801855D8
/* 801855CC 001804CC  38 00 02 AA */	li r0, 0x2aa
/* 801855D0 001804D0  B0 04 00 00 */	sth r0, 0(r4)
/* 801855D4 001804D4  48 00 00 2C */	b lbl_80185600
lbl_801855D8:
/* 801855D8 001804D8  38 00 02 AE */	li r0, 0x2ae
/* 801855DC 001804DC  B0 04 00 00 */	sth r0, 0(r4)
/* 801855E0 001804E0  48 00 00 20 */	b lbl_80185600
lbl_801855E4:
/* 801855E4 001804E4  2C 05 00 02 */	cmpwi r5, 2
/* 801855E8 001804E8  40 82 00 10 */	bne lbl_801855F8
/* 801855EC 001804EC  38 00 02 9A */	li r0, 0x29a
/* 801855F0 001804F0  B0 04 00 00 */	sth r0, 0(r4)
/* 801855F4 001804F4  48 00 00 0C */	b lbl_80185600
lbl_801855F8:
/* 801855F8 001804F8  38 00 02 9E */	li r0, 0x29e
/* 801855FC 001804FC  B0 04 00 00 */	sth r0, 0(r4)
lbl_80185600:
/* 80185600 00180500  2C 05 00 02 */	cmpwi r5, 2
/* 80185604 00180504  41 82 00 3C */	beq lbl_80185640
/* 80185608 00180508  40 80 00 10 */	bge lbl_80185618
/* 8018560C 0018050C  2C 05 00 00 */	cmpwi r5, 0
/* 80185610 00180510  40 80 00 14 */	bge lbl_80185624
/* 80185614 00180514  4E 80 00 20 */	blr 
lbl_80185618:
/* 80185618 00180518  2C 05 00 05 */	cmpwi r5, 5
/* 8018561C 0018051C  4C 80 00 20 */	bgelr 
/* 80185620 00180520  48 00 00 3C */	b lbl_8018565C
lbl_80185624:
/* 80185624 00180524  A0 04 00 00 */	lhz r0, 0(r4)
/* 80185628 00180528  20 80 02 D0 */	subfic r4, r0, 0x2d0
/* 8018562C 0018052C  54 80 0F FE */	srwi r0, r4, 0x1f
/* 80185630 00180530  7C 00 22 14 */	add r0, r0, r4
/* 80185634 00180534  7C 00 0E 70 */	srawi r0, r0, 1
/* 80185638 00180538  B0 03 00 00 */	sth r0, 0(r3)
/* 8018563C 0018053C  4E 80 00 20 */	blr 
lbl_80185640:
/* 80185640 00180540  A0 04 00 00 */	lhz r0, 0(r4)
/* 80185644 00180544  20 80 02 D0 */	subfic r4, r0, 0x2d0
/* 80185648 00180548  54 80 0F FE */	srwi r0, r4, 0x1f
/* 8018564C 0018054C  7C 00 22 14 */	add r0, r0, r4
/* 80185650 00180550  7C 00 0E 70 */	srawi r0, r0, 1
/* 80185654 00180554  B0 03 00 00 */	sth r0, 0(r3)
/* 80185658 00180558  4E 80 00 20 */	blr 
lbl_8018565C:
/* 8018565C 0018055C  A0 04 00 00 */	lhz r0, 0(r4)
/* 80185660 00180560  20 80 02 D0 */	subfic r4, r0, 0x2d0
/* 80185664 00180564  54 80 0F FE */	srwi r0, r4, 0x1f
/* 80185668 00180568  7C 00 22 14 */	add r0, r0, r4
/* 8018566C 0018056C  7C 00 0E 70 */	srawi r0, r0, 1
/* 80185670 00180570  B0 03 00 00 */	sth r0, 0(r3)
/* 80185674 00180574  4E 80 00 20 */	blr 
