.include "macros.inc"

.section .text, "ax"  # 0x800076E0 - 0x80355080 

# __ct__Q44nw4r3snd6detail9StrmSoundFPQ44nw4r3snd6detail50SoundInstanceManager<Q44nw4r3snd6detail9StrmSound>
.global __ct__Q44nw4r3snd6detail9StrmSoundFPQ44nw4r3snd6detail50SoundInstanceManager$$0Q44nw4r3snd6detail9StrmSound$$1
__ct__Q44nw4r3snd6detail9StrmSoundFPQ44nw4r3snd6detail50SoundInstanceManager$$0Q44nw4r3snd6detail9StrmSound$$1:
/* 8004AC48 00045B48  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8004AC4C 00045B4C  7C 08 02 A6 */	mflr r0
/* 8004AC50 00045B50  90 01 00 14 */	stw r0, 0x14(r1)
/* 8004AC54 00045B54  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8004AC58 00045B58  7C 9F 23 78 */	mr r31, r4
/* 8004AC5C 00045B5C  93 C1 00 08 */	stw r30, 8(r1)
/* 8004AC60 00045B60  7C 7E 1B 78 */	mr r30, r3
/* 8004AC64 00045B64  4B FE B6 1D */	bl __ct__Q44nw4r3snd6detail10BasicSoundFv
/* 8004AC68 00045B68  3C 80 80 39 */	lis r4, __vt__Q44nw4r3snd6detail9StrmSound@ha
/* 8004AC6C 00045B6C  38 7E 00 D8 */	addi r3, r30, 0xd8
/* 8004AC70 00045B70  38 84 63 C0 */	addi r4, r4, __vt__Q44nw4r3snd6detail9StrmSound@l
/* 8004AC74 00045B74  90 9E 00 00 */	stw r4, 0(r30)
/* 8004AC78 00045B78  4B FF DB 41 */	bl __ct__Q44nw4r3snd6detail10StrmPlayerFv
/* 8004AC7C 00045B7C  38 00 00 00 */	li r0, 0
/* 8004AC80 00045B80  93 FE 09 24 */	stw r31, 0x924(r30)
/* 8004AC84 00045B84  7F C3 F3 78 */	mr r3, r30
/* 8004AC88 00045B88  90 1E 09 20 */	stw r0, 0x920(r30)
/* 8004AC8C 00045B8C  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8004AC90 00045B90  83 C1 00 08 */	lwz r30, 8(r1)
/* 8004AC94 00045B94  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8004AC98 00045B98  7C 08 03 A6 */	mtlr r0
/* 8004AC9C 00045B9C  38 21 00 10 */	addi r1, r1, 0x10
/* 8004ACA0 00045BA0  4E 80 00 20 */	blr 

