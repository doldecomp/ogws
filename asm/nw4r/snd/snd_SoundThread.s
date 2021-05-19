.include "macros.inc"

.section .bss, "wa"
.global lbl_803E7870
lbl_803E7870:
	.skip 0x10
.global lbl_803E7880
lbl_803E7880:
	.skip 0x3A0

.section .sbss, "wa"
.global lbl_804BEB10
lbl_804BEB10:
	.skip 0x8

.section .text, "ax"  # 0x800076E0 - 0x80355080 
.global GetInstance__Q44nw4r3snd6detail11SoundThreadFv
GetInstance__Q44nw4r3snd6detail11SoundThreadFv:
/* 800478D8 000427D8  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800478DC 000427DC  7C 08 02 A6 */	mflr r0
/* 800478E0 000427E0  90 01 00 14 */	stw r0, 0x14(r1)
/* 800478E4 000427E4  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800478E8 000427E8  88 0D 97 90 */	lbz r0, lbl_804BEB10-_SDA_BASE_(r13)
/* 800478EC 000427EC  7C 00 07 75 */	extsb. r0, r0
/* 800478F0 000427F0  40 82 00 90 */	bne lbl_80047980
/* 800478F4 000427F4  3F E0 80 3E */	lis r31, lbl_803E7880@ha
/* 800478F8 000427F8  38 00 00 00 */	li r0, 0
/* 800478FC 000427FC  3B FF 78 80 */	addi r31, r31, lbl_803E7880@l
/* 80047900 00042800  38 A0 00 04 */	li r5, 4
/* 80047904 00042804  90 1F 03 7C */	stw r0, 0x37c(r31)
/* 80047908 00042808  38 FF 03 7C */	addi r7, r31, 0x37c
/* 8004790C 0004280C  38 DF 03 88 */	addi r6, r31, 0x388
/* 80047910 00042810  38 7F 03 20 */	addi r3, r31, 0x320
/* 80047914 00042814  90 1F 03 80 */	stw r0, 0x380(r31)
/* 80047918 00042818  38 9F 03 40 */	addi r4, r31, 0x340
/* 8004791C 0004281C  90 1F 03 88 */	stw r0, 0x388(r31)
/* 80047920 00042820  90 1F 03 8C */	stw r0, 0x38c(r31)
/* 80047924 00042824  90 1F 03 50 */	stw r0, 0x350(r31)
/* 80047928 00042828  90 1F 03 6C */	stw r0, 0x36c(r31)
/* 8004792C 0004282C  90 1F 03 70 */	stw r0, 0x370(r31)
/* 80047930 00042830  90 1F 03 78 */	stw r0, 0x378(r31)
/* 80047934 00042834  90 FF 03 7C */	stw r7, 0x37c(r31)
/* 80047938 00042838  90 FF 03 80 */	stw r7, 0x380(r31)
/* 8004793C 0004283C  90 1F 03 84 */	stw r0, 0x384(r31)
/* 80047940 00042840  90 DF 03 88 */	stw r6, 0x388(r31)
/* 80047944 00042844  90 DF 03 8C */	stw r6, 0x38c(r31)
/* 80047948 00042848  98 1F 03 94 */	stb r0, 0x394(r31)
/* 8004794C 0004284C  48 0A A7 11 */	bl OSInitMessageQueue
/* 80047950 00042850  38 7F 03 18 */	addi r3, r31, 0x318
/* 80047954 00042854  48 0A C7 F5 */	bl func_800F4148
/* 80047958 00042858  38 7F 03 54 */	addi r3, r31, 0x354
/* 8004795C 0004285C  48 0A B1 E9 */	bl OSInitMutex
/* 80047960 00042860  3C 80 80 04 */	lis r4, __dt__Q44nw4r3snd6detail11SoundThreadFv@ha
/* 80047964 00042864  3C A0 80 3E */	lis r5, lbl_803E7870@ha
/* 80047968 00042868  7F E3 FB 78 */	mr r3, r31
/* 8004796C 0004286C  38 84 79 9C */	addi r4, r4, __dt__Q44nw4r3snd6detail11SoundThreadFv@l
/* 80047970 00042870  38 A5 78 70 */	addi r5, r5, lbl_803E7870@l
/* 80047974 00042874  48 06 9E C1 */	bl func_800B1834
/* 80047978 00042878  38 00 00 01 */	li r0, 1
/* 8004797C 0004287C  98 0D 97 90 */	stb r0, lbl_804BEB10-_SDA_BASE_(r13)
lbl_80047980:
/* 80047980 00042880  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80047984 00042884  3C 60 80 3E */	lis r3, lbl_803E7880@ha
/* 80047988 00042888  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8004798C 0004288C  38 63 78 80 */	addi r3, r3, lbl_803E7880@l
/* 80047990 00042890  7C 08 03 A6 */	mtlr r0
/* 80047994 00042894  38 21 00 10 */	addi r1, r1, 0x10
/* 80047998 00042898  4E 80 00 20 */	blr 

