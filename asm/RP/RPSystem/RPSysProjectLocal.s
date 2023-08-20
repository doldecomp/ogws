.include "macros.inc"

.section .sbss, "wa"
.balign 0x8
.global sInstance__17RPSysProjectLocal
sInstance__17RPSysProjectLocal:
	.skip 0x4

.section .rodata, "a"
.balign 0x8
.global strings_80382450
strings_80382450:
    .string "EN/"
    .string "FR/"
    .string "GE/"
    .string "IT/"
    .string "SP/"
    .string "JP/"
    .string "US/"

.section .data, "wa"
.balign 0x8
.global jtbl_803B97D8
jtbl_803B97D8:
	.incbin "baserom.dol", 0x3B58D8, 0x20
.global __vt__17RPSysProjectLocal
__vt__17RPSysProjectLocal:
    .long 0
    .long 0
    .long __dt__17RPSysProjectLocalFv

.section .text, "ax"
.global setLanguage__17RPSysProjectLocalFQ217RPSysProjectLocal7ERegion
setLanguage__17RPSysProjectLocalFQ217RPSysProjectLocal7ERegion:
/* 80186234 00181134  90 83 00 14 */	stw r4, 0x14(r3)
/* 80186238 00181138  4E 80 00 20 */	blr 

.global setLocale__17RPSysProjectLocalFQ217RPSysProjectLocal7ERegion
setLocale__17RPSysProjectLocalFQ217RPSysProjectLocal7ERegion:
/* 8018623C 0018113C  90 83 00 10 */	stw r4, 0x10(r3)
/* 80186240 00181140  4E 80 00 20 */	blr 

