.include "macros.inc"

# .text1 = .text
.section .sbss, "wa" # 0x804BE9E0 - 0x804BFA20

.global typeInfo__Q34nw4r2ut13DvdFileStream
typeInfo__Q34nw4r2ut13DvdFileStream:
	.skip 0x8

.section .data, "wa"  # 0x80393A80 - 0x803CAF00

.global __vt__Q34nw4r2ut13DvdFileStream
__vt__Q34nw4r2ut13DvdFileStream:
.fill 0x8
.long GetRuntimeTypeInfo__Q34nw4r2ut13DvdFileStreamCFv
.long __dt__Q34nw4r2ut13DvdFileStreamFv
.long Close__Q34nw4r2ut13DvdFileStreamFv
.long Read__Q34nw4r2ut13DvdFileStreamFPvUl
.long ReadAsync__Q34nw4r2ut13DvdFileStreamFPvUlPFlPQ34nw4r2ut8IOStreamPv_vPv
.long Write__Q34nw4r2ut8IOStreamFPCvUl
.long WriteAsync__Q34nw4r2ut8IOStreamFPCvUlPFlPQ34nw4r2ut8IOStreamPv_vPv
.long IsBusy__Q34nw4r2ut13DvdFileStreamCFv
.long CanAsync__Q34nw4r2ut13DvdFileStreamCFv
.long CanRead__Q34nw4r2ut13DvdFileStreamCFv
.long CanWrite__Q34nw4r2ut13DvdFileStreamCFv
.long GetOffsetAlign__Q34nw4r2ut13DvdFileStreamCFv
.long GetSizeAlign__Q34nw4r2ut13DvdFileStreamCFv
.long GetBufferAlign__Q34nw4r2ut13DvdFileStreamCFv
.long GetSize__Q34nw4r2ut13DvdFileStreamCFv
.long Seek__Q34nw4r2ut13DvdFileStreamFlUl
.long Cancel__Q34nw4r2ut13DvdFileStreamFv
.long CancelAsync__Q34nw4r2ut13DvdFileStreamFPFlPQ34nw4r2ut8IOStreamPv_vPv
.long CanSeek__Q34nw4r2ut13DvdFileStreamCFv
.long CanCancel__Q34nw4r2ut13DvdFileStreamCFv
.long Tell__Q34nw4r2ut13DvdFileStreamCFv
.long Peek__Q34nw4r2ut13DvdFileStreamFPvUl
.long PeekAsync__Q34nw4r2ut13DvdFileStreamFPvUlPFlPQ34nw4r2ut8IOStreamPv_vPv
.long 0

.section .text, "ax"  # 0x800076E0 - 0x80355080

.global DvdAsyncCallback___Q34nw4r2ut13DvdFileStreamFlP11DVDFileInfo
DvdAsyncCallback___Q34nw4r2ut13DvdFileStreamFlP11DVDFileInfo:
/* 800084E8 000033E8  80 84 00 3C */	lwz r4, 0x3c(r4)
/* 800084EC 000033EC  38 00 00 00 */	li r0, 0
/* 800084F0 000033F0  98 04 00 6C */	stb r0, 0x6c(r4)
/* 800084F4 000033F4  90 64 00 08 */	stw r3, 8(r4)
/* 800084F8 000033F8  81 84 00 0C */	lwz r12, 0xc(r4)
/* 800084FC 000033FC  2C 0C 00 00 */	cmpwi r12, 0
/* 80008500 00003400  4D 82 00 20 */	beqlr 
/* 80008504 00003404  80 A4 00 10 */	lwz r5, 0x10(r4)
/* 80008508 00003408  7D 89 03 A6 */	mtctr r12
/* 8000850C 0000340C  4E 80 04 20 */	bctr 
/* 80008510 00003410  4E 80 00 20 */	blr 

.global DvdCBAsyncCallback___Q34nw4r2ut13DvdFileStreamFlP15DVDCommandBlock
DvdCBAsyncCallback___Q34nw4r2ut13DvdFileStreamFlP15DVDCommandBlock:
/* 80008514 00003414  80 84 00 3C */	lwz r4, 0x3c(r4)
/* 80008518 00003418  38 00 00 00 */	li r0, 0
/* 8000851C 0000341C  98 04 00 24 */	stb r0, 0x24(r4)
/* 80008520 00003420  81 84 00 1C */	lwz r12, 0x1c(r4)
/* 80008524 00003424  2C 0C 00 00 */	cmpwi r12, 0
/* 80008528 00003428  4D 82 00 20 */	beqlr 
/* 8000852C 0000342C  80 A4 00 20 */	lwz r5, 0x20(r4)
/* 80008530 00003430  7D 89 03 A6 */	mtctr r12
/* 80008534 00003434  4E 80 04 20 */	bctr 
/* 80008538 00003438  4E 80 00 20 */	blr 

