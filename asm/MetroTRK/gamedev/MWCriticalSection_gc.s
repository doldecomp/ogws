.include "macros.inc"

.section .text, "ax"
.global MWExitCriticalSection
MWExitCriticalSection:
/* 800C67B8 000C16B8  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800C67BC 000C16BC  7C 08 02 A6 */	mflr r0
/* 800C67C0 000C16C0  90 01 00 14 */	stw r0, 0x14(r1)
/* 800C67C4 000C16C4  80 63 00 00 */	lwz r3, 0(r3)
/* 800C67C8 000C16C8  48 02 B1 21 */	bl OSRestoreInterrupts
/* 800C67CC 000C16CC  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800C67D0 000C16D0  7C 08 03 A6 */	mtlr r0
/* 800C67D4 000C16D4  38 21 00 10 */	addi r1, r1, 0x10
/* 800C67D8 000C16D8  4E 80 00 20 */	blr 

.global MWEnterCriticalSection
MWEnterCriticalSection:
/* 800C67DC 000C16DC  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800C67E0 000C16E0  7C 08 02 A6 */	mflr r0
/* 800C67E4 000C16E4  90 01 00 14 */	stw r0, 0x14(r1)
/* 800C67E8 000C16E8  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800C67EC 000C16EC  7C 7F 1B 78 */	mr r31, r3
/* 800C67F0 000C16F0  48 02 B0 D1 */	bl OSDisableInterrupts
/* 800C67F4 000C16F4  90 7F 00 00 */	stw r3, 0(r31)
/* 800C67F8 000C16F8  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800C67FC 000C16FC  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 800C6800 000C1700  7C 08 03 A6 */	mtlr r0
/* 800C6804 000C1704  38 21 00 10 */	addi r1, r1, 0x10
/* 800C6808 000C1708  4E 80 00 20 */	blr 

.global MWInitializeCriticalSection
MWInitializeCriticalSection:
/* 800C680C 000C170C  4E 80 00 20 */	blr 