.global appendLocalDirectory__17RPSysProjectLocalFPcPCc
appendLocalDirectory__17RPSysProjectLocalFPcPCc:
/* 80186244 00181144  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80186248 00181148  7C 08 02 A6 */	mflr r0
/* 8018624C 0018114C  90 01 00 14 */	stw r0, 0x14(r1)
/* 80186250 00181150  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80186254 00181154  7C BF 2B 78 */	mr r31, r5
/* 80186258 00181158  93 C1 00 08 */	stw r30, 8(r1)
/* 8018625C 0018115C  7C 9E 23 78 */	mr r30, r4
/* 80186260 00181160  80 03 00 10 */	lwz r0, 0x10(r3)
/* 80186264 00181164  28 00 00 07 */	cmplwi r0, 7
/* 80186268 00181168  41 81 00 D0 */	bgt lbl_80186338
/* 8018626C 0018116C  3C 60 80 3C */	lis r3, jtbl_803B97D8@ha
/* 80186270 00181170  54 00 10 3A */	slwi r0, r0, 2
/* 80186274 00181174  38 63 97 D8 */	addi r3, r3, jtbl_803B97D8@l
/* 80186278 00181178  7C 63 00 2E */	lwzx r3, r3, r0
/* 8018627C 0018117C  7C 69 03 A6 */	mtctr r3
/* 80186280 00181180  4E 80 04 20 */	bctr 
/* 80186284 00181184  3C 80 80 38 */	lis r4, strings_80382450@ha
/* 80186288 00181188  7F C3 F3 78 */	mr r3, r30
/* 8018628C 0018118C  38 84 24 50 */	addi r4, r4, strings_80382450@l
/* 80186290 00181190  4B F3 2A A9 */	bl strcat
/* 80186294 00181194  48 00 00 A4 */	b lbl_80186338
/* 80186298 00181198  3C 80 80 38 */	lis r4, strings_80382450@ha
/* 8018629C 0018119C  7F C3 F3 78 */	mr r3, r30
/* 801862A0 001811A0  38 84 24 50 */	addi r4, r4, strings_80382450@l
/* 801862A4 001811A4  38 84 00 04 */	addi r4, r4, 4
/* 801862A8 001811A8  4B F3 2A 91 */	bl strcat
/* 801862AC 001811AC  48 00 00 8C */	b lbl_80186338
/* 801862B0 001811B0  3C 80 80 38 */	lis r4, strings_80382450@ha
/* 801862B4 001811B4  7F C3 F3 78 */	mr r3, r30
/* 801862B8 001811B8  38 84 24 50 */	addi r4, r4, strings_80382450@l
/* 801862BC 001811BC  38 84 00 08 */	addi r4, r4, 8
/* 801862C0 001811C0  4B F3 2A 79 */	bl strcat
/* 801862C4 001811C4  48 00 00 74 */	b lbl_80186338
/* 801862C8 001811C8  3C 80 80 38 */	lis r4, strings_80382450@ha
/* 801862CC 001811CC  7F C3 F3 78 */	mr r3, r30
/* 801862D0 001811D0  38 84 24 50 */	addi r4, r4, strings_80382450@l
/* 801862D4 001811D4  38 84 00 0C */	addi r4, r4, 0xc
/* 801862D8 001811D8  4B F3 2A 61 */	bl strcat
/* 801862DC 001811DC  48 00 00 5C */	b lbl_80186338
/* 801862E0 001811E0  3C 80 80 38 */	lis r4, strings_80382450@ha
/* 801862E4 001811E4  7F C3 F3 78 */	mr r3, r30
/* 801862E8 001811E8  38 84 24 50 */	addi r4, r4, strings_80382450@l
/* 801862EC 001811EC  38 84 00 10 */	addi r4, r4, 0x10
/* 801862F0 001811F0  4B F3 2A 49 */	bl strcat
/* 801862F4 001811F4  48 00 00 44 */	b lbl_80186338
/* 801862F8 001811F8  3C 80 80 38 */	lis r4, strings_80382450@ha
/* 801862FC 001811FC  7F C3 F3 78 */	mr r3, r30
/* 80186300 00181200  38 84 24 50 */	addi r4, r4, strings_80382450@l
/* 80186304 00181204  4B F3 2A 35 */	bl strcat
/* 80186308 00181208  48 00 00 30 */	b lbl_80186338
/* 8018630C 0018120C  3C 80 80 38 */	lis r4, strings_80382450@ha
/* 80186310 00181210  7F C3 F3 78 */	mr r3, r30
/* 80186314 00181214  38 84 24 50 */	addi r4, r4, strings_80382450@l
/* 80186318 00181218  38 84 00 14 */	addi r4, r4, 0x14
/* 8018631C 0018121C  4B F3 2A 1D */	bl strcat
/* 80186320 00181220  48 00 00 18 */	b lbl_80186338
/* 80186324 00181224  3C 80 80 38 */	lis r4, strings_80382450@ha
/* 80186328 00181228  7F C3 F3 78 */	mr r3, r30
/* 8018632C 0018122C  38 84 24 50 */	addi r4, r4, strings_80382450@l
/* 80186330 00181230  38 84 00 18 */	addi r4, r4, 0x18
/* 80186334 00181234  4B F3 2A 05 */	bl strcat
lbl_80186338:
/* 80186338 00181238  2C 1F 00 00 */	cmpwi r31, 0
/* 8018633C 0018123C  41 82 00 10 */	beq lbl_8018634C
/* 80186340 00181240  7F C3 F3 78 */	mr r3, r30
/* 80186344 00181244  7F E4 FB 78 */	mr r4, r31
/* 80186348 00181248  4B F3 29 F1 */	bl strcat
lbl_8018634C:
/* 8018634C 0018124C  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80186350 00181250  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80186354 00181254  83 C1 00 08 */	lwz r30, 8(r1)
/* 80186358 00181258  7C 08 03 A6 */	mtlr r0
/* 8018635C 0018125C  38 21 00 10 */	addi r1, r1, 0x10
/* 80186360 00181260  4E 80 00 20 */	blr 

