.include "macros.inc"

# .data0 = extab

.section extab_, "wa"  # 0x800064E0 - 0x80006C20
	.incbin "baserom.dol", 0x34FF80, 0x740