.global __dt__Q44nw4r3snd6detail11SoundThreadFv
__dt__Q44nw4r3snd6detail11SoundThreadFv:
/* 8004799C 0004289C  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800479A0 000428A0  7C 08 02 A6 */	mflr r0
/* 800479A4 000428A4  2C 03 00 00 */	cmpwi r3, 0
/* 800479A8 000428A8  90 01 00 14 */	stw r0, 0x14(r1)
/* 800479AC 000428AC  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800479B0 000428B0  7C 9F 23 78 */	mr r31, r4
/* 800479B4 000428B4  93 C1 00 08 */	stw r30, 8(r1)
/* 800479B8 000428B8  7C 7E 1B 78 */	mr r30, r3
/* 800479BC 000428BC  41 82 00 34 */	beq lbl_800479F0
/* 800479C0 000428C0  34 63 03 84 */	addic. r3, r3, 0x384
/* 800479C4 000428C4  41 82 00 0C */	beq lbl_800479D0
/* 800479C8 000428C8  38 80 00 00 */	li r4, 0
/* 800479CC 000428CC  4B FB FF B1 */	bl __dt__Q44nw4r2ut6detail12LinkListImplFv
lbl_800479D0:
/* 800479D0 000428D0  34 7E 03 78 */	addic. r3, r30, 0x378
/* 800479D4 000428D4  41 82 00 0C */	beq lbl_800479E0
/* 800479D8 000428D8  38 80 00 00 */	li r4, 0
/* 800479DC 000428DC  4B FB FF A1 */	bl __dt__Q44nw4r2ut6detail12LinkListImplFv
lbl_800479E0:
/* 800479E0 000428E0  2C 1F 00 00 */	cmpwi r31, 0
/* 800479E4 000428E4  40 81 00 0C */	ble lbl_800479F0
/* 800479E8 000428E8  7F C3 F3 78 */	mr r3, r30
/* 800479EC 000428EC  48 05 B8 99 */	bl __dl__FPv
lbl_800479F0:
/* 800479F0 000428F0  7F C3 F3 78 */	mr r3, r30
/* 800479F4 000428F4  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 800479F8 000428F8  83 C1 00 08 */	lwz r30, 8(r1)
/* 800479FC 000428FC  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80047A00 00042900  7C 08 03 A6 */	mtlr r0
/* 80047A04 00042904  38 21 00 10 */	addi r1, r1, 0x10
/* 80047A08 00042908  4E 80 00 20 */	blr 

