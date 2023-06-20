.include "macros.inc"

.section .text, "ax"
.global fmod
fmod:
/* 800C0E7C 000BBD7C  4B FF CB AC */	b __ieee754_fmod
