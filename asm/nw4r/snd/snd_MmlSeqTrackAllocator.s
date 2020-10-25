.include "macros.inc"

.section .text, "ax"  # 0x800076E0 - 0x80355080 

.global AllocTrack__Q44nw4r3snd6detail20MmlSeqTrackAllocatorFPQ44nw4r3snd6detail9SeqPlayer
AllocTrack__Q44nw4r3snd6detail20MmlSeqTrackAllocatorFPQ44nw4r3snd6detail9SeqPlayer:
/* 8003C864 00037764  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8003C868 00037768  7C 08 02 A6 */	mflr r0
/* 8003C86C 0003776C  90 01 00 14 */	stw r0, 0x14(r1)
/* 8003C870 00037770  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8003C874 00037774  7C 9F 23 78 */	mr r31, r4
/* 8003C878 00037778  93 C1 00 08 */	stw r30, 8(r1)
/* 8003C87C 0003777C  7C 7E 1B 78 */	mr r30, r3
/* 8003C880 00037780  38 63 00 08 */	addi r3, r3, 8
/* 8003C884 00037784  4B FF E9 21 */	bl AllocImpl__Q44nw4r3snd6detail8PoolImplFv
/* 8003C888 00037788  2C 03 00 00 */	cmpwi r3, 0
/* 8003C88C 0003778C  40 82 00 0C */	bne lbl_8003C898
/* 8003C890 00037790  38 60 00 00 */	li r3, 0
/* 8003C894 00037794  48 00 00 0C */	b lbl_8003C8A0
lbl_8003C898:
/* 8003C898 00037798  41 82 00 08 */	beq lbl_8003C8A0
/* 8003C89C 0003779C  4B FF FF 09 */	bl __ct__Q44nw4r3snd6detail11MmlSeqTrackFv
lbl_8003C8A0:
/* 8003C8A0 000377A0  2C 03 00 00 */	cmpwi r3, 0
/* 8003C8A4 000377A4  41 82 00 10 */	beq lbl_8003C8B4
/* 8003C8A8 000377A8  93 E3 00 B8 */	stw r31, 0xb8(r3)
/* 8003C8AC 000377AC  80 1E 00 04 */	lwz r0, 4(r30)
/* 8003C8B0 000377B0  90 03 00 C0 */	stw r0, 0xc0(r3)
lbl_8003C8B4:
/* 8003C8B4 000377B4  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8003C8B8 000377B8  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8003C8BC 000377BC  83 C1 00 08 */	lwz r30, 8(r1)
/* 8003C8C0 000377C0  7C 08 03 A6 */	mtlr r0
/* 8003C8C4 000377C4  38 21 00 10 */	addi r1, r1, 0x10
/* 8003C8C8 000377C8  4E 80 00 20 */	blr 

