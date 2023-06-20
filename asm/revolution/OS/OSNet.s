.include "macros.inc"

.section .data, "wa"
.balign 0x8
.global strings_803A9248
strings_803A9248:
    .string "Failed to register network shutdown function. %d\n"
    .balign 4
    .string "Failed to suspend the WiiConnect24 scheduler. %d\n"
    .balign 4
    .string "Failed to synchronize time with network resource managers. %d\n"
    .balign 4
    .string "NWC24iPrepareShutdown"
    .balign 4
    .string "/dev/net/kd/request"
    .balign 4
    .string "NWC24SuspendScheduler"
    .balign 4
    .string "NWC24ResumeScheduler"
    .balign 4
    .string "NWC24iRequestShutdown"
    .balign 4
    .string "NWC24Shutdown_: Give up!\n"
    .balign 4
    .string "NWC24iSetRtcCounter_"
    .balign 4
    .string "/dev/net/kd/time"
    .balign 4

.section .text, "ax"
.global __OSInitNet
__OSInitNet:
/* 800F6EAC 000F1DAC  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800F6EB0 000F1DB0  7C 08 02 A6 */	mflr r0
/* 800F6EB4 000F1DB4  90 01 00 24 */	stw r0, 0x24(r1)
/* 800F6EB8 000F1DB8  38 61 00 08 */	addi r3, r1, 8
/* 800F6EBC 000F1DBC  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800F6EC0 000F1DC0  3F E0 80 3B */	lis r31, strings_803A9248@ha
/* 800F6EC4 000F1DC4  3B FF 92 48 */	addi r31, r31, strings_803A9248@l
/* 800F6EC8 000F1DC8  4B FF 4F E9 */	bl __OSGetIOSRev
/* 800F6ECC 000F1DCC  88 01 00 09 */	lbz r0, 9(r1)
/* 800F6ED0 000F1DD0  28 00 00 04 */	cmplwi r0, 4
/* 800F6ED4 000F1DD4  40 81 00 68 */	ble lbl_800F6F3C
/* 800F6ED8 000F1DD8  28 00 00 09 */	cmplwi r0, 9
/* 800F6EDC 000F1DDC  40 82 00 08 */	bne lbl_800F6EE4
/* 800F6EE0 000F1DE0  48 00 00 5C */	b lbl_800F6F3C
lbl_800F6EE4:
/* 800F6EE4 000F1DE4  48 05 3D E9 */	bl func_8014ACCC
/* 800F6EE8 000F1DE8  2C 03 00 00 */	cmpwi r3, 0
/* 800F6EEC 000F1DEC  41 82 00 34 */	beq lbl_800F6F20
/* 800F6EF0 000F1DF0  40 80 00 14 */	bge lbl_800F6F04
/* 800F6EF4 000F1DF4  7C 64 1B 78 */	mr r4, r3
/* 800F6EF8 000F1DF8  38 7F 00 00 */	addi r3, r31, 0
/* 800F6EFC 000F1DFC  4C C6 31 82 */	crclr 6
/* 800F6F00 000F1E00  48 08 D0 19 */	bl OSReport
lbl_800F6F04:
/* 800F6F04 000F1E04  48 05 21 65 */	bl func_80149068
/* 800F6F08 000F1E08  2C 03 00 00 */	cmpwi r3, 0
/* 800F6F0C 000F1E0C  40 80 00 14 */	bge lbl_800F6F20
/* 800F6F10 000F1E10  7C 64 1B 78 */	mr r4, r3
/* 800F6F14 000F1E14  38 7F 00 34 */	addi r3, r31, 0x34
/* 800F6F18 000F1E18  4C C6 31 82 */	crclr 6
/* 800F6F1C 000F1E1C  48 08 CF FD */	bl OSReport
lbl_800F6F20:
/* 800F6F20 000F1E20  48 05 36 79 */	bl func_8014A598
/* 800F6F24 000F1E24  2C 03 00 00 */	cmpwi r3, 0
/* 800F6F28 000F1E28  41 82 00 14 */	beq lbl_800F6F3C
/* 800F6F2C 000F1E2C  7C 64 1B 78 */	mr r4, r3
/* 800F6F30 000F1E30  38 7F 00 68 */	addi r3, r31, 0x68
/* 800F6F34 000F1E34  4C C6 31 82 */	crclr 6
/* 800F6F38 000F1E38  48 08 CF E1 */	bl OSReport
lbl_800F6F3C:
/* 800F6F3C 000F1E3C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800F6F40 000F1E40  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800F6F44 000F1E44  7C 08 03 A6 */	mtlr r0
/* 800F6F48 000F1E48  38 21 00 20 */	addi r1, r1, 0x20
/* 800F6F4C 000F1E4C  4E 80 00 20 */	blr 