.global Create__Q44nw4r3snd6detail11SoundThreadFlPvUl
Create__Q44nw4r3snd6detail11SoundThreadFlPvUl:
/* 80047A0C 0004290C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80047A10 00042910  7C 08 02 A6 */	mflr r0
/* 80047A14 00042914  90 01 00 24 */	stw r0, 0x24(r1)
/* 80047A18 00042918  39 61 00 20 */	addi r11, r1, 0x20
/* 80047A1C 0004291C  48 06 A3 25 */	bl _savegpr_26
/* 80047A20 00042920  88 03 03 94 */	lbz r0, 0x394(r3)
/* 80047A24 00042924  7C 7A 1B 78 */	mr r26, r3
/* 80047A28 00042928  7C 9B 23 78 */	mr r27, r4
/* 80047A2C 0004292C  7C BC 2B 78 */	mr r28, r5
/* 80047A30 00042930  2C 00 00 00 */	cmpwi r0, 0
/* 80047A34 00042934  7C DD 33 78 */	mr r29, r6
/* 80047A38 00042938  41 82 00 0C */	beq lbl_80047A44
/* 80047A3C 0004293C  38 60 00 01 */	li r3, 1
/* 80047A40 00042940  48 00 00 EC */	b lbl_80047B2C
lbl_80047A44:
/* 80047A44 00042944  3B E0 00 01 */	li r31, 1
/* 80047A48 00042948  90 A3 03 50 */	stw r5, 0x350(r3)
/* 80047A4C 0004294C  9B E3 03 94 */	stb r31, 0x394(r3)
/* 80047A50 00042950  88 0D 97 90 */	lbz r0, lbl_804BEB10-_SDA_BASE_(r13)
/* 80047A54 00042954  7C 00 07 75 */	extsb. r0, r0
/* 80047A58 00042958  40 82 00 8C */	bne lbl_80047AE4
/* 80047A5C 0004295C  3F C0 80 3E */	lis r30, lbl_803E7880@ha
/* 80047A60 00042960  38 00 00 00 */	li r0, 0
/* 80047A64 00042964  3B DE 78 80 */	addi r30, r30, lbl_803E7880@l
/* 80047A68 00042968  38 A0 00 04 */	li r5, 4
/* 80047A6C 0004296C  90 1E 03 7C */	stw r0, 0x37c(r30)
/* 80047A70 00042970  38 DE 03 7C */	addi r6, r30, 0x37c
/* 80047A74 00042974  38 FE 03 88 */	addi r7, r30, 0x388
/* 80047A78 00042978  38 7E 03 20 */	addi r3, r30, 0x320
/* 80047A7C 0004297C  90 1E 03 80 */	stw r0, 0x380(r30)
/* 80047A80 00042980  38 9E 03 40 */	addi r4, r30, 0x340
/* 80047A84 00042984  90 1E 03 88 */	stw r0, 0x388(r30)
/* 80047A88 00042988  90 1E 03 8C */	stw r0, 0x38c(r30)
/* 80047A8C 0004298C  90 1E 03 50 */	stw r0, 0x350(r30)
/* 80047A90 00042990  90 1E 03 6C */	stw r0, 0x36c(r30)
/* 80047A94 00042994  90 1E 03 70 */	stw r0, 0x370(r30)
/* 80047A98 00042998  90 1E 03 78 */	stw r0, 0x378(r30)
/* 80047A9C 0004299C  90 DE 03 7C */	stw r6, 0x37c(r30)
/* 80047AA0 000429A0  90 DE 03 80 */	stw r6, 0x380(r30)
/* 80047AA4 000429A4  90 1E 03 84 */	stw r0, 0x384(r30)
/* 80047AA8 000429A8  90 FE 03 88 */	stw r7, 0x388(r30)
/* 80047AAC 000429AC  90 FE 03 8C */	stw r7, 0x38c(r30)
/* 80047AB0 000429B0  98 1E 03 94 */	stb r0, 0x394(r30)
/* 80047AB4 000429B4  48 0A A5 A9 */	bl OSInitMessageQueue
/* 80047AB8 000429B8  38 7E 03 18 */	addi r3, r30, 0x318
/* 80047ABC 000429BC  48 0A C6 8D */	bl func_800F4148
/* 80047AC0 000429C0  38 7E 03 54 */	addi r3, r30, 0x354
/* 80047AC4 000429C4  48 0A B0 81 */	bl OSInitMutex
/* 80047AC8 000429C8  3C 80 80 04 */	lis r4, __dt__Q44nw4r3snd6detail11SoundThreadFv@ha
/* 80047ACC 000429CC  3C A0 80 3E */	lis r5, lbl_803E7870@ha
/* 80047AD0 000429D0  7F C3 F3 78 */	mr r3, r30
/* 80047AD4 000429D4  38 84 79 9C */	addi r4, r4, __dt__Q44nw4r3snd6detail11SoundThreadFv@l
/* 80047AD8 000429D8  38 A5 78 70 */	addi r5, r5, lbl_803E7870@l
/* 80047ADC 000429DC  48 06 9D 59 */	bl func_800B1834
/* 80047AE0 000429E0  9B ED 97 90 */	stb r31, lbl_804BEB10-_SDA_BASE_(r13)
lbl_80047AE4:
/* 80047AE4 000429E4  3C 80 80 04 */	lis r4, SoundThreadFunc__Q44nw4r3snd6detail11SoundThreadFPv@ha
/* 80047AE8 000429E8  3C A0 80 3E */	lis r5, lbl_803E7880@ha
/* 80047AEC 000429EC  7F 43 D3 78 */	mr r3, r26
/* 80047AF0 000429F0  7F A7 EB 78 */	mr r7, r29
/* 80047AF4 000429F4  7F 68 DB 78 */	mr r8, r27
/* 80047AF8 000429F8  38 84 7D 50 */	addi r4, r4, SoundThreadFunc__Q44nw4r3snd6detail11SoundThreadFPv@l
/* 80047AFC 000429FC  38 A5 78 80 */	addi r5, r5, lbl_803E7880@l
/* 80047B00 00042A00  7C DC EA 14 */	add r6, r28, r29
/* 80047B04 00042A04  39 20 00 00 */	li r9, 0
/* 80047B08 00042A08  48 0A CC 25 */	bl OSCreateThread
/* 80047B0C 00042A0C  2C 03 00 00 */	cmpwi r3, 0
/* 80047B10 00042A10  7C 7F 1B 78 */	mr r31, r3
/* 80047B14 00042A14  41 82 00 0C */	beq lbl_80047B20
/* 80047B18 00042A18  7F 43 D3 78 */	mr r3, r26
/* 80047B1C 00042A1C  48 0A D3 19 */	bl OSResumeThread
lbl_80047B20:
/* 80047B20 00042A20  7C 1F 00 D0 */	neg r0, r31
/* 80047B24 00042A24  7C 00 FB 78 */	or r0, r0, r31
/* 80047B28 00042A28  54 03 0F FE */	srwi r3, r0, 0x1f
lbl_80047B2C:
/* 80047B2C 00042A2C  39 61 00 20 */	addi r11, r1, 0x20
/* 80047B30 00042A30  48 06 A2 5D */	bl _restgpr_26
/* 80047B34 00042A34  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80047B38 00042A38  7C 08 03 A6 */	mtlr r0
/* 80047B3C 00042A3C  38 21 00 20 */	addi r1, r1, 0x20
/* 80047B40 00042A40  4E 80 00 20 */	blr 

