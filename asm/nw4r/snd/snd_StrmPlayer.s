.include "macros.inc"

.section .data, "wa"
.balign 0x8
.global __vt__Q44nw4r3snd6detail10StrmPlayer
__vt__Q44nw4r3snd6detail10StrmPlayer:
	.long 0
	.long 0
	.long __dt__Q44nw4r3snd6detail10StrmPlayerFv
	.long Start__Q44nw4r3snd6detail10StrmPlayerFv
	.long Stop__Q44nw4r3snd6detail10StrmPlayerFv
	.long Pause__Q44nw4r3snd6detail10StrmPlayerFb
	.long IsActive__Q44nw4r3snd6detail10StrmPlayerCFv
	.long IsStarted__Q44nw4r3snd6detail10StrmPlayerCFv
	.long IsPause__Q44nw4r3snd6detail10StrmPlayerCFv
	.long 0
	.long 0
	.long $2116$2__dt__Q44nw4r3snd6detail10StrmPlayerFv
	.long $2116$2OnUpdateFrameSoundThread__Q44nw4r3snd6detail10StrmPlayerFv
	.long $2116$2OnUpdateVoiceSoundThread__Q44nw4r3snd6detail10StrmPlayerFv
	.long $2116$2OnShutdownSoundThread__Q44nw4r3snd6detail10StrmPlayerFv
	.long OnUpdateFrameSoundThread__Q44nw4r3snd6detail10StrmPlayerFv
	.long OnUpdateVoiceSoundThread__Q44nw4r3snd6detail10StrmPlayerFv
	.long OnShutdownSoundThread__Q44nw4r3snd6detail10StrmPlayerFv
.balign 0x8
.global __vt__Q54nw4r3snd6detail10StrmPlayer16StrmDataLoadTask
__vt__Q54nw4r3snd6detail10StrmPlayer16StrmDataLoadTask:
	.long 0
	.long 0
	.long __dt__Q54nw4r3snd6detail10StrmPlayer16StrmDataLoadTaskFv
	.long Execute__Q54nw4r3snd6detail10StrmPlayer16StrmDataLoadTaskFv
	.long Cancel__Q54nw4r3snd6detail10StrmPlayer16StrmDataLoadTaskFv
	.long OnCancel__Q54nw4r3snd6detail10StrmPlayer16StrmDataLoadTaskFv
.balign 0x8
.global __vt__Q54nw4r3snd6detail10StrmPlayer18StrmHeaderLoadTask
__vt__Q54nw4r3snd6detail10StrmPlayer18StrmHeaderLoadTask:
	.long 0
	.long 0
	.long __dt__Q54nw4r3snd6detail10StrmPlayer18StrmHeaderLoadTaskFv
	.long Execute__Q54nw4r3snd6detail10StrmPlayer18StrmHeaderLoadTaskFv
	.long Cancel__Q54nw4r3snd6detail10StrmPlayer18StrmHeaderLoadTaskFv
	.long OnCancel__Q54nw4r3snd6detail10StrmPlayer18StrmHeaderLoadTaskFv
.balign 0x8

.section .bss, "wa"
.balign 0x8
.global sLoadBuffer__Q44nw4r3snd6detail10StrmPlayer # align to 32
sLoadBuffer__Q44nw4r3snd6detail10StrmPlayer:
	.balign 32
	.skip 0x4020
.global sLoadBufferMutex__Q44nw4r3snd6detail10StrmPlayer
sLoadBufferMutex__Q44nw4r3snd6detail10StrmPlayer:
	.skip 0x18

.section .sbss, "wa"
.balign 0x8
.global lbl_804BEB18
lbl_804BEB18:
	.skip 0x8

.section .sdata2, "a"
.balign 0x8
.global lbl_804C0120
lbl_804C0120:
	.single 0e1
.global lbl_804C0124
lbl_804C0124:
	.single 0e0

.section .text, "ax"  # 0x800076E0 - 0x80355080 
.global __ct__Q44nw4r3snd6detail10StrmPlayerFv
__ct__Q44nw4r3snd6detail10StrmPlayerFv:
/* 800487B8 000436B8  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800487BC 000436BC  7C 08 02 A6 */	mflr r0
/* 800487C0 000436C0  90 01 00 14 */	stw r0, 0x14(r1)
/* 800487C4 000436C4  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800487C8 000436C8  93 C1 00 08 */	stw r30, 8(r1)
/* 800487CC 000436CC  7C 7E 1B 78 */	mr r30, r3
/* 800487D0 000436D0  4B FE D9 51 */	bl __ct__Q44nw4r3snd6detail11BasicPlayerFv
/* 800487D4 000436D4  3B E0 00 00 */	li r31, 0
/* 800487D8 000436D8  3C C0 80 39 */	lis r6, __vt__Q44nw4r3snd6detail10StrmPlayer@ha
/* 800487DC 000436DC  38 C6 63 48 */	addi r6, r6, __vt__Q44nw4r3snd6detail10StrmPlayer@l
/* 800487E0 000436E0  3D 00 80 39 */	lis r8, __vt__Q54nw4r3snd6detail10StrmPlayer18StrmHeaderLoadTask@ha
/* 800487E4 000436E4  38 06 00 24 */	addi r0, r6, 0x24
/* 800487E8 000436E8  93 FE 01 2C */	stw r31, 0x12c(r30)
/* 800487EC 000436EC  39 3E 01 2C */	addi r9, r30, 0x12c
/* 800487F0 000436F0  39 08 63 A8 */	addi r8, r8, __vt__Q54nw4r3snd6detail10StrmPlayer18StrmHeaderLoadTask@l
/* 800487F4 000436F4  93 FE 01 30 */	stw r31, 0x130(r30)
/* 800487F8 000436F8  3C 80 80 05 */	lis r4, __ct__Q54nw4r3snd6detail10StrmPlayer16StrmDataLoadTaskFv@ha
/* 800487FC 000436FC  3C A0 80 05 */	lis r5, __dt__Q54nw4r3snd6detail10StrmPlayer16StrmDataLoadTaskFv@ha
/* 80048800 00043700  38 7E 01 38 */	addi r3, r30, 0x138
/* 80048804 00043704  90 DE 00 00 */	stw r6, 0(r30)
/* 80048808 00043708  38 84 A9 BC */	addi r4, r4, __ct__Q54nw4r3snd6detail10StrmPlayer16StrmDataLoadTaskFv@l
/* 8004880C 0004370C  38 A5 89 0C */	addi r5, r5, __dt__Q54nw4r3snd6detail10StrmPlayer16StrmDataLoadTaskFv@l
/* 80048810 00043710  38 C0 00 34 */	li r6, 0x34
/* 80048814 00043714  93 FE 00 74 */	stw r31, 0x74(r30)
/* 80048818 00043718  38 E0 00 20 */	li r7, 0x20
/* 8004881C 0004371C  93 FE 00 78 */	stw r31, 0x78(r30)
/* 80048820 00043720  90 1E 00 7C */	stw r0, 0x7c(r30)
/* 80048824 00043724  9B FE 00 B8 */	stb r31, 0xb8(r30)
/* 80048828 00043728  9B FE 00 B9 */	stb r31, 0xb9(r30)
/* 8004882C 0004372C  93 FE 01 0C */	stw r31, 0x10c(r30)
/* 80048830 00043730  93 FE 01 10 */	stw r31, 0x110(r30)
/* 80048834 00043734  9B FE 01 14 */	stb r31, 0x114(r30)
/* 80048838 00043738  91 1E 01 08 */	stw r8, 0x108(r30)
/* 8004883C 0004373C  93 FE 01 18 */	stw r31, 0x118(r30)
/* 80048840 00043740  93 FE 01 1C */	stw r31, 0x11c(r30)
/* 80048844 00043744  93 FE 01 24 */	stw r31, 0x124(r30)
/* 80048848 00043748  93 FE 01 28 */	stw r31, 0x128(r30)
/* 8004884C 0004374C  91 3E 01 2C */	stw r9, 0x12c(r30)
/* 80048850 00043750  91 3E 01 30 */	stw r9, 0x130(r30)
/* 80048854 00043754  93 FE 01 34 */	stw r31, 0x134(r30)
/* 80048858 00043758  48 06 91 FD */	bl __construct_array
/* 8004885C 0004375C  93 FE 07 BC */	stw r31, 0x7bc(r30)
/* 80048860 00043760  93 FE 07 C0 */	stw r31, 0x7c0(r30)
/* 80048864 00043764  88 0D 97 98 */	lbz r0, lbl_804BEB18-_SDA_BASE_(r13)
/* 80048868 00043768  2C 00 00 00 */	cmpwi r0, 0
/* 8004886C 0004376C  40 82 00 18 */	bne lbl_80048884
/* 80048870 00043770  3C 60 80 3F */	lis r3, sLoadBufferMutex__Q44nw4r3snd6detail10StrmPlayer@ha
/* 80048874 00043774  38 63 BC 40 */	addi r3, r3, sLoadBufferMutex__Q44nw4r3snd6detail10StrmPlayer@l
/* 80048878 00043778  48 0A A2 CD */	bl OSInitMutex
/* 8004887C 0004377C  38 00 00 01 */	li r0, 1
/* 80048880 00043780  98 0D 97 98 */	stb r0, lbl_804BEB18-_SDA_BASE_(r13)
lbl_80048884:
/* 80048884 00043784  38 7E 01 34 */	addi r3, r30, 0x134
/* 80048888 00043788  38 9E 01 38 */	addi r4, r30, 0x138
/* 8004888C 0004378C  38 A0 06 80 */	li r5, 0x680
/* 80048890 00043790  38 C0 00 34 */	li r6, 0x34
/* 80048894 00043794  4B FF 26 FD */	bl CreateImpl__Q44nw4r3snd6detail8PoolImplFPvUlUl
/* 80048898 00043798  7F C3 F3 78 */	mr r3, r30
/* 8004889C 0004379C  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 800488A0 000437A0  83 C1 00 08 */	lwz r30, 8(r1)
/* 800488A4 000437A4  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800488A8 000437A8  7C 08 03 A6 */	mtlr r0
/* 800488AC 000437AC  38 21 00 10 */	addi r1, r1, 0x10
/* 800488B0 000437B0  4E 80 00 20 */	blr 

.global __dt__Q54nw4r3snd6detail10StrmPlayer18StrmHeaderLoadTaskFv
__dt__Q54nw4r3snd6detail10StrmPlayer18StrmHeaderLoadTaskFv:
/* 800488B4 000437B4  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800488B8 000437B8  7C 08 02 A6 */	mflr r0
/* 800488BC 000437BC  2C 03 00 00 */	cmpwi r3, 0
/* 800488C0 000437C0  90 01 00 14 */	stw r0, 0x14(r1)
/* 800488C4 000437C4  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800488C8 000437C8  7C 9F 23 78 */	mr r31, r4
/* 800488CC 000437CC  93 C1 00 08 */	stw r30, 8(r1)
/* 800488D0 000437D0  7C 7E 1B 78 */	mr r30, r3
/* 800488D4 000437D4  41 82 00 1C */	beq lbl_800488F0
/* 800488D8 000437D8  38 80 00 00 */	li r4, 0
/* 800488DC 000437DC  48 00 26 DD */	bl __dt__Q44nw4r3snd6detail4TaskFv
/* 800488E0 000437E0  2C 1F 00 00 */	cmpwi r31, 0
/* 800488E4 000437E4  40 81 00 0C */	ble lbl_800488F0
/* 800488E8 000437E8  7F C3 F3 78 */	mr r3, r30
/* 800488EC 000437EC  48 05 A9 99 */	bl __dl__FPv
lbl_800488F0:
/* 800488F0 000437F0  7F C3 F3 78 */	mr r3, r30
/* 800488F4 000437F4  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 800488F8 000437F8  83 C1 00 08 */	lwz r30, 8(r1)
/* 800488FC 000437FC  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80048900 00043800  7C 08 03 A6 */	mtlr r0
/* 80048904 00043804  38 21 00 10 */	addi r1, r1, 0x10
/* 80048908 00043808  4E 80 00 20 */	blr 

.global __dt__Q54nw4r3snd6detail10StrmPlayer16StrmDataLoadTaskFv
__dt__Q54nw4r3snd6detail10StrmPlayer16StrmDataLoadTaskFv:
/* 8004890C 0004380C  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80048910 00043810  7C 08 02 A6 */	mflr r0
/* 80048914 00043814  2C 03 00 00 */	cmpwi r3, 0
/* 80048918 00043818  90 01 00 14 */	stw r0, 0x14(r1)
/* 8004891C 0004381C  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80048920 00043820  7C 9F 23 78 */	mr r31, r4
/* 80048924 00043824  93 C1 00 08 */	stw r30, 8(r1)
/* 80048928 00043828  7C 7E 1B 78 */	mr r30, r3
/* 8004892C 0004382C  41 82 00 1C */	beq lbl_80048948
/* 80048930 00043830  38 80 00 00 */	li r4, 0
/* 80048934 00043834  48 00 26 85 */	bl __dt__Q44nw4r3snd6detail4TaskFv
/* 80048938 00043838  2C 1F 00 00 */	cmpwi r31, 0
/* 8004893C 0004383C  40 81 00 0C */	ble lbl_80048948
/* 80048940 00043840  7F C3 F3 78 */	mr r3, r30
/* 80048944 00043844  48 05 A9 41 */	bl __dl__FPv
lbl_80048948:
/* 80048948 00043848  7F C3 F3 78 */	mr r3, r30
/* 8004894C 0004384C  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80048950 00043850  83 C1 00 08 */	lwz r30, 8(r1)
/* 80048954 00043854  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80048958 00043858  7C 08 03 A6 */	mtlr r0
/* 8004895C 0004385C  38 21 00 10 */	addi r1, r1, 0x10
/* 80048960 00043860  4E 80 00 20 */	blr 

.global __dt__Q44nw4r3snd6detail10StrmPlayerFv
__dt__Q44nw4r3snd6detail10StrmPlayerFv:
/* 80048964 00043864  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80048968 00043868  7C 08 02 A6 */	mflr r0
/* 8004896C 0004386C  2C 03 00 00 */	cmpwi r3, 0
/* 80048970 00043870  90 01 00 24 */	stw r0, 0x24(r1)
/* 80048974 00043874  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80048978 00043878  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8004897C 0004387C  7C 9E 23 78 */	mr r30, r4
/* 80048980 00043880  93 A1 00 14 */	stw r29, 0x14(r1)
/* 80048984 00043884  7C 7D 1B 78 */	mr r29, r3
/* 80048988 00043888  41 82 00 C4 */	beq lbl_80048A4C
/* 8004898C 0004388C  3C 80 80 39 */	lis r4, __vt__Q44nw4r3snd6detail10StrmPlayer@ha
/* 80048990 00043890  38 84 63 48 */	addi r4, r4, __vt__Q44nw4r3snd6detail10StrmPlayer@l
/* 80048994 00043894  38 04 00 24 */	addi r0, r4, 0x24
/* 80048998 00043898  90 83 00 00 */	stw r4, 0(r3)
/* 8004899C 0004389C  90 03 00 7C */	stw r0, 0x7c(r3)
/* 800489A0 000438A0  4B FF EF 39 */	bl GetInstance__Q44nw4r3snd6detail11SoundThreadFv
/* 800489A4 000438A4  38 63 03 54 */	addi r3, r3, 0x354
/* 800489A8 000438A8  48 0A A1 D5 */	bl OSLockMutex
/* 800489AC 000438AC  81 9D 00 00 */	lwz r12, 0(r29)
/* 800489B0 000438B0  7F A3 EB 78 */	mr r3, r29
/* 800489B4 000438B4  81 8C 00 10 */	lwz r12, 0x10(r12)
/* 800489B8 000438B8  7D 89 03 A6 */	mtctr r12
/* 800489BC 000438BC  4E 80 04 21 */	bctrl 
/* 800489C0 000438C0  88 1D 00 B8 */	lbz r0, 0xb8(r29)
/* 800489C4 000438C4  2C 00 00 00 */	cmpwi r0, 0
/* 800489C8 000438C8  40 82 00 14 */	bne lbl_800489DC
/* 800489CC 000438CC  4B FF EF 0D */	bl GetInstance__Q44nw4r3snd6detail11SoundThreadFv
/* 800489D0 000438D0  38 63 03 54 */	addi r3, r3, 0x354
/* 800489D4 000438D4  48 0A A2 85 */	bl OSUnlockMutex
/* 800489D8 000438D8  48 00 00 2C */	b lbl_80048A04
lbl_800489DC:
/* 800489DC 000438DC  3B E0 00 00 */	li r31, 0
/* 800489E0 000438E0  38 7D 01 34 */	addi r3, r29, 0x134
/* 800489E4 000438E4  93 FD 07 B8 */	stw r31, 0x7b8(r29)
/* 800489E8 000438E8  38 9D 01 38 */	addi r4, r29, 0x138
/* 800489EC 000438EC  38 A0 06 80 */	li r5, 0x680
/* 800489F0 000438F0  4B FF 26 E5 */	bl DestroyImpl__Q44nw4r3snd6detail8PoolImplFPvUl
/* 800489F4 000438F4  9B FD 00 B8 */	stb r31, 0xb8(r29)
/* 800489F8 000438F8  4B FF EE E1 */	bl GetInstance__Q44nw4r3snd6detail11SoundThreadFv
/* 800489FC 000438FC  38 63 03 54 */	addi r3, r3, 0x354
/* 80048A00 00043900  48 0A A2 59 */	bl OSUnlockMutex
lbl_80048A04:
/* 80048A04 00043904  3C 80 80 05 */	lis r4, __dt__Q54nw4r3snd6detail10StrmPlayer16StrmDataLoadTaskFv@ha
/* 80048A08 00043908  38 7D 01 38 */	addi r3, r29, 0x138
/* 80048A0C 0004390C  38 84 89 0C */	addi r4, r4, __dt__Q54nw4r3snd6detail10StrmPlayer16StrmDataLoadTaskFv@l
/* 80048A10 00043910  38 A0 00 34 */	li r5, 0x34
/* 80048A14 00043914  38 C0 00 20 */	li r6, 0x20
/* 80048A18 00043918  48 06 91 35 */	bl __destroy_arr
/* 80048A1C 0004391C  34 7D 01 28 */	addic. r3, r29, 0x128
/* 80048A20 00043920  41 82 00 0C */	beq lbl_80048A2C
/* 80048A24 00043924  38 80 00 00 */	li r4, 0
/* 80048A28 00043928  4B FB EF 55 */	bl __dt__Q44nw4r2ut6detail12LinkListImplFv
lbl_80048A2C:
/* 80048A2C 0004392C  34 7D 01 08 */	addic. r3, r29, 0x108
/* 80048A30 00043930  41 82 00 0C */	beq lbl_80048A3C
/* 80048A34 00043934  38 80 00 00 */	li r4, 0
/* 80048A38 00043938  48 00 25 81 */	bl __dt__Q44nw4r3snd6detail4TaskFv
lbl_80048A3C:
/* 80048A3C 0004393C  2C 1E 00 00 */	cmpwi r30, 0
/* 80048A40 00043940  40 81 00 0C */	ble lbl_80048A4C
/* 80048A44 00043944  7F A3 EB 78 */	mr r3, r29
/* 80048A48 00043948  48 05 A8 3D */	bl __dl__FPv
lbl_80048A4C:
/* 80048A4C 0004394C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80048A50 00043950  7F A3 EB 78 */	mr r3, r29
/* 80048A54 00043954  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80048A58 00043958  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 80048A5C 0004395C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80048A60 00043960  7C 08 03 A6 */	mtlr r0
/* 80048A64 00043964  38 21 00 20 */	addi r1, r1, 0x20
/* 80048A68 00043968  4E 80 00 20 */	blr 

.global Setup__Q44nw4r3snd6detail10StrmPlayerFPQ44nw4r3snd6detail14StrmBufferPool
Setup__Q44nw4r3snd6detail10StrmPlayerFPQ44nw4r3snd6detail14StrmBufferPool:
/* 80048A6C 0004396C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80048A70 00043970  7C 08 02 A6 */	mflr r0
/* 80048A74 00043974  90 01 00 24 */	stw r0, 0x24(r1)
/* 80048A78 00043978  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80048A7C 0004397C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80048A80 00043980  7C 9E 23 78 */	mr r30, r4
/* 80048A84 00043984  93 A1 00 14 */	stw r29, 0x14(r1)
/* 80048A88 00043988  7C 7D 1B 78 */	mr r29, r3
/* 80048A8C 0004398C  4B FF EE 4D */	bl GetInstance__Q44nw4r3snd6detail11SoundThreadFv
/* 80048A90 00043990  38 63 03 54 */	addi r3, r3, 0x354
/* 80048A94 00043994  48 0A A0 E9 */	bl OSLockMutex
/* 80048A98 00043998  88 1D 00 B8 */	lbz r0, 0xb8(r29)
/* 80048A9C 0004399C  2C 00 00 00 */	cmpwi r0, 0
/* 80048AA0 000439A0  41 82 00 68 */	beq lbl_80048B08
/* 80048AA4 000439A4  4B FF EE 35 */	bl GetInstance__Q44nw4r3snd6detail11SoundThreadFv
/* 80048AA8 000439A8  38 63 03 54 */	addi r3, r3, 0x354
/* 80048AAC 000439AC  48 0A A0 D1 */	bl OSLockMutex
/* 80048AB0 000439B0  81 9D 00 00 */	lwz r12, 0(r29)
/* 80048AB4 000439B4  7F A3 EB 78 */	mr r3, r29
/* 80048AB8 000439B8  81 8C 00 10 */	lwz r12, 0x10(r12)
/* 80048ABC 000439BC  7D 89 03 A6 */	mtctr r12
/* 80048AC0 000439C0  4E 80 04 21 */	bctrl 
/* 80048AC4 000439C4  88 1D 00 B8 */	lbz r0, 0xb8(r29)
/* 80048AC8 000439C8  2C 00 00 00 */	cmpwi r0, 0
/* 80048ACC 000439CC  40 82 00 14 */	bne lbl_80048AE0
/* 80048AD0 000439D0  4B FF EE 09 */	bl GetInstance__Q44nw4r3snd6detail11SoundThreadFv
/* 80048AD4 000439D4  38 63 03 54 */	addi r3, r3, 0x354
/* 80048AD8 000439D8  48 0A A1 81 */	bl OSUnlockMutex
/* 80048ADC 000439DC  48 00 00 2C */	b lbl_80048B08
lbl_80048AE0:
/* 80048AE0 000439E0  3B E0 00 00 */	li r31, 0
/* 80048AE4 000439E4  38 7D 01 34 */	addi r3, r29, 0x134
/* 80048AE8 000439E8  93 FD 07 B8 */	stw r31, 0x7b8(r29)
/* 80048AEC 000439EC  38 9D 01 38 */	addi r4, r29, 0x138
/* 80048AF0 000439F0  38 A0 06 80 */	li r5, 0x680
/* 80048AF4 000439F4  4B FF 25 E1 */	bl DestroyImpl__Q44nw4r3snd6detail8PoolImplFPvUl
/* 80048AF8 000439F8  9B FD 00 B8 */	stb r31, 0xb8(r29)
/* 80048AFC 000439FC  4B FF ED DD */	bl GetInstance__Q44nw4r3snd6detail11SoundThreadFv
/* 80048B00 00043A00  38 63 03 54 */	addi r3, r3, 0x354
/* 80048B04 00043A04  48 0A A1 55 */	bl OSUnlockMutex
lbl_80048B08:
/* 80048B08 00043A08  7F A3 EB 78 */	mr r3, r29
/* 80048B0C 00043A0C  48 00 06 85 */	bl InitParam__Q44nw4r3snd6detail10StrmPlayerFv
/* 80048B10 00043A10  38 00 00 01 */	li r0, 1
/* 80048B14 00043A14  93 DD 07 B8 */	stw r30, 0x7b8(r29)
/* 80048B18 00043A18  98 1D 00 B8 */	stb r0, 0xb8(r29)
/* 80048B1C 00043A1C  4B FF ED BD */	bl GetInstance__Q44nw4r3snd6detail11SoundThreadFv
/* 80048B20 00043A20  38 63 03 54 */	addi r3, r3, 0x354
/* 80048B24 00043A24  48 0A A1 35 */	bl OSUnlockMutex
/* 80048B28 00043A28  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80048B2C 00043A2C  38 60 00 01 */	li r3, 1
/* 80048B30 00043A30  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80048B34 00043A34  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 80048B38 00043A38  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80048B3C 00043A3C  7C 08 03 A6 */	mtlr r0
/* 80048B40 00043A40  38 21 00 20 */	addi r1, r1, 0x20
/* 80048B44 00043A44  4E 80 00 20 */	blr 

.global Shutdown__Q44nw4r3snd6detail10StrmPlayerFv
Shutdown__Q44nw4r3snd6detail10StrmPlayerFv:
/* 80048B48 00043A48  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80048B4C 00043A4C  7C 08 02 A6 */	mflr r0
/* 80048B50 00043A50  90 01 00 14 */	stw r0, 0x14(r1)
/* 80048B54 00043A54  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80048B58 00043A58  93 C1 00 08 */	stw r30, 8(r1)
/* 80048B5C 00043A5C  7C 7E 1B 78 */	mr r30, r3
/* 80048B60 00043A60  4B FF ED 79 */	bl GetInstance__Q44nw4r3snd6detail11SoundThreadFv
/* 80048B64 00043A64  38 63 03 54 */	addi r3, r3, 0x354
/* 80048B68 00043A68  48 0A A0 15 */	bl OSLockMutex
/* 80048B6C 00043A6C  81 9E 00 00 */	lwz r12, 0(r30)
/* 80048B70 00043A70  7F C3 F3 78 */	mr r3, r30
/* 80048B74 00043A74  81 8C 00 10 */	lwz r12, 0x10(r12)
/* 80048B78 00043A78  7D 89 03 A6 */	mtctr r12
/* 80048B7C 00043A7C  4E 80 04 21 */	bctrl 
/* 80048B80 00043A80  88 1E 00 B8 */	lbz r0, 0xb8(r30)
/* 80048B84 00043A84  2C 00 00 00 */	cmpwi r0, 0
/* 80048B88 00043A88  40 82 00 14 */	bne lbl_80048B9C
/* 80048B8C 00043A8C  4B FF ED 4D */	bl GetInstance__Q44nw4r3snd6detail11SoundThreadFv
/* 80048B90 00043A90  38 63 03 54 */	addi r3, r3, 0x354
/* 80048B94 00043A94  48 0A A0 C5 */	bl OSUnlockMutex
/* 80048B98 00043A98  48 00 00 2C */	b lbl_80048BC4
lbl_80048B9C:
/* 80048B9C 00043A9C  3B E0 00 00 */	li r31, 0
/* 80048BA0 00043AA0  38 7E 01 34 */	addi r3, r30, 0x134
/* 80048BA4 00043AA4  93 FE 07 B8 */	stw r31, 0x7b8(r30)
/* 80048BA8 00043AA8  38 9E 01 38 */	addi r4, r30, 0x138
/* 80048BAC 00043AAC  38 A0 06 80 */	li r5, 0x680
/* 80048BB0 00043AB0  4B FF 25 25 */	bl DestroyImpl__Q44nw4r3snd6detail8PoolImplFPvUl
/* 80048BB4 00043AB4  9B FE 00 B8 */	stb r31, 0xb8(r30)
/* 80048BB8 00043AB8  4B FF ED 21 */	bl GetInstance__Q44nw4r3snd6detail11SoundThreadFv
/* 80048BBC 00043ABC  38 63 03 54 */	addi r3, r3, 0x354
/* 80048BC0 00043AC0  48 0A A0 99 */	bl OSUnlockMutex
lbl_80048BC4:
/* 80048BC4 00043AC4  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80048BC8 00043AC8  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80048BCC 00043ACC  83 C1 00 08 */	lwz r30, 8(r1)
/* 80048BD0 00043AD0  7C 08 03 A6 */	mtlr r0
/* 80048BD4 00043AD4  38 21 00 10 */	addi r1, r1, 0x10
/* 80048BD8 00043AD8  4E 80 00 20 */	blr 

