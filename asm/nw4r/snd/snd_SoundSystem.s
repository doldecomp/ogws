.include "macros.inc"

.section .ctors, "a"
.4byte __sinit_$$3snd_SoundSystem_cpp

.section .data, "wa"
$$24063:
.string "<< NW4R    - SND \tfinal   build: Jun  8 2007 11:17:15 (0x4199_60831) >>"

.section .bss, "wa"
.global lbl_803D0BB8
lbl_803D0BB8:
	.skip 0x8 # Contiguous with SeqPlayer::mLocalVariables, never seems to be used though
.global lbl_803D0BC0
lbl_803D0BC0:
	.skip 0x10
.global lbl_803D0BD0
lbl_803D0BD0:
	.skip 0x330
.global lbl_803D0F00
lbl_803D0F00:
	.skip 0x16970

.section .sdata, "wa"
.global NW4R_SND_Version_
NW4R_SND_Version_:
	.long $$24063
.balign 0x8

.section .sbss, "wa"
.global lbl_804BEB08
lbl_804BEB08:
	.skip 0x8

.section .text, "ax"  # 0x800076E0 - 0x80355080 
.global InitSoundSystem__Q34nw4r3snd11SoundSystemFll
InitSoundSystem__Q34nw4r3snd11SoundSystemFll:
/* 80047550 00042450  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80047554 00042454  7C 08 02 A6 */	mflr r0
/* 80047558 00042458  90 01 00 24 */	stw r0, 0x24(r1)
/* 8004755C 0004245C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80047560 00042460  7C 9F 23 78 */	mr r31, r4
/* 80047564 00042464  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80047568 00042468  7C 7E 1B 78 */	mr r30, r3
/* 8004756C 0004246C  80 6D 80 88 */	lwz r3, NW4R_SND_Version_-_SDA_BASE_(r13)
/* 80047570 00042470  48 0A 5A D1 */	bl OSRegisterVersion
/* 80047574 00042474  38 00 40 00 */	li r0, 0x4000
/* 80047578 00042478  3C 80 80 3D */	lis r4, lbl_803D0F00@ha
/* 8004757C 0004247C  3C A0 00 01 */	lis r5, 0x0001696C@ha
/* 80047580 00042480  90 01 00 0C */	stw r0, 0xc(r1)
/* 80047584 00042484  38 61 00 08 */	addi r3, r1, 8
/* 80047588 00042488  38 84 0F 00 */	addi r4, r4, lbl_803D0F00@l
/* 8004758C 0004248C  90 01 00 14 */	stw r0, 0x14(r1)
/* 80047590 00042490  38 A5 69 6C */	addi r5, r5, 0x0001696C@l
/* 80047594 00042494  93 C1 00 08 */	stw r30, 8(r1)
/* 80047598 00042498  93 E1 00 10 */	stw r31, 0x10(r1)
/* 8004759C 0004249C  48 00 00 81 */	bl InitSoundSystem__Q34nw4r3snd11SoundSystemFRCQ44nw4r3snd11SoundSystem16SoundSystemParamPvUl
/* 800475A0 000424A0  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800475A4 000424A4  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800475A8 000424A8  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 800475AC 000424AC  7C 08 03 A6 */	mtlr r0
/* 800475B0 000424B0  38 21 00 20 */	addi r1, r1, 0x20
/* 800475B4 000424B4  4E 80 00 20 */	blr 

