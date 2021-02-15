.include "macros.inc"

.section .data, "wa"  # 0x80393A80 - 0x803CAF00

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

.global __vt__Q44nw4r3snd6detail5Voice
__vt__Q44nw4r3snd6detail5Voice:
	.long 0
	.long 0
	.long __dt__Q44nw4r3snd6detail5VoiceFv
	.long InvalidateData__Q44nw4r3snd6detail5VoiceFPCvPCv
	.long InvalidateWaveData__Q44nw4r3snd6detail5VoiceFPCvPCv
.balign 0x8

# I think this is PanTableTable__Q44nw4r3snd6detail4Util, unsure though
.global lbl_80396468
lbl_80396468:
	.long 0x80376F3C
	.long 0x80377340
	.long 0x80377744
	.long 0
.balign 0x8

.global __vt__Q44nw4r3snd6detail9WaveSound
__vt__Q44nw4r3snd6detail9WaveSound:
	.long 0
	.long 0
	.long GetRuntimeTypeInfo__Q44nw4r3snd6detail9WaveSoundCFv
	.long __dt__Q44nw4r3snd6detail9WaveSoundFv
	.long Update__Q44nw4r3snd6detail10BasicSoundFv
	.long StartPrepared__Q44nw4r3snd6detail10BasicSoundFv
	.long Stop__Q44nw4r3snd6detail10BasicSoundFi
	.long Pause__Q44nw4r3snd6detail10BasicSoundFbi
	.long SetAutoStopCounter__Q44nw4r3snd6detail10BasicSoundFi
	.long FadeIn__Q44nw4r3snd6detail10BasicSoundFi
	.long Shutdown__Q44nw4r3snd6detail9WaveSoundFv
	.long IsPrepared__Q44nw4r3snd6detail9WaveSoundCFv
	.long IsPause__Q44nw4r3snd6detail10BasicSoundCFv
	.long SetInitialVolume__Q44nw4r3snd6detail10BasicSoundFf
	.long SetVolume__Q44nw4r3snd6detail10BasicSoundFfi
	.long SetPitch__Q44nw4r3snd6detail10BasicSoundFf
	.long SetPan__Q44nw4r3snd6detail10BasicSoundFf
	.long SetSurroundPan__Q44nw4r3snd6detail10BasicSoundFf
	.long SetLpfFreq__Q44nw4r3snd6detail10BasicSoundFf
	.long SetPlayerPriority__Q44nw4r3snd6detail9WaveSoundFi
	.long SetRemoteFilter__Q44nw4r3snd6detail10BasicSoundFi
	.long SetPanMode__Q44nw4r3snd6detail10BasicSoundFQ44nw4r3snd6detail7PanMode
	.long SetPanCurve__Q44nw4r3snd6detail10BasicSoundFQ44nw4r3snd6detail8PanCurve
	.long IsAttachedTempSpecialHandle__Q44nw4r3snd6detail9WaveSoundFv
	.long DetachTempSpecialHandle__Q44nw4r3snd6detail9WaveSoundFv
	.long InitParam__Q44nw4r3snd6detail10BasicSoundFv
	.long GetBasicPlayer__Q44nw4r3snd6detail9WaveSoundFv
	.long GetBasicPlayer__Q44nw4r3snd6detail9WaveSoundCFv

.global __vt__Q44nw4r3snd6detail9WsdPlayer
__vt__Q44nw4r3snd6detail9WsdPlayer:
	.long 0
	.long 0
	.long ______dt__Q44nw4r3snd6detail9WsdPlayerFv
	.long Start__Q44nw4r3snd6detail9WsdPlayerFv
	.long Stop__Q44nw4r3snd6detail9WsdPlayerFv
	.long Pause__Q44nw4r3snd6detail9WsdPlayerFb
	.long IsActive__Q44nw4r3snd6detail9WsdPlayerCFv
	.long IsStarted__Q44nw4r3snd6detail9WsdPlayerCFv
	.long IsPause__Q44nw4r3snd6detail9WsdPlayerCFv
	.long 0
	.long 0
	.long $$2116$$2__dt__Q44nw4r3snd6detail9WsdPlayerFv
	.long $$2116$$2InvalidateData__Q44nw4r3snd6detail9WsdPlayerFPCvPCv
	.long $$2116$$2InvalidateWaveData__Q44nw4r3snd6detail9WsdPlayerFPCvPCv
	.long 0
	.long 0
	.long $$2128$$2__dt__Q44nw4r3snd6detail9WsdPlayerFv
	.long $$2128$$2OnUpdateFrameSoundThread__Q44nw4r3snd6detail9WsdPlayerFv
	.long OnUpdateVoiceSoundThread__Q54nw4r3snd6detail11SoundThread14PlayerCallbackFv
	.long $$2128$$2OnShutdownSoundThread__Q44nw4r3snd6detail9WsdPlayerFv
	.long InvalidateData__Q44nw4r3snd6detail9WsdPlayerFPCvPCv
	.long InvalidateWaveData__Q44nw4r3snd6detail9WsdPlayerFPCvPCv
	.long OnUpdateFrameSoundThread__Q44nw4r3snd6detail9WsdPlayerFv
	.long OnShutdownSoundThread__Q44nw4r3snd6detail9WsdPlayerFv
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
.balign 0x8

# ResNameData_Models__Q34nw4r3g3d25@unnamed@g3d_resfile_cpp@
.global ResNameData_Models__Q34nw4r3g3d25$$2unnamed$$2g3d_resfile_cpp$$2
ResNameData_Models__Q34nw4r3g3d25$$2unnamed$$2g3d_resfile_cpp$$2:
	.long 0xE # str length
	# ResNameData name string has max len of 27 it seems
	# Maybe the structure is supposed to align to 32?
	.string "3DModels(NW4R)"
	.balign 16

# ResNameData_Pltts__Q34nw4r3g3d25@unnamed@g3d_resfile_cpp@
.global ResNameData_Pltts__Q34nw4r3g3d25$$2unnamed$$2g3d_resfile_cpp$$2
 ResNameData_Pltts__Q34nw4r3g3d25$$2unnamed$$2g3d_resfile_cpp$$2:
	.long 0xE
	.string "Palettes(NW4R)"
	.balign 16

# ResNameData_Textures__Q34nw4r3g3d25@unnamed@g3d_resfile_cpp@
.global ResNameData_Textures__Q34nw4r3g3d25$$2unnamed$$2g3d_resfile_cpp$$2
ResNameData_Textures__Q34nw4r3g3d25$$2unnamed$$2g3d_resfile_cpp$$2:
	.long 0xE
	.string "Textures(NW4R)"
	.balign 16

# ResNameData_AnmChr__Q34nw4r3g3d25@unnamed@g3d_resfile_cpp@
.global ResNameData_AnmChr__Q34nw4r3g3d25$$2unnamed$$2g3d_resfile_cpp$$2
ResNameData_AnmChr__Q34nw4r3g3d25$$2unnamed$$2g3d_resfile_cpp$$2:
	.long 0xC
	.string "AnmChr(NW4R)"
	.balign 16

# ResNameData_AnmVis__Q34nw4r3g3d25@unnamed@g3d_resfile_cpp@
.global ResNameData_AnmVis__Q34nw4r3g3d25$$2unnamed$$2g3d_resfile_cpp$$2
ResNameData_AnmVis__Q34nw4r3g3d25$$2unnamed$$2g3d_resfile_cpp$$2:
	.long 0xC
	.string "AnmVis(NW4R)"
	.balign 16

# ResNameData_AnmClr__Q34nw4r3g3d25@unnamed@g3d_resfile_cpp@
.global ResNameData_AnmClr__Q34nw4r3g3d25$$2unnamed$$2g3d_resfile_cpp$$2
ResNameData_AnmClr__Q34nw4r3g3d25$$2unnamed$$2g3d_resfile_cpp$$2:
	.long 0xC
	.string "AnmClr(NW4R)"
	.balign 16

# ResNameData_AnmTexPat__Q34nw4r3g3d25@unnamed@g3d_resfile_cpp@
.global ResNameData_AnmTexPat__Q34nw4r3g3d25$$2unnamed$$2g3d_resfile_cpp$$2
ResNameData_AnmTexPat__Q34nw4r3g3d25$$2unnamed$$2g3d_resfile_cpp$$2:
	.long 0xF
	.string "AnmTexPat(NW4R)"
	.balign 16

