.include "macros.inc"

.section .bss, "wa"
.global lbl_803EBCA0
lbl_803EBCA0:
	.skip 0xC
.global lbl_803EBCAC
lbl_803EBCAC:
	.skip 0x1C

.section .sbss, "wa"
.global lbl_804BEB30
lbl_804BEB30:
	.skip 0x8

.section .text, "ax"  # 0x800076E0 - 0x80355080 
.global GetInstance__Q44nw4r3snd6detail12VoiceManagerFv
GetInstance__Q44nw4r3snd6detail12VoiceManagerFv:
/* 8004E0B4 00048FB4  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8004E0B8 00048FB8  7C 08 02 A6 */	mflr r0
/* 8004E0BC 00048FBC  90 01 00 14 */	stw r0, 0x14(r1)
/* 8004E0C0 00048FC0  88 0D 97 B0 */	lbz r0, lbl_804BEB30-_SDA_BASE_(r13)
/* 8004E0C4 00048FC4  7C 00 07 75 */	extsb. r0, r0
/* 8004E0C8 00048FC8  40 82 00 60 */	bne lbl_8004E128
/* 8004E0CC 00048FCC  3C C0 80 3F */	lis r6, lbl_803EBCAC@ha
/* 8004E0D0 00048FD0  38 00 00 00 */	li r0, 0
/* 8004E0D4 00048FD4  38 66 BC AC */	addi r3, r6, lbl_803EBCAC@l
/* 8004E0D8 00048FD8  3C 80 80 05 */	lis r4, __dt__Q44nw4r3snd6detail12VoiceManagerFv@ha
/* 8004E0DC 00048FDC  90 03 00 08 */	stw r0, 8(r3)
/* 8004E0E0 00048FE0  39 03 00 08 */	addi r8, r3, 8
/* 8004E0E4 00048FE4  38 E3 00 14 */	addi r7, r3, 0x14
/* 8004E0E8 00048FE8  3C A0 80 3F */	lis r5, lbl_803EBCA0@ha
/* 8004E0EC 00048FEC  90 03 00 0C */	stw r0, 0xc(r3)
/* 8004E0F0 00048FF0  38 84 E1 40 */	addi r4, r4, __dt__Q44nw4r3snd6detail12VoiceManagerFv@l
/* 8004E0F4 00048FF4  38 A5 BC A0 */	addi r5, r5, lbl_803EBCA0@l
/* 8004E0F8 00048FF8  90 03 00 14 */	stw r0, 0x14(r3)
/* 8004E0FC 00048FFC  90 03 00 18 */	stw r0, 0x18(r3)
/* 8004E100 00049000  98 06 BC AC */	stb r0, -0x4354(r6)
/* 8004E104 00049004  90 03 00 04 */	stw r0, 4(r3)
/* 8004E108 00049008  91 03 00 08 */	stw r8, 8(r3)
/* 8004E10C 0004900C  91 03 00 0C */	stw r8, 0xc(r3)
/* 8004E110 00049010  90 03 00 10 */	stw r0, 0x10(r3)
/* 8004E114 00049014  90 E3 00 14 */	stw r7, 0x14(r3)
/* 8004E118 00049018  90 E3 00 18 */	stw r7, 0x18(r3)
/* 8004E11C 0004901C  48 06 37 19 */	bl func_800B1834
/* 8004E120 00049020  38 00 00 01 */	li r0, 1
/* 8004E124 00049024  98 0D 97 B0 */	stb r0, lbl_804BEB30-_SDA_BASE_(r13)
lbl_8004E128:
/* 8004E128 00049028  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8004E12C 0004902C  3C 60 80 3F */	lis r3, lbl_803EBCAC@ha
/* 8004E130 00049030  38 63 BC AC */	addi r3, r3, lbl_803EBCAC@l
/* 8004E134 00049034  7C 08 03 A6 */	mtlr r0
/* 8004E138 00049038  38 21 00 10 */	addi r1, r1, 0x10
/* 8004E13C 0004903C  4E 80 00 20 */	blr 

.global __dt__Q44nw4r3snd6detail12VoiceManagerFv
__dt__Q44nw4r3snd6detail12VoiceManagerFv:
/* 8004E140 00049040  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8004E144 00049044  7C 08 02 A6 */	mflr r0
/* 8004E148 00049048  2C 03 00 00 */	cmpwi r3, 0
/* 8004E14C 0004904C  90 01 00 14 */	stw r0, 0x14(r1)
/* 8004E150 00049050  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8004E154 00049054  7C 9F 23 78 */	mr r31, r4
/* 8004E158 00049058  93 C1 00 08 */	stw r30, 8(r1)
/* 8004E15C 0004905C  7C 7E 1B 78 */	mr r30, r3
/* 8004E160 00049060  41 82 00 34 */	beq lbl_8004E194
/* 8004E164 00049064  34 63 00 10 */	addic. r3, r3, 0x10
/* 8004E168 00049068  41 82 00 0C */	beq lbl_8004E174
/* 8004E16C 0004906C  38 80 00 00 */	li r4, 0
/* 8004E170 00049070  4B FB 98 0D */	bl __dt__Q44nw4r2ut6detail12LinkListImplFv
lbl_8004E174:
/* 8004E174 00049074  34 7E 00 04 */	addic. r3, r30, 4
/* 8004E178 00049078  41 82 00 0C */	beq lbl_8004E184
/* 8004E17C 0004907C  38 80 00 00 */	li r4, 0
/* 8004E180 00049080  4B FB 97 FD */	bl __dt__Q44nw4r2ut6detail12LinkListImplFv
lbl_8004E184:
/* 8004E184 00049084  2C 1F 00 00 */	cmpwi r31, 0
/* 8004E188 00049088  40 81 00 0C */	ble lbl_8004E194
/* 8004E18C 0004908C  7F C3 F3 78 */	mr r3, r30
/* 8004E190 00049090  48 05 50 F5 */	bl __dl__FPv
lbl_8004E194:
/* 8004E194 00049094  7F C3 F3 78 */	mr r3, r30
/* 8004E198 00049098  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8004E19C 0004909C  83 C1 00 08 */	lwz r30, 8(r1)
/* 8004E1A0 000490A0  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8004E1A4 000490A4  7C 08 03 A6 */	mtlr r0
/* 8004E1A8 000490A8  38 21 00 10 */	addi r1, r1, 0x10
/* 8004E1AC 000490AC  4E 80 00 20 */	blr 

