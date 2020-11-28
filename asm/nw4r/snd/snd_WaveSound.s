.include "macros.inc"

.section .text, "ax"  # 0x800076E0 - 0x80355080 

# __ct__Q44nw4r3snd6detail9WaveSoundFPQ44nw4r3snd6detail50SoundInstanceManager<Q44nw4r3snd6detail9WaveSound>
.global __ct__Q44nw4r3snd6detail9WaveSoundFPQ44nw4r3snd6detail50SoundInstanceManager$$0Q44nw4r3snd6detail9WaveSound$$1
__ct__Q44nw4r3snd6detail9WaveSoundFPQ44nw4r3snd6detail50SoundInstanceManager$$0Q44nw4r3snd6detail9WaveSound$$1:
/* 8004EEE0 00049DE0  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8004EEE4 00049DE4  7C 08 02 A6 */	mflr r0
/* 8004EEE8 00049DE8  90 01 00 14 */	stw r0, 0x14(r1)
/* 8004EEEC 00049DEC  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8004EEF0 00049DF0  7C 9F 23 78 */	mr r31, r4
/* 8004EEF4 00049DF4  93 C1 00 08 */	stw r30, 8(r1)
/* 8004EEF8 00049DF8  7C 7E 1B 78 */	mr r30, r3
/* 8004EEFC 00049DFC  4B FE 73 85 */	bl __ct__Q44nw4r3snd6detail10BasicSoundFv
/* 8004EF00 00049E00  3C 80 80 39 */	lis r4, lbl_80396478@ha
/* 8004EF04 00049E04  38 7E 00 D8 */	addi r3, r30, 0xd8
/* 8004EF08 00049E08  38 84 64 78 */	addi r4, r4, lbl_80396478@l
/* 8004EF0C 00049E0C  90 9E 00 00 */	stw r4, 0(r30)
/* 8004EF10 00049E10  48 00 06 A9 */	bl __ct__Q44nw4r3snd6detail9WsdPlayerFv
/* 8004EF14 00049E14  38 00 00 00 */	li r0, 0
/* 8004EF18 00049E18  93 FE 01 B4 */	stw r31, 0x1b4(r30)
/* 8004EF1C 00049E1C  7F C3 F3 78 */	mr r3, r30
/* 8004EF20 00049E20  90 1E 01 B0 */	stw r0, 0x1b0(r30)
/* 8004EF24 00049E24  98 1E 01 B8 */	stb r0, 0x1b8(r30)
/* 8004EF28 00049E28  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8004EF2C 00049E2C  83 C1 00 08 */	lwz r30, 8(r1)
/* 8004EF30 00049E30  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8004EF34 00049E34  7C 08 03 A6 */	mtlr r0
/* 8004EF38 00049E38  38 21 00 10 */	addi r1, r1, 0x10
/* 8004EF3C 00049E3C  4E 80 00 20 */	blr 

.global __dt__Q44nw4r3snd6detail9WsdPlayerFv
__dt__Q44nw4r3snd6detail9WsdPlayerFv:
/* 8004EF40 00049E40  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8004EF44 00049E44  7C 08 02 A6 */	mflr r0
/* 8004EF48 00049E48  2C 03 00 00 */	cmpwi r3, 0
/* 8004EF4C 00049E4C  90 01 00 14 */	stw r0, 0x14(r1)
/* 8004EF50 00049E50  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8004EF54 00049E54  7C 7F 1B 78 */	mr r31, r3
/* 8004EF58 00049E58  41 82 00 10 */	beq lbl_8004EF68
/* 8004EF5C 00049E5C  2C 04 00 00 */	cmpwi r4, 0
/* 8004EF60 00049E60  40 81 00 08 */	ble lbl_8004EF68
/* 8004EF64 00049E64  48 05 43 21 */	bl __dl__FPv
lbl_8004EF68:
/* 8004EF68 00049E68  7F E3 FB 78 */	mr r3, r31
/* 8004EF6C 00049E6C  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8004EF70 00049E70  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8004EF74 00049E74  7C 08 03 A6 */	mtlr r0
/* 8004EF78 00049E78  38 21 00 10 */	addi r1, r1, 0x10
/* 8004EF7C 00049E7C  4E 80 00 20 */	blr 

