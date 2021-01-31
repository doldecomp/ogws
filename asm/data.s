.include "macros.inc"

.section .data, "wa"  # 0x80393A80 - 0x803CAF00

.global __vt__Q44nw4r3snd6detail10SoundActor
__vt__Q44nw4r3snd6detail10SoundActor:
	.long 0
	.long 0
	.long __dt__Q44nw4r3snd6detail10SoundActorFv
	.long detail_SetupSound__Q44nw4r3snd6detail10SoundActorFPQ34nw4r3snd11SoundHandleUlPQ54nw4r3snd6detail10BasicSound14AmbientArgInfoPQ44nw4r3snd6detail19ExternalSoundPlayerbPCQ44nw4r3snd14SoundStartable9StartInfo
	.long detail_ConvertLabelStringToSoundId__Q44nw4r3snd6detail10SoundActorFPCc
.balign 0x8

.global __vt__Q34nw4r3snd12SoundArchive
__vt__Q34nw4r3snd12SoundArchive:
	.long 0
	.long 0
	.long __dt__Q34nw4r3snd12SoundArchiveFv
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
.balign 0x8

.global __vt__Q34nw4r3snd18SoundArchivePlayer
__vt__Q34nw4r3snd18SoundArchivePlayer:
	.long 0
	.long 0
	.long __dt__Q34nw4r3snd18SoundArchivePlayerFv
	.long InvalidateData__Q34nw4r3snd18SoundArchivePlayerFPCvPCv
	.long InvalidateWaveData__Q34nw4r3snd18SoundArchivePlayerFPCvPCv
	.long 0
	.long 0
	.long $$218$$2__dt__Q34nw4r3snd18SoundArchivePlayerFv____
	.long $$218$$2detail_SetupSound__Q34nw4r3snd18SoundArchivePlayerFPQ34nw4r3snd11SoundHandleUlPQ54nw4r3snd6detail10BasicSound14AmbientArgInfoPQ44nw4r3snd6detail19ExternalSoundPlayerbPCQ44nw4r3snd14SoundStartable9StartInfo
	.long $$218$$2detail_ConvertLabelStringToSoundId__Q34nw4r3snd18SoundArchivePlayerFPCc
	.long detail_SetupSound__Q34nw4r3snd18SoundArchivePlayerFPQ34nw4r3snd11SoundHandleUlPQ54nw4r3snd6detail10BasicSound14AmbientArgInfoPQ44nw4r3snd6detail19ExternalSoundPlayerbPCQ44nw4r3snd14SoundStartable9StartInfo
	.long detail_ConvertLabelStringToSoundId__Q34nw4r3snd18SoundArchivePlayerFPCc
.balign 0x8

.global __vt__Q44nw4r3snd18SoundArchivePlayer11WsdCallback
__vt__Q44nw4r3snd18SoundArchivePlayer11WsdCallback:
	.long 0
	.long 0
	.long __dt__Q44nw4r3snd18SoundArchivePlayer11WsdCallbackFv
	.long GetWaveSoundData__Q44nw4r3snd18SoundArchivePlayer11WsdCallbackCFPQ44nw4r3snd6detail13WaveSoundInfoPQ44nw4r3snd6detail17WaveSoundNoteInfoPQ44nw4r3snd6detail8WaveDataPCviiUl
.balign 0x8

.global __vt__Q44nw4r3snd18SoundArchivePlayer17SeqNoteOnCallback
__vt__Q44nw4r3snd18SoundArchivePlayer17SeqNoteOnCallback:
	.long 0
	.long 0
	.long __dt__Q44nw4r3snd18SoundArchivePlayer17SeqNoteOnCallbackFv
	.long NoteOn__Q44nw4r3snd18SoundArchivePlayer17SeqNoteOnCallbackFPQ44nw4r3snd6detail9SeqPlayeriRCQ44nw4r3snd6detail10NoteOnInfo
.balign 0x8

.global __vt__Q44nw4r3snd6detail10PlayerHeap
__vt__Q44nw4r3snd6detail10PlayerHeap:
	.long 0
	.long 0
	.long __dt__Q44nw4r3snd6detail10PlayerHeapFv
	.long Alloc__Q34nw4r3snd9SoundHeapFUl
.balign 0x8

.global __vt__Q34nw4r3snd9SoundHeap
__vt__Q34nw4r3snd9SoundHeap:
	.long 0
	.long 0
	.long __dt__Q34nw4r3snd9SoundHeapFv
	.long Alloc__Q34nw4r3snd9SoundHeapFUl
.balign 0x8

.global $$24063
$$24063:
.string "<< NW4R    - SND \tfinal   build: Jun  8 2007 11:17:15 (0x4199_60831) >>"
.balign 0x8

.global __vt__Q44nw4r3snd6detail10StrmPlayer
__vt__Q44nw4r3snd6detail10StrmPlayer:
	.long 0
	.long 0
	.long __dt__Q44nw4r3snd6detail10StrmPlayerFv
	.long Start__Q44nw4r3snd6detail10StrmPlayerFv
	.long Stop__Q44nw4r3snd6detail10StrmPlayerFv
	.long Pause__Q44nw4r3snd6detail10StrmPlayerFb
	.long IsActive__Q44nw4r3snd6detail10StrmPlayerCFv
	.long IsStarted__Q44nw4r3snd6detail10StrmPlayerCFv
	.long IsPause__Q44nw4r3snd6detail10StrmPlayerCFv
	.long 0
	.long 0
	.long $2116$2__dt__Q44nw4r3snd6detail10StrmPlayerFv
	.long $2116$2OnUpdateFrameSoundThread__Q44nw4r3snd6detail10StrmPlayerFv
	.long $2116$2OnUpdateVoiceSoundThread__Q44nw4r3snd6detail10StrmPlayerFv
	.long $2116$2OnShutdownSoundThread__Q44nw4r3snd6detail10StrmPlayerFv
	.long OnUpdateFrameSoundThread__Q44nw4r3snd6detail10StrmPlayerFv
	.long OnUpdateVoiceSoundThread__Q44nw4r3snd6detail10StrmPlayerFv
	.long OnShutdownSoundThread__Q44nw4r3snd6detail10StrmPlayerFv
.balign 0x8

.global __vt__Q54nw4r3snd6detail10StrmPlayer16StrmDataLoadTask
__vt__Q54nw4r3snd6detail10StrmPlayer16StrmDataLoadTask:
	.long 0
	.long 0
	.long __dt__Q54nw4r3snd6detail10StrmPlayer16StrmDataLoadTaskFv
	.long Execute__Q54nw4r3snd6detail10StrmPlayer16StrmDataLoadTaskFv
	.long Cancel__Q54nw4r3snd6detail10StrmPlayer16StrmDataLoadTaskFv
	.long OnCancel__Q54nw4r3snd6detail10StrmPlayer16StrmDataLoadTaskFv