.global GetRequiredMemSize__Q34nw4r3snd11SoundSystemFRCQ44nw4r3snd11SoundSystem16SoundSystemParam
GetRequiredMemSize__Q34nw4r3snd11SoundSystemFRCQ44nw4r3snd11SoundSystem16SoundSystemParam:
/* 800475B8 000424B8  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800475BC 000424BC  7C 08 02 A6 */	mflr r0
/* 800475C0 000424C0  90 01 00 14 */	stw r0, 0x14(r1)
/* 800475C4 000424C4  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800475C8 000424C8  93 C1 00 08 */	stw r30, 8(r1)
/* 800475CC 000424CC  7C 7E 1B 78 */	mr r30, r3
/* 800475D0 000424D0  48 00 6A E5 */	bl GetInstance__Q44nw4r3snd6detail12VoiceManagerFv
/* 800475D4 000424D4  48 00 6B DD */	bl GetRequiredMemSize__Q44nw4r3snd6detail12VoiceManagerFv
/* 800475D8 000424D8  7C 7F 1B 78 */	mr r31, r3
/* 800475DC 000424DC  4B FE D9 6D */	bl GetInstance__Q44nw4r3snd6detail14AxVoiceManagerFv
/* 800475E0 000424E0  4B FE DA 91 */	bl GetRequiredMemSize__Q44nw4r3snd6detail14AxVoiceManagerFv
/* 800475E4 000424E4  80 1E 00 0C */	lwz r0, 0xc(r30)
/* 800475E8 000424E8  80 9E 00 04 */	lwz r4, 4(r30)
/* 800475EC 000424EC  7F FF 02 14 */	add r31, r31, r0
/* 800475F0 000424F0  7F C3 22 14 */	add r30, r3, r4
/* 800475F4 000424F4  4B FE FE 75 */	bl GetInstance__Q44nw4r3snd6detail14ChannelManagerFv
/* 800475F8 000424F8  4B FE FF 4D */	bl GetRequiredMemSize__Q44nw4r3snd6detail14ChannelManagerFv
/* 800475FC 000424FC  7C 1E FA 14 */	add r0, r30, r31
/* 80047600 00042500  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80047604 00042504  7C 63 02 14 */	add r3, r3, r0
/* 80047608 00042508  83 C1 00 08 */	lwz r30, 8(r1)
/* 8004760C 0004250C  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80047610 00042510  7C 08 03 A6 */	mtlr r0
/* 80047614 00042514  38 21 00 10 */	addi r1, r1, 0x10
/* 80047618 00042518  4E 80 00 20 */	blr 

