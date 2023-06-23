GROUP_0_O_FILES := \
	build/asm/extab.o \
	build/asm/extabindex.o \

NW4R_O_FILES := \
	build/nw4r/ut/ut_list.o \
	build/nw4r/ut/ut_LinkList.o \
	build/nw4r/ut/ut_binaryFileFormat.o \
	build/nw4r/ut/ut_CharStrmReader.o \
	build/nw4r/ut/ut_TagProcessorBase.o \
	build/nw4r/ut/ut_IOStream.o \
	build/nw4r/ut/ut_FileStream.o \
	build/nw4r/ut/ut_DvdFileStream.o \
	build/nw4r/ut/ut_DvdLockedFileStream.o \
	build/nw4r/ut/ut_NandFileStream.o \
	build/nw4r/ut/ut_LockedCache.o \
	build/nw4r/ut/ut_Font.o \
	build/nw4r/ut/ut_RomFont.o \
	build/nw4r/ut/ut_ResFontBase.o \
	build/nw4r/ut/ut_ResFont.o \
	build/nw4r/ut/ut_CharWriter.o \
	build/asm/nw4r/ut/ut_TextWriterBase.o \
	\
	build/nw4r/ef/ef_draworder.o \
	build/nw4r/ef/ef_effect.o \
	build/nw4r/ef/ef_effectsystem.o \
	build/asm/nw4r/ef/ef_emitter.o \
	build/asm/nw4r/ef/ef_animcurve.o \
	build/asm/nw4r/ef/ef_particle.o \
	build/asm/nw4r/ef/ef_particlemanager.o \
	build/asm/nw4r/ef/ef_resource.o \
	build/asm/nw4r/ef/ef_util.o \
	build/nw4r/ef/ef_handle.o \
	build/asm/nw4r/ef/ef_emitterform.o \
	build/nw4r/ef/ef_creationqueue.o \
	build/nw4r/ef/ef_emform.o \
	build/asm/nw4r/ef/ef_point.o \
	build/asm/nw4r/ef/ef_line.o \
	build/asm/nw4r/ef/ef_disc.o \
	build/asm/nw4r/ef/ef_sphere.o \
	build/asm/nw4r/ef/ef_cylinder.o \
	build/asm/nw4r/ef/ef_torus.o \
	build/asm/nw4r/ef/ef_cube.o \
	build/nw4r/ef/ef_drawstrategybuilder.o \
	build/asm/nw4r/ef/ef_drawstrategyimpl.o \
	build/asm/nw4r/ef/ef_drawbillboardstrategy.o \
	build/asm/nw4r/ef/ef_drawdirectionalstrategy.o \
	build/asm/nw4r/ef/ef_drawfreestrategy.o \
	build/asm/nw4r/ef/ef_drawlinestrategy.o \
	build/asm/nw4r/ef/ef_drawpointstrategy.o \
	build/asm/nw4r/ef/ef_drawstripestrategy.o \
	build/asm/nw4r/ef/ef_drawsmoothstripestrategy.o \
	build/asm/nw4r/nw4r_8002F700.o \
	\
	build/asm/nw4r/math/math_arithmetic.o \
	build/asm/nw4r/math/math_triangular.o \
	build/nw4r/math/math_types.o \
	build/asm/nw4r/math/math_geometry.o \
	\
	build/asm/nw4r/snd/snd_AnimSound.o \
	build/asm/nw4r/snd/snd_AxManager.o \
	build/asm/nw4r/snd/snd_AxVoice.o \
	build/asm/nw4r/snd/snd_AxVoiceManager.o \
	build/nw4r/snd/snd_AxfxImpl.o \
	build/nw4r/snd/snd_Bank.o \
	build/nw4r/snd/snd_BankFile.o \
	build/nw4r/snd/snd_BasicPlayer.o \
	build/asm/nw4r/snd/snd_BasicSound.o \
	build/asm/nw4r/snd/snd_Channel.o \
	build/asm/nw4r/snd/snd_DisposeCallbackManager.o \
	build/nw4r/snd/snd_DvdSoundArchive.o \
	build/nw4r/snd/snd_EnvGenerator.o \
	build/nw4r/snd/snd_ExternalSoundPlayer.o \
	build/asm/nw4r/snd/snd_FrameHeap.o \
	build/nw4r/snd/snd_FxChorus.o \
	build/nw4r/snd/snd_FxDelay.o \
	build/nw4r/snd/snd_FxReverbHi.o \
	build/asm/nw4r/snd/snd_FxReverbHiDpl2.o \
	build/nw4r/snd/snd_InstancePool.o \
	build/nw4r/snd/snd_Lfo.o \
	build/nw4r/snd/snd_MemorySoundArchive.o \
	build/asm/nw4r/snd/snd_MidiSeqPlayer.o \
	build/nw4r/snd/snd_MmlParser.o \
	build/nw4r/snd/snd_MmlSeqTrack.o \
	build/nw4r/snd/snd_MmlSeqTrackAllocator.o \
	build/asm/nw4r/snd/snd_NandSoundArchive.o \
	build/nw4r/snd/snd_RemoteSpeaker.o \
	build/nw4r/snd/snd_RemoteSpeakerManager.o \
	build/nw4r/snd/snd_SeqFile.o \
	build/nw4r/snd/snd_SeqPlayer.o \
	build/nw4r/snd/snd_SeqSound.o \
	build/nw4r/snd/snd_SeqSoundHandle.o \
	build/asm/nw4r/snd/snd_SeqTrack.o \
	build/nw4r/snd/snd_Sound3DActor.o \
	build/nw4r/snd/snd_Sound3DListener.o \
	build/nw4r/snd/snd_Sound3DManager.o \
	build/nw4r/snd/snd_SoundActor.o \
	build/nw4r/snd/snd_SoundArchive.o \
	build/nw4r/snd/snd_SoundArchiveFile.o \
	build/nw4r/snd/snd_SoundArchiveLoader.o \
	build/asm/nw4r/snd/snd_SoundArchivePlayer.o \
	build/nw4r/snd/snd_SoundHandle.o \
	build/nw4r/snd/snd_SoundHeap.o \
	build/asm/nw4r/snd/snd_SoundPlayer.o \
	build/nw4r/snd/snd_SoundStartable.o \
	build/asm/nw4r/snd/snd_SoundSystem.o \
	build/nw4r/snd/snd_SoundThread.o \
	build/nw4r/snd/snd_StrmChannel.o \
	build/asm/nw4r/snd/snd_StrmFile.o \
	build/asm/nw4r/snd/snd_StrmPlayer.o \
	build/nw4r/snd/snd_StrmSound.o \
	build/nw4r/snd/snd_StrmSoundHandle.o \
	build/nw4r/snd/snd_Task.o \
	build/asm/nw4r/snd/snd_TaskManager.o \
	build/nw4r/snd/snd_TaskThread.o \
	build/asm/nw4r/snd/snd_Voice.o \
	build/asm/nw4r/snd/snd_VoiceManager.o \
	build/nw4r/snd/snd_Util.o \
	build/asm/nw4r/snd/snd_WaveFile.o \
	build/nw4r/snd/snd_WaveSound.o \
	build/nw4r/snd/snd_WaveSoundHandle.o \
	build/asm/nw4r/snd/snd_WsdFile.o \
	build/asm/nw4r/snd/snd_WsdPlayer.o \
	build/asm/nw4r/snd/snd_adpcm.o \
	\
	build/nw4r/g3d/g3d_rescommon.o \
	build/nw4r/g3d/g3d_resdict.o \
	build/nw4r/g3d/g3d_resfile.o \
	build/nw4r/g3d/g3d_resmdl.o \
	build/nw4r/g3d/g3d_resshp.o \
	build/nw4r/g3d/g3d_restev.o \
	build/asm/nw4r/g3d/g3d_resmat.o \
	build/nw4r/g3d/g3d_resvtx.o \
	build/nw4r/g3d/g3d_restex.o \
	build/asm/nw4r/g3d/g3d_resnode.o \
	build/nw4r/g3d/g3d_resanm.o \
	build/nw4r/g3d/g3d_resanmvis.o \
	build/nw4r/g3d/g3d_resanmclr.o \
	build/asm/nw4r/g3d/g3d_resanmtexpat.o \
	build/asm/nw4r/g3d/g3d_resanmtexsrt.o \
	build/asm/nw4r/g3d/g3d_resanmchr.o \
	build/asm/nw4r/g3d/g3d_reslightset.o \
	build/asm/nw4r/g3d/g3d_anmvis.o \
	build/asm/nw4r/g3d/g3d_anmclr.o \
	build/asm/nw4r/g3d/g3d_anmtexpat.o \
	build/asm/nw4r/g3d/g3d_anmtexsrt.o \
	build/asm/nw4r/g3d/g3d_anmchr.o \
	build/asm/nw4r/g3d/g3d_anmshp.o \
	build/asm/nw4r/g3d/g3d_anmscn.o \
	build/nw4r/g3d/g3d_obj.o \
	build/nw4r/g3d/g3d_anmobj.o \
	build/asm/nw4r/g3d/g3d_gpu.o \
	build/asm/nw4r/g3d/g3d_tmem.o \
	build/nw4r/g3d/g3d_cpu.o \
	build/asm/nw4r/g3d/g3d_state.o \
	build/asm/nw4r/g3d/g3d_draw1mat1shp.o \
	build/asm/nw4r/g3d/g3d_calcview.o \
	build/nw4r/g3d/g3d_dcc.o \
	build/nw4r/g3d/g3d_workmem.o \
	build/asm/nw4r/g3d/g3d_calcworld.o \
	build/asm/nw4r/g3d/g3d_draw.o \
	build/nw4r/g3d/g3d_camera.o \
	build/nw4r/g3d/g3d_basic.o \
	build/asm/nw4r/g3d/g3d_maya.o \
	build/asm/nw4r/g3d/g3d_xsi.o \
	build/asm/nw4r/g3d/g3d_3dsmax.o \
	build/nw4r/g3d/g3d_scnobj.o \
	build/asm/nw4r/g3d/g3d_scnroot.o \
	build/asm/nw4r/g3d/g3d_scnmdlsmpl.o \
	build/asm/nw4r/g3d/g3d_scnmdl.o \
	build/asm/nw4r/g3d/g3d_calcmaterial.o \
	build/nw4r/g3d/g3d_init.o \
	build/nw4r/g3d/g3d_scnmdl1mat1shp.o \
	build/nw4r/g3d/g3d_scnproc.o \
	build/nw4r/g3d/g3d_fog.o \
	build/nw4r/g3d/g3d_light.o \
	build/asm/nw4r/g3d/g3d_calcvtx.o \
	\
	build/asm/nw4r/lyt/lyt_pane.o \
	build/asm/nw4r/lyt/lyt_group.o \
	build/asm/nw4r/lyt/lyt_layout.o \
	build/asm/nw4r/lyt/lyt_picture.o \
	build/asm/nw4r/lyt/lyt_textBox.o \
	build/asm/nw4r/lyt/lyt_window.o \
	build/nw4r/lyt/lyt_bounding.o \
	build/asm/nw4r/lyt/lyt_material.o \
	build/nw4r/lyt/lyt_texMap.o \
	build/nw4r/lyt/lyt_drawInfo.o \
	build/asm/nw4r/lyt/lyt_animation.o \
	build/nw4r/lyt/lyt_resourceAccessor.o \
	build/nw4r/lyt/lyt_arcResourceAccessor.o \
	build/nw4r/lyt/lyt_common.o \

