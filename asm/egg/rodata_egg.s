.include "macros.inc"

.section .rodata, "a"

.balign 0x8

.global lbl_8037A0F0
lbl_8037A0F0:
	.incbin "baserom.dol", 0x3761F0, 0x88
.global lbl_8037A178
lbl_8037A178:
	.incbin "baserom.dol", 0x376278, 0x68

.balign 0x8