.global __ct__Q34nw4r2ut13DvdFileStreamFl
__ct__Q34nw4r2ut13DvdFileStreamFl:
/* 8000853C 0000343C  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80008540 00003440  7C 08 02 A6 */	mflr r0
/* 80008544 00003444  3C A0 80 39 */	lis r5, __vt__Q34nw4r2ut13DvdFileStream@ha
/* 80008548 00003448  38 C0 00 00 */	li r6, 0
/* 8000854C 0000344C  90 01 00 14 */	stw r0, 0x14(r1)
/* 80008550 00003450  38 A5 3A A8 */	addi r5, r5, __vt__Q34nw4r2ut13DvdFileStream@l
/* 80008554 00003454  38 00 00 02 */	li r0, 2
/* 80008558 00003458  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8000855C 0000345C  7C 7F 1B 78 */	mr r31, r3
/* 80008560 00003460  98 C3 00 6C */	stb r6, 0x6c(r3)
/* 80008564 00003464  90 A3 00 00 */	stw r5, 0(r3)
/* 80008568 00003468  90 C3 00 14 */	stw r6, 0x14(r3)
/* 8000856C 0000346C  90 C3 00 18 */	stw r6, 0x18(r3)
/* 80008570 00003470  98 C3 00 6D */	stb r6, 0x6d(r3)
/* 80008574 00003474  98 C3 00 6E */	stb r6, 0x6e(r3)
/* 80008578 00003478  98 C3 00 04 */	stb r6, 4(r3)
/* 8000857C 0000347C  90 03 00 68 */	stw r0, 0x68(r3)
/* 80008580 00003480  90 C3 00 0C */	stw r6, 0xc(r3)
/* 80008584 00003484  90 C3 00 10 */	stw r6, 0x10(r3)
/* 80008588 00003488  90 C3 00 08 */	stw r6, 8(r3)
/* 8000858C 0000348C  90 C3 00 1C */	stw r6, 0x1c(r3)
/* 80008590 00003490  98 C3 00 24 */	stb r6, 0x24(r3)
/* 80008594 00003494  90 C3 00 20 */	stw r6, 0x20(r3)
/* 80008598 00003498  90 63 00 64 */	stw r3, 0x64(r3)
/* 8000859C 0000349C  48 00 00 08 */	b lbl_800085A4
/* 800085A0 000034A0  4E 80 04 21 */	bctrl 
lbl_800085A4:
/* 800085A4 000034A4  7C 83 23 78 */	mr r3, r4
/* 800085A8 000034A8  38 9F 00 28 */	addi r4, r31, 0x28
/* 800085AC 000034AC  48 13 13 AD */	bl DVDFastOpen
/* 800085B0 000034B0  2C 03 00 00 */	cmpwi r3, 0
/* 800085B4 000034B4  41 82 00 2C */	beq lbl_800085E0
/* 800085B8 000034B8  80 1F 00 5C */	lwz r0, 0x5c(r31)
/* 800085BC 000034BC  38 7F 00 14 */	addi r3, r31, 0x14
/* 800085C0 000034C0  38 80 00 00 */	li r4, 0
/* 800085C4 000034C4  38 A0 00 00 */	li r5, 0
/* 800085C8 000034C8  90 1F 00 14 */	stw r0, 0x14(r31)
/* 800085CC 000034CC  4B FF FE 71 */	bl Seek__Q44nw4r2ut10FileStream12FilePositionFlUl
/* 800085D0 000034D0  38 00 00 01 */	li r0, 1
/* 800085D4 000034D4  98 1F 00 6D */	stb r0, 0x6d(r31)
/* 800085D8 000034D8  98 1F 00 6E */	stb r0, 0x6e(r31)
/* 800085DC 000034DC  98 1F 00 04 */	stb r0, 4(r31)
lbl_800085E0:
/* 800085E0 000034E0  7F E3 FB 78 */	mr r3, r31
/* 800085E4 000034E4  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 800085E8 000034E8  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800085EC 000034EC  7C 08 03 A6 */	mtlr r0
/* 800085F0 000034F0  38 21 00 10 */	addi r1, r1, 0x10
/* 800085F4 000034F4  4E 80 00 20 */	blr 