.global Prepare__Q44nw4r3snd6detail10StrmPlayerFPQ34nw4r2ut10FileStreamiQ54nw4r3snd6detail10StrmPlayer15StartOffsetTypei
Prepare__Q44nw4r3snd6detail10StrmPlayerFPQ34nw4r2ut10FileStreamiQ54nw4r3snd6detail10StrmPlayer15StartOffsetTypei:
/* 80048BDC 00043ADC  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80048BE0 00043AE0  7C 08 02 A6 */	mflr r0
/* 80048BE4 00043AE4  90 01 00 24 */	stw r0, 0x24(r1)
/* 80048BE8 00043AE8  39 61 00 20 */	addi r11, r1, 0x20
/* 80048BEC 00043AEC  48 06 91 59 */	bl _savegpr_27
/* 80048BF0 00043AF0  7C 7B 1B 78 */	mr r27, r3
/* 80048BF4 00043AF4  7C 9F 23 78 */	mr r31, r4
/* 80048BF8 00043AF8  7C BC 2B 78 */	mr r28, r5
/* 80048BFC 00043AFC  7C DD 33 78 */	mr r29, r6
/* 80048C00 00043B00  7C FE 3B 78 */	mr r30, r7
/* 80048C04 00043B04  4B FF EC D5 */	bl GetInstance__Q44nw4r3snd6detail11SoundThreadFv
/* 80048C08 00043B08  38 63 03 54 */	addi r3, r3, 0x354
/* 80048C0C 00043B0C  48 0A 9F 71 */	bl OSLockMutex
/* 80048C10 00043B10  38 60 00 00 */	li r3, 0
/* 80048C14 00043B14  38 00 00 01 */	li r0, 1
/* 80048C18 00043B18  93 FB 07 BC */	stw r31, 0x7bc(r27)
/* 80048C1C 00043B1C  2C 1B 00 00 */	cmpwi r27, 0
/* 80048C20 00043B20  7F 7F DB 78 */	mr r31, r27
/* 80048C24 00043B24  93 9B 07 C8 */	stw r28, 0x7c8(r27)
/* 80048C28 00043B28  93 BB 01 00 */	stw r29, 0x100(r27)
/* 80048C2C 00043B2C  93 DB 01 04 */	stw r30, 0x104(r27)
/* 80048C30 00043B30  98 7B 00 BC */	stb r3, 0xbc(r27)
/* 80048C34 00043B34  98 7B 00 BD */	stb r3, 0xbd(r27)
/* 80048C38 00043B38  98 7B 00 BE */	stb r3, 0xbe(r27)
/* 80048C3C 00043B3C  98 1B 00 B9 */	stb r0, 0xb9(r27)
/* 80048C40 00043B40  41 82 00 08 */	beq lbl_80048C48
/* 80048C44 00043B44  3B FB 00 74 */	addi r31, r27, 0x74
lbl_80048C48:
/* 80048C48 00043B48  4B FF EC 91 */	bl GetInstance__Q44nw4r3snd6detail11SoundThreadFv
/* 80048C4C 00043B4C  7F E4 FB 78 */	mr r4, r31
/* 80048C50 00043B50  4B FF F1 55 */	bl RegisterPlayerCallback__Q44nw4r3snd6detail11SoundThreadFPQ54nw4r3snd6detail11SoundThread14PlayerCallback
/* 80048C54 00043B54  80 9B 07 BC */	lwz r4, 0x7bc(r27)
/* 80048C58 00043B58  3B FB 01 08 */	addi r31, r27, 0x108
/* 80048C5C 00043B5C  80 7B 01 00 */	lwz r3, 0x100(r27)
/* 80048C60 00043B60  80 1B 01 04 */	lwz r0, 0x104(r27)
/* 80048C64 00043B64  93 7B 01 18 */	stw r27, 0x118(r27)
/* 80048C68 00043B68  90 9B 01 1C */	stw r4, 0x11c(r27)
/* 80048C6C 00043B6C  90 7B 01 20 */	stw r3, 0x120(r27)
/* 80048C70 00043B70  90 1B 01 24 */	stw r0, 0x124(r27)
/* 80048C74 00043B74  48 00 23 85 */	bl GetInstance__Q44nw4r3snd6detail11TaskManagerFv
/* 80048C78 00043B78  7F E4 FB 78 */	mr r4, r31
/* 80048C7C 00043B7C  38 A0 00 01 */	li r5, 1
/* 80048C80 00043B80  48 00 24 F1 */	bl AppendTask__Q44nw4r3snd6detail11TaskManagerFPQ44nw4r3snd6detail4TaskQ54nw4r3snd6detail11TaskManager12TaskPriority
/* 80048C84 00043B84  4B FF EC 55 */	bl GetInstance__Q44nw4r3snd6detail11SoundThreadFv
/* 80048C88 00043B88  38 63 03 54 */	addi r3, r3, 0x354
/* 80048C8C 00043B8C  48 0A 9F CD */	bl OSUnlockMutex
/* 80048C90 00043B90  39 61 00 20 */	addi r11, r1, 0x20
/* 80048C94 00043B94  38 60 00 01 */	li r3, 1
/* 80048C98 00043B98  48 06 90 F9 */	bl _restgpr_27
/* 80048C9C 00043B9C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80048CA0 00043BA0  7C 08 03 A6 */	mtlr r0
/* 80048CA4 00043BA4  38 21 00 20 */	addi r1, r1, 0x20
/* 80048CA8 00043BA8  4E 80 00 20 */	blr 

.global Start__Q44nw4r3snd6detail10StrmPlayerFv
Start__Q44nw4r3snd6detail10StrmPlayerFv:
/* 80048CAC 00043BAC  94 21 FF 40 */	stwu r1, -0xc0(r1)
/* 80048CB0 00043BB0  7C 08 02 A6 */	mflr r0
/* 80048CB4 00043BB4  90 01 00 C4 */	stw r0, 0xc4(r1)
/* 80048CB8 00043BB8  93 E1 00 BC */	stw r31, 0xbc(r1)
/* 80048CBC 00043BBC  7C 7F 1B 78 */	mr r31, r3
/* 80048CC0 00043BC0  93 C1 00 B8 */	stw r30, 0xb8(r1)
/* 80048CC4 00043BC4  93 A1 00 B4 */	stw r29, 0xb4(r1)
/* 80048CC8 00043BC8  93 81 00 B0 */	stw r28, 0xb0(r1)
/* 80048CCC 00043BCC  4B FF EC 0D */	bl GetInstance__Q44nw4r3snd6detail11SoundThreadFv
/* 80048CD0 00043BD0  38 63 03 54 */	addi r3, r3, 0x354
/* 80048CD4 00043BD4  48 0A 9E A9 */	bl OSLockMutex
/* 80048CD8 00043BD8  88 1F 00 BB */	lbz r0, 0xbb(r31)
/* 80048CDC 00043BDC  2C 00 00 00 */	cmpwi r0, 0
/* 80048CE0 00043BE0  40 82 00 18 */	bne lbl_80048CF8
/* 80048CE4 00043BE4  4B FF EB F5 */	bl GetInstance__Q44nw4r3snd6detail11SoundThreadFv
/* 80048CE8 00043BE8  38 63 03 54 */	addi r3, r3, 0x354
/* 80048CEC 00043BEC  48 0A 9F 6D */	bl OSUnlockMutex
/* 80048CF0 00043BF0  38 60 00 00 */	li r3, 0
/* 80048CF4 00043BF4  48 00 02 A4 */	b lbl_80048F98
lbl_80048CF8:
/* 80048CF8 00043BF8  88 1F 00 BA */	lbz r0, 0xba(r31)
/* 80048CFC 00043BFC  2C 00 00 00 */	cmpwi r0, 0
/* 80048D00 00043C00  40 82 02 88 */	bne lbl_80048F88
/* 80048D04 00043C04  3B A0 00 00 */	li r29, 0
/* 80048D08 00043C08  7F E3 FB 78 */	mr r3, r31
/* 80048D0C 00043C0C  93 A1 00 10 */	stw r29, 0x10(r1)
/* 80048D10 00043C10  38 81 00 10 */	addi r4, r1, 0x10
/* 80048D14 00043C14  38 A1 00 0C */	addi r5, r1, 0xc
/* 80048D18 00043C18  38 C1 00 08 */	addi r6, r1, 8
/* 80048D1C 00043C1C  93 A1 00 0C */	stw r29, 0xc(r1)
/* 80048D20 00043C20  93 A1 00 08 */	stw r29, 8(r1)
/* 80048D24 00043C24  48 00 19 E1 */	bl CalcStartOffset__Q44nw4r3snd6detail10StrmPlayerFPlPUlPl
/* 80048D28 00043C28  2C 03 00 00 */	cmpwi r3, 0
/* 80048D2C 00043C2C  40 82 00 18 */	bne lbl_80048D44
/* 80048D30 00043C30  4B FF EB A9 */	bl GetInstance__Q44nw4r3snd6detail11SoundThreadFv
/* 80048D34 00043C34  38 63 03 54 */	addi r3, r3, 0x354
/* 80048D38 00043C38  48 0A 9F 21 */	bl OSUnlockMutex
/* 80048D3C 00043C3C  38 60 00 00 */	li r3, 0
/* 80048D40 00043C40  48 00 02 58 */	b lbl_80048F98
lbl_80048D44:
/* 80048D44 00043C44  80 BF 00 C8 */	lwz r5, 0xc8(r31)
/* 80048D48 00043C48  38 00 00 01 */	li r0, 1
/* 80048D4C 00043C4C  80 81 00 08 */	lwz r4, 8(r1)
/* 80048D50 00043C50  88 7F 00 80 */	lbz r3, 0x80(r31)
/* 80048D54 00043C54  7C 85 22 14 */	add r4, r5, r4
/* 80048D58 00043C58  90 9F 00 C8 */	stw r4, 0xc8(r31)
/* 80048D5C 00043C5C  98 61 00 18 */	stb r3, 0x18(r1)
/* 80048D60 00043C60  98 01 00 19 */	stb r0, 0x19(r1)
/* 80048D64 00043C64  80 1F 07 C4 */	lwz r0, 0x7c4(r31)
/* 80048D68 00043C68  98 01 00 1A */	stb r0, 0x1a(r1)
/* 80048D6C 00043C6C  80 1F 00 84 */	lwz r0, 0x84(r31)
/* 80048D70 00043C70  90 01 00 1C */	stw r0, 0x1c(r1)
/* 80048D74 00043C74  93 A1 00 20 */	stw r29, 0x20(r1)
/* 80048D78 00043C78  88 7F 00 80 */	lbz r3, 0x80(r31)
/* 80048D7C 00043C7C  48 00 61 41 */	bl func_8004EEBC
/* 80048D80 00043C80  80 BF 00 D4 */	lwz r5, 0xd4(r31)
/* 80048D84 00043C84  7C 64 1B 78 */	mr r4, r3
/* 80048D88 00043C88  80 1F 00 EC */	lwz r0, 0xec(r31)
/* 80048D8C 00043C8C  7C 65 01 D6 */	mullw r3, r5, r0
/* 80048D90 00043C90  4B FE A2 91 */	bl GetSampleByByte__Q44nw4r3snd6detail7AxVoiceFUlQ54nw4r3snd6detail7AxVoice6Format
/* 80048D94 00043C94  90 61 00 24 */	stw r3, 0x24(r1)
/* 80048D98 00043C98  7F E4 FB 78 */	mr r4, r31
/* 80048D9C 00043C9C  7F E5 FB 78 */	mr r5, r31
/* 80048DA0 00043CA0  38 61 00 28 */	addi r3, r1, 0x28
/* 80048DA4 00043CA4  38 C0 00 00 */	li r6, 0
/* 80048DA8 00043CA8  48 00 00 F8 */	b lbl_80048EA0
lbl_80048DAC:
/* 80048DAC 00043CAC  80 04 07 CC */	lwz r0, 0x7cc(r4)
/* 80048DB0 00043CB0  38 C6 00 01 */	addi r6, r6, 1
/* 80048DB4 00043CB4  90 03 00 00 */	stw r0, 0(r3)
/* 80048DB8 00043CB8  A0 E4 07 D4 */	lhz r7, 0x7d4(r4)
/* 80048DBC 00043CBC  A0 04 07 D6 */	lhz r0, 0x7d6(r4)
/* 80048DC0 00043CC0  B0 E3 00 14 */	sth r7, 0x14(r3)
/* 80048DC4 00043CC4  B0 03 00 16 */	sth r0, 0x16(r3)
/* 80048DC8 00043CC8  A0 E4 07 D8 */	lhz r7, 0x7d8(r4)
/* 80048DCC 00043CCC  A0 04 07 DA */	lhz r0, 0x7da(r4)
/* 80048DD0 00043CD0  B0 E3 00 18 */	sth r7, 0x18(r3)
/* 80048DD4 00043CD4  B0 03 00 1A */	sth r0, 0x1a(r3)
/* 80048DD8 00043CD8  A0 E4 07 DC */	lhz r7, 0x7dc(r4)
/* 80048DDC 00043CDC  A0 04 07 DE */	lhz r0, 0x7de(r4)
/* 80048DE0 00043CE0  B0 E3 00 1C */	sth r7, 0x1c(r3)
/* 80048DE4 00043CE4  B0 03 00 1E */	sth r0, 0x1e(r3)
/* 80048DE8 00043CE8  A0 E4 07 E0 */	lhz r7, 0x7e0(r4)
/* 80048DEC 00043CEC  A0 04 07 E2 */	lhz r0, 0x7e2(r4)
/* 80048DF0 00043CF0  B0 E3 00 20 */	sth r7, 0x20(r3)
/* 80048DF4 00043CF4  B0 03 00 22 */	sth r0, 0x22(r3)
/* 80048DF8 00043CF8  A0 E4 07 E4 */	lhz r7, 0x7e4(r4)
/* 80048DFC 00043CFC  A0 04 07 E6 */	lhz r0, 0x7e6(r4)
/* 80048E00 00043D00  B0 E3 00 24 */	sth r7, 0x24(r3)
/* 80048E04 00043D04  B0 03 00 26 */	sth r0, 0x26(r3)
/* 80048E08 00043D08  A0 E4 07 E8 */	lhz r7, 0x7e8(r4)
/* 80048E0C 00043D0C  A0 04 07 EA */	lhz r0, 0x7ea(r4)
/* 80048E10 00043D10  B0 E3 00 28 */	sth r7, 0x28(r3)
/* 80048E14 00043D14  B0 03 00 2A */	sth r0, 0x2a(r3)
/* 80048E18 00043D18  A0 E4 07 EC */	lhz r7, 0x7ec(r4)
/* 80048E1C 00043D1C  A0 04 07 EE */	lhz r0, 0x7ee(r4)
/* 80048E20 00043D20  B0 E3 00 2C */	sth r7, 0x2c(r3)
/* 80048E24 00043D24  B0 03 00 2E */	sth r0, 0x2e(r3)
/* 80048E28 00043D28  A0 E4 07 F0 */	lhz r7, 0x7f0(r4)
/* 80048E2C 00043D2C  A0 04 07 F2 */	lhz r0, 0x7f2(r4)
/* 80048E30 00043D30  B0 E3 00 30 */	sth r7, 0x30(r3)
/* 80048E34 00043D34  B0 03 00 32 */	sth r0, 0x32(r3)
/* 80048E38 00043D38  A0 E4 07 F4 */	lhz r7, 0x7f4(r4)
/* 80048E3C 00043D3C  A0 04 07 F6 */	lhz r0, 0x7f6(r4)
/* 80048E40 00043D40  B0 E3 00 34 */	sth r7, 0x34(r3)
/* 80048E44 00043D44  B0 03 00 36 */	sth r0, 0x36(r3)
/* 80048E48 00043D48  A0 E4 07 F8 */	lhz r7, 0x7f8(r4)
/* 80048E4C 00043D4C  A0 04 07 FA */	lhz r0, 0x7fa(r4)
/* 80048E50 00043D50  B0 E3 00 38 */	sth r7, 0x38(r3)
/* 80048E54 00043D54  B0 03 00 3A */	sth r0, 0x3a(r3)
/* 80048E58 00043D58  A0 04 07 FC */	lhz r0, 0x7fc(r4)
/* 80048E5C 00043D5C  B0 03 00 3C */	sth r0, 0x3c(r3)
/* 80048E60 00043D60  A0 04 07 FE */	lhz r0, 0x7fe(r4)
/* 80048E64 00043D64  B0 03 00 3E */	sth r0, 0x3e(r3)
/* 80048E68 00043D68  A0 04 08 00 */	lhz r0, 0x800(r4)
/* 80048E6C 00043D6C  B0 03 00 40 */	sth r0, 0x40(r3)
/* 80048E70 00043D70  A0 04 08 02 */	lhz r0, 0x802(r4)
/* 80048E74 00043D74  B0 03 00 42 */	sth r0, 0x42(r3)
/* 80048E78 00043D78  80 E4 07 CC */	lwz r7, 0x7cc(r4)
/* 80048E7C 00043D7C  38 84 00 38 */	addi r4, r4, 0x38
/* 80048E80 00043D80  88 07 00 00 */	lbz r0, 0(r7)
/* 80048E84 00043D84  B0 03 00 36 */	sth r0, 0x36(r3)
/* 80048E88 00043D88  A0 05 08 40 */	lhz r0, 0x840(r5)
/* 80048E8C 00043D8C  B0 03 00 38 */	sth r0, 0x38(r3)
/* 80048E90 00043D90  A0 05 08 44 */	lhz r0, 0x844(r5)
/* 80048E94 00043D94  38 A5 00 02 */	addi r5, r5, 2
/* 80048E98 00043D98  B0 03 00 3A */	sth r0, 0x3a(r3)
/* 80048E9C 00043D9C  38 63 00 44 */	addi r3, r3, 0x44
lbl_80048EA0:
/* 80048EA0 00043DA0  80 1F 07 C4 */	lwz r0, 0x7c4(r31)
/* 80048EA4 00043DA4  7C 06 00 00 */	cmpw r6, r0
/* 80048EA8 00043DA8  41 80 FF 04 */	blt lbl_80048DAC
/* 80048EAC 00043DAC  48 0A 8A 15 */	bl OSDisableInterrupts
/* 80048EB0 00043DB0  80 1F 07 C0 */	lwz r0, 0x7c0(r31)
/* 80048EB4 00043DB4  7C 7E 1B 78 */	mr r30, r3
/* 80048EB8 00043DB8  2C 00 00 00 */	cmpwi r0, 0
/* 80048EBC 00043DBC  41 82 00 BC */	beq lbl_80048F78
/* 80048EC0 00043DC0  80 A1 00 0C */	lwz r5, 0xc(r1)
/* 80048EC4 00043DC4  7C 03 03 78 */	mr r3, r0
/* 80048EC8 00043DC8  38 81 00 18 */	addi r4, r1, 0x18
/* 80048ECC 00043DCC  48 00 35 89 */	bl Setup__Q44nw4r3snd6detail5VoiceFRCQ44nw4r3snd6detail8WaveDataUl
/* 80048ED0 00043DD0  80 7F 07 C0 */	lwz r3, 0x7c0(r31)
/* 80048ED4 00043DD4  38 80 00 01 */	li r4, 1
/* 80048ED8 00043DD8  48 00 40 E5 */	bl SetVoiceType__Q44nw4r3snd6detail5VoiceFQ54nw4r3snd6detail7AxVoice9VoiceType
/* 80048EDC 00043DDC  80 7F 00 98 */	lwz r3, 0x98(r31)
/* 80048EE0 00043DE0  80 81 00 10 */	lwz r4, 0x10(r1)
/* 80048EE4 00043DE4  38 03 FF FE */	addi r0, r3, -2
/* 80048EE8 00043DE8  7C 04 00 40 */	cmplw r4, r0
/* 80048EEC 00043DEC  40 82 00 14 */	bne lbl_80048F00
/* 80048EF0 00043DF0  7F E3 FB 78 */	mr r3, r31
/* 80048EF4 00043DF4  38 80 00 01 */	li r4, 1
/* 80048EF8 00043DF8  48 00 14 3D */	bl UpdateDataLoopAddress__Q44nw4r3snd6detail10StrmPlayerFl
/* 80048EFC 00043DFC  48 00 00 1C */	b lbl_80048F18
lbl_80048F00:
/* 80048F00 00043E00  38 03 FF FF */	addi r0, r3, -1
/* 80048F04 00043E04  7C 04 00 40 */	cmplw r4, r0
/* 80048F08 00043E08  40 82 00 10 */	bne lbl_80048F18
/* 80048F0C 00043E0C  7F E3 FB 78 */	mr r3, r31
/* 80048F10 00043E10  38 80 00 00 */	li r4, 0
/* 80048F14 00043E14  48 00 14 21 */	bl UpdateDataLoopAddress__Q44nw4r3snd6detail10StrmPlayerFl
lbl_80048F18:
/* 80048F18 00043E18  80 7F 07 C0 */	lwz r3, 0x7c0(r31)
/* 80048F1C 00043E1C  48 00 37 E9 */	bl Start__Q44nw4r3snd6detail5VoiceFv
/* 80048F20 00043E20  48 0A 89 A1 */	bl OSDisableInterrupts
/* 80048F24 00043E24  88 1F 00 BF */	lbz r0, 0xbf(r31)
/* 80048F28 00043E28  7C 7D 1B 78 */	mr r29, r3
/* 80048F2C 00043E2C  3B 80 00 00 */	li r28, 0
/* 80048F30 00043E30  2C 00 00 00 */	cmpwi r0, 0
/* 80048F34 00043E34  41 82 00 08 */	beq lbl_80048F3C
/* 80048F38 00043E38  3B 80 00 01 */	li r28, 1
lbl_80048F3C:
/* 80048F3C 00043E3C  88 1F 00 C1 */	lbz r0, 0xc1(r31)
/* 80048F40 00043E40  2C 00 00 00 */	cmpwi r0, 0
/* 80048F44 00043E44  41 82 00 08 */	beq lbl_80048F4C
/* 80048F48 00043E48  3B 80 00 01 */	li r28, 1
lbl_80048F4C:
/* 80048F4C 00043E4C  88 1F 00 C0 */	lbz r0, 0xc0(r31)
/* 80048F50 00043E50  7C 1C 00 40 */	cmplw r28, r0
/* 80048F54 00043E54  41 82 00 1C */	beq lbl_80048F70
/* 80048F58 00043E58  80 7F 07 C0 */	lwz r3, 0x7c0(r31)
/* 80048F5C 00043E5C  2C 03 00 00 */	cmpwi r3, 0
/* 80048F60 00043E60  41 82 00 0C */	beq lbl_80048F6C
/* 80048F64 00043E64  7F 84 E3 78 */	mr r4, r28
/* 80048F68 00043E68  48 00 38 8D */	bl Pause__Q44nw4r3snd6detail5VoiceFb
lbl_80048F6C:
/* 80048F6C 00043E6C  9B 9F 00 C0 */	stb r28, 0xc0(r31)
lbl_80048F70:
/* 80048F70 00043E70  7F A3 EB 78 */	mr r3, r29
/* 80048F74 00043E74  48 0A 89 75 */	bl OSRestoreInterrupts
lbl_80048F78:
/* 80048F78 00043E78  38 00 00 01 */	li r0, 1
/* 80048F7C 00043E7C  7F C3 F3 78 */	mr r3, r30
/* 80048F80 00043E80  98 1F 00 BA */	stb r0, 0xba(r31)
/* 80048F84 00043E84  48 0A 89 65 */	bl OSRestoreInterrupts
lbl_80048F88:
/* 80048F88 00043E88  4B FF E9 51 */	bl GetInstance__Q44nw4r3snd6detail11SoundThreadFv
/* 80048F8C 00043E8C  38 63 03 54 */	addi r3, r3, 0x354
/* 80048F90 00043E90  48 0A 9C C9 */	bl OSUnlockMutex
/* 80048F94 00043E94  38 60 00 01 */	li r3, 1
lbl_80048F98:
/* 80048F98 00043E98  80 01 00 C4 */	lwz r0, 0xc4(r1)
/* 80048F9C 00043E9C  83 E1 00 BC */	lwz r31, 0xbc(r1)
/* 80048FA0 00043EA0  83 C1 00 B8 */	lwz r30, 0xb8(r1)
/* 80048FA4 00043EA4  83 A1 00 B4 */	lwz r29, 0xb4(r1)
/* 80048FA8 00043EA8  83 81 00 B0 */	lwz r28, 0xb0(r1)
/* 80048FAC 00043EAC  7C 08 03 A6 */	mtlr r0
/* 80048FB0 00043EB0  38 21 00 C0 */	addi r1, r1, 0xc0
/* 80048FB4 00043EB4  4E 80 00 20 */	blr 

.global Stop__Q44nw4r3snd6detail10StrmPlayerFv
Stop__Q44nw4r3snd6detail10StrmPlayerFv:
/* 80048FB8 00043EB8  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80048FBC 00043EBC  7C 08 02 A6 */	mflr r0
/* 80048FC0 00043EC0  90 01 00 24 */	stw r0, 0x24(r1)
/* 80048FC4 00043EC4  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80048FC8 00043EC8  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80048FCC 00043ECC  93 A1 00 14 */	stw r29, 0x14(r1)
/* 80048FD0 00043ED0  93 81 00 10 */	stw r28, 0x10(r1)
/* 80048FD4 00043ED4  7C 7C 1B 78 */	mr r28, r3
/* 80048FD8 00043ED8  4B FF E9 01 */	bl GetInstance__Q44nw4r3snd6detail11SoundThreadFv
/* 80048FDC 00043EDC  38 63 03 54 */	addi r3, r3, 0x354
/* 80048FE0 00043EE0  48 0A 9B 9D */	bl OSLockMutex
/* 80048FE4 00043EE4  80 7C 07 C0 */	lwz r3, 0x7c0(r28)
/* 80048FE8 00043EE8  2C 03 00 00 */	cmpwi r3, 0
/* 80048FEC 00043EEC  41 82 00 08 */	beq lbl_80048FF4
/* 80048FF0 00043EF0  48 00 37 35 */	bl Stop__Q44nw4r3snd6detail5VoiceFv
lbl_80048FF4:
/* 80048FF4 00043EF4  7F 83 E3 78 */	mr r3, r28
/* 80048FF8 00043EF8  48 00 0B 1D */	bl FreeChannels__Q44nw4r3snd6detail10StrmPlayerFv
/* 80048FFC 00043EFC  88 1C 00 B9 */	lbz r0, 0xb9(r28)
/* 80049000 00043F00  2C 00 00 00 */	cmpwi r0, 0
/* 80049004 00043F04  41 82 00 20 */	beq lbl_80049024
/* 80049008 00043F08  2C 1C 00 00 */	cmpwi r28, 0
/* 8004900C 00043F0C  7F 9D E3 78 */	mr r29, r28
/* 80049010 00043F10  41 82 00 08 */	beq lbl_80049018
/* 80049014 00043F14  3B BC 00 74 */	addi r29, r28, 0x74
lbl_80049018:
/* 80049018 00043F18  4B FF E8 C1 */	bl GetInstance__Q44nw4r3snd6detail11SoundThreadFv
/* 8004901C 00043F1C  7F A4 EB 78 */	mr r4, r29
/* 80049020 00043F20  4B FF ED ED */	bl UnregisterPlayerCallback__Q44nw4r3snd6detail11SoundThreadFPQ54nw4r3snd6detail11SoundThread14PlayerCallback
lbl_80049024:
/* 80049024 00043F24  4B FF E8 B5 */	bl GetInstance__Q44nw4r3snd6detail11SoundThreadFv
/* 80049028 00043F28  38 63 03 54 */	addi r3, r3, 0x354
/* 8004902C 00043F2C  48 0A 9C 2D */	bl OSUnlockMutex
/* 80049030 00043F30  48 00 1F C9 */	bl GetInstance__Q44nw4r3snd6detail11TaskManagerFv
/* 80049034 00043F34  38 9C 01 08 */	addi r4, r28, 0x108
/* 80049038 00043F38  48 00 24 99 */	bl CancelTask__Q44nw4r3snd6detail11TaskManagerFPQ44nw4r3snd6detail4Task
/* 8004903C 00043F3C  48 0A 88 85 */	bl OSDisableInterrupts
/* 80049040 00043F40  80 1C 01 28 */	lwz r0, 0x128(r28)
/* 80049044 00043F44  7C 7F 1B 78 */	mr r31, r3
/* 80049048 00043F48  2C 00 00 00 */	cmpwi r0, 0
/* 8004904C 00043F4C  41 82 00 28 */	beq lbl_80049074
/* 80049050 00043F50  3B DC 01 2C */	addi r30, r28, 0x12c
/* 80049054 00043F54  48 00 00 14 */	b lbl_80049068
lbl_80049058:
/* 80049058 00043F58  83 BE 00 04 */	lwz r29, 4(r30)
/* 8004905C 00043F5C  48 00 1F 9D */	bl GetInstance__Q44nw4r3snd6detail11TaskManagerFv
/* 80049060 00043F60  38 9D FF D4 */	addi r4, r29, -44
/* 80049064 00043F64  48 00 24 6D */	bl CancelTask__Q44nw4r3snd6detail11TaskManagerFPQ44nw4r3snd6detail4Task
lbl_80049068:
/* 80049068 00043F68  80 1C 01 28 */	lwz r0, 0x128(r28)
/* 8004906C 00043F6C  2C 00 00 00 */	cmpwi r0, 0
/* 80049070 00043F70  40 82 FF E8 */	bne lbl_80049058
lbl_80049074:
/* 80049074 00043F74  7F E3 FB 78 */	mr r3, r31
/* 80049078 00043F78  48 0A 88 71 */	bl OSRestoreInterrupts
/* 8004907C 00043F7C  80 7C 07 BC */	lwz r3, 0x7bc(r28)
/* 80049080 00043F80  2C 03 00 00 */	cmpwi r3, 0
/* 80049084 00043F84  41 82 00 1C */	beq lbl_800490A0
/* 80049088 00043F88  81 83 00 00 */	lwz r12, 0(r3)
/* 8004908C 00043F8C  81 8C 00 10 */	lwz r12, 0x10(r12)
/* 80049090 00043F90  7D 89 03 A6 */	mtctr r12
/* 80049094 00043F94  4E 80 04 21 */	bctrl 
/* 80049098 00043F98  38 00 00 00 */	li r0, 0
/* 8004909C 00043F9C  90 1C 07 BC */	stw r0, 0x7bc(r28)
lbl_800490A0:
/* 800490A0 00043FA0  38 00 00 00 */	li r0, 0
/* 800490A4 00043FA4  98 1C 00 BA */	stb r0, 0xba(r28)
/* 800490A8 00043FA8  98 1C 00 BB */	stb r0, 0xbb(r28)
/* 800490AC 00043FAC  98 1C 00 B9 */	stb r0, 0xb9(r28)
/* 800490B0 00043FB0  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800490B4 00043FB4  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 800490B8 00043FB8  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 800490BC 00043FBC  83 81 00 10 */	lwz r28, 0x10(r1)
/* 800490C0 00043FC0  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800490C4 00043FC4  7C 08 03 A6 */	mtlr r0
/* 800490C8 00043FC8  38 21 00 20 */	addi r1, r1, 0x20
/* 800490CC 00043FCC  4E 80 00 20 */	blr 

