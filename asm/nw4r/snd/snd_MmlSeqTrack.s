.include "macros.inc"

.section .data, "wa"  # 0x80393A80 - 0x803CAF00

.balign 0x8

.global __vt__Q44nw4r3snd6detail11MmlSeqTrack
__vt__Q44nw4r3snd6detail11MmlSeqTrack:
	.long 0
	.long 0
	.long __dt__Q44nw4r3snd6detail11MmlSeqTrackFv
	.long Parse__Q44nw4r3snd6detail11MmlSeqTrackFb

.section .text, "ax"  # 0x800076E0 - 0x80355080 

.global __ct__Q44nw4r3snd6detail11MmlSeqTrackFv
__ct__Q44nw4r3snd6detail11MmlSeqTrackFv:
/* 8003C7A4 000376A4  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8003C7A8 000376A8  7C 08 02 A6 */	mflr r0
/* 8003C7AC 000376AC  90 01 00 14 */	stw r0, 0x14(r1)
/* 8003C7B0 000376B0  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8003C7B4 000376B4  7C 7F 1B 78 */	mr r31, r3
/* 8003C7B8 000376B8  48 00 35 3D */	bl func_8003FCF4
/* 8003C7BC 000376BC  3C A0 80 39 */	lis r5, __vt__Q44nw4r3snd6detail11MmlSeqTrack@ha
/* 8003C7C0 000376C0  38 80 00 01 */	li r4, 1
/* 8003C7C4 000376C4  38 00 00 00 */	li r0, 0
/* 8003C7C8 000376C8  98 9F 00 C5 */	stb r4, 0xc5(r31)
/* 8003C7CC 000376CC  38 A5 60 48 */	addi r5, r5, __vt__Q44nw4r3snd6detail11MmlSeqTrack@l
/* 8003C7D0 000376D0  7F E3 FB 78 */	mr r3, r31
/* 8003C7D4 000376D4  90 BF 00 00 */	stw r5, 0(r31)
/* 8003C7D8 000376D8  98 1F 00 C6 */	stb r0, 0xc6(r31)
/* 8003C7DC 000376DC  98 9F 00 C4 */	stb r4, 0xc4(r31)
/* 8003C7E0 000376E0  98 1F 00 CA */	stb r0, 0xca(r31)
/* 8003C7E4 000376E4  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8003C7E8 000376E8  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8003C7EC 000376EC  7C 08 03 A6 */	mtlr r0
/* 8003C7F0 000376F0  38 21 00 10 */	addi r1, r1, 0x10
/* 8003C7F4 000376F4  4E 80 00 20 */	blr 

.global Parse__Q44nw4r3snd6detail11MmlSeqTrackFb
Parse__Q44nw4r3snd6detail11MmlSeqTrackFb:
/* 8003C7F8 000376F8  7C 60 1B 78 */	mr r0, r3
/* 8003C7FC 000376FC  80 63 00 C0 */	lwz r3, 0xc0(r3)
/* 8003C800 00037700  7C 85 23 78 */	mr r5, r4
/* 8003C804 00037704  7C 04 03 78 */	mr r4, r0
/* 8003C808 00037708  4B FF F0 B0 */	b Parse__Q44nw4r3snd6detail9MmlParserCFPQ44nw4r3snd6detail11MmlSeqTrackb

.global __dt__Q44nw4r3snd6detail11MmlSeqTrackFv
__dt__Q44nw4r3snd6detail11MmlSeqTrackFv:
/* 8003C80C 0003770C  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8003C810 00037710  7C 08 02 A6 */	mflr r0
/* 8003C814 00037714  2C 03 00 00 */	cmpwi r3, 0
/* 8003C818 00037718  90 01 00 14 */	stw r0, 0x14(r1)
/* 8003C81C 0003771C  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8003C820 00037720  7C 9F 23 78 */	mr r31, r4
/* 8003C824 00037724  93 C1 00 08 */	stw r30, 8(r1)
/* 8003C828 00037728  7C 7E 1B 78 */	mr r30, r3
/* 8003C82C 0003772C  41 82 00 1C */	beq lbl_8003C848
/* 8003C830 00037730  38 80 00 00 */	li r4, 0
/* 8003C834 00037734  48 00 35 21 */	bl func_8003FD54
/* 8003C838 00037738  2C 1F 00 00 */	cmpwi r31, 0
/* 8003C83C 0003773C  40 81 00 0C */	ble lbl_8003C848
/* 8003C840 00037740  7F C3 F3 78 */	mr r3, r30
/* 8003C844 00037744  48 06 6A 41 */	bl __dl__FPv
lbl_8003C848:
/* 8003C848 00037748  7F C3 F3 78 */	mr r3, r30
/* 8003C84C 0003774C  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8003C850 00037750  83 C1 00 08 */	lwz r30, 8(r1)
/* 8003C854 00037754  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8003C858 00037758  7C 08 03 A6 */	mtlr r0
/* 8003C85C 0003775C  38 21 00 10 */	addi r1, r1, 0x10
/* 8003C860 00037760  4E 80 00 20 */	blr 
