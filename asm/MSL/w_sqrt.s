.include "macros.inc"

.section .text, "ax"
.global sqrt
sqrt:
/* 800C10D0 000BBFD0  4B FF FD B4 */	b __ieee754_sqrt