# ResNameData_AnmTexSrt__Q34nw4r3g3d25@unnamed@g3d_resfile_cpp@
.global ResNameData_AnmTexSrt__Q34nw4r3g3d25$$2unnamed$$2g3d_resfile_cpp$$2
ResNameData_AnmTexSrt__Q34nw4r3g3d25$$2unnamed$$2g3d_resfile_cpp$$2:
	.long 0xF
	.string "AnmTexSrt(NW4R)"
	.balign 16

# ResNameData_AnmShp__Q34nw4r3g3d25@unnamed@g3d_resfile_cpp@
.global ResNameData_AnmShp__Q34nw4r3g3d25$$2unnamed$$2g3d_resfile_cpp$$2
ResNameData_AnmShp__Q34nw4r3g3d25$$2unnamed$$2g3d_resfile_cpp$$2:
	.long 0xC
	.string "AnmShp(NW4R)"
	.balign 16

# ResNameData_AnmScn__Q34nw4r3g3d25@unnamed@g3d_resfile_cpp@
.global ResNameData_AnmScn__Q34nw4r3g3d25$$2unnamed$$2g3d_resfile_cpp$$2
ResNameData_AnmScn__Q34nw4r3g3d25$$2unnamed$$2g3d_resfile_cpp$$2:
	.long 0xC
	.string "AnmScn(NW4R)"
	.balign 0x10

# ResNameData_Ext__Q34nw4r3g3d25@unnamed@g3d_resfile_cpp@ (UNUSED)
.global ResNameData_Ext__Q34nw4r3g3d25$$2unnamed$$2g3d_resfile_cpp$$2
ResNameData_Ext__Q34nw4r3g3d25$$2unnamed$$2g3d_resfile_cpp$$2:
	.long 0x8
	.string "External"
	.fill 0x13

.global switch_803966C0
switch_803966C0:
    .long 0x80056124
    .long 0x80056130
    .long 0x8005613c
    .long 0x80056148
    .long 0x80056164
    .long 0x8005616c
    .long 0x80056174
    .long 0x8005617c
    .long 0x80056184
    .long 0x8005618c
    .long 0x80056194
    .long 0x8005619c
    .long 0x800561a4
    .long 0x800561ac
    .long 0x800561b4
    .long 0x800561bc
    .long 0x800561c4
    .long 0x800561cc
    .long 0x800561d4
    .long 0x80056154
    .long 0x8005615c
    .long 0
    .long 0
    .long 0

.global ResNameData_LightSet
ResNameData_LightSet:
	.long 0xE
	.string "LightSet(NW4R)"
	.balign 16

.global ResNameData_AmbLights
ResNameData_AmbLights:
	.long 0xF
	.string "AmbLights(NW4R)"
	.balign 16

.global ResNameData_Lights
ResNameData_Lights:
	.long 0xC
	.string "Lights(NW4R)"
	.balign 16

.global __vt__Q34nw4r3g3d12AnmObjVisRes
__vt__Q34nw4r3g3d12AnmObjVisRes:
    .long 0
    .long 0
    .long IsDerivedFrom__Q34nw4r3g3d12AnmObjVisResCFQ44nw4r3g3d6G3dObj7TypeObj
    .long G3dProc__Q34nw4r3g3d9AnmObjVisFUlUlPv
    .long __dt__Q34nw4r3g3d12AnmObjVisResFv
    .long GetTypeObj__Q34nw4r3g3d12AnmObjVisResCFv
    .long GetTypeName__Q34nw4r3g3d12AnmObjVisResCFv
    .long SetFrame__Q34nw4r3g3d12AnmObjVisResFf
    .long GetFrame__Q34nw4r3g3d12AnmObjVisResCFv
    .long UpdateFrame__Q34nw4r3g3d12AnmObjVisResFv
    .long SetUpdateRate__Q34nw4r3g3d12AnmObjVisResFf
    .long GetUpdateRate__Q34nw4r3g3d12AnmObjVisResCFv
    .long Bind__Q34nw4r3g3d12AnmObjVisResFQ34nw4r3g3d6ResMdl
    .long Release__Q34nw4r3g3d9AnmObjVisFv
    .long GetResult__Q34nw4r3g3d12AnmObjVisResFUl
    .long Attach__Q34nw4r3g3d9AnmObjVisFiPQ34nw4r3g3d12AnmObjVisRes
    .long Detach__Q34nw4r3g3d9AnmObjVisFi

.global __vt__Q34nw4r3g3d11AnmObjVisOR
__vt__Q34nw4r3g3d11AnmObjVisOR:
    .long 0
    .long 0
    .long IsDerivedFrom__Q34nw4r3g3d11AnmObjVisORCFQ44nw4r3g3d6G3dObj7TypeObj
    .long G3dProc__Q34nw4r3g3d13AnmObjVisNodeFUlUlPv
    .long __dt__Q34nw4r3g3d11AnmObjVisORFv
    .long GetTypeObj__Q34nw4r3g3d11AnmObjVisORCFv
    .long GetTypeName__Q34nw4r3g3d11AnmObjVisORCFv
    .long SetFrame__Q34nw4r3g3d13AnmObjVisNodeFf
    .long GetFrame__Q34nw4r3g3d13AnmObjVisNodeCFv
    .long UpdateFrame__Q34nw4r3g3d13AnmObjVisNodeFv
    .long SetUpdateRate__Q34nw4r3g3d13AnmObjVisNodeFf
    .long GetUpdateRate__Q34nw4r3g3d13AnmObjVisNodeCFv
    .long Bind__Q34nw4r3g3d13AnmObjVisNodeFQ34nw4r3g3d6ResMdl
    .long Release__Q34nw4r3g3d13AnmObjVisNodeFv
    .long GetResult__Q34nw4r3g3d11AnmObjVisORFUl
    .long Attach__Q34nw4r3g3d13AnmObjVisNodeFiPQ34nw4r3g3d12AnmObjVisRes
    .long Detach__Q34nw4r3g3d13AnmObjVisNodeFi

.global __vt__Q34nw4r3g3d13AnmObjVisNode
__vt__Q34nw4r3g3d13AnmObjVisNode:
    .long 0
    .long 0
    .long IsDerivedFrom__Q34nw4r3g3d13AnmObjVisNodeCFQ44nw4r3g3d6G3dObj7TypeObj
    .long G3dProc__Q34nw4r3g3d13AnmObjVisNodeFUlUlPv
    .long __dt__Q34nw4r3g3d13AnmObjVisNodeFv
    .long GetTypeObj__Q34nw4r3g3d13AnmObjVisNodeCFv
    .long GetTypeName__Q34nw4r3g3d13AnmObjVisNodeCFv
    .long SetFrame__Q34nw4r3g3d13AnmObjVisNodeFf
    .long GetFrame__Q34nw4r3g3d13AnmObjVisNodeCFv
    .long UpdateFrame__Q34nw4r3g3d13AnmObjVisNodeFv
    .long SetUpdateRate__Q34nw4r3g3d13AnmObjVisNodeFf
    .long GetUpdateRate__Q34nw4r3g3d13AnmObjVisNodeCFv
    .long Bind__Q34nw4r3g3d13AnmObjVisNodeFQ34nw4r3g3d6ResMdl
    .long Release__Q34nw4r3g3d13AnmObjVisNodeFv
    .long 0
    .long Attach__Q34nw4r3g3d13AnmObjVisNodeFiPQ34nw4r3g3d12AnmObjVisRes
    .long Detach__Q34nw4r3g3d13AnmObjVisNodeFi

.global __vt__Q34nw4r3g3d9AnmObjVis
__vt__Q34nw4r3g3d9AnmObjVis:
    .long 0
    .long 0
    .long IsDerivedFrom__Q34nw4r3g3d9AnmObjVisCFQ44nw4r3g3d6G3dObj7TypeObj
    .long G3dProc__Q34nw4r3g3d9AnmObjVisFUlUlPv
    .long __dt__Q34nw4r3g3d9AnmObjVisFv
    .long GetTypeObj__Q34nw4r3g3d9AnmObjVisCFv
    .long GetTypeName__Q34nw4r3g3d9AnmObjVisCFv
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long Release__Q34nw4r3g3d9AnmObjVisFv
    .long 0
    .long Attach__Q34nw4r3g3d9AnmObjVisFiPQ34nw4r3g3d12AnmObjVisRes
    .long Detach__Q34nw4r3g3d9AnmObjVisFi