EGG_O_FILES := \
	build/egg/gfx/eggShadowTextureManager.o \
	build/egg/gfx/eggStateGX.o \
	build/egg/gfx/eggTextureBuffer.o \
	build/asm/egg/gfx/eggAnalizeDL.o \
	build/asm/egg/gfx/eggCapTexture.o \
	build/asm/egg/gfx/eggCpuTexture.o \
	build/asm/egg/gfx/eggDrawGX.o \
	build/asm/egg/gfx/eggDrawPathBase.o \
	build/asm/egg/gfx/eggDrawPathBloom.o \
	build/asm/egg/gfx/eggDrawPathDOF.o \
	build/egg/gfx/eggDrawPathHDR.o \
	build/asm/egg/gfx/eggDrawPathShadowVolume.o \
	build/asm/egg/gfx/eggDrawPathLightMap.o \
	build/egg/gfx/eggFog.o \
	build/egg/gfx/eggFogManager.o \
	build/asm/egg/gfx/eggG3DUtility.o \
	build/asm/egg/gfx/eggGfxEngine.o \
	build/asm/egg/gfx/eggLightManager.o \
	build/asm/egg/gfx/eggLightTexture.o \
	build/asm/egg/gfx/eggLightTextureManager.o \
	build/asm/egg/gfx/eggModelBoundingInfo.o \
	build/asm/egg/gfx/eggModelEx.o \
	build/egg/gfx/eggModelSnapshot.o \
	build/egg/gfx/eggPostEffectBase.o \
	build/asm/egg/gfx/eggPostEffectBlur.o \
	build/asm/egg/gfx/eggPostEffectBlurGather.o \
	build/asm/egg/gfx/eggPostEffectBlurSimple.o \
	build/egg/gfx/eggPostEffectHDR.o \
	build/asm/egg/gfx/eggPostEffectMask.o \
	build/egg/gfx/eggPostEffectSimple.o \
	build/egg/gfx/eggScnRootEx.o \
	build/asm/egg/gfx/eggScreen.o \
	build/asm/egg/gfx/eggShadowTexture.o \
	build/egg/gfx/eggIScnProc.o \
	build/egg/gfx/eggScnRenderer.o \
	build/asm/egg/gfx/eggLightObject.o \
	build/asm/egg/gfx/eggPostEffectMaskDOF.o \
	build/asm/egg/gfx/eggScreenEffectBase.o \
	build/asm/egg/gfx/eggFrustum.o \
	build/egg/gfx/eggGXUtility.o \
	build/asm/egg/gfx/eggDrawHelper.o \
	build/asm/egg/gfx/egg_800A1DB0.o \
	\
	build/egg/prim/eggAssert.o \
	build/asm/egg/egg_800A204C.o \
	\
	build/egg/math/eggMath.o \
	build/egg/math/eggMatrix.o \
	build/egg/math/eggQuat.o \
	build/egg/math/eggVector.o \
	\
	build/asm/egg/core/eggExpHeap.o \
	build/asm/egg/core/eggFrmHeap.o \
	build/egg/core/eggHeap.o \
	build/egg/core/eggAllocator.o \
	build/egg/core/eggThread.o \
	build/asm/egg/core/eggSystem.o \
	build/egg/core/eggTaskThread.o \
	build/egg/core/eggGraphicsFifo.o \
	build/egg/core/eggColorFader.o \
	build/egg/core/eggSceneManager.o \
	build/asm/egg/core/eggController.o \
	build/asm/egg/core/eggStream.o \
	build/egg/core/eggDisplay.o \
	build/asm/egg/core/eggVideo.o \
	build/egg/core/eggXfb.o \
	build/egg/core/eggXfbManager.o \
	build/asm/egg/core/eggDvdRipper.o \
	build/egg/core/eggDvdFile.o \
	build/egg/core/eggScene.o \
	build/asm/egg/core/eggProcessMeter.o \
	build/egg/core/eggDisposer.o \
	build/egg/core/eggArchive.o \
	build/asm/egg/core/eggDecomp.o \
	build/egg/core/eggAsyncDisplay.o \
	build/egg/core/eggCntFile.o \
	\
	build/egg/audio/eggAudioArcPlayerMgr.o \
	build/asm/egg/audio/eggAudioExpMgr.o \
	build/asm/egg/audio/eggAudioFxMgr.o \
	build/egg/audio/eggAudioHeapMgr.o \
	build/asm/egg/audio/eggAudioMgr.o \
	build/egg/audio/eggAudioSystem.o \
	\
	build/asm/egg/util/eggMsgRes.o \
	build/egg/util/eggEffect.o \
	build/egg/util/eggException.o \
	build/asm/egg/egg_8037B248.o \

