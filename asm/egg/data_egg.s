.include "macros.inc"

.section .data, "wa"

.balign 0x8
.global switch_80397EE0
switch_80397EE0:
    .long 0x8009cc74
    .long 0x8009cc80
    .long 0x8009cc8c
    .long 0x8009cc98
    .long 0x8009cca4
    .long 0x8009ccb4
    .long 0x8009ccc4
.global lbl_80397EFC
lbl_80397EFC:
	.incbin "baserom.dol", 0x393FFC, 0x3C
.global lbl_80397F38
lbl_80397F38:
	.incbin "baserom.dol", 0x394038, 0x1C
.global lbl_80397F54
lbl_80397F54:
	.incbin "baserom.dol", 0x394054, 0x14
.global lbl_80397F68
lbl_80397F68:
	.incbin "baserom.dol", 0x394068, 0x18
.global lbl_80397F80
lbl_80397F80:
	.incbin "baserom.dol", 0x394080, 0x18
.global lbl_80397F98
lbl_80397F98:
	.incbin "baserom.dol", 0x394098, 0x18
.global lbl_80397FB0
lbl_80397FB0:
	.incbin "baserom.dol", 0x3940B0, 0x18
.global lbl_80397FC8
lbl_80397FC8:
	.incbin "baserom.dol", 0x3940C8, 0x1C
.global lbl_80397FE4
lbl_80397FE4:
	.incbin "baserom.dol", 0x3940E4, 0x18
.global lbl_80397FFC
lbl_80397FFC:
	.incbin "baserom.dol", 0x3940FC, 0x14
.global lbl_80398010
lbl_80398010:
	.incbin "baserom.dol", 0x394110, 0x28
.global lbl_80398038
lbl_80398038:
	.incbin "baserom.dol", 0x394138, 0xC
.global lbl_80398044
lbl_80398044:
	.incbin "baserom.dol", 0x394144, 0x18
.global lbl_8039805C
lbl_8039805C:
	.incbin "baserom.dol", 0x39415C, 0x1C
.global lbl_80398078
lbl_80398078:
	.incbin "baserom.dol", 0x394178, 0x14
.global lbl_8039808C
lbl_8039808C:
	.incbin "baserom.dol", 0x39418C, 0x1C
.global lbl_803980A8
lbl_803980A8:
	.incbin "baserom.dol", 0x3941A8, 0x10
    