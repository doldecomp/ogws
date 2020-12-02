.include "macros.inc"

.section .text, "ax"  # 0x800076E0 - 0x80355080 

.global detail_AttachSoundAsTempHandle__Q34nw4r3snd11SoundHandleFPQ44nw4r3snd6detail10BasicSound
detail_AttachSoundAsTempHandle__Q34nw4r3snd11SoundHandleFPQ44nw4r3snd6detail10BasicSound:
/* 80045A94 00040994  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80045A98 00040998  7C 08 02 A6 */	mflr r0
/* 80045A9C 0004099C  90 01 00 14 */	stw r0, 0x14(r1)
/* 80045AA0 000409A0  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80045AA4 000409A4  7C 7F 1B 78 */	mr r31, r3
/* 80045AA8 000409A8  90 83 00 00 */	stw r4, 0(r3)
/* 80045AAC 000409AC  7C 83 23 78 */	mr r3, r4
/* 80045AB0 000409B0  4B FF 19 01 */	bl IsAttachedTempGeneralHandle__Q44nw4r3snd6detail10BasicSoundFv
/* 80045AB4 000409B4  2C 03 00 00 */	cmpwi r3, 0
/* 80045AB8 000409B8  41 82 00 0C */	beq lbl_80045AC4
/* 80045ABC 000409BC  80 7F 00 00 */	lwz r3, 0(r31)
/* 80045AC0 000409C0  4B FF 19 0D */	bl DetachTempGeneralHandle__Q44nw4r3snd6detail10BasicSoundFv
lbl_80045AC4:
/* 80045AC4 000409C4  80 7F 00 00 */	lwz r3, 0(r31)
/* 80045AC8 000409C8  81 83 00 00 */	lwz r12, 0(r3)
/* 80045ACC 000409CC  81 8C 00 5C */	lwz r12, 0x5c(r12)
/* 80045AD0 000409D0  7D 89 03 A6 */	mtctr r12
/* 80045AD4 000409D4  4E 80 04 21 */	bctrl 
/* 80045AD8 000409D8  2C 03 00 00 */	cmpwi r3, 0
/* 80045ADC 000409DC  41 82 00 18 */	beq lbl_80045AF4
/* 80045AE0 000409E0  80 7F 00 00 */	lwz r3, 0(r31)
/* 80045AE4 000409E4  81 83 00 00 */	lwz r12, 0(r3)
/* 80045AE8 000409E8  81 8C 00 60 */	lwz r12, 0x60(r12)
/* 80045AEC 000409EC  7D 89 03 A6 */	mtctr r12
/* 80045AF0 000409F0  4E 80 04 21 */	bctrl 
lbl_80045AF4:
/* 80045AF4 000409F4  80 7F 00 00 */	lwz r3, 0(r31)
/* 80045AF8 000409F8  93 E3 00 0C */	stw r31, 0xc(r3)
/* 80045AFC 000409FC  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80045B00 00040A00  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80045B04 00040A04  7C 08 03 A6 */	mtlr r0
/* 80045B08 00040A08  38 21 00 10 */	addi r1, r1, 0x10
/* 80045B0C 00040A0C  4E 80 00 20 */	blr 

.global detail_AttachSound__Q34nw4r3snd11SoundHandleFPQ44nw4r3snd6detail10BasicSound
detail_AttachSound__Q34nw4r3snd11SoundHandleFPQ44nw4r3snd6detail10BasicSound:
/* 80045B10 00040A10  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80045B14 00040A14  7C 08 02 A6 */	mflr r0
/* 80045B18 00040A18  90 01 00 14 */	stw r0, 0x14(r1)
/* 80045B1C 00040A1C  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80045B20 00040A20  7C 7F 1B 78 */	mr r31, r3
/* 80045B24 00040A24  90 83 00 00 */	stw r4, 0(r3)
/* 80045B28 00040A28  7C 83 23 78 */	mr r3, r4
/* 80045B2C 00040A2C  4B FF 18 71 */	bl IsAttachedGeneralHandle__Q44nw4r3snd6detail10BasicSoundFv
/* 80045B30 00040A30  2C 03 00 00 */	cmpwi r3, 0
/* 80045B34 00040A34  41 82 00 0C */	beq lbl_80045B40
/* 80045B38 00040A38  80 7F 00 00 */	lwz r3, 0(r31)
/* 80045B3C 00040A3C  4B FF 18 89 */	bl DetachGeneralHandle__Q44nw4r3snd6detail10BasicSoundFv
lbl_80045B40:
/* 80045B40 00040A40  80 7F 00 00 */	lwz r3, 0(r31)
/* 80045B44 00040A44  93 E3 00 08 */	stw r31, 8(r3)
/* 80045B48 00040A48  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80045B4C 00040A4C  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80045B50 00040A50  7C 08 03 A6 */	mtlr r0
/* 80045B54 00040A54  38 21 00 10 */	addi r1, r1, 0x10
/* 80045B58 00040A58  4E 80 00 20 */	blr 

.global DetachSound__Q34nw4r3snd11SoundHandleFv
DetachSound__Q34nw4r3snd11SoundHandleFv:
/* 80045B5C 00040A5C  80 83 00 00 */	lwz r4, 0(r3)
/* 80045B60 00040A60  2C 04 00 00 */	cmpwi r4, 0
/* 80045B64 00040A64  41 82 00 30 */	beq lbl_80045B94
/* 80045B68 00040A68  80 04 00 08 */	lwz r0, 8(r4)
/* 80045B6C 00040A6C  7C 00 18 40 */	cmplw r0, r3
/* 80045B70 00040A70  40 82 00 0C */	bne lbl_80045B7C
/* 80045B74 00040A74  38 00 00 00 */	li r0, 0
/* 80045B78 00040A78  90 04 00 08 */	stw r0, 8(r4)
lbl_80045B7C:
/* 80045B7C 00040A7C  80 83 00 00 */	lwz r4, 0(r3)
/* 80045B80 00040A80  80 04 00 0C */	lwz r0, 0xc(r4)
/* 80045B84 00040A84  7C 00 18 40 */	cmplw r0, r3
/* 80045B88 00040A88  40 82 00 0C */	bne lbl_80045B94
/* 80045B8C 00040A8C  38 00 00 00 */	li r0, 0
/* 80045B90 00040A90  90 04 00 0C */	stw r0, 0xc(r4)
lbl_80045B94:
/* 80045B94 00040A94  80 03 00 00 */	lwz r0, 0(r3)
/* 80045B98 00040A98  2C 00 00 00 */	cmpwi r0, 0
/* 80045B9C 00040A9C  4D 82 00 20 */	beqlr 
/* 80045BA0 00040AA0  38 00 00 00 */	li r0, 0
/* 80045BA4 00040AA4  90 03 00 00 */	stw r0, 0(r3)
/* 80045BA8 00040AA8  4E 80 00 20 */	blr 
