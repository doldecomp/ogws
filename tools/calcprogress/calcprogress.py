#!/usr/bin/env python3

from src.main import main
from src.progress import SliceGroup, Slice

# Can track non-code sections, but it's not really necessary.
# Slice groups in dependancy order (except TRK).
# (Currently broken until BTE/RFL/HBM are split (why?))
EXEC_SLICE_GROUPS = [
    # SliceGroup("Runtime", [
    #     Slice(0x80004000, 0x80004134), # .init
    #     Slice(0x800B1750, 0x800B2414), # .text
    #     ]),
    # SliceGroup("MSL", [
    #     Slice(0x800B2414, 0x800C10D4) # .text
    #     ]),
    # SliceGroup("MetroTRK", [
    #     Slice(0x800C10D4, 0x800C6810) # .text
    #     ]),
    # SliceGroup("RVL SDK", [
    #     Slice(0x800C6810, 0x80167B2C) # .text
    #     ]),
    # SliceGroup("RVLFaceLib", [
    #     Slice(0x80167B2C, 0x801774DC) # .text
    #     ]),
    # SliceGroup("NW4R", [
    #     Slice(0x800076E0, 0x800838A8) # .text
    #     ]),
    # SliceGroup("homeButtonMiniLib", [
    #     Slice(0x801774DC, 0x80182BAC) # .text
    #     ]),
    # SliceGroup("EGG", [
    #     Slice(0x800838A8, 0x800B1750) # .text
    #     ])
]

def exec_progress_callback(src_code: int, total_code: int, src_data: int, total_data: int):
    """Executable (DOL/REL) progress callback.
    Any game-specific counters or extra things should go here.
    """


def slice_group_progress_callback(name: str, src_size: int, total_size: int):
    """Slice group progress callback.
    Any game-specific counters or extra things should go here.
    """


if __name__ == "__main__":
    main(EXEC_SLICE_GROUPS, exec_progress_callback,
         slice_group_progress_callback)
