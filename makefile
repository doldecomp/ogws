#-------------------------------------------------------------------------------
# Files
#-------------------------------------------------------------------------------

# Inputs
S_FILES := $(wildcard asm/*.s)
#C_FILES := $(wildcard src/*.c)
LDSCRIPT := ldscript.lcf

# Outputs
DOL     := main.dol
ELF     := $(DOL:.dol=.elf)
MAP     := ogws_us_r1.map
#O_FILES := $(S_FILES:.s=.o) $(C_FILES:.c=.o)
O_FILES := $(S_FILES:.s=.o)

#-------------------------------------------------------------------------------
# Tools
#-------------------------------------------------------------------------------

# Programs
AS      := tools/powerpc-eabi-as
OBJCOPY := tools/powerpc-eabi-objcopy
CC      := tools/mwcceppc
LD      := tools/mwldeppc
ELF2DOL := tools/elf2dol
SHA1SUM := sha1sum

# Options
ASFLAGS := -mgekko -I include
LDFLAGS := -map $(MAP)
#CFLAGS  := -Cpp_exceptions off -proc gekko -fp hard -O2,p -i include

#-------------------------------------------------------------------------------
# Recipes
#-------------------------------------------------------------------------------

.PHONY: tools

$(DOL): $(ELF) | tools
	$(ELF2DOL) $< $@
	$(SHA1SUM) -c ogws_us_r1.sha1

clean:
	rm -f $(DOL) $(ELF) $(O_FILES) $(MAP)
	$(MAKE) -C tools clean

tools:
	$(MAKE) -C tools

$(ELF): $(O_FILES) $(LDSCRIPT)
	$(LD) $(LDFLAGS) -o $@ -lcf $(LDSCRIPT) $(O_FILES)
# The Metrowerks linker doesn't generate physical addresses in the ELF program headers. This fixes it somehow.
	$(OBJCOPY) $@ $@

%.o: %.s
	$(AS) $(ASFLAGS) -o $@ $<

#%.o: %.c
#	$(CC) $(CFLAGS) -c -o $@ $<
