.include "macros.inc"

# .data1 = extabindex

.section extabindex_, "wa"  # 0x80006C20 - 0x800076E0
	.incbin "baserom.dol", 0x3506C0, 0xA98
.global lbl_800076B8
lbl_800076B8:
	.incbin "baserom.dol", 0x351158, 0x20