.global __vt__Q34nw4r3g3d15AnmObjMatClrRes
__vt__Q34nw4r3g3d15AnmObjMatClrRes:
    .long 0
    .long 0
    .long IsDerivedFrom__Q34nw4r3g3d15AnmObjMatClrResCFQ44nw4r3g3d6G3dObj7TypeObj
    .long G3dProc__Q34nw4r3g3d15AnmObjMatClrResFUlUlPv
    .long __dt__Q34nw4r3g3d15AnmObjMatClrResFv
    .long GetTypeObj__Q34nw4r3g3d15AnmObjMatClrResCFv
    .long GetTypeName__Q34nw4r3g3d15AnmObjMatClrResCFv
    .long SetFrame__Q34nw4r3g3d15AnmObjMatClrResFf
    .long GetFrame__Q34nw4r3g3d15AnmObjMatClrResCFv
    .long UpdateFrame__Q34nw4r3g3d15AnmObjMatClrResFv
    .long SetUpdateRate__Q34nw4r3g3d15AnmObjMatClrResFf
    .long GetUpdateRate__Q34nw4r3g3d15AnmObjMatClrResCFv
    .long Bind__Q34nw4r3g3d15AnmObjMatClrResFQ34nw4r3g3d6ResMdl
    .long Release__Q34nw4r3g3d12AnmObjMatClrFv
    .long GetResult__Q34nw4r3g3d15AnmObjMatClrResFPQ34nw4r3g3d12ClrAnmResultUl
    .long Attach__Q34nw4r3g3d12AnmObjMatClrFiPQ34nw4r3g3d15AnmObjMatClrRes
    .long Detach__Q34nw4r3g3d12AnmObjMatClrFi
    .long DetachAll__Q34nw4r3g3d12AnmObjMatClrFv

.global __vt__Q34nw4r3g3d20AnmObjMatClrOverride
__vt__Q34nw4r3g3d20AnmObjMatClrOverride:
    .long 0
    .long 0
    .long IsDerivedFrom__Q34nw4r3g3d20AnmObjMatClrOverrideCFQ44nw4r3g3d6G3dObj7TypeObj
    .long G3dProc__Q34nw4r3g3d16AnmObjMatClrNodeFUlUlPv
    .long __dt__Q34nw4r3g3d20AnmObjMatClrOverrideFv
    .long GetTypeObj__Q34nw4r3g3d20AnmObjMatClrOverrideCFv
    .long GetTypeName__Q34nw4r3g3d20AnmObjMatClrOverrideCFv
    .long SetFrame__Q34nw4r3g3d16AnmObjMatClrNodeFf
    .long GetFrame__Q34nw4r3g3d16AnmObjMatClrNodeCFv
    .long UpdateFrame__Q34nw4r3g3d16AnmObjMatClrNodeFv
    .long SetUpdateRate__Q34nw4r3g3d16AnmObjMatClrNodeFf
    .long GetUpdateRate__Q34nw4r3g3d16AnmObjMatClrNodeCFv
    .long Bind__Q34nw4r3g3d16AnmObjMatClrNodeFQ34nw4r3g3d6ResMdl
    .long Release__Q34nw4r3g3d16AnmObjMatClrNodeFv
    .long GetResult__Q34nw4r3g3d20AnmObjMatClrOverrideFPQ34nw4r3g3d12ClrAnmResultUl
    .long Attach__Q34nw4r3g3d16AnmObjMatClrNodeFiPQ34nw4r3g3d15AnmObjMatClrRes
    .long Detach__Q34nw4r3g3d16AnmObjMatClrNodeFi
    .long DetachAll__Q34nw4r3g3d16AnmObjMatClrNodeFv

.global __vt__Q34nw4r3g3d16AnmObjMatClrNode
__vt__Q34nw4r3g3d16AnmObjMatClrNode:
    .long 0
    .long 0
    .long IsDerivedFrom__Q34nw4r3g3d16AnmObjMatClrNodeCFQ44nw4r3g3d6G3dObj7TypeObj
    .long G3dProc__Q34nw4r3g3d16AnmObjMatClrNodeFUlUlPv
    .long __dt__Q34nw4r3g3d16AnmObjMatClrNodeFv
    .long GetTypeObj__Q34nw4r3g3d16AnmObjMatClrNodeCFv
    .long GetTypeName__Q34nw4r3g3d16AnmObjMatClrNodeCFv
    .long SetFrame__Q34nw4r3g3d16AnmObjMatClrNodeFf
    .long GetFrame__Q34nw4r3g3d16AnmObjMatClrNodeCFv
    .long UpdateFrame__Q34nw4r3g3d16AnmObjMatClrNodeFv
    .long SetUpdateRate__Q34nw4r3g3d16AnmObjMatClrNodeFf
    .long GetUpdateRate__Q34nw4r3g3d16AnmObjMatClrNodeCFv
    .long Bind__Q34nw4r3g3d16AnmObjMatClrNodeFQ34nw4r3g3d6ResMdl
    .long Release__Q34nw4r3g3d16AnmObjMatClrNodeFv
    .long 0
    .long Attach__Q34nw4r3g3d16AnmObjMatClrNodeFiPQ34nw4r3g3d15AnmObjMatClrRes
    .long Detach__Q34nw4r3g3d16AnmObjMatClrNodeFi
    .long DetachAll__Q34nw4r3g3d16AnmObjMatClrNodeFv

.global __vt__Q34nw4r3g3d12AnmObjMatClr
__vt__Q34nw4r3g3d12AnmObjMatClr:
    .long 0
    .long 0
    .long IsDerivedFrom__Q34nw4r3g3d12AnmObjMatClrCFQ44nw4r3g3d6G3dObj7TypeObj
    .long 0
    .long __dt__Q34nw4r3g3d12AnmObjMatClrFv
    .long GetTypeObj__Q34nw4r3g3d12AnmObjMatClrCFv
    .long GetTypeName__Q34nw4r3g3d12AnmObjMatClrCFv
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long Release__Q34nw4r3g3d12AnmObjMatClrFv
    .long 0
    .long Attach__Q34nw4r3g3d12AnmObjMatClrFiPQ34nw4r3g3d15AnmObjMatClrRes
    .long Detach__Q34nw4r3g3d12AnmObjMatClrFi
    .long DetachAll__Q34nw4r3g3d12AnmObjMatClrFv

.global __vt__Q34nw4r3g3d15AnmObjTexPatRes
__vt__Q34nw4r3g3d15AnmObjTexPatRes:
    .long 0
    .long 0
    .long IsDerivedFrom__Q34nw4r3g3d15AnmObjTexPatResCFQ44nw4r3g3d6G3dObj7TypeObj
    .long G3dProc__Q34nw4r3g3d15AnmObjTexPatResFUlUlPv
    .long __dt__Q34nw4r3g3d15AnmObjTexPatResFv
    .long GetTypeObj__Q34nw4r3g3d15AnmObjTexPatResCFv
    .long GetTypeName__Q34nw4r3g3d15AnmObjTexPatResCFv
    .long SetFrame__Q34nw4r3g3d15AnmObjTexPatResFf
    .long GetFrame__Q34nw4r3g3d15AnmObjTexPatResCFv
    .long UpdateFrame__Q34nw4r3g3d15AnmObjTexPatResFv
    .long SetUpdateRate__Q34nw4r3g3d15AnmObjTexPatResFf
    .long GetUpdateRate__Q34nw4r3g3d15AnmObjTexPatResCFv
    .long Bind__Q34nw4r3g3d15AnmObjTexPatResFQ34nw4r3g3d6ResMdl
    .long Release__Q34nw4r3g3d12AnmObjTexPatFv
    .long GetResult__Q34nw4r3g3d15AnmObjTexPatResFPQ34nw4r3g3d15TexPatAnmResultUl
    .long Attach__Q34nw4r3g3d12AnmObjTexPatFiPQ34nw4r3g3d15AnmObjTexPatRes
    .long Detach__Q34nw4r3g3d12AnmObjTexPatFi
    .long DetachAll__Q34nw4r3g3d12AnmObjTexPatFv

