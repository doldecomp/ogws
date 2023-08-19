.include "macros.inc"

.section .sbss, "wa"
.balign 0x8
CommandInfoCounter:
	.skip 0x4
PauseFlag:
	.skip 0x4
PausingFlag:
	.skip 0x4
FatalErrorFlag:
	.skip 0x4
Canceling:
	.skip 0x4
ResumeFromHere:
	.skip 0x4
NumInternalRetry:
	.skip 0x4
FirstTimeInBootrom:
	.skip 0x4
Breaking:
	.skip 0x4
WaitingForCoverOpen:
	.skip 0x4
WaitingForCoverClose:
	.skip 0x4
MotorStopped:
	.skip 0x4
ChangedDisc:
	.skip 0x4
PreparingCover:
	.skip 0x4
.global __DVDLayoutFormat
__DVDLayoutFormat:
	.skip 0x4
DVDInitialized:
	.skip 0x4
__BS2DVDLowIntType:
	.skip 0x4
Prepared:
	.skip 0x4
BootGameInfo:
	.skip 0x4
PartInfo:
	.skip 0x4
GameToc:
	.skip 0x4
	.balign 8
LastResetEnd:
	.skip 0x8
MotorState:
	.skip 0x4
ResetRequired:
	.skip 0x4
LastError:
	.skip 0x4
CancelLastError:
	.skip 0x4
CancelCallback:
	.skip 0x4
CurrCommand:
	.skip 0x4
bootInfo:
	.skip 0x4
IDShouldBe:
	.skip 0x4
executing:
	.skip 0x4
.global LastState
LastState:
	.skip 0x4

.section .sdata, "wa"
.balign 0x8
.global __DVDVersion
__DVDVersion:
	.incbin "baserom.dol", 0x3C75F8, 0x4
autoInvalidation:
	.incbin "baserom.dol", 0x3C75FC, 0x4
checkOptionalCommand:
	.incbin "baserom.dol", 0x3C7600, 0x4
lbl_804BD984:
	.string "dvd.c"
	.balign 4
DmaCommand:
	.incbin "baserom.dol", 0x3C760C, 0x4

.section .data, "wa"
.balign 0x8
strings_803b5e28:
	.incbin "baserom.dol", 0x3B1F28, 0x48
strings_803B5E70:
	.incbin "baserom.dol", 0x3B1F70, 0x34
lbl_803B5EA4: # jtbl
	.incbin "baserom.dol", 0x3B1FA4, 0x9C
lbl_803B5F40: # jtbl
	.incbin "baserom.dol", 0x3B2040, 0x9C
ImmCommand:
	.long -1
	.long -1
	.long -1
lbl_803B5FE8: # jtbl
	.incbin "baserom.dol", 0x3B20E8, 0x98
lbl_803B6080: # jtbl
	.incbin "baserom.dol", 0x3B2180, 0x38

.section .bss, "wa"
.balign 0x8
BB2: # ALIGN(32)
    .balign 32
	.skip 0x20
DummyCommandBlock:
	.skip 0x30
FatalAlarm:
	.skip 0x30
CoverAlarm:
	.skip 0x30
.balign 32
CurrDiskID: # ALIGN(32)
    .skip 0x20
.balign 32
GameTocBuffer: # ALIGN(32)
	.skip 0x20
.balign 32
PartInfoBuffer: # ALIGN(32)
    .skip 0x20
.balign 64
TmdBuffer: # ALIGN(64)
	.skip 0x4A00
ResetAlarm:
	.skip 0x30
.global __DVDStopMotorCommandBlock
__DVDStopMotorCommandBlock:
	.skip 0x30
.global __DVDRestartMotorCommandBlock
__DVDRestartMotorCommandBlock:
	# UNUSED, will need to stop deadstrip
    .skip 0x30

.section .text, "ax"
.global StampCommand
StampCommand:
/* 8013A068 00134F68  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8013A06C 00134F6C  7C 08 02 A6 */	mflr r0
/* 8013A070 00134F70  90 01 00 24 */	stw r0, 0x24(r1)
/* 8013A074 00134F74  39 61 00 20 */	addi r11, r1, 0x20
/* 8013A078 00134F78  4B F7 7C CD */	bl _savegpr_27
/* 8013A07C 00134F7C  7C 7B 1B 78 */	mr r27, r3
/* 8013A080 00134F80  7C 9C 23 78 */	mr r28, r4
/* 8013A084 00134F84  7C BD 2B 78 */	mr r29, r5
/* 8013A088 00134F88  4B FB 78 39 */	bl OSDisableInterrupts
/* 8013A08C 00134F8C  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013A090 00134F90  7C 7F 1B 78 */	mr r31, r3
/* 8013A094 00134F94  28 00 00 05 */	cmplwi r0, 5
/* 8013A098 00134F98  41 80 00 0C */	blt lbl_8013A0A4
/* 8013A09C 00134F9C  38 00 00 00 */	li r0, 0
/* 8013A0A0 00134FA0  90 0D 9F 98 */	stw r0, CommandInfoCounter-_SDA_BASE_(r13)
lbl_8013A0A4:
/* 8013A0A4 00134FA4  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013A0A8 00134FA8  3F C0 80 48 */	lis r30, __ErrorInfo@ha
/* 8013A0AC 00134FAC  80 6D 9F 98 */	lwz r3, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013A0B0 00134FB0  3B DE A2 20 */	addi r30, r30, __ErrorInfo@l
/* 8013A0B4 00134FB4  1C 80 00 14 */	mulli r4, r0, 0x14
/* 8013A0B8 00134FB8  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013A0BC 00134FBC  1C 63 00 14 */	mulli r3, r3, 0x14
/* 8013A0C0 00134FC0  7C 9E 22 14 */	add r4, r30, r4
/* 8013A0C4 00134FC4  93 64 00 1C */	stw r27, 0x1c(r4)
/* 8013A0C8 00134FC8  7C 7E 1A 14 */	add r3, r30, r3
/* 8013A0CC 00134FCC  1C 00 00 14 */	mulli r0, r0, 0x14
/* 8013A0D0 00134FD0  93 83 00 20 */	stw r28, 0x20(r3)
/* 8013A0D4 00134FD4  7C 7E 02 14 */	add r3, r30, r0
/* 8013A0D8 00134FD8  93 A3 00 24 */	stw r29, 0x24(r3)
/* 8013A0DC 00134FDC  4B FB B5 41 */	bl OSGetTick
/* 8013A0E0 00134FE0  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013A0E4 00134FE4  80 8D 9F 98 */	lwz r4, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013A0E8 00134FE8  1C A0 00 14 */	mulli r5, r0, 0x14
/* 8013A0EC 00134FEC  38 04 00 01 */	addi r0, r4, 1
/* 8013A0F0 00134FF0  90 0D 9F 98 */	stw r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013A0F4 00134FF4  7C 9E 2A 14 */	add r4, r30, r5
/* 8013A0F8 00134FF8  90 64 00 2C */	stw r3, 0x2c(r4)
/* 8013A0FC 00134FFC  7F E3 FB 78 */	mr r3, r31
/* 8013A100 00135000  4B FB 77 E9 */	bl OSRestoreInterrupts
/* 8013A104 00135004  39 61 00 20 */	addi r11, r1, 0x20
/* 8013A108 00135008  4B F7 7C 89 */	bl _restgpr_27
/* 8013A10C 0013500C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8013A110 00135010  7C 08 03 A6 */	mtlr r0
/* 8013A114 00135014  38 21 00 20 */	addi r1, r1, 0x20
/* 8013A118 00135018  4E 80 00 20 */	blr 

.global defaultOptionalCommandChecker
defaultOptionalCommandChecker:
/* 8013A11C 0013501C  4E 80 00 20 */	blr 

.global DVDInit
DVDInit:
/* 8013A120 00135020  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8013A124 00135024  7C 08 02 A6 */	mflr r0
/* 8013A128 00135028  90 01 00 14 */	stw r0, 0x14(r1)
/* 8013A12C 0013502C  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8013A130 00135030  80 0D 9F D4 */	lwz r0, DVDInitialized-_SDA_BASE_(r13)
/* 8013A134 00135034  2C 00 00 00 */	cmpwi r0, 0
/* 8013A138 00135038  40 82 00 B4 */	bne lbl_8013A1EC
/* 8013A13C 0013503C  80 6D 85 F8 */	lwz r3, __DVDVersion-_SDA_BASE_(r13)
/* 8013A140 00135040  4B FB 2F 01 */	bl OSRegisterVersion
/* 8013A144 00135044  3B E0 00 01 */	li r31, 1
/* 8013A148 00135048  93 ED 9F D4 */	stw r31, DVDInitialized-_SDA_BASE_(r13)
/* 8013A14C 0013504C  48 00 4B 91 */	bl DVDLowInit
/* 8013A150 00135050  4B FF F4 D1 */	bl __DVDFSInit
/* 8013A154 00135054  48 00 42 89 */	bl __DVDClearWaitingQueue
/* 8013A158 00135058  3C 00 80 00 */	lis r0, 0x8000
/* 8013A15C 0013505C  38 60 00 00 */	li r3, 0
/* 8013A160 00135060  90 6D 9F F8 */	stw r3, MotorState-_SDA_BASE_(r13)
/* 8013A164 00135064  38 6D 9F 80 */	addi r3, r13, __DVDThreadQueue-_SDA_BASE_
/* 8013A168 00135068  90 0D A0 10 */	stw r0, bootInfo-_SDA_BASE_(r13)
/* 8013A16C 0013506C  90 0D A0 14 */	stw r0, IDShouldBe-_SDA_BASE_(r13)
/* 8013A170 00135070  4B FB 9F D9 */	bl OSInitThreadQueue
/* 8013A174 00135074  48 00 62 65 */	bl DVDLowUnmaskStatusInterrupts
/* 8013A178 00135078  48 00 62 69 */	bl DVDLowMaskCoverInterrupt
/* 8013A17C 0013507C  80 6D A0 10 */	lwz r3, bootInfo-_SDA_BASE_(r13)
/* 8013A180 00135080  80 63 00 20 */	lwz r3, 0x20(r3)
/* 8013A184 00135084  3C 03 1A E0 */	addis r0, r3, 0x1ae0
/* 8013A188 00135088  28 00 7C 22 */	cmplwi r0, 0x7c22
/* 8013A18C 0013508C  41 82 00 14 */	beq lbl_8013A1A0
/* 8013A190 00135090  3C 03 F2 EB */	addis r0, r3, 0xf2eb
/* 8013A194 00135094  28 00 EA 5E */	cmplwi r0, 0xea5e
/* 8013A198 00135098  41 82 00 08 */	beq lbl_8013A1A0
/* 8013A19C 0013509C  93 ED 9F B4 */	stw r31, FirstTimeInBootrom-_SDA_BASE_(r13)
lbl_8013A1A0:
/* 8013A1A0 001350A0  3F E0 80 48 */	lis r31, __ErrorInfo@ha
/* 8013A1A4 001350A4  38 80 00 00 */	li r4, 0
/* 8013A1A8 001350A8  38 7F A2 20 */	addi r3, r31, __ErrorInfo@l
/* 8013A1AC 001350AC  38 A0 00 80 */	li r5, 0x80
/* 8013A1B0 001350B0  4B EC 9F 55 */	bl memset
/* 8013A1B4 001350B4  38 7F A2 20 */	addi r3, r31, -24032
/* 8013A1B8 001350B8  3C 80 80 00 */	lis r4, 0x8000
/* 8013A1BC 001350BC  38 A0 00 04 */	li r5, 4
/* 8013A1C0 001350C0  4B EC 9E 41 */	bl memcpy
/* 8013A1C4 001350C4  3C C0 80 00 */	lis r6, 0x80000006@ha
/* 8013A1C8 001350C8  38 BF A2 20 */	addi r5, r31, -24032
/* 8013A1CC 001350CC  88 86 00 06 */	lbz r4, 0x80000006@l(r6)
/* 8013A1D0 001350D0  38 00 00 00 */	li r0, 0
/* 8013A1D4 001350D4  38 60 00 01 */	li r3, 1
/* 8013A1D8 001350D8  98 85 00 04 */	stb r4, 4(r5)
/* 8013A1DC 001350DC  88 86 00 07 */	lbz r4, 7(r6)
/* 8013A1E0 001350E0  98 85 00 05 */	stb r4, 5(r5)
/* 8013A1E4 001350E4  90 0D 9F D0 */	stw r0, __DVDLayoutFormat-_SDA_BASE_(r13)
/* 8013A1E8 001350E8  48 00 48 F9 */	bl DVDSetAutoFatalMessaging
lbl_8013A1EC:
/* 8013A1EC 001350EC  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8013A1F0 001350F0  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8013A1F4 001350F4  7C 08 03 A6 */	mtlr r0
/* 8013A1F8 001350F8  38 21 00 10 */	addi r1, r1, 0x10
/* 8013A1FC 001350FC  4E 80 00 20 */	blr 

.global stateReadingFST
stateReadingFST:
/* 8013A200 00135100  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8013A204 00135104  7C 08 02 A6 */	mflr r0
/* 8013A208 00135108  3C A0 80 14 */	lis r5, stateReadingFST@ha
/* 8013A20C 0013510C  3C 60 80 47 */	lis r3, BB2@ha
/* 8013A210 00135110  90 01 00 24 */	stw r0, 0x24(r1)
/* 8013A214 00135114  38 A5 A2 00 */	addi r5, r5, stateReadingFST@l
/* 8013A218 00135118  38 63 54 C0 */	addi r3, r3, BB2@l
/* 8013A21C 0013511C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8013A220 00135120  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8013A224 00135124  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8013A228 00135128  93 81 00 10 */	stw r28, 0x10(r1)
/* 8013A22C 0013512C  80 8D A0 10 */	lwz r4, bootInfo-_SDA_BASE_(r13)
/* 8013A230 00135130  90 AD A0 1C */	stw r5, LastState-_SDA_BASE_(r13)
/* 8013A234 00135134  80 03 00 08 */	lwz r0, 8(r3)
/* 8013A238 00135138  80 64 00 3C */	lwz r3, 0x3c(r4)
/* 8013A23C 0013513C  7C 03 00 40 */	cmplw r3, r0
/* 8013A240 00135140  40 80 00 1C */	bge lbl_8013A25C
/* 8013A244 00135144  3C A0 80 3B */	lis r5, strings_803B5E70@ha
/* 8013A248 00135148  38 6D 86 04 */	addi r3, r13, lbl_804BD984-_SDA_BASE_
/* 8013A24C 0013514C  38 A5 5E 70 */	addi r5, r5, strings_803B5E70@l
/* 8013A250 00135150  38 80 04 0B */	li r4, 0x40b
/* 8013A254 00135154  4C C6 31 82 */	crclr 6
/* 8013A258 00135158  4B FB 4D 51 */	bl OSPanic
lbl_8013A25C:
/* 8013A25C 0013515C  38 60 00 00 */	li r3, 0
/* 8013A260 00135160  48 00 61 89 */	bl DVDLowClearCoverInterrupt
/* 8013A264 00135164  80 6D 9F D0 */	lwz r3, __DVDLayoutFormat-_SDA_BASE_(r13)
/* 8013A268 00135168  3C C0 80 47 */	lis r6, BB2@ha
/* 8013A26C 0013516C  38 C6 54 C0 */	addi r6, r6, BB2@l
/* 8013A270 00135170  80 0D 9F D0 */	lwz r0, __DVDLayoutFormat-_SDA_BASE_(r13)
/* 8013A274 00135174  7C 63 18 F8 */	nor r3, r3, r3
/* 8013A278 00135178  80 A6 00 08 */	lwz r5, 8(r6)
/* 8013A27C 0013517C  54 64 07 BC */	rlwinm r4, r3, 0, 0x1e, 0x1e
/* 8013A280 00135180  80 66 00 04 */	lwz r3, 4(r6)
/* 8013A284 00135184  7C A4 20 30 */	slw r4, r5, r4
/* 8013A288 00135188  38 84 00 1F */	addi r4, r4, 0x1f
/* 8013A28C 0013518C  7C 7D 04 30 */	srw r29, r3, r0
/* 8013A290 00135190  54 9C 00 34 */	rlwinm r28, r4, 0, 0, 0x1a
/* 8013A294 00135194  4B FB 76 2D */	bl OSDisableInterrupts
/* 8013A298 00135198  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013A29C 0013519C  7C 7F 1B 78 */	mr r31, r3
/* 8013A2A0 001351A0  28 00 00 05 */	cmplwi r0, 5
/* 8013A2A4 001351A4  41 80 00 0C */	blt lbl_8013A2B0
/* 8013A2A8 001351A8  38 00 00 00 */	li r0, 0
/* 8013A2AC 001351AC  90 0D 9F 98 */	stw r0, CommandInfoCounter-_SDA_BASE_(r13)
lbl_8013A2B0:
/* 8013A2B0 001351B0  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013A2B4 001351B4  3F C0 80 48 */	lis r30, __ErrorInfo@ha
/* 8013A2B8 001351B8  80 6D 9F 98 */	lwz r3, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013A2BC 001351BC  3B DE A2 20 */	addi r30, r30, __ErrorInfo@l
/* 8013A2C0 001351C0  1C 80 00 14 */	mulli r4, r0, 0x14
/* 8013A2C4 001351C4  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013A2C8 001351C8  38 A0 00 01 */	li r5, 1
/* 8013A2CC 001351CC  1C 63 00 14 */	mulli r3, r3, 0x14
/* 8013A2D0 001351D0  7C 9E 22 14 */	add r4, r30, r4
/* 8013A2D4 001351D4  90 A4 00 1C */	stw r5, 0x1c(r4)
/* 8013A2D8 001351D8  7C 7E 1A 14 */	add r3, r30, r3
/* 8013A2DC 001351DC  1C 00 00 14 */	mulli r0, r0, 0x14
/* 8013A2E0 001351E0  93 A3 00 20 */	stw r29, 0x20(r3)
/* 8013A2E4 001351E4  7C 7E 02 14 */	add r3, r30, r0
/* 8013A2E8 001351E8  93 83 00 24 */	stw r28, 0x24(r3)
/* 8013A2EC 001351EC  4B FB B3 31 */	bl OSGetTick
/* 8013A2F0 001351F0  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013A2F4 001351F4  80 8D 9F 98 */	lwz r4, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013A2F8 001351F8  1C A0 00 14 */	mulli r5, r0, 0x14
/* 8013A2FC 001351FC  38 04 00 01 */	addi r0, r4, 1
/* 8013A300 00135200  90 0D 9F 98 */	stw r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013A304 00135204  7C 9E 2A 14 */	add r4, r30, r5
/* 8013A308 00135208  90 64 00 2C */	stw r3, 0x2c(r4)
/* 8013A30C 0013520C  7F E3 FB 78 */	mr r3, r31
/* 8013A310 00135210  4B FB 75 D9 */	bl OSRestoreInterrupts
/* 8013A314 00135214  80 0D 9F D0 */	lwz r0, __DVDLayoutFormat-_SDA_BASE_(r13)
/* 8013A318 00135218  3C 80 80 47 */	lis r4, BB2@ha
/* 8013A31C 0013521C  38 84 54 C0 */	addi r4, r4, BB2@l
/* 8013A320 00135220  3C C0 80 14 */	lis r6, cbForStateReadingFST@ha
/* 8013A324 00135224  7C 00 00 F8 */	nor r0, r0, r0
/* 8013A328 00135228  80 64 00 08 */	lwz r3, 8(r4)
/* 8013A32C 0013522C  54 00 07 BC */	rlwinm r0, r0, 0, 0x1e, 0x1e
/* 8013A330 00135230  80 ED A0 10 */	lwz r7, bootInfo-_SDA_BASE_(r13)
/* 8013A334 00135234  7C 63 00 30 */	slw r3, r3, r0
/* 8013A338 00135238  80 A4 00 04 */	lwz r5, 4(r4)
/* 8013A33C 0013523C  38 83 00 1F */	addi r4, r3, 0x1f
/* 8013A340 00135240  80 0D 9F D0 */	lwz r0, __DVDLayoutFormat-_SDA_BASE_(r13)
/* 8013A344 00135244  80 67 00 38 */	lwz r3, 0x38(r7)
/* 8013A348 00135248  54 84 00 34 */	rlwinm r4, r4, 0, 0, 0x1a
/* 8013A34C 0013524C  7C A5 04 30 */	srw r5, r5, r0
/* 8013A350 00135250  38 C6 A3 78 */	addi r6, r6, cbForStateReadingFST@l
/* 8013A354 00135254  48 00 5B D5 */	bl DVDLowRead
/* 8013A358 00135258  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8013A35C 0013525C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8013A360 00135260  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8013A364 00135264  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8013A368 00135268  83 81 00 10 */	lwz r28, 0x10(r1)
/* 8013A36C 0013526C  7C 08 03 A6 */	mtlr r0
/* 8013A370 00135270  38 21 00 20 */	addi r1, r1, 0x20
/* 8013A374 00135274  4E 80 00 20 */	blr 

.global cbForStateReadingFST
cbForStateReadingFST:
/* 8013A378 00135278  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8013A37C 0013527C  7C 08 02 A6 */	mflr r0
/* 8013A380 00135280  90 01 00 14 */	stw r0, 0x14(r1)
/* 8013A384 00135284  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8013A388 00135288  93 C1 00 08 */	stw r30, 8(r1)
/* 8013A38C 0013528C  7C 7E 1B 78 */	mr r30, r3
/* 8013A390 00135290  4B FB 75 31 */	bl OSDisableInterrupts
/* 8013A394 00135294  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013A398 00135298  2C 00 00 00 */	cmpwi r0, 0
/* 8013A39C 0013529C  40 82 00 14 */	bne lbl_8013A3B0
/* 8013A3A0 001352A0  3C 80 80 48 */	lis r4, __ErrorInfo@ha
/* 8013A3A4 001352A4  38 84 A2 20 */	addi r4, r4, __ErrorInfo@l
/* 8013A3A8 001352A8  93 C4 00 78 */	stw r30, 0x78(r4)
/* 8013A3AC 001352AC  48 00 00 1C */	b lbl_8013A3C8
lbl_8013A3B0:
/* 8013A3B0 001352B0  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013A3B4 001352B4  3C 80 80 48 */	lis r4, __ErrorInfo@ha
/* 8013A3B8 001352B8  38 84 A2 20 */	addi r4, r4, __ErrorInfo@l
/* 8013A3BC 001352BC  1C 00 00 14 */	mulli r0, r0, 0x14
/* 8013A3C0 001352C0  7C 84 02 14 */	add r4, r4, r0
/* 8013A3C4 001352C4  93 C4 00 14 */	stw r30, 0x14(r4)
lbl_8013A3C8:
/* 8013A3C8 001352C8  4B FB 75 21 */	bl OSRestoreInterrupts
/* 8013A3CC 001352CC  28 1E 00 10 */	cmplwi r30, 0x10
/* 8013A3D0 001352D0  40 82 00 1C */	bne lbl_8013A3EC
/* 8013A3D4 001352D4  3C 60 01 23 */	lis r3, 0x01234568@ha
/* 8013A3D8 001352D8  3C 80 80 14 */	lis r4, cbForStoreErrorCode2@ha
/* 8013A3DC 001352DC  38 63 45 68 */	addi r3, r3, 0x01234568@l
/* 8013A3E0 001352E0  38 84 A6 24 */	addi r4, r4, cbForStoreErrorCode2@l
/* 8013A3E4 001352E4  48 00 44 B5 */	bl __DVDStoreErrorCode
/* 8013A3E8 001352E8  48 00 00 FC */	b lbl_8013A4E4
lbl_8013A3EC:
/* 8013A3EC 001352EC  28 1E 00 20 */	cmplwi r30, 0x20
/* 8013A3F0 001352F0  40 82 00 1C */	bne lbl_8013A40C
/* 8013A3F4 001352F4  3C 60 01 23 */	lis r3, 0x01234569@ha
/* 8013A3F8 001352F8  3C 80 80 14 */	lis r4, cbForStoreErrorCode2@ha
/* 8013A3FC 001352FC  38 63 45 69 */	addi r3, r3, 0x01234569@l
/* 8013A400 00135300  38 84 A6 24 */	addi r4, r4, cbForStoreErrorCode2@l
/* 8013A404 00135304  48 00 44 95 */	bl __DVDStoreErrorCode
/* 8013A408 00135308  48 00 00 DC */	b lbl_8013A4E4
lbl_8013A40C:
/* 8013A40C 0013530C  57 C0 07 FF */	clrlwi. r0, r30, 0x1f
/* 8013A410 00135310  41 82 00 44 */	beq lbl_8013A454
/* 8013A414 00135314  3B C0 00 00 */	li r30, 0
/* 8013A418 00135318  93 CD 9F B0 */	stw r30, NumInternalRetry-_SDA_BASE_(r13)
/* 8013A41C 0013531C  4B FF F2 05 */	bl __DVDFSInit
/* 8013A420 00135320  3C 60 80 47 */	lis r3, DummyCommandBlock@ha
/* 8013A424 00135324  80 8D A0 18 */	lwz r4, executing-_SDA_BASE_(r13)
/* 8013A428 00135328  38 63 54 E0 */	addi r3, r3, DummyCommandBlock@l
/* 8013A42C 0013532C  90 6D A0 18 */	stw r3, executing-_SDA_BASE_(r13)
/* 8013A430 00135330  93 C4 00 0C */	stw r30, 0xc(r4)
/* 8013A434 00135334  81 84 00 28 */	lwz r12, 0x28(r4)
/* 8013A438 00135338  2C 0C 00 00 */	cmpwi r12, 0
/* 8013A43C 0013533C  41 82 00 10 */	beq lbl_8013A44C
/* 8013A440 00135340  38 60 00 00 */	li r3, 0
/* 8013A444 00135344  7D 89 03 A6 */	mtctr r12
/* 8013A448 00135348  4E 80 04 21 */	bctrl 
lbl_8013A44C:
/* 8013A44C 0013534C  48 00 25 A1 */	bl stateReady
/* 8013A450 00135350  48 00 00 94 */	b lbl_8013A4E4
lbl_8013A454:
/* 8013A454 00135354  4B FB 74 6D */	bl OSDisableInterrupts
/* 8013A458 00135358  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013A45C 0013535C  7C 7F 1B 78 */	mr r31, r3
/* 8013A460 00135360  28 00 00 05 */	cmplwi r0, 5
/* 8013A464 00135364  41 80 00 0C */	blt lbl_8013A470
/* 8013A468 00135368  38 00 00 00 */	li r0, 0
/* 8013A46C 0013536C  90 0D 9F 98 */	stw r0, CommandInfoCounter-_SDA_BASE_(r13)
lbl_8013A470:
/* 8013A470 00135370  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013A474 00135374  3F C0 80 48 */	lis r30, __ErrorInfo@ha
/* 8013A478 00135378  80 6D 9F 98 */	lwz r3, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013A47C 0013537C  3B DE A2 20 */	addi r30, r30, __ErrorInfo@l
/* 8013A480 00135380  1C A0 00 14 */	mulli r5, r0, 0x14
/* 8013A484 00135384  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013A488 00135388  38 C0 00 27 */	li r6, 0x27
/* 8013A48C 0013538C  38 80 00 00 */	li r4, 0
/* 8013A490 00135390  1C 63 00 14 */	mulli r3, r3, 0x14
/* 8013A494 00135394  7C BE 2A 14 */	add r5, r30, r5
/* 8013A498 00135398  90 C5 00 1C */	stw r6, 0x1c(r5)
/* 8013A49C 0013539C  7C 7E 1A 14 */	add r3, r30, r3
/* 8013A4A0 001353A0  1C 00 00 14 */	mulli r0, r0, 0x14
/* 8013A4A4 001353A4  90 83 00 20 */	stw r4, 0x20(r3)
/* 8013A4A8 001353A8  7C 7E 02 14 */	add r3, r30, r0
/* 8013A4AC 001353AC  90 83 00 24 */	stw r4, 0x24(r3)
/* 8013A4B0 001353B0  4B FB B1 6D */	bl OSGetTick
/* 8013A4B4 001353B4  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013A4B8 001353B8  80 8D 9F 98 */	lwz r4, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013A4BC 001353BC  1C A0 00 14 */	mulli r5, r0, 0x14
/* 8013A4C0 001353C0  38 04 00 01 */	addi r0, r4, 1
/* 8013A4C4 001353C4  90 0D 9F 98 */	stw r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013A4C8 001353C8  7C 9E 2A 14 */	add r4, r30, r5
/* 8013A4CC 001353CC  90 64 00 2C */	stw r3, 0x2c(r4)
/* 8013A4D0 001353D0  7F E3 FB 78 */	mr r3, r31
/* 8013A4D4 001353D4  4B FB 74 15 */	bl OSRestoreInterrupts
/* 8013A4D8 001353D8  3C 60 80 14 */	lis r3, cbForStateGettingError@ha
/* 8013A4DC 001353DC  38 63 A8 18 */	addi r3, r3, cbForStateGettingError@l
/* 8013A4E0 001353E0  48 00 54 45 */	bl DVDLowRequestError
lbl_8013A4E4:
/* 8013A4E4 001353E4  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8013A4E8 001353E8  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8013A4EC 001353EC  83 C1 00 08 */	lwz r30, 8(r1)
/* 8013A4F0 001353F0  7C 08 03 A6 */	mtlr r0
/* 8013A4F4 001353F4  38 21 00 10 */	addi r1, r1, 0x10
/* 8013A4F8 001353F8  4E 80 00 20 */	blr 

.global FatalAlarmHandler
FatalAlarmHandler:
/* 8013A4FC 001353FC  48 00 46 54 */	b __DVDPrintFatalMessage

.global cbForStateError
cbForStateError:
/* 8013A500 00135400  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8013A504 00135404  7C 08 02 A6 */	mflr r0
/* 8013A508 00135408  90 01 00 14 */	stw r0, 0x14(r1)
/* 8013A50C 0013540C  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8013A510 00135410  7C 7F 1B 78 */	mr r31, r3
/* 8013A514 00135414  48 00 46 29 */	bl __DVDGetAutoFatalMessaging
/* 8013A518 00135418  2C 03 00 00 */	cmpwi r3, 0
/* 8013A51C 0013541C  41 82 00 2C */	beq lbl_8013A548
/* 8013A520 00135420  3F E0 80 47 */	lis r31, FatalAlarm@ha
/* 8013A524 00135424  38 7F 55 10 */	addi r3, r31, FatalAlarm@l
/* 8013A528 00135428  4B FB 2B ED */	bl OSCreateAlarm
/* 8013A52C 0013542C  3C E0 80 14 */	lis r7, FatalAlarmHandler@ha
/* 8013A530 00135430  38 7F 55 10 */	addi r3, r31, 0x5510
/* 8013A534 00135434  38 E7 A4 FC */	addi r7, r7, FatalAlarmHandler@l
/* 8013A538 00135438  38 C0 00 01 */	li r6, 1
/* 8013A53C 0013543C  38 A0 00 00 */	li r5, 0
/* 8013A540 00135440  4B FB 2E 35 */	bl OSSetAlarm
/* 8013A544 00135444  48 00 00 B8 */	b lbl_8013A5FC
lbl_8013A548:
/* 8013A548 00135448  80 6D A0 18 */	lwz r3, executing-_SDA_BASE_(r13)
/* 8013A54C 0013544C  38 00 FF FF */	li r0, -1
/* 8013A550 00135450  28 1F 00 10 */	cmplwi r31, 0x10
/* 8013A554 00135454  90 03 00 0C */	stw r0, 0xc(r3)
/* 8013A558 00135458  40 82 00 1C */	bne lbl_8013A574
/* 8013A55C 0013545C  3C 60 01 23 */	lis r3, 0x01234568@ha
/* 8013A560 00135460  3C 80 80 14 */	lis r4, cbForStoreErrorCode2@ha
/* 8013A564 00135464  38 63 45 68 */	addi r3, r3, 0x01234568@l
/* 8013A568 00135468  38 84 A6 24 */	addi r4, r4, cbForStoreErrorCode2@l
/* 8013A56C 0013546C  48 00 43 2D */	bl __DVDStoreErrorCode
/* 8013A570 00135470  48 00 00 8C */	b lbl_8013A5FC
lbl_8013A574:
/* 8013A574 00135474  28 1F 00 20 */	cmplwi r31, 0x20
/* 8013A578 00135478  40 82 00 1C */	bne lbl_8013A594
/* 8013A57C 0013547C  3C 60 01 23 */	lis r3, 0x01234569@ha
/* 8013A580 00135480  3C 80 80 14 */	lis r4, cbForStoreErrorCode2@ha
/* 8013A584 00135484  38 63 45 69 */	addi r3, r3, 0x01234569@l
/* 8013A588 00135488  38 84 A6 24 */	addi r4, r4, cbForStoreErrorCode2@l
/* 8013A58C 0013548C  48 00 43 0D */	bl __DVDStoreErrorCode
/* 8013A590 00135490  48 00 00 6C */	b lbl_8013A5FC
lbl_8013A594:
/* 8013A594 00135494  3C 60 80 47 */	lis r3, DummyCommandBlock@ha
/* 8013A598 00135498  83 ED A0 18 */	lwz r31, executing-_SDA_BASE_(r13)
/* 8013A59C 0013549C  38 63 54 E0 */	addi r3, r3, DummyCommandBlock@l
/* 8013A5A0 001354A0  38 00 00 01 */	li r0, 1
/* 8013A5A4 001354A4  90 0D 9F A4 */	stw r0, FatalErrorFlag-_SDA_BASE_(r13)
/* 8013A5A8 001354A8  90 6D A0 18 */	stw r3, executing-_SDA_BASE_(r13)
/* 8013A5AC 001354AC  81 9F 00 28 */	lwz r12, 0x28(r31)
/* 8013A5B0 001354B0  2C 0C 00 00 */	cmpwi r12, 0
/* 8013A5B4 001354B4  41 82 00 14 */	beq lbl_8013A5C8
/* 8013A5B8 001354B8  7F E4 FB 78 */	mr r4, r31
/* 8013A5BC 001354BC  38 60 FF FF */	li r3, -1
/* 8013A5C0 001354C0  7D 89 03 A6 */	mtctr r12
/* 8013A5C4 001354C4  4E 80 04 21 */	bctrl 
lbl_8013A5C8:
/* 8013A5C8 001354C8  80 0D 9F A8 */	lwz r0, Canceling-_SDA_BASE_(r13)
/* 8013A5CC 001354CC  2C 00 00 00 */	cmpwi r0, 0
/* 8013A5D0 001354D0  41 82 00 28 */	beq lbl_8013A5F8
/* 8013A5D4 001354D4  81 8D A0 08 */	lwz r12, CancelCallback-_SDA_BASE_(r13)
/* 8013A5D8 001354D8  38 00 00 00 */	li r0, 0
/* 8013A5DC 001354DC  90 0D 9F A8 */	stw r0, Canceling-_SDA_BASE_(r13)
/* 8013A5E0 001354E0  2C 0C 00 00 */	cmpwi r12, 0
/* 8013A5E4 001354E4  41 82 00 14 */	beq lbl_8013A5F8
/* 8013A5E8 001354E8  7F E4 FB 78 */	mr r4, r31
/* 8013A5EC 001354EC  38 60 00 00 */	li r3, 0
/* 8013A5F0 001354F0  7D 89 03 A6 */	mtctr r12
/* 8013A5F4 001354F4  4E 80 04 21 */	bctrl 
lbl_8013A5F8:
/* 8013A5F8 001354F8  48 00 23 F5 */	bl stateReady
lbl_8013A5FC:
/* 8013A5FC 001354FC  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8013A600 00135500  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8013A604 00135504  7C 08 03 A6 */	mtlr r0
/* 8013A608 00135508  38 21 00 10 */	addi r1, r1, 0x10
/* 8013A60C 0013550C  4E 80 00 20 */	blr 

cbForStoreErrorCode1:
/* 8013A610 00135510  3C A0 80 14 */	lis r5, cbForStateError@ha
/* 8013A614 00135514  38 60 00 00 */	li r3, 0
/* 8013A618 00135518  38 A5 A5 00 */	addi r5, r5, cbForStateError@l
/* 8013A61C 0013551C  38 80 00 00 */	li r4, 0
/* 8013A620 00135520  48 00 50 08 */	b DVDLowStopMotor

.global cbForStoreErrorCode2
cbForStoreErrorCode2:
/* 8013A624 00135524  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8013A628 00135528  7C 08 02 A6 */	mflr r0
/* 8013A62C 0013552C  38 60 00 00 */	li r3, 0
/* 8013A630 00135530  90 01 00 14 */	stw r0, 0x14(r1)
/* 8013A634 00135534  48 00 54 59 */	bl DVDLowSetSpinupFlag
/* 8013A638 00135538  3C 60 80 14 */	lis r3, cbForStateError@ha
/* 8013A63C 0013553C  38 63 A5 00 */	addi r3, r3, cbForStateError@l
/* 8013A640 00135540  48 00 54 59 */	bl DVDLowReset
/* 8013A644 00135544  38 00 00 00 */	li r0, 0
/* 8013A648 00135548  90 0D 9F FC */	stw r0, ResetRequired-_SDA_BASE_(r13)
/* 8013A64C 0013554C  90 0D 9F AC */	stw r0, ResumeFromHere-_SDA_BASE_(r13)
/* 8013A650 00135550  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8013A654 00135554  7C 08 03 A6 */	mtlr r0
/* 8013A658 00135558  38 21 00 10 */	addi r1, r1, 0x10
/* 8013A65C 0013555C  4E 80 00 20 */	blr 

.global CategorizeError
CategorizeError:
/* 8013A660 00135560  3C 03 FF FE */	addis r0, r3, 0xfffe
/* 8013A664 00135564  28 00 04 00 */	cmplwi r0, 0x400
/* 8013A668 00135568  40 82 00 10 */	bne lbl_8013A678
/* 8013A66C 0013556C  90 6D A0 00 */	stw r3, LastError-_SDA_BASE_(r13)
/* 8013A670 00135570  38 60 00 01 */	li r3, 1
/* 8013A674 00135574  4E 80 00 20 */	blr 
lbl_8013A678:
/* 8013A678 00135578  54 64 02 3E */	clrlwi r4, r3, 8
/* 8013A67C 0013557C  3C 04 FF FA */	addis r0, r4, 0xfffa
/* 8013A680 00135580  28 00 28 00 */	cmplwi r0, 0x2800
/* 8013A684 00135584  41 82 00 28 */	beq lbl_8013A6AC
/* 8013A688 00135588  3C 04 FF FE */	addis r0, r4, 0xfffe
/* 8013A68C 0013558C  28 00 3A 00 */	cmplwi r0, 0x3a00
/* 8013A690 00135590  41 82 00 1C */	beq lbl_8013A6AC
/* 8013A694 00135594  3C 64 FF FB */	addis r3, r4, 0xfffb
/* 8013A698 00135598  28 03 30 00 */	cmplwi r3, 0x3000
/* 8013A69C 0013559C  41 82 00 10 */	beq lbl_8013A6AC
/* 8013A6A0 001355A0  3C 04 FF F5 */	addis r0, r4, 0xfff5
/* 8013A6A4 001355A4  28 00 5A 01 */	cmplwi r0, 0x5a01
/* 8013A6A8 001355A8  40 82 00 0C */	bne lbl_8013A6B4
lbl_8013A6AC:
/* 8013A6AC 001355AC  38 60 00 00 */	li r3, 0
/* 8013A6B0 001355B0  4E 80 00 20 */	blr 
lbl_8013A6B4:
/* 8013A6B4 001355B4  28 03 20 00 */	cmplwi r3, 0x2000
/* 8013A6B8 001355B8  40 82 00 30 */	bne lbl_8013A6E8
/* 8013A6BC 001355BC  80 6D A0 18 */	lwz r3, executing-_SDA_BASE_(r13)
/* 8013A6C0 001355C0  80 03 00 08 */	lwz r0, 8(r3)
/* 8013A6C4 001355C4  28 00 00 25 */	cmplwi r0, 0x25
/* 8013A6C8 001355C8  41 82 00 18 */	beq lbl_8013A6E0
/* 8013A6CC 001355CC  3C 60 80 14 */	lis r3, stateDownRotation@ha
/* 8013A6D0 001355D0  80 0D A0 1C */	lwz r0, LastState-_SDA_BASE_(r13)
/* 8013A6D4 001355D4  38 63 C4 38 */	addi r3, r3, stateDownRotation@l
/* 8013A6D8 001355D8  7C 00 18 40 */	cmplw r0, r3
/* 8013A6DC 001355DC  40 82 00 0C */	bne lbl_8013A6E8
lbl_8013A6E0:
/* 8013A6E0 001355E0  38 60 00 00 */	li r3, 0
/* 8013A6E4 001355E4  4E 80 00 20 */	blr 
lbl_8013A6E8:
/* 8013A6E8 001355E8  80 6D 9F B0 */	lwz r3, NumInternalRetry-_SDA_BASE_(r13)
/* 8013A6EC 001355EC  38 03 00 01 */	addi r0, r3, 1
/* 8013A6F0 001355F0  90 0D 9F B0 */	stw r0, NumInternalRetry-_SDA_BASE_(r13)
/* 8013A6F4 001355F4  80 0D 9F B0 */	lwz r0, NumInternalRetry-_SDA_BASE_(r13)
/* 8013A6F8 001355F8  2C 00 00 02 */	cmpwi r0, 2
/* 8013A6FC 001355FC  40 82 00 28 */	bne lbl_8013A724
/* 8013A700 00135600  80 0D A0 00 */	lwz r0, LastError-_SDA_BASE_(r13)
/* 8013A704 00135604  7C 04 00 40 */	cmplw r4, r0
/* 8013A708 00135608  40 82 00 10 */	bne lbl_8013A718
/* 8013A70C 0013560C  90 8D A0 00 */	stw r4, LastError-_SDA_BASE_(r13)
/* 8013A710 00135610  38 60 00 01 */	li r3, 1
/* 8013A714 00135614  4E 80 00 20 */	blr 
lbl_8013A718:
/* 8013A718 00135618  90 8D A0 00 */	stw r4, LastError-_SDA_BASE_(r13)
/* 8013A71C 0013561C  38 60 00 02 */	li r3, 2
/* 8013A720 00135620  4E 80 00 20 */	blr 
lbl_8013A724:
/* 8013A724 00135624  3C 04 FF FD */	addis r0, r4, 0xfffd
/* 8013A728 00135628  90 8D A0 00 */	stw r4, LastError-_SDA_BASE_(r13)
/* 8013A72C 0013562C  28 00 11 00 */	cmplwi r0, 0x1100
/* 8013A730 00135630  41 82 00 14 */	beq lbl_8013A744
/* 8013A734 00135634  80 6D A0 18 */	lwz r3, executing-_SDA_BASE_(r13)
/* 8013A738 00135638  80 03 00 08 */	lwz r0, 8(r3)
/* 8013A73C 0013563C  28 00 00 05 */	cmplwi r0, 5
/* 8013A740 00135640  40 82 00 0C */	bne lbl_8013A74C
lbl_8013A744:
/* 8013A744 00135644  38 60 00 02 */	li r3, 2
/* 8013A748 00135648  4E 80 00 20 */	blr 
lbl_8013A74C:
/* 8013A74C 0013564C  38 60 00 03 */	li r3, 3
/* 8013A750 00135650  4E 80 00 20 */	blr 

.global cbForStoreErrorCode3
cbForStoreErrorCode3:
/* 8013A754 00135654  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8013A758 00135658  7C 08 02 A6 */	mflr r0
/* 8013A75C 0013565C  90 01 00 14 */	stw r0, 0x14(r1)
/* 8013A760 00135660  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8013A764 00135664  93 C1 00 08 */	stw r30, 8(r1)
/* 8013A768 00135668  4B FB 71 59 */	bl OSDisableInterrupts
/* 8013A76C 0013566C  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013A770 00135670  7C 7F 1B 78 */	mr r31, r3
/* 8013A774 00135674  28 00 00 05 */	cmplwi r0, 5
/* 8013A778 00135678  41 80 00 0C */	blt lbl_8013A784
/* 8013A77C 0013567C  38 00 00 00 */	li r0, 0
/* 8013A780 00135680  90 0D 9F 98 */	stw r0, CommandInfoCounter-_SDA_BASE_(r13)
lbl_8013A784:
/* 8013A784 00135684  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013A788 00135688  3F C0 80 48 */	lis r30, __ErrorInfo@ha
/* 8013A78C 0013568C  80 6D 9F 98 */	lwz r3, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013A790 00135690  3B DE A2 20 */	addi r30, r30, __ErrorInfo@l
/* 8013A794 00135694  1C A0 00 14 */	mulli r5, r0, 0x14
/* 8013A798 00135698  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013A79C 0013569C  38 C0 00 10 */	li r6, 0x10
/* 8013A7A0 001356A0  38 80 00 00 */	li r4, 0
/* 8013A7A4 001356A4  1C 63 00 14 */	mulli r3, r3, 0x14
/* 8013A7A8 001356A8  7C BE 2A 14 */	add r5, r30, r5
/* 8013A7AC 001356AC  90 C5 00 1C */	stw r6, 0x1c(r5)
/* 8013A7B0 001356B0  7C 7E 1A 14 */	add r3, r30, r3
/* 8013A7B4 001356B4  1C 00 00 14 */	mulli r0, r0, 0x14
/* 8013A7B8 001356B8  90 83 00 20 */	stw r4, 0x20(r3)
/* 8013A7BC 001356BC  7C 7E 02 14 */	add r3, r30, r0
/* 8013A7C0 001356C0  90 83 00 24 */	stw r4, 0x24(r3)
/* 8013A7C4 001356C4  4B FB AE 59 */	bl OSGetTick
/* 8013A7C8 001356C8  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013A7CC 001356CC  80 8D 9F 98 */	lwz r4, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013A7D0 001356D0  1C A0 00 14 */	mulli r5, r0, 0x14
/* 8013A7D4 001356D4  38 04 00 01 */	addi r0, r4, 1
/* 8013A7D8 001356D8  90 0D 9F 98 */	stw r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013A7DC 001356DC  7C 9E 2A 14 */	add r4, r30, r5
/* 8013A7E0 001356E0  90 64 00 2C */	stw r3, 0x2c(r4)
/* 8013A7E4 001356E4  7F E3 FB 78 */	mr r3, r31
/* 8013A7E8 001356E8  4B FB 71 01 */	bl OSRestoreInterrupts
/* 8013A7EC 001356EC  3C A0 80 14 */	lis r5, cbForStateGoToRetry@ha
/* 8013A7F0 001356F0  38 60 00 00 */	li r3, 0
/* 8013A7F4 001356F4  38 A5 AF D0 */	addi r5, r5, cbForStateGoToRetry@l
/* 8013A7F8 001356F8  38 80 00 00 */	li r4, 0
/* 8013A7FC 001356FC  48 00 4E 2D */	bl DVDLowStopMotor
/* 8013A800 00135700  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8013A804 00135704  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8013A808 00135708  83 C1 00 08 */	lwz r30, 8(r1)
/* 8013A80C 0013570C  7C 08 03 A6 */	mtlr r0
/* 8013A810 00135710  38 21 00 10 */	addi r1, r1, 0x10
/* 8013A814 00135714  4E 80 00 20 */	blr 

.global cbForStateGettingError
cbForStateGettingError:
/* 8013A818 00135718  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8013A81C 0013571C  7C 08 02 A6 */	mflr r0
/* 8013A820 00135720  90 01 00 24 */	stw r0, 0x24(r1)
/* 8013A824 00135724  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8013A828 00135728  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8013A82C 0013572C  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8013A830 00135730  93 81 00 10 */	stw r28, 0x10(r1)
/* 8013A834 00135734  7C 7C 1B 78 */	mr r28, r3
/* 8013A838 00135738  4B FB 70 89 */	bl OSDisableInterrupts
/* 8013A83C 0013573C  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013A840 00135740  2C 00 00 00 */	cmpwi r0, 0
/* 8013A844 00135744  40 82 00 14 */	bne lbl_8013A858
/* 8013A848 00135748  3C 80 80 48 */	lis r4, __ErrorInfo@ha
/* 8013A84C 0013574C  38 84 A2 20 */	addi r4, r4, __ErrorInfo@l
/* 8013A850 00135750  93 84 00 78 */	stw r28, 0x78(r4)
/* 8013A854 00135754  48 00 00 1C */	b lbl_8013A870
lbl_8013A858:
/* 8013A858 00135758  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013A85C 0013575C  3C 80 80 48 */	lis r4, __ErrorInfo@ha
/* 8013A860 00135760  38 84 A2 20 */	addi r4, r4, __ErrorInfo@l
/* 8013A864 00135764  1C 00 00 14 */	mulli r0, r0, 0x14
/* 8013A868 00135768  7C 84 02 14 */	add r4, r4, r0
/* 8013A86C 0013576C  93 84 00 14 */	stw r28, 0x14(r4)
lbl_8013A870:
/* 8013A870 00135770  4B FB 70 79 */	bl OSRestoreInterrupts
/* 8013A874 00135774  28 1C 00 10 */	cmplwi r28, 0x10
/* 8013A878 00135778  40 82 00 1C */	bne lbl_8013A894
/* 8013A87C 0013577C  3C 60 01 23 */	lis r3, 0x01234568@ha
/* 8013A880 00135780  3C 80 80 14 */	lis r4, cbForStoreErrorCode2@ha
/* 8013A884 00135784  38 63 45 68 */	addi r3, r3, 0x01234568@l
/* 8013A888 00135788  38 84 A6 24 */	addi r4, r4, cbForStoreErrorCode2@l
/* 8013A88C 0013578C  48 00 40 0D */	bl __DVDStoreErrorCode
/* 8013A890 00135790  48 00 04 6C */	b lbl_8013ACFC
lbl_8013A894:
/* 8013A894 00135794  28 1C 00 20 */	cmplwi r28, 0x20
/* 8013A898 00135798  40 82 00 1C */	bne lbl_8013A8B4
/* 8013A89C 0013579C  3C 60 01 23 */	lis r3, 0x01234569@ha
/* 8013A8A0 001357A0  3C 80 80 14 */	lis r4, cbForStoreErrorCode2@ha
/* 8013A8A4 001357A4  38 63 45 69 */	addi r3, r3, 0x01234569@l
/* 8013A8A8 001357A8  38 84 A6 24 */	addi r4, r4, cbForStoreErrorCode2@l
/* 8013A8AC 001357AC  48 00 3F ED */	bl __DVDStoreErrorCode
/* 8013A8B0 001357B0  48 00 04 4C */	b lbl_8013ACFC
lbl_8013A8B4:
/* 8013A8B4 001357B4  57 80 07 BD */	rlwinm. r0, r28, 0, 0x1e, 0x1e
/* 8013A8B8 001357B8  41 82 00 1C */	beq lbl_8013A8D4
/* 8013A8BC 001357BC  3C 60 01 23 */	lis r3, 0x01234567@ha
/* 8013A8C0 001357C0  3C 80 80 14 */	lis r4, cbForStoreErrorCode1@ha
/* 8013A8C4 001357C4  38 63 45 67 */	addi r3, r3, 0x01234567@l
/* 8013A8C8 001357C8  38 84 A6 10 */	addi r4, r4, cbForStoreErrorCode1@l
/* 8013A8CC 001357CC  48 00 3F CD */	bl __DVDStoreErrorCode
/* 8013A8D0 001357D0  48 00 04 2C */	b lbl_8013ACFC
lbl_8013A8D4:
/* 8013A8D4 001357D4  48 00 5A F9 */	bl DVDLowGetImmBufferReg
/* 8013A8D8 001357D8  7C 7D 1B 78 */	mr r29, r3
/* 8013A8DC 001357DC  54 7C 00 0E */	rlwinm r28, r3, 0, 0, 7
/* 8013A8E0 001357E0  4B FF FD 81 */	bl CategorizeError
/* 8013A8E4 001357E4  28 03 00 01 */	cmplwi r3, 1
/* 8013A8E8 001357E8  7C 7E 1B 78 */	mr r30, r3
/* 8013A8EC 001357EC  40 82 00 18 */	bne lbl_8013A904
/* 8013A8F0 001357F0  3C 80 80 14 */	lis r4, cbForStoreErrorCode1@ha
/* 8013A8F4 001357F4  7F A3 EB 78 */	mr r3, r29
/* 8013A8F8 001357F8  38 84 A6 10 */	addi r4, r4, cbForStoreErrorCode1@l
/* 8013A8FC 001357FC  48 00 3F 9D */	bl __DVDStoreErrorCode
/* 8013A900 00135800  48 00 03 FC */	b lbl_8013ACFC
lbl_8013A904:
/* 8013A904 00135804  38 03 FF FE */	addi r0, r3, -2
/* 8013A908 00135808  28 00 00 01 */	cmplwi r0, 1
/* 8013A90C 0013580C  41 81 00 0C */	bgt lbl_8013A918
/* 8013A910 00135810  38 A0 00 00 */	li r5, 0
/* 8013A914 00135814  48 00 00 68 */	b lbl_8013A97C
lbl_8013A918:
/* 8013A918 00135818  3C 1C FF 00 */	addis r0, r28, 0xff00
/* 8013A91C 0013581C  28 00 00 00 */	cmplwi r0, 0
/* 8013A920 00135820  40 82 00 0C */	bne lbl_8013A92C
/* 8013A924 00135824  38 A0 00 04 */	li r5, 4
/* 8013A928 00135828  48 00 00 54 */	b lbl_8013A97C
lbl_8013A92C:
/* 8013A92C 0013582C  3C 1C FE 00 */	addis r0, r28, 0xfe00
/* 8013A930 00135830  28 00 00 00 */	cmplwi r0, 0
/* 8013A934 00135834  40 82 00 0C */	bne lbl_8013A940
/* 8013A938 00135838  38 A0 00 06 */	li r5, 6
/* 8013A93C 0013583C  48 00 00 40 */	b lbl_8013A97C
lbl_8013A940:
/* 8013A940 00135840  3C 1C FD 00 */	addis r0, r28, 0xfd00
/* 8013A944 00135844  28 00 00 00 */	cmplwi r0, 0
/* 8013A948 00135848  40 82 00 0C */	bne lbl_8013A954
/* 8013A94C 0013584C  38 A0 00 03 */	li r5, 3
/* 8013A950 00135850  48 00 00 2C */	b lbl_8013A97C
lbl_8013A954:
/* 8013A954 00135854  2C 1C 00 00 */	cmpwi r28, 0
/* 8013A958 00135858  40 82 00 20 */	bne lbl_8013A978
/* 8013A95C 0013585C  3C 1D FF FB */	addis r0, r29, 0xfffb
/* 8013A960 00135860  28 00 30 00 */	cmplwi r0, 0x3000
/* 8013A964 00135864  40 82 00 0C */	bne lbl_8013A970
/* 8013A968 00135868  38 A0 00 01 */	li r5, 1
/* 8013A96C 0013586C  48 00 00 10 */	b lbl_8013A97C
lbl_8013A970:
/* 8013A970 00135870  38 A0 00 05 */	li r5, 5
/* 8013A974 00135874  48 00 00 08 */	b lbl_8013A97C
lbl_8013A978:
/* 8013A978 00135878  38 A0 00 05 */	li r5, 5
lbl_8013A97C:
/* 8013A97C 0013587C  80 0D 9F A8 */	lwz r0, Canceling-_SDA_BASE_(r13)
/* 8013A980 00135880  2C 00 00 00 */	cmpwi r0, 0
/* 8013A984 00135884  41 82 00 6C */	beq lbl_8013A9F0
/* 8013A988 00135888  3C 60 80 47 */	lis r3, DummyCommandBlock@ha
/* 8013A98C 0013588C  83 ED A0 18 */	lwz r31, executing-_SDA_BASE_(r13)
/* 8013A990 00135890  38 63 54 E0 */	addi r3, r3, DummyCommandBlock@l
/* 8013A994 00135894  38 80 00 00 */	li r4, 0
/* 8013A998 00135898  90 AD 9F AC */	stw r5, ResumeFromHere-_SDA_BASE_(r13)
/* 8013A99C 0013589C  38 00 00 0A */	li r0, 0xa
/* 8013A9A0 001358A0  90 8D 9F A8 */	stw r4, Canceling-_SDA_BASE_(r13)
/* 8013A9A4 001358A4  90 6D A0 18 */	stw r3, executing-_SDA_BASE_(r13)
/* 8013A9A8 001358A8  90 1F 00 0C */	stw r0, 0xc(r31)
/* 8013A9AC 001358AC  81 9F 00 28 */	lwz r12, 0x28(r31)
/* 8013A9B0 001358B0  2C 0C 00 00 */	cmpwi r12, 0
/* 8013A9B4 001358B4  41 82 00 14 */	beq lbl_8013A9C8
/* 8013A9B8 001358B8  7F E4 FB 78 */	mr r4, r31
/* 8013A9BC 001358BC  38 60 FF FD */	li r3, -3
/* 8013A9C0 001358C0  7D 89 03 A6 */	mtctr r12
/* 8013A9C4 001358C4  4E 80 04 21 */	bctrl 
lbl_8013A9C8:
/* 8013A9C8 001358C8  81 8D A0 08 */	lwz r12, CancelCallback-_SDA_BASE_(r13)
/* 8013A9CC 001358CC  2C 0C 00 00 */	cmpwi r12, 0
/* 8013A9D0 001358D0  41 82 00 14 */	beq lbl_8013A9E4
/* 8013A9D4 001358D4  7F E4 FB 78 */	mr r4, r31
/* 8013A9D8 001358D8  38 60 00 00 */	li r3, 0
/* 8013A9DC 001358DC  7D 89 03 A6 */	mtctr r12
/* 8013A9E0 001358E0  4E 80 04 21 */	bctrl 
lbl_8013A9E4:
/* 8013A9E4 001358E4  48 00 20 09 */	bl stateReady
/* 8013A9E8 001358E8  38 00 00 01 */	li r0, 1
/* 8013A9EC 001358EC  48 00 00 08 */	b lbl_8013A9F4
lbl_8013A9F0:
/* 8013A9F0 001358F0  38 00 00 00 */	li r0, 0
lbl_8013A9F4:
/* 8013A9F4 001358F4  2C 00 00 00 */	cmpwi r0, 0
/* 8013A9F8 001358F8  40 82 03 04 */	bne lbl_8013ACFC
/* 8013A9FC 001358FC  28 1E 00 02 */	cmplwi r30, 2
/* 8013AA00 00135900  40 82 00 18 */	bne lbl_8013AA18
/* 8013AA04 00135904  3C 80 80 14 */	lis r4, cbForStoreErrorCode3@ha
/* 8013AA08 00135908  7F A3 EB 78 */	mr r3, r29
/* 8013AA0C 0013590C  38 84 A7 54 */	addi r4, r4, cbForStoreErrorCode3@l
/* 8013AA10 00135910  48 00 3E 89 */	bl __DVDStoreErrorCode
/* 8013AA14 00135914  48 00 02 E8 */	b lbl_8013ACFC
lbl_8013AA18:
/* 8013AA18 00135918  28 1E 00 03 */	cmplwi r30, 3
/* 8013AA1C 0013591C  40 82 00 CC */	bne lbl_8013AAE8
/* 8013AA20 00135920  57 A3 02 3E */	clrlwi r3, r29, 8
/* 8013AA24 00135924  3C 03 FF FD */	addis r0, r3, 0xfffd
/* 8013AA28 00135928  28 00 11 00 */	cmplwi r0, 0x1100
/* 8013AA2C 0013592C  40 82 00 A8 */	bne lbl_8013AAD4
/* 8013AA30 00135930  80 6D A0 18 */	lwz r3, executing-_SDA_BASE_(r13)
/* 8013AA34 00135934  83 A3 00 10 */	lwz r29, 0x10(r3)
/* 8013AA38 00135938  4B FB 6E 89 */	bl OSDisableInterrupts
/* 8013AA3C 0013593C  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013AA40 00135940  7C 7F 1B 78 */	mr r31, r3
/* 8013AA44 00135944  28 00 00 05 */	cmplwi r0, 5
/* 8013AA48 00135948  41 80 00 0C */	blt lbl_8013AA54
/* 8013AA4C 0013594C  38 00 00 00 */	li r0, 0
/* 8013AA50 00135950  90 0D 9F 98 */	stw r0, CommandInfoCounter-_SDA_BASE_(r13)
lbl_8013AA54:
/* 8013AA54 00135954  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013AA58 00135958  3F C0 80 48 */	lis r30, __ErrorInfo@ha
/* 8013AA5C 0013595C  80 6D 9F 98 */	lwz r3, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013AA60 00135960  3B DE A2 20 */	addi r30, r30, __ErrorInfo@l
/* 8013AA64 00135964  1C A0 00 14 */	mulli r5, r0, 0x14
/* 8013AA68 00135968  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013AA6C 0013596C  38 C0 00 02 */	li r6, 2
/* 8013AA70 00135970  38 80 00 00 */	li r4, 0
/* 8013AA74 00135974  1C 63 00 14 */	mulli r3, r3, 0x14
/* 8013AA78 00135978  7C BE 2A 14 */	add r5, r30, r5
/* 8013AA7C 0013597C  90 C5 00 1C */	stw r6, 0x1c(r5)
/* 8013AA80 00135980  7C 7E 1A 14 */	add r3, r30, r3
/* 8013AA84 00135984  1C 00 00 14 */	mulli r0, r0, 0x14
/* 8013AA88 00135988  93 A3 00 20 */	stw r29, 0x20(r3)
/* 8013AA8C 0013598C  7C 7E 02 14 */	add r3, r30, r0
/* 8013AA90 00135990  90 83 00 24 */	stw r4, 0x24(r3)
/* 8013AA94 00135994  4B FB AB 89 */	bl OSGetTick
/* 8013AA98 00135998  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013AA9C 0013599C  80 8D 9F 98 */	lwz r4, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013AAA0 001359A0  1C A0 00 14 */	mulli r5, r0, 0x14
/* 8013AAA4 001359A4  38 04 00 01 */	addi r0, r4, 1
/* 8013AAA8 001359A8  90 0D 9F 98 */	stw r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013AAAC 001359AC  7C 9E 2A 14 */	add r4, r30, r5
/* 8013AAB0 001359B0  90 64 00 2C */	stw r3, 0x2c(r4)
/* 8013AAB4 001359B4  7F E3 FB 78 */	mr r3, r31
/* 8013AAB8 001359B8  4B FB 6E 31 */	bl OSRestoreInterrupts
/* 8013AABC 001359BC  80 6D A0 18 */	lwz r3, executing-_SDA_BASE_(r13)
/* 8013AAC0 001359C0  3C 80 80 14 */	lis r4, cbForUnrecoveredError@ha
/* 8013AAC4 001359C4  38 84 AD 1C */	addi r4, r4, cbForUnrecoveredError@l
/* 8013AAC8 001359C8  80 63 00 10 */	lwz r3, 0x10(r3)
/* 8013AACC 001359CC  48 00 56 0D */	bl DVDLowSeek
/* 8013AAD0 001359D0  48 00 02 2C */	b lbl_8013ACFC
lbl_8013AAD4:
/* 8013AAD4 001359D4  81 8D A0 1C */	lwz r12, LastState-_SDA_BASE_(r13)
/* 8013AAD8 001359D8  80 6D A0 18 */	lwz r3, executing-_SDA_BASE_(r13)
/* 8013AADC 001359DC  7D 89 03 A6 */	mtctr r12
/* 8013AAE0 001359E0  4E 80 04 21 */	bctrl 
/* 8013AAE4 001359E4  48 00 02 18 */	b lbl_8013ACFC
lbl_8013AAE8:
/* 8013AAE8 001359E8  3C 1C FF 00 */	addis r0, r28, 0xff00
/* 8013AAEC 001359EC  28 00 00 00 */	cmplwi r0, 0
/* 8013AAF0 001359F0  40 82 00 84 */	bne lbl_8013AB74
/* 8013AAF4 001359F4  80 8D A0 18 */	lwz r4, executing-_SDA_BASE_(r13)
/* 8013AAF8 001359F8  38 00 00 05 */	li r0, 5
/* 8013AAFC 001359FC  38 60 00 01 */	li r3, 1
/* 8013AB00 00135A00  90 04 00 0C */	stw r0, 0xc(r4)
/* 8013AB04 00135A04  80 0D 9F BC */	lwz r0, WaitingForCoverOpen-_SDA_BASE_(r13)
/* 8013AB08 00135A08  90 6D 9F F8 */	stw r3, MotorState-_SDA_BASE_(r13)
/* 8013AB0C 00135A0C  2C 00 00 00 */	cmpwi r0, 0
/* 8013AB10 00135A10  40 82 01 EC */	bne lbl_8013ACFC
/* 8013AB14 00135A14  80 0D 9F C0 */	lwz r0, WaitingForCoverClose-_SDA_BASE_(r13)
/* 8013AB18 00135A18  2C 00 00 00 */	cmpwi r0, 0
/* 8013AB1C 00135A1C  40 82 01 E0 */	bne lbl_8013ACFC
/* 8013AB20 00135A20  3F C0 80 47 */	lis r30, CoverAlarm@ha
/* 8013AB24 00135A24  90 6D 9F BC */	stw r3, WaitingForCoverOpen-_SDA_BASE_(r13)
/* 8013AB28 00135A28  38 7E 55 40 */	addi r3, r30, CoverAlarm@l
/* 8013AB2C 00135A2C  4B FB 25 E9 */	bl OSCreateAlarm
/* 8013AB30 00135A30  4B FB AA ED */	bl OSGetTick
/* 8013AB34 00135A34  3C A0 80 00 */	lis r5, 0x800000F8@ha
/* 8013AB38 00135A38  3C 80 10 62 */	lis r4, 0x10624DD3@ha
/* 8013AB3C 00135A3C  80 05 00 F8 */	lwz r0, 0x800000F8@l(r5)
/* 8013AB40 00135A40  3D 20 80 14 */	lis r9, CoverAlarmHandler@ha
/* 8013AB44 00135A44  7C 66 1B 78 */	mr r6, r3
/* 8013AB48 00135A48  38 84 4D D3 */	addi r4, r4, 0x10624DD3@l
/* 8013AB4C 00135A4C  54 00 F0 BE */	srwi r0, r0, 2
/* 8013AB50 00135A50  38 7E 55 40 */	addi r3, r30, 0x5540
/* 8013AB54 00135A54  7C 04 00 16 */	mulhwu r0, r4, r0
/* 8013AB58 00135A58  39 29 C9 C8 */	addi r9, r9, CoverAlarmHandler@l
/* 8013AB5C 00135A5C  38 A0 00 00 */	li r5, 0
/* 8013AB60 00135A60  38 E0 00 00 */	li r7, 0
/* 8013AB64 00135A64  54 00 D1 BE */	srwi r0, r0, 6
/* 8013AB68 00135A68  1D 00 00 64 */	mulli r8, r0, 0x64
/* 8013AB6C 00135A6C  4B FB 28 79 */	bl OSSetPeriodicAlarm
/* 8013AB70 00135A70  48 00 01 8C */	b lbl_8013ACFC
lbl_8013AB74:
/* 8013AB74 00135A74  3C 1C FE 00 */	addis r0, r28, 0xfe00
/* 8013AB78 00135A78  28 00 00 00 */	cmplwi r0, 0
/* 8013AB7C 00135A7C  40 82 00 18 */	bne lbl_8013AB94
/* 8013AB80 00135A80  80 6D A0 18 */	lwz r3, executing-_SDA_BASE_(r13)
/* 8013AB84 00135A84  38 00 00 03 */	li r0, 3
/* 8013AB88 00135A88  90 03 00 0C */	stw r0, 0xc(r3)
/* 8013AB8C 00135A8C  48 00 15 5D */	bl stateCoverClosed
/* 8013AB90 00135A90  48 00 01 6C */	b lbl_8013ACFC
lbl_8013AB94:
/* 8013AB94 00135A94  3C 1C FD 00 */	addis r0, r28, 0xfd00
/* 8013AB98 00135A98  28 00 00 00 */	cmplwi r0, 0
/* 8013AB9C 00135A9C  40 82 00 84 */	bne lbl_8013AC20
/* 8013ABA0 00135AA0  80 8D A0 18 */	lwz r4, executing-_SDA_BASE_(r13)
/* 8013ABA4 00135AA4  38 00 00 04 */	li r0, 4
/* 8013ABA8 00135AA8  38 60 00 01 */	li r3, 1
/* 8013ABAC 00135AAC  90 04 00 0C */	stw r0, 0xc(r4)
/* 8013ABB0 00135AB0  80 0D 9F BC */	lwz r0, WaitingForCoverOpen-_SDA_BASE_(r13)
/* 8013ABB4 00135AB4  90 6D 9F F8 */	stw r3, MotorState-_SDA_BASE_(r13)
/* 8013ABB8 00135AB8  2C 00 00 00 */	cmpwi r0, 0
/* 8013ABBC 00135ABC  40 82 01 40 */	bne lbl_8013ACFC
/* 8013ABC0 00135AC0  80 0D 9F C0 */	lwz r0, WaitingForCoverClose-_SDA_BASE_(r13)
/* 8013ABC4 00135AC4  2C 00 00 00 */	cmpwi r0, 0
/* 8013ABC8 00135AC8  40 82 01 34 */	bne lbl_8013ACFC
/* 8013ABCC 00135ACC  3F C0 80 47 */	lis r30, CoverAlarm@ha
/* 8013ABD0 00135AD0  90 6D 9F BC */	stw r3, WaitingForCoverOpen-_SDA_BASE_(r13)
/* 8013ABD4 00135AD4  38 7E 55 40 */	addi r3, r30, CoverAlarm@l
/* 8013ABD8 00135AD8  4B FB 25 3D */	bl OSCreateAlarm
/* 8013ABDC 00135ADC  4B FB AA 41 */	bl OSGetTick
/* 8013ABE0 00135AE0  3C A0 80 00 */	lis r5, 0x800000F8@ha
/* 8013ABE4 00135AE4  3C 80 10 62 */	lis r4, 0x10624DD3@ha
/* 8013ABE8 00135AE8  80 05 00 F8 */	lwz r0, 0x800000F8@l(r5)
/* 8013ABEC 00135AEC  3D 20 80 14 */	lis r9, CoverAlarmHandler@ha
/* 8013ABF0 00135AF0  7C 66 1B 78 */	mr r6, r3
/* 8013ABF4 00135AF4  38 84 4D D3 */	addi r4, r4, 0x10624DD3@l
/* 8013ABF8 00135AF8  54 00 F0 BE */	srwi r0, r0, 2
/* 8013ABFC 00135AFC  38 7E 55 40 */	addi r3, r30, 0x5540
/* 8013AC00 00135B00  7C 04 00 16 */	mulhwu r0, r4, r0
/* 8013AC04 00135B04  39 29 C9 C8 */	addi r9, r9, CoverAlarmHandler@l
/* 8013AC08 00135B08  38 A0 00 00 */	li r5, 0
/* 8013AC0C 00135B0C  38 E0 00 00 */	li r7, 0
/* 8013AC10 00135B10  54 00 D1 BE */	srwi r0, r0, 6
/* 8013AC14 00135B14  1D 00 00 64 */	mulli r8, r0, 0x64
/* 8013AC18 00135B18  4B FB 27 CD */	bl OSSetPeriodicAlarm
/* 8013AC1C 00135B1C  48 00 00 E0 */	b lbl_8013ACFC
lbl_8013AC20:
/* 8013AC20 00135B20  2C 1C 00 00 */	cmpwi r28, 0
/* 8013AC24 00135B24  40 82 00 C4 */	bne lbl_8013ACE8
/* 8013AC28 00135B28  3C 1D FF FB */	addis r0, r29, 0xfffb
/* 8013AC2C 00135B2C  28 00 30 00 */	cmplwi r0, 0x3000
/* 8013AC30 00135B30  40 82 00 A0 */	bne lbl_8013ACD0
/* 8013AC34 00135B34  4B FB 6C 8D */	bl OSDisableInterrupts
/* 8013AC38 00135B38  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013AC3C 00135B3C  7C 7F 1B 78 */	mr r31, r3
/* 8013AC40 00135B40  28 00 00 05 */	cmplwi r0, 5
/* 8013AC44 00135B44  41 80 00 0C */	blt lbl_8013AC50
/* 8013AC48 00135B48  38 00 00 00 */	li r0, 0
/* 8013AC4C 00135B4C  90 0D 9F 98 */	stw r0, CommandInfoCounter-_SDA_BASE_(r13)
lbl_8013AC50:
/* 8013AC50 00135B50  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013AC54 00135B54  3F C0 80 48 */	lis r30, __ErrorInfo@ha
/* 8013AC58 00135B58  80 6D 9F 98 */	lwz r3, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013AC5C 00135B5C  3B DE A2 20 */	addi r30, r30, __ErrorInfo@l
/* 8013AC60 00135B60  1C A0 00 14 */	mulli r5, r0, 0x14
/* 8013AC64 00135B64  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013AC68 00135B68  38 C0 00 10 */	li r6, 0x10
/* 8013AC6C 00135B6C  38 80 00 00 */	li r4, 0
/* 8013AC70 00135B70  1C 63 00 14 */	mulli r3, r3, 0x14
/* 8013AC74 00135B74  7C BE 2A 14 */	add r5, r30, r5
/* 8013AC78 00135B78  90 C5 00 1C */	stw r6, 0x1c(r5)
/* 8013AC7C 00135B7C  7C 7E 1A 14 */	add r3, r30, r3
/* 8013AC80 00135B80  1C 00 00 14 */	mulli r0, r0, 0x14
/* 8013AC84 00135B84  90 83 00 20 */	stw r4, 0x20(r3)
/* 8013AC88 00135B88  7C 7E 02 14 */	add r3, r30, r0
/* 8013AC8C 00135B8C  90 83 00 24 */	stw r4, 0x24(r3)
/* 8013AC90 00135B90  4B FB A9 8D */	bl OSGetTick
/* 8013AC94 00135B94  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013AC98 00135B98  80 8D 9F 98 */	lwz r4, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013AC9C 00135B9C  1C A0 00 14 */	mulli r5, r0, 0x14
/* 8013ACA0 00135BA0  38 04 00 01 */	addi r0, r4, 1
/* 8013ACA4 00135BA4  90 0D 9F 98 */	stw r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013ACA8 00135BA8  7C 9E 2A 14 */	add r4, r30, r5
/* 8013ACAC 00135BAC  90 64 00 2C */	stw r3, 0x2c(r4)
/* 8013ACB0 00135BB0  7F E3 FB 78 */	mr r3, r31
/* 8013ACB4 00135BB4  4B FB 6C 35 */	bl OSRestoreInterrupts
/* 8013ACB8 00135BB8  3C A0 80 14 */	lis r5, cbForStateCheckID1@ha
/* 8013ACBC 00135BBC  38 60 00 00 */	li r3, 0
/* 8013ACC0 00135BC0  38 A5 BD 8C */	addi r5, r5, cbForStateCheckID1@l
/* 8013ACC4 00135BC4  38 80 00 00 */	li r4, 0
/* 8013ACC8 00135BC8  48 00 49 61 */	bl DVDLowStopMotor
/* 8013ACCC 00135BCC  48 00 00 30 */	b lbl_8013ACFC
lbl_8013ACD0:
/* 8013ACD0 00135BD0  3C 60 01 23 */	lis r3, 0x01234567@ha
/* 8013ACD4 00135BD4  3C 80 80 14 */	lis r4, cbForStoreErrorCode1@ha
/* 8013ACD8 00135BD8  38 63 45 67 */	addi r3, r3, 0x01234567@l
/* 8013ACDC 00135BDC  38 84 A6 10 */	addi r4, r4, cbForStoreErrorCode1@l
/* 8013ACE0 00135BE0  48 00 3B B9 */	bl __DVDStoreErrorCode
/* 8013ACE4 00135BE4  48 00 00 18 */	b lbl_8013ACFC
lbl_8013ACE8:
/* 8013ACE8 00135BE8  3C 60 01 23 */	lis r3, 0x01234567@ha
/* 8013ACEC 00135BEC  3C 80 80 14 */	lis r4, cbForStoreErrorCode1@ha
/* 8013ACF0 00135BF0  38 63 45 67 */	addi r3, r3, 0x01234567@l
/* 8013ACF4 00135BF4  38 84 A6 10 */	addi r4, r4, cbForStoreErrorCode1@l
/* 8013ACF8 00135BF8  48 00 3B A1 */	bl __DVDStoreErrorCode
lbl_8013ACFC:
/* 8013ACFC 00135BFC  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8013AD00 00135C00  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8013AD04 00135C04  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8013AD08 00135C08  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8013AD0C 00135C0C  83 81 00 10 */	lwz r28, 0x10(r1)
/* 8013AD10 00135C10  7C 08 03 A6 */	mtlr r0
/* 8013AD14 00135C14  38 21 00 20 */	addi r1, r1, 0x20
/* 8013AD18 00135C18  4E 80 00 20 */	blr 

.global cbForUnrecoveredError
cbForUnrecoveredError:
/* 8013AD1C 00135C1C  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8013AD20 00135C20  7C 08 02 A6 */	mflr r0
/* 8013AD24 00135C24  90 01 00 14 */	stw r0, 0x14(r1)
/* 8013AD28 00135C28  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8013AD2C 00135C2C  93 C1 00 08 */	stw r30, 8(r1)
/* 8013AD30 00135C30  7C 7E 1B 78 */	mr r30, r3
/* 8013AD34 00135C34  4B FB 6B 8D */	bl OSDisableInterrupts
/* 8013AD38 00135C38  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013AD3C 00135C3C  2C 00 00 00 */	cmpwi r0, 0
/* 8013AD40 00135C40  40 82 00 14 */	bne lbl_8013AD54
/* 8013AD44 00135C44  3C 80 80 48 */	lis r4, __ErrorInfo@ha
/* 8013AD48 00135C48  38 84 A2 20 */	addi r4, r4, __ErrorInfo@l
/* 8013AD4C 00135C4C  93 C4 00 78 */	stw r30, 0x78(r4)
/* 8013AD50 00135C50  48 00 00 1C */	b lbl_8013AD6C
lbl_8013AD54:
/* 8013AD54 00135C54  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013AD58 00135C58  3C 80 80 48 */	lis r4, __ErrorInfo@ha
/* 8013AD5C 00135C5C  38 84 A2 20 */	addi r4, r4, __ErrorInfo@l
/* 8013AD60 00135C60  1C 00 00 14 */	mulli r0, r0, 0x14
/* 8013AD64 00135C64  7C 84 02 14 */	add r4, r4, r0
/* 8013AD68 00135C68  93 C4 00 14 */	stw r30, 0x14(r4)
lbl_8013AD6C:
/* 8013AD6C 00135C6C  4B FB 6B 7D */	bl OSRestoreInterrupts
/* 8013AD70 00135C70  28 1E 00 10 */	cmplwi r30, 0x10
/* 8013AD74 00135C74  40 82 00 1C */	bne lbl_8013AD90
/* 8013AD78 00135C78  3C 60 01 23 */	lis r3, 0x01234568@ha
/* 8013AD7C 00135C7C  3C 80 80 14 */	lis r4, cbForStoreErrorCode2@ha
/* 8013AD80 00135C80  38 63 45 68 */	addi r3, r3, 0x01234568@l
/* 8013AD84 00135C84  38 84 A6 24 */	addi r4, r4, cbForStoreErrorCode2@l
/* 8013AD88 00135C88  48 00 3B 11 */	bl __DVDStoreErrorCode
/* 8013AD8C 00135C8C  48 00 01 58 */	b lbl_8013AEE4
lbl_8013AD90:
/* 8013AD90 00135C90  28 1E 00 20 */	cmplwi r30, 0x20
/* 8013AD94 00135C94  40 82 00 1C */	bne lbl_8013ADB0
/* 8013AD98 00135C98  3C 60 01 23 */	lis r3, 0x01234569@ha
/* 8013AD9C 00135C9C  3C 80 80 14 */	lis r4, cbForStoreErrorCode2@ha
/* 8013ADA0 00135CA0  38 63 45 69 */	addi r3, r3, 0x01234569@l
/* 8013ADA4 00135CA4  38 84 A6 24 */	addi r4, r4, cbForStoreErrorCode2@l
/* 8013ADA8 00135CA8  48 00 3A F1 */	bl __DVDStoreErrorCode
/* 8013ADAC 00135CAC  48 00 01 38 */	b lbl_8013AEE4
lbl_8013ADB0:
/* 8013ADB0 00135CB0  57 C0 07 FF */	clrlwi. r0, r30, 0x1f
/* 8013ADB4 00135CB4  41 82 00 A0 */	beq lbl_8013AE54
/* 8013ADB8 00135CB8  4B FB 6B 09 */	bl OSDisableInterrupts
/* 8013ADBC 00135CBC  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013ADC0 00135CC0  7C 7F 1B 78 */	mr r31, r3
/* 8013ADC4 00135CC4  28 00 00 05 */	cmplwi r0, 5
/* 8013ADC8 00135CC8  41 80 00 0C */	blt lbl_8013ADD4
/* 8013ADCC 00135CCC  38 00 00 00 */	li r0, 0
/* 8013ADD0 00135CD0  90 0D 9F 98 */	stw r0, CommandInfoCounter-_SDA_BASE_(r13)
lbl_8013ADD4:
/* 8013ADD4 00135CD4  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013ADD8 00135CD8  3F C0 80 48 */	lis r30, __ErrorInfo@ha
/* 8013ADDC 00135CDC  80 6D 9F 98 */	lwz r3, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013ADE0 00135CE0  3B DE A2 20 */	addi r30, r30, __ErrorInfo@l
/* 8013ADE4 00135CE4  1C A0 00 14 */	mulli r5, r0, 0x14
/* 8013ADE8 00135CE8  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013ADEC 00135CEC  38 C0 00 10 */	li r6, 0x10
/* 8013ADF0 00135CF0  38 80 00 00 */	li r4, 0
/* 8013ADF4 00135CF4  1C 63 00 14 */	mulli r3, r3, 0x14
/* 8013ADF8 00135CF8  7C BE 2A 14 */	add r5, r30, r5
/* 8013ADFC 00135CFC  90 C5 00 1C */	stw r6, 0x1c(r5)
/* 8013AE00 00135D00  7C 7E 1A 14 */	add r3, r30, r3
/* 8013AE04 00135D04  1C 00 00 14 */	mulli r0, r0, 0x14
/* 8013AE08 00135D08  90 83 00 20 */	stw r4, 0x20(r3)
/* 8013AE0C 00135D0C  7C 7E 02 14 */	add r3, r30, r0
/* 8013AE10 00135D10  90 83 00 24 */	stw r4, 0x24(r3)
/* 8013AE14 00135D14  4B FB A8 09 */	bl OSGetTick
/* 8013AE18 00135D18  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013AE1C 00135D1C  80 8D 9F 98 */	lwz r4, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013AE20 00135D20  1C A0 00 14 */	mulli r5, r0, 0x14
/* 8013AE24 00135D24  38 04 00 01 */	addi r0, r4, 1
/* 8013AE28 00135D28  90 0D 9F 98 */	stw r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013AE2C 00135D2C  7C 9E 2A 14 */	add r4, r30, r5
/* 8013AE30 00135D30  90 64 00 2C */	stw r3, 0x2c(r4)
/* 8013AE34 00135D34  7F E3 FB 78 */	mr r3, r31
/* 8013AE38 00135D38  4B FB 6A B1 */	bl OSRestoreInterrupts
/* 8013AE3C 00135D3C  3C A0 80 14 */	lis r5, cbForStateGoToRetry@ha
/* 8013AE40 00135D40  38 60 00 00 */	li r3, 0
/* 8013AE44 00135D44  38 A5 AF D0 */	addi r5, r5, cbForStateGoToRetry@l
/* 8013AE48 00135D48  38 80 00 00 */	li r4, 0
/* 8013AE4C 00135D4C  48 00 47 DD */	bl DVDLowStopMotor
/* 8013AE50 00135D50  48 00 00 94 */	b lbl_8013AEE4
lbl_8013AE54:
/* 8013AE54 00135D54  4B FB 6A 6D */	bl OSDisableInterrupts
/* 8013AE58 00135D58  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013AE5C 00135D5C  7C 7F 1B 78 */	mr r31, r3
/* 8013AE60 00135D60  28 00 00 05 */	cmplwi r0, 5
/* 8013AE64 00135D64  41 80 00 0C */	blt lbl_8013AE70
/* 8013AE68 00135D68  38 00 00 00 */	li r0, 0
/* 8013AE6C 00135D6C  90 0D 9F 98 */	stw r0, CommandInfoCounter-_SDA_BASE_(r13)
lbl_8013AE70:
/* 8013AE70 00135D70  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013AE74 00135D74  3F C0 80 48 */	lis r30, __ErrorInfo@ha
/* 8013AE78 00135D78  80 6D 9F 98 */	lwz r3, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013AE7C 00135D7C  3B DE A2 20 */	addi r30, r30, __ErrorInfo@l
/* 8013AE80 00135D80  1C A0 00 14 */	mulli r5, r0, 0x14
/* 8013AE84 00135D84  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013AE88 00135D88  38 C0 00 27 */	li r6, 0x27
/* 8013AE8C 00135D8C  38 80 00 00 */	li r4, 0
/* 8013AE90 00135D90  1C 63 00 14 */	mulli r3, r3, 0x14
/* 8013AE94 00135D94  7C BE 2A 14 */	add r5, r30, r5
/* 8013AE98 00135D98  90 C5 00 1C */	stw r6, 0x1c(r5)
/* 8013AE9C 00135D9C  7C 7E 1A 14 */	add r3, r30, r3
/* 8013AEA0 00135DA0  1C 00 00 14 */	mulli r0, r0, 0x14
/* 8013AEA4 00135DA4  90 83 00 20 */	stw r4, 0x20(r3)
/* 8013AEA8 00135DA8  7C 7E 02 14 */	add r3, r30, r0
/* 8013AEAC 00135DAC  90 83 00 24 */	stw r4, 0x24(r3)
/* 8013AEB0 00135DB0  4B FB A7 6D */	bl OSGetTick
/* 8013AEB4 00135DB4  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013AEB8 00135DB8  80 8D 9F 98 */	lwz r4, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013AEBC 00135DBC  1C A0 00 14 */	mulli r5, r0, 0x14
/* 8013AEC0 00135DC0  38 04 00 01 */	addi r0, r4, 1
/* 8013AEC4 00135DC4  90 0D 9F 98 */	stw r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013AEC8 00135DC8  7C 9E 2A 14 */	add r4, r30, r5
/* 8013AECC 00135DCC  90 64 00 2C */	stw r3, 0x2c(r4)
/* 8013AED0 00135DD0  7F E3 FB 78 */	mr r3, r31
/* 8013AED4 00135DD4  4B FB 6A 15 */	bl OSRestoreInterrupts
/* 8013AED8 00135DD8  3C 60 80 14 */	lis r3, cbForUnrecoveredErrorRetry@ha
/* 8013AEDC 00135DDC  38 63 AE FC */	addi r3, r3, cbForUnrecoveredErrorRetry@l
/* 8013AEE0 00135DE0  48 00 4A 45 */	bl DVDLowRequestError
lbl_8013AEE4:
/* 8013AEE4 00135DE4  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8013AEE8 00135DE8  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8013AEEC 00135DEC  83 C1 00 08 */	lwz r30, 8(r1)
/* 8013AEF0 00135DF0  7C 08 03 A6 */	mtlr r0
/* 8013AEF4 00135DF4  38 21 00 10 */	addi r1, r1, 0x10
/* 8013AEF8 00135DF8  4E 80 00 20 */	blr 

.global cbForUnrecoveredErrorRetry
cbForUnrecoveredErrorRetry:
/* 8013AEFC 00135DFC  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8013AF00 00135E00  7C 08 02 A6 */	mflr r0
/* 8013AF04 00135E04  90 01 00 14 */	stw r0, 0x14(r1)
/* 8013AF08 00135E08  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8013AF0C 00135E0C  7C 7F 1B 78 */	mr r31, r3
/* 8013AF10 00135E10  4B FB 69 B1 */	bl OSDisableInterrupts
/* 8013AF14 00135E14  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013AF18 00135E18  2C 00 00 00 */	cmpwi r0, 0
/* 8013AF1C 00135E1C  40 82 00 14 */	bne lbl_8013AF30
/* 8013AF20 00135E20  3C 80 80 48 */	lis r4, __ErrorInfo@ha
/* 8013AF24 00135E24  38 84 A2 20 */	addi r4, r4, __ErrorInfo@l
/* 8013AF28 00135E28  93 E4 00 78 */	stw r31, 0x78(r4)
/* 8013AF2C 00135E2C  48 00 00 1C */	b lbl_8013AF48
lbl_8013AF30:
/* 8013AF30 00135E30  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013AF34 00135E34  3C 80 80 48 */	lis r4, __ErrorInfo@ha
/* 8013AF38 00135E38  38 84 A2 20 */	addi r4, r4, __ErrorInfo@l
/* 8013AF3C 00135E3C  1C 00 00 14 */	mulli r0, r0, 0x14
/* 8013AF40 00135E40  7C 84 02 14 */	add r4, r4, r0
/* 8013AF44 00135E44  93 E4 00 14 */	stw r31, 0x14(r4)
lbl_8013AF48:
/* 8013AF48 00135E48  4B FB 69 A1 */	bl OSRestoreInterrupts
/* 8013AF4C 00135E4C  28 1F 00 10 */	cmplwi r31, 0x10
/* 8013AF50 00135E50  40 82 00 1C */	bne lbl_8013AF6C
/* 8013AF54 00135E54  3C 60 01 23 */	lis r3, 0x01234568@ha
/* 8013AF58 00135E58  3C 80 80 14 */	lis r4, cbForStoreErrorCode2@ha
/* 8013AF5C 00135E5C  38 63 45 68 */	addi r3, r3, 0x01234568@l
/* 8013AF60 00135E60  38 84 A6 24 */	addi r4, r4, cbForStoreErrorCode2@l
/* 8013AF64 00135E64  48 00 39 35 */	bl __DVDStoreErrorCode
/* 8013AF68 00135E68  48 00 00 54 */	b lbl_8013AFBC
lbl_8013AF6C:
/* 8013AF6C 00135E6C  28 1F 00 20 */	cmplwi r31, 0x20
/* 8013AF70 00135E70  40 82 00 1C */	bne lbl_8013AF8C
/* 8013AF74 00135E74  3C 60 01 23 */	lis r3, 0x01234569@ha
/* 8013AF78 00135E78  3C 80 80 14 */	lis r4, cbForStoreErrorCode2@ha
/* 8013AF7C 00135E7C  38 63 45 69 */	addi r3, r3, 0x01234569@l
/* 8013AF80 00135E80  38 84 A6 24 */	addi r4, r4, cbForStoreErrorCode2@l
/* 8013AF84 00135E84  48 00 39 15 */	bl __DVDStoreErrorCode
/* 8013AF88 00135E88  48 00 00 34 */	b lbl_8013AFBC
lbl_8013AF8C:
/* 8013AF8C 00135E8C  57 E0 07 BD */	rlwinm. r0, r31, 0, 0x1e, 0x1e
/* 8013AF90 00135E90  41 82 00 1C */	beq lbl_8013AFAC
/* 8013AF94 00135E94  3C 60 01 23 */	lis r3, 0x01234567@ha
/* 8013AF98 00135E98  3C 80 80 14 */	lis r4, cbForStoreErrorCode1@ha
/* 8013AF9C 00135E9C  38 63 45 67 */	addi r3, r3, 0x01234567@l
/* 8013AFA0 00135EA0  38 84 A6 10 */	addi r4, r4, cbForStoreErrorCode1@l
/* 8013AFA4 00135EA4  48 00 38 F5 */	bl __DVDStoreErrorCode
/* 8013AFA8 00135EA8  48 00 00 14 */	b lbl_8013AFBC
lbl_8013AFAC:
/* 8013AFAC 00135EAC  48 00 54 21 */	bl DVDLowGetImmBufferReg
/* 8013AFB0 00135EB0  3C 80 80 14 */	lis r4, cbForStoreErrorCode1@ha
/* 8013AFB4 00135EB4  38 84 A6 10 */	addi r4, r4, cbForStoreErrorCode1@l
/* 8013AFB8 00135EB8  48 00 38 E1 */	bl __DVDStoreErrorCode
lbl_8013AFBC:
/* 8013AFBC 00135EBC  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8013AFC0 00135EC0  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8013AFC4 00135EC4  7C 08 03 A6 */	mtlr r0
/* 8013AFC8 00135EC8  38 21 00 10 */	addi r1, r1, 0x10
/* 8013AFCC 00135ECC  4E 80 00 20 */	blr 

.global cbForStateGoToRetry
cbForStateGoToRetry:
/* 8013AFD0 00135ED0  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8013AFD4 00135ED4  7C 08 02 A6 */	mflr r0
/* 8013AFD8 00135ED8  90 01 00 14 */	stw r0, 0x14(r1)
/* 8013AFDC 00135EDC  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8013AFE0 00135EE0  7C 7F 1B 78 */	mr r31, r3
/* 8013AFE4 00135EE4  4B FB 68 DD */	bl OSDisableInterrupts
/* 8013AFE8 00135EE8  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013AFEC 00135EEC  2C 00 00 00 */	cmpwi r0, 0
/* 8013AFF0 00135EF0  40 82 00 14 */	bne lbl_8013B004
/* 8013AFF4 00135EF4  3C 80 80 48 */	lis r4, __ErrorInfo@ha
/* 8013AFF8 00135EF8  38 84 A2 20 */	addi r4, r4, __ErrorInfo@l
/* 8013AFFC 00135EFC  93 E4 00 78 */	stw r31, 0x78(r4)
/* 8013B000 00135F00  48 00 00 1C */	b lbl_8013B01C
lbl_8013B004:
/* 8013B004 00135F04  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B008 00135F08  3C 80 80 48 */	lis r4, __ErrorInfo@ha
/* 8013B00C 00135F0C  38 84 A2 20 */	addi r4, r4, __ErrorInfo@l
/* 8013B010 00135F10  1C 00 00 14 */	mulli r0, r0, 0x14
/* 8013B014 00135F14  7C 84 02 14 */	add r4, r4, r0
/* 8013B018 00135F18  93 E4 00 14 */	stw r31, 0x14(r4)
lbl_8013B01C:
/* 8013B01C 00135F1C  4B FB 68 CD */	bl OSRestoreInterrupts
/* 8013B020 00135F20  28 1F 00 10 */	cmplwi r31, 0x10
/* 8013B024 00135F24  40 82 00 1C */	bne lbl_8013B040
/* 8013B028 00135F28  3C 60 01 23 */	lis r3, 0x01234568@ha
/* 8013B02C 00135F2C  3C 80 80 14 */	lis r4, cbForStoreErrorCode2@ha
/* 8013B030 00135F30  38 63 45 68 */	addi r3, r3, 0x01234568@l
/* 8013B034 00135F34  38 84 A6 24 */	addi r4, r4, cbForStoreErrorCode2@l
/* 8013B038 00135F38  48 00 38 61 */	bl __DVDStoreErrorCode
/* 8013B03C 00135F3C  48 00 01 A8 */	b lbl_8013B1E4
lbl_8013B040:
/* 8013B040 00135F40  28 1F 00 20 */	cmplwi r31, 0x20
/* 8013B044 00135F44  40 82 00 1C */	bne lbl_8013B060
/* 8013B048 00135F48  3C 60 01 23 */	lis r3, 0x01234569@ha
/* 8013B04C 00135F4C  3C 80 80 14 */	lis r4, cbForStoreErrorCode2@ha
/* 8013B050 00135F50  38 63 45 69 */	addi r3, r3, 0x01234569@l
/* 8013B054 00135F54  38 84 A6 24 */	addi r4, r4, cbForStoreErrorCode2@l
/* 8013B058 00135F58  48 00 38 41 */	bl __DVDStoreErrorCode
/* 8013B05C 00135F5C  48 00 01 88 */	b lbl_8013B1E4
lbl_8013B060:
/* 8013B060 00135F60  57 E0 07 BD */	rlwinm. r0, r31, 0, 0x1e, 0x1e
/* 8013B064 00135F64  41 82 00 1C */	beq lbl_8013B080
/* 8013B068 00135F68  3C 60 01 23 */	lis r3, 0x01234567@ha
/* 8013B06C 00135F6C  3C 80 80 14 */	lis r4, cbForStoreErrorCode1@ha
/* 8013B070 00135F70  38 63 45 67 */	addi r3, r3, 0x01234567@l
/* 8013B074 00135F74  38 84 A6 10 */	addi r4, r4, cbForStoreErrorCode1@l
/* 8013B078 00135F78  48 00 38 21 */	bl __DVDStoreErrorCode
/* 8013B07C 00135F7C  48 00 01 68 */	b lbl_8013B1E4
lbl_8013B080:
/* 8013B080 00135F80  38 00 00 00 */	li r0, 0
/* 8013B084 00135F84  90 0D 9F B0 */	stw r0, NumInternalRetry-_SDA_BASE_(r13)
/* 8013B088 00135F88  80 0D A0 0C */	lwz r0, CurrCommand-_SDA_BASE_(r13)
/* 8013B08C 00135F8C  28 00 00 04 */	cmplwi r0, 4
/* 8013B090 00135F90  41 82 00 4C */	beq lbl_8013B0DC
/* 8013B094 00135F94  80 0D A0 0C */	lwz r0, CurrCommand-_SDA_BASE_(r13)
/* 8013B098 00135F98  28 00 00 05 */	cmplwi r0, 5
/* 8013B09C 00135F9C  41 82 00 40 */	beq lbl_8013B0DC
/* 8013B0A0 00135FA0  80 0D A0 0C */	lwz r0, CurrCommand-_SDA_BASE_(r13)
/* 8013B0A4 00135FA4  28 00 00 0D */	cmplwi r0, 0xd
/* 8013B0A8 00135FA8  41 82 00 34 */	beq lbl_8013B0DC
/* 8013B0AC 00135FAC  80 0D A0 0C */	lwz r0, CurrCommand-_SDA_BASE_(r13)
/* 8013B0B0 00135FB0  28 00 00 21 */	cmplwi r0, 0x21
/* 8013B0B4 00135FB4  41 82 00 28 */	beq lbl_8013B0DC
/* 8013B0B8 00135FB8  80 0D A0 0C */	lwz r0, CurrCommand-_SDA_BASE_(r13)
/* 8013B0BC 00135FBC  28 00 00 22 */	cmplwi r0, 0x22
/* 8013B0C0 00135FC0  41 82 00 1C */	beq lbl_8013B0DC
/* 8013B0C4 00135FC4  80 0D A0 0C */	lwz r0, CurrCommand-_SDA_BASE_(r13)
/* 8013B0C8 00135FC8  28 00 00 0F */	cmplwi r0, 0xf
/* 8013B0CC 00135FCC  41 82 00 10 */	beq lbl_8013B0DC
/* 8013B0D0 00135FD0  80 0D A0 0C */	lwz r0, CurrCommand-_SDA_BASE_(r13)
/* 8013B0D4 00135FD4  28 00 00 25 */	cmplwi r0, 0x25
/* 8013B0D8 00135FD8  40 82 00 0C */	bne lbl_8013B0E4
lbl_8013B0DC:
/* 8013B0DC 00135FDC  38 00 00 01 */	li r0, 1
/* 8013B0E0 00135FE0  90 0D 9F FC */	stw r0, ResetRequired-_SDA_BASE_(r13)
lbl_8013B0E4:
/* 8013B0E4 00135FE4  80 0D 9F A8 */	lwz r0, Canceling-_SDA_BASE_(r13)
/* 8013B0E8 00135FE8  2C 00 00 00 */	cmpwi r0, 0
/* 8013B0EC 00135FEC  41 82 00 70 */	beq lbl_8013B15C
/* 8013B0F0 00135FF0  3C 60 80 47 */	lis r3, DummyCommandBlock@ha
/* 8013B0F4 00135FF4  83 ED A0 18 */	lwz r31, executing-_SDA_BASE_(r13)
/* 8013B0F8 00135FF8  38 63 54 E0 */	addi r3, r3, DummyCommandBlock@l
/* 8013B0FC 00135FFC  38 00 00 02 */	li r0, 2
/* 8013B100 00136000  90 0D 9F AC */	stw r0, ResumeFromHere-_SDA_BASE_(r13)
/* 8013B104 00136004  38 80 00 00 */	li r4, 0
/* 8013B108 00136008  38 00 00 0A */	li r0, 0xa
/* 8013B10C 0013600C  90 8D 9F A8 */	stw r4, Canceling-_SDA_BASE_(r13)
/* 8013B110 00136010  90 6D A0 18 */	stw r3, executing-_SDA_BASE_(r13)
/* 8013B114 00136014  90 1F 00 0C */	stw r0, 0xc(r31)
/* 8013B118 00136018  81 9F 00 28 */	lwz r12, 0x28(r31)
/* 8013B11C 0013601C  2C 0C 00 00 */	cmpwi r12, 0
/* 8013B120 00136020  41 82 00 14 */	beq lbl_8013B134
/* 8013B124 00136024  7F E4 FB 78 */	mr r4, r31
/* 8013B128 00136028  38 60 FF FD */	li r3, -3
/* 8013B12C 0013602C  7D 89 03 A6 */	mtctr r12
/* 8013B130 00136030  4E 80 04 21 */	bctrl 
lbl_8013B134:
/* 8013B134 00136034  81 8D A0 08 */	lwz r12, CancelCallback-_SDA_BASE_(r13)
/* 8013B138 00136038  2C 0C 00 00 */	cmpwi r12, 0
/* 8013B13C 0013603C  41 82 00 14 */	beq lbl_8013B150
/* 8013B140 00136040  7F E4 FB 78 */	mr r4, r31
/* 8013B144 00136044  38 60 00 00 */	li r3, 0
/* 8013B148 00136048  7D 89 03 A6 */	mtctr r12
/* 8013B14C 0013604C  4E 80 04 21 */	bctrl 
lbl_8013B150:
/* 8013B150 00136050  48 00 18 9D */	bl stateReady
/* 8013B154 00136054  38 00 00 01 */	li r0, 1
/* 8013B158 00136058  48 00 00 08 */	b lbl_8013B160
lbl_8013B15C:
/* 8013B15C 0013605C  38 00 00 00 */	li r0, 0
lbl_8013B160:
/* 8013B160 00136060  2C 00 00 00 */	cmpwi r0, 0
/* 8013B164 00136064  40 82 00 80 */	bne lbl_8013B1E4
/* 8013B168 00136068  80 8D A0 18 */	lwz r4, executing-_SDA_BASE_(r13)
/* 8013B16C 0013606C  38 00 00 0B */	li r0, 0xb
/* 8013B170 00136070  38 60 00 01 */	li r3, 1
/* 8013B174 00136074  90 04 00 0C */	stw r0, 0xc(r4)
/* 8013B178 00136078  80 0D 9F BC */	lwz r0, WaitingForCoverOpen-_SDA_BASE_(r13)
/* 8013B17C 0013607C  90 6D 9F F8 */	stw r3, MotorState-_SDA_BASE_(r13)
/* 8013B180 00136080  2C 00 00 00 */	cmpwi r0, 0
/* 8013B184 00136084  40 82 00 60 */	bne lbl_8013B1E4
/* 8013B188 00136088  80 0D 9F C0 */	lwz r0, WaitingForCoverClose-_SDA_BASE_(r13)
/* 8013B18C 0013608C  2C 00 00 00 */	cmpwi r0, 0
/* 8013B190 00136090  40 82 00 54 */	bne lbl_8013B1E4
/* 8013B194 00136094  3F E0 80 47 */	lis r31, CoverAlarm@ha
/* 8013B198 00136098  90 6D 9F BC */	stw r3, WaitingForCoverOpen-_SDA_BASE_(r13)
/* 8013B19C 0013609C  38 7F 55 40 */	addi r3, r31, CoverAlarm@l
/* 8013B1A0 001360A0  4B FB 1F 75 */	bl OSCreateAlarm
/* 8013B1A4 001360A4  4B FB A4 79 */	bl OSGetTick
/* 8013B1A8 001360A8  3C A0 80 00 */	lis r5, 0x800000F8@ha
/* 8013B1AC 001360AC  3C 80 10 62 */	lis r4, 0x10624DD3@ha
/* 8013B1B0 001360B0  80 05 00 F8 */	lwz r0, 0x800000F8@l(r5)
/* 8013B1B4 001360B4  3D 20 80 14 */	lis r9, CoverAlarmHandler@ha
/* 8013B1B8 001360B8  7C 66 1B 78 */	mr r6, r3
/* 8013B1BC 001360BC  38 84 4D D3 */	addi r4, r4, 0x10624DD3@l
/* 8013B1C0 001360C0  54 00 F0 BE */	srwi r0, r0, 2
/* 8013B1C4 001360C4  38 7F 55 40 */	addi r3, r31, 0x5540
/* 8013B1C8 001360C8  7C 04 00 16 */	mulhwu r0, r4, r0
/* 8013B1CC 001360CC  39 29 C9 C8 */	addi r9, r9, CoverAlarmHandler@l
/* 8013B1D0 001360D0  38 A0 00 00 */	li r5, 0
/* 8013B1D4 001360D4  38 E0 00 00 */	li r7, 0
/* 8013B1D8 001360D8  54 00 D1 BE */	srwi r0, r0, 6
/* 8013B1DC 001360DC  1D 00 00 64 */	mulli r8, r0, 0x64
/* 8013B1E0 001360E0  4B FB 22 05 */	bl OSSetPeriodicAlarm
lbl_8013B1E4:
/* 8013B1E4 001360E4  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8013B1E8 001360E8  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8013B1EC 001360EC  7C 08 03 A6 */	mtlr r0
/* 8013B1F0 001360F0  38 21 00 10 */	addi r1, r1, 0x10
/* 8013B1F4 001360F4  4E 80 00 20 */	blr 

.global stateCheckID
stateCheckID:
/* 8013B1F8 001360F8  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8013B1FC 001360FC  7C 08 02 A6 */	mflr r0
/* 8013B200 00136100  90 01 00 24 */	stw r0, 0x24(r1)
/* 8013B204 00136104  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8013B208 00136108  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8013B20C 0013610C  3F C0 80 47 */	lis r30, BB2@ha
/* 8013B210 00136110  3B DE 54 C0 */	addi r30, r30, BB2@l
/* 8013B214 00136114  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8013B218 00136118  80 0D A0 0C */	lwz r0, CurrCommand-_SDA_BASE_(r13)
/* 8013B21C 0013611C  2C 00 00 03 */	cmpwi r0, 3
/* 8013B220 00136120  41 82 00 08 */	beq lbl_8013B228
/* 8013B224 00136124  48 00 01 90 */	b lbl_8013B3B4
lbl_8013B228:
/* 8013B228 00136128  3B E0 00 00 */	li r31, 0
/* 8013B22C 0013612C  80 8D A0 18 */	lwz r4, executing-_SDA_BASE_(r13)
/* 8013B230 00136130  93 ED 9F C8 */	stw r31, ChangedDisc-_SDA_BASE_(r13)
/* 8013B234 00136134  38 7E 00 C0 */	addi r3, r30, 0xc0
/* 8013B238 00136138  80 84 00 24 */	lwz r4, 0x24(r4)
/* 8013B23C 0013613C  48 00 37 01 */	bl DVDCompareDiskID
/* 8013B240 00136140  2C 03 00 00 */	cmpwi r3, 0
/* 8013B244 00136144  41 82 00 D8 */	beq lbl_8013B31C
/* 8013B248 00136148  80 6D A0 14 */	lwz r3, IDShouldBe-_SDA_BASE_(r13)
/* 8013B24C 0013614C  38 9E 00 C0 */	addi r4, r30, 0xc0
/* 8013B250 00136150  38 A0 00 20 */	li r5, 0x20
/* 8013B254 00136154  4B EC 8D AD */	bl memcpy
/* 8013B258 00136158  80 AD A0 18 */	lwz r5, executing-_SDA_BASE_(r13)
/* 8013B25C 0013615C  38 00 00 01 */	li r0, 1
/* 8013B260 00136160  38 7E 00 00 */	addi r3, r30, 0
/* 8013B264 00136164  38 80 00 20 */	li r4, 0x20
/* 8013B268 00136168  90 05 00 0C */	stw r0, 0xc(r5)
/* 8013B26C 0013616C  4B FB 2E 99 */	bl DCInvalidateRange
/* 8013B270 00136170  93 ED 9F B0 */	stw r31, NumInternalRetry-_SDA_BASE_(r13)
/* 8013B274 00136174  38 60 00 00 */	li r3, 0
/* 8013B278 00136178  48 00 51 71 */	bl DVDLowClearCoverInterrupt
/* 8013B27C 0013617C  4B FB 66 45 */	bl OSDisableInterrupts
/* 8013B280 00136180  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B284 00136184  7C 7D 1B 78 */	mr r29, r3
/* 8013B288 00136188  28 00 00 05 */	cmplwi r0, 5
/* 8013B28C 0013618C  41 80 00 08 */	blt lbl_8013B294
/* 8013B290 00136190  93 ED 9F 98 */	stw r31, CommandInfoCounter-_SDA_BASE_(r13)
lbl_8013B294:
/* 8013B294 00136194  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B298 00136198  3F E0 80 48 */	lis r31, __ErrorInfo@ha
/* 8013B29C 0013619C  80 6D 9F 98 */	lwz r3, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B2A0 001361A0  3B FF A2 20 */	addi r31, r31, __ErrorInfo@l
/* 8013B2A4 001361A4  1C C0 00 14 */	mulli r6, r0, 0x14
/* 8013B2A8 001361A8  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B2AC 001361AC  38 E0 00 21 */	li r7, 0x21
/* 8013B2B0 001361B0  3C A0 00 01 */	lis r5, 1
/* 8013B2B4 001361B4  1C 63 00 14 */	mulli r3, r3, 0x14
/* 8013B2B8 001361B8  38 80 00 20 */	li r4, 0x20
/* 8013B2BC 001361BC  7C DF 32 14 */	add r6, r31, r6
/* 8013B2C0 001361C0  90 E6 00 1C */	stw r7, 0x1c(r6)
/* 8013B2C4 001361C4  7C 7F 1A 14 */	add r3, r31, r3
/* 8013B2C8 001361C8  1C 00 00 14 */	mulli r0, r0, 0x14
/* 8013B2CC 001361CC  90 A3 00 20 */	stw r5, 0x20(r3)
/* 8013B2D0 001361D0  7C 7F 02 14 */	add r3, r31, r0
/* 8013B2D4 001361D4  90 83 00 24 */	stw r4, 0x24(r3)
/* 8013B2D8 001361D8  4B FB A3 45 */	bl OSGetTick
/* 8013B2DC 001361DC  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B2E0 001361E0  80 8D 9F 98 */	lwz r4, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B2E4 001361E4  1C A0 00 14 */	mulli r5, r0, 0x14
/* 8013B2E8 001361E8  38 04 00 01 */	addi r0, r4, 1
/* 8013B2EC 001361EC  90 0D 9F 98 */	stw r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B2F0 001361F0  7C 9F 2A 14 */	add r4, r31, r5
/* 8013B2F4 001361F4  90 64 00 2C */	stw r3, 0x2c(r4)
/* 8013B2F8 001361F8  7F A3 EB 78 */	mr r3, r29
/* 8013B2FC 001361FC  4B FB 65 ED */	bl OSRestoreInterrupts
/* 8013B300 00136200  3C C0 80 14 */	lis r6, cbForStateReadingTOC@ha
/* 8013B304 00136204  38 7E 00 E0 */	addi r3, r30, 0xe0
/* 8013B308 00136208  38 C6 B5 30 */	addi r6, r6, cbForStateReadingTOC@l
/* 8013B30C 0013620C  38 80 00 20 */	li r4, 0x20
/* 8013B310 00136210  3C A0 00 01 */	lis r5, 1
/* 8013B314 00136214  48 00 41 81 */	bl DVDLowUnencryptedRead
/* 8013B318 00136218  48 00 01 FC */	b lbl_8013B514
lbl_8013B31C:
/* 8013B31C 0013621C  4B FB 65 A5 */	bl OSDisableInterrupts
/* 8013B320 00136220  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B324 00136224  7C 7D 1B 78 */	mr r29, r3
/* 8013B328 00136228  28 00 00 05 */	cmplwi r0, 5
/* 8013B32C 0013622C  41 80 00 08 */	blt lbl_8013B334
/* 8013B330 00136230  93 ED 9F 98 */	stw r31, CommandInfoCounter-_SDA_BASE_(r13)
lbl_8013B334:
/* 8013B334 00136234  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B338 00136238  3F C0 80 48 */	lis r30, __ErrorInfo@ha
/* 8013B33C 0013623C  80 6D 9F 98 */	lwz r3, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B340 00136240  3B DE A2 20 */	addi r30, r30, __ErrorInfo@l
/* 8013B344 00136244  1C A0 00 14 */	mulli r5, r0, 0x14
/* 8013B348 00136248  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B34C 0013624C  38 C0 00 10 */	li r6, 0x10
/* 8013B350 00136250  38 80 00 00 */	li r4, 0
/* 8013B354 00136254  1C 63 00 14 */	mulli r3, r3, 0x14
/* 8013B358 00136258  7C BE 2A 14 */	add r5, r30, r5
/* 8013B35C 0013625C  90 C5 00 1C */	stw r6, 0x1c(r5)
/* 8013B360 00136260  7C 7E 1A 14 */	add r3, r30, r3
/* 8013B364 00136264  1C 00 00 14 */	mulli r0, r0, 0x14
/* 8013B368 00136268  90 83 00 20 */	stw r4, 0x20(r3)
/* 8013B36C 0013626C  7C 7E 02 14 */	add r3, r30, r0
/* 8013B370 00136270  90 83 00 24 */	stw r4, 0x24(r3)
/* 8013B374 00136274  4B FB A2 A9 */	bl OSGetTick
/* 8013B378 00136278  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B37C 0013627C  80 8D 9F 98 */	lwz r4, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B380 00136280  1C A0 00 14 */	mulli r5, r0, 0x14
/* 8013B384 00136284  38 04 00 01 */	addi r0, r4, 1
/* 8013B388 00136288  90 0D 9F 98 */	stw r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B38C 0013628C  7C 9E 2A 14 */	add r4, r30, r5
/* 8013B390 00136290  90 64 00 2C */	stw r3, 0x2c(r4)
/* 8013B394 00136294  7F A3 EB 78 */	mr r3, r29
/* 8013B398 00136298  4B FB 65 51 */	bl OSRestoreInterrupts
/* 8013B39C 0013629C  3C A0 80 14 */	lis r5, cbForStateCheckID1@ha
/* 8013B3A0 001362A0  38 60 00 00 */	li r3, 0
/* 8013B3A4 001362A4  38 A5 BD 8C */	addi r5, r5, cbForStateCheckID1@l
/* 8013B3A8 001362A8  38 80 00 00 */	li r4, 0
/* 8013B3AC 001362AC  48 00 42 7D */	bl DVDLowStopMotor
/* 8013B3B0 001362B0  48 00 01 64 */	b lbl_8013B514
lbl_8013B3B4:
/* 8013B3B4 001362B4  80 8D A0 14 */	lwz r4, IDShouldBe-_SDA_BASE_(r13)
/* 8013B3B8 001362B8  38 7E 00 C0 */	addi r3, r30, 0xc0
/* 8013B3BC 001362BC  38 A0 00 20 */	li r5, 0x20
/* 8013B3C0 001362C0  4B F7 9B 5D */	bl memcmp
/* 8013B3C4 001362C4  2C 03 00 00 */	cmpwi r3, 0
/* 8013B3C8 001362C8  41 82 00 A0 */	beq lbl_8013B468
/* 8013B3CC 001362CC  4B FB 64 F5 */	bl OSDisableInterrupts
/* 8013B3D0 001362D0  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B3D4 001362D4  7C 7D 1B 78 */	mr r29, r3
/* 8013B3D8 001362D8  28 00 00 05 */	cmplwi r0, 5
/* 8013B3DC 001362DC  41 80 00 0C */	blt lbl_8013B3E8
/* 8013B3E0 001362E0  38 00 00 00 */	li r0, 0
/* 8013B3E4 001362E4  90 0D 9F 98 */	stw r0, CommandInfoCounter-_SDA_BASE_(r13)
lbl_8013B3E8:
/* 8013B3E8 001362E8  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B3EC 001362EC  3F C0 80 48 */	lis r30, __ErrorInfo@ha
/* 8013B3F0 001362F0  80 6D 9F 98 */	lwz r3, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B3F4 001362F4  3B DE A2 20 */	addi r30, r30, __ErrorInfo@l
/* 8013B3F8 001362F8  1C A0 00 14 */	mulli r5, r0, 0x14
/* 8013B3FC 001362FC  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B400 00136300  38 C0 00 10 */	li r6, 0x10
/* 8013B404 00136304  38 80 00 00 */	li r4, 0
/* 8013B408 00136308  1C 63 00 14 */	mulli r3, r3, 0x14
/* 8013B40C 0013630C  7C BE 2A 14 */	add r5, r30, r5
/* 8013B410 00136310  90 C5 00 1C */	stw r6, 0x1c(r5)
/* 8013B414 00136314  7C 7E 1A 14 */	add r3, r30, r3
/* 8013B418 00136318  1C 00 00 14 */	mulli r0, r0, 0x14
/* 8013B41C 0013631C  90 83 00 20 */	stw r4, 0x20(r3)
/* 8013B420 00136320  7C 7E 02 14 */	add r3, r30, r0
/* 8013B424 00136324  90 83 00 24 */	stw r4, 0x24(r3)
/* 8013B428 00136328  4B FB A1 F5 */	bl OSGetTick
/* 8013B42C 0013632C  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B430 00136330  80 8D 9F 98 */	lwz r4, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B434 00136334  1C A0 00 14 */	mulli r5, r0, 0x14
/* 8013B438 00136338  38 04 00 01 */	addi r0, r4, 1
/* 8013B43C 0013633C  90 0D 9F 98 */	stw r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B440 00136340  7C 9E 2A 14 */	add r4, r30, r5
/* 8013B444 00136344  90 64 00 2C */	stw r3, 0x2c(r4)
/* 8013B448 00136348  7F A3 EB 78 */	mr r3, r29
/* 8013B44C 0013634C  4B FB 64 9D */	bl OSRestoreInterrupts
/* 8013B450 00136350  3C A0 80 14 */	lis r5, cbForStateCheckID1@ha
/* 8013B454 00136354  38 60 00 00 */	li r3, 0
/* 8013B458 00136358  38 A5 BD 8C */	addi r5, r5, cbForStateCheckID1@l
/* 8013B45C 0013635C  38 80 00 00 */	li r4, 0
/* 8013B460 00136360  48 00 41 C9 */	bl DVDLowStopMotor
/* 8013B464 00136364  48 00 00 B0 */	b lbl_8013B514
lbl_8013B468:
/* 8013B468 00136368  3B E0 00 00 */	li r31, 0
/* 8013B46C 0013636C  38 60 00 00 */	li r3, 0
/* 8013B470 00136370  93 ED 9F B0 */	stw r31, NumInternalRetry-_SDA_BASE_(r13)
/* 8013B474 00136374  48 00 4F 75 */	bl DVDLowClearCoverInterrupt
/* 8013B478 00136378  4B FB 64 49 */	bl OSDisableInterrupts
/* 8013B47C 0013637C  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B480 00136380  7C 7D 1B 78 */	mr r29, r3
/* 8013B484 00136384  28 00 00 05 */	cmplwi r0, 5
/* 8013B488 00136388  41 80 00 08 */	blt lbl_8013B490
/* 8013B48C 0013638C  93 ED 9F 98 */	stw r31, CommandInfoCounter-_SDA_BASE_(r13)
lbl_8013B490:
/* 8013B490 00136390  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B494 00136394  3F E0 80 48 */	lis r31, __ErrorInfo@ha
/* 8013B498 00136398  80 6D 9F 98 */	lwz r3, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B49C 0013639C  3B FF A2 20 */	addi r31, r31, __ErrorInfo@l
/* 8013B4A0 001363A0  1C C0 00 14 */	mulli r6, r0, 0x14
/* 8013B4A4 001363A4  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B4A8 001363A8  38 E0 00 21 */	li r7, 0x21
/* 8013B4AC 001363AC  3C A0 00 01 */	lis r5, 1
/* 8013B4B0 001363B0  1C 63 00 14 */	mulli r3, r3, 0x14
/* 8013B4B4 001363B4  38 80 00 20 */	li r4, 0x20
/* 8013B4B8 001363B8  7C DF 32 14 */	add r6, r31, r6
/* 8013B4BC 001363BC  90 E6 00 1C */	stw r7, 0x1c(r6)
/* 8013B4C0 001363C0  7C 7F 1A 14 */	add r3, r31, r3
/* 8013B4C4 001363C4  1C 00 00 14 */	mulli r0, r0, 0x14
/* 8013B4C8 001363C8  90 A3 00 20 */	stw r5, 0x20(r3)
/* 8013B4CC 001363CC  7C 7F 02 14 */	add r3, r31, r0
/* 8013B4D0 001363D0  90 83 00 24 */	stw r4, 0x24(r3)
/* 8013B4D4 001363D4  4B FB A1 49 */	bl OSGetTick
/* 8013B4D8 001363D8  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B4DC 001363DC  80 8D 9F 98 */	lwz r4, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B4E0 001363E0  1C A0 00 14 */	mulli r5, r0, 0x14
/* 8013B4E4 001363E4  38 04 00 01 */	addi r0, r4, 1
/* 8013B4E8 001363E8  90 0D 9F 98 */	stw r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B4EC 001363EC  7C 9F 2A 14 */	add r4, r31, r5
/* 8013B4F0 001363F0  90 64 00 2C */	stw r3, 0x2c(r4)
/* 8013B4F4 001363F4  7F A3 EB 78 */	mr r3, r29
/* 8013B4F8 001363F8  4B FB 63 F1 */	bl OSRestoreInterrupts
/* 8013B4FC 001363FC  3C C0 80 14 */	lis r6, cbForStateReadingTOC@ha
/* 8013B500 00136400  38 7E 00 E0 */	addi r3, r30, 0xe0
/* 8013B504 00136404  38 C6 B5 30 */	addi r6, r6, cbForStateReadingTOC@l
/* 8013B508 00136408  38 80 00 20 */	li r4, 0x20
/* 8013B50C 0013640C  3C A0 00 01 */	lis r5, 1
/* 8013B510 00136410  48 00 3F 85 */	bl DVDLowUnencryptedRead
lbl_8013B514:
/* 8013B514 00136414  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8013B518 00136418  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8013B51C 0013641C  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8013B520 00136420  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8013B524 00136424  7C 08 03 A6 */	mtlr r0
/* 8013B528 00136428  38 21 00 20 */	addi r1, r1, 0x20
/* 8013B52C 0013642C  4E 80 00 20 */	blr 

.global cbForStateReadingTOC
cbForStateReadingTOC:
/* 8013B530 00136430  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8013B534 00136434  7C 08 02 A6 */	mflr r0
/* 8013B538 00136438  90 01 00 24 */	stw r0, 0x24(r1)
/* 8013B53C 0013643C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8013B540 00136440  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8013B544 00136444  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8013B548 00136448  7C 7D 1B 78 */	mr r29, r3
/* 8013B54C 0013644C  4B FB 63 75 */	bl OSDisableInterrupts
/* 8013B550 00136450  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B554 00136454  2C 00 00 00 */	cmpwi r0, 0
/* 8013B558 00136458  40 82 00 14 */	bne lbl_8013B56C
/* 8013B55C 0013645C  3C 80 80 48 */	lis r4, __ErrorInfo@ha
/* 8013B560 00136460  38 84 A2 20 */	addi r4, r4, __ErrorInfo@l
/* 8013B564 00136464  93 A4 00 78 */	stw r29, 0x78(r4)
/* 8013B568 00136468  48 00 00 20 */	b lbl_8013B588
lbl_8013B56C:
/* 8013B56C 0013646C  80 8D 9F 98 */	lwz r4, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B570 00136470  3C A0 80 48 */	lis r5, __ErrorInfo@ha
/* 8013B574 00136474  38 A5 A2 20 */	addi r5, r5, __ErrorInfo@l
/* 8013B578 00136478  38 04 FF FF */	addi r0, r4, -1
/* 8013B57C 0013647C  1C 00 00 14 */	mulli r0, r0, 0x14
/* 8013B580 00136480  7C 85 02 14 */	add r4, r5, r0
/* 8013B584 00136484  93 A4 00 28 */	stw r29, 0x28(r4)
lbl_8013B588:
/* 8013B588 00136488  4B FB 63 61 */	bl OSRestoreInterrupts
/* 8013B58C 0013648C  28 1D 00 10 */	cmplwi r29, 0x10
/* 8013B590 00136490  40 82 00 1C */	bne lbl_8013B5AC
/* 8013B594 00136494  3C 60 01 23 */	lis r3, 0x01234568@ha
/* 8013B598 00136498  3C 80 80 14 */	lis r4, cbForStoreErrorCode2@ha
/* 8013B59C 0013649C  38 63 45 68 */	addi r3, r3, 0x01234568@l
/* 8013B5A0 001364A0  38 84 A6 24 */	addi r4, r4, cbForStoreErrorCode2@l
/* 8013B5A4 001364A4  48 00 32 F5 */	bl __DVDStoreErrorCode
/* 8013B5A8 001364A8  48 00 01 0C */	b lbl_8013B6B4
lbl_8013B5AC:
/* 8013B5AC 001364AC  28 1D 00 20 */	cmplwi r29, 0x20
/* 8013B5B0 001364B0  40 82 00 1C */	bne lbl_8013B5CC
/* 8013B5B4 001364B4  3C 60 01 23 */	lis r3, 0x01234569@ha
/* 8013B5B8 001364B8  3C 80 80 14 */	lis r4, cbForStoreErrorCode2@ha
/* 8013B5BC 001364BC  38 63 45 69 */	addi r3, r3, 0x01234569@l
/* 8013B5C0 001364C0  38 84 A6 24 */	addi r4, r4, cbForStoreErrorCode2@l
/* 8013B5C4 001364C4  48 00 32 D5 */	bl __DVDStoreErrorCode
/* 8013B5C8 001364C8  48 00 00 EC */	b lbl_8013B6B4
lbl_8013B5CC:
/* 8013B5CC 001364CC  57 A0 07 FF */	clrlwi. r0, r29, 0x1f
/* 8013B5D0 001364D0  41 82 00 C8 */	beq lbl_8013B698
/* 8013B5D4 001364D4  3C 80 80 47 */	lis r4, GameTocBuffer@ha
/* 8013B5D8 001364D8  3B A0 00 00 */	li r29, 0
/* 8013B5DC 001364DC  38 84 55 A0 */	addi r4, r4, GameTocBuffer@l
/* 8013B5E0 001364E0  93 AD 9F B0 */	stw r29, NumInternalRetry-_SDA_BASE_(r13)
/* 8013B5E4 001364E4  38 60 00 00 */	li r3, 0
/* 8013B5E8 001364E8  90 8D 9F E8 */	stw r4, GameToc-_SDA_BASE_(r13)
/* 8013B5EC 001364EC  48 00 4D FD */	bl DVDLowClearCoverInterrupt
/* 8013B5F0 001364F0  4B FB 62 D1 */	bl OSDisableInterrupts
/* 8013B5F4 001364F4  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B5F8 001364F8  7C 7E 1B 78 */	mr r30, r3
/* 8013B5FC 001364FC  28 00 00 05 */	cmplwi r0, 5
/* 8013B600 00136500  41 80 00 08 */	blt lbl_8013B608
/* 8013B604 00136504  93 AD 9F 98 */	stw r29, CommandInfoCounter-_SDA_BASE_(r13)
lbl_8013B608:
/* 8013B608 00136508  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B60C 0013650C  3F E0 80 48 */	lis r31, __ErrorInfo@ha
/* 8013B610 00136510  80 6D 9F 98 */	lwz r3, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B614 00136514  3F A0 00 01 */	lis r29, 0x00010008@ha
/* 8013B618 00136518  1C 80 00 14 */	mulli r4, r0, 0x14
/* 8013B61C 0013651C  3B FF A2 20 */	addi r31, r31, __ErrorInfo@l
/* 8013B620 00136520  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B624 00136524  38 C0 00 21 */	li r6, 0x21
/* 8013B628 00136528  38 BD 00 08 */	addi r5, r29, 0x00010008@l
/* 8013B62C 0013652C  1C 63 00 14 */	mulli r3, r3, 0x14
/* 8013B630 00136530  7C 9F 22 14 */	add r4, r31, r4
/* 8013B634 00136534  90 C4 00 1C */	stw r6, 0x1c(r4)
/* 8013B638 00136538  7C 7F 1A 14 */	add r3, r31, r3
/* 8013B63C 0013653C  38 80 00 20 */	li r4, 0x20
/* 8013B640 00136540  1C 00 00 14 */	mulli r0, r0, 0x14
/* 8013B644 00136544  90 A3 00 20 */	stw r5, 0x20(r3)
/* 8013B648 00136548  7C 7F 02 14 */	add r3, r31, r0
/* 8013B64C 0013654C  90 83 00 24 */	stw r4, 0x24(r3)
/* 8013B650 00136550  4B FB 9F CD */	bl OSGetTick
/* 8013B654 00136554  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B658 00136558  80 8D 9F 98 */	lwz r4, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B65C 0013655C  1C A0 00 14 */	mulli r5, r0, 0x14
/* 8013B660 00136560  38 04 00 01 */	addi r0, r4, 1
/* 8013B664 00136564  90 0D 9F 98 */	stw r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B668 00136568  7C 9F 2A 14 */	add r4, r31, r5
/* 8013B66C 0013656C  90 64 00 2C */	stw r3, 0x2c(r4)
/* 8013B670 00136570  7F C3 F3 78 */	mr r3, r30
/* 8013B674 00136574  4B FB 62 75 */	bl OSRestoreInterrupts
/* 8013B678 00136578  3C 60 80 47 */	lis r3, PartInfoBuffer@ha
/* 8013B67C 0013657C  3C C0 80 14 */	lis r6, cbForStateReadingPartitionInfo@ha
/* 8013B680 00136580  38 BD 00 08 */	addi r5, r29, 8
/* 8013B684 00136584  38 80 00 20 */	li r4, 0x20
/* 8013B688 00136588  38 63 55 C0 */	addi r3, r3, PartInfoBuffer@l
/* 8013B68C 0013658C  38 C6 B6 D0 */	addi r6, r6, cbForStateReadingPartitionInfo@l
/* 8013B690 00136590  48 00 3E 05 */	bl DVDLowUnencryptedRead
/* 8013B694 00136594  48 00 00 20 */	b lbl_8013B6B4
lbl_8013B698:
/* 8013B698 00136598  38 60 00 27 */	li r3, 0x27
/* 8013B69C 0013659C  38 80 00 00 */	li r4, 0
/* 8013B6A0 001365A0  38 A0 00 00 */	li r5, 0
/* 8013B6A4 001365A4  4B FF E9 C5 */	bl StampCommand
/* 8013B6A8 001365A8  3C 60 80 14 */	lis r3, cbForStateGettingError@ha
/* 8013B6AC 001365AC  38 63 A8 18 */	addi r3, r3, cbForStateGettingError@l
/* 8013B6B0 001365B0  48 00 42 75 */	bl DVDLowRequestError
lbl_8013B6B4:
/* 8013B6B4 001365B4  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8013B6B8 001365B8  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8013B6BC 001365BC  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8013B6C0 001365C0  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8013B6C4 001365C4  7C 08 03 A6 */	mtlr r0
/* 8013B6C8 001365C8  38 21 00 20 */	addi r1, r1, 0x20
/* 8013B6CC 001365CC  4E 80 00 20 */	blr 

.global cbForStateReadingPartitionInfo
cbForStateReadingPartitionInfo:
/* 8013B6D0 001365D0  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8013B6D4 001365D4  7C 08 02 A6 */	mflr r0
/* 8013B6D8 001365D8  90 01 00 24 */	stw r0, 0x24(r1)
/* 8013B6DC 001365DC  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8013B6E0 001365E0  3F E0 80 47 */	lis r31, BB2@ha
/* 8013B6E4 001365E4  3B FF 54 C0 */	addi r31, r31, BB2@l
/* 8013B6E8 001365E8  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8013B6EC 001365EC  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8013B6F0 001365F0  93 81 00 10 */	stw r28, 0x10(r1)
/* 8013B6F4 001365F4  7C 7C 1B 78 */	mr r28, r3
/* 8013B6F8 001365F8  4B FB 61 C9 */	bl OSDisableInterrupts
/* 8013B6FC 001365FC  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B700 00136600  2C 00 00 00 */	cmpwi r0, 0
/* 8013B704 00136604  40 82 00 14 */	bne lbl_8013B718
/* 8013B708 00136608  3C 80 80 48 */	lis r4, __ErrorInfo@ha
/* 8013B70C 0013660C  38 84 A2 20 */	addi r4, r4, __ErrorInfo@l
/* 8013B710 00136610  93 84 00 78 */	stw r28, 0x78(r4)
/* 8013B714 00136614  48 00 00 20 */	b lbl_8013B734
lbl_8013B718:
/* 8013B718 00136618  80 8D 9F 98 */	lwz r4, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B71C 0013661C  3C A0 80 48 */	lis r5, __ErrorInfo@ha
/* 8013B720 00136620  38 A5 A2 20 */	addi r5, r5, __ErrorInfo@l
/* 8013B724 00136624  38 04 FF FF */	addi r0, r4, -1
/* 8013B728 00136628  1C 00 00 14 */	mulli r0, r0, 0x14
/* 8013B72C 0013662C  7C 85 02 14 */	add r4, r5, r0
/* 8013B730 00136630  93 84 00 28 */	stw r28, 0x28(r4)
lbl_8013B734:
/* 8013B734 00136634  4B FB 61 B5 */	bl OSRestoreInterrupts
/* 8013B738 00136638  28 1C 00 10 */	cmplwi r28, 0x10
/* 8013B73C 0013663C  40 82 00 1C */	bne lbl_8013B758
/* 8013B740 00136640  3C 60 01 23 */	lis r3, 0x01234568@ha
/* 8013B744 00136644  3C 80 80 14 */	lis r4, cbForStoreErrorCode2@ha
/* 8013B748 00136648  38 63 45 68 */	addi r3, r3, 0x01234568@l
/* 8013B74C 0013664C  38 84 A6 24 */	addi r4, r4, cbForStoreErrorCode2@l
/* 8013B750 00136650  48 00 31 49 */	bl __DVDStoreErrorCode
/* 8013B754 00136654  48 00 03 2C */	b lbl_8013BA80
lbl_8013B758:
/* 8013B758 00136658  28 1C 00 20 */	cmplwi r28, 0x20
/* 8013B75C 0013665C  40 82 00 1C */	bne lbl_8013B778
/* 8013B760 00136660  3C 60 01 23 */	lis r3, 0x01234569@ha
/* 8013B764 00136664  3C 80 80 14 */	lis r4, cbForStoreErrorCode2@ha
/* 8013B768 00136668  38 63 45 69 */	addi r3, r3, 0x01234569@l
/* 8013B76C 0013666C  38 84 A6 24 */	addi r4, r4, cbForStoreErrorCode2@l
/* 8013B770 00136670  48 00 31 29 */	bl __DVDStoreErrorCode
/* 8013B774 00136674  48 00 03 0C */	b lbl_8013BA80
lbl_8013B778:
/* 8013B778 00136678  57 80 07 FF */	clrlwi. r0, r28, 0x1f
/* 8013B77C 0013667C  41 82 02 E8 */	beq lbl_8013BA64
/* 8013B780 00136680  38 C0 00 00 */	li r6, 0
/* 8013B784 00136684  38 7F 01 00 */	addi r3, r31, 0x100
/* 8013B788 00136688  90 CD 9F B0 */	stw r6, NumInternalRetry-_SDA_BASE_(r13)
/* 8013B78C 0013668C  38 E0 00 00 */	li r7, 0
/* 8013B790 00136690  80 8D 9F E8 */	lwz r4, GameToc-_SDA_BASE_(r13)
/* 8013B794 00136694  90 6D 9F E4 */	stw r3, PartInfo-_SDA_BASE_(r13)
/* 8013B798 00136698  90 CD 9F E0 */	stw r6, BootGameInfo-_SDA_BASE_(r13)
/* 8013B79C 0013669C  48 00 00 24 */	b lbl_8013B7C0
lbl_8013B7A0:
/* 8013B7A0 001366A0  80 03 00 04 */	lwz r0, 4(r3)
/* 8013B7A4 001366A4  2C 00 00 00 */	cmpwi r0, 0
/* 8013B7A8 001366A8  40 82 00 0C */	bne lbl_8013B7B4
/* 8013B7AC 001366AC  7C 66 1B 78 */	mr r6, r3
/* 8013B7B0 001366B0  90 6D 9F E0 */	stw r3, BootGameInfo-_SDA_BASE_(r13)
lbl_8013B7B4:
/* 8013B7B4 001366B4  38 63 00 08 */	addi r3, r3, 8
/* 8013B7B8 001366B8  38 E7 00 01 */	addi r7, r7, 1
/* 8013B7BC 001366BC  90 6D 9F E4 */	stw r3, PartInfo-_SDA_BASE_(r13)
lbl_8013B7C0:
/* 8013B7C0 001366C0  80 04 00 00 */	lwz r0, 0(r4)
/* 8013B7C4 001366C4  7C E5 07 34 */	extsh r5, r7
/* 8013B7C8 001366C8  7C 05 00 40 */	cmplw r5, r0
/* 8013B7CC 001366CC  41 80 FF D4 */	blt lbl_8013B7A0
/* 8013B7D0 001366D0  2C 06 00 00 */	cmpwi r6, 0
/* 8013B7D4 001366D4  41 82 01 94 */	beq lbl_8013B968
/* 8013B7D8 001366D8  80 0D A0 0C */	lwz r0, CurrCommand-_SDA_BASE_(r13)
/* 8013B7DC 001366DC  2C 00 00 03 */	cmpwi r0, 3
/* 8013B7E0 001366E0  41 82 00 08 */	beq lbl_8013B7E8
/* 8013B7E4 001366E4  48 00 00 C4 */	b lbl_8013B8A8
lbl_8013B7E8:
/* 8013B7E8 001366E8  3B A0 00 00 */	li r29, 0
/* 8013B7EC 001366EC  38 60 00 00 */	li r3, 0
/* 8013B7F0 001366F0  93 AD 9F B0 */	stw r29, NumInternalRetry-_SDA_BASE_(r13)
/* 8013B7F4 001366F4  48 00 4B F5 */	bl DVDLowClearCoverInterrupt
/* 8013B7F8 001366F8  80 6D 9F E0 */	lwz r3, BootGameInfo-_SDA_BASE_(r13)
/* 8013B7FC 001366FC  83 83 00 00 */	lwz r28, 0(r3)
/* 8013B800 00136700  4B FB 60 C1 */	bl OSDisableInterrupts
/* 8013B804 00136704  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B808 00136708  7C 7E 1B 78 */	mr r30, r3
/* 8013B80C 0013670C  28 00 00 05 */	cmplwi r0, 5
/* 8013B810 00136710  41 80 00 08 */	blt lbl_8013B818
/* 8013B814 00136714  93 AD 9F 98 */	stw r29, CommandInfoCounter-_SDA_BASE_(r13)
lbl_8013B818:
/* 8013B818 00136718  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B81C 0013671C  3F A0 80 48 */	lis r29, __ErrorInfo@ha
/* 8013B820 00136720  80 6D 9F 98 */	lwz r3, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B824 00136724  3B BD A2 20 */	addi r29, r29, __ErrorInfo@l
/* 8013B828 00136728  1C A0 00 14 */	mulli r5, r0, 0x14
/* 8013B82C 0013672C  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B830 00136730  38 C0 00 22 */	li r6, 0x22
/* 8013B834 00136734  38 80 00 00 */	li r4, 0
/* 8013B838 00136738  1C 63 00 14 */	mulli r3, r3, 0x14
/* 8013B83C 0013673C  7C BD 2A 14 */	add r5, r29, r5
/* 8013B840 00136740  90 C5 00 1C */	stw r6, 0x1c(r5)
/* 8013B844 00136744  7C 7D 1A 14 */	add r3, r29, r3
/* 8013B848 00136748  1C 00 00 14 */	mulli r0, r0, 0x14
/* 8013B84C 0013674C  93 83 00 20 */	stw r28, 0x20(r3)
/* 8013B850 00136750  7C 7D 02 14 */	add r3, r29, r0
/* 8013B854 00136754  90 83 00 24 */	stw r4, 0x24(r3)
/* 8013B858 00136758  4B FB 9D C5 */	bl OSGetTick
/* 8013B85C 0013675C  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B860 00136760  80 8D 9F 98 */	lwz r4, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B864 00136764  1C A0 00 14 */	mulli r5, r0, 0x14
/* 8013B868 00136768  38 04 00 01 */	addi r0, r4, 1
/* 8013B86C 0013676C  90 0D 9F 98 */	stw r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B870 00136770  7C 9D 2A 14 */	add r4, r29, r5
/* 8013B874 00136774  90 64 00 2C */	stw r3, 0x2c(r4)
/* 8013B878 00136778  7F C3 F3 78 */	mr r3, r30
/* 8013B87C 0013677C  4B FB 60 6D */	bl OSRestoreInterrupts
/* 8013B880 00136780  80 6D 9F E0 */	lwz r3, BootGameInfo-_SDA_BASE_(r13)
/* 8013B884 00136784  3D 00 80 14 */	lis r8, cbForStateOpenPartition@ha
/* 8013B888 00136788  38 FF 01 40 */	addi r7, r31, 0x140
/* 8013B88C 0013678C  38 80 00 00 */	li r4, 0
/* 8013B890 00136790  80 63 00 00 */	lwz r3, 0(r3)
/* 8013B894 00136794  39 08 BA A0 */	addi r8, r8, cbForStateOpenPartition@l
/* 8013B898 00136798  38 A0 00 00 */	li r5, 0
/* 8013B89C 0013679C  38 C0 00 00 */	li r6, 0
/* 8013B8A0 001367A0  48 00 38 29 */	bl DVDLowOpenPartition
/* 8013B8A4 001367A4  48 00 01 DC */	b lbl_8013BA80
lbl_8013B8A8:
/* 8013B8A8 001367A8  3B A0 00 00 */	li r29, 0
/* 8013B8AC 001367AC  38 60 00 00 */	li r3, 0
/* 8013B8B0 001367B0  93 AD 9F B0 */	stw r29, NumInternalRetry-_SDA_BASE_(r13)
/* 8013B8B4 001367B4  48 00 4B 35 */	bl DVDLowClearCoverInterrupt
/* 8013B8B8 001367B8  80 6D 9F E0 */	lwz r3, BootGameInfo-_SDA_BASE_(r13)
/* 8013B8BC 001367BC  83 83 00 00 */	lwz r28, 0(r3)
/* 8013B8C0 001367C0  4B FB 60 01 */	bl OSDisableInterrupts
/* 8013B8C4 001367C4  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B8C8 001367C8  7C 7E 1B 78 */	mr r30, r3
/* 8013B8CC 001367CC  28 00 00 05 */	cmplwi r0, 5
/* 8013B8D0 001367D0  41 80 00 08 */	blt lbl_8013B8D8
/* 8013B8D4 001367D4  93 AD 9F 98 */	stw r29, CommandInfoCounter-_SDA_BASE_(r13)
lbl_8013B8D8:
/* 8013B8D8 001367D8  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B8DC 001367DC  3F A0 80 48 */	lis r29, __ErrorInfo@ha
/* 8013B8E0 001367E0  80 6D 9F 98 */	lwz r3, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B8E4 001367E4  3B BD A2 20 */	addi r29, r29, __ErrorInfo@l
/* 8013B8E8 001367E8  1C A0 00 14 */	mulli r5, r0, 0x14
/* 8013B8EC 001367EC  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B8F0 001367F0  38 C0 00 22 */	li r6, 0x22
/* 8013B8F4 001367F4  38 80 00 00 */	li r4, 0
/* 8013B8F8 001367F8  1C 63 00 14 */	mulli r3, r3, 0x14
/* 8013B8FC 001367FC  7C BD 2A 14 */	add r5, r29, r5
/* 8013B900 00136800  90 C5 00 1C */	stw r6, 0x1c(r5)
/* 8013B904 00136804  7C 7D 1A 14 */	add r3, r29, r3
/* 8013B908 00136808  1C 00 00 14 */	mulli r0, r0, 0x14
/* 8013B90C 0013680C  93 83 00 20 */	stw r28, 0x20(r3)
/* 8013B910 00136810  7C 7D 02 14 */	add r3, r29, r0
/* 8013B914 00136814  90 83 00 24 */	stw r4, 0x24(r3)
/* 8013B918 00136818  4B FB 9D 05 */	bl OSGetTick
/* 8013B91C 0013681C  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B920 00136820  80 8D 9F 98 */	lwz r4, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B924 00136824  1C A0 00 14 */	mulli r5, r0, 0x14
/* 8013B928 00136828  38 04 00 01 */	addi r0, r4, 1
/* 8013B92C 0013682C  90 0D 9F 98 */	stw r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013B930 00136830  7C 9D 2A 14 */	add r4, r29, r5
/* 8013B934 00136834  90 64 00 2C */	stw r3, 0x2c(r4)
/* 8013B938 00136838  7F C3 F3 78 */	mr r3, r30
/* 8013B93C 0013683C  4B FB 5F AD */	bl OSRestoreInterrupts
/* 8013B940 00136840  80 6D 9F E0 */	lwz r3, BootGameInfo-_SDA_BASE_(r13)
/* 8013B944 00136844  3D 00 80 14 */	lis r8, cbForStateOpenPartition2@ha
/* 8013B948 00136848  38 FF 01 40 */	addi r7, r31, 0x140
/* 8013B94C 0013684C  38 80 00 00 */	li r4, 0
/* 8013B950 00136850  80 63 00 00 */	lwz r3, 0(r3)
/* 8013B954 00136854  39 08 BC 28 */	addi r8, r8, cbForStateOpenPartition2@l
/* 8013B958 00136858  38 A0 00 00 */	li r5, 0
/* 8013B95C 0013685C  38 C0 00 00 */	li r6, 0
/* 8013B960 00136860  48 00 37 69 */	bl DVDLowOpenPartition
/* 8013B964 00136864  48 00 01 1C */	b lbl_8013BA80
lbl_8013B968:
/* 8013B968 00136868  80 0D 9F A8 */	lwz r0, Canceling-_SDA_BASE_(r13)
/* 8013B96C 0013686C  2C 00 00 00 */	cmpwi r0, 0
/* 8013B970 00136870  41 82 00 6C */	beq lbl_8013B9DC
/* 8013B974 00136874  83 8D A0 18 */	lwz r28, executing-_SDA_BASE_(r13)
/* 8013B978 00136878  38 7F 00 20 */	addi r3, r31, 0x20
/* 8013B97C 0013687C  38 00 00 01 */	li r0, 1
/* 8013B980 00136880  38 80 00 00 */	li r4, 0
/* 8013B984 00136884  90 0D 9F AC */	stw r0, ResumeFromHere-_SDA_BASE_(r13)
/* 8013B988 00136888  38 00 00 0A */	li r0, 0xa
/* 8013B98C 0013688C  90 8D 9F A8 */	stw r4, Canceling-_SDA_BASE_(r13)
/* 8013B990 00136890  90 6D A0 18 */	stw r3, executing-_SDA_BASE_(r13)
/* 8013B994 00136894  90 1C 00 0C */	stw r0, 0xc(r28)
/* 8013B998 00136898  81 9C 00 28 */	lwz r12, 0x28(r28)
/* 8013B99C 0013689C  2C 0C 00 00 */	cmpwi r12, 0
/* 8013B9A0 001368A0  41 82 00 14 */	beq lbl_8013B9B4
/* 8013B9A4 001368A4  7F 84 E3 78 */	mr r4, r28
/* 8013B9A8 001368A8  38 60 FF FD */	li r3, -3
/* 8013B9AC 001368AC  7D 89 03 A6 */	mtctr r12
/* 8013B9B0 001368B0  4E 80 04 21 */	bctrl 
lbl_8013B9B4:
/* 8013B9B4 001368B4  81 8D A0 08 */	lwz r12, CancelCallback-_SDA_BASE_(r13)
/* 8013B9B8 001368B8  2C 0C 00 00 */	cmpwi r12, 0
/* 8013B9BC 001368BC  41 82 00 14 */	beq lbl_8013B9D0
/* 8013B9C0 001368C0  7F 84 E3 78 */	mr r4, r28
/* 8013B9C4 001368C4  38 60 00 00 */	li r3, 0
/* 8013B9C8 001368C8  7D 89 03 A6 */	mtctr r12
/* 8013B9CC 001368CC  4E 80 04 21 */	bctrl 
lbl_8013B9D0:
/* 8013B9D0 001368D0  48 00 10 1D */	bl stateReady
/* 8013B9D4 001368D4  38 00 00 01 */	li r0, 1
/* 8013B9D8 001368D8  48 00 00 08 */	b lbl_8013B9E0
lbl_8013B9DC:
/* 8013B9DC 001368DC  38 00 00 00 */	li r0, 0
lbl_8013B9E0:
/* 8013B9E0 001368E0  2C 00 00 00 */	cmpwi r0, 0
/* 8013B9E4 001368E4  40 82 00 9C */	bne lbl_8013BA80
/* 8013B9E8 001368E8  80 8D A0 18 */	lwz r4, executing-_SDA_BASE_(r13)
/* 8013B9EC 001368EC  38 00 00 06 */	li r0, 6
/* 8013B9F0 001368F0  38 60 00 01 */	li r3, 1
/* 8013B9F4 001368F4  90 04 00 0C */	stw r0, 0xc(r4)
/* 8013B9F8 001368F8  80 0D 9F BC */	lwz r0, WaitingForCoverOpen-_SDA_BASE_(r13)
/* 8013B9FC 001368FC  90 6D 9F F8 */	stw r3, MotorState-_SDA_BASE_(r13)
/* 8013BA00 00136900  2C 00 00 00 */	cmpwi r0, 0
/* 8013BA04 00136904  40 82 00 7C */	bne lbl_8013BA80
/* 8013BA08 00136908  80 0D 9F C0 */	lwz r0, WaitingForCoverClose-_SDA_BASE_(r13)
/* 8013BA0C 0013690C  2C 00 00 00 */	cmpwi r0, 0
/* 8013BA10 00136910  40 82 00 70 */	bne lbl_8013BA80
/* 8013BA14 00136914  90 6D 9F BC */	stw r3, WaitingForCoverOpen-_SDA_BASE_(r13)
/* 8013BA18 00136918  38 7F 00 80 */	addi r3, r31, 0x80
/* 8013BA1C 0013691C  4B FB 16 F9 */	bl OSCreateAlarm
/* 8013BA20 00136920  4B FB 9B FD */	bl OSGetTick
/* 8013BA24 00136924  3C A0 80 00 */	lis r5, 0x800000F8@ha
/* 8013BA28 00136928  3C 80 10 62 */	lis r4, 0x10624DD3@ha
/* 8013BA2C 0013692C  80 05 00 F8 */	lwz r0, 0x800000F8@l(r5)
/* 8013BA30 00136930  3D 20 80 14 */	lis r9, CoverAlarmHandler@ha
/* 8013BA34 00136934  7C 66 1B 78 */	mr r6, r3
/* 8013BA38 00136938  38 84 4D D3 */	addi r4, r4, 0x10624DD3@l
/* 8013BA3C 0013693C  54 00 F0 BE */	srwi r0, r0, 2
/* 8013BA40 00136940  38 7F 00 80 */	addi r3, r31, 0x80
/* 8013BA44 00136944  7C 04 00 16 */	mulhwu r0, r4, r0
/* 8013BA48 00136948  39 29 C9 C8 */	addi r9, r9, CoverAlarmHandler@l
/* 8013BA4C 0013694C  38 A0 00 00 */	li r5, 0
/* 8013BA50 00136950  38 E0 00 00 */	li r7, 0
/* 8013BA54 00136954  54 00 D1 BE */	srwi r0, r0, 6
/* 8013BA58 00136958  1D 00 00 64 */	mulli r8, r0, 0x64
/* 8013BA5C 0013695C  4B FB 19 89 */	bl OSSetPeriodicAlarm
/* 8013BA60 00136960  48 00 00 20 */	b lbl_8013BA80
lbl_8013BA64:
/* 8013BA64 00136964  38 60 00 27 */	li r3, 0x27
/* 8013BA68 00136968  38 80 00 00 */	li r4, 0
/* 8013BA6C 0013696C  38 A0 00 00 */	li r5, 0
/* 8013BA70 00136970  4B FF E5 F9 */	bl StampCommand
/* 8013BA74 00136974  3C 60 80 14 */	lis r3, cbForStateGettingError@ha
/* 8013BA78 00136978  38 63 A8 18 */	addi r3, r3, cbForStateGettingError@l
/* 8013BA7C 0013697C  48 00 3E A9 */	bl DVDLowRequestError
lbl_8013BA80:
/* 8013BA80 00136980  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8013BA84 00136984  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8013BA88 00136988  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8013BA8C 0013698C  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8013BA90 00136990  83 81 00 10 */	lwz r28, 0x10(r1)
/* 8013BA94 00136994  7C 08 03 A6 */	mtlr r0
/* 8013BA98 00136998  38 21 00 20 */	addi r1, r1, 0x20
/* 8013BA9C 0013699C  4E 80 00 20 */	blr 

.global cbForStateOpenPartition
cbForStateOpenPartition:
/* 8013BAA0 001369A0  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8013BAA4 001369A4  7C 08 02 A6 */	mflr r0
/* 8013BAA8 001369A8  90 01 00 14 */	stw r0, 0x14(r1)
/* 8013BAAC 001369AC  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8013BAB0 001369B0  93 C1 00 08 */	stw r30, 8(r1)
/* 8013BAB4 001369B4  7C 7E 1B 78 */	mr r30, r3
/* 8013BAB8 001369B8  4B FB 5E 09 */	bl OSDisableInterrupts
/* 8013BABC 001369BC  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013BAC0 001369C0  2C 00 00 00 */	cmpwi r0, 0
/* 8013BAC4 001369C4  40 82 00 14 */	bne lbl_8013BAD8
/* 8013BAC8 001369C8  3C 80 80 48 */	lis r4, __ErrorInfo@ha
/* 8013BACC 001369CC  38 84 A2 20 */	addi r4, r4, __ErrorInfo@l
/* 8013BAD0 001369D0  93 C4 00 78 */	stw r30, 0x78(r4)
/* 8013BAD4 001369D4  48 00 00 20 */	b lbl_8013BAF4
lbl_8013BAD8:
/* 8013BAD8 001369D8  80 8D 9F 98 */	lwz r4, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013BADC 001369DC  3C A0 80 48 */	lis r5, __ErrorInfo@ha
/* 8013BAE0 001369E0  38 A5 A2 20 */	addi r5, r5, __ErrorInfo@l
/* 8013BAE4 001369E4  38 04 FF FF */	addi r0, r4, -1
/* 8013BAE8 001369E8  1C 00 00 14 */	mulli r0, r0, 0x14
/* 8013BAEC 001369EC  7C 85 02 14 */	add r4, r5, r0
/* 8013BAF0 001369F0  93 C4 00 28 */	stw r30, 0x28(r4)
lbl_8013BAF4:
/* 8013BAF4 001369F4  4B FB 5D F5 */	bl OSRestoreInterrupts
/* 8013BAF8 001369F8  28 1E 00 10 */	cmplwi r30, 0x10
/* 8013BAFC 001369FC  40 82 00 1C */	bne lbl_8013BB18
/* 8013BB00 00136A00  3C 60 01 23 */	lis r3, 0x01234568@ha
/* 8013BB04 00136A04  3C 80 80 14 */	lis r4, cbForStoreErrorCode2@ha
/* 8013BB08 00136A08  38 63 45 68 */	addi r3, r3, 0x01234568@l
/* 8013BB0C 00136A0C  38 84 A6 24 */	addi r4, r4, cbForStoreErrorCode2@l
/* 8013BB10 00136A10  48 00 2D 89 */	bl __DVDStoreErrorCode
/* 8013BB14 00136A14  48 00 00 FC */	b lbl_8013BC10
lbl_8013BB18:
/* 8013BB18 00136A18  28 1E 00 20 */	cmplwi r30, 0x20
/* 8013BB1C 00136A1C  40 82 00 1C */	bne lbl_8013BB38
/* 8013BB20 00136A20  3C 60 01 23 */	lis r3, 0x01234569@ha
/* 8013BB24 00136A24  3C 80 80 14 */	lis r4, cbForStoreErrorCode2@ha
/* 8013BB28 00136A28  38 63 45 69 */	addi r3, r3, 0x01234569@l
/* 8013BB2C 00136A2C  38 84 A6 24 */	addi r4, r4, cbForStoreErrorCode2@l
/* 8013BB30 00136A30  48 00 2D 69 */	bl __DVDStoreErrorCode
/* 8013BB34 00136A34  48 00 00 DC */	b lbl_8013BC10
lbl_8013BB38:
/* 8013BB38 00136A38  57 C0 07 FF */	clrlwi. r0, r30, 0x1f
/* 8013BB3C 00136A3C  41 82 00 B8 */	beq lbl_8013BBF4
/* 8013BB40 00136A40  3B C0 00 00 */	li r30, 0
/* 8013BB44 00136A44  38 60 00 00 */	li r3, 0
/* 8013BB48 00136A48  93 CD 9F B0 */	stw r30, NumInternalRetry-_SDA_BASE_(r13)
/* 8013BB4C 00136A4C  48 00 48 9D */	bl DVDLowClearCoverInterrupt
/* 8013BB50 00136A50  4B FB 5D 71 */	bl OSDisableInterrupts
/* 8013BB54 00136A54  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013BB58 00136A58  7C 7F 1B 78 */	mr r31, r3
/* 8013BB5C 00136A5C  28 00 00 05 */	cmplwi r0, 5
/* 8013BB60 00136A60  41 80 00 08 */	blt lbl_8013BB68
/* 8013BB64 00136A64  93 CD 9F 98 */	stw r30, CommandInfoCounter-_SDA_BASE_(r13)
lbl_8013BB68:
/* 8013BB68 00136A68  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013BB6C 00136A6C  3F C0 80 48 */	lis r30, __ErrorInfo@ha
/* 8013BB70 00136A70  80 6D 9F 98 */	lwz r3, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013BB74 00136A74  3B DE A2 20 */	addi r30, r30, __ErrorInfo@l
/* 8013BB78 00136A78  1C C0 00 14 */	mulli r6, r0, 0x14
/* 8013BB7C 00136A7C  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013BB80 00136A80  38 E0 00 01 */	li r7, 1
/* 8013BB84 00136A84  38 A0 01 08 */	li r5, 0x108
/* 8013BB88 00136A88  1C 63 00 14 */	mulli r3, r3, 0x14
/* 8013BB8C 00136A8C  38 80 00 20 */	li r4, 0x20
/* 8013BB90 00136A90  7C DE 32 14 */	add r6, r30, r6
/* 8013BB94 00136A94  90 E6 00 1C */	stw r7, 0x1c(r6)
/* 8013BB98 00136A98  7C 7E 1A 14 */	add r3, r30, r3
/* 8013BB9C 00136A9C  1C 00 00 14 */	mulli r0, r0, 0x14
/* 8013BBA0 00136AA0  90 A3 00 20 */	stw r5, 0x20(r3)
/* 8013BBA4 00136AA4  7C 7E 02 14 */	add r3, r30, r0
/* 8013BBA8 00136AA8  90 83 00 24 */	stw r4, 0x24(r3)
/* 8013BBAC 00136AAC  4B FB 9A 71 */	bl OSGetTick
/* 8013BBB0 00136AB0  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013BBB4 00136AB4  80 8D 9F 98 */	lwz r4, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013BBB8 00136AB8  1C A0 00 14 */	mulli r5, r0, 0x14
/* 8013BBBC 00136ABC  38 04 00 01 */	addi r0, r4, 1
/* 8013BBC0 00136AC0  90 0D 9F 98 */	stw r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013BBC4 00136AC4  7C 9E 2A 14 */	add r4, r30, r5
/* 8013BBC8 00136AC8  90 64 00 2C */	stw r3, 0x2c(r4)
/* 8013BBCC 00136ACC  7F E3 FB 78 */	mr r3, r31
/* 8013BBD0 00136AD0  4B FB 5D 19 */	bl OSRestoreInterrupts
/* 8013BBD4 00136AD4  3C 60 80 47 */	lis r3, BB2@ha
/* 8013BBD8 00136AD8  3C C0 80 14 */	lis r6, cbForStateCheckID2@ha
/* 8013BBDC 00136ADC  38 63 54 C0 */	addi r3, r3, BB2@l
/* 8013BBE0 00136AE0  38 80 00 20 */	li r4, 0x20
/* 8013BBE4 00136AE4  38 C6 BF 54 */	addi r6, r6, cbForStateCheckID2@l
/* 8013BBE8 00136AE8  38 A0 01 08 */	li r5, 0x108
/* 8013BBEC 00136AEC  48 00 43 3D */	bl DVDLowRead
/* 8013BBF0 00136AF0  48 00 00 20 */	b lbl_8013BC10
lbl_8013BBF4:
/* 8013BBF4 00136AF4  38 60 00 27 */	li r3, 0x27
/* 8013BBF8 00136AF8  38 80 00 00 */	li r4, 0
/* 8013BBFC 00136AFC  38 A0 00 00 */	li r5, 0
/* 8013BC00 00136B00  4B FF E4 69 */	bl StampCommand
/* 8013BC04 00136B04  3C 60 80 14 */	lis r3, cbForStateGettingError@ha
/* 8013BC08 00136B08  38 63 A8 18 */	addi r3, r3, cbForStateGettingError@l
/* 8013BC0C 00136B0C  48 00 3D 19 */	bl DVDLowRequestError
lbl_8013BC10:
/* 8013BC10 00136B10  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8013BC14 00136B14  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8013BC18 00136B18  83 C1 00 08 */	lwz r30, 8(r1)
/* 8013BC1C 00136B1C  7C 08 03 A6 */	mtlr r0
/* 8013BC20 00136B20  38 21 00 10 */	addi r1, r1, 0x10
/* 8013BC24 00136B24  4E 80 00 20 */	blr 

.global cbForStateOpenPartition2
cbForStateOpenPartition2:
/* 8013BC28 00136B28  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8013BC2C 00136B2C  7C 08 02 A6 */	mflr r0
/* 8013BC30 00136B30  90 01 00 14 */	stw r0, 0x14(r1)
/* 8013BC34 00136B34  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8013BC38 00136B38  7C 7F 1B 78 */	mr r31, r3
/* 8013BC3C 00136B3C  4B FB 5C 85 */	bl OSDisableInterrupts
/* 8013BC40 00136B40  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013BC44 00136B44  2C 00 00 00 */	cmpwi r0, 0
/* 8013BC48 00136B48  40 82 00 14 */	bne lbl_8013BC5C
/* 8013BC4C 00136B4C  3C 80 80 48 */	lis r4, __ErrorInfo@ha
/* 8013BC50 00136B50  38 84 A2 20 */	addi r4, r4, __ErrorInfo@l
/* 8013BC54 00136B54  93 E4 00 78 */	stw r31, 0x78(r4)
/* 8013BC58 00136B58  48 00 00 1C */	b lbl_8013BC74
lbl_8013BC5C:
/* 8013BC5C 00136B5C  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013BC60 00136B60  3C 80 80 48 */	lis r4, __ErrorInfo@ha
/* 8013BC64 00136B64  38 84 A2 20 */	addi r4, r4, __ErrorInfo@l
/* 8013BC68 00136B68  1C 00 00 14 */	mulli r0, r0, 0x14
/* 8013BC6C 00136B6C  7C 84 02 14 */	add r4, r4, r0
/* 8013BC70 00136B70  93 E4 00 14 */	stw r31, 0x14(r4)
lbl_8013BC74:
/* 8013BC74 00136B74  4B FB 5C 75 */	bl OSRestoreInterrupts
/* 8013BC78 00136B78  28 1F 00 10 */	cmplwi r31, 0x10
/* 8013BC7C 00136B7C  40 82 00 1C */	bne lbl_8013BC98
/* 8013BC80 00136B80  3C 60 01 23 */	lis r3, 0x01234568@ha
/* 8013BC84 00136B84  3C 80 80 14 */	lis r4, cbForStoreErrorCode2@ha
/* 8013BC88 00136B88  38 63 45 68 */	addi r3, r3, 0x01234568@l
/* 8013BC8C 00136B8C  38 84 A6 24 */	addi r4, r4, cbForStoreErrorCode2@l
/* 8013BC90 00136B90  48 00 2C 09 */	bl __DVDStoreErrorCode
/* 8013BC94 00136B94  48 00 00 E4 */	b lbl_8013BD78
lbl_8013BC98:
/* 8013BC98 00136B98  28 1F 00 20 */	cmplwi r31, 0x20
/* 8013BC9C 00136B9C  40 82 00 1C */	bne lbl_8013BCB8
/* 8013BCA0 00136BA0  3C 60 01 23 */	lis r3, 0x01234569@ha
/* 8013BCA4 00136BA4  3C 80 80 14 */	lis r4, cbForStoreErrorCode2@ha
/* 8013BCA8 00136BA8  38 63 45 69 */	addi r3, r3, 0x01234569@l
/* 8013BCAC 00136BAC  38 84 A6 24 */	addi r4, r4, cbForStoreErrorCode2@l
/* 8013BCB0 00136BB0  48 00 2B E9 */	bl __DVDStoreErrorCode
/* 8013BCB4 00136BB4  48 00 00 C4 */	b lbl_8013BD78
lbl_8013BCB8:
/* 8013BCB8 00136BB8  57 E0 07 FF */	clrlwi. r0, r31, 0x1f
/* 8013BCBC 00136BBC  41 82 00 A0 */	beq lbl_8013BD5C
/* 8013BCC0 00136BC0  38 80 00 00 */	li r4, 0
/* 8013BCC4 00136BC4  90 8D 9F B0 */	stw r4, NumInternalRetry-_SDA_BASE_(r13)
/* 8013BCC8 00136BC8  80 0D 9F A8 */	lwz r0, Canceling-_SDA_BASE_(r13)
/* 8013BCCC 00136BCC  2C 00 00 00 */	cmpwi r0, 0
/* 8013BCD0 00136BD0  41 82 00 68 */	beq lbl_8013BD38
/* 8013BCD4 00136BD4  3C 60 80 47 */	lis r3, DummyCommandBlock@ha
/* 8013BCD8 00136BD8  83 ED A0 18 */	lwz r31, executing-_SDA_BASE_(r13)
/* 8013BCDC 00136BDC  38 63 54 E0 */	addi r3, r3, DummyCommandBlock@l
/* 8013BCE0 00136BE0  90 8D 9F AC */	stw r4, ResumeFromHere-_SDA_BASE_(r13)
/* 8013BCE4 00136BE4  38 00 00 0A */	li r0, 0xa
/* 8013BCE8 00136BE8  90 8D 9F A8 */	stw r4, Canceling-_SDA_BASE_(r13)
/* 8013BCEC 00136BEC  90 6D A0 18 */	stw r3, executing-_SDA_BASE_(r13)
/* 8013BCF0 00136BF0  90 1F 00 0C */	stw r0, 0xc(r31)
/* 8013BCF4 00136BF4  81 9F 00 28 */	lwz r12, 0x28(r31)
/* 8013BCF8 00136BF8  2C 0C 00 00 */	cmpwi r12, 0
/* 8013BCFC 00136BFC  41 82 00 14 */	beq lbl_8013BD10
/* 8013BD00 00136C00  7F E4 FB 78 */	mr r4, r31
/* 8013BD04 00136C04  38 60 FF FD */	li r3, -3
/* 8013BD08 00136C08  7D 89 03 A6 */	mtctr r12
/* 8013BD0C 00136C0C  4E 80 04 21 */	bctrl 
lbl_8013BD10:
/* 8013BD10 00136C10  81 8D A0 08 */	lwz r12, CancelCallback-_SDA_BASE_(r13)
/* 8013BD14 00136C14  2C 0C 00 00 */	cmpwi r12, 0
/* 8013BD18 00136C18  41 82 00 14 */	beq lbl_8013BD2C
/* 8013BD1C 00136C1C  7F E4 FB 78 */	mr r4, r31
/* 8013BD20 00136C20  38 60 00 00 */	li r3, 0
/* 8013BD24 00136C24  7D 89 03 A6 */	mtctr r12
/* 8013BD28 00136C28  4E 80 04 21 */	bctrl 
lbl_8013BD2C:
/* 8013BD2C 00136C2C  48 00 0C C1 */	bl stateReady
/* 8013BD30 00136C30  38 00 00 01 */	li r0, 1
/* 8013BD34 00136C34  48 00 00 08 */	b lbl_8013BD3C
lbl_8013BD38:
/* 8013BD38 00136C38  38 00 00 00 */	li r0, 0
lbl_8013BD3C:
/* 8013BD3C 00136C3C  2C 00 00 00 */	cmpwi r0, 0
/* 8013BD40 00136C40  40 82 00 38 */	bne lbl_8013BD78
/* 8013BD44 00136C44  80 6D A0 18 */	lwz r3, executing-_SDA_BASE_(r13)
/* 8013BD48 00136C48  38 00 00 01 */	li r0, 1
/* 8013BD4C 00136C4C  90 03 00 0C */	stw r0, 0xc(r3)
/* 8013BD50 00136C50  80 6D A0 18 */	lwz r3, executing-_SDA_BASE_(r13)
/* 8013BD54 00136C54  48 00 0F C1 */	bl stateBusy
/* 8013BD58 00136C58  48 00 00 20 */	b lbl_8013BD78
lbl_8013BD5C:
/* 8013BD5C 00136C5C  38 60 00 27 */	li r3, 0x27
/* 8013BD60 00136C60  38 80 00 00 */	li r4, 0
/* 8013BD64 00136C64  38 A0 00 00 */	li r5, 0
/* 8013BD68 00136C68  4B FF E3 01 */	bl StampCommand
/* 8013BD6C 00136C6C  3C 60 80 14 */	lis r3, cbForStateGettingError@ha
/* 8013BD70 00136C70  38 63 A8 18 */	addi r3, r3, cbForStateGettingError@l
/* 8013BD74 00136C74  48 00 3B B1 */	bl DVDLowRequestError
lbl_8013BD78:
/* 8013BD78 00136C78  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8013BD7C 00136C7C  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8013BD80 00136C80  7C 08 03 A6 */	mtlr r0
/* 8013BD84 00136C84  38 21 00 10 */	addi r1, r1, 0x10
/* 8013BD88 00136C88  4E 80 00 20 */	blr 

.global cbForStateCheckID1
cbForStateCheckID1:
/* 8013BD8C 00136C8C  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8013BD90 00136C90  7C 08 02 A6 */	mflr r0
/* 8013BD94 00136C94  90 01 00 14 */	stw r0, 0x14(r1)
/* 8013BD98 00136C98  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8013BD9C 00136C9C  7C 7F 1B 78 */	mr r31, r3
/* 8013BDA0 00136CA0  4B FB 5B 21 */	bl OSDisableInterrupts
/* 8013BDA4 00136CA4  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013BDA8 00136CA8  2C 00 00 00 */	cmpwi r0, 0
/* 8013BDAC 00136CAC  40 82 00 14 */	bne lbl_8013BDC0
/* 8013BDB0 00136CB0  3C 80 80 48 */	lis r4, __ErrorInfo@ha
/* 8013BDB4 00136CB4  38 84 A2 20 */	addi r4, r4, __ErrorInfo@l
/* 8013BDB8 00136CB8  93 E4 00 78 */	stw r31, 0x78(r4)
/* 8013BDBC 00136CBC  48 00 00 1C */	b lbl_8013BDD8
lbl_8013BDC0:
/* 8013BDC0 00136CC0  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013BDC4 00136CC4  3C 80 80 48 */	lis r4, __ErrorInfo@ha
/* 8013BDC8 00136CC8  38 84 A2 20 */	addi r4, r4, __ErrorInfo@l
/* 8013BDCC 00136CCC  1C 00 00 14 */	mulli r0, r0, 0x14
/* 8013BDD0 00136CD0  7C 84 02 14 */	add r4, r4, r0
/* 8013BDD4 00136CD4  93 E4 00 14 */	stw r31, 0x14(r4)
lbl_8013BDD8:
/* 8013BDD8 00136CD8  4B FB 5B 11 */	bl OSRestoreInterrupts
/* 8013BDDC 00136CDC  28 1F 00 10 */	cmplwi r31, 0x10
/* 8013BDE0 00136CE0  40 82 00 1C */	bne lbl_8013BDFC
/* 8013BDE4 00136CE4  3C 60 01 23 */	lis r3, 0x01234568@ha
/* 8013BDE8 00136CE8  3C 80 80 14 */	lis r4, cbForStoreErrorCode2@ha
/* 8013BDEC 00136CEC  38 63 45 68 */	addi r3, r3, 0x01234568@l
/* 8013BDF0 00136CF0  38 84 A6 24 */	addi r4, r4, cbForStoreErrorCode2@l
/* 8013BDF4 00136CF4  48 00 2A A5 */	bl __DVDStoreErrorCode
/* 8013BDF8 00136CF8  48 00 01 48 */	b lbl_8013BF40
lbl_8013BDFC:
/* 8013BDFC 00136CFC  28 1F 00 20 */	cmplwi r31, 0x20
/* 8013BE00 00136D00  40 82 00 1C */	bne lbl_8013BE1C
/* 8013BE04 00136D04  3C 60 01 23 */	lis r3, 0x01234569@ha
/* 8013BE08 00136D08  3C 80 80 14 */	lis r4, cbForStoreErrorCode2@ha
/* 8013BE0C 00136D0C  38 63 45 69 */	addi r3, r3, 0x01234569@l
/* 8013BE10 00136D10  38 84 A6 24 */	addi r4, r4, cbForStoreErrorCode2@l
/* 8013BE14 00136D14  48 00 2A 85 */	bl __DVDStoreErrorCode
/* 8013BE18 00136D18  48 00 01 28 */	b lbl_8013BF40
lbl_8013BE1C:
/* 8013BE1C 00136D1C  57 E0 07 BD */	rlwinm. r0, r31, 0, 0x1e, 0x1e
/* 8013BE20 00136D20  41 82 00 1C */	beq lbl_8013BE3C
/* 8013BE24 00136D24  3C 60 01 23 */	lis r3, 0x01234567@ha
/* 8013BE28 00136D28  3C 80 80 14 */	lis r4, cbForStoreErrorCode1@ha
/* 8013BE2C 00136D2C  38 63 45 67 */	addi r3, r3, 0x01234567@l
/* 8013BE30 00136D30  38 84 A6 10 */	addi r4, r4, cbForStoreErrorCode1@l
/* 8013BE34 00136D34  48 00 2A 65 */	bl __DVDStoreErrorCode
/* 8013BE38 00136D38  48 00 01 08 */	b lbl_8013BF40
lbl_8013BE3C:
/* 8013BE3C 00136D3C  38 80 00 00 */	li r4, 0
/* 8013BE40 00136D40  90 8D 9F B0 */	stw r4, NumInternalRetry-_SDA_BASE_(r13)
/* 8013BE44 00136D44  80 0D 9F A8 */	lwz r0, Canceling-_SDA_BASE_(r13)
/* 8013BE48 00136D48  2C 00 00 00 */	cmpwi r0, 0
/* 8013BE4C 00136D4C  41 82 00 6C */	beq lbl_8013BEB8
/* 8013BE50 00136D50  3C 60 80 47 */	lis r3, DummyCommandBlock@ha
/* 8013BE54 00136D54  83 ED A0 18 */	lwz r31, executing-_SDA_BASE_(r13)
/* 8013BE58 00136D58  38 63 54 E0 */	addi r3, r3, DummyCommandBlock@l
/* 8013BE5C 00136D5C  38 00 00 01 */	li r0, 1
/* 8013BE60 00136D60  90 0D 9F AC */	stw r0, ResumeFromHere-_SDA_BASE_(r13)
/* 8013BE64 00136D64  38 00 00 0A */	li r0, 0xa
/* 8013BE68 00136D68  90 8D 9F A8 */	stw r4, Canceling-_SDA_BASE_(r13)
/* 8013BE6C 00136D6C  90 6D A0 18 */	stw r3, executing-_SDA_BASE_(r13)
/* 8013BE70 00136D70  90 1F 00 0C */	stw r0, 0xc(r31)
/* 8013BE74 00136D74  81 9F 00 28 */	lwz r12, 0x28(r31)
/* 8013BE78 00136D78  2C 0C 00 00 */	cmpwi r12, 0
/* 8013BE7C 00136D7C  41 82 00 14 */	beq lbl_8013BE90
/* 8013BE80 00136D80  7F E4 FB 78 */	mr r4, r31
/* 8013BE84 00136D84  38 60 FF FD */	li r3, -3
/* 8013BE88 00136D88  7D 89 03 A6 */	mtctr r12
/* 8013BE8C 00136D8C  4E 80 04 21 */	bctrl 
lbl_8013BE90:
/* 8013BE90 00136D90  81 8D A0 08 */	lwz r12, CancelCallback-_SDA_BASE_(r13)
/* 8013BE94 00136D94  2C 0C 00 00 */	cmpwi r12, 0
/* 8013BE98 00136D98  41 82 00 14 */	beq lbl_8013BEAC
/* 8013BE9C 00136D9C  7F E4 FB 78 */	mr r4, r31
/* 8013BEA0 00136DA0  38 60 00 00 */	li r3, 0
/* 8013BEA4 00136DA4  7D 89 03 A6 */	mtctr r12
/* 8013BEA8 00136DA8  4E 80 04 21 */	bctrl 
lbl_8013BEAC:
/* 8013BEAC 00136DAC  48 00 0B 41 */	bl stateReady
/* 8013BEB0 00136DB0  38 00 00 01 */	li r0, 1
/* 8013BEB4 00136DB4  48 00 00 08 */	b lbl_8013BEBC
lbl_8013BEB8:
/* 8013BEB8 00136DB8  38 00 00 00 */	li r0, 0
lbl_8013BEBC:
/* 8013BEBC 00136DBC  2C 00 00 00 */	cmpwi r0, 0
/* 8013BEC0 00136DC0  40 82 00 80 */	bne lbl_8013BF40
/* 8013BEC4 00136DC4  80 8D A0 18 */	lwz r4, executing-_SDA_BASE_(r13)
/* 8013BEC8 00136DC8  38 00 00 06 */	li r0, 6
/* 8013BECC 00136DCC  38 60 00 01 */	li r3, 1
/* 8013BED0 00136DD0  90 04 00 0C */	stw r0, 0xc(r4)
/* 8013BED4 00136DD4  80 0D 9F BC */	lwz r0, WaitingForCoverOpen-_SDA_BASE_(r13)
/* 8013BED8 00136DD8  90 6D 9F F8 */	stw r3, MotorState-_SDA_BASE_(r13)
/* 8013BEDC 00136DDC  2C 00 00 00 */	cmpwi r0, 0
/* 8013BEE0 00136DE0  40 82 00 60 */	bne lbl_8013BF40
/* 8013BEE4 00136DE4  80 0D 9F C0 */	lwz r0, WaitingForCoverClose-_SDA_BASE_(r13)
/* 8013BEE8 00136DE8  2C 00 00 00 */	cmpwi r0, 0
/* 8013BEEC 00136DEC  40 82 00 54 */	bne lbl_8013BF40
/* 8013BEF0 00136DF0  3F E0 80 47 */	lis r31, CoverAlarm@ha
/* 8013BEF4 00136DF4  90 6D 9F BC */	stw r3, WaitingForCoverOpen-_SDA_BASE_(r13)
/* 8013BEF8 00136DF8  38 7F 55 40 */	addi r3, r31, CoverAlarm@l
/* 8013BEFC 00136DFC  4B FB 12 19 */	bl OSCreateAlarm
/* 8013BF00 00136E00  4B FB 97 1D */	bl OSGetTick
/* 8013BF04 00136E04  3C A0 80 00 */	lis r5, 0x800000F8@ha
/* 8013BF08 00136E08  3C 80 10 62 */	lis r4, 0x10624DD3@ha
/* 8013BF0C 00136E0C  80 05 00 F8 */	lwz r0, 0x800000F8@l(r5)
/* 8013BF10 00136E10  3D 20 80 14 */	lis r9, CoverAlarmHandler@ha
/* 8013BF14 00136E14  7C 66 1B 78 */	mr r6, r3
/* 8013BF18 00136E18  38 84 4D D3 */	addi r4, r4, 0x10624DD3@l
/* 8013BF1C 00136E1C  54 00 F0 BE */	srwi r0, r0, 2
/* 8013BF20 00136E20  38 7F 55 40 */	addi r3, r31, 0x5540
/* 8013BF24 00136E24  7C 04 00 16 */	mulhwu r0, r4, r0
/* 8013BF28 00136E28  39 29 C9 C8 */	addi r9, r9, CoverAlarmHandler@l
/* 8013BF2C 00136E2C  38 A0 00 00 */	li r5, 0
/* 8013BF30 00136E30  38 E0 00 00 */	li r7, 0
/* 8013BF34 00136E34  54 00 D1 BE */	srwi r0, r0, 6
/* 8013BF38 00136E38  1D 00 00 64 */	mulli r8, r0, 0x64
/* 8013BF3C 00136E3C  4B FB 14 A9 */	bl OSSetPeriodicAlarm
lbl_8013BF40:
/* 8013BF40 00136E40  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8013BF44 00136E44  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8013BF48 00136E48  7C 08 03 A6 */	mtlr r0
/* 8013BF4C 00136E4C  38 21 00 10 */	addi r1, r1, 0x10
/* 8013BF50 00136E50  4E 80 00 20 */	blr 

.global cbForStateCheckID2
cbForStateCheckID2:
/* 8013BF54 00136E54  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8013BF58 00136E58  7C 08 02 A6 */	mflr r0
/* 8013BF5C 00136E5C  90 01 00 14 */	stw r0, 0x14(r1)
/* 8013BF60 00136E60  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8013BF64 00136E64  7C 7F 1B 78 */	mr r31, r3
/* 8013BF68 00136E68  4B FB 59 59 */	bl OSDisableInterrupts
/* 8013BF6C 00136E6C  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013BF70 00136E70  2C 00 00 00 */	cmpwi r0, 0
/* 8013BF74 00136E74  40 82 00 14 */	bne lbl_8013BF88
/* 8013BF78 00136E78  3C 80 80 48 */	lis r4, __ErrorInfo@ha
/* 8013BF7C 00136E7C  38 84 A2 20 */	addi r4, r4, __ErrorInfo@l
/* 8013BF80 00136E80  93 E4 00 78 */	stw r31, 0x78(r4)
/* 8013BF84 00136E84  48 00 00 20 */	b lbl_8013BFA4
lbl_8013BF88:
/* 8013BF88 00136E88  80 8D 9F 98 */	lwz r4, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013BF8C 00136E8C  3C A0 80 48 */	lis r5, __ErrorInfo@ha
/* 8013BF90 00136E90  38 A5 A2 20 */	addi r5, r5, __ErrorInfo@l
/* 8013BF94 00136E94  38 04 FF FF */	addi r0, r4, -1
/* 8013BF98 00136E98  1C 00 00 14 */	mulli r0, r0, 0x14
/* 8013BF9C 00136E9C  7C 85 02 14 */	add r4, r5, r0
/* 8013BFA0 00136EA0  93 E4 00 28 */	stw r31, 0x28(r4)
lbl_8013BFA4:
/* 8013BFA4 00136EA4  4B FB 59 45 */	bl OSRestoreInterrupts
/* 8013BFA8 00136EA8  28 1F 00 10 */	cmplwi r31, 0x10
/* 8013BFAC 00136EAC  40 82 00 1C */	bne lbl_8013BFC8
/* 8013BFB0 00136EB0  3C 60 01 23 */	lis r3, 0x01234568@ha
/* 8013BFB4 00136EB4  3C 80 80 14 */	lis r4, cbForStoreErrorCode2@ha
/* 8013BFB8 00136EB8  38 63 45 68 */	addi r3, r3, 0x01234568@l
/* 8013BFBC 00136EBC  38 84 A6 24 */	addi r4, r4, cbForStoreErrorCode2@l
/* 8013BFC0 00136EC0  48 00 28 D9 */	bl __DVDStoreErrorCode
/* 8013BFC4 00136EC4  48 00 01 10 */	b lbl_8013C0D4
lbl_8013BFC8:
/* 8013BFC8 00136EC8  28 1F 00 20 */	cmplwi r31, 0x20
/* 8013BFCC 00136ECC  40 82 00 1C */	bne lbl_8013BFE8
/* 8013BFD0 00136ED0  3C 60 01 23 */	lis r3, 0x01234569@ha
/* 8013BFD4 00136ED4  3C 80 80 14 */	lis r4, cbForStoreErrorCode2@ha
/* 8013BFD8 00136ED8  38 63 45 69 */	addi r3, r3, 0x01234569@l
/* 8013BFDC 00136EDC  38 84 A6 24 */	addi r4, r4, cbForStoreErrorCode2@l
/* 8013BFE0 00136EE0  48 00 28 B9 */	bl __DVDStoreErrorCode
/* 8013BFE4 00136EE4  48 00 00 F0 */	b lbl_8013C0D4
lbl_8013BFE8:
/* 8013BFE8 00136EE8  57 E0 07 FF */	clrlwi. r0, r31, 0x1f
/* 8013BFEC 00136EEC  41 82 00 CC */	beq lbl_8013C0B8
/* 8013BFF0 00136EF0  3C A0 80 14 */	lis r5, stateReadingFST@ha
/* 8013BFF4 00136EF4  38 00 00 00 */	li r0, 0
/* 8013BFF8 00136EF8  38 A5 A2 00 */	addi r5, r5, stateReadingFST@l
/* 8013BFFC 00136EFC  3C 60 80 47 */	lis r3, BB2@ha
/* 8013C000 00136F00  90 0D 9F B0 */	stw r0, NumInternalRetry-_SDA_BASE_(r13)
/* 8013C004 00136F04  38 63 54 C0 */	addi r3, r3, BB2@l
/* 8013C008 00136F08  80 8D A0 10 */	lwz r4, bootInfo-_SDA_BASE_(r13)
/* 8013C00C 00136F0C  90 AD A0 1C */	stw r5, LastState-_SDA_BASE_(r13)
/* 8013C010 00136F10  80 03 00 08 */	lwz r0, 8(r3)
/* 8013C014 00136F14  80 64 00 3C */	lwz r3, 0x3c(r4)
/* 8013C018 00136F18  7C 03 00 40 */	cmplw r3, r0
/* 8013C01C 00136F1C  40 80 00 1C */	bge lbl_8013C038
/* 8013C020 00136F20  3C A0 80 3B */	lis r5, strings_803B5E70@ha
/* 8013C024 00136F24  38 6D 86 04 */	addi r3, r13, lbl_804BD984-_SDA_BASE_
/* 8013C028 00136F28  38 A5 5E 70 */	addi r5, r5, strings_803B5E70@l
/* 8013C02C 00136F2C  38 80 04 0B */	li r4, 0x40b
/* 8013C030 00136F30  4C C6 31 82 */	crclr 6
/* 8013C034 00136F34  4B FB 2F 75 */	bl OSPanic
lbl_8013C038:
/* 8013C038 00136F38  38 60 00 00 */	li r3, 0
/* 8013C03C 00136F3C  48 00 43 AD */	bl DVDLowClearCoverInterrupt
/* 8013C040 00136F40  80 CD 9F D0 */	lwz r6, __DVDLayoutFormat-_SDA_BASE_(r13)
/* 8013C044 00136F44  3F E0 80 47 */	lis r31, BB2@ha
/* 8013C048 00136F48  3B FF 54 C0 */	addi r31, r31, BB2@l
/* 8013C04C 00136F4C  80 0D 9F D0 */	lwz r0, __DVDLayoutFormat-_SDA_BASE_(r13)
/* 8013C050 00136F50  80 9F 00 08 */	lwz r4, 8(r31)
/* 8013C054 00136F54  38 60 00 01 */	li r3, 1
/* 8013C058 00136F58  7C 00 00 F8 */	nor r0, r0, r0
/* 8013C05C 00136F5C  80 FF 00 04 */	lwz r7, 4(r31)
/* 8013C060 00136F60  54 00 07 BC */	rlwinm r0, r0, 0, 0x1e, 0x1e
/* 8013C064 00136F64  7C 85 00 30 */	slw r5, r4, r0
/* 8013C068 00136F68  7C E4 34 30 */	srw r4, r7, r6
/* 8013C06C 00136F6C  38 05 00 1F */	addi r0, r5, 0x1f
/* 8013C070 00136F70  54 05 00 34 */	rlwinm r5, r0, 0, 0, 0x1a
/* 8013C074 00136F74  4B FF DF F5 */	bl StampCommand
/* 8013C078 00136F78  80 0D 9F D0 */	lwz r0, __DVDLayoutFormat-_SDA_BASE_(r13)
/* 8013C07C 00136F7C  3C C0 80 14 */	lis r6, cbForStateReadingFST@ha
/* 8013C080 00136F80  80 7F 00 08 */	lwz r3, 8(r31)
/* 8013C084 00136F84  38 C6 A3 78 */	addi r6, r6, cbForStateReadingFST@l
/* 8013C088 00136F88  7C 00 00 F8 */	nor r0, r0, r0
/* 8013C08C 00136F8C  80 ED A0 10 */	lwz r7, bootInfo-_SDA_BASE_(r13)
/* 8013C090 00136F90  54 00 07 BC */	rlwinm r0, r0, 0, 0x1e, 0x1e
/* 8013C094 00136F94  80 BF 00 04 */	lwz r5, 4(r31)
/* 8013C098 00136F98  7C 63 00 30 */	slw r3, r3, r0
/* 8013C09C 00136F9C  80 0D 9F D0 */	lwz r0, __DVDLayoutFormat-_SDA_BASE_(r13)
/* 8013C0A0 00136FA0  38 83 00 1F */	addi r4, r3, 0x1f
/* 8013C0A4 00136FA4  80 67 00 38 */	lwz r3, 0x38(r7)
/* 8013C0A8 00136FA8  54 84 00 34 */	rlwinm r4, r4, 0, 0, 0x1a
/* 8013C0AC 00136FAC  7C A5 04 30 */	srw r5, r5, r0
/* 8013C0B0 00136FB0  48 00 3E 79 */	bl DVDLowRead
/* 8013C0B4 00136FB4  48 00 00 20 */	b lbl_8013C0D4
lbl_8013C0B8:
/* 8013C0B8 00136FB8  38 60 00 27 */	li r3, 0x27
/* 8013C0BC 00136FBC  38 80 00 00 */	li r4, 0
/* 8013C0C0 00136FC0  38 A0 00 00 */	li r5, 0
/* 8013C0C4 00136FC4  4B FF DF A5 */	bl StampCommand
/* 8013C0C8 00136FC8  3C 60 80 14 */	lis r3, cbForStateGettingError@ha
/* 8013C0CC 00136FCC  38 63 A8 18 */	addi r3, r3, cbForStateGettingError@l
/* 8013C0D0 00136FD0  48 00 38 55 */	bl DVDLowRequestError
lbl_8013C0D4:
/* 8013C0D4 00136FD4  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8013C0D8 00136FD8  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8013C0DC 00136FDC  7C 08 03 A6 */	mtlr r0
/* 8013C0E0 00136FE0  38 21 00 10 */	addi r1, r1, 0x10
/* 8013C0E4 00136FE4  4E 80 00 20 */	blr 

.global stateCoverClosed
stateCoverClosed:
/* 8013C0E8 00136FE8  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8013C0EC 00136FEC  7C 08 02 A6 */	mflr r0
/* 8013C0F0 00136FF0  38 60 00 01 */	li r3, 1
/* 8013C0F4 00136FF4  90 01 00 14 */	stw r0, 0x14(r1)
/* 8013C0F8 00136FF8  80 0D A0 0C */	lwz r0, CurrCommand-_SDA_BASE_(r13)
/* 8013C0FC 00136FFC  90 6D 9F F8 */	stw r3, MotorState-_SDA_BASE_(r13)
/* 8013C100 00137000  28 00 00 26 */	cmplwi r0, 0x26
/* 8013C104 00137004  41 81 00 7C */	bgt lbl_8013C180
/* 8013C108 00137008  3C 60 80 3B */	lis r3, lbl_803B5EA4@ha
/* 8013C10C 0013700C  54 00 10 3A */	slwi r0, r0, 2
/* 8013C110 00137010  38 63 5E A4 */	addi r3, r3, lbl_803B5EA4@l
/* 8013C114 00137014  7C 63 00 2E */	lwzx r3, r3, r0
/* 8013C118 00137018  7C 69 03 A6 */	mtctr r3
/* 8013C11C 0013701C  4E 80 04 20 */	bctr 
/* 8013C120 00137020  48 00 22 BD */	bl __DVDClearWaitingQueue
/* 8013C124 00137024  3C 60 80 47 */	lis r3, DummyCommandBlock@ha
/* 8013C128 00137028  80 8D A0 18 */	lwz r4, executing-_SDA_BASE_(r13)
/* 8013C12C 0013702C  38 63 54 E0 */	addi r3, r3, DummyCommandBlock@l
/* 8013C130 00137030  90 6D A0 18 */	stw r3, executing-_SDA_BASE_(r13)
/* 8013C134 00137034  81 84 00 28 */	lwz r12, 0x28(r4)
/* 8013C138 00137038  2C 0C 00 00 */	cmpwi r12, 0
/* 8013C13C 0013703C  41 82 00 10 */	beq lbl_8013C14C
/* 8013C140 00137040  38 60 FF FC */	li r3, -4
/* 8013C144 00137044  7D 89 03 A6 */	mtctr r12
/* 8013C148 00137048  4E 80 04 21 */	bctrl 
lbl_8013C14C:
/* 8013C14C 0013704C  48 00 08 A1 */	bl stateReady
/* 8013C150 00137050  48 00 00 4C */	b lbl_8013C19C
/* 8013C154 00137054  38 00 00 00 */	li r0, 0
/* 8013C158 00137058  90 0D 9F F8 */	stw r0, MotorState-_SDA_BASE_(r13)
/* 8013C15C 0013705C  80 6D A0 18 */	lwz r3, executing-_SDA_BASE_(r13)
/* 8013C160 00137060  38 00 00 01 */	li r0, 1
/* 8013C164 00137064  90 03 00 0C */	stw r0, 0xc(r3)
/* 8013C168 00137068  80 6D A0 18 */	lwz r3, executing-_SDA_BASE_(r13)
/* 8013C16C 0013706C  48 00 0B A9 */	bl stateBusy
/* 8013C170 00137070  48 00 00 2C */	b lbl_8013C19C
/* 8013C174 00137074  80 0D 9B 88 */	lwz r0, __OSInIPL-_SDA_BASE_(r13)
/* 8013C178 00137078  2C 00 00 00 */	cmpwi r0, 0
/* 8013C17C 0013707C  40 82 00 20 */	bne lbl_8013C19C
lbl_8013C180:
/* 8013C180 00137080  38 00 00 00 */	li r0, 0
/* 8013C184 00137084  38 60 00 01 */	li r3, 1
/* 8013C188 00137088  90 0D 9F F8 */	stw r0, MotorState-_SDA_BASE_(r13)
/* 8013C18C 0013708C  48 00 39 01 */	bl DVDLowSetSpinupFlag
/* 8013C190 00137090  3C 60 80 14 */	lis r3, cbForStateReset@ha
/* 8013C194 00137094  38 63 C3 54 */	addi r3, r3, cbForStateReset@l
/* 8013C198 00137098  48 00 39 01 */	bl DVDLowReset
lbl_8013C19C:
/* 8013C19C 0013709C  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8013C1A0 001370A0  7C 08 03 A6 */	mtlr r0
/* 8013C1A4 001370A4  38 21 00 10 */	addi r1, r1, 0x10
/* 8013C1A8 001370A8  4E 80 00 20 */	blr 

.global ResetAlarmHandler
ResetAlarmHandler:
/* 8013C1AC 001370AC  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8013C1B0 001370B0  7C 08 02 A6 */	mflr r0
/* 8013C1B4 001370B4  3C 60 80 00 */	lis r3, 0x800030E6@ha
/* 8013C1B8 001370B8  90 01 00 14 */	stw r0, 0x14(r1)
/* 8013C1BC 001370BC  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8013C1C0 001370C0  93 C1 00 08 */	stw r30, 8(r1)
/* 8013C1C4 001370C4  A0 03 30 E6 */	lhz r0, 0x800030E6@l(r3)
/* 8013C1C8 001370C8  28 00 80 03 */	cmplwi r0, 0x8003
/* 8013C1CC 001370CC  40 82 00 B0 */	bne lbl_8013C27C
/* 8013C1D0 001370D0  3C 80 80 14 */	lis r4, stateDownRotation@ha
/* 8013C1D4 001370D4  38 60 00 00 */	li r3, 0
/* 8013C1D8 001370D8  38 84 C4 38 */	addi r4, r4, stateDownRotation@l
/* 8013C1DC 001370DC  90 8D A0 1C */	stw r4, LastState-_SDA_BASE_(r13)
/* 8013C1E0 001370E0  48 00 42 09 */	bl DVDLowClearCoverInterrupt
/* 8013C1E4 001370E4  4B FB 56 DD */	bl OSDisableInterrupts
/* 8013C1E8 001370E8  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013C1EC 001370EC  7C 7F 1B 78 */	mr r31, r3
/* 8013C1F0 001370F0  28 00 00 05 */	cmplwi r0, 5
/* 8013C1F4 001370F4  41 80 00 0C */	blt lbl_8013C200
/* 8013C1F8 001370F8  38 00 00 00 */	li r0, 0
/* 8013C1FC 001370FC  90 0D 9F 98 */	stw r0, CommandInfoCounter-_SDA_BASE_(r13)
lbl_8013C200:
/* 8013C200 00137100  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013C204 00137104  3F C0 80 48 */	lis r30, __ErrorInfo@ha
/* 8013C208 00137108  80 6D 9F 98 */	lwz r3, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013C20C 0013710C  3B DE A2 20 */	addi r30, r30, __ErrorInfo@l
/* 8013C210 00137110  1C A0 00 14 */	mulli r5, r0, 0x14
/* 8013C214 00137114  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013C218 00137118  38 C0 00 25 */	li r6, 0x25
/* 8013C21C 0013711C  38 80 00 00 */	li r4, 0
/* 8013C220 00137120  1C 63 00 14 */	mulli r3, r3, 0x14
/* 8013C224 00137124  7C BE 2A 14 */	add r5, r30, r5
/* 8013C228 00137128  90 C5 00 1C */	stw r6, 0x1c(r5)
/* 8013C22C 0013712C  7C 7E 1A 14 */	add r3, r30, r3
/* 8013C230 00137130  1C 00 00 14 */	mulli r0, r0, 0x14
/* 8013C234 00137134  90 83 00 20 */	stw r4, 0x20(r3)
/* 8013C238 00137138  7C 7E 02 14 */	add r3, r30, r0
/* 8013C23C 0013713C  90 83 00 24 */	stw r4, 0x24(r3)
/* 8013C240 00137140  4B FB 93 DD */	bl OSGetTick
/* 8013C244 00137144  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013C248 00137148  80 8D 9F 98 */	lwz r4, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013C24C 0013714C  1C A0 00 14 */	mulli r5, r0, 0x14
/* 8013C250 00137150  38 04 00 01 */	addi r0, r4, 1
/* 8013C254 00137154  90 0D 9F 98 */	stw r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013C258 00137158  7C 9E 2A 14 */	add r4, r30, r5
/* 8013C25C 0013715C  90 64 00 2C */	stw r3, 0x2c(r4)
/* 8013C260 00137160  7F E3 FB 78 */	mr r3, r31
/* 8013C264 00137164  4B FB 56 85 */	bl OSRestoreInterrupts
/* 8013C268 00137168  3C 80 80 14 */	lis r4, cbForStateDownRotation@ha
/* 8013C26C 0013716C  3C 60 00 02 */	lis r3, 2
/* 8013C270 00137170  38 84 C5 00 */	addi r4, r4, cbForStateDownRotation@l
/* 8013C274 00137174  48 00 3B 35 */	bl DVDLowSetMaximumRotation
/* 8013C278 00137178  48 00 00 C4 */	b lbl_8013C33C
lbl_8013C27C:
/* 8013C27C 0013717C  3C 60 80 47 */	lis r3, CurrDiskID@ha
/* 8013C280 00137180  38 80 00 20 */	li r4, 0x20
/* 8013C284 00137184  38 63 55 80 */	addi r3, r3, CurrDiskID@l
/* 8013C288 00137188  4B FB 1E 7D */	bl DCInvalidateRange
/* 8013C28C 0013718C  3C 80 80 14 */	lis r4, stateCoverClosed_CMD@ha
/* 8013C290 00137190  38 60 00 00 */	li r3, 0
/* 8013C294 00137194  38 84 C6 98 */	addi r4, r4, stateCoverClosed_CMD@l
/* 8013C298 00137198  90 8D A0 1C */	stw r4, LastState-_SDA_BASE_(r13)
/* 8013C29C 0013719C  48 00 41 4D */	bl DVDLowClearCoverInterrupt
/* 8013C2A0 001371A0  4B FB 56 21 */	bl OSDisableInterrupts
/* 8013C2A4 001371A4  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013C2A8 001371A8  7C 7F 1B 78 */	mr r31, r3
/* 8013C2AC 001371AC  28 00 00 05 */	cmplwi r0, 5
/* 8013C2B0 001371B0  41 80 00 0C */	blt lbl_8013C2BC
/* 8013C2B4 001371B4  38 00 00 00 */	li r0, 0
/* 8013C2B8 001371B8  90 0D 9F 98 */	stw r0, CommandInfoCounter-_SDA_BASE_(r13)
lbl_8013C2BC:
/* 8013C2BC 001371BC  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013C2C0 001371C0  3F C0 80 48 */	lis r30, __ErrorInfo@ha
/* 8013C2C4 001371C4  80 6D 9F 98 */	lwz r3, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013C2C8 001371C8  3B DE A2 20 */	addi r30, r30, __ErrorInfo@l
/* 8013C2CC 001371CC  1C C0 00 14 */	mulli r6, r0, 0x14
/* 8013C2D0 001371D0  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013C2D4 001371D4  38 E0 00 05 */	li r7, 5
/* 8013C2D8 001371D8  38 A0 00 00 */	li r5, 0
/* 8013C2DC 001371DC  1C 63 00 14 */	mulli r3, r3, 0x14
/* 8013C2E0 001371E0  38 80 00 20 */	li r4, 0x20
/* 8013C2E4 001371E4  7C DE 32 14 */	add r6, r30, r6
/* 8013C2E8 001371E8  90 E6 00 1C */	stw r7, 0x1c(r6)
/* 8013C2EC 001371EC  7C 7E 1A 14 */	add r3, r30, r3
/* 8013C2F0 001371F0  1C 00 00 14 */	mulli r0, r0, 0x14
/* 8013C2F4 001371F4  90 A3 00 20 */	stw r5, 0x20(r3)
/* 8013C2F8 001371F8  7C 7E 02 14 */	add r3, r30, r0
/* 8013C2FC 001371FC  90 83 00 24 */	stw r4, 0x24(r3)
/* 8013C300 00137200  4B FB 93 1D */	bl OSGetTick
/* 8013C304 00137204  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013C308 00137208  80 8D 9F 98 */	lwz r4, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013C30C 0013720C  1C A0 00 14 */	mulli r5, r0, 0x14
/* 8013C310 00137210  38 04 00 01 */	addi r0, r4, 1
/* 8013C314 00137214  90 0D 9F 98 */	stw r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013C318 00137218  7C 9E 2A 14 */	add r4, r30, r5
/* 8013C31C 0013721C  90 64 00 2C */	stw r3, 0x2c(r4)
/* 8013C320 00137220  7F E3 FB 78 */	mr r3, r31
/* 8013C324 00137224  4B FB 55 C5 */	bl OSRestoreInterrupts
/* 8013C328 00137228  3C 60 80 47 */	lis r3, CurrDiskID@ha
/* 8013C32C 0013722C  3C 80 80 14 */	lis r4, cbForStateCoverClosed@ha
/* 8013C330 00137230  38 63 55 80 */	addi r3, r3, CurrDiskID@l
/* 8013C334 00137234  38 84 C7 68 */	addi r4, r4, cbForStateCoverClosed@l
/* 8013C338 00137238  48 00 2C 09 */	bl DVDLowReadDiskID
lbl_8013C33C:
/* 8013C33C 0013723C  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8013C340 00137240  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8013C344 00137244  83 C1 00 08 */	lwz r30, 8(r1)
/* 8013C348 00137248  7C 08 03 A6 */	mtlr r0
/* 8013C34C 0013724C  38 21 00 10 */	addi r1, r1, 0x10
/* 8013C350 00137250  4E 80 00 20 */	blr 

.global cbForStateReset
cbForStateReset:
/* 8013C354 00137254  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8013C358 00137258  7C 08 02 A6 */	mflr r0
/* 8013C35C 0013725C  28 03 00 10 */	cmplwi r3, 0x10
/* 8013C360 00137260  90 01 00 14 */	stw r0, 0x14(r1)
/* 8013C364 00137264  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8013C368 00137268  40 82 00 1C */	bne lbl_8013C384
/* 8013C36C 0013726C  3C 60 01 23 */	lis r3, 0x01234568@ha
/* 8013C370 00137270  3C 80 80 14 */	lis r4, cbForStoreErrorCode2@ha
/* 8013C374 00137274  38 63 45 68 */	addi r3, r3, 0x01234568@l
/* 8013C378 00137278  38 84 A6 24 */	addi r4, r4, cbForStoreErrorCode2@l
/* 8013C37C 0013727C  48 00 25 1D */	bl __DVDStoreErrorCode
/* 8013C380 00137280  48 00 00 A4 */	b lbl_8013C424
lbl_8013C384:
/* 8013C384 00137284  28 03 00 20 */	cmplwi r3, 0x20
/* 8013C388 00137288  40 82 00 1C */	bne lbl_8013C3A4
/* 8013C38C 0013728C  3C 60 01 23 */	lis r3, 0x01234569@ha
/* 8013C390 00137290  3C 80 80 14 */	lis r4, cbForStoreErrorCode2@ha
/* 8013C394 00137294  38 63 45 69 */	addi r3, r3, 0x01234569@l
/* 8013C398 00137298  38 84 A6 24 */	addi r4, r4, cbForStoreErrorCode2@l
/* 8013C39C 0013729C  48 00 24 FD */	bl __DVDStoreErrorCode
/* 8013C3A0 001372A0  48 00 00 84 */	b lbl_8013C424
lbl_8013C3A4:
/* 8013C3A4 001372A4  54 60 07 FF */	clrlwi. r0, r3, 0x1f
/* 8013C3A8 001372A8  41 82 00 60 */	beq lbl_8013C408
/* 8013C3AC 001372AC  4B FB 92 79 */	bl __OSGetSystemTime
/* 8013C3B0 001372B0  38 00 00 00 */	li r0, 0
/* 8013C3B4 001372B4  90 8D 9F F4 */	stw r4, (LastResetEnd+0x4)-_SDA_BASE_(r13)
/* 8013C3B8 001372B8  3F E0 80 48 */	lis r31, ResetAlarm@ha
/* 8013C3BC 001372BC  90 6D 9F F0 */	stw r3, LastResetEnd-_SDA_BASE_(r13)
/* 8013C3C0 001372C0  38 7F A0 00 */	addi r3, r31, ResetAlarm@l
/* 8013C3C4 001372C4  90 0D 9F FC */	stw r0, ResetRequired-_SDA_BASE_(r13)
/* 8013C3C8 001372C8  90 0D 9F AC */	stw r0, ResumeFromHere-_SDA_BASE_(r13)
/* 8013C3CC 001372CC  4B FB 0D 49 */	bl OSCreateAlarm
/* 8013C3D0 001372D0  3C 80 80 00 */	lis r4, 0x800000F8@ha
/* 8013C3D4 001372D4  3C E0 80 14 */	lis r7, ResetAlarmHandler@ha
/* 8013C3D8 001372D8  80 04 00 F8 */	lwz r0, 0x800000F8@l(r4)
/* 8013C3DC 001372DC  3C 60 10 62 */	lis r3, 0x10624DD3@ha
/* 8013C3E0 001372E0  38 83 4D D3 */	addi r4, r3, 0x10624DD3@l
/* 8013C3E4 001372E4  38 E7 C1 AC */	addi r7, r7, ResetAlarmHandler@l
/* 8013C3E8 001372E8  54 00 F0 BE */	srwi r0, r0, 2
/* 8013C3EC 001372EC  38 7F A0 00 */	addi r3, r31, -24576
/* 8013C3F0 001372F0  7C 04 00 16 */	mulhwu r0, r4, r0
/* 8013C3F4 001372F4  38 A0 00 00 */	li r5, 0
/* 8013C3F8 001372F8  54 00 D1 BE */	srwi r0, r0, 6
/* 8013C3FC 001372FC  1C C0 00 64 */	mulli r6, r0, 0x64
/* 8013C400 00137300  4B FB 0F 75 */	bl OSSetAlarm
/* 8013C404 00137304  48 00 00 20 */	b lbl_8013C424
lbl_8013C408:
/* 8013C408 00137308  38 60 00 27 */	li r3, 0x27
/* 8013C40C 0013730C  38 80 00 00 */	li r4, 0
/* 8013C410 00137310  38 A0 00 00 */	li r5, 0
/* 8013C414 00137314  4B FF DC 55 */	bl StampCommand
/* 8013C418 00137318  3C 60 80 14 */	lis r3, cbForStateGettingError@ha
/* 8013C41C 0013731C  38 63 A8 18 */	addi r3, r3, cbForStateGettingError@l
/* 8013C420 00137320  48 00 35 05 */	bl DVDLowRequestError
lbl_8013C424:
/* 8013C424 00137324  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8013C428 00137328  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8013C42C 0013732C  7C 08 03 A6 */	mtlr r0
/* 8013C430 00137330  38 21 00 10 */	addi r1, r1, 0x10
/* 8013C434 00137334  4E 80 00 20 */	blr 

.global stateDownRotation
stateDownRotation:
/* 8013C438 00137338  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8013C43C 0013733C  7C 08 02 A6 */	mflr r0
/* 8013C440 00137340  38 60 00 00 */	li r3, 0
/* 8013C444 00137344  90 01 00 14 */	stw r0, 0x14(r1)
/* 8013C448 00137348  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8013C44C 0013734C  93 C1 00 08 */	stw r30, 8(r1)
/* 8013C450 00137350  48 00 3F 99 */	bl DVDLowClearCoverInterrupt
/* 8013C454 00137354  4B FB 54 6D */	bl OSDisableInterrupts
/* 8013C458 00137358  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013C45C 0013735C  7C 7F 1B 78 */	mr r31, r3
/* 8013C460 00137360  28 00 00 05 */	cmplwi r0, 5
/* 8013C464 00137364  41 80 00 0C */	blt lbl_8013C470
/* 8013C468 00137368  38 00 00 00 */	li r0, 0
/* 8013C46C 0013736C  90 0D 9F 98 */	stw r0, CommandInfoCounter-_SDA_BASE_(r13)
lbl_8013C470:
/* 8013C470 00137370  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013C474 00137374  3F C0 80 48 */	lis r30, __ErrorInfo@ha
/* 8013C478 00137378  80 6D 9F 98 */	lwz r3, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013C47C 0013737C  3B DE A2 20 */	addi r30, r30, __ErrorInfo@l
/* 8013C480 00137380  1C A0 00 14 */	mulli r5, r0, 0x14
/* 8013C484 00137384  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013C488 00137388  38 C0 00 25 */	li r6, 0x25
/* 8013C48C 0013738C  38 80 00 00 */	li r4, 0
/* 8013C490 00137390  1C 63 00 14 */	mulli r3, r3, 0x14
/* 8013C494 00137394  7C BE 2A 14 */	add r5, r30, r5
/* 8013C498 00137398  90 C5 00 1C */	stw r6, 0x1c(r5)
/* 8013C49C 0013739C  7C 7E 1A 14 */	add r3, r30, r3
/* 8013C4A0 001373A0  1C 00 00 14 */	mulli r0, r0, 0x14
/* 8013C4A4 001373A4  90 83 00 20 */	stw r4, 0x20(r3)
/* 8013C4A8 001373A8  7C 7E 02 14 */	add r3, r30, r0
/* 8013C4AC 001373AC  90 83 00 24 */	stw r4, 0x24(r3)
/* 8013C4B0 001373B0  4B FB 91 6D */	bl OSGetTick
/* 8013C4B4 001373B4  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013C4B8 001373B8  80 8D 9F 98 */	lwz r4, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013C4BC 001373BC  1C A0 00 14 */	mulli r5, r0, 0x14
/* 8013C4C0 001373C0  38 04 00 01 */	addi r0, r4, 1
/* 8013C4C4 001373C4  90 0D 9F 98 */	stw r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013C4C8 001373C8  7C 9E 2A 14 */	add r4, r30, r5
/* 8013C4CC 001373CC  90 64 00 2C */	stw r3, 0x2c(r4)
/* 8013C4D0 001373D0  7F E3 FB 78 */	mr r3, r31
/* 8013C4D4 001373D4  4B FB 54 15 */	bl OSRestoreInterrupts
/* 8013C4D8 001373D8  3C 80 80 14 */	lis r4, cbForStateDownRotation@ha
/* 8013C4DC 001373DC  3C 60 00 02 */	lis r3, 2
/* 8013C4E0 001373E0  38 84 C5 00 */	addi r4, r4, cbForStateDownRotation@l
/* 8013C4E4 001373E4  48 00 38 C5 */	bl DVDLowSetMaximumRotation
/* 8013C4E8 001373E8  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8013C4EC 001373EC  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8013C4F0 001373F0  83 C1 00 08 */	lwz r30, 8(r1)
/* 8013C4F4 001373F4  7C 08 03 A6 */	mtlr r0
/* 8013C4F8 001373F8  38 21 00 10 */	addi r1, r1, 0x10
/* 8013C4FC 001373FC  4E 80 00 20 */	blr 

.global cbForStateDownRotation
cbForStateDownRotation:
/* 8013C500 00137400  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8013C504 00137404  7C 08 02 A6 */	mflr r0
/* 8013C508 00137408  90 01 00 14 */	stw r0, 0x14(r1)
/* 8013C50C 0013740C  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8013C510 00137410  93 C1 00 08 */	stw r30, 8(r1)
/* 8013C514 00137414  7C 7E 1B 78 */	mr r30, r3
/* 8013C518 00137418  4B FB 53 A9 */	bl OSDisableInterrupts
/* 8013C51C 0013741C  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013C520 00137420  2C 00 00 00 */	cmpwi r0, 0
/* 8013C524 00137424  40 82 00 14 */	bne lbl_8013C538
/* 8013C528 00137428  3C 80 80 48 */	lis r4, __ErrorInfo@ha
/* 8013C52C 0013742C  38 84 A2 20 */	addi r4, r4, __ErrorInfo@l
/* 8013C530 00137430  93 C4 00 78 */	stw r30, 0x78(r4)
/* 8013C534 00137434  48 00 00 20 */	b lbl_8013C554
lbl_8013C538:
/* 8013C538 00137438  80 8D 9F 98 */	lwz r4, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013C53C 0013743C  3C A0 80 48 */	lis r5, __ErrorInfo@ha
/* 8013C540 00137440  38 A5 A2 20 */	addi r5, r5, __ErrorInfo@l
/* 8013C544 00137444  38 04 FF FF */	addi r0, r4, -1
/* 8013C548 00137448  1C 00 00 14 */	mulli r0, r0, 0x14
/* 8013C54C 0013744C  7C 85 02 14 */	add r4, r5, r0
/* 8013C550 00137450  93 C4 00 28 */	stw r30, 0x28(r4)
lbl_8013C554:
/* 8013C554 00137454  4B FB 53 95 */	bl OSRestoreInterrupts
/* 8013C558 00137458  28 1E 00 10 */	cmplwi r30, 0x10
/* 8013C55C 0013745C  40 82 00 1C */	bne lbl_8013C578
/* 8013C560 00137460  3C 60 01 23 */	lis r3, 0x01234568@ha
/* 8013C564 00137464  3C 80 80 14 */	lis r4, cbForStoreErrorCode2@ha
/* 8013C568 00137468  38 63 45 68 */	addi r3, r3, 0x01234568@l
/* 8013C56C 0013746C  38 84 A6 24 */	addi r4, r4, cbForStoreErrorCode2@l
/* 8013C570 00137470  48 00 23 29 */	bl __DVDStoreErrorCode
/* 8013C574 00137474  48 00 01 0C */	b lbl_8013C680
lbl_8013C578:
/* 8013C578 00137478  28 1E 00 20 */	cmplwi r30, 0x20
/* 8013C57C 0013747C  40 82 00 1C */	bne lbl_8013C598
/* 8013C580 00137480  3C 60 01 23 */	lis r3, 0x01234569@ha
/* 8013C584 00137484  3C 80 80 14 */	lis r4, cbForStoreErrorCode2@ha
/* 8013C588 00137488  38 63 45 69 */	addi r3, r3, 0x01234569@l
/* 8013C58C 0013748C  38 84 A6 24 */	addi r4, r4, cbForStoreErrorCode2@l
/* 8013C590 00137490  48 00 23 09 */	bl __DVDStoreErrorCode
/* 8013C594 00137494  48 00 00 EC */	b lbl_8013C680
lbl_8013C598:
/* 8013C598 00137498  57 C0 07 FF */	clrlwi. r0, r30, 0x1f
/* 8013C59C 0013749C  41 82 00 C8 */	beq lbl_8013C664
/* 8013C5A0 001374A0  3C 60 80 47 */	lis r3, CurrDiskID@ha
/* 8013C5A4 001374A4  38 80 00 20 */	li r4, 0x20
/* 8013C5A8 001374A8  38 63 55 80 */	addi r3, r3, CurrDiskID@l
/* 8013C5AC 001374AC  4B FB 1B 59 */	bl DCInvalidateRange
/* 8013C5B0 001374B0  3C 80 80 14 */	lis r4, stateCoverClosed_CMD@ha
/* 8013C5B4 001374B4  38 60 00 00 */	li r3, 0
/* 8013C5B8 001374B8  38 84 C6 98 */	addi r4, r4, stateCoverClosed_CMD@l
/* 8013C5BC 001374BC  90 8D A0 1C */	stw r4, LastState-_SDA_BASE_(r13)
/* 8013C5C0 001374C0  48 00 3E 29 */	bl DVDLowClearCoverInterrupt
/* 8013C5C4 001374C4  4B FB 52 FD */	bl OSDisableInterrupts
/* 8013C5C8 001374C8  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013C5CC 001374CC  7C 7F 1B 78 */	mr r31, r3
/* 8013C5D0 001374D0  28 00 00 05 */	cmplwi r0, 5
/* 8013C5D4 001374D4  41 80 00 0C */	blt lbl_8013C5E0
/* 8013C5D8 001374D8  38 00 00 00 */	li r0, 0
/* 8013C5DC 001374DC  90 0D 9F 98 */	stw r0, CommandInfoCounter-_SDA_BASE_(r13)
lbl_8013C5E0:
/* 8013C5E0 001374E0  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013C5E4 001374E4  3F C0 80 48 */	lis r30, __ErrorInfo@ha
/* 8013C5E8 001374E8  80 6D 9F 98 */	lwz r3, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013C5EC 001374EC  3B DE A2 20 */	addi r30, r30, __ErrorInfo@l
/* 8013C5F0 001374F0  1C C0 00 14 */	mulli r6, r0, 0x14
/* 8013C5F4 001374F4  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013C5F8 001374F8  38 E0 00 05 */	li r7, 5
/* 8013C5FC 001374FC  38 A0 00 00 */	li r5, 0
/* 8013C600 00137500  1C 63 00 14 */	mulli r3, r3, 0x14
/* 8013C604 00137504  38 80 00 20 */	li r4, 0x20
/* 8013C608 00137508  7C DE 32 14 */	add r6, r30, r6
/* 8013C60C 0013750C  90 E6 00 1C */	stw r7, 0x1c(r6)
/* 8013C610 00137510  7C 7E 1A 14 */	add r3, r30, r3
/* 8013C614 00137514  1C 00 00 14 */	mulli r0, r0, 0x14
/* 8013C618 00137518  90 A3 00 20 */	stw r5, 0x20(r3)
/* 8013C61C 0013751C  7C 7E 02 14 */	add r3, r30, r0
/* 8013C620 00137520  90 83 00 24 */	stw r4, 0x24(r3)
/* 8013C624 00137524  4B FB 8F F9 */	bl OSGetTick
/* 8013C628 00137528  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013C62C 0013752C  80 8D 9F 98 */	lwz r4, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013C630 00137530  1C A0 00 14 */	mulli r5, r0, 0x14
/* 8013C634 00137534  38 04 00 01 */	addi r0, r4, 1
/* 8013C638 00137538  90 0D 9F 98 */	stw r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013C63C 0013753C  7C 9E 2A 14 */	add r4, r30, r5
/* 8013C640 00137540  90 64 00 2C */	stw r3, 0x2c(r4)
/* 8013C644 00137544  7F E3 FB 78 */	mr r3, r31
/* 8013C648 00137548  4B FB 52 A1 */	bl OSRestoreInterrupts
/* 8013C64C 0013754C  3C 60 80 47 */	lis r3, CurrDiskID@ha
/* 8013C650 00137550  3C 80 80 14 */	lis r4, cbForStateCoverClosed@ha
/* 8013C654 00137554  38 63 55 80 */	addi r3, r3, CurrDiskID@l
/* 8013C658 00137558  38 84 C7 68 */	addi r4, r4, cbForStateCoverClosed@l
/* 8013C65C 0013755C  48 00 28 E5 */	bl DVDLowReadDiskID
/* 8013C660 00137560  48 00 00 20 */	b lbl_8013C680
lbl_8013C664:
/* 8013C664 00137564  38 60 00 27 */	li r3, 0x27
/* 8013C668 00137568  38 80 00 00 */	li r4, 0
/* 8013C66C 0013756C  38 A0 00 00 */	li r5, 0
/* 8013C670 00137570  4B FF D9 F9 */	bl StampCommand
/* 8013C674 00137574  3C 60 80 14 */	lis r3, cbForStateGettingError@ha
/* 8013C678 00137578  38 63 A8 18 */	addi r3, r3, cbForStateGettingError@l
/* 8013C67C 0013757C  48 00 32 A9 */	bl DVDLowRequestError
lbl_8013C680:
/* 8013C680 00137580  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8013C684 00137584  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8013C688 00137588  83 C1 00 08 */	lwz r30, 8(r1)
/* 8013C68C 0013758C  7C 08 03 A6 */	mtlr r0
/* 8013C690 00137590  38 21 00 10 */	addi r1, r1, 0x10
/* 8013C694 00137594  4E 80 00 20 */	blr 

.global stateCoverClosed_CMD
stateCoverClosed_CMD:
/* 8013C698 00137598  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8013C69C 0013759C  7C 08 02 A6 */	mflr r0
/* 8013C6A0 001375A0  38 60 00 00 */	li r3, 0
/* 8013C6A4 001375A4  90 01 00 14 */	stw r0, 0x14(r1)
/* 8013C6A8 001375A8  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8013C6AC 001375AC  93 C1 00 08 */	stw r30, 8(r1)
/* 8013C6B0 001375B0  48 00 3D 39 */	bl DVDLowClearCoverInterrupt
/* 8013C6B4 001375B4  4B FB 52 0D */	bl OSDisableInterrupts
/* 8013C6B8 001375B8  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013C6BC 001375BC  7C 7F 1B 78 */	mr r31, r3
/* 8013C6C0 001375C0  28 00 00 05 */	cmplwi r0, 5
/* 8013C6C4 001375C4  41 80 00 0C */	blt lbl_8013C6D0
/* 8013C6C8 001375C8  38 00 00 00 */	li r0, 0
/* 8013C6CC 001375CC  90 0D 9F 98 */	stw r0, CommandInfoCounter-_SDA_BASE_(r13)
lbl_8013C6D0:
/* 8013C6D0 001375D0  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013C6D4 001375D4  3F C0 80 48 */	lis r30, __ErrorInfo@ha
/* 8013C6D8 001375D8  80 6D 9F 98 */	lwz r3, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013C6DC 001375DC  3B DE A2 20 */	addi r30, r30, __ErrorInfo@l
/* 8013C6E0 001375E0  1C C0 00 14 */	mulli r6, r0, 0x14
/* 8013C6E4 001375E4  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013C6E8 001375E8  38 E0 00 05 */	li r7, 5
/* 8013C6EC 001375EC  38 A0 00 00 */	li r5, 0
/* 8013C6F0 001375F0  1C 63 00 14 */	mulli r3, r3, 0x14
/* 8013C6F4 001375F4  38 80 00 20 */	li r4, 0x20
/* 8013C6F8 001375F8  7C DE 32 14 */	add r6, r30, r6
/* 8013C6FC 001375FC  90 E6 00 1C */	stw r7, 0x1c(r6)
/* 8013C700 00137600  7C 7E 1A 14 */	add r3, r30, r3
/* 8013C704 00137604  1C 00 00 14 */	mulli r0, r0, 0x14
/* 8013C708 00137608  90 A3 00 20 */	stw r5, 0x20(r3)
/* 8013C70C 0013760C  7C 7E 02 14 */	add r3, r30, r0
/* 8013C710 00137610  90 83 00 24 */	stw r4, 0x24(r3)
/* 8013C714 00137614  4B FB 8F 09 */	bl OSGetTick
/* 8013C718 00137618  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013C71C 0013761C  80 8D 9F 98 */	lwz r4, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013C720 00137620  1C A0 00 14 */	mulli r5, r0, 0x14
/* 8013C724 00137624  38 04 00 01 */	addi r0, r4, 1
/* 8013C728 00137628  90 0D 9F 98 */	stw r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013C72C 0013762C  7C 9E 2A 14 */	add r4, r30, r5
/* 8013C730 00137630  90 64 00 2C */	stw r3, 0x2c(r4)
/* 8013C734 00137634  7F E3 FB 78 */	mr r3, r31
/* 8013C738 00137638  4B FB 51 B1 */	bl OSRestoreInterrupts
/* 8013C73C 0013763C  3C 60 80 47 */	lis r3, CurrDiskID@ha
/* 8013C740 00137640  3C 80 80 14 */	lis r4, cbForStateCoverClosed@ha
/* 8013C744 00137644  38 63 55 80 */	addi r3, r3, CurrDiskID@l
/* 8013C748 00137648  38 84 C7 68 */	addi r4, r4, cbForStateCoverClosed@l
/* 8013C74C 0013764C  48 00 27 F5 */	bl DVDLowReadDiskID
/* 8013C750 00137650  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8013C754 00137654  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8013C758 00137658  83 C1 00 08 */	lwz r30, 8(r1)
/* 8013C75C 0013765C  7C 08 03 A6 */	mtlr r0
/* 8013C760 00137660  38 21 00 10 */	addi r1, r1, 0x10
/* 8013C764 00137664  4E 80 00 20 */	blr 

.global cbForStateCoverClosed
cbForStateCoverClosed:
/* 8013C768 00137668  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8013C76C 0013766C  7C 08 02 A6 */	mflr r0
/* 8013C770 00137670  90 01 00 14 */	stw r0, 0x14(r1)
/* 8013C774 00137674  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8013C778 00137678  7C 7F 1B 78 */	mr r31, r3
/* 8013C77C 0013767C  4B FB 51 45 */	bl OSDisableInterrupts
/* 8013C780 00137680  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013C784 00137684  2C 00 00 00 */	cmpwi r0, 0
/* 8013C788 00137688  40 82 00 14 */	bne lbl_8013C79C
/* 8013C78C 0013768C  3C 80 80 48 */	lis r4, __ErrorInfo@ha
/* 8013C790 00137690  38 84 A2 20 */	addi r4, r4, __ErrorInfo@l
/* 8013C794 00137694  93 E4 00 78 */	stw r31, 0x78(r4)
/* 8013C798 00137698  48 00 00 1C */	b lbl_8013C7B4
lbl_8013C79C:
/* 8013C79C 0013769C  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013C7A0 001376A0  3C 80 80 48 */	lis r4, __ErrorInfo@ha
/* 8013C7A4 001376A4  38 84 A2 20 */	addi r4, r4, __ErrorInfo@l
/* 8013C7A8 001376A8  1C 00 00 14 */	mulli r0, r0, 0x14
/* 8013C7AC 001376AC  7C 84 02 14 */	add r4, r4, r0
/* 8013C7B0 001376B0  93 E4 00 14 */	stw r31, 0x14(r4)
lbl_8013C7B4:
/* 8013C7B4 001376B4  4B FB 51 35 */	bl OSRestoreInterrupts
/* 8013C7B8 001376B8  28 1F 00 10 */	cmplwi r31, 0x10
/* 8013C7BC 001376BC  40 82 00 1C */	bne lbl_8013C7D8
/* 8013C7C0 001376C0  3C 60 01 23 */	lis r3, 0x01234568@ha
/* 8013C7C4 001376C4  3C 80 80 14 */	lis r4, cbForStoreErrorCode2@ha
/* 8013C7C8 001376C8  38 63 45 68 */	addi r3, r3, 0x01234568@l
/* 8013C7CC 001376CC  38 84 A6 24 */	addi r4, r4, cbForStoreErrorCode2@l
/* 8013C7D0 001376D0  48 00 20 C9 */	bl __DVDStoreErrorCode
/* 8013C7D4 001376D4  48 00 00 58 */	b lbl_8013C82C
lbl_8013C7D8:
/* 8013C7D8 001376D8  28 1F 00 20 */	cmplwi r31, 0x20
/* 8013C7DC 001376DC  40 82 00 1C */	bne lbl_8013C7F8
/* 8013C7E0 001376E0  3C 60 01 23 */	lis r3, 0x01234569@ha
/* 8013C7E4 001376E4  3C 80 80 14 */	lis r4, cbForStoreErrorCode2@ha
/* 8013C7E8 001376E8  38 63 45 69 */	addi r3, r3, 0x01234569@l
/* 8013C7EC 001376EC  38 84 A6 24 */	addi r4, r4, cbForStoreErrorCode2@l
/* 8013C7F0 001376F0  48 00 20 A9 */	bl __DVDStoreErrorCode
/* 8013C7F4 001376F4  48 00 00 38 */	b lbl_8013C82C
lbl_8013C7F8:
/* 8013C7F8 001376F8  57 E0 07 FF */	clrlwi. r0, r31, 0x1f
/* 8013C7FC 001376FC  41 82 00 14 */	beq lbl_8013C810
/* 8013C800 00137700  38 00 00 00 */	li r0, 0
/* 8013C804 00137704  90 0D 9F B0 */	stw r0, NumInternalRetry-_SDA_BASE_(r13)
/* 8013C808 00137708  4B FF E9 F1 */	bl stateCheckID
/* 8013C80C 0013770C  48 00 00 20 */	b lbl_8013C82C
lbl_8013C810:
/* 8013C810 00137710  38 60 00 27 */	li r3, 0x27
/* 8013C814 00137714  38 80 00 00 */	li r4, 0
/* 8013C818 00137718  38 A0 00 00 */	li r5, 0
/* 8013C81C 0013771C  4B FF D8 4D */	bl StampCommand
/* 8013C820 00137720  3C 60 80 14 */	lis r3, cbForStateGettingError@ha
/* 8013C824 00137724  38 63 A8 18 */	addi r3, r3, cbForStateGettingError@l
/* 8013C828 00137728  48 00 30 FD */	bl DVDLowRequestError
lbl_8013C82C:
/* 8013C82C 0013772C  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8013C830 00137730  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8013C834 00137734  7C 08 03 A6 */	mtlr r0
/* 8013C838 00137738  38 21 00 10 */	addi r1, r1, 0x10
/* 8013C83C 0013773C  4E 80 00 20 */	blr 

.global cbForPrepareCoverRegister
cbForPrepareCoverRegister:
/* 8013C840 00137740  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8013C844 00137744  7C 08 02 A6 */	mflr r0
/* 8013C848 00137748  90 01 00 14 */	stw r0, 0x14(r1)
/* 8013C84C 0013774C  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8013C850 00137750  3B E0 00 00 */	li r31, 0
/* 8013C854 00137754  93 ED 9F CC */	stw r31, PreparingCover-_SDA_BASE_(r13)
/* 8013C858 00137758  80 0D 9F C0 */	lwz r0, WaitingForCoverClose-_SDA_BASE_(r13)
/* 8013C85C 0013775C  2C 00 00 00 */	cmpwi r0, 0
/* 8013C860 00137760  41 82 00 88 */	beq lbl_8013C8E8
/* 8013C864 00137764  48 00 39 F1 */	bl DVDLowGetCoverRegister
/* 8013C868 00137768  54 60 07 FF */	clrlwi. r0, r3, 0x1f
/* 8013C86C 0013776C  40 82 01 48 */	bne lbl_8013C9B4
/* 8013C870 00137770  3C 60 80 47 */	lis r3, CoverAlarm@ha
/* 8013C874 00137774  38 63 55 40 */	addi r3, r3, CoverAlarm@l
/* 8013C878 00137778  4B FB 0B F1 */	bl OSCancelAlarm
/* 8013C87C 0013777C  93 ED 9F C0 */	stw r31, WaitingForCoverClose-_SDA_BASE_(r13)
/* 8013C880 00137780  93 ED 9F C0 */	stw r31, WaitingForCoverClose-_SDA_BASE_(r13)
/* 8013C884 00137784  80 0D A0 0C */	lwz r0, CurrCommand-_SDA_BASE_(r13)
/* 8013C888 00137788  28 00 00 03 */	cmplwi r0, 3
/* 8013C88C 0013778C  40 82 00 0C */	bne lbl_8013C898
/* 8013C890 00137790  38 00 00 01 */	li r0, 1
/* 8013C894 00137794  90 0D 9F C8 */	stw r0, ChangedDisc-_SDA_BASE_(r13)
lbl_8013C898:
/* 8013C898 00137798  80 0D 9F F8 */	lwz r0, MotorState-_SDA_BASE_(r13)
/* 8013C89C 0013779C  28 00 00 02 */	cmplwi r0, 2
/* 8013C8A0 001377A0  40 82 00 1C */	bne lbl_8013C8BC
/* 8013C8A4 001377A4  80 6D A0 18 */	lwz r3, executing-_SDA_BASE_(r13)
/* 8013C8A8 001377A8  2C 03 00 00 */	cmpwi r3, 0
/* 8013C8AC 001377AC  41 82 01 08 */	beq lbl_8013C9B4
/* 8013C8B0 001377B0  38 00 00 0C */	li r0, 0xc
/* 8013C8B4 001377B4  90 03 00 0C */	stw r0, 0xc(r3)
/* 8013C8B8 001377B8  48 00 00 FC */	b lbl_8013C9B4
lbl_8013C8BC:
/* 8013C8BC 001377BC  48 00 3B 25 */	bl DVDLowMaskCoverInterrupt
/* 8013C8C0 001377C0  80 6D A0 18 */	lwz r3, executing-_SDA_BASE_(r13)
/* 8013C8C4 001377C4  2C 03 00 00 */	cmpwi r3, 0
/* 8013C8C8 001377C8  41 82 00 14 */	beq lbl_8013C8DC
/* 8013C8CC 001377CC  38 00 00 03 */	li r0, 3
/* 8013C8D0 001377D0  90 03 00 0C */	stw r0, 0xc(r3)
/* 8013C8D4 001377D4  4B FF F8 15 */	bl stateCoverClosed
/* 8013C8D8 001377D8  48 00 00 DC */	b lbl_8013C9B4
lbl_8013C8DC:
/* 8013C8DC 001377DC  38 00 00 07 */	li r0, 7
/* 8013C8E0 001377E0  90 0D 9F AC */	stw r0, ResumeFromHere-_SDA_BASE_(r13)
/* 8013C8E4 001377E4  48 00 00 D0 */	b lbl_8013C9B4
lbl_8013C8E8:
/* 8013C8E8 001377E8  48 00 39 6D */	bl DVDLowGetCoverRegister
/* 8013C8EC 001377EC  54 60 07 FF */	clrlwi. r0, r3, 0x1f
/* 8013C8F0 001377F0  41 82 00 3C */	beq lbl_8013C92C
/* 8013C8F4 001377F4  80 0D 9F F8 */	lwz r0, MotorState-_SDA_BASE_(r13)
/* 8013C8F8 001377F8  38 60 00 01 */	li r3, 1
/* 8013C8FC 001377FC  93 ED 9F BC */	stw r31, WaitingForCoverOpen-_SDA_BASE_(r13)
/* 8013C900 00137800  28 00 00 02 */	cmplwi r0, 2
/* 8013C904 00137804  90 6D 9F C0 */	stw r3, WaitingForCoverClose-_SDA_BASE_(r13)
/* 8013C908 00137808  40 82 00 14 */	bne lbl_8013C91C
/* 8013C90C 0013780C  80 6D A0 18 */	lwz r3, executing-_SDA_BASE_(r13)
/* 8013C910 00137810  38 00 00 0C */	li r0, 0xc
/* 8013C914 00137814  90 03 00 0C */	stw r0, 0xc(r3)
/* 8013C918 00137818  48 00 00 9C */	b lbl_8013C9B4
lbl_8013C91C:
/* 8013C91C 0013781C  80 6D A0 18 */	lwz r3, executing-_SDA_BASE_(r13)
/* 8013C920 00137820  38 00 00 05 */	li r0, 5
/* 8013C924 00137824  90 03 00 0C */	stw r0, 0xc(r3)
/* 8013C928 00137828  48 00 00 8C */	b lbl_8013C9B4
lbl_8013C92C:
/* 8013C92C 0013782C  48 00 39 29 */	bl DVDLowGetCoverRegister
/* 8013C930 00137830  54 60 07 7B */	rlwinm. r0, r3, 0, 0x1d, 0x1d
/* 8013C934 00137834  41 82 00 80 */	beq lbl_8013C9B4
/* 8013C938 00137838  3C 60 80 47 */	lis r3, CoverAlarm@ha
/* 8013C93C 0013783C  38 63 55 40 */	addi r3, r3, CoverAlarm@l
/* 8013C940 00137840  4B FB 0B 29 */	bl OSCancelAlarm
/* 8013C944 00137844  93 ED 9F BC */	stw r31, WaitingForCoverOpen-_SDA_BASE_(r13)
/* 8013C948 00137848  38 60 00 00 */	li r3, 0
/* 8013C94C 0013784C  48 00 3A 9D */	bl DVDLowClearCoverInterrupt
/* 8013C950 00137850  93 ED 9F C0 */	stw r31, WaitingForCoverClose-_SDA_BASE_(r13)
/* 8013C954 00137854  80 0D A0 0C */	lwz r0, CurrCommand-_SDA_BASE_(r13)
/* 8013C958 00137858  28 00 00 03 */	cmplwi r0, 3
/* 8013C95C 0013785C  40 82 00 0C */	bne lbl_8013C968
/* 8013C960 00137860  38 00 00 01 */	li r0, 1
/* 8013C964 00137864  90 0D 9F C8 */	stw r0, ChangedDisc-_SDA_BASE_(r13)
lbl_8013C968:
/* 8013C968 00137868  80 0D 9F F8 */	lwz r0, MotorState-_SDA_BASE_(r13)
/* 8013C96C 0013786C  28 00 00 02 */	cmplwi r0, 2
/* 8013C970 00137870  40 82 00 1C */	bne lbl_8013C98C
/* 8013C974 00137874  80 6D A0 18 */	lwz r3, executing-_SDA_BASE_(r13)
/* 8013C978 00137878  2C 03 00 00 */	cmpwi r3, 0
/* 8013C97C 0013787C  41 82 00 38 */	beq lbl_8013C9B4
/* 8013C980 00137880  38 00 00 0C */	li r0, 0xc
/* 8013C984 00137884  90 03 00 0C */	stw r0, 0xc(r3)
/* 8013C988 00137888  48 00 00 2C */	b lbl_8013C9B4
lbl_8013C98C:
/* 8013C98C 0013788C  48 00 3A 55 */	bl DVDLowMaskCoverInterrupt
/* 8013C990 00137890  80 6D A0 18 */	lwz r3, executing-_SDA_BASE_(r13)
/* 8013C994 00137894  2C 03 00 00 */	cmpwi r3, 0
/* 8013C998 00137898  41 82 00 14 */	beq lbl_8013C9AC
/* 8013C99C 0013789C  38 00 00 03 */	li r0, 3
/* 8013C9A0 001378A0  90 03 00 0C */	stw r0, 0xc(r3)
/* 8013C9A4 001378A4  4B FF F7 45 */	bl stateCoverClosed
/* 8013C9A8 001378A8  48 00 00 0C */	b lbl_8013C9B4
lbl_8013C9AC:
/* 8013C9AC 001378AC  38 00 00 07 */	li r0, 7
/* 8013C9B0 001378B0  90 0D 9F AC */	stw r0, ResumeFromHere-_SDA_BASE_(r13)
lbl_8013C9B4:
/* 8013C9B4 001378B4  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8013C9B8 001378B8  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8013C9BC 001378BC  7C 08 03 A6 */	mtlr r0
/* 8013C9C0 001378C0  38 21 00 10 */	addi r1, r1, 0x10
/* 8013C9C4 001378C4  4E 80 00 20 */	blr 

.global CoverAlarmHandler
CoverAlarmHandler:
/* 8013C9C8 001378C8  80 0D 9F CC */	lwz r0, PreparingCover-_SDA_BASE_(r13)
/* 8013C9CC 001378CC  2C 00 00 00 */	cmpwi r0, 0
/* 8013C9D0 001378D0  4C 82 00 20 */	bnelr 
/* 8013C9D4 001378D4  38 00 00 01 */	li r0, 1
/* 8013C9D8 001378D8  3C 60 80 14 */	lis r3, cbForPrepareCoverRegister@ha
/* 8013C9DC 001378DC  90 0D 9F CC */	stw r0, PreparingCover-_SDA_BASE_(r13)
/* 8013C9E0 001378E0  38 63 C8 40 */	addi r3, r3, cbForPrepareCoverRegister@l
/* 8013C9E4 001378E4  48 00 38 80 */	b DVDLowPrepareCoverRegister
/* 8013C9E8 001378E8  4E 80 00 20 */	blr 

.global stateReady
stateReady:
/* 8013C9EC 001378EC  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8013C9F0 001378F0  7C 08 02 A6 */	mflr r0
/* 8013C9F4 001378F4  90 01 00 14 */	stw r0, 0x14(r1)
/* 8013C9F8 001378F8  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8013C9FC 001378FC  48 00 1B 21 */	bl __DVDCheckWaitingQueue
/* 8013CA00 00137900  2C 03 00 00 */	cmpwi r3, 0
/* 8013CA04 00137904  40 82 00 10 */	bne lbl_8013CA14
/* 8013CA08 00137908  38 00 00 00 */	li r0, 0
/* 8013CA0C 0013790C  90 0D A0 18 */	stw r0, executing-_SDA_BASE_(r13)
/* 8013CA10 00137910  48 00 02 F0 */	b lbl_8013CD00
lbl_8013CA14:
/* 8013CA14 00137914  80 0D 9F 9C */	lwz r0, PauseFlag-_SDA_BASE_(r13)
/* 8013CA18 00137918  2C 00 00 00 */	cmpwi r0, 0
/* 8013CA1C 0013791C  41 82 00 18 */	beq lbl_8013CA34
/* 8013CA20 00137920  38 60 00 01 */	li r3, 1
/* 8013CA24 00137924  38 00 00 00 */	li r0, 0
/* 8013CA28 00137928  90 6D 9F A0 */	stw r3, PausingFlag-_SDA_BASE_(r13)
/* 8013CA2C 0013792C  90 0D A0 18 */	stw r0, executing-_SDA_BASE_(r13)
/* 8013CA30 00137930  48 00 02 D0 */	b lbl_8013CD00
lbl_8013CA34:
/* 8013CA34 00137934  48 00 1A 49 */	bl __DVDPopWaitingQueue
/* 8013CA38 00137938  80 0D 9F A4 */	lwz r0, FatalErrorFlag-_SDA_BASE_(r13)
/* 8013CA3C 0013793C  90 6D A0 18 */	stw r3, executing-_SDA_BASE_(r13)
/* 8013CA40 00137940  2C 00 00 00 */	cmpwi r0, 0
/* 8013CA44 00137944  41 82 00 3C */	beq lbl_8013CA80
/* 8013CA48 00137948  38 00 FF FF */	li r0, -1
/* 8013CA4C 0013794C  3C A0 80 47 */	lis r5, DummyCommandBlock@ha
/* 8013CA50 00137950  90 03 00 0C */	stw r0, 0xc(r3)
/* 8013CA54 00137954  38 A5 54 E0 */	addi r5, r5, DummyCommandBlock@l
/* 8013CA58 00137958  80 8D A0 18 */	lwz r4, executing-_SDA_BASE_(r13)
/* 8013CA5C 0013795C  90 AD A0 18 */	stw r5, executing-_SDA_BASE_(r13)
/* 8013CA60 00137960  81 84 00 28 */	lwz r12, 0x28(r4)
/* 8013CA64 00137964  2C 0C 00 00 */	cmpwi r12, 0
/* 8013CA68 00137968  41 82 00 10 */	beq lbl_8013CA78
/* 8013CA6C 0013796C  38 60 FF FF */	li r3, -1
/* 8013CA70 00137970  7D 89 03 A6 */	mtctr r12
/* 8013CA74 00137974  4E 80 04 21 */	bctrl 
lbl_8013CA78:
/* 8013CA78 00137978  4B FF FF 75 */	bl stateReady
/* 8013CA7C 0013797C  48 00 02 84 */	b lbl_8013CD00
lbl_8013CA80:
/* 8013CA80 00137980  80 03 00 08 */	lwz r0, 8(r3)
/* 8013CA84 00137984  90 0D A0 0C */	stw r0, CurrCommand-_SDA_BASE_(r13)
/* 8013CA88 00137988  80 0D A0 0C */	lwz r0, CurrCommand-_SDA_BASE_(r13)
/* 8013CA8C 0013798C  28 00 00 20 */	cmplwi r0, 0x20
/* 8013CA90 00137990  41 82 00 1C */	beq lbl_8013CAAC
/* 8013CA94 00137994  80 0D A0 0C */	lwz r0, CurrCommand-_SDA_BASE_(r13)
/* 8013CA98 00137998  28 00 00 0E */	cmplwi r0, 0xe
/* 8013CA9C 0013799C  41 82 00 10 */	beq lbl_8013CAAC
/* 8013CAA0 001379A0  80 0D A0 0C */	lwz r0, CurrCommand-_SDA_BASE_(r13)
/* 8013CAA4 001379A4  28 00 00 23 */	cmplwi r0, 0x23
/* 8013CAA8 001379A8  40 82 00 0C */	bne lbl_8013CAB4
lbl_8013CAAC:
/* 8013CAAC 001379AC  38 00 00 00 */	li r0, 0
/* 8013CAB0 001379B0  90 0D 9F AC */	stw r0, ResumeFromHere-_SDA_BASE_(r13)
lbl_8013CAB4:
/* 8013CAB4 001379B4  80 0D 9F AC */	lwz r0, ResumeFromHere-_SDA_BASE_(r13)
/* 8013CAB8 001379B8  2C 00 00 00 */	cmpwi r0, 0
/* 8013CABC 001379BC  41 82 01 E0 */	beq lbl_8013CC9C
/* 8013CAC0 001379C0  80 0D 9F AC */	lwz r0, ResumeFromHere-_SDA_BASE_(r13)
/* 8013CAC4 001379C4  2C 00 00 04 */	cmpwi r0, 4
/* 8013CAC8 001379C8  41 82 01 2C */	beq lbl_8013CBF4
/* 8013CACC 001379CC  40 80 00 1C */	bge lbl_8013CAE8
/* 8013CAD0 001379D0  2C 00 00 02 */	cmpwi r0, 2
/* 8013CAD4 001379D4  41 82 00 28 */	beq lbl_8013CAFC
/* 8013CAD8 001379D8  40 80 00 A0 */	bge lbl_8013CB78
/* 8013CADC 001379DC  2C 00 00 01 */	cmpwi r0, 1
/* 8013CAE0 001379E0  40 80 01 90 */	bge lbl_8013CC70
/* 8013CAE4 001379E4  48 00 01 AC */	b lbl_8013CC90
lbl_8013CAE8:
/* 8013CAE8 001379E8  2C 00 00 08 */	cmpwi r0, 8
/* 8013CAEC 001379EC  40 80 01 A4 */	bge lbl_8013CC90
/* 8013CAF0 001379F0  2C 00 00 06 */	cmpwi r0, 6
/* 8013CAF4 001379F4  40 80 01 7C */	bge lbl_8013CC70
/* 8013CAF8 001379F8  48 00 01 88 */	b lbl_8013CC80
lbl_8013CAFC:
/* 8013CAFC 001379FC  38 00 00 0B */	li r0, 0xb
/* 8013CB00 00137A00  38 80 00 01 */	li r4, 1
/* 8013CB04 00137A04  90 03 00 0C */	stw r0, 0xc(r3)
/* 8013CB08 00137A08  80 0D 9F BC */	lwz r0, WaitingForCoverOpen-_SDA_BASE_(r13)
/* 8013CB0C 00137A0C  90 8D 9F F8 */	stw r4, MotorState-_SDA_BASE_(r13)
/* 8013CB10 00137A10  2C 00 00 00 */	cmpwi r0, 0
/* 8013CB14 00137A14  40 82 01 7C */	bne lbl_8013CC90
/* 8013CB18 00137A18  80 0D 9F C0 */	lwz r0, WaitingForCoverClose-_SDA_BASE_(r13)
/* 8013CB1C 00137A1C  2C 00 00 00 */	cmpwi r0, 0
/* 8013CB20 00137A20  40 82 01 70 */	bne lbl_8013CC90
/* 8013CB24 00137A24  3F E0 80 47 */	lis r31, CoverAlarm@ha
/* 8013CB28 00137A28  90 8D 9F BC */	stw r4, WaitingForCoverOpen-_SDA_BASE_(r13)
/* 8013CB2C 00137A2C  38 7F 55 40 */	addi r3, r31, CoverAlarm@l
/* 8013CB30 00137A30  4B FB 05 E5 */	bl OSCreateAlarm
/* 8013CB34 00137A34  4B FB 8A E9 */	bl OSGetTick
/* 8013CB38 00137A38  3C A0 80 00 */	lis r5, 0x800000F8@ha
/* 8013CB3C 00137A3C  3C 80 10 62 */	lis r4, 0x10624DD3@ha
/* 8013CB40 00137A40  80 05 00 F8 */	lwz r0, 0x800000F8@l(r5)
/* 8013CB44 00137A44  3D 20 80 14 */	lis r9, CoverAlarmHandler@ha
/* 8013CB48 00137A48  7C 66 1B 78 */	mr r6, r3
/* 8013CB4C 00137A4C  38 84 4D D3 */	addi r4, r4, 0x10624DD3@l
/* 8013CB50 00137A50  54 00 F0 BE */	srwi r0, r0, 2
/* 8013CB54 00137A54  38 7F 55 40 */	addi r3, r31, 0x5540
/* 8013CB58 00137A58  7C 04 00 16 */	mulhwu r0, r4, r0
/* 8013CB5C 00137A5C  39 29 C9 C8 */	addi r9, r9, CoverAlarmHandler@l
/* 8013CB60 00137A60  38 A0 00 00 */	li r5, 0
/* 8013CB64 00137A64  38 E0 00 00 */	li r7, 0
/* 8013CB68 00137A68  54 00 D1 BE */	srwi r0, r0, 6
/* 8013CB6C 00137A6C  1D 00 00 64 */	mulli r8, r0, 0x64
/* 8013CB70 00137A70  4B FB 08 75 */	bl OSSetPeriodicAlarm
/* 8013CB74 00137A74  48 00 01 1C */	b lbl_8013CC90
lbl_8013CB78:
/* 8013CB78 00137A78  38 00 00 04 */	li r0, 4
/* 8013CB7C 00137A7C  38 80 00 01 */	li r4, 1
/* 8013CB80 00137A80  90 03 00 0C */	stw r0, 0xc(r3)
/* 8013CB84 00137A84  80 0D 9F BC */	lwz r0, WaitingForCoverOpen-_SDA_BASE_(r13)
/* 8013CB88 00137A88  90 8D 9F F8 */	stw r4, MotorState-_SDA_BASE_(r13)
/* 8013CB8C 00137A8C  2C 00 00 00 */	cmpwi r0, 0
/* 8013CB90 00137A90  40 82 01 00 */	bne lbl_8013CC90
/* 8013CB94 00137A94  80 0D 9F C0 */	lwz r0, WaitingForCoverClose-_SDA_BASE_(r13)
/* 8013CB98 00137A98  2C 00 00 00 */	cmpwi r0, 0
/* 8013CB9C 00137A9C  40 82 00 F4 */	bne lbl_8013CC90
/* 8013CBA0 00137AA0  3F E0 80 47 */	lis r31, CoverAlarm@ha
/* 8013CBA4 00137AA4  90 8D 9F BC */	stw r4, WaitingForCoverOpen-_SDA_BASE_(r13)
/* 8013CBA8 00137AA8  38 7F 55 40 */	addi r3, r31, CoverAlarm@l
/* 8013CBAC 00137AAC  4B FB 05 69 */	bl OSCreateAlarm
/* 8013CBB0 00137AB0  4B FB 8A 6D */	bl OSGetTick
/* 8013CBB4 00137AB4  3C A0 80 00 */	lis r5, 0x800000F8@ha
/* 8013CBB8 00137AB8  3C 80 10 62 */	lis r4, 0x10624DD3@ha
/* 8013CBBC 00137ABC  80 05 00 F8 */	lwz r0, 0x800000F8@l(r5)
/* 8013CBC0 00137AC0  3D 20 80 14 */	lis r9, CoverAlarmHandler@ha
/* 8013CBC4 00137AC4  7C 66 1B 78 */	mr r6, r3
/* 8013CBC8 00137AC8  38 84 4D D3 */	addi r4, r4, 0x10624DD3@l
/* 8013CBCC 00137ACC  54 00 F0 BE */	srwi r0, r0, 2
/* 8013CBD0 00137AD0  38 7F 55 40 */	addi r3, r31, 0x5540
/* 8013CBD4 00137AD4  7C 04 00 16 */	mulhwu r0, r4, r0
/* 8013CBD8 00137AD8  39 29 C9 C8 */	addi r9, r9, CoverAlarmHandler@l
/* 8013CBDC 00137ADC  38 A0 00 00 */	li r5, 0
/* 8013CBE0 00137AE0  38 E0 00 00 */	li r7, 0
/* 8013CBE4 00137AE4  54 00 D1 BE */	srwi r0, r0, 6
/* 8013CBE8 00137AE8  1D 00 00 64 */	mulli r8, r0, 0x64
/* 8013CBEC 00137AEC  4B FB 07 F9 */	bl OSSetPeriodicAlarm
/* 8013CBF0 00137AF0  48 00 00 A0 */	b lbl_8013CC90
lbl_8013CBF4:
/* 8013CBF4 00137AF4  38 00 00 05 */	li r0, 5
/* 8013CBF8 00137AF8  38 80 00 01 */	li r4, 1
/* 8013CBFC 00137AFC  90 03 00 0C */	stw r0, 0xc(r3)
/* 8013CC00 00137B00  80 0D 9F BC */	lwz r0, WaitingForCoverOpen-_SDA_BASE_(r13)
/* 8013CC04 00137B04  90 8D 9F F8 */	stw r4, MotorState-_SDA_BASE_(r13)
/* 8013CC08 00137B08  2C 00 00 00 */	cmpwi r0, 0
/* 8013CC0C 00137B0C  40 82 00 84 */	bne lbl_8013CC90
/* 8013CC10 00137B10  80 0D 9F C0 */	lwz r0, WaitingForCoverClose-_SDA_BASE_(r13)
/* 8013CC14 00137B14  2C 00 00 00 */	cmpwi r0, 0
/* 8013CC18 00137B18  40 82 00 78 */	bne lbl_8013CC90
/* 8013CC1C 00137B1C  3F E0 80 47 */	lis r31, CoverAlarm@ha
/* 8013CC20 00137B20  90 8D 9F BC */	stw r4, WaitingForCoverOpen-_SDA_BASE_(r13)
/* 8013CC24 00137B24  38 7F 55 40 */	addi r3, r31, CoverAlarm@l
/* 8013CC28 00137B28  4B FB 04 ED */	bl OSCreateAlarm
/* 8013CC2C 00137B2C  4B FB 89 F1 */	bl OSGetTick
/* 8013CC30 00137B30  3C A0 80 00 */	lis r5, 0x800000F8@ha
/* 8013CC34 00137B34  3C 80 10 62 */	lis r4, 0x10624DD3@ha
/* 8013CC38 00137B38  80 05 00 F8 */	lwz r0, 0x800000F8@l(r5)
/* 8013CC3C 00137B3C  3D 20 80 14 */	lis r9, CoverAlarmHandler@ha
/* 8013CC40 00137B40  7C 66 1B 78 */	mr r6, r3
/* 8013CC44 00137B44  38 84 4D D3 */	addi r4, r4, 0x10624DD3@l
/* 8013CC48 00137B48  54 00 F0 BE */	srwi r0, r0, 2
/* 8013CC4C 00137B4C  38 7F 55 40 */	addi r3, r31, 0x5540
/* 8013CC50 00137B50  7C 04 00 16 */	mulhwu r0, r4, r0
/* 8013CC54 00137B54  39 29 C9 C8 */	addi r9, r9, CoverAlarmHandler@l
/* 8013CC58 00137B58  38 A0 00 00 */	li r5, 0
/* 8013CC5C 00137B5C  38 E0 00 00 */	li r7, 0
/* 8013CC60 00137B60  54 00 D1 BE */	srwi r0, r0, 6
/* 8013CC64 00137B64  1D 00 00 64 */	mulli r8, r0, 0x64
/* 8013CC68 00137B68  4B FB 07 7D */	bl OSSetPeriodicAlarm
/* 8013CC6C 00137B6C  48 00 00 24 */	b lbl_8013CC90
lbl_8013CC70:
/* 8013CC70 00137B70  38 00 00 03 */	li r0, 3
/* 8013CC74 00137B74  90 03 00 0C */	stw r0, 0xc(r3)
/* 8013CC78 00137B78  4B FF F4 71 */	bl stateCoverClosed
/* 8013CC7C 00137B7C  48 00 00 14 */	b lbl_8013CC90
lbl_8013CC80:
/* 8013CC80 00137B80  3C 80 80 14 */	lis r4, cbForStoreErrorCode1@ha
/* 8013CC84 00137B84  80 6D A0 04 */	lwz r3, CancelLastError-_SDA_BASE_(r13)
/* 8013CC88 00137B88  38 84 A6 10 */	addi r4, r4, cbForStoreErrorCode1@l
/* 8013CC8C 00137B8C  48 00 1C 0D */	bl __DVDStoreErrorCode
lbl_8013CC90:
/* 8013CC90 00137B90  38 00 00 00 */	li r0, 0
/* 8013CC94 00137B94  90 0D 9F AC */	stw r0, ResumeFromHere-_SDA_BASE_(r13)
/* 8013CC98 00137B98  48 00 00 68 */	b lbl_8013CD00
lbl_8013CC9C:
/* 8013CC9C 00137B9C  80 0D 9F F8 */	lwz r0, MotorState-_SDA_BASE_(r13)
/* 8013CCA0 00137BA0  2C 00 00 01 */	cmpwi r0, 1
/* 8013CCA4 00137BA4  41 82 00 58 */	beq lbl_8013CCFC
/* 8013CCA8 00137BA8  40 80 00 10 */	bge lbl_8013CCB8
/* 8013CCAC 00137BAC  2C 00 00 00 */	cmpwi r0, 0
/* 8013CCB0 00137BB0  40 80 00 38 */	bge lbl_8013CCE8
/* 8013CCB4 00137BB4  48 00 00 48 */	b lbl_8013CCFC
lbl_8013CCB8:
/* 8013CCB8 00137BB8  2C 00 00 03 */	cmpwi r0, 3
/* 8013CCBC 00137BBC  40 80 00 40 */	bge lbl_8013CCFC
/* 8013CCC0 00137BC0  80 0D 9F C4 */	lwz r0, MotorStopped-_SDA_BASE_(r13)
/* 8013CCC4 00137BC4  2C 00 00 00 */	cmpwi r0, 0
/* 8013CCC8 00137BC8  41 82 00 10 */	beq lbl_8013CCD8
/* 8013CCCC 00137BCC  38 00 00 0C */	li r0, 0xc
/* 8013CCD0 00137BD0  90 03 00 0C */	stw r0, 0xc(r3)
/* 8013CCD4 00137BD4  48 00 00 2C */	b lbl_8013CD00
lbl_8013CCD8:
/* 8013CCD8 00137BD8  38 00 00 03 */	li r0, 3
/* 8013CCDC 00137BDC  90 03 00 0C */	stw r0, 0xc(r3)
/* 8013CCE0 00137BE0  4B FF F4 09 */	bl stateCoverClosed
/* 8013CCE4 00137BE4  48 00 00 1C */	b lbl_8013CD00
lbl_8013CCE8:
/* 8013CCE8 00137BE8  38 00 00 01 */	li r0, 1
/* 8013CCEC 00137BEC  90 03 00 0C */	stw r0, 0xc(r3)
/* 8013CCF0 00137BF0  80 6D A0 18 */	lwz r3, executing-_SDA_BASE_(r13)
/* 8013CCF4 00137BF4  48 00 00 21 */	bl stateBusy
/* 8013CCF8 00137BF8  48 00 00 08 */	b lbl_8013CD00
lbl_8013CCFC:
/* 8013CCFC 00137BFC  4B FF F3 ED */	bl stateCoverClosed
lbl_8013CD00:
/* 8013CD00 00137C00  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8013CD04 00137C04  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8013CD08 00137C08  7C 08 03 A6 */	mtlr r0
/* 8013CD0C 00137C0C  38 21 00 10 */	addi r1, r1, 0x10
/* 8013CD10 00137C10  4E 80 00 20 */	blr 

.global stateBusy
stateBusy:
/* 8013CD14 00137C14  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8013CD18 00137C18  7C 08 02 A6 */	mflr r0
/* 8013CD1C 00137C1C  90 01 00 24 */	stw r0, 0x24(r1)
/* 8013CD20 00137C20  39 61 00 20 */	addi r11, r1, 0x20
/* 8013CD24 00137C24  4B F7 50 1D */	bl _savegpr_26
/* 8013CD28 00137C28  3C 80 80 14 */	lis r4, stateBusy@ha
/* 8013CD2C 00137C2C  7C 7D 1B 78 */	mr r29, r3
/* 8013CD30 00137C30  38 84 CD 14 */	addi r4, r4, stateBusy@l
/* 8013CD34 00137C34  90 8D A0 1C */	stw r4, LastState-_SDA_BASE_(r13)
/* 8013CD38 00137C38  83 43 00 08 */	lwz r26, 8(r3)
/* 8013CD3C 00137C3C  2C 1A 00 11 */	cmpwi r26, 0x11
/* 8013CD40 00137C40  40 80 00 30 */	bge lbl_8013CD70
/* 8013CD44 00137C44  2C 1A 00 05 */	cmpwi r26, 5
/* 8013CD48 00137C48  41 82 00 40 */	beq lbl_8013CD88
/* 8013CD4C 00137C4C  40 80 00 18 */	bge lbl_8013CD64
/* 8013CD50 00137C50  2C 1A 00 04 */	cmpwi r26, 4
/* 8013CD54 00137C54  40 80 00 B8 */	bge lbl_8013CE0C
/* 8013CD58 00137C58  2C 1A 00 02 */	cmpwi r26, 2
/* 8013CD5C 00137C5C  40 80 00 2C */	bge lbl_8013CD88
/* 8013CD60 00137C60  48 00 00 AC */	b lbl_8013CE0C
lbl_8013CD64:
/* 8013CD64 00137C64  2C 1A 00 0D */	cmpwi r26, 0xd
/* 8013CD68 00137C68  40 80 00 20 */	bge lbl_8013CD88
/* 8013CD6C 00137C6C  48 00 00 A0 */	b lbl_8013CE0C
lbl_8013CD70:
/* 8013CD70 00137C70  2C 1A 00 25 */	cmpwi r26, 0x25
/* 8013CD74 00137C74  41 82 00 14 */	beq lbl_8013CD88
/* 8013CD78 00137C78  40 80 00 94 */	bge lbl_8013CE0C
/* 8013CD7C 00137C7C  2C 1A 00 22 */	cmpwi r26, 0x22
/* 8013CD80 00137C80  41 82 00 08 */	beq lbl_8013CD88
/* 8013CD84 00137C84  48 00 00 88 */	b lbl_8013CE0C
lbl_8013CD88:
/* 8013CD88 00137C88  83 63 00 14 */	lwz r27, 0x14(r3)
/* 8013CD8C 00137C8C  83 C3 00 10 */	lwz r30, 0x10(r3)
/* 8013CD90 00137C90  4B FB 4B 31 */	bl OSDisableInterrupts
/* 8013CD94 00137C94  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013CD98 00137C98  7C 7F 1B 78 */	mr r31, r3
/* 8013CD9C 00137C9C  28 00 00 05 */	cmplwi r0, 5
/* 8013CDA0 00137CA0  41 80 00 0C */	blt lbl_8013CDAC
/* 8013CDA4 00137CA4  38 00 00 00 */	li r0, 0
/* 8013CDA8 00137CA8  90 0D 9F 98 */	stw r0, CommandInfoCounter-_SDA_BASE_(r13)
lbl_8013CDAC:
/* 8013CDAC 00137CAC  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013CDB0 00137CB0  3F 80 80 48 */	lis r28, __ErrorInfo@ha
/* 8013CDB4 00137CB4  80 6D 9F 98 */	lwz r3, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013CDB8 00137CB8  3B 9C A2 20 */	addi r28, r28, __ErrorInfo@l
/* 8013CDBC 00137CBC  1C 80 00 14 */	mulli r4, r0, 0x14
/* 8013CDC0 00137CC0  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013CDC4 00137CC4  1C 63 00 14 */	mulli r3, r3, 0x14
/* 8013CDC8 00137CC8  7C 9C 22 14 */	add r4, r28, r4
/* 8013CDCC 00137CCC  93 44 00 1C */	stw r26, 0x1c(r4)
/* 8013CDD0 00137CD0  7C 7C 1A 14 */	add r3, r28, r3
/* 8013CDD4 00137CD4  1C 00 00 14 */	mulli r0, r0, 0x14
/* 8013CDD8 00137CD8  93 C3 00 20 */	stw r30, 0x20(r3)
/* 8013CDDC 00137CDC  7C 7C 02 14 */	add r3, r28, r0
/* 8013CDE0 00137CE0  93 63 00 24 */	stw r27, 0x24(r3)
/* 8013CDE4 00137CE4  4B FB 88 39 */	bl OSGetTick
/* 8013CDE8 00137CE8  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013CDEC 00137CEC  80 8D 9F 98 */	lwz r4, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013CDF0 00137CF0  1C A0 00 14 */	mulli r5, r0, 0x14
/* 8013CDF4 00137CF4  38 04 00 01 */	addi r0, r4, 1
/* 8013CDF8 00137CF8  90 0D 9F 98 */	stw r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013CDFC 00137CFC  7C 9C 2A 14 */	add r4, r28, r5
/* 8013CE00 00137D00  90 64 00 2C */	stw r3, 0x2c(r4)
/* 8013CE04 00137D04  7F E3 FB 78 */	mr r3, r31
/* 8013CE08 00137D08  4B FB 4A E1 */	bl OSRestoreInterrupts
lbl_8013CE0C:
/* 8013CE0C 00137D0C  80 1D 00 08 */	lwz r0, 8(r29)
/* 8013CE10 00137D10  28 00 00 26 */	cmplwi r0, 0x26
/* 8013CE14 00137D14  41 81 03 D8 */	bgt lbl_8013D1EC
/* 8013CE18 00137D18  3C 60 80 3B */	lis r3, lbl_803B5F40@ha
/* 8013CE1C 00137D1C  54 00 10 3A */	slwi r0, r0, 2
/* 8013CE20 00137D20  38 63 5F 40 */	addi r3, r3, lbl_803B5F40@l
/* 8013CE24 00137D24  7C 63 00 2E */	lwzx r3, r3, r0
/* 8013CE28 00137D28  7C 69 03 A6 */	mtctr r3
/* 8013CE2C 00137D2C  4E 80 04 20 */	bctr 
/* 8013CE30 00137D30  38 60 00 00 */	li r3, 0
/* 8013CE34 00137D34  48 00 35 B5 */	bl DVDLowClearCoverInterrupt
/* 8013CE38 00137D38  38 00 00 20 */	li r0, 0x20
/* 8013CE3C 00137D3C  3C 80 80 14 */	lis r4, cbForStateBusy@ha
/* 8013CE40 00137D40  90 1D 00 1C */	stw r0, 0x1c(r29)
/* 8013CE44 00137D44  38 84 D2 1C */	addi r4, r4, cbForStateBusy@l
/* 8013CE48 00137D48  80 7D 00 18 */	lwz r3, 0x18(r29)
/* 8013CE4C 00137D4C  48 00 20 F5 */	bl DVDLowReadDiskID
/* 8013CE50 00137D50  48 00 03 B4 */	b lbl_8013D204
/* 8013CE54 00137D54  80 1D 00 14 */	lwz r0, 0x14(r29)
/* 8013CE58 00137D58  2C 00 00 00 */	cmpwi r0, 0
/* 8013CE5C 00137D5C  40 82 00 3C */	bne lbl_8013CE98
/* 8013CE60 00137D60  3C 60 80 47 */	lis r3, DummyCommandBlock@ha
/* 8013CE64 00137D64  80 8D A0 18 */	lwz r4, executing-_SDA_BASE_(r13)
/* 8013CE68 00137D68  38 63 54 E0 */	addi r3, r3, DummyCommandBlock@l
/* 8013CE6C 00137D6C  38 00 00 00 */	li r0, 0
/* 8013CE70 00137D70  90 6D A0 18 */	stw r3, executing-_SDA_BASE_(r13)
/* 8013CE74 00137D74  90 04 00 0C */	stw r0, 0xc(r4)
/* 8013CE78 00137D78  81 84 00 28 */	lwz r12, 0x28(r4)
/* 8013CE7C 00137D7C  2C 0C 00 00 */	cmpwi r12, 0
/* 8013CE80 00137D80  41 82 00 10 */	beq lbl_8013CE90
/* 8013CE84 00137D84  38 60 00 00 */	li r3, 0
/* 8013CE88 00137D88  7D 89 03 A6 */	mtctr r12
/* 8013CE8C 00137D8C  4E 80 04 21 */	bctrl 
lbl_8013CE90:
/* 8013CE90 00137D90  4B FF FB 5D */	bl stateReady
/* 8013CE94 00137D94  48 00 03 70 */	b lbl_8013D204
lbl_8013CE98:
/* 8013CE98 00137D98  38 60 00 00 */	li r3, 0
/* 8013CE9C 00137D9C  48 00 35 4D */	bl DVDLowClearCoverInterrupt
/* 8013CEA0 00137DA0  80 7D 00 20 */	lwz r3, 0x20(r29)
/* 8013CEA4 00137DA4  3F E0 00 08 */	lis r31, 8
/* 8013CEA8 00137DA8  80 1D 00 14 */	lwz r0, 0x14(r29)
/* 8013CEAC 00137DAC  7C 03 00 50 */	subf r0, r3, r0
/* 8013CEB0 00137DB0  7C 00 F8 40 */	cmplw r0, r31
/* 8013CEB4 00137DB4  41 81 00 08 */	bgt lbl_8013CEBC
/* 8013CEB8 00137DB8  7C 1F 03 78 */	mr r31, r0
lbl_8013CEBC:
/* 8013CEBC 00137DBC  80 1D 00 20 */	lwz r0, 0x20(r29)
/* 8013CEC0 00137DC0  80 7D 00 10 */	lwz r3, 0x10(r29)
/* 8013CEC4 00137DC4  54 00 F0 BE */	srwi r0, r0, 2
/* 8013CEC8 00137DC8  93 FD 00 1C */	stw r31, 0x1c(r29)
/* 8013CECC 00137DCC  83 7D 00 08 */	lwz r27, 8(r29)
/* 8013CED0 00137DD0  7F 43 02 14 */	add r26, r3, r0
/* 8013CED4 00137DD4  4B FB 49 ED */	bl OSDisableInterrupts
/* 8013CED8 00137DD8  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013CEDC 00137DDC  7C 7E 1B 78 */	mr r30, r3
/* 8013CEE0 00137DE0  28 00 00 05 */	cmplwi r0, 5
/* 8013CEE4 00137DE4  41 80 00 0C */	blt lbl_8013CEF0
/* 8013CEE8 00137DE8  38 00 00 00 */	li r0, 0
/* 8013CEEC 00137DEC  90 0D 9F 98 */	stw r0, CommandInfoCounter-_SDA_BASE_(r13)
lbl_8013CEF0:
/* 8013CEF0 00137DF0  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013CEF4 00137DF4  3F 80 80 48 */	lis r28, __ErrorInfo@ha
/* 8013CEF8 00137DF8  80 6D 9F 98 */	lwz r3, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013CEFC 00137DFC  3B 9C A2 20 */	addi r28, r28, __ErrorInfo@l
/* 8013CF00 00137E00  1C 80 00 14 */	mulli r4, r0, 0x14
/* 8013CF04 00137E04  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013CF08 00137E08  1C 63 00 14 */	mulli r3, r3, 0x14
/* 8013CF0C 00137E0C  7C 9C 22 14 */	add r4, r28, r4
/* 8013CF10 00137E10  93 64 00 1C */	stw r27, 0x1c(r4)
/* 8013CF14 00137E14  7C 7C 1A 14 */	add r3, r28, r3
/* 8013CF18 00137E18  1C 00 00 14 */	mulli r0, r0, 0x14
/* 8013CF1C 00137E1C  93 43 00 20 */	stw r26, 0x20(r3)
/* 8013CF20 00137E20  7C 7C 02 14 */	add r3, r28, r0
/* 8013CF24 00137E24  93 E3 00 24 */	stw r31, 0x24(r3)
/* 8013CF28 00137E28  4B FB 86 F5 */	bl OSGetTick
/* 8013CF2C 00137E2C  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013CF30 00137E30  80 8D 9F 98 */	lwz r4, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013CF34 00137E34  1C A0 00 14 */	mulli r5, r0, 0x14
/* 8013CF38 00137E38  38 04 00 01 */	addi r0, r4, 1
/* 8013CF3C 00137E3C  90 0D 9F 98 */	stw r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013CF40 00137E40  7C 9C 2A 14 */	add r4, r28, r5
/* 8013CF44 00137E44  90 64 00 2C */	stw r3, 0x2c(r4)
/* 8013CF48 00137E48  7F C3 F3 78 */	mr r3, r30
/* 8013CF4C 00137E4C  4B FB 49 9D */	bl OSRestoreInterrupts
/* 8013CF50 00137E50  80 FD 00 20 */	lwz r7, 0x20(r29)
/* 8013CF54 00137E54  3C C0 80 14 */	lis r6, cbForStateBusy@ha
/* 8013CF58 00137E58  80 7D 00 18 */	lwz r3, 0x18(r29)
/* 8013CF5C 00137E5C  38 C6 D2 1C */	addi r6, r6, cbForStateBusy@l
/* 8013CF60 00137E60  80 BD 00 10 */	lwz r5, 0x10(r29)
/* 8013CF64 00137E64  54 E0 F0 BE */	srwi r0, r7, 2
/* 8013CF68 00137E68  80 9D 00 1C */	lwz r4, 0x1c(r29)
/* 8013CF6C 00137E6C  7C 63 3A 14 */	add r3, r3, r7
/* 8013CF70 00137E70  7C A5 02 14 */	add r5, r5, r0
/* 8013CF74 00137E74  48 00 2F B5 */	bl DVDLowRead
/* 8013CF78 00137E78  48 00 02 8C */	b lbl_8013D204
/* 8013CF7C 00137E7C  38 60 00 00 */	li r3, 0
/* 8013CF80 00137E80  48 00 34 69 */	bl DVDLowClearCoverInterrupt
/* 8013CF84 00137E84  3C 80 80 14 */	lis r4, cbForStateBusy@ha
/* 8013CF88 00137E88  80 7D 00 10 */	lwz r3, 0x10(r29)
/* 8013CF8C 00137E8C  38 84 D2 1C */	addi r4, r4, cbForStateBusy@l
/* 8013CF90 00137E90  48 00 31 49 */	bl DVDLowSeek
/* 8013CF94 00137E94  48 00 02 70 */	b lbl_8013D204
/* 8013CF98 00137E98  3C A0 80 14 */	lis r5, cbForStateBusy@ha
/* 8013CF9C 00137E9C  38 60 00 00 */	li r3, 0
/* 8013CFA0 00137EA0  38 A5 D2 1C */	addi r5, r5, cbForStateBusy@l
/* 8013CFA4 00137EA4  38 80 00 00 */	li r4, 0
/* 8013CFA8 00137EA8  48 00 26 81 */	bl DVDLowStopMotor
/* 8013CFAC 00137EAC  48 00 02 58 */	b lbl_8013D204
/* 8013CFB0 00137EB0  3C A0 80 14 */	lis r5, cbForStateBusy@ha
/* 8013CFB4 00137EB4  38 60 00 00 */	li r3, 0
/* 8013CFB8 00137EB8  38 A5 D2 1C */	addi r5, r5, cbForStateBusy@l
/* 8013CFBC 00137EBC  38 80 00 00 */	li r4, 0
/* 8013CFC0 00137EC0  48 00 26 69 */	bl DVDLowStopMotor
/* 8013CFC4 00137EC4  48 00 02 40 */	b lbl_8013D204
/* 8013CFC8 00137EC8  38 60 00 00 */	li r3, 0
/* 8013CFCC 00137ECC  48 00 34 1D */	bl DVDLowClearCoverInterrupt
/* 8013CFD0 00137ED0  3C A0 80 14 */	lis r5, cbForStateBusy@ha
/* 8013CFD4 00137ED4  80 7D 00 10 */	lwz r3, 0x10(r29)
/* 8013CFD8 00137ED8  80 9D 00 14 */	lwz r4, 0x14(r29)
/* 8013CFDC 00137EDC  38 A5 D2 1C */	addi r5, r5, cbForStateBusy@l
/* 8013CFE0 00137EE0  48 00 2C 35 */	bl DVDLowAudioBufferConfig
/* 8013CFE4 00137EE4  48 00 02 20 */	b lbl_8013D204
/* 8013CFE8 00137EE8  38 60 00 00 */	li r3, 0
/* 8013CFEC 00137EEC  48 00 33 FD */	bl DVDLowClearCoverInterrupt
/* 8013CFF0 00137EF0  38 00 00 20 */	li r0, 0x20
/* 8013CFF4 00137EF4  3C 80 80 14 */	lis r4, cbForStateBusy@ha
/* 8013CFF8 00137EF8  90 1D 00 1C */	stw r0, 0x1c(r29)
/* 8013CFFC 00137EFC  38 84 D2 1C */	addi r4, r4, cbForStateBusy@l
/* 8013D000 00137F00  80 7D 00 18 */	lwz r3, 0x18(r29)
/* 8013D004 00137F04  48 00 27 B9 */	bl DVDLowInquiry
/* 8013D008 00137F08  48 00 01 FC */	b lbl_8013D204
/* 8013D00C 00137F0C  38 60 00 00 */	li r3, 0
/* 8013D010 00137F10  48 00 33 D9 */	bl DVDLowClearCoverInterrupt
/* 8013D014 00137F14  3C A0 80 14 */	lis r5, cbForStateBusy@ha
/* 8013D018 00137F18  38 60 00 00 */	li r3, 0
/* 8013D01C 00137F1C  38 A5 D2 1C */	addi r5, r5, cbForStateBusy@l
/* 8013D020 00137F20  38 80 00 00 */	li r4, 0
/* 8013D024 00137F24  48 00 26 05 */	bl DVDLowStopMotor
/* 8013D028 00137F28  48 00 01 DC */	b lbl_8013D204
/* 8013D02C 00137F2C  38 60 00 01 */	li r3, 1
/* 8013D030 00137F30  48 00 2A 5D */	bl DVDLowSetSpinupFlag
/* 8013D034 00137F34  3C 60 80 14 */	lis r3, cbForStateBusy@ha
/* 8013D038 00137F38  38 63 D2 1C */	addi r3, r3, cbForStateBusy@l
/* 8013D03C 00137F3C  48 00 2A 5D */	bl DVDLowReset
/* 8013D040 00137F40  48 00 01 C4 */	b lbl_8013D204
/* 8013D044 00137F44  80 1D 00 14 */	lwz r0, 0x14(r29)
/* 8013D048 00137F48  2C 00 00 00 */	cmpwi r0, 0
/* 8013D04C 00137F4C  40 82 00 3C */	bne lbl_8013D088
/* 8013D050 00137F50  3C 60 80 47 */	lis r3, DummyCommandBlock@ha
/* 8013D054 00137F54  80 8D A0 18 */	lwz r4, executing-_SDA_BASE_(r13)
/* 8013D058 00137F58  38 63 54 E0 */	addi r3, r3, DummyCommandBlock@l
/* 8013D05C 00137F5C  38 00 00 00 */	li r0, 0
/* 8013D060 00137F60  90 6D A0 18 */	stw r3, executing-_SDA_BASE_(r13)
/* 8013D064 00137F64  90 04 00 0C */	stw r0, 0xc(r4)
/* 8013D068 00137F68  81 84 00 28 */	lwz r12, 0x28(r4)
/* 8013D06C 00137F6C  2C 0C 00 00 */	cmpwi r12, 0
/* 8013D070 00137F70  41 82 00 10 */	beq lbl_8013D080
/* 8013D074 00137F74  38 60 00 00 */	li r3, 0
/* 8013D078 00137F78  7D 89 03 A6 */	mtctr r12
/* 8013D07C 00137F7C  4E 80 04 21 */	bctrl 
lbl_8013D080:
/* 8013D080 00137F80  4B FF F9 6D */	bl stateReady
/* 8013D084 00137F84  48 00 01 80 */	b lbl_8013D204
lbl_8013D088:
/* 8013D088 00137F88  38 60 00 00 */	li r3, 0
/* 8013D08C 00137F8C  48 00 33 5D */	bl DVDLowClearCoverInterrupt
/* 8013D090 00137F90  80 7D 00 20 */	lwz r3, 0x20(r29)
/* 8013D094 00137F94  3F E0 00 08 */	lis r31, 8
/* 8013D098 00137F98  80 1D 00 14 */	lwz r0, 0x14(r29)
/* 8013D09C 00137F9C  7C 03 00 50 */	subf r0, r3, r0
/* 8013D0A0 00137FA0  7C 00 F8 40 */	cmplw r0, r31
/* 8013D0A4 00137FA4  41 81 00 08 */	bgt lbl_8013D0AC
/* 8013D0A8 00137FA8  7C 1F 03 78 */	mr r31, r0
lbl_8013D0AC:
/* 8013D0AC 00137FAC  80 1D 00 20 */	lwz r0, 0x20(r29)
/* 8013D0B0 00137FB0  80 7D 00 10 */	lwz r3, 0x10(r29)
/* 8013D0B4 00137FB4  54 00 F0 BE */	srwi r0, r0, 2
/* 8013D0B8 00137FB8  93 FD 00 1C */	stw r31, 0x1c(r29)
/* 8013D0BC 00137FBC  83 5D 00 08 */	lwz r26, 8(r29)
/* 8013D0C0 00137FC0  7F 63 02 14 */	add r27, r3, r0
/* 8013D0C4 00137FC4  4B FB 47 FD */	bl OSDisableInterrupts
/* 8013D0C8 00137FC8  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013D0CC 00137FCC  7C 7E 1B 78 */	mr r30, r3
/* 8013D0D0 00137FD0  28 00 00 05 */	cmplwi r0, 5
/* 8013D0D4 00137FD4  41 80 00 0C */	blt lbl_8013D0E0
/* 8013D0D8 00137FD8  38 00 00 00 */	li r0, 0
/* 8013D0DC 00137FDC  90 0D 9F 98 */	stw r0, CommandInfoCounter-_SDA_BASE_(r13)
lbl_8013D0E0:
/* 8013D0E0 00137FE0  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013D0E4 00137FE4  3F 80 80 48 */	lis r28, __ErrorInfo@ha
/* 8013D0E8 00137FE8  80 6D 9F 98 */	lwz r3, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013D0EC 00137FEC  3B 9C A2 20 */	addi r28, r28, __ErrorInfo@l
/* 8013D0F0 00137FF0  1C 80 00 14 */	mulli r4, r0, 0x14
/* 8013D0F4 00137FF4  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013D0F8 00137FF8  1C 63 00 14 */	mulli r3, r3, 0x14
/* 8013D0FC 00137FFC  7C 9C 22 14 */	add r4, r28, r4
/* 8013D100 00138000  93 44 00 1C */	stw r26, 0x1c(r4)
/* 8013D104 00138004  7C 7C 1A 14 */	add r3, r28, r3
/* 8013D108 00138008  1C 00 00 14 */	mulli r0, r0, 0x14
/* 8013D10C 0013800C  93 63 00 20 */	stw r27, 0x20(r3)
/* 8013D110 00138010  7C 7C 02 14 */	add r3, r28, r0
/* 8013D114 00138014  93 E3 00 24 */	stw r31, 0x24(r3)
/* 8013D118 00138018  4B FB 85 05 */	bl OSGetTick
/* 8013D11C 0013801C  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013D120 00138020  80 8D 9F 98 */	lwz r4, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013D124 00138024  1C A0 00 14 */	mulli r5, r0, 0x14
/* 8013D128 00138028  38 04 00 01 */	addi r0, r4, 1
/* 8013D12C 0013802C  90 0D 9F 98 */	stw r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013D130 00138030  7C 9C 2A 14 */	add r4, r28, r5
/* 8013D134 00138034  90 64 00 2C */	stw r3, 0x2c(r4)
/* 8013D138 00138038  7F C3 F3 78 */	mr r3, r30
/* 8013D13C 0013803C  4B FB 47 AD */	bl OSRestoreInterrupts
/* 8013D140 00138040  80 FD 00 20 */	lwz r7, 0x20(r29)
/* 8013D144 00138044  3C C0 80 14 */	lis r6, cbForStateBusy@ha
/* 8013D148 00138048  80 7D 00 18 */	lwz r3, 0x18(r29)
/* 8013D14C 0013804C  38 C6 D2 1C */	addi r6, r6, cbForStateBusy@l
/* 8013D150 00138050  80 BD 00 10 */	lwz r5, 0x10(r29)
/* 8013D154 00138054  54 E0 F0 BE */	srwi r0, r7, 2
/* 8013D158 00138058  80 9D 00 1C */	lwz r4, 0x1c(r29)
/* 8013D15C 0013805C  7C 63 3A 14 */	add r3, r3, r7
/* 8013D160 00138060  7C A5 02 14 */	add r5, r5, r0
/* 8013D164 00138064  48 00 23 31 */	bl DVDLowUnencryptedRead
/* 8013D168 00138068  48 00 00 9C */	b lbl_8013D204
/* 8013D16C 0013806C  38 60 00 00 */	li r3, 0
/* 8013D170 00138070  48 00 32 79 */	bl DVDLowClearCoverInterrupt
/* 8013D174 00138074  3D 00 80 14 */	lis r8, cbForStateBusy@ha
/* 8013D178 00138078  80 7D 00 10 */	lwz r3, 0x10(r29)
/* 8013D17C 0013807C  80 FD 00 18 */	lwz r7, 0x18(r29)
/* 8013D180 00138080  39 08 D2 1C */	addi r8, r8, cbForStateBusy@l
/* 8013D184 00138084  38 80 00 00 */	li r4, 0
/* 8013D188 00138088  38 A0 00 00 */	li r5, 0
/* 8013D18C 0013808C  38 C0 00 00 */	li r6, 0
/* 8013D190 00138090  48 00 1F 39 */	bl DVDLowOpenPartition
/* 8013D194 00138094  48 00 00 70 */	b lbl_8013D204
/* 8013D198 00138098  38 60 00 00 */	li r3, 0
/* 8013D19C 0013809C  48 00 32 4D */	bl DVDLowClearCoverInterrupt
/* 8013D1A0 001380A0  3C 60 80 14 */	lis r3, cbForStateBusy@ha
/* 8013D1A4 001380A4  38 63 D2 1C */	addi r3, r3, cbForStateBusy@l
/* 8013D1A8 001380A8  48 00 21 89 */	bl DVDLowClosePartition
/* 8013D1AC 001380AC  48 00 00 58 */	b lbl_8013D204
/* 8013D1B0 001380B0  3C 60 80 14 */	lis r3, cbForStateBusy@ha
/* 8013D1B4 001380B4  38 63 D2 1C */	addi r3, r3, cbForStateBusy@l
/* 8013D1B8 001380B8  48 00 30 AD */	bl DVDLowPrepareCoverRegister
/* 8013D1BC 001380BC  48 00 00 48 */	b lbl_8013D204
/* 8013D1C0 001380C0  3C 60 80 14 */	lis r3, cbForStateBusy@ha
/* 8013D1C4 001380C4  38 63 D2 1C */	addi r3, r3, cbForStateBusy@l
/* 8013D1C8 001380C8  48 00 30 9D */	bl DVDLowPrepareCoverRegister
/* 8013D1CC 001380CC  48 00 00 38 */	b lbl_8013D204
/* 8013D1D0 001380D0  38 60 00 00 */	li r3, 0
/* 8013D1D4 001380D4  48 00 32 15 */	bl DVDLowClearCoverInterrupt
/* 8013D1D8 001380D8  3C 80 80 14 */	lis r4, cbForStateBusy@ha
/* 8013D1DC 001380DC  3C 60 00 02 */	lis r3, 2
/* 8013D1E0 001380E0  38 84 D2 1C */	addi r4, r4, cbForStateBusy@l
/* 8013D1E4 001380E4  48 00 2B C5 */	bl DVDLowSetMaximumRotation
/* 8013D1E8 001380E8  48 00 00 1C */	b lbl_8013D204
lbl_8013D1EC:
/* 8013D1EC 001380EC  81 8D 86 00 */	lwz r12, checkOptionalCommand-_SDA_BASE_(r13)
/* 8013D1F0 001380F0  3C 80 80 14 */	lis r4, cbForStateBusy@ha
/* 8013D1F4 001380F4  7F A3 EB 78 */	mr r3, r29
/* 8013D1F8 001380F8  38 84 D2 1C */	addi r4, r4, cbForStateBusy@l
/* 8013D1FC 001380FC  7D 89 03 A6 */	mtctr r12
/* 8013D200 00138100  4E 80 04 21 */	bctrl 
lbl_8013D204:
/* 8013D204 00138104  39 61 00 20 */	addi r11, r1, 0x20
/* 8013D208 00138108  4B F7 4B 85 */	bl _restgpr_26
/* 8013D20C 0013810C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8013D210 00138110  7C 08 03 A6 */	mtlr r0
/* 8013D214 00138114  38 21 00 20 */	addi r1, r1, 0x20
/* 8013D218 00138118  4E 80 00 20 */	blr 

.global cbForStateBusy
cbForStateBusy:
/* 8013D21C 0013811C  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8013D220 00138120  7C 08 02 A6 */	mflr r0
/* 8013D224 00138124  90 01 00 14 */	stw r0, 0x14(r1)
/* 8013D228 00138128  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8013D22C 0013812C  7C 7F 1B 78 */	mr r31, r3
/* 8013D230 00138130  93 C1 00 08 */	stw r30, 8(r1)
/* 8013D234 00138134  4B FB 46 8D */	bl OSDisableInterrupts
/* 8013D238 00138138  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013D23C 0013813C  2C 00 00 00 */	cmpwi r0, 0
/* 8013D240 00138140  40 82 00 14 */	bne lbl_8013D254
/* 8013D244 00138144  3C 80 80 48 */	lis r4, __ErrorInfo@ha
/* 8013D248 00138148  38 84 A2 20 */	addi r4, r4, __ErrorInfo@l
/* 8013D24C 0013814C  93 E4 00 78 */	stw r31, 0x78(r4)
/* 8013D250 00138150  48 00 00 1C */	b lbl_8013D26C
lbl_8013D254:
/* 8013D254 00138154  80 0D 9F 98 */	lwz r0, CommandInfoCounter-_SDA_BASE_(r13)
/* 8013D258 00138158  3C 80 80 48 */	lis r4, __ErrorInfo@ha
/* 8013D25C 0013815C  38 84 A2 20 */	addi r4, r4, __ErrorInfo@l
/* 8013D260 00138160  1C 00 00 14 */	mulli r0, r0, 0x14
/* 8013D264 00138164  7C 84 02 14 */	add r4, r4, r0
/* 8013D268 00138168  93 E4 00 14 */	stw r31, 0x14(r4)
lbl_8013D26C:
/* 8013D26C 0013816C  4B FB 46 7D */	bl OSRestoreInterrupts
/* 8013D270 00138170  28 1F 00 10 */	cmplwi r31, 0x10
/* 8013D274 00138174  40 82 00 1C */	bne lbl_8013D290
/* 8013D278 00138178  3C 60 01 23 */	lis r3, 0x01234568@ha
/* 8013D27C 0013817C  3C 80 80 14 */	lis r4, cbForStoreErrorCode2@ha
/* 8013D280 00138180  38 63 45 68 */	addi r3, r3, 0x01234568@l
/* 8013D284 00138184  38 84 A6 24 */	addi r4, r4, cbForStoreErrorCode2@l
/* 8013D288 00138188  48 00 16 11 */	bl __DVDStoreErrorCode
/* 8013D28C 0013818C  48 00 07 AC */	b lbl_8013DA38
lbl_8013D290:
/* 8013D290 00138190  28 1F 00 20 */	cmplwi r31, 0x20
/* 8013D294 00138194  40 82 00 1C */	bne lbl_8013D2B0
/* 8013D298 00138198  3C 60 01 23 */	lis r3, 0x01234569@ha
/* 8013D29C 0013819C  3C 80 80 14 */	lis r4, cbForStoreErrorCode2@ha
/* 8013D2A0 001381A0  38 63 45 69 */	addi r3, r3, 0x01234569@l
/* 8013D2A4 001381A4  38 84 A6 24 */	addi r4, r4, cbForStoreErrorCode2@l
/* 8013D2A8 001381A8  48 00 15 F1 */	bl __DVDStoreErrorCode
/* 8013D2AC 001381AC  48 00 07 8C */	b lbl_8013DA38
lbl_8013D2B0:
/* 8013D2B0 001381B0  80 0D A0 0C */	lwz r0, CurrCommand-_SDA_BASE_(r13)
/* 8013D2B4 001381B4  28 00 00 03 */	cmplwi r0, 3
/* 8013D2B8 001381B8  41 82 00 10 */	beq lbl_8013D2C8
/* 8013D2BC 001381BC  80 0D A0 0C */	lwz r0, CurrCommand-_SDA_BASE_(r13)
/* 8013D2C0 001381C0  28 00 00 0F */	cmplwi r0, 0xf
/* 8013D2C4 001381C4  40 82 01 50 */	bne lbl_8013D414
lbl_8013D2C8:
/* 8013D2C8 001381C8  57 E0 07 BD */	rlwinm. r0, r31, 0, 0x1e, 0x1e
/* 8013D2CC 001381CC  41 82 00 1C */	beq lbl_8013D2E8
/* 8013D2D0 001381D0  3C 60 01 23 */	lis r3, 0x01234567@ha
/* 8013D2D4 001381D4  3C 80 80 14 */	lis r4, cbForStoreErrorCode1@ha
/* 8013D2D8 001381D8  38 63 45 67 */	addi r3, r3, 0x01234567@l
/* 8013D2DC 001381DC  38 84 A6 10 */	addi r4, r4, cbForStoreErrorCode1@l
/* 8013D2E0 001381E0  48 00 15 B9 */	bl __DVDStoreErrorCode
/* 8013D2E4 001381E4  48 00 07 54 */	b lbl_8013DA38
lbl_8013D2E8:
/* 8013D2E8 001381E8  38 00 00 00 */	li r0, 0
/* 8013D2EC 001381EC  90 0D 9F B0 */	stw r0, NumInternalRetry-_SDA_BASE_(r13)
/* 8013D2F0 001381F0  80 0D A0 0C */	lwz r0, CurrCommand-_SDA_BASE_(r13)
/* 8013D2F4 001381F4  28 00 00 0F */	cmplwi r0, 0xf
/* 8013D2F8 001381F8  40 82 00 0C */	bne lbl_8013D304
/* 8013D2FC 001381FC  38 00 00 01 */	li r0, 1
/* 8013D300 00138200  90 0D 9F FC */	stw r0, ResetRequired-_SDA_BASE_(r13)
lbl_8013D304:
/* 8013D304 00138204  80 0D 9F A8 */	lwz r0, Canceling-_SDA_BASE_(r13)
/* 8013D308 00138208  2C 00 00 00 */	cmpwi r0, 0
/* 8013D30C 0013820C  41 82 00 70 */	beq lbl_8013D37C
/* 8013D310 00138210  3C 60 80 47 */	lis r3, DummyCommandBlock@ha
/* 8013D314 00138214  83 ED A0 18 */	lwz r31, executing-_SDA_BASE_(r13)
/* 8013D318 00138218  38 63 54 E0 */	addi r3, r3, DummyCommandBlock@l
/* 8013D31C 0013821C  38 00 00 07 */	li r0, 7
/* 8013D320 00138220  90 0D 9F AC */	stw r0, ResumeFromHere-_SDA_BASE_(r13)
/* 8013D324 00138224  38 80 00 00 */	li r4, 0
/* 8013D328 00138228  38 00 00 0A */	li r0, 0xa
/* 8013D32C 0013822C  90 8D 9F A8 */	stw r4, Canceling-_SDA_BASE_(r13)
/* 8013D330 00138230  90 6D A0 18 */	stw r3, executing-_SDA_BASE_(r13)
/* 8013D334 00138234  90 1F 00 0C */	stw r0, 0xc(r31)
/* 8013D338 00138238  81 9F 00 28 */	lwz r12, 0x28(r31)
/* 8013D33C 0013823C  2C 0C 00 00 */	cmpwi r12, 0
/* 8013D340 00138240  41 82 00 14 */	beq lbl_8013D354
/* 8013D344 00138244  7F E4 FB 78 */	mr r4, r31
/* 8013D348 00138248  38 60 FF FD */	li r3, -3
/* 8013D34C 0013824C  7D 89 03 A6 */	mtctr r12
/* 8013D350 00138250  4E 80 04 21 */	bctrl 
lbl_8013D354:
/* 8013D354 00138254  81 8D A0 08 */	lwz r12, CancelCallback-_SDA_BASE_(r13)
/* 8013D358 00138258  2C 0C 00 00 */	cmpwi r12, 0
/* 8013D35C 0013825C  41 82 00 14 */	beq lbl_8013D370
/* 8013D360 00138260  7F E4 FB 78 */	mr r4, r31
/* 8013D364 00138264  38 60 00 00 */	li r3, 0
/* 8013D368 00138268  7D 89 03 A6 */	mtctr r12
/* 8013D36C 0013826C  4E 80 04 21 */	bctrl 
lbl_8013D370:
/* 8013D370 00138270  4B FF F6 7D */	bl stateReady
/* 8013D374 00138274  38 00 00 01 */	li r0, 1
/* 8013D378 00138278  48 00 00 08 */	b lbl_8013D380
lbl_8013D37C:
/* 8013D37C 0013827C  38 00 00 00 */	li r0, 0
lbl_8013D380:
/* 8013D380 00138280  2C 00 00 00 */	cmpwi r0, 0
/* 8013D384 00138284  40 82 06 B4 */	bne lbl_8013DA38
/* 8013D388 00138288  80 0D 9F F8 */	lwz r0, MotorState-_SDA_BASE_(r13)
/* 8013D38C 0013828C  28 00 00 02 */	cmplwi r0, 2
/* 8013D390 00138290  41 82 06 A8 */	beq lbl_8013DA38
/* 8013D394 00138294  80 8D A0 18 */	lwz r4, executing-_SDA_BASE_(r13)
/* 8013D398 00138298  38 00 00 07 */	li r0, 7
/* 8013D39C 0013829C  38 60 00 01 */	li r3, 1
/* 8013D3A0 001382A0  90 04 00 0C */	stw r0, 0xc(r4)
/* 8013D3A4 001382A4  80 0D 9F BC */	lwz r0, WaitingForCoverOpen-_SDA_BASE_(r13)
/* 8013D3A8 001382A8  90 6D 9F F8 */	stw r3, MotorState-_SDA_BASE_(r13)
/* 8013D3AC 001382AC  2C 00 00 00 */	cmpwi r0, 0
/* 8013D3B0 001382B0  40 82 06 88 */	bne lbl_8013DA38
/* 8013D3B4 001382B4  80 0D 9F C0 */	lwz r0, WaitingForCoverClose-_SDA_BASE_(r13)
/* 8013D3B8 001382B8  2C 00 00 00 */	cmpwi r0, 0
/* 8013D3BC 001382BC  40 82 06 7C */	bne lbl_8013DA38
/* 8013D3C0 001382C0  3F E0 80 47 */	lis r31, CoverAlarm@ha
/* 8013D3C4 001382C4  90 6D 9F BC */	stw r3, WaitingForCoverOpen-_SDA_BASE_(r13)
/* 8013D3C8 001382C8  38 7F 55 40 */	addi r3, r31, CoverAlarm@l
/* 8013D3CC 001382CC  4B FA FD 49 */	bl OSCreateAlarm
/* 8013D3D0 001382D0  4B FB 82 4D */	bl OSGetTick
/* 8013D3D4 001382D4  3C A0 80 00 */	lis r5, 0x800000F8@ha
/* 8013D3D8 001382D8  3C 80 10 62 */	lis r4, 0x10624DD3@ha
/* 8013D3DC 001382DC  80 05 00 F8 */	lwz r0, 0x800000F8@l(r5)
/* 8013D3E0 001382E0  3D 20 80 14 */	lis r9, CoverAlarmHandler@ha
/* 8013D3E4 001382E4  7C 66 1B 78 */	mr r6, r3
/* 8013D3E8 001382E8  38 84 4D D3 */	addi r4, r4, 0x10624DD3@l
/* 8013D3EC 001382EC  54 00 F0 BE */	srwi r0, r0, 2
/* 8013D3F0 001382F0  38 7F 55 40 */	addi r3, r31, 0x5540
/* 8013D3F4 001382F4  7C 04 00 16 */	mulhwu r0, r4, r0
/* 8013D3F8 001382F8  39 29 C9 C8 */	addi r9, r9, CoverAlarmHandler@l
/* 8013D3FC 001382FC  38 A0 00 00 */	li r5, 0
/* 8013D400 00138300  38 E0 00 00 */	li r7, 0
/* 8013D404 00138304  54 00 D1 BE */	srwi r0, r0, 6
/* 8013D408 00138308  1D 00 00 64 */	mulli r8, r0, 0x64
/* 8013D40C 0013830C  4B FA FF D9 */	bl OSSetPeriodicAlarm
/* 8013D410 00138310  48 00 06 28 */	b lbl_8013DA38
lbl_8013D414:
/* 8013D414 00138314  80 6D A0 0C */	lwz r3, CurrCommand-_SDA_BASE_(r13)
/* 8013D418 00138318  28 03 00 01 */	cmplwi r3, 1
/* 8013D41C 0013831C  41 82 00 24 */	beq lbl_8013D440
/* 8013D420 00138320  28 03 00 04 */	cmplwi r3, 4
/* 8013D424 00138324  41 82 00 1C */	beq lbl_8013D440
/* 8013D428 00138328  28 03 00 05 */	cmplwi r3, 5
/* 8013D42C 0013832C  41 82 00 14 */	beq lbl_8013D440
/* 8013D430 00138330  28 03 00 21 */	cmplwi r3, 0x21
/* 8013D434 00138334  41 82 00 0C */	beq lbl_8013D440
/* 8013D438 00138338  28 03 00 0E */	cmplwi r3, 0xe
/* 8013D43C 0013833C  40 82 00 0C */	bne lbl_8013D448
lbl_8013D440:
/* 8013D440 00138340  38 00 00 01 */	li r0, 1
/* 8013D444 00138344  48 00 00 1C */	b lbl_8013D460
lbl_8013D448:
/* 8013D448 00138348  80 0D 86 0C */	lwz r0, DmaCommand-_SDA_BASE_(r13)
/* 8013D44C 0013834C  7C 03 00 40 */	cmplw r3, r0
/* 8013D450 00138350  40 82 00 0C */	bne lbl_8013D45C
/* 8013D454 00138354  38 00 00 01 */	li r0, 1
/* 8013D458 00138358  48 00 00 08 */	b lbl_8013D460
lbl_8013D45C:
/* 8013D45C 0013835C  38 00 00 00 */	li r0, 0
lbl_8013D460:
/* 8013D460 00138360  2C 00 00 00 */	cmpwi r0, 0
/* 8013D464 00138364  41 82 00 2C */	beq lbl_8013D490
/* 8013D468 00138368  73 E0 00 09 */	andi. r0, r31, 9
/* 8013D46C 0013836C  41 82 00 10 */	beq lbl_8013D47C
/* 8013D470 00138370  80 6D A0 18 */	lwz r3, executing-_SDA_BASE_(r13)
/* 8013D474 00138374  80 83 00 1C */	lwz r4, 0x1c(r3)
/* 8013D478 00138378  48 00 00 08 */	b lbl_8013D480
lbl_8013D47C:
/* 8013D47C 0013837C  38 80 00 00 */	li r4, 0
lbl_8013D480:
/* 8013D480 00138380  80 6D A0 18 */	lwz r3, executing-_SDA_BASE_(r13)
/* 8013D484 00138384  80 03 00 20 */	lwz r0, 0x20(r3)
/* 8013D488 00138388  7C 00 22 14 */	add r0, r0, r4
/* 8013D48C 0013838C  90 03 00 20 */	stw r0, 0x20(r3)
lbl_8013D490:
/* 8013D490 00138390  80 0D 9F B8 */	lwz r0, Breaking-_SDA_BASE_(r13)
/* 8013D494 00138394  2C 00 00 00 */	cmpwi r0, 0
/* 8013D498 00138398  41 82 00 68 */	beq lbl_8013D500
/* 8013D49C 0013839C  3C 60 80 47 */	lis r3, DummyCommandBlock@ha
/* 8013D4A0 001383A0  83 CD A0 18 */	lwz r30, executing-_SDA_BASE_(r13)
/* 8013D4A4 001383A4  38 80 00 00 */	li r4, 0
/* 8013D4A8 001383A8  38 00 00 0A */	li r0, 0xa
/* 8013D4AC 001383AC  38 63 54 E0 */	addi r3, r3, DummyCommandBlock@l
/* 8013D4B0 001383B0  90 8D 9F B8 */	stw r4, Breaking-_SDA_BASE_(r13)
/* 8013D4B4 001383B4  90 8D 9F A8 */	stw r4, Canceling-_SDA_BASE_(r13)
/* 8013D4B8 001383B8  90 6D A0 18 */	stw r3, executing-_SDA_BASE_(r13)
/* 8013D4BC 001383BC  90 1E 00 0C */	stw r0, 0xc(r30)
/* 8013D4C0 001383C0  81 9E 00 28 */	lwz r12, 0x28(r30)
/* 8013D4C4 001383C4  2C 0C 00 00 */	cmpwi r12, 0
/* 8013D4C8 001383C8  41 82 00 14 */	beq lbl_8013D4DC
/* 8013D4CC 001383CC  7F C4 F3 78 */	mr r4, r30
/* 8013D4D0 001383D0  38 60 FF FD */	li r3, -3
/* 8013D4D4 001383D4  7D 89 03 A6 */	mtctr r12
/* 8013D4D8 001383D8  4E 80 04 21 */	bctrl 
lbl_8013D4DC:
/* 8013D4DC 001383DC  81 8D A0 08 */	lwz r12, CancelCallback-_SDA_BASE_(r13)
/* 8013D4E0 001383E0  2C 0C 00 00 */	cmpwi r12, 0
/* 8013D4E4 001383E4  41 82 00 14 */	beq lbl_8013D4F8
/* 8013D4E8 001383E8  7F C4 F3 78 */	mr r4, r30
/* 8013D4EC 001383EC  38 60 00 00 */	li r3, 0
/* 8013D4F0 001383F0  7D 89 03 A6 */	mtctr r12
/* 8013D4F4 001383F4  4E 80 04 21 */	bctrl 
lbl_8013D4F8:
/* 8013D4F8 001383F8  4B FF F4 F5 */	bl stateReady
/* 8013D4FC 001383FC  48 00 05 3C */	b lbl_8013DA38
lbl_8013D500:
/* 8013D500 00138400  57 E0 07 FF */	clrlwi. r0, r31, 0x1f
/* 8013D504 00138404  41 82 03 F0 */	beq lbl_8013D8F4
/* 8013D508 00138408  3B E0 00 00 */	li r31, 0
/* 8013D50C 0013840C  93 ED 9F B0 */	stw r31, NumInternalRetry-_SDA_BASE_(r13)
/* 8013D510 00138410  80 0D A0 0C */	lwz r0, CurrCommand-_SDA_BASE_(r13)
/* 8013D514 00138414  28 00 00 10 */	cmplwi r0, 0x10
/* 8013D518 00138418  40 82 00 50 */	bne lbl_8013D568
/* 8013D51C 0013841C  80 8D A0 18 */	lwz r4, executing-_SDA_BASE_(r13)
/* 8013D520 00138420  3C 60 80 47 */	lis r3, DummyCommandBlock@ha
/* 8013D524 00138424  38 63 54 E0 */	addi r3, r3, DummyCommandBlock@l
/* 8013D528 00138428  80 A4 00 10 */	lwz r5, 0x10(r4)
/* 8013D52C 0013842C  7C 05 00 D0 */	neg r0, r5
/* 8013D530 00138430  90 6D A0 18 */	stw r3, executing-_SDA_BASE_(r13)
/* 8013D534 00138434  7C 00 2B 78 */	or r0, r0, r5
/* 8013D538 00138438  54 03 0F FE */	srwi r3, r0, 0x1f
/* 8013D53C 0013843C  38 03 00 01 */	addi r0, r3, 1
/* 8013D540 00138440  90 0D 9F F8 */	stw r0, MotorState-_SDA_BASE_(r13)
/* 8013D544 00138444  93 E4 00 0C */	stw r31, 0xc(r4)
/* 8013D548 00138448  81 84 00 28 */	lwz r12, 0x28(r4)
/* 8013D54C 0013844C  2C 0C 00 00 */	cmpwi r12, 0
/* 8013D550 00138450  41 82 00 10 */	beq lbl_8013D560
/* 8013D554 00138454  38 60 00 00 */	li r3, 0
/* 8013D558 00138458  7D 89 03 A6 */	mtctr r12
/* 8013D55C 0013845C  4E 80 04 21 */	bctrl 
lbl_8013D560:
/* 8013D560 00138460  4B FF F4 8D */	bl stateReady
/* 8013D564 00138464  48 00 04 D4 */	b lbl_8013DA38
lbl_8013D568:
/* 8013D568 00138468  80 0D A0 0C */	lwz r0, CurrCommand-_SDA_BASE_(r13)
/* 8013D56C 0013846C  28 00 00 20 */	cmplwi r0, 0x20
/* 8013D570 00138470  40 82 00 50 */	bne lbl_8013D5C0
/* 8013D574 00138474  4B FB 80 B1 */	bl __OSGetSystemTime
/* 8013D578 00138478  3C A0 80 47 */	lis r5, DummyCommandBlock@ha
/* 8013D57C 0013847C  80 CD A0 18 */	lwz r6, executing-_SDA_BASE_(r13)
/* 8013D580 00138480  38 A5 54 E0 */	addi r5, r5, DummyCommandBlock@l
/* 8013D584 00138484  90 8D 9F F4 */	stw r4, (LastResetEnd+0x4)-_SDA_BASE_(r13)
/* 8013D588 00138488  90 6D 9F F0 */	stw r3, LastResetEnd-_SDA_BASE_(r13)
/* 8013D58C 0013848C  93 ED 9F FC */	stw r31, ResetRequired-_SDA_BASE_(r13)
/* 8013D590 00138490  93 ED 9F AC */	stw r31, ResumeFromHere-_SDA_BASE_(r13)
/* 8013D594 00138494  90 AD A0 18 */	stw r5, executing-_SDA_BASE_(r13)
/* 8013D598 00138498  93 E6 00 0C */	stw r31, 0xc(r6)
/* 8013D59C 0013849C  81 86 00 28 */	lwz r12, 0x28(r6)
/* 8013D5A0 001384A0  2C 0C 00 00 */	cmpwi r12, 0
/* 8013D5A4 001384A4  41 82 00 14 */	beq lbl_8013D5B8
/* 8013D5A8 001384A8  7C C4 33 78 */	mr r4, r6
/* 8013D5AC 001384AC  38 60 00 00 */	li r3, 0
/* 8013D5B0 001384B0  7D 89 03 A6 */	mtctr r12
/* 8013D5B4 001384B4  4E 80 04 21 */	bctrl 
lbl_8013D5B8:
/* 8013D5B8 001384B8  4B FF F4 35 */	bl stateReady
/* 8013D5BC 001384BC  48 00 04 7C */	b lbl_8013DA38
lbl_8013D5C0:
/* 8013D5C0 001384C0  80 0D 9F A8 */	lwz r0, Canceling-_SDA_BASE_(r13)
/* 8013D5C4 001384C4  2C 00 00 00 */	cmpwi r0, 0
/* 8013D5C8 001384C8  41 82 00 68 */	beq lbl_8013D630
/* 8013D5CC 001384CC  3C 60 80 47 */	lis r3, DummyCommandBlock@ha
/* 8013D5D0 001384D0  83 CD A0 18 */	lwz r30, executing-_SDA_BASE_(r13)
/* 8013D5D4 001384D4  38 63 54 E0 */	addi r3, r3, DummyCommandBlock@l
/* 8013D5D8 001384D8  93 ED 9F AC */	stw r31, ResumeFromHere-_SDA_BASE_(r13)
/* 8013D5DC 001384DC  38 00 00 0A */	li r0, 0xa
/* 8013D5E0 001384E0  93 ED 9F A8 */	stw r31, Canceling-_SDA_BASE_(r13)
/* 8013D5E4 001384E4  90 6D A0 18 */	stw r3, executing-_SDA_BASE_(r13)
/* 8013D5E8 001384E8  90 1E 00 0C */	stw r0, 0xc(r30)
/* 8013D5EC 001384EC  81 9E 00 28 */	lwz r12, 0x28(r30)
/* 8013D5F0 001384F0  2C 0C 00 00 */	cmpwi r12, 0
/* 8013D5F4 001384F4  41 82 00 14 */	beq lbl_8013D608
/* 8013D5F8 001384F8  7F C4 F3 78 */	mr r4, r30
/* 8013D5FC 001384FC  38 60 FF FD */	li r3, -3
/* 8013D600 00138500  7D 89 03 A6 */	mtctr r12
/* 8013D604 00138504  4E 80 04 21 */	bctrl 
lbl_8013D608:
/* 8013D608 00138508  81 8D A0 08 */	lwz r12, CancelCallback-_SDA_BASE_(r13)
/* 8013D60C 0013850C  2C 0C 00 00 */	cmpwi r12, 0
/* 8013D610 00138510  41 82 00 14 */	beq lbl_8013D624
/* 8013D614 00138514  7F C4 F3 78 */	mr r4, r30
/* 8013D618 00138518  38 60 00 00 */	li r3, 0
/* 8013D61C 0013851C  7D 89 03 A6 */	mtctr r12
/* 8013D620 00138520  4E 80 04 21 */	bctrl 
lbl_8013D624:
/* 8013D624 00138524  4B FF F3 C9 */	bl stateReady
/* 8013D628 00138528  38 00 00 01 */	li r0, 1
/* 8013D62C 0013852C  48 00 00 08 */	b lbl_8013D634
lbl_8013D630:
/* 8013D630 00138530  38 00 00 00 */	li r0, 0
lbl_8013D634:
/* 8013D634 00138534  2C 00 00 00 */	cmpwi r0, 0
/* 8013D638 00138538  40 82 04 00 */	bne lbl_8013DA38
/* 8013D63C 0013853C  80 0D A0 0C */	lwz r0, CurrCommand-_SDA_BASE_(r13)
/* 8013D640 00138540  28 00 00 26 */	cmplwi r0, 0x26
/* 8013D644 00138544  40 82 00 AC */	bne lbl_8013D6F0
/* 8013D648 00138548  48 00 2C 0D */	bl DVDLowGetCoverRegister
/* 8013D64C 0013854C  7C 7F 1B 78 */	mr r31, r3
/* 8013D650 00138550  4B FB 7F D5 */	bl __OSGetSystemTime
/* 8013D654 00138554  3C C0 80 00 */	lis r6, 0x800000F8@ha
/* 8013D658 00138558  3C A0 10 62 */	lis r5, 0x10624DD3@ha
/* 8013D65C 0013855C  80 C6 00 F8 */	lwz r6, 0x800000F8@l(r6)
/* 8013D660 00138560  38 E5 4D D3 */	addi r7, r5, 0x10624DD3@l
/* 8013D664 00138564  81 0D 9F F0 */	lwz r8, LastResetEnd-_SDA_BASE_(r13)
/* 8013D668 00138568  38 00 00 00 */	li r0, 0
/* 8013D66C 0013856C  54 C5 F0 BE */	srwi r5, r6, 2
/* 8013D670 00138570  81 2D 9F F4 */	lwz r9, (LastResetEnd+0x4)-_SDA_BASE_(r13)
/* 8013D674 00138574  7C C7 28 16 */	mulhwu r6, r7, r5
/* 8013D678 00138578  7C 89 20 10 */	subfc r4, r9, r4
/* 8013D67C 0013857C  6C 05 80 00 */	xoris r5, r0, 0x8000
/* 8013D680 00138580  7C 08 19 10 */	subfe r0, r8, r3
/* 8013D684 00138584  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 8013D688 00138588  54 C3 D1 BE */	srwi r3, r6, 6
/* 8013D68C 0013858C  1C 63 00 64 */	mulli r3, r3, 0x64
/* 8013D690 00138590  7C 63 20 10 */	subfc r3, r3, r4
/* 8013D694 00138594  7C A5 01 10 */	subfe r5, r5, r0
/* 8013D698 00138598  7C A0 01 10 */	subfe r5, r0, r0
/* 8013D69C 0013859C  7C A5 00 D1 */	neg. r5, r5
/* 8013D6A0 001385A0  41 82 00 0C */	beq lbl_8013D6AC
/* 8013D6A4 001385A4  38 60 00 00 */	li r3, 0
/* 8013D6A8 001385A8  48 00 00 10 */	b lbl_8013D6B8
lbl_8013D6AC:
/* 8013D6AC 001385AC  57 E0 07 FE */	clrlwi r0, r31, 0x1f
/* 8013D6B0 001385B0  7C 60 00 D0 */	neg r3, r0
/* 8013D6B4 001385B4  38 63 00 02 */	addi r3, r3, 2
lbl_8013D6B8:
/* 8013D6B8 001385B8  3C A0 80 47 */	lis r5, DummyCommandBlock@ha
/* 8013D6BC 001385BC  80 8D A0 18 */	lwz r4, executing-_SDA_BASE_(r13)
/* 8013D6C0 001385C0  38 A5 54 E0 */	addi r5, r5, DummyCommandBlock@l
/* 8013D6C4 001385C4  38 00 00 00 */	li r0, 0
/* 8013D6C8 001385C8  90 AD A0 18 */	stw r5, executing-_SDA_BASE_(r13)
/* 8013D6CC 001385CC  90 04 00 0C */	stw r0, 0xc(r4)
/* 8013D6D0 001385D0  90 64 00 10 */	stw r3, 0x10(r4)
/* 8013D6D4 001385D4  81 84 00 28 */	lwz r12, 0x28(r4)
/* 8013D6D8 001385D8  2C 0C 00 00 */	cmpwi r12, 0
/* 8013D6DC 001385DC  41 82 00 0C */	beq lbl_8013D6E8
/* 8013D6E0 001385E0  7D 89 03 A6 */	mtctr r12
/* 8013D6E4 001385E4  4E 80 04 21 */	bctrl 
lbl_8013D6E8:
/* 8013D6E8 001385E8  4B FF F3 05 */	bl stateReady
/* 8013D6EC 001385EC  48 00 03 4C */	b lbl_8013DA38
lbl_8013D6F0:
/* 8013D6F0 001385F0  80 0D A0 0C */	lwz r0, CurrCommand-_SDA_BASE_(r13)
/* 8013D6F4 001385F4  28 00 00 24 */	cmplwi r0, 0x24
/* 8013D6F8 001385F8  40 82 00 64 */	bne lbl_8013D75C
/* 8013D6FC 001385FC  48 00 2B 59 */	bl DVDLowGetCoverRegister
/* 8013D700 00138600  54 60 F7 FF */	rlwinm. r0, r3, 0x1e, 0x1f, 0x1f
/* 8013D704 00138604  40 82 00 0C */	bne lbl_8013D710
/* 8013D708 00138608  54 60 07 FF */	clrlwi. r0, r3, 0x1f
/* 8013D70C 0013860C  41 82 00 0C */	beq lbl_8013D718
lbl_8013D710:
/* 8013D710 00138610  38 60 00 00 */	li r3, 0
/* 8013D714 00138614  48 00 00 10 */	b lbl_8013D724
lbl_8013D718:
/* 8013D718 00138618  80 0D 9F AC */	lwz r0, ResumeFromHere-_SDA_BASE_(r13)
/* 8013D71C 0013861C  7C 00 00 34 */	cntlzw r0, r0
/* 8013D720 00138620  54 03 D9 7E */	srwi r3, r0, 5
lbl_8013D724:
/* 8013D724 00138624  3C A0 80 47 */	lis r5, DummyCommandBlock@ha
/* 8013D728 00138628  80 8D A0 18 */	lwz r4, executing-_SDA_BASE_(r13)
/* 8013D72C 0013862C  38 A5 54 E0 */	addi r5, r5, DummyCommandBlock@l
/* 8013D730 00138630  38 00 00 00 */	li r0, 0
/* 8013D734 00138634  90 AD A0 18 */	stw r5, executing-_SDA_BASE_(r13)
/* 8013D738 00138638  90 04 00 0C */	stw r0, 0xc(r4)
/* 8013D73C 0013863C  90 64 00 10 */	stw r3, 0x10(r4)
/* 8013D740 00138640  81 84 00 28 */	lwz r12, 0x28(r4)
/* 8013D744 00138644  2C 0C 00 00 */	cmpwi r12, 0
/* 8013D748 00138648  41 82 00 0C */	beq lbl_8013D754
/* 8013D74C 0013864C  7D 89 03 A6 */	mtctr r12
/* 8013D750 00138650  4E 80 04 21 */	bctrl 
lbl_8013D754:
/* 8013D754 00138654  4B FF F2 99 */	bl stateReady
/* 8013D758 00138658  48 00 02 E0 */	b lbl_8013DA38
lbl_8013D75C:
/* 8013D75C 0013865C  80 6D A0 0C */	lwz r3, CurrCommand-_SDA_BASE_(r13)
/* 8013D760 00138660  28 03 00 01 */	cmplwi r3, 1
/* 8013D764 00138664  41 82 00 24 */	beq lbl_8013D788
/* 8013D768 00138668  28 03 00 04 */	cmplwi r3, 4
/* 8013D76C 0013866C  41 82 00 1C */	beq lbl_8013D788
/* 8013D770 00138670  28 03 00 05 */	cmplwi r3, 5
/* 8013D774 00138674  41 82 00 14 */	beq lbl_8013D788
/* 8013D778 00138678  28 03 00 21 */	cmplwi r3, 0x21
/* 8013D77C 0013867C  41 82 00 0C */	beq lbl_8013D788
/* 8013D780 00138680  28 03 00 0E */	cmplwi r3, 0xe
/* 8013D784 00138684  40 82 00 0C */	bne lbl_8013D790
lbl_8013D788:
/* 8013D788 00138688  38 00 00 01 */	li r0, 1
/* 8013D78C 0013868C  48 00 00 1C */	b lbl_8013D7A8
lbl_8013D790:
/* 8013D790 00138690  80 0D 86 0C */	lwz r0, DmaCommand-_SDA_BASE_(r13)
/* 8013D794 00138694  7C 03 00 40 */	cmplw r3, r0
/* 8013D798 00138698  40 82 00 0C */	bne lbl_8013D7A4
/* 8013D79C 0013869C  38 00 00 01 */	li r0, 1
/* 8013D7A0 001386A0  48 00 00 08 */	b lbl_8013D7A8
lbl_8013D7A4:
/* 8013D7A4 001386A4  38 00 00 00 */	li r0, 0
lbl_8013D7A8:
/* 8013D7A8 001386A8  2C 00 00 00 */	cmpwi r0, 0
/* 8013D7AC 001386AC  41 82 00 58 */	beq lbl_8013D804
/* 8013D7B0 001386B0  80 6D A0 18 */	lwz r3, executing-_SDA_BASE_(r13)
/* 8013D7B4 001386B4  80 83 00 20 */	lwz r4, 0x20(r3)
/* 8013D7B8 001386B8  80 03 00 14 */	lwz r0, 0x14(r3)
/* 8013D7BC 001386BC  7C 04 00 40 */	cmplw r4, r0
/* 8013D7C0 001386C0  41 82 00 0C */	beq lbl_8013D7CC
/* 8013D7C4 001386C4  4B FF F5 51 */	bl stateBusy
/* 8013D7C8 001386C8  48 00 02 70 */	b lbl_8013DA38
lbl_8013D7CC:
/* 8013D7CC 001386CC  3C 80 80 47 */	lis r4, DummyCommandBlock@ha
/* 8013D7D0 001386D0  38 00 00 00 */	li r0, 0
/* 8013D7D4 001386D4  38 84 54 E0 */	addi r4, r4, DummyCommandBlock@l
/* 8013D7D8 001386D8  90 8D A0 18 */	stw r4, executing-_SDA_BASE_(r13)
/* 8013D7DC 001386DC  90 03 00 0C */	stw r0, 0xc(r3)
/* 8013D7E0 001386E0  81 83 00 28 */	lwz r12, 0x28(r3)
/* 8013D7E4 001386E4  2C 0C 00 00 */	cmpwi r12, 0
/* 8013D7E8 001386E8  41 82 00 14 */	beq lbl_8013D7FC
/* 8013D7EC 001386EC  7C 64 1B 78 */	mr r4, r3
/* 8013D7F0 001386F0  80 63 00 20 */	lwz r3, 0x20(r3)
/* 8013D7F4 001386F4  7D 89 03 A6 */	mtctr r12
/* 8013D7F8 001386F8  4E 80 04 21 */	bctrl 
lbl_8013D7FC:
/* 8013D7FC 001386FC  4B FF F1 F1 */	bl stateReady
/* 8013D800 00138700  48 00 02 38 */	b lbl_8013DA38
lbl_8013D804:
/* 8013D804 00138704  80 6D A0 0C */	lwz r3, CurrCommand-_SDA_BASE_(r13)
/* 8013D808 00138708  38 03 FF F7 */	addi r0, r3, -9
/* 8013D80C 0013870C  28 00 00 03 */	cmplwi r0, 3
/* 8013D810 00138710  41 81 00 0C */	bgt lbl_8013D81C
/* 8013D814 00138714  38 00 00 01 */	li r0, 1
/* 8013D818 00138718  48 00 00 48 */	b lbl_8013D860
lbl_8013D81C:
/* 8013D81C 0013871C  3C 80 80 3B */	lis r4, 0x803b
/* 8013D820 00138720  84 04 5F DC */	lwzu r0, 0x5fdc(r4)
/* 8013D824 00138724  7C 03 00 40 */	cmplw r3, r0
/* 8013D828 00138728  40 82 00 0C */	bne lbl_8013D834
/* 8013D82C 0013872C  38 00 00 01 */	li r0, 1
/* 8013D830 00138730  48 00 00 30 */	b lbl_8013D860
lbl_8013D834:
/* 8013D834 00138734  80 04 00 04 */	lwz r0, 4(r4)
/* 8013D838 00138738  7C 03 00 40 */	cmplw r3, r0
/* 8013D83C 0013873C  40 82 00 0C */	bne lbl_8013D848
/* 8013D840 00138740  38 00 00 01 */	li r0, 1
/* 8013D844 00138744  48 00 00 1C */	b lbl_8013D860
lbl_8013D848:
/* 8013D848 00138748  80 04 00 08 */	lwz r0, 8(r4)
/* 8013D84C 0013874C  7C 03 00 40 */	cmplw r3, r0
/* 8013D850 00138750  40 82 00 0C */	bne lbl_8013D85C
/* 8013D854 00138754  38 00 00 01 */	li r0, 1
/* 8013D858 00138758  48 00 00 08 */	b lbl_8013D860
lbl_8013D85C:
/* 8013D85C 0013875C  38 00 00 00 */	li r0, 0
lbl_8013D860:
/* 8013D860 00138760  2C 00 00 00 */	cmpwi r0, 0
/* 8013D864 00138764  41 82 00 58 */	beq lbl_8013D8BC
/* 8013D868 00138768  80 6D A0 0C */	lwz r3, CurrCommand-_SDA_BASE_(r13)
/* 8013D86C 0013876C  38 03 FF F6 */	addi r0, r3, -10
/* 8013D870 00138770  28 00 00 01 */	cmplwi r0, 1
/* 8013D874 00138774  41 81 00 10 */	bgt lbl_8013D884
/* 8013D878 00138778  48 00 2B 55 */	bl DVDLowGetImmBufferReg
/* 8013D87C 0013877C  54 63 10 3A */	slwi r3, r3, 2
/* 8013D880 00138780  48 00 00 08 */	b lbl_8013D888
lbl_8013D884:
/* 8013D884 00138784  48 00 2B 49 */	bl DVDLowGetImmBufferReg
lbl_8013D888:
/* 8013D888 00138788  3C A0 80 47 */	lis r5, DummyCommandBlock@ha
/* 8013D88C 0013878C  80 8D A0 18 */	lwz r4, executing-_SDA_BASE_(r13)
/* 8013D890 00138790  38 A5 54 E0 */	addi r5, r5, DummyCommandBlock@l
/* 8013D894 00138794  38 00 00 00 */	li r0, 0
/* 8013D898 00138798  90 AD A0 18 */	stw r5, executing-_SDA_BASE_(r13)
/* 8013D89C 0013879C  90 04 00 0C */	stw r0, 0xc(r4)
/* 8013D8A0 001387A0  81 84 00 28 */	lwz r12, 0x28(r4)
/* 8013D8A4 001387A4  2C 0C 00 00 */	cmpwi r12, 0
/* 8013D8A8 001387A8  41 82 00 0C */	beq lbl_8013D8B4
/* 8013D8AC 001387AC  7D 89 03 A6 */	mtctr r12
/* 8013D8B0 001387B0  4E 80 04 21 */	bctrl 
lbl_8013D8B4:
/* 8013D8B4 001387B4  4B FF F1 39 */	bl stateReady
/* 8013D8B8 001387B8  48 00 01 80 */	b lbl_8013DA38
lbl_8013D8BC:
/* 8013D8BC 001387BC  3C 60 80 47 */	lis r3, DummyCommandBlock@ha
/* 8013D8C0 001387C0  80 8D A0 18 */	lwz r4, executing-_SDA_BASE_(r13)
/* 8013D8C4 001387C4  38 63 54 E0 */	addi r3, r3, DummyCommandBlock@l
/* 8013D8C8 001387C8  38 00 00 00 */	li r0, 0
/* 8013D8CC 001387CC  90 6D A0 18 */	stw r3, executing-_SDA_BASE_(r13)
/* 8013D8D0 001387D0  90 04 00 0C */	stw r0, 0xc(r4)
/* 8013D8D4 001387D4  81 84 00 28 */	lwz r12, 0x28(r4)
/* 8013D8D8 001387D8  2C 0C 00 00 */	cmpwi r12, 0
/* 8013D8DC 001387DC  41 82 00 10 */	beq lbl_8013D8EC
/* 8013D8E0 001387E0  38 60 00 00 */	li r3, 0
/* 8013D8E4 001387E4  7D 89 03 A6 */	mtctr r12
/* 8013D8E8 001387E8  4E 80 04 21 */	bctrl 
lbl_8013D8EC:
/* 8013D8EC 001387EC  4B FF F1 01 */	bl stateReady
/* 8013D8F0 001387F0  48 00 01 48 */	b lbl_8013DA38
lbl_8013D8F4:
/* 8013D8F4 001387F4  80 0D A0 0C */	lwz r0, CurrCommand-_SDA_BASE_(r13)
/* 8013D8F8 001387F8  28 00 00 0E */	cmplwi r0, 0xe
/* 8013D8FC 001387FC  40 82 00 1C */	bne lbl_8013D918
/* 8013D900 00138800  3C 60 01 23 */	lis r3, 0x01234567@ha
/* 8013D904 00138804  3C 80 80 14 */	lis r4, cbForStoreErrorCode1@ha
/* 8013D908 00138808  38 63 45 67 */	addi r3, r3, 0x01234567@l
/* 8013D90C 0013880C  38 84 A6 10 */	addi r4, r4, cbForStoreErrorCode1@l
/* 8013D910 00138810  48 00 0F 89 */	bl __DVDStoreErrorCode
/* 8013D914 00138814  48 00 01 24 */	b lbl_8013DA38
lbl_8013D918:
/* 8013D918 00138818  80 0D A0 0C */	lwz r0, CurrCommand-_SDA_BASE_(r13)
/* 8013D91C 0013881C  28 00 00 01 */	cmplwi r0, 1
/* 8013D920 00138820  41 82 00 34 */	beq lbl_8013D954
/* 8013D924 00138824  80 0D A0 0C */	lwz r0, CurrCommand-_SDA_BASE_(r13)
/* 8013D928 00138828  28 00 00 04 */	cmplwi r0, 4
/* 8013D92C 0013882C  41 82 00 28 */	beq lbl_8013D954
/* 8013D930 00138830  80 0D A0 0C */	lwz r0, CurrCommand-_SDA_BASE_(r13)
/* 8013D934 00138834  28 00 00 05 */	cmplwi r0, 5
/* 8013D938 00138838  41 82 00 1C */	beq lbl_8013D954
/* 8013D93C 0013883C  80 0D A0 0C */	lwz r0, CurrCommand-_SDA_BASE_(r13)
/* 8013D940 00138840  28 00 00 21 */	cmplwi r0, 0x21
/* 8013D944 00138844  41 82 00 10 */	beq lbl_8013D954
/* 8013D948 00138848  80 0D A0 0C */	lwz r0, CurrCommand-_SDA_BASE_(r13)
/* 8013D94C 0013884C  28 00 00 0E */	cmplwi r0, 0xe
/* 8013D950 00138850  40 82 00 CC */	bne lbl_8013DA1C
lbl_8013D954:
/* 8013D954 00138854  83 CD A0 18 */	lwz r30, executing-_SDA_BASE_(r13)
/* 8013D958 00138858  80 7E 00 20 */	lwz r3, 0x20(r30)
/* 8013D95C 0013885C  80 1E 00 14 */	lwz r0, 0x14(r30)
/* 8013D960 00138860  7C 03 00 40 */	cmplw r3, r0
/* 8013D964 00138864  40 82 00 B8 */	bne lbl_8013DA1C
/* 8013D968 00138868  80 0D 9F A8 */	lwz r0, Canceling-_SDA_BASE_(r13)
/* 8013D96C 0013886C  2C 00 00 00 */	cmpwi r0, 0
/* 8013D970 00138870  41 82 00 68 */	beq lbl_8013D9D8
/* 8013D974 00138874  3C 60 80 47 */	lis r3, DummyCommandBlock@ha
/* 8013D978 00138878  38 80 00 00 */	li r4, 0
/* 8013D97C 0013887C  38 63 54 E0 */	addi r3, r3, DummyCommandBlock@l
/* 8013D980 00138880  90 8D 9F AC */	stw r4, ResumeFromHere-_SDA_BASE_(r13)
/* 8013D984 00138884  38 00 00 0A */	li r0, 0xa
/* 8013D988 00138888  90 8D 9F A8 */	stw r4, Canceling-_SDA_BASE_(r13)
/* 8013D98C 0013888C  90 6D A0 18 */	stw r3, executing-_SDA_BASE_(r13)
/* 8013D990 00138890  90 1E 00 0C */	stw r0, 0xc(r30)
/* 8013D994 00138894  81 9E 00 28 */	lwz r12, 0x28(r30)
/* 8013D998 00138898  2C 0C 00 00 */	cmpwi r12, 0
/* 8013D99C 0013889C  41 82 00 14 */	beq lbl_8013D9B0
/* 8013D9A0 001388A0  7F C4 F3 78 */	mr r4, r30
/* 8013D9A4 001388A4  38 60 FF FD */	li r3, -3
/* 8013D9A8 001388A8  7D 89 03 A6 */	mtctr r12
/* 8013D9AC 001388AC  4E 80 04 21 */	bctrl 
lbl_8013D9B0:
/* 8013D9B0 001388B0  81 8D A0 08 */	lwz r12, CancelCallback-_SDA_BASE_(r13)
/* 8013D9B4 001388B4  2C 0C 00 00 */	cmpwi r12, 0
/* 8013D9B8 001388B8  41 82 00 14 */	beq lbl_8013D9CC
/* 8013D9BC 001388BC  7F C4 F3 78 */	mr r4, r30
/* 8013D9C0 001388C0  38 60 00 00 */	li r3, 0
/* 8013D9C4 001388C4  7D 89 03 A6 */	mtctr r12
/* 8013D9C8 001388C8  4E 80 04 21 */	bctrl 
lbl_8013D9CC:
/* 8013D9CC 001388CC  4B FF F0 21 */	bl stateReady
/* 8013D9D0 001388D0  38 00 00 01 */	li r0, 1
/* 8013D9D4 001388D4  48 00 00 08 */	b lbl_8013D9DC
lbl_8013D9D8:
/* 8013D9D8 001388D8  38 00 00 00 */	li r0, 0
lbl_8013D9DC:
/* 8013D9DC 001388DC  2C 00 00 00 */	cmpwi r0, 0
/* 8013D9E0 001388E0  40 82 00 58 */	bne lbl_8013DA38
/* 8013D9E4 001388E4  3C 60 80 47 */	lis r3, DummyCommandBlock@ha
/* 8013D9E8 001388E8  80 8D A0 18 */	lwz r4, executing-_SDA_BASE_(r13)
/* 8013D9EC 001388EC  38 63 54 E0 */	addi r3, r3, DummyCommandBlock@l
/* 8013D9F0 001388F0  38 00 00 00 */	li r0, 0
/* 8013D9F4 001388F4  90 6D A0 18 */	stw r3, executing-_SDA_BASE_(r13)
/* 8013D9F8 001388F8  90 04 00 0C */	stw r0, 0xc(r4)
/* 8013D9FC 001388FC  81 84 00 28 */	lwz r12, 0x28(r4)
/* 8013DA00 00138900  2C 0C 00 00 */	cmpwi r12, 0
/* 8013DA04 00138904  41 82 00 10 */	beq lbl_8013DA14
/* 8013DA08 00138908  80 64 00 20 */	lwz r3, 0x20(r4)
/* 8013DA0C 0013890C  7D 89 03 A6 */	mtctr r12
/* 8013DA10 00138910  4E 80 04 21 */	bctrl 
lbl_8013DA14:
/* 8013DA14 00138914  4B FF EF D9 */	bl stateReady
/* 8013DA18 00138918  48 00 00 20 */	b lbl_8013DA38
lbl_8013DA1C:
/* 8013DA1C 0013891C  38 60 00 27 */	li r3, 0x27
/* 8013DA20 00138920  38 80 00 00 */	li r4, 0
/* 8013DA24 00138924  38 A0 00 00 */	li r5, 0
/* 8013DA28 00138928  4B FF C6 41 */	bl StampCommand
/* 8013DA2C 0013892C  3C 60 80 14 */	lis r3, cbForStateGettingError@ha
/* 8013DA30 00138930  38 63 A8 18 */	addi r3, r3, cbForStateGettingError@l
/* 8013DA34 00138934  48 00 1E F1 */	bl DVDLowRequestError
lbl_8013DA38:
/* 8013DA38 00138938  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8013DA3C 0013893C  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8013DA40 00138940  83 C1 00 08 */	lwz r30, 8(r1)
/* 8013DA44 00138944  7C 08 03 A6 */	mtlr r0
/* 8013DA48 00138948  38 21 00 10 */	addi r1, r1, 0x10
/* 8013DA4C 0013894C  4E 80 00 20 */	blr 

.global DVDReadAbsAsyncPrio
DVDReadAbsAsyncPrio:
/* 8013DA50 00138950  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8013DA54 00138954  7C 08 02 A6 */	mflr r0
/* 8013DA58 00138958  39 20 00 01 */	li r9, 1
/* 8013DA5C 0013895C  90 01 00 24 */	stw r0, 0x24(r1)
/* 8013DA60 00138960  38 00 00 00 */	li r0, 0
/* 8013DA64 00138964  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8013DA68 00138968  7D 1F 43 78 */	mr r31, r8
/* 8013DA6C 0013896C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8013DA70 00138970  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8013DA74 00138974  7C 7D 1B 78 */	mr r29, r3
/* 8013DA78 00138978  91 23 00 08 */	stw r9, 8(r3)
/* 8013DA7C 0013897C  90 83 00 18 */	stw r4, 0x18(r3)
/* 8013DA80 00138980  90 A3 00 14 */	stw r5, 0x14(r3)
/* 8013DA84 00138984  90 C3 00 10 */	stw r6, 0x10(r3)
/* 8013DA88 00138988  90 03 00 20 */	stw r0, 0x20(r3)
/* 8013DA8C 0013898C  90 E3 00 28 */	stw r7, 0x28(r3)
/* 8013DA90 00138990  80 0D 85 FC */	lwz r0, autoInvalidation-_SDA_BASE_(r13)
/* 8013DA94 00138994  2C 00 00 00 */	cmpwi r0, 0
/* 8013DA98 00138998  41 82 00 38 */	beq lbl_8013DAD0
/* 8013DA9C 0013899C  28 09 00 01 */	cmplwi r9, 1
/* 8013DAA0 001389A0  41 82 00 24 */	beq lbl_8013DAC4
/* 8013DAA4 001389A4  28 09 00 04 */	cmplwi r9, 4
/* 8013DAA8 001389A8  41 82 00 1C */	beq lbl_8013DAC4
/* 8013DAAC 001389AC  28 09 00 05 */	cmplwi r9, 5
/* 8013DAB0 001389B0  41 82 00 14 */	beq lbl_8013DAC4
/* 8013DAB4 001389B4  28 09 00 21 */	cmplwi r9, 0x21
/* 8013DAB8 001389B8  41 82 00 0C */	beq lbl_8013DAC4
/* 8013DABC 001389BC  28 09 00 0E */	cmplwi r9, 0xe
/* 8013DAC0 001389C0  40 82 00 10 */	bne lbl_8013DAD0
lbl_8013DAC4:
/* 8013DAC4 001389C4  80 63 00 18 */	lwz r3, 0x18(r3)
/* 8013DAC8 001389C8  80 9D 00 14 */	lwz r4, 0x14(r29)
/* 8013DACC 001389CC  4B FB 06 39 */	bl DCInvalidateRange
lbl_8013DAD0:
/* 8013DAD0 001389D0  4B FB 3D F1 */	bl OSDisableInterrupts
/* 8013DAD4 001389D4  38 00 00 02 */	li r0, 2
/* 8013DAD8 001389D8  7C 7E 1B 78 */	mr r30, r3
/* 8013DADC 001389DC  90 1D 00 0C */	stw r0, 0xc(r29)
/* 8013DAE0 001389E0  7F E3 FB 78 */	mr r3, r31
/* 8013DAE4 001389E4  7F A4 EB 78 */	mr r4, r29
/* 8013DAE8 001389E8  48 00 09 2D */	bl __DVDPushWaitingQueue
/* 8013DAEC 001389EC  80 0D A0 18 */	lwz r0, executing-_SDA_BASE_(r13)
/* 8013DAF0 001389F0  7C 7F 1B 78 */	mr r31, r3
/* 8013DAF4 001389F4  2C 00 00 00 */	cmpwi r0, 0
/* 8013DAF8 001389F8  40 82 00 14 */	bne lbl_8013DB0C
/* 8013DAFC 001389FC  80 0D 9F 9C */	lwz r0, PauseFlag-_SDA_BASE_(r13)
/* 8013DB00 00138A00  2C 00 00 00 */	cmpwi r0, 0
/* 8013DB04 00138A04  40 82 00 08 */	bne lbl_8013DB0C
/* 8013DB08 00138A08  4B FF EE E5 */	bl stateReady
lbl_8013DB0C:
/* 8013DB0C 00138A0C  7F C3 F3 78 */	mr r3, r30
/* 8013DB10 00138A10  4B FB 3D D9 */	bl OSRestoreInterrupts
/* 8013DB14 00138A14  7F E3 FB 78 */	mr r3, r31
/* 8013DB18 00138A18  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8013DB1C 00138A1C  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8013DB20 00138A20  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8013DB24 00138A24  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8013DB28 00138A28  7C 08 03 A6 */	mtlr r0
/* 8013DB2C 00138A2C  38 21 00 20 */	addi r1, r1, 0x20
/* 8013DB30 00138A30  4E 80 00 20 */	blr 

.global DVDInquiryAsync
DVDInquiryAsync:
/* 8013DB34 00138A34  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8013DB38 00138A38  7C 08 02 A6 */	mflr r0
/* 8013DB3C 00138A3C  38 E0 00 0E */	li r7, 0xe
/* 8013DB40 00138A40  38 C0 00 20 */	li r6, 0x20
/* 8013DB44 00138A44  90 01 00 14 */	stw r0, 0x14(r1)
/* 8013DB48 00138A48  38 00 00 00 */	li r0, 0
/* 8013DB4C 00138A4C  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8013DB50 00138A50  7C 7F 1B 78 */	mr r31, r3
/* 8013DB54 00138A54  93 C1 00 08 */	stw r30, 8(r1)
/* 8013DB58 00138A58  90 E3 00 08 */	stw r7, 8(r3)
/* 8013DB5C 00138A5C  90 83 00 18 */	stw r4, 0x18(r3)
/* 8013DB60 00138A60  90 C3 00 14 */	stw r6, 0x14(r3)
/* 8013DB64 00138A64  90 03 00 20 */	stw r0, 0x20(r3)
/* 8013DB68 00138A68  90 A3 00 28 */	stw r5, 0x28(r3)
/* 8013DB6C 00138A6C  80 0D 85 FC */	lwz r0, autoInvalidation-_SDA_BASE_(r13)
/* 8013DB70 00138A70  2C 00 00 00 */	cmpwi r0, 0
/* 8013DB74 00138A74  41 82 00 38 */	beq lbl_8013DBAC
/* 8013DB78 00138A78  28 07 00 01 */	cmplwi r7, 1
/* 8013DB7C 00138A7C  41 82 00 24 */	beq lbl_8013DBA0
/* 8013DB80 00138A80  28 07 00 04 */	cmplwi r7, 4
/* 8013DB84 00138A84  41 82 00 1C */	beq lbl_8013DBA0
/* 8013DB88 00138A88  28 07 00 05 */	cmplwi r7, 5
/* 8013DB8C 00138A8C  41 82 00 14 */	beq lbl_8013DBA0
/* 8013DB90 00138A90  28 07 00 21 */	cmplwi r7, 0x21
/* 8013DB94 00138A94  41 82 00 0C */	beq lbl_8013DBA0
/* 8013DB98 00138A98  28 07 00 0E */	cmplwi r7, 0xe
/* 8013DB9C 00138A9C  40 82 00 10 */	bne lbl_8013DBAC
lbl_8013DBA0:
/* 8013DBA0 00138AA0  80 63 00 18 */	lwz r3, 0x18(r3)
/* 8013DBA4 00138AA4  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 8013DBA8 00138AA8  4B FB 05 5D */	bl DCInvalidateRange
lbl_8013DBAC:
/* 8013DBAC 00138AAC  4B FB 3D 15 */	bl OSDisableInterrupts
/* 8013DBB0 00138AB0  38 00 00 02 */	li r0, 2
/* 8013DBB4 00138AB4  7C 7E 1B 78 */	mr r30, r3
/* 8013DBB8 00138AB8  90 1F 00 0C */	stw r0, 0xc(r31)
/* 8013DBBC 00138ABC  7F E4 FB 78 */	mr r4, r31
/* 8013DBC0 00138AC0  38 60 00 02 */	li r3, 2
/* 8013DBC4 00138AC4  48 00 08 51 */	bl __DVDPushWaitingQueue
/* 8013DBC8 00138AC8  80 0D A0 18 */	lwz r0, executing-_SDA_BASE_(r13)
/* 8013DBCC 00138ACC  7C 7F 1B 78 */	mr r31, r3
/* 8013DBD0 00138AD0  2C 00 00 00 */	cmpwi r0, 0
/* 8013DBD4 00138AD4  40 82 00 14 */	bne lbl_8013DBE8
/* 8013DBD8 00138AD8  80 0D 9F 9C */	lwz r0, PauseFlag-_SDA_BASE_(r13)
/* 8013DBDC 00138ADC  2C 00 00 00 */	cmpwi r0, 0
/* 8013DBE0 00138AE0  40 82 00 08 */	bne lbl_8013DBE8
/* 8013DBE4 00138AE4  4B FF EE 09 */	bl stateReady
lbl_8013DBE8:
/* 8013DBE8 00138AE8  7F C3 F3 78 */	mr r3, r30
/* 8013DBEC 00138AEC  4B FB 3C FD */	bl OSRestoreInterrupts
/* 8013DBF0 00138AF0  7F E3 FB 78 */	mr r3, r31
/* 8013DBF4 00138AF4  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8013DBF8 00138AF8  83 C1 00 08 */	lwz r30, 8(r1)
/* 8013DBFC 00138AFC  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8013DC00 00138B00  7C 08 03 A6 */	mtlr r0
/* 8013DC04 00138B04  38 21 00 10 */	addi r1, r1, 0x10
/* 8013DC08 00138B08  4E 80 00 20 */	blr 

.global DVDGetCommandBlockStatus
DVDGetCommandBlockStatus:
/* 8013DC0C 00138B0C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8013DC10 00138B10  7C 08 02 A6 */	mflr r0
/* 8013DC14 00138B14  90 01 00 24 */	stw r0, 0x24(r1)
/* 8013DC18 00138B18  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8013DC1C 00138B1C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8013DC20 00138B20  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8013DC24 00138B24  7C 7D 1B 78 */	mr r29, r3
/* 8013DC28 00138B28  4B FB 3C 99 */	bl OSDisableInterrupts
/* 8013DC2C 00138B2C  80 1D 00 0C */	lwz r0, 0xc(r29)
/* 8013DC30 00138B30  7C 7E 1B 78 */	mr r30, r3
/* 8013DC34 00138B34  2C 00 00 03 */	cmpwi r0, 3
/* 8013DC38 00138B38  40 82 00 0C */	bne lbl_8013DC44
/* 8013DC3C 00138B3C  3B E0 00 01 */	li r31, 1
/* 8013DC40 00138B40  48 00 00 6C */	b lbl_8013DCAC
lbl_8013DC44:
/* 8013DC44 00138B44  80 1D 00 0C */	lwz r0, 0xc(r29)
/* 8013DC48 00138B48  2C 00 00 05 */	cmpwi r0, 5
/* 8013DC4C 00138B4C  40 82 00 0C */	bne lbl_8013DC58
/* 8013DC50 00138B50  3B E0 00 04 */	li r31, 4
/* 8013DC54 00138B54  48 00 00 58 */	b lbl_8013DCAC
lbl_8013DC58:
/* 8013DC58 00138B58  3F E0 80 48 */	lis r31, __DVDStopMotorCommandBlock@ha
/* 8013DC5C 00138B5C  80 0D A0 18 */	lwz r0, executing-_SDA_BASE_(r13)
/* 8013DC60 00138B60  3B FF A0 30 */	addi r31, r31, __DVDStopMotorCommandBlock@l
/* 8013DC64 00138B64  7C 00 F8 40 */	cmplw r0, r31
/* 8013DC68 00138B68  40 82 00 40 */	bne lbl_8013DCA8
/* 8013DC6C 00138B6C  48 00 09 09 */	bl __DVDGetNextWaitingQueue
/* 8013DC70 00138B70  2C 03 00 00 */	cmpwi r3, 0
/* 8013DC74 00138B74  41 82 00 1C */	beq lbl_8013DC90
/* 8013DC78 00138B78  7C 1D 18 40 */	cmplw r29, r3
/* 8013DC7C 00138B7C  40 82 00 0C */	bne lbl_8013DC88
/* 8013DC80 00138B80  3B E0 00 01 */	li r31, 1
/* 8013DC84 00138B84  48 00 00 28 */	b lbl_8013DCAC
lbl_8013DC88:
/* 8013DC88 00138B88  83 FD 00 0C */	lwz r31, 0xc(r29)
/* 8013DC8C 00138B8C  48 00 00 20 */	b lbl_8013DCAC
lbl_8013DC90:
/* 8013DC90 00138B90  7C 1D F8 40 */	cmplw r29, r31
/* 8013DC94 00138B94  40 82 00 0C */	bne lbl_8013DCA0
/* 8013DC98 00138B98  3B E0 00 00 */	li r31, 0
/* 8013DC9C 00138B9C  48 00 00 10 */	b lbl_8013DCAC
lbl_8013DCA0:
/* 8013DCA0 00138BA0  83 FD 00 0C */	lwz r31, 0xc(r29)
/* 8013DCA4 00138BA4  48 00 00 08 */	b lbl_8013DCAC
lbl_8013DCA8:
/* 8013DCA8 00138BA8  83 FD 00 0C */	lwz r31, 0xc(r29)
lbl_8013DCAC:
/* 8013DCAC 00138BAC  7F C3 F3 78 */	mr r3, r30
/* 8013DCB0 00138BB0  4B FB 3C 39 */	bl OSRestoreInterrupts
/* 8013DCB4 00138BB4  7F E3 FB 78 */	mr r3, r31
/* 8013DCB8 00138BB8  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8013DCBC 00138BBC  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8013DCC0 00138BC0  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8013DCC4 00138BC4  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8013DCC8 00138BC8  7C 08 03 A6 */	mtlr r0
/* 8013DCCC 00138BCC  38 21 00 20 */	addi r1, r1, 0x20
/* 8013DCD0 00138BD0  4E 80 00 20 */	blr 

.global DVDGetDriveStatus
DVDGetDriveStatus:
/* 8013DCD4 00138BD4  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8013DCD8 00138BD8  7C 08 02 A6 */	mflr r0
/* 8013DCDC 00138BDC  90 01 00 14 */	stw r0, 0x14(r1)
/* 8013DCE0 00138BE0  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8013DCE4 00138BE4  93 C1 00 08 */	stw r30, 8(r1)
/* 8013DCE8 00138BE8  4B FB 3B D9 */	bl OSDisableInterrupts
/* 8013DCEC 00138BEC  80 0D 9F A4 */	lwz r0, FatalErrorFlag-_SDA_BASE_(r13)
/* 8013DCF0 00138BF0  7C 7F 1B 78 */	mr r31, r3
/* 8013DCF4 00138BF4  2C 00 00 00 */	cmpwi r0, 0
/* 8013DCF8 00138BF8  41 82 00 0C */	beq lbl_8013DD04
/* 8013DCFC 00138BFC  3B C0 FF FF */	li r30, -1
/* 8013DD00 00138C00  48 00 00 4C */	b lbl_8013DD4C
lbl_8013DD04:
/* 8013DD04 00138C04  80 0D 9F A0 */	lwz r0, PausingFlag-_SDA_BASE_(r13)
/* 8013DD08 00138C08  2C 00 00 00 */	cmpwi r0, 0
/* 8013DD0C 00138C0C  41 82 00 0C */	beq lbl_8013DD18
/* 8013DD10 00138C10  3B C0 00 08 */	li r30, 8
/* 8013DD14 00138C14  48 00 00 38 */	b lbl_8013DD4C
lbl_8013DD18:
/* 8013DD18 00138C18  80 6D A0 18 */	lwz r3, executing-_SDA_BASE_(r13)
/* 8013DD1C 00138C1C  2C 03 00 00 */	cmpwi r3, 0
/* 8013DD20 00138C20  40 82 00 0C */	bne lbl_8013DD2C
/* 8013DD24 00138C24  3B C0 00 00 */	li r30, 0
/* 8013DD28 00138C28  48 00 00 24 */	b lbl_8013DD4C
lbl_8013DD2C:
/* 8013DD2C 00138C2C  3C 80 80 47 */	lis r4, DummyCommandBlock@ha
/* 8013DD30 00138C30  38 84 54 E0 */	addi r4, r4, DummyCommandBlock@l
/* 8013DD34 00138C34  7C 03 20 40 */	cmplw r3, r4
/* 8013DD38 00138C38  40 82 00 0C */	bne lbl_8013DD44
/* 8013DD3C 00138C3C  38 60 00 00 */	li r3, 0
/* 8013DD40 00138C40  48 00 00 08 */	b lbl_8013DD48
lbl_8013DD44:
/* 8013DD44 00138C44  4B FF FE C9 */	bl DVDGetCommandBlockStatus
lbl_8013DD48:
/* 8013DD48 00138C48  7C 7E 1B 78 */	mr r30, r3
lbl_8013DD4C:
/* 8013DD4C 00138C4C  7F E3 FB 78 */	mr r3, r31
/* 8013DD50 00138C50  4B FB 3B 99 */	bl OSRestoreInterrupts
/* 8013DD54 00138C54  7F C3 F3 78 */	mr r3, r30
/* 8013DD58 00138C58  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8013DD5C 00138C5C  83 C1 00 08 */	lwz r30, 8(r1)
/* 8013DD60 00138C60  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8013DD64 00138C64  7C 08 03 A6 */	mtlr r0
/* 8013DD68 00138C68  38 21 00 10 */	addi r1, r1, 0x10
/* 8013DD6C 00138C6C  4E 80 00 20 */	blr 

.global DVDCancelAsync
DVDCancelAsync:
/* 8013DD70 00138C70  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8013DD74 00138C74  7C 08 02 A6 */	mflr r0
/* 8013DD78 00138C78  90 01 00 24 */	stw r0, 0x24(r1)
/* 8013DD7C 00138C7C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8013DD80 00138C80  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8013DD84 00138C84  7C 9E 23 78 */	mr r30, r4
/* 8013DD88 00138C88  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8013DD8C 00138C8C  7C 7D 1B 78 */	mr r29, r3
/* 8013DD90 00138C90  4B FB 3B 31 */	bl OSDisableInterrupts
/* 8013DD94 00138C94  80 9D 00 0C */	lwz r4, 0xc(r29)
/* 8013DD98 00138C98  7C 7F 1B 78 */	mr r31, r3
/* 8013DD9C 00138C9C  38 04 00 01 */	addi r0, r4, 1
/* 8013DDA0 00138CA0  28 00 00 0D */	cmplwi r0, 0xd
/* 8013DDA4 00138CA4  41 81 02 F8 */	bgt lbl_8013E09C
/* 8013DDA8 00138CA8  3C 80 80 3B */	lis r4, lbl_803B6080@ha
/* 8013DDAC 00138CAC  54 00 10 3A */	slwi r0, r0, 2
/* 8013DDB0 00138CB0  38 84 60 80 */	addi r4, r4, lbl_803B6080@l
/* 8013DDB4 00138CB4  7C 84 00 2E */	lwzx r4, r4, r0
/* 8013DDB8 00138CB8  7C 89 03 A6 */	mtctr r4
/* 8013DDBC 00138CBC  4E 80 04 20 */	bctr 
/* 8013DDC0 00138CC0  2C 1E 00 00 */	cmpwi r30, 0
/* 8013DDC4 00138CC4  41 82 02 D8 */	beq lbl_8013E09C
/* 8013DDC8 00138CC8  7F CC F3 78 */	mr r12, r30
/* 8013DDCC 00138CCC  7F A4 EB 78 */	mr r4, r29
/* 8013DDD0 00138CD0  38 60 00 00 */	li r3, 0
/* 8013DDD4 00138CD4  7D 89 03 A6 */	mtctr r12
/* 8013DDD8 00138CD8  4E 80 04 21 */	bctrl 
/* 8013DDDC 00138CDC  48 00 02 C0 */	b lbl_8013E09C
/* 8013DDE0 00138CE0  80 0D 9F A8 */	lwz r0, Canceling-_SDA_BASE_(r13)
/* 8013DDE4 00138CE4  2C 00 00 00 */	cmpwi r0, 0
/* 8013DDE8 00138CE8  41 82 00 10 */	beq lbl_8013DDF8
/* 8013DDEC 00138CEC  4B FB 3A FD */	bl OSRestoreInterrupts
/* 8013DDF0 00138CF0  38 60 00 00 */	li r3, 0
/* 8013DDF4 00138CF4  48 00 02 B4 */	b lbl_8013E0A8
lbl_8013DDF8:
/* 8013DDF8 00138CF8  38 00 00 01 */	li r0, 1
/* 8013DDFC 00138CFC  93 CD A0 08 */	stw r30, CancelCallback-_SDA_BASE_(r13)
/* 8013DE00 00138D00  90 0D 9F A8 */	stw r0, Canceling-_SDA_BASE_(r13)
/* 8013DE04 00138D04  80 1D 00 08 */	lwz r0, 8(r29)
/* 8013DE08 00138D08  28 00 00 04 */	cmplwi r0, 4
/* 8013DE0C 00138D0C  41 82 00 1C */	beq lbl_8013DE28
/* 8013DE10 00138D10  28 00 00 21 */	cmplwi r0, 0x21
/* 8013DE14 00138D14  41 82 00 14 */	beq lbl_8013DE28
/* 8013DE18 00138D18  28 00 00 22 */	cmplwi r0, 0x22
/* 8013DE1C 00138D1C  41 82 00 0C */	beq lbl_8013DE28
/* 8013DE20 00138D20  28 00 00 01 */	cmplwi r0, 1
/* 8013DE24 00138D24  40 82 02 78 */	bne lbl_8013E09C
lbl_8013DE28:
/* 8013DE28 00138D28  38 00 00 01 */	li r0, 1
/* 8013DE2C 00138D2C  90 0D 9F B8 */	stw r0, Breaking-_SDA_BASE_(r13)
/* 8013DE30 00138D30  48 00 02 6C */	b lbl_8013E09C
/* 8013DE34 00138D34  7F A3 EB 78 */	mr r3, r29
/* 8013DE38 00138D38  48 00 07 9D */	bl __DVDDequeueWaitingQueue
/* 8013DE3C 00138D3C  81 9D 00 28 */	lwz r12, 0x28(r29)
/* 8013DE40 00138D40  38 00 00 0A */	li r0, 0xa
/* 8013DE44 00138D44  90 1D 00 0C */	stw r0, 0xc(r29)
/* 8013DE48 00138D48  2C 0C 00 00 */	cmpwi r12, 0
/* 8013DE4C 00138D4C  41 82 00 14 */	beq lbl_8013DE60
/* 8013DE50 00138D50  7F A4 EB 78 */	mr r4, r29
/* 8013DE54 00138D54  38 60 FF FD */	li r3, -3
/* 8013DE58 00138D58  7D 89 03 A6 */	mtctr r12
/* 8013DE5C 00138D5C  4E 80 04 21 */	bctrl 
lbl_8013DE60:
/* 8013DE60 00138D60  2C 1E 00 00 */	cmpwi r30, 0
/* 8013DE64 00138D64  41 82 02 38 */	beq lbl_8013E09C
/* 8013DE68 00138D68  7F CC F3 78 */	mr r12, r30
/* 8013DE6C 00138D6C  7F A4 EB 78 */	mr r4, r29
/* 8013DE70 00138D70  38 60 00 00 */	li r3, 0
/* 8013DE74 00138D74  7D 89 03 A6 */	mtctr r12
/* 8013DE78 00138D78  4E 80 04 21 */	bctrl 
/* 8013DE7C 00138D7C  48 00 02 20 */	b lbl_8013E09C
/* 8013DE80 00138D80  80 1D 00 08 */	lwz r0, 8(r29)
/* 8013DE84 00138D84  28 00 00 25 */	cmplwi r0, 0x25
/* 8013DE88 00138D88  41 81 00 9C */	bgt lbl_8013DF24
/* 8013DE8C 00138D8C  3C 60 80 3B */	lis r3, lbl_803B5FE8@ha
/* 8013DE90 00138D90  54 00 10 3A */	slwi r0, r0, 2
/* 8013DE94 00138D94  38 63 5F E8 */	addi r3, r3, lbl_803B5FE8@l
/* 8013DE98 00138D98  7C 63 00 2E */	lwzx r3, r3, r0
/* 8013DE9C 00138D9C  7C 69 03 A6 */	mtctr r3
/* 8013DEA0 00138DA0  4E 80 04 20 */	bctr 
/* 8013DEA4 00138DA4  2C 1E 00 00 */	cmpwi r30, 0
/* 8013DEA8 00138DA8  41 82 01 F4 */	beq lbl_8013E09C
/* 8013DEAC 00138DAC  7F CC F3 78 */	mr r12, r30
/* 8013DEB0 00138DB0  7F A4 EB 78 */	mr r4, r29
/* 8013DEB4 00138DB4  38 60 00 00 */	li r3, 0
/* 8013DEB8 00138DB8  7D 89 03 A6 */	mtctr r12
/* 8013DEBC 00138DBC  4E 80 04 21 */	bctrl 
/* 8013DEC0 00138DC0  48 00 01 DC */	b lbl_8013E09C
/* 8013DEC4 00138DC4  80 0D 9B 88 */	lwz r0, __OSInIPL-_SDA_BASE_(r13)
/* 8013DEC8 00138DC8  2C 00 00 00 */	cmpwi r0, 0
/* 8013DECC 00138DCC  41 82 00 58 */	beq lbl_8013DF24
/* 8013DED0 00138DD0  3C 60 80 47 */	lis r3, DummyCommandBlock@ha
/* 8013DED4 00138DD4  38 00 00 0A */	li r0, 0xa
/* 8013DED8 00138DD8  38 63 54 E0 */	addi r3, r3, DummyCommandBlock@l
/* 8013DEDC 00138DDC  90 6D A0 18 */	stw r3, executing-_SDA_BASE_(r13)
/* 8013DEE0 00138DE0  81 9D 00 28 */	lwz r12, 0x28(r29)
/* 8013DEE4 00138DE4  90 1D 00 0C */	stw r0, 0xc(r29)
/* 8013DEE8 00138DE8  2C 0C 00 00 */	cmpwi r12, 0
/* 8013DEEC 00138DEC  41 82 00 14 */	beq lbl_8013DF00
/* 8013DEF0 00138DF0  7F A4 EB 78 */	mr r4, r29
/* 8013DEF4 00138DF4  38 60 FF FD */	li r3, -3
/* 8013DEF8 00138DF8  7D 89 03 A6 */	mtctr r12
/* 8013DEFC 00138DFC  4E 80 04 21 */	bctrl 
lbl_8013DF00:
/* 8013DF00 00138E00  2C 1E 00 00 */	cmpwi r30, 0
/* 8013DF04 00138E04  41 82 00 18 */	beq lbl_8013DF1C
/* 8013DF08 00138E08  7F CC F3 78 */	mr r12, r30
/* 8013DF0C 00138E0C  7F A4 EB 78 */	mr r4, r29
/* 8013DF10 00138E10  38 60 00 00 */	li r3, 0
/* 8013DF14 00138E14  7D 89 03 A6 */	mtctr r12
/* 8013DF18 00138E18  4E 80 04 21 */	bctrl 
lbl_8013DF1C:
/* 8013DF1C 00138E1C  4B FF EA D1 */	bl stateReady
/* 8013DF20 00138E20  48 00 01 7C */	b lbl_8013E09C
lbl_8013DF24:
/* 8013DF24 00138E24  80 0D 9F A8 */	lwz r0, Canceling-_SDA_BASE_(r13)
/* 8013DF28 00138E28  2C 00 00 00 */	cmpwi r0, 0
/* 8013DF2C 00138E2C  41 82 00 14 */	beq lbl_8013DF40
/* 8013DF30 00138E30  7F E3 FB 78 */	mr r3, r31
/* 8013DF34 00138E34  4B FB 39 B5 */	bl OSRestoreInterrupts
/* 8013DF38 00138E38  38 60 00 00 */	li r3, 0
/* 8013DF3C 00138E3C  48 00 01 6C */	b lbl_8013E0A8
lbl_8013DF40:
/* 8013DF40 00138E40  38 00 00 01 */	li r0, 1
/* 8013DF44 00138E44  93 CD A0 08 */	stw r30, CancelCallback-_SDA_BASE_(r13)
/* 8013DF48 00138E48  90 0D 9F A8 */	stw r0, Canceling-_SDA_BASE_(r13)
/* 8013DF4C 00138E4C  48 00 01 50 */	b lbl_8013E09C
/* 8013DF50 00138E50  80 0D 9F C0 */	lwz r0, WaitingForCoverClose-_SDA_BASE_(r13)
/* 8013DF54 00138E54  2C 00 00 00 */	cmpwi r0, 0
/* 8013DF58 00138E58  40 82 00 1C */	bne lbl_8013DF74
/* 8013DF5C 00138E5C  80 0D 9F BC */	lwz r0, WaitingForCoverOpen-_SDA_BASE_(r13)
/* 8013DF60 00138E60  2C 00 00 00 */	cmpwi r0, 0
/* 8013DF64 00138E64  40 82 00 10 */	bne lbl_8013DF74
/* 8013DF68 00138E68  4B FB 39 81 */	bl OSRestoreInterrupts
/* 8013DF6C 00138E6C  38 60 00 00 */	li r3, 0
/* 8013DF70 00138E70  48 00 01 38 */	b lbl_8013E0A8
lbl_8013DF74:
/* 8013DF74 00138E74  80 0D 9F BC */	lwz r0, WaitingForCoverOpen-_SDA_BASE_(r13)
/* 8013DF78 00138E78  2C 00 00 00 */	cmpwi r0, 0
/* 8013DF7C 00138E7C  41 82 00 18 */	beq lbl_8013DF94
/* 8013DF80 00138E80  3C 60 80 47 */	lis r3, CoverAlarm@ha
/* 8013DF84 00138E84  38 63 55 40 */	addi r3, r3, CoverAlarm@l
/* 8013DF88 00138E88  4B FA F4 E1 */	bl OSCancelAlarm
/* 8013DF8C 00138E8C  38 00 00 00 */	li r0, 0
/* 8013DF90 00138E90  90 0D 9F BC */	stw r0, WaitingForCoverOpen-_SDA_BASE_(r13)
lbl_8013DF94:
/* 8013DF94 00138E94  80 1D 00 0C */	lwz r0, 0xc(r29)
/* 8013DF98 00138E98  2C 00 00 04 */	cmpwi r0, 4
/* 8013DF9C 00138E9C  40 82 00 0C */	bne lbl_8013DFA8
/* 8013DFA0 00138EA0  38 00 00 03 */	li r0, 3
/* 8013DFA4 00138EA4  90 0D 9F AC */	stw r0, ResumeFromHere-_SDA_BASE_(r13)
lbl_8013DFA8:
/* 8013DFA8 00138EA8  80 1D 00 0C */	lwz r0, 0xc(r29)
/* 8013DFAC 00138EAC  2C 00 00 05 */	cmpwi r0, 5
/* 8013DFB0 00138EB0  40 82 00 0C */	bne lbl_8013DFBC
/* 8013DFB4 00138EB4  38 00 00 04 */	li r0, 4
/* 8013DFB8 00138EB8  90 0D 9F AC */	stw r0, ResumeFromHere-_SDA_BASE_(r13)
lbl_8013DFBC:
/* 8013DFBC 00138EBC  80 1D 00 0C */	lwz r0, 0xc(r29)
/* 8013DFC0 00138EC0  2C 00 00 06 */	cmpwi r0, 6
/* 8013DFC4 00138EC4  40 82 00 0C */	bne lbl_8013DFD0
/* 8013DFC8 00138EC8  38 00 00 01 */	li r0, 1
/* 8013DFCC 00138ECC  90 0D 9F AC */	stw r0, ResumeFromHere-_SDA_BASE_(r13)
lbl_8013DFD0:
/* 8013DFD0 00138ED0  80 1D 00 0C */	lwz r0, 0xc(r29)
/* 8013DFD4 00138ED4  2C 00 00 0B */	cmpwi r0, 0xb
/* 8013DFD8 00138ED8  40 82 00 0C */	bne lbl_8013DFE4
/* 8013DFDC 00138EDC  38 00 00 02 */	li r0, 2
/* 8013DFE0 00138EE0  90 0D 9F AC */	stw r0, ResumeFromHere-_SDA_BASE_(r13)
lbl_8013DFE4:
/* 8013DFE4 00138EE4  80 1D 00 0C */	lwz r0, 0xc(r29)
/* 8013DFE8 00138EE8  2C 00 00 07 */	cmpwi r0, 7
/* 8013DFEC 00138EEC  40 82 00 0C */	bne lbl_8013DFF8
/* 8013DFF0 00138EF0  38 00 00 07 */	li r0, 7
/* 8013DFF4 00138EF4  90 0D 9F AC */	stw r0, ResumeFromHere-_SDA_BASE_(r13)
lbl_8013DFF8:
/* 8013DFF8 00138EF8  3C 60 80 47 */	lis r3, DummyCommandBlock@ha
/* 8013DFFC 00138EFC  38 00 00 0A */	li r0, 0xa
/* 8013E000 00138F00  38 63 54 E0 */	addi r3, r3, DummyCommandBlock@l
/* 8013E004 00138F04  90 6D A0 18 */	stw r3, executing-_SDA_BASE_(r13)
/* 8013E008 00138F08  81 9D 00 28 */	lwz r12, 0x28(r29)
/* 8013E00C 00138F0C  90 1D 00 0C */	stw r0, 0xc(r29)
/* 8013E010 00138F10  2C 0C 00 00 */	cmpwi r12, 0
/* 8013E014 00138F14  41 82 00 14 */	beq lbl_8013E028
/* 8013E018 00138F18  7F A4 EB 78 */	mr r4, r29
/* 8013E01C 00138F1C  38 60 FF FD */	li r3, -3
/* 8013E020 00138F20  7D 89 03 A6 */	mtctr r12
/* 8013E024 00138F24  4E 80 04 21 */	bctrl 
lbl_8013E028:
/* 8013E028 00138F28  2C 1E 00 00 */	cmpwi r30, 0
/* 8013E02C 00138F2C  41 82 00 18 */	beq lbl_8013E044
/* 8013E030 00138F30  7F CC F3 78 */	mr r12, r30
/* 8013E034 00138F34  7F A4 EB 78 */	mr r4, r29
/* 8013E038 00138F38  38 60 00 00 */	li r3, 0
/* 8013E03C 00138F3C  7D 89 03 A6 */	mtctr r12
/* 8013E040 00138F40  4E 80 04 21 */	bctrl 
lbl_8013E044:
/* 8013E044 00138F44  4B FF E9 A9 */	bl stateReady
/* 8013E048 00138F48  48 00 00 54 */	b lbl_8013E09C
/* 8013E04C 00138F4C  3C 60 80 47 */	lis r3, DummyCommandBlock@ha
/* 8013E050 00138F50  38 00 00 0A */	li r0, 0xa
/* 8013E054 00138F54  38 63 54 E0 */	addi r3, r3, DummyCommandBlock@l
/* 8013E058 00138F58  90 6D A0 18 */	stw r3, executing-_SDA_BASE_(r13)
/* 8013E05C 00138F5C  81 9D 00 28 */	lwz r12, 0x28(r29)
/* 8013E060 00138F60  90 1D 00 0C */	stw r0, 0xc(r29)
/* 8013E064 00138F64  2C 0C 00 00 */	cmpwi r12, 0
/* 8013E068 00138F68  41 82 00 14 */	beq lbl_8013E07C
/* 8013E06C 00138F6C  7F A4 EB 78 */	mr r4, r29
/* 8013E070 00138F70  38 60 FF FD */	li r3, -3
/* 8013E074 00138F74  7D 89 03 A6 */	mtctr r12
/* 8013E078 00138F78  4E 80 04 21 */	bctrl 
lbl_8013E07C:
/* 8013E07C 00138F7C  2C 1E 00 00 */	cmpwi r30, 0
/* 8013E080 00138F80  41 82 00 18 */	beq lbl_8013E098
/* 8013E084 00138F84  7F CC F3 78 */	mr r12, r30
/* 8013E088 00138F88  7F A4 EB 78 */	mr r4, r29
/* 8013E08C 00138F8C  38 60 00 00 */	li r3, 0
/* 8013E090 00138F90  7D 89 03 A6 */	mtctr r12
/* 8013E094 00138F94  4E 80 04 21 */	bctrl 
lbl_8013E098:
/* 8013E098 00138F98  4B FF E9 55 */	bl stateReady
lbl_8013E09C:
/* 8013E09C 00138F9C  7F E3 FB 78 */	mr r3, r31
/* 8013E0A0 00138FA0  4B FB 38 49 */	bl OSRestoreInterrupts
/* 8013E0A4 00138FA4  38 60 00 01 */	li r3, 1
lbl_8013E0A8:
/* 8013E0A8 00138FA8  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8013E0AC 00138FAC  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8013E0B0 00138FB0  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8013E0B4 00138FB4  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8013E0B8 00138FB8  7C 08 03 A6 */	mtlr r0
/* 8013E0BC 00138FBC  38 21 00 20 */	addi r1, r1, 0x20
/* 8013E0C0 00138FC0  4E 80 00 20 */	blr 

.global DVDCancel
DVDCancel:
/* 8013E0C4 00138FC4  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8013E0C8 00138FC8  7C 08 02 A6 */	mflr r0
/* 8013E0CC 00138FCC  3C 80 80 14 */	lis r4, cbForCancelSync@ha
/* 8013E0D0 00138FD0  90 01 00 14 */	stw r0, 0x14(r1)
/* 8013E0D4 00138FD4  38 84 E1 90 */	addi r4, r4, cbForCancelSync@l
/* 8013E0D8 00138FD8  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8013E0DC 00138FDC  93 C1 00 08 */	stw r30, 8(r1)
/* 8013E0E0 00138FE0  7C 7E 1B 78 */	mr r30, r3
/* 8013E0E4 00138FE4  4B FF FC 8D */	bl DVDCancelAsync
/* 8013E0E8 00138FE8  2C 03 00 00 */	cmpwi r3, 0
/* 8013E0EC 00138FEC  40 82 00 0C */	bne lbl_8013E0F8
/* 8013E0F0 00138FF0  38 60 FF FF */	li r3, -1
/* 8013E0F4 00138FF4  48 00 00 84 */	b lbl_8013E178
lbl_8013E0F8:
/* 8013E0F8 00138FF8  4B FB 37 C9 */	bl OSDisableInterrupts
/* 8013E0FC 00138FFC  7C 7F 1B 78 */	mr r31, r3
lbl_8013E100:
/* 8013E100 00139000  80 1E 00 0C */	lwz r0, 0xc(r30)
/* 8013E104 00139004  2C 00 00 00 */	cmpwi r0, 0
/* 8013E108 00139008  41 82 00 64 */	beq lbl_8013E16C
/* 8013E10C 0013900C  2C 00 FF FF */	cmpwi r0, -1
/* 8013E110 00139010  41 82 00 5C */	beq lbl_8013E16C
/* 8013E114 00139014  2C 00 00 0A */	cmpwi r0, 0xa
/* 8013E118 00139018  41 82 00 54 */	beq lbl_8013E16C
/* 8013E11C 0013901C  2C 00 00 03 */	cmpwi r0, 3
/* 8013E120 00139020  40 82 00 40 */	bne lbl_8013E160
/* 8013E124 00139024  80 1E 00 08 */	lwz r0, 8(r30)
/* 8013E128 00139028  28 00 00 04 */	cmplwi r0, 4
/* 8013E12C 0013902C  41 82 00 40 */	beq lbl_8013E16C
/* 8013E130 00139030  28 00 00 05 */	cmplwi r0, 5
/* 8013E134 00139034  41 82 00 38 */	beq lbl_8013E16C
/* 8013E138 00139038  28 00 00 0D */	cmplwi r0, 0xd
/* 8013E13C 0013903C  41 82 00 30 */	beq lbl_8013E16C
/* 8013E140 00139040  28 00 00 21 */	cmplwi r0, 0x21
/* 8013E144 00139044  41 82 00 28 */	beq lbl_8013E16C
/* 8013E148 00139048  28 00 00 22 */	cmplwi r0, 0x22
/* 8013E14C 0013904C  41 82 00 20 */	beq lbl_8013E16C
/* 8013E150 00139050  28 00 00 0F */	cmplwi r0, 0xf
/* 8013E154 00139054  41 82 00 18 */	beq lbl_8013E16C
/* 8013E158 00139058  28 00 00 25 */	cmplwi r0, 0x25
/* 8013E15C 0013905C  41 82 00 10 */	beq lbl_8013E16C
lbl_8013E160:
/* 8013E160 00139060  38 6D 9F 80 */	addi r3, r13, __DVDThreadQueue-_SDA_BASE_
/* 8013E164 00139064  4B FB 70 FD */	bl OSSleepThread
/* 8013E168 00139068  4B FF FF 98 */	b lbl_8013E100
lbl_8013E16C:
/* 8013E16C 0013906C  7F E3 FB 78 */	mr r3, r31
/* 8013E170 00139070  4B FB 37 79 */	bl OSRestoreInterrupts
/* 8013E174 00139074  38 60 00 00 */	li r3, 0
lbl_8013E178:
/* 8013E178 00139078  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8013E17C 0013907C  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8013E180 00139080  83 C1 00 08 */	lwz r30, 8(r1)
/* 8013E184 00139084  7C 08 03 A6 */	mtlr r0
/* 8013E188 00139088  38 21 00 10 */	addi r1, r1, 0x10
/* 8013E18C 0013908C  4E 80 00 20 */	blr 

.global cbForCancelSync
cbForCancelSync:
/* 8013E190 00139090  38 6D 9F 80 */	addi r3, r13, __DVDThreadQueue-_SDA_BASE_
/* 8013E194 00139094  4B FB 71 B8 */	b OSWakeupThread

.global DVDGetCurrentDiskID
DVDGetCurrentDiskID:
/* 8013E198 00139098  3C 60 80 00 */	lis r3, 0x8000
/* 8013E19C 0013909C  4E 80 00 20 */	blr 

.global __BS2DVDLowCallback
__BS2DVDLowCallback:
/* 8013E1A0 001390A0  90 6D 9F D8 */	stw r3, __BS2DVDLowIntType-_SDA_BASE_(r13)
/* 8013E1A4 001390A4  4E 80 00 20 */	blr 

.global __DVDGetCoverStatus
__DVDGetCoverStatus:
/* 8013E1A8 001390A8  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8013E1AC 001390AC  7C 08 02 A6 */	mflr r0
/* 8013E1B0 001390B0  3C 60 80 14 */	lis r3, __BS2DVDLowCallback@ha
/* 8013E1B4 001390B4  90 01 00 14 */	stw r0, 0x14(r1)
/* 8013E1B8 001390B8  38 00 00 00 */	li r0, 0
/* 8013E1BC 001390BC  38 63 E1 A0 */	addi r3, r3, __BS2DVDLowCallback@l
/* 8013E1C0 001390C0  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8013E1C4 001390C4  90 0D 9F D8 */	stw r0, __BS2DVDLowIntType-_SDA_BASE_(r13)
/* 8013E1C8 001390C8  48 00 20 9D */	bl DVDLowPrepareCoverRegister
lbl_8013E1CC:
/* 8013E1CC 001390CC  80 0D 9F D8 */	lwz r0, __BS2DVDLowIntType-_SDA_BASE_(r13)
/* 8013E1D0 001390D0  2C 00 00 00 */	cmpwi r0, 0
/* 8013E1D4 001390D4  41 82 FF F8 */	beq lbl_8013E1CC
/* 8013E1D8 001390D8  80 0D 9F D8 */	lwz r0, __BS2DVDLowIntType-_SDA_BASE_(r13)
/* 8013E1DC 001390DC  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 8013E1E0 001390E0  40 82 00 0C */	bne lbl_8013E1EC
/* 8013E1E4 001390E4  38 60 00 00 */	li r3, 0
/* 8013E1E8 001390E8  48 00 00 74 */	b lbl_8013E25C
lbl_8013E1EC:
/* 8013E1EC 001390EC  48 00 20 69 */	bl DVDLowGetCoverRegister
/* 8013E1F0 001390F0  7C 7F 1B 78 */	mr r31, r3
/* 8013E1F4 001390F4  4B FB 74 31 */	bl __OSGetSystemTime
/* 8013E1F8 001390F8  3C C0 80 00 */	lis r6, 0x800000F8@ha
/* 8013E1FC 001390FC  3C A0 10 62 */	lis r5, 0x10624DD3@ha
/* 8013E200 00139100  80 C6 00 F8 */	lwz r6, 0x800000F8@l(r6)
/* 8013E204 00139104  38 E5 4D D3 */	addi r7, r5, 0x10624DD3@l
/* 8013E208 00139108  81 0D 9F F0 */	lwz r8, LastResetEnd-_SDA_BASE_(r13)
/* 8013E20C 0013910C  38 00 00 00 */	li r0, 0
/* 8013E210 00139110  54 C5 F0 BE */	srwi r5, r6, 2
/* 8013E214 00139114  81 2D 9F F4 */	lwz r9, (LastResetEnd+0x4)-_SDA_BASE_(r13)
/* 8013E218 00139118  7C C7 28 16 */	mulhwu r6, r7, r5
/* 8013E21C 0013911C  7C 89 20 10 */	subfc r4, r9, r4
/* 8013E220 00139120  6C 05 80 00 */	xoris r5, r0, 0x8000
/* 8013E224 00139124  7C 08 19 10 */	subfe r0, r8, r3
/* 8013E228 00139128  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 8013E22C 0013912C  54 C3 D1 BE */	srwi r3, r6, 6
/* 8013E230 00139130  1C 63 00 64 */	mulli r3, r3, 0x64
/* 8013E234 00139134  7C 63 20 10 */	subfc r3, r3, r4
/* 8013E238 00139138  7C A5 01 10 */	subfe r5, r5, r0
/* 8013E23C 0013913C  7C A0 01 10 */	subfe r5, r0, r0
/* 8013E240 00139140  7C A5 00 D1 */	neg. r5, r5
/* 8013E244 00139144  41 82 00 0C */	beq lbl_8013E250
/* 8013E248 00139148  38 60 00 00 */	li r3, 0
/* 8013E24C 0013914C  48 00 00 10 */	b lbl_8013E25C
lbl_8013E250:
/* 8013E250 00139150  57 E0 07 FE */	clrlwi r0, r31, 0x1f
/* 8013E254 00139154  7C 60 00 D0 */	neg r3, r0
/* 8013E258 00139158  38 63 00 02 */	addi r3, r3, 2
lbl_8013E25C:
/* 8013E25C 0013915C  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8013E260 00139160  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8013E264 00139164  7C 08 03 A6 */	mtlr r0
/* 8013E268 00139168  38 21 00 10 */	addi r1, r1, 0x10
/* 8013E26C 0013916C  4E 80 00 20 */	blr 

.global Callback
Callback:
/* 8013E270 00139170  38 00 00 01 */	li r0, 1
/* 8013E274 00139174  90 0D 9F DC */	stw r0, Prepared-_SDA_BASE_(r13)
/* 8013E278 00139178  4E 80 00 20 */	blr 

.global __DVDPrepareReset
__DVDPrepareReset:
/* 8013E27C 0013917C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8013E280 00139180  7C 08 02 A6 */	mflr r0
/* 8013E284 00139184  90 01 00 24 */	stw r0, 0x24(r1)
/* 8013E288 00139188  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8013E28C 0013918C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8013E290 00139190  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8013E294 00139194  4B FB 36 2D */	bl OSDisableInterrupts
/* 8013E298 00139198  3B E0 00 00 */	li r31, 0
/* 8013E29C 0013919C  93 ED 9F DC */	stw r31, Prepared-_SDA_BASE_(r13)
/* 8013E2A0 001391A0  4B FB 36 21 */	bl OSDisableInterrupts
/* 8013E2A4 001391A4  7C 7D 1B 78 */	mr r29, r3
/* 8013E2A8 001391A8  48 00 01 35 */	bl __DVDClearWaitingQueue
/* 8013E2AC 001391AC  80 0D 9F A8 */	lwz r0, Canceling-_SDA_BASE_(r13)
/* 8013E2B0 001391B0  2C 00 00 00 */	cmpwi r0, 0
/* 8013E2B4 001391B4  41 82 00 14 */	beq lbl_8013E2C8
/* 8013E2B8 001391B8  3C 60 80 14 */	lis r3, Callback@ha
/* 8013E2BC 001391BC  38 63 E2 70 */	addi r3, r3, Callback@l
/* 8013E2C0 001391C0  90 6D A0 08 */	stw r3, CancelCallback-_SDA_BASE_(r13)
/* 8013E2C4 001391C4  48 00 00 B8 */	b lbl_8013E37C
lbl_8013E2C8:
/* 8013E2C8 001391C8  80 6D A0 18 */	lwz r3, executing-_SDA_BASE_(r13)
/* 8013E2CC 001391CC  2C 03 00 00 */	cmpwi r3, 0
/* 8013E2D0 001391D0  41 82 00 08 */	beq lbl_8013E2D8
/* 8013E2D4 001391D4  93 E3 00 28 */	stw r31, 0x28(r3)
lbl_8013E2D8:
/* 8013E2D8 001391D8  4B FB 35 E9 */	bl OSDisableInterrupts
/* 8013E2DC 001391DC  7C 7F 1B 78 */	mr r31, r3
/* 8013E2E0 001391E0  4B FB 35 E1 */	bl OSDisableInterrupts
/* 8013E2E4 001391E4  80 0D A0 18 */	lwz r0, executing-_SDA_BASE_(r13)
/* 8013E2E8 001391E8  38 80 00 01 */	li r4, 1
/* 8013E2EC 001391EC  90 8D 9F 9C */	stw r4, PauseFlag-_SDA_BASE_(r13)
/* 8013E2F0 001391F0  2C 00 00 00 */	cmpwi r0, 0
/* 8013E2F4 001391F4  40 82 00 08 */	bne lbl_8013E2FC
/* 8013E2F8 001391F8  90 8D 9F A0 */	stw r4, PausingFlag-_SDA_BASE_(r13)
lbl_8013E2FC:
/* 8013E2FC 001391FC  4B FB 35 ED */	bl OSRestoreInterrupts
/* 8013E300 00139200  48 00 00 0C */	b lbl_8013E30C
lbl_8013E304:
/* 8013E304 00139204  38 80 00 00 */	li r4, 0
/* 8013E308 00139208  4B FF FA 69 */	bl DVDCancelAsync
lbl_8013E30C:
/* 8013E30C 0013920C  48 00 01 71 */	bl __DVDPopWaitingQueue
/* 8013E310 00139210  2C 03 00 00 */	cmpwi r3, 0
/* 8013E314 00139214  40 82 FF F0 */	bne lbl_8013E304
/* 8013E318 00139218  80 6D A0 18 */	lwz r3, executing-_SDA_BASE_(r13)
/* 8013E31C 0013921C  2C 03 00 00 */	cmpwi r3, 0
/* 8013E320 00139220  41 82 00 14 */	beq lbl_8013E334
/* 8013E324 00139224  3C 80 80 14 */	lis r4, Callback@ha
/* 8013E328 00139228  38 84 E2 70 */	addi r4, r4, Callback@l
/* 8013E32C 0013922C  4B FF FA 45 */	bl DVDCancelAsync
/* 8013E330 00139230  48 00 00 18 */	b lbl_8013E348
lbl_8013E334:
/* 8013E334 00139234  3C 00 80 14 */	lis r0, 0x8014
/* 8013E338 00139238  34 00 E2 70 */	addic. r0, r0, -7568
/* 8013E33C 0013923C  41 82 00 0C */	beq lbl_8013E348
/* 8013E340 00139240  38 00 00 01 */	li r0, 1
/* 8013E344 00139244  90 0D 9F DC */	stw r0, Prepared-_SDA_BASE_(r13)
lbl_8013E348:
/* 8013E348 00139248  4B FB 35 79 */	bl OSDisableInterrupts
/* 8013E34C 0013924C  38 80 00 00 */	li r4, 0
/* 8013E350 00139250  7C 7E 1B 78 */	mr r30, r3
/* 8013E354 00139254  90 8D 9F 9C */	stw r4, PauseFlag-_SDA_BASE_(r13)
/* 8013E358 00139258  80 0D 9F A0 */	lwz r0, PausingFlag-_SDA_BASE_(r13)
/* 8013E35C 0013925C  2C 00 00 00 */	cmpwi r0, 0
/* 8013E360 00139260  41 82 00 0C */	beq lbl_8013E36C
/* 8013E364 00139264  90 8D 9F A0 */	stw r4, PausingFlag-_SDA_BASE_(r13)
/* 8013E368 00139268  4B FF E6 85 */	bl stateReady
lbl_8013E36C:
/* 8013E36C 0013926C  7F C3 F3 78 */	mr r3, r30
/* 8013E370 00139270  4B FB 35 79 */	bl OSRestoreInterrupts
/* 8013E374 00139274  7F E3 FB 78 */	mr r3, r31
/* 8013E378 00139278  4B FB 35 71 */	bl OSRestoreInterrupts
lbl_8013E37C:
/* 8013E37C 0013927C  7F A3 EB 78 */	mr r3, r29
/* 8013E380 00139280  4B FB 35 69 */	bl OSRestoreInterrupts
/* 8013E384 00139284  4B FB 35 51 */	bl OSEnableInterrupts
lbl_8013E388:
/* 8013E388 00139288  80 0D 9F DC */	lwz r0, Prepared-_SDA_BASE_(r13)
/* 8013E38C 0013928C  2C 00 00 01 */	cmpwi r0, 1
/* 8013E390 00139290  40 82 FF F8 */	bne lbl_8013E388
/* 8013E394 00139294  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8013E398 00139298  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8013E39C 0013929C  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8013E3A0 001392A0  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8013E3A4 001392A4  7C 08 03 A6 */	mtlr r0
/* 8013E3A8 001392A8  38 21 00 20 */	addi r1, r1, 0x20
/* 8013E3AC 001392AC  4E 80 00 20 */	blr 

.global __DVDTestAlarm
__DVDTestAlarm:
/* 8013E3B0 001392B0  3C 80 80 48 */	lis r4, ResetAlarm@ha
/* 8013E3B4 001392B4  38 84 A0 00 */	addi r4, r4, ResetAlarm@l
/* 8013E3B8 001392B8  7C 03 20 40 */	cmplw r3, r4
/* 8013E3BC 001392BC  40 82 00 0C */	bne lbl_8013E3C8
/* 8013E3C0 001392C0  38 60 00 01 */	li r3, 1
/* 8013E3C4 001392C4  4E 80 00 20 */	blr 
lbl_8013E3C8:
/* 8013E3C8 001392C8  48 00 21 84 */	b __DVDLowTestAlarm
/* 8013E3CC 001392CC  4E 80 00 20 */	blr 

.global __DVDStopMotorAsync
__DVDStopMotorAsync:
/* 8013E3D0 001392D0  38 60 00 01 */	li r3, 1
/* 8013E3D4 001392D4  4E 80 00 20 */	blr 

.global __DVDRestartMotor
__DVDRestartMotor:
/* 8013E3D8 001392D8  4E 80 00 20 */	blr 