.global GetRequiredMemSize__Q44nw4r3snd6detail12VoiceManagerFv
GetRequiredMemSize__Q44nw4r3snd6detail12VoiceManagerFv:
/* 8004E1B0 000490B0  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8004E1B4 000490B4  7C 08 02 A6 */	mflr r0
/* 8004E1B8 000490B8  90 01 00 14 */	stw r0, 0x14(r1)
/* 8004E1BC 000490BC  48 0B 93 E5 */	bl AXGetMaxVoices
/* 8004E1C0 000490C0  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8004E1C4 000490C4  1C 63 01 2C */	mulli r3, r3, 0x12c
/* 8004E1C8 000490C8  7C 08 03 A6 */	mtlr r0
/* 8004E1CC 000490CC  38 21 00 10 */	addi r1, r1, 0x10
/* 8004E1D0 000490D0  4E 80 00 20 */	blr 

.global Setup__Q44nw4r3snd6detail12VoiceManagerFPvUl
Setup__Q44nw4r3snd6detail12VoiceManagerFPvUl:
/* 8004E1D4 000490D4  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8004E1D8 000490D8  7C 08 02 A6 */	mflr r0
/* 8004E1DC 000490DC  90 01 00 34 */	stw r0, 0x34(r1)
/* 8004E1E0 000490E0  39 61 00 30 */	addi r11, r1, 0x30
/* 8004E1E4 000490E4  48 06 3B 61 */	bl _savegpr_27
/* 8004E1E8 000490E8  88 03 00 00 */	lbz r0, 0(r3)
/* 8004E1EC 000490EC  7C 7B 1B 78 */	mr r27, r3
/* 8004E1F0 000490F0  2C 00 00 00 */	cmpwi r0, 0
/* 8004E1F4 000490F4  40 82 00 6C */	bne lbl_8004E260
/* 8004E1F8 000490F8  3C C0 1B 4F */	lis r6, 0x1B4E81B5@ha
/* 8004E1FC 000490FC  7C 9D 23 78 */	mr r29, r4
/* 8004E200 00049100  38 06 81 B5 */	addi r0, r6, 0x1B4E81B5@l
/* 8004E204 00049104  3B 80 00 00 */	li r28, 0
/* 8004E208 00049108  7C 00 28 16 */	mulhwu r0, r0, r5
/* 8004E20C 0004910C  54 1E D9 7F */	rlwinm. r30, r0, 0x1b, 5, 0x1f
/* 8004E210 00049110  41 82 00 48 */	beq lbl_8004E258
/* 8004E214 00049114  3B E3 00 14 */	addi r31, r3, 0x14
/* 8004E218 00049118  48 00 00 38 */	b lbl_8004E250
lbl_8004E21C:
/* 8004E21C 0004911C  2C 1D 00 00 */	cmpwi r29, 0
/* 8004E220 00049120  7F A5 EB 78 */	mr r5, r29
/* 8004E224 00049124  41 82 00 10 */	beq lbl_8004E234
/* 8004E228 00049128  7F A3 EB 78 */	mr r3, r29
/* 8004E22C 0004912C  4B FF D7 55 */	bl __ct__Q44nw4r3snd6detail5VoiceFv
/* 8004E230 00049130  7C 65 1B 78 */	mr r5, r3
lbl_8004E234:
/* 8004E234 00049134  93 E1 00 08 */	stw r31, 8(r1)
/* 8004E238 00049138  38 7B 00 10 */	addi r3, r27, 0x10
/* 8004E23C 0004913C  38 81 00 08 */	addi r4, r1, 8
/* 8004E240 00049140  38 A5 01 24 */	addi r5, r5, 0x124
/* 8004E244 00049144  4B FB 98 49 */	bl Insert__Q44nw4r2ut6detail12LinkListImplFQ54nw4r2ut6detail12LinkListImpl8IteratorPQ34nw4r2ut12LinkListNode
/* 8004E248 00049148  3B BD 01 2C */	addi r29, r29, 0x12c
/* 8004E24C 0004914C  3B 9C 00 01 */	addi r28, r28, 1
lbl_8004E250:
/* 8004E250 00049150  7C 1C F0 40 */	cmplw r28, r30
/* 8004E254 00049154  41 80 FF C8 */	blt lbl_8004E21C
lbl_8004E258:
/* 8004E258 00049158  38 00 00 01 */	li r0, 1
/* 8004E25C 0004915C  98 1B 00 00 */	stb r0, 0(r27)
lbl_8004E260:
/* 8004E260 00049160  39 61 00 30 */	addi r11, r1, 0x30
/* 8004E264 00049164  48 06 3B 2D */	bl _restgpr_27
/* 8004E268 00049168  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8004E26C 0004916C  7C 08 03 A6 */	mtlr r0
/* 8004E270 00049170  38 21 00 30 */	addi r1, r1, 0x30
/* 8004E274 00049174  4E 80 00 20 */	blr 