.global Shutdown__Q44nw4r3snd6detail11SoundThreadFv
Shutdown__Q44nw4r3snd6detail11SoundThreadFv:
/* 80047B44 00042A44  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80047B48 00042A48  7C 08 02 A6 */	mflr r0
/* 80047B4C 00042A4C  90 01 00 14 */	stw r0, 0x14(r1)
/* 80047B50 00042A50  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80047B54 00042A54  93 C1 00 08 */	stw r30, 8(r1)
/* 80047B58 00042A58  7C 7E 1B 78 */	mr r30, r3
/* 80047B5C 00042A5C  88 03 03 94 */	lbz r0, 0x394(r3)
/* 80047B60 00042A60  2C 00 00 00 */	cmpwi r0, 0
/* 80047B64 00042A64  41 82 00 C8 */	beq lbl_80047C2C
/* 80047B68 00042A68  88 0D 97 90 */	lbz r0, lbl_804BEB10-_SDA_BASE_(r13)
/* 80047B6C 00042A6C  7C 00 07 75 */	extsb. r0, r0
/* 80047B70 00042A70  40 82 00 90 */	bne lbl_80047C00
/* 80047B74 00042A74  3F E0 80 3E */	lis r31, lbl_803E7880@ha
/* 80047B78 00042A78  38 00 00 00 */	li r0, 0
/* 80047B7C 00042A7C  3B FF 78 80 */	addi r31, r31, lbl_803E7880@l
/* 80047B80 00042A80  38 A0 00 04 */	li r5, 4
/* 80047B84 00042A84  90 1F 03 7C */	stw r0, 0x37c(r31)
/* 80047B88 00042A88  38 DF 03 7C */	addi r6, r31, 0x37c
/* 80047B8C 00042A8C  38 FF 03 88 */	addi r7, r31, 0x388
/* 80047B90 00042A90  38 7F 03 20 */	addi r3, r31, 0x320
/* 80047B94 00042A94  90 1F 03 80 */	stw r0, 0x380(r31)
/* 80047B98 00042A98  38 9F 03 40 */	addi r4, r31, 0x340
/* 80047B9C 00042A9C  90 1F 03 88 */	stw r0, 0x388(r31)
/* 80047BA0 00042AA0  90 1F 03 8C */	stw r0, 0x38c(r31)
/* 80047BA4 00042AA4  90 1F 03 50 */	stw r0, 0x350(r31)
/* 80047BA8 00042AA8  90 1F 03 6C */	stw r0, 0x36c(r31)
/* 80047BAC 00042AAC  90 1F 03 70 */	stw r0, 0x370(r31)
/* 80047BB0 00042AB0  90 1F 03 78 */	stw r0, 0x378(r31)
/* 80047BB4 00042AB4  90 DF 03 7C */	stw r6, 0x37c(r31)
/* 80047BB8 00042AB8  90 DF 03 80 */	stw r6, 0x380(r31)
/* 80047BBC 00042ABC  90 1F 03 84 */	stw r0, 0x384(r31)
/* 80047BC0 00042AC0  90 FF 03 88 */	stw r7, 0x388(r31)
/* 80047BC4 00042AC4  90 FF 03 8C */	stw r7, 0x38c(r31)
/* 80047BC8 00042AC8  98 1F 03 94 */	stb r0, 0x394(r31)
/* 80047BCC 00042ACC  48 0A A4 91 */	bl OSInitMessageQueue
/* 80047BD0 00042AD0  38 7F 03 18 */	addi r3, r31, 0x318
/* 80047BD4 00042AD4  48 0A C5 75 */	bl func_800F4148
/* 80047BD8 00042AD8  38 7F 03 54 */	addi r3, r31, 0x354
/* 80047BDC 00042ADC  48 0A AF 69 */	bl OSInitMutex
/* 80047BE0 00042AE0  3C 80 80 04 */	lis r4, __dt__Q44nw4r3snd6detail11SoundThreadFv@ha
/* 80047BE4 00042AE4  3C A0 80 3E */	lis r5, lbl_803E7870@ha
/* 80047BE8 00042AE8  7F E3 FB 78 */	mr r3, r31
/* 80047BEC 00042AEC  38 84 79 9C */	addi r4, r4, __dt__Q44nw4r3snd6detail11SoundThreadFv@l
/* 80047BF0 00042AF0  38 A5 78 70 */	addi r5, r5, lbl_803E7870@l
/* 80047BF4 00042AF4  48 06 9C 41 */	bl func_800B1834
/* 80047BF8 00042AF8  38 00 00 01 */	li r0, 1
/* 80047BFC 00042AFC  98 0D 97 90 */	stb r0, lbl_804BEB10-_SDA_BASE_(r13)
lbl_80047C00:
/* 80047C00 00042B00  3C 60 80 3E */	lis r3, lbl_803E7880@ha
/* 80047C04 00042B04  38 80 00 02 */	li r4, 2
/* 80047C08 00042B08  38 63 78 80 */	addi r3, r3, lbl_803E7880@l
/* 80047C0C 00042B0C  38 A0 00 01 */	li r5, 1
/* 80047C10 00042B10  38 63 03 20 */	addi r3, r3, 0x320
/* 80047C14 00042B14  48 0A A6 4D */	bl func_800F2260
/* 80047C18 00042B18  7F C3 F3 78 */	mr r3, r30
/* 80047C1C 00042B1C  38 80 00 00 */	li r4, 0
/* 80047C20 00042B20  48 0A D0 35 */	bl OSJoinThread
/* 80047C24 00042B24  38 00 00 00 */	li r0, 0
/* 80047C28 00042B28  98 1E 03 94 */	stb r0, 0x394(r30)
lbl_80047C2C:
/* 80047C2C 00042B2C  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80047C30 00042B30  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80047C34 00042B34  83 C1 00 08 */	lwz r30, 8(r1)
/* 80047C38 00042B38  7C 08 03 A6 */	mtlr r0
/* 80047C3C 00042B3C  38 21 00 10 */	addi r1, r1, 0x10
/* 80047C40 00042B40  4E 80 00 20 */	blr 

