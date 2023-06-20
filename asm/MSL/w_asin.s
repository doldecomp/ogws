.include "macros.inc"

.section .text, "ax"
.global asin
asin:
/* 800C0E74 000BBD74  4B FF C6 AC */	b __ieee754_asin
