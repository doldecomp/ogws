.include "macros.inc"

.section .data, "wa"

.balign 0x8
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
    