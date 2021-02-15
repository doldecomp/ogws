.include "macros.inc"

.section .data, "wa"
.global __vt__Q34nw4r3snd9SoundHeap
__vt__Q34nw4r3snd9SoundHeap:
	.long 0
	.long 0
	.long __dt__Q34nw4r3snd9SoundHeapFv
	.long Alloc__Q34nw4r3snd9SoundHeapFUl
.balign 0x8

.section .text, "ax"  # 0x800076E0 - 0x80355080 
.global __ct__Q34nw4r3snd9SoundHeapFv
__ct__Q34nw4r3snd9SoundHeapFv:
/* 80045BAC 00040AAC  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80045BB0 00040AB0  7C 08 02 A6 */	mflr r0
/* 80045BB4 00040AB4  3C 80 80 39 */	lis r4, __vt__Q34nw4r3snd9SoundHeap@ha
/* 80045BB8 00040AB8  90 01 00 14 */	stw r0, 0x14(r1)
/* 80045BBC 00040ABC  38 84 62 F0 */	addi r4, r4, __vt__Q34nw4r3snd9SoundHeap@l
/* 80045BC0 00040AC0  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80045BC4 00040AC4  7C 7F 1B 78 */	mr r31, r3
/* 80045BC8 00040AC8  90 83 00 00 */	stw r4, 0(r3)
/* 80045BCC 00040ACC  38 63 00 1C */	addi r3, r3, 0x1c
/* 80045BD0 00040AD0  4B FF 38 E9 */	bl __ct__Q44nw4r3snd6detail9FrameHeapFv
/* 80045BD4 00040AD4  38 7F 00 04 */	addi r3, r31, 4
/* 80045BD8 00040AD8  48 0A CF 6D */	bl OSInitMutex
/* 80045BDC 00040ADC  7F E3 FB 78 */	mr r3, r31
/* 80045BE0 00040AE0  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80045BE4 00040AE4  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80045BE8 00040AE8  7C 08 03 A6 */	mtlr r0
/* 80045BEC 00040AEC  38 21 00 10 */	addi r1, r1, 0x10
/* 80045BF0 00040AF0  4E 80 00 20 */	blr 

.global __dt__Q34nw4r3snd9SoundHeapFv
__dt__Q34nw4r3snd9SoundHeapFv:
/* 80045BF4 00040AF4  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80045BF8 00040AF8  7C 08 02 A6 */	mflr r0
/* 80045BFC 00040AFC  2C 03 00 00 */	cmpwi r3, 0
/* 80045C00 00040B00  90 01 00 14 */	stw r0, 0x14(r1)
/* 80045C04 00040B04  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80045C08 00040B08  7C 9F 23 78 */	mr r31, r4
/* 80045C0C 00040B0C  93 C1 00 08 */	stw r30, 8(r1)
/* 80045C10 00040B10  7C 7E 1B 78 */	mr r30, r3
/* 80045C14 00040B14  41 82 00 34 */	beq lbl_80045C48
/* 80045C18 00040B18  3C 80 80 39 */	lis r4, __vt__Q34nw4r3snd9SoundHeap@ha
/* 80045C1C 00040B1C  38 84 62 F0 */	addi r4, r4, __vt__Q34nw4r3snd9SoundHeap@l
/* 80045C20 00040B20  90 83 00 00 */	stw r4, 0(r3)
/* 80045C24 00040B24  38 63 00 1C */	addi r3, r3, 0x1c
/* 80045C28 00040B28  4B FF 3B 65 */	bl Destroy__Q44nw4r3snd6detail9FrameHeapFv
/* 80045C2C 00040B2C  38 7E 00 1C */	addi r3, r30, 0x1c
/* 80045C30 00040B30  38 80 FF FF */	li r4, -1
/* 80045C34 00040B34  4B FF 38 A9 */	bl __dt__Q44nw4r3snd6detail9FrameHeapFv
/* 80045C38 00040B38  2C 1F 00 00 */	cmpwi r31, 0
/* 80045C3C 00040B3C  40 81 00 0C */	ble lbl_80045C48
/* 80045C40 00040B40  7F C3 F3 78 */	mr r3, r30
/* 80045C44 00040B44  48 05 D6 41 */	bl __dl__FPv
lbl_80045C48:
/* 80045C48 00040B48  7F C3 F3 78 */	mr r3, r30
/* 80045C4C 00040B4C  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80045C50 00040B50  83 C1 00 08 */	lwz r30, 8(r1)
/* 80045C54 00040B54  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80045C58 00040B58  7C 08 03 A6 */	mtlr r0
/* 80045C5C 00040B5C  38 21 00 10 */	addi r1, r1, 0x10
/* 80045C60 00040B60  4E 80 00 20 */	blr 

