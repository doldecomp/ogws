.include "macros.inc"

.section .sdata, "wa"  # 0x804BD380 - 0x804BE9E0

.balign 0x8

.global lbl_804BD880
lbl_804BD880:
	.incbin "baserom.dol", 0x3C7500, 0x8
.global lbl_804BD888
lbl_804BD888:
	.incbin "baserom.dol", 0x3C7508, 0x8
