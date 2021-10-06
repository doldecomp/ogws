.include "macros.inc"

.section .sdata2, "a"

.balign 0x8

.global lbl_804C0998
lbl_804C0998:
	.incbin "baserom.dol", 0x3C95D8, 0x8
.global lbl_804C09A0
lbl_804C09A0:
	.incbin "baserom.dol", 0x3C95E0, 0x4
.global lbl_804C09A4
lbl_804C09A4:
	.incbin "baserom.dol", 0x3C95E4, 0x4
.global lbl_804C09A8
lbl_804C09A8:
	.incbin "baserom.dol", 0x3C95E8, 0x4
.global lbl_804C09AC
lbl_804C09AC:
	.incbin "baserom.dol", 0x3C95EC, 0x4
.global lbl_804C09B0
lbl_804C09B0:
	.incbin "baserom.dol", 0x3C95F0, 0x8