.global InitSoundSystem__Q34nw4r3snd11SoundSystemFRCQ44nw4r3snd11SoundSystem16SoundSystemParamPvUl
InitSoundSystem__Q34nw4r3snd11SoundSystemFRCQ44nw4r3snd11SoundSystem16SoundSystemParamPvUl:
/* 8004761C 0004251C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80047620 00042520  7C 08 02 A6 */	mflr r0
/* 80047624 00042524  90 01 00 24 */	stw r0, 0x24(r1)
/* 80047628 00042528  39 61 00 20 */	addi r11, r1, 0x20
/* 8004762C 0004252C  48 06 A7 15 */	bl _savegpr_26
/* 80047630 00042530  88 0D 97 88 */	lbz r0, lbl_804BEB08-_SDA_BASE_(r13)
/* 80047634 00042534  7C 7A 1B 78 */	mr r26, r3
/* 80047638 00042538  7C 9B 23 78 */	mr r27, r4
/* 8004763C 0004253C  2C 00 00 00 */	cmpwi r0, 0
/* 80047640 00042540  40 82 01 50 */	bne lbl_80047790
/* 80047644 00042544  38 00 00 01 */	li r0, 1
/* 80047648 00042548  98 0D 97 88 */	stb r0, lbl_804BEB08-_SDA_BASE_(r13)
/* 8004764C 0004254C  4B FE 9C 9D */	bl GetInstance__Q44nw4r3snd6detail9AxManagerFv
/* 80047650 00042550  4B FE 9D 75 */	bl Init__Q44nw4r3snd6detail9AxManagerFv
/* 80047654 00042554  48 0A F9 B1 */	bl func_800F7004
lbl_80047658:
/* 80047658 00042558  48 0A FA 4D */	bl func_800F70A4
/* 8004765C 0004255C  28 03 00 01 */	cmplwi r3, 1
/* 80047660 00042560  41 82 FF F8 */	beq lbl_80047658
/* 80047664 00042564  48 0B 15 41 */	bl func_800F8BA4
/* 80047668 00042568  54 60 06 3E */	clrlwi r0, r3, 0x18
/* 8004766C 0004256C  2C 00 00 01 */	cmpwi r0, 1
/* 80047670 00042570  41 82 00 30 */	beq lbl_800476A0
/* 80047674 00042574  40 80 00 10 */	bge lbl_80047684
/* 80047678 00042578  2C 00 00 00 */	cmpwi r0, 0
/* 8004767C 0004257C  40 80 00 14 */	bge lbl_80047690
/* 80047680 00042580  48 00 00 40 */	b lbl_800476C0
lbl_80047684:
/* 80047684 00042584  2C 00 00 03 */	cmpwi r0, 3
/* 80047688 00042588  40 80 00 38 */	bge lbl_800476C0
/* 8004768C 0004258C  48 00 00 24 */	b lbl_800476B0
lbl_80047690:
/* 80047690 00042590  4B FE 9C 59 */	bl GetInstance__Q44nw4r3snd6detail9AxManagerFv
/* 80047694 00042594  38 80 00 03 */	li r4, 3
/* 80047698 00042598  4B FE A4 05 */	bl SetOutputMode__Q44nw4r3snd6detail9AxManagerFQ34nw4r3snd10OutputMode
/* 8004769C 0004259C  48 00 00 30 */	b lbl_800476CC
lbl_800476A0:
/* 800476A0 000425A0  4B FE 9C 49 */	bl GetInstance__Q44nw4r3snd6detail9AxManagerFv
/* 800476A4 000425A4  38 80 00 00 */	li r4, 0
/* 800476A8 000425A8  4B FE A3 F5 */	bl SetOutputMode__Q44nw4r3snd6detail9AxManagerFQ34nw4r3snd10OutputMode
/* 800476AC 000425AC  48 00 00 20 */	b lbl_800476CC
lbl_800476B0:
/* 800476B0 000425B0  4B FE 9C 39 */	bl GetInstance__Q44nw4r3snd6detail9AxManagerFv
/* 800476B4 000425B4  38 80 00 02 */	li r4, 2
/* 800476B8 000425B8  4B FE A3 E5 */	bl SetOutputMode__Q44nw4r3snd6detail9AxManagerFQ34nw4r3snd10OutputMode
/* 800476BC 000425BC  48 00 00 10 */	b lbl_800476CC
lbl_800476C0:
/* 800476C0 000425C0  4B FE 9C 29 */	bl GetInstance__Q44nw4r3snd6detail9AxManagerFv
/* 800476C4 000425C4  38 80 00 00 */	li r4, 0
/* 800476C8 000425C8  4B FE A3 D5 */	bl SetOutputMode__Q44nw4r3snd6detail9AxManagerFQ34nw4r3snd10OutputMode
lbl_800476CC:
/* 800476CC 000425CC  4B FF 64 51 */	bl GetInstance__Q44nw4r3snd6detail20RemoteSpeakerManagerFv
/* 800476D0 000425D0  4B FF 64 F5 */	bl Setup__Q44nw4r3snd6detail20RemoteSpeakerManagerFv
/* 800476D4 000425D4  80 7A 00 0C */	lwz r3, 0xc(r26)
/* 800476D8 000425D8  80 1A 00 04 */	lwz r0, 4(r26)
/* 800476DC 000425DC  7F DB 1A 14 */	add r30, r27, r3
/* 800476E0 000425E0  7F DD F3 78 */	mr r29, r30
/* 800476E4 000425E4  7F DE 02 14 */	add r30, r30, r0
/* 800476E8 000425E8  7F DC F3 78 */	mr r28, r30
/* 800476EC 000425EC  4B FE D8 5D */	bl GetInstance__Q44nw4r3snd6detail14AxVoiceManagerFv
/* 800476F0 000425F0  4B FE D9 81 */	bl GetRequiredMemSize__Q44nw4r3snd6detail14AxVoiceManagerFv
/* 800476F4 000425F4  7F DE 1A 14 */	add r30, r30, r3
/* 800476F8 000425F8  4B FE D8 51 */	bl GetInstance__Q44nw4r3snd6detail14AxVoiceManagerFv
/* 800476FC 000425FC  4B FE D9 75 */	bl GetRequiredMemSize__Q44nw4r3snd6detail14AxVoiceManagerFv
/* 80047700 00042600  7C 7F 1B 78 */	mr r31, r3
/* 80047704 00042604  4B FE D8 45 */	bl GetInstance__Q44nw4r3snd6detail14AxVoiceManagerFv
/* 80047708 00042608  7F 84 E3 78 */	mr r4, r28
/* 8004770C 0004260C  7F E5 FB 78 */	mr r5, r31
/* 80047710 00042610  4B FE D9 89 */	bl Setup__Q44nw4r3snd6detail14AxVoiceManagerFPvUl
/* 80047714 00042614  7F DC F3 78 */	mr r28, r30
/* 80047718 00042618  48 00 69 9D */	bl GetInstance__Q44nw4r3snd6detail12VoiceManagerFv
/* 8004771C 0004261C  48 00 6A 95 */	bl GetRequiredMemSize__Q44nw4r3snd6detail12VoiceManagerFv
/* 80047720 00042620  7F DE 1A 14 */	add r30, r30, r3
/* 80047724 00042624  48 00 69 91 */	bl GetInstance__Q44nw4r3snd6detail12VoiceManagerFv
/* 80047728 00042628  48 00 6A 89 */	bl GetRequiredMemSize__Q44nw4r3snd6detail12VoiceManagerFv
/* 8004772C 0004262C  7C 7F 1B 78 */	mr r31, r3
/* 80047730 00042630  48 00 69 85 */	bl GetInstance__Q44nw4r3snd6detail12VoiceManagerFv
/* 80047734 00042634  7F 84 E3 78 */	mr r4, r28
/* 80047738 00042638  7F E5 FB 78 */	mr r5, r31
/* 8004773C 0004263C  48 00 6A 99 */	bl Setup__Q44nw4r3snd6detail12VoiceManagerFPvUl
/* 80047740 00042640  4B FE FD 29 */	bl GetInstance__Q44nw4r3snd6detail14ChannelManagerFv
/* 80047744 00042644  4B FE FE 01 */	bl GetRequiredMemSize__Q44nw4r3snd6detail14ChannelManagerFv
/* 80047748 00042648  4B FE FD 21 */	bl GetInstance__Q44nw4r3snd6detail14ChannelManagerFv
/* 8004774C 0004264C  4B FE FD F9 */	bl GetRequiredMemSize__Q44nw4r3snd6detail14ChannelManagerFv
/* 80047750 00042650  7C 7F 1B 78 */	mr r31, r3
/* 80047754 00042654  4B FE FD 15 */	bl GetInstance__Q44nw4r3snd6detail14ChannelManagerFv
/* 80047758 00042658  7F C4 F3 78 */	mr r4, r30
/* 8004775C 0004265C  7F E5 FB 78 */	mr r5, r31
/* 80047760 00042660  4B FE FE 0D */	bl Setup__Q44nw4r3snd6detail14ChannelManagerFPvUl
/* 80047764 00042664  3C 60 80 3D */	lis r3, lbl_803D0BD0@ha
/* 80047768 00042668  80 9A 00 08 */	lwz r4, 8(r26)
/* 8004776C 0004266C  80 DA 00 0C */	lwz r6, 0xc(r26)
/* 80047770 00042670  7F 65 DB 78 */	mr r5, r27
/* 80047774 00042674  38 63 0B D0 */	addi r3, r3, lbl_803D0BD0@l
/* 80047778 00042678  48 00 40 85 */	bl Create__Q44nw4r3snd6detail10TaskThreadFlPvUl
/* 8004777C 0004267C  48 00 01 5D */	bl GetInstance__Q44nw4r3snd6detail11SoundThreadFv
/* 80047780 00042680  80 9A 00 00 */	lwz r4, 0(r26)
/* 80047784 00042684  7F A5 EB 78 */	mr r5, r29
/* 80047788 00042688  80 DA 00 04 */	lwz r6, 4(r26)
/* 8004778C 0004268C  48 00 02 81 */	bl Create__Q44nw4r3snd6detail11SoundThreadFlPvUl
lbl_80047790:
/* 80047790 00042690  39 61 00 20 */	addi r11, r1, 0x20
/* 80047794 00042694  48 06 A5 F9 */	bl _restgpr_26
/* 80047798 00042698  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8004779C 0004269C  7C 08 03 A6 */	mtlr r0
/* 800477A0 000426A0  38 21 00 20 */	addi r1, r1, 0x20
/* 800477A4 000426A4  4E 80 00 20 */	blr 