.global Pause__Q44nw4r3snd6detail10StrmPlayerFb
Pause__Q44nw4r3snd6detail10StrmPlayerFb:
/* 800490D0 00043FD0  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800490D4 00043FD4  7C 08 02 A6 */	mflr r0
/* 800490D8 00043FD8  90 01 00 24 */	stw r0, 0x24(r1)
/* 800490DC 00043FDC  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800490E0 00043FE0  93 C1 00 18 */	stw r30, 0x18(r1)
/* 800490E4 00043FE4  7C 9E 23 78 */	mr r30, r4
/* 800490E8 00043FE8  93 A1 00 14 */	stw r29, 0x14(r1)
/* 800490EC 00043FEC  7C 7D 1B 78 */	mr r29, r3
/* 800490F0 00043FF0  4B FF E7 E9 */	bl GetInstance__Q44nw4r3snd6detail11SoundThreadFv
/* 800490F4 00043FF4  38 63 03 54 */	addi r3, r3, 0x354
/* 800490F8 00043FF8  48 0A 9A 85 */	bl OSLockMutex
/* 800490FC 00043FFC  2C 1E 00 00 */	cmpwi r30, 0
/* 80049100 00044000  9B DD 00 BF */	stb r30, 0xbf(r29)
/* 80049104 00044004  41 82 00 0C */	beq lbl_80049110
/* 80049108 00044008  38 00 00 01 */	li r0, 1
/* 8004910C 0004400C  98 1D 00 C1 */	stb r0, 0xc1(r29)
lbl_80049110:
/* 80049110 00044010  48 0A 87 B1 */	bl OSDisableInterrupts
/* 80049114 00044014  88 1D 00 BF */	lbz r0, 0xbf(r29)
/* 80049118 00044018  7C 7F 1B 78 */	mr r31, r3
/* 8004911C 0004401C  3B C0 00 00 */	li r30, 0
/* 80049120 00044020  2C 00 00 00 */	cmpwi r0, 0
/* 80049124 00044024  41 82 00 08 */	beq lbl_8004912C
/* 80049128 00044028  3B C0 00 01 */	li r30, 1
lbl_8004912C:
/* 8004912C 0004402C  88 1D 00 C1 */	lbz r0, 0xc1(r29)
/* 80049130 00044030  2C 00 00 00 */	cmpwi r0, 0
/* 80049134 00044034  41 82 00 08 */	beq lbl_8004913C
/* 80049138 00044038  3B C0 00 01 */	li r30, 1
lbl_8004913C:
/* 8004913C 0004403C  88 1D 00 C0 */	lbz r0, 0xc0(r29)
/* 80049140 00044040  7C 1E 00 40 */	cmplw r30, r0
/* 80049144 00044044  41 82 00 1C */	beq lbl_80049160
/* 80049148 00044048  80 7D 07 C0 */	lwz r3, 0x7c0(r29)
/* 8004914C 0004404C  2C 03 00 00 */	cmpwi r3, 0
/* 80049150 00044050  41 82 00 0C */	beq lbl_8004915C
/* 80049154 00044054  7F C4 F3 78 */	mr r4, r30
/* 80049158 00044058  48 00 36 9D */	bl Pause__Q44nw4r3snd6detail5VoiceFb
lbl_8004915C:
/* 8004915C 0004405C  9B DD 00 C0 */	stb r30, 0xc0(r29)
lbl_80049160:
/* 80049160 00044060  7F E3 FB 78 */	mr r3, r31
/* 80049164 00044064  48 0A 87 85 */	bl OSRestoreInterrupts
/* 80049168 00044068  4B FF E7 71 */	bl GetInstance__Q44nw4r3snd6detail11SoundThreadFv
/* 8004916C 0004406C  38 63 03 54 */	addi r3, r3, 0x354
/* 80049170 00044070  48 0A 9A E9 */	bl OSUnlockMutex
/* 80049174 00044074  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80049178 00044078  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8004917C 0004407C  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80049180 00044080  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 80049184 00044084  7C 08 03 A6 */	mtlr r0
/* 80049188 00044088  38 21 00 20 */	addi r1, r1, 0x20
/* 8004918C 0004408C  4E 80 00 20 */	blr 

.global InitParam__Q44nw4r3snd6detail10StrmPlayerFv
InitParam__Q44nw4r3snd6detail10StrmPlayerFv:
/* 80049190 00044090  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80049194 00044094  7C 08 02 A6 */	mflr r0
/* 80049198 00044098  90 01 00 14 */	stw r0, 0x14(r1)
/* 8004919C 0004409C  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800491A0 000440A0  7C 7F 1B 78 */	mr r31, r3
/* 800491A4 000440A4  4B FE CF C1 */	bl InitParam__Q44nw4r3snd6detail11BasicPlayerFv
/* 800491A8 000440A8  38 60 00 00 */	li r3, 0
/* 800491AC 000440AC  38 00 00 01 */	li r0, 1
/* 800491B0 000440B0  98 7F 00 BA */	stb r3, 0xba(r31)
/* 800491B4 000440B4  98 7F 00 BB */	stb r3, 0xbb(r31)
/* 800491B8 000440B8  98 7F 00 C6 */	stb r3, 0xc6(r31)
/* 800491BC 000440BC  98 7F 00 BF */	stb r3, 0xbf(r31)
/* 800491C0 000440C0  98 7F 00 C0 */	stb r3, 0xc0(r31)
/* 800491C4 000440C4  98 7F 00 C1 */	stb r3, 0xc1(r31)
/* 800491C8 000440C8  98 7F 00 C2 */	stb r3, 0xc2(r31)
/* 800491CC 000440CC  98 7F 00 C5 */	stb r3, 0xc5(r31)
/* 800491D0 000440D0  98 7F 00 C3 */	stb r3, 0xc3(r31)
/* 800491D4 000440D4  98 7F 00 C4 */	stb r3, 0xc4(r31)
/* 800491D8 000440D8  90 7F 07 C4 */	stw r3, 0x7c4(r31)
/* 800491DC 000440DC  90 7F 00 C8 */	stw r3, 0xc8(r31)
/* 800491E0 000440E0  90 1F 07 C8 */	stw r0, 0x7c8(r31)
/* 800491E4 000440E4  90 7F 07 CC */	stw r3, 0x7cc(r31)
/* 800491E8 000440E8  90 7F 07 D0 */	stw r3, 0x7d0(r31)
/* 800491EC 000440EC  90 7F 08 04 */	stw r3, 0x804(r31)
/* 800491F0 000440F0  90 7F 08 08 */	stw r3, 0x808(r31)
/* 800491F4 000440F4  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 800491F8 000440F8  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800491FC 000440FC  7C 08 03 A6 */	mtlr r0
/* 80049200 00044100  38 21 00 10 */	addi r1, r1, 0x10
/* 80049204 00044104  4E 80 00 20 */	blr 

.global LoadHeader__Q44nw4r3snd6detail10StrmPlayerFPQ34nw4r2ut10FileStreamQ54nw4r3snd6detail10StrmPlayer15StartOffsetTypei
LoadHeader__Q44nw4r3snd6detail10StrmPlayerFPQ34nw4r2ut10FileStreamQ54nw4r3snd6detail10StrmPlayer15StartOffsetTypei:
/* 80049208 00044108  94 21 FD F0 */	stwu r1, -0x210(r1)
/* 8004920C 0004410C  7C 08 02 A6 */	mflr r0
/* 80049210 00044110  90 01 02 14 */	stw r0, 0x214(r1)
/* 80049214 00044114  39 61 02 10 */	addi r11, r1, 0x210
/* 80049218 00044118  48 06 8B 29 */	bl _savegpr_26
/* 8004921C 0004411C  3F E0 80 3F */	lis r31, sLoadBufferMutex__Q44nw4r3snd6detail10StrmPlayer@ha
/* 80049220 00044120  7C 7D 1B 78 */	mr r29, r3
/* 80049224 00044124  3B FF BC 40 */	addi r31, r31, sLoadBufferMutex__Q44nw4r3snd6detail10StrmPlayer@l
/* 80049228 00044128  7C 9A 23 78 */	mr r26, r4
/* 8004922C 0004412C  7C BB 2B 78 */	mr r27, r5
/* 80049230 00044130  7C DE 33 78 */	mr r30, r6
/* 80049234 00044134  7F E3 FB 78 */	mr r3, r31
/* 80049238 00044138  48 0A 99 45 */	bl OSLockMutex
/* 8004923C 0004413C  93 41 00 08 */	stw r26, 8(r1)
/* 80049240 00044140  38 61 00 0C */	addi r3, r1, 0xc
/* 80049244 00044144  4B FF EF A9 */	bl __ct__Q44nw4r3snd6detail14StrmFileReaderFv
/* 80049248 00044148  3C 80 80 3E */	lis r4, sLoadBuffer__Q44nw4r3snd6detail10StrmPlayer@ha
/* 8004924C 0004414C  38 61 00 08 */	addi r3, r1, 8
/* 80049250 00044150  38 84 7C 20 */	addi r4, r4, sLoadBuffer__Q44nw4r3snd6detail10StrmPlayer@l
/* 80049254 00044154  38 A0 02 00 */	li r5, 0x200
/* 80049258 00044158  4B FF F1 F9 */	bl LoadFileHeader__Q44nw4r3snd6detail14StrmFileLoaderFPvUl
/* 8004925C 0004415C  2C 03 00 00 */	cmpwi r3, 0
/* 80049260 00044160  40 82 00 14 */	bne lbl_80049274
/* 80049264 00044164  7F E3 FB 78 */	mr r3, r31
/* 80049268 00044168  48 0A 99 F1 */	bl OSUnlockMutex
/* 8004926C 0004416C  38 60 00 00 */	li r3, 0
/* 80049270 00044170  48 00 02 0C */	b lbl_8004947C
lbl_80049274:
/* 80049274 00044174  80 61 00 0C */	lwz r3, 0xc(r1)
/* 80049278 00044178  7C 03 00 D0 */	neg r0, r3
/* 8004927C 0004417C  7C 00 1B 78 */	or r0, r0, r3
/* 80049280 00044180  54 00 0F FF */	rlwinm. r0, r0, 1, 0x1f, 0x1f
/* 80049284 00044184  40 82 00 08 */	bne lbl_8004928C
/* 80049288 00044188  48 00 00 10 */	b lbl_80049298
lbl_8004928C:
/* 8004928C 0004418C  38 61 00 0C */	addi r3, r1, 0xc
/* 80049290 00044190  38 81 00 18 */	addi r4, r1, 0x18
/* 80049294 00044194  4B FF EF 69 */	bl ReadStrmInfo__Q44nw4r3snd6detail14StrmFileReaderCFPQ44nw4r3snd6detail8StrmInfo
lbl_80049298:
/* 80049298 00044198  3B 40 00 00 */	li r26, 0
/* 8004929C 0004419C  3B 80 00 00 */	li r28, 0
/* 800492A0 000441A0  48 00 00 38 */	b lbl_800492D8
lbl_800492A4:
/* 800492A4 000441A4  80 61 00 0C */	lwz r3, 0xc(r1)
/* 800492A8 000441A8  7C 03 00 D0 */	neg r0, r3
/* 800492AC 000441AC  7C 00 1B 78 */	or r0, r0, r3
/* 800492B0 000441B0  54 00 0F FF */	rlwinm. r0, r0, 1, 0x1f, 0x1f
/* 800492B4 000441B4  40 82 00 08 */	bne lbl_800492BC
/* 800492B8 000441B8  48 00 00 18 */	b lbl_800492D0
lbl_800492BC:
/* 800492BC 000441BC  38 81 00 50 */	addi r4, r1, 0x50
/* 800492C0 000441C0  7F 45 D3 78 */	mr r5, r26
/* 800492C4 000441C4  38 61 00 0C */	addi r3, r1, 0xc
/* 800492C8 000441C8  7C 84 E2 14 */	add r4, r4, r28
/* 800492CC 000441CC  4B FF EF FD */	bl ReadAdpcmInfo__Q44nw4r3snd6detail14StrmFileReaderCFPQ44nw4r3snd6detail9AdpcmInfoi
lbl_800492D0:
/* 800492D0 000441D0  3B 5A 00 01 */	addi r26, r26, 1
/* 800492D4 000441D4  3B 9C 00 30 */	addi r28, r28, 0x30
lbl_800492D8:
/* 800492D8 000441D8  88 01 00 1A */	lbz r0, 0x1a(r1)
/* 800492DC 000441DC  7C 1A 00 00 */	cmpw r26, r0
/* 800492E0 000441E0  41 80 FF C4 */	blt lbl_800492A4
/* 800492E4 000441E4  88 01 00 18 */	lbz r0, 0x18(r1)
/* 800492E8 000441E8  28 00 00 02 */	cmplwi r0, 2
/* 800492EC 000441EC  40 82 00 A8 */	bne lbl_80049394
/* 800492F0 000441F0  2C 1E 00 00 */	cmpwi r30, 0
/* 800492F4 000441F4  40 82 00 50 */	bne lbl_80049344
/* 800492F8 000441F8  39 01 00 74 */	addi r8, r1, 0x74
/* 800492FC 000441FC  38 E1 01 D0 */	addi r7, r1, 0x1d0
/* 80049300 00044200  38 C1 00 76 */	addi r6, r1, 0x76
/* 80049304 00044204  38 A1 01 E0 */	addi r5, r1, 0x1e0
/* 80049308 00044208  39 20 00 00 */	li r9, 0
/* 8004930C 0004420C  38 60 00 00 */	li r3, 0
/* 80049310 00044210  38 80 00 00 */	li r4, 0
/* 80049314 00044214  48 00 00 20 */	b lbl_80049334
lbl_80049318:
/* 80049318 00044218  7C 08 1A 2E */	lhzx r0, r8, r3
/* 8004931C 0004421C  39 29 00 01 */	addi r9, r9, 1
/* 80049320 00044220  7C 07 23 2E */	sthx r0, r7, r4
/* 80049324 00044224  7C 06 1A 2E */	lhzx r0, r6, r3
/* 80049328 00044228  38 63 00 30 */	addi r3, r3, 0x30
/* 8004932C 0004422C  7C 05 23 2E */	sthx r0, r5, r4
/* 80049330 00044230  38 84 00 02 */	addi r4, r4, 2
lbl_80049334:
/* 80049334 00044234  88 01 00 1A */	lbz r0, 0x1a(r1)
/* 80049338 00044238  7C 09 00 00 */	cmpw r9, r0
/* 8004933C 0004423C  41 80 FF DC */	blt lbl_80049318
/* 80049340 00044240  48 00 00 54 */	b lbl_80049394
lbl_80049344:
/* 80049344 00044244  2C 1B 00 00 */	cmpwi r27, 0
/* 80049348 00044248  40 82 00 08 */	bne lbl_80049350
/* 8004934C 0004424C  48 00 00 2C */	b lbl_80049378
lbl_80049350:
/* 80049350 00044250  2C 1B 00 01 */	cmpwi r27, 1
/* 80049354 00044254  40 82 00 24 */	bne lbl_80049378
/* 80049358 00044258  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8004935C 0004425C  3C 60 10 62 */	lis r3, 0x10624DD3@ha
/* 80049360 00044260  38 63 4D D3 */	addi r3, r3, 0x10624DD3@l
/* 80049364 00044264  7C 1E 01 D6 */	mullw r0, r30, r0
/* 80049368 00044268  7C 03 00 96 */	mulhw r0, r3, r0
/* 8004936C 0004426C  7C 00 36 70 */	srawi r0, r0, 6
/* 80049370 00044270  54 03 0F FE */	srwi r3, r0, 0x1f
/* 80049374 00044274  7F C0 1A 14 */	add r30, r0, r3
lbl_80049378:
/* 80049378 00044278  80 01 00 38 */	lwz r0, 0x38(r1)
/* 8004937C 0004427C  38 61 00 08 */	addi r3, r1, 8
/* 80049380 00044280  88 E1 00 1A */	lbz r7, 0x1a(r1)
/* 80049384 00044284  38 81 01 D0 */	addi r4, r1, 0x1d0
/* 80049388 00044288  7C DE 03 D6 */	divw r6, r30, r0
/* 8004938C 0004428C  38 A1 01 E0 */	addi r5, r1, 0x1e0
/* 80049390 00044290  4B FF F2 85 */	bl ReadAdpcBlockData__Q44nw4r3snd6detail14StrmFileLoaderFPUsPUsii
lbl_80049394:
/* 80049394 00044294  7F A3 EB 78 */	mr r3, r29
/* 80049398 00044298  38 81 00 18 */	addi r4, r1, 0x18
/* 8004939C 0004429C  48 00 03 29 */	bl SetupPlayer__Q44nw4r3snd6detail10StrmPlayerFPCQ54nw4r3snd6detail10StrmPlayer10StrmHeader
/* 800493A0 000442A0  2C 03 00 00 */	cmpwi r3, 0
/* 800493A4 000442A4  40 82 00 14 */	bne lbl_800493B8
/* 800493A8 000442A8  7F E3 FB 78 */	mr r3, r31
/* 800493AC 000442AC  48 0A 98 AD */	bl OSUnlockMutex
/* 800493B0 000442B0  38 60 00 00 */	li r3, 0
/* 800493B4 000442B4  48 00 00 C8 */	b lbl_8004947C
lbl_800493B8:
/* 800493B8 000442B8  38 00 00 00 */	li r0, 0
/* 800493BC 000442BC  3B 40 00 00 */	li r26, 0
/* 800493C0 000442C0  90 1D 00 CC */	stw r0, 0xcc(r29)
/* 800493C4 000442C4  48 00 00 28 */	b lbl_800493EC
lbl_800493C8:
/* 800493C8 000442C8  7F A3 EB 78 */	mr r3, r29
/* 800493CC 000442CC  48 00 11 11 */	bl UpdateLoadingBlockIndex__Q44nw4r3snd6detail10StrmPlayerFv
/* 800493D0 000442D0  80 7D 00 CC */	lwz r3, 0xcc(r29)
/* 800493D4 000442D4  88 1D 00 C6 */	lbz r0, 0xc6(r29)
/* 800493D8 000442D8  38 63 00 01 */	addi r3, r3, 1
/* 800493DC 000442DC  2C 00 00 00 */	cmpwi r0, 0
/* 800493E0 000442E0  90 7D 00 CC */	stw r3, 0xcc(r29)
/* 800493E4 000442E4  40 82 00 14 */	bne lbl_800493F8
/* 800493E8 000442E8  3B 5A 00 01 */	addi r26, r26, 1
lbl_800493EC:
/* 800493EC 000442EC  80 1D 00 DC */	lwz r0, 0xdc(r29)
/* 800493F0 000442F0  7C 1A 00 00 */	cmpw r26, r0
/* 800493F4 000442F4  41 80 FF D4 */	blt lbl_800493C8
lbl_800493F8:
/* 800493F8 000442F8  80 7D 00 98 */	lwz r3, 0x98(r29)
/* 800493FC 000442FC  28 03 00 02 */	cmplwi r3, 2
/* 80049400 00044300  41 81 00 70 */	bgt lbl_80049470
/* 80049404 00044304  88 1D 00 81 */	lbz r0, 0x81(r29)
/* 80049408 00044308  2C 00 00 00 */	cmpwi r0, 0
/* 8004940C 0004430C  40 82 00 64 */	bne lbl_80049470
/* 80049410 00044310  3B 63 FF FF */	addi r27, r3, -1
/* 80049414 00044314  48 0A 84 AD */	bl OSDisableInterrupts
/* 80049418 00044318  7C 7C 1B 78 */	mr r28, r3
/* 8004941C 0004431C  3B 40 00 00 */	li r26, 0
/* 80049420 00044320  3B C0 00 00 */	li r30, 0
/* 80049424 00044324  48 00 00 30 */	b lbl_80049454
lbl_80049428:
/* 80049428 00044328  80 1D 00 A0 */	lwz r0, 0xa0(r29)
/* 8004942C 0004432C  7C BD F2 14 */	add r5, r29, r30
/* 80049430 00044330  80 DD 00 A8 */	lwz r6, 0xa8(r29)
/* 80049434 00044334  7F 44 D3 78 */	mr r4, r26
/* 80049438 00044338  7C 1B 01 D6 */	mullw r0, r27, r0
/* 8004943C 0004433C  80 7D 07 C0 */	lwz r3, 0x7c0(r29)
/* 80049440 00044340  80 A5 07 CC */	lwz r5, 0x7cc(r5)
/* 80049444 00044344  7C C6 02 14 */	add r6, r6, r0
/* 80049448 00044348  48 00 3B 01 */	bl StopAtPoint__Q44nw4r3snd6detail5VoiceFiPCvUl
/* 8004944C 0004434C  3B 5A 00 01 */	addi r26, r26, 1
/* 80049450 00044350  3B DE 00 38 */	addi r30, r30, 0x38
lbl_80049454:
/* 80049454 00044354  80 1D 07 C4 */	lwz r0, 0x7c4(r29)
/* 80049458 00044358  7C 1A 00 00 */	cmpw r26, r0
/* 8004945C 0004435C  41 80 FF CC */	blt lbl_80049428
/* 80049460 00044360  7F 83 E3 78 */	mr r3, r28
/* 80049464 00044364  48 0A 84 85 */	bl OSRestoreInterrupts
/* 80049468 00044368  38 00 00 01 */	li r0, 1
/* 8004946C 0004436C  98 1D 00 C5 */	stb r0, 0xc5(r29)
lbl_80049470:
/* 80049470 00044370  7F E3 FB 78 */	mr r3, r31
/* 80049474 00044374  48 0A 97 E5 */	bl OSUnlockMutex
/* 80049478 00044378  38 60 00 01 */	li r3, 1
lbl_8004947C:
/* 8004947C 0004437C  39 61 02 10 */	addi r11, r1, 0x210
/* 80049480 00044380  48 06 89 0D */	bl _restgpr_26
/* 80049484 00044384  80 01 02 14 */	lwz r0, 0x214(r1)
/* 80049488 00044388  7C 08 03 A6 */	mtlr r0
/* 8004948C 0004438C  38 21 02 10 */	addi r1, r1, 0x210
/* 80049490 00044390  4E 80 00 20 */	blr 