.global __dt__17RPSysProjectLocalFv
__dt__17RPSysProjectLocalFv:
/* 80186364 00181264  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80186368 00181268  7C 08 02 A6 */	mflr r0
/* 8018636C 0018126C  2C 03 00 00 */	cmpwi r3, 0
/* 80186370 00181270  90 01 00 14 */	stw r0, 0x14(r1)
/* 80186374 00181274  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80186378 00181278  7C 7F 1B 78 */	mr r31, r3
/* 8018637C 0018127C  41 82 00 10 */	beq lbl_8018638C
/* 80186380 00181280  2C 04 00 00 */	cmpwi r4, 0
/* 80186384 00181284  40 81 00 08 */	ble lbl_8018638C
/* 80186388 00181288  4B F1 CE FD */	bl __dl__FPv
lbl_8018638C:
/* 8018638C 0018128C  7F E3 FB 78 */	mr r3, r31
/* 80186390 00181290  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80186394 00181294  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80186398 00181298  7C 08 03 A6 */	mtlr r0
/* 8018639C 0018129C  38 21 00 10 */	addi r1, r1, 0x10
/* 801863A0 001812A0  4E 80 00 20 */	blr 

.global CreateInstance__17RPSysProjectLocalFPQ23EGG4Heap
CreateInstance__17RPSysProjectLocalFPQ23EGG4Heap:
/* 801863A4 001812A4  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 801863A8 001812A8  7C 08 02 A6 */	mflr r0
/* 801863AC 001812AC  90 01 00 14 */	stw r0, 0x14(r1)
/* 801863B0 001812B0  93 E1 00 0C */	stw r31, 0xc(r1)
/* 801863B4 001812B4  7C 7F 1B 78 */	mr r31, r3
/* 801863B8 001812B8  80 0D A1 60 */	lwz r0, sInstance__17RPSysProjectLocal-_SDA_BASE_(r13)
/* 801863BC 001812BC  2C 00 00 00 */	cmpwi r0, 0
/* 801863C0 001812C0  40 82 00 58 */	bne lbl_80186418
/* 801863C4 001812C4  7F E4 FB 78 */	mr r4, r31
/* 801863C8 001812C8  38 60 00 20 */	li r3, 0x20
/* 801863CC 001812CC  38 A0 00 04 */	li r5, 4
/* 801863D0 001812D0  4B F1 CE 81 */	bl __nw__FUlPQ23EGG4Heapi
/* 801863D4 001812D4  2C 03 00 00 */	cmpwi r3, 0
/* 801863D8 001812D8  41 82 00 38 */	beq lbl_80186410
/* 801863DC 001812DC  3C C0 80 3C */	lis r6, __vt__17RPSysProjectLocal@ha
/* 801863E0 001812E0  38 A0 00 01 */	li r5, 1
/* 801863E4 001812E4  38 C6 97 F8 */	addi r6, r6, __vt__17RPSysProjectLocal@l
/* 801863E8 001812E8  38 80 00 00 */	li r4, 0
/* 801863EC 001812EC  90 C3 00 00 */	stw r6, 0(r3)
/* 801863F0 001812F0  38 00 00 07 */	li r0, 7
/* 801863F4 001812F4  93 E3 00 04 */	stw r31, 4(r3)
/* 801863F8 001812F8  90 A3 00 08 */	stw r5, 8(r3)
/* 801863FC 001812FC  90 83 00 0C */	stw r4, 0xc(r3)
/* 80186400 00181300  90 03 00 10 */	stw r0, 0x10(r3)
/* 80186404 00181304  90 03 00 14 */	stw r0, 0x14(r3)
/* 80186408 00181308  90 83 00 18 */	stw r4, 0x18(r3)
/* 8018640C 0018130C  90 83 00 1C */	stw r4, 0x1c(r3)
lbl_80186410:
/* 80186410 00181310  90 6D A1 60 */	stw r3, sInstance__17RPSysProjectLocal-_SDA_BASE_(r13)
/* 80186414 00181314  48 00 00 08 */	b lbl_8018641C
lbl_80186418:
/* 80186418 00181318  38 60 00 00 */	li r3, 0
lbl_8018641C:
/* 8018641C 0018131C  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80186420 00181320  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80186424 00181324  7C 08 03 A6 */	mtlr r0
/* 80186428 00181328  38 21 00 10 */	addi r1, r1, 0x10
/* 8018642C 0018132C  4E 80 00 20 */	blr 