.global __vt__Q34nw4r3g3d20AnmObjTexPatOverride
__vt__Q34nw4r3g3d20AnmObjTexPatOverride:
    .long 0
    .long 0
    .long IsDerivedFrom__Q34nw4r3g3d20AnmObjTexPatOverrideCFQ44nw4r3g3d6G3dObj7TypeObj
    .long G3dProc__Q34nw4r3g3d16AnmObjTexPatNodeFUlUlPv
    .long __dt__Q34nw4r3g3d20AnmObjTexPatOverrideFv
    .long GetTypeObj__Q34nw4r3g3d20AnmObjTexPatOverrideCFv
    .long GetTypeName__Q34nw4r3g3d20AnmObjTexPatOverrideCFv
    .long SetFrame__Q34nw4r3g3d16AnmObjTexPatNodeFf
    .long GetFrame__Q34nw4r3g3d16AnmObjTexPatNodeCFv
    .long UpdateFrame__Q34nw4r3g3d16AnmObjTexPatNodeFv
    .long SetUpdateRate__Q34nw4r3g3d16AnmObjTexPatNodeFf
    .long GetUpdateRate__Q34nw4r3g3d16AnmObjTexPatNodeCFv
    .long Bind__Q34nw4r3g3d16AnmObjTexPatNodeFQ34nw4r3g3d6ResMdl
    .long Release__Q34nw4r3g3d16AnmObjTexPatNodeFv
    .long GetResult__Q34nw4r3g3d20AnmObjTexPatOverrideFPQ34nw4r3g3d15TexPatAnmResultUl
    .long Attach__Q34nw4r3g3d16AnmObjTexPatNodeFiPQ34nw4r3g3d15AnmObjTexPatRes
    .long Detach__Q34nw4r3g3d16AnmObjTexPatNodeFi
    .long DetachAll__Q34nw4r3g3d16AnmObjTexPatNodeFv

.global __vt__Q34nw4r3g3d16AnmObjTexPatNode
__vt__Q34nw4r3g3d16AnmObjTexPatNode:
    .long 0
    .long 0
    .long IsDerivedFrom__Q34nw4r3g3d16AnmObjTexPatNodeCFQ44nw4r3g3d6G3dObj7TypeObj
    .long G3dProc__Q34nw4r3g3d16AnmObjTexPatNodeFUlUlPv
    .long __dt__Q34nw4r3g3d16AnmObjTexPatNodeFv
    .long GetTypeObj__Q34nw4r3g3d16AnmObjTexPatNodeCFv
    .long GetTypeName__Q34nw4r3g3d16AnmObjTexPatNodeCFv
    .long SetFrame__Q34nw4r3g3d16AnmObjTexPatNodeFf
    .long GetFrame__Q34nw4r3g3d16AnmObjTexPatNodeCFv
    .long UpdateFrame__Q34nw4r3g3d16AnmObjTexPatNodeFv
    .long SetUpdateRate__Q34nw4r3g3d16AnmObjTexPatNodeFf
    .long GetUpdateRate__Q34nw4r3g3d16AnmObjTexPatNodeCFv
    .long Bind__Q34nw4r3g3d16AnmObjTexPatNodeFQ34nw4r3g3d6ResMdl
    .long Release__Q34nw4r3g3d16AnmObjTexPatNodeFv
    .long 0
    .long Attach__Q34nw4r3g3d16AnmObjTexPatNodeFiPQ34nw4r3g3d15AnmObjTexPatRes
    .long Detach__Q34nw4r3g3d16AnmObjTexPatNodeFi
    .long DetachAll__Q34nw4r3g3d16AnmObjTexPatNodeFv

.global __vt__Q34nw4r3g3d12AnmObjTexPat
__vt__Q34nw4r3g3d12AnmObjTexPat:
    .long 0
    .long 0
    .long IsDerivedFrom__Q34nw4r3g3d12AnmObjTexPatCFQ44nw4r3g3d6G3dObj7TypeObj
    .long 0
    .long __dt__Q34nw4r3g3d12AnmObjTexPatFv
    .long GetTypeObj__Q34nw4r3g3d12AnmObjTexPatCFv
    .long GetTypeName__Q34nw4r3g3d12AnmObjTexPatCFv
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long Release__Q34nw4r3g3d12AnmObjTexPatFv
    .long 0
    .long Attach__Q34nw4r3g3d12AnmObjTexPatFiPQ34nw4r3g3d15AnmObjTexPatRes
    .long Detach__Q34nw4r3g3d12AnmObjTexPatFi
    .long DetachAll__Q34nw4r3g3d12AnmObjTexPatFv

.global __vt__Q34nw4r3g3d15AnmObjTexSrtRes
__vt__Q34nw4r3g3d15AnmObjTexSrtRes:
    .long 0
    .long 0
    .long IsDerivedFrom__Q34nw4r3g3d15AnmObjTexSrtResCFQ44nw4r3g3d6G3dObj7TypeObj
    .long G3dProc__Q34nw4r3g3d15AnmObjTexSrtResFUlUlPv
    .long __dt__Q34nw4r3g3d15AnmObjTexSrtResFv
    .long GetTypeObj__Q34nw4r3g3d15AnmObjTexSrtResCFv
    .long GetTypeName__Q34nw4r3g3d15AnmObjTexSrtResCFv
    .long SetFrame__Q34nw4r3g3d15AnmObjTexSrtResFf
    .long GetFrame__Q34nw4r3g3d15AnmObjTexSrtResCFv
    .long UpdateFrame__Q34nw4r3g3d15AnmObjTexSrtResFv
    .long SetUpdateRate__Q34nw4r3g3d15AnmObjTexSrtResFf
    .long GetUpdateRate__Q34nw4r3g3d15AnmObjTexSrtResCFv
    .long Bind__Q34nw4r3g3d15AnmObjTexSrtResFQ34nw4r3g3d6ResMdl
    .long Release__Q34nw4r3g3d12AnmObjTexSrtFv
    .long GetResult__Q34nw4r3g3d15AnmObjTexSrtResFPQ34nw4r3g3d15TexSrtAnmResultUl
    .long Attach__Q34nw4r3g3d12AnmObjTexSrtFiPQ34nw4r3g3d15AnmObjTexSrtRes
    .long Detach__Q34nw4r3g3d12AnmObjTexSrtFi
    .long DetachAll__Q34nw4r3g3d12AnmObjTexSrtFv

.global __vt__Q34nw4r3g3d20AnmObjTexSrtOverride
__vt__Q34nw4r3g3d20AnmObjTexSrtOverride:
    .long 0
    .long 0
    .long IsDerivedFrom__Q34nw4r3g3d20AnmObjTexSrtOverrideCFQ44nw4r3g3d6G3dObj7TypeObj
    .long G3dProc__Q34nw4r3g3d16AnmObjTexSrtNodeFUlUlPv
    .long __dt__Q34nw4r3g3d20AnmObjTexSrtOverrideFv
    .long GetTypeObj__Q34nw4r3g3d20AnmObjTexSrtOverrideCFv
    .long GetTypeName__Q34nw4r3g3d20AnmObjTexSrtOverrideCFv
    .long SetFrame__Q34nw4r3g3d16AnmObjTexSrtNodeFf
    .long GetFrame__Q34nw4r3g3d16AnmObjTexSrtNodeCFv
    .long UpdateFrame__Q34nw4r3g3d16AnmObjTexSrtNodeFv
    .long SetUpdateRate__Q34nw4r3g3d16AnmObjTexSrtNodeFf
    .long GetUpdateRate__Q34nw4r3g3d16AnmObjTexSrtNodeCFv
    .long Bind__Q34nw4r3g3d16AnmObjTexSrtNodeFQ34nw4r3g3d6ResMdl
    .long Release__Q34nw4r3g3d16AnmObjTexSrtNodeFv
    .long GetResult__Q34nw4r3g3d20AnmObjTexSrtOverrideFPQ34nw4r3g3d15TexSrtAnmResultUl
    .long Attach__Q34nw4r3g3d16AnmObjTexSrtNodeFiPQ34nw4r3g3d15AnmObjTexSrtRes
    .long Detach__Q34nw4r3g3d16AnmObjTexSrtNodeFi
    .long DetachAll__Q34nw4r3g3d16AnmObjTexSrtNodeFv