.global Prepare__Q44nw4r3snd6detail9WaveSoundFPCvlQ54nw4r3snd6detail9WsdPlayer15StartOffsetTypeliPCQ54nw4r3snd6detail9WsdPlayer11WsdCallbackUl
Prepare__Q44nw4r3snd6detail9WaveSoundFPCvlQ54nw4r3snd6detail9WsdPlayer15StartOffsetTypeliPCQ54nw4r3snd6detail9WsdPlayer11WsdCallbackUl:
/* 8004EF80 00049E80  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8004EF84 00049E84  7C 08 02 A6 */	mflr r0
/* 8004EF88 00049E88  90 01 00 34 */	stw r0, 0x34(r1)
/* 8004EF8C 00049E8C  39 61 00 30 */	addi r11, r1, 0x30
/* 8004EF90 00049E90  48 06 2D A9 */	bl _savegpr_24
/* 8004EF94 00049E94  81 83 00 00 */	lwz r12, 0(r3)
/* 8004EF98 00049E98  7C 78 1B 78 */	mr r24, r3
/* 8004EF9C 00049E9C  7C 99 23 78 */	mr r25, r4
/* 8004EFA0 00049EA0  7C BA 2B 78 */	mr r26, r5
/* 8004EFA4 00049EA4  81 8C 00 64 */	lwz r12, 0x64(r12)
/* 8004EFA8 00049EA8  7C DB 33 78 */	mr r27, r6
/* 8004EFAC 00049EAC  7C FC 3B 78 */	mr r28, r7
/* 8004EFB0 00049EB0  7D 1D 43 78 */	mr r29, r8
/* 8004EFB4 00049EB4  7D 3E 4B 78 */	mr r30, r9
/* 8004EFB8 00049EB8  7D 5F 53 78 */	mr r31, r10
/* 8004EFBC 00049EBC  7D 89 03 A6 */	mtctr r12
/* 8004EFC0 00049EC0  4E 80 04 21 */	bctrl 
/* 8004EFC4 00049EC4  7F 24 CB 78 */	mr r4, r25
/* 8004EFC8 00049EC8  7F 45 D3 78 */	mr r5, r26
/* 8004EFCC 00049ECC  7F 66 DB 78 */	mr r6, r27
/* 8004EFD0 00049ED0  7F 87 E3 78 */	mr r7, r28
/* 8004EFD4 00049ED4  7F A8 EB 78 */	mr r8, r29
/* 8004EFD8 00049ED8  7F C9 F3 78 */	mr r9, r30
/* 8004EFDC 00049EDC  7F EA FB 78 */	mr r10, r31
/* 8004EFE0 00049EE0  38 78 00 D8 */	addi r3, r24, 0xd8
/* 8004EFE4 00049EE4  48 00 06 E9 */	bl Prepare__Q44nw4r3snd6detail9WsdPlayerFPCviQ54nw4r3snd6detail9WsdPlayer15StartOffsetTypeiiPCQ54nw4r3snd6detail9WsdPlayer11WsdCallbackUl
/* 8004EFE8 00049EE8  2C 03 00 00 */	cmpwi r3, 0
/* 8004EFEC 00049EEC  40 82 00 0C */	bne lbl_8004EFF8
/* 8004EFF0 00049EF0  38 60 00 00 */	li r3, 0
/* 8004EFF4 00049EF4  48 00 00 10 */	b lbl_8004F004
lbl_8004EFF8:
/* 8004EFF8 00049EF8  38 00 00 01 */	li r0, 1
/* 8004EFFC 00049EFC  38 60 00 01 */	li r3, 1
/* 8004F000 00049F00  98 18 01 B8 */	stb r0, 0x1b8(r24)
lbl_8004F004:
/* 8004F004 00049F04  39 61 00 30 */	addi r11, r1, 0x30
/* 8004F008 00049F08  48 06 2D 7D */	bl _restgpr_24
/* 8004F00C 00049F0C  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8004F010 00049F10  7C 08 03 A6 */	mtlr r0
/* 8004F014 00049F14  38 21 00 30 */	addi r1, r1, 0x30
/* 8004F018 00049F18  4E 80 00 20 */	blr 

