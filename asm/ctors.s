.include "macros.inc"

# .data2 = .ctors

.section .ctors, "a"  # 0x80355080 - 0x80355260
.global lbl_80355080
lbl_80355080:
	.incbin "baserom.dol", 0x351180, 0x1E0
