.include "macros.inc"

.section .rodata, "a"
.balign 8
.global lbl_8037B0C0
lbl_8037B0C0:
	.string "eggAudioHeapMgr.cpp"
    .string "mHeap.IsValid()"

.section .data, "wa"
.balign 8
.global __vt__Q23EGG14SimpleAudioMgr
__vt__Q23EGG14SimpleAudioMgr:
    .long 0
    .long 0
    .long initialize__Q23EGG14SimpleAudioMgrFPQ33EGG9IAudioMgr3Arg
    .long calc__Q23EGG14SimpleAudioMgrFv
.global vtable_803986a0
vtable_803986a0:
    .long 0
    .long 0
    .long loadState__Q23EGG12SoundHeapMgrFl
    .long getCurrentLevel__Q23EGG12SoundHeapMgrFv
    .long func_800AF980
.global vtable_803986bc
vtable_803986bc:
    .long 0
    .long 0
    .long func_800B0F10
    .long openArchive__Q23EGG9ArcPlayerFPCcPQ34nw4r3snd9SoundHeapQ33EGG9ArcPlayer12SARC_STORAGEP9ARCHandle
    .long 0x800afb08
    .long 0x800afb00
    .long 0x800afaf8
    .long 0x800afab0
    .long setupMemoryArchive__Q23EGG9ArcPlayerFPCvPQ34nw4r3snd9SoundHeapl
    .long 0x800afaa8
    .long 0x800afac8
    .long 0x800afad0
    .long 0x800afad8
    .long 0x800afac0
    .long startSound__Q23EGG9ArcPlayerFPQ34nw4r3snd11SoundHandleUl
    .long startSound__Q23EGG9ArcPlayerFPQ34nw4r3snd11SoundHandleUi
    .long startSound__Q23EGG9ArcPlayerFPQ34nw4r3snd11SoundHandlePCc
    .long prepareSound__Q23EGG9ArcPlayerFPQ34nw4r3snd11SoundHandleUl
    .long prepareSound__Q23EGG9ArcPlayerFPQ34nw4r3snd11SoundHandleUi
    .long prepareSound__Q23EGG9ArcPlayerFPQ34nw4r3snd11SoundHandlePCc
    .long holdSound__Q23EGG9ArcPlayerFPQ34nw4r3snd11SoundHandleUl
    .long holdSound__Q23EGG9ArcPlayerFPQ34nw4r3snd11SoundHandleUi
    .long holdSound__Q23EGG9ArcPlayerFPQ34nw4r3snd11SoundHandlePCc
    .long __dt__Q23EGG14SimpleAudioMgrFv
    .long func_800B0ECC
    .long func_800B0ED4
    .long func_800B0EDC
    .long func_800B0EE4
    .long func_800B0EEC
    .long func_800B0EF4
    .long func_800B0EFC
    .long func_800B0F04
    .long 0
.global __vt__Q23EGG9IAudioMgr
__vt__Q23EGG9IAudioMgr:
    .long 0
    .long 0
    .long initialize__Q23EGG9IAudioMgrFPQ33EGG9IAudioMgr3Arg
    .long 0
.global vtable_80398748
vtable_80398748:
    .long 0
    .long 0
    .long loadState__Q23EGG12SoundHeapMgrFl
    .long getCurrentLevel__Q23EGG12SoundHeapMgrFv
    .long func_800AF980
    .long 0

.section .text, "ax"
.global func_800B0A58
func_800B0A58:
/* 800B0A58 000AB958  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 800B0A5C 000AB95C  7C 08 02 A6 */	mflr r0
/* 800B0A60 000AB960  90 01 00 34 */	stw r0, 0x34(r1)
/* 800B0A64 000AB964  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 800B0A68 000AB968  7C BF 2B 78 */	mr r31, r5
/* 800B0A6C 000AB96C  38 A0 00 20 */	li r5, 0x20
/* 800B0A70 000AB970  93 C1 00 28 */	stw r30, 0x28(r1)
/* 800B0A74 000AB974  7C 7E 1B 78 */	mr r30, r3
/* 800B0A78 000AB978  38 61 00 08 */	addi r3, r1, 8
/* 800B0A7C 000AB97C  4B FF 29 A1 */	bl __ct__Q23EGG9AllocatorFPQ23EGG4Heapl
/* 800B0A80 000AB980  80 1E 00 20 */	lwz r0, 0x20(r30)
/* 800B0A84 000AB984  2C 00 00 00 */	cmpwi r0, 0
/* 800B0A88 000AB988  40 82 00 50 */	bne lbl_800B0AD8
/* 800B0A8C 000AB98C  81 81 00 18 */	lwz r12, 0x18(r1)
/* 800B0A90 000AB990  7F E4 FB 78 */	mr r4, r31
/* 800B0A94 000AB994  38 61 00 08 */	addi r3, r1, 8
/* 800B0A98 000AB998  81 8C 00 0C */	lwz r12, 0xc(r12)
/* 800B0A9C 000AB99C  7D 89 03 A6 */	mtctr r12
/* 800B0AA0 000AB9A0  4E 80 04 21 */	bctrl 
/* 800B0AA4 000AB9A4  7C 64 1B 78 */	mr r4, r3
/* 800B0AA8 000AB9A8  7F E5 FB 78 */	mr r5, r31
/* 800B0AAC 000AB9AC  38 7E 00 04 */	addi r3, r30, 4
/* 800B0AB0 000AB9B0  4B F9 51 B5 */	bl Create__Q34nw4r3snd9SoundHeapFPvUl
/* 800B0AB4 000AB9B4  80 1E 00 20 */	lwz r0, 0x20(r30)
/* 800B0AB8 000AB9B8  2C 00 00 00 */	cmpwi r0, 0
/* 800B0ABC 000AB9BC  40 82 00 1C */	bne lbl_800B0AD8
/* 800B0AC0 000AB9C0  3C 60 80 38 */	lis r3, lbl_8037B0C0@ha
/* 800B0AC4 000AB9C4  38 80 00 3B */	li r4, 0x3b
/* 800B0AC8 000AB9C8  38 63 B0 C0 */	addi r3, r3, lbl_8037B0C0@l
/* 800B0ACC 000AB9CC  38 A3 00 14 */	addi r5, r3, 0x14
/* 800B0AD0 000AB9D0  4C C6 31 82 */	crclr 6
/* 800B0AD4 000AB9D4  4B FF 14 35 */	bl system_halt
lbl_800B0AD8:
/* 800B0AD8 000AB9D8  38 61 00 08 */	addi r3, r1, 8
/* 800B0ADC 000AB9DC  38 80 FF FF */	li r4, -1
/* 800B0AE0 000AB9E0  4B FF 29 8D */	bl __dt__Q23EGG9AllocatorFv
/* 800B0AE4 000AB9E4  80 01 00 34 */	lwz r0, 0x34(r1)
/* 800B0AE8 000AB9E8  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 800B0AEC 000AB9EC  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 800B0AF0 000AB9F0  7C 08 03 A6 */	mtlr r0
/* 800B0AF4 000AB9F4  38 21 00 30 */	addi r1, r1, 0x30
/* 800B0AF8 000AB9F8  4E 80 00 20 */	blr 

