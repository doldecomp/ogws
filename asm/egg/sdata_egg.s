.include "macros.inc"

.section .sdata, "wa"

.balign 0x8

.global lbl_804BD480
lbl_804BD480:
	.long 0x00200000
.global lbl_804BD484
lbl_804BD484:
	.single 0e1
.global lbl_804BD488
lbl_804BD488:
	.long 1
	.long 0
.global lbl_804BD490
lbl_804BD490:
	.string "pBuffer"
	.balign 4
.global lbl_804BD498
lbl_804BD498:
	.incbin "baserom.dol", 0x3C7118, 0x4
.global lbl_804BD49C
lbl_804BD49C:
	.incbin "baserom.dol", 0x3C711C, 0x4
.global lbl_804BD4A0
lbl_804BD4A0:
	.incbin "baserom.dol", 0x3C7120, 0x8
.global lbl_804BD4A8
lbl_804BD4A8:
	.incbin "baserom.dol", 0x3C7128, 0x8
.global lbl_804BD4B0
lbl_804BD4B0:
	.incbin "baserom.dol", 0x3C7130, 0x4
.global lbl_804BD4B4
lbl_804BD4B4:
	.incbin "baserom.dol", 0x3C7134, 0x4
.global lbl_804BD4B8
lbl_804BD4B8:
	.incbin "baserom.dol", 0x3C7138, 0x8
.global lbl_804BD4C0
lbl_804BD4C0:
	.incbin "baserom.dol", 0x3C7140, 0x8
.global lbl_804BD4C8
lbl_804BD4C8:
	.incbin "baserom.dol", 0x3C7148, 0x8
.global lbl_804BD4D0
lbl_804BD4D0:
	.incbin "baserom.dol", 0x3C7150, 0x8
.global lbl_804BD4D8
lbl_804BD4D8:
	.incbin "baserom.dol", 0x3C7158, 0x4
.global lbl_804BD4DC
lbl_804BD4DC:
	.incbin "baserom.dol", 0x3C715C, 0x4
.global lbl_804BD4E0
lbl_804BD4E0:
	.incbin "baserom.dol", 0x3C7160, 0x8
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
    