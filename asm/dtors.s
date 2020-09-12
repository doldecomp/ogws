.include "macros.inc"

.section .dtors, "a"  # 0x80355260 - 0x80355280

.global global_dtors
global_dtors:
.4byte func_800B184C
.4byte func_800B22C4
.fill 0x18