.global Prepare__Q44nw4r3snd6detail9StrmSoundFPQ44nw4r3snd6detail14StrmBufferPoolQ54nw4r3snd6detail10StrmPlayer15StartOffsetTypeliPQ34nw4r2ut10FileStream
Prepare__Q44nw4r3snd6detail9StrmSoundFPQ44nw4r3snd6detail14StrmBufferPoolQ54nw4r3snd6detail10StrmPlayer15StartOffsetTypeliPQ34nw4r2ut10FileStream:
/* 8004ACA4 00045BA4  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8004ACA8 00045BA8  7C 08 02 A6 */	mflr r0
/* 8004ACAC 00045BAC  90 01 00 24 */	stw r0, 0x24(r1)
/* 8004ACB0 00045BB0  39 61 00 20 */	addi r11, r1, 0x20
/* 8004ACB4 00045BB4  48 06 70 8D */	bl _savegpr_26
/* 8004ACB8 00045BB8  2C 04 00 00 */	cmpwi r4, 0
/* 8004ACBC 00045BBC  7C 7A 1B 78 */	mr r26, r3
/* 8004ACC0 00045BC0  7C 9B 23 78 */	mr r27, r4
/* 8004ACC4 00045BC4  7C BC 2B 78 */	mr r28, r5
/* 8004ACC8 00045BC8  7C DD 33 78 */	mr r29, r6
/* 8004ACCC 00045BCC  7C FE 3B 78 */	mr r30, r7
/* 8004ACD0 00045BD0  7D 1F 43 78 */	mr r31, r8
/* 8004ACD4 00045BD4  40 82 00 0C */	bne lbl_8004ACE0
/* 8004ACD8 00045BD8  38 60 00 00 */	li r3, 0
/* 8004ACDC 00045BDC  48 00 00 64 */	b lbl_8004AD40
lbl_8004ACE0:
/* 8004ACE0 00045BE0  81 83 00 00 */	lwz r12, 0(r3)
/* 8004ACE4 00045BE4  81 8C 00 64 */	lwz r12, 0x64(r12)
/* 8004ACE8 00045BE8  7D 89 03 A6 */	mtctr r12
/* 8004ACEC 00045BEC  4E 80 04 21 */	bctrl 
/* 8004ACF0 00045BF0  7F 64 DB 78 */	mr r4, r27
/* 8004ACF4 00045BF4  38 7A 00 D8 */	addi r3, r26, 0xd8
/* 8004ACF8 00045BF8  4B FF DD 75 */	bl Setup__Q44nw4r3snd6detail10StrmPlayerFPQ44nw4r3snd6detail14StrmBufferPool
/* 8004ACFC 00045BFC  2C 03 00 00 */	cmpwi r3, 0
/* 8004AD00 00045C00  40 82 00 0C */	bne lbl_8004AD0C
/* 8004AD04 00045C04  38 60 00 00 */	li r3, 0
/* 8004AD08 00045C08  48 00 00 38 */	b lbl_8004AD40
lbl_8004AD0C:
/* 8004AD0C 00045C0C  7F E4 FB 78 */	mr r4, r31
/* 8004AD10 00045C10  7F C5 F3 78 */	mr r5, r30
/* 8004AD14 00045C14  7F 86 E3 78 */	mr r6, r28
/* 8004AD18 00045C18  7F A7 EB 78 */	mr r7, r29
/* 8004AD1C 00045C1C  38 7A 00 D8 */	addi r3, r26, 0xd8
/* 8004AD20 00045C20  4B FF DE BD */	bl Prepare__Q44nw4r3snd6detail10StrmPlayerFPQ34nw4r2ut10FileStreamiQ54nw4r3snd6detail10StrmPlayer15StartOffsetTypei
/* 8004AD24 00045C24  2C 03 00 00 */	cmpwi r3, 0
/* 8004AD28 00045C28  40 82 00 14 */	bne lbl_8004AD3C
/* 8004AD2C 00045C2C  38 7A 00 D8 */	addi r3, r26, 0xd8
/* 8004AD30 00045C30  4B FF DE 19 */	bl Shutdown__Q44nw4r3snd6detail10StrmPlayerFv
/* 8004AD34 00045C34  38 60 00 00 */	li r3, 0
/* 8004AD38 00045C38  48 00 00 08 */	b lbl_8004AD40
lbl_8004AD3C:
/* 8004AD3C 00045C3C  38 60 00 01 */	li r3, 1
lbl_8004AD40:
/* 8004AD40 00045C40  39 61 00 20 */	addi r11, r1, 0x20
/* 8004AD44 00045C44  48 06 70 49 */	bl _restgpr_26
/* 8004AD48 00045C48  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8004AD4C 00045C4C  7C 08 03 A6 */	mtlr r0
/* 8004AD50 00045C50  38 21 00 20 */	addi r1, r1, 0x20
/* 8004AD54 00045C54  4E 80 00 20 */	blr 