.global __vt__Q34nw4r3g3d16AnmObjTexSrtNode
__vt__Q34nw4r3g3d16AnmObjTexSrtNode:
    .long 0
    .long 0
    .long IsDerivedFrom__Q34nw4r3g3d16AnmObjTexSrtNodeCFQ44nw4r3g3d6G3dObj7TypeObj
    .long G3dProc__Q34nw4r3g3d16AnmObjTexSrtNodeFUlUlPv
    .long __dt__Q34nw4r3g3d16AnmObjTexSrtNodeFv
    .long GetTypeObj__Q34nw4r3g3d16AnmObjTexSrtNodeCFv
    .long GetTypeName__Q34nw4r3g3d16AnmObjTexSrtNodeCFv
    .long SetFrame__Q34nw4r3g3d16AnmObjTexSrtNodeFf
    .long GetFrame__Q34nw4r3g3d16AnmObjTexSrtNodeCFv
    .long UpdateFrame__Q34nw4r3g3d16AnmObjTexSrtNodeFv
    .long SetUpdateRate__Q34nw4r3g3d16AnmObjTexSrtNodeFf
    .long GetUpdateRate__Q34nw4r3g3d16AnmObjTexSrtNodeCFv
    .long Bind__Q34nw4r3g3d16AnmObjTexSrtNodeFQ34nw4r3g3d6ResMdl
    .long Release__Q34nw4r3g3d16AnmObjTexSrtNodeFv
    .long 0
    .long Attach__Q34nw4r3g3d16AnmObjTexSrtNodeFiPQ34nw4r3g3d15AnmObjTexSrtRes
    .long Detach__Q34nw4r3g3d16AnmObjTexSrtNodeFi
    .long DetachAll__Q34nw4r3g3d16AnmObjTexSrtNodeFv

.global __vt__Q34nw4r3g3d12AnmObjTexSrt
__vt__Q34nw4r3g3d12AnmObjTexSrt:
    .long 0
    .long 0
    .long IsDerivedFrom__Q34nw4r3g3d12AnmObjTexSrtCFQ44nw4r3g3d6G3dObj7TypeObj
    .long 0
    .long __dt__Q34nw4r3g3d12AnmObjTexSrtFv
    .long GetTypeObj__Q34nw4r3g3d12AnmObjTexSrtCFv
    .long GetTypeName__Q34nw4r3g3d12AnmObjTexSrtCFv
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long Release__Q34nw4r3g3d12AnmObjTexSrtFv
    .long 0
    .long Attach__Q34nw4r3g3d12AnmObjTexSrtFiPQ34nw4r3g3d15AnmObjTexSrtRes
    .long Detach__Q34nw4r3g3d12AnmObjTexSrtFi
    .long DetachAll__Q34nw4r3g3d12AnmObjTexSrtFv

.global __vt__Q34nw4r3g3d12AnmObjChrRes
__vt__Q34nw4r3g3d12AnmObjChrRes:
    .long 0
    .long 0
    .long IsDerivedFrom__Q34nw4r3g3d12AnmObjChrResCFQ44nw4r3g3d6G3dObj7TypeObj
    .long G3dProc__Q34nw4r3g3d12AnmObjChrResFUlUlPv
    .long __dt__Q34nw4r3g3d12AnmObjChrResFv
    .long GetTypeObj__Q34nw4r3g3d12AnmObjChrResCFv
    .long GetTypeName__Q34nw4r3g3d12AnmObjChrResCFv
    .long SetFrame__Q34nw4r3g3d12AnmObjChrResFf
    .long GetFrame__Q34nw4r3g3d12AnmObjChrResCFv
    .long UpdateFrame__Q34nw4r3g3d12AnmObjChrResFv
    .long SetUpdateRate__Q34nw4r3g3d12AnmObjChrResFf
    .long GetUpdateRate__Q34nw4r3g3d12AnmObjChrResCFv
    .long Bind__Q34nw4r3g3d12AnmObjChrResFQ34nw4r3g3d6ResMdl
    .long Release__Q34nw4r3g3d9AnmObjChrFv
    .long GetResult__Q34nw4r3g3d12AnmObjChrResFPQ34nw4r3g3d12ChrAnmResultUl
    .long Attach__Q34nw4r3g3d9AnmObjChrFiPQ34nw4r3g3d12AnmObjChrRes
    .long Detach__Q34nw4r3g3d9AnmObjChrFi
    .long DetachAll__Q34nw4r3g3d9AnmObjChrFv
    .long SetWeight__Q34nw4r3g3d9AnmObjChrFif
    .long GetWeight__Q34nw4r3g3d9AnmObjChrCFi
    .long Bind__Q34nw4r3g3d12AnmObjChrResFQ34nw4r3g3d6ResMdlUlQ44nw4r3g3d9AnmObjChr10BindOption
    .long Release__Q34nw4r3g3d12AnmObjChrResFQ34nw4r3g3d6ResMdlUlQ44nw4r3g3d9AnmObjChr10BindOption

.global __vt__Q34nw4r3g3d14AnmObjChrBlend
__vt__Q34nw4r3g3d14AnmObjChrBlend:
    .long 0
    .long 0
    .long IsDerivedFrom__Q34nw4r3g3d14AnmObjChrBlendCFQ44nw4r3g3d6G3dObj7TypeObj
    .long G3dProc__Q34nw4r3g3d13AnmObjChrNodeFUlUlPv
    .long __dt__Q34nw4r3g3d14AnmObjChrBlendFv
    .long GetTypeObj__Q34nw4r3g3d14AnmObjChrBlendCFv
    .long GetTypeName__Q34nw4r3g3d14AnmObjChrBlendCFv
    .long SetFrame__Q34nw4r3g3d13AnmObjChrNodeFf
    .long GetFrame__Q34nw4r3g3d13AnmObjChrNodeCFv
    .long UpdateFrame__Q34nw4r3g3d13AnmObjChrNodeFv
    .long SetUpdateRate__Q34nw4r3g3d13AnmObjChrNodeFf
    .long GetUpdateRate__Q34nw4r3g3d13AnmObjChrNodeCFv
    .long Bind__Q34nw4r3g3d13AnmObjChrNodeFQ34nw4r3g3d6ResMdl
    .long Release__Q34nw4r3g3d13AnmObjChrNodeFv
    .long GetResult__Q34nw4r3g3d14AnmObjChrBlendFPQ34nw4r3g3d12ChrAnmResultUl
    .long Attach__Q34nw4r3g3d13AnmObjChrNodeFiPQ34nw4r3g3d12AnmObjChrRes
    .long Detach__Q34nw4r3g3d13AnmObjChrNodeFi
    .long DetachAll__Q34nw4r3g3d13AnmObjChrNodeFv
    .long SetWeight__Q34nw4r3g3d14AnmObjChrBlendFif
    .long GetWeight__Q34nw4r3g3d14AnmObjChrBlendCFi
    .long Bind__Q34nw4r3g3d13AnmObjChrNodeFQ34nw4r3g3d6ResMdlUlQ44nw4r3g3d9AnmObjChr10BindOption
    .long Release__Q34nw4r3g3d13AnmObjChrNodeFQ34nw4r3g3d6ResMdlUlQ44nw4r3g3d9AnmObjChr10BindOption

