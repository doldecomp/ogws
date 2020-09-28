INIT_O_FILES := \
	build/RevoSDK/TRK/__mem.o \
	build/RevoSDK/TRK_old/mem_TRK.o \
	build/asm/RevoSDK/TRK/__exception.o \
	build/asm/RevoSDK/TRK/dolphin_trk.o \
	build/asm/RevoSDK/TRK/__start.o \
	build/asm/RevoSDK/TRK/__ppc_eabi_init.o \

EXTAB_O_FILES := build/asm/extab.o

EXTABINDEX_O_FILES := build/asm/extabindex.o

TEXT_O_FILES := \
	build/nw4r/ut/ut_list.o \
	build/nw4r/ut/ut_LinkList.o \
	build/nw4r/ut/ut_binaryFileFormat.o \
	build/nw4r/ut/ut_CharStrmReader.o \
	build/nw4r/ut/ut_TagProcessorBase.o \
	build/asm/ctors_1.o \
	build/nw4r/ut/ut_IOStream.o \
	build/nw4r/ut/ut_FileStream.o \
	build/asm/nw4r/ut/ut_DvdFileStream.o \
	build/nw4r/ut/ut_DvdLockedFileStream.o \
	build/nw4r/ut/ut_NandFileStream.o \
	build/nw4r/ut/ut_LockedCache.o \
	build/nw4r/ut/ut_Font.o \
	build/nw4r/ut/ut_RomFont.o \
	build/nw4r/ut/ut_ResFontBase.o \
	build/nw4r/ut/ut_ResFont.o \
	build/asm/nw4r/ut/ut_Color.o \
	build/asm/nw4r/ut/ut_CharWriter.o \
	build/asm/nw4r/ut/ut_TextWriterBase.o \
	build/asm/nw4r/ef/ef_draworder.o \
	build/asm/nw4r/ef/ef_effect.o \
	build/asm/nw4r/ef/ef_effectsystem.o \
	build/asm/nw4r/ef/ef_emitter.o \
	build/asm/nw4r/ef/ef_animcurve.o \
	build/asm/nw4r/ef/ef_particle.o \
	build/asm/nw4r/ef/ef_particlemanager.o \
	build/asm/nw4r/ef/ef_resource.o \
	build/asm/nw4r/ef/ef_util.o \
	build/asm/nw4r/ef/ef_handle.o \
	build/asm/nw4r/ef/ef_emitterform.o \
	build/asm/nw4r/ef/ef_creationqueue.o \
	build/asm/nw4r/ef/ef_emform.o \
	build/asm/nw4r/ef/ef_point.o \
	build/asm/nw4r/ef/ef_line.o \
	build/asm/nw4r/ef/ef_disc.o \
	build/asm/nw4r/ef/ef_sphere.o \
	build/asm/nw4r/ef/ef_cylinder.o \
	build/asm/nw4r/ef/ef_torus.o \
	build/asm/nw4r/ef/ef_cube.o \
	build/asm/nw4r/ef/ef_drawstrategybuilder.o \
	build/asm/nw4r/ef/ef_drawstrategyimpl.o \
	build/asm/nw4r/ef/ef_drawbillboardstrategy.o \
	build/asm/nw4r/ef/ef_drawdirectionalstrategy.o \
	build/asm/nw4r/ef/ef_drawfreestrategy.o \
	build/asm/nw4r/ef/ef_drawlinestrategy.o \
	build/asm/nw4r/ef/ef_drawpointstrategy.o \
	build/asm/nw4r/ef/ef_drawstripestrategy.o \
	build/asm/nw4r/ef/ef_drawsmoothstripestrategy.o \
	build/asm/nw4r/nw4r_8002F700.o \
	build/asm/nw4r/math/math_arithmetic.o \
	build/asm/nw4r/math/math_triangular.o \
	build/asm/nw4r/math/math_types.o \
	build/asm/nw4r/math/math_geometry.o \
	build/asm/nw4r/snd/snd_AxManager.o \
	build/asm/nw4r/snd/snd_AxVoice.o \
	build/asm/nw4r/snd/snd_AxVoiceManager.o \
	build/asm/nw4r/snd/snd_AxfxImpl.o \
	build/asm/nw4r/snd/snd_Bank.o \
	build/asm/nw4r/snd/snd_BankFile.o \
	build/asm/nw4r/snd/snd_BasicPlayer.o \
	build/asm/nw4r/snd/snd_BasicSound.o \
	build/asm/text.o \

CTORS_O_FILES := build/asm/ctors_2.o

DTORS_O_FILES := build/asm/dtors.o

RODATA_O_FILES := build/asm/file.o

DATA_O_FILES := build/asm/rodata.o

DATA6_O_FILES := build/asm/data.o

BSS_O_FILES := build/asm/bss.o

SDATA_O_FILES := build/asm/sdata.o

SBSS_O_FILES := build/asm/sbss.o

SDATA_O_FILES := build/asm/sdata.o

SBSS2_O_FILES := build/asm/sbss2.o

SDATA2_O_FILES := build/asm/sdata2.o

