.include "macros.inc"

.section .rodata, "a"

.balign 0x8

.global lbl_80379CD8
lbl_80379CD8:
	.incbin "baserom.dol", 0x375DD8, 0x10
.global lbl_80379CE8
lbl_80379CE8:
	.incbin "baserom.dol", 0x375DE8, 0xC
.global lbl_80379CF4
lbl_80379CF4:
	.incbin "baserom.dol", 0x375DF4, 0xFC
.global lbl_80379DF0
lbl_80379DF0:
	.incbin "baserom.dol", 0x375EF0, 0xA0
.global lbl_80379E90
lbl_80379E90:
	.incbin "baserom.dol", 0x375F90, 0xC8
.global lbl_80379F58
lbl_80379F58:
	.incbin "baserom.dol", 0x376058, 0xC
.global lbl_80379F64
lbl_80379F64:
	.incbin "baserom.dol", 0x376064, 0x94
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
