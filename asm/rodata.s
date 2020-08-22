.include "macros.inc"

# .data4 = .rodata???

.section .rodata, "a"  # 0x80355280 - 0x80375780
.global lbl_80355280
lbl_80355280:
	.incbin "baserom.dol", 0x351380, 0x1AD84
.global lbl_80370004
lbl_80370004:
	.incbin "baserom.dol", 0x36C104, 0x577C