.balign 0x8

.global __vt__Q54nw4r3snd6detail10StrmPlayer18StrmHeaderLoadTask
__vt__Q54nw4r3snd6detail10StrmPlayer18StrmHeaderLoadTask:
	.long 0
	.long 0
	.long __dt__Q54nw4r3snd6detail10StrmPlayer18StrmHeaderLoadTaskFv
	.long Execute__Q54nw4r3snd6detail10StrmPlayer18StrmHeaderLoadTaskFv
	.long Cancel__Q54nw4r3snd6detail10StrmPlayer18StrmHeaderLoadTaskFv
	.long OnCancel__Q54nw4r3snd6detail10StrmPlayer18StrmHeaderLoadTaskFv
.balign 0x8

.global __vt__Q44nw4r3snd6detail9StrmSound
__vt__Q44nw4r3snd6detail9StrmSound:
	.long 0
	.long 0
	.long GetRuntimeTypeInfo__Q44nw4r3snd6detail9StrmSoundCFv
	.long __dt__Q44nw4r3snd6detail9StrmSoundFv
	.long Update__Q44nw4r3snd6detail10BasicSoundFv
	.long StartPrepared__Q44nw4r3snd6detail10BasicSoundFv
	.long Stop__Q44nw4r3snd6detail10BasicSoundFi
	.long Pause__Q44nw4r3snd6detail10BasicSoundFbi
	.long SetAutoStopCounter__Q44nw4r3snd6detail10BasicSoundFi
	.long FadeIn__Q44nw4r3snd6detail10BasicSoundFi
	.long Shutdown__Q44nw4r3snd6detail9StrmSoundFv
	.long IsPrepared__Q44nw4r3snd6detail9StrmSoundCFv
	.long IsPause__Q44nw4r3snd6detail10BasicSoundCFv
	.long SetInitialVolume__Q44nw4r3snd6detail10BasicSoundFf
	.long SetVolume__Q44nw4r3snd6detail10BasicSoundFfi
	.long SetPitch__Q44nw4r3snd6detail10BasicSoundFf
	.long SetPan__Q44nw4r3snd6detail10BasicSoundFf
	.long SetSurroundPan__Q44nw4r3snd6detail10BasicSoundFf
	.long SetLpfFreq__Q44nw4r3snd6detail10BasicSoundFf
	.long SetPlayerPriority__Q44nw4r3snd6detail9StrmSoundFi
	.long SetRemoteFilter__Q44nw4r3snd6detail10BasicSoundFi
	.long SetPanMode__Q44nw4r3snd6detail10BasicSoundFQ44nw4r3snd6detail7PanMode
	.long SetPanCurve__Q44nw4r3snd6detail10BasicSoundFQ44nw4r3snd6detail8PanCurve
	.long IsAttachedTempSpecialHandle__Q44nw4r3snd6detail9StrmSoundFv
	.long DetachTempSpecialHandle__Q44nw4r3snd6detail9StrmSoundFv
	.long InitParam__Q44nw4r3snd6detail10BasicSoundFv
	.long GetBasicPlayer__Q44nw4r3snd6detail9StrmSoundFv
	.long GetBasicPlayer__Q44nw4r3snd6detail9StrmSoundCFv
.balign 0x8

.global switch_80396430
switch_80396430:
	.long 0x8004D780
	.long 0x8004D788
	.long 0x8004D798
	.long 0x8004D7AC
	.long 0x8004D7B8
	.long 0x8004D7C8
	.long 0x8004D7DC
	.long 0x8004D7E8
	.long 0x8004D7FC

.global lbl_80396454
lbl_80396454:
	.incbin "baserom.dol", 0x392554, 0x14
.global lbl_80396468
lbl_80396468:
	.incbin "baserom.dol", 0x392568, 0x10
.global lbl_80396478
lbl_80396478:
	.incbin "baserom.dol", 0x392578, 0x70
.global lbl_803964E8
lbl_803964E8:
	.incbin "baserom.dol", 0x3925E8, 0x78
.global lbl_80396560
lbl_80396560:
	.incbin "baserom.dol", 0x392660, 0x20
.global lbl_80396580
lbl_80396580:
	.incbin "baserom.dol", 0x392680, 0x20
.global lbl_803965A0
lbl_803965A0:
	.incbin "baserom.dol", 0x3926A0, 0x20
.global lbl_803965C0
lbl_803965C0:
	.incbin "baserom.dol", 0x3926C0, 0x20
.global lbl_803965E0
lbl_803965E0:
	.incbin "baserom.dol", 0x3926E0, 0x20
.global lbl_80396600
lbl_80396600:
	.incbin "baserom.dol", 0x392700, 0x20
.global lbl_80396620
lbl_80396620:
	.incbin "baserom.dol", 0x392720, 0x20
.global lbl_80396640
lbl_80396640:
	.incbin "baserom.dol", 0x392740, 0x20
.global lbl_80396660
lbl_80396660:
	.incbin "baserom.dol", 0x392760, 0x20
.global lbl_80396680
lbl_80396680:
	.incbin "baserom.dol", 0x392780, 0x40
.global lbl_803966C0
lbl_803966C0:
	.incbin "baserom.dol", 0x3927C0, 0x60
.global lbl_80396720
lbl_80396720:
	.incbin "baserom.dol", 0x392820, 0x20
.global lbl_80396740
lbl_80396740:
	.incbin "baserom.dol", 0x392840, 0x20
.global lbl_80396760
lbl_80396760:
	.incbin "baserom.dol", 0x392860, 0x20
.global lbl_80396780
lbl_80396780:
	.incbin "baserom.dol", 0x392880, 0x44
.global lbl_803967C4
lbl_803967C4:
	.incbin "baserom.dol", 0x3928C4, 0x44
.global lbl_80396808
lbl_80396808:
	.incbin "baserom.dol", 0x392908, 0x44
.global lbl_8039684C
lbl_8039684C:
	.incbin "baserom.dol", 0x39294C, 0x44
.global lbl_80396890
lbl_80396890:
	.incbin "baserom.dol", 0x392990, 0x48
.global lbl_803968D8
lbl_803968D8:
	.incbin "baserom.dol", 0x3929D8, 0x48
.global lbl_80396920
lbl_80396920:
	.incbin "baserom.dol", 0x392A20, 0x48
.global lbl_80396968
lbl_80396968:
	.incbin "baserom.dol", 0x392A68, 0x48