.global LoadStreamData__Q44nw4r3snd6detail10StrmPlayerFPQ34nw4r2ut10FileStreamiUlUlib
LoadStreamData__Q44nw4r3snd6detail10StrmPlayerFPQ34nw4r2ut10FileStreamiUlUlib:
/* 80049494 00044394  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 80049498 00044398  7C 08 02 A6 */	mflr r0
/* 8004949C 0004439C  90 01 00 44 */	stw r0, 0x44(r1)
/* 800494A0 000443A0  39 61 00 40 */	addi r11, r1, 0x40
/* 800494A4 000443A4  48 06 88 85 */	bl _savegpr_20
/* 800494A8 000443A8  7C 97 23 78 */	mr r23, r4
/* 800494AC 000443AC  7C 79 1B 78 */	mr r25, r3
/* 800494B0 000443B0  81 97 00 00 */	lwz r12, 0(r23)
/* 800494B4 000443B4  7E E3 BB 78 */	mr r3, r23
/* 800494B8 000443B8  7C B6 2B 78 */	mr r22, r5
/* 800494BC 000443BC  7C D4 33 78 */	mr r20, r6
/* 800494C0 000443C0  81 8C 00 08 */	lwz r12, 8(r12)
/* 800494C4 000443C4  7C FA 3B 78 */	mr r26, r7
/* 800494C8 000443C8  7D 1B 43 78 */	mr r27, r8
/* 800494CC 000443CC  7D 3C 4B 78 */	mr r28, r9
/* 800494D0 000443D0  3A AD 96 70 */	addi r21, r13, typeInfo__Q34nw4r2ut13DvdFileStream-_SDA_BASE_
/* 800494D4 000443D4  7D 89 03 A6 */	mtctr r12
/* 800494D8 000443D8  4E 80 04 21 */	bctrl 
/* 800494DC 000443DC  48 00 00 18 */	b lbl_800494F4
lbl_800494E0:
/* 800494E0 000443E0  7C 03 A8 40 */	cmplw r3, r21
/* 800494E4 000443E4  40 82 00 0C */	bne lbl_800494F0
/* 800494E8 000443E8  38 00 00 01 */	li r0, 1
/* 800494EC 000443EC  48 00 00 14 */	b lbl_80049500
lbl_800494F0:
/* 800494F0 000443F0  80 63 00 00 */	lwz r3, 0(r3)
lbl_800494F4:
/* 800494F4 000443F4  2C 03 00 00 */	cmpwi r3, 0
/* 800494F8 000443F8  40 82 FF E8 */	bne lbl_800494E0
/* 800494FC 000443FC  38 00 00 00 */	li r0, 0
lbl_80049500:
/* 80049500 00044400  2C 00 00 00 */	cmpwi r0, 0
/* 80049504 00044404  41 82 00 0C */	beq lbl_80049510
/* 80049508 00044408  7E E3 BB 78 */	mr r3, r23
/* 8004950C 0004440C  48 00 00 08 */	b lbl_80049514
lbl_80049510:
/* 80049510 00044410  38 60 00 00 */	li r3, 0
lbl_80049514:
/* 80049514 00044414  2C 03 00 00 */	cmpwi r3, 0
/* 80049518 00044418  41 82 00 0C */	beq lbl_80049524
/* 8004951C 0004441C  38 00 00 01 */	li r0, 1
/* 80049520 00044420  90 03 00 68 */	stw r0, 0x68(r3)
lbl_80049524:
/* 80049524 00044424  3F E0 80 3F */	lis r31, sLoadBufferMutex__Q44nw4r3snd6detail10StrmPlayer@ha
/* 80049528 00044428  3B FF BC 40 */	addi r31, r31, sLoadBufferMutex__Q44nw4r3snd6detail10StrmPlayer@l
/* 8004952C 0004442C  7F E3 FB 78 */	mr r3, r31
/* 80049530 00044430  48 0A 96 4D */	bl OSLockMutex
/* 80049534 00044434  3E A0 80 3E */	lis r21, sLoadBuffer__Q44nw4r3snd6detail10StrmPlayer@ha
/* 80049538 00044438  7E 84 A3 78 */	mr r4, r20
/* 8004953C 0004443C  38 75 7C 20 */	addi r3, r21, sLoadBuffer__Q44nw4r3snd6detail10StrmPlayer@l
/* 80049540 00044440  48 0A 4B C5 */	bl func_800EE104
/* 80049544 00044444  81 97 00 00 */	lwz r12, 0(r23)
/* 80049548 00044448  7E E3 BB 78 */	mr r3, r23
/* 8004954C 0004444C  7E C4 B3 78 */	mr r4, r22
/* 80049550 00044450  38 A0 00 00 */	li r5, 0
/* 80049554 00044454  81 8C 00 44 */	lwz r12, 0x44(r12)
/* 80049558 00044458  7D 89 03 A6 */	mtctr r12
/* 8004955C 0004445C  4E 80 04 21 */	bctrl 
/* 80049560 00044460  81 97 00 00 */	lwz r12, 0(r23)
/* 80049564 00044464  7E E3 BB 78 */	mr r3, r23
/* 80049568 00044468  7E 85 A3 78 */	mr r5, r20
/* 8004956C 0004446C  38 95 7C 20 */	addi r4, r21, 0x7c20
/* 80049570 00044470  81 8C 00 14 */	lwz r12, 0x14(r12)
/* 80049574 00044474  7D 89 03 A6 */	mtctr r12
/* 80049578 00044478  4E 80 04 21 */	bctrl 
/* 8004957C 0004447C  7C 03 A0 40 */	cmplw r3, r20
/* 80049580 00044480  41 82 00 14 */	beq lbl_80049594
/* 80049584 00044484  7F E3 FB 78 */	mr r3, r31
/* 80049588 00044488  48 0A 96 D1 */	bl OSUnlockMutex
/* 8004958C 0004448C  38 60 00 00 */	li r3, 0
/* 80049590 00044490  48 00 01 1C */	b lbl_800496AC
lbl_80049594:
/* 80049594 00044494  38 1A 00 1F */	addi r0, r26, 0x1f
/* 80049598 00044498  3A B5 7C 20 */	addi r21, r21, 0x7c20
/* 8004959C 0004449C  54 1D 00 34 */	rlwinm r29, r0, 0, 0, 0x1a
/* 800495A0 000444A0  3A C1 00 08 */	addi r22, r1, 8
/* 800495A4 000444A4  3B C0 00 00 */	li r30, 0
/* 800495A8 000444A8  3B 00 00 00 */	li r24, 0
/* 800495AC 000444AC  3A E0 00 00 */	li r23, 0
/* 800495B0 000444B0  48 00 00 70 */	b lbl_80049620
lbl_800495B4:
/* 800495B4 000444B4  2C 1C 00 00 */	cmpwi r28, 0
/* 800495B8 000444B8  41 82 00 20 */	beq lbl_800495D8
/* 800495BC 000444BC  38 1A 00 1F */	addi r0, r26, 0x1f
/* 800495C0 000444C0  A0 79 00 88 */	lhz r3, 0x88(r25)
/* 800495C4 000444C4  54 00 00 34 */	rlwinm r0, r0, 0, 0, 0x1a
/* 800495C8 000444C8  7C 1E 01 D6 */	mullw r0, r30, r0
/* 800495CC 000444CC  7C 63 02 14 */	add r3, r3, r0
/* 800495D0 000444D0  7C 03 A8 AE */	lbzx r0, r3, r21
/* 800495D4 000444D4  7C 16 BB 2E */	sthx r0, r22, r23
lbl_800495D8:
/* 800495D8 000444D8  80 19 00 D4 */	lwz r0, 0xd4(r25)
/* 800495DC 000444DC  7C 79 C2 14 */	add r3, r25, r24
/* 800495E0 000444E0  7C 9E E9 D6 */	mullw r4, r30, r29
/* 800495E4 000444E4  A0 D9 00 88 */	lhz r6, 0x88(r25)
/* 800495E8 000444E8  80 63 07 CC */	lwz r3, 0x7cc(r3)
/* 800495EC 000444EC  7F A5 EB 78 */	mr r5, r29
/* 800495F0 000444F0  7C E0 D9 D6 */	mullw r7, r0, r27
/* 800495F4 000444F4  7C 06 22 14 */	add r0, r6, r4
/* 800495F8 000444F8  7C 80 AA 14 */	add r4, r0, r21
/* 800495FC 000444FC  7E 87 1A 14 */	add r20, r7, r3
/* 80049600 00044500  7E 83 A3 78 */	mr r3, r20
/* 80049604 00044504  4B FB A9 FD */	bl memcpy
/* 80049608 00044508  7E 83 A3 78 */	mr r3, r20
/* 8004960C 0004450C  7F A4 EB 78 */	mr r4, r29
/* 80049610 00044510  48 0A 4B 21 */	bl DCFlushRange
/* 80049614 00044514  3B DE 00 01 */	addi r30, r30, 1
/* 80049618 00044518  3B 18 00 38 */	addi r24, r24, 0x38
/* 8004961C 0004451C  3A F7 00 02 */	addi r23, r23, 2
lbl_80049620:
/* 80049620 00044520  80 D9 07 C4 */	lwz r6, 0x7c4(r25)
/* 80049624 00044524  7C 1E 30 00 */	cmpw r30, r6
/* 80049628 00044528  41 80 FF 8C */	blt lbl_800495B4
/* 8004962C 0004452C  2C 1C 00 00 */	cmpwi r28, 0
/* 80049630 00044530  41 82 00 4C */	beq lbl_8004967C
/* 80049634 00044534  88 19 00 80 */	lbz r0, 0x80(r25)
/* 80049638 00044538  28 00 00 02 */	cmplwi r0, 2
/* 8004963C 0004453C  40 82 00 40 */	bne lbl_8004967C
/* 80049640 00044540  38 A1 00 08 */	addi r5, r1, 8
/* 80049644 00044544  38 E0 00 00 */	li r7, 0
/* 80049648 00044548  38 60 00 00 */	li r3, 0
/* 8004964C 0004454C  48 00 00 18 */	b lbl_80049664
lbl_80049650:
/* 80049650 00044550  7C 05 1A 2E */	lhzx r0, r5, r3
/* 80049654 00044554  7C 99 1A 14 */	add r4, r25, r3
/* 80049658 00044558  38 E7 00 01 */	addi r7, r7, 1
/* 8004965C 0004455C  38 63 00 02 */	addi r3, r3, 2
/* 80049660 00044560  B0 04 08 3C */	sth r0, 0x83c(r4)
lbl_80049664:
/* 80049664 00044564  7C 07 30 00 */	cmpw r7, r6
/* 80049668 00044568  40 80 00 0C */	bge lbl_80049674
/* 8004966C 0004456C  2C 07 00 02 */	cmpwi r7, 2
/* 80049670 00044570  41 80 FF E0 */	blt lbl_80049650
lbl_80049674:
/* 80049674 00044574  38 00 00 01 */	li r0, 1
/* 80049678 00044578  98 19 00 C4 */	stb r0, 0xc4(r25)
lbl_8004967C:
/* 8004967C 0004457C  88 19 00 BB */	lbz r0, 0xbb(r25)
/* 80049680 00044580  2C 00 00 00 */	cmpwi r0, 0
/* 80049684 00044584  40 82 00 1C */	bne lbl_800496A0
/* 80049688 00044588  80 19 00 CC */	lwz r0, 0xcc(r25)
/* 8004968C 0004458C  34 00 FF FF */	addic. r0, r0, -1
/* 80049690 00044590  90 19 00 CC */	stw r0, 0xcc(r25)
/* 80049694 00044594  40 82 00 0C */	bne lbl_800496A0
/* 80049698 00044598  38 00 00 01 */	li r0, 1
/* 8004969C 0004459C  98 19 00 BB */	stb r0, 0xbb(r25)
lbl_800496A0:
/* 800496A0 000445A0  7F E3 FB 78 */	mr r3, r31
/* 800496A4 000445A4  48 0A 95 B5 */	bl OSUnlockMutex
/* 800496A8 000445A8  38 60 00 01 */	li r3, 1
lbl_800496AC:
/* 800496AC 000445AC  39 61 00 40 */	addi r11, r1, 0x40
/* 800496B0 000445B0  48 06 86 C5 */	bl _restgpr_20
/* 800496B4 000445B4  80 01 00 44 */	lwz r0, 0x44(r1)
/* 800496B8 000445B8  7C 08 03 A6 */	mtlr r0
/* 800496BC 000445BC  38 21 00 40 */	addi r1, r1, 0x40
/* 800496C0 000445C0  4E 80 00 20 */	blr 

.global SetupPlayer__Q44nw4r3snd6detail10StrmPlayerFPCQ54nw4r3snd6detail10StrmPlayer10StrmHeader
SetupPlayer__Q44nw4r3snd6detail10StrmPlayerFPCQ54nw4r3snd6detail10StrmPlayer10StrmHeader:
/* 800496C4 000445C4  94 21 FF B0 */	stwu r1, -0x50(r1)
/* 800496C8 000445C8  7C 08 02 A6 */	mflr r0
/* 800496CC 000445CC  90 01 00 54 */	stw r0, 0x54(r1)
/* 800496D0 000445D0  39 61 00 50 */	addi r11, r1, 0x50
/* 800496D4 000445D4  48 06 86 51 */	bl _savegpr_19
/* 800496D8 000445D8  80 A3 07 B8 */	lwz r5, 0x7b8(r3)
/* 800496DC 000445DC  38 00 00 00 */	li r0, 0
/* 800496E0 000445E0  8A 64 00 00 */	lbz r19, 0(r4)
/* 800496E4 000445E4  7C 7D 1B 78 */	mr r29, r3
/* 800496E8 000445E8  83 E5 00 08 */	lwz r31, 8(r5)
/* 800496EC 000445EC  7C 9E 23 78 */	mr r30, r4
/* 800496F0 000445F0  8A 84 00 01 */	lbz r20, 1(r4)
/* 800496F4 000445F4  38 A1 00 0C */	addi r5, r1, 0xc
/* 800496F8 000445F8  8A A4 00 02 */	lbz r21, 2(r4)
/* 800496FC 000445FC  38 C1 00 08 */	addi r6, r1, 8
/* 80049700 00044600  82 C4 00 04 */	lwz r22, 4(r4)
/* 80049704 00044604  A2 E4 00 08 */	lhz r23, 8(r4)
/* 80049708 00044608  83 04 00 0C */	lwz r24, 0xc(r4)
/* 8004970C 0004460C  83 24 00 10 */	lwz r25, 0x10(r4)
/* 80049710 00044610  83 44 00 14 */	lwz r26, 0x14(r4)
/* 80049714 00044614  83 64 00 18 */	lwz r27, 0x18(r4)
/* 80049718 00044618  83 84 00 1C */	lwz r28, 0x1c(r4)
/* 8004971C 0004461C  81 84 00 20 */	lwz r12, 0x20(r4)
/* 80049720 00044620  81 64 00 24 */	lwz r11, 0x24(r4)
/* 80049724 00044624  81 44 00 28 */	lwz r10, 0x28(r4)
/* 80049728 00044628  81 24 00 2C */	lwz r9, 0x2c(r4)
/* 8004972C 0004462C  81 04 00 30 */	lwz r8, 0x30(r4)
/* 80049730 00044630  80 E4 00 34 */	lwz r7, 0x34(r4)
/* 80049734 00044634  38 81 00 10 */	addi r4, r1, 0x10
/* 80049738 00044638  9A 63 00 80 */	stb r19, 0x80(r3)
/* 8004973C 0004463C  9A 83 00 81 */	stb r20, 0x81(r3)
/* 80049740 00044640  9A A3 00 82 */	stb r21, 0x82(r3)
/* 80049744 00044644  92 C3 00 84 */	stw r22, 0x84(r3)
/* 80049748 00044648  B2 E3 00 88 */	sth r23, 0x88(r3)
/* 8004974C 0004464C  93 03 00 8C */	stw r24, 0x8c(r3)
/* 80049750 00044650  93 23 00 90 */	stw r25, 0x90(r3)
/* 80049754 00044654  93 43 00 94 */	stw r26, 0x94(r3)
/* 80049758 00044658  93 63 00 98 */	stw r27, 0x98(r3)
/* 8004975C 0004465C  93 83 00 9C */	stw r28, 0x9c(r3)
/* 80049760 00044660  91 83 00 A0 */	stw r12, 0xa0(r3)
/* 80049764 00044664  91 63 00 A4 */	stw r11, 0xa4(r3)
/* 80049768 00044668  91 43 00 A8 */	stw r10, 0xa8(r3)
/* 8004976C 0004466C  91 23 00 AC */	stw r9, 0xac(r3)
/* 80049770 00044670  91 03 00 B0 */	stw r8, 0xb0(r3)
/* 80049774 00044674  90 E3 00 B4 */	stw r7, 0xb4(r3)
/* 80049778 00044678  90 01 00 10 */	stw r0, 0x10(r1)
/* 8004977C 0004467C  90 01 00 0C */	stw r0, 0xc(r1)
/* 80049780 00044680  90 01 00 08 */	stw r0, 8(r1)
/* 80049784 00044684  48 00 0F 81 */	bl CalcStartOffset__Q44nw4r3snd6detail10StrmPlayerFPlPUlPl
/* 80049788 00044688  2C 03 00 00 */	cmpwi r3, 0
/* 8004978C 0004468C  40 82 00 0C */	bne lbl_80049798
/* 80049790 00044690  38 60 00 00 */	li r3, 0
/* 80049794 00044694  48 00 02 44 */	b lbl_800499D8
lbl_80049798:
/* 80049798 00044698  88 1D 00 80 */	lbz r0, 0x80(r29)
/* 8004979C 0004469C  28 00 00 02 */	cmplwi r0, 2
/* 800497A0 000446A0  40 82 01 08 */	bne lbl_800498A8
/* 800497A4 000446A4  7F A3 EB 78 */	mr r3, r29
/* 800497A8 000446A8  7F C4 F3 78 */	mr r4, r30
/* 800497AC 000446AC  7F A5 EB 78 */	mr r5, r29
/* 800497B0 000446B0  38 C0 00 00 */	li r6, 0
/* 800497B4 000446B4  48 00 00 E8 */	b lbl_8004989C
lbl_800497B8:
/* 800497B8 000446B8  A0 FE 00 38 */	lhz r7, 0x38(r30)
/* 800497BC 000446BC  38 C6 00 01 */	addi r6, r6, 1
/* 800497C0 000446C0  A0 1E 00 3A */	lhz r0, 0x3a(r30)
/* 800497C4 000446C4  B0 E3 07 D4 */	sth r7, 0x7d4(r3)
/* 800497C8 000446C8  A0 FE 00 3C */	lhz r7, 0x3c(r30)
/* 800497CC 000446CC  B0 03 07 D6 */	sth r0, 0x7d6(r3)
/* 800497D0 000446D0  A0 1E 00 3E */	lhz r0, 0x3e(r30)
/* 800497D4 000446D4  B0 E3 07 D8 */	sth r7, 0x7d8(r3)
/* 800497D8 000446D8  A0 FE 00 40 */	lhz r7, 0x40(r30)
/* 800497DC 000446DC  B0 03 07 DA */	sth r0, 0x7da(r3)
/* 800497E0 000446E0  A0 1E 00 42 */	lhz r0, 0x42(r30)
/* 800497E4 000446E4  B0 E3 07 DC */	sth r7, 0x7dc(r3)
/* 800497E8 000446E8  A0 FE 00 44 */	lhz r7, 0x44(r30)
/* 800497EC 000446EC  B0 03 07 DE */	sth r0, 0x7de(r3)
/* 800497F0 000446F0  A0 1E 00 46 */	lhz r0, 0x46(r30)
/* 800497F4 000446F4  B0 E3 07 E0 */	sth r7, 0x7e0(r3)
/* 800497F8 000446F8  A0 FE 00 48 */	lhz r7, 0x48(r30)
/* 800497FC 000446FC  B0 03 07 E2 */	sth r0, 0x7e2(r3)
/* 80049800 00044700  A0 1E 00 4A */	lhz r0, 0x4a(r30)
/* 80049804 00044704  B0 E3 07 E4 */	sth r7, 0x7e4(r3)
/* 80049808 00044708  A0 FE 00 4C */	lhz r7, 0x4c(r30)
/* 8004980C 0004470C  B0 03 07 E6 */	sth r0, 0x7e6(r3)
/* 80049810 00044710  A0 1E 00 4E */	lhz r0, 0x4e(r30)
/* 80049814 00044714  B0 E3 07 E8 */	sth r7, 0x7e8(r3)
/* 80049818 00044718  A0 FE 00 50 */	lhz r7, 0x50(r30)
/* 8004981C 0004471C  B0 03 07 EA */	sth r0, 0x7ea(r3)
/* 80049820 00044720  A0 1E 00 52 */	lhz r0, 0x52(r30)
/* 80049824 00044724  B0 E3 07 EC */	sth r7, 0x7ec(r3)
/* 80049828 00044728  A0 FE 00 54 */	lhz r7, 0x54(r30)
/* 8004982C 0004472C  B0 03 07 EE */	sth r0, 0x7ee(r3)
/* 80049830 00044730  A0 1E 00 56 */	lhz r0, 0x56(r30)
/* 80049834 00044734  B0 E3 07 F0 */	sth r7, 0x7f0(r3)
/* 80049838 00044738  A0 FE 00 58 */	lhz r7, 0x58(r30)
/* 8004983C 0004473C  B0 03 07 F2 */	sth r0, 0x7f2(r3)
/* 80049840 00044740  A0 1E 00 5A */	lhz r0, 0x5a(r30)
/* 80049844 00044744  B0 E3 07 F4 */	sth r7, 0x7f4(r3)
/* 80049848 00044748  A0 FE 00 5C */	lhz r7, 0x5c(r30)
/* 8004984C 0004474C  B0 03 07 F6 */	sth r0, 0x7f6(r3)
/* 80049850 00044750  A0 1E 00 5E */	lhz r0, 0x5e(r30)
/* 80049854 00044754  B0 E3 07 F8 */	sth r7, 0x7f8(r3)
/* 80049858 00044758  A0 FE 00 60 */	lhz r7, 0x60(r30)
/* 8004985C 0004475C  B0 03 07 FA */	sth r0, 0x7fa(r3)
/* 80049860 00044760  A0 1E 00 62 */	lhz r0, 0x62(r30)
/* 80049864 00044764  B0 E3 07 FC */	sth r7, 0x7fc(r3)
/* 80049868 00044768  A0 FE 00 64 */	lhz r7, 0x64(r30)
/* 8004986C 0004476C  B0 03 07 FE */	sth r0, 0x7fe(r3)
/* 80049870 00044770  A0 1E 00 66 */	lhz r0, 0x66(r30)
/* 80049874 00044774  3B DE 00 30 */	addi r30, r30, 0x30
/* 80049878 00044778  B0 E3 08 00 */	sth r7, 0x800(r3)
/* 8004987C 0004477C  A0 E4 01 B8 */	lhz r7, 0x1b8(r4)
/* 80049880 00044780  B0 03 08 02 */	sth r0, 0x802(r3)
/* 80049884 00044784  38 63 00 38 */	addi r3, r3, 0x38
/* 80049888 00044788  A0 04 01 C8 */	lhz r0, 0x1c8(r4)
/* 8004988C 0004478C  38 84 00 02 */	addi r4, r4, 2
/* 80049890 00044790  B0 E5 08 40 */	sth r7, 0x840(r5)
/* 80049894 00044794  B0 05 08 44 */	sth r0, 0x844(r5)
/* 80049898 00044798  38 A5 00 02 */	addi r5, r5, 2
lbl_8004989C:
/* 8004989C 0004479C  88 1D 00 82 */	lbz r0, 0x82(r29)
/* 800498A0 000447A0  7C 06 00 00 */	cmpw r6, r0
/* 800498A4 000447A4  41 80 FF 14 */	blt lbl_800497B8
lbl_800498A8:
/* 800498A8 000447A8  80 9D 00 8C */	lwz r4, 0x8c(r29)
/* 800498AC 000447AC  80 7D 00 A0 */	lwz r3, 0xa0(r29)
/* 800498B0 000447B0  80 1D 00 9C */	lwz r0, 0x9c(r29)
/* 800498B4 000447B4  7C 84 1B 96 */	divwu r4, r4, r3
/* 800498B8 000447B8  80 7D 00 98 */	lwz r3, 0x98(r29)
/* 800498BC 000447BC  2C 00 20 00 */	cmpwi r0, 0x2000
/* 800498C0 000447C0  90 1D 00 D4 */	stw r0, 0xd4(r29)
/* 800498C4 000447C4  38 63 FF FF */	addi r3, r3, -1
/* 800498C8 000447C8  90 7D 00 FC */	stw r3, 0xfc(r29)
/* 800498CC 000447CC  90 9D 00 F8 */	stw r4, 0xf8(r29)
/* 800498D0 000447D0  40 81 00 0C */	ble lbl_800498DC
/* 800498D4 000447D4  38 60 00 00 */	li r3, 0
/* 800498D8 000447D8  48 00 01 00 */	b lbl_800499D8
lbl_800498DC:
/* 800498DC 000447DC  7C 1F 03 96 */	divwu r0, r31, r0
/* 800498E0 000447E0  2C 00 00 04 */	cmpwi r0, 4
/* 800498E4 000447E4  90 1D 00 D8 */	stw r0, 0xd8(r29)
/* 800498E8 000447E8  40 80 00 0C */	bge lbl_800498F4
/* 800498EC 000447EC  38 60 00 00 */	li r3, 0
/* 800498F0 000447F0  48 00 00 E8 */	b lbl_800499D8
lbl_800498F4:
/* 800498F4 000447F4  2C 00 00 20 */	cmpwi r0, 0x20
/* 800498F8 000447F8  40 81 00 0C */	ble lbl_80049904
/* 800498FC 000447FC  38 00 00 20 */	li r0, 0x20
/* 80049900 00044800  90 1D 00 D8 */	stw r0, 0xd8(r29)
lbl_80049904:
/* 80049904 00044804  80 9D 00 D8 */	lwz r4, 0xd8(r29)
/* 80049908 00044808  38 60 00 00 */	li r3, 0
/* 8004990C 0004480C  88 1D 00 C2 */	lbz r0, 0xc2(r29)
/* 80049910 00044810  38 A4 FF FF */	addi r5, r4, -1
/* 80049914 00044814  90 BD 00 DC */	stw r5, 0xdc(r29)
/* 80049918 00044818  2C 00 00 00 */	cmpwi r0, 0
/* 8004991C 0004481C  90 BD 00 D0 */	stw r5, 0xd0(r29)
/* 80049920 00044820  80 01 00 10 */	lwz r0, 0x10(r1)
/* 80049924 00044824  90 1D 00 F4 */	stw r0, 0xf4(r29)
/* 80049928 00044828  80 81 00 10 */	lwz r4, 0x10(r1)
/* 8004992C 0004482C  90 9D 00 E8 */	stw r4, 0xe8(r29)
/* 80049930 00044830  90 7D 00 E4 */	stw r3, 0xe4(r29)
/* 80049934 00044834  90 7D 00 F0 */	stw r3, 0xf0(r29)
/* 80049938 00044838  41 82 00 10 */	beq lbl_80049948
/* 8004993C 0004483C  80 1D 00 98 */	lwz r0, 0x98(r29)
/* 80049940 00044840  90 1D 00 E0 */	stw r0, 0xe0(r29)
/* 80049944 00044844  48 00 00 3C */	b lbl_80049980
lbl_80049948:
/* 80049948 00044848  80 DD 00 FC */	lwz r6, 0xfc(r29)
/* 8004994C 0004484C  38 E5 00 01 */	addi r7, r5, 1
/* 80049950 00044850  80 1D 00 F8 */	lwz r0, 0xf8(r29)
/* 80049954 00044854  7C 64 30 50 */	subf r3, r4, r6
/* 80049958 00044858  38 83 00 01 */	addi r4, r3, 1
/* 8004995C 0004485C  7C 60 30 50 */	subf r3, r0, r6
/* 80049960 00044860  7C 84 38 50 */	subf r4, r4, r7
/* 80049964 00044864  38 63 00 01 */	addi r3, r3, 1
/* 80049968 00044868  7C 04 1B D6 */	divw r0, r4, r3
/* 8004996C 0004486C  7C 00 19 D6 */	mullw r0, r0, r3
/* 80049970 00044870  7C 00 20 51 */	subf. r0, r0, r4
/* 80049974 00044874  40 82 00 08 */	bne lbl_8004997C
/* 80049978 00044878  7C E5 3B 78 */	mr r5, r7
lbl_8004997C:
/* 8004997C 0004487C  90 BD 00 E0 */	stw r5, 0xe0(r29)
lbl_80049980:
/* 80049980 00044880  80 1D 00 E0 */	lwz r0, 0xe0(r29)
/* 80049984 00044884  90 1D 00 EC */	stw r0, 0xec(r29)
/* 80049988 00044888  48 0A 7F 39 */	bl OSDisableInterrupts
/* 8004998C 0004488C  88 1D 00 82 */	lbz r0, 0x82(r29)
/* 80049990 00044890  7C 7E 1B 78 */	mr r30, r3
/* 80049994 00044894  38 80 00 02 */	li r4, 2
/* 80049998 00044898  2C 00 00 02 */	cmpwi r0, 2
/* 8004999C 0004489C  41 81 00 08 */	bgt lbl_800499A4
/* 800499A0 000448A0  7C 04 03 78 */	mr r4, r0
lbl_800499A4:
/* 800499A4 000448A4  90 9D 07 C4 */	stw r4, 0x7c4(r29)
/* 800499A8 000448A8  7F A3 EB 78 */	mr r3, r29
/* 800499AC 000448AC  80 BD 07 C8 */	lwz r5, 0x7c8(r29)
/* 800499B0 000448B0  48 00 00 41 */	bl AllocChannels__Q44nw4r3snd6detail10StrmPlayerFii
/* 800499B4 000448B4  2C 03 00 00 */	cmpwi r3, 0
/* 800499B8 000448B8  40 82 00 14 */	bne lbl_800499CC
/* 800499BC 000448BC  7F C3 F3 78 */	mr r3, r30
/* 800499C0 000448C0  48 0A 7F 29 */	bl OSRestoreInterrupts
/* 800499C4 000448C4  38 60 00 00 */	li r3, 0
/* 800499C8 000448C8  48 00 00 10 */	b lbl_800499D8
lbl_800499CC:
/* 800499CC 000448CC  7F C3 F3 78 */	mr r3, r30
/* 800499D0 000448D0  48 0A 7F 19 */	bl OSRestoreInterrupts
/* 800499D4 000448D4  38 60 00 01 */	li r3, 1
lbl_800499D8:
/* 800499D8 000448D8  39 61 00 50 */	addi r11, r1, 0x50
/* 800499DC 000448DC  48 06 83 95 */	bl _restgpr_19
/* 800499E0 000448E0  80 01 00 54 */	lwz r0, 0x54(r1)
/* 800499E4 000448E4  7C 08 03 A6 */	mtlr r0
/* 800499E8 000448E8  38 21 00 50 */	addi r1, r1, 0x50
/* 800499EC 000448EC  4E 80 00 20 */	blr 