.global Shutdown__Q44nw4r3snd6detail12VoiceManagerFv
Shutdown__Q44nw4r3snd6detail12VoiceManagerFv:
/* 8004E278 00049178  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8004E27C 0004917C  7C 08 02 A6 */	mflr r0
/* 8004E280 00049180  90 01 00 24 */	stw r0, 0x24(r1)
/* 8004E284 00049184  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8004E288 00049188  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8004E28C 0004918C  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8004E290 00049190  7C 7D 1B 78 */	mr r29, r3
/* 8004E294 00049194  88 03 00 00 */	lbz r0, 0(r3)
/* 8004E298 00049198  2C 00 00 00 */	cmpwi r0, 0
/* 8004E29C 0004919C  41 82 00 A0 */	beq lbl_8004E33C
/* 8004E2A0 000491A0  48 0A 36 21 */	bl OSDisableInterrupts
/* 8004E2A4 000491A4  7C 7F 1B 78 */	mr r31, r3
/* 8004E2A8 000491A8  48 00 00 3C */	b lbl_8004E2E4
lbl_8004E2AC:
/* 8004E2AC 000491AC  80 7D 00 08 */	lwz r3, 8(r29)
/* 8004E2B0 000491B0  3B C3 FE DC */	addi r30, r3, -292
/* 8004E2B4 000491B4  7F C3 F3 78 */	mr r3, r30
/* 8004E2B8 000491B8  4B FF E4 6D */	bl Stop__Q44nw4r3snd6detail5VoiceFv
/* 8004E2BC 000491BC  81 9E 00 A4 */	lwz r12, 0xa4(r30)
/* 8004E2C0 000491C0  2C 0C 00 00 */	cmpwi r12, 0
/* 8004E2C4 000491C4  41 82 00 18 */	beq lbl_8004E2DC
/* 8004E2C8 000491C8  7F C3 F3 78 */	mr r3, r30
/* 8004E2CC 000491CC  80 BE 00 A8 */	lwz r5, 0xa8(r30)
/* 8004E2D0 000491D0  38 80 00 01 */	li r4, 1
/* 8004E2D4 000491D4  7D 89 03 A6 */	mtctr r12
/* 8004E2D8 000491D8  4E 80 04 21 */	bctrl 
lbl_8004E2DC:
/* 8004E2DC 000491DC  7F C3 F3 78 */	mr r3, r30
/* 8004E2E0 000491E0  4B FF E0 A9 */	bl Free__Q44nw4r3snd6detail5VoiceFv
lbl_8004E2E4:
/* 8004E2E4 000491E4  80 1D 00 04 */	lwz r0, 4(r29)
/* 8004E2E8 000491E8  2C 00 00 00 */	cmpwi r0, 0
/* 8004E2EC 000491EC  40 82 FF C0 */	bne lbl_8004E2AC
/* 8004E2F0 000491F0  7F E3 FB 78 */	mr r3, r31
/* 8004E2F4 000491F4  48 0A 35 F5 */	bl OSRestoreInterrupts
/* 8004E2F8 000491F8  48 00 00 30 */	b lbl_8004E328
lbl_8004E2FC:
/* 8004E2FC 000491FC  83 DD 00 14 */	lwz r30, 0x14(r29)
/* 8004E300 00049200  38 7D 00 10 */	addi r3, r29, 0x10
/* 8004E304 00049204  38 81 00 08 */	addi r4, r1, 8
/* 8004E308 00049208  93 C1 00 08 */	stw r30, 8(r1)
/* 8004E30C 0004920C  4B FB 96 F5 */	bl Erase__Q44nw4r2ut6detail12LinkListImplFQ54nw4r2ut6detail12LinkListImpl8Iterator
/* 8004E310 00049210  81 9E FE E4 */	lwz r12, -0x11c(r30)
/* 8004E314 00049214  38 7E FE DC */	addi r3, r30, -292
/* 8004E318 00049218  38 80 FF FF */	li r4, -1
/* 8004E31C 0004921C  81 8C 00 08 */	lwz r12, 8(r12)
/* 8004E320 00049220  7D 89 03 A6 */	mtctr r12
/* 8004E324 00049224  4E 80 04 21 */	bctrl 
lbl_8004E328:
/* 8004E328 00049228  80 1D 00 10 */	lwz r0, 0x10(r29)
/* 8004E32C 0004922C  2C 00 00 00 */	cmpwi r0, 0
/* 8004E330 00049230  40 82 FF CC */	bne lbl_8004E2FC
/* 8004E334 00049234  38 00 00 00 */	li r0, 0
/* 8004E338 00049238  98 1D 00 00 */	stb r0, 0(r29)
lbl_8004E33C:
/* 8004E33C 0004923C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8004E340 00049240  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8004E344 00049244  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8004E348 00049248  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8004E34C 0004924C  7C 08 03 A6 */	mtlr r0
/* 8004E350 00049250  38 21 00 20 */	addi r1, r1, 0x20
/* 8004E354 00049254  4E 80 00 20 */	blr 

