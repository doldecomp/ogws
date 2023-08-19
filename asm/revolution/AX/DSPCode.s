.include "macros.inc"

.section .data, "wa"
.balign 0x8
.global axDspSlave # ALIGN(32)
axDspSlave:
.balign 32
	.incbin "baserom.dol", 0x3A8940, 0x2000

.section .sdata, "wa"
.balign 0x8
.global axDspInitVector
axDspInitVector:
	.short 0x0010
.global axDspResumeVector
axDspResumeVector:
	.short 0x0037
.global axDspSlaveLength
axDspSlaveLength:
	.short 0x2000