.global __vt__Q34nw4r3g3d13AnmObjChrNode
__vt__Q34nw4r3g3d13AnmObjChrNode:
    .long 0
    .long 0
    .long IsDerivedFrom__Q34nw4r3g3d13AnmObjChrNodeCFQ44nw4r3g3d6G3dObj7TypeObj
    .long G3dProc__Q34nw4r3g3d13AnmObjChrNodeFUlUlPv
    .long __dt__Q34nw4r3g3d13AnmObjChrNodeFv
    .long GetTypeObj__Q34nw4r3g3d13AnmObjChrNodeCFv
    .long GetTypeName__Q34nw4r3g3d13AnmObjChrNodeCFv
    .long SetFrame__Q34nw4r3g3d13AnmObjChrNodeFf
    .long GetFrame__Q34nw4r3g3d13AnmObjChrNodeCFv
    .long UpdateFrame__Q34nw4r3g3d13AnmObjChrNodeFv
    .long SetUpdateRate__Q34nw4r3g3d13AnmObjChrNodeFf
    .long GetUpdateRate__Q34nw4r3g3d13AnmObjChrNodeCFv
    .long Bind__Q34nw4r3g3d13AnmObjChrNodeFQ34nw4r3g3d6ResMdl
    .long Release__Q34nw4r3g3d13AnmObjChrNodeFv
    .long 0
    .long Attach__Q34nw4r3g3d13AnmObjChrNodeFiPQ34nw4r3g3d12AnmObjChrRes
    .long Detach__Q34nw4r3g3d13AnmObjChrNodeFi
    .long DetachAll__Q34nw4r3g3d13AnmObjChrNodeFv
    .long SetWeight__Q34nw4r3g3d9AnmObjChrFif
    .long GetWeight__Q34nw4r3g3d9AnmObjChrCFi
    .long Bind__Q34nw4r3g3d13AnmObjChrNodeFQ34nw4r3g3d6ResMdlUlQ44nw4r3g3d9AnmObjChr10BindOption
    .long Release__Q34nw4r3g3d13AnmObjChrNodeFQ34nw4r3g3d6ResMdlUlQ44nw4r3g3d9AnmObjChr10BindOption

.global __vt__Q34nw4r3g3d9AnmObjChr
__vt__Q34nw4r3g3d9AnmObjChr:
    .long 0
    .long 0
    .long IsDerivedFrom__Q34nw4r3g3d9AnmObjChrCFQ44nw4r3g3d6G3dObj7TypeObj
    .long 0
    .long __dt__Q34nw4r3g3d9AnmObjChrFv
    .long GetTypeObj__Q34nw4r3g3d9AnmObjChrCFv
    .long GetTypeName__Q34nw4r3g3d9AnmObjChrCFv
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long Release__Q34nw4r3g3d9AnmObjChrFv
    .long 0
    .long Attach__Q34nw4r3g3d9AnmObjChrFiPQ34nw4r3g3d12AnmObjChrRes
    .long Detach__Q34nw4r3g3d9AnmObjChrFi
    .long DetachAll__Q34nw4r3g3d9AnmObjChrFv
    .long SetWeight__Q34nw4r3g3d9AnmObjChrFif
    .long GetWeight__Q34nw4r3g3d9AnmObjChrCFi
    .long 0
    .long 0

.global __vt__Q34nw4r3g3d12AnmObjShpRes
__vt__Q34nw4r3g3d12AnmObjShpRes:
    .long 0
    .long 0
    .long IsDerivedFrom__Q34nw4r3g3d12AnmObjShpResCFQ44nw4r3g3d6G3dObj7TypeObj
    .long G3dProc__Q34nw4r3g3d12AnmObjShpResFUlUlPv
    .long __dt__Q34nw4r3g3d12AnmObjShpResFv
    .long GetTypeObj__Q34nw4r3g3d12AnmObjShpResCFv
    .long GetTypeName__Q34nw4r3g3d12AnmObjShpResCFv
    .long SetFrame__Q34nw4r3g3d12AnmObjShpResFf
    .long GetFrame__Q34nw4r3g3d12AnmObjShpResCFv
    .long UpdateFrame__Q34nw4r3g3d12AnmObjShpResFv
    .long SetUpdateRate__Q34nw4r3g3d12AnmObjShpResFf
    .long GetUpdateRate__Q34nw4r3g3d12AnmObjShpResCFv
    .long Bind__Q34nw4r3g3d12AnmObjShpResFQ34nw4r3g3d6ResMdl
    .long Release__Q34nw4r3g3d9AnmObjShpFv
    .long GetResult__Q34nw4r3g3d12AnmObjShpResFPQ34nw4r3g3d12ShpAnmResultUl
    .long Attach__Q34nw4r3g3d9AnmObjShpFiPQ34nw4r3g3d12AnmObjShpRes
    .long Detach__Q34nw4r3g3d9AnmObjShpFi
    .long DetachAll__Q34nw4r3g3d9AnmObjShpFv
    .long SetWeight__Q34nw4r3g3d9AnmObjShpFif
    .long GetWeight__Q34nw4r3g3d9AnmObjShpCFi

.global __vt__Q34nw4r3g3d14AnmObjShpBlend
__vt__Q34nw4r3g3d14AnmObjShpBlend:
    .long 0
    .long 0
    .long IsDerivedFrom__Q34nw4r3g3d14AnmObjShpBlendCFQ44nw4r3g3d6G3dObj7TypeObj
    .long G3dProc__Q34nw4r3g3d13AnmObjShpNodeFUlUlPv
    .long __dt__Q34nw4r3g3d14AnmObjShpBlendFv
    .long GetTypeObj__Q34nw4r3g3d14AnmObjShpBlendCFv
    .long GetTypeName__Q34nw4r3g3d14AnmObjShpBlendCFv
    .long SetFrame__Q34nw4r3g3d13AnmObjShpNodeFf
    .long GetFrame__Q34nw4r3g3d13AnmObjShpNodeCFv
    .long UpdateFrame__Q34nw4r3g3d13AnmObjShpNodeFv
    .long SetUpdateRate__Q34nw4r3g3d13AnmObjShpNodeFf
    .long GetUpdateRate__Q34nw4r3g3d13AnmObjShpNodeCFv
    .long Bind__Q34nw4r3g3d13AnmObjShpNodeFQ34nw4r3g3d6ResMdl
    .long Release__Q34nw4r3g3d13AnmObjShpNodeFv
    .long GetResult__Q34nw4r3g3d14AnmObjShpBlendFPQ34nw4r3g3d12ShpAnmResultUl
    .long Attach__Q34nw4r3g3d13AnmObjShpNodeFiPQ34nw4r3g3d12AnmObjShpRes
    .long Detach__Q34nw4r3g3d13AnmObjShpNodeFi
    .long DetachAll__Q34nw4r3g3d13AnmObjShpNodeFv
    .long SetWeight__Q34nw4r3g3d14AnmObjShpBlendFif
    .long GetWeight__Q34nw4r3g3d14AnmObjShpBlendCFi

.global __vt__Q34nw4r3g3d13AnmObjShpNode
__vt__Q34nw4r3g3d13AnmObjShpNode:
    .long 0
    .long 0
    .long IsDerivedFrom__Q34nw4r3g3d13AnmObjShpNodeCFQ44nw4r3g3d6G3dObj7TypeObj
    .long G3dProc__Q34nw4r3g3d13AnmObjShpNodeFUlUlPv
    .long __dt__Q34nw4r3g3d13AnmObjShpNodeFv
    .long GetTypeObj__Q34nw4r3g3d13AnmObjShpNodeCFv
    .long GetTypeName__Q34nw4r3g3d13AnmObjShpNodeCFv
    .long SetFrame__Q34nw4r3g3d13AnmObjShpNodeFf
    .long GetFrame__Q34nw4r3g3d13AnmObjShpNodeCFv
    .long UpdateFrame__Q34nw4r3g3d13AnmObjShpNodeFv
    .long SetUpdateRate__Q34nw4r3g3d13AnmObjShpNodeFf
    .long GetUpdateRate__Q34nw4r3g3d13AnmObjShpNodeCFv
    .long Bind__Q34nw4r3g3d13AnmObjShpNodeFQ34nw4r3g3d6ResMdl
    .long Release__Q34nw4r3g3d13AnmObjShpNodeFv
    .long 0
    .long Attach__Q34nw4r3g3d13AnmObjShpNodeFiPQ34nw4r3g3d12AnmObjShpRes
    .long Detach__Q34nw4r3g3d13AnmObjShpNodeFi
    .long DetachAll__Q34nw4r3g3d13AnmObjShpNodeFv
    .long SetWeight__Q34nw4r3g3d9AnmObjShpFif
    .long GetWeight__Q34nw4r3g3d9AnmObjShpCFi

