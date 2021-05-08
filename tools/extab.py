#!/usr/bin/env python3

################################################################################
#                                 Description                                  #
################################################################################
# extab.py: Disassembles the extab/extabindex sections of the OGWS DOL.        #
# The user can optionally supply an output path for both assembly files.       #
# Syntax: extab.py {EXTAB_OUT_PATH} {EXTABINDEX_OUT_PATH}                      #
#                                                                              #
# Requirements:                                                                #
#   - extab.py must be in the repo's \tools\ directory.                        #
#   - The DOL must have been built at least once, so that the build map can    #
#   be referenced.                                                             #
################################################################################




###############################################
#                                             #
#                  Imports                    #
#                                             #
###############################################

import os
from sys import argv
import struct

###############################################
#                                             #
#                 Constants                   #
#                                             #
###############################################

UNK_VALUE = 0xD58AC

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
EXTAB_SECTION = {
    "START" : 0x800064e0, # Virtual address of section
    "OFFSET" : 0x34ff80,  # Local offset (in file)
    "SIZE" : 0x740        # Size (B)
}
EXTABINDEX_SECTION = {
    "START" : 0x80006c20, # Virtual address of section
    "OFFSET" : 0x3506c0,  # Local offset (in file)
    "SIZE" : 0xac0        # Size (B)
}

PPC_INST_SIZE = 4
EXTABINDEX_ENTRY_SIZE = PPC_INST_SIZE * 3

# Table placed at the end of extabindex,
# used by __init_cpp_exceptions/__register_fragment
"""
struct _eti_init_info_ {
    void *pExtabindex; // aka ptr to first entry
    void *p_eti_init_info_;
    void *pFirstFunc;
    u32 totalCodeSize;
    u32 unk[4];
}
"""
INIT_TABLE_LEN = 10 * PPC_INST_SIZE

EXTABINDEX_HEADER = \
    ".include \"macros.inc\"\n\n" \
    ".section extabindex_, \"wa\"\n\n"

EXTAB_HEADER = \
    ".include \"macros.inc\"\n\n" \
    ".section extab_, \"wa\"\n\n"

###############################################
#                                             #
#                   Classes                   #
#                                             #
###############################################

class ExtabIndexEntry:
    def __init__(self, funcPtr : str, funcSize : str, handlerPtr : int):
        self.funcPtr = funcPtr
        self.funcSize = funcSize
        self.handlerPtr = handlerPtr
        self.symbol = proc(getSymbolByAddr(self.funcPtr))

    def ToString(self) -> str:
        return "\n".join([f".global _index_{self.symbol}",
                          f"_index_{self.symbol}:",
                          f"    .long {self.symbol}",
                          f"    .long 0x{self.funcSize}",
                          f"    .long _unwind_{self.symbol}",
                           "\n"])