RUNTIME_O_FILES := \
	build/runtime/__mem.o \
	build/asm/runtime/__va_arg.o \
	build/asm/runtime/global_destructor_chain.o \
	build/asm/runtime/NMWException.o \
	build/asm/runtime/ptmf.o \
	build/asm/runtime/runtime.o \
	build/asm/runtime/__init_cpp_exceptions.o \
	build/asm/runtime/Gecko_ExceptionPPC.o \
	build/asm/runtime/GCN_mem_alloc.o \

MSL_O_FILES := \
	build/asm/MSL/alloc.o \
	build/asm/MSL/ansi_files.o \
	build/asm/MSL/ansi_fp.o \
	build/asm/MSL/arith.o \
	build/asm/MSL/buffer_io.o \
	build/asm/MSL/direct_io.o \
	build/asm/MSL/errno.o \
	build/asm/MSL/file_io.o \
	build/asm/MSL/FILE_POS.o \
	build/asm/MSL/locale.o \
	build/asm/MSL/mbstring.o \
	build/asm/MSL/mem.o \
	build/asm/MSL/mem_funcs.o \
	build/asm/MSL/math_api.o \
	build/asm/MSL/misc_io.o \
	build/asm/MSL/printf.o \
	build/asm/MSL/rand.o \
	build/asm/MSL/scanf.o \
	build/asm/MSL/string.o \
	build/asm/MSL/strtold.o \
	build/asm/MSL/strtoul.o \
	build/asm/MSL/wctype.o \
	build/asm/MSL/wmem.o \
	build/asm/MSL/wprintf.o \
	build/asm/MSL/wstring.o \
	build/asm/MSL/wchar_io.o \
	build/asm/MSL/uart_console_io_gcn.o \
	build/asm/MSL/abort_exit_ppc_eabi.o \
	build/asm/MSL/math_sun.o \
	build/asm/MSL/math_float.o \
	build/asm/MSL/extras.o \
	build/asm/MSL/float.o \
	build/asm/MSL/e_acos.o \
	build/asm/MSL/e_asin.o \
	build/asm/MSL/e_atan2.o \
	build/asm/MSL/e_fmod.o \
	build/asm/MSL/e_pow.o \
	build/asm/MSL/e_rem_pio2.o \
	build/asm/MSL/k_cos.o \
	build/asm/MSL/k_rem_pio2.o \
	build/asm/MSL/k_sin.o \
	build/asm/MSL/k_tan.o \
	build/asm/MSL/s_atan.o \
	build/asm/MSL/s_ceil.o \
	build/asm/MSL/s_copysign.o \
	build/asm/MSL/s_cos.o \
	build/asm/MSL/s_floor.o \
	build/asm/MSL/s_frexp.o \
	build/asm/MSL/s_ldexp.o \
	build/asm/MSL/s_modf.o \
	build/asm/MSL/s_sin.o \
	build/asm/MSL/s_tan.o \
	build/asm/MSL/w_acos.o \
	build/asm/MSL/w_asin.o \
	build/asm/MSL/w_atan2.o \
	build/asm/MSL/w_fmod.o \
	build/asm/MSL/w_pow.o \
	build/asm/MSL/e_sqrt.o \
	build/asm/MSL/math_ppc.o \
	build/asm/MSL/w_sqrt.o \

