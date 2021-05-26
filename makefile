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
CC       := tools/mwcceppc
CC_OLD   := tools/old/mwcceppc
LD       := tools/mwldeppc
ELF2DOL  := tools/elf2dol
SHA1SUM  := sha1sum
PYTHON   := python
PPROC    := tools/postprocess.py
PROGRESS := tools/calcprogress.py

# Options
ASFLAGS := -mgekko -I include
LDFLAGS := -map $(MAP) -mapunused -proc gekko -fp hard -nodefaults -nofail
#CFLAGS  := -Cpp_exceptions off -proc gekko -fp hard -O2,p -i include

# Compiler flags for the Target Resident Kernel
CFLAGS_TRK := -Cpp_exceptions off -proc gekko -fp hard -O4,s -i include/RevoSDK/TRK -I- -i include -i include/STL -nodefaults
# Compiler flags for NintendoWare for Revolution
CFLAGS_NW4R := -lang c99 -enum int -inline auto -Cpp_exceptions off -RTTI off -proc gekko -fp hard -O4,p  -ir include/nw4r -I- -Iinclude -Iinclude/STL -ir include/RevoSDK -nodefaults
# Compiler flags for EGG
CFLAGS_EGG := -lang c99 -enum int -inline auto -Cpp_exceptions off -RTTI off -proc gekko -fp hard -O4,p  -ir include/egg -ir include/nw4r -I- -Iinclude -Iinclude/STL -ir include/RevoSDK -nodefaults -rostr -str pool
# Compiler flags for ARC
CFLAGS_ARC := -lang c99 -enum int -O4,p -inline auto -ipa file -volatileasm -Cpp_exceptions off -RTTI off -proc gekko -fp hard -I- -Iinclude -Iinclude/STL -ir include/RevoSDK -nodefaults

# elf2dol needs to know these in order to calculate sbss correctly.
BSS_PDHR := 9

ASM_DIRS := asm \
	asm/RevoSDK asm/nw4r asm/egg \
	asm/RevoSDK/TRK \
	asm/nw4r/ut asm/nw4r/ef asm/nw4r/math asm/nw4r/snd asm/nw4r/g3d asm/nw4r/lyt \
	asm/egg/gfx asm/egg/prim asm/egg/math asm/egg/core asm/egg/audio asm/egg/util

SRC_DIRS := nw4r egg RevoSDK \
	nw4r/ut nw4r/ef nw4r/math nw4r/snd nw4r/g3d nw4r/lyt \
	egg/math egg/core egg/audio \
	RevoSDK/TRK RevoSDK/TRK_old RevoSDK/ARC

# Flags for Riidefi's post-processing script
PPROCFLAGS := -fsymbol-fixup

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
	$(PROGRESS)

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

$(BUILD_DIR)/RevoSDK/TRK/%.o: src/RevoSDK/TRK/%.c
	$(CC) $(CFLAGS_TRK) -c -o $@ $<

$(BUILD_DIR)/RevoSDK/TRK_old/%.o: src/RevoSDK/TRK_old/%.c
	$(CC_OLD) $(CFLAGS_TRK) -c -o $@ $<

$(BUILD_DIR)/nw4r/%.o: src/nw4r/%.cpp
	$(CC) $(CFLAGS_NW4R) -c -o $@ $<
	$(PPROC) $(PPROCFLAGS) $@

$(BUILD_DIR)/egg/%.o: src/egg/%.cpp
	$(CC) $(CFLAGS_EGG) -c -o $@ $<
	$(PPROC) $(PPROCFLAGS) $@

$(BUILD_DIR)/RevoSDK/ARC/%.o: src/RevoSDK/ARC/%.c
	$(CC) $(CFLAGS_ARC) -c -o $@ $<
	$(PPROC) $(PPROCFLAGS) $@