.global lbl_803969B0
lbl_803969B0:
	.incbin "baserom.dol", 0x392AB0, 0x48
.global lbl_803969F8
lbl_803969F8:
	.incbin "baserom.dol", 0x392AF8, 0x48
.global lbl_80396A40
lbl_80396A40:
	.incbin "baserom.dol", 0x392B40, 0x48
.global lbl_80396A88
lbl_80396A88:
	.incbin "baserom.dol", 0x392B88, 0x48
.global lbl_80396AD0
lbl_80396AD0:
	.incbin "baserom.dol", 0x392BD0, 0x48
.global lbl_80396B18
lbl_80396B18:
	.incbin "baserom.dol", 0x392C18, 0x48
.global lbl_80396B60
lbl_80396B60:
	.incbin "baserom.dol", 0x392C60, 0x48
.global lbl_80396BA8
lbl_80396BA8:
	.incbin "baserom.dol", 0x392CA8, 0x48
.global lbl_80396BF0
lbl_80396BF0:
	.incbin "baserom.dol", 0x392CF0, 0x58
.global lbl_80396C48
lbl_80396C48:
	.incbin "baserom.dol", 0x392D48, 0x58
.global lbl_80396CA0
lbl_80396CA0:
	.incbin "baserom.dol", 0x392DA0, 0x58
.global lbl_80396CF8
lbl_80396CF8:
	.incbin "baserom.dol", 0x392DF8, 0x58
.global lbl_80396D50
lbl_80396D50:
	.incbin "baserom.dol", 0x392E50, 0x50
.global lbl_80396DA0
lbl_80396DA0:
	.incbin "baserom.dol", 0x392EA0, 0x50
.global lbl_80396DF0
lbl_80396DF0:
	.incbin "baserom.dol", 0x392EF0, 0x50
.global lbl_80396E40
lbl_80396E40:
	.incbin "baserom.dol", 0x392F40, 0x50
.global lbl_80396E90
lbl_80396E90:
	.incbin "baserom.dol", 0x392F90, 0x20
.global lbl_80396EB0
lbl_80396EB0:
	.incbin "baserom.dol", 0x392FB0, 0x18
.global lbl_80396EC8
lbl_80396EC8:
	.incbin "baserom.dol", 0x392FC8, 0x10
.global lbl_80396ED8
lbl_80396ED8:
	.incbin "baserom.dol", 0x392FD8, 0x28
.global lbl_80396F00
lbl_80396F00:
	.incbin "baserom.dol", 0x393000, 0x28
.global lbl_80396F28
lbl_80396F28:
	.incbin "baserom.dol", 0x393028, 0x40
.global lbl_80396F68
lbl_80396F68:
	.incbin "baserom.dol", 0x393068, 0x38
.global lbl_80396FA0
lbl_80396FA0:
	.incbin "baserom.dol", 0x3930A0, 0x28
.global lbl_80396FC8
lbl_80396FC8:
	.incbin "baserom.dol", 0x3930C8, 0x40
.global lbl_80397008
lbl_80397008:
	.incbin "baserom.dol", 0x393108, 0x1C
.global lbl_80397024
lbl_80397024:
	.incbin "baserom.dol", 0x393124, 0xC
.global lbl_80397030
lbl_80397030:
	.incbin "baserom.dol", 0x393130, 0x48
.global lbl_80397078
lbl_80397078:
	.incbin "baserom.dol", 0x393178, 0x48

.global $$27641
$$27641:
	.string "<< NW4R    - G3D \tfinal   build: Jun  8 2007 11:16:25 (0x4199_60831) >>"

.global lbl_80397108
lbl_80397108:
	.incbin "baserom.dol", 0x393208, 0x38

.global lbl_80397140
lbl_80397140:
.string "<< NW4R    - LYT \tfinal   build: Jun  8 2007 11:17:26 (0x4199_60831) >>"

.global lbl_80397188
lbl_80397188:
	.incbin "baserom.dol", 0x393288, 0x68
.global lbl_803971F0
lbl_803971F0:
	.incbin "baserom.dol", 0x3932F0, 0x10
.global lbl_80397200
lbl_80397200:
	.incbin "baserom.dol", 0x393300, 0x38
.global lbl_80397238
lbl_80397238:
	.incbin "baserom.dol", 0x393338, 0x68
.global lbl_803972A0
lbl_803972A0:
	.incbin "baserom.dol", 0x3933A0, 0x78
.global lbl_80397318
lbl_80397318:
	.incbin "baserom.dol", 0x393418, 0x3C
.global lbl_80397354
lbl_80397354:
	.incbin "baserom.dol", 0x393454, 0x7C
.global lbl_803973D0
lbl_803973D0:
	.incbin "baserom.dol", 0x3934D0, 0x68
.global lbl_80397438
lbl_80397438:
	.incbin "baserom.dol", 0x393538, 0x20
.global lbl_80397458
lbl_80397458:
	.incbin "baserom.dol", 0x393558, 0x20
.global lbl_80397478
lbl_80397478:
	.incbin "baserom.dol", 0x393578, 0x28
.global lbl_803974A0
lbl_803974A0:
	.incbin "baserom.dol", 0x3935A0, 0x10
.global lbl_803974B0
lbl_803974B0:
	.incbin "baserom.dol", 0x3935B0, 0x20
.global lbl_803974D0
lbl_803974D0:
	.incbin "baserom.dol", 0x3935D0, 0x18
.global lbl_803974E8
lbl_803974E8:
	.incbin "baserom.dol", 0x3935E8, 0x18
.global lbl_80397500
lbl_80397500:
	.incbin "baserom.dol", 0x393600, 0xC
.global lbl_8039750C
lbl_8039750C:
	.incbin "baserom.dol", 0x39360C, 0xC
.global lbl_80397518
lbl_80397518:
	.incbin "baserom.dol", 0x393618, 0x18
.global lbl_80397530
lbl_80397530:
	.incbin "baserom.dol", 0x393630, 0x18
.global lbl_80397548
lbl_80397548:
	.incbin "baserom.dol", 0x393648, 0x20
.global lbl_80397568
lbl_80397568:
	.incbin "baserom.dol", 0x393668, 0x10
.global lbl_80397578
lbl_80397578:
	.incbin "baserom.dol", 0x393678, 0x10
.global lbl_80397588
lbl_80397588:
	.incbin "baserom.dol", 0x393688, 0x38
.global lbl_803975C0
lbl_803975C0:
	.incbin "baserom.dol", 0x3936C0, 0x20
.global lbl_803975E0
lbl_803975E0:
	.incbin "baserom.dol", 0x3936E0, 0x40