.global AxCallbackFunc__Q44nw4r3snd6detail11SoundThreadFv
AxCallbackFunc__Q44nw4r3snd6detail11SoundThreadFv:
/* 80047C44 00042B44  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80047C48 00042B48  7C 08 02 A6 */	mflr r0
/* 80047C4C 00042B4C  90 01 00 14 */	stw r0, 0x14(r1)
/* 80047C50 00042B50  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80047C54 00042B54  93 C1 00 08 */	stw r30, 8(r1)
/* 80047C58 00042B58  88 0D 97 90 */	lbz r0, lbl_804BEB10-_SDA_BASE_(r13)
/* 80047C5C 00042B5C  7C 00 07 75 */	extsb. r0, r0
/* 80047C60 00042B60  40 82 00 90 */	bne lbl_80047CF0
/* 80047C64 00042B64  3F C0 80 3E */	lis r30, lbl_803E7880@ha
/* 80047C68 00042B68  38 00 00 00 */	li r0, 0
/* 80047C6C 00042B6C  3B DE 78 80 */	addi r30, r30, lbl_803E7880@l
/* 80047C70 00042B70  38 A0 00 04 */	li r5, 4
/* 80047C74 00042B74  90 1E 03 7C */	stw r0, 0x37c(r30)
/* 80047C78 00042B78  38 DE 03 7C */	addi r6, r30, 0x37c
/* 80047C7C 00042B7C  38 FE 03 88 */	addi r7, r30, 0x388
/* 80047C80 00042B80  38 7E 03 20 */	addi r3, r30, 0x320
/* 80047C84 00042B84  90 1E 03 80 */	stw r0, 0x380(r30)
/* 80047C88 00042B88  38 9E 03 40 */	addi r4, r30, 0x340
/* 80047C8C 00042B8C  90 1E 03 88 */	stw r0, 0x388(r30)
/* 80047C90 00042B90  90 1E 03 8C */	stw r0, 0x38c(r30)
/* 80047C94 00042B94  90 1E 03 50 */	stw r0, 0x350(r30)
/* 80047C98 00042B98  90 1E 03 6C */	stw r0, 0x36c(r30)
/* 80047C9C 00042B9C  90 1E 03 70 */	stw r0, 0x370(r30)
/* 80047CA0 00042BA0  90 1E 03 78 */	stw r0, 0x378(r30)
/* 80047CA4 00042BA4  90 DE 03 7C */	stw r6, 0x37c(r30)
/* 80047CA8 00042BA8  90 DE 03 80 */	stw r6, 0x380(r30)
/* 80047CAC 00042BAC  90 1E 03 84 */	stw r0, 0x384(r30)
/* 80047CB0 00042BB0  90 FE 03 88 */	stw r7, 0x388(r30)
/* 80047CB4 00042BB4  90 FE 03 8C */	stw r7, 0x38c(r30)
/* 80047CB8 00042BB8  98 1E 03 94 */	stb r0, 0x394(r30)
/* 80047CBC 00042BBC  48 0A A3 A1 */	bl OSInitMessageQueue
/* 80047CC0 00042BC0  38 7E 03 18 */	addi r3, r30, 0x318
/* 80047CC4 00042BC4  48 0A C4 85 */	bl func_800F4148
/* 80047CC8 00042BC8  38 7E 03 54 */	addi r3, r30, 0x354
/* 80047CCC 00042BCC  48 0A AE 79 */	bl OSInitMutex
/* 80047CD0 00042BD0  3C 80 80 04 */	lis r4, __dt__Q44nw4r3snd6detail11SoundThreadFv@ha
/* 80047CD4 00042BD4  3C A0 80 3E */	lis r5, lbl_803E7870@ha
/* 80047CD8 00042BD8  7F C3 F3 78 */	mr r3, r30
/* 80047CDC 00042BDC  38 84 79 9C */	addi r4, r4, __dt__Q44nw4r3snd6detail11SoundThreadFv@l
/* 80047CE0 00042BE0  38 A5 78 70 */	addi r5, r5, lbl_803E7870@l
/* 80047CE4 00042BE4  48 06 9B 51 */	bl func_800B1834
/* 80047CE8 00042BE8  38 00 00 01 */	li r0, 1
/* 80047CEC 00042BEC  98 0D 97 90 */	stb r0, lbl_804BEB10-_SDA_BASE_(r13)
lbl_80047CF0:
/* 80047CF0 00042BF0  3F C0 80 3E */	lis r30, lbl_803E7880@ha
/* 80047CF4 00042BF4  38 80 00 01 */	li r4, 1
/* 80047CF8 00042BF8  3B DE 78 80 */	addi r30, r30, lbl_803E7880@l
/* 80047CFC 00042BFC  38 A0 00 00 */	li r5, 0
/* 80047D00 00042C00  38 7E 03 20 */	addi r3, r30, 0x320
/* 80047D04 00042C04  48 0A A3 B9 */	bl func_800F20BC
/* 80047D08 00042C08  87 FE 03 88 */	lwzu r31, 0x388(r30)
/* 80047D0C 00042C0C  48 00 00 1C */	b lbl_80047D28
lbl_80047D10:
/* 80047D10 00042C10  7F E3 FB 78 */	mr r3, r31
/* 80047D14 00042C14  83 FF 00 00 */	lwz r31, 0(r31)
/* 80047D18 00042C18  81 83 00 08 */	lwz r12, 8(r3)
/* 80047D1C 00042C1C  81 8C 00 10 */	lwz r12, 0x10(r12)
/* 80047D20 00042C20  7D 89 03 A6 */	mtctr r12
/* 80047D24 00042C24  4E 80 04 21 */	bctrl 
lbl_80047D28:
/* 80047D28 00042C28  7C 1F F0 40 */	cmplw r31, r30
/* 80047D2C 00042C2C  40 82 FF E4 */	bne lbl_80047D10
/* 80047D30 00042C30  48 00 63 85 */	bl GetInstance__Q44nw4r3snd6detail12VoiceManagerFv
/* 80047D34 00042C34  48 00 69 29 */	bl NotifyVoiceUpdate__Q44nw4r3snd6detail12VoiceManagerFv
/* 80047D38 00042C38  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80047D3C 00042C3C  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80047D40 00042C40  83 C1 00 08 */	lwz r30, 8(r1)
/* 80047D44 00042C44  7C 08 03 A6 */	mtlr r0
/* 80047D48 00042C48  38 21 00 10 */	addi r1, r1, 0x10
/* 80047D4C 00042C4C  4E 80 00 20 */	blr 