.global AllocVoice__Q44nw4r3snd6detail12VoiceManagerFiiiPFPQ44nw4r3snd6detail5VoiceQ54nw4r3snd6detail5Voice19VoiceCallbackStatusPv_vPv
AllocVoice__Q44nw4r3snd6detail12VoiceManagerFiiiPFPQ44nw4r3snd6detail5VoiceQ54nw4r3snd6detail5Voice19VoiceCallbackStatusPv_vPv:
/* 8004E358 00049258  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 8004E35C 0004925C  7C 08 02 A6 */	mflr r0
/* 8004E360 00049260  90 01 00 44 */	stw r0, 0x44(r1)
/* 8004E364 00049264  39 61 00 40 */	addi r11, r1, 0x40
/* 8004E368 00049268  48 06 39 CD */	bl _savegpr_23
/* 8004E36C 0004926C  7C 7F 1B 78 */	mr r31, r3
/* 8004E370 00049270  7C 97 23 78 */	mr r23, r4
/* 8004E374 00049274  7C B8 2B 78 */	mr r24, r5
/* 8004E378 00049278  7C D9 33 78 */	mr r25, r6
/* 8004E37C 0004927C  7C FA 3B 78 */	mr r26, r7
/* 8004E380 00049280  7D 1B 43 78 */	mr r27, r8
/* 8004E384 00049284  48 0A 35 3D */	bl OSDisableInterrupts
/* 8004E388 00049288  80 1F 00 10 */	lwz r0, 0x10(r31)
/* 8004E38C 0004928C  7C 7E 1B 78 */	mr r30, r3
/* 8004E390 00049290  2C 00 00 00 */	cmpwi r0, 0
/* 8004E394 00049294  40 82 00 7C */	bne lbl_8004E410
/* 8004E398 00049298  3B A0 00 00 */	li r29, 0
/* 8004E39C 0004929C  40 82 00 5C */	bne lbl_8004E3F8
/* 8004E3A0 000492A0  80 7F 00 08 */	lwz r3, 8(r31)
/* 8004E3A4 000492A4  80 03 FF 90 */	lwz r0, -0x70(r3)
/* 8004E3A8 000492A8  3B 83 FE DC */	addi r28, r3, -292
/* 8004E3AC 000492AC  7C 00 C8 00 */	cmpw r0, r25
/* 8004E3B0 000492B0  40 81 00 0C */	ble lbl_8004E3BC
/* 8004E3B4 000492B4  3B A0 00 00 */	li r29, 0
/* 8004E3B8 000492B8  48 00 00 40 */	b lbl_8004E3F8
lbl_8004E3BC:
/* 8004E3BC 000492BC  80 9C 00 9C */	lwz r4, 0x9c(r28)
/* 8004E3C0 000492C0  7F 83 E3 78 */	mr r3, r28
/* 8004E3C4 000492C4  80 1C 00 A0 */	lwz r0, 0xa0(r28)
/* 8004E3C8 000492C8  7F A4 01 D6 */	mullw r29, r4, r0
/* 8004E3CC 000492CC  4B FF E3 59 */	bl Stop__Q44nw4r3snd6detail5VoiceFv
/* 8004E3D0 000492D0  7F 83 E3 78 */	mr r3, r28
/* 8004E3D4 000492D4  4B FF DF B5 */	bl Free__Q44nw4r3snd6detail5VoiceFv
/* 8004E3D8 000492D8  81 9C 00 A4 */	lwz r12, 0xa4(r28)
/* 8004E3DC 000492DC  2C 0C 00 00 */	cmpwi r12, 0
/* 8004E3E0 000492E0  41 82 00 18 */	beq lbl_8004E3F8
/* 8004E3E4 000492E4  7F 83 E3 78 */	mr r3, r28
/* 8004E3E8 000492E8  80 BC 00 A8 */	lwz r5, 0xa8(r28)
/* 8004E3EC 000492EC  38 80 00 02 */	li r4, 2
/* 8004E3F0 000492F0  7D 89 03 A6 */	mtctr r12
/* 8004E3F4 000492F4  4E 80 04 21 */	bctrl 
lbl_8004E3F8:
/* 8004E3F8 000492F8  2C 1D 00 00 */	cmpwi r29, 0
/* 8004E3FC 000492FC  40 82 00 14 */	bne lbl_8004E410
/* 8004E400 00049300  7F C3 F3 78 */	mr r3, r30
/* 8004E404 00049304  48 0A 34 E5 */	bl OSRestoreInterrupts
/* 8004E408 00049308  38 60 00 00 */	li r3, 0
/* 8004E40C 0004930C  48 00 00 F0 */	b lbl_8004E4FC
lbl_8004E410:
/* 8004E410 00049310  80 7F 00 14 */	lwz r3, 0x14(r31)
/* 8004E414 00049314  7E E4 BB 78 */	mr r4, r23
/* 8004E418 00049318  7F 05 C3 78 */	mr r5, r24
/* 8004E41C 0004931C  7F 26 CB 78 */	mr r6, r25
/* 8004E420 00049320  3B 83 FE DC */	addi r28, r3, -292
/* 8004E424 00049324  7F 47 D3 78 */	mr r7, r26
/* 8004E428 00049328  7F 83 E3 78 */	mr r3, r28
/* 8004E42C 0004932C  7F 68 DB 78 */	mr r8, r27
/* 8004E430 00049330  4B FF DD 1D */	bl Acquire__Q44nw4r3snd6detail5VoiceFiiiPFPQ44nw4r3snd6detail5VoiceQ54nw4r3snd6detail5Voice19VoiceCallbackStatusPv_vPv
/* 8004E434 00049334  2C 03 00 00 */	cmpwi r3, 0
/* 8004E438 00049338  40 82 00 14 */	bne lbl_8004E44C
/* 8004E43C 0004933C  7F C3 F3 78 */	mr r3, r30
/* 8004E440 00049340  48 0A 34 A9 */	bl OSRestoreInterrupts
/* 8004E444 00049344  38 60 00 00 */	li r3, 0
/* 8004E448 00049348  48 00 00 B4 */	b lbl_8004E4FC
lbl_8004E44C:
/* 8004E44C 0004934C  57 20 06 3E */	clrlwi r0, r25, 0x18
/* 8004E450 00049350  90 1C 00 B4 */	stw r0, 0xb4(r28)
/* 8004E454 00049354  48 0A 34 6D */	bl OSDisableInterrupts
/* 8004E458 00049358  3B 7C 01 24 */	addi r27, r28, 0x124
/* 8004E45C 0004935C  7C 7D 1B 78 */	mr r29, r3
/* 8004E460 00049360  7F 64 DB 78 */	mr r4, r27
/* 8004E464 00049364  38 7F 00 10 */	addi r3, r31, 0x10
/* 8004E468 00049368  4B FB 96 51 */	bl Erase__Q44nw4r2ut6detail12LinkListImplFPQ34nw4r2ut12LinkListNode
/* 8004E46C 0004936C  80 BF 00 08 */	lwz r5, 8(r31)
/* 8004E470 00049370  38 7F 00 08 */	addi r3, r31, 8
/* 8004E474 00049374  48 00 00 1C */	b lbl_8004E490
lbl_8004E478:
/* 8004E478 00049378  80 C3 00 04 */	lwz r6, 4(r3)
/* 8004E47C 0004937C  80 1C 00 B4 */	lwz r0, 0xb4(r28)
/* 8004E480 00049380  80 86 FF 90 */	lwz r4, -0x70(r6)
/* 8004E484 00049384  7C 04 00 00 */	cmpw r4, r0
/* 8004E488 00049388  40 81 00 10 */	ble lbl_8004E498
/* 8004E48C 0004938C  7C C3 33 78 */	mr r3, r6
lbl_8004E490:
/* 8004E490 00049390  7C 03 28 40 */	cmplw r3, r5
/* 8004E494 00049394  40 82 FF E4 */	bne lbl_8004E478
lbl_8004E498:
/* 8004E498 00049398  90 61 00 08 */	stw r3, 8(r1)
/* 8004E49C 0004939C  7F 65 DB 78 */	mr r5, r27
/* 8004E4A0 000493A0  38 7F 00 04 */	addi r3, r31, 4
/* 8004E4A4 000493A4  38 81 00 08 */	addi r4, r1, 8
/* 8004E4A8 000493A8  4B FB 95 E5 */	bl Insert__Q44nw4r2ut6detail12LinkListImplFQ54nw4r2ut6detail12LinkListImpl8IteratorPQ34nw4r2ut12LinkListNode
/* 8004E4AC 000493AC  7F A3 EB 78 */	mr r3, r29
/* 8004E4B0 000493B0  48 0A 34 39 */	bl OSRestoreInterrupts
/* 8004E4B4 000493B4  3B BF 00 08 */	addi r29, r31, 8
/* 8004E4B8 000493B8  48 00 00 24 */	b lbl_8004E4DC
lbl_8004E4BC:
/* 8004E4BC 000493BC  80 1B FF 90 */	lwz r0, -0x70(r27)
/* 8004E4C0 000493C0  38 7B FE DC */	addi r3, r27, -292
/* 8004E4C4 000493C4  2C 00 00 01 */	cmpwi r0, 1
/* 8004E4C8 000493C8  40 81 00 1C */	ble lbl_8004E4E4
/* 8004E4CC 000493CC  2C 00 00 FF */	cmpwi r0, 0xff
/* 8004E4D0 000493D0  41 82 00 08 */	beq lbl_8004E4D8
/* 8004E4D4 000493D4  4B FF E7 E1 */	bl UpdateVoicesPriority__Q44nw4r3snd6detail5VoiceFv
lbl_8004E4D8:
/* 8004E4D8 000493D8  83 7B 00 00 */	lwz r27, 0(r27)
lbl_8004E4DC:
/* 8004E4DC 000493DC  7C 1B E8 40 */	cmplw r27, r29
/* 8004E4E0 000493E0  40 82 FF DC */	bne lbl_8004E4BC
lbl_8004E4E4:
/* 8004E4E4 000493E4  4B FE A0 A1 */	bl GetInstance__Q44nw4r3snd6detail22DisposeCallbackManagerFv
/* 8004E4E8 000493E8  7F 84 E3 78 */	mr r4, r28
/* 8004E4EC 000493EC  4B FE A1 7D */	bl RegisterDisposeCallback__Q44nw4r3snd6detail22DisposeCallbackManagerFPQ44nw4r3snd6detail15DisposeCallback
/* 8004E4F0 000493F0  7F C3 F3 78 */	mr r3, r30
/* 8004E4F4 000493F4  48 0A 33 F5 */	bl OSRestoreInterrupts
/* 8004E4F8 000493F8  7F 83 E3 78 */	mr r3, r28
lbl_8004E4FC:
/* 8004E4FC 000493FC  39 61 00 40 */	addi r11, r1, 0x40
/* 8004E500 00049400  48 06 38 81 */	bl _restgpr_23
/* 8004E504 00049404  80 01 00 44 */	lwz r0, 0x44(r1)
/* 8004E508 00049408  7C 08 03 A6 */	mtlr r0
/* 8004E50C 0004940C  38 21 00 40 */	addi r1, r1, 0x40
/* 8004E510 00049410  4E 80 00 20 */	blr 