.global AllocChannels__Q44nw4r3snd6detail10StrmPlayerFii
AllocChannels__Q44nw4r3snd6detail10StrmPlayerFii:
/* 800499F0 000448F0  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800499F4 000448F4  7C 08 02 A6 */	mflr r0
/* 800499F8 000448F8  90 01 00 24 */	stw r0, 0x24(r1)
/* 800499FC 000448FC  39 61 00 20 */	addi r11, r1, 0x20
/* 80049A00 00044900  48 06 83 41 */	bl _savegpr_26
/* 80049A04 00044904  7C 7A 1B 78 */	mr r26, r3
/* 80049A08 00044908  7C 9B 23 78 */	mr r27, r4
/* 80049A0C 0004490C  7C BC 2B 78 */	mr r28, r5
/* 80049A10 00044910  48 0A 7E B1 */	bl OSDisableInterrupts
/* 80049A14 00044914  7C 7F 1B 78 */	mr r31, r3
/* 80049A18 00044918  7F 5E D3 78 */	mr r30, r26
/* 80049A1C 0004491C  3B A0 00 00 */	li r29, 0
/* 80049A20 00044920  48 00 00 64 */	b lbl_80049A84
lbl_80049A24:
/* 80049A24 00044924  80 7A 07 B8 */	lwz r3, 0x7b8(r26)
/* 80049A28 00044928  4B FF E6 69 */	bl Alloc__Q44nw4r3snd6detail14StrmBufferPoolFv
/* 80049A2C 0004492C  2C 03 00 00 */	cmpwi r3, 0
/* 80049A30 00044930  40 82 00 3C */	bne lbl_80049A6C
/* 80049A34 00044934  7F 5E D3 78 */	mr r30, r26
/* 80049A38 00044938  3B 80 00 00 */	li r28, 0
/* 80049A3C 0004493C  48 00 00 18 */	b lbl_80049A54
lbl_80049A40:
/* 80049A40 00044940  80 7A 07 B8 */	lwz r3, 0x7b8(r26)
/* 80049A44 00044944  80 9E 07 CC */	lwz r4, 0x7cc(r30)
/* 80049A48 00044948  4B FF E7 2D */	bl Free__Q44nw4r3snd6detail14StrmBufferPoolFPv
/* 80049A4C 0004494C  3B DE 00 38 */	addi r30, r30, 0x38
/* 80049A50 00044950  3B 9C 00 01 */	addi r28, r28, 1
lbl_80049A54:
/* 80049A54 00044954  7C 1C E8 00 */	cmpw r28, r29
/* 80049A58 00044958  41 80 FF E8 */	blt lbl_80049A40
/* 80049A5C 0004495C  7F E3 FB 78 */	mr r3, r31
/* 80049A60 00044960  48 0A 7E 89 */	bl OSRestoreInterrupts
/* 80049A64 00044964  38 60 00 00 */	li r3, 0
/* 80049A68 00044968  48 00 00 94 */	b lbl_80049AFC
lbl_80049A6C:
/* 80049A6C 0004496C  90 7E 07 CC */	stw r3, 0x7cc(r30)
/* 80049A70 00044970  3B BD 00 01 */	addi r29, r29, 1
/* 80049A74 00044974  80 7A 07 B8 */	lwz r3, 0x7b8(r26)
/* 80049A78 00044978  80 03 00 08 */	lwz r0, 8(r3)
/* 80049A7C 0004497C  90 1E 07 D0 */	stw r0, 0x7d0(r30)
/* 80049A80 00044980  3B DE 00 38 */	addi r30, r30, 0x38
lbl_80049A84:
/* 80049A84 00044984  7C 1D D8 00 */	cmpw r29, r27
/* 80049A88 00044988  41 80 FF 9C */	blt lbl_80049A24
/* 80049A8C 0004498C  48 00 46 29 */	bl GetInstance__Q44nw4r3snd6detail12VoiceManagerFv
/* 80049A90 00044990  3C E0 80 05 */	lis r7, VoiceCallbackFunc__Q44nw4r3snd6detail10StrmPlayerFPQ44nw4r3snd6detail5VoiceQ54nw4r3snd6detail5Voice19VoiceCallbackStatusPv@ha
/* 80049A94 00044994  7F 64 DB 78 */	mr r4, r27
/* 80049A98 00044998  7F 85 E3 78 */	mr r5, r28
/* 80049A9C 0004499C  7F 48 D3 78 */	mr r8, r26
/* 80049AA0 000449A0  38 E7 A8 1C */	addi r7, r7, VoiceCallbackFunc__Q44nw4r3snd6detail10StrmPlayerFPQ44nw4r3snd6detail5VoiceQ54nw4r3snd6detail5Voice19VoiceCallbackStatusPv@l
/* 80049AA4 000449A4  38 C0 00 FF */	li r6, 0xff
/* 80049AA8 000449A8  48 00 48 B1 */	bl AllocVoice__Q44nw4r3snd6detail12VoiceManagerFiiiPFPQ44nw4r3snd6detail5VoiceQ54nw4r3snd6detail5Voice19VoiceCallbackStatusPv_vPv
/* 80049AAC 000449AC  2C 03 00 00 */	cmpwi r3, 0
/* 80049AB0 000449B0  40 82 00 3C */	bne lbl_80049AEC
/* 80049AB4 000449B4  7F 5E D3 78 */	mr r30, r26
/* 80049AB8 000449B8  3B 80 00 00 */	li r28, 0
/* 80049ABC 000449BC  48 00 00 18 */	b lbl_80049AD4
lbl_80049AC0:
/* 80049AC0 000449C0  80 7A 07 B8 */	lwz r3, 0x7b8(r26)
/* 80049AC4 000449C4  80 9E 07 CC */	lwz r4, 0x7cc(r30)
/* 80049AC8 000449C8  4B FF E6 AD */	bl Free__Q44nw4r3snd6detail14StrmBufferPoolFPv
/* 80049ACC 000449CC  3B DE 00 38 */	addi r30, r30, 0x38
/* 80049AD0 000449D0  3B 9C 00 01 */	addi r28, r28, 1
lbl_80049AD4:
/* 80049AD4 000449D4  7C 1C D8 00 */	cmpw r28, r27
/* 80049AD8 000449D8  41 80 FF E8 */	blt lbl_80049AC0
/* 80049ADC 000449DC  7F E3 FB 78 */	mr r3, r31
/* 80049AE0 000449E0  48 0A 7E 09 */	bl OSRestoreInterrupts
/* 80049AE4 000449E4  38 60 00 00 */	li r3, 0
/* 80049AE8 000449E8  48 00 00 14 */	b lbl_80049AFC
lbl_80049AEC:
/* 80049AEC 000449EC  90 7A 07 C0 */	stw r3, 0x7c0(r26)
/* 80049AF0 000449F0  7F E3 FB 78 */	mr r3, r31
/* 80049AF4 000449F4  48 0A 7D F5 */	bl OSRestoreInterrupts
/* 80049AF8 000449F8  38 60 00 01 */	li r3, 1
lbl_80049AFC:
/* 80049AFC 000449FC  39 61 00 20 */	addi r11, r1, 0x20
/* 80049B00 00044A00  48 06 82 8D */	bl _restgpr_26
/* 80049B04 00044A04  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80049B08 00044A08  7C 08 03 A6 */	mtlr r0
/* 80049B0C 00044A0C  38 21 00 20 */	addi r1, r1, 0x20
/* 80049B10 00044A10  4E 80 00 20 */	blr 

.global FreeChannels__Q44nw4r3snd6detail10StrmPlayerFv
FreeChannels__Q44nw4r3snd6detail10StrmPlayerFv:
/* 80049B14 00044A14  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80049B18 00044A18  7C 08 02 A6 */	mflr r0
/* 80049B1C 00044A1C  90 01 00 24 */	stw r0, 0x24(r1)
/* 80049B20 00044A20  39 61 00 20 */	addi r11, r1, 0x20
/* 80049B24 00044A24  48 06 82 21 */	bl _savegpr_27
/* 80049B28 00044A28  7C 7B 1B 78 */	mr r27, r3
/* 80049B2C 00044A2C  48 0A 7D 95 */	bl OSDisableInterrupts
/* 80049B30 00044A30  7C 7F 1B 78 */	mr r31, r3
/* 80049B34 00044A34  7F 7D DB 78 */	mr r29, r27
/* 80049B38 00044A38  3B 80 00 00 */	li r28, 0
/* 80049B3C 00044A3C  3B C0 00 00 */	li r30, 0
/* 80049B40 00044A40  48 00 00 28 */	b lbl_80049B68
lbl_80049B44:
/* 80049B44 00044A44  80 9D 07 CC */	lwz r4, 0x7cc(r29)
/* 80049B48 00044A48  2C 04 00 00 */	cmpwi r4, 0
/* 80049B4C 00044A4C  41 82 00 14 */	beq lbl_80049B60
/* 80049B50 00044A50  80 7B 07 B8 */	lwz r3, 0x7b8(r27)
/* 80049B54 00044A54  4B FF E6 21 */	bl Free__Q44nw4r3snd6detail14StrmBufferPoolFPv
/* 80049B58 00044A58  93 DD 07 CC */	stw r30, 0x7cc(r29)
/* 80049B5C 00044A5C  93 DD 07 D0 */	stw r30, 0x7d0(r29)
lbl_80049B60:
/* 80049B60 00044A60  3B BD 00 38 */	addi r29, r29, 0x38
/* 80049B64 00044A64  3B 9C 00 01 */	addi r28, r28, 1
lbl_80049B68:
/* 80049B68 00044A68  80 1B 07 C4 */	lwz r0, 0x7c4(r27)
/* 80049B6C 00044A6C  7C 1C 00 00 */	cmpw r28, r0
/* 80049B70 00044A70  41 80 FF D4 */	blt lbl_80049B44
/* 80049B74 00044A74  80 7B 07 C0 */	lwz r3, 0x7c0(r27)
/* 80049B78 00044A78  3B C0 00 00 */	li r30, 0
/* 80049B7C 00044A7C  93 DB 07 C4 */	stw r30, 0x7c4(r27)
/* 80049B80 00044A80  2C 03 00 00 */	cmpwi r3, 0
/* 80049B84 00044A84  41 82 00 0C */	beq lbl_80049B90
/* 80049B88 00044A88  48 00 28 01 */	bl Free__Q44nw4r3snd6detail5VoiceFv
/* 80049B8C 00044A8C  93 DB 07 C0 */	stw r30, 0x7c0(r27)
lbl_80049B90:
/* 80049B90 00044A90  7F E3 FB 78 */	mr r3, r31
/* 80049B94 00044A94  48 0A 7D 55 */	bl OSRestoreInterrupts
/* 80049B98 00044A98  39 61 00 20 */	addi r11, r1, 0x20
/* 80049B9C 00044A9C  48 06 81 F5 */	bl _restgpr_27
/* 80049BA0 00044AA0  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80049BA4 00044AA4  7C 08 03 A6 */	mtlr r0
/* 80049BA8 00044AA8  38 21 00 20 */	addi r1, r1, 0x20
/* 80049BAC 00044AAC  4E 80 00 20 */	blr 

.global Update__Q44nw4r3snd6detail10StrmPlayerFv
Update__Q44nw4r3snd6detail10StrmPlayerFv:
/* 80049BB0 00044AB0  94 21 FF 30 */	stwu r1, -0xd0(r1)
/* 80049BB4 00044AB4  7C 08 02 A6 */	mflr r0
/* 80049BB8 00044AB8  90 01 00 D4 */	stw r0, 0xd4(r1)
/* 80049BBC 00044ABC  DB E1 00 C0 */	stfd f31, 0xc0(r1)
/* 80049BC0 00044AC0  F3 E1 00 C8 */	psq_st f31, 200(r1), 0, qr0
/* 80049BC4 00044AC4  DB C1 00 B0 */	stfd f30, 0xb0(r1)
/* 80049BC8 00044AC8  F3 C1 00 B8 */	psq_st f30, 184(r1), 0, qr0
/* 80049BCC 00044ACC  DB A1 00 A0 */	stfd f29, 0xa0(r1)
/* 80049BD0 00044AD0  F3 A1 00 A8 */	psq_st f29, 168(r1), 0, qr0
/* 80049BD4 00044AD4  DB 81 00 90 */	stfd f28, 0x90(r1)
/* 80049BD8 00044AD8  F3 81 00 98 */	psq_st f28, 152(r1), 0, qr0
/* 80049BDC 00044ADC  DB 61 00 80 */	stfd f27, 0x80(r1)
/* 80049BE0 00044AE0  F3 61 00 88 */	psq_st f27, 136(r1), 0, qr0
/* 80049BE4 00044AE4  DB 41 00 70 */	stfd f26, 0x70(r1)
/* 80049BE8 00044AE8  F3 41 00 78 */	psq_st f26, 120(r1), 0, qr0
/* 80049BEC 00044AEC  DB 21 00 60 */	stfd f25, 0x60(r1)
/* 80049BF0 00044AF0  F3 21 00 68 */	psq_st f25, 104(r1), 0, qr0
/* 80049BF4 00044AF4  39 61 00 60 */	addi r11, r1, 0x60
/* 80049BF8 00044AF8  48 06 81 49 */	bl _savegpr_26
/* 80049BFC 00044AFC  88 03 00 B9 */	lbz r0, 0xb9(r3)
/* 80049C00 00044B00  7C 7F 1B 78 */	mr r31, r3
/* 80049C04 00044B04  2C 00 00 00 */	cmpwi r0, 0
/* 80049C08 00044B08  41 82 02 F8 */	beq lbl_80049F00
/* 80049C0C 00044B0C  88 03 00 BC */	lbz r0, 0xbc(r3)
/* 80049C10 00044B10  2C 00 00 00 */	cmpwi r0, 0
/* 80049C14 00044B14  41 82 00 24 */	beq lbl_80049C38
/* 80049C18 00044B18  88 03 00 BD */	lbz r0, 0xbd(r3)
/* 80049C1C 00044B1C  2C 00 00 00 */	cmpwi r0, 0
/* 80049C20 00044B20  40 82 00 18 */	bne lbl_80049C38
/* 80049C24 00044B24  81 83 00 00 */	lwz r12, 0(r3)
/* 80049C28 00044B28  81 8C 00 10 */	lwz r12, 0x10(r12)
/* 80049C2C 00044B2C  7D 89 03 A6 */	mtctr r12
/* 80049C30 00044B30  4E 80 04 21 */	bctrl 
/* 80049C34 00044B34  48 00 02 CC */	b lbl_80049F00
lbl_80049C38:
/* 80049C38 00044B38  88 03 00 BA */	lbz r0, 0xba(r3)
/* 80049C3C 00044B3C  2C 00 00 00 */	cmpwi r0, 0
/* 80049C40 00044B40  41 82 00 28 */	beq lbl_80049C68
/* 80049C44 00044B44  80 03 07 C0 */	lwz r0, 0x7c0(r3)
/* 80049C48 00044B48  2C 00 00 00 */	cmpwi r0, 0
/* 80049C4C 00044B4C  40 82 00 1C */	bne lbl_80049C68
/* 80049C50 00044B50  81 9F 00 00 */	lwz r12, 0(r31)
/* 80049C54 00044B54  7F E3 FB 78 */	mr r3, r31
/* 80049C58 00044B58  81 8C 00 10 */	lwz r12, 0x10(r12)
/* 80049C5C 00044B5C  7D 89 03 A6 */	mtctr r12
/* 80049C60 00044B60  4E 80 04 21 */	bctrl 
/* 80049C64 00044B64  48 00 02 9C */	b lbl_80049F00
lbl_80049C68:
/* 80049C68 00044B68  88 03 00 C1 */	lbz r0, 0xc1(r3)
/* 80049C6C 00044B6C  2C 00 00 00 */	cmpwi r0, 0
/* 80049C70 00044B70  41 82 00 70 */	beq lbl_80049CE0
/* 80049C74 00044B74  80 03 01 28 */	lwz r0, 0x128(r3)
/* 80049C78 00044B78  2C 00 00 00 */	cmpwi r0, 0
/* 80049C7C 00044B7C  40 82 00 64 */	bne lbl_80049CE0
/* 80049C80 00044B80  38 00 00 00 */	li r0, 0
/* 80049C84 00044B84  98 03 00 C1 */	stb r0, 0xc1(r3)
/* 80049C88 00044B88  48 0A 7C 39 */	bl OSDisableInterrupts
/* 80049C8C 00044B8C  88 1F 00 BF */	lbz r0, 0xbf(r31)
/* 80049C90 00044B90  7C 7E 1B 78 */	mr r30, r3
/* 80049C94 00044B94  3B A0 00 00 */	li r29, 0
/* 80049C98 00044B98  2C 00 00 00 */	cmpwi r0, 0
/* 80049C9C 00044B9C  41 82 00 08 */	beq lbl_80049CA4
/* 80049CA0 00044BA0  3B A0 00 01 */	li r29, 1
lbl_80049CA4:
/* 80049CA4 00044BA4  88 1F 00 C1 */	lbz r0, 0xc1(r31)
/* 80049CA8 00044BA8  2C 00 00 00 */	cmpwi r0, 0
/* 80049CAC 00044BAC  41 82 00 08 */	beq lbl_80049CB4
/* 80049CB0 00044BB0  3B A0 00 01 */	li r29, 1
lbl_80049CB4:
/* 80049CB4 00044BB4  88 1F 00 C0 */	lbz r0, 0xc0(r31)
/* 80049CB8 00044BB8  7C 1D 00 40 */	cmplw r29, r0
/* 80049CBC 00044BBC  41 82 00 1C */	beq lbl_80049CD8
/* 80049CC0 00044BC0  80 7F 07 C0 */	lwz r3, 0x7c0(r31)
/* 80049CC4 00044BC4  2C 03 00 00 */	cmpwi r3, 0
/* 80049CC8 00044BC8  41 82 00 0C */	beq lbl_80049CD4
/* 80049CCC 00044BCC  7F A4 EB 78 */	mr r4, r29
/* 80049CD0 00044BD0  48 00 2B 25 */	bl Pause__Q44nw4r3snd6detail5VoiceFb
lbl_80049CD4:
/* 80049CD4 00044BD4  9B BF 00 C0 */	stb r29, 0xc0(r31)
lbl_80049CD8:
/* 80049CD8 00044BD8  7F C3 F3 78 */	mr r3, r30
/* 80049CDC 00044BDC  48 0A 7C 0D */	bl OSRestoreInterrupts
lbl_80049CE0:
/* 80049CE0 00044BE0  88 1F 00 BE */	lbz r0, 0xbe(r31)
/* 80049CE4 00044BE4  2C 00 00 00 */	cmpwi r0, 0
/* 80049CE8 00044BE8  41 82 00 0C */	beq lbl_80049CF4
/* 80049CEC 00044BEC  38 00 00 00 */	li r0, 0
/* 80049CF0 00044BF0  98 1F 00 BE */	stb r0, 0xbe(r31)
lbl_80049CF4:
/* 80049CF4 00044BF4  80 1F 07 C0 */	lwz r0, 0x7c0(r31)
/* 80049CF8 00044BF8  2C 00 00 00 */	cmpwi r0, 0
/* 80049CFC 00044BFC  41 82 02 04 */	beq lbl_80049F00
/* 80049D00 00044C00  C3 C2 87 00 */	lfs f30, lbl_804C0120-_SDA2_BASE_(r2)
/* 80049D04 00044C04  3B 61 00 38 */	addi r27, r1, 0x38
/* 80049D08 00044C08  C0 1F 00 08 */	lfs f0, 8(r31)
/* 80049D0C 00044C0C  3B 80 00 00 */	li r28, 0
/* 80049D10 00044C10  FF A0 F0 90 */	fmr f29, f30
/* 80049D14 00044C14  C3 82 87 04 */	lfs f28, lbl_804C0124-_SDA2_BASE_(r2)
/* 80049D18 00044C18  EF DE 00 32 */	fmuls f30, f30, f0
/* 80049D1C 00044C1C  C0 1F 00 0C */	lfs f0, 0xc(r31)
/* 80049D20 00044C20  FF 60 E0 90 */	fmr f27, f28
/* 80049D24 00044C24  C0 3F 00 10 */	lfs f1, 0x10(r31)
/* 80049D28 00044C28  EF BD 00 32 */	fmuls f29, f29, f0
/* 80049D2C 00044C2C  C0 1F 00 14 */	lfs f0, 0x14(r31)
/* 80049D30 00044C30  EF 9C 08 2A */	fadds f28, f28, f1
/* 80049D34 00044C34  C3 22 87 04 */	lfs f25, lbl_804C0124-_SDA2_BASE_(r2)
/* 80049D38 00044C38  EF 7B 00 2A */	fadds f27, f27, f0
/* 80049D3C 00044C3C  C3 42 87 00 */	lfs f26, lbl_804C0120-_SDA2_BASE_(r2)
/* 80049D40 00044C40  C0 3F 00 18 */	lfs f1, 0x18(r31)
/* 80049D44 00044C44  FF E0 C8 90 */	fmr f31, f25
/* 80049D48 00044C48  C0 1F 00 28 */	lfs f0, 0x28(r31)
/* 80049D4C 00044C4C  EF 5A 08 2A */	fadds f26, f26, f1
/* 80049D50 00044C50  8B 5F 00 68 */	lbz r26, 0x68(r31)
/* 80049D54 00044C54  EF 39 00 2A */	fadds f25, f25, f0
lbl_80049D58:
/* 80049D58 00044C58  D3 FB 00 00 */	stfs f31, 0(r27)
/* 80049D5C 00044C5C  7F E3 FB 78 */	mr r3, r31
/* 80049D60 00044C60  7F 84 E3 78 */	mr r4, r28
/* 80049D64 00044C64  4B FE C4 8D */	bl GetFxSend__Q44nw4r3snd6detail11BasicPlayerCFQ34nw4r3snd6AuxBus
/* 80049D68 00044C68  C0 1B 00 00 */	lfs f0, 0(r27)
/* 80049D6C 00044C6C  3B 9C 00 01 */	addi r28, r28, 1
/* 80049D70 00044C70  2C 1C 00 03 */	cmpwi r28, 3
/* 80049D74 00044C74  EC 00 08 2A */	fadds f0, f0, f1
/* 80049D78 00044C78  D0 1B 00 00 */	stfs f0, 0(r27)
/* 80049D7C 00044C7C  3B 7B 00 04 */	addi r27, r27, 4
/* 80049D80 00044C80  41 80 FF D8 */	blt lbl_80049D58
/* 80049D84 00044C84  C3 E2 87 04 */	lfs f31, lbl_804C0124-_SDA2_BASE_(r2)
/* 80049D88 00044C88  3B 61 00 28 */	addi r27, r1, 0x28
/* 80049D8C 00044C8C  3B 81 00 18 */	addi r28, r1, 0x18
/* 80049D90 00044C90  3B A1 00 08 */	addi r29, r1, 8
/* 80049D94 00044C94  3B C0 00 00 */	li r30, 0
lbl_80049D98:
/* 80049D98 00044C98  7F E3 FB 78 */	mr r3, r31
/* 80049D9C 00044C9C  7F C4 F3 78 */	mr r4, r30
/* 80049DA0 00044CA0  4B FE C4 71 */	bl GetRemoteOutVolume__Q44nw4r3snd6detail11BasicPlayerCFi
/* 80049DA4 00044CA4  D0 3B 00 00 */	stfs f1, 0(r27)
/* 80049DA8 00044CA8  7F E3 FB 78 */	mr r3, r31
/* 80049DAC 00044CAC  7F C4 F3 78 */	mr r4, r30
/* 80049DB0 00044CB0  D3 FC 00 00 */	stfs f31, 0(r28)
/* 80049DB4 00044CB4  4B FE C4 6D */	bl GetRemoteSend__Q44nw4r3snd6detail11BasicPlayerCFi
/* 80049DB8 00044CB8  C0 1C 00 00 */	lfs f0, 0(r28)
/* 80049DBC 00044CBC  7F E3 FB 78 */	mr r3, r31
/* 80049DC0 00044CC0  D3 FD 00 00 */	stfs f31, 0(r29)
/* 80049DC4 00044CC4  7F C4 F3 78 */	mr r4, r30
/* 80049DC8 00044CC8  EC 00 08 2A */	fadds f0, f0, f1
/* 80049DCC 00044CCC  D0 1C 00 00 */	stfs f0, 0(r28)
/* 80049DD0 00044CD0  4B FE C4 61 */	bl GetRemoteFxSend__Q44nw4r3snd6detail11BasicPlayerCFi
/* 80049DD4 00044CD4  C0 1D 00 00 */	lfs f0, 0(r29)
/* 80049DD8 00044CD8  3B DE 00 01 */	addi r30, r30, 1
/* 80049DDC 00044CDC  2C 1E 00 04 */	cmpwi r30, 4
/* 80049DE0 00044CE0  3B 7B 00 04 */	addi r27, r27, 4
/* 80049DE4 00044CE4  EC 00 08 2A */	fadds f0, f0, f1
/* 80049DE8 00044CE8  3B 9C 00 04 */	addi r28, r28, 4
/* 80049DEC 00044CEC  D0 1D 00 00 */	stfs f0, 0(r29)
/* 80049DF0 00044CF0  3B BD 00 04 */	addi r29, r29, 4
/* 80049DF4 00044CF4  41 80 FF A4 */	blt lbl_80049D98
/* 80049DF8 00044CF8  48 0A 7A C9 */	bl OSDisableInterrupts
/* 80049DFC 00044CFC  80 1F 07 C0 */	lwz r0, 0x7c0(r31)
/* 80049E00 00044D00  7C 7E 1B 78 */	mr r30, r3
/* 80049E04 00044D04  2C 00 00 00 */	cmpwi r0, 0
/* 80049E08 00044D08  41 82 00 F0 */	beq lbl_80049EF8
/* 80049E0C 00044D0C  FC 20 F0 90 */	fmr f1, f30
/* 80049E10 00044D10  7C 03 03 78 */	mr r3, r0
/* 80049E14 00044D14  48 00 2A 1D */	bl SetVolume__Q44nw4r3snd6detail5VoiceFf
/* 80049E18 00044D18  FC 20 E8 90 */	fmr f1, f29
/* 80049E1C 00044D1C  80 7F 07 C0 */	lwz r3, 0x7c0(r31)
/* 80049E20 00044D20  48 00 2A F9 */	bl SetPitch__Q44nw4r3snd6detail5VoiceFf
/* 80049E24 00044D24  FC 20 E0 90 */	fmr f1, f28
/* 80049E28 00044D28  80 7F 07 C0 */	lwz r3, 0x7c0(r31)
/* 80049E2C 00044D2C  48 00 2B 4D */	bl SetPan__Q44nw4r3snd6detail5VoiceFf
/* 80049E30 00044D30  FC 20 D8 90 */	fmr f1, f27
/* 80049E34 00044D34  80 7F 07 C0 */	lwz r3, 0x7c0(r31)
/* 80049E38 00044D38  48 00 2B 61 */	bl SetSurroundPan__Q44nw4r3snd6detail5VoiceFf
/* 80049E3C 00044D3C  FC 20 D0 90 */	fmr f1, f26
/* 80049E40 00044D40  80 7F 07 C0 */	lwz r3, 0x7c0(r31)
/* 80049E44 00044D44  48 00 2B 75 */	bl SetLpfFreq__Q44nw4r3snd6detail5VoiceFf
/* 80049E48 00044D48  80 7F 07 C0 */	lwz r3, 0x7c0(r31)
/* 80049E4C 00044D4C  7F 44 D3 78 */	mr r4, r26
/* 80049E50 00044D50  48 00 2B AD */	bl SetRemoteFilter__Q44nw4r3snd6detail5VoiceFi
/* 80049E54 00044D54  80 7F 07 C0 */	lwz r3, 0x7c0(r31)
/* 80049E58 00044D58  80 9F 00 20 */	lwz r4, 0x20(r31)
/* 80049E5C 00044D5C  48 00 2B D9 */	bl SetOutputLine__Q44nw4r3snd6detail5VoiceFi
/* 80049E60 00044D60  C0 3F 00 24 */	lfs f1, 0x24(r31)
/* 80049E64 00044D64  80 7F 07 C0 */	lwz r3, 0x7c0(r31)
/* 80049E68 00044D68  48 00 2B ED */	bl SetMainOutVolume__Q44nw4r3snd6detail5VoiceFf
/* 80049E6C 00044D6C  FC 20 C8 90 */	fmr f1, f25
/* 80049E70 00044D70  80 7F 07 C0 */	lwz r3, 0x7c0(r31)
/* 80049E74 00044D74  48 00 2C 25 */	bl SetMainSend__Q44nw4r3snd6detail5VoiceFf
/* 80049E78 00044D78  3B 61 00 38 */	addi r27, r1, 0x38
/* 80049E7C 00044D7C  3B 40 00 00 */	li r26, 0
lbl_80049E80:
/* 80049E80 00044D80  80 7F 07 C0 */	lwz r3, 0x7c0(r31)
/* 80049E84 00044D84  7F 44 D3 78 */	mr r4, r26
/* 80049E88 00044D88  C0 3B 00 00 */	lfs f1, 0(r27)
/* 80049E8C 00044D8C  48 00 2C 55 */	bl SetFxSend__Q44nw4r3snd6detail5VoiceFQ34nw4r3snd6AuxBusf
/* 80049E90 00044D90  3B 5A 00 01 */	addi r26, r26, 1
/* 80049E94 00044D94  3B 7B 00 04 */	addi r27, r27, 4
/* 80049E98 00044D98  2C 1A 00 03 */	cmpwi r26, 3
/* 80049E9C 00044D9C  41 80 FF E4 */	blt lbl_80049E80
/* 80049EA0 00044DA0  3B A1 00 28 */	addi r29, r1, 0x28
/* 80049EA4 00044DA4  3B 81 00 18 */	addi r28, r1, 0x18
/* 80049EA8 00044DA8  3B 61 00 08 */	addi r27, r1, 8
/* 80049EAC 00044DAC  3B 40 00 00 */	li r26, 0
lbl_80049EB0:
/* 80049EB0 00044DB0  80 7F 07 C0 */	lwz r3, 0x7c0(r31)
/* 80049EB4 00044DB4  7F 44 D3 78 */	mr r4, r26
/* 80049EB8 00044DB8  C0 3D 00 00 */	lfs f1, 0(r29)
/* 80049EBC 00044DBC  48 00 2C 71 */	bl SetRemoteOutVolume__Q44nw4r3snd6detail5VoiceFif
/* 80049EC0 00044DC0  80 7F 07 C0 */	lwz r3, 0x7c0(r31)
/* 80049EC4 00044DC4  7F 44 D3 78 */	mr r4, r26
/* 80049EC8 00044DC8  C0 3C 00 00 */	lfs f1, 0(r28)
/* 80049ECC 00044DCC  48 00 2C AD */	bl SetRemoteSend__Q44nw4r3snd6detail5VoiceFif
/* 80049ED0 00044DD0  80 7F 07 C0 */	lwz r3, 0x7c0(r31)
/* 80049ED4 00044DD4  7F 44 D3 78 */	mr r4, r26
/* 80049ED8 00044DD8  C0 3B 00 00 */	lfs f1, 0(r27)
/* 80049EDC 00044DDC  48 00 2C ED */	bl SetRemoteFxSend__Q44nw4r3snd6detail5VoiceFif
/* 80049EE0 00044DE0  3B 5A 00 01 */	addi r26, r26, 1
/* 80049EE4 00044DE4  3B 9C 00 04 */	addi r28, r28, 4
/* 80049EE8 00044DE8  2C 1A 00 04 */	cmpwi r26, 4
/* 80049EEC 00044DEC  3B 7B 00 04 */	addi r27, r27, 4
/* 80049EF0 00044DF0  3B BD 00 04 */	addi r29, r29, 4
/* 80049EF4 00044DF4  41 80 FF BC */	blt lbl_80049EB0
lbl_80049EF8:
/* 80049EF8 00044DF8  7F C3 F3 78 */	mr r3, r30
/* 80049EFC 00044DFC  48 0A 79 ED */	bl OSRestoreInterrupts
lbl_80049F00:
/* 80049F00 00044E00  E3 E1 00 C8 */	psq_l f31, 200(r1), 0, qr0
/* 80049F04 00044E04  CB E1 00 C0 */	lfd f31, 0xc0(r1)
/* 80049F08 00044E08  E3 C1 00 B8 */	psq_l f30, 184(r1), 0, qr0
/* 80049F0C 00044E0C  CB C1 00 B0 */	lfd f30, 0xb0(r1)
/* 80049F10 00044E10  E3 A1 00 A8 */	psq_l f29, 168(r1), 0, qr0
/* 80049F14 00044E14  CB A1 00 A0 */	lfd f29, 0xa0(r1)
/* 80049F18 00044E18  E3 81 00 98 */	psq_l f28, 152(r1), 0, qr0
/* 80049F1C 00044E1C  CB 81 00 90 */	lfd f28, 0x90(r1)
/* 80049F20 00044E20  E3 61 00 88 */	psq_l f27, 136(r1), 0, qr0
/* 80049F24 00044E24  CB 61 00 80 */	lfd f27, 0x80(r1)
/* 80049F28 00044E28  E3 41 00 78 */	psq_l f26, 120(r1), 0, qr0
/* 80049F2C 00044E2C  CB 41 00 70 */	lfd f26, 0x70(r1)
/* 80049F30 00044E30  E3 21 00 68 */	psq_l f25, 104(r1), 0, qr0
/* 80049F34 00044E34  39 61 00 60 */	addi r11, r1, 0x60
/* 80049F38 00044E38  CB 21 00 60 */	lfd f25, 0x60(r1)
/* 80049F3C 00044E3C  48 06 7E 51 */	bl _restgpr_26
/* 80049F40 00044E40  80 01 00 D4 */	lwz r0, 0xd4(r1)
/* 80049F44 00044E44  7C 08 03 A6 */	mtlr r0
/* 80049F48 00044E48  38 21 00 D0 */	addi r1, r1, 0xd0
/* 80049F4C 00044E4C  4E 80 00 20 */	blr 