.global __ct__Q34nw4r2ut13DvdFileStreamFPC11DVDFileInfob
__ct__Q34nw4r2ut13DvdFileStreamFPC11DVDFileInfob:
/* 800085F8 000034F8  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 800085FC 000034FC  7C 08 02 A6 */	mflr r0
/* 80008600 00003500  90 01 00 34 */	stw r0, 0x34(r1)
/* 80008604 00003504  39 61 00 30 */	addi r11, r1, 0x30
/* 80008608 00003508  48 0A 97 29 */	bl func_800B1D30
/* 8000860C 0000350C  3C C0 80 39 */	lis r6, __vt__Q34nw4r2ut13DvdFileStream@ha
/* 80008610 00003510  38 E0 00 00 */	li r7, 0
/* 80008614 00003514  38 C6 3A A8 */	addi r6, r6, __vt__Q34nw4r2ut13DvdFileStream@l
/* 80008618 00003518  38 00 00 02 */	li r0, 2
/* 8000861C 0000351C  98 E3 00 6C */	stb r7, 0x6c(r3)
/* 80008620 00003520  7C 7E 1B 78 */	mr r30, r3
/* 80008624 00003524  7C 96 23 78 */	mr r22, r4
/* 80008628 00003528  7C BF 2B 78 */	mr r31, r5
/* 8000862C 0000352C  90 C3 00 00 */	stw r6, 0(r3)
/* 80008630 00003530  90 E3 00 14 */	stw r7, 0x14(r3)
/* 80008634 00003534  90 E3 00 18 */	stw r7, 0x18(r3)
/* 80008638 00003538  98 E3 00 6D */	stb r7, 0x6d(r3)
/* 8000863C 0000353C  98 E3 00 6E */	stb r7, 0x6e(r3)
/* 80008640 00003540  98 E3 00 04 */	stb r7, 4(r3)
/* 80008644 00003544  90 03 00 68 */	stw r0, 0x68(r3)
/* 80008648 00003548  90 E3 00 0C */	stw r7, 0xc(r3)
/* 8000864C 0000354C  90 E3 00 10 */	stw r7, 0x10(r3)
/* 80008650 00003550  90 E3 00 08 */	stw r7, 8(r3)
/* 80008654 00003554  90 E3 00 1C */	stw r7, 0x1c(r3)
/* 80008658 00003558  98 E3 00 24 */	stb r7, 0x24(r3)
/* 8000865C 0000355C  90 E3 00 20 */	stw r7, 0x20(r3)
/* 80008660 00003560  90 63 00 64 */	stw r3, 0x64(r3)
/* 80008664 00003564  48 00 00 08 */	b lbl_8000866C
/* 80008668 00003568  4E 80 04 21 */	bctrl 
lbl_8000866C:
/* 8000866C 0000356C  80 D6 00 34 */	lwz r6, 0x34(r22)
/* 80008670 00003570  38 7E 00 14 */	addi r3, r30, 0x14
/* 80008674 00003574  82 F6 00 00 */	lwz r23, 0(r22)
/* 80008678 00003578  38 80 00 00 */	li r4, 0
/* 8000867C 0000357C  83 16 00 04 */	lwz r24, 4(r22)
/* 80008680 00003580  38 A0 00 00 */	li r5, 0
/* 80008684 00003584  83 36 00 08 */	lwz r25, 8(r22)
/* 80008688 00003588  83 56 00 0C */	lwz r26, 0xc(r22)
/* 8000868C 0000358C  83 76 00 10 */	lwz r27, 0x10(r22)
/* 80008690 00003590  83 96 00 14 */	lwz r28, 0x14(r22)
/* 80008694 00003594  83 B6 00 18 */	lwz r29, 0x18(r22)
/* 80008698 00003598  81 96 00 1C */	lwz r12, 0x1c(r22)
/* 8000869C 0000359C  81 76 00 20 */	lwz r11, 0x20(r22)
/* 800086A0 000035A0  81 56 00 24 */	lwz r10, 0x24(r22)
/* 800086A4 000035A4  81 36 00 28 */	lwz r9, 0x28(r22)
/* 800086A8 000035A8  81 16 00 2C */	lwz r8, 0x2c(r22)
/* 800086AC 000035AC  80 F6 00 30 */	lwz r7, 0x30(r22)
/* 800086B0 000035B0  80 16 00 38 */	lwz r0, 0x38(r22)
/* 800086B4 000035B4  92 FE 00 28 */	stw r23, 0x28(r30)
/* 800086B8 000035B8  93 1E 00 2C */	stw r24, 0x2c(r30)
/* 800086BC 000035BC  93 3E 00 30 */	stw r25, 0x30(r30)
/* 800086C0 000035C0  93 5E 00 34 */	stw r26, 0x34(r30)
/* 800086C4 000035C4  93 7E 00 38 */	stw r27, 0x38(r30)
/* 800086C8 000035C8  93 9E 00 3C */	stw r28, 0x3c(r30)
/* 800086CC 000035CC  93 BE 00 40 */	stw r29, 0x40(r30)
/* 800086D0 000035D0  91 9E 00 44 */	stw r12, 0x44(r30)
/* 800086D4 000035D4  91 7E 00 48 */	stw r11, 0x48(r30)
/* 800086D8 000035D8  91 5E 00 4C */	stw r10, 0x4c(r30)
/* 800086DC 000035DC  91 3E 00 50 */	stw r9, 0x50(r30)
/* 800086E0 000035E0  91 1E 00 54 */	stw r8, 0x54(r30)
/* 800086E4 000035E4  90 FE 00 58 */	stw r7, 0x58(r30)
/* 800086E8 000035E8  90 DE 00 5C */	stw r6, 0x5c(r30)
/* 800086EC 000035EC  90 1E 00 60 */	stw r0, 0x60(r30)
/* 800086F0 000035F0  90 DE 00 14 */	stw r6, 0x14(r30)
/* 800086F4 000035F4  4B FF FD 49 */	bl Seek__Q44nw4r2ut10FileStream12FilePositionFlUl
/* 800086F8 000035F8  38 60 00 00 */	li r3, 0
/* 800086FC 000035FC  38 00 00 01 */	li r0, 1
/* 80008700 00003600  98 7E 00 6D */	stb r3, 0x6d(r30)
/* 80008704 00003604  39 61 00 30 */	addi r11, r1, 0x30
/* 80008708 00003608  7F C3 F3 78 */	mr r3, r30
/* 8000870C 0000360C  9B FE 00 6E */	stb r31, 0x6e(r30)
/* 80008710 00003610  98 1E 00 04 */	stb r0, 4(r30)
/* 80008714 00003614  48 0A 96 69 */	bl func_800B1D7C
/* 80008718 00003618  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8000871C 0000361C  7C 08 03 A6 */	mtlr r0
/* 80008720 00003620  38 21 00 30 */	addi r1, r1, 0x30
/* 80008724 00003624  4E 80 00 20 */	blr 