.global FreeVoice__Q44nw4r3snd6detail12VoiceManagerFPQ44nw4r3snd6detail5Voice
FreeVoice__Q44nw4r3snd6detail12VoiceManagerFPQ44nw4r3snd6detail5Voice:
/* 8004E514 00049414  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8004E518 00049418  7C 08 02 A6 */	mflr r0
/* 8004E51C 0004941C  90 01 00 24 */	stw r0, 0x24(r1)
/* 8004E520 00049420  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8004E524 00049424  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8004E528 00049428  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8004E52C 0004942C  7C 9D 23 78 */	mr r29, r4
/* 8004E530 00049430  93 81 00 10 */	stw r28, 0x10(r1)
/* 8004E534 00049434  7C 7C 1B 78 */	mr r28, r3
/* 8004E538 00049438  48 0A 33 89 */	bl OSDisableInterrupts
/* 8004E53C 0004943C  7C 7F 1B 78 */	mr r31, r3
/* 8004E540 00049440  4B FE A0 45 */	bl GetInstance__Q44nw4r3snd6detail22DisposeCallbackManagerFv
/* 8004E544 00049444  7F A4 EB 78 */	mr r4, r29
/* 8004E548 00049448  4B FE A1 51 */	bl UnregisterDisposeCallback__Q44nw4r3snd6detail22DisposeCallbackManagerFPQ44nw4r3snd6detail15DisposeCallback
/* 8004E54C 0004944C  48 0A 33 75 */	bl OSDisableInterrupts
/* 8004E550 00049450  3B BD 01 24 */	addi r29, r29, 0x124
/* 8004E554 00049454  7C 7E 1B 78 */	mr r30, r3
/* 8004E558 00049458  7F A4 EB 78 */	mr r4, r29
/* 8004E55C 0004945C  38 7C 00 04 */	addi r3, r28, 4
/* 8004E560 00049460  4B FB 95 59 */	bl Erase__Q44nw4r2ut6detail12LinkListImplFPQ34nw4r2ut12LinkListNode
/* 8004E564 00049464  38 1C 00 14 */	addi r0, r28, 0x14
/* 8004E568 00049468  7F A5 EB 78 */	mr r5, r29
/* 8004E56C 0004946C  90 01 00 08 */	stw r0, 8(r1)
/* 8004E570 00049470  38 7C 00 10 */	addi r3, r28, 0x10
/* 8004E574 00049474  38 81 00 08 */	addi r4, r1, 8
/* 8004E578 00049478  4B FB 95 15 */	bl Insert__Q44nw4r2ut6detail12LinkListImplFQ54nw4r2ut6detail12LinkListImpl8IteratorPQ34nw4r2ut12LinkListNode
/* 8004E57C 0004947C  7F C3 F3 78 */	mr r3, r30
/* 8004E580 00049480  48 0A 33 69 */	bl OSRestoreInterrupts
/* 8004E584 00049484  7F E3 FB 78 */	mr r3, r31
/* 8004E588 00049488  48 0A 33 61 */	bl OSRestoreInterrupts
/* 8004E58C 0004948C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8004E590 00049490  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8004E594 00049494  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8004E598 00049498  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8004E59C 0004949C  83 81 00 10 */	lwz r28, 0x10(r1)
/* 8004E5A0 000494A0  7C 08 03 A6 */	mtlr r0
/* 8004E5A4 000494A4  38 21 00 20 */	addi r1, r1, 0x20
/* 8004E5A8 000494A8  4E 80 00 20 */	blr 