.global Create__Q34nw4r3snd9SoundHeapFPvUl
Create__Q34nw4r3snd9SoundHeapFPvUl:
/* 80045C64 00040B64  38 63 00 1C */	addi r3, r3, 0x1c
/* 80045C68 00040B68  4B FF 39 88 */	b Create__Q44nw4r3snd6detail9FrameHeapFPvUl

.global Destroy__Q34nw4r3snd9SoundHeapFv
Destroy__Q34nw4r3snd9SoundHeapFv:
/* 80045C6C 00040B6C  38 63 00 1C */	addi r3, r3, 0x1c
/* 80045C70 00040B70  4B FF 3B 1C */	b Destroy__Q44nw4r3snd6detail9FrameHeapFv

.global Alloc__Q34nw4r3snd9SoundHeapFUl
Alloc__Q34nw4r3snd9SoundHeapFUl:
/* 80045C74 00040B74  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80045C78 00040B78  7C 08 02 A6 */	mflr r0
/* 80045C7C 00040B7C  90 01 00 24 */	stw r0, 0x24(r1)
/* 80045C80 00040B80  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80045C84 00040B84  3B E3 00 04 */	addi r31, r3, 4
/* 80045C88 00040B88  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80045C8C 00040B8C  7C 9E 23 78 */	mr r30, r4
/* 80045C90 00040B90  93 A1 00 14 */	stw r29, 0x14(r1)
/* 80045C94 00040B94  7C 7D 1B 78 */	mr r29, r3
/* 80045C98 00040B98  7F E3 FB 78 */	mr r3, r31
/* 80045C9C 00040B9C  48 0A CE E1 */	bl OSLockMutex
/* 80045CA0 00040BA0  3C A0 80 04 */	lis r5, DisposeCallbackFunc__Q34nw4r3snd9SoundHeapFPvUlPv@ha
/* 80045CA4 00040BA4  7F C4 F3 78 */	mr r4, r30
/* 80045CA8 00040BA8  38 7D 00 1C */	addi r3, r29, 0x1c
/* 80045CAC 00040BAC  38 C0 00 00 */	li r6, 0
/* 80045CB0 00040BB0  38 A5 5E 7C */	addi r5, r5, DisposeCallbackFunc__Q34nw4r3snd9SoundHeapFPvUlPv@l
/* 80045CB4 00040BB4  4B FF 3C F5 */	bl Alloc__Q44nw4r3snd6detail9FrameHeapFUlPFPvUlPv_vPv
/* 80045CB8 00040BB8  7C 7E 1B 78 */	mr r30, r3
/* 80045CBC 00040BBC  7F E3 FB 78 */	mr r3, r31
/* 80045CC0 00040BC0  48 0A CF 99 */	bl OSUnlockMutex
/* 80045CC4 00040BC4  7F C3 F3 78 */	mr r3, r30
/* 80045CC8 00040BC8  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80045CCC 00040BCC  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80045CD0 00040BD0  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 80045CD4 00040BD4  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80045CD8 00040BD8  7C 08 03 A6 */	mtlr r0
/* 80045CDC 00040BDC  38 21 00 20 */	addi r1, r1, 0x20
/* 80045CE0 00040BE0  4E 80 00 20 */	blr 

