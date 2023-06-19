.include "macros.inc"

.section .sdata, "wa"
.global random_next
random_next:
	.long 1

.section .text, "ax"
.global rand
rand:
/* 800B76A8 000B25A8  3C 60 41 C6 */	lis r3, 0x41C64E6D@ha
/* 800B76AC 000B25AC  80 8D 81 C0 */	lwz r4, random_next-_SDA_BASE_(r13)
/* 800B76B0 000B25B0  38 03 4E 6D */	addi r0, r3, 0x41C64E6D@l
/* 800B76B4 000B25B4  7C 64 01 D6 */	mullw r3, r4, r0
/* 800B76B8 000B25B8  38 03 30 39 */	addi r0, r3, 0x3039
/* 800B76BC 000B25BC  90 0D 81 C0 */	stw r0, random_next-_SDA_BASE_(r13)
/* 800B76C0 000B25C0  54 03 84 7E */	rlwinm r3, r0, 0x10, 0x11, 0x1f
/* 800B76C4 000B25C4  4E 80 00 20 */	blr 