METROTRK_O_FILES := \
	build/asm/MetroTRK/debugger/Portable/mainloop.o \
	build/asm/MetroTRK/debugger/Portable/nubevent.o \
	build/asm/MetroTRK/debugger/Portable/nubinit.o \
	build/asm/MetroTRK/debugger/Portable/msg.o \
	build/asm/MetroTRK/debugger/Portable/msgbuf.o \
	build/asm/MetroTRK/debugger/Portable/serpoll.o \
	build/asm/MetroTRK/debugger/Os/usr_put.o \
	build/asm/MetroTRK/debugger/Portable/dispatch.o \
	build/asm/MetroTRK/debugger/Portable/msghndlr.o \
	build/asm/MetroTRK/debugger/Portable/support.o \
	build/asm/MetroTRK/debugger/Portable/mutex_TRK.o \
	build/asm/MetroTRK/debugger/Portable/notify.o \
	build/asm/MetroTRK/debugger/Processor/flush_cache.o \
	build/asm/MetroTRK/debugger/Portable/mem_TRK.o \
	build/asm/MetroTRK/debugger/Portable/string_TRK.o \
	build/asm/MetroTRK/debugger/Processor/targimpl.o \
	build/asm/MetroTRK/debugger/Processor/targsupp.o \
	build/asm/MetroTRK/debugger/Processor/mpc_7xx_603e.o \
	build/asm/MetroTRK/debugger/Export/mslsupp.o \
	build/asm/MetroTRK/debugger/Processor/__exception.o \
	build/asm/MetroTRK/debugger/Os/dolphin_trk.o \
	build/asm/MetroTRK/debugger/Portable/main_TRK.o \
	build/asm/MetroTRK/debugger/Os/dolphin_trk_glue.o \
	build/asm/MetroTRK/debugger/Os/targcont.o \
	build/asm/MetroTRK/debugger/Os/target_options.o \
	build/asm/MetroTRK/debugger/Os/UDP_Stubs.o \
	\
	build/asm/MetroTRK/gamedev/main.o \
	build/asm/MetroTRK/gamedev/CircleBuffer.o \
	build/asm/MetroTRK/gamedev/MWCriticalSection_gc.o \