.global __vt__Q34nw4r3g3d9AnmObjShp
__vt__Q34nw4r3g3d9AnmObjShp:
    .long 0
    .long 0
    .long IsDerivedFrom__Q34nw4r3g3d9AnmObjShpCFQ44nw4r3g3d6G3dObj7TypeObj
    .long 0
    .long __dt__Q34nw4r3g3d9AnmObjShpFv
    .long GetTypeObj__Q34nw4r3g3d9AnmObjShpCFv
    .long GetTypeName__Q34nw4r3g3d9AnmObjShpCFv
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long Release__Q34nw4r3g3d9AnmObjShpFv
    .long 0
    .long Attach__Q34nw4r3g3d9AnmObjShpFiPQ34nw4r3g3d12AnmObjShpRes
    .long Detach__Q34nw4r3g3d9AnmObjShpFi
    .long DetachAll__Q34nw4r3g3d9AnmObjShpFv
    .long SetWeight__Q34nw4r3g3d9AnmObjShpFif
    .long GetWeight__Q34nw4r3g3d9AnmObjShpCFi

.global __vt__Q34nw4r3g3d6G3dObj
__vt__Q34nw4r3g3d6G3dObj:
    .long 0
    .long 0
    .long IsDerivedFrom__Q34nw4r3g3d6G3dObjCFQ44nw4r3g3d6G3dObj7TypeObj
    .long 0
    .long __dt__Q34nw4r3g3d6G3dObjFv
    .long GetTypeObj__Q34nw4r3g3d6G3dObjCFv
    .long GetTypeName__Q34nw4r3g3d6G3dObjCFv
    .long 0

.global __vt__Q44nw4r3g3d8G3DState11IndMtxOpStd
__vt__Q44nw4r3g3d8G3DState11IndMtxOpStd:
    .long 0
    .long 0
    .long __cl__Q44nw4r3g3d8G3DState11IndMtxOpStdFPQ44nw4r3g3d8G3DState13IndTexMtxInfo
    .long __dt__Q44nw4r3g3d8G3DState11IndMtxOpStdFv
    .long Reset__Q44nw4r3g3d8G3DState11IndMtxOpStdFv
    .long SetNrmMapMtx__Q44nw4r3g3d8G3DState11IndMtxOpStdF14_GXIndTexMtxIDPCQ34nw4r4math4VEC3PCQ34nw4r4math5MTX34Q44nw4r3g3d14ResMatMiscData14IndirectMethod

.global lbl_80396EC8
lbl_80396EC8:
	.string "NodeTree"
	.balign 0x8

.global switch_80396ED8
switch_80396ED8:
    .long lbl_8006FE3C
    .long 0x8006fcd4
    .long 0x8006fcfc
    .long 0x8006fd24
    .long 0x8006fd4c
    .long 0x8006fd74
    .long 0x8006fd9c
    .long 0x8006fdc4
    .long 0x8006fdec
    .long 0x8006fe14

.global switch_80396F00
switch_80396F00:
    .long 0x8006ff0c
    .long 0x8006fe7c
    .long 0x8006fe8c
    .long 0x8006fe9c
    .long 0x8006feac
    .long 0x8006febc
    .long 0x8006fecc
    .long 0x8006fedc
    .long 0x8006feec
    .long 0x8006fefc

.global __vt__Q34nw4r3g3d8ScnGroup
__vt__Q34nw4r3g3d8ScnGroup:
    .long 0
    .long 0
    .long IsDerivedFrom__Q34nw4r3g3d8ScnGroupCFQ44nw4r3g3d6G3dObj7TypeObj
    .long G3dProc__Q34nw4r3g3d8ScnGroupFUlUlPv
    .long __dt__Q34nw4r3g3d8ScnGroupFv
    .long GetTypeObj__Q34nw4r3g3d8ScnGroupCFv
    .long GetTypeName__Q34nw4r3g3d8ScnGroupCFv
    .long ForEach__Q34nw4r3g3d8ScnGroupFPFPQ34nw4r3g3d6ScnObjPv_Q44nw4r3g3d6ScnObj13ForEachResultPvb
    .long SetScnObjOption__Q34nw4r3g3d6ScnObjFUlUl
    .long GetScnObjOption__Q34nw4r3g3d6ScnObjCFUlPUl
    .long GetValueForSortOpa__Q34nw4r3g3d6ScnObjCFv
    .long GetValueForSortXlu__Q34nw4r3g3d6ScnObjCFv
    .long CalcWorldMtx__Q34nw4r3g3d6ScnObjFPCQ34nw4r4math5MTX34PUl
    .long Insert__Q34nw4r3g3d8ScnGroupFUlPQ34nw4r3g3d6ScnObj
    .long Remove__Q34nw4r3g3d8ScnGroupFUl
    .long Remove__Q34nw4r3g3d8ScnGroupFPQ34nw4r3g3d6ScnObj

.global __vt__Q34nw4r3g3d6ScnObj
__vt__Q34nw4r3g3d6ScnObj:
    .long 0
    .long 0
    .long IsDerivedFrom__Q34nw4r3g3d6ScnObjCFQ44nw4r3g3d6G3dObj7TypeObj
    .long 0
    .long __dt__Q34nw4r3g3d6ScnObjFv
    .long GetTypeObj__Q34nw4r3g3d6ScnObjCFv
    .long GetTypeName__Q34nw4r3g3d6ScnObjCFv
    .long 0
    .long SetScnObjOption__Q34nw4r3g3d6ScnObjFUlUl
    .long GetScnObjOption__Q34nw4r3g3d6ScnObjCFUlPUl
    .long GetValueForSortOpa__Q34nw4r3g3d6ScnObjCFv
    .long GetValueForSortXlu__Q34nw4r3g3d6ScnObjCFv
    .long CalcWorldMtx__Q34nw4r3g3d6ScnObjFPCQ34nw4r4math5MTX34PUl
    .long 0

.global __vt__Q34nw4r3g3d12ScnObjGather
__vt__Q34nw4r3g3d12ScnObjGather:
    .long 0
    .long 0
    .long __dt__Q34nw4r3g3d12ScnObjGatherFv
    .long Add__Q34nw4r3g3d12ScnObjGatherFPQ34nw4r3g3d6ScnObjbb
    .long Clear__Q34nw4r3g3d12ScnObjGatherFv
    .long ZSort__Q34nw4r3g3d12ScnObjGatherFv
    .long Sort__Q34nw4r3g3d12ScnObjGatherFv
    .long Sort__Q34nw4r3g3d12ScnObjGatherFPFPCQ34nw4r3g3d6ScnObjPCQ34nw4r3g3d6ScnObj_bPFPCQ34nw4r3g3d6ScnObjPCQ34nw4r3g3d6ScnObj_b
    .long DrawOpa__Q34nw4r3g3d12ScnObjGatherFPQ34nw4r3g3d14ResMdlDrawMode
    .long DrawXlu__Q34nw4r3g3d12ScnObjGatherFPQ34nw4r3g3d14ResMdlDrawMode

.global __vt__Q34nw4r3g3d7ScnRoot
__vt__Q34nw4r3g3d7ScnRoot:
    .long 0
    .long 0
    .long IsDerivedFrom__Q34nw4r3g3d7ScnRootCFQ44nw4r3g3d6G3dObj7TypeObj
    .long G3dProc__Q34nw4r3g3d7ScnRootFUlUlPv
    .long __dt__Q34nw4r3g3d7ScnRootFv
    .long GetTypeObj__Q34nw4r3g3d7ScnRootCFv
    .long GetTypeName__Q34nw4r3g3d7ScnRootCFv
    .long ForEach__Q34nw4r3g3d8ScnGroupFPFPQ34nw4r3g3d6ScnObjPv_Q44nw4r3g3d6ScnObj13ForEachResultPvb
    .long SetScnObjOption__Q34nw4r3g3d6ScnObjFUlUl
    .long GetScnObjOption__Q34nw4r3g3d6ScnObjCFUlPUl
    .long GetValueForSortOpa__Q34nw4r3g3d6ScnObjCFv
    .long GetValueForSortXlu__Q34nw4r3g3d6ScnObjCFv
    .long CalcWorldMtx__Q34nw4r3g3d6ScnObjFPCQ34nw4r4math5MTX34PUl
    .long Insert__Q34nw4r3g3d8ScnGroupFUlPQ34nw4r3g3d6ScnObj
    .long Remove__Q34nw4r3g3d8ScnGroupFUl
    .long Remove__Q34nw4r3g3d8ScnGroupFPQ34nw4r3g3d6ScnObj