.global SoundThreadFunc__Q44nw4r3snd6detail11SoundThreadFPv
SoundThreadFunc__Q44nw4r3snd6detail11SoundThreadFPv:
/* 80047D50 00042C50  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80047D54 00042C54  7C 08 02 A6 */	mflr r0
/* 80047D58 00042C58  90 01 00 14 */	stw r0, 0x14(r1)
/* 80047D5C 00042C5C  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80047D60 00042C60  7C 7F 1B 78 */	mr r31, r3
/* 80047D64 00042C64  4B FE 95 85 */	bl GetInstance__Q44nw4r3snd6detail9AxManagerFv
/* 80047D68 00042C68  3C A0 80 04 */	lis r5, AxCallbackFunc__Q44nw4r3snd6detail11SoundThreadFv@ha
/* 80047D6C 00042C6C  38 9F 03 6C */	addi r4, r31, 0x36c
/* 80047D70 00042C70  38 A5 7C 44 */	addi r5, r5, AxCallbackFunc__Q44nw4r3snd6detail11SoundThreadFv@l
/* 80047D74 00042C74  4B FE 9C 65 */	bl RegisterCallback__Q44nw4r3snd6detail9AxManagerFPQ54nw4r3snd6detail9AxManager16CallbackListNodePFv_v
/* 80047D78 00042C78  7F E3 FB 78 */	mr r3, r31
/* 80047D7C 00042C7C  48 00 00 ED */	bl SoundThreadProc__Q44nw4r3snd6detail11SoundThreadFv
/* 80047D80 00042C80  4B FE 95 69 */	bl GetInstance__Q44nw4r3snd6detail9AxManagerFv
/* 80047D84 00042C84  38 9F 03 6C */	addi r4, r31, 0x36c
/* 80047D88 00042C88  4B FE 9C BD */	bl UnregisterCallback__Q44nw4r3snd6detail9AxManagerFPQ54nw4r3snd6detail9AxManager16CallbackListNode
/* 80047D8C 00042C8C  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80047D90 00042C90  38 60 00 00 */	li r3, 0
/* 80047D94 00042C94  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80047D98 00042C98  7C 08 03 A6 */	mtlr r0
/* 80047D9C 00042C9C  38 21 00 10 */	addi r1, r1, 0x10
/* 80047DA0 00042CA0  4E 80 00 20 */	blr 

.global RegisterPlayerCallback__Q44nw4r3snd6detail11SoundThreadFPQ54nw4r3snd6detail11SoundThread14PlayerCallback
RegisterPlayerCallback__Q44nw4r3snd6detail11SoundThreadFPQ54nw4r3snd6detail11SoundThread14PlayerCallback:
/* 80047DA4 00042CA4  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80047DA8 00042CA8  7C 08 02 A6 */	mflr r0
/* 80047DAC 00042CAC  90 01 00 24 */	stw r0, 0x24(r1)
/* 80047DB0 00042CB0  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80047DB4 00042CB4  3B E3 03 54 */	addi r31, r3, 0x354
/* 80047DB8 00042CB8  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80047DBC 00042CBC  7C 9E 23 78 */	mr r30, r4
/* 80047DC0 00042CC0  93 A1 00 14 */	stw r29, 0x14(r1)
/* 80047DC4 00042CC4  7C 7D 1B 78 */	mr r29, r3
/* 80047DC8 00042CC8  7F E3 FB 78 */	mr r3, r31
/* 80047DCC 00042CCC  48 0A AD B1 */	bl OSLockMutex
/* 80047DD0 00042CD0  38 1D 03 88 */	addi r0, r29, 0x388
/* 80047DD4 00042CD4  7F C5 F3 78 */	mr r5, r30
/* 80047DD8 00042CD8  90 01 00 08 */	stw r0, 8(r1)
/* 80047DDC 00042CDC  38 7D 03 84 */	addi r3, r29, 0x384
/* 80047DE0 00042CE0  38 81 00 08 */	addi r4, r1, 8
/* 80047DE4 00042CE4  4B FB FC A9 */	bl Insert__Q44nw4r2ut6detail12LinkListImplFQ54nw4r2ut6detail12LinkListImpl8IteratorPQ34nw4r2ut12LinkListNode
/* 80047DE8 00042CE8  7F E3 FB 78 */	mr r3, r31
/* 80047DEC 00042CEC  48 0A AE 6D */	bl OSUnlockMutex
/* 80047DF0 00042CF0  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80047DF4 00042CF4  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80047DF8 00042CF8  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80047DFC 00042CFC  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 80047E00 00042D00  7C 08 03 A6 */	mtlr r0
/* 80047E04 00042D04  38 21 00 20 */	addi r1, r1, 0x20
/* 80047E08 00042D08  4E 80 00 20 */	blr 

