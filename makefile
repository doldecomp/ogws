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

O_FILES := $(INIT_O_FILES) $(EXTAB_O_FILES) $(EXTABINDEX_O_FILES) $(TEXT_O_FILES) \
           $(CTORS_O_FILES) $(DTORS_O_FILES) $(RODATA_O_FILES) $(DATA_O_FILES)    \
           $(DATA6_O_FILES) $(BSS_O_FILES) $(SDATA_O_FILES) $(SBSS_O_FILES) \
		   $(SDATA2_O_FILES) $(SBSS2_O_FILES)

#-------------------------------------------------------------------------------
# Tools
#-------------------------------------------------------------------------------

# Programs
AS      := tools/powerpc-eabi-as
OBJCOPY := tools/powerpc-eabi-objcopy
CPP     := cpp -P
CC      := tools/mwcceppc
LD      := tools/mwldeppc
ELF2DOL := tools/elf2dol
SHA1SUM := sha1sum

# Options
ASFLAGS := -mgekko -I include
LDFLAGS := -map $(MAP) -fp hard -nodefaults
#CFLAGS  := -Cpp_exceptions off -proc gekko -fp hard -O2,p -i include

# Compiler flags for the Target Resident Kernel
CFLAGS_TRK := -Cpp_exceptions off -proc gekko -fp hard -O4,s -i include/RevoSDK/TRK -nodefaults
# Compiler flags for NintendoWare for Revolution
CFLAGS_NW4R := -Cpp_exceptions off -proc gekko -fp hard -O4,p -i include/nw4r/ut -nodefaults

# elf2dol needs to know these in order to calculate sbss correctly.
SDATA_PDHR := 10
SBSS_PDHR := 11

#-------------------------------------------------------------------------------
# Recipes
#-------------------------------------------------------------------------------

default: all

all: $(DOL)

ALL_DIRS := build $(BUILD_DIR) $(addprefix $(BUILD_DIR)/,$(SRC_DIRS) $(ASM_DIRS))

# Make sure build directory exists before compiling anything
DUMMY != mkdir -p $(ALL_DIRS)


.PHONY: tools

$(LDSCRIPT): ldscript.lcf
	$(CPP) -MMD -MP -MT $@ -MF $@.d -I include/ -I . -DBUILD_DIR=$(BUILD_DIR) -o $@ $<
#	cp ldscript.lcf $(LDSCRIPT)

$(DOL): $(ELF) | tools
	$(ELF2DOL) $< $@ $(SDATA_PDHR) $(SBSS_PDHR) $(TARGET_COL)
	$(SHA1SUM) -c $(TARGET).sha1

clean:
	rm -f $(DOL) $(ELF) $(O_FILES) $(MAP) $(LDSCRIPT)
	$(MAKE) -C tools clean

tools:
	$(MAKE) -C tools

$(ELF): $(O_FILES) $(LDSCRIPT)
	$(LD) $(LDFLAGS) -o $@ -lcf $(LDSCRIPT) $(O_FILES)
# The Metrowerks linker doesn't generate physical addresses in the ELF program headers. This fixes it somehow.
#	$(OBJCOPY) $@ $@

$(BUILD_DIR)/%.o: %.s
	$(AS) $(ASFLAGS) -o $@ $<

$(BUILD_DIR)/RevoSDK/TRK/%.o: src/RevoSDK/TRK/%.c
	$(CC) $(CFLAGS_TRK) -c -o $@ $<

$(BUILD_DIR)/nw4r/%.o: src/nw4r/%.cpp
	$(CC) $(CFLAGS_NW4R) -c -o $@ $<