.global lbl_80397620
lbl_80397620:
	.incbin "baserom.dol", 0x393720, 0x38
.global lbl_80397658
lbl_80397658:
	.incbin "baserom.dol", 0x393758, 0x48
.global lbl_803976A0
lbl_803976A0:
	.incbin "baserom.dol", 0x3937A0, 0x30
.global lbl_803976D0
lbl_803976D0:
	.incbin "baserom.dol", 0x3937D0, 0xC
.global lbl_803976DC
lbl_803976DC:
	.incbin "baserom.dol", 0x3937DC, 0x14
.global lbl_803976F0
lbl_803976F0:
	.incbin "baserom.dol", 0x3937F0, 0x5C
.global lbl_8039774C
lbl_8039774C:
	.incbin "baserom.dol", 0x39384C, 0x1C
.global lbl_80397768
lbl_80397768:
	.incbin "baserom.dol", 0x393868, 0x48
.global lbl_803977B0
lbl_803977B0:
	.incbin "baserom.dol", 0x3938B0, 0x30
.global lbl_803977E0
lbl_803977E0:
	.incbin "baserom.dol", 0x3938E0, 0x20
.global lbl_80397800
lbl_80397800:
	.incbin "baserom.dol", 0x393900, 0x18
.global lbl_80397818
lbl_80397818:
	.incbin "baserom.dol", 0x393918, 0x1C
.global lbl_80397834
lbl_80397834:
	.incbin "baserom.dol", 0x393934, 0x18
.global lbl_8039784C
lbl_8039784C:
	.incbin "baserom.dol", 0x39394C, 0x20
.global lbl_8039786C
lbl_8039786C:
	.incbin "baserom.dol", 0x39396C, 0x1C
.global lbl_80397888
lbl_80397888:
	.incbin "baserom.dol", 0x393988, 0x30
.global lbl_803978B8
lbl_803978B8:
	.incbin "baserom.dol", 0x3939B8, 0x30
.global lbl_803978E8
lbl_803978E8:
	.incbin "baserom.dol", 0x3939E8, 0x30
.global lbl_80397918
lbl_80397918:
	.incbin "baserom.dol", 0x393A18, 0x18
.global lbl_80397930
lbl_80397930:
	.incbin "baserom.dol", 0x393A30, 0x10
.global lbl_80397940
lbl_80397940:
	.incbin "baserom.dol", 0x393A40, 0x10
.global lbl_80397950
lbl_80397950:
	.incbin "baserom.dol", 0x393A50, 0x48
.global lbl_80397998
lbl_80397998:
	.incbin "baserom.dol", 0x393A98, 0x14
.global lbl_803979AC
lbl_803979AC:
	.incbin "baserom.dol", 0x393AAC, 0x14
.global lbl_803979C0
lbl_803979C0:
	.incbin "baserom.dol", 0x393AC0, 0xA4
.global lbl_80397A64
lbl_80397A64:
	.incbin "baserom.dol", 0x393B64, 0x14
.global lbl_80397A78
lbl_80397A78:
	.incbin "baserom.dol", 0x393B78, 0x64
.global lbl_80397ADC
lbl_80397ADC:
	.incbin "baserom.dol", 0x393BDC, 0x14
.global lbl_80397AF0
lbl_80397AF0:
	.incbin "baserom.dol", 0x393BF0, 0x18
.global lbl_80397B08
lbl_80397B08:
	.incbin "baserom.dol", 0x393C08, 0x20
.global lbl_80397B28
lbl_80397B28:
	.incbin "baserom.dol", 0x393C28, 0xC
.global lbl_80397B34
lbl_80397B34:
	.incbin "baserom.dol", 0x393C34, 0x28
.global lbl_80397B5C
lbl_80397B5C:
	.incbin "baserom.dol", 0x393C5C, 0x1C
.global lbl_80397B78
lbl_80397B78:
	.incbin "baserom.dol", 0x393C78, 0xC
.global lbl_80397B84
lbl_80397B84:
	.incbin "baserom.dol", 0x393C84, 0xC
.global lbl_80397B90
lbl_80397B90:
	.incbin "baserom.dol", 0x393C90, 0x70
.global lbl_80397C00
lbl_80397C00:
	.incbin "baserom.dol", 0x393D00, 0x1C
.global lbl_80397C1C
lbl_80397C1C:
	.incbin "baserom.dol", 0x393D1C, 0x14
.global lbl_80397C30
lbl_80397C30:
	.incbin "baserom.dol", 0x393D30, 0x48
.global lbl_80397C78
lbl_80397C78:
	.incbin "baserom.dol", 0x393D78, 0x28
.global lbl_80397CA0
lbl_80397CA0:
	.incbin "baserom.dol", 0x393DA0, 0x28
.global lbl_80397CC8
lbl_80397CC8:
	.incbin "baserom.dol", 0x393DC8, 0x10
.global lbl_80397CD8
lbl_80397CD8:
	.incbin "baserom.dol", 0x393DD8, 0x10
.global lbl_80397CE8
lbl_80397CE8:
	.incbin "baserom.dol", 0x393DE8, 0x28
.global lbl_80397D10
lbl_80397D10:
	.incbin "baserom.dol", 0x393E10, 0x28
.global lbl_80397D38
lbl_80397D38:
	.incbin "baserom.dol", 0x393E38, 0x28
.global lbl_80397D60
lbl_80397D60:
	.incbin "baserom.dol", 0x393E60, 0x28
.global lbl_80397D88
lbl_80397D88:
	.incbin "baserom.dol", 0x393E88, 0x28
.global lbl_80397DB0
lbl_80397DB0:
	.incbin "baserom.dol", 0x393EB0, 0x28
.global lbl_80397DD8
lbl_80397DD8:
	.incbin "baserom.dol", 0x393ED8, 0x30
.global lbl_80397E08
lbl_80397E08:
	.incbin "baserom.dol", 0x393F08, 0xC
.global lbl_80397E14
lbl_80397E14:
	.incbin "baserom.dol", 0x393F14, 0x14
.global lbl_80397E28
lbl_80397E28:
	.incbin "baserom.dol", 0x393F28, 0x14
.global lbl_80397E3C
lbl_80397E3C:
	.incbin "baserom.dol", 0x393F3C, 0x10
.global lbl_80397E4C
lbl_80397E4C:
	.incbin "baserom.dol", 0x393F4C, 0x10
.global lbl_80397E5C
lbl_80397E5C:
	.incbin "baserom.dol", 0x393F5C, 0x10
.global lbl_80397E6C
lbl_80397E6C:
	.incbin "baserom.dol", 0x393F6C, 0x14