.global __dt__Q34nw4r2ut13DvdFileStreamFv
__dt__Q34nw4r2ut13DvdFileStreamFv:
/* 80008728 00003628  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8000872C 0000362C  7C 08 02 A6 */	mflr r0
/* 80008730 00003630  2C 03 00 00 */	cmpwi r3, 0
/* 80008734 00003634  90 01 00 14 */	stw r0, 0x14(r1)
/* 80008738 00003638  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8000873C 0000363C  7C 9F 23 78 */	mr r31, r4
/* 80008740 00003640  93 C1 00 08 */	stw r30, 8(r1)
/* 80008744 00003644  7C 7E 1B 78 */	mr r30, r3
/* 80008748 00003648  41 82 00 3C */	beq lbl_80008784
/* 8000874C 0000364C  88 03 00 6D */	lbz r0, 0x6d(r3)
/* 80008750 00003650  3C 80 80 39 */	lis r4, __vt__Q34nw4r2ut13DvdFileStream@ha
/* 80008754 00003654  38 84 3A A8 */	addi r4, r4, __vt__Q34nw4r2ut13DvdFileStream@l
/* 80008758 00003658  2C 00 00 00 */	cmpwi r0, 0
/* 8000875C 0000365C  90 83 00 00 */	stw r4, 0(r3)
/* 80008760 00003660  41 82 00 14 */	beq lbl_80008774
/* 80008764 00003664  81 83 00 00 */	lwz r12, 0(r3)
/* 80008768 00003668  81 8C 00 10 */	lwz r12, 0x10(r12)
/* 8000876C 0000366C  7D 89 03 A6 */	mtctr r12
/* 80008770 00003670  4E 80 04 21 */	bctrl 
lbl_80008774:
/* 80008774 00003674  2C 1F 00 00 */	cmpwi r31, 0
/* 80008778 00003678  40 81 00 0C */	ble lbl_80008784
/* 8000877C 0000367C  7F C3 F3 78 */	mr r3, r30
/* 80008780 00003680  48 09 AB 05 */	bl __dl__FPv
lbl_80008784:
/* 80008784 00003684  7F C3 F3 78 */	mr r3, r30
/* 80008788 00003688  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8000878C 0000368C  83 C1 00 08 */	lwz r30, 8(r1)
/* 80008790 00003690  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80008794 00003694  7C 08 03 A6 */	mtlr r0
/* 80008798 00003698  38 21 00 10 */	addi r1, r1, 0x10
/* 8000879C 0000369C  4E 80 00 20 */	blr 

.global Close__Q34nw4r2ut13DvdFileStreamFv
Close__Q34nw4r2ut13DvdFileStreamFv:
/* 800087A0 000036A0  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800087A4 000036A4  7C 08 02 A6 */	mflr r0
/* 800087A8 000036A8  90 01 00 14 */	stw r0, 0x14(r1)
/* 800087AC 000036AC  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800087B0 000036B0  7C 7F 1B 78 */	mr r31, r3
/* 800087B4 000036B4  88 03 00 6E */	lbz r0, 0x6e(r3)
/* 800087B8 000036B8  2C 00 00 00 */	cmpwi r0, 0
/* 800087BC 000036BC  41 82 00 20 */	beq lbl_800087DC
/* 800087C0 000036C0  88 03 00 04 */	lbz r0, 4(r3)
/* 800087C4 000036C4  2C 00 00 00 */	cmpwi r0, 0
/* 800087C8 000036C8  41 82 00 14 */	beq lbl_800087DC
/* 800087CC 000036CC  38 63 00 28 */	addi r3, r3, 0x28
/* 800087D0 000036D0  48 13 14 9D */	bl DVDClose
/* 800087D4 000036D4  38 00 00 00 */	li r0, 0
/* 800087D8 000036D8  98 1F 00 04 */	stb r0, 4(r31)
lbl_800087DC:
/* 800087DC 000036DC  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800087E0 000036E0  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 800087E4 000036E4  7C 08 03 A6 */	mtlr r0
/* 800087E8 000036E8  38 21 00 10 */	addi r1, r1, 0x10
/* 800087EC 000036EC  4E 80 00 20 */	blr 