.global Shutdown__Q44nw4r3snd6detail9StrmSoundFv
Shutdown__Q44nw4r3snd6detail9StrmSoundFv:
/* 8004AD58 00045C58  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8004AD5C 00045C5C  7C 08 02 A6 */	mflr r0
/* 8004AD60 00045C60  90 01 00 24 */	stw r0, 0x24(r1)
/* 8004AD64 00045C64  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8004AD68 00045C68  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8004AD6C 00045C6C  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8004AD70 00045C70  7C 7D 1B 78 */	mr r29, r3
/* 8004AD74 00045C74  4B FE C1 A5 */	bl Shutdown__Q44nw4r3snd6detail10BasicSoundFv
/* 8004AD78 00045C78  83 DD 09 24 */	lwz r30, 0x924(r29)
/* 8004AD7C 00045C7C  3B FE 00 10 */	addi r31, r30, 0x10
/* 8004AD80 00045C80  7F E3 FB 78 */	mr r3, r31
/* 8004AD84 00045C84  48 0A 7D F9 */	bl OSLockMutex
/* 8004AD88 00045C88  80 1E 00 04 */	lwz r0, 4(r30)
/* 8004AD8C 00045C8C  2C 00 00 00 */	cmpwi r0, 0
/* 8004AD90 00045C90  40 82 00 10 */	bne lbl_8004ADA0
/* 8004AD94 00045C94  7F E3 FB 78 */	mr r3, r31
/* 8004AD98 00045C98  48 0A 7E C1 */	bl OSUnlockMutex
/* 8004AD9C 00045C9C  48 00 00 3C */	b lbl_8004ADD8
lbl_8004ADA0:
/* 8004ADA0 00045CA0  38 7E 00 04 */	addi r3, r30, 4
/* 8004ADA4 00045CA4  38 9D 00 B8 */	addi r4, r29, 0xb8
/* 8004ADA8 00045CA8  4B FB CD 11 */	bl Erase__Q44nw4r2ut6detail12LinkListImplFPQ34nw4r2ut12LinkListNode
/* 8004ADAC 00045CAC  81 9D 00 00 */	lwz r12, 0(r29)
/* 8004ADB0 00045CB0  7F A3 EB 78 */	mr r3, r29
/* 8004ADB4 00045CB4  38 80 FF FF */	li r4, -1
/* 8004ADB8 00045CB8  81 8C 00 0C */	lwz r12, 0xc(r12)
/* 8004ADBC 00045CBC  7D 89 03 A6 */	mtctr r12
/* 8004ADC0 00045CC0  4E 80 04 21 */	bctrl 
/* 8004ADC4 00045CC4  7F C3 F3 78 */	mr r3, r30
/* 8004ADC8 00045CC8  7F A4 EB 78 */	mr r4, r29
/* 8004ADCC 00045CCC  4B FF 04 35 */	bl FreeImpl__Q44nw4r3snd6detail8PoolImplFPv
/* 8004ADD0 00045CD0  7F E3 FB 78 */	mr r3, r31
/* 8004ADD4 00045CD4  48 0A 7E 85 */	bl OSUnlockMutex
lbl_8004ADD8:
/* 8004ADD8 00045CD8  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8004ADDC 00045CDC  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8004ADE0 00045CE0  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8004ADE4 00045CE4  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8004ADE8 00045CE8  7C 08 03 A6 */	mtlr r0
/* 8004ADEC 00045CEC  38 21 00 20 */	addi r1, r1, 0x20
/* 8004ADF0 00045CF0  4E 80 00 20 */	blr 

.global __dt__Q44nw4r3snd6detail9StrmSoundFv
__dt__Q44nw4r3snd6detail9StrmSoundFv:
/* 8004ADF4 00045CF4  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8004ADF8 00045CF8  7C 08 02 A6 */	mflr r0
/* 8004ADFC 00045CFC  2C 03 00 00 */	cmpwi r3, 0
/* 8004AE00 00045D00  90 01 00 14 */	stw r0, 0x14(r1)
/* 8004AE04 00045D04  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8004AE08 00045D08  7C 9F 23 78 */	mr r31, r4
/* 8004AE0C 00045D0C  93 C1 00 08 */	stw r30, 8(r1)
/* 8004AE10 00045D10  7C 7E 1B 78 */	mr r30, r3
/* 8004AE14 00045D14  41 82 00 20 */	beq lbl_8004AE34
/* 8004AE18 00045D18  38 80 FF FF */	li r4, -1
/* 8004AE1C 00045D1C  38 63 00 D8 */	addi r3, r3, 0xd8
/* 8004AE20 00045D20  4B FF DB 45 */	bl __dt__Q44nw4r3snd6detail10StrmPlayerFv
/* 8004AE24 00045D24  2C 1F 00 00 */	cmpwi r31, 0
/* 8004AE28 00045D28  40 81 00 0C */	ble lbl_8004AE34
/* 8004AE2C 00045D2C  7F C3 F3 78 */	mr r3, r30
/* 8004AE30 00045D30  48 05 84 55 */	bl __dl__FPv
lbl_8004AE34:
/* 8004AE34 00045D34  7F C3 F3 78 */	mr r3, r30
/* 8004AE38 00045D38  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8004AE3C 00045D3C  83 C1 00 08 */	lwz r30, 8(r1)
/* 8004AE40 00045D40  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8004AE44 00045D44  7C 08 03 A6 */	mtlr r0
/* 8004AE48 00045D48  38 21 00 10 */	addi r1, r1, 0x10
/* 8004AE4C 00045D4C  4E 80 00 20 */	blr 