.global lbl_80397E80
lbl_80397E80:
	.incbin "baserom.dol", 0x393F80, 0x20
.global lbl_80397EA0
lbl_80397EA0:
	.incbin "baserom.dol", 0x393FA0, 0x10
.global lbl_80397EB0
lbl_80397EB0:
	.incbin "baserom.dol", 0x393FB0, 0x1C
.global lbl_80397ECC
lbl_80397ECC:
	.incbin "baserom.dol", 0x393FCC, 0x30
.global lbl_80397EFC
lbl_80397EFC:
	.incbin "baserom.dol", 0x393FFC, 0x3C
.global lbl_80397F38
lbl_80397F38:
	.incbin "baserom.dol", 0x394038, 0x1C
.global lbl_80397F54
lbl_80397F54:
	.incbin "baserom.dol", 0x394054, 0x14
.global lbl_80397F68
lbl_80397F68:
	.incbin "baserom.dol", 0x394068, 0x18
.global lbl_80397F80
lbl_80397F80:
	.incbin "baserom.dol", 0x394080, 0x18
.global lbl_80397F98
lbl_80397F98:
	.incbin "baserom.dol", 0x394098, 0x18
.global lbl_80397FB0
lbl_80397FB0:
	.incbin "baserom.dol", 0x3940B0, 0x18
.global lbl_80397FC8
lbl_80397FC8:
	.incbin "baserom.dol", 0x3940C8, 0x1C
.global lbl_80397FE4
lbl_80397FE4:
	.incbin "baserom.dol", 0x3940E4, 0x18
.global lbl_80397FFC
lbl_80397FFC:
	.incbin "baserom.dol", 0x3940FC, 0x14
.global lbl_80398010
lbl_80398010:
	.incbin "baserom.dol", 0x394110, 0x28
.global lbl_80398038
lbl_80398038:
	.incbin "baserom.dol", 0x394138, 0xC
.global lbl_80398044
lbl_80398044:
	.incbin "baserom.dol", 0x394144, 0x18
.global lbl_8039805C
lbl_8039805C:
	.incbin "baserom.dol", 0x39415C, 0x1C
.global lbl_80398078
lbl_80398078:
	.incbin "baserom.dol", 0x394178, 0x14
.global lbl_8039808C
lbl_8039808C:
	.incbin "baserom.dol", 0x39418C, 0x1C
.global lbl_803980A8
lbl_803980A8:
	.incbin "baserom.dol", 0x3941A8, 0x10
.global lbl_803980B8
lbl_803980B8:
	.incbin "baserom.dol", 0x3941B8, 0x30
.global lbl_803980E8
lbl_803980E8:
	.incbin "baserom.dol", 0x3941E8, 0x30
.global lbl_80398118
lbl_80398118:
	.incbin "baserom.dol", 0x394218, 0x30
.global lbl_80398148
lbl_80398148:
	.incbin "baserom.dol", 0x394248, 0x18
.global lbl_80398160
lbl_80398160:
	.incbin "baserom.dol", 0x394260, 0x18
.global lbl_80398178
lbl_80398178:
	.incbin "baserom.dol", 0x394278, 0x38
.global lbl_803981B0
lbl_803981B0:
	.incbin "baserom.dol", 0x3942B0, 0x18
.global lbl_803981C8
lbl_803981C8:
	.incbin "baserom.dol", 0x3942C8, 0x10
.global lbl_803981D8
lbl_803981D8:
	.incbin "baserom.dol", 0x3942D8, 0x28
.global lbl_80398200
lbl_80398200:
	.incbin "baserom.dol", 0x394300, 0x28
.global lbl_80398228
lbl_80398228:
	.incbin "baserom.dol", 0x394328, 0xC
.global lbl_80398234
lbl_80398234:
	.incbin "baserom.dol", 0x394334, 0xC
.global lbl_80398240
lbl_80398240:
	.incbin "baserom.dol", 0x394340, 0x20
.global lbl_80398260
lbl_80398260:
	.incbin "baserom.dol", 0x394360, 0x10
.global lbl_80398270
lbl_80398270:
	.incbin "baserom.dol", 0x394370, 0x1C
.global lbl_8039828C
lbl_8039828C:
	.incbin "baserom.dol", 0x39438C, 0x1C
.global lbl_803982A8
lbl_803982A8:
	.incbin "baserom.dol", 0x3943A8, 0x10
.global lbl_803982B8
lbl_803982B8:
	.incbin "baserom.dol", 0x3943B8, 0x20
.global lbl_803982D8
lbl_803982D8:
	.incbin "baserom.dol", 0x3943D8, 0x24
.global lbl_803982FC
lbl_803982FC:
	.incbin "baserom.dol", 0x3943FC, 0x3C
.global lbl_80398338
lbl_80398338:
	.incbin "baserom.dol", 0x394438, 0x18
.global lbl_80398350
lbl_80398350:
	.incbin "baserom.dol", 0x394450, 0x20
.global lbl_80398370
lbl_80398370:
	.incbin "baserom.dol", 0x394470, 0x28
.global lbl_80398398
lbl_80398398:
	.incbin "baserom.dol", 0x394498, 0x28
.global lbl_803983C0
lbl_803983C0:
	.incbin "baserom.dol", 0x3944C0, 0x68
.global lbl_80398428
lbl_80398428:
	.incbin "baserom.dol", 0x394528, 0x18
.global lbl_80398440
lbl_80398440:
	.incbin "baserom.dol", 0x394540, 0x18
.global lbl_80398458
lbl_80398458:
	.incbin "baserom.dol", 0x394558, 0x10
.global lbl_80398468
lbl_80398468:
	.incbin "baserom.dol", 0x394568, 0x18
.global lbl_80398480
lbl_80398480:
	.incbin "baserom.dol", 0x394580, 0x40
.global lbl_803984C0
lbl_803984C0:
	.incbin "baserom.dol", 0x3945C0, 0x20
.global lbl_803984E0
lbl_803984E0:
	.incbin "baserom.dol", 0x3945E0, 0x20
.global lbl_80398500
lbl_80398500:
	.incbin "baserom.dol", 0x394600, 0x10
.global lbl_80398510
lbl_80398510:
	.incbin "baserom.dol", 0x394610, 0x60
.global lbl_80398570
lbl_80398570:
	.incbin "baserom.dol", 0x394670, 0xB0
.global lbl_80398620
lbl_80398620:
	.incbin "baserom.dol", 0x394720, 0x10
.global lbl_80398630
lbl_80398630:
	.incbin "baserom.dol", 0x394730, 0x10