.global FreeTrack__Q44nw4r3snd6detail20MmlSeqTrackAllocatorFPQ44nw4r3snd6detail8SeqTrack
FreeTrack__Q44nw4r3snd6detail20MmlSeqTrackAllocatorFPQ44nw4r3snd6detail8SeqTrack:
/* 8003C8CC 000377CC  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8003C8D0 000377D0  7C 08 02 A6 */	mflr r0
/* 8003C8D4 000377D4  2C 04 00 00 */	cmpwi r4, 0
/* 8003C8D8 000377D8  90 01 00 14 */	stw r0, 0x14(r1)
/* 8003C8DC 000377DC  38 00 00 00 */	li r0, 0
/* 8003C8E0 000377E0  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8003C8E4 000377E4  7C 9F 23 78 */	mr r31, r4
/* 8003C8E8 000377E8  93 C1 00 08 */	stw r30, 8(r1)
/* 8003C8EC 000377EC  7C 7E 1B 78 */	mr r30, r3
/* 8003C8F0 000377F0  90 04 00 B8 */	stw r0, 0xb8(r4)
/* 8003C8F4 000377F4  41 82 00 28 */	beq lbl_8003C91C
/* 8003C8F8 000377F8  81 9F 00 00 */	lwz r12, 0(r31)
/* 8003C8FC 000377FC  7F E3 FB 78 */	mr r3, r31
/* 8003C900 00037800  38 80 FF FF */	li r4, -1
/* 8003C904 00037804  81 8C 00 08 */	lwz r12, 8(r12)
/* 8003C908 00037808  7D 89 03 A6 */	mtctr r12
/* 8003C90C 0003780C  4E 80 04 21 */	bctrl 
/* 8003C910 00037810  7F E4 FB 78 */	mr r4, r31
/* 8003C914 00037814  38 7E 00 08 */	addi r3, r30, 8
/* 8003C918 00037818  4B FF E8 E9 */	bl FreeImpl__Q44nw4r3snd6detail8PoolImplFPv
lbl_8003C91C:
/* 8003C91C 0003781C  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8003C920 00037820  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8003C924 00037824  83 C1 00 08 */	lwz r30, 8(r1)
/* 8003C928 00037828  7C 08 03 A6 */	mtlr r0
/* 8003C92C 0003782C  38 21 00 10 */	addi r1, r1, 0x10
/* 8003C930 00037830  4E 80 00 20 */	blr 

.global Create__Q44nw4r3snd6detail20MmlSeqTrackAllocatorFPvUl
Create__Q44nw4r3snd6detail20MmlSeqTrackAllocatorFPvUl:
/* 8003C934 00037834  38 C0 00 D8 */	li r6, 0xd8
/* 8003C938 00037838  38 63 00 08 */	addi r3, r3, 8
/* 8003C93C 0003783C  4B FF E6 54 */	b CreateImpl__Q44nw4r3snd6detail8PoolImplFPvUlUl

.global Destroy__Q44nw4r3snd6detail20MmlSeqTrackAllocatorFPvUl
Destroy__Q44nw4r3snd6detail20MmlSeqTrackAllocatorFPvUl:
/* 8003C940 00037840  38 63 00 08 */	addi r3, r3, 8
/* 8003C944 00037844  4B FF E7 90 */	b DestroyImpl__Q44nw4r3snd6detail8PoolImplFPvUl

.global GetAllocatableTrackCount__Q44nw4r3snd6detail20MmlSeqTrackAllocatorCFv
GetAllocatableTrackCount__Q44nw4r3snd6detail20MmlSeqTrackAllocatorCFv:
/* 8003C948 00037848  38 63 00 08 */	addi r3, r3, 8
/* 8003C94C 0003784C  4B FF E8 08 */	b CountImpl__Q44nw4r3snd6detail8PoolImplCFv

.global __dt__Q44nw4r3snd6detail20MmlSeqTrackAllocatorFv
__dt__Q44nw4r3snd6detail20MmlSeqTrackAllocatorFv:
/* 8003C950 00037850  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8003C954 00037854  7C 08 02 A6 */	mflr r0
/* 8003C958 00037858  2C 03 00 00 */	cmpwi r3, 0
/* 8003C95C 0003785C  90 01 00 14 */	stw r0, 0x14(r1)
/* 8003C960 00037860  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8003C964 00037864  7C 7F 1B 78 */	mr r31, r3
/* 8003C968 00037868  41 82 00 10 */	beq lbl_8003C978
/* 8003C96C 0003786C  2C 04 00 00 */	cmpwi r4, 0
/* 8003C970 00037870  40 81 00 08 */	ble lbl_8003C978
/* 8003C974 00037874  48 06 69 11 */	bl __dl__FPv
lbl_8003C978:
/* 8003C978 00037878  7F E3 FB 78 */	mr r3, r31
/* 8003C97C 0003787C  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8003C980 00037880  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8003C984 00037884  7C 08 03 A6 */	mtlr r0
/* 8003C988 00037888  38 21 00 10 */	addi r1, r1, 0x10
/* 8003C98C 0003788C  4E 80 00 20 */	blr 