.global createSoundHeap__Q23EGG12SoundHeapMgrFPQ23EGG9AllocatorUl
createSoundHeap__Q23EGG12SoundHeapMgrFPQ23EGG9AllocatorUl:
/* 800B0AFC 000AB9FC  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800B0B00 000ABA00  7C 08 02 A6 */	mflr r0
/* 800B0B04 000ABA04  90 01 00 14 */	stw r0, 0x14(r1)
/* 800B0B08 000ABA08  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800B0B0C 000ABA0C  7C BF 2B 78 */	mr r31, r5
/* 800B0B10 000ABA10  93 C1 00 08 */	stw r30, 8(r1)
/* 800B0B14 000ABA14  7C 7E 1B 78 */	mr r30, r3
/* 800B0B18 000ABA18  80 03 00 20 */	lwz r0, 0x20(r3)
/* 800B0B1C 000ABA1C  2C 00 00 00 */	cmpwi r0, 0
/* 800B0B20 000ABA20  40 82 00 50 */	bne lbl_800B0B70
/* 800B0B24 000ABA24  7C 83 23 78 */	mr r3, r4
/* 800B0B28 000ABA28  7F E4 FB 78 */	mr r4, r31
/* 800B0B2C 000ABA2C  81 83 00 10 */	lwz r12, 0x10(r3)
/* 800B0B30 000ABA30  81 8C 00 0C */	lwz r12, 0xc(r12)
/* 800B0B34 000ABA34  7D 89 03 A6 */	mtctr r12
/* 800B0B38 000ABA38  4E 80 04 21 */	bctrl 
/* 800B0B3C 000ABA3C  7C 64 1B 78 */	mr r4, r3
/* 800B0B40 000ABA40  7F E5 FB 78 */	mr r5, r31
/* 800B0B44 000ABA44  38 7E 00 04 */	addi r3, r30, 4
/* 800B0B48 000ABA48  4B F9 51 1D */	bl Create__Q34nw4r3snd9SoundHeapFPvUl
/* 800B0B4C 000ABA4C  80 1E 00 20 */	lwz r0, 0x20(r30)
/* 800B0B50 000ABA50  2C 00 00 00 */	cmpwi r0, 0
/* 800B0B54 000ABA54  40 82 00 1C */	bne lbl_800B0B70
/* 800B0B58 000ABA58  3C 60 80 38 */	lis r3, lbl_8037B0C0@ha
/* 800B0B5C 000ABA5C  38 80 00 3B */	li r4, 0x3b
/* 800B0B60 000ABA60  38 63 B0 C0 */	addi r3, r3, lbl_8037B0C0@l
/* 800B0B64 000ABA64  38 A3 00 14 */	addi r5, r3, 0x14
/* 800B0B68 000ABA68  4C C6 31 82 */	crclr 6
/* 800B0B6C 000ABA6C  4B FF 13 9D */	bl system_halt
lbl_800B0B70:
/* 800B0B70 000ABA70  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800B0B74 000ABA74  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 800B0B78 000ABA78  83 C1 00 08 */	lwz r30, 8(r1)
/* 800B0B7C 000ABA7C  7C 08 03 A6 */	mtlr r0
/* 800B0B80 000ABA80  38 21 00 10 */	addi r1, r1, 0x10
/* 800B0B84 000ABA84  4E 80 00 20 */	blr 

.global destroySoundHeap__Q23EGG12SoundHeapMgrFv
destroySoundHeap__Q23EGG12SoundHeapMgrFv:
/* 800B0B88 000ABA88  38 63 00 04 */	addi r3, r3, 4
/* 800B0B8C 000ABA8C  4B F9 50 E0 */	b Destroy__Q34nw4r3snd9SoundHeapFv
