.include "macros.inc"

.section .text, "ax"  # 0x800076E0 - 0x80355080 

.global detail_StartSound__Q34nw4r3snd14SoundStartableFPQ34nw4r3snd11SoundHandleUlPQ54nw4r3snd6detail10BasicSound14AmbientArgInfoPQ44nw4r3snd6detail19ExternalSoundPlayerPCQ44nw4r3snd14SoundStartable9StartInfo
detail_StartSound__Q34nw4r3snd14SoundStartableFPQ34nw4r3snd11SoundHandleUlPQ54nw4r3snd6detail10BasicSound14AmbientArgInfoPQ44nw4r3snd6detail19ExternalSoundPlayerPCQ44nw4r3snd14SoundStartable9StartInfo:
/* 80047400 00042300  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80047404 00042304  7C 08 02 A6 */	mflr r0
/* 80047408 00042308  7D 09 43 78 */	mr r9, r8
/* 8004740C 0004230C  39 00 00 00 */	li r8, 0
/* 80047410 00042310  90 01 00 14 */	stw r0, 0x14(r1)
/* 80047414 00042314  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80047418 00042318  7C 9F 23 78 */	mr r31, r4
/* 8004741C 0004231C  81 83 00 00 */	lwz r12, 0(r3)
/* 80047420 00042320  81 8C 00 0C */	lwz r12, 0xc(r12)
/* 80047424 00042324  7D 89 03 A6 */	mtctr r12
/* 80047428 00042328  4E 80 04 21 */	bctrl 
/* 8004742C 0004232C  2C 03 00 00 */	cmpwi r3, 0
/* 80047430 00042330  41 82 00 08 */	beq lbl_80047438
/* 80047434 00042334  48 00 00 24 */	b lbl_80047458
lbl_80047438:
/* 80047438 00042338  80 7F 00 00 */	lwz r3, 0(r31)
/* 8004743C 0004233C  2C 03 00 00 */	cmpwi r3, 0
/* 80047440 00042340  41 82 00 14 */	beq lbl_80047454
/* 80047444 00042344  81 83 00 00 */	lwz r12, 0(r3)
/* 80047448 00042348  81 8C 00 14 */	lwz r12, 0x14(r12)
/* 8004744C 0004234C  7D 89 03 A6 */	mtctr r12
/* 80047450 00042350  4E 80 04 21 */	bctrl 
lbl_80047454:
/* 80047454 00042354  38 60 00 00 */	li r3, 0
lbl_80047458:
/* 80047458 00042358  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8004745C 0004235C  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80047460 00042360  7C 08 03 A6 */	mtlr r0
/* 80047464 00042364  38 21 00 10 */	addi r1, r1, 0x10
/* 80047468 00042368  4E 80 00 20 */	blr 

