.include "macros.inc"

.section .rodata, "a"

.balign 0x8

.global lbl_80379FF8
lbl_80379FF8:
	.incbin "baserom.dol", 0x3760F8, 0x60
.global lbl_8037A058
lbl_8037A058:
	.incbin "baserom.dol", 0x376158, 0x98
.global lbl_8037A0F0
lbl_8037A0F0:
	.incbin "baserom.dol", 0x3761F0, 0x88
.global lbl_8037A178
lbl_8037A178:
	.incbin "baserom.dol", 0x376278, 0x68

.balign 0x8