.global UpdateAllVoices__Q44nw4r3snd6detail12VoiceManagerFv
UpdateAllVoices__Q44nw4r3snd6detail12VoiceManagerFv:
/* 8004E5AC 000494AC  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8004E5B0 000494B0  7C 08 02 A6 */	mflr r0
/* 8004E5B4 000494B4  90 01 00 24 */	stw r0, 0x24(r1)
/* 8004E5B8 000494B8  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8004E5BC 000494BC  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8004E5C0 000494C0  3B C3 00 08 */	addi r30, r3, 8
/* 8004E5C4 000494C4  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8004E5C8 000494C8  7C 7D 1B 78 */	mr r29, r3
/* 8004E5CC 000494CC  83 E3 00 08 */	lwz r31, 8(r3)
/* 8004E5D0 000494D0  48 00 00 14 */	b lbl_8004E5E4
lbl_8004E5D4:
/* 8004E5D4 000494D4  7F E3 FB 78 */	mr r3, r31
/* 8004E5D8 000494D8  83 FF 00 00 */	lwz r31, 0(r31)
/* 8004E5DC 000494DC  38 63 FE DC */	addi r3, r3, -292
/* 8004E5E0 000494E0  4B FF D5 45 */	bl StopFinished__Q44nw4r3snd6detail5VoiceFv
lbl_8004E5E4:
/* 8004E5E4 000494E4  7C 1F F0 40 */	cmplw r31, r30
/* 8004E5E8 000494E8  40 82 FF EC */	bne lbl_8004E5D4
/* 8004E5EC 000494EC  83 DD 00 08 */	lwz r30, 8(r29)
/* 8004E5F0 000494F0  3B FD 00 08 */	addi r31, r29, 8
/* 8004E5F4 000494F4  48 00 00 14 */	b lbl_8004E608
lbl_8004E5F8:
/* 8004E5F8 000494F8  7F C3 F3 78 */	mr r3, r30
/* 8004E5FC 000494FC  83 DE 00 00 */	lwz r30, 0(r30)
/* 8004E600 00049500  38 63 FE DC */	addi r3, r3, -292
/* 8004E604 00049504  4B FF D5 BD */	bl Calc__Q44nw4r3snd6detail5VoiceFv
lbl_8004E608:
/* 8004E608 00049508  7C 1E F8 40 */	cmplw r30, r31
/* 8004E60C 0004950C  40 82 FF EC */	bne lbl_8004E5F8
/* 8004E610 00049510  48 0A 32 B1 */	bl OSDisableInterrupts
/* 8004E614 00049514  87 FD 00 08 */	lwzu r31, 8(r29)
/* 8004E618 00049518  7C 7E 1B 78 */	mr r30, r3
/* 8004E61C 0004951C  48 00 00 14 */	b lbl_8004E630
lbl_8004E620:
/* 8004E620 00049520  7F E3 FB 78 */	mr r3, r31
/* 8004E624 00049524  83 FF 00 00 */	lwz r31, 0(r31)
/* 8004E628 00049528  38 63 FE DC */	addi r3, r3, -292
/* 8004E62C 0004952C  4B FF D7 E5 */	bl Update__Q44nw4r3snd6detail5VoiceFv
lbl_8004E630:
/* 8004E630 00049530  7C 1F E8 40 */	cmplw r31, r29
/* 8004E634 00049534  40 82 FF EC */	bne lbl_8004E620
/* 8004E638 00049538  7F C3 F3 78 */	mr r3, r30
/* 8004E63C 0004953C  48 0A 32 AD */	bl OSRestoreInterrupts
/* 8004E640 00049540  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8004E644 00049544  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8004E648 00049548  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8004E64C 0004954C  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8004E650 00049550  7C 08 03 A6 */	mtlr r0
/* 8004E654 00049554  38 21 00 20 */	addi r1, r1, 0x20
/* 8004E658 00049558  4E 80 00 20 */	blr 

