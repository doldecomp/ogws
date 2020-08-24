INIT_O_FILES := \
	build/RevoSDK/TRK/memcpy.o \
	build/RevoSDK/TRK/__fill_mem.o \
	build/RevoSDK/TRK/memset.o \
	build/asm/RevoSDK/TRK/mem_TRK.o \
	build/asm/RevoSDK/TRK/__exception.o \
	build/asm/RevoSDK/TRK/dolphin_trk.o \
	build/asm/RevoSDK/TRK/__start.o \
	build/asm/RevoSDK/TRK/__ppc_eabi_init.o \

EXTAB_O_FILES := build/asm/extab.o

EXTABINDEX_O_FILES := build/asm/extabindex.o

TEXT_O_FILES := \
	build/nw4r/ut/ut_List.o \
	build/asm/nw4r/ut/list.o \
	build/asm/nw4r/ut/ut_LinkListImpl.o \
	build/asm/nw4r/ut/binaryFile.o \
	build/asm/nw4r/ut/ut_CharStrmReader.o \
	build/asm/nw4r/ut/ut_TagProcessorBase.o \
	build/asm/nw4r/ut/ut_IOStream.o \
	build/asm/nw4r/ut/ut_FileStream.o \
	build/asm/nw4r/ut/ut_DvdFileStream.o \
	build/asm/nw4r/ut/ut_DvdLockedFileStream.o \
	build/asm/nw4r/ut/ut_NandFileStream.o \
	build/asm/nw4r/ut/ut_LC.o \
	build/asm/nw4r/ut/ut_RomFont.o \
	build/asm/text.o

CTORS_O_FILES := build/asm/ctors.o

DTORS_O_FILES := build/asm/dtors.o

RODATA_O_FILES := build/asm/rodata.o

DATA_O_FILES := build/asm/data.o

DATA6_O_FILES := build/asm/data6.o

BSS_O_FILES := build/asm/bss.o

SDATA_O_FILES := build/asm/sdata.o

SBSS_O_FILES := build/asm/sbss.o

SDATA_O_FILES := build/asm/sdata.o

SBSS2_O_FILES := build/asm/sbss2.o

SDATA2_O_FILES := build/asm/sdata2.o

