.include "macros.inc"

.section .sdata, "wa"
.balign 0x8
.global __OSArenaLo
__OSArenaLo:
	.long 0xFFFFFFFF
.global s_mem2ArenaLo
s_mem2ArenaLo:
	.long 0xFFFFFFFF

.section .sbss, "wa"
.balign 0x8
.global __OSArenaHi
__OSArenaHi:
	.skip 0x4
.global s_mem2ArenaHi
s_mem2ArenaHi:
	.skip 0x4

.section .text, "ax"
.global OSGetMEM1ArenaHi
OSGetMEM1ArenaHi:
/* 800EDBA8 000E8AA8  80 6D 9B E8 */	lwz r3, __OSArenaHi-_SDA_BASE_(r13)
/* 800EDBAC 000E8AAC  4E 80 00 20 */	blr 

.global OSGetMEM2ArenaHi
OSGetMEM2ArenaHi:
/* 800EDBB0 000E8AB0  80 6D 9B EC */	lwz r3, s_mem2ArenaHi-_SDA_BASE_(r13)
/* 800EDBB4 000E8AB4  4E 80 00 20 */	blr 

.global OSGetArenaHi
OSGetArenaHi:
/* 800EDBB8 000E8AB8  80 6D 9B E8 */	lwz r3, __OSArenaHi-_SDA_BASE_(r13)
/* 800EDBBC 000E8ABC  4E 80 00 20 */	blr 

.global OSGetMEM1ArenaLo
OSGetMEM1ArenaLo:
/* 800EDBC0 000E8AC0  80 6D 83 68 */	lwz r3, __OSArenaLo-_SDA_BASE_(r13)
/* 800EDBC4 000E8AC4  4E 80 00 20 */	blr 

.global OSGetMEM2ArenaLo
OSGetMEM2ArenaLo:
/* 800EDBC8 000E8AC8  80 6D 83 6C */	lwz r3, s_mem2ArenaLo-_SDA_BASE_(r13)
/* 800EDBCC 000E8ACC  4E 80 00 20 */	blr 

.global OSGetArenaLo
OSGetArenaLo:
/* 800EDBD0 000E8AD0  80 6D 83 68 */	lwz r3, __OSArenaLo-_SDA_BASE_(r13)
/* 800EDBD4 000E8AD4  4E 80 00 20 */	blr 

.global OSSetMEM1ArenaHi
OSSetMEM1ArenaHi:
/* 800EDBD8 000E8AD8  90 6D 9B E8 */	stw r3, __OSArenaHi-_SDA_BASE_(r13)
/* 800EDBDC 000E8ADC  4E 80 00 20 */	blr 

.global OSSetMEM2ArenaHi
OSSetMEM2ArenaHi:
/* 800EDBE0 000E8AE0  90 6D 9B EC */	stw r3, s_mem2ArenaHi-_SDA_BASE_(r13)
/* 800EDBE4 000E8AE4  4E 80 00 20 */	blr 

.global OSSetArenaHi
OSSetArenaHi:
/* 800EDBE8 000E8AE8  90 6D 9B E8 */	stw r3, __OSArenaHi-_SDA_BASE_(r13)
/* 800EDBEC 000E8AEC  4E 80 00 20 */	blr 

.global OSSetMEM1ArenaLo
OSSetMEM1ArenaLo:
/* 800EDBF0 000E8AF0  90 6D 83 68 */	stw r3, __OSArenaLo-_SDA_BASE_(r13)
/* 800EDBF4 000E8AF4  4E 80 00 20 */	blr 

.global OSSetMEM2ArenaLo
OSSetMEM2ArenaLo:
/* 800EDBF8 000E8AF8  90 6D 83 6C */	stw r3, s_mem2ArenaLo-_SDA_BASE_(r13)
/* 800EDBFC 000E8AFC  4E 80 00 20 */	blr 

.global OSSetArenaLo
OSSetArenaLo:
/* 800EDC00 000E8B00  90 6D 83 68 */	stw r3, __OSArenaLo-_SDA_BASE_(r13)
/* 800EDC04 000E8B04  4E 80 00 20 */	blr 

.global OSAllocFromMEM1ArenaLo
OSAllocFromMEM1ArenaLo:
/* 800EDC08 000E8B08  80 0D 83 68 */	lwz r0, __OSArenaLo-_SDA_BASE_(r13)
/* 800EDC0C 000E8B0C  38 A4 FF FF */	addi r5, r4, -1
/* 800EDC10 000E8B10  7C A6 28 F8 */	nor r6, r5, r5
/* 800EDC14 000E8B14  7C A4 02 14 */	add r5, r4, r0
/* 800EDC18 000E8B18  38 05 FF FF */	addi r0, r5, -1
/* 800EDC1C 000E8B1C  7C C0 00 38 */	and r0, r6, r0
/* 800EDC20 000E8B20  7C 60 1A 14 */	add r3, r0, r3
/* 800EDC24 000E8B24  7C 83 22 14 */	add r4, r3, r4
/* 800EDC28 000E8B28  7C 03 03 78 */	mr r3, r0
/* 800EDC2C 000E8B2C  38 04 FF FF */	addi r0, r4, -1
/* 800EDC30 000E8B30  7C C0 00 38 */	and r0, r6, r0
/* 800EDC34 000E8B34  90 0D 83 68 */	stw r0, __OSArenaLo-_SDA_BASE_(r13)
/* 800EDC38 000E8B38  4E 80 00 20 */	blr 