.global Alloc__Q34nw4r3snd9SoundHeapFUlPFPvUlPv_vPv
Alloc__Q34nw4r3snd9SoundHeapFUlPFPvUlPv_vPv:
/* 80045CE4 00040BE4  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80045CE8 00040BE8  7C 08 02 A6 */	mflr r0
/* 80045CEC 00040BEC  90 01 00 24 */	stw r0, 0x24(r1)
/* 80045CF0 00040BF0  39 61 00 20 */	addi r11, r1, 0x20
/* 80045CF4 00040BF4  48 06 C0 51 */	bl _savegpr_27
/* 80045CF8 00040BF8  3B E3 00 04 */	addi r31, r3, 4
/* 80045CFC 00040BFC  7C 7B 1B 78 */	mr r27, r3
/* 80045D00 00040C00  7C 9C 23 78 */	mr r28, r4
/* 80045D04 00040C04  7C BD 2B 78 */	mr r29, r5
/* 80045D08 00040C08  7C DE 33 78 */	mr r30, r6
/* 80045D0C 00040C0C  7F E3 FB 78 */	mr r3, r31
/* 80045D10 00040C10  48 0A CE 6D */	bl OSLockMutex
/* 80045D14 00040C14  7F 84 E3 78 */	mr r4, r28
/* 80045D18 00040C18  7F A5 EB 78 */	mr r5, r29
/* 80045D1C 00040C1C  7F C6 F3 78 */	mr r6, r30
/* 80045D20 00040C20  38 7B 00 1C */	addi r3, r27, 0x1c
/* 80045D24 00040C24  4B FF 3C 85 */	bl Alloc__Q44nw4r3snd6detail9FrameHeapFUlPFPvUlPv_vPv
/* 80045D28 00040C28  7C 7E 1B 78 */	mr r30, r3
/* 80045D2C 00040C2C  7F E3 FB 78 */	mr r3, r31
/* 80045D30 00040C30  48 0A CF 29 */	bl OSUnlockMutex
/* 80045D34 00040C34  39 61 00 20 */	addi r11, r1, 0x20
/* 80045D38 00040C38  7F C3 F3 78 */	mr r3, r30
/* 80045D3C 00040C3C  48 06 C0 55 */	bl _restgpr_27
/* 80045D40 00040C40  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80045D44 00040C44  7C 08 03 A6 */	mtlr r0
/* 80045D48 00040C48  38 21 00 20 */	addi r1, r1, 0x20
/* 80045D4C 00040C4C  4E 80 00 20 */	blr 

.global Clear__Q34nw4r3snd9SoundHeapFv
Clear__Q34nw4r3snd9SoundHeapFv:
/* 80045D50 00040C50  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80045D54 00040C54  7C 08 02 A6 */	mflr r0
/* 80045D58 00040C58  90 01 00 14 */	stw r0, 0x14(r1)
/* 80045D5C 00040C5C  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80045D60 00040C60  3B E3 00 04 */	addi r31, r3, 4
/* 80045D64 00040C64  93 C1 00 08 */	stw r30, 8(r1)
/* 80045D68 00040C68  7C 7E 1B 78 */	mr r30, r3
/* 80045D6C 00040C6C  7F E3 FB 78 */	mr r3, r31
/* 80045D70 00040C70  48 0A CE 0D */	bl OSLockMutex
/* 80045D74 00040C74  48 00 1B 65 */	bl GetInstance__Q44nw4r3snd6detail11SoundThreadFv
/* 80045D78 00040C78  38 63 03 54 */	addi r3, r3, 0x354
/* 80045D7C 00040C7C  48 0A CE 01 */	bl OSLockMutex
/* 80045D80 00040C80  38 7E 00 1C */	addi r3, r30, 0x1c
/* 80045D84 00040C84  4B FF 3A F9 */	bl Clear__Q44nw4r3snd6detail9FrameHeapFv
/* 80045D88 00040C88  48 00 1B 51 */	bl GetInstance__Q44nw4r3snd6detail11SoundThreadFv
/* 80045D8C 00040C8C  38 63 03 54 */	addi r3, r3, 0x354
/* 80045D90 00040C90  48 0A CE C9 */	bl OSUnlockMutex
/* 80045D94 00040C94  7F E3 FB 78 */	mr r3, r31
/* 80045D98 00040C98  48 0A CE C1 */	bl OSUnlockMutex
/* 80045D9C 00040C9C  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80045DA0 00040CA0  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80045DA4 00040CA4  83 C1 00 08 */	lwz r30, 8(r1)
/* 80045DA8 00040CA8  7C 08 03 A6 */	mtlr r0
/* 80045DAC 00040CAC  38 21 00 10 */	addi r1, r1, 0x10
/* 80045DB0 00040CB0  4E 80 00 20 */	blr 