.global ShutdownSoundSystem__Q34nw4r3snd11SoundSystemFv
ShutdownSoundSystem__Q34nw4r3snd11SoundSystemFv:
/* 800477A8 000426A8  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800477AC 000426AC  7C 08 02 A6 */	mflr r0
/* 800477B0 000426B0  90 01 00 14 */	stw r0, 0x14(r1)
/* 800477B4 000426B4  88 0D 97 88 */	lbz r0, lbl_804BEB08-_SDA_BASE_(r13)
/* 800477B8 000426B8  2C 00 00 00 */	cmpwi r0, 0
/* 800477BC 000426BC  41 82 00 50 */	beq lbl_8004780C
/* 800477C0 000426C0  48 00 01 19 */	bl GetInstance__Q44nw4r3snd6detail11SoundThreadFv
/* 800477C4 000426C4  48 00 03 81 */	bl Shutdown__Q44nw4r3snd6detail11SoundThreadFv
/* 800477C8 000426C8  48 00 38 31 */	bl GetInstance__Q44nw4r3snd6detail11TaskManagerFv
/* 800477CC 000426CC  48 00 3D F5 */	bl CancelAllTask__Q44nw4r3snd6detail11TaskManagerFv
/* 800477D0 000426D0  3C 60 80 3D */	lis r3, lbl_803D0BD0@ha
/* 800477D4 000426D4  38 63 0B D0 */	addi r3, r3, lbl_803D0BD0@l
/* 800477D8 000426D8  48 00 40 F9 */	bl Destroy__Q44nw4r3snd6detail10TaskThreadFv
/* 800477DC 000426DC  4B FF 63 41 */	bl GetInstance__Q44nw4r3snd6detail20RemoteSpeakerManagerFv
/* 800477E0 000426E0  4B FF 64 81 */	bl Shutdown__Q44nw4r3snd6detail20RemoteSpeakerManagerFv
/* 800477E4 000426E4  4B FE FC 85 */	bl GetInstance__Q44nw4r3snd6detail14ChannelManagerFv
/* 800477E8 000426E8  4B FE FE 19 */	bl Shutdown__Q44nw4r3snd6detail14ChannelManagerFv
/* 800477EC 000426EC  48 00 68 C9 */	bl GetInstance__Q44nw4r3snd6detail12VoiceManagerFv
/* 800477F0 000426F0  48 00 6A 89 */	bl Shutdown__Q44nw4r3snd6detail12VoiceManagerFv
/* 800477F4 000426F4  4B FE D7 55 */	bl GetInstance__Q44nw4r3snd6detail14AxVoiceManagerFv
/* 800477F8 000426F8  4B FE D9 45 */	bl Shutdown__Q44nw4r3snd6detail14AxVoiceManagerFv
/* 800477FC 000426FC  4B FE 9A ED */	bl GetInstance__Q44nw4r3snd6detail9AxManagerFv
/* 80047800 00042700  4B FE 9C 99 */	bl Shutdown__Q44nw4r3snd6detail9AxManagerFv
/* 80047804 00042704  38 00 00 00 */	li r0, 0
/* 80047808 00042708  98 0D 97 88 */	stb r0, lbl_804BEB08-_SDA_BASE_(r13)
lbl_8004780C:
/* 8004780C 0004270C  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80047810 00042710  7C 08 03 A6 */	mtlr r0
/* 80047814 00042714  38 21 00 10 */	addi r1, r1, 0x10
/* 80047818 00042718  4E 80 00 20 */	blr 

