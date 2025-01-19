#!/usr/bin/env python3

###
# Generates build files for the project.
# This file also includes the project configuration,
# such as compiler flags and the object matching status.
#
# Usage:
#   python3 configure.py
#   ninja
#
# Append --help to see available options.
###

import argparse
import sys
from pathlib import Path

from tools.project import (
    Object,
    ProgressCategory,
    ProjectConfig,
    calculate_progress,
    generate_build,
    is_windows,
)

# Game versions
DEFAULT_VERSION = 0
VERSIONS = [
    "RSPE01_01",  # USA Rev 1
]

parser = argparse.ArgumentParser()
parser.add_argument(
    "mode",
    choices=["configure", "progress"],
    default="configure",
    help="script mode (default: configure)",
    nargs="?",
)
parser.add_argument(
    "-v",
    "--version",
    choices=VERSIONS,
    type=str.upper,
    default=VERSIONS[DEFAULT_VERSION],
    help="version to build",
)
parser.add_argument(
    "--build-dir",
    metavar="DIR",
    type=Path,
    default=Path("build"),
    help="base build directory (default: build)",
)
parser.add_argument(
    "--binutils",
    metavar="BINARY",
    type=Path,
    help="path to binutils (optional)",
)
parser.add_argument(
    "--compilers",
    metavar="DIR",
    type=Path,
    help="path to compilers (optional)",
)
parser.add_argument(
    "--map",
    action="store_true",
    help="generate map file(s)",
)
parser.add_argument(
    "--debug",
    action="store_true",
    help="build with debug info (non-matching)",
)
if not is_windows():
    parser.add_argument(
        "--wrapper",
        metavar="BINARY",
        type=Path,
        help="path to wibo or wine (optional)",
    )
parser.add_argument(
    "--dtk",
    metavar="BINARY | DIR",
    type=Path,
    help="path to decomp-toolkit binary or source (optional)",
)
parser.add_argument(
    "--objdiff",
    metavar="BINARY | DIR",
    type=Path,
    help="path to objdiff-cli binary or source (optional)",
)
parser.add_argument(
    "--sjiswrap",
    metavar="EXE",
    type=Path,
    help="path to sjiswrap.exe (optional)",
)
parser.add_argument(
    "--verbose",
    action="store_true",
    help="print verbose output",
)
parser.add_argument(
    "--non-matching",
    dest="non_matching",
    action="store_true",
    help="builds equivalent (but non-matching) or modded objects",
)
parser.add_argument(
    "--no-progress",
    dest="progress",
    action="store_false",
    help="disable progress calculation",
)
args = parser.parse_args()

config = ProjectConfig()
config.version = str(args.version)
version_num = VERSIONS.index(config.version)

# Apply arguments
config.build_dir = args.build_dir
config.dtk_path = args.dtk
config.objdiff_path = args.objdiff
config.binutils_path = args.binutils
config.compilers_path = args.compilers
config.generate_map = args.map
config.non_matching = args.non_matching
config.sjiswrap_path = args.sjiswrap
config.progress = args.progress
if not is_windows():
    config.wrapper = args.wrapper
# Don't build asm unless we're --non-matching
if not config.non_matching:
    config.asm_dir = None

# Tool versions
config.binutils_tag = "2.42-1"
config.compilers_tag = "20240706"
config.dtk_tag = "v1.3.0"
config.objdiff_tag = "v2.6.0"
config.sjiswrap_tag = "v1.2.0"
config.wibo_tag = "0.6.11"

# Project
config.config_path = Path("config") / config.version / "config.yml"
config.check_sha_path = Path("config") / config.version / "build.sha1"
config.asflags = [
    "-mgekko",
    "--strip-local-absolute",
    "-I include",
    f"-I build/{config.version}/include",
    f"--defsym BUILD_VERSION={version_num}",
]
config.ldflags = [
    "-fp hardware",
    "-nodefaults",
]
if args.debug:
    config.ldflags.append("-gdwarf-2")
if args.map:
    config.ldflags.append("-mapunused")
    config.ldflags.append("-listclosure")

# Use for any additional files that should cause a re-configure when modified
config.reconfig_deps = []

# Optional numeric ID for decomp.me preset
# Can be overridden in libraries or objects
config.scratch_preset_id = None

# Base flags, common to most GC/Wii games.
# Generally leave untouched, with overrides added below.
cflags_base = [
    "-nodefaults",
    "-proc gekko",
    "-align powerpc",
    "-enum int",
    "-fp hardware",
    "-Cpp_exceptions off",
    "-O4,p",
    "-inline auto",
    '-pragma "cats off"',
    '-pragma "warn_notinlined off"',
    "-maxerrors 1",
    "-nosyspath",
    "-RTTI off",
    "-fp_contract on",
    "-str reuse",
    "-i include",
    "-ir include/MSL",
    f"-i build/{config.version}/include",
    f"-DBUILD_VERSION={version_num}",
]

# Debug flags
if args.debug:
    cflags_base.extend(["-sym dwarf-2", "-DDEBUG=1"])
else:
    cflags_base.append("-DNDEBUG=1")

cflags_pedantic = [
    "-w unused",
    "-w missingreturn",
    "-w hidevirtual",
    "-w filecaps",
    "-w sysfilecaps",
    "-w tokenpasting",
    "-w impl_float2int",
    '-pragma "warn_no_explicit_virtual on"',
    "-w err",
]

# Metrowerks library flags
cflags_runtime = [
    *cflags_base,
    "-use_lmw_stmw on",
    "-str reuse,pool,readonly",
    "-fp_contract off",
    "-D_IEEE_LIBM",
]

# MetroTRK flags
cflags_trk = [
    *cflags_base,
    "-use_lmw_stmw on",
    "-str reuse,pool,readonly",
    "-inline deferred",
    "-sdata 0",
]

# NW4R utility library flags
cflags_libnw4r_ut = [
    *cflags_base,
    *cflags_pedantic,
    "-enc SJIS",
    "-fp_contract off",
    "-ipa file",
    "-ir include/revolution",
    "-ir include/nw4r",
]

# NW4R effect library flags
cflags_libnw4r_ef = [
    *cflags_base,
    *cflags_pedantic,
    "-enc SJIS",
    "-fp_contract off",
    "-ipa file",
    "-ir include/revolution",
    "-ir include/nw4r",
]

# NW4R math library flags
cflags_libnw4r_math = [
    *cflags_base,
    *cflags_pedantic,
    "-enc SJIS",
    "-fp_contract off",
    "-ipa file",
    "-ir include/revolution",
    "-ir include/nw4r",
]

# NW4R sound library flags
cflags_libnw4r_snd = [
    *cflags_base,
    *cflags_pedantic,
    "-enc SJIS",
    "-fp_contract off",
    "-ipa file",
    "-ir include/revolution",
    "-ir include/nw4r",
]