.global UnregisterPlayerCallback__Q44nw4r3snd6detail11SoundThreadFPQ54nw4r3snd6detail11SoundThread14PlayerCallback
UnregisterPlayerCallback__Q44nw4r3snd6detail11SoundThreadFPQ54nw4r3snd6detail11SoundThread14PlayerCallback:
/* 80047E0C 00042D0C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80047E10 00042D10  7C 08 02 A6 */	mflr r0
/* 80047E14 00042D14  90 01 00 24 */	stw r0, 0x24(r1)
/* 80047E18 00042D18  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80047E1C 00042D1C  3B E3 03 54 */	addi r31, r3, 0x354
/* 80047E20 00042D20  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80047E24 00042D24  7C 9E 23 78 */	mr r30, r4
/* 80047E28 00042D28  93 A1 00 14 */	stw r29, 0x14(r1)
/* 80047E2C 00042D2C  7C 7D 1B 78 */	mr r29, r3
/* 80047E30 00042D30  7F E3 FB 78 */	mr r3, r31
/* 80047E34 00042D34  48 0A AD 49 */	bl OSLockMutex
/* 80047E38 00042D38  7F C4 F3 78 */	mr r4, r30
/* 80047E3C 00042D3C  38 7D 03 84 */	addi r3, r29, 0x384
/* 80047E40 00042D40  4B FB FC 79 */	bl Erase__Q44nw4r2ut6detail12LinkListImplFPQ34nw4r2ut12LinkListNode
/* 80047E44 00042D44  7F E3 FB 78 */	mr r3, r31
/* 80047E48 00042D48  48 0A AE 11 */	bl OSUnlockMutex
/* 80047E4C 00042D4C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80047E50 00042D50  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80047E54 00042D54  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80047E58 00042D58  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 80047E5C 00042D5C  7C 08 03 A6 */	mtlr r0
/* 80047E60 00042D60  38 21 00 20 */	addi r1, r1, 0x20
/* 80047E64 00042D64  4E 80 00 20 */	blr 