.global WaitForResetReady__Q34nw4r3snd11SoundSystemFv
WaitForResetReady__Q34nw4r3snd11SoundSystemFv:
/* 8004781C 0004271C  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80047820 00042720  7C 08 02 A6 */	mflr r0
/* 80047824 00042724  90 01 00 14 */	stw r0, 0x14(r1)
/* 80047828 00042728  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8004782C 0004272C  93 C1 00 08 */	stw r30, 8(r1)
/* 80047830 00042730  88 0D 97 88 */	lbz r0, lbl_804BEB08-_SDA_BASE_(r13)
/* 80047834 00042734  2C 00 00 00 */	cmpwi r0, 0
/* 80047838 00042738  41 82 00 40 */	beq lbl_80047878
/* 8004783C 0004273C  48 0A DD E1 */	bl OSGetTick
/* 80047840 00042740  7C 7E 1B 78 */	mr r30, r3
/* 80047844 00042744  3F E0 80 00 */	lis r31, 0x8000
/* 80047848 00042748  48 00 00 1C */	b lbl_80047864
lbl_8004784C:
/* 8004784C 0004274C  48 0A DD D1 */	bl OSGetTick
/* 80047850 00042750  80 1F 00 F8 */	lwz r0, 0xf8(r31)
/* 80047854 00042754  7C 7E 18 50 */	subf r3, r30, r3
/* 80047858 00042758  54 00 F0 BE */	srwi r0, r0, 2
/* 8004785C 0004275C  7C 03 03 97 */	divwu. r0, r3, r0
/* 80047860 00042760  40 82 00 18 */	bne lbl_80047878
lbl_80047864:
/* 80047864 00042764  4B FE 9A 85 */	bl GetInstance__Q44nw4r3snd6detail9AxManagerFv
/* 80047868 00042768  80 03 00 50 */	lwz r0, 0x50(r3)
/* 8004786C 0004276C  7C 00 00 34 */	cntlzw r0, r0
/* 80047870 00042770  54 00 D9 7F */	rlwinm. r0, r0, 0x1b, 5, 0x1f
/* 80047874 00042774  41 82 FF D8 */	beq lbl_8004784C
lbl_80047878:
/* 80047878 00042778  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8004787C 0004277C  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80047880 00042780  83 C1 00 08 */	lwz r30, 8(r1)
/* 80047884 00042784  7C 08 03 A6 */	mtlr r0
/* 80047888 00042788  38 21 00 10 */	addi r1, r1, 0x10
/* 8004788C 0004278C  4E 80 00 20 */	blr 