.global Read__Q34nw4r2ut13DvdFileStreamFPvUl
Read__Q34nw4r2ut13DvdFileStreamFPvUl:
/* 800087F0 000036F0  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800087F4 000036F4  7C 08 02 A6 */	mflr r0
/* 800087F8 000036F8  90 01 00 14 */	stw r0, 0x14(r1)
/* 800087FC 000036FC  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80008800 00003700  93 C1 00 08 */	stw r30, 8(r1)
/* 80008804 00003704  7C 7E 1B 78 */	mr r30, r3
/* 80008808 00003708  80 C3 00 18 */	lwz r6, 0x18(r3)
/* 8000880C 0000370C  81 03 00 14 */	lwz r8, 0x14(r3)
/* 80008810 00003710  7C E6 2A 14 */	add r7, r6, r5
/* 80008814 00003714  38 E7 00 1F */	addi r7, r7, 0x1f
/* 80008818 00003718  38 08 00 1F */	addi r0, r8, 0x1f
/* 8000881C 0000371C  54 E7 00 34 */	rlwinm r7, r7, 0, 0, 0x1a
/* 80008820 00003720  54 00 00 34 */	rlwinm r0, r0, 0, 0, 0x1a
/* 80008824 00003724  7C 07 00 40 */	cmplw r7, r0
/* 80008828 00003728  40 81 00 10 */	ble lbl_80008838
/* 8000882C 0000372C  7C A6 40 50 */	subf r5, r6, r8
/* 80008830 00003730  38 05 00 1F */	addi r0, r5, 0x1f
/* 80008834 00003734  54 05 00 34 */	rlwinm r5, r0, 0, 0, 0x1a
lbl_80008838:
/* 80008838 00003738  80 E3 00 68 */	lwz r7, 0x68(r3)
/* 8000883C 0000373C  38 63 00 28 */	addi r3, r3, 0x28
/* 80008840 00003740  48 13 16 F9 */	bl DVDReadPrio
/* 80008844 00003744  2C 03 00 00 */	cmpwi r3, 0
/* 80008848 00003748  7C 7F 1B 78 */	mr r31, r3
/* 8000884C 0000374C  40 81 00 10 */	ble lbl_8000885C
/* 80008850 00003750  7F E4 FB 78 */	mr r4, r31
/* 80008854 00003754  38 7E 00 14 */	addi r3, r30, 0x14
/* 80008858 00003758  4B FF FB 31 */	bl Skip__Q44nw4r2ut10FileStream12FilePositionFl
lbl_8000885C:
/* 8000885C 0000375C  7F E3 FB 78 */	mr r3, r31
/* 80008860 00003760  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80008864 00003764  83 C1 00 08 */	lwz r30, 8(r1)
/* 80008868 00003768  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8000886C 0000376C  7C 08 03 A6 */	mtlr r0
/* 80008870 00003770  38 21 00 10 */	addi r1, r1, 0x10
/* 80008874 00003774  4E 80 00 20 */	blr 

