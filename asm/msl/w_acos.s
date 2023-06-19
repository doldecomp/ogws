.include "macros.inc"

.section .text, "ax"
.global acos
acos:
/* 800C0E70 000BBD70  4B FF C3 EC */	b __ieee754_acos
