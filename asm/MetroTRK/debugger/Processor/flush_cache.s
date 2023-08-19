.include "macros.inc"

.section .text, "ax"
.global TRK_flush_cache
TRK_flush_cache:
/* 800C39A0 000BE8A0  3C A0 FF FF */	lis r5, 0xFFFFFFF1@h
/* 800C39A4 000BE8A4  60 A5 FF F1 */	ori r5, r5, 0xFFFFFFF1@l
/* 800C39A8 000BE8A8  7C A5 18 38 */	and r5, r5, r3
/* 800C39AC 000BE8AC  7C 65 18 50 */	subf r3, r5, r3
/* 800C39B0 000BE8B0  7C 84 1A 14 */	add r4, r4, r3
lbl_800C39B4:
/* 800C39B4 000BE8B4  7C 00 28 6C */	dcbst 0, r5
/* 800C39B8 000BE8B8  7C 00 28 AC */	dcbf 0, r5
/* 800C39BC 000BE8BC  7C 00 04 AC */	sync 0
/* 800C39C0 000BE8C0  7C 00 2F AC */	icbi 0, r5
/* 800C39C4 000BE8C4  30 A5 00 08 */	addic r5, r5, 8
/* 800C39C8 000BE8C8  34 84 FF F8 */	addic. r4, r4, -8
/* 800C39CC 000BE8CC  40 80 FF E8 */	bge lbl_800C39B4
/* 800C39D0 000BE8D0  4C 00 01 2C */	isync 
/* 800C39D4 000BE8D4  4E 80 00 20 */	blr 
