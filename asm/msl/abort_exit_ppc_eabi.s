.include "macros.inc"

.section .sbss, "wa"
.balign 0x8
.global __stdio_exit
__stdio_exit:
	.skip 0x8