.global SetPlayerPriority__Q44nw4r3snd6detail9StrmSoundFi
SetPlayerPriority__Q44nw4r3snd6detail9StrmSoundFi:
/* 8004AE50 00045D50  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8004AE54 00045D54  7C 08 02 A6 */	mflr r0
/* 8004AE58 00045D58  90 01 00 24 */	stw r0, 0x24(r1)
/* 8004AE5C 00045D5C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8004AE60 00045D60  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8004AE64 00045D64  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8004AE68 00045D68  93 81 00 10 */	stw r28, 0x10(r1)
/* 8004AE6C 00045D6C  7C 7C 1B 78 */	mr r28, r3
/* 8004AE70 00045D70  4B FE C2 19 */	bl SetPlayerPriority__Q44nw4r3snd6detail10BasicSoundFi
/* 8004AE74 00045D74  88 7C 00 74 */	lbz r3, 0x74(r28)
/* 8004AE78 00045D78  80 1C 00 40 */	lwz r0, 0x40(r28)
/* 8004AE7C 00045D7C  7C 63 02 14 */	add r3, r3, r0
/* 8004AE80 00045D80  2C 03 00 7F */	cmpwi r3, 0x7f
/* 8004AE84 00045D84  40 81 00 0C */	ble lbl_8004AE90
/* 8004AE88 00045D88  3B A0 00 7F */	li r29, 0x7f
/* 8004AE8C 00045D8C  48 00 00 0C */	b lbl_8004AE98
lbl_8004AE90:
/* 8004AE90 00045D90  7C 60 FE 70 */	srawi r0, r3, 0x1f
/* 8004AE94 00045D94  7C 7D 00 78 */	andc r29, r3, r0
lbl_8004AE98:
/* 8004AE98 00045D98  83 DC 09 24 */	lwz r30, 0x924(r28)
/* 8004AE9C 00045D9C  3B FE 00 10 */	addi r31, r30, 0x10
/* 8004AEA0 00045DA0  7F E3 FB 78 */	mr r3, r31
/* 8004AEA4 00045DA4  48 0A 7C D9 */	bl OSLockMutex
/* 8004AEA8 00045DA8  3B 9C 00 B8 */	addi r28, r28, 0xb8
/* 8004AEAC 00045DAC  38 7E 00 04 */	addi r3, r30, 4
/* 8004AEB0 00045DB0  7F 84 E3 78 */	mr r4, r28
/* 8004AEB4 00045DB4  4B FB CC 05 */	bl Erase__Q44nw4r2ut6detail12LinkListImplFPQ34nw4r2ut12LinkListNode
/* 8004AEB8 00045DB8  80 7E 00 08 */	lwz r3, 8(r30)
/* 8004AEBC 00045DBC  38 1E 00 08 */	addi r0, r30, 8
/* 8004AEC0 00045DC0  48 00 00 34 */	b lbl_8004AEF4
lbl_8004AEC4:
/* 8004AEC4 00045DC4  88 A3 FF BC */	lbz r5, -0x44(r3)
/* 8004AEC8 00045DC8  80 83 FF 88 */	lwz r4, -0x78(r3)
/* 8004AECC 00045DCC  7C A5 22 14 */	add r5, r5, r4
/* 8004AED0 00045DD0  2C 05 00 7F */	cmpwi r5, 0x7f
/* 8004AED4 00045DD4  40 81 00 0C */	ble lbl_8004AEE0
/* 8004AED8 00045DD8  38 80 00 7F */	li r4, 0x7f
/* 8004AEDC 00045DDC  48 00 00 0C */	b lbl_8004AEE8
lbl_8004AEE0:
/* 8004AEE0 00045DE0  7C A4 FE 70 */	srawi r4, r5, 0x1f
/* 8004AEE4 00045DE4  7C A4 20 78 */	andc r4, r5, r4
lbl_8004AEE8:
/* 8004AEE8 00045DE8  7C 1D 20 00 */	cmpw r29, r4
/* 8004AEEC 00045DEC  41 80 00 10 */	blt lbl_8004AEFC
/* 8004AEF0 00045DF0  80 63 00 00 */	lwz r3, 0(r3)
lbl_8004AEF4:
/* 8004AEF4 00045DF4  7C 03 00 40 */	cmplw r3, r0
/* 8004AEF8 00045DF8  40 82 FF CC */	bne lbl_8004AEC4
lbl_8004AEFC:
/* 8004AEFC 00045DFC  90 61 00 08 */	stw r3, 8(r1)
/* 8004AF00 00045E00  7F 85 E3 78 */	mr r5, r28
/* 8004AF04 00045E04  38 7E 00 04 */	addi r3, r30, 4
/* 8004AF08 00045E08  38 81 00 08 */	addi r4, r1, 8
/* 8004AF0C 00045E0C  4B FB CB 81 */	bl Insert__Q44nw4r2ut6detail12LinkListImplFQ54nw4r2ut6detail12LinkListImpl8IteratorPQ34nw4r2ut12LinkListNode
/* 8004AF10 00045E10  7F E3 FB 78 */	mr r3, r31
/* 8004AF14 00045E14  48 0A 7D 45 */	bl OSUnlockMutex
/* 8004AF18 00045E18  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8004AF1C 00045E1C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8004AF20 00045E20  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8004AF24 00045E24  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8004AF28 00045E28  83 81 00 10 */	lwz r28, 0x10(r1)
/* 8004AF2C 00045E2C  7C 08 03 A6 */	mtlr r0
/* 8004AF30 00045E30  38 21 00 20 */	addi r1, r1, 0x20
/* 8004AF34 00045E34  4E 80 00 20 */	blr 