.global Shutdown__Q44nw4r3snd6detail9WaveSoundFv
Shutdown__Q44nw4r3snd6detail9WaveSoundFv:
/* 8004F01C 00049F1C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8004F020 00049F20  7C 08 02 A6 */	mflr r0
/* 8004F024 00049F24  90 01 00 24 */	stw r0, 0x24(r1)
/* 8004F028 00049F28  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8004F02C 00049F2C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8004F030 00049F30  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8004F034 00049F34  7C 7D 1B 78 */	mr r29, r3
/* 8004F038 00049F38  4B FE 7E E1 */	bl Shutdown__Q44nw4r3snd6detail10BasicSoundFv
/* 8004F03C 00049F3C  83 DD 01 B4 */	lwz r30, 0x1b4(r29)
/* 8004F040 00049F40  3B FE 00 10 */	addi r31, r30, 0x10
/* 8004F044 00049F44  7F E3 FB 78 */	mr r3, r31
/* 8004F048 00049F48  48 0A 3B 35 */	bl OSLockMutex
/* 8004F04C 00049F4C  80 1E 00 04 */	lwz r0, 4(r30)
/* 8004F050 00049F50  2C 00 00 00 */	cmpwi r0, 0
/* 8004F054 00049F54  40 82 00 10 */	bne lbl_8004F064
/* 8004F058 00049F58  7F E3 FB 78 */	mr r3, r31
/* 8004F05C 00049F5C  48 0A 3B FD */	bl OSUnlockMutex
/* 8004F060 00049F60  48 00 00 3C */	b lbl_8004F09C
lbl_8004F064:
/* 8004F064 00049F64  38 7E 00 04 */	addi r3, r30, 4
/* 8004F068 00049F68  38 9D 00 B8 */	addi r4, r29, 0xb8
/* 8004F06C 00049F6C  4B FB 8A 4D */	bl Erase__Q44nw4r2ut6detail12LinkListImplFPQ34nw4r2ut12LinkListNode
/* 8004F070 00049F70  81 9D 00 00 */	lwz r12, 0(r29)
/* 8004F074 00049F74  7F A3 EB 78 */	mr r3, r29
/* 8004F078 00049F78  38 80 FF FF */	li r4, -1
/* 8004F07C 00049F7C  81 8C 00 0C */	lwz r12, 0xc(r12)
/* 8004F080 00049F80  7D 89 03 A6 */	mtctr r12
/* 8004F084 00049F84  4E 80 04 21 */	bctrl 
/* 8004F088 00049F88  7F C3 F3 78 */	mr r3, r30
/* 8004F08C 00049F8C  7F A4 EB 78 */	mr r4, r29
/* 8004F090 00049F90  4B FE C1 71 */	bl FreeImpl__Q44nw4r3snd6detail8PoolImplFPv
/* 8004F094 00049F94  7F E3 FB 78 */	mr r3, r31
/* 8004F098 00049F98  48 0A 3B C1 */	bl OSUnlockMutex
lbl_8004F09C:
/* 8004F09C 00049F9C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8004F0A0 00049FA0  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8004F0A4 00049FA4  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8004F0A8 00049FA8  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8004F0AC 00049FAC  7C 08 03 A6 */	mtlr r0
/* 8004F0B0 00049FB0  38 21 00 20 */	addi r1, r1, 0x20
/* 8004F0B4 00049FB4  4E 80 00 20 */	blr 

.global __dt__Q44nw4r3snd6detail9WaveSoundFv
__dt__Q44nw4r3snd6detail9WaveSoundFv:
/* 8004F0B8 00049FB8  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8004F0BC 00049FBC  7C 08 02 A6 */	mflr r0
/* 8004F0C0 00049FC0  2C 03 00 00 */	cmpwi r3, 0
/* 8004F0C4 00049FC4  90 01 00 14 */	stw r0, 0x14(r1)
/* 8004F0C8 00049FC8  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8004F0CC 00049FCC  7C 7F 1B 78 */	mr r31, r3
/* 8004F0D0 00049FD0  41 82 00 10 */	beq lbl_8004F0E0
/* 8004F0D4 00049FD4  2C 04 00 00 */	cmpwi r4, 0
/* 8004F0D8 00049FD8  40 81 00 08 */	ble lbl_8004F0E0
/* 8004F0DC 00049FDC  48 05 41 A9 */	bl __dl__FPv
lbl_8004F0E0:
/* 8004F0E0 00049FE0  7F E3 FB 78 */	mr r3, r31
/* 8004F0E4 00049FE4  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8004F0E8 00049FE8  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8004F0EC 00049FEC  7C 08 03 A6 */	mtlr r0
/* 8004F0F0 00049FF0  38 21 00 10 */	addi r1, r1, 0x10
/* 8004F0F4 00049FF4  4E 80 00 20 */	blr 

.global SetChannelPriority__Q44nw4r3snd6detail9WaveSoundFi
SetChannelPriority__Q44nw4r3snd6detail9WaveSoundFi:
/* 8004F0F8 00049FF8  38 63 00 D8 */	addi r3, r3, 0xd8
/* 8004F0FC 00049FFC  48 00 09 B8 */	b SetChannelPriority__Q44nw4r3snd6detail9WsdPlayerFi