.global UpdateBuffer__Q44nw4r3snd6detail10StrmPlayerFv
UpdateBuffer__Q44nw4r3snd6detail10StrmPlayerFv:
/* 80049F50 00044E50  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80049F54 00044E54  7C 08 02 A6 */	mflr r0
/* 80049F58 00044E58  90 01 00 24 */	stw r0, 0x24(r1)
/* 80049F5C 00044E5C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80049F60 00044E60  7C 7F 1B 78 */	mr r31, r3
/* 80049F64 00044E64  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80049F68 00044E68  93 A1 00 14 */	stw r29, 0x14(r1)
/* 80049F6C 00044E6C  88 03 00 BA */	lbz r0, 0xba(r3)
/* 80049F70 00044E70  2C 00 00 00 */	cmpwi r0, 0
/* 80049F74 00044E74  41 82 01 5C */	beq lbl_8004A0D0
/* 80049F78 00044E78  80 03 07 C0 */	lwz r0, 0x7c0(r3)
/* 80049F7C 00044E7C  2C 00 00 00 */	cmpwi r0, 0
/* 80049F80 00044E80  41 82 01 50 */	beq lbl_8004A0D0
/* 80049F84 00044E84  4B FE 73 65 */	bl GetInstance__Q44nw4r3snd6detail9AxManagerFv
/* 80049F88 00044E88  88 03 00 1A */	lbz r0, 0x1a(r3)
/* 80049F8C 00044E8C  2C 00 00 00 */	cmpwi r0, 0
/* 80049F90 00044E90  41 82 00 64 */	beq lbl_80049FF4
/* 80049F94 00044E94  38 00 00 01 */	li r0, 1
/* 80049F98 00044E98  98 1F 00 C1 */	stb r0, 0xc1(r31)
/* 80049F9C 00044E9C  48 0A 79 25 */	bl OSDisableInterrupts
/* 80049FA0 00044EA0  88 1F 00 BF */	lbz r0, 0xbf(r31)
/* 80049FA4 00044EA4  7C 7E 1B 78 */	mr r30, r3
/* 80049FA8 00044EA8  3B A0 00 00 */	li r29, 0
/* 80049FAC 00044EAC  2C 00 00 00 */	cmpwi r0, 0
/* 80049FB0 00044EB0  41 82 00 08 */	beq lbl_80049FB8
/* 80049FB4 00044EB4  3B A0 00 01 */	li r29, 1
lbl_80049FB8:
/* 80049FB8 00044EB8  88 1F 00 C1 */	lbz r0, 0xc1(r31)
/* 80049FBC 00044EBC  2C 00 00 00 */	cmpwi r0, 0
/* 80049FC0 00044EC0  41 82 00 08 */	beq lbl_80049FC8
/* 80049FC4 00044EC4  3B A0 00 01 */	li r29, 1
lbl_80049FC8:
/* 80049FC8 00044EC8  88 1F 00 C0 */	lbz r0, 0xc0(r31)
/* 80049FCC 00044ECC  7C 1D 00 40 */	cmplw r29, r0
/* 80049FD0 00044ED0  41 82 00 1C */	beq lbl_80049FEC
/* 80049FD4 00044ED4  80 7F 07 C0 */	lwz r3, 0x7c0(r31)
/* 80049FD8 00044ED8  2C 03 00 00 */	cmpwi r3, 0
/* 80049FDC 00044EDC  41 82 00 0C */	beq lbl_80049FE8
/* 80049FE0 00044EE0  7F A4 EB 78 */	mr r4, r29
/* 80049FE4 00044EE4  48 00 28 11 */	bl Pause__Q44nw4r3snd6detail5VoiceFb
lbl_80049FE8:
/* 80049FE8 00044EE8  9B BF 00 C0 */	stb r29, 0xc0(r31)
lbl_80049FEC:
/* 80049FEC 00044EEC  7F C3 F3 78 */	mr r3, r30
/* 80049FF0 00044EF0  48 0A 78 F9 */	bl OSRestoreInterrupts
lbl_80049FF4:
/* 80049FF4 00044EF4  88 1F 00 C5 */	lbz r0, 0xc5(r31)
/* 80049FF8 00044EF8  2C 00 00 00 */	cmpwi r0, 0
/* 80049FFC 00044EFC  40 82 00 D4 */	bne lbl_8004A0D0
/* 8004A000 00044F00  88 1F 00 C2 */	lbz r0, 0xc2(r31)
/* 8004A004 00044F04  2C 00 00 00 */	cmpwi r0, 0
/* 8004A008 00044F08  40 82 00 C8 */	bne lbl_8004A0D0
/* 8004A00C 00044F0C  88 1F 00 C1 */	lbz r0, 0xc1(r31)
/* 8004A010 00044F10  2C 00 00 00 */	cmpwi r0, 0
/* 8004A014 00044F14  40 82 00 BC */	bne lbl_8004A0D0
/* 8004A018 00044F18  80 7F 07 C0 */	lwz r3, 0x7c0(r31)
/* 8004A01C 00044F1C  48 00 2D A5 */	bl GetCurrentPlayingSample__Q44nw4r3snd6detail5VoiceCFv
/* 8004A020 00044F20  80 1F 00 A0 */	lwz r0, 0xa0(r31)
/* 8004A024 00044F24  7F A3 03 96 */	divwu r29, r3, r0
/* 8004A028 00044F28  48 00 00 9C */	b lbl_8004A0C4
lbl_8004A02C:
/* 8004A02C 00044F2C  88 1F 00 C1 */	lbz r0, 0xc1(r31)
/* 8004A030 00044F30  2C 00 00 00 */	cmpwi r0, 0
/* 8004A034 00044F34  40 82 00 80 */	bne lbl_8004A0B4
/* 8004A038 00044F38  80 7F 00 DC */	lwz r3, 0xdc(r31)
/* 8004A03C 00044F3C  80 9F 01 28 */	lwz r4, 0x128(r31)
/* 8004A040 00044F40  38 03 FF FE */	addi r0, r3, -2
/* 8004A044 00044F44  7C 04 00 40 */	cmplw r4, r0
/* 8004A048 00044F48  41 80 00 6C */	blt lbl_8004A0B4
/* 8004A04C 00044F4C  38 00 00 01 */	li r0, 1
/* 8004A050 00044F50  98 1F 00 BE */	stb r0, 0xbe(r31)
/* 8004A054 00044F54  98 1F 00 C1 */	stb r0, 0xc1(r31)
/* 8004A058 00044F58  48 0A 78 69 */	bl OSDisableInterrupts
/* 8004A05C 00044F5C  88 1F 00 BF */	lbz r0, 0xbf(r31)
/* 8004A060 00044F60  7C 7E 1B 78 */	mr r30, r3
/* 8004A064 00044F64  3B A0 00 00 */	li r29, 0
/* 8004A068 00044F68  2C 00 00 00 */	cmpwi r0, 0
/* 8004A06C 00044F6C  41 82 00 08 */	beq lbl_8004A074
/* 8004A070 00044F70  3B A0 00 01 */	li r29, 1
lbl_8004A074:
/* 8004A074 00044F74  88 1F 00 C1 */	lbz r0, 0xc1(r31)
/* 8004A078 00044F78  2C 00 00 00 */	cmpwi r0, 0
/* 8004A07C 00044F7C  41 82 00 08 */	beq lbl_8004A084
/* 8004A080 00044F80  3B A0 00 01 */	li r29, 1
lbl_8004A084:
/* 8004A084 00044F84  88 1F 00 C0 */	lbz r0, 0xc0(r31)
/* 8004A088 00044F88  7C 1D 00 40 */	cmplw r29, r0
/* 8004A08C 00044F8C  41 82 00 1C */	beq lbl_8004A0A8
/* 8004A090 00044F90  80 7F 07 C0 */	lwz r3, 0x7c0(r31)
/* 8004A094 00044F94  2C 03 00 00 */	cmpwi r3, 0
/* 8004A098 00044F98  41 82 00 0C */	beq lbl_8004A0A4
/* 8004A09C 00044F9C  7F A4 EB 78 */	mr r4, r29
/* 8004A0A0 00044FA0  48 00 27 55 */	bl Pause__Q44nw4r3snd6detail5VoiceFb
lbl_8004A0A4:
/* 8004A0A4 00044FA4  9B BF 00 C0 */	stb r29, 0xc0(r31)
lbl_8004A0A8:
/* 8004A0A8 00044FA8  7F C3 F3 78 */	mr r3, r30
/* 8004A0AC 00044FAC  48 0A 78 3D */	bl OSRestoreInterrupts
/* 8004A0B0 00044FB0  48 00 00 20 */	b lbl_8004A0D0
lbl_8004A0B4:
/* 8004A0B4 00044FB4  7F E3 FB 78 */	mr r3, r31
/* 8004A0B8 00044FB8  48 00 00 35 */	bl UpdatePlayingBlockIndex__Q44nw4r3snd6detail10StrmPlayerFv
/* 8004A0BC 00044FBC  7F E3 FB 78 */	mr r3, r31
/* 8004A0C0 00044FC0  48 00 04 1D */	bl UpdateLoadingBlockIndex__Q44nw4r3snd6detail10StrmPlayerFv
lbl_8004A0C4:
/* 8004A0C4 00044FC4  80 1F 00 F0 */	lwz r0, 0xf0(r31)
/* 8004A0C8 00044FC8  7C 00 E8 00 */	cmpw r0, r29
/* 8004A0CC 00044FCC  40 82 FF 60 */	bne lbl_8004A02C
lbl_8004A0D0:
/* 8004A0D0 00044FD0  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8004A0D4 00044FD4  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8004A0D8 00044FD8  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8004A0DC 00044FDC  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8004A0E0 00044FE0  7C 08 03 A6 */	mtlr r0
/* 8004A0E4 00044FE4  38 21 00 20 */	addi r1, r1, 0x20
/* 8004A0E8 00044FE8  4E 80 00 20 */	blr 

.global UpdatePlayingBlockIndex__Q44nw4r3snd6detail10StrmPlayerFv
UpdatePlayingBlockIndex__Q44nw4r3snd6detail10StrmPlayerFv:
/* 8004A0EC 00044FEC  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8004A0F0 00044FF0  7C 08 02 A6 */	mflr r0
/* 8004A0F4 00044FF4  90 01 00 34 */	stw r0, 0x34(r1)
/* 8004A0F8 00044FF8  39 61 00 30 */	addi r11, r1, 0x30
/* 8004A0FC 00044FFC  48 06 7C 49 */	bl _savegpr_27
/* 8004A100 00045000  80 83 00 F4 */	lwz r4, 0xf4(r3)
/* 8004A104 00045004  7C 7F 1B 78 */	mr r31, r3
/* 8004A108 00045008  80 03 00 FC */	lwz r0, 0xfc(r3)
/* 8004A10C 0004500C  38 84 00 01 */	addi r4, r4, 1
/* 8004A110 00045010  7C 04 00 00 */	cmpw r4, r0
/* 8004A114 00045014  90 83 00 F4 */	stw r4, 0xf4(r3)
/* 8004A118 00045018  40 81 00 A4 */	ble lbl_8004A1BC
/* 8004A11C 0004501C  88 03 00 81 */	lbz r0, 0x81(r3)
/* 8004A120 00045020  2C 00 00 00 */	cmpwi r0, 0
/* 8004A124 00045024  41 82 00 98 */	beq lbl_8004A1BC
/* 8004A128 00045028  3C 80 80 00 */	lis r4, 0x7FFFFFFF@ha
/* 8004A12C 0004502C  80 A3 00 C8 */	lwz r5, 0xc8(r3)
/* 8004A130 00045030  38 04 FF FF */	addi r0, r4, 0x7FFFFFFF@l
/* 8004A134 00045034  80 83 00 F8 */	lwz r4, 0xf8(r3)
/* 8004A138 00045038  7C 05 00 00 */	cmpw r5, r0
/* 8004A13C 0004503C  90 83 00 F4 */	stw r4, 0xf4(r3)
/* 8004A140 00045040  40 80 00 0C */	bge lbl_8004A14C
/* 8004A144 00045044  38 05 00 01 */	addi r0, r5, 1
/* 8004A148 00045048  90 03 00 C8 */	stw r0, 0xc8(r3)
lbl_8004A14C:
/* 8004A14C 0004504C  80 83 00 EC */	lwz r4, 0xec(r3)
/* 8004A150 00045050  80 03 00 A0 */	lwz r0, 0xa0(r3)
/* 8004A154 00045054  7F A4 01 D6 */	mullw r29, r4, r0
/* 8004A158 00045058  48 0A 77 69 */	bl OSDisableInterrupts
/* 8004A15C 0004505C  7C 7E 1B 78 */	mr r30, r3
/* 8004A160 00045060  7F FB FB 78 */	mr r27, r31
/* 8004A164 00045064  3B 80 00 00 */	li r28, 0
/* 8004A168 00045068  48 00 00 34 */	b lbl_8004A19C
lbl_8004A16C:
/* 8004A16C 0004506C  80 7F 07 C0 */	lwz r3, 0x7c0(r31)
/* 8004A170 00045070  7F 84 E3 78 */	mr r4, r28
/* 8004A174 00045074  80 BB 07 CC */	lwz r5, 0x7cc(r27)
/* 8004A178 00045078  38 C0 00 00 */	li r6, 0
/* 8004A17C 0004507C  48 00 2C 5D */	bl SetLoopStart__Q44nw4r3snd6detail5VoiceFiPCvUl
/* 8004A180 00045080  80 7F 07 C0 */	lwz r3, 0x7c0(r31)
/* 8004A184 00045084  7F 84 E3 78 */	mr r4, r28
/* 8004A188 00045088  80 BB 07 CC */	lwz r5, 0x7cc(r27)
/* 8004A18C 0004508C  7F A6 EB 78 */	mr r6, r29
/* 8004A190 00045090  48 00 2C BD */	bl SetLoopEnd__Q44nw4r3snd6detail5VoiceFiPCvUl
/* 8004A194 00045094  3B 7B 00 38 */	addi r27, r27, 0x38
/* 8004A198 00045098  3B 9C 00 01 */	addi r28, r28, 1
lbl_8004A19C:
/* 8004A19C 0004509C  80 1F 07 C4 */	lwz r0, 0x7c4(r31)
/* 8004A1A0 000450A0  7C 1C 00 00 */	cmpw r28, r0
/* 8004A1A4 000450A4  41 80 FF C8 */	blt lbl_8004A16C
/* 8004A1A8 000450A8  80 7F 07 C0 */	lwz r3, 0x7c0(r31)
/* 8004A1AC 000450AC  38 80 00 01 */	li r4, 1
/* 8004A1B0 000450B0  48 00 2D 11 */	bl SetLoopFlag__Q44nw4r3snd6detail5VoiceFb
/* 8004A1B4 000450B4  7F C3 F3 78 */	mr r3, r30
/* 8004A1B8 000450B8  48 0A 77 31 */	bl OSRestoreInterrupts
lbl_8004A1BC:
/* 8004A1BC 000450BC  80 7F 00 F0 */	lwz r3, 0xf0(r31)
/* 8004A1C0 000450C0  80 1F 00 EC */	lwz r0, 0xec(r31)
/* 8004A1C4 000450C4  38 63 00 01 */	addi r3, r3, 1
/* 8004A1C8 000450C8  7C 03 00 00 */	cmpw r3, r0
/* 8004A1CC 000450CC  90 7F 00 F0 */	stw r3, 0xf0(r31)
/* 8004A1D0 000450D0  41 80 00 80 */	blt lbl_8004A250
/* 8004A1D4 000450D4  80 7F 00 E0 */	lwz r3, 0xe0(r31)
/* 8004A1D8 000450D8  38 80 00 00 */	li r4, 0
/* 8004A1DC 000450DC  80 1F 00 A0 */	lwz r0, 0xa0(r31)
/* 8004A1E0 000450E0  90 9F 00 F0 */	stw r4, 0xf0(r31)
/* 8004A1E4 000450E4  7F 83 01 D6 */	mullw r28, r3, r0
/* 8004A1E8 000450E8  90 7F 00 EC */	stw r3, 0xec(r31)
/* 8004A1EC 000450EC  48 0A 76 D5 */	bl OSDisableInterrupts
/* 8004A1F0 000450F0  7C 7E 1B 78 */	mr r30, r3
/* 8004A1F4 000450F4  7F FB FB 78 */	mr r27, r31
/* 8004A1F8 000450F8  3B A0 00 00 */	li r29, 0
/* 8004A1FC 000450FC  48 00 00 34 */	b lbl_8004A230
lbl_8004A200:
/* 8004A200 00045100  80 7F 07 C0 */	lwz r3, 0x7c0(r31)
/* 8004A204 00045104  7F A4 EB 78 */	mr r4, r29
/* 8004A208 00045108  80 BB 07 CC */	lwz r5, 0x7cc(r27)
/* 8004A20C 0004510C  38 C0 00 00 */	li r6, 0
/* 8004A210 00045110  48 00 2B C9 */	bl SetLoopStart__Q44nw4r3snd6detail5VoiceFiPCvUl
/* 8004A214 00045114  80 7F 07 C0 */	lwz r3, 0x7c0(r31)
/* 8004A218 00045118  7F A4 EB 78 */	mr r4, r29
/* 8004A21C 0004511C  80 BB 07 CC */	lwz r5, 0x7cc(r27)
/* 8004A220 00045120  7F 86 E3 78 */	mr r6, r28
/* 8004A224 00045124  48 00 2C 29 */	bl SetLoopEnd__Q44nw4r3snd6detail5VoiceFiPCvUl
/* 8004A228 00045128  3B 7B 00 38 */	addi r27, r27, 0x38
/* 8004A22C 0004512C  3B BD 00 01 */	addi r29, r29, 1
lbl_8004A230:
/* 8004A230 00045130  80 1F 07 C4 */	lwz r0, 0x7c4(r31)
/* 8004A234 00045134  7C 1D 00 00 */	cmpw r29, r0
/* 8004A238 00045138  41 80 FF C8 */	blt lbl_8004A200
/* 8004A23C 0004513C  80 7F 07 C0 */	lwz r3, 0x7c0(r31)
/* 8004A240 00045140  38 80 00 01 */	li r4, 1
/* 8004A244 00045144  48 00 2C 7D */	bl SetLoopFlag__Q44nw4r3snd6detail5VoiceFb
/* 8004A248 00045148  7F C3 F3 78 */	mr r3, r30
/* 8004A24C 0004514C  48 0A 76 9D */	bl OSRestoreInterrupts
lbl_8004A250:
/* 8004A250 00045150  80 7F 00 EC */	lwz r3, 0xec(r31)
/* 8004A254 00045154  80 9F 00 F0 */	lwz r4, 0xf0(r31)
/* 8004A258 00045158  38 03 FF FF */	addi r0, r3, -1
/* 8004A25C 0004515C  7C 04 00 00 */	cmpw r4, r0
/* 8004A260 00045160  40 82 00 98 */	bne lbl_8004A2F8
/* 8004A264 00045164  80 7F 07 C0 */	lwz r3, 0x7c0(r31)
/* 8004A268 00045168  48 00 25 AD */	bl GetFormat__Q44nw4r3snd6detail5VoiceCFv
/* 8004A26C 0004516C  2C 03 00 00 */	cmpwi r3, 0
/* 8004A270 00045170  40 82 00 88 */	bne lbl_8004A2F8
/* 8004A274 00045174  88 1F 00 C3 */	lbz r0, 0xc3(r31)
/* 8004A278 00045178  2C 00 00 00 */	cmpwi r0, 0
/* 8004A27C 0004517C  40 82 00 70 */	bne lbl_8004A2EC
/* 8004A280 00045180  88 1F 00 C4 */	lbz r0, 0xc4(r31)
/* 8004A284 00045184  2C 00 00 00 */	cmpwi r0, 0
/* 8004A288 00045188  41 82 00 64 */	beq lbl_8004A2EC
/* 8004A28C 0004518C  48 0A 76 35 */	bl OSDisableInterrupts
/* 8004A290 00045190  7C 7E 1B 78 */	mr r30, r3
/* 8004A294 00045194  7F FC FB 78 */	mr r28, r31
/* 8004A298 00045198  3B 60 00 00 */	li r27, 0
/* 8004A29C 0004519C  3B A0 00 00 */	li r29, 0
/* 8004A2A0 000451A0  48 00 00 2C */	b lbl_8004A2CC
lbl_8004A2A4:
/* 8004A2A4 000451A4  A0 1C 08 3C */	lhz r0, 0x83c(r28)
/* 8004A2A8 000451A8  7F 64 DB 78 */	mr r4, r27
/* 8004A2AC 000451AC  38 A1 00 08 */	addi r5, r1, 8
/* 8004A2B0 000451B0  B0 01 00 08 */	sth r0, 8(r1)
/* 8004A2B4 000451B4  B3 A1 00 0A */	sth r29, 0xa(r1)
/* 8004A2B8 000451B8  B3 A1 00 0C */	sth r29, 0xc(r1)
/* 8004A2BC 000451BC  80 7F 07 C0 */	lwz r3, 0x7c0(r31)
/* 8004A2C0 000451C0  48 00 2A 85 */	bl SetAdpcmLoop__Q44nw4r3snd6detail5VoiceFiPCQ44nw4r3snd6detail14AdpcmLoopParam
/* 8004A2C4 000451C4  3B 9C 00 02 */	addi r28, r28, 2
/* 8004A2C8 000451C8  3B 7B 00 01 */	addi r27, r27, 1
lbl_8004A2CC:
/* 8004A2CC 000451CC  80 1F 07 C4 */	lwz r0, 0x7c4(r31)
/* 8004A2D0 000451D0  7C 1B 00 00 */	cmpw r27, r0
/* 8004A2D4 000451D4  41 80 FF D0 */	blt lbl_8004A2A4
/* 8004A2D8 000451D8  80 7F 07 C0 */	lwz r3, 0x7c0(r31)
/* 8004A2DC 000451DC  38 80 00 01 */	li r4, 1
/* 8004A2E0 000451E0  48 00 2C DD */	bl SetVoiceType__Q44nw4r3snd6detail5VoiceFQ54nw4r3snd6detail7AxVoice9VoiceType
/* 8004A2E4 000451E4  7F C3 F3 78 */	mr r3, r30
/* 8004A2E8 000451E8  48 0A 76 01 */	bl OSRestoreInterrupts
lbl_8004A2EC:
/* 8004A2EC 000451EC  38 00 00 00 */	li r0, 0
/* 8004A2F0 000451F0  98 1F 00 C4 */	stb r0, 0xc4(r31)
/* 8004A2F4 000451F4  98 1F 00 C3 */	stb r0, 0xc3(r31)
lbl_8004A2F8:
/* 8004A2F8 000451F8  80 7F 00 FC */	lwz r3, 0xfc(r31)
/* 8004A2FC 000451FC  80 9F 00 F4 */	lwz r4, 0xf4(r31)
/* 8004A300 00045200  38 03 FF FF */	addi r0, r3, -1
/* 8004A304 00045204  7C 04 00 00 */	cmpw r4, r0
/* 8004A308 00045208  40 82 00 14 */	bne lbl_8004A31C
/* 8004A30C 0004520C  80 9F 00 F0 */	lwz r4, 0xf0(r31)
/* 8004A310 00045210  7F E3 FB 78 */	mr r3, r31
/* 8004A314 00045214  38 84 00 01 */	addi r4, r4, 1
/* 8004A318 00045218  48 00 00 1D */	bl UpdateDataLoopAddress__Q44nw4r3snd6detail10StrmPlayerFl
lbl_8004A31C:
/* 8004A31C 0004521C  39 61 00 30 */	addi r11, r1, 0x30
/* 8004A320 00045220  48 06 7A 71 */	bl _restgpr_27
/* 8004A324 00045224  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8004A328 00045228  7C 08 03 A6 */	mtlr r0
/* 8004A32C 0004522C  38 21 00 30 */	addi r1, r1, 0x30
/* 8004A330 00045230  4E 80 00 20 */	blr 

