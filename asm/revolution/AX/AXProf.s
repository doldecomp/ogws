.include "macros.inc"

.section .sbss, "wa"
.balign 0x8
__AXProfileInitialized:
	.skip 0x4
__AXCurrentProfile:
	.skip 0x4
__AXMaxProfiles:
	.skip 0x4
__AXProfile:
	.skip 0x4

.section .text, "ax"
.global __AXGetCurrentProfile
__AXGetCurrentProfile:
/* 801075A8 001024A8  80 0D 9F 08 */	lwz r0, __AXProfileInitialized-_SDA_BASE_(r13)
/* 801075AC 001024AC  2C 00 00 00 */	cmpwi r0, 0
/* 801075B0 001024B0  41 82 00 30 */	beq lbl_801075E0
/* 801075B4 001024B4  80 AD 9F 0C */	lwz r5, __AXCurrentProfile-_SDA_BASE_(r13)
/* 801075B8 001024B8  80 6D 9F 10 */	lwz r3, __AXMaxProfiles-_SDA_BASE_(r13)
/* 801075BC 001024BC  38 85 00 01 */	addi r4, r5, 1
/* 801075C0 001024C0  80 CD 9F 14 */	lwz r6, __AXProfile-_SDA_BASE_(r13)
/* 801075C4 001024C4  7C 04 1B 96 */	divwu r0, r4, r3
/* 801075C8 001024C8  7C 00 19 D6 */	mullw r0, r0, r3
/* 801075CC 001024CC  1C 65 00 38 */	mulli r3, r5, 0x38
/* 801075D0 001024D0  7C 00 20 50 */	subf r0, r0, r4
/* 801075D4 001024D4  90 0D 9F 0C */	stw r0, __AXCurrentProfile-_SDA_BASE_(r13)
/* 801075D8 001024D8  7C 66 1A 14 */	add r3, r6, r3
/* 801075DC 001024DC  4E 80 00 20 */	blr 
lbl_801075E0:
/* 801075E0 001024E0  38 60 00 00 */	li r3, 0
/* 801075E4 001024E4  4E 80 00 20 */	blr 
