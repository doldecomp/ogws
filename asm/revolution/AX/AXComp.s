.include "macros.inc"

.section .data, "wa"
.balign 0x8
.global __AXCompressorTable # ALIGN(32)
__AXCompressorTable:
    .balign 32
	.incbin "baserom.dol", 0x3A7980, 0xFC0