.global SetReleasePriorityFix__Q44nw4r3snd6detail9WaveSoundFb
SetReleasePriorityFix__Q44nw4r3snd6detail9WaveSoundFb:
/* 8004F100 0004A000  38 63 00 D8 */	addi r3, r3, 0xd8
/* 8004F104 0004A004  48 00 09 B8 */	b SetReleasePriorityFix__Q44nw4r3snd6detail9WsdPlayerFb

.global SetPlayerPriority__Q44nw4r3snd6detail9WaveSoundFi
SetPlayerPriority__Q44nw4r3snd6detail9WaveSoundFi:
/* 8004F108 0004A008  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8004F10C 0004A00C  7C 08 02 A6 */	mflr r0
/* 8004F110 0004A010  90 01 00 24 */	stw r0, 0x24(r1)
/* 8004F114 0004A014  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8004F118 0004A018  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8004F11C 0004A01C  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8004F120 0004A020  93 81 00 10 */	stw r28, 0x10(r1)
/* 8004F124 0004A024  7C 7C 1B 78 */	mr r28, r3
/* 8004F128 0004A028  4B FE 7F 61 */	bl SetPlayerPriority__Q44nw4r3snd6detail10BasicSoundFi
/* 8004F12C 0004A02C  88 7C 00 74 */	lbz r3, 0x74(r28)
/* 8004F130 0004A030  80 1C 00 40 */	lwz r0, 0x40(r28)
/* 8004F134 0004A034  7C 63 02 14 */	add r3, r3, r0
/* 8004F138 0004A038  2C 03 00 7F */	cmpwi r3, 0x7f
/* 8004F13C 0004A03C  40 81 00 0C */	ble lbl_8004F148
/* 8004F140 0004A040  3B A0 00 7F */	li r29, 0x7f
/* 8004F144 0004A044  48 00 00 0C */	b lbl_8004F150
lbl_8004F148:
/* 8004F148 0004A048  7C 60 FE 70 */	srawi r0, r3, 0x1f
/* 8004F14C 0004A04C  7C 7D 00 78 */	andc r29, r3, r0
lbl_8004F150:
/* 8004F150 0004A050  83 DC 01 B4 */	lwz r30, 0x1b4(r28)
/* 8004F154 0004A054  3B FE 00 10 */	addi r31, r30, 0x10
/* 8004F158 0004A058  7F E3 FB 78 */	mr r3, r31
/* 8004F15C 0004A05C  48 0A 3A 21 */	bl OSLockMutex
/* 8004F160 0004A060  3B 9C 00 B8 */	addi r28, r28, 0xb8
/* 8004F164 0004A064  38 7E 00 04 */	addi r3, r30, 4
/* 8004F168 0004A068  7F 84 E3 78 */	mr r4, r28
/* 8004F16C 0004A06C  4B FB 89 4D */	bl Erase__Q44nw4r2ut6detail12LinkListImplFPQ34nw4r2ut12LinkListNode
/* 8004F170 0004A070  80 7E 00 08 */	lwz r3, 8(r30)
/* 8004F174 0004A074  38 1E 00 08 */	addi r0, r30, 8
/* 8004F178 0004A078  48 00 00 34 */	b lbl_8004F1AC
lbl_8004F17C:
/* 8004F17C 0004A07C  88 A3 FF BC */	lbz r5, -0x44(r3)
/* 8004F180 0004A080  80 83 FF 88 */	lwz r4, -0x78(r3)
/* 8004F184 0004A084  7C A5 22 14 */	add r5, r5, r4
/* 8004F188 0004A088  2C 05 00 7F */	cmpwi r5, 0x7f
/* 8004F18C 0004A08C  40 81 00 0C */	ble lbl_8004F198
/* 8004F190 0004A090  38 80 00 7F */	li r4, 0x7f
/* 8004F194 0004A094  48 00 00 0C */	b lbl_8004F1A0
lbl_8004F198:
/* 8004F198 0004A098  7C A4 FE 70 */	srawi r4, r5, 0x1f
/* 8004F19C 0004A09C  7C A4 20 78 */	andc r4, r5, r4
lbl_8004F1A0:
/* 8004F1A0 0004A0A0  7C 1D 20 00 */	cmpw r29, r4
/* 8004F1A4 0004A0A4  41 80 00 10 */	blt lbl_8004F1B4
/* 8004F1A8 0004A0A8  80 63 00 00 */	lwz r3, 0(r3)
lbl_8004F1AC:
/* 8004F1AC 0004A0AC  7C 03 00 40 */	cmplw r3, r0
/* 8004F1B0 0004A0B0  40 82 FF CC */	bne lbl_8004F17C
lbl_8004F1B4:
/* 8004F1B4 0004A0B4  90 61 00 08 */	stw r3, 8(r1)
/* 8004F1B8 0004A0B8  7F 85 E3 78 */	mr r5, r28
/* 8004F1BC 0004A0BC  38 7E 00 04 */	addi r3, r30, 4
/* 8004F1C0 0004A0C0  38 81 00 08 */	addi r4, r1, 8
/* 8004F1C4 0004A0C4  4B FB 88 C9 */	bl Insert__Q44nw4r2ut6detail12LinkListImplFQ54nw4r2ut6detail12LinkListImpl8IteratorPQ34nw4r2ut12LinkListNode
/* 8004F1C8 0004A0C8  7F E3 FB 78 */	mr r3, r31
/* 8004F1CC 0004A0CC  48 0A 3A 8D */	bl OSUnlockMutex
/* 8004F1D0 0004A0D0  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8004F1D4 0004A0D4  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8004F1D8 0004A0D8  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8004F1DC 0004A0DC  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8004F1E0 0004A0E0  83 81 00 10 */	lwz r28, 0x10(r1)
/* 8004F1E4 0004A0E4  7C 08 03 A6 */	mtlr r0
/* 8004F1E8 0004A0E8  38 21 00 20 */	addi r1, r1, 0x20
/* 8004F1EC 0004A0EC  4E 80 00 20 */	blr 