.global NotifyVoiceUpdate__Q44nw4r3snd6detail12VoiceManagerFv
NotifyVoiceUpdate__Q44nw4r3snd6detail12VoiceManagerFv:
/* 8004E65C 0004955C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8004E660 00049560  7C 08 02 A6 */	mflr r0
/* 8004E664 00049564  90 01 00 24 */	stw r0, 0x24(r1)
/* 8004E668 00049568  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8004E66C 0004956C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8004E670 00049570  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8004E674 00049574  7C 7D 1B 78 */	mr r29, r3
/* 8004E678 00049578  48 0A 32 49 */	bl OSDisableInterrupts
/* 8004E67C 0004957C  87 DD 00 08 */	lwzu r30, 8(r29)
/* 8004E680 00049580  7C 7F 1B 78 */	mr r31, r3
/* 8004E684 00049584  48 00 00 14 */	b lbl_8004E698
lbl_8004E688:
/* 8004E688 00049588  7F C3 F3 78 */	mr r3, r30
/* 8004E68C 0004958C  83 DE 00 00 */	lwz r30, 0(r30)
/* 8004E690 00049590  38 63 FE DC */	addi r3, r3, -292
/* 8004E694 00049594  4B FF EB 8D */	bl ResetDelta__Q44nw4r3snd6detail5VoiceFv
lbl_8004E698:
/* 8004E698 00049598  7C 1E E8 40 */	cmplw r30, r29
/* 8004E69C 0004959C  40 82 FF EC */	bne lbl_8004E688
/* 8004E6A0 000495A0  7F E3 FB 78 */	mr r3, r31
/* 8004E6A4 000495A4  48 0A 32 45 */	bl OSRestoreInterrupts
/* 8004E6A8 000495A8  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8004E6AC 000495AC  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8004E6B0 000495B0  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8004E6B4 000495B4  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8004E6B8 000495B8  7C 08 03 A6 */	mtlr r0
/* 8004E6BC 000495BC  38 21 00 20 */	addi r1, r1, 0x20
/* 8004E6C0 000495C0  4E 80 00 20 */	blr 

.global ChangeVoicePriority__Q44nw4r3snd6detail12VoiceManagerFPQ44nw4r3snd6detail5Voice
ChangeVoicePriority__Q44nw4r3snd6detail12VoiceManagerFPQ44nw4r3snd6detail5Voice:
/* 8004E6C4 000495C4  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8004E6C8 000495C8  7C 08 02 A6 */	mflr r0
/* 8004E6CC 000495CC  90 01 00 34 */	stw r0, 0x34(r1)
/* 8004E6D0 000495D0  39 61 00 30 */	addi r11, r1, 0x30
/* 8004E6D4 000495D4  48 06 36 71 */	bl _savegpr_27
/* 8004E6D8 000495D8  7C 7B 1B 78 */	mr r27, r3
/* 8004E6DC 000495DC  7C 9C 23 78 */	mr r28, r4
/* 8004E6E0 000495E0  48 0A 31 E1 */	bl OSDisableInterrupts
/* 8004E6E4 000495E4  7C 7F 1B 78 */	mr r31, r3
/* 8004E6E8 000495E8  48 0A 31 D9 */	bl OSDisableInterrupts
/* 8004E6EC 000495EC  3B BC 01 24 */	addi r29, r28, 0x124
/* 8004E6F0 000495F0  7C 7E 1B 78 */	mr r30, r3
/* 8004E6F4 000495F4  7F A4 EB 78 */	mr r4, r29
/* 8004E6F8 000495F8  38 7B 00 04 */	addi r3, r27, 4
/* 8004E6FC 000495FC  4B FB 93 BD */	bl Erase__Q44nw4r2ut6detail12LinkListImplFPQ34nw4r2ut12LinkListNode
/* 8004E700 00049600  38 1B 00 14 */	addi r0, r27, 0x14
/* 8004E704 00049604  7F A5 EB 78 */	mr r5, r29
/* 8004E708 00049608  90 01 00 0C */	stw r0, 0xc(r1)
/* 8004E70C 0004960C  38 7B 00 10 */	addi r3, r27, 0x10
/* 8004E710 00049610  38 81 00 0C */	addi r4, r1, 0xc
/* 8004E714 00049614  4B FB 93 79 */	bl Insert__Q44nw4r2ut6detail12LinkListImplFQ54nw4r2ut6detail12LinkListImpl8IteratorPQ34nw4r2ut12LinkListNode
/* 8004E718 00049618  7F C3 F3 78 */	mr r3, r30
/* 8004E71C 0004961C  48 0A 31 CD */	bl OSRestoreInterrupts
/* 8004E720 00049620  48 0A 31 A1 */	bl OSDisableInterrupts
/* 8004E724 00049624  7C 7E 1B 78 */	mr r30, r3
/* 8004E728 00049628  7F A4 EB 78 */	mr r4, r29
/* 8004E72C 0004962C  38 7B 00 10 */	addi r3, r27, 0x10
/* 8004E730 00049630  4B FB 93 89 */	bl Erase__Q44nw4r2ut6detail12LinkListImplFPQ34nw4r2ut12LinkListNode
/* 8004E734 00049634  80 BB 00 08 */	lwz r5, 8(r27)
/* 8004E738 00049638  38 7B 00 08 */	addi r3, r27, 8
/* 8004E73C 0004963C  48 00 00 1C */	b lbl_8004E758
lbl_8004E740:
/* 8004E740 00049640  80 C3 00 04 */	lwz r6, 4(r3)
/* 8004E744 00049644  80 1C 00 B4 */	lwz r0, 0xb4(r28)
/* 8004E748 00049648  80 86 FF 90 */	lwz r4, -0x70(r6)
/* 8004E74C 0004964C  7C 04 00 00 */	cmpw r4, r0
/* 8004E750 00049650  40 81 00 10 */	ble lbl_8004E760
/* 8004E754 00049654  7C C3 33 78 */	mr r3, r6
lbl_8004E758:
/* 8004E758 00049658  7C 03 28 40 */	cmplw r3, r5
/* 8004E75C 0004965C  40 82 FF E4 */	bne lbl_8004E740
lbl_8004E760:
/* 8004E760 00049660  90 61 00 08 */	stw r3, 8(r1)
/* 8004E764 00049664  7F A5 EB 78 */	mr r5, r29
/* 8004E768 00049668  38 7B 00 04 */	addi r3, r27, 4
/* 8004E76C 0004966C  38 81 00 08 */	addi r4, r1, 8
/* 8004E770 00049670  4B FB 93 1D */	bl Insert__Q44nw4r2ut6detail12LinkListImplFQ54nw4r2ut6detail12LinkListImpl8IteratorPQ34nw4r2ut12LinkListNode
/* 8004E774 00049674  7F C3 F3 78 */	mr r3, r30
/* 8004E778 00049678  48 0A 31 71 */	bl OSRestoreInterrupts
/* 8004E77C 0004967C  3B DB 00 08 */	addi r30, r27, 8
/* 8004E780 00049680  48 00 00 24 */	b lbl_8004E7A4
lbl_8004E784:
/* 8004E784 00049684  80 1D FF 90 */	lwz r0, -0x70(r29)
/* 8004E788 00049688  38 7D FE DC */	addi r3, r29, -292
/* 8004E78C 0004968C  2C 00 00 01 */	cmpwi r0, 1
/* 8004E790 00049690  40 81 00 1C */	ble lbl_8004E7AC
/* 8004E794 00049694  2C 00 00 FF */	cmpwi r0, 0xff
/* 8004E798 00049698  41 82 00 08 */	beq lbl_8004E7A0
/* 8004E79C 0004969C  4B FF E5 19 */	bl UpdateVoicesPriority__Q44nw4r3snd6detail5VoiceFv
lbl_8004E7A0:
/* 8004E7A0 000496A0  83 BD 00 00 */	lwz r29, 0(r29)
lbl_8004E7A4:
/* 8004E7A4 000496A4  7C 1D F0 40 */	cmplw r29, r30
/* 8004E7A8 000496A8  40 82 FF DC */	bne lbl_8004E784
lbl_8004E7AC:
/* 8004E7AC 000496AC  7F E3 FB 78 */	mr r3, r31
/* 8004E7B0 000496B0  48 0A 31 39 */	bl OSRestoreInterrupts
/* 8004E7B4 000496B4  39 61 00 30 */	addi r11, r1, 0x30
/* 8004E7B8 000496B8  48 06 35 D9 */	bl _restgpr_27
/* 8004E7BC 000496BC  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8004E7C0 000496C0  7C 08 03 A6 */	mtlr r0
/* 8004E7C4 000496C4  38 21 00 30 */	addi r1, r1, 0x30
/* 8004E7C8 000496C8  4E 80 00 20 */	blr 

