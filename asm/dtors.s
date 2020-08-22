.include "macros.inc"

# .data3 = .dtors

.section .dtors, "a"  # 0x80355260 - 0x80355280
.global lbl_80355260
lbl_80355260:
	.incbin "baserom.dol", 0x351360, 0x20