.global SoundThreadProc__Q44nw4r3snd6detail11SoundThreadFv
SoundThreadProc__Q44nw4r3snd6detail11SoundThreadFv:
/* 80047E68 00042D68  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 80047E6C 00042D6C  7C 08 02 A6 */	mflr r0
/* 80047E70 00042D70  90 01 00 34 */	stw r0, 0x34(r1)
/* 80047E74 00042D74  39 61 00 30 */	addi r11, r1, 0x30
/* 80047E78 00042D78  48 06 9E CD */	bl _savegpr_27
/* 80047E7C 00042D7C  7C 7B 1B 78 */	mr r27, r3
lbl_80047E80:
/* 80047E80 00042D80  38 7B 03 20 */	addi r3, r27, 0x320
/* 80047E84 00042D84  38 81 00 08 */	addi r4, r1, 8
/* 80047E88 00042D88  38 A0 00 01 */	li r5, 1
/* 80047E8C 00042D8C  48 0A A2 F9 */	bl func_800F2184
/* 80047E90 00042D90  80 01 00 08 */	lwz r0, 8(r1)
/* 80047E94 00042D94  28 00 00 01 */	cmplwi r0, 1
/* 80047E98 00042D98  40 82 00 E8 */	bne lbl_80047F80
/* 80047E9C 00042D9C  3B 9B 03 54 */	addi r28, r27, 0x354
/* 80047EA0 00042DA0  7F 83 E3 78 */	mr r3, r28
/* 80047EA4 00042DA4  48 0A AC D9 */	bl OSLockMutex
/* 80047EA8 00042DA8  83 FB 03 7C */	lwz r31, 0x37c(r27)
/* 80047EAC 00042DAC  3B DB 03 7C */	addi r30, r27, 0x37c
/* 80047EB0 00042DB0  48 00 00 1C */	b lbl_80047ECC
lbl_80047EB4:
/* 80047EB4 00042DB4  7F E3 FB 78 */	mr r3, r31
/* 80047EB8 00042DB8  83 FF 00 00 */	lwz r31, 0(r31)
/* 80047EBC 00042DBC  81 83 00 08 */	lwz r12, 8(r3)
/* 80047EC0 00042DC0  81 8C 00 0C */	lwz r12, 0xc(r12)
/* 80047EC4 00042DC4  7D 89 03 A6 */	mtctr r12
/* 80047EC8 00042DC8  4E 80 04 21 */	bctrl 
lbl_80047ECC:
/* 80047ECC 00042DCC  7C 1F F0 40 */	cmplw r31, r30
/* 80047ED0 00042DD0  40 82 FF E4 */	bne lbl_80047EB4
/* 80047ED4 00042DD4  48 0A D7 49 */	bl func_800F561C
/* 80047ED8 00042DD8  7C 7D 1B 78 */	mr r29, r3
/* 80047EDC 00042DDC  4B FE D0 6D */	bl GetInstance__Q44nw4r3snd6detail14AxVoiceManagerFv
/* 80047EE0 00042DE0  4B FE D9 21 */	bl FreeAllReservedAxVoice__Q44nw4r3snd6detail14AxVoiceManagerFv
/* 80047EE4 00042DE4  4B FE 94 05 */	bl GetInstance__Q44nw4r3snd6detail9AxManagerFv
/* 80047EE8 00042DE8  4B FE 96 C5 */	bl Update__Q44nw4r3snd6detail9AxManagerFv
/* 80047EEC 00042DEC  4B FE 93 FD */	bl GetInstance__Q44nw4r3snd6detail9AxManagerFv
/* 80047EF0 00042DF0  88 03 00 1A */	lbz r0, 0x1a(r3)
/* 80047EF4 00042DF4  2C 00 00 00 */	cmpwi r0, 0
/* 80047EF8 00042DF8  40 82 00 38 */	bne lbl_80047F30
/* 80047EFC 00042DFC  83 DB 03 88 */	lwz r30, 0x388(r27)
/* 80047F00 00042E00  3B FB 03 88 */	addi r31, r27, 0x388
/* 80047F04 00042E04  48 00 00 1C */	b lbl_80047F20
lbl_80047F08:
/* 80047F08 00042E08  7F C3 F3 78 */	mr r3, r30
/* 80047F0C 00042E0C  83 DE 00 00 */	lwz r30, 0(r30)
/* 80047F10 00042E10  81 83 00 08 */	lwz r12, 8(r3)
/* 80047F14 00042E14  81 8C 00 0C */	lwz r12, 0xc(r12)
/* 80047F18 00042E18  7D 89 03 A6 */	mtctr r12
/* 80047F1C 00042E1C  4E 80 04 21 */	bctrl 
lbl_80047F20:
/* 80047F20 00042E20  7C 1E F8 40 */	cmplw r30, r31
/* 80047F24 00042E24  40 82 FF E4 */	bne lbl_80047F08
/* 80047F28 00042E28  4B FE F5 41 */	bl GetInstance__Q44nw4r3snd6detail14ChannelManagerFv
/* 80047F2C 00042E2C  4B FE F8 31 */	bl UpdateAllChannel__Q44nw4r3snd6detail14ChannelManagerFv
lbl_80047F30:
/* 80047F30 00042E30  48 00 6D 29 */	bl CalcRandom__Q44nw4r3snd6detail4UtilFv
/* 80047F34 00042E34  48 00 61 81 */	bl GetInstance__Q44nw4r3snd6detail12VoiceManagerFv
/* 80047F38 00042E38  48 00 66 75 */	bl UpdateAllVoices__Q44nw4r3snd6detail12VoiceManagerFv
/* 80047F3C 00042E3C  48 0A D6 E1 */	bl func_800F561C
/* 80047F40 00042E40  7C 1D 18 50 */	subf r0, r29, r3
/* 80047F44 00042E44  83 DB 03 7C */	lwz r30, 0x37c(r27)
/* 80047F48 00042E48  90 1B 03 90 */	stw r0, 0x390(r27)
/* 80047F4C 00042E4C  3B FB 03 7C */	addi r31, r27, 0x37c
/* 80047F50 00042E50  48 00 00 1C */	b lbl_80047F6C
lbl_80047F54:
/* 80047F54 00042E54  7F C3 F3 78 */	mr r3, r30
/* 80047F58 00042E58  83 DE 00 00 */	lwz r30, 0(r30)
/* 80047F5C 00042E5C  81 83 00 08 */	lwz r12, 8(r3)
/* 80047F60 00042E60  81 8C 00 10 */	lwz r12, 0x10(r12)
/* 80047F64 00042E64  7D 89 03 A6 */	mtctr r12
/* 80047F68 00042E68  4E 80 04 21 */	bctrl 
lbl_80047F6C:
/* 80047F6C 00042E6C  7C 1E F8 40 */	cmplw r30, r31
/* 80047F70 00042E70  40 82 FF E4 */	bne lbl_80047F54
/* 80047F74 00042E74  7F 83 E3 78 */	mr r3, r28
/* 80047F78 00042E78  48 0A AC E1 */	bl OSUnlockMutex
/* 80047F7C 00042E7C  4B FF FF 04 */	b lbl_80047E80
lbl_80047F80:
/* 80047F80 00042E80  28 00 00 02 */	cmplwi r0, 2
/* 80047F84 00042E84  40 82 FE FC */	bne lbl_80047E80
/* 80047F88 00042E88  83 DB 03 88 */	lwz r30, 0x388(r27)
/* 80047F8C 00042E8C  3B FB 03 88 */	addi r31, r27, 0x388
/* 80047F90 00042E90  48 00 00 1C */	b lbl_80047FAC
lbl_80047F94:
/* 80047F94 00042E94  7F C3 F3 78 */	mr r3, r30
/* 80047F98 00042E98  83 DE 00 00 */	lwz r30, 0(r30)
/* 80047F9C 00042E9C  81 83 00 08 */	lwz r12, 8(r3)
/* 80047FA0 00042EA0  81 8C 00 14 */	lwz r12, 0x14(r12)
/* 80047FA4 00042EA4  7D 89 03 A6 */	mtctr r12
/* 80047FA8 00042EA8  4E 80 04 21 */	bctrl 
lbl_80047FAC:
/* 80047FAC 00042EAC  7C 1E F8 40 */	cmplw r30, r31
/* 80047FB0 00042EB0  40 82 FF E4 */	bne lbl_80047F94
/* 80047FB4 00042EB4  39 61 00 30 */	addi r11, r1, 0x30
/* 80047FB8 00042EB8  48 06 9D D9 */	bl _restgpr_27
/* 80047FBC 00042EBC  80 01 00 34 */	lwz r0, 0x34(r1)
/* 80047FC0 00042EC0  7C 08 03 A6 */	mtlr r0
/* 80047FC4 00042EC4  38 21 00 30 */	addi r1, r1, 0x30
/* 80047FC8 00042EC8  4E 80 00 20 */	blr 