.global UpdateAllVoicesSync__Q44nw4r3snd6detail12VoiceManagerFUl
UpdateAllVoicesSync__Q44nw4r3snd6detail12VoiceManagerFUl:
/* 8004E7CC 000496CC  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8004E7D0 000496D0  7C 08 02 A6 */	mflr r0
/* 8004E7D4 000496D4  90 01 00 14 */	stw r0, 0x14(r1)
/* 8004E7D8 000496D8  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8004E7DC 000496DC  7C 9F 23 78 */	mr r31, r4
/* 8004E7E0 000496E0  93 C1 00 08 */	stw r30, 8(r1)
/* 8004E7E4 000496E4  7C 7E 1B 78 */	mr r30, r3
/* 8004E7E8 000496E8  48 0A 30 D9 */	bl OSDisableInterrupts
/* 8004E7EC 000496EC  80 9E 00 08 */	lwz r4, 8(r30)
/* 8004E7F0 000496F0  38 1E 00 08 */	addi r0, r30, 8
/* 8004E7F4 000496F4  48 00 00 24 */	b lbl_8004E818
lbl_8004E7F8:
/* 8004E7F8 000496F8  7C 86 23 78 */	mr r6, r4
/* 8004E7FC 000496FC  80 84 00 00 */	lwz r4, 0(r4)
/* 8004E800 00049700  88 A6 FF 88 */	lbz r5, -0x78(r6)
/* 8004E804 00049704  2C 05 00 00 */	cmpwi r5, 0
/* 8004E808 00049708  41 82 00 10 */	beq lbl_8004E818
/* 8004E80C 0004970C  88 A6 FF 8D */	lbz r5, -0x73(r6)
/* 8004E810 00049710  7C A5 FB 78 */	or r5, r5, r31
/* 8004E814 00049714  98 A6 FF 8D */	stb r5, -0x73(r6)
lbl_8004E818:
/* 8004E818 00049718  7C 04 00 40 */	cmplw r4, r0
/* 8004E81C 0004971C  40 82 FF DC */	bne lbl_8004E7F8
/* 8004E820 00049720  48 0A 30 C9 */	bl OSRestoreInterrupts
/* 8004E824 00049724  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8004E828 00049728  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8004E82C 0004972C  83 C1 00 08 */	lwz r30, 8(r1)
/* 8004E830 00049730  7C 08 03 A6 */	mtlr r0
/* 8004E834 00049734  38 21 00 10 */	addi r1, r1, 0x10
/* 8004E838 00049738  4E 80 00 20 */	blr 
