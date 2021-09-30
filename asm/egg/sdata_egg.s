.include "macros.inc"

.section .sdata, "wa"

.balign 0x8

.global lbl_804BD4E8
lbl_804BD4E8:
	.incbin "baserom.dol", 0x3C7168, 0x4
.global lbl_804BD4EC
lbl_804BD4EC:
	.incbin "baserom.dol", 0x3C716C, 0x4
.global lbl_804BD4F0
lbl_804BD4F0:
	.incbin "baserom.dol", 0x3C7170, 0x8
.global lbl_804BD4F8
lbl_804BD4F8:
	.incbin "baserom.dol", 0x3C7178, 0x8
    