.global IsAttachedTempSpecialHandle__Q44nw4r3snd6detail9StrmSoundFv
IsAttachedTempSpecialHandle__Q44nw4r3snd6detail9StrmSoundFv:
/* 8004AF38 00045E38  80 63 09 20 */	lwz r3, 0x920(r3)
/* 8004AF3C 00045E3C  7C 03 00 D0 */	neg r0, r3
/* 8004AF40 00045E40  7C 00 1B 78 */	or r0, r0, r3
/* 8004AF44 00045E44  54 03 0F FE */	srwi r3, r0, 0x1f
/* 8004AF48 00045E48  4E 80 00 20 */	blr 

.global DetachTempSpecialHandle__Q44nw4r3snd6detail9StrmSoundFv
DetachTempSpecialHandle__Q44nw4r3snd6detail9StrmSoundFv:
/* 8004AF4C 00045E4C  80 63 09 20 */	lwz r3, 0x920(r3)
/* 8004AF50 00045E50  48 00 00 30 */	b DetachSound__Q34nw4r3snd15StrmSoundHandleFv

.global GetBasicPlayer__Q44nw4r3snd6detail9StrmSoundFv
GetBasicPlayer__Q44nw4r3snd6detail9StrmSoundFv:
/* 8004AF54 00045E54  38 63 00 D8 */	addi r3, r3, 0xd8
/* 8004AF58 00045E58  4E 80 00 20 */	blr 

.global GetBasicPlayer__Q44nw4r3snd6detail9StrmSoundCFv
GetBasicPlayer__Q44nw4r3snd6detail9StrmSoundCFv:
/* 8004AF5C 00045E5C  38 63 00 D8 */	addi r3, r3, 0xd8
/* 8004AF60 00045E60  4E 80 00 20 */	blr 

.global IsPrepared__Q44nw4r3snd6detail9StrmSoundCFv
IsPrepared__Q44nw4r3snd6detail9StrmSoundCFv:
/* 8004AF64 00045E64  88 63 01 93 */	lbz r3, 0x193(r3)
/* 8004AF68 00045E68  4E 80 00 20 */	blr 

.global GetRuntimeTypeInfo__Q44nw4r3snd6detail9StrmSoundCFv
GetRuntimeTypeInfo__Q44nw4r3snd6detail9StrmSoundCFv:
/* 8004AF6C 00045E6C  38 6D 97 A0 */	addi r3, r13, lbl_804BEB20-_SDA_BASE_
/* 8004AF70 00045E70  4E 80 00 20 */	blr 

# __sinit_\snd_StrmSound_cpp
.global __sinit_$$3snd_StrmSound_cpp
__sinit_$$3snd_StrmSound_cpp:
/* 8004AF74 00045E74  38 0D 96 F8 */	addi r0, r13, typeInfo__Q44nw4r3snd6detail10BasicSound-_SDA_BASE_
/* 8004AF78 00045E78  90 0D 97 A0 */	stw r0, lbl_804BEB20-_SDA_BASE_(r13)
/* 8004AF7C 00045E7C  4E 80 00 20 */	blr 