.global UpdateDataLoopAddress__Q44nw4r3snd6detail10StrmPlayerFl
UpdateDataLoopAddress__Q44nw4r3snd6detail10StrmPlayerFl:
/* 8004A334 00045234  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8004A338 00045238  7C 08 02 A6 */	mflr r0
/* 8004A33C 0004523C  90 01 00 34 */	stw r0, 0x34(r1)
/* 8004A340 00045240  39 61 00 30 */	addi r11, r1, 0x30
/* 8004A344 00045244  48 06 79 F5 */	bl _savegpr_24
/* 8004A348 00045248  88 03 00 81 */	lbz r0, 0x81(r3)
/* 8004A34C 0004524C  7C 7E 1B 78 */	mr r30, r3
/* 8004A350 00045250  7C 9F 23 78 */	mr r31, r4
/* 8004A354 00045254  2C 00 00 00 */	cmpwi r0, 0
/* 8004A358 00045258  41 82 01 14 */	beq lbl_8004A46C
/* 8004A35C 0004525C  80 03 00 EC */	lwz r0, 0xec(r3)
/* 8004A360 00045260  3B 04 00 01 */	addi r24, r4, 1
/* 8004A364 00045264  7C 18 00 00 */	cmpw r24, r0
/* 8004A368 00045268  41 80 00 08 */	blt lbl_8004A370
/* 8004A36C 0004526C  7F 00 C0 50 */	subf r24, r0, r24
lbl_8004A370:
/* 8004A370 00045270  48 0A 75 51 */	bl OSDisableInterrupts
/* 8004A374 00045274  80 9E 00 A0 */	lwz r4, 0xa0(r30)
/* 8004A378 00045278  7C 7D 1B 78 */	mr r29, r3
/* 8004A37C 0004527C  80 7E 00 A8 */	lwz r3, 0xa8(r30)
/* 8004A380 00045280  7C 1F 21 D6 */	mullw r0, r31, r4
/* 8004A384 00045284  7F 78 21 D6 */	mullw r27, r24, r4
/* 8004A388 00045288  7F 43 02 14 */	add r26, r3, r0
/* 8004A38C 0004528C  48 0A 75 35 */	bl OSDisableInterrupts
/* 8004A390 00045290  7C 7C 1B 78 */	mr r28, r3
/* 8004A394 00045294  7F D8 F3 78 */	mr r24, r30
/* 8004A398 00045298  3B 20 00 00 */	li r25, 0
/* 8004A39C 0004529C  48 00 00 34 */	b lbl_8004A3D0
lbl_8004A3A0:
/* 8004A3A0 000452A0  80 7E 07 C0 */	lwz r3, 0x7c0(r30)
/* 8004A3A4 000452A4  7F 24 CB 78 */	mr r4, r25
/* 8004A3A8 000452A8  80 B8 07 CC */	lwz r5, 0x7cc(r24)
/* 8004A3AC 000452AC  7F 66 DB 78 */	mr r6, r27
/* 8004A3B0 000452B0  48 00 2A 29 */	bl SetLoopStart__Q44nw4r3snd6detail5VoiceFiPCvUl
/* 8004A3B4 000452B4  80 7E 07 C0 */	lwz r3, 0x7c0(r30)
/* 8004A3B8 000452B8  7F 24 CB 78 */	mr r4, r25
/* 8004A3BC 000452BC  80 B8 07 CC */	lwz r5, 0x7cc(r24)
/* 8004A3C0 000452C0  7F 46 D3 78 */	mr r6, r26
/* 8004A3C4 000452C4  48 00 2A 89 */	bl SetLoopEnd__Q44nw4r3snd6detail5VoiceFiPCvUl
/* 8004A3C8 000452C8  3B 18 00 38 */	addi r24, r24, 0x38
/* 8004A3CC 000452CC  3B 39 00 01 */	addi r25, r25, 1
lbl_8004A3D0:
/* 8004A3D0 000452D0  80 1E 07 C4 */	lwz r0, 0x7c4(r30)
/* 8004A3D4 000452D4  7C 19 00 00 */	cmpw r25, r0
/* 8004A3D8 000452D8  41 80 FF C8 */	blt lbl_8004A3A0
/* 8004A3DC 000452DC  80 7E 07 C0 */	lwz r3, 0x7c0(r30)
/* 8004A3E0 000452E0  38 80 00 01 */	li r4, 1
/* 8004A3E4 000452E4  48 00 2A DD */	bl SetLoopFlag__Q44nw4r3snd6detail5VoiceFb
/* 8004A3E8 000452E8  7F 83 E3 78 */	mr r3, r28
/* 8004A3EC 000452EC  48 0A 74 FD */	bl OSRestoreInterrupts
/* 8004A3F0 000452F0  88 1E 00 80 */	lbz r0, 0x80(r30)
/* 8004A3F4 000452F4  28 00 00 02 */	cmplwi r0, 2
/* 8004A3F8 000452F8  40 82 00 68 */	bne lbl_8004A460
/* 8004A3FC 000452FC  80 7E 07 C0 */	lwz r3, 0x7c0(r30)
/* 8004A400 00045300  48 00 24 15 */	bl GetFormat__Q44nw4r3snd6detail5VoiceCFv
/* 8004A404 00045304  2C 03 00 00 */	cmpwi r3, 0
/* 8004A408 00045308  40 82 00 40 */	bne lbl_8004A448
/* 8004A40C 0004530C  80 7E 07 C0 */	lwz r3, 0x7c0(r30)
/* 8004A410 00045310  38 80 00 00 */	li r4, 0
/* 8004A414 00045314  48 00 2B A9 */	bl SetVoiceType__Q44nw4r3snd6detail5VoiceFQ54nw4r3snd6detail7AxVoice9VoiceType
/* 8004A418 00045318  3B 3E 07 FC */	addi r25, r30, 0x7fc
/* 8004A41C 0004531C  3B 00 00 00 */	li r24, 0
/* 8004A420 00045320  48 00 00 1C */	b lbl_8004A43C
lbl_8004A424:
/* 8004A424 00045324  80 7E 07 C0 */	lwz r3, 0x7c0(r30)
/* 8004A428 00045328  7F 04 C3 78 */	mr r4, r24
/* 8004A42C 0004532C  7F 25 CB 78 */	mr r5, r25
/* 8004A430 00045330  48 00 29 15 */	bl SetAdpcmLoop__Q44nw4r3snd6detail5VoiceFiPCQ44nw4r3snd6detail14AdpcmLoopParam
/* 8004A434 00045334  3B 39 00 38 */	addi r25, r25, 0x38
/* 8004A438 00045338  3B 18 00 01 */	addi r24, r24, 1
lbl_8004A43C:
/* 8004A43C 0004533C  80 1E 07 C4 */	lwz r0, 0x7c4(r30)
/* 8004A440 00045340  7C 18 00 00 */	cmpw r24, r0
/* 8004A444 00045344  41 80 FF E0 */	blt lbl_8004A424
lbl_8004A448:
/* 8004A448 00045348  80 7E 00 EC */	lwz r3, 0xec(r30)
/* 8004A44C 0004534C  38 03 FF FF */	addi r0, r3, -1
/* 8004A450 00045350  7C 1F 00 00 */	cmpw r31, r0
/* 8004A454 00045354  40 82 00 0C */	bne lbl_8004A460
/* 8004A458 00045358  38 00 00 01 */	li r0, 1
/* 8004A45C 0004535C  98 1E 00 C3 */	stb r0, 0xc3(r30)
lbl_8004A460:
/* 8004A460 00045360  7F A3 EB 78 */	mr r3, r29
/* 8004A464 00045364  48 0A 74 85 */	bl OSRestoreInterrupts
/* 8004A468 00045368  48 00 00 5C */	b lbl_8004A4C4
lbl_8004A46C:
/* 8004A46C 0004536C  48 0A 74 55 */	bl OSDisableInterrupts
/* 8004A470 00045370  7C 7C 1B 78 */	mr r28, r3
/* 8004A474 00045374  7F DA F3 78 */	mr r26, r30
/* 8004A478 00045378  3B 20 00 00 */	li r25, 0
/* 8004A47C 0004537C  48 00 00 2C */	b lbl_8004A4A8
lbl_8004A480:
/* 8004A480 00045380  80 1E 00 A0 */	lwz r0, 0xa0(r30)
/* 8004A484 00045384  7F 24 CB 78 */	mr r4, r25
/* 8004A488 00045388  80 DE 00 A8 */	lwz r6, 0xa8(r30)
/* 8004A48C 0004538C  7C 1F 01 D6 */	mullw r0, r31, r0
/* 8004A490 00045390  80 7E 07 C0 */	lwz r3, 0x7c0(r30)
/* 8004A494 00045394  80 BA 07 CC */	lwz r5, 0x7cc(r26)
/* 8004A498 00045398  7C C6 02 14 */	add r6, r6, r0
/* 8004A49C 0004539C  48 00 2A AD */	bl StopAtPoint__Q44nw4r3snd6detail5VoiceFiPCvUl
/* 8004A4A0 000453A0  3B 5A 00 38 */	addi r26, r26, 0x38
/* 8004A4A4 000453A4  3B 39 00 01 */	addi r25, r25, 1
lbl_8004A4A8:
/* 8004A4A8 000453A8  80 1E 07 C4 */	lwz r0, 0x7c4(r30)
/* 8004A4AC 000453AC  7C 19 00 00 */	cmpw r25, r0
/* 8004A4B0 000453B0  41 80 FF D0 */	blt lbl_8004A480
/* 8004A4B4 000453B4  7F 83 E3 78 */	mr r3, r28
/* 8004A4B8 000453B8  48 0A 74 31 */	bl OSRestoreInterrupts
/* 8004A4BC 000453BC  38 00 00 01 */	li r0, 1
/* 8004A4C0 000453C0  98 1E 00 C5 */	stb r0, 0xc5(r30)
lbl_8004A4C4:
/* 8004A4C4 000453C4  39 61 00 30 */	addi r11, r1, 0x30
/* 8004A4C8 000453C8  48 06 78 BD */	bl _restgpr_24
/* 8004A4CC 000453CC  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8004A4D0 000453D0  7C 08 03 A6 */	mtlr r0
/* 8004A4D4 000453D4  38 21 00 30 */	addi r1, r1, 0x30
/* 8004A4D8 000453D8  4E 80 00 20 */	blr 

.global UpdateLoadingBlockIndex__Q44nw4r3snd6detail10StrmPlayerFv
UpdateLoadingBlockIndex__Q44nw4r3snd6detail10StrmPlayerFv:
/* 8004A4DC 000453DC  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8004A4E0 000453E0  7C 08 02 A6 */	mflr r0
/* 8004A4E4 000453E4  90 01 00 34 */	stw r0, 0x34(r1)
/* 8004A4E8 000453E8  39 61 00 30 */	addi r11, r1, 0x30
/* 8004A4EC 000453EC  48 06 78 55 */	bl _savegpr_26
/* 8004A4F0 000453F0  88 03 00 C6 */	lbz r0, 0xc6(r3)
/* 8004A4F4 000453F4  7C 7D 1B 78 */	mr r29, r3
/* 8004A4F8 000453F8  2C 00 00 00 */	cmpwi r0, 0
/* 8004A4FC 000453FC  40 82 01 F0 */	bne lbl_8004A6EC
/* 8004A500 00045400  80 83 00 98 */	lwz r4, 0x98(r3)
/* 8004A504 00045404  81 23 00 E8 */	lwz r9, 0xe8(r3)
/* 8004A508 00045408  38 04 FF FF */	addi r0, r4, -1
/* 8004A50C 0004540C  7C 09 00 00 */	cmpw r9, r0
/* 8004A510 00045410  40 80 00 0C */	bge lbl_8004A51C
/* 8004A514 00045414  83 E3 00 9C */	lwz r31, 0x9c(r3)
/* 8004A518 00045418  48 00 00 08 */	b lbl_8004A520
lbl_8004A51C:
/* 8004A51C 0004541C  83 E3 00 AC */	lwz r31, 0xac(r3)
lbl_8004A520:
/* 8004A520 00045420  80 83 00 9C */	lwz r4, 0x9c(r3)
/* 8004A524 00045424  38 BF 00 1F */	addi r5, r31, 0x1f
/* 8004A528 00045428  88 03 00 82 */	lbz r0, 0x82(r3)
/* 8004A52C 0004542C  54 A6 00 34 */	rlwinm r6, r5, 0, 0, 0x1a
/* 8004A530 00045430  A1 03 00 88 */	lhz r8, 0x88(r3)
/* 8004A534 00045434  3B C0 00 00 */	li r30, 0
/* 8004A538 00045438  7C 84 01 D6 */	mullw r4, r4, r0
/* 8004A53C 0004543C  80 03 00 E4 */	lwz r0, 0xe4(r3)
/* 8004A540 00045440  80 E3 07 C4 */	lwz r7, 0x7c4(r3)
/* 8004A544 00045444  2C 00 00 00 */	cmpwi r0, 0
/* 8004A548 00045448  80 A3 00 94 */	lwz r5, 0x94(r3)
/* 8004A54C 0004544C  7C 08 22 14 */	add r0, r8, r4
/* 8004A550 00045450  7C 87 31 D6 */	mullw r4, r7, r6
/* 8004A554 00045454  7C 09 01 D6 */	mullw r0, r9, r0
/* 8004A558 00045458  7F 68 22 14 */	add r27, r8, r4
/* 8004A55C 0004545C  7F 45 02 14 */	add r26, r5, r0
/* 8004A560 00045460  40 82 00 14 */	bne lbl_8004A574
/* 8004A564 00045464  88 03 00 80 */	lbz r0, 0x80(r3)
/* 8004A568 00045468  28 00 00 02 */	cmplwi r0, 2
/* 8004A56C 0004546C  40 82 00 08 */	bne lbl_8004A574
/* 8004A570 00045470  3B C0 00 01 */	li r30, 1
lbl_8004A574:
/* 8004A574 00045474  38 63 01 34 */	addi r3, r3, 0x134
/* 8004A578 00045478  4B FF 0C 2D */	bl AllocImpl__Q44nw4r3snd6detail8PoolImplFv
/* 8004A57C 0004547C  2C 03 00 00 */	cmpwi r3, 0
/* 8004A580 00045480  40 82 00 0C */	bne lbl_8004A58C
/* 8004A584 00045484  3B 80 00 00 */	li r28, 0
/* 8004A588 00045488  48 00 00 50 */	b lbl_8004A5D8
lbl_8004A58C:
/* 8004A58C 0004548C  7C 7C 1B 78 */	mr r28, r3
/* 8004A590 00045490  41 82 00 48 */	beq lbl_8004A5D8
/* 8004A594 00045494  38 A0 00 00 */	li r5, 0
/* 8004A598 00045498  3C 80 80 39 */	lis r4, __vt__Q54nw4r3snd6detail10StrmPlayer16StrmDataLoadTask@ha
/* 8004A59C 0004549C  90 A3 00 04 */	stw r5, 4(r3)
/* 8004A5A0 000454A0  38 84 63 90 */	addi r4, r4, __vt__Q54nw4r3snd6detail10StrmPlayer16StrmDataLoadTask@l
/* 8004A5A4 000454A4  38 00 FF FF */	li r0, -1
/* 8004A5A8 000454A8  90 A3 00 08 */	stw r5, 8(r3)
/* 8004A5AC 000454AC  98 A3 00 0C */	stb r5, 0xc(r3)
/* 8004A5B0 000454B0  90 83 00 00 */	stw r4, 0(r3)
/* 8004A5B4 000454B4  90 A3 00 10 */	stw r5, 0x10(r3)
/* 8004A5B8 000454B8  90 A3 00 14 */	stw r5, 0x14(r3)
/* 8004A5BC 000454BC  90 A3 00 18 */	stw r5, 0x18(r3)
/* 8004A5C0 000454C0  90 A3 00 1C */	stw r5, 0x1c(r3)
/* 8004A5C4 000454C4  90 A3 00 20 */	stw r5, 0x20(r3)
/* 8004A5C8 000454C8  90 03 00 24 */	stw r0, 0x24(r3)
/* 8004A5CC 000454CC  98 A3 00 28 */	stb r5, 0x28(r3)
/* 8004A5D0 000454D0  90 A3 00 2C */	stw r5, 0x2c(r3)
/* 8004A5D4 000454D4  90 A3 00 30 */	stw r5, 0x30(r3)
lbl_8004A5D8:
/* 8004A5D8 000454D8  93 BC 00 10 */	stw r29, 0x10(r28)
/* 8004A5DC 000454DC  80 1D 07 BC */	lwz r0, 0x7bc(r29)
/* 8004A5E0 000454E0  90 1C 00 14 */	stw r0, 0x14(r28)
/* 8004A5E4 000454E4  93 7C 00 18 */	stw r27, 0x18(r28)
/* 8004A5E8 000454E8  93 5C 00 1C */	stw r26, 0x1c(r28)
/* 8004A5EC 000454EC  93 FC 00 20 */	stw r31, 0x20(r28)
/* 8004A5F0 000454F0  80 1D 00 E4 */	lwz r0, 0xe4(r29)
/* 8004A5F4 000454F4  90 1C 00 24 */	stw r0, 0x24(r28)
/* 8004A5F8 000454F8  9B DC 00 28 */	stb r30, 0x28(r28)
/* 8004A5FC 000454FC  48 0A 72 C5 */	bl OSDisableInterrupts
/* 8004A600 00045500  38 1D 01 2C */	addi r0, r29, 0x12c
/* 8004A604 00045504  7C 7E 1B 78 */	mr r30, r3
/* 8004A608 00045508  90 01 00 08 */	stw r0, 8(r1)
/* 8004A60C 0004550C  38 7D 01 28 */	addi r3, r29, 0x128
/* 8004A610 00045510  38 81 00 08 */	addi r4, r1, 8
/* 8004A614 00045514  38 BC 00 2C */	addi r5, r28, 0x2c
/* 8004A618 00045518  4B FB D4 75 */	bl Insert__Q44nw4r2ut6detail12LinkListImplFQ54nw4r2ut6detail12LinkListImpl8IteratorPQ34nw4r2ut12LinkListNode
/* 8004A61C 0004551C  88 1D 00 BA */	lbz r0, 0xba(r29)
/* 8004A620 00045520  3B E0 00 01 */	li r31, 1
/* 8004A624 00045524  2C 00 00 00 */	cmpwi r0, 0
/* 8004A628 00045528  41 82 00 08 */	beq lbl_8004A630
/* 8004A62C 0004552C  3B E0 00 02 */	li r31, 2
lbl_8004A630:
/* 8004A630 00045530  48 00 09 C9 */	bl GetInstance__Q44nw4r3snd6detail11TaskManagerFv
/* 8004A634 00045534  7F 84 E3 78 */	mr r4, r28
/* 8004A638 00045538  7F E5 FB 78 */	mr r5, r31
/* 8004A63C 0004553C  48 00 0B 35 */	bl AppendTask__Q44nw4r3snd6detail11TaskManagerFPQ44nw4r3snd6detail4TaskQ54nw4r3snd6detail11TaskManager12TaskPriority
/* 8004A640 00045540  80 7D 00 E8 */	lwz r3, 0xe8(r29)
/* 8004A644 00045544  80 1D 00 FC */	lwz r0, 0xfc(r29)
/* 8004A648 00045548  38 63 00 01 */	addi r3, r3, 1
/* 8004A64C 0004554C  7C 03 00 00 */	cmpw r3, r0
/* 8004A650 00045550  90 7D 00 E8 */	stw r3, 0xe8(r29)
/* 8004A654 00045554  40 81 00 30 */	ble lbl_8004A684
/* 8004A658 00045558  88 1D 00 81 */	lbz r0, 0x81(r29)
/* 8004A65C 0004555C  2C 00 00 00 */	cmpwi r0, 0
/* 8004A660 00045560  41 82 00 10 */	beq lbl_8004A670
/* 8004A664 00045564  80 1D 00 F8 */	lwz r0, 0xf8(r29)
/* 8004A668 00045568  90 1D 00 E8 */	stw r0, 0xe8(r29)
/* 8004A66C 0004556C  48 00 00 18 */	b lbl_8004A684
lbl_8004A670:
/* 8004A670 00045570  38 00 00 01 */	li r0, 1
/* 8004A674 00045574  7F C3 F3 78 */	mr r3, r30
/* 8004A678 00045578  98 1D 00 C6 */	stb r0, 0xc6(r29)
/* 8004A67C 0004557C  48 0A 72 6D */	bl OSRestoreInterrupts
/* 8004A680 00045580  48 00 00 6C */	b lbl_8004A6EC
lbl_8004A684:
/* 8004A684 00045584  80 7D 00 E4 */	lwz r3, 0xe4(r29)
/* 8004A688 00045588  80 1D 00 E0 */	lwz r0, 0xe0(r29)
/* 8004A68C 0004558C  38 63 00 01 */	addi r3, r3, 1
/* 8004A690 00045590  7C 03 00 00 */	cmpw r3, r0
/* 8004A694 00045594  90 7D 00 E4 */	stw r3, 0xe4(r29)
/* 8004A698 00045598  41 80 00 4C */	blt lbl_8004A6E4
/* 8004A69C 0004559C  80 BD 00 FC */	lwz r5, 0xfc(r29)
/* 8004A6A0 000455A0  38 80 00 00 */	li r4, 0
/* 8004A6A4 000455A4  80 7D 00 E8 */	lwz r3, 0xe8(r29)
/* 8004A6A8 000455A8  80 DD 00 DC */	lwz r6, 0xdc(r29)
/* 8004A6AC 000455AC  80 1D 00 F8 */	lwz r0, 0xf8(r29)
/* 8004A6B0 000455B0  7C 63 28 50 */	subf r3, r3, r5
/* 8004A6B4 000455B4  90 9D 00 E4 */	stw r4, 0xe4(r29)
/* 8004A6B8 000455B8  38 83 00 01 */	addi r4, r3, 1
/* 8004A6BC 000455BC  38 E6 00 01 */	addi r7, r6, 1
/* 8004A6C0 000455C0  7C 60 28 50 */	subf r3, r0, r5
/* 8004A6C4 000455C4  7C 84 38 50 */	subf r4, r4, r7
/* 8004A6C8 000455C8  38 63 00 01 */	addi r3, r3, 1
/* 8004A6CC 000455CC  7C 04 1B D6 */	divw r0, r4, r3
/* 8004A6D0 000455D0  7C 00 19 D6 */	mullw r0, r0, r3
/* 8004A6D4 000455D4  7C 00 20 51 */	subf. r0, r0, r4
/* 8004A6D8 000455D8  40 82 00 08 */	bne lbl_8004A6E0
/* 8004A6DC 000455DC  7C E6 3B 78 */	mr r6, r7
lbl_8004A6E0:
/* 8004A6E0 000455E0  90 DD 00 E0 */	stw r6, 0xe0(r29)
lbl_8004A6E4:
/* 8004A6E4 000455E4  7F C3 F3 78 */	mr r3, r30
/* 8004A6E8 000455E8  48 0A 72 01 */	bl OSRestoreInterrupts
lbl_8004A6EC:
/* 8004A6EC 000455EC  39 61 00 30 */	addi r11, r1, 0x30
/* 8004A6F0 000455F0  48 06 76 9D */	bl _restgpr_26
/* 8004A6F4 000455F4  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8004A6F8 000455F8  7C 08 03 A6 */	mtlr r0
/* 8004A6FC 000455FC  38 21 00 30 */	addi r1, r1, 0x30
/* 8004A700 00045600  4E 80 00 20 */	blr 

.global CalcStartOffset__Q44nw4r3snd6detail10StrmPlayerFPlPUlPl
CalcStartOffset__Q44nw4r3snd6detail10StrmPlayerFPlPUlPl:
/* 8004A704 00045604  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8004A708 00045608  7C 08 02 A6 */	mflr r0
/* 8004A70C 0004560C  90 01 00 24 */	stw r0, 0x24(r1)
/* 8004A710 00045610  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8004A714 00045614  7C BF 2B 78 */	mr r31, r5
/* 8004A718 00045618  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8004A71C 0004561C  7C 9E 23 78 */	mr r30, r4
/* 8004A720 00045620  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8004A724 00045624  7C 7D 1B 78 */	mr r29, r3
/* 8004A728 00045628  93 81 00 10 */	stw r28, 0x10(r1)
/* 8004A72C 0004562C  7C DC 33 78 */	mr r28, r6
/* 8004A730 00045630  80 03 00 A0 */	lwz r0, 0xa0(r3)
/* 8004A734 00045634  2C 00 00 00 */	cmpwi r0, 0
/* 8004A738 00045638  40 82 00 0C */	bne lbl_8004A744
/* 8004A73C 0004563C  38 60 00 00 */	li r3, 0
/* 8004A740 00045640  48 00 00 BC */	b lbl_8004A7FC
lbl_8004A744:
/* 8004A744 00045644  80 03 01 00 */	lwz r0, 0x100(r3)
/* 8004A748 00045648  2C 00 00 00 */	cmpwi r0, 0
/* 8004A74C 0004564C  40 82 00 0C */	bne lbl_8004A758
/* 8004A750 00045650  80 83 01 04 */	lwz r4, 0x104(r3)
/* 8004A754 00045654  48 00 00 28 */	b lbl_8004A77C
lbl_8004A758:
/* 8004A758 00045658  2C 00 00 01 */	cmpwi r0, 1
/* 8004A75C 0004565C  40 82 00 20 */	bne lbl_8004A77C
/* 8004A760 00045660  80 E3 01 04 */	lwz r7, 0x104(r3)
/* 8004A764 00045664  38 C0 03 E8 */	li r6, 0x3e8
/* 8004A768 00045668  80 03 00 84 */	lwz r0, 0x84(r3)
/* 8004A76C 0004566C  38 A0 00 00 */	li r5, 0
/* 8004A770 00045670  7C 87 01 D6 */	mullw r4, r7, r0
/* 8004A774 00045674  7C 67 00 96 */	mulhw r3, r7, r0
/* 8004A778 00045678  48 06 77 1D */	bl __div2i
lbl_8004A77C:
/* 8004A77C 0004567C  38 00 00 00 */	li r0, 0
/* 8004A780 00045680  90 1C 00 00 */	stw r0, 0(r28)
/* 8004A784 00045684  80 7D 00 90 */	lwz r3, 0x90(r29)
/* 8004A788 00045688  7C 04 18 40 */	cmplw r4, r3
/* 8004A78C 0004568C  41 80 00 40 */	blt lbl_8004A7CC
/* 8004A790 00045690  88 1D 00 81 */	lbz r0, 0x81(r29)
/* 8004A794 00045694  2C 00 00 00 */	cmpwi r0, 0
/* 8004A798 00045698  41 82 00 2C */	beq lbl_8004A7C4
/* 8004A79C 0004569C  80 BD 00 8C */	lwz r5, 0x8c(r29)
/* 8004A7A0 000456A0  7C 83 20 50 */	subf r4, r3, r4
/* 8004A7A4 000456A4  7C 05 18 50 */	subf r0, r5, r3
/* 8004A7A8 000456A8  7C 64 03 D6 */	divw r3, r4, r0
/* 8004A7AC 000456AC  7C 03 01 D6 */	mullw r0, r3, r0
/* 8004A7B0 000456B0  38 63 00 01 */	addi r3, r3, 1
/* 8004A7B4 000456B4  90 7C 00 00 */	stw r3, 0(r28)
/* 8004A7B8 000456B8  7C 00 20 50 */	subf r0, r0, r4
/* 8004A7BC 000456BC  7C 85 02 14 */	add r4, r5, r0
/* 8004A7C0 000456C0  48 00 00 0C */	b lbl_8004A7CC
lbl_8004A7C4:
/* 8004A7C4 000456C4  38 60 00 00 */	li r3, 0
/* 8004A7C8 000456C8  48 00 00 34 */	b lbl_8004A7FC
lbl_8004A7CC:
/* 8004A7CC 000456CC  80 1D 00 A0 */	lwz r0, 0xa0(r29)
/* 8004A7D0 000456D0  7C 04 03 D6 */	divw r0, r4, r0
/* 8004A7D4 000456D4  90 1E 00 00 */	stw r0, 0(r30)
/* 8004A7D8 000456D8  88 1D 00 80 */	lbz r0, 0x80(r29)
/* 8004A7DC 000456DC  28 00 00 02 */	cmplwi r0, 2
/* 8004A7E0 000456E0  40 82 00 18 */	bne lbl_8004A7F8
/* 8004A7E4 000456E4  80 7D 00 A0 */	lwz r3, 0xa0(r29)
/* 8004A7E8 000456E8  7C 04 1B 96 */	divwu r0, r4, r3
/* 8004A7EC 000456EC  7C 00 19 D6 */	mullw r0, r0, r3
/* 8004A7F0 000456F0  7C 00 20 50 */	subf r0, r0, r4
/* 8004A7F4 000456F4  90 1F 00 00 */	stw r0, 0(r31)
lbl_8004A7F8:
/* 8004A7F8 000456F8  38 60 00 01 */	li r3, 1
lbl_8004A7FC:
/* 8004A7FC 000456FC  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8004A800 00045700  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8004A804 00045704  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8004A808 00045708  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8004A80C 0004570C  83 81 00 10 */	lwz r28, 0x10(r1)
/* 8004A810 00045710  7C 08 03 A6 */	mtlr r0
/* 8004A814 00045714  38 21 00 20 */	addi r1, r1, 0x20
/* 8004A818 00045718  4E 80 00 20 */	blr 