.global ReadAsync__Q34nw4r2ut13DvdFileStreamFPvUlPFlPQ34nw4r2ut8IOStreamPv_vPv
ReadAsync__Q34nw4r2ut13DvdFileStreamFPvUlPFlPQ34nw4r2ut8IOStreamPv_vPv:
/* 80008878 00003778  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8000887C 0000377C  7C 08 02 A6 */	mflr r0
/* 80008880 00003780  90 01 00 24 */	stw r0, 0x24(r1)
/* 80008884 00003784  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80008888 00003788  7C 7F 1B 78 */	mr r31, r3
/* 8000888C 0000378C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80008890 00003790  7C BE 2B 78 */	mr r30, r5
/* 80008894 00003794  93 A1 00 14 */	stw r29, 0x14(r1)
/* 80008898 00003798  81 03 00 18 */	lwz r8, 0x18(r3)
/* 8000889C 0000379C  81 23 00 14 */	lwz r9, 0x14(r3)
/* 800088A0 000037A0  7C A8 2A 14 */	add r5, r8, r5
/* 800088A4 000037A4  38 A5 00 1F */	addi r5, r5, 0x1f
/* 800088A8 000037A8  38 09 00 1F */	addi r0, r9, 0x1f
/* 800088AC 000037AC  54 A5 00 34 */	rlwinm r5, r5, 0, 0, 0x1a
/* 800088B0 000037B0  54 00 00 34 */	rlwinm r0, r0, 0, 0, 0x1a
/* 800088B4 000037B4  7C 05 00 40 */	cmplw r5, r0
/* 800088B8 000037B8  40 81 00 10 */	ble lbl_800088C8
/* 800088BC 000037BC  7C A8 48 50 */	subf r5, r8, r9
/* 800088C0 000037C0  38 05 00 1F */	addi r0, r5, 0x1f
/* 800088C4 000037C4  54 1E 00 34 */	rlwinm r30, r0, 0, 0, 0x1a
lbl_800088C8:
/* 800088C8 000037C8  81 63 00 18 */	lwz r11, 0x18(r3)
/* 800088CC 000037CC  39 20 00 01 */	li r9, 1
/* 800088D0 000037D0  81 43 00 14 */	lwz r10, 0x14(r3)
/* 800088D4 000037D4  7F C5 F3 78 */	mr r5, r30
/* 800088D8 000037D8  7D 0B F2 14 */	add r8, r11, r30
/* 800088DC 000037DC  90 C3 00 0C */	stw r6, 0xc(r3)
/* 800088E0 000037E0  38 C8 00 1F */	addi r6, r8, 0x1f
/* 800088E4 000037E4  38 0A 00 1F */	addi r0, r10, 0x1f
/* 800088E8 000037E8  54 C6 00 34 */	rlwinm r6, r6, 0, 0, 0x1a
/* 800088EC 000037EC  90 E3 00 10 */	stw r7, 0x10(r3)
/* 800088F0 000037F0  54 00 00 34 */	rlwinm r0, r0, 0, 0, 0x1a
/* 800088F4 000037F4  7C 06 00 40 */	cmplw r6, r0
/* 800088F8 000037F8  99 23 00 6C */	stb r9, 0x6c(r3)
/* 800088FC 000037FC  40 81 00 10 */	ble lbl_8000890C
/* 80008900 00003800  7C AB 50 50 */	subf r5, r11, r10
/* 80008904 00003804  38 05 00 1F */	addi r0, r5, 0x1f
/* 80008908 00003808  54 05 00 34 */	rlwinm r5, r0, 0, 0, 0x1a
lbl_8000890C:
/* 8000890C 0000380C  81 03 00 68 */	lwz r8, 0x68(r3)
/* 80008910 00003810  3C E0 80 01 */	lis r7, DvdAsyncCallback___Q34nw4r2ut13DvdFileStreamFlP11DVDFileInfo@ha
/* 80008914 00003814  7D 66 5B 78 */	mr r6, r11
/* 80008918 00003818  38 63 00 28 */	addi r3, r3, 0x28
/* 8000891C 0000381C  38 E7 84 E8 */	addi r7, r7, DvdAsyncCallback___Q34nw4r2ut13DvdFileStreamFlP11DVDFileInfo@l
/* 80008920 00003820  48 13 15 31 */	bl DVDReadAsyncPrio
/* 80008924 00003824  7C 03 00 D0 */	neg r0, r3
/* 80008928 00003828  7C 00 1B 78 */	or r0, r0, r3
/* 8000892C 0000382C  54 1D 0F FF */	rlwinm. r29, r0, 1, 0x1f, 0x1f
/* 80008930 00003830  41 82 00 14 */	beq lbl_80008944
/* 80008934 00003834  7F C4 F3 78 */	mr r4, r30
/* 80008938 00003838  38 7F 00 14 */	addi r3, r31, 0x14
/* 8000893C 0000383C  4B FF FA 4D */	bl Skip__Q44nw4r2ut10FileStream12FilePositionFl
/* 80008940 00003840  48 00 00 0C */	b lbl_8000894C
lbl_80008944:
/* 80008944 00003844  38 00 00 00 */	li r0, 0
/* 80008948 00003848  98 1F 00 6C */	stb r0, 0x6c(r31)
lbl_8000894C:
/* 8000894C 0000384C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80008950 00003850  7F A3 EB 78 */	mr r3, r29
/* 80008954 00003854  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80008958 00003858  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8000895C 0000385C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80008960 00003860  7C 08 03 A6 */	mtlr r0
/* 80008964 00003864  38 21 00 20 */	addi r1, r1, 0x20
/* 80008968 00003868  4E 80 00 20 */	blr 

.global Peek__Q34nw4r2ut13DvdFileStreamFPvUl
Peek__Q34nw4r2ut13DvdFileStreamFPvUl:
/* 8000896C 0000386C  80 C3 00 18 */	lwz r6, 0x18(r3)
/* 80008970 00003870  81 03 00 14 */	lwz r8, 0x14(r3)
/* 80008974 00003874  7C E6 2A 14 */	add r7, r6, r5
/* 80008978 00003878  38 E7 00 1F */	addi r7, r7, 0x1f
/* 8000897C 0000387C  38 08 00 1F */	addi r0, r8, 0x1f
/* 80008980 00003880  54 E7 00 34 */	rlwinm r7, r7, 0, 0, 0x1a
/* 80008984 00003884  54 00 00 34 */	rlwinm r0, r0, 0, 0, 0x1a
/* 80008988 00003888  7C 07 00 40 */	cmplw r7, r0
/* 8000898C 0000388C  40 81 00 10 */	ble lbl_8000899C
/* 80008990 00003890  7C A6 40 50 */	subf r5, r6, r8
/* 80008994 00003894  38 05 00 1F */	addi r0, r5, 0x1f
/* 80008998 00003898  54 05 00 34 */	rlwinm r5, r0, 0, 0, 0x1a
lbl_8000899C:
/* 8000899C 0000389C  80 E3 00 68 */	lwz r7, 0x68(r3)
/* 800089A0 000038A0  38 63 00 28 */	addi r3, r3, 0x28
/* 800089A4 000038A4  48 13 15 94 */	b DVDReadPrio

