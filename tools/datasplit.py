#!/usr/bin/env python3

################################################################################
#                                 Description                                  #
################################################################################
# datasplit: Used for disassembling labels in the OGWS DOL's data sections.    #
# *Technically* works with non 4-byte aligned data, but isn't recommended.     #
# Syntax: datasplit.py {VIRT_START_ADDR} {VIRT_END_ADDR}                       #
#                                                                              #
# Supported sections:                                                          #
# .ctors, .dtors, .rodata, .data, .sdata, .sdata2                              #
#                                                                              #
# Requirements:                                                                #
#   - datasplit.py must be in the repo's \tools\ directory.                    #
#   - The DOL must have been built at least once, so that the build map can    #
#   be referenced.                                                             #
#                                                                              #
# Ex: datasplit.py 80396454 80396468                                           #
#                                                                              #
# DOL data:           Datasplit output:                                        #
# 00 00 00 00         .long 0                                                  #
# 00 00 00 00         .long 0                                                  #
# 80 04 b9 dc         .long __dt__Q44nw4r3snd6detail5VoiceFv                   #
# 80 04 e0 b0         .long InvalidateData__Q44nw4r3snd6detail5VoiceFPCvPCv    #
# 80 04 df 64         .long InvalidateWaveData__Q44nw4r3snd6detail5VoiceFPCvPC #
################################################################################




###############################################
#                                             #
#                  Imports                    #
#                                             #
###############################################

import os
import sys
import re
import struct

###############################################
#                                             #
#                 Constants                   #
#                                             #
###############################################

# From postprocess
substitutions = (
    ('<',  '$$0'),
    ('>',  '$$1'),
    ('@',  '$$2'),
    ('\\', '$$3'),
    (',',  '$$4'),
    ('-',  '$$5'),
)

# Section info
CTORS_SECTION = {
    "START" : 0x80355080, # Virtual address of section
    "OFFSET" : 0x351180,  # Local offset (in file)
    "SIZE" : 0x1e0      # Size (B)
}
DTORS_SECTION = {
    "START" : 0x80355260, # Virtual address of section
    "OFFSET" : 0x351360,  # Local offset (in file)
    "SIZE" : 0x20      # Size (B)
}
FILE_SIZE = 0x20500
RODATA_SECTION = {
    "START" : 0x80375780, # Virtual address of section
    "OFFSET" : 0x371880,  # Local offset (in file)
    "SIZE" : 0x1E300      # Size (B)
}
DATA_SECTION = {
    "START" : 0x80393A80,
    "OFFSET" : 0x38FB80,
    "SIZE" : 0x37480
}
SDATA_SECTION = {
    "START" : 0x804BD380,
    "OFFSET" : 0x3C7000,
    "SIZE" : 0x1660
}
SDATA2_SECTION = {
    "START" : 0x804BFA20,
    "OFFSET" : 0x3C8660,
    "SIZE" : 0x6FC0
}
BSS_SIZE = 0xF2480
SBSS_SIZE = 0x1040

###############################################
#                                             #
#                  Functions                  #
#                                             #
###############################################

# Symbol dictionary
symbols = dict()

def format(symbol):
    for sub in substitutions:
        symbol = symbol.replace(sub[0], sub[1])
    return symbol

def toHex32(val) -> str:
    return "{:08x}".format(val)

def toF32_7(val) -> str:
    return "{:.7f}".format(val)

def getU32(data, ofs) -> int:
    return ((data[ofs + 0] << 24) |
            (data[ofs + 1] << 16) |
            (data[ofs + 2] << 8) |
            (data[ofs + 3] << 0))

def getU32BE(data, ofs) -> int:
    return ((data[ofs + 3] << 24) |
            (data[ofs + 2] << 16) |
            (data[ofs + 1] << 8) |
            (data[ofs + 0] << 0))

def getF32(data, ofs) -> float:
    return (struct.unpack('!f', bytes.fromhex(
        toHex32(getU32(data, ofs))
    ))[0])

def getF32BE(data, ofs) -> float:
    return (struct.unpack('!f', bytes.fromhex(
        toHex32(getU32BE(data, ofs))
    ))[0])

def isValidWiiPtr(addr) -> bool:
    return (
            # MEM1, cached
            (addr >= 0x80004000 and addr <= 0x817FFFFF) or
            # MEM1, uncached
            (addr >= 0xC0000000 and addr <= 0xC17FFFFF) or
            # MEM2, cached
            (addr >= 0x90000000 and addr <= 0x93FFFFFF) or
            # MEM2, uncached
            (addr >= 0xD0000000 and addr <= 0xD3FFFFFF) or
            # Hollywood/Starlet registers
            (addr >= 0xCD000000 and addr <= 0xCD008000)
    )