.global SaveState__Q34nw4r3snd9SoundHeapFv
SaveState__Q34nw4r3snd9SoundHeapFv:
/* 80045DB4 00040CB4  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80045DB8 00040CB8  7C 08 02 A6 */	mflr r0
/* 80045DBC 00040CBC  90 01 00 14 */	stw r0, 0x14(r1)
/* 80045DC0 00040CC0  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80045DC4 00040CC4  3B E3 00 04 */	addi r31, r3, 4
/* 80045DC8 00040CC8  93 C1 00 08 */	stw r30, 8(r1)
/* 80045DCC 00040CCC  7C 7E 1B 78 */	mr r30, r3
/* 80045DD0 00040CD0  7F E3 FB 78 */	mr r3, r31
/* 80045DD4 00040CD4  48 0A CD A9 */	bl OSLockMutex
/* 80045DD8 00040CD8  38 7E 00 1C */	addi r3, r30, 0x1c
/* 80045DDC 00040CDC  4B FF 3C 71 */	bl SaveState__Q44nw4r3snd6detail9FrameHeapFv
/* 80045DE0 00040CE0  7C 7E 1B 78 */	mr r30, r3
/* 80045DE4 00040CE4  7F E3 FB 78 */	mr r3, r31
/* 80045DE8 00040CE8  48 0A CE 71 */	bl OSUnlockMutex
/* 80045DEC 00040CEC  7F C3 F3 78 */	mr r3, r30
/* 80045DF0 00040CF0  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80045DF4 00040CF4  83 C1 00 08 */	lwz r30, 8(r1)
/* 80045DF8 00040CF8  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80045DFC 00040CFC  7C 08 03 A6 */	mtlr r0
/* 80045E00 00040D00  38 21 00 10 */	addi r1, r1, 0x10
/* 80045E04 00040D04  4E 80 00 20 */	blr 