.global PeekAsync__Q34nw4r2ut13DvdFileStreamFPvUlPFlPQ34nw4r2ut8IOStreamPv_vPv
PeekAsync__Q34nw4r2ut13DvdFileStreamFPvUlPFlPQ34nw4r2ut8IOStreamPv_vPv:
/* 800089A8 000038A8  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800089AC 000038AC  7C 08 02 A6 */	mflr r0
/* 800089B0 000038B0  39 20 00 01 */	li r9, 1
/* 800089B4 000038B4  90 01 00 14 */	stw r0, 0x14(r1)
/* 800089B8 000038B8  81 63 00 18 */	lwz r11, 0x18(r3)
/* 800089BC 000038BC  81 43 00 14 */	lwz r10, 0x14(r3)
/* 800089C0 000038C0  7D 0B 2A 14 */	add r8, r11, r5
/* 800089C4 000038C4  90 C3 00 0C */	stw r6, 0xc(r3)
/* 800089C8 000038C8  38 C8 00 1F */	addi r6, r8, 0x1f
/* 800089CC 000038CC  38 0A 00 1F */	addi r0, r10, 0x1f
/* 800089D0 000038D0  54 C6 00 34 */	rlwinm r6, r6, 0, 0, 0x1a
/* 800089D4 000038D4  90 E3 00 10 */	stw r7, 0x10(r3)
/* 800089D8 000038D8  54 00 00 34 */	rlwinm r0, r0, 0, 0, 0x1a
/* 800089DC 000038DC  7C 06 00 40 */	cmplw r6, r0
/* 800089E0 000038E0  99 23 00 6C */	stb r9, 0x6c(r3)
/* 800089E4 000038E4  40 81 00 10 */	ble lbl_800089F4
/* 800089E8 000038E8  7C AB 50 50 */	subf r5, r11, r10
/* 800089EC 000038EC  38 05 00 1F */	addi r0, r5, 0x1f
/* 800089F0 000038F0  54 05 00 34 */	rlwinm r5, r0, 0, 0, 0x1a
lbl_800089F4:
/* 800089F4 000038F4  81 03 00 68 */	lwz r8, 0x68(r3)
/* 800089F8 000038F8  3C E0 80 01 */	lis r7, DvdAsyncCallback___Q34nw4r2ut13DvdFileStreamFlP11DVDFileInfo@ha
/* 800089FC 000038FC  7D 66 5B 78 */	mr r6, r11
/* 80008A00 00003900  38 63 00 28 */	addi r3, r3, 0x28
/* 80008A04 00003904  38 E7 84 E8 */	addi r7, r7, DvdAsyncCallback___Q34nw4r2ut13DvdFileStreamFlP11DVDFileInfo@l
/* 80008A08 00003908  48 13 14 49 */	bl DVDReadAsyncPrio
/* 80008A0C 0000390C  7C 03 00 D0 */	neg r0, r3
/* 80008A10 00003910  7C 00 1B 78 */	or r0, r0, r3
/* 80008A14 00003914  54 03 0F FE */	srwi r3, r0, 0x1f
/* 80008A18 00003918  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80008A1C 0000391C  7C 08 03 A6 */	mtlr r0
/* 80008A20 00003920  38 21 00 10 */	addi r1, r1, 0x10
/* 80008A24 00003924  4E 80 00 20 */	blr 

.global Seek__Q34nw4r2ut13DvdFileStreamFlUl
Seek__Q34nw4r2ut13DvdFileStreamFlUl:
/* 80008A28 00003928  38 63 00 14 */	addi r3, r3, 0x14
/* 80008A2C 0000392C  4B FF FA 10 */	b Seek__Q44nw4r2ut10FileStream12FilePositionFlUl

.global Cancel__Q34nw4r2ut13DvdFileStreamFv
Cancel__Q34nw4r2ut13DvdFileStreamFv:
/* 80008A30 00003930  38 63 00 28 */	addi r3, r3, 0x28
/* 80008A34 00003934  48 13 56 90 */	b DVDCancel

.global CancelAsync__Q34nw4r2ut13DvdFileStreamFPFlPQ34nw4r2ut8IOStreamPv_vPv
CancelAsync__Q34nw4r2ut13DvdFileStreamFPFlPQ34nw4r2ut8IOStreamPv_vPv:
/* 80008A38 00003938  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80008A3C 0000393C  7C 08 02 A6 */	mflr r0
/* 80008A40 00003940  90 01 00 14 */	stw r0, 0x14(r1)
/* 80008A44 00003944  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80008A48 00003948  7C 7F 1B 78 */	mr r31, r3
/* 80008A4C 0000394C  90 83 00 1C */	stw r4, 0x1c(r3)
/* 80008A50 00003950  3C 80 80 01 */	lis r4, DvdCBAsyncCallback___Q34nw4r2ut13DvdFileStreamFlP15DVDCommandBlock@ha
/* 80008A54 00003954  38 84 85 14 */	addi r4, r4, DvdCBAsyncCallback___Q34nw4r2ut13DvdFileStreamFlP15DVDCommandBlock@l
/* 80008A58 00003958  90 A3 00 20 */	stw r5, 0x20(r3)
/* 80008A5C 0000395C  38 63 00 28 */	addi r3, r3, 0x28
/* 80008A60 00003960  48 13 53 11 */	bl DVDCancelAsync
/* 80008A64 00003964  2C 03 00 00 */	cmpwi r3, 0
/* 80008A68 00003968  41 82 00 0C */	beq lbl_80008A74
/* 80008A6C 0000396C  38 00 00 01 */	li r0, 1
/* 80008A70 00003970  98 1F 00 24 */	stb r0, 0x24(r31)
lbl_80008A74:
/* 80008A74 00003974  7C 03 00 D0 */	neg r0, r3
/* 80008A78 00003978  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80008A7C 0000397C  7C 00 1B 78 */	or r0, r0, r3
/* 80008A80 00003980  54 03 0F FE */	srwi r3, r0, 0x1f
/* 80008A84 00003984  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80008A88 00003988  7C 08 03 A6 */	mtlr r0
/* 80008A8C 0000398C  38 21 00 10 */	addi r1, r1, 0x10
/* 80008A90 00003990  4E 80 00 20 */	blr 

