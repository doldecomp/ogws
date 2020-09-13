.include "macros.inc"

.section .ctors, "a"  # 0x80355080 - 0x80355260

.global global_ctors
global_ctors:
.4byte func_800B2288