.global lbl_80398640
lbl_80398640:
	.incbin "baserom.dol", 0x394740, 0x38
.global lbl_80398678
lbl_80398678:
	.incbin "baserom.dol", 0x394778, 0x18
.global lbl_80398690
lbl_80398690:
	.incbin "baserom.dol", 0x394790, 0xA8
.global lbl_80398738
lbl_80398738:
	.incbin "baserom.dol", 0x394838, 0x10
.global lbl_80398748
lbl_80398748:
	.incbin "baserom.dol", 0x394848, 0x18
.global lbl_80398760
lbl_80398760:
	.incbin "baserom.dol", 0x394860, 0x38
.global lbl_80398798
lbl_80398798:
	.incbin "baserom.dol", 0x394898, 0x140
.global lbl_803988D8
lbl_803988D8:
	.incbin "baserom.dol", 0x3949D8, 0x128
.global lbl_80398A00
lbl_80398A00:
	.incbin "baserom.dol", 0x394B00, 0x40
.global lbl_80398A40
lbl_80398A40:
	.incbin "baserom.dol", 0x394B40, 0x1B0
.global lbl_80398BF0
lbl_80398BF0:
	.incbin "baserom.dol", 0x394CF0, 0x48
.global lbl_80398C38
lbl_80398C38:
	.incbin "baserom.dol", 0x394D38, 0x124
.global lbl_80398D5C
lbl_80398D5C:
	.incbin "baserom.dol", 0x394E5C, 0x84
.global lbl_80398DE0
lbl_80398DE0:
	.incbin "baserom.dol", 0x394EE0, 0xA8
.global lbl_80398E88
lbl_80398E88:
	.incbin "baserom.dol", 0x394F88, 0xE0
.global lbl_80398F68
lbl_80398F68:
	.incbin "baserom.dol", 0x395068, 0x20
.global lbl_80398F88
lbl_80398F88:
	.incbin "baserom.dol", 0x395088, 0xA8
.global lbl_80399030
lbl_80399030:
	.incbin "baserom.dol", 0x395130, 0x124
.global lbl_80399154
lbl_80399154:
	.incbin "baserom.dol", 0x395254, 0x84
.global lbl_803991D8
lbl_803991D8:
	.incbin "baserom.dol", 0x3952D8, 0xA8
.global lbl_80399280
lbl_80399280:
	.incbin "baserom.dol", 0x395380, 0x58
.global lbl_803992D8
lbl_803992D8:
	.incbin "baserom.dol", 0x3953D8, 0x70
.global lbl_80399348
lbl_80399348:
	.incbin "baserom.dol", 0x395448, 0x1C
.global lbl_80399364
lbl_80399364:
	.incbin "baserom.dol", 0x395464, 0x1C
.global lbl_80399380
lbl_80399380:
	.incbin "baserom.dol", 0x395480, 0xC
.global lbl_8039938C
lbl_8039938C:
	.incbin "baserom.dol", 0x39548C, 0x10
.global lbl_8039939C
lbl_8039939C:
	.incbin "baserom.dol", 0x39549C, 0x14
.global lbl_803993B0
lbl_803993B0:
	.incbin "baserom.dol", 0x3954B0, 0x40
.global lbl_803993F0
lbl_803993F0:
	.incbin "baserom.dol", 0x3954F0, 0x74
.global lbl_80399464
lbl_80399464:
	.incbin "baserom.dol", 0x395564, 0xC
.global lbl_80399470
lbl_80399470:
	.incbin "baserom.dol", 0x395570, 0x4C
.global lbl_803994BC
lbl_803994BC:
	.incbin "baserom.dol", 0x3955BC, 0x1C
.global lbl_803994D8
lbl_803994D8:
	.incbin "baserom.dol", 0x3955D8, 0x1C
.global lbl_803994F4
lbl_803994F4:
	.incbin "baserom.dol", 0x3955F4, 0x34
.global lbl_80399528
lbl_80399528:
	.incbin "baserom.dol", 0x395628, 0x10
.global lbl_80399538
lbl_80399538:
	.incbin "baserom.dol", 0x395638, 0x28
.global lbl_80399560
lbl_80399560:
	.incbin "baserom.dol", 0x395660, 0x18
.global lbl_80399578
lbl_80399578:
	.incbin "baserom.dol", 0x395678, 0xC
.global lbl_80399584
lbl_80399584:
	.incbin "baserom.dol", 0x395684, 0x38
.global lbl_803995BC
lbl_803995BC:
	.incbin "baserom.dol", 0x3956BC, 0xA4
.global lbl_80399660
lbl_80399660:
	.incbin "baserom.dol", 0x395760, 0x18
.global lbl_80399678
lbl_80399678:
	.incbin "baserom.dol", 0x395778, 0x2C
.global lbl_803996A4
lbl_803996A4:
	.incbin "baserom.dol", 0x3957A4, 0x1C
.global lbl_803996C0
lbl_803996C0:
	.incbin "baserom.dol", 0x3957C0, 0x1C
.global lbl_803996DC
lbl_803996DC:
	.incbin "baserom.dol", 0x3957DC, 0x1C
.global lbl_803996F8
lbl_803996F8:
	.incbin "baserom.dol", 0x3957F8, 0x1C
.global lbl_80399714
lbl_80399714:
	.incbin "baserom.dol", 0x395814, 0x1C
.global lbl_80399730
lbl_80399730:
	.incbin "baserom.dol", 0x395830, 0x28
.global lbl_80399758
lbl_80399758:
	.incbin "baserom.dol", 0x395858, 0x80
.global lbl_803997D8
lbl_803997D8:
	.incbin "baserom.dol", 0x3958D8, 0x290
.global lbl_80399A68
lbl_80399A68:
	.incbin "baserom.dol", 0x395B68, 0xC
.global lbl_80399A74
lbl_80399A74:
	.incbin "baserom.dol", 0x395B74, 0x144
.global lbl_80399BB8
lbl_80399BB8:
	.incbin "baserom.dol", 0x395CB8, 0x1370
.global lbl_8039AF28
lbl_8039AF28:
	.incbin "baserom.dol", 0x397028, 0x38
.global lbl_8039AF60
lbl_8039AF60:
	.incbin "baserom.dol", 0x397060, 0x170
.global lbl_8039B0D0
lbl_8039B0D0:
	.incbin "baserom.dol", 0x3971D0, 0xC0
.global lbl_8039B190
lbl_8039B190:
	.incbin "baserom.dol", 0x397290, 0x10
.global lbl_8039B1A0
lbl_8039B1A0:
	.incbin "baserom.dol", 0x3972A0, 0x18