.global switch_80397008
switch_80397008:
    .long 0x80073e54
    .long 0x80073eac
    .long 0x80073f04
    .long 0x80073f5c
    .long 0x80073fb4
    .long 0x800741b8
    .long 0x80074008

.global lbl_80397024
lbl_80397024:
	.string "NodeTree"
	.balign 0x8

.global __vt__Q34nw4r3g3d12ScnMdlSimple
__vt__Q34nw4r3g3d12ScnMdlSimple:
    .long 0
    .long 0
    .long IsDerivedFrom__Q34nw4r3g3d12ScnMdlSimpleCFQ44nw4r3g3d6G3dObj7TypeObj
    .long G3dProc__Q34nw4r3g3d12ScnMdlSimpleFUlUlPv
    .long __dt__Q34nw4r3g3d12ScnMdlSimpleFv
    .long GetTypeObj__Q34nw4r3g3d12ScnMdlSimpleCFv
    .long GetTypeName__Q34nw4r3g3d12ScnMdlSimpleCFv
    .long ForEach__Q34nw4r3g3d7ScnLeafFPFPQ34nw4r3g3d6ScnObjPv_Q44nw4r3g3d6ScnObj13ForEachResultPvb
    .long SetScnObjOption__Q34nw4r3g3d12ScnMdlSimpleFUlUl
    .long GetScnObjOption__Q34nw4r3g3d12ScnMdlSimpleCFUlPUl
    .long GetValueForSortOpa__Q34nw4r3g3d6ScnObjCFv
    .long GetValueForSortXlu__Q34nw4r3g3d6ScnObjCFv
    .long CalcWorldMtx__Q34nw4r3g3d7ScnLeafFPCQ34nw4r4math5MTX34PUl
    .long SetAnmObj__Q34nw4r3g3d12ScnMdlSimpleFPQ34nw4r3g3d6AnmObjQ44nw4r3g3d12ScnMdlSimple10AnmObjType
    .long RemoveAnmObj__Q34nw4r3g3d12ScnMdlSimpleFPQ34nw4r3g3d6AnmObj
    .long RemoveAnmObj__Q34nw4r3g3d12ScnMdlSimpleFQ44nw4r3g3d12ScnMdlSimple10AnmObjType
    .long GetAnmObj__Q34nw4r3g3d12ScnMdlSimpleFQ44nw4r3g3d12ScnMdlSimple10AnmObjType
    .long GetAnmObj__Q34nw4r3g3d12ScnMdlSimpleCFQ44nw4r3g3d12ScnMdlSimple10AnmObjType

.global __vt__Q34nw4r3g3d6ScnMdl
__vt__Q34nw4r3g3d6ScnMdl:
    .long 0
    .long 0
    .long IsDerivedFrom__Q34nw4r3g3d6ScnMdlCFQ44nw4r3g3d6G3dObj7TypeObj
    .long func_80076614
    .long __dt__Q34nw4r3g3d6ScnMdlFv
    .long GetTypeObj__Q34nw4r3g3d6ScnMdlCFv
    .long GetTypeName__Q34nw4r3g3d6ScnMdlCFv
    .long ForEach__Q34nw4r3g3d7ScnLeafFPFPQ34nw4r3g3d6ScnObjPv_Q44nw4r3g3d6ScnObj13ForEachResultPvb
    .long SetScnObjOption__Q34nw4r3g3d6ScnMdlFUlUl
    .long GetScnObjOption__Q34nw4r3g3d6ScnMdlCFUlPUl
    .long GetValueForSortOpa__Q34nw4r3g3d6ScnObjCFv
    .long GetValueForSortXlu__Q34nw4r3g3d6ScnObjCFv
    .long CalcWorldMtx__Q34nw4r3g3d7ScnLeafFPCQ34nw4r4math5MTX34PUl
    .long SetAnmObj__Q34nw4r3g3d6ScnMdlFPQ34nw4r3g3d6AnmObjQ44nw4r3g3d12ScnMdlSimple10AnmObjType
    .long RemoveAnmObj__Q34nw4r3g3d6ScnMdlFPQ34nw4r3g3d6AnmObj
    .long RemoveAnmObj__Q34nw4r3g3d6ScnMdlFQ44nw4r3g3d12ScnMdlSimple10AnmObjType
    .long GetAnmObj__Q34nw4r3g3d6ScnMdlFQ44nw4r3g3d12ScnMdlSimple10AnmObjType
    .long GetAnmObj__Q34nw4r3g3d6ScnMdlCFQ44nw4r3g3d12ScnMdlSimple10AnmObjType

.global $$27641
$$27641:
	.string "<< NW4R    - G3D \tfinal   build: Jun  8 2007 11:16:25 (0x4199_60831) >>"

.global lbl_80397108
lbl_80397108:
    .long 0
    .long 0
    .long IsDerivedFrom__Q34nw4r3g3d7ScnProcCFQ44nw4r3g3d6G3dObj7TypeObj
    .long 0x80077d3c
    .long 0x80077ee8
    .long GetTypeObj__Q34nw4r3g3d7ScnProcCFv
    .long GetTypeName__Q34nw4r3g3d7ScnProcCFv
    .long ForEach__Q34nw4r3g3d7ScnLeafFPFPQ34nw4r3g3d6ScnObjPv_Q44nw4r3g3d6ScnObj13ForEachResultPvb
    .long SetScnObjOption__Q34nw4r3g3d7ScnLeafFUlUl
    .long GetScnObjOption__Q34nw4r3g3d7ScnLeafCFUlPUl
    .long GetValueForSortOpa__Q34nw4r3g3d6ScnObjCFv
    .long GetValueForSortXlu__Q34nw4r3g3d6ScnObjCFv
    .long CalcWorldMtx__Q34nw4r3g3d7ScnLeafFPCQ34nw4r4math5MTX34PUl
    .long 0

.global lbl_80397140
lbl_80397140:
.string "<< NW4R    - LYT \tfinal   build: Jun  8 2007 11:17:26 (0x4199_60831) >>"

.global __vt__Q34nw4r3lyt4Pane
__vt__Q34nw4r3lyt4Pane:
    .long 0
    .long 0
    .long __dt__Q34nw4r3lyt4PaneFv
    .long func_8007A218
    .long CalculateMtx__Q34nw4r3lyt4PaneFRCQ34nw4r3lyt8DrawInfo
    .long Draw__Q34nw4r3lyt4PaneFRCQ34nw4r3lyt8DrawInfo
    .long DrawSelf__Q34nw4r3lyt4PaneFRCQ34nw4r3lyt8DrawInfo
    .long Animate__Q34nw4r3lyt4PaneFUl
    .long AnimateSelf__Q34nw4r3lyt4PaneFUl
    .long GetVtxColor__Q34nw4r3lyt4PaneCFUl
    .long SetVtxColor__Q34nw4r3lyt4PaneFUlQ34nw4r2ut5Color
    .long GetColorElement__Q34nw4r3lyt4PaneCFUl
    .long SetColorElement__Q34nw4r3lyt4PaneFUlUc
    .long GetVtxColorElement__Q34nw4r3lyt4PaneCFUl
    .long SetVtxColorElement__Q34nw4r3lyt4PaneFUlUc
    .long FindPaneByName__Q34nw4r3lyt4PaneFPCcb
    .long FindMaterialByName__Q34nw4r3lyt4PaneFPCcb
    .long BindAnimation__Q34nw4r3lyt4PaneFPQ34nw4r3lyt13AnimTransformb
    .long UnbindAnimation__Q34nw4r3lyt4PaneFPQ34nw4r3lyt13AnimTransformb
    .long UnbindAllAnimation__Q34nw4r3lyt4PaneFb
    .long UnbindAnimationSelf__Q34nw4r3lyt4PaneFPQ34nw4r3lyt13AnimTransform
    .long FindAnimationLink__Q34nw4r3lyt4PaneFPQ34nw4r3lyt13AnimTransform
    .long SetAnimationEnable__Q34nw4r3lyt4PaneFPQ34nw4r3lyt13AnimTransformbb
    .long GetMaterial__Q34nw4r3lyt4PaneCFv
    .long LoadMtx__Q34nw4r3lyt4PaneFRCQ34nw4r3lyt8DrawInfo
    .long 0

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