.global GetBufferAlign__Q34nw4r2ut13DvdFileStreamCFv
GetBufferAlign__Q34nw4r2ut13DvdFileStreamCFv:
/* 80008A94 00003994  38 60 00 20 */	li r3, 0x20
/* 80008A98 00003998  4E 80 00 20 */	blr 

.global GetSizeAlign__Q34nw4r2ut13DvdFileStreamCFv
GetSizeAlign__Q34nw4r2ut13DvdFileStreamCFv:
/* 80008A9C 0000399C  38 60 00 20 */	li r3, 0x20
/* 80008AA0 000039A0  4E 80 00 20 */	blr 

.global GetOffsetAlign__Q34nw4r2ut13DvdFileStreamCFv
GetOffsetAlign__Q34nw4r2ut13DvdFileStreamCFv:
/* 80008AA4 000039A4  38 60 00 04 */	li r3, 4
/* 80008AA8 000039A8  4E 80 00 20 */	blr 

.global CanCancel__Q34nw4r2ut13DvdFileStreamCFv
CanCancel__Q34nw4r2ut13DvdFileStreamCFv:
/* 80008AAC 000039AC  38 60 00 01 */	li r3, 1
/* 80008AB0 000039B0  4E 80 00 20 */	blr 

.global CanWrite__Q34nw4r2ut13DvdFileStreamCFv
CanWrite__Q34nw4r2ut13DvdFileStreamCFv:
/* 80008AB4 000039B4  38 60 00 00 */	li r3, 0
/* 80008AB8 000039B8  4E 80 00 20 */	blr 

.global CanRead__Q34nw4r2ut13DvdFileStreamCFv
CanRead__Q34nw4r2ut13DvdFileStreamCFv:
/* 80008ABC 000039BC  38 60 00 01 */	li r3, 1
/* 80008AC0 000039C0  4E 80 00 20 */	blr 

.global CanSeek__Q34nw4r2ut13DvdFileStreamCFv
CanSeek__Q34nw4r2ut13DvdFileStreamCFv:
/* 80008AC4 000039C4  38 60 00 01 */	li r3, 1
/* 80008AC8 000039C8  4E 80 00 20 */	blr 

.global CanAsync__Q34nw4r2ut13DvdFileStreamCFv
CanAsync__Q34nw4r2ut13DvdFileStreamCFv:
/* 80008ACC 000039CC  38 60 00 01 */	li r3, 1
/* 80008AD0 000039D0  4E 80 00 20 */	blr 

.global GetSize__Q34nw4r2ut13DvdFileStreamCFv
GetSize__Q34nw4r2ut13DvdFileStreamCFv:
/* 80008AD4 000039D4  80 63 00 14 */	lwz r3, 0x14(r3)
/* 80008AD8 000039D8  4E 80 00 20 */	blr 

.global Tell__Q34nw4r2ut13DvdFileStreamCFv
Tell__Q34nw4r2ut13DvdFileStreamCFv:
/* 80008ADC 000039DC  80 63 00 18 */	lwz r3, 0x18(r3)
/* 80008AE0 000039E0  4E 80 00 20 */	blr 

.global IsBusy__Q34nw4r2ut13DvdFileStreamCFv
IsBusy__Q34nw4r2ut13DvdFileStreamCFv:
/* 80008AE4 000039E4  88 63 00 6C */	lbz r3, 0x6c(r3)
/* 80008AE8 000039E8  4E 80 00 20 */	blr 

.global GetRuntimeTypeInfo__Q34nw4r2ut13DvdFileStreamCFv
GetRuntimeTypeInfo__Q34nw4r2ut13DvdFileStreamCFv:
/* 80008AEC 000039EC  38 6D 96 70 */	addi r3, r13, typeInfo__Q34nw4r2ut13DvdFileStream-_SDA_BASE_
/* 80008AF0 000039F0  4E 80 00 20 */	blr 

# __sinit_\ut_DvdFileStream_cpp
.global __sinit_$$3ut_DvdFileStream_cpp
__sinit_$$3ut_DvdFileStream_cpp:
/* 80008AF4 000039F4  38 0D 96 68 */	addi r0, r13, typeInfo__Q34nw4r2ut10FileStream-_SDA_BASE_
/* 80008AF8 000039F8  90 0D 96 70 */	stw r0, typeInfo__Q34nw4r2ut13DvdFileStream-_SDA_BASE_(r13)
/* 80008AFC 000039FC  4E 80 00 20 */	blr 
