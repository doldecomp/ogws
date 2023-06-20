.include "macros.inc"

.section .text, "ax"
.global atan2
atan2:
/* 800C0E78 000BBD78  4B FF C9 40 */	b __ieee754_atan2