def getSymbolByAddr(addr) -> str:
    for key in symbols:
        if key == addr:
            return format(symbols[key])
    return "0x" + addr

###############################################
#                                             #
#                Entrypoint                   #
#                                             #
###############################################

if __name__ == "__main__":

    # Build symbol dictionary
    with open("build/ogws_us_r1.map", "r") as f:
        map = f.readlines() 

    for i in map:
        # Get symbol virtual address
        addr = i[18:26]
        # Get symbol name
        symbEnd = i[39:].find(' ')
        symb = i[39:symbEnd+39]
        # Add to dict
        symbols[addr] = symb


    # Process user input
    # Non-numeric chars are discarded so that args such as "lbl_80004000" can be used.
    LBL_START = int(re.sub("^[a-z_]*", "", sys.argv[1]), 16)
    LBL_END = int(re.sub("^[a-z_]*", "", sys.argv[2]), 16)
    try:
        assert(isValidWiiPtr(LBL_START) and isValidWiiPtr(LBL_END))
    except AssertionError:
        print("\nEither your starting or ending address is invalid or has been processed incorrectly.\n" +
        "Please make sure you have entered the label correctly.\n\n" +
        "Valid input includes:\n" +
        "    80004000\n" + "    lbl_80004000\n")
        exit()

    # Read baserom data
    with open("include/baserom.dol", "rb") as f:
        baserom = bytearray(f.read())

    # Split section data
    # baserom[offset : offset + size]
    ctors = baserom[
        CTORS_SECTION["OFFSET"] :
        CTORS_SECTION["OFFSET"] + CTORS_SECTION["SIZE"]]
    dtors = baserom[
        DTORS_SECTION["OFFSET"] :
        DTORS_SECTION["OFFSET"] + DTORS_SECTION["SIZE"]]
    rodata = baserom[
        RODATA_SECTION["OFFSET"] :
        RODATA_SECTION["OFFSET"] + RODATA_SECTION["SIZE"]]
    data = baserom[
        DATA_SECTION["OFFSET"] :
        DATA_SECTION["OFFSET"] + DATA_SECTION["SIZE"]]
    sdata = baserom[
        SDATA_SECTION["OFFSET"] :
        SDATA_SECTION["OFFSET"] + SDATA_SECTION["SIZE"]]
    sdata2 = baserom[
        SDATA2_SECTION["OFFSET"] :
        SDATA2_SECTION["OFFSET"] + SDATA2_SECTION["SIZE"]]

    # Create contiguous section
    # ctors -> dtors -> file -> rodata -> data -> bss -> sdata -> sbss -> sdata2
    baserom = bytearray(ctors + dtors + bytearray(FILE_SIZE) + rodata + data + bytearray(BSS_SIZE) + sdata + bytearray(SBSS_SIZE) + sdata2)

    # Process data at label
    SECTION_BASE = CTORS_SECTION["START"] # Used to convert LBL_START into a local offset of baserom
    label_data = baserom[LBL_START - SECTION_BASE : LBL_END - SECTION_BASE]

    # Label header
    label_txt = ""
    label_txt += ".global lbl_" + hex(LBL_START)[2:].upper() + '\n'
    label_txt += "lbl_" + hex(LBL_START)[2:].upper() + ":\n"

    # Read label data byte by byte, and try to guess the data type
    offset = 0
    while True:
        # Check how many bytes of data are left
        if (len(label_data) == offset): break
        # If there are less than 4 bytes remaining, read individual bytes
        if (len(label_data) - offset < 4):
            for i in range(len(label_data) - offset):
                label_txt += (
                    ".byte " + hex(label_data[offset])
                    + "int=" + str(label_data[offset])
                )
                offset += 1
        # Check 4-byte data types
        else:
            current_u32 = getU32(label_data, offset)
            current_u32BE = getU32BE(label_data, offset)
            current_f32 = getF32(label_data, offset)
            offset += 4
            # Possible pointer?
            if (isValidWiiPtr(current_u32)):
                    label_txt += (
                        "    .long " + getSymbolByAddr(toHex32(current_u32)) + '\n'
                    )   
            else:
                label_txt += (
                    "    .long " + ("0" if (current_u32 == 0) else hex(current_u32))
                    + ((" # f32 = " + toF32_7(current_f32)) if (current_u32 != 0) else "")
                    + ((", u32 = " + str(current_u32BE) + '\n') if (current_u32 != 0) else "\n")
                )

    print(label_txt)
