.include "macros.inc"

.section .file, "a"  # 0x80355280 - 0x80375780

.global lbl_80355280
lbl_80355280:
	.incbin "baserom.dol", 0x351380, 0x20500