.global detail_HoldSound__Q34nw4r3snd14SoundStartableFPQ34nw4r3snd11SoundHandleUlPQ54nw4r3snd6detail10BasicSound14AmbientArgInfoPQ44nw4r3snd6detail19ExternalSoundPlayerPCQ44nw4r3snd14SoundStartable9StartInfo
detail_HoldSound__Q34nw4r3snd14SoundStartableFPQ34nw4r3snd11SoundHandleUlPQ54nw4r3snd6detail10BasicSound14AmbientArgInfoPQ44nw4r3snd6detail19ExternalSoundPlayerPCQ44nw4r3snd14SoundStartable9StartInfo:
/* 8004746C 0004236C  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80047470 00042370  7C 08 02 A6 */	mflr r0
/* 80047474 00042374  90 01 00 14 */	stw r0, 0x14(r1)
/* 80047478 00042378  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8004747C 0004237C  7C 9F 23 78 */	mr r31, r4
/* 80047480 00042380  81 24 00 00 */	lwz r9, 0(r4)
/* 80047484 00042384  2C 09 00 00 */	cmpwi r9, 0
/* 80047488 00042388  41 82 00 3C */	beq lbl_800474C4
/* 8004748C 0004238C  41 82 00 0C */	beq lbl_80047498
/* 80047490 00042390  80 09 00 78 */	lwz r0, 0x78(r9)
/* 80047494 00042394  48 00 00 08 */	b lbl_8004749C
lbl_80047498:
/* 80047498 00042398  38 00 FF FF */	li r0, -1
lbl_8004749C:
/* 8004749C 0004239C  7C 05 00 40 */	cmplw r5, r0
/* 800474A0 000423A0  40 82 00 24 */	bne lbl_800474C4
/* 800474A4 000423A4  81 89 00 00 */	lwz r12, 0(r9)
/* 800474A8 000423A8  7D 23 4B 78 */	mr r3, r9
/* 800474AC 000423AC  38 80 00 01 */	li r4, 1
/* 800474B0 000423B0  81 8C 00 20 */	lwz r12, 0x20(r12)
/* 800474B4 000423B4  7D 89 03 A6 */	mtctr r12
/* 800474B8 000423B8  4E 80 04 21 */	bctrl 
/* 800474BC 000423BC  38 60 00 00 */	li r3, 0
/* 800474C0 000423C0  48 00 00 64 */	b lbl_80047524
lbl_800474C4:
/* 800474C4 000423C4  81 83 00 00 */	lwz r12, 0(r3)
/* 800474C8 000423C8  7D 09 43 78 */	mr r9, r8
/* 800474CC 000423CC  7F E4 FB 78 */	mr r4, r31
/* 800474D0 000423D0  39 00 00 01 */	li r8, 1
/* 800474D4 000423D4  81 8C 00 0C */	lwz r12, 0xc(r12)
/* 800474D8 000423D8  7D 89 03 A6 */	mtctr r12
/* 800474DC 000423DC  4E 80 04 21 */	bctrl 
/* 800474E0 000423E0  2C 03 00 00 */	cmpwi r3, 0
/* 800474E4 000423E4  41 82 00 08 */	beq lbl_800474EC
/* 800474E8 000423E8  48 00 00 3C */	b lbl_80047524
lbl_800474EC:
/* 800474EC 000423EC  80 7F 00 00 */	lwz r3, 0(r31)
/* 800474F0 000423F0  2C 03 00 00 */	cmpwi r3, 0
/* 800474F4 000423F4  41 82 00 14 */	beq lbl_80047508
/* 800474F8 000423F8  81 83 00 00 */	lwz r12, 0(r3)
/* 800474FC 000423FC  81 8C 00 14 */	lwz r12, 0x14(r12)
/* 80047500 00042400  7D 89 03 A6 */	mtctr r12
/* 80047504 00042404  4E 80 04 21 */	bctrl 
lbl_80047508:
/* 80047508 00042408  80 7F 00 00 */	lwz r3, 0(r31)
/* 8004750C 0004240C  38 80 00 01 */	li r4, 1
/* 80047510 00042410  81 83 00 00 */	lwz r12, 0(r3)
/* 80047514 00042414  81 8C 00 20 */	lwz r12, 0x20(r12)
/* 80047518 00042418  7D 89 03 A6 */	mtctr r12
/* 8004751C 0004241C  4E 80 04 21 */	bctrl 
/* 80047520 00042420  38 60 00 00 */	li r3, 0
lbl_80047524:
/* 80047524 00042424  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80047528 00042428  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8004752C 0004242C  7C 08 03 A6 */	mtlr r0
/* 80047530 00042430  38 21 00 10 */	addi r1, r1, 0x10
/* 80047534 00042434  4E 80 00 20 */	blr 

.global detail_PrepareSound__Q34nw4r3snd14SoundStartableFPQ34nw4r3snd11SoundHandleUlPQ54nw4r3snd6detail10BasicSound14AmbientArgInfoPQ44nw4r3snd6detail19ExternalSoundPlayerPCQ44nw4r3snd14SoundStartable9StartInfo
detail_PrepareSound__Q34nw4r3snd14SoundStartableFPQ34nw4r3snd11SoundHandleUlPQ54nw4r3snd6detail10BasicSound14AmbientArgInfoPQ44nw4r3snd6detail19ExternalSoundPlayerPCQ44nw4r3snd14SoundStartable9StartInfo:
/* 80047538 00042438  81 83 00 00 */	lwz r12, 0(r3)
/* 8004753C 0004243C  7D 09 43 78 */	mr r9, r8
/* 80047540 00042440  39 00 00 00 */	li r8, 0
/* 80047544 00042444  81 8C 00 0C */	lwz r12, 0xc(r12)
/* 80047548 00042448  7D 89 03 A6 */	mtctr r12
/* 8004754C 0004244C  4E 80 04 20 */	bctr 