# NW4R 3D graphics library flags
cflags_libnw4r_g3d = [
    *cflags_base,
    *cflags_pedantic,
    "-enc SJIS",
    "-fp_contract off",
    "-ipa file",
    "-ir include/revolution",
    "-ir include/nw4r",
]

# NW4R layout library flags
cflags_libnw4r_lyt = [
    *cflags_base,
    *cflags_pedantic,
    "-enc SJIS",
    "-fp_contract off",
    "-ir include/revolution",
    "-ir include/nw4r",
]

# NW4R RFL extension flags
cflags_libnw4r_g3d_scnrfl = [
    *cflags_base,
    *cflags_pedantic,
    "-enc SJIS",
    "-fp_contract on",
    "-use_lmw_stmw on",
    "-inline deferred",
    "-ir include/revolution",
    "-ir include/nw4r",
]

# EGG flags
cflags_egg = [
    *cflags_base,
    "-enc SJIS",
    "-use_lmw_stmw on",
    "-str reuse,pool,readonly",
    "-ir include/revolution",
    "-ir include/nw4r",
    "-ir include/egg",
]

# RVL SDK flags
cflags_rvl = [
    *cflags_base,
    "-enc SJIS",
    "-fp_contract off",
    "-ipa file",
    "-ir include/revolution",
]

# RVLFaceLib flags
cflags_rfl = [
    *cflags_base,
    "-enc SJIS",
    "-fp_contract off",
    "-Cpp_exceptions on",
    "-ipa file",
    "-ir include/revolution",
]


# RP flags
cflags_rp = [
    *cflags_base,
    *cflags_pedantic,
    "-enc SJIS",
    "-inline deferred",
    "-fp_contract on",
    "-use_lmw_stmw on",
    "-str reuse,pool,readonly",
    "-ir include/revolution",
    "-ir include/nw4r",
    "-ir include/egg",
]

config.linker_version = "GC/3.0a5.2"

Matching = True                   # Object matches and should be linked
NonMatching = False               # Object does not match and should not be linked
# Object should be linked when configured with --non-matching
Equivalent = config.non_matching


# Object is only matching for specific versions
def MatchingFor(*versions):
    return config.version in versions