.global lbl_8039B1B8
lbl_8039B1B8:
	.incbin "baserom.dol", 0x3972B8, 0x18
.global lbl_8039B1D0
lbl_8039B1D0:
	.incbin "baserom.dol", 0x3972D0, 0xD0
.global lbl_8039B2A0
lbl_8039B2A0:
	.incbin "baserom.dol", 0x3973A0, 0x68
.global lbl_8039B308
lbl_8039B308:
	.incbin "baserom.dol", 0x397408, 0x88
.global lbl_8039B390
lbl_8039B390:
	.incbin "baserom.dol", 0x397490, 0x44
.global lbl_8039B3D4
lbl_8039B3D4:
	.incbin "baserom.dol", 0x3974D4, 0x1C
.global lbl_8039B3F0
lbl_8039B3F0:
	.incbin "baserom.dol", 0x3974F0, 0x58
.global lbl_8039B448
lbl_8039B448:
	.incbin "baserom.dol", 0x397548, 0x3C
.global lbl_8039B484
lbl_8039B484:
	.incbin "baserom.dol", 0x397584, 0x3C
.global lbl_8039B4C0
lbl_8039B4C0:
	.incbin "baserom.dol", 0x3975C0, 0x3C
.global lbl_8039B4FC
lbl_8039B4FC:
	.incbin "baserom.dol", 0x3975FC, 0x3C
.global lbl_8039B538
lbl_8039B538:
	.incbin "baserom.dol", 0x397638, 0x20
.global lbl_8039B558
lbl_8039B558:
	.incbin "baserom.dol", 0x397658, 0xF4
.global lbl_8039B64C
lbl_8039B64C:
	.incbin "baserom.dol", 0x39774C, 0xF4
.global lbl_8039B740
lbl_8039B740:
	.incbin "baserom.dol", 0x397840, 0x40
.global lbl_8039B780
lbl_8039B780:
	.incbin "baserom.dol", 0x397880, 0x50
.global lbl_8039B7D0
lbl_8039B7D0:
	.incbin "baserom.dol", 0x3978D0, 0x28
.global lbl_8039B7F8
lbl_8039B7F8:
	.incbin "baserom.dol", 0x3978F8, 0x20
.global lbl_8039B818
lbl_8039B818:
	.incbin "baserom.dol", 0x397918, 0x5C
.global lbl_8039B874
lbl_8039B874:
	.incbin "baserom.dol", 0x397974, 0x94
.global lbl_8039B908
lbl_8039B908:
	.incbin "baserom.dol", 0x397A08, 0xC
.global lbl_8039B914
lbl_8039B914:
	.incbin "baserom.dol", 0x397A14, 0xC
.global lbl_8039B920
lbl_8039B920:
	.incbin "baserom.dol", 0x397A20, 0x60
.global lbl_8039B980
lbl_8039B980:
	.incbin "baserom.dol", 0x397A80, 0x50
.global lbl_8039B9D0
lbl_8039B9D0:
	.incbin "baserom.dol", 0x397AD0, 0xC
.global lbl_8039B9DC
lbl_8039B9DC:
	.incbin "baserom.dol", 0x397ADC, 0xC
.global lbl_8039B9E8
lbl_8039B9E8:
	.incbin "baserom.dol", 0x397AE8, 0xD8
.global lbl_8039BAC0
lbl_8039BAC0:
	.incbin "baserom.dol", 0x397BC0, 0x30
.global lbl_8039BAF0
lbl_8039BAF0:
	.incbin "baserom.dol", 0x397BF0, 0x1F0
.global lbl_8039BCE0
lbl_8039BCE0:
	.incbin "baserom.dol", 0x397DE0, 0x200
.global lbl_8039BEE0
lbl_8039BEE0:
	.incbin "baserom.dol", 0x397FE0, 0x10
.global lbl_8039BEF0
lbl_8039BEF0:
	.incbin "baserom.dol", 0x397FF0, 0x80
.global lbl_8039BF70
lbl_8039BF70:
	.incbin "baserom.dol", 0x398070, 0x238
.global lbl_8039C1A8
lbl_8039C1A8:
	.incbin "baserom.dol", 0x3982A8, 0x1B8
.global lbl_8039C360
lbl_8039C360:
	.incbin "baserom.dol", 0x398460, 0x28
.global lbl_8039C388
lbl_8039C388:
	.incbin "baserom.dol", 0x398488, 0x2DC
.global lbl_8039C664
lbl_8039C664:
	.incbin "baserom.dol", 0x398764, 0x44
.global lbl_8039C6A8
lbl_8039C6A8:
	.incbin "baserom.dol", 0x3987A8, 0x180
.global lbl_8039C828
lbl_8039C828:
	.incbin "baserom.dol", 0x398928, 0x990
.global lbl_8039D1B8
lbl_8039D1B8:
	.incbin "baserom.dol", 0x3992B8, 0x30
.global lbl_8039D1E8
lbl_8039D1E8:
	.incbin "baserom.dol", 0x3992E8, 0x10
.global lbl_8039D1F8
lbl_8039D1F8:
	.incbin "baserom.dol", 0x3992F8, 0xC
.global lbl_8039D204
lbl_8039D204:
	.incbin "baserom.dol", 0x399304, 0x30
.global lbl_8039D234
lbl_8039D234:
	.incbin "baserom.dol", 0x399334, 0x3C
.global lbl_8039D270
lbl_8039D270:
	.incbin "baserom.dol", 0x399370, 0x30
.global lbl_8039D2A0
lbl_8039D2A0:
	.incbin "baserom.dol", 0x3993A0, 0x30
.global lbl_8039D2D0
lbl_8039D2D0:
	.incbin "baserom.dol", 0x3993D0, 0xBA40
.global lbl_803A8D10
lbl_803A8D10:
	.incbin "baserom.dol", 0x3A4E10, 0x400
.global lbl_803A9110
lbl_803A9110:
	.incbin "baserom.dol", 0x3A5210, 0x14
.global lbl_803A9124
lbl_803A9124:
	.incbin "baserom.dol", 0x3A5224, 0x14
.global lbl_803A9138
lbl_803A9138:
	.incbin "baserom.dol", 0x3A5238, 0xC
.global lbl_803A9144
lbl_803A9144:
	.incbin "baserom.dol", 0x3A5244, 0x38
.global lbl_803A917C
lbl_803A917C:
	.incbin "baserom.dol", 0x3A527C, 0x38
.global lbl_803A91B4
lbl_803A91B4:
	.incbin "baserom.dol", 0x3A52B4, 0x24
.global lbl_803A91D8
lbl_803A91D8:
	.incbin "baserom.dol", 0x3A52D8, 0x2C
