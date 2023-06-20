.include "macros.inc"

.section .text, "ax"
.global pow
pow:
/* 800C0E80 000BBD80  4B FF CE D8 */	b __ieee754_pow