.global VoiceCallbackFunc__Q44nw4r3snd6detail10StrmPlayerFPQ44nw4r3snd6detail5VoiceQ54nw4r3snd6detail5Voice19VoiceCallbackStatusPv
VoiceCallbackFunc__Q44nw4r3snd6detail10StrmPlayerFPQ44nw4r3snd6detail5VoiceQ54nw4r3snd6detail5Voice19VoiceCallbackStatusPv:
/* 8004A81C 0004571C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8004A820 00045720  7C 08 02 A6 */	mflr r0
/* 8004A824 00045724  90 01 00 24 */	stw r0, 0x24(r1)
/* 8004A828 00045728  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8004A82C 0004572C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8004A830 00045730  7C BE 2B 78 */	mr r30, r5
/* 8004A834 00045734  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8004A838 00045738  7C 9D 23 78 */	mr r29, r4
/* 8004A83C 0004573C  93 81 00 10 */	stw r28, 0x10(r1)
/* 8004A840 00045740  7C 7C 1B 78 */	mr r28, r3
/* 8004A844 00045744  48 0A 70 7D */	bl OSDisableInterrupts
/* 8004A848 00045748  2C 1D 00 02 */	cmpwi r29, 2
/* 8004A84C 0004574C  7C 7F 1B 78 */	mr r31, r3
/* 8004A850 00045750  40 80 00 10 */	bge lbl_8004A860
/* 8004A854 00045754  2C 1D 00 00 */	cmpwi r29, 0
/* 8004A858 00045758  40 80 00 14 */	bge lbl_8004A86C
/* 8004A85C 0004575C  48 00 00 30 */	b lbl_8004A88C
lbl_8004A860:
/* 8004A860 00045760  2C 1D 00 04 */	cmpwi r29, 4
/* 8004A864 00045764  40 80 00 28 */	bge lbl_8004A88C
/* 8004A868 00045768  48 00 00 18 */	b lbl_8004A880
lbl_8004A86C:
/* 8004A86C 0004576C  7F 83 E3 78 */	mr r3, r28
/* 8004A870 00045770  48 00 1B 19 */	bl Free__Q44nw4r3snd6detail5VoiceFv
/* 8004A874 00045774  38 00 00 00 */	li r0, 0
/* 8004A878 00045778  90 1E 07 C0 */	stw r0, 0x7c0(r30)
/* 8004A87C 0004577C  48 00 00 1C */	b lbl_8004A898
lbl_8004A880:
/* 8004A880 00045780  38 00 00 00 */	li r0, 0
/* 8004A884 00045784  90 1E 07 C0 */	stw r0, 0x7c0(r30)
/* 8004A888 00045788  48 00 00 10 */	b lbl_8004A898
lbl_8004A88C:
/* 8004A88C 0004578C  7F E3 FB 78 */	mr r3, r31
/* 8004A890 00045790  48 0A 70 59 */	bl OSRestoreInterrupts
/* 8004A894 00045794  48 00 00 0C */	b lbl_8004A8A0
lbl_8004A898:
/* 8004A898 00045798  7F E3 FB 78 */	mr r3, r31
/* 8004A89C 0004579C  48 0A 70 4D */	bl OSRestoreInterrupts
lbl_8004A8A0:
/* 8004A8A0 000457A0  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8004A8A4 000457A4  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8004A8A8 000457A8  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8004A8AC 000457AC  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8004A8B0 000457B0  83 81 00 10 */	lwz r28, 0x10(r1)
/* 8004A8B4 000457B4  7C 08 03 A6 */	mtlr r0
/* 8004A8B8 000457B8  38 21 00 20 */	addi r1, r1, 0x20
/* 8004A8BC 000457BC  4E 80 00 20 */	blr 

.global Execute__Q54nw4r3snd6detail10StrmPlayer18StrmHeaderLoadTaskFv
Execute__Q54nw4r3snd6detail10StrmPlayer18StrmHeaderLoadTaskFv:
/* 8004A8C0 000457C0  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8004A8C4 000457C4  7C 08 02 A6 */	mflr r0
/* 8004A8C8 000457C8  90 01 00 14 */	stw r0, 0x14(r1)
/* 8004A8CC 000457CC  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8004A8D0 000457D0  7C 7F 1B 78 */	mr r31, r3
/* 8004A8D4 000457D4  80 63 00 10 */	lwz r3, 0x10(r3)
/* 8004A8D8 000457D8  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 8004A8DC 000457DC  80 BF 00 18 */	lwz r5, 0x18(r31)
/* 8004A8E0 000457E0  80 DF 00 1C */	lwz r6, 0x1c(r31)
/* 8004A8E4 000457E4  4B FF E9 25 */	bl LoadHeader__Q44nw4r3snd6detail10StrmPlayerFPQ34nw4r2ut10FileStreamQ54nw4r3snd6detail10StrmPlayer15StartOffsetTypei
/* 8004A8E8 000457E8  2C 03 00 00 */	cmpwi r3, 0
/* 8004A8EC 000457EC  40 82 00 10 */	bne lbl_8004A8FC
/* 8004A8F0 000457F0  80 7F 00 10 */	lwz r3, 0x10(r31)
/* 8004A8F4 000457F4  38 00 00 01 */	li r0, 1
/* 8004A8F8 000457F8  98 03 00 BC */	stb r0, 0xbc(r3)
lbl_8004A8FC:
/* 8004A8FC 000457FC  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8004A900 00045800  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8004A904 00045804  7C 08 03 A6 */	mtlr r0
/* 8004A908 00045808  38 21 00 10 */	addi r1, r1, 0x10
/* 8004A90C 0004580C  4E 80 00 20 */	blr 

.global Cancel__Q54nw4r3snd6detail10StrmPlayer18StrmHeaderLoadTaskFv
Cancel__Q54nw4r3snd6detail10StrmPlayer18StrmHeaderLoadTaskFv:
/* 8004A910 00045810  4E 80 00 20 */	blr 

.global OnCancel__Q54nw4r3snd6detail10StrmPlayer18StrmHeaderLoadTaskFv
OnCancel__Q54nw4r3snd6detail10StrmPlayer18StrmHeaderLoadTaskFv:
/* 8004A914 00045814  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8004A918 00045818  7C 08 02 A6 */	mflr r0
/* 8004A91C 0004581C  90 01 00 14 */	stw r0, 0x14(r1)
/* 8004A920 00045820  38 00 00 01 */	li r0, 1
/* 8004A924 00045824  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8004A928 00045828  7C 7F 1B 78 */	mr r31, r3
/* 8004A92C 0004582C  80 83 00 10 */	lwz r4, 0x10(r3)
/* 8004A930 00045830  98 04 00 BD */	stb r0, 0xbd(r4)
/* 8004A934 00045834  80 63 00 14 */	lwz r3, 0x14(r3)
/* 8004A938 00045838  2C 03 00 00 */	cmpwi r3, 0
/* 8004A93C 0004583C  41 82 00 6C */	beq lbl_8004A9A8
/* 8004A940 00045840  81 83 00 00 */	lwz r12, 0(r3)
/* 8004A944 00045844  81 8C 00 54 */	lwz r12, 0x54(r12)
/* 8004A948 00045848  7D 89 03 A6 */	mtctr r12
/* 8004A94C 0004584C  4E 80 04 21 */	bctrl 
/* 8004A950 00045850  2C 03 00 00 */	cmpwi r3, 0
/* 8004A954 00045854  41 82 00 54 */	beq lbl_8004A9A8
/* 8004A958 00045858  80 7F 00 14 */	lwz r3, 0x14(r31)
/* 8004A95C 0004585C  81 83 00 00 */	lwz r12, 0(r3)
/* 8004A960 00045860  81 8C 00 28 */	lwz r12, 0x28(r12)
/* 8004A964 00045864  7D 89 03 A6 */	mtctr r12
/* 8004A968 00045868  4E 80 04 21 */	bctrl 
/* 8004A96C 0004586C  2C 03 00 00 */	cmpwi r3, 0
/* 8004A970 00045870  41 82 00 24 */	beq lbl_8004A994
/* 8004A974 00045874  80 7F 00 14 */	lwz r3, 0x14(r31)
/* 8004A978 00045878  38 80 00 00 */	li r4, 0
/* 8004A97C 0004587C  38 A0 00 00 */	li r5, 0
/* 8004A980 00045880  81 83 00 00 */	lwz r12, 0(r3)
/* 8004A984 00045884  81 8C 00 4C */	lwz r12, 0x4c(r12)
/* 8004A988 00045888  7D 89 03 A6 */	mtctr r12
/* 8004A98C 0004588C  4E 80 04 21 */	bctrl 
/* 8004A990 00045890  48 00 00 18 */	b lbl_8004A9A8
lbl_8004A994:
/* 8004A994 00045894  80 7F 00 14 */	lwz r3, 0x14(r31)
/* 8004A998 00045898  81 83 00 00 */	lwz r12, 0(r3)
/* 8004A99C 0004589C  81 8C 00 48 */	lwz r12, 0x48(r12)
/* 8004A9A0 000458A0  7D 89 03 A6 */	mtctr r12
/* 8004A9A4 000458A4  4E 80 04 21 */	bctrl 
lbl_8004A9A8:
/* 8004A9A8 000458A8  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8004A9AC 000458AC  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8004A9B0 000458B0  7C 08 03 A6 */	mtlr r0
/* 8004A9B4 000458B4  38 21 00 10 */	addi r1, r1, 0x10
/* 8004A9B8 000458B8  4E 80 00 20 */	blr 

.global __ct__Q54nw4r3snd6detail10StrmPlayer16StrmDataLoadTaskFv
__ct__Q54nw4r3snd6detail10StrmPlayer16StrmDataLoadTaskFv:
/* 8004A9BC 000458BC  3C 80 80 39 */	lis r4, __vt__Q54nw4r3snd6detail10StrmPlayer16StrmDataLoadTask@ha
/* 8004A9C0 000458C0  38 A0 00 00 */	li r5, 0
/* 8004A9C4 000458C4  38 84 63 90 */	addi r4, r4, __vt__Q54nw4r3snd6detail10StrmPlayer16StrmDataLoadTask@l
/* 8004A9C8 000458C8  38 00 FF FF */	li r0, -1
/* 8004A9CC 000458CC  90 A3 00 04 */	stw r5, 4(r3)
/* 8004A9D0 000458D0  90 A3 00 08 */	stw r5, 8(r3)
/* 8004A9D4 000458D4  98 A3 00 0C */	stb r5, 0xc(r3)
/* 8004A9D8 000458D8  90 83 00 00 */	stw r4, 0(r3)
/* 8004A9DC 000458DC  90 A3 00 10 */	stw r5, 0x10(r3)
/* 8004A9E0 000458E0  90 A3 00 14 */	stw r5, 0x14(r3)
/* 8004A9E4 000458E4  90 A3 00 18 */	stw r5, 0x18(r3)
/* 8004A9E8 000458E8  90 A3 00 1C */	stw r5, 0x1c(r3)
/* 8004A9EC 000458EC  90 A3 00 20 */	stw r5, 0x20(r3)
/* 8004A9F0 000458F0  90 03 00 24 */	stw r0, 0x24(r3)
/* 8004A9F4 000458F4  98 A3 00 28 */	stb r5, 0x28(r3)
/* 8004A9F8 000458F8  90 A3 00 2C */	stw r5, 0x2c(r3)
/* 8004A9FC 000458FC  90 A3 00 30 */	stw r5, 0x30(r3)
/* 8004AA00 00045900  4E 80 00 20 */	blr 

.global Execute__Q54nw4r3snd6detail10StrmPlayer16StrmDataLoadTaskFv
Execute__Q54nw4r3snd6detail10StrmPlayer16StrmDataLoadTaskFv:
/* 8004AA04 00045904  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8004AA08 00045908  7C 08 02 A6 */	mflr r0
/* 8004AA0C 0004590C  90 01 00 24 */	stw r0, 0x24(r1)
/* 8004AA10 00045910  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8004AA14 00045914  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8004AA18 00045918  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8004AA1C 0004591C  7C 7D 1B 78 */	mr r29, r3
/* 8004AA20 00045920  80 63 00 10 */	lwz r3, 0x10(r3)
/* 8004AA24 00045924  80 9D 00 14 */	lwz r4, 0x14(r29)
/* 8004AA28 00045928  80 BD 00 1C */	lwz r5, 0x1c(r29)
/* 8004AA2C 0004592C  80 DD 00 18 */	lwz r6, 0x18(r29)
/* 8004AA30 00045930  80 FD 00 20 */	lwz r7, 0x20(r29)
/* 8004AA34 00045934  81 1D 00 24 */	lwz r8, 0x24(r29)
/* 8004AA38 00045938  89 3D 00 28 */	lbz r9, 0x28(r29)
/* 8004AA3C 0004593C  4B FF EA 59 */	bl LoadStreamData__Q44nw4r3snd6detail10StrmPlayerFPQ34nw4r2ut10FileStreamiUlUlib
/* 8004AA40 00045940  2C 03 00 00 */	cmpwi r3, 0
/* 8004AA44 00045944  40 82 00 10 */	bne lbl_8004AA54
/* 8004AA48 00045948  80 7D 00 10 */	lwz r3, 0x10(r29)
/* 8004AA4C 0004594C  38 00 00 01 */	li r0, 1
/* 8004AA50 00045950  98 03 00 BC */	stb r0, 0xbc(r3)
lbl_8004AA54:
/* 8004AA54 00045954  48 0A 6E 6D */	bl OSDisableInterrupts
/* 8004AA58 00045958  80 BD 00 10 */	lwz r5, 0x10(r29)
/* 8004AA5C 0004595C  7C 7F 1B 78 */	mr r31, r3
/* 8004AA60 00045960  38 9D 00 2C */	addi r4, r29, 0x2c
/* 8004AA64 00045964  38 65 01 28 */	addi r3, r5, 0x128
/* 8004AA68 00045968  4B FB D0 51 */	bl Erase__Q44nw4r2ut6detail12LinkListImplFPQ34nw4r2ut12LinkListNode
/* 8004AA6C 0004596C  80 7D 00 10 */	lwz r3, 0x10(r29)
/* 8004AA70 00045970  2C 1D 00 00 */	cmpwi r29, 0
/* 8004AA74 00045974  3B C3 01 34 */	addi r30, r3, 0x134
/* 8004AA78 00045978  41 82 00 28 */	beq lbl_8004AAA0
/* 8004AA7C 0004597C  81 9D 00 00 */	lwz r12, 0(r29)
/* 8004AA80 00045980  7F A3 EB 78 */	mr r3, r29
/* 8004AA84 00045984  38 80 FF FF */	li r4, -1
/* 8004AA88 00045988  81 8C 00 08 */	lwz r12, 8(r12)
/* 8004AA8C 0004598C  7D 89 03 A6 */	mtctr r12
/* 8004AA90 00045990  4E 80 04 21 */	bctrl 
/* 8004AA94 00045994  7F C3 F3 78 */	mr r3, r30
/* 8004AA98 00045998  7F A4 EB 78 */	mr r4, r29
/* 8004AA9C 0004599C  4B FF 07 65 */	bl FreeImpl__Q44nw4r3snd6detail8PoolImplFPv
lbl_8004AAA0:
/* 8004AAA0 000459A0  7F E3 FB 78 */	mr r3, r31
/* 8004AAA4 000459A4  48 0A 6E 45 */	bl OSRestoreInterrupts
/* 8004AAA8 000459A8  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8004AAAC 000459AC  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8004AAB0 000459B0  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8004AAB4 000459B4  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8004AAB8 000459B8  7C 08 03 A6 */	mtlr r0
/* 8004AABC 000459BC  38 21 00 20 */	addi r1, r1, 0x20
/* 8004AAC0 000459C0  4E 80 00 20 */	blr 

.global Cancel__Q54nw4r3snd6detail10StrmPlayer16StrmDataLoadTaskFv
Cancel__Q54nw4r3snd6detail10StrmPlayer16StrmDataLoadTaskFv:
/* 8004AAC4 000459C4  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8004AAC8 000459C8  7C 08 02 A6 */	mflr r0
/* 8004AACC 000459CC  90 01 00 24 */	stw r0, 0x24(r1)
/* 8004AAD0 000459D0  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8004AAD4 000459D4  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8004AAD8 000459D8  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8004AADC 000459DC  7C 7D 1B 78 */	mr r29, r3
/* 8004AAE0 000459E0  48 0A 6D E1 */	bl OSDisableInterrupts
/* 8004AAE4 000459E4  80 BD 00 10 */	lwz r5, 0x10(r29)
/* 8004AAE8 000459E8  7C 7F 1B 78 */	mr r31, r3
/* 8004AAEC 000459EC  38 9D 00 2C */	addi r4, r29, 0x2c
/* 8004AAF0 000459F0  38 65 01 28 */	addi r3, r5, 0x128
/* 8004AAF4 000459F4  4B FB CF C5 */	bl Erase__Q44nw4r2ut6detail12LinkListImplFPQ34nw4r2ut12LinkListNode
/* 8004AAF8 000459F8  80 7D 00 10 */	lwz r3, 0x10(r29)
/* 8004AAFC 000459FC  2C 1D 00 00 */	cmpwi r29, 0
/* 8004AB00 00045A00  3B C3 01 34 */	addi r30, r3, 0x134
/* 8004AB04 00045A04  41 82 00 28 */	beq lbl_8004AB2C
/* 8004AB08 00045A08  81 9D 00 00 */	lwz r12, 0(r29)
/* 8004AB0C 00045A0C  7F A3 EB 78 */	mr r3, r29
/* 8004AB10 00045A10  38 80 FF FF */	li r4, -1
/* 8004AB14 00045A14  81 8C 00 08 */	lwz r12, 8(r12)
/* 8004AB18 00045A18  7D 89 03 A6 */	mtctr r12
/* 8004AB1C 00045A1C  4E 80 04 21 */	bctrl 
/* 8004AB20 00045A20  7F C3 F3 78 */	mr r3, r30
/* 8004AB24 00045A24  7F A4 EB 78 */	mr r4, r29
/* 8004AB28 00045A28  4B FF 06 D9 */	bl FreeImpl__Q44nw4r3snd6detail8PoolImplFPv
lbl_8004AB2C:
/* 8004AB2C 00045A2C  7F E3 FB 78 */	mr r3, r31
/* 8004AB30 00045A30  48 0A 6D B9 */	bl OSRestoreInterrupts
/* 8004AB34 00045A34  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8004AB38 00045A38  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8004AB3C 00045A3C  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8004AB40 00045A40  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8004AB44 00045A44  7C 08 03 A6 */	mtlr r0
/* 8004AB48 00045A48  38 21 00 20 */	addi r1, r1, 0x20
/* 8004AB4C 00045A4C  4E 80 00 20 */	blr 

.global OnCancel__Q54nw4r3snd6detail10StrmPlayer16StrmDataLoadTaskFv
OnCancel__Q54nw4r3snd6detail10StrmPlayer16StrmDataLoadTaskFv:
/* 8004AB50 00045A50  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8004AB54 00045A54  7C 08 02 A6 */	mflr r0
/* 8004AB58 00045A58  90 01 00 14 */	stw r0, 0x14(r1)
/* 8004AB5C 00045A5C  38 00 00 01 */	li r0, 1
/* 8004AB60 00045A60  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8004AB64 00045A64  7C 7F 1B 78 */	mr r31, r3
/* 8004AB68 00045A68  80 83 00 10 */	lwz r4, 0x10(r3)
/* 8004AB6C 00045A6C  98 04 00 BD */	stb r0, 0xbd(r4)
/* 8004AB70 00045A70  80 63 00 14 */	lwz r3, 0x14(r3)
/* 8004AB74 00045A74  2C 03 00 00 */	cmpwi r3, 0
/* 8004AB78 00045A78  41 82 00 6C */	beq lbl_8004ABE4
/* 8004AB7C 00045A7C  81 83 00 00 */	lwz r12, 0(r3)
/* 8004AB80 00045A80  81 8C 00 54 */	lwz r12, 0x54(r12)
/* 8004AB84 00045A84  7D 89 03 A6 */	mtctr r12
/* 8004AB88 00045A88  4E 80 04 21 */	bctrl 
/* 8004AB8C 00045A8C  2C 03 00 00 */	cmpwi r3, 0
/* 8004AB90 00045A90  41 82 00 54 */	beq lbl_8004ABE4
/* 8004AB94 00045A94  80 7F 00 14 */	lwz r3, 0x14(r31)
/* 8004AB98 00045A98  81 83 00 00 */	lwz r12, 0(r3)
/* 8004AB9C 00045A9C  81 8C 00 28 */	lwz r12, 0x28(r12)
/* 8004ABA0 00045AA0  7D 89 03 A6 */	mtctr r12
/* 8004ABA4 00045AA4  4E 80 04 21 */	bctrl 
/* 8004ABA8 00045AA8  2C 03 00 00 */	cmpwi r3, 0
/* 8004ABAC 00045AAC  41 82 00 24 */	beq lbl_8004ABD0
/* 8004ABB0 00045AB0  80 7F 00 14 */	lwz r3, 0x14(r31)
/* 8004ABB4 00045AB4  38 80 00 00 */	li r4, 0
/* 8004ABB8 00045AB8  38 A0 00 00 */	li r5, 0
/* 8004ABBC 00045ABC  81 83 00 00 */	lwz r12, 0(r3)
/* 8004ABC0 00045AC0  81 8C 00 4C */	lwz r12, 0x4c(r12)
/* 8004ABC4 00045AC4  7D 89 03 A6 */	mtctr r12
/* 8004ABC8 00045AC8  4E 80 04 21 */	bctrl 
/* 8004ABCC 00045ACC  48 00 00 18 */	b lbl_8004ABE4
lbl_8004ABD0:
/* 8004ABD0 00045AD0  80 7F 00 14 */	lwz r3, 0x14(r31)
/* 8004ABD4 00045AD4  81 83 00 00 */	lwz r12, 0(r3)
/* 8004ABD8 00045AD8  81 8C 00 48 */	lwz r12, 0x48(r12)
/* 8004ABDC 00045ADC  7D 89 03 A6 */	mtctr r12
/* 8004ABE0 00045AE0  4E 80 04 21 */	bctrl 
lbl_8004ABE4:
/* 8004ABE4 00045AE4  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8004ABE8 00045AE8  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8004ABEC 00045AEC  7C 08 03 A6 */	mtlr r0
/* 8004ABF0 00045AF0  38 21 00 10 */	addi r1, r1, 0x10
/* 8004ABF4 00045AF4  4E 80 00 20 */	blr 

.global OnUpdateFrameSoundThread__Q44nw4r3snd6detail10StrmPlayerFv
OnUpdateFrameSoundThread__Q44nw4r3snd6detail10StrmPlayerFv:
/* 8004ABF8 00045AF8  4B FF EF B8 */	b Update__Q44nw4r3snd6detail10StrmPlayerFv

.global OnUpdateVoiceSoundThread__Q44nw4r3snd6detail10StrmPlayerFv
OnUpdateVoiceSoundThread__Q44nw4r3snd6detail10StrmPlayerFv:
/* 8004ABFC 00045AFC  4B FF F3 54 */	b UpdateBuffer__Q44nw4r3snd6detail10StrmPlayerFv

.global OnShutdownSoundThread__Q44nw4r3snd6detail10StrmPlayerFv
OnShutdownSoundThread__Q44nw4r3snd6detail10StrmPlayerFv:
/* 8004AC00 00045B00  81 83 00 00 */	lwz r12, 0(r3)
/* 8004AC04 00045B04  81 8C 00 10 */	lwz r12, 0x10(r12)
/* 8004AC08 00045B08  7D 89 03 A6 */	mtctr r12
/* 8004AC0C 00045B0C  4E 80 04 20 */	bctr 

.global IsPause__Q44nw4r3snd6detail10StrmPlayerCFv
IsPause__Q44nw4r3snd6detail10StrmPlayerCFv:
/* 8004AC10 00045B10  88 63 00 BF */	lbz r3, 0xbf(r3)
/* 8004AC14 00045B14  4E 80 00 20 */	blr 

.global IsStarted__Q44nw4r3snd6detail10StrmPlayerCFv
IsStarted__Q44nw4r3snd6detail10StrmPlayerCFv:
/* 8004AC18 00045B18  88 63 00 BA */	lbz r3, 0xba(r3)
/* 8004AC1C 00045B1C  4E 80 00 20 */	blr 

.global IsActive__Q44nw4r3snd6detail10StrmPlayerCFv
IsActive__Q44nw4r3snd6detail10StrmPlayerCFv:
/* 8004AC20 00045B20  88 63 00 B9 */	lbz r3, 0xb9(r3)
/* 8004AC24 00045B24  4E 80 00 20 */	blr 

.global $2116$2OnShutdownSoundThread__Q44nw4r3snd6detail10StrmPlayerFv
$2116$2OnShutdownSoundThread__Q44nw4r3snd6detail10StrmPlayerFv:
/* 8004AC28 00045B28  38 63 FF 8C */	addi r3, r3, -116
/* 8004AC2C 00045B2C  4B FF FF D4 */	b OnShutdownSoundThread__Q44nw4r3snd6detail10StrmPlayerFv

.global $2116$2OnUpdateVoiceSoundThread__Q44nw4r3snd6detail10StrmPlayerFv
$2116$2OnUpdateVoiceSoundThread__Q44nw4r3snd6detail10StrmPlayerFv:
/* 8004AC30 00045B30  38 63 FF 8C */	addi r3, r3, -116
/* 8004AC34 00045B34  4B FF FF C8 */	b OnUpdateVoiceSoundThread__Q44nw4r3snd6detail10StrmPlayerFv

.global $2116$2OnUpdateFrameSoundThread__Q44nw4r3snd6detail10StrmPlayerFv
$2116$2OnUpdateFrameSoundThread__Q44nw4r3snd6detail10StrmPlayerFv:
/* 8004AC38 00045B38  38 63 FF 8C */	addi r3, r3, -116
/* 8004AC3C 00045B3C  4B FF FF BC */	b OnUpdateFrameSoundThread__Q44nw4r3snd6detail10StrmPlayerFv

.global $2116$2__dt__Q44nw4r3snd6detail10StrmPlayerFv
$2116$2__dt__Q44nw4r3snd6detail10StrmPlayerFv:
/* 8004AC40 00045B40  38 63 FF 8C */	addi r3, r3, -116
/* 8004AC44 00045B44  4B FF DD 20 */	b __dt__Q44nw4r3snd6detail10StrmPlayerFv