RVL_SDK_O_FILES := \
	build/asm/revolution/NdevExi2AD/DebuggerDriver.o \
	build/asm/revolution/NdevExi2AD/exi2.o \
	\
	build/asm/revolution/KPAD/KPAD.o \
	\
	build/asm/revolution/PAD/Pad.o \
	\
	build/asm/revolution/WPAD/WPAD.o \
	build/asm/revolution/WPAD/WPADHIDParser.o \
	build/asm/revolution/WPAD/WPADEncrypt.o \
	build/asm/revolution/WPAD/WPADMem.o \
	build/asm/revolution/WPAD/debug_msg.o \
	\
	build/asm/revolution/EUART/euart.o \
	\
	build/asm/revolution/EXI/EXIBios.o \
	build/asm/revolution/EXI/EXIUart.o \
	build/asm/revolution/EXI/EXICommon.o \
	\
	build/asm/revolution/FS/fs.o \
	\
	build/asm/revolution/GX/GXInit.o \
	build/asm/revolution/GX/GXFifo.o \
	build/asm/revolution/GX/GXAttr.o \
	build/asm/revolution/GX/GXMisc.o \
	build/asm/revolution/GX/GXGeometry.o \
	build/asm/revolution/GX/GXFrameBuf.o \
	build/asm/revolution/GX/GXLight.o \
	build/asm/revolution/GX/GXTexture.o \
	build/asm/revolution/GX/GXBump.o \
	build/asm/revolution/GX/GXTev.o \
	build/asm/revolution/GX/GXPixel.o \
	build/asm/revolution/GX/GXDraw.o \
	build/asm/revolution/GX/GXDisplayList.o \
	build/asm/revolution/GX/GXTransform.o \
	build/asm/revolution/GX/GXPerf.o \
	\
	build/asm/revolution/IPC/ipcMain.o \
	build/asm/revolution/IPC/ipcclt.o \
	build/asm/revolution/IPC/memory.o \
	build/asm/revolution/IPC/ipcProfile.o \
	\
	build/asm/revolution/MEM/mem_heapCommon.o \
	build/asm/revolution/MEM/mem_expHeap.o \
	build/asm/revolution/MEM/mem_frameHeap.o \
	build/asm/revolution/MEM/mem_allocator.o \
	build/asm/revolution/MEM/mem_list.o \
	\
	build/asm/revolution/MTX/mtx.o \
	build/asm/revolution/MTX/mtxvec.o \
	build/asm/revolution/MTX/mtx44.o \
	build/asm/revolution/MTX/vec.o \
	build/asm/revolution/MTX/quat.o \
	\
	build/asm/revolution/NAND/nand.o \
	build/asm/revolution/NAND/NANDOpenClose.o \
	build/asm/revolution/NAND/NANDCore.o \
	build/asm/revolution/NAND/NANDCheck.o \
	\
	build/asm/revolution/OS/OS.o \
	build/asm/revolution/OS/OSAlarm.o \
	build/asm/revolution/OS/OSAlloc.o \
	build/asm/revolution/OS/OSArena.o \
	build/asm/revolution/OS/OSAudioSystem.o \
	build/asm/revolution/OS/OSCache.o \
	build/asm/revolution/OS/OSContext.o \
	build/asm/revolution/OS/OSError.o \
	build/asm/revolution/OS/OSExec.o \
	build/asm/revolution/OS/OSFatal.o \
	build/asm/revolution/OS/OSFont.o \
	build/asm/revolution/OS/OSInterrupt.o \
	build/asm/revolution/OS/OSLink.o \
	build/asm/revolution/OS/OSMessage.o \
	build/asm/revolution/OS/OSMemory.o \
	build/asm/revolution/OS/OSMutex.o \
	build/asm/revolution/OS/OSReset.o \
	build/asm/revolution/OS/OSRtc.o \
	build/asm/revolution/OS/OSSync.o \
	build/asm/revolution/OS/OSThread.o \
	build/asm/revolution/OS/OSTime.o \
	build/asm/revolution/OS/OSUtf.o \
	build/asm/revolution/OS/OSIpc.o \
	build/asm/revolution/OS/OSStateTM.o \
	build/asm/revolution/OS/__start.o \
	build/asm/revolution/OS/OSPlayRecord.o \
	build/asm/revolution/OS/OSStateFlags.o \
	build/asm/revolution/OS/OSNet.o \
	build/asm/revolution/OS/__ppc_eabi_init.o \
	\
	build/asm/revolution/SC/scsystem.o \
	build/asm/revolution/SC/scapi.o \
	build/asm/revolution/SC/scapi_prdinfo.o \
	\
	build/asm/revolution/USB/usb.o \
	\
	build/asm/revolution/VI/vi.o \
	build/asm/revolution/VI/i2c.o \
	build/asm/revolution/VI/vi3in1.o \
	\
	build/asm/revolution/WUD/WUD.o \
	build/asm/revolution/WUD/WUDHidHost.o \
	build/asm/revolution/WUD/debug_msg.o \
	\
	build/asm/revolution/AI/ai.o \
	\
	build/revolution/ARC/arc.o \
	\
	build/asm/revolution/AX/AX.o \
	build/asm/revolution/AX/AXAlloc.o \
	build/asm/revolution/AX/AXAux.o \
	build/asm/revolution/AX/AXCL.o \
	build/asm/revolution/AX/AXOut.o \
	build/asm/revolution/AX/AXSPB.o \
	build/asm/revolution/AX/AXVPB.o \
	build/asm/revolution/AX/AXComp.o \
	build/asm/revolution/AX/DSPCode.o \
	build/asm/revolution/AX/AXProf.o \
	build/asm/revolution/AXFX/AXFXReverbHi.o \
	build/asm/revolution/AXFX/AXFXReverbHiDpl2.o \
	build/asm/revolution/AXFX/AXFXReverbHiExp.o \
	build/asm/revolution/AXFX/AXFXReverbHiExpDpl2.o \
	build/asm/revolution/AXFX/AXFXDelay.o \
	build/asm/revolution/AXFX/AXFXChorus.o \
	build/asm/revolution/AXFX/AXFXChorusExp.o \
	build/asm/revolution/AXFX/AXFXLfoTable.o \
	build/asm/revolution/AXFX/AXFXSrcCoef.o \
	build/asm/revolution/AXFX/AXFXHooks.o \
	\
	build/revolution/BASE/PPCArch.o \
	\
	build/asm/revolution/BTE/bte_unsplit.o \
	\
	build/asm/revolution/DB/db.o \
	\
	build/asm/revolution/DSP/dsp.o \
	build/asm/revolution/DSP/dsp_debug.o \
	build/asm/revolution/DSP/dsp_task.o \
	\
	build/asm/revolution/DVD/dvdfs.o \
	build/asm/revolution/DVD/dvd.o \
	build/asm/revolution/DVD/dvdqueue.o \
	build/asm/revolution/DVD/dvderror.o \
	build/asm/revolution/DVD/dvdidutils.o \
	build/asm/revolution/DVD/dvdFatal.o \
	build/asm/revolution/DVD/dvd_broadway.o \
	\
	build/asm/revolution/SI/SIBios.o \
	build/asm/revolution/SI/SISamplingRate.o \
	\
	build/asm/revolution/TPL/TPL.o \
	\
	build/asm/revolution/WENC/wenc.o \
	\
	build/asm/revolution/CNT/cnt.o \
	\
	build/asm/revolution/ESP/esp.o \
	\
	build/asm/revolution/NET/nettime.o \
	build/asm/revolution/NET/NETVersion.o \
	\
	build/asm/revolution/NWC24/NWC24StdApi.o \
	build/asm/revolution/NWC24/NWC24FileApi.o \
	build/asm/revolution/NWC24/NWC24Config.o \
	build/asm/revolution/NWC24/NWC24Utils.o \
	build/asm/revolution/NWC24/NWC24Manage.o \
	build/asm/revolution/NWC24/NWC24MsgObj.o \
	build/asm/revolution/NWC24/NWC24MBoxCtrl.o \
	build/asm/revolution/NWC24/NWC24Mime.o \
	build/asm/revolution/NWC24/NWC24Parser.o \
	build/asm/revolution/NWC24/NWC24MsgCommit.o \
	build/asm/revolution/NWC24/NWC24Schedule.o \
	build/asm/revolution/NWC24/NWC24DateParser.o \
	build/asm/revolution/NWC24/NWC24FriendList.o \
	build/asm/revolution/NWC24/NWC24SecretFList.o \
	build/asm/revolution/NWC24/NWC24Time.o \
	build/asm/revolution/NWC24/NWC24Ipc.o \
	build/asm/revolution/NWC24/NWC24Download.o \
	build/asm/revolution/NWC24/NWC24System.o \
	\
	build/asm/revolution/VF/vf_unsplit.o \
	\
	build/asm/RVLFaceLib/rfl_unsplit.o \
	\
	build/asm/homebuttonMiniLib/hbm_unsplit.o \


GROUP_1_O_FILES := \
	build/asm/text.o \
	build/asm/data.o \
	build/asm/sdata.o \
	build/asm/ctors.o \
	build/asm/file.o \
	build/asm/rodata.o \
	build/asm/bss.o \
	build/asm/sbss.o \
	build/asm/sdata.o \
	build/asm/sbss2.o \
	build/asm/sdata2.o \

O_FILES := $(GROUP_0_O_FILES) $(NW4R_O_FILES) $(EGG_O_FILES) $(RUNTIME_O_FILES) $(MSL_O_FILES) $(METROTRK_O_FILES) $(RVL_SDK_O_FILES) $(GROUP_1_O_FILES)