.global IsAttachedTempSpecialHandle__Q44nw4r3snd6detail9WaveSoundFv
IsAttachedTempSpecialHandle__Q44nw4r3snd6detail9WaveSoundFv:
/* 8004F1F0 0004A0F0  80 63 01 B0 */	lwz r3, 0x1b0(r3)
/* 8004F1F4 0004A0F4  7C 03 00 D0 */	neg r0, r3
/* 8004F1F8 0004A0F8  7C 00 1B 78 */	or r0, r0, r3
/* 8004F1FC 0004A0FC  54 03 0F FE */	srwi r3, r0, 0x1f
/* 8004F200 0004A100  4E 80 00 20 */	blr 

.global DetachTempSpecialHandle__Q44nw4r3snd6detail9WaveSoundFv
DetachTempSpecialHandle__Q44nw4r3snd6detail9WaveSoundFv:
/* 8004F204 0004A104  80 63 01 B0 */	lwz r3, 0x1b0(r3)
/* 8004F208 0004A108  48 00 00 30 */	b DetachSound__Q34nw4r3snd15WaveSoundHandleFv

.global GetBasicPlayer__Q44nw4r3snd6detail9WaveSoundFv
GetBasicPlayer__Q44nw4r3snd6detail9WaveSoundFv:
/* 8004F20C 0004A10C  38 63 00 D8 */	addi r3, r3, 0xd8
/* 8004F210 0004A110  4E 80 00 20 */	blr 

.global GetBasicPlayer__Q44nw4r3snd6detail9WaveSoundCFv
GetBasicPlayer__Q44nw4r3snd6detail9WaveSoundCFv:
/* 8004F214 0004A114  38 63 00 D8 */	addi r3, r3, 0xd8
/* 8004F218 0004A118  4E 80 00 20 */	blr 

.global IsPrepared__Q44nw4r3snd6detail9WaveSoundCFv
IsPrepared__Q44nw4r3snd6detail9WaveSoundCFv:
/* 8004F21C 0004A11C  88 63 01 B8 */	lbz r3, 0x1b8(r3)
/* 8004F220 0004A120  4E 80 00 20 */	blr 

.global GetRuntimeTypeInfo__Q44nw4r3snd6detail9WaveSoundCFv
GetRuntimeTypeInfo__Q44nw4r3snd6detail9WaveSoundCFv:
/* 8004F224 0004A124  38 6D 97 B8 */	addi r3, r13, lbl_804BEB38-_SDA_BASE_
/* 8004F228 0004A128  4E 80 00 20 */	blr 

# __sinit_\snd_WaveSound_cpp
.global __sinit_$$3snd_WaveSound_cpp
__sinit_$$3snd_WaveSound_cpp:
/* 8004F22C 0004A12C  38 0D 96 F8 */	addi r0, r13, typeInfo__Q44nw4r3snd6detail10BasicSound-_SDA_BASE_
/* 8004F230 0004A130  90 0D 97 B8 */	stw r0, lbl_804BEB38-_SDA_BASE_(r13)
/* 8004F234 0004A134  4E 80 00 20 */	blr 