.global lbl_803A9204
lbl_803A9204:
	.incbin "baserom.dol", 0x3A5304, 0x1C
.global lbl_803A9220
lbl_803A9220:
	.incbin "baserom.dol", 0x3A5320, 0x28
.global lbl_803A9248
lbl_803A9248:
	.incbin "baserom.dol", 0x3A5348, 0x1F8
.global lbl_803A9440
lbl_803A9440:
	.incbin "baserom.dol", 0x3A5540, 0x118
.global lbl_803A9558
lbl_803A9558:
	.incbin "baserom.dol", 0x3A5658, 0x28
.global lbl_803A9580
lbl_803A9580:
	.incbin "baserom.dol", 0x3A5680, 0x48
.global lbl_803A95C8
lbl_803A95C8:
	.incbin "baserom.dol", 0x3A56C8, 0x620
.global lbl_803A9BE8
lbl_803A9BE8:
	.incbin "baserom.dol", 0x3A5CE8, 0x48
.global lbl_803A9C30
lbl_803A9C30:
	.incbin "baserom.dol", 0x3A5D30, 0x1A4
.global lbl_803A9DD4
lbl_803A9DD4:
	.incbin "baserom.dol", 0x3A5ED4, 0x34
.global lbl_803A9E08
lbl_803A9E08:
	.incbin "baserom.dol", 0x3A5F08, 0x10
.global lbl_803A9E18
lbl_803A9E18:
	.incbin "baserom.dol", 0x3A5F18, 0x20
.global lbl_803A9E38
lbl_803A9E38:
	.incbin "baserom.dol", 0x3A5F38, 0x7C
.global lbl_803A9EB4
lbl_803A9EB4:
	.incbin "baserom.dol", 0x3A5FB4, 0x174
.global lbl_803AA028
lbl_803AA028:
	.incbin "baserom.dol", 0x3A6128, 0x20
.global lbl_803AA048
lbl_803AA048:
	.incbin "baserom.dol", 0x3A6148, 0x20
.global lbl_803AA068
lbl_803AA068:
	.incbin "baserom.dol", 0x3A6168, 0x590
.global lbl_803AA5F8
lbl_803AA5F8:
	.incbin "baserom.dol", 0x3A66F8, 0xDC
.global lbl_803AA6D4
lbl_803AA6D4:
	.incbin "baserom.dol", 0x3A67D4, 0x10
.global lbl_803AA6E4
lbl_803AA6E4:
	.incbin "baserom.dol", 0x3A67E4, 0x10
.global lbl_803AA6F4
lbl_803AA6F4:
	.incbin "baserom.dol", 0x3A67F4, 0x24
.global lbl_803AA718
lbl_803AA718:
	.incbin "baserom.dol", 0x3A6818, 0x28
.global lbl_803AA740
lbl_803AA740:
	.incbin "baserom.dol", 0x3A6840, 0x28
.global lbl_803AA768
lbl_803AA768:
	.incbin "baserom.dol", 0x3A6868, 0x20
.global lbl_803AA788
lbl_803AA788:
	.incbin "baserom.dol", 0x3A6888, 0x10C
.global lbl_803AA894
lbl_803AA894:
	.incbin "baserom.dol", 0x3A6994, 0x100
.global lbl_803AA994
lbl_803AA994:
	.incbin "baserom.dol", 0x3A6A94, 0xC
.global lbl_803AA9A0
lbl_803AA9A0:
	.incbin "baserom.dol", 0x3A6AA0, 0x18
.global lbl_803AA9B8
lbl_803AA9B8:
	.incbin "baserom.dol", 0x3A6AB8, 0x14
.global lbl_803AA9CC
lbl_803AA9CC:
	.incbin "baserom.dol", 0x3A6ACC, 0x10
.global lbl_803AA9DC
lbl_803AA9DC:
	.incbin "baserom.dol", 0x3A6ADC, 0x1C
.global lbl_803AA9F8
lbl_803AA9F8:
	.incbin "baserom.dol", 0x3A6AF8, 0x34
.global lbl_803AAA2C
lbl_803AAA2C:
	.incbin "baserom.dol", 0x3A6B2C, 0x30
.global lbl_803AAA5C
lbl_803AAA5C:
	.incbin "baserom.dol", 0x3A6B5C, 0x18
.global lbl_803AAA74
lbl_803AAA74:
	.incbin "baserom.dol", 0x3A6B74, 0x1C
.global lbl_803AAA90
lbl_803AAA90:
	.incbin "baserom.dol", 0x3A6B90, 0x18
.global lbl_803AAAA8
lbl_803AAAA8:
	.incbin "baserom.dol", 0x3A6BA8, 0x1C
.global lbl_803AAAC4
lbl_803AAAC4:
	.incbin "baserom.dol", 0x3A6BC4, 0x1C
.global lbl_803AAAE0
lbl_803AAAE0:
	.incbin "baserom.dol", 0x3A6BE0, 0x1C
.global lbl_803AAAFC
lbl_803AAAFC:
	.incbin "baserom.dol", 0x3A6BFC, 0xBC
.global lbl_803AABB8
lbl_803AABB8:
	.incbin "baserom.dol", 0x3A6CB8, 0x5C
.global lbl_803AAC14
lbl_803AAC14:
	.incbin "baserom.dol", 0x3A6D14, 0x138
.global lbl_803AAD4C
lbl_803AAD4C:
	.incbin "baserom.dol", 0x3A6E4C, 0x18
.global lbl_803AAD64
lbl_803AAD64:
	.incbin "baserom.dol", 0x3A6E64, 0x27C
.global lbl_803AAFE0
lbl_803AAFE0:
	.incbin "baserom.dol", 0x3A70E0, 0x1A0
.global lbl_803AB180
lbl_803AB180:
	.incbin "baserom.dol", 0x3A7280, 0x1C
.global lbl_803AB19C
lbl_803AB19C:
	.incbin "baserom.dol", 0x3A729C, 0x2C4
.global lbl_803AB460
lbl_803AB460:
	.incbin "baserom.dol", 0x3A7560, 0x200
.global lbl_803AB660
lbl_803AB660:
	.incbin "baserom.dol", 0x3A7760, 0x40
.global lbl_803AB6A0
lbl_803AB6A0:
	.incbin "baserom.dol", 0x3A77A0, 0x18
.global lbl_803AB6B8
lbl_803AB6B8:
	.incbin "baserom.dol", 0x3A77B8, 0x14
.global lbl_803AB6CC
lbl_803AB6CC:
	.incbin "baserom.dol", 0x3A77CC, 0x5C