.global LoadState__Q34nw4r3snd9SoundHeapFi
LoadState__Q34nw4r3snd9SoundHeapFi:
/* 80045E08 00040D08  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80045E0C 00040D0C  7C 08 02 A6 */	mflr r0
/* 80045E10 00040D10  90 01 00 24 */	stw r0, 0x24(r1)
/* 80045E14 00040D14  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80045E18 00040D18  3B E3 00 04 */	addi r31, r3, 4
/* 80045E1C 00040D1C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80045E20 00040D20  7C 9E 23 78 */	mr r30, r4
/* 80045E24 00040D24  93 A1 00 14 */	stw r29, 0x14(r1)
/* 80045E28 00040D28  7C 7D 1B 78 */	mr r29, r3
/* 80045E2C 00040D2C  7F E3 FB 78 */	mr r3, r31
/* 80045E30 00040D30  48 0A CD 4D */	bl OSLockMutex
/* 80045E34 00040D34  48 00 1A A5 */	bl GetInstance__Q44nw4r3snd6detail11SoundThreadFv
/* 80045E38 00040D38  38 63 03 54 */	addi r3, r3, 0x354
/* 80045E3C 00040D3C  48 0A CD 41 */	bl OSLockMutex
/* 80045E40 00040D40  7F C4 F3 78 */	mr r4, r30
/* 80045E44 00040D44  38 7D 00 1C */	addi r3, r29, 0x1c
/* 80045E48 00040D48  4B FF 3C D1 */	bl LoadState__Q44nw4r3snd6detail9FrameHeapFi
/* 80045E4C 00040D4C  48 00 1A 8D */	bl GetInstance__Q44nw4r3snd6detail11SoundThreadFv
/* 80045E50 00040D50  38 63 03 54 */	addi r3, r3, 0x354
/* 80045E54 00040D54  48 0A CE 05 */	bl OSUnlockMutex
/* 80045E58 00040D58  7F E3 FB 78 */	mr r3, r31
/* 80045E5C 00040D5C  48 0A CD FD */	bl OSUnlockMutex
/* 80045E60 00040D60  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80045E64 00040D64  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80045E68 00040D68  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80045E6C 00040D6C  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 80045E70 00040D70  7C 08 03 A6 */	mtlr r0
/* 80045E74 00040D74  38 21 00 20 */	addi r1, r1, 0x20
/* 80045E78 00040D78  4E 80 00 20 */	blr 

.global DisposeCallbackFunc__Q34nw4r3snd9SoundHeapFPvUlPv
DisposeCallbackFunc__Q34nw4r3snd9SoundHeapFPvUlPv:
/* 80045E7C 00040D7C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80045E80 00040D80  7C 08 02 A6 */	mflr r0
/* 80045E84 00040D84  90 01 00 24 */	stw r0, 0x24(r1)
/* 80045E88 00040D88  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80045E8C 00040D8C  7C BF 2B 78 */	mr r31, r5
/* 80045E90 00040D90  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80045E94 00040D94  7C 9E 23 78 */	mr r30, r4
/* 80045E98 00040D98  93 A1 00 14 */	stw r29, 0x14(r1)
/* 80045E9C 00040D9C  7C 7D 1B 78 */	mr r29, r3
/* 80045EA0 00040DA0  4B FF 26 E5 */	bl GetInstance__Q44nw4r3snd6detail22DisposeCallbackManagerFv
/* 80045EA4 00040DA4  7F A4 EB 78 */	mr r4, r29
/* 80045EA8 00040DA8  7F C5 F3 78 */	mr r5, r30
/* 80045EAC 00040DAC  7F E6 FB 78 */	mr r6, r31
/* 80045EB0 00040DB0  4B FF 27 ED */	bl Dispose__Q44nw4r3snd6detail22DisposeCallbackManagerFPvUlPv
/* 80045EB4 00040DB4  4B FF 26 D1 */	bl GetInstance__Q44nw4r3snd6detail22DisposeCallbackManagerFv
/* 80045EB8 00040DB8  7F A4 EB 78 */	mr r4, r29
/* 80045EBC 00040DBC  7F C5 F3 78 */	mr r5, r30
/* 80045EC0 00040DC0  7F E6 FB 78 */	mr r6, r31
/* 80045EC4 00040DC4  4B FF 28 FD */	bl DisposeWave__Q44nw4r3snd6detail22DisposeCallbackManagerFPvUlPv
/* 80045EC8 00040DC8  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80045ECC 00040DCC  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80045ED0 00040DD0  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80045ED4 00040DD4  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 80045ED8 00040DD8  7C 08 03 A6 */	mtlr r0
/* 80045EDC 00040DDC  38 21 00 20 */	addi r1, r1, 0x20
/* 80045EE0 00040DE0  4E 80 00 20 */	blr 
