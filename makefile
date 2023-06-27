#-------------------------------------------------------------------------------
# Files
#-------------------------------------------------------------------------------
TARGET_COL := wii

TARGET := ogws_us_r1

BUILD_DIR := build

# Inputs
S_FILES := $(wildcard asm/*.s)
#C_FILES := $(wildcard src/*.c)
LDSCRIPT := $(BUILD_DIR)/ldscript.lcf

# Outputs
DOL     := $(BUILD_DIR)/main.dol
ELF     := $(DOL:.dol=.elf)
MAP     := $(BUILD_DIR)/$(TARGET).map
#O_FILES := $(S_FILES:.s=.o) $(C_FILES:.c=.o)

include obj_files.mk

#-------------------------------------------------------------------------------
# Tools
#-------------------------------------------------------------------------------

# Programs
AS       := tools/powerpc-eabi-as
OBJCOPY  := tools/powerpc-eabi-objcopy
CPP      := cpp -P
CC       := tools/codewarrior/GC/3.0/mwcceppc
CC_TRK   := tools/codewarrior/GC/2.7/mwcceppc
CC_MSL   := tools/codewarrior/GC/3.0a3/mwcceppc
LD       := tools/codewarrior/GC/3.0/mwldeppc
ELF2DOL  := tools/elf2dol
SHA1SUM  := sha1sum
PYTHON   := python
PPROC    := tools/postprocess.py
PROGRESS := tools/calcprogress/calcprogress.py

# Options
ASFLAGS := -mgekko -I include
LDFLAGS := -map $(MAP) -mapunused -proc gekko -fp hard -nodefaults -nofail
#CFLAGS  := -Cpp_exceptions off -proc gekko -fp hard -O2,p -i include

#
# Module flags
#

# Compiler flags for the Metrowerks Target Resident Kernel (MetroTRK)
CFLAGS_TRK := -lang c -sdata 0 -use_lmw_stmw on -enum int -inline deferred -Cpp_exceptions off -proc gekko -fp hard -O4,p -ir include/MetroTRK -I- -i include -ir include/MSL -nodefaults
# Compiler flags for the CodeWarrior runtime library
CFLAGS_RUNTIME := -use_lmw_stmw on -enum int -inline auto -rostr -Cpp_exceptions off -proc gekko -fp hard -O4,p -ir include/MetroTRK -I- -i include -ir include/MSL -nodefaults
# Compiler flags for the Metrowerks Standard Library (MSL)
CFLAGS_MSL := -lang c -use_lmw_stmw on -enum int -inline auto -rostr -D_IEEE_LIBM -Cpp_exceptions off -proc gekko -fp hard -O4,p -ir include/MetroTRK -I- -i include -ir include/MSL -nodefaults
# Compiler flags for NintendoWare for Revolution
CFLAGS_NW4R := -lang c99 -enum int -inline auto -Cpp_exceptions off -RTTI off -proc gekko -fp hard -O4,p  -ir include/nw4r -I- -Iinclude -ir include/MSL -ir include/revolution -nodefaults
# Compiler flags for EGG
CFLAGS_EGG := -lang c99 -enum int -inline auto -Cpp_exceptions off -RTTI off -proc gekko -fp hard -O4,p  -ir include/egg -ir include/nw4r -I- -Iinclude -ir include/MSL -ir include/revolution -nodefaults -rostr -str pool
# Compiler flags for RVL SDK
CFLAGS_RVL := -lang c99 -enum int -O4,p -inline auto -ipa file -volatileasm -Cpp_exceptions off -RTTI off -proc gekko -fp hard -I- -Iinclude -ir include/MSL -ir include/revolution -nodefaults

#
# One-off file flags
#
# EXI/EXIBios.c
CFLAGS_EXIBIOS := -lang c99 -enum int -O3 -inline auto -ipa file -volatileasm -Cpp_exceptions off -RTTI off -proc gekko -fp hard -I- -Iinclude -ir include/MSL -ir include/revolution -nodefaults

# elf2dol needs to know these in order to calculate sbss correctly.
BSS_PDHR := 9

ASM_DIRS := asm \
	asm/revolution asm/nw4r asm/egg asm/runtime asm/MSL asm/MetroTRK asm/RVLFaceLib asm/homebuttonMiniLib asm/RP \
	asm/MetroTRK/debugger/Export asm/MetroTRK/debugger/Os asm/MetroTRK/debugger/Os/dolphin asm/MetroTRK/debugger/Portable asm/MetroTRK/debugger/Processor asm/MetroTRK/gamedev \
	asm/revolution/NdevExi2AD asm/revolution/KPAD asm/revolution/PAD asm/revolution/WPAD asm/revolution/EUART asm/revolution/EXI asm/revolution/FS \
	asm/revolution/GX asm/revolution/IPC asm/revolution/MEM asm/revolution/MTX asm/revolution/NAND asm/revolution/OS asm/revolution/SC \
	asm/revolution/USB asm/revolution/VI asm/revolution/WUD asm/revolution/AI asm/revolution/ARC asm/revolution/AX asm/revolution/AXFX \
	asm/revolution/BASE asm/revolution/BTE asm/revolution/DB asm/revolution/DSP asm/revolution/DVD asm/revolution/SI asm/revolution/TPL \
	asm/revolution/WENC asm/revolution/CNT asm/revolution/ESP asm/revolution/NET asm/revolution/NWC24 asm/revolution/VF \
	asm/nw4r/ut asm/nw4r/ef asm/nw4r/math asm/nw4r/snd asm/nw4r/g3d asm/nw4r/lyt \
	asm/egg/gfx asm/egg/math asm/egg/core asm/egg/audio asm/egg/util \
	asm/RP/RPKernel

SRC_DIRS := src \
	revolution nw4r egg runtime MetroTRK MSL RVLFaceLib homebuttonMiniLib \
	MetroTRK/debugger/Export MetroTRK/debugger/Os MetroTRK/debugger/Os/dolphin MetroTRK/debugger/Portable MetroTRK/debugger/Processor MetroTRK/gamedev \
	revolution/NdevExi2AD revolution/KPAD revolution/PAD revolution/WPAD revolution/EUART revolution/EXI revolution/FS \
	revolution/GX revolution/IPC revolution/MEM revolution/MTX revolution/NAND revolution/OS revolution/SC \
	revolution/USB revolution/VI revolution/WUD revolution/AI revolution/ARC revolution/AX revolution/AXFX \
	revolution/BASE revolution/BTE revolution/DB revolution/DSP revolution/DVD revolution/SI revolution/TPL \
	revolution/WENC revolution/CNT revolution/ESP revolution/NET revolution/NWC24 revolution/VF \
	nw4r/ut nw4r/ef nw4r/math nw4r/snd nw4r/g3d nw4r/lyt \
	egg/math egg/core egg/audio egg/util egg/gfx egg/prim

# Flags for Riidefi's post-processing script
PPROCFLAGS := -fsymbol-fixup

# Flags for progress calculation script
PROGRESSFLAGS := --dol=$(DOL) --map=$(MAP)

#-------------------------------------------------------------------------------
# Recipes
#-------------------------------------------------------------------------------

default: all

all: $(DOL)

ALL_DIRS := build $(BUILD_DIR) $(addprefix $(BUILD_DIR)/,$(SRC_DIRS) $(ASM_DIRS))
$(warning ALL_DIRS is $(ALL_DIRS))
# Make sure build directory exists before compiling anything
DUMMY != mkdir -p $(ALL_DIRS)


.PHONY: tools

$(LDSCRIPT): ldscript.lcf
	$(CPP) -MMD -MP -MT $@ -MF $@.d -I include/ -I . -DBUILD_DIR=$(BUILD_DIR) -o $@ $<
#	cp ldscript.lcf $(LDSCRIPT)

$(DOL): $(ELF) | tools
	$(ELF2DOL) $< $@ $(BSS_PDHR) $(TARGET_COL)
	$(SHA1SUM) -c $(TARGET).sha1
	$(PROGRESS) $(PROGRESSFLAGS)

clean:
	rm -fdr build
	$(MAKE) -C tools clean

tools:
	$(MAKE) -C tools

$(ELF): $(O_FILES) $(LDSCRIPT)
	$(LD) $(LDFLAGS) -o $@ -lcf $(LDSCRIPT) $(O_FILES)
# The Metrowerks linker doesn't generate physical addresses in the ELF program headers. This fixes it somehow.
#	$(OBJCOPY) $@ $@

$(BUILD_DIR)/%.o: %.s
	$(AS) $(ASFLAGS) -o $@ $<
	$(PPROC) $(PPROCFLAGS) $@

$(BUILD_DIR)/nw4r/%.o: src/nw4r/%.cpp
	$(CC) $(CFLAGS_NW4R) -c -o $@ $<
	$(PPROC) $(PPROCFLAGS) $@

$(BUILD_DIR)/egg/%.o: src/egg/%.cpp
	$(CC) $(CFLAGS_EGG) -c -o $@ $<
	$(PPROC) $(PPROCFLAGS) $@

$(BUILD_DIR)/runtime/%.o: src/runtime/%.c
	$(CC) -lang c $(CFLAGS_RUNTIME) -c -o $@ $<
	$(PPROC) $(PPROCFLAGS) $@

$(BUILD_DIR)/runtime/%.o: src/runtime/%.cpp
	$(CC) -lang c++ $(CFLAGS_RUNTIME) -c -o $@ $<
	$(PPROC) $(PPROCFLAGS) $@

$(BUILD_DIR)/MSL/%.o: src/MSL/%.c
	$(CC_MSL) $(CFLAGS_MSL) -c -o $@ $<
	$(PPROC) $(PPROCFLAGS) $@

$(BUILD_DIR)/MetroTRK/%.o: src/MetroTRK/%.c
	$(CC_TRK) $(CFLAGS_TRK) -c -o $@ $<
	$(PPROC) $(PPROCFLAGS) $@

# EXIBios is a special case, compiled differently from rest of library
$(BUILD_DIR)/revolution/EXI/EXIBios.o: src/revolution/EXI/EXIBios.c
	$(CC) $(CFLAGS_EXIBIOS) -c -o $@ $<
	$(PPROC) $(PPROCFLAGS) $@

$(BUILD_DIR)/revolution/%.o: src/revolution/%.c
	$(CC) $(CFLAGS_RVL) -c -o $@ $<
	$(PPROC) $(PPROCFLAGS) $@