# __sinit_\snd_SoundSystem_cpp
.global __sinit_$$3snd_SoundSystem_cpp
__sinit_$$3snd_SoundSystem_cpp:
/* 80047890 00042790  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80047894 00042794  7C 08 02 A6 */	mflr r0
/* 80047898 00042798  90 01 00 14 */	stw r0, 0x14(r1)
/* 8004789C 0004279C  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800478A0 000427A0  3F E0 80 3D */	lis r31, lbl_803D0BD0@ha
/* 800478A4 000427A4  38 7F 0B D0 */	addi r3, r31, lbl_803D0BD0@l
/* 800478A8 000427A8  48 00 3E BD */	bl __ct__Q44nw4r3snd6detail10TaskThreadFv
/* 800478AC 000427AC  3C 80 80 05 */	lis r4, __dt__Q44nw4r3snd6detail10TaskThreadFv@ha
/* 800478B0 000427B0  3C A0 80 3D */	lis r5, lbl_803D0BC0@ha
/* 800478B4 000427B4  38 7F 0B D0 */	addi r3, r31, 0xbd0
/* 800478B8 000427B8  38 84 B7 78 */	addi r4, r4, __dt__Q44nw4r3snd6detail10TaskThreadFv@l
/* 800478BC 000427BC  38 A5 0B C0 */	addi r5, r5, lbl_803D0BC0@l
/* 800478C0 000427C0  48 06 9F 75 */	bl func_800B1834
/* 800478C4 000427C4  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800478C8 000427C8  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 800478CC 000427CC  7C 08 03 A6 */	mtlr r0
/* 800478D0 000427D0  38 21 00 10 */	addi r1, r1, 0x10
/* 800478D4 000427D4  4E 80 00 20 */	blr 