config.warn_missing_config = False  # TODO enable
config.warn_missing_source = False
config.libs = [
    {
        "lib": "libnw4r_ut",
        "mw_version": config.linker_version,
        "cflags": cflags_libnw4r_ut,
        "progress_category": "nw4r",
        "objects": [
            Object(Matching, "nw4r/ut/ut_list.cpp"),
            Object(Matching, "nw4r/ut/ut_LinkList.cpp"),
            Object(Matching, "nw4r/ut/ut_binaryFileFormat.cpp"),
            Object(Matching, "nw4r/ut/ut_CharStrmReader.cpp"),
            Object(Matching, "nw4r/ut/ut_TagProcessorBase.cpp"),
            Object(Matching, "nw4r/ut/ut_IOStream.cpp"),
            Object(Matching, "nw4r/ut/ut_FileStream.cpp"),
            Object(Matching, "nw4r/ut/ut_DvdFileStream.cpp"),
            Object(Matching, "nw4r/ut/ut_DvdLockedFileStream.cpp"),
            Object(Matching, "nw4r/ut/ut_NandFileStream.cpp"),
            Object(Matching, "nw4r/ut/ut_LockedCache.cpp"),
            Object(Matching, "nw4r/ut/ut_Font.cpp"),
            Object(Matching, "nw4r/ut/ut_RomFont.cpp"),
            Object(Matching, "nw4r/ut/ut_ResFontBase.cpp"),
            Object(Matching, "nw4r/ut/ut_ResFont.cpp"),
            Object(Matching, "nw4r/ut/ut_CharWriter.cpp"),
            Object(Matching, "nw4r/ut/ut_TextWriterBase.cpp"),
        ]
    },
    {
        "lib": "libnw4r_ef",
        "mw_version": config.linker_version,
        "cflags": cflags_libnw4r_ef,
        "progress_category": "nw4r",
        "objects": [
            Object(Matching, "nw4r/ef/ef_draworder.cpp"),
            Object(NonMatching, "nw4r/ef/ef_effect.cpp"),
            Object(NonMatching, "nw4r/ef/ef_effectsystem.cpp"),
            Object(Matching, "nw4r/ef/ef_emitter.cpp"),
            Object(NonMatching, "nw4r/ef/ef_animcurve.cpp"),
            Object(Matching, "nw4r/ef/ef_particle.cpp"),
            Object(NonMatching, "nw4r/ef/ef_particlemanager.cpp"),
            Object(NonMatching, "nw4r/ef/ef_resource.cpp"),
            Object(Matching, "nw4r/ef/ef_util.cpp"),
            Object(Matching, "nw4r/ef/ef_handle.cpp"),
            Object(NonMatching, "nw4r/ef/ef_emitterform.cpp"),
            Object(NonMatching, "nw4r/ef/ef_creationqueue.cpp"),
            Object(Matching, "nw4r/ef/ef_emform.cpp"),
            Object(NonMatching, "nw4r/ef/ef_point.cpp"),
            Object(NonMatching, "nw4r/ef/ef_line.cpp"),
            Object(NonMatching, "nw4r/ef/ef_disc.cpp"),
            Object(NonMatching, "nw4r/ef/ef_sphere.cpp"),
            Object(NonMatching, "nw4r/ef/ef_cylinder.cpp"),
            Object(NonMatching, "nw4r/ef/ef_torus.cpp"),
            Object(NonMatching, "nw4r/ef/ef_cube.cpp"),
            Object(Matching, "nw4r/ef/ef_drawstrategybuilder.cpp"),
            Object(NonMatching, "nw4r/ef/ef_drawstrategyimpl.cpp"),
            Object(NonMatching, "nw4r/ef/ef_drawbillboardstrategy.cpp"),
            Object(NonMatching, "nw4r/ef/ef_drawdirectionalstrategy.cpp"),
            Object(NonMatching, "nw4r/ef/ef_drawfreestrategy.cpp"),
            Object(NonMatching, "nw4r/ef/ef_drawlinestrategy.cpp"),
            Object(NonMatching, "nw4r/ef/ef_drawpointstrategy.cpp"),
            Object(NonMatching, "nw4r/ef/ef_drawstripestrategy.cpp"),
            Object(NonMatching, "nw4r/ef/ef_drawsmoothstripestrategy.cpp"),
        ]
    },
    {
        "lib": "libnw4r_math",
        "mw_version": config.linker_version,
        "cflags": cflags_libnw4r_math,
        "progress_category": "nw4r",
        "objects": [
            Object(Matching, "nw4r/math/math_arithmetic.cpp"),
            Object(Matching, "nw4r/math/math_triangular.cpp"),
            Object(Matching, "nw4r/math/math_types.cpp"),
            Object(Matching, "nw4r/math/math_geometry.cpp"),
        ]
    },

    {
        "lib": "libnw4r_snd",
        "mw_version": config.linker_version,
        "cflags": cflags_libnw4r_snd,
        "progress_category": "nw4r",
        "objects": [
            Object(Matching, "nw4r/snd/snd_AnimSound.cpp"),
            Object(Matching, "nw4r/snd/snd_AxManager.cpp"),
            Object(Matching, "nw4r/snd/snd_AxVoice.cpp"),
            Object(Matching, "nw4r/snd/snd_AxVoiceManager.cpp"),
            Object(Matching, "nw4r/snd/snd_AxfxImpl.cpp"),
            Object(Matching, "nw4r/snd/snd_Bank.cpp"),
            Object(Matching, "nw4r/snd/snd_BankFile.cpp"),
            Object(Matching, "nw4r/snd/snd_BasicPlayer.cpp"),
            Object(Matching, "nw4r/snd/snd_BasicSound.cpp"),
            Object(Matching, "nw4r/snd/snd_Channel.cpp"),
            Object(Matching, "nw4r/snd/snd_DisposeCallbackManager.cpp"),
            Object(Matching, "nw4r/snd/snd_DvdSoundArchive.cpp"),
            Object(Matching, "nw4r/snd/snd_EnvGenerator.cpp"),
            Object(Matching, "nw4r/snd/snd_ExternalSoundPlayer.cpp"),
            Object(Matching, "nw4r/snd/snd_FrameHeap.cpp"),
            Object(Matching, "nw4r/snd/snd_FxChorus.cpp"),
            Object(Matching, "nw4r/snd/snd_FxDelay.cpp"),
            Object(Matching, "nw4r/snd/snd_FxReverbHi.cpp"),
            Object(Matching, "nw4r/snd/snd_FxReverbHiDpl2.cpp"),
            Object(Matching, "nw4r/snd/snd_InstancePool.cpp"),
            Object(Matching, "nw4r/snd/snd_Lfo.cpp"),
            Object(Matching, "nw4r/snd/snd_MemorySoundArchive.cpp"),
            Object(Matching, "nw4r/snd/snd_MidiSeqPlayer.cpp"),
            Object(Matching, "nw4r/snd/snd_MmlParser.cpp"),
            Object(Matching, "nw4r/snd/snd_MmlSeqTrack.cpp"),
            Object(Matching, "nw4r/snd/snd_MmlSeqTrackAllocator.cpp"),
            Object(Matching, "nw4r/snd/snd_NandSoundArchive.cpp"),
            Object(Matching, "nw4r/snd/snd_RemoteSpeaker.cpp"),
            Object(Matching, "nw4r/snd/snd_RemoteSpeakerManager.cpp"),
            Object(Matching, "nw4r/snd/snd_SeqFile.cpp"),
            Object(Matching, "nw4r/snd/snd_SeqPlayer.cpp"),
            Object(Matching, "nw4r/snd/snd_SeqSound.cpp"),
            Object(Matching, "nw4r/snd/snd_SeqSoundHandle.cpp"),
            Object(Matching, "nw4r/snd/snd_SeqTrack.cpp"),
            Object(Matching, "nw4r/snd/snd_Sound3DActor.cpp"),
            Object(Matching, "nw4r/snd/snd_Sound3DListener.cpp"),
            Object(Matching, "nw4r/snd/snd_Sound3DManager.cpp"),
            Object(Matching, "nw4r/snd/snd_SoundActor.cpp"),
            Object(Matching, "nw4r/snd/snd_SoundArchive.cpp"),
            Object(Matching, "nw4r/snd/snd_SoundArchiveFile.cpp"),
            Object(Matching, "nw4r/snd/snd_SoundArchiveLoader.cpp"),
            Object(Matching, "nw4r/snd/snd_SoundArchivePlayer.cpp"),
            Object(Matching, "nw4r/snd/snd_SoundHandle.cpp"),
            Object(Matching, "nw4r/snd/snd_SoundHeap.cpp"),
            Object(Matching, "nw4r/snd/snd_SoundPlayer.cpp"),
            Object(Matching, "nw4r/snd/snd_SoundStartable.cpp"),
            Object(Matching, "nw4r/snd/snd_SoundSystem.cpp"),
            Object(Matching, "nw4r/snd/snd_SoundThread.cpp"),
            Object(Matching, "nw4r/snd/snd_StrmChannel.cpp"),
            Object(Matching, "nw4r/snd/snd_StrmFile.cpp"),
            Object(Matching, "nw4r/snd/snd_StrmPlayer.cpp"),
            Object(Matching, "nw4r/snd/snd_StrmSound.cpp"),
            Object(Matching, "nw4r/snd/snd_StrmSoundHandle.cpp"),
            Object(Matching, "nw4r/snd/snd_Task.cpp"),
            Object(Matching, "nw4r/snd/snd_TaskManager.cpp"),
            Object(Matching, "nw4r/snd/snd_TaskThread.cpp"),
            Object(Matching, "nw4r/snd/snd_Voice.cpp"),
            Object(Matching, "nw4r/snd/snd_VoiceManager.cpp"),
            Object(Matching, "nw4r/snd/snd_Util.cpp"),
            Object(Matching, "nw4r/snd/snd_WaveFile.cpp"),
            Object(Matching, "nw4r/snd/snd_WaveSound.cpp"),
            Object(Matching, "nw4r/snd/snd_WaveSoundHandle.cpp"),
            Object(Matching, "nw4r/snd/snd_WsdFile.cpp"),
            Object(Matching, "nw4r/snd/snd_WsdPlayer.cpp"),
            Object(Matching, "nw4r/snd/snd_adpcm.cpp"),
        ]
    },
    {
        "lib": "libnw4r_g3d",
        "mw_version": config.linker_version,
        "cflags": cflags_libnw4r_g3d,
        "progress_category": "nw4r",
        "objects": [
            Object(Matching, "nw4r/g3d/res/g3d_rescommon.cpp"),
            Object(Matching, "nw4r/g3d/res/g3d_resdict.cpp"),
            Object(Matching, "nw4r/g3d/res/g3d_resfile.cpp"),
            Object(Matching, "nw4r/g3d/res/g3d_resmdl.cpp"),
            Object(Matching, "nw4r/g3d/res/g3d_resshp.cpp"),
            Object(Matching, "nw4r/g3d/res/g3d_restev.cpp"),
            Object(Matching, "nw4r/g3d/res/g3d_resmat.cpp"),
            Object(Matching, "nw4r/g3d/res/g3d_resvtx.cpp"),
            Object(Matching, "nw4r/g3d/res/g3d_restex.cpp"),
            Object(Matching, "nw4r/g3d/res/g3d_resnode.cpp"),
            Object(Matching, "nw4r/g3d/res/g3d_resanm.cpp"),
            Object(Matching, "nw4r/g3d/res/g3d_resanmvis.cpp"),
            Object(Matching, "nw4r/g3d/res/g3d_resanmclr.cpp"),
            Object(Matching, "nw4r/g3d/res/g3d_resanmtexpat.cpp"),
            Object(Matching, "nw4r/g3d/res/g3d_resanmtexsrt.cpp"),
            Object(Matching, "nw4r/g3d/res/g3d_resanmchr.cpp"),
            Object(Matching, "nw4r/g3d/res/g3d_reslightset.cpp"),
            Object(Matching, "nw4r/g3d/res/g3d_resanmamblight.cpp"),
            Object(Matching, "nw4r/g3d/res/g3d_resanmlight.cpp"),
            Object(Matching, "nw4r/g3d/res/g3d_resanmfog.cpp"),
            Object(Matching, "nw4r/g3d/res/g3d_resanmcamera.cpp"),
            Object(Matching, "nw4r/g3d/res/g3d_resanmscn.cpp"),
            Object(Matching, "nw4r/g3d/res/g3d_resanmshp.cpp"),
            Object(Matching, "nw4r/g3d/g3d_anmvis.cpp"),
            Object(Matching, "nw4r/g3d/g3d_anmclr.cpp"),
            Object(Matching, "nw4r/g3d/g3d_anmtexpat.cpp"),
            Object(Matching, "nw4r/g3d/g3d_anmtexsrt.cpp"),
            Object(Matching, "nw4r/g3d/g3d_anmchr.cpp"),
            Object(Matching, "nw4r/g3d/g3d_anmshp.cpp"),
            Object(Matching, "nw4r/g3d/g3d_anmscn.cpp"),
            Object(Matching, "nw4r/g3d/g3d_obj.cpp"),
            Object(Matching, "nw4r/g3d/g3d_anmobj.cpp"),
            Object(Matching, "nw4r/g3d/platform/g3d_gpu.cpp"),
            Object(Matching, "nw4r/g3d/platform/g3d_tmem.cpp"),
            Object(Matching, "nw4r/g3d/platform/g3d_cpu.cpp"),
            Object(Matching, "nw4r/g3d/g3d_state.cpp"),
            Object(Matching, "nw4r/g3d/g3d_draw1mat1shp.cpp"),
            Object(Matching, "nw4r/g3d/g3d_calcview.cpp"),
            Object(Matching, "nw4r/g3d/g3d_dcc.cpp"),
            Object(Matching, "nw4r/g3d/g3d_workmem.cpp"),
            Object(Matching, "nw4r/g3d/g3d_calcworld.cpp"),
            Object(Matching, "nw4r/g3d/g3d_draw.cpp"),
            Object(Matching, "nw4r/g3d/g3d_camera.cpp"),
            Object(Matching, "nw4r/g3d/g3d_basic.cpp"),
            Object(Matching, "nw4r/g3d/g3d_maya.cpp"),
            Object(Matching, "nw4r/g3d/g3d_xsi.cpp"),
            Object(Matching, "nw4r/g3d/g3d_3dsmax.cpp"),
            Object(Matching, "nw4r/g3d/g3d_scnobj.cpp"),
            Object(Matching, "nw4r/g3d/g3d_scnroot.cpp"),
            Object(Matching, "nw4r/g3d/g3d_scnmdlsmpl.cpp"),
            Object(Matching, "nw4r/g3d/g3d_scnmdl.cpp"),
            Object(Matching, "nw4r/g3d/g3d_calcmaterial.cpp"),
            Object(Matching, "nw4r/g3d/g3d_init.cpp"),
            Object(Matching, "nw4r/g3d/g3d_scnmdl1mat1shp.cpp"),
            Object(Matching, "nw4r/g3d/g3d_scnproc.cpp"),
            Object(Matching, "nw4r/g3d/g3d_fog.cpp"),
            Object(Matching, "nw4r/g3d/g3d_light.cpp"),
            Object(Matching, "nw4r/g3d/g3d_calcvtx.cpp"),
        ]
    },
    {
        "lib": "libnw4r_lyt",
        "mw_version": config.linker_version,
        "cflags": cflags_libnw4r_lyt,
        "progress_category": "nw4r",
        "objects": [
            Object(NonMatching, "nw4r/lyt/lyt_pane.cpp"),
            Object(NonMatching, "nw4r/lyt/lyt_group.cpp"),
            Object(NonMatching, "nw4r/lyt/lyt_layout.cpp"),
            Object(NonMatching, "nw4r/lyt/lyt_picture.cpp"),
            Object(NonMatching, "nw4r/lyt/lyt_textBox.cpp"),
            Object(NonMatching, "nw4r/lyt/lyt_window.cpp"),
            Object(Matching, "nw4r/lyt/lyt_bounding.cpp"),
            Object(NonMatching, "nw4r/lyt/lyt_material.cpp"),
            Object(Matching, "nw4r/lyt/lyt_texMap.cpp"),
            Object(Matching, "nw4r/lyt/lyt_drawInfo.cpp"),
            Object(NonMatching, "nw4r/lyt/lyt_animation.cpp"),
            Object(Matching, "nw4r/lyt/lyt_resourceAccessor.cpp"),
            Object(Matching, "nw4r/lyt/lyt_arcResourceAccessor.cpp"),
            Object(Matching, "nw4r/lyt/lyt_common.cpp"),
        ]
    },
    {
        "lib": "libnw4r_g3d_scnrfl",
        "mw_version": config.linker_version,
        "cflags": cflags_libnw4r_g3d_scnrfl,
        "progress_category": "nw4r",
        "objects": [
            Object(Matching, "nw4r/g3d/g3d_scnrfl.cpp"),
        ],
    },
    {
        "lib": "egg",
        "mw_version": config.linker_version,
        "cflags": cflags_egg,
        "progress_category": "egg",
        "objects": [
            Object(Matching, "egg/gfx/eggShadowTextureManager.cpp"),
            Object(Matching, "egg/gfx/eggStateGX.cpp"),
            Object(Matching, "egg/gfx/eggTextureBuffer.cpp"),
            Object(NonMatching, "egg/gfx/eggAnalizeDL.cpp"),
            Object(NonMatching, "egg/gfx/eggCapTexture.cpp"),
            Object(NonMatching, "egg/gfx/eggCpuTexture.cpp"),
            Object(NonMatching, "egg/gfx/eggDrawGX.cpp"),
            Object(NonMatching, "egg/gfx/eggDrawPathBase.cpp"),
            Object(NonMatching, "egg/gfx/eggDrawPathBloom.cpp"),
            Object(NonMatching, "egg/gfx/eggDrawPathDOF.cpp"),
            Object(Matching, "egg/gfx/eggDrawPathHDR.cpp"),
            Object(NonMatching, "egg/gfx/eggDrawPathShadowVolume.cpp"),
            Object(NonMatching, "egg/gfx/eggDrawPathLightMap.cpp"),
            Object(Matching, "egg/gfx/eggFog.cpp"),
            Object(Matching, "egg/gfx/eggFogManager.cpp"),
            Object(NonMatching, "egg/gfx/eggG3DUtility.cpp"),
            Object(NonMatching, "egg/gfx/eggGfxEngine.cpp"),
            Object(NonMatching, "egg/gfx/eggLightManager.cpp"),
            Object(NonMatching, "egg/gfx/eggLightTexture.cpp"),
            Object(NonMatching, "egg/gfx/eggLightTextureManager.cpp"),
            Object(NonMatching, "egg/gfx/eggModelBoundingInfo.cpp"),
            Object(NonMatching, "egg/gfx/eggModelEx.cpp"),
            Object(Matching, "egg/gfx/eggModelSnapshot.cpp"),
            Object(Matching, "egg/gfx/eggPostEffectBase.cpp"),
            Object(NonMatching, "egg/gfx/eggPostEffectBlur.cpp"),
            Object(NonMatching, "egg/gfx/eggPostEffectBlurGather.cpp"),
            Object(NonMatching, "egg/gfx/eggPostEffectBlurSimple.cpp"),
            Object(Matching, "egg/gfx/eggPostEffectHDR.cpp"),
            Object(NonMatching, "egg/gfx/eggPostEffectMask.cpp"),
            Object(Matching, "egg/gfx/eggPostEffectSimple.cpp"),
            Object(Matching, "egg/gfx/eggScnRootEx.cpp"),
            Object(NonMatching, "egg/gfx/eggScreen.cpp"),
            Object(NonMatching, "egg/gfx/eggShadowTexture.cpp"),
            Object(Matching, "egg/gfx/eggIScnProc.cpp"),
            Object(Matching, "egg/gfx/eggScnRenderer.cpp"),
            Object(NonMatching, "egg/gfx/eggLightObject.cpp"),
            Object(NonMatching, "egg/gfx/eggPostEffectMaskDOF.cpp"),
            Object(NonMatching, "egg/gfx/eggScreenEffectBase.cpp"),
            Object(NonMatching, "egg/gfx/eggFrustum.cpp"),
            Object(Matching, "egg/gfx/eggGXUtility.cpp"),
            Object(NonMatching, "egg/gfx/eggDrawHelper.cpp"),
            Object(Matching, "egg/prim/eggAssert.cpp",
                   extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "egg/math/eggMath.cpp",
                   extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "egg/math/eggMatrix.cpp",
                   extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "egg/math/eggQuat.cpp",
                   extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "egg/math/eggVector.cpp",
                   extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "egg/core/eggExpHeap.cpp"),
            Object(NonMatching, "egg/core/eggFrmHeap.cpp"),
            Object(Matching, "egg/core/eggHeap.cpp"),
            Object(Matching, "egg/core/eggAllocator.cpp"),
            Object(Matching, "egg/core/eggThread.cpp"),
            Object(NonMatching, "egg/core/eggSystem.cpp"),
            Object(Matching, "egg/core/eggTaskThread.cpp"),
            Object(Matching, "egg/core/eggGraphicsFifo.cpp"),
            Object(Matching, "egg/core/eggColorFader.cpp"),
            Object(Matching, "egg/core/eggSceneManager.cpp"),
            Object(NonMatching, "egg/core/eggController.cpp"),
            Object(NonMatching, "egg/core/eggStream.cpp"),
            Object(Matching, "egg/core/eggDisplay.cpp"),
            Object(NonMatching, "egg/core/eggVideo.cpp"),
            Object(Matching, "egg/core/eggXfb.cpp"),
            Object(Matching, "egg/core/eggXfbManager.cpp"),
            Object(NonMatching, "egg/core/eggDvdRipper.cpp"),
            Object(Matching, "egg/core/eggDvdFile.cpp"),
            Object(Matching, "egg/core/eggScene.cpp"),
            Object(NonMatching, "egg/core/eggProcessMeter.cpp"),
            Object(Matching, "egg/core/eggDisposer.cpp"),
            Object(Matching, "egg/core/eggArchive.cpp"),
            Object(NonMatching, "egg/core/eggDecomp.cpp"),
            Object(Matching, "egg/core/eggAsyncDisplay.cpp"),
            Object(Matching, "egg/core/eggCntFile.cpp"),
            Object(Matching, "egg/audio/eggAudioArcPlayerMgr.cpp"),
            Object(NonMatching, "egg/audio/eggAudioExpMgr.cpp"),
            Object(NonMatching, "egg/audio/eggAudioFxMgr.cpp"),
            Object(Matching, "egg/audio/eggAudioHeapMgr.cpp"),
            Object(NonMatching, "egg/audio/eggAudioMgr.cpp"),
            Object(Matching, "egg/audio/eggAudioSystem.cpp"),
            Object(NonMatching, "egg/util/eggMsgRes.cpp"),
            Object(NonMatching, "egg/util/eggEffect.cpp"),
            Object(Matching, "egg/util/eggException.cpp"),
        ],
    },
    {
        "lib": "Runtime.PPCEABI.H",
        "mw_version": config.linker_version,
        "cflags": cflags_runtime,
        "progress_category": "sdk",
        "objects": [
            Object(Matching, "runtime/__mem.c"),
            Object(Matching, "runtime/__va_arg.c"),
            Object(NonMatching, "runtime/global_destructor_chain.c"),
            Object(NonMatching, "runtime/NMWException.c"),
            Object(Matching, "runtime/ptmf.c"),
            Object(Matching, "runtime/runtime.c"),
            Object(NonMatching, "runtime/__init_cpp_exceptions.cpp"),
            Object(Matching, "runtime/Gecko_ExceptionPPC.c"),
            Object(Matching, "runtime/GCN_mem_alloc.c"),
        ],
    },
    {
        "lib": "MSL_C",
        "mw_version": "GC/3.0a3",
        "cflags": cflags_runtime,
        "progress_category": "sdk",
        "objects": [
            Object(NonMatching, "MSL/alloc.c"),
            Object(NonMatching, "MSL/ansi_files.c"),
            Object(NonMatching, "MSL/ansi_fp.c"),
            Object(NonMatching, "MSL/arith.c"),
            Object(NonMatching, "MSL/buffer_io.c"),
            Object(NonMatching, "MSL/direct_io.c"),
            Object(NonMatching, "MSL/errno.c"),
            Object(NonMatching, "MSL/file_io.c"),
            Object(NonMatching, "MSL/FILE_POS.c"),
            Object(NonMatching, "MSL/locale.c"),
            Object(NonMatching, "MSL/mbstring.c"),
            Object(NonMatching, "MSL/mem.c"),
            Object(NonMatching, "MSL/mem_funcs.c"),
            Object(NonMatching, "MSL/math_api.c"),
            Object(NonMatching, "MSL/misc_io.c"),
            Object(NonMatching, "MSL/printf.c"),
            Object(NonMatching, "MSL/rand.c"),
            Object(NonMatching, "MSL/scanf.c"),
            Object(NonMatching, "MSL/string.c"),
            Object(NonMatching, "MSL/strtold.c"),
            Object(NonMatching, "MSL/strtoul.c"),
            Object(NonMatching, "MSL/wctype.c"),
            Object(NonMatching, "MSL/wmem.c"),
            Object(NonMatching, "MSL/wprintf.c"),
            Object(NonMatching, "MSL/wstring.c"),
            Object(NonMatching, "MSL/wchar_io.c"),
            Object(NonMatching, "MSL/uart_console_io_gcn.c"),
            Object(NonMatching, "MSL/abort_exit_ppc_eabi.c"),
            Object(NonMatching, "MSL/math_sun.c"),
            Object(NonMatching, "MSL/math_float.c"),
            Object(NonMatching, "MSL/extras.c"),
            Object(Matching, "MSL/float.c"),
            Object(Matching, "MSL/e_acos.c"),
            Object(Matching, "MSL/e_asin.c"),
            Object(Matching, "MSL/e_atan2.c"),
            Object(Matching, "MSL/e_fmod.c"),
            Object(Matching, "MSL/e_pow.c"),
            Object(Matching, "MSL/e_rem_pio2.c"),
            Object(Matching, "MSL/k_cos.c"),
            Object(Matching, "MSL/k_rem_pio2.c"),
            Object(Matching, "MSL/k_sin.c"),
            Object(Matching, "MSL/k_tan.c"),
            Object(Matching, "MSL/s_atan.c"),
            Object(Matching, "MSL/s_ceil.c"),
            Object(Matching, "MSL/s_copysign.c"),
            Object(Matching, "MSL/s_cos.c"),
            Object(Matching, "MSL/s_floor.c"),
            Object(Matching, "MSL/s_frexp.c"),
            Object(Matching, "MSL/s_ldexp.c"),
            Object(Matching, "MSL/s_modf.c"),
            Object(Matching, "MSL/s_sin.c"),
            Object(Matching, "MSL/s_tan.c"),
            Object(Matching, "MSL/w_acos.c"),
            Object(Matching, "MSL/w_asin.c"),
            Object(Matching, "MSL/w_atan2.c"),
            Object(Matching, "MSL/w_fmod.c"),
            Object(Matching, "MSL/w_pow.c"),
            Object(Matching, "MSL/e_sqrt.c"),
            Object(Matching, "MSL/math_ppc.c"),
            Object(Matching, "MSL/w_sqrt.c"),
        ],
    },
    {
        "lib": "MetroTRK",
        "mw_version": "GC/2.7",
        "cflags": cflags_trk,
        "progress_category": "sdk",
        "objects": [
            Object(NonMatching, "MetroTRK/debugger/Portable/mainloop.c"),
            Object(Matching, "MetroTRK/debugger/Portable/nubevent.c"),
            Object(NonMatching, "MetroTRK/debugger/Portable/nubinit.c"),
            Object(Matching, "MetroTRK/debugger/Portable/msg.c"),
            Object(Matching, "MetroTRK/debugger/Portable/msgbuf.c"),
            Object(NonMatching, "MetroTRK/debugger/Portable/serpoll.c"),
            Object(NonMatching, "MetroTRK/debugger/Os/dolphin/usr_put.c"),
            Object(Matching, "MetroTRK/debugger/Portable/dispatch.c"),
            Object(NonMatching, "MetroTRK/debugger/Portable/msghndlr.c"),
            Object(NonMatching, "MetroTRK/debugger/Portable/support.c"),
            Object(Matching, "MetroTRK/debugger/Portable/mutex_TRK.c"),
            Object(NonMatching, "MetroTRK/debugger/Portable/notify.c"),
            Object(NonMatching, "MetroTRK/debugger/Processor/flush_cache.c"),
            Object(NonMatching, "MetroTRK/debugger/Portable/mem_TRK.c"),
            Object(NonMatching, "MetroTRK/debugger/Portable/string_TRK.c"),
            Object(NonMatching, "MetroTRK/debugger/Processor/targimpl.c"),
            Object(NonMatching, "MetroTRK/debugger/Processor/targsupp.c"),
            Object(NonMatching, "MetroTRK/debugger/Processor/mpc_7xx_603e.c"),
            Object(NonMatching, "MetroTRK/debugger/Export/mslsupp.c"),
            Object(NonMatching, "MetroTRK/debugger/Processor/__exception.c"),
            Object(NonMatching, "MetroTRK/debugger/Os/dolphin/dolphin_trk.c"),
            Object(NonMatching, "MetroTRK/debugger/Portable/main_TRK.c"),
            Object(NonMatching, "MetroTRK/debugger/Os/dolphin/dolphin_trk_glue.c"),
            Object(NonMatching, "MetroTRK/debugger/Os/dolphin/targcont.c"),
            Object(NonMatching, "MetroTRK/debugger/Os/dolphin/target_options.c"),
            Object(NonMatching, "MetroTRK/debugger/Os/dolphin/UDP_Stubs.c"),
            Object(NonMatching, "MetroTRK/gamedev/main.c"),
            Object(NonMatching, "MetroTRK/gamedev/CircleBuffer.c"),
            Object(NonMatching, "MetroTRK/gamedev/MWCriticalSection_gc.c"),
        ],
    },
    {
        "lib": "RVL_SDK",
        "mw_version": config.linker_version,
        "cflags": cflags_rvl,
        "progress_category": "sdk",
        "objects": [
            Object(NonMatching, "revolution/NdevExi2AD/DebuggerDriver.c"),
            Object(Matching, "revolution/NdevExi2AD/exi2.c"),
            Object(NonMatching, "revolution/KPAD/KPAD.c"),
            Object(Matching, "revolution/PAD/Pad.c"),
            Object(NonMatching, "revolution/WPAD/WPAD.c"),
            Object(NonMatching, "revolution/WPAD/WPADHIDParser.c"),
            Object(NonMatching, "revolution/WPAD/WPADEncrypt.c"),
            Object(NonMatching, "revolution/WPAD/WPADMem.c"),
            Object(NonMatching, "revolution/WPAD/debug_msg.c"),
            Object(Matching, "revolution/EUART/euart.c"),
            Object(Matching, "revolution/EXI/EXIBios.c",
                   extra_cflags=["-schedule off"]),
            Object(Matching, "revolution/EXI/EXIUart.c"),
            Object(Matching, "revolution/EXI/EXICommon.c"),
            Object(Matching, "revolution/FS/fs.c"),
            Object(NonMatching, "revolution/GX/GXInit.c"),
            Object(NonMatching, "revolution/GX/GXFifo.c"),
            Object(Matching, "revolution/GX/GXAttr.c"),
            Object(NonMatching, "revolution/GX/GXMisc.c"),
            Object(Matching, "revolution/GX/GXGeometry.c"),
            Object(NonMatching, "revolution/GX/GXFrameBuf.c"),
            Object(Matching, "revolution/GX/GXLight.c"),
            Object(NonMatching, "revolution/GX/GXTexture.c"),
            Object(Matching, "revolution/GX/GXBump.c"),
            Object(NonMatching, "revolution/GX/GXTev.c"),
            Object(Matching, "revolution/GX/GXPixel.c"),
            Object(Matching, "revolution/GX/GXDraw.c"),
            Object(Matching, "revolution/GX/GXDisplayList.c"),
            Object(Matching, "revolution/GX/GXTransform.c"),
            Object(NonMatching, "revolution/GX/GXPerf.c"),
            Object(Matching, "revolution/IPC/ipcMain.c"),
            Object(Matching, "revolution/IPC/ipcclt.c"),
            Object(Matching, "revolution/IPC/memory.c"),
            Object(Matching, "revolution/IPC/ipcProfile.c"),
            Object(Matching, "revolution/MEM/mem_heapCommon.c"),
            Object(NonMatching, "revolution/MEM/mem_expHeap.c"),
            Object(Matching, "revolution/MEM/mem_frameHeap.c"),
            Object(Matching, "revolution/MEM/mem_allocator.c"),
            Object(Matching, "revolution/MEM/mem_list.c"),
            Object(NonMatching, "revolution/MTX/mtx.c"),
            Object(Matching, "revolution/MTX/mtxvec.c"),
            Object(Matching, "revolution/MTX/mtx44.c"),
            Object(Matching, "revolution/MTX/vec.c"),
            Object(Matching, "revolution/MTX/quat.c"),
            Object(Matching, "revolution/NAND/nand.c"),
            Object(Matching, "revolution/NAND/NANDOpenClose.c"),
            Object(Matching, "revolution/NAND/NANDCore.c"),
            Object(Matching, "revolution/NAND/NANDCheck.c"),
            Object(Matching, "revolution/OS/OS.c"),
            Object(Matching, "revolution/OS/OSAlarm.c"),
            Object(Matching, "revolution/OS/OSAlloc.c"),
            Object(Matching, "revolution/OS/OSArena.c"),
            Object(Matching, "revolution/OS/OSAudioSystem.c"),
            Object(Matching, "revolution/OS/OSCache.c"),
            Object(Matching, "revolution/OS/OSContext.c"),
            Object(Matching, "revolution/OS/OSError.c"),
            Object(Matching, "revolution/OS/OSExec.c"),
            Object(Matching, "revolution/OS/OSFatal.c"),
            Object(Matching, "revolution/OS/OSFont.c"),
            Object(Matching, "revolution/OS/OSInterrupt.c"),
            Object(Matching, "revolution/OS/OSLink.c"),
            Object(Matching, "revolution/OS/OSMessage.c"),
            Object(Matching, "revolution/OS/OSMemory.c"),
            Object(Matching, "revolution/OS/OSMutex.c"),
            Object(Matching, "revolution/OS/OSReset.c"),
            Object(Matching, "revolution/OS/OSRtc.c"),
            Object(Matching, "revolution/OS/OSSync.c"),
            Object(Matching, "revolution/OS/OSThread.c"),
            Object(Matching, "revolution/OS/OSTime.c"),
            Object(Matching, "revolution/OS/OSUtf.c"),
            Object(Matching, "revolution/OS/OSIpc.c"),
            Object(Matching, "revolution/OS/OSStateTM.c"),
            Object(Matching, "revolution/OS/__start.c"),
            Object(Matching, "revolution/OS/OSPlayRecord.c"),
            Object(Matching, "revolution/OS/OSStateFlags.c"),
            Object(Matching, "revolution/OS/OSNet.c"),
            Object(NonMatching, "revolution/OS/__ppc_eabi_init.c"),
            Object(Matching, "revolution/SC/scsystem.c"),
            Object(Matching, "revolution/SC/scapi.c"),
            Object(Matching, "revolution/SC/scapi_prdinfo.c"),
            Object(Matching, "revolution/USB/usb.c"),
            Object(NonMatching, "revolution/VI/vi.c"),
            Object(NonMatching, "revolution/VI/i2c.c"),
            Object(NonMatching, "revolution/VI/vi3in1.c"),
            Object(NonMatching, "revolution/WUD/WUD.c"),
            Object(NonMatching, "revolution/WUD/WUDHidHost.c"),
            Object(NonMatching, "revolution/WUD/debug_msg.c"),
            Object(Matching, "revolution/AI/ai.c"),
            Object(Matching, "revolution/ARC/arc.c"),
            Object(Matching, "revolution/AX/AX.c"),
            Object(Matching, "revolution/AX/AXAlloc.c"),
            Object(Matching, "revolution/AX/AXAux.c"),
            Object(Matching, "revolution/AX/AXCL.c"),
            Object(Matching, "revolution/AX/AXOut.c"),
            Object(Matching, "revolution/AX/AXSPB.c"),
            Object(Matching, "revolution/AX/AXVPB.c"),
            Object(Matching, "revolution/AX/AXComp.c"),
            Object(Matching, "revolution/AX/DSPCode.c"),
            Object(Matching, "revolution/AX/AXProf.c"),
            Object(Matching, "revolution/AXFX/AXFXReverbHi.c"),
            Object(Matching, "revolution/AXFX/AXFXReverbHiDpl2.c"),
            Object(NonMatching, "revolution/AXFX/AXFXReverbHiExp.c"),
            Object(NonMatching, "revolution/AXFX/AXFXReverbHiExpDpl2.c"),
            Object(Matching, "revolution/AXFX/AXFXDelay.c"),
            Object(Matching, "revolution/AXFX/AXFXChorus.c"),
            Object(NonMatching, "revolution/AXFX/AXFXChorusExp.c"),
            Object(Matching, "revolution/AXFX/AXFXLfoTable.c"),
            Object(Matching, "revolution/AXFX/AXFXSrcCoef.c"),
            Object(Matching, "revolution/AXFX/AXFXHooks.c"),
            Object(Matching, "revolution/BASE/PPCArch.c"),
            Object(NonMatching, "revolution/BTE/bte_unsplit.c"),
            Object(Matching, "revolution/DB/db.c"),
            Object(Matching, "revolution/DSP/dsp.c"),
            Object(Matching, "revolution/DSP/dsp_debug.c"),
            Object(Matching, "revolution/DSP/dsp_task.c"),
            Object(Matching, "revolution/DVD/dvdfs.c"),
            Object(Matching, "revolution/DVD/dvd.c"),
            Object(Matching, "revolution/DVD/dvdqueue.c"),
            Object(Matching, "revolution/DVD/dvderror.c"),
            Object(Matching, "revolution/DVD/dvdidutils.c"),
            Object(Matching, "revolution/DVD/dvdFatal.c"),
            Object(Matching, "revolution/DVD/dvd_broadway.c"),
            Object(NonMatching, "revolution/SI/SIBios.c"),
            Object(Matching, "revolution/SI/SISamplingRate.c"),
            Object(Matching, "revolution/TPL/TPL.c"),
            Object(Matching, "revolution/WENC/wenc.c"),
            Object(NonMatching, "revolution/CNT/cnt.c"),
            Object(Matching, "revolution/ESP/esp.c"),
            Object(NonMatching, "revolution/NET/nettime.c"),
            Object(NonMatching, "revolution/NET/NETVersion.c"),
            Object(NonMatching, "revolution/NWC24/NWC24StdApi.c"),
            Object(Matching, "revolution/NWC24/NWC24FileApi.c"),
            Object(Matching, "revolution/NWC24/NWC24Config.c"),
            Object(Matching, "revolution/NWC24/NWC24Utils.c"),
            Object(Matching, "revolution/NWC24/NWC24Manage.c"),
            Object(Matching, "revolution/NWC24/NWC24MsgObj.c"),
            Object(NonMatching, "revolution/NWC24/NWC24MBoxCtrl.c"),
            Object(NonMatching, "revolution/NWC24/NWC24Mime.c"),
            Object(Matching, "revolution/NWC24/NWC24Parser.c"),
            Object(NonMatching, "revolution/NWC24/NWC24MsgCommit.c"),
            Object(Matching, "revolution/NWC24/NWC24Schedule.c"),
            Object(NonMatching, "revolution/NWC24/NWC24DateParser.c"),
            Object(Matching, "revolution/NWC24/NWC24FriendList.c"),
            Object(Matching, "revolution/NWC24/NWC24SecretFList.c"),
            Object(Matching, "revolution/NWC24/NWC24Time.c"),
            Object(Matching, "revolution/NWC24/NWC24Ipc.c"),
            Object(Matching, "revolution/NWC24/NWC24Download.c"),
            Object(Matching, "revolution/NWC24/NWC24System.c"),
        ],
    },
    {
        "lib": "RVLFaceLib",
        "mw_version": config.linker_version,
        "cflags": cflags_rfl,
        "progress_category": "rfl",
        "objects": [
            Object(Matching, "RVLFaceLib/RFL_System.c"),
            Object(Matching, "RVLFaceLib/RFL_NANDLoader.c"),
            Object(Matching, "RVLFaceLib/RFL_NANDAccess.c"),
            Object(Matching, "RVLFaceLib/RFL_Model.c"),
            Object(Matching, "RVLFaceLib/RFL_MakeTex.c"),
            Object(Matching, "RVLFaceLib/RFL_Icon.c"),
            Object(Matching, "RVLFaceLib/RFL_HiddenDatabase.c"),
            Object(Matching, "RVLFaceLib/RFL_Database.c"),
            Object(Matching, "RVLFaceLib/RFL_Controller.c"),
            Object(Matching, "RVLFaceLib/RFL_MiddleDatabase.c"),
            Object(Matching, "RVLFaceLib/RFL_MakeRandomFace.c"),
            Object(Matching, "RVLFaceLib/RFL_DefaultDatabase.c"),
            Object(Matching, "RVLFaceLib/RFL_DataUtility.c"),
            Object(Matching, "RVLFaceLib/RFL_NWC24.c"),
            Object(Matching, "RVLFaceLib/RFL_Format.c"),
        ],
    },
    {
        "lib": "RP",
        "mw_version": config.linker_version,
        "cflags": cflags_rp,
        # "progress_category": "game",
        "objects": [
            Object(NonMatching, "RP/RPKernel/RPSysSystem.c"),
            Object(NonMatching, "main.c"),
            Object(NonMatching, "RP/RPSystem/RPSysSceneCreator.c"),
            Object(NonMatching, "RP/RPSystem/RPSysScene.c"),
            Object(NonMatching, "RP/RPSystem/RPSysRenderMode.c"),
            Object(NonMatching, "RP/RPSystem/RPSysSceneMgr.c"),
            Object(NonMatching, "RP/RPSystem/RPSysProjectLocal.c"),
            Object(NonMatching, "RP/RPSystem/RPSysGameConfig.c"),
            Object(NonMatching, "RP/RPSystem/RPSysLoadScene.c"),
            Object(NonMatching, "RP/RPSystem/RPSysResourceManager.c"),
            Object(NonMatching, "RP/RPSystem/RPSysQueuedScene.c"),
            Object(NonMatching, "RP/RPSystem/RPSysCommonObject.c"),
            Object(NonMatching, "RP/RPSystem/RPSysDvdStatus.c"),
            Object(NonMatching, "RP/RPSystem/RPSysSaveDataMgr.c"),
            Object(NonMatching, "RP/RPSystem/RPSportsSystemData.c"),
            Object(NonMatching, "RP/RPSystem/RPSportsPlayerData.c"),
            Object(NonMatching, "RP/RPSystem/RPSysFontManager.c"),
            Object(NonMatching, "RP/RPSystem/RPSysSaveData.c"),
            Object(NonMatching, "RP/RPSystem/RPSysPauseMgr.c"),
            Object(NonMatching, "RP/RPSystem/RPPartySystemData.c"),
            Object(NonMatching, "RP/RPSystem/RPPartyPlayerData.c"),
            Object(NonMatching, "RP/RPSystem/RPSysPlayerMgr.c"),
            Object(NonMatching, "RP/RPSystem/RPSysPlayer.c"),
            Object(NonMatching, "RP/RPKernel/IRPSysHostIOSocket.c"),
            Object(NonMatching, "RP/RPKernel/RPSysHostIOSocketManager.c"),
            Object(NonMatching, "RP/RPKernel/RPSysTextWriter.c"),
            Object(NonMatching, "RP/RPKernel/RPSysMessage.c"),
            Object(NonMatching, "RP/RPKernel/RPSysKokeshi.c"),
        ],
    },
]

# Optional extra categories for progress tracking
config.progress_categories = [
    ProgressCategory("nw4r", "NW4R"),
    ProgressCategory("egg", "EGG"),
    ProgressCategory("sdk", "SDK"),
    ProgressCategory("rfl", "RVLFaceLib"),
    # Disabled since RP is not fully split
    # ProgressCategory("game", "Game"),
]
config.progress_all = False
config.progress_each_module = args.verbose
config.progress_use_fancy = True
config.progress_code_fancy_frac = 2500
config.progress_code_fancy_item = "skill points"
config.progress_data_fancy_frac = 100
config.progress_data_fancy_item = "stamps"

if args.mode == "configure":
    # Write build.ninja and objdiff.json
    generate_build(config)
elif args.mode == "progress":
    # Print progress and write progress.json
    calculate_progress(config)
else:
    sys.exit("Unknown mode: " + args.mode)
