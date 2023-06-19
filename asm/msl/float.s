.include "macros.inc"

.section .sdata, "wa"
.balign 0x8
.global __float_nan
__float_nan:
	.incbin "baserom.dol", 0x3C71C8, 0x4
.global __float_huge
__float_huge:
	.incbin "baserom.dol", 0x3C71CC, 0x4
.global __double_huge
__double_huge:
	.incbin "baserom.dol", 0x3C71D0, 0x8
