.include "macros.inc"

.section .sdata2, "a"
.balign 0x8
# Seems to be all one byte array (@3177?)
.global lbl_804C1030
lbl_804C1030:
	.incbin "baserom.dol", 0x3C9C70, 0x1
.global lbl_804C1031
lbl_804C1031:
	.incbin "baserom.dol", 0x3C9C71, 0x1
.global lbl_804C1032
lbl_804C1032:
	.incbin "baserom.dol", 0x3C9C72, 0x1
.global lbl_804C1033
lbl_804C1033:
	.incbin "baserom.dol", 0x3C9C73, 0x1
.global lbl_804C1034
lbl_804C1034:
	.incbin "baserom.dol", 0x3C9C74, 0x1
.global lbl_804C1035
lbl_804C1035:
	.incbin "baserom.dol", 0x3C9C75, 0x1
.global lbl_804C1036
lbl_804C1036:
	.incbin "baserom.dol", 0x3C9C76, 0x2

.section .sdata, "wa"
.balign 0x8
.global __WPADVersion
__WPADVersion:
	.incbin "baserom.dol", 0x3C7250, 0x4
__WPAD_acc_diff_count_threshold:
	.incbin "baserom.dol", 0x3C7254, 0x2
__WPAD_dpd_diff_count_threshold:
	.incbin "baserom.dol", 0x3C7256, 0x2
__WPAD_acc_hyst_count_threshold:
	.incbin "baserom.dol", 0x3C7258, 0x2
__WPAD_dpd_hyst_count_threshold:
	.incbin "baserom.dol", 0x3C725A, 0x2
$$22472:
	.incbin "baserom.dol", 0x3C725C, 0x4

.section .sbss, "wa"
.balign 0x8
.global _regShutdown
_regShutdown:
	.skip 0x2 # Real size = 0x1
.global _senseCnt
_senseCnt:
	.skip 0x2
.global _checkCnt
_checkCnt:
	.skip 0x2 # Real size = 0x1
.global lbl_804BEDD6 # Link map suggests this is _extCnt
lbl_804BEDD6:
	.skip 0x2
.global lbl_804BEDD8 
lbl_804BEDD8:
	.skip 0x4
.global lbl_804BEDDC
lbl_804BEDDC:
	.skip 0x4
.global lbl_804BEDE0
lbl_804BEDE0:
	.skip 0x4
.global _afhChannel
_afhChannel:
	.skip 0x1
.global lbl_804BEDE5 # Should be _shutdown
lbl_804BEDE5:
	.skip 0x1
.global _scSetting
_scSetting:
	.skip 0x2 # Real size = 0x1
.global _chan_active_state
_chan_active_state:
	.skip 0x4
.global _gamecode
_gamecode:
	.skip 0x4
.global _gametype
_gametype:
	.skip 0x1
.global lbl_804BEDF1 # _scFlush?
lbl_804BEDF1:
	.skip 0x1
.global _speakerVolume
_speakerVolume:
	.skip 0x2 # Real size = 0x1
.global _rumble
_rumble:
	.skip 0x4
.global _sensorBarPos
_sensorBarPos:
	.skip 0x1
.global _dpdSensitivity
_dpdSensitivity:
	.skip 0x1
.global _sleepTime
_sleepTime:
	.skip 0x6 # Real size = 0x1

.section .rodata, "a"
.balign 0x8
.global cfg1$3396
cfg1$3396:
	.incbin "baserom.dol", 0x378570, 0x2D
	.balign 4
.global cfg2$3397
cfg2$3397:
	.incbin "baserom.dol", 0x3785A0, 0xA

.section .data, "wa"
.balign 0x8
.global lbl_80399470
lbl_80399470:
	.string "<< RVL_SDK - WPAD \trelease build: May 17 2007 01:52:03 (0x4199_60831) >>"
    .balign 4
.global lbl_803994BC
lbl_803994BC:
	.string "No Alloc: Nothing to do!!!\n"
    .balign 4
.global lbl_803994D8
lbl_803994D8:
	.string "No Free: Nothing to do!!!\n"
    .balign 4
.global lbl_803994F4
lbl_803994F4:
	.string "Deregister allocators because of fatal error.\n"
    .long 0
    .balign 4
.global ShutdownFunctionInfo
ShutdownFunctionInfo:
	.long OnShutdown
	.long 0x7F
	.long 0
	.long 0
.global lbl_80399538
lbl_80399538:
	.incbin "baserom.dol", 0x395638, 0x28
.global lbl_80399560
lbl_80399560:
	.incbin "baserom.dol", 0x395660, 0x18
.global lbl_80399578
lbl_80399578:
	.incbin "baserom.dol", 0x395678, 0xC
.global lbl_80399584
lbl_80399584:
	.incbin "baserom.dol", 0x395684, 0x38
.global lbl_803995BC
lbl_803995BC:
	.incbin "baserom.dol", 0x3956BC, 0xA4
.global lbl_80399660
lbl_80399660:
	.incbin "baserom.dol", 0x395760, 0x18
.global lbl_80399678
lbl_80399678:
	.incbin "baserom.dol", 0x395778, 0x2C
.global lbl_803996A4
lbl_803996A4:
	.incbin "baserom.dol", 0x3957A4, 0x1C
.global lbl_803996C0
lbl_803996C0:
	.incbin "baserom.dol", 0x3957C0, 0x1C
.global lbl_803996DC
lbl_803996DC:
	.incbin "baserom.dol", 0x3957DC, 0x1C
.global lbl_803996F8
lbl_803996F8:
	.incbin "baserom.dol", 0x3957F8, 0x1C
.global lbl_80399714
lbl_80399714:
	.incbin "baserom.dol", 0x395814, 0x1C
.global lbl_80399730
lbl_80399730:
	.incbin "baserom.dol", 0x395830, 0x28

.section .bss, "wa"
.balign 0x8
.global _managerAlarm
_managerAlarm:
	.skip 0x30
.global _wpdcb
_wpdcb:
	.skip 0x10
.global __WPADiManageHandlerStack
__WPADiManageHandlerStack:
	.skip 0x1000
# I guess this is _wpd?
# Not sure why it is much larger than 0x2380
.global lbl_80410640
lbl_80410640:
	.skip 0x26E8

.section .text, "ax"
.global noAlloc
noAlloc:
/* 800CA3D0 000C52D0  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800CA3D4 000C52D4  7C 08 02 A6 */	mflr r0
/* 800CA3D8 000C52D8  3C 60 80 3A */	lis r3, lbl_803994BC@ha
/* 800CA3DC 000C52DC  90 01 00 14 */	stw r0, 0x14(r1)
/* 800CA3E0 000C52E0  38 63 94 BC */	addi r3, r3, lbl_803994BC@l
/* 800CA3E4 000C52E4  4C C6 31 82 */	crclr 6
/* 800CA3E8 000C52E8  48 00 D3 75 */	bl DEBUGPrint
/* 800CA3EC 000C52EC  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800CA3F0 000C52F0  38 60 00 00 */	li r3, 0
/* 800CA3F4 000C52F4  7C 08 03 A6 */	mtlr r0
/* 800CA3F8 000C52F8  38 21 00 10 */	addi r1, r1, 0x10
/* 800CA3FC 000C52FC  4E 80 00 20 */	blr 

.global noFree
noFree:
/* 800CA400 000C5300  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800CA404 000C5304  7C 08 02 A6 */	mflr r0
/* 800CA408 000C5308  3C 60 80 3A */	lis r3, lbl_803994D8@ha
/* 800CA40C 000C530C  90 01 00 14 */	stw r0, 0x14(r1)
/* 800CA410 000C5310  38 63 94 D8 */	addi r3, r3, lbl_803994D8@l
/* 800CA414 000C5314  4C C6 31 82 */	crclr 6
/* 800CA418 000C5318  48 00 D3 45 */	bl DEBUGPrint
/* 800CA41C 000C531C  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800CA420 000C5320  38 60 00 00 */	li r3, 0
/* 800CA424 000C5324  7C 08 03 A6 */	mtlr r0
/* 800CA428 000C5328  38 21 00 10 */	addi r1, r1, 0x10
/* 800CA42C 000C532C  4E 80 00 20 */	blr 

.global OnShutdown
OnShutdown:
/* 800CA430 000C5330  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800CA434 000C5334  7C 08 02 A6 */	mflr r0
/* 800CA438 000C5338  90 01 00 24 */	stw r0, 0x24(r1)
/* 800CA43C 000C533C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800CA440 000C5340  7C 7F 1B 78 */	mr r31, r3
/* 800CA444 000C5344  93 C1 00 18 */	stw r30, 0x18(r1)
/* 800CA448 000C5348  7C 9E 23 78 */	mr r30, r4
/* 800CA44C 000C534C  93 A1 00 14 */	stw r29, 0x14(r1)
/* 800CA450 000C5350  3B A0 00 00 */	li r29, 0
/* 800CA454 000C5354  48 03 63 05 */	bl WUDGetStatus
/* 800CA458 000C5358  2C 1F 00 00 */	cmpwi r31, 0
/* 800CA45C 000C535C  40 82 01 74 */	bne lbl_800CA5D0
/* 800CA460 000C5360  2C 03 00 03 */	cmpwi r3, 3
/* 800CA464 000C5364  40 82 01 2C */	bne lbl_800CA590
/* 800CA468 000C5368  2C 1E 00 01 */	cmpwi r30, 1
/* 800CA46C 000C536C  41 82 00 D4 */	beq lbl_800CA540
/* 800CA470 000C5370  40 80 00 10 */	bge lbl_800CA480
/* 800CA474 000C5374  2C 1E 00 00 */	cmpwi r30, 0
/* 800CA478 000C5378  40 80 00 1C */	bge lbl_800CA494
/* 800CA47C 000C537C  48 00 01 58 */	b lbl_800CA5D4
lbl_800CA480:
/* 800CA480 000C5380  2C 1E 00 07 */	cmpwi r30, 7
/* 800CA484 000C5384  40 80 01 50 */	bge lbl_800CA5D4
/* 800CA488 000C5388  2C 1E 00 04 */	cmpwi r30, 4
/* 800CA48C 000C538C  40 80 00 B4 */	bge lbl_800CA540
/* 800CA490 000C5390  48 00 00 28 */	b lbl_800CA4B8
lbl_800CA494:
/* 800CA494 000C5394  3C 60 80 3A */	lis r3, lbl_803994F4@ha
/* 800CA498 000C5398  38 63 94 F4 */	addi r3, r3, lbl_803994F4@l
/* 800CA49C 000C539C  4C C6 31 82 */	crclr 6
/* 800CA4A0 000C53A0  48 00 D2 BD */	bl DEBUGPrint
/* 800CA4A4 000C53A4  3C 60 80 0D */	lis r3, noAlloc@ha
/* 800CA4A8 000C53A8  3C 80 80 0D */	lis r4, noFree@ha
/* 800CA4AC 000C53AC  38 63 A3 D0 */	addi r3, r3, noAlloc@l
/* 800CA4B0 000C53B0  38 84 A4 00 */	addi r4, r4, noFree@l
/* 800CA4B4 000C53B4  48 03 60 C9 */	bl WUDRegisterAllocator
lbl_800CA4B8:
/* 800CA4B8 000C53B8  48 02 74 09 */	bl OSDisableInterrupts
/* 800CA4BC 000C53BC  88 0D 9A 65 */	lbz r0, lbl_804BEDE5-_SDA_BASE_(r13)
/* 800CA4C0 000C53C0  7C 7E 1B 78 */	mr r30, r3
/* 800CA4C4 000C53C4  2C 00 00 00 */	cmpwi r0, 0
/* 800CA4C8 000C53C8  41 82 00 0C */	beq lbl_800CA4D4
/* 800CA4CC 000C53CC  48 02 74 1D */	bl OSRestoreInterrupts
/* 800CA4D0 000C53D0  48 00 00 68 */	b lbl_800CA538
lbl_800CA4D4:
/* 800CA4D4 000C53D4  38 00 00 01 */	li r0, 1
/* 800CA4D8 000C53D8  38 60 00 00 */	li r3, 0
/* 800CA4DC 000C53DC  98 0D 9A 65 */	stb r0, lbl_804BEDE5-_SDA_BASE_(r13)
/* 800CA4E0 000C53E0  38 80 00 00 */	li r4, 0
/* 800CA4E4 000C53E4  48 03 69 C5 */	bl WUDSetVisibility
/* 800CA4E8 000C53E8  3C 60 80 43 */	lis r3, _scArray@ha
/* 800CA4EC 000C53EC  3B E0 00 0A */	li r31, 0xa
/* 800CA4F0 000C53F0  38 63 99 68 */	addi r3, r3, _scArray@l
/* 800CA4F4 000C53F4  3B A3 02 BD */	addi r29, r3, 0x2bd
lbl_800CA4F8:
/* 800CA4F8 000C53F8  7F A3 EB 78 */	mr r3, r29
/* 800CA4FC 000C53FC  38 80 00 00 */	li r4, 0
/* 800CA500 000C5400  38 A0 00 46 */	li r5, 0x46
/* 800CA504 000C5404  4B F3 9C 01 */	bl memset
/* 800CA508 000C5408  3B FF 00 01 */	addi r31, r31, 1
/* 800CA50C 000C540C  3B BD 00 46 */	addi r29, r29, 0x46
/* 800CA510 000C5410  2C 1F 00 0E */	cmpwi r31, 0xe
/* 800CA514 000C5414  41 80 FF E4 */	blt lbl_800CA4F8
/* 800CA518 000C5418  3C 60 80 41 */	lis r3, _managerAlarm@ha
/* 800CA51C 000C541C  38 63 F6 00 */	addi r3, r3, _managerAlarm@l
/* 800CA520 000C5420  48 02 2F 49 */	bl OSCancelAlarm
/* 800CA524 000C5424  38 60 00 00 */	li r3, 0
/* 800CA528 000C5428  48 03 68 C9 */	bl WUDSetHidRecvCallback
/* 800CA52C 000C542C  48 03 60 A1 */	bl WUDShutdown
/* 800CA530 000C5430  7F C3 F3 78 */	mr r3, r30
/* 800CA534 000C5434  48 02 73 B5 */	bl OSRestoreInterrupts
lbl_800CA538:
/* 800CA538 000C5438  3B A0 00 00 */	li r29, 0
/* 800CA53C 000C543C  48 00 00 98 */	b lbl_800CA5D4
lbl_800CA540:
/* 800CA540 000C5440  48 02 73 81 */	bl OSDisableInterrupts
/* 800CA544 000C5444  88 0D 9A 65 */	lbz r0, lbl_804BEDE5-_SDA_BASE_(r13)
/* 800CA548 000C5448  7C 7E 1B 78 */	mr r30, r3
/* 800CA54C 000C544C  2C 00 00 00 */	cmpwi r0, 0
/* 800CA550 000C5450  41 82 00 0C */	beq lbl_800CA55C
/* 800CA554 000C5454  48 02 73 95 */	bl OSRestoreInterrupts
/* 800CA558 000C5458  48 00 00 30 */	b lbl_800CA588
lbl_800CA55C:
/* 800CA55C 000C545C  38 00 00 01 */	li r0, 1
/* 800CA560 000C5460  98 0D 9A 65 */	stb r0, lbl_804BEDE5-_SDA_BASE_(r13)
/* 800CA564 000C5464  48 04 74 C5 */	bl func_80111A28
/* 800CA568 000C5468  3C 60 80 41 */	lis r3, _managerAlarm@ha
/* 800CA56C 000C546C  38 63 F6 00 */	addi r3, r3, _managerAlarm@l
/* 800CA570 000C5470  48 02 2E F9 */	bl OSCancelAlarm
/* 800CA574 000C5474  38 60 00 00 */	li r3, 0
/* 800CA578 000C5478  48 03 68 79 */	bl WUDSetHidRecvCallback
/* 800CA57C 000C547C  48 03 60 51 */	bl WUDShutdown
/* 800CA580 000C5480  7F C3 F3 78 */	mr r3, r30
/* 800CA584 000C5484  48 02 73 65 */	bl OSRestoreInterrupts
lbl_800CA588:
/* 800CA588 000C5488  3B A0 00 00 */	li r29, 0
/* 800CA58C 000C548C  48 00 00 48 */	b lbl_800CA5D4
lbl_800CA590:
/* 800CA590 000C5490  2C 03 00 05 */	cmpwi r3, 5
/* 800CA594 000C5494  40 82 00 10 */	bne lbl_800CA5A4
/* 800CA598 000C5498  48 03 65 B5 */	bl WUDStopSyncSimple
/* 800CA59C 000C549C  3B A0 00 00 */	li r29, 0
/* 800CA5A0 000C54A0  48 00 00 34 */	b lbl_800CA5D4
lbl_800CA5A4:
/* 800CA5A4 000C54A4  2C 03 00 04 */	cmpwi r3, 4
/* 800CA5A8 000C54A8  41 82 00 10 */	beq lbl_800CA5B8
/* 800CA5AC 000C54AC  38 03 FF FF */	addi r0, r3, -1
/* 800CA5B0 000C54B0  28 00 00 01 */	cmplwi r0, 1
/* 800CA5B4 000C54B4  41 81 00 0C */	bgt lbl_800CA5C0
lbl_800CA5B8:
/* 800CA5B8 000C54B8  3B A0 00 00 */	li r29, 0
/* 800CA5BC 000C54BC  48 00 00 18 */	b lbl_800CA5D4
lbl_800CA5C0:
/* 800CA5C0 000C54C0  2C 03 00 00 */	cmpwi r3, 0
/* 800CA5C4 000C54C4  40 82 00 10 */	bne lbl_800CA5D4
/* 800CA5C8 000C54C8  3B A0 00 01 */	li r29, 1
/* 800CA5CC 000C54CC  48 00 00 08 */	b lbl_800CA5D4
lbl_800CA5D0:
/* 800CA5D0 000C54D0  3B A0 00 01 */	li r29, 1
lbl_800CA5D4:
/* 800CA5D4 000C54D4  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800CA5D8 000C54D8  7F A3 EB 78 */	mr r3, r29
/* 800CA5DC 000C54DC  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 800CA5E0 000C54E0  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 800CA5E4 000C54E4  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800CA5E8 000C54E8  7C 08 03 A6 */	mtlr r0
/* 800CA5EC 000C54EC  38 21 00 20 */	addi r1, r1, 0x20
/* 800CA5F0 000C54F0  4E 80 00 20 */	blr 

.global WPADiSendData
WPADiSendData:
/* 800CA5F4 000C54F4  94 21 FF A0 */	stwu r1, -0x60(r1)
/* 800CA5F8 000C54F8  7C 08 02 A6 */	mflr r0
/* 800CA5FC 000C54FC  90 01 00 64 */	stw r0, 0x64(r1)
/* 800CA600 000C5500  39 61 00 60 */	addi r11, r1, 0x60
/* 800CA604 000C5504  4B FE 77 35 */	bl _savegpr_24
/* 800CA608 000C5508  3F E0 80 41 */	lis r31, _wpdcb@ha
/* 800CA60C 000C550C  54 7E 10 3A */	slwi r30, r3, 2
/* 800CA610 000C5510  3B FF F6 30 */	addi r31, r31, _wpdcb@l
/* 800CA614 000C5514  7C 7A 1B 78 */	mr r26, r3
/* 800CA618 000C5518  7F BF F0 2E */	lwzx r29, r31, r30
/* 800CA61C 000C551C  7C 98 23 78 */	mr r24, r4
/* 800CA620 000C5520  48 02 72 A1 */	bl OSDisableInterrupts
/* 800CA624 000C5524  83 9D 08 BC */	lwz r28, 0x8bc(r29)
/* 800CA628 000C5528  48 02 72 C1 */	bl OSRestoreInterrupts
/* 800CA62C 000C552C  2C 1C 00 00 */	cmpwi r28, 0
/* 800CA630 000C5530  40 82 00 90 */	bne lbl_800CA6C0
/* 800CA634 000C5534  48 02 72 8D */	bl OSDisableInterrupts
/* 800CA638 000C5538  8B 3D 08 C0 */	lbz r25, 0x8c0(r29)
/* 800CA63C 000C553C  48 02 72 AD */	bl OSRestoreInterrupts
/* 800CA640 000C5540  2C 19 00 00 */	cmpwi r25, 0
/* 800CA644 000C5544  41 82 00 0C */	beq lbl_800CA650
/* 800CA648 000C5548  3B 80 FF FE */	li r28, -2
/* 800CA64C 000C554C  48 00 00 94 */	b lbl_800CA6E0
lbl_800CA650:
/* 800CA650 000C5550  83 38 00 00 */	lwz r25, 0(r24)
/* 800CA654 000C5554  7F 43 D3 78 */	mr r3, r26
/* 800CA658 000C5558  83 58 00 04 */	lwz r26, 4(r24)
/* 800CA65C 000C555C  38 81 00 10 */	addi r4, r1, 0x10
/* 800CA660 000C5560  83 78 00 08 */	lwz r27, 8(r24)
/* 800CA664 000C5564  81 98 00 0C */	lwz r12, 0xc(r24)
/* 800CA668 000C5568  81 78 00 10 */	lwz r11, 0x10(r24)
/* 800CA66C 000C556C  81 58 00 14 */	lwz r10, 0x14(r24)
/* 800CA670 000C5570  81 38 00 18 */	lwz r9, 0x18(r24)
/* 800CA674 000C5574  81 18 00 1C */	lwz r8, 0x1c(r24)
/* 800CA678 000C5578  80 F8 00 20 */	lwz r7, 0x20(r24)
/* 800CA67C 000C557C  80 D8 00 24 */	lwz r6, 0x24(r24)
/* 800CA680 000C5580  80 B8 00 28 */	lwz r5, 0x28(r24)
/* 800CA684 000C5584  80 18 00 2C */	lwz r0, 0x2c(r24)
/* 800CA688 000C5588  93 21 00 10 */	stw r25, 0x10(r1)
/* 800CA68C 000C558C  93 41 00 14 */	stw r26, 0x14(r1)
/* 800CA690 000C5590  93 61 00 18 */	stw r27, 0x18(r1)
/* 800CA694 000C5594  91 81 00 1C */	stw r12, 0x1c(r1)
/* 800CA698 000C5598  91 61 00 20 */	stw r11, 0x20(r1)
/* 800CA69C 000C559C  91 41 00 24 */	stw r10, 0x24(r1)
/* 800CA6A0 000C55A0  91 21 00 28 */	stw r9, 0x28(r1)
/* 800CA6A4 000C55A4  91 01 00 2C */	stw r8, 0x2c(r1)
/* 800CA6A8 000C55A8  90 E1 00 30 */	stw r7, 0x30(r1)
/* 800CA6AC 000C55AC  90 C1 00 34 */	stw r6, 0x34(r1)
/* 800CA6B0 000C55B0  90 A1 00 38 */	stw r5, 0x38(r1)
/* 800CA6B4 000C55B4  90 01 00 3C */	stw r0, 0x3c(r1)
/* 800CA6B8 000C55B8  48 00 69 A9 */	bl __SendData
/* 800CA6BC 000C55BC  48 00 00 24 */	b lbl_800CA6E0
lbl_800CA6C0:
/* 800CA6C0 000C55C0  2C 1C FF FE */	cmpwi r28, -2
/* 800CA6C4 000C55C4  41 82 00 1C */	beq lbl_800CA6E0
/* 800CA6C8 000C55C8  2C 1C FF FD */	cmpwi r28, -3
/* 800CA6CC 000C55CC  40 82 00 14 */	bne lbl_800CA6E0
/* 800CA6D0 000C55D0  48 02 71 F1 */	bl OSDisableInterrupts
/* 800CA6D4 000C55D4  38 00 00 00 */	li r0, 0
/* 800CA6D8 000C55D8  90 1D 08 BC */	stw r0, 0x8bc(r29)
/* 800CA6DC 000C55DC  48 02 72 0D */	bl OSRestoreInterrupts
lbl_800CA6E0:
/* 800CA6E0 000C55E0  2C 1C FF FE */	cmpwi r28, -2
/* 800CA6E4 000C55E4  40 82 00 D0 */	bne lbl_800CA7B4
/* 800CA6E8 000C55E8  48 02 AF 3D */	bl __OSGetSystemTime
/* 800CA6EC 000C55EC  80 DD 09 0C */	lwz r6, 0x90c(r29)
/* 800CA6F0 000C55F0  3C A0 80 00 */	lis r5, 0x800000F8@ha
/* 800CA6F4 000C55F4  80 05 00 F8 */	lwz r0, 0x800000F8@l(r5)
/* 800CA6F8 000C55F8  38 A0 00 00 */	li r5, 0
/* 800CA6FC 000C55FC  7C 86 20 10 */	subfc r4, r6, r4
/* 800CA700 000C5600  80 FD 09 08 */	lwz r7, 0x908(r29)
/* 800CA704 000C5604  54 06 F0 BE */	srwi r6, r0, 2
/* 800CA708 000C5608  7C 67 19 10 */	subfe r3, r7, r3
/* 800CA70C 000C560C  4B FE 77 89 */	bl __div2i
/* 800CA710 000C5610  2C 04 00 01 */	cmpwi r4, 1
/* 800CA714 000C5614  40 81 00 A0 */	ble lbl_800CA7B4
/* 800CA718 000C5618  88 0D 9A 7A */	lbz r0, _sleepTime-_SDA_BASE_(r13)
/* 800CA71C 000C561C  2C 00 00 00 */	cmpwi r0, 0
/* 800CA720 000C5620  41 82 00 94 */	beq lbl_800CA7B4
/* 800CA724 000C5624  88 1D 09 10 */	lbz r0, 0x910(r29)
/* 800CA728 000C5628  2C 00 00 00 */	cmpwi r0, 0
/* 800CA72C 000C562C  40 82 00 78 */	bne lbl_800CA7A4
/* 800CA730 000C5630  48 02 AE F5 */	bl __OSGetSystemTime
/* 800CA734 000C5634  90 9D 09 0C */	stw r4, 0x90c(r29)
/* 800CA738 000C5638  90 7D 09 08 */	stw r3, 0x908(r29)
/* 800CA73C 000C563C  7F 3F F0 2E */	lwzx r25, r31, r30
/* 800CA740 000C5640  48 02 71 81 */	bl OSDisableInterrupts
/* 800CA744 000C5644  83 39 08 BC */	lwz r25, 0x8bc(r25)
/* 800CA748 000C5648  48 02 71 A1 */	bl OSRestoreInterrupts
/* 800CA74C 000C564C  2C 19 FF FF */	cmpwi r25, -1
/* 800CA750 000C5650  41 82 00 64 */	beq lbl_800CA7B4
/* 800CA754 000C5654  7F 3F F0 2E */	lwzx r25, r31, r30
/* 800CA758 000C5658  48 02 71 69 */	bl OSDisableInterrupts
/* 800CA75C 000C565C  8B 39 08 C3 */	lbz r25, 0x8c3(r25)
/* 800CA760 000C5660  48 02 71 89 */	bl OSRestoreInterrupts
/* 800CA764 000C5664  7F 23 CB 78 */	mr r3, r25
/* 800CA768 000C5668  48 03 87 51 */	bl _WUDGetDevAddr
/* 800CA76C 000C566C  2C 03 00 00 */	cmpwi r3, 0
/* 800CA770 000C5670  41 82 00 18 */	beq lbl_800CA788
/* 800CA774 000C5674  7C 64 1B 78 */	mr r4, r3
/* 800CA778 000C5678  38 61 00 08 */	addi r3, r1, 8
/* 800CA77C 000C567C  38 A0 00 06 */	li r5, 6
/* 800CA780 000C5680  4B F3 98 81 */	bl memcpy
/* 800CA784 000C5684  48 00 00 14 */	b lbl_800CA798
lbl_800CA788:
/* 800CA788 000C5688  38 61 00 08 */	addi r3, r1, 8
/* 800CA78C 000C568C  38 80 00 00 */	li r4, 0
/* 800CA790 000C5690  38 A0 00 06 */	li r5, 6
/* 800CA794 000C5694  4B F3 99 71 */	bl memset
lbl_800CA798:
/* 800CA798 000C5698  38 61 00 08 */	addi r3, r1, 8
/* 800CA79C 000C569C  48 04 BC C1 */	bl func_8011645C
/* 800CA7A0 000C56A0  48 00 00 14 */	b lbl_800CA7B4
lbl_800CA7A4:
/* 800CA7A4 000C56A4  48 02 71 1D */	bl OSDisableInterrupts
/* 800CA7A8 000C56A8  38 00 FF FD */	li r0, -3
/* 800CA7AC 000C56AC  90 1D 08 BC */	stw r0, 0x8bc(r29)
/* 800CA7B0 000C56B0  48 02 71 39 */	bl OSRestoreInterrupts
lbl_800CA7B4:
/* 800CA7B4 000C56B4  39 61 00 60 */	addi r11, r1, 0x60
/* 800CA7B8 000C56B8  7F 83 E3 78 */	mr r3, r28
/* 800CA7BC 000C56BC  4B FE 75 C9 */	bl _restgpr_24
/* 800CA7C0 000C56C0  80 01 00 64 */	lwz r0, 0x64(r1)
/* 800CA7C4 000C56C4  7C 08 03 A6 */	mtlr r0
/* 800CA7C8 000C56C8  38 21 00 60 */	addi r1, r1, 0x60
/* 800CA7CC 000C56CC  4E 80 00 20 */	blr 

.global WPADiRadioSensitivity
WPADiRadioSensitivity:
/* 800CA7D0 000C56D0  3C A0 80 41 */	lis r5, _wpdcb@ha
/* 800CA7D4 000C56D4  3C 80 66 66 */	lis r4, 0x66666667@ha
/* 800CA7D8 000C56D8  54 63 10 3A */	slwi r3, r3, 2
/* 800CA7DC 000C56DC  38 00 00 64 */	li r0, 0x64
/* 800CA7E0 000C56E0  38 A5 F6 30 */	addi r5, r5, _wpdcb@l
/* 800CA7E4 000C56E4  38 84 66 67 */	addi r4, r4, 0x66666667@l
/* 800CA7E8 000C56E8  7C E5 18 2E */	lwzx r7, r5, r3
/* 800CA7EC 000C56EC  A0 67 09 84 */	lhz r3, 0x984(r7)
/* 800CA7F0 000C56F0  88 C7 09 83 */	lbz r6, 0x983(r7)
/* 800CA7F4 000C56F4  1C 63 00 64 */	mulli r3, r3, 0x64
/* 800CA7F8 000C56F8  54 C5 18 38 */	slwi r5, r6, 3
/* 800CA7FC 000C56FC  7C A5 32 14 */	add r5, r5, r6
/* 800CA800 000C5700  54 A5 04 3E */	clrlwi r5, r5, 0x10
/* 800CA804 000C5704  54 63 FC 3E */	rlwinm r3, r3, 0x1f, 0x10, 0x1f
/* 800CA808 000C5708  7C A5 1A 14 */	add r5, r5, r3
/* 800CA80C 000C570C  54 A3 04 3E */	clrlwi r3, r5, 0x10
/* 800CA810 000C5710  7C 64 18 96 */	mulhw r3, r4, r3
/* 800CA814 000C5714  7C 63 16 70 */	srawi r3, r3, 2
/* 800CA818 000C5718  54 64 0F FE */	srwi r4, r3, 0x1f
/* 800CA81C 000C571C  7C 63 22 14 */	add r3, r3, r4
/* 800CA820 000C5720  54 65 04 3E */	clrlwi r5, r3, 0x10
/* 800CA824 000C5724  28 05 00 64 */	cmplwi r5, 0x64
/* 800CA828 000C5728  41 81 00 08 */	bgt lbl_800CA830
/* 800CA82C 000C572C  7C A0 2B 78 */	mr r0, r5
lbl_800CA830:
/* 800CA830 000C5730  98 07 09 83 */	stb r0, 0x983(r7)
/* 800CA834 000C5734  38 80 00 00 */	li r4, 0
/* 800CA838 000C5738  54 03 04 3E */	clrlwi r3, r0, 0x10
/* 800CA83C 000C573C  B0 87 09 84 */	sth r4, 0x984(r7)
/* 800CA840 000C5740  88 07 08 CD */	lbz r0, 0x8cd(r7)
/* 800CA844 000C5744  2C 00 00 00 */	cmpwi r0, 0
/* 800CA848 000C5748  41 82 00 44 */	beq lbl_800CA88C
/* 800CA84C 000C574C  28 03 00 55 */	cmplwi r3, 0x55
/* 800CA850 000C5750  40 81 00 10 */	ble lbl_800CA860
/* 800CA854 000C5754  98 87 08 CD */	stb r4, 0x8cd(r7)
/* 800CA858 000C5758  98 87 08 CE */	stb r4, 0x8ce(r7)
/* 800CA85C 000C575C  4E 80 00 20 */	blr 
lbl_800CA860:
/* 800CA860 000C5760  28 03 00 50 */	cmplwi r3, 0x50
/* 800CA864 000C5764  4C 81 00 20 */	blelr 
/* 800CA868 000C5768  88 67 08 CE */	lbz r3, 0x8ce(r7)
/* 800CA86C 000C576C  38 63 00 01 */	addi r3, r3, 1
/* 800CA870 000C5770  54 60 06 3E */	clrlwi r0, r3, 0x18
/* 800CA874 000C5774  98 67 08 CE */	stb r3, 0x8ce(r7)
/* 800CA878 000C5778  28 00 00 14 */	cmplwi r0, 0x14
/* 800CA87C 000C577C  4D 80 00 20 */	bltlr 
/* 800CA880 000C5780  98 87 08 CD */	stb r4, 0x8cd(r7)
/* 800CA884 000C5784  98 87 08 CE */	stb r4, 0x8ce(r7)
/* 800CA888 000C5788  4E 80 00 20 */	blr 
lbl_800CA88C:
/* 800CA88C 000C578C  28 03 00 4B */	cmplwi r3, 0x4b
/* 800CA890 000C5790  40 80 00 14 */	bge lbl_800CA8A4
/* 800CA894 000C5794  38 00 00 01 */	li r0, 1
/* 800CA898 000C5798  98 07 08 CD */	stb r0, 0x8cd(r7)
/* 800CA89C 000C579C  98 87 08 CE */	stb r4, 0x8ce(r7)
/* 800CA8A0 000C57A0  4E 80 00 20 */	blr 
lbl_800CA8A4:
/* 800CA8A4 000C57A4  28 03 00 50 */	cmplwi r3, 0x50
/* 800CA8A8 000C57A8  4C 80 00 20 */	bgelr 
/* 800CA8AC 000C57AC  88 67 08 CE */	lbz r3, 0x8ce(r7)
/* 800CA8B0 000C57B0  38 63 00 01 */	addi r3, r3, 1
/* 800CA8B4 000C57B4  54 60 06 3E */	clrlwi r0, r3, 0x18
/* 800CA8B8 000C57B8  98 67 08 CE */	stb r3, 0x8ce(r7)
/* 800CA8BC 000C57BC  28 00 00 01 */	cmplwi r0, 1
/* 800CA8C0 000C57C0  4D 80 00 20 */	bltlr 
/* 800CA8C4 000C57C4  38 00 00 01 */	li r0, 1
/* 800CA8C8 000C57C8  98 07 08 CD */	stb r0, 0x8cd(r7)
/* 800CA8CC 000C57CC  98 87 08 CE */	stb r4, 0x8ce(r7)
/* 800CA8D0 000C57D0  4E 80 00 20 */	blr 

.global IsControllerDataChanged
IsControllerDataChanged:
/* 800CA8D4 000C57D4  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800CA8D8 000C57D8  7C 08 02 A6 */	mflr r0
/* 800CA8DC 000C57DC  90 01 00 24 */	stw r0, 0x24(r1)
/* 800CA8E0 000C57E0  39 61 00 20 */	addi r11, r1, 0x20
/* 800CA8E4 000C57E4  4B FE 74 61 */	bl _savegpr_27
/* 800CA8E8 000C57E8  80 C3 08 B8 */	lwz r6, 0x8b8(r3)
/* 800CA8EC 000C57EC  89 03 08 C2 */	lbz r8, 0x8c2(r3)
/* 800CA8F0 000C57F0  28 06 00 02 */	cmplwi r6, 2
/* 800CA8F4 000C57F4  41 81 02 14 */	bgt lbl_800CAB08
/* 800CA8F8 000C57F8  88 04 00 29 */	lbz r0, 0x29(r4)
/* 800CA8FC 000C57FC  A1 04 00 00 */	lhz r8, 0(r4)
/* 800CA900 000C5800  A0 E5 00 00 */	lhz r7, 0(r5)
/* 800CA904 000C5804  7C 00 07 75 */	extsb. r0, r0
/* 800CA908 000C5808  7C C8 38 50 */	subf r6, r8, r7
/* 800CA90C 000C580C  7C 07 40 50 */	subf r0, r7, r8
/* 800CA910 000C5810  7C C0 03 78 */	or r0, r6, r0
/* 800CA914 000C5814  54 00 0F FE */	srwi r0, r0, 0x1f
/* 800CA918 000C5818  40 82 0B 4C */	bne lbl_800CB464
/* 800CA91C 000C581C  88 C5 00 29 */	lbz r6, 0x29(r5)
/* 800CA920 000C5820  7C C6 07 75 */	extsb. r6, r6
/* 800CA924 000C5824  40 82 0B 40 */	bne lbl_800CB464
/* 800CA928 000C5828  A8 E5 00 04 */	lha r7, 4(r5)
/* 800CA92C 000C582C  A8 C4 00 04 */	lha r6, 4(r4)
/* 800CA930 000C5830  7D 47 30 51 */	subf. r10, r7, r6
/* 800CA934 000C5834  40 80 00 08 */	bge lbl_800CA93C
/* 800CA938 000C5838  7D 46 38 50 */	subf r10, r6, r7
lbl_800CA93C:
/* 800CA93C 000C583C  A9 25 00 02 */	lha r9, 2(r5)
/* 800CA940 000C5840  69 46 00 0C */	xori r6, r10, 0xc
/* 800CA944 000C5844  A9 04 00 02 */	lha r8, 2(r4)
/* 800CA948 000C5848  7C C7 0E 70 */	srawi r7, r6, 1
/* 800CA94C 000C584C  7C C6 50 38 */	and r6, r6, r10
/* 800CA950 000C5850  7C C6 38 50 */	subf r6, r6, r7
/* 800CA954 000C5854  7D 69 40 51 */	subf. r11, r9, r8
/* 800CA958 000C5858  54 CA 0F FE */	srwi r10, r6, 0x1f
/* 800CA95C 000C585C  40 80 00 08 */	bge lbl_800CA964
/* 800CA960 000C5860  7D 68 48 50 */	subf r11, r8, r9
lbl_800CA964:
/* 800CA964 000C5864  A9 25 00 06 */	lha r9, 6(r5)
/* 800CA968 000C5868  69 66 00 0C */	xori r6, r11, 0xc
/* 800CA96C 000C586C  A9 04 00 06 */	lha r8, 6(r4)
/* 800CA970 000C5870  7C C7 0E 70 */	srawi r7, r6, 1
/* 800CA974 000C5874  7C C6 58 38 */	and r6, r6, r11
/* 800CA978 000C5878  7C C6 38 50 */	subf r6, r6, r7
/* 800CA97C 000C587C  7D 69 40 51 */	subf. r11, r9, r8
/* 800CA980 000C5880  54 C6 0F FE */	srwi r6, r6, 0x1f
/* 800CA984 000C5884  40 80 00 08 */	bge lbl_800CA98C
/* 800CA988 000C5888  7D 68 48 50 */	subf r11, r8, r9
lbl_800CA98C:
/* 800CA98C 000C588C  69 67 00 0C */	xori r7, r11, 0xc
/* 800CA990 000C5890  7C C6 53 78 */	or r6, r6, r10
/* 800CA994 000C5894  7C E8 0E 70 */	srawi r8, r7, 1
/* 800CA998 000C5898  7C E7 58 38 */	and r7, r7, r11
/* 800CA99C 000C589C  7C E7 40 50 */	subf r7, r7, r8
/* 800CA9A0 000C58A0  54 E7 0F FE */	srwi r7, r7, 0x1f
/* 800CA9A4 000C58A4  7C E6 33 79 */	or. r6, r7, r6
/* 800CA9A8 000C58A8  41 82 00 38 */	beq lbl_800CA9E0
/* 800CA9AC 000C58AC  A0 C3 08 FC */	lhz r6, 0x8fc(r3)
/* 800CA9B0 000C58B0  38 C6 00 01 */	addi r6, r6, 1
/* 800CA9B4 000C58B4  B0 C3 08 FC */	sth r6, 0x8fc(r3)
/* 800CA9B8 000C58B8  54 C7 04 3E */	clrlwi r7, r6, 0x10
/* 800CA9BC 000C58BC  A0 CD 82 54 */	lhz r6, __WPAD_acc_diff_count_threshold-_SDA_BASE_(r13)
/* 800CA9C0 000C58C0  7C 07 30 40 */	cmplw r7, r6
/* 800CA9C4 000C58C4  40 81 00 60 */	ble lbl_800CAA24
/* 800CA9C8 000C58C8  38 C0 00 00 */	li r6, 0
/* 800CA9CC 000C58CC  60 00 00 01 */	ori r0, r0, 1
/* 800CA9D0 000C58D0  B0 C3 08 FC */	sth r6, 0x8fc(r3)
/* 800CA9D4 000C58D4  54 00 06 3E */	clrlwi r0, r0, 0x18
/* 800CA9D8 000C58D8  B0 C3 08 FE */	sth r6, 0x8fe(r3)
/* 800CA9DC 000C58DC  48 00 00 48 */	b lbl_800CAA24
lbl_800CA9E0:
/* 800CA9E0 000C58E0  A0 C3 08 FE */	lhz r6, 0x8fe(r3)
/* 800CA9E4 000C58E4  A0 ED 82 58 */	lhz r7, __WPAD_acc_hyst_count_threshold-_SDA_BASE_(r13)
/* 800CA9E8 000C58E8  39 06 00 01 */	addi r8, r6, 1
/* 800CA9EC 000C58EC  7C C8 3B D6 */	divw r6, r8, r7
/* 800CA9F0 000C58F0  7C C6 39 D6 */	mullw r6, r6, r7
/* 800CA9F4 000C58F4  7C C6 40 50 */	subf r6, r6, r8
/* 800CA9F8 000C58F8  B0 C3 08 FE */	sth r6, 0x8fe(r3)
/* 800CA9FC 000C58FC  54 C7 04 3E */	clrlwi r7, r6, 0x10
/* 800CAA00 000C5900  A0 CD 82 58 */	lhz r6, __WPAD_acc_hyst_count_threshold-_SDA_BASE_(r13)
/* 800CAA04 000C5904  38 C6 FF FF */	addi r6, r6, -1
/* 800CAA08 000C5908  7C 07 30 00 */	cmpw r7, r6
/* 800CAA0C 000C590C  40 82 00 18 */	bne lbl_800CAA24
/* 800CAA10 000C5910  A0 C3 08 FC */	lhz r6, 0x8fc(r3)
/* 800CAA14 000C5914  2C 06 00 00 */	cmpwi r6, 0
/* 800CAA18 000C5918  41 82 00 0C */	beq lbl_800CAA24
/* 800CAA1C 000C591C  38 C6 FF FF */	addi r6, r6, -1
/* 800CAA20 000C5920  B0 C3 08 FC */	sth r6, 0x8fc(r3)
lbl_800CAA24:
/* 800CAA24 000C5924  38 C0 00 04 */	li r6, 4
/* 800CAA28 000C5928  39 20 00 00 */	li r9, 0
/* 800CAA2C 000C592C  7C C9 03 A6 */	mtctr r6
lbl_800CAA30:
/* 800CAA30 000C5930  A8 E5 00 0A */	lha r7, 0xa(r5)
/* 800CAA34 000C5934  A8 C4 00 0A */	lha r6, 0xa(r4)
/* 800CAA38 000C5938  7D 67 30 51 */	subf. r11, r7, r6
/* 800CAA3C 000C593C  40 80 00 08 */	bge lbl_800CAA44
/* 800CAA40 000C5940  7D 66 38 50 */	subf r11, r6, r7
lbl_800CAA44:
/* 800CAA44 000C5944  A9 45 00 08 */	lha r10, 8(r5)
/* 800CAA48 000C5948  69 66 00 02 */	xori r6, r11, 2
/* 800CAA4C 000C594C  A9 04 00 08 */	lha r8, 8(r4)
/* 800CAA50 000C5950  7C C7 0E 70 */	srawi r7, r6, 1
/* 800CAA54 000C5954  7C C6 58 38 */	and r6, r6, r11
/* 800CAA58 000C5958  7C C6 38 50 */	subf r6, r6, r7
/* 800CAA5C 000C595C  7D 8A 40 51 */	subf. r12, r10, r8
/* 800CAA60 000C5960  54 CB 0F FE */	srwi r11, r6, 0x1f
/* 800CAA64 000C5964  40 80 00 08 */	bge lbl_800CAA6C
/* 800CAA68 000C5968  7D 88 50 50 */	subf r12, r8, r10
lbl_800CAA6C:
/* 800CAA6C 000C596C  69 86 00 02 */	xori r6, r12, 2
/* 800CAA70 000C5970  7C C7 0E 70 */	srawi r7, r6, 1
/* 800CAA74 000C5974  7C C6 60 38 */	and r6, r6, r12
/* 800CAA78 000C5978  7C C6 38 50 */	subf r6, r6, r7
/* 800CAA7C 000C597C  54 C6 0F FE */	srwi r6, r6, 0x1f
/* 800CAA80 000C5980  7C C6 5B 79 */	or. r6, r6, r11
/* 800CAA84 000C5984  41 82 00 30 */	beq lbl_800CAAB4
/* 800CAA88 000C5988  A0 C3 08 F8 */	lhz r6, 0x8f8(r3)
/* 800CAA8C 000C598C  38 C6 00 01 */	addi r6, r6, 1
/* 800CAA90 000C5990  B0 C3 08 F8 */	sth r6, 0x8f8(r3)
/* 800CAA94 000C5994  54 C7 04 3E */	clrlwi r7, r6, 0x10
/* 800CAA98 000C5998  A0 CD 82 56 */	lhz r6, __WPAD_dpd_diff_count_threshold-_SDA_BASE_(r13)
/* 800CAA9C 000C599C  7C 07 30 40 */	cmplw r7, r6
/* 800CAAA0 000C59A0  40 81 00 58 */	ble lbl_800CAAF8
/* 800CAAA4 000C59A4  60 00 00 01 */	ori r0, r0, 1
/* 800CAAA8 000C59A8  B1 23 08 F8 */	sth r9, 0x8f8(r3)
/* 800CAAAC 000C59AC  54 00 06 3E */	clrlwi r0, r0, 0x18
/* 800CAAB0 000C59B0  48 00 00 48 */	b lbl_800CAAF8
lbl_800CAAB4:
/* 800CAAB4 000C59B4  A0 C3 08 FA */	lhz r6, 0x8fa(r3)
/* 800CAAB8 000C59B8  A0 ED 82 5A */	lhz r7, __WPAD_dpd_hyst_count_threshold-_SDA_BASE_(r13)
/* 800CAABC 000C59BC  39 06 00 01 */	addi r8, r6, 1
/* 800CAAC0 000C59C0  7C C8 3B D6 */	divw r6, r8, r7
/* 800CAAC4 000C59C4  7C C6 39 D6 */	mullw r6, r6, r7
/* 800CAAC8 000C59C8  7C C6 40 50 */	subf r6, r6, r8
/* 800CAACC 000C59CC  B0 C3 08 FA */	sth r6, 0x8fa(r3)
/* 800CAAD0 000C59D0  54 C7 04 3E */	clrlwi r7, r6, 0x10
/* 800CAAD4 000C59D4  A0 CD 82 5A */	lhz r6, __WPAD_dpd_hyst_count_threshold-_SDA_BASE_(r13)
/* 800CAAD8 000C59D8  38 C6 FF FF */	addi r6, r6, -1
/* 800CAADC 000C59DC  7C 07 30 00 */	cmpw r7, r6
/* 800CAAE0 000C59E0  40 82 00 18 */	bne lbl_800CAAF8
/* 800CAAE4 000C59E4  A0 C3 08 F8 */	lhz r6, 0x8f8(r3)
/* 800CAAE8 000C59E8  2C 06 00 00 */	cmpwi r6, 0
/* 800CAAEC 000C59EC  41 82 00 0C */	beq lbl_800CAAF8
/* 800CAAF0 000C59F0  38 C6 FF FF */	addi r6, r6, -1
/* 800CAAF4 000C59F4  B0 C3 08 F8 */	sth r6, 0x8f8(r3)
lbl_800CAAF8:
/* 800CAAF8 000C59F8  38 A5 00 08 */	addi r5, r5, 8
/* 800CAAFC 000C59FC  38 84 00 08 */	addi r4, r4, 8
/* 800CAB00 000C5A00  42 00 FF 30 */	bdnz lbl_800CAA30
/* 800CAB04 000C5A04  48 00 09 60 */	b lbl_800CB464
lbl_800CAB08:
/* 800CAB08 000C5A08  38 06 FF FD */	addi r0, r6, -3
/* 800CAB0C 000C5A0C  28 00 00 02 */	cmplwi r0, 2
/* 800CAB10 000C5A10  41 81 03 80 */	bgt lbl_800CAE90
/* 800CAB14 000C5A14  88 04 00 29 */	lbz r0, 0x29(r4)
/* 800CAB18 000C5A18  7C 86 23 78 */	mr r6, r4
/* 800CAB1C 000C5A1C  A1 44 00 00 */	lhz r10, 0(r4)
/* 800CAB20 000C5A20  7C A7 2B 78 */	mr r7, r5
/* 800CAB24 000C5A24  A1 25 00 00 */	lhz r9, 0(r5)
/* 800CAB28 000C5A28  7C 00 07 75 */	extsb. r0, r0
/* 800CAB2C 000C5A2C  7D 0A 48 50 */	subf r8, r10, r9
/* 800CAB30 000C5A30  7C 09 50 50 */	subf r0, r9, r10
/* 800CAB34 000C5A34  7D 00 03 78 */	or r0, r8, r0
/* 800CAB38 000C5A38  54 00 0F FE */	srwi r0, r0, 0x1f
/* 800CAB3C 000C5A3C  40 82 09 28 */	bne lbl_800CB464
/* 800CAB40 000C5A40  89 05 00 29 */	lbz r8, 0x29(r5)
/* 800CAB44 000C5A44  7D 08 07 75 */	extsb. r8, r8
/* 800CAB48 000C5A48  40 82 09 1C */	bne lbl_800CB464
/* 800CAB4C 000C5A4C  A9 25 00 04 */	lha r9, 4(r5)
/* 800CAB50 000C5A50  A9 04 00 04 */	lha r8, 4(r4)
/* 800CAB54 000C5A54  7D 89 40 51 */	subf. r12, r9, r8
/* 800CAB58 000C5A58  40 80 00 08 */	bge lbl_800CAB60
/* 800CAB5C 000C5A5C  7D 88 48 50 */	subf r12, r8, r9
lbl_800CAB60:
/* 800CAB60 000C5A60  A9 65 00 02 */	lha r11, 2(r5)
/* 800CAB64 000C5A64  69 88 00 0C */	xori r8, r12, 0xc
/* 800CAB68 000C5A68  A9 44 00 02 */	lha r10, 2(r4)
/* 800CAB6C 000C5A6C  7D 09 0E 70 */	srawi r9, r8, 1
/* 800CAB70 000C5A70  7D 08 60 38 */	and r8, r8, r12
/* 800CAB74 000C5A74  7D 08 48 50 */	subf r8, r8, r9
/* 800CAB78 000C5A78  7F 8B 50 51 */	subf. r28, r11, r10
/* 800CAB7C 000C5A7C  55 0C 0F FE */	srwi r12, r8, 0x1f
/* 800CAB80 000C5A80  40 80 00 08 */	bge lbl_800CAB88
/* 800CAB84 000C5A84  7F 8A 58 50 */	subf r28, r10, r11
lbl_800CAB88:
/* 800CAB88 000C5A88  A9 65 00 06 */	lha r11, 6(r5)
/* 800CAB8C 000C5A8C  6B 88 00 0C */	xori r8, r28, 0xc
/* 800CAB90 000C5A90  A9 44 00 06 */	lha r10, 6(r4)
/* 800CAB94 000C5A94  7D 09 0E 70 */	srawi r9, r8, 1
/* 800CAB98 000C5A98  7D 08 E0 38 */	and r8, r8, r28
/* 800CAB9C 000C5A9C  7D 08 48 50 */	subf r8, r8, r9
/* 800CABA0 000C5AA0  7F 8B 50 51 */	subf. r28, r11, r10
/* 800CABA4 000C5AA4  55 08 0F FE */	srwi r8, r8, 0x1f
/* 800CABA8 000C5AA8  40 80 00 08 */	bge lbl_800CABB0
/* 800CABAC 000C5AAC  7F 8A 58 50 */	subf r28, r10, r11
lbl_800CABB0:
/* 800CABB0 000C5AB0  6B 89 00 0C */	xori r9, r28, 0xc
/* 800CABB4 000C5AB4  7D 08 63 78 */	or r8, r8, r12
/* 800CABB8 000C5AB8  7D 2A 0E 70 */	srawi r10, r9, 1
/* 800CABBC 000C5ABC  7D 29 E0 38 */	and r9, r9, r28
/* 800CABC0 000C5AC0  7D 29 50 50 */	subf r9, r9, r10
/* 800CABC4 000C5AC4  55 29 0F FE */	srwi r9, r9, 0x1f
/* 800CABC8 000C5AC8  7D 28 43 79 */	or. r8, r9, r8
/* 800CABCC 000C5ACC  41 82 00 38 */	beq lbl_800CAC04
/* 800CABD0 000C5AD0  A1 03 08 FC */	lhz r8, 0x8fc(r3)
/* 800CABD4 000C5AD4  39 08 00 01 */	addi r8, r8, 1
/* 800CABD8 000C5AD8  B1 03 08 FC */	sth r8, 0x8fc(r3)
/* 800CABDC 000C5ADC  55 09 04 3E */	clrlwi r9, r8, 0x10
/* 800CABE0 000C5AE0  A1 0D 82 54 */	lhz r8, __WPAD_acc_diff_count_threshold-_SDA_BASE_(r13)
/* 800CABE4 000C5AE4  7C 09 40 40 */	cmplw r9, r8
/* 800CABE8 000C5AE8  40 81 00 60 */	ble lbl_800CAC48
/* 800CABEC 000C5AEC  39 00 00 00 */	li r8, 0
/* 800CABF0 000C5AF0  60 00 00 01 */	ori r0, r0, 1
/* 800CABF4 000C5AF4  B1 03 08 FC */	sth r8, 0x8fc(r3)
/* 800CABF8 000C5AF8  54 00 06 3E */	clrlwi r0, r0, 0x18
/* 800CABFC 000C5AFC  B1 03 08 FE */	sth r8, 0x8fe(r3)
/* 800CAC00 000C5B00  48 00 00 48 */	b lbl_800CAC48
lbl_800CAC04:
/* 800CAC04 000C5B04  A1 03 08 FE */	lhz r8, 0x8fe(r3)
/* 800CAC08 000C5B08  A1 2D 82 58 */	lhz r9, __WPAD_acc_hyst_count_threshold-_SDA_BASE_(r13)
/* 800CAC0C 000C5B0C  39 48 00 01 */	addi r10, r8, 1
/* 800CAC10 000C5B10  7D 0A 4B D6 */	divw r8, r10, r9
/* 800CAC14 000C5B14  7D 08 49 D6 */	mullw r8, r8, r9
/* 800CAC18 000C5B18  7D 08 50 50 */	subf r8, r8, r10
/* 800CAC1C 000C5B1C  B1 03 08 FE */	sth r8, 0x8fe(r3)
/* 800CAC20 000C5B20  55 09 04 3E */	clrlwi r9, r8, 0x10
/* 800CAC24 000C5B24  A1 0D 82 58 */	lhz r8, __WPAD_acc_hyst_count_threshold-_SDA_BASE_(r13)
/* 800CAC28 000C5B28  39 08 FF FF */	addi r8, r8, -1
/* 800CAC2C 000C5B2C  7C 09 40 00 */	cmpw r9, r8
/* 800CAC30 000C5B30  40 82 00 18 */	bne lbl_800CAC48
/* 800CAC34 000C5B34  A1 03 08 FC */	lhz r8, 0x8fc(r3)
/* 800CAC38 000C5B38  2C 08 00 00 */	cmpwi r8, 0
/* 800CAC3C 000C5B3C  41 82 00 0C */	beq lbl_800CAC48
/* 800CAC40 000C5B40  39 08 FF FF */	addi r8, r8, -1
/* 800CAC44 000C5B44  B1 03 08 FC */	sth r8, 0x8fc(r3)
lbl_800CAC48:
/* 800CAC48 000C5B48  39 00 00 04 */	li r8, 4
/* 800CAC4C 000C5B4C  39 60 00 00 */	li r11, 0
/* 800CAC50 000C5B50  7D 09 03 A6 */	mtctr r8
lbl_800CAC54:
/* 800CAC54 000C5B54  A9 27 00 0A */	lha r9, 0xa(r7)
/* 800CAC58 000C5B58  A9 06 00 0A */	lha r8, 0xa(r6)
/* 800CAC5C 000C5B5C  7F 89 40 51 */	subf. r28, r9, r8
/* 800CAC60 000C5B60  40 80 00 08 */	bge lbl_800CAC68
/* 800CAC64 000C5B64  7F 88 48 50 */	subf r28, r8, r9
lbl_800CAC68:
/* 800CAC68 000C5B68  A9 87 00 08 */	lha r12, 8(r7)
/* 800CAC6C 000C5B6C  6B 88 00 02 */	xori r8, r28, 2
/* 800CAC70 000C5B70  A9 46 00 08 */	lha r10, 8(r6)
/* 800CAC74 000C5B74  7D 09 0E 70 */	srawi r9, r8, 1
/* 800CAC78 000C5B78  7D 08 E0 38 */	and r8, r8, r28
/* 800CAC7C 000C5B7C  7D 08 48 50 */	subf r8, r8, r9
/* 800CAC80 000C5B80  7F 8C 50 51 */	subf. r28, r12, r10
/* 800CAC84 000C5B84  55 1D 0F FE */	srwi r29, r8, 0x1f
/* 800CAC88 000C5B88  40 80 00 08 */	bge lbl_800CAC90
/* 800CAC8C 000C5B8C  7F 8A 60 50 */	subf r28, r10, r12
lbl_800CAC90:
/* 800CAC90 000C5B90  6B 88 00 02 */	xori r8, r28, 2
/* 800CAC94 000C5B94  7D 09 0E 70 */	srawi r9, r8, 1
/* 800CAC98 000C5B98  7D 08 E0 38 */	and r8, r8, r28
/* 800CAC9C 000C5B9C  7D 08 48 50 */	subf r8, r8, r9
/* 800CACA0 000C5BA0  55 08 0F FE */	srwi r8, r8, 0x1f
/* 800CACA4 000C5BA4  7D 08 EB 79 */	or. r8, r8, r29
/* 800CACA8 000C5BA8  41 82 00 30 */	beq lbl_800CACD8
/* 800CACAC 000C5BAC  A1 03 08 F8 */	lhz r8, 0x8f8(r3)
/* 800CACB0 000C5BB0  39 08 00 01 */	addi r8, r8, 1
/* 800CACB4 000C5BB4  B1 03 08 F8 */	sth r8, 0x8f8(r3)
/* 800CACB8 000C5BB8  55 09 04 3E */	clrlwi r9, r8, 0x10
/* 800CACBC 000C5BBC  A1 0D 82 56 */	lhz r8, __WPAD_dpd_diff_count_threshold-_SDA_BASE_(r13)
/* 800CACC0 000C5BC0  7C 09 40 40 */	cmplw r9, r8
/* 800CACC4 000C5BC4  40 81 00 58 */	ble lbl_800CAD1C
/* 800CACC8 000C5BC8  60 00 00 01 */	ori r0, r0, 1
/* 800CACCC 000C5BCC  B1 63 08 F8 */	sth r11, 0x8f8(r3)
/* 800CACD0 000C5BD0  54 00 06 3E */	clrlwi r0, r0, 0x18
/* 800CACD4 000C5BD4  48 00 00 48 */	b lbl_800CAD1C
lbl_800CACD8:
/* 800CACD8 000C5BD8  A1 03 08 FA */	lhz r8, 0x8fa(r3)
/* 800CACDC 000C5BDC  A1 2D 82 5A */	lhz r9, __WPAD_dpd_hyst_count_threshold-_SDA_BASE_(r13)
/* 800CACE0 000C5BE0  39 48 00 01 */	addi r10, r8, 1
/* 800CACE4 000C5BE4  7D 0A 4B D6 */	divw r8, r10, r9
/* 800CACE8 000C5BE8  7D 08 49 D6 */	mullw r8, r8, r9
/* 800CACEC 000C5BEC  7D 08 50 50 */	subf r8, r8, r10
/* 800CACF0 000C5BF0  B1 03 08 FA */	sth r8, 0x8fa(r3)
/* 800CACF4 000C5BF4  55 09 04 3E */	clrlwi r9, r8, 0x10
/* 800CACF8 000C5BF8  A1 0D 82 5A */	lhz r8, __WPAD_dpd_hyst_count_threshold-_SDA_BASE_(r13)
/* 800CACFC 000C5BFC  39 08 FF FF */	addi r8, r8, -1
/* 800CAD00 000C5C00  7C 09 40 00 */	cmpw r9, r8
/* 800CAD04 000C5C04  40 82 00 18 */	bne lbl_800CAD1C
/* 800CAD08 000C5C08  A1 03 08 F8 */	lhz r8, 0x8f8(r3)
/* 800CAD0C 000C5C0C  2C 08 00 00 */	cmpwi r8, 0
/* 800CAD10 000C5C10  41 82 00 0C */	beq lbl_800CAD1C
/* 800CAD14 000C5C14  39 08 FF FF */	addi r8, r8, -1
/* 800CAD18 000C5C18  B1 03 08 F8 */	sth r8, 0x8f8(r3)
lbl_800CAD1C:
/* 800CAD1C 000C5C1C  38 E7 00 08 */	addi r7, r7, 8
/* 800CAD20 000C5C20  38 C6 00 08 */	addi r6, r6, 8
/* 800CAD24 000C5C24  42 00 FF 30 */	bdnz lbl_800CAC54
/* 800CAD28 000C5C28  A8 E5 00 2C */	lha r7, 0x2c(r5)
/* 800CAD2C 000C5C2C  A8 C4 00 2C */	lha r6, 0x2c(r4)
/* 800CAD30 000C5C30  7D 47 30 51 */	subf. r10, r7, r6
/* 800CAD34 000C5C34  40 80 00 08 */	bge lbl_800CAD3C
/* 800CAD38 000C5C38  7D 46 38 50 */	subf r10, r6, r7
lbl_800CAD3C:
/* 800CAD3C 000C5C3C  A9 25 00 2A */	lha r9, 0x2a(r5)
/* 800CAD40 000C5C40  69 46 00 0C */	xori r6, r10, 0xc
/* 800CAD44 000C5C44  A9 04 00 2A */	lha r8, 0x2a(r4)
/* 800CAD48 000C5C48  7C C7 0E 70 */	srawi r7, r6, 1
/* 800CAD4C 000C5C4C  7C C6 50 38 */	and r6, r6, r10
/* 800CAD50 000C5C50  7C C6 38 50 */	subf r6, r6, r7
/* 800CAD54 000C5C54  7D 69 40 51 */	subf. r11, r9, r8
/* 800CAD58 000C5C58  54 CA 0F FE */	srwi r10, r6, 0x1f
/* 800CAD5C 000C5C5C  40 80 00 08 */	bge lbl_800CAD64
/* 800CAD60 000C5C60  7D 68 48 50 */	subf r11, r8, r9
lbl_800CAD64:
/* 800CAD64 000C5C64  A9 25 00 2E */	lha r9, 0x2e(r5)
/* 800CAD68 000C5C68  69 66 00 0C */	xori r6, r11, 0xc
/* 800CAD6C 000C5C6C  A9 04 00 2E */	lha r8, 0x2e(r4)
/* 800CAD70 000C5C70  7C C7 0E 70 */	srawi r7, r6, 1
/* 800CAD74 000C5C74  7C C6 58 38 */	and r6, r6, r11
/* 800CAD78 000C5C78  7C C6 38 50 */	subf r6, r6, r7
/* 800CAD7C 000C5C7C  7D 69 40 51 */	subf. r11, r9, r8
/* 800CAD80 000C5C80  54 C6 0F FE */	srwi r6, r6, 0x1f
/* 800CAD84 000C5C84  40 80 00 08 */	bge lbl_800CAD8C
/* 800CAD88 000C5C88  7D 68 48 50 */	subf r11, r8, r9
lbl_800CAD8C:
/* 800CAD8C 000C5C8C  69 67 00 0C */	xori r7, r11, 0xc
/* 800CAD90 000C5C90  7C C6 53 78 */	or r6, r6, r10
/* 800CAD94 000C5C94  7C E8 0E 70 */	srawi r8, r7, 1
/* 800CAD98 000C5C98  7C E7 58 38 */	and r7, r7, r11
/* 800CAD9C 000C5C9C  7C E7 40 50 */	subf r7, r7, r8
/* 800CADA0 000C5CA0  54 E7 0F FE */	srwi r7, r7, 0x1f
/* 800CADA4 000C5CA4  7C E6 33 79 */	or. r6, r7, r6
/* 800CADA8 000C5CA8  41 82 00 38 */	beq lbl_800CADE0
/* 800CADAC 000C5CAC  A0 C3 09 00 */	lhz r6, 0x900(r3)
/* 800CADB0 000C5CB0  38 C6 00 01 */	addi r6, r6, 1
/* 800CADB4 000C5CB4  B0 C3 09 00 */	sth r6, 0x900(r3)
/* 800CADB8 000C5CB8  54 C7 04 3E */	clrlwi r7, r6, 0x10
/* 800CADBC 000C5CBC  A0 CD 82 54 */	lhz r6, __WPAD_acc_diff_count_threshold-_SDA_BASE_(r13)
/* 800CADC0 000C5CC0  7C 07 30 40 */	cmplw r7, r6
/* 800CADC4 000C5CC4  40 81 00 60 */	ble lbl_800CAE24
/* 800CADC8 000C5CC8  38 C0 00 00 */	li r6, 0
/* 800CADCC 000C5CCC  60 00 00 01 */	ori r0, r0, 1
/* 800CADD0 000C5CD0  B0 C3 09 00 */	sth r6, 0x900(r3)
/* 800CADD4 000C5CD4  54 00 06 3E */	clrlwi r0, r0, 0x18
/* 800CADD8 000C5CD8  B0 C3 09 02 */	sth r6, 0x902(r3)
/* 800CADDC 000C5CDC  48 00 00 48 */	b lbl_800CAE24
lbl_800CADE0:
/* 800CADE0 000C5CE0  A0 C3 09 02 */	lhz r6, 0x902(r3)
/* 800CADE4 000C5CE4  A0 ED 82 58 */	lhz r7, __WPAD_acc_hyst_count_threshold-_SDA_BASE_(r13)
/* 800CADE8 000C5CE8  39 06 00 01 */	addi r8, r6, 1
/* 800CADEC 000C5CEC  7C C8 3B D6 */	divw r6, r8, r7
/* 800CADF0 000C5CF0  7C C6 39 D6 */	mullw r6, r6, r7
/* 800CADF4 000C5CF4  7C C6 40 50 */	subf r6, r6, r8
/* 800CADF8 000C5CF8  B0 C3 09 02 */	sth r6, 0x902(r3)
/* 800CADFC 000C5CFC  54 C7 04 3E */	clrlwi r7, r6, 0x10
/* 800CAE00 000C5D00  A0 CD 82 58 */	lhz r6, __WPAD_acc_hyst_count_threshold-_SDA_BASE_(r13)
/* 800CAE04 000C5D04  38 C6 FF FF */	addi r6, r6, -1
/* 800CAE08 000C5D08  7C 07 30 00 */	cmpw r7, r6
/* 800CAE0C 000C5D0C  40 82 00 18 */	bne lbl_800CAE24
/* 800CAE10 000C5D10  A0 C3 09 00 */	lhz r6, 0x900(r3)
/* 800CAE14 000C5D14  2C 06 00 00 */	cmpwi r6, 0
/* 800CAE18 000C5D18  41 82 00 0C */	beq lbl_800CAE24
/* 800CAE1C 000C5D1C  38 C6 FF FF */	addi r6, r6, -1
/* 800CAE20 000C5D20  B0 C3 09 00 */	sth r6, 0x900(r3)
lbl_800CAE24:
/* 800CAE24 000C5D24  88 C5 00 30 */	lbz r6, 0x30(r5)
/* 800CAE28 000C5D28  88 64 00 30 */	lbz r3, 0x30(r4)
/* 800CAE2C 000C5D2C  7C C6 07 74 */	extsb r6, r6
/* 800CAE30 000C5D30  7C 63 07 74 */	extsb r3, r3
/* 800CAE34 000C5D34  7C E6 18 51 */	subf. r7, r6, r3
/* 800CAE38 000C5D38  40 80 00 08 */	bge lbl_800CAE40
/* 800CAE3C 000C5D3C  7C E3 30 50 */	subf r7, r3, r6
lbl_800CAE40:
/* 800CAE40 000C5D40  88 C5 00 31 */	lbz r6, 0x31(r5)
/* 800CAE44 000C5D44  68 E3 00 01 */	xori r3, r7, 1
/* 800CAE48 000C5D48  88 A4 00 31 */	lbz r5, 0x31(r4)
/* 800CAE4C 000C5D4C  7C 64 0E 70 */	srawi r4, r3, 1
/* 800CAE50 000C5D50  7C 63 38 38 */	and r3, r3, r7
/* 800CAE54 000C5D54  7C C6 07 74 */	extsb r6, r6
/* 800CAE58 000C5D58  7C A5 07 74 */	extsb r5, r5
/* 800CAE5C 000C5D5C  7C 63 20 50 */	subf r3, r3, r4
/* 800CAE60 000C5D60  54 63 0F FE */	srwi r3, r3, 0x1f
/* 800CAE64 000C5D64  7C E6 28 51 */	subf. r7, r6, r5
/* 800CAE68 000C5D68  7C 00 1B 78 */	or r0, r0, r3
/* 800CAE6C 000C5D6C  40 80 00 08 */	bge lbl_800CAE74
/* 800CAE70 000C5D70  7C E5 30 50 */	subf r7, r5, r6
lbl_800CAE74:
/* 800CAE74 000C5D74  68 E3 00 01 */	xori r3, r7, 1
/* 800CAE78 000C5D78  7C 64 0E 70 */	srawi r4, r3, 1
/* 800CAE7C 000C5D7C  7C 63 38 38 */	and r3, r3, r7
/* 800CAE80 000C5D80  7C 63 20 50 */	subf r3, r3, r4
/* 800CAE84 000C5D84  54 63 0F FE */	srwi r3, r3, 0x1f
/* 800CAE88 000C5D88  7C 00 1B 78 */	or r0, r0, r3
/* 800CAE8C 000C5D8C  48 00 05 D8 */	b lbl_800CB464
lbl_800CAE90:
/* 800CAE90 000C5D90  38 06 FF FA */	addi r0, r6, -6
/* 800CAE94 000C5D94  28 00 00 02 */	cmplwi r0, 2
/* 800CAE98 000C5D98  41 81 03 C0 */	bgt lbl_800CB258
/* 800CAE9C 000C5D9C  2C 08 00 02 */	cmpwi r8, 2
/* 800CAEA0 000C5DA0  7C 86 23 78 */	mr r6, r4
/* 800CAEA4 000C5DA4  7C A7 2B 78 */	mr r7, r5
/* 800CAEA8 000C5DA8  41 82 00 40 */	beq lbl_800CAEE8
/* 800CAEAC 000C5DAC  40 80 00 10 */	bge lbl_800CAEBC
/* 800CAEB0 000C5DB0  2C 08 00 01 */	cmpwi r8, 1
/* 800CAEB4 000C5DB4  40 80 00 14 */	bge lbl_800CAEC8
/* 800CAEB8 000C5DB8  48 00 00 30 */	b lbl_800CAEE8
lbl_800CAEBC:
/* 800CAEBC 000C5DBC  2C 08 00 04 */	cmpwi r8, 4
/* 800CAEC0 000C5DC0  40 80 00 28 */	bge lbl_800CAEE8
/* 800CAEC4 000C5DC4  48 00 00 14 */	b lbl_800CAED8
lbl_800CAEC8:
/* 800CAEC8 000C5DC8  39 00 00 10 */	li r8, 0x10
/* 800CAECC 000C5DCC  39 20 00 20 */	li r9, 0x20
/* 800CAED0 000C5DD0  39 40 00 08 */	li r10, 8
/* 800CAED4 000C5DD4  48 00 00 20 */	b lbl_800CAEF4
lbl_800CAED8:
/* 800CAED8 000C5DD8  39 00 00 04 */	li r8, 4
/* 800CAEDC 000C5DDC  39 20 00 04 */	li r9, 4
/* 800CAEE0 000C5DE0  39 40 00 01 */	li r10, 1
/* 800CAEE4 000C5DE4  48 00 00 10 */	b lbl_800CAEF4
lbl_800CAEE8:
/* 800CAEE8 000C5DE8  39 00 00 01 */	li r8, 1
/* 800CAEEC 000C5DEC  39 20 00 01 */	li r9, 1
/* 800CAEF0 000C5DF0  39 40 00 01 */	li r10, 1
lbl_800CAEF4:
/* 800CAEF4 000C5DF4  88 04 00 29 */	lbz r0, 0x29(r4)
/* 800CAEF8 000C5DF8  A3 C4 00 00 */	lhz r30, 0(r4)
/* 800CAEFC 000C5DFC  A1 85 00 00 */	lhz r12, 0(r5)
/* 800CAF00 000C5E00  7C 00 07 75 */	extsb. r0, r0
/* 800CAF04 000C5E04  7D 7E 60 50 */	subf r11, r30, r12
/* 800CAF08 000C5E08  7C 0C F0 50 */	subf r0, r12, r30
/* 800CAF0C 000C5E0C  7D 60 03 78 */	or r0, r11, r0
/* 800CAF10 000C5E10  54 00 0F FE */	srwi r0, r0, 0x1f
/* 800CAF14 000C5E14  40 82 05 50 */	bne lbl_800CB464
/* 800CAF18 000C5E18  89 65 00 29 */	lbz r11, 0x29(r5)
/* 800CAF1C 000C5E1C  7D 6B 07 75 */	extsb. r11, r11
/* 800CAF20 000C5E20  40 82 05 44 */	bne lbl_800CB464
/* 800CAF24 000C5E24  A9 85 00 04 */	lha r12, 4(r5)
/* 800CAF28 000C5E28  A9 64 00 04 */	lha r11, 4(r4)
/* 800CAF2C 000C5E2C  7F 8C 58 51 */	subf. r28, r12, r11
/* 800CAF30 000C5E30  40 80 00 08 */	bge lbl_800CAF38
/* 800CAF34 000C5E34  7F 8B 60 50 */	subf r28, r11, r12
lbl_800CAF38:
/* 800CAF38 000C5E38  AB E5 00 02 */	lha r31, 2(r5)
/* 800CAF3C 000C5E3C  6B 8B 00 0C */	xori r11, r28, 0xc
/* 800CAF40 000C5E40  AB C4 00 02 */	lha r30, 2(r4)
/* 800CAF44 000C5E44  7D 6C 0E 70 */	srawi r12, r11, 1
/* 800CAF48 000C5E48  7D 6B E0 38 */	and r11, r11, r28
/* 800CAF4C 000C5E4C  7D 6B 60 50 */	subf r11, r11, r12
/* 800CAF50 000C5E50  7F 9F F0 51 */	subf. r28, r31, r30
/* 800CAF54 000C5E54  55 7D 0F FE */	srwi r29, r11, 0x1f
/* 800CAF58 000C5E58  40 80 00 08 */	bge lbl_800CAF60
/* 800CAF5C 000C5E5C  7F 9E F8 50 */	subf r28, r30, r31
lbl_800CAF60:
/* 800CAF60 000C5E60  AB E5 00 06 */	lha r31, 6(r5)
/* 800CAF64 000C5E64  6B 8B 00 0C */	xori r11, r28, 0xc
/* 800CAF68 000C5E68  AB C4 00 06 */	lha r30, 6(r4)
/* 800CAF6C 000C5E6C  7D 6C 0E 70 */	srawi r12, r11, 1
/* 800CAF70 000C5E70  7D 6B E0 38 */	and r11, r11, r28
/* 800CAF74 000C5E74  7D 6B 60 50 */	subf r11, r11, r12
/* 800CAF78 000C5E78  7F 9F F0 51 */	subf. r28, r31, r30
/* 800CAF7C 000C5E7C  55 6B 0F FE */	srwi r11, r11, 0x1f
/* 800CAF80 000C5E80  40 80 00 08 */	bge lbl_800CAF88
/* 800CAF84 000C5E84  7F 9E F8 50 */	subf r28, r30, r31
lbl_800CAF88:
/* 800CAF88 000C5E88  6B 8C 00 0C */	xori r12, r28, 0xc
/* 800CAF8C 000C5E8C  7D 6B EB 78 */	or r11, r11, r29
/* 800CAF90 000C5E90  7D 9E 0E 70 */	srawi r30, r12, 1
/* 800CAF94 000C5E94  7D 8C E0 38 */	and r12, r12, r28
/* 800CAF98 000C5E98  7D 8C F0 50 */	subf r12, r12, r30
/* 800CAF9C 000C5E9C  55 8C 0F FE */	srwi r12, r12, 0x1f
/* 800CAFA0 000C5EA0  7D 8B 5B 79 */	or. r11, r12, r11
/* 800CAFA4 000C5EA4  41 82 00 38 */	beq lbl_800CAFDC
/* 800CAFA8 000C5EA8  A1 63 08 FC */	lhz r11, 0x8fc(r3)
/* 800CAFAC 000C5EAC  39 6B 00 01 */	addi r11, r11, 1
/* 800CAFB0 000C5EB0  B1 63 08 FC */	sth r11, 0x8fc(r3)
/* 800CAFB4 000C5EB4  55 6C 04 3E */	clrlwi r12, r11, 0x10
/* 800CAFB8 000C5EB8  A1 6D 82 54 */	lhz r11, __WPAD_acc_diff_count_threshold-_SDA_BASE_(r13)
/* 800CAFBC 000C5EBC  7C 0C 58 40 */	cmplw r12, r11
/* 800CAFC0 000C5EC0  40 81 00 60 */	ble lbl_800CB020
/* 800CAFC4 000C5EC4  39 60 00 00 */	li r11, 0
/* 800CAFC8 000C5EC8  60 00 00 01 */	ori r0, r0, 1
/* 800CAFCC 000C5ECC  B1 63 08 FC */	sth r11, 0x8fc(r3)
/* 800CAFD0 000C5ED0  54 00 06 3E */	clrlwi r0, r0, 0x18
/* 800CAFD4 000C5ED4  B1 63 08 FE */	sth r11, 0x8fe(r3)
/* 800CAFD8 000C5ED8  48 00 00 48 */	b lbl_800CB020
lbl_800CAFDC:
/* 800CAFDC 000C5EDC  A1 63 08 FE */	lhz r11, 0x8fe(r3)
/* 800CAFE0 000C5EE0  A1 8D 82 58 */	lhz r12, __WPAD_acc_hyst_count_threshold-_SDA_BASE_(r13)
/* 800CAFE4 000C5EE4  3B CB 00 01 */	addi r30, r11, 1
/* 800CAFE8 000C5EE8  7D 7E 63 D6 */	divw r11, r30, r12
/* 800CAFEC 000C5EEC  7D 6B 61 D6 */	mullw r11, r11, r12
/* 800CAFF0 000C5EF0  7D 6B F0 50 */	subf r11, r11, r30
/* 800CAFF4 000C5EF4  B1 63 08 FE */	sth r11, 0x8fe(r3)
/* 800CAFF8 000C5EF8  55 6C 04 3E */	clrlwi r12, r11, 0x10
/* 800CAFFC 000C5EFC  A1 6D 82 58 */	lhz r11, __WPAD_acc_hyst_count_threshold-_SDA_BASE_(r13)
/* 800CB000 000C5F00  39 6B FF FF */	addi r11, r11, -1
/* 800CB004 000C5F04  7C 0C 58 00 */	cmpw r12, r11
/* 800CB008 000C5F08  40 82 00 18 */	bne lbl_800CB020
/* 800CB00C 000C5F0C  A1 63 08 FC */	lhz r11, 0x8fc(r3)
/* 800CB010 000C5F10  2C 0B 00 00 */	cmpwi r11, 0
/* 800CB014 000C5F14  41 82 00 0C */	beq lbl_800CB020
/* 800CB018 000C5F18  39 6B FF FF */	addi r11, r11, -1
/* 800CB01C 000C5F1C  B1 63 08 FC */	sth r11, 0x8fc(r3)
lbl_800CB020:
/* 800CB020 000C5F20  39 60 00 04 */	li r11, 4
/* 800CB024 000C5F24  3B C0 00 00 */	li r30, 0
/* 800CB028 000C5F28  7D 69 03 A6 */	mtctr r11
lbl_800CB02C:
/* 800CB02C 000C5F2C  A9 87 00 0A */	lha r12, 0xa(r7)
/* 800CB030 000C5F30  A9 66 00 0A */	lha r11, 0xa(r6)
/* 800CB034 000C5F34  7F 8C 58 51 */	subf. r28, r12, r11
/* 800CB038 000C5F38  40 80 00 08 */	bge lbl_800CB040
/* 800CB03C 000C5F3C  7F 8B 60 50 */	subf r28, r11, r12
lbl_800CB040:
/* 800CB040 000C5F40  AB A7 00 08 */	lha r29, 8(r7)
/* 800CB044 000C5F44  6B 8B 00 02 */	xori r11, r28, 2
/* 800CB048 000C5F48  AB E6 00 08 */	lha r31, 8(r6)
/* 800CB04C 000C5F4C  7D 6C 0E 70 */	srawi r12, r11, 1
/* 800CB050 000C5F50  7D 6B E0 38 */	and r11, r11, r28
/* 800CB054 000C5F54  7D 6B 60 50 */	subf r11, r11, r12
/* 800CB058 000C5F58  7F 7D F8 51 */	subf. r27, r29, r31
/* 800CB05C 000C5F5C  55 7C 0F FE */	srwi r28, r11, 0x1f
/* 800CB060 000C5F60  40 80 00 08 */	bge lbl_800CB068
/* 800CB064 000C5F64  7F 7F E8 50 */	subf r27, r31, r29
lbl_800CB068:
/* 800CB068 000C5F68  6B 6B 00 02 */	xori r11, r27, 2
/* 800CB06C 000C5F6C  7D 6C 0E 70 */	srawi r12, r11, 1
/* 800CB070 000C5F70  7D 6B D8 38 */	and r11, r11, r27
/* 800CB074 000C5F74  7D 6B 60 50 */	subf r11, r11, r12
/* 800CB078 000C5F78  55 6B 0F FE */	srwi r11, r11, 0x1f
/* 800CB07C 000C5F7C  7D 6B E3 79 */	or. r11, r11, r28
/* 800CB080 000C5F80  41 82 00 30 */	beq lbl_800CB0B0
/* 800CB084 000C5F84  A1 63 08 F8 */	lhz r11, 0x8f8(r3)
/* 800CB088 000C5F88  39 6B 00 01 */	addi r11, r11, 1
/* 800CB08C 000C5F8C  B1 63 08 F8 */	sth r11, 0x8f8(r3)
/* 800CB090 000C5F90  55 6C 04 3E */	clrlwi r12, r11, 0x10
/* 800CB094 000C5F94  A1 6D 82 56 */	lhz r11, __WPAD_dpd_diff_count_threshold-_SDA_BASE_(r13)
/* 800CB098 000C5F98  7C 0C 58 40 */	cmplw r12, r11
/* 800CB09C 000C5F9C  40 81 00 58 */	ble lbl_800CB0F4
/* 800CB0A0 000C5FA0  60 00 00 01 */	ori r0, r0, 1
/* 800CB0A4 000C5FA4  B3 C3 08 F8 */	sth r30, 0x8f8(r3)
/* 800CB0A8 000C5FA8  54 00 06 3E */	clrlwi r0, r0, 0x18
/* 800CB0AC 000C5FAC  48 00 00 48 */	b lbl_800CB0F4
lbl_800CB0B0:
/* 800CB0B0 000C5FB0  A1 63 08 FA */	lhz r11, 0x8fa(r3)
/* 800CB0B4 000C5FB4  A1 8D 82 5A */	lhz r12, __WPAD_dpd_hyst_count_threshold-_SDA_BASE_(r13)
/* 800CB0B8 000C5FB8  3B EB 00 01 */	addi r31, r11, 1
/* 800CB0BC 000C5FBC  7D 7F 63 D6 */	divw r11, r31, r12
/* 800CB0C0 000C5FC0  7D 6B 61 D6 */	mullw r11, r11, r12
/* 800CB0C4 000C5FC4  7D 6B F8 50 */	subf r11, r11, r31
/* 800CB0C8 000C5FC8  B1 63 08 FA */	sth r11, 0x8fa(r3)
/* 800CB0CC 000C5FCC  55 6C 04 3E */	clrlwi r12, r11, 0x10
/* 800CB0D0 000C5FD0  A1 6D 82 5A */	lhz r11, __WPAD_dpd_hyst_count_threshold-_SDA_BASE_(r13)
/* 800CB0D4 000C5FD4  39 6B FF FF */	addi r11, r11, -1
/* 800CB0D8 000C5FD8  7C 0C 58 00 */	cmpw r12, r11
/* 800CB0DC 000C5FDC  40 82 00 18 */	bne lbl_800CB0F4
/* 800CB0E0 000C5FE0  A1 63 08 F8 */	lhz r11, 0x8f8(r3)
/* 800CB0E4 000C5FE4  2C 0B 00 00 */	cmpwi r11, 0
/* 800CB0E8 000C5FE8  41 82 00 0C */	beq lbl_800CB0F4
/* 800CB0EC 000C5FEC  39 6B FF FF */	addi r11, r11, -1
/* 800CB0F0 000C5FF0  B1 63 08 F8 */	sth r11, 0x8f8(r3)
lbl_800CB0F4:
/* 800CB0F4 000C5FF4  38 E7 00 08 */	addi r7, r7, 8
/* 800CB0F8 000C5FF8  38 C6 00 08 */	addi r6, r6, 8
/* 800CB0FC 000C5FFC  42 00 FF 30 */	bdnz lbl_800CB02C
/* 800CB100 000C6000  A8 C5 00 2C */	lha r6, 0x2c(r5)
/* 800CB104 000C6004  A1 64 00 2A */	lhz r11, 0x2a(r4)
/* 800CB108 000C6008  7D 86 43 D6 */	divw r12, r6, r8
/* 800CB10C 000C600C  A0 C5 00 2A */	lhz r6, 0x2a(r5)
/* 800CB110 000C6010  A8 64 00 2C */	lha r3, 0x2c(r4)
/* 800CB114 000C6014  7C EB 30 50 */	subf r7, r11, r6
/* 800CB118 000C6018  7C C6 58 50 */	subf r6, r6, r11
/* 800CB11C 000C601C  7C E6 33 78 */	or r6, r7, r6
/* 800CB120 000C6020  7C E3 43 D6 */	divw r7, r3, r8
/* 800CB124 000C6024  54 C3 0F FE */	srwi r3, r6, 0x1f
/* 800CB128 000C6028  7C 00 1B 78 */	or r0, r0, r3
/* 800CB12C 000C602C  7F 6C 38 51 */	subf. r27, r12, r7
/* 800CB130 000C6030  40 80 00 08 */	bge lbl_800CB138
/* 800CB134 000C6034  7F 67 60 50 */	subf r27, r7, r12
lbl_800CB138:
/* 800CB138 000C6038  A8 C5 00 2E */	lha r6, 0x2e(r5)
/* 800CB13C 000C603C  6B 6B 00 01 */	xori r11, r27, 1
/* 800CB140 000C6040  A8 64 00 2E */	lha r3, 0x2e(r4)
/* 800CB144 000C6044  7D 67 0E 70 */	srawi r7, r11, 1
/* 800CB148 000C6048  7D 86 43 D6 */	divw r12, r6, r8
/* 800CB14C 000C604C  7D 66 D8 38 */	and r6, r11, r27
/* 800CB150 000C6050  7C C6 38 50 */	subf r6, r6, r7
/* 800CB154 000C6054  54 C6 0F FE */	srwi r6, r6, 0x1f
/* 800CB158 000C6058  7C 00 33 78 */	or r0, r0, r6
/* 800CB15C 000C605C  7C 63 43 D6 */	divw r3, r3, r8
/* 800CB160 000C6060  7F 6C 18 51 */	subf. r27, r12, r3
/* 800CB164 000C6064  40 80 00 08 */	bge lbl_800CB16C
/* 800CB168 000C6068  7F 63 60 50 */	subf r27, r3, r12
lbl_800CB16C:
/* 800CB16C 000C606C  A8 C5 00 30 */	lha r6, 0x30(r5)
/* 800CB170 000C6070  6B 68 00 01 */	xori r8, r27, 1
/* 800CB174 000C6074  A8 64 00 30 */	lha r3, 0x30(r4)
/* 800CB178 000C6078  7D 07 0E 70 */	srawi r7, r8, 1
/* 800CB17C 000C607C  7D 66 4B D6 */	divw r11, r6, r9
/* 800CB180 000C6080  7D 06 D8 38 */	and r6, r8, r27
/* 800CB184 000C6084  7C C6 38 50 */	subf r6, r6, r7
/* 800CB188 000C6088  54 C6 0F FE */	srwi r6, r6, 0x1f
/* 800CB18C 000C608C  7C 00 33 78 */	or r0, r0, r6
/* 800CB190 000C6090  7C 63 4B D6 */	divw r3, r3, r9
/* 800CB194 000C6094  7D 8B 18 51 */	subf. r12, r11, r3
/* 800CB198 000C6098  40 80 00 08 */	bge lbl_800CB1A0
/* 800CB19C 000C609C  7D 83 58 50 */	subf r12, r3, r11
lbl_800CB1A0:
/* 800CB1A0 000C60A0  A8 C5 00 32 */	lha r6, 0x32(r5)
/* 800CB1A4 000C60A4  69 88 00 01 */	xori r8, r12, 1
/* 800CB1A8 000C60A8  A8 64 00 32 */	lha r3, 0x32(r4)
/* 800CB1AC 000C60AC  7D 07 0E 70 */	srawi r7, r8, 1
/* 800CB1B0 000C60B0  7D 66 4B D6 */	divw r11, r6, r9
/* 800CB1B4 000C60B4  7D 06 60 38 */	and r6, r8, r12
/* 800CB1B8 000C60B8  7C C6 38 50 */	subf r6, r6, r7
/* 800CB1BC 000C60BC  54 C6 0F FE */	srwi r6, r6, 0x1f
/* 800CB1C0 000C60C0  7C 00 33 78 */	or r0, r0, r6
/* 800CB1C4 000C60C4  7C 63 4B D6 */	divw r3, r3, r9
/* 800CB1C8 000C60C8  7D 8B 18 51 */	subf. r12, r11, r3
/* 800CB1CC 000C60CC  40 80 00 08 */	bge lbl_800CB1D4
/* 800CB1D0 000C60D0  7D 83 58 50 */	subf r12, r3, r11
lbl_800CB1D4:
/* 800CB1D4 000C60D4  88 C5 00 34 */	lbz r6, 0x34(r5)
/* 800CB1D8 000C60D8  69 88 00 01 */	xori r8, r12, 1
/* 800CB1DC 000C60DC  88 64 00 34 */	lbz r3, 0x34(r4)
/* 800CB1E0 000C60E0  7D 07 0E 70 */	srawi r7, r8, 1
/* 800CB1E4 000C60E4  7D 26 53 D6 */	divw r9, r6, r10
/* 800CB1E8 000C60E8  7D 06 60 38 */	and r6, r8, r12
/* 800CB1EC 000C60EC  7C C6 38 50 */	subf r6, r6, r7
/* 800CB1F0 000C60F0  54 C6 0F FE */	srwi r6, r6, 0x1f
/* 800CB1F4 000C60F4  7C 00 33 78 */	or r0, r0, r6
/* 800CB1F8 000C60F8  7C 63 53 D6 */	divw r3, r3, r10
/* 800CB1FC 000C60FC  7D 09 18 51 */	subf. r8, r9, r3
/* 800CB200 000C6100  40 80 00 08 */	bge lbl_800CB208
/* 800CB204 000C6104  7D 03 48 50 */	subf r8, r3, r9
lbl_800CB208:
/* 800CB208 000C6108  88 A5 00 35 */	lbz r5, 0x35(r5)
/* 800CB20C 000C610C  69 07 00 01 */	xori r7, r8, 1
/* 800CB210 000C6110  88 64 00 35 */	lbz r3, 0x35(r4)
/* 800CB214 000C6114  7C E6 0E 70 */	srawi r6, r7, 1
/* 800CB218 000C6118  7C A5 53 D6 */	divw r5, r5, r10
/* 800CB21C 000C611C  7C E4 40 38 */	and r4, r7, r8
/* 800CB220 000C6120  7C 84 30 50 */	subf r4, r4, r6
/* 800CB224 000C6124  54 84 0F FE */	srwi r4, r4, 0x1f
/* 800CB228 000C6128  7C 00 23 78 */	or r0, r0, r4
/* 800CB22C 000C612C  7C 63 53 D6 */	divw r3, r3, r10
/* 800CB230 000C6130  7C C5 18 51 */	subf. r6, r5, r3
/* 800CB234 000C6134  40 80 00 08 */	bge lbl_800CB23C
/* 800CB238 000C6138  7C C3 28 50 */	subf r6, r3, r5
lbl_800CB23C:
/* 800CB23C 000C613C  68 C3 00 01 */	xori r3, r6, 1
/* 800CB240 000C6140  7C 64 0E 70 */	srawi r4, r3, 1
/* 800CB244 000C6144  7C 63 30 38 */	and r3, r3, r6
/* 800CB248 000C6148  7C 63 20 50 */	subf r3, r3, r4
/* 800CB24C 000C614C  54 63 0F FE */	srwi r3, r3, 0x1f
/* 800CB250 000C6150  7C 00 1B 78 */	or r0, r0, r3
/* 800CB254 000C6154  48 00 02 10 */	b lbl_800CB464
lbl_800CB258:
/* 800CB258 000C6158  88 04 00 29 */	lbz r0, 0x29(r4)
/* 800CB25C 000C615C  A1 04 00 00 */	lhz r8, 0(r4)
/* 800CB260 000C6160  A0 E5 00 00 */	lhz r7, 0(r5)
/* 800CB264 000C6164  7C 00 07 75 */	extsb. r0, r0
/* 800CB268 000C6168  7C C8 38 50 */	subf r6, r8, r7
/* 800CB26C 000C616C  7C 07 40 50 */	subf r0, r7, r8
/* 800CB270 000C6170  7C C0 03 78 */	or r0, r6, r0
/* 800CB274 000C6174  54 00 0F FE */	srwi r0, r0, 0x1f
/* 800CB278 000C6178  40 82 01 EC */	bne lbl_800CB464
/* 800CB27C 000C617C  88 C5 00 29 */	lbz r6, 0x29(r5)
/* 800CB280 000C6180  7C C6 07 75 */	extsb. r6, r6
/* 800CB284 000C6184  40 82 01 E0 */	bne lbl_800CB464
/* 800CB288 000C6188  A8 E5 00 04 */	lha r7, 4(r5)
/* 800CB28C 000C618C  A8 C4 00 04 */	lha r6, 4(r4)
/* 800CB290 000C6190  7D 47 30 51 */	subf. r10, r7, r6
/* 800CB294 000C6194  40 80 00 08 */	bge lbl_800CB29C
/* 800CB298 000C6198  7D 46 38 50 */	subf r10, r6, r7
lbl_800CB29C:
/* 800CB29C 000C619C  A9 25 00 02 */	lha r9, 2(r5)
/* 800CB2A0 000C61A0  69 46 00 0C */	xori r6, r10, 0xc
/* 800CB2A4 000C61A4  A9 04 00 02 */	lha r8, 2(r4)
/* 800CB2A8 000C61A8  7C C7 0E 70 */	srawi r7, r6, 1
/* 800CB2AC 000C61AC  7C C6 50 38 */	and r6, r6, r10
/* 800CB2B0 000C61B0  7C C6 38 50 */	subf r6, r6, r7
/* 800CB2B4 000C61B4  7D 69 40 51 */	subf. r11, r9, r8
/* 800CB2B8 000C61B8  54 CA 0F FE */	srwi r10, r6, 0x1f
/* 800CB2BC 000C61BC  40 80 00 08 */	bge lbl_800CB2C4
/* 800CB2C0 000C61C0  7D 68 48 50 */	subf r11, r8, r9
lbl_800CB2C4:
/* 800CB2C4 000C61C4  A9 25 00 06 */	lha r9, 6(r5)
/* 800CB2C8 000C61C8  69 66 00 0C */	xori r6, r11, 0xc
/* 800CB2CC 000C61CC  A9 04 00 06 */	lha r8, 6(r4)
/* 800CB2D0 000C61D0  7C C7 0E 70 */	srawi r7, r6, 1
/* 800CB2D4 000C61D4  7C C6 58 38 */	and r6, r6, r11
/* 800CB2D8 000C61D8  7C C6 38 50 */	subf r6, r6, r7
/* 800CB2DC 000C61DC  7D 69 40 51 */	subf. r11, r9, r8
/* 800CB2E0 000C61E0  54 C6 0F FE */	srwi r6, r6, 0x1f
/* 800CB2E4 000C61E4  40 80 00 08 */	bge lbl_800CB2EC
/* 800CB2E8 000C61E8  7D 68 48 50 */	subf r11, r8, r9
lbl_800CB2EC:
/* 800CB2EC 000C61EC  69 67 00 0C */	xori r7, r11, 0xc
/* 800CB2F0 000C61F0  7C C6 53 78 */	or r6, r6, r10
/* 800CB2F4 000C61F4  7C E8 0E 70 */	srawi r8, r7, 1
/* 800CB2F8 000C61F8  7C E7 58 38 */	and r7, r7, r11
/* 800CB2FC 000C61FC  7C E7 40 50 */	subf r7, r7, r8
/* 800CB300 000C6200  54 E7 0F FE */	srwi r7, r7, 0x1f
/* 800CB304 000C6204  7C E6 33 79 */	or. r6, r7, r6
/* 800CB308 000C6208  41 82 00 38 */	beq lbl_800CB340
/* 800CB30C 000C620C  A0 C3 08 FC */	lhz r6, 0x8fc(r3)
/* 800CB310 000C6210  38 C6 00 01 */	addi r6, r6, 1
/* 800CB314 000C6214  B0 C3 08 FC */	sth r6, 0x8fc(r3)
/* 800CB318 000C6218  54 C7 04 3E */	clrlwi r7, r6, 0x10
/* 800CB31C 000C621C  A0 CD 82 54 */	lhz r6, __WPAD_acc_diff_count_threshold-_SDA_BASE_(r13)
/* 800CB320 000C6220  7C 07 30 40 */	cmplw r7, r6
/* 800CB324 000C6224  40 81 00 60 */	ble lbl_800CB384
/* 800CB328 000C6228  38 C0 00 00 */	li r6, 0
/* 800CB32C 000C622C  60 00 00 01 */	ori r0, r0, 1
/* 800CB330 000C6230  B0 C3 08 FC */	sth r6, 0x8fc(r3)
/* 800CB334 000C6234  54 00 06 3E */	clrlwi r0, r0, 0x18
/* 800CB338 000C6238  B0 C3 08 FE */	sth r6, 0x8fe(r3)
/* 800CB33C 000C623C  48 00 00 48 */	b lbl_800CB384
lbl_800CB340:
/* 800CB340 000C6240  A0 C3 08 FE */	lhz r6, 0x8fe(r3)
/* 800CB344 000C6244  A0 ED 82 58 */	lhz r7, __WPAD_acc_hyst_count_threshold-_SDA_BASE_(r13)
/* 800CB348 000C6248  39 06 00 01 */	addi r8, r6, 1
/* 800CB34C 000C624C  7C C8 3B D6 */	divw r6, r8, r7
/* 800CB350 000C6250  7C C6 39 D6 */	mullw r6, r6, r7
/* 800CB354 000C6254  7C C6 40 50 */	subf r6, r6, r8
/* 800CB358 000C6258  B0 C3 08 FE */	sth r6, 0x8fe(r3)
/* 800CB35C 000C625C  54 C7 04 3E */	clrlwi r7, r6, 0x10
/* 800CB360 000C6260  A0 CD 82 58 */	lhz r6, __WPAD_acc_hyst_count_threshold-_SDA_BASE_(r13)
/* 800CB364 000C6264  38 C6 FF FF */	addi r6, r6, -1
/* 800CB368 000C6268  7C 07 30 00 */	cmpw r7, r6
/* 800CB36C 000C626C  40 82 00 18 */	bne lbl_800CB384
/* 800CB370 000C6270  A0 C3 08 FC */	lhz r6, 0x8fc(r3)
/* 800CB374 000C6274  2C 06 00 00 */	cmpwi r6, 0
/* 800CB378 000C6278  41 82 00 0C */	beq lbl_800CB384
/* 800CB37C 000C627C  38 C6 FF FF */	addi r6, r6, -1
/* 800CB380 000C6280  B0 C3 08 FC */	sth r6, 0x8fc(r3)
lbl_800CB384:
/* 800CB384 000C6284  38 C0 00 04 */	li r6, 4
/* 800CB388 000C6288  39 20 00 00 */	li r9, 0
/* 800CB38C 000C628C  7C C9 03 A6 */	mtctr r6
lbl_800CB390:
/* 800CB390 000C6290  A8 E5 00 0A */	lha r7, 0xa(r5)
/* 800CB394 000C6294  A8 C4 00 0A */	lha r6, 0xa(r4)
/* 800CB398 000C6298  7D 67 30 51 */	subf. r11, r7, r6
/* 800CB39C 000C629C  40 80 00 08 */	bge lbl_800CB3A4
/* 800CB3A0 000C62A0  7D 66 38 50 */	subf r11, r6, r7
lbl_800CB3A4:
/* 800CB3A4 000C62A4  A9 45 00 08 */	lha r10, 8(r5)
/* 800CB3A8 000C62A8  69 66 00 02 */	xori r6, r11, 2
/* 800CB3AC 000C62AC  A9 04 00 08 */	lha r8, 8(r4)
/* 800CB3B0 000C62B0  7C C7 0E 70 */	srawi r7, r6, 1
/* 800CB3B4 000C62B4  7C C6 58 38 */	and r6, r6, r11
/* 800CB3B8 000C62B8  7C C6 38 50 */	subf r6, r6, r7
/* 800CB3BC 000C62BC  7D 8A 40 51 */	subf. r12, r10, r8
/* 800CB3C0 000C62C0  54 CB 0F FE */	srwi r11, r6, 0x1f
/* 800CB3C4 000C62C4  40 80 00 08 */	bge lbl_800CB3CC
/* 800CB3C8 000C62C8  7D 88 50 50 */	subf r12, r8, r10
lbl_800CB3CC:
/* 800CB3CC 000C62CC  69 86 00 02 */	xori r6, r12, 2
/* 800CB3D0 000C62D0  7C C7 0E 70 */	srawi r7, r6, 1
/* 800CB3D4 000C62D4  7C C6 60 38 */	and r6, r6, r12
/* 800CB3D8 000C62D8  7C C6 38 50 */	subf r6, r6, r7
/* 800CB3DC 000C62DC  54 C6 0F FE */	srwi r6, r6, 0x1f
/* 800CB3E0 000C62E0  7C C6 5B 79 */	or. r6, r6, r11
/* 800CB3E4 000C62E4  41 82 00 30 */	beq lbl_800CB414
/* 800CB3E8 000C62E8  A0 C3 08 F8 */	lhz r6, 0x8f8(r3)
/* 800CB3EC 000C62EC  38 C6 00 01 */	addi r6, r6, 1
/* 800CB3F0 000C62F0  B0 C3 08 F8 */	sth r6, 0x8f8(r3)
/* 800CB3F4 000C62F4  54 C7 04 3E */	clrlwi r7, r6, 0x10
/* 800CB3F8 000C62F8  A0 CD 82 56 */	lhz r6, __WPAD_dpd_diff_count_threshold-_SDA_BASE_(r13)
/* 800CB3FC 000C62FC  7C 07 30 40 */	cmplw r7, r6
/* 800CB400 000C6300  40 81 00 58 */	ble lbl_800CB458
/* 800CB404 000C6304  60 00 00 01 */	ori r0, r0, 1
/* 800CB408 000C6308  B1 23 08 F8 */	sth r9, 0x8f8(r3)
/* 800CB40C 000C630C  54 00 06 3E */	clrlwi r0, r0, 0x18
/* 800CB410 000C6310  48 00 00 48 */	b lbl_800CB458
lbl_800CB414:
/* 800CB414 000C6314  A0 C3 08 FA */	lhz r6, 0x8fa(r3)
/* 800CB418 000C6318  A0 ED 82 5A */	lhz r7, __WPAD_dpd_hyst_count_threshold-_SDA_BASE_(r13)
/* 800CB41C 000C631C  39 06 00 01 */	addi r8, r6, 1
/* 800CB420 000C6320  7C C8 3B D6 */	divw r6, r8, r7
/* 800CB424 000C6324  7C C6 39 D6 */	mullw r6, r6, r7
/* 800CB428 000C6328  7C C6 40 50 */	subf r6, r6, r8
/* 800CB42C 000C632C  B0 C3 08 FA */	sth r6, 0x8fa(r3)
/* 800CB430 000C6330  54 C7 04 3E */	clrlwi r7, r6, 0x10
/* 800CB434 000C6334  A0 CD 82 5A */	lhz r6, __WPAD_dpd_hyst_count_threshold-_SDA_BASE_(r13)
/* 800CB438 000C6338  38 C6 FF FF */	addi r6, r6, -1
/* 800CB43C 000C633C  7C 07 30 00 */	cmpw r7, r6
/* 800CB440 000C6340  40 82 00 18 */	bne lbl_800CB458
/* 800CB444 000C6344  A0 C3 08 F8 */	lhz r6, 0x8f8(r3)
/* 800CB448 000C6348  2C 06 00 00 */	cmpwi r6, 0
/* 800CB44C 000C634C  41 82 00 0C */	beq lbl_800CB458
/* 800CB450 000C6350  38 C6 FF FF */	addi r6, r6, -1
/* 800CB454 000C6354  B0 C3 08 F8 */	sth r6, 0x8f8(r3)
lbl_800CB458:
/* 800CB458 000C6358  38 A5 00 08 */	addi r5, r5, 8
/* 800CB45C 000C635C  38 84 00 08 */	addi r4, r4, 8
/* 800CB460 000C6360  42 00 FF 30 */	bdnz lbl_800CB390
lbl_800CB464:
/* 800CB464 000C6364  39 61 00 20 */	addi r11, r1, 0x20
/* 800CB468 000C6368  54 03 06 3E */	clrlwi r3, r0, 0x18
/* 800CB46C 000C636C  4B FE 69 25 */	bl _restgpr_27
/* 800CB470 000C6370  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800CB474 000C6374  7C 08 03 A6 */	mtlr r0
/* 800CB478 000C6378  38 21 00 20 */	addi r1, r1, 0x20
/* 800CB47C 000C637C  4E 80 00 20 */	blr 

.global CheckButtonCombination
CheckButtonCombination:
/* 800CB480 000C6380  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800CB484 000C6384  7C 08 02 A6 */	mflr r0
/* 800CB488 000C6388  90 01 00 24 */	stw r0, 0x24(r1)
/* 800CB48C 000C638C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800CB490 000C6390  3F E0 80 41 */	lis r31, _wpdcb@ha
/* 800CB494 000C6394  3B FF F6 30 */	addi r31, r31, _wpdcb@l
/* 800CB498 000C6398  93 C1 00 18 */	stw r30, 0x18(r1)
/* 800CB49C 000C639C  54 7E 10 3A */	slwi r30, r3, 2
/* 800CB4A0 000C63A0  93 A1 00 14 */	stw r29, 0x14(r1)
/* 800CB4A4 000C63A4  93 81 00 10 */	stw r28, 0x10(r1)
/* 800CB4A8 000C63A8  3B 80 FF FF */	li r28, -1
/* 800CB4AC 000C63AC  7F BF F0 2E */	lwzx r29, r31, r30
/* 800CB4B0 000C63B0  48 02 64 11 */	bl OSDisableInterrupts
/* 800CB4B4 000C63B4  88 1D 08 C8 */	lbz r0, 0x8c8(r29)
/* 800CB4B8 000C63B8  80 BD 08 B8 */	lwz r5, 0x8b8(r29)
/* 800CB4BC 000C63BC  7C 00 00 34 */	cntlzw r0, r0
/* 800CB4C0 000C63C0  54 04 DE 3E */	rlwinm r4, r0, 0x1b, 0x18, 0x1f
/* 800CB4C4 000C63C4  38 05 FF FD */	addi r0, r5, -3
/* 800CB4C8 000C63C8  1C 84 00 60 */	mulli r4, r4, 0x60
/* 800CB4CC 000C63CC  28 00 00 02 */	cmplwi r0, 2
/* 800CB4D0 000C63D0  7C 9D 22 14 */	add r4, r29, r4
/* 800CB4D4 000C63D4  41 81 00 14 */	bgt lbl_800CB4E8
/* 800CB4D8 000C63D8  A0 04 00 A0 */	lhz r0, 0xa0(r4)
/* 800CB4DC 000C63DC  28 00 1C 10 */	cmplwi r0, 0x1c10
/* 800CB4E0 000C63E0  40 82 00 08 */	bne lbl_800CB4E8
/* 800CB4E4 000C63E4  3B 80 00 01 */	li r28, 1
lbl_800CB4E8:
/* 800CB4E8 000C63E8  38 05 FF FA */	addi r0, r5, -6
/* 800CB4EC 000C63EC  28 00 00 02 */	cmplwi r0, 2
/* 800CB4F0 000C63F0  41 81 00 38 */	bgt lbl_800CB528
/* 800CB4F4 000C63F4  A0 04 00 A0 */	lhz r0, 0xa0(r4)
/* 800CB4F8 000C63F8  28 00 1C 10 */	cmplwi r0, 0x1c10
/* 800CB4FC 000C63FC  40 82 00 08 */	bne lbl_800CB504
/* 800CB500 000C6400  3B 80 00 01 */	li r28, 1
lbl_800CB504:
/* 800CB504 000C6404  88 04 00 C9 */	lbz r0, 0xc9(r4)
/* 800CB508 000C6408  7C 00 07 75 */	extsb. r0, r0
/* 800CB50C 000C640C  41 82 00 0C */	beq lbl_800CB518
/* 800CB510 000C6410  3B 80 00 00 */	li r28, 0
/* 800CB514 000C6414  48 00 00 14 */	b lbl_800CB528
lbl_800CB518:
/* 800CB518 000C6418  A0 04 00 CA */	lhz r0, 0xca(r4)
/* 800CB51C 000C641C  28 00 14 50 */	cmplwi r0, 0x1450
/* 800CB520 000C6420  40 82 00 08 */	bne lbl_800CB528
/* 800CB524 000C6424  3B 80 00 01 */	li r28, 1
lbl_800CB528:
/* 800CB528 000C6428  2C 1C 00 00 */	cmpwi r28, 0
/* 800CB52C 000C642C  40 80 00 10 */	bge lbl_800CB53C
/* 800CB530 000C6430  38 00 00 00 */	li r0, 0
/* 800CB534 000C6434  B0 1D 09 12 */	sth r0, 0x912(r29)
/* 800CB538 000C6438  48 00 00 10 */	b lbl_800CB548
lbl_800CB53C:
/* 800CB53C 000C643C  A0 1D 09 12 */	lhz r0, 0x912(r29)
/* 800CB540 000C6440  7C 00 E2 14 */	add r0, r0, r28
/* 800CB544 000C6444  B0 1D 09 12 */	sth r0, 0x912(r29)
lbl_800CB548:
/* 800CB548 000C6448  48 02 63 A1 */	bl OSRestoreInterrupts
/* 800CB54C 000C644C  A0 1D 09 12 */	lhz r0, 0x912(r29)
/* 800CB550 000C6450  28 00 02 58 */	cmplwi r0, 0x258
/* 800CB554 000C6454  40 81 00 18 */	ble lbl_800CB56C
/* 800CB558 000C6458  7F 9F F0 2E */	lwzx r28, r31, r30
/* 800CB55C 000C645C  48 02 63 65 */	bl OSDisableInterrupts
/* 800CB560 000C6460  38 00 00 00 */	li r0, 0
/* 800CB564 000C6464  98 1C 09 11 */	stb r0, 0x911(r28)
/* 800CB568 000C6468  48 02 63 81 */	bl OSRestoreInterrupts
lbl_800CB56C:
/* 800CB56C 000C646C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800CB570 000C6470  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800CB574 000C6474  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 800CB578 000C6478  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 800CB57C 000C647C  83 81 00 10 */	lwz r28, 0x10(r1)
/* 800CB580 000C6480  7C 08 03 A6 */	mtlr r0
/* 800CB584 000C6484  38 21 00 20 */	addi r1, r1, 0x20
/* 800CB588 000C6488  4E 80 00 20 */	blr 

.global WPADiCheckContInputs
WPADiCheckContInputs:
/* 800CB58C 000C648C  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 800CB590 000C6490  7C 08 02 A6 */	mflr r0
/* 800CB594 000C6494  90 01 00 34 */	stw r0, 0x34(r1)
/* 800CB598 000C6498  39 61 00 30 */	addi r11, r1, 0x30
/* 800CB59C 000C649C  4B FE 67 9D */	bl _savegpr_24
/* 800CB5A0 000C64A0  3F E0 80 41 */	lis r31, _wpdcb@ha
/* 800CB5A4 000C64A4  54 7E 10 3A */	slwi r30, r3, 2
/* 800CB5A8 000C64A8  3B FF F6 30 */	addi r31, r31, _wpdcb@l
/* 800CB5AC 000C64AC  7C 7B 1B 78 */	mr r27, r3
/* 800CB5B0 000C64B0  7F BF F0 2E */	lwzx r29, r31, r30
/* 800CB5B4 000C64B4  3B 80 00 00 */	li r28, 0
/* 800CB5B8 000C64B8  80 1D 08 BC */	lwz r0, 0x8bc(r29)
/* 800CB5BC 000C64BC  2C 00 FF FF */	cmpwi r0, -1
/* 800CB5C0 000C64C0  41 82 01 38 */	beq lbl_800CB6F8
/* 800CB5C4 000C64C4  48 02 62 FD */	bl OSDisableInterrupts
/* 800CB5C8 000C64C8  88 1D 08 C8 */	lbz r0, 0x8c8(r29)
/* 800CB5CC 000C64CC  7C 79 1B 78 */	mr r25, r3
/* 800CB5D0 000C64D0  7F A3 EB 78 */	mr r3, r29
/* 800CB5D4 000C64D4  38 BD 00 40 */	addi r5, r29, 0x40
/* 800CB5D8 000C64D8  7C 00 00 34 */	cntlzw r0, r0
/* 800CB5DC 000C64DC  54 00 DE 3E */	rlwinm r0, r0, 0x1b, 0x18, 0x1f
/* 800CB5E0 000C64E0  1C 00 00 60 */	mulli r0, r0, 0x60
/* 800CB5E4 000C64E4  7C 9D 02 14 */	add r4, r29, r0
/* 800CB5E8 000C64E8  3B 04 00 A0 */	addi r24, r4, 0xa0
/* 800CB5EC 000C64EC  7F 04 C3 78 */	mr r4, r24
/* 800CB5F0 000C64F0  4B FF F2 E5 */	bl IsControllerDataChanged
/* 800CB5F4 000C64F4  2C 03 00 00 */	cmpwi r3, 0
/* 800CB5F8 000C64F8  7C 7A 1B 78 */	mr r26, r3
/* 800CB5FC 000C64FC  41 82 00 14 */	beq lbl_800CB610
/* 800CB600 000C6500  7F 04 C3 78 */	mr r4, r24
/* 800CB604 000C6504  38 7D 00 40 */	addi r3, r29, 0x40
/* 800CB608 000C6508  38 A0 00 60 */	li r5, 0x60
/* 800CB60C 000C650C  4B F3 89 F5 */	bl memcpy
lbl_800CB610:
/* 800CB610 000C6510  88 1D 00 69 */	lbz r0, 0x69(r29)
/* 800CB614 000C6514  7C 00 07 75 */	extsb. r0, r0
/* 800CB618 000C6518  41 82 00 14 */	beq lbl_800CB62C
/* 800CB61C 000C651C  38 7D 00 40 */	addi r3, r29, 0x40
/* 800CB620 000C6520  38 80 00 00 */	li r4, 0
/* 800CB624 000C6524  38 A0 00 60 */	li r5, 0x60
/* 800CB628 000C6528  4B F3 8A DD */	bl memset
lbl_800CB62C:
/* 800CB62C 000C652C  7F 23 CB 78 */	mr r3, r25
/* 800CB630 000C6530  48 02 62 B9 */	bl OSRestoreInterrupts
/* 800CB634 000C6534  7F 63 DB 78 */	mr r3, r27
/* 800CB638 000C6538  4B FF FE 49 */	bl CheckButtonCombination
/* 800CB63C 000C653C  2C 1A 00 00 */	cmpwi r26, 0
/* 800CB640 000C6540  41 82 00 18 */	beq lbl_800CB658
/* 800CB644 000C6544  3B 80 00 01 */	li r28, 1
/* 800CB648 000C6548  48 02 9F DD */	bl __OSGetSystemTime
/* 800CB64C 000C654C  90 9D 08 F4 */	stw r4, 0x8f4(r29)
/* 800CB650 000C6550  90 7D 08 F0 */	stw r3, 0x8f0(r29)
/* 800CB654 000C6554  48 00 00 98 */	b lbl_800CB6EC
lbl_800CB658:
/* 800CB658 000C6558  88 0D 9A 7A */	lbz r0, _sleepTime-_SDA_BASE_(r13)
/* 800CB65C 000C655C  2C 00 00 00 */	cmpwi r0, 0
/* 800CB660 000C6560  41 82 00 8C */	beq lbl_800CB6EC
/* 800CB664 000C6564  48 02 9F C1 */	bl __OSGetSystemTime
/* 800CB668 000C6568  80 DD 08 F4 */	lwz r6, 0x8f4(r29)
/* 800CB66C 000C656C  3C A0 80 00 */	lis r5, 0x800000F8@ha
/* 800CB670 000C6570  80 05 00 F8 */	lwz r0, 0x800000F8@l(r5)
/* 800CB674 000C6574  38 A0 00 00 */	li r5, 0
/* 800CB678 000C6578  7C 86 20 10 */	subfc r4, r6, r4
/* 800CB67C 000C657C  80 FD 08 F0 */	lwz r7, 0x8f0(r29)
/* 800CB680 000C6580  54 06 F0 BE */	srwi r6, r0, 2
/* 800CB684 000C6584  7C 67 19 10 */	subfe r3, r7, r3
/* 800CB688 000C6588  4B FE 68 0D */	bl __div2i
/* 800CB68C 000C658C  88 0D 9A 7A */	lbz r0, _sleepTime-_SDA_BASE_(r13)
/* 800CB690 000C6590  1C 00 00 3C */	mulli r0, r0, 0x3c
/* 800CB694 000C6594  7C 04 00 00 */	cmpw r4, r0
/* 800CB698 000C6598  40 81 00 54 */	ble lbl_800CB6EC
/* 800CB69C 000C659C  7F BF F0 2E */	lwzx r29, r31, r30
/* 800CB6A0 000C65A0  48 02 62 21 */	bl OSDisableInterrupts
/* 800CB6A4 000C65A4  83 5D 08 BC */	lwz r26, 0x8bc(r29)
/* 800CB6A8 000C65A8  48 02 62 41 */	bl OSRestoreInterrupts
/* 800CB6AC 000C65AC  2C 1A FF FF */	cmpwi r26, -1
/* 800CB6B0 000C65B0  41 82 00 3C */	beq lbl_800CB6EC
/* 800CB6B4 000C65B4  48 02 62 0D */	bl OSDisableInterrupts
/* 800CB6B8 000C65B8  88 1D 09 86 */	lbz r0, 0x986(r29)
/* 800CB6BC 000C65BC  2C 00 00 00 */	cmpwi r0, 0
/* 800CB6C0 000C65C0  41 82 00 0C */	beq lbl_800CB6CC
/* 800CB6C4 000C65C4  48 02 62 25 */	bl OSRestoreInterrupts
/* 800CB6C8 000C65C8  48 00 00 24 */	b lbl_800CB6EC
lbl_800CB6CC:
/* 800CB6CC 000C65CC  38 00 00 01 */	li r0, 1
/* 800CB6D0 000C65D0  98 1D 09 86 */	stb r0, 0x986(r29)
/* 800CB6D4 000C65D4  48 02 62 15 */	bl OSRestoreInterrupts
/* 800CB6D8 000C65D8  3C A0 80 0D */	lis r5, CloseCallback@ha
/* 800CB6DC 000C65DC  7F 63 DB 78 */	mr r3, r27
/* 800CB6E0 000C65E0  38 A5 D5 20 */	addi r5, r5, CloseCallback@l
/* 800CB6E4 000C65E4  38 80 00 00 */	li r4, 0
/* 800CB6E8 000C65E8  48 00 25 85 */	bl WPADControlLed
lbl_800CB6EC:
/* 800CB6EC 000C65EC  2C 1C 00 00 */	cmpwi r28, 0
/* 800CB6F0 000C65F0  41 82 00 08 */	beq lbl_800CB6F8
/* 800CB6F4 000C65F4  48 03 12 A1 */	bl __VIResetRFIdle
lbl_800CB6F8:
/* 800CB6F8 000C65F8  39 61 00 30 */	addi r11, r1, 0x30
/* 800CB6FC 000C65FC  4B FE 66 89 */	bl _restgpr_24
/* 800CB700 000C6600  80 01 00 34 */	lwz r0, 0x34(r1)
/* 800CB704 000C6604  7C 08 03 A6 */	mtlr r0
/* 800CB708 000C6608  38 21 00 30 */	addi r1, r1, 0x30
/* 800CB70C 000C660C  4E 80 00 20 */	blr 

.global WPADiManageHandler
WPADiManageHandler:
/* 800CB710 000C6610  94 21 FE A0 */	stwu r1, -0x160(r1)
/* 800CB714 000C6614  7C 08 02 A6 */	mflr r0
/* 800CB718 000C6618  90 01 01 64 */	stw r0, 0x164(r1)
/* 800CB71C 000C661C  39 61 01 60 */	addi r11, r1, 0x160
/* 800CB720 000C6620  4B FE 66 09 */	bl _savegpr_20
/* 800CB724 000C6624  48 03 50 35 */	bl WUDGetStatus
/* 800CB728 000C6628  2C 03 00 03 */	cmpwi r3, 3
/* 800CB72C 000C662C  41 82 00 3C */	beq lbl_800CB768
/* 800CB730 000C6630  2C 03 00 02 */	cmpwi r3, 2
/* 800CB734 000C6634  40 82 06 EC */	bne lbl_800CBE20
/* 800CB738 000C6638  80 0D 9A 60 */	lwz r0, lbl_804BEDE0-_SDA_BASE_(r13)
/* 800CB73C 000C663C  2C 00 00 00 */	cmpwi r0, 0
/* 800CB740 000C6640  40 82 06 E0 */	bne lbl_800CBE20
/* 800CB744 000C6644  38 00 00 01 */	li r0, 1
/* 800CB748 000C6648  3C 60 80 0D */	lis r3, WPADiConnCallback@ha
/* 800CB74C 000C664C  90 0D 9A 60 */	stw r0, lbl_804BEDE0-_SDA_BASE_(r13)
/* 800CB750 000C6650  38 63 CF 98 */	addi r3, r3, WPADiConnCallback@l
/* 800CB754 000C6654  48 03 56 F9 */	bl WUDSetHidConnCallback
/* 800CB758 000C6658  3C 60 80 0D */	lis r3, WPADiRecvCallback@ha
/* 800CB75C 000C665C  38 63 D3 DC */	addi r3, r3, WPADiRecvCallback@l
/* 800CB760 000C6660  48 03 56 91 */	bl WUDSetHidRecvCallback
/* 800CB764 000C6664  48 00 06 BC */	b lbl_800CBE20
lbl_800CB768:
/* 800CB768 000C6668  3F 20 80 41 */	lis r25, _wpdcb@ha
/* 800CB76C 000C666C  3A E0 00 00 */	li r23, 0
/* 800CB770 000C6670  3B 39 F6 30 */	addi r25, r25, _wpdcb@l
/* 800CB774 000C6674  3B 4D 9A 58 */	addi r26, r13, lbl_804BEDD8-_SDA_BASE_
/* 800CB778 000C6678  3B 0D 9A 5C */	addi r24, r13, lbl_804BEDDC-_SDA_BASE_
/* 800CB77C 000C667C  3B A0 00 00 */	li r29, 0
/* 800CB780 000C6680  3B C0 00 10 */	li r30, 0x10
/* 800CB784 000C6684  3B E0 00 01 */	li r31, 1
lbl_800CB788:
/* 800CB788 000C6688  88 1A 00 00 */	lbz r0, 0(r26)
/* 800CB78C 000C668C  3A C0 00 00 */	li r22, 0
/* 800CB790 000C6690  28 00 00 05 */	cmplwi r0, 5
/* 800CB794 000C6694  40 82 01 CC */	bne lbl_800CB960
/* 800CB798 000C6698  83 79 00 00 */	lwz r27, 0(r25)
/* 800CB79C 000C669C  80 1B 08 D8 */	lwz r0, 0x8d8(r27)
/* 800CB7A0 000C66A0  2C 00 00 00 */	cmpwi r0, 0
/* 800CB7A4 000C66A4  41 82 01 AC */	beq lbl_800CB950
/* 800CB7A8 000C66A8  48 02 61 19 */	bl OSDisableInterrupts
/* 800CB7AC 000C66AC  7C 7C 1B 78 */	mr r28, r3
/* 800CB7B0 000C66B0  48 02 61 11 */	bl OSDisableInterrupts
/* 800CB7B4 000C66B4  88 9B 05 EC */	lbz r4, 0x5ec(r27)
/* 800CB7B8 000C66B8  88 1B 05 ED */	lbz r0, 0x5ed(r27)
/* 800CB7BC 000C66BC  7C 04 00 50 */	subf r0, r4, r0
/* 800CB7C0 000C66C0  7C 14 07 75 */	extsb. r20, r0
/* 800CB7C4 000C66C4  40 80 00 10 */	bge lbl_800CB7D4
/* 800CB7C8 000C66C8  80 1B 05 F4 */	lwz r0, 0x5f4(r27)
/* 800CB7CC 000C66CC  7C 14 02 14 */	add r0, r20, r0
/* 800CB7D0 000C66D0  7C 14 07 74 */	extsb r20, r0
lbl_800CB7D4:
/* 800CB7D4 000C66D4  48 02 61 15 */	bl OSRestoreInterrupts
/* 800CB7D8 000C66D8  2C 14 00 00 */	cmpwi r20, 0
/* 800CB7DC 000C66DC  40 82 00 14 */	bne lbl_800CB7F0
/* 800CB7E0 000C66E0  7F 83 E3 78 */	mr r3, r28
/* 800CB7E4 000C66E4  48 02 61 05 */	bl OSRestoreInterrupts
/* 800CB7E8 000C66E8  38 00 00 00 */	li r0, 0
/* 800CB7EC 000C66EC  48 00 00 30 */	b lbl_800CB81C
lbl_800CB7F0:
/* 800CB7F0 000C66F0  88 1B 05 EC */	lbz r0, 0x5ec(r27)
/* 800CB7F4 000C66F4  38 61 00 C8 */	addi r3, r1, 0xc8
/* 800CB7F8 000C66F8  80 9B 05 F0 */	lwz r4, 0x5f0(r27)
/* 800CB7FC 000C66FC  38 A0 00 30 */	li r5, 0x30
/* 800CB800 000C6700  7C 00 07 74 */	extsb r0, r0
/* 800CB804 000C6704  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CB808 000C6708  7C 84 02 14 */	add r4, r4, r0
/* 800CB80C 000C670C  4B F3 87 F5 */	bl memcpy
/* 800CB810 000C6710  7F 83 E3 78 */	mr r3, r28
/* 800CB814 000C6714  48 02 60 D5 */	bl OSRestoreInterrupts
/* 800CB818 000C6718  38 00 00 01 */	li r0, 1
lbl_800CB81C:
/* 800CB81C 000C671C  2C 00 00 00 */	cmpwi r0, 0
/* 800CB820 000C6720  41 82 01 30 */	beq lbl_800CB950
/* 800CB824 000C6724  80 01 00 C8 */	lwz r0, 0xc8(r1)
/* 800CB828 000C6728  28 00 00 12 */	cmplwi r0, 0x12
/* 800CB82C 000C672C  41 82 00 10 */	beq lbl_800CB83C
/* 800CB830 000C6730  80 1B 08 40 */	lwz r0, 0x840(r27)
/* 800CB834 000C6734  2C 00 00 00 */	cmpwi r0, 0
/* 800CB838 000C6738  41 82 01 18 */	beq lbl_800CB950
lbl_800CB83C:
/* 800CB83C 000C673C  82 C1 00 C8 */	lwz r22, 0xc8(r1)
/* 800CB840 000C6740  7E E3 BB 78 */	mr r3, r23
/* 800CB844 000C6744  82 A1 00 CC */	lwz r21, 0xcc(r1)
/* 800CB848 000C6748  38 81 00 F8 */	addi r4, r1, 0xf8
/* 800CB84C 000C674C  82 81 00 D0 */	lwz r20, 0xd0(r1)
/* 800CB850 000C6750  81 81 00 D4 */	lwz r12, 0xd4(r1)
/* 800CB854 000C6754  81 61 00 D8 */	lwz r11, 0xd8(r1)
/* 800CB858 000C6758  81 41 00 DC */	lwz r10, 0xdc(r1)
/* 800CB85C 000C675C  81 21 00 E0 */	lwz r9, 0xe0(r1)
/* 800CB860 000C6760  81 01 00 E4 */	lwz r8, 0xe4(r1)
/* 800CB864 000C6764  80 E1 00 E8 */	lwz r7, 0xe8(r1)
/* 800CB868 000C6768  80 C1 00 EC */	lwz r6, 0xec(r1)
/* 800CB86C 000C676C  80 A1 00 F0 */	lwz r5, 0xf0(r1)
/* 800CB870 000C6770  80 01 00 F4 */	lwz r0, 0xf4(r1)
/* 800CB874 000C6774  92 C1 00 F8 */	stw r22, 0xf8(r1)
/* 800CB878 000C6778  92 A1 00 FC */	stw r21, 0xfc(r1)
/* 800CB87C 000C677C  92 81 01 00 */	stw r20, 0x100(r1)
/* 800CB880 000C6780  91 81 01 04 */	stw r12, 0x104(r1)
/* 800CB884 000C6784  91 61 01 08 */	stw r11, 0x108(r1)
/* 800CB888 000C6788  91 41 01 0C */	stw r10, 0x10c(r1)
/* 800CB88C 000C678C  91 21 01 10 */	stw r9, 0x110(r1)
/* 800CB890 000C6790  91 01 01 14 */	stw r8, 0x114(r1)
/* 800CB894 000C6794  90 E1 01 18 */	stw r7, 0x118(r1)
/* 800CB898 000C6798  90 C1 01 1C */	stw r6, 0x11c(r1)
/* 800CB89C 000C679C  90 A1 01 20 */	stw r5, 0x120(r1)
/* 800CB8A0 000C67A0  90 01 01 24 */	stw r0, 0x124(r1)
/* 800CB8A4 000C67A4  4B FF ED 51 */	bl WPADiSendData
/* 800CB8A8 000C67A8  2C 03 00 00 */	cmpwi r3, 0
/* 800CB8AC 000C67AC  40 82 00 A4 */	bne lbl_800CB950
/* 800CB8B0 000C67B0  48 02 60 11 */	bl OSDisableInterrupts
/* 800CB8B4 000C67B4  7C 7C 1B 78 */	mr r28, r3
/* 800CB8B8 000C67B8  48 02 60 09 */	bl OSDisableInterrupts
/* 800CB8BC 000C67BC  88 9B 05 EC */	lbz r4, 0x5ec(r27)
/* 800CB8C0 000C67C0  88 1B 05 ED */	lbz r0, 0x5ed(r27)
/* 800CB8C4 000C67C4  7C 04 00 50 */	subf r0, r4, r0
/* 800CB8C8 000C67C8  7C 14 07 75 */	extsb. r20, r0
/* 800CB8CC 000C67CC  40 80 00 10 */	bge lbl_800CB8DC
/* 800CB8D0 000C67D0  80 1B 05 F4 */	lwz r0, 0x5f4(r27)
/* 800CB8D4 000C67D4  7C 14 02 14 */	add r0, r20, r0
/* 800CB8D8 000C67D8  7C 14 07 74 */	extsb r20, r0
lbl_800CB8DC:
/* 800CB8DC 000C67DC  48 02 60 0D */	bl OSRestoreInterrupts
/* 800CB8E0 000C67E0  2C 14 00 00 */	cmpwi r20, 0
/* 800CB8E4 000C67E4  40 82 00 10 */	bne lbl_800CB8F4
/* 800CB8E8 000C67E8  7F 83 E3 78 */	mr r3, r28
/* 800CB8EC 000C67EC  48 02 5F FD */	bl OSRestoreInterrupts
/* 800CB8F0 000C67F0  48 00 00 58 */	b lbl_800CB948
lbl_800CB8F4:
/* 800CB8F4 000C67F4  88 1B 05 EC */	lbz r0, 0x5ec(r27)
/* 800CB8F8 000C67F8  38 80 00 00 */	li r4, 0
/* 800CB8FC 000C67FC  80 7B 05 F0 */	lwz r3, 0x5f0(r27)
/* 800CB900 000C6800  38 A0 00 30 */	li r5, 0x30
/* 800CB904 000C6804  7C 00 07 74 */	extsb r0, r0
/* 800CB908 000C6808  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CB90C 000C680C  7C 63 02 14 */	add r3, r3, r0
/* 800CB910 000C6810  4B F3 87 F5 */	bl memset
/* 800CB914 000C6814  88 1B 05 EC */	lbz r0, 0x5ec(r27)
/* 800CB918 000C6818  7F 83 E3 78 */	mr r3, r28
/* 800CB91C 000C681C  80 9B 05 F4 */	lwz r4, 0x5f4(r27)
/* 800CB920 000C6820  7C 06 07 74 */	extsb r6, r0
/* 800CB924 000C6824  38 84 FF FF */	addi r4, r4, -1
/* 800CB928 000C6828  7C A4 30 50 */	subf r5, r4, r6
/* 800CB92C 000C682C  38 06 00 01 */	addi r0, r6, 1
/* 800CB930 000C6830  7C 86 20 50 */	subf r4, r6, r4
/* 800CB934 000C6834  7C A4 20 F8 */	nor r4, r5, r4
/* 800CB938 000C6838  7C 84 FE 70 */	srawi r4, r4, 0x1f
/* 800CB93C 000C683C  7C 00 20 78 */	andc r0, r0, r4
/* 800CB940 000C6840  98 1B 05 EC */	stb r0, 0x5ec(r27)
/* 800CB944 000C6844  48 02 5F A5 */	bl OSRestoreInterrupts
lbl_800CB948:
/* 800CB948 000C6848  3A C0 00 01 */	li r22, 1
/* 800CB94C 000C684C  48 00 00 08 */	b lbl_800CB954
lbl_800CB950:
/* 800CB950 000C6850  3A C0 00 00 */	li r22, 0
lbl_800CB954:
/* 800CB954 000C6854  2C 16 00 00 */	cmpwi r22, 0
/* 800CB958 000C6858  41 82 00 08 */	beq lbl_800CB960
/* 800CB95C 000C685C  9B BA 00 00 */	stb r29, 0(r26)
lbl_800CB960:
/* 800CB960 000C6860  2C 16 00 00 */	cmpwi r22, 0
/* 800CB964 000C6864  40 82 01 AC */	bne lbl_800CBB10
/* 800CB968 000C6868  83 99 00 00 */	lwz r28, 0(r25)
/* 800CB96C 000C686C  80 1C 08 D8 */	lwz r0, 0x8d8(r28)
/* 800CB970 000C6870  2C 00 00 00 */	cmpwi r0, 0
/* 800CB974 000C6874  41 82 01 94 */	beq lbl_800CBB08
/* 800CB978 000C6878  48 02 5F 49 */	bl OSDisableInterrupts
/* 800CB97C 000C687C  7C 7B 1B 78 */	mr r27, r3
/* 800CB980 000C6880  48 02 5F 41 */	bl OSDisableInterrupts
/* 800CB984 000C6884  88 9C 01 60 */	lbz r4, 0x160(r28)
/* 800CB988 000C6888  88 1C 01 61 */	lbz r0, 0x161(r28)
/* 800CB98C 000C688C  7C 04 00 50 */	subf r0, r4, r0
/* 800CB990 000C6890  7C 14 07 75 */	extsb. r20, r0
/* 800CB994 000C6894  40 80 00 10 */	bge lbl_800CB9A4
/* 800CB998 000C6898  80 1C 01 68 */	lwz r0, 0x168(r28)
/* 800CB99C 000C689C  7C 14 02 14 */	add r0, r20, r0
/* 800CB9A0 000C68A0  7C 14 07 74 */	extsb r20, r0
lbl_800CB9A4:
/* 800CB9A4 000C68A4  48 02 5F 45 */	bl OSRestoreInterrupts
/* 800CB9A8 000C68A8  2C 14 00 00 */	cmpwi r20, 0
/* 800CB9AC 000C68AC  40 82 00 14 */	bne lbl_800CB9C0
/* 800CB9B0 000C68B0  7F 63 DB 78 */	mr r3, r27
/* 800CB9B4 000C68B4  48 02 5F 35 */	bl OSRestoreInterrupts
/* 800CB9B8 000C68B8  38 00 00 00 */	li r0, 0
/* 800CB9BC 000C68BC  48 00 00 30 */	b lbl_800CB9EC
lbl_800CB9C0:
/* 800CB9C0 000C68C0  88 1C 01 60 */	lbz r0, 0x160(r28)
/* 800CB9C4 000C68C4  38 61 00 68 */	addi r3, r1, 0x68
/* 800CB9C8 000C68C8  80 9C 01 64 */	lwz r4, 0x164(r28)
/* 800CB9CC 000C68CC  38 A0 00 30 */	li r5, 0x30
/* 800CB9D0 000C68D0  7C 00 07 74 */	extsb r0, r0
/* 800CB9D4 000C68D4  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CB9D8 000C68D8  7C 84 02 14 */	add r4, r4, r0
/* 800CB9DC 000C68DC  4B F3 86 25 */	bl memcpy
/* 800CB9E0 000C68E0  7F 63 DB 78 */	mr r3, r27
/* 800CB9E4 000C68E4  48 02 5F 05 */	bl OSRestoreInterrupts
/* 800CB9E8 000C68E8  38 00 00 01 */	li r0, 1
lbl_800CB9EC:
/* 800CB9EC 000C68EC  2C 00 00 00 */	cmpwi r0, 0
/* 800CB9F0 000C68F0  41 82 01 18 */	beq lbl_800CBB08
/* 800CB9F4 000C68F4  82 81 00 68 */	lwz r20, 0x68(r1)
/* 800CB9F8 000C68F8  7E E3 BB 78 */	mr r3, r23
/* 800CB9FC 000C68FC  82 A1 00 6C */	lwz r21, 0x6c(r1)
/* 800CBA00 000C6900  38 81 00 98 */	addi r4, r1, 0x98
/* 800CBA04 000C6904  83 61 00 70 */	lwz r27, 0x70(r1)
/* 800CBA08 000C6908  81 81 00 74 */	lwz r12, 0x74(r1)
/* 800CBA0C 000C690C  81 61 00 78 */	lwz r11, 0x78(r1)
/* 800CBA10 000C6910  81 41 00 7C */	lwz r10, 0x7c(r1)
/* 800CBA14 000C6914  81 21 00 80 */	lwz r9, 0x80(r1)
/* 800CBA18 000C6918  81 01 00 84 */	lwz r8, 0x84(r1)
/* 800CBA1C 000C691C  80 E1 00 88 */	lwz r7, 0x88(r1)
/* 800CBA20 000C6920  80 C1 00 8C */	lwz r6, 0x8c(r1)
/* 800CBA24 000C6924  80 A1 00 90 */	lwz r5, 0x90(r1)
/* 800CBA28 000C6928  80 01 00 94 */	lwz r0, 0x94(r1)
/* 800CBA2C 000C692C  92 81 00 98 */	stw r20, 0x98(r1)
/* 800CBA30 000C6930  92 A1 00 9C */	stw r21, 0x9c(r1)
/* 800CBA34 000C6934  93 61 00 A0 */	stw r27, 0xa0(r1)
/* 800CBA38 000C6938  91 81 00 A4 */	stw r12, 0xa4(r1)
/* 800CBA3C 000C693C  91 61 00 A8 */	stw r11, 0xa8(r1)
/* 800CBA40 000C6940  91 41 00 AC */	stw r10, 0xac(r1)
/* 800CBA44 000C6944  91 21 00 B0 */	stw r9, 0xb0(r1)
/* 800CBA48 000C6948  91 01 00 B4 */	stw r8, 0xb4(r1)
/* 800CBA4C 000C694C  90 E1 00 B8 */	stw r7, 0xb8(r1)
/* 800CBA50 000C6950  90 C1 00 BC */	stw r6, 0xbc(r1)
/* 800CBA54 000C6954  90 A1 00 C0 */	stw r5, 0xc0(r1)
/* 800CBA58 000C6958  90 01 00 C4 */	stw r0, 0xc4(r1)
/* 800CBA5C 000C695C  4B FF EB 99 */	bl WPADiSendData
/* 800CBA60 000C6960  2C 03 00 00 */	cmpwi r3, 0
/* 800CBA64 000C6964  40 82 00 A4 */	bne lbl_800CBB08
/* 800CBA68 000C6968  48 02 5E 59 */	bl OSDisableInterrupts
/* 800CBA6C 000C696C  7C 7B 1B 78 */	mr r27, r3
/* 800CBA70 000C6970  48 02 5E 51 */	bl OSDisableInterrupts
/* 800CBA74 000C6974  88 9C 01 60 */	lbz r4, 0x160(r28)
/* 800CBA78 000C6978  88 1C 01 61 */	lbz r0, 0x161(r28)
/* 800CBA7C 000C697C  7C 04 00 50 */	subf r0, r4, r0
/* 800CBA80 000C6980  7C 14 07 75 */	extsb. r20, r0
/* 800CBA84 000C6984  40 80 00 10 */	bge lbl_800CBA94
/* 800CBA88 000C6988  80 1C 01 68 */	lwz r0, 0x168(r28)
/* 800CBA8C 000C698C  7C 14 02 14 */	add r0, r20, r0
/* 800CBA90 000C6990  7C 14 07 74 */	extsb r20, r0
lbl_800CBA94:
/* 800CBA94 000C6994  48 02 5E 55 */	bl OSRestoreInterrupts
/* 800CBA98 000C6998  2C 14 00 00 */	cmpwi r20, 0
/* 800CBA9C 000C699C  40 82 00 10 */	bne lbl_800CBAAC
/* 800CBAA0 000C69A0  7F 63 DB 78 */	mr r3, r27
/* 800CBAA4 000C69A4  48 02 5E 45 */	bl OSRestoreInterrupts
/* 800CBAA8 000C69A8  48 00 00 58 */	b lbl_800CBB00
lbl_800CBAAC:
/* 800CBAAC 000C69AC  88 1C 01 60 */	lbz r0, 0x160(r28)
/* 800CBAB0 000C69B0  38 80 00 00 */	li r4, 0
/* 800CBAB4 000C69B4  80 7C 01 64 */	lwz r3, 0x164(r28)
/* 800CBAB8 000C69B8  38 A0 00 30 */	li r5, 0x30
/* 800CBABC 000C69BC  7C 00 07 74 */	extsb r0, r0
/* 800CBAC0 000C69C0  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CBAC4 000C69C4  7C 63 02 14 */	add r3, r3, r0
/* 800CBAC8 000C69C8  4B F3 86 3D */	bl memset
/* 800CBACC 000C69CC  88 1C 01 60 */	lbz r0, 0x160(r28)
/* 800CBAD0 000C69D0  7F 63 DB 78 */	mr r3, r27
/* 800CBAD4 000C69D4  80 9C 01 68 */	lwz r4, 0x168(r28)
/* 800CBAD8 000C69D8  7C 06 07 74 */	extsb r6, r0
/* 800CBADC 000C69DC  38 84 FF FF */	addi r4, r4, -1
/* 800CBAE0 000C69E0  7C A4 30 50 */	subf r5, r4, r6
/* 800CBAE4 000C69E4  38 06 00 01 */	addi r0, r6, 1
/* 800CBAE8 000C69E8  7C 86 20 50 */	subf r4, r6, r4
/* 800CBAEC 000C69EC  7C A4 20 F8 */	nor r4, r5, r4
/* 800CBAF0 000C69F0  7C 84 FE 70 */	srawi r4, r4, 0x1f
/* 800CBAF4 000C69F4  7C 00 20 78 */	andc r0, r0, r4
/* 800CBAF8 000C69F8  98 1C 01 60 */	stb r0, 0x160(r28)
/* 800CBAFC 000C69FC  48 02 5D ED */	bl OSRestoreInterrupts
lbl_800CBB00:
/* 800CBB00 000C6A00  38 00 00 01 */	li r0, 1
/* 800CBB04 000C6A04  48 00 00 08 */	b lbl_800CBB0C
lbl_800CBB08:
/* 800CBB08 000C6A08  38 00 00 00 */	li r0, 0
lbl_800CBB0C:
/* 800CBB0C 000C6A0C  7E D6 03 78 */	or r22, r22, r0
lbl_800CBB10:
/* 800CBB10 000C6A10  82 B9 00 00 */	lwz r21, 0(r25)
/* 800CBB14 000C6A14  80 15 08 BC */	lwz r0, 0x8bc(r21)
/* 800CBB18 000C6A18  2C 00 FF FF */	cmpwi r0, -1
/* 800CBB1C 000C6A1C  41 82 00 F4 */	beq lbl_800CBC10
/* 800CBB20 000C6A20  2C 16 00 01 */	cmpwi r22, 1
/* 800CBB24 000C6A24  41 82 00 34 */	beq lbl_800CBB58
/* 800CBB28 000C6A28  48 02 5D 99 */	bl OSDisableInterrupts
/* 800CBB2C 000C6A2C  88 95 01 60 */	lbz r4, 0x160(r21)
/* 800CBB30 000C6A30  88 15 01 61 */	lbz r0, 0x161(r21)
/* 800CBB34 000C6A34  7C 04 00 50 */	subf r0, r4, r0
/* 800CBB38 000C6A38  7C 14 07 75 */	extsb. r20, r0
/* 800CBB3C 000C6A3C  40 80 00 10 */	bge lbl_800CBB4C
/* 800CBB40 000C6A40  80 15 01 68 */	lwz r0, 0x168(r21)
/* 800CBB44 000C6A44  7C 14 02 14 */	add r0, r20, r0
/* 800CBB48 000C6A48  7C 14 07 74 */	extsb r20, r0
lbl_800CBB4C:
/* 800CBB4C 000C6A4C  48 02 5D 9D */	bl OSRestoreInterrupts
/* 800CBB50 000C6A50  2C 14 00 00 */	cmpwi r20, 0
/* 800CBB54 000C6A54  40 81 00 10 */	ble lbl_800CBB64
lbl_800CBB58:
/* 800CBB58 000C6A58  80 79 00 00 */	lwz r3, 0(r25)
/* 800CBB5C 000C6A5C  93 A3 08 D0 */	stw r29, 0x8d0(r3)
/* 800CBB60 000C6A60  48 00 00 8C */	b lbl_800CBBEC
lbl_800CBB64:
/* 800CBB64 000C6A64  88 18 00 00 */	lbz r0, 0(r24)
/* 800CBB68 000C6A68  28 00 00 05 */	cmplwi r0, 5
/* 800CBB6C 000C6A6C  40 82 00 80 */	bne lbl_800CBBEC
/* 800CBB70 000C6A70  B3 E1 00 22 */	sth r31, 0x22(r1)
/* 800CBB74 000C6A74  7E E3 BB 78 */	mr r3, r23
/* 800CBB78 000C6A78  80 B9 00 00 */	lwz r5, 0(r25)
/* 800CBB7C 000C6A7C  38 81 00 38 */	addi r4, r1, 0x38
/* 800CBB80 000C6A80  9B A1 00 0C */	stb r29, 0xc(r1)
/* 800CBB84 000C6A84  81 81 00 10 */	lwz r12, 0x10(r1)
/* 800CBB88 000C6A88  93 A5 08 D0 */	stw r29, 0x8d0(r5)
/* 800CBB8C 000C6A8C  82 C1 00 0C */	lwz r22, 0xc(r1)
/* 800CBB90 000C6A90  81 61 00 14 */	lwz r11, 0x14(r1)
/* 800CBB94 000C6A94  81 41 00 18 */	lwz r10, 0x18(r1)
/* 800CBB98 000C6A98  81 21 00 1C */	lwz r9, 0x1c(r1)
/* 800CBB9C 000C6A9C  81 01 00 20 */	lwz r8, 0x20(r1)
/* 800CBBA0 000C6AA0  80 E1 00 24 */	lwz r7, 0x24(r1)
/* 800CBBA4 000C6AA4  80 C1 00 28 */	lwz r6, 0x28(r1)
/* 800CBBA8 000C6AA8  80 A1 00 2C */	lwz r5, 0x2c(r1)
/* 800CBBAC 000C6AAC  80 01 00 30 */	lwz r0, 0x30(r1)
/* 800CBBB0 000C6AB0  93 C1 00 08 */	stw r30, 8(r1)
/* 800CBBB4 000C6AB4  93 A1 00 34 */	stw r29, 0x34(r1)
/* 800CBBB8 000C6AB8  93 C1 00 38 */	stw r30, 0x38(r1)
/* 800CBBBC 000C6ABC  92 C1 00 3C */	stw r22, 0x3c(r1)
/* 800CBBC0 000C6AC0  91 81 00 40 */	stw r12, 0x40(r1)
/* 800CBBC4 000C6AC4  91 61 00 44 */	stw r11, 0x44(r1)
/* 800CBBC8 000C6AC8  91 41 00 48 */	stw r10, 0x48(r1)
/* 800CBBCC 000C6ACC  91 21 00 4C */	stw r9, 0x4c(r1)
/* 800CBBD0 000C6AD0  91 01 00 50 */	stw r8, 0x50(r1)
/* 800CBBD4 000C6AD4  90 E1 00 54 */	stw r7, 0x54(r1)
/* 800CBBD8 000C6AD8  90 C1 00 58 */	stw r6, 0x58(r1)
/* 800CBBDC 000C6ADC  90 A1 00 5C */	stw r5, 0x5c(r1)
/* 800CBBE0 000C6AE0  90 01 00 60 */	stw r0, 0x60(r1)
/* 800CBBE4 000C6AE4  93 A1 00 64 */	stw r29, 0x64(r1)
/* 800CBBE8 000C6AE8  48 00 54 79 */	bl __SendData
lbl_800CBBEC:
/* 800CBBEC 000C6AEC  80 79 00 00 */	lwz r3, 0(r25)
/* 800CBBF0 000C6AF0  80 03 08 D0 */	lwz r0, 0x8d0(r3)
/* 800CBBF4 000C6AF4  2C 00 00 00 */	cmpwi r0, 0
/* 800CBBF8 000C6AF8  41 82 00 10 */	beq lbl_800CBC08
/* 800CBBFC 000C6AFC  88 78 00 00 */	lbz r3, 0(r24)
/* 800CBC00 000C6B00  38 03 00 01 */	addi r0, r3, 1
/* 800CBC04 000C6B04  48 00 00 08 */	b lbl_800CBC0C
lbl_800CBC08:
/* 800CBC08 000C6B08  38 00 00 00 */	li r0, 0
lbl_800CBC0C:
/* 800CBC0C 000C6B0C  98 18 00 00 */	stb r0, 0(r24)
lbl_800CBC10:
/* 800CBC10 000C6B10  88 0D 9A 54 */	lbz r0, _checkCnt-_SDA_BASE_(r13)
/* 800CBC14 000C6B14  28 00 00 05 */	cmplwi r0, 5
/* 800CBC18 000C6B18  40 82 00 0C */	bne lbl_800CBC24
/* 800CBC1C 000C6B1C  7E E3 BB 78 */	mr r3, r23
/* 800CBC20 000C6B20  4B FF F9 6D */	bl WPADiCheckContInputs
lbl_800CBC24:
/* 800CBC24 000C6B24  A0 0D 9A 52 */	lhz r0, _senseCnt-_SDA_BASE_(r13)
/* 800CBC28 000C6B28  28 00 00 0A */	cmplwi r0, 0xa
/* 800CBC2C 000C6B2C  40 82 00 0C */	bne lbl_800CBC38
/* 800CBC30 000C6B30  7E E3 BB 78 */	mr r3, r23
/* 800CBC34 000C6B34  4B FF EB 9D */	bl WPADiRadioSensitivity
lbl_800CBC38:
/* 800CBC38 000C6B38  88 7A 00 00 */	lbz r3, 0(r26)
/* 800CBC3C 000C6B3C  28 03 00 05 */	cmplwi r3, 5
/* 800CBC40 000C6B40  38 03 00 01 */	addi r0, r3, 1
/* 800CBC44 000C6B44  40 82 00 08 */	bne lbl_800CBC4C
/* 800CBC48 000C6B48  7C 60 1B 78 */	mr r0, r3
lbl_800CBC4C:
/* 800CBC4C 000C6B4C  3A F7 00 01 */	addi r23, r23, 1
/* 800CBC50 000C6B50  98 1A 00 00 */	stb r0, 0(r26)
/* 800CBC54 000C6B54  2C 17 00 04 */	cmpwi r23, 4
/* 800CBC58 000C6B58  3B 5A 00 01 */	addi r26, r26, 1
/* 800CBC5C 000C6B5C  3B 39 00 04 */	addi r25, r25, 4
/* 800CBC60 000C6B60  3B 18 00 01 */	addi r24, r24, 1
/* 800CBC64 000C6B64  41 80 FB 24 */	blt lbl_800CB788
/* 800CBC68 000C6B68  A0 0D 9A 56 */	lhz r0, lbl_804BEDD6-_SDA_BASE_(r13)
/* 800CBC6C 000C6B6C  28 00 EA 60 */	cmplwi r0, 0xea60
/* 800CBC70 000C6B70  40 82 00 68 */	bne lbl_800CBCD8
/* 800CBC74 000C6B74  3E C0 80 00 */	lis r22, 0x800031A2@ha
/* 800CBC78 000C6B78  38 80 00 01 */	li r4, 1
/* 800CBC7C 000C6B7C  38 76 31 A2 */	addi r3, r22, 0x800031A2@l
/* 800CBC80 000C6B80  48 02 24 85 */	bl DCInvalidateRange
/* 800CBC84 000C6B84  3C 60 80 3A */	lis r3, lbl_80399538@ha
/* 800CBC88 000C6B88  38 63 95 38 */	addi r3, r3, lbl_80399538@l
/* 800CBC8C 000C6B8C  4C C6 31 82 */	crclr 6
/* 800CBC90 000C6B90  48 00 BA CD */	bl DEBUGPrint
/* 800CBC94 000C6B94  88 6D 9A 64 */	lbz r3, _afhChannel-_SDA_BASE_(r13)
/* 800CBC98 000C6B98  88 16 31 A2 */	lbz r0, 0x31a2(r22)
/* 800CBC9C 000C6B9C  7C 63 07 74 */	extsb r3, r3
/* 800CBCA0 000C6BA0  7C 03 00 00 */	cmpw r3, r0
/* 800CBCA4 000C6BA4  41 82 00 34 */	beq lbl_800CBCD8
/* 800CBCA8 000C6BA8  48 02 5C 19 */	bl OSDisableInterrupts
/* 800CBCAC 000C6BAC  88 16 31 A2 */	lbz r0, 0x31a2(r22)
/* 800CBCB0 000C6BB0  98 0D 9A 64 */	stb r0, _afhChannel-_SDA_BASE_(r13)
/* 800CBCB4 000C6BB4  48 02 5C 35 */	bl OSRestoreInterrupts
/* 800CBCB8 000C6BB8  3C 60 80 3A */	lis r3, lbl_80399560@ha
/* 800CBCBC 000C6BBC  88 96 31 A2 */	lbz r4, 0x31a2(r22)
/* 800CBCC0 000C6BC0  38 63 95 60 */	addi r3, r3, lbl_80399560@l
/* 800CBCC4 000C6BC4  4C C6 31 82 */	crclr 6
/* 800CBCC8 000C6BC8  48 00 BA 95 */	bl DEBUGPrint
/* 800CBCCC 000C6BCC  88 0D 9A 64 */	lbz r0, _afhChannel-_SDA_BASE_(r13)
/* 800CBCD0 000C6BD0  7C 03 07 74 */	extsb r3, r0
/* 800CBCD4 000C6BD4  48 03 50 31 */	bl WUDSetDisableChannel
lbl_800CBCD8:
/* 800CBCD8 000C6BD8  A0 CD 9A 52 */	lhz r6, _senseCnt-_SDA_BASE_(r13)
/* 800CBCDC 000C6BDC  3C 60 00 01 */	lis r3, 0x0000EA60@ha
/* 800CBCE0 000C6BE0  38 03 EA 60 */	addi r0, r3, 0x0000EA60@l
/* 800CBCE4 000C6BE4  89 2D 9A 54 */	lbz r9, _checkCnt-_SDA_BASE_(r13)
/* 800CBCE8 000C6BE8  38 86 FF F6 */	addi r4, r6, -10
/* 800CBCEC 000C6BEC  20 66 00 0A */	subfic r3, r6, 0xa
/* 800CBCF0 000C6BF0  7C 83 18 F8 */	nor r3, r4, r3
/* 800CBCF4 000C6BF4  A1 4D 9A 56 */	lhz r10, lbl_804BEDD6-_SDA_BASE_(r13)
/* 800CBCF8 000C6BF8  7C 68 FE 70 */	srawi r8, r3, 0x1f
/* 800CBCFC 000C6BFC  38 E6 00 01 */	addi r7, r6, 1
/* 800CBD00 000C6C00  54 00 04 3E */	clrlwi r0, r0, 0x10
/* 800CBD04 000C6C04  38 89 FF FB */	addi r4, r9, -5
/* 800CBD08 000C6C08  20 69 00 05 */	subfic r3, r9, 5
/* 800CBD0C 000C6C0C  7C E7 40 78 */	andc r7, r7, r8
/* 800CBD10 000C6C10  7C 85 18 F8 */	nor r5, r4, r3
/* 800CBD14 000C6C14  7C 80 50 50 */	subf r4, r0, r10
/* 800CBD18 000C6C18  7C 6A 00 50 */	subf r3, r10, r0
/* 800CBD1C 000C6C1C  88 0D 9A 71 */	lbz r0, lbl_804BEDF1-_SDA_BASE_(r13)
/* 800CBD20 000C6C20  7C A6 FE 70 */	srawi r6, r5, 0x1f
/* 800CBD24 000C6C24  38 A9 00 01 */	addi r5, r9, 1
/* 800CBD28 000C6C28  7C 84 18 F8 */	nor r4, r4, r3
/* 800CBD2C 000C6C2C  38 6A 00 01 */	addi r3, r10, 1
/* 800CBD30 000C6C30  7C 84 FE 70 */	srawi r4, r4, 0x1f
/* 800CBD34 000C6C34  7C A5 30 78 */	andc r5, r5, r6
/* 800CBD38 000C6C38  7C 63 20 78 */	andc r3, r3, r4
/* 800CBD3C 000C6C3C  2C 00 00 00 */	cmpwi r0, 0
/* 800CBD40 000C6C40  B0 ED 9A 52 */	sth r7, _senseCnt-_SDA_BASE_(r13)
/* 800CBD44 000C6C44  98 AD 9A 54 */	stb r5, _checkCnt-_SDA_BASE_(r13)
/* 800CBD48 000C6C48  B0 6D 9A 56 */	sth r3, lbl_804BEDD6-_SDA_BASE_(r13)
/* 800CBD4C 000C6C4C  41 82 00 34 */	beq lbl_800CBD80
/* 800CBD50 000C6C50  48 02 B3 55 */	bl SCCheckStatus
/* 800CBD54 000C6C54  2C 03 00 00 */	cmpwi r3, 0
/* 800CBD58 000C6C58  40 82 00 28 */	bne lbl_800CBD80
/* 800CBD5C 000C6C5C  3C 60 80 43 */	lis r3, _scArray@ha
/* 800CBD60 000C6C60  38 63 99 68 */	addi r3, r3, _scArray@l
/* 800CBD64 000C6C64  48 02 CE F1 */	bl SCSetBtDeviceInfoArray
/* 800CBD68 000C6C68  2C 03 00 01 */	cmpwi r3, 1
/* 800CBD6C 000C6C6C  40 82 00 14 */	bne lbl_800CBD80
/* 800CBD70 000C6C70  38 60 00 00 */	li r3, 0
/* 800CBD74 000C6C74  48 02 C6 A1 */	bl SCFlushAsync
/* 800CBD78 000C6C78  38 00 00 00 */	li r0, 0
/* 800CBD7C 000C6C7C  98 0D 9A 71 */	stb r0, lbl_804BEDF1-_SDA_BASE_(r13)
lbl_800CBD80:
/* 800CBD80 000C6C80  88 0D 9A 66 */	lbz r0, _scSetting-_SDA_BASE_(r13)
/* 800CBD84 000C6C84  2C 00 00 00 */	cmpwi r0, 0
/* 800CBD88 000C6C88  41 82 00 94 */	beq lbl_800CBE1C
/* 800CBD8C 000C6C8C  48 02 B3 19 */	bl SCCheckStatus
/* 800CBD90 000C6C90  2C 03 00 00 */	cmpwi r3, 0
/* 800CBD94 000C6C94  40 82 00 88 */	bne lbl_800CBE1C
/* 800CBD98 000C6C98  48 02 CE C9 */	bl SCGetBtDpdSensibility
/* 800CBD9C 000C6C9C  54 60 06 3E */	clrlwi r0, r3, 0x18
/* 800CBDA0 000C6CA0  28 00 00 01 */	cmplwi r0, 1
/* 800CBDA4 000C6CA4  40 80 00 08 */	bge lbl_800CBDAC
/* 800CBDA8 000C6CA8  38 00 00 01 */	li r0, 1
lbl_800CBDAC:
/* 800CBDAC 000C6CAC  28 00 00 05 */	cmplwi r0, 5
/* 800CBDB0 000C6CB0  40 81 00 08 */	ble lbl_800CBDB8
/* 800CBDB4 000C6CB4  38 00 00 05 */	li r0, 5
lbl_800CBDB8:
/* 800CBDB8 000C6CB8  98 0D 9A 79 */	stb r0, _dpdSensitivity-_SDA_BASE_(r13)
/* 800CBDBC 000C6CBC  48 02 CF 69 */	bl SCGetWpadSensorBarPosition
/* 800CBDC0 000C6CC0  54 63 06 3E */	clrlwi r3, r3, 0x18
/* 800CBDC4 000C6CC4  38 03 FF FF */	addi r0, r3, -1
/* 800CBDC8 000C6CC8  7C 00 00 34 */	cntlzw r0, r0
/* 800CBDCC 000C6CCC  54 00 DE 3E */	rlwinm r0, r0, 0x1b, 0x18, 0x1f
/* 800CBDD0 000C6CD0  98 0D 9A 78 */	stb r0, _sensorBarPos-_SDA_BASE_(r13)
/* 800CBDD4 000C6CD4  48 02 CE F5 */	bl SCGetWpadMotorMode
/* 800CBDD8 000C6CD8  54 63 06 3E */	clrlwi r3, r3, 0x18
/* 800CBDDC 000C6CDC  38 03 FF FF */	addi r0, r3, -1
/* 800CBDE0 000C6CE0  7C 00 00 34 */	cntlzw r0, r0
/* 800CBDE4 000C6CE4  54 00 D9 7E */	srwi r0, r0, 5
/* 800CBDE8 000C6CE8  90 0D 9A 74 */	stw r0, _rumble-_SDA_BASE_(r13)
/* 800CBDEC 000C6CEC  48 02 CF 8D */	bl SCGetWpadSpeakerVolume
/* 800CBDF0 000C6CF0  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 800CBDF4 000C6CF4  7C 64 1B 78 */	mr r4, r3
/* 800CBDF8 000C6CF8  40 82 00 08 */	bne lbl_800CBE00
/* 800CBDFC 000C6CFC  38 80 00 00 */	li r4, 0
lbl_800CBE00:
/* 800CBE00 000C6D00  54 60 06 3E */	clrlwi r0, r3, 0x18
/* 800CBE04 000C6D04  28 00 00 7F */	cmplwi r0, 0x7f
/* 800CBE08 000C6D08  41 80 00 08 */	blt lbl_800CBE10
/* 800CBE0C 000C6D0C  38 80 00 7F */	li r4, 0x7f
lbl_800CBE10:
/* 800CBE10 000C6D10  38 00 00 00 */	li r0, 0
/* 800CBE14 000C6D14  98 8D 9A 72 */	stb r4, _speakerVolume-_SDA_BASE_(r13)
/* 800CBE18 000C6D18  98 0D 9A 66 */	stb r0, _scSetting-_SDA_BASE_(r13)
lbl_800CBE1C:
/* 800CBE1C 000C6D1C  48 04 82 85 */	bl func_801140A0
lbl_800CBE20:
/* 800CBE20 000C6D20  39 61 01 60 */	addi r11, r1, 0x160
/* 800CBE24 000C6D24  4B FE 5F 51 */	bl _restgpr_20
/* 800CBE28 000C6D28  80 01 01 64 */	lwz r0, 0x164(r1)
/* 800CBE2C 000C6D2C  7C 08 03 A6 */	mtlr r0
/* 800CBE30 000C6D30  38 21 01 60 */	addi r1, r1, 0x160
/* 800CBE34 000C6D34  4E 80 00 20 */	blr 

.global WPADiManageHandler0
WPADiManageHandler0:
/* 800CBE38 000C6D38  3D 00 80 41 */	lis r8, __WPADiManageHandlerStack@ha
/* 800CBE3C 000C6D3C  3C E0 80 0D */	lis r7, WPADiManageHandler@ha
/* 800CBE40 000C6D40  39 08 F6 40 */	addi r8, r8, __WPADiManageHandlerStack@l
/* 800CBE44 000C6D44  38 A0 00 00 */	li r5, 0
/* 800CBE48 000C6D48  38 E7 B7 10 */	addi r7, r7, WPADiManageHandler@l
/* 800CBE4C 000C6D4C  38 C0 00 00 */	li r6, 0
/* 800CBE50 000C6D50  39 08 10 00 */	addi r8, r8, 0x1000
/* 800CBE54 000C6D54  48 02 2D 18 */	b OSSwitchFiberEx

.global __ClearControlBlock
__ClearControlBlock:
/* 800CBE58 000C6D58  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800CBE5C 000C6D5C  7C 08 02 A6 */	mflr r0
/* 800CBE60 000C6D60  90 01 00 24 */	stw r0, 0x24(r1)
/* 800CBE64 000C6D64  39 61 00 20 */	addi r11, r1, 0x20
/* 800CBE68 000C6D68  4B FE 5E DD */	bl _savegpr_27
/* 800CBE6C 000C6D6C  3C 80 80 41 */	lis r4, _wpdcb@ha
/* 800CBE70 000C6D70  54 60 10 3A */	slwi r0, r3, 2
/* 800CBE74 000C6D74  38 84 F6 30 */	addi r4, r4, _wpdcb@l
/* 800CBE78 000C6D78  3B 80 00 00 */	li r28, 0
/* 800CBE7C 000C6D7C  7F 64 00 2E */	lwzx r27, r4, r0
/* 800CBE80 000C6D80  3B A0 FF FF */	li r29, -1
/* 800CBE84 000C6D84  38 00 00 FD */	li r0, 0xfd
/* 800CBE88 000C6D88  3B C0 00 0C */	li r30, 0xc
/* 800CBE8C 000C6D8C  9B 9B 08 C8 */	stb r28, 0x8c8(r27)
/* 800CBE90 000C6D90  7C 7F 1B 78 */	mr r31, r3
/* 800CBE94 000C6D94  93 9B 08 50 */	stw r28, 0x850(r27)
/* 800CBE98 000C6D98  93 9B 08 D4 */	stw r28, 0x8d4(r27)
/* 800CBE9C 000C6D9C  93 9B 08 9C */	stw r28, 0x89c(r27)
/* 800CBEA0 000C6DA0  93 9B 08 A0 */	stw r28, 0x8a0(r27)
/* 800CBEA4 000C6DA4  93 9B 08 A8 */	stw r28, 0x8a8(r27)
/* 800CBEA8 000C6DA8  93 9B 08 AC */	stw r28, 0x8ac(r27)
/* 800CBEAC 000C6DAC  93 9B 08 B0 */	stw r28, 0x8b0(r27)
/* 800CBEB0 000C6DB0  93 9B 08 B4 */	stw r28, 0x8b4(r27)
/* 800CBEB4 000C6DB4  93 9B 08 B8 */	stw r28, 0x8b8(r27)
/* 800CBEB8 000C6DB8  93 BB 08 BC */	stw r29, 0x8bc(r27)
/* 800CBEBC 000C6DBC  98 1B 08 C1 */	stb r0, 0x8c1(r27)
/* 800CBEC0 000C6DC0  9B 9B 08 C2 */	stb r28, 0x8c2(r27)
/* 800CBEC4 000C6DC4  9B 9B 09 11 */	stb r28, 0x911(r27)
/* 800CBEC8 000C6DC8  B3 9B 09 12 */	sth r28, 0x912(r27)
/* 800CBECC 000C6DCC  9B 9B 08 C0 */	stb r28, 0x8c0(r27)
/* 800CBED0 000C6DD0  9B DB 08 CA */	stb r30, 0x8ca(r27)
/* 800CBED4 000C6DD4  9B 9B 08 CB */	stb r28, 0x8cb(r27)
/* 800CBED8 000C6DD8  9B 9B 08 CC */	stb r28, 0x8cc(r27)
/* 800CBEDC 000C6DDC  B3 9B 08 F8 */	sth r28, 0x8f8(r27)
/* 800CBEE0 000C6DE0  B3 9B 08 FA */	sth r28, 0x8fa(r27)
/* 800CBEE4 000C6DE4  B3 9B 08 FC */	sth r28, 0x8fc(r27)
/* 800CBEE8 000C6DE8  B3 9B 08 FE */	sth r28, 0x8fe(r27)
/* 800CBEEC 000C6DEC  B3 9B 09 00 */	sth r28, 0x900(r27)
/* 800CBEF0 000C6DF0  B3 9B 09 02 */	sth r28, 0x902(r27)
/* 800CBEF4 000C6DF4  48 02 97 31 */	bl __OSGetSystemTime
/* 800CBEF8 000C6DF8  90 9B 08 F4 */	stw r4, 0x8f4(r27)
/* 800CBEFC 000C6DFC  90 7B 08 F0 */	stw r3, 0x8f0(r27)
/* 800CBF00 000C6E00  48 02 97 25 */	bl __OSGetSystemTime
/* 800CBF04 000C6E04  90 9B 09 0C */	stw r4, 0x90c(r27)
/* 800CBF08 000C6E08  38 00 00 01 */	li r0, 1
/* 800CBF0C 000C6E0C  38 80 00 00 */	li r4, 0
/* 800CBF10 000C6E10  38 A0 00 18 */	li r5, 0x18
/* 800CBF14 000C6E14  90 7B 09 08 */	stw r3, 0x908(r27)
/* 800CBF18 000C6E18  38 7B 08 38 */	addi r3, r27, 0x838
/* 800CBF1C 000C6E1C  9B 9B 09 10 */	stb r28, 0x910(r27)
/* 800CBF20 000C6E20  9B 9B 08 C9 */	stb r28, 0x8c9(r27)
/* 800CBF24 000C6E24  93 9B 08 C4 */	stw r28, 0x8c4(r27)
/* 800CBF28 000C6E28  93 9B 09 74 */	stw r28, 0x974(r27)
/* 800CBF2C 000C6E2C  93 9B 09 78 */	stw r28, 0x978(r27)
/* 800CBF30 000C6E30  B3 9B 09 80 */	sth r28, 0x980(r27)
/* 800CBF34 000C6E34  93 9B 09 7C */	stw r28, 0x97c(r27)
/* 800CBF38 000C6E38  9B BB 08 C3 */	stb r29, 0x8c3(r27)
/* 800CBF3C 000C6E3C  93 9B 08 D8 */	stw r28, 0x8d8(r27)
/* 800CBF40 000C6E40  93 9B 08 DC */	stw r28, 0x8dc(r27)
/* 800CBF44 000C6E44  93 9B 08 E0 */	stw r28, 0x8e0(r27)
/* 800CBF48 000C6E48  98 1B 08 CD */	stb r0, 0x8cd(r27)
/* 800CBF4C 000C6E4C  9B 9B 08 CE */	stb r28, 0x8ce(r27)
/* 800CBF50 000C6E50  9B 9B 08 CF */	stb r28, 0x8cf(r27)
/* 800CBF54 000C6E54  9B 9B 09 82 */	stb r28, 0x982(r27)
/* 800CBF58 000C6E58  9B 9B 09 83 */	stb r28, 0x983(r27)
/* 800CBF5C 000C6E5C  B3 9B 09 84 */	sth r28, 0x984(r27)
/* 800CBF60 000C6E60  98 1B 09 86 */	stb r0, 0x986(r27)
/* 800CBF64 000C6E64  9B 9B 09 8C */	stb r28, 0x98c(r27)
/* 800CBF68 000C6E68  93 9B 09 88 */	stw r28, 0x988(r27)
/* 800CBF6C 000C6E6C  4B F3 81 99 */	bl memset
/* 800CBF70 000C6E70  38 7B 09 34 */	addi r3, r27, 0x934
/* 800CBF74 000C6E74  38 80 00 00 */	li r4, 0
/* 800CBF78 000C6E78  38 A0 00 40 */	li r5, 0x40
/* 800CBF7C 000C6E7C  4B F3 81 89 */	bl memset
/* 800CBF80 000C6E80  38 7B 00 A0 */	addi r3, r27, 0xa0
/* 800CBF84 000C6E84  38 80 00 00 */	li r4, 0
/* 800CBF88 000C6E88  38 A0 00 C0 */	li r5, 0xc0
/* 800CBF8C 000C6E8C  4B F3 81 79 */	bl memset
/* 800CBF90 000C6E90  38 7B 00 40 */	addi r3, r27, 0x40
/* 800CBF94 000C6E94  38 80 00 00 */	li r4, 0
/* 800CBF98 000C6E98  38 A0 00 60 */	li r5, 0x60
/* 800CBF9C 000C6E9C  4B F3 81 69 */	bl memset
/* 800CBFA0 000C6EA0  38 7B 08 54 */	addi r3, r27, 0x854
/* 800CBFA4 000C6EA4  38 80 00 00 */	li r4, 0
/* 800CBFA8 000C6EA8  38 A0 00 2E */	li r5, 0x2e
/* 800CBFAC 000C6EAC  4B F3 81 59 */	bl memset
/* 800CBFB0 000C6EB0  38 7B 08 82 */	addi r3, r27, 0x882
/* 800CBFB4 000C6EB4  38 80 00 00 */	li r4, 0
/* 800CBFB8 000C6EB8  38 A0 00 1A */	li r5, 0x1a
/* 800CBFBC 000C6EBC  4B F3 81 49 */	bl memset
/* 800CBFC0 000C6EC0  38 7B 09 14 */	addi r3, r27, 0x914
/* 800CBFC4 000C6EC4  38 80 00 00 */	li r4, 0
/* 800CBFC8 000C6EC8  38 A0 00 10 */	li r5, 0x10
/* 800CBFCC 000C6ECC  4B F3 81 39 */	bl memset
/* 800CBFD0 000C6ED0  38 7B 09 24 */	addi r3, r27, 0x924
/* 800CBFD4 000C6ED4  38 80 00 00 */	li r4, 0
/* 800CBFD8 000C6ED8  38 A0 00 08 */	li r5, 8
/* 800CBFDC 000C6EDC  4B F3 81 29 */	bl memset
/* 800CBFE0 000C6EE0  38 7B 09 2C */	addi r3, r27, 0x92c
/* 800CBFE4 000C6EE4  38 80 00 00 */	li r4, 0
/* 800CBFE8 000C6EE8  38 A0 00 08 */	li r5, 8
/* 800CBFEC 000C6EEC  4B F3 81 19 */	bl memset
/* 800CBFF0 000C6EF0  7F 63 DB 78 */	mr r3, r27
/* 800CBFF4 000C6EF4  38 80 00 00 */	li r4, 0
/* 800CBFF8 000C6EF8  38 A0 00 38 */	li r5, 0x38
/* 800CBFFC 000C6EFC  4B F3 81 09 */	bl memset
/* 800CC000 000C6F00  93 BB 00 38 */	stw r29, 0x38(r27)
/* 800CC004 000C6F04  38 9B 01 6C */	addi r4, r27, 0x16c
/* 800CC008 000C6F08  38 60 00 18 */	li r3, 0x18
/* 800CC00C 000C6F0C  38 1B 05 F8 */	addi r0, r27, 0x5f8
/* 800CC010 000C6F10  93 BB 00 3C */	stw r29, 0x3c(r27)
/* 800CC014 000C6F14  90 9B 01 64 */	stw r4, 0x164(r27)
/* 800CC018 000C6F18  90 7B 01 68 */	stw r3, 0x168(r27)
/* 800CC01C 000C6F1C  90 1B 05 F0 */	stw r0, 0x5f0(r27)
/* 800CC020 000C6F20  93 DB 05 F4 */	stw r30, 0x5f4(r27)
/* 800CC024 000C6F24  48 02 58 9D */	bl OSDisableInterrupts
/* 800CC028 000C6F28  9B 9B 01 60 */	stb r28, 0x160(r27)
/* 800CC02C 000C6F2C  7C 7D 1B 78 */	mr r29, r3
/* 800CC030 000C6F30  38 80 00 00 */	li r4, 0
/* 800CC034 000C6F34  9B 9B 01 61 */	stb r28, 0x161(r27)
/* 800CC038 000C6F38  80 1B 01 68 */	lwz r0, 0x168(r27)
/* 800CC03C 000C6F3C  80 7B 01 64 */	lwz r3, 0x164(r27)
/* 800CC040 000C6F40  1C A0 00 30 */	mulli r5, r0, 0x30
/* 800CC044 000C6F44  4B F3 80 C1 */	bl memset
/* 800CC048 000C6F48  7F A3 EB 78 */	mr r3, r29
/* 800CC04C 000C6F4C  48 02 58 9D */	bl OSRestoreInterrupts
/* 800CC050 000C6F50  48 02 58 71 */	bl OSDisableInterrupts
/* 800CC054 000C6F54  9B 9B 05 EC */	stb r28, 0x5ec(r27)
/* 800CC058 000C6F58  7C 7D 1B 78 */	mr r29, r3
/* 800CC05C 000C6F5C  38 80 00 00 */	li r4, 0
/* 800CC060 000C6F60  9B 9B 05 ED */	stb r28, 0x5ed(r27)
/* 800CC064 000C6F64  80 1B 05 F4 */	lwz r0, 0x5f4(r27)
/* 800CC068 000C6F68  80 7B 05 F0 */	lwz r3, 0x5f0(r27)
/* 800CC06C 000C6F6C  1C A0 00 30 */	mulli r5, r0, 0x30
/* 800CC070 000C6F70  4B F3 80 95 */	bl memset
/* 800CC074 000C6F74  7F A3 EB 78 */	mr r3, r29
/* 800CC078 000C6F78  48 02 58 71 */	bl OSRestoreInterrupts
/* 800CC07C 000C6F7C  1C 1F 00 14 */	mulli r0, r31, 0x14
/* 800CC080 000C6F80  3C 80 80 41 */	lis r4, _wmb@ha
/* 800CC084 000C6F84  38 6D 9A 58 */	addi r3, r13, lbl_804BEDD8-_SDA_BASE_
/* 800CC088 000C6F88  38 84 2D 40 */	addi r4, r4, _wmb@l
/* 800CC08C 000C6F8C  7F 83 F9 AE */	stbx r28, r3, r31
/* 800CC090 000C6F90  38 6D 9A 5C */	addi r3, r13, lbl_804BEDDC-_SDA_BASE_
/* 800CC094 000C6F94  7F 84 01 2E */	stwx r28, r4, r0
/* 800CC098 000C6F98  7C 84 02 14 */	add r4, r4, r0
/* 800CC09C 000C6F9C  39 61 00 20 */	addi r11, r1, 0x20
/* 800CC0A0 000C6FA0  93 84 00 04 */	stw r28, 4(r4)
/* 800CC0A4 000C6FA4  B3 84 00 08 */	sth r28, 8(r4)
/* 800CC0A8 000C6FA8  93 84 00 0C */	stw r28, 0xc(r4)
/* 800CC0AC 000C6FAC  93 84 00 10 */	stw r28, 0x10(r4)
/* 800CC0B0 000C6FB0  7F 83 F9 AE */	stbx r28, r3, r31
/* 800CC0B4 000C6FB4  4B FE 5C DD */	bl _restgpr_27
/* 800CC0B8 000C6FB8  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800CC0BC 000C6FBC  7C 08 03 A6 */	mtlr r0
/* 800CC0C0 000C6FC0  38 21 00 20 */	addi r1, r1, 0x20
/* 800CC0C4 000C6FC4  4E 80 00 20 */	blr 

.global WPADiInitSub
WPADiInitSub:
/* 800CC0C8 000C6FC8  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 800CC0CC 000C6FCC  7C 08 02 A6 */	mflr r0
/* 800CC0D0 000C6FD0  90 01 00 34 */	stw r0, 0x34(r1)
/* 800CC0D4 000C6FD4  39 61 00 30 */	addi r11, r1, 0x30
/* 800CC0D8 000C6FD8  4B FE 5C 61 */	bl _savegpr_24
/* 800CC0DC 000C6FDC  3F E0 80 41 */	lis r31, _managerAlarm@ha
/* 800CC0E0 000C6FE0  3B FF F6 00 */	addi r31, r31, _managerAlarm@l
/* 800CC0E4 000C6FE4  48 02 57 DD */	bl OSDisableInterrupts
/* 800CC0E8 000C6FE8  3C 80 CD 00 */	lis r4, 0xCD0000C0@ha
/* 800CC0EC 000C6FEC  80 04 00 C0 */	lwz r0, 0xCD0000C0@l(r4)
/* 800CC0F0 000C6FF0  60 00 01 00 */	ori r0, r0, 0x100
/* 800CC0F4 000C6FF4  90 04 00 C0 */	stw r0, 0xc0(r4)
/* 800CC0F8 000C6FF8  48 02 57 F1 */	bl OSRestoreInterrupts
/* 800CC0FC 000C6FFC  38 9F 10 40 */	addi r4, r31, 0x1040
/* 800CC100 000C7000  38 00 FF FF */	li r0, -1
/* 800CC104 000C7004  98 04 00 00 */	stb r0, 0(r4)
/* 800CC108 000C7008  3C 60 80 3A */	lis r3, lbl_80399578@ha
/* 800CC10C 000C700C  38 63 95 78 */	addi r3, r3, lbl_80399578@l
/* 800CC110 000C7010  98 04 00 01 */	stb r0, 1(r4)
/* 800CC114 000C7014  98 04 00 02 */	stb r0, 2(r4)
/* 800CC118 000C7018  98 04 00 03 */	stb r0, 3(r4)
/* 800CC11C 000C701C  98 04 00 04 */	stb r0, 4(r4)
/* 800CC120 000C7020  98 04 00 05 */	stb r0, 5(r4)
/* 800CC124 000C7024  98 04 00 06 */	stb r0, 6(r4)
/* 800CC128 000C7028  98 04 00 07 */	stb r0, 7(r4)
/* 800CC12C 000C702C  98 04 00 08 */	stb r0, 8(r4)
/* 800CC130 000C7030  98 04 00 09 */	stb r0, 9(r4)
/* 800CC134 000C7034  98 04 00 0A */	stb r0, 0xa(r4)
/* 800CC138 000C7038  98 04 00 0B */	stb r0, 0xb(r4)
/* 800CC13C 000C703C  98 04 00 0C */	stb r0, 0xc(r4)
/* 800CC140 000C7040  98 04 00 0D */	stb r0, 0xd(r4)
/* 800CC144 000C7044  98 04 00 0E */	stb r0, 0xe(r4)
/* 800CC148 000C7048  98 04 00 0F */	stb r0, 0xf(r4)
/* 800CC14C 000C704C  4C C6 31 82 */	crclr 6
/* 800CC150 000C7050  48 00 B6 0D */	bl DEBUGPrint
/* 800CC154 000C7054  3B BF 10 60 */	addi r29, r31, 0x1060
/* 800CC158 000C7058  3B 9F 00 30 */	addi r28, r31, 0x30
/* 800CC15C 000C705C  3B 00 00 00 */	li r24, 0
/* 800CC160 000C7060  3B 6D 9A 68 */	addi r27, r13, _chan_active_state-_SDA_BASE_
/* 800CC164 000C7064  3B 4D 9A 58 */	addi r26, r13, lbl_804BEDD8-_SDA_BASE_
/* 800CC168 000C7068  3B 2D 9A 5C */	addi r25, r13, lbl_804BEDDC-_SDA_BASE_
/* 800CC16C 000C706C  3B C0 00 00 */	li r30, 0
lbl_800CC170:
/* 800CC170 000C7070  93 BC 00 00 */	stw r29, 0(r28)
/* 800CC174 000C7074  7F 03 C3 78 */	mr r3, r24
/* 800CC178 000C7078  9B DB 00 00 */	stb r30, 0(r27)
/* 800CC17C 000C707C  80 9C 00 00 */	lwz r4, 0(r28)
/* 800CC180 000C7080  93 C4 08 A4 */	stw r30, 0x8a4(r4)
/* 800CC184 000C7084  4B FF FC D5 */	bl __ClearControlBlock
/* 800CC188 000C7088  38 7D 08 E4 */	addi r3, r29, 0x8e4
/* 800CC18C 000C708C  48 02 7F BD */	bl OSInitThreadQueue
/* 800CC190 000C7090  3B 18 00 01 */	addi r24, r24, 1
/* 800CC194 000C7094  9B DA 00 00 */	stb r30, 0(r26)
/* 800CC198 000C7098  2C 18 00 04 */	cmpwi r24, 4
/* 800CC19C 000C709C  3B 9C 00 04 */	addi r28, r28, 4
/* 800CC1A0 000C70A0  9B D9 00 00 */	stb r30, 0(r25)
/* 800CC1A4 000C70A4  3B 7B 00 01 */	addi r27, r27, 1
/* 800CC1A8 000C70A8  3B 5A 00 01 */	addi r26, r26, 1
/* 800CC1AC 000C70AC  3B 39 00 01 */	addi r25, r25, 1
/* 800CC1B0 000C70B0  3B BD 09 A0 */	addi r29, r29, 0x9a0
/* 800CC1B4 000C70B4  41 80 FF BC */	blt lbl_800CC170
/* 800CC1B8 000C70B8  38 00 00 05 */	li r0, 5
/* 800CC1BC 000C70BC  98 0D 9A 7A */	stb r0, _sleepTime-_SDA_BASE_(r13)
/* 800CC1C0 000C70C0  48 02 0E 91 */	bl OSGetAppGamename
/* 800CC1C4 000C70C4  90 6D 9A 6C */	stw r3, _gamecode-_SDA_BASE_(r13)
/* 800CC1C8 000C70C8  48 02 0E D5 */	bl OSGetAppType
/* 800CC1CC 000C70CC  98 6D 9A 70 */	stb r3, _gametype-_SDA_BASE_(r13)
/* 800CC1D0 000C70D0  48 02 CA 91 */	bl SCGetBtDpdSensibility
/* 800CC1D4 000C70D4  54 60 06 3E */	clrlwi r0, r3, 0x18
/* 800CC1D8 000C70D8  28 00 00 01 */	cmplwi r0, 1
/* 800CC1DC 000C70DC  40 80 00 08 */	bge lbl_800CC1E4
/* 800CC1E0 000C70E0  38 00 00 01 */	li r0, 1
lbl_800CC1E4:
/* 800CC1E4 000C70E4  28 00 00 05 */	cmplwi r0, 5
/* 800CC1E8 000C70E8  40 81 00 08 */	ble lbl_800CC1F0
/* 800CC1EC 000C70EC  38 00 00 05 */	li r0, 5
lbl_800CC1F0:
/* 800CC1F0 000C70F0  98 0D 9A 79 */	stb r0, _dpdSensitivity-_SDA_BASE_(r13)
/* 800CC1F4 000C70F4  48 02 CB 31 */	bl SCGetWpadSensorBarPosition
/* 800CC1F8 000C70F8  54 63 06 3E */	clrlwi r3, r3, 0x18
/* 800CC1FC 000C70FC  38 03 FF FF */	addi r0, r3, -1
/* 800CC200 000C7100  7C 00 00 34 */	cntlzw r0, r0
/* 800CC204 000C7104  54 00 DE 3E */	rlwinm r0, r0, 0x1b, 0x18, 0x1f
/* 800CC208 000C7108  98 0D 9A 78 */	stb r0, _sensorBarPos-_SDA_BASE_(r13)
/* 800CC20C 000C710C  48 02 CA BD */	bl SCGetWpadMotorMode
/* 800CC210 000C7110  54 63 06 3E */	clrlwi r3, r3, 0x18
/* 800CC214 000C7114  38 03 FF FF */	addi r0, r3, -1
/* 800CC218 000C7118  7C 00 00 34 */	cntlzw r0, r0
/* 800CC21C 000C711C  54 00 D9 7E */	srwi r0, r0, 5
/* 800CC220 000C7120  90 0D 9A 74 */	stw r0, _rumble-_SDA_BASE_(r13)
/* 800CC224 000C7124  48 02 CB 55 */	bl SCGetWpadSpeakerVolume
/* 800CC228 000C7128  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 800CC22C 000C712C  7C 66 1B 78 */	mr r6, r3
/* 800CC230 000C7130  40 82 00 08 */	bne lbl_800CC238
/* 800CC234 000C7134  38 C0 00 00 */	li r6, 0
lbl_800CC238:
/* 800CC238 000C7138  54 60 06 3E */	clrlwi r0, r3, 0x18
/* 800CC23C 000C713C  28 00 00 7F */	cmplwi r0, 0x7f
/* 800CC240 000C7140  41 80 00 08 */	blt lbl_800CC248
/* 800CC244 000C7144  38 C0 00 7F */	li r6, 0x7f
lbl_800CC248:
/* 800CC248 000C7148  38 A0 00 00 */	li r5, 0
/* 800CC24C 000C714C  38 80 00 01 */	li r4, 1
/* 800CC250 000C7150  38 00 FF FF */	li r0, -1
/* 800CC254 000C7154  98 CD 9A 72 */	stb r6, _speakerVolume-_SDA_BASE_(r13)
/* 800CC258 000C7158  38 7F 00 00 */	addi r3, r31, 0
/* 800CC25C 000C715C  B0 AD 9A 52 */	sth r5, _senseCnt-_SDA_BASE_(r13)
/* 800CC260 000C7160  98 AD 9A 54 */	stb r5, _checkCnt-_SDA_BASE_(r13)
/* 800CC264 000C7164  B0 AD 9A 56 */	sth r5, lbl_804BEDD6-_SDA_BASE_(r13)
/* 800CC268 000C7168  98 AD 9A 65 */	stb r5, lbl_804BEDE5-_SDA_BASE_(r13)
/* 800CC26C 000C716C  98 AD 9A 71 */	stb r5, lbl_804BEDF1-_SDA_BASE_(r13)
/* 800CC270 000C7170  98 8D 9A 66 */	stb r4, _scSetting-_SDA_BASE_(r13)
/* 800CC274 000C7174  98 0D 9A 64 */	stb r0, _afhChannel-_SDA_BASE_(r13)
/* 800CC278 000C7178  48 02 0E 9D */	bl OSCreateAlarm
/* 800CC27C 000C717C  48 02 93 89 */	bl OSGetTime
/* 800CC280 000C7180  3C A0 80 00 */	lis r5, 0x800000F8@ha
/* 800CC284 000C7184  3D 20 80 0D */	lis r9, WPADiManageHandler0@ha
/* 800CC288 000C7188  80 05 00 F8 */	lwz r0, 0x800000F8@l(r5)
/* 800CC28C 000C718C  3C C0 10 62 */	lis r6, 0x10624DD3@ha
/* 800CC290 000C7190  7C 65 1B 78 */	mr r5, r3
/* 800CC294 000C7194  39 29 BE 38 */	addi r9, r9, WPADiManageHandler0@l
/* 800CC298 000C7198  38 66 4D D3 */	addi r3, r6, 0x10624DD3@l
/* 800CC29C 000C719C  54 00 F0 BE */	srwi r0, r0, 2
/* 800CC2A0 000C71A0  7C 03 00 16 */	mulhwu r0, r3, r0
/* 800CC2A4 000C71A4  7C 86 23 78 */	mr r6, r4
/* 800CC2A8 000C71A8  38 7F 00 00 */	addi r3, r31, 0
/* 800CC2AC 000C71AC  38 E0 00 00 */	li r7, 0
/* 800CC2B0 000C71B0  54 08 D1 BE */	srwi r8, r0, 6
/* 800CC2B4 000C71B4  48 02 11 31 */	bl OSSetPeriodicAlarm
/* 800CC2B8 000C71B8  80 6D 82 50 */	lwz r3, __WPADVersion-_SDA_BASE_(r13)
/* 800CC2BC 000C71BC  48 02 0D 85 */	bl OSRegisterVersion
/* 800CC2C0 000C71C0  39 61 00 30 */	addi r11, r1, 0x30
/* 800CC2C4 000C71C4  4B FE 5A C1 */	bl _restgpr_24
/* 800CC2C8 000C71C8  80 01 00 34 */	lwz r0, 0x34(r1)
/* 800CC2CC 000C71CC  7C 08 03 A6 */	mtlr r0
/* 800CC2D0 000C71D0  38 21 00 30 */	addi r1, r1, 0x30
/* 800CC2D4 000C71D4  4E 80 00 20 */	blr 

.global WPADInit
WPADInit:
/* 800CC2D8 000C71D8  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800CC2DC 000C71DC  7C 08 02 A6 */	mflr r0
/* 800CC2E0 000C71E0  90 01 00 14 */	stw r0, 0x14(r1)
/* 800CC2E4 000C71E4  88 0D 9A 50 */	lbz r0, _regShutdown-_SDA_BASE_(r13)
/* 800CC2E8 000C71E8  2C 00 00 00 */	cmpwi r0, 0
/* 800CC2EC 000C71EC  40 82 00 18 */	bne lbl_800CC304
/* 800CC2F0 000C71F0  3C 60 80 3A */	lis r3, ShutdownFunctionInfo@ha
/* 800CC2F4 000C71F4  38 63 95 28 */	addi r3, r3, ShutdownFunctionInfo@l
/* 800CC2F8 000C71F8  48 02 6B 51 */	bl OSRegisterShutdownFunction
/* 800CC2FC 000C71FC  38 00 00 01 */	li r0, 1
/* 800CC300 000C7200  98 0D 9A 50 */	stb r0, _regShutdown-_SDA_BASE_(r13)
lbl_800CC304:
/* 800CC304 000C7204  48 03 41 81 */	bl WUDInit
/* 800CC308 000C7208  2C 03 00 00 */	cmpwi r3, 0
/* 800CC30C 000C720C  41 82 00 10 */	beq lbl_800CC31C
/* 800CC310 000C7210  38 00 00 00 */	li r0, 0
/* 800CC314 000C7214  90 0D 9A 60 */	stw r0, lbl_804BEDE0-_SDA_BASE_(r13)
/* 800CC318 000C7218  4B FF FD B1 */	bl WPADiInitSub
lbl_800CC31C:
/* 800CC31C 000C721C  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800CC320 000C7220  7C 08 03 A6 */	mtlr r0
/* 800CC324 000C7224  38 21 00 10 */	addi r1, r1, 0x10
/* 800CC328 000C7228  4E 80 00 20 */	blr 

.global WPADStartSimpleSync
WPADStartSimpleSync:
/* 800CC32C 000C722C  48 03 47 94 */	b WUDStartSyncSimple

.global WPADStartFastSimpleSync
WPADStartFastSimpleSync:
/* 800CC330 000C7230  48 03 47 04 */	b WUDStartFastSyncSimple

.global WPADStopSimpleSync
WPADStopSimpleSync:
/* 800CC334 000C7234  48 03 48 18 */	b WUDStopSyncSimple

.global WPADStartClearDevice
WPADStartClearDevice:
/* 800CC338 000C7238  48 03 48 AC */	b WUDStartClearDevice

.global WPADSetSimpleSyncCallback
WPADSetSimpleSyncCallback:
/* 800CC33C 000C723C  48 03 45 0C */	b WUDSetSyncDeviceCallback

.global WPADSetClearDeviceCallback
WPADSetClearDeviceCallback:
/* 800CC340 000C7240  48 03 45 64 */	b WUDSetClearDeviceCallback

.global WPADRegisterAllocator
WPADRegisterAllocator:
/* 800CC344 000C7244  48 03 42 38 */	b WUDRegisterAllocator

.global WPADGetWorkMemorySize
WPADGetWorkMemorySize:
/* 800CC348 000C7248  48 03 42 80 */	b WUDGetWorkMemorySize

.global WPADGetStatus
WPADGetStatus:
/* 800CC34C 000C724C  48 03 44 0C */	b WUDGetStatus

.global WPADGetAddress
WPADGetAddress:
/* 800CC350 000C7250  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800CC354 000C7254  7C 08 02 A6 */	mflr r0
/* 800CC358 000C7258  3C A0 80 41 */	lis r5, _wpdcb@ha
/* 800CC35C 000C725C  90 01 00 14 */	stw r0, 0x14(r1)
/* 800CC360 000C7260  54 60 10 3A */	slwi r0, r3, 2
/* 800CC364 000C7264  38 A5 F6 30 */	addi r5, r5, _wpdcb@l
/* 800CC368 000C7268  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800CC36C 000C726C  93 C1 00 08 */	stw r30, 8(r1)
/* 800CC370 000C7270  7C 9E 23 78 */	mr r30, r4
/* 800CC374 000C7274  7F E5 00 2E */	lwzx r31, r5, r0
/* 800CC378 000C7278  48 02 55 49 */	bl OSDisableInterrupts
/* 800CC37C 000C727C  8B FF 08 C3 */	lbz r31, 0x8c3(r31)
/* 800CC380 000C7280  48 02 55 69 */	bl OSRestoreInterrupts
/* 800CC384 000C7284  7F E3 FB 78 */	mr r3, r31
/* 800CC388 000C7288  48 03 6B 31 */	bl _WUDGetDevAddr
/* 800CC38C 000C728C  2C 03 00 00 */	cmpwi r3, 0
/* 800CC390 000C7290  7C 64 1B 78 */	mr r4, r3
/* 800CC394 000C7294  41 82 00 14 */	beq lbl_800CC3A8
/* 800CC398 000C7298  7F C3 F3 78 */	mr r3, r30
/* 800CC39C 000C729C  38 A0 00 06 */	li r5, 6
/* 800CC3A0 000C72A0  4B F3 7C 61 */	bl memcpy
/* 800CC3A4 000C72A4  48 00 00 14 */	b lbl_800CC3B8
lbl_800CC3A8:
/* 800CC3A8 000C72A8  7F C3 F3 78 */	mr r3, r30
/* 800CC3AC 000C72AC  38 80 00 00 */	li r4, 0
/* 800CC3B0 000C72B0  38 A0 00 06 */	li r5, 6
/* 800CC3B4 000C72B4  4B F3 7D 51 */	bl memset
lbl_800CC3B8:
/* 800CC3B8 000C72B8  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800CC3BC 000C72BC  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 800CC3C0 000C72C0  83 C1 00 08 */	lwz r30, 8(r1)
/* 800CC3C4 000C72C4  7C 08 03 A6 */	mtlr r0
/* 800CC3C8 000C72C8  38 21 00 10 */	addi r1, r1, 0x10
/* 800CC3CC 000C72CC  4E 80 00 20 */	blr 

.global WPADGetSensorBarPosition
WPADGetSensorBarPosition:
/* 800CC3D0 000C72D0  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800CC3D4 000C72D4  7C 08 02 A6 */	mflr r0
/* 800CC3D8 000C72D8  90 01 00 14 */	stw r0, 0x14(r1)
/* 800CC3DC 000C72DC  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800CC3E0 000C72E0  48 02 54 E1 */	bl OSDisableInterrupts
/* 800CC3E4 000C72E4  8B ED 9A 78 */	lbz r31, _sensorBarPos-_SDA_BASE_(r13)
/* 800CC3E8 000C72E8  48 02 55 01 */	bl OSRestoreInterrupts
/* 800CC3EC 000C72EC  7F E3 FB 78 */	mr r3, r31
/* 800CC3F0 000C72F0  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 800CC3F4 000C72F4  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800CC3F8 000C72F8  7C 08 03 A6 */	mtlr r0
/* 800CC3FC 000C72FC  38 21 00 10 */	addi r1, r1, 0x10
/* 800CC400 000C7300  4E 80 00 20 */	blr 

.global setupCallback
setupCallback:
/* 800CC404 000C7304  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800CC408 000C7308  7C 08 02 A6 */	mflr r0
/* 800CC40C 000C730C  2C 04 FF FF */	cmpwi r4, -1
/* 800CC410 000C7310  90 01 00 24 */	stw r0, 0x24(r1)
/* 800CC414 000C7314  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800CC418 000C7318  3F E0 80 41 */	lis r31, _wpdcb@ha
/* 800CC41C 000C731C  3B FF F6 30 */	addi r31, r31, _wpdcb@l
/* 800CC420 000C7320  93 C1 00 18 */	stw r30, 0x18(r1)
/* 800CC424 000C7324  54 7E 10 3A */	slwi r30, r3, 2
/* 800CC428 000C7328  93 A1 00 14 */	stw r29, 0x14(r1)
/* 800CC42C 000C732C  7F BF F0 2E */	lwzx r29, r31, r30
/* 800CC430 000C7330  41 82 00 8C */	beq lbl_800CC4BC
/* 800CC434 000C7334  2C 04 00 00 */	cmpwi r4, 0
/* 800CC438 000C7338  40 82 00 24 */	bne lbl_800CC45C
/* 800CC43C 000C733C  38 00 00 01 */	li r0, 1
/* 800CC440 000C7340  90 1D 08 DC */	stw r0, 0x8dc(r29)
/* 800CC444 000C7344  81 9D 08 A4 */	lwz r12, 0x8a4(r29)
/* 800CC448 000C7348  2C 0C 00 00 */	cmpwi r12, 0
/* 800CC44C 000C734C  41 82 00 70 */	beq lbl_800CC4BC
/* 800CC450 000C7350  7D 89 03 A6 */	mtctr r12
/* 800CC454 000C7354  4E 80 04 21 */	bctrl 
/* 800CC458 000C7358  48 00 00 64 */	b lbl_800CC4BC
lbl_800CC45C:
/* 800CC45C 000C735C  48 02 54 65 */	bl OSDisableInterrupts
/* 800CC460 000C7360  83 BD 08 BC */	lwz r29, 0x8bc(r29)
/* 800CC464 000C7364  48 02 54 85 */	bl OSRestoreInterrupts
/* 800CC468 000C7368  2C 1D FF FF */	cmpwi r29, -1
/* 800CC46C 000C736C  41 82 00 50 */	beq lbl_800CC4BC
/* 800CC470 000C7370  7F DF F0 2E */	lwzx r30, r31, r30
/* 800CC474 000C7374  48 02 54 4D */	bl OSDisableInterrupts
/* 800CC478 000C7378  8B DE 08 C3 */	lbz r30, 0x8c3(r30)
/* 800CC47C 000C737C  48 02 54 6D */	bl OSRestoreInterrupts
/* 800CC480 000C7380  7F C3 F3 78 */	mr r3, r30
/* 800CC484 000C7384  48 03 6A 35 */	bl _WUDGetDevAddr
/* 800CC488 000C7388  2C 03 00 00 */	cmpwi r3, 0
/* 800CC48C 000C738C  41 82 00 18 */	beq lbl_800CC4A4
/* 800CC490 000C7390  7C 64 1B 78 */	mr r4, r3
/* 800CC494 000C7394  38 61 00 08 */	addi r3, r1, 8
/* 800CC498 000C7398  38 A0 00 06 */	li r5, 6
/* 800CC49C 000C739C  4B F3 7B 65 */	bl memcpy
/* 800CC4A0 000C73A0  48 00 00 14 */	b lbl_800CC4B4
lbl_800CC4A4:
/* 800CC4A4 000C73A4  38 61 00 08 */	addi r3, r1, 8
/* 800CC4A8 000C73A8  38 80 00 00 */	li r4, 0
/* 800CC4AC 000C73AC  38 A0 00 06 */	li r5, 6
/* 800CC4B0 000C73B0  4B F3 7C 55 */	bl memset
lbl_800CC4B4:
/* 800CC4B4 000C73B4  38 61 00 08 */	addi r3, r1, 8
/* 800CC4B8 000C73B8  48 04 9F A5 */	bl func_8011645C
lbl_800CC4BC:
/* 800CC4BC 000C73BC  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800CC4C0 000C73C0  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800CC4C4 000C73C4  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 800CC4C8 000C73C8  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 800CC4CC 000C73CC  7C 08 03 A6 */	mtlr r0
/* 800CC4D0 000C73D0  38 21 00 20 */	addi r1, r1, 0x20
/* 800CC4D4 000C73D4  4E 80 00 20 */	blr 

.global abortConnCallback
abortConnCallback:
/* 800CC4D8 000C73D8  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 800CC4DC 000C73DC  7C 08 02 A6 */	mflr r0
/* 800CC4E0 000C73E0  90 01 00 34 */	stw r0, 0x34(r1)
/* 800CC4E4 000C73E4  39 61 00 30 */	addi r11, r1, 0x30
/* 800CC4E8 000C73E8  4B FE 58 5D */	bl _savegpr_27
/* 800CC4EC 000C73EC  3F E0 80 41 */	lis r31, _wpdcb@ha
/* 800CC4F0 000C73F0  2C 04 00 00 */	cmpwi r4, 0
/* 800CC4F4 000C73F4  54 7E 10 3A */	slwi r30, r3, 2
/* 800CC4F8 000C73F8  7C 9B 23 78 */	mr r27, r4
/* 800CC4FC 000C73FC  3B FF F6 30 */	addi r31, r31, _wpdcb@l
/* 800CC500 000C7400  7F 9F F0 2E */	lwzx r28, r31, r30
/* 800CC504 000C7404  41 82 00 A0 */	beq lbl_800CC5A4
/* 800CC508 000C7408  48 02 53 B9 */	bl OSDisableInterrupts
/* 800CC50C 000C740C  38 00 00 00 */	li r0, 0
/* 800CC510 000C7410  7C 7D 1B 78 */	mr r29, r3
/* 800CC514 000C7414  98 1C 01 60 */	stb r0, 0x160(r28)
/* 800CC518 000C7418  38 80 00 00 */	li r4, 0
/* 800CC51C 000C741C  98 1C 01 61 */	stb r0, 0x161(r28)
/* 800CC520 000C7420  80 1C 01 68 */	lwz r0, 0x168(r28)
/* 800CC524 000C7424  80 7C 01 64 */	lwz r3, 0x164(r28)
/* 800CC528 000C7428  1C A0 00 30 */	mulli r5, r0, 0x30
/* 800CC52C 000C742C  4B F3 7B D9 */	bl memset
/* 800CC530 000C7430  7F A3 EB 78 */	mr r3, r29
/* 800CC534 000C7434  48 02 53 B5 */	bl OSRestoreInterrupts
/* 800CC538 000C7438  2C 1B FF FF */	cmpwi r27, -1
/* 800CC53C 000C743C  41 82 00 68 */	beq lbl_800CC5A4
/* 800CC540 000C7440  7F BF F0 2E */	lwzx r29, r31, r30
/* 800CC544 000C7444  48 02 53 7D */	bl OSDisableInterrupts
/* 800CC548 000C7448  83 BD 08 BC */	lwz r29, 0x8bc(r29)
/* 800CC54C 000C744C  48 02 53 9D */	bl OSRestoreInterrupts
/* 800CC550 000C7450  2C 1D FF FF */	cmpwi r29, -1
/* 800CC554 000C7454  41 82 00 50 */	beq lbl_800CC5A4
/* 800CC558 000C7458  7F BF F0 2E */	lwzx r29, r31, r30
/* 800CC55C 000C745C  48 02 53 65 */	bl OSDisableInterrupts
/* 800CC560 000C7460  8B BD 08 C3 */	lbz r29, 0x8c3(r29)
/* 800CC564 000C7464  48 02 53 85 */	bl OSRestoreInterrupts
/* 800CC568 000C7468  7F A3 EB 78 */	mr r3, r29
/* 800CC56C 000C746C  48 03 69 4D */	bl _WUDGetDevAddr
/* 800CC570 000C7470  2C 03 00 00 */	cmpwi r3, 0
/* 800CC574 000C7474  41 82 00 18 */	beq lbl_800CC58C
/* 800CC578 000C7478  7C 64 1B 78 */	mr r4, r3
/* 800CC57C 000C747C  38 61 00 08 */	addi r3, r1, 8
/* 800CC580 000C7480  38 A0 00 06 */	li r5, 6
/* 800CC584 000C7484  4B F3 7A 7D */	bl memcpy
/* 800CC588 000C7488  48 00 00 14 */	b lbl_800CC59C
lbl_800CC58C:
/* 800CC58C 000C748C  38 61 00 08 */	addi r3, r1, 8
/* 800CC590 000C7490  38 80 00 00 */	li r4, 0
/* 800CC594 000C7494  38 A0 00 06 */	li r5, 6
/* 800CC598 000C7498  4B F3 7B 6D */	bl memset
lbl_800CC59C:
/* 800CC59C 000C749C  38 61 00 08 */	addi r3, r1, 8
/* 800CC5A0 000C74A0  48 04 9E BD */	bl func_8011645C
lbl_800CC5A4:
/* 800CC5A4 000C74A4  39 61 00 30 */	addi r11, r1, 0x30
/* 800CC5A8 000C74A8  4B FE 57 E9 */	bl _restgpr_27
/* 800CC5AC 000C74AC  80 01 00 34 */	lwz r0, 0x34(r1)
/* 800CC5B0 000C74B0  7C 08 03 A6 */	mtlr r0
/* 800CC5B4 000C74B4  38 21 00 30 */	addi r1, r1, 0x30
/* 800CC5B8 000C74B8  4E 80 00 20 */	blr 

.global firmwareCheckCallback
firmwareCheckCallback:
/* 800CC5BC 000C74BC  94 21 FD 80 */	stwu r1, -0x280(r1)
/* 800CC5C0 000C74C0  7C 08 02 A6 */	mflr r0
/* 800CC5C4 000C74C4  90 01 02 84 */	stw r0, 0x284(r1)
/* 800CC5C8 000C74C8  39 61 02 80 */	addi r11, r1, 0x280
/* 800CC5CC 000C74CC  4B FE 57 75 */	bl _savegpr_26
/* 800CC5D0 000C74D0  3C A0 80 41 */	lis r5, _wpdcb@ha
/* 800CC5D4 000C74D4  2C 04 FF FF */	cmpwi r4, -1
/* 800CC5D8 000C74D8  54 60 10 3A */	slwi r0, r3, 2
/* 800CC5DC 000C74DC  7C 7B 1B 78 */	mr r27, r3
/* 800CC5E0 000C74E0  38 A5 F6 30 */	addi r5, r5, _wpdcb@l
/* 800CC5E4 000C74E4  7C 9A 23 78 */	mr r26, r4
/* 800CC5E8 000C74E8  7F A5 00 2E */	lwzx r29, r5, r0
/* 800CC5EC 000C74EC  41 82 08 94 */	beq lbl_800CCE80
/* 800CC5F0 000C74F0  48 02 52 D1 */	bl OSDisableInterrupts
/* 800CC5F4 000C74F4  7F 44 00 34 */	cntlzw r4, r26
/* 800CC5F8 000C74F8  38 00 00 00 */	li r0, 0
/* 800CC5FC 000C74FC  54 84 D9 7E */	srwi r4, r4, 5
/* 800CC600 000C7500  90 9D 08 E0 */	stw r4, 0x8e0(r29)
/* 800CC604 000C7504  90 1D 08 BC */	stw r0, 0x8bc(r29)
/* 800CC608 000C7508  48 02 52 E1 */	bl OSRestoreInterrupts
/* 800CC60C 000C750C  2C 1A 00 00 */	cmpwi r26, 0
/* 800CC610 000C7510  3B E0 00 2A */	li r31, 0x2a
/* 800CC614 000C7514  40 82 00 08 */	bne lbl_800CC61C
/* 800CC618 000C7518  3B E0 00 14 */	li r31, 0x14
lbl_800CC61C:
/* 800CC61C 000C751C  7F 43 00 34 */	cntlzw r3, r26
/* 800CC620 000C7520  80 1D 08 E0 */	lwz r0, 0x8e0(r29)
/* 800CC624 000C7524  54 64 DF FE */	rlwinm r4, r3, 0x1b, 0x1f, 0x1f
/* 800CC628 000C7528  7C A4 00 D0 */	neg r5, r4
/* 800CC62C 000C752C  3C 60 80 3A */	lis r3, lbl_80399584@ha
/* 800CC630 000C7530  2F 00 00 00 */	cmpwi cr6, r0, 0
/* 800CC634 000C7534  3C 80 80 3A */	lis r4, lbl_803995BC@ha
/* 800CC638 000C7538  70 BC 17 6C */	andi. r28, r5, 0x176c
/* 800CC63C 000C753C  38 63 95 84 */	addi r3, r3, lbl_80399584@l
/* 800CC640 000C7540  38 84 95 BC */	addi r4, r4, lbl_803995BC@l
/* 800CC644 000C7544  41 9A 00 08 */	beq cr6, lbl_800CC64C
/* 800CC648 000C7548  38 8D 82 5C */	addi r4, r13, $$22472-_SDA_BASE_
lbl_800CC64C:
/* 800CC64C 000C754C  4C C6 31 82 */	crclr 6
/* 800CC650 000C7550  48 00 B1 0D */	bl DEBUGPrint
/* 800CC654 000C7554  3F C0 80 0D */	lis r30, abortConnCallback@ha
/* 800CC658 000C7558  38 7D 01 60 */	addi r3, r29, 0x160
/* 800CC65C 000C755C  38 BE C4 D8 */	addi r5, r30, abortConnCallback@l
/* 800CC660 000C7560  38 80 00 00 */	li r4, 0
/* 800CC664 000C7564  48 00 4C 31 */	bl WPADiSendSetReportType
/* 800CC668 000C7568  38 60 00 01 */	li r3, 1
/* 800CC66C 000C756C  38 00 00 00 */	li r0, 0
/* 800CC670 000C7570  B0 61 02 1A */	sth r3, 0x21a(r1)
/* 800CC674 000C7574  39 9E C4 D8 */	addi r12, r30, -15144
/* 800CC678 000C7578  3B C0 00 1A */	li r30, 0x1a
/* 800CC67C 000C757C  81 41 02 08 */	lwz r10, 0x208(r1)
/* 800CC680 000C7580  98 01 02 04 */	stb r0, 0x204(r1)
/* 800CC684 000C7584  81 21 02 0C */	lwz r9, 0x20c(r1)
/* 800CC688 000C7588  81 61 02 04 */	lwz r11, 0x204(r1)
/* 800CC68C 000C758C  81 01 02 10 */	lwz r8, 0x210(r1)
/* 800CC690 000C7590  80 E1 02 14 */	lwz r7, 0x214(r1)
/* 800CC694 000C7594  80 C1 02 18 */	lwz r6, 0x218(r1)
/* 800CC698 000C7598  80 A1 02 1C */	lwz r5, 0x21c(r1)
/* 800CC69C 000C759C  80 81 02 20 */	lwz r4, 0x220(r1)
/* 800CC6A0 000C75A0  80 61 02 24 */	lwz r3, 0x224(r1)
/* 800CC6A4 000C75A4  80 01 02 28 */	lwz r0, 0x228(r1)
/* 800CC6A8 000C75A8  93 C1 02 00 */	stw r30, 0x200(r1)
/* 800CC6AC 000C75AC  91 81 02 2C */	stw r12, 0x22c(r1)
/* 800CC6B0 000C75B0  93 C1 02 30 */	stw r30, 0x230(r1)
/* 800CC6B4 000C75B4  91 61 02 34 */	stw r11, 0x234(r1)
/* 800CC6B8 000C75B8  91 41 02 38 */	stw r10, 0x238(r1)
/* 800CC6BC 000C75BC  91 21 02 3C */	stw r9, 0x23c(r1)
/* 800CC6C0 000C75C0  91 01 02 40 */	stw r8, 0x240(r1)
/* 800CC6C4 000C75C4  90 E1 02 44 */	stw r7, 0x244(r1)
/* 800CC6C8 000C75C8  90 C1 02 48 */	stw r6, 0x248(r1)
/* 800CC6CC 000C75CC  90 A1 02 4C */	stw r5, 0x24c(r1)
/* 800CC6D0 000C75D0  90 81 02 50 */	stw r4, 0x250(r1)
/* 800CC6D4 000C75D4  90 61 02 54 */	stw r3, 0x254(r1)
/* 800CC6D8 000C75D8  90 01 02 58 */	stw r0, 0x258(r1)
/* 800CC6DC 000C75DC  91 81 02 5C */	stw r12, 0x25c(r1)
/* 800CC6E0 000C75E0  48 02 51 E1 */	bl OSDisableInterrupts
/* 800CC6E4 000C75E4  7C 7E 1B 78 */	mr r30, r3
/* 800CC6E8 000C75E8  48 02 51 D9 */	bl OSDisableInterrupts
/* 800CC6EC 000C75EC  88 9D 01 60 */	lbz r4, 0x160(r29)
/* 800CC6F0 000C75F0  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800CC6F4 000C75F4  7C 04 00 50 */	subf r0, r4, r0
/* 800CC6F8 000C75F8  7C 1A 07 75 */	extsb. r26, r0
/* 800CC6FC 000C75FC  40 80 00 10 */	bge lbl_800CC70C
/* 800CC700 000C7600  80 1D 01 68 */	lwz r0, 0x168(r29)
/* 800CC704 000C7604  7C 1A 02 14 */	add r0, r26, r0
/* 800CC708 000C7608  7C 1A 07 74 */	extsb r26, r0
lbl_800CC70C:
/* 800CC70C 000C760C  48 02 51 DD */	bl OSRestoreInterrupts
/* 800CC710 000C7610  80 7D 01 68 */	lwz r3, 0x168(r29)
/* 800CC714 000C7614  38 03 FF FF */	addi r0, r3, -1
/* 800CC718 000C7618  7C 00 D0 40 */	cmplw r0, r26
/* 800CC71C 000C761C  40 82 00 10 */	bne lbl_800CC72C
/* 800CC720 000C7620  7F C3 F3 78 */	mr r3, r30
/* 800CC724 000C7624  48 02 51 C5 */	bl OSRestoreInterrupts
/* 800CC728 000C7628  48 00 00 78 */	b lbl_800CC7A0
lbl_800CC72C:
/* 800CC72C 000C762C  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800CC730 000C7630  38 80 00 00 */	li r4, 0
/* 800CC734 000C7634  80 7D 01 64 */	lwz r3, 0x164(r29)
/* 800CC738 000C7638  38 A0 00 30 */	li r5, 0x30
/* 800CC73C 000C763C  7C 00 07 74 */	extsb r0, r0
/* 800CC740 000C7640  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CC744 000C7644  7C 63 02 14 */	add r3, r3, r0
/* 800CC748 000C7648  4B F3 79 BD */	bl memset
/* 800CC74C 000C764C  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800CC750 000C7650  38 81 02 30 */	addi r4, r1, 0x230
/* 800CC754 000C7654  80 7D 01 64 */	lwz r3, 0x164(r29)
/* 800CC758 000C7658  38 A0 00 30 */	li r5, 0x30
/* 800CC75C 000C765C  7C 00 07 74 */	extsb r0, r0
/* 800CC760 000C7660  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CC764 000C7664  7C 63 02 14 */	add r3, r3, r0
/* 800CC768 000C7668  4B F3 78 99 */	bl memcpy
/* 800CC76C 000C766C  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800CC770 000C7670  7F C3 F3 78 */	mr r3, r30
/* 800CC774 000C7674  80 9D 01 68 */	lwz r4, 0x168(r29)
/* 800CC778 000C7678  7C 06 07 74 */	extsb r6, r0
/* 800CC77C 000C767C  38 84 FF FF */	addi r4, r4, -1
/* 800CC780 000C7680  7C A4 30 50 */	subf r5, r4, r6
/* 800CC784 000C7684  38 06 00 01 */	addi r0, r6, 1
/* 800CC788 000C7688  7C 86 20 50 */	subf r4, r6, r4
/* 800CC78C 000C768C  7C A4 20 F8 */	nor r4, r5, r4
/* 800CC790 000C7690  7C 84 FE 70 */	srawi r4, r4, 0x1f
/* 800CC794 000C7694  7C 00 20 78 */	andc r0, r0, r4
/* 800CC798 000C7698  98 1D 01 61 */	stb r0, 0x161(r29)
/* 800CC79C 000C769C  48 02 51 4D */	bl OSRestoreInterrupts
lbl_800CC7A0:
/* 800CC7A0 000C76A0  38 60 00 01 */	li r3, 1
/* 800CC7A4 000C76A4  3B C0 00 11 */	li r30, 0x11
/* 800CC7A8 000C76A8  7C 60 D8 30 */	slw r0, r3, r27
/* 800CC7AC 000C76AC  B0 61 01 BA */	sth r3, 0x1ba(r1)
/* 800CC7B0 000C76B0  54 00 26 36 */	rlwinm r0, r0, 4, 0x18, 0x1b
/* 800CC7B4 000C76B4  81 41 01 A8 */	lwz r10, 0x1a8(r1)
/* 800CC7B8 000C76B8  98 01 01 A4 */	stb r0, 0x1a4(r1)
/* 800CC7BC 000C76BC  3D 80 80 0D */	lis r12, abortConnCallback@ha
/* 800CC7C0 000C76C0  39 8C C4 D8 */	addi r12, r12, abortConnCallback@l
/* 800CC7C4 000C76C4  81 21 01 AC */	lwz r9, 0x1ac(r1)
/* 800CC7C8 000C76C8  81 61 01 A4 */	lwz r11, 0x1a4(r1)
/* 800CC7CC 000C76CC  81 01 01 B0 */	lwz r8, 0x1b0(r1)
/* 800CC7D0 000C76D0  80 E1 01 B4 */	lwz r7, 0x1b4(r1)
/* 800CC7D4 000C76D4  80 C1 01 B8 */	lwz r6, 0x1b8(r1)
/* 800CC7D8 000C76D8  80 A1 01 BC */	lwz r5, 0x1bc(r1)
/* 800CC7DC 000C76DC  80 81 01 C0 */	lwz r4, 0x1c0(r1)
/* 800CC7E0 000C76E0  80 61 01 C4 */	lwz r3, 0x1c4(r1)
/* 800CC7E4 000C76E4  80 01 01 C8 */	lwz r0, 0x1c8(r1)
/* 800CC7E8 000C76E8  93 C1 01 A0 */	stw r30, 0x1a0(r1)
/* 800CC7EC 000C76EC  91 81 01 CC */	stw r12, 0x1cc(r1)
/* 800CC7F0 000C76F0  93 C1 01 D0 */	stw r30, 0x1d0(r1)
/* 800CC7F4 000C76F4  91 61 01 D4 */	stw r11, 0x1d4(r1)
/* 800CC7F8 000C76F8  91 41 01 D8 */	stw r10, 0x1d8(r1)
/* 800CC7FC 000C76FC  91 21 01 DC */	stw r9, 0x1dc(r1)
/* 800CC800 000C7700  91 01 01 E0 */	stw r8, 0x1e0(r1)
/* 800CC804 000C7704  90 E1 01 E4 */	stw r7, 0x1e4(r1)
/* 800CC808 000C7708  90 C1 01 E8 */	stw r6, 0x1e8(r1)
/* 800CC80C 000C770C  90 A1 01 EC */	stw r5, 0x1ec(r1)
/* 800CC810 000C7710  90 81 01 F0 */	stw r4, 0x1f0(r1)
/* 800CC814 000C7714  90 61 01 F4 */	stw r3, 0x1f4(r1)
/* 800CC818 000C7718  90 01 01 F8 */	stw r0, 0x1f8(r1)
/* 800CC81C 000C771C  91 81 01 FC */	stw r12, 0x1fc(r1)
/* 800CC820 000C7720  48 02 50 A1 */	bl OSDisableInterrupts
/* 800CC824 000C7724  7C 7E 1B 78 */	mr r30, r3
/* 800CC828 000C7728  48 02 50 99 */	bl OSDisableInterrupts
/* 800CC82C 000C772C  88 9D 01 60 */	lbz r4, 0x160(r29)
/* 800CC830 000C7730  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800CC834 000C7734  7C 04 00 50 */	subf r0, r4, r0
/* 800CC838 000C7738  7C 1A 07 75 */	extsb. r26, r0
/* 800CC83C 000C773C  40 80 00 10 */	bge lbl_800CC84C
/* 800CC840 000C7740  80 1D 01 68 */	lwz r0, 0x168(r29)
/* 800CC844 000C7744  7C 1A 02 14 */	add r0, r26, r0
/* 800CC848 000C7748  7C 1A 07 74 */	extsb r26, r0
lbl_800CC84C:
/* 800CC84C 000C774C  48 02 50 9D */	bl OSRestoreInterrupts
/* 800CC850 000C7750  80 7D 01 68 */	lwz r3, 0x168(r29)
/* 800CC854 000C7754  38 03 FF FF */	addi r0, r3, -1
/* 800CC858 000C7758  7C 00 D0 40 */	cmplw r0, r26
/* 800CC85C 000C775C  40 82 00 10 */	bne lbl_800CC86C
/* 800CC860 000C7760  7F C3 F3 78 */	mr r3, r30
/* 800CC864 000C7764  48 02 50 85 */	bl OSRestoreInterrupts
/* 800CC868 000C7768  48 00 00 78 */	b lbl_800CC8E0
lbl_800CC86C:
/* 800CC86C 000C776C  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800CC870 000C7770  38 80 00 00 */	li r4, 0
/* 800CC874 000C7774  80 7D 01 64 */	lwz r3, 0x164(r29)
/* 800CC878 000C7778  38 A0 00 30 */	li r5, 0x30
/* 800CC87C 000C777C  7C 00 07 74 */	extsb r0, r0
/* 800CC880 000C7780  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CC884 000C7784  7C 63 02 14 */	add r3, r3, r0
/* 800CC888 000C7788  4B F3 78 7D */	bl memset
/* 800CC88C 000C778C  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800CC890 000C7790  38 81 01 D0 */	addi r4, r1, 0x1d0
/* 800CC894 000C7794  80 7D 01 64 */	lwz r3, 0x164(r29)
/* 800CC898 000C7798  38 A0 00 30 */	li r5, 0x30
/* 800CC89C 000C779C  7C 00 07 74 */	extsb r0, r0
/* 800CC8A0 000C77A0  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CC8A4 000C77A4  7C 63 02 14 */	add r3, r3, r0
/* 800CC8A8 000C77A8  4B F3 77 59 */	bl memcpy
/* 800CC8AC 000C77AC  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800CC8B0 000C77B0  7F C3 F3 78 */	mr r3, r30
/* 800CC8B4 000C77B4  80 9D 01 68 */	lwz r4, 0x168(r29)
/* 800CC8B8 000C77B8  7C 06 07 74 */	extsb r6, r0
/* 800CC8BC 000C77BC  38 84 FF FF */	addi r4, r4, -1
/* 800CC8C0 000C77C0  7C A4 30 50 */	subf r5, r4, r6
/* 800CC8C4 000C77C4  38 06 00 01 */	addi r0, r6, 1
/* 800CC8C8 000C77C8  7C 86 20 50 */	subf r4, r6, r4
/* 800CC8CC 000C77CC  7C A4 20 F8 */	nor r4, r5, r4
/* 800CC8D0 000C77D0  7C 84 FE 70 */	srawi r4, r4, 0x1f
/* 800CC8D4 000C77D4  7C 00 20 78 */	andc r0, r0, r4
/* 800CC8D8 000C77D8  98 1D 01 61 */	stb r0, 0x161(r29)
/* 800CC8DC 000C77DC  48 02 50 0D */	bl OSRestoreInterrupts
lbl_800CC8E0:
/* 800CC8E0 000C77E0  3C C0 80 0D */	lis r6, abortConnCallback@ha
/* 800CC8E4 000C77E4  38 60 00 2A */	li r3, 0x2a
/* 800CC8E8 000C77E8  38 C6 C4 D8 */	addi r6, r6, abortConnCallback@l
/* 800CC8EC 000C77EC  39 00 00 38 */	li r8, 0x38
/* 800CC8F0 000C77F0  38 E0 00 17 */	li r7, 0x17
/* 800CC8F4 000C77F4  38 00 00 06 */	li r0, 6
/* 800CC8F8 000C77F8  90 61 00 18 */	stw r3, 0x18(r1)
/* 800CC8FC 000C77FC  38 61 01 44 */	addi r3, r1, 0x144
/* 800CC900 000C7800  38 81 00 18 */	addi r4, r1, 0x18
/* 800CC904 000C7804  38 A0 00 04 */	li r5, 4
/* 800CC908 000C7808  B1 01 00 0C */	sth r8, 0xc(r1)
/* 800CC90C 000C780C  90 E1 01 40 */	stw r7, 0x140(r1)
/* 800CC910 000C7810  B0 01 01 5A */	sth r0, 0x15a(r1)
/* 800CC914 000C7814  90 C1 01 6C */	stw r6, 0x16c(r1)
/* 800CC918 000C7818  4B F3 76 E9 */	bl memcpy
/* 800CC91C 000C781C  38 61 01 48 */	addi r3, r1, 0x148
/* 800CC920 000C7820  38 81 00 0C */	addi r4, r1, 0xc
/* 800CC924 000C7824  38 A0 00 02 */	li r5, 2
/* 800CC928 000C7828  4B F3 76 D9 */	bl memcpy
/* 800CC92C 000C782C  A0 01 00 0C */	lhz r0, 0xc(r1)
/* 800CC930 000C7830  3B 7D 09 34 */	addi r27, r29, 0x934
/* 800CC934 000C7834  81 81 00 18 */	lwz r12, 0x18(r1)
/* 800CC938 000C7838  B0 01 01 60 */	sth r0, 0x160(r1)
/* 800CC93C 000C783C  81 61 01 40 */	lwz r11, 0x140(r1)
/* 800CC940 000C7840  81 41 01 44 */	lwz r10, 0x144(r1)
/* 800CC944 000C7844  81 21 01 48 */	lwz r9, 0x148(r1)
/* 800CC948 000C7848  81 01 01 4C */	lwz r8, 0x14c(r1)
/* 800CC94C 000C784C  80 E1 01 50 */	lwz r7, 0x150(r1)
/* 800CC950 000C7850  80 C1 01 54 */	lwz r6, 0x154(r1)
/* 800CC954 000C7854  80 A1 01 58 */	lwz r5, 0x158(r1)
/* 800CC958 000C7858  80 81 01 60 */	lwz r4, 0x160(r1)
/* 800CC95C 000C785C  80 61 01 68 */	lwz r3, 0x168(r1)
/* 800CC960 000C7860  80 01 01 6C */	lwz r0, 0x16c(r1)
/* 800CC964 000C7864  93 61 01 5C */	stw r27, 0x15c(r1)
/* 800CC968 000C7868  91 81 01 64 */	stw r12, 0x164(r1)
/* 800CC96C 000C786C  91 61 01 70 */	stw r11, 0x170(r1)
/* 800CC970 000C7870  91 41 01 74 */	stw r10, 0x174(r1)
/* 800CC974 000C7874  91 21 01 78 */	stw r9, 0x178(r1)
/* 800CC978 000C7878  91 01 01 7C */	stw r8, 0x17c(r1)
/* 800CC97C 000C787C  90 E1 01 80 */	stw r7, 0x180(r1)
/* 800CC980 000C7880  90 C1 01 84 */	stw r6, 0x184(r1)
/* 800CC984 000C7884  90 A1 01 88 */	stw r5, 0x188(r1)
/* 800CC988 000C7888  93 61 01 8C */	stw r27, 0x18c(r1)
/* 800CC98C 000C788C  90 81 01 90 */	stw r4, 0x190(r1)
/* 800CC990 000C7890  91 81 01 94 */	stw r12, 0x194(r1)
/* 800CC994 000C7894  90 61 01 98 */	stw r3, 0x198(r1)
/* 800CC998 000C7898  90 01 01 9C */	stw r0, 0x19c(r1)
/* 800CC99C 000C789C  48 02 4F 25 */	bl OSDisableInterrupts
/* 800CC9A0 000C78A0  7C 7E 1B 78 */	mr r30, r3
/* 800CC9A4 000C78A4  48 02 4F 1D */	bl OSDisableInterrupts
/* 800CC9A8 000C78A8  88 9D 01 60 */	lbz r4, 0x160(r29)
/* 800CC9AC 000C78AC  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800CC9B0 000C78B0  7C 04 00 50 */	subf r0, r4, r0
/* 800CC9B4 000C78B4  7C 1A 07 75 */	extsb. r26, r0
/* 800CC9B8 000C78B8  40 80 00 10 */	bge lbl_800CC9C8
/* 800CC9BC 000C78BC  80 1D 01 68 */	lwz r0, 0x168(r29)
/* 800CC9C0 000C78C0  7C 1A 02 14 */	add r0, r26, r0
/* 800CC9C4 000C78C4  7C 1A 07 74 */	extsb r26, r0
lbl_800CC9C8:
/* 800CC9C8 000C78C8  48 02 4F 21 */	bl OSRestoreInterrupts
/* 800CC9CC 000C78CC  80 7D 01 68 */	lwz r3, 0x168(r29)
/* 800CC9D0 000C78D0  38 03 FF FF */	addi r0, r3, -1
/* 800CC9D4 000C78D4  7C 00 D0 40 */	cmplw r0, r26
/* 800CC9D8 000C78D8  40 82 00 10 */	bne lbl_800CC9E8
/* 800CC9DC 000C78DC  7F C3 F3 78 */	mr r3, r30
/* 800CC9E0 000C78E0  48 02 4F 09 */	bl OSRestoreInterrupts
/* 800CC9E4 000C78E4  48 00 00 78 */	b lbl_800CCA5C
lbl_800CC9E8:
/* 800CC9E8 000C78E8  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800CC9EC 000C78EC  38 80 00 00 */	li r4, 0
/* 800CC9F0 000C78F0  80 7D 01 64 */	lwz r3, 0x164(r29)
/* 800CC9F4 000C78F4  38 A0 00 30 */	li r5, 0x30
/* 800CC9F8 000C78F8  7C 00 07 74 */	extsb r0, r0
/* 800CC9FC 000C78FC  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CCA00 000C7900  7C 63 02 14 */	add r3, r3, r0
/* 800CCA04 000C7904  4B F3 77 01 */	bl memset
/* 800CCA08 000C7908  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800CCA0C 000C790C  38 81 01 70 */	addi r4, r1, 0x170
/* 800CCA10 000C7910  80 7D 01 64 */	lwz r3, 0x164(r29)
/* 800CCA14 000C7914  38 A0 00 30 */	li r5, 0x30
/* 800CCA18 000C7918  7C 00 07 74 */	extsb r0, r0
/* 800CCA1C 000C791C  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CCA20 000C7920  7C 63 02 14 */	add r3, r3, r0
/* 800CCA24 000C7924  4B F3 75 DD */	bl memcpy
/* 800CCA28 000C7928  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800CCA2C 000C792C  7F C3 F3 78 */	mr r3, r30
/* 800CCA30 000C7930  80 9D 01 68 */	lwz r4, 0x168(r29)
/* 800CCA34 000C7934  7C 06 07 74 */	extsb r6, r0
/* 800CCA38 000C7938  38 84 FF FF */	addi r4, r4, -1
/* 800CCA3C 000C793C  7C A4 30 50 */	subf r5, r4, r6
/* 800CCA40 000C7940  38 06 00 01 */	addi r0, r6, 1
/* 800CCA44 000C7944  7C 86 20 50 */	subf r4, r6, r4
/* 800CCA48 000C7948  7C A4 20 F8 */	nor r4, r5, r4
/* 800CCA4C 000C794C  7C 84 FE 70 */	srawi r4, r4, 0x1f
/* 800CCA50 000C7950  7C 00 20 78 */	andc r0, r0, r4
/* 800CCA54 000C7954  98 1D 01 61 */	stb r0, 0x161(r29)
/* 800CCA58 000C7958  48 02 4E 91 */	bl OSRestoreInterrupts
lbl_800CCA5C:
/* 800CCA5C 000C795C  3C C0 80 0D */	lis r6, abortConnCallback@ha
/* 800CCA60 000C7960  38 60 00 62 */	li r3, 0x62
/* 800CCA64 000C7964  38 C6 C4 D8 */	addi r6, r6, abortConnCallback@l
/* 800CCA68 000C7968  39 00 00 38 */	li r8, 0x38
/* 800CCA6C 000C796C  38 E0 00 17 */	li r7, 0x17
/* 800CCA70 000C7970  38 00 00 06 */	li r0, 6
/* 800CCA74 000C7974  90 61 00 14 */	stw r3, 0x14(r1)
/* 800CCA78 000C7978  38 61 00 E4 */	addi r3, r1, 0xe4
/* 800CCA7C 000C797C  38 81 00 14 */	addi r4, r1, 0x14
/* 800CCA80 000C7980  38 A0 00 04 */	li r5, 4
/* 800CCA84 000C7984  B1 01 00 0A */	sth r8, 0xa(r1)
/* 800CCA88 000C7988  90 E1 00 E0 */	stw r7, 0xe0(r1)
/* 800CCA8C 000C798C  B0 01 00 FA */	sth r0, 0xfa(r1)
/* 800CCA90 000C7990  90 C1 01 0C */	stw r6, 0x10c(r1)
/* 800CCA94 000C7994  4B F3 75 6D */	bl memcpy
/* 800CCA98 000C7998  38 61 00 E8 */	addi r3, r1, 0xe8
/* 800CCA9C 000C799C  38 81 00 0A */	addi r4, r1, 0xa
/* 800CCAA0 000C79A0  38 A0 00 02 */	li r5, 2
/* 800CCAA4 000C79A4  4B F3 75 5D */	bl memcpy
/* 800CCAA8 000C79A8  A0 01 00 0A */	lhz r0, 0xa(r1)
/* 800CCAAC 000C79AC  3B 7D 09 34 */	addi r27, r29, 0x934
/* 800CCAB0 000C79B0  81 81 00 14 */	lwz r12, 0x14(r1)
/* 800CCAB4 000C79B4  B0 01 01 00 */	sth r0, 0x100(r1)
/* 800CCAB8 000C79B8  81 61 00 E0 */	lwz r11, 0xe0(r1)
/* 800CCABC 000C79BC  81 41 00 E4 */	lwz r10, 0xe4(r1)
/* 800CCAC0 000C79C0  81 21 00 E8 */	lwz r9, 0xe8(r1)
/* 800CCAC4 000C79C4  81 01 00 EC */	lwz r8, 0xec(r1)
/* 800CCAC8 000C79C8  80 E1 00 F0 */	lwz r7, 0xf0(r1)
/* 800CCACC 000C79CC  80 C1 00 F4 */	lwz r6, 0xf4(r1)
/* 800CCAD0 000C79D0  80 A1 00 F8 */	lwz r5, 0xf8(r1)
/* 800CCAD4 000C79D4  80 81 01 00 */	lwz r4, 0x100(r1)
/* 800CCAD8 000C79D8  80 61 01 08 */	lwz r3, 0x108(r1)
/* 800CCADC 000C79DC  80 01 01 0C */	lwz r0, 0x10c(r1)
/* 800CCAE0 000C79E0  93 61 00 FC */	stw r27, 0xfc(r1)
/* 800CCAE4 000C79E4  91 81 01 04 */	stw r12, 0x104(r1)
/* 800CCAE8 000C79E8  91 61 01 10 */	stw r11, 0x110(r1)
/* 800CCAEC 000C79EC  91 41 01 14 */	stw r10, 0x114(r1)
/* 800CCAF0 000C79F0  91 21 01 18 */	stw r9, 0x118(r1)
/* 800CCAF4 000C79F4  91 01 01 1C */	stw r8, 0x11c(r1)
/* 800CCAF8 000C79F8  90 E1 01 20 */	stw r7, 0x120(r1)
/* 800CCAFC 000C79FC  90 C1 01 24 */	stw r6, 0x124(r1)
/* 800CCB00 000C7A00  90 A1 01 28 */	stw r5, 0x128(r1)
/* 800CCB04 000C7A04  93 61 01 2C */	stw r27, 0x12c(r1)
/* 800CCB08 000C7A08  90 81 01 30 */	stw r4, 0x130(r1)
/* 800CCB0C 000C7A0C  91 81 01 34 */	stw r12, 0x134(r1)
/* 800CCB10 000C7A10  90 61 01 38 */	stw r3, 0x138(r1)
/* 800CCB14 000C7A14  90 01 01 3C */	stw r0, 0x13c(r1)
/* 800CCB18 000C7A18  48 02 4D A9 */	bl OSDisableInterrupts
/* 800CCB1C 000C7A1C  7C 7E 1B 78 */	mr r30, r3
/* 800CCB20 000C7A20  48 02 4D A1 */	bl OSDisableInterrupts
/* 800CCB24 000C7A24  88 9D 01 60 */	lbz r4, 0x160(r29)
/* 800CCB28 000C7A28  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800CCB2C 000C7A2C  7C 04 00 50 */	subf r0, r4, r0
/* 800CCB30 000C7A30  7C 1A 07 75 */	extsb. r26, r0
/* 800CCB34 000C7A34  40 80 00 10 */	bge lbl_800CCB44
/* 800CCB38 000C7A38  80 1D 01 68 */	lwz r0, 0x168(r29)
/* 800CCB3C 000C7A3C  7C 1A 02 14 */	add r0, r26, r0
/* 800CCB40 000C7A40  7C 1A 07 74 */	extsb r26, r0
lbl_800CCB44:
/* 800CCB44 000C7A44  48 02 4D A5 */	bl OSRestoreInterrupts
/* 800CCB48 000C7A48  80 7D 01 68 */	lwz r3, 0x168(r29)
/* 800CCB4C 000C7A4C  38 03 FF FF */	addi r0, r3, -1
/* 800CCB50 000C7A50  7C 00 D0 40 */	cmplw r0, r26
/* 800CCB54 000C7A54  40 82 00 10 */	bne lbl_800CCB64
/* 800CCB58 000C7A58  7F C3 F3 78 */	mr r3, r30
/* 800CCB5C 000C7A5C  48 02 4D 8D */	bl OSRestoreInterrupts
/* 800CCB60 000C7A60  48 00 00 78 */	b lbl_800CCBD8
lbl_800CCB64:
/* 800CCB64 000C7A64  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800CCB68 000C7A68  38 80 00 00 */	li r4, 0
/* 800CCB6C 000C7A6C  80 7D 01 64 */	lwz r3, 0x164(r29)
/* 800CCB70 000C7A70  38 A0 00 30 */	li r5, 0x30
/* 800CCB74 000C7A74  7C 00 07 74 */	extsb r0, r0
/* 800CCB78 000C7A78  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CCB7C 000C7A7C  7C 63 02 14 */	add r3, r3, r0
/* 800CCB80 000C7A80  4B F3 75 85 */	bl memset
/* 800CCB84 000C7A84  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800CCB88 000C7A88  38 81 01 10 */	addi r4, r1, 0x110
/* 800CCB8C 000C7A8C  80 7D 01 64 */	lwz r3, 0x164(r29)
/* 800CCB90 000C7A90  38 A0 00 30 */	li r5, 0x30
/* 800CCB94 000C7A94  7C 00 07 74 */	extsb r0, r0
/* 800CCB98 000C7A98  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CCB9C 000C7A9C  7C 63 02 14 */	add r3, r3, r0
/* 800CCBA0 000C7AA0  4B F3 74 61 */	bl memcpy
/* 800CCBA4 000C7AA4  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800CCBA8 000C7AA8  7F C3 F3 78 */	mr r3, r30
/* 800CCBAC 000C7AAC  80 9D 01 68 */	lwz r4, 0x168(r29)
/* 800CCBB0 000C7AB0  7C 06 07 74 */	extsb r6, r0
/* 800CCBB4 000C7AB4  38 84 FF FF */	addi r4, r4, -1
/* 800CCBB8 000C7AB8  7C A4 30 50 */	subf r5, r4, r6
/* 800CCBBC 000C7ABC  38 06 00 01 */	addi r0, r6, 1
/* 800CCBC0 000C7AC0  7C 86 20 50 */	subf r4, r6, r4
/* 800CCBC4 000C7AC4  7C A4 20 F8 */	nor r4, r5, r4
/* 800CCBC8 000C7AC8  7C 84 FE 70 */	srawi r4, r4, 0x1f
/* 800CCBCC 000C7ACC  7C 00 20 78 */	andc r0, r0, r4
/* 800CCBD0 000C7AD0  98 1D 01 61 */	stb r0, 0x161(r29)
/* 800CCBD4 000C7AD4  48 02 4D 15 */	bl OSRestoreInterrupts
lbl_800CCBD8:
/* 800CCBD8 000C7AD8  3C C0 80 0D */	lis r6, setupCallback@ha
/* 800CCBDC 000C7ADC  38 E0 00 17 */	li r7, 0x17
/* 800CCBE0 000C7AE0  38 C6 C4 04 */	addi r6, r6, setupCallback@l
/* 800CCBE4 000C7AE4  38 00 00 06 */	li r0, 6
/* 800CCBE8 000C7AE8  93 81 00 10 */	stw r28, 0x10(r1)
/* 800CCBEC 000C7AEC  38 61 00 84 */	addi r3, r1, 0x84
/* 800CCBF0 000C7AF0  38 81 00 10 */	addi r4, r1, 0x10
/* 800CCBF4 000C7AF4  38 A0 00 04 */	li r5, 4
/* 800CCBF8 000C7AF8  B3 E1 00 08 */	sth r31, 8(r1)
/* 800CCBFC 000C7AFC  90 E1 00 80 */	stw r7, 0x80(r1)
/* 800CCC00 000C7B00  B0 01 00 9A */	sth r0, 0x9a(r1)
/* 800CCC04 000C7B04  90 C1 00 AC */	stw r6, 0xac(r1)
/* 800CCC08 000C7B08  4B F3 73 F9 */	bl memcpy
/* 800CCC0C 000C7B0C  38 61 00 88 */	addi r3, r1, 0x88
/* 800CCC10 000C7B10  38 81 00 08 */	addi r4, r1, 8
/* 800CCC14 000C7B14  38 A0 00 02 */	li r5, 2
/* 800CCC18 000C7B18  4B F3 73 E9 */	bl memcpy
/* 800CCC1C 000C7B1C  A0 01 00 08 */	lhz r0, 8(r1)
/* 800CCC20 000C7B20  3B 7D 09 34 */	addi r27, r29, 0x934
/* 800CCC24 000C7B24  81 81 00 10 */	lwz r12, 0x10(r1)
/* 800CCC28 000C7B28  B0 01 00 A0 */	sth r0, 0xa0(r1)
/* 800CCC2C 000C7B2C  81 61 00 80 */	lwz r11, 0x80(r1)
/* 800CCC30 000C7B30  81 41 00 84 */	lwz r10, 0x84(r1)
/* 800CCC34 000C7B34  81 21 00 88 */	lwz r9, 0x88(r1)
/* 800CCC38 000C7B38  81 01 00 8C */	lwz r8, 0x8c(r1)
/* 800CCC3C 000C7B3C  80 E1 00 90 */	lwz r7, 0x90(r1)
/* 800CCC40 000C7B40  80 C1 00 94 */	lwz r6, 0x94(r1)
/* 800CCC44 000C7B44  80 A1 00 98 */	lwz r5, 0x98(r1)
/* 800CCC48 000C7B48  80 81 00 A0 */	lwz r4, 0xa0(r1)
/* 800CCC4C 000C7B4C  80 61 00 A8 */	lwz r3, 0xa8(r1)
/* 800CCC50 000C7B50  80 01 00 AC */	lwz r0, 0xac(r1)
/* 800CCC54 000C7B54  93 61 00 9C */	stw r27, 0x9c(r1)
/* 800CCC58 000C7B58  91 81 00 A4 */	stw r12, 0xa4(r1)
/* 800CCC5C 000C7B5C  91 61 00 B0 */	stw r11, 0xb0(r1)
/* 800CCC60 000C7B60  91 41 00 B4 */	stw r10, 0xb4(r1)
/* 800CCC64 000C7B64  91 21 00 B8 */	stw r9, 0xb8(r1)
/* 800CCC68 000C7B68  91 01 00 BC */	stw r8, 0xbc(r1)
/* 800CCC6C 000C7B6C  90 E1 00 C0 */	stw r7, 0xc0(r1)
/* 800CCC70 000C7B70  90 C1 00 C4 */	stw r6, 0xc4(r1)
/* 800CCC74 000C7B74  90 A1 00 C8 */	stw r5, 0xc8(r1)
/* 800CCC78 000C7B78  93 61 00 CC */	stw r27, 0xcc(r1)
/* 800CCC7C 000C7B7C  90 81 00 D0 */	stw r4, 0xd0(r1)
/* 800CCC80 000C7B80  91 81 00 D4 */	stw r12, 0xd4(r1)
/* 800CCC84 000C7B84  90 61 00 D8 */	stw r3, 0xd8(r1)
/* 800CCC88 000C7B88  90 01 00 DC */	stw r0, 0xdc(r1)
/* 800CCC8C 000C7B8C  48 02 4C 35 */	bl OSDisableInterrupts
/* 800CCC90 000C7B90  7C 7A 1B 78 */	mr r26, r3
/* 800CCC94 000C7B94  48 02 4C 2D */	bl OSDisableInterrupts
/* 800CCC98 000C7B98  88 9D 01 60 */	lbz r4, 0x160(r29)
/* 800CCC9C 000C7B9C  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800CCCA0 000C7BA0  7C 04 00 50 */	subf r0, r4, r0
/* 800CCCA4 000C7BA4  7C 1B 07 75 */	extsb. r27, r0
/* 800CCCA8 000C7BA8  40 80 00 10 */	bge lbl_800CCCB8
/* 800CCCAC 000C7BAC  80 1D 01 68 */	lwz r0, 0x168(r29)
/* 800CCCB0 000C7BB0  7C 1B 02 14 */	add r0, r27, r0
/* 800CCCB4 000C7BB4  7C 1B 07 74 */	extsb r27, r0
lbl_800CCCB8:
/* 800CCCB8 000C7BB8  48 02 4C 31 */	bl OSRestoreInterrupts
/* 800CCCBC 000C7BBC  80 7D 01 68 */	lwz r3, 0x168(r29)
/* 800CCCC0 000C7BC0  38 03 FF FF */	addi r0, r3, -1
/* 800CCCC4 000C7BC4  7C 00 D8 40 */	cmplw r0, r27
/* 800CCCC8 000C7BC8  40 82 00 10 */	bne lbl_800CCCD8
/* 800CCCCC 000C7BCC  7F 43 D3 78 */	mr r3, r26
/* 800CCCD0 000C7BD0  48 02 4C 19 */	bl OSRestoreInterrupts
/* 800CCCD4 000C7BD4  48 00 00 78 */	b lbl_800CCD4C
lbl_800CCCD8:
/* 800CCCD8 000C7BD8  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800CCCDC 000C7BDC  38 80 00 00 */	li r4, 0
/* 800CCCE0 000C7BE0  80 7D 01 64 */	lwz r3, 0x164(r29)
/* 800CCCE4 000C7BE4  38 A0 00 30 */	li r5, 0x30
/* 800CCCE8 000C7BE8  7C 00 07 74 */	extsb r0, r0
/* 800CCCEC 000C7BEC  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CCCF0 000C7BF0  7C 63 02 14 */	add r3, r3, r0
/* 800CCCF4 000C7BF4  4B F3 74 11 */	bl memset
/* 800CCCF8 000C7BF8  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800CCCFC 000C7BFC  38 81 00 B0 */	addi r4, r1, 0xb0
/* 800CCD00 000C7C00  80 7D 01 64 */	lwz r3, 0x164(r29)
/* 800CCD04 000C7C04  38 A0 00 30 */	li r5, 0x30
/* 800CCD08 000C7C08  7C 00 07 74 */	extsb r0, r0
/* 800CCD0C 000C7C0C  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CCD10 000C7C10  7C 63 02 14 */	add r3, r3, r0
/* 800CCD14 000C7C14  4B F3 72 ED */	bl memcpy
/* 800CCD18 000C7C18  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800CCD1C 000C7C1C  7F 43 D3 78 */	mr r3, r26
/* 800CCD20 000C7C20  80 9D 01 68 */	lwz r4, 0x168(r29)
/* 800CCD24 000C7C24  7C 06 07 74 */	extsb r6, r0
/* 800CCD28 000C7C28  38 84 FF FF */	addi r4, r4, -1
/* 800CCD2C 000C7C2C  7C A4 30 50 */	subf r5, r4, r6
/* 800CCD30 000C7C30  38 06 00 01 */	addi r0, r6, 1
/* 800CCD34 000C7C34  7C 86 20 50 */	subf r4, r6, r4
/* 800CCD38 000C7C38  7C A4 20 F8 */	nor r4, r5, r4
/* 800CCD3C 000C7C3C  7C 84 FE 70 */	srawi r4, r4, 0x1f
/* 800CCD40 000C7C40  7C 00 20 78 */	andc r0, r0, r4
/* 800CCD44 000C7C44  98 1D 01 61 */	stb r0, 0x161(r29)
/* 800CCD48 000C7C48  48 02 4B A1 */	bl OSRestoreInterrupts
lbl_800CCD4C:
/* 800CCD4C 000C7C4C  39 60 00 00 */	li r11, 0
/* 800CCD50 000C7C50  38 00 00 01 */	li r0, 1
/* 800CCD54 000C7C54  B0 01 00 3A */	sth r0, 0x3a(r1)
/* 800CCD58 000C7C58  39 80 00 15 */	li r12, 0x15
/* 800CCD5C 000C7C5C  81 21 00 28 */	lwz r9, 0x28(r1)
/* 800CCD60 000C7C60  99 61 00 24 */	stb r11, 0x24(r1)
/* 800CCD64 000C7C64  81 01 00 2C */	lwz r8, 0x2c(r1)
/* 800CCD68 000C7C68  81 41 00 24 */	lwz r10, 0x24(r1)
/* 800CCD6C 000C7C6C  80 E1 00 30 */	lwz r7, 0x30(r1)
/* 800CCD70 000C7C70  80 C1 00 34 */	lwz r6, 0x34(r1)
/* 800CCD74 000C7C74  80 A1 00 38 */	lwz r5, 0x38(r1)
/* 800CCD78 000C7C78  80 81 00 3C */	lwz r4, 0x3c(r1)
/* 800CCD7C 000C7C7C  80 61 00 40 */	lwz r3, 0x40(r1)
/* 800CCD80 000C7C80  80 01 00 44 */	lwz r0, 0x44(r1)
/* 800CCD84 000C7C84  91 81 00 20 */	stw r12, 0x20(r1)
/* 800CCD88 000C7C88  91 61 00 4C */	stw r11, 0x4c(r1)
/* 800CCD8C 000C7C8C  91 61 00 48 */	stw r11, 0x48(r1)
/* 800CCD90 000C7C90  91 81 00 50 */	stw r12, 0x50(r1)
/* 800CCD94 000C7C94  91 41 00 54 */	stw r10, 0x54(r1)
/* 800CCD98 000C7C98  91 21 00 58 */	stw r9, 0x58(r1)
/* 800CCD9C 000C7C9C  91 01 00 5C */	stw r8, 0x5c(r1)
/* 800CCDA0 000C7CA0  90 E1 00 60 */	stw r7, 0x60(r1)
/* 800CCDA4 000C7CA4  90 C1 00 64 */	stw r6, 0x64(r1)
/* 800CCDA8 000C7CA8  90 A1 00 68 */	stw r5, 0x68(r1)
/* 800CCDAC 000C7CAC  90 81 00 6C */	stw r4, 0x6c(r1)
/* 800CCDB0 000C7CB0  90 61 00 70 */	stw r3, 0x70(r1)
/* 800CCDB4 000C7CB4  90 01 00 74 */	stw r0, 0x74(r1)
/* 800CCDB8 000C7CB8  91 61 00 78 */	stw r11, 0x78(r1)
/* 800CCDBC 000C7CBC  91 61 00 7C */	stw r11, 0x7c(r1)
/* 800CCDC0 000C7CC0  48 02 4B 01 */	bl OSDisableInterrupts
/* 800CCDC4 000C7CC4  7C 7A 1B 78 */	mr r26, r3
/* 800CCDC8 000C7CC8  48 02 4A F9 */	bl OSDisableInterrupts
/* 800CCDCC 000C7CCC  88 9D 01 60 */	lbz r4, 0x160(r29)
/* 800CCDD0 000C7CD0  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800CCDD4 000C7CD4  7C 04 00 50 */	subf r0, r4, r0
/* 800CCDD8 000C7CD8  7C 1B 07 75 */	extsb. r27, r0
/* 800CCDDC 000C7CDC  40 80 00 10 */	bge lbl_800CCDEC
/* 800CCDE0 000C7CE0  80 1D 01 68 */	lwz r0, 0x168(r29)
/* 800CCDE4 000C7CE4  7C 1B 02 14 */	add r0, r27, r0
/* 800CCDE8 000C7CE8  7C 1B 07 74 */	extsb r27, r0
lbl_800CCDEC:
/* 800CCDEC 000C7CEC  48 02 4A FD */	bl OSRestoreInterrupts
/* 800CCDF0 000C7CF0  80 7D 01 68 */	lwz r3, 0x168(r29)
/* 800CCDF4 000C7CF4  38 03 FF FF */	addi r0, r3, -1
/* 800CCDF8 000C7CF8  7C 00 D8 40 */	cmplw r0, r27
/* 800CCDFC 000C7CFC  40 82 00 10 */	bne lbl_800CCE0C
/* 800CCE00 000C7D00  7F 43 D3 78 */	mr r3, r26
/* 800CCE04 000C7D04  48 02 4A E5 */	bl OSRestoreInterrupts
/* 800CCE08 000C7D08  48 00 00 78 */	b lbl_800CCE80
lbl_800CCE0C:
/* 800CCE0C 000C7D0C  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800CCE10 000C7D10  38 80 00 00 */	li r4, 0
/* 800CCE14 000C7D14  80 7D 01 64 */	lwz r3, 0x164(r29)
/* 800CCE18 000C7D18  38 A0 00 30 */	li r5, 0x30
/* 800CCE1C 000C7D1C  7C 00 07 74 */	extsb r0, r0
/* 800CCE20 000C7D20  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CCE24 000C7D24  7C 63 02 14 */	add r3, r3, r0
/* 800CCE28 000C7D28  4B F3 72 DD */	bl memset
/* 800CCE2C 000C7D2C  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800CCE30 000C7D30  38 81 00 50 */	addi r4, r1, 0x50
/* 800CCE34 000C7D34  80 7D 01 64 */	lwz r3, 0x164(r29)
/* 800CCE38 000C7D38  38 A0 00 30 */	li r5, 0x30
/* 800CCE3C 000C7D3C  7C 00 07 74 */	extsb r0, r0
/* 800CCE40 000C7D40  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CCE44 000C7D44  7C 63 02 14 */	add r3, r3, r0
/* 800CCE48 000C7D48  4B F3 71 B9 */	bl memcpy
/* 800CCE4C 000C7D4C  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800CCE50 000C7D50  7F 43 D3 78 */	mr r3, r26
/* 800CCE54 000C7D54  80 9D 01 68 */	lwz r4, 0x168(r29)
/* 800CCE58 000C7D58  7C 06 07 74 */	extsb r6, r0
/* 800CCE5C 000C7D5C  38 84 FF FF */	addi r4, r4, -1
/* 800CCE60 000C7D60  7C A4 30 50 */	subf r5, r4, r6
/* 800CCE64 000C7D64  38 06 00 01 */	addi r0, r6, 1
/* 800CCE68 000C7D68  7C 86 20 50 */	subf r4, r6, r4
/* 800CCE6C 000C7D6C  7C A4 20 F8 */	nor r4, r5, r4
/* 800CCE70 000C7D70  7C 84 FE 70 */	srawi r4, r4, 0x1f
/* 800CCE74 000C7D74  7C 00 20 78 */	andc r0, r0, r4
/* 800CCE78 000C7D78  98 1D 01 61 */	stb r0, 0x161(r29)
/* 800CCE7C 000C7D7C  48 02 4A 6D */	bl OSRestoreInterrupts
lbl_800CCE80:
/* 800CCE80 000C7D80  39 61 02 80 */	addi r11, r1, 0x280
/* 800CCE84 000C7D84  4B FE 4F 09 */	bl _restgpr_26
/* 800CCE88 000C7D88  80 01 02 84 */	lwz r0, 0x284(r1)
/* 800CCE8C 000C7D8C  7C 08 03 A6 */	mtlr r0
/* 800CCE90 000C7D90  38 21 02 80 */	addi r1, r1, 0x280
/* 800CCE94 000C7D94  4E 80 00 20 */	blr 

.global WPADiRetrieveChannel
WPADiRetrieveChannel:
/* 800CCE98 000C7D98  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800CCE9C 000C7D9C  7C 08 02 A6 */	mflr r0
/* 800CCEA0 000C7DA0  90 01 00 24 */	stw r0, 0x24(r1)
/* 800CCEA4 000C7DA4  39 61 00 20 */	addi r11, r1, 0x20
/* 800CCEA8 000C7DA8  4B FE 4E 9D */	bl _savegpr_27
/* 800CCEAC 000C7DAC  48 03 60 0D */	bl _WUDGetDevAddr
/* 800CCEB0 000C7DB0  3F E0 80 43 */	lis r31, _scArray@ha
/* 800CCEB4 000C7DB4  7C 7C 1B 78 */	mr r28, r3
/* 800CCEB8 000C7DB8  3B FF 99 68 */	addi r31, r31, _scArray@l
/* 800CCEBC 000C7DBC  3B 60 00 00 */	li r27, 0
/* 800CCEC0 000C7DC0  3B C0 00 00 */	li r30, 0
/* 800CCEC4 000C7DC4  3B AD 9A 68 */	addi r29, r13, _chan_active_state-_SDA_BASE_
lbl_800CCEC8:
/* 800CCEC8 000C7DC8  7C 7E FA 14 */	add r3, r30, r31
/* 800CCECC 000C7DCC  7F 84 E3 78 */	mr r4, r28
/* 800CCED0 000C7DD0  38 63 02 BD */	addi r3, r3, 0x2bd
/* 800CCED4 000C7DD4  38 A0 00 06 */	li r5, 6
/* 800CCED8 000C7DD8  4B FE 80 45 */	bl memcmp
/* 800CCEDC 000C7DDC  2C 03 00 00 */	cmpwi r3, 0
/* 800CCEE0 000C7DE0  40 82 00 24 */	bne lbl_800CCF04
/* 800CCEE4 000C7DE4  88 1D 00 00 */	lbz r0, 0(r29)
/* 800CCEE8 000C7DE8  2C 00 00 00 */	cmpwi r0, 0
/* 800CCEEC 000C7DEC  40 82 00 18 */	bne lbl_800CCF04
/* 800CCEF0 000C7DF0  38 00 00 01 */	li r0, 1
/* 800CCEF4 000C7DF4  38 6D 9A 68 */	addi r3, r13, _chan_active_state-_SDA_BASE_
/* 800CCEF8 000C7DF8  7C 03 D9 AE */	stbx r0, r3, r27
/* 800CCEFC 000C7DFC  7F 63 DB 78 */	mr r3, r27
/* 800CCF00 000C7E00  48 00 00 80 */	b lbl_800CCF80
lbl_800CCF04:
/* 800CCF04 000C7E04  3B 7B 00 01 */	addi r27, r27, 1
/* 800CCF08 000C7E08  3B BD 00 01 */	addi r29, r29, 1
/* 800CCF0C 000C7E0C  2C 1B 00 04 */	cmpwi r27, 4
/* 800CCF10 000C7E10  3B DE 00 46 */	addi r30, r30, 0x46
/* 800CCF14 000C7E14  41 80 FF B4 */	blt lbl_800CCEC8
/* 800CCF18 000C7E18  38 00 00 04 */	li r0, 4
/* 800CCF1C 000C7E1C  3B A0 00 00 */	li r29, 0
/* 800CCF20 000C7E20  38 6D 9A 68 */	addi r3, r13, _chan_active_state-_SDA_BASE_
/* 800CCF24 000C7E24  7C 09 03 A6 */	mtctr r0
lbl_800CCF28:
/* 800CCF28 000C7E28  88 03 00 00 */	lbz r0, 0(r3)
/* 800CCF2C 000C7E2C  2C 00 00 00 */	cmpwi r0, 0
/* 800CCF30 000C7E30  40 82 00 40 */	bne lbl_800CCF70
/* 800CCF34 000C7E34  38 1D 00 0A */	addi r0, r29, 0xa
/* 800CCF38 000C7E38  3C 60 80 43 */	lis r3, _scArray@ha
/* 800CCF3C 000C7E3C  1C 00 00 46 */	mulli r0, r0, 0x46
/* 800CCF40 000C7E40  3B E0 00 01 */	li r31, 1
/* 800CCF44 000C7E44  38 63 99 68 */	addi r3, r3, _scArray@l
/* 800CCF48 000C7E48  38 8D 9A 68 */	addi r4, r13, _chan_active_state-_SDA_BASE_
/* 800CCF4C 000C7E4C  7C 63 02 14 */	add r3, r3, r0
/* 800CCF50 000C7E50  7F E4 E9 AE */	stbx r31, r4, r29
/* 800CCF54 000C7E54  7F 84 E3 78 */	mr r4, r28
/* 800CCF58 000C7E58  38 A0 00 06 */	li r5, 6
/* 800CCF5C 000C7E5C  38 63 00 01 */	addi r3, r3, 1
/* 800CCF60 000C7E60  4B F3 70 A1 */	bl memcpy
/* 800CCF64 000C7E64  9B ED 9A 71 */	stb r31, lbl_804BEDF1-_SDA_BASE_(r13)
/* 800CCF68 000C7E68  7F A3 EB 78 */	mr r3, r29
/* 800CCF6C 000C7E6C  48 00 00 14 */	b lbl_800CCF80
lbl_800CCF70:
/* 800CCF70 000C7E70  38 63 00 01 */	addi r3, r3, 1
/* 800CCF74 000C7E74  3B BD 00 01 */	addi r29, r29, 1
/* 800CCF78 000C7E78  42 00 FF B0 */	bdnz lbl_800CCF28
/* 800CCF7C 000C7E7C  38 60 FF FF */	li r3, -1
lbl_800CCF80:
/* 800CCF80 000C7E80  39 61 00 20 */	addi r11, r1, 0x20
/* 800CCF84 000C7E84  4B FE 4E 0D */	bl _restgpr_27
/* 800CCF88 000C7E88  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800CCF8C 000C7E8C  7C 08 03 A6 */	mtlr r0
/* 800CCF90 000C7E90  38 21 00 20 */	addi r1, r1, 0x20
/* 800CCF94 000C7E94  4E 80 00 20 */	blr 

.global WPADiConnCallback
WPADiConnCallback:
/* 800CCF98 000C7E98  94 21 FF 40 */	stwu r1, -0xc0(r1)
/* 800CCF9C 000C7E9C  7C 08 02 A6 */	mflr r0
/* 800CCFA0 000C7EA0  90 01 00 C4 */	stw r0, 0xc4(r1)
/* 800CCFA4 000C7EA4  39 61 00 C0 */	addi r11, r1, 0xc0
/* 800CCFA8 000C7EA8  4B FE 4D 99 */	bl _savegpr_26
/* 800CCFAC 000C7EAC  2C 04 00 00 */	cmpwi r4, 0
/* 800CCFB0 000C7EB0  3F E0 80 3A */	lis r31, lbl_80399470@ha
/* 800CCFB4 000C7EB4  7C 7A 1B 78 */	mr r26, r3
/* 800CCFB8 000C7EB8  3B FF 94 70 */	addi r31, r31, lbl_80399470@l
/* 800CCFBC 000C7EBC  41 82 01 E0 */	beq lbl_800CD19C
/* 800CCFC0 000C7EC0  38 7F 01 5C */	addi r3, r31, 0x15c
/* 800CCFC4 000C7EC4  4C C6 31 82 */	crclr 6
/* 800CCFC8 000C7EC8  48 00 A7 95 */	bl DEBUGPrint
/* 800CCFCC 000C7ECC  7F 43 D3 78 */	mr r3, r26
/* 800CCFD0 000C7ED0  4B FF FE C9 */	bl WPADiRetrieveChannel
/* 800CCFD4 000C7ED4  3C A0 80 41 */	lis r5, _wpdcb@ha
/* 800CCFD8 000C7ED8  3C 80 80 41 */	lis r4, lbl_80410640@ha
/* 800CCFDC 000C7EDC  38 84 06 40 */	addi r4, r4, lbl_80410640@l
/* 800CCFE0 000C7EE0  54 60 10 3A */	slwi r0, r3, 2
/* 800CCFE4 000C7EE4  38 A5 F6 30 */	addi r5, r5, _wpdcb@l
/* 800CCFE8 000C7EE8  7C 64 D1 AE */	stbx r3, r4, r26
/* 800CCFEC 000C7EEC  7F 85 00 2E */	lwzx r28, r5, r0
/* 800CCFF0 000C7EF0  4B FF EE 69 */	bl __ClearControlBlock
/* 800CCFF4 000C7EF4  9B 5C 08 C3 */	stb r26, 0x8c3(r28)
/* 800CCFF8 000C7EF8  39 60 00 00 */	li r11, 0
/* 800CCFFC 000C7EFC  3C C0 80 0D */	lis r6, firmwareCheckCallback@ha
/* 800CD000 000C7F00  39 40 00 01 */	li r10, 1
/* 800CD004 000C7F04  99 7C 08 C1 */	stb r11, 0x8c1(r28)
/* 800CD008 000C7F08  39 20 00 64 */	li r9, 0x64
/* 800CD00C 000C7F0C  38 C6 C5 BC */	addi r6, r6, firmwareCheckCallback@l
/* 800CD010 000C7F10  39 00 17 70 */	li r8, 0x1770
/* 800CD014 000C7F14  91 7C 08 B8 */	stw r11, 0x8b8(r28)
/* 800CD018 000C7F18  38 E0 00 17 */	li r7, 0x17
/* 800CD01C 000C7F1C  38 00 00 06 */	li r0, 6
/* 800CD020 000C7F20  38 61 00 14 */	addi r3, r1, 0x14
/* 800CD024 000C7F24  91 5C 08 D8 */	stw r10, 0x8d8(r28)
/* 800CD028 000C7F28  38 81 00 0C */	addi r4, r1, 0xc
/* 800CD02C 000C7F2C  38 A0 00 04 */	li r5, 4
/* 800CD030 000C7F30  91 7C 08 BC */	stw r11, 0x8bc(r28)
/* 800CD034 000C7F34  99 3C 09 83 */	stb r9, 0x983(r28)
/* 800CD038 000C7F38  99 7C 09 86 */	stb r11, 0x986(r28)
/* 800CD03C 000C7F3C  91 01 00 0C */	stw r8, 0xc(r1)
/* 800CD040 000C7F40  B1 41 00 08 */	sth r10, 8(r1)
/* 800CD044 000C7F44  90 E1 00 10 */	stw r7, 0x10(r1)
/* 800CD048 000C7F48  B0 01 00 2A */	sth r0, 0x2a(r1)
/* 800CD04C 000C7F4C  90 C1 00 3C */	stw r6, 0x3c(r1)
/* 800CD050 000C7F50  4B F3 6F B1 */	bl memcpy
/* 800CD054 000C7F54  38 61 00 18 */	addi r3, r1, 0x18
/* 800CD058 000C7F58  38 81 00 08 */	addi r4, r1, 8
/* 800CD05C 000C7F5C  38 A0 00 02 */	li r5, 2
/* 800CD060 000C7F60  4B F3 6F A1 */	bl memcpy
/* 800CD064 000C7F64  A0 01 00 08 */	lhz r0, 8(r1)
/* 800CD068 000C7F68  3B BC 09 34 */	addi r29, r28, 0x934
/* 800CD06C 000C7F6C  81 81 00 0C */	lwz r12, 0xc(r1)
/* 800CD070 000C7F70  B0 01 00 30 */	sth r0, 0x30(r1)
/* 800CD074 000C7F74  81 61 00 10 */	lwz r11, 0x10(r1)
/* 800CD078 000C7F78  81 41 00 14 */	lwz r10, 0x14(r1)
/* 800CD07C 000C7F7C  81 21 00 18 */	lwz r9, 0x18(r1)
/* 800CD080 000C7F80  81 01 00 1C */	lwz r8, 0x1c(r1)
/* 800CD084 000C7F84  80 E1 00 20 */	lwz r7, 0x20(r1)
/* 800CD088 000C7F88  80 C1 00 24 */	lwz r6, 0x24(r1)
/* 800CD08C 000C7F8C  80 A1 00 28 */	lwz r5, 0x28(r1)
/* 800CD090 000C7F90  80 81 00 30 */	lwz r4, 0x30(r1)
/* 800CD094 000C7F94  80 61 00 38 */	lwz r3, 0x38(r1)
/* 800CD098 000C7F98  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 800CD09C 000C7F9C  93 A1 00 2C */	stw r29, 0x2c(r1)
/* 800CD0A0 000C7FA0  91 81 00 34 */	stw r12, 0x34(r1)
/* 800CD0A4 000C7FA4  91 61 00 40 */	stw r11, 0x40(r1)
/* 800CD0A8 000C7FA8  91 41 00 44 */	stw r10, 0x44(r1)
/* 800CD0AC 000C7FAC  91 21 00 48 */	stw r9, 0x48(r1)
/* 800CD0B0 000C7FB0  91 01 00 4C */	stw r8, 0x4c(r1)
/* 800CD0B4 000C7FB4  90 E1 00 50 */	stw r7, 0x50(r1)
/* 800CD0B8 000C7FB8  90 C1 00 54 */	stw r6, 0x54(r1)
/* 800CD0BC 000C7FBC  90 A1 00 58 */	stw r5, 0x58(r1)
/* 800CD0C0 000C7FC0  93 A1 00 5C */	stw r29, 0x5c(r1)
/* 800CD0C4 000C7FC4  90 81 00 60 */	stw r4, 0x60(r1)
/* 800CD0C8 000C7FC8  91 81 00 64 */	stw r12, 0x64(r1)
/* 800CD0CC 000C7FCC  90 61 00 68 */	stw r3, 0x68(r1)
/* 800CD0D0 000C7FD0  90 01 00 6C */	stw r0, 0x6c(r1)
/* 800CD0D4 000C7FD4  48 02 47 ED */	bl OSDisableInterrupts
/* 800CD0D8 000C7FD8  7C 7D 1B 78 */	mr r29, r3
/* 800CD0DC 000C7FDC  48 02 47 E5 */	bl OSDisableInterrupts
/* 800CD0E0 000C7FE0  88 9C 01 60 */	lbz r4, 0x160(r28)
/* 800CD0E4 000C7FE4  88 1C 01 61 */	lbz r0, 0x161(r28)
/* 800CD0E8 000C7FE8  7C 04 00 50 */	subf r0, r4, r0
/* 800CD0EC 000C7FEC  7C 1E 07 75 */	extsb. r30, r0
/* 800CD0F0 000C7FF0  40 80 00 10 */	bge lbl_800CD100
/* 800CD0F4 000C7FF4  80 1C 01 68 */	lwz r0, 0x168(r28)
/* 800CD0F8 000C7FF8  7C 1E 02 14 */	add r0, r30, r0
/* 800CD0FC 000C7FFC  7C 1E 07 74 */	extsb r30, r0
lbl_800CD100:
/* 800CD100 000C8000  48 02 47 E9 */	bl OSRestoreInterrupts
/* 800CD104 000C8004  80 7C 01 68 */	lwz r3, 0x168(r28)
/* 800CD108 000C8008  38 03 FF FF */	addi r0, r3, -1
/* 800CD10C 000C800C  7C 00 F0 40 */	cmplw r0, r30
/* 800CD110 000C8010  40 82 00 10 */	bne lbl_800CD120
/* 800CD114 000C8014  7F A3 EB 78 */	mr r3, r29
/* 800CD118 000C8018  48 02 47 D1 */	bl OSRestoreInterrupts
/* 800CD11C 000C801C  48 00 00 78 */	b lbl_800CD194
lbl_800CD120:
/* 800CD120 000C8020  88 1C 01 61 */	lbz r0, 0x161(r28)
/* 800CD124 000C8024  38 80 00 00 */	li r4, 0
/* 800CD128 000C8028  80 7C 01 64 */	lwz r3, 0x164(r28)
/* 800CD12C 000C802C  38 A0 00 30 */	li r5, 0x30
/* 800CD130 000C8030  7C 00 07 74 */	extsb r0, r0
/* 800CD134 000C8034  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CD138 000C8038  7C 63 02 14 */	add r3, r3, r0
/* 800CD13C 000C803C  4B F3 6F C9 */	bl memset
/* 800CD140 000C8040  88 1C 01 61 */	lbz r0, 0x161(r28)
/* 800CD144 000C8044  38 81 00 40 */	addi r4, r1, 0x40
/* 800CD148 000C8048  80 7C 01 64 */	lwz r3, 0x164(r28)
/* 800CD14C 000C804C  38 A0 00 30 */	li r5, 0x30
/* 800CD150 000C8050  7C 00 07 74 */	extsb r0, r0
/* 800CD154 000C8054  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CD158 000C8058  7C 63 02 14 */	add r3, r3, r0
/* 800CD15C 000C805C  4B F3 6E A5 */	bl memcpy
/* 800CD160 000C8060  88 1C 01 61 */	lbz r0, 0x161(r28)
/* 800CD164 000C8064  7F A3 EB 78 */	mr r3, r29
/* 800CD168 000C8068  80 9C 01 68 */	lwz r4, 0x168(r28)
/* 800CD16C 000C806C  7C 06 07 74 */	extsb r6, r0
/* 800CD170 000C8070  38 84 FF FF */	addi r4, r4, -1
/* 800CD174 000C8074  7C A4 30 50 */	subf r5, r4, r6
/* 800CD178 000C8078  38 06 00 01 */	addi r0, r6, 1
/* 800CD17C 000C807C  7C 86 20 50 */	subf r4, r6, r4
/* 800CD180 000C8080  7C A4 20 F8 */	nor r4, r5, r4
/* 800CD184 000C8084  7C 84 FE 70 */	srawi r4, r4, 0x1f
/* 800CD188 000C8088  7C 00 20 78 */	andc r0, r0, r4
/* 800CD18C 000C808C  98 1C 01 61 */	stb r0, 0x161(r28)
/* 800CD190 000C8090  48 02 47 59 */	bl OSRestoreInterrupts
lbl_800CD194:
/* 800CD194 000C8094  48 02 F8 01 */	bl __VIResetRFIdle
/* 800CD198 000C8098  48 00 02 2C */	b lbl_800CD3C4
lbl_800CD19C:
/* 800CD19C 000C809C  38 7F 01 74 */	addi r3, r31, 0x174
/* 800CD1A0 000C80A0  4C C6 31 82 */	crclr 6
/* 800CD1A4 000C80A4  48 00 A5 B9 */	bl DEBUGPrint
/* 800CD1A8 000C80A8  3C 60 80 41 */	lis r3, lbl_80410640@ha
/* 800CD1AC 000C80AC  38 80 FF FF */	li r4, -1
/* 800CD1B0 000C80B0  38 63 06 40 */	addi r3, r3, lbl_80410640@l
/* 800CD1B4 000C80B4  7F A3 D0 AE */	lbzx r29, r3, r26
/* 800CD1B8 000C80B8  7F BD 07 74 */	extsb r29, r29
/* 800CD1BC 000C80BC  7C 83 D1 AE */	stbx r4, r3, r26
/* 800CD1C0 000C80C0  2C 1D FF FF */	cmpwi r29, -1
/* 800CD1C4 000C80C4  41 82 01 F4 */	beq lbl_800CD3B8
/* 800CD1C8 000C80C8  3C 60 80 41 */	lis r3, _wpdcb@ha
/* 800CD1CC 000C80CC  57 A0 10 3A */	slwi r0, r29, 2
/* 800CD1D0 000C80D0  38 63 F6 30 */	addi r3, r3, _wpdcb@l
/* 800CD1D4 000C80D4  7F 83 00 2E */	lwzx r28, r3, r0
/* 800CD1D8 000C80D8  90 9C 08 BC */	stw r4, 0x8bc(r28)
/* 800CD1DC 000C80DC  81 9C 08 9C */	lwz r12, 0x89c(r28)
/* 800CD1E0 000C80E0  2C 0C 00 00 */	cmpwi r12, 0
/* 800CD1E4 000C80E4  41 82 00 18 */	beq lbl_800CD1FC
/* 800CD1E8 000C80E8  7F A3 EB 78 */	mr r3, r29
/* 800CD1EC 000C80EC  38 80 FF FF */	li r4, -1
/* 800CD1F0 000C80F0  7D 89 03 A6 */	mtctr r12
/* 800CD1F4 000C80F4  4E 80 04 21 */	bctrl 
/* 800CD1F8 000C80F8  48 00 00 30 */	b lbl_800CD228
lbl_800CD1FC:
/* 800CD1FC 000C80FC  1C 1D 00 14 */	mulli r0, r29, 0x14
/* 800CD200 000C8100  3C 60 80 41 */	lis r3, _wmb@ha
/* 800CD204 000C8104  38 63 2D 40 */	addi r3, r3, _wmb@l
/* 800CD208 000C8108  7C 63 02 14 */	add r3, r3, r0
/* 800CD20C 000C810C  81 83 00 10 */	lwz r12, 0x10(r3)
/* 800CD210 000C8110  2C 0C 00 00 */	cmpwi r12, 0
/* 800CD214 000C8114  41 82 00 14 */	beq lbl_800CD228
/* 800CD218 000C8118  7F A3 EB 78 */	mr r3, r29
/* 800CD21C 000C811C  38 80 FF FF */	li r4, -1
/* 800CD220 000C8120  7D 89 03 A6 */	mtctr r12
/* 800CD224 000C8124  4E 80 04 21 */	bctrl 
lbl_800CD228:
/* 800CD228 000C8128  48 02 46 99 */	bl OSDisableInterrupts
/* 800CD22C 000C812C  7C 7B 1B 78 */	mr r27, r3
/* 800CD230 000C8130  48 02 46 91 */	bl OSDisableInterrupts
/* 800CD234 000C8134  88 9C 01 60 */	lbz r4, 0x160(r28)
/* 800CD238 000C8138  88 1C 01 61 */	lbz r0, 0x161(r28)
/* 800CD23C 000C813C  7C 04 00 50 */	subf r0, r4, r0
/* 800CD240 000C8140  7C 1E 07 75 */	extsb. r30, r0
/* 800CD244 000C8144  40 80 00 10 */	bge lbl_800CD254
/* 800CD248 000C8148  80 1C 01 68 */	lwz r0, 0x168(r28)
/* 800CD24C 000C814C  7C 1E 02 14 */	add r0, r30, r0
/* 800CD250 000C8150  7C 1E 07 74 */	extsb r30, r0
lbl_800CD254:
/* 800CD254 000C8154  48 02 46 95 */	bl OSRestoreInterrupts
/* 800CD258 000C8158  2C 1E 00 00 */	cmpwi r30, 0
/* 800CD25C 000C815C  40 82 00 14 */	bne lbl_800CD270
/* 800CD260 000C8160  7F 63 DB 78 */	mr r3, r27
/* 800CD264 000C8164  48 02 46 85 */	bl OSRestoreInterrupts
/* 800CD268 000C8168  3B C0 00 00 */	li r30, 0
/* 800CD26C 000C816C  48 00 00 30 */	b lbl_800CD29C
lbl_800CD270:
/* 800CD270 000C8170  88 1C 01 60 */	lbz r0, 0x160(r28)
/* 800CD274 000C8174  38 61 00 70 */	addi r3, r1, 0x70
/* 800CD278 000C8178  80 9C 01 64 */	lwz r4, 0x164(r28)
/* 800CD27C 000C817C  38 A0 00 30 */	li r5, 0x30
/* 800CD280 000C8180  7C 00 07 74 */	extsb r0, r0
/* 800CD284 000C8184  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CD288 000C8188  7C 84 02 14 */	add r4, r4, r0
/* 800CD28C 000C818C  4B F3 6D 75 */	bl memcpy
/* 800CD290 000C8190  7F 63 DB 78 */	mr r3, r27
/* 800CD294 000C8194  48 02 46 55 */	bl OSRestoreInterrupts
/* 800CD298 000C8198  3B C0 00 01 */	li r30, 1
lbl_800CD29C:
/* 800CD29C 000C819C  2C 1E 00 00 */	cmpwi r30, 0
/* 800CD2A0 000C81A0  41 82 00 B8 */	beq lbl_800CD358
/* 800CD2A4 000C81A4  81 81 00 9C */	lwz r12, 0x9c(r1)
/* 800CD2A8 000C81A8  2C 0C 00 00 */	cmpwi r12, 0
/* 800CD2AC 000C81AC  41 82 00 14 */	beq lbl_800CD2C0
/* 800CD2B0 000C81B0  7F A3 EB 78 */	mr r3, r29
/* 800CD2B4 000C81B4  38 80 FF FF */	li r4, -1
/* 800CD2B8 000C81B8  7D 89 03 A6 */	mtctr r12
/* 800CD2BC 000C81BC  4E 80 04 21 */	bctrl 
lbl_800CD2C0:
/* 800CD2C0 000C81C0  48 02 46 01 */	bl OSDisableInterrupts
/* 800CD2C4 000C81C4  7C 7A 1B 78 */	mr r26, r3
/* 800CD2C8 000C81C8  48 02 45 F9 */	bl OSDisableInterrupts
/* 800CD2CC 000C81CC  88 9C 01 60 */	lbz r4, 0x160(r28)
/* 800CD2D0 000C81D0  88 1C 01 61 */	lbz r0, 0x161(r28)
/* 800CD2D4 000C81D4  7C 04 00 50 */	subf r0, r4, r0
/* 800CD2D8 000C81D8  7C 1B 07 75 */	extsb. r27, r0
/* 800CD2DC 000C81DC  40 80 00 10 */	bge lbl_800CD2EC
/* 800CD2E0 000C81E0  80 1C 01 68 */	lwz r0, 0x168(r28)
/* 800CD2E4 000C81E4  7C 1B 02 14 */	add r0, r27, r0
/* 800CD2E8 000C81E8  7C 1B 07 74 */	extsb r27, r0
lbl_800CD2EC:
/* 800CD2EC 000C81EC  48 02 45 FD */	bl OSRestoreInterrupts
/* 800CD2F0 000C81F0  2C 1B 00 00 */	cmpwi r27, 0
/* 800CD2F4 000C81F4  40 82 00 10 */	bne lbl_800CD304
/* 800CD2F8 000C81F8  7F 43 D3 78 */	mr r3, r26
/* 800CD2FC 000C81FC  48 02 45 ED */	bl OSRestoreInterrupts
/* 800CD300 000C8200  48 00 00 58 */	b lbl_800CD358
lbl_800CD304:
/* 800CD304 000C8204  88 1C 01 60 */	lbz r0, 0x160(r28)
/* 800CD308 000C8208  38 80 00 00 */	li r4, 0
/* 800CD30C 000C820C  80 7C 01 64 */	lwz r3, 0x164(r28)
/* 800CD310 000C8210  38 A0 00 30 */	li r5, 0x30
/* 800CD314 000C8214  7C 00 07 74 */	extsb r0, r0
/* 800CD318 000C8218  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CD31C 000C821C  7C 63 02 14 */	add r3, r3, r0
/* 800CD320 000C8220  4B F3 6D E5 */	bl memset
/* 800CD324 000C8224  88 1C 01 60 */	lbz r0, 0x160(r28)
/* 800CD328 000C8228  7F 43 D3 78 */	mr r3, r26
/* 800CD32C 000C822C  80 9C 01 68 */	lwz r4, 0x168(r28)
/* 800CD330 000C8230  7C 06 07 74 */	extsb r6, r0
/* 800CD334 000C8234  38 84 FF FF */	addi r4, r4, -1
/* 800CD338 000C8238  7C A4 30 50 */	subf r5, r4, r6
/* 800CD33C 000C823C  38 06 00 01 */	addi r0, r6, 1
/* 800CD340 000C8240  7C 86 20 50 */	subf r4, r6, r4
/* 800CD344 000C8244  7C A4 20 F8 */	nor r4, r5, r4
/* 800CD348 000C8248  7C 84 FE 70 */	srawi r4, r4, 0x1f
/* 800CD34C 000C824C  7C 00 20 78 */	andc r0, r0, r4
/* 800CD350 000C8250  98 1C 01 60 */	stb r0, 0x160(r28)
/* 800CD354 000C8254  48 02 45 95 */	bl OSRestoreInterrupts
lbl_800CD358:
/* 800CD358 000C8258  2C 1E 00 00 */	cmpwi r30, 0
/* 800CD35C 000C825C  40 82 FE CC */	bne lbl_800CD228
/* 800CD360 000C8260  38 7F 01 90 */	addi r3, r31, 0x190
/* 800CD364 000C8264  4C C6 31 82 */	crclr 6
/* 800CD368 000C8268  48 00 A3 F5 */	bl DEBUGPrint
/* 800CD36C 000C826C  80 9C 08 AC */	lwz r4, 0x8ac(r28)
/* 800CD370 000C8270  2C 04 00 00 */	cmpwi r4, 0
/* 800CD374 000C8274  41 82 00 10 */	beq lbl_800CD384
/* 800CD378 000C8278  80 BC 08 B4 */	lwz r5, 0x8b4(r28)
/* 800CD37C 000C827C  7F A3 EB 78 */	mr r3, r29
/* 800CD380 000C8280  48 00 0D 21 */	bl WPADSetAutoSamplingBuf
lbl_800CD384:
/* 800CD384 000C8284  7F A3 EB 78 */	mr r3, r29
/* 800CD388 000C8288  4B FF EA D1 */	bl __ClearControlBlock
/* 800CD38C 000C828C  38 00 00 00 */	li r0, 0
/* 800CD390 000C8290  38 6D 9A 68 */	addi r3, r13, _chan_active_state-_SDA_BASE_
/* 800CD394 000C8294  7C 03 E9 AE */	stbx r0, r3, r29
/* 800CD398 000C8298  81 9C 08 A4 */	lwz r12, 0x8a4(r28)
/* 800CD39C 000C829C  2C 0C 00 00 */	cmpwi r12, 0
/* 800CD3A0 000C82A0  41 82 00 24 */	beq lbl_800CD3C4
/* 800CD3A4 000C82A4  7F A3 EB 78 */	mr r3, r29
/* 800CD3A8 000C82A8  38 80 FF FF */	li r4, -1
/* 800CD3AC 000C82AC  7D 89 03 A6 */	mtctr r12
/* 800CD3B0 000C82B0  4E 80 04 21 */	bctrl 
/* 800CD3B4 000C82B4  48 00 00 10 */	b lbl_800CD3C4
lbl_800CD3B8:
/* 800CD3B8 000C82B8  38 7F 01 A8 */	addi r3, r31, 0x1a8
/* 800CD3BC 000C82BC  4C C6 31 82 */	crclr 6
/* 800CD3C0 000C82C0  48 00 A3 9D */	bl DEBUGPrint
lbl_800CD3C4:
/* 800CD3C4 000C82C4  39 61 00 C0 */	addi r11, r1, 0xc0
/* 800CD3C8 000C82C8  4B FE 49 C5 */	bl _restgpr_26
/* 800CD3CC 000C82CC  80 01 00 C4 */	lwz r0, 0xc4(r1)
/* 800CD3D0 000C82D0  7C 08 03 A6 */	mtlr r0
/* 800CD3D4 000C82D4  38 21 00 C0 */	addi r1, r1, 0xc0
/* 800CD3D8 000C82D8  4E 80 00 20 */	blr 

.global WPADiRecvCallback
WPADiRecvCallback:
/* 800CD3DC 000C82DC  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800CD3E0 000C82E0  7C 08 02 A6 */	mflr r0
/* 800CD3E4 000C82E4  3C A0 80 41 */	lis r5, lbl_80410640@ha
/* 800CD3E8 000C82E8  90 01 00 14 */	stw r0, 0x14(r1)
/* 800CD3EC 000C82EC  38 A5 06 40 */	addi r5, r5, lbl_80410640@l
/* 800CD3F0 000C82F0  7C 05 18 AE */	lbzx r0, r5, r3
/* 800CD3F4 000C82F4  28 00 00 04 */	cmplwi r0, 4
/* 800CD3F8 000C82F8  41 81 00 2C */	bgt lbl_800CD424
/* 800CD3FC 000C82FC  7C 03 03 78 */	mr r3, r0
/* 800CD400 000C8300  48 00 56 89 */	bl WPADiHIDParser
/* 800CD404 000C8304  2C 03 00 00 */	cmpwi r3, 0
/* 800CD408 000C8308  7C 64 1B 78 */	mr r4, r3
/* 800CD40C 000C830C  41 82 00 2C */	beq lbl_800CD438
/* 800CD410 000C8310  3C 60 80 3A */	lis r3, lbl_80399660@ha
/* 800CD414 000C8314  38 63 96 60 */	addi r3, r3, lbl_80399660@l
/* 800CD418 000C8318  4C C6 31 82 */	crclr 6
/* 800CD41C 000C831C  48 00 A3 41 */	bl DEBUGPrint
/* 800CD420 000C8320  48 00 00 18 */	b lbl_800CD438
lbl_800CD424:
/* 800CD424 000C8324  3C 60 80 3A */	lis r3, lbl_80399678@ha
/* 800CD428 000C8328  7C 04 03 78 */	mr r4, r0
/* 800CD42C 000C832C  38 63 96 78 */	addi r3, r3, lbl_80399678@l
/* 800CD430 000C8330  4C C6 31 82 */	crclr 6
/* 800CD434 000C8334  48 00 A3 29 */	bl DEBUGPrint
lbl_800CD438:
/* 800CD438 000C8338  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800CD43C 000C833C  7C 08 03 A6 */	mtlr r0
/* 800CD440 000C8340  38 21 00 10 */	addi r1, r1, 0x10
/* 800CD444 000C8344  4E 80 00 20 */	blr 

.global WPADGetAccGravityUnit
WPADGetAccGravityUnit:
/* 800CD448 000C8348  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800CD44C 000C834C  7C 08 02 A6 */	mflr r0
/* 800CD450 000C8350  3C C0 80 41 */	lis r6, _wpdcb@ha
/* 800CD454 000C8354  90 01 00 24 */	stw r0, 0x24(r1)
/* 800CD458 000C8358  54 60 10 3A */	slwi r0, r3, 2
/* 800CD45C 000C835C  38 C6 F6 30 */	addi r6, r6, _wpdcb@l
/* 800CD460 000C8360  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800CD464 000C8364  7C BF 2B 78 */	mr r31, r5
/* 800CD468 000C8368  93 C1 00 18 */	stw r30, 0x18(r1)
/* 800CD46C 000C836C  93 A1 00 14 */	stw r29, 0x14(r1)
/* 800CD470 000C8370  7C 9D 23 78 */	mr r29, r4
/* 800CD474 000C8374  7F C6 00 2E */	lwzx r30, r6, r0
/* 800CD478 000C8378  48 02 44 49 */	bl OSDisableInterrupts
/* 800CD47C 000C837C  2C 1F 00 00 */	cmpwi r31, 0
/* 800CD480 000C8380  41 82 00 80 */	beq lbl_800CD500
/* 800CD484 000C8384  2C 1D 00 01 */	cmpwi r29, 1
/* 800CD488 000C8388  41 82 00 48 */	beq lbl_800CD4D0
/* 800CD48C 000C838C  40 80 00 74 */	bge lbl_800CD500
/* 800CD490 000C8390  2C 1D 00 00 */	cmpwi r29, 0
/* 800CD494 000C8394  40 80 00 08 */	bge lbl_800CD49C
/* 800CD498 000C8398  48 00 00 68 */	b lbl_800CD500
lbl_800CD49C:
/* 800CD49C 000C839C  A8 9E 08 74 */	lha r4, 0x874(r30)
/* 800CD4A0 000C83A0  A8 1E 08 7A */	lha r0, 0x87a(r30)
/* 800CD4A4 000C83A4  7C 04 00 50 */	subf r0, r4, r0
/* 800CD4A8 000C83A8  B0 1F 00 00 */	sth r0, 0(r31)
/* 800CD4AC 000C83AC  A8 9E 08 76 */	lha r4, 0x876(r30)
/* 800CD4B0 000C83B0  A8 1E 08 7C */	lha r0, 0x87c(r30)
/* 800CD4B4 000C83B4  7C 04 00 50 */	subf r0, r4, r0
/* 800CD4B8 000C83B8  B0 1F 00 02 */	sth r0, 2(r31)
/* 800CD4BC 000C83BC  A8 9E 08 78 */	lha r4, 0x878(r30)
/* 800CD4C0 000C83C0  A8 1E 08 7E */	lha r0, 0x87e(r30)
/* 800CD4C4 000C83C4  7C 04 00 50 */	subf r0, r4, r0
/* 800CD4C8 000C83C8  B0 1F 00 04 */	sth r0, 4(r31)
/* 800CD4CC 000C83CC  48 00 00 34 */	b lbl_800CD500
lbl_800CD4D0:
/* 800CD4D0 000C83D0  A8 9E 08 8E */	lha r4, 0x88e(r30)
/* 800CD4D4 000C83D4  A8 1E 08 94 */	lha r0, 0x894(r30)
/* 800CD4D8 000C83D8  7C 04 00 50 */	subf r0, r4, r0
/* 800CD4DC 000C83DC  B0 1F 00 00 */	sth r0, 0(r31)
/* 800CD4E0 000C83E0  A8 9E 08 90 */	lha r4, 0x890(r30)
/* 800CD4E4 000C83E4  A8 1E 08 96 */	lha r0, 0x896(r30)
/* 800CD4E8 000C83E8  7C 04 00 50 */	subf r0, r4, r0
/* 800CD4EC 000C83EC  B0 1F 00 02 */	sth r0, 2(r31)
/* 800CD4F0 000C83F0  A8 9E 08 92 */	lha r4, 0x892(r30)
/* 800CD4F4 000C83F4  A8 1E 08 98 */	lha r0, 0x898(r30)
/* 800CD4F8 000C83F8  7C 04 00 50 */	subf r0, r4, r0
/* 800CD4FC 000C83FC  B0 1F 00 04 */	sth r0, 4(r31)
lbl_800CD500:
/* 800CD500 000C8400  48 02 43 E9 */	bl OSRestoreInterrupts
/* 800CD504 000C8404  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800CD508 000C8408  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800CD50C 000C840C  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 800CD510 000C8410  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 800CD514 000C8414  7C 08 03 A6 */	mtlr r0
/* 800CD518 000C8418  38 21 00 20 */	addi r1, r1, 0x20
/* 800CD51C 000C841C  4E 80 00 20 */	blr 

.global CloseCallback
CloseCallback:
/* 800CD520 000C8420  3C A0 80 41 */	lis r5, _wpdcb@ha
/* 800CD524 000C8424  2C 04 FF FF */	cmpwi r4, -1
/* 800CD528 000C8428  54 60 10 3A */	slwi r0, r3, 2
/* 800CD52C 000C842C  38 A5 F6 30 */	addi r5, r5, _wpdcb@l
/* 800CD530 000C8430  7C 65 00 2E */	lwzx r3, r5, r0
/* 800CD534 000C8434  4D 82 00 20 */	beqlr 
/* 800CD538 000C8438  88 63 08 C3 */	lbz r3, 0x8c3(r3)
/* 800CD53C 000C843C  48 04 68 A8 */	b lbl_80113DE4
/* 800CD540 000C8440  4E 80 00 20 */	blr 

.global WPADDisconnect
WPADDisconnect:
/* 800CD544 000C8444  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800CD548 000C8448  7C 08 02 A6 */	mflr r0
/* 800CD54C 000C844C  3C A0 80 43 */	lis r5, _scArray@ha
/* 800CD550 000C8450  38 80 00 00 */	li r4, 0
/* 800CD554 000C8454  90 01 00 24 */	stw r0, 0x24(r1)
/* 800CD558 000C8458  38 03 00 0A */	addi r0, r3, 0xa
/* 800CD55C 000C845C  1C 00 00 46 */	mulli r0, r0, 0x46
/* 800CD560 000C8460  38 A5 99 68 */	addi r5, r5, _scArray@l
/* 800CD564 000C8464  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800CD568 000C8468  93 C1 00 18 */	stw r30, 0x18(r1)
/* 800CD56C 000C846C  93 A1 00 14 */	stw r29, 0x14(r1)
/* 800CD570 000C8470  93 81 00 10 */	stw r28, 0x10(r1)
/* 800CD574 000C8474  7C 7C 1B 78 */	mr r28, r3
/* 800CD578 000C8478  7C 65 02 14 */	add r3, r5, r0
/* 800CD57C 000C847C  38 A0 00 46 */	li r5, 0x46
/* 800CD580 000C8480  38 63 00 01 */	addi r3, r3, 1
/* 800CD584 000C8484  4B F3 6B 81 */	bl memset
/* 800CD588 000C8488  3C 60 80 41 */	lis r3, _wpdcb@ha
/* 800CD58C 000C848C  3B E0 00 01 */	li r31, 1
/* 800CD590 000C8490  57 80 10 3A */	slwi r0, r28, 2
/* 800CD594 000C8494  9B ED 9A 71 */	stb r31, lbl_804BEDF1-_SDA_BASE_(r13)
/* 800CD598 000C8498  38 63 F6 30 */	addi r3, r3, _wpdcb@l
/* 800CD59C 000C849C  7F A3 00 2E */	lwzx r29, r3, r0
/* 800CD5A0 000C84A0  48 02 43 21 */	bl OSDisableInterrupts
/* 800CD5A4 000C84A4  83 DD 08 BC */	lwz r30, 0x8bc(r29)
/* 800CD5A8 000C84A8  48 02 43 41 */	bl OSRestoreInterrupts
/* 800CD5AC 000C84AC  2C 1E FF FF */	cmpwi r30, -1
/* 800CD5B0 000C84B0  41 82 00 38 */	beq lbl_800CD5E8
/* 800CD5B4 000C84B4  48 02 43 0D */	bl OSDisableInterrupts
/* 800CD5B8 000C84B8  88 1D 09 86 */	lbz r0, 0x986(r29)
/* 800CD5BC 000C84BC  2C 00 00 00 */	cmpwi r0, 0
/* 800CD5C0 000C84C0  41 82 00 0C */	beq lbl_800CD5CC
/* 800CD5C4 000C84C4  48 02 43 25 */	bl OSRestoreInterrupts
/* 800CD5C8 000C84C8  48 00 00 20 */	b lbl_800CD5E8
lbl_800CD5CC:
/* 800CD5CC 000C84CC  9B FD 09 86 */	stb r31, 0x986(r29)
/* 800CD5D0 000C84D0  48 02 43 19 */	bl OSRestoreInterrupts
/* 800CD5D4 000C84D4  3C A0 80 0D */	lis r5, CloseCallback@ha
/* 800CD5D8 000C84D8  7F 83 E3 78 */	mr r3, r28
/* 800CD5DC 000C84DC  38 A5 D5 20 */	addi r5, r5, CloseCallback@l
/* 800CD5E0 000C84E0  38 80 00 00 */	li r4, 0
/* 800CD5E4 000C84E4  48 00 06 89 */	bl WPADControlLed
lbl_800CD5E8:
/* 800CD5E8 000C84E8  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800CD5EC 000C84EC  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800CD5F0 000C84F0  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 800CD5F4 000C84F4  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 800CD5F8 000C84F8  83 81 00 10 */	lwz r28, 0x10(r1)
/* 800CD5FC 000C84FC  7C 08 03 A6 */	mtlr r0
/* 800CD600 000C8500  38 21 00 20 */	addi r1, r1, 0x20
/* 800CD604 000C8504  4E 80 00 20 */	blr 

.global WPADProbe
WPADProbe:
/* 800CD608 000C8508  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800CD60C 000C850C  7C 08 02 A6 */	mflr r0
/* 800CD610 000C8510  3C A0 80 41 */	lis r5, _wpdcb@ha
/* 800CD614 000C8514  90 01 00 14 */	stw r0, 0x14(r1)
/* 800CD618 000C8518  54 60 10 3A */	slwi r0, r3, 2
/* 800CD61C 000C851C  38 A5 F6 30 */	addi r5, r5, _wpdcb@l
/* 800CD620 000C8520  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800CD624 000C8524  93 C1 00 08 */	stw r30, 8(r1)
/* 800CD628 000C8528  7C 9E 23 78 */	mr r30, r4
/* 800CD62C 000C852C  7F E5 00 2E */	lwzx r31, r5, r0
/* 800CD630 000C8530  48 02 42 91 */	bl OSDisableInterrupts
/* 800CD634 000C8534  2C 1E 00 00 */	cmpwi r30, 0
/* 800CD638 000C8538  41 82 00 0C */	beq lbl_800CD644
/* 800CD63C 000C853C  88 1F 08 C1 */	lbz r0, 0x8c1(r31)
/* 800CD640 000C8540  90 1E 00 00 */	stw r0, 0(r30)
lbl_800CD644:
/* 800CD644 000C8544  83 DF 08 BC */	lwz r30, 0x8bc(r31)
/* 800CD648 000C8548  2C 1E FF FF */	cmpwi r30, -1
/* 800CD64C 000C854C  41 82 00 28 */	beq lbl_800CD674
/* 800CD650 000C8550  88 1F 08 C1 */	lbz r0, 0x8c1(r31)
/* 800CD654 000C8554  28 00 00 FD */	cmplwi r0, 0xfd
/* 800CD658 000C8558  40 82 00 0C */	bne lbl_800CD664
/* 800CD65C 000C855C  3B C0 FF FF */	li r30, -1
/* 800CD660 000C8560  48 00 00 14 */	b lbl_800CD674
lbl_800CD664:
/* 800CD664 000C8564  80 1F 08 DC */	lwz r0, 0x8dc(r31)
/* 800CD668 000C8568  2C 00 00 00 */	cmpwi r0, 0
/* 800CD66C 000C856C  40 82 00 08 */	bne lbl_800CD674
/* 800CD670 000C8570  3B C0 FF FE */	li r30, -2
lbl_800CD674:
/* 800CD674 000C8574  48 02 42 75 */	bl OSRestoreInterrupts
/* 800CD678 000C8578  7F C3 F3 78 */	mr r3, r30
/* 800CD67C 000C857C  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 800CD680 000C8580  83 C1 00 08 */	lwz r30, 8(r1)
/* 800CD684 000C8584  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800CD688 000C8588  7C 08 03 A6 */	mtlr r0
/* 800CD68C 000C858C  38 21 00 10 */	addi r1, r1, 0x10
/* 800CD690 000C8590  4E 80 00 20 */	blr 

.global WPADSetSamplingCallback
WPADSetSamplingCallback:
/* 800CD694 000C8594  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800CD698 000C8598  7C 08 02 A6 */	mflr r0
/* 800CD69C 000C859C  3C A0 80 3A */	lis r5, lbl_803996A4@ha
/* 800CD6A0 000C85A0  90 01 00 14 */	stw r0, 0x14(r1)
/* 800CD6A4 000C85A4  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800CD6A8 000C85A8  7C 7F 1B 78 */	mr r31, r3
/* 800CD6AC 000C85AC  38 65 96 A4 */	addi r3, r5, lbl_803996A4@l
/* 800CD6B0 000C85B0  93 C1 00 08 */	stw r30, 8(r1)
/* 800CD6B4 000C85B4  7C 9E 23 78 */	mr r30, r4
/* 800CD6B8 000C85B8  4C C6 31 82 */	crclr 6
/* 800CD6BC 000C85BC  48 00 A0 A1 */	bl DEBUGPrint
/* 800CD6C0 000C85C0  48 02 42 01 */	bl OSDisableInterrupts
/* 800CD6C4 000C85C4  3C 80 80 41 */	lis r4, _wpdcb@ha
/* 800CD6C8 000C85C8  57 E0 10 3A */	slwi r0, r31, 2
/* 800CD6CC 000C85CC  38 84 F6 30 */	addi r4, r4, _wpdcb@l
/* 800CD6D0 000C85D0  7C 84 00 2E */	lwzx r4, r4, r0
/* 800CD6D4 000C85D4  83 E4 08 A8 */	lwz r31, 0x8a8(r4)
/* 800CD6D8 000C85D8  93 C4 08 A8 */	stw r30, 0x8a8(r4)
/* 800CD6DC 000C85DC  48 02 42 0D */	bl OSRestoreInterrupts
/* 800CD6E0 000C85E0  7F E3 FB 78 */	mr r3, r31
/* 800CD6E4 000C85E4  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 800CD6E8 000C85E8  83 C1 00 08 */	lwz r30, 8(r1)
/* 800CD6EC 000C85EC  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800CD6F0 000C85F0  7C 08 03 A6 */	mtlr r0
/* 800CD6F4 000C85F4  38 21 00 10 */	addi r1, r1, 0x10
/* 800CD6F8 000C85F8  4E 80 00 20 */	blr 

.global WPADSetConnectCallback
WPADSetConnectCallback:
/* 800CD6FC 000C85FC  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800CD700 000C8600  7C 08 02 A6 */	mflr r0
/* 800CD704 000C8604  3C A0 80 3A */	lis r5, lbl_803996C0@ha
/* 800CD708 000C8608  90 01 00 14 */	stw r0, 0x14(r1)
/* 800CD70C 000C860C  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800CD710 000C8610  7C 7F 1B 78 */	mr r31, r3
/* 800CD714 000C8614  38 65 96 C0 */	addi r3, r5, lbl_803996C0@l
/* 800CD718 000C8618  93 C1 00 08 */	stw r30, 8(r1)
/* 800CD71C 000C861C  7C 9E 23 78 */	mr r30, r4
/* 800CD720 000C8620  4C C6 31 82 */	crclr 6
/* 800CD724 000C8624  48 00 A0 39 */	bl DEBUGPrint
/* 800CD728 000C8628  48 02 41 99 */	bl OSDisableInterrupts
/* 800CD72C 000C862C  3C 80 80 41 */	lis r4, _wpdcb@ha
/* 800CD730 000C8630  57 E0 10 3A */	slwi r0, r31, 2
/* 800CD734 000C8634  38 84 F6 30 */	addi r4, r4, _wpdcb@l
/* 800CD738 000C8638  7C 84 00 2E */	lwzx r4, r4, r0
/* 800CD73C 000C863C  83 E4 08 A4 */	lwz r31, 0x8a4(r4)
/* 800CD740 000C8640  93 C4 08 A4 */	stw r30, 0x8a4(r4)
/* 800CD744 000C8644  48 02 41 A5 */	bl OSRestoreInterrupts
/* 800CD748 000C8648  7F E3 FB 78 */	mr r3, r31
/* 800CD74C 000C864C  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 800CD750 000C8650  83 C1 00 08 */	lwz r30, 8(r1)
/* 800CD754 000C8654  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800CD758 000C8658  7C 08 03 A6 */	mtlr r0
/* 800CD75C 000C865C  38 21 00 10 */	addi r1, r1, 0x10
/* 800CD760 000C8660  4E 80 00 20 */	blr 

.global WPADSetExtensionCallback
WPADSetExtensionCallback:
/* 800CD764 000C8664  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800CD768 000C8668  7C 08 02 A6 */	mflr r0
/* 800CD76C 000C866C  3C A0 80 3A */	lis r5, lbl_803996DC@ha
/* 800CD770 000C8670  90 01 00 14 */	stw r0, 0x14(r1)
/* 800CD774 000C8674  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800CD778 000C8678  7C 7F 1B 78 */	mr r31, r3
/* 800CD77C 000C867C  38 65 96 DC */	addi r3, r5, lbl_803996DC@l
/* 800CD780 000C8680  93 C1 00 08 */	stw r30, 8(r1)
/* 800CD784 000C8684  7C 9E 23 78 */	mr r30, r4
/* 800CD788 000C8688  4C C6 31 82 */	crclr 6
/* 800CD78C 000C868C  48 00 9F D1 */	bl DEBUGPrint
/* 800CD790 000C8690  48 02 41 31 */	bl OSDisableInterrupts
/* 800CD794 000C8694  3C 80 80 41 */	lis r4, _wpdcb@ha
/* 800CD798 000C8698  57 E0 10 3A */	slwi r0, r31, 2
/* 800CD79C 000C869C  38 84 F6 30 */	addi r4, r4, _wpdcb@l
/* 800CD7A0 000C86A0  7C 84 00 2E */	lwzx r4, r4, r0
/* 800CD7A4 000C86A4  83 E4 08 A0 */	lwz r31, 0x8a0(r4)
/* 800CD7A8 000C86A8  93 C4 08 A0 */	stw r30, 0x8a0(r4)
/* 800CD7AC 000C86AC  48 02 41 3D */	bl OSRestoreInterrupts
/* 800CD7B0 000C86B0  7F E3 FB 78 */	mr r3, r31
/* 800CD7B4 000C86B4  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 800CD7B8 000C86B8  83 C1 00 08 */	lwz r30, 8(r1)
/* 800CD7BC 000C86BC  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800CD7C0 000C86C0  7C 08 03 A6 */	mtlr r0
/* 800CD7C4 000C86C4  38 21 00 10 */	addi r1, r1, 0x10
/* 800CD7C8 000C86C8  4E 80 00 20 */	blr 

.global WPADGetDataFormat
WPADGetDataFormat:
/* 800CD7CC 000C86CC  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800CD7D0 000C86D0  7C 08 02 A6 */	mflr r0
/* 800CD7D4 000C86D4  90 01 00 14 */	stw r0, 0x14(r1)
/* 800CD7D8 000C86D8  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800CD7DC 000C86DC  7C 7F 1B 78 */	mr r31, r3
/* 800CD7E0 000C86E0  48 02 40 E1 */	bl OSDisableInterrupts
/* 800CD7E4 000C86E4  3C 80 80 41 */	lis r4, _wpdcb@ha
/* 800CD7E8 000C86E8  57 E0 10 3A */	slwi r0, r31, 2
/* 800CD7EC 000C86EC  38 84 F6 30 */	addi r4, r4, _wpdcb@l
/* 800CD7F0 000C86F0  7C 84 00 2E */	lwzx r4, r4, r0
/* 800CD7F4 000C86F4  83 E4 08 B8 */	lwz r31, 0x8b8(r4)
/* 800CD7F8 000C86F8  48 02 40 F1 */	bl OSRestoreInterrupts
/* 800CD7FC 000C86FC  7F E3 FB 78 */	mr r3, r31
/* 800CD800 000C8700  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 800CD804 000C8704  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800CD808 000C8708  7C 08 03 A6 */	mtlr r0
/* 800CD80C 000C870C  38 21 00 10 */	addi r1, r1, 0x10
/* 800CD810 000C8710  4E 80 00 20 */	blr 

.global WPADSetDataFormat
WPADSetDataFormat:
/* 800CD814 000C8714  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800CD818 000C8718  7C 08 02 A6 */	mflr r0
/* 800CD81C 000C871C  90 01 00 24 */	stw r0, 0x24(r1)
/* 800CD820 000C8720  39 61 00 20 */	addi r11, r1, 0x20
/* 800CD824 000C8724  4B FE 45 21 */	bl _savegpr_27
/* 800CD828 000C8728  3C A0 80 41 */	lis r5, _wpdcb@ha
/* 800CD82C 000C872C  54 60 10 3A */	slwi r0, r3, 2
/* 800CD830 000C8730  38 A5 F6 30 */	addi r5, r5, _wpdcb@l
/* 800CD834 000C8734  7C 9B 23 78 */	mr r27, r4
/* 800CD838 000C8738  7F E5 00 2E */	lwzx r31, r5, r0
/* 800CD83C 000C873C  48 02 40 85 */	bl OSDisableInterrupts
/* 800CD840 000C8740  83 BF 08 DC */	lwz r29, 0x8dc(r31)
/* 800CD844 000C8744  83 DF 08 BC */	lwz r30, 0x8bc(r31)
/* 800CD848 000C8748  83 9F 08 B8 */	lwz r28, 0x8b8(r31)
/* 800CD84C 000C874C  48 02 40 9D */	bl OSRestoreInterrupts
/* 800CD850 000C8750  2C 1E FF FF */	cmpwi r30, -1
/* 800CD854 000C8754  41 82 00 54 */	beq lbl_800CD8A8
/* 800CD858 000C8758  2C 1D 00 00 */	cmpwi r29, 0
/* 800CD85C 000C875C  40 82 00 0C */	bne lbl_800CD868
/* 800CD860 000C8760  3B C0 FF FE */	li r30, -2
/* 800CD864 000C8764  48 00 00 44 */	b lbl_800CD8A8
lbl_800CD868:
/* 800CD868 000C8768  7C 1C D8 40 */	cmplw r28, r27
/* 800CD86C 000C876C  41 82 00 38 */	beq lbl_800CD8A4
/* 800CD870 000C8770  7F 64 DB 78 */	mr r4, r27
/* 800CD874 000C8774  38 7F 01 60 */	addi r3, r31, 0x160
/* 800CD878 000C8778  38 A0 00 00 */	li r5, 0
/* 800CD87C 000C877C  48 00 3A 19 */	bl WPADiSendSetReportType
/* 800CD880 000C8780  2C 03 00 00 */	cmpwi r3, 0
/* 800CD884 000C8784  40 82 00 0C */	bne lbl_800CD890
/* 800CD888 000C8788  3B C0 FF FE */	li r30, -2
/* 800CD88C 000C878C  48 00 00 1C */	b lbl_800CD8A8
lbl_800CD890:
/* 800CD890 000C8790  48 02 40 31 */	bl OSDisableInterrupts
/* 800CD894 000C8794  93 7F 08 B8 */	stw r27, 0x8b8(r31)
/* 800CD898 000C8798  48 02 40 51 */	bl OSRestoreInterrupts
/* 800CD89C 000C879C  3B C0 00 00 */	li r30, 0
/* 800CD8A0 000C87A0  48 00 00 08 */	b lbl_800CD8A8
lbl_800CD8A4:
/* 800CD8A4 000C87A4  3B C0 00 00 */	li r30, 0
lbl_800CD8A8:
/* 800CD8A8 000C87A8  39 61 00 20 */	addi r11, r1, 0x20
/* 800CD8AC 000C87AC  7F C3 F3 78 */	mr r3, r30
/* 800CD8B0 000C87B0  4B FE 44 E1 */	bl _restgpr_27
/* 800CD8B4 000C87B4  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800CD8B8 000C87B8  7C 08 03 A6 */	mtlr r0
/* 800CD8BC 000C87BC  38 21 00 20 */	addi r1, r1, 0x20
/* 800CD8C0 000C87C0  4E 80 00 20 */	blr 

.global __wpadInfoCallback
__wpadInfoCallback:
/* 800CD8C4 000C87C4  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800CD8C8 000C87C8  7C 08 02 A6 */	mflr r0
/* 800CD8CC 000C87CC  3C A0 80 41 */	lis r5, _wpdcb@ha
/* 800CD8D0 000C87D0  90 01 00 14 */	stw r0, 0x14(r1)
/* 800CD8D4 000C87D4  54 60 10 3A */	slwi r0, r3, 2
/* 800CD8D8 000C87D8  38 A5 F6 30 */	addi r5, r5, _wpdcb@l
/* 800CD8DC 000C87DC  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800CD8E0 000C87E0  7F E5 00 2E */	lwzx r31, r5, r0
/* 800CD8E4 000C87E4  81 9F 09 88 */	lwz r12, 0x988(r31)
/* 800CD8E8 000C87E8  2C 0C 00 00 */	cmpwi r12, 0
/* 800CD8EC 000C87EC  41 82 00 0C */	beq lbl_800CD8F8
/* 800CD8F0 000C87F0  7D 89 03 A6 */	mtctr r12
/* 800CD8F4 000C87F4  4E 80 04 21 */	bctrl 
lbl_800CD8F8:
/* 800CD8F8 000C87F8  38 00 00 00 */	li r0, 0
/* 800CD8FC 000C87FC  90 1F 09 88 */	stw r0, 0x988(r31)
/* 800CD900 000C8800  98 1F 09 8C */	stb r0, 0x98c(r31)
/* 800CD904 000C8804  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 800CD908 000C8808  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800CD90C 000C880C  7C 08 03 A6 */	mtlr r0
/* 800CD910 000C8810  38 21 00 10 */	addi r1, r1, 0x10
/* 800CD914 000C8814  4E 80 00 20 */	blr 

.global WPADGetInfoAsync
WPADGetInfoAsync:
/* 800CD918 000C8818  94 21 FF 70 */	stwu r1, -0x90(r1)
/* 800CD91C 000C881C  7C 08 02 A6 */	mflr r0
/* 800CD920 000C8820  90 01 00 94 */	stw r0, 0x94(r1)
/* 800CD924 000C8824  39 61 00 90 */	addi r11, r1, 0x90
/* 800CD928 000C8828  4B FE 44 15 */	bl _savegpr_25
/* 800CD92C 000C882C  3C C0 80 41 */	lis r6, _wpdcb@ha
/* 800CD930 000C8830  54 60 10 3A */	slwi r0, r3, 2
/* 800CD934 000C8834  38 C6 F6 30 */	addi r6, r6, _wpdcb@l
/* 800CD938 000C8838  7C 7C 1B 78 */	mr r28, r3
/* 800CD93C 000C883C  7F C6 00 2E */	lwzx r30, r6, r0
/* 800CD940 000C8840  7C 9F 23 78 */	mr r31, r4
/* 800CD944 000C8844  7C BD 2B 78 */	mr r29, r5
/* 800CD948 000C8848  48 02 3F 79 */	bl OSDisableInterrupts
/* 800CD94C 000C884C  83 7E 08 DC */	lwz r27, 0x8dc(r30)
/* 800CD950 000C8850  83 5E 08 BC */	lwz r26, 0x8bc(r30)
/* 800CD954 000C8854  8B 3E 09 8C */	lbz r25, 0x98c(r30)
/* 800CD958 000C8858  48 02 3F 91 */	bl OSRestoreInterrupts
/* 800CD95C 000C885C  2C 1A FF FF */	cmpwi r26, -1
/* 800CD960 000C8860  41 82 01 98 */	beq lbl_800CDAF8
/* 800CD964 000C8864  2C 1B 00 00 */	cmpwi r27, 0
/* 800CD968 000C8868  41 82 00 0C */	beq lbl_800CD974
/* 800CD96C 000C886C  2C 19 00 00 */	cmpwi r25, 0
/* 800CD970 000C8870  41 82 00 0C */	beq lbl_800CD97C
lbl_800CD974:
/* 800CD974 000C8874  3B 40 FF FE */	li r26, -2
/* 800CD978 000C8878  48 00 01 80 */	b lbl_800CDAF8
lbl_800CD97C:
/* 800CD97C 000C887C  48 02 3F 45 */	bl OSDisableInterrupts
/* 800CD980 000C8880  3B 60 00 01 */	li r27, 1
/* 800CD984 000C8884  9B 7E 09 8C */	stb r27, 0x98c(r30)
/* 800CD988 000C8888  93 BE 09 88 */	stw r29, 0x988(r30)
/* 800CD98C 000C888C  48 02 3F 5D */	bl OSRestoreInterrupts
/* 800CD990 000C8890  38 00 00 00 */	li r0, 0
/* 800CD994 000C8894  39 80 00 15 */	li r12, 0x15
/* 800CD998 000C8898  98 01 00 0C */	stb r0, 0xc(r1)
/* 800CD99C 000C889C  3D 60 80 0D */	lis r11, __wpadInfoCallback@ha
/* 800CD9A0 000C88A0  39 6B D8 C4 */	addi r11, r11, __wpadInfoCallback@l
/* 800CD9A4 000C88A4  81 21 00 10 */	lwz r9, 0x10(r1)
/* 800CD9A8 000C88A8  B3 61 00 22 */	sth r27, 0x22(r1)
/* 800CD9AC 000C88AC  81 01 00 14 */	lwz r8, 0x14(r1)
/* 800CD9B0 000C88B0  81 41 00 0C */	lwz r10, 0xc(r1)
/* 800CD9B4 000C88B4  80 E1 00 18 */	lwz r7, 0x18(r1)
/* 800CD9B8 000C88B8  80 C1 00 1C */	lwz r6, 0x1c(r1)
/* 800CD9BC 000C88BC  80 A1 00 20 */	lwz r5, 0x20(r1)
/* 800CD9C0 000C88C0  80 81 00 24 */	lwz r4, 0x24(r1)
/* 800CD9C4 000C88C4  80 61 00 28 */	lwz r3, 0x28(r1)
/* 800CD9C8 000C88C8  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 800CD9CC 000C88CC  91 81 00 08 */	stw r12, 8(r1)
/* 800CD9D0 000C88D0  91 61 00 34 */	stw r11, 0x34(r1)
/* 800CD9D4 000C88D4  93 E1 00 30 */	stw r31, 0x30(r1)
/* 800CD9D8 000C88D8  91 81 00 38 */	stw r12, 0x38(r1)
/* 800CD9DC 000C88DC  91 41 00 3C */	stw r10, 0x3c(r1)
/* 800CD9E0 000C88E0  91 21 00 40 */	stw r9, 0x40(r1)
/* 800CD9E4 000C88E4  91 01 00 44 */	stw r8, 0x44(r1)
/* 800CD9E8 000C88E8  90 E1 00 48 */	stw r7, 0x48(r1)
/* 800CD9EC 000C88EC  90 C1 00 4C */	stw r6, 0x4c(r1)
/* 800CD9F0 000C88F0  90 A1 00 50 */	stw r5, 0x50(r1)
/* 800CD9F4 000C88F4  90 81 00 54 */	stw r4, 0x54(r1)
/* 800CD9F8 000C88F8  90 61 00 58 */	stw r3, 0x58(r1)
/* 800CD9FC 000C88FC  90 01 00 5C */	stw r0, 0x5c(r1)
/* 800CDA00 000C8900  93 E1 00 60 */	stw r31, 0x60(r1)
/* 800CDA04 000C8904  91 61 00 64 */	stw r11, 0x64(r1)
/* 800CDA08 000C8908  48 02 3E B9 */	bl OSDisableInterrupts
/* 800CDA0C 000C890C  7C 7F 1B 78 */	mr r31, r3
/* 800CDA10 000C8910  48 02 3E B1 */	bl OSDisableInterrupts
/* 800CDA14 000C8914  88 9E 01 60 */	lbz r4, 0x160(r30)
/* 800CDA18 000C8918  88 1E 01 61 */	lbz r0, 0x161(r30)
/* 800CDA1C 000C891C  7C 04 00 50 */	subf r0, r4, r0
/* 800CDA20 000C8920  7C 1B 07 75 */	extsb. r27, r0
/* 800CDA24 000C8924  40 80 00 10 */	bge lbl_800CDA34
/* 800CDA28 000C8928  80 1E 01 68 */	lwz r0, 0x168(r30)
/* 800CDA2C 000C892C  7C 1B 02 14 */	add r0, r27, r0
/* 800CDA30 000C8930  7C 1B 07 74 */	extsb r27, r0
lbl_800CDA34:
/* 800CDA34 000C8934  48 02 3E B5 */	bl OSRestoreInterrupts
/* 800CDA38 000C8938  80 7E 01 68 */	lwz r3, 0x168(r30)
/* 800CDA3C 000C893C  38 03 FF FF */	addi r0, r3, -1
/* 800CDA40 000C8940  7C 00 D8 40 */	cmplw r0, r27
/* 800CDA44 000C8944  40 82 00 14 */	bne lbl_800CDA58
/* 800CDA48 000C8948  7F E3 FB 78 */	mr r3, r31
/* 800CDA4C 000C894C  48 02 3E 9D */	bl OSRestoreInterrupts
/* 800CDA50 000C8950  38 00 00 00 */	li r0, 0
/* 800CDA54 000C8954  48 00 00 7C */	b lbl_800CDAD0
lbl_800CDA58:
/* 800CDA58 000C8958  88 1E 01 61 */	lbz r0, 0x161(r30)
/* 800CDA5C 000C895C  38 80 00 00 */	li r4, 0
/* 800CDA60 000C8960  80 7E 01 64 */	lwz r3, 0x164(r30)
/* 800CDA64 000C8964  38 A0 00 30 */	li r5, 0x30
/* 800CDA68 000C8968  7C 00 07 74 */	extsb r0, r0
/* 800CDA6C 000C896C  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CDA70 000C8970  7C 63 02 14 */	add r3, r3, r0
/* 800CDA74 000C8974  4B F3 66 91 */	bl memset
/* 800CDA78 000C8978  88 1E 01 61 */	lbz r0, 0x161(r30)
/* 800CDA7C 000C897C  38 81 00 38 */	addi r4, r1, 0x38
/* 800CDA80 000C8980  80 7E 01 64 */	lwz r3, 0x164(r30)
/* 800CDA84 000C8984  38 A0 00 30 */	li r5, 0x30
/* 800CDA88 000C8988  7C 00 07 74 */	extsb r0, r0
/* 800CDA8C 000C898C  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CDA90 000C8990  7C 63 02 14 */	add r3, r3, r0
/* 800CDA94 000C8994  4B F3 65 6D */	bl memcpy
/* 800CDA98 000C8998  88 1E 01 61 */	lbz r0, 0x161(r30)
/* 800CDA9C 000C899C  7F E3 FB 78 */	mr r3, r31
/* 800CDAA0 000C89A0  80 9E 01 68 */	lwz r4, 0x168(r30)
/* 800CDAA4 000C89A4  7C 06 07 74 */	extsb r6, r0
/* 800CDAA8 000C89A8  38 84 FF FF */	addi r4, r4, -1
/* 800CDAAC 000C89AC  7C A4 30 50 */	subf r5, r4, r6
/* 800CDAB0 000C89B0  38 06 00 01 */	addi r0, r6, 1
/* 800CDAB4 000C89B4  7C 86 20 50 */	subf r4, r6, r4
/* 800CDAB8 000C89B8  7C A4 20 F8 */	nor r4, r5, r4
/* 800CDABC 000C89BC  7C 84 FE 70 */	srawi r4, r4, 0x1f
/* 800CDAC0 000C89C0  7C 00 20 78 */	andc r0, r0, r4
/* 800CDAC4 000C89C4  98 1E 01 61 */	stb r0, 0x161(r30)
/* 800CDAC8 000C89C8  48 02 3E 21 */	bl OSRestoreInterrupts
/* 800CDACC 000C89CC  38 00 00 01 */	li r0, 1
lbl_800CDAD0:
/* 800CDAD0 000C89D0  2C 00 00 00 */	cmpwi r0, 0
/* 800CDAD4 000C89D4  41 82 00 0C */	beq lbl_800CDAE0
/* 800CDAD8 000C89D8  3B 40 00 00 */	li r26, 0
/* 800CDADC 000C89DC  48 00 00 1C */	b lbl_800CDAF8
lbl_800CDAE0:
/* 800CDAE0 000C89E0  3B 40 FF FE */	li r26, -2
/* 800CDAE4 000C89E4  48 02 3D DD */	bl OSDisableInterrupts
/* 800CDAE8 000C89E8  38 00 00 00 */	li r0, 0
/* 800CDAEC 000C89EC  98 1E 09 8C */	stb r0, 0x98c(r30)
/* 800CDAF0 000C89F0  90 1E 09 88 */	stw r0, 0x988(r30)
/* 800CDAF4 000C89F4  48 02 3D F5 */	bl OSRestoreInterrupts
lbl_800CDAF8:
/* 800CDAF8 000C89F8  2C 1A 00 00 */	cmpwi r26, 0
/* 800CDAFC 000C89FC  41 82 00 20 */	beq lbl_800CDB1C
/* 800CDB00 000C8A00  2C 1D 00 00 */	cmpwi r29, 0
/* 800CDB04 000C8A04  41 82 00 18 */	beq lbl_800CDB1C
/* 800CDB08 000C8A08  7F AC EB 78 */	mr r12, r29
/* 800CDB0C 000C8A0C  7F 83 E3 78 */	mr r3, r28
/* 800CDB10 000C8A10  7F 44 D3 78 */	mr r4, r26
/* 800CDB14 000C8A14  7D 89 03 A6 */	mtctr r12
/* 800CDB18 000C8A18  4E 80 04 21 */	bctrl 
lbl_800CDB1C:
/* 800CDB1C 000C8A1C  39 61 00 90 */	addi r11, r1, 0x90
/* 800CDB20 000C8A20  7F 43 D3 78 */	mr r3, r26
/* 800CDB24 000C8A24  4B FE 42 65 */	bl _restgpr_25
/* 800CDB28 000C8A28  80 01 00 94 */	lwz r0, 0x94(r1)
/* 800CDB2C 000C8A2C  7C 08 03 A6 */	mtlr r0
/* 800CDB30 000C8A30  38 21 00 90 */	addi r1, r1, 0x90
/* 800CDB34 000C8A34  4E 80 00 20 */	blr 

.global WPADControlMotor
WPADControlMotor:
/* 800CDB38 000C8A38  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800CDB3C 000C8A3C  7C 08 02 A6 */	mflr r0
/* 800CDB40 000C8A40  3C A0 80 41 */	lis r5, _wpdcb@ha
/* 800CDB44 000C8A44  90 01 00 14 */	stw r0, 0x14(r1)
/* 800CDB48 000C8A48  54 60 10 3A */	slwi r0, r3, 2
/* 800CDB4C 000C8A4C  38 A5 F6 30 */	addi r5, r5, _wpdcb@l
/* 800CDB50 000C8A50  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800CDB54 000C8A54  93 C1 00 08 */	stw r30, 8(r1)
/* 800CDB58 000C8A58  7C 9E 23 78 */	mr r30, r4
/* 800CDB5C 000C8A5C  7F E5 00 2E */	lwzx r31, r5, r0
/* 800CDB60 000C8A60  48 02 3D 61 */	bl OSDisableInterrupts
/* 800CDB64 000C8A64  80 1F 08 BC */	lwz r0, 0x8bc(r31)
/* 800CDB68 000C8A68  2C 00 FF FF */	cmpwi r0, -1
/* 800CDB6C 000C8A6C  40 82 00 0C */	bne lbl_800CDB78
/* 800CDB70 000C8A70  48 02 3D 79 */	bl OSRestoreInterrupts
/* 800CDB74 000C8A74  48 00 00 78 */	b lbl_800CDBEC
lbl_800CDB78:
/* 800CDB78 000C8A78  80 0D 9A 74 */	lwz r0, _rumble-_SDA_BASE_(r13)
/* 800CDB7C 000C8A7C  2C 00 00 00 */	cmpwi r0, 0
/* 800CDB80 000C8A80  40 82 00 20 */	bne lbl_800CDBA0
/* 800CDB84 000C8A84  2C 1E 00 00 */	cmpwi r30, 0
/* 800CDB88 000C8A88  40 82 00 10 */	bne lbl_800CDB98
/* 800CDB8C 000C8A8C  80 1F 08 D4 */	lwz r0, 0x8d4(r31)
/* 800CDB90 000C8A90  2C 00 00 01 */	cmpwi r0, 1
/* 800CDB94 000C8A94  41 82 00 0C */	beq lbl_800CDBA0
lbl_800CDB98:
/* 800CDB98 000C8A98  48 02 3D 51 */	bl OSRestoreInterrupts
/* 800CDB9C 000C8A9C  48 00 00 50 */	b lbl_800CDBEC
lbl_800CDBA0:
/* 800CDBA0 000C8AA0  2C 1E 00 00 */	cmpwi r30, 0
/* 800CDBA4 000C8AA4  40 82 00 10 */	bne lbl_800CDBB4
/* 800CDBA8 000C8AA8  80 1F 08 D4 */	lwz r0, 0x8d4(r31)
/* 800CDBAC 000C8AAC  2C 00 00 00 */	cmpwi r0, 0
/* 800CDBB0 000C8AB0  41 82 00 18 */	beq lbl_800CDBC8
lbl_800CDBB4:
/* 800CDBB4 000C8AB4  28 1E 00 01 */	cmplwi r30, 1
/* 800CDBB8 000C8AB8  40 82 00 18 */	bne lbl_800CDBD0
/* 800CDBBC 000C8ABC  80 1F 08 D4 */	lwz r0, 0x8d4(r31)
/* 800CDBC0 000C8AC0  2C 00 00 01 */	cmpwi r0, 1
/* 800CDBC4 000C8AC4  40 82 00 0C */	bne lbl_800CDBD0
lbl_800CDBC8:
/* 800CDBC8 000C8AC8  48 02 3D 21 */	bl OSRestoreInterrupts
/* 800CDBCC 000C8ACC  48 00 00 20 */	b lbl_800CDBEC
lbl_800CDBD0:
/* 800CDBD0 000C8AD0  7C 9E 00 D0 */	neg r4, r30
/* 800CDBD4 000C8AD4  38 00 00 01 */	li r0, 1
/* 800CDBD8 000C8AD8  7C 84 F3 78 */	or r4, r4, r30
/* 800CDBDC 000C8ADC  54 84 0F FE */	srwi r4, r4, 0x1f
/* 800CDBE0 000C8AE0  90 9F 08 D4 */	stw r4, 0x8d4(r31)
/* 800CDBE4 000C8AE4  90 1F 08 D0 */	stw r0, 0x8d0(r31)
/* 800CDBE8 000C8AE8  48 02 3D 01 */	bl OSRestoreInterrupts
lbl_800CDBEC:
/* 800CDBEC 000C8AEC  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800CDBF0 000C8AF0  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 800CDBF4 000C8AF4  83 C1 00 08 */	lwz r30, 8(r1)
/* 800CDBF8 000C8AF8  7C 08 03 A6 */	mtlr r0
/* 800CDBFC 000C8AFC  38 21 00 10 */	addi r1, r1, 0x10
/* 800CDC00 000C8B00  4E 80 00 20 */	blr 

.global WPADEnableMotor
WPADEnableMotor:
/* 800CDC04 000C8B04  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800CDC08 000C8B08  7C 08 02 A6 */	mflr r0
/* 800CDC0C 000C8B0C  90 01 00 14 */	stw r0, 0x14(r1)
/* 800CDC10 000C8B10  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800CDC14 000C8B14  7C 7F 1B 78 */	mr r31, r3
/* 800CDC18 000C8B18  48 02 3C A9 */	bl OSDisableInterrupts
/* 800CDC1C 000C8B1C  93 ED 9A 74 */	stw r31, _rumble-_SDA_BASE_(r13)
/* 800CDC20 000C8B20  48 02 3C C9 */	bl OSRestoreInterrupts
/* 800CDC24 000C8B24  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800CDC28 000C8B28  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 800CDC2C 000C8B2C  7C 08 03 A6 */	mtlr r0
/* 800CDC30 000C8B30  38 21 00 10 */	addi r1, r1, 0x10
/* 800CDC34 000C8B34  4E 80 00 20 */	blr 

.global WPADIsMotorEnabled
WPADIsMotorEnabled:
/* 800CDC38 000C8B38  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800CDC3C 000C8B3C  7C 08 02 A6 */	mflr r0
/* 800CDC40 000C8B40  90 01 00 14 */	stw r0, 0x14(r1)
/* 800CDC44 000C8B44  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800CDC48 000C8B48  48 02 3C 79 */	bl OSDisableInterrupts
/* 800CDC4C 000C8B4C  83 ED 9A 74 */	lwz r31, _rumble-_SDA_BASE_(r13)
/* 800CDC50 000C8B50  48 02 3C 99 */	bl OSRestoreInterrupts
/* 800CDC54 000C8B54  7F E3 FB 78 */	mr r3, r31
/* 800CDC58 000C8B58  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 800CDC5C 000C8B5C  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800CDC60 000C8B60  7C 08 03 A6 */	mtlr r0
/* 800CDC64 000C8B64  38 21 00 10 */	addi r1, r1, 0x10
/* 800CDC68 000C8B68  4E 80 00 20 */	blr 

.global WPADControlLed
WPADControlLed:
/* 800CDC6C 000C8B6C  94 21 FF 80 */	stwu r1, -0x80(r1)
/* 800CDC70 000C8B70  7C 08 02 A6 */	mflr r0
/* 800CDC74 000C8B74  90 01 00 84 */	stw r0, 0x84(r1)
/* 800CDC78 000C8B78  39 61 00 80 */	addi r11, r1, 0x80
/* 800CDC7C 000C8B7C  4B FE 40 C5 */	bl _savegpr_26
/* 800CDC80 000C8B80  3C C0 80 41 */	lis r6, _wpdcb@ha
/* 800CDC84 000C8B84  54 60 10 3A */	slwi r0, r3, 2
/* 800CDC88 000C8B88  38 C6 F6 30 */	addi r6, r6, _wpdcb@l
/* 800CDC8C 000C8B8C  7C 7C 1B 78 */	mr r28, r3
/* 800CDC90 000C8B90  7F C6 00 2E */	lwzx r30, r6, r0
/* 800CDC94 000C8B94  7C 9A 23 78 */	mr r26, r4
/* 800CDC98 000C8B98  7C BD 2B 78 */	mr r29, r5
/* 800CDC9C 000C8B9C  48 02 3C 25 */	bl OSDisableInterrupts
/* 800CDCA0 000C8BA0  83 FE 08 BC */	lwz r31, 0x8bc(r30)
/* 800CDCA4 000C8BA4  83 7E 08 DC */	lwz r27, 0x8dc(r30)
/* 800CDCA8 000C8BA8  48 02 3C 41 */	bl OSRestoreInterrupts
/* 800CDCAC 000C8BAC  2C 1F FF FF */	cmpwi r31, -1
/* 800CDCB0 000C8BB0  41 82 01 64 */	beq lbl_800CDE14
/* 800CDCB4 000C8BB4  2C 1B 00 00 */	cmpwi r27, 0
/* 800CDCB8 000C8BB8  40 82 00 0C */	bne lbl_800CDCC4
/* 800CDCBC 000C8BBC  3B E0 FF FE */	li r31, -2
/* 800CDCC0 000C8BC0  48 00 01 54 */	b lbl_800CDE14
lbl_800CDCC4:
/* 800CDCC4 000C8BC4  57 40 26 36 */	rlwinm r0, r26, 4, 0x18, 0x1b
/* 800CDCC8 000C8BC8  38 60 00 01 */	li r3, 1
/* 800CDCCC 000C8BCC  B0 61 00 22 */	sth r3, 0x22(r1)
/* 800CDCD0 000C8BD0  39 80 00 11 */	li r12, 0x11
/* 800CDCD4 000C8BD4  81 41 00 10 */	lwz r10, 0x10(r1)
/* 800CDCD8 000C8BD8  98 01 00 0C */	stb r0, 0xc(r1)
/* 800CDCDC 000C8BDC  81 21 00 14 */	lwz r9, 0x14(r1)
/* 800CDCE0 000C8BE0  81 61 00 0C */	lwz r11, 0xc(r1)
/* 800CDCE4 000C8BE4  81 01 00 18 */	lwz r8, 0x18(r1)
/* 800CDCE8 000C8BE8  80 E1 00 1C */	lwz r7, 0x1c(r1)
/* 800CDCEC 000C8BEC  80 C1 00 20 */	lwz r6, 0x20(r1)
/* 800CDCF0 000C8BF0  80 A1 00 24 */	lwz r5, 0x24(r1)
/* 800CDCF4 000C8BF4  80 81 00 28 */	lwz r4, 0x28(r1)
/* 800CDCF8 000C8BF8  80 61 00 2C */	lwz r3, 0x2c(r1)
/* 800CDCFC 000C8BFC  80 01 00 30 */	lwz r0, 0x30(r1)
/* 800CDD00 000C8C00  91 81 00 08 */	stw r12, 8(r1)
/* 800CDD04 000C8C04  93 A1 00 34 */	stw r29, 0x34(r1)
/* 800CDD08 000C8C08  91 81 00 38 */	stw r12, 0x38(r1)
/* 800CDD0C 000C8C0C  91 61 00 3C */	stw r11, 0x3c(r1)
/* 800CDD10 000C8C10  91 41 00 40 */	stw r10, 0x40(r1)
/* 800CDD14 000C8C14  91 21 00 44 */	stw r9, 0x44(r1)
/* 800CDD18 000C8C18  91 01 00 48 */	stw r8, 0x48(r1)
/* 800CDD1C 000C8C1C  90 E1 00 4C */	stw r7, 0x4c(r1)
/* 800CDD20 000C8C20  90 C1 00 50 */	stw r6, 0x50(r1)
/* 800CDD24 000C8C24  90 A1 00 54 */	stw r5, 0x54(r1)
/* 800CDD28 000C8C28  90 81 00 58 */	stw r4, 0x58(r1)
/* 800CDD2C 000C8C2C  90 61 00 5C */	stw r3, 0x5c(r1)
/* 800CDD30 000C8C30  90 01 00 60 */	stw r0, 0x60(r1)
/* 800CDD34 000C8C34  93 A1 00 64 */	stw r29, 0x64(r1)
/* 800CDD38 000C8C38  48 02 3B 89 */	bl OSDisableInterrupts
/* 800CDD3C 000C8C3C  7C 7F 1B 78 */	mr r31, r3
/* 800CDD40 000C8C40  48 02 3B 81 */	bl OSDisableInterrupts
/* 800CDD44 000C8C44  88 9E 01 60 */	lbz r4, 0x160(r30)
/* 800CDD48 000C8C48  88 1E 01 61 */	lbz r0, 0x161(r30)
/* 800CDD4C 000C8C4C  7C 04 00 50 */	subf r0, r4, r0
/* 800CDD50 000C8C50  7C 1B 07 75 */	extsb. r27, r0
/* 800CDD54 000C8C54  40 80 00 10 */	bge lbl_800CDD64
/* 800CDD58 000C8C58  80 1E 01 68 */	lwz r0, 0x168(r30)
/* 800CDD5C 000C8C5C  7C 1B 02 14 */	add r0, r27, r0
/* 800CDD60 000C8C60  7C 1B 07 74 */	extsb r27, r0
lbl_800CDD64:
/* 800CDD64 000C8C64  48 02 3B 85 */	bl OSRestoreInterrupts
/* 800CDD68 000C8C68  80 7E 01 68 */	lwz r3, 0x168(r30)
/* 800CDD6C 000C8C6C  38 03 FF FF */	addi r0, r3, -1
/* 800CDD70 000C8C70  7C 00 D8 40 */	cmplw r0, r27
/* 800CDD74 000C8C74  40 82 00 14 */	bne lbl_800CDD88
/* 800CDD78 000C8C78  7F E3 FB 78 */	mr r3, r31
/* 800CDD7C 000C8C7C  48 02 3B 6D */	bl OSRestoreInterrupts
/* 800CDD80 000C8C80  38 80 00 00 */	li r4, 0
/* 800CDD84 000C8C84  48 00 00 7C */	b lbl_800CDE00
lbl_800CDD88:
/* 800CDD88 000C8C88  88 1E 01 61 */	lbz r0, 0x161(r30)
/* 800CDD8C 000C8C8C  38 80 00 00 */	li r4, 0
/* 800CDD90 000C8C90  80 7E 01 64 */	lwz r3, 0x164(r30)
/* 800CDD94 000C8C94  38 A0 00 30 */	li r5, 0x30
/* 800CDD98 000C8C98  7C 00 07 74 */	extsb r0, r0
/* 800CDD9C 000C8C9C  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CDDA0 000C8CA0  7C 63 02 14 */	add r3, r3, r0
/* 800CDDA4 000C8CA4  4B F3 63 61 */	bl memset
/* 800CDDA8 000C8CA8  88 1E 01 61 */	lbz r0, 0x161(r30)
/* 800CDDAC 000C8CAC  38 81 00 38 */	addi r4, r1, 0x38
/* 800CDDB0 000C8CB0  80 7E 01 64 */	lwz r3, 0x164(r30)
/* 800CDDB4 000C8CB4  38 A0 00 30 */	li r5, 0x30
/* 800CDDB8 000C8CB8  7C 00 07 74 */	extsb r0, r0
/* 800CDDBC 000C8CBC  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CDDC0 000C8CC0  7C 63 02 14 */	add r3, r3, r0
/* 800CDDC4 000C8CC4  4B F3 62 3D */	bl memcpy
/* 800CDDC8 000C8CC8  88 1E 01 61 */	lbz r0, 0x161(r30)
/* 800CDDCC 000C8CCC  7F E3 FB 78 */	mr r3, r31
/* 800CDDD0 000C8CD0  80 9E 01 68 */	lwz r4, 0x168(r30)
/* 800CDDD4 000C8CD4  7C 06 07 74 */	extsb r6, r0
/* 800CDDD8 000C8CD8  38 84 FF FF */	addi r4, r4, -1
/* 800CDDDC 000C8CDC  7C A4 30 50 */	subf r5, r4, r6
/* 800CDDE0 000C8CE0  38 06 00 01 */	addi r0, r6, 1
/* 800CDDE4 000C8CE4  7C 86 20 50 */	subf r4, r6, r4
/* 800CDDE8 000C8CE8  7C A4 20 F8 */	nor r4, r5, r4
/* 800CDDEC 000C8CEC  7C 84 FE 70 */	srawi r4, r4, 0x1f
/* 800CDDF0 000C8CF0  7C 00 20 78 */	andc r0, r0, r4
/* 800CDDF4 000C8CF4  98 1E 01 61 */	stb r0, 0x161(r30)
/* 800CDDF8 000C8CF8  48 02 3A F1 */	bl OSRestoreInterrupts
/* 800CDDFC 000C8CFC  38 80 00 01 */	li r4, 1
lbl_800CDE00:
/* 800CDE00 000C8D00  7C 64 00 D0 */	neg r3, r4
/* 800CDE04 000C8D04  38 00 FF FE */	li r0, -2
/* 800CDE08 000C8D08  7C 63 23 78 */	or r3, r3, r4
/* 800CDE0C 000C8D0C  7C 63 FE 70 */	srawi r3, r3, 0x1f
/* 800CDE10 000C8D10  7C 1F 18 78 */	andc r31, r0, r3
lbl_800CDE14:
/* 800CDE14 000C8D14  2C 1F 00 00 */	cmpwi r31, 0
/* 800CDE18 000C8D18  41 82 00 20 */	beq lbl_800CDE38
/* 800CDE1C 000C8D1C  2C 1D 00 00 */	cmpwi r29, 0
/* 800CDE20 000C8D20  41 82 00 18 */	beq lbl_800CDE38
/* 800CDE24 000C8D24  7F AC EB 78 */	mr r12, r29
/* 800CDE28 000C8D28  7F 83 E3 78 */	mr r3, r28
/* 800CDE2C 000C8D2C  7F E4 FB 78 */	mr r4, r31
/* 800CDE30 000C8D30  7D 89 03 A6 */	mtctr r12
/* 800CDE34 000C8D34  4E 80 04 21 */	bctrl 
lbl_800CDE38:
/* 800CDE38 000C8D38  39 61 00 80 */	addi r11, r1, 0x80
/* 800CDE3C 000C8D3C  7F E3 FB 78 */	mr r3, r31
/* 800CDE40 000C8D40  4B FE 3F 4D */	bl _restgpr_26
/* 800CDE44 000C8D44  80 01 00 84 */	lwz r0, 0x84(r1)
/* 800CDE48 000C8D48  7C 08 03 A6 */	mtlr r0
/* 800CDE4C 000C8D4C  38 21 00 80 */	addi r1, r1, 0x80
/* 800CDE50 000C8D50  4E 80 00 20 */	blr 

.global WPADSaveConfig
WPADSaveConfig:
/* 800CDE54 000C8D54  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800CDE58 000C8D58  7C 08 02 A6 */	mflr r0
/* 800CDE5C 000C8D5C  90 01 00 24 */	stw r0, 0x24(r1)
/* 800CDE60 000C8D60  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800CDE64 000C8D64  93 C1 00 18 */	stw r30, 0x18(r1)
/* 800CDE68 000C8D68  93 A1 00 14 */	stw r29, 0x14(r1)
/* 800CDE6C 000C8D6C  7C 7D 1B 78 */	mr r29, r3
/* 800CDE70 000C8D70  48 02 92 35 */	bl SCCheckStatus
/* 800CDE74 000C8D74  2C 03 00 00 */	cmpwi r3, 0
/* 800CDE78 000C8D78  41 82 00 0C */	beq lbl_800CDE84
/* 800CDE7C 000C8D7C  38 60 00 00 */	li r3, 0
/* 800CDE80 000C8D80  48 00 00 64 */	b lbl_800CDEE4
lbl_800CDE84:
/* 800CDE84 000C8D84  48 02 3A 3D */	bl OSDisableInterrupts
/* 800CDE88 000C8D88  80 8D 9A 74 */	lwz r4, _rumble-_SDA_BASE_(r13)
/* 800CDE8C 000C8D8C  8B CD 9A 72 */	lbz r30, _speakerVolume-_SDA_BASE_(r13)
/* 800CDE90 000C8D90  7C 04 00 D0 */	neg r0, r4
/* 800CDE94 000C8D94  7C 00 23 78 */	or r0, r0, r4
/* 800CDE98 000C8D98  54 1F 0F FE */	srwi r31, r0, 0x1f
/* 800CDE9C 000C8D9C  48 02 3A 4D */	bl OSRestoreInterrupts
/* 800CDEA0 000C8DA0  7F C3 F3 78 */	mr r3, r30
/* 800CDEA4 000C8DA4  48 02 AF 29 */	bl SCSetWpadSpeakerVolume
/* 800CDEA8 000C8DA8  54 7E 07 FE */	clrlwi r30, r3, 0x1f
/* 800CDEAC 000C8DAC  7F E3 FB 78 */	mr r3, r31
/* 800CDEB0 000C8DB0  48 02 AE 6D */	bl SCSetWpadMotorMode
/* 800CDEB4 000C8DB4  7F DE 18 39 */	and. r30, r30, r3
/* 800CDEB8 000C8DB8  41 82 00 10 */	beq lbl_800CDEC8
/* 800CDEBC 000C8DBC  7F A3 EB 78 */	mr r3, r29
/* 800CDEC0 000C8DC0  48 02 A5 55 */	bl SCFlushAsync
/* 800CDEC4 000C8DC4  48 00 00 1C */	b lbl_800CDEE0
lbl_800CDEC8:
/* 800CDEC8 000C8DC8  2C 1D 00 00 */	cmpwi r29, 0
/* 800CDECC 000C8DCC  41 82 00 14 */	beq lbl_800CDEE0
/* 800CDED0 000C8DD0  7F AC EB 78 */	mr r12, r29
/* 800CDED4 000C8DD4  38 60 00 02 */	li r3, 2
/* 800CDED8 000C8DD8  7D 89 03 A6 */	mtctr r12
/* 800CDEDC 000C8DDC  4E 80 04 21 */	bctrl 
lbl_800CDEE0:
/* 800CDEE0 000C8DE0  7F C3 F3 78 */	mr r3, r30
lbl_800CDEE4:
/* 800CDEE4 000C8DE4  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800CDEE8 000C8DE8  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800CDEEC 000C8DEC  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 800CDEF0 000C8DF0  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 800CDEF4 000C8DF4  7C 08 03 A6 */	mtlr r0
/* 800CDEF8 000C8DF8  38 21 00 20 */	addi r1, r1, 0x20
/* 800CDEFC 000C8DFC  4E 80 00 20 */	blr 

.global WPADRead
WPADRead:
/* 800CDF00 000C8E00  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800CDF04 000C8E04  7C 08 02 A6 */	mflr r0
/* 800CDF08 000C8E08  90 01 00 24 */	stw r0, 0x24(r1)
/* 800CDF0C 000C8E0C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800CDF10 000C8E10  93 C1 00 18 */	stw r30, 0x18(r1)
/* 800CDF14 000C8E14  7C 9E 23 78 */	mr r30, r4
/* 800CDF18 000C8E18  93 A1 00 14 */	stw r29, 0x14(r1)
/* 800CDF1C 000C8E1C  7C 7D 1B 78 */	mr r29, r3
/* 800CDF20 000C8E20  48 02 39 A1 */	bl OSDisableInterrupts
/* 800CDF24 000C8E24  3C 80 80 41 */	lis r4, _wpdcb@ha
/* 800CDF28 000C8E28  57 A0 10 3A */	slwi r0, r29, 2
/* 800CDF2C 000C8E2C  38 84 F6 30 */	addi r4, r4, _wpdcb@l
/* 800CDF30 000C8E30  7C 7F 1B 78 */	mr r31, r3
/* 800CDF34 000C8E34  7C 84 00 2E */	lwzx r4, r4, r0
/* 800CDF38 000C8E38  88 04 08 C8 */	lbz r0, 0x8c8(r4)
/* 800CDF3C 000C8E3C  7C 00 00 34 */	cntlzw r0, r0
/* 800CDF40 000C8E40  54 00 DE 3E */	rlwinm r0, r0, 0x1b, 0x18, 0x1f
/* 800CDF44 000C8E44  1C 00 00 60 */	mulli r0, r0, 0x60
/* 800CDF48 000C8E48  7C 64 02 14 */	add r3, r4, r0
/* 800CDF4C 000C8E4C  88 03 00 C9 */	lbz r0, 0xc9(r3)
/* 800CDF50 000C8E50  3B A3 00 A0 */	addi r29, r3, 0xa0
/* 800CDF54 000C8E54  7C 00 07 74 */	extsb r0, r0
/* 800CDF58 000C8E58  2C 00 FF FE */	cmpwi r0, -2
/* 800CDF5C 000C8E5C  41 82 00 94 */	beq lbl_800CDFF0
/* 800CDF60 000C8E60  40 80 00 10 */	bge lbl_800CDF70
/* 800CDF64 000C8E64  2C 00 FF F9 */	cmpwi r0, -7
/* 800CDF68 000C8E68  41 82 00 88 */	beq lbl_800CDFF0
/* 800CDF6C 000C8E6C  48 00 00 98 */	b lbl_800CE004
lbl_800CDF70:
/* 800CDF70 000C8E70  2C 00 00 00 */	cmpwi r0, 0
/* 800CDF74 000C8E74  41 82 00 08 */	beq lbl_800CDF7C
/* 800CDF78 000C8E78  48 00 00 8C */	b lbl_800CE004
lbl_800CDF7C:
/* 800CDF7C 000C8E7C  80 64 08 B8 */	lwz r3, 0x8b8(r4)
/* 800CDF80 000C8E80  28 03 00 02 */	cmplwi r3, 2
/* 800CDF84 000C8E84  41 81 00 18 */	bgt lbl_800CDF9C
/* 800CDF88 000C8E88  7F C3 F3 78 */	mr r3, r30
/* 800CDF8C 000C8E8C  7F A4 EB 78 */	mr r4, r29
/* 800CDF90 000C8E90  38 A0 00 2A */	li r5, 0x2a
/* 800CDF94 000C8E94  4B F3 60 6D */	bl memcpy
/* 800CDF98 000C8E98  48 00 00 E4 */	b lbl_800CE07C
lbl_800CDF9C:
/* 800CDF9C 000C8E9C  38 03 FF FD */	addi r0, r3, -3
/* 800CDFA0 000C8EA0  28 00 00 02 */	cmplwi r0, 2
/* 800CDFA4 000C8EA4  41 81 00 18 */	bgt lbl_800CDFBC
/* 800CDFA8 000C8EA8  7F C3 F3 78 */	mr r3, r30
/* 800CDFAC 000C8EAC  7F A4 EB 78 */	mr r4, r29
/* 800CDFB0 000C8EB0  38 A0 00 32 */	li r5, 0x32
/* 800CDFB4 000C8EB4  4B F3 60 4D */	bl memcpy
/* 800CDFB8 000C8EB8  48 00 00 C4 */	b lbl_800CE07C
lbl_800CDFBC:
/* 800CDFBC 000C8EBC  38 03 FF FA */	addi r0, r3, -6
/* 800CDFC0 000C8EC0  28 00 00 02 */	cmplwi r0, 2
/* 800CDFC4 000C8EC4  41 81 00 18 */	bgt lbl_800CDFDC
/* 800CDFC8 000C8EC8  7F C3 F3 78 */	mr r3, r30
/* 800CDFCC 000C8ECC  7F A4 EB 78 */	mr r4, r29
/* 800CDFD0 000C8ED0  38 A0 00 36 */	li r5, 0x36
/* 800CDFD4 000C8ED4  4B F3 60 2D */	bl memcpy
/* 800CDFD8 000C8ED8  48 00 00 A4 */	b lbl_800CE07C
lbl_800CDFDC:
/* 800CDFDC 000C8EDC  7F C3 F3 78 */	mr r3, r30
/* 800CDFE0 000C8EE0  7F A4 EB 78 */	mr r4, r29
/* 800CDFE4 000C8EE4  38 A0 00 5A */	li r5, 0x5a
/* 800CDFE8 000C8EE8  4B F3 60 19 */	bl memcpy
/* 800CDFEC 000C8EEC  48 00 00 90 */	b lbl_800CE07C
lbl_800CDFF0:
/* 800CDFF0 000C8EF0  7F C3 F3 78 */	mr r3, r30
/* 800CDFF4 000C8EF4  7F A4 EB 78 */	mr r4, r29
/* 800CDFF8 000C8EF8  38 A0 00 2A */	li r5, 0x2a
/* 800CDFFC 000C8EFC  4B F3 60 05 */	bl memcpy
/* 800CE000 000C8F00  48 00 00 7C */	b lbl_800CE07C
lbl_800CE004:
/* 800CE004 000C8F04  80 64 08 B8 */	lwz r3, 0x8b8(r4)
/* 800CE008 000C8F08  28 03 00 02 */	cmplwi r3, 2
/* 800CE00C 000C8F0C  41 81 00 18 */	bgt lbl_800CE024
/* 800CE010 000C8F10  7F C3 F3 78 */	mr r3, r30
/* 800CE014 000C8F14  38 80 00 00 */	li r4, 0
/* 800CE018 000C8F18  38 A0 00 2A */	li r5, 0x2a
/* 800CE01C 000C8F1C  4B F3 60 E9 */	bl memset
/* 800CE020 000C8F20  48 00 00 54 */	b lbl_800CE074
lbl_800CE024:
/* 800CE024 000C8F24  38 03 FF FD */	addi r0, r3, -3
/* 800CE028 000C8F28  28 00 00 02 */	cmplwi r0, 2
/* 800CE02C 000C8F2C  41 81 00 18 */	bgt lbl_800CE044
/* 800CE030 000C8F30  7F C3 F3 78 */	mr r3, r30
/* 800CE034 000C8F34  38 80 00 00 */	li r4, 0
/* 800CE038 000C8F38  38 A0 00 32 */	li r5, 0x32
/* 800CE03C 000C8F3C  4B F3 60 C9 */	bl memset
/* 800CE040 000C8F40  48 00 00 34 */	b lbl_800CE074
lbl_800CE044:
/* 800CE044 000C8F44  38 03 FF FA */	addi r0, r3, -6
/* 800CE048 000C8F48  28 00 00 02 */	cmplwi r0, 2
/* 800CE04C 000C8F4C  41 81 00 18 */	bgt lbl_800CE064
/* 800CE050 000C8F50  7F C3 F3 78 */	mr r3, r30
/* 800CE054 000C8F54  38 80 00 00 */	li r4, 0
/* 800CE058 000C8F58  38 A0 00 36 */	li r5, 0x36
/* 800CE05C 000C8F5C  4B F3 60 A9 */	bl memset
/* 800CE060 000C8F60  48 00 00 14 */	b lbl_800CE074
lbl_800CE064:
/* 800CE064 000C8F64  7F C3 F3 78 */	mr r3, r30
/* 800CE068 000C8F68  38 80 00 00 */	li r4, 0
/* 800CE06C 000C8F6C  38 A0 00 5A */	li r5, 0x5a
/* 800CE070 000C8F70  4B F3 60 95 */	bl memset
lbl_800CE074:
/* 800CE074 000C8F74  88 1D 00 29 */	lbz r0, 0x29(r29)
/* 800CE078 000C8F78  98 1E 00 29 */	stb r0, 0x29(r30)
lbl_800CE07C:
/* 800CE07C 000C8F7C  7F E3 FB 78 */	mr r3, r31
/* 800CE080 000C8F80  48 02 38 69 */	bl OSRestoreInterrupts
/* 800CE084 000C8F84  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800CE088 000C8F88  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800CE08C 000C8F8C  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 800CE090 000C8F90  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 800CE094 000C8F94  7C 08 03 A6 */	mtlr r0
/* 800CE098 000C8F98  38 21 00 20 */	addi r1, r1, 0x20
/* 800CE09C 000C8F9C  4E 80 00 20 */	blr 

.global WPADSetAutoSamplingBuf
WPADSetAutoSamplingBuf:
/* 800CE0A0 000C8FA0  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800CE0A4 000C8FA4  7C 08 02 A6 */	mflr r0
/* 800CE0A8 000C8FA8  90 01 00 24 */	stw r0, 0x24(r1)
/* 800CE0AC 000C8FAC  39 61 00 20 */	addi r11, r1, 0x20
/* 800CE0B0 000C8FB0  4B FE 3C 91 */	bl _savegpr_26
/* 800CE0B4 000C8FB4  3C C0 80 3A */	lis r6, lbl_803996F8@ha
/* 800CE0B8 000C8FB8  7C 7A 1B 78 */	mr r26, r3
/* 800CE0BC 000C8FBC  7C 9E 23 78 */	mr r30, r4
/* 800CE0C0 000C8FC0  7C BF 2B 78 */	mr r31, r5
/* 800CE0C4 000C8FC4  38 66 96 F8 */	addi r3, r6, lbl_803996F8@l
/* 800CE0C8 000C8FC8  4C C6 31 82 */	crclr 6
/* 800CE0CC 000C8FCC  48 00 96 91 */	bl DEBUGPrint
/* 800CE0D0 000C8FD0  48 02 37 F1 */	bl OSDisableInterrupts
/* 800CE0D4 000C8FD4  3C 80 80 41 */	lis r4, _wpdcb@ha
/* 800CE0D8 000C8FD8  57 40 10 3A */	slwi r0, r26, 2
/* 800CE0DC 000C8FDC  38 84 F6 30 */	addi r4, r4, _wpdcb@l
/* 800CE0E0 000C8FE0  7C 7B 1B 78 */	mr r27, r3
/* 800CE0E4 000C8FE4  7F 84 00 2E */	lwzx r28, r4, r0
/* 800CE0E8 000C8FE8  3B A0 FF FC */	li r29, -4
/* 800CE0EC 000C8FEC  80 1C 08 BC */	lwz r0, 0x8bc(r28)
/* 800CE0F0 000C8FF0  2C 00 FF FF */	cmpwi r0, -1
/* 800CE0F4 000C8FF4  40 82 00 08 */	bne lbl_800CE0FC
/* 800CE0F8 000C8FF8  3B A0 FF FF */	li r29, -1
lbl_800CE0FC:
/* 800CE0FC 000C8FFC  80 7C 08 B8 */	lwz r3, 0x8b8(r28)
/* 800CE100 000C9000  28 03 00 02 */	cmplwi r3, 2
/* 800CE104 000C9004  41 81 00 0C */	bgt lbl_800CE110
/* 800CE108 000C9008  3B 40 00 2A */	li r26, 0x2a
/* 800CE10C 000C900C  48 00 00 2C */	b lbl_800CE138
lbl_800CE110:
/* 800CE110 000C9010  38 03 FF FD */	addi r0, r3, -3
/* 800CE114 000C9014  28 00 00 02 */	cmplwi r0, 2
/* 800CE118 000C9018  41 81 00 0C */	bgt lbl_800CE124
/* 800CE11C 000C901C  3B 40 00 32 */	li r26, 0x32
/* 800CE120 000C9020  48 00 00 18 */	b lbl_800CE138
lbl_800CE124:
/* 800CE124 000C9024  38 03 FF FA */	addi r0, r3, -6
/* 800CE128 000C9028  3B 40 00 5A */	li r26, 0x5a
/* 800CE12C 000C902C  28 00 00 02 */	cmplwi r0, 2
/* 800CE130 000C9030  41 81 00 08 */	bgt lbl_800CE138
/* 800CE134 000C9034  3B 40 00 36 */	li r26, 0x36
lbl_800CE138:
/* 800CE138 000C9038  2C 1E 00 00 */	cmpwi r30, 0
/* 800CE13C 000C903C  41 82 00 BC */	beq lbl_800CE1F8
/* 800CE140 000C9040  7C BA F9 D6 */	mullw r5, r26, r31
/* 800CE144 000C9044  7F C3 F3 78 */	mr r3, r30
/* 800CE148 000C9048  38 80 00 00 */	li r4, 0
/* 800CE14C 000C904C  4B F3 5F B9 */	bl memset
/* 800CE150 000C9050  28 1F 00 00 */	cmplwi r31, 0
/* 800CE154 000C9054  7F E3 FB 78 */	mr r3, r31
/* 800CE158 000C9058  38 80 00 00 */	li r4, 0
/* 800CE15C 000C905C  40 81 00 90 */	ble lbl_800CE1EC
/* 800CE160 000C9060  57 E0 E8 FF */	rlwinm. r0, r31, 0x1d, 3, 0x1f
/* 800CE164 000C9064  7C 09 03 A6 */	mtctr r0
/* 800CE168 000C9068  41 82 00 70 */	beq lbl_800CE1D8
lbl_800CE16C:
/* 800CE16C 000C906C  7C 7E 22 14 */	add r3, r30, r4
/* 800CE170 000C9070  7C 84 D2 14 */	add r4, r4, r26
/* 800CE174 000C9074  9B A3 00 29 */	stb r29, 0x29(r3)
/* 800CE178 000C9078  7C 7E 22 14 */	add r3, r30, r4
/* 800CE17C 000C907C  7C 84 D2 14 */	add r4, r4, r26
/* 800CE180 000C9080  9B A3 00 29 */	stb r29, 0x29(r3)
/* 800CE184 000C9084  7C 7E 22 14 */	add r3, r30, r4
/* 800CE188 000C9088  7C 84 D2 14 */	add r4, r4, r26
/* 800CE18C 000C908C  9B A3 00 29 */	stb r29, 0x29(r3)
/* 800CE190 000C9090  7C 7E 22 14 */	add r3, r30, r4
/* 800CE194 000C9094  7C 84 D2 14 */	add r4, r4, r26
/* 800CE198 000C9098  9B A3 00 29 */	stb r29, 0x29(r3)
/* 800CE19C 000C909C  7C 7E 22 14 */	add r3, r30, r4
/* 800CE1A0 000C90A0  7C 84 D2 14 */	add r4, r4, r26
/* 800CE1A4 000C90A4  9B A3 00 29 */	stb r29, 0x29(r3)
/* 800CE1A8 000C90A8  7C 7E 22 14 */	add r3, r30, r4
/* 800CE1AC 000C90AC  7C 84 D2 14 */	add r4, r4, r26
/* 800CE1B0 000C90B0  9B A3 00 29 */	stb r29, 0x29(r3)
/* 800CE1B4 000C90B4  7C 7E 22 14 */	add r3, r30, r4
/* 800CE1B8 000C90B8  7C 84 D2 14 */	add r4, r4, r26
/* 800CE1BC 000C90BC  9B A3 00 29 */	stb r29, 0x29(r3)
/* 800CE1C0 000C90C0  7C 7E 22 14 */	add r3, r30, r4
/* 800CE1C4 000C90C4  7C 84 D2 14 */	add r4, r4, r26
/* 800CE1C8 000C90C8  9B A3 00 29 */	stb r29, 0x29(r3)
/* 800CE1CC 000C90CC  42 00 FF A0 */	bdnz lbl_800CE16C
/* 800CE1D0 000C90D0  73 E3 00 07 */	andi. r3, r31, 7
/* 800CE1D4 000C90D4  41 82 00 18 */	beq lbl_800CE1EC
lbl_800CE1D8:
/* 800CE1D8 000C90D8  7C 69 03 A6 */	mtctr r3
lbl_800CE1DC:
/* 800CE1DC 000C90DC  7C 7E 22 14 */	add r3, r30, r4
/* 800CE1E0 000C90E0  7C 84 D2 14 */	add r4, r4, r26
/* 800CE1E4 000C90E4  9B A3 00 29 */	stb r29, 0x29(r3)
/* 800CE1E8 000C90E8  42 00 FF F4 */	bdnz lbl_800CE1DC
lbl_800CE1EC:
/* 800CE1EC 000C90EC  38 00 FF FF */	li r0, -1
/* 800CE1F0 000C90F0  90 1C 08 B0 */	stw r0, 0x8b0(r28)
/* 800CE1F4 000C90F4  93 FC 08 B4 */	stw r31, 0x8b4(r28)
lbl_800CE1F8:
/* 800CE1F8 000C90F8  93 DC 08 AC */	stw r30, 0x8ac(r28)
/* 800CE1FC 000C90FC  7F 63 DB 78 */	mr r3, r27
/* 800CE200 000C9100  48 02 36 E9 */	bl OSRestoreInterrupts
/* 800CE204 000C9104  39 61 00 20 */	addi r11, r1, 0x20
/* 800CE208 000C9108  4B FE 3B 85 */	bl _restgpr_26
/* 800CE20C 000C910C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800CE210 000C9110  7C 08 03 A6 */	mtlr r0
/* 800CE214 000C9114  38 21 00 20 */	addi r1, r1, 0x20
/* 800CE218 000C9118  4E 80 00 20 */	blr 

.global WPADiExcludeButton
WPADiExcludeButton:
/* 800CE21C 000C911C  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800CE220 000C9120  7C 08 02 A6 */	mflr r0
/* 800CE224 000C9124  3C 80 80 41 */	lis r4, _wpdcb@ha
/* 800CE228 000C9128  90 01 00 14 */	stw r0, 0x14(r1)
/* 800CE22C 000C912C  54 60 10 3A */	slwi r0, r3, 2
/* 800CE230 000C9130  38 84 F6 30 */	addi r4, r4, _wpdcb@l
/* 800CE234 000C9134  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800CE238 000C9138  7F E4 00 2E */	lwzx r31, r4, r0
/* 800CE23C 000C913C  48 02 36 85 */	bl OSDisableInterrupts
/* 800CE240 000C9140  88 1F 08 C8 */	lbz r0, 0x8c8(r31)
/* 800CE244 000C9144  7C 00 00 34 */	cntlzw r0, r0
/* 800CE248 000C9148  54 00 DE 3E */	rlwinm r0, r0, 0x1b, 0x18, 0x1f
/* 800CE24C 000C914C  1C 00 00 60 */	mulli r0, r0, 0x60
/* 800CE250 000C9150  7C DF 02 14 */	add r6, r31, r0
/* 800CE254 000C9154  A0 86 00 A0 */	lhz r4, 0xa0(r6)
/* 800CE258 000C9158  54 80 07 BE */	clrlwi r0, r4, 0x1e
/* 800CE25C 000C915C  2C 00 00 03 */	cmpwi r0, 3
/* 800CE260 000C9160  40 82 00 0C */	bne lbl_800CE26C
/* 800CE264 000C9164  54 80 07 FA */	rlwinm r0, r4, 0, 0x1f, 0x1d
/* 800CE268 000C9168  B0 06 00 A0 */	sth r0, 0xa0(r6)
lbl_800CE26C:
/* 800CE26C 000C916C  A0 86 00 A0 */	lhz r4, 0xa0(r6)
/* 800CE270 000C9170  54 80 07 3A */	rlwinm r0, r4, 0, 0x1c, 0x1d
/* 800CE274 000C9174  2C 00 00 0C */	cmpwi r0, 0xc
/* 800CE278 000C9178  40 82 00 0C */	bne lbl_800CE284
/* 800CE27C 000C917C  54 80 07 B8 */	rlwinm r0, r4, 0, 0x1e, 0x1c
/* 800CE280 000C9180  B0 06 00 A0 */	sth r0, 0xa0(r6)
lbl_800CE284:
/* 800CE284 000C9184  80 9F 08 B8 */	lwz r4, 0x8b8(r31)
/* 800CE288 000C9188  38 04 FF FA */	addi r0, r4, -6
/* 800CE28C 000C918C  28 00 00 02 */	cmplwi r0, 2
/* 800CE290 000C9190  41 81 00 38 */	bgt lbl_800CE2C8
/* 800CE294 000C9194  A0 A6 00 CA */	lhz r5, 0xca(r6)
/* 800CE298 000C9198  70 A4 80 02 */	andi. r4, r5, 0x8002
/* 800CE29C 000C919C  3C 04 00 00 */	addis r0, r4, 0
/* 800CE2A0 000C91A0  28 00 80 02 */	cmplwi r0, 0x8002
/* 800CE2A4 000C91A4  40 82 00 0C */	bne lbl_800CE2B0
/* 800CE2A8 000C91A8  54 A0 04 7E */	clrlwi r0, r5, 0x11
/* 800CE2AC 000C91AC  B0 06 00 CA */	sth r0, 0xca(r6)
lbl_800CE2B0:
/* 800CE2B0 000C91B0  A0 86 00 CA */	lhz r4, 0xca(r6)
/* 800CE2B4 000C91B4  70 80 40 01 */	andi. r0, r4, 0x4001
/* 800CE2B8 000C91B8  2C 00 40 01 */	cmpwi r0, 0x4001
/* 800CE2BC 000C91BC  40 82 00 0C */	bne lbl_800CE2C8
/* 800CE2C0 000C91C0  54 80 04 A0 */	rlwinm r0, r4, 0, 0x12, 0x10
/* 800CE2C4 000C91C4  B0 06 00 CA */	sth r0, 0xca(r6)
lbl_800CE2C8:
/* 800CE2C8 000C91C8  48 02 36 21 */	bl OSRestoreInterrupts
/* 800CE2CC 000C91CC  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800CE2D0 000C91D0  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 800CE2D4 000C91D4  7C 08 03 A6 */	mtlr r0
/* 800CE2D8 000C91D8  38 21 00 10 */	addi r1, r1, 0x10
/* 800CE2DC 000C91DC  4E 80 00 20 */	blr 

.global WPADiCopyOut
WPADiCopyOut:
/* 800CE2E0 000C91E0  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800CE2E4 000C91E4  7C 08 02 A6 */	mflr r0
/* 800CE2E8 000C91E8  3C 80 80 41 */	lis r4, _wpdcb@ha
/* 800CE2EC 000C91EC  90 01 00 24 */	stw r0, 0x24(r1)
/* 800CE2F0 000C91F0  54 60 10 3A */	slwi r0, r3, 2
/* 800CE2F4 000C91F4  38 84 F6 30 */	addi r4, r4, _wpdcb@l
/* 800CE2F8 000C91F8  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800CE2FC 000C91FC  93 C1 00 18 */	stw r30, 0x18(r1)
/* 800CE300 000C9200  93 A1 00 14 */	stw r29, 0x14(r1)
/* 800CE304 000C9204  7C 7D 1B 78 */	mr r29, r3
/* 800CE308 000C9208  7F E4 00 2E */	lwzx r31, r4, r0
/* 800CE30C 000C920C  48 02 35 B5 */	bl OSDisableInterrupts
/* 800CE310 000C9210  88 9F 08 C8 */	lbz r4, 0x8c8(r31)
/* 800CE314 000C9214  7C 7E 1B 78 */	mr r30, r3
/* 800CE318 000C9218  80 1F 08 AC */	lwz r0, 0x8ac(r31)
/* 800CE31C 000C921C  7C 83 00 34 */	cntlzw r3, r4
/* 800CE320 000C9220  54 63 DE 3E */	rlwinm r3, r3, 0x1b, 0x18, 0x1f
/* 800CE324 000C9224  2C 00 00 00 */	cmpwi r0, 0
/* 800CE328 000C9228  1C 03 00 60 */	mulli r0, r3, 0x60
/* 800CE32C 000C922C  7C 7F 02 14 */	add r3, r31, r0
/* 800CE330 000C9230  38 83 00 A0 */	addi r4, r3, 0xa0
/* 800CE334 000C9234  41 82 00 E4 */	beq lbl_800CE418
/* 800CE338 000C9238  80 7F 08 B0 */	lwz r3, 0x8b0(r31)
/* 800CE33C 000C923C  38 63 00 01 */	addi r3, r3, 1
/* 800CE340 000C9240  90 7F 08 B0 */	stw r3, 0x8b0(r31)
/* 800CE344 000C9244  80 1F 08 B4 */	lwz r0, 0x8b4(r31)
/* 800CE348 000C9248  7C 03 00 40 */	cmplw r3, r0
/* 800CE34C 000C924C  41 80 00 0C */	blt lbl_800CE358
/* 800CE350 000C9250  38 00 00 00 */	li r0, 0
/* 800CE354 000C9254  90 1F 08 B0 */	stw r0, 0x8b0(r31)
lbl_800CE358:
/* 800CE358 000C9258  80 7F 08 B8 */	lwz r3, 0x8b8(r31)
/* 800CE35C 000C925C  28 03 00 02 */	cmplwi r3, 2
/* 800CE360 000C9260  41 81 00 20 */	bgt lbl_800CE380
/* 800CE364 000C9264  80 1F 08 B0 */	lwz r0, 0x8b0(r31)
/* 800CE368 000C9268  38 A0 00 2A */	li r5, 0x2a
/* 800CE36C 000C926C  80 7F 08 AC */	lwz r3, 0x8ac(r31)
/* 800CE370 000C9270  1C 00 00 2A */	mulli r0, r0, 0x2a
/* 800CE374 000C9274  7C 63 02 14 */	add r3, r3, r0
/* 800CE378 000C9278  4B F3 5C 89 */	bl memcpy
/* 800CE37C 000C927C  48 00 00 9C */	b lbl_800CE418
lbl_800CE380:
/* 800CE380 000C9280  38 03 FF FD */	addi r0, r3, -3
/* 800CE384 000C9284  28 00 00 02 */	cmplwi r0, 2
/* 800CE388 000C9288  41 81 00 30 */	bgt lbl_800CE3B8
/* 800CE38C 000C928C  80 7F 08 B0 */	lwz r3, 0x8b0(r31)
/* 800CE390 000C9290  38 A0 00 2A */	li r5, 0x2a
/* 800CE394 000C9294  88 04 00 29 */	lbz r0, 0x29(r4)
/* 800CE398 000C9298  1C 63 00 32 */	mulli r3, r3, 0x32
/* 800CE39C 000C929C  80 DF 08 AC */	lwz r6, 0x8ac(r31)
/* 800CE3A0 000C92A0  7C 00 07 75 */	extsb. r0, r0
/* 800CE3A4 000C92A4  7C 66 1A 14 */	add r3, r6, r3
/* 800CE3A8 000C92A8  40 82 00 08 */	bne lbl_800CE3B0
/* 800CE3AC 000C92AC  38 A0 00 32 */	li r5, 0x32
lbl_800CE3B0:
/* 800CE3B0 000C92B0  4B F3 5C 51 */	bl memcpy
/* 800CE3B4 000C92B4  48 00 00 64 */	b lbl_800CE418
lbl_800CE3B8:
/* 800CE3B8 000C92B8  38 03 FF FA */	addi r0, r3, -6
/* 800CE3BC 000C92BC  28 00 00 02 */	cmplwi r0, 2
/* 800CE3C0 000C92C0  41 81 00 30 */	bgt lbl_800CE3F0
/* 800CE3C4 000C92C4  80 7F 08 B0 */	lwz r3, 0x8b0(r31)
/* 800CE3C8 000C92C8  38 A0 00 2A */	li r5, 0x2a
/* 800CE3CC 000C92CC  88 04 00 29 */	lbz r0, 0x29(r4)
/* 800CE3D0 000C92D0  1C 63 00 36 */	mulli r3, r3, 0x36
/* 800CE3D4 000C92D4  80 DF 08 AC */	lwz r6, 0x8ac(r31)
/* 800CE3D8 000C92D8  7C 00 07 75 */	extsb. r0, r0
/* 800CE3DC 000C92DC  7C 66 1A 14 */	add r3, r6, r3
/* 800CE3E0 000C92E0  40 82 00 08 */	bne lbl_800CE3E8
/* 800CE3E4 000C92E4  38 A0 00 36 */	li r5, 0x36
lbl_800CE3E8:
/* 800CE3E8 000C92E8  4B F3 5C 19 */	bl memcpy
/* 800CE3EC 000C92EC  48 00 00 2C */	b lbl_800CE418
lbl_800CE3F0:
/* 800CE3F0 000C92F0  80 7F 08 B0 */	lwz r3, 0x8b0(r31)
/* 800CE3F4 000C92F4  38 A0 00 2A */	li r5, 0x2a
/* 800CE3F8 000C92F8  88 04 00 29 */	lbz r0, 0x29(r4)
/* 800CE3FC 000C92FC  1C 63 00 5A */	mulli r3, r3, 0x5a
/* 800CE400 000C9300  80 DF 08 AC */	lwz r6, 0x8ac(r31)
/* 800CE404 000C9304  7C 00 07 75 */	extsb. r0, r0
/* 800CE408 000C9308  7C 66 1A 14 */	add r3, r6, r3
/* 800CE40C 000C930C  40 82 00 08 */	bne lbl_800CE414
/* 800CE410 000C9310  38 A0 00 5A */	li r5, 0x5a
lbl_800CE414:
/* 800CE414 000C9314  4B F3 5B ED */	bl memcpy
lbl_800CE418:
/* 800CE418 000C9318  81 9F 08 A8 */	lwz r12, 0x8a8(r31)
/* 800CE41C 000C931C  2C 0C 00 00 */	cmpwi r12, 0
/* 800CE420 000C9320  41 82 00 10 */	beq lbl_800CE430
/* 800CE424 000C9324  7F A3 EB 78 */	mr r3, r29
/* 800CE428 000C9328  7D 89 03 A6 */	mtctr r12
/* 800CE42C 000C932C  4E 80 04 21 */	bctrl 
lbl_800CE430:
/* 800CE430 000C9330  A0 9F 09 84 */	lhz r4, 0x984(r31)
/* 800CE434 000C9334  7F C3 F3 78 */	mr r3, r30
/* 800CE438 000C9338  38 04 00 01 */	addi r0, r4, 1
/* 800CE43C 000C933C  B0 1F 09 84 */	sth r0, 0x984(r31)
/* 800CE440 000C9340  48 02 34 A9 */	bl OSRestoreInterrupts
/* 800CE444 000C9344  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800CE448 000C9348  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800CE44C 000C934C  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 800CE450 000C9350  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 800CE454 000C9354  7C 08 03 A6 */	mtlr r0
/* 800CE458 000C9358  38 21 00 20 */	addi r1, r1, 0x20
/* 800CE45C 000C935C  4E 80 00 20 */	blr 

.global WPADIsSpeakerEnabled
WPADIsSpeakerEnabled:
/* 800CE460 000C9360  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800CE464 000C9364  7C 08 02 A6 */	mflr r0
/* 800CE468 000C9368  3C 80 80 41 */	lis r4, _wpdcb@ha
/* 800CE46C 000C936C  90 01 00 14 */	stw r0, 0x14(r1)
/* 800CE470 000C9370  54 60 10 3A */	slwi r0, r3, 2
/* 800CE474 000C9374  38 84 F6 30 */	addi r4, r4, _wpdcb@l
/* 800CE478 000C9378  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800CE47C 000C937C  7F E4 00 2E */	lwzx r31, r4, r0
/* 800CE480 000C9380  48 02 34 41 */	bl OSDisableInterrupts
/* 800CE484 000C9384  83 FF 08 3C */	lwz r31, 0x83c(r31)
/* 800CE488 000C9388  48 02 34 61 */	bl OSRestoreInterrupts
/* 800CE48C 000C938C  7F E3 FB 78 */	mr r3, r31
/* 800CE490 000C9390  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 800CE494 000C9394  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800CE498 000C9398  7C 08 03 A6 */	mtlr r0
/* 800CE49C 000C939C  38 21 00 10 */	addi r1, r1, 0x10
/* 800CE4A0 000C93A0  4E 80 00 20 */	blr 

.global WPADControlSpeaker
WPADControlSpeaker:
/* 800CE4A4 000C93A4  94 21 FA 00 */	stwu r1, -0x600(r1)
/* 800CE4A8 000C93A8  7C 08 02 A6 */	mflr r0
/* 800CE4AC 000C93AC  90 01 06 04 */	stw r0, 0x604(r1)
/* 800CE4B0 000C93B0  39 61 06 00 */	addi r11, r1, 0x600
/* 800CE4B4 000C93B4  4B FE 38 89 */	bl _savegpr_25
/* 800CE4B8 000C93B8  89 62 96 10 */	lbz r11, lbl_804C1030-_SDA2_BASE_(r2)
/* 800CE4BC 000C93BC  3C C0 80 41 */	lis r6, _wpdcb@ha
/* 800CE4C0 000C93C0  89 42 96 11 */	lbz r10, lbl_804C1031-_SDA2_BASE_(r2)
/* 800CE4C4 000C93C4  7C 99 23 78 */	mr r25, r4
/* 800CE4C8 000C93C8  89 22 96 12 */	lbz r9, lbl_804C1032-_SDA2_BASE_(r2)
/* 800CE4CC 000C93CC  54 60 10 3A */	slwi r0, r3, 2
/* 800CE4D0 000C93D0  89 02 96 13 */	lbz r8, lbl_804C1033-_SDA2_BASE_(r2)
/* 800CE4D4 000C93D4  7C 7B 1B 78 */	mr r27, r3
/* 800CE4D8 000C93D8  88 E2 96 14 */	lbz r7, lbl_804C1034-_SDA2_BASE_(r2)
/* 800CE4DC 000C93DC  38 C6 F6 30 */	addi r6, r6, _wpdcb@l
/* 800CE4E0 000C93E0  88 82 96 15 */	lbz r4, lbl_804C1035-_SDA2_BASE_(r2)
/* 800CE4E4 000C93E4  7C BC 2B 78 */	mr r28, r5
/* 800CE4E8 000C93E8  88 62 96 16 */	lbz r3, lbl_804C1036-_SDA2_BASE_(r2)
/* 800CE4EC 000C93EC  99 61 00 2C */	stb r11, 0x2c(r1)
/* 800CE4F0 000C93F0  7F E6 00 2E */	lwzx r31, r6, r0
/* 800CE4F4 000C93F4  99 41 00 2D */	stb r10, 0x2d(r1)
/* 800CE4F8 000C93F8  99 21 00 2E */	stb r9, 0x2e(r1)
/* 800CE4FC 000C93FC  99 01 00 2F */	stb r8, 0x2f(r1)
/* 800CE500 000C9400  98 E1 00 30 */	stb r7, 0x30(r1)
/* 800CE504 000C9404  98 81 00 31 */	stb r4, 0x31(r1)
/* 800CE508 000C9408  98 61 00 32 */	stb r3, 0x32(r1)
/* 800CE50C 000C940C  48 02 33 B5 */	bl OSDisableInterrupts
/* 800CE510 000C9410  83 BF 08 3C */	lwz r29, 0x83c(r31)
/* 800CE514 000C9414  83 5F 08 BC */	lwz r26, 0x8bc(r31)
/* 800CE518 000C9418  83 DF 08 DC */	lwz r30, 0x8dc(r31)
/* 800CE51C 000C941C  48 02 33 CD */	bl OSRestoreInterrupts
/* 800CE520 000C9420  2C 1A FF FF */	cmpwi r26, -1
/* 800CE524 000C9424  41 82 15 64 */	beq lbl_800CFA88
/* 800CE528 000C9428  2C 1E 00 00 */	cmpwi r30, 0
/* 800CE52C 000C942C  40 82 00 0C */	bne lbl_800CE538
/* 800CE530 000C9430  3B 40 FF FE */	li r26, -2
/* 800CE534 000C9434  48 00 15 54 */	b lbl_800CFA88
lbl_800CE538:
/* 800CE538 000C9438  2C 19 00 00 */	cmpwi r25, 0
/* 800CE53C 000C943C  40 82 07 18 */	bne lbl_800CEC54
/* 800CE540 000C9440  2C 1D 00 00 */	cmpwi r29, 0
/* 800CE544 000C9444  40 82 00 0C */	bne lbl_800CE550
/* 800CE548 000C9448  3B 40 00 00 */	li r26, 0
/* 800CE54C 000C944C  48 00 15 3C */	b lbl_800CFA88
lbl_800CE550:
/* 800CE550 000C9450  48 02 33 71 */	bl OSDisableInterrupts
/* 800CE554 000C9454  7C 7D 1B 78 */	mr r29, r3
/* 800CE558 000C9458  48 02 33 69 */	bl OSDisableInterrupts
/* 800CE55C 000C945C  88 9F 01 60 */	lbz r4, 0x160(r31)
/* 800CE560 000C9460  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CE564 000C9464  7C 04 00 50 */	subf r0, r4, r0
/* 800CE568 000C9468  7C 1E 07 75 */	extsb. r30, r0
/* 800CE56C 000C946C  40 80 00 10 */	bge lbl_800CE57C
/* 800CE570 000C9470  80 1F 01 68 */	lwz r0, 0x168(r31)
/* 800CE574 000C9474  7C 1E 02 14 */	add r0, r30, r0
/* 800CE578 000C9478  7C 1E 07 74 */	extsb r30, r0
lbl_800CE57C:
/* 800CE57C 000C947C  48 02 33 6D */	bl OSRestoreInterrupts
/* 800CE580 000C9480  80 7F 01 68 */	lwz r3, 0x168(r31)
/* 800CE584 000C9484  38 9E 00 05 */	addi r4, r30, 5
/* 800CE588 000C9488  38 03 FF FF */	addi r0, r3, -1
/* 800CE58C 000C948C  7C 04 00 40 */	cmplw r4, r0
/* 800CE590 000C9490  41 81 06 B4 */	bgt lbl_800CEC44
/* 800CE594 000C9494  38 60 00 01 */	li r3, 1
/* 800CE598 000C9498  38 00 00 04 */	li r0, 4
/* 800CE59C 000C949C  B0 61 05 92 */	sth r3, 0x592(r1)
/* 800CE5A0 000C94A0  3B 60 00 19 */	li r27, 0x19
/* 800CE5A4 000C94A4  39 80 00 00 */	li r12, 0
/* 800CE5A8 000C94A8  81 41 05 80 */	lwz r10, 0x580(r1)
/* 800CE5AC 000C94AC  98 01 05 7C */	stb r0, 0x57c(r1)
/* 800CE5B0 000C94B0  81 21 05 84 */	lwz r9, 0x584(r1)
/* 800CE5B4 000C94B4  81 61 05 7C */	lwz r11, 0x57c(r1)
/* 800CE5B8 000C94B8  81 01 05 88 */	lwz r8, 0x588(r1)
/* 800CE5BC 000C94BC  80 E1 05 8C */	lwz r7, 0x58c(r1)
/* 800CE5C0 000C94C0  80 C1 05 90 */	lwz r6, 0x590(r1)
/* 800CE5C4 000C94C4  80 A1 05 94 */	lwz r5, 0x594(r1)
/* 800CE5C8 000C94C8  80 81 05 98 */	lwz r4, 0x598(r1)
/* 800CE5CC 000C94CC  80 61 05 9C */	lwz r3, 0x59c(r1)
/* 800CE5D0 000C94D0  80 01 05 A0 */	lwz r0, 0x5a0(r1)
/* 800CE5D4 000C94D4  93 61 05 78 */	stw r27, 0x578(r1)
/* 800CE5D8 000C94D8  91 81 05 A4 */	stw r12, 0x5a4(r1)
/* 800CE5DC 000C94DC  93 61 05 A8 */	stw r27, 0x5a8(r1)
/* 800CE5E0 000C94E0  91 61 05 AC */	stw r11, 0x5ac(r1)
/* 800CE5E4 000C94E4  91 41 05 B0 */	stw r10, 0x5b0(r1)
/* 800CE5E8 000C94E8  91 21 05 B4 */	stw r9, 0x5b4(r1)
/* 800CE5EC 000C94EC  91 01 05 B8 */	stw r8, 0x5b8(r1)
/* 800CE5F0 000C94F0  90 E1 05 BC */	stw r7, 0x5bc(r1)
/* 800CE5F4 000C94F4  90 C1 05 C0 */	stw r6, 0x5c0(r1)
/* 800CE5F8 000C94F8  90 A1 05 C4 */	stw r5, 0x5c4(r1)
/* 800CE5FC 000C94FC  90 81 05 C8 */	stw r4, 0x5c8(r1)
/* 800CE600 000C9500  90 61 05 CC */	stw r3, 0x5cc(r1)
/* 800CE604 000C9504  90 01 05 D0 */	stw r0, 0x5d0(r1)
/* 800CE608 000C9508  91 81 05 D4 */	stw r12, 0x5d4(r1)
/* 800CE60C 000C950C  48 02 32 B5 */	bl OSDisableInterrupts
/* 800CE610 000C9510  7C 7E 1B 78 */	mr r30, r3
/* 800CE614 000C9514  48 02 32 AD */	bl OSDisableInterrupts
/* 800CE618 000C9518  88 9F 01 60 */	lbz r4, 0x160(r31)
/* 800CE61C 000C951C  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CE620 000C9520  7C 04 00 50 */	subf r0, r4, r0
/* 800CE624 000C9524  7C 1B 07 75 */	extsb. r27, r0
/* 800CE628 000C9528  40 80 00 10 */	bge lbl_800CE638
/* 800CE62C 000C952C  80 1F 01 68 */	lwz r0, 0x168(r31)
/* 800CE630 000C9530  7C 1B 02 14 */	add r0, r27, r0
/* 800CE634 000C9534  7C 1B 07 74 */	extsb r27, r0
lbl_800CE638:
/* 800CE638 000C9538  48 02 32 B1 */	bl OSRestoreInterrupts
/* 800CE63C 000C953C  80 7F 01 68 */	lwz r3, 0x168(r31)
/* 800CE640 000C9540  38 03 FF FF */	addi r0, r3, -1
/* 800CE644 000C9544  7C 00 D8 40 */	cmplw r0, r27
/* 800CE648 000C9548  40 82 00 10 */	bne lbl_800CE658
/* 800CE64C 000C954C  7F C3 F3 78 */	mr r3, r30
/* 800CE650 000C9550  48 02 32 99 */	bl OSRestoreInterrupts
/* 800CE654 000C9554  48 00 00 78 */	b lbl_800CE6CC
lbl_800CE658:
/* 800CE658 000C9558  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CE65C 000C955C  38 80 00 00 */	li r4, 0
/* 800CE660 000C9560  80 7F 01 64 */	lwz r3, 0x164(r31)
/* 800CE664 000C9564  38 A0 00 30 */	li r5, 0x30
/* 800CE668 000C9568  7C 00 07 74 */	extsb r0, r0
/* 800CE66C 000C956C  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CE670 000C9570  7C 63 02 14 */	add r3, r3, r0
/* 800CE674 000C9574  4B F3 5A 91 */	bl memset
/* 800CE678 000C9578  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CE67C 000C957C  38 81 05 A8 */	addi r4, r1, 0x5a8
/* 800CE680 000C9580  80 7F 01 64 */	lwz r3, 0x164(r31)
/* 800CE684 000C9584  38 A0 00 30 */	li r5, 0x30
/* 800CE688 000C9588  7C 00 07 74 */	extsb r0, r0
/* 800CE68C 000C958C  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CE690 000C9590  7C 63 02 14 */	add r3, r3, r0
/* 800CE694 000C9594  4B F3 59 6D */	bl memcpy
/* 800CE698 000C9598  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CE69C 000C959C  7F C3 F3 78 */	mr r3, r30
/* 800CE6A0 000C95A0  80 9F 01 68 */	lwz r4, 0x168(r31)
/* 800CE6A4 000C95A4  7C 06 07 74 */	extsb r6, r0
/* 800CE6A8 000C95A8  38 84 FF FF */	addi r4, r4, -1
/* 800CE6AC 000C95AC  7C A4 30 50 */	subf r5, r4, r6
/* 800CE6B0 000C95B0  38 06 00 01 */	addi r0, r6, 1
/* 800CE6B4 000C95B4  7C 86 20 50 */	subf r4, r6, r4
/* 800CE6B8 000C95B8  7C A4 20 F8 */	nor r4, r5, r4
/* 800CE6BC 000C95BC  7C 84 FE 70 */	srawi r4, r4, 0x1f
/* 800CE6C0 000C95C0  7C 00 20 78 */	andc r0, r0, r4
/* 800CE6C4 000C95C4  98 1F 01 61 */	stb r0, 0x161(r31)
/* 800CE6C8 000C95C8  48 02 32 21 */	bl OSRestoreInterrupts
lbl_800CE6CC:
/* 800CE6CC 000C95CC  3C 60 04 A2 */	lis r3, 0x04A20001@ha
/* 800CE6D0 000C95D0  39 20 00 01 */	li r9, 1
/* 800CE6D4 000C95D4  39 03 00 01 */	addi r8, r3, 0x04A20001@l
/* 800CE6D8 000C95D8  38 E0 00 16 */	li r7, 0x16
/* 800CE6DC 000C95DC  38 C0 00 15 */	li r6, 0x15
/* 800CE6E0 000C95E0  38 00 00 00 */	li r0, 0
/* 800CE6E4 000C95E4  99 21 00 12 */	stb r9, 0x12(r1)
/* 800CE6E8 000C95E8  38 61 05 4C */	addi r3, r1, 0x54c
/* 800CE6EC 000C95EC  38 81 00 28 */	addi r4, r1, 0x28
/* 800CE6F0 000C95F0  38 A0 00 04 */	li r5, 4
/* 800CE6F4 000C95F4  91 01 00 28 */	stw r8, 0x28(r1)
/* 800CE6F8 000C95F8  99 21 00 11 */	stb r9, 0x11(r1)
/* 800CE6FC 000C95FC  90 E1 05 48 */	stw r7, 0x548(r1)
/* 800CE700 000C9600  B0 C1 05 62 */	sth r6, 0x562(r1)
/* 800CE704 000C9604  90 01 05 74 */	stw r0, 0x574(r1)
/* 800CE708 000C9608  4B F3 58 F9 */	bl memcpy
/* 800CE70C 000C960C  38 61 05 50 */	addi r3, r1, 0x550
/* 800CE710 000C9610  38 81 00 11 */	addi r4, r1, 0x11
/* 800CE714 000C9614  38 A0 00 01 */	li r5, 1
/* 800CE718 000C9618  4B F3 58 E9 */	bl memcpy
/* 800CE71C 000C961C  38 61 05 51 */	addi r3, r1, 0x551
/* 800CE720 000C9620  38 81 00 12 */	addi r4, r1, 0x12
/* 800CE724 000C9624  38 A0 00 01 */	li r5, 1
/* 800CE728 000C9628  4B F3 58 D9 */	bl memcpy
/* 800CE72C 000C962C  83 61 05 48 */	lwz r27, 0x548(r1)
/* 800CE730 000C9630  81 81 05 4C */	lwz r12, 0x54c(r1)
/* 800CE734 000C9634  81 61 05 50 */	lwz r11, 0x550(r1)
/* 800CE738 000C9638  81 41 05 54 */	lwz r10, 0x554(r1)
/* 800CE73C 000C963C  81 21 05 58 */	lwz r9, 0x558(r1)
/* 800CE740 000C9640  81 01 05 5C */	lwz r8, 0x55c(r1)
/* 800CE744 000C9644  80 E1 05 60 */	lwz r7, 0x560(r1)
/* 800CE748 000C9648  80 C1 05 64 */	lwz r6, 0x564(r1)
/* 800CE74C 000C964C  80 A1 05 68 */	lwz r5, 0x568(r1)
/* 800CE750 000C9650  80 81 05 6C */	lwz r4, 0x56c(r1)
/* 800CE754 000C9654  80 61 05 70 */	lwz r3, 0x570(r1)
/* 800CE758 000C9658  80 01 05 74 */	lwz r0, 0x574(r1)
/* 800CE75C 000C965C  93 61 05 18 */	stw r27, 0x518(r1)
/* 800CE760 000C9660  91 81 05 1C */	stw r12, 0x51c(r1)
/* 800CE764 000C9664  91 61 05 20 */	stw r11, 0x520(r1)
/* 800CE768 000C9668  91 41 05 24 */	stw r10, 0x524(r1)
/* 800CE76C 000C966C  91 21 05 28 */	stw r9, 0x528(r1)
/* 800CE770 000C9670  91 01 05 2C */	stw r8, 0x52c(r1)
/* 800CE774 000C9674  90 E1 05 30 */	stw r7, 0x530(r1)
/* 800CE778 000C9678  90 C1 05 34 */	stw r6, 0x534(r1)
/* 800CE77C 000C967C  90 A1 05 38 */	stw r5, 0x538(r1)
/* 800CE780 000C9680  90 81 05 3C */	stw r4, 0x53c(r1)
/* 800CE784 000C9684  90 61 05 40 */	stw r3, 0x540(r1)
/* 800CE788 000C9688  90 01 05 44 */	stw r0, 0x544(r1)
/* 800CE78C 000C968C  48 02 31 35 */	bl OSDisableInterrupts
/* 800CE790 000C9690  7C 7E 1B 78 */	mr r30, r3
/* 800CE794 000C9694  48 02 31 2D */	bl OSDisableInterrupts
/* 800CE798 000C9698  88 9F 01 60 */	lbz r4, 0x160(r31)
/* 800CE79C 000C969C  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CE7A0 000C96A0  7C 04 00 50 */	subf r0, r4, r0
/* 800CE7A4 000C96A4  7C 1B 07 75 */	extsb. r27, r0
/* 800CE7A8 000C96A8  40 80 00 10 */	bge lbl_800CE7B8
/* 800CE7AC 000C96AC  80 1F 01 68 */	lwz r0, 0x168(r31)
/* 800CE7B0 000C96B0  7C 1B 02 14 */	add r0, r27, r0
/* 800CE7B4 000C96B4  7C 1B 07 74 */	extsb r27, r0
lbl_800CE7B8:
/* 800CE7B8 000C96B8  48 02 31 31 */	bl OSRestoreInterrupts
/* 800CE7BC 000C96BC  80 7F 01 68 */	lwz r3, 0x168(r31)
/* 800CE7C0 000C96C0  38 03 FF FF */	addi r0, r3, -1
/* 800CE7C4 000C96C4  7C 00 D8 40 */	cmplw r0, r27
/* 800CE7C8 000C96C8  40 82 00 10 */	bne lbl_800CE7D8
/* 800CE7CC 000C96CC  7F C3 F3 78 */	mr r3, r30
/* 800CE7D0 000C96D0  48 02 31 19 */	bl OSRestoreInterrupts
/* 800CE7D4 000C96D4  48 00 00 78 */	b lbl_800CE84C
lbl_800CE7D8:
/* 800CE7D8 000C96D8  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CE7DC 000C96DC  38 80 00 00 */	li r4, 0
/* 800CE7E0 000C96E0  80 7F 01 64 */	lwz r3, 0x164(r31)
/* 800CE7E4 000C96E4  38 A0 00 30 */	li r5, 0x30
/* 800CE7E8 000C96E8  7C 00 07 74 */	extsb r0, r0
/* 800CE7EC 000C96EC  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CE7F0 000C96F0  7C 63 02 14 */	add r3, r3, r0
/* 800CE7F4 000C96F4  4B F3 59 11 */	bl memset
/* 800CE7F8 000C96F8  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CE7FC 000C96FC  38 81 05 18 */	addi r4, r1, 0x518
/* 800CE800 000C9700  80 7F 01 64 */	lwz r3, 0x164(r31)
/* 800CE804 000C9704  38 A0 00 30 */	li r5, 0x30
/* 800CE808 000C9708  7C 00 07 74 */	extsb r0, r0
/* 800CE80C 000C970C  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CE810 000C9710  7C 63 02 14 */	add r3, r3, r0
/* 800CE814 000C9714  4B F3 57 ED */	bl memcpy
/* 800CE818 000C9718  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CE81C 000C971C  7F C3 F3 78 */	mr r3, r30
/* 800CE820 000C9720  80 9F 01 68 */	lwz r4, 0x168(r31)
/* 800CE824 000C9724  7C 06 07 74 */	extsb r6, r0
/* 800CE828 000C9728  38 84 FF FF */	addi r4, r4, -1
/* 800CE82C 000C972C  7C A4 30 50 */	subf r5, r4, r6
/* 800CE830 000C9730  38 06 00 01 */	addi r0, r6, 1
/* 800CE834 000C9734  7C 86 20 50 */	subf r4, r6, r4
/* 800CE838 000C9738  7C A4 20 F8 */	nor r4, r5, r4
/* 800CE83C 000C973C  7C 84 FE 70 */	srawi r4, r4, 0x1f
/* 800CE840 000C9740  7C 00 20 78 */	andc r0, r0, r4
/* 800CE844 000C9744  98 1F 01 61 */	stb r0, 0x161(r31)
/* 800CE848 000C9748  48 02 30 A1 */	bl OSRestoreInterrupts
lbl_800CE84C:
/* 800CE84C 000C974C  3C 60 04 A2 */	lis r3, 0x04A20009@ha
/* 800CE850 000C9750  39 20 00 00 */	li r9, 0
/* 800CE854 000C9754  39 03 00 09 */	addi r8, r3, 0x04A20009@l
/* 800CE858 000C9758  38 E0 00 01 */	li r7, 1
/* 800CE85C 000C975C  38 C0 00 16 */	li r6, 0x16
/* 800CE860 000C9760  38 00 00 15 */	li r0, 0x15
/* 800CE864 000C9764  99 21 00 10 */	stb r9, 0x10(r1)
/* 800CE868 000C9768  38 61 04 EC */	addi r3, r1, 0x4ec
/* 800CE86C 000C976C  38 81 00 24 */	addi r4, r1, 0x24
/* 800CE870 000C9770  38 A0 00 04 */	li r5, 4
/* 800CE874 000C9774  91 01 00 24 */	stw r8, 0x24(r1)
/* 800CE878 000C9778  98 E1 00 0F */	stb r7, 0xf(r1)
/* 800CE87C 000C977C  90 C1 04 E8 */	stw r6, 0x4e8(r1)
/* 800CE880 000C9780  B0 01 05 02 */	sth r0, 0x502(r1)
/* 800CE884 000C9784  91 21 05 14 */	stw r9, 0x514(r1)
/* 800CE888 000C9788  4B F3 57 79 */	bl memcpy
/* 800CE88C 000C978C  38 61 04 F0 */	addi r3, r1, 0x4f0
/* 800CE890 000C9790  38 81 00 0F */	addi r4, r1, 0xf
/* 800CE894 000C9794  38 A0 00 01 */	li r5, 1
/* 800CE898 000C9798  4B F3 57 69 */	bl memcpy
/* 800CE89C 000C979C  38 61 04 F1 */	addi r3, r1, 0x4f1
/* 800CE8A0 000C97A0  38 81 00 10 */	addi r4, r1, 0x10
/* 800CE8A4 000C97A4  38 A0 00 01 */	li r5, 1
/* 800CE8A8 000C97A8  4B F3 57 59 */	bl memcpy
/* 800CE8AC 000C97AC  83 61 04 E8 */	lwz r27, 0x4e8(r1)
/* 800CE8B0 000C97B0  81 81 04 EC */	lwz r12, 0x4ec(r1)
/* 800CE8B4 000C97B4  81 61 04 F0 */	lwz r11, 0x4f0(r1)
/* 800CE8B8 000C97B8  81 41 04 F4 */	lwz r10, 0x4f4(r1)
/* 800CE8BC 000C97BC  81 21 04 F8 */	lwz r9, 0x4f8(r1)
/* 800CE8C0 000C97C0  81 01 04 FC */	lwz r8, 0x4fc(r1)
/* 800CE8C4 000C97C4  80 E1 05 00 */	lwz r7, 0x500(r1)
/* 800CE8C8 000C97C8  80 C1 05 04 */	lwz r6, 0x504(r1)
/* 800CE8CC 000C97CC  80 A1 05 08 */	lwz r5, 0x508(r1)
/* 800CE8D0 000C97D0  80 81 05 0C */	lwz r4, 0x50c(r1)
/* 800CE8D4 000C97D4  80 61 05 10 */	lwz r3, 0x510(r1)
/* 800CE8D8 000C97D8  80 01 05 14 */	lwz r0, 0x514(r1)
/* 800CE8DC 000C97DC  93 61 04 B8 */	stw r27, 0x4b8(r1)
/* 800CE8E0 000C97E0  91 81 04 BC */	stw r12, 0x4bc(r1)
/* 800CE8E4 000C97E4  91 61 04 C0 */	stw r11, 0x4c0(r1)
/* 800CE8E8 000C97E8  91 41 04 C4 */	stw r10, 0x4c4(r1)
/* 800CE8EC 000C97EC  91 21 04 C8 */	stw r9, 0x4c8(r1)
/* 800CE8F0 000C97F0  91 01 04 CC */	stw r8, 0x4cc(r1)
/* 800CE8F4 000C97F4  90 E1 04 D0 */	stw r7, 0x4d0(r1)
/* 800CE8F8 000C97F8  90 C1 04 D4 */	stw r6, 0x4d4(r1)
/* 800CE8FC 000C97FC  90 A1 04 D8 */	stw r5, 0x4d8(r1)
/* 800CE900 000C9800  90 81 04 DC */	stw r4, 0x4dc(r1)
/* 800CE904 000C9804  90 61 04 E0 */	stw r3, 0x4e0(r1)
/* 800CE908 000C9808  90 01 04 E4 */	stw r0, 0x4e4(r1)
/* 800CE90C 000C980C  48 02 2F B5 */	bl OSDisableInterrupts
/* 800CE910 000C9810  7C 7E 1B 78 */	mr r30, r3
/* 800CE914 000C9814  48 02 2F AD */	bl OSDisableInterrupts
/* 800CE918 000C9818  88 9F 01 60 */	lbz r4, 0x160(r31)
/* 800CE91C 000C981C  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CE920 000C9820  7C 04 00 50 */	subf r0, r4, r0
/* 800CE924 000C9824  7C 1B 07 75 */	extsb. r27, r0
/* 800CE928 000C9828  40 80 00 10 */	bge lbl_800CE938
/* 800CE92C 000C982C  80 1F 01 68 */	lwz r0, 0x168(r31)
/* 800CE930 000C9830  7C 1B 02 14 */	add r0, r27, r0
/* 800CE934 000C9834  7C 1B 07 74 */	extsb r27, r0
lbl_800CE938:
/* 800CE938 000C9838  48 02 2F B1 */	bl OSRestoreInterrupts
/* 800CE93C 000C983C  80 7F 01 68 */	lwz r3, 0x168(r31)
/* 800CE940 000C9840  38 03 FF FF */	addi r0, r3, -1
/* 800CE944 000C9844  7C 00 D8 40 */	cmplw r0, r27
/* 800CE948 000C9848  40 82 00 10 */	bne lbl_800CE958
/* 800CE94C 000C984C  7F C3 F3 78 */	mr r3, r30
/* 800CE950 000C9850  48 02 2F 99 */	bl OSRestoreInterrupts
/* 800CE954 000C9854  48 00 00 78 */	b lbl_800CE9CC
lbl_800CE958:
/* 800CE958 000C9858  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CE95C 000C985C  38 80 00 00 */	li r4, 0
/* 800CE960 000C9860  80 7F 01 64 */	lwz r3, 0x164(r31)
/* 800CE964 000C9864  38 A0 00 30 */	li r5, 0x30
/* 800CE968 000C9868  7C 00 07 74 */	extsb r0, r0
/* 800CE96C 000C986C  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CE970 000C9870  7C 63 02 14 */	add r3, r3, r0
/* 800CE974 000C9874  4B F3 57 91 */	bl memset
/* 800CE978 000C9878  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CE97C 000C987C  38 81 04 B8 */	addi r4, r1, 0x4b8
/* 800CE980 000C9880  80 7F 01 64 */	lwz r3, 0x164(r31)
/* 800CE984 000C9884  38 A0 00 30 */	li r5, 0x30
/* 800CE988 000C9888  7C 00 07 74 */	extsb r0, r0
/* 800CE98C 000C988C  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CE990 000C9890  7C 63 02 14 */	add r3, r3, r0
/* 800CE994 000C9894  4B F3 56 6D */	bl memcpy
/* 800CE998 000C9898  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CE99C 000C989C  7F C3 F3 78 */	mr r3, r30
/* 800CE9A0 000C98A0  80 9F 01 68 */	lwz r4, 0x168(r31)
/* 800CE9A4 000C98A4  7C 06 07 74 */	extsb r6, r0
/* 800CE9A8 000C98A8  38 84 FF FF */	addi r4, r4, -1
/* 800CE9AC 000C98AC  7C A4 30 50 */	subf r5, r4, r6
/* 800CE9B0 000C98B0  38 06 00 01 */	addi r0, r6, 1
/* 800CE9B4 000C98B4  7C 86 20 50 */	subf r4, r6, r4
/* 800CE9B8 000C98B8  7C A4 20 F8 */	nor r4, r5, r4
/* 800CE9BC 000C98BC  7C 84 FE 70 */	srawi r4, r4, 0x1f
/* 800CE9C0 000C98C0  7C 00 20 78 */	andc r0, r0, r4
/* 800CE9C4 000C98C4  98 1F 01 61 */	stb r0, 0x161(r31)
/* 800CE9C8 000C98C8  48 02 2F 21 */	bl OSRestoreInterrupts
lbl_800CE9CC:
/* 800CE9CC 000C98CC  39 80 00 00 */	li r12, 0
/* 800CE9D0 000C98D0  38 00 00 01 */	li r0, 1
/* 800CE9D4 000C98D4  B0 01 04 72 */	sth r0, 0x472(r1)
/* 800CE9D8 000C98D8  3B 60 00 14 */	li r27, 0x14
/* 800CE9DC 000C98DC  81 41 04 60 */	lwz r10, 0x460(r1)
/* 800CE9E0 000C98E0  99 81 04 5C */	stb r12, 0x45c(r1)
/* 800CE9E4 000C98E4  81 21 04 64 */	lwz r9, 0x464(r1)
/* 800CE9E8 000C98E8  81 61 04 5C */	lwz r11, 0x45c(r1)
/* 800CE9EC 000C98EC  81 01 04 68 */	lwz r8, 0x468(r1)
/* 800CE9F0 000C98F0  80 E1 04 6C */	lwz r7, 0x46c(r1)
/* 800CE9F4 000C98F4  80 C1 04 70 */	lwz r6, 0x470(r1)
/* 800CE9F8 000C98F8  80 A1 04 74 */	lwz r5, 0x474(r1)
/* 800CE9FC 000C98FC  80 81 04 78 */	lwz r4, 0x478(r1)
/* 800CEA00 000C9900  80 61 04 7C */	lwz r3, 0x47c(r1)
/* 800CEA04 000C9904  80 01 04 80 */	lwz r0, 0x480(r1)
/* 800CEA08 000C9908  93 61 04 58 */	stw r27, 0x458(r1)
/* 800CEA0C 000C990C  91 81 04 84 */	stw r12, 0x484(r1)
/* 800CEA10 000C9910  93 61 04 88 */	stw r27, 0x488(r1)
/* 800CEA14 000C9914  91 61 04 8C */	stw r11, 0x48c(r1)
/* 800CEA18 000C9918  91 41 04 90 */	stw r10, 0x490(r1)
/* 800CEA1C 000C991C  91 21 04 94 */	stw r9, 0x494(r1)
/* 800CEA20 000C9920  91 01 04 98 */	stw r8, 0x498(r1)
/* 800CEA24 000C9924  90 E1 04 9C */	stw r7, 0x49c(r1)
/* 800CEA28 000C9928  90 C1 04 A0 */	stw r6, 0x4a0(r1)
/* 800CEA2C 000C992C  90 A1 04 A4 */	stw r5, 0x4a4(r1)
/* 800CEA30 000C9930  90 81 04 A8 */	stw r4, 0x4a8(r1)
/* 800CEA34 000C9934  90 61 04 AC */	stw r3, 0x4ac(r1)
/* 800CEA38 000C9938  90 01 04 B0 */	stw r0, 0x4b0(r1)
/* 800CEA3C 000C993C  91 81 04 B4 */	stw r12, 0x4b4(r1)
/* 800CEA40 000C9940  48 02 2E 81 */	bl OSDisableInterrupts
/* 800CEA44 000C9944  7C 7E 1B 78 */	mr r30, r3
/* 800CEA48 000C9948  48 02 2E 79 */	bl OSDisableInterrupts
/* 800CEA4C 000C994C  88 9F 01 60 */	lbz r4, 0x160(r31)
/* 800CEA50 000C9950  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CEA54 000C9954  7C 04 00 50 */	subf r0, r4, r0
/* 800CEA58 000C9958  7C 1B 07 75 */	extsb. r27, r0
/* 800CEA5C 000C995C  40 80 00 10 */	bge lbl_800CEA6C
/* 800CEA60 000C9960  80 1F 01 68 */	lwz r0, 0x168(r31)
/* 800CEA64 000C9964  7C 1B 02 14 */	add r0, r27, r0
/* 800CEA68 000C9968  7C 1B 07 74 */	extsb r27, r0
lbl_800CEA6C:
/* 800CEA6C 000C996C  48 02 2E 7D */	bl OSRestoreInterrupts
/* 800CEA70 000C9970  80 7F 01 68 */	lwz r3, 0x168(r31)
/* 800CEA74 000C9974  38 03 FF FF */	addi r0, r3, -1
/* 800CEA78 000C9978  7C 00 D8 40 */	cmplw r0, r27
/* 800CEA7C 000C997C  40 82 00 10 */	bne lbl_800CEA8C
/* 800CEA80 000C9980  7F C3 F3 78 */	mr r3, r30
/* 800CEA84 000C9984  48 02 2E 65 */	bl OSRestoreInterrupts
/* 800CEA88 000C9988  48 00 00 78 */	b lbl_800CEB00
lbl_800CEA8C:
/* 800CEA8C 000C998C  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CEA90 000C9990  38 80 00 00 */	li r4, 0
/* 800CEA94 000C9994  80 7F 01 64 */	lwz r3, 0x164(r31)
/* 800CEA98 000C9998  38 A0 00 30 */	li r5, 0x30
/* 800CEA9C 000C999C  7C 00 07 74 */	extsb r0, r0
/* 800CEAA0 000C99A0  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CEAA4 000C99A4  7C 63 02 14 */	add r3, r3, r0
/* 800CEAA8 000C99A8  4B F3 56 5D */	bl memset
/* 800CEAAC 000C99AC  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CEAB0 000C99B0  38 81 04 88 */	addi r4, r1, 0x488
/* 800CEAB4 000C99B4  80 7F 01 64 */	lwz r3, 0x164(r31)
/* 800CEAB8 000C99B8  38 A0 00 30 */	li r5, 0x30
/* 800CEABC 000C99BC  7C 00 07 74 */	extsb r0, r0
/* 800CEAC0 000C99C0  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CEAC4 000C99C4  7C 63 02 14 */	add r3, r3, r0
/* 800CEAC8 000C99C8  4B F3 55 39 */	bl memcpy
/* 800CEACC 000C99CC  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CEAD0 000C99D0  7F C3 F3 78 */	mr r3, r30
/* 800CEAD4 000C99D4  80 9F 01 68 */	lwz r4, 0x168(r31)
/* 800CEAD8 000C99D8  7C 06 07 74 */	extsb r6, r0
/* 800CEADC 000C99DC  38 84 FF FF */	addi r4, r4, -1
/* 800CEAE0 000C99E0  7C A4 30 50 */	subf r5, r4, r6
/* 800CEAE4 000C99E4  38 06 00 01 */	addi r0, r6, 1
/* 800CEAE8 000C99E8  7C 86 20 50 */	subf r4, r6, r4
/* 800CEAEC 000C99EC  7C A4 20 F8 */	nor r4, r5, r4
/* 800CEAF0 000C99F0  7C 84 FE 70 */	srawi r4, r4, 0x1f
/* 800CEAF4 000C99F4  7C 00 20 78 */	andc r0, r0, r4
/* 800CEAF8 000C99F8  98 1F 01 61 */	stb r0, 0x161(r31)
/* 800CEAFC 000C99FC  48 02 2D ED */	bl OSRestoreInterrupts
lbl_800CEB00:
/* 800CEB00 000C9A00  39 60 00 00 */	li r11, 0
/* 800CEB04 000C9A04  38 00 00 01 */	li r0, 1
/* 800CEB08 000C9A08  B0 01 04 12 */	sth r0, 0x412(r1)
/* 800CEB0C 000C9A0C  39 80 00 15 */	li r12, 0x15
/* 800CEB10 000C9A10  81 21 04 00 */	lwz r9, 0x400(r1)
/* 800CEB14 000C9A14  99 61 03 FC */	stb r11, 0x3fc(r1)
/* 800CEB18 000C9A18  81 01 04 04 */	lwz r8, 0x404(r1)
/* 800CEB1C 000C9A1C  81 41 03 FC */	lwz r10, 0x3fc(r1)
/* 800CEB20 000C9A20  80 E1 04 08 */	lwz r7, 0x408(r1)
/* 800CEB24 000C9A24  80 C1 04 0C */	lwz r6, 0x40c(r1)
/* 800CEB28 000C9A28  80 A1 04 10 */	lwz r5, 0x410(r1)
/* 800CEB2C 000C9A2C  80 81 04 14 */	lwz r4, 0x414(r1)
/* 800CEB30 000C9A30  80 61 04 18 */	lwz r3, 0x418(r1)
/* 800CEB34 000C9A34  80 01 04 1C */	lwz r0, 0x41c(r1)
/* 800CEB38 000C9A38  91 81 03 F8 */	stw r12, 0x3f8(r1)
/* 800CEB3C 000C9A3C  93 81 04 24 */	stw r28, 0x424(r1)
/* 800CEB40 000C9A40  91 61 04 20 */	stw r11, 0x420(r1)
/* 800CEB44 000C9A44  91 81 04 28 */	stw r12, 0x428(r1)
/* 800CEB48 000C9A48  91 41 04 2C */	stw r10, 0x42c(r1)
/* 800CEB4C 000C9A4C  91 21 04 30 */	stw r9, 0x430(r1)
/* 800CEB50 000C9A50  91 01 04 34 */	stw r8, 0x434(r1)
/* 800CEB54 000C9A54  90 E1 04 38 */	stw r7, 0x438(r1)
/* 800CEB58 000C9A58  90 C1 04 3C */	stw r6, 0x43c(r1)
/* 800CEB5C 000C9A5C  90 A1 04 40 */	stw r5, 0x440(r1)
/* 800CEB60 000C9A60  90 81 04 44 */	stw r4, 0x444(r1)
/* 800CEB64 000C9A64  90 61 04 48 */	stw r3, 0x448(r1)
/* 800CEB68 000C9A68  90 01 04 4C */	stw r0, 0x44c(r1)
/* 800CEB6C 000C9A6C  91 61 04 50 */	stw r11, 0x450(r1)
/* 800CEB70 000C9A70  93 81 04 54 */	stw r28, 0x454(r1)
/* 800CEB74 000C9A74  48 02 2D 4D */	bl OSDisableInterrupts
/* 800CEB78 000C9A78  7C 7E 1B 78 */	mr r30, r3
/* 800CEB7C 000C9A7C  48 02 2D 45 */	bl OSDisableInterrupts
/* 800CEB80 000C9A80  88 9F 01 60 */	lbz r4, 0x160(r31)
/* 800CEB84 000C9A84  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CEB88 000C9A88  7C 04 00 50 */	subf r0, r4, r0
/* 800CEB8C 000C9A8C  7C 1B 07 75 */	extsb. r27, r0
/* 800CEB90 000C9A90  40 80 00 10 */	bge lbl_800CEBA0
/* 800CEB94 000C9A94  80 1F 01 68 */	lwz r0, 0x168(r31)
/* 800CEB98 000C9A98  7C 1B 02 14 */	add r0, r27, r0
/* 800CEB9C 000C9A9C  7C 1B 07 74 */	extsb r27, r0
lbl_800CEBA0:
/* 800CEBA0 000C9AA0  48 02 2D 49 */	bl OSRestoreInterrupts
/* 800CEBA4 000C9AA4  80 7F 01 68 */	lwz r3, 0x168(r31)
/* 800CEBA8 000C9AA8  38 03 FF FF */	addi r0, r3, -1
/* 800CEBAC 000C9AAC  7C 00 D8 40 */	cmplw r0, r27
/* 800CEBB0 000C9AB0  40 82 00 10 */	bne lbl_800CEBC0
/* 800CEBB4 000C9AB4  7F C3 F3 78 */	mr r3, r30
/* 800CEBB8 000C9AB8  48 02 2D 31 */	bl OSRestoreInterrupts
/* 800CEBBC 000C9ABC  48 00 00 78 */	b lbl_800CEC34
lbl_800CEBC0:
/* 800CEBC0 000C9AC0  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CEBC4 000C9AC4  38 80 00 00 */	li r4, 0
/* 800CEBC8 000C9AC8  80 7F 01 64 */	lwz r3, 0x164(r31)
/* 800CEBCC 000C9ACC  38 A0 00 30 */	li r5, 0x30
/* 800CEBD0 000C9AD0  7C 00 07 74 */	extsb r0, r0
/* 800CEBD4 000C9AD4  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CEBD8 000C9AD8  7C 63 02 14 */	add r3, r3, r0
/* 800CEBDC 000C9ADC  4B F3 55 29 */	bl memset
/* 800CEBE0 000C9AE0  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CEBE4 000C9AE4  38 81 04 28 */	addi r4, r1, 0x428
/* 800CEBE8 000C9AE8  80 7F 01 64 */	lwz r3, 0x164(r31)
/* 800CEBEC 000C9AEC  38 A0 00 30 */	li r5, 0x30
/* 800CEBF0 000C9AF0  7C 00 07 74 */	extsb r0, r0
/* 800CEBF4 000C9AF4  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CEBF8 000C9AF8  7C 63 02 14 */	add r3, r3, r0
/* 800CEBFC 000C9AFC  4B F3 54 05 */	bl memcpy
/* 800CEC00 000C9B00  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CEC04 000C9B04  7F C3 F3 78 */	mr r3, r30
/* 800CEC08 000C9B08  80 9F 01 68 */	lwz r4, 0x168(r31)
/* 800CEC0C 000C9B0C  7C 06 07 74 */	extsb r6, r0
/* 800CEC10 000C9B10  38 84 FF FF */	addi r4, r4, -1
/* 800CEC14 000C9B14  7C A4 30 50 */	subf r5, r4, r6
/* 800CEC18 000C9B18  38 06 00 01 */	addi r0, r6, 1
/* 800CEC1C 000C9B1C  7C 86 20 50 */	subf r4, r6, r4
/* 800CEC20 000C9B20  7C A4 20 F8 */	nor r4, r5, r4
/* 800CEC24 000C9B24  7C 84 FE 70 */	srawi r4, r4, 0x1f
/* 800CEC28 000C9B28  7C 00 20 78 */	andc r0, r0, r4
/* 800CEC2C 000C9B2C  98 1F 01 61 */	stb r0, 0x161(r31)
/* 800CEC30 000C9B30  48 02 2C B9 */	bl OSRestoreInterrupts
lbl_800CEC34:
/* 800CEC34 000C9B34  7F A3 EB 78 */	mr r3, r29
/* 800CEC38 000C9B38  48 02 2C B1 */	bl OSRestoreInterrupts
/* 800CEC3C 000C9B3C  38 60 00 00 */	li r3, 0
/* 800CEC40 000C9B40  48 00 0E 68 */	b lbl_800CFAA8
lbl_800CEC44:
/* 800CEC44 000C9B44  7F A3 EB 78 */	mr r3, r29
/* 800CEC48 000C9B48  3B 40 FF FE */	li r26, -2
/* 800CEC4C 000C9B4C  48 02 2C 9D */	bl OSRestoreInterrupts
/* 800CEC50 000C9B50  48 00 0E 38 */	b lbl_800CFA88
lbl_800CEC54:
/* 800CEC54 000C9B54  2C 19 00 03 */	cmpwi r25, 3
/* 800CEC58 000C9B58  41 82 0B 40 */	beq lbl_800CF798
/* 800CEC5C 000C9B5C  40 80 00 14 */	bge lbl_800CEC70
/* 800CEC60 000C9B60  2C 19 00 01 */	cmpwi r25, 1
/* 800CEC64 000C9B64  41 82 00 1C */	beq lbl_800CEC80
/* 800CEC68 000C9B68  40 80 09 DC */	bge lbl_800CF644
/* 800CEC6C 000C9B6C  48 00 0E 1C */	b lbl_800CFA88
lbl_800CEC70:
/* 800CEC70 000C9B70  2C 19 00 05 */	cmpwi r25, 5
/* 800CEC74 000C9B74  41 82 00 0C */	beq lbl_800CEC80
/* 800CEC78 000C9B78  40 80 0E 10 */	bge lbl_800CFA88
/* 800CEC7C 000C9B7C  48 00 0C 70 */	b lbl_800CF8EC
lbl_800CEC80:
/* 800CEC80 000C9B80  48 02 2C 41 */	bl OSDisableInterrupts
/* 800CEC84 000C9B84  7C 7D 1B 78 */	mr r29, r3
/* 800CEC88 000C9B88  48 02 2C 39 */	bl OSDisableInterrupts
/* 800CEC8C 000C9B8C  88 9F 01 60 */	lbz r4, 0x160(r31)
/* 800CEC90 000C9B90  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CEC94 000C9B94  7C 04 00 50 */	subf r0, r4, r0
/* 800CEC98 000C9B98  7C 1E 07 75 */	extsb. r30, r0
/* 800CEC9C 000C9B9C  40 80 00 10 */	bge lbl_800CECAC
/* 800CECA0 000C9BA0  80 1F 01 68 */	lwz r0, 0x168(r31)
/* 800CECA4 000C9BA4  7C 1E 02 14 */	add r0, r30, r0
/* 800CECA8 000C9BA8  7C 1E 07 74 */	extsb r30, r0
lbl_800CECAC:
/* 800CECAC 000C9BAC  48 02 2C 3D */	bl OSRestoreInterrupts
/* 800CECB0 000C9BB0  80 7F 01 68 */	lwz r3, 0x168(r31)
/* 800CECB4 000C9BB4  38 9E 00 07 */	addi r4, r30, 7
/* 800CECB8 000C9BB8  38 03 FF FF */	addi r0, r3, -1
/* 800CECBC 000C9BBC  7C 04 00 40 */	cmplw r4, r0
/* 800CECC0 000C9BC0  41 81 09 74 */	bgt lbl_800CF634
/* 800CECC4 000C9BC4  38 60 00 01 */	li r3, 1
/* 800CECC8 000C9BC8  38 00 00 04 */	li r0, 4
/* 800CECCC 000C9BCC  B0 61 03 B2 */	sth r3, 0x3b2(r1)
/* 800CECD0 000C9BD0  3B 60 00 14 */	li r27, 0x14
/* 800CECD4 000C9BD4  39 80 00 00 */	li r12, 0
/* 800CECD8 000C9BD8  81 41 03 A0 */	lwz r10, 0x3a0(r1)
/* 800CECDC 000C9BDC  98 01 03 9C */	stb r0, 0x39c(r1)
/* 800CECE0 000C9BE0  81 21 03 A4 */	lwz r9, 0x3a4(r1)
/* 800CECE4 000C9BE4  81 61 03 9C */	lwz r11, 0x39c(r1)
/* 800CECE8 000C9BE8  81 01 03 A8 */	lwz r8, 0x3a8(r1)
/* 800CECEC 000C9BEC  80 E1 03 AC */	lwz r7, 0x3ac(r1)
/* 800CECF0 000C9BF0  80 C1 03 B0 */	lwz r6, 0x3b0(r1)
/* 800CECF4 000C9BF4  80 A1 03 B4 */	lwz r5, 0x3b4(r1)
/* 800CECF8 000C9BF8  80 81 03 B8 */	lwz r4, 0x3b8(r1)
/* 800CECFC 000C9BFC  80 61 03 BC */	lwz r3, 0x3bc(r1)
/* 800CED00 000C9C00  80 01 03 C0 */	lwz r0, 0x3c0(r1)
/* 800CED04 000C9C04  93 61 03 98 */	stw r27, 0x398(r1)
/* 800CED08 000C9C08  91 81 03 C4 */	stw r12, 0x3c4(r1)
/* 800CED0C 000C9C0C  93 61 03 C8 */	stw r27, 0x3c8(r1)
/* 800CED10 000C9C10  91 61 03 CC */	stw r11, 0x3cc(r1)
/* 800CED14 000C9C14  91 41 03 D0 */	stw r10, 0x3d0(r1)
/* 800CED18 000C9C18  91 21 03 D4 */	stw r9, 0x3d4(r1)
/* 800CED1C 000C9C1C  91 01 03 D8 */	stw r8, 0x3d8(r1)
/* 800CED20 000C9C20  90 E1 03 DC */	stw r7, 0x3dc(r1)
/* 800CED24 000C9C24  90 C1 03 E0 */	stw r6, 0x3e0(r1)
/* 800CED28 000C9C28  90 A1 03 E4 */	stw r5, 0x3e4(r1)
/* 800CED2C 000C9C2C  90 81 03 E8 */	stw r4, 0x3e8(r1)
/* 800CED30 000C9C30  90 61 03 EC */	stw r3, 0x3ec(r1)
/* 800CED34 000C9C34  90 01 03 F0 */	stw r0, 0x3f0(r1)
/* 800CED38 000C9C38  91 81 03 F4 */	stw r12, 0x3f4(r1)
/* 800CED3C 000C9C3C  48 02 2B 85 */	bl OSDisableInterrupts
/* 800CED40 000C9C40  7C 7E 1B 78 */	mr r30, r3
/* 800CED44 000C9C44  48 02 2B 7D */	bl OSDisableInterrupts
/* 800CED48 000C9C48  88 9F 01 60 */	lbz r4, 0x160(r31)
/* 800CED4C 000C9C4C  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CED50 000C9C50  7C 04 00 50 */	subf r0, r4, r0
/* 800CED54 000C9C54  7C 1B 07 75 */	extsb. r27, r0
/* 800CED58 000C9C58  40 80 00 10 */	bge lbl_800CED68
/* 800CED5C 000C9C5C  80 1F 01 68 */	lwz r0, 0x168(r31)
/* 800CED60 000C9C60  7C 1B 02 14 */	add r0, r27, r0
/* 800CED64 000C9C64  7C 1B 07 74 */	extsb r27, r0
lbl_800CED68:
/* 800CED68 000C9C68  48 02 2B 81 */	bl OSRestoreInterrupts
/* 800CED6C 000C9C6C  80 7F 01 68 */	lwz r3, 0x168(r31)
/* 800CED70 000C9C70  38 03 FF FF */	addi r0, r3, -1
/* 800CED74 000C9C74  7C 00 D8 40 */	cmplw r0, r27
/* 800CED78 000C9C78  40 82 00 10 */	bne lbl_800CED88
/* 800CED7C 000C9C7C  7F C3 F3 78 */	mr r3, r30
/* 800CED80 000C9C80  48 02 2B 69 */	bl OSRestoreInterrupts
/* 800CED84 000C9C84  48 00 00 78 */	b lbl_800CEDFC
lbl_800CED88:
/* 800CED88 000C9C88  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CED8C 000C9C8C  38 80 00 00 */	li r4, 0
/* 800CED90 000C9C90  80 7F 01 64 */	lwz r3, 0x164(r31)
/* 800CED94 000C9C94  38 A0 00 30 */	li r5, 0x30
/* 800CED98 000C9C98  7C 00 07 74 */	extsb r0, r0
/* 800CED9C 000C9C9C  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CEDA0 000C9CA0  7C 63 02 14 */	add r3, r3, r0
/* 800CEDA4 000C9CA4  4B F3 53 61 */	bl memset
/* 800CEDA8 000C9CA8  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CEDAC 000C9CAC  38 81 03 C8 */	addi r4, r1, 0x3c8
/* 800CEDB0 000C9CB0  80 7F 01 64 */	lwz r3, 0x164(r31)
/* 800CEDB4 000C9CB4  38 A0 00 30 */	li r5, 0x30
/* 800CEDB8 000C9CB8  7C 00 07 74 */	extsb r0, r0
/* 800CEDBC 000C9CBC  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CEDC0 000C9CC0  7C 63 02 14 */	add r3, r3, r0
/* 800CEDC4 000C9CC4  4B F3 52 3D */	bl memcpy
/* 800CEDC8 000C9CC8  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CEDCC 000C9CCC  7F C3 F3 78 */	mr r3, r30
/* 800CEDD0 000C9CD0  80 9F 01 68 */	lwz r4, 0x168(r31)
/* 800CEDD4 000C9CD4  7C 06 07 74 */	extsb r6, r0
/* 800CEDD8 000C9CD8  38 84 FF FF */	addi r4, r4, -1
/* 800CEDDC 000C9CDC  7C A4 30 50 */	subf r5, r4, r6
/* 800CEDE0 000C9CE0  38 06 00 01 */	addi r0, r6, 1
/* 800CEDE4 000C9CE4  7C 86 20 50 */	subf r4, r6, r4
/* 800CEDE8 000C9CE8  7C A4 20 F8 */	nor r4, r5, r4
/* 800CEDEC 000C9CEC  7C 84 FE 70 */	srawi r4, r4, 0x1f
/* 800CEDF0 000C9CF0  7C 00 20 78 */	andc r0, r0, r4
/* 800CEDF4 000C9CF4  98 1F 01 61 */	stb r0, 0x161(r31)
/* 800CEDF8 000C9CF8  48 02 2A F1 */	bl OSRestoreInterrupts
lbl_800CEDFC:
/* 800CEDFC 000C9CFC  38 60 00 01 */	li r3, 1
/* 800CEE00 000C9D00  38 00 00 04 */	li r0, 4
/* 800CEE04 000C9D04  B0 61 03 52 */	sth r3, 0x352(r1)
/* 800CEE08 000C9D08  3B 60 00 19 */	li r27, 0x19
/* 800CEE0C 000C9D0C  39 80 00 00 */	li r12, 0
/* 800CEE10 000C9D10  81 41 03 40 */	lwz r10, 0x340(r1)
/* 800CEE14 000C9D14  98 01 03 3C */	stb r0, 0x33c(r1)
/* 800CEE18 000C9D18  81 21 03 44 */	lwz r9, 0x344(r1)
/* 800CEE1C 000C9D1C  81 61 03 3C */	lwz r11, 0x33c(r1)
/* 800CEE20 000C9D20  81 01 03 48 */	lwz r8, 0x348(r1)
/* 800CEE24 000C9D24  80 E1 03 4C */	lwz r7, 0x34c(r1)
/* 800CEE28 000C9D28  80 C1 03 50 */	lwz r6, 0x350(r1)
/* 800CEE2C 000C9D2C  80 A1 03 54 */	lwz r5, 0x354(r1)
/* 800CEE30 000C9D30  80 81 03 58 */	lwz r4, 0x358(r1)
/* 800CEE34 000C9D34  80 61 03 5C */	lwz r3, 0x35c(r1)
/* 800CEE38 000C9D38  80 01 03 60 */	lwz r0, 0x360(r1)
/* 800CEE3C 000C9D3C  93 61 03 38 */	stw r27, 0x338(r1)
/* 800CEE40 000C9D40  91 81 03 64 */	stw r12, 0x364(r1)
/* 800CEE44 000C9D44  93 61 03 68 */	stw r27, 0x368(r1)
/* 800CEE48 000C9D48  91 61 03 6C */	stw r11, 0x36c(r1)
/* 800CEE4C 000C9D4C  91 41 03 70 */	stw r10, 0x370(r1)
/* 800CEE50 000C9D50  91 21 03 74 */	stw r9, 0x374(r1)
/* 800CEE54 000C9D54  91 01 03 78 */	stw r8, 0x378(r1)
/* 800CEE58 000C9D58  90 E1 03 7C */	stw r7, 0x37c(r1)
/* 800CEE5C 000C9D5C  90 C1 03 80 */	stw r6, 0x380(r1)
/* 800CEE60 000C9D60  90 A1 03 84 */	stw r5, 0x384(r1)
/* 800CEE64 000C9D64  90 81 03 88 */	stw r4, 0x388(r1)
/* 800CEE68 000C9D68  90 61 03 8C */	stw r3, 0x38c(r1)
/* 800CEE6C 000C9D6C  90 01 03 90 */	stw r0, 0x390(r1)
/* 800CEE70 000C9D70  91 81 03 94 */	stw r12, 0x394(r1)
/* 800CEE74 000C9D74  48 02 2A 4D */	bl OSDisableInterrupts
/* 800CEE78 000C9D78  7C 7E 1B 78 */	mr r30, r3
/* 800CEE7C 000C9D7C  48 02 2A 45 */	bl OSDisableInterrupts
/* 800CEE80 000C9D80  88 9F 01 60 */	lbz r4, 0x160(r31)
/* 800CEE84 000C9D84  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CEE88 000C9D88  7C 04 00 50 */	subf r0, r4, r0
/* 800CEE8C 000C9D8C  7C 1B 07 75 */	extsb. r27, r0
/* 800CEE90 000C9D90  40 80 00 10 */	bge lbl_800CEEA0
/* 800CEE94 000C9D94  80 1F 01 68 */	lwz r0, 0x168(r31)
/* 800CEE98 000C9D98  7C 1B 02 14 */	add r0, r27, r0
/* 800CEE9C 000C9D9C  7C 1B 07 74 */	extsb r27, r0
lbl_800CEEA0:
/* 800CEEA0 000C9DA0  48 02 2A 49 */	bl OSRestoreInterrupts
/* 800CEEA4 000C9DA4  80 7F 01 68 */	lwz r3, 0x168(r31)
/* 800CEEA8 000C9DA8  38 03 FF FF */	addi r0, r3, -1
/* 800CEEAC 000C9DAC  7C 00 D8 40 */	cmplw r0, r27
/* 800CEEB0 000C9DB0  40 82 00 10 */	bne lbl_800CEEC0
/* 800CEEB4 000C9DB4  7F C3 F3 78 */	mr r3, r30
/* 800CEEB8 000C9DB8  48 02 2A 31 */	bl OSRestoreInterrupts
/* 800CEEBC 000C9DBC  48 00 00 78 */	b lbl_800CEF34
lbl_800CEEC0:
/* 800CEEC0 000C9DC0  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CEEC4 000C9DC4  38 80 00 00 */	li r4, 0
/* 800CEEC8 000C9DC8  80 7F 01 64 */	lwz r3, 0x164(r31)
/* 800CEECC 000C9DCC  38 A0 00 30 */	li r5, 0x30
/* 800CEED0 000C9DD0  7C 00 07 74 */	extsb r0, r0
/* 800CEED4 000C9DD4  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CEED8 000C9DD8  7C 63 02 14 */	add r3, r3, r0
/* 800CEEDC 000C9DDC  4B F3 52 29 */	bl memset
/* 800CEEE0 000C9DE0  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CEEE4 000C9DE4  38 81 03 68 */	addi r4, r1, 0x368
/* 800CEEE8 000C9DE8  80 7F 01 64 */	lwz r3, 0x164(r31)
/* 800CEEEC 000C9DEC  38 A0 00 30 */	li r5, 0x30
/* 800CEEF0 000C9DF0  7C 00 07 74 */	extsb r0, r0
/* 800CEEF4 000C9DF4  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CEEF8 000C9DF8  7C 63 02 14 */	add r3, r3, r0
/* 800CEEFC 000C9DFC  4B F3 51 05 */	bl memcpy
/* 800CEF00 000C9E00  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CEF04 000C9E04  7F C3 F3 78 */	mr r3, r30
/* 800CEF08 000C9E08  80 9F 01 68 */	lwz r4, 0x168(r31)
/* 800CEF0C 000C9E0C  7C 06 07 74 */	extsb r6, r0
/* 800CEF10 000C9E10  38 84 FF FF */	addi r4, r4, -1
/* 800CEF14 000C9E14  7C A4 30 50 */	subf r5, r4, r6
/* 800CEF18 000C9E18  38 06 00 01 */	addi r0, r6, 1
/* 800CEF1C 000C9E1C  7C 86 20 50 */	subf r4, r6, r4
/* 800CEF20 000C9E20  7C A4 20 F8 */	nor r4, r5, r4
/* 800CEF24 000C9E24  7C 84 FE 70 */	srawi r4, r4, 0x1f
/* 800CEF28 000C9E28  7C 00 20 78 */	andc r0, r0, r4
/* 800CEF2C 000C9E2C  98 1F 01 61 */	stb r0, 0x161(r31)
/* 800CEF30 000C9E30  48 02 29 B9 */	bl OSRestoreInterrupts
lbl_800CEF34:
/* 800CEF34 000C9E34  3C 60 04 A2 */	lis r3, 0x04A20009@ha
/* 800CEF38 000C9E38  39 20 00 01 */	li r9, 1
/* 800CEF3C 000C9E3C  39 03 00 09 */	addi r8, r3, 0x04A20009@l
/* 800CEF40 000C9E40  38 E0 00 16 */	li r7, 0x16
/* 800CEF44 000C9E44  38 C0 00 15 */	li r6, 0x15
/* 800CEF48 000C9E48  38 00 00 00 */	li r0, 0
/* 800CEF4C 000C9E4C  99 21 00 0E */	stb r9, 0xe(r1)
/* 800CEF50 000C9E50  38 61 03 0C */	addi r3, r1, 0x30c
/* 800CEF54 000C9E54  38 81 00 20 */	addi r4, r1, 0x20
/* 800CEF58 000C9E58  38 A0 00 04 */	li r5, 4
/* 800CEF5C 000C9E5C  91 01 00 20 */	stw r8, 0x20(r1)
/* 800CEF60 000C9E60  99 21 00 0D */	stb r9, 0xd(r1)
/* 800CEF64 000C9E64  90 E1 03 08 */	stw r7, 0x308(r1)
/* 800CEF68 000C9E68  B0 C1 03 22 */	sth r6, 0x322(r1)
/* 800CEF6C 000C9E6C  90 01 03 34 */	stw r0, 0x334(r1)
/* 800CEF70 000C9E70  4B F3 50 91 */	bl memcpy
/* 800CEF74 000C9E74  38 61 03 10 */	addi r3, r1, 0x310
/* 800CEF78 000C9E78  38 81 00 0D */	addi r4, r1, 0xd
/* 800CEF7C 000C9E7C  38 A0 00 01 */	li r5, 1
/* 800CEF80 000C9E80  4B F3 50 81 */	bl memcpy
/* 800CEF84 000C9E84  38 61 03 11 */	addi r3, r1, 0x311
/* 800CEF88 000C9E88  38 81 00 0E */	addi r4, r1, 0xe
/* 800CEF8C 000C9E8C  38 A0 00 01 */	li r5, 1
/* 800CEF90 000C9E90  4B F3 50 71 */	bl memcpy
/* 800CEF94 000C9E94  83 61 03 08 */	lwz r27, 0x308(r1)
/* 800CEF98 000C9E98  81 81 03 0C */	lwz r12, 0x30c(r1)
/* 800CEF9C 000C9E9C  81 61 03 10 */	lwz r11, 0x310(r1)
/* 800CEFA0 000C9EA0  81 41 03 14 */	lwz r10, 0x314(r1)
/* 800CEFA4 000C9EA4  81 21 03 18 */	lwz r9, 0x318(r1)
/* 800CEFA8 000C9EA8  81 01 03 1C */	lwz r8, 0x31c(r1)
/* 800CEFAC 000C9EAC  80 E1 03 20 */	lwz r7, 0x320(r1)
/* 800CEFB0 000C9EB0  80 C1 03 24 */	lwz r6, 0x324(r1)
/* 800CEFB4 000C9EB4  80 A1 03 28 */	lwz r5, 0x328(r1)
/* 800CEFB8 000C9EB8  80 81 03 2C */	lwz r4, 0x32c(r1)
/* 800CEFBC 000C9EBC  80 61 03 30 */	lwz r3, 0x330(r1)
/* 800CEFC0 000C9EC0  80 01 03 34 */	lwz r0, 0x334(r1)
/* 800CEFC4 000C9EC4  93 61 02 D8 */	stw r27, 0x2d8(r1)
/* 800CEFC8 000C9EC8  91 81 02 DC */	stw r12, 0x2dc(r1)
/* 800CEFCC 000C9ECC  91 61 02 E0 */	stw r11, 0x2e0(r1)
/* 800CEFD0 000C9ED0  91 41 02 E4 */	stw r10, 0x2e4(r1)
/* 800CEFD4 000C9ED4  91 21 02 E8 */	stw r9, 0x2e8(r1)
/* 800CEFD8 000C9ED8  91 01 02 EC */	stw r8, 0x2ec(r1)
/* 800CEFDC 000C9EDC  90 E1 02 F0 */	stw r7, 0x2f0(r1)
/* 800CEFE0 000C9EE0  90 C1 02 F4 */	stw r6, 0x2f4(r1)
/* 800CEFE4 000C9EE4  90 A1 02 F8 */	stw r5, 0x2f8(r1)
/* 800CEFE8 000C9EE8  90 81 02 FC */	stw r4, 0x2fc(r1)
/* 800CEFEC 000C9EEC  90 61 03 00 */	stw r3, 0x300(r1)
/* 800CEFF0 000C9EF0  90 01 03 04 */	stw r0, 0x304(r1)
/* 800CEFF4 000C9EF4  48 02 28 CD */	bl OSDisableInterrupts
/* 800CEFF8 000C9EF8  7C 7E 1B 78 */	mr r30, r3
/* 800CEFFC 000C9EFC  48 02 28 C5 */	bl OSDisableInterrupts
/* 800CF000 000C9F00  88 9F 01 60 */	lbz r4, 0x160(r31)
/* 800CF004 000C9F04  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CF008 000C9F08  7C 04 00 50 */	subf r0, r4, r0
/* 800CF00C 000C9F0C  7C 1B 07 75 */	extsb. r27, r0
/* 800CF010 000C9F10  40 80 00 10 */	bge lbl_800CF020
/* 800CF014 000C9F14  80 1F 01 68 */	lwz r0, 0x168(r31)
/* 800CF018 000C9F18  7C 1B 02 14 */	add r0, r27, r0
/* 800CF01C 000C9F1C  7C 1B 07 74 */	extsb r27, r0
lbl_800CF020:
/* 800CF020 000C9F20  48 02 28 C9 */	bl OSRestoreInterrupts
/* 800CF024 000C9F24  80 7F 01 68 */	lwz r3, 0x168(r31)
/* 800CF028 000C9F28  38 03 FF FF */	addi r0, r3, -1
/* 800CF02C 000C9F2C  7C 00 D8 40 */	cmplw r0, r27
/* 800CF030 000C9F30  40 82 00 10 */	bne lbl_800CF040
/* 800CF034 000C9F34  7F C3 F3 78 */	mr r3, r30
/* 800CF038 000C9F38  48 02 28 B1 */	bl OSRestoreInterrupts
/* 800CF03C 000C9F3C  48 00 00 78 */	b lbl_800CF0B4
lbl_800CF040:
/* 800CF040 000C9F40  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CF044 000C9F44  38 80 00 00 */	li r4, 0
/* 800CF048 000C9F48  80 7F 01 64 */	lwz r3, 0x164(r31)
/* 800CF04C 000C9F4C  38 A0 00 30 */	li r5, 0x30
/* 800CF050 000C9F50  7C 00 07 74 */	extsb r0, r0
/* 800CF054 000C9F54  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CF058 000C9F58  7C 63 02 14 */	add r3, r3, r0
/* 800CF05C 000C9F5C  4B F3 50 A9 */	bl memset
/* 800CF060 000C9F60  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CF064 000C9F64  38 81 02 D8 */	addi r4, r1, 0x2d8
/* 800CF068 000C9F68  80 7F 01 64 */	lwz r3, 0x164(r31)
/* 800CF06C 000C9F6C  38 A0 00 30 */	li r5, 0x30
/* 800CF070 000C9F70  7C 00 07 74 */	extsb r0, r0
/* 800CF074 000C9F74  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CF078 000C9F78  7C 63 02 14 */	add r3, r3, r0
/* 800CF07C 000C9F7C  4B F3 4F 85 */	bl memcpy
/* 800CF080 000C9F80  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CF084 000C9F84  7F C3 F3 78 */	mr r3, r30
/* 800CF088 000C9F88  80 9F 01 68 */	lwz r4, 0x168(r31)
/* 800CF08C 000C9F8C  7C 06 07 74 */	extsb r6, r0
/* 800CF090 000C9F90  38 84 FF FF */	addi r4, r4, -1
/* 800CF094 000C9F94  7C A4 30 50 */	subf r5, r4, r6
/* 800CF098 000C9F98  38 06 00 01 */	addi r0, r6, 1
/* 800CF09C 000C9F9C  7C 86 20 50 */	subf r4, r6, r4
/* 800CF0A0 000C9FA0  7C A4 20 F8 */	nor r4, r5, r4
/* 800CF0A4 000C9FA4  7C 84 FE 70 */	srawi r4, r4, 0x1f
/* 800CF0A8 000C9FA8  7C 00 20 78 */	andc r0, r0, r4
/* 800CF0AC 000C9FAC  98 1F 01 61 */	stb r0, 0x161(r31)
/* 800CF0B0 000C9FB0  48 02 28 39 */	bl OSRestoreInterrupts
lbl_800CF0B4:
/* 800CF0B4 000C9FB4  3C 60 04 A2 */	lis r3, 0x04A20001@ha
/* 800CF0B8 000C9FB8  38 80 00 80 */	li r4, 0x80
/* 800CF0BC 000C9FBC  38 A3 00 01 */	addi r5, r3, 0x04A20001@l
/* 800CF0C0 000C9FC0  39 00 00 01 */	li r8, 1
/* 800CF0C4 000C9FC4  38 E0 00 16 */	li r7, 0x16
/* 800CF0C8 000C9FC8  38 C0 00 15 */	li r6, 0x15
/* 800CF0CC 000C9FCC  38 00 00 00 */	li r0, 0
/* 800CF0D0 000C9FD0  98 81 00 0C */	stb r4, 0xc(r1)
/* 800CF0D4 000C9FD4  38 61 02 AC */	addi r3, r1, 0x2ac
/* 800CF0D8 000C9FD8  38 81 00 1C */	addi r4, r1, 0x1c
/* 800CF0DC 000C9FDC  90 A1 00 1C */	stw r5, 0x1c(r1)
/* 800CF0E0 000C9FE0  38 A0 00 04 */	li r5, 4
/* 800CF0E4 000C9FE4  99 01 00 0B */	stb r8, 0xb(r1)
/* 800CF0E8 000C9FE8  90 E1 02 A8 */	stw r7, 0x2a8(r1)
/* 800CF0EC 000C9FEC  B0 C1 02 C2 */	sth r6, 0x2c2(r1)
/* 800CF0F0 000C9FF0  90 01 02 D4 */	stw r0, 0x2d4(r1)
/* 800CF0F4 000C9FF4  4B F3 4F 0D */	bl memcpy
/* 800CF0F8 000C9FF8  38 61 02 B0 */	addi r3, r1, 0x2b0
/* 800CF0FC 000C9FFC  38 81 00 0B */	addi r4, r1, 0xb
/* 800CF100 000CA000  38 A0 00 01 */	li r5, 1
/* 800CF104 000CA004  4B F3 4E FD */	bl memcpy
/* 800CF108 000CA008  38 61 02 B1 */	addi r3, r1, 0x2b1
/* 800CF10C 000CA00C  38 81 00 0C */	addi r4, r1, 0xc
/* 800CF110 000CA010  38 A0 00 01 */	li r5, 1
/* 800CF114 000CA014  4B F3 4E ED */	bl memcpy
/* 800CF118 000CA018  83 61 02 A8 */	lwz r27, 0x2a8(r1)
/* 800CF11C 000CA01C  81 81 02 AC */	lwz r12, 0x2ac(r1)
/* 800CF120 000CA020  81 61 02 B0 */	lwz r11, 0x2b0(r1)
/* 800CF124 000CA024  81 41 02 B4 */	lwz r10, 0x2b4(r1)
/* 800CF128 000CA028  81 21 02 B8 */	lwz r9, 0x2b8(r1)
/* 800CF12C 000CA02C  81 01 02 BC */	lwz r8, 0x2bc(r1)
/* 800CF130 000CA030  80 E1 02 C0 */	lwz r7, 0x2c0(r1)
/* 800CF134 000CA034  80 C1 02 C4 */	lwz r6, 0x2c4(r1)
/* 800CF138 000CA038  80 A1 02 C8 */	lwz r5, 0x2c8(r1)
/* 800CF13C 000CA03C  80 81 02 CC */	lwz r4, 0x2cc(r1)
/* 800CF140 000CA040  80 61 02 D0 */	lwz r3, 0x2d0(r1)
/* 800CF144 000CA044  80 01 02 D4 */	lwz r0, 0x2d4(r1)
/* 800CF148 000CA048  93 61 02 78 */	stw r27, 0x278(r1)
/* 800CF14C 000CA04C  91 81 02 7C */	stw r12, 0x27c(r1)
/* 800CF150 000CA050  91 61 02 80 */	stw r11, 0x280(r1)
/* 800CF154 000CA054  91 41 02 84 */	stw r10, 0x284(r1)
/* 800CF158 000CA058  91 21 02 88 */	stw r9, 0x288(r1)
/* 800CF15C 000CA05C  91 01 02 8C */	stw r8, 0x28c(r1)
/* 800CF160 000CA060  90 E1 02 90 */	stw r7, 0x290(r1)
/* 800CF164 000CA064  90 C1 02 94 */	stw r6, 0x294(r1)
/* 800CF168 000CA068  90 A1 02 98 */	stw r5, 0x298(r1)
/* 800CF16C 000CA06C  90 81 02 9C */	stw r4, 0x29c(r1)
/* 800CF170 000CA070  90 61 02 A0 */	stw r3, 0x2a0(r1)
/* 800CF174 000CA074  90 01 02 A4 */	stw r0, 0x2a4(r1)
/* 800CF178 000CA078  48 02 27 49 */	bl OSDisableInterrupts
/* 800CF17C 000CA07C  7C 7E 1B 78 */	mr r30, r3
/* 800CF180 000CA080  48 02 27 41 */	bl OSDisableInterrupts
/* 800CF184 000CA084  88 9F 01 60 */	lbz r4, 0x160(r31)
/* 800CF188 000CA088  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CF18C 000CA08C  7C 04 00 50 */	subf r0, r4, r0
/* 800CF190 000CA090  7C 1B 07 75 */	extsb. r27, r0
/* 800CF194 000CA094  40 80 00 10 */	bge lbl_800CF1A4
/* 800CF198 000CA098  80 1F 01 68 */	lwz r0, 0x168(r31)
/* 800CF19C 000CA09C  7C 1B 02 14 */	add r0, r27, r0
/* 800CF1A0 000CA0A0  7C 1B 07 74 */	extsb r27, r0
lbl_800CF1A4:
/* 800CF1A4 000CA0A4  48 02 27 45 */	bl OSRestoreInterrupts
/* 800CF1A8 000CA0A8  80 7F 01 68 */	lwz r3, 0x168(r31)
/* 800CF1AC 000CA0AC  38 03 FF FF */	addi r0, r3, -1
/* 800CF1B0 000CA0B0  7C 00 D8 40 */	cmplw r0, r27
/* 800CF1B4 000CA0B4  40 82 00 10 */	bne lbl_800CF1C4
/* 800CF1B8 000CA0B8  7F C3 F3 78 */	mr r3, r30
/* 800CF1BC 000CA0BC  48 02 27 2D */	bl OSRestoreInterrupts
/* 800CF1C0 000CA0C0  48 00 00 78 */	b lbl_800CF238
lbl_800CF1C4:
/* 800CF1C4 000CA0C4  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CF1C8 000CA0C8  38 80 00 00 */	li r4, 0
/* 800CF1CC 000CA0CC  80 7F 01 64 */	lwz r3, 0x164(r31)
/* 800CF1D0 000CA0D0  38 A0 00 30 */	li r5, 0x30
/* 800CF1D4 000CA0D4  7C 00 07 74 */	extsb r0, r0
/* 800CF1D8 000CA0D8  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CF1DC 000CA0DC  7C 63 02 14 */	add r3, r3, r0
/* 800CF1E0 000CA0E0  4B F3 4F 25 */	bl memset
/* 800CF1E4 000CA0E4  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CF1E8 000CA0E8  38 81 02 78 */	addi r4, r1, 0x278
/* 800CF1EC 000CA0EC  80 7F 01 64 */	lwz r3, 0x164(r31)
/* 800CF1F0 000CA0F0  38 A0 00 30 */	li r5, 0x30
/* 800CF1F4 000CA0F4  7C 00 07 74 */	extsb r0, r0
/* 800CF1F8 000CA0F8  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CF1FC 000CA0FC  7C 63 02 14 */	add r3, r3, r0
/* 800CF200 000CA100  4B F3 4E 01 */	bl memcpy
/* 800CF204 000CA104  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CF208 000CA108  7F C3 F3 78 */	mr r3, r30
/* 800CF20C 000CA10C  80 9F 01 68 */	lwz r4, 0x168(r31)
/* 800CF210 000CA110  7C 06 07 74 */	extsb r6, r0
/* 800CF214 000CA114  38 84 FF FF */	addi r4, r4, -1
/* 800CF218 000CA118  7C A4 30 50 */	subf r5, r4, r6
/* 800CF21C 000CA11C  38 06 00 01 */	addi r0, r6, 1
/* 800CF220 000CA120  7C 86 20 50 */	subf r4, r6, r4
/* 800CF224 000CA124  7C A4 20 F8 */	nor r4, r5, r4
/* 800CF228 000CA128  7C 84 FE 70 */	srawi r4, r4, 0x1f
/* 800CF22C 000CA12C  7C 00 20 78 */	andc r0, r0, r4
/* 800CF230 000CA130  98 1F 01 61 */	stb r0, 0x161(r31)
/* 800CF234 000CA134  48 02 26 B5 */	bl OSRestoreInterrupts
lbl_800CF238:
/* 800CF238 000CA138  88 8D 9A 72 */	lbz r4, _speakerVolume-_SDA_BASE_(r13)
/* 800CF23C 000CA13C  3C 60 04 A2 */	lis r3, 0x04A20001@ha
/* 800CF240 000CA140  38 A3 00 01 */	addi r5, r3, 0x04A20001@l
/* 800CF244 000CA144  39 00 00 07 */	li r8, 7
/* 800CF248 000CA148  38 E0 00 16 */	li r7, 0x16
/* 800CF24C 000CA14C  38 C0 00 15 */	li r6, 0x15
/* 800CF250 000CA150  38 00 00 00 */	li r0, 0
/* 800CF254 000CA154  98 81 00 30 */	stb r4, 0x30(r1)
/* 800CF258 000CA158  38 61 02 1C */	addi r3, r1, 0x21c
/* 800CF25C 000CA15C  38 81 00 18 */	addi r4, r1, 0x18
/* 800CF260 000CA160  90 A1 00 18 */	stw r5, 0x18(r1)
/* 800CF264 000CA164  38 A0 00 04 */	li r5, 4
/* 800CF268 000CA168  99 01 00 0A */	stb r8, 0xa(r1)
/* 800CF26C 000CA16C  90 E1 02 18 */	stw r7, 0x218(r1)
/* 800CF270 000CA170  B0 C1 02 32 */	sth r6, 0x232(r1)
/* 800CF274 000CA174  90 01 02 44 */	stw r0, 0x244(r1)
/* 800CF278 000CA178  4B F3 4D 89 */	bl memcpy
/* 800CF27C 000CA17C  38 61 02 20 */	addi r3, r1, 0x220
/* 800CF280 000CA180  38 81 00 0A */	addi r4, r1, 0xa
/* 800CF284 000CA184  38 A0 00 01 */	li r5, 1
/* 800CF288 000CA188  4B F3 4D 79 */	bl memcpy
/* 800CF28C 000CA18C  38 61 02 21 */	addi r3, r1, 0x221
/* 800CF290 000CA190  38 81 00 2C */	addi r4, r1, 0x2c
/* 800CF294 000CA194  38 A0 00 07 */	li r5, 7
/* 800CF298 000CA198  4B F3 4D 69 */	bl memcpy
/* 800CF29C 000CA19C  83 61 02 18 */	lwz r27, 0x218(r1)
/* 800CF2A0 000CA1A0  81 81 02 1C */	lwz r12, 0x21c(r1)
/* 800CF2A4 000CA1A4  81 61 02 20 */	lwz r11, 0x220(r1)
/* 800CF2A8 000CA1A8  81 41 02 24 */	lwz r10, 0x224(r1)
/* 800CF2AC 000CA1AC  81 21 02 28 */	lwz r9, 0x228(r1)
/* 800CF2B0 000CA1B0  81 01 02 2C */	lwz r8, 0x22c(r1)
/* 800CF2B4 000CA1B4  80 E1 02 30 */	lwz r7, 0x230(r1)
/* 800CF2B8 000CA1B8  80 C1 02 34 */	lwz r6, 0x234(r1)
/* 800CF2BC 000CA1BC  80 A1 02 38 */	lwz r5, 0x238(r1)
/* 800CF2C0 000CA1C0  80 81 02 3C */	lwz r4, 0x23c(r1)
/* 800CF2C4 000CA1C4  80 61 02 40 */	lwz r3, 0x240(r1)
/* 800CF2C8 000CA1C8  80 01 02 44 */	lwz r0, 0x244(r1)
/* 800CF2CC 000CA1CC  93 61 02 48 */	stw r27, 0x248(r1)
/* 800CF2D0 000CA1D0  91 81 02 4C */	stw r12, 0x24c(r1)
/* 800CF2D4 000CA1D4  91 61 02 50 */	stw r11, 0x250(r1)
/* 800CF2D8 000CA1D8  91 41 02 54 */	stw r10, 0x254(r1)
/* 800CF2DC 000CA1DC  91 21 02 58 */	stw r9, 0x258(r1)
/* 800CF2E0 000CA1E0  91 01 02 5C */	stw r8, 0x25c(r1)
/* 800CF2E4 000CA1E4  90 E1 02 60 */	stw r7, 0x260(r1)
/* 800CF2E8 000CA1E8  90 C1 02 64 */	stw r6, 0x264(r1)
/* 800CF2EC 000CA1EC  90 A1 02 68 */	stw r5, 0x268(r1)
/* 800CF2F0 000CA1F0  90 81 02 6C */	stw r4, 0x26c(r1)
/* 800CF2F4 000CA1F4  90 61 02 70 */	stw r3, 0x270(r1)
/* 800CF2F8 000CA1F8  90 01 02 74 */	stw r0, 0x274(r1)
/* 800CF2FC 000CA1FC  48 02 25 C5 */	bl OSDisableInterrupts
/* 800CF300 000CA200  7C 7E 1B 78 */	mr r30, r3
/* 800CF304 000CA204  48 02 25 BD */	bl OSDisableInterrupts
/* 800CF308 000CA208  88 9F 01 60 */	lbz r4, 0x160(r31)
/* 800CF30C 000CA20C  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CF310 000CA210  7C 04 00 50 */	subf r0, r4, r0
/* 800CF314 000CA214  7C 1B 07 75 */	extsb. r27, r0
/* 800CF318 000CA218  40 80 00 10 */	bge lbl_800CF328
/* 800CF31C 000CA21C  80 1F 01 68 */	lwz r0, 0x168(r31)
/* 800CF320 000CA220  7C 1B 02 14 */	add r0, r27, r0
/* 800CF324 000CA224  7C 1B 07 74 */	extsb r27, r0
lbl_800CF328:
/* 800CF328 000CA228  48 02 25 C1 */	bl OSRestoreInterrupts
/* 800CF32C 000CA22C  80 7F 01 68 */	lwz r3, 0x168(r31)
/* 800CF330 000CA230  38 03 FF FF */	addi r0, r3, -1
/* 800CF334 000CA234  7C 00 D8 40 */	cmplw r0, r27
/* 800CF338 000CA238  40 82 00 10 */	bne lbl_800CF348
/* 800CF33C 000CA23C  7F C3 F3 78 */	mr r3, r30
/* 800CF340 000CA240  48 02 25 A9 */	bl OSRestoreInterrupts
/* 800CF344 000CA244  48 00 00 78 */	b lbl_800CF3BC
lbl_800CF348:
/* 800CF348 000CA248  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CF34C 000CA24C  38 80 00 00 */	li r4, 0
/* 800CF350 000CA250  80 7F 01 64 */	lwz r3, 0x164(r31)
/* 800CF354 000CA254  38 A0 00 30 */	li r5, 0x30
/* 800CF358 000CA258  7C 00 07 74 */	extsb r0, r0
/* 800CF35C 000CA25C  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CF360 000CA260  7C 63 02 14 */	add r3, r3, r0
/* 800CF364 000CA264  4B F3 4D A1 */	bl memset
/* 800CF368 000CA268  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CF36C 000CA26C  38 81 02 48 */	addi r4, r1, 0x248
/* 800CF370 000CA270  80 7F 01 64 */	lwz r3, 0x164(r31)
/* 800CF374 000CA274  38 A0 00 30 */	li r5, 0x30
/* 800CF378 000CA278  7C 00 07 74 */	extsb r0, r0
/* 800CF37C 000CA27C  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CF380 000CA280  7C 63 02 14 */	add r3, r3, r0
/* 800CF384 000CA284  4B F3 4C 7D */	bl memcpy
/* 800CF388 000CA288  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CF38C 000CA28C  7F C3 F3 78 */	mr r3, r30
/* 800CF390 000CA290  80 9F 01 68 */	lwz r4, 0x168(r31)
/* 800CF394 000CA294  7C 06 07 74 */	extsb r6, r0
/* 800CF398 000CA298  38 84 FF FF */	addi r4, r4, -1
/* 800CF39C 000CA29C  7C A4 30 50 */	subf r5, r4, r6
/* 800CF3A0 000CA2A0  38 06 00 01 */	addi r0, r6, 1
/* 800CF3A4 000CA2A4  7C 86 20 50 */	subf r4, r6, r4
/* 800CF3A8 000CA2A8  7C A4 20 F8 */	nor r4, r5, r4
/* 800CF3AC 000CA2AC  7C 84 FE 70 */	srawi r4, r4, 0x1f
/* 800CF3B0 000CA2B0  7C 00 20 78 */	andc r0, r0, r4
/* 800CF3B4 000CA2B4  98 1F 01 61 */	stb r0, 0x161(r31)
/* 800CF3B8 000CA2B8  48 02 25 31 */	bl OSRestoreInterrupts
lbl_800CF3BC:
/* 800CF3BC 000CA2BC  39 80 00 00 */	li r12, 0
/* 800CF3C0 000CA2C0  38 00 00 01 */	li r0, 1
/* 800CF3C4 000CA2C4  B0 01 01 D2 */	sth r0, 0x1d2(r1)
/* 800CF3C8 000CA2C8  3B 60 00 19 */	li r27, 0x19
/* 800CF3CC 000CA2CC  81 41 01 C0 */	lwz r10, 0x1c0(r1)
/* 800CF3D0 000CA2D0  99 81 01 BC */	stb r12, 0x1bc(r1)
/* 800CF3D4 000CA2D4  81 21 01 C4 */	lwz r9, 0x1c4(r1)
/* 800CF3D8 000CA2D8  81 61 01 BC */	lwz r11, 0x1bc(r1)
/* 800CF3DC 000CA2DC  81 01 01 C8 */	lwz r8, 0x1c8(r1)
/* 800CF3E0 000CA2E0  80 E1 01 CC */	lwz r7, 0x1cc(r1)
/* 800CF3E4 000CA2E4  80 C1 01 D0 */	lwz r6, 0x1d0(r1)
/* 800CF3E8 000CA2E8  80 A1 01 D4 */	lwz r5, 0x1d4(r1)
/* 800CF3EC 000CA2EC  80 81 01 D8 */	lwz r4, 0x1d8(r1)
/* 800CF3F0 000CA2F0  80 61 01 DC */	lwz r3, 0x1dc(r1)
/* 800CF3F4 000CA2F4  80 01 01 E0 */	lwz r0, 0x1e0(r1)
/* 800CF3F8 000CA2F8  93 61 01 B8 */	stw r27, 0x1b8(r1)
/* 800CF3FC 000CA2FC  91 81 01 E4 */	stw r12, 0x1e4(r1)
/* 800CF400 000CA300  93 61 01 E8 */	stw r27, 0x1e8(r1)
/* 800CF404 000CA304  91 61 01 EC */	stw r11, 0x1ec(r1)
/* 800CF408 000CA308  91 41 01 F0 */	stw r10, 0x1f0(r1)
/* 800CF40C 000CA30C  91 21 01 F4 */	stw r9, 0x1f4(r1)
/* 800CF410 000CA310  91 01 01 F8 */	stw r8, 0x1f8(r1)
/* 800CF414 000CA314  90 E1 01 FC */	stw r7, 0x1fc(r1)
/* 800CF418 000CA318  90 C1 02 00 */	stw r6, 0x200(r1)
/* 800CF41C 000CA31C  90 A1 02 04 */	stw r5, 0x204(r1)
/* 800CF420 000CA320  90 81 02 08 */	stw r4, 0x208(r1)
/* 800CF424 000CA324  90 61 02 0C */	stw r3, 0x20c(r1)
/* 800CF428 000CA328  90 01 02 10 */	stw r0, 0x210(r1)
/* 800CF42C 000CA32C  91 81 02 14 */	stw r12, 0x214(r1)
/* 800CF430 000CA330  48 02 24 91 */	bl OSDisableInterrupts
/* 800CF434 000CA334  7C 7E 1B 78 */	mr r30, r3
/* 800CF438 000CA338  48 02 24 89 */	bl OSDisableInterrupts
/* 800CF43C 000CA33C  88 9F 01 60 */	lbz r4, 0x160(r31)
/* 800CF440 000CA340  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CF444 000CA344  7C 04 00 50 */	subf r0, r4, r0
/* 800CF448 000CA348  7C 1B 07 75 */	extsb. r27, r0
/* 800CF44C 000CA34C  40 80 00 10 */	bge lbl_800CF45C
/* 800CF450 000CA350  80 1F 01 68 */	lwz r0, 0x168(r31)
/* 800CF454 000CA354  7C 1B 02 14 */	add r0, r27, r0
/* 800CF458 000CA358  7C 1B 07 74 */	extsb r27, r0
lbl_800CF45C:
/* 800CF45C 000CA35C  48 02 24 8D */	bl OSRestoreInterrupts
/* 800CF460 000CA360  80 7F 01 68 */	lwz r3, 0x168(r31)
/* 800CF464 000CA364  38 03 FF FF */	addi r0, r3, -1
/* 800CF468 000CA368  7C 00 D8 40 */	cmplw r0, r27
/* 800CF46C 000CA36C  40 82 00 10 */	bne lbl_800CF47C
/* 800CF470 000CA370  7F C3 F3 78 */	mr r3, r30
/* 800CF474 000CA374  48 02 24 75 */	bl OSRestoreInterrupts
/* 800CF478 000CA378  48 00 00 78 */	b lbl_800CF4F0
lbl_800CF47C:
/* 800CF47C 000CA37C  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CF480 000CA380  38 80 00 00 */	li r4, 0
/* 800CF484 000CA384  80 7F 01 64 */	lwz r3, 0x164(r31)
/* 800CF488 000CA388  38 A0 00 30 */	li r5, 0x30
/* 800CF48C 000CA38C  7C 00 07 74 */	extsb r0, r0
/* 800CF490 000CA390  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CF494 000CA394  7C 63 02 14 */	add r3, r3, r0
/* 800CF498 000CA398  4B F3 4C 6D */	bl memset
/* 800CF49C 000CA39C  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CF4A0 000CA3A0  38 81 01 E8 */	addi r4, r1, 0x1e8
/* 800CF4A4 000CA3A4  80 7F 01 64 */	lwz r3, 0x164(r31)
/* 800CF4A8 000CA3A8  38 A0 00 30 */	li r5, 0x30
/* 800CF4AC 000CA3AC  7C 00 07 74 */	extsb r0, r0
/* 800CF4B0 000CA3B0  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CF4B4 000CA3B4  7C 63 02 14 */	add r3, r3, r0
/* 800CF4B8 000CA3B8  4B F3 4B 49 */	bl memcpy
/* 800CF4BC 000CA3BC  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CF4C0 000CA3C0  7F C3 F3 78 */	mr r3, r30
/* 800CF4C4 000CA3C4  80 9F 01 68 */	lwz r4, 0x168(r31)
/* 800CF4C8 000CA3C8  7C 06 07 74 */	extsb r6, r0
/* 800CF4CC 000CA3CC  38 84 FF FF */	addi r4, r4, -1
/* 800CF4D0 000CA3D0  7C A4 30 50 */	subf r5, r4, r6
/* 800CF4D4 000CA3D4  38 06 00 01 */	addi r0, r6, 1
/* 800CF4D8 000CA3D8  7C 86 20 50 */	subf r4, r6, r4
/* 800CF4DC 000CA3DC  7C A4 20 F8 */	nor r4, r5, r4
/* 800CF4E0 000CA3E0  7C 84 FE 70 */	srawi r4, r4, 0x1f
/* 800CF4E4 000CA3E4  7C 00 20 78 */	andc r0, r0, r4
/* 800CF4E8 000CA3E8  98 1F 01 61 */	stb r0, 0x161(r31)
/* 800CF4EC 000CA3EC  48 02 23 FD */	bl OSRestoreInterrupts
lbl_800CF4F0:
/* 800CF4F0 000CA3F0  39 60 00 00 */	li r11, 0
/* 800CF4F4 000CA3F4  38 00 00 01 */	li r0, 1
/* 800CF4F8 000CA3F8  B0 01 01 72 */	sth r0, 0x172(r1)
/* 800CF4FC 000CA3FC  39 80 00 15 */	li r12, 0x15
/* 800CF500 000CA400  81 21 01 60 */	lwz r9, 0x160(r1)
/* 800CF504 000CA404  99 61 01 5C */	stb r11, 0x15c(r1)
/* 800CF508 000CA408  81 01 01 64 */	lwz r8, 0x164(r1)
/* 800CF50C 000CA40C  81 41 01 5C */	lwz r10, 0x15c(r1)
/* 800CF510 000CA410  80 E1 01 68 */	lwz r7, 0x168(r1)
/* 800CF514 000CA414  80 C1 01 6C */	lwz r6, 0x16c(r1)
/* 800CF518 000CA418  80 A1 01 70 */	lwz r5, 0x170(r1)
/* 800CF51C 000CA41C  80 81 01 74 */	lwz r4, 0x174(r1)
/* 800CF520 000CA420  80 61 01 78 */	lwz r3, 0x178(r1)
/* 800CF524 000CA424  80 01 01 7C */	lwz r0, 0x17c(r1)
/* 800CF528 000CA428  91 81 01 58 */	stw r12, 0x158(r1)
/* 800CF52C 000CA42C  93 81 01 84 */	stw r28, 0x184(r1)
/* 800CF530 000CA430  91 61 01 80 */	stw r11, 0x180(r1)
/* 800CF534 000CA434  91 81 01 88 */	stw r12, 0x188(r1)
/* 800CF538 000CA438  91 41 01 8C */	stw r10, 0x18c(r1)
/* 800CF53C 000CA43C  91 21 01 90 */	stw r9, 0x190(r1)
/* 800CF540 000CA440  91 01 01 94 */	stw r8, 0x194(r1)
/* 800CF544 000CA444  90 E1 01 98 */	stw r7, 0x198(r1)
/* 800CF548 000CA448  90 C1 01 9C */	stw r6, 0x19c(r1)
/* 800CF54C 000CA44C  90 A1 01 A0 */	stw r5, 0x1a0(r1)
/* 800CF550 000CA450  90 81 01 A4 */	stw r4, 0x1a4(r1)
/* 800CF554 000CA454  90 61 01 A8 */	stw r3, 0x1a8(r1)
/* 800CF558 000CA458  90 01 01 AC */	stw r0, 0x1ac(r1)
/* 800CF55C 000CA45C  91 61 01 B0 */	stw r11, 0x1b0(r1)
/* 800CF560 000CA460  93 81 01 B4 */	stw r28, 0x1b4(r1)
/* 800CF564 000CA464  48 02 23 5D */	bl OSDisableInterrupts
/* 800CF568 000CA468  7C 7E 1B 78 */	mr r30, r3
/* 800CF56C 000CA46C  48 02 23 55 */	bl OSDisableInterrupts
/* 800CF570 000CA470  88 9F 01 60 */	lbz r4, 0x160(r31)
/* 800CF574 000CA474  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CF578 000CA478  7C 04 00 50 */	subf r0, r4, r0
/* 800CF57C 000CA47C  7C 1B 07 75 */	extsb. r27, r0
/* 800CF580 000CA480  40 80 00 10 */	bge lbl_800CF590
/* 800CF584 000CA484  80 1F 01 68 */	lwz r0, 0x168(r31)
/* 800CF588 000CA488  7C 1B 02 14 */	add r0, r27, r0
/* 800CF58C 000CA48C  7C 1B 07 74 */	extsb r27, r0
lbl_800CF590:
/* 800CF590 000CA490  48 02 23 59 */	bl OSRestoreInterrupts
/* 800CF594 000CA494  80 7F 01 68 */	lwz r3, 0x168(r31)
/* 800CF598 000CA498  38 03 FF FF */	addi r0, r3, -1
/* 800CF59C 000CA49C  7C 00 D8 40 */	cmplw r0, r27
/* 800CF5A0 000CA4A0  40 82 00 10 */	bne lbl_800CF5B0
/* 800CF5A4 000CA4A4  7F C3 F3 78 */	mr r3, r30
/* 800CF5A8 000CA4A8  48 02 23 41 */	bl OSRestoreInterrupts
/* 800CF5AC 000CA4AC  48 00 00 78 */	b lbl_800CF624
lbl_800CF5B0:
/* 800CF5B0 000CA4B0  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CF5B4 000CA4B4  38 80 00 00 */	li r4, 0
/* 800CF5B8 000CA4B8  80 7F 01 64 */	lwz r3, 0x164(r31)
/* 800CF5BC 000CA4BC  38 A0 00 30 */	li r5, 0x30
/* 800CF5C0 000CA4C0  7C 00 07 74 */	extsb r0, r0
/* 800CF5C4 000CA4C4  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CF5C8 000CA4C8  7C 63 02 14 */	add r3, r3, r0
/* 800CF5CC 000CA4CC  4B F3 4B 39 */	bl memset
/* 800CF5D0 000CA4D0  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CF5D4 000CA4D4  38 81 01 88 */	addi r4, r1, 0x188
/* 800CF5D8 000CA4D8  80 7F 01 64 */	lwz r3, 0x164(r31)
/* 800CF5DC 000CA4DC  38 A0 00 30 */	li r5, 0x30
/* 800CF5E0 000CA4E0  7C 00 07 74 */	extsb r0, r0
/* 800CF5E4 000CA4E4  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CF5E8 000CA4E8  7C 63 02 14 */	add r3, r3, r0
/* 800CF5EC 000CA4EC  4B F3 4A 15 */	bl memcpy
/* 800CF5F0 000CA4F0  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CF5F4 000CA4F4  7F C3 F3 78 */	mr r3, r30
/* 800CF5F8 000CA4F8  80 9F 01 68 */	lwz r4, 0x168(r31)
/* 800CF5FC 000CA4FC  7C 06 07 74 */	extsb r6, r0
/* 800CF600 000CA500  38 84 FF FF */	addi r4, r4, -1
/* 800CF604 000CA504  7C A4 30 50 */	subf r5, r4, r6
/* 800CF608 000CA508  38 06 00 01 */	addi r0, r6, 1
/* 800CF60C 000CA50C  7C 86 20 50 */	subf r4, r6, r4
/* 800CF610 000CA510  7C A4 20 F8 */	nor r4, r5, r4
/* 800CF614 000CA514  7C 84 FE 70 */	srawi r4, r4, 0x1f
/* 800CF618 000CA518  7C 00 20 78 */	andc r0, r0, r4
/* 800CF61C 000CA51C  98 1F 01 61 */	stb r0, 0x161(r31)
/* 800CF620 000CA520  48 02 22 C9 */	bl OSRestoreInterrupts
lbl_800CF624:
/* 800CF624 000CA524  7F A3 EB 78 */	mr r3, r29
/* 800CF628 000CA528  48 02 22 C1 */	bl OSRestoreInterrupts
/* 800CF62C 000CA52C  38 60 00 00 */	li r3, 0
/* 800CF630 000CA530  48 00 04 78 */	b lbl_800CFAA8
lbl_800CF634:
/* 800CF634 000CA534  7F A3 EB 78 */	mr r3, r29
/* 800CF638 000CA538  3B 40 FF FE */	li r26, -2
/* 800CF63C 000CA53C  48 02 22 AD */	bl OSRestoreInterrupts
/* 800CF640 000CA540  48 00 04 48 */	b lbl_800CFA88
lbl_800CF644:
/* 800CF644 000CA544  38 60 00 01 */	li r3, 1
/* 800CF648 000CA548  38 00 00 04 */	li r0, 4
/* 800CF64C 000CA54C  B0 61 01 12 */	sth r3, 0x112(r1)
/* 800CF650 000CA550  39 80 00 19 */	li r12, 0x19
/* 800CF654 000CA554  81 41 01 00 */	lwz r10, 0x100(r1)
/* 800CF658 000CA558  98 01 00 FC */	stb r0, 0xfc(r1)
/* 800CF65C 000CA55C  81 21 01 04 */	lwz r9, 0x104(r1)
/* 800CF660 000CA560  81 61 00 FC */	lwz r11, 0xfc(r1)
/* 800CF664 000CA564  81 01 01 08 */	lwz r8, 0x108(r1)
/* 800CF668 000CA568  80 E1 01 0C */	lwz r7, 0x10c(r1)
/* 800CF66C 000CA56C  80 C1 01 10 */	lwz r6, 0x110(r1)
/* 800CF670 000CA570  80 A1 01 14 */	lwz r5, 0x114(r1)
/* 800CF674 000CA574  80 81 01 18 */	lwz r4, 0x118(r1)
/* 800CF678 000CA578  80 61 01 1C */	lwz r3, 0x11c(r1)
/* 800CF67C 000CA57C  80 01 01 20 */	lwz r0, 0x120(r1)
/* 800CF680 000CA580  91 81 00 F8 */	stw r12, 0xf8(r1)
/* 800CF684 000CA584  93 81 01 24 */	stw r28, 0x124(r1)
/* 800CF688 000CA588  91 81 01 28 */	stw r12, 0x128(r1)
/* 800CF68C 000CA58C  91 61 01 2C */	stw r11, 0x12c(r1)
/* 800CF690 000CA590  91 41 01 30 */	stw r10, 0x130(r1)
/* 800CF694 000CA594  91 21 01 34 */	stw r9, 0x134(r1)
/* 800CF698 000CA598  91 01 01 38 */	stw r8, 0x138(r1)
/* 800CF69C 000CA59C  90 E1 01 3C */	stw r7, 0x13c(r1)
/* 800CF6A0 000CA5A0  90 C1 01 40 */	stw r6, 0x140(r1)
/* 800CF6A4 000CA5A4  90 A1 01 44 */	stw r5, 0x144(r1)
/* 800CF6A8 000CA5A8  90 81 01 48 */	stw r4, 0x148(r1)
/* 800CF6AC 000CA5AC  90 61 01 4C */	stw r3, 0x14c(r1)
/* 800CF6B0 000CA5B0  90 01 01 50 */	stw r0, 0x150(r1)
/* 800CF6B4 000CA5B4  93 81 01 54 */	stw r28, 0x154(r1)
/* 800CF6B8 000CA5B8  48 02 22 09 */	bl OSDisableInterrupts
/* 800CF6BC 000CA5BC  7C 7E 1B 78 */	mr r30, r3
/* 800CF6C0 000CA5C0  48 02 22 01 */	bl OSDisableInterrupts
/* 800CF6C4 000CA5C4  88 9F 01 60 */	lbz r4, 0x160(r31)
/* 800CF6C8 000CA5C8  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CF6CC 000CA5CC  7C 04 00 50 */	subf r0, r4, r0
/* 800CF6D0 000CA5D0  7C 1D 07 75 */	extsb. r29, r0
/* 800CF6D4 000CA5D4  40 80 00 10 */	bge lbl_800CF6E4
/* 800CF6D8 000CA5D8  80 1F 01 68 */	lwz r0, 0x168(r31)
/* 800CF6DC 000CA5DC  7C 1D 02 14 */	add r0, r29, r0
/* 800CF6E0 000CA5E0  7C 1D 07 74 */	extsb r29, r0
lbl_800CF6E4:
/* 800CF6E4 000CA5E4  48 02 22 05 */	bl OSRestoreInterrupts
/* 800CF6E8 000CA5E8  80 7F 01 68 */	lwz r3, 0x168(r31)
/* 800CF6EC 000CA5EC  38 03 FF FF */	addi r0, r3, -1
/* 800CF6F0 000CA5F0  7C 00 E8 40 */	cmplw r0, r29
/* 800CF6F4 000CA5F4  40 82 00 14 */	bne lbl_800CF708
/* 800CF6F8 000CA5F8  7F C3 F3 78 */	mr r3, r30
/* 800CF6FC 000CA5FC  48 02 21 ED */	bl OSRestoreInterrupts
/* 800CF700 000CA600  38 00 00 00 */	li r0, 0
/* 800CF704 000CA604  48 00 00 7C */	b lbl_800CF780
lbl_800CF708:
/* 800CF708 000CA608  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CF70C 000CA60C  38 80 00 00 */	li r4, 0
/* 800CF710 000CA610  80 7F 01 64 */	lwz r3, 0x164(r31)
/* 800CF714 000CA614  38 A0 00 30 */	li r5, 0x30
/* 800CF718 000CA618  7C 00 07 74 */	extsb r0, r0
/* 800CF71C 000CA61C  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CF720 000CA620  7C 63 02 14 */	add r3, r3, r0
/* 800CF724 000CA624  4B F3 49 E1 */	bl memset
/* 800CF728 000CA628  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CF72C 000CA62C  38 81 01 28 */	addi r4, r1, 0x128
/* 800CF730 000CA630  80 7F 01 64 */	lwz r3, 0x164(r31)
/* 800CF734 000CA634  38 A0 00 30 */	li r5, 0x30
/* 800CF738 000CA638  7C 00 07 74 */	extsb r0, r0
/* 800CF73C 000CA63C  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CF740 000CA640  7C 63 02 14 */	add r3, r3, r0
/* 800CF744 000CA644  4B F3 48 BD */	bl memcpy
/* 800CF748 000CA648  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CF74C 000CA64C  7F C3 F3 78 */	mr r3, r30
/* 800CF750 000CA650  80 9F 01 68 */	lwz r4, 0x168(r31)
/* 800CF754 000CA654  7C 06 07 74 */	extsb r6, r0
/* 800CF758 000CA658  38 84 FF FF */	addi r4, r4, -1
/* 800CF75C 000CA65C  7C A4 30 50 */	subf r5, r4, r6
/* 800CF760 000CA660  38 06 00 01 */	addi r0, r6, 1
/* 800CF764 000CA664  7C 86 20 50 */	subf r4, r6, r4
/* 800CF768 000CA668  7C A4 20 F8 */	nor r4, r5, r4
/* 800CF76C 000CA66C  7C 84 FE 70 */	srawi r4, r4, 0x1f
/* 800CF770 000CA670  7C 00 20 78 */	andc r0, r0, r4
/* 800CF774 000CA674  98 1F 01 61 */	stb r0, 0x161(r31)
/* 800CF778 000CA678  48 02 21 71 */	bl OSRestoreInterrupts
/* 800CF77C 000CA67C  38 00 00 01 */	li r0, 1
lbl_800CF780:
/* 800CF780 000CA680  2C 00 00 00 */	cmpwi r0, 0
/* 800CF784 000CA684  40 82 00 0C */	bne lbl_800CF790
/* 800CF788 000CA688  3B 40 FF FE */	li r26, -2
/* 800CF78C 000CA68C  48 00 02 FC */	b lbl_800CFA88
lbl_800CF790:
/* 800CF790 000CA690  38 60 00 00 */	li r3, 0
/* 800CF794 000CA694  48 00 03 14 */	b lbl_800CFAA8
lbl_800CF798:
/* 800CF798 000CA698  38 60 00 01 */	li r3, 1
/* 800CF79C 000CA69C  38 00 00 00 */	li r0, 0
/* 800CF7A0 000CA6A0  B0 61 00 B2 */	sth r3, 0xb2(r1)
/* 800CF7A4 000CA6A4  39 80 00 19 */	li r12, 0x19
/* 800CF7A8 000CA6A8  81 41 00 A0 */	lwz r10, 0xa0(r1)
/* 800CF7AC 000CA6AC  98 01 00 9C */	stb r0, 0x9c(r1)
/* 800CF7B0 000CA6B0  81 21 00 A4 */	lwz r9, 0xa4(r1)
/* 800CF7B4 000CA6B4  81 61 00 9C */	lwz r11, 0x9c(r1)
/* 800CF7B8 000CA6B8  81 01 00 A8 */	lwz r8, 0xa8(r1)
/* 800CF7BC 000CA6BC  80 E1 00 AC */	lwz r7, 0xac(r1)
/* 800CF7C0 000CA6C0  80 C1 00 B0 */	lwz r6, 0xb0(r1)
/* 800CF7C4 000CA6C4  80 A1 00 B4 */	lwz r5, 0xb4(r1)
/* 800CF7C8 000CA6C8  80 81 00 B8 */	lwz r4, 0xb8(r1)
/* 800CF7CC 000CA6CC  80 61 00 BC */	lwz r3, 0xbc(r1)
/* 800CF7D0 000CA6D0  80 01 00 C0 */	lwz r0, 0xc0(r1)
/* 800CF7D4 000CA6D4  91 81 00 98 */	stw r12, 0x98(r1)
/* 800CF7D8 000CA6D8  93 81 00 C4 */	stw r28, 0xc4(r1)
/* 800CF7DC 000CA6DC  91 81 00 C8 */	stw r12, 0xc8(r1)
/* 800CF7E0 000CA6E0  91 61 00 CC */	stw r11, 0xcc(r1)
/* 800CF7E4 000CA6E4  91 41 00 D0 */	stw r10, 0xd0(r1)
/* 800CF7E8 000CA6E8  91 21 00 D4 */	stw r9, 0xd4(r1)
/* 800CF7EC 000CA6EC  91 01 00 D8 */	stw r8, 0xd8(r1)
/* 800CF7F0 000CA6F0  90 E1 00 DC */	stw r7, 0xdc(r1)
/* 800CF7F4 000CA6F4  90 C1 00 E0 */	stw r6, 0xe0(r1)
/* 800CF7F8 000CA6F8  90 A1 00 E4 */	stw r5, 0xe4(r1)
/* 800CF7FC 000CA6FC  90 81 00 E8 */	stw r4, 0xe8(r1)
/* 800CF800 000CA700  90 61 00 EC */	stw r3, 0xec(r1)
/* 800CF804 000CA704  90 01 00 F0 */	stw r0, 0xf0(r1)
/* 800CF808 000CA708  93 81 00 F4 */	stw r28, 0xf4(r1)
/* 800CF80C 000CA70C  48 02 20 B5 */	bl OSDisableInterrupts
/* 800CF810 000CA710  7C 7E 1B 78 */	mr r30, r3
/* 800CF814 000CA714  48 02 20 AD */	bl OSDisableInterrupts
/* 800CF818 000CA718  88 9F 01 60 */	lbz r4, 0x160(r31)
/* 800CF81C 000CA71C  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CF820 000CA720  7C 04 00 50 */	subf r0, r4, r0
/* 800CF824 000CA724  7C 1D 07 75 */	extsb. r29, r0
/* 800CF828 000CA728  40 80 00 10 */	bge lbl_800CF838
/* 800CF82C 000CA72C  80 1F 01 68 */	lwz r0, 0x168(r31)
/* 800CF830 000CA730  7C 1D 02 14 */	add r0, r29, r0
/* 800CF834 000CA734  7C 1D 07 74 */	extsb r29, r0
lbl_800CF838:
/* 800CF838 000CA738  48 02 20 B1 */	bl OSRestoreInterrupts
/* 800CF83C 000CA73C  80 7F 01 68 */	lwz r3, 0x168(r31)
/* 800CF840 000CA740  38 03 FF FF */	addi r0, r3, -1
/* 800CF844 000CA744  7C 00 E8 40 */	cmplw r0, r29
/* 800CF848 000CA748  40 82 00 14 */	bne lbl_800CF85C
/* 800CF84C 000CA74C  7F C3 F3 78 */	mr r3, r30
/* 800CF850 000CA750  48 02 20 99 */	bl OSRestoreInterrupts
/* 800CF854 000CA754  38 00 00 00 */	li r0, 0
/* 800CF858 000CA758  48 00 00 7C */	b lbl_800CF8D4
lbl_800CF85C:
/* 800CF85C 000CA75C  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CF860 000CA760  38 80 00 00 */	li r4, 0
/* 800CF864 000CA764  80 7F 01 64 */	lwz r3, 0x164(r31)
/* 800CF868 000CA768  38 A0 00 30 */	li r5, 0x30
/* 800CF86C 000CA76C  7C 00 07 74 */	extsb r0, r0
/* 800CF870 000CA770  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CF874 000CA774  7C 63 02 14 */	add r3, r3, r0
/* 800CF878 000CA778  4B F3 48 8D */	bl memset
/* 800CF87C 000CA77C  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CF880 000CA780  38 81 00 C8 */	addi r4, r1, 0xc8
/* 800CF884 000CA784  80 7F 01 64 */	lwz r3, 0x164(r31)
/* 800CF888 000CA788  38 A0 00 30 */	li r5, 0x30
/* 800CF88C 000CA78C  7C 00 07 74 */	extsb r0, r0
/* 800CF890 000CA790  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CF894 000CA794  7C 63 02 14 */	add r3, r3, r0
/* 800CF898 000CA798  4B F3 47 69 */	bl memcpy
/* 800CF89C 000CA79C  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CF8A0 000CA7A0  7F C3 F3 78 */	mr r3, r30
/* 800CF8A4 000CA7A4  80 9F 01 68 */	lwz r4, 0x168(r31)
/* 800CF8A8 000CA7A8  7C 06 07 74 */	extsb r6, r0
/* 800CF8AC 000CA7AC  38 84 FF FF */	addi r4, r4, -1
/* 800CF8B0 000CA7B0  7C A4 30 50 */	subf r5, r4, r6
/* 800CF8B4 000CA7B4  38 06 00 01 */	addi r0, r6, 1
/* 800CF8B8 000CA7B8  7C 86 20 50 */	subf r4, r6, r4
/* 800CF8BC 000CA7BC  7C A4 20 F8 */	nor r4, r5, r4
/* 800CF8C0 000CA7C0  7C 84 FE 70 */	srawi r4, r4, 0x1f
/* 800CF8C4 000CA7C4  7C 00 20 78 */	andc r0, r0, r4
/* 800CF8C8 000CA7C8  98 1F 01 61 */	stb r0, 0x161(r31)
/* 800CF8CC 000CA7CC  48 02 20 1D */	bl OSRestoreInterrupts
/* 800CF8D0 000CA7D0  38 00 00 01 */	li r0, 1
lbl_800CF8D4:
/* 800CF8D4 000CA7D4  2C 00 00 00 */	cmpwi r0, 0
/* 800CF8D8 000CA7D8  40 82 00 0C */	bne lbl_800CF8E4
/* 800CF8DC 000CA7DC  3B 40 FF FE */	li r26, -2
/* 800CF8E0 000CA7E0  48 00 01 A8 */	b lbl_800CFA88
lbl_800CF8E4:
/* 800CF8E4 000CA7E4  38 60 00 00 */	li r3, 0
/* 800CF8E8 000CA7E8  48 00 01 C0 */	b lbl_800CFAA8
lbl_800CF8EC:
/* 800CF8EC 000CA7EC  3C 60 04 A2 */	lis r3, 0x04A20008@ha
/* 800CF8F0 000CA7F0  38 E0 00 01 */	li r7, 1
/* 800CF8F4 000CA7F4  38 A3 00 08 */	addi r5, r3, 0x04A20008@l
/* 800CF8F8 000CA7F8  38 C0 00 16 */	li r6, 0x16
/* 800CF8FC 000CA7FC  38 00 00 15 */	li r0, 0x15
/* 800CF900 000CA800  90 A1 00 14 */	stw r5, 0x14(r1)
/* 800CF904 000CA804  38 61 00 6C */	addi r3, r1, 0x6c
/* 800CF908 000CA808  38 81 00 14 */	addi r4, r1, 0x14
/* 800CF90C 000CA80C  98 E1 00 09 */	stb r7, 9(r1)
/* 800CF910 000CA810  38 A0 00 04 */	li r5, 4
/* 800CF914 000CA814  98 E1 00 08 */	stb r7, 8(r1)
/* 800CF918 000CA818  90 C1 00 68 */	stw r6, 0x68(r1)
/* 800CF91C 000CA81C  B0 01 00 82 */	sth r0, 0x82(r1)
/* 800CF920 000CA820  93 81 00 94 */	stw r28, 0x94(r1)
/* 800CF924 000CA824  4B F3 46 DD */	bl memcpy
/* 800CF928 000CA828  38 61 00 70 */	addi r3, r1, 0x70
/* 800CF92C 000CA82C  38 81 00 08 */	addi r4, r1, 8
/* 800CF930 000CA830  38 A0 00 01 */	li r5, 1
/* 800CF934 000CA834  4B F3 46 CD */	bl memcpy
/* 800CF938 000CA838  38 61 00 71 */	addi r3, r1, 0x71
/* 800CF93C 000CA83C  38 81 00 09 */	addi r4, r1, 9
/* 800CF940 000CA840  38 A0 00 01 */	li r5, 1
/* 800CF944 000CA844  4B F3 46 BD */	bl memcpy
/* 800CF948 000CA848  83 A1 00 68 */	lwz r29, 0x68(r1)
/* 800CF94C 000CA84C  81 81 00 6C */	lwz r12, 0x6c(r1)
/* 800CF950 000CA850  81 61 00 70 */	lwz r11, 0x70(r1)
/* 800CF954 000CA854  81 41 00 74 */	lwz r10, 0x74(r1)
/* 800CF958 000CA858  81 21 00 78 */	lwz r9, 0x78(r1)
/* 800CF95C 000CA85C  81 01 00 7C */	lwz r8, 0x7c(r1)
/* 800CF960 000CA860  80 E1 00 80 */	lwz r7, 0x80(r1)
/* 800CF964 000CA864  80 C1 00 84 */	lwz r6, 0x84(r1)
/* 800CF968 000CA868  80 A1 00 88 */	lwz r5, 0x88(r1)
/* 800CF96C 000CA86C  80 81 00 8C */	lwz r4, 0x8c(r1)
/* 800CF970 000CA870  80 61 00 90 */	lwz r3, 0x90(r1)
/* 800CF974 000CA874  80 01 00 94 */	lwz r0, 0x94(r1)
/* 800CF978 000CA878  93 A1 00 38 */	stw r29, 0x38(r1)
/* 800CF97C 000CA87C  91 81 00 3C */	stw r12, 0x3c(r1)
/* 800CF980 000CA880  91 61 00 40 */	stw r11, 0x40(r1)
/* 800CF984 000CA884  91 41 00 44 */	stw r10, 0x44(r1)
/* 800CF988 000CA888  91 21 00 48 */	stw r9, 0x48(r1)
/* 800CF98C 000CA88C  91 01 00 4C */	stw r8, 0x4c(r1)
/* 800CF990 000CA890  90 E1 00 50 */	stw r7, 0x50(r1)
/* 800CF994 000CA894  90 C1 00 54 */	stw r6, 0x54(r1)
/* 800CF998 000CA898  90 A1 00 58 */	stw r5, 0x58(r1)
/* 800CF99C 000CA89C  90 81 00 5C */	stw r4, 0x5c(r1)
/* 800CF9A0 000CA8A0  90 61 00 60 */	stw r3, 0x60(r1)
/* 800CF9A4 000CA8A4  90 01 00 64 */	stw r0, 0x64(r1)
/* 800CF9A8 000CA8A8  48 02 1F 19 */	bl OSDisableInterrupts
/* 800CF9AC 000CA8AC  7C 7E 1B 78 */	mr r30, r3
/* 800CF9B0 000CA8B0  48 02 1F 11 */	bl OSDisableInterrupts
/* 800CF9B4 000CA8B4  88 9F 01 60 */	lbz r4, 0x160(r31)
/* 800CF9B8 000CA8B8  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CF9BC 000CA8BC  7C 04 00 50 */	subf r0, r4, r0
/* 800CF9C0 000CA8C0  7C 1D 07 75 */	extsb. r29, r0
/* 800CF9C4 000CA8C4  40 80 00 10 */	bge lbl_800CF9D4
/* 800CF9C8 000CA8C8  80 1F 01 68 */	lwz r0, 0x168(r31)
/* 800CF9CC 000CA8CC  7C 1D 02 14 */	add r0, r29, r0
/* 800CF9D0 000CA8D0  7C 1D 07 74 */	extsb r29, r0
lbl_800CF9D4:
/* 800CF9D4 000CA8D4  48 02 1F 15 */	bl OSRestoreInterrupts
/* 800CF9D8 000CA8D8  80 7F 01 68 */	lwz r3, 0x168(r31)
/* 800CF9DC 000CA8DC  38 03 FF FF */	addi r0, r3, -1
/* 800CF9E0 000CA8E0  7C 00 E8 40 */	cmplw r0, r29
/* 800CF9E4 000CA8E4  40 82 00 14 */	bne lbl_800CF9F8
/* 800CF9E8 000CA8E8  7F C3 F3 78 */	mr r3, r30
/* 800CF9EC 000CA8EC  48 02 1E FD */	bl OSRestoreInterrupts
/* 800CF9F0 000CA8F0  38 00 00 00 */	li r0, 0
/* 800CF9F4 000CA8F4  48 00 00 7C */	b lbl_800CFA70
lbl_800CF9F8:
/* 800CF9F8 000CA8F8  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CF9FC 000CA8FC  38 80 00 00 */	li r4, 0
/* 800CFA00 000CA900  80 7F 01 64 */	lwz r3, 0x164(r31)
/* 800CFA04 000CA904  38 A0 00 30 */	li r5, 0x30
/* 800CFA08 000CA908  7C 00 07 74 */	extsb r0, r0
/* 800CFA0C 000CA90C  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CFA10 000CA910  7C 63 02 14 */	add r3, r3, r0
/* 800CFA14 000CA914  4B F3 46 F1 */	bl memset
/* 800CFA18 000CA918  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CFA1C 000CA91C  38 81 00 38 */	addi r4, r1, 0x38
/* 800CFA20 000CA920  80 7F 01 64 */	lwz r3, 0x164(r31)
/* 800CFA24 000CA924  38 A0 00 30 */	li r5, 0x30
/* 800CFA28 000CA928  7C 00 07 74 */	extsb r0, r0
/* 800CFA2C 000CA92C  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CFA30 000CA930  7C 63 02 14 */	add r3, r3, r0
/* 800CFA34 000CA934  4B F3 45 CD */	bl memcpy
/* 800CFA38 000CA938  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CFA3C 000CA93C  7F C3 F3 78 */	mr r3, r30
/* 800CFA40 000CA940  80 9F 01 68 */	lwz r4, 0x168(r31)
/* 800CFA44 000CA944  7C 06 07 74 */	extsb r6, r0
/* 800CFA48 000CA948  38 84 FF FF */	addi r4, r4, -1
/* 800CFA4C 000CA94C  7C A4 30 50 */	subf r5, r4, r6
/* 800CFA50 000CA950  38 06 00 01 */	addi r0, r6, 1
/* 800CFA54 000CA954  7C 86 20 50 */	subf r4, r6, r4
/* 800CFA58 000CA958  7C A4 20 F8 */	nor r4, r5, r4
/* 800CFA5C 000CA95C  7C 84 FE 70 */	srawi r4, r4, 0x1f
/* 800CFA60 000CA960  7C 00 20 78 */	andc r0, r0, r4
/* 800CFA64 000CA964  98 1F 01 61 */	stb r0, 0x161(r31)
/* 800CFA68 000CA968  48 02 1E 81 */	bl OSRestoreInterrupts
/* 800CFA6C 000CA96C  38 00 00 01 */	li r0, 1
lbl_800CFA70:
/* 800CFA70 000CA970  2C 00 00 00 */	cmpwi r0, 0
/* 800CFA74 000CA974  40 82 00 0C */	bne lbl_800CFA80
/* 800CFA78 000CA978  3B 40 FF FE */	li r26, -2
/* 800CFA7C 000CA97C  48 00 00 0C */	b lbl_800CFA88
lbl_800CFA80:
/* 800CFA80 000CA980  38 60 00 00 */	li r3, 0
/* 800CFA84 000CA984  48 00 00 24 */	b lbl_800CFAA8
lbl_800CFA88:
/* 800CFA88 000CA988  2C 1C 00 00 */	cmpwi r28, 0
/* 800CFA8C 000CA98C  41 82 00 18 */	beq lbl_800CFAA4
/* 800CFA90 000CA990  7F 8C E3 78 */	mr r12, r28
/* 800CFA94 000CA994  7F 63 DB 78 */	mr r3, r27
/* 800CFA98 000CA998  7F 44 D3 78 */	mr r4, r26
/* 800CFA9C 000CA99C  7D 89 03 A6 */	mtctr r12
/* 800CFAA0 000CA9A0  4E 80 04 21 */	bctrl 
lbl_800CFAA4:
/* 800CFAA4 000CA9A4  7F 43 D3 78 */	mr r3, r26
lbl_800CFAA8:
/* 800CFAA8 000CA9A8  39 61 06 00 */	addi r11, r1, 0x600
/* 800CFAAC 000CA9AC  4B FE 22 DD */	bl _restgpr_25
/* 800CFAB0 000CA9B0  80 01 06 04 */	lwz r0, 0x604(r1)
/* 800CFAB4 000CA9B4  7C 08 03 A6 */	mtlr r0
/* 800CFAB8 000CA9B8  38 21 06 00 */	addi r1, r1, 0x600
/* 800CFABC 000CA9BC  4E 80 00 20 */	blr 

.global WPADGetSpeakerVolume
WPADGetSpeakerVolume:
/* 800CFAC0 000CA9C0  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800CFAC4 000CA9C4  7C 08 02 A6 */	mflr r0
/* 800CFAC8 000CA9C8  90 01 00 14 */	stw r0, 0x14(r1)
/* 800CFACC 000CA9CC  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800CFAD0 000CA9D0  48 02 1D F1 */	bl OSDisableInterrupts
/* 800CFAD4 000CA9D4  8B ED 9A 72 */	lbz r31, _speakerVolume-_SDA_BASE_(r13)
/* 800CFAD8 000CA9D8  48 02 1E 11 */	bl OSRestoreInterrupts
/* 800CFADC 000CA9DC  7F E3 FB 78 */	mr r3, r31
/* 800CFAE0 000CA9E0  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 800CFAE4 000CA9E4  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800CFAE8 000CA9E8  7C 08 03 A6 */	mtlr r0
/* 800CFAEC 000CA9EC  38 21 00 10 */	addi r1, r1, 0x10
/* 800CFAF0 000CA9F0  4E 80 00 20 */	blr 

.global WPADSetSpeakerVolume
WPADSetSpeakerVolume:
/* 800CFAF4 000CA9F4  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800CFAF8 000CA9F8  7C 08 02 A6 */	mflr r0
/* 800CFAFC 000CA9FC  90 01 00 14 */	stw r0, 0x14(r1)
/* 800CFB00 000CAA00  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800CFB04 000CAA04  7C 7F 1B 78 */	mr r31, r3
/* 800CFB08 000CAA08  48 02 1D B9 */	bl OSDisableInterrupts
/* 800CFB0C 000CAA0C  2C 1F 00 00 */	cmpwi r31, 0
/* 800CFB10 000CAA10  7F E0 FB 78 */	mr r0, r31
/* 800CFB14 000CAA14  40 82 00 08 */	bne lbl_800CFB1C
/* 800CFB18 000CAA18  38 00 00 00 */	li r0, 0
lbl_800CFB1C:
/* 800CFB1C 000CAA1C  28 1F 00 7F */	cmplwi r31, 0x7f
/* 800CFB20 000CAA20  41 80 00 08 */	blt lbl_800CFB28
/* 800CFB24 000CAA24  38 00 00 7F */	li r0, 0x7f
lbl_800CFB28:
/* 800CFB28 000CAA28  98 0D 9A 72 */	stb r0, _speakerVolume-_SDA_BASE_(r13)
/* 800CFB2C 000CAA2C  48 02 1D BD */	bl OSRestoreInterrupts
/* 800CFB30 000CAA30  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800CFB34 000CAA34  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 800CFB38 000CAA38  7C 08 03 A6 */	mtlr r0
/* 800CFB3C 000CAA3C  38 21 00 10 */	addi r1, r1, 0x10
/* 800CFB40 000CAA40  4E 80 00 20 */	blr 

.global IsBusyStream
IsBusyStream:
/* 800CFB44 000CAA44  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 800CFB48 000CAA48  7C 08 02 A6 */	mflr r0
/* 800CFB4C 000CAA4C  90 01 00 34 */	stw r0, 0x34(r1)
/* 800CFB50 000CAA50  39 61 00 30 */	addi r11, r1, 0x30
/* 800CFB54 000CAA54  4B FE 21 DD */	bl _savegpr_22
/* 800CFB58 000CAA58  3F 60 80 41 */	lis r27, _wpdcb@ha
/* 800CFB5C 000CAA5C  54 79 10 3A */	slwi r25, r3, 2
/* 800CFB60 000CAA60  3B 7B F6 30 */	addi r27, r27, _wpdcb@l
/* 800CFB64 000CAA64  7F DB C8 2E */	lwzx r30, r27, r25
/* 800CFB68 000CAA68  48 02 1D 59 */	bl OSDisableInterrupts
/* 800CFB6C 000CAA6C  8B BE 08 CD */	lbz r29, 0x8cd(r30)
/* 800CFB70 000CAA70  7C 7F 1B 78 */	mr r31, r3
/* 800CFB74 000CAA74  8B 9E 08 C1 */	lbz r28, 0x8c1(r30)
/* 800CFB78 000CAA78  48 03 0C 1D */	bl WUDGetBufferStatus
/* 800CFB7C 000CAA7C  7C 7A 1B 78 */	mr r26, r3
/* 800CFB80 000CAA80  48 02 1D 41 */	bl OSDisableInterrupts
/* 800CFB84 000CAA84  88 9E 01 60 */	lbz r4, 0x160(r30)
/* 800CFB88 000CAA88  88 1E 01 61 */	lbz r0, 0x161(r30)
/* 800CFB8C 000CAA8C  7C 04 00 50 */	subf r0, r4, r0
/* 800CFB90 000CAA90  7C 18 07 75 */	extsb. r24, r0
/* 800CFB94 000CAA94  40 80 00 10 */	bge lbl_800CFBA4
/* 800CFB98 000CAA98  80 1E 01 68 */	lwz r0, 0x168(r30)
/* 800CFB9C 000CAA9C  7C 18 02 14 */	add r0, r24, r0
/* 800CFBA0 000CAAA0  7C 18 07 74 */	extsb r24, r0
lbl_800CFBA4:
/* 800CFBA4 000CAAA4  48 02 1D 45 */	bl OSRestoreInterrupts
/* 800CFBA8 000CAAA8  7E FB C8 2E */	lwzx r23, r27, r25
/* 800CFBAC 000CAAAC  48 02 1D 15 */	bl OSDisableInterrupts
/* 800CFBB0 000CAAB0  82 D7 08 BC */	lwz r22, 0x8bc(r23)
/* 800CFBB4 000CAAB4  8A F7 08 C3 */	lbz r23, 0x8c3(r23)
/* 800CFBB8 000CAAB8  48 02 1D 31 */	bl OSRestoreInterrupts
/* 800CFBBC 000CAABC  2C 16 FF FF */	cmpwi r22, -1
/* 800CFBC0 000CAAC0  41 82 00 0C */	beq lbl_800CFBCC
/* 800CFBC4 000CAAC4  7E E3 07 74 */	extsb r3, r23
/* 800CFBC8 000CAAC8  48 03 33 45 */	bl _WUDGetQueuedSize
lbl_800CFBCC:
/* 800CFBCC 000CAACC  7E DB C8 2E */	lwzx r22, r27, r25
/* 800CFBD0 000CAAD0  48 02 1C F1 */	bl OSDisableInterrupts
/* 800CFBD4 000CAAD4  82 F6 08 BC */	lwz r23, 0x8bc(r22)
/* 800CFBD8 000CAAD8  8A D6 08 C3 */	lbz r22, 0x8c3(r22)
/* 800CFBDC 000CAADC  48 02 1D 0D */	bl OSRestoreInterrupts
/* 800CFBE0 000CAAE0  2C 17 FF FF */	cmpwi r23, -1
/* 800CFBE4 000CAAE4  40 82 00 0C */	bne lbl_800CFBF0
/* 800CFBE8 000CAAE8  3B 60 00 00 */	li r27, 0
/* 800CFBEC 000CAAEC  48 00 00 10 */	b lbl_800CFBFC
lbl_800CFBF0:
/* 800CFBF0 000CAAF0  7E C3 07 74 */	extsb r3, r22
/* 800CFBF4 000CAAF4  48 03 33 75 */	bl _WUDGetNotAckedSize
/* 800CFBF8 000CAAF8  7C 7B 1B 78 */	mr r27, r3
lbl_800CFBFC:
/* 800CFBFC 000CAAFC  8A DE 08 CF */	lbz r22, 0x8cf(r30)
/* 800CFC00 000CAB00  48 03 33 C5 */	bl _WUDGetLinkNumber
/* 800CFC04 000CAB04  7C 7E 1B 78 */	mr r30, r3
/* 800CFC08 000CAB08  7F E3 FB 78 */	mr r3, r31
/* 800CFC0C 000CAB0C  48 02 1C DD */	bl OSRestoreInterrupts
/* 800CFC10 000CAB10  2C 1D 00 00 */	cmpwi r29, 0
/* 800CFC14 000CAB14  40 82 00 44 */	bne lbl_800CFC58
/* 800CFC18 000CAB18  57 60 04 3E */	clrlwi r0, r27, 0x10
/* 800CFC1C 000CAB1C  28 00 00 03 */	cmplwi r0, 3
/* 800CFC20 000CAB20  41 81 00 38 */	bgt lbl_800CFC58
/* 800CFC24 000CAB24  57 44 06 3E */	clrlwi r4, r26, 0x18
/* 800CFC28 000CAB28  28 04 00 0A */	cmplwi r4, 0xa
/* 800CFC2C 000CAB2C  41 82 00 2C */	beq lbl_800CFC58
/* 800CFC30 000CAB30  57 C3 0D FC */	rlwinm r3, r30, 1, 0x17, 0x1e
/* 800CFC34 000CAB34  38 03 00 02 */	addi r0, r3, 2
/* 800CFC38 000CAB38  7C 04 00 00 */	cmpw r4, r0
/* 800CFC3C 000CAB3C  40 80 00 1C */	bge lbl_800CFC58
/* 800CFC40 000CAB40  28 1C 00 FF */	cmplwi r28, 0xff
/* 800CFC44 000CAB44  41 82 00 14 */	beq lbl_800CFC58
/* 800CFC48 000CAB48  2C 18 00 15 */	cmpwi r24, 0x15
/* 800CFC4C 000CAB4C  40 80 00 0C */	bge lbl_800CFC58
/* 800CFC50 000CAB50  28 16 00 01 */	cmplwi r22, 1
/* 800CFC54 000CAB54  41 80 00 0C */	blt lbl_800CFC60
lbl_800CFC58:
/* 800CFC58 000CAB58  38 60 00 01 */	li r3, 1
/* 800CFC5C 000CAB5C  48 00 00 08 */	b lbl_800CFC64
lbl_800CFC60:
/* 800CFC60 000CAB60  38 60 00 00 */	li r3, 0
lbl_800CFC64:
/* 800CFC64 000CAB64  39 61 00 30 */	addi r11, r1, 0x30
/* 800CFC68 000CAB68  4B FE 21 15 */	bl _restgpr_22
/* 800CFC6C 000CAB6C  80 01 00 34 */	lwz r0, 0x34(r1)
/* 800CFC70 000CAB70  7C 08 03 A6 */	mtlr r0
/* 800CFC74 000CAB74  38 21 00 30 */	addi r1, r1, 0x30
/* 800CFC78 000CAB78  4E 80 00 20 */	blr 

.global WPADCanSendStreamData
WPADCanSendStreamData:
/* 800CFC7C 000CAB7C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800CFC80 000CAB80  7C 08 02 A6 */	mflr r0
/* 800CFC84 000CAB84  3C 80 80 41 */	lis r4, _wpdcb@ha
/* 800CFC88 000CAB88  90 01 00 24 */	stw r0, 0x24(r1)
/* 800CFC8C 000CAB8C  54 60 10 3A */	slwi r0, r3, 2
/* 800CFC90 000CAB90  38 84 F6 30 */	addi r4, r4, _wpdcb@l
/* 800CFC94 000CAB94  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800CFC98 000CAB98  93 C1 00 18 */	stw r30, 0x18(r1)
/* 800CFC9C 000CAB9C  93 A1 00 14 */	stw r29, 0x14(r1)
/* 800CFCA0 000CABA0  7C 7D 1B 78 */	mr r29, r3
/* 800CFCA4 000CABA4  7F E4 00 2E */	lwzx r31, r4, r0
/* 800CFCA8 000CABA8  48 02 1C 19 */	bl OSDisableInterrupts
/* 800CFCAC 000CABAC  83 DF 08 BC */	lwz r30, 0x8bc(r31)
/* 800CFCB0 000CABB0  83 FF 08 DC */	lwz r31, 0x8dc(r31)
/* 800CFCB4 000CABB4  48 02 1C 35 */	bl OSRestoreInterrupts
/* 800CFCB8 000CABB8  2C 1E FF FF */	cmpwi r30, -1
/* 800CFCBC 000CABBC  41 82 00 1C */	beq lbl_800CFCD8
/* 800CFCC0 000CABC0  2C 1F 00 00 */	cmpwi r31, 0
/* 800CFCC4 000CABC4  41 82 00 14 */	beq lbl_800CFCD8
/* 800CFCC8 000CABC8  7F A3 EB 78 */	mr r3, r29
/* 800CFCCC 000CABCC  4B FF FE 79 */	bl IsBusyStream
/* 800CFCD0 000CABD0  2C 03 00 00 */	cmpwi r3, 0
/* 800CFCD4 000CABD4  41 82 00 0C */	beq lbl_800CFCE0
lbl_800CFCD8:
/* 800CFCD8 000CABD8  38 60 00 00 */	li r3, 0
/* 800CFCDC 000CABDC  48 00 00 08 */	b lbl_800CFCE4
lbl_800CFCE0:
/* 800CFCE0 000CABE0  38 60 00 01 */	li r3, 1
lbl_800CFCE4:
/* 800CFCE4 000CABE4  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800CFCE8 000CABE8  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800CFCEC 000CABEC  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 800CFCF0 000CABF0  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 800CFCF4 000CABF4  7C 08 03 A6 */	mtlr r0
/* 800CFCF8 000CABF8  38 21 00 20 */	addi r1, r1, 0x20
/* 800CFCFC 000CABFC  4E 80 00 20 */	blr 

.global WPADSendStreamData
WPADSendStreamData:
/* 800CFD00 000CAC00  94 21 FF 80 */	stwu r1, -0x80(r1)
/* 800CFD04 000CAC04  7C 08 02 A6 */	mflr r0
/* 800CFD08 000CAC08  90 01 00 84 */	stw r0, 0x84(r1)
/* 800CFD0C 000CAC0C  39 61 00 80 */	addi r11, r1, 0x80
/* 800CFD10 000CAC10  4B FE 20 31 */	bl _savegpr_26
/* 800CFD14 000CAC14  3C C0 80 41 */	lis r6, _wpdcb@ha
/* 800CFD18 000CAC18  54 60 10 3A */	slwi r0, r3, 2
/* 800CFD1C 000CAC1C  38 C6 F6 30 */	addi r6, r6, _wpdcb@l
/* 800CFD20 000CAC20  7C 7A 1B 78 */	mr r26, r3
/* 800CFD24 000CAC24  7F E6 00 2E */	lwzx r31, r6, r0
/* 800CFD28 000CAC28  7C 9B 23 78 */	mr r27, r4
/* 800CFD2C 000CAC2C  7C BC 2B 78 */	mr r28, r5
/* 800CFD30 000CAC30  48 02 1B 91 */	bl OSDisableInterrupts
/* 800CFD34 000CAC34  83 DF 08 BC */	lwz r30, 0x8bc(r31)
/* 800CFD38 000CAC38  83 BF 08 DC */	lwz r29, 0x8dc(r31)
/* 800CFD3C 000CAC3C  48 02 1B AD */	bl OSRestoreInterrupts
/* 800CFD40 000CAC40  2C 1E FF FF */	cmpwi r30, -1
/* 800CFD44 000CAC44  40 82 00 0C */	bne lbl_800CFD50
/* 800CFD48 000CAC48  38 60 FF FF */	li r3, -1
/* 800CFD4C 000CAC4C  48 00 01 AC */	b lbl_800CFEF8
lbl_800CFD50:
/* 800CFD50 000CAC50  2C 1D 00 00 */	cmpwi r29, 0
/* 800CFD54 000CAC54  40 82 00 0C */	bne lbl_800CFD60
/* 800CFD58 000CAC58  38 60 FF FE */	li r3, -2
/* 800CFD5C 000CAC5C  48 00 01 9C */	b lbl_800CFEF8
lbl_800CFD60:
/* 800CFD60 000CAC60  7F 43 D3 78 */	mr r3, r26
/* 800CFD64 000CAC64  4B FF FD E1 */	bl IsBusyStream
/* 800CFD68 000CAC68  2C 03 00 00 */	cmpwi r3, 0
/* 800CFD6C 000CAC6C  41 82 00 0C */	beq lbl_800CFD78
/* 800CFD70 000CAC70  38 60 FF FE */	li r3, -2
/* 800CFD74 000CAC74  48 00 01 84 */	b lbl_800CFEF8
lbl_800CFD78:
/* 800CFD78 000CAC78  57 86 1E 38 */	rlwinm r6, r28, 3, 0x18, 0x1c
/* 800CFD7C 000CAC7C  38 60 00 18 */	li r3, 0x18
/* 800CFD80 000CAC80  38 E0 00 15 */	li r7, 0x15
/* 800CFD84 000CAC84  38 00 00 00 */	li r0, 0
/* 800CFD88 000CAC88  90 61 00 08 */	stw r3, 8(r1)
/* 800CFD8C 000CAC8C  7F 64 DB 78 */	mr r4, r27
/* 800CFD90 000CAC90  7F 85 E3 78 */	mr r5, r28
/* 800CFD94 000CAC94  38 61 00 0D */	addi r3, r1, 0xd
/* 800CFD98 000CAC98  B0 E1 00 22 */	sth r7, 0x22(r1)
/* 800CFD9C 000CAC9C  98 C1 00 0C */	stb r6, 0xc(r1)
/* 800CFDA0 000CACA0  90 01 00 34 */	stw r0, 0x34(r1)
/* 800CFDA4 000CACA4  4B F3 42 5D */	bl memcpy
/* 800CFDA8 000CACA8  83 C1 00 08 */	lwz r30, 8(r1)
/* 800CFDAC 000CACAC  81 81 00 0C */	lwz r12, 0xc(r1)
/* 800CFDB0 000CACB0  81 61 00 10 */	lwz r11, 0x10(r1)
/* 800CFDB4 000CACB4  81 41 00 14 */	lwz r10, 0x14(r1)
/* 800CFDB8 000CACB8  81 21 00 18 */	lwz r9, 0x18(r1)
/* 800CFDBC 000CACBC  81 01 00 1C */	lwz r8, 0x1c(r1)
/* 800CFDC0 000CACC0  80 E1 00 20 */	lwz r7, 0x20(r1)
/* 800CFDC4 000CACC4  80 C1 00 24 */	lwz r6, 0x24(r1)
/* 800CFDC8 000CACC8  80 A1 00 28 */	lwz r5, 0x28(r1)
/* 800CFDCC 000CACCC  80 81 00 2C */	lwz r4, 0x2c(r1)
/* 800CFDD0 000CACD0  80 61 00 30 */	lwz r3, 0x30(r1)
/* 800CFDD4 000CACD4  80 01 00 34 */	lwz r0, 0x34(r1)
/* 800CFDD8 000CACD8  93 C1 00 38 */	stw r30, 0x38(r1)
/* 800CFDDC 000CACDC  91 81 00 3C */	stw r12, 0x3c(r1)
/* 800CFDE0 000CACE0  91 61 00 40 */	stw r11, 0x40(r1)
/* 800CFDE4 000CACE4  91 41 00 44 */	stw r10, 0x44(r1)
/* 800CFDE8 000CACE8  91 21 00 48 */	stw r9, 0x48(r1)
/* 800CFDEC 000CACEC  91 01 00 4C */	stw r8, 0x4c(r1)
/* 800CFDF0 000CACF0  90 E1 00 50 */	stw r7, 0x50(r1)
/* 800CFDF4 000CACF4  90 C1 00 54 */	stw r6, 0x54(r1)
/* 800CFDF8 000CACF8  90 A1 00 58 */	stw r5, 0x58(r1)
/* 800CFDFC 000CACFC  90 81 00 5C */	stw r4, 0x5c(r1)
/* 800CFE00 000CAD00  90 61 00 60 */	stw r3, 0x60(r1)
/* 800CFE04 000CAD04  90 01 00 64 */	stw r0, 0x64(r1)
/* 800CFE08 000CAD08  48 02 1A B9 */	bl OSDisableInterrupts
/* 800CFE0C 000CAD0C  7C 7E 1B 78 */	mr r30, r3
/* 800CFE10 000CAD10  48 02 1A B1 */	bl OSDisableInterrupts
/* 800CFE14 000CAD14  88 9F 01 60 */	lbz r4, 0x160(r31)
/* 800CFE18 000CAD18  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CFE1C 000CAD1C  7C 04 00 50 */	subf r0, r4, r0
/* 800CFE20 000CAD20  7C 1D 07 75 */	extsb. r29, r0
/* 800CFE24 000CAD24  40 80 00 10 */	bge lbl_800CFE34
/* 800CFE28 000CAD28  80 1F 01 68 */	lwz r0, 0x168(r31)
/* 800CFE2C 000CAD2C  7C 1D 02 14 */	add r0, r29, r0
/* 800CFE30 000CAD30  7C 1D 07 74 */	extsb r29, r0
lbl_800CFE34:
/* 800CFE34 000CAD34  48 02 1A B5 */	bl OSRestoreInterrupts
/* 800CFE38 000CAD38  80 7F 01 68 */	lwz r3, 0x168(r31)
/* 800CFE3C 000CAD3C  38 03 FF FF */	addi r0, r3, -1
/* 800CFE40 000CAD40  7C 00 E8 40 */	cmplw r0, r29
/* 800CFE44 000CAD44  40 82 00 14 */	bne lbl_800CFE58
/* 800CFE48 000CAD48  7F C3 F3 78 */	mr r3, r30
/* 800CFE4C 000CAD4C  48 02 1A 9D */	bl OSRestoreInterrupts
/* 800CFE50 000CAD50  38 00 00 00 */	li r0, 0
/* 800CFE54 000CAD54  48 00 00 7C */	b lbl_800CFED0
lbl_800CFE58:
/* 800CFE58 000CAD58  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CFE5C 000CAD5C  38 80 00 00 */	li r4, 0
/* 800CFE60 000CAD60  80 7F 01 64 */	lwz r3, 0x164(r31)
/* 800CFE64 000CAD64  38 A0 00 30 */	li r5, 0x30
/* 800CFE68 000CAD68  7C 00 07 74 */	extsb r0, r0
/* 800CFE6C 000CAD6C  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CFE70 000CAD70  7C 63 02 14 */	add r3, r3, r0
/* 800CFE74 000CAD74  4B F3 42 91 */	bl memset
/* 800CFE78 000CAD78  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CFE7C 000CAD7C  38 81 00 38 */	addi r4, r1, 0x38
/* 800CFE80 000CAD80  80 7F 01 64 */	lwz r3, 0x164(r31)
/* 800CFE84 000CAD84  38 A0 00 30 */	li r5, 0x30
/* 800CFE88 000CAD88  7C 00 07 74 */	extsb r0, r0
/* 800CFE8C 000CAD8C  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800CFE90 000CAD90  7C 63 02 14 */	add r3, r3, r0
/* 800CFE94 000CAD94  4B F3 41 6D */	bl memcpy
/* 800CFE98 000CAD98  88 1F 01 61 */	lbz r0, 0x161(r31)
/* 800CFE9C 000CAD9C  7F C3 F3 78 */	mr r3, r30
/* 800CFEA0 000CADA0  80 9F 01 68 */	lwz r4, 0x168(r31)
/* 800CFEA4 000CADA4  7C 06 07 74 */	extsb r6, r0
/* 800CFEA8 000CADA8  38 84 FF FF */	addi r4, r4, -1
/* 800CFEAC 000CADAC  7C A4 30 50 */	subf r5, r4, r6
/* 800CFEB0 000CADB0  38 06 00 01 */	addi r0, r6, 1
/* 800CFEB4 000CADB4  7C 86 20 50 */	subf r4, r6, r4
/* 800CFEB8 000CADB8  7C A4 20 F8 */	nor r4, r5, r4
/* 800CFEBC 000CADBC  7C 84 FE 70 */	srawi r4, r4, 0x1f
/* 800CFEC0 000CADC0  7C 00 20 78 */	andc r0, r0, r4
/* 800CFEC4 000CADC4  98 1F 01 61 */	stb r0, 0x161(r31)
/* 800CFEC8 000CADC8  48 02 1A 21 */	bl OSRestoreInterrupts
/* 800CFECC 000CADCC  38 00 00 01 */	li r0, 1
lbl_800CFED0:
/* 800CFED0 000CADD0  2C 00 00 00 */	cmpwi r0, 0
/* 800CFED4 000CADD4  40 82 00 0C */	bne lbl_800CFEE0
/* 800CFED8 000CADD8  38 60 FF FE */	li r3, -2
/* 800CFEDC 000CADDC  48 00 00 1C */	b lbl_800CFEF8
lbl_800CFEE0:
/* 800CFEE0 000CADE0  48 02 19 E1 */	bl OSDisableInterrupts
/* 800CFEE4 000CADE4  88 9F 08 CF */	lbz r4, 0x8cf(r31)
/* 800CFEE8 000CADE8  38 04 00 01 */	addi r0, r4, 1
/* 800CFEEC 000CADEC  98 1F 08 CF */	stb r0, 0x8cf(r31)
/* 800CFEF0 000CADF0  48 02 19 F9 */	bl OSRestoreInterrupts
/* 800CFEF4 000CADF4  38 60 00 00 */	li r3, 0
lbl_800CFEF8:
/* 800CFEF8 000CADF8  39 61 00 80 */	addi r11, r1, 0x80
/* 800CFEFC 000CADFC  4B FE 1E 91 */	bl _restgpr_26
/* 800CFF00 000CAE00  80 01 00 84 */	lwz r0, 0x84(r1)
/* 800CFF04 000CAE04  7C 08 03 A6 */	mtlr r0
/* 800CFF08 000CAE08  38 21 00 80 */	addi r1, r1, 0x80
/* 800CFF0C 000CAE0C  4E 80 00 20 */	blr 

.global WPADGetDpdSensitivity
WPADGetDpdSensitivity:
/* 800CFF10 000CAE10  88 6D 9A 79 */	lbz r3, _dpdSensitivity-_SDA_BASE_(r13)
/* 800CFF14 000CAE14  4E 80 00 20 */	blr 

# Not sure what this is.
# WiiBrew lists 0xCD0000C0 as the disc slot LED register?
# IDK why WPAD would touch that.
.global func_800CFF18
func_800CFF18:
/* 800CFF18 000CAE18  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800CFF1C 000CAE1C  7C 08 02 A6 */	mflr r0
/* 800CFF20 000CAE20  90 01 00 14 */	stw r0, 0x14(r1)
/* 800CFF24 000CAE24  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800CFF28 000CAE28  7C 7F 1B 78 */	mr r31, r3
/* 800CFF2C 000CAE2C  48 02 19 95 */	bl OSDisableInterrupts
/* 800CFF30 000CAE30  3C 80 CD 00 */	lis r4, 0xCD0000C0@ha
/* 800CFF34 000CAE34  2C 1F 00 00 */	cmpwi r31, 0
/* 800CFF38 000CAE38  80 A4 00 C0 */	lwz r5, 0xCD0000C0@l(r4)
/* 800CFF3C 000CAE3C  54 A0 06 2C */	rlwinm r0, r5, 0, 0x18, 0x16
/* 800CFF40 000CAE40  41 82 00 08 */	beq lbl_800CFF48
/* 800CFF44 000CAE44  60 A0 01 00 */	ori r0, r5, 0x100
lbl_800CFF48:
/* 800CFF48 000CAE48  3C 80 CD 00 */	lis r4, 0xCD0000C0@ha
/* 800CFF4C 000CAE4C  54 BF C7 FE */	rlwinm r31, r5, 0x18, 0x1f, 0x1f
/* 800CFF50 000CAE50  90 04 00 C0 */	stw r0, 0xCD0000C0@l(r4)
/* 800CFF54 000CAE54  48 02 19 95 */	bl OSRestoreInterrupts
/* 800CFF58 000CAE58  7F E3 FB 78 */	mr r3, r31
/* 800CFF5C 000CAE5C  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 800CFF60 000CAE60  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800CFF64 000CAE64  7C 08 03 A6 */	mtlr r0
/* 800CFF68 000CAE68  38 21 00 10 */	addi r1, r1, 0x10
/* 800CFF6C 000CAE6C  4E 80 00 20 */	blr 

.global WPADIsDpdEnabled
WPADIsDpdEnabled:
/* 800CFF70 000CAE70  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800CFF74 000CAE74  7C 08 02 A6 */	mflr r0
/* 800CFF78 000CAE78  3C 80 80 41 */	lis r4, _wpdcb@ha
/* 800CFF7C 000CAE7C  90 01 00 14 */	stw r0, 0x14(r1)
/* 800CFF80 000CAE80  54 60 10 3A */	slwi r0, r3, 2
/* 800CFF84 000CAE84  38 84 F6 30 */	addi r4, r4, _wpdcb@l
/* 800CFF88 000CAE88  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800CFF8C 000CAE8C  7F E4 00 2E */	lwzx r31, r4, r0
/* 800CFF90 000CAE90  48 02 19 31 */	bl OSDisableInterrupts
/* 800CFF94 000CAE94  83 FF 08 38 */	lwz r31, 0x838(r31)
/* 800CFF98 000CAE98  48 02 19 51 */	bl OSRestoreInterrupts
/* 800CFF9C 000CAE9C  7F E3 FB 78 */	mr r3, r31
/* 800CFFA0 000CAEA0  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 800CFFA4 000CAEA4  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800CFFA8 000CAEA8  7C 08 03 A6 */	mtlr r0
/* 800CFFAC 000CAEAC  38 21 00 10 */	addi r1, r1, 0x10
/* 800CFFB0 000CAEB0  4E 80 00 20 */	blr 
lbl_800CFFB4:
/* 800CFFB4 000CAEB4  3C 80 80 41 */	lis r4, _wpdcb@ha
/* 800CFFB8 000CAEB8  54 60 10 3A */	slwi r0, r3, 2
/* 800CFFBC 000CAEBC  38 84 F6 30 */	addi r4, r4, _wpdcb@l
/* 800CFFC0 000CAEC0  7C 84 00 2E */	lwzx r4, r4, r0
/* 800CFFC4 000CAEC4  88 04 08 CC */	lbz r0, 0x8cc(r4)
/* 800CFFC8 000CAEC8  98 04 08 CB */	stb r0, 0x8cb(r4)
/* 800CFFCC 000CAECC  88 64 08 CC */	lbz r3, 0x8cc(r4)
/* 800CFFD0 000CAED0  7C 03 00 D0 */	neg r0, r3
/* 800CFFD4 000CAED4  7C 00 1B 78 */	or r0, r0, r3
/* 800CFFD8 000CAED8  54 00 0F FE */	srwi r0, r0, 0x1f
/* 800CFFDC 000CAEDC  90 04 08 38 */	stw r0, 0x838(r4)
/* 800CFFE0 000CAEE0  4E 80 00 20 */	blr 

.global WPADControlDpd
WPADControlDpd:
/* 800CFFE4 000CAEE4  94 21 FB 90 */	stwu r1, -0x470(r1)
/* 800CFFE8 000CAEE8  7C 08 02 A6 */	mflr r0
/* 800CFFEC 000CAEEC  90 01 04 74 */	stw r0, 0x474(r1)
/* 800CFFF0 000CAEF0  39 61 04 70 */	addi r11, r1, 0x470
/* 800CFFF4 000CAEF4  4B FE 1D 45 */	bl _savegpr_24
/* 800CFFF8 000CAEF8  3C C0 80 41 */	lis r6, _wpdcb@ha
/* 800CFFFC 000CAEFC  54 60 10 3A */	slwi r0, r3, 2
/* 800D0000 000CAF00  38 C6 F6 30 */	addi r6, r6, _wpdcb@l
/* 800D0004 000CAF04  7C 7F 1B 78 */	mr r31, r3
/* 800D0008 000CAF08  7F A6 00 2E */	lwzx r29, r6, r0
/* 800D000C 000CAF0C  7C 9B 23 78 */	mr r27, r4
/* 800D0010 000CAF10  7C BC 2B 78 */	mr r28, r5
/* 800D0014 000CAF14  48 02 18 AD */	bl OSDisableInterrupts
/* 800D0018 000CAF18  83 5D 08 38 */	lwz r26, 0x838(r29)
/* 800D001C 000CAF1C  8B 3D 08 CC */	lbz r25, 0x8cc(r29)
/* 800D0020 000CAF20  83 1D 08 BC */	lwz r24, 0x8bc(r29)
/* 800D0024 000CAF24  83 DD 08 DC */	lwz r30, 0x8dc(r29)
/* 800D0028 000CAF28  48 02 18 C1 */	bl OSRestoreInterrupts
/* 800D002C 000CAF2C  2C 18 FF FF */	cmpwi r24, -1
/* 800D0030 000CAF30  41 82 0F F8 */	beq lbl_800D1028
/* 800D0034 000CAF34  2C 1E 00 00 */	cmpwi r30, 0
/* 800D0038 000CAF38  40 82 00 0C */	bne lbl_800D0044
/* 800D003C 000CAF3C  3B 00 FF FE */	li r24, -2
/* 800D0040 000CAF40  48 00 0F E8 */	b lbl_800D1028
lbl_800D0044:
/* 800D0044 000CAF44  2C 1B 00 00 */	cmpwi r27, 0
/* 800D0048 000CAF48  40 82 04 20 */	bne lbl_800D0468
/* 800D004C 000CAF4C  2C 1A 00 00 */	cmpwi r26, 0
/* 800D0050 000CAF50  40 82 00 0C */	bne lbl_800D005C
/* 800D0054 000CAF54  3B 00 00 00 */	li r24, 0
/* 800D0058 000CAF58  48 00 0F D0 */	b lbl_800D1028
lbl_800D005C:
/* 800D005C 000CAF5C  48 02 18 65 */	bl OSDisableInterrupts
/* 800D0060 000CAF60  7C 7E 1B 78 */	mr r30, r3
/* 800D0064 000CAF64  48 02 18 5D */	bl OSDisableInterrupts
/* 800D0068 000CAF68  88 9D 01 60 */	lbz r4, 0x160(r29)
/* 800D006C 000CAF6C  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800D0070 000CAF70  7C 04 00 50 */	subf r0, r4, r0
/* 800D0074 000CAF74  7C 1A 07 75 */	extsb. r26, r0
/* 800D0078 000CAF78  40 80 00 10 */	bge lbl_800D0088
/* 800D007C 000CAF7C  80 1D 01 68 */	lwz r0, 0x168(r29)
/* 800D0080 000CAF80  7C 1A 02 14 */	add r0, r26, r0
/* 800D0084 000CAF84  7C 1A 07 74 */	extsb r26, r0
lbl_800D0088:
/* 800D0088 000CAF88  48 02 18 61 */	bl OSRestoreInterrupts
/* 800D008C 000CAF8C  80 7D 01 68 */	lwz r3, 0x168(r29)
/* 800D0090 000CAF90  38 9A 00 03 */	addi r4, r26, 3
/* 800D0094 000CAF94  38 03 FF FF */	addi r0, r3, -1
/* 800D0098 000CAF98  7C 04 00 40 */	cmplw r4, r0
/* 800D009C 000CAF9C  41 81 03 BC */	bgt lbl_800D0458
/* 800D00A0 000CAFA0  39 80 00 00 */	li r12, 0
/* 800D00A4 000CAFA4  38 00 00 01 */	li r0, 1
/* 800D00A8 000CAFA8  B0 01 04 02 */	sth r0, 0x402(r1)
/* 800D00AC 000CAFAC  3B E0 00 13 */	li r31, 0x13
/* 800D00B0 000CAFB0  81 41 03 F0 */	lwz r10, 0x3f0(r1)
/* 800D00B4 000CAFB4  9B 7D 08 CC */	stb r27, 0x8cc(r29)
/* 800D00B8 000CAFB8  81 21 03 F4 */	lwz r9, 0x3f4(r1)
/* 800D00BC 000CAFBC  99 81 03 EC */	stb r12, 0x3ec(r1)
/* 800D00C0 000CAFC0  81 01 03 F8 */	lwz r8, 0x3f8(r1)
/* 800D00C4 000CAFC4  81 61 03 EC */	lwz r11, 0x3ec(r1)
/* 800D00C8 000CAFC8  80 E1 03 FC */	lwz r7, 0x3fc(r1)
/* 800D00CC 000CAFCC  80 C1 04 00 */	lwz r6, 0x400(r1)
/* 800D00D0 000CAFD0  80 A1 04 04 */	lwz r5, 0x404(r1)
/* 800D00D4 000CAFD4  80 81 04 08 */	lwz r4, 0x408(r1)
/* 800D00D8 000CAFD8  80 61 04 0C */	lwz r3, 0x40c(r1)
/* 800D00DC 000CAFDC  80 01 04 10 */	lwz r0, 0x410(r1)
/* 800D00E0 000CAFE0  93 E1 03 E8 */	stw r31, 0x3e8(r1)
/* 800D00E4 000CAFE4  91 81 04 14 */	stw r12, 0x414(r1)
/* 800D00E8 000CAFE8  93 E1 04 18 */	stw r31, 0x418(r1)
/* 800D00EC 000CAFEC  91 61 04 1C */	stw r11, 0x41c(r1)
/* 800D00F0 000CAFF0  91 41 04 20 */	stw r10, 0x420(r1)
/* 800D00F4 000CAFF4  91 21 04 24 */	stw r9, 0x424(r1)
/* 800D00F8 000CAFF8  91 01 04 28 */	stw r8, 0x428(r1)
/* 800D00FC 000CAFFC  90 E1 04 2C */	stw r7, 0x42c(r1)
/* 800D0100 000CB000  90 C1 04 30 */	stw r6, 0x430(r1)
/* 800D0104 000CB004  90 A1 04 34 */	stw r5, 0x434(r1)
/* 800D0108 000CB008  90 81 04 38 */	stw r4, 0x438(r1)
/* 800D010C 000CB00C  90 61 04 3C */	stw r3, 0x43c(r1)
/* 800D0110 000CB010  90 01 04 40 */	stw r0, 0x440(r1)
/* 800D0114 000CB014  91 81 04 44 */	stw r12, 0x444(r1)
/* 800D0118 000CB018  48 02 17 A9 */	bl OSDisableInterrupts
/* 800D011C 000CB01C  7C 7F 1B 78 */	mr r31, r3
/* 800D0120 000CB020  48 02 17 A1 */	bl OSDisableInterrupts
/* 800D0124 000CB024  88 9D 01 60 */	lbz r4, 0x160(r29)
/* 800D0128 000CB028  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800D012C 000CB02C  7C 04 00 50 */	subf r0, r4, r0
/* 800D0130 000CB030  7C 1A 07 75 */	extsb. r26, r0
/* 800D0134 000CB034  40 80 00 10 */	bge lbl_800D0144
/* 800D0138 000CB038  80 1D 01 68 */	lwz r0, 0x168(r29)
/* 800D013C 000CB03C  7C 1A 02 14 */	add r0, r26, r0
/* 800D0140 000CB040  7C 1A 07 74 */	extsb r26, r0
lbl_800D0144:
/* 800D0144 000CB044  48 02 17 A5 */	bl OSRestoreInterrupts
/* 800D0148 000CB048  80 7D 01 68 */	lwz r3, 0x168(r29)
/* 800D014C 000CB04C  38 03 FF FF */	addi r0, r3, -1
/* 800D0150 000CB050  7C 00 D0 40 */	cmplw r0, r26
/* 800D0154 000CB054  40 82 00 10 */	bne lbl_800D0164
/* 800D0158 000CB058  7F E3 FB 78 */	mr r3, r31
/* 800D015C 000CB05C  48 02 17 8D */	bl OSRestoreInterrupts
/* 800D0160 000CB060  48 00 00 78 */	b lbl_800D01D8
lbl_800D0164:
/* 800D0164 000CB064  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800D0168 000CB068  38 80 00 00 */	li r4, 0
/* 800D016C 000CB06C  80 7D 01 64 */	lwz r3, 0x164(r29)
/* 800D0170 000CB070  38 A0 00 30 */	li r5, 0x30
/* 800D0174 000CB074  7C 00 07 74 */	extsb r0, r0
/* 800D0178 000CB078  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800D017C 000CB07C  7C 63 02 14 */	add r3, r3, r0
/* 800D0180 000CB080  4B F3 3F 85 */	bl memset
/* 800D0184 000CB084  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800D0188 000CB088  38 81 04 18 */	addi r4, r1, 0x418
/* 800D018C 000CB08C  80 7D 01 64 */	lwz r3, 0x164(r29)
/* 800D0190 000CB090  38 A0 00 30 */	li r5, 0x30
/* 800D0194 000CB094  7C 00 07 74 */	extsb r0, r0
/* 800D0198 000CB098  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800D019C 000CB09C  7C 63 02 14 */	add r3, r3, r0
/* 800D01A0 000CB0A0  4B F3 3E 61 */	bl memcpy
/* 800D01A4 000CB0A4  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800D01A8 000CB0A8  7F E3 FB 78 */	mr r3, r31
/* 800D01AC 000CB0AC  80 9D 01 68 */	lwz r4, 0x168(r29)
/* 800D01B0 000CB0B0  7C 06 07 74 */	extsb r6, r0
/* 800D01B4 000CB0B4  38 84 FF FF */	addi r4, r4, -1
/* 800D01B8 000CB0B8  7C A4 30 50 */	subf r5, r4, r6
/* 800D01BC 000CB0BC  38 06 00 01 */	addi r0, r6, 1
/* 800D01C0 000CB0C0  7C 86 20 50 */	subf r4, r6, r4
/* 800D01C4 000CB0C4  7C A4 20 F8 */	nor r4, r5, r4
/* 800D01C8 000CB0C8  7C 84 FE 70 */	srawi r4, r4, 0x1f
/* 800D01CC 000CB0CC  7C 00 20 78 */	andc r0, r0, r4
/* 800D01D0 000CB0D0  98 1D 01 61 */	stb r0, 0x161(r29)
/* 800D01D4 000CB0D4  48 02 17 15 */	bl OSRestoreInterrupts
lbl_800D01D8:
/* 800D01D8 000CB0D8  38 60 00 01 */	li r3, 1
/* 800D01DC 000CB0DC  38 00 00 00 */	li r0, 0
/* 800D01E0 000CB0E0  B0 61 03 A2 */	sth r3, 0x3a2(r1)
/* 800D01E4 000CB0E4  3B 60 00 1A */	li r27, 0x1a
/* 800D01E8 000CB0E8  81 41 03 90 */	lwz r10, 0x390(r1)
/* 800D01EC 000CB0EC  3D 80 80 0D */	lis r12, lbl_800CFFB4@ha
/* 800D01F0 000CB0F0  98 01 03 8C */	stb r0, 0x38c(r1)
/* 800D01F4 000CB0F4  39 8C FF B4 */	addi r12, r12, lbl_800CFFB4@l
/* 800D01F8 000CB0F8  81 21 03 94 */	lwz r9, 0x394(r1)
/* 800D01FC 000CB0FC  81 61 03 8C */	lwz r11, 0x38c(r1)
/* 800D0200 000CB100  81 01 03 98 */	lwz r8, 0x398(r1)
/* 800D0204 000CB104  80 E1 03 9C */	lwz r7, 0x39c(r1)
/* 800D0208 000CB108  80 C1 03 A0 */	lwz r6, 0x3a0(r1)
/* 800D020C 000CB10C  80 A1 03 A4 */	lwz r5, 0x3a4(r1)
/* 800D0210 000CB110  80 81 03 A8 */	lwz r4, 0x3a8(r1)
/* 800D0214 000CB114  80 61 03 AC */	lwz r3, 0x3ac(r1)
/* 800D0218 000CB118  80 01 03 B0 */	lwz r0, 0x3b0(r1)
/* 800D021C 000CB11C  93 61 03 88 */	stw r27, 0x388(r1)
/* 800D0220 000CB120  91 81 03 B4 */	stw r12, 0x3b4(r1)
/* 800D0224 000CB124  93 61 03 B8 */	stw r27, 0x3b8(r1)
/* 800D0228 000CB128  91 61 03 BC */	stw r11, 0x3bc(r1)
/* 800D022C 000CB12C  91 41 03 C0 */	stw r10, 0x3c0(r1)
/* 800D0230 000CB130  91 21 03 C4 */	stw r9, 0x3c4(r1)
/* 800D0234 000CB134  91 01 03 C8 */	stw r8, 0x3c8(r1)
/* 800D0238 000CB138  90 E1 03 CC */	stw r7, 0x3cc(r1)
/* 800D023C 000CB13C  90 C1 03 D0 */	stw r6, 0x3d0(r1)
/* 800D0240 000CB140  90 A1 03 D4 */	stw r5, 0x3d4(r1)
/* 800D0244 000CB144  90 81 03 D8 */	stw r4, 0x3d8(r1)
/* 800D0248 000CB148  90 61 03 DC */	stw r3, 0x3dc(r1)
/* 800D024C 000CB14C  90 01 03 E0 */	stw r0, 0x3e0(r1)
/* 800D0250 000CB150  91 81 03 E4 */	stw r12, 0x3e4(r1)
/* 800D0254 000CB154  48 02 16 6D */	bl OSDisableInterrupts
/* 800D0258 000CB158  7C 7F 1B 78 */	mr r31, r3
/* 800D025C 000CB15C  48 02 16 65 */	bl OSDisableInterrupts
/* 800D0260 000CB160  88 9D 01 60 */	lbz r4, 0x160(r29)
/* 800D0264 000CB164  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800D0268 000CB168  7C 04 00 50 */	subf r0, r4, r0
/* 800D026C 000CB16C  7C 1A 07 75 */	extsb. r26, r0
/* 800D0270 000CB170  40 80 00 10 */	bge lbl_800D0280
/* 800D0274 000CB174  80 1D 01 68 */	lwz r0, 0x168(r29)
/* 800D0278 000CB178  7C 1A 02 14 */	add r0, r26, r0
/* 800D027C 000CB17C  7C 1A 07 74 */	extsb r26, r0
lbl_800D0280:
/* 800D0280 000CB180  48 02 16 69 */	bl OSRestoreInterrupts
/* 800D0284 000CB184  80 7D 01 68 */	lwz r3, 0x168(r29)
/* 800D0288 000CB188  38 03 FF FF */	addi r0, r3, -1
/* 800D028C 000CB18C  7C 00 D0 40 */	cmplw r0, r26
/* 800D0290 000CB190  40 82 00 10 */	bne lbl_800D02A0
/* 800D0294 000CB194  7F E3 FB 78 */	mr r3, r31
/* 800D0298 000CB198  48 02 16 51 */	bl OSRestoreInterrupts
/* 800D029C 000CB19C  48 00 00 78 */	b lbl_800D0314
lbl_800D02A0:
/* 800D02A0 000CB1A0  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800D02A4 000CB1A4  38 80 00 00 */	li r4, 0
/* 800D02A8 000CB1A8  80 7D 01 64 */	lwz r3, 0x164(r29)
/* 800D02AC 000CB1AC  38 A0 00 30 */	li r5, 0x30
/* 800D02B0 000CB1B0  7C 00 07 74 */	extsb r0, r0
/* 800D02B4 000CB1B4  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800D02B8 000CB1B8  7C 63 02 14 */	add r3, r3, r0
/* 800D02BC 000CB1BC  4B F3 3E 49 */	bl memset
/* 800D02C0 000CB1C0  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800D02C4 000CB1C4  38 81 03 B8 */	addi r4, r1, 0x3b8
/* 800D02C8 000CB1C8  80 7D 01 64 */	lwz r3, 0x164(r29)
/* 800D02CC 000CB1CC  38 A0 00 30 */	li r5, 0x30
/* 800D02D0 000CB1D0  7C 00 07 74 */	extsb r0, r0
/* 800D02D4 000CB1D4  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800D02D8 000CB1D8  7C 63 02 14 */	add r3, r3, r0
/* 800D02DC 000CB1DC  4B F3 3D 25 */	bl memcpy
/* 800D02E0 000CB1E0  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800D02E4 000CB1E4  7F E3 FB 78 */	mr r3, r31
/* 800D02E8 000CB1E8  80 9D 01 68 */	lwz r4, 0x168(r29)
/* 800D02EC 000CB1EC  7C 06 07 74 */	extsb r6, r0
/* 800D02F0 000CB1F0  38 84 FF FF */	addi r4, r4, -1
/* 800D02F4 000CB1F4  7C A4 30 50 */	subf r5, r4, r6
/* 800D02F8 000CB1F8  38 06 00 01 */	addi r0, r6, 1
/* 800D02FC 000CB1FC  7C 86 20 50 */	subf r4, r6, r4
/* 800D0300 000CB200  7C A4 20 F8 */	nor r4, r5, r4
/* 800D0304 000CB204  7C 84 FE 70 */	srawi r4, r4, 0x1f
/* 800D0308 000CB208  7C 00 20 78 */	andc r0, r0, r4
/* 800D030C 000CB20C  98 1D 01 61 */	stb r0, 0x161(r29)
/* 800D0310 000CB210  48 02 15 D9 */	bl OSRestoreInterrupts
lbl_800D0314:
/* 800D0314 000CB214  39 60 00 00 */	li r11, 0
/* 800D0318 000CB218  38 00 00 01 */	li r0, 1
/* 800D031C 000CB21C  B0 01 03 42 */	sth r0, 0x342(r1)
/* 800D0320 000CB220  39 80 00 15 */	li r12, 0x15
/* 800D0324 000CB224  81 21 03 30 */	lwz r9, 0x330(r1)
/* 800D0328 000CB228  99 61 03 2C */	stb r11, 0x32c(r1)
/* 800D032C 000CB22C  81 01 03 34 */	lwz r8, 0x334(r1)
/* 800D0330 000CB230  81 41 03 2C */	lwz r10, 0x32c(r1)
/* 800D0334 000CB234  80 E1 03 38 */	lwz r7, 0x338(r1)
/* 800D0338 000CB238  80 C1 03 3C */	lwz r6, 0x33c(r1)
/* 800D033C 000CB23C  80 A1 03 40 */	lwz r5, 0x340(r1)
/* 800D0340 000CB240  80 81 03 44 */	lwz r4, 0x344(r1)
/* 800D0344 000CB244  80 61 03 48 */	lwz r3, 0x348(r1)
/* 800D0348 000CB248  80 01 03 4C */	lwz r0, 0x34c(r1)
/* 800D034C 000CB24C  91 81 03 28 */	stw r12, 0x328(r1)
/* 800D0350 000CB250  93 81 03 54 */	stw r28, 0x354(r1)
/* 800D0354 000CB254  91 61 03 50 */	stw r11, 0x350(r1)
/* 800D0358 000CB258  91 81 03 58 */	stw r12, 0x358(r1)
/* 800D035C 000CB25C  91 41 03 5C */	stw r10, 0x35c(r1)
/* 800D0360 000CB260  91 21 03 60 */	stw r9, 0x360(r1)
/* 800D0364 000CB264  91 01 03 64 */	stw r8, 0x364(r1)
/* 800D0368 000CB268  90 E1 03 68 */	stw r7, 0x368(r1)
/* 800D036C 000CB26C  90 C1 03 6C */	stw r6, 0x36c(r1)
/* 800D0370 000CB270  90 A1 03 70 */	stw r5, 0x370(r1)
/* 800D0374 000CB274  90 81 03 74 */	stw r4, 0x374(r1)
/* 800D0378 000CB278  90 61 03 78 */	stw r3, 0x378(r1)
/* 800D037C 000CB27C  90 01 03 7C */	stw r0, 0x37c(r1)
/* 800D0380 000CB280  91 61 03 80 */	stw r11, 0x380(r1)
/* 800D0384 000CB284  93 81 03 84 */	stw r28, 0x384(r1)
/* 800D0388 000CB288  48 02 15 39 */	bl OSDisableInterrupts
/* 800D038C 000CB28C  7C 7F 1B 78 */	mr r31, r3
/* 800D0390 000CB290  48 02 15 31 */	bl OSDisableInterrupts
/* 800D0394 000CB294  88 9D 01 60 */	lbz r4, 0x160(r29)
/* 800D0398 000CB298  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800D039C 000CB29C  7C 04 00 50 */	subf r0, r4, r0
/* 800D03A0 000CB2A0  7C 1A 07 75 */	extsb. r26, r0
/* 800D03A4 000CB2A4  40 80 00 10 */	bge lbl_800D03B4
/* 800D03A8 000CB2A8  80 1D 01 68 */	lwz r0, 0x168(r29)
/* 800D03AC 000CB2AC  7C 1A 02 14 */	add r0, r26, r0
/* 800D03B0 000CB2B0  7C 1A 07 74 */	extsb r26, r0
lbl_800D03B4:
/* 800D03B4 000CB2B4  48 02 15 35 */	bl OSRestoreInterrupts
/* 800D03B8 000CB2B8  80 7D 01 68 */	lwz r3, 0x168(r29)
/* 800D03BC 000CB2BC  38 03 FF FF */	addi r0, r3, -1
/* 800D03C0 000CB2C0  7C 00 D0 40 */	cmplw r0, r26
/* 800D03C4 000CB2C4  40 82 00 10 */	bne lbl_800D03D4
/* 800D03C8 000CB2C8  7F E3 FB 78 */	mr r3, r31
/* 800D03CC 000CB2CC  48 02 15 1D */	bl OSRestoreInterrupts
/* 800D03D0 000CB2D0  48 00 00 78 */	b lbl_800D0448
lbl_800D03D4:
/* 800D03D4 000CB2D4  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800D03D8 000CB2D8  38 80 00 00 */	li r4, 0
/* 800D03DC 000CB2DC  80 7D 01 64 */	lwz r3, 0x164(r29)
/* 800D03E0 000CB2E0  38 A0 00 30 */	li r5, 0x30
/* 800D03E4 000CB2E4  7C 00 07 74 */	extsb r0, r0
/* 800D03E8 000CB2E8  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800D03EC 000CB2EC  7C 63 02 14 */	add r3, r3, r0
/* 800D03F0 000CB2F0  4B F3 3D 15 */	bl memset
/* 800D03F4 000CB2F4  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800D03F8 000CB2F8  38 81 03 58 */	addi r4, r1, 0x358
/* 800D03FC 000CB2FC  80 7D 01 64 */	lwz r3, 0x164(r29)
/* 800D0400 000CB300  38 A0 00 30 */	li r5, 0x30
/* 800D0404 000CB304  7C 00 07 74 */	extsb r0, r0
/* 800D0408 000CB308  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800D040C 000CB30C  7C 63 02 14 */	add r3, r3, r0
/* 800D0410 000CB310  4B F3 3B F1 */	bl memcpy
/* 800D0414 000CB314  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800D0418 000CB318  7F E3 FB 78 */	mr r3, r31
/* 800D041C 000CB31C  80 9D 01 68 */	lwz r4, 0x168(r29)
/* 800D0420 000CB320  7C 06 07 74 */	extsb r6, r0
/* 800D0424 000CB324  38 84 FF FF */	addi r4, r4, -1
/* 800D0428 000CB328  7C A4 30 50 */	subf r5, r4, r6
/* 800D042C 000CB32C  38 06 00 01 */	addi r0, r6, 1
/* 800D0430 000CB330  7C 86 20 50 */	subf r4, r6, r4
/* 800D0434 000CB334  7C A4 20 F8 */	nor r4, r5, r4
/* 800D0438 000CB338  7C 84 FE 70 */	srawi r4, r4, 0x1f
/* 800D043C 000CB33C  7C 00 20 78 */	andc r0, r0, r4
/* 800D0440 000CB340  98 1D 01 61 */	stb r0, 0x161(r29)
/* 800D0444 000CB344  48 02 14 A5 */	bl OSRestoreInterrupts
lbl_800D0448:
/* 800D0448 000CB348  7F C3 F3 78 */	mr r3, r30
/* 800D044C 000CB34C  48 02 14 9D */	bl OSRestoreInterrupts
/* 800D0450 000CB350  38 60 00 00 */	li r3, 0
/* 800D0454 000CB354  48 00 0B F4 */	b lbl_800D1048
lbl_800D0458:
/* 800D0458 000CB358  7F C3 F3 78 */	mr r3, r30
/* 800D045C 000CB35C  3B 00 FF FE */	li r24, -2
/* 800D0460 000CB360  48 02 14 89 */	bl OSRestoreInterrupts
/* 800D0464 000CB364  48 00 0B C4 */	b lbl_800D1028
lbl_800D0468:
/* 800D0468 000CB368  7C 1B C8 40 */	cmplw r27, r25
/* 800D046C 000CB36C  41 82 0B BC */	beq lbl_800D1028
/* 800D0470 000CB370  48 02 14 51 */	bl OSDisableInterrupts
/* 800D0474 000CB374  7C 7E 1B 78 */	mr r30, r3
/* 800D0478 000CB378  48 02 14 49 */	bl OSDisableInterrupts
/* 800D047C 000CB37C  88 9D 01 60 */	lbz r4, 0x160(r29)
/* 800D0480 000CB380  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800D0484 000CB384  7C 04 00 50 */	subf r0, r4, r0
/* 800D0488 000CB388  7C 1A 07 75 */	extsb. r26, r0
/* 800D048C 000CB38C  40 80 00 10 */	bge lbl_800D049C
/* 800D0490 000CB390  80 1D 01 68 */	lwz r0, 0x168(r29)
/* 800D0494 000CB394  7C 1A 02 14 */	add r0, r26, r0
/* 800D0498 000CB398  7C 1A 07 74 */	extsb r26, r0
lbl_800D049C:
/* 800D049C 000CB39C  48 02 14 4D */	bl OSRestoreInterrupts
/* 800D04A0 000CB3A0  80 7D 01 68 */	lwz r3, 0x168(r29)
/* 800D04A4 000CB3A4  38 9A 00 08 */	addi r4, r26, 8
/* 800D04A8 000CB3A8  38 03 FF FF */	addi r0, r3, -1
/* 800D04AC 000CB3AC  7C 04 00 40 */	cmplw r4, r0
/* 800D04B0 000CB3B0  41 81 0B 6C */	bgt lbl_800D101C
/* 800D04B4 000CB3B4  38 60 00 01 */	li r3, 1
/* 800D04B8 000CB3B8  38 00 00 04 */	li r0, 4
/* 800D04BC 000CB3BC  B0 61 02 E2 */	sth r3, 0x2e2(r1)
/* 800D04C0 000CB3C0  3B E0 00 13 */	li r31, 0x13
/* 800D04C4 000CB3C4  39 80 00 00 */	li r12, 0
/* 800D04C8 000CB3C8  81 41 02 D0 */	lwz r10, 0x2d0(r1)
/* 800D04CC 000CB3CC  9B 7D 08 CC */	stb r27, 0x8cc(r29)
/* 800D04D0 000CB3D0  81 21 02 D4 */	lwz r9, 0x2d4(r1)
/* 800D04D4 000CB3D4  98 01 02 CC */	stb r0, 0x2cc(r1)
/* 800D04D8 000CB3D8  81 01 02 D8 */	lwz r8, 0x2d8(r1)
/* 800D04DC 000CB3DC  81 61 02 CC */	lwz r11, 0x2cc(r1)
/* 800D04E0 000CB3E0  80 E1 02 DC */	lwz r7, 0x2dc(r1)
/* 800D04E4 000CB3E4  80 C1 02 E0 */	lwz r6, 0x2e0(r1)
/* 800D04E8 000CB3E8  80 A1 02 E4 */	lwz r5, 0x2e4(r1)
/* 800D04EC 000CB3EC  80 81 02 E8 */	lwz r4, 0x2e8(r1)
/* 800D04F0 000CB3F0  80 61 02 EC */	lwz r3, 0x2ec(r1)
/* 800D04F4 000CB3F4  80 01 02 F0 */	lwz r0, 0x2f0(r1)
/* 800D04F8 000CB3F8  93 E1 02 C8 */	stw r31, 0x2c8(r1)
/* 800D04FC 000CB3FC  91 81 02 F4 */	stw r12, 0x2f4(r1)
/* 800D0500 000CB400  93 E1 02 F8 */	stw r31, 0x2f8(r1)
/* 800D0504 000CB404  91 61 02 FC */	stw r11, 0x2fc(r1)
/* 800D0508 000CB408  91 41 03 00 */	stw r10, 0x300(r1)
/* 800D050C 000CB40C  91 21 03 04 */	stw r9, 0x304(r1)
/* 800D0510 000CB410  91 01 03 08 */	stw r8, 0x308(r1)
/* 800D0514 000CB414  90 E1 03 0C */	stw r7, 0x30c(r1)
/* 800D0518 000CB418  90 C1 03 10 */	stw r6, 0x310(r1)
/* 800D051C 000CB41C  90 A1 03 14 */	stw r5, 0x314(r1)
/* 800D0520 000CB420  90 81 03 18 */	stw r4, 0x318(r1)
/* 800D0524 000CB424  90 61 03 1C */	stw r3, 0x31c(r1)
/* 800D0528 000CB428  90 01 03 20 */	stw r0, 0x320(r1)
/* 800D052C 000CB42C  91 81 03 24 */	stw r12, 0x324(r1)
/* 800D0530 000CB430  48 02 13 91 */	bl OSDisableInterrupts
/* 800D0534 000CB434  7C 7F 1B 78 */	mr r31, r3
/* 800D0538 000CB438  48 02 13 89 */	bl OSDisableInterrupts
/* 800D053C 000CB43C  88 9D 01 60 */	lbz r4, 0x160(r29)
/* 800D0540 000CB440  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800D0544 000CB444  7C 04 00 50 */	subf r0, r4, r0
/* 800D0548 000CB448  7C 1A 07 75 */	extsb. r26, r0
/* 800D054C 000CB44C  40 80 00 10 */	bge lbl_800D055C
/* 800D0550 000CB450  80 1D 01 68 */	lwz r0, 0x168(r29)
/* 800D0554 000CB454  7C 1A 02 14 */	add r0, r26, r0
/* 800D0558 000CB458  7C 1A 07 74 */	extsb r26, r0
lbl_800D055C:
/* 800D055C 000CB45C  48 02 13 8D */	bl OSRestoreInterrupts
/* 800D0560 000CB460  80 7D 01 68 */	lwz r3, 0x168(r29)
/* 800D0564 000CB464  38 03 FF FF */	addi r0, r3, -1
/* 800D0568 000CB468  7C 00 D0 40 */	cmplw r0, r26
/* 800D056C 000CB46C  40 82 00 10 */	bne lbl_800D057C
/* 800D0570 000CB470  7F E3 FB 78 */	mr r3, r31
/* 800D0574 000CB474  48 02 13 75 */	bl OSRestoreInterrupts
/* 800D0578 000CB478  48 00 00 78 */	b lbl_800D05F0
lbl_800D057C:
/* 800D057C 000CB47C  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800D0580 000CB480  38 80 00 00 */	li r4, 0
/* 800D0584 000CB484  80 7D 01 64 */	lwz r3, 0x164(r29)
/* 800D0588 000CB488  38 A0 00 30 */	li r5, 0x30
/* 800D058C 000CB48C  7C 00 07 74 */	extsb r0, r0
/* 800D0590 000CB490  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800D0594 000CB494  7C 63 02 14 */	add r3, r3, r0
/* 800D0598 000CB498  4B F3 3B 6D */	bl memset
/* 800D059C 000CB49C  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800D05A0 000CB4A0  38 81 02 F8 */	addi r4, r1, 0x2f8
/* 800D05A4 000CB4A4  80 7D 01 64 */	lwz r3, 0x164(r29)
/* 800D05A8 000CB4A8  38 A0 00 30 */	li r5, 0x30
/* 800D05AC 000CB4AC  7C 00 07 74 */	extsb r0, r0
/* 800D05B0 000CB4B0  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800D05B4 000CB4B4  7C 63 02 14 */	add r3, r3, r0
/* 800D05B8 000CB4B8  4B F3 3A 49 */	bl memcpy
/* 800D05BC 000CB4BC  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800D05C0 000CB4C0  7F E3 FB 78 */	mr r3, r31
/* 800D05C4 000CB4C4  80 9D 01 68 */	lwz r4, 0x168(r29)
/* 800D05C8 000CB4C8  7C 06 07 74 */	extsb r6, r0
/* 800D05CC 000CB4CC  38 84 FF FF */	addi r4, r4, -1
/* 800D05D0 000CB4D0  7C A4 30 50 */	subf r5, r4, r6
/* 800D05D4 000CB4D4  38 06 00 01 */	addi r0, r6, 1
/* 800D05D8 000CB4D8  7C 86 20 50 */	subf r4, r6, r4
/* 800D05DC 000CB4DC  7C A4 20 F8 */	nor r4, r5, r4
/* 800D05E0 000CB4E0  7C 84 FE 70 */	srawi r4, r4, 0x1f
/* 800D05E4 000CB4E4  7C 00 20 78 */	andc r0, r0, r4
/* 800D05E8 000CB4E8  98 1D 01 61 */	stb r0, 0x161(r29)
/* 800D05EC 000CB4EC  48 02 12 FD */	bl OSRestoreInterrupts
lbl_800D05F0:
/* 800D05F0 000CB4F0  38 60 00 01 */	li r3, 1
/* 800D05F4 000CB4F4  38 00 00 04 */	li r0, 4
/* 800D05F8 000CB4F8  B0 61 02 82 */	sth r3, 0x282(r1)
/* 800D05FC 000CB4FC  3B E0 00 1A */	li r31, 0x1a
/* 800D0600 000CB500  39 80 00 00 */	li r12, 0
/* 800D0604 000CB504  81 41 02 70 */	lwz r10, 0x270(r1)
/* 800D0608 000CB508  98 01 02 6C */	stb r0, 0x26c(r1)
/* 800D060C 000CB50C  81 21 02 74 */	lwz r9, 0x274(r1)
/* 800D0610 000CB510  81 61 02 6C */	lwz r11, 0x26c(r1)
/* 800D0614 000CB514  81 01 02 78 */	lwz r8, 0x278(r1)
/* 800D0618 000CB518  80 E1 02 7C */	lwz r7, 0x27c(r1)
/* 800D061C 000CB51C  80 C1 02 80 */	lwz r6, 0x280(r1)
/* 800D0620 000CB520  80 A1 02 84 */	lwz r5, 0x284(r1)
/* 800D0624 000CB524  80 81 02 88 */	lwz r4, 0x288(r1)
/* 800D0628 000CB528  80 61 02 8C */	lwz r3, 0x28c(r1)
/* 800D062C 000CB52C  80 01 02 90 */	lwz r0, 0x290(r1)
/* 800D0630 000CB530  93 E1 02 68 */	stw r31, 0x268(r1)
/* 800D0634 000CB534  91 81 02 94 */	stw r12, 0x294(r1)
/* 800D0638 000CB538  93 E1 02 98 */	stw r31, 0x298(r1)
/* 800D063C 000CB53C  91 61 02 9C */	stw r11, 0x29c(r1)
/* 800D0640 000CB540  91 41 02 A0 */	stw r10, 0x2a0(r1)
/* 800D0644 000CB544  91 21 02 A4 */	stw r9, 0x2a4(r1)
/* 800D0648 000CB548  91 01 02 A8 */	stw r8, 0x2a8(r1)
/* 800D064C 000CB54C  90 E1 02 AC */	stw r7, 0x2ac(r1)
/* 800D0650 000CB550  90 C1 02 B0 */	stw r6, 0x2b0(r1)
/* 800D0654 000CB554  90 A1 02 B4 */	stw r5, 0x2b4(r1)
/* 800D0658 000CB558  90 81 02 B8 */	stw r4, 0x2b8(r1)
/* 800D065C 000CB55C  90 61 02 BC */	stw r3, 0x2bc(r1)
/* 800D0660 000CB560  90 01 02 C0 */	stw r0, 0x2c0(r1)
/* 800D0664 000CB564  91 81 02 C4 */	stw r12, 0x2c4(r1)
/* 800D0668 000CB568  48 02 12 59 */	bl OSDisableInterrupts
/* 800D066C 000CB56C  7C 7F 1B 78 */	mr r31, r3
/* 800D0670 000CB570  48 02 12 51 */	bl OSDisableInterrupts
/* 800D0674 000CB574  88 9D 01 60 */	lbz r4, 0x160(r29)
/* 800D0678 000CB578  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800D067C 000CB57C  7C 04 00 50 */	subf r0, r4, r0
/* 800D0680 000CB580  7C 1A 07 75 */	extsb. r26, r0
/* 800D0684 000CB584  40 80 00 10 */	bge lbl_800D0694
/* 800D0688 000CB588  80 1D 01 68 */	lwz r0, 0x168(r29)
/* 800D068C 000CB58C  7C 1A 02 14 */	add r0, r26, r0
/* 800D0690 000CB590  7C 1A 07 74 */	extsb r26, r0
lbl_800D0694:
/* 800D0694 000CB594  48 02 12 55 */	bl OSRestoreInterrupts
/* 800D0698 000CB598  80 7D 01 68 */	lwz r3, 0x168(r29)
/* 800D069C 000CB59C  38 03 FF FF */	addi r0, r3, -1
/* 800D06A0 000CB5A0  7C 00 D0 40 */	cmplw r0, r26
/* 800D06A4 000CB5A4  40 82 00 10 */	bne lbl_800D06B4
/* 800D06A8 000CB5A8  7F E3 FB 78 */	mr r3, r31
/* 800D06AC 000CB5AC  48 02 12 3D */	bl OSRestoreInterrupts
/* 800D06B0 000CB5B0  48 00 00 78 */	b lbl_800D0728
lbl_800D06B4:
/* 800D06B4 000CB5B4  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800D06B8 000CB5B8  38 80 00 00 */	li r4, 0
/* 800D06BC 000CB5BC  80 7D 01 64 */	lwz r3, 0x164(r29)
/* 800D06C0 000CB5C0  38 A0 00 30 */	li r5, 0x30
/* 800D06C4 000CB5C4  7C 00 07 74 */	extsb r0, r0
/* 800D06C8 000CB5C8  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800D06CC 000CB5CC  7C 63 02 14 */	add r3, r3, r0
/* 800D06D0 000CB5D0  4B F3 3A 35 */	bl memset
/* 800D06D4 000CB5D4  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800D06D8 000CB5D8  38 81 02 98 */	addi r4, r1, 0x298
/* 800D06DC 000CB5DC  80 7D 01 64 */	lwz r3, 0x164(r29)
/* 800D06E0 000CB5E0  38 A0 00 30 */	li r5, 0x30
/* 800D06E4 000CB5E4  7C 00 07 74 */	extsb r0, r0
/* 800D06E8 000CB5E8  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800D06EC 000CB5EC  7C 63 02 14 */	add r3, r3, r0
/* 800D06F0 000CB5F0  4B F3 39 11 */	bl memcpy
/* 800D06F4 000CB5F4  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800D06F8 000CB5F8  7F E3 FB 78 */	mr r3, r31
/* 800D06FC 000CB5FC  80 9D 01 68 */	lwz r4, 0x168(r29)
/* 800D0700 000CB600  7C 06 07 74 */	extsb r6, r0
/* 800D0704 000CB604  38 84 FF FF */	addi r4, r4, -1
/* 800D0708 000CB608  7C A4 30 50 */	subf r5, r4, r6
/* 800D070C 000CB60C  38 06 00 01 */	addi r0, r6, 1
/* 800D0710 000CB610  7C 86 20 50 */	subf r4, r6, r4
/* 800D0714 000CB614  7C A4 20 F8 */	nor r4, r5, r4
/* 800D0718 000CB618  7C 84 FE 70 */	srawi r4, r4, 0x1f
/* 800D071C 000CB61C  7C 00 20 78 */	andc r0, r0, r4
/* 800D0720 000CB620  98 1D 01 61 */	stb r0, 0x161(r29)
/* 800D0724 000CB624  48 02 11 C5 */	bl OSRestoreInterrupts
lbl_800D0728:
/* 800D0728 000CB628  3C 60 04 B0 */	lis r3, 0x04B00030@ha
/* 800D072C 000CB62C  39 20 00 01 */	li r9, 1
/* 800D0730 000CB630  39 03 00 30 */	addi r8, r3, 0x04B00030@l
/* 800D0734 000CB634  38 E0 00 16 */	li r7, 0x16
/* 800D0738 000CB638  38 C0 00 15 */	li r6, 0x15
/* 800D073C 000CB63C  38 00 00 00 */	li r0, 0
/* 800D0740 000CB640  99 21 00 0F */	stb r9, 0xf(r1)
/* 800D0744 000CB644  38 61 02 3C */	addi r3, r1, 0x23c
/* 800D0748 000CB648  38 81 00 20 */	addi r4, r1, 0x20
/* 800D074C 000CB64C  38 A0 00 04 */	li r5, 4
/* 800D0750 000CB650  91 01 00 20 */	stw r8, 0x20(r1)
/* 800D0754 000CB654  99 21 00 0E */	stb r9, 0xe(r1)
/* 800D0758 000CB658  90 E1 02 38 */	stw r7, 0x238(r1)
/* 800D075C 000CB65C  B0 C1 02 52 */	sth r6, 0x252(r1)
/* 800D0760 000CB660  90 01 02 64 */	stw r0, 0x264(r1)
/* 800D0764 000CB664  4B F3 38 9D */	bl memcpy
/* 800D0768 000CB668  38 61 02 40 */	addi r3, r1, 0x240
/* 800D076C 000CB66C  38 81 00 0E */	addi r4, r1, 0xe
/* 800D0770 000CB670  38 A0 00 01 */	li r5, 1
/* 800D0774 000CB674  4B F3 38 8D */	bl memcpy
/* 800D0778 000CB678  38 61 02 41 */	addi r3, r1, 0x241
/* 800D077C 000CB67C  38 81 00 0F */	addi r4, r1, 0xf
/* 800D0780 000CB680  38 A0 00 01 */	li r5, 1
/* 800D0784 000CB684  4B F3 38 7D */	bl memcpy
/* 800D0788 000CB688  83 E1 02 38 */	lwz r31, 0x238(r1)
/* 800D078C 000CB68C  81 81 02 3C */	lwz r12, 0x23c(r1)
/* 800D0790 000CB690  81 61 02 40 */	lwz r11, 0x240(r1)
/* 800D0794 000CB694  81 41 02 44 */	lwz r10, 0x244(r1)
/* 800D0798 000CB698  81 21 02 48 */	lwz r9, 0x248(r1)
/* 800D079C 000CB69C  81 01 02 4C */	lwz r8, 0x24c(r1)
/* 800D07A0 000CB6A0  80 E1 02 50 */	lwz r7, 0x250(r1)
/* 800D07A4 000CB6A4  80 C1 02 54 */	lwz r6, 0x254(r1)
/* 800D07A8 000CB6A8  80 A1 02 58 */	lwz r5, 0x258(r1)
/* 800D07AC 000CB6AC  80 81 02 5C */	lwz r4, 0x25c(r1)
/* 800D07B0 000CB6B0  80 61 02 60 */	lwz r3, 0x260(r1)
/* 800D07B4 000CB6B4  80 01 02 64 */	lwz r0, 0x264(r1)
/* 800D07B8 000CB6B8  93 E1 02 08 */	stw r31, 0x208(r1)
/* 800D07BC 000CB6BC  91 81 02 0C */	stw r12, 0x20c(r1)
/* 800D07C0 000CB6C0  91 61 02 10 */	stw r11, 0x210(r1)
/* 800D07C4 000CB6C4  91 41 02 14 */	stw r10, 0x214(r1)
/* 800D07C8 000CB6C8  91 21 02 18 */	stw r9, 0x218(r1)
/* 800D07CC 000CB6CC  91 01 02 1C */	stw r8, 0x21c(r1)
/* 800D07D0 000CB6D0  90 E1 02 20 */	stw r7, 0x220(r1)
/* 800D07D4 000CB6D4  90 C1 02 24 */	stw r6, 0x224(r1)
/* 800D07D8 000CB6D8  90 A1 02 28 */	stw r5, 0x228(r1)
/* 800D07DC 000CB6DC  90 81 02 2C */	stw r4, 0x22c(r1)
/* 800D07E0 000CB6E0  90 61 02 30 */	stw r3, 0x230(r1)
/* 800D07E4 000CB6E4  90 01 02 34 */	stw r0, 0x234(r1)
/* 800D07E8 000CB6E8  48 02 10 D9 */	bl OSDisableInterrupts
/* 800D07EC 000CB6EC  7C 7F 1B 78 */	mr r31, r3
/* 800D07F0 000CB6F0  48 02 10 D1 */	bl OSDisableInterrupts
/* 800D07F4 000CB6F4  88 9D 01 60 */	lbz r4, 0x160(r29)
/* 800D07F8 000CB6F8  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800D07FC 000CB6FC  7C 04 00 50 */	subf r0, r4, r0
/* 800D0800 000CB700  7C 1A 07 75 */	extsb. r26, r0
/* 800D0804 000CB704  40 80 00 10 */	bge lbl_800D0814
/* 800D0808 000CB708  80 1D 01 68 */	lwz r0, 0x168(r29)
/* 800D080C 000CB70C  7C 1A 02 14 */	add r0, r26, r0
/* 800D0810 000CB710  7C 1A 07 74 */	extsb r26, r0
lbl_800D0814:
/* 800D0814 000CB714  48 02 10 D5 */	bl OSRestoreInterrupts
/* 800D0818 000CB718  80 7D 01 68 */	lwz r3, 0x168(r29)
/* 800D081C 000CB71C  38 03 FF FF */	addi r0, r3, -1
/* 800D0820 000CB720  7C 00 D0 40 */	cmplw r0, r26
/* 800D0824 000CB724  40 82 00 10 */	bne lbl_800D0834
/* 800D0828 000CB728  7F E3 FB 78 */	mr r3, r31
/* 800D082C 000CB72C  48 02 10 BD */	bl OSRestoreInterrupts
/* 800D0830 000CB730  48 00 00 78 */	b lbl_800D08A8
lbl_800D0834:
/* 800D0834 000CB734  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800D0838 000CB738  38 80 00 00 */	li r4, 0
/* 800D083C 000CB73C  80 7D 01 64 */	lwz r3, 0x164(r29)
/* 800D0840 000CB740  38 A0 00 30 */	li r5, 0x30
/* 800D0844 000CB744  7C 00 07 74 */	extsb r0, r0
/* 800D0848 000CB748  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800D084C 000CB74C  7C 63 02 14 */	add r3, r3, r0
/* 800D0850 000CB750  4B F3 38 B5 */	bl memset
/* 800D0854 000CB754  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800D0858 000CB758  38 81 02 08 */	addi r4, r1, 0x208
/* 800D085C 000CB75C  80 7D 01 64 */	lwz r3, 0x164(r29)
/* 800D0860 000CB760  38 A0 00 30 */	li r5, 0x30
/* 800D0864 000CB764  7C 00 07 74 */	extsb r0, r0
/* 800D0868 000CB768  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800D086C 000CB76C  7C 63 02 14 */	add r3, r3, r0
/* 800D0870 000CB770  4B F3 37 91 */	bl memcpy
/* 800D0874 000CB774  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800D0878 000CB778  7F E3 FB 78 */	mr r3, r31
/* 800D087C 000CB77C  80 9D 01 68 */	lwz r4, 0x168(r29)
/* 800D0880 000CB780  7C 06 07 74 */	extsb r6, r0
/* 800D0884 000CB784  38 84 FF FF */	addi r4, r4, -1
/* 800D0888 000CB788  7C A4 30 50 */	subf r5, r4, r6
/* 800D088C 000CB78C  38 06 00 01 */	addi r0, r6, 1
/* 800D0890 000CB790  7C 86 20 50 */	subf r4, r6, r4
/* 800D0894 000CB794  7C A4 20 F8 */	nor r4, r5, r4
/* 800D0898 000CB798  7C 84 FE 70 */	srawi r4, r4, 0x1f
/* 800D089C 000CB79C  7C 00 20 78 */	andc r0, r0, r4
/* 800D08A0 000CB7A0  98 1D 01 61 */	stb r0, 0x161(r29)
/* 800D08A4 000CB7A4  48 02 10 45 */	bl OSRestoreInterrupts
lbl_800D08A8:
/* 800D08A8 000CB7A8  88 AD 9A 79 */	lbz r5, _dpdSensitivity-_SDA_BASE_(r13)
/* 800D08AC 000CB7AC  3D 20 04 B0 */	lis r9, 0x4b0
/* 800D08B0 000CB7B0  3C 80 80 38 */	lis r4, cfg1$3396@ha
/* 800D08B4 000CB7B4  38 60 00 09 */	li r3, 9
/* 800D08B8 000CB7B8  39 05 FF FF */	addi r8, r5, -1
/* 800D08BC 000CB7BC  38 A0 00 16 */	li r5, 0x16
/* 800D08C0 000CB7C0  55 07 18 38 */	slwi r7, r8, 3
/* 800D08C4 000CB7C4  38 C0 00 15 */	li r6, 0x15
/* 800D08C8 000CB7C8  38 00 00 00 */	li r0, 0
/* 800D08CC 000CB7CC  98 61 00 0D */	stb r3, 0xd(r1)
/* 800D08D0 000CB7D0  7C E7 42 14 */	add r7, r7, r8
/* 800D08D4 000CB7D4  38 84 C4 70 */	addi r4, r4, cfg1$3396@l
/* 800D08D8 000CB7D8  90 A1 01 A8 */	stw r5, 0x1a8(r1)
/* 800D08DC 000CB7DC  7F 44 3A 14 */	add r26, r4, r7
/* 800D08E0 000CB7E0  38 61 01 AC */	addi r3, r1, 0x1ac
/* 800D08E4 000CB7E4  38 81 00 1C */	addi r4, r1, 0x1c
/* 800D08E8 000CB7E8  91 21 00 1C */	stw r9, 0x1c(r1)
/* 800D08EC 000CB7EC  38 A0 00 04 */	li r5, 4
/* 800D08F0 000CB7F0  B0 C1 01 C2 */	sth r6, 0x1c2(r1)
/* 800D08F4 000CB7F4  90 01 01 D4 */	stw r0, 0x1d4(r1)
/* 800D08F8 000CB7F8  4B F3 37 09 */	bl memcpy
/* 800D08FC 000CB7FC  38 61 01 B0 */	addi r3, r1, 0x1b0
/* 800D0900 000CB800  38 81 00 0D */	addi r4, r1, 0xd
/* 800D0904 000CB804  38 A0 00 01 */	li r5, 1
/* 800D0908 000CB808  4B F3 36 F9 */	bl memcpy
/* 800D090C 000CB80C  7F 44 D3 78 */	mr r4, r26
/* 800D0910 000CB810  38 61 01 B1 */	addi r3, r1, 0x1b1
/* 800D0914 000CB814  38 A0 00 09 */	li r5, 9
/* 800D0918 000CB818  4B F3 36 E9 */	bl memcpy
/* 800D091C 000CB81C  83 E1 01 A8 */	lwz r31, 0x1a8(r1)
/* 800D0920 000CB820  81 81 01 AC */	lwz r12, 0x1ac(r1)
/* 800D0924 000CB824  81 61 01 B0 */	lwz r11, 0x1b0(r1)
/* 800D0928 000CB828  81 41 01 B4 */	lwz r10, 0x1b4(r1)
/* 800D092C 000CB82C  81 21 01 B8 */	lwz r9, 0x1b8(r1)
/* 800D0930 000CB830  81 01 01 BC */	lwz r8, 0x1bc(r1)
/* 800D0934 000CB834  80 E1 01 C0 */	lwz r7, 0x1c0(r1)
/* 800D0938 000CB838  80 C1 01 C4 */	lwz r6, 0x1c4(r1)
/* 800D093C 000CB83C  80 A1 01 C8 */	lwz r5, 0x1c8(r1)
/* 800D0940 000CB840  80 81 01 CC */	lwz r4, 0x1cc(r1)
/* 800D0944 000CB844  80 61 01 D0 */	lwz r3, 0x1d0(r1)
/* 800D0948 000CB848  80 01 01 D4 */	lwz r0, 0x1d4(r1)
/* 800D094C 000CB84C  93 E1 01 D8 */	stw r31, 0x1d8(r1)
/* 800D0950 000CB850  91 81 01 DC */	stw r12, 0x1dc(r1)
/* 800D0954 000CB854  91 61 01 E0 */	stw r11, 0x1e0(r1)
/* 800D0958 000CB858  91 41 01 E4 */	stw r10, 0x1e4(r1)
/* 800D095C 000CB85C  91 21 01 E8 */	stw r9, 0x1e8(r1)
/* 800D0960 000CB860  91 01 01 EC */	stw r8, 0x1ec(r1)
/* 800D0964 000CB864  90 E1 01 F0 */	stw r7, 0x1f0(r1)
/* 800D0968 000CB868  90 C1 01 F4 */	stw r6, 0x1f4(r1)
/* 800D096C 000CB86C  90 A1 01 F8 */	stw r5, 0x1f8(r1)
/* 800D0970 000CB870  90 81 01 FC */	stw r4, 0x1fc(r1)
/* 800D0974 000CB874  90 61 02 00 */	stw r3, 0x200(r1)
/* 800D0978 000CB878  90 01 02 04 */	stw r0, 0x204(r1)
/* 800D097C 000CB87C  48 02 0F 45 */	bl OSDisableInterrupts
/* 800D0980 000CB880  7C 7F 1B 78 */	mr r31, r3
/* 800D0984 000CB884  48 02 0F 3D */	bl OSDisableInterrupts
/* 800D0988 000CB888  88 9D 01 60 */	lbz r4, 0x160(r29)
/* 800D098C 000CB88C  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800D0990 000CB890  7C 04 00 50 */	subf r0, r4, r0
/* 800D0994 000CB894  7C 1A 07 75 */	extsb. r26, r0
/* 800D0998 000CB898  40 80 00 10 */	bge lbl_800D09A8
/* 800D099C 000CB89C  80 1D 01 68 */	lwz r0, 0x168(r29)
/* 800D09A0 000CB8A0  7C 1A 02 14 */	add r0, r26, r0
/* 800D09A4 000CB8A4  7C 1A 07 74 */	extsb r26, r0
lbl_800D09A8:
/* 800D09A8 000CB8A8  48 02 0F 41 */	bl OSRestoreInterrupts
/* 800D09AC 000CB8AC  80 7D 01 68 */	lwz r3, 0x168(r29)
/* 800D09B0 000CB8B0  38 03 FF FF */	addi r0, r3, -1
/* 800D09B4 000CB8B4  7C 00 D0 40 */	cmplw r0, r26
/* 800D09B8 000CB8B8  40 82 00 10 */	bne lbl_800D09C8
/* 800D09BC 000CB8BC  7F E3 FB 78 */	mr r3, r31
/* 800D09C0 000CB8C0  48 02 0F 29 */	bl OSRestoreInterrupts
/* 800D09C4 000CB8C4  48 00 00 78 */	b lbl_800D0A3C
lbl_800D09C8:
/* 800D09C8 000CB8C8  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800D09CC 000CB8CC  38 80 00 00 */	li r4, 0
/* 800D09D0 000CB8D0  80 7D 01 64 */	lwz r3, 0x164(r29)
/* 800D09D4 000CB8D4  38 A0 00 30 */	li r5, 0x30
/* 800D09D8 000CB8D8  7C 00 07 74 */	extsb r0, r0
/* 800D09DC 000CB8DC  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800D09E0 000CB8E0  7C 63 02 14 */	add r3, r3, r0
/* 800D09E4 000CB8E4  4B F3 37 21 */	bl memset
/* 800D09E8 000CB8E8  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800D09EC 000CB8EC  38 81 01 D8 */	addi r4, r1, 0x1d8
/* 800D09F0 000CB8F0  80 7D 01 64 */	lwz r3, 0x164(r29)
/* 800D09F4 000CB8F4  38 A0 00 30 */	li r5, 0x30
/* 800D09F8 000CB8F8  7C 00 07 74 */	extsb r0, r0
/* 800D09FC 000CB8FC  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800D0A00 000CB900  7C 63 02 14 */	add r3, r3, r0
/* 800D0A04 000CB904  4B F3 35 FD */	bl memcpy
/* 800D0A08 000CB908  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800D0A0C 000CB90C  7F E3 FB 78 */	mr r3, r31
/* 800D0A10 000CB910  80 9D 01 68 */	lwz r4, 0x168(r29)
/* 800D0A14 000CB914  7C 06 07 74 */	extsb r6, r0
/* 800D0A18 000CB918  38 84 FF FF */	addi r4, r4, -1
/* 800D0A1C 000CB91C  7C A4 30 50 */	subf r5, r4, r6
/* 800D0A20 000CB920  38 06 00 01 */	addi r0, r6, 1
/* 800D0A24 000CB924  7C 86 20 50 */	subf r4, r6, r4
/* 800D0A28 000CB928  7C A4 20 F8 */	nor r4, r5, r4
/* 800D0A2C 000CB92C  7C 84 FE 70 */	srawi r4, r4, 0x1f
/* 800D0A30 000CB930  7C 00 20 78 */	andc r0, r0, r4
/* 800D0A34 000CB934  98 1D 01 61 */	stb r0, 0x161(r29)
/* 800D0A38 000CB938  48 02 0E B1 */	bl OSRestoreInterrupts
lbl_800D0A3C:
/* 800D0A3C 000CB93C  88 6D 9A 79 */	lbz r3, _dpdSensitivity-_SDA_BASE_(r13)
/* 800D0A40 000CB940  3C 80 04 B0 */	lis r4, 0x04B0001A@ha
/* 800D0A44 000CB944  39 04 00 1A */	addi r8, r4, 0x04B0001A@l
/* 800D0A48 000CB948  38 A0 00 16 */	li r5, 0x16
/* 800D0A4C 000CB94C  38 E3 FF FF */	addi r7, r3, -1
/* 800D0A50 000CB950  3C 80 80 38 */	lis r4, cfg2$3397@ha
/* 800D0A54 000CB954  38 60 00 02 */	li r3, 2
/* 800D0A58 000CB958  38 C0 00 15 */	li r6, 0x15
/* 800D0A5C 000CB95C  38 00 00 00 */	li r0, 0
/* 800D0A60 000CB960  98 61 00 0C */	stb r3, 0xc(r1)
/* 800D0A64 000CB964  54 E7 08 3C */	slwi r7, r7, 1
/* 800D0A68 000CB968  38 84 C4 A0 */	addi r4, r4, cfg2$3397@l
/* 800D0A6C 000CB96C  90 A1 01 48 */	stw r5, 0x148(r1)
/* 800D0A70 000CB970  7F 44 3A 14 */	add r26, r4, r7
/* 800D0A74 000CB974  38 61 01 4C */	addi r3, r1, 0x14c
/* 800D0A78 000CB978  38 81 00 18 */	addi r4, r1, 0x18
/* 800D0A7C 000CB97C  91 01 00 18 */	stw r8, 0x18(r1)
/* 800D0A80 000CB980  38 A0 00 04 */	li r5, 4
/* 800D0A84 000CB984  B0 C1 01 62 */	sth r6, 0x162(r1)
/* 800D0A88 000CB988  90 01 01 74 */	stw r0, 0x174(r1)
/* 800D0A8C 000CB98C  4B F3 35 75 */	bl memcpy
/* 800D0A90 000CB990  38 61 01 50 */	addi r3, r1, 0x150
/* 800D0A94 000CB994  38 81 00 0C */	addi r4, r1, 0xc
/* 800D0A98 000CB998  38 A0 00 01 */	li r5, 1
/* 800D0A9C 000CB99C  4B F3 35 65 */	bl memcpy
/* 800D0AA0 000CB9A0  7F 44 D3 78 */	mr r4, r26
/* 800D0AA4 000CB9A4  38 61 01 51 */	addi r3, r1, 0x151
/* 800D0AA8 000CB9A8  38 A0 00 02 */	li r5, 2
/* 800D0AAC 000CB9AC  4B F3 35 55 */	bl memcpy
/* 800D0AB0 000CB9B0  83 E1 01 48 */	lwz r31, 0x148(r1)
/* 800D0AB4 000CB9B4  81 81 01 4C */	lwz r12, 0x14c(r1)
/* 800D0AB8 000CB9B8  81 61 01 50 */	lwz r11, 0x150(r1)
/* 800D0ABC 000CB9BC  81 41 01 54 */	lwz r10, 0x154(r1)
/* 800D0AC0 000CB9C0  81 21 01 58 */	lwz r9, 0x158(r1)
/* 800D0AC4 000CB9C4  81 01 01 5C */	lwz r8, 0x15c(r1)
/* 800D0AC8 000CB9C8  80 E1 01 60 */	lwz r7, 0x160(r1)
/* 800D0ACC 000CB9CC  80 C1 01 64 */	lwz r6, 0x164(r1)
/* 800D0AD0 000CB9D0  80 A1 01 68 */	lwz r5, 0x168(r1)
/* 800D0AD4 000CB9D4  80 81 01 6C */	lwz r4, 0x16c(r1)
/* 800D0AD8 000CB9D8  80 61 01 70 */	lwz r3, 0x170(r1)
/* 800D0ADC 000CB9DC  80 01 01 74 */	lwz r0, 0x174(r1)
/* 800D0AE0 000CB9E0  93 E1 01 78 */	stw r31, 0x178(r1)
/* 800D0AE4 000CB9E4  91 81 01 7C */	stw r12, 0x17c(r1)
/* 800D0AE8 000CB9E8  91 61 01 80 */	stw r11, 0x180(r1)
/* 800D0AEC 000CB9EC  91 41 01 84 */	stw r10, 0x184(r1)
/* 800D0AF0 000CB9F0  91 21 01 88 */	stw r9, 0x188(r1)
/* 800D0AF4 000CB9F4  91 01 01 8C */	stw r8, 0x18c(r1)
/* 800D0AF8 000CB9F8  90 E1 01 90 */	stw r7, 0x190(r1)
/* 800D0AFC 000CB9FC  90 C1 01 94 */	stw r6, 0x194(r1)
/* 800D0B00 000CBA00  90 A1 01 98 */	stw r5, 0x198(r1)
/* 800D0B04 000CBA04  90 81 01 9C */	stw r4, 0x19c(r1)
/* 800D0B08 000CBA08  90 61 01 A0 */	stw r3, 0x1a0(r1)
/* 800D0B0C 000CBA0C  90 01 01 A4 */	stw r0, 0x1a4(r1)
/* 800D0B10 000CBA10  48 02 0D B1 */	bl OSDisableInterrupts
/* 800D0B14 000CBA14  7C 7F 1B 78 */	mr r31, r3
/* 800D0B18 000CBA18  48 02 0D A9 */	bl OSDisableInterrupts
/* 800D0B1C 000CBA1C  88 9D 01 60 */	lbz r4, 0x160(r29)
/* 800D0B20 000CBA20  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800D0B24 000CBA24  7C 04 00 50 */	subf r0, r4, r0
/* 800D0B28 000CBA28  7C 1A 07 75 */	extsb. r26, r0
/* 800D0B2C 000CBA2C  40 80 00 10 */	bge lbl_800D0B3C
/* 800D0B30 000CBA30  80 1D 01 68 */	lwz r0, 0x168(r29)
/* 800D0B34 000CBA34  7C 1A 02 14 */	add r0, r26, r0
/* 800D0B38 000CBA38  7C 1A 07 74 */	extsb r26, r0
lbl_800D0B3C:
/* 800D0B3C 000CBA3C  48 02 0D AD */	bl OSRestoreInterrupts
/* 800D0B40 000CBA40  80 7D 01 68 */	lwz r3, 0x168(r29)
/* 800D0B44 000CBA44  38 03 FF FF */	addi r0, r3, -1
/* 800D0B48 000CBA48  7C 00 D0 40 */	cmplw r0, r26
/* 800D0B4C 000CBA4C  40 82 00 10 */	bne lbl_800D0B5C
/* 800D0B50 000CBA50  7F E3 FB 78 */	mr r3, r31
/* 800D0B54 000CBA54  48 02 0D 95 */	bl OSRestoreInterrupts
/* 800D0B58 000CBA58  48 00 00 78 */	b lbl_800D0BD0
lbl_800D0B5C:
/* 800D0B5C 000CBA5C  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800D0B60 000CBA60  38 80 00 00 */	li r4, 0
/* 800D0B64 000CBA64  80 7D 01 64 */	lwz r3, 0x164(r29)
/* 800D0B68 000CBA68  38 A0 00 30 */	li r5, 0x30
/* 800D0B6C 000CBA6C  7C 00 07 74 */	extsb r0, r0
/* 800D0B70 000CBA70  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800D0B74 000CBA74  7C 63 02 14 */	add r3, r3, r0
/* 800D0B78 000CBA78  4B F3 35 8D */	bl memset
/* 800D0B7C 000CBA7C  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800D0B80 000CBA80  38 81 01 78 */	addi r4, r1, 0x178
/* 800D0B84 000CBA84  80 7D 01 64 */	lwz r3, 0x164(r29)
/* 800D0B88 000CBA88  38 A0 00 30 */	li r5, 0x30
/* 800D0B8C 000CBA8C  7C 00 07 74 */	extsb r0, r0
/* 800D0B90 000CBA90  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800D0B94 000CBA94  7C 63 02 14 */	add r3, r3, r0
/* 800D0B98 000CBA98  4B F3 34 69 */	bl memcpy
/* 800D0B9C 000CBA9C  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800D0BA0 000CBAA0  7F E3 FB 78 */	mr r3, r31
/* 800D0BA4 000CBAA4  80 9D 01 68 */	lwz r4, 0x168(r29)
/* 800D0BA8 000CBAA8  7C 06 07 74 */	extsb r6, r0
/* 800D0BAC 000CBAAC  38 84 FF FF */	addi r4, r4, -1
/* 800D0BB0 000CBAB0  7C A4 30 50 */	subf r5, r4, r6
/* 800D0BB4 000CBAB4  38 06 00 01 */	addi r0, r6, 1
/* 800D0BB8 000CBAB8  7C 86 20 50 */	subf r4, r6, r4
/* 800D0BBC 000CBABC  7C A4 20 F8 */	nor r4, r5, r4
/* 800D0BC0 000CBAC0  7C 84 FE 70 */	srawi r4, r4, 0x1f
/* 800D0BC4 000CBAC4  7C 00 20 78 */	andc r0, r0, r4
/* 800D0BC8 000CBAC8  98 1D 01 61 */	stb r0, 0x161(r29)
/* 800D0BCC 000CBACC  48 02 0D 1D */	bl OSRestoreInterrupts
lbl_800D0BD0:
/* 800D0BD0 000CBAD0  3C 60 04 B0 */	lis r3, 0x04B00033@ha
/* 800D0BD4 000CBAD4  39 00 00 01 */	li r8, 1
/* 800D0BD8 000CBAD8  39 23 00 33 */	addi r9, r3, 0x04B00033@l
/* 800D0BDC 000CBADC  38 E0 00 16 */	li r7, 0x16
/* 800D0BE0 000CBAE0  38 C0 00 15 */	li r6, 0x15
/* 800D0BE4 000CBAE4  38 00 00 00 */	li r0, 0
/* 800D0BE8 000CBAE8  9B 61 00 0B */	stb r27, 0xb(r1)
/* 800D0BEC 000CBAEC  38 61 01 1C */	addi r3, r1, 0x11c
/* 800D0BF0 000CBAF0  38 81 00 14 */	addi r4, r1, 0x14
/* 800D0BF4 000CBAF4  38 A0 00 04 */	li r5, 4
/* 800D0BF8 000CBAF8  91 21 00 14 */	stw r9, 0x14(r1)
/* 800D0BFC 000CBAFC  99 01 00 0A */	stb r8, 0xa(r1)
/* 800D0C00 000CBB00  90 E1 01 18 */	stw r7, 0x118(r1)
/* 800D0C04 000CBB04  B0 C1 01 32 */	sth r6, 0x132(r1)
/* 800D0C08 000CBB08  90 01 01 44 */	stw r0, 0x144(r1)
/* 800D0C0C 000CBB0C  4B F3 33 F5 */	bl memcpy
/* 800D0C10 000CBB10  38 61 01 20 */	addi r3, r1, 0x120
/* 800D0C14 000CBB14  38 81 00 0A */	addi r4, r1, 0xa
/* 800D0C18 000CBB18  38 A0 00 01 */	li r5, 1
/* 800D0C1C 000CBB1C  4B F3 33 E5 */	bl memcpy
/* 800D0C20 000CBB20  38 61 01 21 */	addi r3, r1, 0x121
/* 800D0C24 000CBB24  38 81 00 0B */	addi r4, r1, 0xb
/* 800D0C28 000CBB28  38 A0 00 01 */	li r5, 1
/* 800D0C2C 000CBB2C  4B F3 33 D5 */	bl memcpy
/* 800D0C30 000CBB30  83 61 01 18 */	lwz r27, 0x118(r1)
/* 800D0C34 000CBB34  81 81 01 1C */	lwz r12, 0x11c(r1)
/* 800D0C38 000CBB38  81 61 01 20 */	lwz r11, 0x120(r1)
/* 800D0C3C 000CBB3C  81 41 01 24 */	lwz r10, 0x124(r1)
/* 800D0C40 000CBB40  81 21 01 28 */	lwz r9, 0x128(r1)
/* 800D0C44 000CBB44  81 01 01 2C */	lwz r8, 0x12c(r1)
/* 800D0C48 000CBB48  80 E1 01 30 */	lwz r7, 0x130(r1)
/* 800D0C4C 000CBB4C  80 C1 01 34 */	lwz r6, 0x134(r1)
/* 800D0C50 000CBB50  80 A1 01 38 */	lwz r5, 0x138(r1)
/* 800D0C54 000CBB54  80 81 01 3C */	lwz r4, 0x13c(r1)
/* 800D0C58 000CBB58  80 61 01 40 */	lwz r3, 0x140(r1)
/* 800D0C5C 000CBB5C  80 01 01 44 */	lwz r0, 0x144(r1)
/* 800D0C60 000CBB60  93 61 00 E8 */	stw r27, 0xe8(r1)
/* 800D0C64 000CBB64  91 81 00 EC */	stw r12, 0xec(r1)
/* 800D0C68 000CBB68  91 61 00 F0 */	stw r11, 0xf0(r1)
/* 800D0C6C 000CBB6C  91 41 00 F4 */	stw r10, 0xf4(r1)
/* 800D0C70 000CBB70  91 21 00 F8 */	stw r9, 0xf8(r1)
/* 800D0C74 000CBB74  91 01 00 FC */	stw r8, 0xfc(r1)
/* 800D0C78 000CBB78  90 E1 01 00 */	stw r7, 0x100(r1)
/* 800D0C7C 000CBB7C  90 C1 01 04 */	stw r6, 0x104(r1)
/* 800D0C80 000CBB80  90 A1 01 08 */	stw r5, 0x108(r1)
/* 800D0C84 000CBB84  90 81 01 0C */	stw r4, 0x10c(r1)
/* 800D0C88 000CBB88  90 61 01 10 */	stw r3, 0x110(r1)
/* 800D0C8C 000CBB8C  90 01 01 14 */	stw r0, 0x114(r1)
/* 800D0C90 000CBB90  48 02 0C 31 */	bl OSDisableInterrupts
/* 800D0C94 000CBB94  7C 7F 1B 78 */	mr r31, r3
/* 800D0C98 000CBB98  48 02 0C 29 */	bl OSDisableInterrupts
/* 800D0C9C 000CBB9C  88 9D 01 60 */	lbz r4, 0x160(r29)
/* 800D0CA0 000CBBA0  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800D0CA4 000CBBA4  7C 04 00 50 */	subf r0, r4, r0
/* 800D0CA8 000CBBA8  7C 1A 07 75 */	extsb. r26, r0
/* 800D0CAC 000CBBAC  40 80 00 10 */	bge lbl_800D0CBC
/* 800D0CB0 000CBBB0  80 1D 01 68 */	lwz r0, 0x168(r29)
/* 800D0CB4 000CBBB4  7C 1A 02 14 */	add r0, r26, r0
/* 800D0CB8 000CBBB8  7C 1A 07 74 */	extsb r26, r0
lbl_800D0CBC:
/* 800D0CBC 000CBBBC  48 02 0C 2D */	bl OSRestoreInterrupts
/* 800D0CC0 000CBBC0  80 7D 01 68 */	lwz r3, 0x168(r29)
/* 800D0CC4 000CBBC4  38 03 FF FF */	addi r0, r3, -1
/* 800D0CC8 000CBBC8  7C 00 D0 40 */	cmplw r0, r26
/* 800D0CCC 000CBBCC  40 82 00 10 */	bne lbl_800D0CDC
/* 800D0CD0 000CBBD0  7F E3 FB 78 */	mr r3, r31
/* 800D0CD4 000CBBD4  48 02 0C 15 */	bl OSRestoreInterrupts
/* 800D0CD8 000CBBD8  48 00 00 78 */	b lbl_800D0D50
lbl_800D0CDC:
/* 800D0CDC 000CBBDC  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800D0CE0 000CBBE0  38 80 00 00 */	li r4, 0
/* 800D0CE4 000CBBE4  80 7D 01 64 */	lwz r3, 0x164(r29)
/* 800D0CE8 000CBBE8  38 A0 00 30 */	li r5, 0x30
/* 800D0CEC 000CBBEC  7C 00 07 74 */	extsb r0, r0
/* 800D0CF0 000CBBF0  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800D0CF4 000CBBF4  7C 63 02 14 */	add r3, r3, r0
/* 800D0CF8 000CBBF8  4B F3 34 0D */	bl memset
/* 800D0CFC 000CBBFC  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800D0D00 000CBC00  38 81 00 E8 */	addi r4, r1, 0xe8
/* 800D0D04 000CBC04  80 7D 01 64 */	lwz r3, 0x164(r29)
/* 800D0D08 000CBC08  38 A0 00 30 */	li r5, 0x30
/* 800D0D0C 000CBC0C  7C 00 07 74 */	extsb r0, r0
/* 800D0D10 000CBC10  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800D0D14 000CBC14  7C 63 02 14 */	add r3, r3, r0
/* 800D0D18 000CBC18  4B F3 32 E9 */	bl memcpy
/* 800D0D1C 000CBC1C  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800D0D20 000CBC20  7F E3 FB 78 */	mr r3, r31
/* 800D0D24 000CBC24  80 9D 01 68 */	lwz r4, 0x168(r29)
/* 800D0D28 000CBC28  7C 06 07 74 */	extsb r6, r0
/* 800D0D2C 000CBC2C  38 84 FF FF */	addi r4, r4, -1
/* 800D0D30 000CBC30  7C A4 30 50 */	subf r5, r4, r6
/* 800D0D34 000CBC34  38 06 00 01 */	addi r0, r6, 1
/* 800D0D38 000CBC38  7C 86 20 50 */	subf r4, r6, r4
/* 800D0D3C 000CBC3C  7C A4 20 F8 */	nor r4, r5, r4
/* 800D0D40 000CBC40  7C 84 FE 70 */	srawi r4, r4, 0x1f
/* 800D0D44 000CBC44  7C 00 20 78 */	andc r0, r0, r4
/* 800D0D48 000CBC48  98 1D 01 61 */	stb r0, 0x161(r29)
/* 800D0D4C 000CBC4C  48 02 0B 9D */	bl OSRestoreInterrupts
lbl_800D0D50:
/* 800D0D50 000CBC50  3C 60 04 B0 */	lis r3, 0x04B00030@ha
/* 800D0D54 000CBC54  3C C0 80 0D */	lis r6, lbl_800CFFB4@ha
/* 800D0D58 000CBC58  39 23 00 30 */	addi r9, r3, 0x04B00030@l
/* 800D0D5C 000CBC5C  39 00 00 01 */	li r8, 1
/* 800D0D60 000CBC60  38 60 00 08 */	li r3, 8
/* 800D0D64 000CBC64  38 C6 FF B4 */	addi r6, r6, lbl_800CFFB4@l
/* 800D0D68 000CBC68  38 E0 00 16 */	li r7, 0x16
/* 800D0D6C 000CBC6C  38 00 00 15 */	li r0, 0x15
/* 800D0D70 000CBC70  98 61 00 09 */	stb r3, 9(r1)
/* 800D0D74 000CBC74  38 61 00 BC */	addi r3, r1, 0xbc
/* 800D0D78 000CBC78  38 81 00 10 */	addi r4, r1, 0x10
/* 800D0D7C 000CBC7C  38 A0 00 04 */	li r5, 4
/* 800D0D80 000CBC80  91 21 00 10 */	stw r9, 0x10(r1)
/* 800D0D84 000CBC84  99 01 00 08 */	stb r8, 8(r1)
/* 800D0D88 000CBC88  90 E1 00 B8 */	stw r7, 0xb8(r1)
/* 800D0D8C 000CBC8C  B0 01 00 D2 */	sth r0, 0xd2(r1)
/* 800D0D90 000CBC90  90 C1 00 E4 */	stw r6, 0xe4(r1)
/* 800D0D94 000CBC94  4B F3 32 6D */	bl memcpy
/* 800D0D98 000CBC98  38 61 00 C0 */	addi r3, r1, 0xc0
/* 800D0D9C 000CBC9C  38 81 00 08 */	addi r4, r1, 8
/* 800D0DA0 000CBCA0  38 A0 00 01 */	li r5, 1
/* 800D0DA4 000CBCA4  4B F3 32 5D */	bl memcpy
/* 800D0DA8 000CBCA8  38 61 00 C1 */	addi r3, r1, 0xc1
/* 800D0DAC 000CBCAC  38 81 00 09 */	addi r4, r1, 9
/* 800D0DB0 000CBCB0  38 A0 00 01 */	li r5, 1
/* 800D0DB4 000CBCB4  4B F3 32 4D */	bl memcpy
/* 800D0DB8 000CBCB8  83 61 00 B8 */	lwz r27, 0xb8(r1)
/* 800D0DBC 000CBCBC  81 81 00 BC */	lwz r12, 0xbc(r1)
/* 800D0DC0 000CBCC0  81 61 00 C0 */	lwz r11, 0xc0(r1)
/* 800D0DC4 000CBCC4  81 41 00 C4 */	lwz r10, 0xc4(r1)
/* 800D0DC8 000CBCC8  81 21 00 C8 */	lwz r9, 0xc8(r1)
/* 800D0DCC 000CBCCC  81 01 00 CC */	lwz r8, 0xcc(r1)
/* 800D0DD0 000CBCD0  80 E1 00 D0 */	lwz r7, 0xd0(r1)
/* 800D0DD4 000CBCD4  80 C1 00 D4 */	lwz r6, 0xd4(r1)
/* 800D0DD8 000CBCD8  80 A1 00 D8 */	lwz r5, 0xd8(r1)
/* 800D0DDC 000CBCDC  80 81 00 DC */	lwz r4, 0xdc(r1)
/* 800D0DE0 000CBCE0  80 61 00 E0 */	lwz r3, 0xe0(r1)
/* 800D0DE4 000CBCE4  80 01 00 E4 */	lwz r0, 0xe4(r1)
/* 800D0DE8 000CBCE8  93 61 00 88 */	stw r27, 0x88(r1)
/* 800D0DEC 000CBCEC  91 81 00 8C */	stw r12, 0x8c(r1)
/* 800D0DF0 000CBCF0  91 61 00 90 */	stw r11, 0x90(r1)
/* 800D0DF4 000CBCF4  91 41 00 94 */	stw r10, 0x94(r1)
/* 800D0DF8 000CBCF8  91 21 00 98 */	stw r9, 0x98(r1)
/* 800D0DFC 000CBCFC  91 01 00 9C */	stw r8, 0x9c(r1)
/* 800D0E00 000CBD00  90 E1 00 A0 */	stw r7, 0xa0(r1)
/* 800D0E04 000CBD04  90 C1 00 A4 */	stw r6, 0xa4(r1)
/* 800D0E08 000CBD08  90 A1 00 A8 */	stw r5, 0xa8(r1)
/* 800D0E0C 000CBD0C  90 81 00 AC */	stw r4, 0xac(r1)
/* 800D0E10 000CBD10  90 61 00 B0 */	stw r3, 0xb0(r1)
/* 800D0E14 000CBD14  90 01 00 B4 */	stw r0, 0xb4(r1)
/* 800D0E18 000CBD18  48 02 0A A9 */	bl OSDisableInterrupts
/* 800D0E1C 000CBD1C  7C 7F 1B 78 */	mr r31, r3
/* 800D0E20 000CBD20  48 02 0A A1 */	bl OSDisableInterrupts
/* 800D0E24 000CBD24  88 9D 01 60 */	lbz r4, 0x160(r29)
/* 800D0E28 000CBD28  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800D0E2C 000CBD2C  7C 04 00 50 */	subf r0, r4, r0
/* 800D0E30 000CBD30  7C 1A 07 75 */	extsb. r26, r0
/* 800D0E34 000CBD34  40 80 00 10 */	bge lbl_800D0E44
/* 800D0E38 000CBD38  80 1D 01 68 */	lwz r0, 0x168(r29)
/* 800D0E3C 000CBD3C  7C 1A 02 14 */	add r0, r26, r0
/* 800D0E40 000CBD40  7C 1A 07 74 */	extsb r26, r0
lbl_800D0E44:
/* 800D0E44 000CBD44  48 02 0A A5 */	bl OSRestoreInterrupts
/* 800D0E48 000CBD48  80 7D 01 68 */	lwz r3, 0x168(r29)
/* 800D0E4C 000CBD4C  38 03 FF FF */	addi r0, r3, -1
/* 800D0E50 000CBD50  7C 00 D0 40 */	cmplw r0, r26
/* 800D0E54 000CBD54  40 82 00 10 */	bne lbl_800D0E64
/* 800D0E58 000CBD58  7F E3 FB 78 */	mr r3, r31
/* 800D0E5C 000CBD5C  48 02 0A 8D */	bl OSRestoreInterrupts
/* 800D0E60 000CBD60  48 00 00 78 */	b lbl_800D0ED8
lbl_800D0E64:
/* 800D0E64 000CBD64  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800D0E68 000CBD68  38 80 00 00 */	li r4, 0
/* 800D0E6C 000CBD6C  80 7D 01 64 */	lwz r3, 0x164(r29)
/* 800D0E70 000CBD70  38 A0 00 30 */	li r5, 0x30
/* 800D0E74 000CBD74  7C 00 07 74 */	extsb r0, r0
/* 800D0E78 000CBD78  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800D0E7C 000CBD7C  7C 63 02 14 */	add r3, r3, r0
/* 800D0E80 000CBD80  4B F3 32 85 */	bl memset
/* 800D0E84 000CBD84  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800D0E88 000CBD88  38 81 00 88 */	addi r4, r1, 0x88
/* 800D0E8C 000CBD8C  80 7D 01 64 */	lwz r3, 0x164(r29)
/* 800D0E90 000CBD90  38 A0 00 30 */	li r5, 0x30
/* 800D0E94 000CBD94  7C 00 07 74 */	extsb r0, r0
/* 800D0E98 000CBD98  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800D0E9C 000CBD9C  7C 63 02 14 */	add r3, r3, r0
/* 800D0EA0 000CBDA0  4B F3 31 61 */	bl memcpy
/* 800D0EA4 000CBDA4  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800D0EA8 000CBDA8  7F E3 FB 78 */	mr r3, r31
/* 800D0EAC 000CBDAC  80 9D 01 68 */	lwz r4, 0x168(r29)
/* 800D0EB0 000CBDB0  7C 06 07 74 */	extsb r6, r0
/* 800D0EB4 000CBDB4  38 84 FF FF */	addi r4, r4, -1
/* 800D0EB8 000CBDB8  7C A4 30 50 */	subf r5, r4, r6
/* 800D0EBC 000CBDBC  38 06 00 01 */	addi r0, r6, 1
/* 800D0EC0 000CBDC0  7C 86 20 50 */	subf r4, r6, r4
/* 800D0EC4 000CBDC4  7C A4 20 F8 */	nor r4, r5, r4
/* 800D0EC8 000CBDC8  7C 84 FE 70 */	srawi r4, r4, 0x1f
/* 800D0ECC 000CBDCC  7C 00 20 78 */	andc r0, r0, r4
/* 800D0ED0 000CBDD0  98 1D 01 61 */	stb r0, 0x161(r29)
/* 800D0ED4 000CBDD4  48 02 0A 15 */	bl OSRestoreInterrupts
lbl_800D0ED8:
/* 800D0ED8 000CBDD8  39 60 00 00 */	li r11, 0
/* 800D0EDC 000CBDDC  38 00 00 01 */	li r0, 1
/* 800D0EE0 000CBDE0  B0 01 00 42 */	sth r0, 0x42(r1)
/* 800D0EE4 000CBDE4  39 80 00 15 */	li r12, 0x15
/* 800D0EE8 000CBDE8  81 21 00 30 */	lwz r9, 0x30(r1)
/* 800D0EEC 000CBDEC  99 61 00 2C */	stb r11, 0x2c(r1)
/* 800D0EF0 000CBDF0  81 01 00 34 */	lwz r8, 0x34(r1)
/* 800D0EF4 000CBDF4  81 41 00 2C */	lwz r10, 0x2c(r1)
/* 800D0EF8 000CBDF8  80 E1 00 38 */	lwz r7, 0x38(r1)
/* 800D0EFC 000CBDFC  80 C1 00 3C */	lwz r6, 0x3c(r1)
/* 800D0F00 000CBE00  80 A1 00 40 */	lwz r5, 0x40(r1)
/* 800D0F04 000CBE04  80 81 00 44 */	lwz r4, 0x44(r1)
/* 800D0F08 000CBE08  80 61 00 48 */	lwz r3, 0x48(r1)
/* 800D0F0C 000CBE0C  80 01 00 4C */	lwz r0, 0x4c(r1)
/* 800D0F10 000CBE10  91 81 00 28 */	stw r12, 0x28(r1)
/* 800D0F14 000CBE14  93 81 00 54 */	stw r28, 0x54(r1)
/* 800D0F18 000CBE18  91 61 00 50 */	stw r11, 0x50(r1)
/* 800D0F1C 000CBE1C  91 81 00 58 */	stw r12, 0x58(r1)
/* 800D0F20 000CBE20  91 41 00 5C */	stw r10, 0x5c(r1)
/* 800D0F24 000CBE24  91 21 00 60 */	stw r9, 0x60(r1)
/* 800D0F28 000CBE28  91 01 00 64 */	stw r8, 0x64(r1)
/* 800D0F2C 000CBE2C  90 E1 00 68 */	stw r7, 0x68(r1)
/* 800D0F30 000CBE30  90 C1 00 6C */	stw r6, 0x6c(r1)
/* 800D0F34 000CBE34  90 A1 00 70 */	stw r5, 0x70(r1)
/* 800D0F38 000CBE38  90 81 00 74 */	stw r4, 0x74(r1)
/* 800D0F3C 000CBE3C  90 61 00 78 */	stw r3, 0x78(r1)
/* 800D0F40 000CBE40  90 01 00 7C */	stw r0, 0x7c(r1)
/* 800D0F44 000CBE44  91 61 00 80 */	stw r11, 0x80(r1)
/* 800D0F48 000CBE48  93 81 00 84 */	stw r28, 0x84(r1)
/* 800D0F4C 000CBE4C  48 02 09 75 */	bl OSDisableInterrupts
/* 800D0F50 000CBE50  7C 7F 1B 78 */	mr r31, r3
/* 800D0F54 000CBE54  48 02 09 6D */	bl OSDisableInterrupts
/* 800D0F58 000CBE58  88 9D 01 60 */	lbz r4, 0x160(r29)
/* 800D0F5C 000CBE5C  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800D0F60 000CBE60  7C 04 00 50 */	subf r0, r4, r0
/* 800D0F64 000CBE64  7C 1A 07 75 */	extsb. r26, r0
/* 800D0F68 000CBE68  40 80 00 10 */	bge lbl_800D0F78
/* 800D0F6C 000CBE6C  80 1D 01 68 */	lwz r0, 0x168(r29)
/* 800D0F70 000CBE70  7C 1A 02 14 */	add r0, r26, r0
/* 800D0F74 000CBE74  7C 1A 07 74 */	extsb r26, r0
lbl_800D0F78:
/* 800D0F78 000CBE78  48 02 09 71 */	bl OSRestoreInterrupts
/* 800D0F7C 000CBE7C  80 7D 01 68 */	lwz r3, 0x168(r29)
/* 800D0F80 000CBE80  38 03 FF FF */	addi r0, r3, -1
/* 800D0F84 000CBE84  7C 00 D0 40 */	cmplw r0, r26
/* 800D0F88 000CBE88  40 82 00 10 */	bne lbl_800D0F98
/* 800D0F8C 000CBE8C  7F E3 FB 78 */	mr r3, r31
/* 800D0F90 000CBE90  48 02 09 59 */	bl OSRestoreInterrupts
/* 800D0F94 000CBE94  48 00 00 78 */	b lbl_800D100C
lbl_800D0F98:
/* 800D0F98 000CBE98  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800D0F9C 000CBE9C  38 80 00 00 */	li r4, 0
/* 800D0FA0 000CBEA0  80 7D 01 64 */	lwz r3, 0x164(r29)
/* 800D0FA4 000CBEA4  38 A0 00 30 */	li r5, 0x30
/* 800D0FA8 000CBEA8  7C 00 07 74 */	extsb r0, r0
/* 800D0FAC 000CBEAC  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800D0FB0 000CBEB0  7C 63 02 14 */	add r3, r3, r0
/* 800D0FB4 000CBEB4  4B F3 31 51 */	bl memset
/* 800D0FB8 000CBEB8  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800D0FBC 000CBEBC  38 81 00 58 */	addi r4, r1, 0x58
/* 800D0FC0 000CBEC0  80 7D 01 64 */	lwz r3, 0x164(r29)
/* 800D0FC4 000CBEC4  38 A0 00 30 */	li r5, 0x30
/* 800D0FC8 000CBEC8  7C 00 07 74 */	extsb r0, r0
/* 800D0FCC 000CBECC  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800D0FD0 000CBED0  7C 63 02 14 */	add r3, r3, r0
/* 800D0FD4 000CBED4  4B F3 30 2D */	bl memcpy
/* 800D0FD8 000CBED8  88 1D 01 61 */	lbz r0, 0x161(r29)
/* 800D0FDC 000CBEDC  7F E3 FB 78 */	mr r3, r31
/* 800D0FE0 000CBEE0  80 9D 01 68 */	lwz r4, 0x168(r29)
/* 800D0FE4 000CBEE4  7C 06 07 74 */	extsb r6, r0
/* 800D0FE8 000CBEE8  38 84 FF FF */	addi r4, r4, -1
/* 800D0FEC 000CBEEC  7C A4 30 50 */	subf r5, r4, r6
/* 800D0FF0 000CBEF0  38 06 00 01 */	addi r0, r6, 1
/* 800D0FF4 000CBEF4  7C 86 20 50 */	subf r4, r6, r4
/* 800D0FF8 000CBEF8  7C A4 20 F8 */	nor r4, r5, r4
/* 800D0FFC 000CBEFC  7C 84 FE 70 */	srawi r4, r4, 0x1f
/* 800D1000 000CBF00  7C 00 20 78 */	andc r0, r0, r4
/* 800D1004 000CBF04  98 1D 01 61 */	stb r0, 0x161(r29)
/* 800D1008 000CBF08  48 02 08 E1 */	bl OSRestoreInterrupts
lbl_800D100C:
/* 800D100C 000CBF0C  7F C3 F3 78 */	mr r3, r30
/* 800D1010 000CBF10  48 02 08 D9 */	bl OSRestoreInterrupts
/* 800D1014 000CBF14  38 60 00 00 */	li r3, 0
/* 800D1018 000CBF18  48 00 00 30 */	b lbl_800D1048
lbl_800D101C:
/* 800D101C 000CBF1C  7F C3 F3 78 */	mr r3, r30
/* 800D1020 000CBF20  3B 00 FF FE */	li r24, -2
/* 800D1024 000CBF24  48 02 08 C5 */	bl OSRestoreInterrupts
lbl_800D1028:
/* 800D1028 000CBF28  2C 1C 00 00 */	cmpwi r28, 0
/* 800D102C 000CBF2C  41 82 00 18 */	beq lbl_800D1044
/* 800D1030 000CBF30  7F 8C E3 78 */	mr r12, r28
/* 800D1034 000CBF34  7F E3 FB 78 */	mr r3, r31
/* 800D1038 000CBF38  7F 04 C3 78 */	mr r4, r24
/* 800D103C 000CBF3C  7D 89 03 A6 */	mtctr r12
/* 800D1040 000CBF40  4E 80 04 21 */	bctrl 
lbl_800D1044:
/* 800D1044 000CBF44  7F 03 C3 78 */	mr r3, r24
lbl_800D1048:
/* 800D1048 000CBF48  39 61 04 70 */	addi r11, r1, 0x470
/* 800D104C 000CBF4C  4B FE 0D 39 */	bl _restgpr_24
/* 800D1050 000CBF50  80 01 04 74 */	lwz r0, 0x474(r1)
/* 800D1054 000CBF54  7C 08 03 A6 */	mtlr r0
/* 800D1058 000CBF58  38 21 04 70 */	addi r1, r1, 0x470
/* 800D105C 000CBF5C  4E 80 00 20 */	blr 

.global __SendData
__SendData:
/* 800D1060 000CBF60  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 800D1064 000CBF64  7C 08 02 A6 */	mflr r0
/* 800D1068 000CBF68  90 01 00 44 */	stw r0, 0x44(r1)
/* 800D106C 000CBF6C  39 61 00 40 */	addi r11, r1, 0x40
/* 800D1070 000CBF70  4B FE 0C C5 */	bl _savegpr_23
/* 800D1074 000CBF74  80 04 00 00 */	lwz r0, 0(r4)
/* 800D1078 000CBF78  7C 77 1B 78 */	mr r23, r3
/* 800D107C 000CBF7C  A3 24 00 1A */	lhz r25, 0x1a(r4)
/* 800D1080 000CBF80  7C 98 23 78 */	mr r24, r4
/* 800D1084 000CBF84  54 1B 06 3E */	clrlwi r27, r0, 0x18
/* 800D1088 000CBF88  3B 44 00 04 */	addi r26, r4, 4
/* 800D108C 000CBF8C  48 02 08 35 */	bl OSDisableInterrupts
/* 800D1090 000CBF90  3C 80 80 41 */	lis r4, _wpdcb@ha
/* 800D1094 000CBF94  56 E0 10 3A */	slwi r0, r23, 2
/* 800D1098 000CBF98  38 84 F6 30 */	addi r4, r4, _wpdcb@l
/* 800D109C 000CBF9C  7F 84 00 2E */	lwzx r28, r4, r0
/* 800D10A0 000CBFA0  8B BC 08 C3 */	lbz r29, 0x8c3(r28)
/* 800D10A4 000CBFA4  82 FC 08 BC */	lwz r23, 0x8bc(r28)
/* 800D10A8 000CBFA8  7F A0 07 75 */	extsb. r0, r29
/* 800D10AC 000CBFAC  40 80 00 0C */	bge lbl_800D10B8
/* 800D10B0 000CBFB0  48 02 08 39 */	bl OSRestoreInterrupts
/* 800D10B4 000CBFB4  48 00 01 C8 */	b lbl_800D127C
lbl_800D10B8:
/* 800D10B8 000CBFB8  38 00 FF FE */	li r0, -2
/* 800D10BC 000CBFBC  90 1C 08 BC */	stw r0, 0x8bc(r28)
/* 800D10C0 000CBFC0  80 9C 08 D4 */	lwz r4, 0x8d4(r28)
/* 800D10C4 000CBFC4  80 0D 9A 74 */	lwz r0, _rumble-_SDA_BASE_(r13)
/* 800D10C8 000CBFC8  7C 9E 00 38 */	and r30, r4, r0
/* 800D10CC 000CBFCC  48 02 08 1D */	bl OSRestoreInterrupts
/* 800D10D0 000CBFD0  28 1B 00 10 */	cmplwi r27, 0x10
/* 800D10D4 000CBFD4  40 82 00 14 */	bne lbl_800D10E8
/* 800D10D8 000CBFD8  48 02 07 E9 */	bl OSDisableInterrupts
/* 800D10DC 000CBFDC  92 FC 08 BC */	stw r23, 0x8bc(r28)
/* 800D10E0 000CBFE0  48 02 08 09 */	bl OSRestoreInterrupts
/* 800D10E4 000CBFE4  48 00 01 14 */	b lbl_800D11F8
lbl_800D10E8:
/* 800D10E8 000CBFE8  28 1B 00 18 */	cmplwi r27, 0x18
/* 800D10EC 000CBFEC  40 82 00 20 */	bne lbl_800D110C
/* 800D10F0 000CBFF0  48 02 07 D1 */	bl OSDisableInterrupts
/* 800D10F4 000CBFF4  92 FC 08 BC */	stw r23, 0x8bc(r28)
/* 800D10F8 000CBFF8  88 9C 08 CF */	lbz r4, 0x8cf(r28)
/* 800D10FC 000CBFFC  38 04 FF FF */	addi r0, r4, -1
/* 800D1100 000CC000  98 1C 08 CF */	stb r0, 0x8cf(r28)
/* 800D1104 000CC004  48 02 07 E5 */	bl OSRestoreInterrupts
/* 800D1108 000CC008  48 00 00 F0 */	b lbl_800D11F8
lbl_800D110C:
/* 800D110C 000CC00C  48 02 07 B5 */	bl OSDisableInterrupts
/* 800D1110 000CC010  2C 1B 00 17 */	cmpwi r27, 0x17
/* 800D1114 000CC014  7C 7F 1B 78 */	mr r31, r3
/* 800D1118 000CC018  41 82 00 24 */	beq lbl_800D113C
/* 800D111C 000CC01C  40 80 00 14 */	bge lbl_800D1130
/* 800D1120 000CC020  2C 1B 00 15 */	cmpwi r27, 0x15
/* 800D1124 000CC024  41 82 00 3C */	beq lbl_800D1160
/* 800D1128 000CC028  40 80 00 94 */	bge lbl_800D11BC
/* 800D112C 000CC02C  48 00 00 84 */	b lbl_800D11B0
lbl_800D1130:
/* 800D1130 000CC030  2C 1B 00 FF */	cmpwi r27, 0xff
/* 800D1134 000CC034  41 82 00 44 */	beq lbl_800D1178
/* 800D1138 000CC038  48 00 00 78 */	b lbl_800D11B0
lbl_800D113C:
/* 800D113C 000CC03C  38 00 00 00 */	li r0, 0
/* 800D1140 000CC040  90 1C 09 7C */	stw r0, 0x97c(r28)
/* 800D1144 000CC044  80 18 00 24 */	lwz r0, 0x24(r24)
/* 800D1148 000CC048  90 1C 09 78 */	stw r0, 0x978(r28)
/* 800D114C 000CC04C  A0 18 00 20 */	lhz r0, 0x20(r24)
/* 800D1150 000CC050  B0 1C 09 80 */	sth r0, 0x980(r28)
/* 800D1154 000CC054  80 18 00 1C */	lwz r0, 0x1c(r24)
/* 800D1158 000CC058  90 1C 09 74 */	stw r0, 0x974(r28)
/* 800D115C 000CC05C  48 00 00 60 */	b lbl_800D11BC
lbl_800D1160:
/* 800D1160 000CC060  92 FC 08 BC */	stw r23, 0x8bc(r28)
/* 800D1164 000CC064  38 00 00 01 */	li r0, 1
/* 800D1168 000CC068  80 78 00 28 */	lwz r3, 0x28(r24)
/* 800D116C 000CC06C  90 7C 08 50 */	stw r3, 0x850(r28)
/* 800D1170 000CC070  98 1C 08 C0 */	stb r0, 0x8c0(r28)
/* 800D1174 000CC074  48 00 00 48 */	b lbl_800D11BC
lbl_800D1178:
/* 800D1178 000CC078  38 61 00 08 */	addi r3, r1, 8
/* 800D117C 000CC07C  7F 44 D3 78 */	mr r4, r26
/* 800D1180 000CC080  38 A0 00 04 */	li r5, 4
/* 800D1184 000CC084  4B F3 2E 7D */	bl memcpy
/* 800D1188 000CC088  48 02 44 9D */	bl __OSGetSystemTime
/* 800D118C 000CC08C  80 C1 00 08 */	lwz r6, 8(r1)
/* 800D1190 000CC090  38 A0 00 00 */	li r5, 0
/* 800D1194 000CC094  38 00 00 01 */	li r0, 1
/* 800D1198 000CC098  7C 86 20 14 */	addc r4, r6, r4
/* 800D119C 000CC09C  90 9C 09 0C */	stw r4, 0x90c(r28)
/* 800D11A0 000CC0A0  7C 65 19 14 */	adde r3, r5, r3
/* 800D11A4 000CC0A4  90 7C 09 08 */	stw r3, 0x908(r28)
/* 800D11A8 000CC0A8  98 1C 09 10 */	stb r0, 0x910(r28)
/* 800D11AC 000CC0AC  48 00 00 D0 */	b lbl_800D127C
lbl_800D11B0:
/* 800D11B0 000CC0B0  88 1A 00 00 */	lbz r0, 0(r26)
/* 800D11B4 000CC0B4  60 00 00 02 */	ori r0, r0, 2
/* 800D11B8 000CC0B8  98 1A 00 00 */	stb r0, 0(r26)
lbl_800D11BC:
/* 800D11BC 000CC0BC  80 18 00 2C */	lwz r0, 0x2c(r24)
/* 800D11C0 000CC0C0  90 1C 08 9C */	stw r0, 0x89c(r28)
/* 800D11C4 000CC0C4  9B 7C 09 87 */	stb r27, 0x987(r28)
/* 800D11C8 000CC0C8  48 02 44 5D */	bl __OSGetSystemTime
/* 800D11CC 000CC0CC  3C C0 80 00 */	lis r6, 0x800000F8@ha
/* 800D11D0 000CC0D0  38 A0 00 00 */	li r5, 0
/* 800D11D4 000CC0D4  80 06 00 F8 */	lwz r0, 0x800000F8@l(r6)
/* 800D11D8 000CC0D8  54 00 F8 7C */	rlwinm r0, r0, 0x1f, 1, 0x1e
/* 800D11DC 000CC0DC  7C 00 20 14 */	addc r0, r0, r4
/* 800D11E0 000CC0E0  90 1C 09 0C */	stw r0, 0x90c(r28)
/* 800D11E4 000CC0E4  7C 05 19 14 */	adde r0, r5, r3
/* 800D11E8 000CC0E8  7F E3 FB 78 */	mr r3, r31
/* 800D11EC 000CC0EC  90 1C 09 08 */	stw r0, 0x908(r28)
/* 800D11F0 000CC0F0  98 BC 09 10 */	stb r5, 0x910(r28)
/* 800D11F4 000CC0F4  48 02 06 F5 */	bl OSRestoreInterrupts
lbl_800D11F8:
/* 800D11F8 000CC0F8  3C 60 80 3A */	lis r3, lbl_80399714@ha
/* 800D11FC 000CC0FC  7F 65 DB 78 */	mr r5, r27
/* 800D1200 000CC100  38 63 97 14 */	addi r3, r3, lbl_80399714@l
/* 800D1204 000CC104  7F A4 07 74 */	extsb r4, r29
/* 800D1208 000CC108  4C C6 31 82 */	crclr 6
/* 800D120C 000CC10C  48 00 65 51 */	bl DEBUGPrint
/* 800D1210 000CC110  38 19 00 12 */	addi r0, r25, 0x12
/* 800D1214 000CC114  54 03 06 3E */	clrlwi r3, r0, 0x18
/* 800D1218 000CC118  48 03 9E 51 */	bl func_8010B068
/* 800D121C 000CC11C  38 99 00 01 */	addi r4, r25, 1
/* 800D1220 000CC120  38 00 00 0A */	li r0, 0xa
/* 800D1224 000CC124  54 84 06 3E */	clrlwi r4, r4, 0x18
/* 800D1228 000CC128  3B 83 00 12 */	addi r28, r3, 0x12
/* 800D122C 000CC12C  B0 83 00 02 */	sth r4, 2(r3)
/* 800D1230 000CC130  7C 78 1B 78 */	mr r24, r3
/* 800D1234 000CC134  7F 44 D3 78 */	mr r4, r26
/* 800D1238 000CC138  7F 25 CB 78 */	mr r5, r25
/* 800D123C 000CC13C  B0 03 00 04 */	sth r0, 4(r3)
/* 800D1240 000CC140  38 7C 00 01 */	addi r3, r28, 1
/* 800D1244 000CC144  9B 7C 00 00 */	stb r27, 0(r28)
/* 800D1248 000CC148  4B F3 2D B9 */	bl memcpy
/* 800D124C 000CC14C  2C 1E 00 00 */	cmpwi r30, 0
/* 800D1250 000CC150  41 82 00 14 */	beq lbl_800D1264
/* 800D1254 000CC154  88 1C 00 01 */	lbz r0, 1(r28)
/* 800D1258 000CC158  60 00 00 01 */	ori r0, r0, 1
/* 800D125C 000CC15C  98 1C 00 01 */	stb r0, 1(r28)
/* 800D1260 000CC160  48 00 00 10 */	b lbl_800D1270
lbl_800D1264:
/* 800D1264 000CC164  88 1C 00 01 */	lbz r0, 1(r28)
/* 800D1268 000CC168  54 00 06 3C */	rlwinm r0, r0, 0, 0x18, 0x1e
/* 800D126C 000CC16C  98 1C 00 01 */	stb r0, 1(r28)
lbl_800D1270:
/* 800D1270 000CC170  7F A3 EB 78 */	mr r3, r29
/* 800D1274 000CC174  7F 04 C3 78 */	mr r4, r24
/* 800D1278 000CC178  48 04 2C 85 */	bl func_80113EFC
lbl_800D127C:
/* 800D127C 000CC17C  39 61 00 40 */	addi r11, r1, 0x40
/* 800D1280 000CC180  4B FE 0B 01 */	bl _restgpr_23
/* 800D1284 000CC184  80 01 00 44 */	lwz r0, 0x44(r1)
/* 800D1288 000CC188  7C 08 03 A6 */	mtlr r0
/* 800D128C 000CC18C  38 21 00 40 */	addi r1, r1, 0x40
/* 800D1290 000CC190  4E 80 00 20 */	blr 

.global WPADiSendSetReportType
WPADiSendSetReportType:
/* 800D1294 000CC194  94 21 FF 80 */	stwu r1, -0x80(r1)
/* 800D1298 000CC198  7C 08 02 A6 */	mflr r0
/* 800D129C 000CC19C  38 E0 00 12 */	li r7, 0x12
/* 800D12A0 000CC1A0  38 C0 00 02 */	li r6, 2
/* 800D12A4 000CC1A4  90 01 00 84 */	stw r0, 0x84(r1)
/* 800D12A8 000CC1A8  38 00 00 04 */	li r0, 4
/* 800D12AC 000CC1AC  28 04 00 09 */	cmplwi r4, 9
/* 800D12B0 000CC1B0  93 E1 00 7C */	stw r31, 0x7c(r1)
/* 800D12B4 000CC1B4  93 C1 00 78 */	stw r30, 0x78(r1)
/* 800D12B8 000CC1B8  7C 7E 1B 78 */	mr r30, r3
/* 800D12BC 000CC1BC  93 A1 00 74 */	stw r29, 0x74(r1)
/* 800D12C0 000CC1C0  90 E1 00 38 */	stw r7, 0x38(r1)
/* 800D12C4 000CC1C4  B0 C1 00 52 */	sth r6, 0x52(r1)
/* 800D12C8 000CC1C8  98 01 00 3C */	stb r0, 0x3c(r1)
/* 800D12CC 000CC1CC  90 A1 00 64 */	stw r5, 0x64(r1)
/* 800D12D0 000CC1D0  41 81 00 90 */	bgt lbl_800D1360
/* 800D12D4 000CC1D4  3C 60 80 3A */	lis r3, lbl_80399730@ha
/* 800D12D8 000CC1D8  54 80 10 3A */	slwi r0, r4, 2
/* 800D12DC 000CC1DC  38 63 97 30 */	addi r3, r3, lbl_80399730@l
/* 800D12E0 000CC1E0  7C 63 00 2E */	lwzx r3, r3, r0
/* 800D12E4 000CC1E4  7C 69 03 A6 */	mtctr r3
/* 800D12E8 000CC1E8  4E 80 04 20 */	bctr 
/* 800D12EC 000CC1EC  38 00 00 30 */	li r0, 0x30
/* 800D12F0 000CC1F0  98 01 00 3D */	stb r0, 0x3d(r1)
/* 800D12F4 000CC1F4  48 00 00 6C */	b lbl_800D1360
/* 800D12F8 000CC1F8  38 00 00 31 */	li r0, 0x31
/* 800D12FC 000CC1FC  98 01 00 3D */	stb r0, 0x3d(r1)
/* 800D1300 000CC200  48 00 00 60 */	b lbl_800D1360
/* 800D1304 000CC204  38 00 00 33 */	li r0, 0x33
/* 800D1308 000CC208  98 01 00 3D */	stb r0, 0x3d(r1)
/* 800D130C 000CC20C  48 00 00 54 */	b lbl_800D1360
/* 800D1310 000CC210  38 00 00 32 */	li r0, 0x32
/* 800D1314 000CC214  98 01 00 3D */	stb r0, 0x3d(r1)
/* 800D1318 000CC218  48 00 00 48 */	b lbl_800D1360
/* 800D131C 000CC21C  38 00 00 35 */	li r0, 0x35
/* 800D1320 000CC220  98 01 00 3D */	stb r0, 0x3d(r1)
/* 800D1324 000CC224  48 00 00 3C */	b lbl_800D1360
/* 800D1328 000CC228  38 00 00 37 */	li r0, 0x37
/* 800D132C 000CC22C  98 01 00 3D */	stb r0, 0x3d(r1)
/* 800D1330 000CC230  48 00 00 30 */	b lbl_800D1360
/* 800D1334 000CC234  38 00 00 32 */	li r0, 0x32
/* 800D1338 000CC238  98 01 00 3D */	stb r0, 0x3d(r1)
/* 800D133C 000CC23C  48 00 00 24 */	b lbl_800D1360
/* 800D1340 000CC240  38 00 00 35 */	li r0, 0x35
/* 800D1344 000CC244  98 01 00 3D */	stb r0, 0x3d(r1)
/* 800D1348 000CC248  48 00 00 18 */	b lbl_800D1360
/* 800D134C 000CC24C  38 00 00 37 */	li r0, 0x37
/* 800D1350 000CC250  98 01 00 3D */	stb r0, 0x3d(r1)
/* 800D1354 000CC254  48 00 00 0C */	b lbl_800D1360
/* 800D1358 000CC258  38 00 00 3E */	li r0, 0x3e
/* 800D135C 000CC25C  98 01 00 3D */	stb r0, 0x3d(r1)
lbl_800D1360:
/* 800D1360 000CC260  83 E1 00 38 */	lwz r31, 0x38(r1)
/* 800D1364 000CC264  81 81 00 3C */	lwz r12, 0x3c(r1)
/* 800D1368 000CC268  81 61 00 40 */	lwz r11, 0x40(r1)
/* 800D136C 000CC26C  81 41 00 44 */	lwz r10, 0x44(r1)
/* 800D1370 000CC270  81 21 00 48 */	lwz r9, 0x48(r1)
/* 800D1374 000CC274  81 01 00 4C */	lwz r8, 0x4c(r1)
/* 800D1378 000CC278  80 E1 00 50 */	lwz r7, 0x50(r1)
/* 800D137C 000CC27C  80 C1 00 54 */	lwz r6, 0x54(r1)
/* 800D1380 000CC280  80 A1 00 58 */	lwz r5, 0x58(r1)
/* 800D1384 000CC284  80 81 00 5C */	lwz r4, 0x5c(r1)
/* 800D1388 000CC288  80 61 00 60 */	lwz r3, 0x60(r1)
/* 800D138C 000CC28C  80 01 00 64 */	lwz r0, 0x64(r1)
/* 800D1390 000CC290  93 E1 00 08 */	stw r31, 8(r1)
/* 800D1394 000CC294  91 81 00 0C */	stw r12, 0xc(r1)
/* 800D1398 000CC298  91 61 00 10 */	stw r11, 0x10(r1)
/* 800D139C 000CC29C  91 41 00 14 */	stw r10, 0x14(r1)
/* 800D13A0 000CC2A0  91 21 00 18 */	stw r9, 0x18(r1)
/* 800D13A4 000CC2A4  91 01 00 1C */	stw r8, 0x1c(r1)
/* 800D13A8 000CC2A8  90 E1 00 20 */	stw r7, 0x20(r1)
/* 800D13AC 000CC2AC  90 C1 00 24 */	stw r6, 0x24(r1)
/* 800D13B0 000CC2B0  90 A1 00 28 */	stw r5, 0x28(r1)
/* 800D13B4 000CC2B4  90 81 00 2C */	stw r4, 0x2c(r1)
/* 800D13B8 000CC2B8  90 61 00 30 */	stw r3, 0x30(r1)
/* 800D13BC 000CC2BC  90 01 00 34 */	stw r0, 0x34(r1)
/* 800D13C0 000CC2C0  48 02 05 01 */	bl OSDisableInterrupts
/* 800D13C4 000CC2C4  7C 7F 1B 78 */	mr r31, r3
/* 800D13C8 000CC2C8  48 02 04 F9 */	bl OSDisableInterrupts
/* 800D13CC 000CC2CC  88 9E 00 00 */	lbz r4, 0(r30)
/* 800D13D0 000CC2D0  88 1E 00 01 */	lbz r0, 1(r30)
/* 800D13D4 000CC2D4  7C 04 00 50 */	subf r0, r4, r0
/* 800D13D8 000CC2D8  7C 1D 07 75 */	extsb. r29, r0
/* 800D13DC 000CC2DC  40 80 00 10 */	bge lbl_800D13EC
/* 800D13E0 000CC2E0  80 1E 00 08 */	lwz r0, 8(r30)
/* 800D13E4 000CC2E4  7C 1D 02 14 */	add r0, r29, r0
/* 800D13E8 000CC2E8  7C 1D 07 74 */	extsb r29, r0
lbl_800D13EC:
/* 800D13EC 000CC2EC  48 02 04 FD */	bl OSRestoreInterrupts
/* 800D13F0 000CC2F0  80 7E 00 08 */	lwz r3, 8(r30)
/* 800D13F4 000CC2F4  38 03 FF FF */	addi r0, r3, -1
/* 800D13F8 000CC2F8  7C 00 E8 40 */	cmplw r0, r29
/* 800D13FC 000CC2FC  40 82 00 14 */	bne lbl_800D1410
/* 800D1400 000CC300  7F E3 FB 78 */	mr r3, r31
/* 800D1404 000CC304  48 02 04 E5 */	bl OSRestoreInterrupts
/* 800D1408 000CC308  38 60 00 00 */	li r3, 0
/* 800D140C 000CC30C  48 00 00 7C */	b lbl_800D1488
lbl_800D1410:
/* 800D1410 000CC310  88 1E 00 01 */	lbz r0, 1(r30)
/* 800D1414 000CC314  38 80 00 00 */	li r4, 0
/* 800D1418 000CC318  80 7E 00 04 */	lwz r3, 4(r30)
/* 800D141C 000CC31C  38 A0 00 30 */	li r5, 0x30
/* 800D1420 000CC320  7C 00 07 74 */	extsb r0, r0
/* 800D1424 000CC324  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800D1428 000CC328  7C 63 02 14 */	add r3, r3, r0
/* 800D142C 000CC32C  4B F3 2C D9 */	bl memset
/* 800D1430 000CC330  88 1E 00 01 */	lbz r0, 1(r30)
/* 800D1434 000CC334  38 81 00 08 */	addi r4, r1, 8
/* 800D1438 000CC338  80 7E 00 04 */	lwz r3, 4(r30)
/* 800D143C 000CC33C  38 A0 00 30 */	li r5, 0x30
/* 800D1440 000CC340  7C 00 07 74 */	extsb r0, r0
/* 800D1444 000CC344  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800D1448 000CC348  7C 63 02 14 */	add r3, r3, r0
/* 800D144C 000CC34C  4B F3 2B B5 */	bl memcpy
/* 800D1450 000CC350  88 1E 00 01 */	lbz r0, 1(r30)
/* 800D1454 000CC354  7F E3 FB 78 */	mr r3, r31
/* 800D1458 000CC358  80 9E 00 08 */	lwz r4, 8(r30)
/* 800D145C 000CC35C  7C 06 07 74 */	extsb r6, r0
/* 800D1460 000CC360  38 84 FF FF */	addi r4, r4, -1
/* 800D1464 000CC364  7C A4 30 50 */	subf r5, r4, r6
/* 800D1468 000CC368  38 06 00 01 */	addi r0, r6, 1
/* 800D146C 000CC36C  7C 86 20 50 */	subf r4, r6, r4
/* 800D1470 000CC370  7C A4 20 F8 */	nor r4, r5, r4
/* 800D1474 000CC374  7C 84 FE 70 */	srawi r4, r4, 0x1f
/* 800D1478 000CC378  7C 00 20 78 */	andc r0, r0, r4
/* 800D147C 000CC37C  98 1E 00 01 */	stb r0, 1(r30)
/* 800D1480 000CC380  48 02 04 69 */	bl OSRestoreInterrupts
/* 800D1484 000CC384  38 60 00 01 */	li r3, 1
lbl_800D1488:
/* 800D1488 000CC388  80 01 00 84 */	lwz r0, 0x84(r1)
/* 800D148C 000CC38C  83 E1 00 7C */	lwz r31, 0x7c(r1)
/* 800D1490 000CC390  83 C1 00 78 */	lwz r30, 0x78(r1)
/* 800D1494 000CC394  83 A1 00 74 */	lwz r29, 0x74(r1)
/* 800D1498 000CC398  7C 08 03 A6 */	mtlr r0
/* 800D149C 000CC39C  38 21 00 80 */	addi r1, r1, 0x80
/* 800D14A0 000CC3A0  4E 80 00 20 */	blr 

.global WPADiSendWriteDataCmd
WPADiSendWriteDataCmd:
/* 800D14A4 000CC3A4  94 21 FF 80 */	stwu r1, -0x80(r1)
/* 800D14A8 000CC3A8  7C 08 02 A6 */	mflr r0
/* 800D14AC 000CC3AC  39 00 00 01 */	li r8, 1
/* 800D14B0 000CC3B0  38 E0 00 16 */	li r7, 0x16
/* 800D14B4 000CC3B4  90 01 00 84 */	stw r0, 0x84(r1)
/* 800D14B8 000CC3B8  38 00 00 15 */	li r0, 0x15
/* 800D14BC 000CC3BC  93 E1 00 7C */	stw r31, 0x7c(r1)
/* 800D14C0 000CC3C0  7C 7F 1B 78 */	mr r31, r3
/* 800D14C4 000CC3C4  38 61 00 14 */	addi r3, r1, 0x14
/* 800D14C8 000CC3C8  93 C1 00 78 */	stw r30, 0x78(r1)
/* 800D14CC 000CC3CC  93 A1 00 74 */	stw r29, 0x74(r1)
/* 800D14D0 000CC3D0  98 81 00 08 */	stb r4, 8(r1)
/* 800D14D4 000CC3D4  38 81 00 0C */	addi r4, r1, 0xc
/* 800D14D8 000CC3D8  90 A1 00 0C */	stw r5, 0xc(r1)
/* 800D14DC 000CC3DC  38 A0 00 04 */	li r5, 4
/* 800D14E0 000CC3E0  99 01 00 09 */	stb r8, 9(r1)
/* 800D14E4 000CC3E4  90 E1 00 10 */	stw r7, 0x10(r1)
/* 800D14E8 000CC3E8  B0 01 00 2A */	sth r0, 0x2a(r1)
/* 800D14EC 000CC3EC  90 C1 00 3C */	stw r6, 0x3c(r1)
/* 800D14F0 000CC3F0  4B F3 2B 11 */	bl memcpy
/* 800D14F4 000CC3F4  38 61 00 18 */	addi r3, r1, 0x18
/* 800D14F8 000CC3F8  38 81 00 09 */	addi r4, r1, 9
/* 800D14FC 000CC3FC  38 A0 00 01 */	li r5, 1
/* 800D1500 000CC400  4B F3 2B 01 */	bl memcpy
/* 800D1504 000CC404  38 61 00 19 */	addi r3, r1, 0x19
/* 800D1508 000CC408  38 81 00 08 */	addi r4, r1, 8
/* 800D150C 000CC40C  38 A0 00 01 */	li r5, 1
/* 800D1510 000CC410  4B F3 2A F1 */	bl memcpy
/* 800D1514 000CC414  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 800D1518 000CC418  81 81 00 14 */	lwz r12, 0x14(r1)
/* 800D151C 000CC41C  81 61 00 18 */	lwz r11, 0x18(r1)
/* 800D1520 000CC420  81 41 00 1C */	lwz r10, 0x1c(r1)
/* 800D1524 000CC424  81 21 00 20 */	lwz r9, 0x20(r1)
/* 800D1528 000CC428  81 01 00 24 */	lwz r8, 0x24(r1)
/* 800D152C 000CC42C  80 E1 00 28 */	lwz r7, 0x28(r1)
/* 800D1530 000CC430  80 C1 00 2C */	lwz r6, 0x2c(r1)
/* 800D1534 000CC434  80 A1 00 30 */	lwz r5, 0x30(r1)
/* 800D1538 000CC438  80 81 00 34 */	lwz r4, 0x34(r1)
/* 800D153C 000CC43C  80 61 00 38 */	lwz r3, 0x38(r1)
/* 800D1540 000CC440  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 800D1544 000CC444  93 C1 00 40 */	stw r30, 0x40(r1)
/* 800D1548 000CC448  91 81 00 44 */	stw r12, 0x44(r1)
/* 800D154C 000CC44C  91 61 00 48 */	stw r11, 0x48(r1)
/* 800D1550 000CC450  91 41 00 4C */	stw r10, 0x4c(r1)
/* 800D1554 000CC454  91 21 00 50 */	stw r9, 0x50(r1)
/* 800D1558 000CC458  91 01 00 54 */	stw r8, 0x54(r1)
/* 800D155C 000CC45C  90 E1 00 58 */	stw r7, 0x58(r1)
/* 800D1560 000CC460  90 C1 00 5C */	stw r6, 0x5c(r1)
/* 800D1564 000CC464  90 A1 00 60 */	stw r5, 0x60(r1)
/* 800D1568 000CC468  90 81 00 64 */	stw r4, 0x64(r1)
/* 800D156C 000CC46C  90 61 00 68 */	stw r3, 0x68(r1)
/* 800D1570 000CC470  90 01 00 6C */	stw r0, 0x6c(r1)
/* 800D1574 000CC474  48 02 03 4D */	bl OSDisableInterrupts
/* 800D1578 000CC478  7C 7E 1B 78 */	mr r30, r3
/* 800D157C 000CC47C  48 02 03 45 */	bl OSDisableInterrupts
/* 800D1580 000CC480  88 9F 00 00 */	lbz r4, 0(r31)
/* 800D1584 000CC484  88 1F 00 01 */	lbz r0, 1(r31)
/* 800D1588 000CC488  7C 04 00 50 */	subf r0, r4, r0
/* 800D158C 000CC48C  7C 1D 07 75 */	extsb. r29, r0
/* 800D1590 000CC490  40 80 00 10 */	bge lbl_800D15A0
/* 800D1594 000CC494  80 1F 00 08 */	lwz r0, 8(r31)
/* 800D1598 000CC498  7C 1D 02 14 */	add r0, r29, r0
/* 800D159C 000CC49C  7C 1D 07 74 */	extsb r29, r0
lbl_800D15A0:
/* 800D15A0 000CC4A0  48 02 03 49 */	bl OSRestoreInterrupts
/* 800D15A4 000CC4A4  80 7F 00 08 */	lwz r3, 8(r31)
/* 800D15A8 000CC4A8  38 03 FF FF */	addi r0, r3, -1
/* 800D15AC 000CC4AC  7C 00 E8 40 */	cmplw r0, r29
/* 800D15B0 000CC4B0  40 82 00 14 */	bne lbl_800D15C4
/* 800D15B4 000CC4B4  7F C3 F3 78 */	mr r3, r30
/* 800D15B8 000CC4B8  48 02 03 31 */	bl OSRestoreInterrupts
/* 800D15BC 000CC4BC  38 60 00 00 */	li r3, 0
/* 800D15C0 000CC4C0  48 00 00 7C */	b lbl_800D163C
lbl_800D15C4:
/* 800D15C4 000CC4C4  88 1F 00 01 */	lbz r0, 1(r31)
/* 800D15C8 000CC4C8  38 80 00 00 */	li r4, 0
/* 800D15CC 000CC4CC  80 7F 00 04 */	lwz r3, 4(r31)
/* 800D15D0 000CC4D0  38 A0 00 30 */	li r5, 0x30
/* 800D15D4 000CC4D4  7C 00 07 74 */	extsb r0, r0
/* 800D15D8 000CC4D8  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800D15DC 000CC4DC  7C 63 02 14 */	add r3, r3, r0
/* 800D15E0 000CC4E0  4B F3 2B 25 */	bl memset
/* 800D15E4 000CC4E4  88 1F 00 01 */	lbz r0, 1(r31)
/* 800D15E8 000CC4E8  38 81 00 40 */	addi r4, r1, 0x40
/* 800D15EC 000CC4EC  80 7F 00 04 */	lwz r3, 4(r31)
/* 800D15F0 000CC4F0  38 A0 00 30 */	li r5, 0x30
/* 800D15F4 000CC4F4  7C 00 07 74 */	extsb r0, r0
/* 800D15F8 000CC4F8  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800D15FC 000CC4FC  7C 63 02 14 */	add r3, r3, r0
/* 800D1600 000CC500  4B F3 2A 01 */	bl memcpy
/* 800D1604 000CC504  88 1F 00 01 */	lbz r0, 1(r31)
/* 800D1608 000CC508  7F C3 F3 78 */	mr r3, r30
/* 800D160C 000CC50C  80 9F 00 08 */	lwz r4, 8(r31)
/* 800D1610 000CC510  7C 06 07 74 */	extsb r6, r0
/* 800D1614 000CC514  38 84 FF FF */	addi r4, r4, -1
/* 800D1618 000CC518  7C A4 30 50 */	subf r5, r4, r6
/* 800D161C 000CC51C  38 06 00 01 */	addi r0, r6, 1
/* 800D1620 000CC520  7C 86 20 50 */	subf r4, r6, r4
/* 800D1624 000CC524  7C A4 20 F8 */	nor r4, r5, r4
/* 800D1628 000CC528  7C 84 FE 70 */	srawi r4, r4, 0x1f
/* 800D162C 000CC52C  7C 00 20 78 */	andc r0, r0, r4
/* 800D1630 000CC530  98 1F 00 01 */	stb r0, 1(r31)
/* 800D1634 000CC534  48 02 02 B5 */	bl OSRestoreInterrupts
/* 800D1638 000CC538  38 60 00 01 */	li r3, 1
lbl_800D163C:
/* 800D163C 000CC53C  80 01 00 84 */	lwz r0, 0x84(r1)
/* 800D1640 000CC540  83 E1 00 7C */	lwz r31, 0x7c(r1)
/* 800D1644 000CC544  83 C1 00 78 */	lwz r30, 0x78(r1)
/* 800D1648 000CC548  83 A1 00 74 */	lwz r29, 0x74(r1)
/* 800D164C 000CC54C  7C 08 03 A6 */	mtlr r0
/* 800D1650 000CC550  38 21 00 80 */	addi r1, r1, 0x80
/* 800D1654 000CC554  4E 80 00 20 */	blr 

.global WPADiSendWriteData
WPADiSendWriteData:
/* 800D1658 000CC558  94 21 FF 80 */	stwu r1, -0x80(r1)
/* 800D165C 000CC55C  7C 08 02 A6 */	mflr r0
/* 800D1660 000CC560  54 A9 06 FE */	clrlwi r9, r5, 0x1b
/* 800D1664 000CC564  39 00 00 16 */	li r8, 0x16
/* 800D1668 000CC568  90 01 00 84 */	stw r0, 0x84(r1)
/* 800D166C 000CC56C  38 00 00 15 */	li r0, 0x15
/* 800D1670 000CC570  93 E1 00 7C */	stw r31, 0x7c(r1)
/* 800D1674 000CC574  7C 9F 23 78 */	mr r31, r4
/* 800D1678 000CC578  38 81 00 08 */	addi r4, r1, 8
/* 800D167C 000CC57C  93 C1 00 78 */	stw r30, 0x78(r1)
/* 800D1680 000CC580  7C 7E 1B 78 */	mr r30, r3
/* 800D1684 000CC584  38 61 00 44 */	addi r3, r1, 0x44
/* 800D1688 000CC588  93 A1 00 74 */	stw r29, 0x74(r1)
/* 800D168C 000CC58C  7C BD 2B 78 */	mr r29, r5
/* 800D1690 000CC590  38 A0 00 04 */	li r5, 4
/* 800D1694 000CC594  90 C1 00 08 */	stw r6, 8(r1)
/* 800D1698 000CC598  99 21 00 0C */	stb r9, 0xc(r1)
/* 800D169C 000CC59C  91 01 00 40 */	stw r8, 0x40(r1)
/* 800D16A0 000CC5A0  B0 01 00 5A */	sth r0, 0x5a(r1)
/* 800D16A4 000CC5A4  90 E1 00 6C */	stw r7, 0x6c(r1)
/* 800D16A8 000CC5A8  4B F3 29 59 */	bl memcpy
/* 800D16AC 000CC5AC  38 61 00 48 */	addi r3, r1, 0x48
/* 800D16B0 000CC5B0  38 81 00 0C */	addi r4, r1, 0xc
/* 800D16B4 000CC5B4  38 A0 00 01 */	li r5, 1
/* 800D16B8 000CC5B8  4B F3 29 49 */	bl memcpy
/* 800D16BC 000CC5BC  7F E4 FB 78 */	mr r4, r31
/* 800D16C0 000CC5C0  7F A5 EB 78 */	mr r5, r29
/* 800D16C4 000CC5C4  38 61 00 49 */	addi r3, r1, 0x49
/* 800D16C8 000CC5C8  4B F3 29 39 */	bl memcpy
/* 800D16CC 000CC5CC  83 E1 00 40 */	lwz r31, 0x40(r1)
/* 800D16D0 000CC5D0  81 81 00 44 */	lwz r12, 0x44(r1)
/* 800D16D4 000CC5D4  81 61 00 48 */	lwz r11, 0x48(r1)
/* 800D16D8 000CC5D8  81 41 00 4C */	lwz r10, 0x4c(r1)
/* 800D16DC 000CC5DC  81 21 00 50 */	lwz r9, 0x50(r1)
/* 800D16E0 000CC5E0  81 01 00 54 */	lwz r8, 0x54(r1)
/* 800D16E4 000CC5E4  80 E1 00 58 */	lwz r7, 0x58(r1)
/* 800D16E8 000CC5E8  80 C1 00 5C */	lwz r6, 0x5c(r1)
/* 800D16EC 000CC5EC  80 A1 00 60 */	lwz r5, 0x60(r1)
/* 800D16F0 000CC5F0  80 81 00 64 */	lwz r4, 0x64(r1)
/* 800D16F4 000CC5F4  80 61 00 68 */	lwz r3, 0x68(r1)
/* 800D16F8 000CC5F8  80 01 00 6C */	lwz r0, 0x6c(r1)
/* 800D16FC 000CC5FC  93 E1 00 10 */	stw r31, 0x10(r1)
/* 800D1700 000CC600  91 81 00 14 */	stw r12, 0x14(r1)
/* 800D1704 000CC604  91 61 00 18 */	stw r11, 0x18(r1)
/* 800D1708 000CC608  91 41 00 1C */	stw r10, 0x1c(r1)
/* 800D170C 000CC60C  91 21 00 20 */	stw r9, 0x20(r1)
/* 800D1710 000CC610  91 01 00 24 */	stw r8, 0x24(r1)
/* 800D1714 000CC614  90 E1 00 28 */	stw r7, 0x28(r1)
/* 800D1718 000CC618  90 C1 00 2C */	stw r6, 0x2c(r1)
/* 800D171C 000CC61C  90 A1 00 30 */	stw r5, 0x30(r1)
/* 800D1720 000CC620  90 81 00 34 */	stw r4, 0x34(r1)
/* 800D1724 000CC624  90 61 00 38 */	stw r3, 0x38(r1)
/* 800D1728 000CC628  90 01 00 3C */	stw r0, 0x3c(r1)
/* 800D172C 000CC62C  48 02 01 95 */	bl OSDisableInterrupts
/* 800D1730 000CC630  7C 7F 1B 78 */	mr r31, r3
/* 800D1734 000CC634  48 02 01 8D */	bl OSDisableInterrupts
/* 800D1738 000CC638  88 9E 00 00 */	lbz r4, 0(r30)
/* 800D173C 000CC63C  88 1E 00 01 */	lbz r0, 1(r30)
/* 800D1740 000CC640  7C 04 00 50 */	subf r0, r4, r0
/* 800D1744 000CC644  7C 1D 07 75 */	extsb. r29, r0
/* 800D1748 000CC648  40 80 00 10 */	bge lbl_800D1758
/* 800D174C 000CC64C  80 1E 00 08 */	lwz r0, 8(r30)
/* 800D1750 000CC650  7C 1D 02 14 */	add r0, r29, r0
/* 800D1754 000CC654  7C 1D 07 74 */	extsb r29, r0
lbl_800D1758:
/* 800D1758 000CC658  48 02 01 91 */	bl OSRestoreInterrupts
/* 800D175C 000CC65C  80 7E 00 08 */	lwz r3, 8(r30)
/* 800D1760 000CC660  38 03 FF FF */	addi r0, r3, -1
/* 800D1764 000CC664  7C 00 E8 40 */	cmplw r0, r29
/* 800D1768 000CC668  40 82 00 14 */	bne lbl_800D177C
/* 800D176C 000CC66C  7F E3 FB 78 */	mr r3, r31
/* 800D1770 000CC670  48 02 01 79 */	bl OSRestoreInterrupts
/* 800D1774 000CC674  38 60 00 00 */	li r3, 0
/* 800D1778 000CC678  48 00 00 7C */	b lbl_800D17F4
lbl_800D177C:
/* 800D177C 000CC67C  88 1E 00 01 */	lbz r0, 1(r30)
/* 800D1780 000CC680  38 80 00 00 */	li r4, 0
/* 800D1784 000CC684  80 7E 00 04 */	lwz r3, 4(r30)
/* 800D1788 000CC688  38 A0 00 30 */	li r5, 0x30
/* 800D178C 000CC68C  7C 00 07 74 */	extsb r0, r0
/* 800D1790 000CC690  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800D1794 000CC694  7C 63 02 14 */	add r3, r3, r0
/* 800D1798 000CC698  4B F3 29 6D */	bl memset
/* 800D179C 000CC69C  88 1E 00 01 */	lbz r0, 1(r30)
/* 800D17A0 000CC6A0  38 81 00 10 */	addi r4, r1, 0x10
/* 800D17A4 000CC6A4  80 7E 00 04 */	lwz r3, 4(r30)
/* 800D17A8 000CC6A8  38 A0 00 30 */	li r5, 0x30
/* 800D17AC 000CC6AC  7C 00 07 74 */	extsb r0, r0
/* 800D17B0 000CC6B0  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800D17B4 000CC6B4  7C 63 02 14 */	add r3, r3, r0
/* 800D17B8 000CC6B8  4B F3 28 49 */	bl memcpy
/* 800D17BC 000CC6BC  88 1E 00 01 */	lbz r0, 1(r30)
/* 800D17C0 000CC6C0  7F E3 FB 78 */	mr r3, r31
/* 800D17C4 000CC6C4  80 9E 00 08 */	lwz r4, 8(r30)
/* 800D17C8 000CC6C8  7C 06 07 74 */	extsb r6, r0
/* 800D17CC 000CC6CC  38 84 FF FF */	addi r4, r4, -1
/* 800D17D0 000CC6D0  7C A4 30 50 */	subf r5, r4, r6
/* 800D17D4 000CC6D4  38 06 00 01 */	addi r0, r6, 1
/* 800D17D8 000CC6D8  7C 86 20 50 */	subf r4, r6, r4
/* 800D17DC 000CC6DC  7C A4 20 F8 */	nor r4, r5, r4
/* 800D17E0 000CC6E0  7C 84 FE 70 */	srawi r4, r4, 0x1f
/* 800D17E4 000CC6E4  7C 00 20 78 */	andc r0, r0, r4
/* 800D17E8 000CC6E8  98 1E 00 01 */	stb r0, 1(r30)
/* 800D17EC 000CC6EC  48 02 00 FD */	bl OSRestoreInterrupts
/* 800D17F0 000CC6F0  38 60 00 01 */	li r3, 1
lbl_800D17F4:
/* 800D17F4 000CC6F4  80 01 00 84 */	lwz r0, 0x84(r1)
/* 800D17F8 000CC6F8  83 E1 00 7C */	lwz r31, 0x7c(r1)
/* 800D17FC 000CC6FC  83 C1 00 78 */	lwz r30, 0x78(r1)
/* 800D1800 000CC700  83 A1 00 74 */	lwz r29, 0x74(r1)
/* 800D1804 000CC704  7C 08 03 A6 */	mtlr r0
/* 800D1808 000CC708  38 21 00 80 */	addi r1, r1, 0x80
/* 800D180C 000CC70C  4E 80 00 20 */	blr 

.global WPADiSendReadData
WPADiSendReadData:
/* 800D1810 000CC710  94 21 FF 80 */	stwu r1, -0x80(r1)
/* 800D1814 000CC714  7C 08 02 A6 */	mflr r0
/* 800D1818 000CC718  39 00 00 17 */	li r8, 0x17
/* 800D181C 000CC71C  90 01 00 84 */	stw r0, 0x84(r1)
/* 800D1820 000CC720  38 00 00 06 */	li r0, 6
/* 800D1824 000CC724  93 E1 00 7C */	stw r31, 0x7c(r1)
/* 800D1828 000CC728  93 C1 00 78 */	stw r30, 0x78(r1)
/* 800D182C 000CC72C  7C 7E 1B 78 */	mr r30, r3
/* 800D1830 000CC730  38 61 00 44 */	addi r3, r1, 0x44
/* 800D1834 000CC734  93 A1 00 74 */	stw r29, 0x74(r1)
/* 800D1838 000CC738  7C 9D 23 78 */	mr r29, r4
/* 800D183C 000CC73C  38 81 00 0C */	addi r4, r1, 0xc
/* 800D1840 000CC740  B0 A1 00 08 */	sth r5, 8(r1)
/* 800D1844 000CC744  38 A0 00 04 */	li r5, 4
/* 800D1848 000CC748  90 C1 00 0C */	stw r6, 0xc(r1)
/* 800D184C 000CC74C  91 01 00 40 */	stw r8, 0x40(r1)
/* 800D1850 000CC750  B0 01 00 5A */	sth r0, 0x5a(r1)
/* 800D1854 000CC754  90 E1 00 6C */	stw r7, 0x6c(r1)
/* 800D1858 000CC758  4B F3 27 A9 */	bl memcpy
/* 800D185C 000CC75C  38 61 00 48 */	addi r3, r1, 0x48
/* 800D1860 000CC760  38 81 00 08 */	addi r4, r1, 8
/* 800D1864 000CC764  38 A0 00 02 */	li r5, 2
/* 800D1868 000CC768  4B F3 27 99 */	bl memcpy
/* 800D186C 000CC76C  A0 01 00 08 */	lhz r0, 8(r1)
/* 800D1870 000CC770  81 81 00 0C */	lwz r12, 0xc(r1)
/* 800D1874 000CC774  B0 01 00 60 */	sth r0, 0x60(r1)
/* 800D1878 000CC778  81 61 00 40 */	lwz r11, 0x40(r1)
/* 800D187C 000CC77C  81 41 00 44 */	lwz r10, 0x44(r1)
/* 800D1880 000CC780  81 21 00 48 */	lwz r9, 0x48(r1)
/* 800D1884 000CC784  81 01 00 4C */	lwz r8, 0x4c(r1)
/* 800D1888 000CC788  80 E1 00 50 */	lwz r7, 0x50(r1)
/* 800D188C 000CC78C  80 C1 00 54 */	lwz r6, 0x54(r1)
/* 800D1890 000CC790  80 A1 00 58 */	lwz r5, 0x58(r1)
/* 800D1894 000CC794  80 81 00 60 */	lwz r4, 0x60(r1)
/* 800D1898 000CC798  80 61 00 68 */	lwz r3, 0x68(r1)
/* 800D189C 000CC79C  80 01 00 6C */	lwz r0, 0x6c(r1)
/* 800D18A0 000CC7A0  93 A1 00 5C */	stw r29, 0x5c(r1)
/* 800D18A4 000CC7A4  91 81 00 64 */	stw r12, 0x64(r1)
/* 800D18A8 000CC7A8  91 61 00 10 */	stw r11, 0x10(r1)
/* 800D18AC 000CC7AC  91 41 00 14 */	stw r10, 0x14(r1)
/* 800D18B0 000CC7B0  91 21 00 18 */	stw r9, 0x18(r1)
/* 800D18B4 000CC7B4  91 01 00 1C */	stw r8, 0x1c(r1)
/* 800D18B8 000CC7B8  90 E1 00 20 */	stw r7, 0x20(r1)
/* 800D18BC 000CC7BC  90 C1 00 24 */	stw r6, 0x24(r1)
/* 800D18C0 000CC7C0  90 A1 00 28 */	stw r5, 0x28(r1)
/* 800D18C4 000CC7C4  93 A1 00 2C */	stw r29, 0x2c(r1)
/* 800D18C8 000CC7C8  90 81 00 30 */	stw r4, 0x30(r1)
/* 800D18CC 000CC7CC  91 81 00 34 */	stw r12, 0x34(r1)
/* 800D18D0 000CC7D0  90 61 00 38 */	stw r3, 0x38(r1)
/* 800D18D4 000CC7D4  90 01 00 3C */	stw r0, 0x3c(r1)
/* 800D18D8 000CC7D8  48 01 FF E9 */	bl OSDisableInterrupts
/* 800D18DC 000CC7DC  7C 7F 1B 78 */	mr r31, r3
/* 800D18E0 000CC7E0  48 01 FF E1 */	bl OSDisableInterrupts
/* 800D18E4 000CC7E4  88 9E 00 00 */	lbz r4, 0(r30)
/* 800D18E8 000CC7E8  88 1E 00 01 */	lbz r0, 1(r30)
/* 800D18EC 000CC7EC  7C 04 00 50 */	subf r0, r4, r0
/* 800D18F0 000CC7F0  7C 1D 07 75 */	extsb. r29, r0
/* 800D18F4 000CC7F4  40 80 00 10 */	bge lbl_800D1904
/* 800D18F8 000CC7F8  80 1E 00 08 */	lwz r0, 8(r30)
/* 800D18FC 000CC7FC  7C 1D 02 14 */	add r0, r29, r0
/* 800D1900 000CC800  7C 1D 07 74 */	extsb r29, r0
lbl_800D1904:
/* 800D1904 000CC804  48 01 FF E5 */	bl OSRestoreInterrupts
/* 800D1908 000CC808  80 7E 00 08 */	lwz r3, 8(r30)
/* 800D190C 000CC80C  38 03 FF FF */	addi r0, r3, -1
/* 800D1910 000CC810  7C 00 E8 40 */	cmplw r0, r29
/* 800D1914 000CC814  40 82 00 14 */	bne lbl_800D1928
/* 800D1918 000CC818  7F E3 FB 78 */	mr r3, r31
/* 800D191C 000CC81C  48 01 FF CD */	bl OSRestoreInterrupts
/* 800D1920 000CC820  38 60 00 00 */	li r3, 0
/* 800D1924 000CC824  48 00 00 7C */	b lbl_800D19A0
lbl_800D1928:
/* 800D1928 000CC828  88 1E 00 01 */	lbz r0, 1(r30)
/* 800D192C 000CC82C  38 80 00 00 */	li r4, 0
/* 800D1930 000CC830  80 7E 00 04 */	lwz r3, 4(r30)
/* 800D1934 000CC834  38 A0 00 30 */	li r5, 0x30
/* 800D1938 000CC838  7C 00 07 74 */	extsb r0, r0
/* 800D193C 000CC83C  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800D1940 000CC840  7C 63 02 14 */	add r3, r3, r0
/* 800D1944 000CC844  4B F3 27 C1 */	bl memset
/* 800D1948 000CC848  88 1E 00 01 */	lbz r0, 1(r30)
/* 800D194C 000CC84C  38 81 00 10 */	addi r4, r1, 0x10
/* 800D1950 000CC850  80 7E 00 04 */	lwz r3, 4(r30)
/* 800D1954 000CC854  38 A0 00 30 */	li r5, 0x30
/* 800D1958 000CC858  7C 00 07 74 */	extsb r0, r0
/* 800D195C 000CC85C  1C 00 00 30 */	mulli r0, r0, 0x30
/* 800D1960 000CC860  7C 63 02 14 */	add r3, r3, r0
/* 800D1964 000CC864  4B F3 26 9D */	bl memcpy
/* 800D1968 000CC868  88 1E 00 01 */	lbz r0, 1(r30)
/* 800D196C 000CC86C  7F E3 FB 78 */	mr r3, r31
/* 800D1970 000CC870  80 9E 00 08 */	lwz r4, 8(r30)
/* 800D1974 000CC874  7C 06 07 74 */	extsb r6, r0
/* 800D1978 000CC878  38 84 FF FF */	addi r4, r4, -1
/* 800D197C 000CC87C  7C A4 30 50 */	subf r5, r4, r6
/* 800D1980 000CC880  38 06 00 01 */	addi r0, r6, 1
/* 800D1984 000CC884  7C 86 20 50 */	subf r4, r6, r4
/* 800D1988 000CC888  7C A4 20 F8 */	nor r4, r5, r4
/* 800D198C 000CC88C  7C 84 FE 70 */	srawi r4, r4, 0x1f
/* 800D1990 000CC890  7C 00 20 78 */	andc r0, r0, r4
/* 800D1994 000CC894  98 1E 00 01 */	stb r0, 1(r30)
/* 800D1998 000CC898  48 01 FF 51 */	bl OSRestoreInterrupts
/* 800D199C 000CC89C  38 60 00 01 */	li r3, 1
lbl_800D19A0:
/* 800D19A0 000CC8A0  80 01 00 84 */	lwz r0, 0x84(r1)
/* 800D19A4 000CC8A4  83 E1 00 7C */	lwz r31, 0x7c(r1)
/* 800D19A8 000CC8A8  83 C1 00 78 */	lwz r30, 0x78(r1)
/* 800D19AC 000CC8AC  83 A1 00 74 */	lwz r29, 0x74(r1)
/* 800D19B0 000CC8B0  7C 08 03 A6 */	mtlr r0
/* 800D19B4 000CC8B4  38 21 00 80 */	addi r1, r1, 0x80
/* 800D19B8 000CC8B8  4E 80 00 20 */	blr 

.global WPADiClearQueue
WPADiClearQueue:
/* 800D19BC 000CC8BC  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800D19C0 000CC8C0  7C 08 02 A6 */	mflr r0
/* 800D19C4 000CC8C4  90 01 00 14 */	stw r0, 0x14(r1)
/* 800D19C8 000CC8C8  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800D19CC 000CC8CC  93 C1 00 08 */	stw r30, 8(r1)
/* 800D19D0 000CC8D0  7C 7E 1B 78 */	mr r30, r3
/* 800D19D4 000CC8D4  48 01 FE ED */	bl OSDisableInterrupts
/* 800D19D8 000CC8D8  80 1E 00 08 */	lwz r0, 8(r30)
/* 800D19DC 000CC8DC  38 80 00 00 */	li r4, 0
/* 800D19E0 000CC8E0  7C 7F 1B 78 */	mr r31, r3
/* 800D19E4 000CC8E4  98 9E 00 00 */	stb r4, 0(r30)
/* 800D19E8 000CC8E8  1C A0 00 30 */	mulli r5, r0, 0x30
/* 800D19EC 000CC8EC  80 7E 00 04 */	lwz r3, 4(r30)
/* 800D19F0 000CC8F0  98 9E 00 01 */	stb r4, 1(r30)
/* 800D19F4 000CC8F4  38 80 00 00 */	li r4, 0
/* 800D19F8 000CC8F8  4B F3 27 0D */	bl memset
/* 800D19FC 000CC8FC  7F E3 FB 78 */	mr r3, r31
/* 800D1A00 000CC900  48 01 FE E9 */	bl OSRestoreInterrupts
/* 800D1A04 000CC904  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800D1A08 000CC908  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 800D1A0C 000CC90C  83 C1 00 08 */	lwz r30, 8(r1)
/* 800D1A10 000CC910  7C 08 03 A6 */	mtlr r0
/* 800D1A14 000CC914  38 21 00 10 */	addi r1, r1, 0x10
/* 800D1A18 000CC918  4E 80 00 20 */	blr 