class ExtabEntry:
    def __init__(self, parent : ExtabIndexEntry, code : list):
        self.parent = parent
        self.code = code

    def ToString(self) -> str:
        code = ""
        for i in range(len(self.code) // PPC_INST_SIZE):
            currLong = self.code[i * 4 : (i + 1) * 4].hex()
            # Sometimes a destructor is inserted after the stack-unwinding instructions.
            # This will catch those occurrences and label them appropriately.
            currSymb = getSymbolByAddr(currLong)
            code = "".join([code, f"    .long {currSymb}", "\n"]); i += 4

        return "\n".join([f".global _unwind_{self.parent.symbol}",
                          f"_unwind_{self.parent.symbol}:",
                           code]) + "\n"

###############################################
#                                             #
#                  Functions                  #
#                                             #
###############################################

def proc(symbol):
    for sub in substitutions:
        symbol = symbol.replace(sub[0], sub[1])
    return symbol

def toHex32(val) -> str:
    return "{:08x}".format(val)

def getU32(data, ofs) -> int:
    return ((data[ofs + 0] << 24) |
            (data[ofs + 1] << 16) |
            (data[ofs + 2] << 8)  |
            (data[ofs + 3] << 0))

def getU32BE(data, ofs) -> int:
    return ((data[ofs + 3] << 24) |
            (data[ofs + 2] << 16) |
            (data[ofs + 1] << 8)  |
            (data[ofs + 0] << 0))

def getSymbolByAddr(addr) -> str:
    for key in symbols:
        if key == addr:
            return format(symbols[key])
    return "0x" + str(addr)

###############################################
#                                             #
#                Entrypoint                   #
#                                             #
###############################################

if __name__ == "__main__":

    # Symbol dictionary
    symbols = dict()

    # Args (optional)
    customOut = True
    try:
        EXTAB_OUT = argv[1]
        EXTABINDEX_OUT = argv[2]
    except IndexError:
        print("No output path specified. Writing to extab.s and extabindex.s, respectively.")
        customOut = False

    # Build symbol dictionary
    with open("build/ogws_us_r1.map", "r") as f:
        map = f.readlines() 

    assert len(map) > 1, "Are you sure the map file is not empty from a failed build?"

    for i in map:
        # Get symbol virtual address
        addr = i[18:26]
        # Get symbol name
        symbEnd = i[39:].find(' ')
        symb = i[39:symbEnd+39]
        # Add to dict
        symbols[addr] = symb

    # Read baserom data
    with open("include/baserom.dol", "rb") as f:
        baserom = bytearray(f.read())

    # Split section data
    # baserom[offset : offset + size]
    extabindex_ = baserom[
        EXTABINDEX_SECTION["OFFSET"] :
        EXTABINDEX_SECTION["OFFSET"] + EXTABINDEX_SECTION["SIZE"]]

    extab_ = baserom[
        EXTAB_SECTION["OFFSET"] :
        EXTAB_SECTION["OFFSET"] + EXTAB_SECTION["SIZE"]]

    # Build extabindex entries
    extabindex = list()
    i = 0
    totalCodeSize = 0
    while i < (EXTABINDEX_SECTION["SIZE"] - INIT_TABLE_LEN):
        func = toHex32(getU32(extabindex_, i)); i+= PPC_INST_SIZE
        size = getU32(extabindex_, i); i += PPC_INST_SIZE
        totalCodeSize += size
        handler = getU32(extabindex_, i); i += PPC_INST_SIZE
        extabindex.append(ExtabIndexEntry(func, toHex32(size), handler))

    # Write extabindex
    if (customOut):
        f = open(EXTABINDEX_OUT, "w+")
    else:
        f = open("extabindex.s", "w+")

    f.write(EXTABINDEX_HEADER)
    for i in extabindex:
        f.writelines(i.ToString())

    # Write eti info
    f.write("# For __init_cpp_exceptions/__register_fragment\n")
    f.write(".global _eti_init_info_\n")
    f.write("_eti_init_info_:\n")
    f.write(f"    .long _index_{extabindex[0].symbol} # &extabindex[0]\n")
    f.write(f"    .long _eti_init_info_ # &_eti_init_info_\n")
    f.write(f"    .long {extabindex[0].symbol} # &extabindex[0].func\n")
    f.write(f"    .long 0x{toHex32(UNK_VALUE)} # unkValue\n")
    f.writelines(["    .long 0x00000000 # Padding\n"] * 4)
    f.write(".balign 0x8\n")
    f.close()

    # Parse extab
    extab = list()
    for j in range(len(extabindex)):
        currentHandler = extabindex[j].handlerPtr - EXTAB_SECTION["START"]

        # The last extab entry will end at the end of the extab section
        if (j == len(extabindex) - 1):
            extab.append(ExtabEntry(extabindex[j], extab_[currentHandler : ]))
        # All other extab entries end at the start of the next entry (the next extabindex entry's handler ptr)
        else:
            nextHandler = extabindex[j + 1].handlerPtr - EXTAB_SECTION["START"]
            extab.append(ExtabEntry(extabindex[j], extab_[currentHandler : nextHandler]))

    # Write extab
    if (customOut):
        f = open(EXTAB_OUT, "w+")
    else:
        f = open("extab.s", "w+")

    f.write(EXTAB_HEADER)
    for i in extab:
        f.writelines(i.ToString())
    f.close()

    print("Done!")
